#include <assert.h>
#include <string.h>

// DEBUG
#include <stdio.h>   

#include "secp256k1_ecdh.h"
#include "secp256k1_preallocated.h"
#include "secp256k1_recovery.h"

#include "firefly-ecc.h"

#define loadPubkey(_pubkey,_data) \
    { \
        status = secp256k1_ec_pubkey_parse(ctx, &(_pubkey), \
          (_data)->data, sizeof((_data)->data)); \
    } \

#define savePubkey(_data,_pubkey,_comp) \
    { \
        size_t length = sizeof((_data)->data); \
        status = secp256k1_ec_pubkey_serialize(ctx, (_data)->data, \
          &length, &(_pubkey), \
          (_comp) ? SECP256K1_EC_COMPRESSED: SECP256K1_EC_UNCOMPRESSED); \
        if (length != sizeof((_data)->data)) { status = 0; } \
    }

#define zeroify(v) \
  do { memset(&v, 0, sizeof(v)); } while (0);

static secp256k1_context* getContext(uint8_t *randomize) {
    static uint8_t _ctxBuffer[208];
    static secp256k1_context* ctx = NULL;

    if (ctx == NULL) {
        static int count = 0;

        count++;

        size_t size = secp256k1_context_preallocated_size(
          SECP256K1_CONTEXT_NONE);

        if (size > sizeof(_ctxBuffer)) {
            printf("ERROR: _ctxBuffer must be at least %d bytes\n", (int)size);
        }

        assert(size <= sizeof(_ctxBuffer));

        ctx = secp256k1_context_preallocated_create(
          _ctxBuffer, SECP256K1_CONTEXT_NONE);

        if (randomize) {
            int status = secp256k1_context_randomize(ctx, randomize);
            assert(status == 1);
        } else {
            printf("WARNING: ECC library not randomized\n");
        }

        // Make sure we weren't double-init-ed as this could corrupt the
        // context if it changed (randomized) during an operation
        assert(count == 1);
    }

    return ctx;
}

void ffx_ec_init(uint8_t *randomize) {
    getContext(randomize);
}

bool ffx_ec_computePubkey(FfxEcPubkey *pubkeyOut, const FfxEcPrivkey *privkey) {

    secp256k1_context *ctx = getContext(NULL);
    int status = 1;

    secp256k1_pubkey pubkey;
    status = secp256k1_ec_pubkey_create(ctx, &pubkey, privkey->data);

    if (status) {
        savePubkey(pubkeyOut, pubkey, false);
    }

    zeroify(pubkey);

    return !!status;
}

bool ffx_ec_computeCompPubkey(FfxEcCompPubkey *pubkeyOut,
  const FfxEcPrivkey *privkey) {

    secp256k1_context *ctx = getContext(NULL);
    int status = 1;

    secp256k1_pubkey pubkey;
    status = secp256k1_ec_pubkey_create(ctx, &pubkey, privkey->data);

    if (status) {
        savePubkey(pubkeyOut, pubkey, true);
    }

    zeroify(pubkey);

    return !!status;
}

bool ffx_ec_recoverPubkey(FfxEcPubkey *pubkeyOut, const FfxEcDigest *digest,
  const FfxEcSignature *sig) {

    secp256k1_context *ctx = getContext(NULL);
    int status = 1;

    int recid = sig->data[64];
    if (recid == 27 || recid == 28) { recid -= 27; }
    if (recid != 0 && recid != 1) { return false; }

    secp256k1_pubkey recPubkey;

    secp256k1_ecdsa_recoverable_signature recSig;
    status = secp256k1_ecdsa_recoverable_signature_parse_compact(ctx,
      &recSig, sig->data, recid);

    if (status) {
        status = secp256k1_ecdsa_recover(ctx, &recPubkey, &recSig,
          digest->data);

        if (status) {
            savePubkey(pubkeyOut, recPubkey, false);
        }
    }

    zeroify(recSig);
    zeroify(recPubkey);

    return !!status;
}

