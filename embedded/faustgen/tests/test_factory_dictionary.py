"""Regression tests for cached patch restoration.

Compile the actual dictionary methods with small stand-ins for Max's dictionary
and memory APIs, so this test does not require a running Max installation.
"""

from pathlib import Path
import tempfile
import unittest

from cpp_test_support import (
    FACTORY_HEADER as HEADER,
    FACTORY_SOURCE as SOURCE,
    ROOT,
    compile_and_run,
    definition,
)



STUBS = r'''
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;
#define LLVM_OPTIMIZATION -1
using t_atom_long = long;
using t_max_err = int;
const int MAX_ERR_NONE = 0;
const char* FAUSTGEN_VERSION = "test-version";
const char* DEFAULT_SOURCE_CODE = "process = 0,0;";
int allocations = 0;
int frees = 0;
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
    assert(size >= 0);
    ++allocations;
    auto handle = static_cast<char**>(malloc(sizeof(char*)));
    *handle = static_cast<char*>(calloc(size, 1)); return handle;
}
void sysmem_freehandle(char** handle) { ++frees; free(*handle); free(handle); }
void sysmem_copyptr(const char* source, char* target, long size) {
    memcpy(target, source, size);
}
void post(const char*, ...) {}
string getSerialNumber() { return "test-machine"; }
string getTarget() { return "test-target"; }
struct dsp_factory {
    vector<string> getIncludePathnames() { return {}; }
};
struct llvm_dsp_factory : dsp_factory {};
using interpreter_dsp_factory = llvm_dsp_factory;
string writeDSPFactoryToMachine(llvm_dsp_factory*, const string&) { return "cached-code"; }
string writeInterpreterDSPFactoryToBitcode(interpreter_dsp_factory*) { return "cached-code"; }
// Records the arguments given to libfaust when a DSP is compiled from its source.
llvm_dsp_factory compiled_from_source;
vector<string> compiled_arguments;
llvm_dsp_factory* createDSPFactoryFromString(const string&, const string&, int argc,
                                             const char* argv[], const string&, string&, int) {
    compiled_arguments.assign(argv, argv + argc);
    return &compiled_from_source;
}
interpreter_dsp_factory* createInterpreterDSPFactoryFromString(const string&, const string&, int argc,
                                                               const char* argv[], string&) {
    compiled_arguments.assign(argv, argv + argc);
    return &compiled_from_source;
}
struct SoundUI {
    SoundUI(const vector<string>&, int, void*, bool) {}
};
struct faustgen {
    void hilight_error(const string&) {}
};
class faustgen_factory {
public:
    using StringVectorIt = vector<string>::const_iterator;
    enum sampleFormat : long { kFloat, kDouble, kNone };
    long fSourceCodeSize = 0, fBitCodeSize = 0;
    char** fSourceCode = sysmem_newhandleclear(1);
    char** fBitCode = nullptr;
    sampleFormat fSampleFormat = kNone;
    set<string> fLibraryPath;
    llvm_dsp_factory* fDSPfactory = nullptr;
    set<faustgen*> fInstances;
    SoundUI* fSoundUI = nullptr;
    string fDrawPath = "/draw/";
    vector<string> fOptions;
    vector<string> fCompileOptions;
    int fOptLevel = LLVM_OPTIMIZATION;
    int fFaustNumber = 1;
    ~faustgen_factory() {
        if (fSourceCode) sysmem_freehandle(fSourceCode);
        if (fBitCode) sysmem_freehandle(fBitCode);
        delete fSoundUI;
    }
    void remove_svg() {}
    void add_compile_option(const string&, const string&);
    void add_compile_option(const string&);
    void default_compile_options();
    void print_compile_options();
    dsp_factory* create_factory_from_sourcecode();
    void load_compile_options(t_dictionary*);
    void load_library_paths(t_dictionary*);
    void free_sourcecode();
    void free_bitcode();
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
    // A patch saved by an older faustgen~, with its machine code and machine
    t_dictionary saved;
    saved.strings = {{"sourcecode", source}, {"machinecode", "cached-code"},
        {"serial_number", getSerialNumber()}, {"version", FAUSTGEN_VERSION},
        {"library_path0", "/custom/faust-libraries"}};
    saved.numbers = {{"sourcecode_size", long(source.size())},
        {"machinecode_size", 11}, {"sample_format", 0}};
    // The source and library paths survive repeated save/reopen cycles. The machine code of
    // an older patch is ignored (the disk cache keeps the compiled code), and no machine
    // code, serial number or sample format is written any more.
    for (int reopen = 0; reopen < 3; ++reopen) {
        faustgen_factory factory;
        factory.getfromdictionary(&saved);
        assert(string(factory.get_sourcecode()) == source);
        assert(factory.fSourceCodeSize == long(source.size()));
        assert(!factory.fBitCode && factory.fBitCodeSize == 0);
        // The sample format comes from the options (-double by default), not from 'sample_format'
        assert(factory.fSampleFormat == faustgen_factory::kDouble);
        assert(factory.fLibraryPath.count("/custom/faust-libraries"));
        llvm_dsp_factory compiled;
        factory.fDSPfactory = &compiled;
        t_dictionary next;
        factory.appendtodictionary(&next);
        assert(next.strings.at("sourcecode") == source);
        assert(next.numbers.at("sourcecode_size") == long(source.size()));
        assert(next.strings.at("version") == FAUSTGEN_VERSION);
        assert(next.strings.at("library_path0") == "/custom/faust-libraries");
        assert(!next.strings.count("machinecode") && !next.strings.count("serial_number"));
        assert(!next.numbers.count("machinecode_size") && !next.numbers.count("sample_format"));
        saved = next;
    }
    // Reapplying dictionaries to one named factory replaces, rather than leaks, the source
    // buffer, and drops the code compiled for the previous dictionary.
    {
        faustgen_factory factory;
        factory.getfromdictionary(&saved);
        int live_before = allocations - frees;
        factory.getfromdictionary(&saved);
        assert(allocations - frees == live_before);
        factory.fBitCode = sysmem_newhandleclear(5);
        strcpy(*factory.fBitCode, "code");
        factory.fBitCodeSize = 4;
        factory.getfromdictionary(&saved);
        assert(!factory.fBitCode && factory.fBitCodeSize == 0);
        assert(string(factory.get_sourcecode()) == source);
        assert(allocations - frees == 1);
    }
    // Legacy dictionaries without source must still get the default DSP text.
    auto without_source = saved;
    without_source.strings.erase("sourcecode"); without_source.numbers.erase("sourcecode_size");
    faustgen_factory legacy;
    legacy.getfromdictionary(&without_source);
    assert(string(legacy.get_sourcecode()) == DEFAULT_SOURCE_CODE);

    // Older file imports counted the null terminator in sourcecode_size.
    auto terminated_size = saved;
    terminated_size.numbers["sourcecode_size"] = long(source.size() + 1);
    faustgen_factory old_file_import;
    old_file_import.getfromdictionary(&terminated_size);
    assert(string(old_file_import.get_sourcecode()) == source);
    assert(old_file_import.fSourceCodeSize == long(source.size()));

    // A damaged in-memory state must not dereference a null source handle while saving.
    faustgen_factory inconsistent_source;
    sysmem_freehandle(inconsistent_source.fSourceCode);
    inconsistent_source.fSourceCode = nullptr;
    inconsistent_source.fSourceCodeSize = 12;
    t_dictionary inconsistent_saved;
    inconsistent_source.appendtodictionary(&inconsistent_saved);
    assert(!inconsistent_saved.numbers.count("sourcecode_size"));
    assert(!inconsistent_saved.strings.count("sourcecode"));

    // Corrupt or inconsistent source lengths are rejected before allocation/copying.
    for (int malformed = 0; malformed < 2; ++malformed) {
        auto dictionary = saved;
        if (malformed == 0) dictionary.numbers["sourcecode_size"] = -1;
        if (malformed == 1) dictionary.numbers["sourcecode_size"] += 2;
        faustgen_factory factory;
        factory.getfromdictionary(&dictionary);
        assert(string(factory.get_sourcecode()) == DEFAULT_SOURCE_CODE);
    }
    cout << "source, library paths, repeated loads, corrupt lengths, legacy, no machine code: OK\n";

    // The 'compileoptions' arguments are saved with the patch and restored, so a DSP
    // compiled with an entry point other than 'process' (-pn) keeps it after reopening:
    // they select the code of the disk cache, or the DSP compiled from source.
    const string program = "import(\"stdfaust.lib\");\nprocess = _;\n"
                           "p2 = _ <: si.bus(2);\np3 = _ <: si.bus(3);";
    const vector<string> options = {"-pn", "myDsp", "--process-name", "p2",
                                    "-I", "/Users/somebody/My Faust Libraries/"};
    auto contains = [](const vector<string>& arguments, const vector<string>& sequence) {
        return search(arguments.begin(), arguments.end(), sequence.begin(), sequence.end())
               != arguments.end();
    };
    t_dictionary with_options;
    {
        t_dictionary source_only;
        source_only.strings = {{"sourcecode", program}};
        source_only.numbers = {{"sourcecode_size", long(program.size())}};
        faustgen_factory factory;
        factory.getfromdictionary(&source_only);
        // State after 'compileoptions -pn myDsp --process-name p2 -I ...' and compilation.
        factory.fOptions = options;
        compiled_arguments.clear();
        factory.fDSPfactory = static_cast<llvm_dsp_factory*>(factory.create_factory_from_sourcecode());
        assert(contains(compiled_arguments, options));
        assert(factory.fSampleFormat == faustgen_factory::kDouble);
        factory.appendtodictionary(&with_options);
    }
    for (size_t i = 0; i < options.size(); ++i) {
        assert(with_options.strings.at("compile_option" + to_string(i)) == options[i]);
    }
    assert(!with_options.strings.count("compile_option" + to_string(options.size())));

    // Reopened, on this machine or another one, by this faustgen~ or another version: the
    // options are restored, and a compilation from source keeps the entry point.
    for (int other = 0; other < 3; ++other) {
        auto dictionary = with_options;
        if (other == 1) dictionary.strings["serial_number"] = "other-machine";
        if (other == 2) dictionary.strings["version"] = "other-version";
        faustgen_factory factory;
        factory.getfromdictionary(&dictionary);
        assert(!factory.fBitCode);
        assert(factory.fOptions == options);
        assert(contains(factory.fCompileOptions, options));
        assert(factory.fSampleFormat == faustgen_factory::kDouble);
        compiled_arguments.clear();
        factory.create_factory_from_sourcecode();
        assert(contains(compiled_arguments, options));
        assert(contains(compiled_arguments, {"-I", "/Users/somebody/My Faust Libraries/"}));
        // Saving again writes back the same options.
        llvm_dsp_factory compiled;
        factory.fDSPfactory = &compiled;
        t_dictionary resaved;
        factory.appendtodictionary(&resaved);
        for (size_t i = 0; i < options.size(); ++i) {
            assert(resaved.strings.at("compile_option" + to_string(i)) == options[i]);
        }
    }

    // A patch saved without options (older faustgen~, or no 'compileoptions') restores
    // none, even on a factory that had some.
    {
        faustgen_factory factory;
        factory.getfromdictionary(&with_options);
        auto without_options = with_options;
        for (size_t i = 0; i < options.size(); ++i) {
            without_options.strings.erase("compile_option" + to_string(i));
        }
        factory.getfromdictionary(&without_options);
        assert(factory.fOptions.empty());
        assert(!contains(factory.fCompileOptions, {"--process-name"}));
    }

    // Instances with their own saved state (six abstractions, -pn p2 ... p7) each get
    // back their own entry point.
    {
        vector<t_dictionary> patches(6);
        for (int n = 0; n < 6; ++n) {
            faustgen_factory factory;
            factory.getfromdictionary(&with_options);
            factory.fOptions = {"-pn", "myDsp", "--process-name", "p" + to_string(n + 2)};
            llvm_dsp_factory compiled;
            factory.fDSPfactory = &compiled;
            factory.appendtodictionary(&patches[n]);
        }
        vector<faustgen_factory> reopened(6);
        for (int n = 0; n < 6; ++n) {
            reopened[n].getfromdictionary(&patches[n]);
        }
        for (int n = 0; n < 6; ++n) {
            compiled_arguments.clear();
            reopened[n].create_factory_from_sourcecode();
            assert(contains(compiled_arguments, {"--process-name", "p" + to_string(n + 2)}));
            for (int other = 0; other < 6; ++other) {
                if (other != n) {
                    assert(!contains(compiled_arguments, {"--process-name", "p" + to_string(other + 2)}));
                }
            }
            assert(!contains(compiled_arguments, {"-I", "/Users/somebody/My Faust Libraries/"}));
        }
    }

    // The sample format follows the options: '-single' gives float samples, whatever the
    // 'sample_format' key of an older patch says.
    for (int with_single = 0; with_single < 2; ++with_single) {
        auto dictionary = with_options;
        dictionary.numbers["sample_format"] = with_single ? faustgen_factory::kDouble : faustgen_factory::kFloat;
        for (size_t i = 0; i < options.size(); ++i) {
            dictionary.strings.erase("compile_option" + to_string(i));
        }
        if (with_single) dictionary.strings["compile_option0"] = "-single";
        faustgen_factory factory;
        factory.getfromdictionary(&dictionary);
        assert(factory.fSampleFormat == (with_single ? faustgen_factory::kFloat : faustgen_factory::kDouble));
    }
    cout << "compile options and process name saved, restored and recompiled: OK\n";
}
'''


