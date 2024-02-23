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

#include "faust/dsp/libfaust-box.h"
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
inline Box SR()
{
    return boxMin(boxReal(192000.0), boxMax(boxReal(1.0), boxFConst(SType::kSInt, "fSamplingFreq", "<math.h>")));
}

/**
 * Return the current runtime buffer size.
 *
 * Reproduce the 'BS' definition in platform.lib: BS = fvariable(int count, <math.h>);
 *
 * @return the current runtime buffer size.
 */
inline Box BS()
{
    return boxFVar(SType::kSInt, "count", "<math.h>");
}

/**
 * Creates a foreign function*
 */
inline Box SINH()
{
    return boxFFun(SType::kSReal, {"sinhf", "sinh", "sinhl", "sinhfx"}, { SType::kSReal }, "<FOO.h>",  "");
}

#define COMPILER(exp)    \
{                        \
    createLibContext();  \
    exp                  \
    destroyLibContext(); \
}                        \
    
static void compile(const string& name_app, Box box, int argc = 0, const char* argv[] = nullptr)
{
    string error_msg, source = createSourceFromBoxes(name_app, box, "cpp", argc, argv, error_msg);
    if (source != "") {
        cout << source;
    } else {
        cerr << error_msg;
    }
}

// process = ffunction(float sinhf|sinh|sinhl|sinhfx(float), <math.h>, "");

static void test0()
{
    COMPILER
    (
        compile("test0", SINH());
    )
}

// process = 7,3.14;

static void test1()
{
    COMPILER
    (
        Box box = boxPar(boxInt(7), boxReal(3.14));
     
        compile("test1", box);
    )
}

// process = _,3.14 : +;

static void test2()
{
    COMPILER
    (
        Box box = boxSeq(boxPar(boxWire(), boxReal(3.14)), boxAdd());
     
        compile("test2", box);
    )
}

// Alternate version with the binary 'boxAdd' version
// process = +(_,3.14);

static void test3()
{
    COMPILER
    (
        Box box = boxAdd(boxWire(), boxReal(3.14));
     
        compile("test3", box);
    )
}


// process = _,_ : +;

static void test4()
{
    COMPILER
    (
        Box box = boxSeq(boxPar(boxWire(), boxWire()), boxAdd());
     
        compile("test4", box);
    )
}

// Connection error
// process = _ : +;

static void test5()
{
    COMPILER
    (
        Box box = boxSeq(boxWire(), boxMul());
     
        compile("test5", box);
    )
}

// process = @(_,7);

static void test6()
{
    COMPILER
    (
        Box box = boxDelay(boxWire(), boxInt(7));
     
        compile("test6", box);
    )
}

// process = @(_,7);

static void test7()
{
    createLibContext();
    Box box = boxDelay(boxWire(), boxInt(7));
     
    // Vector compilation
    const char* argv[] = { "-vec", "-lv", "1" };
    compile("test7", box, 3, argv);
    destroyLibContext();
}

// process = _ <: @(500) + 0.5, @(3000) * 1.5;

static void test8()
{
    COMPILER
    (
        Box box = boxSplit(boxWire(), boxPar(boxAdd(boxDelay(boxWire(), boxReal(500)), boxReal(0.5)),
                                             boxMul(boxDelay(boxWire(), boxReal(3000)), boxReal(1.5))));
     
        compile("test8", box);
    )
}

// Equivalent signal expressions

static void equivalent1()
{
    COMPILER
    (
         Box b1 = boxAdd(boxDelay(boxWire(), boxReal(500)), boxReal(0.5));
         Box box = boxPar(b1, b1);
     
         compile("equivalent1", box);
    )
}

static void equivalent2()
{
    COMPILER
    (
        Box box = boxPar(boxAdd(boxDelay(boxWire(), boxReal(500)), boxReal(0.5)),
                         boxAdd(boxDelay(boxWire(), boxReal(500)), boxReal(0.5)));
     
        compile("equivalent2", box);
    )
}

