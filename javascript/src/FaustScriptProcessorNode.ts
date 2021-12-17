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

///<reference path="FaustWebAudioImp.ts"/>

namespace Faust {

    // Base class for Monophonic and Polyphonic ScriptProcessorNode
    class FaustScriptProcessorNodeImp {

        protected fDSPCode!: BaseDSP;

        // Needed for ScriptProcessorNode
        protected fInputs!: Float32Array[];
        protected fOutputs!: Float32Array[];

        protected setupNode(node: FaustMonoNode) {

            this.fInputs = new Array(this.fDSPCode.getNumInputs());
            this.fOutputs = new Array(this.fDSPCode.getNumOutputs());

            let tmp = node as unknown;
            let spnode = tmp as ScriptProcessorNode;

            spnode.onaudioprocess = (e) => {

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

            node.setComputeHandler = (handler: ComputeHandler) => {
                this.fDSPCode.setComputeHandler(handler);
            }

            node.getComputeHandler = () => { return this.fDSPCode.getComputeHandler(); }

            node.setPlotHandler = (handler: PlotHandler) => {
                this.fDSPCode.setPlotHandler(handler);
            }

            node.getPlotHandler = () => { return this.fDSPCode.getPlotHandler(); }

            node.getNumInputs = () => { return this.fDSPCode.getNumInputs(); }
            node.getNumOutputs = () => { return this.fDSPCode.getNumOutputs(); }

            node.metadata = (handler: MetadataHandler) => { }

            node.midiMessage = (data: number[] | Uint8Array) => { this.fDSPCode.midiMessage(data); }

            node.ctrlChange = (chan: number, ctrl: number, value: number) => { this.fDSPCode.ctrlChange(chan, ctrl, value); }
            node.pitchWheel = (chan: number, value: number) => { this.fDSPCode.pitchWheel(chan, value); }

            node.setParamValue = (path: string, value: number) => { this.fDSPCode.setParamValue(path, value); }
            node.getParamValue = (path: string) => { return this.fDSPCode.getParamValue(path); }
            node.getParams = () => { return this.fDSPCode.getParams(); }

            node.getJSON = () => { return this.fDSPCode.getJSON(); }
            node.getDescriptors = () => { return this.fDSPCode.getDescriptors(); }
            node.getUI = () => { return this.fDSPCode.getUI(); }

            node.start = () => { this.fDSPCode.start(); }
            node.stop = () => { this.fDSPCode.stop(); }

            node.destroy = () => { this.fDSPCode.destroy(); }
        }
    }

    // Monophonic ScriptProcessorNode
    export class FaustMonoScriptProcessorNodeImp extends FaustScriptProcessorNodeImp {

        async init(context: BaseAudioContext, instance: MonoDSP, buffer_size: number): Promise<FaustMonoNode | null> {
            try {
                this.fDSPCode = instance;
                let node = context.createScriptProcessor(buffer_size, this.fDSPCode.getNumInputs(), this.fDSPCode.getNumOutputs()) as unknown;
                let faustnode = node as FaustMonoNode;
                super.setupNode(faustnode);
                return faustnode;
            } catch (e) {
                console.log("Error in FaustMonoScriptProcessorNodeImp createScriptProcessor: " + (e as Error).message);
                return null;
            }
        }
    }

    // Polyphonic ScriptProcessorNode
    export class FaustPolyScriptProcessorNodeImp extends FaustScriptProcessorNodeImp {

        async init(context: BaseAudioContext, instance: PolyDSP, buffer_size: number): Promise<FaustPolyNode | null> {
            try {
                this.fDSPCode = instance;
                let node = context.createScriptProcessor(buffer_size, this.fDSPCode.getNumInputs(), this.fDSPCode.getNumOutputs()) as unknown;
                let faustnode = node as FaustPolyNode;
                super.setupNode(faustnode);
                // Public API
                faustnode.keyOn = (channel: number, pitch: number, velocity: number) => {
                    (this.fDSPCode as PolyDSP).keyOn(channel, pitch, velocity);
                }
                faustnode.keyOff = (channel: number, pitch: number, velocity: number) => {
                    (this.fDSPCode as PolyDSP).keyOff(channel, pitch, velocity);
                }
                faustnode.allNotesOff = (hard: boolean) => {
                    (this.fDSPCode as PolyDSP).allNotesOff(hard);
                }
                return faustnode;
            } catch (e) {
                console.log("Error in FaustPolyScriptProcessorNodeImp createScriptProcessor: " + (e as Error).message);
                return null;
            }
        }
    }
}
