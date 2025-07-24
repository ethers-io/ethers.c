import { dirname, resolve as _resolve } from 'node:path';
import { fileURLToPath } from 'node:url';

// Resolves a path relative to this file
export function resolve(...args) {
  return _resolve(dirname(fileURLToPath(import.meta.url)), '..', ...args);
}

function repeat(c, length) {
  if (c.length === 0) { throw new Error("bad string"); }
  while (c.length < length) { c += c; }
  return c.substring(0, length);
}

function padLeft(v, c, length) {
  v = String(v);
  return repeat(c, length - v.length) + v;
}

// records = [ { key: KEY, values: [ string0, ... ] } ]
export function doth(tag, width, records) {

  // Map<paddedHexKeys, Array<string>>
  const originalKeys = new Map();
  const map = new Map();
  for (const { key, values } of records) {
      let k = key;
      if (typeof(k) === "number" || typeof(k) === "bigint") {
          k = k.toString(16);
      }
      k = padLeft(k, "0", 4 * 2 * width);
      if (map.has(k)) { throw new Error(`duplicate entry: ${ key }`); }
      originalKeys.set(k, key);
      map.set(k, values);
  }
  console.log(map);

  const strings = [ ];
  let stringsIndex = 0;

  const indices = [ ];

  for (const key of Array.from(map.keys()).sort()) {
    for (let i = 0; i < key.length; i += 8) {
        indices.push(`0x${ key.substring(i, i + 8) }`);
    }
    indices.push(`0x${ padLeft(stringsIndex.toString(16), "0", 8) }`);

    const values = map.get(key);

    let value = values.map((v) => (v + "\\0")).join("");
    const padding = repeat(" ", 28 - value.length);
    const dbgOffset = `0x${ padLeft(stringsIndex.toString(16), "0", 5) }`;
    const dbgKey = originalKeys.get(key);
    strings.push(`"${ value }" ${ padding }// ${ dbgOffset } key: ${ dbgKey }`);

    // We added "\\0" to each value, but the "\\" does not count in offset
    stringsIndex += value.length - values.length;
  }

  const TAG = tag.toUpperCase();

  const lines = [ ];
  lines.push(`#ifndef __DB_${ TAG }_H__`);
  lines.push(`#define __DB_${ TAG }_H__`);
  lines.push(``);
  lines.push(`// This file is generated! Do NOT modify manually. See export-db-${ tag }.mjs.`);
  lines.push(``);
  lines.push(`#ifdef __cplusplus`);
  lines.push(`extern "C" {`);
  lines.push(`#endif /* __cplusplus */`);
  lines.push(``)
  lines.push(`#include <stddef.h>`);
  lines.push(`#include <stdint.h>`);
  lines.push(``)
  lines.push(`// Strings for each record`)
  lines.push(`const char _ffx_db_${ tag }Strings[] =`)
  for (const str of strings) {
      lines.push("    " + str);
  }
  lines.push(`;`)
  lines.push(``)
  lines.push(`// Number of entries in indices`)
  lines.push(`const size_t _ffx_db_${ tag }Count = ${ indices.length };`)
  lines.push(``)
  lines.push(`// Width (in words) of each key`)
  lines.push(`const size_t _ffx_db_${ tag }Width = ${ width };`)
  lines.push(``)
  lines.push(`// Each key, followed by its index into Strings`)
  lines.push(`const uint32_t _ffx_db_${ tag }Index[] = {`)
  while (indices.length) {
    const l = [ ];
    while (indices.length) {
      l.push(indices.shift() + ",");
      if (l.length > 5) { break; }
    }
    lines.push("    " + l.join(" "));
  }
  lines.push(`};`)
  lines.push(``)
  lines.push(`#ifdef __cplusplus`);
  lines.push(`}`);
  lines.push(`#endif /* __cplusplus */`);
  lines.push(``);
  lines.push(`#endif /* __DB_${ TAG }_H__ */`);

  return lines.join("\n");
}
