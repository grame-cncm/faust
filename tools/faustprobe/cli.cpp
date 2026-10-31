/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This file is part of faustprobe, the offline probe of a Faust program.
 It is distributed under the same license as the Faust tools: see
 COPYING.txt at the root of the repository.
 ************************************************************************/

#include "cli.h"

#include <cstdio>
#include <cstdlib>
#include <functional>
#include <map>

#include "faust/dsp/llvm-dsp.h"

static const char* kHelp = R"(Probe a Faust DSP: set controls, render offline, report samples and statistics.

Usage: faustprobe [OPTIONS] <FILE>

  <FILE>                       Faust DSP source file (a .lib under --eval)

Program:
  --eval EXPR                  Evaluate EXPR in the scope of FILE and probe that
                               instead of FILE's process (repeatable: the outputs
                               side by side). FILE may be a .lib
  -I, --import-dir DIR         Add a Faust library import directory (repeatable)
  --opt-level N                LLVM optimisation level, -1 is the highest [default: 0]

Render:
  --sr HZ                      Sample rate [default: 44100]
  --block N                    Frames per compute call [default: 64]
  -n, --render N               Frames to render [default: 15000]
  --in MODE                    Input excitation: zero, impulse, impulse:CH, dc,
                               white[:SEED], sine:HZ, file:PATH[:CH] (.wav, .npy,
                               .f64, .f32) [default: impulse]
  --set PATH=VALUE             Set a control before rendering (repeatable). PATH is
                               an address or a trailing fragment of one
  --clamp                      Accept a value outside its control's range by
                               clamping it, and say so (an error otherwise)
  --at FRAME PATH=VALUE        Set a control at an exact frame (repeatable)
  --skip N                     Exclude the first N frames from dump and statistics
  --every N                    Print one frame out of N [default: 1]
  --fail-above LEVEL           Fail when a sample exceeds LEVEL in magnitude

Output:
  --quiet                      Print statistics only, no per-frame dump
  --format FORMAT              csv, ir (the impulse-test text) or json [default: csv]
  --precision N|full           Text of the numbers: `full`, the shortest that parses
                               back to the same float, or fixed decimals
  --out FILE                   Write the window to FILE (.npy, .wav, .f64, .f32) and
                               print the statistics only
  --list-params                List the controls and bargraphs and exit
  --bargraphs                  Add one column per bargraph to the rows
  --protocol NAME              free, or impulse-test: the reference protocol, and
                               the flags that would perturb it refused [default: free]
  --time                       Report what the compilation and compute calls cost

Comparison:
  --compare OTHER              Compare with OTHER, compiled and rendered alike;
                               exit status 1 beyond the tolerance
  --ref FILE                   Compare with the samples of FILE
  --set-a PATH=VALUE           --set for FILE only, under --compare (repeatable)
  --set-b PATH=VALUE           --set for OTHER only, under --compare (repeatable)
  --tolerance ABS              Largest accepted |a - b| (0, bit equality, by default)
  --rel-tolerance REL          Tolerance relative to the reference's peak
  --compare-outputs N,...      Outputs a comparison or a check looks at
  --check CHECK                Check an invariant (repeatable): block[=N1,N2,...],
                               reset, determinism, width, all

Sweeps and measures:
  --sweep PATH=V1,V2,...       Sweep a control (repeatable: cartesian product)
  --points FILE                Sweep the points of a CSV file
  --reduce R                   One number per output: rms, peak, energy, dc, f0,
                               sfdr, thd
  --f0 HZ                      Fundamental of --reduce sfdr / thd
  --describe LIST              loudness, attack, decay[:DB], sustain:A..B,
                               centroid[:A..B], width[:A..B]
  --describe-hop SECONDS       Envelope frame of --describe [default: 0.01]
  --describe-fft N             Transform length of centroid [default: 2048]

Polyphony:
  --nvoices N                  Polyphonic voice count; 0 renders the DSP directly
  --note PITCH[:VEL]@ON[..OFF] Play a note (repeatable)
  --chord P1,P2,...[:VEL]@ON[..OFF]  Play several pitches at once (repeatable)
  --effect FILE                Effect DSP, run on the voices' mix
  --voice-stop-level LEVEL     RMS below which a releasing voice is reclaimed
                               [default: 0.00003162]

