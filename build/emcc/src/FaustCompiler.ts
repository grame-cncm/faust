/************************************************************************
 ************************************************************************
	FAUST compiler
	Copyright (C) 2003-2020 GRAME, Centre National de Creation Musicale
	---------------------------------------------------------------------
	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

///<reference path="libfaust.d.ts"/>
///<reference path="FaustCompiler.d.ts"/>

namespace Faust {

	class InstanceAPIImpl implements Faust.InstanceAPI {
		private readonly fExports: Faust.InstanceAPI;

		constructor(exports: Faust.InstanceAPI) { this.fExports = exports; }

		compute(dsp: Faust.DSP, count: number, input: Faust.AudioBuffer, output: Faust.AudioBuffer) { this.fExports.compute(dsp, count, input, output); }
		getNumInputs(dsp: Faust.DSP) { return this.fExports.getNumInputs(dsp); }
		getNumOutputs(dsp: Faust.DSP) { return this.fExports.getNumOutputs(dsp); }
		getParamValue(dsp: Faust.DSP, index: number) { return this.fExports.getParamValue(dsp, index); }
		getSampleRate(dsp: Faust.DSP) { return this.fExports.getSampleRate(dsp); }
		init(dsp: Faust.DSP, sampleRate: number) { this.fExports.init(dsp, sampleRate); }
		instanceClear(dsp: Faust.DSP) { this.fExports.instanceClear(dsp); }
		instanceConstants(dsp: Faust.DSP, sampleRate: number) { this.fExports.instanceConstants(dsp, sampleRate); }
		instanceInit(dsp: Faust.DSP, sampleRate: number) { this.fExports.instanceInit(dsp, sampleRate); }
		instanceResetUserInterface(dsp: Faust.DSP) { this.fExports.instanceResetUserInterface(dsp); }
		setParamValue(dsp: Faust.DSP, index: number, value: number) { this.fExports.setParamValue(dsp, index, value); }
	}

	export class Compiler {
		private fFaustEngine: LibFaust;

		private intVec2intArray(vec: IntVector): Uint8Array {
			const size = vec.size();
			const ui8Code = new Uint8Array(size);
			for (let i = 0; i < size; i++) {
				ui8Code[i] = vec.get(i);
			}
			return ui8Code;
		}

		// private heap2Str(buf: Uint8Array) {
		// 	let str = "";
		// 	let i = 0;
		// 	while (buf[i] !== 0) {
		// 		str += String.fromCharCode(buf[i++]);
		// 	}
		// 	return str;
		// }

		private createWasmImport = (memory?: WebAssembly.Memory) => ({
			env: {
				//memory: new WebAssembly.Memory({ initial: 100 }),
				memory: memory, memoryBase: 0, tableBase: 0,
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
				table: new WebAssembly.Table({ initial: 0, element: "anyfunc" })
			}
		});

		private createWasmMemory = (voicesIn: number, dspMeta: TFaustJSON, effectMeta: TFaustJSON, bufferSize: number) => {
			// Hack : at least 4 voices (to avoid weird WASM memory bug?)
			const voices = Math.max(4, voicesIn);
			// Memory allocator
			const ptrSize = 4;
			const sampleSize = 4;
			const pow2limit = (x: number) => {
				let n = 65536; // Minimum = 64 kB
				while (n < x) { n *= 2; }
				return n;
			};
			const effectSize = effectMeta ? effectMeta.size : 0;

			// Memory for voices + effect + audio buffers. TODO: handle effect memory separately
			let memorySize = pow2limit(
				effectSize
				+ dspMeta.size * voices
				+ (dspMeta.inputs + dspMeta.outputs * 2)
				* (ptrSize + bufferSize * sampleSize)
			) / 65536;
			memorySize = Math.max(2, memorySize); // As least 2
			return new WebAssembly.Memory({ initial: memorySize, maximum: memorySize });
		};

		constructor(engine?: LibFaust) {
			this.fFaustEngine = engine;
		}

		version(): string { return this.fFaustEngine.version(); }

		createDSPFactory(name_app: string, dsp_content: string, args: string, poly: boolean): Promise<Faust.Factory> {
			return new Promise((resolve, reject) => {
				try {
					const factory = this.fFaustEngine.createDSPFactory(name_app, dsp_content, args, !poly);
					const wasm = this.fFaustEngine.getWasmModule(factory);
					console.log(wasm.json);
					WebAssembly.compile(this.intVec2intArray(wasm.data)).then(module => {
						this.fFaustEngine.freeWasmModule(factory);
						resolve({ module: module, json: wasm.json, poly: poly });
					});
				} catch {
					const error = this.fFaustEngine.getErrorAfterException();
					console.log("=> exception raised while running createDSPFactory: " + error);
					this.fFaustEngine.cleanupAfterException();
					reject(error);
				}
			});
		}

		createDSPInstance(factory: Factory): Instance {
			const instance = new WebAssembly.Instance(factory.module, this.createWasmImport());
			const functions: any = instance.exports;
			const api = new InstanceAPIImpl(<InstanceAPI>functions);
			const memory: any = instance.exports.memory;
			return { memory: memory, api: api, json: factory.json }
		}

		expandDSP(name_app: string, dsp_content: string, args: string) {
			try {
				const out = this.fFaustEngine.expandDSP(name_app, dsp_content, args);
				return { dsp: out.dsp, shakey: out.shakey, error: "" };
			} catch {
				const error = this.fFaustEngine.getErrorAfterException();
				console.log("=> exception raised while running expandDSP: " + error);
				this.fFaustEngine.cleanupAfterException();
				return { dsp: "", shakey: "", error: error };
			}
		}

		generateAuxFiles(name_app: string, dsp_content: string, args: string) {
			try {
				const done = this.fFaustEngine.generateAuxFiles(name_app, dsp_content, args);
				return { success: done, error: "" };
			} catch {
				const error = this.fFaustEngine.getErrorAfterException();
				console.log("=> exception raised while running generateAuxFiles: " + error);
				this.fFaustEngine.cleanupAfterException();
				return { success: false, error: error };
			}
		}

		// deleteAllDSPFactories(): void;
	}

}
