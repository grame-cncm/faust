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
#include "faust/dsp/dsp-combiner.h"
#include "faust/audio/dummy-audio.h"
#include "faust/misc.h"

// Ciaramella C++ code
#include "ciaramella-code/lp_filter.cpp"
#include "ciaramella-code/lp_filter2.cpp"
#include "ciaramella-code/lp_filter3.cpp"
#include "ciaramella-code/lowshelffilter.cpp"
#include "ciaramella-code/diode_clipper.cpp"

// Faust C++ code
#include "ciaramella-code/lp_filter2_faust.cpp"

#define SAMPLE_RATE 44100

#define CUTOFF 0.8
#define VOL 0.9
#define GAIN 0.5

// Base Faust ciaramella adapter class
struct ciaramella_dsp : public dsp {

    ciaramella_dsp()
    {}
    
    virtual int getNumInputs() { return -1; }
    virtual int getNumOutputs() { return -1; }
    
    virtual void init(int sample_rate)
    {}
    
    virtual void instanceInit(int sample_rate)
    {}
    virtual void instanceConstants(int sample_rate)
    {}
    
    virtual void instanceResetUserInterface()
    {}
    
    virtual void instanceClear()
    {}
    
    virtual dsp* clone() { return new ciaramella_dsp(); }
    
    virtual void metadata(Meta* m) {}
    
    virtual void buildUserInterface(UI* ui_interface)
    {}
    
    virtual int getSampleRate() { return SAMPLE_RATE; }
    
    virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
    {}
};

// Faust adapter for lp_filter
struct ciaramella_lp_dsp : public ciaramella_dsp {
    
    lp_filter fFilter;
    
    ciaramella_lp_dsp()
    {}
    
    int getNumInputs() { return 1; }
    int getNumOutputs() { return 1; }
    
    void init(int sample_rate)
    {
        fFilter.setSampleRate(sample_rate);
        fFilter.reset();
        fFilter.setcutoff(CUTOFF);
    }
    
    dsp* clone() { return new ciaramella_lp_dsp(); }
    
    void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
    {
        fFilter.process(inputs[0], outputs[0], count);
    }
};

// Faust adapter for lp_filter2
struct ciaramella_lp2_dsp : public ciaramella_dsp {
    
    lp_filter2 fFilter;
    
    ciaramella_lp2_dsp()
    {}
    
    int getNumInputs() { return 1; }
    int getNumOutputs() { return 1; }
    
    void init(int sample_rate)
    {
        fFilter.setSampleRate(sample_rate);
        fFilter.reset();
        fFilter.setcutoff(CUTOFF);
    }
    
    dsp* clone() { return new ciaramella_lp2_dsp(); }
     
    void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
    {
        fFilter.process(inputs[0], outputs[0], count);
    }
};

// Faust adapter for lp_filter3
struct ciaramella_lp3_dsp : public ciaramella_dsp {
    
    lp_filter3 fFilter;
    
    ciaramella_lp3_dsp()
    {}
    
    int getNumInputs() { return 1; }
    int getNumOutputs() { return 1; }
    
    void init(int sample_rate)
    {
        fFilter.setSampleRate(sample_rate);
        fFilter.reset();
        fFilter.setcutoff(CUTOFF);
        fFilter.setvol(VOL);
    }
    
    dsp* clone() { return new ciaramella_lp3_dsp(); }
     
    void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
    {
        fFilter.process(inputs[0], outputs[0], count);
    }
};

// Faust adapter for lowshelffilter
struct ciaramella_lowshelffilter_dsp : public ciaramella_dsp {
    
    lowshelffilter fFilter;
    
    ciaramella_lowshelffilter_dsp()
    {}
    
    int getNumInputs() { return 1; }
    int getNumOutputs() { return 1; }
    
    void init(int sample_rate)
    {
        fFilter.setSampleRate(sample_rate);
        fFilter.reset();
        fFilter.setgain(GAIN);
    }
        
    dsp* clone() { return new ciaramella_lowshelffilter_dsp(); }
    
    void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
    {
        fFilter.process(inputs[0], outputs[0], count);
    }
};

// Faust adapter for diode_clipper
struct ciaramella_diode_clipper_dsp : public ciaramella_dsp {
    
    diode_clipper fDiode;
    
    ciaramella_diode_clipper_dsp()
    {}
    
    int getNumInputs() { return 1; }
    int getNumOutputs() { return 1; }
    
    void init(int sample_rate)
    {
        fDiode.setSampleRate(sample_rate);
        fDiode.reset();
    }
    
