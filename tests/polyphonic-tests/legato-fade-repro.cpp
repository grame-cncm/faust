/**
 * @file legato-fade-repro.cpp
 * @brief Regression reproducer for the level step on a stolen (legato) voice.
 *
 * When `mydsp_poly` steals a voice, `mydsp_poly::compute` renders that voice
 * across the block in two halves (`dsp_voice::computeLegato`): the note being
 * lost plays the first half, which `fadeOut` ramps down to 1/count; `keyOn` then
 * starts the next note and the second half is rendered from the DSP's live
 * state.
 *
 * `fadeOut` scales the buffer, not the voice.  A DSP whose envelope has not
 * reached silence -- every release that is longer than half a block, i.e.
 * every real instrument -- carries on at its current level after `keyOn`, so
 * the second half started at full level: a step from ~0 to the envelope's
 * value at the split, on every stolen note.  On a monophonic patch (one
 * voice, never silent between notes) that is a click on every note after the
 * first.  The correction fades the second half in, the mirror of the fade
 * out, so both halves meet near zero.
 *
 * Below, `sustained_tone` is a mono DSP with a one-pole envelope that follows
 * `gate * gain` slowly -- slow enough that half a block barely moves it.  One
 * voice plays note 60, then note 62 steals it.  On an unpatched tree the
 * largest sample-to-sample step inside the stolen block is the envelope's
 * level (~0.7); with the fade-in it is the ramp's own increment (< 0.02).
 *
 * This file is intentionally independent of an audio device and of generated
 * Faust code, like `voice-steal-repro.cpp`.
 */

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <list>
#include <vector>

#include "faust/dsp/poly-dsp.h"

// GUI owns these global registries.  Standalone architecture programs must
// provide their definitions, normally supplied by an architecture driver.
std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

/**
 * @brief Minimal mono DSP with an envelope that outlives half a block.
 *
 * The output is a one-pole follower of `gate * gain`: it rises when the gate
 * opens and decays when it closes, in both directions with a time constant
 * of ~1000 samples.  That is what a stolen voice looks like in practice --
 * the previous note is still sounding when the next one takes the voice.
 */
class sustained_tone : public dsp {

    private:

        /// Sample rate retained to fulfill the `dsp` instance contract.
        int fSampleRate = 0;

        /// MIDI note frequency written by `dsp_voice::keyOn`; not synthesized.
        FAUSTFLOAT fFrequency = FAUSTFLOAT(440);

        /// Velocity-derived amplitude the envelope follows.
        FAUSTFLOAT fGain = FAUSTFLOAT(0);

        /// Note gate set to one by key-on and cleared by key-off.
        FAUSTFLOAT fGate = FAUSTFLOAT(0);

        /// The envelope's current level -- the state `keyOn` does not reset.
        FAUSTFLOAT fLevel = FAUSTFLOAT(0);

    public:

        /// This test generator has no audio input.
        int getNumInputs() override { return 0; }

        /// One output is sufficient for `mydsp_poly` to compute voice levels.
        int getNumOutputs() override { return 1; }

        /// Return the sample rate saved by `instanceConstants`.
        int getSampleRate() override { return fSampleRate; }

        /// Declare the conventional `/freq`, `/gain`, `/gate` controls.
        void buildUserInterface(UI* ui) override
        {
            ui->openVerticalBox("sustained_tone");
            ui->addHorizontalSlider("freq", &fFrequency, FAUSTFLOAT(440), FAUSTFLOAT(20), FAUSTFLOAT(2000), FAUSTFLOAT(0.01));
            ui->addHorizontalSlider("gain", &fGain, FAUSTFLOAT(0.8), FAUSTFLOAT(0), FAUSTFLOAT(1), FAUSTFLOAT(0.01));
            ui->addButton("gate", &fGate);
            ui->closeBox();
        }

        /// Initialize constants, controls, and processing state as a DSP does.
        void init(int sample_rate) override { instanceInit(sample_rate); }

