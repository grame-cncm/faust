/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This file is part of faustprobe, the offline probe of a Faust program.
 It is distributed under the same license as the Faust tools: see
 COPYING.txt at the root of the repository.
 ************************************************************************/

// What every mode shares: what the command line means (the excitation, the
// assignments, the schedule, the program), the writes of a run checked against
// their ranges, how a result is said, what a failed render is explained with,
// and what a render is measured by.

#ifndef __faustprobe_report__
#define __faustprobe_report__

#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "cli.h"
#include "engine.h"
#include "eval.h"
#include "json.h"
#include "poly.h"

// ---------------------------------------------------------------- setup

// The program of a run.
struct Compiled {
    std::shared_ptr<Factory>     factory;  // what instances are made from
    std::shared_ptr<EvalProgram> eval;  // the wrapped file, under --eval
    double                       seconds = 0.0;  // what the compilation took, for --time
};

// FILE, or under --eval the expressions in its scope, at the width asked. compileTimed()
// is that at the width of the command line, timed.
Compiled    compileProgram(const Args& args, bool isDouble);
Compiled    compileTimed(const Args& args);
// PATH=VALUE, one or several; nothing resolved yet.
Assignments parseAssignments(const std::vector<std::string>& texts);
std::pair<std::string, double> parseAssignment(const std::string& text);
// The axes of --sweep, the flag a run's points come from, and its axes and points.
std::vector<Axis> sweepAxes(const Args& args);
std::string       sweepFlag(const Args& args);
void              sweepPoints(const Args& args, std::vector<Axis>& axes, std::vector<Point>& points);
// Parses --in. parseInputAt() adds the checks against the program: an impulse on an
// input it does not have, a file recorded at another rate.
InputMode         parseInput(const std::string& spec);
InputMode         parseInputAt(const std::string& spec, int sr, size_t inputs);
// An impulse on a missing input would excite nothing: an error, worded alike in every mode.
void              checkImpulseChannel(const InputMode& input, size_t inputs);
// What each output is: outN, or under --eval the expression it computes.
std::vector<std::string> outputLabels(const Args& args, const Compiled& compiled, size_t outputs);
// The number text of this run: --precision, at the program's width.
NumberFormat      numberFormat(const Args& args);
// Collects --at, --note and --chord into one schedule.
Schedule          buildSchedule(const Args& args);

// ---------------------------------------------------------------- writes

// A value clamped under --clamp, for the notices.
struct Clamped {
    std::string path;
    double      requested = 0.0;
    double      applied   = 0.0;
    // As a # clamped line, and as a JSON object.
    std::string line() const;
    Json        json() const;
    bool        operator==(const Clamped& other) const;
};

// Validates one write before any render, and returns the value the control takes.
// Outside the range: an error, or under --clamp a recorded clamp.
double checkValue(const ControlMap& controls, const std::string& query, double value, bool clamp,
                  std::vector<Clamped>& clamped);
// The same for a write broadcast to an instrument, a clamp being recorded once.
void   checkPolyValue(const PolyProbe& poly, const std::string& query, double value, bool clamp,
                      std::vector<Clamped>& clamped);

// The clamps of a run that may sweep: those every render runs under, and those
// of the sweep's values, each of which concerns the points that use it.
struct Clamps {
    std::vector<Clamped>                     fixed;
    std::vector<std::pair<size_t, Clamped>>  axes;  // with the index of their axis

    // Checks every value of every axis.
    void                 checkAxes(const ControlMap& controls, const std::vector<Axis>& sweep, bool clamp);
    // All of them, the fixed ones first: what is said once, before the rows of a sweep.
    std::vector<Clamped> all() const;
    // Those one point ran under: the fixed ones and those of its own values.
    std::vector<Clamped> ofPoint(const Point& point) const;
};

// The values a point's render uses, keyed by query: a row must not claim a value that
// was clamped.
Assignments applied(const ControlMap& controls, const Point& point);
// The controls a render wrote before its first frame, by path: what a failure says.
Assignments written(const ControlMap& controls, const Assignments& fixed, const Point& point);
// The known state every point starts from: a cleared instance, --set, the point's values.
void        prime(Probe& probe, const Assignments& fixed, const Point& point);

// ---------------------------------------------------------------- said

// Where the lines that go with a result are written: when nothing else owns
// stdout the annotations are the output; when rows own it, they go to stderr.
class Sink {
   public:
    // The sink of annotations, given whether rows own stdout.
    static Sink beside(bool rowsOwnStdout) { return Sink(rowsOwnStdout); }
    void        say(const std::string& line) const;
    void        sayAll(const std::vector<std::string>& lines) const;

   private:
    explicit Sink(bool toStderr) : fStderr(toStderr) {}
    bool fStderr;
};

