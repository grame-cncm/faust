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

#include <libgen.h>
#include <iostream>
#include <string>
#include <vector>

#include "faust/dsp/libfaust-signal.h"
#include "faust/dsp/llvm-dsp.h"
#include "faust/dsp/interpreter-dsp.h"
#include "faust/dsp/poly-dsp.h"
#include "faust/audio/jack-dsp.h"
#include "faust/gui/GTKUI.h"
#include "faust/gui/MidiUI.h"
#include "faust/misc.h"

using namespace std;


/**
 * Return the current runtime sample rate.
 *
 * Reproduce the 'SR' definition in platform.lib: SR = min(192000.0, max(1.0, fconstant(int fSamplingFreq, <math.h>)));
 *
 * @return the current runtime sample rate.
 */
inline Signal SR()
{
    return sigMin(sigReal(192000.0), sigMax(sigReal(1.0), sigFConst(SType::kSInt, "fSamplingFreq", "<math.h>")));
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
    return sigFVar(SType::kSInt, "count", "<math.h>");
}


#define COMPILER(exp)    \
{                        \
    createLibContext();  \
    exp                  \
    destroyLibContext(); \
}                        \
    
static void compile(const string& name_app, tvec signals, int argc = 0, const char* argv[] = nullptr)
{
    string error_msg, source = createSourceFromSignals(name_app, signals, "cpp", argc, argv, error_msg);
    if (source != "") {
        cout << source;
    } else {
        cerr << error_msg;
    }
}

// process = 0.5;

static void test1()
{
    COMPILER
    (
        tvec signals;
        signals.push_back(sigReal(0.5));
     
        compile("test1", signals);
    )
}

// process = _ <: +(0.5), *(1.5);

static void test2()
{
    COMPILER
    (
        tvec signals;
        Signal in1 = sigInput(0);
        signals.push_back(sigAdd(in1, sigReal(0.5)));
        signals.push_back(sigMul(in1, sigReal(1.5)));
        
        compile("test2", signals);
     )
}

// process = _ <: @(+(0.5), 500), @(*(1.5), 3000);

static void test3()
{
    COMPILER
    (
        tvec signals;
        Signal in1 = sigInput(0);
        signals.push_back(sigDelay(sigAdd(in1, sigReal(0.5)), sigInt(500)));
        signals.push_back(sigDelay(sigMul(in1, sigReal(1.5)), sigInt(3000)));
         
        compile("test3", signals);
    )
}

// process = _ <: @(500) + 0.5, @(3000) * 1.5;

static void test4()
{
    COMPILER
    (
        tvec signals;
        Signal in1 = sigInput(0);
        signals.push_back(sigAdd(sigDelay(in1, sigInt(500)), sigReal(0.5)));
        signals.push_back(sigMul(sigDelay(in1, sigInt(3000)), sigReal(1.5)));

        compile("test4", signals);
    )
}

// process = _ <: @(+(0.5), 500), sin(@(@(+(0.5), 500), 600));

static void test5()
{
    COMPILER
    (
        tvec signals;
        Signal in1 = sigInput(0);
        signals.push_back(sigDelay(sigAdd(in1, sigReal(0.5)), sigInt(500)));
        signals.push_back(sigSin(sigDelay(sigDelay(sigAdd(in1, sigReal(0.5)), sigInt(500)), sigInt(600))));
        
        compile("test5", signals);
    )
}

// process = _ <: @(+(0.5), 500), @(*(1.5), 3000);

static void test6()
{
    createLibContext();
    
    tvec signals;
    Signal in1 = sigInput(0);
    signals.push_back(sigDelay(sigAdd(in1, sigReal(0.5)), sigInt(500)));
    signals.push_back(sigDelay(sigMul(in1, sigReal(1.5)), sigInt(3000)));
    
    // Vector compilation
    const char* argv[] = { "-vec", "-lv", "1" , "-double" };
    compile("test6", signals, 4, argv);

    destroyLibContext();
}

