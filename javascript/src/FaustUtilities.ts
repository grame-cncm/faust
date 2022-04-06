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
///<reference path="FaustUtilities.d.ts"/>


// Public contructor
function createSVGDiagrams(compiler: Compiler, name: string, dsp_code: string, args: string) {
    return new SVGDiagramsImp(compiler, name, dsp_code, args);
}
if (typeof module === 'object' && module.exports) {
    module.exports = { createSVGDiagrams };
}


class SVGDiagramsImp implements SVGDiagrams {
    private fSuccess: boolean;
    private fError: string;
    private fFolder: string;

    private debug(path: string) {
        console.log("getSVG file: " + path);
        let content = WFS.readdir(".");
        console.log("getSVG dir: " + content);
    }

    constructor(compiler: Compiler, name: string, dsp_code: string, args: string) {
        this.fSuccess = compiler.generateAuxFiles(name, dsp_code, "-lang wasm -svg " + args);
        this.fError = (this.fSuccess) ? "" : compiler.getErrorMessage();
        this.fFolder = name + "-svg";
    }

    error(): string     { return this.fError; }
    success(): boolean  { return this.fSuccess; }
    getFolder(): string { return this.fFolder; }

    getSVG(name?: string): string {
        if (!name) name = this.fFolder + "/process.svg";
        if (this.fSuccess) {
            let path = name;
            try {
                // this.debug(path);
                return WFS.readFile(path, { encoding: "utf8" }) as string;
            } catch (e) {
                console.log("SVGDiagrams: can't read file " + path);
                return "";
            }
        } else {
            return "SVGDiagrams: not a valid diagram: " + this.fError;
        }
    }

    getSVGs(module: any, f: SVGCallback) {
        let content = module.FS.readdir(this.fFolder) as Array<string>;
        content.forEach (element => {
            if ((element !== '.') && (element !=='..'))
                f(element, module.FS.readFile(this.fFolder+"/"+element, { encoding: "utf8" }) as string); 
        });
    }
}

