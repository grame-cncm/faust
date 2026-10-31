/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This file is part of faustprobe, the offline probe of a Faust program.
 It is distributed under the same license as the Faust tools: see
 COPYING.txt at the root of the repository.
 ************************************************************************/

#include "engine.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>

#include "faust/dsp/llvm-dsp.h"
#include "faust/gui/PathBuilder.h"
#include "faust/gui/Soundfile.h"
#include "faust/gui/UI.h"

// steady_clock: a render's cost must not move with the wall clock.
uint64_t nowNanos()
{
    using namespace std::chrono;
    return static_cast<uint64_t>(duration_cast<nanoseconds>(steady_clock::now().time_since_epoch()).count());
}

// See engine.h.
double secondsSince(uint64_t startNanos)
{
    return double(nowNanos() - startNanos) * 1e-9;
}

// ---------------------------------------------------------------- excitation

// Empty files are refused: they would excite nothing and say nothing.
InputMode InputMode::fromFile(const std::string& path, const Optional<size_t>& channel)
{
    AudioFile file = readChannels(path);
    if (file.channels.empty() || file.channels[0].empty()) {
        throw Failure(path + ": no samples");
    }
    if (channel) {
        if (*channel >= file.channels.size()) {
            throw Failure(path + ": channel " + str(*channel) + " requested, the file has " +
                          str(file.channels.size()));
        }
        file.channels = Channels(1, file.channels[*channel]);
    }
    InputMode mode;
    mode.kind           = Kind::File;
    mode.fileChannels   = std::make_shared<Channels>(file.channels);
    mode.fileSampleRate = file.sampleRate;
    return mode;
}

// Position-addressed uniform noise in [-1, 1): the SplitMix64 finalizer over
// (seed, channel, frame), so that a run is reproducible and block-independent.
static double white(uint64_t seed, size_t channel, size_t frame)
{
    uint64_t z = seed + uint64_t(channel) * 0x9E3779B97F4A7C15ull + uint64_t(frame) * 0xBF58476D1CE4E5B9ull;
    z          = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ull;
    z          = (z ^ (z >> 27)) * 0x94D049BB133111EBull;
    z ^= z >> 31;
    double unit = double(z >> 11) / double(1ull << 53);
    return std::fma(unit, 2.0, -1.0);
}

// A file feeds input i from channel i, or from its last channel; silence past its end.
double InputMode::sample(size_t ch, size_t frame, double sampleRate) const
{
    switch (kind) {
        case Kind::Zero:
            return 0.0;
        case Kind::Impulse:
            return frame == 0 ? 1.0 : 0.0;
        case Kind::ImpulseChannel:
            return frame == 0 && ch == channel ? 1.0 : 0.0;
        case Kind::Impulses: {
            if (only && *only != ch) {
                return 0.0;
            }
            double sum = 0.0;
            for (const auto& tap : taps) {
                if (tap.first == frame) {
                    sum += tap.second;
                }
            }
            return sum;
        }
        case Kind::Dc:
            return 1.0;
        case Kind::White:
            return white(seed, ch, frame);
        case Kind::Sine:
            return sin(6.283185307179586476925286766559 * hz * double(frame) / sampleRate);
        default: {
            const std::vector<double>& source = (*fileChannels)[std::min(ch, fileChannels->size() - 1)];
            return frame < source.size() ? source[frame] : 0.0;
        }
    }
}

// ---------------------------------------------------------------- statistics

// The earliest of the per-channel locations; the lowest channel wins a tie.
template <typename GET>
static Optional<std::pair<size_t, Located>> earliest(const std::vector<ChannelStats>& channels, GET get)
{
    Optional<std::pair<size_t, Located>> best;
    for (size_t ch = 0; ch < channels.size(); ch++) {
        const Optional<Located>& located = get(channels[ch]);
        if (located && (!best || located.value.frame < best.value.second.frame)) {
            best = std::make_pair(ch, located.value);
        }
    }
    return best;
}

// See earliest() above.
Optional<std::pair<size_t, Located>> RenderStats::firstNonFinite() const
{
    return earliest(channels, [](const ChannelStats& c) -> const Optional<Located>& { return c.firstNonFinite; });
}

Optional<std::pair<size_t, Located>> RenderStats::firstAbove() const
{
    return earliest(channels, [](const ChannelStats& c) -> const Optional<Located>& { return c.firstAbove; });
}

// An empty window says nothing about the program.
bool RenderStats::isSilent() const
{
    if (windowLength == 0) {
        return false;
    }
    for (const ChannelStats& channel : channels) {
        if (!(channel.finite && channel.peak == 0.0)) {
            return false;
        }
    }
    return true;
}

