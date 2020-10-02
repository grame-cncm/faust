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

namespace Faust {

	// Injected by Faust
	type FaustData = {
		id: string;
		voices: number;
		dspMeta: TFaustJSON;
		effectMeta?: TFaustJSON;
	};
	declare const faustData: FaustData;

	class MonoDSPImp implements Faust.MonoDSP {

		fOutputHandler: Faust.OutputParamHandler;

		fInChannels: Float32Array[];
		fOutChannels: Float32Array[];

		fBufferSize: number;
		gPtrSize: number;
		gSampleSize: number;

		fInstance: Faust.Instance;

		fOutputsTimer: number;
		fInputsItems: string[];
		fOutputsItems: string[];

		fAudioInputs: number;
		fAudioOutputs: number;
		fDSP: number;

		fPitchwheelLabel: { path: string; min: number; max: number }[];
		fCtrlLabel: { path: string; min: number; max: number }[][];
		fPathTable: { [address: string]: number };

		fDestroyed: boolean;

		fJSONObj: TFaustJSON;

		constructor(instance: Faust.Instance, sampleRate: number, bufferSize: number) {
			this.fOutputHandler = null;
			this.fBufferSize = bufferSize;

			this.fInChannels = [];
			this.fOutChannels = [];

			this.fInstance = instance;

			this.gPtrSize = 4;
			this.gSampleSize = 4;

			this.fOutputsTimer = 5;
			this.fInputsItems = [];
			this.fOutputsItems = [];

			this.fPitchwheelLabel = [];
			this.fCtrlLabel = [];
			this.fPathTable = {};

			this.fDestroyed = false;

			// Create JSON object
			this.fJSONObj = JSON.parse(this.fInstance.json);

			// Setup GUI
			this.initUI();

			// Setup WASM memory
			this.initMemory();

			// Init DSP
			this.fInstance.api.init(this.fDSP, sampleRate);
		}

