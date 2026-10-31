/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This file is part of faustprobe, the offline probe of a Faust program.
 It is distributed under the same license as the Faust tools: see
 COPYING.txt at the root of the repository.
 ************************************************************************/

#include "report.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

// ---------------------------------------------------------------- setup

Compiled compileProgram(const Args& args, bool isDouble)
{
    Compiled compiled;
    if (args.evals.empty()) {
        compiled.factory = Factory::compileFile(args.file, args.importDirs, args.compile.argv(), isDouble, args.optLevel);
        return compiled;
    }
    compiled.eval = std::make_shared<EvalProgram>(readTextFile(args.file), args.evals);
    // named after the file: that is what a control's path starts with
    std::string name = stemOf(args.file);
    try {
        compiled.factory = Factory::compileString(name, args.file, compiled.eval->source(), args.importDirs,
                                                  args.compile.argv(), isDouble, args.optLevel);
    } catch (const Failure& failure) {
        throw Failure(compiled.eval->explain(name, failure.what()));
    }
    return compiled;
}

Compiled compileTimed(const Args& args)
{
    uint64_t started  = nowNanos();
    Compiled compiled = compileProgram(args, args.compile.isDouble);
    compiled.seconds  = secondsSince(started);
    return compiled;
}

std::pair<std::string, double> parseAssignment(const std::string& text)
{
    size_t equal = text.find('=');
    if (equal == std::string::npos) {
        throw Failure("expected PATH=VALUE, got `" + text + "`");
    }
    std::string value = text.substr(equal + 1);
    double      parsed;
    if (!parseDouble(value, parsed)) {
        throw Failure("`" + value + "` is not a number in `" + text + "`");
    }
    return std::make_pair(text.substr(0, equal), parsed);
}

Assignments parseAssignments(const std::vector<std::string>& texts)
{
    Assignments assignments;
    for (const std::string& text : texts) {
        assignments.push_back(parseAssignment(text));
    }
    return assignments;
}

std::vector<Axis> sweepAxes(const Args& args)
{
    std::vector<Axis> axes;
    for (const std::string& text : args.sweeps) {
        axes.push_back(parseAxis(text));
    }
    return axes;
}

std::string sweepFlag(const Args& args)
{
    return args.points.has ? "--points" : "--sweep";
}

void sweepPoints(const Args& args, std::vector<Axis>& axes, std::vector<Point>& points)
{
    if (args.points.has) {
        const std::string& path = *args.points;
        try {
            FILE* file = fopen(path.c_str(), "rb");
            if (file == nullptr) {
                throw Failure(strerror(errno));
            }
            fclose(file);
            parsePoints(readTextFile(path), axes, points);
        } catch (const Failure& failure) {
            throw Failure("--points " + path + ": " + failure.what());
        }
    } else {
        axes   = sweepAxes(args);
        points = cartesian(axes);
    }
}

InputMode parseInput(const std::string& spec)
{
    size_t      colon   = spec.find(':');
    bool        hasTail = colon != std::string::npos;
    std::string head    = spec.substr(0, colon);
    std::string tail    = hasTail ? spec.substr(colon + 1) : "";
    InputMode   mode;
    if (head == "zero" && !hasTail) {
        mode.kind = InputMode::Kind::Zero;
    } else if (head == "impulse" && !hasTail) {
        mode.kind = InputMode::Kind::Impulse;
    } else if (head == "impulse") {
        mode.kind = InputMode::Kind::ImpulseChannel;
        if (!parseSize(tail, mode.channel)) {
            throw Failure("invalid channel in `--in impulse:" + tail + "`");
        }
    } else if (head == "dc" && !hasTail) {
        mode.kind = InputMode::Kind::Dc;
    } else if (head == "white") {
        mode.kind = InputMode::Kind::White;
        if (hasTail) {
            size_t seed;
            if (!parseSize(tail, seed)) {
                throw Failure("invalid seed in `--in white:" + tail + "`");
            }
            mode.seed = seed;
        }
    } else if (head == "sine") {
        if (!hasTail) {
            throw Failure("`--in sine` needs a frequency, e.g. sine:440");
        }
        mode.kind = InputMode::Kind::Sine;
        if (!parseDouble(tail, mode.hz)) {
            throw Failure("invalid frequency in `--in sine:" + tail + "`");
        }
    } else if (head == "file") {
        if (!hasTail) {
            throw Failure("`--in file` needs a path, e.g. file:target.wav");
        }
        // file:PATH or file:PATH:CH: a trailing :N is a channel
        std::string      path = tail;
        Optional<size_t> channel;
        size_t           last = tail.rfind(':');
        size_t           parsed;
        if (last != std::string::npos && parseSize(tail.substr(last + 1), parsed)) {
            path    = tail.substr(0, last);
            channel = parsed;
        }
        return InputMode::fromFile(path, channel);
    } else {
        throw Failure("unknown input mode `" + spec + "`");
    }
    return mode;
}

