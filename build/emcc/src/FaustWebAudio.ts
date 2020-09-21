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

///<reference path="libfaust.d.ts"/>
///<reference path="FaustCompiler.ts"/>
///<reference path="FaustWebAudio.d.ts"/>

class FaustAudioNodeImpl extends AudioNode implements FaustAudioNode {

	setOutputParamHandler(handler: OutputParamHandler) { }
	getOutputParamHandler() { return function (path: string, value: number) { } }

	metadata(handler: MetadataHandler) { return function (path: string, value: number) { } }

	ctrlChange(chan: number, ctrl: number, value: number) { }
	pitchWheel(chan: number, value: number) { }

	setParamValue(path: string, value: number) { }
	getParamValue(path: string) { return 0; }
	getParams() 				{ return new Array<string>(); }

	getJSON() { return ""; }
	destroy() { } // to do: check is this function is still really needed
}


class FaustAudioPolyNodeImpl extends FaustAudioNodeImpl implements FaustAudioPolyNode {
	keyOn(key: number, vel: number) { }
	keyOff(key: number, vel: number) { }
	allNotesOff() { }
}


class FaustWebAudioNode {
	private createDSPFactory(faust: LibFaust, dsp_content: string, args: string, poly: boolean): Promise<FaustFactory> {
		let compiler = new FaustCompiler(faust);
		return compiler.createDSPFactory("faustdsp", dsp_content, args, poly);
	}

	compileMonoNode(faust: LibFaust, dsp_content: string, args: string, scriptprocessor: boolean): Promise<FaustAudioNode> {
		return this.createDSPFactory(faust, dsp_content, args, false).then(module => {
			return this.createMonoNode(module, scriptprocessor);
		});
	}

	compilePolyNode(faust: LibFaust, dsp_content: string, args: string, voices: number, scriptprocessor: boolean): Promise<FaustAudioPolyNode> {
		return this.createDSPFactory(faust, dsp_content, args, true).then(module => {
			return this.createPolyNode(module, voices, scriptprocessor);
		});
	}

	createMonoNode(module: FaustFactory, scriptprocessor: boolean): Promise<FaustAudioNode> {
		return null;
	}
	createPolyNode(module: FaustFactory, voices: number, scriptprocessor: boolean): Promise<FaustAudioPolyNode> {
		return null;
	}
}
