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

    static InputMode fromFile(const std::string& path, const Optional<size_t>& channel);
    double           sample(size_t ch, size_t frame, double sampleRate) const;
};

// ---------------------------------------------------------------- statistics

// A sample and where it is: what turns "the render failed" into a frame to look at.
struct Located {
    size_t frame = 0;
    double value = 0.0;
};

struct ChannelStats {
    double            peak   = 0.0;
    double            rms    = 0.0;
    double            dc     = 0.0;
    bool              finite = true;
    Optional<size_t>  peakAt;
    Optional<Located> firstNonFinite;
    Optional<Located> firstAbove;
    size_t            subnormal = 0;
    Optional<size_t>  subnormalAt;
};

struct RenderStats {
    size_t                    windowStart = 0;
    size_t                    windowLength = 0;
    std::vector<ChannelStats> channels;
    size_t                    nonFiniteFrames = 0;
    Optional<Timing>          timing;

    Optional<std::pair<size_t, Located>> firstNonFinite() const;
    Optional<std::pair<size_t, Located>> firstAbove() const;
    // Every output exactly zero over the window: not quiet, silent.
    bool isSilent() const;
};

class StatsAccumulator {
   public:
    StatsAccumulator(size_t channels, size_t start, const Optional<double>& limit, bool isDouble);
    void        push(size_t frame, const std::vector<double>& samples);
    RenderStats finish() const;

   private:
    std::vector<ChannelStats> fChannels;
    std::vector<double>       fSumSquares;
    std::vector<double>       fSum;
    size_t                    fNonFiniteFrames = 0;
    bool                      fSingle;
    Optional<double>          fLimit;
    size_t                    fCounted = 0;
    size_t                    fStart;
};

// ---------------------------------------------------------------- schedule

struct Event {
    enum class Kind { SetParam, NoteOn, NoteOff };
    Kind        kind = Kind::SetParam;
    std::string path;
    double      value    = 0.0;
    int         pitch    = 0;
    int         velocity = 0;
};

struct ParamWrite {
    size_t      frame;
    std::string path;
    double      value;
};

// Events ordered by frame, those of one frame in insertion order: a note-off
// and a note-on for one pitch at one frame are applied in the order given.
class Schedule {
   public:
    void                                push(size_t frame, const Event& event);
    const std::vector<Event>&           at(size_t frame) const;
    Optional<size_t>                    nextAfter(size_t frame) const;
    bool                                needsPoly() const;
    std::vector<std::string>            paramPaths() const;
    std::vector<ParamWrite>             paramWrites() const;
    std::vector<std::pair<int, size_t>> notesHeldAt(size_t frame) const;

   private:
    std::map<size_t, std::vector<Event>> fEvents;
};

std::pair<size_t, Event>              parseAt(const std::string& frame, const std::string& assignment);
std::vector<std::pair<size_t, Event>> parseNote(const std::string& text);
std::vector<std::pair<size_t, Event>> parseChord(const std::string& text);

// The length of the block that starts at 'written': shorter so that the next
// scheduled event lands on a block boundary, which is what makes its timing
// sample-exact.
size_t nextBlock(const Schedule& schedule, size_t block, size_t frames, size_t written);

// ---------------------------------------------------------------- sweep

typedef std::vector<std::pair<std::string, double>> Assignments;

struct Axis {
    std::string         path;
    std::vector<double> values;
};

struct Point {
    Assignments assignments;
};

std::vector<Point> cartesian(const std::vector<Axis>& axes);
Axis               parseAxis(const std::string& text);
void               parsePoints(const std::string& text, std::vector<Axis>& axes, std::vector<Point>& points);

// ---------------------------------------------------------------- controls

enum class ControlKind { Button, CheckButton, Slider, NumEntry, Bargraph };
const char* controlKindName(ControlKind kind);

struct Control {
    std::string path;
    ControlKind kind = ControlKind::Slider;
    void*       zone = nullptr;  // of the width the program was compiled in
    double      init = 0.0;
    double      min  = 0.0;
    double      max  = 0.0;
    double      step = 0.0;

