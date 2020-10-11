/************************************************************************
 This file describes the high level interface to the Faust compiler.
 ************************************************************************/

///<reference path="FaustCompiler.d.ts"/>

declare namespace Faust {

    /**
     * Mixer used in polyphonic mode
    */
    interface MixerAPI {
        clearOutput(bufferSize: number, chans: number, ouputs: AudioBuffer): void;
        mixVoice(bufferSize: number, chans: number, inputs: AudioBuffer, ouputs: AudioBuffer): void;
    }

    interface Instance {
        memory: WebAssembly.Memory;
        api: InstanceAPI;
        json: string;
    }

    interface PolyInstance {
        memory: WebAssembly.Memory;
        voices: number;
        voice_api: InstanceAPI;
        effect_api?: InstanceAPI;
        mixer_api: MixerAPI;
        voice_json: string;
        effect_json?: string;
    }

    interface Generator {

        /**
         * Create a factory from Faust statically compiled wasm (either 'monophonic' or 'polyphonic') and JSON files. This function is running asynchronously.
         *
         * @param {string} wasm_path - the wasm file pathname
         * @param {string} json_path - the JSON file pathname
         * @returns {Promise<Factory | null>} on completion, gives a wasm module and retains the poly status given as parameter.
         */
        loadDSPFactory(wasm_path: string, json_path: string, poly: boolean): Promise<Factory | null>;

        /**
         * Create a WebAssembly module from the wasm mixer file. This function is running asynchronously.
         *
         * @param {string} mixer_path - the mixer wasm file pathname
         * @returns {Promise<WebAssembly.Module | null>} on completion, the mixer wasm module.
         */
        loadDSPMixer(mixer_path: string): Promise<WebAssembly.Module | null>;

        /**
         * Asynchronously create a wasm instance of a wasm factory.
         *
         * @param {Factory} module - a module previously created using createDSPFactory or loadDSPFactory
         * @returns {Promise<Instance>} returns a monophonic instance.
         */
        createAsyncMonoDSPInstance(factory: Factory): Promise<Instance>;

        /**
        * Synchronously create a wasm instance of a wasm factory.
        *
        * @param {Factory} module - a module previously created using createDSPFactory or loadDSPFactory
        * @returns {Instance} returns a monophonic instance.
        */
        createSyncMonoDSPInstance(factory: Factory): Instance;

        /**
         * Asynchronously create a polyphonic wasm instance of a wasm voice factory and effect factory. 
         *
         * @param {Factory} voice_factory - a factory previously created using createDSPFactory or loadDSPFactory
         * @param {WebAssembly.Module} mixer_module - a WebAssembly module previously created using loadDSPMixer
         * @param {number} voices - the number of voices to be created
         * @param {Factory} effect_factory - a factory previously created using createDSPFactory or loadDSPFactory
         * @returns {Promise<PolyInstance>} returns a polyphonic instance.
         */
        createAsyncPolyDSPInstance(voice_factory: Factory, mixer_factory: WebAssembly.Module, voices: number, effect_factory?: Factory): Promise<PolyInstance>;

        /**
        * Synchronously create a polyphonic wasm instance of a wasm voice factory and effect factory. 
        *
        * @param {Factory} voice_factory - a factory previously created using createDSPFactory or loadDSPFactory
        * @param {WebAssembly.Module} mixer_module - a module previously created using the mixer32.wasm file
        * @param {number} voices - the number of voices to be created
        * @param {Factory} effect_factory - a factory previously created using createDSPFactory or loadDSPFactory
        * @returns {PolyInstance} returns a polyphonic instance.
        */
        createSyncPolyDSPInstance(voice_factory: Factory, mixer_factory: WebAssembly.Module, voices: number, effect_factory?: Factory): PolyInstance;

    }
}
