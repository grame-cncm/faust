
///<reference path="FaustCompiler.ts"/>

interface FaustAudioNode extends AudioNode {
	setOutputParamHandler(handler: any) : void; // handler is actually a function of type function(path, value), how to we represent that?
	getOutputParamHandler() : any;
	metadata(handler: any) : void; // handler is actually a function of type function(key, value), how to we represent that?
	ctrlChange(chan: number, ctrl: number, value: number) : void;
	pitchWheel(chan: number, value: number) : void;
	setParamValue(path: string, value: number) : void;
	getParamValue(path: string) : number;
	//getParams() : any;   // returns an array of paths
	getJSON() : string;
	destroy() : void; // to check is this function is still really needed
}

interface FaustAudioPolyNode extends FaustAudioNode {
	keyOn(key: number, vel: number) : void;
	keyOff(key: number, vel: number) : void;
	allNotesOff() : void;
}

interface FaustWebAudioNode {
	compileMonoNode(compiler: FaustCompiler, dsp_content: string, args: string, scriptprocessor: boolean) : FaustAudioNode;
	compilePolyNode(compiler: FaustCompiler, dsp_content: string, args: string, voices: number, scriptprocessor: boolean) : FaustAudioPolyNode;

	getMonoNode(module: WasmModule, scriptprocessor: boolean) : FaustAudioNode;
	getPolyNode(module: WasmModule, voices: number, scriptprocessor: boolean) : FaustAudioPolyNode;
}
