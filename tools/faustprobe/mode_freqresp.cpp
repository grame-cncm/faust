/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This file is part of faustprobe, the offline probe of a Faust program.
 It is distributed under the same license as the Faust tools: see
 COPYING.txt at the root of the repository.
 ************************************************************************/

// --freqresp: the frequency response of a linear program from one impulse
// response, after three renders that check that it is one. With --sweep, one
// response per point, each checked; nothing is printed before every point has
// been measured: a family with a member that is not a frequency response is
// refused whole, with the point that broke.

#include <algorithm>
#include <cmath>

#include "report.h"

namespace {

struct PointResponse {
    Assignments                                    set;
    RenderStats                                    stats;
    std::vector<std::pair<Property, double>>       deviations;
    std::vector<std::vector<FreqPoint>>            responses;
    std::vector<Optional<double>>                  tails;

    std::string label() const
    {
        std::vector<std::string> parts;
        for (const auto& value : set) {
            parts.push_back(value.first + "=" + plainNumber(value.second));
        }
        return join(parts, " ");
    }

    std::string tag() const { return set.empty() ? "" : " [" + label() + "]"; }

    // What is said of a response that was cut while it rang.
    std::vector<std::string> notes(size_t frames) const
    {
        std::vector<std::string> notes;
        for (size_t output = 0; output < tails.size(); output++) {
            if (tails[output] && *tails[output] > kRinging) {
                notes.push_back((set.empty() ? "" : "[" + label() + "] ") + "out" + str(output) +
                                " is still ringing " + str(frames) +
                                " frames after the impulse: what -n cut off is of the order of the last tenth's "
                                "share, and near a resonance the magnitude is off by about its square root (" +
                                threeDigits(100.0 * sqrt(*tails[output])) + "%); raise -n");
            }
        }
        return notes;
    }
};

class Family {
   public:
    explicit Family(const Args& args) : fArgs(args), fFmt(numberFormat(args))
    {
        const std::string spec = args.freqresp.has ? *args.freqresp : "";
        refuseFlags();
        fGrid = FreqGrid::parse(spec, double(args.sr));
        if (args.linearityTolerance) {
            fTolerance = *args.linearityTolerance;
            if (!(fTolerance >= 0.0 && std::isfinite(fTolerance))) {
                throw Failure("--linearity-tolerance must be a non-negative number");
            }
        } else {
            fTolerance = defaultLinearityTolerance(args.compile.isDouble);
        }
        if (args.render < 4) {
            throw Failure("--freqresp needs a window of at least 4 frames (-n) for its linearity checks");
        }
        fCompiled = compileTimed(args);
        fProbe.reset(new Probe(fCompiled.factory, args.sr));
        if (fProbe->inputs() == 0) {
            throw Failure("--freqresp measures the response to an input, and the program has none");
        }
        // The excitation is an impulse, on every input or on one: a transfer
        // function is a response to that and to nothing else.
        InputMode input = parseInput(args.input);
        checkImpulseChannel(input, fProbe->inputs());
        if (input.kind == InputMode::Kind::ImpulseChannel) {
            fChannel = input.channel;
        } else if (input.kind != InputMode::Kind::Impulse) {
            throw Failure("--freqresp measures an impulse response: `--in " + args.input +
                          "` is not `impulse` or `impulse:CH`");
        }
        // Everything that will be written is checked before any render.
        fFixed = parseAssignments(args.sets);
        for (const auto& set : fFixed) {
            checkValue(fProbe->controls(), set.first, set.second, args.clamp, fClamps.fixed);
        }
        fAxes = sweepAxes(args);
        fClamps.checkAxes(fProbe->controls(), fAxes, args.clamp);
        fLabels = outputLabels(args, fCompiled, fProbe->outputs());
        fHz     = fGrid.frequencies();
        fShift  = shiftFor(args.render);
        fPoints = cartesian(fAxes);
    }

    void run()
    {
        std::vector<PointResponse> measured;
        TotalTiming                totalTiming;
        for (const Point& point : fPoints) {
            measured.push_back(measure(point));
            totalTiming.add(measured.back().stats.timing);
        }
        if (fArgs.format == Format::Json) {
            json(measured);
            return;
        }
        if (!fArgs.quiet) {
            rows(measured);
        }
        annotations(measured, totalTiming);
    }

