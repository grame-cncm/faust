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

    export class InstanceAPIImpl implements Faust.InstanceAPI {
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
        private fFaustEngine: Faust.LibFaust;

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

        private createWasmMemory = (voicesIn: number, dspJSON: TFaustJSON, effectJSON: TFaustJSON, bufferSize: number) => {
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
            const effectSize = effectJSON ? effectJSON.size : 0;
            // Memory for voices + effect + audio buffers.
            let memorySize = pow2limit(
                effectSize
                + dspJSON.size * voices
                + (dspJSON.inputs + dspJSON.outputs * 2)
                * (ptrSize + bufferSize * sampleSize)
            ) / 65536;
            memorySize = Math.max(2, memorySize); // As least 2
            return new WebAssembly.Memory({ initial: memorySize, maximum: memorySize });
        };

        constructor(engine?: Faust.LibFaust) {
            this.fFaustEngine = engine;
        }

        version(): string { return this.fFaustEngine.version(); }

        createDSPFactory(name_app: string, dsp_content: string, args: string, poly: boolean): Promise<Faust.Factory> {
            return new Promise((resolve, reject) => {
                try {
                    const factory = this.fFaustEngine.createDSPFactory(name_app, dsp_content, args, !poly);
                    const wasm = this.fFaustEngine.getWasmModule(factory);
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

        // TODO
        // loadDSPFactory(wasm_path: string, json_path: string, poly: boolean): Promise<Faust.Factory> {
        // 	return new Promise((resolve, reject) => {
        // 		try {
        // 			const wasm_file = fetch(wasm_path);
        // 			const wasm_buffer = wasm_file.arrayBuffer();
        // 			const module = WebAssembly.compile(wasm_buffer);
        // 			const json_file = fetch(json_path);
        // 			const json = json_file.text();
        // 			resolve({ module: module, json: json, poly: poly });
        // 		} catch (e) {
        // 			console.log("=> exception raised while running loadDSPFactory: " + e);
        // 			reject(e);
        // 		}
        // 	});
        // } 

        createDSPInstance(factory: Factory): Instance {
            const instance = new WebAssembly.Instance(factory.module, this.createWasmImport());
            const functions: any = instance.exports;
            const api = new InstanceAPIImpl(<InstanceAPI>functions);
            const memory: any = instance.exports.memory;
            return { memory: memory, api: api, json: factory.json }
        }

        createPolyDSPInstance(voice_factory: Factory, mixer_module: WebAssembly.Module, nvoices: number, effect_factory: Factory): PolyInstance {
            // Parse JSON to get 'size' and 'inputs/ouputs' infos 
            const voice_JSON = JSON.parse(voice_factory.json);
            const effect_JSON = (effect_factory) ? JSON.parse(effect_factory.json) : null;
            // Memory will be shared by voice, mixer and (possibly) effect instances
            const memory = this.createWasmMemory(nvoices, voice_JSON, effect_JSON, 4096);
            // Create voice 
            const voice_instance = new WebAssembly.Instance(voice_factory.module, this.createWasmImport(memory));
            const voice_functions: any = voice_instance.exports;
            const voice_api = new InstanceAPIImpl(<InstanceAPI>voice_functions);
            // Possibly create effect instance 
            let effect_api;
            if (effect_factory) {
                const effect_instance = new WebAssembly.Instance(effect_factory.module, this.createWasmImport(memory));
                const effect_functions: any = effect_instance.exports;
                effect_api = new InstanceAPIImpl(<InstanceAPI>effect_functions);
            }
            // Create mixer instance
            const mix_import = {
                imports: { print: console.log },
                memory: { memory }
            };
            const mixer_instance = new WebAssembly.Instance(mixer_module, mix_import);
            const mixer_functions: any = mixer_instance.exports;
            const mixer_api = mixer_functions;
            return { memory: memory, voice_api: voice_api, effect_api: effect_api, mixer_api: mixer_api, voice_json: voice_factory.json, effect_json: effect_factory.json };
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

    }

    export class Factory implements Faust.Factory {
        constructor(module: WebAssembly.Module, json: string, poly: boolean) {
            this.module = module;
            this.json = json;
            this.poly = poly;
        }
    }

    // deleteAllDSPFactories(): void;
}
