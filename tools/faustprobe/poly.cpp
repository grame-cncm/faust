/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This file is part of faustprobe, the offline probe of a Faust program.
 It is distributed under the same license as the Faust tools: see
 COPYING.txt at the root of the repository.
 ************************************************************************/

#include "poly.h"

#include <algorithm>
#include <cmath>

// As in poly-dsp.h.
static const int kFreeVoice    = -1;
static const int kReleaseVoice = -2;
static const int kLegatoVoice  = -3;

// dsp_voice::midiToFreq.
static double midiToFreq(double note)
{
    return 440.0 * pow(2.0, (note - 69.0) / 12.0);
}

// What a note writes, by the conversion its control's name selected.
static double convertKey(KeyConversion conversion, int pitch)
{
    return conversion == KeyConversion::Freq ? midiToFreq(pitch) : double(pitch);
}

// And what a velocity is worth: 0..1 for /gain, as it is for /vel.
static double convertVelocity(VelConversion conversion, int velocity)
{
    return conversion == VelConversion::Gain ? double(velocity) / 127.0 : double(velocity);
}

// In the order of std::map, as MapUI's own: extractPaths overwrites the
// conversions on every match, so that the last path sorted decides.
static VoiceControlPaths extractPaths(const ControlMap& controls)
{
    VoiceControlPaths result;
    for (const auto& entry : controls.all()) {
        const std::string& path = entry.first;
        if (endsWith(path, "/gate")) {
            result.gate.push_back(path);
        } else if (endsWith(path, "/freq")) {
            result.keyFun = KeyConversion::Freq;
            result.freq.push_back(path);
        } else if (endsWith(path, "/key")) {
            result.keyFun = KeyConversion::Key;
            result.freq.push_back(path);
        } else if (endsWith(path, "/gain")) {
            result.velFun = VelConversion::Gain;
            result.gain.push_back(path);
        } else if (endsWith(path, "/vel") || endsWith(path, "/velocity")) {
            result.velFun = VelConversion::Velocity;
            result.gain.push_back(path);
        }
    }
    return result;
}

// The oldest voice sounding 'pitch', one mid-steal whose queued note it is
// included: getPlayingVoice. keyOn never asks: a repeated note takes a voice.
static int getPlayingVoice(const std::vector<VoiceState>& voices, int pitch)
{
    int      best = -1;
    uint64_t date = 0;
    for (size_t i = 0; i < voices.size(); i++) {
        const VoiceState& v       = voices[i];
        bool              matches = v.curNote == pitch || (v.curNote == kLegatoVoice && v.nextNote == pitch);
        if (matches && (best < 0 || v.date < date)) {
            best = static_cast<int>(i);
            date = v.date;
        }
    }
    return best;
}

// The first free voice; failing that the oldest releasing one; failing that
// the oldest playing one, stolen: getFreeVoice.
static int getFreeVoice(const std::vector<VoiceState>& voices, bool& steal)
{
    for (size_t i = 0; i < voices.size(); i++) {
        if (voices[i].curNote == kFreeVoice) {
            steal = false;
            return static_cast<int>(i);
        }
    }
    int      release = -1, playing = -1;
    uint64_t releaseDate = 0, playingDate = 0;
    for (size_t i = 0; i < voices.size(); i++) {
        const VoiceState& v = voices[i];
        if (v.curNote == kReleaseVoice) {
            if (release < 0 || v.date < releaseDate) {
                release     = static_cast<int>(i);
                releaseDate = v.date;
            }
        } else if (playing < 0 || v.date < playingDate) {
            playing     = static_cast<int>(i);
            playingDate = v.date;
        }
    }
    steal = true;
    return release >= 0 ? release : playing;
}

// Mixes a voice's block into 'out', and returns the voice's own RMS level.
static double mixCheckVoice(const Channels& voice, Channels& out)
{
    double sumSquares = 0.0;
    size_t total      = 0;
    for (size_t ch = 0; ch < voice.size(); ch++) {
        for (size_t i = 0; i < voice[ch].size(); i++) {
            sumSquares += voice[ch][i] * voice[ch][i];
            out[ch][i] += voice[ch][i];
        }
        total += voice[ch].size();
    }
    return total == 0 ? 0.0 : sqrt(sumSquares / double(total));
}