// A line on stdout.
void writeLine(const std::string& line);
// The table of --list-params.
void printControls(const std::string& title, const ControlMap& controls, const NumberFormat& fmt);
// The # outN: line of each output, and the JSON of the statistics and of the window.
std::vector<std::string> channelLines(const RenderStats& stats, const NumberFormat& fmt);
Json channelsJson(const RenderStats& stats);
Json windowJson(const RenderStats& stats);
// What every JSON document starts with.
Json documentJson(const Args& args);
// What a document holding several renders says of --eval and of the compilation.
void describeProgram(Json& document, const Args& args, const std::vector<std::string>* evalLabels,
                     double compileSeconds);
// A document, which is then the whole of stdout.
void printJson(const Json& document);
// The # time lines: the compilation, compute against real time, the worst block,
// which a render names by its frame and a descent by its number.
std::vector<std::string> renderTimeLines(double compileSeconds, const Timing& timing);
std::vector<std::string> timeLines(double compileSeconds, const Timing& timing,
                                   const std::function<std::string(const WorstBlock&)>& worstName);
// The same in JSON, in seconds.
Json timingJson(const Timing& timing, const Optional<double>& compileSeconds = Optional<double>());
// Facts that explain a render whose every output is exactly zero.
std::vector<std::string> silenceNotes(const Probe& probe, const InputMode& input);

// The cost of several renders, for the outputs with no statistics block per render.
class TotalTiming {
   public:
    void                     add(const Optional<Timing>& timing);
    std::vector<std::string> lines(double compileSeconds, size_t renders) const;

   private:
    Optional<Timing> fTotal;
};

// ---------------------------------------------------------------- failures

// What a failure at a frame is explained with.
typedef std::function<std::string(size_t frame)> FrameContext;

// The failure of a render, if it has one. A runaway is reported where it
// starts: the sample above --fail-above comes first, and the non-finite frame
// that follows is mentioned with it.
Optional<std::string> renderFailure(const RenderStats& stats, const Optional<std::pair<size_t, Located>>& nonFinite,
                                    const Optional<double>& failAbove, size_t frames, const NumberFormat& fmt,
                                    const FrameContext& context);
// The value of each written control at that frame and the last scheduled write before
// it; for an instrument, the notes held too.
std::string failureContext(size_t frame, const Assignments& writtenBefore, const Schedule& schedule,
                           const ControlMap& controls);
// For an instrument: a write lands on the voices, on the effect or on both.
std::string polyFailureContext(size_t frame, const Assignments& fixed, const Schedule& schedule,
                               const PolyProbe& poly);

// ---------------------------------------------------------------- measures

// One render, measured.
struct Measured {
    Optional<std::vector<double>> reduced;    // per output, under --reduce
    std::vector<double>           described;  // the descriptors' values
};

// --reduce and --describe, validated before any render.
class Measures {
   public:
    // Parses the flags and checks the descriptors against this program and window.
    Measures(const Args& args, size_t outputs, size_t window, int sampleRate);

    // The reduction, as such and as the JSON field of a document.
    const Optional<Reduction>& reduction() const { return fReduction; }
    Json                       reductionJson() const;
    // Whether a render must keep its window's samples.
    bool                       needsSamples() const;
    // The columns of a sweep's row after the swept controls: per output the reduction, or
    // without one and without descriptors the three statistics; then one per descriptor.
    std::vector<std::string>   header(size_t outputs) const;
    // Measures one render; 'collected' holds its window when needsSamples().
    Measured                   measure(const RenderStats& stats, const Channels& collected) const;
    // The columns header() names.
    std::vector<std::string>   row(const Measured& measured, const RenderStats& stats, const NumberFormat& fmt) const;
    // Adds what the reduction says to a JSON entry; false without one.
    bool                       addReduced(Json& entry, const Measured& measured) const;
    // Adds the describe object; a non-finite value is null.
    void                       addDescribed(Json& entry, const Measured& measured) const;
    // The # describe line of a single render, and why a value is NaN.
    std::vector<std::string>   lines(const Measured& measured, const NumberFormat& fmt) const;
    // After a sweep's rows: at how many points a descriptor was NaN, and why.
    std::vector<std::string>   sweepNotes(const std::vector<Measured>& all) const;

   private:
    Optional<Reduction>     fReduction;
    std::vector<Descriptor> fDescriptors;
    DescribeSettings        fSettings;
    Optional<double>        fF0;
    double                  fSampleRate;
};

// ---------------------------------------------------------------- modes

// One function per mode: mode_render.cpp, mode_poly.cpp, mode_freqresp.cpp,
// mode_train.cpp, mode_svg.cpp.
void runRender(const Args& args, bool impulseTest);
void runPoly(const Args& args);
void runFreqresp(const Args& args);
void runTrain(const Args& args);
void runSvg(const Args& args);
// The second process of --check determinism.
void determinismWorker(const Args& args);
// A second compilation, in another process: the render's samples, and its program key.
std::string determinismRender(const Args& args, Samples& samples);
// A render from a cleared instance with 'sets' written. A reference that is not finite
// cannot be compared with: a Failure.
Samples     renderForComparison(Probe& probe, const RenderSpec& spec, const Assignments& sets, const std::string& what);

#endif
