"""Tests for 'report' (controls sent when they change) and 'json'."""

import tempfile
import unittest

from cpp_test_support import FAUSTGEN_SOURCE, compile_and_run, definitions


STUBS = r'''
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <vector>
using namespace std;

#define FAUSTFLOAT double
#define A_LONG 1
#define A_FLOAT 2
#define A_SYM 3

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
double atom_getfloat(t_atom* atom) {
    return atom->a_type == A_LONG ? double(atom->a_w.w_long) : atom->a_w.w_float;
}
void atom_setsym(t_atom* atom, t_symbol* value) { atom->a_type = A_SYM; atom->a_w.w_sym = value; }
void atom_setfloat(t_atom* atom, double value) { atom->a_type = A_FLOAT; atom->a_w.w_float = value; }

vector<string> posts;
void post(const char* text, ...) { posts.push_back(text); }

// What the control outlet sent: "json <text>", or "path cur min max"
vector<string> sent;
void outlet_list(void*, t_symbol*, long ac, t_atom* av) {
    assert(ac == 4);
    sent.push_back(string(av[0].a_w.w_sym->s_name) + " " + to_string(av[1].a_w.w_float) + " "
                   + to_string(av[2].a_w.w_float) + " " + to_string(av[3].a_w.w_float));
}
void outlet_anything(void*, t_symbol* s, long ac, t_atom* av) {
    assert(ac == 1);
    sent.push_back(string(s->s_name) + " " + av[0].a_w.w_sym->s_name);
}

// The clock: armed with a delay, or unset
double clock_delay = -1;
void clock_fdelay(void*, double ms) { clock_delay = ms; }
void clock_unset(void*) { clock_delay = -1; }

struct Item {
    double value, min, max;
    double getValue() { return value; }
    double getMinValue() { return min; }
    double getMaxValue() { return max; }
};
struct mspUI {
    typedef map<string, Item*>::iterator iterator;
    map<string, Item*> inputs, outputs;
    iterator begin2() { return inputs.begin(); }
    iterator end2() { return inputs.end(); }
    iterator begin4() { return outputs.begin(); }
    iterator end4() { return outputs.end(); }
};

struct faustgen_factory {
    recursive_mutex ui_mutex;
    int ui_locks = 0, ui_unlocks = 0;
    bool locked_while_sending = false;
    void lock_ui() { ++ui_locks; ui_mutex.lock(); }
    void unlock_ui() { ++ui_unlocks; ui_mutex.unlock(); }
    const char* get_json() { return "{\"name\":\"x\"}"; }
};

class faustgen {
public:
    faustgen_factory* fDSPfactory = nullptr;
    mspUI* fDSPUI = nullptr;
    void* m_control_outlet = nullptr;
    void* fReportClock = nullptr;
    long fReportPeriod = 0;
    map<string, FAUSTFLOAT> fReported;

    void send_json();
    void json(long, t_symbol*, long, t_atom*);
    void schedule_report();
    void report(long, t_symbol*, long, t_atom*);
    void report_changes();
};
'''


CASES = r'''
static t_atom make_long(long value) {
    t_atom atom; atom.a_type = A_LONG; atom.a_w.w_long = value; return atom;
}
static t_atom make_symbol(const char* value) {
    t_atom atom; atom.a_type = A_SYM; atom.a_w.w_sym = gensym(value); return atom;
}

int main() {
    faustgen_factory factory;
    faustgen object;
    object.fDSPfactory = &factory;
    Item freq{440, 20, 2000}, gain{0.5, 0, 1}, level{0, 0, 1}, nan_meter{NAN, 0, 1};
    object.fDSPUI = new mspUI();
    object.fDSPUI->inputs = {{"/x/freq", &freq}, {"/x/gain", &gain}};
    object.fDSPUI->outputs = {{"/x/level", &level}, {"/x/nan", &nan_meter}};

    // 'json' answers on the control outlet
    object.json(0, gensym("json"), 0, nullptr);
    assert((sent == vector<string>{"json {\"name\":\"x\"}"}));
    sent.clear();

    // 'report' with a bad argument changes nothing
    t_atom bad = make_symbol("fast");
    object.report(0, gensym("report"), 1, &bad);
    assert(object.fReportPeriod == 0 && clock_delay == -1 && sent.empty());

    // 'report 30': the JSON at once, the clock armed
    t_atom thirty = make_long(30);
    object.report(0, gensym("report"), 1, &thirty);
    assert(object.fReportPeriod == 30 && clock_delay == 30);
    assert((sent == vector<string>{"json {\"name\":\"x\"}"}));
    sent.clear();

    // First tick: every control, inputs then outputs, and the clock again
    clock_delay = -1;
    object.report_changes();
    assert(sent.size() == 4 && clock_delay == 30);
    assert(sent[0] == "/x/freq 440.000000 20.000000 2000.000000");
    assert(sent[2] == "/x/level 0.000000 0.000000 1.000000");
    sent.clear();

    // Nothing changed (a NaN bargraph included): nothing sent
    object.report_changes();
    assert(sent.empty());

    // A control moved, whatever moved it, and a bargraph: only those
    freq.value = 660;
    level.value = 0.25;
    object.report_changes();
    assert((sent == vector<string>{"/x/freq 660.000000 20.000000 2000.000000",
                                   "/x/level 0.250000 0.000000 1.000000"}));
    sent.clear();
    assert(factory.ui_locks == factory.ui_unlocks);

    // Already on: another period, no second JSON
    t_atom ten = make_long(10);
    object.report(0, gensym("report"), 1, &ten);
    assert(object.fReportPeriod == 10 && clock_delay == 10 && sent.empty());

    // 'report 0': the clock stops; a tick that was due arms nothing
    t_atom zero = make_long(0);
    object.report(0, gensym("report"), 1, &zero);
    assert(object.fReportPeriod == 0 && clock_delay == -1);
    object.report_changes();
    assert(clock_delay == -1);

    // On again: every control is sent again, after the JSON
    object.report(0, gensym("report"), 1, &thirty);
    object.report_changes();
    assert(sent.size() == 5 && sent[0].rfind("json ", 0) == 0);

    cout << "report and json: OK\n";
}
'''


class FaustgenReportTest(unittest.TestCase):
    def test_report_and_json(self):
        source = FAUSTGEN_SOURCE.read_text()
        methods = definitions(
            source,
            (
                "void faustgen::send_json",
                "void faustgen::json(long",
                "void faustgen::schedule_report",
                "void faustgen::report(long",
                "void faustgen::report_changes",
            ),
        )
        with tempfile.TemporaryDirectory(prefix="faustgen-report-") as temporary:
            compile_and_run(STUBS + methods + CASES, temporary, "faustgen-report")


if __name__ == "__main__":
    unittest.main()
