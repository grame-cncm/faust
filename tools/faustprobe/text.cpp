/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This file is part of faustprobe, the offline probe of a Faust program.
 It is distributed under the same license as the Faust tools: see
 COPYING.txt at the root of the repository.
 ************************************************************************/

#include "text.h"

#include <algorithm>
#include <cerrno>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>

// See text.h for what each of these helpers promises.
std::string str(size_t value)
{
    return std::to_string(value);
}

// See text.h.
std::string join(const std::vector<std::string>& parts, const std::string& separator)
{
    std::string out;
    for (size_t i = 0; i < parts.size(); i++) {
        if (i > 0) {
            out += separator;
        }
        out += parts[i];
    }
    return out;
}

// See text.h.
std::vector<std::string> split(const std::string& text, char separator)
{
    std::vector<std::string> parts;
    size_t                   start = 0;
    while (true) {
        size_t at = text.find(separator, start);
        if (at == std::string::npos) {
            parts.push_back(text.substr(start));
            return parts;
        }
        parts.push_back(text.substr(start, at - start));
        start = at + 1;
    }
}

// isspace wants an unsigned char: a byte of UTF-8 is negative as a char.
std::string trim(const std::string& text)
{
    size_t from = 0, to = text.size();
    while (from < to && isspace(static_cast<unsigned char>(text[from]))) {
        from++;
    }
    while (to > from && isspace(static_cast<unsigned char>(text[to - 1]))) {
        to--;
    }
    return text.substr(from, to - from);
}

// compare stops at the end of the text.
bool startsWith(const std::string& text, const std::string& prefix)
{
    return text.compare(0, prefix.size(), prefix) == 0;
}

// See text.h.
bool endsWith(const std::string& text, const std::string& suffix)
{
    return text.size() >= suffix.size() &&
           text.compare(text.size() - suffix.size(), suffix.size(), suffix) == 0;
}

// The search goes on after the replacement.
std::string replaceAll(std::string text, const std::string& from, const std::string& to)
{
    size_t at = 0;
    while ((at = text.find(from, at)) != std::string::npos) {
        text.replace(at, from.size(), to);
        at += to.size();
    }
    return text;
}

// See text.h.
std::string lower(std::string text)
{
    std::transform(text.begin(), text.end(), text.begin(),
                   [](unsigned char c) { return static_cast<char>(tolower(c)); });
    return text;
}

// Binary: the text is compiled as it is on disk.
std::string readTextFile(const std::string& path)
{
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        throw Failure("cannot read '" + path + "'");
    }
    std::stringstream text;
    text << file.rdbuf();
    return text.str();
}

// A dot leading the file name is no extension.
std::string extensionOf(const std::string& path)
{
    size_t slash = path.find_last_of('/');
    size_t dot   = path.find_last_of('.');
    if (dot == std::string::npos || dot == 0 || (slash != std::string::npos && dot < slash + 2)) {
        return "";
    }
    return lower(path.substr(dot + 1));
}

// See text.h.
std::string directoryOf(const std::string& path)
{
    size_t slash = path.find_last_of('/');
    return slash == std::string::npos ? "." : (slash == 0 ? "/" : path.substr(0, slash));
}

// See text.h.
std::string stemOf(const std::string& path)
{
    size_t      slash = path.find_last_of('/');
    std::string name  = slash == std::string::npos ? path : path.substr(slash + 1);
    size_t      dot   = name.find_last_of('.');
    return dot == std::string::npos || dot == 0 ? name : name.substr(0, dot);
}

// See text.h.
bool parseDouble(const std::string& text, double& value)
{
    // strtod skips leading space, which no number of a command line has.
    if (text.empty() || isspace(static_cast<unsigned char>(text[0]))) {
        return false;
    }
    // hexadecimal is strtod's, and no command line of this tool means it
    if (text.find('x') != std::string::npos || text.find('X') != std::string::npos) {
        return false;
    }
    char* end = nullptr;
    // strtod stops at the first character it cannot read: the whole text must be consumed.
    value     = strtod(text.c_str(), &end);
    return end == text.c_str() + text.size();
}

// Unsigned, in 64 bits.
bool parseSize(const std::string& text, size_t& value)
{
    // Digits only: strtoull would read "-1" as a huge number.
    if (text.empty() || !std::all_of(text.begin(), text.end(), [](unsigned char c) { return isdigit(c); })) {
        return false;
    }
    errno     = 0;
    char* end = nullptr;
    // errno says whether it fitted in 64 bits.
    value     = strtoull(text.c_str(), &end, 10);
    return errno == 0 && end == text.c_str() + text.size();
}

