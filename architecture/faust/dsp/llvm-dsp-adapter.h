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

#include "faust/gui/CGlue.h"
#include "faust/gui/SoundUI.h"
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
    
    comp_llvm_dsp* newmydsp();
    void deletemydsp(comp_llvm_dsp* dsp);
    
    int getNumInputsmydsp(comp_llvm_dsp* dsp);
    int getNumOutputsmydsp(comp_llvm_dsp* dsp);
    
    void buildUserInterfacemydsp(comp_llvm_dsp* dsp, UIGlue* ui);
    
    int getSampleRatemydsp(comp_llvm_dsp* dsp);
    
    void initmydsp(comp_llvm_dsp* dsp, int samplingRate);
    void instanceInitmydsp(comp_llvm_dsp* dsp, int samplingRate);
    void instanceConstantsmydsp(comp_llvm_dsp* dsp, int samplingRate);
    void instanceResetUserInterfacemydsp(comp_llvm_dsp* dsp);
    void instanceClearmydsp(comp_llvm_dsp* dsp);
    
    void classInitmydsp(int samplingRate);
    
    void metadatamydsp(MetaGlue* meta);
    
    void setDefaultSoundmydsp(Soundfile* sf);
    
    char* getJSONmydsp();
    
    void computemydsp(comp_llvm_dsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs);
    
#ifdef __cplusplus
}
#endif

class mydsp : public dsp {
    
    private:
        
        comp_llvm_dsp* fDSP;
        JSONUIDecoder* fDecoder;
    
    public:
        
        mydsp()
        {
            fDecoder = new JSONUIDecoder(getJSONmydsp());
            fDSP = newmydsp();
            setDefaultSoundmydsp(defaultsound);
        }
        
        virtual ~mydsp()
        {
            deletemydsp(fDSP);
            delete fDecoder;
        }
    
        virtual int getNumInputs() { return getNumInputsmydsp(fDSP); }
        
        virtual int getNumOutputs() { return getNumOutputsmydsp(fDSP); }
        
        virtual void buildUserInterface(UI* ui_interface)
        {
            UIGlue glue;
            buildUIGlue(&glue, ui_interface, fDecoder->hasCompileOption("-double"));
            buildUserInterfacemydsp(fDSP, &glue);
        }
        
        virtual int getSampleRate()
        {
            return getSampleRatemydsp(fDSP);
        }
        
        virtual void init(int samplingRate)
        {
            classInitmydsp(samplingRate);
            initmydsp(fDSP, samplingRate);
        }
    
        virtual void instanceInit(int samplingRate)
        {
            instanceInitmydsp(fDSP, samplingRate);
        }
        
        virtual void instanceConstants(int samplingRate)
        {
            instanceConstantsmydsp(fDSP, samplingRate);
        }
        
        virtual void instanceResetUserInterface()
        {
            instanceResetUserInterfacemydsp(fDSP);
        }
        
        virtual void instanceClear()
        {
            instanceClearmydsp(fDSP);
        }
    
        static void classInit(int samplingRate)
        {
            classInitmydsp(samplingRate);
        }
    
        virtual dsp* clone()
        {
            return new mydsp();
        }
        
        virtual void metadata(Meta* m)
        {
            MetaGlue glue;
            buildMetaGlue(&glue, m);
            metadatamydsp(&glue);
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
