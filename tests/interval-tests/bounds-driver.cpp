/*
 The driver of the interval tests : every slider and num entry at its minimum, then at
 its maximum, the inputs at -1 then 1, a few blocks of samples. Compiled with
 -fsanitize=array-bounds, an access out of a table stops the program.
*/

#include <cstdio>
#include <vector>

#include "faust/dsp/dsp.h"
#include "faust/gui/UI.h"
#include "faust/gui/meta.h"

<<includeIntrinsic>>

<<includeclass>>

struct BoundsUI : public UI {
    struct Zone {
        FAUSTFLOAT* zone;
        FAUSTFLOAT  min, max;
    };
    std::vector<Zone> fZones;

    void set(bool atMax)
    {
        for (const Zone& z : fZones) *z.zone = atMax ? z.max : z.min;
    }

    void openTabBox(const char*) override {}
    void openHorizontalBox(const char*) override {}
    void openVerticalBox(const char*) override {}
    void closeBox() override {}
    void addButton(const char*, FAUSTFLOAT* zone) override { fZones.push_back({zone, 0, 1}); }
    void addCheckButton(const char*, FAUSTFLOAT* zone) override { fZones.push_back({zone, 0, 1}); }
    void addVerticalSlider(const char*, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT min, FAUSTFLOAT max,
                           FAUSTFLOAT) override
    {
        fZones.push_back({zone, min, max});
    }
    void addHorizontalSlider(const char*, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT min,
                             FAUSTFLOAT max, FAUSTFLOAT) override
    {
        fZones.push_back({zone, min, max});
    }
    void addNumEntry(const char*, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT min, FAUSTFLOAT max,
                     FAUSTFLOAT) override
    {
        fZones.push_back({zone, min, max});
    }
    void addHorizontalBargraph(const char*, FAUSTFLOAT*, FAUSTFLOAT, FAUSTFLOAT) override {}
    void addVerticalBargraph(const char*, FAUSTFLOAT*, FAUSTFLOAT, FAUSTFLOAT) override {}
    void addSoundfile(const char*, const char*, Soundfile**) override {}
};

int main()
{
    const int count = 64;
    mydsp     dsp;
    dsp.init(48000);
    BoundsUI ui;
    dsp.buildUserInterface(&ui);
    std::vector<std::vector<FAUSTFLOAT>> in(dsp.getNumInputs(), std::vector<FAUSTFLOAT>(count));
    std::vector<std::vector<FAUSTFLOAT>> out(dsp.getNumOutputs(), std::vector<FAUSTFLOAT>(count));
    std::vector<FAUSTFLOAT*>             ins, outs;
    for (auto& v : in) ins.push_back(v.data());
    for (auto& v : out) outs.push_back(v.data());
    for (int side = 0; side < 2; side++) {
        ui.set(side == 1);
        for (auto& v : in) v.assign(count, side ? 1 : -1);
        for (int block = 0; block < 4; block++) dsp.compute(count, ins.data(), outs.data());
    }
    return 0;
}
