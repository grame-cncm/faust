/**
 * @file held-notes-repro.cpp
 * @brief Regression test for the held-note stack of `mydsp_poly` (monophonic
 * and duophonic behaviour, issue #252).
 *
 * `mydsp_poly` used to forget a key once another one stole its voice.  With
 * `nvoices:1`, holding A, pressing then releasing B left nothing sounding while
 * A was still down.  The engine now remembers every held key and reconciles the
 * voices with the keys that should sound, chosen by the `voicing`,
 * `note_priority` and `trigger` options.
 *
 * Each scenario below drives `mydsp_poly` with MIDI events and reads back the
 * pitches that are audible once the block has been rendered: voices with an
 * open gate whose note has started.  Besides the behaviour of the options, the
 * checks cover the cases a stack of held keys makes easy to get wrong:
 *  - a note that is still waiting for its legato crossfade when the next key
 *    arrives in the same block must still start;
 *  - a voice handed out by `newVoice()` is not the engine's to release;
 *  - a key pressed again while its note sounds must not leave a second voice
 *    that no key-off can reach;
 *  - the MIDI entry points run in the audio thread and must not allocate.
 *
 * This file is intentionally independent of an audio device and of generated
 * Faust code, like `voice-steal-repro.cpp`.
 */

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <list>
#include <new>
#include <string>
#include <vector>

#include "faust/dsp/poly-dsp.h"

// GUI owns these global registries.  Standalone architecture programs must
// provide their definitions, normally supplied by an architecture driver.
std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

// Count the heap allocations made while `gCountAllocations` is set.
static bool gCountAllocations = false;
static long gAllocations = 0;

void* operator new(std::size_t size)
{
    if (gCountAllocations) {
        gAllocations++;
    }
    void* ptr = std::malloc(size ? size : 1);
    if (!ptr) {
        throw std::bad_alloc();
    }
    return ptr;
}
void operator delete(void* ptr) noexcept { std::free(ptr); }
void operator delete(void* ptr, std::size_t) noexcept { std::free(ptr); }

/**
 * @brief Minimal mono DSP used to drive `mydsp_poly`.
 *
 * It has the `freq`, `gain` and `gate` controls that `dsp_voice` maps to note
 * pitch, velocity and note state.  Its output is `gate * gain`, so a released
 * voice becomes silent and is freed by the next rendered block.  With a release
 * tail, the output instead decays slowly after the gate closes, so that the
 * released voice is still sounding when the next key arrives, as with any
 * instrument that has a release.  The `options` metadata is the string given to
 * the constructor.
 */
class held_tone : public dsp {

    private:

        int fSampleRate = 0;
        FAUSTFLOAT fFrequency = FAUSTFLOAT(440);
        FAUSTFLOAT fGain = FAUSTFLOAT(0.8);
        FAUSTFLOAT fGate = FAUSTFLOAT(0);
        FAUSTFLOAT fEnvelope = FAUSTFLOAT(0);
        std::string fOptions;
        bool fReleaseTail;

    public:

        explicit held_tone(const std::string& options = "", bool release_tail = false)
        : fOptions(options), fReleaseTail(release_tail) {}

        int getNumInputs() override { return 0; }
        int getNumOutputs() override { return 1; }
        int getSampleRate() override { return fSampleRate; }

        void buildUserInterface(UI* ui) override
        {
            ui->openVerticalBox("held_tone");
            ui->addHorizontalSlider("freq", &fFrequency, FAUSTFLOAT(440), FAUSTFLOAT(20), FAUSTFLOAT(2000), FAUSTFLOAT(0.01));
            ui->addHorizontalSlider("gain", &fGain, FAUSTFLOAT(0.8), FAUSTFLOAT(0), FAUSTFLOAT(1), FAUSTFLOAT(0.01));
            ui->addButton("gate", &fGate);
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
            fGain = FAUSTFLOAT(0.8);
            fGate = FAUSTFLOAT(0);
        }

        void instanceClear() override { fEnvelope = FAUSTFLOAT(0); }

