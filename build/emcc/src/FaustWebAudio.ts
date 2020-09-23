/************************************************************************
 ************************************************************************
	FAUST compiler
	Copyright (C) 2003-2020 GRAME, Centre National de Creation Musicale
	---------------------------------------------------------------------
	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

///<reference path="libfaust.d.ts"/>
///<reference path="FaustCompiler.ts"/>
///<reference path="FaustWebAudio.d.ts"/>

// JSON UI

export type TFaustJSON = {
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

export type TFaustUI = TFaustUIGroup[];
export type TFaustUIItem = TFaustUIInputItem | TFaustUIOutputItem | TFaustUIGroup;
export type TFaustUIInputItem = {
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
export type TFaustUIOutputItem = {
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
export type TFaustUIGroupType = "vgroup" | "hgroup" | "tgroup";
export type TFaustUIOutputType = "hbargraph" | "vbargraph";
export type TFaustUIInputType = "vslider" | "hslider" | "button" | "checkbox" | "nentry";
export type TFaustUIGroup = {
	type: TFaustUIGroupType;
	label: string;
	items: TFaustUIItem[];
}
export type TFaustUIType = TFaustUIGroupType | TFaustUIOutputType | TFaustUIInputType;

class MonoDSPImp implements MonoDSP {

	fOutputHandler: OutputParamHandler;

	fInputs: number;
	fOutputs: number;

	fInChannels: Float32Array[];
	fOutChannels: Float32Array[];

	fBufferSize: number;
	gPtrSize: number;
	gSampleSize: number;

	fInstance: Faust.Instance;

	fOutputsTimer: number;

	fInputsItems: Array<string>;
	fOutputsItems: Array<string>;

	fAudioInputs: number;
	fAudioOutputs: number;
	fDSP: number;

	fPitchwheelLabel: { path: string; min: number; max: number }[];
	fCtrlLabel: { path: string; min: number; max: number }[][];

	fPathTable: { [address: string]: number };

	fDestroyed: boolean;

	fJSONObj: TFaustJSON;

	constructor(instance: Faust.Instance) {
		this.fOutputHandler = null;
		this.fInstance = instance;

		this.gPtrSize = 4;
		this.gSampleSize = 4;
		this.fDestroyed = false;

		this.setup();
	}

	// JSON parsing functions
	static parseUI(ui: TFaustUI, callback: (...args: any[]) => any) {
		ui.forEach(group => MonoDSPImp.parseGroup(group, callback));
	}

	static parseGroup(group: TFaustUIGroup, callback: (...args: any[]) => any) {
		if (group.items) {
			MonoDSPImp.parseItems(group.items, callback);
		}
	}
	static parseItems(items: TFaustUIItem[], callback: (...args: any[]) => any) {
		items.forEach(item => MonoDSPImp.parseItem(item, callback));
	}

	static parseItem(item: TFaustUIItem, callback: (...args: any[]) => any) {
		if (item.type === "vgroup" || item.type === "hgroup" || item.type === "tgroup") {
			MonoDSPImp.parseItems(item.items, callback);
		} else {
			callback(item);
		}
	}

	private setupMemory() {

		// Start of DSP memory: Mono DSP is placed first with index 0
		this.fDSP = 0;

		// DSP is placed first with index 0. Audio buffer start at the end of DSP.
		let audio_ptr = this.fJSONObj.size;

		// Setup pointers offset
		this.fAudioInputs = audio_ptr;
		this.fAudioOutputs = this.fAudioInputs + this.fInputs * this.gPtrSize;

		// Prepare WASM memory layout
		let audio_inputs_ptr = this.fAudioOutputs + (this.fOutputs * this.gPtrSize);
		let audio_outputs_ptr = audio_inputs_ptr + (this.fInputs * this.fBufferSize * this.gSampleSize);

		const memory: any = this.fInstance.instance.exports.memory;
		const HEAP = memory.buffer;

		const HEAP32 = new Int32Array(HEAP);
		const HEAPF32 = new Float32Array(HEAP);

		if (this.fInputs > 0) {

			//node.$ins = node.$$audioHeapInputs;
			for (let chan = 0; chan < this.fInputs; chan++) {
				HEAP32[(this.fAudioInputs >> 2) + chan] = audio_inputs_ptr + this.fBufferSize * this.gSampleSize * chan;
			}
			// Prepare Ins buffer tables
			const dspInChans = HEAP32.subarray(this.fAudioInputs >> 2, (this.fAudioInputs + this.fInputs * this.gPtrSize) >> 2);
			for (let chan = 0; chan < this.fInputs; chan++) {
				this.fInChannels[chan] = HEAPF32.subarray(dspInChans[chan] >> 2, (dspInChans[chan] + this.fBufferSize * this.gSampleSize) >> 2);
			}
		}
		if (this.fOutputs > 0) {

			//node.$outs = node.$$audioHeapOutputs;
			for (let chan = 0; chan < this.fOutputs; chan++) {
				HEAP32[(this.fAudioOutputs >> 2) + chan] = audio_outputs_ptr + this.fBufferSize * this.gSampleSize * chan;
			}
			// Prepare Out buffer tables
			const dspOutChans = HEAP32.subarray(this.fAudioOutputs >> 2, (this.fAudioOutputs + this.fOutputs * this.gPtrSize) >> 2);
			for (let chan = 0; chan < this.fOutputs; chan++) {
				this.fOutChannels[chan] = HEAPF32.subarray(dspOutChans[chan] >> 2, (dspOutChans[chan] + this.fBufferSize * this.gSampleSize) >> 2);
			}
		}
	}

	compute(input: Float32Array[], output: Float32Array[]) {

		// CHeck DSP state
		if (this.fDestroyed) return false;

		// Check inputs
		if (this.fInputs > 0 && (!input || !input[0] || input[0].length === 0)) {
			// console.log("Process input error");
			return true;
		}

		// Check outputs
		if (this.fOutputs > 0 && (!output || !output[0] || output[0].length === 0)) {
			// console.log("Process output error");
			return true;
		}

		// Copy inputs
		if (input !== undefined) { // TO CHECK
			for (let chan = 0; chan < Math.min(this.fInputs, input.length); ++chan) {
				const dspInput = this.fInChannels[chan];
				dspInput.set(input[chan]);
			}
		}

		/*
		// Update controls (possibly needed for sample accurate control)
		for (const path in parameters) {
			const paramArray = parameters[path];
			this.setParamValue(path, paramArray[0]);
		}
		// Possibly call an externally given callback (for instance to synchronize playing a MIDIFile...)
		if (this.computeHandler) this.computeHandler(this.bufferSize);
		*/

		// Compute
		this.fInstance.api.compute(this.fDSP, this.fBufferSize, this.fAudioInputs, this.fAudioOutputs);

		// Update bargraph
		this.updateOutputs();

		// Copy outputs
		if (output !== undefined) {	// TO CHECK
			for (let chan = 0; chan < Math.min(this.fOutputs, output.length); chan++) {
				const dspOutput = this.fOutChannels[chan];
				output[chan].set(dspOutput);
			}

			// TODO
			/*
			this.port.postMessage({ type: "plot", value: output, index: this.$buffer++, events: this.cachedEvents });
			this.cachedEvents = [];
			*/
		}
		return true;
	}

	private setup() {

		this.setupMemory();

		// Parse UI
		this.fJSONObj = JSON.parse(this.fInstance.json);

		let callback = (item: TFaustUIItem) => {

			if (item.type === "hbargraph" || item.type === "vbargraph") {
				// Keep bargraph adresses
				this.fOutputsItems.push(item.address);
				this.fPathTable[item.address] = item.index;
			} else if (item.type === "vslider" || item.type === "hslider" || item.type === "button" || item.type === "checkbox" || item.type === "nentry") {
				// Keep inputs adresses
				this.fInputsItems.push(item.address);
				this.fPathTable[item.address] = item.index;
				// TODO
				/*
				if (item.meta) {
					item.meta.forEach((meta) => {
						const { midi } = meta;
						if (!midi) return;
						const strMidi = midi.trim();
						if (strMidi === "pitchwheel") {
							node.fPitchwheelLabel.push({ path: item.address, min: item.min, max: item.max });
						} else {
							const matched = strMidi.match(/^ctrl\s(\d+)/);
							if (!matched) return;
							node.fCtrlLabel[parseInt(matched[1])].push({ path: item.address, min: item.min, max: item.max });
						}
					});
				}
				*/
			}
		}

		MonoDSPImp.parseUI(this.fJSONObj.ui, callback);
	}

	private updateOutputs() { }

	getNumInputs() {
		return this.fInstance.api.getNumInputs(this.fDSP);
	}
	getNumOutputs() {
		return this.fInstance.api.getNumOutputs(this.fDSP);
	}

	ctrlChange(chan: number, ctrl: number, value: number) { }
	pitchWheel(chan: number, value: number) { }

	setParamValue(path: string, value: number) {
		this.fInstance.api.setParamValue(this.fDSP, this.fPathTable[path], value);
	}
	getParamValue(path: string) {
		return this.fInstance.api.getParamValue(this.fDSP, this.fPathTable[path]);
	}

	getParams() { return this.fInputsItems; }

	getJSON() { return this.fInstance.json; }

}

