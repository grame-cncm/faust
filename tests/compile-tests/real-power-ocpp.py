#!/usr/bin/env python3
"""The real power of a constant integer exponent, in the ocpp generator (LA-PUISSANCE).

The normal form writes a product x * x * x as pow(x, 3), and the promotion gives the exponent
of a real power the real nature : 3.0. The cpp generator writes such a power as products
(isIntPowArg, exponents 0 to 8), and so does ocpp now, faustpower<k>, instead of calling the
libm pow (which only -ffast-math turned into products) ; beyond 8, the interval model widens
the power by the 2 ulps of the libm only, and the libm pow stays.

1. The code : for x real, in single and double precision, pow(x, k) is faustpower<k> for k
   from 2 to 8, written with an integer or a real exponent, and for the product x * x * x ;
   pow (powf) for k = 9 ; neither for k = 0 and 1 (folded). The power of integers keeps
   faustpower<k> for every k (the product wrapped on 32 bits).
2. The values, ocpp against cpp and against the exact power : x^2 and x^3 equal to those of
   cpp bit for bit ; x^k, k from 2 to 8, within k ulps of the exact power rounded to the
   program's precision (the widening of the interval model) ; NaN, +-inf and +-0 give the
   values of the libm pow, the sign of a zero included.
"""

import argparse
from fractions import Fraction
import math
from pathlib import Path
import re
import struct
import subprocess
import sys
import tempfile

INPUTS = [1.1, -1.3, 0.5, -0.75, 3.0, -2.5, 0.1, 7.9, -0.33, 12.5,
          0.0, -0.0, math.inf, -math.inf, math.nan]

RUNNER = r"""
#include <faust/dsp/dsp.h>
#include <faust/gui/meta.h>
#include <faust/gui/UI.h>
#include "generated.cpp"
#include <cmath>
#include <cstdio>

int main()
{
    static const double in[] = {%INPUTS%};
    const int n = sizeof(in) / sizeof(in[0]);
    FAUSTFLOAT input[64], outs[8][64];
    for (int i = 0; i < n; i++) input[i] = FAUSTFLOAT(in[i]);
    FAUSTFLOAT* inputs[1] = {input};
    FAUSTFLOAT* outputs[8];
    for (int j = 0; j < 8; j++) outputs[j] = outs[j];
    mydsp dsp;
    dsp.init(48000);
    dsp.compute(n, inputs, outputs);
    for (int i = 0; i < n; i++) {
        printf("%a", double(input[i]));
        for (int j = 0; j < 8; j++) printf(" %a", double(outs[j][i]));
        printf(" %a\n", double(std::pow(input[i], FAUSTFLOAT(3))));
    }
    return 0;
}
"""

# x^2 .. x^8, then the product x * x * x
VALUES = "process = _ <: par(i, 7, pow(_, i + 2)), (_ <: _*_*_);\n"


def compute_code(text):
    m = re.search(r"virtual void compute\s*\(", text)
    if m is None:
        raise RuntimeError("no compute method in the generated code")
    return text[m.start():]


def faust(args, dsp, lang, prec, out=None):
    cmd = [str(args.faust), "-lang", lang, "-" + prec, str(dsp)]
    if out is not None:
        cmd += ["-o", str(out)]
    r = subprocess.run(cmd, capture_output=True, text=True)
    if r.returncode != 0:
        raise RuntimeError(f"faust {lang} {prec} {dsp.name} : {r.stderr.strip()}")
    return r.stdout


def round_to(prec, x):
    return struct.unpack("f", struct.pack("f", x))[0] if prec == "single" else x


def ulp(prec, x):
    if prec == "single":
        f = struct.unpack("I", struct.pack("f", abs(x)))[0]
        return struct.unpack("f", struct.pack("I", f + 1))[0] - abs(x)
    return math.ulp(x)


