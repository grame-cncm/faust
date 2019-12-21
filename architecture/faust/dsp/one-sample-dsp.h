/************************** BEGIN one-sample-dsp.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019 GRAME, Centre National de Creation Musicale
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

#ifndef __one_sample_dsp__
#define __one_sample_dsp__

#include "faust/dsp/dsp.h"

class one_sample_dsp : public dsp {
  
    protected:
        
        int* iZone;
        FAUSTFLOAT* fZone;
    
    public:
    
        one_sample_dsp():iZone(NULL),fZone(NULL)
        {}
    
        virtual ~one_sample_dsp()
        {}
    
        /**
         * Return the number of 'int' typed values necessary to compute the internal DSP state
         *
         * @return the number of 'int' typed values.
         */
        virtual int getNumIntControls() = 0;
    
        /**
         * Return the number of 'float, double or quad' typed values necessary to compute the DSP control state
         *
         * @return the number of 'float, double or quad' typed values.
         */
        virtual int getNumRealControls() = 0;
    
        /**
         * Update the DSP control state.
         *
         * @param icontrol - an externally allocated array of 'int' typed values used to keep the DSP control state
         * @param fcontrol - an externally allocated array of 'float, double or quad' typed values used to keep the DSP control state
         */
        virtual void control(int* iControl, FAUSTFLOAT* fControl) = 0;
        
        /**
         * Compute one sample.
         *
         * @param inputs - the input audio buffers as an array of getNumInputs FAUSTFLOAT samples (either float, double or quad)
         * @param outputs - the output audio buffers as an array of getNumOutputs FAUSTFLOAT samples (either float, double or quad)
         * @param icontrol - the externally allocated array of 'int' typed values used to keep the DSP control state
         * @param fcontrol - the externally allocated array of 'float, double or quad' typed values used to keep the DSP control state
         */
        virtual void compute(FAUSTFLOAT* inputs, FAUSTFLOAT* outputs, int* iControl, FAUSTFLOAT* fControl) = 0;
    
        // The standard 'compute' expressed using the control/compute (one sample) model
        virtual void compute(int count, FAUSTFLOAT** inputs_aux, FAUSTFLOAT** outputs_aux)
        {
            // Control
            int int_control[getNumIntControls()];
            FAUSTFLOAT real_control[getNumRealControls()];
            control(int_control, real_control);
            
            // Compute
            FAUSTFLOAT inputs[getNumInputs()];
            FAUSTFLOAT outputs[getNumOutputs()];
            for (int frame = 0; frame < count; frame++) {
                for (int chan = 0; chan < getNumInputs(); chan++) {
                    inputs[chan] = inputs_aux[chan][frame];
                }
                // One sample compute
                compute(inputs, outputs, int_control, real_control);
                for (int chan = 0; chan < getNumOutputs(); chan++) {
                    outputs_aux[chan][frame] = outputs[chan];
                }
            }
        }
        
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            compute(count, inputs, outputs);
        }
    
};

#endif
/**************************  END  one-sample-dsp.h **************************/