// Every sum at zero, every location absent.
StatsAccumulator::StatsAccumulator(size_t channels, size_t start, const Optional<double>& limit, bool isDouble)
    : fChannels(channels), fSumSquares(channels, 0.0), fSum(channels, 0.0), fSingle(!isDouble), fLimit(limit),
      fStart(start)
{
}

// A non-finite sample skips the sums, which would be lost to it: what it means is
// said by firstNonFinite.
void StatsAccumulator::push(size_t frame, const std::vector<double>& samples)
{
    bool inside         = frame >= fStart;
    bool frameNonFinite = false;
    for (size_t ch = 0; ch < samples.size(); ch++) {
        double        value   = samples[ch];
        ChannelStats& channel = fChannels[ch];
        if (!std::isfinite(value)) {
            channel.finite = false;
            frameNonFinite = true;
            if (!channel.firstNonFinite) {
                Located located;
                located.frame          = frame;
                located.value          = value;
                channel.firstNonFinite = located;
            }
            continue;
        }
        if (!inside) {
            continue;
        }
        double magnitude = fabs(value);
        if (magnitude > channel.peak) {
            channel.peak   = magnitude;
            channel.peakAt = frame;
        }
        if (fLimit && magnitude > *fLimit && !channel.firstAbove) {
            Located located;
            located.frame      = frame;
            located.value      = value;
            channel.firstAbove = located;
        }
        // fused, as the reference statistics of faust-rs are
        fSumSquares[ch] = std::fma(value, value, fSumSquares[ch]);
        fSum[ch] += value;
        // exact in single precision: the sample was a float
        bool subnormal = fSingle ? std::fpclassify(static_cast<float>(value)) == FP_SUBNORMAL
                                 : std::fpclassify(value) == FP_SUBNORMAL;
        if (subnormal) {
            channel.subnormal++;
            if (!channel.subnormalAt) {
                channel.subnormalAt = frame;
            }
        }
    }
    if (frameNonFinite) {
        fNonFiniteFrames++;
    }
    if (inside) {
        fCounted++;
    }
}

// n is at least 1, so that an empty window gives zeros and not NaN.
RenderStats StatsAccumulator::finish() const
{
    double      n = double(std::max<size_t>(fCounted, 1));
    RenderStats stats;
    stats.windowStart     = fStart;
    stats.windowLength    = fCounted;
    stats.channels        = fChannels;
    stats.nonFiniteFrames = fNonFiniteFrames;
    for (size_t ch = 0; ch < stats.channels.size(); ch++) {
        stats.channels[ch].rms = sqrt(fSumSquares[ch] / n);
        stats.channels[ch].dc  = fSum[ch] / n;
    }
    return stats;
}

// ---------------------------------------------------------------- schedule

// A frame keeps its events in insertion order.
void Schedule::push(size_t frame, const Event& event)
{
    fEvents[frame].push_back(event);
}

// A reference, so the empty case needs a vector that lives on.
const std::vector<Event>& Schedule::at(size_t frame) const
{
    static const std::vector<Event> none;
    auto                            found = fEvents.find(frame);
    return found == fEvents.end() ? none : found->second;
}

// upper_bound: strictly after.
Optional<size_t> Schedule::nextAfter(size_t frame) const
{
    auto next = fEvents.upper_bound(frame);
    return next == fEvents.end() ? Optional<size_t>() : Optional<size_t>(next->first);
}

bool Schedule::needsPoly() const
{
    for (const auto& entry : fEvents) {
        for (const Event& event : entry.second) {
            if (event.kind != Event::Kind::SetParam) {
                return true;
            }
        }
    }
    return false;
}

std::vector<std::string> Schedule::paramPaths() const
{
    std::vector<std::string> paths;
    for (const ParamWrite& write : paramWrites()) {
        paths.push_back(write.path);
    }
    return paths;
}

std::vector<ParamWrite> Schedule::paramWrites() const
{
    std::vector<ParamWrite> writes;
    for (const auto& entry : fEvents) {
        for (const Event& event : entry.second) {
            if (event.kind == Event::Kind::SetParam) {
                writes.push_back({entry.first, event.path, event.value});
            }
        }
    }
    return writes;
}

