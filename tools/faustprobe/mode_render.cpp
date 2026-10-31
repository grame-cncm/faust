/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This file is part of faustprobe, the offline probe of a Faust program.
 It is distributed under the same license as the Faust tools: see
 COPYING.txt at the root of the repository.
 ************************************************************************/

// The plain render and the sweep: one program, its controls set, rendered once
// or once per point; and --compare, --ref, --check, which judge that render.
//
// Everything the command line asks is validated before any render, in one
// place and one order, so that which of two errors is reported does not depend
// on where a check happened to be written.

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#if defined(__APPLE__)
#include <mach-o/dyld.h>
#endif

#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>

#include "report.h"

// ---------------------------------------------------------------- .ir text

// controlTools.h::normalize: values below 1e-6 in magnitude print as zero.
// Non-finite values pass, so that a divergence stays visible.
static double irNormalize(double value)
{
    return (std::isfinite(value) && fabs(value) < 0.000001) ? 0.0 : value;
}

static std::string irHeader(size_t inputs, size_t outputs, size_t frames)
{
    char text[128];
    snprintf(text, sizeof(text), "number_of_inputs  : %3zu\nnumber_of_outputs : %3zu\nnumber_of_frames  : %6zu\n",
             inputs, outputs, frames);
    return text;
}

static std::string irLine(size_t frame, const std::vector<double>& samples)
{
    char text[512];  // the largest double has 309 digits before its point
    snprintf(text, sizeof(text), "%6zu : ", frame);
    std::string line = text;
    for (double sample : samples) {
        double value = irNormalize(sample);
        if (std::isfinite(value)) {
            snprintf(text, sizeof(text), " %8.6f", value);
        } else {
            snprintf(text, sizeof(text), " %8s", std::isnan(value) ? "NaN" : (value > 0 ? "inf" : "-inf"));
        }
        line += text;
    }
    return line + "\n";
}

// ---------------------------------------------------------------- --check determinism

// Factories with equal keys are one factory in a process, so a second
// compilation runs in another one. Samples travel as bit patterns, signed zero
// included, without decimal rounding.
static std::string currentExecutable()
{
#if defined(__APPLE__)
    char     path[PATH_MAX];
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) != 0) {
        throw Failure("--check determinism: cannot find this executable");
    }
    return path;
#else
    char    path[PATH_MAX];
    ssize_t size = readlink("/proc/self/exe", path, sizeof(path) - 1);
    if (size < 0) {
        throw Failure("--check determinism: cannot find this executable");
    }
    path[size] = '\0';
    return path;
#endif
}

std::string determinismRender(const Args& args, Samples& samples)
{
    std::vector<std::string> command = {currentExecutable(), "--determinism-worker"};
    command.push_back("--sr=" + std::to_string(args.sr));
    command.push_back("--block=" + str(args.block));
    command.push_back("--render=" + str(args.render));
    command.push_back("--skip=" + str(args.skip));
    command.push_back("--opt-level=" + std::to_string(args.optLevel));
    command.push_back("--in=" + args.input);
    for (const std::string& value : args.importDirs) {
        command.push_back("--import-dir=" + value);
    }
    for (const std::string& value : args.evals) {
        command.push_back("--eval=" + value);
    }
    for (const std::string& value : args.sets) {
        command.push_back("--set=" + value);
    }
    for (const std::string& value : args.setA) {
        command.push_back("--set=" + value);
    }
    for (size_t i = 0; i + 1 < args.ats.size(); i += 2) {
        command.push_back("--at");
        command.push_back(args.ats[i]);
        command.push_back(args.ats[i + 1]);
    }
    for (const std::string& value : args.compile.argv()) {
        command.push_back(value);
    }
    if (args.compile.isDouble) {
        command.push_back("-double");
    }
    command.push_back("--");
    command.push_back(args.file);

    int output[2], errors[2];
    if (pipe(output) != 0 || pipe(errors) != 0) {
        throw Failure("--check determinism: cannot run independent process: " + std::string(strerror(errno)));
    }
    std::vector<char*> argv;
    for (std::string& word : command) {
        argv.push_back(const_cast<char*>(word.c_str()));
    }
    argv.push_back(nullptr);
    fflush(stdout);
    fflush(stderr);
    pid_t child = fork();
    if (child < 0) {
        throw Failure("--check determinism: cannot run independent process: " + std::string(strerror(errno)));
    }
    if (child == 0) {
        dup2(output[1], 1);
        dup2(errors[1], 2);
        close(output[0]), close(output[1]), close(errors[0]), close(errors[1]);
        execv(argv[0], argv.data());
        _exit(127);
    }
    close(output[1]), close(errors[1]);
    std::string report, failure;
    char        buffer[65536];
    ssize_t     count;
    while ((count = read(output[0], buffer, sizeof(buffer))) > 0) {
        report.append(buffer, static_cast<size_t>(count));
    }
    while ((count = read(errors[0], buffer, sizeof(buffer))) > 0) {
        failure.append(buffer, static_cast<size_t>(count));
    }
    close(output[0]), close(errors[0]);
    int status = 0;
    waitpid(child, &status, 0);
    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        throw Failure("--check determinism: independent process failed: " + trim(failure));
    }
    // the key, the window's start, the channels, then one line of bit patterns per frame
    FILE* stream = fmemopen(const_cast<char*>(report.data()), report.size(), "r");
    if (stream == nullptr) {
        throw Failure("--check determinism: invalid independent render response");
    }
    char   key[256];
    size_t start = 0, channels = 0, frames = 0;
    bool   valid = fscanf(stream, "%255s %zu %zu %zu", key, &start, &channels, &frames) == 4;
    samples.start = start;
    samples.channels.assign(channels, std::vector<double>(frames));
    for (size_t ch = 0; valid && ch < channels; ch++) {
        for (size_t frame = 0; valid && frame < frames; frame++) {
            unsigned long long bits;
            valid = fscanf(stream, "%llx", &bits) == 1;
            memcpy(&samples.channels[ch][frame], &bits, sizeof(double));
        }
    }
    fclose(stream);
    if (!valid) {
        throw Failure("--check determinism: invalid independent render response");
    }
    return key;
}

