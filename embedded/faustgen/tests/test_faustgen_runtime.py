"""Tests for faustgen message routing and audio-callback behaviour."""

import tempfile
import unittest

from cpp_test_support import FAUSTGEN_SOURCE, compile_and_run, definitions


STUBS = r'''
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdarg>
#include <cstring>
#include <iostream>
#include <map>
#include <mutex>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#define FAUSTFLOAT double
#define A_LONG 1
#define A_FLOAT 2
#define A_SYM 3
using t_sample = double;

struct t_symbol { string storage; const char* s_name; };
map<string, t_symbol> symbols;
t_symbol* gensym(const char* text) {
    auto result = symbols.emplace(text, t_symbol{text, nullptr}).first;
    result->second.s_name = result->second.storage.c_str();
    return &result->second;
}
struct t_atom {
    int a_type = 0;
    union { long w_long; double w_float; t_symbol* w_sym; } a_w{};
};
int atom_gettype(t_atom* atom) { return atom->a_type; }
t_symbol* atom_getsym(t_atom* atom) { return atom->a_w.w_sym; }

vector<string> posts;
void post(const char* format, ...) {
    char text[512];
    va_list arguments;
    va_start(arguments, format);
    vsnprintf(text, sizeof(text), format, arguments);
    va_end(arguments);
    posts.push_back(text);
}

vector<string> destruction_order;
struct UIBase {
    string label;
    explicit UIBase(string value) : label(std::move(value)) {}
    virtual ~UIBase() { destruction_order.push_back(label); }
};

struct mspUI : UIBase {
    map<string, double> values;
    vector<pair<string, double>> writes;
    mspUI() : UIBase("dsp-ui") {}
    bool isValue(const string& name) const { return values.count(name); }
    bool setValue(const string& name, double value) {
        auto item = values.find(name);
        if (item == values.end()) return false;
        item->second = value;
        writes.push_back({name, value});
        return true;
    }
    static bool checkDigit(const string& name) {
        return !name.empty() && isdigit(static_cast<unsigned char>(name.back()));
    }
    static int countDigit(const string& value) {
        return count_if(value.begin(), value.end(), [](unsigned char c) { return isdigit(c); });
    }
};

struct MidiUI : UIBase { MidiUI() : UIBase("midi-ui") {} };
struct SaveUI : UIBase {
    int saves = 0;
    SaveUI() : UIBase("saved-ui") {}
    void save() { ++saves; }
};

struct OSCUI;
struct dsp {
    int inputs;
    int outputs;
    int computes = 0;
    explicit dsp(int ins = 1, int outs = 1) : inputs(ins), outputs(outs) {}
    virtual ~dsp() { destruction_order.push_back("dsp"); }
    virtual int getNumInputs() { return inputs; }
    virtual int getNumOutputs() { return outputs; }
    virtual void compute(int count, double** input, double** output) {
        ++computes;
        for (int channel = 0; channel < outputs; ++channel) {
            for (int frame = 0; frame < count; ++frame) {
                output[channel][frame] = input && channel < inputs
                    ? input[channel][frame] * 2.0 : 42.0;
            }
        }
    }
    virtual void buildUserInterface(OSCUI*) {}
};

struct dsp_adapter : dsp {
    dsp* borrowed;
    dsp_adapter(dsp* value, int ins, int outs, int, bool)
        : dsp(ins, outs), borrowed(value) {}
    ~dsp_adapter() override { destruction_order.push_back("mc-adapter"); }
    void compute(int count, double** input, double** output) override {
        ++computes;
        borrowed->compute(count, input, output);
    }
};

namespace oscfaust {
struct OSCControler {
    static recursive_mutex& globalMutex() {
        static recursive_mutex mutex;
        return mutex;
    }
};
}

struct OSCUI : UIBase {
    static vector<string> last_arguments;
    static int runs;
    OSCUI(const char*, int argc, char** argv) : UIBase("osc-ui") {
        last_arguments.assign(argv, argv + argc);
    }
    void run() { ++runs; }
    string getInfos() { return "OSC ready"; }
};
vector<string> OSCUI::last_arguments;
int OSCUI::runs = 0;

struct GUI {
    static int updates;
    static void updateAllGuis() { ++updates; }
};
int GUI::updates = 0;

recursive_mutex gGUIRegistryMutex;
using RecursiveLock = lock_guard<recursive_mutex>;
using TryRecursiveLock = unique_lock<recursive_mutex>;

struct max_midi {
    vector<vector<long>> events;
    void handleSync(double, long status) { events.push_back({status}); }
    void handleData1(double, int type, int channel, long data) {
        events.push_back({type, channel, data});
    }
    void handleData2(double, int type, int channel, long data1, long data2) {
        events.push_back({type, channel, data1, data2});
    }
};

struct faustgen_factory {
    recursive_mutex audio_mutex;
    recursive_mutex ui_mutex;
    bool audio_available = true;
    int audio_unlocks = 0;
    int ui_locks = 0;
    int ui_unlocks = 0;
    bool try_lock_audio() {
        return audio_available && audio_mutex.try_lock();
    }
    void unlock_audio() { ++audio_unlocks; audio_mutex.unlock(); }
    void lock_audio() { audio_mutex.lock(); }
    void lock_ui() { ++ui_locks; ui_mutex.lock(); }
    void unlock_ui() { ++ui_unlocks; ui_mutex.unlock(); }
};

class faustgen {
public:
    faustgen_factory* fDSPfactory = nullptr;
    max_midi fMidiHandler;
    mspUI* fDSPUI = nullptr;
    MidiUI* fMidiUI = nullptr;
    OSCUI* fOSCUI = nullptr;
    SaveUI* fSavedUI = nullptr;
    dsp* fDSP = nullptr;
    dsp* fMCDSP = nullptr;
    bool fMute = false;
    bool m_is_mc = false;
    int output_dumps = 0;

    void anything(long, t_symbol*, long, t_atom*);
    void osc(long, t_symbol*, long, t_atom*);
    void midievent(long, t_symbol*, long, t_atom*);
    void perform(int, t_sample**, long, t_sample**, long);
    void free_dsp();
    void mute(long, long);
    long multichanneloutputs(long);
    void dump_outputs() { ++output_dumps; }
};
'''


