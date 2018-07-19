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

#include <cstdlib>
#include <string>

#include "dsp_aux.hh"
#include "dsp_factory.hh"
#include "export.hh"
#include "faust/dsp/dsp.h"

class JSONUIDecoder;
class dsp_factory_base;

// The C++ side version of compiled wasm code

class EXPORT wasm_dsp : public dsp {
    private:
        dsp_factory_base* fFactory;
        JSONUIDecoder* fDecoder;
        int fDSP;   // Index of JavaScript DSP instance
    
    public:
        wasm_dsp():fFactory(nullptr), fDecoder(nullptr), fDSP(-1) {}
        wasm_dsp(dsp_factory_base* factory, int dsp);
        virtual ~wasm_dsp();
    
        virtual int getNumInputs();
        
        virtual int getNumOutputs();
    
        virtual void buildUserInterface(UI* ui_interface);
    
        virtual int getSampleRate();
        
        virtual void init(int samplingRate);
        
        virtual void instanceInit(int samplingRate);
        
        virtual void instanceConstants(int samplingRate);
        
        virtual void instanceResetUserInterface();
        
        virtual void instanceClear();
        
        virtual wasm_dsp* clone();
        
        virtual void metadata(Meta* m);
   
        virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
    
        virtual void computeJS(int count, uintptr_t input, uintptr_t output);
    
        virtual void computeJSTest(int count);
};

class EXPORT wasm_dsp_factory : public dsp_factory, public faust_smartable {
   protected:
    dsp_factory_base* fFactory;
    int fModule;    // Index of JavaScript DSP module

   public:
    wasm_dsp_factory() {}
    wasm_dsp_factory(dsp_factory_base* factory);
    
    virtual ~wasm_dsp_factory();
  
    std::string getName();

    std::string getSHAKey();
    void        setSHAKey(std::string sha_key);

    std::string getDSPCode();
    void        setDSPCode(std::string code);

    wasm_dsp* createDSPInstance();

    virtual std::vector<std::string> getDSPFactoryLibraryList() { return fFactory->getDSPFactoryLibraryList(); }
    virtual std::vector<std::string> getDSPFactoryIncludePathnames()
    {
        return fFactory->getDSPFactoryIncludePathnames();
    }

    void                setMemoryManager(dsp_memory_manager* manager);
    dsp_memory_manager* getMemoryManager();

    void write(std::ostream* out, bool binary, bool small = false);
    void writeAux(std::ostream* out, bool binary, bool small = false);

    std::string getBinaryCode();
    
    static int createModuleFromString(const std::string& code);
    
    static wasm_dsp_factory* createWasmDSPFactoryFromString2(const std::string& name_app, const std::string& dsp_content,
                                                             const std::vector<std::string>& argv, bool internal_memory);
    
    static std::string gErrorMessage;
    
    static const std::string& getErrorMessage();
  
};

EXPORT wasm_dsp_factory* createWasmDSPFactoryFromFile(const std::string& filename, int argc, const char* argv[],
                                                      std::string& error_msg, bool internal_memory);

EXPORT wasm_dsp_factory* createWasmDSPFactoryFromString(const std::string& name_app, const std::string& dsp_content, int argc,
                                                        const char* argv[], std::string& error_msg, bool internal_memory);

EXPORT bool deleteWasmDSPFactory(wasm_dsp_factory* factory);

EXPORT wasm_dsp_factory* readWasmDSPFactoryFromMachine(const std::string& machine_code);

EXPORT std::string writeWasmDSPFactoryToMachine(wasm_dsp_factory* factory);

EXPORT wasm_dsp_factory* readWasmDSPFactoryFromMachineFile(const std::string& machine_code_path);

EXPORT void writeWasmDSPFactoryToMachineFile(wasm_dsp_factory* factory, const std::string& machine_code_path);

#ifdef __cplusplus
extern "C" {
#endif
    
EXPORT wasm_dsp_factory* createWasmCDSPFactoryFromFile2(const char* filename, int argc, const char* argv[],
                                                      char* error_msg, bool internal_memory);

EXPORT wasm_dsp_factory* createWasmCDSPFactoryFromString2(const char* name_app, const char* dsp_content, int argc,
                                                        const char* argv[], char* error_msg, bool internal_memory);

EXPORT bool deleteWasmCDSPFactory(wasm_dsp_factory* factory);

EXPORT wasm_dsp_factory* readWasmCDSPFactoryFromMachine(const char* machine_code);

EXPORT char* writeWasmCDSPFactoryToMachine(wasm_dsp_factory* factory);

EXPORT wasm_dsp_factory* readWasmCDSPFactoryFromMachineFile(const char* machine_code_path);

EXPORT void writeWasmCDSPFactoryToMachineFile(wasm_dsp_factory* factory, const char* machine_code_path);

typedef struct {
    char*       fCode;
    int         fCodeSize;
    const char* fHelpers;
} WasmModule;

/**
 * Create a Faust DSP WebAssembly module and additional helper functions from a DSP source code as a file.
 *
 * @param filename - the DSP filename
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param error_msg - the error string to be filled, has to be 4096 characters long
 * @param internal_memory - whether the memory is allocated inside the module (= faster DSP fields access) or from the
 * JS context
 *
 * @return a valid WebAssembly module and additional helper functions as a WasmRes struct on success (to be deleted by
 * the caller), otherwise a null pointer.
 */
EXPORT WasmModule* createWasmCDSPFactoryFromFile(const char* filename, int argc, const char* argv[], char* error_msg,
                                                 bool internal_memory);

/**
 * Create a Faust DSP WebAssembly module and additional helper functions from a DSP source code as a string.
 *
 * @param name_app - the name of the Faust program
 * @param dsp_content - the Faust program as a string
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters
 * @param error_msg - the error string to be filled, has to be 4096 characters long
 * @param internal_memory - whether the memory is allocated inside the module (= faster DSP fields access) or from the
 * JS context
 *
 * @return a valid WebAssembly module and additional helper functions as a WasmRes struct on success (to be deleted by
 * the caller), otherwise a null pointer.
 */
EXPORT WasmModule* createWasmCDSPFactoryFromString(const char* name_app, const char* dsp_content, int argc,
                                                   const char* argv[], char* error_msg, bool internal_memory);

/**
 * Get the WebAssembly module from the WasmRes structure.
 *
 * @param module - the WebAssembly module
 *
 * @return the WebAssembly module as an array of bytes.
 */
EXPORT const char* getWasmCModule(WasmModule* module);

/**
 * Get the WebAssembly module size.
 *
 * @param module - the WebAssembly module
 *
 * @return the WebAssembly module size.
 */
EXPORT int getWasmCModuleSize(WasmModule* module);

/**
 * Get the additional helper functions module from the WasmRes structure.
 *
 * @param module - the WebAssembly module
 *
 * @return the additional helper functions as a string.
 */
EXPORT const char* getWasmCHelpers(WasmModule* module);

/**
 * The free function to be used on memory returned by createWasmCDSPFactoryFromString.
 *
 * @param module - the WebAssembly module
 *
 * @param ptr - the WasmRes structure to be deleted.
 */
EXPORT void freeWasmCModule(WasmModule* module);

/**
 * Get the error message after an exception occured.
 *
 * @return the error as a static string.
 */
EXPORT const char* getErrorAfterException();

/**
 *  Cleanup library global context after an exception occured.
 *
 */
EXPORT void cleanupAfterException();

#ifdef __cplusplus
}
#endif

#endif
