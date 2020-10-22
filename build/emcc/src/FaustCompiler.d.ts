/************************************************************************
 This file describes the high level interface to the Faust compiler.
 ************************************************************************/

declare namespace Faust {

    type AudioBuffer = number;
    type DSP = number;

    type TFaustJSON = {
        name: string;
        filename: string;
        compile_options: string;
        include_pathnames: string[];
        inputs: number;
        outputs: number;
        size: number;
        version: string;
        library_list: string[];
        meta: { [key: string]: string }[];
        ui: TFaustUI;
    };

    type TFaustUI = TFaustUIGroup[];
    type TFaustUIItem = TFaustUIInputItem | TFaustUIOutputItem | TFaustUIGroup;
    type TFaustUIInputItem = {
        type: TFaustUIInputType;
        label: string;
        address: string;
        index: number;
        init: number;
        min: number;
        max: number;
        step: number;
        meta?: TFaustUIMeta[];
    };

    type TFaustUIOutputItem = {
        type: TFaustUIOutputType;
        label: string;
        address: string;
        index: number;
        min: number;
        max: number;
        meta: TFaustUIMeta[];
    };

    type TFaustUIMeta = {
        [order: number]: string;
        style: string; // "knob" | "menu{'Name0':value0;'Name1':value1}" | "radio{'Name0':value0;'Name1':value1}" | "led";
        unit: string;
        scale: "linear" | "exp" | "log";
        tooltip: string;
        hidden: string;
        [key: string]: string;
    }

    type TFaustUIGroupType = "vgroup" | "hgroup" | "tgroup";
    type TFaustUIOutputType = "hbargraph" | "vbargraph";
    type TFaustUIInputType = "vslider" | "hslider" | "button" | "checkbox" | "nentry";
    type TFaustUIGroup = {
        type: TFaustUIGroupType;
        label: string;
        items: TFaustUIItem[];
    }
    type TFaustUIType = TFaustUIGroupType | TFaustUIOutputType | TFaustUIInputType;

    interface createFaustJSON { (json: string): TFaustJSON }

    interface Factory {
        cfactory: number;
        module: WebAssembly.Module;
        json: string;
        poly: boolean;
    }

    /**
     * The Compiler constructor.
     * 
     * @param {LibFaust} engine - an instance of the low level engine, actually a libFaustWasm instance of FaustModule
     * @return the created Compiler object 
     */
    interface createCompiler { (engine: LibFaust): Compiler }

    interface Compiler {

        /**
         * Gives the Faust compiler version.
         * @return {string} a version string
         */
        version(): string;

        /**
        * Gives the last compilation error.
        * @return {string} an error string
        */
        getErrorMessage(): string;

        /**
         * Create a wasm factory from Faust code i.e. wasm compiled code, to be used to create monophonic instances. 
         * This function is running asynchronously.
         *
         * @param {string} name - an arbitrary name for the Faust factory
         * @param {string} dsp_code - Faust dsp code
         * @param {string} args - the compiler options
         * @returns {Promise<Factory | null>} returns the wasm factory
         */
        createMonoDSPFactory(name: string, dsp_code: string, args: string): Promise<Factory | null>;

        /**
         * Create a wasm factory from Faust code i.e. wasm compiled code, to be used to create polyphonic instances. 
         * This function is running asynchronously.
         *
         * @param {string} name - an arbitrary name for the Faust factory
         * @param {string} dsp_code - Faust dsp code
         * @param {string} args - the compiler options
         * @returns {Promise<Factory | null>} returns the wasm factory
         */
        createPolyDSPFactory(name: string, dsp_code: string, args: string): Promise<Factory | null>;

        /**
         * Delete a dsp factory.
         *
         * @param {Factory} factory - the factory to be deleted
         */
        deleteDSPFactory(factory: Factory): void;

        /**
         * Expand Faust code i.e. linearize included libraries.
         *
         * @param {string} dsp_code - Faust dsp code
         * @param {string} args - the compiler options
         * @returns {interface} returns the expanded dsp code
         */
        expandDSP(dsp_code: string, args: string): string | null

        /**
         * Generates auxiliary files from Faust code. The output depends on the compiler options.
         *
         * @param {string} name - an arbitrary name for the Faust module
         * @param {string} dsp_code - Faust dsp code
         * @param {string} args - the compiler options
         * @returns {boolean} whether the generation actually succeded
        */
        generateAuxFiles(name: string, dsp_code: string, args: string): boolean;

        /**
         * Delete all factories.
        */
        deleteAllDSPFactories(): void;
    }

}
