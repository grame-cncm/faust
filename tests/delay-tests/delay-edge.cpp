/*
 Runs the generated DSP class (-DGENERATED="file") with the controls at their declared minimum or
 maximum (CONTROLS_AT_MIN, CONTROLS_AT_MAX), or with a NaN in the input (NAN_INPUT).
 See README.md.
*/

#include <cmath>
#include <cstdio>
#include <limits>
#include <vector>

#include "faust/dsp/dsp.h"
#include "faust/gui/UI.h"
#include "faust/gui/meta.h"

#include GENERATED

#define COUNT 64

// Sets every slider and numerical entry to its declared minimum or maximum
struct EdgeUI : public UI {
    static FAUSTFLOAT edge(FAUSTFLOAT min, FAUSTFLOAT max)
    {
#ifdef CONTROLS_AT_MIN
        (void)max;
        return min;
#else
        (void)min;
        return max;
#endif
    }
    void openTabBox(const char*) override {}
    void openHorizontalBox(const char*) override {}
    void openVerticalBox(const char*) override {}
    void closeBox() override {}
    void addButton(const char*, FAUSTFLOAT*) override {}
    void addCheckButton(const char*, FAUSTFLOAT*) override {}
    void addVerticalSlider(const char*, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT min,
                           FAUSTFLOAT max, FAUSTFLOAT) override
    {
        *zone = edge(min, max);
    }
    void addHorizontalSlider(const char*, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT min,
                             FAUSTFLOAT max, FAUSTFLOAT) override
    {
        *zone = edge(min, max);
    }
    void addNumEntry(const char*, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT min, FAUSTFLOAT max,
                     FAUSTFLOAT) override
    {
        *zone = edge(min, max);
    }
    void addHorizontalBargraph(const char*, FAUSTFLOAT*, FAUSTFLOAT, FAUSTFLOAT) override {}
    void addVerticalBargraph(const char*, FAUSTFLOAT*, FAUSTFLOAT, FAUSTFLOAT) override {}
    void addSoundfile(const char*, const char*, Soundfile**) override {}
};

int main()
{
    mydsp* dsp = new mydsp();
    dsp->init(48000);
    EdgeUI ui;
    dsp->buildUserInterface(&ui);

    int                                  inputs  = dsp->getNumInputs();
    int                                  outputs = dsp->getNumOutputs();
    std::vector<std::vector<FAUSTFLOAT>> in(inputs, std::vector<FAUSTFLOAT>(COUNT));
    std::vector<std::vector<FAUSTFLOAT>> out(outputs, std::vector<FAUSTFLOAT>(COUNT));
    std::vector<FAUSTFLOAT*>             in_ptr(inputs), out_ptr(outputs);
    for (int chan = 0; chan < inputs; chan++) {
        for (int i = 0; i < COUNT; i++) {
            in[chan][i] = FAUSTFLOAT(i + 1) / FAUSTFLOAT(COUNT);
        }
#ifdef NAN_INPUT
        in[chan][3] = std::numeric_limits<FAUSTFLOAT>::quiet_NaN();
#endif
        in_ptr[chan] = in[chan].data();
    }
    for (int chan = 0; chan < outputs; chan++) {
        out_ptr[chan] = out[chan].data();
    }

    // Two blocks: the second one reads the values written by the first one
    dsp->compute(COUNT, in_ptr.data(), out_ptr.data());
    dsp->compute(COUNT, in_ptr.data(), out_ptr.data());

    delete dsp;
    printf("PASSED\n");
    return 0;
}
