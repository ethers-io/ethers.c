#ifndef __FIREFLY_ADDRESS_H__
#define __FIREFLY_ADDRESS_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


#define FFX_ADDRESS_LENGTH            (20)
#define FFX_ADDRESS_STRING_LENGTH     (43)

/**
 *  Computes the EIP-155 %%checksumed%% address of %%address%.
 *
 *  The %%address%% must be E_ADDRESS_LENGTH bytes and
 *  %%checksumed%% must be at least E_ADDRESS_STRING_LENGTH
 *  bytes.
 */
void ffx_eth_checksumAddress(char *checksumOut, const uint8_t *address);

void ffx_eth_computeAddress(uint8_t *addressOut, const uint8_t *pubkey);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __FIREFLY_ADDRESS_H__ */
