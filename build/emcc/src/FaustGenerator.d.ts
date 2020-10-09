/************************************************************************
 This file describes the high level interface to the Faust compiler.
 ************************************************************************/

///<reference path="FaustCompiler.d.ts"/>

declare namespace Faust {

    interface Generator {

        /**
         * Load a wasm factory from wasm and JSON files This function is running asynchronously.
         *
         * @param {string} wasm_path - the wasm file pathname
         * @param {string} json_path - the JSON file pathname
         * @param {boolean} poly - tells the compiler to generate static embedded memory or not
         * @returns {Promise<Factory>} on completion, gives a wasm module and retains the poly status given as parameter.
         */
        loadDSPFactory(wasm_path: string, json_path: string, poly: boolean): Promise<Faust.Factory>;

        /**
         * Asynchronously create a wasm instance of a wasm factory.
         *
         * @param {Factory} module - a module previously created using createDSPFactory or loadDSPFactory
         * @returns {Promise<Instance>} returns a monophonic instance.
         */
        createAsyncDSPInstance(factory: Factory): Promise<Instance>;

        /**
        * Synchronously create a wasm instance of a wasm factory.
        *
        * @param {Factory} module - a module previously created using createDSPFactory or loadDSPFactory
        * @returns {Instance} returns a monophonic instance.
        */
        createSyncDSPInstance(factory: Factory): Instance;

        /**
         * Asynchronously create a polyphonic wasm instance of a wasm voice factory and effect factory. 
         *
         * @param {Factory} voice_factory - a factory previously created using createDSPFactory or loadDSPFactory
         * @param {WebAssembly.Module} mixer_module - a module previously created using the mixer32.wasm file
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