        dsp* clone() override { return new held_tone(fOptions, fReleaseTail); }

        void metadata(Meta* m) override
        {
            if (!fOptions.empty()) {
                m->declare("options", fOptions.c_str());
            }
        }

        void compute(int count, FAUSTFLOAT**, FAUSTFLOAT** outputs) override
        {
            for (int i = 0; i < count; i++) {
                fEnvelope = (fReleaseTail && fGate <= FAUSTFLOAT(0)) ? fEnvelope * FAUSTFLOAT(0.9995) : fGate;
                outputs[0][i] = fEnvelope * fGain;
            }
        }
};

static int gChecks = 0;
static int gFailures = 0;

/// Record one check, and describe it when it fails.
static void check(bool ok, const char* scenario, const std::string& what)
{
    gChecks++;
    if (!ok) {
        gFailures++;
        std::printf("FAIL %s: %s\n", scenario, what.c_str());
    }
}

/// Render the pitches as "[60 64]", for failure messages.
static std::string show(const std::vector<int>& pitches)
{
    std::string res = "[";
    for (size_t i = 0; i < pitches.size(); i++) {
        res += (i ? " " : "") + std::to_string(pitches[i]);
    }
    return res + "]";
}

/// Advance the polyphonic renderer by one block: it completes the legato
/// crossfades started by the MIDI events and frees the released voices.
static void render(mydsp_poly& poly)
{
    constexpr int kBlockSize = 64;
    FAUSTFLOAT output[kBlockSize];
    FAUSTFLOAT* outputs[] = {output};
    poly.compute(kBlockSize, nullptr, outputs);
}

/// Gate of a voice (1 while its note is held).
static double gate_of(dsp_voice* voice) { return voice->getParamValue("/held_tone/gate"); }

/// Gain (normalised velocity) of a voice.
static double gain_of(dsp_voice* voice) { return voice->getParamValue("/held_tone/gain"); }

/// Sorted pitches that are audible: started notes with an open gate and the
/// matching frequency.
static std::vector<int> audible(mydsp_poly& poly)
{
    std::vector<int> pitches;
    for (dsp_voice* voice : poly.fVoiceTable) {
        if (voice->fCurNote >= 0 && gate_of(voice) > 0.5 &&
            std::fabs(voice->getParamValue("/held_tone/freq") - dsp_voice::midiToFreq(voice->fCurNote)) < 1e-3) {
            pitches.push_back(voice->fCurNote);
        }
    }
    std::sort(pitches.begin(), pitches.end());
    return pitches;
}

/// Number of voices that are neither free nor driven by their owner.
static int busy_voices(mydsp_poly& poly)
{
    int count = 0;
    for (dsp_voice* voice : poly.fVoiceTable) {
        count += (voice->fCurNote != kFreeVoice && voice->fCurNote != kManualVoice);
    }
    return count;
}

/// Press a key and render the block.
static void press(mydsp_poly& poly, int pitch, int velocity = 100)
{
    poly.keyOn(0, pitch, velocity);
    render(poly);
}

/// Release a key and render the block.
static void release(mydsp_poly& poly, int pitch)
{
    poly.keyOff(0, pitch);
    render(poly);
}

/// Check the audible pitches after the events of a scenario.
static void expect(mydsp_poly& poly, const char* scenario, const std::string& step, const std::vector<int>& wanted)
{
    const std::vector<int> got = audible(poly);
    check(got == wanted, scenario, step + ": sounding " + show(got) + ", expected " + show(wanted));
}

/// Issue #252 as reported: with a single voice, pressing then releasing a second key
/// must bring back the first one, which is still held.
static void issue_252()
{
    const char* name = "issue 252 (nvoices 1, default options)";
    mydsp_poly poly(new held_tone(), 1, true, false);
    poly.init(48000);
    press(poly, 60);
    expect(poly, name, "A down", {60});
    press(poly, 64);
    expect(poly, name, "A and B down", {64});
    release(poly, 64);
    expect(poly, name, "B released while A is held", {60});
    release(poly, 60);
    expect(poly, name, "A released", {});
}

