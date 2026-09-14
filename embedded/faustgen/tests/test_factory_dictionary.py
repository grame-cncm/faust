"""Regression test for cached patch restoration; run with Python 3 and a C++ compiler.

Compile the actual dictionary methods with small stand-ins for Max's dictionary
and memory APIs, so this test does not require a running Max installation.
"""

from pathlib import Path
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "src/faustgen_factory.cpp"
HEADER = ROOT / "src/faustgen_factory.h"


def method(source, signature):
    start = source.index(signature)
    opening = source.index("{", start)
    depth = 1
    closing = opening + 1
    while depth:
        depth += (source[closing] == "{") - (source[closing] == "}")
        closing += 1
    return source[start:closing]


STUBS = r'''
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;
using t_atom_long = long;
using t_max_err = int;
const int MAX_ERR_NONE = 0;
const char* FAUSTGEN_VERSION = "test-version";
const char* DEFAULT_SOURCE_CODE = "process = 0,0;";
using t_symbol = const char*;
struct t_dictionary {
    map<string, string> strings;
    map<string, long> numbers;
};
t_symbol gensym(const char* value) { return value; }
int dictionary_getstring(t_dictionary* d, t_symbol key, const char** value) {
    auto item = d->strings.find(key);
    if (item == d->strings.end()) return 1;
    *value = item->second.c_str(); return 0;
}
int dictionary_getlong(t_dictionary* d, t_symbol key, t_atom_long* value) {
    auto item = d->numbers.find(key);
    if (item == d->numbers.end()) return 1;
    *value = item->second; return 0;
}
void dictionary_appendstring(t_dictionary* d, t_symbol key, const char* value) {
    d->strings[key] = value;
}
void dictionary_appendlong(t_dictionary* d, t_symbol key, long value) {
    d->numbers[key] = value;
}
char** sysmem_newhandleclear(long size) {
    auto handle = static_cast<char**>(malloc(sizeof(char*)));
    *handle = static_cast<char*>(calloc(size, 1)); return handle;
}
void sysmem_freehandle(char** handle) { free(*handle); free(handle); }
void sysmem_copyptr(const char* source, char* target, long size) {
    memcpy(target, source, size);
}
void post(const char*, ...) {}
string getSerialNumber() { return "test-machine"; }
string getTarget() { return "test-target"; }
struct llvm_dsp_factory {};
using interpreter_dsp_factory = llvm_dsp_factory;
string writeDSPFactoryToMachine(llvm_dsp_factory*, const string&) { return "cached-code"; }
string writeInterpreterDSPFactoryToBitcode(interpreter_dsp_factory*) { return "cached-code"; }
class faustgen_factory {
public:
    enum sampleFormat : long { kFloat, kDouble, kNone };
    long fSourceCodeSize = 0, fBitCodeSize = 0;
    char** fSourceCode = nullptr;
    char** fBitCode = nullptr;
    sampleFormat fSampleFormat = kNone;
    set<string> fLibraryPath;
    llvm_dsp_factory* fDSPfactory = nullptr;
    ~faustgen_factory() {
        if (fSourceCode) sysmem_freehandle(fSourceCode);
        if (fBitCode) sysmem_freehandle(fBitCode);
    }
    void load_library_paths(t_dictionary*);
    void default_source_code();
    void load_source_code(t_dictionary*);
    void getfromdictionary(t_dictionary*);
    void appendtodictionary(t_dictionary*);
    char* get_sourcecode();
};
'''


CASES = r'''
int main() {
    const string source = u8"declare name \"Mémoire\"; process = _,_;";
    t_dictionary saved;
    saved.strings = {{"sourcecode", source}, {"machinecode", "cached-code"},
        {"serial_number", getSerialNumber()}, {"version", FAUSTGEN_VERSION},
        {"library_path0", "/custom/faust-libraries"}};
    saved.numbers = {{"sourcecode_size", long(source.size())},
        {"machinecode_size", 11}, {"sample_format", 1}};
    // Cached DSP and editable source must survive repeated save/reopen cycles.
    for (int reopen = 0; reopen < 3; ++reopen) {
        faustgen_factory factory;
        factory.getfromdictionary(&saved);
        assert(string(factory.get_sourcecode()) == source);
        assert(factory.fSourceCodeSize == long(source.size()));
        assert(factory.fBitCode && string(*factory.fBitCode) == "cached-code");
        assert(factory.fSampleFormat == faustgen_factory::kDouble);
        assert(factory.fLibraryPath.count("/custom/faust-libraries"));
        llvm_dsp_factory compiled;
        factory.fDSPfactory = &compiled;
        t_dictionary next;
        factory.appendtodictionary(&next);
        assert(next.strings.at("sourcecode") == source);
        assert(next.strings.at("machinecode") == "cached-code");
        saved = next;
    }
    // Invalid or absent cache must preserve the existing source fallback.
    for (int fallback = 0; fallback < 5; ++fallback) {
        auto dictionary = saved;
        if (fallback == 0) dictionary.strings["serial_number"] = "other-machine";
        if (fallback == 1) dictionary.strings["version"] = "other-version";
        if (fallback == 2) dictionary.strings.erase("version");
        if (fallback == 3) dictionary.numbers.erase("machinecode_size");
        if (fallback == 4) dictionary.strings.erase("machinecode");
        faustgen_factory factory;
        factory.getfromdictionary(&dictionary);
        assert(string(factory.get_sourcecode()) == source);
        assert(!factory.fBitCode);
        assert(factory.fLibraryPath.count("/custom/faust-libraries"));
    }
    // Legacy dictionaries without source must still get the default DSP text.
    saved.strings.erase("sourcecode"); saved.numbers.erase("sourcecode_size");
    faustgen_factory legacy;
    legacy.getfromdictionary(&saved);
    assert(string(legacy.get_sourcecode()) == DEFAULT_SOURCE_CODE);
    assert(legacy.fBitCode);
    cout << "cached source, library paths, 3 save/reopen cycles, 5 fallbacks, legacy: OK\n";
}
'''


class DictionaryRestoreTest(unittest.TestCase):
    def test_cached_patch_retains_editable_source(self):
        source = SOURCE.read_text()
        definitions = "\n".join(method(source, "void faustgen_factory::" + name)
                                for name in ("load_library_paths", "default_source_code",
                                             "load_source_code", "getfromdictionary",
                                             "appendtodictionary"))
        getter = method(HEADER.read_text(), "char* get_sourcecode()")
        getter = getter.replace("char* get_sourcecode()", "char* faustgen_factory::get_sourcecode()", 1)
        with tempfile.TemporaryDirectory(prefix="faustgen-dictionary-test-") as temporary:
            cpp = Path(temporary) / "dictionary.cpp"
            cpp.write_text(STUBS + definitions + getter + CASES)
            for backend in ([], ["-DINTERP_BACKEND"]):
                with self.subTest(backend=backend):
                    binary = Path(temporary) / "dictionary-test"
                    subprocess.run(["c++", "-std=c++11", *backend, str(cpp), "-o", str(binary)], check=True)
                    subprocess.run([str(binary)], check=True)


if __name__ == "__main__":
    import sys
    if len(sys.argv) > 1 and Path(sys.argv[1]).is_dir():
        ROOT = Path(sys.argv.pop(1)).resolve()
        SOURCE = ROOT / "src/faustgen_factory.cpp"
        HEADER = ROOT / "src/faustgen_factory.h"
    unittest.main()
