
"use strict";

const fs = require ("fs");
const path = require('path');
const process = require("process");
const FaustModule  = require ("../libfaust-wasm");
const lib = require ("../FaustNode");

function usage (err) {
    console.log(`faust2wasm.js <file.dsp> <outputDir> [options] [faustargs]
  Generates WebAssembly and metadata JSON files of a given Faust DSP.
  Options are:
    -poly n : generates a polyphonic output
    -version : print faust version and exit
    -help | -h : print this help and exit
  faustargs are passed to the faust compiler.`);
    process.exit(err);
}

const argv = process.argv.slice(2);
if (argv[0] === "-help" || argv[0] === "-h") usage(0);
if (argv.length < 1) usage(1);

const poly = argv.indexOf("-poly") !== -1;
const showVers = argv.indexOf("-version") !== -1;
const [inputFile, outputDir, ...argvFaust] = argv;
if (!showVers && !outputDir) usage(0);

function getdsp (file) {
    try {
       return fs.readFileSync(file, 'utf8');
    } catch (err) {
        console.error("can't read file " + file + ":", err);
        process.exit(1);
    }
}

function write (factory, outname) {
    fs.writeFileSync (outname+'.json', factory.json);
    fs.writeFileSync (outname+'.wasm', factory.code, { encoding: null });
}

function doit(module, name, dsp , outdir, poly, faustargs) {
    let faust = lib.createLibFaust(module);
    let comp = lib.createCompiler(faust);
    if (poly) {
        comp.createPolyDSPFactory(name, dsp, faustargs.join(" ")).then (
            (factory) => { write( factory, outdir+'/'+name); } );
    }
    else {
        comp.createMonoDSPFactory(name, dsp, faustargs.join(" ")).then (
            (factory) => { write( factory, outdir+'/'+name); } );
    }
}

FaustModule().then ( (module) => { 
    if (showVers) {
        let faustwasm = new module.libFaustWasm();
        console.log ('Faust v.' + faustwasm.version());
    }
    else {
        if (!fs.existsSync(outputDir)) {
            fs.mkdirSync(outputDir);
        }
        doit (module, path.basename(inputFile, '.dsp'), getdsp(inputFile), outputDir, poly, argvFaust);
    }
});