void determinismWorker(const Args& args)
{
    Compiled compiled = compileProgram(args, args.compile.isDouble);
    Probe    probe(compiled.factory, args.sr);
    RenderSpec spec;
    spec.frames   = args.render;
    spec.block    = args.block;
    spec.input    = parseInputAt(args.input, args.sr, probe.inputs());
    spec.skip     = args.skip;
    spec.schedule = buildSchedule(args);
    Samples samples = renderForComparison(probe, spec, parseAssignments(args.sets), "--check determinism");
    printf("%s %zu %zu %zu\n", compiled.factory->shaKey().c_str(), samples.start, samples.channels.size(),
           samples.frames());
    for (const std::vector<double>& channel : samples.channels) {
        for (double value : channel) {
            unsigned long long bits;
            memcpy(&bits, &value, sizeof(double));
            printf("%llx\n", bits);
        }
    }
}

// ---------------------------------------------------------------- verification

namespace {

struct Check {
    enum class Kind { Block, Reset, Determinism, Width };
    Kind   kind = Kind::Reset;
    size_t size = 0;

    std::string name() const
    {
        switch (kind) {
            case Kind::Block:
                return "block=" + str(size);
            case Kind::Reset:
                return "reset";
            case Kind::Determinism:
                return "determinism";
            default:
                return "width";
        }
    }
    bool operator==(const Check& other) const { return kind == other.kind && size == other.size; }
};

}  // namespace

// Block sizes equal to the render's own are dropped: that render is what the
// others are compared with.
static std::vector<Check> parseChecks(const std::vector<std::string>& specs, size_t ownBlock)
{
    std::vector<Check> checks;
    auto               push = [&](Check::Kind kind, size_t size) {
        Check check;
        check.kind = kind;
        check.size = size;
        if (!(kind == Check::Kind::Block && size == ownBlock) &&
            std::find(checks.begin(), checks.end(), check) == checks.end()) {
            checks.push_back(check);
        }
    };
    // a sample at a time, a size that divides nothing, and a large one
    auto defaultBlocks = [&]() {
        for (size_t size : {size_t(1), size_t(7), size_t(512)}) {
            push(Check::Kind::Block, size);
        }
    };
    for (const std::string& spec : specs) {
        if (spec == "reset") {
            push(Check::Kind::Reset, 0);
        } else if (spec == "determinism") {
            push(Check::Kind::Determinism, 0);
        } else if (spec == "width") {
            push(Check::Kind::Width, 0);
        } else if (spec == "block") {
            defaultBlocks();
        } else if (spec == "all") {
            defaultBlocks();
            push(Check::Kind::Reset, 0);
            push(Check::Kind::Determinism, 0);
            push(Check::Kind::Width, 0);
        } else {
            if (!startsWith(spec, "block=")) {
                throw Failure("unknown check `" + spec +
                              "` (expected block[=N1,N2,...], reset, determinism, width or all)");
            }
            for (const std::string& item : split(spec.substr(6), ',')) {
                size_t size;
                if (!parseSize(trim(item), size) || size == 0) {
                    throw Failure("`--check " + spec + "`: `" + item + "` is not a block size");
                }
                push(Check::Kind::Block, size);
            }
        }
    }
    return checks;
}

