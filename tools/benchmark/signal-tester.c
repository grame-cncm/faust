/************************************************************************
 FAUST Architecture File
 Copyright (C) 2021 GRAME, Centre National de Creation Musicale
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

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <assert.h>

#include "faust/dsp/libfaust-box-c.h"
#include "faust/dsp/libfaust-signal-c.h"
#include "faust/dsp/llvm-dsp-c.h"
#include "faust/gui/PrintCUI.h"

#define BUFFER_SIZE 64
#define SAMPLE_RATE 44100

/**
 * Return the current runtime sample rate.
 *
 * Reproduce the 'SR' definition in platform.lib: SR = min(192000.0, max(1.0, fconstant(int fSamplingFreq, <math.h>)));
 *
 * @return the current runtime sample rate.
 */
inline Signal SR()
{
    return CsigMin(CsigReal(192000.0), CsigMax(CsigReal(1.0), CsigFConst(kSInt, "fSamplingFreq", "<math.h>")));
}

/**
 * Return the current runtime buffer size.
 *
 * Reproduce the 'BS' definition in platform.lib: BS = fvariable(int count, <math.h>);
 *
 * @return the current runtime buffer size.
 */
inline Signal BS()
{
    return CsigFVar(kSInt, "count", "<math.h>");
}

static void render(llvm_dsp* dsp)
{
    printf("=================render=================\n");
    printf("getNumInputs : %d\n", getNumInputsCDSPInstance(dsp));
    printf("getNumOutputs : %d\n", getNumOutputsCDSPInstance(dsp));
    
    // Init with audio driver SR
    instanceInitCDSPInstance(dsp, SAMPLE_RATE);

    // Compute one buffer
    FAUSTFLOAT* inputs[getNumInputsCDSPInstance(dsp)];
    FAUSTFLOAT* outputs[getNumOutputsCDSPInstance(dsp)];
    for (int chan = 0; chan < getNumInputsCDSPInstance(dsp); ++chan) {
        inputs[chan] = ( FAUSTFLOAT*)malloc(sizeof(FAUSTFLOAT) * BUFFER_SIZE);
    }
    for (int chan = 0; chan < getNumOutputsCDSPInstance(dsp); ++chan) {
        outputs[chan] = ( FAUSTFLOAT*)malloc(sizeof(FAUSTFLOAT) * BUFFER_SIZE);
    }
    computeCDSPInstance(dsp, BUFFER_SIZE, inputs, outputs);

    // Print output buffers
    for (int frame = 0; frame < BUFFER_SIZE; ++frame) {
        for (int chan = 0; chan < getNumOutputsCDSPInstance(dsp); ++chan) {
            printf("Audio output chan: %d sample: %f\n", chan, outputs[chan][frame]);
        }
    }

    for (int chan = 0; chan < getNumInputsCDSPInstance(dsp); ++chan) {
        free(inputs[chan]);
    }
    for (int chan = 0; chan < getNumOutputsCDSPInstance(dsp); ++chan) {
        free(outputs[chan]);
    }
}

/*
 import("stdfaust.lib");
 process = phasor(440)
 with {
     decimalpart(x) = x-int(x);
     phasor(f) = f/ma.SR : (+ : decimalpart) ~ _;
 };
 */

static Signal decimalpart(Signal x)
{
    return CsigSub(x, CsigIntCast(x));
}

static Signal phasor(Signal f)
{
    return CsigRecursion(decimalpart(CsigAdd(CsigSelf(), CsigDiv(f, SR()))));
}

static void test1()
{
    createLibContext();
    {
        Signal signals[2];
        signals[0] = phasor(CsigReal(2000));
        signals[1] = NULL; // Null terminated array
    
        printf("%s\n", CprintSignal(signals[0], false, INT_MAX));
        printf("%s\n", CprintSignal(signals[0], true, INT_MAX));
     
        char error_msg[4096];
        llvm_dsp_factory* factory = createCDSPFactoryFromSignals("test1", signals, 0, NULL, "", error_msg, -1);
            
        if (factory) {
            
            llvm_dsp* dsp = createCDSPInstance(factory);
            assert(dsp);
            
            // Render audio
            render(dsp);
            
            // Cleanup
            deleteCDSPInstance(dsp);
            deleteCDSPFactory(factory);
        
        } else {
            printf("Cannot create factory : %s\n", error_msg);
        }
    }
    destroyLibContext();
}

/*
 import("stdfaust.lib");
 process = osc(440), osc(440)
 with {
    decimalpart(x) = x-int(x);
    phasor(f) = f/ma.SR : (+ : decimalpart) ~ _;
    osc(f) = sin(2 * ma.PI * phasor(f));
 };
 */

static Signal osc(Signal f)
{
    return CsigSin(CsigMul(phasor(f), CsigMul(CsigReal(2.0), CsigReal(3.141592653))));
}

