// Bench architecture for the synthetic tests : the DSP on the heap, computed
// in blocks like print_arch.cpp, timed over several rounds, the best round
// printed as nanoseconds per frame (one number on stdout).
//   usage : <binary> [frames=48000] [samplerate=48000] [block=64] [rounds=7]
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <memory>
#include <vector>
#include <algorithm>
#include <cmath>

#include "faust/dsp/dsp.h"
#include "faust/gui/meta.h"
#include "faust/gui/DecoratorUI.h"

<<includeIntrinsic>>

<<includeclass>>

int main(int argc, char* argv[])
{
    int frames = (argc > 1) ? std::atoi(argv[1]) : 48000;
    int sr     = (argc > 2) ? std::atoi(argv[2]) : 48000;
    int block  = (argc > 3) ? std::atoi(argv[3]) : 64;
    int rounds = (argc > 4) ? std::atoi(argv[4]) : 7;
    if (frames <= 0) frames = 48000;
    if (sr <= 0) sr = 48000;
    if (block <= 0) block = 64;
    if (rounds <= 0) rounds = 7;

    std::unique_ptr<mydsp> dsp(new mydsp());
    dsp->init(sr);
    GenericUI ui;
    dsp->buildUserInterface(&ui);

    const int nin = dsp->getNumInputs(), nout = dsp->getNumOutputs();
    std::vector<std::vector<FAUSTFLOAT>> in(nin, std::vector<FAUSTFLOAT>(block, FAUSTFLOAT(0)));
    std::vector<std::vector<FAUSTFLOAT>> out(nout, std::vector<FAUSTFLOAT>(block, FAUSTFLOAT(0)));
    std::vector<FAUSTFLOAT*> inp(nin), outp(nout);
    for (int i = 0; i < nin; i++) inp[i] = in[i].data();
    for (int i = 0; i < nout; i++) outp[i] = out[i].data();

    double best = 1e300;
    volatile double sink = 0;  // the outputs are consumed, so nothing is dead
    for (int r = 0; r < rounds + 1; r++) {  // round 0 is the warm-up
        auto t0 = std::chrono::steady_clock::now();
        for (int done = 0; done < frames; done += block) {
            int n = std::min(block, frames - done);
            dsp->compute(n, nin ? inp.data() : nullptr, nout ? outp.data() : nullptr);
            for (int c = 0; c < nout; c++) sink += out[c][n - 1];
        }
        auto t1 = std::chrono::steady_clock::now();
        double ns = std::chrono::duration<double, std::nano>(t1 - t0).count() / frames;
        if (r > 0 && ns < best) best = ns;
    }
    if (!std::isfinite(sink)) std::fprintf(stderr, "non-finite output\n");
    std::printf("%.4f\n", best);
    return 0;
}