Host loop of a program with loss and gradient lanes:
  --train CONTROLS             Train these controls, in the order of their lanes
  --loss-lane N                Output lane of the per-sample loss [default: 0]
  --grad-lane N                Output lane of the first gradient [default: 1]
  --optimizer NAME             adam or sgd [default: adam]
  --lr RATE                    Learning rate [default: 0.01]
  --blocks N                   Number of blocks, one step each [default: 100]
  --reset-per-block            Start every block from a cleared state
  --fd-check[=WHERE]           Check the gradient lanes against finite differences:
                               start (the default), end, both
  --fd-step H                  Step of the finite differences [default: 0.001]
  --fd-tolerance TOL           Largest accepted relative error [default: 0.02]
  --train-verbose              Add the block's mean gradients to the rows

Frequency response of a linear program:
  --freqresp N[:FMIN:FMAX]     N log-spaced frequencies, from one impulse response,
                               after checks that the program is linear
  --settle N                   Frames of silence before the impulse
  --linearity-tolerance REL    Largest accepted departure from linearity

Block diagrams:
  --svg DIR                    Draw the block diagrams into DIR, print an index, exit
  --fold N, -f N               Fold above this complexity; 0 is one file [default: 25]
  --fold-complexity N, -fc N   Smallest complexity worth a file [default: 2]
  --max-name-size N, -mns N    Longest label [default: 40]
  --simplify-diagrams, -sd     Draw constant sub-diagrams as their value
  --scaled-svg, -sc            SVG sized by its viewBox alone
  --shadow-blur, -blur         A drop shadow under the boxes
  --draw-route-frame, -drf     A frame around route boxes

Compiler options (as faust):
  -double, --double            Compile in double precision
  -single, --single            Compile in single precision (the default)
  -pn NAME, --process-name NAME  Probe this definition instead of process
  -vec, --vec                  Vector mode
  -vs N, -lv N                 Vector size, loop variant
  -ss N, --scheduling-strategy N  Scheduling strategy
  -mcd N, -dlt N, -ct N, -ftz N   As faust
  -ec, -os, -mem0              Refused: a probe drives compute and supplies no memory
                               manager

  -h, --help                   Print this help
  -v, --version                Print the version
)";

[[noreturn]] static void usageError(const std::string& message)
{
    fprintf(stderr, "error: %s\n\nUsage: faustprobe [OPTIONS] <FILE>\n\nFor more information, try '--help'.\n",
            message.c_str());
    exit(2);
}

std::vector<std::string> CompileOptions::argv() const
{
    std::vector<std::string> out;
    auto valued = [&out](const char* flag, const Optional<std::string>& value) {
        if (value) {
            out.push_back(flag);
            out.push_back(*value);
        }
    };
    if (processName != "process") {
        out.push_back("-pn");
        out.push_back(processName);
    }
    valued("-mcd", mcd);
    valued("-dlt", dlt);
    valued("-ct", checkTable);
    valued("-ftz", ftz);
    valued("-vs", vs);
    valued("-lv", lv);
    valued("-ss", scheduling);
    if (vec) {
        out.push_back("-vec");
    }
    return out;
}

namespace {

// One option of the command line: its long name, what it does with its value.
struct Option {
    bool                                     takesValue;
    std::string                              valueName;
    std::function<void(const std::string&)>  set;
};

class Parser {
   public:
    explicit Parser(Args& args) : fArgs(args) { declare(); }

