# Faust Wasm Library

## Building

For convenience, a Makefile is present in this folder. 
You should use it to be able to perform the tests located in the `tests`folder.
Available targets are:

- **all** (default): build the faust wasm library and copy the result to the `npm/dist` folder. Creates also a sym link for data in the `tests` folder.
- **cmake** : re-run cmake (required if you never compiled the new bindigs).

## Testing

To test, launch a local server, then open the page: `tests/testAPI.html`

Note that you can disable CORS security on Firefox and test without server: go to the `about:config` page and set  `security.fileuri.strict_origin_policy` to false. Then simply drop the `tests/testAPI.html` to Firefox.

## Files

The typescript interface to the faust library is described in `npm/dist/libfaust.d.ts`.  
Note that it is based on the new bindings. The names of the functions have been deliberately changed so as not to confuse the new bindings with the old ones. The function interface is also changed.