   private:
    const Args&            fArgs;
    NumberFormat           fFmt;
    Compiled               fCompiled;
    std::unique_ptr<Probe> fProbe;
    FreqGrid               fGrid;
    std::vector<double>    fHz;
    double                 fTolerance = 0.0;
    size_t                 fShift     = 1;
    Optional<size_t>       fChannel;
    Assignments            fFixed;
    std::vector<Axis>      fAxes;
    Clamps                 fClamps;
    std::vector<std::string> fLabels;
    std::vector<Point>     fPoints;

    void refuseFlags() const
    {
        const Args& args = fArgs;
        struct Why {
            const char* flag;
            const char* why;
            bool        given;
        };
        const Why table[] = {
            {"--reduce", "the response is the reduction", args.reduce.has},
            {"--describe", "the response is the reduction", args.describe.has},
            {"--points", "a family of curves is a --sweep", args.points.has},
            {"--at", "a control that changes during the response makes the program time-varying", !args.ats.empty()},
            {"--note/--chord", "they drive the polyphonic wrapper", !args.notes.empty() || !args.chords.empty()},
            {"--skip", "the transform is that of the whole response, from frame 0", args.skip != 0},
            {"--every", "the rows are frequencies, not frames", args.every != 1},
            {"--bargraphs", "the rows are frequencies, not frames", args.bargraphs},
            {"--out", "a plain render writes the impulse response", args.out.has},
            {"--fail-above", "it gates a plain render", args.failAbove.has},
            {"--compare/--ref/--check", "they look at the samples of a plain render", verificationRequested(args)},
            {"--format ir", "`.ir` holds frames", args.format == Format::Ir},
        };
        for (const Why& entry : table) {
            if (entry.given) {
                throw Failure(std::string(entry.flag) + " cannot be combined with --freqresp: " + entry.why);
            }
        }
    }

    // One render per excitation, each from a cleared instance: --settle frames
    // of silence, then the impulses, the window being the -n frames that follow.
    RenderStats renderTaps(const Point& point, const std::vector<std::pair<size_t, double>>& taps, bool time,
                           Samples& samples)
    {
        prime(*fProbe, fFixed, point);
        RenderSpec spec;
        spec.frames     = fArgs.settle + fArgs.render;
        spec.block      = fArgs.block;
        spec.input.kind = InputMode::Kind::Impulses;
        spec.input.only = fChannel;
        for (const auto& tap : taps) {
            spec.input.taps.push_back(std::make_pair(fArgs.settle + tap.first, tap.second));
        }
        spec.skip = fArgs.settle;
        spec.time = time;
        return fProbe->collect(spec, samples);
    }

    PointResponse measure(const Point& point)
    {
        PointResponse response;
        response.set   = applied(fProbe->controls(), point);
        std::string at = response.set.empty() ? "" : "at `" + response.label() + "`, ";
        Samples     h;
        response.stats = renderTaps(point, {{0, 1.0}}, fArgs.time, h);
        auto first     = response.stats.firstNonFinite();
        if (first) {
            throw Failure(at + "the impulse response is not finite\n  first: frame " +
                          str(first.value.second.frame) + ", out" + str(first.value.first) + " (" +
                          nonFiniteName(first.value.second.value) + "); " + str(response.stats.nonFiniteFrames) +
                          " of " + str(fArgs.render) + " frames affected");
        }
        // is there a transfer function to measure?
        for (Property property : allProperties()) {
            Samples answer;
            renderTaps(point, propertyTaps(property, fShift), false, answer);
            Tolerance tolerance;
            tolerance.rel         = fTolerance;
            Comparison comparison = compare(answer, propertyExpected(property, h, fShift), tolerance, nullptr);
            auto       beyond     = comparison.firstBeyond();
            if (beyond) {
                throw Failure(notAResponse(point, at, property, beyond.value.first, beyond.value.second, response.stats));
            }
            double worst = 0.0;
            for (const auto& channel : comparison.channels) {
                worst = std::max(worst, channel.second.maxRel);
            }
            response.deviations.push_back(std::make_pair(property, worst));
        }
        for (const std::vector<double>& channel : h.channels) {
            response.responses.push_back(frequencyResponse(channel, double(fArgs.sr), fHz));
            response.tails.push_back(tailEnergyFraction(channel));
        }
        return response;
    }

