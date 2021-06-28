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

// AudioWorkletNode/AudioWorkletProcessor
///<reference path="FaustWebAudio.d.ts"/>
///<reference path="FaustAudioWorkletNode.ts"/>
///<reference path="FaustAudioWorkletProcessor.ts"/>

// ScriptProcessorNode
///<reference path="FaustScriptProcessorNode.ts"/>

// OfflineProcessor
///<reference path="FaustOfflineProcessor.ts"/>

namespace Faust {

    export function createMonoFactory() { return new MonoFactoryImp(); }

    export function createPolyFactory() { return new PolyFactoryImp(); }

    class MonoFactoryImp implements MonoFactory {

        fFactory: Factory | null;

        // Set of all created WorkletProcessors, each of them has to be unique
        private static gWorkletProcessors: Set<string> = new Set();

        constructor() {
            this.fFactory = null;
        }

        async compileNode(context: BaseAudioContext, name: string, compiler: Compiler, dsp_code: string, args: string, sp: boolean, buffer_size?: number)
            : Promise<FaustMonoNode | null> {
            this.fFactory = await compiler.createMonoDSPFactory(name, dsp_code, args);
            return (this.fFactory) ? this.createNode(context, name, this.fFactory, sp, buffer_size) : null;
        }

        async createNode(context: BaseAudioContext, name_aux: string, factory: Factory, sp: boolean, buffer_size?: number)
            : Promise<FaustMonoNode | null> {
            const JSONObj = createFaustJSON(factory.json);
            const sample_size = JSONObj.compile_options.match("-double") ? 8 : 4;
            if (sp) {
                buffer_size = (buffer_size) ? buffer_size : 1024; // Set a default value if needed
                const instance = await createGenerator().createAsyncMonoDSPInstance(factory);
                const mono_dsp = createMonoDSP(instance, context.sampleRate, sample_size, buffer_size);
                return new FaustMonoScriptProcessorNodeImp().init(context, mono_dsp, buffer_size);
            } else {
                const name = name_aux + factory.cfactory.toString();
                // Dynamically create AudioWorkletProcessor if code not yet created
                if (!MonoFactoryImp.gWorkletProcessors.has(name)) {
                    try {
                        const processor_code = `
                            // Create a Faust namespace
                            let Faust = {};
                            // DSP name and JSON string for DSP are generated
                            const faustData = { dsp_name: '${name}', dsp_JSON: '${factory.json}' };
                            // Implementation needed classes of functions
                            ${BaseDSPImp.toString()}
                            ${MonoDSPImp.toString()}
                            ${Faust.GeneratorImp.toString()} 
                            ${Faust.InstanceAPIImpl.toString()} 
                            ${Faust.createMonoDSP.toString()} 
                            ${Faust.createFaustJSON.toString()} 
                            // Put them in Faust namespace
                            Faust.BaseDSPImp = BaseDSPImp;
                            Faust.MonoDSPImp = MonoDSPImp;
                            Faust.GeneratorImp = GeneratorImp;
                            Faust.createMonoDSP = createMonoDSP;
                            Faust.createFaustJSON = createFaustJSON;
                            // Generate the actual AudioWorkletProcessor code
                            (${FaustAudioWorkletProcessorGenerator.toString()})(); `;
                        const url = window.URL.createObjectURL(new Blob([processor_code], { type: "text/javascript" }));
                        await context.audioWorklet.addModule(url);
                        // Keep the DSP name
                        MonoFactoryImp.gWorkletProcessors.add(name);
                    } catch (e) {
                        console.error("=> exception raised while running createMonoNode: " + e);
                        console.error("=> check that your page is served using https." + e);
                        return null;
                    }
                }
                // Create the AWN
                return new FaustMonoAudioWorkletNodeImp(context, name, factory, sample_size);
            }
        }

        async createOfflineProcessor(factory: Factory, sample_rate: number, buffer_size: number)
            : Promise<FaustOfflineProcessor | null> {
            const instance = await createGenerator().createAsyncMonoDSPInstance(factory);
            const JSONObj = createFaustJSON(factory.json);
            const sample_size = JSONObj.compile_options.match("-double") ? 8 : 4;
            const mono_dsp = createMonoDSP(instance, sample_rate, sample_size, buffer_size);
            return new FaustOfflineProcessorImp(mono_dsp, buffer_size);
        }

        getFactory(): Factory | null {
            return this.fFactory;
        }
    }

    class PolyFactoryImp implements PolyFactory {

        fVoiceFactory: Factory | null;
        fEffectFactory: Factory | null;

        // Set of all created WorkletProcessors, each of them has to be unique
        private static gWorkletProcessors: Set<string> = new Set();

        constructor() {
            this.fVoiceFactory = null;
            this.fEffectFactory = null;
        }

