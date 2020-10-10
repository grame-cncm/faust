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

// AudioWorkletNode/AudioWorkletProcessor
///<reference path="FaustAudioWorkletNode.ts"/>
///<reference path="FaustAudioWorkletProcessor.ts"/>

// ScriptProcessorNode
///<reference path="FaustScriptProcessorNode.ts"/>

namespace Faust {

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
                        Faust.Generator = Generator;
                        Faust.BaseDSPImp = BaseDSPImp;
                        Faust.MonoDSPImp = MonoDSPImp;
                        (${FaustAudioWorkletProcessorGenerator.toString()})(); `;
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
                        Faust.Generator = Generator;
                        Faust.BaseDSPImp = BaseDSPImp;
                        Faust.PolyDSPImp = PolyDSPImp;
                        (${FaustAudioWorkletProcessorGenerator.toString()})();`;
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
