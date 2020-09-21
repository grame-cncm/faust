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

	fJSON: {};

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

	//fPitchwheelLabel: Array<string>;
	fPitchwheelLabel: { path: string; min: number; max: number }[];
	fCtrlLabel: { path: string; min: number; max: number }[][];

	fPathTable: { [address: string]: number };

	fDestroyed: boolean;

	constructor() {
		this.fOutputHandler = null;

		this.gPtrSize = 4;
		this.gSampleSize = 4;
		this.fDestroyed = false;

		this.setup();
	}

	// JSON parsing functions
	static parseUI(ui: TFaustUI, obj: AudioParamDescriptor[] | MonoDSPImp, callback: (...args: any[]) => any) {
		for (let i = 0; i < ui.length; i++) {
			this.parseGroup(ui[i], obj, callback);
		}
	}
	static parseGroup(group: TFaustUIGroup, obj: AudioParamDescriptor[] | MonoDSPImp, callback: (...args: any[]) => any) {
		if (group.items) {
			this.parseItems(group.items, obj, callback);
		}
	}
	static parseItems(items: TFaustUIItem[], obj: AudioParamDescriptor[] | MonoDSPImp, callback: (...args: any[]) => any) {
		for (let i = 0; i < items.length; i++) {
			callback(items[i], obj, callback);
		}
	}
	static parseItem(item: TFaustUIItem, obj: AudioParamDescriptor[], callback: (...args: any[]) => any) {
		if (item.type === "vgroup" || item.type === "hgroup" || item.type === "tgroup") {
			this.parseItems(item.items, obj, callback); // callback may not binded to this
		} else if (item.type === "hbargraph" || item.type === "vbargraph") {
			// Nothing
		} else if (item.type === "vslider" || item.type === "hslider" || item.type === "nentry") {
			//if (!faustData.voices || (!item.address.endsWith("/gate") && !item.address.endsWith("/freq") && !item.address.endsWith("/gain"))) {
			if ((!item.address.endsWith("/gate") && !item.address.endsWith("/freq") && !item.address.endsWith("/gain"))) {
				obj.push({ name: item.address, defaultValue: item.init || 0, minValue: item.min || 0, maxValue: item.max || 0 });
			}
		} else if (item.type === "button" || item.type === "checkbox") {
			//if (!faustData.voices || (!item.address.endsWith("/gate") && !item.address.endsWith("/freq") && !item.address.endsWith("/gain"))) {
			if ((!item.address.endsWith("/gate") && !item.address.endsWith("/freq") && !item.address.endsWith("/gain"))) {
				obj.push({ name: item.address, defaultValue: item.init || 0, minValue: 0, maxValue: 1 });
			}
		}
	}
	static parseItem2(item: TFaustUIItem, obj: MonoDSPImp, callback: (...args: any[]) => any) {
		if (item.type === "vgroup" || item.type === "hgroup" || item.type === "tgroup") {
			this.parseItems(item.items, obj, callback); // callback may not binded to this
		} else if (item.type === "hbargraph" || item.type === "vbargraph") {
			// Keep bargraph adresses
			obj.fOutputsItems.push(item.address);
			obj.fPathTable[item.address] = item.index;
		} else if (item.type === "vslider" || item.type === "hslider" || item.type === "button" || item.type === "checkbox" || item.type === "nentry") {
			// Keep inputs adresses
			obj.fInputsItems.push(item.address);
			obj.fPathTable[item.address] = item.index;
			if (!item.meta) return;
			item.meta.forEach((meta) => {
				const { midi } = meta;
				if (!midi) return;
				const strMidi = midi.trim();
				if (strMidi === "pitchwheel") {
					obj.fPitchwheelLabel.push({ path: item.address, min: item.min, max: item.max });
				} else {
					const matched = strMidi.match(/^ctrl\s(\d+)/);
					if (!matched) return;
					obj.fCtrlLabel[parseInt(matched[1])].push({ path: item.address, min: item.min, max: item.max });
				}
			});
		}
	}

	private setupMemory() {

		// Start of DSP memory: Mono DSP is placed first with index 0
		this.fDSP = 0;

		// DSP is placed first with index 0. Audio buffer start at the end of DSP.

		// TODO
		//let audio_ptr = this.fJSON.size;
		let audio_ptr = 0;

		// Setup pointers offset
		this.fAudioInputs = audio_ptr;
		this.fAudioOutputs = this.fAudioInputs + this.fInputs * this.gPtrSize;

		// Prepare WASM memory layout
		let audio_inputs_ptr = this.fAudioOutputs + (this.fOutputs * this.gPtrSize);
		let audio_outputs_ptr = audio_inputs_ptr + (this.fInputs * this.fBufferSize * this.gSampleSize);

		// TODO
		//const HEAP = fInstance.instance.memory;
		const HEAP: any = null;

		let HEAP32 = new Int32Array(HEAP);
		let HEAPF32 = new Float32Array(HEAP);

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

	private compute(inputs: Float32Array[][], outputs: Float32Array[][]) {

		// CHeck DSP state
		if (this.fDestroyed) return false;

		const input = inputs[0];
		const output = outputs[0];

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
		if (input !== undefined) {
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
		if (output !== undefined) {
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
		//this.parseUI(this.dspMeta.ui);
	}

	updateOutputs() { }

	ctrlChange(chan: number, ctrl: number, value: number) { }
	pitchWheel(chan: number, value: number) { }

	setParamValue(path: string, value: number) { }
	getParamValue(path: string) { return 0; }

	getParams() { return new Array<string>(); }


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

	getJSON() { return ""; }
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

	setOutputParamHandler(handler: OutputParamHandler) { }
	getOutputParamHandler() { return function (path: string, value: number) { } }

	metadata(handler: MetadataHandler) { return function (path: string, value: number) { } }

	ctrlChange(chan: number, ctrl: number, value: number) { this.fDSPCode.ctrlChange(chan, ctrl, value); }
	pitchWheel(chan: number, value: number) { this.fDSPCode.pitchWheel(chan, value); }

	setParamValue(path: string, value: number) { this.fDSPCode.setParamValue(path, value); }
	getParamValue(path: string) { return this.fDSPCode.getParamValue(path); }
	getParams() { return this.fDSPCode.getParams(); }


	getJSON() { return ""; }
	destroy() { } // to do: check is this function is still really needed
}

class FaustPolyScriptProcessorNode extends FaustScriptProcessorNode implements FaustAudioPolyNode {

	keyOn(key: number, vel: number) { }
	keyOff(key: number, vel: number) { }
	allNotesOff() { }
}

class FaustWebAudioNode {

	compileMonoNode(context: BaseAudioContext, name: string, faust: LibFaust, dsp_content: string, args: string, scriptprocessor: boolean): Promise<FaustAudioNode> {
		return new Faust.Compiler(faust).createDSPFactory("faustdsp", dsp_content, args, false).then(module => {
			return this.createMonoNode(context, name, module, scriptprocessor);
		});
	}

	compilePolyNode(context: BaseAudioContext, name: string, faust: LibFaust, dsp_content: string, args: string, voices: number, scriptprocessor: boolean): Promise<FaustAudioPolyNode> {
		return new Faust.Compiler(faust).createDSPFactory("faustdsp", dsp_content, args, true).then(module => {
			return this.createPolyNode(context, name, module, voices, scriptprocessor);
		});
	}

	createMonoNode(context: BaseAudioContext, name: string, module: Faust.Factory, scriptprocessor: boolean): Promise<FaustAudioNode> {
		return new Promise((resolve, reject) => {
			resolve((scriptprocessor) ? new FaustScriptProcessorNode() : new FaustAudioWorkletNode(context, name));
			// TODO: reject ?
		});
	}

	createPolyNode(context: BaseAudioContext, name: string, module: Faust.Factory, voices: number, scriptprocessor: boolean): Promise<FaustAudioPolyNode> {
		return new Promise((resolve, reject) => {
			resolve((scriptprocessor) ? new FaustPolyScriptProcessorNode() : new FaustPolyAudioWorkletNode(context, name));
			// TODO: reject ?
		});
	}
}

