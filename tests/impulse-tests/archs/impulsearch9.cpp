/************************************************************************
 FAUST Architecture File
 Copyright (C) 2016-2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
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
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include "controlTools.h"

//----------------------------------------------------------------------------
//FAUST generated code
//----------------------------------------------------------------------------

<<includeIntrinsic>>

<<includeclass>>

// Wrapping C++ class for the C object

class Cdsp : public dsp {
    
    private:
        
        mydsp* fDSP;
        
    public:
        
        Cdsp()
        {
            fDSP = newmydsp();
        }
        
        virtual ~Cdsp()
        {
            deletemydsp(fDSP);
        }
        
        virtual int getNumInputs() { return getNumInputsmydsp(fDSP); }
        
        virtual int getNumOutputs() { return getNumOutputsmydsp(fDSP); }
        
        virtual void buildUserInterface(UI* ui_interface)
        {
            UIGlue glue;
            buildUIGlue(&glue, ui_interface, true);
            buildUserInterfacemydsp(fDSP, &glue);
        }
        
        virtual int getSampleRate()
        {
            return getSampleRatemydsp(fDSP);
        }
        
        virtual void init(int sample_rate)
        {
            initmydsp(fDSP, sample_rate);
        }
        
        static void classInit(int sample_rate)
        {
            classInitmydsp(sample_rate);
        }
        
        virtual void instanceInit(int sample_rate)
        {
            instanceInitmydsp(fDSP, sample_rate);
        }
        
        virtual void instanceConstants(int sample_rate)
        {
            instanceConstantsmydsp(fDSP, sample_rate);
        }
        
        virtual void instanceResetUserInterface()
        {
            instanceResetUserInterfacemydsp(fDSP);
        }
        
        virtual void instanceClear()
        {
            instanceClearmydsp(fDSP);
        }
        
        virtual dsp* clone()
        {
            return new Cdsp();
        }
        
        virtual void metadata(Meta* m)
        {
            MetaGlue glue;
            buildMetaGlue(&glue, m);
            metadatamydsp(&glue);
        }
    
        virtual void control()
        {
            controlmydsp(fDSP);
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


// Wrapping C++ class used with -ec option.

struct ControlDSP : public decorator_dsp {
    
    ControlDSP(dsp* dsp):decorator_dsp(dsp)
    {}
    
    // This is mandatory
    virtual ControlDSP* clone()
    {
        return new ControlDSP(fDSP->clone());
    }
    
    void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs)
    {
        fDSP->control();
        fDSP->compute(count, inputs, outputs);
    }
    
};

int main(int argc, char* argv[])
{
    int linenum = 0;
    int nbsamples = 60000;
  
    // print general informations
    printHeader(new Cdsp(), nbsamples);
    
    // linenum is incremented in runDSP
    runDSP(new ControlDSP(new Cdsp()), argv[0], linenum, nbsamples/4);
    runDSP(new ControlDSP(new Cdsp()), argv[0], linenum, nbsamples/4, false, true);
     
    return 0;
}
