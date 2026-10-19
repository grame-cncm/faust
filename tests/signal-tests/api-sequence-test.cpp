/************************************************************************
 FAUST compiler
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 ************************************************************************/

// Successive compilations in one libfaust context must give what each compilation gives
// alone in a fresh process : the same refusal, or the same generated code.
//
//   api-sequence-test seq     every step in one context
//   api-sequence-test one i   step i alone
//
// The Makefile target check-api-sequence runs both and compares them. The programs import
// stdfaust.lib : FAUST_LIB_PATH must name the libraries.

#include <iostream>
#include <string>
#include <vector>

#include "faust/dsp/libfaust-box.h"
#include "faust/dsp/libfaust-signal.h"

using namespace std;

// a filter certified for less than 10 seconds : always refused
static const char* kShortCertificate =
    "import(\"stdfaust.lib\"); process = 1-1' : fi.nlf2(440, 1.000001) : _,!;";
// a slider and a button, read according to -rui / -norui and the precision
static const char* kControls = "process = int(hslider(\"v\",0.5,0,1,0.01)*7), button(\"b\")*3;";

struct Step {
    bool                kBox;      // through DSPToBoxes and the Box API, or through signals built here
    const char*         fProgram;  // for the Box API
    vector<const char*> fOptions;
};

// The signals built here come first : the metadata of a program read by DSPToBoxes (its
// filename) stay in the context and reach the code of signals built afterwards, which have
// no metadata of their own (a known limit of the API, outside this test).
static const vector<Step> kSteps = {
    {false, nullptr, {"-norui"}},
    {false, nullptr, {}},
    {false, nullptr, {"-double"}},
    {false, nullptr, {}},
    {true, kShortCertificate, {}},
    {true, kShortCertificate, {}},
    {true, kControls, {"-norui"}},
    {true, kControls, {}},
    {true, kControls, {"-double"}},
    {true, kControls, {}},
};

// the signals of kControls, built with the Signal API
static tvec controlSignals()
{
    Signal sl = sigHSlider("v", sigReal(0.5), sigReal(0), sigReal(1), sigReal(0.01));
    Signal a  = sigIntCast(sigMul(sl, sigReal(7)));
    Signal b  = sigMul(sigButton("b"), sigReal(3));
    return {a, b};
}

// the refusal or the generated code of one step
static string run(const Step& s, const tvec& signals)
{
    string              err;
    string              code;
    vector<const char*> opts = s.fOptions;
    int                 argc = int(opts.size());
    if (s.kBox) {
        int ins, outs;
        Box box = DSPToBoxes("seq", s.fProgram, argc, opts.data(), &ins, &outs, err);
        if (box) {
            code = createSourceFromBoxes("seq", box, "cpp", argc, opts.data(), err);
        }
    } else {
        code = createSourceFromSignals("seq", signals, "cpp", argc, opts.data(), err);
    }
    if (!err.empty()) {
        return "REFUSED " + err.substr(0, err.find('\n')) + "\n";
    }
    return code;
}

int main(int argc, char** argv)
{
    string mode = (argc > 1) ? argv[1] : "";
    if (mode == "seq") {
        createLibContext();
        tvec signals = controlSignals();
        for (size_t i = 0; i < kSteps.size(); i++) {
            cout << "== step " << i + 1 << "\n" << run(kSteps[i], signals);
        }
        destroyLibContext();
        return 0;
    }
    if (mode == "one" && argc > 2) {
        size_t i = size_t(atoi(argv[2]));
        if (i < 1 || i > kSteps.size()) {
            return 1;
        }
        createLibContext();
        tvec signals = controlSignals();
        cout << "== step " << i << "\n" << run(kSteps[i - 1], signals);
        destroyLibContext();
        return 0;
    }
    if (mode == "count") {
        cout << kSteps.size() << endl;
        return 0;
    }
    cerr << "usage : api-sequence-test seq | one <i> | count" << endl;
    return 1;
}
