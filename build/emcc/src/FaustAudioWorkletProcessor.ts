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

///<reference path="FaustWebAudioImp.ts"/>

namespace Faust {

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

    // Injected in the string to be compiled on AudioWorkletProcessor side
    type FaustData = {
        dsp_name: string;
        dsp_JSON: string;
        effect_JSON: string;
    };
    declare const faustData: FaustData;

    // Dynamic AudioWorkletProcessor code generator
    export const FaustAudioWorkletProcessorGenerator = () => {

        class FaustConst {
            static dsp_name = faustData.dsp_name;
            static dsp_JSON = faustData.dsp_JSON;
            static effect_JSON = faustData.effect_JSON;
        }

        // Base class for Monophonic and Polyphonic AudioWorkletProcessor
        class FaustAudioWorkletProcessorImp extends AudioWorkletProcessor {

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
                        break;
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
        class FaustMonoAudioWorkletProcessor extends FaustAudioWorkletProcessorImp {

            constructor(options: AudioWorkletNodeOptions) {
                super(options);

                // Create Monophonic DSP
                this.fDSPCode = new MonoDSPImp(new Generator().createSyncMonoDSPInstance(options.processorOptions.factory), sampleRate, 128);

                // Setup output handler
                this.fDSPCode.setOutputParamHandler((path, value) => this.port.postMessage({ path, value, type: "param" }));
            }
        }

        // Polyphonic AudioWorkletProcessor
        class FaustPolyAudioWorkletProcessor extends FaustAudioWorkletProcessorImp {

            constructor(options: AudioWorkletNodeOptions) {
                super(options);

                // Create Polyphonic DSP
                this.fDSPCode = new PolyDSPImp(new Generator().createSyncPolyDSPInstance(
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
                        break;
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
}