// process = _ <: @(+(0.5), 500), atan2(@(*(1.5), 3000), 0.5);

static void test7()
{
    COMPILER
    (
        tvec signals;
        Signal in1 = sigInput(0);
        signals.push_back(sigDelay(sigAdd(in1, sigReal(0.5)), sigInt(500)));
        signals.push_back(sigAtan2(sigDelay(sigMul(in1, sigReal(1.5)), sigInt(3000)), sigReal(0.5)));

        compile("test7", signals);
    )
}

// Equivalent signal expressions

static void equivalent1()
{
    COMPILER
    (
         tvec signals;
         Signal s1 = sigAdd(sigDelay(sigInput(0), sigInt(500)), sigReal(0.5));
         signals.push_back(s1);
         signals.push_back(s1);
         
         compile("equivalent1", signals);
     
         // Print the signals
         cout << "\nPrint the signals\n";
         for (size_t i = 0; i < signals.size(); i++) {
             cout << printSignal(signals[i], false, INT_MAX);
         }
     )
}

static void equivalent2()
{
    COMPILER
    (
         tvec signals;
         signals.push_back(sigAdd(sigDelay(sigInput(0), sigInt(500)), sigReal(0.5)));
         signals.push_back(sigAdd(sigDelay(sigInput(0), sigInt(500)), sigReal(0.5)));
     
         compile("equivalent2", signals);
     
         // Print the signals
         cout << "\nPrint the signals\n";
         for (size_t i = 0; i < signals.size(); i++) {
             cout << printSignal(signals[i], false, INT_MAX);
         }
    )
}

// Signals in normal form

static void normalform()
{
    COMPILER
    (
        tvec signals;
        signals.push_back(sigAdd(sigAdd(sigDelay(sigDelay(sigInput(0), sigReal(500)), sigReal(200)), sigReal(0.5)), sigReal(3)));
        signals.push_back(sigMul(sigMul(sigDelay(sigInput(0), sigInt(500)), sigReal(0.5)), sigReal(4)));

        compile("normalform", signals);

        // Print the signals
        cout << "\nPrint the signals\n";
        for (size_t i = 0; i < signals.size(); i++) {
            cout << printSignal(signals[i], false, INT_MAX);
        }
     
        cout << "\nPrint the signals in short form\n";
        for (size_t i = 0; i < signals.size(); i++) {
             cout << printSignal(signals[i], false, 128);
        }

        cout << "\nPrint the signals in shared form\n";
        for (size_t i = 0; i < signals.size(); i++) {
            cout << printSignal(signals[i], true, INT_MAX);
        }

        // Compute normal form
        tvec nf = simplifyToNormalForm2(signals);
     
        cout << "\nPrint the signals in normal form\n";
        for (size_t i = 0; i < nf.size(); i++) {
            cout << printSignal(nf[i], false, INT_MAX);
        }
     
        cout << "\nPrint the signals in short form\n";
        for (size_t i = 0; i < nf.size(); i++) {
            cout << printSignal(nf[i], false, 128);
        }

        cout << "\nPrint the signals in normal form in shared mode\n";
        for (size_t i = 0; i < nf.size(); i++) {
            cout << printSignal(nf[i], true, INT_MAX);
        }
     )
}

