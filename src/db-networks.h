#ifndef __DB_NETWORKS_H__
#define __DB_NETWORKS_H__

// This file is generated! Do NOT modify manually. See export-db-networks.mjs.

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stddef.h>
#include <stdint.h>

// Strings for each record
const char _ffx_db_networksStrings[] =
    "mainnet\0ETH\0"               // 0x00000 key: 1
    "Optimism\0ETH\0"              // 0x0000c key: 10
    "Polygon\0POL\0"               // 0x00019 key: 137
    "Base\0ETH\0"                  // 0x00025 key: 8453
    "Arbitrum\0ETH\0"              // 0x0002e key: 42161
    "Linea Sepolia\0sETH\0"        // 0x0003b key: 59141
    "Linea\0ETH\0"                 // 0x0004e key: 59144
    "Base Sepolia\0sETH\0"         // 0x00058 key: 84532
    "Arb Sepolia\0sETH\0"          // 0x0006a key: 421614
    "Sepolia\0sETH\0"              // 0x0007b key: 11155111
    "OP Sepolia\0sETH\0"           // 0x00088 key: 11155420
;

// Number of entries in indices
const size_t _ffx_db_networksCount = 22;

// Width (in words) of each key
const size_t _ffx_db_networksWidth = 1;

// Each key, followed by its index into Strings
const uint32_t _ffx_db_networksIndex[] = {
    0x00000001, 0x00000000, 0x0000000a, 0x0000000c, 0x00000089, 0x00000019,
    0x00002105, 0x00000025, 0x0000a4b1, 0x0000002e, 0x0000e705, 0x0000003b,
    0x0000e708, 0x0000004e, 0x00014a34, 0x00000058, 0x00066eee, 0x0000006a,
    0x00aa36a7, 0x0000007b, 0x00aa37dc, 0x00000088,
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DB_NETWORKS_H__ */