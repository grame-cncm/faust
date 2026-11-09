#!/usr/bin/env python3
"""The real max and min of the ocpp generator (LE-MAX-ET-LE-MIN).

ocpp wrote a real max as fmax and a real min as fmin, which g++ calls in the libm unless
-ffinite-math-only, and whose value differs from that of cpp when the first operand is NaN
(fmax(NaN, b) is b, std::max(NaN, b) is NaN). ocpp now writes them faustmax and faustmin, the
comparisons of std::max and std::min : max(a, b) = (a < b) ? b : a, min(a, b) = (b < a) ? b : a.

1. The code : in single, double and quad precision, a real max or min of ocpp is faustmax or
   faustmin, defined once, and its compute method calls neither fmax nor fmin ; the integer max
   and min stay faustmaxi and faustmini.
2. The values : max and min of two inputs in both orders, and against a constant on either
   side, on ordinary values, +-0, +-inf and NaN at each place, in single and double precision :
   the outputs of ocpp equal those of cpp bit for bit (the sign of a zero and NaN included) ;
   a NaN first operand gives NaN, a NaN second operand the first one.
"""

import argparse
import math
from pathlib import Path
import re
import struct
import subprocess
import sys
import tempfile

VALUES = [1.5, -2.0, 0.0, -0.0, math.inf, -math.inf, math.nan, 0.25]

DSP = """process(x, y) = max(x, y), min(x, y), max(y, x), min(y, x),
                 max(x, 0.5), min(x, 0.5), max(0.5, x), min(0.5, x);
"""

RUNNER = r"""
#include <faust/dsp/dsp.h>
#include <faust/gui/meta.h>
#include <faust/gui/UI.h>
#include "generated.cpp"
#include <cmath>
#include <cstdio>

int main()
{
    static const double v[] = {%VALUES%};
    const int m = sizeof(v) / sizeof(v[0]);
    static FAUSTFLOAT in0[256], in1[256], outs[8][256];
    int n = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++, n++) { in0[n] = FAUSTFLOAT(v[i]); in1[n] = FAUSTFLOAT(v[j]); }
    FAUSTFLOAT* inputs[2] = {in0, in1};
    FAUSTFLOAT* outputs[8];
    for (int k = 0; k < 8; k++) outputs[k] = outs[k];
    mydsp dsp;
    dsp.init(48000);
    dsp.compute(n, inputs, outputs);
    for (int i = 0; i < n; i++) {
        printf("%a %a", double(in0[i]), double(in1[i]));
        for (int k = 0; k < 8; k++) printf(" %a", double(outs[k][i]));
        printf("\n");
    }
    return 0;
}
"""


def faust(args, dsp, lang, prec, out=None):
    cmd = [str(args.faust), "-lang", lang, "-" + prec, str(dsp)]
    if out is not None:
        cmd += ["-o", str(out)]
    r = subprocess.run(cmd, capture_output=True, text=True)
    if r.returncode != 0:
        raise RuntimeError(f"faust {lang} {prec} {dsp.name} : {r.stderr.strip()}")
    return r.stdout


def compute_code(text):
    m = re.search(r"virtual void compute\s*\(", text)
    if m is None:
        raise RuntimeError("no compute method in the generated code")
    return text[m.start():]


def check_code(args, work):
    fails = []
    dsp = work / "code.dsp"
    dsp.write_text(DSP + "\n")
    idsp = work / "int.dsp"
    idsp.write_text("process = int(_ * 10) <: max(_, 3), min(_, -3);\n")
    for prec in ("single", "double", "quad"):
        text = faust(args, dsp, "ocpp", prec)
        code = compute_code(text)
        n_max, n_min = code.count("faustmax("), code.count("faustmin(")
        libm = re.search(r"\bf(max|min)[fl]?\(", code)
        defs = len(re.findall(r"static inline [a-z ]+ faust(max|min)\(", text))
        # the normal form may write max(x, y) and max(y, x) as one node
        ok = n_max >= 2 and n_min >= 2 and libm is None and defs == 2
        print(f"{'ok  ' if ok else 'FAIL'} code {prec:6s} faustmax {n_max}, faustmin {n_min}, "
              f"definitions {defs}, fmax/fmin {'yes' if libm else 'no'}")
        if not ok:
            fails.append(f"code {prec}")
        icode = compute_code(faust(args, idsp, "ocpp", prec))
        ok = "faustmaxi(" in icode and "faustmini(" in icode
        print(f"{'ok  ' if ok else 'FAIL'} code {prec:6s} integers : faustmaxi and faustmini")
        if not ok:
            fails.append(f"code {prec} integers")
    return fails


