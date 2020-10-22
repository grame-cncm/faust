/************************************************************************
 This file describes the high level interface to the Faust compiler.
 ************************************************************************/

///<reference path="FaustCompiler.d.ts"/>

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
    interface createGenerator { (): Generator }

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
        createAsyncPolyDSPInstance(voice_factory: Factory, mixer_factory: WebAssembly.Module, voices: number, effect_factory?: Factory): Promise<PolyInstance>;

        /**
         * Synchronously create a polyphonic wasm instance using a wasm voice factory and effect factory. 
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
