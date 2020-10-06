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
        dsp_name: string;
        dsp_JSON: string;
        //voices: number;
        //effectMeta?: TFaustJSON;
    };
    declare const faustData: FaustData;

    class BaseDSPImp implements Faust.BaseDSP {

        fOutputHandler: Faust.OutputParamHandler;

        fInChannels: Float32Array[];
        fOutChannels: Float32Array[];

        fOutputsTimer: number;
        fInputsItems: string[];
        fOutputsItems: string[];

        fAudioInputs: number;
        fAudioOutputs: number;
        fDSP: number;

        fBufferSize: number;
        gPtrSize: number;
        gSampleSize: number;

        fPitchwheelLabel: { path: string; min: number; max: number }[];
        fCtrlLabel: { path: string; min: number; max: number }[][];
        fPathTable: { [address: string]: number };

        fDestroyed: boolean;

        fJSONObj: TFaustJSON;

        constructor(bufferSize: number) {
            this.fOutputHandler = null;
            this.fBufferSize = bufferSize;

            this.fInChannels = [];
            this.fOutChannels = [];

            this.gPtrSize = 4;
            this.gSampleSize = 4;

            this.fOutputsTimer = 5;
            this.fInputsItems = [];
            this.fOutputsItems = [];

            this.fPitchwheelLabel = [];
            this.fCtrlLabel = [];
            this.fPathTable = {};

            this.fDestroyed = false;
        }

        // Tools
        static remap(v: number, mn0: number, mx0: number, mn1: number, mx1: number) {
            return (v - mn0) / (mx0 - mn0) * (mx1 - mn1) + mn1;
        }

        // JSON parsing functions
        static parseUI(ui: TFaustUI, callback: (...args: any[]) => any) {
            ui.forEach(group => BaseDSPImp.parseGroup(group, callback));
        }

        static parseGroup(group: TFaustUIGroup, callback: (...args: any[]) => any) {
            if (group.items) {
                BaseDSPImp.parseItems(group.items, callback);
            }
        }
        static parseItems(items: TFaustUIItem[], callback: (...args: any[]) => any) {
            items.forEach(item => BaseDSPImp.parseItem(item, callback));
        }

        static parseItem(item: TFaustUIItem, callback: (...args: any[]) => any) {
            if (item.type === "vgroup" || item.type === "hgroup" || item.type === "tgroup") {
                BaseDSPImp.parseItems(item.items, callback);
            } else {
                callback(item);
            }
        }

        // Public API

        metadata(handler: MetadataHandler) { }

        compute(input: Float32Array[], output: Float32Array[]) {
            return false;
        }

        setOutputParamHandler(handler: OutputParamHandler) {
            this.fOutputHandler = handler;
        }
        getOutputParamHandler(): OutputParamHandler {
            return this.fOutputHandler;
        }

        getNumInputs() {
            return -1;
        }
        getNumOutputs() {
            return -1;
        }

        midiMessage(data: number[] | Uint8Array) {
            // TODO: node.cachedEvents.push({ data, type: "midi" });
            const cmd = data[0] >> 4;
            const channel = data[0] & 0xf;
            const data1 = data[1];
            const data2 = data[2];
            if (cmd === 11) return this.ctrlChange(channel, data1, data2);
            if (cmd === 14) return this.pitchWheel(channel, (data2 * 128.0 + data1));
        };

        ctrlChange(channel: number, ctrl: number, value: number) {
            // TODO: node.cachedEvents.push({ type: "ctrlChange", data: [channel, ctrl, value] });
            if (this.fCtrlLabel[ctrl].length) {
                this.fCtrlLabel[ctrl].forEach((ctrl) => {
                    const { path } = ctrl;
                    this.setParamValue(path, BaseDSPImp.remap(value, 0, 127, ctrl.min, ctrl.max));
                    if (this.fOutputHandler) this.fOutputHandler(path, this.getParamValue(path));
                });
            }
        }

        pitchWheel(channel: number, wheel: number) {
            // TODO : node.cachedEvents.push({ type: "pitchWheel", data: [channel, wheel] });
            this.fPitchwheelLabel.forEach((pw) => {
                this.setParamValue(pw.path, BaseDSPImp.remap(wheel, 0, 16383, pw.min, pw.max));
                if (this.fOutputHandler) this.fOutputHandler(pw.path, this.getParamValue(pw.path));
            });
        }

        setParamValue(path: string, value: number) { }
        getParamValue(path: string) { return 0; }

        getParams() { return this.fInputsItems; }
        getJSON() { return ""; }
        destroy() { this.fDestroyed = true; }
    }

    // Monophonic DSP
    class MonoDSPImp extends BaseDSPImp {

        fInstance: Faust.Instance;

        constructor(instance: Faust.Instance, sampleRate: number, bufferSize: number) {

            super(bufferSize);
            this.fInstance = instance;

            // Create JSON object
            this.fJSONObj = JSON.parse(this.fInstance.json);

            // Setup GUI
            this.initUI();

            // Setup WASM memory
            this.initMemory();

            // Init DSP
            this.fInstance.api.init(this.fDSP, sampleRate);
        }

        protected initMemory() {

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

        protected initUI() {

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
            BaseDSPImp.parseUI(this.fJSONObj.ui, callback);
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
            if (input !== undefined) {
                for (let chan = 0; chan < Math.min(this.getNumInputs(), input.length); ++chan) {
                    const dspInput = this.fInChannels[chan];
                    dspInput.set(input[chan]);
                }
            }

            /*
            // Possibly call an externally given callback (for instance to synchronize playing a MIDIFile...)
            if (this.computeHandler) this.computeHandler(this.bufferSize);
            */

            // Compute
            this.fInstance.api.compute(this.fDSP, this.fBufferSize, this.fAudioInputs, this.fAudioOutputs);

            // Update bargraph
            this.updateOutputs();

            // Copy outputs
            if (output !== undefined) {
                for (let chan = 0; chan < Math.min(this.getNumOutputs(), output.length); chan++) {
                    const dspOutput = this.fOutChannels[chan];
                    output[chan].set(dspOutput);
                }
            }

            // TODO
            /*
            this.port.postMessage({ type: "plot", value: output, index: this.$buffer++, events: this.cachedEvents });
            this.cachedEvents = [];
            */
            return true;
        }

        // Public API

        getNumInputs() {
            return this.fInstance.api.getNumInputs(this.fDSP);
        }
        getNumOutputs() {
            return this.fInstance.api.getNumOutputs(this.fDSP);
        }

        setParamValue(path: string, value: number) {
            this.fInstance.api.setParamValue(this.fDSP, this.fPathTable[path], value);
        }
        getParamValue(path: string) {
            return this.fInstance.api.getParamValue(this.fDSP, this.fPathTable[path]);
        }

        getJSON() { return this.fInstance.json; }
    }

    class DspVoice {
        fLevel: number;

    }

    // Polyphonic DSP
    class PolyDSPImp extends BaseDSPImp {

        fInstance: Faust.PolyInstance;

        fFreqLabel: number[];
        fGateLabel: number[];
        fGainLabel: number[];

        fDSPVoices?: number[];
        fDSPVoicesState?: number[];
        fDSPVoicesLevel?: number[];
        fDSPVoicesDate?: number[];

        kActiveVoice?: number;
        kFreeVoice?: number;
        kReleaseVoice?: number;
        kNoVoice?: number;

        constructor(instance: Faust.PolyInstance, sampleRate: number, bufferSize?: number) {
            super(bufferSize);

            // Create JSON object
            this.fJSONObj = JSON.parse(this.fInstance.voice_json);

            // Setup GUI
            this.initUI();

            // Setup WASM memory
            this.initMemory();

            // Init DSP voices
            // node.dspVoices$.forEach($voice => node.factory.init($voice, sampleRate));
        }

        protected initMemory() {

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

        protected initUI() {

        }

        private getPlayingVoice(pitch: number) {
            return -1;
        }

        private getFreeVoice(pitch: number) {
            return -1;
        }

        // Public API

        compute(input: Float32Array[], output: Float32Array[]) {
            return true;
        }
        getNumInputs() {
            return this.fInstance.voice_api.getNumInputs(this.fDSP);
        }
        getNumOutputs() {
            return this.fInstance.voice_api.getNumOutputs(this.fDSP);
        }

        setParamValue(path: string, value: number) {
            // TODO
            //this.fInstance.voice_api.setParamValue(this.fDSP, this.fPathTable[path], value);
        }
        getParamValue(path: string) {
            // TODO
            //return this.fInstance.voice_api.getParamValue(this.fDSP, this.fPathTable[path]);
            return 0;
        }

        getJSON() {
            // TODO
            //return this.fInstance.json;
            return "";
        }

        midiMessage(data: number[] | Uint8Array) {
            // TODO: node.cachedEvents.push({ data, type: "midi" });
            const cmd = data[0] >> 4;
            const channel = data[0] & 0xf;
            const data1 = data[1];
            const data2 = data[2];
            if (cmd === 8 || (cmd === 9 && data2 === 0)) return this.keyOff(channel, data1, data2);
            else if (cmd === 9) return this.keyOn(channel, data1, data2);
            else super.midiMessage(data);
        };

        ctrlChange(channel: number, ctrl: number, value: number) {
            if (ctrl === 123 || ctrl === 120) {
                this.allNotesOff();
            } else {
                super.ctrlChange(channel, ctrl, value);
            }
        }

        keyOn(channel: number, pitch: number, vel: number) { }
        keyOff(channel: number, pitch: number, velocity: number) { }

        allNotesOff() { }
    };

    // Public API

    // Test extending 'AudioWorkletNode'
    //class FaustAudioWorkletNode extends AudioWorkletNode implements Faust.FaustAudioNode {
    /*
        name is a key for the BaseAudioContext’s node name to parameter descriptor map
    */

    // Common class for Monophonic and Polyphonic AudioWorkletNode
    class FaustAudioWorkletNode extends AudioWorkletNode {

        fDSPCode: BaseDSP;

        constructor(context: BaseAudioContext, name: string, factory: Faust.Factory) {

            // Create JSON object
            const JSONObj = JSON.parse(factory.json);

            // Create proxy FaustAudioWorkletProcessor
            super(context, name, {
                numberOfInputs: JSONObj.inputs > 0 ? 1 : 0,
                numberOfOutputs: JSONObj.outputs > 0 ? 1 : 0,
                channelCount: Math.max(1, JSONObj.inputs),
                outputChannelCount: [JSONObj.outputs],
                channelCountMode: "explicit",
                channelInterpretation: "speakers",
                processorOptions: { name: name, factory: factory }
            });
        }

        // Public API

        setOutputParamHandler(handler: OutputParamHandler) {
            this.fDSPCode.setOutputParamHandler(handler);
        }
        getOutputParamHandler() { return this.fDSPCode.getOutputParamHandler(); }

        getNumInputs() {
            return this.fDSPCode.getNumInputs();
        }
        getNumOutputs() {
            return this.fDSPCode.getNumOutputs();
        }

        compute(inputs: Float32Array[], outputs: Float32Array[]) {
            return this.fDSPCode.compute(inputs, outputs);
        }

        metadata(handler: MetadataHandler) { return function (path: string, value: number) { } }

        midiMessage(data: number[] | Uint8Array): void {
            const cmd = data[0] >> 4;
            const channel = data[0] & 0xf;
            const data1 = data[1];
            const data2 = data[2];
            //if (cmd === 8 || (cmd === 9 && data2 === 0)) this.keyOff(channel, data1, data2);
            //else if (cmd === 9) this.keyOn(channel, data1, data2);
            if (cmd === 11) this.ctrlChange(channel, data1, data2);
            else if (cmd === 14) this.pitchWheel(channel, data2 * 128.0 + data1);
            else this.port.postMessage({ data, type: "midi" });
        }

        ctrlChange(channel: number, ctrl: number, value: number) {
            const e = { type: "ctrlChange", data: [channel, ctrl, value] };
            this.port.postMessage(e);
        }
        pitchWheel(channel: number, wheel: number) {
            const e = { type: "pitchWheel", data: [channel, wheel] };
            this.port.postMessage(e);
        }

        setParamValue(path: string, value: number) {
            //const e = { type: "param", data: { path, value } };
            //this.port.postMessage(e);
            const param = this.parameters.get(path);
            if (param) param.setValueAtTime(value, this.context.currentTime);
        }
        getParamValue(path: string) {
            const param = this.parameters.get(path);
            return (param) ? param.value : 0;
        }

        getParams() { return this.fDSPCode.getParams(); }

        getJSON() { return this.fDSPCode.getJSON(); }

        destroy() {
            this.port.postMessage({ type: "destroy" });
            this.port.close();
        }
    }

    class FaustMonoAudioWorkletNode extends FaustAudioWorkletNode {

        // TODO
        onprocessorerror = (e: ErrorEvent) => {
            //console.error("Error from " + this.dspMeta.name + " AudioWorkletNode: "); // eslint-disable-line no-console
            throw e.error;
        }

        constructor(context: BaseAudioContext, name: string, factory: Faust.Factory) {

            super(context, name, factory);

            this.fDSPCode = new MonoDSPImp(new Faust.Compiler().createDSPInstance(factory), context.sampleRate, 128);

            // Patch it with additional functions
            this.port.onmessage = (e: MessageEvent) => {
                if (e.data.type === "param" && this.fDSPCode.getOutputParamHandler()) {
                    this.fDSPCode.getOutputParamHandler()(e.data.path, e.data.value);
                } else if (e.data.type === "plot") {
                    // TODO 
                    //if (this.plotHandler) this.plotHandler(e.data.value, e.data.index, e.data.events);
                }
            };

            try {
                if (this.parameters) this.parameters.forEach(p => p.automationRate = "k-rate");
            } catch (e) { } // eslint-disable-line no-empty
        }

    }

    //class FaustPolyAudioWorkletNode extends FaustAudioWorkletNode implements Faust.FaustAudioPolyNode {
    class FaustPolyAudioWorkletNode extends FaustAudioWorkletNode {

        // TODO
        onprocessorerror = (e: ErrorEvent) => {
            //console.error("Error from " + this.dspMeta.name + " AudioWorkletNode: "); // eslint-disable-line no-console
            throw e.error;
        }

        constructor(context: BaseAudioContext, name: string, voice_factory: Faust.Factory, mixer_module: WebAssembly.Module, voices: number, effect_factory?: Faust.Factory) {
            super(context, name, voice_factory);

            this.fDSPCode = new PolyDSPImp(
                new Faust.Compiler().createPolyDSPInstance(
                    voice_factory,
                    mixer_module,
                    voices,
                    effect_factory),
                context.sampleRate, 128);
        }

        keyOn(channel: number, key: number, vel: number) {
            (this.fDSPCode as PolyDSPImp).keyOn(channel, key, vel);
        }

        keyOff(channel: number, key: number, vel: number) {
            (this.fDSPCode as PolyDSPImp).keyOff(channel, key, vel);
        }

        allNotesOff() {
            (this.fDSPCode as PolyDSPImp).allNotesOff();
        }
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

    export const FaustAudioWorkletProcessorFactory = () => {

        class FaustConst {
            static dsp_name = faustData.dsp_name;
            static dsp_JSON = faustData.dsp_JSON;
            //static effectMeta = faustData.effectMeta;
        }

        // Common class for Monophonic and Polyphonic AudioWorkletProcessor
        class FaustAudioWorkletProcessor extends AudioWorkletProcessor {

            fDSPCode: BaseDSP;

            constructor(options: AudioWorkletNodeOptions) {
                super(options);

                // Setup port message handling
                this.port.onmessage = this.handleMessage; // Naturally binded with arrow function property
            }

            static get parameterDescriptors() {
                const params = [] as AudioParamDescriptor[];
                // Analyse JSON to generate AudioParam parameters
                let callback = (item: TFaustUIItem) => {
                    if (item.type === "vslider" || item.type === "hslider" || item.type === "nentry") {
                        params.push({ name: item.address, defaultValue: item.init || 0, minValue: item.min || 0, maxValue: item.max || 0 });
                    } else if (item.type === "button" || item.type === "checkbox") {
                        params.push({ name: item.address, defaultValue: item.init || 0, minValue: 0, maxValue: 1 });
                    }
                }
                BaseDSPImp.parseUI(JSON.parse(FaustConst.dsp_JSON).ui, callback);
                /*
                if (FaustConst.effectMeta) this.parseUI(FaustConst.effectMeta.ui, params, this.parseItem);
                */
                console.log(params);
                return params;
            }

            process(inputs: Float32Array[][], outputs: Float32Array[][], parameters: { [key: string]: Float32Array }) {

                // Update controls (possibly needed for sample accurate control)
                for (const path in parameters) {
                    const paramArray = parameters[path];
                    this.fDSPCode.setParamValue(path, paramArray[0]);
                }

                return this.fDSPCode.compute(inputs[0], outputs[0]);
            }

            protected handleMessage = (e: MessageEvent) => { // use arrow function for binding
                const msg = e.data;
                // TODO
                //this.cachedEvents.push({ type: e.data.type, data: e.data.data });

                switch (msg.type) {
                    // Generic MIDI message
                    case "midi": this.midiMessage(msg.data); break;
                    // Typed MIDI message
                    case "ctrlChange": this.ctrlChange(msg.data[0], msg.data[1], msg.data[2]); break;
                    case "pitchWheel": this.pitchWheel(msg.data[0], msg.data[1]); break;
                    // Generic data message
                    case "param": this.fDSPCode.setParamValue(msg.data.path, msg.data.value); break;
                    // case "patch": this.onpatch(msg.data); break;
                    case "destroy": {
                        this.port.close();
                        this.fDSPCode.destroy();
                        // STILL NEEDED ?
                        //delete this.fOutputHandler;
                        //delete this.fComputeHandler;
                        break;
                    }
                    default:
                }
            }

            protected midiMessage(data: number[] | Uint8Array) {
                this.fDSPCode.midiMessage(data);
            }

            protected ctrlChange(channel: number, ctrl: number, value: number) {
                this.fDSPCode.ctrlChange(channel, ctrl, value);
            }

            protected pitchWheel(channel: number, wheel: number) {
                this.fDSPCode.pitchWheel(channel, wheel);
            }
        }

        // Monophonic AudioWorkletProcessor
        class FaustMonoAudioWorkletProcessor extends FaustAudioWorkletProcessor {

            constructor(options: AudioWorkletNodeOptions) {
                super(options);

                // 'sampleRate' is defined in AudioWorkletGlobalScope
                this.fDSPCode = new MonoDSPImp(new Faust.Compiler().createDSPInstance(options.processorOptions.factory), sampleRate, 128);

                // Setup output handler
                this.fDSPCode.setOutputParamHandler((path, value) => this.port.postMessage({ path, value, type: "param" }));
            }
        }

        // Polyphonic AudioWorkletProcessor
        class FaustPolyAudioWorkletProcessor extends FaustAudioWorkletProcessor {

            constructor(options: AudioWorkletNodeOptions) {
                super(options);

                // 'sampleRate' is defined in AudioWorkletGlobalScope
                this.fDSPCode = new PolyDSPImp(
                    new Faust.Compiler().createPolyDSPInstance(
                        options.processorOptions.voice_factory,
                        options.processorOptions.mixer_module,
                        options.processorOptions.voices,
                        options.processorOptions.effect_factory),
                    sampleRate, 128);

                // Setup output handler
                this.fDSPCode.setOutputParamHandler((path, value) => this.port.postMessage({ path, value, type: "param" }));
            }

            protected midiMessage(data: number[] | Uint8Array) {
                const cmd = data[0] >> 4;
                const channel = data[0] & 0xf;
                const data1 = data[1];
                const data2 = data[2];
                if (cmd === 8 || (cmd === 9 && data2 === 0)) this.keyOff(channel, data1, data2);
                else if (cmd === 9) this.keyOn(channel, data1, data2);
                else super.midiMessage(data);
            }

            protected handleMessage = (e: MessageEvent) => { // use arrow function for binding
                const msg = e.data;
                // TODO
                //this.cachedEvents.push({ type: e.data.type, data: e.data.data });

                switch (msg.type) {
                    case "keyOn": this.keyOn(msg.data[0], msg.data[1], msg.data[2]); break;
                    case "keyOff": this.keyOff(msg.data[0], msg.data[1], msg.data[2]); break;
                    default:
                        super.handleMessage(e);
                        break
                }
            }

            keyOn(channel: number, key: number, vel: number) {
                (this.fDSPCode as PolyDSPImp).keyOn(channel, key, vel);
            }

            keyOff(channel: number, key: number, vel: number) {
                (this.fDSPCode as PolyDSPImp).keyOff(channel, key, vel);
            }

            allNotesOff() {
                (this.fDSPCode as PolyDSPImp).allNotesOff();
            }
        }

        // Synchronously compile and instantiate the WASM module
        registerProcessor(FaustConst.dsp_name || "mydsp", FaustMonoAudioWorkletProcessor);
        registerProcessor(FaustConst.dsp_name + "_poly" || "mydsp_poly", FaustPolyAudioWorkletProcessor);
    }

    // Test extending 'ScriptProcessorNode'
    //class FaustScriptProcessorNode implements Faust.FaustAudioNode {

    // Common class for Monophonic and Polyphonic ScriptProcessorNode
    class FaustWasmScriptProcessorNode {

        fDSPCode: Faust.BaseDSP;

        // Needed for SP
        fInputs: Float32Array[];
        fOutputs: Float32Array[];

        protected setupNode(node: FaustScriptProcessorNode) {

            this.fInputs = new Array(this.fDSPCode.getNumInputs());
            this.fOutputs = new Array(this.fDSPCode.getNumOutputs());

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

            // Public API

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
            node.destroy = () => { this.fDSPCode.destroy(); }
        }
    }

    class FaustWasmMonoScriptProcessorNode extends FaustWasmScriptProcessorNode {

        initMonoNode(context: BaseAudioContext, factory: Faust.Factory, bufferSize: number) {

            this.fDSPCode = new MonoDSPImp(new Faust.Compiler().createDSPInstance(factory), context.sampleRate, bufferSize);

            let node: FaustScriptProcessorNode;
            try {
                node = context.createScriptProcessor(bufferSize, this.fDSPCode.getNumInputs(), this.fDSPCode.getNumOutputs()) as FaustScriptProcessorNode;
            } catch (e) {
                //this.faust.error("Error in createScriptProcessor: " + e.message);
                throw e;
            }

            this.setupNode(node);
            return node;
        }
    }

    class FaustWasmPolyScriptProcessorNode extends FaustWasmScriptProcessorNode {

        initPolyNode(context: BaseAudioContext, voice_factory: Faust.Factory, mixer_module: WebAssembly.Module, voices: number, bufferSize: number, effect_factory?: Factory) {
            this.fDSPCode = new PolyDSPImp(new Faust.Compiler().createPolyDSPInstance(
                voice_factory,
                mixer_module,
                voices,
                effect_factory),
                context.sampleRate, bufferSize);

            let node: FaustPolyScriptProcessorNode;
            try {
                node = context.createScriptProcessor(bufferSize, this.fDSPCode.getNumInputs(), this.fDSPCode.getNumOutputs()) as FaustPolyScriptProcessorNode;
            } catch (e) {
                //this.faust.error("Error in createScriptProcessor: " + e.message);
                throw e;
            }

            this.setupNode(node);
            return node;
        }

        keyOn(channel: number, key: number, vel: number) {
            (this.fDSPCode as PolyDSPImp).keyOn(channel, key, vel);
        }

        keyOff(channel: number, key: number, vel: number) {
            (this.fDSPCode as PolyDSPImp).keyOff(channel, key, vel);
        }

        allNotesOff() {
            (this.fDSPCode as PolyDSPImp).allNotesOff();
        }
    }

    export class AudioNodeFactory implements Faust.AudioNodeFactory {

        // Table of all create WorkletProcessors, each of them has to stay unique
        private fWorkletProcessors: string[] = [];

        async compileMonoNode(context: BaseAudioContext, name: string, faust: LibFaust, dsp_content: string, args: string, scriptprocessor: boolean, bufferSize?: number)
            : Promise<Faust.FaustScriptProcessorNode | Faust.FaustAudioWorkletNode> {
            return new Faust.Compiler(faust).createDSPFactory("faustdsp", dsp_content, args, false).then(factory => {
                return this.createMonoNode(context, name, factory, scriptprocessor);
            });
        }

        // We assume that 'dsp_content' contains an integrated effect
        // TODO
        // - extract separated voice and effect code from 'dsp_content'
        // - create voice and effect factories
        async compilePolyNode(context: BaseAudioContext, name: string, faust: LibFaust, dsp_content: string, args: string, voices: number, scriptprocessor: boolean, bufferSize?: number)
            : Promise<Faust.FaustPolyScriptProcessorNode | Faust.FaustPolyAudioWorkletNode> {
            /*
            return new Faust.Compiler(faust).createDSPFactory("faustdsp", dsp_content, args, true).then(factory => {
                return this.createPolyNode(context, name, factory, voices, scriptprocessor);
            });
            */
            return null;
        }

        createMonoNode(context: BaseAudioContext, name: string, factory: Faust.Factory, scriptprocessor: boolean, bufferSize?: number)
            : Promise<Faust.FaustScriptProcessorNode | Faust.FaustAudioWorkletNode> {
            return new Promise((resolve, reject) => {
                if (scriptprocessor) {
                    resolve(new FaustWasmMonoScriptProcessorNode().initMonoNode(context, factory, bufferSize));
                } else if (this.fWorkletProcessors.indexOf(name) === -1) {

                    // Dynamically create Mono AudioWorkletProcessor code
                    const processor_code = `
                            // Create a Faust namespace
                            var Faust = {};
                            const faustData = { dsp_name: "${name}", dsp_JSON: '${factory.json}' };
                            ${BaseDSPImp.toString()}
                            ${MonoDSPImp.toString()}
                            ${Faust.Compiler.toString()} ${Faust.InstanceAPIImpl.toString()} 
                            (${FaustAudioWorkletProcessorFactory.toString()})();           
                            Faust.Compiler = Compiler;
                            `;

                    const url = window.URL.createObjectURL(new Blob([processor_code], { type: "text/javascript" }));
                    //console.log(processor_code);
                    //console.log(url);

                    // Keep the DSP name
                    this.fWorkletProcessors.push(name);

                    try {
                        context.audioWorklet.addModule(url).then(() => {
                            resolve(new FaustMonoAudioWorkletNode(context, name, factory));
                        });

                        /*
                        // FOR TEST
                        context.audioWorklet.addModule('test.js').then(() => {
                            console.log("SUCCESS");
                            const node = new FaustAudioWorkletNode(context, name, factory);
                            console.log(node);
                            resolve(node);
                        });
                        */

                    } catch (e) {
                        console.log("FAILURE");
                        console.log(e);
                        reject(e);
                    }
                } else {
                    resolve(new FaustMonoAudioWorkletNode(context, name, factory));
                }
            });
        }

        createPolyNode(context: BaseAudioContext, name: string, voice_factory: Faust.Factory, mixer_module: WebAssembly.Module, voices: number, scriptprocessor: boolean, bufferSize?: number, effect_factory?: Factory)
            : Promise<Faust.FaustPolyScriptProcessorNode | Faust.FaustPolyAudioWorkletNode> {
            return new Promise((resolve, reject) => {
                if (scriptprocessor) {
                    resolve(new FaustWasmPolyScriptProcessorNode().initPolyNode(context, voice_factory, mixer_module, voices, bufferSize, effect_factory));
                } else if (this.fWorkletProcessors.indexOf(name) === -1) {
                    // Dynamically create Poly AudioWorkletProcessor code
                    const processor_code = `
                            // Create a Faust namespace
                            var Faust = {};
                            const faustData = { dsp_name: "${name}", dsp_JSON: '${voice_factory.json}' };
                            ${BaseDSPImp.toString()}
                            ${PolyDSPImp.toString()}
                            ${Faust.Compiler.toString()} ${Faust.InstanceAPIImpl.toString()} 
                            (${FaustAudioWorkletProcessorFactory.toString()})();           
                            Faust.Compiler = Compiler;
                            `;

                    const url = window.URL.createObjectURL(new Blob([processor_code], { type: "text/javascript" }));
                    //console.log(processor_code);
                    //console.log(url);

                    // Keep the DSP name
                    this.fWorkletProcessors.push(name);

                    /*
                    try {
                        context.audioWorklet.addModule(url).then(() => {
                            resolve(new FaustMonoAudioWorkletNode(context, name, factory));
                        });

                    } catch (e) {
                        console.log("FAILURE");
                        console.log(e);
                        reject(e);
                    }
                    */
                } else {

                }
                //resolve((scriptprocessor) ? new FaustPolyScriptProcessorNode(context, factory, bufferSize) : new FaustPolyAudioWorkletNode(context, factory, name));
                // TODO: reject ?
            });
        }
    }

}
