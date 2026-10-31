/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This file is part of faustprobe, the offline probe of a Faust program.
 It is distributed under the same license as the Faust tools: see
 COPYING.txt at the root of the repository.
 ************************************************************************/

// --nvoices: the polyphonic wrapper, played by --note and --chord. A sweep
// renders every point from a reset instrument: the voices and the effect
// cleared, every voice free, the notes of the schedule played again.

#include <algorithm>

#include "report.h"

// What operates on one instance only is refused.
static void refuseScalarOnly(const Args& args)
{
    if (args.format == Format::Ir) {
        throw Failure("--format ir is scoped to the scalar impulse-test protocol");
    }
    if (args.bargraphs) {
        throw Failure("--bargraphs reads the scalar Probe only; use --nvoices 0");
    }
    std::vector<std::string> given = args.compile.argv();
    if (!given.empty()) {
        throw Failure("the compiler options (" + join(given, " ") + ") reach the scalar Probe only; use --nvoices 0");
    }
    refuse({{"--eval", !args.evals.empty()},
            {"--compare/--ref/--check", verificationRequested(args)},
            {"--freqresp", args.freqresp.has}},
           "", " operates on the scalar Probe only; use --nvoices 0");
}

// A poly render is silent until a note plays: say which it is.
static std::vector<std::string> polySilenceNotes(const RenderStats& stats, const Schedule& schedule,
                                                 const InputMode& input, const PolyProbe& poly)
{
    std::vector<std::string> notes;
    if (stats.isSilent()) {
        notes.push_back("every output is exactly zero over the window");
        if (!schedule.needsPoly()) {
            notes.push_back("no --note or --chord is scheduled: every voice stays free");
        }
        if (input.kind == InputMode::Kind::Zero && poly.inputs() > 0) {
            notes.push_back("input is `zero` and a voice has " + str(poly.inputs()) + " input(s)");
        }
    }
    return notes;
}

// Every write of the command line, checked before any render as for a scalar
// program. What a note writes is not a widget's doing and is not checked.
static std::vector<Clamped> checkWrites(const Args& args, const PolyProbe& poly, const Assignments& fixed,
                                        const Schedule& schedule, const std::vector<Axis>& axes)
{
    std::vector<Clamped> clamped;
    for (const auto& set : fixed) {
        checkPolyValue(poly, set.first, set.second, args.clamp, clamped);
    }
    for (const ParamWrite& write : schedule.paramWrites()) {
        checkPolyValue(poly, write.path, write.value, args.clamp, clamped);
    }
    // as on the scalar path: a scheduled write to a swept control would
    // override the swept value
    for (const std::string& path : schedule.paramPaths()) {
        for (const Axis& axis : axes) {
            if (axis.path == path) {
                throw Failure("--at writes `" + axis.path + "`, which " + sweepFlag(args) +
                              " is also driving; the scheduled write would override the swept value");
            }
        }
    }
    for (const Axis& axis : axes) {
        for (double value : axis.values) {
            checkPolyValue(poly, axis.path, value, args.clamp, clamped);
        }
    }
    return clamped;
}

// The clamps as a JSON array, and as lines.
static Json clampedJson(const std::vector<Clamped>& clamped)
{
    Json json = Json::array();
    for (const Clamped& clamp : clamped) {
        json.push(clamp.json());
    }
    return json;
}

static std::vector<std::string> clampLines(const std::vector<Clamped>& clamped)
{
    std::vector<std::string> lines;
    for (const Clamped& clamp : clamped) {
        lines.push_back(clamp.line());
    }
    return lines;
}

namespace {

// A sweep of a polyphonic instrument: one render per point, each from a reset
// instrument, said as rows (CSV) or as the runs of one document.
struct PolySweep {
    const Args&                 args;
    PolyProbe&                  poly;
    const PolyRenderSpec&       spec;
    const Assignments&          fixed;
    const Schedule&             schedule;
    const Measures&             measures;
    const std::vector<Clamped>& clamped;
    const NumberFormat&         fmt;
    double                      compileSeconds;