void checkImpulseChannel(const InputMode& input, size_t inputs)
{
    if (input.kind != InputMode::Kind::ImpulseChannel || input.channel < inputs) {
        return;
    }
    std::string says;
    if (inputs == 0) {
        says = "the program has no input";
    } else if (inputs == 1) {
        says = "the program has one input, channel 0";
    } else {
        says = "the program has " + str(inputs) + " inputs, channels 0 to " + str(inputs - 1);
    }
    throw Failure("--in impulse:" + str(input.channel) + ": " + says);
}

InputMode parseInputAt(const std::string& spec, int sr, size_t inputs)
{
    InputMode input = parseInput(spec);
    checkImpulseChannel(input, inputs);
    if (input.kind == InputMode::Kind::File && input.fileSampleRate && *input.fileSampleRate != sr) {
        fprintf(stderr, "warning: `--in %s` is recorded at %d Hz, the program runs at %d Hz (--sr)\n", spec.c_str(),
                *input.fileSampleRate, sr);
    }
    return input;
}

// With several expressions the columns are attributed by the number of outputs
// of each, which a second, tiny program computes.
std::vector<std::string> outputLabels(const Args& args, const Compiled& compiled, size_t outputs)
{
    if (compiled.eval == nullptr) {
        std::vector<std::string> labels;
        for (size_t ch = 0; ch < outputs; ch++) {
            labels.push_back("out" + str(ch));
        }
        return labels;
    }
    const EvalProgram& eval = *compiled.eval;
    if (eval.exprs().size() == 1) {
        return eval.labels(std::vector<size_t>(1, outputs), outputs);
    }
    std::string              name = stemOf(args.file);
    std::shared_ptr<Factory> factory;
    try {
        factory = Factory::compileString(name, args.file, eval.aritySource(), args.importDirs, args.compile.argv(),
                                         true, 0);
    } catch (const Failure& failure) {
        throw Failure(eval.explain(name, failure.what()));
    }
    Probe      probe(factory, args.sr);
    RenderSpec spec;
    spec.frames     = 1;
    spec.input.kind = InputMode::Kind::Zero;
    std::vector<size_t> arities;
    probe.render(spec, [&arities](size_t, const std::vector<double>& samples) {
        arities.clear();
        for (double count : samples) {
            arities.push_back(static_cast<size_t>(count));
        }
    });
    return eval.labels(arities, outputs);
}

NumberFormat numberFormat(const Args& args)
{
    NumberFormat format;
    if (args.precision) {
        format.precision = Precision::parse(*args.precision);
    }
    format.isDouble = args.compile.isDouble;
    return format;
}

Schedule buildSchedule(const Args& args)
{
    Schedule schedule;
    for (size_t i = 0; i + 1 < args.ats.size(); i += 2) {
        std::pair<size_t, Event> at = parseAt(args.ats[i], args.ats[i + 1]);
        schedule.push(at.first, at.second);
    }
    for (const std::string& text : args.notes) {
        for (const auto& note : parseNote(text)) {
            schedule.push(note.first, note.second);
        }
    }
    for (const std::string& text : args.chords) {
        for (const auto& note : parseChord(text)) {
            schedule.push(note.first, note.second);
        }
    }
    return schedule;
}

// ---------------------------------------------------------------- writes

std::string Clamped::line() const
{
    return "# clamped " + path + ": " + plainNumber(requested) + " -> " + plainNumber(applied);
}

Json Clamped::json() const
{
    return Json::object().set("path", path).set("requested", requested).set("applied", applied);
}

