"""Tests for shell-command construction and SVG/library actions."""

import tempfile
import unittest

from cpp_test_support import FACTORY_SOURCE, compile_and_run, definitions


STUBS = r'''
#include <cassert>
#include <cstdarg>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

#define FAUST_PDF_LIBRARY "library.pdf"
vector<string> posts;
void post(const char* format, ...) {
    char text[512];
    va_list arguments;
    va_start(arguments, format);
    vsnprintf(text, sizeof(text), format, arguments);
    va_end(arguments);
    posts.push_back(text);
}

vector<string> commands;
vector<int> command_results;
int test_system(const char* command) {
    commands.push_back(command);
    if (command_results.empty()) return 0;
    int result = command_results.front();
    command_results.erase(command_results.begin());
    return result;
}
#define system test_system

const char* TEXT_APPL_LIST[] = {
    "Visual\\ Studio\\ Code", "Atom", "Smultron", "TextWrangler", "TextExit", ""
};

struct dsp_factory {};
using llvm_dsp_factory = dsp_factory;
using interpreter_dsp_factory = dsp_factory;
int llvm_deletions = 0;
int interpreter_deletions = 0;
void deleteDSPFactory(llvm_dsp_factory* factory) { if (factory) ++llvm_deletions; delete factory; }
void deleteInterpreterDSPFactory(interpreter_dsp_factory* factory) {
    if (factory) ++interpreter_deletions;
    delete factory;
}

class faustgen_factory {
public:
    string fDrawPath;
    int fFaustNumber = 0;
    set<string> fLibraryPath;
    int source_compilations = 0;

    bool try_open_svg();
    void open_svg();
    void remove_svg();
    bool open_file(const char*);
    bool open_file(const char*, const char*);
    void display_svg();
    void display_documentation();
    void display_libraries_aux(const char*);
    void display_libraries();
    dsp_factory* create_factory_from_sourcecode() {
        ++source_compilations;
        return new dsp_factory();
    }
};
'''


CASES = r'''
int main() {
    faustgen_factory factory;
    factory.fFaustNumber = 7;
    factory.fDrawPath = "/tmp/faust draw/";

    assert(factory.try_open_svg());
#ifdef WIN32
    assert(commands.back() == "type \"file:////tmp/faust draw/faustgen-7-svg/process.svg\"");
#else
    assert(commands.back() == "open \"file:///tmp/faust draw/faustgen-7-svg/process.svg\"");
#endif
    size_t commands_before = commands.size();
    factory.fDrawPath = "/tmp/$unsafe/";
    assert(!factory.try_open_svg());
    factory.open_svg();
    factory.remove_svg();
    assert(commands.size() == commands_before);

    factory.fDrawPath = "/tmp/faust draw/";
    factory.open_svg();
#ifdef WIN32
    assert(commands.back() == "start \"\" \"file:////tmp/faust draw/faustgen-7-svg/process.svg\"");
#else
    assert(commands.back() == "open \"file:///tmp/faust draw/faustgen-7-svg/process.svg\"");
#endif
    factory.remove_svg();
#ifdef WIN32
    assert(commands.back() == "rmdir /S/Q \"/tmp/faust draw/faustgen-7-svg\"");
#else
    assert(commands.back() == "rm -r \"/tmp/faust draw/faustgen-7-svg\"");
#endif

    // Unsafe search paths are skipped; safe paths are tried until one succeeds.
    factory.fLibraryPath = {"/bad;/", "/good path/", "/other/"};
    command_results = {1, 0};
    commands_before = commands.size();
    assert(factory.open_file("filters.lib"));
    assert(commands.size() == commands_before + 2);
    assert(commands[commands_before].find("/bad;/") == string::npos);
    assert(commands[commands_before].find("/good path/filters.lib") != string::npos);
    assert(commands[commands_before + 1].find("/other/filters.lib") != string::npos);

    factory.fLibraryPath = {"/safe/"};
    command_results.clear();
    assert(factory.open_file("Atom", "maths.lib"));
#ifdef WIN32
    assert(commands.back() == "start \"\" Atom \"/safe/maths.lib\"");
#else
    assert(commands.back() == "open -a Atom \"/safe/maths.lib\"");
#endif

    factory.display_documentation();
    assert(commands.back().find("https://faustdoc.grame.fr/manual/introduction") != string::npos);

    // Existing SVGs open directly; missing ones trigger one temporary compilation.
    factory.fDrawPath = "/tmp/";
    command_results = {0};
    int compilations_before = factory.source_compilations;
    factory.display_svg();
    assert(factory.source_compilations == compilations_before);
    command_results = {1, 0};
    factory.display_svg();
    assert(factory.source_compilations == compilations_before + 1);
#ifdef INTERP_BACKEND
    assert(interpreter_deletions == 1 && llvm_deletions == 0);
#else
    assert(llvm_deletions == 1 && interpreter_deletions == 0);
#endif

    // The complete bundled library list is traversed, from all.lib to webaudio.lib.
    commands_before = commands.size();
    command_results.clear();
    factory.fLibraryPath = {"/bundle/"};
    factory.display_libraries();
    vector<string> library_commands(commands.begin() + commands_before, commands.end());
    assert(library_commands.size() >= 42);
    bool saw_all = false, saw_stdfaust = false, saw_webaudio = false;
    for (const auto& command : library_commands) {
        saw_all |= command.find("all.lib") != string::npos;
        saw_stdfaust |= command.find("stdfaust.lib") != string::npos;
        saw_webaudio |= command.find("webaudio.lib") != string::npos;
    }
    assert(saw_all && saw_stdfaust && saw_webaudio);

    cout << "safe commands, SVG lifecycle, documentation, and libraries: OK\n";
}
'''


class FactoryCommandsTest(unittest.TestCase):
    def test_commands_for_all_platform_and_backend_branches(self):
        source = FACTORY_SOURCE.read_text()
        code = definitions(
            source,
            (
                "static bool isSafePathSegment",
                "bool faustgen_factory::try_open_svg",
                "void faustgen_factory::open_svg",
                "void faustgen_factory::remove_svg",
                "void faustgen_factory::display_svg",
                "bool faustgen_factory::open_file(const char* file)",
                "bool faustgen_factory::open_file(const char* appl",
                "void faustgen_factory::display_documentation",
                "void faustgen_factory::display_libraries_aux",
                "void faustgen_factory::display_libraries()",
            ),
        )
        configurations = (
            ("unix-llvm", ()),
            ("unix-interpreter", ("-DINTERP_BACKEND",)),
            ("windows-llvm", ("-DWIN32",)),
            ("windows-interpreter", ("-DWIN32", "-DINTERP_BACKEND")),
        )
        with tempfile.TemporaryDirectory(prefix="faustgen-commands-") as temporary:
            for name, flags in configurations:
                with self.subTest(configuration=name):
                    compile_and_run(STUBS + code + CASES, temporary, name, flags)


if __name__ == "__main__":
    unittest.main()
