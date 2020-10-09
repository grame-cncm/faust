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
///<reference path="FaustCompiler.d.ts"/>

namespace Faust {

    export class Compiler {
        private fFaustEngine: Faust.LibFaust;

        private intVec2intArray(vec: IntVector): Uint8Array {
            const size = vec.size();
            const ui8Code = new Uint8Array(size);
            for (let i = 0; i < size; i++) {
                ui8Code[i] = vec.get(i);
            }
            return ui8Code;
        }

        // Public API
        constructor(engine?: Faust.LibFaust) {
            this.fFaustEngine = engine;
        }
        version(): string { return this.fFaustEngine.version(); }

        async createDSPFactory(name_app: string, dsp_code: string, args: string, poly: boolean): Promise<Faust.Factory> {
            try {
                const factory = this.fFaustEngine.createDSPFactory(name_app, dsp_code, args, !poly);
                const wasm = this.fFaustEngine.getWasmModule(factory);
                const module = await WebAssembly.compile(this.intVec2intArray(wasm.data));
                return { module: module, json: wasm.json, poly: poly };
            } catch {
                const error = this.fFaustEngine.getErrorAfterException();
                console.log("=> exception raised while running createDSPFactory: " + error);
                this.fFaustEngine.cleanupAfterException();
                return null;
            }
        }

        async loadDSPFactory(wasm_path: string, json_path: string, poly: boolean): Promise<Faust.Factory> {
            try {
                const wasm_file = await fetch(wasm_path);
                const wasm_buffer = await wasm_file.arrayBuffer();
                const module = await WebAssembly.compile(wasm_buffer);
                const json_file = await fetch(json_path);
                const json = await json_file.text();
                return { module: module, json: json, poly: poly };
            } catch (e) {
                console.log("=> exception raised while running loadDSPFactory: " + e);
                return null;
            }
        }

        expandDSP(name_app: string, dsp_code: string, args: string) {
            try {
                const out = this.fFaustEngine.expandDSP(name_app, dsp_code, args);
                return { dsp: out.dsp, shakey: out.shakey, error: "" };
            } catch {
                const error = this.fFaustEngine.getErrorAfterException();
                console.log("=> exception raised while running expandDSP: " + error);
                this.fFaustEngine.cleanupAfterException();
                return { dsp: "", shakey: "", error: error };
            }
        }

        generateAuxFiles(name_app: string, dsp_code: string, args: string) {
            try {
                const done = this.fFaustEngine.generateAuxFiles(name_app, dsp_code, args);
                return { success: done, error: "" };
            } catch {
                const error = this.fFaustEngine.getErrorAfterException();
                console.log("=> exception raised while running generateAuxFiles: " + error);
                this.fFaustEngine.cleanupAfterException();
                return { success: false, error: error };
            }
        }

        deleteAllDSPFactories() {
            this.fFaustEngine.deleteAllDSPFactories();
        }
    }

    export class Factory implements Faust.Factory {
        constructor(module: WebAssembly.Module, json: string, poly: boolean) {
            this.module = module;
            this.json = json;
            this.poly = poly;
        }
    }
}