static bool sameBits(double a, double b)
{
    return memcmp(&a, &b, sizeof(double)) == 0;
}

bool Clamped::operator==(const Clamped& other) const
{
    return path == other.path && requested == other.requested && applied == other.applied;
}

double checkValue(const ControlMap& controls, const std::string& query, double value, bool clamp,
                  std::vector<Clamped>& clamped)
{
    Write write = controls.checkWrite(query, value);
    if (!write.inRange()) {
        if (!clamp) {
            throw Failure(write.rangeError(query) + " (--clamp accepts it, clamped to the range)");
        }
        clamped.push_back({write.control->path, value, write.applied});
    }
    return write.applied;
}

void checkPolyValue(const PolyProbe& poly, const std::string& query, double value, bool clamp,
                    std::vector<Clamped>& clamped)
{
    for (const PolyWrite& write : poly.checkWrite(query, value)) {
        if (write.write.inRange()) {
            continue;
        }
        if (!clamp) {
            throw Failure(write.write.rangeError(query) + " " + write.place() +
                          " (--clamp accepts it, clamped to the range)");
        }
        Clamped record = {write.write.control->path, value, write.write.applied};
        // a control written by --set and again by an --at is one clamp
        if (std::find(clamped.begin(), clamped.end(), record) == clamped.end()) {
            clamped.push_back(record);
        }
    }
}

void Clamps::checkAxes(const ControlMap& controls, const std::vector<Axis>& sweep, bool clamp)
{
    for (size_t index = 0; index < sweep.size(); index++) {
        std::vector<Clamped> ofAxis;
        for (double value : sweep[index].values) {
            checkValue(controls, sweep[index].path, value, clamp, ofAxis);
        }
        for (const Clamped& record : ofAxis) {
            axes.push_back(std::make_pair(index, record));
        }
    }
}

std::vector<Clamped> Clamps::all() const
{
    std::vector<Clamped> all = fixed;
    for (const auto& axis : axes) {
        all.push_back(axis.second);
    }
    return all;
}

std::vector<Clamped> Clamps::ofPoint(const Point& point) const
{
    std::vector<Clamped> clamps = fixed;
    for (const auto& axis : axes) {
        if (axis.first < point.assignments.size() &&
            sameBits(point.assignments[axis.first].second, axis.second.requested)) {
            clamps.push_back(axis.second);
        }
    }
    return clamps;
}

Assignments applied(const ControlMap& controls, const Point& point)
{
    Assignments values;
    for (const auto& assignment : point.assignments) {
        double value = assignment.second;
        try {
            value = controls.checkWrite(assignment.first, value).applied;
        } catch (const Failure&) {
        }
        values.push_back(std::make_pair(assignment.first, value));
    }
    return values;
}

Assignments written(const ControlMap& controls, const Assignments& fixed, const Point& point)
{
    Assignments all = fixed;
    all.insert(all.end(), point.assignments.begin(), point.assignments.end());
    Assignments values;
    for (const auto& assignment : all) {
        try {
            Write write = controls.checkWrite(assignment.first, assignment.second);
            values.push_back(std::make_pair(write.control->path, write.applied));
        } catch (const Failure&) {
        }
    }
    return values;
}

void prime(Probe& probe, const Assignments& fixed, const Point& point)
{
    probe.reset();
    for (const auto& assignment : fixed) {
        probe.set(assignment.first, assignment.second);
    }
    for (const auto& assignment : point.assignments) {
        probe.set(assignment.first, assignment.second);
    }
}

// ---------------------------------------------------------------- said

void writeLine(const std::string& line)
{
    fwrite(line.data(), 1, line.size(), stdout);
    fputc('\n', stdout);
}

void Sink::say(const std::string& line) const
{
    if (fStderr) {
        fprintf(stderr, "%s\n", line.c_str());
    } else {
        writeLine(line);
    }
}

void Sink::sayAll(const std::vector<std::string>& lines) const
{
    for (const std::string& line : lines) {
        say(line);
    }
}

static std::string padded(const std::string& text, size_t width, bool left)
{
    std::string padding(text.size() < width ? width - text.size() : 0, ' ');
    return left ? text + padding : padding + text;
}

