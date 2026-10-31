/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This file is part of faustprobe, the offline probe of a Faust program.
 It is distributed under the same license as the Faust tools: see
 COPYING.txt at the root of the repository.
 ************************************************************************/

#include "json.h"

#include <cmath>
#include <cstdio>

// The magnitude of an int is taken in long long, where that of INT_MIN fits.
Json::Json() : fKind(Kind::Null) {}
// One constructor per kind of value.
Json::Json(bool value) : fKind(Kind::Bool), fBool(value) {}
Json::Json(int value)
    : fKind(Kind::Integer),
      fInteger(static_cast<size_t>(value < 0 ? -static_cast<long long>(value) : value)),
      fNegative(value < 0)
{
}
Json::Json(size_t value) : fKind(Kind::Integer), fInteger(value) {}
Json::Json(double value) : fKind(std::isfinite(value) ? Kind::Number : Kind::Null), fNumber(value) {}
Json::Json(const char* value) : fKind(Kind::String), fString(value) {}
Json::Json(const std::string& value) : fKind(Kind::String), fString(value) {}

// Containers start from a null, which gets its kind here.
Json Json::object()
{
    Json json;
    json.fKind = Kind::Object;
    return json;
}

Json Json::array()
{
    Json json;
    json.fKind = Kind::Array;
    return json;
}

// An array of strings, and below of numbers and of sizes.
Json Json::strings(const std::vector<std::string>& values)
{
    Json json = array();
    for (const std::string& value : values) {
        json.push(value);
    }
    return json;
}

Json Json::numbers(const std::vector<double>& values)
{
    Json json = array();
    for (double value : values) {
        json.push(value);
    }
    return json;
}

Json Json::sizes(const std::vector<size_t>& values)
{
    Json json = array();
    for (size_t value : values) {
        json.push(value);
    }
    return json;
}

// Replaces a key already there; std::map keeps the keys sorted.
Json& Json::set(const std::string& key, const Json& value)
{
    fObject[key] = value;
    return *this;
}

// Appends to an array.
Json& Json::push(const Json& value)
{
    fArray.push_back(value);
    return *this;
}

bool Json::empty() const
{
    return fKind == Kind::Object ? fObject.empty() : fArray.empty();
}

// Plain up to sixteen integer digits and down to 1e-5, an exponent elsewhere:
// the text every JSON reader of this tool's output has seen.
static std::string numberText(double value)
{
    std::string sign = std::signbit(value) ? "-" : "";
    if (value == 0.0) {
        return sign + "0.0";
    }
    ShortestDigits d      = shortestDigits(value);
    int            length = static_cast<int>(d.digits.size());
    // length digits, the point after the kk-th of them
    int            kk     = d.exponent + 1;  // 10^(kk-1) <= |value| < 10^kk
    std::string    out;
    // 1234e7 -> 12340000000.0
    if (kk >= length && kk <= 16) {
        out = d.digits + std::string(kk - length, '0') + ".0";
    // 1234e-2 -> 12.34
    } else if (kk > 0 && kk <= 16) {
        out = d.digits.substr(0, kk) + "." + d.digits.substr(kk);
    // 1234e-6 -> 0.001234
    } else if (kk > -5 && kk <= 0) {
        out = "0." + std::string(-kk, '0') + d.digits;
    // 1e30
    } else if (length == 1) {
        out = d.digits + "e" + std::to_string(kk - 1);
    } else {
        out = d.digits.substr(0, 1) + "." + d.digits.substr(1) + "e" + std::to_string(kk - 1);
    }
    return sign + out;
}

// A JSON string: quotes, backslashes and control characters escaped, UTF-8 as it is.
static void writeString(std::string& out, const std::string& text)
{
    out += '"';
    for (unsigned char c : text) {
        switch (c) {
            case '"':
                out += "\\\"";
                break;
            case '\\':
                out += "\\\\";
                break;
            case '\n':
                out += "\\n";
                break;
            case '\r':
                out += "\\r";
                break;
            case '\t':
                out += "\\t";
                break;
            default:
                if (c < 0x20) {
                    char escaped[8];
                    snprintf(escaped, sizeof(escaped), "\\u%04x", c);
                    out += escaped;
                } else {
                    out += static_cast<char>(c);
                }
        }
    }
    out += '"';
}

// inner indents the elements of a container, close its closing bracket.
void Json::write(std::string& out, int indent) const
{
    std::string inner(2 * (indent + 1), ' ');
    std::string close(2 * indent, ' ');
    switch (fKind) {
        case Kind::Null:
            out += "null";
            break;
        case Kind::Bool:
            out += fBool ? "true" : "false";
            break;
        case Kind::Integer:
            out += (fNegative ? "-" : "") + std::to_string(fInteger);
            break;
        case Kind::Number:
            out += numberText(fNumber);
            break;
        case Kind::String:
            writeString(out, fString);
            break;
        case Kind::Array: {
            if (fArray.empty()) {
                out += "[]";
                break;
            }
            out += "[\n";
            for (size_t i = 0; i < fArray.size(); i++) {
                out += inner;
                fArray[i].write(out, indent + 1);
                out += i + 1 < fArray.size() ? ",\n" : "\n";
            }
            out += close + "]";
            break;
        }
        case Kind::Object: {
            if (fObject.empty()) {
                out += "{}";
                break;
            }
            out += "{\n";
            size_t left = fObject.size();
            for (const auto& entry : fObject) {
                out += inner;
                writeString(out, entry.first);
                out += ": ";
                entry.second.write(out, indent + 1);
                out += --left > 0 ? ",\n" : "\n";
            }
            out += close + "}";
            break;
        }
    }
}

std::string Json::pretty() const
{
    std::string out;
    write(out, 0);
    return out;
}
