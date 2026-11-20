"""Tests for 'wasm': the DSP compiled for the phones, and the order a new DSP is announced in.

The module and its JSON come from libfaust's wasm-dsp.h API, which a client
linked against libfaust checks; here, what faustgen~ does with them."""

import tempfile
import unittest

from cpp_test_support import FACTORY_SOURCE, FAUSTGEN_SOURCE, compile_and_run, definitions


STUBS = r'''
#include <cassert>
#include <cstdlib>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#define A_LONG 1
#define A_FLOAT 2
#define A_SYM 3
struct t_symbol { string storage; const char* s_name; };
t_symbol* gensym(const char* text) {
    t_symbol* symbol = new t_symbol{text, nullptr};
    symbol->s_name = symbol->storage.c_str();
    return symbol;
}
struct t_atom {
    int a_type = 0;
    union { long w_long; double w_float; t_symbol* w_sym; } a_w{};
};
int atom_gettype(t_atom* atom) { return atom->a_type; }
t_symbol* atom_getsym(t_atom* atom) { return atom->a_w.w_sym; }

vector<string> events;
void post(const char* format, ...) { events.push_back(string("post ") + format); }


struct faustgen_factory {
    bool fail = false;
    bool write_wasm(const string& folder, bool poly, string& error) {
        events.push_back("wasm " + folder + (poly ? " poly" : " mono"));
        if (fail) error = "broken";
        return !fail;
    }
};

class faustgen {
public:
    faustgen_factory* fDSPfactory = nullptr;
    int fVoices = 0;
    long fReportPeriod = 0;
    string fWasmFolder;
    void create_jsui() { events.push_back("jsui"); }
    void send_json() { events.push_back("json"); }
    void export_wasm();
    void announce_dsp();
    void wasm(long, t_symbol*, long, t_atom*);
};
'''


CASES = r'''
int main() {
    string json = "{\"name\": \"x\", \"size\": 16}";

    // Written whole, through a temporary file that does not stay
    char folder[] = "/tmp/faustgen-wasm-XXXXXX";
    assert(mkdtemp(folder));
    string path = string(folder) + "/dsp-meta.json";
    assert(write_file_atomically(path, "first"));
    assert(write_file_atomically(path, json));
    ifstream in(path);
    stringstream read;
    read << in.rdbuf();
    assert(read.str() == json);
    assert(!ifstream(path + ".tmp"));
    assert(!write_file_atomically(string(folder) + "/missing/dsp-meta.json", json));
    remove(path.c_str());
    rmdir(folder);

    faustgen_factory factory;
    faustgen object;
    object.fDSPfactory = &factory;

    // No folder: the JSON only, to the js objects, and on the outlet with 'report'
    object.announce_dsp();
    assert((events == vector<string>{"jsui"}));
    events.clear();
    object.fReportPeriod = 30;

    // 'wasm <folder>': written at once, without the trailing separator
    t_atom folder_atom;
    folder_atom.a_type = A_SYM;
    folder_atom.a_w.w_sym = gensym("/served/app/");
    object.wasm(0, gensym("wasm"), 1, &folder_atom);
    assert(object.fWasmFolder == "/served/app");
    assert(events.size() == 2 && events[0] == "wasm /served/app mono");
    events.clear();

    // A new DSP: its wasm first, then its JSON; a polyphonic one with external memory
    object.fVoices = 8;
    object.announce_dsp();
    assert(events.size() == 4 && events[0] == "wasm /served/app poly"
           && events[2] == "jsui" && events[3] == "json");
    events.clear();

    // A failed compilation is said, and the JSON still goes
    factory.fail = true;
    object.announce_dsp();
    assert(events[1].find("not compiled") != string::npos && events.back() == "json");
    events.clear();

    // A number is no folder; 'wasm' alone stops
    t_atom number;
    number.a_type = A_LONG;
    number.a_w.w_long = 3;
    object.wasm(0, gensym("wasm"), 1, &number);
    assert(object.fWasmFolder == "/served/app" && events.size() == 1);
    events.clear();
    object.wasm(0, gensym("wasm"), 0, nullptr);
    assert(object.fWasmFolder.empty());
    object.announce_dsp();
    assert((events == vector<string>{"jsui", "json"}));

    cout << "wasm export and announce order: OK\n";
}
'''


class FaustgenWasmTest(unittest.TestCase):
    def test_wasm_export(self):
        factory = definitions(
            FACTORY_SOURCE.read_text(),
            (
                "static bool write_file_atomically",
            ),
        )
        methods = definitions(
            FAUSTGEN_SOURCE.read_text(),
            (
                "void faustgen::announce_dsp",
                "void faustgen::export_wasm",
                "void faustgen::wasm(long",
            ),
        )
        with tempfile.TemporaryDirectory(prefix="faustgen-wasm-") as temporary:
            compile_and_run(STUBS + factory + methods + CASES, temporary, "faustgen-wasm")


if __name__ == "__main__":
    unittest.main()
