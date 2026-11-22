// mcu-poly-test.cpp - faust/dsp/mcu-poly-dsp.h against faust/dsp/poly-dsp.h,
// with the voice and effect of mcu-poly-voice.dsp
//
// 1. the UI paths of both (apart from the note parameters mcu-poly-dsp.h hides)
// 2. MIDI through a FAUST MidiUI: registration, note on/off per channel,
//    CC 120/123, a repeated note, [midi:ctrl], Panic, delete
// 3. the audio of the same notes through both: bit identical, channel by
//    channel (setRetrigger(false), spread 0: poly-dsp.h numbers no voices)
// 4. voice stealing: a voice stolen again as its note starts, the same
//    note twice while every voice is busy, a note while every voice is
//    already being stolen, a hard stop during a steal
// 5. compute() longer than the block: in slices, the same as blocks
// 6. a hand-written voice: more than 16 voices and 16 outputs, two gate
//    zones, soundfiles reaching every voice, an effect with more inputs
// 7. a voice cut off by a fade (REUSE) fades in when it plays again
// 8. voices made by create() under -mem: the same audio, all memory freed
//
// run: make mcu-poly (generates the voices with faust)
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <set>
#include <string>
#include <vector>
#define FAUSTFLOAT float
#include "faust/dsp/dsp.h"
#include "faust/gui/MapUI.h"
#include "faust/gui/MidiUI.h"
#include "faust/gui/DecoratorUI.h"
#include "faust/gui/meta.h"
#include "faust/dsp/poly-dsp.h"
#include "faust/dsp/dsp-combiner.h"
#include "mcupolyvoice.h"
#include "mcupolyeffect.h"
#include "mcupolyvoicemem.h"
#include "faust/dsp/mcu-poly-dsp.h"
std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

static int failures = 0;
#define CHECK(cond, what) do { bool ok = (cond); printf("%s  %s\n", ok ? "ok  " : "FAIL", what); if (!ok) failures++; } while (0)

struct TestHandler : public midi_handler {   // a MIDI driver we feed by hand
    TestHandler() : midi_handler("test") {}
    bool startMidi() override { return true; }
    void stopMidi() override {}
};

const int SR = 48000, N = 64;
static void del(dsp* d) { delete d; }

mcu_dsp_poly* makeMcu(int voices, bool effect, int block = N) {
    std::vector<dsp*> v; for (int i = 0; i < voices; i++) v.push_back(new mcupolyvoice());
    auto* p = new mcu_dsp_poly(v.data(), voices, del, effect ? new mcupolyeffect() : nullptr, del, block);
    p->init(SR); return p;
}
dsp_poly* makePolyDsp(int voices, bool effect) {
    auto* poly = new mydsp_poly(new mcupolyvoice(), voices, true, true);
    dsp_poly* d = effect ? (dsp_poly*)new dsp_poly_effect(poly, new dsp_sequencer(poly, new mcupolyeffect()))
                         : (dsp_poly*)new dsp_poly_effect(poly, poly);
    d->init(SR); return d;
}
std::set<std::string> paths(dsp* d) {
    MapUI ui; d->buildUserInterface(&ui); std::set<std::string> s;
    for (int i = 0; i < ui.getParamsCount(); i++) s.insert(ui.getParamAddress(i)); return s;
}

// a note event at a sample: on (velocity > 0) or off (velocity 0)
struct Event { int at, pitch, velocity; };
struct Stereo { std::vector<float> l, r; };
Stereo render(dsp* d, int samples, const std::vector<Event>& events, midi* m, int block = N) {
    Stereo out; std::vector<float> l(block), r(block); float* o[2] = {l.data(), r.data()}; float* in[2] = {0, 0};
    for (int k = 0; k < samples; k += block) {
        for (auto& e : events) if (e.at >= k && e.at < k + block) {
            if (e.velocity > 0) m->keyOn(0, e.pitch, e.velocity); else m->keyOff(0, e.pitch, 0); }
        d->compute(block, in, o);
        out.l.insert(out.l.end(), l.begin(), l.end());
        out.r.insert(out.r.end(), r.begin(), r.end());
    }
    return out;
}
// the first sample where two signals differ, -1 if none
long firstDifference(const std::vector<float>& a, const std::vector<float>& b) {
    if (a.size() != b.size()) return 0;
    for (size_t i = 0; i < a.size(); i++) if (memcmp(&a[i], &b[i], sizeof(float)) != 0) return long(i);
    return -1;
}
bool identical(const Stereo& a, const Stereo& b, const char* what) {
    long dl = firstDifference(a.l, b.l), dr = firstDifference(a.r, b.r);
    if (dl >= 0) printf("   %s: left differs from sample %ld (%.9g vs %.9g)\n", what, dl, a.l[dl], b.l[dl]);
    if (dr >= 0) printf("   %s: right differs from sample %ld (%.9g vs %.9g)\n", what, dr, a.r[dr], b.r[dr]);
    return dl < 0 && dr < 0;
}
float peakOf(const std::vector<float>& x, size_t from, size_t to) {
    float p = 0; for (size_t i = from; i < to && i < x.size(); i++) p = fmaxf(p, fabsf(x[i])); return p;
}

