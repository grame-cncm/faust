
///<reference path="FaustCompiler.d.ts" />
///<reference path="FaustGenerator.d.ts" />
///<reference path="FaustUtilities.d.ts" />
///<reference path="FaustWAP.d.ts" />
///<reference path="FaustWebAudio.d.ts" />
///<reference path="libfaust.d.ts" />

declare namespace Faust {

    /**
     * Instantiates the Faust Library.
     *
     * @param {string} module - the Faust Wasm module, typically retrieved with an async call to FaustModule()
     * @returns {LibFaust} an instance of Faust library
     */
    function createLibFaust(module: FaustModule): LibFaust | null;

    /**
     * Creates a high level Faust compiler.
     *
     * @param {LibFaust} libfaust - an instance of the Faust Library
     * @returns {Compiler} an instance of the Faust compiler
     */
    function createCompiler(libfaust: LibFaust): Compiler;

    /**
     * Creates a factory ready to generate Monophonic ScriptProcessorNode and AudioWorkletNode nodes.
     */
    function createMonoFactory(): MonoFactory;

    /**
    * Creates a factory ready to generate Polyphonic ScriptProcessorNode and AudioWorkletNode nodes.
    */
    function createPolyFactory(): PolyFactory;

    /**
     * Creates an instance of a Generator, which provides memory instances of Web assembly module,
     * as well as objects to access and manipulate theses instances.
     * @returns {Generator} a Generator
     */
    function createGenerator(): Generator;

    /**
     * Higher level function to compile a WebAudio node from its DSP code.
     *
     * @param {BaseAudioContext} context the WebAudio context
     * @param {FaustModule} module - the Faust module as given by an async FaustModule() call
     * @param {string} dsp_code - the Faust dsp code (may contain an integrated effect)
     * @param {string | null} effect_code - optional effect DSP code, that can be used in place of the integrated effect model
     * @param {number} voices - the number of voices. When voices = 0, a monophonic node is created, otherwise a polyphonic one
     * @param {boolean} is_double - whether the sample has to be 'double'
     * 
     * @preturn {Promise<FaustMonoNode | FaustPolyNode | null>} the compiled WebAudio node or 'null' in case of failure
     */
    function compileAudioNode(audioCtx: BaseAudioContext, module: FaustModule, dsp_code: string, effect_code: string | null, voices: number, is_double: number): Promise<FaustMonoNode | FaustPolyNode | null>

    /**
     * The SVGDiagrams generator constructor.
     * You should check the object status using the success() method after creation.
     * 
     * @param {LibFaust} engine - an instance of the Faust engine 
     * @param {string} name - an arbitrary name for the Faust module
     * @param {string} dsp_code - Faust dsp code
     * @param {string} args - the compiler options, only svg specific options are meaningfull (automatically appends -svg)
     */
    function createSVGDiagrams(engine: LibFaust, name: string, dsp_code: string, args: string): SVGDiagrams;

    /**
     * WAP (Web Audio Plugins see https://github.com/micbuffa/WebAudioPlugins) API.   
     */
    function createMonoAudioWAPFactory(context: BaseAudioContext, baseURL: string): MonoWAPFactory;
    function createPolyWAPFactory(context: BaseAudioContext, baseURL: string): PolyWAPFactory;

    /**
     * Transforms a Faust processor JSON description into a high level structured object.
     *
     * @param {string} json - a jsong string
     * @returns {TFaustJSON} a high level structured object describing a Faust processor
     */
    function createFaustJSON(json: string): TFaustJSON;

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