// fadeOut: a linear fade of the first half, over the outgoing note, across the splice.
static void fadeOut(Channels& buffer, size_t half)
{
    if (half == 0) {
        return;
    }
    double step = 1.0 / double(half);
    for (std::vector<double>& channel : buffer) {
        double factor = 1.0;
        for (size_t i = 0; i < half && i < channel.size(); i++) {
            channel[i] *= factor;
            factor -= step;
        }
    }
}

// A wrapper compiled and instantiated; null when the compiler refuses it, which is
// what a program without effect looks like.
static std::unique_ptr<Probe> compileInlineEffect(const std::string& wrapped, const std::string& path,
                                                  const std::vector<std::string>& importDirs, int sampleRate,
                                                  bool isDouble, int optLevel)
{
    try {
        std::shared_ptr<Factory> factory =
            Factory::compileString("faustprobe-effect", path, wrapped, importDirs, {}, isDouble, optLevel);
        return std::unique_ptr<Probe>(new Probe(factory, sampleRate));
    } catch (const Failure&) {
        return nullptr;
    }
}

// See poly.h. One compilation for every voice; the effect comes after, so that it can
// be checked against the width of a voice.
PolyProbe::PolyProbe(const std::string& path, const std::vector<std::string>& importDirs, int sampleRate,
                     bool isDouble, int optLevel, size_t nvoices, const Optional<std::string>& effectPath,
                     double stopLevel)
    : fStopLevel(stopLevel), fSampleRate(sampleRate)
{
    std::shared_ptr<Factory> factory = Factory::compileFile(path, importDirs, {}, isDouble, optLevel);
    for (size_t i = 0; i < nvoices; i++) {
        Voice voice;
        voice.probe.reset(new Probe(factory, sampleRate));
        voice.paths = extractPaths(voice.probe->controls());
        fVoices.push_back(std::move(voice));
    }
    // the voices are instances of one DSP: the first speaks for all
    fBusOutputs = fVoices[0].probe->outputs();
    fInputs     = fVoices[0].probe->inputs();
    fKeyFun     = fVoices[0].paths.keyFun;
    fVelFun     = fVoices[0].paths.velFun;
    fStates.assign(nvoices, VoiceState());

    if (effectPath) {
        std::shared_ptr<Factory> compiled = Factory::compileFile(*effectPath, importDirs, {}, isDouble, optLevel);
        fEffect.reset(new Probe(compiled, sampleRate));
        if (fEffect->inputs() != fBusOutputs) {
            throw Failure("--effect expects " + str(fEffect->inputs()) + " input(s) but the poly bus produces " +
                          str(fBusOutputs) +
                          "; channel-arity auto-adaptation is out of scope for this tool, pass a matching effect");
        }
    } else {
        std::string source;
        try {
            source = readTextFile(path);
        } catch (const Failure&) {
            source.clear();
        }
        if (!source.empty()) {
            // dsp_poly_factory::getEffectCode: the adaptor splits the process
            // outputs into the effect inputs when there are at least as many
            // inputs, and merges them otherwise.
            std::string wrapped =
                "bus(n) = par(i,n,_); adapt(1,n,m) = bus(n) <: bus(m); adapt(0,n,m) = bus(n) :> bus(m);\n"
                "adaptor(F,G) = adapt(outputs(F) <= inputs(G), outputs(F), inputs(G));\n"
                "dsp_code = environment{ " +
                source +
                " };\n"
                "process = adaptor(dsp_code.process, dsp_code.effect) : dsp_code.effect;\n";
            std::unique_ptr<Probe> effect =
                compileInlineEffect(wrapped, path, importDirs, sampleRate, isDouble, optLevel);
            if (effect != nullptr) {
                // the adaptor's inputs are the process outputs by construction
                if (effect->inputs() == fBusOutputs) {
                    fEffect = std::move(effect);
                } else {
                    fWarnings.push_back("the program's adapted `effect` takes " + str(effect->inputs()) +
                                        " input(s) but a voice has " + str(fBusOutputs) +
                                        " output(s): the effect is left out");
                }
            } else {
                // Is there an effect the adaptor refuses, or none? A second
                // compile, paid on this path only: an effect dropped in
                // silence would render a dry instrument that looks intended.
                std::string alone = "dsp_code = environment{ " + source +
                                    " };\n"
                                    "process = dsp_code.effect;\n";
                effect = compileInlineEffect(alone, path, importDirs, sampleRate, isDouble, optLevel);
                if (effect != nullptr) {
                    fWarnings.push_back(
                        "the program's `effect` takes " + str(effect->inputs()) + " input(s) but a voice has " +
                        str(fBusOutputs) +
                        " output(s), which `poly-dsp.h`'s adaptor does not reconcile (one count must be a multiple "
                        "of the other): the effect is left out; pass a matching --effect FILE");
                }
            }
        }
    }
    fOutputs = fEffect != nullptr ? fEffect->outputs() : fBusOutputs;
}

