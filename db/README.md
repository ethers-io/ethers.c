Databases
=========

These databases files are built into header files to provide a "trusted"
source for Ethereum (and ilk) data useful for user interfaces.


Modifying
---------

These files would get large if *just anyone* were allowed to commit updates
as there are many projects that wish to include their details in any place
they can get their marketting clws into.

For this reason, the included Databases are meant to be kept lean,
relevant and useful for a broad audience.

However, since each application may have its own requirements, scripts
are provided to simplify developers updating the database and generating
the corresponding header files used by the API.


BIP39 Wordlist
--------------

The BIP-39 English wordlist is the 2048 words used by most blockchains to
represent mnemonic phrases as a backup.

```
Imports:       db/db-lang-en.txt
Export Script: db/export-bip39-en.mjs
Generates:     src/bip39-en.h

API:
  // Returns the index of the word (or -1 if not present)
  int ffx_bip39_index(const char* const word);

  // Returns the word at index (or NULL if outside the range [0, 2047])
  const char* ffx_bip39_word(int index);```
```


Contracts Database
------------------

The Contracts database stores hashed (address, network) tuples mapped
to the contract name.

```
Imports:       db/db-contracts.json
Export Script: db/export-contracts.mjs
Generates:     src/db-contracts.h

API:
  // Returns the Contract Name for the %%addr%% on %%chainId%% (or NULL)
  // e.g. "DAI Token" or "Firefly Faucet"
  const char* ffx_db_getContractName(FfxBigInt *chainId, FfxDataResult *addr);
```


Network Database
----------------

The Network database stores network Chain ID mapped to (Network Name,
Network Token) tuples.

```
Imports:       db/db-networks.json
Export Script: db/export-networks.mjs
Generates:     src/db-networks.h

API:
  // Returns the network name for %%chainId%% (or NULL)
  // e.g. "mainnet" or "optimism"
  const char* ffx_db_getNetworkName(FfxBigInt *chainId);

  // Returns the network token for %%chainId%% (or NULL)
  // e.g. "ETH" or "sETH" (for Sepolia ETH)
  const char* ffx_db_getNetworkToken(FfxBigInt *chainId);
```


