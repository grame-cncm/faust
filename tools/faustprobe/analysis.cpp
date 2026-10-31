/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This file is part of faustprobe, the offline probe of a Faust program.
 It is distributed under the same license as the Faust tools: see
 COPYING.txt at the root of the repository.
 ************************************************************************/

#include "analysis.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <limits>

// What a descriptor without a value, and a silent reference, are worth.
static const double kNaN      = std::numeric_limits<double>::quiet_NaN();
static const double kInfinity = std::numeric_limits<double>::infinity();
static const double kTau      = 6.283185307179586476925286766559;

// ---------------------------------------------------------------- comparison

// Equality of bits tells -0.0 from 0.0, and NaN equals itself.
static uint64_t bitsOf(double value)
{
    uint64_t bits;
    memcpy(&bits, &value, sizeof(bits));
    return bits;
}

// Only a disagreement beyond the tolerance counts.
bool Comparison::agrees() const
{
    for (const auto& channel : channels) {
        if (channel.second.firstBeyond) {
            return false;
        }
    }
    return true;
}

Optional<std::pair<size_t, Disagreement>> Comparison::firstBeyond() const
{
    Optional<std::pair<size_t, Disagreement>> best;
    for (const auto& channel : channels) {
        if (!channel.second.firstBeyond) {
            continue;
        }
        const Disagreement& d = *channel.second.firstBeyond;
        if (!best || d.frame < best.value.second.frame ||
            (d.frame == best.value.second.frame && channel.first < best.value.first)) {
            best = std::make_pair(channel.first, d);
        }
    }
    return best;
}

// One output. The tolerance is relative to the reference's peak over its finite samples.
static ChannelDiff compareChannel(const std::vector<double>& a, const std::vector<double>& b, size_t start,
                                  const Tolerance& tolerance)
{
    double peak = 0.0;
    for (double v : b) {
        if (std::isfinite(v)) {
            peak = std::max(peak, fabs(v));
        }
    }
    double      limit = tolerance.abs + tolerance.rel * peak;
    bool        exact = tolerance.abs == 0.0 && tolerance.rel == 0.0;
    ChannelDiff diff;
    for (size_t k = 0; k < a.size(); k++) {
        double value = a[k], reference = b[k];
        if (bitsOf(value) == bitsOf(reference)) {
            continue;
        }
        diff.identical  = false;
        double distance = fabs(value - reference);
        if (distance > diff.maxAbs) {
            diff.maxAbs   = distance;
            diff.maxAbsAt = start + k;
        }
        // The bits already differ: exact mode must reject signed-zero
        // differences too, and a non-finite sample requires identical bits.
        bool beyond = exact || !std::isfinite(value) || !std::isfinite(reference) || distance > limit;
        if (beyond && !diff.firstBeyond) {
            Disagreement d;
            d.frame          = start + k;
            d.value          = value;
            d.reference      = reference;
            diff.firstBeyond = d;
        }
    }
    diff.maxRel = diff.maxAbs == 0.0 ? 0.0 : (peak > 0.0 ? diff.maxAbs / peak : kInfinity);
    return diff;
}

// See analysis.h.
Comparison compare(const Samples& render, const Samples& reference, const Tolerance& tolerance,
                   const std::vector<size_t>* outputs)
{
    if (render.channels.size() != reference.channels.size()) {
        throw Failure("the render has " + str(render.channels.size()) + " output(s) and the reference " +
                      str(reference.channels.size()));
    }
    if (render.frames() != reference.frames()) {
        throw Failure("the render's window holds " + str(render.frames()) + " frames and the reference " +
                      str(reference.frames()));
    }
    if (render.start != reference.start) {
        throw Failure("the render's window starts at frame " + str(render.start) + " and the reference's at " +
                      str(reference.start));
    }
    std::vector<size_t> all;
    for (size_t ch = 0; ch < render.channels.size(); ch++) {
        all.push_back(ch);
    }
    Comparison comparison;
    for (size_t ch : (outputs != nullptr ? *outputs : all)) {
        if (ch >= render.channels.size()) {
            throw Failure("output " + str(ch) + " does not exist: the renders have " +
                          str(render.channels.size()) + " output(s)");
        }
        comparison.channels.push_back(
            std::make_pair(ch, compareChannel(render.channels[ch], reference.channels[ch], render.start, tolerance)));
    }
    return comparison;
}