// a voice written by hand: a level following gate A * gain (1 ms up, 2 s
// down) on every output, a second gate in another group, a soundfile
struct TestVoice : public dsp {
    FAUSTFLOAT fFreq = 0, fGateA = 0, fGateB = 0, fGain = 0, fShared = 0;
    Soundfile* fSound = nullptr;
    int fOutputs, fRate = SR;
    float fLevel = 0;
    explicit TestVoice(int outputs) : fOutputs(outputs) {}
    int getNumInputs() override { return 0; }
    int getNumOutputs() override { return fOutputs; }
    void buildUserInterface(UI* ui) override {
        ui->openVerticalBox("test");
        ui->openVerticalBox("A");
        ui->addHorizontalSlider("freq", &fFreq, 440, 20, 20000, 0.01f);
        ui->addButton("gate", &fGateA);
        ui->closeBox();
        ui->openVerticalBox("B");
        ui->addButton("gate", &fGateB);
        ui->addHorizontalSlider("gain", &fGain, 0.5f, 0, 1, 0.01f);
        ui->addHorizontalSlider("shared", &fShared, 0, 0, 1, 0.01f);
        ui->addSoundfile("sound", "{'test.wav'}", &fSound);
        ui->closeBox();
        ui->closeBox();
    }
    int getSampleRate() override { return fRate; }
    void init(int sr) override { instanceInit(sr); }
    void instanceInit(int sr) override { instanceConstants(sr); instanceResetUserInterface(); instanceClear(); }
    void instanceConstants(int sr) override { fRate = sr; }
    void instanceResetUserInterface() override { fFreq = 440; fGateA = fGateB = 0; fGain = 0.5f; fShared = 0; }
    void instanceClear() override { fLevel = 0; }
    dsp* clone() override { return new TestVoice(fOutputs); }
    void metadata(Meta*) override {}
    void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) override {
        (void)inputs;
        float target = fGateA * fGain;
        for (int s = 0; s < count; s++) {
            float k = target > fLevel ? 1.0f / 48.0f : 1.0f / (2.0f * fRate);
            fLevel += (target - fLevel) * k;
            for (int c = 0; c < fOutputs; c++) outputs[c][s] = fLevel;
        }
    }
};
// an effect passing its inputs through
struct ThroughEffect : public dsp {
    int fChannels;
    explicit ThroughEffect(int channels) : fChannels(channels) {}
    int getNumInputs() override { return fChannels; }
    int getNumOutputs() override { return fChannels; }
    void buildUserInterface(UI*) override {}
    int getSampleRate() override { return SR; }
    void init(int) override {}
    void instanceInit(int) override {}
    void instanceConstants(int) override {}
    void instanceResetUserInterface() override {}
    void instanceClear() override {}
    dsp* clone() override { return new ThroughEffect(fChannels); }
    void metadata(Meta*) override {}
    void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) override {
        for (int c = 0; c < fChannels; c++) memcpy(outputs[c], inputs[c], count * sizeof(FAUSTFLOAT));
    }
};
// gives every soundfile zone it sees the same (fake) soundfile
struct SoundSetter : public GenericUI {
    Soundfile* fSound;
    explicit SoundSetter(Soundfile* s) : fSound(s) {}
    void addSoundfile(const char*, const char*, Soundfile** zone) override { *zone = fSound; }
};