Samples renderForComparison(Probe& probe, const RenderSpec& spec, const Assignments& sets, const std::string& what)
{
    probe.reset();
    for (const auto& set : sets) {
        probe.set(set.first, set.second);
    }
    Samples     samples;
    RenderStats stats = probe.collect(spec, samples);
    auto        first = stats.firstNonFinite();
    if (first) {
        throw Failure(what + " produced non-finite samples: first at frame " + str(first.value.second.frame) +
                      ", out" + str(first.value.first) + " (" + nonFiniteName(first.value.second.value) + ")");
    }
    return samples;
}

static std::vector<std::string> comparisonLines(const std::string& tag, const Comparison& comparison, bool gate,
                                                const NumberFormat& fmt)
{
    std::vector<std::string> lines;
    for (const auto& entry : comparison.channels) {
        const ChannelDiff& diff   = entry.second;
        std::string        output = "# " + tag + " out" + str(entry.first) + ": ";
        if (diff.identical) {
            lines.push_back(output + "identical");
            continue;
        }
        std::string at = diff.maxAbsAt ? "frame " + str(*diff.maxAbsAt) : "a non-finite sample";
        std::string verdict;
        if (diff.firstBeyond && gate) {
            const Disagreement& d = *diff.firstBeyond;
            verdict = "first beyond tolerance: frame " + str(d.frame) + " (" + fmt.sample(d.value) + " vs " +
                      fmt.sample(d.reference) + ")";
        } else if (diff.firstBeyond) {
            verdict = "first difference: frame " + str(diff.firstBeyond.value.frame);
        } else {
            verdict = "within tolerance";
        }
        lines.push_back(output + "max_abs=" + fmt.computed(diff.maxAbs) + " at " + at +
                        ", max_rel=" + fmt.computed(diff.maxRel) + ", " + verdict);
    }
    return lines;
}

static Json comparisonJson(const Comparison& comparison)
{
    Json channels = Json::array();
    for (const auto& entry : comparison.channels) {
        const ChannelDiff& diff   = entry.second;
        Json               beyond;
        if (diff.firstBeyond) {
            const Disagreement& d = *diff.firstBeyond;
            beyond = Json::object().set("frame", d.frame).set("value", d.value).set("reference", d.reference);
        }
        channels.push(Json::object()
                          .set("output", entry.first)
                          .set("identical", diff.identical)
                          .set("max_abs", diff.maxAbs)
                          .set("max_abs_at", diff.maxAbsAt)
                          .set("max_rel", diff.maxRel)
                          .set("first_beyond", beyond));
    }
    return Json::object().set("agrees", comparison.agrees()).set("channels", channels);
}

namespace {

struct Subject {
    const Args&                     args;
    const std::shared_ptr<Factory>& factory;
    Probe&                          probe;
    const RenderSpec&               spec;
    const Assignments&              fixed;
    const NumberFormat&             fmt;
};

// What is said of a render that was verified.
struct Verdict {
    std::vector<std::string> lines;
    Json                     json = Json::object();
    Optional<std::string>    failure;
};

// What --compare, --ref and --check need, settled before any render.
class Verification {
   public:
    bool requested = false;

