
"use strict";

const fs = require ("fs");
const path = require('path');
const process = require("process");
const FaustModule  = require ("../libfaust-wasm");
const lib = require ("../FaustNode");
const { exit } = require("process");

function usage (err) {
    console.log(`faust2svg.js <file.dsp> <outputDir>
    Generates SVG Diagrams of a given Faust DSP.
  Options are:
    -version : print faust version and exit
    -help | -h : print this help and exit`);
    process.exit(err);
}

const argv = process.argv.slice(2);
const showVers = argv.indexOf("-version") !== -1;
if (argv[0] === "-help" || argv[0] === "-h") usage(0);
if (argv.length < 1) usage(1);

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

function write (name, content)
{
    let path = outputDir+'/'+name;
    fs.writeFileSync (outputDir+'/'+name, content);
}

function doit(module, name, dsp , outdir, faustargs) {
    let faust = lib.createLibFaust(module);
    let svg = lib.createSVGDiagrams(lib.createCompiler(faust), name, dsp, "-xlink " + faustargs);
    if (svg.success()) {
        svg.getSVGs(module, write);
    }
    else  {
        console.log (svg.error());
        exit(1);
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
        doit (module, path.basename(inputFile, '.dsp'), getdsp(inputFile), outputDir, argvFaust);
    }
});



