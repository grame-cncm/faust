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

///<reference path="FaustGenerator.d.ts"/>

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

    export class Generator {

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

        private createWasmMemory(voicesIn: number, dsp_JSON: TFaustJSON, effect_JSON: TFaustJSON, buffer_size: number): WebAssembly.Memory {
            // Hack : at least 4 voices (to avoid weird WASM memory bug?)
            const voices = Math.max(4, voicesIn);
            // Memory allocator
            const ptr_size = 4;
            const sample_size = 4;
            const pow2limit = (x: number) => {
                let n = 65536; // Minimum = 64 kB
                while (n < x) { n *= 2; }
                return n;
            };
            const effect_size = effect_JSON ? effect_JSON.size : 0;
            // Memory for voices + effect + audio buffers.
            let memory_size = pow2limit(
                effect_size
                + dsp_JSON.size * voices
                + (dsp_JSON.inputs + dsp_JSON.outputs * 2)
                * (ptr_size + buffer_size * sample_size)
            ) / 65536;
            memory_size = Math.max(2, memory_size); // As least 2
            console.log("memory_size", memory_size);
            return new WebAssembly.Memory({ initial: memory_size, maximum: memory_size });
        }

        private createDSPInstanceAux(instance: WebAssembly.Instance, factory: Factory) {
            const functions: any = instance.exports;
            const api = new InstanceAPIImpl(<InstanceAPI>functions);
            const memory: any = instance.exports.memory;
            return { memory: memory, api: api, json: factory.json };
        }

        private createMemoryAux(voices: number, voice_factory: Factory, effect_factory: Factory): WebAssembly.Memory {
            // Parse JSON to get 'size' and 'inputs/ouputs' infos
            const voice_JSON = JSON.parse(voice_factory.json);
            const effect_JSON = (effect_factory) ? JSON.parse(effect_factory.json) : null;
            // Memory will be shared by voice, mixer and (possibly) effect instances
            return this.createWasmMemory(voices, voice_JSON, effect_JSON, 4096);
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
        async createAsyncDSPInstance(factory: Factory): Promise<Instance> {
            const instance = await WebAssembly.instantiate(factory.module, this.createWasmImport());
            return (instance) ? this.createDSPInstanceAux(instance, factory) : null;
        }

        createSyncDSPInstance(factory: Factory): Instance {
            const instance = new WebAssembly.Instance(factory.module, this.createWasmImport());
            return (instance) ? this.createDSPInstanceAux(instance, factory) : null;
        }

        async createAsyncPolyDSPInstance(voice_factory: Factory, mixer_module: WebAssembly.Module, voices: number, effect_factory: Factory): Promise<PolyInstance> {
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
                let effect_api = new InstanceAPIImpl(<InstanceAPI>effect_functions);
                return { memory: memory, voices: voices, voice_api: voice_api, effect_api: effect_api, mixer_api: mixer_api, voice_json: voice_factory.json, effect_json: effect_factory.json };
            } else {
                return { memory: memory, voices: voices, voice_api: voice_api, effect_api: null, mixer_api: mixer_api, voice_json: voice_factory.json, effect_json: "" };
            }
        }

        createSyncPolyDSPInstance(voice_factory: Factory, mixer_module: WebAssembly.Module, voices: number, effect_factory: Factory): PolyInstance {
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
                let effect_api = new InstanceAPIImpl(<InstanceAPI>effect_functions);
                return { memory: memory, voices: voices, voice_api: voice_api, effect_api: effect_api, mixer_api: mixer_api, voice_json: voice_factory.json, effect_json: effect_factory.json };
            } else {
                return { memory: memory, voices: voices, voice_api: voice_api, effect_api: null, mixer_api: mixer_api, voice_json: voice_factory.json, effect_json: "" };
            }
        }
    }
}