    void prepare(const Args& args, Probe& probe, const Schedule& schedule, bool sweeping, std::vector<Clamped>& clamped)
    {
        requested = verificationRequested(args);
        if (requested) {
            refuse({{sweepFlag(args), sweeping}, {"--format ir", args.format == Format::Ir}}, "",
                   " cannot be combined with --compare, --ref or --check, which look at one render");
        }
        if (args.compare.has && args.reference.has) {
            throw Failure("--compare and --ref both name the reference: give one");
        }
        if (!args.compare.has && (!args.setA.empty() || !args.setB.empty())) {
            throw Failure("--set-a and --set-b address the two programs of --compare");
        }
        auto nonNegative = [](const char* flag, const Optional<double>& value) {
            if (value && !(*value >= 0.0 && std::isfinite(*value))) {
                throw Failure(std::string(flag) + " must be a non-negative number");
            }
        };
        nonNegative("--tolerance", args.tolerance);
        nonNegative("--rel-tolerance", args.relTolerance);
        for (size_t output : args.compareOutputs) {
            if (output >= probe.outputs()) {
                throw Failure("--compare-outputs " + str(output) + ": the program has " + str(probe.outputs()) +
                              " output(s)");
            }
        }
        fChecks = parseChecks(args.checks, args.block);
        // the second program, with the values it alone is given
        fOtherSets = parseAssignments(args.sets);
        for (const auto& set : parseAssignments(args.setB)) {
            fOtherSets.push_back(set);
        }
        if (args.compare) {
            fOtherPath = *args.compare;
            otherProgram(args, probe, schedule, clamped);
        }
        if (args.reference) {
            fReferencePath     = *args.reference;
            fReference.start    = args.skip;
            fReference.channels = readChannels(*args.reference).channels;
            fHasReference       = true;
        }
        fTolerance.abs     = args.tolerance.has ? *args.tolerance : 0.0;
        fTolerance.rel     = args.relTolerance.has ? *args.relTolerance : 0.0;
        fExplicitTolerance = args.tolerance.has || args.relTolerance.has;
        fOutputs           = args.compareOutputs.empty() ? nullptr : &args.compareOutputs;
    }

    Verdict judge(const Subject& subject, const Samples& render, const FrameContext& context)
    {
        Verdict verdict;
        if (!requested) {
            return verdict;
        }
        const NumberFormat& fmt    = subject.fmt;
        auto                failed = [&](const std::string& what, const Comparison& comparison) {
            auto first = comparison.firstBeyond();
            if (!verdict.failure && first) {
                const Disagreement& d = first.value.second;
                verdict.failure       = what + "\n  first: frame " + str(d.frame) + ", out" + str(first.value.first) +
                                  ": " + fmt.sample(d.value) + " vs " + fmt.sample(d.reference) + context(d.frame);
            }
        };
        std::string name;
        Samples     reference;
        bool        hasReference = false;
        if (fOther != nullptr) {
            name         = fOtherPath;
            reference    = renderForComparison(*fOther, subject.spec, fOtherSets, "`" + fOtherPath + "`");
            hasReference = true;
        } else if (fHasReference) {
            name         = fReferencePath;
            reference    = fReference;
            hasReference = true;
        }
        if (hasReference) {
            Comparison comparison;
            try {
                comparison = compare(render, reference, fTolerance, fOutputs);
            } catch (const Failure& failure) {
                throw Failure("cannot compare with `" + name + "`: " + failure.what());
            }
            verdict.lines.push_back("# compare: against " + name + ", tolerance abs=" + plainNumber(fTolerance.abs) +
                                    " rel=" + plainNumber(fTolerance.rel));
            for (const std::string& line : comparisonLines("compare", comparison, true, fmt)) {
                verdict.lines.push_back(line);
            }
            verdict.json.set("compare", comparisonJson(comparison).set("reference", name));
            if (!comparison.agrees()) {
                failed("the render differs from `" + name + "` beyond the tolerance", comparison);
            }
        }
        Json checksJson = Json::array();
        for (const Check& check : fChecks) {
            std::string tag = "check " + check.name();
            Samples     samples;
            bool        gate = true;
            Tolerance   limit = fTolerance;
            renderAgain(check, tag, subject, verdict.lines, samples, gate, limit);
            Comparison comparison;
            try {
                comparison = compare(render, samples, limit, fOutputs);
            } catch (const Failure& failure) {
                throw Failure(tag + ": " + failure.what());
            }
            for (const std::string& line : comparisonLines(tag, comparison, gate, fmt)) {
                verdict.lines.push_back(line);
            }
            checksJson.push(comparisonJson(comparison).set("check", check.name()).set("gate", gate));
            if (gate && !comparison.agrees()) {
                failed("--" + tag + " failed: the render is not the same", comparison);
            }
        }
        if (!checksJson.empty()) {
            verdict.json.set("checks", checksJson);
        }
        return verdict;
    }

   private:
    Tolerance                  fTolerance;
    bool                       fExplicitTolerance = false;
    const std::vector<size_t>* fOutputs           = nullptr;
    std::vector<Check>         fChecks;
    std::unique_ptr<Probe>     fOther;
    std::string                fOtherPath;
    Assignments                fOtherSets;
    std::string                fReferencePath;
    Samples                    fReference;
    bool                       fHasReference = false;

