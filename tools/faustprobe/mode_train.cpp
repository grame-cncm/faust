/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This file is part of faustprobe, the offline probe of a Faust program.
 It is distributed under the same license as the Faust tools: see
 COPYING.txt at the root of the repository.
 ************************************************************************/

// --train and --fd-check: the sequence is the writes checked, the grid when
// --sweep asks for one, the gradient checked at the start, the descent, its
// summary, the gradient checked at the end.

#include <algorithm>
#include <cmath>

#include "report.h"

namespace {

// What a host loop says: the lines as they come, a descent being watched; the
// JSON document is printed once, at the end or with the failure.
class Report {
   public:
    // The form of the output comes from --format.
    explicit Report(const Args& args) : fArgs(args), fJson(args.format == Format::Json), fTrain(Json::object()) {}

    bool asJson() const { return fJson; }

    // Lines are the output of the text form only.
    void say(const std::string& line) const
    {
        if (!fJson) {
            writeLine(line);
        }
    }
    void sayAll(const std::vector<std::string>& lines) const
    {
        for (const std::string& line : lines) {
            say(line);
        }
    }
    // A field of the document's train object.
    void insert(const std::string& key, const Json& value) { fTrain.set(key, value); }

    // Prints the document, under --format json.
    void finish() const
    {
        if (fJson) {
            printJson(Json(documentJson(fArgs)).set("train", fTrain));
        }
    }

   private:
    const Args& fArgs;
    bool        fJson;
    Json        fTrain;
};

// What is said of one --fd-check.
struct FdReport {
    std::vector<std::string> lines;
    Json                     json;
    Optional<std::string>    failure;
};

}  // namespace

// One --fd-check at 'place', start or end: its lines, its JSON, and the error when a
// lane departs from the finite differences.
static FdReport fdCheckReport(const Args& args, const std::string& place, const std::vector<FdCheck>& checks)
{
    std::string tag   = place == "start" ? "" : " " + place;
    double      worst = 0.0;
    FdReport    report;
    Json        entries = Json::array();
    for (const FdCheck& check : checks) {
        // at the end of a descent the gradient is small, which is the point:
        // six decimals would print it as zero; a one-sided difference is named
        std::string side =
            check.scheme == FdScheme::Central ? "" : " (" + std::string(fdSchemeName(check.scheme)) + ", at a bound)";
        if (place == "start") {
            report.lines.push_back("# fd-check " + check.path + ": rad " + fixed(check.rad, 6) + " fd " +
                                   fixed(check.fd, 6) + " relative error " + scientific(check.relativeError, 2) + side);
        } else {
            report.lines.push_back("# fd-check" + tag + " " + check.path + ": rad " + scientific(check.rad, 6) +
                                   " fd " + scientific(check.fd, 6) + " relative error " +
                                   scientific(check.relativeError, 2) + side);
        }
        // a NaN error is the worst there is, and max would drop it
        worst = std::isnan(check.relativeError) || std::isnan(worst) ? NAN : std::max(worst, check.relativeError);
        entries.push(Json::object()
                         .set("path", check.path)
                         .set("rad", check.rad)
                         .set("fd", check.fd)
                         .set("fd_plain", check.fdPlain)
                         .set("relative_error", check.relativeError)
                         .set("scheme", fdSchemeName(check.scheme)));
    }
    report.lines.push_back("# fd-check" + tag + ": block " + str(args.block) + " frames, step " +
                           plainNumber(args.fdStep) + ", worst relative error " + scientific(worst, 2) +
                           " (tolerance " + plainNumber(args.fdTolerance) + ")");
    bool passes = worst <= args.fdTolerance;
    report.json = Json::object()
                      .set("block", args.block)
                      .set("step", args.fdStep)
                      .set("tolerance", args.fdTolerance)
                      .set("worst_relative_error", worst)
                      .set("passes", passes)
                      .set("checks", entries);
    if (!passes) {
        report.failure = "a gradient lane departs from finite differences by " + scientific(worst, 2) + " at the " +
                         place + " of the descent, above --fd-tolerance " + plainNumber(args.fdTolerance);
    }
    return report;
}

