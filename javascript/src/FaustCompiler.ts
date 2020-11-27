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


///<reference path="FaustCompiler.d.ts"/>
/*///<reference path="../node_modules/js-sha256/index.d.ts"/>*/

namespace Faust {

    export function createFaustJSON(json: string): TFaustJSON { return JSON.parse(json); }
    export function createCompiler(engine: LibFaust) { return new CompilerImp(engine); }

    class CompilerImp implements Compiler {
        private fFaustEngine: LibFaust;
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
                CompilerImp.gFactories.forEach((value, key) => {
                    // Cleanup C++ side of each factory
                    this.deleteDSPFactory(value);
                });
                CompilerImp.gFactories.clear();
            }

            let sha_key = name + dsp_code + args + ((poly) ? "poly" : "mono");
            console.log(sha_key);
            //let sha_key = sha256.Hash(name + dsp_code + args + ((poly) ? "poly" : "mono"));

            // If code is already compiled, return the cached factory
            if (CompilerImp.gFactories.has(sha_key)) {
                console.log("Use cached factory");
                return CompilerImp.gFactories.get(sha_key) as Factory;
            } else {
                try {
                    // Can possibly raise an C++ exception catched by the second catch()
                    const faust_wasm = this.fFaustEngine.createDSPFactory(name, dsp_code, args, !poly);
                    try {
                        const module = await WebAssembly.compile(this.intVec2intArray(faust_wasm.data));
                        const factory = { cfactory: faust_wasm.cfactory, module: module, json: faust_wasm.json, poly: poly }
                        // Keep the compiled factory in the cache
                        console.log("Compile factory");
                        CompilerImp.gFactories.set(sha_key, factory);
                        return factory;
                    } catch (e) {
                        console.error(e);
                        return null;
                    }
                } catch {
                    this.fErrorMessage = this.fFaustEngine.getErrorAfterException();
                    console.error("=> exception raised while running createDSPFactory: " + this.fErrorMessage);
                    this.fFaustEngine.cleanupAfterException();
                    return null;
                }
            }
        }

        // Public API
        constructor(engine: LibFaust) {
            this.fFaustEngine = engine;
            this.fErrorMessage = "";
        }

        version(): string { return this.fFaustEngine.version(); }

        getErrorMessage(): string { return this.fErrorMessage; }

        async createMonoDSPFactory(name: string, dsp_code: string, args: string): Promise<Factory | null> {
            return this.createDSPFactoryImp(name, dsp_code, args, false);
        }

        async createPolyDSPFactory(name: string, dsp_code: string, args: string): Promise<Factory | null> {
            return this.createDSPFactoryImp(name, dsp_code, args, true);
        }

        deleteDSPFactory(factory: Factory): void {
            this.fFaustEngine.deleteDSPFactory(factory.cfactory);
        }

        expandDSP(dsp_code: string, args: string): string | null {
            try {
                return this.fFaustEngine.expandDSP("FaustDSP", dsp_code, args);
            } catch {
                this.fErrorMessage = this.fFaustEngine.getErrorAfterException();
                console.error("=> exception raised while running expandDSP: " + this.fErrorMessage);
                this.fFaustEngine.cleanupAfterException();
                return null;
            }
        }

        generateAuxFiles(name: string, dsp_code: string, args: string): boolean {
            try {
                return this.fFaustEngine.generateAuxFiles(name, dsp_code, args);
            } catch {
                this.fErrorMessage = this.fFaustEngine.getErrorAfterException();
                console.error("=> exception raised while running generateAuxFiles: " + this.fErrorMessage);
                this.fFaustEngine.cleanupAfterException();
                return false;
            }
        }

        deleteAllDSPFactories(): void {
            this.fFaustEngine.deleteAllDSPFactories();
        }
    }
}