    void parse(int argc, char* argv[])
    {
        std::vector<std::string> tokens(argv + 1, argv + argc);
        bool                     onlyFiles = false;
        std::vector<std::string> files;
        for (size_t i = 0; i < tokens.size(); i++) {
            std::string token = tokens[i];
            if (onlyFiles || token.empty() || token[0] != '-' || token == "-") {
                files.push_back(token);
                continue;
            }
            if (token == "--") {
                onlyFiles = true;
                continue;
            }
            if (token == "-h" || token == "--help") {
                fputs(kHelp, stdout);
                exit(0);
            }
            if (token == "-v" || token == "--version") {
                printf("faustprobe %s\n", getCLibFaustVersion());
                puts("Copyright (C) 2002-2026, GRAME - Centre National de Creation Musicale. All rights reserved.");
                exit(0);
            }
            if (startsWith(token, "-I") && token != "-I" && !startsWith(token, "--")) {
                fArgs.importDirs.push_back(token.substr(2));
                continue;
            }
            std::string name = token, value;
            bool        hasValue = false;
            size_t      equal    = token.find('=');
            if (startsWith(token, "--") && equal != std::string::npos) {
                name     = token.substr(0, equal);
                value    = token.substr(equal + 1);
                hasValue = true;
            }
            auto alias = fAliases.find(name);
            if (alias != fAliases.end()) {
                name = alias->second;
            }
            if (name == "--at") {
                if (i + 2 >= tokens.size()) {
                    // what remains is taken for the file
                    usageError("the following required arguments were not provided:\n  <FILE>");
                }
                fArgs.ats.push_back(tokens[++i]);
                fArgs.ats.push_back(tokens[++i]);
                fArgs.given.insert(name);
                continue;
            }
            if (name == "--fd-check") {
                fArgs.given.insert(name);
                fdWhere(hasValue ? value : "start");
                continue;
            }
            auto option = fOptions.find(name);
            if (option == fOptions.end()) {
                usageError("unexpected argument '" + token + "' found");
            }
            fArgs.given.insert(name);
            if (option->second.takesValue) {
                if (!hasValue) {
                    if (i + 1 >= tokens.size()) {
                        usageError("a value is required for '" + name + " <" + option->second.valueName +
                                   ">' but none was supplied");
                    }
                    value = tokens[++i];
                }
                fCurrent = name;
                option->second.set(value);
            } else {
                if (hasValue) {
                    usageError("unexpected value '" + value + "' for '" + name + "' found");
                }
                option->second.set("");
            }
        }
        if (files.empty()) {
            usageError("the following required arguments were not provided:\n  <FILE>");
        }
        if (files.size() > 1) {
            usageError("unexpected argument '" + files[1] + "' found");
        }
        fArgs.file = files[0];
        checkRelations();
    }

   private:
    Args&                         fArgs;
    std::map<std::string, Option> fOptions;
    std::map<std::string, std::string> fAliases;
    std::string                   fCurrent;

    void flag(const std::string& name, const std::function<void()>& set)
    {
        fOptions[name] = {false, "", [set](const std::string&) { set(); }};
    }

    void valued(const std::string& name, const std::string& valueName,
                const std::function<void(const std::string&)>& set)
    {
        fOptions[name] = {true, valueName, set};
    }

    [[noreturn]] void invalid(const std::string& value, const std::string& why)
    {
        usageError("invalid value '" + value + "' for '" + fCurrent + " <" + fOptions[fCurrent].valueName +
                   ">': " + why);
    }

    void text(const std::string& name, const std::string& valueName, std::string& target)
    {
        valued(name, valueName, [&target](const std::string& value) { target = value; });
    }
    void text(const std::string& name, const std::string& valueName, Optional<std::string>& target)
    {
        valued(name, valueName, [&target](const std::string& value) { target = value; });
    }
    void list(const std::string& name, const std::string& valueName, std::vector<std::string>& target)
    {
        valued(name, valueName, [&target](const std::string& value) { target.push_back(value); });
    }
    void size(const std::string& name, const std::string& valueName, size_t& target)
    {
        valued(name, valueName, [this, &target](const std::string& value) {
            if (!parseSize(value, target)) {
                invalid(value, "invalid digit found in string");
            }
        });
    }
    void size(const std::string& name, const std::string& valueName, Optional<size_t>& target)
    {
        valued(name, valueName, [this, &target](const std::string& value) {
            size_t parsed;
            if (!parseSize(value, parsed)) {
                invalid(value, "invalid digit found in string");
            }
            target = parsed;
        });
    }
    void number(const std::string& name, const std::string& valueName, double& target)
    {
        valued(name, valueName, [this, &target](const std::string& value) {
            if (!parseDouble(value, target)) {
                invalid(value, "invalid float literal");
            }
        });
    }
    void number(const std::string& name, const std::string& valueName, Optional<double>& target)
    {
        valued(name, valueName, [this, &target](const std::string& value) {
            double parsed;
            if (!parseDouble(value, parsed)) {
                invalid(value, "invalid float literal");
            }
            target = parsed;
        });
    }
    void integer(const std::string& name, const std::string& valueName, int& target)
    {
        valued(name, valueName, [this, &target](const std::string& value) {
            if (!parseInt(value, target)) {
                invalid(value, "invalid digit found in string");
            }
        });
    }
    void compilerValue(const std::string& name, Optional<std::string>& target)
    {
        valued(name, "N", [this, &target](const std::string& value) {
            int parsed;
            if (!parseInt(value, parsed)) {
                invalid(value, "invalid digit found in string");
            }
            target = value;
        });
    }

