#include <iostream>
#include "faust/dsp/timed-dsp.h"

std::list<GUI*> GUI::fGuiList;
ztimedmap       GUI::gTimedZoneMap;

struct ControlDSP : dsp {
    FAUSTFLOAT value = 0;
    int        rate  = 0;
    int        getNumInputs() override { return 0; }
    int        getNumOutputs() override { return 1; }
    int        getSampleRate() override { return rate; }
    void buildUserInterface(UI* ui) override { ui->addNumEntry("value", &value, 0, 0, 10, 1); }
    void init(int sr) override { instanceInit(sr); }
    void instanceInit(int sr) override
    {
        instanceConstants(sr);
        instanceResetUserInterface();
    }
    void        instanceConstants(int sr) override { rate = sr; }
    void        instanceResetUserInterface() override { value = 0; }
    void        instanceClear() override {}
    ControlDSP* clone() override { return new ControlDSP; }
    void        metadata(Meta*) override {}
    void        compute(int count, FAUSTFLOAT**, FAUSTFLOAT** outputs) override
    {
        for (int i = 0; i < count; ++i) {
            outputs[0][i] = value;
        }
    }
};

struct TimedItem : uiTimedItem {
    TimedItem(GUI* ui, FAUSTFLOAT* zone) : uiTimedItem(ui, zone) {}
    void reflectZone() override {}
};

struct TestTimedDSP : timed_dsp {
    TestTimedDSP(dsp* processor) : timed_dsp(processor) {}
    double origin() const { return fDateUsec; }
};

int main()
{
    ControlDSP*  inner = new ControlDSP;
    TestTimedDSP processor(inner);
    GUI          ui;
    TimedItem*   control = new TimedItem(&ui, &inner->value);
    processor.buildUserInterface(&ui);
    processor.init(8000);
    FAUSTFLOAT  samples[8];
    FAUSTFLOAT* outputs[] = {samples};
    processor.compute(0.0, 0, nullptr, outputs);
    control->modifyZone(0, 1);
    control->modifyZone(processor.origin() + 1500, 2);
    control->modifyZone(processor.origin() + 2500, 3);
    int              failures       = 0;
    const FAUSTFLOAT expected[4][8] = {{1, 1, 1, 1, 1, 1, 1, 1},
                                       {1, 1, 1, 1, 2, 2, 2, 2},
                                       {2, 2, 2, 2, 3, 3, 3, 3},
                                       {3, 3, 3, 3, 3, 3, 3, 3}};
    // At 8 kHz a block lasts 1000 us. timed_dsp renders the previous block's events.
    for (int block = 0; block < 4; ++block) {
        processor.compute(double((block + 1) * 1000), 8, nullptr, outputs);
        std::cout << "block " << block << ":";
        for (int i = 0; i < 8; ++i) {
            std::cout << ' ' << samples[i];
            failures += samples[i] != expected[block][i];
        }
        std::cout << '\n';
    }
    // Events at the block boundary must remain queued until the next callback.
    const double start = processor.origin();
    control->modifyZone(start + 875, 4);
    control->modifyZone(start + 1000, 5);
    control->modifyZone(start + 1000, 6);
    control->modifyZone(start + 1125, 7);

    processor.compute(5000.0, 8, nullptr, outputs);
    for (int i = 0; i < 8; ++i) {
        failures += samples[i] != (i < 7 ? 3 : 4);
    }

    bool boundary_failed = inner->value != 4;
    std::cout << "Boundary state: "
              << (boundary_failed ? "FAIL" : "PASS") << '\n';

    processor.compute(6000.0, 8, nullptr, outputs);
    for (int i = 0; i < 8; ++i) {
        failures += samples[i] != (i == 0 ? 6 : 7);
    }

    // Frame-relative timestamps retain sample-accurate slicing within a block.
    control->modifyZone(0, 1);
    control->modifyZone(4, 2);
    processor.compute(-1.0, 8, nullptr, outputs);
    for (int i = 0; i < 8; ++i) {
        failures += samples[i] != (i < 4 ? 1 : 2);
    }
    std::cout << "frame block:";
    for (FAUSTFLOAT sample : samples) {
        std::cout << ' ' << sample;
    }
    std::cout << '\n';
    std::cout << "56 samples, " << failures << " failures\n";
    return (failures || boundary_failed) ? 1 : 0;
}