class PolyDSPImp extends MonoDSPImp {

	fEffectInstance?: Faust.Instance;
	fMixerInstance?: Faust.Instance;

	fFreqLabel?: number[];
	fGateLabel?: number[];
	fGainLabel?: number[];

	fDSPVoices?: number[];
	fDSPVoicesState?: number[];
	fDSPVoicesLevel?: number[];
	fDSPVoicesDate?: number[];

	kActiveVoice?: number;
	kFreeVoice?: number;
	kReleaseVoice?: number;
	kNoVoice?: number;

};

// Public API

// Test extending 'AudioWorkletNode'
class FaustAudioWorkletNode extends AudioWorkletNode implements FaustAudioNode {

	fDSPCode: MonoDSP;

	constructor(context: BaseAudioContext, name: string, options?: AudioWorkletNodeOptions) {
		super(context, name, options);
	}

	setOutputParamHandler(handler: OutputParamHandler) { }
	getOutputParamHandler() { return function (path: string, value: number) { } }

	metadata(handler: MetadataHandler) { return function (path: string, value: number) { } }

	ctrlChange(chan: number, ctrl: number, value: number) { this.fDSPCode.ctrlChange(chan, ctrl, value); }
	pitchWheel(chan: number, value: number) { this.fDSPCode.pitchWheel(chan, value); }

