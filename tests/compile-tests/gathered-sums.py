#!/usr/bin/env python3
"""The nested sums gathered before the partial sums (step 3f.1 of the computation form).

A real sum at the sample rate that only one sum reads, or its negation, is spliced into
that sum when the gathered sum has at least 8 sample-rate terms ; the gathered sum is then
cut in 4 partial sums (sumLanes). The decoders below give such nested sums (the gains of
the speakers, a sum subtracted from a number, gains of both signs), in cpp and ocpp, single
and double precision.

1. The code : the default and -nosl differ (the gathering and the partial sums happen),
   and -nosl writes no partial sum.
2. The values : the default and -nosl compute the same outputs, up to the rounding of a
   reassociation : over 2 000 samples of a deterministic input, the largest difference is
   below 1e-5 (single) or 1e-12 (double) of the largest output. A term spliced with the
   wrong sign, or lost, is far beyond.
"""

import argparse
import math
from pathlib import Path
import re
import subprocess
import sys
import tempfile

DSP = {
    "decoder": """
a = hslider("angle", 0.3, -6.28, 6.28, 0.001) : *(0.001) : +~*(0.999);
r = hslider("radius", 1, 0, 5, 0.001) : *(0.001) : +~*(0.999);
g(j) = max(0, min(1, r*(j+1) - j));
speaker(k) = 0.0625 + sum(j, 4, g(j) * (0.1/(j+1)) * cos((j+1)*(a - k*0.785398)));
w(k) = 0.5 + 0.4*cos(k*0.785398);
process(x) = x * sum(k, 8, w(k) * speaker(k)), x * (1 - sum(k, 8, (1 - w(k)) * speaker(k)));
""",
    "signs": """
a = hslider("angle", 0.7, -6.28, 6.28, 0.001) : *(0.001) : +~*(0.999);
r = hslider("radius", 2, 0, 5, 0.001) : *(0.001) : +~*(0.999);
g(j) = max(0, min(1, r*(j+1) - j));
speaker(k) = 0.0625 - sum(j, 5, g(j) * (0.1/(j+1)) * sin((j+1)*(a - k*0.6283185)));
w(k) = 0.7*cos(k*0.6283185);
process(x) = x * sum(k, 10, w(k) * speaker(k)), x * (0.25 - sum(k, 10, w(k)*w(k) * speaker(k)));
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
    with tempfile.TemporaryDirectory(prefix="faust-gathered-sums-") as temp:
        work = Path(temp)
        for name, src in DSP.items():
            dsp = work / f"{name}.dsp"
            dsp.write_text(src)
            for lang in ("cpp", "ocpp"):
                for prec in ("single", "double"):
                    case = f"{name} {lang:4s} {prec}"
                    dflt = faust(args, dsp, lang, prec, [], work / "dflt.cpp")
                    nosl = faust(args, dsp, lang, prec, ["-nosl"], work / "nosl.cpp")
                    if body(dflt) == body(nosl):
                        fails.append(f"{case} : the default code is the code of -nosl")
                        print(f"FAIL {case} : no partial sum")
                        continue
                    a, b = run(args, work, dflt, prec), run(args, work, nosl, prec)
                    scale = max(abs(v) for row in b for v in row)
                    diff = max(abs(x - y) for ra, rb in zip(a, b) for x, y in zip(ra, rb))
                    tol = (1e-5 if prec == "single" else 1e-12) * scale
                    ok = len(a) == len(b) and scale > 0 and diff <= tol and not math.isnan(diff)
                    print(f"{'ok  ' if ok else 'FAIL'} {case} : largest output {scale:.3g}, "
                          f"largest difference to -nosl {diff:.3g} (tolerance {tol:.3g})")
                    if not ok:
                        fails.append(case)
    if fails:
        print(f"{len(fails)} failures : {', '.join(fails)}")
        sys.exit(1)
    print("The gathered sums compute the values of the nested sums, up to the rounding.")


if __name__ == "__main__":
    main()
