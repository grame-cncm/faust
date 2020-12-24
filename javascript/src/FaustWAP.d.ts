
///<reference path="FaustWebAudio.d.ts"/>

declare namespace Faust {

    /**
     * WAP (Web Audio Plugins see https://github.com/micbuffa/WebAudioPlugins) API.   
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

    interface FaustMonoWAPNode extends FaustMonoNode, WAP { }

    interface MonoWAPFactory {

        load(wasm_path: string, json_path: string, sp: boolean)
            : Promise<FaustMonoWAPNode | null>;
    }

    interface FaustPolyWAPNode extends FaustPolyNode, WAP { }

    interface PolyWAPFactory {

        load(voice_path: string,
            voice_json_path: string,
            effect_path: string,
            effect_json_path: string,
            mixer32_path: string,
            mixer64_path: string,
            voices: number,
            sp: boolean,
            buffer_size?: number)
            : Promise<FaustPolyWAPNode | null>;
    }
}

// Moved at the end of the file to please Visual Studio code completion tools.

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
