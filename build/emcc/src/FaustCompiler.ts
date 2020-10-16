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

    // Public contructor
    export function createCompiler(engine: LibFaust) { return new CompilerImp(engine); }

    class CompilerImp implements Compiler {
        private fFaustEngine: LibFaust;
        private fErrorMessage: string;

        private intVec2intArray(vec: IntVector): Uint8Array {
            const size = vec.size();
            const ui8Code = new Uint8Array(size);
            for (let i = 0; i < size; i++) {
                ui8Code[i] = vec.get(i);
            }
            return ui8Code;
        }

        private async createDSPFactoryImp(name: string, dsp_code: string, args: string, poly: boolean): Promise<Factory | null> {
            try {
                // Can possibly raise an exception catched by the second catch()
                const faust_wasm = this.fFaustEngine.createDSPFactory(name, dsp_code, args, !poly);
                try {
                    const module = await WebAssembly.compile(this.intVec2intArray(faust_wasm.data));
                    return { cfactory: faust_wasm.cfactory, module: module, json: faust_wasm.json, poly: poly };
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

        expandDSP(name: string, dsp_code: string, args: string): string | null {
            try {
                return this.fFaustEngine.expandDSP(name, dsp_code, args);
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
