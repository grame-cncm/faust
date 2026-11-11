#!/usr/bin/env python3
"""The forms of the real max and min read the signs of the zeros in the intervals
(LES-NAN-DU-MAX-ET-DU-MIN, « Le signe des zéros lu dans les intervalles »).

The comparison (p < q) ? q : p of a max gives its first operand on a tie : it is exact when p
is not NaN and is not -0 against a +0 (+0 against a -0 for a min). The generators read the zeros
an operand may hold in the bounds of its interval (in float and double, on an interval of negative
lsb), not only in a literal zero. The inputs are bounded in the program, xc = max(-2, min(2, x)),
so that the intervals hold the signs : p = abs(xc) is never -0, n = -1*abs(xc) is never +0, xc - yc
and xc*yc may be either. (The interval of xc*xc holds -0 : the power of an interval holding zero
keeps a zero of either sign, an imprecision of the analysis, not of this rule.)

1. The forms : the helper each max and min calls for in ocpp and cpp, single precision.
2. The values : x and y in {1.5, -2, +0, -0, +inf, -inf, 0.25}, sixteen max and min of p, n, q,
   r and abs, compared bit for bit, the signs of the zeros included, with the model computed
   here, in single and double precision, for cpp and ocpp, compiled by g++ and, when installed,
   by clang++.
"""

import argparse
import math
from pathlib import Path
import re
import shutil
import struct
import subprocess
import sys
import tempfile

VALUES = [1.5, -2.0, 0.0, -0.0, math.inf, -math.inf, 0.25]

DEFS = ("with { xc = max(-2.0, min(2.0, x)); yc = max(-2.0, min(2.0, y)); p = abs(xc); n = -1*abs(xc);\n"
        "       q = xc - yc; r = xc*yc; u = abs(xc); v = abs(yc); w = 0.5*abs(yc); };")

# the outputs and how the model computes them from p, n, q, r, u, v, w
OUTPUTS = [
    ("max(p, q)", lambda o: rmax(o["p"], o["q"])), ("max(q, p)", lambda o: rmax(o["q"], o["p"])),
    ("min(p, q)", lambda o: rmin(o["p"], o["q"])), ("min(q, p)", lambda o: rmin(o["q"], o["p"])),
    ("max(n, q)", lambda o: rmax(o["n"], o["q"])), ("max(q, n)", lambda o: rmax(o["q"], o["n"])),
    ("min(n, q)", lambda o: rmin(o["n"], o["q"])), ("min(q, n)", lambda o: rmin(o["q"], o["n"])),
    ("max(p, n)", lambda o: rmax(o["p"], o["n"])), ("min(n, p)", lambda o: rmin(o["n"], o["p"])),
    ("max(u, v)", lambda o: rmax(o["u"], o["v"])), ("min(u, w)", lambda o: rmin(o["u"], o["w"])),
    ("max(r, p)", lambda o: rmax(o["r"], o["p"])), ("min(r, n)", lambda o: rmin(o["r"], o["n"])),
    ("max(q, r)", lambda o: rmax(o["q"], o["r"])), ("min(q, r)", lambda o: rmin(o["q"], o["r"])),
]
VALUES_DSP = "process(x, y) = " + ", ".join(e for e, _ in OUTPUTS) + "\n" + DEFS + "\n"

# the helper each one calls for, without the type suffix : the comparison with an operand that
# cannot be the losing zero first, the free form when no tie of zeros of different signs is
# possible, the full form when both operands may be both zeros
FORMS = [("max(p, q)", "faustmax", "p"), ("max(q, p)", "faustmax", "p"),
         ("min(n, q)", "faustmin", "n"), ("min(q, n)", "faustmin", "n"),
         ("max(p, n)", "faustmax", "p"), ("min(n, p)", "faustmin", "n"),
         ("max(u, v)", "faustmaxk", None), ("min(u, w)", "faustmink", None),
         ("max(q, r)", "faustmaxn", None), ("min(q, r)", "faustminn", None)]


def rmax(a, b):
    if math.isnan(a): return b
    if math.isnan(b): return a
    if a == b: return a if math.copysign(1, a) > 0 else b
    return max(a, b)


def rmin(a, b):
    if math.isnan(a): return b
    if math.isnan(b): return a
    if a == b: return a if math.copysign(1, a) < 0 else b
    return min(a, b)


def f32(v):
    return struct.unpack("f", struct.pack("f", v))[0]


def model(prec):
    rnd = f32 if prec == "single" else (lambda v: v)
    rows = []
    for x in VALUES:
        for y in VALUES:
            xc, yc = rmax(-2.0, rmin(2.0, x)), rmax(-2.0, rmin(2.0, y))
            p = abs(xc)
            o = {"p": p, "n": -p, "q": rnd(xc - yc), "r": rnd(xc * yc), "u": abs(xc), "v": abs(yc),
                 "w": rnd(0.5 * abs(yc))}
            rows.append([f(o) for _, f in OUTPUTS])
    return rows


def same(u, v):
    if math.isnan(u) or math.isnan(v):
        return math.isnan(u) and math.isnan(v)
    return u == v and math.copysign(1, u) == math.copysign(1, v)


def lit(v):
    if math.isinf(v):
        return "INFINITY" if v > 0 else "-INFINITY"
    return "-0.0" if v == 0 and math.copysign(1, v) < 0 else repr(v)


PAIRS = ", ".join(f"{{{lit(x)}, {lit(y)}}}" for x in VALUES for y in VALUES)
N = len(OUTPUTS)

