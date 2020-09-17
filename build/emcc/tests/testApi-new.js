var options = "-I libraries/";

//----------------------------------------------------------------------------
// Misc. functions
//----------------------------------------------------------------------------
function misc (faust, log, code )
{
	let exp = faust.expandDSP("test", code, options);
	log ("  expandDSP             " + exp.dsp + " sha: " + exp.shakey + " " + exp.error);

	try {
		let aux = faust.generateAuxFiles("test", code, options + " -lang wast/wasm");
		log ("  generateAuxFiles      " + aux.success + " " + aux.error);
	}
	catch {
		log ("=> exception raised while running generateAuxFiles: " + faust.getErrorAfterException() );
		faust.cleanupAfterException();
	}
}

function run (engine, log, code) {
	let faust = new FaustCompiler (engine);
	log ( "libfaust version: " + faust.version());
	misc (faust, log, code);
	log ( "createDSPFactory: ");
	faust.createDSPFactory  ("test", code, options, false).then (faustmodule => {
		log ( "createDSPInstance: ");
		faust.createDSPInstance (faustmodule).then (instance => {
			log ( "  getNumInputs : " + instance.api.getNumInputs());
			log ( "  getNumOutputs: " + instance.api.getNumOutputs());
			log ("\nEnd of API tests");
		});
	});
}

if ((typeof process !== 'undefined') && (process.release.name === 'node')) {
	module.exports = run;
}