// The pitches sounding at 'frame', with the frame of their note-on, in the
// order they were played. A pitch played twice is held from its last note-on.
std::vector<std::pair<int, size_t>> Schedule::notesHeldAt(size_t frame) const
{
    std::vector<std::pair<int, size_t>> held;
    // Removes a pitch from the notes held.
    auto drop = [&held](int pitch) {
        held.erase(std::remove_if(held.begin(), held.end(),
                                  [pitch](const std::pair<int, size_t>& note) { return note.first == pitch; }),
                   held.end());
    };
    for (const auto& entry : fEvents) {
        if (entry.first > frame) {
            break;
        }
        for (const Event& event : entry.second) {
            if (event.kind == Event::Kind::NoteOn) {
                drop(event.pitch);
                held.push_back(std::make_pair(event.pitch, entry.first));
            } else if (event.kind == Event::Kind::NoteOff) {
                drop(event.pitch);
            }
        }
    }
    return held;
}

// See engine.h for the three grammars.
std::pair<size_t, Event> parseAt(const std::string& frameText, const std::string& assignment)
{
    size_t frame;
    if (!parseSize(frameText, frame)) {
        throw Failure("`" + frameText + "` is not a frame index in `--at " + frameText + " " + assignment + "`");
    }
    size_t equal = assignment.find('=');
    if (equal == std::string::npos) {
        throw Failure("expected PATH=VALUE, got `" + assignment + "`");
    }
    std::string text = assignment.substr(equal + 1);
    Event       event;
    if (!parseDouble(text, event.value)) {
        throw Failure("`" + text + "` is not a number in `" + assignment + "`");
    }
    event.kind = Event::Kind::SetParam;
    event.path = assignment.substr(0, equal);
    return std::make_pair(frame, event);
}

// Reversed spans and out-of-range values are errors: swapping or clamping them would
// render something that was not asked for.
std::vector<std::pair<size_t, Event>> parseNote(const std::string& text)
{
    size_t at = text.find('@');
    if (at == std::string::npos) {
        throw Failure("expected PITCH[:VEL]@ON[..OFF], got `" + text + "`");
    }
    std::string head = text.substr(0, at), span = text.substr(at + 1);
    size_t      colon     = head.find(':');
    std::string pitchText = head.substr(0, colon);
    int         pitch, velocity = 100;
    if (!parseInt(trim(pitchText), pitch)) {
        throw Failure("`" + pitchText + "` is not a MIDI pitch in `" + text + "`");
    }
    if (colon != std::string::npos) {
        std::string v = head.substr(colon + 1);
        if (!parseInt(trim(v), velocity)) {
            throw Failure("`" + v + "` is not a velocity in `" + text + "`");
        }
    }
    if (pitch < 0 || pitch > 127) {
        throw Failure("pitch " + std::to_string(pitch) + " out of MIDI range 0..=127 in `" + text + "`");
    }
    if (velocity < 0 || velocity > 127) {
        throw Failure("velocity " + std::to_string(velocity) + " out of MIDI range 0..=127 in `" + text + "`");
    }
    size_t      dots   = span.find("..");
    std::string onText = span.substr(0, dots);
    size_t      on;
    if (!parseSize(trim(onText), on)) {
        throw Failure("`" + onText + "` is not a frame index in `" + text + "`");
    }
    Event noteOn;
    noteOn.kind     = Event::Kind::NoteOn;
    noteOn.pitch    = pitch;
    noteOn.velocity = velocity;
    std::vector<std::pair<size_t, Event>> out;
    out.push_back(std::make_pair(on, noteOn));
    if (dots != std::string::npos) {
        std::string offText = trim(span.substr(dots + 2));
        if (!offText.empty()) {
            size_t off;
            if (!parseSize(offText, off)) {
                throw Failure("`" + offText + "` is not a frame index in `" + text + "`");
            }
            if (off < on) {
                throw Failure("note-off frame " + str(off) + " precedes note-on frame " + str(on) + " in `" + text +
                              "`");
            }
            Event noteOff;
            noteOff.kind  = Event::Kind::NoteOff;
            noteOff.pitch = pitch;
            out.push_back(std::make_pair(off, noteOff));
        }
    }
    return out;
}

// Everything after the pitches is shared by the notes.
std::vector<std::pair<size_t, Event>> parseChord(const std::string& text)
{
    size_t at = text.find(':');
    if (at == std::string::npos) {
        at = text.find('@');
    }
    if (at == std::string::npos) {
        throw Failure("expected P1,P2,...[:VEL]@ON[..OFF], got `" + text + "`");
    }
    std::vector<std::pair<size_t, Event>> out;
    for (const std::string& raw : split(text.substr(0, at), ',')) {
        std::string pitch = trim(raw);
        if (pitch.empty()) {
            throw Failure("empty pitch in `" + text + "`");
        }
        // the separator is kept, so that the note reads as a single-note spec
        for (const auto& note : parseNote(pitch + text.substr(at))) {
            out.push_back(note);
        }
    }
    return out;
}

