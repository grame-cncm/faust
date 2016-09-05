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
 
#ifndef WASM_DSP_AUX_H
#define WASM_DSP_AUX_H

#include <string>
#include <cstdlib>
#include "export.hh"
#include "faust/dsp/dsp.h"
#include "dsp_aux.hh"
#include "dsp_factory.hh"

using namespace std;

class EXPORT wasm_dsp : public dsp {};

class EXPORT wasm_dsp_factory : public dsp_factory, public faust_smartable {
    
    protected:
        
        dsp_factory_base* fFactory;
        
        virtual ~wasm_dsp_factory()
        {
            delete fFactory;
        }
        
    public:
        
        wasm_dsp_factory(dsp_factory_base* factory):fFactory(factory)
        {}
    
        std::string getName() { return fFactory->getName(); }
        
        std::string getSHAKey() { return fFactory->getSHAKey(); }
        void setSHAKey(std::string sha_key) { fFactory->setSHAKey(sha_key); }
        
        std::string getDSPCode() { return fFactory->getDSPCode(); }
        void setDSPCode(std::string code) { fFactory->setDSPCode(code); }
        
        wasm_dsp* createDSPInstance() { return nullptr; }
        
        void write(std::ostream* out, bool binary, bool small = false) { fFactory->write(out, binary, small); }
    
};

EXPORT wasm_dsp_factory* createWasmDSPFactoryFromFile(const string& filename, int argc, const char* argv[], string& error_msg);

EXPORT wasm_dsp_factory* createWasmDSPFactoryFromString(const string& name_app, const string& dsp_content, int argc, const char* argv[], string& error_msg);

EXPORT bool deleteWasmDSPFactory(wasm_dsp_factory* factory);

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * Create a Faust DSP asm.js module and additional helpers functions from a DSP source code as a file.
     *
     * @param filename - the DSP filename
     * @param argc - the number of parameters in argv array
     * @param argv - the array of parameters
     * @param error_msg - the error string to be filled, has to be 4096 characters long
     *
     * @return a valid WASM module and additional helpers functions as a string on success (to be deleted by the caller), otherwise a null pointer.
     */
    EXPORT const char* createWasmDSPFactoryFromFile(const char* filename, int argc, const char* argv[], char* error_msg);

     /**
     * Create a Faust DSP WASM module and additional helpers functions from a DSP source code.
     * 
     * @param name_app - the name of the Faust program
     * @param dsp_content - the Faust program as a string
     * @param argc - the number of parameters in argv array
     * @param argv - the array of parameters
     * @param error_msg - the error string to be filled, has to be 4096 characters long
     *
     * @return a valid WASM module and additional helpers functions as a string on success (to be deleted by the caller), otherwise a null pointer.
     */ 
    EXPORT const char* createWasmCDSPFactoryFromString(const char* name_app, const char* dsp_content, int argc, const char* argv[], char* error_msg);
    
    /**
     * Get the library version.
     * 
     * @return the library version as a static string.
     */
    EXPORT char* getCLibFaustVersion();
    
    /**
     * The free function to be used on memory returned by createWasmCDSPFactoryFromString.
     * 
     * @param ptr - the pointer to be deleted.
     */
    EXPORT void freeCDSP(void* ptr);
    
#ifdef __cplusplus
}
#endif

#endif
