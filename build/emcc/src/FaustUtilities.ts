/************************************************************************
 This file describes the high level interface to the Faust compiler.
 ************************************************************************/

///<reference path="FaustCompiler.d.ts"/>
///<reference path="FaustUtilities.d.ts"/>

namespace Faust {

    export class SVGDiagrams implements SVGDiagrams {
        private fSuccess: boolean;
        private fError: string;
        private fFolder: string;
        private fEngine: LibFaust;

        private debug(path: string) {
            console.log("getSVG file: " + path);
            let content = this.fEngine.module().FS.readdir(".");
            console.log("getSVG dir: " + content);
        }

        constructor(engine: LibFaust, name_app: string, dsp_code: string, args: string) {
            this.fEngine = engine;
            let compiler = new Compiler(engine);
            this.fSuccess = compiler.generateAuxFiles(name_app, dsp_code, "-lang wasm -svg " + args);
            this.fError = (this.fSuccess) ? "" : compiler.getErrorMessage();
            this.fFolder = name_app + "-svg";
        }

        error(): string { return this.fError; }
        success(): boolean { return this.fSuccess; }

        getSVG(name?: string): string {
            if (!name) name = this.fFolder + "/process.svg";
            if (this.fSuccess) {
                let path = name;
                try {
                    // this.debug(path);
                    return this.fEngine.module().FS.readFile(path, { encoding: "utf8" }) as string;
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


