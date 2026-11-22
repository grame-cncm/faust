#!/usr/bin/env python3
"""The smoother of a slow target written by its error, in single precision (irmErrorForm.hh).

si.smooth of a control is the node IRM(x; p), y = mix(p, x, y'). In single precision the C and
C++ generators write it by its error e = y - x : the jump x' - x added to the error once per
block, e = p * e' and y = x + e per sample. The weighted sum (1 - p) * x + p * y' stops up to
ulp(x) / (2 (1 - p)) short of x, 0.06 short of 4000 for si.smoo at 48 kHz ; the error form
reaches x. In double precision the code is the weighted sum.

The programs : si.smoo of a slider in [0, 5000], alone, and feeding a comparison (a node that
reaches a decision, as the reed of a clarinet) ; si.smooth(ba.tau2pole(0.1)) of the same slider.
The slider goes from 0 to 4000, then to 4001, then to 1000 ; each value is held 4 s at 48 kHz.

1. The code : in single precision, compute() holds the error and the previous target, fields
   of their own, and adds the jump before its loop ; in double precision it does not.
2. The values, in cpp, cpp -vec and ocpp : in single precision, the output equals the target
   exactly over the last second of each value, and is never below 0, the lower bound of its
   certified interval (the form may cross 0 by a rounding, its output is bounded there) ; in
   double precision, it is within 1e-8 of the target (the weighted sum stops up to 1e-9 short
   of it). ocpp -vec emits through -ls, which keeps the weighted sum : it is not tested here.
"""

import argparse
from pathlib import Path
import re
import subprocess
import sys
import tempfile

DSP = {
    "smoo": 'import("stdfaust.lib");\nprocess = hslider("x", 0, 0, 5000, 0.001) : si.smoo;\n',
    "decision": 'import("stdfaust.lib");\n'
                'process = hslider("x", 0, 0, 5000, 0.001) : si.smoo <: _, (_ > 2000.5);\n',
    "tau01": 'import("stdfaust.lib");\n'
             'process = hslider("x", 0, 0, 5000, 0.001) : si.smooth(ba.tau2pole(0.1));\n',
}

TARGETS = [4000.0, 4001.0, 1000.0]
SR = 48000
HOLD = 4 * SR
BLOCK = 64

RUNNER = r"""
#include <faust/dsp/dsp.h>
#include <faust/gui/meta.h>
#include <faust/gui/UI.h>
#include <cstdio>

struct ZoneUI : public UI {
    FAUSTFLOAT* fX = nullptr;
    void openTabBox(const char*) override {}
    void openHorizontalBox(const char*) override {}
    void openVerticalBox(const char*) override {}
    void closeBox() override {}
    void addButton(const char*, FAUSTFLOAT* z) override { *z = 0; }
    void addCheckButton(const char*, FAUSTFLOAT* z) override { *z = 0; }
    void addVerticalSlider(const char*, FAUSTFLOAT* z, FAUSTFLOAT i, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT) override { *z = i; }
    void addHorizontalSlider(const char*, FAUSTFLOAT* z, FAUSTFLOAT i, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT) override { *z = i; fX = z; }
    void addNumEntry(const char*, FAUSTFLOAT* z, FAUSTFLOAT i, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT) override { *z = i; }
    void addHorizontalBargraph(const char*, FAUSTFLOAT*, FAUSTFLOAT, FAUSTFLOAT) override {}
    void addVerticalBargraph(const char*, FAUSTFLOAT*, FAUSTFLOAT, FAUSTFLOAT) override {}
    void addSoundfile(const char*, const char*, Soundfile**) override {}
};

#include "generated.cpp"

int main()
{
    const double targets[] = {TARGETS};
    const int    hold = HOLD, block = BLOCK, sr = SR;
    static FAUSTFLOAT outs[2][BLOCK];
    FAUSTFLOAT* outputs[2] = {outs[0], outs[1]};
    mydsp dsp;
    dsp.init(sr);
    ZoneUI ui;
    dsp.buildUserInterface(&ui);
    for (double t : targets) {
        *ui.fX = FAUSTFLOAT(t);
        for (int n = 0; n < hold; n += block) {
            dsp.compute(block, nullptr, outputs);
            if (n >= hold - sr) {
                for (int i = 0; i < block; i++) printf("%a\n", double(outs[0][i]));
            } else {
                double lo = outs[0][0];
                for (int i = 1; i < block; i++) lo = (double(outs[0][i]) < lo) ? double(outs[0][i]) : lo;
                printf("min %a\n", lo);
            }
        }
    }
    return 0;
}
"""


