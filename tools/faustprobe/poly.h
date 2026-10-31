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

enum class KeyConversion { Freq, Key };
enum class VelConversion { Gain, Velocity };

// A voice's control paths, found by suffix, as dsp_voice::extractPaths does.
struct VoiceControlPaths {
    std::vector<std::string> gate, freq, gain;
    KeyConversion            keyFun = KeyConversion::Freq;
    VelConversion            velFun = VelConversion::Gain;
};

struct VoiceState {
    int      curNote  = -1;  // a pitch, or kFreeVoice, kReleaseVoice, kLegatoVoice
    int      nextNote = -1;
    int      nextVel  = -1;
    uint64_t date     = 0;
    double   level    = 0.0;
};

struct PolyRenderSpec {
    size_t           frames = 15000;
    size_t           block  = 64;
    InputMode        input;
    size_t           skip = 0;
    Schedule         schedule;
    Optional<double> limit;
    bool             time = false;
};

enum class PolyTarget { Voices, Effect };

// One control a broadcast write reaches, with the value it would take.
struct PolyWrite {
    PolyTarget target;
    Write      write;
    const char* place() const { return target == PolyTarget::Voices ? "on every voice" : "on the effect"; }
};

class PolyProbe {
   public:
    // The effect comes from 'effectPath' when given. Otherwise a program that
    // declares 'effect' has it extracted the way dsp_poly_factory does: the
    // source wrapped in environment{}, through the same adaptor.
    PolyProbe(const std::string& path, const std::vector<std::string>& importDirs, int sampleRate, bool isDouble,
              int optLevel, size_t nvoices, const Optional<std::string>& effectPath, double stopLevel);

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
    std::vector<PolyWrite> checkWrite(const std::string& query, double value) const;
    void                   setAll(const std::string& query, double value);
    RenderStats            render(const PolyRenderSpec& spec, const FrameCallback& onFrame);

   private:
    struct Voice {
        std::unique_ptr<Probe> probe;
        VoiceControlPaths      paths;
    };

    void     keyOn(int pitch, int velocity);
    void     keyOff(int pitch);
    Channels computeWithInputs(const Channels& inputs, size_t frames);
    Channels computeLegato(size_t voice, size_t frames, const Channels& inputs);
    void     writeKeyOn(size_t voice, double freq, double gain);
    void     writeGate(size_t voice, double value);

    std::vector<Voice>      fVoices;
    std::vector<VoiceState> fStates;
    std::unique_ptr<Probe>  fEffect;
    double                  fStopLevel;
    KeyConversion           fKeyFun = KeyConversion::Freq;
    VelConversion           fVelFun = VelConversion::Gain;
    size_t                  fInputs     = 0;
    size_t                  fBusOutputs = 0;
    size_t                  fOutputs    = 0;
    std::vector<std::string> fWarnings;
    int                     fSampleRate;
};

#endif
