#include <string.h>

#include "firefly-eth.h"
#include "firefly-hash.h"


const char FfxMessagePrefix[27] = {
    0x19, 0x45, 0x74, 0x68, 0x65, 0x72, 0x65, 0x75, 0x6d, 0x20,
    0x53, 0x69, 0x67, 0x6e, 0x65, 0x64, 0x20, 0x4d, 0x65, 0x73,
    0x73, 0x61, 0x67, 0x65, 0x3a, 0x0a, 0x00
};

FfxHash256 ffx_eth_hashMessage(const char* message) {
    return ffx_eth_hashMessageData((const uint8_t*)message, strlen(message));
}

FfxHash256 ffx_eth_hashMessageData(const uint8_t* data, size_t length) {
    FfxHash256 result = { 0 };

    FfxKeccak256Context ctx = { 0 };
    ffx_hash_initKeccak256(&ctx);
    ffx_hash_updateKeccak256(&ctx, (const uint8_t*)FfxMessagePrefix, 26);

    char lengthStr[11] = { 0 };
    if (length == 0) {
        // The message length (and message) is just the string "0"
        lengthStr[0] = 0x30;
        ffx_hash_updateKeccak256(&ctx, (uint8_t*)lengthStr, 1);

    } else {
        // Add the message length as an ASCII string
        int i = 11;
        size_t lv = length;
        while (lv) {
            i--;
            lengthStr[i] = 0x30 + (lv % 10);
            lv /= 10;
        }
        ffx_hash_updateKeccak256(&ctx, (uint8_t*)&lengthStr[i], 11 - i);

        // Add the message payload
        ffx_hash_updateKeccak256(&ctx, data, length);
    }

    ffx_hash_finalKeccak256(&ctx, result.data);

    return result;
}