CASES = r'''
static t_atom make_long(long value) {
    t_atom atom; atom.a_type = A_LONG; atom.a_w.w_long = value; return atom;
}
static t_atom make_float(double value) {
    t_atom atom; atom.a_type = A_FLOAT; atom.a_w.w_float = value; return atom;
}
static t_atom make_symbol(const char* value) {
    t_atom atom; atom.a_type = A_SYM; atom.a_w.w_sym = gensym(value); return atom;
}

int main() {
    faustgen_factory factory;
    faustgen object;
    object.fDSPfactory = &factory;
    object.fDSPUI = new mspUI();
    object.fDSPUI->values = {{"button", 0}, {"gain", 0}, {"band  1", 0},
                             {"band  2", 0}, {"band  3", 0}, {"fallback1", 0}};

    // A zero-argument known control is pulsed 0 -> 1 -> 0 without touching av.
    object.anything(0, gensym("button"), 0, nullptr);
    assert((object.fDSPUI->writes == vector<pair<string, double>>{
        {"button", 0}, {"button", 1}, {"button", 0}}));
    assert(object.fDSPUI->values["button"] == 0);
    assert(factory.ui_locks == factory.ui_unlocks);

    // Numbered messages expand over padded parameter names.
    t_atom list[] = {make_long(10), make_float(11.5), make_long(12)};
    object.anything(0, gensym("band  1"), 3, list);
    assert(object.fDSPUI->values["band  1"] == 10);
    assert(object.fDSPUI->values["band  2"] == 11.5);
    assert(object.fDSPUI->values["band  3"] == 12);

    // If the expanded name is absent, the original numbered name is used.
    t_atom fallback = make_float(0.25);
    object.anything(0, gensym("fallback1"), 1, &fallback);
    assert(object.fDSPUI->values["fallback1"] == 0.25);

    t_atom value = make_long(7);
    object.anything(0, gensym("gain"), 1, &value);
    assert(object.fDSPUI->values["gain"] == 7);
    size_t writes_before_invalid = object.fDSPUI->writes.size();
    t_atom invalid = make_symbol("not-a-number");
    object.anything(0, gensym("gain"), 1, &invalid);
    assert(object.fDSPUI->writes.size() == writes_before_invalid);
    object.anything(0, gensym("missing"), 0, nullptr);
    assert(factory.ui_locks == factory.ui_unlocks);

    // OSC rejects malformed calls and translates a valid call exactly.
    int runs_before = OSCUI::runs;
    object.osc(0, gensym("osc"), 0, nullptr);
    assert(OSCUI::runs == runs_before);
    t_atom bad_osc[] = {make_symbol("localhost"), make_long(5510), make_float(5511),
                        make_long(1), make_long(0)};
    object.osc(0, gensym("osc"), 5, bad_osc);
    assert(OSCUI::runs == runs_before);

    object.fDSP = new dsp(1, 2);
    t_atom osc[] = {make_symbol("127.0.0.1"), make_long(5510), make_long(5511),
                    make_long(2), make_long(1)};
    object.osc(0, gensym("osc"), 5, osc);
    assert(OSCUI::runs == runs_before + 1);
    assert((OSCUI::last_arguments == vector<string>{
        "Faust", "-desthost", "127.0.0.1", "-port", "5510",
        "-outport", "5511", "-xmit", "2", "-bundle", "1"}));
    assert(factory.ui_locks == factory.ui_unlocks);

    // MIDI status bytes are split into type/channel and dispatched by arity.
    object.midievent(0, gensym("midievent"), 0, nullptr);
    t_atom midi1[] = {make_long(0xf8)};
    t_atom midi2[] = {make_long(0xc3), make_long(64)};
    t_atom midi3[] = {make_long(0x92), make_long(60), make_long(100)};
    object.midievent(0, gensym("midievent"), 1, midi1);
    object.midievent(0, gensym("midievent"), 2, midi2);
    object.midievent(0, gensym("midievent"), 3, midi3);
    assert((object.fMidiHandler.events == vector<vector<long>>{
        {0xf8}, {0xc0, 3, 64}, {0x90, 2, 60, 100}}));
    t_atom bad_midi[] = {make_symbol("note"), make_long(1)};
    object.midievent(0, gensym("midievent"), 2, bad_midi);
    assert(object.fMidiHandler.events.size() == 3);

    // Audio outputs are always cleared, including mute and lock-contention paths.
    double input_data[] = {1, 2, 3, 4};
    double output_a[] = {9, 9, 9, 9};
    double output_b[] = {9, 9, 9, 9};
    double* inputs[] = {input_data};
    double* outputs[] = {output_a, output_b};
    int unlocks_before_audio = factory.audio_unlocks;

    object.mute(0, 1);
    object.perform(4, inputs, 1, outputs, 2);
    assert(all_of(output_a, output_a + 4, [](double x) { return x == 0; }));
    assert(all_of(output_b, output_b + 4, [](double x) { return x == 0; }));
    assert(object.fDSP->computes == 0);

    object.mute(0, 0);
    factory.audio_available = false;
    fill(output_a, output_a + 4, 9);
    object.perform(4, inputs, 1, outputs, 2);
    assert(all_of(output_a, output_a + 4, [](double x) { return x == 0; }));
    assert(object.fDSP->computes == 0);

    factory.audio_available = true;
    object.perform(4, inputs, 1, outputs, 2);
    assert((vector<double>(output_a, output_a + 4) == vector<double>{2, 4, 6, 8}));
    assert(all_of(output_b, output_b + 4, [](double x) { return x == 42; }));
    assert(object.fDSP->computes == 1);
    assert(object.output_dumps == 1 && GUI::updates == 1);
    assert(factory.audio_unlocks == unlocks_before_audio + 1);

    // Multichannel mode lazily creates and then reuses its layout adapter.
    object.m_is_mc = true;
    delete object.fDSP;
    object.fDSP = new dsp(1, 2);
    object.perform(4, inputs, 1, outputs, 2);
    dsp* first_adapter = object.fMCDSP;
    assert(first_adapter);
    object.perform(4, inputs, 1, outputs, 2);
    assert(object.fMCDSP == first_adapter);
    assert(object.multichanneloutputs(0) == 2);
    assert(object.multichanneloutputs(1) == 0);
    object.m_is_mc = false;
    assert(object.multichanneloutputs(0) == 1);

    // Teardown preserves ownership order: adapter, DSP, MIDI, OSC, control UI.
    object.fSavedUI = new SaveUI();
    object.fMidiUI = new MidiUI();
    destruction_order.clear();
    object.free_dsp();
    assert(!object.fSavedUI && !object.fMCDSP && !object.fDSP && !object.fMidiUI
           && !object.fOSCUI && !object.fDSPUI);
    auto adapter_pos = find(destruction_order.begin(), destruction_order.end(), "mc-adapter");
    auto dsp_pos = find(destruction_order.begin(), destruction_order.end(), "dsp");
    auto midi_pos = find(destruction_order.begin(), destruction_order.end(), "midi-ui");
    auto osc_pos = find(destruction_order.begin(), destruction_order.end(), "osc-ui");
    auto ui_pos = find(destruction_order.begin(), destruction_order.end(), "dsp-ui");
    assert(adapter_pos < dsp_pos && dsp_pos < midi_pos && midi_pos < osc_pos && osc_pos < ui_pos);

    cout << "parameters, OSC, MIDI, audio, MC adapter, and teardown: OK\n";
}
'''


class FaustgenRuntimeTest(unittest.TestCase):
    def test_runtime_behaviour(self):
        source = FAUSTGEN_SOURCE.read_text()
        methods = definitions(
            source,
            (
                "void faustgen::free_dsp",
                "void faustgen::anything",
                "void faustgen::osc",
                "void faustgen::midievent",
                "inline void faustgen::perform",
                "void faustgen::mute",
                "long faustgen::multichanneloutputs",
            ),
        )
        with tempfile.TemporaryDirectory(prefix="faustgen-runtime-") as temporary:
            compile_and_run(STUBS + methods + CASES, temporary, "faustgen-runtime")


if __name__ == "__main__":
    unittest.main()
