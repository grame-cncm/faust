/************************************************************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This file is part of faustprobe, the offline probe of a Faust program.
 It is distributed under the same license as the Faust tools: see
 COPYING.txt at the root of the repository.
 ************************************************************************/

// What needs no DSP: the text of numbers, JSON, audio files, analysis.

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <limits>

#include "../analysis.h"
#include "../audio.h"
#include "../json.h"
#include "../text.h"

static int gFailures = 0;

// Compares two texts, and two numbers within a tolerance.
static void same(const std::string& got, const std::string& expected, const char* what)
{
    if (got != expected) {
        printf("FAIL %s: got `%s`, expected `%s`\n", what, got.c_str(), expected.c_str());
        gFailures++;
    }
}

// tolerance 0 is equality.
static void near(double got, double expected, double tolerance, const char* what)
{
    if (!(fabs(got - expected) <= tolerance)) {
        printf("FAIL %s: got %.17g, expected %.17g\n", what, got, expected);
        gFailures++;
    }
}

// The text of numbers: every form a script reads.
static void numbers()
{
    const double nan = std::numeric_limits<double>::quiet_NaN();
    const double inf = std::numeric_limits<double>::infinity();
    same(roundTrip(1.0), "1.0", "integer");
    same(roundTrip(0.0), "0.0", "zero");
    same(roundTrip(-0.0), "-0.0", "negative zero");
    same(roundTrip(0.1), "0.1", "decimal");
    same(roundTrip(0.0001), "0.0001", "smallest plain");
    same(roundTrip(0.00001), "1e-5", "first exponent");
    same(roundTrip(1.0e-7 / 3.0), "3.3333333333333334e-8", "small keeps its digits");
    same(roundTrip(1e16), "1e16", "large");
    same(roundTrip(123456789.0), "123456789.0", "large plain");
    same(roundTrip(nan), "NaN", "nan");
    same(roundTrip(-inf), "-inf", "inf");
    same(roundTrip(0.001f), "0.001", "a float is printed as a float");
    same(roundTrip(static_cast<double>(0.001f)), "0.0010000000474974513", "and its double as a double");
    same(plainNumber(1e-7), "0.0000001", "plain small");
    same(plainNumber(440.0), "440", "plain integer");
    same(plainNumber(0.7f), "0.7", "plain float");
    same(scientific(2.5e-4), "2.5e-4", "scientific");
    same(scientific(1.0), "1e0", "scientific one");
    same(scientific(2.388789544e-4, 2), "2.39e-4", "scientific decimals");
    same(scientific(0.5, 6), "5.000000e-1", "scientific six decimals");
    same(fixed(0.5, 9), "0.500000000", "fixed");
    same(threeDigits(27.63), "27.6", "three digits");
    same(threeDigits(1523.4), "1523", "three digits, large");
    same(humanSeconds(0.0123), "12.3 ms", "ms");
    same(humanSeconds(41.2e-6), "41.2 us", "us");
    same(csvField("a,b"), "\"a,b\"", "csv");
    // every text parses back to its value
    for (double value : {1.0 / 3.0, M_PI, -2.5e-300, 6.02e23, 5e-324, 1.7976931348623157e308}) {
        if (strtod(roundTrip(value).c_str(), nullptr) != value) {
            printf("FAIL round trip of %.17g\n", value);
            gFailures++;
        }
    }
}

// Keys sorted, numbers as a JSON reader expects, a NaN as null.
static void json()
{
    Json object = Json::object().set("b", 0.5).set("a", 1).set("c", Json::array().push(1e-6).push(NAN)).set("d", "x\"");
    same(object.pretty(), "{\n  \"a\": 1,\n  \"b\": 0.5,\n  \"c\": [\n    1e-6,\n    null\n  ],\n  \"d\": \"x\\\"\"\n}",
         "json");
    same(Json(1.0).pretty(), "1.0", "json float");
    same(Json(0.00001).pretty(), "0.00001", "json small plain");
    same(Json(1e16).pretty(), "1e16", "json large");
}

// What SampleWriter writes, read back by readChannels, independent code: bit for bit.
static void audio()
{
    for (const char* name : {"out/t.npy", "out/t.wav"}) {
        for (bool wide : {true, false}) {
            std::vector<double> frame = {1.0 / 3.0, -0.25};
            {
                SampleWriter writer(name, 2, 3, wide, 48000);
                for (int i = 0; i < 3; i++) {
                    writer.push(frame);
                }
                writer.finish();
            }
            AudioFile file     = readChannels(name);
            double    expected = wide ? 1.0 / 3.0 : static_cast<double>(static_cast<float>(1.0 / 3.0));
            near(file.channels[0][2], expected, 0.0, name);
            near(file.channels[1][0], -0.25, 0.0, name);
        }
    }
}

// Each measure against a value known from its definition.
static void analysis()
{
    const double sr = 48000.0;
    std::vector<double> sine(4096), both(8192);
    for (size_t i = 0; i < sine.size(); i++) {
        sine[i] = sin(2.0 * M_PI * 468.75 * double(i) / sr);
    }
    near(dominantFrequency(sine, sr), 468.75, 12.0, "dominant frequency");
    for (size_t i = 0; i < both.size(); i++) {
        double t = double(i) / sr;
        both[i]  = sin(2.0 * M_PI * 1000.0 * t) + 0.001 * sin(2.0 * M_PI * 1531.0 * t);
    }
    near(sfdrDb(both, sr, 1000.0), 60.0, 2.0, "sfdr of a planted spur");

    std::vector<double> decay(1200);
    for (size_t n = 0; n < decay.size(); n++) {
        decay[n] = pow(0.5, double(n));
    }
    // H = 1 / (1 - a exp(-jw)), which is 1 / 1.5 at half the sample rate
    FreqPoint point = frequencyResponse(decay, 44100.0, {22050.0})[0];
    near(point.magnitudeDb, 20.0 * log10(1.0 / 1.5), 1e-12, "transform of a geometric response");

    std::vector<double> hz = FreqGrid::parse("4:100:800", 44100.0).frequencies();
    near(hz[1], 200.0, 0.0, "log grid");

    Samples a, b;
    a.channels = {{1.0, 1.0, 1.001, 1.0, 1.5}};
    b.channels = {{1.0, 1.0, 1.0, 1.0, 1.0}};
    a.start = b.start = 10;
    Comparison comparison = compare(a, b, Tolerance(), nullptr);
    same(str(comparison.firstBeyond().value.second.frame), "12", "first differing frame");
    same(str(*comparison.channels[0].second.maxAbsAt), "14", "largest difference");
}

// Each group counts its failures; the exit status is the verdict.
int main()
{
    numbers();
    json();
    audio();
    analysis();
    printf(gFailures == 0 ? "unit: all passed\n" : "unit: %d failure(s)\n", gFailures);
    return gFailures == 0 ? 0 : 1;
}
