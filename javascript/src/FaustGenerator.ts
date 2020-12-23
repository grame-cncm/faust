/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2020 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 ************************************************************************
 ************************************************************************/

///<reference path="libfaust.ts"/>
///<reference path="FaustCompiler.ts"/>
///<reference path="FaustGenerator.d.ts"/>

namespace Faust {

    export function createInstanceAPI(exports: InstanceAPI): InstanceAPI { return new InstanceAPIImpl(exports); }

    export class InstanceAPIImpl implements InstanceAPI {
        private readonly fExports: InstanceAPI;

        constructor(exports: InstanceAPI) { this.fExports = exports; }

        compute(dsp: DSP, count: number, input: AudioBuffer, output: AudioBuffer) { this.fExports.compute(dsp, count, input, output); }
        getNumInputs(dsp: DSP) { return this.fExports.getNumInputs(dsp); }
        getNumOutputs(dsp: DSP) { return this.fExports.getNumOutputs(dsp); }
        getParamValue(dsp: DSP, index: number) { return this.fExports.getParamValue(dsp, index); }
        getSampleRate(dsp: DSP) { return this.fExports.getSampleRate(dsp); }
        init(dsp: DSP, sampleRate: number) { this.fExports.init(dsp, sampleRate); }
        instanceClear(dsp: DSP) { this.fExports.instanceClear(dsp); }
        instanceConstants(dsp: DSP, sampleRate: number) { this.fExports.instanceConstants(dsp, sampleRate); }
        instanceInit(dsp: DSP, sampleRate: number) { this.fExports.instanceInit(dsp, sampleRate); }
        instanceResetUserInterface(dsp: DSP) { this.fExports.instanceResetUserInterface(dsp); }
        setParamValue(dsp: DSP, index: number, value: number) { this.fExports.setParamValue(dsp, index, value); }
    }

    export function createGenerator() { return new GeneratorImp(); }

    export class GeneratorImp implements Generator {