// ---------------------------------------------------------------- reductions

// The name on the command line and in the column headers.
const char* reductionName(Reduction reduction)
{
    switch (reduction) {
        case Reduction::Rms:
            return "rms";
        case Reduction::Peak:
            return "peak";
        case Reduction::Energy:
            return "energy";
        case Reduction::Dc:
            return "dc";
        case Reduction::F0:
            return "f0";
        case Reduction::Sfdr:
            return "sfdr";
        default:
            return "thd";
    }
}

// Reads back reductionName().
Reduction parseReduction(const std::string& name)
{
    const Reduction all[] = {Reduction::Rms, Reduction::Peak, Reduction::Energy, Reduction::Dc,
                             Reduction::F0,  Reduction::Sfdr, Reduction::Thd};
    for (Reduction reduction : all) {
        if (name == reductionName(reduction)) {
            return reduction;
        }
    }
    throw Failure("unknown reduction `" + name + "`; expected rms, peak, energy, dc, f0, sfdr or thd");
}

// The smallest power of two at least n.
static size_t nextPowerOfTwo(size_t n)
{
    size_t power = 1;
    while (power < n) {
        power <<= 1;
    }
    return power;
}

// What the radix-2 transform needs.
static bool isPowerOfTwo(size_t n)
{
    return n != 0 && (n & (n - 1)) == 0;
}

// In-place iterative radix-2 FFT: re and im have the same power-of-two length.
void fft(std::vector<double>& re, std::vector<double>& im)
{
    // Bit-reversal permutation.
    size_t n = re.size();
    size_t j = 0;
    for (size_t i = 1; i < n; i++) {
        size_t bit = n >> 1;
        while (j & bit) {
            j ^= bit;
            bit >>= 1;
        }
        j |= bit;
        if (i < j) {
            std::swap(re[i], re[j]);
            std::swap(im[i], im[j]);
        }
    }
    // Butterflies, doubling the length; the twiddle factor is updated by recurrence.
    for (size_t len = 2; len <= n; len <<= 1) {
        double angle = -2.0 * M_PI / double(len);
        double wr = cos(angle), wi = sin(angle);
        for (size_t start = 0; start < n; start += len) {
            double cr = 1.0, ci = 0.0;
            for (size_t k = 0; k < len / 2; k++) {
                double ar = re[start + k], ai = im[start + k];
                double br = re[start + k + len / 2], bi = im[start + k + len / 2];
                double tr = br * cr - bi * ci, ti = br * ci + bi * cr;
                re[start + k]           = ar + tr;
                im[start + k]           = ai + ti;
                re[start + k + len / 2] = ar - tr;
                im[start + k + len / 2] = ai - ti;
                double ncr              = cr * wr - ci * wi;
                ci                      = cr * wi + ci * wr;
                cr                      = ncr;
            }
        }
    }
}

// Frequency of the strongest non-DC bin: the signal zero-padded to the next
// power of two, DC excluded because an offset would otherwise always win.
double dominantFrequency(const std::vector<double>& samples, double sampleRate)
{
    if (samples.size() < 2) {
        return 0.0;
    }
    size_t              n = nextPowerOfTwo(samples.size());
    std::vector<double> re(n, 0.0), im(n, 0.0);
    std::copy(samples.begin(), samples.end(), re.begin());
    fft(re, im);
    size_t best    = 1;
    double bestMag = -kInfinity;
    for (size_t k = 1; k < n / 2; k++) {
        double mag = std::fma(re[k], re[k], im[k] * im[k]);
        if (mag > bestMag) {
            bestMag = mag;
            best    = k;
        }
    }
    return double(best) * sampleRate / double(n);
}

// Bins within this of a harmonic are attributed to it: the window's main lobe
// is four bins wide.
static const int64_t kHarmonicGuard = 4;

// A windowed magnitude spectrum, and the bin position of the fundamental.
struct Spectrum {
    std::vector<double> mags;
    double              f0Bin = 0.0;
};

