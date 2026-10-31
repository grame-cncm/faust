/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This file is part of faustprobe, the offline probe of a Faust program.
 It is distributed under the same license as the Faust tools: see
 COPYING.txt at the root of the repository.
 ************************************************************************/

// --svg DIR: the block diagrams of the program, written into DIR, and the
// index of what was written on stdout. Draw-only: nothing is rendered.
//
// The drawing is the compiler's own (-svg, through generateAuxFiles), in a
// directory of its own inside DIR. Two things differ from faust -svg:
//
// - the files land in DIR itself, never next to the source;
// - a folded sub-diagram is named by its definition, feedbackNetwork.svg, then
//   feedbackNetwork-2.svg for a second distinct diagram of that name, in the
//   order the root's links reach them, rather than by a number that changes
//   with the compiler's state: the same input gives the same files.

#include <unistd.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <map>
#include <set>
#include <sstream>

#include "faust/dsp/libfaust.h"

#include "report.h"

namespace fs = std::filesystem;

// One drawing.
struct Diagram {
    std::string file;   // its name in the compiler's directory, then in DIR
    std::string name;   // its title
    std::string text;
};

// The bytes of a drawing.
static std::string readFile(const fs::path& path)
{
    std::ifstream     stream(path, std::ios::binary);
    std::stringstream text;
    text << stream.rdbuf();
    return text.str();
}

// A text as an SVG holds it.
static std::string xmlEscape(const std::string& text)
{
    return replaceAll(replaceAll(replaceAll(replaceAll(text, "&", "&amp;"), "<", "&lt;"), ">", "&gt;"), "\"", "&quot;");
}

// The files a drawing links to, in order.
static std::vector<std::string> linksOf(const std::string& svg)
{
    const std::string        marker = "xlink:href=\"";
    std::vector<std::string> links;
    for (size_t at = svg.find(marker); at != std::string::npos; at = svg.find(marker, at + 1)) {
        size_t      from = at + marker.size();
        std::string link = svg.substr(from, svg.find('"', from) - from);
        if (std::find(links.begin(), links.end(), link) == links.end()) {
            links.push_back(link);
        }
    }
    return links;
}

// 'stage-22766.svg' is 'stage': the number is the compiler's.
static std::string baseOf(const std::string& file)
{
    std::string base = stemOf(file);
    size_t      dash = base.rfind('-');
    if (dash != std::string::npos && dash > 0 &&
        base.find_first_not_of("0123456789", dash + 1) == std::string::npos && dash + 1 < base.size()) {
        base = base.substr(0, dash);
    }
    return replaceAll(base, "__faustprobe_eval", "eval");
}

// The options of the drawing, as faust spells them.
static std::vector<std::string> drawArgv(const Args& args, const std::string& directory)
{
    // the -o is the compiler's generated code, which would otherwise go to stdout
    std::vector<std::string> argv = {"-svg", "-O", directory, "-o", "faustprobe-unused.cpp"};
    for (const std::string& dir : args.importDirs) {
        argv.push_back("-I");
        argv.push_back(dir);
    }
    argv.push_back("-I");
    argv.push_back(directoryOf(args.file));
    if (args.compile.isDouble) {
        argv.push_back("-double");
    }
    for (const std::string& value : args.compile.argv()) {
        argv.push_back(value);
    }
    auto number = [&argv](const char* flag, const Optional<size_t>& value) {
        if (value) {
            argv.push_back(flag);
            argv.push_back(str(*value));
        }
    };
    number("-f", args.fold);
    number("-fc", args.foldComplexity);
    number("-mns", args.maxNameSize);
    auto word = [&argv](const char* flag, bool given) {
        if (given) {
            argv.push_back(flag);
        }
    };
    word("-sd", args.simplifyDiagrams);
    word("-sc", args.scaledSvg);
    word("-blur", args.shadowBlur);
    word("-drf", args.drawRouteFrame);
    return argv;
}

