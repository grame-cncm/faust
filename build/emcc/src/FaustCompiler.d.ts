/************************************************************************
 This file describes the high level interface to the Faust compiler.
 ************************************************************************/

declare namespace Faust {

type AudioBuffer = number;

/**
 * A Faust wasm instance interface.
*/
interface InstanceAPI {

    /**
     * The dsp computation.
     *
     * @param {number} count - the audio buffer size
     * @param {AudioBuffer} inputs - the input audio buffer
     * @param {AudioBuffer} output - the output audio buffer
     */
	compute(count: number, inputs: AudioBuffer, output: AudioBuffer): void;

    /**
     * Gives the number of inputs of a Faust wasm instance
     */
	getNumInputs(): number;
    /**
     * Gives the number of outputs of a Faust wasm instance
     */
	getNumOutputs(): number;
    /**
     * Gives a parameter current value
    * @param {number} index - the parameter index
    * @preturn {number} the parameter value
    */
	getParamValue(index: number): number;
    /**
     * Gives the Faust wasm instance sample rate
     */
	getSampleRate(): number;
	init(sampleRate: number): void;
	instanceClear(): void;
	instanceConstants(sampleRate: number): void;
	instanceInit(sampleRate: number): void;
	instanceResetUserInterface(): void;
    /**
     * Set a parameter current value
    * @param {number} index - the parameter index
    * @param {number} value - the parameter value
    */
   setParamValue(index: number, value: number): void;
}

interface Instance {
	instance: WebAssembly.Instance;
	api: InstanceAPI;
	json: string;
}

interface Factory {
	module: WebAssembly.Module;
	poly: boolean;
}

interface ExpandOut { 
	dsp: string;
	shakey: string;
	error: string; 
}

interface AuxOut  { 
	success: boolean;
	error: string; 
}

interface Compiler {

	/**
	 * The Faust.Compiler constructor.
	 * @param {LibFaust} engine - an instance of the low level engine, actually a libFaustWasm instance of FaustModule
	 */
	new(engine: LibFaust): Compiler;

	/**
	 * Gives the Faust engine version.
	 * @return {string} a version string
	 */
	version(): string;

    /**
     * Create a wasm factory from faust code i.e. wasm compiled code. This function is running asynchronously.
     *
     * @param {string} name - an arbitrary name for the faust module
     * @param {string} code - faust dsp code
     * @param {string} args - the compiler options
     * @param {boolean} internal_memory - tell the compiler to generate static embedded memory or not
	 * @returns {Promise<Factory>} on completion, gives a wasm module and retains the poly status given as parameter.
     */
	createDSPFactory(name_app: string, dsp_content: string, args: string, poly: boolean): Promise<Factory>;

    /**
     * Create a wasm instance of a wasm factory. This function is running asynchronously.
     *
     * @param {Factory} module - a module previously created using createDSPFactory
	 * @returns {Promise<Instance>} on completion, gives a wasm instance and the associated object to manipulate this instance.
     */
	createDSPInstance(module: Factory): Promise<Instance>;

    /**
     * Expand faust code i.e. linearize included libraries
     *
     * @param {string} name - an arbitrary name for the faust module
     * @param {string} code - faust dsp code
     * @param {string} args - the compiler options
	 * @returns {Expand} contains the expanded dsp code, the corresponding sha key and an error string (empty in case of success)
     */
	expandDSP(name_app: string, dsp_content: string, args: string): ExpandOut

    /**
     * Generates auxiliary files from faust code. The output depends on the compiler options
     *
     * @param {string} name - an arbitrary name for the faust module
     * @param {string} code - faust dsp code
     * @param {string} args - the compiler options
 	 * @returns {AuxOut} contains the boolean status code and an error string (empty in case of success)
    */
	generateAuxFiles(name_app: string, dsp_content: string, args: string): AuxOut;
}

}