        /// Reset one instance completely while preserving the requested rate.
        void instanceInit(int sample_rate) override
        {
            instanceConstants(sample_rate);
            instanceResetUserInterface();
            instanceClear();
        }

        /// Store the rate.  The envelope's pole is per sample, not per second.
        void instanceConstants(int sample_rate) override { fSampleRate = sample_rate; }

        /// Restore the default UI state, in particular a closed gate.
        void instanceResetUserInterface() override
        {
            fFrequency = FAUSTFLOAT(440);
            fGain = FAUSTFLOAT(0.8);
            fGate = FAUSTFLOAT(0);
        }

        /// The envelope is the only processing state.
        void instanceClear() override { fLevel = FAUSTFLOAT(0); }

        /// Allocate an independent mono instance for each polyphonic slot.
        dsp* clone() override { return new sustained_tone(); }

        /// The reproducer has no metadata relevant to voice allocation.
        void metadata(Meta*) override {}

        /// One-pole envelope towards `gate * gain`, ~1000 samples time constant.
        void compute(int count, FAUSTFLOAT**, FAUSTFLOAT** outputs) override
        {
            const FAUSTFLOAT target = fGate * fGain;
            const FAUSTFLOAT pole = FAUSTFLOAT(0.999);
            for (int i = 0; i < count; i++) {
                fLevel = target + (fLevel - target) * pole;
                outputs[0][i] = fLevel;
            }
        }
};

/// The largest |x[n] - x[n-1]| in the block.
static FAUSTFLOAT largest_step(const FAUSTFLOAT* x, int count)
{
    FAUSTFLOAT step = 0;
    for (int i = 1; i < count; i++) {
        step = std::max(step, FAUSTFLOAT(std::fabs(x[i] - x[i - 1])));
    }
    return step;
}

int main()
{
    constexpr int kBlockSize = 128;
    constexpr int kVoices = 1;
    // A legitimate step is the fade's own increment: level / (kBlockSize / 2).
    // The bug's step is the whole level.  Half way between is a safe bound.
    const FAUSTFLOAT kMaxStep = FAUSTFLOAT(0.1);

    FAUSTFLOAT output[kBlockSize];
    FAUSTFLOAT* outputs[] = {output};

    mydsp_poly poly(new sustained_tone(), kVoices, true, false);
    poly.init(48000);

    // Note 60 plays long enough for its envelope to settle.
    poly.keyOn(0, 60, 100);
    for (int block = 0; block < 64; block++) {
        poly.compute(kBlockSize, nullptr, outputs);
    }
    const FAUSTFLOAT settled = output[kBlockSize - 1];
    const FAUSTFLOAT held_step = largest_step(output, kBlockSize);

    // Note 62 steals the only voice: this block is the legato hand-over.
    poly.keyOn(0, 62, 100);
    poly.compute(kBlockSize, nullptr, outputs);
    const FAUSTFLOAT stolen_step = largest_step(output, kBlockSize);
    const int half = kBlockSize / 2;

    std::cout << "1 voice, note 60 settled at " << settled
              << " (largest step while held: " << held_step << ").\n";
    std::cout << "note 62 steals it: samples around the split "
              << output[half - 2] << ' ' << output[half - 1] << " | "
              << output[half] << ' ' << output[half + 1]
              << ", largest step in the block: " << stolen_step << '\n';

    bool failed = false;
    // Sanity: a held note is a smooth signal, so any step found below is the
    // hand-over's own.
    if (held_step > kMaxStep) {
        std::cout << "BUG: the held note is not smooth; the test signal is wrong\n";
        failed = true;
    }
    if (stolen_step > kMaxStep) {
        std::cout << "BUG: the second half starts at the envelope's level instead of fading in\n";
        failed = true;
    }
    // The fade-in must reach unity: the block ends at the sustained level (the
    // new note's envelope has the same target), not somewhere below it.
    if (std::fabs(output[kBlockSize - 1] - settled) > kMaxStep) {
        std::cout << "BUG: the block does not end at the sustained level\n";
        failed = true;
    }
    return failed ? EXIT_FAILURE : EXIT_SUCCESS;
}
