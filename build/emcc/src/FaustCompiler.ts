
///<reference path="libfaust.d.ts"/>
///<reference path="FaustCompiler.d.ts"/>


class FaustInstanceAPIImpl implements FaustInstanceAPI {
	private readonly fExports: FaustInstanceAPI;

	constructor (exports: FaustInstanceAPI) { this.fExports = exports; }

	compute(count: number, input: number, output: number) { this.fExports.compute(count, input, output); }
	getNumInputs() { return this.fExports.getNumInputs(); }
	getNumOutputs() { return this.fExports.getNumOutputs(); }
	getParamValue(index: number) { return this.fExports.getParamValue(index); }
	getSampleRate() { return this.fExports.getSampleRate(); }
	init(sampleRate: number) { this.fExports.init(sampleRate); }
	instanceClear() { this.fExports.instanceClear(); }
	instanceConstants(sampleRate: number) { this.fExports.instanceConstants(sampleRate); }
	instanceInit(sampleRate: number) { this.fExports.instanceInit(sampleRate); }
	instanceResetUserInterface() { this.fExports.instanceResetUserInterface(); }
	setParamValue(index: number, value: number) { this.fExports.setParamValue(index, value); }
}


class FaustCompiler {
	private fFaustEngine: LibFaust;

	private intVec2intArray(vec: IntVector) : Uint8Array {
		const size = vec.size();
		const ui8Code = new Uint8Array(size);
		for (let i = 0; i < size; i++) {
			ui8Code[i] = vec.get(i);
		}
		return ui8Code;
	}

	private createWasmImport = () => ({
		env: {
			memory: new WebAssembly.Memory({ initial: 100 }),
			// Integer version
			_abs: Math.abs,
			// Float version
			_acosf: Math.acos, _asinf: Math.asin, _atanf: Math.atan, _atan2f: Math.atan2,
			_ceilf: Math.ceil, _cosf: Math.cos, _expf: Math.exp, _floorf: Math.floor,
			_fmodf: (x: number, y: number) => x % y,
			_logf: Math.log, _log10f: Math.log10, _max_f: Math.max, _min_f: Math.min,
			_remainderf: (x: number, y: number) => x - Math.round(x / y) * y,
			_powf: Math.pow, _roundf: Math.fround, _sinf: Math.sin, _sqrtf: Math.sqrt, _tanf: Math.tan,
			_acoshf: Math.acosh, _asinhf: Math.asinh, _atanhf: Math.atanh,
			_coshf: Math.cosh, _sinhf: Math.sinh, _tanhf: Math.tanh,
			// Double version
			_acos: Math.acos, _asin: Math.asin, _atan: Math.atan, _atan2: Math.atan2,
			_ceil: Math.ceil, _cos: Math.cos, _exp: Math.exp, _floor: Math.floor,
			_fmod: (x: number, y: number) => x % y,
			_log: Math.log, _log10: Math.log10, _max_: Math.max, _min_: Math.min,
			_remainder: (x: number, y: number) => x - Math.round(x / y) * y,
			_pow: Math.pow, _round: Math.fround, _sin: Math.sin, _sqrt: Math.sqrt, _tan: Math.tan,
			_acosh: Math.acosh, _asinh: Math.asinh, _atanh: Math.atanh,
			_cosh: Math.cosh, _sinh: Math.sinh, _tanh: Math.tanh,
		//     table: new WebAssembly.Table({ initial: 0, element: "anyfunc" })
		}
	});


	constructor(engine: LibFaust) {
		this.fFaustEngine = engine;
	}

	version() : string { return this.fFaustEngine.version(); }

	createDSPFactory(name_app: string, dsp_content: string, args: string, poly: boolean) : Promise<FaustFactory> {
		let fact = this.fFaustEngine.createDSPFactory(name_app, dsp_content, args, poly ? false : true);
		let wasm = this.fFaustEngine.getWasmModule(fact.module);
		return WebAssembly.compile( this.intVec2intArray(wasm.data)).then ( module => {
			this.fFaustEngine.freeWasmModule(fact.module);
			return { module: module, poly: poly};
		}
		);
	}

	createDSPInstance(module: FaustFactory) : Promise<FaustInstance> {
		return WebAssembly.instantiate(module.module, this.createWasmImport() ).then( instance => {
			let tmp: any = instance.exports;
			let moduleapi = new FaustInstanceAPIImpl(<FaustInstanceAPI>tmp);
			return { instance: instance, api: moduleapi }
		});
	}

	expandDSP (name: string, dsp: string, args: string)       { return this.fFaustEngine.expandDSP(name, dsp, args); }
	generateAuxFiles(name: string, dsp: string, args: string) { return this.fFaustEngine.generateAuxFiles(name, dsp, args); }

//	deleteAllDSPFactories(): void;
}
