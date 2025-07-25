import { concat, keccak256, toBeArray } from "./lib/ethers.js";

import { readJSON, writeDoth } from "./lib/utils.mjs";

const networks = readJSON("db/db-networks.json").reduce((a, v) => {
   if (v.name) { a.set(v.name.toLowerCase(), BigInt(v.chainId)); }
   return a;
}, new Map());

const NetworkMap = {
  "op": "optimism"
};

function getNetwork(value) {
    if (value.match(/^[0-9]+$/)) { return BigInt(value); }
    if (NetworkMap[value]) { value = NetworkMap[value]; }

    const chainId = networks.get(value.toLowerCase().replace(/-/g, " "));
    if (chainId != null) { return chainId; }
    throw new Error(`unknown network: ${ value }`);
}


const data = readJSON("db/db-contracts.json");

const records = [ ];
for (const { name, address } of data) {
    if (!name) { continue; }
    for (const entry of address) {
      const comps = entry.split(":");
      if (comps.length !== 2) { throw new Error(`bad entry: ${ entry }`); }
      const chainId = toBeArray(getNetwork(comps[0]), 32);
      const addr = comps[1];
      const key = keccak256(concat([ addr, chainId ])).substring(2, 26);
      records.push({ key, values: [ name ] });
    }
}

writeDoth("src/db-contracts.h", "contracts", 3, records);
