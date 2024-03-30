/************************** BEGIN llvm-dsp-adapter1.h ***********************
FAUST Architecture File
Copyright (C) 2024 GRAME, Centre National de Creation Musicale
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

#ifndef LLVM_mydsp_adapter_H
#define LLVM_mydsp_adapter_H

// This allows to use -Dfoo to generate a "foo" class expecting to have the LLVM code compiled with the '-cn foo' option.
#ifndef FAUSTCLASS
#define FAUSTCLASS mydsp
#endif

#define CONCATENATE_IMPL(prefix, name) prefix##name
#define CONCATENATE(prefix, name) CONCATENATE_IMPL(prefix, name)

#if defined(SOUNDFILE)
#include "faust/gui/SoundUI.h"
#endif

#include "faust/dsp/dsp.h"
#include "faust/gui/JSONUIDecoder.h"

/*
 Wraps a LLVM module compiled as object code in a C++ 'dsp' class.
 */
#ifdef __cplusplus
extern "C"
{
#endif

    // LLVM module API
    typedef char comp_llvm_mydsp;
    
    void CONCATENATE(allocate, FAUSTCLASS)(comp_llvm_mydsp* dsp);
    void CONCATENATE(destroy, FAUSTCLASS)(comp_llvm_mydsp* dsp);
    void CONCATENATE(instanceConstants, FAUSTCLASS)(comp_llvm_mydsp* dsp, int sample_rate);
    void CONCATENATE(instanceClear, FAUSTCLASS)(comp_llvm_mydsp* dsp);
    void CONCATENATE(classInit, FAUSTCLASS)(int sample_rate);
    void CONCATENATE(compute, FAUSTCLASS)(comp_llvm_mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs);
    char* CONCATENATE(getJSON, FAUSTCLASS)();

#ifdef __cplusplus
}
#endif

class FAUSTCLASS : public dsp {
    
    private:
        
        comp_llvm_mydsp* fDSP;
        JSONUIDecoderBase* fDecoder;
    
    public:
    
        FAUSTCLASS()
        {
            fDecoder = createJSONUIDecoder(CONCATENATE(getJSON, FAUSTCLASS)());
            fDSP = static_cast<comp_llvm_mydsp*>(calloc(1, fDecoder->getDSPSize()));
            CONCATENATE(allocate, FAUSTCLASS)(fDSP);
        }
        
        virtual ~FAUSTCLASS()
        {
            CONCATENATE(destroy, FAUSTCLASS)(fDSP);
            free(fDSP);
            delete fDecoder;
        }
  
        virtual int getNumInputs() { return fDecoder->getNumInputs(); }
        
        virtual int getNumOutputs() { return fDecoder->getNumOutputs(); }
    
        virtual void buildUserInterface(UI* ui_interface)
        {
            fDecoder->buildUserInterface(ui_interface, fDSP);
        }
    
        virtual int getSampleRate()
        {
            return fDecoder->getSampleRate(fDSP);
        }
        
        virtual void init(int sample_rate)
        {
            classInit(sample_rate);
            instanceInit(sample_rate);
        }
    
        virtual void instanceInit(int sample_rate)
        {
            instanceConstants(sample_rate);
            instanceResetUserInterface();
            instanceClear();
        }
        
        virtual void instanceConstants(int sample_rate)
        {
            CONCATENATE(instanceConstants, FAUSTCLASS)(fDSP, sample_rate);
        }
    
        virtual void instanceResetUserInterface()
        {
        #if defined(SOUNDFILE)
            fDecoder->resetUserInterface(fDSP, defaultsound);
        #else
            fDecoder->resetUserInterface(fDSP, nullptr);
        #endif
        }
    
        virtual void instanceClear()
        {
            CONCATENATE(instanceClear, FAUSTCLASS)(fDSP);
        }
    
        static void classInit(int sample_rate)
        {
            CONCATENATE(classInit, FAUSTCLASS)(sample_rate);
        }
    
        virtual FAUSTCLASS* clone()
        {
            return new FAUSTCLASS();
        }
        
        virtual void metadata(Meta* m)
        {
            fDecoder->metadata(m);
        }
        
        virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
        {
            CONCATENATE(compute, FAUSTCLASS)(fDSP, count, input, output);
        }
    
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            compute(count, inputs, outputs);
        }
    
};

// Factory API

dsp* CONCATENATE(create, FAUSTCLASS)() { return new FAUSTCLASS(); }

#endif
/************************** END llvm-dsp-adapter1.h **************************/