class DictionaryRestoreTest(unittest.TestCase):
    def test_cached_patch_retains_editable_source(self):
        source = SOURCE.read_text()
        signatures = ["void faustgen_factory::" + name
                      for name in ("add_compile_option(const string& key",
                                   "add_compile_option(const string& value",
                                   "default_compile_options", "print_compile_options",
                                   "load_compile_options",
                                   "load_library_paths", "free_sourcecode", "free_bitcode", "default_source_code",
                                   "load_source_code", "getfromdictionary",
                                   "appendtodictionary")]
        signatures.append("dsp_factory* faustgen_factory::create_factory_from_sourcecode")
        methods = "\n".join(definition(source, signature) for signature in signatures)
        getter = definition(HEADER.read_text(), "char* get_sourcecode()")
        getter = getter.replace("char* get_sourcecode()", "char* faustgen_factory::get_sourcecode()", 1)
        with tempfile.TemporaryDirectory(prefix="faustgen-dictionary-test-") as temporary:
            for backend in ([], ["-DINTERP_BACKEND"]):
                with self.subTest(backend=backend):
                    compile_and_run(
                        STUBS + methods + getter + CASES,
                        temporary,
                        name="dictionary-test",
                        flags=backend,
                    )


if __name__ == "__main__":
    import sys
    if len(sys.argv) > 1 and Path(sys.argv[1]).is_dir():
        ROOT = Path(sys.argv.pop(1)).resolve()
        SOURCE = ROOT / "src/faustgen_factory.cpp"
        HEADER = ROOT / "src/faustgen_factory.h"
    unittest.main()
