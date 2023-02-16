/************************** BEGIN one-sample-dsp.h ************************
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

#ifndef __one_sample_dsp__
#define __one_sample_dsp__

#include <assert.h>
#include "faust/dsp/dsp.h"

template <typename REAL>
class FAUST_API one_sample_dsp : public dsp {
  
    protected:
        
        FAUSTFLOAT* fInputs;
        FAUSTFLOAT* fOutputs;
    
        int* iControl;
        REAL* fControl;
    
        bool fDelete;
    
        void checkAlloc()
        {
            // Allocated once (TODO : make this RT safe)
            if (!fInputs) {
                fInputs = new FAUSTFLOAT[getNumInputs() * 4096];
                fOutputs = new FAUSTFLOAT[getNumOutputs() * 4096];
            }
            if (!iControl) {
                iControl = new int[getNumIntControls()];
                fControl = new REAL[getNumRealControls()];
            }
        }
    
    public:
    
        one_sample_dsp():fInputs(nullptr), fOutputs(nullptr), iControl(nullptr), fControl(nullptr), fDelete(true)
        {}
        
        one_sample_dsp(int* iControl, REAL* fControl)
        :fInputs(nullptr), fOutputs(nullptr),
        iControl(iControl), fControl(fControl), fDelete(false)
        {}
        
        virtual ~one_sample_dsp()
        {
            delete [] fInputs;
            delete [] fOutputs;
            if (fDelete) {
                delete [] iControl;
                delete [] fControl;
            }
        }
    
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
         * @param iControl - an externally allocated array of 'int' typed values used to keep the DSP control state
         * @param fControl - an externally allocated array of 'float, double or quad' typed values used to keep the DSP control state
         */
        virtual void control(int* iControl, REAL* fControl) = 0;
    
        // Alternative external version
        virtual void control()
        {
            checkAlloc();
            control(iControl, fControl);
        }
        
        /**
         * Compute one sample.
         *
         * @param inputs - the input audio buffers as an array of getNumInputs FAUSTFLOAT samples (either float, double or quad)
         * @param outputs - the output audio buffers as an array of getNumOutputs FAUSTFLOAT samples (either float, double or quad)
         * @param iControl - the externally allocated array of 'int' typed values used to keep the DSP control state
         * @param fControl - the externally allocated array of 'float, double or quad' typed values used to keep the DSP control state
         */
        virtual void compute(FAUSTFLOAT* inputs, FAUSTFLOAT* outputs, int* iControl, REAL* fControl) = 0;
    
        // The standard 'compute' expressed using the control/compute (one sample) model
        virtual void compute(int count, FAUSTFLOAT** inputs_aux, FAUSTFLOAT** outputs_aux)
        {
            // Control
            control();
            
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
                compute(inputs_ptr, outputs_ptr, iControl, fControl);
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
    
        int* getIControl() { return iControl; }
        REAL* getFControl() { return fControl; }
    
};

// To be used with -os1 and -os2 mode

template <typename REAL>
class FAUST_API one_sample_dsp_real : public dsp {
    
    protected:
    
        FAUSTFLOAT* fInputs;
        FAUSTFLOAT* fOutputs;
        
        int* iControl;
        REAL* fControl;
    
        int* iZone;
        REAL* fZone;
    
        bool fDelete;
    
        void checkAlloc()
        {
            // Allocated once (TODO : make this RT safe)
            if (!fInputs) {
                fInputs = new FAUSTFLOAT[getNumInputs() * 4096];
                fOutputs = new FAUSTFLOAT[getNumOutputs() * 4096];
            }
            if (!iControl) {
                iControl = new int[getNumIntControls()];
                fControl = new REAL[getNumRealControls()];
                iZone = new int[getiZoneSize()];
                fZone = new REAL[getfZoneSize()];
            }
        }
    
    public:
    
        one_sample_dsp_real()
        :fInputs(nullptr), fOutputs(nullptr),
        iControl(nullptr), fControl(nullptr),
        iZone(nullptr), fZone(nullptr), fDelete(true)
        {}
    
        one_sample_dsp_real(int* iControl, REAL* fControl, int* iZone, REAL* fZone)
        :fInputs(nullptr), fOutputs(nullptr),
        iControl(iControl), fControl(fControl),
        iZone(iZone), fZone(fZone), fDelete(false)
        {}
        
        virtual ~one_sample_dsp_real()
        {
            delete [] fInputs;
            delete [] fOutputs;
            if (fDelete) {
                delete [] iControl;
                delete [] fControl;
                delete [] iZone;
                delete [] fZone;
            }
        }
    
        virtual void init(int sample_rate)
        {
            checkAlloc();
            init(sample_rate, iZone, fZone);
        }
    
        virtual void init(int sample_rate, int* iZone, REAL* fZone) = 0;
    
        virtual void instanceInit(int sample_rate)
        {
            checkAlloc();
            instanceInit(sample_rate, iZone, fZone);
        }
    