    void fdWhere(const std::string& value)
    {
        if (value == "start") {
            fArgs.fdCheck = FdWhere::Start;
        } else if (value == "end") {
            fArgs.fdCheck = FdWhere::End;
        } else if (value == "both") {
            fArgs.fdCheck = FdWhere::Both;
        } else {
            usageError("invalid value '" + value +
                       "' for '--fd-check[=<WHERE>]'\n  [possible values: start, end, both]");
        }
    }

    void declare()
    {
        Args& a = fArgs;
        flag("--determinism-worker", [&a]() { a.determinismWorker = true; });
        list("--eval", "EXPR", a.evals);
        list("--import-dir", "DIR", a.importDirs);
        fAliases["-I"] = "--import-dir";
        integer("--opt-level", "OPT_LEVEL", a.optLevel);
        integer("--sr", "SR", a.sr);
        size("--block", "BLOCK", a.block);
        size("--render", "RENDER", a.render);
        fAliases["-n"] = "--render";
        list("--set", "PATH=VALUE", a.sets);
        flag("--clamp", [&a]() { a.clamp = true; });
        text("--in", "MODE", a.input);
        size("--skip", "SKIP", a.skip);
        size("--every", "EVERY", a.every);
        flag("--list-params", [&a]() { a.listParams = true; });
        flag("--bargraphs", [&a]() { a.bargraphs = true; });
        flag("--quiet", [&a]() { a.quiet = true; });
        text("--precision", "N|full", a.precision);
        text("--out", "FILE", a.out);
        text("--compare", "OTHER", a.compare);
        text("--ref", "FILE", a.reference);
        list("--set-a", "PATH=VALUE", a.setA);
        list("--set-b", "PATH=VALUE", a.setB);
        number("--tolerance", "ABS", a.tolerance);
        number("--rel-tolerance", "REL", a.relTolerance);
        valued("--compare-outputs", "N,...", [this, &a](const std::string& value) {
            for (const std::string& item : split(value, ',')) {
                size_t output;
                if (!parseSize(item, output)) {
                    invalid(item, "invalid digit found in string");
                }
                a.compareOutputs.push_back(output);
            }
        });
        list("--check", "CHECK", a.checks);
        number("--fail-above", "LEVEL", a.failAbove);
        valued("--format", "FORMAT", [&a](const std::string& value) {
            if (value == "csv") {
                a.format = Format::Csv;
            } else if (value == "ir") {
                a.format = Format::Ir;
            } else if (value == "json") {
                a.format = Format::Json;
            } else {
                usageError("invalid value '" + value + "' for '--format <FORMAT>'\n  [possible values: csv, ir, json]");
            }
        });
        list("--sweep", "PATH=V1,V2,...", a.sweeps);
        text("--points", "FILE", a.points);
        text("--reduce", "R", a.reduce);
        number("--f0", "HZ", a.f0);
        text("--describe", "LIST", a.describe);
        number("--describe-hop", "SECONDS", a.describeHop);
        size("--describe-fft", "N", a.describeFft);
        list("--note", "PITCH[:VEL]@ON[..OFF]", a.notes);
        list("--chord", "P1,P2,...[:VEL]@ON[..OFF]", a.chords);
        valued("--protocol", "PROTOCOL", [&a](const std::string& value) {
            if (value == "free") {
                a.protocol = ProtocolKind::Free;
            } else if (value == "impulse-test") {
                a.protocol = ProtocolKind::ImpulseTest;
            } else {
                usageError("invalid value '" + value +
                           "' for '--protocol <PROTOCOL>'\n  [possible values: free, impulse-test]");
            }
        });
        size("--nvoices", "NVOICES", a.nvoices);
        text("--effect", "FILE", a.effect);
        number("--voice-stop-level", "VOICE_STOP_LEVEL", a.voiceStopLevel);
        valued("--train", "CONTROLS", [&a](const std::string& value) {
            for (const std::string& item : split(value, ',')) {
                a.train.push_back(item);
            }
        });
        size("--loss-lane", "LOSS_LANE", a.lossLane);
        size("--grad-lane", "GRAD_LANE", a.gradLane);
        valued("--optimizer", "OPTIMIZER", [&a](const std::string& value) {
            if (value == "adam") {
                a.optimizer = OptimizerKind::Adam;
            } else if (value == "sgd") {
                a.optimizer = OptimizerKind::Sgd;
            } else {
                usageError("invalid value '" + value + "' for '--optimizer <OPTIMIZER>'\n  [possible values: adam, sgd]");
            }
        });
        number("--lr", "LR", a.lr);
        size("--blocks", "BLOCKS", a.blocks);
        flag("--reset-per-block", [&a]() { a.resetPerBlock = true; });
        number("--fd-step", "FD_STEP", a.fdStep);
        number("--fd-tolerance", "FD_TOLERANCE", a.fdTolerance);
        flag("--train-verbose", [&a]() { a.trainVerbose = true; });
        flag("--time", [&a]() { a.time = true; });
        text("--freqresp", "N[:FMIN:FMAX]", a.freqresp);
        size("--settle", "N", a.settle);
        number("--linearity-tolerance", "REL", a.linearityTolerance);
        valued("--error-format", "ERROR_FORMAT", [](const std::string& value) {
            if (value == "json") {
                throw Failure("--error-format json is the diagnostics-v2 report of faust-rs, which libfaust does not "
                              "have: a compile error is reported as text");
            }
            if (value != "human") {
                usageError("invalid value '" + value + "' for '--error-format <ERROR_FORMAT>'\n  [possible values: human]");
            }
        });
        text("--svg", "DIR", a.svg);
        size("--fold", "N", a.fold);
        size("--fold-complexity", "N", a.foldComplexity);
        size("--max-name-size", "N", a.maxNameSize);
        flag("--simplify-diagrams", [&a]() { a.simplifyDiagrams = true; });
        flag("--scaled-svg", [&a]() { a.scaledSvg = true; });
        flag("--shadow-blur", [&a]() { a.shadowBlur = true; });
        flag("--draw-route-frame", [&a]() { a.drawRouteFrame = true; });
        fAliases["-f"]    = "--fold";
        fAliases["-fc"]   = "--fold-complexity";
        fAliases["-mns"]  = "--max-name-size";
        fAliases["-sd"]   = "--simplify-diagrams";
        fAliases["-sc"]   = "--scaled-svg";
        fAliases["-blur"] = "--shadow-blur";
        fAliases["-drf"]  = "--draw-route-frame";

        // the compiler's options, with faust's spellings
        CompileOptions& c = a.compile;
        flag("--double", [&c]() { c.isDouble = true; });
        flag("--single", [&c]() { c.isDouble = false; });
        text("--process-name", "NAME", c.processName);
        flag("--vec", [&c]() { c.vec = true; });
        compilerValue("--vs", c.vs);
        compilerValue("--lv", c.lv);
        compilerValue("--scheduling-strategy", c.scheduling);
        compilerValue("--mcd", c.mcd);
        compilerValue("--dlt", c.dlt);
        compilerValue("--check-table", c.checkTable);
        compilerValue("--ftz", c.ftz);
        flag("--ec", [&c]() { c.externalControl = true; });
        flag("--os", [&c]() { c.oneSample = true; });
        flag("--memory-manager", [&c]() { c.memoryManager = true; });
        fAliases["-double"]             = "--double";
        fAliases["-single"]             = "--single";
        fAliases["-pn"]                 = "--process-name";
        fAliases["-vec"]                = "--vec";
        fAliases["-vs"]                 = "--vs";
        fAliases["-lv"]                 = "--lv";
        fAliases["-ss"]                 = "--scheduling-strategy";
        fAliases["-mcd"]                = "--mcd";
        fAliases["-dlt"]                = "--dlt";
        fAliases["-ct"]                 = "--check-table";
        fAliases["-ftz"]                = "--ftz";
        fAliases["-ec"]                 = "--ec";
        fAliases["--external-control"]  = "--ec";
        fAliases["-os"]                 = "--os";
        fAliases["--one-sample"]        = "--os";
        fAliases["-mem0"]               = "--memory-manager";
        fAliases["-mem"]                = "--memory-manager";
    }

