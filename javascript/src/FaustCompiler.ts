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

///<reference path="FaustCompiler.d.ts"/>

namespace Faust {

    export function createFaustJSON(json: string): TFaustJSON { return JSON.parse(json); }
    export function createCompiler(libfaust: LibFaust) { return new CompilerImp(libfaust); }

    class CompilerImp implements Compiler {
        private fLibFaust: LibFaust;
        private fErrorMessage: string;
        private static gFactories: Map<string, Factory> = new Map<string, Factory>();

        private intVec2intArray(vec: IntVector): Uint8Array {
            const size = vec.size();
            const ui8Code = new Uint8Array(size);
            for (let i = 0; i < size; i++) {
                ui8Code[i] = vec.get(i);
            }
            return ui8Code;
        }

        private async createDSPFactoryImp(name: string, dsp_code: string, args: string, poly: boolean): Promise<Factory | null> {

            // Cleanup the cache
            if (CompilerImp.gFactories.size > 10) {
                CompilerImp.gFactories.clear();
            }

            // If code is already compiled, return the cached factory
            let sha_key = hash(name + dsp_code + args + ((poly) ? "poly" : "mono"));
            if (CompilerImp.gFactories.has(sha_key)) {
                return CompilerImp.gFactories.get(sha_key) as Factory;
            } else {
                try {
                    // Can possibly raise a C++ exception catched by the second catch()
                    const faust_wasm = this.fLibFaust.createDSPFactory(name, dsp_code, args, !poly);
                    try {
                        const code = this.intVec2intArray(faust_wasm.data);
                        const module = await WebAssembly.compile(code);
                        const factory = { cfactory: faust_wasm.cfactory, code: code, module: module, json: faust_wasm.json, poly: poly }
                        // Factory C++ side can be deallocated immediately
                        this.deleteDSPFactory(factory);
                        // Keep the compiled factory in the cache
                        CompilerImp.gFactories.set(sha_key, factory);
                        return factory;
                    } catch (e) {
                        console.error(e);
                        return null;
                    }
                } catch {
                    this.fErrorMessage = this.fLibFaust.getErrorAfterException();
                    console.error("=> exception raised while running createDSPFactory: " + this.fErrorMessage);
                    this.fLibFaust.cleanupAfterException();
                    return null;
                }
            }
        }

        // Public API
        constructor(libfaust: LibFaust) {
            this.fLibFaust = libfaust;
            this.fErrorMessage = "";
        }

        version(): string { return this.fLibFaust.version(); }

        getErrorMessage(): string { return this.fErrorMessage; }

        async createMonoDSPFactory(name: string, dsp_code: string, args: string): Promise<Factory | null> {
            return this.createDSPFactoryImp(name, dsp_code, args, false);
        }

        async createPolyDSPFactory(name: string, dsp_code: string, args: string): Promise<Factory | null> {
            return this.createDSPFactoryImp(name, dsp_code, args, true);
        }

        deleteDSPFactory(factory: Factory): void {
            this.fLibFaust.deleteDSPFactory(factory.cfactory);
            factory.cfactory = 0;
        }

        expandDSP(dsp_code: string, args: string): string | null {
            try {
                return this.fLibFaust.expandDSP("FaustDSP", dsp_code, args);
            } catch {
                this.fErrorMessage = this.fLibFaust.getErrorAfterException();
                console.error("=> exception raised while running expandDSP: " + this.fErrorMessage);
                this.fLibFaust.cleanupAfterException();
                return null;
            }
        }

        generateAuxFiles(name: string, dsp_code: string, args: string): boolean {
            try {
                return this.fLibFaust.generateAuxFiles(name, dsp_code, args);
            } catch {
                this.fErrorMessage = this.fLibFaust.getErrorAfterException();
                console.error("=> exception raised while running generateAuxFiles: " + this.fErrorMessage);
                this.fLibFaust.cleanupAfterException();
                return false;
            }
        }

        deleteAllDSPFactories(): void {
            this.fLibFaust.deleteAllDSPFactories();
        }
    }
}
