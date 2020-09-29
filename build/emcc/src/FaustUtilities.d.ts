/************************************************************************
 This file describes the high level interface to the Faust compiler.
 ************************************************************************/


declare namespace Faust {

    interface SVGDiagrams {

        /**
         * The Faust.Compiler constructor.
         * @param {string} name - an arbitrary name for the faust module
         * @param {string} code - faust dsp code
         * @param {string} args - the compiler options, only svg specific options are meaningfull (automatically appends -svg)
         * @param {Faust.Compiler} compiler - an instance of the faust compiler
         */
        new(engine: LibFaust, name_app: string, dsp_content: string, args: string): SVGDiagrams;

 
        /**
         * Generates auxiliary files from faust code. The output depends on the compiler options.
         *
         * @param {string} name - the svg file name (default to "process.svg")
         * @returns {string} the svg diagram as a string
        */
        getSVG(name? : string): string;
    }

}