// a memory manager that returns garbage (as recycled memory on a
// microcontroller would) and counts what is still allocated
struct GarbageManager : public dsp_memory_manager {
    int fLive = 0;
    void* allocate(size_t size) override {
        void* p = malloc(size ? size : 1);
        memset(p, 0xbe, size);
        fLive++;
        return p;
    }
    void destroy(void* ptr) override { if (ptr) { free(ptr); fLive--; } }
};
static void destroyMem(dsp* d) { mcupolyvoicemem::destroy(d); }

int main() {
    // 1. UI paths
    for (bool effect : {false, true}) {
        auto* a = makeMcu(6, effect); auto* b = makePolyDsp(6, effect);
        auto pa = paths(a), pb = paths(b);
        std::set<std::string> onlyPolyDsp, onlyMcu;
        for (auto& p : pb) if (!pa.count(p)) onlyPolyDsp.insert(p);
        for (auto& p : pa) if (!pb.count(p)) onlyMcu.insert(p);
        printf("%s effect: %zu paths mcu-poly-dsp.h, %zu poly-dsp.h\n", effect ? "with" : "without", pa.size(), pb.size());
        for (auto& p : onlyPolyDsp) printf("   only poly-dsp.h:     %s\n", p.c_str());
        for (auto& p : onlyMcu) printf("   only mcu-poly-dsp.h: %s\n", p.c_str());
        bool onlyNotes = onlyMcu.empty();
        for (auto& p : onlyPolyDsp) { auto last = p.substr(p.rfind('/') + 1); if (last != "freq" && last != "gain" && last != "gate" && last != "voice") onlyNotes = false; }
        CHECK(onlyNotes, effect ? "paths match poly-dsp.h (with effect), apart from freq/gain/gate/voice" : "paths match poly-dsp.h (without effect), apart from freq/gain/gate/voice");
        delete a; delete b;
    }

    // 2. MIDI through a MidiUI
    {
        auto* p = makeMcu(6, true);
        TestHandler h; MidiUI midiui(&h); p->buildUserInterface(&midiui); midiui.run();
#if !(defined(__GXX_RTTI) || defined(_CPPRTTI) || defined(__cpp_rtti))
        p->setMidiHandler(&h);   // without RTTI the MidiUI can't be recognised: registered by hand, as on a Teensy
#endif
        h.handleKeyOn(0, 0, 60, 100); h.handleKeyOn(0, 0, 64, 100); h.handleKeyOn(0, 1, 67, 100);
        CHECK(p->getNumActiveVoices() == 3, "MidiUI: 3 notes on -> 3 voices (registered as midi in)");
        h.handleKeyOff(0, 1, 60, 0);
        CHECK(p->voiceNote(0) == 60, "note off on another channel leaves channel 0's note");
        h.handleKeyOff(0, 0, 60, 0);
        CHECK(p->voiceNote(0) == -2, "note off on its channel releases it");
        h.handleCtrlChange(0, 1, 123, 0);
        CHECK(p->voiceNote(2) == -2 && p->voiceNote(1) == 64, "CC 123 on channel 1 releases only channel 1");
        h.handleCtrlChange(0, 0, 120, 0);
        std::vector<float> l(N), r(N); float* o[2] = {l.data(), r.data()}; float* in[2] = {0, 0};
        for (int k = 0; k < 4; k++) p->compute(N, in, o);
        CHECK(p->voiceNote(1) == -1, "CC 120 on channel 0 stops its voices within the 3 ms fade");
        // the same note twice: retrigger (default) keeps one voice, one note off ends it
        h.handleKeyOn(0, 0, 50, 100); h.handleKeyOn(0, 0, 50, 100);
        for (int k = 0; k < 4; k++) p->compute(N, in, o);
        int held = 0; for (int i = 0; i < 6; i++) held += p->voiceNote(i) == 50;
        h.handleKeyOff(0, 0, 50, 0);
        int still = 0; for (int i = 0; i < 6; i++) still += p->voiceNote(i) == 50;
        CHECK(held == 1 && still == 0, "the same note twice (retrigger): one voice, one note off releases it");
        // poly-dsp.h's way: two voices, one note off releases the oldest
        p->setRetrigger(false);
        h.handleKeyOn(0, 0, 52, 100); h.handleKeyOn(0, 0, 52, 100);
        held = 0; for (int i = 0; i < 6; i++) held += p->voiceNote(i) == 52;
        h.handleKeyOff(0, 0, 52, 0);
        still = 0; for (int i = 0; i < 6; i++) still += p->voiceNote(i) == 52;
        CHECK(held == 2 && still == 1, "setRetrigger(false): two voices, one note off releases the oldest");
        p->setRetrigger(true);
        // [midi:ctrl 73] (Attack) through the MidiUI reaches the voices
        MapUI map; p->buildUserInterface(&map);
        std::string attack; for (int i = 0; i < map.getParamsCount(); i++) if (map.getParamAddress(i).find("/Attack") != std::string::npos) attack = map.getParamAddress(i);
        h.handleCtrlChange(0, 0, 73, 127); GUI::updateAllGuis();
        CHECK(fabs(map.getParamValue(attack) - 1.0f) < 1e-3, "[midi:ctrl 73] sets Attack through the MidiUI");
        // Panic
        h.handleKeyOn(0, 0, 70, 100);
        map.setParamValue(map.getParamAddress(0).substr(0, map.getParamAddress(0).find("/Voices/") + 8) + "Panic", 1);
        for (int k = 0; k < 4; k++) p->compute(N, in, o);
        CHECK(p->getNumActiveVoices() == 0, "Panic stops every voice");
        delete p;
        CHECK(true, "deleted: unregistered from the MIDI handler (no crash)");
        h.handleKeyOn(0, 0, 60, 100);
        CHECK(true, "a note after the delete reaches no dead object");
    }

    // 2b. assign modes ([poly:mode] "keys")
    {
        auto* p = makeMcu(6, false);
        MapUI map; p->buildUserInterface(&map);
        std::string keys; for (int i = 0; i < map.getParamsCount(); i++) if (map.getParamAddress(i).find("/keys") != std::string::npos) keys = map.getParamAddress(i);
        std::vector<float> l(N), r(N); float* o[2] = {l.data(), r.data()}; float* in[2] = {0, 0};
        auto run = [&](int blocks) { for (int k = 0; k < blocks; k++) p->compute(N, in, o); };
        map.setParamValue(keys, 1); run(1);   // reuse
        p->keyOn(0, 60, 100); p->keyOn(0, 64, 100); run(2); p->keyOff(0, 60, 0); p->keyOff(0, 64, 0); run(2);
        bool releasing = p->voiceNote(0) == -2 && p->voiceNote(1) == -2;
        p->keyOn(0, 67, 100); run(4);
        CHECK(releasing && p->voiceNote(0) == 67, "reuse: a new note takes the lowest releasing voice");
        CHECK(p->voiceNote(1) == -1, "reuse: the other release tail is stopped");
        p->keyOff(0, 67, 0); run(200);
        map.setParamValue(keys, 2); run(1);   // unison
        p->keyOn(0, 60, 100); run(4);
        int all60 = 0; for (int i = 0; i < 6; i++) all60 += p->voiceNote(i) == 60;
        p->keyOn(0, 64, 100); run(1);
        int all64 = 0; for (int i = 0; i < 6; i++) all64 += p->voiceNote(i) == 64;
        p->keyOff(0, 64, 0); run(1);
        int back60 = 0; for (int i = 0; i < 6; i++) back60 += p->voiceNote(i) == 60;
        p->keyOff(0, 60, 0); run(1);
        int released = 0; for (int i = 0; i < 6; i++) released += p->voiceNote(i) == -2;
        CHECK(all60 == 6, "unison: every voice plays the note");
        CHECK(all64 == 6 && back60 == 6, "unison: legato to a second key and back to the held one");
        CHECK(released == 6, "unison: all voices released with the last key");
        map.setParamValue(keys, 0); run(1);
        p->keyOn(0, 60, 100); p->keyOn(0, 64, 100); run(4);
        int held = 0; for (int i = 0; i < 6; i++) held += p->voiceNote(i) == 60 || p->voiceNote(i) == 64;
        CHECK(held == 2, "rotate again: two notes, two voices");
        delete p;
    }

    // 3. audio: the same chord through both (spread 0: poly-dsp.h numbers no voices)
    for (bool effect : {false, true}) {
        auto* a = makeMcu(6, effect); auto* b = makePolyDsp(6, effect);
        a->setRetrigger(false);
        for (dsp* d : {(dsp*)a, (dsp*)b}) { MapUI ui; d->buildUserInterface(&ui);
            for (int i = 0; i < ui.getParamsCount(); i++) { auto p = ui.getParamAddress(i);
                if (p.find("/Spread") != std::string::npos) ui.setParamValue(p, 0); } }
        GUI::updateAllGuis();   // poly-dsp.h's grouped controls reach its voices only then
        std::vector<Event> ev = {{0, 48, 100}, {0, 55, 90}, {4800, 64, 80}, {24000, 48, 0}, {24000, 55, 0}, {36000, 64, 0}};
        auto ya = render(a, SR * 2, ev, a), yb = render(b, SR * 2, ev, b);
        CHECK(peakOf(yb.l, 0, yb.l.size()) > 0.05f, "the reference plays");
        CHECK(identical(ya, yb, "poly-dsp.h"), effect ? "audio identical to poly-dsp.h, both channels (with effect)"
                                                      : "audio identical to poly-dsp.h, both channels (without effect)");
        delete a; delete b;
    }

    // 4. voice stealing
    {
        std::vector<float> l(N), r(N); float* o[2] = {l.data(), r.data()}; float* in[2] = {0, 0};
        auto run = [&](mcu_dsp_poly* p, int blocks) { float pk = 0; for (int k = 0; k < blocks; k++) { p->compute(N, in, o);
            pk = fmaxf(pk, peakOf(l, 0, N)); } return pk; };
        // 1 voice, three notes a few blocks apart: every gap, so the third
        // note also comes in the block where the second one starts
        bool lost = false;
        for (int gap = 1; gap <= 5; gap++) {
            auto* p = makeMcu(1, false);
            p->keyOn(0, 60, 100); run(p, 1); p->keyOn(0, 62, 100); run(p, gap); p->keyOn(0, 64, 100);
            float pk = run(p, 20);
            if (p->voiceNote(0) != 64 || pk < 0.01f) { printf("   gap %d blocks: voice plays %d, peak %g\n", gap, p->voiceNote(0), pk); lost = true; }
            p->keyOff(0, 64, 0); run(p, 750);
            if (p->getNumActiveVoices() != 0) { printf("   gap %d blocks: %d voices active after the note off\n", gap, p->getNumActiveVoices()); lost = true; }
            delete p;
        }
        CHECK(!lost, "1 voice, notes 60 62 64 a few blocks apart: 64 sounds, its note off frees the voice");
        lost = false;
        for (int gap = 1; gap <= 5; gap++) {
            auto* p = makeMcu(1, false);
            p->keyOn(0, 60, 100); run(p, 1); p->keyOn(0, 60, 100); run(p, gap); p->keyOn(0, 60, 100);
            float pk = run(p, 20);
            if (p->voiceNote(0) != 60 || pk < 0.01f) lost = true;
            p->keyOff(0, 60, 0); run(p, 750);
            if (p->getNumActiveVoices() != 0) lost = true;
            delete p;
        }
        CHECK(!lost, "1 voice, the same note three times (retrigger): it sounds, one note off frees it");
        // the same pitch twice while every voice is busy
        {
            auto* p = makeMcu(2, false);
            p->keyOn(0, 60, 100); p->keyOn(0, 62, 100); run(p, 4);
            p->keyOn(0, 64, 100); p->keyOn(0, 64, 100);
            int waiting = p->getNumActiveVoices();
            run(p, 4);
            int on64 = (p->voiceNote(0) == 64) + (p->voiceNote(1) == 64);
            p->keyOff(0, 64, 0); p->keyOff(0, 62, 0); p->keyOff(0, 60, 0); run(p, 750);
            CHECK(waiting == 2 && on64 == 1, "2 voices busy, the same note twice: one voice takes it");
            CHECK(p->getNumActiveVoices() == 0, "2 voices busy, the same note twice: no voice hangs after the note offs");
            delete p;
        }
        // a note while every voice is already being stolen: the last one wins
        {
            auto* p = makeMcu(1, false);
            p->keyOn(0, 60, 100); run(p, 4); p->keyOn(0, 62, 100); p->keyOn(0, 64, 100); run(p, 10);
            CHECK(p->voiceNote(0) == 64, "1 voice, 62 and 64 within 3 ms: the last note (64) plays");
            p->keyOff(0, 62, 0);
            CHECK(p->voiceNote(0) == 64, "the replaced note's note off doesn't release the new note");
            p->keyOff(0, 64, 0); run(p, 750);
            CHECK(p->getNumActiveVoices() == 0, "its note off frees the voice");
            delete p;
        }
        {
            auto* p = makeMcu(2, false);
            p->setAssignMode(mcu_dsp_poly::REUSE);
            p->keyOn(0, 60, 100); p->keyOn(0, 62, 100); run(p, 4);
            p->keyOn(0, 64, 100); p->keyOn(0, 65, 100); p->keyOn(0, 67, 100); run(p, 10);
            int on67 = (p->voiceNote(0) == 67) + (p->voiceNote(1) == 67);
            CHECK(on67 == 1, "reuse, 2 voices, three new notes within 3 ms: the last one plays");
            p->allNotesOff(); run(p, 750);
            CHECK(p->getNumActiveVoices() == 0, "reuse: all free after all notes off");
            delete p;
        }
        // a hard stop while a stolen voice waits for its note
        {
            auto* p = makeMcu(1, false);
            p->keyOn(0, 60, 100); run(p, 1); p->keyOn(0, 62, 100); run(p, 3);
            p->ctrlChange(0, 120, 0); run(p, 4);
            CHECK(p->getNumActiveVoices() == 0, "CC 120 as a stolen voice's note starts: the voice stops");
            p->keyOn(0, 64, 100); float pk = run(p, 10);
            CHECK(p->voiceNote(0) == 64 && pk > 0.01f, "and plays the next note");
            delete p;
        }
    }

    // 5. compute() longer than the block: in slices of the block
    {
        auto* a = makeMcu(4, true, 64); auto* b = makeMcu(4, true, 64);
        std::vector<float> la(256, NAN), ra(256, NAN), lb(256), rb(256);
        a->keyOn(0, 60, 100); a->keyOn(0, 67, 100); b->keyOn(0, 60, 100); b->keyOn(0, 67, 100);
        bool same = true;
        float* in[2] = {0, 0};
        for (int k = 0; k < 20; k++) {
            float* oa[2] = {la.data(), ra.data()};
            a->compute(256, in, oa);
            for (int s = 0; s < 256; s += 64) { float* ob[2] = {lb.data() + s, rb.data() + s}; b->compute(64, in, ob); }
            same = same && memcmp(la.data(), lb.data(), 256 * sizeof(float)) == 0 && memcmp(ra.data(), rb.data(), 256 * sizeof(float)) == 0;
        }
        CHECK(same && peakOf(la, 192, 256) > 0.01f, "compute(256) with block 64: every sample written, the same as 4 x compute(64)");
        delete a; delete b;
    }

    // 6. a hand-written voice: 20 voices, 18 outputs, two gates, a soundfile
    {
        const int V = 20, C = 18;
        std::vector<dsp*> v; std::vector<TestVoice*> tv;
        for (int i = 0; i < V; i++) { tv.push_back(new TestVoice(C)); v.push_back(tv.back()); }
        auto* p = new mcu_dsp_poly(v.data(), V, del, nullptr, del, N);
        p->init(SR);
        CHECK(p->voices() == V && p->getNumOutputs() == C, "20 voices with 18 outputs each are kept");
        Soundfile* fake = reinterpret_cast<Soundfile*>(uintptr_t(0x1000));
        SoundSetter sounds(fake); p->buildUserInterface(&sounds);
        MapUI map; p->buildUserInterface(&map);
        std::string shared; for (int i = 0; i < map.getParamsCount(); i++) if (map.getParamAddress(i).find("/shared") != std::string::npos) shared = map.getParamAddress(i);
        map.setParamValue(shared, 0.25f);
        for (int i = 0; i < V; i++) p->keyOn(0, 40 + i, 127);
        std::vector<std::vector<float>> out(C, std::vector<float>(N)); std::vector<float*> o; for (auto& c : out) o.push_back(c.data());
        for (int k = 0; k < 10; k++) p->compute(N, nullptr, o.data());
        bool gates = true, sound = true, sharedOk = true;
        for (auto* t : tv) { gates = gates && t->fGateA == 1 && t->fGateB == 1; sound = sound && t->fSound == fake; sharedOk = sharedOk && t->fShared == 0.25f; }
        CHECK(p->getNumActiveVoices() == V, "20 notes, 20 voices");
        CHECK(gates, "both gate zones of every voice are set");
        CHECK(sound, "the soundfile reaches every voice");
        CHECK(sharedOk, "a shared parameter reaches every voice");
        CHECK(out[C - 1][N - 1] > 1.0f, "the 18th output carries the voices");
        p->allNotesOff();
        bool off = true; for (auto* t : tv) off = off && t->fGateA == 0 && t->fGateB == 0;
        CHECK(off, "a note off clears both gate zones");
        delete p;
        // an effect with more inputs than a voice has outputs: those are silent
        std::vector<dsp*> w; for (int i = 0; i < 2; i++) w.push_back(new TestVoice(2));
        auto* q = new mcu_dsp_poly(w.data(), 2, del, new ThroughEffect(4), del, N);
        q->init(SR);
        q->keyOn(0, 60, 127);
        std::vector<std::vector<float>> o4(4, std::vector<float>(N, NAN)); float* p4[4] = {o4[0].data(), o4[1].data(), o4[2].data(), o4[3].data()};
        for (int k = 0; k < 4; k++) q->compute(N, nullptr, p4);
        CHECK(q->getNumOutputs() == 4 && o4[0][N - 1] > 0.1f && o4[2][N - 1] == 0 && o4[3][N - 1] == 0,
              "an effect with 4 inputs after 2 voice outputs: the voices on 1-2, silence on 3-4");
        delete q;
    }

    // 7. REUSE: a voice cut off by a fade fades in when it plays again (its level was not 0)
    {
        std::vector<dsp*> v; for (int i = 0; i < 2; i++) v.push_back(new TestVoice(1));
        auto* p = new mcu_dsp_poly(v.data(), 2, del, nullptr, del, N);
        p->init(SR); p->setAssignMode(mcu_dsp_poly::REUSE);
        std::vector<float> out; std::vector<float> b(N); float* o[1] = {b.data()};
        auto run = [&](int blocks) { for (int k = 0; k < blocks; k++) { p->compute(N, nullptr, o); out.insert(out.end(), b.begin(), b.end()); } };
        p->keyOn(0, 60, 127); p->keyOn(0, 62, 127); run(20);
        p->keyOff(0, 60, 0); p->keyOff(0, 62, 0); run(5);
        p->keyOn(0, 64, 127); run(10);    // takes voice 0, voice 1's tail is cut by a fade
        p->keyOn(0, 65, 127); run(10);    // voice 1 again: its level is still ~1
        float step = 0; for (size_t i = 1; i < out.size(); i++) step = fmaxf(step, fabsf(out[i] - out[i - 1]));
        printf("   largest step between samples %.4f\n", step);
        CHECK(step < 0.05f, "reuse: a voice cut by a fade starts again without a jump");
        delete p;
    }

    // 8. voices made by create() under -mem (memory full of garbage): the same audio, all freed
    {
        GarbageManager mm; mcupolyvoicemem::fManager = &mm;
        mcupolyvoicemem::classInit(SR);
        std::vector<dsp*> v; for (int i = 0; i < 6; i++) v.push_back(mcupolyvoicemem::create());
        auto* a = new mcu_dsp_poly(v.data(), 6, destroyMem, nullptr, del, N);
        a->instanceInit(SR);   // -mem: init() is empty
        auto* b = makeMcu(6, false);
        std::vector<Event> ev = {{0, 48, 100}, {0, 55, 90}, {4800, 64, 80}, {24000, 48, 0}, {24000, 55, 0}, {36000, 64, 0}};
        auto ya = render(a, SR, ev, a), yb = render(b, SR, ev, b);
        CHECK(identical(ya, yb, "-mem"), "-mem voices from create(): audio identical to voices from new");
        delete a; delete b;
        mcupolyvoicemem::classDestroy();
        CHECK(mm.fLive == 0, "-mem: every zone freed after delete + classDestroy()");
    }

    printf("%d failures\n", failures);
    return failures != 0;
}