    bool given(const std::string& name) const { return fArgs.given.count(name) > 0; }

    std::string shown(const std::string& name)
    {
        const Option& option = fOptions[name];
        return option.takesValue ? name + " <" + option.valueName + ">" : name;
    }

    void needs(const std::string& name, const std::string& needed)
    {
        if (given(name) && !given(needed)) {
            usageError("the following required arguments were not provided:\n  " + shown(needed));
        }
    }

    void checkRelations()
    {
        if (given("--points") && given("--sweep")) {
            usageError("the argument '" + shown("--points") + "' cannot be used with '" + shown("--sweep") + "'");
        }
        needs("--describe-hop", "--describe");
        needs("--describe-fft", "--describe");
        for (const char* name : {"--fold", "--fold-complexity", "--max-name-size", "--simplify-diagrams",
                                 "--scaled-svg", "--shadow-blur", "--draw-route-frame"}) {
            needs(name, "--svg");
        }
        if (given("--svg")) {
            // the drawing is the whole of the command
            for (const char* name :
                 {"--render",    "--sr",           "--block",       "--opt-level",        "--set",
                  "--set-a",     "--set-b",        "--clamp",       "--in",               "--skip",
                  "--every",     "--list-params",  "--bargraphs",   "--quiet",            "--precision",
                  "--out",       "--compare",      "--ref",         "--tolerance",        "--rel-tolerance",
                  "--compare-outputs", "--check",  "--fail-above",  "--sweep",            "--points",
                  "--reduce",    "--f0",           "--describe",    "--describe-hop",     "--describe-fft",
                  "--at",        "--note",         "--chord",       "--nvoices",          "--effect",
                  "--voice-stop-level", "--train", "--loss-lane",   "--grad-lane",        "--optimizer",
                  "--lr",        "--blocks",       "--reset-per-block", "--fd-check",     "--fd-step",
                  "--fd-tolerance", "--train-verbose", "--time",    "--freqresp",         "--settle",
                  "--linearity-tolerance"}) {
                if (given(name)) {
                    usageError("the argument '" + shown("--svg") + "' cannot be used with '" + name + "'");
                }
            }
        }
    }
};

}  // namespace

