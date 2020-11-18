
/**
 * This interface describes the type of the javascript function called by the svg diagram components.
 * This function is called on user clicks when a diagram component has sub-diagrams.
 * The function name is build using the name_app parameter passed to the SVGDiagram constructor as follow:
 *     <function_name> = name + "svg" 
 * It's the user responsibility to instanciate this function e.g.
 * when you create a diagram names 'myEcho':
 *   var myEchosvg = (path) => { any code to handle the sub diagram };

 * @param {string} path - the full path of the sub-diagram file
 */
interface FaustSVGLinkHandler { (path: string): void }

declare namespace Faust {

    interface SVGDiagrams {

        /**
         * Generates auxiliary files from Faust code. The output depends on the compiler options.
         *
         * @param {string} name - the svg file name (default to "process.svg")
         * @returns {string} the svg diagram as a string
        */
        getSVG(name?: string): string;

        error(): string;

        success(): boolean;
    }
}
