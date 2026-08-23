/**
 * @file voice-steal-repro.cpp
 * @brief Regression reproducer for polyphonic voice stealing (PR #1284).
 *
 * `mydsp_poly` owns a fixed pool of voice instances.  When every instance is
 * active and a new MIDI note arrives, it must reuse the voice whose current
 * note has been held for the longest time.  Here, four voices hold notes
 * 60, 63, 65, and 68; the fifth note (70) must therefore replace note 60.
 *
 * Before PR #1284, `mydsp_poly::allocVoice` incremented a date stored in the
 * selected voice.  That made the date a per-slot allocation counter rather
 * than a global allocation timestamp.  Notes played and released before the
 * chord repeatedly reuse the first slot, increasing only that slot's date.
 * When the chord subsequently overflows the four-voice pool, the allocator
 * incorrectly considers the second slot to be older and steals note 63.
 *
 * The correction assigns each allocated voice the monotonically increasing
 * `mydsp_poly::fDate` value.  With that change, all scenarios in `main()`
 * return note 60 and the process exits successfully.  On an unpatched tree,
 * at least one scenario returns note 63 and the process exits with failure;
 * that failure is the intended proof that the bug is reproduced.
 *
 * This file is intentionally independent of an audio device and of generated
 * Faust code.  The small `held_tone` below implements only the standard
 * `freq`, `gain`, and `gate` controls recognized by `poly-dsp.h`.
 */

#include <algorithm>
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
 * @brief Minimal mono DSP used to drive `mydsp_poly`.
 *
 * The polyphonic wrapper discovers MIDI controls from their UI paths.  In
 * particular, labels ending in `/freq`, `/gain`, and `/gate` are mapped to
 * note pitch, velocity, and note-on/note-off state.  The audio signal itself
 * is deliberately constant: its only purpose is to become zero immediately
 * when `gate` is cleared, allowing a released voice to be returned to the
 * free pool after one render block.
 */
class held_tone : public dsp {

    private:

        /// Sample rate retained to fulfill the `dsp` instance contract.
        int fSampleRate = 0;

        /// MIDI note frequency written by `dsp_voice::keyOn`; not synthesized.
        FAUSTFLOAT fFrequency = FAUSTFLOAT(440);

        /// Velocity-derived amplitude used to make an active voice non-silent.
        FAUSTFLOAT fGain = FAUSTFLOAT(0);

        /// Note gate set to one by key-on and cleared by key-off.
        FAUSTFLOAT fGate = FAUSTFLOAT(0);

    public:

        /// This test generator has no audio input.
        int getNumInputs() override { return 0; }

        /// One output is sufficient for `mydsp_poly` to compute voice levels.
        int getNumOutputs() override { return 1; }

        /// Return the sample rate saved by `instanceConstants`.
        int getSampleRate() override { return fSampleRate; }

        /**
         * @brief Declare the conventional controls consumed by `dsp_voice`.
         *
         * The exact labels matter: `poly-dsp.h` finds controls by the suffixes
         * `/freq`, `/gain`, and `/gate` in their fully-qualified UI paths.
         */
        void buildUserInterface(UI* ui) override
        {
            ui->openVerticalBox("held_tone");
            ui->addHorizontalSlider("freq", &fFrequency, FAUSTFLOAT(440), FAUSTFLOAT(20), FAUSTFLOAT(2000), FAUSTFLOAT(0.01));
            ui->addHorizontalSlider("gain", &fGain, FAUSTFLOAT(0.8), FAUSTFLOAT(0), FAUSTFLOAT(1), FAUSTFLOAT(0.01));
            ui->addButton("gate", &fGate);
            ui->closeBox();
        }

        /// Initialize constants, controls, and processing state as a DSP does.
        void init(int sample_rate) override
        {
            instanceInit(sample_rate);
        }

        /// Reset one instance completely while preserving the requested rate.
        void instanceInit(int sample_rate) override
        {
            instanceConstants(sample_rate);
            instanceResetUserInterface();
            instanceClear();
        }

        /// Store the rate.  This signal has no rate-dependent coefficients.
        void instanceConstants(int sample_rate) override
        {
            fSampleRate = sample_rate;
        }

        /// Restore the default UI state, in particular a closed gate.
        void instanceResetUserInterface() override
        {
            fFrequency = FAUSTFLOAT(440);
            fGain = FAUSTFLOAT(0.8);
            fGate = FAUSTFLOAT(0);
        }

