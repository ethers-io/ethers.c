#include <string.h>

#include "firefly-address.h"
#include "firefly-hash.h"


const char FfxMessagePrefix[27] = {
    0x19, 0x45, 0x74, 0x68, 0x65, 0x72, 0x65, 0x75, 0x6d, 0x20,
    0x53, 0x69, 0x67, 0x6e, 0x65, 0x64, 0x20, 0x4d, 0x65, 0x73,
    0x73, 0x61, 0x67, 0x65, 0x3a, 0x0a, 0x00
};


FfxChecksumAddress ffx_eth_checksumAddress(const FfxAddress *address) {

    const uint8_t *bytes = address->data;

    FfxChecksumAddress result;
    char *checksumOut = result.text;

    // Add the "0x" prefix and advance the pointer (so we can ignore it)
    checksumOut[0] = '0';
    checksumOut[1] = 'x';
    checksumOut += 2;

    // Place the ASCII representation of the address in checksumed
    const char * const HexNibbles = "0123456789abcdef";
    int offset = 0;
    for (int i = 0; i < 20; i++) {
        checksumOut[offset++] = HexNibbles[bytes[i] >> 4];
        checksumOut[offset++] = HexNibbles[bytes[i] & 0xf];
    }
    checksumOut[offset++] = 0;

    // Hash the ASCII representation
    uint8_t digest[FFX_KECCAK256_DIGEST_LENGTH] = { 0 };
    ffx_hash_keccak256(digest, (const uint8_t*)checksumOut, 40);

    // Uppercase any (alpha) nibble if the coresponding hash nibble >= 8
    for (int i = 0; i < 40; i += 2) {
        uint8_t c = digest[i >> 1];

        if (checksumOut[i] >= 'a' && ((c >> 4) >= 8)) {
            checksumOut[i] -= 0x20;
        }

        if (checksumOut[i + 1] >= 'a' && ((c & 0x0f) >= 8)) {
            checksumOut[i + 1] -= 0x20;
        }
    }

    return result;
}

FfxAddress ffx_eth_getAddress(const FfxEcPubkey *pubkey) {
    uint8_t hashed[32];
    ffx_hash_keccak256(hashed, &pubkey->data[1], 64);

    FfxAddress result;
    memcpy(result.data, &hashed[12], 20);

    return result;
}