/// Overflowing the voices of a polyphonic instrument remembers the displaced keys.
static void overflow_remembers_held_keys()
{
    const char* name = "poly overflow";
    mydsp_poly poly(new held_tone(), 2, true, false);
    poly.init(48000);
    press(poly, 60);
    press(poly, 62);
    press(poly, 64);
    expect(poly, name, "three keys on two voices", {62, 64});
    release(poly, 64);
    expect(poly, name, "newest released", {60, 62});
    release(poly, 62);
    expect(poly, name, "second released", {60});
    release(poly, 60);
    expect(poly, name, "all released", {});
    check(busy_voices(poly) == 0, name, "voices left busy after all keys are released");
}

/// Last, lowest and highest note priority in mono, whatever the size of the voice pool.
static void mono_note_priorities()
{
    for (int voices : {1, 3}) {
        const std::string suffix = " (nvoices " + std::to_string(voices) + ")";

        const std::string last = "mono last" + suffix;
        mydsp_poly last_poly(new held_tone("[voicing:mono][note_priority:last]"), voices, true, false);
        last_poly.init(48000);
        press(last_poly, 60);
        press(last_poly, 64);
        press(last_poly, 67);
        expect(last_poly, last.c_str(), "three keys", {67});
        release(last_poly, 67);
        expect(last_poly, last.c_str(), "newest released", {64});
        release(last_poly, 64);
        expect(last_poly, last.c_str(), "second released", {60});

        const std::string low = "mono low" + suffix;
        mydsp_poly low_poly(new held_tone("[voicing:mono][note_priority:low]"), voices, true, false);
        low_poly.init(48000);
        press(low_poly, 64);
        press(low_poly, 60);
        press(low_poly, 62);
        expect(low_poly, low.c_str(), "three keys", {60});
        release(low_poly, 60);
        expect(low_poly, low.c_str(), "lowest released", {62});

        const std::string high = "mono high" + suffix;
        mydsp_poly high_poly(new held_tone("[voicing:mono][note_priority:high]"), voices, true, false);
        high_poly.init(48000);
        press(high_poly, 60);
        press(high_poly, 64);
        press(high_poly, 62);
        expect(high_poly, high.c_str(), "three keys", {64});
        release(high_poly, 64);
        expect(high_poly, high.c_str(), "highest released", {62});
    }
}

/// Duophonic: two notes sound, the others are remembered.
static void duo_last()
{
    const char* name = "duo last";
    mydsp_poly poly(new held_tone("[voicing:duo]"), 3, true, false);
    poly.init(48000);
    press(poly, 60);
    press(poly, 64);
    press(poly, 67);
    expect(poly, name, "three keys", {64, 67});
    release(poly, 67);
    expect(poly, name, "newest released", {60, 64});
}

/// Single trigger keeps the gate open when the note changes, multi trigger re-strikes.
static void trigger_modes()
{
    const char* single = "mono single trigger";
    mydsp_poly legato(new held_tone("[voicing:mono][trigger:single]"), 1, true, false);
    legato.init(48000);
    press(legato, 60);
    legato.keyOn(0, 64, 100);
    check(gate_of(legato.fVoiceTable[0]) > 0.5 && legato.fVoiceTable[0]->fCurNote == 64, single,
          "a new note must change the pitch of the sounding voice and keep its gate open");
    render(legato);
    legato.keyOff(0, 64);
    check(gate_of(legato.fVoiceTable[0]) > 0.5 && legato.fVoiceTable[0]->fCurNote == 60, single,
          "falling back to the held key must keep the gate open");
    render(legato);
    expect(legato, single, "fall back to A", {60});
    release(legato, 60);
    expect(legato, single, "all released", {});

    const char* multi = "mono multi trigger";
    mydsp_poly strike(new held_tone("[voicing:mono][trigger:multi]"), 1, true, false);
    strike.init(48000);
    press(strike, 60);
    strike.keyOn(0, 64, 100);
    check(strike.fVoiceTable[0]->fCurNote == kLegatoVoice, multi,
          "a new note must re-strike the voice through the legato crossfade");
    render(strike);
    expect(strike, multi, "B started", {64});
}

