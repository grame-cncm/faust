"""Tests for the disk cache of compiled code (faustgen_cache.cpp) and its use by the factory.

The real faustgen_cache.cpp is compiled with a stand-in for libfaust's generateSHA1, with the
cache directory in a temporary folder (FAUSTGEN_CACHE_DIR). The factory methods computing the
cache key and moving the code between the factory and the cache are extracted from the
sources, with stand-ins for Max and libfaust.
"""

import os
from pathlib import Path
import shutil
import tempfile
import unittest

from cpp_test_support import FACTORY_SOURCE, ROOT, compile_and_run, definitions

CACHE_SOURCE = ROOT / "src/faustgen_cache.cpp"
CACHE_HEADER = ROOT / "src/faustgen_cache.h"

STUBS = r'''
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <utime.h>
#include <dirent.h>
using namespace std;

// Stand-in for libfaust's generateSHA1: any digest of the whole data (40 hex digits)
string generateSHA1(const string& data) {
    unsigned long long a = 1469598103934665603ULL, b = 1099511628211ULL;
    for (unsigned char c : data) { a = (a ^ c) * 1099511628211ULL; b = (b + c) * 6364136223846793005ULL + 1; }
    char text[41];
    snprintf(text, sizeof(text), "%016llx%016llx%08llx", a, b, (a ^ b) & 0xffffffffULL);
    return text;
}
'''

FACTORY_STUBS = r'''
#define FAUSTGEN_VERSION "test-version"
#define LLVM_OPTIMIZATION -1
using t_atom_long = long;
vector<string> posts;
void post(const char* format, ...) { posts.push_back(format); }
char** sysmem_newhandleclear(long size) {
    auto handle = static_cast<char**>(malloc(sizeof(char*)));
    *handle = static_cast<char*>(calloc(size, 1)); return handle;
}
void sysmem_freehandle(char** handle) { free(*handle); free(handle); }
void sysmem_copyptr(const char* source, char* target, long size) { memcpy(target, source, size); }
string getSerialNumber() { return "test-machine"; }
string getTarget() { return "test-target"; }
const char* getCLibFaustVersion() { return "test-libfaust"; }
struct dsp_factory {
    string code;
    vector<string> libraries;
    vector<string> getLibraryList() { return libraries; }
};
using llvm_dsp_factory = dsp_factory;
using interpreter_dsp_factory = dsp_factory;
string writeDSPFactoryToMachine(llvm_dsp_factory* factory, const string&) { return factory->code; }
string writeInterpreterDSPFactoryToBitcode(interpreter_dsp_factory* factory) { return factory->code; }

class faustgen_factory {
public:
    enum sampleFormat { kFloat, kDouble, kNone };
    long fSourceCodeSize = 0, fBitCodeSize = 0;
    char** fSourceCode = nullptr;
    char** fBitCode = nullptr;
    dsp_factory* fDSPfactory = nullptr;
    set<string> fLibraryPath;
    vector<string> fOptions;
    sampleFormat fSampleFormat = kNone;
    int compile_options_builds = 0;
    ~faustgen_factory() { free_bitcode(); if (fSourceCode) sysmem_freehandle(fSourceCode); }
    void set_source(const string& source) {
        if (fSourceCode) sysmem_freehandle(fSourceCode);
        fSourceCodeSize = long(source.size());
        fSourceCode = sysmem_newhandleclear(fSourceCodeSize + 1);
        memcpy(*fSourceCode, source.c_str(), source.size());
    }
    char* get_sourcecode() { static char empty = 0; return fSourceCode ? *fSourceCode : &empty; }
    void free_bitcode() { if (fBitCode) sysmem_freehandle(fBitCode); fBitCode = nullptr; fBitCodeSize = 0; }
    // The sample format of the options, as default_compile_options does
    void default_compile_options() {
        ++compile_options_builds;
        fSampleFormat = (find(fOptions.begin(), fOptions.end(), "-single") != fOptions.end()) ? kFloat : kDouble;
    }
    string cache_key();
    bool restore_from_cache();
    void save_to_cache();
};
'''