// Blackman-Harris windowed magnitudes, and the fundamental's bin position.
static bool prepareSpectrum(const std::vector<double>& samples, double sampleRate, double f0, Spectrum& spectrum)
{
    if (samples.size() < 8 || sampleRate <= 0.0) {
        return false;
    }
    double f = f0 > 0.0 ? f0 : dominantFrequency(samples, sampleRate);
    if (f <= 0.0) {
        return false;
    }
    // Blackman-Harris 4 terms: its sidelobes are 92 dB down, where the loud fundamental
    // of a rectangular window would bury what these measures look for.
    static const double a[4] = {0.35875, 0.48829, 0.14128, 0.01168};
    size_t              n    = nextPowerOfTwo(samples.size());
    std::vector<double> re(n, 0.0), im(n, 0.0);
    for (size_t i = 0; i < samples.size(); i++) {
        double x = 2.0 * M_PI * double(i) / double(samples.size());
        double w = a[0] - a[1] * cos(x) + a[2] * cos(2.0 * x) - a[3] * cos(3.0 * x);
        re[i]    = samples[i] * w;
    }
    fft(re, im);
    spectrum.mags.resize(n / 2 + 1);
    for (size_t k = 0; k <= n / 2; k++) {
        spectrum.mags[k] = hypot(re[k], im[k]);
    }
    spectrum.f0Bin = f / (sampleRate / double(n));
    return true;
}

// Largest magnitude within the guard band around a bin position.
static double peakNear(const std::vector<double>& mags, double bin)
{
    int64_t center = static_cast<int64_t>(round(bin));
    size_t  lo     = static_cast<size_t>(std::max<int64_t>(center - kHarmonicGuard, 1));
    size_t  hi     = std::min(static_cast<size_t>(center + kHarmonicGuard), mags.size() - 1);
    if (lo > hi) {
        return 0.0;
    }
    double peak = 0.0;
    for (size_t k = lo; k <= hi; k++) {
        peak = std::max(peak, mags[k]);
    }
    return peak;
}

// Whether bin k belongs to the harmonic grid of the fundamental.
static bool onGrid(size_t k, double f0Bin, size_t bins)
{
    if (f0Bin <= 0.0) {
        return false;
    }
    double position = double(k);
    double nearest  = std::max(round(position / f0Bin), 0.0);
    double centre   = nearest * f0Bin;
    return fabs(position - centre) <= double(kHarmonicGuard) && static_cast<size_t>(nearest) <= bins;
}

// Infinite when nothing is off the grid, 0 for a window too short or silent.
double sfdrDb(const std::vector<double>& samples, double sampleRate, double f0)
{
    Spectrum spectrum;
    if (!prepareSpectrum(samples, sampleRate, f0, spectrum)) {
        return 0.0;
    }
    double fundamental = peakNear(spectrum.mags, spectrum.f0Bin);
    if (fundamental <= 0.0) {
        return 0.0;
    }
    double worst = 0.0;
    for (size_t k = 1; k < spectrum.mags.size(); k++) {
        if (!onGrid(k, spectrum.f0Bin, spectrum.mags.size())) {
            worst = std::max(worst, spectrum.mags[k]);
        }
    }
    return worst <= 0.0 ? kInfinity : 20.0 * log10(fundamental / worst);
}

// Minus infinity for a pure tone, 0 for a window too short or silent.
double thdDb(const std::vector<double>& samples, double sampleRate, double f0)
{
    Spectrum spectrum;
    if (!prepareSpectrum(samples, sampleRate, f0, spectrum)) {
        return 0.0;
    }
    double fundamental = peakNear(spectrum.mags, spectrum.f0Bin);
    if (fundamental <= 0.0) {
        return 0.0;
    }
    double energy = 0.0;
    for (double n = 2.0; n * spectrum.f0Bin < double(spectrum.mags.size()); n += 1.0) {
        double m = peakNear(spectrum.mags, n * spectrum.f0Bin);
        energy += m * m;
    }
    return energy <= 0.0 ? -kInfinity : 20.0 * log10(sqrt(energy) / fundamental);
}

// ---------------------------------------------------------------- --describe

// Rounded to whole samples; ranges were checked non-negative.
static size_t secondsToSamples(double seconds, double sr)
{
    return static_cast<size_t>(std::max(round(seconds * sr), 0.0));
}

