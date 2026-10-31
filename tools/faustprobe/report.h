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

struct Compiled {
    std::shared_ptr<Factory>     factory;
    std::shared_ptr<EvalProgram> eval;  // the wrapped file, under --eval
    double                       seconds = 0.0;
};

Compiled    compileProgram(const Args& args, bool isDouble);
Compiled    compileTimed(const Args& args);
Assignments parseAssignments(const std::vector<std::string>& texts);
std::pair<std::string, double> parseAssignment(const std::string& text);
std::vector<Axis> sweepAxes(const Args& args);
std::string       sweepFlag(const Args& args);
void              sweepPoints(const Args& args, std::vector<Axis>& axes, std::vector<Point>& points);
InputMode         parseInput(const std::string& spec);
InputMode         parseInputAt(const std::string& spec, int sr, size_t inputs);
void              checkImpulseChannel(const InputMode& input, size_t inputs);
std::vector<std::string> outputLabels(const Args& args, const Compiled& compiled, size_t outputs);
NumberFormat      numberFormat(const Args& args);
Schedule          buildSchedule(const Args& args);

// ---------------------------------------------------------------- writes

struct Clamped {
    std::string path;
    double      requested = 0.0;
    double      applied   = 0.0;
    std::string line() const;
    Json        json() const;
    bool        operator==(const Clamped& other) const;
};

double checkValue(const ControlMap& controls, const std::string& query, double value, bool clamp,
                  std::vector<Clamped>& clamped);
void   checkPolyValue(const PolyProbe& poly, const std::string& query, double value, bool clamp,
                      std::vector<Clamped>& clamped);

// The clamps of a run that may sweep: those every render runs under, and those
// of the sweep's values, each of which concerns the points that use it.
struct Clamps {
    std::vector<Clamped>                     fixed;
    std::vector<std::pair<size_t, Clamped>>  axes;  // with the index of their axis

    void                 checkAxes(const ControlMap& controls, const std::vector<Axis>& sweep, bool clamp);
    std::vector<Clamped> all() const;
    std::vector<Clamped> ofPoint(const Point& point) const;
};

Assignments applied(const ControlMap& controls, const Point& point);
Assignments written(const ControlMap& controls, const Assignments& fixed, const Point& point);
void        prime(Probe& probe, const Assignments& fixed, const Point& point);

// ---------------------------------------------------------------- said

// Where the lines that go with a result are written: when nothing else owns
// stdout the annotations are the output; when rows own it, they go to stderr.
class Sink {
   public:
    static Sink beside(bool rowsOwnStdout) { return Sink(rowsOwnStdout); }
    void        say(const std::string& line) const;
    void        sayAll(const std::vector<std::string>& lines) const;

   private:
    explicit Sink(bool toStderr) : fStderr(toStderr) {}
    bool fStderr;
};

void writeLine(const std::string& line);
void printControls(const std::string& title, const ControlMap& controls, const NumberFormat& fmt);
std::vector<std::string> channelLines(const RenderStats& stats, const NumberFormat& fmt);
Json channelsJson(const RenderStats& stats);
Json windowJson(const RenderStats& stats);
Json documentJson(const Args& args);
void describeProgram(Json& document, const Args& args, const std::vector<std::string>* evalLabels,
                     double compileSeconds);
void printJson(const Json& document);
std::vector<std::string> renderTimeLines(double compileSeconds, const Timing& timing);
std::vector<std::string> timeLines(double compileSeconds, const Timing& timing,
                                   const std::function<std::string(const WorstBlock&)>& worstName);
Json timingJson(const Timing& timing, const Optional<double>& compileSeconds = Optional<double>());
std::vector<std::string> silenceNotes(const Probe& probe, const InputMode& input);

class TotalTiming {
   public:
    void                     add(const Optional<Timing>& timing);
    std::vector<std::string> lines(double compileSeconds, size_t renders) const;

   private:
    Optional<Timing> fTotal;
};

// ---------------------------------------------------------------- failures

typedef std::function<std::string(size_t frame)> FrameContext;

// The failure of a render, if it has one. A runaway is reported where it
// starts: the sample above --fail-above comes first, and the non-finite frame
// that follows is mentioned with it.
Optional<std::string> renderFailure(const RenderStats& stats, const Optional<std::pair<size_t, Located>>& nonFinite,
                                    const Optional<double>& failAbove, size_t frames, const NumberFormat& fmt,
                                    const FrameContext& context);
std::string failureContext(size_t frame, const Assignments& writtenBefore, const Schedule& schedule,
                           const ControlMap& controls);
std::string polyFailureContext(size_t frame, const Assignments& fixed, const Schedule& schedule,
                               const PolyProbe& poly);

// ---------------------------------------------------------------- measures

struct Measured {
    Optional<std::vector<double>> reduced;    // per output, under --reduce
    std::vector<double>           described;  // the descriptors' values
};

// --reduce and --describe, validated before any render.
class Measures {
   public:
    Measures(const Args& args, size_t outputs, size_t window, int sampleRate);

    const Optional<Reduction>& reduction() const { return fReduction; }
    Json                       reductionJson() const;
    bool                       needsSamples() const;
    std::vector<std::string>   header(size_t outputs) const;
    Measured                   measure(const RenderStats& stats, const Channels& collected) const;
    std::vector<std::string>   row(const Measured& measured, const RenderStats& stats, const NumberFormat& fmt) const;
    // Adds what the reduction says to a JSON entry; false without one.
    bool                       addReduced(Json& entry, const Measured& measured) const;
    void                       addDescribed(Json& entry, const Measured& measured) const;
    std::vector<std::string>   lines(const Measured& measured, const NumberFormat& fmt) const;
    std::vector<std::string>   sweepNotes(const std::vector<Measured>& all) const;

   private:
    Optional<Reduction>     fReduction;
    std::vector<Descriptor> fDescriptors;
    DescribeSettings        fSettings;
    Optional<double>        fF0;
    double                  fSampleRate;
};

// ---------------------------------------------------------------- modes

void runRender(const Args& args, bool impulseTest);
void runPoly(const Args& args);
void runFreqresp(const Args& args);
void runTrain(const Args& args);
void runSvg(const Args& args);
void determinismWorker(const Args& args);
// A second compilation, in another process: the render's samples, and its program key.
std::string determinismRender(const Args& args, Samples& samples);
Samples     renderForComparison(Probe& probe, const RenderSpec& spec, const Assignments& sets, const std::string& what);

#endif