    // One render per point, then what closes the output.
    void run(const std::vector<Axis>& axes, const std::vector<Point>& points)
    {
        bool csv = args.format == Format::Csv;
        if (csv && !args.quiet) {
            std::vector<std::string> header;
            for (const Axis& axis : axes) {
                header.push_back(axis.path);
            }
            for (const std::string& column : measures.header(poly.outputs())) {
                header.push_back(column);
            }
            writeLine(join(header, ","));
        }
        // the rows own stdout: what annotates them goes beside, once
        Sink annotate = Sink::beside(true);
        if (csv) {
            annotate.sayAll(clampLines(clamped));
        }
        Json                     runs = Json::array();
        std::vector<Measured>    measured;
        size_t                   silentPoints = 0;
        TotalTiming              totalTiming;
        std::vector<std::string> lastNotes;
        for (const Point& point : points) {
            Measured    values;
            RenderStats stats = renderPoint(point, values);
            std::vector<std::string> notes = polySilenceNotes(stats, schedule, spec.input, poly);
            if (!notes.empty()) {
                silentPoints++;
            }
            totalTiming.add(stats.timing);
            Assignments used = appliedValues(point);
            if (csv) {
                std::vector<std::string> row;
                for (const auto& value : used) {
                    row.push_back(plainNumber(value.second));
                }
                for (const std::string& column : measures.row(values, stats, fmt)) {
                    row.push_back(column);
                }
                writeLine(join(row, ","));
            } else {
                runs.push(jsonRun(used, stats, values, notes));
            }
            measured.push_back(values);
            lastNotes = notes;
        }
        if (csv) {
            annotate.sayAll(totalTiming.lines(compileSeconds, points.size()));
            if (silentPoints == points.size()) {
                for (const std::string& note : lastNotes) {
                    annotate.say("# note: " + note + " (at every sweep point)");
                }
            }
            annotate.sayAll(measures.sweepNotes(measured));
            return;
        }
        Json document = documentJson(args);
        document.set("nvoices", args.nvoices);
        document.set("frames", args.render);
        document.set("reduce", measures.reductionJson());
        if (!clamped.empty()) {
            document.set("clamped", clampedJson(clamped));
        }
        document.set("runs", runs);
        if (args.time) {
            document.set("timing", Json::object().set("compile_s", compileSeconds));
        }
        printJson(document);
    }

    // One point from a reset instrument; a Failure if the render fails.
    RenderStats renderPoint(const Point& point, Measured& values)
    {
        poly.reset();
        for (const auto& set : fixed) {
            poly.setAll(set.first, set.second);
        }
        for (const auto& assignment : point.assignments) {
            poly.setAll(assignment.first, assignment.second);
        }
        Channels collected;
        if (measures.needsSamples()) {
            collected.assign(poly.outputs(), std::vector<double>());
        }
        RenderStats stats = poly.render(spec, [&collected](size_t, const std::vector<double>& samples) {
            for (size_t ch = 0; ch < collected.size(); ch++) {
                collected[ch].push_back(samples[ch]);
            }
        });
        Assignments writes = fixed;
        writes.insert(writes.end(), point.assignments.begin(), point.assignments.end());
        Optional<std::string> failure =
            renderFailure(stats, stats.firstNonFinite(), args.failAbove, args.render, fmt,
                          [&](size_t frame) { return polyFailureContext(frame, writes, schedule, poly); });
        if (failure) {
            throw Failure(*failure);
        }
        values = measures.measure(stats, collected);
        return stats;
    }

    // The values a point's render used: the requested ones, unless --clamp clamped them.
    Assignments appliedValues(const Point& point) const
    {
        Assignments values;
        for (const auto& assignment : point.assignments) {
            double value = assignment.second;
            try {
                std::vector<PolyWrite> writes = poly.checkWrite(assignment.first, value);
                if (!writes.empty()) {
                    value = writes[0].write.applied;
                }
            } catch (const Failure&) {
            }
            values.push_back(std::make_pair(assignment.first, value));
        }
        return values;
    }

    // One render, as an entry of the document's runs.
    Json jsonRun(const Assignments& used, const RenderStats& stats, const Measured& values,
                 const std::vector<std::string>& notes) const
    {
        Json entry = Json::object();
        Json set   = Json::object();
        for (const auto& value : used) {
            set.set(value.first, value.second);
        }
        entry.set("set", set);
        if (!notes.empty()) {
            entry.set("notes", Json::strings(notes));
        }
        entry.set("window", windowJson(stats));
        entry.set("active_voices", poly.activeVoiceCount());
        if (!measures.addReduced(entry, values)) {
            entry.set("channels", channelsJson(stats));
        }
        measures.addDescribed(entry, values);
        if (stats.timing) {
            entry.set("timing", timingJson(*stats.timing));
        }
        return entry;
    }
};

}  // namespace

