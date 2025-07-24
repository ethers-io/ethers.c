#ifndef __FIREFLY_DB_H__
#define __FIREFLY_DB_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "firefly-bigint.h"
#include "firefly-data.h"


const char* ffx_db_getNetworkName(FfxBigInt *chainId);
const char* ffx_db_getNetworkToken(FfxBigInt *chainId);

const char* ffx_db_getContractName(FfxBigInt *chainId, FfxDataResult *addr);

const char* ffx_db_getSelectorName(FfxDataResult *data);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __FIREFLY_DB_H__ */