// What a host loop does not take.
static void refuseFlags(const Args& args)
{
    refuse({{"--reduce", args.reduce.has},
            {"--describe", args.describe.has},
            {"--points", args.points.has},
            {"--at", !args.ats.empty()},
            {"--bargraphs", args.bargraphs},
            {"--protocol impulse-test", args.protocol == ProtocolKind::ImpulseTest},
            {"--format ir", args.format == Format::Ir},
            {"--out", args.out.has},
            {"--fail-above", args.failAbove.has},
            {"--compare/--ref/--check", verificationRequested(args)},
            {"--freqresp", args.freqresp.has}},
           "", " cannot be combined with --train / --fd-check");
}

// The axes of a grid of starting points: a control, and the values it takes.
typedef std::vector<std::pair<std::string, std::vector<double>>> GridAxes;

// Checks --set and the values of --sweep against their ranges, says the
// clamps, and returns the axes with the values the grid will use.
static GridAxes checkWrites(const Args& args, const std::shared_ptr<Factory>& factory, Report& report, size_t& inputs)
{
    std::vector<Clamped> clamped;
    GridAxes             axes;
    Probe                probe(factory, args.sr);
    // parsed first, then checked: of a malformed --set and one out of range,
    // the malformed one is reported
    for (const auto& set : parseAssignments(args.sets)) {
        checkValue(probe.controls(), set.first, set.second, args.clamp, clamped);
    }
    for (const Axis& axis : sweepAxes(args)) {
        std::vector<double> values;
        for (double value : axis.values) {
            values.push_back(checkValue(probe.controls(), axis.path, value, args.clamp, clamped));
        }
        axes.push_back(std::make_pair(axis.path, values));
    }
    if (!clamped.empty()) {
        Json json = Json::array();
        for (const Clamped& clamp : clamped) {
            report.say(clamp.line());
            json.push(clamp.json());
        }
        report.insert("clamped", json);
    }
    inputs = probe.inputs();
    return axes;
}

// Grid, then descent: --sweep over trained controls gives the loss of one block
// at every point, and the descent leaves from the best.
static void gridThenStart(const Args& args, const std::shared_ptr<Factory>& factory, TrainSpec& spec,
                          const GridAxes& axes, const NumberFormat& fmt, Report& report)
{
    TrainGrid grid   = trainGrid(factory, args.sr, spec, axes);
    Json      points = Json::array();
    for (size_t index = 0; index < grid.points.size(); index++) {
        const auto&              point = grid.points[index];
        std::vector<std::string> at;
        Json                     set = Json::object();
        for (size_t k = 0; k < grid.paths.size(); k++) {
            at.push_back(grid.paths[k] + "=" + plainNumber(point.first[k]));
            set.set(grid.paths[k], point.first[k]);
        }
        report.say("# grid " + join(at, " ") + " loss=" + fmt.loss(point.second) +
                   (index == grid.best ? " (best)" : ""));
        points.push(Json::object().set("set", set).set("loss", point.second));
    }
    report.say("# grid: " + str(grid.points.size()) + " points, one block of " + str(args.block) +
               " frames each; the descent starts from the best");
    report.insert("grid", Json::object().set("points", points).set("best", grid.best));
    // after the --set values: on a control given both, the grid decides
    for (const auto& assignment : grid.bestAssignments()) {
        spec.sets.push_back(assignment);
    }
}

// What being kept in its range did to a control; empty if it never met a bound.
static std::string boundText(const BoundStats& stats, size_t blocks)
{
    std::vector<std::string> parts;
    auto part = [&](Bound bound, size_t count) {
        if (count > 0) {
            parts.push_back(std::string("on its ") + boundName(bound) + " bound for " + str(count) + " of " +
                            str(blocks) + " blocks, " +
                            (stats.endsOn == bound ? "the last one included" : "not the last one"));
        }
    };
    part(Bound::Lower, stats.onLower);
    part(Bound::Upper, stats.onUpper);
    return join(parts, "; ");
}

