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
    size_t   start = 0;  // absolute frame of the window's first sample (--skip)
    Channels channels;
    size_t   frames() const { return channels.empty() ? 0 : channels[0].size(); }
};

// A pair agrees when |a - b| <= abs + rel * peak, peak being the largest
// magnitude of the reference on that output. With both at zero, agreement is
// bit equality. A non-finite sample agrees only with the very same bits.
struct Tolerance {
    // absolute part, and the part relative to the reference's peak
    double abs = 0.0;
    double rel = 0.0;
};

// A pair of samples that does not agree, and where.
struct Disagreement {
    size_t frame = 0;
    double value = 0.0;
    double reference = 0.0;
};

// One output of a comparison.
struct ChannelDiff {
    bool                   identical = true;  // every pair has the same bits
    double                 maxAbs    = 0.0;  // largest |a - b| over the finite pairs
    Optional<size_t>       maxAbsAt;  // first frame at that distance
    double                 maxRel = 0.0;  // maxAbs over the reference's peak, infinite if it is silent
    Optional<Disagreement> firstBeyond;  // the first pair beyond the tolerance
};

// A render compared with a reference, output by output.
struct Comparison {
    std::vector<std::pair<size_t, ChannelDiff>> channels;  // with the index of the output

    // Whether every compared output is within the tolerance.
    bool agrees() const;
    // The earliest disagreement and its output; the lowest output wins a tie.
    Optional<std::pair<size_t, Disagreement>> firstBeyond() const;
};

// Compares 'outputs' (every output when null). Renders of different shapes are
// refused: a comparison of what the two have in common would call them equal.
Comparison compare(const Samples& render, const Samples& reference, const Tolerance& tolerance,
                   const std::vector<size_t>* outputs);

// ---------------------------------------------------------------- reductions

// What --reduce makes of a render: one number per output.
enum class Reduction { Rms, Peak, Energy, Dc, F0, Sfdr, Thd };
const char* reductionName(Reduction reduction);
Reduction   parseReduction(const std::string& name);

// In-place radix-2 FFT: both vectors have the same power-of-two length.
void   fft(std::vector<double>& re, std::vector<double>& im);
// Frequency of the strongest non-DC bin.
double dominantFrequency(const std::vector<double>& samples, double sampleRate);
// dB from the fundamental down to the loudest component off its harmonic grid, and
// dB of the harmonics against the fundamental. f0 <= 0 estimates the fundamental.
double sfdrDb(const std::vector<double>& samples, double sampleRate, double f0);
double thdDb(const std::vector<double>& samples, double sampleRate, double f0);

// ---------------------------------------------------------------- --describe

// The parameters every descriptor shares.
struct DescribeSettings {
    double hopSeconds = 0.01;  // envelope frame, --describe-hop
    size_t fft        = 2048;  // transform length of centroid, --describe-fft
};

// A stretch of the window, in seconds from its first frame.
struct DescribeRange {
    double from = 0.0;
    double to   = 0.0;
    std::pair<size_t, size_t> samples(double sr) const;
    std::string               text() const;
};

// One descriptor of --describe.
struct Descriptor {
    enum class Kind { Loudness, Attack, Decay, Sustain, Centroid, Width };
    Kind                    kind = Kind::Loudness;
    double                  db   = 30.0;  // the fall of Decay
    Optional<DescribeRange> range;

    // The canonical spelling, which heads the descriptor's column.
    std::string name() const;
    bool        operator==(const Descriptor& other) const;
};

// Parses --describe. checkDescriptors() refuses, before any render, what cannot be
// measured on that window; describe() then assumes what it verified.
std::vector<Descriptor> parseDescriptors(const std::string& text);
void                    checkDescriptors(const std::vector<Descriptor>& descriptors, const DescribeSettings& settings,
                                         size_t outputs, size_t window, double sr);
std::vector<double>     describe(const Channels& channels, double sr, const std::vector<Descriptor>& descriptors,
                                 const DescribeSettings& settings);

// ---------------------------------------------------------------- --freqresp

constexpr double kRinging = 1e-6;  // above this share of the energy, a response still rings

// The frequencies of a response: log-spaced, the two ends included.
struct FreqGrid {
    size_t points = 0;
    double fmin   = 0.0;
    double fmax   = 0.0;
    // Parses N or N:FMIN:FMAX; without a range, 20 Hz to half the sample rate.
    static FreqGrid     parse(const std::string& spec, double sampleRate);
    std::vector<double> frequencies() const;
};

// One point of a response: 20 log10 |H|, and the argument of H in (-pi, pi].
struct FreqPoint {
    double magnitudeDb = 0.0;
    double phase       = 0.0;
};

// The transform of the samples at each frequency, by direct summation: no bin grid
// decides where the response is known.
std::vector<FreqPoint> frequencyResponse(const std::vector<double>& samples, double sampleRate,
                                         const std::vector<double>& hz);
// The share of the energy in the last tenth, absent for a response that is all zero.
Optional<double>       tailEnergyFraction(const std::vector<double>& samples);
// Rounding in a linear filter stays far below it, a real nonlinearity far above.
double                 defaultLinearityTolerance(bool isDouble);
// The delay of the time-invariance check: 37, or a quarter of a short window.
size_t                 shiftFor(size_t frames);

// One of the three properties checked before a response is transformed.
enum class Property { Homogeneity, TimeInvariance, Superposition };
// In the order they are checked: the first failure names the defect.
const std::vector<Property>&             allProperties();
const char*                              propertyName(Property property);
// The excitation of the check, (frame, amplitude), and what a linear time-invariant
// program answers to it given its response h to the unit impulse.
std::vector<std::pair<size_t, double>>   propertyTaps(Property property, size_t shift);
Samples                                  propertyExpected(Property property, const Samples& h, size_t shift);
// What the check found false, at for the frame of the unit impulse, and what usually
// explains it.
std::string                              propertyViolation(Property property, size_t at, size_t shift);
const char*                              propertyUsualCause(Property property);

// ---------------------------------------------------------------- --time

// The block that came closest to its deadline.
struct WorstBlock {
    size_t frame   = 0;
    size_t frames  = 0;
    double seconds = 0.0;
};

// The cost of the compute calls of one render, or of several added up.
struct Timing {
    double               sampleRate = 0.0;
    size_t               frames     = 0;
    size_t               blocks     = 0;
    double               computeSeconds = 0.0;
    Optional<WorstBlock> worst;

    // The duration of what was computed; how many times faster than real time; the time
    // a host leaves a block of that many frames.
    double           audioSeconds() const { return double(frames) / sampleRate; }
    double           realtimeFactor() const { return audioSeconds() / computeSeconds; }
    double           budgetSeconds(size_t count) const { return double(count) / sampleRate; }
    // The worst block's time against its own budget.
    Optional<double> worstBudgetFraction() const;
    // Adds another render of the same program: the next point of a sweep.
    void             absorb(const Timing& other);
};

// Accumulates the blocks of a render. The worst block is measured against its own
// budget: a block of one frame that takes as long as one of sixty-four is closer to
// its deadline. The first of two equally bad blocks is kept.
class BlockTimer {
   public:
    // A timer for a program running at this rate.
    explicit BlockTimer(double sampleRate);
    void   record(size_t frame, size_t frames, double seconds);
    Timing finish() const { return fTiming; }

   private:
    Timing fTiming;
    double fWorstFraction;
};

#endif
