var options = "-I libraries/";

//----------------------------------------------------------------------------
// Misc. functions
//----------------------------------------------------------------------------
function factory (faust, log, code )
{
	log( "\nFactory :");
	try {
		let fact = faust.createDSPFactory("test", code, options, false);
		log ("  createDSPFactory      " + fact.module  + " : " + fact.error);
	}
	catch {
		log ("=> exception raised while running createDSPFactory: " + faust.getErrorAfterException() );
		faust.cleanupAfterException();	
	}

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

	try {
	faust.deleteAllDSPFactories();
	log ("  deleteAllDSPFactories done"); 
	}
	catch {
		log ("=> exception raised while running deleteAllDSPFactories: " + faust.getErrorAfterException() );
		faust.cleanupAfterException();
	}
}

function intVec2intArray (vec) {
	const size = vec.size();
	const ui8Code = new Uint8Array(size);
	for (let i = 0; i < size; i++) {
		ui8Code[i] = vec.get(i);
	}
	return ui8Code;
}

const createWasmImport = () => ({
    env: {
        memory: new WebAssembly.Memory({ initial: 100 }),
        _abs: Math.abs,
        // Float version
        _acosf: Math.acos, _asinf: Math.asin, _atanf: Math.atan, _atan2f: Math.atan2,
        _ceilf: Math.ceil, _cosf: Math.cos, _expf: Math.exp, _floorf: Math.floor,
        _fmodf: (x, y) => x % y,
        _logf: Math.log, _log10f: Math.log10, _max_f: Math.max, _min_f: Math.min,
        _remainderf: (x, y) => x - Math.round(x / y) * y,
        _powf: Math.pow, _roundf: Math.fround, _sinf: Math.sin, _sqrtf: Math.sqrt, _tanf: Math.tan,
        _acoshf: Math.acosh, _asinhf: Math.asinh, _atanhf: Math.atanh,
        _coshf: Math.cosh, _sinhf: Math.sinh, _tanhf: Math.tanh,
        // Double version
        _acos: Math.acos, _asin: Math.asin, _atan: Math.atan, _atan2: Math.atan2,
        _ceil: Math.ceil, _cos: Math.cos, _exp: Math.exp, _floor: Math.floor,
        _fmod: (x, y) => x % y,
        _log: Math.log, _log10: Math.log10, _max_: Math.max, _min_: Math.min,
        _remainder: (x, y) => x - Math.round(x / y) * y,
        _pow: Math.pow, _round: Math.fround, _sin: Math.sin, _sqrt: Math.sqrt, _tan: Math.tan,
        _acosh: Math.acosh, _asinh: Math.asinh, _atanh: Math.atanh,
        _cosh: Math.cosh, _sinh: Math.sinh, _tanh: Math.tanh,
    //     table: new WebAssembly.Table({ initial: 0, element: "anyfunc" })
    }
});

function modules (faust, log, code )
{
	log( "\nModules :");
	let fact = faust.createDSPFactory("test", code, options, false);

	let wasm = faust.getWasmModule (fact.module);
	log ("  getWasmModule      " + wasm.data.size() + " " + wasm.helper.length);
	eval (wasm.helper);
	let json = JSON.parse (getJSONmydsp());
	log ("  UI      " + json.ui);

	WebAssembly.compile( intVec2intArray(wasm.data)).then ( module => { 
		log ("  module      " + module);
		var exports = WebAssembly.Module.exports(module);
		log ("  exports      " + exports.length);
		for (i=0; i<exports.length; i++) {
			log ("     - " + exports[i].name);
		}

		// var importObject = { imports: { print: arg => console.log(arg) } }    
		WebAssembly.instantiate ( module, createWasmImport() ).then ( instance => { 
			log ( "getNumInputs: " + instance.exports.getNumInputs());
			log ( "getNumInputs: " + instance.exports.getNumOutputs());
		});
		faust.freeWasmModule (fact.module);
		log ("  freeWasmModule     done");
	});
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