        // 'dsp_code' can possibly contain an integrated effect
        async compileNode(
            context: BaseAudioContext,
            name: string,
            compiler: Compiler,
            dsp_code: string,
            effect_code: string | null,
            args: string,
            voices: number,
            sp: boolean,
            buffer_size?: number)
            : Promise<FaustPolyNode | null> {
            const voice_dsp = dsp_code;
            const effect_dsp = effect_code ? effect_code :
                `adapt(1,1) = _; adapt(2,2) = _,_; adapt(1,2) = _ <: _,_; adapt(2,1) = _,_ :> _;
                                adaptor(F,G) = adapt(outputs(F),inputs(G));
                                dsp_code = environment{${dsp_code}};
                                process = adaptor(dsp_code.process, dsp_code.effect) : dsp_code.effect;`;
            // Compile voice
            const voice_factory = await compiler.createPolyDSPFactory(name, voice_dsp, args);
            if (!voice_factory) return null;
            // Compile effect, possibly failing since 'compilePolyNode2' can be called by called by 'compilePolyNode'
            const effect_factory = await compiler.createPolyDSPFactory(name, effect_dsp, args);
            // Compile mixer
            const JSONObj = createFaustJSON(voice_factory.json);
            const is_double = JSONObj.compile_options.match("-double");
            const mixer_module = await createGenerator().loadDSPMixer((is_double) ? '/usr/rsrc/mixer64.wasm' : '/usr/rsrc/mixer32.wasm');
            return (mixer_module) ? this.createNode(context, name, voice_factory, mixer_module, voices, sp, ((effect_factory) ? effect_factory : undefined), buffer_size) : null;
        }

        async createNode(
            context: BaseAudioContext,
            name_aux: string,
            voice_factory: Factory,
            mixer_module: WebAssembly.Module,
            voices: number,
            sp: boolean,
            effect_factory?: Factory,
            buffer_size?: number,
        ): Promise<FaustPolyNode | null> {
            const JSONObj = createFaustJSON(voice_factory.json);
            const sample_size = JSONObj.compile_options.match("-double") ? 8 : 4;
            if (sp) {
                buffer_size = (buffer_size) ? buffer_size : 1024; // Set a default value if needed
                const instance = await createGenerator().createAsyncPolyDSPInstance(voice_factory, mixer_module, voices, effect_factory);
                const poly_dsp = createPolyDSP(instance, context.sampleRate, sample_size, buffer_size);
                return new FaustPolyScriptProcessorNodeImp().init(context, poly_dsp, buffer_size);
            } else {
                const name = name_aux + voice_factory.cfactory.toString() + "_poly";
                // Dynamically create AudioWorkletProcessor if code not yet created
                if (!PolyFactoryImp.gWorkletProcessors.has(name)) {
                    try {
                        const processor_code = `
                            // Create a Faust namespace
                            let Faust = {};
                            // DSP name and JSON strings for DSP and (possible) effect are generated
                            const faustData = { dsp_name: '${name}', dsp_JSON: '${voice_factory.json}', effect_JSON: '${(effect_factory) ? effect_factory.json : ""}'};
                            // Implementation needed classes of functions
                            ${BaseDSPImp.toString()}
                            ${PolyDSPImp.toString()}
                            ${DspVoice.toString()}
                            ${Faust.GeneratorImp.toString()} 
                            ${Faust.InstanceAPIImpl.toString()} 
                            ${Faust.createPolyDSP.toString()}
                            ${Faust.createFaustJSON.toString()}  
                            // Put them in Faust namespace
                            Faust.BaseDSPImp = BaseDSPImp;
                            Faust.PolyDSPImp = PolyDSPImp;
                            Faust.GeneratorImp = GeneratorImp;
                            Faust.createPolyDSP = createPolyDSP;
                            Faust.createFaustJSON = createFaustJSON;
                            // Generate the actual AudioWorkletProcessor code
                            (${FaustAudioWorkletProcessorGenerator.toString()})();`;
                        const url = window.URL.createObjectURL(new Blob([processor_code], { type: "text/javascript" }));
                        await context.audioWorklet.addModule(url);
                        // Keep the DSP name
                        PolyFactoryImp.gWorkletProcessors.add(name);
                    } catch (e) {
                        console.error("=> exception raised while running createPolyNode: " + e);
                        return null;
                    }
                }
                // Create the AWN
                return new FaustPolyAudioWorkletNodeImp(context, name, voice_factory, mixer_module, voices, sample_size, effect_factory);
            }
        }

        getVoiceFactory(): Factory | null {
            return this.fVoiceFactory;
        }

        getEffectFactory(): Factory | null {
            return this.fEffectFactory;
        }
    }
}
