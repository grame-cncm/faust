#!/usr/bin/env python3
"""Regression test: no constant folding from the interval of an audio input.

The typing gives an audio input the interval [-1, 1]. It is a convention,
not a guarantee: a host can send any value (a control voltage, a frequency
in Hz, a phase). The interval constant propagation replaced a signal whose
interval is a single value by that value, so with an input x outside
[-1, 1] the generated code was wrong:

    process = _ * 0.4 : rint;          // output0[i0] = 0.0f;
    process = _ <: select2(_ > 2, 0, 1);  // always 0

and rint(x / (2*pi)), the range reduction of a sine, became 0. A signal
that depends on an audio input must keep its computation.

The program below is compiled for each backend, in float and double, run
on inputs outside [-1, 1], and compared with the C library.
"""

import argparse
from pathlib import Path
import subprocess
import sys
import tempfile

DSP = """
t = ((+(1) ~ _) % 2) == 0;
hold(x) = select2(t, _, x) ~ _;  // a sample and hold: a recursion, |y| <= 1 too
process = _ <: rint(0.4*_),                                    // 0 for |x| < 1.25
               select2(_ > 2, 0, 1),                           // 0 for x <= 1
               min(1, pow(abs(0.1*(_ + 0.4)) + 0.75, -4)),     // pm.bowTable: 1 for |x| <= 1
               _/6.283185307179586 - rint(_/6.283185307179586), // a sine's reduction: x/(2pi)
               (hold : *(0.4) : rint);                         // 0 through the recursion
"""

RUNNER = """
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <faust/dsp/dsp.h>
#include <faust/gui/meta.h>
#include <faust/gui/UI.h>
#include "generated.cpp"

int main() {
    const int N = 4;
    FAUSTFLOAT in[N] = {10, -4, 0.5, 3};
    FAUSTFLOAT out[5][N];
    FAUSTFLOAT* inputs[1] = {in};
    FAUSTFLOAT* outputs[5] = {out[0], out[1], out[2], out[3], out[4]};
    mydsp dsp;
    dsp.init(48000);
    dsp.compute(N, inputs, outputs);
    int failures = 0;
    double y = 0;  // the hold: the counter is k + 1, x is taken when it is even
    for (int k = 0; k < N; k++) {
        double x = in[k];
        y = ((k + 1) % 2 == 0) ? x : y;
        double expected[5] = {std::rint(0.4 * x), x > 2 ? 1.0 : 0.0,
                              std::min(1.0, std::pow(std::fabs(0.1 * (x + 0.4)) + 0.75, -4.0)),
                              x / 6.283185307179586 - std::rint(x / 6.283185307179586),
                              std::rint(0.4 * y)};
        for (int o = 0; o < 5; o++) {
            if (std::fabs(out[o][k] - expected[o]) > 1e-5 * std::max(1.0, std::fabs(expected[o]))) {
                std::printf("    output %d, x = %g: %g instead of %g\\n", o, x, double(out[o][k]),
                            expected[o]);
                failures++;
            }
        }
    }
    return failures ? 1 : 0;
}
"""


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    parser.add_argument("--cxx", default="c++")
    parser.add_argument("--langs", nargs="+", default=["cpp", "ocpp"])
    args = parser.parse_args()

    failures = 0
    with tempfile.TemporaryDirectory(prefix="faust-input-interval-") as temp:
        work = Path(temp)
        dsp_file = work / "input.dsp"
        dsp_file.write_text(DSP)
        (work / "runner.cpp").write_text(RUNNER)
        for lang in args.langs:
            for precision in ["-single", "-double"]:
                leg = f"{lang} {precision}"
                r = subprocess.run([str(args.faust.resolve()), "-lang", lang, precision,
                                    str(dsp_file), "-o", str(work / "generated.cpp")],
                                   cwd=work, capture_output=True, text=True)
                if r.returncode != 0:
                    print(f"FAIL [{leg}]: faust failed: {r.stderr.strip()}")
                    failures += 1
                    continue
                define = ["-DFAUSTFLOAT=double"] if precision == "-double" else []
                r = subprocess.run([args.cxx, "-std=c++17", "-O1", *define,
                                    "-I", str(repo / "architecture"), "runner.cpp",
                                    "-o", "runner"],
                                   cwd=work, capture_output=True, text=True)
                if r.returncode != 0:
                    print(f"FAIL [{leg}]: the C++ compiler failed: {r.stderr.strip()}")
                    failures += 1
                    continue
                r = subprocess.run([str(work / "runner")], cwd=work, capture_output=True,
                                   text=True)
                if r.returncode != 0:
                    print(f"FAIL [{leg}]: wrong output")
                    print(r.stdout.rstrip())
                    failures += 1
                else:
                    print(f"ok   [{leg}]")
    if failures:
        sys.exit(1)


if __name__ == "__main__":
    main()
