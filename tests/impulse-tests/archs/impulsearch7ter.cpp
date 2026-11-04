/************************************************************************
 FAUST Architecture File
 Copyright (C) 2024-2026 GRAME, Centre National de Creation Musicale
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

struct OneSample : public decorator_dsp {
    
   FAUSTFLOAT* fInputs;
    FAUSTFLOAT* fOutputs;
    
    OneSample(dsp* dsp):decorator_dsp(dsp),fInputs(nullptr),fOutputs(nullptr)
    {}
    
    virtual ~OneSample()
    {
        delete [] fInputs;
        delete [] fOutputs;
    }
    
    // This is mandatory
    virtual OneSample* clone()
    {
        return new OneSample(fDSP->clone());
    }
    
    // The standard 'compute' expressed using the control/compute (one sample) model
    virtual void compute(int count, FAUSTFLOAT** inputs_aux, FAUSTFLOAT** outputs_aux)
    {
        // TODO : not RT safe
        if (!fInputs) {
            fInputs = new FAUSTFLOAT[getNumInputs() * 4096];
            fOutputs = new FAUSTFLOAT[getNumOutputs() * 4096];
        }
        
        // Control
        fDSP->control();
        
        // Compute
        int num_inputs = getNumInputs();
        int num_outputs = getNumOutputs();
        
        FAUSTFLOAT* inputs_ptr = &fInputs[0];
        FAUSTFLOAT* outputs_ptr = &fOutputs[0];
        
        for (int frame = 0; frame < count; frame++) {
            for (int chan = 0; chan < num_inputs; chan++) {
                inputs_ptr[chan] = inputs_aux[chan][frame];
            }
            inputs_ptr += num_inputs;
        }
        
        inputs_ptr = &fInputs[0];
        for (int frame = 0; frame < count; frame++) {
            // One sample compute
            fDSP->frame(inputs_ptr, outputs_ptr);
            inputs_ptr += num_inputs;
            outputs_ptr += num_outputs;
        }
        
        outputs_ptr = &fOutputs[0];
        for (int frame = 0; frame < count; frame++) {
            for (int chan = 0; chan < num_outputs; chan++) {
                outputs_aux[chan][frame] = outputs_ptr[chan];
            }
            outputs_ptr += num_outputs;
        }
    }
    
    virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
    {
        compute(count, inputs, outputs);
    }
    
};

int main(int argc, char* argv[])
{
    int linenum = 0;
    int nbsamples = 60000;
    
    // print general informations
    printHeader(new mydsp(), nbsamples);
    
    // linenum is incremented in runDSP and runPolyDSP
    runDSP(new OneSample(new mydsp()), argv[0], linenum, nbsamples/4);
    runDSP(new OneSample(new mydsp()), argv[0], linenum, nbsamples/4, false, true);
    runPolyDSP(new OneSample(new mydsp()), linenum, nbsamples/4, 4);
    runPolyDSP(new OneSample(new mydsp()), linenum, nbsamples/4, 1);
    
    return 0;
}
