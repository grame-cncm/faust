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

///<reference path="FaustWAP.d.ts"/>
///<reference path="FaustWebAudio.d.ts"/>

namespace Faust {

    export function createAudioWAPNodeFactory(context: BaseAudioContext, baseURL: string = "") {
        return new AudioWAPNodeFactoryImp(context, baseURL);
    }

    export class AudioWAPNodeFactoryImp implements AudioWAPNodeFactory {

        fContext: BaseAudioContext;
        fBaseURL: string;

        constructor(context: BaseAudioContext, baseURL: string = "") {
            this.fContext = context;
            this.fBaseURL = baseURL;
        }

        async load(): Promise<FaustMonoWAPScriptProcessorNode | FaustMonoWAPAudioWorkletNode | null> {
            const wasm_path = (this.fBaseURL === "") ? "mydsp.wasm" : (this.fBaseURL + "/mydsp.wasm");
            const json_path = (this.fBaseURL === "") ? "mydsp.js" : (this.fBaseURL + "/mydsp.js");
            const factory = await createGenerator().loadDSPFactory(wasm_path, json_path);
            if (factory) {
                let node = await this.createMonoNode(this.fContext, "FausDSP", factory, false);
                if (node) node.fBaseURL = this.fBaseURL;
                return node;
            } else {
                return null;
            }
        }

        // TODO
        //async loadGui();

        private async compileWAPMonoNode(
            context: BaseAudioContext,
            name: string,
            compiler: Compiler,
            dsp_code: string,
            args: string,
            sp: boolean,
            buffer_size?: number)
            : Promise<FaustMonoWAPScriptProcessorNode | FaustMonoWAPAudioWorkletNode | null> {
            let node = await createAudioNodeFactory().compileMonoNode(context, name, compiler, dsp_code, args, sp, buffer_size);
            let wap = node as FaustMonoWAPScriptProcessorNode | FaustMonoWAPAudioWorkletNode;
            // Dynamically add WAP API to the node
            if (wap) {
                wap.getMetadata = async () => {
                    const real_url = (wap.fBaseURL === "") ? "main.json" : (wap.fBaseURL + "/main.json");
                    const json_file = await fetch(real_url);
                    return json_file.json();
                }
                wap.setParam = (path: string, value: number) => {
                    wap.setParamValue(path, value);
                }
                wap.getParam = (path: string) => {
                    return wap.getParamValue(path);
                }
                wap.inputChannelCount = () => {
                    return wap.getNumInputs();
                }
                wap.outputChannelCount = () => {
                    return wap.getNumOutputs();
                }
                wap.onMidi = (data: number[] | Uint8Array) => {
                    return wap.midiMessage(data);
                }
            }
            return wap;
        }

        private async createMonoNode(
            context: BaseAudioContext,
            name: string,
            factory: Factory,
            sp: boolean,
            buffer_size?: number)
            : Promise<FaustMonoWAPScriptProcessorNode | FaustMonoWAPAudioWorkletNode | null> {
            let node = await createAudioNodeFactory().createMonoNode(context, name, factory, sp, buffer_size);
            let wap = node as FaustMonoWAPScriptProcessorNode | FaustMonoWAPAudioWorkletNode;
            // Dynamically add WAP API to the node
            if (wap) {
                wap.getMetadata = async () => {
                    const real_url = (wap.fBaseURL === "") ? "main.json" : (wap.fBaseURL + "/main.json");
                    const json_file = await fetch(real_url);
                    return json_file.json();
                }
                wap.setParam = (path: string, value: number) => {
                    wap.setParamValue(path, value);
                }
                wap.getParam = (path: string) => {
                    return wap.getParamValue(path);
                }
                wap.inputChannelCount = () => {
                    return wap.getNumInputs();
                }
                wap.outputChannelCount = () => {
                    return wap.getNumOutputs();
                }
                wap.onMidi = (data: number[] | Uint8Array) => {
                    return wap.midiMessage(data);
                }
            }
            return wap;
        }

    }
}