    void otherProgram(const Args& args, Probe& probe, const Schedule& schedule, std::vector<Clamped>& clamped)
    {
        std::shared_ptr<Factory> factory;
        try {
            factory = Factory::compileFile(fOtherPath, args.importDirs, args.compile.argv(), args.compile.isDouble,
                                           args.optLevel);
        } catch (const Failure& failure) {
            throw Failure("--compare: " + std::string(failure.what()));
        }
        fOther.reset(new Probe(factory, args.sr));
        if (fOther->outputs() != probe.outputs()) {
            throw Failure("--compare: `" + args.file + "` has " + str(probe.outputs()) + " output(s) and `" +
                          fOtherPath + "` " + str(fOther->outputs()));
        }
        try {
            for (const auto& set : fOtherSets) {
                checkValue(fOther->controls(), set.first, set.second, args.clamp, clamped);
            }
            for (const ParamWrite& write : schedule.paramWrites()) {
                checkValue(fOther->controls(), write.path, write.value, args.clamp, clamped);
            }
        } catch (const Failure& failure) {
            throw Failure("--compare `" + fOtherPath + "`: " + failure.what());
        }
    }

    void renderAgain(const Check& check, const std::string& tag, const Subject& subject, std::vector<std::string>& lines,
                     Samples& samples, bool& gate, Tolerance& limit)
    {
        const Args& args = subject.args;
        switch (check.kind) {
            case Check::Kind::Block: {
                Probe      fresh(subject.factory, args.sr);
                RenderSpec atSize = subject.spec;
                atSize.block      = check.size;
                samples           = renderForComparison(fresh, atSize, subject.fixed, tag);
                break;
            }
            case Check::Kind::Reset:
                samples = renderForComparison(subject.probe, subject.spec, subject.fixed, tag);
                break;
            case Check::Kind::Determinism: {
                std::string key = determinismRender(args, samples);
                lines.push_back("# " + tag + ": a second compilation gives " +
                                (key == subject.factory->shaKey() ? "the same" : "ANOTHER") + " program key");
                lines.push_back("# " + tag + ": rendered in an independent process");
                // two compilations of one source owe each other the very bits
                limit = Tolerance();
                break;
            }
            case Check::Kind::Width: {
                Compiled other = compileProgram(args, !args.compile.isDouble);
                Probe    fresh(other.factory, args.sr);
                lines.push_back("# " + tag + ": this render in " + (args.compile.isDouble ? "double" : "single") +
                                " precision against the " + (args.compile.isDouble ? "single" : "double") + " one" +
                                (fExplicitTolerance ? "" : " (a report: no tolerance given)"));
                samples = renderForComparison(fresh, subject.spec, subject.fixed, tag);
                gate    = fExplicitTolerance;
                break;
            }
        }
    }
};

// One render, once it succeeded: what the outputs are made of.
struct Rendered {
    RenderStats              stats;
    Channels                 collected;
    std::vector<std::string> notes;
    std::vector<Clamped>     clamps;
    Assignments              bargraphs;
    Measured                 measured;
    bool                     dumping = false;
};

// What a run will do, validated before any render.
class Run {
   public:
    Run(const Args& args, const Compiled& compiled, Probe& probe, const NumberFormat& fmt, bool impulseTest,
        const std::vector<Axis>& axes, const std::vector<Point>& points)
        : fArgs(args), fCompiled(compiled), fProbe(probe), fFmt(fmt),
          fMeasures(args, probe.outputs(), args.render > args.skip ? args.render - args.skip : 0, probe.sampleRate()),
          fAxes(axes), fPoints(points)
    {
        fSchedule = buildSchedule(args);
        if (fSchedule.needsPoly()) {
            throw Failure("--note/--chord require --nvoices > 0");
        }
        // A schedule replays at every sweep point, which is what measuring a
        // triggered instrument needs. The one genuine conflict is a schedule
        // that writes a control the sweep is also driving.
        for (const std::string& path : fSchedule.paramPaths()) {
            for (const Axis& axis : fAxes) {
                if (axis.path == path) {
                    throw Failure("--at writes `" + axis.path + "`, which " + sweepFlag(args) +
                                  " is also driving; the scheduled write would override the swept value");
                }
            }
        }
        fFixed = parseAssignments(args.sets);
        for (const auto& set : parseAssignments(args.setA)) {
            fFixed.push_back(set);
        }
        // Everything a render will write is checked before any render: the
        // scheduled writes ignore their errors inside the render loop.
        for (const auto& set : fFixed) {
            checkValue(probe.controls(), set.first, set.second, args.clamp, fClamps.fixed);
        }
        for (const ParamWrite& write : fSchedule.paramWrites()) {
            checkValue(probe.controls(), write.path, write.value, args.clamp, fClamps.fixed);
        }
        fClamps.checkAxes(probe.controls(), fAxes, args.clamp);
        if (args.bargraphs && args.format == Format::Ir) {
            throw Failure("--bargraphs cannot be combined with --format ir");
        }
        for (const auto& bargraph : probe.bargraphs()) {
            fBargraphPaths.push_back(bargraph.first);
        }
        fLabels = outputLabels(args, compiled, probe.outputs());
        if (compiled.eval != nullptr) {
            for (size_t ch = 0; ch < fLabels.size(); ch++) {
                fLegend.push_back("# eval out" + str(ch) + " = " + fLabels[ch]);
            }
        }
        bool sweeping = !fAxes.empty();
        fVerification.prepare(args, probe, fSchedule, sweeping, fClamps.fixed);

        fSpec.frames       = args.render;
        fSpec.block        = args.block;
        fSpec.input        = parseInputAt(args.input, args.sr, probe.inputs());
        fSpec.skip         = args.skip;
        fSpec.schedule     = fSchedule;
        fSpec.driveButtons = impulseTest;
        fSpec.limit        = args.failAbove;
        fSpec.time         = args.time;

        if (args.out) {
            refuse({{sweepFlag(args), sweeping}, {"--format ir", args.format == Format::Ir}, {"--every", args.every != 1}},
                   "", " cannot be combined with --out, which writes every frame of one render");
        }
        // .ir describes exactly one render and cannot hold a sweep at all
        if (sweeping && args.format == Format::Ir) {
            throw Failure(sweepFlag(args) + " cannot be combined with --format ir");
        }
        if (args.describe && args.format == Format::Ir) {
            throw Failure("--describe cannot be combined with --format ir");
        }
        fSweepCsv = sweeping && args.format == Format::Csv;
    }

