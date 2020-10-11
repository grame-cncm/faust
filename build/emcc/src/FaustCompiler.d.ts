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

    /**
     * The Faust wasm instance interface.
    */
    interface InstanceAPI {

        /**
         * The dsp computation.
         *
         * @param {DSP} dsp - the DSP pointer
         * @param {number} count - the audio buffer size in frames
         * @param {AudioBuffer} inputs - the input audio buffer
         * @param {AudioBuffer} output - the output audio buffer
         */
        compute(dsp: DSP, count: number, inputs: AudioBuffer, output: AudioBuffer): void;

        /**
         * Gives the number of inputs of a Faust wasm instance
         * 
         * @param {DSP} dsp - the DSP pointer
         */
        getNumInputs(dsp: DSP): number;
        /**
         * Gives the number of outputs of a Faust wasm instance
         * 
         * @param {DSP} dsp - the DSP pointer
         */
        getNumOutputs(dsp: DSP): number;
        /**
         * Gives a parameter current value
         * 
         * @param {DSP} dsp - the DSP pointer
         * @param {number} index - the parameter index
         * @preturn {number} the parameter value
        */
        getParamValue(dsp: DSP, index: number): number;
        /**
         * Gives the Faust wasm instance sample rate
         * 
         * @param {DSP} dsp - the DSP pointer
         */
        getSampleRate(dsp: DSP): number;
        init(dsp: DSP, sample_rate: number): void;
        instanceClear(dsp: DSP): void;
        instanceConstants(dsp: DSP, sample_rate: number): void;
        instanceInit(dsp: DSP, sample_rate: number): void;
        instanceResetUserInterface(dsp: DSP): void;
        /**
         * Set a parameter current value
         * 
         * @param {DSP} dsp - the DSP pointer
         * @param {number} index - the parameter index
         * @param {number} value - the parameter value
        */
        setParamValue(dsp: DSP, index: number, value: number): void;
    }

    interface Factory {
        module: WebAssembly.Module;
        json: string;
        poly: boolean;
    }

    interface ExpandOut {
        dsp: string;
        shakey: string;
        error: string;
    }

    interface AuxOut {
        success: boolean;
        error: string;
    }

    interface Compiler {

        /**
         * The Compiler constructor.
         * @param {LibFaust} engine - an instance of the low level engine, actually a libFaustWasm instance of FaustModule
         */
        new(engine: LibFaust): Compiler;

        /**
         * Gives the Faust engine version.
         * @return {string} a version string
         */
        version(): string;

        /**
         * Create a wasm factory from Faust code i.e. wasm compiled code. This function is running asynchronously.
         *
         * @param {string} name - an arbitrary name for the Faust factory
         * @param {string} dsp_code - Faust dsp code
         * @param {string} args - the compiler options
         * @param {boolean} poly - tells the compiler to generate static embedded memory or not
         * @returns {Promise<Factory>} on completion, gives a wasm module and retains the poly status given as parameter.
         */
        createDSPFactory(name_app: string, dsp_code: string, args: string, poly: boolean): Promise<Factory | null>;

        /**
         * Expand faust code i.e. linearize included libraries.
         *
         * @param {string} name_app - an arbitrary name for the faust module
         * @param {string} dsp_code - faust dsp code
         * @param {string} args - the compiler options
         * @returns {Expand} contains the expanded dsp code, the corresponding sha key and an error string (empty in case of success)
         */
        expandDSP(name_app: string, dsp_code: string, args: string): ExpandOut

        /**
         * Generates auxiliary files from faust code. The output depends on the compiler options.
         *
         * @param {string} name_app - an arbitrary name for the faust module
         * @param {string} dsp_code - faust dsp code
         * @param {string} args - the compiler options
         * @returns {AuxOut} contains the boolean status code and an error string (empty in case of success)
        */
        generateAuxFiles(name_app: string, dsp_code: string, args: string): AuxOut;

        /**
         * Delete all factories.
        */
        deleteAllDSPFactories(): void;
    }

}
