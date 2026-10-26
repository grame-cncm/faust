#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include "controlTools.h"

//----------------------------------------------------------------------------
// The controls driver : the impulse response with the controls driven inside their ranges.
// The certification decides on the whole range of each control, not on its default value
// (rule 6 of "The contract of a gate", tests/TESTING.md) : three passes, every slider,
// numerical entry and checkbox set to a value drawn inside its range (a function of its
// path and a fixed seed ; a checkbox is drawn 0 or 1, its range), then to its minimum,
// then to its maximum.
// Buttons are pressed during the first block of each pass, as in the impulse driver.
//----------------------------------------------------------------------------

struct RangeUI : public GenericUI {
    struct Range {
        FAUSTFLOAT* zone;
        double      min, max;
        bool        binary;  // a checkbox : 0 or 1, never in between
        std::string path;    // its groups and label : what its drawn value depends on
    };
    std::vector<Range>       fRanges;
    std::vector<std::string> fGroups;

    void openTabBox(const char* label) override { fGroups.push_back(label); }
    void openHorizontalBox(const char* label) override { fGroups.push_back(label); }
    void openVerticalBox(const char* label) override { fGroups.push_back(label); }
    void closeBox() override
    {
        if (!fGroups.empty()) fGroups.pop_back();
    }
    std::string path(const char* label) const
    {
        std::string p;
        for (const std::string& g : fGroups) p += g + "/";
        return p + label;
    }
    void addCheckButton(const char* label, FAUSTFLOAT* zone) override { fRanges.push_back({zone, 0, 1, true, path(label)}); }
    void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT) override
    {
        fRanges.push_back({zone, double(min), double(max), false, path(label)});
    }
    void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT) override
    {
        fRanges.push_back({zone, double(min), double(max), false, path(label)});
    }
    void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT) override
    {
        fRanges.push_back({zone, double(min), double(max), false, path(label)});
    }

    // the drawn value of a control depends on its path and the seed only, not on its rank : a
    // compiler that leaves out an unused control must not change the values of the others
    static double draw(const std::string& key, unsigned int seed)
    {
        unsigned long long h = 1469598103934665603ULL ^ seed;  // FNV-1a
        for (unsigned char c : key) {
            h ^= c;
            h *= 1099511628211ULL;
        }
        return double((h >> 20) & 0xffff) / 65535.0;
    }

    // pass 0 : drawn inside the range ; pass 1 : the minimum ; pass 2 : the maximum
    void set(int pass, unsigned int seed)
    {
        for (const Range& r : fRanges) {
            double u = 0;
            if (pass == 0) {
                u = draw(r.path, seed);  // the same draws on every machine
            } else {
                u = (pass == 1) ? 0.0 : 1.0;
            }
            if (r.binary) {
                u = (u < 0.5) ? 0.0 : 1.0;  // the range of a checkbox is {0, 1}
            }
            *r.zone = FAUSTFLOAT(r.min + u * (r.max - r.min));
        }
    }
};

static void runControlsDSP(dsp* DSP, int& linenum, int nbsamples, int pass, unsigned int seed)
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
