var options = "-I libraries/";
var errCode = "foo";

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

async function createDsp (faust, log, code) {
	log ("\nCreating DSP instance:");
	log ( "createDSPFactory: ");
	let faustmodule = await faust.createDSPFactory  ("test", code, options, false);
	if (typeof faustmodule == "string") {
		log ("createDSPFactory error: " + faustmodule);
		return;
	}

	log ( "faustmodule poly: " + faustmodule.poly);
	log ( "createDSPInstance: ");
	let instance = await faust.createDSPInstance (faustmodule);
	log ( "  getNumInputs : " + instance.api.getNumInputs());
	log ( "  getNumOutputs: " + instance.api.getNumOutputs());
}

async function run (engine, log, code) {
	let faust = new FaustCompiler (engine);
	log ( "libfaust version: " + faust.version());
	misc (faust, log, code);
	await createDsp (faust, log, code); //.then ( () => { log ("\nEnd of API tests"); } );
	await createDsp (faust, log, errCode).catch (e => {log(e); }); 
	log ("\nEnd of API tests");
	//.then ( () => { log ("\nEnd of API tests"); } );
	// log ( "createDSPFactory: ");
	// faust.createDSPFactory  ("test", code, options, false).then (faustmodule => {
	// 	log ( "createDSPInstance: ");
	// 	faust.createDSPInstance (faustmodule).then (instance => {
	// 		log ( "  getNumInputs : " + instance.api.getNumInputs());
	// 		log ( "  getNumOutputs: " + instance.api.getNumOutputs());
	// 		log ("\nEnd of API tests");
	// 	});
	// });
}

if ((typeof process !== 'undefined') && (process.release.name === 'node')) {
	module.exports = run;
}
