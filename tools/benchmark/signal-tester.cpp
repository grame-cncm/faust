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
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "faust/dsp/libfaust-signal.h"
#include "faust/misc.h"

using namespace std;

#define COMPILER(exp)    \
{                        \
    createLibContext();  \
    exp                  \
    destroyLibContext(); \
}                        \
    
static void compile(const string& name, tvec signals, int argc = 0, const char* argv[] = nullptr)
{
    string error_msg;
    dsp_factory_base* factory = compileDSPSignalFactory(argc, argv, name, signals, error_msg);
    if (factory) {
        factory->write(&cout);
        delete(factory);
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
        signals.push_back(sigFixDelay(sigAdd(in1, sigReal(0.5)), sigReal(500)));
        signals.push_back(sigFixDelay(sigMul(in1, sigReal(1.5)), sigReal(3000)));
         
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
        signals.push_back(sigAdd(sigFixDelay(in1, sigReal(500)), sigReal(0.5)));
        signals.push_back(sigMul(sigFixDelay(in1, sigReal(3000)), sigReal(1.5)));

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
        signals.push_back(sigFixDelay(sigAdd(in1, sigReal(0.5)), sigReal(500)));
        signals.push_back(sigSin(sigFixDelay(sigFixDelay(sigAdd(in1, sigReal(0.5)), sigReal(500)), sigReal(600))));
        
        compile("test5", signals);
    )
}

// process = _ <: @(+(0.5), 500), @(*(1.5), 3000);

static void test6()
{
    createLibContext();
    
    tvec signals;
    Signal in1 = sigInput(0);
    signals.push_back(sigFixDelay(sigAdd(in1, sigReal(0.5)), sigReal(500)));
    signals.push_back(sigFixDelay(sigMul(in1, sigReal(1.5)), sigReal(3000)));
    
    // Vector compilation
    compile("test6", signals, 3, (const char* []){ "-vec", "-lv", "1" });

    destroyLibContext();
}

// process = _ <: @(+(0.5), 500), atan2(@(*(1.5), 3000), 0.5);

static void test7()
{
    COMPILER
    (
        tvec signals;
        Signal in1 = sigInput(0);
        signals.push_back(sigFixDelay(sigAdd(in1, sigReal(0.5)), sigReal(500)));
        signals.push_back(sigAtan2(sigFixDelay(sigMul(in1, sigReal(1.5)), sigReal(3000)), sigReal(0.5)));

        compile("test7", signals);
    )
}

// Equivalent signal expressions
static void equivalent1()
{
    COMPILER
    (
         tvec signals;
         Signal s1 = sigAdd(sigFixDelay(sigInput(0), sigReal(500)), sigReal(0.5));
         signals.push_back(s1);
         signals.push_back(s1);
     
         compile("equivalent1", signals);
     )
}

static void equivalent2()
{
    COMPILER
    (
         tvec signals;
         signals.push_back(sigAdd(sigFixDelay(sigInput(0), sigReal(500)), sigReal(0.5)));
         signals.push_back(sigAdd(sigFixDelay(sigInput(0), sigReal(500)), sigReal(0.5)));
     
         compile("equivalent2", signals);
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
        signals.push_back(sigMul(slider, sigFixDelay(sigAdd(in1, sigReal(0.5)), sigReal(500))));
        
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

// import("stdfaust.lib");
// process = ma.SR, ma.BS;

static void test11()
{
    COMPILER
    (
        tvec signals;
        signals.push_back(getSampleRate());
        signals.push_back(getBufferSize());
        
        compile("test11", signals);
    )
}

// process = waveform { 0, 100, 200, 300, 400 };

static void test12()
{
    COMPILER
    (
        tvec waveform;
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
    return sigRecursion(decimalpart(sigAdd(sigSelf(), sigDiv(f, getSampleRate()))));
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

// process = 0,0 : soundfile("sound[url:{'tango.wav'}]", 1);

static void test19()
{
    COMPILER
    (
        tvec signals;
        Signal sf = sigSoundfile("sound[url:{'tango.wav'}]");
        signals.push_back(sigSoundfileLength(sf, sigInt(0)));
        signals.push_back(sigSoundfileRate(sf, sigInt(0)));
        signals.push_back(sigSoundfileLength(sf, sigInt(0)));
        signals.push_back(sigSoundfileBuffer(sf, sigInt(0), sigInt(0), sigInt(0)));
    
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
    test21();
    
    return 0;
}

