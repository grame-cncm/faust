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
static int envInt(const char* name, int dflt)
{
    const char* v = getenv(name);
    return v ? atoi(v) : dflt;
}

// Writes every widget's DECLARED default into its zone. Without this, the
// control values are whatever the heap held (ocpp assigns defaults only in
// buildUserInterface) : on programs whose per-sample work depends on a
// control (oscillator frequencies, enables), the measured cost was the
// cost of garbage -- observed 48 to 128 ns/frame on quantizedChords from
// one process to the next.
struct SetDefaultUI : public GenericUI {
    void addButton(const char*, FAUSTFLOAT* z) override { *z = 0; }
    void addCheckButton(const char*, FAUSTFLOAT* z) override { *z = 0; }
    void addVerticalSlider(const char*, FAUSTFLOAT* z, FAUSTFLOAT init, FAUSTFLOAT, FAUSTFLOAT,
                           FAUSTFLOAT) override
    {
        *z = init;
    }
    void addHorizontalSlider(const char*, FAUSTFLOAT* z, FAUSTFLOAT init, FAUSTFLOAT, FAUSTFLOAT,
                             FAUSTFLOAT) override
    {
        *z = init;
    }
    void addNumEntry(const char*, FAUSTFLOAT* z, FAUSTFLOAT init, FAUSTFLOAT, FAUSTFLOAT,
                     FAUSTFLOAT) override
    {
        *z = init;
    }
};

int main()
{
    const int count  = envInt("FLASH_COUNT", 512);
    const int warm   = envInt("FLASH_WARM", 400);
    const int reps   = envInt("FLASH_REPS", 30);
    const int blocks = envInt("FLASH_BLOCKS", 200);
    // FLASH_SCRUB=<KB> : between two blocks, dirty this much cache -- the
    // simulated concurrent workload that evicts the DSP state between real
    // audio callbacks (0 = back-to-back hot blocks). When active, timing
    // switches to per-block sums so the scrub cost itself stays OUT of the
    // measurement.
    const long scrubKB = envInt("FLASH_SCRUB", 0);

    mydsp* d = new mydsp();
    d->init(44100);
    SetDefaultUI ui;
    d->buildUserInterface(&ui);
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

    char*         scrub  = scrubKB ? new char[scrubKB * 1024] : nullptr;
    unsigned char scrubv = 1;
    auto          doScrub = [&]() {
        for (long i = 0; i < scrubKB * 1024; i += 64) {
            scrub[i] = char(i + scrubv);
        }
        scrubv++;
    };

    fill();
    // Core promotion (diagnosed on the 2026-08-23 measurements) : this
    // scheduler starts short processes on E-cores and only promotes
    // SUSTAINED work to P-cores. A flash run computes mere hundreds of
    // microseconds : it lived and died on an E-core whose DVFS steps
    // were our whole ladder of "mystery slow modes" (2.10, 2.46, 2.98,
    // 3.91, 4.76 -- one per frequency rung), lottery-drawn per process
    // against the desktop hum. ~200 ms of insistence buys the P-core
    // before anything is timed. FLASH_SPIN_MS=0 disables (forensics).
    {
        double spinMs = envInt("FLASH_SPIN_MS", 200);
        volatile double spin = 1.0;
        auto t0 = std::chrono::steady_clock::now();
        while (std::chrono::duration<double, std::milli>(
                   std::chrono::steady_clock::now() - t0).count() < spinMs) {
            for (int i = 0; i < 20000; i++) {
                spin = spin * 1.0000001 + 1e-9;
            }
        }
        if (spin < 0) printf("%f", spin);  // keep the loop observable
    }
    for (int w = 0; w < warm; w++) {
        d->compute(count, in, out);
    }

    double best = 1e30;
    for (int r = 0; r < reps; r++) {
        fill();
        double ns;
        if (scrub) {
            double sum = 0;
            for (int b = 0; b < blocks; b++) {
                doScrub();
                auto t0 = std::chrono::steady_clock::now();
                d->compute(count, in, out);
                auto t1 = std::chrono::steady_clock::now();
                sum += std::chrono::duration<double, std::nano>(t1 - t0).count();
            }
            ns = sum / (double(blocks) * double(count));
        } else {
            auto t0 = std::chrono::steady_clock::now();
            for (int b = 0; b < blocks; b++) {
                d->compute(count, in, out);
            }
            auto t1 = std::chrono::steady_clock::now();
            ns = std::chrono::duration<double, std::nano>(t1 - t0).count() /
                 (double(blocks) * double(count));
        }
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