// What is said of a finished descent: where each control ended and what its
// range did to it, the loss, and the facts a reader would otherwise miss.
static void summarize(const Args& args, const Trained& trained, const NumberFormat& fmt, Report& report)
{
    std::vector<std::string> notes, stopped;
    Json                     trainedJson = Json::array();
    for (size_t k = 0; k < trained.paths.size(); k++) {
        const BoundStats& bounds = trained.bounds[k];
        std::string       text   = boundText(bounds, args.blocks);
        report.say("# trained " + trained.paths[k] + "=" + fmt.computed(trained.values[k]) +
                   (text.empty() ? "" : " (" + text + ")"));
        if (bounds.endsOn != Bound::None) {
            stopped.push_back(trained.paths[k]);
        }
        trainedJson.push(Json::object()
                             .set("path", trained.paths[k])
                             .set("value", trained.values[k])
                             .set("min", trained.ranges[k].first)
                             .set("max", trained.ranges[k].second)
                             .set("blocks_on_lower", bounds.onLower)
                             .set("blocks_on_upper", bounds.onUpper)
                             .set("ends_on", bounds.endsOn == Bound::None ? Json() : Json(boundName(bounds.endsOn))));
    }
    report.say("# loss: block 1 " + scientific(trained.firstLoss, 6) + ", block " + str(args.blocks) + " " +
               scientific(trained.lastLoss, 6));
    report.say("# loss: minimum " + scientific(trained.minLoss, 6) + " at block " + str(trained.minLossBlock));
    if (!stopped.empty()) {
        notes.push_back("a control that ends on a bound is stopped, not converged: " + join(stopped, " "));
    }
    // a ratio means something for a positive loss only
    if (trained.minLoss > 0.0 && trained.lastLoss > 10.0 * trained.minLoss) {
        std::vector<std::string> then;
        for (size_t k = 0; k < trained.paths.size(); k++) {
            then.push_back(trained.paths[k] + "=" + fmt.computed(trained.valuesAtMin[k]));
        }
        notes.push_back("the last loss is " + threeDigits(trained.lastLoss / trained.minLoss) +
                        " times the minimum, which block " + str(trained.minLossBlock) + " reached with " +
                        join(then, " "));
    }
    for (const std::string& note : notes) {
        report.say("# note: " + note);
    }
    report.insert("trained", trainedJson);
    report.insert("loss", Json::object()
                              .set("first", trained.firstLoss)
                              .set("last", trained.lastLoss)
                              .set("min", trained.minLoss)
                              .set("min_block", trained.minLossBlock)
                              .set("values_at_min", Json::numbers(trained.valuesAtMin)));
    if (!notes.empty()) {
        report.insert("notes", Json::strings(notes));
    }
}

