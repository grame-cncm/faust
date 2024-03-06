/* ------------------------------------------------------------
 name: "test7"
 Code generated with Faust 2.66.10 (https://faust.grame.fr)
 Compilation options: -lang cpp -ct 1 -cn lp_filter2_faust -es 1 -mcd 16 -single -ftz 0
 ------------------------------------------------------------ */

#ifndef  __lp_filter2_faust_H__
#define  __lp_filter2_faust_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS
#define FAUSTCLASS lp_filter2_faust
#endif

#ifdef __APPLE__
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif


class lp_filter2_faust : public dsp {
    
    private:
        
        FAUSTFLOAT fVslider0;
        float fRec1[2];
        int fSampleRate;
        float fConst1;
        float fConst2;
        float fConst3;
        float fRec5[2];
        float fConst4;
        
    public:
        lp_filter2_faust() {}
        
        void metadata(Meta* m) {
            m->declare("compile_options", "-lang cpp -ct 1 -cn lp_filter2_faust -es 1 -mcd 16 -single -ftz 0");
            m->declare("name", "test7");
        }
        
        virtual int getNumInputs() {
            return 1;
        }
        virtual int getNumOutputs() {
            return 1;
        }
        
        static void classInit(int sample_rate) {
        }
        
        virtual void instanceConstants(int sample_rate) {
            fSampleRate = sample_rate;
            float fConst0 = float(fSampleRate);
            fConst1 = 1.0f / fConst0;
            fConst2 = 2e-06f * fConst0;
            fConst3 = 5e+05f / fConst0;
            fConst4 = 159154.94f / fConst0;
        }
        
        virtual void instanceResetUserInterface() {
            fVslider0 = FAUSTFLOAT(0.8f);
        }
        
        virtual void instanceClear() {
            for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
                fRec1[l0] = 0.0f;
            }
            for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
                fRec5[l1] = 0.0f;
            }
        }
        
        virtual void init(int sample_rate) {
            classInit(sample_rate);
            instanceInit(sample_rate);
        }
        
        virtual void instanceInit(int sample_rate) {
            instanceConstants(sample_rate);
            instanceResetUserInterface();
            instanceClear();
        }
        
        virtual lp_filter2_faust* clone() {
            return new lp_filter2_faust();
        }
        
        virtual int getSampleRate() {
            return fSampleRate;
        }
        
        virtual void buildUserInterface(UI* ui_interface) {
            ui_interface->openVerticalBox("test7");
            ui_interface->addVerticalSlider("cutoff", &fVslider0, FAUSTFLOAT(0.8f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
            ui_interface->closeBox();
        }
        
        // Manually edited to correct variable dependencies
        virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
            FAUSTFLOAT* input0 = inputs[0];
            FAUSTFLOAT* output0 = outputs[0];
            float fSlow0 = 0.3f * float(fVslider0) + 0.01f;
            float fSlow1 = 159154.94f / fSlow0 + 5e+05f;
            float fSlow2 = 5e+05f / fSlow1;
            float fSlow3 = fConst1 * fSlow1;
            float fSlow4 = fConst4 / fSlow0;
            for (int i0 = 0; i0 < count; i0 = i0 + 1) {
                float fRec0 = -1.0f * fRec1[1];
                float fRec2 = fSlow3;
                float fTemp1 = fConst3 + fRec2;
                float fRec6 = fConst3 * (fRec2 / fTemp1);
                float fTemp7 = fSlow4 + fRec6;
                float fTemp2 = fRec2 * (fConst2 + (fConst2 * fTemp1 + 1.0f) / fRec2);
                float fTemp3 = 2.0f * (fRec0 / fTemp2);
                float fTemp4 = 2.0f / fTemp2;
                float fTemp5 = (1.0f - fTemp4) * fRec5[1];
                float fRec3 = fTemp3 + fTemp5;
                float fRec7 = -1.0f * fRec3;
                float fTemp6 = 2.0f * float(input0[i0]) + fRec3 - fRec7;
                float fRec8 = fRec3 - fRec6 * fTemp6 / fTemp7;
                float fRec4 = fRec0 * (fTemp4 + -1.0f) + fRec8 + fTemp5;
                float fTemp0 = fRec4 + fRec1[1];
                fRec1[0] = fRec1[1] - fSlow2 * fTemp0;
                fRec5[0] = fRec5[1] * (0.0f - fTemp4) + fRec8 + fTemp3;
                output0[i0] = FAUSTFLOAT(0.5f * (fRec1[0] + fRec1[1]));
                fRec1[1] = fRec1[0];
                fRec5[1] = fRec5[0];
            }
        }
        
};

#endif

