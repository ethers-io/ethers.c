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
    "@ricmoo\0"                    // 0x00000 key: d944321005d50e40dde62aec
    "DAI Token\0"                  // 0x00008 key: 7be3042b4dddc67b02103cb8
    "Testnet USDC\0"               // 0x00012 key: f0f8c938189da0d5d67e9688
    "USDC Token\0"                 // 0x0001f key: 96f24f45430cb7919ef88750
      // Dup: "USDC Token\0"          0x0001f key: 3f3c9645db8a50e8ae910ebd
      // Dup: "USDC Token\0"          0x0001f key: df858e466058203597bde3b3
      // Dup: "Testnet USDC\0"        0x00012 key: fb77205a640faddfdde33258
      // Dup: "Testnet USDC\0"        0x00012 key: 419f6d618f9e99e465e72de9
    "ENS Registry\0"               // 0x0002a key: e89a6f6509af1263c5e8af89
      // Dup: "Testnet USDC\0"        0x00012 key: d6c5607583ea5ecdc52f6c5d
      // Dup: "@ricmoo\0"             0x00000 key: e578127a55769a52b36886fd
    "OP Token\0"                   // 0x00037 key: ec57cdb60e9620a9bd5a58d6
      // Dup: "USDC Token\0"          0x0001f key: 96a5c2c36be417a7c59d8be7
    "Firefly Faucet\0"             // 0x00040 key: b9f823cc063f4c56e6cc032c
    "ENS Registrar\0"              // 0x0004f key: a74937cd51c1456557c5dce9
      // Dup: "USDC Token\0"          0x0001f key: b345e7e5167fce13eb894d1a
    "ENS Token\0"                  // 0x0005d key: b370abed77b46ca7f1d905e7
      // Dup: "Testnet USDC\0"        0x00012 key: 1528bff307c7dbf10c3a3ccf
;

// Number of entries in indices
const size_t _ffx_db_contractsCount = 18;

// Width (in words) of each key
const size_t _ffx_db_contractsWidth = 3;

// Each key, followed by its index into Strings
const uint32_t _ffx_db_contractsIndex[] = {
    0x103244d9, 0x400ed505, 0xec2ae6dd, 0x00000000, 0x2b04e37b, 0x7bc6dd4d,
    0xb83c1002, 0x00000008, 0x38c9f8f0, 0xd5a09d18, 0x88967ed6, 0x00000012,
    0x454ff296, 0x91b70c43, 0x5087f89e, 0x0000001f, 0x45963c3f, 0xe8508adb,
    0xbd0e91ae, 0x0000001f, 0x468e85df, 0x35205860, 0xb3e3bd97, 0x0000001f,
    0x5a2077fb, 0xdfad0f64, 0x5832e3dd, 0x00000012, 0x616d9f41, 0xe4999e8f,
    0xe92de765, 0x00000012, 0x656f9ae8, 0x6312af09, 0x89afe8c5, 0x0000002a,
    0x7560c5d6, 0xcd5eea83, 0x5d6c2fc5, 0x00000012, 0x7a1278e5, 0x529a7655,
    0xfd8668b3, 0x00000000, 0xb6cd57ec, 0xa920960e, 0xd6585abd, 0x00000037,
    0xc3c2a596, 0xa717e46b, 0xe78b9dc5, 0x0000001f, 0xcc23f8b9, 0x564c3f06,
    0x2c03cce6, 0x00000040, 0xcd3749a7, 0x6545c151, 0xe9dcc557, 0x0000004f,
    0xe5e745b3, 0x13ce7f16, 0x1a4d89eb, 0x0000001f, 0xedab70b3, 0xa76cb477,
    0xe705d9f1, 0x0000005d, 0xf3bf2815, 0xf1dbc707, 0xcf3c3a0c, 0x00000012,
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DB_CONTRACTS_H__ */