		// Tools
		static remap(v: number, mn0: number, mx0: number, mn1: number, mx1: number) {
			return (v - mn0) / (mx0 - mn0) * (mx1 - mn1) + mn1;
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

		private initMemory() {

			// Start of DSP memory: Mono DSP is placed first with index 0
			this.fDSP = 0;

			// Audio buffer start at the end of DSP
			let audio_ptr = this.fJSONObj.size;

			// Setup pointers offset
			this.fAudioInputs = audio_ptr;
			this.fAudioOutputs = this.fAudioInputs + this.getNumInputs() * this.gPtrSize;

			// Prepare WASM memory layout
			let audio_inputs_ptr = this.fAudioOutputs + this.getNumOutputs() * this.gPtrSize;
			let audio_outputs_ptr = audio_inputs_ptr + this.getNumInputs() * this.fBufferSize * this.gSampleSize;

			const HEAP = this.fInstance.memory.buffer;
			const HEAP32 = new Int32Array(HEAP);
			const HEAPF32 = new Float32Array(HEAP);

			if (this.getNumInputs() > 0) {
				for (let chan = 0; chan < this.getNumInputs(); chan++) {
					HEAP32[(this.fAudioInputs >> 2) + chan] = audio_inputs_ptr + this.fBufferSize * this.gSampleSize * chan;
				}
				// Prepare Ins buffer tables
				const dspInChans = HEAP32.subarray(this.fAudioInputs >> 2, (this.fAudioInputs + this.getNumInputs() * this.gPtrSize) >> 2);
				for (let chan = 0; chan < this.getNumInputs(); chan++) {
					this.fInChannels[chan] = HEAPF32.subarray(dspInChans[chan] >> 2, (dspInChans[chan] + this.fBufferSize * this.gSampleSize) >> 2);
				}
			}
			if (this.getNumOutputs() > 0) {
				for (let chan = 0; chan < this.getNumOutputs(); chan++) {
					HEAP32[(this.fAudioOutputs >> 2) + chan] = audio_outputs_ptr + this.fBufferSize * this.gSampleSize * chan;
				}
				// Prepare Out buffer tables
				const dspOutChans = HEAP32.subarray(this.fAudioOutputs >> 2, (this.fAudioOutputs + this.getNumOutputs() * this.gPtrSize) >> 2);
				for (let chan = 0; chan < this.getNumOutputs(); chan++) {
					this.fOutChannels[chan] = HEAPF32.subarray(dspOutChans[chan] >> 2, (dspOutChans[chan] + this.fBufferSize * this.gSampleSize) >> 2);
				}
			}

			console.log("============== Memory layout ==============");
			console.log("this.fBufferSize: " + this.fBufferSize);
			console.log("this.fJSONObj.size: " + this.fJSONObj.size);
			console.log("this.fAudioInputs: " + this.fAudioInputs);
			console.log("this.fAudioOutputs: " + this.fAudioOutputs);
			console.log("audio_inputs_ptrs: " + audio_inputs_ptr);
			console.log("audio_outputs_ptr: " + audio_outputs_ptr);
			console.log("this.fDSP: " + this.fDSP);
		}

		private initUI() {

			// Parse UI
			let callback = (item: TFaustUIItem) => {
				if (item.type === "hbargraph" || item.type === "vbargraph") {
					// Keep bargraph adresses
					this.fOutputsItems.push(item.address);
					this.fPathTable[item.address] = item.index;
				} else if (item.type === "vslider" || item.type === "hslider" || item.type === "button" || item.type === "checkbox" || item.type === "nentry") {
					// Keep inputs adresses
					this.fInputsItems.push(item.address);
					this.fPathTable[item.address] = item.index;
					// Parse 'midi' metadata
					if (item.meta) {
						item.meta.forEach((meta) => {
							const { midi } = meta;
							if (!midi) return;
							const strMidi = midi.trim();
							if (strMidi === "pitchwheel") {
								this.fPitchwheelLabel.push({ path: item.address, min: item.min, max: item.max });
							} else {
								const matched = strMidi.match(/^ctrl\s(\d+)/);
								if (!matched) return;
								this.fCtrlLabel[parseInt(matched[1])].push({ path: item.address, min: item.min, max: item.max });
							}
						});
					}
				}
			}
			MonoDSPImp.parseUI(this.fJSONObj.ui, callback);
		}

		private updateOutputs() {
			if (this.fOutputsItems.length > 0 && this.fOutputHandler && this.fOutputsTimer-- === 0) {
				this.fOutputsTimer = 5;
				this.fOutputsItems.forEach(item => this.fOutputHandler(item, this.getParamValue(item)));
			}
		}

		compute(input: Float32Array[], output: Float32Array[]) {

			// CHeck DSP state
			if (this.fDestroyed) return false;

			// Check inputs
			if (this.getNumInputs() > 0 && (!input || !input[0] || input[0].length === 0)) {
				// console.log("Process input error");
				return true;
			}

			// Check outputs
			if (this.getNumOutputs() > 0 && (!output || !output[0] || output[0].length === 0)) {
				// console.log("Process output error");
				return true;
			}

			// Copy inputs
			if (input !== undefined) { // TO CHECK
				for (let chan = 0; chan < Math.min(this.getNumInputs(), input.length); ++chan) {
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
				for (let chan = 0; chan < Math.min(this.getNumOutputs(), output.length); chan++) {
					const dspOutput = this.fOutChannels[chan];
					//console.log("output.length ", output.length);
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


		// Public API

		setOutputParamHandler(handler: OutputParamHandler) {
			this.fOutputHandler = handler;
		}
		getOutputParamHandler(): OutputParamHandler {
			return this.fOutputHandler;
		}

		getNumInputs() {
			return this.fInstance.api.getNumInputs(this.fDSP);
		}
		getNumOutputs() {
			return this.fInstance.api.getNumOutputs(this.fDSP);
		}

		midiMessage(data: any) {
			// TODO: node.cachedEvents.push({ data, type: "midi" });

			const cmd = data[0] >> 4;
			const channel = data[0] & 0xf;
			const data1 = data[1];
			const data2 = data[2];
			if (channel === 9) return undefined;
			/*
			if (node.voices) {
				if (cmd === 8 || (cmd === 9 && data2 === 0)) return node.keyOff(channel, data1, data2);
				if (cmd === 9) return node.keyOn(channel, data1, data2);
			}
			*/
			if (cmd === 11) return this.ctrlChange(channel, data1, data2);
			if (cmd === 14) return this.pitchWheel(channel, (data2 * 128.0 + data1));
		};

		ctrlChange(chan: number, ctrl: number, value: number) {
			// TODO: node.cachedEvents.push({ type: "ctrlChange", data: [channel, ctrl, value] });
			/*
			if (ctrl === 123 || ctrl === 120) {
				this.allNotesOff();
			}
			*/
			if (this.fCtrlLabel[ctrl].length) {
				this.fCtrlLabel[ctrl].forEach((ctrl) => {
					const { path } = ctrl;
					this.setParamValue(path, MonoDSPImp.remap(value, 0, 127, ctrl.min, ctrl.max));
					if (this.fOutputHandler) this.fOutputHandler(path, this.getParamValue(path));
				});
			}
		}

		pitchWheel(chan: number, wheel: number) {
			// TODO : node.cachedEvents.push({ type: "pitchWheel", data: [channel, wheel] });
			this.fPitchwheelLabel.forEach((pw) => {
				this.setParamValue(pw.path, MonoDSPImp.remap(wheel, 0, 16383, pw.min, pw.max));
				if (this.fOutputHandler) this.fOutputHandler(pw.path, this.getParamValue(pw.path));
			});
		}

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
	//class FaustAudioWorkletNode extends AudioWorkletNode implements Faust.FaustAudioNode {
	class FaustAudioWorkletNode extends AudioWorkletNode {

		fDSPCode: MonoDSP;

		constructor(context: BaseAudioContext, module: Faust.Factory, name: string, options?: AudioWorkletNodeOptions) {

			// instance has to be create to know DSP inputs/outputs number
			const instance = new Faust.Compiler().createDSPInstance(module);

			super(context, name, options);

			/*
			super(options.audioCtx, options.id, {
				numberOfInputs: options.compiledDsp.dspMeta.inputs > 0 ? 1 : 0,
				numberOfOutputs: options.compiledDsp.dspMeta.outputs > 0 ? 1 : 0,
				channelCount: Math.max(1, options.compiledDsp.dspMeta.inputs),
				outputChannelCount: [options.compiledDsp.dspMeta.outputs],
				channelCountMode: "explicit",
				channelInterpretation: "speakers",
				processorOptions: { id: options.id, voices: options.voices, compiledDsp: options.compiledDsp, mixer32Module: options.mixer32Module }
			});
			*/
		}

		setOutputParamHandler(handler: OutputParamHandler) {
			this.fDSPCode.setOutputParamHandler(handler);
		}
		getOutputParamHandler() { return this.fDSPCode.getOutputParamHandler(); }

		metadata(handler: MetadataHandler) { return function (path: string, value: number) { } }

		ctrlChange(chan: number, ctrl: number, value: number) { this.fDSPCode.ctrlChange(chan, ctrl, value); }
		pitchWheel(chan: number, value: number) { this.fDSPCode.pitchWheel(chan, value); }

		setParamValue(path: string, value: number) { this.fDSPCode.setParamValue(path, value); }
		getParamValue(path: string) { return this.fDSPCode.getParamValue(path); }
		getParams() { return this.fDSPCode.getParams(); }

		getJSON() { return this.fDSPCode.getJSON(); }
		destroy() { } // to do: check is this function is still really needed
	}

	//class FaustPolyAudioWorkletNode extends FaustAudioWorkletNode implements Faust.FaustAudioPolyNode {
	class FaustPolyAudioWorkletNode extends FaustAudioWorkletNode {

		constructor(context: BaseAudioContext, module: Faust.Factory, name: string, options?: AudioWorkletNodeOptions) {
			super(context, module, name, options);
		}

		keyOn(pitch: number, vel: number) {

		}

		keyOff(pitch: number, velocity: number) {

		}

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

	// // Test extending 'AudioWorkletProcessor'
	// class FaustAudioWorkletProcessor extends AudioWorkletProcessor {

	// 	fDSPCode: MonoDSP;

	// 	constructor(options: AudioWorkletNodeOptions) {
	// 		super(options);

	// 		this.fDSPCode = new MonoDSPImp(new Faust.Compiler().createDSPInstance(options.processorOptions.module));
	// 	}

	// 	static get parameterDescriptors() {
	// 		// Analyse JSON to generate AudioParam parameters
	// 		const params = [] as AudioParamDescriptor[];
	// 		// TODO
	// 		/*
	// 		this.parseUI(FaustConst.dspMeta.ui, params, this.parseItem);
	// 		if (FaustConst.effectMeta) this.parseUI(FaustConst.effectMeta.ui, params, this.parseItem);
	// 		*/
	// 		return params;
	// 	}

	// 	process(inputs: Float32Array[][], outputs: Float32Array[][], parameters: { [key: string]: Float32Array }) {

	// 		return this.fDSPCode.compute(inputs[0], outputs[0]);
	// 	}

	// 	private midiMessage(data: number[] | Uint8Array) {
	// 		/*
	// 		const cmd = data[0] >> 4;
	// 		const channel = data[0] & 0xf;
	// 		const data1 = data[1];
	// 		const data2 = data[2];
	// 		if (channel === 9) return;
	// 		if (cmd === 8 || (cmd === 9 && data2 === 0)) this.keyOff(channel, data1, data2);
	// 		else if (cmd === 9) this.keyOn(channel, data1, data2);
	// 		else if (cmd === 11) this.ctrlChange(channel, data1, data2);
	// 		else if (cmd === 14) this.pitchWheel(channel, data2 * 128.0 + data1);
	// 		*/
	// 	}

	// 	private handleMessage = (e: MessageEvent) => { // use arrow function for binding
	// 		const msg = e.data;
	// 		// TODO
	// 		//this.cachedEvents.push({ type: e.data.type, data: e.data.data });

	// 		/*
	// 		switch (msg.type) {
	// 			// Generic MIDI message
	// 			case "midi": this.midiMessage(msg.data); break;
	// 			// Typed MIDI message
	// 			case "keyOn": this.keyOn(msg.data[0], msg.data[1], msg.data[2]); break;
	// 			case "keyOff": this.keyOff(msg.data[0], msg.data[1], msg.data[2]); break;
	// 			case "ctrlChange": this.ctrlChange(msg.data[0], msg.data[1], msg.data[2]); break;
	// 			case "pitchWheel": this.pitchWheel(msg.data[0], msg.data[1]); break;
	// 			// Generic data message
	// 			case "param": this.setParamValue(msg.data.path, msg.data.value); break;
	// 			// case "patch": this.onpatch(msg.data); break;
	// 			case "destroy": {
	// 				this.port.close();
	// 				this.fDestroyed = true;
	// 				delete this.fOutputHandler;
	// 				delete this.fComputeHandler;
	// 				break;
	// 			}
	// 			default:
	// 		}
	// 		*/
	// 	}

	// }

	// Test extending 'ScriptProcessorNode'
	//class FaustScriptProcessorNode implements Faust.FaustAudioNode {
	class FaustWasmScriptProcessorNode {

		fDSPCode: Faust.MonoDSP;

		// Needed for SP
		fInputs: Float32Array[];
		fOutputs: Float32Array[];

		initNode(context: BaseAudioContext, module: Faust.Factory, bufferSize: number) {

			this.fDSPCode = new MonoDSPImp(new Faust.Compiler().createDSPInstance(module), context.sampleRate, bufferSize);

			this.fInputs = new Array(this.fDSPCode.getNumInputs());
			this.fOutputs = new Array(this.fDSPCode.getNumOutputs());

			let node: FaustScriptProcessorNode;
			try {
				node = context.createScriptProcessor(bufferSize, this.fDSPCode.getNumInputs(), this.fDSPCode.getNumOutputs()) as FaustScriptProcessorNode;
			} catch (e) {
				//this.faust.error("Error in createScriptProcessor: " + e.message);
				throw e;
			}

			node.onaudioprocess = (e) => {

				// Read inputs
				for (let chan = 0; chan < this.fDSPCode.getNumInputs(); chan++) {
					this.fInputs[chan] = e.inputBuffer.getChannelData(chan);
				}

				// Read outputs
				for (let chan = 0; chan < this.fDSPCode.getNumOutputs(); chan++) {
					this.fOutputs[chan] = e.outputBuffer.getChannelData(chan);
				}

				return this.fDSPCode.compute(this.fInputs, this.fOutputs);
			}

			// TODO
			node.setOutputParamHandler = (handler: OutputParamHandler) => {
				this.fDSPCode.setOutputParamHandler(handler);
			}

			node.getOutputParamHandler = () => { return this.fDSPCode.getOutputParamHandler(); }

			node.metadata = (handler: Faust.MetadataHandler) => { return function (path: string, value: number) { } }

			node.ctrlChange = (chan: number, ctrl: number, value: number) => { this.fDSPCode.ctrlChange(chan, ctrl, value); }
			node.pitchWheel = (chan: number, value: number) => { this.fDSPCode.pitchWheel(chan, value); }

			node.setParamValue = (path: string, value: number) => { this.fDSPCode.setParamValue(path, value); }
			node.getParamValue = (path: string) => { return this.fDSPCode.getParamValue(path); }
			node.getParams = () => { return this.fDSPCode.getParams(); }

			node.getJSON = () => { return this.fDSPCode.getJSON(); }
			node.destroy = () => { } // to do: check is this function is still really needed

			return node;
		}
	}

	/*
	class FaustWasmPolyScriptProcessorNode extends FaustScriptProcessorNode implements Faust.FaustAudioPolyNode {
		
		constructor(context: BaseAudioContext, module: Faust.Factory, bufferSize?: number) {
			super(context, module, bufferSize);
		}
		keyOn(key: number, vel: number) { }
		keyOff(key: number, vel: number) { }
		allNotesOff() { }
	}
	*/

	export class AudioNodeFactory implements Faust.AudioNodeFactory {

		async compileMonoNode(context: BaseAudioContext, name: string, faust: LibFaust, dsp_content: string, args: string, scriptprocessor: boolean, bufferSize?: number)
			: Promise<Faust.FaustScriptProcessorNode | Faust.FaustAudioWorletNode> {
			return new Faust.Compiler(faust).createDSPFactory("faustdsp", dsp_content, args, false).then(module => {
				return this.createMonoNode(context, name, module, scriptprocessor);
			});
		}

		async compilePolyNode(context: BaseAudioContext, name: string, faust: LibFaust, dsp_content: string, args: string, voices: number, scriptprocessor: boolean, bufferSize?: number)
			: Promise<Faust.FaustScriptProcessorNode | Faust.FaustAudioWorletNode> {
			return new Faust.Compiler(faust).createDSPFactory("faustdsp", dsp_content, args, true).then(module => {
				return this.createPolyNode(context, name, module, voices, scriptprocessor);
			});
		}

		createMonoNode(context: BaseAudioContext, name: string, module: Faust.Factory, scriptprocessor: boolean, bufferSize?: number)
			: Promise<Faust.FaustScriptProcessorNode | Faust.FaustAudioWorletNode> {
			return new Promise((resolve, reject) => {
				resolve(new FaustWasmScriptProcessorNode().initNode(context, module, bufferSize));
				//resolve(new FaustAudioWorkletNode(context, module, name));
				//resolve((scriptprocessor)
				//	? new FaustWasmScriptProcessorNode(module).initNode(context, bufferSize)
				//	: new FaustAudioWorkletNode(context, module, name));
				// TODO: reject ?
			});
		}

		createPolyNode(context: BaseAudioContext, name: string, module: Faust.Factory, voices: number, scriptprocessor: boolean, bufferSize?: number)
			: Promise<Faust.FaustScriptProcessorNode | Faust.FaustAudioWorletNode> {
			return new Promise((resolve, reject) => {
				//resolve((scriptprocessor) ? new FaustPolyScriptProcessorNode(context, module, bufferSize) : new FaustPolyAudioWorkletNode(context, module, name));
				// TODO: reject ?
			});
		}
	}

}