// Draws into a work directory inside DIR, reads the drawings back, renames them and
// rewrites their links, then writes them into DIR. The work directory is removed
// whether or not the drawing succeeded.
void runSvg(const Args& args)
{
    if (args.format == Format::Ir) {
        throw Failure("--svg prints an index, as CSV or with --format json; not as .ir");
    }
    std::shared_ptr<EvalProgram> eval;
    if (!args.evals.empty()) {
        eval = std::make_shared<EvalProgram>(readTextFile(args.file), args.evals);
    }
    const std::string& dir = *args.svg;
    std::error_code    code;
    fs::create_directories(dir, code);
    if (code) {
        throw Failure("cannot create '" + dir + "': " + code.message());
    }
    fs::path work = fs::path(dir) / (".faustprobe-" + std::to_string(getpid()));
    fs::create_directories(work);

    std::vector<Diagram> diagrams;
    try {
        std::vector<std::string> storage = drawArgv(args, work.string());
        std::vector<const char*> argv;
        for (const std::string& word : storage) {
            argv.push_back(word.c_str());
        }
        std::string error;
        std::string name = stemOf(args.file);
        bool        drawn;
        if (eval != nullptr) {
            drawn = generateAuxFilesFromString(name, eval->source(), static_cast<int>(argv.size()), argv.data(), error);
        } else {
            drawn = generateAuxFilesFromFile(args.file, static_cast<int>(argv.size()), argv.data(), error);
        }
        if (!drawn) {
            throw Failure(eval != nullptr ? eval->explain(name, trim(error)) : trim(error));
        }
        fs::path drawing;
        for (const auto& entry : fs::directory_iterator(work)) {
            if (entry.is_directory()) {
                drawing = entry.path();
            }
        }
        // named process.svg, or after the definition -pn chose
        std::string root = fs::exists(drawing / "process.svg") ? "process.svg" : args.compile.processName + ".svg";
        if (drawing.empty()) {
            throw Failure("the compiler drew nothing for '" + args.file + "'");
        }

        // the root first, then what its links reach, depth first
        std::map<std::string, std::string> texts;
        for (const auto& entry : fs::directory_iterator(drawing)) {
            texts[entry.path().filename().string()] = readFile(entry.path());
        }
        if (texts.count(root) == 0) {
            // some versions name the root after its definition and a number
            root.clear();
            for (const auto& entry : texts) {
                if (root.empty() && baseOf(entry.first) == args.compile.processName) {
                    root = entry.first;
                }
            }
            if (root.empty()) {
                throw Failure("the compiler drew nothing for '" + args.file + "'");
            }
        }
        std::vector<std::string> order, pending = {root};
        std::set<std::string>    seen;
        while (!pending.empty()) {
            std::string file = pending.back();
            pending.pop_back();
            if (!seen.insert(file).second || texts.count(file) == 0) {
                continue;
            }
            order.push_back(file);
            std::vector<std::string> links = linksOf(texts[file]);
            pending.insert(pending.end(), links.rbegin(), links.rend());
        }
        for (const auto& entry : texts) {
            if (seen.insert(entry.first).second) {
                order.push_back(entry.first);
            }
        }

        // stable names, compared without case: a case-insensitive file system
        // would otherwise merge two diagrams
        std::string                   rootFile = (eval != nullptr ? "process" : args.compile.processName) + ".svg";
        std::map<std::string, std::string> renamed;
        std::map<std::string, size_t> taken;
        for (const std::string& file : order) {
            if (file == root) {
                renamed[file] = rootFile;
                taken[lower(stemOf(rootFile))]++;
                continue;
            }
            std::string base  = baseOf(file);
            size_t      count = ++taken[lower(base)];
            renamed[file]     = count == 1 ? base + ".svg" : base + "-" + str(count) + ".svg";
        }
        for (const std::string& file : order) {
            Diagram diagram;
            diagram.file = renamed[file];
            diagram.text = texts[file];
            for (const auto& entry : renamed) {
                diagram.text =
                    replaceAll(diagram.text, "href=\"" + entry.first + "\"", "href=\"" + entry.second + "\"");
            }
            diagram.name = baseOf(file);
            if (file == root) {
                diagram.name = stemOf(rootFile);
                if (eval != nullptr) {
                    diagram.name = join(eval->exprs(), ", ");
                    // the root is titled with the expressions
                    size_t empty = diagram.text.find("></text>");
                    if (empty != std::string::npos) {
                        diagram.text.insert(empty + 1, xmlEscape(diagram.name));
                    }
                }
            } else if (eval != nullptr) {
                diagram.name = eval->renameMembers(replaceAll(diagram.name, "eval", "__faustprobe_eval"));
            }
            if (eval != nullptr) {
                diagram.text = eval->renameMembers(diagram.text);
            }
            diagrams.push_back(diagram);
        }
    } catch (...) {
        fs::remove_all(work, code);
        throw;
    }
    fs::remove_all(work, code);

    for (const Diagram& diagram : diagrams) {
        fs::path      path = fs::path(dir) / diagram.file;
        std::ofstream stream(path, std::ios::binary);
        stream << diagram.text;
        if (!stream) {
            throw Failure("cannot write '" + path.string() + "'");
        }
    }

    if (args.format == Format::Json) {
        Json document = Json::object().set("schema_version", 1).set("dsp", args.file).set("svg_dir", dir);
        if (eval != nullptr) {
            document.set("eval", Json::strings(eval->exprs()));
        }
        Json entries = Json::array();
        for (const Diagram& diagram : diagrams) {
            entries.push(Json::object().set("file", diagram.file).set("name", diagram.name));
        }
        document.set("diagrams", entries);
        printJson(document);
        return;
    }
    writeLine("file,name");
    for (const Diagram& diagram : diagrams) {
        writeLine(diagram.file + "," + csvFieldWithBreaks(diagram.name));
    }
}
