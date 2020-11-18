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

///<reference path="libfaust.ts"/>
///<reference path="FaustCompiler.ts"/>
///<reference path="FaustWebAudio.ts"/>

namespace Faust {

    export function compileAudioNode (audioCtx: BaseAudioContext, module: FaustModule, code: string, voices: number, effect_code: string | null = null) 
    : Promise<FaustMonoNode | FaustPolyNode | null> 
    {
        let sp = typeof (window.AudioWorkletNode) == "undefined";
        let libfaust = createLibFaust(module);
        if (libfaust) {
            let compiler = createCompiler(libfaust);
            if (voices > 1)
                return createAudioNodeFactory().compilePolyNode(audioCtx, "Faust", compiler, code, effect_code, "", voices, sp, 0);
            else
                return createAudioNodeFactory().compileMonoNode(audioCtx, "Faust", compiler, code, "", sp, 0);
        }
        return new Promise<null>(() => { return null;} );
    }
}