    dsp* clone() { return new ciaramella_diode_clipper_dsp(); }
    
    void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
    {
        fDiode.process(inputs[0], outputs[0], count);
    }
};

using namespace std;

#define COMPILER(exp)    \
{                        \
    createLibContext();  \
    exp                  \
    destroyLibContext(); \
}                        \

static tvec concat(tvec v1, tvec v2)
{
    v1.insert(v1.end(), v2.begin(), v2.end());
    return v1;
}

static void compile(const string& name_app, tvec signals, int argc = 0, const char* argv[] = nullptr)
{
    string error_msg, source = createSourceFromSignals(name_app, signals, "cpp", argc, argv, error_msg);
    if (source != "") {
        cout << source;
    } else {
        cerr << error_msg;
    }
}
/**
 * Return the current runtime sample rate.
 *
 * Reproduce the 'SR' definition in platform.lib: SR = fconstant(int fSamplingFreq, <math.h>);
 *
 * @return the current runtime sample rate.
 */
inline Signal fs()
{
    return sigFConst(SType::kSInt, "fSamplingFreq", "<math.h>");
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

// WDF based filters

// Create the PI constant
inline Signal pi()
{
    return sigReal(3.141592653589793);
}

// Faust and ciamarella DSP tester: send a same noise test signal in both DSPs.

typedef Signal (*signal_builder)();

static void filter_tester(signal_builder faust_dsp, dsp* ciaramella_dsp)
{
    // Create a noise test signal
    string error_msg;
    llvm_dsp_factory* noise_factory = createDSPFactoryFromString("FaustDSP",
                                                                 "import(\"stdfaust.lib\"); process = no.noise;",
                                                                 0, NULL, "",
                                                                 error_msg, -1);
    assert(noise_factory);
    
    dsp* noise_dsp = noise_factory->createDSPInstance();
    assert(noise_dsp);
    
    createLibContext();
    {
        // Create the filter using the signal API
        tvec signals = { faust_dsp() };
        
        // Compile the filter
        llvm_dsp_factory* filter_factory = createDSPFactoryFromSignals("FaustDSP", signals, 0, nullptr, "", error_msg);
        assert(filter_factory);
        
        // Instantiate the Faust filter
        dsp* filter_dsp = filter_factory->createDSPInstance();
        assert(filter_dsp);
        
        // Create the parallelizer with both filters
        dsp* parallel_dsp = createDSPParallelizer(ciaramella_dsp, filter_dsp, error_msg);
        
        // Split the noise test signal in both filters
        dsp* splitter = createDSPSplitter(noise_dsp, parallel_dsp, error_msg);
        
        // Render the audio
        dummyaudio audio(SAMPLE_RATE, 128, 1, 128);
        audio.init("Test", splitter);
        
        // Audio real-time processing
        audio.start();
        audio.stop();
        
        delete filter_dsp;
        deleteDSPFactory(filter_factory);
    }
    destroyLibContext();
    
    delete noise_dsp;
    deleteDSPFactory(noise_factory);
}

static void filter_tester2(dsp* faust_dsp, dsp* ciaramella_dsp)
{
    // Create a noise test signal
    string error_msg;
    llvm_dsp_factory* noise_factory = createDSPFactoryFromString("FaustDSP",
                                                                 "import(\"stdfaust.lib\"); process = no.noise;",
                                                                 0, NULL, "",
                                                                 error_msg, -1);
    assert(noise_factory);
    
    dsp* noise_dsp = noise_factory->createDSPInstance();
    assert(noise_dsp);

    // Create the parallelizer with both filters
    dsp* parallel_dsp = createDSPParallelizer(ciaramella_dsp, faust_dsp, error_msg);
    
    // Split the noise test signal in both filters
    dsp* splitter = createDSPSplitter(noise_dsp, parallel_dsp, error_msg);
    
    // Render the audio
    dummyaudio audio(SAMPLE_RATE, 128, 1, 128);
    audio.init("Test", splitter);
    
    // Audio real-time processing
    audio.start();
    audio.stop();
    
    delete noise_dsp;
    deleteDSPFactory(noise_factory);
}

/*
b, R0 = wdf_resistor(a, R) {
    b = 0
    R0 = R
}
*/
static tvec wdf_resistor(Signal a, Signal R)
{
    return { sigReal(0.0), R };
}

/*
b, R0 = wdf_capacitor(a, C) {
    b = delay1(a)
    R0 = 0.5 / (C * fs)
}
*/
static tvec wdf_capacitor(Signal a, Signal C)
{
    return { sigDelay1(a), sigDiv(sigReal(0.5), sigMul(C, fs())) };
}

/*
b = wdf_voltage_source_root(a, E) {
    b = 2 * E - a
}
*/
static Signal wdf_voltage_source_root(Signal a, Signal E)
{
    return sigSub(sigMul(sigReal(2), E), a);
}

/*
bu, bl, br, R0 = wdf_3port_series(au, al, ar, Rl, Rr) {
    bl = al - Rl / (Rl + Rr) * (al + ar + au)
    br = ar - Rr / (Rl + Rr) * (al + ar + au)
    bu = -(al + ar)
    R0 = Rl + Rr
}
*/
static tvec wdf_3port_series(Signal au, Signal al, Signal ar, Signal Rl, Signal Rr)
{
    Signal bl = sigSub(al, sigMul(sigDiv(Rl, sigAdd(Rl, Rr)), sigAdd(sigAdd(al, ar), au)));
    Signal br = sigSub(ar, sigMul(sigDiv(Rr, sigAdd(Rl, Rr)), sigAdd(sigAdd(al, ar), au)));
    Signal bu = sigSub(sigReal(0.0), sigAdd(al, ar));
    Signal R0 = sigAdd(Rl, Rr);
    return { bu, bl, br, R0 };
}

/*
bu, bl, br, R0 = wdf_3port_parallel(au, al, ar, Rl, Rr) {
    # Naive implementation
    bl = (dl - 1) * al + dr * ar + au
    br = dl * al + (dr - 1) * ar + au
    bu = dl * al + dr * ar
    
    R0 = (Rl * Rr) / (Rl + Rr)
    Gu = 1.0 / R0
    Gl = 1.0 / Rl
    Gr = 1.0 / Rr
    dl = 2.0 * Gl / (Gu + Gl + Gr)
    dr = 1.0 - dl
}
*/
static tvec wdf_3port_parallel(Signal au, Signal al, Signal ar, Signal Rl, Signal Rr)
{
    Signal R0 = sigDiv(sigMul(Rl, Rr), sigAdd(Rl, Rr));
    Signal Gu = sigDiv(sigReal(1.), R0);
    Signal Gl = sigDiv(sigReal(1.), Rl);
    Signal Gr = sigDiv(sigReal(1.), Rr);
    Signal dl = sigDiv(sigMul(sigReal(2.), Gl), sigAdd(sigAdd(Gu, Gl), Gr));
    Signal dr = sigSub(sigReal(1.), dl);
    
    Signal bl = sigAdd(sigAdd(sigMul(sigSub(dl, sigReal(1.)), al), sigMul(dr, ar)), au);
    Signal br = sigAdd(sigAdd(sigMul(dl, al), sigMul(sigSub(dr, sigReal(1.)), ar)), au);
    Signal bu = sigAdd(sigMul(dl, al), sigMul(dr, ar));
    
    return { bu, bl, br, R0 };
}

/*
y = lp_filter(x, cutoff) {
    fc = (0.1 + 0.3 * cutoff) * fs
    C = 1e-6
    R = 1 / (2 * pi * fc * C)
    
    bR, RR = wdf_resistor(aR, R)
    bC, RC = wdf_capacitor(aC, C)
    bV = wdf_voltage_source_root(aV, x)
    aV, aR, aC, Rp = wdf_3port_series(bV, bR, bC, RR, RC)
    @aC = 0
    
    y = 0.5 * (aC + bC)
}
*/
static Signal lp_filter(Signal x, Signal cutoff)
{
    Signal fc = sigMul(sigAdd(sigReal(0.1), sigMul(sigReal(0.3), cutoff)), fs());
    Signal C = sigReal(1e-6);
    Signal R = sigDiv(sigReal(1.0), sigMul(sigMul(sigMul(sigReal(2.0), pi()), fc), C));
    
    // Recursive signals
    Signal bR = sigSelfZeroN(0);
    Signal RR = sigSelfZeroN(1);
    Signal bC = sigSelfZeroN(2);
    Signal RC = sigSelfZeroN(3);
   
    Signal aV = sigSelfZeroN(4);
    Signal aR = sigSelfZeroN(5);
    Signal aC = sigSelfZeroN(6);
    Signal Rp = sigSelfZeroN(7);
    
    // bR, RR = wdf_resistor(aR, R);
    tvec res1 = wdf_resistor(aR, R);
    
    // bC, RC = wdf_capacitor(aC, C);
    tvec res2 = wdf_capacitor(aC, C);
    
    // bV = wdf_voltage_source_root(aV, x);
    Signal bV = wdf_voltage_source_root(aV, x);
    
    // aV, aR, aC, Rp = wdf_3port_series(bV, bR, bC, RR, RC);
    // Recursion is build here to access aV, aR, aC signals
    tvec res3 = wdf_3port_series(bV, bR, bC, RR, RC);
    
    // Create recursion
    tvec ins = concat(concat(res1, res2), res3);
    tvec outs = sigRecursionN(ins);
    
    // bC recursive signal explicitly taken again here
    // y = 0.5 * (aC + bC)
    aC = outs[6];
    bC = outs[2];
    
    return sigMul(sigReal(0.5), sigAdd(aC, bC));
}

/*
y = lp_filter3 (x, cutoff, vol) {
    y = lp_filter(lp_filter(lp_filter(x, cutoff), cutoff), cutoff) * vol
}
*/
static Signal lp_filter3(Signal x, Signal cutoff, Signal vol)
{
    return sigMul(lp_filter(lp_filter(lp_filter(x, cutoff), cutoff), cutoff), vol);
}

/*
 y = lp_filter2(x, cutoff) {
     # component values
     fc = (0.01 + 0.3 * cutoff) * fs
     C = 1e-6
     R = 1 / (2 * pi * fc * C)
     
     # input
     bV = wdf_voltage_source_root(aV, x)
     
     # filter 1
     bR1, RR1 = wdf_resistor(aR1, R)
     bC1, RC1 = wdf_capacitor(aC1, C)
     @aC1 = 0
     
     # filter 2
     bR2, RR2 = wdf_resistor(aR2, R)
     bC2, RC2 = wdf_capacitor(aC2, C)
     @aC2 = 0
     
     # connections
     aP1, aR2, aC2, Rp2 = wdf_3port_series(bP1, bR2, bC2, RR2, RC2)
     aS1, bP1, aC1, Rp1 = wdf_3port_parallel(bS1, aP1, bC1, Rp2, RC1)
     aV, aR1, bS1, Rp0 = wdf_3port_series(bV, bR1, aS1, RR1, Rp1)
     
     # output
     y = 0.5 * (aC2 + bC2)
}
*/

static Signal lp_filter2(Signal x, Signal cutoff)
{
    // component values
    // fc = (0.01 + 0.3 * cutoff) * fs
    // C = 1e-6
    // R = 1 / (2 * pi * fc * C)

    Signal fc = sigMul(sigAdd(sigReal(0.01), sigMul(sigReal(0.3), cutoff)), fs());
    Signal C = sigReal(1e-6);
    Signal R = sigDiv(sigReal(1.0), sigMul(sigMul(sigMul(sigReal(2.0), pi()), fc), C));
    
    // Recursive signals
    Signal aP1 = sigSelfZeroN(0);
    Signal aR2 = sigSelfZeroN(1);
    Signal aC2 = sigSelfZeroN(2);
    Signal Rp2 = sigSelfZeroN(3);
    
    Signal aS1 = sigSelfZeroN(4);
    Signal bP1 = sigSelfZeroN(5);
    Signal aC1 = sigSelfZeroN(6);
    Signal Rp1 = sigSelfZeroN(7);
    
    Signal aV = sigSelfZeroN(8);
    Signal aR1 = sigSelfZeroN(9);
    Signal bS1 = sigSelfZeroN(10);
    Signal Rp0 = sigSelfZeroN(11);
    
    // Input
    Signal bV = wdf_voltage_source_root(aV, x);
    //tvec res0 = { wdf_voltage_source_root(aV, x) };
    
    // filter 1
    // bR1, RR1 = wdf_resistor(aR1, R)
    // bC1, RC1 = wdf_capacitor(aC1, C)
    tvec res1 = wdf_resistor(aR1, R);
    tvec res2 = wdf_capacitor(aC1, C);
    
    // filter 2
    // bR2, RR2 = wdf_resistor(aR2, R)
    // bC2, RC2 = wdf_capacitor(aC2, C)
    tvec res3 = wdf_resistor(aR2, R);
    tvec res4 = wdf_capacitor(aC2, C);
    
    // connections
    // aP1, aR2, aC2, Rp2 = wdf_3port_series(bP1, bR2, bC2, RR2, RC2)
    // aS1, bP1, aC1, Rp1 = wdf_3port_parallel(bS1, aP1, bC1, Rp2, RC1)
    // aV, aR1, bS1, Rp0 = wdf_3port_series(bV, bR1, aS1, RR1, Rp1)
    tvec res5 = wdf_3port_series(bP1, res3[0], res4[0], res3[1], res4[1]);
    tvec res6 = wdf_3port_parallel(bS1, aP1, res2[0], Rp2, res2[1]);
    tvec res7 = wdf_3port_series(bV, res1[0], aS1, res1[1], Rp1);
    
    // Create recursion
    tvec ins = concat(concat(res5, res6), res7);
    tvec outs = sigRecursionN(ins);
    
    // output
    // y = 0.5 * (aC2 + bC2);
    aC2 = outs[2];
    Signal bC2 = wdf_capacitor(aC2, C)[0];
    return sigMul(sigReal(0.5), sigAdd(aC2, bC2));
}

/*
 y = lowshelffilter(x, gain) {
     K = gain
     f0 = 200
     z = (pi*f0)/fs
     
     a = (z - 1) / (z + 1)
     
     u = ((K - 1 ) / 2) * (a * x + delay1(x)) - a * delay1(u)
     @u = 0
     
     y = ((K + 1) / 2) * x + u
 }
 */
static Signal lowshelffilter(Signal x, Signal gain)
{
    Signal K = gain;
    Signal f0 = sigReal(200.);
    Signal z = sigDiv(sigMul(pi(), f0), fs());
    
    Signal a = sigDiv(sigSub(z, sigReal(1.)), sigAdd(z, sigReal(1.)));
    
    Signal n_u = sigRecursion(sigSub(sigMul(sigDiv(sigSub(K, sigReal(1.)), sigReal(2.)),
                                            sigAdd(sigMul(a, x), sigDelay1(x))), sigMul(a, sigDelay1(sigSelfZero()))));
    
    Signal y = sigAdd(sigMul(sigDiv(sigAdd(K, sigReal(1.)), sigReal(2.)), x), n_u);
    return y;
}

/*
y = diode_clipper (x) {
     Is = 1e-16
     VT = 0.026
     R = 2.2e3
     C = 0.01e-6
     
     k1 = 1.0 / (R * C)
     k4 = 1.0 / VT
     
     B0 = 2 * fs
     B1 = -B0
     A1 = 1
     
     k2 = (C * R) / (B0 * C * R + 1.0)
     k3 = (Is * R) / (B0 * C * R + 1.0)
     k5 = log((Is * R) / ((B0 * C * R + 1.0) * VT))
     k6 = B1 - A1 * B0
     
     p_z1 = delay1(p)
     q = k1 * x - p_z1
     r = sign(q)
     w = k2 * q + k3 * r
     y = w - VT * r * omega(k4 * r * w + k5)
     p = k6 * x - A1 * p_z1
     
     @p = 0
 }
*/

static Signal sign(Signal x)
{
    return sigSelect2(sigLT(x, sigReal(0.)), sigSelect2(sigGT(x, sigReal(0.)), sigReal(0.), sigReal(1.)), sigReal(-1.));
}
static Signal omega(Signal x) { return sigMax(sigReal(0.), x); }

static Signal diode_clipper(Signal x)
{
    Signal Is = sigReal(1e-16);
    Signal VT = sigReal(0.026);
    Signal R = sigReal(2.2e3);
    Signal C = sigReal(0.01e-6);
    
    Signal k1 = sigDiv(sigReal(1.), sigMul(R, C));
    Signal k4 = sigDiv(sigReal(1.), VT);
    
    Signal B0 = sigMul(sigReal(2.), fs());
    Signal B1 = sigSub(sigReal(0.), B0);
    Signal A1 = sigReal(1.);
    
    Signal k2 = sigDiv(sigMul(C, R), sigAdd(sigMul(sigMul(B0, C), R), sigReal(1.)));
    Signal k3 = sigDiv(sigMul(Is, R), sigAdd(sigMul(sigMul(B0, C), R), sigReal(1.)));
    Signal k5 = sigLog(sigDiv(sigMul(Is, R), sigMul(sigAdd(sigMul(sigMul(B0, C), R), sigReal(1.)), VT)));
    Signal k6 = sigSub(B1, sigMul(A1, B0));
    
    // Recursive signal
    Signal p = sigSelfZeroN(0);
    
    Signal p_z1 = sigDelay1(p);
    Signal q = sigSub(sigMul(k1, x), p_z1);
    Signal r = sign(q);
    Signal w = sigAdd(sigMul(k2, q), sigMul(k3, r));
    Signal y = sigSub(w, sigMul(sigMul(VT, r), omega(sigAdd(sigMul(sigMul(k4, r), w), k5))));
    tvec outs = sigRecursionN({sigSub(sigMul(k6, x), sigMul(A1, p_z1)), y});
    
    return outs[1];
}

// =======
// Tests
// =======

static Signal lp_filter_builder()
{
    Signal in1 = sigInput(0);
    Signal cutoff = sigVSlider("cutoff", sigReal(CUTOFF), sigReal(0), sigReal(1), sigReal(0.01));
    return lp_filter(in1, cutoff);
}

// Generate the Faust C++ output
static void test1()
{
    createLibContext();
    {
        tvec signals = { lp_filter_builder() };
        int argc = 2;
        const char* argv[] = { "-cn", "lp_filter" };
        compile("test1", signals, argc, argv);
    }
    destroyLibContext();
}

// Compare the Faust and Ciaramella versions with a same noise test signal
static void test2()
{
    filter_tester(lp_filter_builder, new ciaramella_lp_dsp());
}

static Signal lp_filter3_builder()
{
    Signal in1 = sigInput(0);
    Signal vol = sigVSlider("vol", sigReal(VOL), sigReal(0), sigReal(1), sigReal(0.01));
    Signal cutoff = sigVSlider("cutoff", sigReal(CUTOFF), sigReal(0), sigReal(1), sigReal(0.01));
    return lp_filter3(in1, cutoff, vol);
}

// Generate the Faust C++ output
static void test3()
{
    createLibContext();
    {
        tvec signals = { lp_filter3_builder() };
        int argc = 2;
        const char* argv[] = { "-cn", "lp_filter3" };
        compile("test3", signals, argc, argv);
    }
    destroyLibContext();
}

// Compare the Faust and Ciaramella versions with a same noise test signal
static void test4()
{
    filter_tester(lp_filter3_builder, new ciaramella_lp3_dsp());
}

static Signal lowshelffilter_builder()
{
    Signal in1 = sigInput(0);
    Signal gain = sigVSlider("gain", sigReal(GAIN), sigReal(0), sigReal(1), sigReal(0.01));
    return lowshelffilter(in1, gain);
}

// Generate the Faust C++ output
static void test5()
{
    createLibContext();
    {
        tvec signals = { lowshelffilter_builder() };
        int argc = 2;
        const char* argv[] = { "-cn", "lowshelffilter" };
        compile("test5", signals, argc, argv);
    }
    destroyLibContext();
}

// Compare the Faust and Ciaramella versions with a same noise test signal
static void test6()
{
    filter_tester(lowshelffilter_builder, new ciaramella_lowshelffilter_dsp());
}

static Signal lp_filter2_builder()
{
    Signal in1 = sigInput(0);
    Signal cutoff = sigVSlider("cutoff", sigReal(CUTOFF), sigReal(0), sigReal(1), sigReal(0.01));
    return lp_filter2(in1, cutoff);
}

// Generate the Faust C++ output
static void test7()
{
    createLibContext();
    {
        Signal in1 = sigInput(0);
        Signal cutoff = sigVSlider("cutoff", sigReal(CUTOFF), sigReal(0), sigReal(1), sigReal(0.01));
        
        tvec signals = { lp_filter2(in1, cutoff) };
        int argc = 2;
        const char* argv[] = { "-cn", "lp_filter2_faust" };
        compile("test7", signals, argc, argv);
    }
    destroyLibContext();
}

// Compare the Faust and Ciaramella versions with a same noise test signal
// lp_filter2_faust is manually edited to correct variable dependencies
static void test8()
{
    filter_tester2(new lp_filter2_faust(), new ciaramella_lp2_dsp());
}

static Signal diode_clipper_builder()
{
    Signal in1 = sigInput(0);
    return diode_clipper(in1);
}

// Generate the Faust C++ output
static void test9()
{
    createLibContext();
    {
        tvec signals = { diode_clipper_builder() };
        int argc = 2;
        const char* argv[] = { "-cn", "diode_clipper" };
        compile("test9", signals, argc, argv);
    }
    destroyLibContext();
}

// Compare the Faust and Ciaramella versions with a same noise test signal
static void test10()
{
    filter_tester(diode_clipper_builder, new ciaramella_diode_clipper_dsp());
}

int main(int argc, char* argv[])
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    // Incorrect code generated
    test7();
    // Test with manually edited to correct variable dependencies
    test8();
    test9();
    test10();
    return 0;
}

