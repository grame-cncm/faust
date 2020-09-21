var options = "-I libraries/";
var errCode = "foo";

//----------------------------------------------------------------------------
// Misc. functions
//----------------------------------------------------------------------------
function misc (faust, log, code )
{
	let exp = faust.expandDSP("test", code, options);
	let  msg = exp.error ? exp.error : exp.dsp + " sha " + exp.shakey;
	log ("  expandDSP             " + msg);

	let aux = faust.generateAuxFiles("test", code, options + " -lang wast/wasm");
	msg = aux.success ? "done" : aux.error;
	log ("  generateAuxFiles      " + msg);
}

async function createDsp (faust, log, code) {
	log ( "createDSPFactory: ");
	let faustmodule = await faust.createDSPFactory ("test", code, options, false);

	log ( "faustmodule poly: " + faustmodule.poly);
	log ( "createDSPInstance: ");
	let instance = await faust.createDSPInstance (faustmodule);
	log ( "  getNumInputs : " + instance.api.getNumInputs());
	log ( "  getNumOutputs: " + instance.api.getNumOutputs());
}

async function run (engine, log, code) {
	let faust = new Faust.Compiler (engine);
	log ( "libfaust version: " + faust.version());
	log ( "\n-----------------\nMisc tests" + faust.version());
	misc (faust, log, code);
	log ( "\n-----------------\nMisc tests with error code");
	misc (faust, log, errCode);
	log ("\n-----------------\nCreating DSP instance:");
	await createDsp (faust, log, code);
	log ("\n-----------------\nCreating DSP instance with error code:");
	await createDsp (faust, log, errCode).catch (e => {log(e); }); 
	log ("\nEnd of API tests");
}

if ((typeof process !== 'undefined') && (process.release.name === 'node')) {
	module.exports = run;
}
