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

///<reference path="FaustCompiler.d.ts"/>
///<reference path="FaustWAP.d.ts"/>
///<reference path="FaustWebAudio.ts"/>
///<reference path="FaustGenerator.ts"/>

namespace Faust {

    export function createMonoWAPFactory(context: BaseAudioContext, baseURL: string = "") {
        return new MonoWAPFactoryImp(context, baseURL);
    }

    class MonoWAPFactoryImp implements MonoWAPFactory {

        fContext: BaseAudioContext;
        fBaseURL: string;

        private makeMonoWAP(node: FaustMonoNode | null) {
            const wap = node as FaustMonoWAPNode;
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
                wap.getDescriptor = () => {
                    let desc = {};
                    const descriptor = wap.getDescriptors();
                    for (const item in descriptor) {
                        if (descriptor.hasOwnProperty(item)) {
                            if (descriptor[item].label != "bypass") {
                                desc = Object.assign({ [descriptor[item].label]: { minValue: descriptor[item].min, maxValue: descriptor[item].max, defaultValue: descriptor[item].init } }, desc);
                            }
                        }
                    }
                    return desc;
                }
                return wap;
            } else {
                return null;
            }
        }

        private async compileMonoWAPNode(
            context: BaseAudioContext,
            name: string,
            compiler: Compiler,
            dsp_code: string,
            args: string,
            sp: boolean,
            buffer_size?: number)
            : Promise<FaustMonoWAPNode | null> {
            const node = await createMonoFactory().compileNode(context, name, compiler, dsp_code, args, sp, buffer_size);
            // Dynamically add WAP API to the node
            return this.makeMonoWAP(node);
        }

        private async createMonoWAPNode(
            context: BaseAudioContext,
            name: string,
            factory: Factory,
            sp: boolean,
            buffer_size?: number)
            : Promise<FaustMonoWAPNode | null> {
            const node = await createMonoFactory().createNode(context, name, factory, sp, buffer_size);
            // Dynamically add WAP API to the node
            return this.makeMonoWAP(node);
        }

        // Public API
        constructor(context: BaseAudioContext, baseURL: string = "") {
            this.fContext = context;
            this.fBaseURL = baseURL;
        }

        async load(wasm_path_aux: string, json_path_aux: string, sp: boolean = false)
            : Promise<FaustMonoWAPNode | null> {
            const wasm_path = (this.fBaseURL === "") ? wasm_path_aux : (this.fBaseURL + '/' + wasm_path_aux);
            const json_path = (this.fBaseURL === "") ? json_path_aux : (this.fBaseURL + '/' + json_path_aux);
            const factory = await createGenerator().loadDSPFactory(wasm_path, json_path);
            if (factory) {
                const node = await this.createMonoWAPNode(this.fContext, "FausDSP", factory, sp, 1024);
                if (node) node.fBaseURL = this.fBaseURL;
                return node;
            } else {
                return null;
            }
        }
    }

    export function createPolyWAPFactory(context: BaseAudioContext, baseURL: string = "") {
        return new PolyWAPFactoryImp(context, baseURL);
    }

    class PolyWAPFactoryImp implements PolyWAPFactory {

        fContext: BaseAudioContext;
        fBaseURL: string;

        private makePolyWAP(node: | FaustPolyNode | null) {
            const wap = node as FaustPolyWAPNode;
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
                wap.getDescriptor = () => {
                    let desc = {};
                    const descriptor = wap.getDescriptors();
                    for (const item in descriptor) {
                        if (descriptor.hasOwnProperty(item)) {
                            if (descriptor[item].label != "bypass") {
                                desc = Object.assign({ [descriptor[item].label]: { minValue: descriptor[item].min, maxValue: descriptor[item].max, defaultValue: descriptor[item].init } }, desc);
                            }
                        }
                    }
                    return desc;
                }
                return wap;
            } else {
                return null;
            }
        }

        private async createPolyWAPNode(
            context: BaseAudioContext,
            name_aux: string,
            voice_factory: Factory,
            mixer_module: WebAssembly.Module,
            voices: number,
            sp: boolean,
            effect_factory?: Factory,
            buffer_size?: number)
            : Promise<FaustPolyWAPNode | null> {
            const node = await createPolyFactory().createNode(context, "FaustDSP", voice_factory, mixer_module, voices, sp, effect_factory, buffer_size);
            // Dynamically add WAP API to the node
            return this.makePolyWAP(node);
        }

        // Public API
        constructor(context: BaseAudioContext, baseURL: string = "") {
            this.fContext = context;
            this.fBaseURL = baseURL;
        }

        async load(voice_path_aux: string,
            voice_json_path_aux: string,
            effect_path_aux: string,
            effect_json_path_aux: string,
            mixer32_path_aux: string,
            mixer64_path_aux: string,
            voices: number,
            sp: boolean,
            buffer_size?: number)
            : Promise<FaustPolyWAPNode | null> {
            const voice_path = (this.fBaseURL === "") ? voice_path_aux : (this.fBaseURL + '/' + voice_path_aux);
            const voice_json_path = (this.fBaseURL === "") ? voice_json_path_aux : (this.fBaseURL + '/' + voice_json_path_aux);
            const effect_path = (this.fBaseURL === "") ? effect_path_aux : (this.fBaseURL + '/' + effect_path_aux);
            const effect_json_path = (this.fBaseURL === "") ? effect_json_path_aux : (this.fBaseURL + '/' + effect_json_path_aux);
            const gen = createGenerator();
            const voice_factory = await gen.loadDSPFactory(voice_path, voice_json_path);
            if (!voice_factory) return null;
            const effect_factory = await gen.loadDSPFactory(effect_path, effect_json_path);
            const JSONObj = createFaustJSON(voice_factory.json);
            const is_double = JSONObj.compile_options.match("-double");
            let mixer_path = null;
            if (is_double) {
                mixer_path = (this.fBaseURL === "") ? mixer64_path_aux : (this.fBaseURL + '/' + mixer64_path_aux);
            } else {
                mixer_path = (this.fBaseURL === "") ? mixer32_path_aux : (this.fBaseURL + '/' + mixer32_path_aux);
            }
            const mixer_module = await gen.loadDSPMixer(mixer_path);
            if (!mixer_module) return null;
            const node = await this.createPolyWAPNode(this.fContext, "FaustDSP", voice_factory, mixer_module, voices, sp, ((effect_factory) ? effect_factory : undefined), 1024);
            if (node) node.fBaseURL = this.fBaseURL;
            return node;
        }
    }
}