// See engine.h.
size_t nextBlock(const Schedule& schedule, size_t block, size_t frames, size_t written)
{
    size_t           n    = std::min(block, frames - written);
    Optional<size_t> next = schedule.nextAfter(written);
    if (next && *next > written) {
        n = std::min(n, *next - written);
    }
    return n;
}

// ---------------------------------------------------------------- sweep

// Each axis multiplies the points so far: the last one varies fastest.
std::vector<Point> cartesian(const std::vector<Axis>& axes)
{
    std::vector<Point> points(1);
    for (const Axis& axis : axes) {
        std::vector<Point> next;
        for (const Point& point : points) {
            for (double value : axis.values) {
                Point more = point;
                more.assignments.push_back(std::make_pair(axis.path, value));
                next.push_back(more);
            }
        }
        points = next;
    }
    return points;
}

// Control paths are not checked here: nothing is compiled yet.
Axis parseAxis(const std::string& text)
{
    size_t equal = text.find('=');
    if (equal == std::string::npos) {
        throw Failure("expected PATH=V1,V2,..., got `" + text + "`");
    }
    Axis axis;
    axis.path = text.substr(0, equal);
    if (axis.path.empty()) {
        throw Failure("empty control path in `" + text + "`");
    }
    for (const std::string& item : split(text.substr(equal + 1), ',')) {
        std::string trimmed = trim(item);
        if (trimmed.empty()) {
            throw Failure("empty value in `" + text + "`");
        }
        double value;
        if (!parseDouble(trimmed, value)) {
            throw Failure("`" + trimmed + "` is not a number in `" + text + "`");
        }
        axis.values.push_back(value);
    }
    return axis;
}

// The controls become axes too, each with its column: the range checks read them.
void parsePoints(const std::string& text, std::vector<Axis>& axes, std::vector<Point>& points)
{
    std::vector<std::string> lines = split(text, '\n');
    bool                     headed = false;
    for (size_t index = 0; index < lines.size(); index++) {
        std::string line = trim(lines[index]);
        if (line.empty() || line[0] == '#') {
            continue;
        }
        if (!headed) {
            headed = true;
            for (const std::string& raw : split(line, ',')) {
                std::string name = trim(raw);
                if (name.empty()) {
                    throw Failure("empty control name in the header `" + line + "`");
                }
                for (const Axis& axis : axes) {
                    if (axis.path == name) {
                        throw Failure("`" + name + "` is named twice in the header");
                    }
                }
                Axis axis;
                axis.path = name;
                axes.push_back(axis);
            }
            continue;
        }
        std::string              number = std::to_string(index + 1);
        std::vector<std::string> fields = split(line, ',');
        if (fields.size() != axes.size()) {
            throw Failure("line " + number + ": " + str(fields.size()) + " field(s) for " + str(axes.size()) +
                          " control(s)");
        }
        Point point;
        for (size_t k = 0; k < fields.size(); k++) {
            std::string field = trim(fields[k]);
            double      value;
            if (!parseDouble(field, value)) {
                throw Failure("line " + number + ": `" + field + "` is not a number");
            }
            axes[k].values.push_back(value);
            point.assignments.push_back(std::make_pair(axes[k].path, value));
        }
        points.push_back(point);
    }
    if (!headed) {
        throw Failure("no header line naming the controls");
    }
    if (points.empty()) {
        throw Failure("no point after the header");
    }
}

// ---------------------------------------------------------------- controls

// See engine.h.
const char* controlKindName(ControlKind kind)
{
    switch (kind) {
        case ControlKind::Button:
            return "button";
        case ControlKind::CheckButton:
            return "checkbox";
        case ControlKind::Slider:
            return "slider";
        case ControlKind::NumEntry:
            return "nentry";
        default:
            return "bargraph";
    }
}

// A value is in range when it is, or when it is at single precision: a host
// writing floats would send that, and a bound declared 0.7 of a single-precision
// program is 0.699999988 here, below the 0.7 typed on the command line.
bool Control::holds(double value) const
{
    double narrow = static_cast<double>(static_cast<float>(value));
    return (min <= value && value <= max) || (min <= narrow && narrow <= max);
}

// A value it holds is returned as it is, not pulled onto a single-precision bound.
double Control::clamp(double value) const
{
    return holds(value) ? value : std::min(std::max(value, min), max);
}

std::string Write::rangeError(const std::string& query) const
{
    // the bounds as declared, which is what their single precision prints
    return "`" + query + "`=" + plainNumber(requested) + " is outside the range [" +
           plainNumber(static_cast<float>(control->min)) + ", " + plainNumber(static_cast<float>(control->max)) +
           "] of " + control->path;
}