// The samples [from, to) at this rate.
std::pair<size_t, size_t> DescribeRange::samples(double sr) const
{
    return std::make_pair(secondsToSamples(from, sr), secondsToSamples(to, sr));
}

// A..B, in a descriptor's name.
std::string DescribeRange::text() const
{
    return plainNumber(from) + ".." + plainNumber(to);
}

// decay is always decay:30: one descriptor, one column name.
std::string Descriptor::name() const
{
    switch (kind) {
        case Kind::Loudness:
            return "loudness";
        case Kind::Attack:
            return "attack";
        case Kind::Decay:
            return "decay:" + plainNumber(db);
        case Kind::Sustain:
            return "sustain:" + range.value.text();
        case Kind::Centroid:
            return range ? "centroid:" + range.value.text() : "centroid";
        default:
            return range ? "width:" + range.value.text() : "width";
    }
}

// Two spellings of one descriptor are the same.
bool Descriptor::operator==(const Descriptor& other) const
{
    return name() == other.name();
}

// For the messages.
static const char* kAcceptedDescriptors =
    "loudness, attack, decay[:DB], sustain:A..B, centroid[:A..B], width[:A..B]";

// A..B in seconds, with 0 <= A < B.
static DescribeRange parseDescribeRange(const std::string& item, const std::string& parameter)
{
    size_t dots = parameter.find("..");
    if (dots == std::string::npos) {
        throw Failure("expected A..B (seconds) in `" + item + "`");
    }
    auto number = [&item](const std::string& text) {
        double value;
        if (!parseDouble(trim(text), value) || !std::isfinite(value)) {
            throw Failure("`" + text + "` is not a number of seconds in `" + item + "`");
        }
        return value;
    };
    DescribeRange range;
    range.from = number(parameter.substr(0, dots));
    range.to   = number(parameter.substr(dots + 2));
    if (!(range.from >= 0.0 && range.from < range.to)) {
        throw Failure("`" + item + "`: the stretch must satisfy 0 <= A < B");
    }
    return range;
}

// One item of the list: a name, and after a colon its parameter.
static Descriptor parseDescriptor(const std::string& item)
{
    size_t      colon        = item.find(':');
    bool        hasParameter = colon != std::string::npos;
    std::string name         = item.substr(0, colon);
    std::string parameter    = hasParameter ? item.substr(colon + 1) : "";
    Descriptor  descriptor;
    if (name == "loudness" || name == "attack") {
        if (hasParameter) {
            throw Failure("`" + name + "` takes no parameter, got `" + item + "`");
        }
        descriptor.kind = name == "attack" ? Descriptor::Kind::Attack : Descriptor::Kind::Loudness;
    } else if (name == "decay") {
        descriptor.kind = Descriptor::Kind::Decay;
        if (hasParameter) {
            if (!parseDouble(parameter, descriptor.db)) {
                throw Failure("`" + parameter + "` is not a number of dB in `" + item + "`");
            }
            if (!(std::isfinite(descriptor.db) && descriptor.db > 0.0)) {
                throw Failure("`" + item + "`: the fall must be a positive number of dB");
            }
        }
    } else if (name == "sustain") {
        if (!hasParameter) {
            throw Failure(
                "`sustain` needs the stretch it measures, in seconds from the window's start: `sustain:A..B`");
        }
        descriptor.kind  = Descriptor::Kind::Sustain;
        descriptor.range = parseDescribeRange(item, parameter);
    } else if (name == "centroid" || name == "width") {
        descriptor.kind = name == "centroid" ? Descriptor::Kind::Centroid : Descriptor::Kind::Width;
        if (hasParameter) {
            descriptor.range = parseDescribeRange(item, parameter);
        }
    } else {
        throw Failure("unknown descriptor `" + item + "`; expected " + kAcceptedDescriptors);
    }
    return descriptor;
}

// Items separated by commas; none may be empty, or given twice.
std::vector<Descriptor> parseDescriptors(const std::string& text)
{
    std::vector<Descriptor> list;
    for (const std::string& raw : split(text, ',')) {
        std::string item = trim(raw);
        if (item.empty()) {
            throw Failure("empty descriptor in `" + text + "`; expected " + kAcceptedDescriptors);
        }
        Descriptor descriptor = parseDescriptor(item);
        if (std::find(list.begin(), list.end(), descriptor) != list.end()) {
            throw Failure("`" + descriptor.name() + "` is given twice in `" + text + "`");
        }
        list.push_back(descriptor);
    }
    return list;
}

