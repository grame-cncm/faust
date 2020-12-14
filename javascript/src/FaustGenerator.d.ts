
///<reference path="FaustCompiler.d.ts"/>

/************************************************************************
 FaustGenerator provides the first level above the compiler: it uses the 
 compiler to generate a wasm module and instantiates this module in memory, 
 making the API of this module available.
 ************************************************************************/

declare namespace Faust {

    /**
     * The Faust wasm instance interface.
    */
    interface InstanceAPI {

        /**
         * The dsp computation, to be called with successive input/output audio buffers.
         *
         * @param {DSP} dsp - the DSP pointer
         * @param {number} count - the audio buffer size in frames
         * @param {AudioBuffer} inputs - the input audio buffer as in index in wasm memory
         * @param {AudioBuffer} output - the output audio buffer as in index in wasm memory
         */
        compute(dsp: DSP, count: number, inputs: AudioBuffer, output: AudioBuffer): void;

        /**
         * Give the number of inputs of a Faust wasm instance.
         * 
         * @param {DSP} dsp - the DSP pointer
         */
        getNumInputs(dsp: DSP): number;

        /**
         * Give the number of outputs of a Faust wasm instance.
         * 
         * @param {DSP} dsp - the DSP pointer
         */
        getNumOutputs(dsp: DSP): number;

        /**
         * Give a parameter current value.
         * 
         * @param {DSP} dsp - the DSP pointer
         * @param {number} index - the parameter index
         * @preturn {number} the parameter value
         */
        getParamValue(dsp: DSP, index: number): number;

        /**
         * Give the Faust wasm instance sample rate.
         * 
         * @param {DSP} dsp - the DSP pointer
         * @preturn {number} the sample rate
         */
        getSampleRate(dsp: DSP): number;

        /**
         * Global init, calls the following methods:
         * - static class 'classInit': static tables initialization
         * - 'instanceInit': constants and instance state initialization
         *
         * @param {DSP} dsp - the DSP pointer
         * @param sample_rate - the sampling rate in Hertz
         */
        init(dsp: DSP, sample_rate: number): void;

        /** Init instance state (delay lines...).
         * 
         * @param {DSP} dsp - the DSP pointer
         */
        instanceClear(dsp: DSP): void;

        /** Init instance constant state.
         * 
         * @param {DSP} dsp - the DSP pointer
         * @param sample_rate - the sampling rate in Hertz
         */
        instanceConstants(dsp: DSP, sample_rate: number): void;

        /** Init instance state.
         * 
         * @param {DSP} dsp - the DSP pointer
         * @param sample_rate - the sampling rate in Hertz
         */
        instanceInit(dsp: DSP, sample_rate: number): void;

        /** Init default control parameters values.
         * 
         * @param {DSP} dsp - the DSP pointer
         */
        instanceResetUserInterface(dsp: DSP): void;

        /**
         * Set a parameter current value.
         * 
         * @param {DSP} dsp - the DSP pointer
         * @param {number} index - the parameter index
         * @param {number} value - the parameter value
         */
        setParamValue(dsp: DSP, index: number, value: number): void;
    }

    /**
     * Monophonic instance.
     */
    interface MonoInstance {
        memory: WebAssembly.Memory;
        api: InstanceAPI;
        json: string;
    }

    /**
     * Polyphonic instance.
     */
    interface PolyInstance {
        memory: WebAssembly.Memory;
        voices: number;
        voice_api: InstanceAPI;
        effect_api?: InstanceAPI;
        mixer_api: MixerAPI;
        voice_json: string;
        effect_json?: string;
    }

    /**
     * Mixer used in polyphonic mode.
     */
    interface MixerAPI {
        clearOutput(bufferSize: number, chans: number, ouputs: AudioBuffer): void;
        mixVoice(bufferSize: number, chans: number, inputs: AudioBuffer, ouputs: AudioBuffer): number;
    }

    /**
     * The generator constructor.
     */

    interface Generator {

        /**
         * Create a factory from Faust statically compiled wasm (either 'monophonic' or 'polyphonic') and JSON files. 
         * This function is running asynchronously.
         *
         * @param {string} wasm_path - the wasm file pathname
         * @param {string} json_path - the JSON file pathname
         * @returns {Promise<Factory | null>} on completion, gives a wasm module and retains the poly status given as parameter.
         */
        loadDSPFactory(wasm_path: string, json_path: string): Promise<Factory | null>;

        /**
         * Create a WebAssembly module from the wasm mixer file. 
         * This function is running asynchronously.
         *
         * @param {string} mixer_path - the mixer wasm file pathname
         * @returns {Promise<WebAssembly.Module | null>} on completion, the mixer wasm module.
         */
        loadDSPMixer(mixer_path: string): Promise<WebAssembly.Module | null>;

        /**
         * Asynchronously create a wasm instance using a wasm factory.
         *
         * @param {Factory} module - a module previously created using createDSPFactory or loadDSPFactory
         * @returns {Promise<Instance>} returns a monophonic instance.
         */
        createAsyncMonoDSPInstance(factory: Factory): Promise<MonoInstance>;

        /**
         * Synchronously create a wasm instance using a wasm factory.
         *
         * @param {Factory} module - a module previously created using createDSPFactory or loadDSPFactory
         * @returns {Instance} returns a monophonic instance.
         */
        createSyncMonoDSPInstance(factory: Factory): MonoInstance;

        /**
         * Asynchronously create a polyphonic wasm instance using a wasm voice factory and effect factory. 
         *
         * @param {Factory} voice_factory - a factory previously created using createDSPFactory or loadDSPFactory
         * @param {WebAssembly.Module} mixer_module - a WebAssembly module previously created using loadDSPMixer
         * @param {number} voices - the number of voices to be created
         * @param {Factory} effect_factory - a factory previously created using createDSPFactory or loadDSPFactory
         * @returns {Promise<PolyInstance>} returns a polyphonic instance.
         */
        createAsyncPolyDSPInstance(voice_factory: Factory, mixer_module: WebAssembly.Module, voices: number, effect_factory?: Factory): Promise<PolyInstance>;

        /**
         * Synchronously create a polyphonic wasm instance using a wasm voice factory and effect factory. 
         *
         * @param {Factory} voice_factory - a factory previously created using createDSPFactory or loadDSPFactory
         * @param {WebAssembly.Module} mixer_module - a module previously created using the mixer32.wasm file
         * @param {number} voices - the number of voices to be created
         * @param {Factory} effect_factory - a factory previously created using createDSPFactory or loadDSPFactory
         * @returns {PolyInstance} returns a polyphonic instance.
         */
        createSyncPolyDSPInstance(voice_factory: Factory, mixer_module: WebAssembly.Module, voices: number, effect_factory?: Factory): PolyInstance;

    }
}

// Moved at the end of the file to please Visual Studio code completions tools.

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
