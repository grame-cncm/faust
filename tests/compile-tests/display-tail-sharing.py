#!/usr/bin/env python3
"""Regression test: a bargraph's block-rate tail computes a shared node once.

The ocpp backend evaluates a harvested bargraph once per block, from
values captured at the end of the sample loop and the stateless operators
above them (the display tail). The tail was emitted as one inlined
expression, so a node used twice was written out twice, and a chain of
D shared levels became 2^D copies: 65535 calls of sin for

    process = _ <: _, (seq(k, 16, _ <: sin + cos) : hbargraph("level", -2, 2)) : attach;

and, in the libraries, an octave analyzer whose band levels feed
bargraphs (an.mth_octave_spectral_level6e) made the compiler grow past
100 GB. A node with several uses is now stored in a temporary.

For each backend and precision, the generated code must call sin exactly
D times, and the bargraph must hold the chain computed directly on the
last input sample.
"""

import argparse
from pathlib import Path
import re
import subprocess
import sys
import tempfile

DEPTH = 16
DSP = f"""
process = _ <: _, (seq(k, {DEPTH}, _ <: sin + cos) : hbargraph("level", -2, 2)) : attach;
"""

RUNNER = """
#include <cmath>
#include <cstdio>
#include <faust/dsp/dsp.h>
#include <faust/gui/meta.h>
#include <faust/gui/DecoratorUI.h>
#include "generated.cpp"

struct Bargraph : public GenericUI {
    FAUSTFLOAT* fZone = nullptr;
    void addHorizontalBargraph(const char*, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT) override { fZone = zone; }
};

int main() {
    const int N = 64;
    FAUSTFLOAT in[N], out[N];
    for (int i = 0; i < N; i++) in[i] = FAUSTFLOAT(0.01 * i - 0.2);
    FAUSTFLOAT* inputs[1]  = {in};
    FAUSTFLOAT* outputs[1] = {out};
    mydsp dsp;
    dsp.init(44100);
    Bargraph ui;
    dsp.buildUserInterface(&ui);
    dsp.compute(N, inputs, outputs);
    FAUSTFLOAT v = in[N - 1];
    for (int k = 0; k < DEPTH; k++) v = std::sin(v) + std::cos(v);
    bool ok = ui.fZone && std::fabs(double(*ui.fZone) - double(v)) <= 1e-6 * std::fabs(double(v));
    if (!ok) std::printf("    bargraph %.9g, expected %.9g\\n", ui.fZone ? double(*ui.fZone) : 0.0, double(v));
    return ok ? 0 : 1;
}
"""

SIN = re.compile(r"\bsin[fl]?\s*\(")


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    parser.add_argument("--cxx", default="c++")
    parser.add_argument("--langs", nargs="+", default=["ocpp", "cpp"])
    args = parser.parse_args()

    failures = 0
    for lang in args.langs:
        for precision in ["single", "double"]:
            with tempfile.TemporaryDirectory(prefix="faust-display-tail-") as temp:
                work = Path(temp)
                (work / "tail.dsp").write_text(DSP)
                try:
                    # the defect makes the compiler grow without bound
                    r = subprocess.run([str(args.faust), "-lang", lang, "-" + precision,
                                        str(work / "tail.dsp"), "-o", str(work / "generated.cpp")],
                                       capture_output=True, text=True, timeout=60)
                except subprocess.TimeoutExpired:
                    print(f"FAIL [{lang} {precision}]: faust did not finish in 60 s")
                    failures += 1
                    continue
                if r.returncode != 0:
                    print(f"FAIL [{lang} {precision}]: faust failed: {r.stderr.strip()}")
                    failures += 1
                    continue
                calls = len(SIN.findall((work / "generated.cpp").read_text()))
                if calls != DEPTH:
                    print(f"FAIL [{lang} {precision}]: {calls} calls of sin, expected {DEPTH}")
                    failures += 1
                    continue
                (work / "runner.cpp").write_text(RUNNER)
                define = ["-DFAUSTFLOAT=double"] if precision == "double" else []
                r = subprocess.run([args.cxx, "-std=c++17", "-O1", "-ffp-contract=off", *define,
                                    f"-DDEPTH={DEPTH}", "-I", str(repo / "architecture"),
                                    "runner.cpp", "-o", "runner"],
                                   cwd=work, capture_output=True, text=True)
                if r.returncode != 0:
                    print(f"FAIL [{lang} {precision}]: C++ compilation failed:\n{r.stderr.strip()}")
                    failures += 1
                    continue
                r = subprocess.run([str(work / "runner")], cwd=work, capture_output=True, text=True)
                if r.returncode != 0:
                    print(f"FAIL [{lang} {precision}]: wrong bargraph value\n{r.stdout.rstrip()}")
                    failures += 1
                    continue
                print(f"ok   [{lang} {precision}]")
    if failures:
        sys.exit(1)


if __name__ == "__main__":
    main()