        virtual void instanceInit(int sample_rate, int* iZone, REAL* fZone) = 0;
 
        virtual void instanceConstants(int sample_rate)
        {
            checkAlloc();
            instanceConstants(sample_rate, iZone, fZone);
        }
    
        virtual void instanceConstants(int sample_rate, int* iZone, REAL* fZone) = 0;
  
        virtual void instanceClear()
        {
            checkAlloc();
            instanceClear(iZone, fZone);
        }
    
        virtual void instanceClear(int* iZone, REAL* fZone) = 0;

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
        * Return the size on 'float, double or quad' typed values necessary to compute the DSP state
        *
        * @return the number of 'float, double or quad' typed values.
        */
        virtual int getiZoneSize() = 0;
        
        /**
         * Return the size on 'int' typed values necessary to compute the DSP state
         *
         * @return the number of 'int' typed values.
         */
        virtual int getfZoneSize() = 0;
    
        /**
         * Update the DSP control state.
         *
         * @param iControl - an externally allocated array of 'int' typed values used to keep the DSP control state
         * @param fControl - an externally allocated array of 'float, double or quad' typed values used to keep the DSP control state
         * @param iZone - an externally allocated array of 'int' typed values used to keep the DSP state
         * @param fZone - an externally allocated array of 'float, double or quad' typed values used to keep the DSP state
         */
        virtual void control(int* iControl, REAL* fControl, int* iZone, REAL* fZone) = 0;
        
        // Alternative external version
        virtual void control()
        {
            control(iControl, fControl, iZone, fZone);
        }
    
        /**
         * Compute one sample.
         *
         * @param inputs - the input audio buffers as an array of getNumInputs FAUSTFLOAT samples (either float, double or quad)
         * @param outputs - the output audio buffers as an array of getNumOutputs FAUSTFLOAT samples (either float, double or quad)
         * @param iControl - the externally allocated array of 'int' typed values used to keep the DSP control state
         * @param fControl - the externally allocated array of 'float, double or quad' typed values used to keep the DSP control state
         * @param iZone - an externally allocated array of 'int' typed values used to keep the DSP state
         * @param fZone - an externally allocated array of 'float, double or quad' typed values used to keep the DSP state
         */
        virtual void compute(FAUSTFLOAT* inputs, FAUSTFLOAT* outputs,
                             int* iControl, REAL* fControl,
                             int* iZone, REAL* fZone) = 0;
        
        // The standard 'compute' expressed using the control/compute (one sample) model
        virtual void compute(int count, FAUSTFLOAT** inputs_aux, FAUSTFLOAT** outputs_aux)
        {
            assert(fInputs);
            
            // Control
            control();
            
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
                compute(inputs_ptr, outputs_ptr, iControl, fControl, iZone, fZone);
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
    
        int* getIControl() { return iControl; }
        REAL* getFControl() { return fControl; }
        
        int* getIZone() { return iZone; }
        REAL* getFZone() { return fZone; }
    
};

// To be used with -os3 mode

template <typename REAL>
class FAUST_API one_sample_dsp_real1 : public dsp {
    
    protected:
        
        FAUSTFLOAT* fInputs;
        FAUSTFLOAT* fOutputs;
            
    public:
        
        one_sample_dsp_real1():fInputs(nullptr), fOutputs(nullptr)
        {}
        
        virtual ~one_sample_dsp_real1()
        {
            delete [] fInputs;
            delete [] fOutputs;
        }
        
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
         * Return the size on 'float, double or quad' typed values necessary to compute the DSP state
         *
         * @return the number of 'float, double or quad' typed values.
         */
        virtual int getiZoneSize() = 0;
        
        /**
         * Return the size on 'int' typed values necessary to compute the DSP state
         *
         * @return the number of 'int' typed values.
         */
        virtual int getfZoneSize() = 0;
        
        /**
         * Update the DSP control state.
         */
        virtual void control() = 0;
        
        /**
         * Compute one sample.
         *
         * @param inputs - the input audio buffers as an array of getNumInputs FAUSTFLOAT samples (either float, double or quad)
         * @param outputs - the output audio buffers as an array of getNumOutputs FAUSTFLOAT samples (either float, double or quad)
         */
        virtual void compute(FAUSTFLOAT* inputs, FAUSTFLOAT* outputs) = 0;
        
        // The standard 'compute' expressed using the control/compute (one sample) model
        virtual void compute(int count, FAUSTFLOAT** inputs_aux, FAUSTFLOAT** outputs_aux)
        {
            // TODO : not RT safe
            if (!fInputs) {
                fInputs = new FAUSTFLOAT[getNumInputs() * 4096];
                fOutputs = new FAUSTFLOAT[getNumOutputs() * 4096];
            }
            
            // Control
            control();
            
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
                compute(inputs_ptr, outputs_ptr);
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

#endif
/************************** END one-sample-dsp.h **************************/