static void test2()
{
    createLibContext();
    {
        Signal signals[3];
        signals[0] = osc(CsigReal(440.0));
        signals[1] = osc(CsigReal(440.0));
        signals[2] = NULL; // Null terminated array
        
        char error_msg[4096];
        llvm_dsp_factory* factory = createCDSPFactoryFromSignals("test2", signals, 0, NULL, "", error_msg, -1);
        
        if (factory) {
            
            llvm_dsp* dsp = createCDSPInstance(factory);
            assert(dsp);
            
            // Render audio
            render(dsp);
            
            // Cleanup
            deleteCDSPInstance(dsp);
            deleteCDSPFactory(factory);
            
        } else {
            printf("Cannot create factory : %s\n", error_msg);
        }
    }
    destroyLibContext();
}

/*
 import("stdfaust.lib");
 
 freq = vslider("h:Oscillator/freq", 440, 50, 1000, 0.1);
 gain = vslider("h:Oscillator/gain", 0, 0, 1, 0.01);
 
 process = freq * gain;
 */

static void test3()
{
    createLibContext();
    {
        Signal signals[2];
        Signal freq = CsigVSlider("h:Oscillator/freq", CsigReal(440), CsigReal(50), CsigReal(1000), CsigReal(0.1));
        Signal gain = CsigVSlider("h:Oscillator/gain", CsigReal(0), CsigReal(0), CsigReal(1), CsigReal(0.011));
        signals[0] = CsigMul(freq, CsigMul(gain, CsigInput(0)));
        signals[1] = NULL; // Null terminated array

        char error_msg[4096];
        llvm_dsp_factory* factory = createCDSPFactoryFromSignals("test3", signals, 0, NULL, "", error_msg, -1);
        
        if (factory) {
            
            llvm_dsp* dsp = createCDSPInstance(factory);
            assert(dsp);
            
            printf("=================UI=================\n");
            
            // Defined in PrintCUI.h
            metadataCDSPInstance(dsp, &mglue);
            
            buildUserInterfaceCDSPInstance(dsp, &uglue);
            
            // Cleanup
            deleteCDSPInstance(dsp);
            deleteCDSPFactory(factory);
            
        } else {
            printf("Cannot create factory : %s\n", error_msg);
        }
    }
    destroyLibContext();
}

// Compile a complete DSP program to a box expression, then to a source string
// in several target languages
static void test4()
{
    printf("test4\n");
    const char* lang[] = { "c", "cpp", "cmajor", "codebox", "csharp", "dlang", "fir", "interp", "jax", "jsfx", "julia", "rust", "wast" };
    // Context has to be created/destroyed each time
    for (int i = 0; i < 13; i++) {
        createLibContext();
        {
            int inputs = 0;
            int outputs = 0;
            char error_msg[4096];
            
            // Create the oscillator
            Box osc = CDSPToBoxes("FaustDSP", "import(\"stdfaust.lib\"); process = os.osc(440);", 0, NULL, &inputs, &outputs, error_msg);
            if (!osc) {
                printf("%s", error_msg);
                destroyLibContext();
                return;
            }
        
            // Compile it to the target language
            char* source = CcreateSourceFromBoxes("FaustDSP", osc, lang[i], 0, NULL, error_msg);
            if (source) {
                printf("%s\n", source);
                freeCMemory(source);
            } else {
                printf("%s\n", error_msg);
            }
        }
        destroyLibContext();
    }
}

// Compile a complete DSP program to a box expression, then a list of signals, then to a source string
// in several target languages
static void test5()
{
    printf("test5\n");
    const char* lang[] = { "c", "cpp", "cmajor", "codebox", "csharp", "dlang", "fir", "interp", "jax", "jsfx", "julia", "rust", "wast" };
    // Context has to be created/destroyed each time
    for (int i = 0; i < 13; i++) {
        createLibContext();
        {
            int inputs = 0;
            int outputs = 0;
            char error_msg[4096];
            
            // Create the oscillator
            Box osc = CDSPToBoxes("FaustDSP", "import(\"stdfaust.lib\"); process = os.osc(440);", 0, NULL, &inputs, &outputs, error_msg);
            if (!osc) {
                printf("%s", error_msg);
                destroyLibContext();
                return;
            }
            
            // Compile to signals
            Signal* signals = CboxesToSignals(osc, error_msg);
            if (!signals) {
                printf("%s", error_msg);
                destroyLibContext();
                return;
            }
            
            // Compile signals to the target language
            char* source = CcreateSourceFromSignals("FaustDSP", signals, lang[i], 0, NULL, error_msg);
            if (source) {
                printf("%s\n", source);
                freeCMemory(source);
            } else {
                printf("%s\n", error_msg);
            }
        }
        destroyLibContext();
    }
}

int main(int argc, char* argv[])
{
    test1();
    test2();
    test3();
    test4();
    test5();
    
    return 0;
}