def faust(args, dsp, lang, prec, extra, out):
    cmd = [str(args.faust), "-lang", lang, "-" + prec] + extra + [str(dsp), "-o", str(out)]
    r = subprocess.run(cmd, capture_output=True, text=True, cwd=dsp.parent)
    if r.returncode != 0:
        raise RuntimeError(f"faust {' '.join(cmd[1:])} : {r.stderr.strip()}")
    return out.read_text()


def compute_part(text):
    return text[text.index("void compute"):]


def run(args, work, cpp, prec):
    d = work / "run"
    d.mkdir(exist_ok=True)
    (d / "generated.cpp").write_text(cpp)
    src = (RUNNER.replace("TARGETS", ", ".join(repr(t) for t in TARGETS))
           .replace("HOLD", str(HOLD)).replace("BLOCK", str(BLOCK)).replace("SR", str(SR)))
    (d / "runner.cpp").write_text(src)
    fl = "float" if prec == "single" else "double"
    subprocess.run([args.cxx, "-O1", "-ffp-contract=off", "-std=c++17", f"-DFAUSTFLOAT={fl}",
                    "-I", str(args.arch), str(d / "runner.cpp"), "-o", str(d / "runner")],
                   check=True, capture_output=True, text=True)
    out = subprocess.run([str(d / "runner")], capture_output=True, text=True, check=True).stdout
    lows, tails, cur = [], [], []
    for line in out.splitlines():
        if line.startswith("min "):
            lows.append(float.fromhex(line[4:]))
            if cur:
                tails.append(cur)
                cur = []
        else:
            cur.append(float.fromhex(line))
    tails.append(cur)
    return lows, [t for t in tails if t]


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    parser.add_argument("--cxx", default="g++")
    parser.add_argument("--arch", type=Path, default=repo / "architecture")
    args, _ = parser.parse_known_args()
    args.faust = args.faust.resolve()
    fails = []
    with tempfile.TemporaryDirectory(prefix="faust-smoother-error-") as temp:
        work = Path(temp)
        for name, src in DSP.items():
            dsp = work / f"{name}.dsp"
            dsp.write_text(src)
            for lang, extra in (("cpp", []), ("cpp", ["-vec"]), ("ocpp", [])):
                for prec in ("single", "double"):
                    case = f"{name:8s} {lang:4s} {' '.join(extra):4s} {prec}"
                    code = compute_part(faust(args, dsp, lang, prec, extra, work / "gen.cpp"))
                    jump = re.search(r"fIRMe\d+ = fIRMe\d+ \+ \(fIRMx\d+ - ", code) is not None
                    if jump != (prec == "single"):
                        fails.append(case)
                        print(f"FAIL {case} : the jump of the target {'missing' if prec == 'single' else 'present'}")
                        continue
                    lows, tails = run(args, work, faust(args, dsp, lang, prec, extra, work / "gen.cpp"), prec)
                    tol = 0.0 if prec == "single" else 1e-8
                    worst = max(abs(v - t) for t, tail in zip(TARGETS, tails) for v in tail)
                    lowest = min(lows)
                    ok = len(tails) == len(TARGETS) and worst <= tol and lowest >= 0
                    print(f"{'ok  ' if ok else 'FAIL'} {case} : largest distance to the target over the last "
                          f"second {worst:.3g} (tolerance {tol:g}), lowest output {lowest:.3g}")
                    if not ok:
                        fails.append(case)
    if fails:
        print(f"{len(fails)} failures : {', '.join(fails)}")
        sys.exit(1)
    print("The smoothers of a control reach their target in single precision.")


if __name__ == "__main__":
    main()
