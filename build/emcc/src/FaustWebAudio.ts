
///<reference path="FaustCompiler.ts"/>


interface FaustAudioNode extends AudioNode {
}

interface FaustAudioPolyNode extends FaustAudioNode {
	keyOn(key: number) : void;
	keyOff(key: number) : void;
	allNotesOff() : void;
}

interface FaustWebAudioNode {
	compileMonoNode(compiler: FaustCompiler, dsp_content: string, args: string, scriptprocessor: boolean) : FaustAudioNode;
	compilePolyNode(compiler: FaustCompiler, dsp_content: string, args: string, voices: number, scriptprocessor: boolean) : FaustAudioPolyNode;

	getMonoNode(module: WasmModule, scriptprocessor: boolean) : FaustAudioNode;
	getPolyNode(module: WasmModule, voices: number, scriptprocessor: boolean) : FaustAudioPolyNode;
}