def lit(v):
    if math.isnan(v):
        return "NAN"
    if math.isinf(v):
        return "INFINITY" if v > 0 else "-INFINITY"
    return "-0.0" if v == 0 and math.copysign(1, v) < 0 else repr(v)


def run_values(args, work, lang, prec):
    d = work / f"{lang}-{prec}"
    d.mkdir()
    (d / "values.dsp").write_text(DSP)
    faust(args, d / "values.dsp", lang, prec, d / "generated.cpp")
    (d / "runner.cpp").write_text(RUNNER.replace("%VALUES%", ", ".join(lit(v) for v in VALUES)))
    fl = "float" if prec == "single" else "double"
    subprocess.run([args.cxx, "-O1", "-ffp-contract=off", "-std=c++17", f"-DFAUSTFLOAT={fl}",
                    "-I", str(args.arch), str(d / "runner.cpp"), "-o", str(d / "runner")],
                   check=True, cwd=d)
    out = subprocess.run([str(d / "runner")], capture_output=True, text=True, check=True).stdout
    return [line.split() for line in out.split("\n") if line]


def check_values(args, work):
    fails = []
    for prec in ("single", "double"):
        ocpp = run_values(args, work, "ocpp", prec)
        cpp = run_values(args, work, "cpp", prec)
        bad = 0
        first_nan = 0
        for ro, rc in zip(ocpp, cpp):
            # hex floats : equal text is equal bits, the sign of a zero included ; NaN as is
            if ro != rc:
                bad += 1
                print(f"FAIL value {prec} x={ro[0]} y={ro[1]} : ocpp {' '.join(ro[2:])} | cpp {' '.join(rc[2:])}")
            x = float.fromhex(ro[0])
            if math.isnan(x):
                first_nan += 1
                # max(x, 0.5) and min(x, 0.5) : a NaN first operand gives NaN
                if not (math.isnan(float.fromhex(ro[6])) and math.isnan(float.fromhex(ro[7]))):
                    bad += 1
                    print(f"FAIL value {prec} max(NaN, 0.5) = {ro[6]}, min(NaN, 0.5) = {ro[7]}")
                # max(0.5, x) and min(0.5, x) : a NaN second operand gives the first
                if float.fromhex(ro[8]) != 0.5 or float.fromhex(ro[9]) != 0.5:
                    bad += 1
                    print(f"FAIL value {prec} max(0.5, NaN) = {ro[8]}, min(0.5, NaN) = {ro[9]}")
        print(f"{'ok  ' if bad == 0 else 'FAIL'} values {prec} : {len(ocpp)} pairs of inputs, 8 outputs, "
              f"{first_nan} with a NaN first input, {bad} wrong")
        if bad:
            fails.append(f"values {prec}")
    return fails


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    parser.add_argument("--cxx", default="g++")
    parser.add_argument("--arch", type=Path, default=repo / "architecture")
    args, _ = parser.parse_known_args()
    args.faust = args.faust.resolve()
    with tempfile.TemporaryDirectory(prefix="faust-real-minmax-") as temp:
        work = Path(temp)
        fails = check_code(args, work) + check_values(args, work)
    if fails:
        print(f"{len(fails)} failures : {', '.join(fails)}")
        sys.exit(1)
    print("The real max and min of ocpp are the comparisons of cpp, with the values of cpp.")


if __name__ == "__main__":
    main()