// The envelope frames lying wholly within the samples [from, to).
static std::pair<size_t, size_t> framesWithin(size_t from, size_t to, size_t hop)
{
    return std::make_pair((from + hop - 1) / hop, to / hop);
}

// See analysis.h. Each descriptor needs a stretch inside the window and enough of it.
void checkDescriptors(const std::vector<Descriptor>& descriptors, const DescribeSettings& settings, size_t outputs,
                      size_t window, double sr)
{
    if (!(std::isfinite(settings.hopSeconds) && settings.hopSeconds > 0.0)) {
        throw Failure("--describe-hop must be a positive number of seconds");
    }
    size_t hop = secondsToSamples(settings.hopSeconds, sr);
    if (hop == 0) {
        throw Failure("--describe-hop " + plainNumber(settings.hopSeconds) + " is shorter than one sample at " +
                      plainNumber(sr) + " Hz");
    }
    if (!(isPowerOfTwo(settings.fft) && settings.fft >= 8)) {
        throw Failure("--describe-fft " + str(settings.fft) + " must be a power of two of at least 8");
    }
    if (outputs == 0) {
        throw Failure("--describe needs a program with outputs");
    }
    double duration = double(window) / sr;
    // A stretch in samples, refused when it ends beyond the window.
    auto   within   = [&](const Descriptor& descriptor, const DescribeRange& range) {
        std::pair<size_t, size_t> samples = range.samples(sr);
        if (samples.second > window) {
            throw Failure("`" + descriptor.name() + "` ends at " + plainNumber(range.to) +
                          " s, beyond the window of " + plainNumber(duration) + " s (" + str(window) + " frames)");
        }
        return samples;
    };
    for (const Descriptor& descriptor : descriptors) {
        switch (descriptor.kind) {
            case Descriptor::Kind::Loudness:
            case Descriptor::Kind::Attack:
            case Descriptor::Kind::Decay:
                if (window < hop) {
                    throw Failure("`" + descriptor.name() + "` needs one envelope frame (" + str(hop) +
                                  " samples); the window has " + str(window));
                }
                break;
            case Descriptor::Kind::Sustain: {
                std::pair<size_t, size_t> samples = within(descriptor, descriptor.range.value);
                std::pair<size_t, size_t> frames  = framesWithin(samples.first, samples.second, hop);
                if (frames.first >= frames.second) {
                    throw Failure("`" + descriptor.name() + "` holds no whole envelope frame of " + str(hop) +
                                  " samples");
                }
                break;
            }
            case Descriptor::Kind::Centroid: {
                std::pair<size_t, size_t> samples(0, window);
                if (descriptor.range) {
                    samples = within(descriptor, descriptor.range.value);
                }
                if (samples.second - samples.first < settings.fft) {
                    throw Failure("`" + descriptor.name() + "` covers " + str(samples.second - samples.first) +
                                  " samples, fewer than one transform of " + str(settings.fft) +
                                  " (--describe-fft)");
                }
                break;
            }
            case Descriptor::Kind::Width:
                if (outputs != 2) {
                    throw Failure("`" + descriptor.name() + "` compares two outputs; this program has " +
                                  str(outputs));
                }
                if (descriptor.range) {
                    within(descriptor, descriptor.range.value);
                }
                break;
        }
    }
}

// 10 log10, minus infinity for zero.
static double energyDb(double energy)
{
    return 10.0 * log10(energy);
}

// Summed Hann-windowed power spectra of n samples, hop n/2, over bins 2..n/2.
static double centroid(const double* signal, size_t size, double sr, size_t n)
{
    std::vector<double> hann(n), power(n / 2, 0.0), re(n), im(n);
    for (size_t i = 0; i < n; i++) {
        hann[i] = 0.5 - 0.5 * cos(kTau * double(i) / double(n));
    }
    for (size_t start = 0; start + n <= size; start += n / 2) {
        for (size_t i = 0; i < n; i++) {
            re[i] = hann[i] * signal[start + i];
            im[i] = 0.0;
        }
        fft(re, im);
        for (size_t k = 0; k < power.size(); k++) {
            power[k] += re[k] * re[k] + im[k] * im[k];
        }
    }
    double bin = sr / double(n), total = 0.0, weighted = 0.0;
    for (size_t k = 2; k < power.size(); k++) {
        total += power[k];
        weighted += power[k] * double(k) * bin;
    }
    return total > 0.0 ? weighted / total : kNaN;
}