        private createWasmImport(memory?: WebAssembly.Memory): WebAssembly.Imports {
            return {
                env: {
                    memory: ((memory) ? memory : new WebAssembly.Memory({ initial: 100 })),
                    memoryBase: 0,
                    tableBase: 0,
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
            }
        }

        private createWasmMemory(voices_in: number, sample_size: number, voice_JSON: TFaustJSON, effect_JSON: TFaustJSON | null, buffer_size: number)
            : WebAssembly.Memory {
            // Hack : at least 4 voices (to avoid weird WASM memory bug?)
            const voices = Math.max(4, voices_in);
            // Memory allocator
            const ptr_size = sample_size; // Done on wast/wasm backend side
            const pow2limit = (x: number) => {
                let n = 65536; // Minimum = 64 kB
                while (n < x) { n *= 2; }
                return n;
            };
            const effect_size = (effect_JSON ? effect_JSON.size : 0);
            // Memory for voices + effect + audio buffers
            let memory_size = pow2limit(
                effect_size
                + voice_JSON.size * voices
                + (voice_JSON.inputs + voice_JSON.outputs * 2)
                * (ptr_size + buffer_size * sample_size)
            ) / 65536;
            memory_size = Math.max(2, memory_size); // As least 2
            return new WebAssembly.Memory({ initial: memory_size, maximum: memory_size });
        }

        private createMonoDSPInstanceAux(instance: WebAssembly.Instance, factory: Factory) {
            const functions: any = instance.exports;
            const api = new InstanceAPIImpl(<InstanceAPI>functions);
            const memory: any = instance.exports.memory;
            return { memory: memory, api: api, json: factory.json };
        }

        private createMemoryAux(voices: number, voice_factory: Factory, effect_factory?: Factory): WebAssembly.Memory {
            // Parse JSON to get 'size' and 'inputs/outputs' infos
            const voice_JSON = createFaustJSON(voice_factory.json);
            const effect_JSON = (effect_factory && effect_factory.json) ? createFaustJSON(effect_factory.json) : null;
            const sample_size = voice_JSON.compile_options.match("-double") ? 8 : 4;
            // Memory will be shared by voice, mixer and (possibly) effect instances
            return this.createWasmMemory(voices, sample_size, voice_JSON, effect_JSON, 8192);
        }

        private createMixerAux(mixer_module: WebAssembly.Module, memory: WebAssembly.Memory): MixerAPI {
            // Create mixer instance
            const mix_import = {
                imports: { print: console.log },
                memory: { memory }
            };
            const mixer_instance = new WebAssembly.Instance(mixer_module, mix_import);
            const mixer_functions: any = mixer_instance.exports;
            return mixer_functions;
        }

        // Public API
        async loadDSPFactory(wasm_path: string, json_path: string): Promise<Factory | null> {
            const wasm_file = await fetch(wasm_path);
            if (!wasm_file.ok) {
                console.error("=> exception raised while running loadDSPFactory, file not found: " + wasm_path);
                return null;
            }
            try {
                const wasm_buffer = await wasm_file.arrayBuffer();
                const module = await WebAssembly.compile(wasm_buffer);
                const json_file = await fetch(json_path);
                const json = await json_file.text();
                const JSONDsp = createFaustJSON(json);
                const c_options = JSONDsp.compile_options;
                const poly = c_options.indexOf('wasm-e') !== -1;
                return { cfactory: 0, code: wasm_buffer as Uint8Array, module: module, json: json, poly: poly };
            } catch (e) {
                console.error("=> exception raised while running loadDSPFactory: " + e);
                return null;
            }
        }

        async loadDSPMixer(mixer_path: string): Promise<WebAssembly.Module | null> {
            try {
                let mixer_buffer = null;
                if (FS) {
                    mixer_buffer = FS.readFile(mixer_path, { encoding: 'binary' });
                } else {
                    const mixer_file = await fetch(mixer_path);
                    mixer_buffer = await mixer_file.arrayBuffer();
                }
                // Compile mixer
                return WebAssembly.compile(mixer_buffer);
            } catch (e) {
                console.error("=> exception raised while running loadMixer: " + e);
                return null;
            }
        }

        async createAsyncMonoDSPInstance(factory: Factory): Promise<MonoInstance> {
            const instance = await WebAssembly.instantiate(factory.module, this.createWasmImport());
            return this.createMonoDSPInstanceAux(instance, factory);
        }

        createSyncMonoDSPInstance(factory: Factory): MonoInstance {
            const instance = new WebAssembly.Instance(factory.module, this.createWasmImport());
            return this.createMonoDSPInstanceAux(instance, factory);
        }

        async createAsyncPolyDSPInstance(voice_factory: Factory, mixer_module: WebAssembly.Module, voices: number, effect_factory?: Factory): Promise<PolyInstance> {
            const memory = this.createMemoryAux(voices, voice_factory, effect_factory);
            // Create voice 
            const voice_instance = await WebAssembly.instantiate(voice_factory.module, this.createWasmImport(memory));
            const voice_functions: any = voice_instance.exports;
            const voice_api = new InstanceAPIImpl(<InstanceAPI>voice_functions);
            // Create mixer
            const mixer_api = this.createMixerAux(mixer_module, memory);

            // Possibly create effect instance 
            if (effect_factory) {
                const effect_instance = await WebAssembly.instantiate(effect_factory.module, this.createWasmImport(memory));
                const effect_functions: any = effect_instance.exports;
                const effect_api = new InstanceAPIImpl(<InstanceAPI>effect_functions);
                return {
                    memory: memory,
                    voices: voices,
                    voice_api: voice_api,
                    effect_api: effect_api,
                    mixer_api: mixer_api,
                    voice_json: voice_factory.json,
                    effect_json: effect_factory.json
                };
            } else {
                return {
                    memory: memory,
                    voices: voices,
                    voice_api: voice_api,
                    effect_api: undefined,
                    mixer_api: mixer_api,
                    voice_json: voice_factory.json,
                    effect_json: undefined
                };
            }
        }

        createSyncPolyDSPInstance(voice_factory: Factory, mixer_module: WebAssembly.Module, voices: number, effect_factory?: Factory): PolyInstance {
            const memory = this.createMemoryAux(voices, voice_factory, effect_factory);
            // Create voice 
            const voice_instance = new WebAssembly.Instance(voice_factory.module, this.createWasmImport(memory));
            const voice_functions: any = voice_instance.exports;
            const voice_api = new InstanceAPIImpl(<InstanceAPI>voice_functions);
            // Create mixer
            const mixer_api = this.createMixerAux(mixer_module, memory);

            // Possibly create effect instance 
            if (effect_factory) {
                const effect_instance = new WebAssembly.Instance(effect_factory.module, this.createWasmImport(memory));
                const effect_functions: any = effect_instance.exports;
                const effect_api = new InstanceAPIImpl(<InstanceAPI>effect_functions);
                return {
                    memory: memory,
                    voices: voices,
                    voice_api: voice_api,
                    effect_api: effect_api,
                    mixer_api: mixer_api,
                    voice_json: voice_factory.json,
                    effect_json: effect_factory.json
                };
            } else {
                return {
                    memory: memory,
                    voices: voices,
                    voice_api: voice_api,
                    effect_api: undefined,
                    mixer_api: mixer_api,
                    voice_json: voice_factory.json,
                    effect_json: undefined
                };
            }
        }
    }
}