static std::string controlRow(const std::string& path, const std::string& kind, const std::string& init,
                              const std::string& min, const std::string& max, const std::string& step)
{
    return padded(path, 44, true) + " " + padded(kind, 9, true) + " " + padded(init, 10, false) + " " +
           padded(min, 10, false) + " " + padded(max, 10, false) + " " + padded(step, 10, false);
}

void printControls(const std::string& title, const ControlMap& controls, const NumberFormat& fmt)
{
    writeLine(controlRow(title, "kind", "init", "min", "max", "step"));
    for (const auto& entry : controls.all()) {
        const Control& control = entry.second;
        // a control's numbers live at the program's width
        writeLine(controlRow(control.path, controlKindName(control.kind), fmt.sample(control.init),
                             fmt.sample(control.min), fmt.sample(control.max), fmt.sample(control.step)));
    }
}

std::vector<std::string> channelLines(const RenderStats& stats, const NumberFormat& fmt)
{
    std::vector<std::string> lines;
    for (size_t ch = 0; ch < stats.channels.size(); ch++) {
        const ChannelStats& channel = stats.channels[ch];
        // peak_at comes last, and subnormal only when there is one
        std::string line = "# out" + str(ch) + ": peak=" + fmt.sample(channel.peak) + " rms=" +
                           fmt.computed(channel.rms) + " dc=" + fmt.computed(channel.dc) +
                           " finite=" + (channel.finite ? "yes" : "no") +
                           " peak_at=" + (channel.peakAt ? str(*channel.peakAt) : "none");
        if (channel.subnormalAt) {
            line += " subnormal=" + str(channel.subnormal) + " subnormal_at=" + str(*channel.subnormalAt);
        }
        lines.push_back(line);
    }
    return lines;
}

Json channelsJson(const RenderStats& stats)
{
    Json channels = Json::array();
    for (const ChannelStats& c : stats.channels) {
        channels.push(Json::object()
                          .set("peak", c.peak)
                          .set("rms", c.rms)
                          .set("dc", c.dc)
                          .set("peak_at", c.peakAt)
                          .set("subnormal", c.subnormal)
                          .set("subnormal_at", c.subnormalAt));
    }
    return channels;
}

Json windowJson(const RenderStats& stats)
{
    return Json::object().set("start", stats.windowStart).set("frames", stats.windowLength);
}

Json documentJson(const Args& args)
{
    return Json::object().set("schema_version", 1).set("dsp", args.file).set("sr", args.sr);
}

void describeProgram(Json& document, const Args& args, const std::vector<std::string>* evalLabels,
                     double compileSeconds)
{
    if (evalLabels != nullptr) {
        document.set("eval", Json::strings(*evalLabels));
    }
    if (args.time) {
        document.set("timing", Json::object().set("compile_s", compileSeconds));
    }
}

void printJson(const Json& document)
{
    writeLine(document.pretty());
}

std::vector<std::string> timeLines(double compileSeconds, const Timing& timing,
                                   const std::function<std::string(const WorstBlock&)>& worstName)
{
    std::vector<std::string> lines = {"# time: compile " + humanSeconds(compileSeconds)};
    if (timing.blocks == 0) {
        return lines;
    }
    lines.push_back("# time: compute " + humanSeconds(timing.computeSeconds) + " for " +
                    humanSeconds(timing.audioSeconds()) + " of audio (" + str(timing.frames) + " frames in " +
                    str(timing.blocks) + " block" + (timing.blocks == 1 ? "" : "s") + "): " +
                    threeDigits(timing.realtimeFactor()) + "x real time");
    if (timing.worst) {
        const WorstBlock& worst = *timing.worst;
        lines.push_back("# time: worst block: " + worstName(worst) + ", " + str(worst.frames) + " frames in " +
                        humanSeconds(worst.seconds) + ", " +
                        threeDigits(100.0 * *timing.worstBudgetFraction()) + "% of its " +
                        humanSeconds(timing.budgetSeconds(worst.frames)) + " budget");
    }
    return lines;
}

std::vector<std::string> renderTimeLines(double compileSeconds, const Timing& timing)
{
    return timeLines(compileSeconds, timing, [](const WorstBlock& worst) { return "frame " + str(worst.frame); });
}

