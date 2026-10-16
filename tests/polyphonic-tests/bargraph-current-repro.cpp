/**
 * @file bargraph-current-repro.cpp
 * @brief Regression test for grouped polyphonic bargraph values.
 */

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <list>

#include "faust/dsp/poly-dsp.h"
#include "faust/gui/MidiUI.h"
#include "faust/midi/midi.h"

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

class bargraph_tone : public dsp {

    private:

        int fSampleRate = 0;
        FAUSTFLOAT fFrequency = FAUSTFLOAT(440);
        FAUSTFLOAT fGain = FAUSTFLOAT(0);
        FAUSTFLOAT fGate = FAUSTFLOAT(0);
        FAUSTFLOAT fMeter = FAUSTFLOAT(0);

    public:

        int getNumInputs() override { return 0; }
        int getNumOutputs() override { return 1; }
        int getSampleRate() override { return fSampleRate; }

        void buildUserInterface(UI* ui) override
        {
            ui->openVerticalBox("bargraph_tone");
            ui->addHorizontalSlider("freq", &fFrequency, FAUSTFLOAT(440), FAUSTFLOAT(20), FAUSTFLOAT(22500), FAUSTFLOAT(1));
            ui->addHorizontalSlider("gain", &fGain, FAUSTFLOAT(1), FAUSTFLOAT(0), FAUSTFLOAT(1), FAUSTFLOAT(0.01));
            ui->addButton("gate", &fGate);
            ui->addVerticalBargraph("param", &fMeter, FAUSTFLOAT(20), FAUSTFLOAT(22500));
            ui->closeBox();
        }

        void init(int sample_rate) override { instanceInit(sample_rate); }

        void instanceInit(int sample_rate) override
        {
            instanceConstants(sample_rate);
            instanceResetUserInterface();
            instanceClear();
        }

        void instanceConstants(int sample_rate) override { fSampleRate = sample_rate; }

        void instanceResetUserInterface() override
        {
            fFrequency = FAUSTFLOAT(440);
            fGain = FAUSTFLOAT(1);
            fGate = FAUSTFLOAT(0);
            fMeter = FAUSTFLOAT(0);
        }

        void instanceClear() override {}
        dsp* clone() override { return new bargraph_tone(); }
        void metadata(Meta*) override {}

        void compute(int count, FAUSTFLOAT**, FAUSTFLOAT** outputs) override
        {
            fMeter = fFrequency * fGain * fGate;
            std::fill(outputs[0], outputs[0] + count, fMeter);
        }
};

class BargraphUI : public GenericUI {

    public:

        FAUSTFLOAT* fZone = nullptr;

        void addHorizontalBargraph(const char*, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT) override { fZone = zone; }
        void addVerticalBargraph(const char*, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT) override { fZone = zone; }
};

int main()
{
    mydsp_poly poly(new bargraph_tone(), 2, true, true);
    poly.init(48000);

    // This is the path used by the Max external: MIDI is delivered through
    // a midi_interface that has registered the polyphonic DSP.
    midi_handler midi_handler;
    MidiUI midi_ui(&midi_handler);
    poly.buildUserInterface(&midi_ui);

    BargraphUI ui;
    poly.buildUserInterface(&ui);
    if (!ui.fZone) {
        std::cerr << "No bargraph was exposed by the grouped polyphonic UI.\n";
        return EXIT_FAILURE;
    }

    midi_handler.handleData2(0, midi::MIDI_NOTE_ON, 0, 60, 127);
    FAUSTFLOAT output[64];
    FAUSTFLOAT* outputs[] = {output};
    poly.compute(64, nullptr, outputs);
    GUI::updateAllGuis();

    if (*ui.fZone <= FAUSTFLOAT(20)) {
        std::cerr << "Grouped bargraph did not report the active voice value: " << *ui.fZone << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
