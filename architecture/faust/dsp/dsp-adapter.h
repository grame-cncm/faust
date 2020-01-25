/************************** BEGIN dsp-adapter.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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

#ifndef __dsp_adapter__
#define __dsp_adapter__

#include <string.h>
#include <iostream>

#include "faust/dsp/dsp.h"

// Adapts a DSP for a different number of inputs/outputs
class dsp_adapter : public decorator_dsp {
    
    private:
        
        FAUSTFLOAT** fAdaptedInputs;
        FAUSTFLOAT** fAdaptedOutputs;
        int fHardwareInputs;
        int fHardwareOutputs;
        
        void adaptBuffers(FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            for (int i = 0; i < fHardwareInputs; i++) {
                fAdaptedInputs[i] = inputs[i];
            }
            for (int i = 0; i < fHardwareOutputs; i++) {
                fAdaptedOutputs[i] = outputs[i];
            }
        }
        
    public:
        
        dsp_adapter(dsp* dsp, int hardware_inputs, int hardware_outputs, int buffer_size):decorator_dsp(dsp)
        {
            fHardwareInputs = hardware_inputs;
            fHardwareOutputs = hardware_outputs;
             
            fAdaptedInputs = new FAUSTFLOAT*[dsp->getNumInputs()];
            for (int i = 0; i < dsp->getNumInputs() - fHardwareInputs; i++) {
                fAdaptedInputs[i + fHardwareInputs] = new FAUSTFLOAT[buffer_size];
                memset(fAdaptedInputs[i + fHardwareInputs], 0, sizeof(FAUSTFLOAT) * buffer_size);
            }
            
            fAdaptedOutputs = new FAUSTFLOAT*[dsp->getNumOutputs()];
            for (int i = 0; i < dsp->getNumOutputs() - fHardwareOutputs; i++) {
                fAdaptedOutputs[i + fHardwareOutputs] = new FAUSTFLOAT[buffer_size];
                memset(fAdaptedOutputs[i + fHardwareOutputs], 0, sizeof(FAUSTFLOAT) * buffer_size);
            }
        }
        
        virtual ~dsp_adapter()
        {
            for (int i = 0; i < fDSP->getNumInputs() - fHardwareInputs; i++) {
                delete [] fAdaptedInputs[i + fHardwareInputs];
            }
            delete [] fAdaptedInputs;
            
            for (int i = 0; i < fDSP->getNumOutputs() - fHardwareOutputs; i++) {
                delete [] fAdaptedOutputs[i + fHardwareOutputs];
            }
            delete [] fAdaptedOutputs;
        }
    
        virtual int getNumInputs() { return fHardwareInputs; }
        virtual int getNumOutputs() { return fHardwareOutputs; }
    
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            adaptBuffers(inputs, outputs);
            fDSP->compute(date_usec, count, fAdaptedInputs, fAdaptedOutputs);
        }
        
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            adaptBuffers(inputs, outputs);
            fDSP->compute(count, fAdaptedInputs, fAdaptedOutputs);
        }
};

// Adapts a DSP for a different sample size
template <typename TYPE_INT, typename TYPE_EXT>
class dsp_sample_adapter : public decorator_dsp {
    
    protected:
    
        TYPE_INT** fAdaptedInputs;
        TYPE_INT** fAdaptedOutputs;
    
        void adaptInputBuffers(int count, FAUSTFLOAT** inputs)
        {
            for (int chan = 0; chan < fDSP->getNumInputs(); chan++) {
                for (int frame = 0; frame < count; frame++) {
                    fAdaptedInputs[chan][frame] = TYPE_INT(reinterpret_cast<TYPE_EXT**>(inputs)[chan][frame]);
                }
            }
        }
    
        void adaptOutputsBuffers(int count, FAUSTFLOAT** outputs)
        {
            for (int chan = 0; chan < fDSP->getNumOutputs(); chan++) {
                for (int frame = 0; frame < count; frame++) {
                    reinterpret_cast<TYPE_EXT**>(outputs)[chan][frame] = TYPE_EXT(fAdaptedOutputs[chan][frame]);
                }
            }
        }
    
    public:
    
        dsp_sample_adapter(dsp* dsp):decorator_dsp(dsp)
        {
            fAdaptedInputs = new TYPE_INT*[dsp->getNumInputs()];
            for (int i = 0; i < dsp->getNumInputs(); i++) {
                fAdaptedInputs[i] = new TYPE_INT[4096];
            }
            
            fAdaptedOutputs = new TYPE_INT*[dsp->getNumOutputs()];
            for (int i = 0; i < dsp->getNumOutputs(); i++) {
                fAdaptedOutputs[i] = new TYPE_INT[4096];
            }
        }
    
        virtual ~dsp_sample_adapter()
        {
            for (int i = 0; i < fDSP->getNumInputs(); i++) {
                delete [] fAdaptedInputs[i];
            }
            delete [] fAdaptedInputs;
            
            for (int i = 0; i < fDSP->getNumOutputs(); i++) {
                delete [] fAdaptedOutputs[i];
            }
            delete [] fAdaptedOutputs;
        }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            adaptInputBuffers(count, inputs);
            // DSP base class uses FAUSTFLOAT** type, so reinterpret_cast has to be used even if the real DSP uses TYPE_INT
            fDSP->compute(count, reinterpret_cast<FAUSTFLOAT**>(fAdaptedInputs), reinterpret_cast<FAUSTFLOAT**>(fAdaptedOutputs));
            adaptOutputsBuffers(count, outputs);
        }
    
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            adaptInputBuffers(count, inputs);
            // DSP base class uses FAUSTFLOAT** type, so reinterpret_cast has to be used even if the real DSP uses TYPE_INT
            fDSP->compute(date_usec, count, reinterpret_cast<FAUSTFLOAT**>(fAdaptedInputs), reinterpret_cast<FAUSTFLOAT**>(fAdaptedOutputs));
            adaptOutputsBuffers(count, outputs);
       }
};

// Down sample rate adapter
template <int DownFactor>
class dsp_down_sampler : public decorator_dsp {
    
    private:
    
        // Generated with process = fi.lowpass(3, ma.SR*0.5/vslider("DownFactor", 2, 2, 16, 1));
        template <int fVslider0>
        struct LowPass3 {
            
            float fVec0[2];
            float fRec1[2];
            float fRec0[3];
            
            static float mydsp_faustpower2_f(float value)
            {
                return (value * value);
            }
       
            LowPass3()
            {
                for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
                    fVec0[l0] = 0.0f;
                }
                for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
                    fRec1[l1] = 0.0f;
                }
                for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
                    fRec0[l2] = 0.0f;
                }
            }
            
            inline void compute(int count, FAUSTFLOAT* input0, FAUSTFLOAT* output0)
            {
                // Will be computed at template specialization time
                float fSlow0 = std::tan((1.57079637f / float(fVslider0)));
                float fSlow1 = (1.0f / fSlow0);
                float fSlow2 = (1.0f / (((fSlow1 + 1.0f) / fSlow0) + 1.0f));
                float fSlow3 = (1.0f / (fSlow1 + 1.0f));
                float fSlow4 = (1.0f - fSlow1);
                float fSlow5 = (((fSlow1 + -1.0f) / fSlow0) + 1.0f);
                float fSlow6 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fSlow0))));
                
                // Computed at runtime
                for (int i = 0; (i < count); i = (i + 1)) {
                    float fTemp0 = float(input0[i]);
                    fVec0[0] = fTemp0;
                    fRec1[0] = (0.0f - (fSlow3 * ((fSlow4 * fRec1[1]) - (fTemp0 + fVec0[1]))));
                    fRec0[0] = (fRec1[0] - (fSlow2 * ((fSlow5 * fRec0[2]) + (fSlow6 * fRec0[1]))));
                    output0[i] = FAUSTFLOAT((fSlow2 * (fRec0[2] + (fRec0[0] + (2.0f * fRec0[1])))));
                    fVec0[1] = fVec0[0];
                    fRec1[1] = fRec1[0];
                    fRec0[2] = fRec0[1];
                    fRec0[1] = fRec0[0];
                }
            }
        };
    
        // Generated with process = fi.lowpass(4, ma.SR*0.5/vslider("DownFactor", 2, 2, 16, 1));
        template <int fVslider0>
        struct LowPass4 {
            
            float fRec1[3];
            float fRec0[3];
            
            static float mydsp_faustpower2_f(float value)
            {
                return (value * value);
            }
            
            LowPass4()
            {
                for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
                    fRec1[l0] = 0.0f;
                }
                for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) {
                    fRec0[l1] = 0.0f;
                }
            }
            
            inline void compute(int count, FAUSTFLOAT* input0, FAUSTFLOAT* output0)
            {
                // Will be computed at template specialization time
                float fSlow0 = std::tan((1.57079637f / float(fVslider0)));
                float fSlow1 = (1.0f / fSlow0);
                float fSlow2 = (1.0f / (((fSlow1 + 0.765366852f) / fSlow0) + 1.0f));
                float fSlow3 = (1.0f / (((fSlow1 + 1.84775901f) / fSlow0) + 1.0f));
                float fSlow4 = (((fSlow1 + -1.84775901f) / fSlow0) + 1.0f);
                float fSlow5 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fSlow0))));
                float fSlow6 = (((fSlow1 + -0.765366852f) / fSlow0) + 1.0f);
                
                // Computed at runtime
                for (int i = 0; (i < count); i = (i + 1)) {
                    fRec1[0] = (float(input0[i]) - (fSlow3 * ((fSlow4 * fRec1[2]) + (fSlow5 * fRec1[1]))));
                    fRec0[0] = ((fSlow3 * (fRec1[2] + (fRec1[0] + (2.0f * fRec1[1])))) - (fSlow2 * ((fSlow6 * fRec0[2]) + (fSlow5 * fRec0[1]))));
                    output0[i] = FAUSTFLOAT((fSlow2 * (fRec0[2] + (fRec0[0] + (2.0f * fRec0[1])))));
                    fRec1[2] = fRec1[1];
                    fRec1[1] = fRec1[0];
                    fRec0[2] = fRec0[1];
                    fRec0[1] = fRec0[0];
                }
            }
        };
    
        std::vector<LowPass4<DownFactor>> fInputLowPass;
        std::vector<LowPass4<DownFactor>> fOutputLowPass;
    
    public:
    
        dsp_down_sampler(dsp* dsp):decorator_dsp(dsp)
        {
            for (int chan = 0; chan < fDSP->getNumInputs(); chan++) {
               fInputLowPass.push_back(LowPass4<DownFactor>());
            }
            for (int chan = 0; chan < fDSP->getNumOutputs(); chan++) {
                fOutputLowPass.push_back(LowPass4<DownFactor>());
            }
        }
    
        virtual void init(int sample_rate)
        {
            fDSP->init(sample_rate/DownFactor);
        }
    
        virtual void instanceInit(int sample_rate)
        {
            fDSP->instanceInit(sample_rate/DownFactor);
        }
    
        virtual void instanceConstants(int sample_rate)
        {
            fDSP->instanceConstants(sample_rate/DownFactor);
        }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            int real_count = count/DownFactor;
           
            // Adapts inputs
            FAUSTFLOAT* fInputs[fDSP->getNumInputs()];
            for (int chan = 0; chan < fDSP->getNumInputs(); chan++) {
                // Lowpass filtering in place on the inputs
                fInputLowPass[chan].compute(count, inputs[chan], inputs[chan]);
                // Allocate fInputs with 'real_count' frames
                fInputs[chan] = (FAUSTFLOAT*)alloca(sizeof(FAUSTFLOAT) * real_count);
                // Decimate
                for (int frame = 0; frame < real_count; frame++) {
                    fInputs[chan][frame] = inputs[chan][frame * DownFactor];
                }
            }
            
            // Allocate fOutputs with 'real_count' frames
            FAUSTFLOAT* fOutputs[fDSP->getNumOutputs()];
            for (int chan = 0; chan < fDSP->getNumOutputs(); chan++) {
                fOutputs[chan] = (FAUSTFLOAT*)alloca(sizeof(FAUSTFLOAT) * real_count);
            }
            
            // Compute at lower rate
            fDSP->compute(real_count, fInputs, fOutputs);
            
            // Adapts outputs
            for (int chan = 0; chan < fDSP->getNumOutputs(); chan++) {
                for (int frame = 0; frame < real_count; frame++) {
                    // Copy one sample
                    outputs[chan][frame*DownFactor] = fOutputs[chan][frame];
                    // Then write 0 (DownFactor - 1) times
                    for (int step = 1; step < DownFactor; step++) {
                        outputs[chan][frame * DownFactor + step] = 0;
                    }
                }
                // Lowpass filtering in place on the output
                fOutputLowPass[chan].compute(count, outputs[chan], outputs[chan]);
            }
        }
    
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
};

#endif
/**************************  END  dsp-adapter.h **************************/