// Signed, in an int.
bool parseInt(const std::string& text, int& value)
{
    if (text.empty()) {
        return false;
    }
    errno     = 0;
    char* end = nullptr;
    // Accepts a sign; the cast below tells whether it fits in an int.
    long  v   = strtol(text.c_str(), &end, 10);
    if (errno != 0 || end != text.c_str() + text.size() || v != static_cast<int>(v) ||
        isspace(static_cast<unsigned char>(text[0]))) {
        return false;
    }
    value = static_cast<int>(v);
    return true;
}

// The digits out of '%.*e': 'd.ddde[+-]xx'.
static ShortestDigits digitsOf(const char* text)
{
    ShortestDigits result;
    const char*    e = text;
    for (const char* p = text; *p != '\0' && *p != 'e'; p++, e = p) {
        if (*p != '.' && *p != '-') {
            result.digits += *p;
        }
    }
    result.exponent = atoi(e + 1);
    while (result.digits.size() > 1 && result.digits.back() == '0') {
        result.digits.pop_back();
    }
    return result;
}

// The precision grows until the text parses back to the very value: correctly
// rounded digits, the fewest that identify it.
template <typename REAL, typename PARSE>
static ShortestDigits shortest(REAL value, int maxDigits, PARSE parse)
{
    char text[64];
    for (int precision = 0; precision < maxDigits; precision++) {
        snprintf(text, sizeof(text), "%.*e", precision, static_cast<double>(value));
        if (parse(text) == value) {
            break;
        }
    }
    return digitsOf(text);
}

// Seventeen significant digits identify any double, nine any float: the loops stop
// there. The sign is not part of the digits.
ShortestDigits shortestDigits(double value)
{
    return shortest(fabs(value), 17, [](const char* t) { return strtod(t, nullptr); });
}

// Parsed back with strtof: a float must round to itself as a float.
ShortestDigits shortestDigits(float value)
{
    return shortest(fabsf(value), 9, [](const char* t) { return strtof(t, nullptr); });
}

// The digits as a plain decimal.
// pointZero adds the ".0" of an integer, which roundTrip() has and plainNumber() has not.
static std::string plainDigits(const ShortestDigits& d, bool pointZero)
{
    std::string out;
    int         exponent = d.exponent;
    int         count    = static_cast<int>(d.digits.size());
    // below 1: 0.00ddd
    if (exponent < 0) {
        out = "0." + std::string(-exponent - 1, '0') + d.digits;
    // an integer, padded with the zeros the digits do not hold
    } else if (exponent + 1 >= count) {
        out = d.digits + std::string(exponent + 1 - count, '0');
        if (pointZero) {
            out += ".0";
        }
    } else {
        out = d.digits.substr(0, exponent + 1) + "." + d.digits.substr(exponent + 1);
    }
    return out;
}

// d.ddde-N, as the exponent form of a number reads in Python and in Rust.
static std::string exponentDigits(const ShortestDigits& d)
{
    std::string out = d.digits.substr(0, 1);
    if (d.digits.size() > 1) {
        out += "." + d.digits.substr(1);
    }
    return out + "e" + std::to_string(d.exponent);
}

// The text of a non-finite value, which Python's float() reads back.
static const char* nonFiniteText(double value)
{
    return std::isnan(value) ? "NaN" : (value > 0 ? "inf" : "-inf");
}

// plainNumber(), at the width of the value.
template <typename REAL>
static std::string plainText(REAL value)
{
    if (!std::isfinite(value)) {
        return nonFiniteText(value);
    }
    std::string sign = std::signbit(value) ? "-" : "";
    return value == 0 ? sign + "0" : sign + plainDigits(shortestDigits(value), false);
}

// Both widths share plainText.
std::string plainNumber(double value)
{
    return plainText(value);
}

std::string plainNumber(float value)
{
    return plainText(value);
}

// roundTrip(), at the width of the value. Scripts compare this text, so its limits
// are a contract: plain from 1e-4 up to 1e16, an exponent elsewhere, as faust-rs prints.
template <typename REAL>
static std::string roundTripText(REAL value)
{
    if (!std::isfinite(value)) {
        return nonFiniteText(value);
    }
    std::string sign = std::signbit(value) ? "-" : "";
    REAL        abs  = std::fabs(value);
    if (abs == 0) {
        return sign + "0.0";
    }
    ShortestDigits digits = shortestDigits(abs);
    if (abs >= REAL(1e16) || abs < REAL(1e-4)) {
        return sign + exponentDigits(digits);
    }
    return sign + plainDigits(digits, true);
}