static void intervals()
{
    COMPILER
    (
        tvec signals;
     
        Signal s1 = sigAdd(sigAdd(sigDelay(sigDelay(sigInput(0), sigReal(500)), sigReal(200)), sigReal(0.5)), sigReal(3));
        Signal s2 = sigMul(sigMul(sigDelay(sigInput(0), sigInt(500)), sigReal(0.5)), sigReal(4));
        signals.push_back(s1);
        signals.push_back(s2);
         
        compile("intervals1", signals);
     
        Interval i1 = getSigInterval(s1);
        Interval i2 = getSigInterval(s2);
     
        cout << i1 << endl;
        cout << i2 << endl;
     
        Interval i3(48);
        Interval i4(-10, 10, 48);
        setSigInterval(s1, i3);
        setSigInterval(s2, i4);
     
        // Compute normal form
        tvec nf = simplifyToNormalForm2(signals);
         
        cout << "\nPrint the signals in normal form\n";
        for (size_t i = 0; i < nf.size(); i++) {
            cout << printSignal(nf[i], false, INT_MAX);
        }
         
        cout << "\nPrint the signals in short form\n";
        for (size_t i = 0; i < nf.size(); i++) {
            cout << printSignal(nf[i], false, 128);
        }
         
        cout << "\nPrint the signals in normal form in shared mode\n";
        for (size_t i = 0; i < nf.size(); i++) {
            cout << printSignal(nf[i], true, INT_MAX);
        }
     
        compile("intervals2", signals);
     )
}

// process = @(+(0.5), 500) * vslider("Vol", 0.5, 0, 1, 0.01);

static void test8()
{
    COMPILER
    (
        tvec signals;
        Signal in1 = sigInput(0);
        Signal slider = sigVSlider("Vol", sigReal(0.5), sigReal(0.0), sigReal(1.0), sigReal(0.01));
        signals.push_back(sigMul(slider, sigDelay(sigAdd(in1, sigReal(0.5)), sigInt(500))));
        
        compile("test8", signals);
    )
}

/*
import("stdfaust.lib");
 
freq = vslider("h:Oscillator/freq", 440, 50, 1000, 0.1);
gain = vslider("h:Oscillator/gain", 0, 0, 1, 0.01);
 
process = freq * gain;
*/

static void test9()
{
    COMPILER
    (
        tvec signals;
        Signal freq = sigVSlider("h:Oscillator/freq", sigReal(440), sigReal(50), sigReal(1000), sigReal(0.1));
        Signal gain = sigVSlider("h:Oscillator/gain", sigReal(0), sigReal(0), sigReal(1), sigReal(0.011));
        signals.push_back(sigMul(freq, sigMul(gain, sigInput(0))));
     
        compile("test9", signals);
     )
}

// process = + ~ _;

static void test10()
{
    COMPILER
    (
        tvec signals;
        Signal in1 = sigInput(0);
        signals.push_back(sigRecursion(sigAdd(sigSelf(), in1)));
        
        compile("test10", signals);
    )
}

// Alternate way of writing
static void test10bis()
{
    COMPILER
    (
        Signal in1 = sigInput(0);
        tvec ins;
        ins.push_back(sigAdd(sigSelfN(0), in1));
        tvec outs = sigRecursionN(ins);
     
        compile("test10bis", outs);
    )
}

// mutual recursion

/*
process = (cross : (+,+)) ~ (*(0.9),*(0.5))
with {
    // Route a,b, (recursive) and c,d (inputs) signals
    cross(a,b,c,d) = d,b,c,a;
};
*/

static void test10ter()
{
    COMPILER
    (
        Signal in0 = sigInput(0);
        Signal in1 = sigInput(1);
        tvec ins;
        ins.push_back(sigAdd(sigMul(sigSelfN(1), sigReal(0.5)), in0));
        ins.push_back(sigAdd(sigMul(sigSelfN(0), sigReal(0.9)), in1));
        tvec outs = sigRecursionN(ins);
        
        compile("test10ter", outs);
     )
}


// import("stdfaust.lib");
// process = ma.SR, ma.BS;

static void test11()
{
    COMPILER
    (
        tvec signals;
        signals.push_back(SR());
        signals.push_back(BS());
        
        compile("test11", signals);
    )
}

// process = waveform { 0, 100, 200, 300, 400 };

static void test12()
{
    COMPILER
    (
        tvec waveform;
        // Fill the waveform content vector
        for (int i = 0; i < 5; i++) {
            waveform.push_back(sigReal(100*i));
        }
        tvec signals;
        signals.push_back(sigInt(waveform.size())); // the waveform size
        signals.push_back(sigWaveform(waveform));   // the waveform content
        
        compile("test12", signals);
     )
}