// Releasing voices count: they still sound.
size_t PolyProbe::activeVoiceCount() const
{
    size_t count = 0;
    for (const VoiceState& state : fStates) {
        if (state.curNote != kFreeVoice) {
            count++;
        }
    }
    return count;
}

// A voice still releasing from one sweep point would otherwise sound in the next.
void PolyProbe::reset()
{
    for (Voice& voice : fVoices) {
        voice.probe->reset();
    }
    if (fEffect != nullptr) {
        fEffect->reset();
    }
    fStates.assign(fVoices.size(), VoiceState());
}

std::vector<PolyWrite> PolyProbe::checkWrite(const std::string& query, double value) const
{
    // Voices are instances of one DSP: a fragment that is unambiguous on one
    // is so on all. The effect is another DSP, with its own resolution.
    std::vector<PolyWrite> writes;
    auto                   visit = [&](PolyTarget target, const ControlMap& controls) {
        PolyWrite write;
        write.target = target;
        if (!controls.exists(query)) {
            return;
        }
        try {
            write.write = controls.checkWrite(query, value);
        } catch (const Failure& failure) {
            throw Failure(std::string(failure.what()) + " (" + write.place() + ")");
        }
        writes.push_back(write);
    };
    visit(PolyTarget::Voices, fVoices[0].probe->controls());
    if (fEffect != nullptr) {
        visit(PolyTarget::Effect, fEffect->controls());
    }
    if (writes.empty()) {
        throw Failure("no control matching `" + query + "` on any voice or the effect");
    }
    return writes;
}

// The clamp is that of a widget, already in the write. What a note writes is not a
// widget's doing and goes through writeKeyOn, unclamped, as in poly-dsp.h.
void PolyProbe::setAll(const std::string& query, double value)
{
    for (const PolyWrite& write : checkWrite(query, value)) {
        if (write.target == PolyTarget::Voices) {
            for (Voice& voice : fVoices) {
                voice.probe->setExact(write.write.control->path, write.write.applied);
            }
        } else {
            fEffect->setExact(write.write.control->path, write.write.applied);
        }
    }
}

// dsp_voice::keyOn: frequency, gate, gain, in that order.
void PolyProbe::writeKeyOn(size_t voice, double freq, double gain)
{
    const VoiceControlPaths& paths = fVoices[voice].paths;
    for (const std::string& path : paths.freq) {
        fVoices[voice].probe->setExact(path, freq);
    }
    writeGate(voice, 1.0);
    for (const std::string& path : paths.gain) {
        fVoices[voice].probe->setExact(path, gain);
    }
}

// Every path ending in /gate.
void PolyProbe::writeGate(size_t voice, double value)
{
    for (const std::string& path : fVoices[voice].paths.gate) {
        fVoices[voice].probe->setExact(path, value);
    }
}

// A free voice sounds at once; a stolen one waits for its tail to be rendered.
void PolyProbe::keyOn(int pitch, int velocity)
{
    bool steal = false;
    int  voice = getFreeVoice(fStates, steal);
    fStates[voice].date++;
    if (steal) {
        // the write waits for the outgoing note's tail: computeLegato
        fStates[voice].curNote  = kLegatoVoice;
        fStates[voice].nextNote = pitch;
        fStates[voice].nextVel  = velocity;
    } else {
        fStates[voice].curNote = pitch;
        writeKeyOn(voice, convertKey(fKeyFun, pitch), convertVelocity(fVelFun, velocity));
    }
}

// Without a voice sounding that pitch, nothing happens.
void PolyProbe::keyOff(int pitch)
{
    int voice = getPlayingVoice(fStates, pitch);
    if (voice >= 0) {
        fStates[voice].curNote = kReleaseVoice;
        writeGate(voice, 0.0);
    }
}

