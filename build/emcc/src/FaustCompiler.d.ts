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

interface InstanceAPI {
	compute(count: number, inputs: number, output: number): void;
	getNumInputs(): number;
	getNumOutputs(): number;
	getParamValue(index: number): number;
	getSampleRate(): number;
	init(sampleRate: number): void;
	instanceClear(): void;
	instanceConstants(sampleRate: number): void;
	instanceInit(sampleRate: number): void;
	instanceResetUserInterface(): void;
	setParamValue(index: number, value: number): void;
}

interface Instance {
	instance: WebAssembly.Instance;
	api: InstanceAPI;
	json: string;
}

interface Factory {
	module: WebAssembly.Module;
	poly: boolean;
}

interface ExpandOut extends Expand { error: string; }
interface AuxOut  { 
	success: boolean;
	error: string; 
}

interface Compiler {

	new(engine: LibFaust): Compiler;

	version(): string;

	createDSPFactory(name_app: string, dsp_content: string, args: string, poly: boolean): Promise<Factory>;
	createDSPInstance(module: Factory): Promise<Instance>;

	expandDSP(name_app: string, dsp_content: string, args: string): ExpandOut
	generateAuxFiles(name_app: string, dsp_content: string, args: string): AuxOut;
}

}