    void run()
    {
        const Args& args      = fArgs;
        bool        rowsAlone = fSweepCsv || args.format == Format::Ir;
        if (fSweepCsv && !args.quiet) {
            writeLine(join(sweepHeader(), ","));
        }
        // under --quiet the annotations are the output; otherwise they
        // annotate a dump or a sweep's rows, which own stdout
        Sink annotate = Sink::beside(!args.quiet || rowsAlone);
        if (rowsAlone) {
            for (const Clamped& clamp : fClamps.all()) {
                annotate.say(clamp.line());
            }
        }
        if (fSweepCsv) {
            annotate.sayAll(fLegend);
        }
        Json                  runs = Json::array();
        size_t                silentPoints = 0;
        std::vector<Measured> measured;
        TotalTiming           totalTiming;
        Optional<std::string> verificationFailure;

        for (const Point& point : fPoints) {
            Rendered rendered = renderPoint(point);
            if (!rendered.notes.empty()) {
                silentPoints++;
            }
            // after the bargraphs were read: --check reset renders again on this instance
            Verdict verdict = verify(point, rendered);
            if (!verificationFailure) {
                verificationFailure = verdict.failure;
            }
            totalTiming.add(rendered.stats.timing);
            if (args.format == Format::Json) {
                runs.push(jsonRun(point, rendered, verdict));
            } else if (args.format == Format::Csv) {
                if (fSweepCsv) {
                    writeLine(join(sweepRow(point, rendered), ","));
                } else {
                    statistics(rendered, verdict);
                }
            }
            measured.push_back(rendered.measured);
        }
        if (rowsAlone) {
            annotate.sayAll(totalTiming.lines(fCompiled.seconds, fPoints.size()));
        }
        // A sweep's rows show their zeros; what they do not show is why.
        if (fSweepCsv && silentPoints == fPoints.size()) {
            for (const std::string& note : silenceNotes(fProbe, fSpec.input)) {
                annotate.say("# note: " + note + " (at every sweep point)");
            }
        }
        if (fSweepCsv) {
            annotate.sayAll(fMeasures.sweepNotes(measured));
        }
        if (args.format == Format::Json) {
            Json document = documentJson(args);
            document.set("frames", args.render);
            document.set("reduce", fMeasures.reductionJson());
            document.set("runs", runs);
            describeProgram(document, args, fCompiled.eval != nullptr ? &fLabels : nullptr, fCompiled.seconds);
            printJson(document);
        }
        // the output above carries the details; the verdict is the exit status
        if (verificationFailure) {
            throw Failure(*verificationFailure);
        }
    }

