/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This file is part of faustprobe, the offline probe of a Faust program.
 It is distributed under the same license as the Faust tools: see
 COPYING.txt at the root of the repository.
 ************************************************************************/

// What is computed from samples, whoever rendered them: renders compared,
// reductions, descriptors of a sound, a frequency response, the cost of a
// render. Nothing here knows a DSP, so all of it can be tested without one.

#ifndef __faustprobe_analysis__
#define __faustprobe_analysis__

#include <string>
#include <utility>
#include <vector>

#include "audio.h"
#include "text.h"

// ---------------------------------------------------------------- comparison

// The samples of one render: channels[ch][k] is output ch at the k-th frame of
// the window, whose first frame is 'start'.
struct Samples {
    size_t   start = 0;
    Channels channels;
    size_t   frames() const { return channels.empty() ? 0 : channels[0].size(); }
};

// A pair agrees when |a - b| <= abs + rel * peak, peak being the largest
// magnitude of the reference on that output. With both at zero, agreement is
// bit equality. A non-finite sample agrees only with the very same bits.
struct Tolerance {
    double abs = 0.0;
    double rel = 0.0;
};

struct Disagreement {
    size_t frame = 0;
    double value = 0.0;
    double reference = 0.0;
};

struct ChannelDiff {
    bool                   identical = true;
    double                 maxAbs    = 0.0;
    Optional<size_t>       maxAbsAt;
    double                 maxRel = 0.0;
    Optional<Disagreement> firstBeyond;
};

struct Comparison {
    std::vector<std::pair<size_t, ChannelDiff>> channels;  // with the index of the output

    bool agrees() const;
    // The earliest disagreement and its output; the lowest output wins a tie.
    Optional<std::pair<size_t, Disagreement>> firstBeyond() const;
};

// Compares 'outputs' (every output when null). Renders of different shapes are
// refused: a comparison of what the two have in common would call them equal.
Comparison compare(const Samples& render, const Samples& reference, const Tolerance& tolerance,
                   const std::vector<size_t>* outputs);

// ---------------------------------------------------------------- reductions

enum class Reduction { Rms, Peak, Energy, Dc, F0, Sfdr, Thd };
const char* reductionName(Reduction reduction);
Reduction   parseReduction(const std::string& name);

void   fft(std::vector<double>& re, std::vector<double>& im);
double dominantFrequency(const std::vector<double>& samples, double sampleRate);
double sfdrDb(const std::vector<double>& samples, double sampleRate, double f0);
double thdDb(const std::vector<double>& samples, double sampleRate, double f0);

// ---------------------------------------------------------------- --describe

struct DescribeSettings {
    double hopSeconds = 0.01;
    size_t fft        = 2048;
};

struct DescribeRange {
    double from = 0.0;
    double to   = 0.0;
    std::pair<size_t, size_t> samples(double sr) const;
    std::string               text() const;
};

struct Descriptor {
    enum class Kind { Loudness, Attack, Decay, Sustain, Centroid, Width };
    Kind                    kind = Kind::Loudness;
    double                  db   = 30.0;  // the fall of Decay
    Optional<DescribeRange> range;

    // The canonical spelling, which heads the descriptor's column.
    std::string name() const;
    bool        operator==(const Descriptor& other) const;
};

std::vector<Descriptor> parseDescriptors(const std::string& text);
void                    checkDescriptors(const std::vector<Descriptor>& descriptors, const DescribeSettings& settings,
                                         size_t outputs, size_t window, double sr);
std::vector<double>     describe(const Channels& channels, double sr, const std::vector<Descriptor>& descriptors,
                                 const DescribeSettings& settings);

// ---------------------------------------------------------------- --freqresp

constexpr double kRinging = 1e-6;  // above this share of the energy, a response still rings

struct FreqGrid {
    size_t points = 0;
    double fmin   = 0.0;
    double fmax   = 0.0;
    static FreqGrid     parse(const std::string& spec, double sampleRate);
    std::vector<double> frequencies() const;
};

struct FreqPoint {
    double magnitudeDb = 0.0;
    double phase       = 0.0;
};

std::vector<FreqPoint> frequencyResponse(const std::vector<double>& samples, double sampleRate,
                                         const std::vector<double>& hz);
Optional<double>       tailEnergyFraction(const std::vector<double>& samples);
double                 defaultLinearityTolerance(bool isDouble);
size_t                 shiftFor(size_t frames);

// One of the three properties checked before a response is transformed.
enum class Property { Homogeneity, TimeInvariance, Superposition };
const std::vector<Property>&             allProperties();
const char*                              propertyName(Property property);
std::vector<std::pair<size_t, double>>   propertyTaps(Property property, size_t shift);
Samples                                  propertyExpected(Property property, const Samples& h, size_t shift);
std::string                              propertyViolation(Property property, size_t at, size_t shift);
const char*                              propertyUsualCause(Property property);

// ---------------------------------------------------------------- --time

struct WorstBlock {
    size_t frame   = 0;
    size_t frames  = 0;
    double seconds = 0.0;
};

struct Timing {
    double               sampleRate = 0.0;
    size_t               frames     = 0;
    size_t               blocks     = 0;
    double               computeSeconds = 0.0;
    Optional<WorstBlock> worst;

    double           audioSeconds() const { return double(frames) / sampleRate; }
    double           realtimeFactor() const { return audioSeconds() / computeSeconds; }
    double           budgetSeconds(size_t count) const { return double(count) / sampleRate; }
    Optional<double> worstBudgetFraction() const;
    void             absorb(const Timing& other);
};

class BlockTimer {
   public:
    explicit BlockTimer(double sampleRate);
    void   record(size_t frame, size_t frames, double seconds);
    Timing finish() const { return fTiming; }

   private:
    Timing fTiming;
    double fWorstFraction;
};

#endif