    // The refusal of a program that is not linear and time-invariant at a
    // point: the property it breaks, where, and what can be established of the cause.
    std::string notAResponse(const Point& point, const std::string& at, Property property, size_t output,
                             const Disagreement& d, const RenderStats& stats)
    {
        std::string error =
            "--freqresp: " + at +
            "the program is not linear and time-invariant: its impulse response has no transfer function to give\n  " +
            propertyViolation(property, fArgs.settle, fShift) + "\n  first: frame " + str(d.frame) + ", out" +
            str(output) + ": " + fFmt.sample(d.value) + " where " + fFmt.sample(d.reference) +
            " was expected (tolerance " + scientific(fTolerance) + " of the peak)\n  usual cause: " +
            propertyUsualCause(property);
        // what the program says to silence: said when it is of a size to
        // explain the refusal, which the 1e-20 a reverberator injects is not
        Samples     unused;
        RenderStats silence = renderTaps(point, {}, false, unused);
        size_t      loudest = 0;
        double      peak    = 0.0;
        for (size_t ch = 0; ch < silence.channels.size(); ch++) {
            if (silence.channels[ch].peak > peak) {
                loudest = ch;
                peak    = silence.channels[ch].peak;
            }
        }
        if (peak > fTolerance * stats.channels[loudest].peak) {
            error += "\n  with no input at all the program outputs a signal (out" + str(loudest) + " peaks at " +
                     fFmt.sample(peak) + "): it is not a function of its input alone";
        }
        if (property == Property::TimeInvariance) {
            error +=
                "\n  a smoothed control (si.smoo) is such an envelope until it has settled: --settle N renders N "
                "frames of silence before the impulse";
        }
        error +=
            "\n  a program that is not linear is measured at one level and one frequency at a time: --in sine:HZ "
            "--skip N --reduce rms";
        return error;
    }

    void json(const std::vector<PointResponse>& measured) const
    {
        Json runs = Json::array();
        for (size_t i = 0; i < measured.size(); i++) {
            runs.push(jsonRun(measured[i], fPoints[i]));
        }
        Json document = documentJson(fArgs);
        document.set("frames", fArgs.render);
        document.set("freqresp", Json::object()
                                     .set("input", fChannel)
                                     .set("settle", fArgs.settle)
                                     .set("hz", Json::numbers(fHz))
                                     .set("runs", runs));
        describeProgram(document, fArgs, fCompiled.eval != nullptr ? &fLabels : nullptr, fCompiled.seconds);
        printJson(document);
    }

    Json jsonRun(const PointResponse& response, const Point& point) const
    {
        Json outputs = Json::array();
        for (size_t output = 0; output < response.responses.size(); output++) {
            std::vector<double> magnitudes, phases;
            for (const FreqPoint& p : response.responses[output]) {
                magnitudes.push_back(p.magnitudeDb);
                phases.push_back(p.phase);
            }
            outputs.push(Json::object()
                             .set("output", output)
                             .set("mag_db", Json::numbers(magnitudes))
                             .set("phase", Json::numbers(phases))
                             .set("tail_energy_fraction", response.tails[output])
                             .set("peak", response.stats.channels[output].peak));
        }
        Json linearity = Json::object().set("tolerance", fTolerance).set("shift", fShift);
        for (const auto& deviation : response.deviations) {
            linearity.set(propertyName(deviation.first), deviation.second);
        }
        Json set = Json::object();
        for (const auto& value : response.set) {
            set.set(value.first, value.second);
        }
        Json run = Json::object().set("set", set).set("linearity", linearity).set("outputs", outputs);
        std::vector<Clamped> clamps = fClamps.ofPoint(point);
        if (!clamps.empty()) {
            Json clamped = Json::array();
            for (const Clamped& clamp : clamps) {
                clamped.push(clamp.json());
            }
            run.set("clamped", clamped);
        }
        std::vector<std::string> notes = response.notes(fArgs.render);
        if (!notes.empty()) {
            run.set("notes", Json::strings(notes));
        }
        if (response.stats.timing) {
            run.set("timing", timingJson(*response.stats.timing));
        }
        return run;
    }