def check_code(args, work):
    fails = []
    cases = []
    for k in range(0, 10):
        cases.append((f"process = pow(_, {k});\n", k, f"pow(_, {k})"))
        cases.append((f"process = pow(_, {k}.0);\n", k, f"pow(_, {k}.0)"))
    cases.append(("process = _ <: _*_*_;\n", 3, "_*_*_"))
    for prec in ("single", "double"):
        for src, k, label in cases:
            dsp = work / "code.dsp"
            dsp.write_text(src)
            code = compute_code(faust(args, dsp, "ocpp", prec))
            power = re.search(r"faustpower<(\d+)>\((float|double)\(", code)
            libm = re.search(r"\bpow[fl]?\(", code)
            if 2 <= k <= 8:
                ok = power is not None and int(power.group(1)) == k and libm is None
            elif k == 9:
                ok = power is None and libm is not None
            else:
                ok = power is None and libm is None
            print(f"{'ok  ' if ok else 'FAIL'} code {prec:6s} {label:12s}"
                  f" faustpower={power.group(0) if power else '-'} libm={'yes' if libm else 'no'}")
            if not ok:
                fails.append(f"code {prec} {label}")
        dsp = work / "int.dsp"
        dsp.write_text("process = int(_ * 100) <: pow(_, 20);\n")
        code = compute_code(faust(args, dsp, "ocpp", prec))
        ok = re.search(r"faustpower<20>\(int\(", code) is not None
        print(f"{'ok  ' if ok else 'FAIL'} code {prec:6s} integers     pow(int, 20) is faustpower<20>")
        if not ok:
            fails.append(f"code {prec} integers")
    return fails


def run_values(args, work, lang, prec):
    d = work / f"{lang}-{prec}"
    d.mkdir()
    (d / "values.dsp").write_text(VALUES)
    faust(args, d / "values.dsp", lang, prec, d / "generated.cpp")
    lits = ", ".join("NAN" if math.isnan(v) else ("-INFINITY" if v == -math.inf else
                     ("INFINITY" if v == math.inf else repr(v))) for v in INPUTS)
    (d / "runner.cpp").write_text(RUNNER.replace("%INPUTS%", lits))
    fl = "float" if prec == "single" else "double"
    subprocess.run([args.cxx, "-O1", "-ffp-contract=off", "-std=c++17", f"-DFAUSTFLOAT={fl}",
                    "-I", str(args.arch), str(d / "runner.cpp"), "-o", str(d / "runner")],
                   check=True, cwd=d)
    out = subprocess.run([str(d / "runner")], capture_output=True, text=True, check=True).stdout
    return [[float.fromhex(v) for v in line.split()] for line in out.split("\n") if line]


def same(a, b):
    if math.isnan(a) or math.isnan(b):
        return math.isnan(a) and math.isnan(b)
    return a == b and math.copysign(1, a) == math.copysign(1, b)


def check_values(args, work):
    fails = []
    for prec in ("single", "double"):
        ocpp = run_values(args, work, "ocpp", prec)
        cpp = run_values(args, work, "cpp", prec)
        bad = 0
        for ro, rc in zip(ocpp, cpp):
            x = ro[0]
            for k in range(2, 9):
                y = ro[k - 1]
                if not math.isfinite(x) or x == 0:
                    ref = round_to(prec, math.pow(x, k))
                    ok = same(y, ref)
                else:
                    exact = round_to(prec, float(Fraction(x) ** k))
                    ok = math.isfinite(y) and abs(y - exact) <= k * ulp(prec, exact)
                if k in (2, 3):
                    ok = ok and same(y, rc[k - 1])
                if not ok:
                    bad += 1
                    print(f"FAIL value {prec} x={x!r} k={k} : ocpp {y!r}, cpp {rc[k - 1]!r}")
            # the product x * x * x : the power of k = 3, and pow(x, 3) for the special values
            if not same(ro[8], ro[2]) or (not math.isfinite(x) or x == 0) and not same(ro[8], ro[9]):
                bad += 1
                print(f"FAIL value {prec} x={x!r} x*x*x : {ro[8]!r}, pow : {ro[9]!r}")
        print(f"{'ok  ' if bad == 0 else 'FAIL'} values {prec} : {len(ocpp)} inputs, x^2 .. x^8 and x*x*x,"
              f" {bad} wrong")
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
    with tempfile.TemporaryDirectory(prefix="faust-real-power-") as temp:
        work = Path(temp)
        fails = check_code(args, work) + check_values(args, work)
    if fails:
        print(f"{len(fails)} failures : {', '.join(fails)}")
        sys.exit(1)
    print("The real powers of a constant integer exponent are products in ocpp, within the interval model.")


if __name__ == "__main__":
    main()
