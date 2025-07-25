
import { readJSON, writeDoth } from "./lib/utils.mjs"

const data = readJSON("db/db-networks.json");


const records = [ ];
for (const { name, token, chainId } of data) {
    if (!name) { continue; }
    if (chainId > 0x7fffffff) {
        console.log("Skipping", { name, token, chainId });
        continue;
    }
    records.push({ key: chainId, values: [ name, token ] });
}

writeDoth("src/db-networks.h", "networks", 1, records);