Json timingJson(const Timing& timing, const Optional<double>& compileSeconds)
{
    Json json = Json::object()
                    .set("compute_s", timing.computeSeconds)
                    .set("audio_s", timing.audioSeconds())
                    .set("frames", timing.frames)
                    .set("blocks", timing.blocks)
                    .set("realtime_factor", timing.realtimeFactor());
    if (timing.worst) {
        const WorstBlock& worst = *timing.worst;
        json.set("worst_block", Json::object()
                                    .set("frame", worst.frame)
                                    .set("frames", worst.frames)
                                    .set("seconds", worst.seconds)
                                    .set("budget_s", timing.budgetSeconds(worst.frames))
                                    .set("budget_fraction", *timing.worstBudgetFraction()));
    } else {
        json.set("worst_block", Json());
    }
    if (compileSeconds) {
        json.set("compile_s", *compileSeconds);
    }
    return json;
}

void TotalTiming::add(const Optional<Timing>& timing)
{
    if (!timing) {
        return;
    }
    if (fTotal) {
        fTotal.value.absorb(*timing);
    } else {
        fTotal = *timing;
    }
}

std::vector<std::string> TotalTiming::lines(double compileSeconds, size_t renders) const
{
    std::vector<std::string> lines;
    if (!fTotal) {
        return lines;
    }
    if (renders > 1) {
        lines.push_back("# time: " + str(renders) + " renders");
    }
    for (const std::string& line : renderTimeLines(compileSeconds, *fTotal)) {
        lines.push_back(line);
    }
    return lines;
}

std::vector<std::string> silenceNotes(const Probe& probe, const InputMode& input)
{
    std::vector<std::string> notes = {"every output is exactly zero over the window"};
    std::vector<std::string> released;
    for (const auto& entry : probe.controlValues()) {
        ControlKind kind = entry.first->kind;
        if ((kind == ControlKind::Button || kind == ControlKind::CheckButton) && entry.second == 0.0) {
            released.push_back(entry.first->path);
        }
    }
    if (!released.empty()) {
        notes.push_back("buttons and checkboxes at 0: " + join(released, " "));
    }
    if (input.kind == InputMode::Kind::Zero && probe.inputs() > 0) {
        notes.push_back("input is `zero` and the program has " + str(probe.inputs()) + " input(s)");
    }
    return notes;
}

// ---------------------------------------------------------------- failures

Optional<std::string> renderFailure(const RenderStats& stats, const Optional<std::pair<size_t, Located>>& nonFinite,
                                    const Optional<double>& failAbove, size_t frames, const NumberFormat& fmt,
                                    const FrameContext& context)
{
    Optional<std::pair<size_t, Located>> above = stats.firstAbove();
    if (above && (!nonFinite || above.value.second.frame <= nonFinite.value.second.frame)) {
        std::string later;
        if (nonFinite) {
            later = "\n  the render turns non-finite at frame " + str(nonFinite.value.second.frame) + ", out" +
                    str(nonFinite.value.first) + " (" + nonFiniteName(nonFinite.value.second.value) + ")";
        }
        const Located& located = above.value.second;
        return std::string("a sample exceeds --fail-above " + plainNumber(failAbove.has ? *failAbove : 0.0) +
                           "\n  first: frame " + str(located.frame) + ", out" + str(above.value.first) + " = " +
                           fmt.sample(located.value) + later + context(located.frame));
    }
    if (!nonFinite) {
        return Optional<std::string>();
    }
    const Located& located = nonFinite.value.second;
    return std::string("render produced non-finite samples\n  first: frame " + str(located.frame) + ", out" +
                       str(nonFinite.value.first) + " (" + nonFiniteName(located.value) + "); " +
                       str(stats.nonFiniteFrames) + " of " + str(frames) + " frames affected" +
                       context(located.frame));
}

namespace {

// The value of each written control at a frame, and the last scheduled write
// before it.
struct WrittenBy {
    Assignments           then;
    Optional<std::string> lastEvent;

    void record(const std::string& path, double value)
    {
        for (auto& entry : then) {
            if (entry.first == path) {
                entry.second = value;
                return;
            }
        }
        then.push_back(std::make_pair(path, value));
    }

    void scheduled(size_t at, const std::string& path, double value)
    {
        record(path, value);
        lastEvent = "frame " + str(at) + ", " + path + "=" + plainNumber(value);
    }

