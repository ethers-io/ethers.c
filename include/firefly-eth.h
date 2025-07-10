#ifndef __FIREFLY_ETH_H__
#define __FIREFLY_ETH_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "firefly-ecc.h"


typedef struct FfxAddress {
    uint8_t data[20];
} FfxAddress;

typedef struct FfxChecksumAddress {
    // '0' 'x' [ 40 case-sensitive nibbles ] '\0'
    char text[43];
} FfxChecksumAddress;


#define FFX_INIT_ADDRESS(name,value) \
  FfxAddress name; memcpy(name.data, value, sizeof(name.data));

#define FFX_INIT_CHECKSUMADDRESS(name,value) \
  FfxChecksumAddress name; memcpy(name.data, value, sizeof(name.data));



/**
 *  Returns the EIP-155 %%checksumed%% address of %%address%.
 */
FfxChecksumAddress ffx_eth_checksumAddress(const FfxAddress *address);


/**
 *  Returns the address bytes for %%pubkey%%.
 */
FfxAddress ffx_eth_getAddress(const FfxEcPubkey *pubkey);


///////////////////////////////
// EIP-191 Personal Message

// @TODO: move this to hash and use it as the result type for sha256 adn keccak

typedef struct FfxHash256 {
    uint8_t data[32];
} FfxHash256;

/**
 *  The EIP-191 signed personal message prefix, including NULL-termination.
 */
extern const char FfxMessagePrefix[27];

FfxHash256 ffx_eth_hashMessage(const char* message);
FfxHash256 ffx_eth_hashMessageData(const uint8_t* data, size_t length);



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __FIREFLY_ETH_H__ */
