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


Contracts Database
------------------

The Contracts database stores hashed (address, network) tuples mapped
to the contract name.

```
Imports:       db/contracts.json
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
Imports:       db/networks.json
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


