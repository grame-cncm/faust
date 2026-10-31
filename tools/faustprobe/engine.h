/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This file is part of faustprobe, the offline probe of a Faust program.
 It is distributed under the same license as the Faust tools: see
 COPYING.txt at the root of the repository.
 ************************************************************************/

// What is rendered and how: the excitation, the schedule of control changes
// and notes, the points of a sweep, the program's controls, the LLVM factory
// and the instances made from it.

#ifndef __faustprobe_engine__
#define __faustprobe_engine__

#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "analysis.h"
#include "audio.h"
#include "text.h"

class llvm_dsp;
class llvm_dsp_factory;
struct Soundfile;

// ---------------------------------------------------------------- excitation

// What to feed the DSP inputs: every sample is addressed by its position, so
// the value at a frame does not depend on how the render was cut into blocks.
struct InputMode {
    enum class Kind { Zero, Impulse, ImpulseChannel, Impulses, Dc, White, Sine, File };
    Kind                                   kind    = Kind::Impulse;
    size_t                                 channel = 0;     // of ImpulseChannel
    Optional<size_t>                       only;            // of Impulses: one channel, or all
    std::vector<std::pair<size_t, double>> taps;            // of Impulses: (frame, amplitude)
    uint64_t                               seed = 0;        // of White
    double                                 hz   = 0.0;      // of Sine
    std::shared_ptr<Channels>              fileChannels;    // of File
    Optional<int>                          fileSampleRate;  // of File, when the format records one

    // The excitation read from a file; with 'channel', that channel alone feeds every input.
    static InputMode fromFile(const std::string& path, const Optional<size_t>& channel);
    // Sample of input 'ch' at absolute 'frame'.
    double           sample(size_t ch, size_t frame, double sampleRate) const;
};

// ---------------------------------------------------------------- statistics

// A sample and where it is: what turns "the render failed" into a frame to look at.
struct Located {
    size_t frame = 0;
    double value = 0.0;
};

// Statistics of one output over the window, the part of the render after --skip.
struct ChannelStats {
    double            peak   = 0.0;  // largest magnitude
    double            rms    = 0.0;  // root mean square
    double            dc     = 0.0;  // mean: non-zero flags an offset
    bool              finite = true;  // whether every sample, in or out of the window, was finite
    Optional<size_t>  peakAt;  // first frame at the peak: an onset, or a level still rising
    Optional<Located> firstNonFinite;  // in or out of the window
    Optional<Located> firstAbove;  // first sample of the window above --fail-above
    size_t            subnormal = 0;  // subnormal samples at the width of the program
    Optional<size_t>  subnormalAt;  // the first of them
};

// Statistics of a whole render, with the window they describe.
struct RenderStats {
    size_t                    windowStart = 0;  // first frame counted
    size_t                    windowLength = 0;  // frames counted
    std::vector<ChannelStats> channels;
    size_t                    nonFiniteFrames = 0;  // frames with a non-finite sample, in or out of the window
    Optional<Timing>          timing;  // under --time only: the one thing that differs between two runs

    // The earliest such sample of the render and its channel; the lowest channel wins a tie.
    Optional<std::pair<size_t, Located>> firstNonFinite() const;
    Optional<std::pair<size_t, Located>> firstAbove() const;
    // Every output exactly zero over the window: not quiet, silent.
    bool isSilent() const;
};

// Builds the statistics frame by frame. isDouble says what "subnormal" is measured
// against: a single-precision subnormal is a normal double.
class StatsAccumulator {
   public:
    StatsAccumulator(size_t channels, size_t start, const Optional<double>& limit, bool isDouble);
    // One frame, of absolute index 'frame': one before the window counts for finiteness only.
    void        push(size_t frame, const std::vector<double>& samples);
    RenderStats finish() const;

   private:
    std::vector<ChannelStats> fChannels;
    std::vector<double>       fSumSquares;  // per output, over the window
    std::vector<double>       fSum;  // likewise
    size_t                    fNonFiniteFrames = 0;
    bool                      fSingle;  // the samples come from a single-precision program
    Optional<double>          fLimit;  // --fail-above
    size_t                    fCounted = 0;  // frames inside the window
    size_t                    fStart;  // first frame of the window
};

// ---------------------------------------------------------------- schedule

// Something to do at a frame: --at, or a note of --note and --chord. path is the
// control of a SetParam, as typed.
struct Event {
    enum class Kind { SetParam, NoteOn, NoteOff };
    Kind        kind = Kind::SetParam;
    std::string path;
    double      value    = 0.0;  // its value
    int         pitch    = 0;  // MIDI, of NoteOn and NoteOff
    int         velocity = 0;  // MIDI, of NoteOn
};