// Both widths share roundTripText.
std::string roundTrip(double value)
{
    return roundTripText(value);
}

std::string roundTrip(float value)
{
    return roundTripText(value);
}

// The shortest digits with an exponent; a zero keeps its sign.
std::string scientific(double value)
{
    if (!std::isfinite(value)) {
        return nonFiniteText(value);
    }
    std::string sign = std::signbit(value) ? "-" : "";
    return value == 0.0 ? sign + "0e0" : sign + exponentDigits(shortestDigits(value));
}

// printf writes e-04 and e+00: the exponent is rewritten as a plain integer.
std::string scientific(double value, int decimals)
{
    if (!std::isfinite(value)) {
        return nonFiniteText(value);
    }
    char text[64];
    snprintf(text, sizeof(text), "%.*e", decimals, value);
    // the exponent without its sign or padding: 'e-4', 'e0'
    std::string out(text);
    size_t      e        = out.find('e');
    int         exponent = atoi(out.c_str() + e + 1);
    return out.substr(0, e) + "e" + std::to_string(exponent);
}

// The buffer holds the 309 digits of the largest double and any decimals asked for.
std::string fixed(double value, int decimals)
{
    if (!std::isfinite(value)) {
        return nonFiniteText(value);
    }
    char text[512];
    snprintf(text, sizeof(text), "%.*f", decimals, value);
    return text;
}

// `full`, or a number of fixed decimals.
Precision Precision::parse(const std::string& text)
{
    Precision precision;
    if (text == "full") {
        return precision;
    }
    size_t decimals;
    if (!parseSize(text, decimals)) {
        throw Failure("`--precision " + text + "`: expected `full` or a number of decimals");
    }
    precision.roundTrip = false;
    precision.decimals  = static_cast<int>(decimals);
    return precision;
}

// A single-precision sample goes back to its float, which is exact, before printing.
std::string NumberFormat::sample(double value) const
{
    if (!precision.roundTrip) {
        return fixed(value, precision.decimals);
    }
    return isDouble ? roundTrip(value) : roundTrip(static_cast<float>(value));
}

std::string NumberFormat::computed(double value) const
{
    return precision.roundTrip ? roundTrip(value) : fixed(value, precision.decimals);
}

std::string NumberFormat::loss(double value) const
{
    return precision.roundTrip ? scientific(value) : scientific(value, precision.decimals);
}

// The number of decimals falls as the magnitude grows.
std::string threeDigits(double value)
{
    double magnitude = fabs(value);
    if (!std::isfinite(value)) {
        return nonFiniteText(value);
    } else if (magnitude >= 100.0) {
        return fixed(value, 0);
    } else if (magnitude >= 10.0) {
        return fixed(value, 1);
    } else {
        return fixed(value, 2);
    }
}

// The unit that leaves a number between 1 and 1000, then threeDigits()'s rule.
std::string humanSeconds(double seconds)
{
    if (!std::isfinite(seconds)) {
        return std::string(nonFiniteText(seconds)) + " s";
    }
    double      scaled;
    const char* unit;
    if (seconds >= 1.0) {
        scaled = seconds, unit = "s";
    } else if (seconds >= 1e-3) {
        scaled = seconds * 1e3, unit = "ms";
    } else if (seconds >= 1e-6) {
        scaled = seconds * 1e6, unit = "us";
    } else {
        scaled = seconds * 1e9, unit = "ns";
    }
    int decimals = scaled >= 100.0 ? 0 : (scaled >= 10.0 ? 1 : 2);
    return fixed(scaled, decimals) + " " + unit;
}

// RFC 4180: in double quotes, its quotes doubled.
static std::string quoted(const std::string& text)
{
    return "\"" + replaceAll(text, "\"", "\"\"") + "\"";
}

// Headers: an expression with arguments holds a comma.
std::string csvField(const std::string& text)
{
    return text.find_first_of(",\"") != std::string::npos ? quoted(text) : text;
}

// The same, for a text that may also hold a line break: a diagram's name.
std::string csvFieldWithBreaks(const std::string& text)
{
    return text.find_first_of(",\"\n\r") != std::string::npos ? quoted(text) : text;
}

// With the sign of an infinity: this one is for messages about a sample.
const char* nonFiniteName(double value)
{
    return std::isnan(value) ? "NaN" : (value > 0 ? "+inf" : "-inf");
}
