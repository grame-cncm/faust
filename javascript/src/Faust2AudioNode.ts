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

///<reference path="libfaust.ts"/>
///<reference path="FaustCompiler.ts"/>
///<reference path="FaustWebAudio.ts"/>

namespace Faust {

    export function compileAudioNode(
        context: BaseAudioContext,
        module: FaustModule,
        dsp_code: string,
        effect_code: string | null,
        voices: number, is_double: boolean)
        : Promise<FaustMonoNode | FaustPolyNode | null> {
        let sp = typeof (window.AudioWorkletNode) == "undefined";
        let libfaust = createLibFaust(module);
        if (libfaust) {
            let compiler = createCompiler(libfaust);
            const argv = (is_double) ? "-double -ftz 2" : "-ftz 2";
            if (voices === 0) {
                return createMonoFactory().compileNode(context, "FaustDSP", compiler, dsp_code, argv, sp, 0);
            } else {
                return createPolyFactory().compileNode(context, "FaustDSP", compiler, dsp_code, effect_code, argv, voices, sp, 0);
            }
        }
        return new Promise<null>(() => { return null; });
    }

    export async function createMonoAudioNode(
        context: BaseAudioContext,
        wasm_path: string,
        json_path: string,
        buffer_size?: number)
        : Promise<FaustMonoNode | FaustPolyNode | null> {
        let sp = typeof (window.AudioWorkletNode) == "undefined";
        const factory = await createGenerator().loadDSPFactory(wasm_path, json_path);
        return (factory) ? createMonoFactory().createNode(context, "FaustDSP", factory, sp, buffer_size) : null;
    }

    export async function createPolyAudioNode(
        context: BaseAudioContext,
        voice_path: string,
        voice_json_path: string,
        effect_path: string | null,
        effect_json_path: string | null,
        mixer_path: string,
        voices: number,
        buffer_size?: number)
        : Promise<FaustMonoNode | FaustPolyNode | null> {
        {
            let sp = typeof (window.AudioWorkletNode) == "undefined";
            const gen = createGenerator();
            const mixer_module = await gen.loadDSPMixer(mixer_path);
            if (!mixer_module) return null;
            const voice_factory = await gen.loadDSPFactory(voice_path, voice_json_path);
            if (!voice_factory) return null;
            const effect_factory = (effect_path && effect_json_path) ? await gen.loadDSPFactory(effect_path, effect_json_path) : null;
            return createPolyFactory().createNode(context, "FaustDSP", voice_factory, mixer_module, voices, sp, ((effect_factory) ? effect_factory : undefined), buffer_size);
        }
    }
}