    bool   holds(double value) const;
    double clamp(double value) const;
};

// What writing 'requested' to a control does: 'applied' is the value it can hold.
struct Write {
    const Control* control   = nullptr;
    double         requested = 0.0;
    double         applied   = 0.0;
    bool           inRange() const { return control->holds(requested); }
    std::string    rangeError(const std::string& query) const;
};

// Controls discovered from one instance, by path, ordered by path.
class ControlMap {
   public:
    void                        add(const Control& control) { fControls[control.path] = control; }
    const std::map<std::string, Control>& all() const { return fControls; }
    const Control*              get(const std::string& path) const;
    // A full path, or a trailing fragment of one. Null when nothing matches;
    // 'candidates' lists several matches, which are reported rather than guessed.
    const Control* resolve(const std::string& query, std::vector<std::string>* candidates) const;
    bool           exists(const std::string& query) const;
    const Control& writable(const std::string& query) const;
    Write          checkWrite(const std::string& query, double value) const;

   private:
    std::map<std::string, Control> fControls;
};

// ---------------------------------------------------------------- factory

// A program compiled by LLVM, shared by every instance made from it.
class Factory {
   public:
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

    bool              isDouble() const { return fDouble; }
    std::string       shaKey() const;
    llvm_dsp_factory* handle() const { return fFactory; }

   private:
    Factory(llvm_dsp_factory* factory, bool isDouble) : fFactory(factory), fDouble(isDouble) {}
    llvm_dsp_factory* fFactory;
    bool              fDouble;
};

// ---------------------------------------------------------------- instance

struct RenderSpec {
    size_t           frames = 15000;
    size_t           block  = 64;
    InputMode        input;
    size_t           skip = 0;
    Schedule         schedule;
    bool             driveButtons = false;  // every button held for the first block
    Optional<double> limit;                 // --fail-above
    bool             time = false;          // --time
};

typedef std::function<void(size_t frame, const std::vector<double>& samples)> FrameCallback;

// One instance of a compiled program: its controls, and the render loop.
class Probe {
   public:
    Probe(const std::shared_ptr<Factory>& factory, int sampleRate);
    ~Probe();
    Probe(const Probe&) = delete;
    Probe& operator=(const Probe&) = delete;

    const ControlMap& controls() const { return fControls; }
    size_t            inputs() const { return fInputs; }
    size_t            outputs() const { return fOutputs; }
    bool              isDouble() const { return fFactory->isDouble(); }
    int               sampleRate() const { return fSampleRate; }

    std::vector<std::pair<std::string, double>>    bargraphs() const;
    std::vector<std::pair<const Control*, double>> controlValues() const;

    // Controls at their defaults and every piece of state zeroed: a sweep does
    // this between points, or a resonant filter rings into the next one.
    void reset();
    // By path or fragment, clamped to the declared range.
    void set(const std::string& query, double value);
    // By exact path, unclamped: what a note writes is written as computed.
    void setExact(const std::string& path, double value);

    RenderStats render(const RenderSpec& spec, const FrameCallback& onFrame);
    RenderStats collect(const RenderSpec& spec, Samples& samples);
    // One compute call over 'frames' samples of the given inputs.
    Channels computeRaw(const Channels& inputs, size_t frames);

   private:
    template <typename REAL>
    RenderStats renderAt(const RenderSpec& spec, const FrameCallback& onFrame);
    template <typename REAL>
    Channels computeAt(const Channels& inputs, size_t frames);
    void     setZone(void* zone, double value);
    double   getZone(void* zone) const;

    std::shared_ptr<Factory>                fFactory;
    llvm_dsp*                               fDsp = nullptr;
    ControlMap                              fControls;
    std::vector<std::unique_ptr<Soundfile>> fSoundfiles;
    size_t                                  fInputs     = 0;
    size_t                                  fOutputs    = 0;
    int                                     fSampleRate = 0;
};

// Seconds since a time point of the caller.
double secondsSince(uint64_t startNanos);
uint64_t nowNanos();

#endif