   private:
    const Args&       fArgs;
    const Compiled&   fCompiled;
    Probe&            fProbe;
    NumberFormat      fFmt;
    Measures          fMeasures;
    std::vector<Axis> fAxes;
    std::vector<Point> fPoints;
    Schedule          fSchedule;
    Assignments       fFixed;
    Clamps            fClamps;
    std::vector<std::string> fBargraphPaths;
    std::vector<std::string> fLabels;
    std::vector<std::string> fLegend;
    Verification      fVerification;
    RenderSpec        fSpec;
    bool              fSweepCsv = false;

    std::vector<std::string> sweepHeader() const
    {
        std::vector<std::string> header;
        for (const Axis& axis : fAxes) {
            header.push_back(axis.path);
        }
        for (const std::string& column : fMeasures.header(fProbe.outputs())) {
            header.push_back(column);
        }
        if (fArgs.bargraphs) {
            header.insert(header.end(), fBargraphPaths.begin(), fBargraphPaths.end());
        }
        return header;
    }

    void printFramesHeader() const
    {
        if (fArgs.format == Format::Csv) {
            std::string line = "frame";
            for (const std::string& label : fLabels) {
                line += "," + csvField(label);
            }
            if (fArgs.bargraphs) {
                for (const std::string& path : fBargraphPaths) {
                    line += "," + path;
                }
            }
            writeLine(line);
        } else if (fArgs.format == Format::Ir) {
            fputs(irHeader(fProbe.inputs(), fProbe.outputs(), fArgs.render).c_str(), stdout);
        }
    }

    void printFrame(size_t frame, const std::vector<double>& samples) const
    {
        if (fArgs.format == Format::Csv) {
            std::string line = str(frame);
            for (double value : samples) {
                line += ',';
                line += fFmt.sample(value);
            }
            if (fArgs.bargraphs) {
                // read after the block this frame belongs to was computed
                for (const auto& bargraph : fProbe.bargraphs()) {
                    line += ',';
                    line += fFmt.sample(bargraph.second);
                }
            }
            writeLine(line);
        } else if (fArgs.format == Format::Ir) {
            fputs(irLine(frame, samples).c_str(), stdout);
        }
    }

    Rendered renderPoint(const Point& point)
    {
        const Args& args = fArgs;
        prime(fProbe, fFixed, point);

        std::unique_ptr<SampleWriter> writer;
        if (args.out) {
            writer.reset(new SampleWriter(*args.out, fProbe.outputs(), args.render > args.skip ? args.render - args.skip : 0,
                                          args.compile.isDouble, args.sr));
        }
        Rendered rendered;
        rendered.dumping = !args.quiet && writer == nullptr;
        bool streaming   = rendered.dumping && args.format != Format::Json && !fSweepCsv;
        if (streaming) {
            printFramesHeader();
        }
        // the samples are collected only when something needs them
        bool wantSamples = fVerification.requested || fMeasures.needsSamples();
        if (wantSamples) {
            rendered.collected.assign(fProbe.outputs(), std::vector<double>());
        }
        size_t every = std::max<size_t>(args.every, 1);
        rendered.stats = fProbe.render(fSpec, [&](size_t frame, const std::vector<double>& samples) {
            if (wantSamples) {
                for (size_t ch = 0; ch < samples.size(); ch++) {
                    rendered.collected[ch].push_back(samples[ch]);
                }
            }
            if (writer != nullptr) {
                writer->push(samples);
            }
            if (streaming && (frame - fSpec.skip) % every == 0) {
                printFrame(frame, samples);
            }
        });
        if (writer != nullptr) {
            writer->finish();
        }
        // A non-finite sample invalidates a measurement, so the free path
        // fails on it. The .ir path must not: the reference corpus holds DSPs
        // whose expected output has NaN in it, and the artifact is what
        // filesCompare judges.
        Optional<std::pair<size_t, Located>> nonFinite;
        if (args.format != Format::Ir) {
            nonFinite = rendered.stats.firstNonFinite();
        }
        Optional<std::string> failure =
            renderFailure(rendered.stats, nonFinite, args.failAbove, args.render, fFmt,
                          [&](size_t frame) { return context(point, frame); });
        if (failure) {
            throw Failure(*failure);
        }
        // Exact silence is nearly always a gate never pressed or an input never fed.
        if (rendered.stats.isSilent()) {
            rendered.notes = silenceNotes(fProbe, fSpec.input);
        }
        rendered.measured  = fMeasures.measure(rendered.stats, rendered.collected);
        rendered.clamps    = fClamps.ofPoint(point);
        rendered.bargraphs = fProbe.bargraphs();
        return rendered;
    }