// The mid signal, its envelope and its loudest frame are what most descriptors share.
std::vector<double> describe(const Channels& channels, double sr, const std::vector<Descriptor>& descriptors,
                             const DescribeSettings& settings)
{
    size_t              length = channels.empty() ? 0 : channels[0].size();
    // the mean of the outputs
    std::vector<double> mid(length);
    for (size_t i = 0; i < length; i++) {
        double sum = 0.0;
        for (const std::vector<double>& channel : channels) {
            sum += channel[i];
        }
        mid[i] = sum / double(channels.size());
    }
    size_t              hop = secondsToSamples(settings.hopSeconds, sr);
    // mean of the mid's square over whole frames: a last partial frame is left out
    std::vector<double> envelope;
    for (size_t start = 0; start + hop <= length; start += hop) {
        double sum = 0.0;
        for (size_t i = 0; i < hop; i++) {
            sum += mid[start + i] * mid[start + i];
        }
        envelope.push_back(sum / double(hop));
    }
    // the first largest frame
    size_t peakFrame = 0;
    double peak      = 0.0;
    for (size_t k = 0; k < envelope.size(); k++) {
        if (envelope[k] > peak) {
            peakFrame = k;
            peak      = envelope[k];
        }
    }
    auto seconds = [&](size_t frames) { return double(frames * hop) / sr; };

    std::vector<double> values;
    for (const Descriptor& descriptor : descriptors) {
        double value = kNaN;
        switch (descriptor.kind) {
            case Descriptor::Kind::Loudness:
                value = energyDb(peak);
                break;
            case Descriptor::Kind::Attack:
                if (peak > 0.0) {
                    for (size_t k = 0; k < envelope.size(); k++) {
                        if (envelope[k] >= 0.81 * peak) {
                            value = seconds(k);
                            break;
                        }
                    }
                }
                break;
            case Descriptor::Kind::Decay:
                if (peak > 0.0) {
                    // from the loudest frame down; not reached stays NaN, which is not the window's end
                    double floorLevel = peak * pow(10.0, -descriptor.db / 10.0);
                    for (size_t k = peakFrame; k < envelope.size(); k++) {
                        if (envelope[k] <= floorLevel) {
                            value = seconds(k - peakFrame);
                            break;
                        }
                    }
                }
                break;
            case Descriptor::Kind::Sustain: {
                std::pair<size_t, size_t> samples = descriptor.range.value.samples(sr);
                std::pair<size_t, size_t> frames  = framesWithin(samples.first, samples.second, hop);
                double                    sum     = 0.0;
                for (size_t k = frames.first; k < frames.second; k++) {
                    sum += envelope[k];
                }
                double mean = sum / double(frames.second - frames.first);
                if (peak > 0.0) {
                    value = energyDb(mean) - energyDb(peak);
                }
                break;
            }
            case Descriptor::Kind::Centroid: {
                std::pair<size_t, size_t> samples(0, length);
                if (descriptor.range) {
                    samples = descriptor.range.value.samples(sr);
                }
                value = centroid(mid.data() + samples.first, samples.second - samples.first, sr, settings.fft);
                break;
            }
            case Descriptor::Kind::Width: {
                std::pair<size_t, size_t> samples(0, length);
                if (descriptor.range) {
                    samples = descriptor.range.value.samples(sr);
                }
                double side = 0.0, center = 0.0;
                for (size_t i = samples.first; i < samples.second; i++) {
                    double l = channels[0][i], r = channels[1][i];
                    side += (l - r) * (l - r);
                    center += (l + r) * (l + r);
                }
                value = energyDb(side) - energyDb(center);
                break;
            }
        }
        values.push_back(value);
    }
    return values;
}

// ---------------------------------------------------------------- --freqresp