CPP_RUNNER = """
#include <faust/dsp/dsp.h>
#include <faust/gui/meta.h>
#include <faust/gui/UI.h>
#include <cmath>
#include <cstdio>
#include "generated.cpp"
int main() {
    static const double in[][2] = {%PAIRS%};
    const int n = sizeof(in) / sizeof(in[0]);
    static FAUSTFLOAT i0[64], i1[64], o[%N%][64];
    FAUSTFLOAT* ip[2] = {i0, i1}; FAUSTFLOAT* op[%N%];
    for (int k = 0; k < %N%; k++) op[k] = o[k];
    for (int i = 0; i < n; i++) { i0[i] = FAUSTFLOAT(in[i][0]); i1[i] = FAUSTFLOAT(in[i][1]); }
    mydsp d; d.init(48000); d.compute(n, ip, op);
    for (int i = 0; i < n; i++) { for (int k = 0; k < %N%; k++) printf("%a ", double(o[k][i])); printf("\\n"); }
    return 0;
}
""".replace("%PAIRS%", PAIRS).replace("%N%", str(N))


def run(command, work):
    r = subprocess.run([str(c) for c in command], cwd=work, capture_output=True, text=True)
    if r.returncode:
        print(f"FAIL {' '.join(str(c) for c in command[:4])} ... : {r.stderr.strip()[:300]}")
    return r


def compute_code(text):
    i = text.find("void compute")
    return text[i:] if i >= 0 else ""


def check_forms(args, work):
    fails = []
    for lang in ("ocpp", "cpp"):
        for expr, helper, first in FORMS:
            dsp = work / "form.dsp"
            dsp.write_text(f"process(x, y) = {expr}\n{DEFS}\n")
            r = run([args.faust, "-lang", lang, "-single", dsp], work)
            if r.returncode:
                fails.append(f"forms {lang} {expr}")
                continue
            # the outermost call of the output, the bounds of the inputs aside
            line = next((l for l in compute_code(r.stdout).splitlines() if re.search(r"output0\[i0?\] =", l)), "")
            calls = re.findall(r"\b(faust(?:max|min)[kn]?)f\(", line)[:1]
            ok = calls == [helper]
            if ok and first is not None:
                # the operand that cannot be the losing zero is written first : abs(xc), or its
                # negation, as the generator writes it
                m = re.search(helper + r"f\(\s*\(?\s*([^,]*)", line)
                arg = m.group(1) if m else ""
                # p is never a negation nor a difference (the other operands are), n is a negation
                arg = arg.lstrip("(").strip()
                if first == "p":
                    ok = not arg.startswith("-") and " - " not in arg
                else:
                    ok = arg.startswith("-")
            print(f"{'ok  ' if ok else 'FAIL'} forms {lang:4s} {expr:10s} : {calls} (expected {helper}"
                  f"{', ' + first + ' first' if first else ''})")
            if not ok:
                fails.append(f"forms {lang} {expr}")
    return fails


def check_rows(label, rows, expected):
    wrong = 0
    for x_i, (got, want) in enumerate(zip(rows, expected)):
        for k, (g, w) in enumerate(zip(got, want)):
            if not same(g, w):
                if wrong < 6:
                    x, y = VALUES[x_i // len(VALUES)], VALUES[x_i % len(VALUES)]
                    print(f"     {label} x={x} y={y} {OUTPUTS[k][0]} : {g!r}, expected {w!r}")
                wrong += 1
    ok = wrong == 0 and len(rows) == len(expected)
    print(f"{'ok  ' if ok else 'FAIL'} values {label} : {len(rows)} pairs of inputs, {N} outputs, {wrong} wrong")
    return ok


def check_values(args, work):
    fails = []
    compilers = [c for c in ("g++", "clang++") if shutil.which(c)]
    for prec in ("single", "double"):
        expected = model(prec)
        for lang in ("cpp", "ocpp"):
            d = work / f"{lang}-{prec}"
            d.mkdir()
            (d / "values.dsp").write_text(VALUES_DSP)
            gen = d / "generated.cpp"
            if run([args.faust, "-lang", lang, "-" + prec, d / "values.dsp", "-o", gen], d).returncode:
                fails.append(f"{lang} {prec}")
                continue
            (d / "runner.cpp").write_text(CPP_RUNNER)
            fl = "float" if prec == "single" else "double"
            for cxx in compilers:
                exe = d / f"runner-{cxx}"
                build = [cxx, "-std=c++17", "-O2", "-march=native", "-fno-fast-math", "-ffp-contract=fast",
                         f"-DFAUSTFLOAT={fl}", "-I", args.arch, d / "runner.cpp", "-o", exe]
                if run(build, d).returncode:
                    fails.append(f"{lang} {prec} {cxx} build")
                    continue
                out = run([exe], d).stdout
                rows = [[float.fromhex(v) for v in line.split()] for line in out.splitlines()]
                if not check_rows(f"{lang:4s} {prec} {cxx}", rows, expected):
                    fails.append(f"{lang} {prec} {cxx}")
    return fails


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    parser.add_argument("--arch", type=Path, default=repo / "architecture")
    args, _ = parser.parse_known_args()
    args.faust = args.faust.resolve()
    print(subprocess.run([args.faust, "--version"], capture_output=True, text=True).stdout.splitlines()[1])
    with tempfile.TemporaryDirectory(prefix="faust-minmax-zeros-") as temp:
        work = Path(temp)
        fails = check_forms(args, work) + check_values(args, work)
    if fails:
        print(f"{len(fails)} failures : {', '.join(fails)}")
        sys.exit(1)
    print("max and min keep their values with the forms the signs of the zeros allow.")


if __name__ == "__main__":
    main()