// See the top of this file.
void runTrain(const Args& args)
{
    if (args.train.empty()) {
        throw Failure("--fd-check needs the controls to check: --train CONTROLS");
    }
    refuseFlags(args);
    bool fdAtStart = args.fdCheck && (*args.fdCheck == FdWhere::Start || *args.fdCheck == FdWhere::Both);
    bool fdAtEnd   = args.fdCheck && (*args.fdCheck == FdWhere::End || *args.fdCheck == FdWhere::Both);
    if (fdAtEnd && args.blocks == 0) {
        throw Failure("--fd-check=end checks the trained values: it needs a descent, --blocks > 0");
    }
    NumberFormat                    fmt      = numberFormat(args);
    Compiled                        compiled = compileTimed(args);
    const std::shared_ptr<Factory>& factory  = compiled.factory;
    Report                          report(args);

    size_t   inputs = 0;
    GridAxes axes   = checkWrites(args, factory, report, inputs);

    TrainSpec spec;
    spec.params        = args.train;
    spec.lossLane      = args.lossLane;
    spec.firstGradLane = args.gradLane;
    spec.optimizer     = args.optimizer;
    spec.lr            = args.lr;
    spec.block         = args.block;
    spec.blocks        = args.blocks;
    spec.input         = parseInputAt(args.input, args.sr, inputs);
    spec.resetPerBlock = args.resetPerBlock;
    spec.sets          = parseAssignments(args.sets);
    report.insert("options", Json::object()
                                 .set("optimizer", args.optimizer == OptimizerKind::Adam ? "adam" : "sgd")
                                 .set("lr", args.lr)
                                 .set("block", args.block)
                                 .set("blocks", args.blocks)
                                 .set("reset_per_block", args.resetPerBlock));
    if (!axes.empty()) {
        gridThenStart(args, factory, spec, axes, fmt, report);
    }

    Json fdReports = Json::object();
    if (fdAtStart) {
        FdReport fd = fdCheckReport(args, "start", fdCheck(factory, args.sr, spec, args.fdStep, nullptr));
        report.sayAll(fd.lines);
        fdReports.set("start", fd.json);
        if (fd.failure) {
            report.insert("fd_check", fdReports);
            report.finish();
            throw Failure(*fd.failure);
        }
    }
    if (args.blocks == 0) {
        if (!fdReports.empty()) {
            report.insert("fd_check", fdReports);
        }
        if (args.time) {
            Timing none = BlockTimer(double(args.sr)).finish();
            report.sayAll(timeLines(compiled.seconds, none, [](const WorstBlock&) { return std::string(); }));
            report.insert("timing", Json::object().set("compile_s", compiled.seconds));
        }
        report.finish();
        return;
    }

    // the rows printed as they come (every --every blocks, and the last), or
    // kept for the JSON document
    bool   headerDone = false;
    Json   rows       = Json::array();
    size_t every      = std::max<size_t>(args.every, 1);
    auto   onStep     = [&](const TrainStep& step) {
        if (step.block % every != 0 && step.block != args.blocks) {
            return;
        }
        if (report.asJson()) {
            rows.push(Json::object()
                          .set("block", step.block)
                          .set("loss", step.loss)
                          .set("values", Json::numbers(step.params))
                          .set("grads", Json::numbers(step.grads)));
            return;
        }
        if (!headerDone) {
            std::string header = "block,loss," + join(spec.params, ",");
            if (args.trainVerbose) {
                for (const std::string& param : spec.params) {
                    header += ",grad_" + param;
                }
            }
            writeLine(header);
            headerDone = true;
        }
        std::vector<std::string> fields;
        for (double value : step.params) {
            fields.push_back(fmt.computed(value));
        }
        if (args.trainVerbose) {
            for (double grad : step.grads) {
                fields.push_back(fmt.loss(grad));
            }
        }
        writeLine(str(step.block) + "," + fmt.loss(step.loss) + "," + join(fields, ","));
    };
    Trained trained;
    try {
        trained = train(factory, args.sr, spec, onStep);
    } catch (const Failure&) {
        // the rows up to the block that failed are the evidence
        report.insert("rows", rows);
        report.finish();
        throw;
    }
    report.insert("rows", rows);
    summarize(args, trained, fmt, report);

    // A descent is finished where the gradient is small *and* right.
    Optional<std::string> failure;
    if (fdAtEnd) {
        FdReport fd = fdCheckReport(args, "end", fdCheck(factory, args.sr, spec, args.fdStep, &trained.values));
        report.sayAll(fd.lines);
        fdReports.set("end", fd.json);
        failure = fd.failure;
    }
    if (!fdReports.empty()) {
        report.insert("fd_check", fdReports);
    }
    if (args.time) {
        report.sayAll(timeLines(compiled.seconds, trained.timing, [&args](const WorstBlock& worst) {
            return "block " + str(worst.frame / std::max<size_t>(args.block, 1) + 1);
        }));
        report.insert("timing", timingJson(trained.timing, compiled.seconds));
    }
    report.finish();
    if (failure) {
        throw Failure(*failure);
    }
}
