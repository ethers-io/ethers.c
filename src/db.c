#include <stdio.h>
#include <string.h>

#include "firefly-db.h"
#include "firefly-hash.h"

#include "db-contracts.h"
#include "db-networks.h"

const char* ffx_db_getNetworkNameU32(uint32_t chainId) {
    for (int i = 0; i < _ffx_db_networksCount; i++) {
        uint32_t id = _ffx_db_networksIndex[2 * i];
        if (id == chainId) {
            return &_ffx_db_networksStrings[_ffx_db_networksIndex[2 * i + 1]];
        }
    }
    return NULL;
}

const char* ffx_db_getNetworkName(FfxBigInt *chainId) {
    for (int i = 0; i < _ffx_db_networksCount; i++) {
        uint32_t id = _ffx_db_networksIndex[2 * i];
        if (ffx_bigint_cmpU32(chainId, id) == 0) {
            return &_ffx_db_networksStrings[_ffx_db_networksIndex[2 * i + 1]];
        }
    }
    return NULL;
}

const char* ffx_db_getNetworkToken(FfxBigInt *chainId) {
    const char *result = ffx_db_getNetworkName(chainId);
    if (result == NULL) { return NULL; }
    return &result[strlen(result) + 1];
}

/*
const char* ffx_db_getNetwork(FfxBigInt *chainId) {
    if (ffx_bigint_cmpU32(chainId, 0x7fffffff) >= 0) {
        return NULL;
    }
    return ffx_db_getNetworkU32(ffx_bigint_getU32(chainId).value);
}
*/

/*
static void dumpbuf(const char* header, uint8_t *data, size_t length) {
    printf("%s", header);
    for (int i = 0; i < length; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}
*/

int cmpbuf32(const uint32_t *a, const uint32_t *b, size_t length) {
    for (int i = 0; i < length; i++) {
        int d = ((int)(b[i])) - ((int)(a[i]));
        if (d) { return d; }
    }
    return 0;
}


const char* ffx_db_getContractName(FfxBigInt *chainId, FfxDataResult *addr) {
    if (addr->length != 20) { return NULL; }

    // Compute the lookup key keccak256(address ++ u256(chainId))[0: 12]
    uint8_t data[52] = { 0 };
    memcpy(&data[0], addr->bytes, 20);
    ffx_bigint_getBytes(chainId, &data[20]);

    ffx_hash_keccak256(data, data, sizeof(data));

    // Search for a matching entry
    for (int i = 0; i < _ffx_db_contractsCount; i++) {
        size_t offset = (_ffx_db_contractsWidth + 1) * i;
        const uint32_t *key = &_ffx_db_contractsIndex[offset];
        if (cmpbuf32((uint32_t*)data, key, _ffx_db_contractsWidth) == 0) {
            offset = _ffx_db_contractsIndex[offset + _ffx_db_contractsWidth];
            return &_ffx_db_contractsStrings[offset];
        }
    }

    return NULL;

}

