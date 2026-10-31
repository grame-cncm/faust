/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This file is part of faustprobe, the offline probe of a Faust program.
 It is distributed under the same license as the Faust tools: see
 COPYING.txt at the root of the repository.
 ************************************************************************/

// N voices of one factory and an optional effect: the allocation of
// architecture/faust/dsp/poly-dsp.h in its MIDI-allocated mode, at the width
// of the program. poly-dsp.h itself mixes FAUSTFLOAT buffers of a size fixed
// when it is compiled, and this tool chooses its width at run time: the
// decisions are the header's, the samples are carried in doubles.

#ifndef __faustprobe_poly__
#define __faustprobe_poly__

#include <memory>
#include <string>
#include <vector>

#include "engine.h"

constexpr double kDefaultVoiceStopLevel = 0.00003162;  // VOICE_STOP_LEVEL, -90 dB

// How a /freq or /key path takes a MIDI pitch, and a /gain or /vel path a velocity:
// mixed up, they detune every note by an octave-scale factor.
enum class KeyConversion { Freq, Key };
enum class VelConversion { Gain, Velocity };

// A voice's control paths, found by suffix, as dsp_voice::extractPaths does.
struct VoiceControlPaths {
    std::vector<std::string> gate, freq, gain;
    KeyConversion            keyFun = KeyConversion::Freq;
    VelConversion            velFun = VelConversion::Gain;
};

// One voice's bookkeeping: the fields of dsp_voice.
struct VoiceState {
    int      curNote  = -1;  // a pitch, or kFreeVoice, kReleaseVoice, kLegatoVoice
    int      nextNote = -1;  // in the legato state, the pitch queued
    int      nextVel  = -1;  // and its velocity
    uint64_t date     = 0;  // allocation counter: higher is more recent
    double   level    = 0.0;  // RMS of its last block
};

// What RenderSpec holds, less the driving of buttons: only a note presses a gate.
struct PolyRenderSpec {
    size_t           frames = 15000;
    size_t           block  = 64;
    InputMode        input;
    size_t           skip = 0;
    Schedule         schedule;
    Optional<double> limit;
    bool             time = false;
};

// Where a broadcast write lands: the control of every voice, or one of the effect.
enum class PolyTarget { Voices, Effect };

// One control a broadcast write reaches, with the value it would take.
struct PolyWrite {
    PolyTarget target;
    Write      write;
    const char* place() const { return target == PolyTarget::Voices ? "on every voice" : "on the effect"; }
};

// The instrument: voices of one factory, their mix, and an optional effect.
class PolyProbe {
   public:
    // The effect comes from 'effectPath' when given. Otherwise a program that
    // declares 'effect' has it extracted the way dsp_poly_factory does: the
    // source wrapped in environment{}, through the same adaptor.
    PolyProbe(const std::string& path, const std::vector<std::string>& importDirs, int sampleRate, bool isDouble,
              int optLevel, size_t nvoices, const Optional<std::string>& effectPath, double stopLevel);

    // What the instrument is: outputs() are the effect's when there is one, busOutputs()
    // those of a voice; warnings() what the construction left out without failing.
    size_t                          voiceCount() const { return fVoices.size(); }
    size_t                          inputs() const { return fInputs; }
    size_t                          outputs() const { return fOutputs; }
    size_t                          busOutputs() const { return fBusOutputs; }
    int                             sampleRate() const { return fSampleRate; }
    bool                            isDouble() const { return fVoices[0].probe->isDouble(); }
    bool                            hasEffect() const { return fEffect != nullptr; }
    const std::vector<std::string>& warnings() const { return fWarnings; }
    const ControlMap&               voiceControls() const { return fVoices[0].probe->controls(); }
    size_t                          activeVoiceCount() const;

    // Back to a freshly compiled instrument: every voice free, state cleared.
    void                   reset();
    // What setAll would write and where, each against the range of its own control. A
    // value outside it is the caller's to judge; nothing is written.
    std::vector<PolyWrite> checkWrite(const std::string& query, double value) const;
    // Writes a control on every voice, and on the effect if it resolves there.
    void                   setAll(const std::string& query, double value);
    // Notes and writes applied at their exact frames; the very statistics of a scalar render.
    RenderStats            render(const PolyRenderSpec& spec, const FrameCallback& onFrame);

   private:
    // An instance, and the paths a note writes to.
    struct Voice {
        std::unique_ptr<Probe> probe;
        VoiceControlPaths      paths;
    };

    // mydsp_poly::keyOn and keyOff.
    void     keyOn(int pitch, int velocity);
    void     keyOff(int pitch);
    // One host block: the voices, their mix, the effect.
    Channels computeWithInputs(const Channels& inputs, size_t frames);
    // One block of a stolen voice.
    Channels computeLegato(size_t voice, size_t frames, const Channels& inputs);
    // The zone writes of a note.
    void     writeKeyOn(size_t voice, double freq, double gain);
    void     writeGate(size_t voice, double value);

    std::vector<Voice>      fVoices;  // instances of one factory
    std::vector<VoiceState> fStates;  // one per voice
    std::unique_ptr<Probe>  fEffect;  // run once on the mix; null without one
    double                  fStopLevel;  // below it a releasing voice is free
    KeyConversion           fKeyFun = KeyConversion::Freq;
    VelConversion           fVelFun = VelConversion::Gain;
    size_t                  fInputs     = 0;  // of one voice
    size_t                  fBusOutputs = 0;  // of one voice: the width of the mix
    size_t                  fOutputs    = 0;  // of the instrument
    std::vector<std::string> fWarnings;
    int                     fSampleRate;
};

#endif
