
interface WasmModule     {}

interface Factory {
	module  : WasmModule;
	error  : string;
}
interface Expand {
	dsp  : string;
	shakey  : string;
	error  : string;
}
interface Aux {
	success  : boolean;
	error  : string;
}


interface LibFaust {
	version() : string;

	createDSPFactory(name_app: string, dsp_content: string, args: string, internal_memory: boolean) : Factory;

	expandDSP(name_app: string, dsp_content: string, args: string) : Expand	

	generateAuxFiles(name_app: string, dsp_content: string, args: string) : Aux;

	deleteAllDSPFactories(): void;

	getWasmModule(module: WasmModule) : string;
	getWasmModuleSize( module: WasmModule) : number;
	getWasmHelpers(module: WasmModule) : string;
	freeWasmModule(module: WasmModule) : void;
	freeMemory (mem: any) : void;

	cleanupAfterException(): void;
	getErrorAfterException() : string;
}
