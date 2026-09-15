"""Tests for faustgen_factory file loading, change detection, and saving."""

import tempfile
import unittest

from cpp_test_support import FACTORY_SOURCE, compile_and_run, definitions


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
#define MAX_FILENAME_CHARS 256
#define TEXT_LB_UNIX 1
#define TEXT_NULL_TERMINATE 2
#define SYSFILE_FROMSTART 0
#define READ_PERM 1
#define WRITE_PERM 2
using t_max_err = int;
using t_fourcc = long;
using t_sysfile_text_flags = int;

struct t_symbol { string storage; const char* s_name; };
map<string, t_symbol> symbols;
t_symbol* gensym(const char* text) {
    auto result = symbols.emplace(text, t_symbol{text, nullptr}).first;
    result->second.s_name = result->second.storage.c_str();
    return &result->second;
}

vector<string> posts;
void post(const char* format, ...) {
    char text[512];
    va_list arguments;
    va_start(arguments, format);
    vsnprintf(text, sizeof(text), format, arguments);
    va_end(arguments);
    posts.push_back(text);
}

map<char**, long> handle_sizes;
char** sysmem_newhandle(long size) {
    char** handle = static_cast<char**>(malloc(sizeof(char*)));
    *handle = static_cast<char*>(calloc(static_cast<size_t>(max(1L, size)), 1));
    handle_sizes[handle] = size;
    return handle;
}
char** sysmem_newhandleclear(long size) { return sysmem_newhandle(size); }
void sysmem_freehandle(char** handle) {
    if (!handle) return;
    handle_sizes.erase(handle);
    free(*handle);
    free(handle);
}
long sysmem_handlesize(char** handle) { return handle_sizes.at(handle); }

struct FakeFile {
    string name;
    string content;
    bool read_error;
    bool write_error;
    int resets;
    FakeFile(string file_name, string file_content, bool cannot_read = false,
             bool cannot_write = false)
        : name(std::move(file_name)), content(std::move(file_content)),
          read_error(cannot_read), write_error(cannot_write), resets(0) {}
};
using t_filehandle = FakeFile*;

map<string, string> files;
set<string> read_failures;
set<string> write_failures;
set<string> open_failures;
set<string> create_failures;
int closes = 0;
int opens = 0;
int creates = 0;
int reads = 0;
int writes = 0;
bool dialog_cancel = false;
string dialog_name = "dialog.dsp";
bool path_name_failure = false;

t_max_err sysfile_readtextfile(t_filehandle file, char** handle, int, t_sysfile_text_flags) {
    ++reads;
    if (!file || file->read_error) return 1;
    free(*handle);
    *handle = static_cast<char*>(calloc(file->content.size() + 1, 1));
    memcpy(*handle, file->content.data(), file->content.size());
    handle_sizes[handle] = static_cast<long>(file->content.size() + 1);
    return 0;
}
void sysfile_setpos(t_filehandle file, int, int) { if (file) ++file->resets; }
t_max_err sysfile_writetextfile(t_filehandle file, char** handle, t_sysfile_text_flags) {
    ++writes;
    if (!file || file->write_error) return 1;
    file->content = *handle ? *handle : "";
    files[file->name] = file->content;
    return 0;
}
void sysfile_close(t_filehandle file) {
    assert(file);
    ++closes;
    delete file;
}

string generateSHA1(const char* text) { return text ? string(text) : string(); }

int open_dialog(char* name, short* path, t_fourcc*, t_fourcc*, int) {
    if (dialog_cancel) return 1;
    strcpy(name, dialog_name.c_str());
    *path = 7;
    return 0;
}
int saveas_dialog(char* name, short* path, void*) {
    if (dialog_cancel) return 1;
    strcpy(name, dialog_name.c_str());
    *path = 7;
    return 0;
}
void strncpy_zero(char* target, const char* source, long size) {
    strncpy(target, source, static_cast<size_t>(size));
    target[size - 1] = 0;
}
void path_setdefault(short, int) {}
int locatefile_extended(char* name, short* path, t_fourcc*, t_fourcc*, int) {
    *path = 7;
    return files.count(name) || open_failures.count(name) ? 0 : 1;
}
t_max_err path_opensysfile(char* name, short, t_filehandle* result, int permission) {
    ++opens;
    if (open_failures.count(name)) return 1;
    auto file = new FakeFile{name, files[name]};
    file->read_error = read_failures.count(name);
    file->write_error = permission == WRITE_PERM && write_failures.count(name);
    *result = file;
    return 0;
}
t_max_err path_createsysfile(char* name, short, long, t_filehandle* result) {
    ++creates;
    if (create_failures.count(name)) return 1;
    files[name] = "";
    *result = new FakeFile{name, ""};
    return 0;
}
t_max_err path_topathname(short, char* name, char* result) {
    if (path_name_failure) return 1;
    snprintf(result, MAX_FILENAME_CHARS, "/base/%s", name);
    return 0;
}

struct faustgen {
    int updates = 0;
    void update_sourcecode() { ++updates; }
};
struct dsp_factory {};