const Control* ControlMap::get(const std::string& path) const
{
    auto found = fControls.find(path);
    return found == fControls.end() ? nullptr : &found->second;
}

// An exact path wins over a fragment; several matches are never resolved arbitrarily.
const Control* ControlMap::resolve(const std::string& query, std::vector<std::string>* candidates) const
{
    if (const Control* exact = get(query)) {
        return exact;
    }
    // a fragment matches whole segments: `volume` does not match osc0_volume
    std::string                 suffix = startsWith(query, "/") ? query : "/" + query;
    std::vector<const Control*> matches;
    for (const auto& entry : fControls) {
        if (endsWith(entry.first, suffix)) {
            matches.push_back(&entry.second);
        }
    }
    if (matches.size() == 1) {
        return matches[0];
    }
    if (candidates != nullptr) {
        for (const Control* match : matches) {
            candidates->push_back(match->path);
        }
    }
    return nullptr;
}

bool ControlMap::exists(const std::string& query) const
{
    std::vector<std::string> candidates;
    return resolve(query, &candidates) != nullptr || !candidates.empty();
}

const Control& ControlMap::writable(const std::string& query) const
{
    std::vector<std::string> candidates;
    const Control*           control = resolve(query, &candidates);
    if (control != nullptr) {
        if (control->kind == ControlKind::Bargraph) {
            throw Failure("`" + control->path + "` is a bargraph, an output of the program: it cannot be set");
        }
        return *control;
    }
    if (candidates.empty()) {
        throw Failure("no control matching `" + query + "`");
    }
    throw Failure("`" + query + "` is ambiguous, matches: " + join(candidates, ", "));
}

// NaN is in no range: it is replaced by the initial value, which the clamp notice says.
Write ControlMap::checkWrite(const std::string& query, double value) const
{
    const Control& control = writable(query);
    Write          write;
    write.control   = &control;
    write.requested = value;
    write.applied   = std::isnan(value) ? control.init : control.clamp(value);
    return write;
}

// The in-memory soundfile the reference impulse-test protocol reads: a DSP
// declaring soundfile(...) gets a pointer the host must fill in, or the first
// compute dereferences null.
// The parts of a soundfile URL, {'a';'b'} or a single name.
static int soundfilePartCount(const std::string& url)
{
    std::string trimmed = trim(url);
    size_t      open    = trimmed.find('{');
    if (open == std::string::npos) {
        return 1;
    }
    size_t close = trimmed.find('}', open + 1);
    if (close == std::string::npos) {
        return 1;
    }
    int count = 0;
    for (const std::string& raw : split(trimmed.substr(open + 1, close - open - 1), ';')) {
        std::string part = trim(raw);
        if (!part.empty() && part != "'" && part != "''") {
            count++;
        }
    }
    return std::max(count, 1);
}

// The fixture: real parts of 4096 frames holding a sine, then empty parts up to the
// fixed count of a Soundfile. REAL is the width of the program.
template <typename REAL>
static Soundfile* makeSoundfile(int realParts, bool isDouble)
{
    const int kChannels = 2, kLength = 4096, kSampleRate = 44100, kBufferSize = 1024;
    realParts = std::min(realParts, MAX_SOUNDFILE_PARTS);
    int total = realParts * kLength + (MAX_SOUNDFILE_PARTS - realParts) * kBufferSize;

    Soundfile* soundfile = new Soundfile(kChannels, total, MAX_CHAN, realParts, isDouble);
    int        offset    = 0;
    for (int part = 0; part < MAX_SOUNDFILE_PARTS; part++) {
        int length             = part < realParts ? kLength : kBufferSize;
        soundfile->fLength[part] = length;
        soundfile->fSR[part]     = kSampleRate;
        soundfile->fOffset[part] = offset;
        if (part < realParts) {
            // each channel has its own phase, so that a channel wrap is observable
            for (int sample = 0; sample < length; sample++) {
                for (int chan = 0; chan < kChannels; chan++) {
                    static_cast<REAL**>(soundfile->fBuffers)[chan][offset + sample] =
                        static_cast<REAL>(sin(double(part) + double(chan) + 2.0 * M_PI * double(sample) / length));
                }
            }
        }
        offset += length;
    }
    return soundfile;
}

// The walk of buildUserInterface: the stack of groups gives every control its
// path, as MapUI does. Templated on the width of the program: the zones and
// the bounds of a double-precision program are doubles (UIReal::sizeOfFAUSTFLOAT
// tells libfaust which width this UI takes).
template <typename REAL>
class ControlWalker : public UIReal<REAL>, public PathBuilder {
   public:
    ControlWalker(ControlMap& controls, std::vector<std::unique_ptr<Soundfile>>& soundfiles, bool isDouble)
        : fControls(controls), fSoundfiles(soundfiles), fDouble(isDouble)
    {
    }