    std::string text() const
    {
        std::string out;
        if (then.empty()) {
            out = "\n  controls then: all at their initial values";
        } else {
            std::vector<std::string> listed;
            for (const auto& entry : then) {
                listed.push_back(entry.first + "=" + plainNumber(entry.second));
            }
            out = "\n  controls written by then: " + join(listed, " ");
        }
        if (lastEvent) {
            out += "\n  last scheduled write before it: " + *lastEvent;
        }
        return out;
    }
};

}  // namespace

std::string failureContext(size_t frame, const Assignments& writtenBefore, const Schedule& schedule,
                           const ControlMap& controls)
{
    WrittenBy by;
    for (const auto& entry : writtenBefore) {
        by.record(entry.first, entry.second);
    }
    for (const ParamWrite& write : schedule.paramWrites()) {
        if (write.frame > frame) {
            break;
        }
        try {
            Write checked = controls.checkWrite(write.path, write.value);
            by.scheduled(write.frame, checked.control->path, checked.applied);
        } catch (const Failure&) {
        }
    }
    return by.text();
}

std::string polyFailureContext(size_t frame, const Assignments& fixed, const Schedule& schedule, const PolyProbe& poly)
{
    // where a broadcast write lands: every voice's control, the effect's, or both
    auto landing = [&poly](const std::string& query, double value) {
        Assignments lands;
        try {
            for (const PolyWrite& write : poly.checkWrite(query, value)) {
                lands.push_back(std::make_pair(write.write.control->path, write.write.applied));
            }
        } catch (const Failure&) {
        }
        return lands;
    };
    WrittenBy by;
    for (const auto& entry : fixed) {
        for (const auto& land : landing(entry.first, entry.second)) {
            by.record(land.first, land.second);
        }
    }
    for (const ParamWrite& write : schedule.paramWrites()) {
        if (write.frame > frame) {
            break;
        }
        for (const auto& land : landing(write.path, write.value)) {
            by.scheduled(write.frame, land.first, land.second);
        }
    }
    std::string text = by.text();
    auto        held = schedule.notesHeldAt(frame);
    if (held.empty()) {
        text += "\n  notes held then: none";
    } else {
        std::vector<std::string> listed;
        for (const auto& note : held) {
            listed.push_back(std::to_string(note.first) + " (on at frame " + str(note.second) + ")");
        }
        text += "\n  notes held then: " + join(listed, ", ");
    }
    return text;
}

// ---------------------------------------------------------------- measures

Measures::Measures(const Args& args, size_t outputs, size_t window, int sampleRate)
    : fF0(args.f0), fSampleRate(sampleRate)
{
    if (args.reduce) {
        fReduction = parseReduction(*args.reduce);
    }
    fSettings.hopSeconds = args.describeHop;
    fSettings.fft        = args.describeFft;
    if (args.describe) {
        fDescriptors = parseDescriptors(*args.describe);
        checkDescriptors(fDescriptors, fSettings, outputs, window, fSampleRate);
    }
}

Json Measures::reductionJson() const
{
    return fReduction ? Json(reductionName(*fReduction)) : Json();
}

bool Measures::needsSamples() const
{
    if (!fDescriptors.empty()) {
        return true;
    }
    return fReduction && (*fReduction == Reduction::F0 || *fReduction == Reduction::Sfdr ||
                          *fReduction == Reduction::Thd);
}

std::vector<std::string> Measures::header(size_t outputs) const
{
    std::vector<std::string> header;
    for (size_t ch = 0; ch < outputs; ch++) {
        if (fReduction) {
            header.push_back(std::string(reductionName(*fReduction)) + "_out" + str(ch));
        } else if (fDescriptors.empty()) {
            header.push_back("peak_out" + str(ch));
            header.push_back("rms_out" + str(ch));
            header.push_back("dc_out" + str(ch));
        }
    }
    for (const Descriptor& descriptor : fDescriptors) {
        header.push_back(descriptor.name());
    }
    return header;
}