// N, or N:FMIN:FMAX; a log axis has no 0 Hz.
FreqGrid FreqGrid::parse(const std::string& spec, double sampleRate)
{
    double                   nyquist = sampleRate / 2.0;
    std::vector<std::string> fields  = split(spec, ':');
    FreqGrid                 grid;
    if (!parseSize(fields[0], grid.points) || grid.points == 0) {
        throw Failure("--freqresp `" + spec + "`: `" + fields[0] + "` is not a number of frequencies");
    }
    if (fields.size() == 1) {
        grid.fmin = std::min(20.0, nyquist);
        grid.fmax = nyquist;
    } else if (fields.size() == 3) {
        auto bound = [&spec](const std::string& text) {
            double value;
            if (!parseDouble(text, value)) {
                throw Failure("--freqresp `" + spec + "`: `" + text + "` is not a frequency");
            }
            return value;
        };
        grid.fmin = bound(fields[1]);
        grid.fmax = bound(fields[2]);
    } else {
        throw Failure("--freqresp `" + spec + "`: expected N or N:FMIN:FMAX");
    }
    if (!(grid.fmin > 0.0 && grid.fmin <= grid.fmax && grid.fmax <= nyquist)) {
        throw Failure("--freqresp `" + spec + "`: the range must satisfy 0 < FMIN <= FMAX <= " +
                      plainNumber(nyquist) + " Hz (half the sample rate); a log axis has no 0 Hz");
    }
    return grid;
}

// The two ends are the bounds themselves, and the points between are rounded
// to twelve significant digits, so that the third of 4:250:2000 is 1000: the
// response is evaluated at the frequency that is printed.
std::vector<double> FreqGrid::frequencies() const
{
    std::vector<double> hz;
    size_t              last = points - 1;
    for (size_t i = 0; i < points; i++) {
        if (i == 0) {
            hz.push_back(fmin);
        } else if (i == last) {
            hz.push_back(fmax);
        } else {
            double f     = fmin * pow(fmax / fmin, double(i) / double(last));
            double scale = __builtin_powi(10.0, 11 - static_cast<int>(floor(log10(f))));
            hz.push_back(round(f * scale) / scale);
        }
    }
    return hz;
}

// The transform at omega by Horner's rule on the polynomial in z^-1, from the
// last sample: the small samples of a decaying tail are summed first.
static void transform(const std::vector<double>& response, double omega, double& re, double& im)
{
    double s = sin(omega), c = cos(omega);
    re = 0.0, im = 0.0;
    for (size_t n = response.size(); n-- > 0;) {
        double r = re * c + im * s + response[n];
        double i = im * c - re * s;
        re       = r;
        im       = i;
    }
}

// 20 log10 of a zero is minus infinity, and atan2(0, 0) a phase of 0 rather than NaN.
std::vector<FreqPoint> frequencyResponse(const std::vector<double>& samples, double sampleRate,
                                         const std::vector<double>& hz)
{
    std::vector<FreqPoint> points;
    for (double f : hz) {
        double re, im;
        transform(samples, kTau * f / sampleRate, re, im);
        FreqPoint point;
        point.magnitudeDb = 20.0 * log10(hypot(re, im));
        point.phase       = atan2(im, re);
        points.push_back(point);
    }
    return points;
}

// At least one frame, even of a short window.
Optional<double> tailEnergyFraction(const std::vector<double>& samples)
{
    auto energy = [&samples](size_t from) {
        double sum = 0.0;
        for (size_t i = from; i < samples.size(); i++) {
            sum += samples[i] * samples[i];
        }
        return sum;
    };
    double total = energy(0);
    if (total == 0.0) {
        return Optional<double>();
    }
    size_t tail = std::min(std::max<size_t>(samples.size() / 10, 1), samples.size());
    return energy(samples.size() - tail) / total;
}

// See analysis.h.
double defaultLinearityTolerance(bool isDouble)
{
    return isDouble ? 1e-9 : 1e-4;
}

// 37 is divided by no block size.
size_t shiftFor(size_t frames)
{
    return std::max<size_t>(std::min<size_t>(37, frames / 4), 1);
}

// See analysis.h.
const std::vector<Property>& allProperties()
{
    static const std::vector<Property> all = {Property::Homogeneity, Property::TimeInvariance,
                                              Property::Superposition};
    return all;
}

