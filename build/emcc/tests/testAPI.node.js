
"use strict";

const lib = require ("./libfaust");
const run = require ("./testAPI");

var engine = new lib().initialize ("../npm/dist/libfaust-wasm").then (doit);

function log(str) 		{ console.log (str); }
function svg(str, name) { 
	fs.writeFileSync (name + ".svg", str, "utf8" );
	log ("  SVG flushed to " + name);
}

function doit (engine) {
 	run ( engine, log, "process = +;" );
}
