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
///<reference path="FaustGenerator.ts"/>
///<reference path="FaustWebAudio.d.ts"/>

namespace Faust {

    // Injected by Faust
    type FaustData = {
        dsp_name: string;
        dsp_JSON: string;
        effect_JSON: string;
    };
    declare const faustData: FaustData;

    class BaseDSPImp implements Faust.BaseDSP {

        protected fOutputHandler: Faust.OutputParamHandler;

        protected fInChannels: Float32Array[];
        protected fOutChannels: Float32Array[];

        protected fOutputsTimer: number;
        protected fInputsItems: string[];
        protected fOutputsItems: string[];

        // Buffers in wasm memory
        protected fAudioInputs: AudioBuffer;
        protected fAudioOutputs: AudioBuffer;

        protected fBufferSize: number;
        protected gPtrSize: number;
        protected gSampleSize: number;

        protected fPitchwheelLabel: { path: string; min: number; max: number }[];
        protected fCtrlLabel: { path: string; min: number; max: number }[][];
        protected fPathTable: { [address: string]: number };
        protected fUICallback: UIHandler;

        protected fDestroyed: boolean;

        protected fJSONDsp: TFaustJSON;

        constructor(buffer_size: number) {
            this.fOutputHandler = null;
            this.fBufferSize = buffer_size;

            this.fInChannels = [];
            this.fOutChannels = [];

            this.gPtrSize = 4;
            this.gSampleSize = 4;

            this.fOutputsTimer = 5;
            this.fInputsItems = [];
            this.fOutputsItems = [];

            this.fPitchwheelLabel = [];
            this.fCtrlLabel = new Array(128).fill(null).map(() => []);
            this.fPathTable = {};

            this.fDestroyed = false;

            this.fUICallback = (item: TFaustUIItem) => {
                if (item.type === "hbargraph" || item.type === "vbargraph") {
                    // Keep bargraph adresses
                    this.fOutputsItems.push(item.address);
                    this.fPathTable[item.address] = item.index;
                } else if (item.type === "vslider" || item.type === "hslider" || item.type === "button" || item.type === "checkbox" || item.type === "nentry") {
                    // Keep inputs adresses
                    this.fInputsItems.push(item.address);
                    this.fPathTable[item.address] = item.index;
                    // Parse 'midi' metadata
                    if (!item.meta) return
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

        protected updateOutputs() {
            if (this.fOutputsItems.length > 0 && this.fOutputHandler && this.fOutputsTimer-- === 0) {
                this.fOutputsTimer = 5;
                this.fOutputsItems.forEach(item => this.fOutputHandler(item, this.getParamValue(item)));
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

        private fInstance: Faust.Instance;
        private fDSP: DSP;

        constructor(instance: Faust.Instance, sample_rate: number, buffer_size: number) {

            super(buffer_size);
            this.fInstance = instance;

            // Create JSON object
            this.fJSONDsp = JSON.parse(this.fInstance.json);

            // Setup GUI
            BaseDSPImp.parseUI(this.fJSONDsp.ui, this.fUICallback);

            // Setup wasm memory
            this.initMemory();

            // Init DSP
            this.fInstance.api.init(this.fDSP, sample_rate);
        }

        private initMemory() {

            // Start of DSP memory: Mono DSP is placed first with index 0
            this.fDSP = 0;

            // Audio buffer start at the end of DSP
            let audio_ptr = this.fJSONDsp.size;

            // Setup pointers offset
            this.fAudioInputs = audio_ptr;
            this.fAudioOutputs = this.fAudioInputs + this.getNumInputs() * this.gPtrSize;

            // Prepare wasm memory layout
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

            console.log("============== Mono Memory layout ==============");
            console.log("this.fBufferSize: " + this.fBufferSize);
            console.log("this.fJSONDsp.size: " + this.fJSONDsp.size);
            console.log("this.fAudioInputs: " + this.fAudioInputs);
            console.log("this.fAudioOutputs: " + this.fAudioOutputs);
            console.log("audio_inputs_ptrs: " + audio_inputs_ptr);
            console.log("audio_outputs_ptr: " + audio_outputs_ptr);
            console.log("this.fDSP: " + this.fDSP);
        }

        // Public API
        compute(input: Float32Array[], output: Float32Array[]) {

            // Check DSP state
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

    // Voice management
    class DspVoice {
        static kActiveVoice: number;
        static kFreeVoice: number;
        static kReleaseVoice: number;
        static kNoVoice: number;
        fNote: number;
        fDate: number;
        private fFreqLabel: number[];
        private fGateLabel: number[];
        private fGainLabel: number[];
        private fDSP: DSP;               // Voice DSP location in wasm memory
        private fAPI: Faust.InstanceAPI; // Voice DSP code

        constructor(dsp: DSP,
            api: Faust.InstanceAPI,
            input_items: string[],
            path_table: { [address: string]: number },
            sample_rate: number) {
            // Voice state
            DspVoice.kActiveVoice = 0;
            DspVoice.kFreeVoice = -1;
            DspVoice.kReleaseVoice = -2;
            DspVoice.kNoVoice = -3;
            this.fNote = DspVoice.kFreeVoice;
            this.fDate = 0;
            this.fDSP = dsp;
            this.fAPI = api;
            this.fGateLabel = [];
            this.fGainLabel = [];
            this.fFreqLabel = [];
            this.fAPI.init(this.fDSP, sample_rate);
            this.extractPaths(input_items, path_table);
        }

        static midiToFreq(note: number) { return 440.0 * 2 ** ((note - 69) / 12) };

        private extractPaths(input_items: string[], path_table: { [address: string]: number }) {
            input_items.forEach((item) => {
                if (item.endsWith("/gate")) this.fGateLabel.push(path_table[item]);
                else if (item.endsWith("/freq")) this.fFreqLabel.push(path_table[item]);
                else if (item.endsWith("/gain")) this.fGainLabel.push(path_table[item]);
            });
        }

        // Public API
        keyOn(pitch: number, velocity: number) {
            this.fAPI.instanceClear(this.fDSP);
            this.fFreqLabel.forEach(index => this.fAPI.setParamValue(this.fDSP, index, DspVoice.midiToFreq(pitch)));
            this.fGateLabel.forEach(index => this.fAPI.setParamValue(this.fDSP, index, 1));
            this.fGainLabel.forEach(index => this.fAPI.setParamValue(this.fDSP, index, velocity / 127));
        }

        keyOff(hard: boolean = false) {
            this.fGateLabel.forEach(index => this.fAPI.setParamValue(this.fDSP, index, 0));
            if (hard) {
                this.fNote = DspVoice.kFreeVoice;
            } else {
                this.fNote = DspVoice.kReleaseVoice;
            }
        }

        compute(buffer_size: number, inputs: AudioBuffer, outputs: AudioBuffer) {
            this.fAPI.compute(this.fDSP, buffer_size, inputs, outputs);
        }

        setParamValue(index: number, value: number) {
            this.fAPI.setParamValue(this.fDSP, index, value);
        }
        getParamValue(index: number) {
            return this.fAPI.getParamValue(this.fDSP, index);
        }
    }

    // Polyphonic DSP
    class PolyDSPImp extends BaseDSPImp {

        private fInstance: Faust.PolyInstance;
        private fEffect: DSP;
        private fJSONEffect: TFaustJSON;
        private fAudioMixing: AudioBuffer;
        private fVoiceTable: DspVoice[];

        constructor(instance: Faust.PolyInstance, sample_rate: number, buffer_size?: number) {
            super(buffer_size);
            this.fInstance = instance;

            // Create JSON for voice
            this.fJSONDsp = JSON.parse(this.fInstance.voice_json);

            // Create JSON for effect
            this.fJSONEffect = (this.fInstance.effect_api) ? JSON.parse(this.fInstance.effect_json) : null;

            // Setup GUI
            BaseDSPImp.parseUI(this.fJSONDsp.ui, this.fUICallback);
            if (this.fJSONEffect) BaseDSPImp.parseUI(this.fJSONEffect.ui, this.fUICallback);

            // Setup wasm memory
            this.initMemory();

            // Init DSP voices
            this.fVoiceTable = [];
            for (let voice = 0; voice < this.fInstance.voices; voice++) {
                this.fVoiceTable.push(new DspVoice(
                    this.fJSONDsp.size * voice,
                    this.fInstance.voice_api,
                    this.fInputsItems,
                    this.fPathTable,
                    sample_rate));
            }

            // Init effect
            if (this.fInstance.effect_api) this.fInstance.effect_api.init(this.fEffect, sample_rate);
        }

        private initMemory() {

            // Effet start at the end of all DSP voices
            this.fEffect = this.fJSONDsp.size * this.fInstance.voices;

            // Audio buffer start at the end of effect
            let audio_ptr = this.fEffect + ((this.fJSONEffect) ? this.fJSONEffect.size : 0);

            // Setup pointers offset
            this.fAudioInputs = audio_ptr;
            this.fAudioOutputs = this.fAudioInputs + this.getNumInputs() * this.gPtrSize;
            this.fAudioMixing = this.fAudioOutputs + this.getNumOutputs() * this.gPtrSize;

            // Prepare wasm memory layout
            let audio_inputs_ptr = this.fAudioMixing + this.getNumOutputs() * this.gPtrSize;
            let audio_outputs_ptr = audio_inputs_ptr + this.getNumInputs() * this.fBufferSize * this.gSampleSize;
            let audio_mixing_ptr = audio_outputs_ptr + this.getNumOutputs() * this.fBufferSize * this.gSampleSize;

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
                    HEAP32[(this.fAudioMixing >> 2) + chan] = audio_mixing_ptr + this.fBufferSize * this.gSampleSize * chan;
                }
                // Prepare Out buffer tables
                const dspOutChans = HEAP32.subarray(this.fAudioOutputs >> 2, (this.fAudioOutputs + this.getNumOutputs() * this.gPtrSize) >> 2);
                for (let chan = 0; chan < this.getNumOutputs(); chan++) {
                    this.fOutChannels[chan] = HEAPF32.subarray(dspOutChans[chan] >> 2, (dspOutChans[chan] + this.fBufferSize * this.gSampleSize) >> 2);
                }
            }

            console.log("============== Poly Memory layout ==============");
            console.log("this.fBufferSize: " + this.fBufferSize);
            console.log("this.fJSONDsp.size: " + this.fJSONDsp.size);
            console.log("this.fAudioInputs: " + this.fAudioInputs);
            console.log("this.fAudioOutputs: " + this.fAudioOutputs);
            console.log("this.fAudioMixing: " + this.fAudioMixing);
            console.log("audio_inputs_ptrs: " + audio_inputs_ptr);
            console.log("audio_outputs_ptr: " + audio_outputs_ptr);
            console.log("audio_mixing_ptr: " + audio_mixing_ptr);
        }

        private allocVoice(voice: number) {
            this.fVoiceTable[voice].fDate++;
            this.fVoiceTable[voice].fNote = DspVoice.kActiveVoice;
            return voice;
        };

        private getPlayingVoice(pitch: number) {
            let playing_voice = DspVoice.kNoVoice;
            let oldest_date_playing = Number.MAX_VALUE;

            for (let voice = 0; voice < this.fInstance.voices; voice++) {
                if (this.fVoiceTable[voice].fNote === pitch) {
                    // Keeps oldest playing voice
                    if (this.fVoiceTable[voice].fDate < oldest_date_playing) {
                        oldest_date_playing = this.fVoiceTable[voice].fDate;
                        playing_voice = voice;
                    }
                }
            }
            return playing_voice;
        }

        private getFreeVoice() {
            for (let voice = 0; voice < this.fInstance.voices; voice++) {
                if (this.fVoiceTable[voice].fNote === DspVoice.kFreeVoice) return this.allocVoice(voice);
            }

            let voice_release = DspVoice.kNoVoice;
            let voice_playing = DspVoice.kNoVoice;
            let oldest_date_release = Number.MAX_VALUE;
            let oldest_date_playing = Number.MAX_VALUE;

            for (let voice = 0; voice < this.fInstance.voices; voice++) { // Scan all voices
                // Try to steal a voice in DspVoice.kReleaseVoice mode...
                if (this.fVoiceTable[voice].fNote === DspVoice.kReleaseVoice) {
                    // Keeps oldest release voice
                    if (this.fVoiceTable[voice].fDate < oldest_date_release) {
                        oldest_date_release = this.fVoiceTable[voice].fDate;
                        voice_release = voice;
                    }
                } else if (this.fVoiceTable[voice].fDate < oldest_date_playing) {
                    oldest_date_playing = this.fVoiceTable[voice].fDate;
                    voice_playing = voice;
                }
            }
            // Then decide which one to steal
            if (oldest_date_release !== Number.MAX_VALUE) {
                console.log(`Steal release voice : voice_date = ${this.fVoiceTable[voice_release].fDate} voice = ${voice_release}`);
                return this.allocVoice(voice_release);
            }
            if (oldest_date_playing !== Number.MAX_VALUE) {
                console.log(`Steal playing voice : voice_date = ${this.fVoiceTable[voice_playing].fDate} voice = ${voice_playing}`);
                return this.allocVoice(voice_playing);
            }
            return DspVoice.kNoVoice;
        }

        // Public API
        compute(input: Float32Array[], output: Float32Array[]) {
            // Check DSP state
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
            this.fInstance.mixer_api.clearOutput(this.fBufferSize, this.getNumOutputs(), this.fAudioOutputs);
            this.fVoiceTable.forEach(voice => {
                voice.compute(this.fBufferSize, this.fAudioInputs, this.fAudioMixing);
                this.fInstance.mixer_api.mixVoice(this.fBufferSize, this.getNumOutputs(), this.fAudioMixing, this.fAudioOutputs);
            });
            if (this.fInstance.effect_api) this.fInstance.effect_api.compute(this.fEffect, this.fBufferSize, this.fAudioOutputs, this.fAudioOutputs);

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
        getNumInputs() {
            return this.fInstance.voice_api.getNumInputs(0);
        }
        getNumOutputs() {
            return this.fInstance.voice_api.getNumOutputs(0);
        }

        private static findPath(o: any, p: string) {
            if (typeof o !== "object") {
                return false;
            } else if (o.address) {
                return (o.address === p);
            } else {
                for (const k in o) {
                    if (PolyDSPImp.findPath(o[k], p)) return true;
                }
                return false;
            }
        }

        setParamValue(path: string, value: number) {
            // TODO:  node.cachedEvents.push({ type: "param", data: { path, value } });
            if (this.fJSONEffect && PolyDSPImp.findPath(this.fJSONEffect.ui, path)) {
                this.fInstance.effect_api.setParamValue(this.fEffect, this.fPathTable[path], value);
            } else {
                this.fVoiceTable.forEach(voice => { voice.setParamValue(this.fPathTable[path], value); });
            }
        }
        getParamValue(path: string) {
            if (this.fJSONEffect && PolyDSPImp.findPath(this.fJSONEffect.ui, path)) {
                return this.fInstance.effect_api.getParamValue(this.fEffect, this.fPathTable[path]);
            } else {
                return this.fVoiceTable[0].getParamValue(this.fPathTable[path]);
            }
        }

        getJSON() {
            const o = this.fJSONDsp;
            const e = this.fJSONEffect;
            const r = { ...o };
            if (e) {
                r.ui = [{
                    type: "tgroup", label: "Sequencer", items: [
                        { type: "vgroup", label: "Instrument", items: o.ui },
                        { type: "vgroup", label: "Effect", items: e.ui }
                    ]
                }];
            } else {
                r.ui = [{
                    type: "tgroup", label: "Polyphonic", items: [
                        { type: "vgroup", label: "Voices", items: o.ui }
                    ]
                }];
            }
            return JSON.stringify(r);
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

        keyOn(channel: number, pitch: number, velocity: number) {
            let voice = this.getFreeVoice();
            this.fVoiceTable[voice].keyOn(pitch, velocity);
        }

        keyOff(channel: number, pitch: number, velocity: number) {
            let voice = this.getPlayingVoice(pitch);
            if (voice !== DspVoice.kNoVoice) {
                this.fVoiceTable[voice].keyOff();
            } else {
                console.log("Playing pitch = %d not found\n", pitch);
            }
        }

        allNotesOff(hard: boolean = false) {
            this.fVoiceTable.forEach(voice => voice.keyOff(hard));
        }
    };

    // Common class for Monophonic and Polyphonic AudioWorkletNode
    class FaustAudioWorkletNode extends AudioWorkletNode {

        protected fJSONDsp: TFaustJSON;
        protected fInputsItems: string[];
        protected fJSON: string;
        protected fOutputHandler: Faust.OutputParamHandler;

        constructor(context: BaseAudioContext, name: string, factory: Faust.Factory, options: any) {

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
                processorOptions: options
            });

            this.fJSONDsp = JSONObj;
            this.fJSON = factory.json;

            // Parse UI
            this.fInputsItems = [];
            let callback = (item: TFaustUIItem) => {
                if (item.type === "vslider" || item.type === "hslider" || item.type === "button" || item.type === "checkbox" || item.type === "nentry") {
                    // Keep inputs adresses
                    this.fInputsItems.push(item.address);
                }
            }
            BaseDSPImp.parseUI(this.fJSONDsp.ui, callback);

            // Patch it with additional functions
            this.port.onmessage = (e: MessageEvent) => {
                if (e.data.type === "param" && this.fOutputHandler) {
                    this.fOutputHandler(e.data.path, e.data.value);
                } else if (e.data.type === "plot") {
                    // TODO
                    //if (this.plotHandler) this.plotHandler(e.data.value, e.data.index, e.data.events);
                }
            };
        }

        // Public API
        setOutputParamHandler(handler: OutputParamHandler) {
            this.fOutputHandler = handler;
        }
        getOutputParamHandler() {
            return this.fOutputHandler;
        }

        getNumInputs() {
            return this.fJSONDsp.inputs;
        }
        getNumOutputs() {
            return this.fJSONDsp.outputs;
        }

        // Not used
        compute(inputs: Float32Array[], outputs: Float32Array[]) {
            return false;
        }

        metadata(handler: MetadataHandler) { return function (path: string, value: number) { } }

        midiMessage(data: number[] | Uint8Array): void {
            const cmd = data[0] >> 4;
            const channel = data[0] & 0xf;
            const data1 = data[1];
            const data2 = data[2];
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
            const e = { type: "param", data: { path, value } };
            this.port.postMessage(e);
            // Set value on AudioParam (but this is not used on Processor side for now)
            const param = this.parameters.get(path);
            if (param) param.setValueAtTime(value, this.context.currentTime);

        }
        getParamValue(path: string) {
            // Get value of AudioParam
            const param = this.parameters.get(path);
            return (param) ? param.value : 0;
        }

        getParams() {
            return this.fInputsItems;
        }
        getJSON() {
            return this.fJSON;
        }

        destroy() {
            this.port.postMessage({ type: "destroy" });
            this.port.close();
        }
    }

    // Monophonic AudioWorkletNode 
    class FaustMonoAudioWorkletNode extends FaustAudioWorkletNode {

        onprocessorerror = (e: ErrorEvent) => {
            console.error("Error from " + this.fJSONDsp.name + " FaustMonoAudioWorkletNode");
            throw e.error;
        }

        constructor(context: BaseAudioContext, name: string, factory: Faust.Factory) {
            super(context, name, factory, { name: name, factory: factory });
        }
    }

    // Polyphonic AudioWorkletNode 
    class FaustPolyAudioWorkletNode extends FaustAudioWorkletNode {

        onprocessorerror = (e: ErrorEvent) => {
            console.error("Error from " + this.fJSONDsp.name + " FaustPolyAudioWorkletNode");
            throw e.error;
        }

        constructor(context: BaseAudioContext, name: string,
            voice_factory: Faust.Factory,
            mixer_module: WebAssembly.Module,
            voices: number,
            effect_factory?: Faust.Factory) {
            super(context, name, voice_factory,
                {
                    name: name,
                    voice_factory: voice_factory,
                    mixer_module: mixer_module,
                    voices: voices,
                    effect_factory: effect_factory
                });
        }

        // Public API
        keyOn(channel: number, pitch: number, velocity: number) {
            const e = { type: "keyOn", data: [channel, pitch, velocity] };
            this.port.postMessage(e);
        }

        keyOff(channel: number, pitch: number, velocity: number) {
            const e = { type: "keyOff", data: [channel, pitch, velocity] };
            this.port.postMessage(e);
        }

        allNotesOff() {
            const e = { type: "ctrlChange", data: [0, 123, 0] };
            this.port.postMessage(e);
        }
    }

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

    export const FaustAudioWorkletProcessorGenerator = () => {

        class FaustConst {
            static dsp_name = faustData.dsp_name;
            static dsp_JSON = faustData.dsp_JSON;
            static effect_JSON = faustData.effect_JSON;
        }

        // Common class for Monophonic and Polyphonic AudioWorkletProcessor
        class FaustAudioWorkletProcessor extends AudioWorkletProcessor {

            protected fDSPCode: BaseDSP;

            constructor(options: AudioWorkletNodeOptions) {
                super(options);

                // Setup port message handling
                this.port.onmessage = this.handleMessage; // Naturally binded with arrow function property
            }

            static get parameterDescriptors() {
                const params = [] as AudioParamDescriptor[];
                // Analyse voice JSON to generate AudioParam parameters
                let callback = (item: TFaustUIItem) => {
                    if (item.type === "vslider" || item.type === "hslider" || item.type === "nentry") {
                        params.push({ name: item.address, defaultValue: item.init || 0, minValue: item.min || 0, maxValue: item.max || 0 });
                    } else if (item.type === "button" || item.type === "checkbox") {
                        params.push({ name: item.address, defaultValue: item.init || 0, minValue: 0, maxValue: 1 });
                    }
                }
                BaseDSPImp.parseUI(JSON.parse(FaustConst.dsp_JSON).ui, callback);
                // Analyse effect JSON to generate AudioParam parameters
                if (FaustConst.effect_JSON) BaseDSPImp.parseUI(JSON.parse(FaustConst.effect_JSON).ui, callback);
                console.log(params);
                return params;
            }

            process(inputs: Float32Array[][], outputs: Float32Array[][], parameters: { [key: string]: Float32Array }) {

                /*
                // Update controls (possibly needed for sample accurate control), deactivated for now
                for (const path in parameters) {
                    const paramArray = parameters[path];
                    this.fDSPCode.setParamValue(path, paramArray[0]);
                }
                */

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

                this.fDSPCode = new MonoDSPImp(new Faust.Generator().createSyncDSPInstance(options.processorOptions.factory), sampleRate, 128);

                // Setup output handler
                this.fDSPCode.setOutputParamHandler((path, value) => this.port.postMessage({ path, value, type: "param" }));
            }
        }

        // Polyphonic AudioWorkletProcessor
        class FaustPolyAudioWorkletProcessor extends FaustAudioWorkletProcessor {

            constructor(options: AudioWorkletNodeOptions) {
                super(options);

                this.fDSPCode = new PolyDSPImp(new Faust.Generator().createSyncPolyDSPInstance(
                    options.processorOptions.voice_factory,
                    options.processorOptions.mixer_module,
                    options.processorOptions.voices,
                    options.processorOptions.effect_factory), sampleRate, 128);

                // Setup port message handling
                this.port.onmessage = this.handleMessage; // Naturally binded with arrow function property

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

            // Public API
            keyOn(channel: number, pitch: number, velocity: number) {
                (this.fDSPCode as PolyDSPImp).keyOn(channel, pitch, velocity);
            }

            keyOff(channel: number, pitch: number, velocity: number) {
                (this.fDSPCode as PolyDSPImp).keyOff(channel, pitch, velocity);
            }

            allNotesOff() {
                (this.fDSPCode as PolyDSPImp).allNotesOff();
            }
        }

        // Synchronously compile and instantiate the wasm module
        if (FaustConst.dsp_name.endsWith("_poly")) {
            registerProcessor(FaustConst.dsp_name || "mydsp_poly", FaustPolyAudioWorkletProcessor);
        } else {
            registerProcessor(FaustConst.dsp_name || "mydsp", FaustMonoAudioWorkletProcessor);
        }
    }

    // Common class for Monophonic and Polyphonic ScriptProcessorNode
    class FaustScriptProcessorNodeImp {

        protected fDSPCode: Faust.BaseDSP;

        // Needed for SP
        protected fInputs: Float32Array[];
        protected fOutputs: Float32Array[];

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

    // Monophonic ScriptProcessorNode
    class FaustMonoScriptProcessorNodeImp extends FaustScriptProcessorNodeImp {

        async init(context: BaseAudioContext, factory: Faust.Factory, buffer_size: number): Promise<Faust.FaustScriptProcessorNode> {
            try {
                const instance = await new Faust.Generator().createAsyncDSPInstance(factory);
                this.fDSPCode = new MonoDSPImp(instance, context.sampleRate, buffer_size);
                let node: FaustScriptProcessorNode = context.createScriptProcessor(buffer_size, this.fDSPCode.getNumInputs(), this.fDSPCode.getNumOutputs()) as FaustScriptProcessorNode;
                super.setupNode(node);
                return node;
            } catch (e) {
                console.log("Error in createScriptProcessor: " + e.message);
                return null;
            }
        }
    }

    // Polyohonic ScriptProcessorNode
    class FaustPolyScriptProcessorNodeImp extends FaustScriptProcessorNodeImp {

        async init(context: BaseAudioContext,
            voice_factory: Faust.Factory,
            mixer_module: WebAssembly.Module,
            voices: number,
            buffer_size: number,
            effect_factory?: Factory): Promise<Faust.FaustPolyScriptProcessorNode> {
            try {
                const instance = await new Faust.Generator().createAsyncPolyDSPInstance(voice_factory, mixer_module, voices, effect_factory)
                this.fDSPCode = new PolyDSPImp(instance, context.sampleRate, buffer_size);
                let node: FaustPolyScriptProcessorNode = context.createScriptProcessor(buffer_size, this.fDSPCode.getNumInputs(), this.fDSPCode.getNumOutputs()) as FaustPolyScriptProcessorNode;

                // Public API
                node.keyOn = (channel: number, pitch: number, velocity: number) => {
                    (this.fDSPCode as PolyDSPImp).keyOn(channel, pitch, velocity);
                }

                node.keyOff = (channel: number, pitch: number, velocity: number) => {
                    (this.fDSPCode as PolyDSPImp).keyOff(channel, pitch, velocity);
                }

                node.allNotesOff = () => {
                    (this.fDSPCode as PolyDSPImp).allNotesOff();
                }

                super.setupNode(node);
                return node;
            } catch (e) {
                console.log("Error in createScriptProcessor: " + e.message);
                return null;
            }
        }
    }

    export class AudioNodeFactory implements Faust.AudioNodeFactory {

        // Table of all create WorkletProcessors, each of them has to be unique
        private fWorkletProcessors: string[] = [];

        async compileMonoNode(context: BaseAudioContext, name: string, compiler: Compiler, dsp_code: string, args: string, sp: boolean, buffer_size?: number)
            : Promise<Faust.FaustScriptProcessorNode | Faust.FaustAudioWorkletNode> {
            const factory = await compiler.createDSPFactory(name, dsp_code, args, false);
            return this.createMonoNode(context, name, factory, sp, buffer_size);
        }

        async createMonoNode(context: BaseAudioContext, name: string, factory: Faust.Factory, sp: boolean, buffer_size?: number)
            : Promise<Faust.FaustScriptProcessorNode | Faust.FaustAudioWorkletNode> {
            if (sp) {
                return new FaustMonoScriptProcessorNodeImp().init(context, factory, buffer_size);
            } else {
                if (this.fWorkletProcessors.indexOf(name) === -1) {
                    // Dynamically create Mono AudioWorkletProcessor code
                    const processor_code = `
                        // Create a Faust namespace
                        let Faust = {};
                        const faustData = { dsp_name: '${name}', dsp_JSON: '${factory.json}' };
                        ${BaseDSPImp.toString()}
                        ${MonoDSPImp.toString()}
                        ${Faust.Generator.toString()} 
                        ${Faust.InstanceAPIImpl.toString()} 
                        (${FaustAudioWorkletProcessorGenerator.toString()})();           
                        Faust.Generator = Generator;`;
                    //console.log(processor_code);
                    const url = window.URL.createObjectURL(new Blob([processor_code], { type: "text/javascript" }));
                    await context.audioWorklet.addModule(url);
                    // Keep the DSP name
                    this.fWorkletProcessors.push(name);
                }
                // Create the AWN
                return new FaustMonoAudioWorkletNode(context, name, factory);
            }
        }

        // We assume that 'dsp_code' contains an integrated effect
        async compilePolyNode(context: BaseAudioContext, name_aux: string, compiler: Compiler, dsp_code: string, args: string, voices: number, sp: boolean, buffer_size?: number)
            : Promise<Faust.FaustPolyScriptProcessorNode | Faust.FaustPolyAudioWorkletNode> {
            const name = name_aux + "_poly";
            // Compile voice
            const voice_factory = await compiler.createDSPFactory(name, dsp_code, args, true);
            if (!voice_factory) return null;
            // Compile effect
            const dsp_effect = `adapt(1,1) = _; adapt(2,2) = _,_; adapt(1,2) = _ <: _,_; adapt(2,1) = _,_ :> _;
                                adaptor(F,G) = adapt(outputs(F),inputs(G));
                                dsp_code = environment{${dsp_code}};
                                process = adaptor(dsp_code.process, dsp_code.effect) : dsp_code.effect;`;
            const effect_factory = await compiler.createDSPFactory(name, dsp_effect, args, true);
            // Compile mixer
            const mixer_file = await fetch('mixer32.wasm');
            const mixer_buffer = await mixer_file.arrayBuffer();
            const mixer_module = await WebAssembly.compile(mixer_buffer);
            return this.createPolyNode(context, name, voice_factory, mixer_module, voices, sp, buffer_size, effect_factory);
        }

        async createPolyNode(context: BaseAudioContext, name_aux: string, voice_factory: Faust.Factory, mixer_module: WebAssembly.Module, voices: number, sp: boolean, buffer_size?: number, effect_factory?: Factory)
            : Promise<Faust.FaustPolyScriptProcessorNode | Faust.FaustPolyAudioWorkletNode> {
            const name = name_aux + "_poly";
            if (sp) {
                return new FaustPolyScriptProcessorNodeImp().init(context, voice_factory, mixer_module, voices, buffer_size, effect_factory);
            } else {
                if (this.fWorkletProcessors.indexOf(name) === -1) {
                    // Dynamically create Poly AudioWorkletProcessor code
                    const processor_code = `
                        // Create a Faust namespace
                        let Faust = {};
                        const faustData = { dsp_name: '${name}', dsp_JSON: '${voice_factory.json}', effect_JSON: '${(effect_factory) ? effect_factory.json : ""}'};
                        ${BaseDSPImp.toString()}
                        ${PolyDSPImp.toString()}
                        ${DspVoice.toString()}
                        ${Faust.Generator.toString()} 
                        ${Faust.InstanceAPIImpl.toString()} 
                        (${FaustAudioWorkletProcessorGenerator.toString()})();           
                        Faust.Generator = Generator;`;
                    console.log(processor_code);
                    const url = window.URL.createObjectURL(new Blob([processor_code], { type: "text/javascript" }));
                    await context.audioWorklet.addModule(url);
                    // Keep the DSP name
                    this.fWorkletProcessors.push(name);
                }
                // Create the AWN
                return new FaustPolyAudioWorkletNode(context, name, voice_factory, mixer_module, voices, effect_factory);
            }
        }
    }
}
