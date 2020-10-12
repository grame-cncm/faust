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

    export class AudioNodeFactory implements AudioNodeFactory {

        // Table of all create WorkletProcessors, each of them has to be unique
        private fWorkletProcessors: string[] = [];

        async compileMonoNode(context: BaseAudioContext, name: string, compiler: Compiler, dsp_code: string, args: string, sp: boolean, buffer_size?: number)
            : Promise<FaustMonoScriptProcessorNode | FaustMonoAudioWorkletNode | null> {
            const factory = await compiler.createMonoDSPFactory(name, dsp_code, args);
            return (factory) ? this.createMonoNode(context, name, factory, sp, buffer_size) : null;
        }

        async createMonoNode(context: BaseAudioContext, name: string, factory: Factory, sp: boolean, buffer_size?: number)
            : Promise<FaustMonoScriptProcessorNode | FaustMonoAudioWorkletNode | null> {
            if (sp) {
                buffer_size = (buffer_size) ? buffer_size : 1024; // Set a default value if needed
                const instance = await new GeneratorImp().createAsyncMonoDSPInstance(factory);
                const mono_dsp = createMonoDSP(MonoDSPImp, instance, context.sampleRate, buffer_size);
                return new FaustMonoScriptProcessorNodeImp().init(context, mono_dsp, buffer_size);
            } else {
                // Dynamically create AudioWorkletProcessor if code not yet created
                if (this.fWorkletProcessors.indexOf(name) === -1) {
                    try {
                        const processor_code = `
                            // Create a Faust namespace
                            let Faust = {};
                            // DSP name and JSON string for DSP are generated
                            const faustData = { dsp_name: '${name}', dsp_JSON: '${factory.json}' };
                            // Implementation needed classes
                            ${BaseDSPImp.toString()}
                            ${MonoDSPImp.toString()}
                            ${Faust.GeneratorImp.toString()} 
                            ${Faust.InstanceAPIImpl.toString()} 
                            // Put them in Faust namespace
                            Faust.GeneratorImp = GeneratorImp;
                            Faust.BaseDSPImp = BaseDSPImp;
                            Faust.MonoDSPImp = MonoDSPImp;
                            // Generate the actual AudioWorkletProcessor code
                            (${FaustAudioWorkletProcessorGenerator.toString()})(); `;
                        const url = window.URL.createObjectURL(new Blob([processor_code], { type: "text/javascript" }));
                        await context.audioWorklet.addModule(url);
                        // Keep the DSP name
                        this.fWorkletProcessors.push(name);
                    } catch (e) {
                        console.error("=> exception raised while running createMonoNode: " + e);
                        return null;
                    }
                }
                // Create the AWN
                return new FaustMonoAudioWorkletNode(context, name, factory);
            }
        }

        // We assume that 'dsp_code' contains an integrated effect
        async compilePolyNode(
            context: BaseAudioContext,
            name: string,
            compiler: Compiler,
            dsp_code: string,
            args: string,
            voices: number,
            sp: boolean,
            buffer_size?: number)
            : Promise<FaustPolyScriptProcessorNode | FaustPolyAudioWorkletNode | null> {
            const voice_dsp = dsp_code;
            const effect_dsp = `adapt(1,1) = _; adapt(2,2) = _,_; adapt(1,2) = _ <: _,_; adapt(2,1) = _,_ :> _;
                                adaptor(F,G) = adapt(outputs(F),inputs(G));
                                dsp_code = environment{${dsp_code}};
                                process = adaptor(dsp_code.process, dsp_code.effect) : dsp_code.effect;`;
            return this.compilePolyNode2(context, name, compiler, voice_dsp, effect_dsp, args, voices, sp, buffer_size);
        }

        // Separated voice and effect DSPs
        async compilePolyNode2(context: BaseAudioContext,
            name: string,
            compiler: Compiler,
            voices_dsp: string,
            effect_dsp: string,
            args: string,
            voices: number,
            sp: boolean,
            buffer_size?: number)
            : Promise<FaustPolyScriptProcessorNode | FaustPolyAudioWorkletNode | null> {
            // Compile voice
            const voice_factory = await compiler.createPolyDSPFactory(name, voices_dsp, args);
            if (!voice_factory) return null;
            // Compile effect
            const effect_factory = await compiler.createPolyDSPFactory(name, effect_dsp, args);
            if (!effect_factory) return null;
            // Compile mixer
            const mixer_module = await new GeneratorImp().loadDSPMixer('mixer32.wasm');
            return (mixer_module) ? this.createPolyNode(context, name, voice_factory, mixer_module, voices, sp, effect_factory, buffer_size) : null;
        }

        async createPolyNode(
            context: BaseAudioContext,
            name_aux: string,
            voice_factory: Factory,
            mixer_module: WebAssembly.Module,
            voices: number,
            sp: boolean,
            effect_factory?: Factory,
            buffer_size?: number)
            : Promise<FaustPolyScriptProcessorNode | FaustPolyAudioWorkletNode | null> {
            const name = name_aux + "_poly";
            if (sp) {
                buffer_size = (buffer_size) ? buffer_size : 1024; // Set a default value if needed
                const instance = await new GeneratorImp().createAsyncPolyDSPInstance(voice_factory, mixer_module, voices, effect_factory);
                const poly_dsp = createPolyDSP(PolyDSPImp, instance, context.sampleRate, buffer_size);
                return new FaustPolyScriptProcessorNodeImp().init(context, poly_dsp, buffer_size);
            } else {
                // Dynamically create AudioWorkletProcessor if code not yet created
                if (this.fWorkletProcessors.indexOf(name) === -1) {
                    try {
                        const processor_code = `
                            // Create a Faust namespace
                            let Faust = {};
                            // DSP name and JSON strings for DSP and (possible) effect are generated
                            const faustData = { dsp_name: '${name}', dsp_JSON: '${voice_factory.json}', effect_JSON: '${(effect_factory) ? effect_factory.json : ""}'};
                            // Implementation needed classes
                            ${BaseDSPImp.toString()}
                            ${PolyDSPImp.toString()}
                            ${DspVoice.toString()}
                            ${Faust.GeneratorImp.toString()} 
                            ${Faust.InstanceAPIImpl.toString()} 
                            // Put them in Faust namespace
                            Faust.GeneratorImp = GeneratorImp;
                            Faust.BaseDSPImp = BaseDSPImp;
                            Faust.PolyDSPImp = PolyDSPImp;
                            // Generate the actual AudioWorkletProcessor code
                            (${FaustAudioWorkletProcessorGenerator.toString()})();`;
                        const url = window.URL.createObjectURL(new Blob([processor_code], { type: "text/javascript" }));
                        await context.audioWorklet.addModule(url);
                        // Keep the DSP name
                        this.fWorkletProcessors.push(name);
                    } catch (e) {
                        console.error("=> exception raised while running createPolyNode: " + e);
                        return null;
                    }
                }
                // Create the AWN
                return new FaustPolyAudioWorkletNode(context, name, voice_factory, mixer_module, voices, effect_factory);
            }
        }
    }
}
