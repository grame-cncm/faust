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

///<reference path="FaustWebAudio.d.ts"/>

declare namespace Faust {

    /**
     * Compiles a WebAudio node from its DSP code
     *
     * @param {BaseAudioContext} context the WebAudio context
     * @param {FaustModule} module - the Faust module as given by an async FaustModule() call
     * @param {string} dsp_code - the Faust dsp code (may contain an integrated effect)
     * @param {string | null} effect_code - optional effect DSP code
     * @param {number} voices - the number of voices. When voices = 0, a monophonic node is created, otherwisee a polyohonic one.
     * @preturn {Promise<FaustMonoNode | FaustPolyNode | null>} the compiled WebAudio node or 'null' in case of failure
     */
    interface compileAudioNode {
        (audioCtx: BaseAudioContext, module: FaustModule, dsp_code: string, effect_code: string | null, voices: number): Promise<FaustMonoNode | FaustPolyNode | null>
    }

}