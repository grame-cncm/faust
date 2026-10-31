/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This file is part of faustprobe, the offline probe of a Faust program.
 It is distributed under the same license as the Faust tools: see
 COPYING.txt at the root of the repository.
 ************************************************************************/

// How the probe writes things. The probe is read by scripts that compare its
// output with a reference, so the text of a number is part of the measurement.

#ifndef __faustprobe_text__
#define __faustprobe_text__

#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

// An error that ends the command: printed as 'faustprobe: MESSAGE', exit 1.
// Thrown by any layer; main() catches it, so a mode never has to carry an error by hand.
struct Failure : public std::runtime_error {
    // The message printed after "faustprobe: ".
    explicit Failure(const std::string& message) : std::runtime_error(message) {}
};

// A number the probe writes, or the absence of it.
// A value that may be absent. Tested as a bool, read with * or .value.
template <typename T>
struct Optional {
    bool has = false;  // whether a value is held
    T    value{};  // the value, default-constructed when absent
    Optional() {}
    Optional(const T& v) : has(true), value(v) {}
    // Whether a value is held.
    explicit operator bool() const { return has; }
    const T& operator*() const { return value; }
};

// A size as decimal text.
std::string              str(size_t value);
// The parts with the separator between them.
std::string              join(const std::vector<std::string>& parts, const std::string& separator);
// Every field between separators, empty ones included: split("a,,b", ',') has three.
std::vector<std::string> split(const std::string& text, char separator);
// Without the white space at both ends.
std::string              trim(const std::string& text);
// Whether the text begins, or ends, with the fragment.
bool                     startsWith(const std::string& text, const std::string& prefix);
bool                     endsWith(const std::string& text, const std::string& suffix);
// Every occurrence of a fragment replaced; a replacement is not scanned again.
std::string              replaceAll(std::string text, const std::string& from, const std::string& to);
// In lower case, ASCII only: for file extensions.
std::string              lower(std::string text);
// The whole file, or a Failure naming it.
std::string              readTextFile(const std::string& path);
// Parts of a path: the extension in lower case and without its dot ("" for a dot
// file), the directory ("." when there is none), the name without its extension.
std::string              extensionOf(const std::string& path);
std::string              directoryOf(const std::string& path);
std::string              stemOf(const std::string& path);

// A whole string as a number: false when anything is left over. These accept
// what a command line means by a number, 'inf' and 'nan' included.
bool parseDouble(const std::string& text, double& value);
bool parseSize(const std::string& text, size_t& value);
bool parseInt(const std::string& text, int& value);

// The shortest decimal digits that parse back to the same value, and the
// exponent of the first digit.
struct ShortestDigits {
    std::string digits;  // no sign, no point, no trailing zero
    int         exponent;  // value = d.ddd x 10^exponent
};
ShortestDigits shortestDigits(double value);
ShortestDigits shortestDigits(float value);

// A value as text, for a person: the shortest digits, never an exponent, no
// '.0' on an integer ('0.5', '440', '0.0000001').
std::string plainNumber(double value);
std::string plainNumber(float value);
// The shortest digits at the width of the value, plain between 1e-4 and 1e16,
// with an exponent elsewhere ('1.0', '0.5', '3.3333333333333334e-8', 'NaN', 'inf').
std::string roundTrip(double value);
// A float is formatted from the float: its double needs seventeen digits to say
// what nine say (0.0010000000474974513 for 0.001).
std::string roundTrip(float value);
// The shortest digits and an exponent ('1e-9', '3.46e-28').
std::string scientific(double value);
// 'decimals' digits after the point and an exponent ('2.39e-4').
std::string scientific(double value, int decimals);
// 'decimals' digits after the point ('0.500000000').
std::string fixed(double value, int decimals);

// The text form of the numbers of a run.
struct Precision {
    bool roundTrip = true;  // the shortest text that parses back to the same float
    int  decimals  = 0;     // else this many fixed decimals
    // Parses --precision: `full` or a number of decimals.
    static Precision parse(const std::string& text);
};

// A Precision bound to the width of the program's samples.
struct NumberFormat {
    Precision precision;
    bool      isDouble = false;

    // A value that lives at the program's width: a sample, a peak, a bargraph, a bound.
    std::string sample(double value) const;
    // A value computed in double whatever the program's width: a mean, an RMS.
    std::string computed(double value) const;
    // A training loss: always scientific, since it spans many decades.
    std::string loss(double value) const;
};

// Three significant digits of a ratio: '27.6', '1523', '0.84'.
std::string threeDigits(double value);
// A duration for a person: three significant digits and the unit that fits.
std::string humanSeconds(double seconds);
// A CSV field, quoted when it holds a comma or a quote.
std::string csvField(const std::string& text);
std::string csvFieldWithBreaks(const std::string& text);
// A non-finite sample the way it prints.
const char* nonFiniteName(double value);

#endif
