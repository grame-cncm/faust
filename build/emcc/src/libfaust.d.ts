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

interface WasmModule { }

interface Factory {
	module: WasmModule;
	error: string;
}
interface Expand {
	dsp: string;
	shakey: string;
	error: string;
}
interface Aux {
	success: boolean;
	error: string;
}

interface IntVector { size(): number; get(i: number): number; }

interface FaustWasm {
	data: IntVector;
	json: string;
}

interface LibFaust {
	version(): string;

	createDSPFactory(name_app: string, dsp_content: string, args: string, internal_memory: boolean): Factory;
	expandDSP(name_app: string, dsp_content: string, args: string): Expand
	generateAuxFiles(name_app: string, dsp_content: string, args: string): Aux;
	deleteAllDSPFactories(): void;

	getWasmModule(module: WasmModule): FaustWasm;
	freeWasmModule(module: WasmModule): void;

	cleanupAfterException(): void;
	getErrorAfterException(): string;
}
