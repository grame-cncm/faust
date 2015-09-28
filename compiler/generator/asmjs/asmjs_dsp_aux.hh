/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2014 GRAME, Centre National de Creation Musicale
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
 
#ifndef ASMJS_DSP_AUX_H
#define ASMJS_DSP_AUX_H

#include <string>
#include <cstdlib>
#include "export.hh"

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

     /**
     * Create a Faust DSP asm.js module and additional helpers functions from a DSP source code. 
     * 
     * @param name_app - the name of the Faust program
     * @param dsp_content - the Faust program as a string
     * @param argc - the number of parameters in argv array
     * @param argv - the array of parameters
     * @param error_msg - the error string to be filled, has to be 256 characters long
     *
     * @return a valid DSP asm.js module and additional helpers functions as a string on success (to be deleted by the caller), otherwise a null pointer.
     */ 
    EXPORT const char* createAsmCDSPFactoryFromString(const char* name_app, const char* dsp_content, int argc, const char* argv[], char* error_msg);
    
    /**
     * Get the library version.
     * 
     * @return the library version as a static string.
     */
    EXPORT char* getCLibFaustVersion();
    
    /**
     * The free function to be used on memory returned by createAsmCDSPFactoryFromString.
     * 
     * @param ptr - the pointer to be deleted.
     */
    EXPORT void freeCDSP(void* ptr);
    
#ifdef __cplusplus
}
#endif

#endif
