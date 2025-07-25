#ifndef __DB_CONTRACTS_H__
#define __DB_CONTRACTS_H__

// This file is generated! Do NOT modify manually. See export-db-contracts.mjs.

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stddef.h>
#include <stdint.h>

// Strings for each record
const char _ffx_db_contractsStrings[] =
    "Testnet USDC\0"               // 0x00000 key: 20347798b9604e1329aca150
      // Dup: "Testnet USDC\0"        0x00000 key: 560e7d9fd2c02793b9e80843
    "USDC Token\0"                 // 0x0000d key: 63a60b1c03d7c2688cbc7adb
    "DAI Token\0"                  // 0x00018 key: 6c5960195073111bbebc2173
    "ENS Registrar\0"              // 0x00022 key: 6e3c81233185953860f543eb
      // Dup: "USDC Token\0"          0x0000d key: 71caeb431420c82aaee1c031
      // Dup: "Testnet USDC\0"        0x00000 key: 7324a1b1776b4607046d6e89
    "@ricmoo\0"                    // 0x00030 key: 7fbbe37c2c3a93b8d3364177
    "ENS Registry\0"               // 0x00038 key: 883b5ee2810655d4e8425b84
      // Dup: "USDC Token\0"          0x0000d key: 919d1e353d21172b34877a22
    "OP Token\0"                   // 0x00045 key: 94657521289b8402f441eb22
    "ENS Token\0"                  // 0x0004e key: aa328fb24ab020508546cf0e
      // Dup: "Testnet USDC\0"        0x00000 key: b1a7f7b7cc4aabe211c7be56
      // Dup: "@ricmoo\0"             0x00030 key: b5dcd720ed7238e4bf152f7b
      // Dup: "USDC Token\0"          0x0000d key: d0cffc40c1070187b6e6c296
    "Firefly Faucet\0"             // 0x00058 key: f44e9e31a120aaf4dd1f037d
      // Dup: "Testnet USDC\0"        0x00000 key: f482db1c736d35de091d442c
      // Dup: "USDC Token\0"          0x0000d key: fb552a13f8a3ef84dbe4d883
;

// Number of entries in indices
const size_t _ffx_db_contractsCount = 72;

// Width (in words) of each key
const size_t _ffx_db_contractsWidth = 3;

// Each key, followed by its index into Strings
const uint32_t _ffx_db_contractsIndex[] = {
    0x20347798, 0xb9604e13, 0x29aca150, 0x00000000, 0x560e7d9f, 0xd2c02793,
    0xb9e80843, 0x00000000, 0x63a60b1c, 0x03d7c268, 0x8cbc7adb, 0x0000000d,
    0x6c596019, 0x5073111b, 0xbebc2173, 0x00000018, 0x6e3c8123, 0x31859538,
    0x60f543eb, 0x00000022, 0x71caeb43, 0x1420c82a, 0xaee1c031, 0x0000000d,
    0x7324a1b1, 0x776b4607, 0x046d6e89, 0x00000000, 0x7fbbe37c, 0x2c3a93b8,
    0xd3364177, 0x00000030, 0x883b5ee2, 0x810655d4, 0xe8425b84, 0x00000038,
    0x919d1e35, 0x3d21172b, 0x34877a22, 0x0000000d, 0x94657521, 0x289b8402,
    0xf441eb22, 0x00000045, 0xaa328fb2, 0x4ab02050, 0x8546cf0e, 0x0000004e,
    0xb1a7f7b7, 0xcc4aabe2, 0x11c7be56, 0x00000000, 0xb5dcd720, 0xed7238e4,
    0xbf152f7b, 0x00000030, 0xd0cffc40, 0xc1070187, 0xb6e6c296, 0x0000000d,
    0xf44e9e31, 0xa120aaf4, 0xdd1f037d, 0x00000058, 0xf482db1c, 0x736d35de,
    0x091d442c, 0x00000000, 0xfb552a13, 0xf8a3ef84, 0xdbe4d883, 0x0000000d,
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DB_CONTRACTS_H__ */