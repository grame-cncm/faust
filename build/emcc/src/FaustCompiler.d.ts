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


interface FaustInstanceAPI {
	compute (count: number, inputs: number, output: number) : void;
	getNumInputs() : number;
	getNumOutputs() : number;
	getParamValue(index: number) : number;
	getSampleRate() : number;
	init(sampleRate: number) : void;
	instanceClear() : void;
	instanceConstants(sampleRate: number) : void;
	instanceInit(sampleRate: number) : void;
	instanceResetUserInterface() : void;
	setParamValue(index: number, value: number) : void;
}

interface FaustInstance {
 	instance  : WebAssembly.Instance;
 	api       : FaustInstanceAPI;
}

interface FaustFactory {
	module  : WebAssembly.Module;
	poly    : boolean;
}

interface FaustCompiler {

	new(engine: LibFaust) : FaustCompiler;

	version() : string;

	createDSPFactory(name_app: string, dsp_content: string, args: string, poly: boolean) : Promise<FaustFactory>;
	createDSPInstance(module: FaustFactory) : Promise<FaustInstance>;

	expandDSP(name_app: string, dsp_content: string, args: string) : Expand
	generateAuxFiles(name_app: string, dsp_content: string, args: string) : Aux;
}