// process = _,hslider("Freq [midi:ctrl 7][style:knob]", 100, 100, 2000, 1) : *;

static void test9()
{
    COMPILER
    (
        Box box = boxMul(boxWire(), boxHSlider("Freq [midi:ctrl 7][style:knob]", boxReal(100), boxReal(100), boxReal(2000), boxReal(1)));
        
        compile("test9", box);
    )
}

/*
 import("stdfaust.lib");
 
 freq = vslider("h:Oscillator/freq", 440, 50, 1000, 0.1);
 gain = vslider("h:Oscillator/gain", 0, 0, 1, 0.01);
 
 process = freq * gain;
 */

static void test10()
{
    COMPILER
    (
        Box box = boxMul(boxVSlider("h:Oscillator/freq", boxReal(440), boxReal(50), boxReal(1000), boxReal(0.1)),
                         boxVSlider("h:Oscillator/gain", boxReal(0), boxReal(0), boxReal(1), boxReal(0.01)));
     
        compile("test10", box);
    )
}

// import("stdfaust.lib");
// process = ma.SR, ma.BS;

static void test11()
{
    COMPILER
    (
        Box box = boxPar(SR(), BS());
     
        compile("test11", box);
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
             waveform.push_back(boxReal(100*i));
         }
         Box box = boxWaveform(waveform);   // the waveform content
     
         compile("test12", box);
    )
}

// process = _ <: +;

static void test13()
{
    COMPILER
    (
        Box box = boxSplit(boxWire(), boxAdd());
     
        compile("test13", box);
     )
}

// process = _,_ <: !,_,_,! :> _,_;

static void test14()
{
    COMPILER
    (
        Box box = boxSplit(boxPar(boxWire(), boxWire()),
                           boxMerge(boxPar4(boxCut(), boxWire(), boxWire(), boxCut()),
                                    boxPar(boxWire(), boxWire())));
     
        compile("test14", box);
    )
}

// process = + ~ _;

static void test15()
{
    COMPILER
    (
        Box box = boxRec(boxAdd(), boxWire());
     
        compile("test15", box);
    )
}

/*
import("stdfaust.lib");
process = phasor(440)
with {
    decimalpart = _,int(_) : -;
    phasor(f) = f/ma.SR : (+ <: decimalpart) ~ _;
};
*/

static Box decimalpart()
{
    return boxSub(boxWire(), boxIntCast(boxWire()));
}

static Box phasor(Box f)
{
    return boxSeq(boxDiv(f, SR()), boxRec(boxSplit(boxAdd(), decimalpart()), boxWire()));
}

