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

declare namespace Faust {

    /**
     * WAP (Web Audio Plugins) API.   
     */
    interface WAP {

        fBaseURL: string;

        getMetadata(): Promise<string>;

        setParam(path: string, value: number): void;
        getParam(path: string): number;

        inputChannelCount(): number;
        outputChannelCount(): number;

        // TODO (proper typing)
        getDescriptor(): any;

        onMidi(data: number[] | Uint8Array): void;
    }

    interface FaustMonoWAPScriptProcessorNode extends FaustMonoScriptProcessorNode, WAP { }

    interface FaustMonoWAPAudioWorkletNode extends FaustMonoAudioWorkletNode, WAP { }

    /**
     * Constructor.   
     */
    interface createMonoAudioWAPFactory { (context: BaseAudioContext, baseURL: string): MonoWAPFactory }

    interface MonoWAPFactory {

        load(wasm_path_aux: string, json_path_aux: string, sp: boolean)
            : Promise<FaustMonoWAPScriptProcessorNode | FaustMonoWAPAudioWorkletNode | null>;
    }

    interface FaustPolyWAPScriptProcessorNode extends FaustPolyScriptProcessorNode, WAP { }

    interface FaustPolyWAPAudioWorkletNode extends FaustPolyAudioWorkletNode, WAP { }

    /**
     * Constructor.   
     */
    interface createPolyWAPFactory { (context: BaseAudioContext, baseURL: string): PolyWAPFactory }

    interface PolyWAPFactory {

        load(voice_path_aux: string,
            voice_json_path_aux: string,
            effect_path_aux: string,
            effect_json_path_aux: string,
            mixer_path_aux: string,
            voices: number,
            sp: boolean,
            buffer_size?: number)
            : Promise<FaustPolyWAPScriptProcessorNode | FaustPolyWAPAudioWorkletNode | null>;
    }
}