    void openTabBox(const char* label) override { pushLabel(label); }
    void openHorizontalBox(const char* label) override { pushLabel(label); }
    void openVerticalBox(const char* label) override { pushLabel(label); }
    void closeBox() override { popLabel(); }

    void addButton(const char* label, REAL* zone) override
    {
        add(label, ControlKind::Button, zone, 0, 0, 1, 1);
    }
    void addCheckButton(const char* label, REAL* zone) override
    {
        add(label, ControlKind::CheckButton, zone, 0, 0, 1, 1);
    }
    void addVerticalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) override
    {
        add(label, ControlKind::Slider, zone, init, min, max, step);
    }
    void addHorizontalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) override
    {
        add(label, ControlKind::Slider, zone, init, min, max, step);
    }
    void addNumEntry(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) override
    {
        add(label, ControlKind::NumEntry, zone, init, min, max, step);
    }
    void addHorizontalBargraph(const char* label, REAL* zone, REAL min, REAL max) override
    {
        add(label, ControlKind::Bargraph, zone, 0, min, max, 0);
    }
    void addVerticalBargraph(const char* label, REAL* zone, REAL min, REAL max) override
    {
        add(label, ControlKind::Bargraph, zone, 0, min, max, 0);
    }
    void addSoundfile(const char* /*label*/, const char* url, Soundfile** zone) override
    {
        fSoundfiles.emplace_back(makeSoundfile<REAL>(soundfilePartCount(url), fDouble));
        *zone = fSoundfiles.back().get();
    }

   private:
    // buildPath() is PathBuilder's, what MapUI and a host use: paths agree with theirs.
    void add(const char* label, ControlKind kind, REAL* zone, double init, double min, double max, double step)
    {
        Control control;
        control.path = buildPath(label);
        control.kind = kind;
        control.zone = zone;
        control.init = init;
        control.min  = min;
        control.max  = max;
        control.step = step;
        fControls.add(control);
    }

    ControlMap&                              fControls;
    std::vector<std::unique_ptr<Soundfile>>& fSoundfiles;
    bool                                     fDouble;
};

// ---------------------------------------------------------------- factory

// The argv of libfaust: -I DIR..., the precision, the other options. The returned
// pointers live in 'storage'.
static std::vector<const char*> compilerArgv(const std::vector<std::string>& importDirs,
                                             const std::vector<std::string>& extraArgs, bool isDouble,
                                             std::vector<std::string>& storage)
{
    for (const std::string& dir : importDirs) {
        storage.push_back("-I");
        storage.push_back(dir);
    }
    storage.push_back(isDouble ? "-double" : "-single");
    storage.insert(storage.end(), extraArgs.begin(), extraArgs.end());
    std::vector<const char*> argv;
    for (const std::string& arg : storage) {
        argv.push_back(arg.c_str());
    }
    return argv;
}

// See engine.h.
std::shared_ptr<Factory> Factory::compileFile(const std::string& path, const std::vector<std::string>& importDirs,
                                              const std::vector<std::string>& extraArgs, bool isDouble, int optLevel)
{
    // libfaust says nothing of a file it cannot read
    if (!std::ifstream(path).good()) {
        throw Failure("cannot read '" + path + "': " + strerror(errno));
    }
    // the files beside it come after the -I directories, as for the compiler
    std::vector<std::string> dirs = importDirs;
    dirs.push_back(directoryOf(path));
    std::vector<std::string> storage;
    std::vector<const char*> argv = compilerArgv(dirs, extraArgs, isDouble, storage);
    std::string              error;
    llvm_dsp_factory*        factory =
        createDSPFactoryFromFile(path, static_cast<int>(argv.size()), argv.data(), "", error, optLevel);
    if (factory == nullptr) {
        throw Failure(trim(error));
    }
    return std::shared_ptr<Factory>(new Factory(factory, isDouble));
}

// See engine.h.
std::shared_ptr<Factory> Factory::compileString(const std::string& name, const std::string& file,
                                                const std::string& source, const std::vector<std::string>& importDirs,
                                                const std::vector<std::string>& extraArgs, bool isDouble, int optLevel)
{
    // a file compiled from its path sees the files beside it; so must its text
    std::vector<std::string> dirs = importDirs;
    if (!file.empty()) {
        dirs.push_back(directoryOf(file));
    }
    std::vector<std::string> storage;
    std::vector<const char*> argv = compilerArgv(dirs, extraArgs, isDouble, storage);
    std::string              error;
    llvm_dsp_factory*        factory =
        createDSPFactoryFromString(name, source, static_cast<int>(argv.size()), argv.data(), "", error, optLevel);
    if (factory == nullptr) {
        throw Failure(trim(error));
    }
    return std::shared_ptr<Factory>(new Factory(factory, isDouble));
}