CASES = r'''
static string temporary_dir;

static void write_text(const string& path, const string& text) { ofstream(path.c_str(), ios::binary) << text; }
static string read_text(const string& path) {
    ifstream in(path.c_str(), ios::binary); stringstream s; s << in.rdbuf(); return s.str();
}
static bool exists(const string& path) { struct stat info; return stat(path.c_str(), &info) == 0; }
static vector<string> files_in(const string& dir) {
    vector<string> names;
    if (DIR* d = opendir(dir.c_str())) {
        while (dirent* e = readdir(d)) if (e->d_name[0] != '.') names.push_back(e->d_name);
        closedir(d);
    }
    return names;
}
// Date an entry in the past, as if used long ago
static void age(const string& path, long seconds) {
    struct utimbuf times; times.actime = times.modtime = time(nullptr) - seconds; utime(path.c_str(), &times);
}

int main() {
    temporary_dir = getenv("TEST_DIR");
    // A cache directory and its missing parents are created
    string root = temporary_dir + "/a/b/cache";
    setenv("FAUSTGEN_CACHE_DIR", (root + "/").c_str(), 1);
    unsetenv("FAUSTGEN_CACHE_SIZE");
    string dir = faustgen_cache::directory();
    assert(dir == root + "/" && exists(root));

    string libs = temporary_dir + "/libs";
    mkdir(libs.c_str(), 0755);
    string stdfaust = libs + "/stdfaust.lib", filters = libs + "/filters with space.lib";
    write_text(stdfaust, "import(\"filters.lib\");");
    write_text(filters, "lowpass = _;");
    string key = generateSHA1("program p2"), other = generateSHA1("program p3");

    // Written then read back; nothing else is left in the directory
    string code;
    assert(!faustgen_cache::read(key, code));
    assert(faustgen_cache::write(key, "machine code\nof p2", {stdfaust, filters}));
    assert(faustgen_cache::read(key, code) && code == "machine code\nof p2");
    assert(files_in(root) == vector<string>{key + ".fgcache"});
    assert(!faustgen_cache::read(other, code));
    // A key that is not a plain name is refused
    assert(!faustgen_cache::write("../outside", "x", {}) && !exists(temporary_dir + "/a/b/outside.fgcache"));
    assert(!faustgen_cache::read("../outside", code));
    // Written again: replaced
    assert(faustgen_cache::write(key, "new code of p2", {stdfaust, filters}));
    assert(faustgen_cache::read(key, code) && code == "new code of p2");

    // A library changed or removed makes the entry stale: refused and removed
    write_text(filters, "lowpass = _ : *(0.5);");
    assert(!faustgen_cache::read(key, code) && !exists(dir + key + ".fgcache"));
    assert(faustgen_cache::write(key, "code of p2", {stdfaust, filters}));
    remove(filters.c_str());
    assert(!faustgen_cache::read(key, code) && !exists(dir + key + ".fgcache"));
    // Code compiled with a library that cannot be read is not stored
    assert(!faustgen_cache::write(key, "code of p2", {stdfaust, filters}) && !exists(dir + key + ".fgcache"));
    write_text(filters, "lowpass = _;");

    // A damaged entry (truncated, other format) is refused and removed
    assert(faustgen_cache::write(key, "0123456789", {stdfaust}));
    string entry = dir + key + ".fgcache";
    string text = read_text(entry);
    write_text(entry, text.substr(0, text.size() - 3));
    assert(!faustgen_cache::read(key, code) && !exists(entry));
    write_text(entry, "faustgen~ cache 0\nmachinecode 1\nx");
    assert(!faustgen_cache::read(key, code) && !exists(entry));
    write_text(entry, text + "more");
    assert(!faustgen_cache::read(key, code) && !exists(entry));

    // Bounded size: the entries used least recently go first, a read counts as a use
    string big(1000, 'm');
    vector<string> keys;
    for (int i = 0; i < 4; ++i) {
        keys.push_back(generateSHA1("entry " + to_string(i)));
        assert(faustgen_cache::write(keys[i], big, {stdfaust}));
        age(dir + keys[i] + ".fgcache", 1000 - 100 * i);   // entry 0 is the oldest
    }
    assert(faustgen_cache::read(keys[0], code));            // entry 0 used now
    struct stat info;
    stat((dir + keys[0] + ".fgcache").c_str(), &info);
    setenv("FAUSTGEN_CACHE_SIZE", to_string(3 * info.st_size + info.st_size / 2).c_str(), 1);  // room for 3 entries
    string fifth = generateSHA1("entry 4");
    assert(faustgen_cache::write(fifth, big, {stdfaust}));
    assert(exists(dir + keys[0] + ".fgcache") && exists(dir + fifth + ".fgcache"));
    assert(!exists(dir + keys[1] + ".fgcache") && !exists(dir + keys[2] + ".fgcache"));
    assert(exists(dir + keys[3] + ".fgcache"));
    unsetenv("FAUSTGEN_CACHE_SIZE");

    // Cleared: every entry removed, and counted
    int entries = int(files_in(root).size());
    assert(faustgen_cache::clear() == entries && files_in(root).empty());
    cout << "cache entries written, read, refused when stale or damaged, bounded and cleared: OK\n";

    // The factory: the code compiled with some options is found again with the same source,
    // options and library paths, and only then; the sample format follows the options.
    auto factory_with = [&](const string& source, vector<string> options, set<string> paths) {
        faustgen_factory* f = new faustgen_factory();
        f->set_source(source);
        f->fOptions = options;
        f->fLibraryPath = paths;
        return f;
    };
    const string program = "import(\"stdfaust.lib\");\np2 = _ <: _,_;\np3 = _ <: _,_,_;";
    dsp_factory compiled_p2{"machine code of p2", {stdfaust}};
    {
        faustgen_factory* f = factory_with(program, {"--process-name", "p2"}, {libs});
        assert(!f->restore_from_cache() && !f->fBitCode);
        f->fDSPfactory = &compiled_p2;
        f->save_to_cache();
        delete f;
    }
    {
        faustgen_factory* f = factory_with(program, {"--process-name", "p2"}, {libs});
        f->fSampleFormat = faustgen_factory::kNone;
        assert(f->restore_from_cache());
        assert(string(*f->fBitCode) == "machine code of p2" && f->fBitCodeSize == long(compiled_p2.code.size()));
        assert(f->fSampleFormat == faustgen_factory::kDouble);
        delete f;
    }
    for (int change = 0; change < 5; ++change) {
        faustgen_factory* f = factory_with(program, {"--process-name", "p2"}, {libs});
        if (change == 0) f->fOptions = {"--process-name", "p3"};
        if (change == 1) f->fOptions = {"-pn", "p2"};            // other options, same DSP: another entry
        if (change == 2) f->set_source(program + "\n");
        if (change == 3) f->fLibraryPath = {libs, "/other/libraries/"};
        if (change == 4) f->fOptions = {"--process-name", "p2", "-single"};
        assert(!f->restore_from_cache() && !f->fBitCode);
        delete f;
    }
    // A field cannot be confused with the next ones: the options 'ab' and 'a', 'b' differ,
    // and so do an option and a library path
    {
        faustgen_factory* one = factory_with(program, {"ab"}, {});
        faustgen_factory* two = factory_with(program, {"a", "b"}, {});
        faustgen_factory* three = factory_with(program, {}, {"ab"});
        assert(one->cache_key() != two->cache_key() && one->cache_key() != three->cache_key());
        delete one; delete two; delete three;
    }
    // A library of the DSP changed since: compiled again
    write_text(stdfaust, "import(\"filters.lib\"); // changed");
    {
        faustgen_factory* f = factory_with(program, {"--process-name", "p2"}, {libs});
        assert(!f->restore_from_cache());
        delete f;
    }
    // A cache that cannot be written is reported, nothing else
    setenv("FAUSTGEN_CACHE_DIR", (stdfaust + "/cache").c_str(), 1);   // below a file: cannot be created
    {
        faustgen_factory* f = factory_with(program, {"--process-name", "p2"}, {libs});
        assert(!f->restore_from_cache());
        size_t before = posts.size();
        f->fDSPfactory = &compiled_p2;
        f->save_to_cache();
        assert(posts.size() == before + 1);
        delete f;
    }
    cout << "factory cache key, restore and save: OK\n";
}
'''


class CacheTest(unittest.TestCase):
    def test_disk_cache(self):
        cache = (CACHE_SOURCE.read_text()
                 .replace("#include <faust/dsp/libfaust.h>  // generateSHA1", "")
                 .replace("#include \"faustgen_cache.h\"", CACHE_HEADER.read_text()))
        methods = definitions(
            FACTORY_SOURCE.read_text(),
            (
                "string faustgen_factory::cache_key",
                "bool faustgen_factory::restore_from_cache",
                "void faustgen_factory::save_to_cache",
            ),
        )
        with tempfile.TemporaryDirectory(prefix="faustgen-cache-test-") as temporary:
            os.environ["TEST_DIR"] = temporary
            for flags in ((), ("-DINTERP_BACKEND",)):
                with self.subTest(backend=flags or ("LLVM",)):
                    # each backend starts with an empty cache and fresh libraries
                    for name in ("a", "libs"):
                        shutil.rmtree(Path(temporary) / name, ignore_errors=True)
                    compile_and_run(
                        STUBS + cache + FACTORY_STUBS + methods + CASES,
                        temporary,
                        name="cache-test",
                        flags=flags,
                    )


if __name__ == "__main__":
    unittest.main()
