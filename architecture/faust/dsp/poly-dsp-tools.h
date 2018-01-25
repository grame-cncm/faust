/************************************************************************
 FAUST Architecture File
 Copyright (C) 2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __poly_dsp_tools__
#define __poly_dsp_tools__

#include <string>
#include <iostream>
#include <fstream>

#include "faust/dsp/llvm-dsp.h"
#include "faust/dsp/dsp-combiner.h"
#include "faust/dsp/poly-dsp.h"

inline std::string pathToContent(const std::string& path)
{
    std::ifstream file(path.c_str(), std::ifstream::binary);
    
    file.seekg(0, file.end);
    int size = int(file.tellg());
    file.seekg(0, file.beg);
    
    // And allocate buffer to that a single line can be read...
    char* buffer = new char[size + 1];
    file.read(buffer, size);
    
    // Terminate the string
    buffer[size] = 0;
    string result = buffer;
    file.close();
    delete [] buffer;
    return result;
}

/**
 * Polyphonic DSP factory class. Helper code to support polyphonic DSP source with an integrated effect.
 */

struct dsp_poly_factory : public dsp_factory {
    
    llvm_dsp_factory* fProcessFactory;
    llvm_dsp_factory* fEffectFactory;
    
    dsp_poly_factory(llvm_dsp_factory* process_factory,
                     llvm_dsp_factory* effect_factory)
        :fProcessFactory(process_factory),
        fEffectFactory(effect_factory)
    {}

    dsp_poly_factory(const std::string& name_app,
                     const std::string& dsp_content,
                     int argc, const char* argv[],
                     const std::string& target,
                     std::string& error_msg,
                     int opt_level = -1)
    {
        // Create 'effect' expression
        std::stringstream code_effect;
        code_effect << "adapt(1,1) = _; adapt(2,2) = _,_; adapt(1,2) = _ <: _,_; adapt(2,1) = _,_ :> _;";
        code_effect << "adaptor(F,G) = adapt(outputs(F),inputs(G)); dsp_code = environment{ " << dsp_content << " };";
        code_effect << "process = adaptor(dsp_code.process, dsp_code.effect) : dsp_code.effect;";
        
        fProcessFactory = createDSPFactoryFromString(name_app, dsp_content, argc, argv, target, error_msg);
        if (fProcessFactory) {
            fEffectFactory = createDSPFactoryFromString(name_app, code_effect.str(), argc, argv, target, error_msg);
        } else {
            throw std::bad_alloc();
        }
    }
    
    virtual ~dsp_poly_factory()
    {
        deleteDSPFactory(fProcessFactory);
        if (fEffectFactory) { deleteDSPFactory(fEffectFactory); }
    }
    
    virtual std::string getName() { return fProcessFactory->getName(); }
    virtual std::string getSHAKey() { return fProcessFactory->getSHAKey(); }
    virtual std::string getDSPCode() { return fProcessFactory->getDSPCode(); }
    
    virtual void setMemoryManager(dsp_memory_manager* manager)
    {
        fProcessFactory->setMemoryManager(manager);
        if (fEffectFactory) {
            fEffectFactory->setMemoryManager(manager);
        }
    }
    virtual dsp_memory_manager* getMemoryManager() { return fProcessFactory->getMemoryManager(); }
    
    /* Create a new polyphonic DSP instance with global effect */
    dsp* createPolyDSPInstance(int nvoices, bool control, bool group, mydsp_poly** poly_dsp)
    {
        if (nvoices == 1) {
            *poly_dsp = nullptr;
            return fProcessFactory->createDSPInstance();
        } else {
            *poly_dsp = new mydsp_poly(fProcessFactory->createDSPInstance(), nvoices, control, group);
            if (fEffectFactory) {
                return new dsp_sequencer(*poly_dsp, fEffectFactory->createDSPInstance());
            } else {
                return *poly_dsp;
            }
        }
    }
    
    dsp* createDSPInstance()
    {
        return fProcessFactory->createDSPInstance();
    }

};

dsp_poly_factory* createPolyDSPFactoryFromString(const std::string& name_app,
                                                 const std::string& dsp_content,
                                                 int argc, const char* argv[],
                                                 const std::string& target,
                                                 std::string& error_msg,
                                                 int opt_level = -1)

{
    return new dsp_poly_factory(name_app, dsp_content, argc, argv, target, error_msg, opt_level);
}

dsp_poly_factory* createPolyDSPFactoryFromFile(const std::string& filename,
                                               int argc, const char* argv[],
                                               const std::string& target,
                                               std::string& error_msg,
                                               int opt_level = -1)
{
    return createPolyDSPFactoryFromString("FaustDSP", pathToContent(filename), argc, argv, target, error_msg, opt_level);
}

dsp_poly_factory* readPolyDSPFactoryFromBitcodeFile(const std::string& bit_code_path, const std::string& target, int opt_level = -1)
{
    std::string process_path = bit_code_path + "_process";
    std::string effect_path = bit_code_path + "_effect";
    
    llvm_dsp_factory* process_factory = readDSPFactoryFromBitcodeFile(process_path, target, opt_level);
    llvm_dsp_factory* effect_factory = readDSPFactoryFromBitcodeFile(effect_path, target, opt_level);
    
    if (!process_factory && !effect_factory) {
        return nullptr;
    } else {
        return new dsp_poly_factory(process_factory, effect_factory);
    }
}

void writePolyDSPFactoryToBitcodeFile(dsp_poly_factory* factory, const std::string& bit_code_path)
{
    std::string process_path = bit_code_path + "_process";
    std::string effect_path = bit_code_path + "_effect";
    
    writeDSPFactoryToBitcodeFile(factory->fProcessFactory, process_path);
    writeDSPFactoryToBitcodeFile(factory->fEffectFactory, effect_path);
}

#endif // __poly_dsp_tools__
