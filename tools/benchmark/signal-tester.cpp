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
     
        compile("test1", signals, 0);
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

// process = _ <: @(+(0.5), 500), sin(@(@(+(0.5), 500), 600));

static void test4()
{
    COMPILER
    (
        tvec signals;
        Signal in1 = sigInput(0);
        signals.push_back(sigFixDelay(sigAdd(in1, sigReal(0.5)), sigReal(500)));
        signals.push_back(sigSin(sigFixDelay(sigFixDelay(sigAdd(in1, sigReal(0.5)), sigReal(500)), sigReal(600))));
        
        compile("test4", signals);
    )
}

// process = _ <: @(+(0.5), 500), @(*(1.5), 3000);

static void test5()
{
    createLibContext();
    
    tvec signals;
    Signal in1 = sigInput(0);
    signals.push_back(sigFixDelay(sigAdd(in1, sigReal(0.5)), sigReal(500)));
    signals.push_back(sigFixDelay(sigMul(in1, sigReal(1.5)), sigReal(3000)));
    
    // Vector compilation
    compile("test5", signals, 3, (const char* []){ "-vec", "-lv", "1" });

    destroyLibContext();
}

// process = _ <: @(+(0.5), 500), atan2(@(*(1.5), 3000), 0.5);

static void test6()
{
    COMPILER
    (
        tvec signals;
        Signal in1 = sigInput(0);
        signals.push_back(sigFixDelay(sigAdd(in1, sigReal(0.5)), sigReal(500)));
        signals.push_back(sigAtan2(sigFixDelay(sigMul(in1, sigReal(1.5)), sigReal(3000)), sigReal(0.5)));

        compile("test6", signals);
    )
}

// process = @(+(0.5), 500) * vslider("Vol", 0.5, 0, 1, 0.01);

static void test7()
{
    COMPILER
    (
        tvec signals;
        Signal in1 = sigInput(0);
        Signal slider = sigVSlider("Vol", sigReal(0.5), sigReal(0.0), sigReal(1.0), sigReal(0.01));
        signals.push_back(sigMul(slider, sigFixDelay(sigAdd(in1, sigReal(0.5)), sigReal(500))));
        
        compile("test7", signals);
    )
}

// process = + ~ _;

static void test8()
{
    COMPILER
    (
        tvec signals;
        Signal in1 = sigInput(0);
        signals.push_back(sigRecursion(sigAdd(sigSelf(), in1)));
        
        compile("test8", signals);
    )
}

// import("stdfaust.lib");
// process = ma.SR, ma.BS;

static void test9()
{
    COMPILER
    (
        tvec signals;
        signals.push_back(getSampleRate());
        signals.push_back(getBufferSize());
        
        compile("test9", signals);
    )
}

// process = waveform { 0, 100, 200, 300, 400 };

static void test10()
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
        
        compile("test10", signals);
     )
}

// process = waveform { 100+0, 100+100, 100+200, 100+300, 100+400 }; ==> failure

static void test11()
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
        
        compile("test11", signals);
     )
}

// process = _ <: +;

static void test12()
{
    COMPILER
    (
        tvec signals;
        Signal in1 = sigInput(0);
        signals.push_back(sigAdd(in1, in1));
     
        compile("test12", signals);
    )
}

// process = _,_ <: !,_,_,! :> _,_;

static void test13()
{
    COMPILER
    (
        tvec signals;
        Signal in1 = sigInput(0);
        Signal in2 = sigInput(1);
        signals.push_back(in2);
        signals.push_back(in1);
         
        compile("test13", signals);
    )
}

// process = _,_,_,_ : _,!,!,_;

static void test14()
{
    COMPILER
    (
        tvec signals;
        Signal in1 = sigInput(0);
        Signal in3 = sigInput(3);
        signals.push_back(in1);
        signals.push_back(in3);
         
        compile("test14", signals);
    )
}

/*
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

static void test15()
{
    COMPILER
    (
        tvec signals;
        signals.push_back(phasor(sigReal(440.0)));

        compile("test15", signals);
    )
}

/*
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

static void test16()
{
    COMPILER
    (
        tvec signals;
        signals.push_back(osc(sigReal(440.0)));
        signals.push_back(osc(sigReal(440.0)));

        compile("test16", signals);
    )
}

// process = 0,0 : soundfile("sound[url:{'tango.wav'}]", 1);

static void test17()
{
    COMPILER
    (
        tvec signals;
        Signal sf = sigSoundfile("sound[url:{'tango.wav'}]");
        signals.push_back(sigSoundfileLength(sf, sigInt(0)));
        signals.push_back(sigSoundfileRate(sf, sigInt(0)));
        signals.push_back(sigSoundfileLength(sf, sigInt(0)));
        signals.push_back(sigSoundfileBuffer(sf, sigInt(0), sigInt(0), sigInt(0)));
    
        compile("test17", signals);
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
    
    return 0;
}

