"""Unit tests for faustgen_factory logic that does not require a Max process."""

import tempfile
import unittest

from cpp_test_support import FACTORY_SOURCE, compile_and_run, definition, definitions


STUBS = r'''
#include <algorithm>
#include <cassert>
#include <cstdarg>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

#define SEPARATOR '/'
#define DEFAULT_SOURCE_CODE "import(\"stdfaust.lib\");\nprocess=_,_;"
#define LLVM_OPTIMIZATION -1
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
long atom_getlong(t_atom* atom) { return atom->a_w.w_long; }
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

int allocations = 0;
int frees = 0;
char** sysmem_newhandleclear(long size) {
    assert(size >= 0);
    ++allocations;
    char** handle = static_cast<char**>(malloc(sizeof(char*)));
    *handle = static_cast<char*>(calloc(static_cast<size_t>(size), 1));
    return handle;
}
void sysmem_freehandle(char** handle) {
    assert(handle);
    ++frees;
    free(*handle);
    free(handle);
}
void sysmem_copyptr(const char* source, char* target, long size) {
    memcpy(target, source, static_cast<size_t>(size));
}

struct dsp_factory {};
struct faustgen {
    int updates = 0;
    string last_codebox;
    void update_sourcecode(const string& codebox = "") {
        ++updates;
        last_codebox = codebox;
    }
};

vector<string> generated_arguments;
string generated_error;
string generated_result = "compiled-codebox";
string generateAuxFilesFromString2(const string&, const string&, int argc,
                                   const char* const* argv, string& error) {
    generated_arguments.assign(argv, argv + argc);
    error = generated_error;
    return generated_result;
}

class faustgen_factory {
public:
    using StringVectorIt = vector<string>::const_iterator;
    enum sampleFormat { kFloat, kDouble, kNone };

    set<faustgen*> fInstances;
    dsp_factory* fDSPfactory = nullptr;
    long fSourceCodeSize = 0;
    char** fSourceCode = nullptr;
    long fBitCodeSize = 0;
    char** fBitCode = nullptr;
    set<string> fLibraryPath;
    string fResourcePath;
    string fDrawPath;
    vector<string> fOptions;
    vector<string> fCompileOptions;
    int fOptLevel = LLVM_OPTIMIZATION;
    sampleFormat fSampleFormat = kNone;
    int factory_frees = 0;

    void add_library_path(const string&);
    void add_compile_option(const string&, const string&);
    void add_compile_option(const string&);
    void default_compile_options();
    void default_source_code();
    void free_sourcecode();
    void free_bitcode();
    void update_sourcecode(int, char*);
    void compileoptions(long, t_symbol*, long, t_atom*);
    void librarypath(long, t_symbol*);
    void free_dsp_factory() { ++factory_frees; fDSPfactory = nullptr; }
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
    // Pure pathname helpers and shell-safety validation.
    assert(getFolderFromFilename("/tmp/faust/test.dsp") == "/tmp/faust");
    assert(getFolderFromFilename("test.dsp") == "");
    assert(getFolderFromFilename("/test.dsp") == "");
    assert(getFolderFromPath("/tmp/faust/") == "/tmp/faust/");
    assert(getFolderFromPath("volume.dsp") == "");
    assert(getFolderFromPath("name/relative") == "/relative");
    for (const string& safe : {"/tmp/a b/", "C:\\Faust Files\\", "été", "a'b", "a(b)"}) {
        assert(isSafePathSegment(safe));
    }
    for (const string& unsafe : vector<string>{
             "a\"b", "a`b", "a$b", "a|b", "a&b", "a;b", "a<b", "a>b",
             "a%b", "a\nb", "a\rb", string("a\x7f", 2)}) {
        assert(!isSafePathSegment(unsafe));
    }

    faustgen_factory factory;
    factory.add_library_path("/z/");
    factory.add_library_path("/a/");
    factory.add_library_path("/z/");
    assert((factory.fLibraryPath == set<string>{"/a/", "/z/"}));

    factory.add_compile_option("");
    factory.add_compile_option("-I", "");
    factory.add_compile_option("", "/ignored");
    assert(factory.fCompileOptions.empty());
    factory.add_compile_option("-vec");
    factory.add_compile_option("-I", "/extra/");
    assert((factory.fCompileOptions == vector<string>{"-vec", "-I", "/extra/"}));

    factory.fDrawPath = "/draw/";
    factory.fOptions = {"-vec", "-vs", "32"};
    factory.default_compile_options();
    assert(factory.fSampleFormat == faustgen_factory::kDouble);
    assert(factory.fOptLevel == LLVM_OPTIMIZATION);
    assert((factory.fCompileOptions == vector<string>{
        "-svg", "-I", "/a/", "-I", "/z/", "-O", "/draw/",
        "-vec", "-vs", "32", "-double"}));

    factory.fOptions = {"-single", "-opt", "4"};
    factory.default_compile_options();
    assert(factory.fSampleFormat == faustgen_factory::kFloat);
    assert(factory.fOptLevel == 4);
    assert(find(factory.fCompileOptions.begin(), factory.fCompileOptions.end(), "-single")
           != factory.fCompileOptions.end());
    assert(find(factory.fCompileOptions.begin(), factory.fCompileOptions.end(), "-double")
           == factory.fCompileOptions.end());

    // Removing -opt restores the documented maximum/default optimization.
    factory.fOptions = {"-double"};
    factory.default_compile_options();
    assert(factory.fOptLevel == LLVM_OPTIMIZATION);
    assert(factory.fSampleFormat == faustgen_factory::kDouble);

    // A malformed trailing -opt must not dereference fOptions.end().
    factory.fOptions = {"-opt"};
    factory.default_compile_options();
    assert(factory.fOptLevel == LLVM_OPTIMIZATION);
    assert(factory.fSampleFormat == faustgen_factory::kDouble);

    // Buffer release is idempotent and always restores the size/pointer invariant.
    factory.fSourceCode = sysmem_newhandleclear(4);
    factory.fSourceCodeSize = 3;
    factory.free_sourcecode();
    factory.free_sourcecode();
    assert(!factory.fSourceCode && factory.fSourceCodeSize == 0);
    factory.fBitCodeSize = 99;
    factory.free_bitcode();
    assert(!factory.fBitCode && factory.fBitCodeSize == 0);
    factory.fBitCode = sysmem_newhandleclear(4);
    factory.fBitCodeSize = 3;
    factory.free_bitcode();
    factory.free_bitcode();
    assert(!factory.fBitCode && factory.fBitCodeSize == 0);

    // Installing default source replaces any previous allocation without leaking it.
    factory.fSourceCode = sysmem_newhandleclear(4);
    factory.fSourceCodeSize = 3;
    int frees_before_default = frees;
    factory.default_source_code();
    assert(frees == frees_before_default + 1);
    assert(string(*factory.fSourceCode) == DEFAULT_SOURCE_CODE);
    assert(factory.fSourceCodeSize == long(strlen(DEFAULT_SOURCE_CODE)));

    // An unchanged edit is a no-op. A changed edit drops caches and updates all clients.
    faustgen first, second;
    factory.fInstances = {&first, &second};
    factory.fCompileOptions = {"-double", "-I", "/library/"};
    factory.fBitCode = sysmem_newhandleclear(7);
    strcpy(*factory.fBitCode, "cache");
    factory.fBitCodeSize = 5;
    string unchanged = DEFAULT_SOURCE_CODE;
    int factory_frees_before = factory.factory_frees;
    factory.update_sourcecode(static_cast<int>(unchanged.size()), &unchanged[0]);
    assert(factory.factory_frees == factory_frees_before);
    assert(first.updates == 0 && second.updates == 0);

    string replacement = u8"process = _ * 0.5; // été";
    factory.update_sourcecode(static_cast<int>(replacement.size()), &replacement[0]);
    assert(factory.factory_frees == factory_frees_before + 1);
    assert(!factory.fBitCode && factory.fBitCodeSize == 0);
    assert(string(*factory.fSourceCode) == replacement);
    assert(factory.fSourceCodeSize == long(replacement.size()));
    assert((generated_arguments == vector<string>{
        "-double", "-I", "/library/", "-lang", "codebox", "-o", "string"}));
    assert(first.updates == 1 && second.updates == 1);
    assert(first.last_codebox == "compiled-codebox");

    // librarypath clears custom paths but retains the bundled resource directory.
    factory.fResourcePath = "/bundle/";
    factory.librarypath(0, gensym(""));
    assert((factory.fLibraryPath == set<string>{"/bundle/"}));
    factory.librarypath(0, gensym("/custom/lib/filter.lib"));
    assert(factory.fLibraryPath.count("/custom/lib/filter.lib"));

    // Compiler option parsing accepts symbols/integers, rejects floats, and honors nc.
    first.updates = second.updates = 0;
    t_atom no_compile[] = {make_symbol("-vec"), make_long(8), make_float(1.5),
                           make_symbol("nc")};
    factory_frees_before = factory.factory_frees;
    factory.compileoptions(0, gensym("compileoptions"), 4, no_compile);
    assert((factory.fOptions == vector<string>{"-vec", "8"}));
    assert(factory.factory_frees == factory_frees_before);
    assert(first.updates == 0 && second.updates == 0);

    t_atom compile[] = {make_symbol("-sch"), make_long(2)};
    factory.fBitCode = sysmem_newhandleclear(6);
    factory.fBitCodeSize = 5;
    factory.compileoptions(0, gensym("compileoptions"), 2, compile);
    assert((factory.fOptions == vector<string>{"-sch", "2"}));
    assert(factory.factory_frees == factory_frees_before + 1);
    assert(!factory.fBitCode && factory.fBitCodeSize == 0);
    assert(first.updates == 1 && second.updates == 1);

    factory.free_sourcecode();
    assert(allocations == frees);
    cout << "factory helpers, options, buffers, edits, and messages: OK\n";
}
'''


class FactoryCoreTest(unittest.TestCase):
    def test_factory_core_behaviour(self):
        source = FACTORY_SOURCE.read_text()
        helpers = definitions(
            source,
            (
                "static string getFolderFromFilename",
                "static string getFolderFromPath",
                "static bool isSafePathSegment",
            ),
        )
        methods = definitions(
            source,
            (
                "void faustgen_factory::free_sourcecode",
                "void faustgen_factory::free_bitcode",
                "void faustgen_factory::add_library_path",
                "void faustgen_factory::add_compile_option(const string& key",
                "void faustgen_factory::add_compile_option(const string& value",
                "void faustgen_factory::default_compile_options",
                "void faustgen_factory::default_source_code",
                "void faustgen_factory::update_sourcecode",
                "void faustgen_factory::librarypath",
                "void faustgen_factory::compileoptions",
            ),
        )
        with tempfile.TemporaryDirectory(prefix="faustgen-factory-core-") as temporary:
            compile_and_run(STUBS + helpers + methods + CASES, temporary, "factory-core")


if __name__ == "__main__":
    unittest.main()