bool ffx_ec_signDigest(FfxEcSignature *sigOut, const FfxEcPrivkey *privkey,
  const FfxEcDigest *digest) {

    secp256k1_context *ctx = getContext(NULL);
    int status = 1;

    secp256k1_ecdsa_recoverable_signature recSig;
    int recid = -1;

    status = secp256k1_ecdsa_sign_recoverable(ctx, &recSig, digest->data,
      privkey->data, NULL, NULL);

    if (status) {
        status = secp256k1_ecdsa_recoverable_signature_serialize_compact(ctx,
          sigOut->data, &recid, &recSig);

        if (status) {
            sigOut->data[64] = 27 + recid;
        }
    }

    zeroify(recSig);
    recid = -1;

    return !!status;
}

bool ffx_ec_compressPubkey(FfxEcCompPubkey *pubkeyOut,
  const FfxEcPubkey *_pubkey) {

    secp256k1_context *ctx = getContext(NULL);
    int status = 1;

    secp256k1_pubkey pubkey;
    loadPubkey(pubkey, _pubkey);

    if (status) {
        savePubkey(pubkeyOut, pubkey, true);
    }

    zeroify(pubkey);

    return true;
}

bool ffx_ec_decompressPubkey(FfxEcPubkey *pubkeyOut,
  const FfxEcCompPubkey *_pubkey) {

    secp256k1_context *ctx = getContext(NULL);
    int status = 1;

    secp256k1_pubkey pubkey;
    loadPubkey(pubkey, _pubkey);

    if (status) {
        savePubkey(pubkeyOut, pubkey, false);
    }

    zeroify(pubkey);

    return true;
}

bool ffx_ec_modAddPrivkey(uint8_t *resultOut, const uint8_t *a, const uint8_t *b) {
    secp256k1_context *ctx = getContext(NULL);

    memcpy(resultOut, a, 32);

    return !!secp256k1_ec_seckey_tweak_add(ctx, resultOut, b);
}

bool ffx_ec_modMulPrivkey(uint8_t *resultOut, const uint8_t *a,
  const uint8_t *b) {

    secp256k1_context *ctx = getContext(NULL);

    memcpy(resultOut, a, 32);

    return !!secp256k1_ec_seckey_tweak_mul(ctx, resultOut, b);
}

bool ffx_ec_addPointsCompPubkey(uint8_t *resultOut, const uint8_t *a,
  const uint8_t *b) {

    secp256k1_context *ctx = getContext(NULL);
    int status = 1;

    secp256k1_pubkey points[2];
    const secp256k1_pubkey* ps[2];
    ps[0] = &points[0];
    ps[1] = &points[1];

    secp256k1_pubkey sum;

    status = secp256k1_ec_pubkey_parse(ctx, &points[0], a, 33);
    if (status) {
        status = secp256k1_ec_pubkey_parse(ctx, &points[1], b, 33);
        if (status) {
            status = secp256k1_ec_pubkey_combine(ctx, &sum, ps, 2);
            if (status) {
                //savePubkey(resultOut, sum, true);
                size_t length = 33;
                status = secp256k1_ec_pubkey_serialize(ctx, resultOut, &length, &sum,
                  SECP256K1_EC_COMPRESSED);

                if (length != 33) { status = 0; }
            }
        }
    }

    zeroify(points[0]);
    zeroify(points[1]);
    zeroify(sum);

    return !!status;
}

bool ffx_ec_computeSharedSecret(FfxEcSharedSecret *secretOut,
  const FfxEcPrivkey *privkey, const FfxEcPubkey *_pubkey) {

    secp256k1_context *ctx = getContext(NULL);
    int status = 1;

    secp256k1_pubkey pubkey;
    loadPubkey(pubkey, _pubkey);

    status = secp256k1_ecdh(ctx, secretOut->data, &pubkey, privkey->data,
      secp256k1_ecdh_hash_function_default, NULL);

    zeroify(pubkey);

    return !!status;
}
