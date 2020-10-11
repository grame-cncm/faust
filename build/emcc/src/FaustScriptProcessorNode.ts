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

    // Base class for Monophonic and Polyphonic ScriptProcessorNode
    class FaustScriptProcessorNodeImp {

        protected fDSPCode: BaseDSP;

        // Needed for ScriptProcessorNode
        protected fInputs: Float32Array[];
        protected fOutputs: Float32Array[];

        protected setupNode(node: FaustMonoScriptProcessorNode | FaustPolyScriptProcessorNode) {

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

            node.metadata = (handler: MetadataHandler) => { }

            node.ctrlChange = (chan: number, ctrl: number, value: number) => { this.fDSPCode.ctrlChange(chan, ctrl, value); }
            node.pitchWheel = (chan: number, value: number) => { this.fDSPCode.pitchWheel(chan, value); }

            node.setParamValue = (path: string, value: number) => { this.fDSPCode.setParamValue(path, value); }
            node.getParamValue = (path: string) => { return this.fDSPCode.getParamValue(path); }
            node.getParams = () => { return this.fDSPCode.getParams(); }

            node.getJSON = () => { return this.fDSPCode.getJSON(); }
            node.getUI = () => { return this.fDSPCode.getUI(); }
            node.destroy = () => { this.fDSPCode.destroy(); }
        }
    }

    // Monophonic ScriptProcessorNode
    export class FaustMonoScriptProcessorNodeImp extends FaustScriptProcessorNodeImp {

        async init(context: BaseAudioContext, instance: MonoDSP, buffer_size: number): Promise<FaustMonoScriptProcessorNode> {
            try {
                this.fDSPCode = instance;
                let node: FaustMonoScriptProcessorNode = context.createScriptProcessor(buffer_size, this.fDSPCode.getNumInputs(), this.fDSPCode.getNumOutputs()) as FaustMonoScriptProcessorNode;
                super.setupNode(node);
                return node;
            } catch (e) {
                console.log("Error in FaustMonoScriptProcessorNodeImp createScriptProcessor: " + e.message);
                return null;
            }
        }
    }

    // Polyphonic ScriptProcessorNode
    export class FaustPolyScriptProcessorNodeImp extends FaustScriptProcessorNodeImp {

        async init(context: BaseAudioContext, instance: PolyDSP, buffer_size: number): Promise<FaustPolyScriptProcessorNode> {
            try {
                this.fDSPCode = instance;
                let node: FaustPolyScriptProcessorNode = context.createScriptProcessor(buffer_size, this.fDSPCode.getNumInputs(), this.fDSPCode.getNumOutputs()) as FaustPolyScriptProcessorNode;
                super.setupNode(node);
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
                return node;
            } catch (e) {
                console.log("Error in FaustPolyScriptProcessorNodeImp createScriptProcessor: " + e.message);
                return null;
            }
        }
    }
}
