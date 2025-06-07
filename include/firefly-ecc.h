#ifndef __FIREFLY_ECC_H__
#define __FIREFLY_ECC_H__

/**
 *  The ECC (Elliptic Curve Cryptography) library, which handles elliptic
 *  cryptographic primitives.
 *
 *  In general, these functions all operate on pointers to values so that
 *  no (potentially sensitive) data is left on the stack after returning.
 *
 *  The parameters are all structs with the explicit size of data expected,
 *  which mitigates buffer overruns caused by misallocating the correct
 *  space the operation was expecting.
 *
 *  As such they intentionally have a more "function" feel than a "method"
 *  feel, as the output is the first variable with the const inputs
 *  following.
 */


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdbool.h>
#include <stdint.h>


typedef struct FfxEcPubkey {
    uint8_t data[65];
} FfxEcPubkey;

typedef struct FfxEcCompPubkey {
    uint8_t data[33];
} FfxEcCompPubkey;

typedef struct FfxEcPrivkey {
    uint8_t data[32];
} FfxEcPrivkey;

typedef struct FfxEcDigest {
    uint8_t data[32];
} FfxEcDigest;

typedef struct FfxEcSignature {
    uint8_t data[65];
} FfxEcSignature;

typedef struct FfxEcSharedSecret {
    uint8_t data[32];
} FfxEcSharedSecret;


#define FFX_INIT_PUBKEY(name,value) \
  FfxEcPubkey name; memcpy(name.data, value, sizeof(name.data));

#define FFX_INIT_COMPPUBKEY(name,value) \
  FfxEcCompPubkey name; memcpy(name.data, value, sizeof(name.data));

#define FFX_INIT_PRIVKEY(name,value) \
  FfxEcPrivkey name; memcpy(name.data, value, sizeof(name.data));

#define FFX_INIT_DIGEST(name,value) \
  FfxEcDigest name; memcpy(name.data, value, sizeof(name.data));

#define FFX_INIT_SIGNATURE(name,value) \
  FfxEcSignature name; memcpy(name.data, value, sizeof(name.data));

#define FFX_INIT_SHARED_SECRET(name,value) \
  FfxEcSharedSecret name; memcpy(name.data, value, sizeof(name.data));


/**
 *  Optionally initialize the ECC library with %%randomize%% bytes to
 *  tweak the curve points to mitigate side-channel attacks.
 */
void ffx_ec_init(uint8_t *randomize);


bool ffx_ec_computePubkey(FfxEcPubkey *pubkeyOut, const FfxEcPrivkey *privkey);

bool ffx_ec_computeCompPubkey(FfxEcCompPubkey *pubkeyOut,
  const FfxEcPrivkey *privkey);

bool ffx_ec_recoverPubkey(FfxEcPubkey *pubkeyOut, const FfxEcDigest *digest,
  const FfxEcSignature *sig);

bool ffx_ec_signDigest(FfxEcSignature *sigOut, const FfxEcPrivkey *privkey,
  const FfxEcDigest *digest);

bool ffx_ec_compressPubkey(FfxEcCompPubkey *pubkeyOut,
  const FfxEcPubkey *_pubkey);

bool ffx_ec_decompressPubkey(FfxEcPubkey *pubkeyOut,
  const FfxEcCompPubkey *_pubkey);

bool ffx_ec_computeSharedSecret(FfxEcSharedSecret *secretOut,
  const FfxEcPrivkey *privkey, const FfxEcPubkey *pubkey);


// Low-level Point maths (used for BIP32 operations)
bool ffx_ec_modAddPrivkey(uint8_t *result32Out, const uint8_t *a32,
  const uint8_t *b32);
bool ffx_ec_modMulPrivkey(uint8_t *result32Out, const uint8_t *a32,
  const uint8_t *b32);
bool ffx_ec_addPointsCompPubkey(uint8_t *result33Out, const uint8_t *a33,
  const uint8_t *b33);

//bool ffx_ec_modAdd(FfxEcPrivkey *resultOut, FfxEcPrivkey *a, FfxEcPrivkey *b);
//bool ffx_ec_modMul(FfxEcPrivkey *resultOut, FfxEcPrivkey *a, FfxEcPrivkey *b);
//bool ffx_ec_addPoints(FfxEcPubkey *resultOut, const FfxEcPubkey *a,
//  const FfxEcPubkey *b);




#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __FIREFLY_ECC_H__ */
