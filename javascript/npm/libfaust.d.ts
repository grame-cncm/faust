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

/*
    This file describes the API to instantiate a low level Faust library.
    This library provides access to the Faust compiler but the compiler interface
    is not public. Thus LibFaust is an opaque reference that is required by
    higher level APIs.
*/

declare namespace Faust {

    type FaustModule = any;    
    type TFaustInfoType = "help" | "version";

    interface LibFaust {

        /**
         * Return the Faust compiler version.
         * 
         * @returns {string} the version
         */
        version(): string;

        /**
         * Get info about the embedded Faust engine
         * @param {string} what - the requested info
         */
        getInfos( what: TFaustInfoType ): string;
    }

    /**
     * Instantiates the Faust Library.
     *
     * @param {string} module - the Faust Wasm module, typically retrieved with an async call to FaustModule()
     * @returns {LibFaust} an instance of Faust library
     */

    function createLibFaust (module: FaustModule): LibFaust | null;
}