	setParamValue(path: string, value: number) { this.fDSPCode.setParamValue(path, value); }
	getParamValue(path: string) { return this.fDSPCode.getParamValue(path); }
	getParams() { return this.fDSPCode.getParams(); }

	getJSON() { return this.fDSPCode.getJSON(); }
	destroy() { } // to do: check is this function is still really needed
}

class FaustPolyAudioWorkletNode extends FaustAudioWorkletNode implements FaustAudioPolyNode {

	constructor(context: BaseAudioContext, name: string, options?: AudioWorkletNodeOptions) {
		super(context, name, options);
	}

	keyOn(pitch: number, vel: number) {

	}

	keyOff(pitch: number, velocity: number) { }

	allNotesOff() { }
}

// Code From Shihong

// AudioWorklet Globals
declare class AudioWorkletProcessor {
	public port: MessagePort;
	public process(inputs: Float32Array[][], outputs: Float32Array[][], parameters: { [key: string]: Float32Array }): boolean;
	constructor(options: AudioWorkletNodeOptions);
}
type AudioWorkletProcessorConstructor<T extends AudioWorkletProcessor> = {
	new(options: AudioWorkletNodeOptions): T;
};
declare function registerProcessor<T extends AudioWorkletProcessor>(name: string, constructor: AudioWorkletProcessorConstructor<T>): void;
declare const currentFrame: number;
declare const currentTime: number;
declare const sampleRate: number;
interface AudioParamDescriptor {
	automationRate?: AutomationRate;
	defaultValue?: number;
	maxValue?: number;
	minValue?: number;
	name: string;
}

// Test extending 'AudioWorkletNode'
class FaustAudioWorkletProcessor extends AudioWorkletProcessor {
	constructor(options: AudioWorkletNodeOptions) {
		super(options);
	}

	private midiMessage(data: number[] | Uint8Array) {
		/*
		const cmd = data[0] >> 4;
		const channel = data[0] & 0xf;
		const data1 = data[1];
		const data2 = data[2];
		if (channel === 9) return;
		if (cmd === 8 || (cmd === 9 && data2 === 0)) this.keyOff(channel, data1, data2);
		else if (cmd === 9) this.keyOn(channel, data1, data2);
		else if (cmd === 11) this.ctrlChange(channel, data1, data2);
		else if (cmd === 14) this.pitchWheel(channel, data2 * 128.0 + data1);
		*/
	}

