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


interface OutputParamHandler { (path: string, value: number): void }
interface MetadataHandler { (key: string, value: number): void }

// Implemntation types
interface MonoDSP {


	fInChannels: Float32Array[];
	fOutChannels: Float32Array[];

	fInstance: Faust.Instance;

	getNumInputs(): number;
	getNumOutputs(): number;

	compute(inputs: Float32Array[], outputs: Float32Array[]): boolean;

	ctrlChange(chan: number, ctrl: number, value: number): void;
	pitchWheel(chan: number, value: number): void;

	setParamValue(path: string, value: number): void;
	getParamValue(path: string): number;

	getParams(): Array<string>;

	getJSON(): string;

}

interface PolyDSP extends MonoDSP {
}

// Public API
interface FaustAudioNode {

	setOutputParamHandler(handler: OutputParamHandler): void;
	getOutputParamHandler(): OutputParamHandler;
	metadata(handler: MetadataHandler): void;
	ctrlChange(chan: number, ctrl: number, value: number): void;
	pitchWheel(chan: number, value: number): void;
	setParamValue(path: string, value: number): void;
	getParamValue(path: string): number;
	getParams(): Array<string>;
	getJSON(): string;
	destroy(): void; // to do: check is this function is still really needed
}

interface FaustAudioPolyNode extends FaustAudioNode {
	keyOn(pitch: number, velocity: number): void;
	keyOff(pitch: number, velocity: number): void;
	allNotesOff(): void;

	//midiMessage(data: number[] | Uint8Array): void;
}

interface FaustWebAudioNode {
	compileMonoNode(context: BaseAudioContext, name: string, faust: LibFaust, dsp_content: string, args: string, scriptprocessor: boolean): Promise<FaustAudioNode>;
	compilePolyNode(context: BaseAudioContext, name: string, faust: LibFaust, dsp_content: string, args: string, voices: number, scriptprocessor: boolean): Promise<FaustAudioPolyNode>;

	createMonoNode(context: BaseAudioContext, name: string, module: Faust.Factory, scriptprocessor: boolean): Promise<FaustAudioNode>;
	createPolyNode(context: BaseAudioContext, name: string, module: Faust.Factory, voices: number, scriptprocessor: boolean): Promise<FaustAudioPolyNode>;
}
