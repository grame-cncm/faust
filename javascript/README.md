# Faust Web Audio Library

The Faust Web Audio library provides all the services of the Faust compiler to the Web, as well as high level functions to get an Audio Node from Faust dsp code.


## Install dependencies

~~~~~~~~
npm install
~~~~~~~~


## Building

For convenience, a Makefile is present in this folder. Simply type 

~~~~~~~~
make
~~~~~~~~
or
~~~~~~~~
npm run make
~~~~~~~~

More information on the build process : 
~~~~~~~~
make help
~~~~~~~~


## Testing

To test, launch a local server, then open the page: `tests/testCompiler.html`

Note that you can disable CORS security on Firefox and test without server: go to the `about:config` page and set  `security.fileuri.strict_origin_policy` to false. Then simply drop the `tests/testCompiler.html` to Firefox.

Note also that you need to copy `npm/libfaust-wasm.data` to the `tests` folder due to a yet unresolved issue with .data file loading when not located where the referring web page is.

## Files

The typescript interface to the Faust library is described in `npm`.  
See [npm/README.md](npm/README.md) for more details.
