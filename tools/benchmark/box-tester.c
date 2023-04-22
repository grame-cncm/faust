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
#include <string.h>
#include <assert.h>

#include "faust/dsp/libfaust-box-c.h"
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
inline Box SR()
{
    return CboxMinAux(CboxReal(192000.0), CboxMaxAux(CboxReal(1.0), CboxFConst(kSInt, "fSamplingFreq", "<math.h>")));
}

/**
 * Return the current runtime buffer size.
 *
 * Reproduce the 'BS' definition in platform.lib: BS = fvariable(int count, <math.h>);
 *
 * @return the current runtime buffer size.
 */
inline Box getBufferSize()
{
    return CboxFVar(kSInt, "count", "<math.h>");
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

static Box decimalpart()
{
    return CboxSubAux(CboxWire(), CboxIntCastAux(CboxWire()));
}

static Box phasor(Box f)
{
    return CboxSeq(CboxDivAux(f, SR()), CboxRec(CboxSplit(CboxAdd(), decimalpart()), CboxWire()));
}

static void test1()
{
    printf("test1\n");
    createLibContext();
    {
        Box box = phasor(CboxReal(2000));
     
        char error_msg[4096];
        llvm_dsp_factory* factory = createCDSPFactoryFromBoxes("test1", box, 0, NULL, "", error_msg, -1);
            
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

static Box osc(Box f)
{
    return CboxSinAux(CboxMulAux(CboxMulAux(CboxReal(2.0), CboxReal(3.141592653)), phasor(f)));
}

static void test2()
{
    printf("test2\n");
    createLibContext();
    {
        Box box = CboxPar(osc(CboxReal(440.0)), osc(CboxReal(440.0)));
       
        char error_msg[4096];
        llvm_dsp_factory* factory = createCDSPFactoryFromBoxes("test2", box, 0, NULL, "", error_msg, -1);
        
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
    printf("test3\n");
    createLibContext();
    {
        Box freq = CboxVSlider("h:Oscillator/freq", CboxReal(440), CboxReal(50), CboxReal(1000), CboxReal(0.1));
        Box gain = CboxVSlider("h:Oscillator/gain", CboxReal(0), CboxReal(0), CboxReal(1), CboxReal(0.011));
        Box box = CboxMulAux(freq, CboxMulAux(gain, CboxWire()));
  
        char error_msg[4096];
        llvm_dsp_factory* factory = createCDSPFactoryFromBoxes("test3", box, 0, NULL, "", error_msg, -1);
        
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

// Compile a complete DSP program to a box expression, then use the result in another expression
static void test4()
{
    printf("test4\n");
    createLibContext();
    {
        int inputs = 0;
        int outputs = 0;
        char error_msg[4096];
        
        // Create the filter without parameter
        Box filter = CDSPToBoxes("FaustDSP", "import(\"stdfaust.lib\"); process = fi.lowpass(5);", 0, NULL, &inputs, &outputs, error_msg);
        if (!filter) {
            printf("%s", error_msg);
            destroyLibContext();
            return;
        }
        // Create the filter parameters and connect
        Box cutoff = CboxHSlider("cutoff", CboxReal(300), CboxReal(100), CboxReal(2000), CboxReal(0.01));
        Box cutoffAndInput = CboxPar(cutoff, CboxWire());
        Box filteredInput = CboxSeq(cutoffAndInput, filter);
        
        CgetBoxType(filteredInput, &inputs, &outputs);
        printf("CgetBoxType inputs: %d outputs: %d\n", inputs, outputs);
        
        llvm_dsp_factory* factory = createCDSPFactoryFromBoxes("test4", filteredInput, 0, NULL, "", error_msg, -1);
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
static void test5()
{
    printf("test25\n");
    const char* lang[] = { "c", "cpp", "cmajor", "csharp", "dlang", "interp", "jax", "julia", "rust", "wast" };
    // Context has to be created/destroyed each time
    for (int i = 0; i < 10; i++) {
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
            // Compile it
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

int main(int argc, const char* argv[])
{
    test1();
    test2();
    test3();
    test4();
    test5();
    
    return 0;
}