// process = waveform { 100+0, 100+100, 100+200, 100+300, 100+400 }; ==> failure

static void test13()
{
    COMPILER
    (
        tvec waveform;
        for (int i = 0; i < 5; i++) {
            waveform.push_back(sigAdd(sigReal(100), sigReal(100*i)));
        }
        tvec signals;
        signals.push_back(sigInt(waveform.size())); // the waveform size
        signals.push_back(sigWaveform(waveform));   // the waveform content
        
        compile("test13", signals);
     )
}

// process = _ <: +;

static void test14()
{
    COMPILER
    (
        tvec signals;
        Signal in1 = sigInput(0);
        signals.push_back(sigAdd(in1, in1));
     
        compile("test14", signals);
    )
}

// process = _,_ <: !,_,_,! :> _,_;

static void test15()
{
    COMPILER
    (
        tvec signals;
        Signal in1 = sigInput(0);
        Signal in2 = sigInput(1);
        signals.push_back(in2);
        signals.push_back(in1);
         
        compile("test15", signals);
    )
}

// process = _,_,_,_ : _,!,!,_;

static void test16()
{
    COMPILER
    (
        tvec signals;
        Signal in1 = sigInput(0);
        Signal in3 = sigInput(3);
        signals.push_back(in1);
        signals.push_back(in3);
         
        compile("test16", signals);
    )
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
    return sigSub(x, sigIntCast(x));
}

static Signal phasor(Signal f)
{
    return sigRecursion(decimalpart(sigAdd(sigSelf(), sigDiv(f, SR()))));
}

static void test17()
{
    COMPILER
    (
        tvec signals;
        signals.push_back(phasor(sigReal(440.0)));

        compile("test17", signals);
    )
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
    return sigSin(sigMul(phasor(f), sigMul(sigReal(2.0), sigReal(3.141592653))));
}

static void test18()
{
    COMPILER
    (
        tvec signals;
        signals.push_back(osc(sigReal(440.0)));
        signals.push_back(osc(sigReal(440.0)));

        compile("test18", signals);
    )
}

// process = 0,0 : soundfile("sound[url:{'tango.wav'}]", 2);

static void test19()
{
    COMPILER
    (
         tvec signals;
         // Soundfile definition
         Signal sf = sigSoundfile("sound[url:{'tango.wav'}]");
         // Simple read index of 0
         Signal rdx = sigInt(0);
         // Part 0
         Signal part = sigInt(0);
         // Wrapped index to avoid reading outside the buffer
         Signal wridx = sigIntCast(sigMax(sigInt(0), sigMin(rdx, sigSub(sigSoundfileLength(sf, sigInt(0)), sigInt(1)))));
         // Accessing part 0 length
         signals.push_back(sigSoundfileLength(sf, part));
         // Accessing part 0 SR
         signals.push_back(sigSoundfileRate(sf, part));
         // Accessing chan 0 and part 0, with a wrapped read index
         signals.push_back(sigSoundfileBuffer(sf, sigInt(0), part, wridx));
         // Accessing chan 1 and part 0, with a wrapped read index
         signals.push_back(sigSoundfileBuffer(sf, sigInt(1), part, wridx));
     
         compile("test19", signals);
     )
}

// process = 10,1,int(_) : rdtable;

static void test20()
{
    COMPILER
    (
        tvec signals;
        signals.push_back(sigReadOnlyTable(sigInt(10), sigInt(1), sigIntCast(sigInput(0))));

        compile("test20", signals);
    )
}

// process = 10,1,int(_),int(_),int(_) : rwtable;

static void test21()
{
    COMPILER
    (
         tvec signals;
         signals.push_back(sigWriteReadTable(sigInt(10), sigInt(1), sigIntCast(sigInput(0)), sigIntCast(sigInput(1)), sigIntCast(sigInput(2))));
     
         compile("test21", signals);
     )
}