// A voice being stolen: the outgoing note's tail on the first half of the
// block, the incoming note's onset on the second half, faded across the
// splice. dsp_voice::computeLegato and the fadeOut that follows it.
Channels PolyProbe::computeLegato(size_t voice, size_t frames, const Channels& inputs)
{
    writeGate(voice, 0.0);
    size_t half = frames / 2, rest = frames - half;
    // each half of the block reads its own half of the inputs
    auto   slice = [&inputs](size_t from, size_t count) {
        Channels part;
        for (const std::vector<double>& channel : inputs) {
            part.push_back(std::vector<double>(channel.begin() + from, channel.begin() + from + count));
        }
        return part;
    };
    Channels first = fVoices[voice].probe->computeRaw(slice(0, half), half);

    int pitch = fStates[voice].nextNote, velocity = fStates[voice].nextVel;
    fStates[voice].curNote = pitch;
    writeKeyOn(voice, convertKey(fKeyFun, pitch), convertVelocity(fVelFun, velocity));

    Channels second = fVoices[voice].probe->computeRaw(slice(half, rest), rest);
    for (size_t ch = 0; ch < first.size(); ch++) {
        first[ch].insert(first[ch].end(), second[ch].begin(), second[ch].end());
    }
    fadeOut(first, half);
    return first;
}

// mydsp_poly::compute: the host's inputs go to every playing voice.
Channels PolyProbe::computeWithInputs(const Channels& inputs, size_t frames)
{
    // the width of a voice: the effect may change it
    Channels mixed(fBusOutputs, std::vector<double>(frames, 0.0));
    for (size_t i = 0; i < fVoices.size(); i++) {
        int curNote = fStates[i].curNote;
        if (curNote == kFreeVoice) {
            continue;
        }
        Channels output = curNote == kLegatoVoice ? computeLegato(i, frames, inputs)
                                                  : fVoices[i].probe->computeRaw(inputs, frames);
        double level    = mixCheckVoice(output, mixed);
        fStates[i].level = level;
        if (fStates[i].curNote == kReleaseVoice && level < fStopLevel) {
            fStates[i].curNote = kFreeVoice;
        }
    }
    return fEffect != nullptr ? fEffect->computeRaw(mixed, frames) : mixed;
}

// See engine.cpp, Probe::renderAt: the same loop over a whole instrument.
RenderStats PolyProbe::render(const PolyRenderSpec& spec, const FrameCallback& onFrame)
{
    StatsAccumulator accumulator(fOutputs, spec.skip, spec.limit, isDouble());
    size_t           block      = std::max<size_t>(spec.block, 1);
    double           sampleRate = fSampleRate;
    BlockTimer       timer(sampleRate);

    std::vector<double> frame(fOutputs, 0.0);
    size_t              written = 0;
    while (written < spec.frames) {
        // The note timing is what a release measurement reads: rounding it to
        // the block grid would put a systematic error into the result.
        for (const Event& event : spec.schedule.at(written)) {
            switch (event.kind) {
                case Event::Kind::NoteOn:
                    keyOn(event.pitch, event.velocity);
                    break;
                case Event::Kind::NoteOff:
                    keyOff(event.pitch);
                    break;
                case Event::Kind::SetParam:
                    setAll(event.path, event.value);
                    break;
            }
        }
        size_t   n = nextBlock(spec.schedule, block, spec.frames, written);
        Channels inputs(fInputs, std::vector<double>(n));
        for (size_t ch = 0; ch < fInputs; ch++) {
            for (size_t j = 0; j < n; j++) {
                inputs[ch][j] = spec.input.sample(ch, written + j, sampleRate);
            }
        }
        // the voices, their mix and the effect: what a host's callback runs
        uint64_t started = spec.time ? nowNanos() : 0;
        Channels output  = computeWithInputs(inputs, n);
        if (spec.time) {
            timer.record(written, n, secondsSince(started));
        }
        for (size_t j = 0; j < n; j++) {
            for (size_t ch = 0; ch < fOutputs; ch++) {
                frame[ch] = output[ch][j];
            }
            accumulator.push(written + j, frame);
            if (written + j >= spec.skip) {
                onFrame(written + j, frame);
            }
        }
        written += n;
    }
    RenderStats stats = accumulator.finish();
    if (spec.time) {
        stats.timing = timer.finish();
    }
    return stats;
}