// A SetParam with its frame.
struct ParamWrite {
    size_t      frame;
    std::string path;
    double      value;
};

// Events ordered by frame, those of one frame in insertion order: a note-off
// and a note-on for one pitch at one frame are applied in the order given.
class Schedule {
   public:
    // Adds an event at a frame.
    void                                push(size_t frame, const Event& event);
    // The events of exactly this frame.
    const std::vector<Event>&           at(size_t frame) const;
    // The next frame strictly after this one that carries an event.
    Optional<size_t>                    nextAfter(size_t frame) const;
    // Whether a note is scheduled, which only the polyphonic wrapper can play.
    bool                                needsPoly() const;
    // The controls written, and the writes, in frame order.
    std::vector<std::string>            paramPaths() const;
    std::vector<ParamWrite>             paramWrites() const;
    // The notes sounding at a frame, for the context of a failure.
    std::vector<std::pair<int, size_t>> notesHeldAt(size_t frame) const;

   private:
    std::map<size_t, std::vector<Event>> fEvents;
};

// Parsers of --at FRAME PATH=VALUE, --note PITCH[:VEL]@ON[..OFF] and --chord
// P1,P2,...[:VEL]@ON[..OFF]. Velocity defaults to 100; without OFF a note is held.
std::pair<size_t, Event>              parseAt(const std::string& frame, const std::string& assignment);
std::vector<std::pair<size_t, Event>> parseNote(const std::string& text);
std::vector<std::pair<size_t, Event>> parseChord(const std::string& text);

// The length of the block that starts at 'written': shorter so that the next
// scheduled event lands on a block boundary, which is what makes its timing
// sample-exact.
size_t nextBlock(const Schedule& schedule, size_t block, size_t frames, size_t written);

// ---------------------------------------------------------------- sweep

// PATH=VALUE pairs, in the order given.
typedef std::vector<std::pair<std::string, double>> Assignments;

// One swept control and the values it takes.
struct Axis {
    std::string         path;
    std::vector<double> values;
};

// One point of a sweep: a value per axis.
struct Point {
    Assignments assignments;
};

// Every combination of the axes, the last varying fastest; one empty point without axes.
std::vector<Point> cartesian(const std::vector<Axis>& axes);
// Parses PATH=V1,V2,...
Axis               parseAxis(const std::string& text);
// Parses a --points file: a header naming the controls, one point per line, # comments.
void               parsePoints(const std::string& text, std::vector<Axis>& axes, std::vector<Point>& points);

// ---------------------------------------------------------------- controls

// A bargraph resolves like a control but is an output: writing it means nothing.
enum class ControlKind { Button, CheckButton, Slider, NumEntry, Bargraph };
// The name --list-params prints.
const char* controlKindName(ControlKind kind);

// One discovered control.
struct Control {
    std::string path;
    ControlKind kind = ControlKind::Slider;
    void*       zone = nullptr;  // of the width the program was compiled in
    double      init = 0.0;
    double      min  = 0.0;
    double      max  = 0.0;
    double      step = 0.0;

    // Whether the value is one the control can hold, which NaN is not; the value itself
    // if it does, else the nearest bound.
    bool   holds(double value) const;
    double clamp(double value) const;
};

// What writing 'requested' to a control does: 'applied' is the value it can hold.
struct Write {
    const Control* control   = nullptr;
    double         requested = 0.0;
    double         applied   = 0.0;
    bool           inRange() const { return control->holds(requested); }
    // The message of a request outside the range, naming the query as typed.
    std::string    rangeError(const std::string& query) const;
};

// Controls discovered from one instance, by path, ordered by path.
class ControlMap {
   public:
    // A later control of one path replaces the earlier.
    void                        add(const Control& control) { fControls[control.path] = control; }
    const std::map<std::string, Control>& all() const { return fControls; }
    // By exact path; null when there is none.
    const Control*              get(const std::string& path) const;
    // A full path, or a trailing fragment of one. Null when nothing matches;
    // 'candidates' lists several matches, which are reported rather than guessed.
    const Control* resolve(const std::string& query, std::vector<std::string>* candidates) const;
    // Whether the query names one control or several: not a NotFound.
    bool           exists(const std::string& query) const;
    // The one control the query names, or a Failure naming the bargraph, the candidates
    // of an ambiguous fragment, or the query.
    const Control& writable(const std::string& query) const;
    // What writing this value would do; the caller decides what out of range means.
    Write          checkWrite(const std::string& query, double value) const;

