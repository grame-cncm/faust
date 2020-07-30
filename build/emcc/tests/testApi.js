

//----------------------------------------------------------------------------
// Misc. functions
//----------------------------------------------------------------------------
function factory (faust, log, code )
{
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

function modules (faust, log, code )
{
	log( "\nModules :");
	let fact = faust.createDSPFactory("test", code, "", false);

	let wasm = faust.getWasmModule (fact.module);
	log ("  getWasmModule      " + wasm.data.size() + " " + wasm.helper.length);

	faust.freeWasmModule (fact.module);
	log ("  freeWasmModule     done");
}

function run (faust, log, code) {
	log ( "libfaust version: " + faust.version());
	factory (faust, log, code);
	modules (faust, log, code);
	log ("\nEnd of API tests");
}

if ((typeof process !== 'undefined') && (process.release.name === 'node')) {
	module.exports = run;
}
