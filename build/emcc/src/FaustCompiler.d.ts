

interface FaustInstanceAPI {
	compute (count: number, inputs: number, output: number) : void;
	getNumInputs() : number;
	getNumOutputs() : number;
	getParamValue(index: number) : number;
	getSampleRate() : number;
	init(sampleRate: number) : void;
	instanceClear() : void;
	instanceConstants(sampleRate: number) : void;
	instanceInit(sampleRate: number) : void;
	instanceResetUserInterface() : void;
	setParamValue(index: number, value: number) : void;
}

interface FaustInstance {
 	instance  : WebAssembly.Instance;
 	api       : FaustInstanceAPI;
}

interface FaustFactory {
	module  : WebAssembly.Module;
	poly    : boolean;
}

interface FaustCompiler {

	new(engine: LibFaust) : FaustCompiler;

	version() : string;

	createDSPFactory(name_app: string, dsp_content: string, args: string, poly: boolean) : Promise<FaustFactory>;
	createDSPInstance(module: FaustFactory) : Promise<FaustInstance>;

	expandDSP(name_app: string, dsp_content: string, args: string) : Expand
	generateAuxFiles(name_app: string, dsp_content: string, args: string) : Aux;
}