/*
 import("stdfaust.lib");
 process = osc(f1), osc(f2)
 with {
    decimalpart(x) = x-int(x);
    phasor(f) = f/ma.SR : (+ : decimalpart) ~ _;
    osc(f) = sin(2 * ma.PI * phasor(f));
    f1 = vslider("Freq1", 300, 100, 2000, 0.01);
    f2 = vslider("Freq2", 500, 100, 2000, 0.01);
 };
 */

// Using the LLVM backend.
static void test22(int argc, char* argv[])
{
    cout << "test22\n";
    createLibContext();
    {
        tvec signals;
        signals.push_back(osc(sigVSlider("h:Oscillator/Freq1", sigReal(300), sigReal(100), sigReal(2000), sigReal(0.01))));
        signals.push_back(osc(sigVSlider("h:Oscillator/Freq2", sigReal(500), sigReal(100), sigReal(2000), sigReal(0.01))));
     
        string error_msg;
        llvm_dsp_factory* factory = createDSPFactoryFromSignals("FaustDSP", signals, 0, nullptr, "", error_msg);
    
        if (factory) {
            dsp* dsp = factory->createDSPInstance();
            assert(dsp);
            
            // Allocate audio driver
            jackaudio audio;
            audio.init("Test", dsp);

            // Create GUI
            GTKUI gtk_ui = GTKUI((char*)"Organ", &argc, &argv);
            dsp->buildUserInterface(&gtk_ui);
            
            // Start real-time processing
            audio.start();
            
            // Start GUI
            gtk_ui.run();
            
            // Cleanup
            audio.stop();
            delete dsp;
            deleteDSPFactory(factory);
        } else {
            cerr << "Cannot create factory" << error_msg << endl;
        }
    }
    destroyLibContext();
}

// Using the Interpreter backend.
static void test23(int argc, char* argv[])
{
    cout << "test23\n";
    interpreter_dsp_factory* factory = nullptr;
    string error_msg;
    
    createLibContext();
    {
        tvec signals;
        signals.push_back(osc(sigHSlider("v:Oscillator/Freq1", sigReal(300), sigReal(100), sigReal(2000), sigReal(0.01))));
        signals.push_back(osc(sigHSlider("v:Oscillator/Freq2", sigReal(500), sigReal(100), sigReal(2000), sigReal(0.01))));
    
        factory = createInterpreterDSPFactoryFromSignals("FaustDSP", signals, 0, nullptr, error_msg);
    }
    destroyLibContext();
    
    // Use factory outside of the createLibContext/destroyLibContext scope
    if (factory) {
        dsp* dsp = factory->createDSPInstance();
        assert(dsp);
        
        // Allocate audio driver
        jackaudio audio;
        audio.init("Test", dsp);
        
        // Create GUI
        GTKUI gtk_ui = GTKUI((char*)"Organ", &argc, &argv);
        dsp->buildUserInterface(&gtk_ui);
        
        // Start real-time processing
        audio.start();
        
        // Start GUI
        gtk_ui.run();
        
        // Cleanup
        audio.stop();
        delete dsp;
        deleteInterpreterDSPFactory(factory);
    } else {
        cerr << "Cannot create factory" << error_msg << endl;
    }
}

/*
import("stdfaust.lib");
process = organ, organ
with {
    decimalpart(x) = x-int(x);
    phasor(f) = f/ma.SR : (+ : decimalpart) ~ _;
    osc(f) = sin(2 * ma.PI * phasor(f));
    freq = nentry("freq", 100, 100, 3000, 0.01);
    gate = button("gate");
    gain = nentry("gain", 0.5, 0, 1, 0.01);
    organ = gate * (osc(freq) * gain + osc(2 * freq) * gain);
};
*/