static void test16()
{
    COMPILER
    (
        Box box = phasor(boxReal(440));
     
        compile("test16", box);
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

static Box osc(Box f)
{
    return boxSin(boxMul(boxMul(boxReal(2.0), boxReal(3.141592653)), phasor(f)));
}

static void test17()
{
    COMPILER
    (
        Box box = boxPar(osc(boxReal(440)), osc(boxReal(440)));
     
        compile("test17", box);
    )
}

// process = 0,0 : soundfile("sound[url:{'tango.wav'}]", 2);

static void test18()
{
    COMPILER
    (
        Box box = boxSoundfile("sound[url:{'tango.wav'}]", boxInt(2),  boxInt(0),  boxInt(0));
     
        compile("test18", box);
    )
}

// process = 10,1,int(_) : rdtable;

static void test19()
{
    COMPILER
    (
        Box box = boxReadOnlyTable(boxInt(10), boxInt(1), boxIntCast(boxWire()));
     
        compile("test19", box);
    )
}

// process = 10,1,int(_),int(_),int(_) : rwtable;

static void test20()
{
    COMPILER
    (
        Box box = boxWriteReadTable(boxInt(10), boxInt(1), boxIntCast(boxWire()), boxIntCast(boxWire()), boxIntCast(boxWire()));
     
        compile("test20", box);
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
static void test21(int argc, const char* argv[])
{
    cout << "test21\n";
    string error_msg;
    llvm_dsp_factory* factory = nullptr;
    
    createLibContext();
    {
        Box sl1 = boxVSlider("h:Oscillator/Freq1", boxReal(300), boxReal(100), boxReal(2000), boxReal(0.01));
        Box sl2 = boxVSlider("h:Oscillator/Freq2", boxReal(300), boxReal(100), boxReal(2000), boxReal(0.01));
        Box group = boxPar(osc(sl1), osc(sl2));
        Box box = boxVGroup("test21", group);
        
        factory = createDSPFactoryFromBoxes("FaustDSP", box, 0, nullptr, "", error_msg);
    }
    destroyLibContext();
    
    // The factory can be used outside of the createLibContext/destroyLibContext scope
    if (factory) {
        dsp* dsp = factory->createDSPInstance();
        assert(dsp);
        
        // Allocate audio driver
        jackaudio audio;
        audio.init("Test", dsp);
        
        // Create GUI
        GTKUI gtk_ui = GTKUI((char*)"Organ", &argc, (char***)&argv);
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

// Using the Interpreter backend.
static void test22(int argc, const char* argv[])
{
    cout << "test22\n";
    string error_msg;
    interpreter_dsp_factory* factory = nullptr;
    
    createLibContext();
    {
        Box sl1 = boxHSlider("v:Oscillator/Freq1", boxReal(300), boxReal(100), boxReal(2000), boxReal(0.01));
        Box sl2 = boxHSlider("v:Oscillator/Freq2", boxReal(300), boxReal(100), boxReal(2000), boxReal(0.01));
        Box group = boxPar(osc(sl1), osc(sl2));
        Box box = boxHGroup("test22", group);
 
        factory = createInterpreterDSPFactoryFromBoxes("FaustDSP", box, 0, nullptr, error_msg);
    }
    destroyLibContext();
    
    // The factory can be used outside of the createLibContext/destroyLibContext scope
    if (factory) {
        dsp* dsp = factory->createDSPInstance();
        assert(dsp);
        
        // Allocate audio driver
        jackaudio audio;
        audio.init("Test", dsp);
        
        // Create GUI
        GTKUI gtk_ui = GTKUI((char*)"Organ", &argc, (char***)&argv);
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

// Using the Interpreter backend.
static void test23(int argc, const char* argv[])
{
    cout << "test23\n";
    interpreter_dsp_factory* factory = nullptr;
    string error_msg;
    
    createLibContext();
    {
        Box sl1 = boxHSlider("v:Oscillator/Freq1", boxReal(300),
                             boxReal(100), boxReal(2000), boxReal(0.01));
        Box sl2 = boxHSlider("v:Oscillator/Freq2", boxReal(300),
                             boxReal(100), boxReal(2000), boxReal(0.01));
        Box group = boxPar(osc(sl1), osc(sl2));
        Box box = boxTGroup("test23", group);
    
        // Print the box
        cout << "Print the box\n";
        cout << printBox(box, false, INT_MAX);
    
        // Print the box in short form
        cout << "Print the box in short form\n";
        cout << printBox(box, false, 128);
    
        // Print the box in shared mode
        cout << "Print the box with shared identifiers\n";
        cout << printBox(box, true, INT_MAX);
        
        // Compile the 'box' to 'signals'
        tvec signals = boxesToSignals(box, error_msg);
    
        // Print the signals
        cout << "Print the signals\n";
        for (size_t i = 0; i < signals.size(); i++) {
            cout << printSignal(signals[i], false, INT_MAX) << endl;
        }
        cout << "Print the signals in short form\n";
        for (size_t i = 0; i < signals.size(); i++) {
            cout << printSignal(signals[i], false, 128) << endl;
        }
        // Print the signals in shared mode
        cout << "Print the signals in shared mode\n";
        for (size_t i = 0; i < signals.size(); i++) {
            cout << printSignal(signals[i], true, INT_MAX) << endl;
        }
        
        // Then compile the 'signals' to a DSP factory
        factory = createInterpreterDSPFactoryFromSignals("FaustDSP",
                                                         signals, 0,
                                                         nullptr, error_msg);
    }
    destroyLibContext();
    
    // The factory can be used outside of the createLibContext/destroyLibContext scope
    if (factory) {
        dsp* dsp = factory->createDSPInstance();
        assert(dsp);
        
        // Allocate audio driver
        jackaudio audio;
        audio.init("Test", dsp);
        
        // Create GUI
        GTKUI gtk_ui = GTKUI((char*)"Organ", &argc, (char***)&argv);
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
        cerr << error_msg;
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
static void test24(int argc, const char* argv[])
{
    cout << "test24\n";
    interpreter_dsp_factory* factory = nullptr;
    string error_msg;
    
    createLibContext();
    {
        // Follow the freq/gate/gain convention, see: https://faustdoc.grame.fr/manual/midi/#standard-polyphony-parameters
        Box freq = boxNumEntry("freq", boxReal(100), boxReal(100), boxReal(3000), boxReal(0.01));
        Box gate = boxButton("gate");
        Box gain = boxNumEntry("gain", boxReal(0.5), boxReal(0), boxReal(1), boxReal(0.01));
        Box organ = boxMul(gate, boxAdd(boxMul(osc(freq), gain), boxMul(osc(boxMul(freq, boxInt(2))), gain)));
        // Stereo
        Box box = boxPar(organ, organ);
        
        factory = createInterpreterDSPFactoryFromBoxes("FaustDSP", box, 0, nullptr, error_msg);
    }
    destroyLibContext();
        
    // The factory can be used outside of the createLibContext/destroyLibContext scope
    if (factory) {
        dsp* dsp = factory->createDSPInstance();
        assert(dsp);
        
        // Allocate polyphonic DSP
        dsp = new mydsp_poly(dsp, 8, true, true);
        
        // Allocate MIDI/audio driver
        jackaudio_midi audio;
        audio.init("Organ", dsp);
        
        // Create GUI
        GTKUI gtk_ui = GTKUI((char*)"Organ", &argc, (char***)&argv);
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

// Compile a complete DSP program to a box expression, then use the result in another expression
static void test26()
{
    cout << "test26\n";
    createLibContext();
    {
        int inputs = 0;
        int outputs = 0;
        string error_msg;
        
        // Create the filter without parameter
        Box filter = DSPToBoxes("FaustDSP", "import(\"stdfaust.lib\"); process = fi.lowpass(5);", 0, nullptr, &inputs, &outputs, error_msg);
        if (!filter) {
            cerr << error_msg;
            destroyLibContext();
            return;
        }
        // Create the filter parameters and connect
        Box cutoff = boxHSlider("cutoff", boxReal(300), boxReal(100), boxReal(2000), boxReal(0.01));
        Box cutoffAndInput = boxPar(cutoff, boxWire());
        Box filteredInput = boxSeq(cutoffAndInput, filter);
    
        getBoxType(filteredInput, &inputs, &outputs);
        std::cout << "getBoxType inputs: " << inputs << " outputs: " << outputs << std::endl;
    
        // Compile it
        string source = createSourceFromBoxes("FaustDSP", filteredInput, "cpp", 0, nullptr, error_msg);
        if (source != "") {
            cout << source;
        } else {
            cerr << error_msg;
        }
    }
    destroyLibContext();
}

list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

int main(int argc, const char* argv[])
{
    test0();
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    equivalent1();
    equivalent2();
    test8();
    test9();
    test10();
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
    
    // Test 'DSPToBoxes' API (1)
    test25();
    
    // Test 'DSPToBoxes/createSourceFromBoxes' API (2)
    test26();
    
    // Test with audio, GUI and LLVM backend
    test21(argc, argv);
    
    // Test with audio, GUI and Interp backend
    test22(argc, argv);
    
    // Test with audio, GUI and Interp backend and using 'boxesToSignals' function
    test23(argc, argv);
    
    // Test with audio, GUI, MIDI and Interp backend
    test24(argc, argv);
    
    return 0;
}