        /// No delay lines or other audio state are needed by this test signal.
        void instanceClear() override {}

        /// Allocate an independent mono instance for each polyphonic slot.
        dsp* clone() override { return new held_tone(); }

        /// The reproducer has no metadata relevant to voice allocation.
        void metadata(Meta*) override {}

        /**
         * @brief Render a constant block that represents the current gate.
         *
         * An active voice produces a non-zero value.  After key-off, `gate`
         * becomes zero; then `mydsp_poly::compute` observes a zero level and
         * marks that released voice free.  This mirrors the essential lifetime
         * behavior of the held organ tone in the original WASM reproducer.
         */
        void compute(int count, FAUSTFLOAT**, FAUSTFLOAT** outputs) override
        {
            const FAUSTFLOAT sample = fGate * fGain;
            std::fill(outputs[0], outputs[0] + count, sample);
        }
};

/**
 * @brief Advance the polyphonic renderer by one deterministic audio block.
 *
 * Rendering after every MIDI event is necessary: a voice stolen during a
 * `keyOn` is first marked as legato, then its replacement note is activated
 * by `mydsp_poly::compute`.  Rendering after each `keyOff` also lets the
 * minimal DSP become silent, freeing that slot for the next history note.
 */
static void render(mydsp_poly& poly)
{
    constexpr int kBlockSize = 64;
    FAUSTFLOAT output[kBlockSize];
    FAUSTFLOAT* outputs[] = {output};
    poly.compute(kBlockSize, nullptr, outputs);
}

/**
 * @brief Return the chord note absent after a five-note allocation.
 * @param history Notes played and released before the held chord.
 * @return The stolen MIDI note, or `kNoVoice` if every chord note remains.
 *
 * The history matches the gist linked from PR #1284.  It changes allocation
 * history without leaving audible notes allocated.  The final five notes are
 * pressed in order and never released, deliberately exceeding `kVoices` by
 * one.  Inspecting `fVoiceTable` after rendering is more robust than spectral
 * analysis for this architecture-level test and tests the allocator directly.
 */
static int stolen_note(const std::vector<int>& history)
{
    constexpr int kVoices = 4;
    const std::vector<int> chord = {60, 63, 65, 68, 70};

    // `mydsp_poly` takes ownership of this DSP.  Voice control enables MIDI
    // allocation; group control is irrelevant to allocation and disabled.
    mydsp_poly poly(new held_tone(), kVoices, true, false);
    poly.init(48000);

    // Each history note must leave the pool free before the next one starts.
    for (int note : history) {
        poly.keyOn(0, note, 100);
        render(poly);
        poly.keyOff(0, note);
        render(poly);
    }

    // Hold all five chord notes.  The final note forces voice stealing.
    for (int note : chord) {
        poly.keyOn(0, note, 100);
        render(poly);
    }

    // A completed legato replacement has its new MIDI pitch in `fCurNote`.
    std::vector<int> active_notes;
    for (dsp_voice* voice : poly.fVoiceTable) {
        if (voice->fCurNote >= 0) {
            active_notes.push_back(voice->fCurNote);
        }
    }

    // Exactly one chord note must be absent because there are only four slots.
    for (int note : chord) {
        if (std::find(active_notes.begin(), active_notes.end(), note) == active_notes.end()) {
            return note;
        }
    }

    return kNoVoice;
}

/**
 * @brief Execute the allocation scenarios from the associated WASM gist.
 *
 * The empty history is a control case and passes both before and after the
 * fix.  Every non-empty history exposes the old per-slot counter behavior.
 * Returning failure when a note other than 60 is stolen makes this executable
 * usable as a regression test after the PR is applied.
 */
int main()
{
    const std::vector<std::vector<int>> histories = {
        {}, {48}, {48, 50}, {48, 50, 52}, {48, 50, 52, 53, 55, 57}
    };
    bool failed = false;

    std::cout << "4 voices, then 5 held notes. Expected stolen note: 60.\n";
    for (const std::vector<int>& history : histories) {
        const int stolen = stolen_note(history);
        std::cout << "history size " << history.size() << ": stolen note " << stolen;
        if (stolen != 60) {
            std::cout << " (BUG: expected 60)";
            failed = true;
        }
        std::cout << '\n';
    }

    return failed ? EXIT_FAILURE : EXIT_SUCCESS;
}