// Simple polyphonic DSP.
static void test24(int argc, char* argv[])
{
    cout << "test24\n";
    interpreter_dsp_factory* factory = nullptr;
    string error_msg;
    
    createLibContext();
    {
        tvec signals;
    
        // Follow the freq/gate/gain convention, see: https://faustdoc.grame.fr/manual/midi/#standard-polyphony-parameters
        Signal freq = sigNumEntry("freq", sigReal(100), sigReal(100), sigReal(3000), sigReal(0.01));
        Signal gate = sigButton("gate");
        Signal gain = sigNumEntry("gain", sigReal(0.5), sigReal(0), sigReal(1), sigReal(0.01));
        Signal organ = sigMul(gate, sigAdd(sigMul(osc(freq), gain), sigMul(osc(sigMul(freq, sigInt(2))), gain)));
        // Stereo
        signals.push_back(organ);
        signals.push_back(organ);
    
        factory = createInterpreterDSPFactoryFromSignals("FaustDSP", signals, 0, nullptr, error_msg);
    }
    destroyLibContext();
    
    // Use factory outside of the createLibContext/destroyLibContext scope
    if (factory) {
        dsp* dsp = factory->createDSPInstance();
        assert(dsp);
        
        // Allocate polyphonic DSP
        dsp = new mydsp_poly(dsp, 8, true, true);
        
        // Allocate MIDI/audio driver
        jackaudio_midi audio;
        audio.init("Organ", dsp);
        
        // Create GUI
        GTKUI gtk_ui = GTKUI((char*)"Organ", &argc, &argv);
        dsp->buildUserInterface(&gtk_ui);
        
        // Create MIDI controller
        MidiUI midi_ui = MidiUI(&audio);
        dsp->buildUserInterface(&midi_ui);
        
        // Start real-time processing
        audio.start();
        
        // Start MIDI
        midi_ui.run();
        
        // Start GUI
        gtk_ui.run();
        
        // Cleanup
        audio.stop();
        delete dsp;
        deleteInterpreterDSPFactory(factory);
    } else {
        cerr << "Cannot create factory" << error_msg << endl;
    }
}

// Compile a complete DSP program to a box expression, then to a source string
// in several target languages
static void test25()
{
    cout << "test25\n";
    vector<const char*> lang = { "c", "cpp", "cmajor", "codebox", "csharp", "dlang", "fir", "interp", "jax", "jsfx", "julia", "rust", "wast" };
    // Context has to be created/destroyed each time
    for (const auto& it : lang) {
        createLibContext();
        {
            int inputs = 0;
            int outputs = 0;
            string error_msg;
        
            // Create the oscillator
            Box osc = DSPToBoxes("FaustDSP", "import(\"stdfaust.lib\"); process = os.osc(440);", 0, nullptr, &inputs, &outputs, error_msg);
            if (!osc) {
                cerr << error_msg;
                destroyLibContext();
                return;
            }
        
            // Convert to signals
            tvec signals = boxesToSignals(osc, error_msg);
            if (signals.size() == 0) {
                cerr << error_msg;
                destroyLibContext();
                return;
            }
        
            // Compile it to the target language
            string source = createSourceFromBoxes("FaustDSP", osc, it, 0, nullptr, error_msg);
            if (source != "") {
                cout << source;
            } else {
                cerr << error_msg;
            }
        }
        destroyLibContext();
    }
}


list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

int main(int argc, char* argv[])
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    equivalent1();
    equivalent2();
    normalform();
    intervals();
    test8();
    test9();
    test10();
    test10bis();
    test10ter();
    test11();
    test12();
    test13();
    test14();
    test15();
    test16();
    test17();
    test18();
    test19();
    test20();
    test21();
    
    // Test 'DSPToBoxes' API (1)
    test25();
    
    // Test with audio, GUI and LLVM backend
    test22(argc, argv);
    
    // Test with audio, GUI and Interp backend
    test23(argc, argv);
    
    // Test with audio, GUI, MIDI and Interp backend
    test24(argc, argv);

    return 0;
}