// Instances are gone by now: they hold a shared_ptr to this factory.
Factory::~Factory()
{
    deleteDSPFactory(fFactory);
}

std::string Factory::shaKey() const
{
    return fFactory->getSHAKey();
}

// ---------------------------------------------------------------- instance

// See engine.h.
Probe::Probe(const std::shared_ptr<Factory>& factory, int sampleRate) : fFactory(factory), fSampleRate(sampleRate)
{
    fDsp = factory->handle()->createDSPInstance();
    if (fDsp == nullptr) {
        throw Failure("LLVM instance creation failed");
    }
    fDsp->init(sampleRate);
    fInputs  = static_cast<size_t>(fDsp->getNumInputs());
    fOutputs = static_cast<size_t>(fDsp->getNumOutputs());
    // After init: the zones are bound once the instance owns its state. The
    // walker is a UIReal of the program's width, which is what the UI*
    // parameter stands for: UI is UIReal<FAUSTFLOAT> and the vtables agree.
    if (factory->isDouble()) {
        ControlWalker<double> walker(fControls, fSoundfiles, true);
        fDsp->buildUserInterface(reinterpret_cast<UI*>(static_cast<UIReal<double>*>(&walker)));
    } else {
        ControlWalker<float> walker(fControls, fSoundfiles, false);
        fDsp->buildUserInterface(reinterpret_cast<UI*>(static_cast<UIReal<float>*>(&walker)));
    }
}

// Deleting an instance leaves its factory to the other instances.
Probe::~Probe()
{
    delete fDsp;
}

// The fields of a DSP compiled by LLVM are packed: a zone may be misaligned.
void Probe::setZone(void* zone, double value)
{
    if (isDouble()) {
        memcpy(zone, &value, sizeof(value));
    } else {
        float narrow = static_cast<float>(value);
        memcpy(zone, &narrow, sizeof(narrow));
    }
}

double Probe::getZone(void* zone) const
{
    if (isDouble()) {
        double value;
        memcpy(&value, zone, sizeof(value));
        return value;
    }
    float value;
    memcpy(&value, zone, sizeof(value));
    return value;
}

std::vector<std::pair<std::string, double>> Probe::bargraphs() const
{
    std::vector<std::pair<std::string, double>> values;
    for (const auto& entry : fControls.all()) {
        if (entry.second.kind == ControlKind::Bargraph) {
            values.push_back(std::make_pair(entry.first, getZone(entry.second.zone)));
        }
    }
    return values;
}

std::vector<std::pair<const Control*, double>> Probe::controlValues() const
{
    std::vector<std::pair<const Control*, double>> values;
    for (const auto& entry : fControls.all()) {
        if (entry.second.kind != ControlKind::Bargraph) {
            values.push_back(std::make_pair(&entry.second, getZone(entry.second.zone)));
        }
    }
    return values;
}

// instanceResetUserInterface brings the controls back, instanceClear the state.
void Probe::reset()
{
    fDsp->instanceResetUserInterface();
    fDsp->instanceClear();
}

// The value written is the one checkWrite reports as applied: what the command line
// says of a clamp is what the render runs with.
void Probe::set(const std::string& query, double value)
{
    Write write = fControls.checkWrite(query, value);
    setZone(write.control->zone, write.applied);
}

// See engine.h: a note writes a frequency as computed, whatever the slider declares.
void Probe::setExact(const std::string& path, double value)
{
    const Control* control = fControls.get(path);
    if (control == nullptr) {
        throw Failure("no control at exact path `" + path + "`");
    }
    setZone(control->zone, value);
}