/// A note that has not started yet (legato crossfade pending) when the next key arrives
/// in the same block must still start, for either trigger and priority.  The released
/// voice still has its tail, which is what makes the next key take it over.
static void note_pending_in_the_same_block()
{
    // Mono: A is released and its tail is stolen by B, then C arrives before the render.
    for (const char* options : {"[voicing:mono][note_priority:last][trigger:single]",
                                "[voicing:mono][note_priority:last][trigger:multi]"}) {
        const std::string name = std::string("pending note, ") + options;
        mydsp_poly poly(new held_tone(options, true), 1, true, false);
        poly.init(48000);
        press(poly, 60);
        release(poly, 60);
        poly.keyOn(0, 64, 100);
        poly.keyOn(0, 67, 100);
        render(poly);
        expect(poly, name.c_str(), "B then C in one block", {67});
    }

    // Duo with the lowest notes: B is pending on the released voice when a lower key arrives.
    const char* duo = "pending note, duo low single";
    mydsp_poly poly(new held_tone("[voicing:duo][note_priority:low][trigger:single]", true), 2, true, false);
    poly.init(48000);
    press(poly, 60);
    press(poly, 72);
    release(poly, 60);
    poly.keyOn(0, 80, 100);
    poly.keyOn(0, 48, 100);
    render(poly);
    expect(poly, duo, "80 then 48 in one block", {48, 72});
}

/// A key pressed again while its note sounds keeps one voice, and one key-off ends it.
static void repeated_key_on()
{
    const char* name = "repeated key-on";
    mydsp_poly poly(new held_tone(), 4, true, false);
    poly.init(48000);
    press(poly, 60, 40);
    press(poly, 60, 127);
    expect(poly, name, "same key twice", {60});
    check(busy_voices(poly) == 1, name, "a second voice was allocated for the same key");
    for (dsp_voice* voice : poly.fVoiceTable) {
        if (voice->fCurNote == 60) {
            check(std::fabs(gain_of(voice) - 1.0) < 1e-6, name, "the voice was not re-struck with the new velocity");
        }
    }
    release(poly, 60);
    expect(poly, name, "key released", {});
    check(busy_voices(poly) == 0, name, "a voice is left sounding after the key-off");

    const char* single = "repeated key-on, single trigger";
    mydsp_poly legato(new held_tone("[trigger:single]"), 4, true, false);
    legato.init(48000);
    press(legato, 60, 40);
    press(legato, 60, 127);
    expect(legato, single, "same key twice", {60});
    check(busy_voices(legato) == 1, single, "a second voice was allocated for the same key");
    release(legato, 60);
    check(busy_voices(legato) == 0, single, "a voice is left sounding after the key-off");
}

/// Voices from `newVoice()` belong to their owner, whatever the MIDI keys do, and
/// MIDI pitch 0 is a note like another one.
static void manual_voice_untouched()
{
    const char* name = "newVoice";
    mydsp_poly poly(new held_tone(), 4, true, false);
    poly.init(48000);
    MapUI* manual = poly.newVoice();
    manual->setParamValue("/held_tone/gate", 1);
    press(poly, 72);
    press(poly, 0);
    check(gate_of(poly.fVoiceTable[0]) > 0.5 && poly.fVoiceTable[0]->fCurNote == kManualVoice, name,
          "a MIDI key released the voice given out by newVoice()");
    expect(poly, name, "keys 72 and 0", {0, 72});
    release(poly, 0);
    expect(poly, name, "key 0 released", {72});
    release(poly, 72);
    check(gate_of(poly.fVoiceTable[0]) > 0.5, name, "the voice given out by newVoice() was released by a key-off");
    poly.deleteVoice(manual);
    render(poly);
    check(busy_voices(poly) == 0 && poly.fVoiceTable[0]->fCurNote == kFreeVoice, name,
          "deleteVoice() did not give the voice back");
}

