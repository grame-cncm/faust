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
        private fEngine: Faust.LibFaust;

        constructor(engine: Faust.LibFaust, name_app: string, dsp_content: string, args: string) {
            this.fEngine = engine;
            let compiler = new Faust.Compiler(engine);
            let result = compiler.generateAuxFiles(name_app, dsp_content, "-lang wasm -svg " + args);
            this.fSuccess = result.success;
            this.fError = result.error;
            this.fFolder = name_app + "-svg";
        }

        error(): string { return this.fError; }
        success(): boolean { return this.fSuccess; }

        private debug(path: string) {
            console.log("getSVG file: " + path);
            let content = this.fEngine.module().FS.readdir(".");
            console.log("getSVG dir: " + content);
        }

        getSVG(name?: string): string {
            if (!name) name = this.fFolder + "/process.svg";
            if (!this.fSuccess)
                return "SVGDiagrams: not a valid diagram: " + this.fError;

            let path = name;
            try {
                // this.debug(path);
                return this.fEngine.module().FS.readFile(path, { encoding: "utf8" }) as string;
            }
            catch (e) {
                console.log("SVGDiagrams: can't read file " + path);
                return "";
            }
        }
    }
}


