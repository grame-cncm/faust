# Faust Web Audio Library

The Faust Web Audio library provides all the services of the Faust compiler to the Web, as well as high level functions to get an Audio Node from Faust dsp code.


## Building

For convenience, a Makefile is present in this folder. 
Available targets are:

- **all** (default): build the Faust wasm library and the javascript library. 
- **cmake** : re-run cmake (required if you never compiled the bindings).
- **dist** : copy the library typescript interface to the `npm/dist` folder.


## Testing

To test, launch a local server, then open the page: `tests/testCompiler.html`

Note that you can disable CORS security on Firefox and test without server: go to the `about:config` page and set  `security.fileuri.strict_origin_policy` to false. Then simply drop the `tests/testCompiler.html` to Firefox.

## Files

The typescript interface to the faust library is described in `npm/dist`.  
See [npm/README.md](npm/README.md) for more details.
