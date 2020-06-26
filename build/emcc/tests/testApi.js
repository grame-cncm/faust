

//----------------------------------------------------------------------------
// Misc. functions
//----------------------------------------------------------------------------
function factory (lib, log, code )
{
	let faust = lib.faust;
	log( "\nFactory :");
	let fact = faust.createDSPFactory("test", code, "", false);
	log ("  createDSPFactory      " + fact.module  + " : " + fact.error);

	let exp = faust.expandDSP("test", code, "");
	log ("  expandDSP             " + exp.dsp + " sha: " + exp.shakey + " " + exp.error);

	try {
	let aux = faust.generateAuxFiles("test", code, "-lang wast/wasm");
	log ("  generateAuxFiles      " + aux.success + " " + aux.error);
	}
	catch {
		log ("=> exception raised while running generateAuxFiles: " + faust.getErrorAfterException() );
		faust.cleanupAfterException();
	}

	try {
	faust.deleteAllDSPFactories();
	log ("  deleteAllDSPFactories done"); 
	}
	catch {
		log ("=> exception raised while running deleteAllDSPFactories: " + faust.getErrorAfterException() );
		faust.cleanupAfterException();
	}
}

function modules (lib, log, code )
{
	let faust = lib.faust;
	log( "\nModules :");
	let fact = faust.createDSPFactory("test", code, "", false);

	let wasm = faust.getWasmModule (fact.module);
	log ("  getWasmModule      done");
	let size = faust.getWasmModuleSize (fact.module);
	log ("  getWasmModuleSize  " + size);
	let helpers = faust.getWasmHelpers (fact.module);
	log ("  getWasmHelpers     " + helpers.length);
	faust.freeWasmModule (fact.module);
	log ("  freeWasmModule     done");
}

function run (engine, log, code) {
	log ( "libfaust version: " + lib.faust.version());
	factory (lib, log, code);
	modules (lib, log, code);
	log ("\nEnd of API tests");
}

if ((typeof process !== 'undefined') && (process.release.name === 'node')) {
	module.exports = run;
}