class faustgen_factory {
public:
    dsp_factory* fDSPfactory = nullptr;
    long fSourceCodeSize = 0;
    char** fSourceCode = nullptr;
    long fBitCodeSize = 0;
    char** fBitCode = nullptr;
    set<string> fLibraryPath;
    set<faustgen*> fInstances;
    short fDefaultPath = 11;
    int factory_frees = 0;

    void free_dsp_factory() { ++factory_frees; fDSPfactory = nullptr; }
    void free_bitcode();
    void add_library_path(const string& value) { fLibraryPath.insert(value); }
    char* get_sourcecode() {
        static char empty = 0;
        return fSourceCode ? *fSourceCode : &empty;
    }
    bool is_new(t_filehandle, char*);
    void compile_file(t_filehandle, short, char*);
    void read(long, t_symbol*);
    void write(long, t_symbol*);
};
'''


CASES = r'''
static void set_source(faustgen_factory& factory, const string& source) {
    if (factory.fSourceCode) sysmem_freehandle(factory.fSourceCode);
    factory.fSourceCode = sysmem_newhandleclear(static_cast<long>(source.size() + 1));
    memcpy(*factory.fSourceCode, source.data(), source.size());
    factory.fSourceCodeSize = static_cast<long>(source.size());
}

int main() {
    faustgen_factory factory;
    set_source(factory, "process = _;");

    // Change detection resets the file position and handles read errors safely.
    char same_name[] = "same.dsp";
    FakeFile same{same_name, "process = _;"};
    assert(!factory.is_new(&same, same_name));
    assert(same.resets == 1);
    char changed_name[] = "changed.dsp";
    FakeFile changed{changed_name, "process = _ * 2;"};
    assert(factory.is_new(&changed, changed_name));
    assert(changed.resets == 1);
    FakeFile unreadable{"bad.dsp", "ignored", true};
    char bad_name[] = "bad.dsp";
    assert(!factory.is_new(&unreadable, bad_name));
    assert(unreadable.resets == 1);

    // Dialog cancellation and lookup failure return without opening a handle.
    dialog_cancel = true;
    factory.read(0, gensym(""));
    assert(opens == 0 && closes == 0);
    dialog_cancel = false;
    factory.read(0, gensym("missing.dsp"));
    assert(opens == 0 && closes == 0);

    // Unchanged files are closed without recompilation.
    files["same.dsp"] = "process = _;";
    faustgen instance;
    factory.fInstances.insert(&instance);
    factory.read(0, gensym("same.dsp"));
    assert(opens == 1 && closes == 1);
    assert(factory.factory_frees == 0 && instance.updates == 0);

    // Changed files replace source/cache, add their folder, and update clients.
    files["changed.dsp"] = u8"process = _ * 2; // été";
    factory.fBitCode = sysmem_newhandleclear(6);
    strcpy(*factory.fBitCode, "cache");
    factory.fBitCodeSize = 5;
    factory.fDSPfactory = reinterpret_cast<dsp_factory*>(1);
    factory.read(0, gensym("changed.dsp"));
    assert(opens == 2 && closes == 2);
    assert(factory.factory_frees == 1 && instance.updates == 1);
    assert(!factory.fBitCode && factory.fBitCodeSize == 0);
    assert(string(factory.get_sourcecode()) == files["changed.dsp"]);
    assert(factory.fSourceCodeSize == long(files["changed.dsp"].size()));
    assert(factory.fLibraryPath.count("/base"));

    // An open failure never attempts to close an uninitialized handle.
    open_failures.insert("open-fails.dsp");
    int closes_before_failure = closes;
    factory.read(0, gensym("open-fails.dsp"));
    assert(closes == closes_before_failure);

    // Existing files are overwritten; missing files are created.
    set_source(factory, "process = 42;");
    files["existing.dsp"] = "old";
    factory.write(0, gensym("existing.dsp"));
    assert(files["existing.dsp"] == "process = 42;");
    assert(closes == closes_before_failure + 1);
    factory.write(0, gensym("created.dsp"));
    assert(files["created.dsp"] == "process = 42;");
    assert(creates == 1 && closes == closes_before_failure + 2);

    // Save-dialog cancellation and create errors leave no handles behind.
    dialog_cancel = true;
    factory.write(0, gensym(""));
    assert(closes == closes_before_failure + 2);
    dialog_cancel = false;
    create_failures.insert("cannot-create.dsp");
    factory.write(0, gensym("cannot-create.dsp"));
    assert(closes == closes_before_failure + 2);

    sysmem_freehandle(factory.fSourceCode);
    factory.fSourceCode = nullptr;
    assert(handle_sizes.empty());
    cout << "file change detection, read, compile, and write paths: OK\n";
}
'''


class FactoryFilesTest(unittest.TestCase):
    def test_file_operations(self):
        source = FACTORY_SOURCE.read_text()
        code = definitions(
            source,
            (
                "static string getFolderFromFilename",
                "void faustgen_factory::free_bitcode",
                "bool faustgen_factory::is_new",
                "void faustgen_factory::compile_file",
                "void faustgen_factory::read",
                "void faustgen_factory::write",
            ),
        )
        with tempfile.TemporaryDirectory(prefix="faustgen-files-") as temporary:
            compile_and_run(STUBS + code + CASES, temporary, "factory-files")


if __name__ == "__main__":
    unittest.main()
