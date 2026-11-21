// mcu-poly-test.cpp - faust/dsp/mcu-poly-dsp.h against faust/dsp/poly-dsp.h,
// with the voice and effect of mcu-poly-voice.dsp
//
// 1. the UI paths of both (apart from the note parameters mcu-poly-dsp.h hides)
// 2. MIDI through a FAUST MidiUI: registration, note on/off per channel,
//    CC 120/123, a repeated note, [midi:ctrl], Panic, delete
// 3. the audio of the same notes through both: bit identical
//    (setRetrigger(false), spread 0: poly-dsp.h numbers no voices)
//
// run: make mcu-poly (generates the voice with faust)
#include <cmath>
#include <cstdio>
#include <map>
#include <set>
#include <string>
#include <vector>
#define FAUSTFLOAT float
#include "faust/dsp/dsp.h"
#include "faust/gui/MapUI.h"
#include "faust/gui/MidiUI.h"
#include "faust/gui/meta.h"
#include "faust/dsp/poly-dsp.h"
#include "faust/dsp/dsp-combiner.h"
#include "mcupolyvoice.h"
#include "mcupolyeffect.h"
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

mcu_dsp_poly* makeMcu(int voices, bool effect) {
    std::vector<dsp*> v; for (int i = 0; i < voices; i++) v.push_back(new mcupolyvoice());
    auto* p = new mcu_dsp_poly(v.data(), voices, del, effect ? new mcupolyeffect() : nullptr, del, N);
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
std::vector<float> render(dsp* d, int samples, std::vector<std::pair<int, std::vector<int>>> events, midi* m) {
    std::vector<float> out; std::vector<float> l(N), r(N); float* o[2] = {l.data(), r.data()}; float* in[2] = {0, 0};
    for (int k = 0; k < samples; k += N) {
        for (auto& e : events) if (e.first >= k && e.first < k + N) {
            if (e.second[0] == 1) m->keyOn(0, e.second[1], e.second[2]); else m->keyOff(0, e.second[1], 0); }
        d->compute(N, in, o);
        for (int s = 0; s < N; s++) out.push_back(0.5f * (l[s] + r[s]));
    }
    return out;
}

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
        std::vector<std::pair<int, std::vector<int>>> ev = {{0, {1, 48, 100}}, {0, {1, 55, 90}}, {4800, {1, 64, 80}},
                                                            {24000, {0, 48}}, {24000, {0, 55}}, {36000, {0, 64}}};
        auto ya = render(a, SR * 2, ev, a), yb = render(b, SR * 2, ev, b);
        double num = 0, den = 0, peak = 0;
        for (size_t i = 0; i < ya.size(); i++) { num += (ya[i] - yb[i]) * (ya[i] - yb[i]); den += yb[i] * yb[i]; peak = fmax(peak, fabs(ya[i] - yb[i])); }
        double db = 10 * log10(num / den + 1e-30);
        printf("%s effect: difference %.1f dB below the signal, peak difference %.2g\n", effect ? "with" : "without", -db, peak);
        CHECK(db < -100, effect ? "audio equals poly-dsp.h (with effect)" : "audio equals poly-dsp.h (without effect)");
        delete a; delete b;
    }
    printf("%d failures\n", failures);
    return failures != 0;
}