// The key of the property in the JSON document and in the report.
const char* propertyName(Property property)
{
    switch (property) {
        case Property::Homogeneity:
            return "homogeneity";
        case Property::TimeInvariance:
            return "time_invariance";
        default:
            return "superposition";
    }
}

// Powers of two: in a linear program the first two hold to the bit. The sign catches
// a rectifier; two adjacent frames catch a rank-order filter, which looks at a short window.
std::vector<std::pair<size_t, double>> propertyTaps(Property property, size_t shift)
{
    switch (property) {
        case Property::Homogeneity:
            return {{0, -0.5}};
        case Property::TimeInvariance:
            return {{shift, 1.0}};
        default:
            return {{0, 1.0}, {1, 0.5}};
    }
}

// What the linear combination of the responses must be, sample by sample.
Samples propertyExpected(Property property, const Samples& h, size_t shift)
{
    Samples expected;
    expected.start = h.start;
    for (const std::vector<double>& channel : h.channels) {
        // the response delayed, zero before it starts
        auto delayed = [&channel](size_t by, size_t k) { return k >= by ? channel[k - by] : 0.0; };
        std::vector<double> out(channel.size());
        for (size_t k = 0; k < channel.size(); k++) {
            switch (property) {
                case Property::Homogeneity:
                    out[k] = -0.5 * channel[k];
                    break;
                case Property::TimeInvariance:
                    out[k] = delayed(shift, k);
                    break;
                default:
                    out[k] = channel[k] + 0.5 * delayed(1, k);
            }
        }
        expected.channels.push_back(out);
    }
    return expected;
}

// For the refusal: what is false, at the frames of this render.
std::string propertyViolation(Property property, size_t at, size_t shift)
{
    switch (property) {
        case Property::Homogeneity:
            return "homogeneity: the response to an impulse of -0.5 is not -0.5 times the response to an impulse of 1";
        case Property::TimeInvariance:
            return "time invariance: the response to an impulse at frame " + str(at + shift) +
                   " is not the response to an impulse at frame " + str(at) + ", " + str(shift) + " frames later";
        default:
            return "superposition: the response to impulses of 1 at frame " + str(at) + " and 0.5 at frame " +
                   str(at + 1) + " is not the sum of their responses";
    }
}

// For the refusal: what the program most likely does.
const char* propertyUsualCause(Property property)
{
    switch (property) {
        case Property::Homogeneity:
            return "a saturation, a rectifier, a threshold, or an output that does not come from the input";
        case Property::TimeInvariance:
            return "a modulation (an LFO on a coefficient, a tremolo), an envelope, a noise source";
        default:
            return "a rank-order operation (median, min, max) over neighbouring samples";
    }
}

// ---------------------------------------------------------------- --time

Optional<double> Timing::worstBudgetFraction() const
{
    if (!worst) {
        return Optional<double>();
    }
    return worst.value.seconds / budgetSeconds(worst.value.frames);
}

// A timing without a worst block changes nothing.
void Timing::absorb(const Timing& other)
{
    Optional<double> mine   = worstBudgetFraction();
    Optional<double> theirs = other.worstBudgetFraction();
    if (theirs && (!mine || *theirs > *mine)) {
        worst = other.worst;
    }
    frames += other.frames;
    blocks += other.blocks;
    computeSeconds += other.computeSeconds;
}

// Any first block is the worst so far.
BlockTimer::BlockTimer(double sampleRate) : fWorstFraction(-kInfinity)
{
    fTiming.sampleRate = sampleRate;
}

// Records the compute call of the block of 'frames' frames starting at 'frame'.
void BlockTimer::record(size_t frame, size_t frames, double seconds)
{
    fTiming.frames += frames;
    fTiming.blocks += 1;
    fTiming.computeSeconds += seconds;
    if (frames == 0) {
        return;
    }
    // against its own budget: a block of one frame that takes as long as a
    // block of sixty-four is sixty-four times closer to its deadline
    double fraction = seconds / fTiming.budgetSeconds(frames);
    if (fraction > fWorstFraction) {
        fWorstFraction = fraction;
        WorstBlock worst;
        worst.frame   = frame;
        worst.frames  = frames;
        worst.seconds = seconds;
        fTiming.worst = worst;
    }
}
