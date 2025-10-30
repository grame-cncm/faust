// FileResolver regression suite ---------------------------------------------------------------
// This executable focuses on the small but critical C++17 filesystem shim that backs the Faust
// parser. The resolver is responsible for canonicalising search directories, normalising import
// paths, and exposing deterministic answers even when users provide malformed strings or URL-style
// hints. Subsystems ranging from SourceReader to architecture loaders rely on these guarantees.
//
// Coverage checklist:
//  - canonicalisation: confirm duplicate directories and redundant path components are eliminated;
//  - positive lookups: relative, normalised, absolute, and direct filesystem paths resolve to the
//    same canonical answer;
//  - architecture parity: architecture lookups behave exactly like imports;
//  - failure behaviour: missing files, invalid schemes, nonexistent absolute paths, and directories
//    supplied instead of files must quietly return std::nullopt rather than throwing;
//  - helper utilities: legacy basename/dirname helpers and canonical directory lists stay aligned
//    with the primary resolver logic.
//
// Each test case below documents the specific behaviour under scrutiny so any regression surfaces
// with minimal debugging effort.

#include <cassert>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "parser/enrobage.hh"
#include "parser/fileresolver.hh"

namespace fs = std::filesystem;
using faust::parser::FileResolver;

namespace {

// Resolve the tests directory starting at this source file.
fs::path resolveTestsRoot()
{
    auto here = fs::weakly_canonical(fs::path(__FILE__));
    return here.parent_path().parent_path();  // compiler/tests
}

// Resolve the fixtures directory shared across test cases.
fs::path fixturesRoot()
{
    return resolveTestsRoot() / "parser" / "fixtures";
}

// Ensure directories are deduplicated and canonicalised during registration.
void testDirectoryRegistration()
{
    FileResolver resolver;
    auto         fixtures = fixturesRoot();

    resolver.addImportDirectory(fixtures);        // canonical path
    resolver.addImportDirectory(fixtures / ".");  // duplicate after normalization should be ignored
    resolver.addArchitectureDirectory(fixtures / "arch");

    auto expectedFixtures = fs::weakly_canonical(fixtures);
    auto expectedArch     = fs::weakly_canonical(fixtures / "arch");

    assert(resolver.importDirectories().size() == 1);
    assert(resolver.importDirectories().front() == expectedFixtures);

    assert(resolver.architectureDirectories().size() == 1);
    assert(resolver.architectureDirectories().front() == expectedArch);
}

// Validate import resolution for relative, normalised, absolute, and direct path inputs.
void testImportResolution()
{
    FileResolver resolver;
    auto         fixtures = fixturesRoot();

    resolver.addImportDirectory(fixtures);

    const auto expected = fs::weakly_canonical(fixtures / "simple" / "main.dsp");

    auto relative = resolver.resolveImport("simple/main.dsp");
    assert(relative && *relative == expected);

    auto normalizedRelative = resolver.resolveImport("simple/../simple/main.dsp");
    assert(normalizedRelative && *normalizedRelative == expected);

    auto absolute = resolver.resolveImport(expected);
    assert(absolute && *absolute == expected);

    auto direct = resolver.resolveImport(fixtures / "simple" / "main.dsp");
    assert(direct && *direct == expected);
}

// Validate architecture resolution parallels the import resolution behaviour.
void testArchitectureResolution()
{
    FileResolver resolver;
    auto         fixtures = fixturesRoot();

    resolver.addArchitectureDirectory(fixtures / "arch");

    const auto expected = fs::weakly_canonical(fixtures / "arch" / "minimal.arch");

    auto resolved = resolver.resolveArchitecture("minimal.arch");
    assert(resolved && *resolved == expected);
}

// Confirm missing files, bad schemes, absolute misses, and directories all yield std::nullopt.
void testResolutionFailures()
{
    FileResolver resolver;
    auto         fixtures = fixturesRoot();
    resolver.addImportDirectory(fixtures);

    auto missing = resolver.resolveImport("simple/nope.dsp");
    assert(!missing);

    auto url = resolver.resolveImport("http://example.com/foo.dsp");
    assert(!url);

    auto bogusAbsolute = resolver.resolveImport(fixtures / "missing.dsp");
    assert(!bogusAbsolute);

    auto directoryPath = resolver.resolveImport(fixtures / "simple");
    assert(!directoryPath);
}

// Confirm legacy basename/dirname helpers keep returning canonicalised values.
void testPathUtilities()
{
    auto fixtures = fixturesRoot();
    auto sample   = (fixtures / "simple" / "main.dsp").string();

    auto base = fileBasename(sample);
    assert(base == "main.dsp");

    auto dir = fileDirname(sample);
    assert(fs::path(dir) == fixtures / "simple");
}

// Exercise canonical directory string helpers and duplicate suppression.
void testDirectoryHelpers()
{
    std::vector<std::string> dirs;
    auto                     fixtures = fixturesRoot();

    faust::parser::appendUniqueDirectory(dirs, fixtures / "simple" / ".." / "simple");
    assert(dirs.size() == 1);

    auto expected = faust::parser::canonicalDirectoryString(fixtures / "simple");
    assert(dirs.front() == expected);

    faust::parser::appendUniqueDirectory(dirs, fixtures / "simple");
    assert(dirs.size() == 1);
}

}  // namespace

int main()
{
    // Report fixtures path for debugging and execute the scoped tests.
    std::cout << "[parser-tests] Using fixtures rooted at " << resolveTestsRoot() << '\n';
    testDirectoryRegistration();
    testImportResolution();
    testArchitectureResolution();
    testResolutionFailures();
    testPathUtilities();
    testDirectoryHelpers();
    std::cout << "[parser-tests] Completed FileResolver tests\n";
    return 0;
}