   private:
    std::map<std::string, Control> fControls;
};

// ---------------------------------------------------------------- factory

// A program compiled by LLVM, shared by every instance made from it.
class Factory {
   public:
    // Compiles a file: libfaust's message is the Failure of a program it refuses.
    static std::shared_ptr<Factory> compileFile(const std::string& path, const std::vector<std::string>& importDirs,
                                                const std::vector<std::string>& extraArgs, bool isDouble, int optLevel);
    // 'name' names the program, 'file' is where its text came from, against
    // whose directory its relative imports are resolved ("" when it has none).
    static std::shared_ptr<Factory> compileString(const std::string& name, const std::string& file,
                                                  const std::string& source,
                                                  const std::vector<std::string>& importDirs,
                                                  const std::vector<std::string>& extraArgs, bool isDouble,
                                                  int optLevel);
    ~Factory();

    // The width of the samples of every instance; the key of the compiled program, which
    // two compilations of one source share; the libfaust handle.
    bool              isDouble() const { return fDouble; }
    std::string       shaKey() const;
    llvm_dsp_factory* handle() const { return fFactory; }

   private:
    Factory(llvm_dsp_factory* factory, bool isDouble) : fFactory(factory), fDouble(isDouble) {}
    llvm_dsp_factory* fFactory;
    bool              fDouble;
};

// ---------------------------------------------------------------- instance

// How a render is driven.
struct RenderSpec {
    size_t           frames = 15000;  // total frames
    size_t           block  = 64;  // frames per compute call, before the schedule shortens one
    InputMode        input;  // the excitation
    size_t           skip = 0;  // first frame of statistics and dump
    Schedule         schedule;  // control changes at exact frames
    bool             driveButtons = false;  // every button held for the first block
    Optional<double> limit;                 // --fail-above
    bool             time = false;          // --time
};

// Called for each frame of the window, with its absolute index.
typedef std::function<void(size_t frame, const std::vector<double>& samples)> FrameCallback;

// One instance of a compiled program: its controls, and the render loop.
class Probe {
   public:
    // Creates and initialises an instance, and discovers its controls. A factory can feed
    // many: that is what lets N voices pay for one compilation.
    Probe(const std::shared_ptr<Factory>& factory, int sampleRate);
    ~Probe();
    Probe(const Probe&) = delete;
    Probe& operator=(const Probe&) = delete;

    // What the instance is.
    const ControlMap& controls() const { return fControls; }
    size_t            inputs() const { return fInputs; }
    size_t            outputs() const { return fOutputs; }
    bool              isDouble() const { return fFactory->isDouble(); }
    int               sampleRate() const { return fSampleRate; }

    // The bargraphs now, by path: updated by compute, so the value at the last sample of
    // the last block. Then the writable controls now, which explain a silent render.
    std::vector<std::pair<std::string, double>>    bargraphs() const;
    std::vector<std::pair<const Control*, double>> controlValues() const;

    // Controls at their defaults and every piece of state zeroed: a sweep does
    // this between points, or a resonant filter rings into the next one.
    void reset();
    // By path or fragment, clamped to the declared range.
    void set(const std::string& query, double value);
    // By exact path, unclamped: what a note writes is written as computed.
    void setExact(const std::string& path, double value);

    // Runs a render from the current state.
    RenderStats render(const RenderSpec& spec, const FrameCallback& onFrame);
    // A render that keeps the window's samples.
    RenderStats collect(const RenderSpec& spec, Samples& samples);
    // One compute call over 'frames' samples of the given inputs.
    Channels computeRaw(const Channels& inputs, size_t frames);

   private:
    // The two loops, at the buffer type of the program: float or double.
    template <typename REAL>
    RenderStats renderAt(const RenderSpec& spec, const FrameCallback& onFrame);
    template <typename REAL>
    Channels computeAt(const Channels& inputs, size_t frames);
    // A control's zone, at the width of the program.
    void     setZone(void* zone, double value);
    double   getZone(void* zone) const;

    std::shared_ptr<Factory>                fFactory;  // outlives the instance
    llvm_dsp*                               fDsp = nullptr;  // owned
    ControlMap                              fControls;
    std::vector<std::unique_ptr<Soundfile>> fSoundfiles;  // the DSP holds bare pointers to them
    size_t                                  fInputs     = 0;
    size_t                                  fOutputs    = 0;
    int                                     fSampleRate = 0;
};

// Seconds since a time point of the caller.
// A monotonic clock: nowNanos() at the start, then secondsSince().
double secondsSince(uint64_t startNanos);
uint64_t nowNanos();

#endif