    std::string context(const Point& point, size_t frame) const
    {
        return failureContext(frame, written(fProbe.controls(), fFixed, point), fSchedule, fProbe.controls());
    }

    Verdict verify(const Point& point, const Rendered& rendered)
    {
        if (!fVerification.requested) {
            return Verdict();
        }
        Samples render;
        render.start    = fSpec.skip;
        render.channels = rendered.collected;
        Subject subject = {fArgs, fCompiled.factory, fProbe, fSpec, fFixed, fFmt};
        return fVerification.judge(subject, render, [&](size_t frame) { return context(point, frame); });
    }

    Json jsonRun(const Point& point, const Rendered& rendered, const Verdict& verdict) const
    {
        Json entry = verdict.json;
        Json set   = Json::object();
        for (const auto& value : applied(fProbe.controls(), point)) {
            set.set(value.first, value.second);
        }
        entry.set("set", set);
        if (!rendered.clamps.empty()) {
            Json clamped = Json::array();
            for (const Clamped& clamp : rendered.clamps) {
                clamped.push(clamp.json());
            }
            entry.set("clamped", clamped);
        }
        if (!rendered.notes.empty()) {
            entry.set("notes", Json::strings(rendered.notes));
        }
        entry.set("window", windowJson(rendered.stats));
        // without an explicit reduction, the full statistics: a sweep with no
        // numbers is useless
        if (!fMeasures.addReduced(entry, rendered.measured)) {
            entry.set("channels", channelsJson(rendered.stats));
        }
        fMeasures.addDescribed(entry, rendered.measured);
        if (!rendered.bargraphs.empty()) {
            Json shown = Json::object();
            for (const auto& bargraph : rendered.bargraphs) {
                shown.set(bargraph.first, bargraph.second);
            }
            entry.set("bargraphs", shown);
        }
        if (rendered.stats.timing) {
            entry.set("timing", timingJson(*rendered.stats.timing));
        }
        return entry;
    }

    std::vector<std::string> sweepRow(const Point& point, const Rendered& rendered) const
    {
        // the value the render used: under --clamp the row must not claim the requested one
        std::vector<std::string> row;
        for (const auto& value : applied(fProbe.controls(), point)) {
            row.push_back(plainNumber(value.second));
        }
        for (const std::string& column : fMeasures.row(rendered.measured, rendered.stats, fFmt)) {
            row.push_back(column);
        }
        if (fArgs.bargraphs) {
            for (const auto& bargraph : rendered.bargraphs) {
                row.push_back(fFmt.sample(bargraph.second));
            }
        }
        return row;
    }

    void statistics(const Rendered& rendered, const Verdict& verdict) const
    {
        const RenderStats& stats = rendered.stats;
        // with --quiet or --out the statistics are the whole output; otherwise
        // they annotate a dump that already owns stdout
        Sink sink = Sink::beside(rendered.dumping);
        sink.say("# frames=" + str(fArgs.render) + " sr=" + std::to_string(fArgs.sr) + " window=" +
                 str(stats.windowStart) + ".." + str(stats.windowStart + stats.windowLength) + " (" +
                 str(stats.windowLength) + " frames)");
        sink.sayAll(fLegend);
        sink.sayAll(channelLines(stats, fFmt));
        sink.sayAll(fMeasures.lines(rendered.measured, fFmt));
        for (const auto& bargraph : rendered.bargraphs) {
            sink.say("# bargraph " + bargraph.first + "=" + fFmt.sample(bargraph.second));
        }
        for (const Clamped& clamp : rendered.clamps) {
            sink.say(clamp.line());
        }
        for (const std::string& note : rendered.notes) {
            sink.say("# note: " + note);
        }
        sink.sayAll(verdict.lines);
        if (stats.timing) {
            sink.sayAll(renderTimeLines(fCompiled.seconds, *stats.timing));
        }
    }
};

}  // namespace

void runRender(const Args& args, bool impulseTest)
{
    Compiled     compiled = compileTimed(args);
    Probe        probe(compiled.factory, args.sr);
    NumberFormat fmt = numberFormat(args);
    if (args.listParams) {
        printControls("path", probe.controls(), fmt);
        return;
    }
    std::vector<Axis>  axes;
    std::vector<Point> points;
    sweepPoints(args, axes, points);
    Run run(args, compiled, probe, fmt, impulseTest, axes, points);
    run.run();
}
