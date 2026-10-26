#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include "controlTools.h"

//----------------------------------------------------------------------------
// The controls driver : the impulse response with the controls driven inside their ranges.
// The certification decides on the whole range of each control, not on its default value
// (rule 6 of "The contract of a gate", tests/TESTING.md) : three passes, every slider,
// numerical entry and checkbox set to a value drawn inside its range (fixed seed), then to
// its minimum, then to its maximum. Buttons are pressed during the first block of each pass,
// as in the impulse driver.
//----------------------------------------------------------------------------

struct RangeUI : public GenericUI {
    struct Range {
        FAUSTFLOAT* zone;
        double      min, max;
    };
    std::vector<Range> fRanges;

    void addCheckButton(const char*, FAUSTFLOAT* zone) override { fRanges.push_back({zone, 0, 1}); }
    void addVerticalSlider(const char*, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT) override
    {
        fRanges.push_back({zone, double(min), double(max)});
    }
    void addHorizontalSlider(const char*, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT) override
    {
        fRanges.push_back({zone, double(min), double(max)});
    }
    void addNumEntry(const char*, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT) override
    {
        fRanges.push_back({zone, double(min), double(max)});
    }

    // pass 0 : drawn inside the range ; pass 1 : the minimum ; pass 2 : the maximum
    void set(int pass, unsigned int& seed)
    {
        for (const Range& r : fRanges) {
            double u = 0;
            if (pass == 0) {
                seed = seed * 1103515245u + 12345u;  // the same draws on every machine
                u    = double((seed >> 8) & 0xffff) / 65535.0;
            } else {
                u = (pass == 1) ? 0.0 : 1.0;
            }
            *r.zone = FAUSTFLOAT(r.min + u * (r.max - r.min));
        }
    }
};

static void runControlsDSP(dsp* DSP, int& linenum, int nbsamples, int pass, unsigned int& seed)
{
    DSP->buildUserInterface(sound_ui);
    FUI finterface;
    DSP->buildUserInterface(&finterface);
    RangeUI ranges;
    DSP->buildUserInterface(&ranges);
    DSP->init(44100);
    ranges.set(pass, seed);

    int       nins  = DSP->getNumInputs();
    int       nouts = DSP->getNumOutputs();
    channels* ichan = new channels(kFrames, nins);
    channels* ochan = new channels(kFrames, nouts);

    int run = 0;
    int i   = 0;
    try {
        while (nbsamples > 0) {
            if (run == 0) {
                ichan->impulse();
                finterface.setButtons(true);
            } else {
                ichan->zero();
                finterface.setButtons(false);
            }
            int nFrames = min(kFrames, nbsamples);
            DSP->compute(nFrames, ichan->buffers(), ochan->buffers());
            run++;
            for (i = 0; i < nFrames; i++) {
                printf("%6d : ", linenum++);
                for (int c = 0; c < nouts; c++) {
                    FAUSTFLOAT f = normalize(ochan->buffers()[c][i]);
                    printf(" %8.6f", f);
                }
                printf("\n");
            }
            nbsamples -= nFrames;
        }
    } catch (...) {
        cerr << "ERROR in pass " << pass << " at line : " << i << std::endl;
    }
    delete ichan;
    delete ochan;
    delete DSP;
}

//----------------------------------------------------------------------------
//FAUST generated code
//----------------------------------------------------------------------------

<<includeIntrinsic>>

<<includeclass>>

int main(int argc, char* argv[])
{
    int          linenum = 0;
    int          pass    = 4000;  // samples per pass
    unsigned int seed    = 20261026;

    printHeader(new mydsp(), 3 * pass);
    for (int p = 0; p < 3; p++) {
        runControlsDSP(new mydsp(), linenum, pass, p, seed);
    }
    return 0;
}
