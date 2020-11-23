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

    let gNodeCount = 0;

    export function compileAudioNode(audioCtx: BaseAudioContext, module: FaustModule, dsp_code: string, effect_code: string | null, voices: number)
        : Promise<FaustMonoNode | FaustPolyNode | null> {
        let sp = typeof (window.AudioWorkletNode) == "undefined";
        let libfaust = createLibFaust(module);
        if (libfaust) {
            let compiler = createCompiler(libfaust);
            gNodeCount++;
            if (voices === 0) {
                return createAudioNodeFactory().compileMonoNode(audioCtx, "Faust" + gNodeCount.toString(), compiler, dsp_code, "-ftz 2", sp, 0);
            } else {
                return createAudioNodeFactory().compilePolyNode(audioCtx, "Faust" + gNodeCount.toString(), compiler, dsp_code, effect_code, "-ftz 2", voices, sp, 0);
            }
        }
        return new Promise<null>(() => { return null; });
    }
}
