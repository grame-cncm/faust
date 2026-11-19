/*
 Runs an FBC file with the libfaust it is linked with: the plain interpreter (INTERP backend) or the interpreter
 with a compiled DSP block (INTERP_COMP backend, here built with INTERP_FPB_BUILD).

   interp-fpb-bench bench <file.fbc> [sampleRate 48000] [blockSize 128] [seconds 1]
       prints one JSON line: ns per sample (best of 5 runs), and the factory's compile options
   interp-fpb-bench dump <file.fbc> <out.f32> [blocks 400] [sampleRate 48000] [blockSize 128]
       writes the outputs (planar float32) for a fixed noise input; at the middle block every parameter is
       moved to 60 % of its range, so the control code is exercised too
   interp-fpb-bench multi <file.fbc> <out.f32>
       two instances of the same factory computed alternately (the FPB steps are bound to each instance's heaps)

 Set FAUST_INTERP_FPB_TRACE=1 to see whether the FPB compiler took the DSP block.
*/

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "faust/dsp/interpreter-dsp.h"
#include "faust/gui/UI.h"
#include "faust/gui/meta.h"

struct Zones : public UI {
    struct Z {
        FAUSTFLOAT* zone;
        FAUSTFLOAT  min, max;
    };
    std::vector<Z> fZones;
    void openTabBox(const char*) {}
    void openHorizontalBox(const char*) {}
    void openVerticalBox(const char*) {}
    void closeBox() {}
    void addButton(const char*, FAUSTFLOAT* z) { fZones.push_back({z, 0, 1}); }
    void addCheckButton(const char*, FAUSTFLOAT* z) { fZones.push_back({z, 0, 1}); }
    void addVerticalSlider(const char*, FAUSTFLOAT* z, FAUSTFLOAT, FAUSTFLOAT mn, FAUSTFLOAT mx, FAUSTFLOAT)
    {
        fZones.push_back({z, mn, mx});
    }
    void addHorizontalSlider(const char*, FAUSTFLOAT* z, FAUSTFLOAT, FAUSTFLOAT mn, FAUSTFLOAT mx, FAUSTFLOAT)
    {
        fZones.push_back({z, mn, mx});
    }
    void addNumEntry(const char*, FAUSTFLOAT* z, FAUSTFLOAT, FAUSTFLOAT mn, FAUSTFLOAT mx, FAUSTFLOAT)
    {
        fZones.push_back({z, mn, mx});
    }
    void addHorizontalBargraph(const char*, FAUSTFLOAT*, FAUSTFLOAT, FAUSTFLOAT) {}
    void addVerticalBargraph(const char*, FAUSTFLOAT*, FAUSTFLOAT, FAUSTFLOAT) {}
    void addSoundfile(const char*, const char*, Soundfile**) {}
    void declare(FAUSTFLOAT*, const char*, const char*) {}
};

struct Buffers {
    std::vector<std::vector<FAUSTFLOAT>> in, out;
    std::vector<FAUSTFLOAT*>             inp, outp;
    Buffers(int nIn, int nOut, int bs) : in(nIn, std::vector<FAUSTFLOAT>(bs)), out(nOut, std::vector<FAUSTFLOAT>(bs))
    {
        for (auto& c : in) inp.push_back(c.data());
        for (auto& c : out) outp.push_back(c.data());
    }
    void noise(unsigned& seed)
    {
        for (auto& c : in) {
            for (auto& x : c) {
                seed = seed * 1103515245u + 12345u;
                x    = FAUSTFLOAT(seed / 4294967296.0 - 0.5);
            }
        }
    }
};

static interpreter_dsp_factory* load(const char* file)
{
    std::string              err;
    interpreter_dsp_factory* f = readInterpreterDSPFactoryFromBitcodeFile(file, err);
    if (!f) {
        fprintf(stderr, "%s: %s\n", file, err.c_str());
        exit(2);
    }
    return f;
}

