// Print architecture for the synthetic tests : no input, no UI, the DSP on
// the heap, computed in blocks (so that the block boundaries of the emitters
// are exercised), every output sample printed with 17 significant digits.
//   usage : <binary> [frames=48000] [samplerate=48000] [block=64]
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include <algorithm>

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
    if (frames <= 0) frames = 48000;
    if (sr <= 0) sr = 48000;
    if (block <= 0) block = 64;

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

    std::cout << std::setprecision(17);
    for (int done = 0; done < frames; done += block) {
        int n = std::min(block, frames - done);
        dsp->compute(n, nin ? inp.data() : nullptr, nout ? outp.data() : nullptr);
        for (int f = 0; f < n; f++) {
            std::cout << (done + f);
            for (int c = 0; c < nout; c++) std::cout << '\t' << out[c][f];
            std::cout << '\n';
        }
    }
    return 0;
}