	private handleMessage = (e: MessageEvent) => { // use arrow function for binding
		const msg = e.data;
		// TODO
		//this.cachedEvents.push({ type: e.data.type, data: e.data.data });

		/*
		switch (msg.type) {
			// Generic MIDI message
			case "midi": this.midiMessage(msg.data); break;
			// Typed MIDI message
			case "keyOn": this.keyOn(msg.data[0], msg.data[1], msg.data[2]); break;
			case "keyOff": this.keyOff(msg.data[0], msg.data[1], msg.data[2]); break;
			case "ctrlChange": this.ctrlChange(msg.data[0], msg.data[1], msg.data[2]); break;
			case "pitchWheel": this.pitchWheel(msg.data[0], msg.data[1]); break;
			// Generic data message
			case "param": this.setParamValue(msg.data.path, msg.data.value); break;
			// case "patch": this.onpatch(msg.data); break;
			case "destroy": {
				this.port.close();
				this.fDestroyed = true;
				delete this.fOutputHandler;
				delete this.fComputeHandler;
				break;
			}
			default:
		}
		*/
	}

}

// Test extending 'ScriptProcessorNode'
class FaustScriptProcessorNode extends ScriptProcessorNode implements FaustAudioNode {

	fDSPCode: MonoDSP;

	fInputs: Float32Array[];
	fOutputs: Float32Array[];

	constructor(context: BaseAudioContext, bufferSize?: number) {
		super();
		this.onaudioprocess = (e) => {

			// TODO
			for (let chan = 0; chan < this.fDSPCode.getNumInputs(); chan++) { // Read inputs
				this.fInputs[chan] = e.inputBuffer.getChannelData(chan);
			}
			for (let chan = 0; chan < this.fDSPCode.getNumOutputs(); chan++) { // Read outputs
				this.fOutputs[chan] = e.outputBuffer.getChannelData(chan);
			}

			return this.fDSPCode.compute(this.fInputs, this.fOutputs);
		}

	}

	setOutputParamHandler(handler: OutputParamHandler) { }
	getOutputParamHandler() { return function (path: string, value: number) { } }

	metadata(handler: MetadataHandler) { return function (path: string, value: number) { } }

	ctrlChange(chan: number, ctrl: number, value: number) { this.fDSPCode.ctrlChange(chan, ctrl, value); }
	pitchWheel(chan: number, value: number) { this.fDSPCode.pitchWheel(chan, value); }

	setParamValue(path: string, value: number) { this.fDSPCode.setParamValue(path, value); }
	getParamValue(path: string) { return this.fDSPCode.getParamValue(path); }
	getParams() { return this.fDSPCode.getParams(); }

	getJSON() { return this.fDSPCode.getJSON(); }
	destroy() { } // to do: check is this function is still really needed
}

class FaustPolyScriptProcessorNode extends FaustScriptProcessorNode implements FaustAudioPolyNode {

	constructor(context: BaseAudioContext, bufferSize?: number) {
		super(context, bufferSize);
	}
	keyOn(key: number, vel: number) { }
	keyOff(key: number, vel: number) { }
	allNotesOff() { }
}

class FaustWebAudioNode {

	async compileMonoNode(context: BaseAudioContext, name: string, faust: LibFaust, dsp_content: string, args: string, scriptprocessor: boolean, bufferSize?: number): Promise<FaustAudioNode> {
		return new Faust.Compiler(faust).createDSPFactory("faustdsp", dsp_content, args, false).then(module => {
			return this.createMonoNode(context, name, module, scriptprocessor);
		});
	}

	async compilePolyNode(context: BaseAudioContext, name: string, faust: LibFaust, dsp_content: string, args: string, voices: number, scriptprocessor: boolean, bufferSize?: number): Promise<FaustAudioPolyNode> {
		return new Faust.Compiler(faust).createDSPFactory("faustdsp", dsp_content, args, true).then(module => {
			return this.createPolyNode(context, name, module, voices, scriptprocessor);
		});
	}

	async createMonoNode(context: BaseAudioContext, name: string, module: Faust.Factory, scriptprocessor: boolean, bufferSize?: number): Promise<FaustAudioNode> {
		return new Promise((resolve, reject) => {
			resolve((scriptprocessor) ? new FaustScriptProcessorNode(context, bufferSize) : new FaustAudioWorkletNode(context, name));
			// TODO: reject ?
		});
	}

	async createPolyNode(context: BaseAudioContext, name: string, module: Faust.Factory, voices: number, scriptprocessor: boolean, bufferSize?: number): Promise<FaustAudioPolyNode> {
		return new Promise((resolve, reject) => {
			resolve((scriptprocessor) ? new FaustPolyScriptProcessorNode(context, bufferSize) : new FaustPolyAudioWorkletNode(context, name));
			// TODO: reject ?
		});
	}
}

