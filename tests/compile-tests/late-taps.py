#!/usr/bin/env python3
"""The late term of a filter added last (step 3f.5 of the computation form, -nolt keeps the order).

A real FIR outside the cone of the memory decisions adds its taps from the last delay to the
first, the tap of delay 0 (computed in the sample) last ; a real IIR adds its feedback taps
from the last delay to y@1, then its input ; an IIR whose input is such a FIR, read by it
alone, takes the taps of the FIR in its own chain : the delayed taps of the FIR, the feedback
taps, then the tap of delay 0. The chain takes the sign of its first term. The cascades of
biquads below (coefficients of a control, and numbers) and the resonators (a positive y@1
tap, a negative y@2 tap) give FIR and IIR nodes, in cpp, ocpp and ocpp -ls, single and double
precision.

1. The code : the default and -nolt differ.
2. The values : the default and -nolt compute the same outputs, up to the rounding of a
   reassociation : over 2 000 samples of a deterministic input, the largest difference is
   below 1e-5 (single) or 1e-12 (double) of the largest output. A tap subtracted instead of
   added, or lost, is far beyond.
"""

import argparse
import math
from pathlib import Path
import re
import subprocess
import sys
import tempfile

DSP = {
    "biquads": """
g = hslider("gain", 0.3, 0, 1, 0.001);
bq(b0, b1, b2, a1, a2) = (+ ~ (_ <: *(0-a1), (_' : *(0-a2)) :> _)) <: *(b0), (_' : *(b1)), (_'' : *(b2)) :> _;
process = bq(0.2 + g, 0.4, 0.2, -0.5 * g, 0.25) : bq(0.3, -0.1 * g, 0.2, 0.3, 0.1 + 0.2 * g)
        : bq(0.25, 0.5, 0.25, -0.9, 0.4 * g) : bq(1, -2 * g, 1, -1.2 * g, 0.5)
        <: _, (_ : bq(0.5, 0, -0.5, 0.1, -0.3));
""",
    "resonators": """
f = hslider("freq", 0.1, 0.01, 0.5, 0.001);
r = 0.95;
res(k) = + ~ (_ <: *(2 * r * cos(f * (k + 1))), (_' : *(0 - r * r)) :> _) : *(1 - r);
process = _ <: par(k, 4, res(k)) :> _ <: _, (_ <: _, _' :> *(0.5));
""",
}

RUNNER = r"""
#include <faust/dsp/dsp.h>
#include <faust/gui/meta.h>
#include <faust/gui/UI.h>
#include <cmath>
#include <cstdio>

struct InitUI : public UI {
    void openTabBox(const char*) override {}
    void openHorizontalBox(const char*) override {}
    void openVerticalBox(const char*) override {}
    void closeBox() override {}
    void addButton(const char*, FAUSTFLOAT* z) override { *z = 0; }
    void addCheckButton(const char*, FAUSTFLOAT* z) override { *z = 0; }
    void addVerticalSlider(const char*, FAUSTFLOAT* z, FAUSTFLOAT i, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT) override { *z = i; }
    void addHorizontalSlider(const char*, FAUSTFLOAT* z, FAUSTFLOAT i, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT) override { *z = i; }
    void addNumEntry(const char*, FAUSTFLOAT* z, FAUSTFLOAT i, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT) override { *z = i; }
    void addHorizontalBargraph(const char*, FAUSTFLOAT*, FAUSTFLOAT, FAUSTFLOAT) override {}
    void addVerticalBargraph(const char*, FAUSTFLOAT*, FAUSTFLOAT, FAUSTFLOAT) override {}
    void addSoundfile(const char*, const char*, Soundfile**) override {}
};

#include "generated.cpp"

int main()
{
    const int n = 2000;
    static FAUSTFLOAT input[n], out0[n], out1[n];
    for (int i = 0; i < n; i++) input[i] = FAUSTFLOAT(std::sin(0.01 * i) + 0.3 * std::cos(0.37 * i));
    FAUSTFLOAT* inputs[1]  = {input};
    FAUSTFLOAT* outputs[2] = {out0, out1};
    mydsp dsp;
    dsp.init(48000);
    InitUI ui;
    dsp.buildUserInterface(&ui);
    dsp.compute(n, inputs, outputs);
    for (int i = 0; i < n; i++) printf("%a %a\n", double(out0[i]), double(out1[i]));
    return 0;
}
"""


def faust(args, dsp, lang, prec, extra, out):
    cmd = [str(args.faust), "-lang", lang, "-" + prec] + extra + [str(dsp), "-o", str(out)]
    r = subprocess.run(cmd, capture_output=True, text=True)
    if r.returncode != 0:
        raise RuntimeError(f"faust {' '.join(cmd[1:])} : {r.stderr.strip()}")
    return out.read_text()


def body(text):
    """the generated code without its header lines"""
    return "\n".join(l for l in text.splitlines()
                     if "Code generated with Faust" not in l and "ompil" not in l)


def run(args, work, cpp, prec):
    d = work / "run"
    d.mkdir(exist_ok=True)
    (d / "generated.cpp").write_text(cpp)
    (d / "runner.cpp").write_text(RUNNER)
    fl = "float" if prec == "single" else "double"
    subprocess.run([args.cxx, "-O1", "-ffp-contract=off", "-std=c++17", f"-DFAUSTFLOAT={fl}",
                    "-I", str(args.arch), str(d / "runner.cpp"), "-o", str(d / "runner")],
                   check=True, capture_output=True, text=True)
    out = subprocess.run([str(d / "runner")], capture_output=True, text=True, check=True).stdout
    return [[float.fromhex(v) for v in line.split()] for line in out.splitlines()]


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    parser.add_argument("--cxx", default="g++")
    parser.add_argument("--arch", type=Path, default=repo / "architecture")
    args, _ = parser.parse_known_args()
    args.faust = args.faust.resolve()
    fails = []
    with tempfile.TemporaryDirectory(prefix="faust-late-taps-") as temp:
        work = Path(temp)
        for name, src in DSP.items():
            dsp = work / f"{name}.dsp"
            dsp.write_text(src)
            for lang, extra in (("cpp", []), ("ocpp", []), ("ocpp", ["-ls"])):
                for prec in ("single", "double"):
                    case = f"{name} {lang:4s} {' '.join(extra):3s} {prec}"
                    dflt = faust(args, dsp, lang, prec, extra, work / "dflt.cpp")
                    nosl = faust(args, dsp, lang, prec, extra + ["-nolt"], work / "nosl.cpp")
                    if body(dflt) == body(nosl):
                        fails.append(f"{case} : the default code is the code of -nolt")
                        print(f"FAIL {case} : no late tap")
                        continue
                    a, b = run(args, work, dflt, prec), run(args, work, nosl, prec)
                    scale = max(abs(v) for row in b for v in row)
                    diff = max(abs(x - y) for ra, rb in zip(a, b) for x, y in zip(ra, rb))
                    tol = (1e-5 if prec == "single" else 1e-12) * scale
                    ok = len(a) == len(b) and scale > 0 and diff <= tol and not math.isnan(diff)
                    print(f"{'ok  ' if ok else 'FAIL'} {case} : largest output {scale:.3g}, "
                          f"largest difference to -nolt {diff:.3g} (tolerance {tol:.3g})")
                    if not ok:
                        fails.append(case)
    if fails:
        print(f"{len(fails)} failures : {', '.join(fails)}")
        sys.exit(1)
    print("The late taps compute the values of the taps in their order, up to the rounding.")


if __name__ == "__main__":
    main()