    void rows(const std::vector<PointResponse>& measured) const
    {
        std::vector<std::string> header;
        for (const Axis& axis : fAxes) {
            header.push_back(axis.path);
        }
        header.push_back("hz");
        for (size_t output = 0; output < fProbe->outputs(); output++) {
            header.push_back("mag_db_out" + str(output));
            header.push_back("phase_out" + str(output));
        }
        writeLine(join(header, ","));
        for (const PointResponse& response : measured) {
            for (size_t k = 0; k < fHz.size(); k++) {
                std::vector<std::string> row;
                for (const auto& value : response.set) {
                    row.push_back(plainNumber(value.second));
                }
                row.push_back(fFmt.computed(fHz[k]));
                for (const std::vector<FreqPoint>& points : response.responses) {
                    row.push_back(fFmt.computed(points[k].magnitudeDb));
                    row.push_back(fFmt.computed(points[k].phase));
                }
                writeLine(join(row, ","));
            }
        }
    }

    void annotations(const std::vector<PointResponse>& measured, const TotalTiming& totalTiming) const
    {
        std::string excited;
        if (fChannel) {
            excited = "input " + str(*fChannel);
        } else if (fProbe->inputs() == 1) {
            excited = "the input";
        } else {
            excited = "all " + str(fProbe->inputs()) + " inputs at once";
        }
        // as for a render: under --quiet the annotations are the output
        Sink sink = Sink::beside(!fArgs.quiet);
        sink.say("# freqresp: " + str(fHz.size()) + " frequenc" + (fHz.size() == 1 ? "y" : "ies") + " from " +
                 fFmt.computed(fGrid.fmin) + " to " + fFmt.computed(fGrid.fmax) + " Hz, from the response of " +
                 str(fArgs.render) + " frames to an impulse on " + excited +
                 (fArgs.settle == 0 ? "" : " at frame " + str(fArgs.settle)) +
                 (fAxes.empty() ? "" : ", at each of " + str(measured.size()) + " sweep points"));
        if (fCompiled.eval != nullptr) {
            for (size_t output = 0; output < fLabels.size(); output++) {
                sink.say("# eval out" + str(output) + " = " + fLabels[output]);
            }
        }
        // a sweep's clamps are said once, before what concerns each point
        for (const Clamped& clamp : fClamps.all()) {
            sink.say(clamp.line());
        }
        for (const PointResponse& response : measured) {
            std::string              tag = response.tag();
            std::vector<std::string> shown;
            for (const auto& deviation : response.deviations) {
                shown.push_back(std::string(propertyName(deviation.first)) + " " + fFmt.computed(deviation.second));
            }
            sink.say("# freqresp" + tag + ": linear and time-invariant within " + scientific(fTolerance) +
                     " of the peak (" + join(shown, ", ") + ")");
            for (size_t output = 0; output < response.tails.size(); output++) {
                const ChannelStats& channel = response.stats.channels[output];
                if (response.tails[output]) {
                    sink.say("# freqresp" + tag + " out" + str(output) + ": peak=" + fFmt.sample(channel.peak) +
                             " peak_at=" + (channel.peakAt ? str(*channel.peakAt) : "none") +
                             ", the last tenth of the window holds " + fFmt.computed(*response.tails[output]) +
                             " of the energy");
                } else {
                    sink.say("# freqresp" + tag + " out" + str(output) +
                             ": the response is exactly zero: nothing reaches this output from " + excited);
                }
            }
            for (const std::string& note : response.notes(fArgs.render)) {
                sink.say("# note: " + note);
            }
        }
        sink.sayAll(totalTiming.lines(fCompiled.seconds, measured.size()));
    }
};

}  // namespace

void runFreqresp(const Args& args)
{
    Family family(args);
    family.run();
}
