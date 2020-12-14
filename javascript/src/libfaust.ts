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

///<reference path="libfaust.d.ts"/>

namespace Faust {

    export var FS: FS;

    class LibFaustImp implements LibFaust {
        private fModule: FaustModule;
        private fCompiler: LibFaust;
        private fFileSystem: FS;

        constructor(module: FaustModule) {
            this.fModule = module;
            this.fCompiler = new module.libFaustWasm();
            this.fFileSystem = this.fModule.FS;
            FS = this.fFileSystem;
        }

        version(): string { return this.fCompiler.version(); }

        createDSPFactory(name: string, dsp_code: string, args: string, internal_memory: boolean): FaustWasm { return this.fCompiler.createDSPFactory(name, dsp_code, args, internal_memory); }

        deleteDSPFactory(cfactory: number): void { this.fCompiler.deleteDSPFactory(cfactory); }

        expandDSP(name: string, dsp_code: string, args: string): string { return this.fCompiler.expandDSP(name, dsp_code, args); }

        generateAuxFiles(name: string, dsp_code: string, args: string): boolean { return this.fCompiler.generateAuxFiles(name, dsp_code, args); }

        deleteAllDSPFactories() { this.fCompiler.deleteAllDSPFactories(); }

        getErrorAfterException(): string { return this.fCompiler.getErrorAfterException(); }

        cleanupAfterException() { this.fCompiler.cleanupAfterException(); }

        module(): FaustModule { return this.fModule; }
        fs(): FS { return this.fFileSystem; }

        getInfos(what: TFaustInfoType) { return this.fCompiler.getInfos(what); }

        toString() { return "LibFaust module: " + this.fModule + " compiler: " + this.fCompiler; }
    }

    export function createLibFaust(module: FaustModule): LibFaust | null {
        return (!module || (typeof (module) == 'undefined')) ? null : new LibFaustImp(module);
    }
}