Args parseArgs(int argc, char* argv[])
{
    Args   args;
    Parser parser(args);
    parser.parse(argc, argv);
    return args;
}

void refuse(const std::vector<Refusal>& conflicts, const std::string& before, const std::string& after)
{
    for (const Refusal& conflict : conflicts) {
        if (conflict.given) {
            throw Failure(before + conflict.flag + after);
        }
    }
}

bool verificationRequested(const Args& args)
{
    return args.compare.has || args.reference.has || !args.checks.empty();
}

// Rejecting rather than overriding: a protocol run whose sample rate was
// quietly ignored would produce a .ir that looks valid and compares wrong.
void rejectProtocolConflicts(const Args& args)
{
    std::vector<std::pair<const char*, bool>> flags = {
        {"--sr", args.sr != 44100},
        {"--block", args.block != 64},
        {"--in", args.input != "impulse"},
        {"--skip", args.skip != 0},
        {"--bargraphs", args.bargraphs},
        {"--every", args.every != 1},
        {"--set", !args.sets.empty()},
        {"--format", args.format != Format::Ir},
        {"--sweep", !args.sweeps.empty()},
        {"--points", args.points.has},
        {"--reduce", args.reduce.has},
        {"--describe", args.describe.has},
        {"--at", !args.ats.empty()},
        {"--note/--chord", !args.notes.empty() || !args.chords.empty()},
        {"--nvoices", args.nvoices != 0},
        // .ir has its own number text and is the whole output: a flag that
        // would be ignored there is refused rather than ignored
        {"--precision", args.precision.has},
        {"--out", args.out.has},
        {"--fail-above", args.failAbove.has},
        {"--eval", !args.evals.empty()},
        {"--compare/--ref/--check", verificationRequested(args)},
        {"--freqresp", args.freqresp.has},
        {"--svg", args.svg.has},
    };
    std::vector<std::string> offenders;
    for (const auto& flag : flags) {
        if (flag.second) {
            offenders.push_back(flag.first);
        }
    }
    if (!offenders.empty()) {
        throw Failure("--protocol impulse-test fixes the rendering conditions; remove " + join(offenders, ", "));
    }
}