// What is written is validated before anything is printed. Without a sweep, one render
// said as a dump and statistics, or as one document.
void runPoly(const Args& args)
{
    refuseScalarOnly(args);
    std::vector<Axis>  axes;
    std::vector<Point> points;
    sweepPoints(args, axes, points);
    bool sweeping = !axes.empty();
    if (args.out) {
        refuse({{sweepFlag(args), sweeping}, {"--every", args.every != 1}}, "",
               " cannot be combined with --out, which writes every frame of one render");
    }
    NumberFormat fmt = numberFormat(args);

    // the voices and the effect: everything a render of the instrument compiles
    uint64_t  started = nowNanos();
    PolyProbe poly(args.file, args.importDirs, args.sr, args.compile.isDouble, args.optLevel, args.nvoices, args.effect,
                   args.voiceStopLevel);
    double    compileSeconds = secondsSince(started);
    // an inline effect left out: the render that follows is not the
    // instrument the program declares
    for (const std::string& warning : poly.warnings()) {
        fprintf(stderr, "warning: %s\n", warning.c_str());
    }
    if (args.listParams) {
        writeLine(str(poly.voiceCount()) + " voice(s), " + str(poly.inputs()) + " input(s)/voice, " +
                  str(poly.outputs()) + " output(s), effect: " +
                  (poly.hasEffect() ? "yes (" + str(poly.busOutputs()) + " -> " + str(poly.outputs()) + ")" : "no"));
        printControls("path (per voice)", poly.voiceControls(), fmt);
        return;
    }

    Assignments          fixed    = parseAssignments(args.sets);
    Schedule             schedule = buildSchedule(args);
    std::vector<Clamped> clamped  = checkWrites(args, poly, fixed, schedule, axes);
    size_t               window   = args.render > args.skip ? args.render - args.skip : 0;
    Measures             measures(args, poly.outputs(), window, poly.sampleRate());

    PolyRenderSpec spec;
    spec.frames = args.render;
    spec.block  = args.block;
    // every playing voice receives the excitation, as mydsp_poly::compute does
    spec.input    = parseInputAt(args.input, args.sr, poly.inputs());
    spec.skip     = args.skip;
    spec.schedule = schedule;
    spec.limit    = args.failAbove;
    spec.time     = args.time;
    if (sweeping) {
        PolySweep sweep = {args, poly, spec, fixed, schedule, measures, clamped, fmt, compileSeconds};
        sweep.run(axes, points);
        return;
    }
    for (const auto& set : fixed) {
        poly.setAll(set.first, set.second);
    }
    // created before anything is printed: an extension it cannot write is an
    // error of the command line
    std::unique_ptr<SampleWriter> writer;
    if (args.out) {
        writer.reset(new SampleWriter(*args.out, poly.outputs(), window, args.compile.isDouble, args.sr));
    }
    size_t every   = std::max<size_t>(args.every, 1);
    bool   dumping = !args.quiet && args.format == Format::Csv && writer == nullptr;
    if (dumping) {
        std::string line = "frame";
        for (size_t ch = 0; ch < poly.outputs(); ch++) {
            line += ",out" + str(ch);
        }
        writeLine(line);
    }
    Channels collected;
    if (measures.needsSamples()) {
        collected.assign(poly.outputs(), std::vector<double>());
    }
    RenderStats stats = poly.render(spec, [&](size_t frame, const std::vector<double>& samples) {
        for (size_t ch = 0; ch < collected.size(); ch++) {
            collected[ch].push_back(samples[ch]);
        }
        if (writer != nullptr) {
            writer->push(samples);
        }
        if (!dumping || (frame - spec.skip) % every != 0) {
            return;
        }
        std::string line = str(frame);
        for (double value : samples) {
            line += ',';
            line += fmt.sample(value);
        }
        writeLine(line);
    });
    if (writer != nullptr) {
        writer->finish();
    }
    // A render that went wrong fails, as a scalar one does, and says where it
    // starts and what had been written and played by then.
    Optional<std::string> failure =
        renderFailure(stats, stats.firstNonFinite(), args.failAbove, args.render, fmt,
                      [&](size_t frame) { return polyFailureContext(frame, fixed, schedule, poly); });
    if (failure) {
        throw Failure(*failure);
    }
    std::vector<std::string> notes    = polySilenceNotes(stats, schedule, spec.input, poly);
    Measured                 measured = measures.measure(stats, collected);
    if (args.format == Format::Json) {
        Json document = documentJson(args);
        document.set("nvoices", args.nvoices);
        document.set("frames", args.render);
        document.set("window", windowJson(stats));
        document.set("active_voices", poly.activeVoiceCount());
        document.set("channels", channelsJson(stats));
        measures.addReduced(document, measured);
        measures.addDescribed(document, measured);
        if (!clamped.empty()) {
            document.set("clamped", clampedJson(clamped));
        }
        if (!notes.empty()) {
            document.set("notes", Json::strings(notes));
        }
        if (stats.timing) {
            document.set("timing", timingJson(*stats.timing, compileSeconds));
        }
        printJson(document);
        return;
    }
    // same rule as the scalar path: under --quiet or --out the statistics are
    // the output, otherwise they annotate a dump
    Sink sink = Sink::beside(!args.quiet && !args.out.has);
    sink.say("# frames=" + str(args.render) + " sr=" + std::to_string(args.sr) + " nvoices=" + str(args.nvoices) +
             " active_voices=" + str(poly.activeVoiceCount()) + " window=" + str(stats.windowStart) + ".." +
             str(stats.windowStart + stats.windowLength) + " (" + str(stats.windowLength) + " frames)");
    sink.sayAll(channelLines(stats, fmt));
    sink.sayAll(measures.lines(measured, fmt));
    sink.sayAll(clampLines(clamped));
    for (const std::string& note : notes) {
        sink.say("# note: " + note);
    }
    if (stats.timing) {
        sink.sayAll(renderTimeLines(compileSeconds, *stats.timing));
    }
}
