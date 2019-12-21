/************************** BEGIN llvm-dsp-adapter.h **************************/
/************************************************************************
 ************************************************************************
 Copyright (C) 2019 GRAME, Centre National de Creation Musicale
 
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

#ifndef LLVM_DSP_ADAPTER_H
#define LLVM_DSP_ADAPTER_H

#include "faust/gui/JSONUIDecoder.h"

/*
 Wraps a LLVM module compiled as object code in a 'dsp' class.
 */

#ifdef __cplusplus
extern "C"
{
#endif
    
    // LLVM module API
    typedef char comp_llvm_dsp;

    // Used in -sch mode
    void allocatemydsp(comp_llvm_dsp* dsp);
    void destroymydsp(comp_llvm_dsp* dsp);
   
    void instanceConstantsmydsp(comp_llvm_dsp* dsp, int sample_rate);
    void instanceClearmydsp(comp_llvm_dsp* dsp);
    
    void classInitmydsp(int sample_rate);
    
    char* getJSONmydsp();
    
    void computemydsp(comp_llvm_dsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs);
    
#ifdef __cplusplus
}
#endif

class mydsp : public dsp {
    
    private:
        
        comp_llvm_dsp* fDSP;
        JSONUITemplatedDecoder* fDecoder;
    
    public:
    
        mydsp()
        {
            fDecoder = createJSONUIDecoder(getJSONmydsp());
            fDSP = static_cast<comp_llvm_dsp*>(calloc(1, fDecoder->getDSPSize()));
            allocatemydsp(fDSP);
        }
        
        virtual ~mydsp()
        {
            destroymydsp(fDSP);
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
            instanceConstantsmydsp(fDSP, sample_rate);
        }
    
        virtual void instanceResetUserInterface()
        {
            fDecoder->resetUserInterface(fDSP, defaultsound);
        }
    
        virtual void instanceClear()
        {
            instanceClearmydsp(fDSP);
        }
    
        static void classInit(int sample_rate)
        {
            classInitmydsp(sample_rate);
        }
    
        virtual mydsp* clone()
        {
            return new mydsp();
        }
        
        virtual void metadata(Meta* m)
        {
            fDecoder->metadata(m);
        }
        
        virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
        {
            computemydsp(fDSP, count, input, output);
        }
    
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            compute(count, inputs, outputs);
        }
    
};

#endif
/**************************  END  llvm-dsp-adapter.h **************************/