// The render loop at the program's width. FAUSTFLOAT** is only the type compute
// declares: it forwards pointers, which the program reads at its own width.
template <typename REAL>
RenderStats Probe::renderAt(const RenderSpec& spec, const FrameCallback& onFrame)
{
    StatsAccumulator accumulator(fOutputs, spec.skip, spec.limit, isDouble());
    size_t           block      = std::max<size_t>(spec.block, 1);
    double           sampleRate = fSampleRate;
    BlockTimer       timer(sampleRate);

    std::vector<std::vector<REAL>> ins(fInputs, std::vector<REAL>(block));
    std::vector<std::vector<REAL>> outs(fOutputs, std::vector<REAL>(block));
    // the buffers never move: their pointers are taken once
    std::vector<FAUSTFLOAT*>       inputs, outputs;
    for (auto& channel : ins) {
        inputs.push_back(reinterpret_cast<FAUSTFLOAT*>(channel.data()));
    }
    for (auto& channel : outs) {
        outputs.push_back(reinterpret_cast<FAUSTFLOAT*>(channel.data()));
    }
    // held for the first block only: FUI::setButtons in the impulse-test protocol
    std::vector<void*> buttons;
    if (spec.driveButtons) {
        for (const auto& entry : fControls.all()) {
            if (entry.second.kind == ControlKind::Button) {
                buttons.push_back(entry.second.zone);
            }
        }
    }
    std::vector<double> frame(fOutputs, 0.0);
    size_t              written = 0, cycle = 0;
    while (written < spec.frames) {
        // Apply anything due exactly here, then shorten the block so the next
        // event also lands on a boundary.
        for (const Event& event : spec.schedule.at(written)) {
            if (event.kind == Event::Kind::SetParam) {
                try {
                    set(event.path, event.value);
                } catch (const Failure&) {
                    // every scheduled write was checked before the render
                }
            }
        }
        size_t n = nextBlock(spec.schedule, block, spec.frames, written);
        for (void* zone : buttons) {
            setZone(zone, cycle == 0 ? 1.0 : 0.0);
        }
        for (size_t ch = 0; ch < fInputs; ch++) {
            for (size_t j = 0; j < n; j++) {
                ins[ch][j] = static_cast<REAL>(spec.input.sample(ch, written + j, sampleRate));
            }
        }
        // the compute call and nothing else: not the excitation, not the
        // statistics, not the dump
        uint64_t started = spec.time ? nowNanos() : 0;
        fDsp->compute(static_cast<int>(n), inputs.data(), outputs.data());
        if (spec.time) {
            timer.record(written, n, secondsSince(started));
        }
        for (size_t j = 0; j < n; j++) {
            for (size_t ch = 0; ch < fOutputs; ch++) {
                frame[ch] = static_cast<double>(outs[ch][j]);
            }
            accumulator.push(written + j, frame);
            if (written + j >= spec.skip) {
                onFrame(written + j, frame);
            }
        }
        written += n;
        cycle++;
    }
    RenderStats stats = accumulator.finish();
    if (spec.time) {
        stats.timing = timer.finish();
    }
    return stats;
}

// Choosing the buffer type here is what keeps a wrong width from corrupting memory.
RenderStats Probe::render(const RenderSpec& spec, const FrameCallback& onFrame)
{
    return isDouble() ? renderAt<double>(spec, onFrame) : renderAt<float>(spec, onFrame);
}

// The window's samples, in addition to the statistics.
RenderStats Probe::collect(const RenderSpec& spec, Samples& samples)
{
    samples.start = spec.skip;
    samples.channels.assign(fOutputs, std::vector<double>());
    for (std::vector<double>& channel : samples.channels) {
        channel.reserve(spec.frames > spec.skip ? spec.frames - spec.skip : 0);
    }
    return render(spec, [&samples](size_t, const std::vector<double>& frame) {
        for (size_t ch = 0; ch < frame.size(); ch++) {
            samples.channels[ch].push_back(frame[ch]);
        }
    });
}

// One compute call, its buffers converted from and to doubles.
template <typename REAL>
Channels Probe::computeAt(const Channels& inputs, size_t frames)
{
    std::vector<std::vector<REAL>> ins(fInputs, std::vector<REAL>(frames));
    std::vector<std::vector<REAL>> outs(fOutputs, std::vector<REAL>(frames));
    std::vector<FAUSTFLOAT*>       inputPointers, outputPointers;
    for (size_t ch = 0; ch < fInputs; ch++) {
        for (size_t i = 0; i < frames; i++) {
            ins[ch][i] = static_cast<REAL>(inputs[ch][i]);
        }
        inputPointers.push_back(reinterpret_cast<FAUSTFLOAT*>(ins[ch].data()));
    }
    for (auto& channel : outs) {
        outputPointers.push_back(reinterpret_cast<FAUSTFLOAT*>(channel.data()));
    }
    fDsp->compute(static_cast<int>(frames), inputPointers.data(), outputPointers.data());
    Channels result;
    for (const auto& channel : outs) {
        result.push_back(std::vector<double>(channel.begin(), channel.end()));
    }
    return result;
}

// See render(): the width decides the buffers.
Channels Probe::computeRaw(const Channels& inputs, size_t frames)
{
    return isDouble() ? computeAt<double>(inputs, frames) : computeAt<float>(inputs, frames);
}
