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

///<reference path="FaustCompiler.ts"/>
///<reference path="FaustUtilities.d.ts"/>

namespace Faust {

    // Public contructor
    export function createSVGDiagrams(libfaust: LibFaust, name: string, dsp_code: string, args: string) {
        return new SVGDiagramsImp(libfaust, name, dsp_code, args);
    }

    class SVGDiagramsImp implements SVGDiagrams {
        private fSuccess: boolean;
        private fError: string;
        private fFolder: string;
        private fLibFaust: LibFaust;

        private debug(path: string) {
            console.log("getSVG file: " + path);
            let content = this.fLibFaust.module().FS.readdir(".");
            console.log("getSVG dir: " + content);
        }

        constructor(libfaust: LibFaust, name: string, dsp_code: string, args: string) {
            this.fLibFaust = libfaust;
            let compiler = createCompiler(libfaust);
            this.fSuccess = compiler.generateAuxFiles(name, dsp_code, "-lang wasm -svg " + args);
            this.fError = (this.fSuccess) ? "" : compiler.getErrorMessage();
            this.fFolder = name + "-svg";
        }

        error(): string { return this.fError; }
        success(): boolean { return this.fSuccess; }

        getSVG(name?: string): string {
            if (!name) name = this.fFolder + "/process.svg";
            if (this.fSuccess) {
                let path = name;
                try {
                    // this.debug(path);
                    return this.fLibFaust.module().FS.readFile(path, { encoding: "utf8" }) as string;
                } catch (e) {
                    console.log("SVGDiagrams: can't read file " + path);
                    return "";
                }
            } else {
                return "SVGDiagrams: not a valid diagram: " + this.fError;
            }
        }
    }
}


