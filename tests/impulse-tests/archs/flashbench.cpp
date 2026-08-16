#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <chrono>
#include <cstdio>
#include <cstring>

#include "controlTools.h"

//----------------------------------------------------------------------------
// FAUST generated code
//----------------------------------------------------------------------------

<<includeIntrinsic>>

<<includeclass>>

// Flash-bench runner : deterministic pseudo-random input (an LCG -- silence
// would let a reverb settle to exact zeros and measure nothing), 512-frame
// blocks, warmup then repetitions, prints the BEST ns/frame (the min is the
// machine's clean answer, the rest is scheduling noise).
int main()
{
    const int count = 512, warm = 400, reps = 30, blocks = 200;

    mydsp* d = new mydsp();
    d->init(44100);
    int nins  = d->getNumInputs();
    int nouts = d->getNumOutputs();

    FAUSTFLOAT** in  = new FAUSTFLOAT*[nins ? nins : 1];
    FAUSTFLOAT** out = new FAUSTFLOAT*[nouts ? nouts : 1];
    for (int i = 0; i < nins; i++) {
        in[i] = new FAUSTFLOAT[count];
    }
    for (int i = 0; i < nouts; i++) {
        out[i] = new FAUSTFLOAT[count];
    }

    unsigned lcg  = 123456789u;
    auto     fill = [&]() {
        for (int i = 0; i < nins; i++) {
            for (int j = 0; j < count; j++) {
                lcg      = lcg * 1664525u + 1013904223u;
                in[i][j] = FAUSTFLOAT(int(lcg >> 9) % 65536 - 32768) / FAUSTFLOAT(32768);
            }
        }
    };

    fill();
    for (int w = 0; w < warm; w++) {
        d->compute(count, in, out);
    }

    double best = 1e30;
    for (int r = 0; r < reps; r++) {
        fill();
        auto t0 = std::chrono::steady_clock::now();
        for (int b = 0; b < blocks; b++) {
            d->compute(count, in, out);
        }
        auto   t1 = std::chrono::steady_clock::now();
        double ns = std::chrono::duration<double, std::nano>(t1 - t0).count() /
                    (double(blocks) * double(count));
        if (ns < best) {
            best = ns;
        }
    }
    // the output buffers must stay observable, or the whole loop is dead code
    double sink = 0;
    for (int i = 0; i < nouts; i++) {
        sink += double(out[i][count - 1]);
    }
    printf("%.3f ns/frame (sink %g)\n", best, sink);
    return 0;
}
