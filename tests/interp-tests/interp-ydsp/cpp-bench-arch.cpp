/*
 Faust architecture file: the C++ class of a DSP, timed like interp-fpb-bench.cpp times an FBC factory (same noise
 input, same blocks, best of 5 runs), to give the ceiling of the interp-ydsp bench (run-bench.py).

   faust -lang cpp -single -a cpp-bench-arch.cpp foo.dsp -o foo.cpp
   c++ -std=c++17 -O3 -ffp-contract=off -I <faust>/architecture foo.cpp -o foo
   foo [sampleRate 48000] [blockSize 128] [seconds 1]     prints {"ns": <ns per sample>}
*/

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "faust/dsp/dsp.h"
#include "faust/gui/UI.h"
#include "faust/gui/meta.h"

<<includeIntrinsic>>

<<includeclass>>

int main(int argc, char** argv)
{
    int    sr = argc > 1 ? atoi(argv[1]) : 48000, bs = argc > 2 ? atoi(argv[2]) : 128;
    double seconds = argc > 3 ? atof(argv[3]) : 1.0;
    mydsp  d;
    d.init(sr);
    std::vector<std::vector<FAUSTFLOAT>> in(d.getNumInputs(), std::vector<FAUSTFLOAT>(bs));
    std::vector<std::vector<FAUSTFLOAT>> out(d.getNumOutputs(), std::vector<FAUSTFLOAT>(bs));
    std::vector<FAUSTFLOAT*>             inp, outp;
    for (auto& c : in) inp.push_back(c.data());
    for (auto& c : out) outp.push_back(c.data());
    unsigned seed = 12345;
    for (auto& c : in) {
        for (auto& x : c) {
            seed = seed * 1103515245u + 12345u;
            x    = FAUSTFLOAT(seed / 4294967296.0 - 0.5);
        }
    }
    using clk = std::chrono::steady_clock;
    for (int k = 0; k < 200; k++) d.compute(bs, inp.data(), outp.data());
    double best = 1e30;
    for (int rep = 0; rep < 5; rep++) {
        long   n  = 0;
        auto   t0 = clk::now();
        double el = 0;
        do {
            for (int k = 0; k < 64; k++) d.compute(bs, inp.data(), outp.data());
            n += 64;
            el = std::chrono::duration<double>(clk::now() - t0).count();
        } while (el < seconds / 5);
        best = std::min(best, el * 1e9 / (double(n) * bs));
    }
    printf("{\"ns\": %.3f}\n", best);
    return 0;
}
