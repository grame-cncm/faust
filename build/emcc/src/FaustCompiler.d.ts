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
        init?: number;
        min?: number;
        max?: number;
        step?: number;
        meta?: TFaustUIMeta[];
    };
    type TFaustUIOutputItem = {
        type: TFaustUIOutputType;
        label: string;
        address: string;
        index: number;
        min?: number;
        max?: number;
        meta?: TFaustUIMeta[];
    };
    type TFaustUIMeta = {
        [order: number]: string;
        style?: string; // "knob" | "menu{'Name0':value0;'Name1':value1}" | "radio{'Name0':value0;'Name1':value1}" | "led";
        unit?: string;
        scale?: "linear" | "exp" | "log";
        tooltip?: string;
        hidden?: string;
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
     * A Faust wasm instance interface.
    */
    interface InstanceAPI {

        /**
         * The dsp computation.
         *
         * @param {DSP} dsp - the DSP pointer
         * @param {number} count - the audio buffer size
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

    /**
     * Mixer used in polyphonic mode
    */
    interface MixerAPI {
        clearOutput(bufferSize: number, chans: number, ouputs: AudioBuffer): void;
        mixVoice(bufferSize: number, chans: number, inputs: AudioBuffer, ouputs: AudioBuffer): void;
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

    interface Instance {
        memory: WebAssembly.Memory;
        api: InstanceAPI;
        json: string;
    }

    interface PolyInstance {
        memory: WebAssembly.Memory;
        voices: number;
        voice_api: InstanceAPI;
        effect_api: InstanceAPI;
        mixer_api: MixerAPI;
        voice_json: string;
        effect_json: string;
    }

    interface Compiler {

        /**
         * The Faust.Compiler constructor.
         * @param {LibFaust} engine - an instance of the low level engine, actually a libFaustWasm instance of FaustModule
         */
        new(engine: Faust.LibFaust): Compiler;

        /**
         * Gives the Faust engine version.
         * @return {string} a version string
         */
        version(): string;

        /**
         * Create a wasm factory from Faust code i.e. wasm compiled code. This function is running asynchronously.
         *
         * @param {string} name - an arbitrary name for the Faust factory
         * @param {string} code - Faust dsp code
         * @param {string} args - the compiler options
         * @param {boolean} poly - tells the compiler to generate static embedded memory or not
         * @returns {Promise<Factory>} on completion, gives a wasm module and retains the poly status given as parameter.
         */
        createDSPFactory(name_app: string, dsp_content: string, args: string, poly: boolean): Promise<Factory>;

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

        /**
         * Expand faust code i.e. linearize included libraries.
         *
         * @param {string} name_app - an arbitrary name for the faust module
         * @param {string} dsp_content - faust dsp code
         * @param {string} args - the compiler options
         * @returns {Expand} contains the expanded dsp code, the corresponding sha key and an error string (empty in case of success)
         */
        expandDSP(name_app: string, dsp_content: string, args: string): ExpandOut

        /**
         * Generates auxiliary files from faust code. The output depends on the compiler options.
         *
         * @param {string} name_app - an arbitrary name for the faust module
         * @param {string} dsp_content - faust dsp code
         * @param {string} args - the compiler options
         * @returns {AuxOut} contains the boolean status code and an error string (empty in case of success)
        */
        generateAuxFiles(name_app: string, dsp_content: string, args: string): AuxOut;

        /**
         * Delete all factories.
        */
        deleteAllDSPFactories(): void;
    }

}