static double reduceChannel(Reduction reduction, const RenderStats& stats, size_t ch, const Channels& collected,
                            double sr, const Optional<double>& f0)
{
    double fundamental = f0.has ? *f0 : 0.0;
    switch (reduction) {
        case Reduction::Rms:
            return stats.channels[ch].rms;
        case Reduction::Peak:
            return stats.channels[ch].peak;
        case Reduction::Energy:
            return stats.channels[ch].rms * stats.channels[ch].rms * double(stats.windowLength);
        case Reduction::Dc:
            return stats.channels[ch].dc;
        case Reduction::F0:
            return dominantFrequency(collected[ch], sr);
        case Reduction::Sfdr:
            return sfdrDb(collected[ch], sr, fundamental);
        default:
            return thdDb(collected[ch], sr, fundamental);
    }
}

Measured Measures::measure(const RenderStats& stats, const Channels& collected) const
{
    Measured measured;
    if (fReduction) {
        std::vector<double> values;
        for (size_t ch = 0; ch < stats.channels.size(); ch++) {
            values.push_back(reduceChannel(*fReduction, stats, ch, collected, fSampleRate, fF0));
        }
        measured.reduced = values;
    }
    if (!fDescriptors.empty()) {
        measured.described = describe(collected, fSampleRate, fDescriptors, fSettings);
    }
    return measured;
}

std::vector<std::string> Measures::row(const Measured& measured, const RenderStats& stats,
                                       const NumberFormat& fmt) const
{
    std::vector<std::string> row;
    if (measured.reduced && fReduction) {
        // a peak is a sample's magnitude; the others are computed
        for (double value : *measured.reduced) {
            row.push_back(*fReduction == Reduction::Peak ? fmt.sample(value) : fmt.computed(value));
        }
    } else if (fDescriptors.empty()) {
        for (const ChannelStats& channel : stats.channels) {
            row.push_back(fmt.sample(channel.peak));
            row.push_back(fmt.computed(channel.rms));
            row.push_back(fmt.computed(channel.dc));
        }
    }
    for (double value : measured.described) {
        row.push_back(fmt.computed(value));
    }
    return row;
}

bool Measures::addReduced(Json& entry, const Measured& measured) const
{
    if (!fReduction || !measured.reduced) {
        return false;
    }
    entry.set(reductionName(*fReduction), Json::numbers(*measured.reduced));
    return true;
}

void Measures::addDescribed(Json& entry, const Measured& measured) const
{
    if (fDescriptors.empty()) {
        return;
    }
    Json object = Json::object();
    for (size_t k = 0; k < fDescriptors.size(); k++) {
        object.set(fDescriptors[k].name(), measured.described[k]);
    }
    entry.set("describe", object);
}

static const char* whyNan(const Descriptor& descriptor)
{
    switch (descriptor.kind) {
        case Descriptor::Kind::Decay:
            return "not reached before the window ends (or the window is silent)";
        case Descriptor::Kind::Centroid:
            return "its stretch holds no energy above the second bin";
        case Descriptor::Kind::Width:
            return "both outputs are silent over its stretch";
        default:
            return "the window is silent";
    }
}

std::vector<std::string> Measures::lines(const Measured& measured, const NumberFormat& fmt) const
{
    std::vector<std::string> lines;
    if (fDescriptors.empty()) {
        return lines;
    }
    std::vector<std::string> pairs;
    for (size_t k = 0; k < fDescriptors.size(); k++) {
        pairs.push_back(fDescriptors[k].name() + "=" + fmt.computed(measured.described[k]));
    }
    lines.push_back("# describe " + join(pairs, " "));
    for (size_t k = 0; k < fDescriptors.size(); k++) {
        if (std::isnan(measured.described[k])) {
            lines.push_back("# note: " + fDescriptors[k].name() + " is NaN: " + whyNan(fDescriptors[k]));
        }
    }
    return lines;
}

std::vector<std::string> Measures::sweepNotes(const std::vector<Measured>& all) const
{
    std::vector<std::string> notes;
    for (size_t k = 0; k < fDescriptors.size(); k++) {
        size_t count = 0;
        for (const Measured& measured : all) {
            if (std::isnan(measured.described[k])) {
                count++;
            }
        }
        if (count > 0) {
            notes.push_back("# note: " + fDescriptors[k].name() + " is NaN at " + str(count) + " of " +
                            str(all.size()) + " point(s): " + whyNan(fDescriptors[k]));
        }
    }
    return notes;
}
