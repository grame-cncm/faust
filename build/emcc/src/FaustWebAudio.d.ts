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

interface OutputParamHandler 	{ (path: string, value: number) : void }
interface MetadataHandler 		{ (key: string, value: number) : void }

interface FaustAudioNode {  // extends AudioNode { : pose problème, il manque des fonctions à implémenter pour AudioNode
	setOutputParamHandler (handler: OutputParamHandler) : void;
	getOutputParamHandler () : OutputParamHandler;
	metadata(handler: MetadataHandler) : void;
	ctrlChange(chan: number, ctrl: number, value: number) : void;
	pitchWheel(chan: number, value: number) : void;
	setParamValue(path: string, value: number) : void;
	getParamValue(path: string) : number;
	//getParams() : any;   // returns an array of paths
	getJSON() : string;
	destroy() : void; // to check is this function is still really needed
}

interface FaustAudioPolyNode extends FaustAudioNode {
	keyOn(key: number, vel: number) : void;
	keyOff(key: number, vel: number) : void;
	allNotesOff() : void;
}

interface FaustWebAudioNode {
	compileMonoNode(faust: LibFaust, dsp_content: string, args: string, scriptprocessor: boolean) 					: Promise<FaustAudioNode>;
	compilePolyNode(faust: LibFaust, dsp_content: string, args: string, voices: number, scriptprocessor: boolean)	: Promise<FaustAudioPolyNode>;

	createMonoNode(module: FaustFactory, scriptprocessor: boolean) 					: Promise<FaustAudioNode>;
	createPolyNode(module: FaustFactory, voices: number, scriptprocessor: boolean) 	: Promise<FaustAudioPolyNode>;
}
