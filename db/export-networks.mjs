import { readFileSync, writeFileSync } from "node:fs";

import { doth, resolve } from "./utils.mjs"

const data = JSON.parse(readFileSync(resolve("db/networks.json")).toString());


const records = [ ];
for (const { name, token, chainId } of data) {
    if (!name) { continue; }
    if (chainId > 0x7fffffff) {
        console.log("Skipping", { name, token, chainId });
        continue;
    }
    records.push({ key: chainId, values: [ name, token ] });
}

const filename = resolve("src/db-networks.h");
console.log(`Writing: ${ filename }`);
writeFileSync(filename, doth("networks", 1, records));