/// All Notes Off also clears the held keys: a later key-off must not bring one back.
static void all_notes_off_forgets_held_keys()
{
    const char* name = "all notes off";
    mydsp_poly poly(new held_tone("[voicing:mono]"), 1, true, false);
    poly.init(48000);
    press(poly, 60);
    press(poly, 64);
    poly.ctrlChange(0, midi::ALL_NOTES_OFF, 0);
    render(poly);
    expect(poly, name, "after all notes off", {});
    release(poly, 64);
    expect(poly, name, "key-off of a forgotten key", {});
}

/// Reading the options, the precedence of an explicit policy, and clones.
static void policy_options()
{
    const char* name = "options";
    PolyPolicy policy;
    held_tone spelled("[nvoices:4][voicing:duo][note_priority:lowest][trigger:legato]");
    MidiMeta::analysePolicy(&spelled, policy);
    check(policy.voicing == Voicing::Duo && policy.priority == NotePriority::Low && policy.trigger == TriggerMode::Single,
          name, "aliases and values were not read");

    PolyPolicy kept;
    held_tone nothing("[nvoices:4][midi:on]");
    MidiMeta::analysePolicy(&nothing, kept);
    check(kept.voicing == Voicing::Poly && kept.priority == NotePriority::Last && kept.trigger == TriggerMode::Multi,
          name, "options that are not declared must leave the defaults");

    // The unknown value is reported on stderr: that message is expected here.
    PolyPolicy typo;
    held_tone misspelled("[voicing:monophonic][note_priority:highest]");
    MidiMeta::analysePolicy(&misspelled, typo);
    check(typo.voicing == Voicing::Poly && typo.priority == NotePriority::High, name,
          "an unknown value must be ignored without affecting the other options");

    // An explicit policy wins over the metadata.
    PolyPolicy poly_policy;
    mydsp_poly explicit_poly(new held_tone("[voicing:mono]"), 4, true, false, &poly_policy);
    explicit_poly.init(48000);
    press(explicit_poly, 60);
    press(explicit_poly, 64);
    expect(explicit_poly, name, "explicit poly policy over mono metadata", {60, 64});

    // A clone keeps the policy.
    mydsp_poly mono(new held_tone("[voicing:mono]"), 2, true, false);
    mono.init(48000);
    mydsp_poly* copy = mono.clone();
    copy->init(48000);
    copy->keyOn(0, 60, 100);
    copy->keyOn(0, 64, 100);
    render(*copy);
    expect(*copy, name, "clone of a mono instrument", {64});
    delete copy;
}

/// The MIDI entry points run in the audio thread: they must not allocate.
static void midi_does_not_allocate()
{
    const char* name = "allocation";
    for (const char* options : {"", "[voicing:mono][trigger:single]", "[voicing:duo][note_priority:low]"}) {
        mydsp_poly poly(new held_tone(options), 8, true, false);
        poly.init(48000);
        gAllocations = 0;
        gCountAllocations = true;
        for (int pitch = 40; pitch < 56; pitch++) {
            poly.keyOn(0, pitch, 100);
            render(poly);
        }
        for (int pitch = 40; pitch < 56; pitch++) {
            poly.keyOff(0, pitch);
            render(poly);
        }
        gCountAllocations = false;
        check(gAllocations == 0, name,
              std::string("options '") + options + "': " + std::to_string(gAllocations) + " allocations in 32 key events");
    }
}

int main()
{
    issue_252();
    overflow_remembers_held_keys();
    mono_note_priorities();
    duo_last();
    trigger_modes();
    note_pending_in_the_same_block();
    repeated_key_on();
    manual_voice_untouched();
    all_notes_off_forgets_held_keys();
    policy_options();
    midi_does_not_allocate();

    std::printf("%d checks, %d failed\n", gChecks, gFailures);
    return gFailures ? EXIT_FAILURE : EXIT_SUCCESS;
}
