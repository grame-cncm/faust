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

class dsp_poly_factory {
    
    private:
        
        llvm_dsp_factory* fFactory;
        llvm_dsp_factory* fEffectFactory;
    
    public:
        
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
            
            fFactory = createDSPFactoryFromString(name_app, dsp_content, argc, argv, target, error_msg);
            if (fFactory) {
                fEffectFactory = createDSPFactoryFromString(name_app, code_effect.str(), argc, argv, target, error_msg);
            } else {
                throw std::bad_alloc();
            }
        }
        
        virtual ~dsp_poly_factory()
        {
            deleteDSPFactory(fFactory);
            if (fEffectFactory) deleteDSPFactory(fEffectFactory);
        }
        
        /* Create a new polyphonic DSP instance with global effect, to be deleted with C++ 'delete' */
        dsp* createPolyDSPInstance(int nvoices, bool control, bool group, mydsp_poly** poly_dsp)
        {
            *poly_dsp = new mydsp_poly(fFactory->createDSPInstance(), nvoices, control, group);
            if (fEffectFactory) {
                return new dsp_sequencer(*poly_dsp, fEffectFactory->createDSPInstance());
            } else {
                return *poly_dsp;
            }
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

#endif // __poly_dsp_tools__
