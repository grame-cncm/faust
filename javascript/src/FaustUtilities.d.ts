/************************************************************************
 ************************************************************************
    FAUST compiler and web audio interface
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

    /**
     * The SVGDiagrams constructor.
     * @param {LibFaust} engine - an instance of the Faust engine 
     * @param {string} name - an arbitrary name for the Faust module
     * @param {string} dsp_code - Faust dsp code
     * @param {string} args - the compiler options, only svg specific options are meaningfull (automatically appends -svg)
     */
    interface createSVGDiagrams { (engine: LibFaust, name: string, dsp_code: string, args: string): SVGDiagrams }

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
