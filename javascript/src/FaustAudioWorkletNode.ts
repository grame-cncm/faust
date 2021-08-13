/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2020 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 ************************************************************************
 ************************************************************************/

///<reference path="FaustCompiler.ts"/>
///<reference path="FaustWebAudioImp.ts"/>

namespace Faust {

    // Base class for Monophonic and Polyphonic AudioWorkletNode
    class FaustAudioWorkletNodeImp extends (window.AudioWorkletNode || null) {

        protected fJSONDsp: TFaustJSON;
        protected fJSON: string;
        protected fInputsItems: string[];
        protected fOutputHandler: OutputParamHandler | null;
        protected fComputeHandler: ComputeHandler | null;
        protected fPlotHandler: PlotHandler | null;
        protected fUICallback: UIHandler;
        protected fDescriptor: TFaustUIInputItem[];

        constructor(context: BaseAudioContext, name: string, factory: Factory, options: any) {

            // Create JSON object
            const JSONObj = createFaustJSON(factory.json);

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
            this.fOutputHandler = null;
            this.fComputeHandler = null;
            this.fPlotHandler = null;
            this.fDescriptor = [];

            // Parse UI
            this.fInputsItems = [];
            this.fUICallback = (item: TFaustUIItem) => {
                if (item.type === "vslider" || item.type === "hslider" || item.type === "button" || item.type === "checkbox" || item.type === "nentry") {
                    // Keep inputs adresses
                    this.fInputsItems.push(item.address);
                    this.fDescriptor.push(item);
                }
            }
            BaseDSPImp.parseUI(this.fJSONDsp.ui, this.fUICallback);

            // Patch it with additional functions
            this.port.onmessage = (e: MessageEvent) => {
                if (e.data.type === "param" && this.fOutputHandler) {
                    this.fOutputHandler(e.data.path, e.data.value);
                } else if (e.data.type === "plot" && this.fPlotHandler) {
                    this.fPlotHandler(e.data.value, e.data.index, e.data.events);
                }
            };
        }

        // Public API
        setOutputParamHandler(handler: OutputParamHandler | null) {
            this.fOutputHandler = handler;
        }
        getOutputParamHandler() {
            return this.fOutputHandler;
        }

        setComputeHandler(handler: ComputeHandler | null) {
            this.fComputeHandler = handler;
        }
        getComputeHandler(): ComputeHandler | null {
            return this.fComputeHandler;
        }

        setPlotHandler(handler: PlotHandler | null) {
            this.fPlotHandler = handler;
            // Set PlotHandler on processor side
            if (this.fPlotHandler) {
                this.port.postMessage({ type: "setPlotHandler", data: true });
            } else {
                this.port.postMessage({ type: "setPlotHandler", data: false });
            }
        }
        getPlotHandler(): PlotHandler | null {
            return this.fPlotHandler;
        }

        getNumInputs() {
            return this.fJSONDsp.inputs;
        }
        getNumOutputs() {
            return this.fJSONDsp.outputs;
        }

        // Implemented in subclasses
        compute(inputs: Float32Array[], outputs: Float32Array[]) {
            return false;
        }

        metadata(handler: MetadataHandler) {
            if (this.fJSONDsp.meta) {
                this.fJSONDsp.meta.forEach(meta => handler(Object.keys(meta)[0], meta[Object.keys(meta)[0]]));
            }
        }

        midiMessage(data: number[] | Uint8Array): void {
            const cmd = data[0] >> 4;
            const channel = data[0] & 0xf;
            const data1 = data[1];
            const data2 = data[2];
            if (cmd === 11) this.ctrlChange(channel, data1, data2);
            else if (cmd === 14) this.pitchWheel(channel, data2 * 128.0 + data1);
            else this.port.postMessage({ type: "midi", data: data });
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

        getParams() { return this.fInputsItems; }
        getJSON() { return this.fJSON; }
        getUI() { return this.fJSONDsp.ui; }
        getDescriptors() { return this.fDescriptor; }

        start() {
            this.port.postMessage({ type: "start" });
        }

        stop() {
            this.port.postMessage({ type: "stop" });
        }

        destroy() {
            this.port.postMessage({ type: "destroy" });
            this.port.close();
        }
    }

    // Monophonic AudioWorkletNode 
    export class FaustMonoAudioWorkletNodeImp extends FaustAudioWorkletNodeImp implements MonoDSP {

        onprocessorerror = (e: Event) => {
            console.error("Error from " + this.fJSONDsp.name + " FaustMonoAudioWorkletNode");
            throw e;
        }

        constructor(context: BaseAudioContext, name: string, factory: Factory, sample_size: number) {
            super(context, name, factory, { name: name, factory: factory, sample_size: sample_size });
        }
    }

    // Polyphonic AudioWorkletNode 
    export class FaustPolyAudioWorkletNodeImp extends FaustAudioWorkletNodeImp implements PolyDSP {

        private fJSONEffect: TFaustJSON | null;

        onprocessorerror = (e: Event) => {
            console.error("Error from " + this.fJSONDsp.name + " FaustPolyAudioWorkletNode");
            throw e;
        }

        constructor(context: BaseAudioContext, name: string,
            voice_factory: Factory,
            mixer_module: WebAssembly.Module,
            voices: number,
            sample_size: number,
            effect_factory?: Factory) {

            super(context, name, voice_factory,
                {
                    name: name,
                    voice_factory: voice_factory,
                    mixer_module: mixer_module,
                    voices: voices,
                    sample_size: sample_size,
                    effect_factory: effect_factory
                });

            this.fJSONEffect = (effect_factory) ? createFaustJSON(effect_factory.json) : null;

            if (this.fJSONEffect) {
                BaseDSPImp.parseUI(this.fJSONEffect.ui, this.fUICallback);
            }
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

        allNotesOff(hard: boolean) {
            const e = { type: "ctrlChange", data: [0, 123, 0] };
            this.port.postMessage(e);
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

        getUI() {
            const o = this.fJSONDsp;
            const e = this.fJSONEffect;
            const r = { ...o };
            if (e) {
                return [{
                    type: "tgroup", label: "Sequencer", items: [
                        { type: "vgroup", label: "Instrument", items: o.ui },
                        { type: "vgroup", label: "Effect", items: e.ui }
                    ]
                }] as TFaustUI;
            } else {
                return [{
                    type: "tgroup", label: "Polyphonic", items: [
                        { type: "vgroup", label: "Voices", items: o.ui }
                    ]
                }] as TFaustUI;
            }
        }
    }
}
