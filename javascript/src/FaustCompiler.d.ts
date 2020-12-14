
///<reference path="libfaust.d.ts"/>

declare namespace Faust {

    type AudioBuffer = number;
    type DSP = number;

    type TFaustJSON = {
        name: string;
        filename: string;
        compile_options: string;
        include_pathnames: string[];
        inputs: number;
        outputs: number;
        size: number;
        version: string;
        library_list: string[];
        meta: { [key: string]: string }[];
        ui: TFaustUI;
    };

    type TFaustUI = TFaustUIGroup[];
    type TFaustUIItem = TFaustUIInputItem | TFaustUIOutputItem | TFaustUIGroup;
    type TFaustUIInputItem = {
        type: TFaustUIInputType;
        label: string;
        address: string;
        index: number;
        init: number;
        min: number;
        max: number;
        step: number;
        meta?: TFaustUIMeta[];
    };

    type TFaustUIOutputItem = {
        type: TFaustUIOutputType;
        label: string;
        address: string;
        index: number;
        min: number;
        max: number;
        meta: TFaustUIMeta[];
    };

    type TFaustUIMeta = {
        [order: number]: string;
        style: string; // "knob" | "menu{'Name0':value0;'Name1':value1}" | "radio{'Name0':value0;'Name1':value1}" | "led";
        unit: string;
        scale: "linear" | "exp" | "log";
        tooltip: string;
        hidden: string;
        [key: string]: string;
    }

    type TFaustUIGroupType = "vgroup" | "hgroup" | "tgroup";
    type TFaustUIOutputType = "hbargraph" | "vbargraph";
    type TFaustUIInputType = "vslider" | "hslider" | "button" | "checkbox" | "nentry";
    type TFaustUIGroup = {
        type: TFaustUIGroupType;
        label: string;
        items: TFaustUIItem[];
    }
    type TFaustUIType = TFaustUIGroupType | TFaustUIOutputType | TFaustUIInputType;

    /**
     * The Factory structure.
     * cfactory: a "pointer" (as an integer) on the internal C++ factory 
     * code: the WASM code as a binary array
     * module: the compule WASM module
     * json: the compiled DSP JSON description
     * poly: whether the factory is a polyphonic one or not
     */
    interface Factory {
        cfactory: number;
        code: Uint8Array;
        module: WebAssembly.Module;
        json: string;
        poly: boolean;
    }

    /**
     * The Compiler constructor.
     * 
     * @param {LibFaust} engine - an instance of the low level engine, actually a libFaustWasm instance of FaustModule
     * @return the created compiler object 
     */

    interface Compiler {

        /**
         * Gives the Faust compiler version.
         * @return {string} a version string
         */
        version(): string;

        /**
        * Gives the last compilation error.
        * @return {string} an error string
        */
        getErrorMessage(): string;

        /**
         * Create a wasm factory from Faust code i.e. wasm compiled code, to be used to create monophonic instances. 
         * This function is running asynchronously.
         *
         * @param {string} name - an arbitrary name for the Faust factory
         * @param {string} dsp_code - Faust dsp code
         * @param {string} args - the compiler options
         * @returns {Promise<Factory | null>} returns the wasm factory
         */
        createMonoDSPFactory(name: string, dsp_code: string, args: string): Promise<Factory | null>;

        /**
         * Create a wasm factory from Faust code i.e. wasm compiled code, to be used to create polyphonic instances. 
         * This function is running asynchronously.
         *
         * @param {string} name - an arbitrary name for the Faust factory
         * @param {string} dsp_code - Faust dsp code
         * @param {string} args - the compiler options
         * @returns {Promise<Factory | null>} returns the wasm factory
         */
        createPolyDSPFactory(name: string, dsp_code: string, args: string): Promise<Factory | null>;

        /**
         * Delete a dsp factory.
         *
         * @param {Factory} factory - the factory to be deleted
         */
        deleteDSPFactory(factory: Factory): void;

        /**
         * Expand Faust code i.e. linearize included libraries.
         *
         * @param {string} dsp_code - Faust dsp code
         * @param {string} args - the compiler options
         * @returns {interface} returns the expanded dsp code
         */
        expandDSP(dsp_code: string, args: string): string | null

        /**
         * Generates auxiliary files from Faust code. The output depends on the compiler options.
         *
         * @param {string} name - an arbitrary name for the Faust module
         * @param {string} dsp_code - Faust dsp code
         * @param {string} args - the compiler options
         * @returns {boolean} whether the generation actually succeded
        */
        generateAuxFiles(name: string, dsp_code: string, args: string): boolean;

        /**
         * Delete all factories.
        */
        deleteAllDSPFactories(): void;
    }

}

// Moved at the end of the file to please Visual Studio code completion tools.

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