int main(int argc, char** argv)
{
    if (argc < 3) {
        fprintf(stderr, "usage: %s bench <file.fbc> [sr] [bs] [seconds] | dump <file.fbc> <out.f32> [blocks] [sr] [bs]\n",
                argv[0]);
        return 1;
    }
    std::string mode = argv[1];
    if (mode == "bench") {
        int    sr = argc > 3 ? atoi(argv[3]) : 48000, bs = argc > 4 ? atoi(argv[4]) : 128;
        double seconds = argc > 5 ? atof(argv[5]) : 1.0;
        interpreter_dsp_factory* f = load(argv[2]);
        dsp*                     d = f->createDSPInstance();
        d->init(sr);
        Buffers  b(d->getNumInputs(), d->getNumOutputs(), bs);
        unsigned seed = 12345;
        b.noise(seed);
        using clk = std::chrono::steady_clock;
        for (int k = 0; k < 200; k++) d->compute(bs, b.inp.data(), b.outp.data());
        double best = 1e30;
        for (int rep = 0; rep < 5; rep++) {
            long   n  = 0;
            auto   t0 = clk::now();
            double el = 0;
            do {
                for (int k = 0; k < 64; k++) d->compute(bs, b.inp.data(), b.outp.data());
                n += 64;
                el = std::chrono::duration<double>(clk::now() - t0).count();
            } while (el < seconds / 5);
            best = std::min(best, el * 1e9 / (double(n) * bs));
        }
        printf("{\"ns\": %.3f, \"options\": \"%s\"}\n", best, f->getCompileOptions().c_str());
        delete d;
        deleteInterpreterDSPFactory(f);
        return 0;
    }
    if (mode == "dump" && argc >= 4) {
        int blocks = argc > 4 ? atoi(argv[4]) : 400, sr = argc > 5 ? atoi(argv[5]) : 48000,
            bs = argc > 6 ? atoi(argv[6]) : 128;
        interpreter_dsp_factory* f = load(argv[2]);
        dsp*                     d = f->createDSPInstance();
        d->init(sr);
        Zones zones;
        d->buildUserInterface(&zones);
        int                     nOut = d->getNumOutputs();
        Buffers                 b(d->getNumInputs(), nOut, bs);
        std::vector<FAUSTFLOAT> all((size_t)nOut * blocks * bs);
        unsigned                seed = 12345;
        for (int k = 0; k < blocks; k++) {
            if (k == blocks / 2) {
                for (auto& z : zones.fZones) *z.zone = z.min + (z.max - z.min) * FAUSTFLOAT(0.6);
            }
            b.noise(seed);
            d->compute(bs, b.inp.data(), b.outp.data());
            for (int c = 0; c < nOut; c++) {
                memcpy(&all[((size_t)c * blocks + k) * bs], b.out[c].data(), bs * sizeof(FAUSTFLOAT));
            }
        }
        FILE* out = fopen(argv[3], "wb");
        if (!out) return 1;
        fwrite(all.data(), sizeof(FAUSTFLOAT), all.size(), out);
        fclose(out);
        delete d;
        deleteInterpreterDSPFactory(f);
        return 0;
    }
    if (mode == "multi" && argc >= 4) {
        // two instances of one factory, computed alternately with different inputs: both outputs are written
        int blocks = 200, sr = 48000, bs = 128;
        interpreter_dsp_factory* f = load(argv[2]);
        dsp*                     d[2] = {f->createDSPInstance(), f->createDSPInstance()};
        d[0]->init(sr);
        d[1]->init(sr);
        int                     nOut = d[0]->getNumOutputs();
        Buffers                 b0(d[0]->getNumInputs(), nOut, bs), b1(d[1]->getNumInputs(), nOut, bs);
        Buffers*                b[2] = {&b0, &b1};
        unsigned                seed[2] = {12345, 777};
        std::vector<FAUSTFLOAT> all((size_t)2 * nOut * blocks * bs);
        for (int k = 0; k < blocks; k++) {
            for (int j = 0; j < 2; j++) {
                b[j]->noise(seed[j]);
                d[j]->compute(bs, b[j]->inp.data(), b[j]->outp.data());
                for (int c = 0; c < nOut; c++) {
                    memcpy(&all[(((size_t)j * nOut + c) * blocks + k) * bs], b[j]->out[c].data(),
                           bs * sizeof(FAUSTFLOAT));
                }
            }
        }
        FILE* out = fopen(argv[3], "wb");
        if (!out) return 1;
        fwrite(all.data(), sizeof(FAUSTFLOAT), all.size(), out);
        fclose(out);
        delete d[0];
        delete d[1];
        deleteInterpreterDSPFactory(f);
        return 0;
    }
    fprintf(stderr, "unknown mode %s\n", mode.c_str());
    return 1;
}
