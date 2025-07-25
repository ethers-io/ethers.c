import { readFile, writeFile } from "./lib/utils.mjs";


const words = readFile("db/db-lang-en.txt").trim().split("\n");
if (words.length !== 2048) { throw new Error("bad list!"); }


const lines = [ ];
lines.push("#ifndef __BIP39_EN_H__");
lines.push("#define __BIP39_EN_H__");
lines.push("");
lines.push("#ifdef __cplusplus");
lines.push('extern "C" {');
lines.push("#endif /* __cplusplus */");
lines.push("");

lines.push("const char* wordlist_en = ");
for (let i = 0; i < words.length; i++) {
    lines.push(`    "${ words[i] }\\0"`);
}
lines.push("    ;");

lines.push("");
lines.push("#ifdef __cplusplus");
lines.push("}");
lines.push("#endif /* __cplusplus */");
lines.push("");
lines.push("#endif /* __BIP39_EN_H__ */");


writeFile("src/bip39-en.h", lines.join("\n"));
