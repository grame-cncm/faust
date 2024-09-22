/************************** BEGIN dsp-compute-adapter.h ********************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

EXCEPTION : As a special exception, you may create a larger work
that contains this FAUST architecture section and distribute
that work under terms of your choice, so long as this FAUST
architecture section is not modified.
***************************************************************************/

#ifndef __dsp_compute_adapter__
#define __dsp_compute_adapter__

#include <sstream>
#include "dsp.h"

/*
 To be used to decorate a DSP compiled with the --compute-mix option.
 - the 'computeAdding' method adds the processed samples in the 'outputs' buffer parameter
 - the 'computeRemplacing' method writes the processed samples in the 'outputs' buffer parameter
 
 Usage:
 
 faust -cm foo.dsp -o foo.cpp
 
 dsp_compute_mix* dsp = new dsp_compute_mix(new mydsp());
 
 // Use 'dsp' as usual and use the added dsp->computeAdding(...) or dsp->computeRemplacing(...) methods
 
 delete dsp;
 */
class dsp_compute_mix : public decorator_dsp {
    
    public:
    
        dsp_compute_mix(::dsp* dsp) : decorator_dsp(dsp)
        {}
    
        virtual void computeAdding(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fDSP->compute(count, inputs, outputs);
        }
    
        virtual void computeRemplacing(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            for (int chan = 0; chan < fDSP->getNumOutputs(); chan++) {
                memset(outputs[chan], 0, sizeof(FAUSTFLOAT) * count);
            }
            fDSP->compute(count, inputs, outputs);
        }
    
};

/*
 To be used to decorate a DSP compiled with the --in-place option.
 - the 'buffers' parameters contains input samples to be replaced 'in place' by computed output samples using 'computeRemplacing'
 
 Usage:
 
 faust -inpl foo.dsp -o foo.cpp
 
 dsp_compute_inpl* dsp = new dsp_compute_inpl(new mydsp());
 
 // Use 'dsp' as usual and use the added dsp->computeRemplacing(...) method
 
 delete dsp;
 */
class dsp_compute_inpl : public decorator_dsp {
    
    public:
    
        dsp_compute_inpl(::dsp* dsp) : decorator_dsp(dsp)
        {}
    
        virtual void computeReplacing(int count, FAUSTFLOAT** buffers)
        {
            fDSP->compute(count, buffers, buffers);
        }
    
};

/*
 To be used to decorate a DSP compiled with the --compute-mix and --in-place options.
 - the 'buffers' parameters contains input samples to be added in place with computed output samples using 'computeAdding'
 
 Usage:
 
 faust -inpl -cm foo.dsp -o foo.cpp
 
 dsp_compute_inpl_mix* dsp = new dsp_compute_inpl_mix(new mydsp());
 
 // Use 'dsp' as usual and use the added dsp->computeAdding(...) method
 
 delete dsp;
 */
class dsp_compute_inpl_mix : public decorator_dsp {
    
    private:
    
        struct MyMeta : public Meta {
            
            int fInputs = 0;
            
            MyMeta(int inputs):fInputs(inputs)
            {}
            
            void declare(const char* key, const char* value)
            {
                if (strcmp(key, "compile_options") == 0) {
                    std::stringstream tokenizer(value);
                    bool cm = false;
                    bool inpl = false;
                    
                    // Use ' ' as delim for cutting string
                    std::string token;
                    while (getline(tokenizer, token, ' ')) {
                        cm = (token == "-cm");
                        inpl = (token == "-inpl");
                    }
                    
                    if (fInputs > 0 && cm && inpl) {
                        std::cout << "WARNING : using -cm and -inpl options with an effect !\n";
                    }
                }
            }
        };
    
    public:
    
        dsp_compute_inpl_mix(::dsp* dsp) : decorator_dsp(dsp)
        {
            MyMeta my_meta = MyMeta(dsp->getNumInputs());
            dsp->metadata(&my_meta);
        }
    
        virtual void computeAdding(int count, FAUSTFLOAT** buffers)
        {
            fDSP->compute(count, buffers, buffers);
        }
    
};

#endif

/************************** END dsp-compute-adapter.h **************************/
