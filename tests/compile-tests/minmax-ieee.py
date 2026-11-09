#!/usr/bin/env python3
"""The real max and min of Faust : maximumNumber and minimumNumber of IEEE 754-2019
(LES-NAN-DU-MAX-ET-DU-MIN).

A NaN operand gives the other one (NaN when both are), and -0 < +0 : max(-0, +0) = +0 and
min(-0, +0) = -0, in both orders ; the operation is commutative. The C and C++ generators
(cpp, ocpp, C) write each max and min in the cheapest form that has this value, from what the
interval of the program proves : faustmaxk (the first operand not NaN, no tie of zeros : fmax
under clang, the comparison otherwise), faustmax (a tie of zeros, the literal +0 first ; -0 for
faustmin), faustmaxn (any operands), with the libm suffix of the real type (f, none, l).

1. The code : the helper written for eleven max and min, in ocpp, cpp and C, single, double
   and quad (C : single and double).
2. The values : a = sqrt(x), b = sqrt(y) (NaN for a negative input, -0 for -0) and the inputs,
   x and y in {1.5, -2, +0, -0, +inf, -inf, 0.25} : sixteen max and min of a, b, x, y and the
   constants 0.5 and 0 in both orders, compared bit for bit with the model computed here, in
   single and double precision, for cpp, ocpp and C, compiled by g++ and gcc and, when
   installed, by clang.
3. The constant folding, done once in the normal form : max and min of -0 and +0 in both
   orders fold to +0 and -0 (read in the cpp code, which writes every output).
4. The interpreter of the signals, when the static libfaust of the build exists (--libfaust) :
   the same values in double precision.
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

# the outputs and how the model computes them from x, y, a = sqrt(x), b = sqrt(y)
OUTPUTS = [
    ("max(a, b)", lambda x, y, a, b: rmax(a, b)), ("min(a, b)", lambda x, y, a, b: rmin(a, b)),
    ("max(b, a)", lambda x, y, a, b: rmax(b, a)), ("min(b, a)", lambda x, y, a, b: rmin(b, a)),
    ("max(a, 0.5)", lambda x, y, a, b: rmax(a, 0.5)), ("min(a, 0.5)", lambda x, y, a, b: rmin(a, 0.5)),
    ("max(0.5, a)", lambda x, y, a, b: rmax(0.5, a)), ("min(0.5, a)", lambda x, y, a, b: rmin(0.5, a)),
    ("max(a, 0.0)", lambda x, y, a, b: rmax(a, 0.0)), ("min(a, 0.0)", lambda x, y, a, b: rmin(a, 0.0)),
    ("max(0.0, a)", lambda x, y, a, b: rmax(0.0, a)), ("min(0.0, a)", lambda x, y, a, b: rmin(0.0, a)),
    ("max(x, y)", lambda x, y, a, b: rmax(x, y)), ("min(x, y)", lambda x, y, a, b: rmin(x, y)),
    ("max(a, y)", lambda x, y, a, b: rmax(a, y)), ("min(y, a)", lambda x, y, a, b: rmin(y, a)),
]
VALUES_DSP = ("process(x, y) = " + ", ".join(e for e, _ in OUTPUTS) +
              "\nwith { a = sqrt(x); b = sqrt(y); };\n")

# the helper each max and min calls for, without the type suffix
FORMS = [("max(sqrt(x), 0.5)", "faustmaxk"), ("max(0.5, sqrt(x))", "faustmaxk"),
         ("max(x, 0.5)", "faustmaxk"), ("max(x, y)", "faustmaxn"), ("min(0.25, x)", "faustmink"),
         ("min(x, y)", "faustminn"), ("max(0.0, x)", "faustmax"), ("min(x, -2.0)", "faustmink"),
         ("max(x, 0.0)", "faustmax"), ("min(0.0, x)", "faustmin"), ("max(sqrt(x), sqrt(y))", "faustmaxn")]

FOLD_DSP = "z = 0.0 * -1.0;\nprocess = max(z, 0.0), max(0.0, z), min(z, 0.0), min(0.0, z);\n"
FOLD_EXPECTED = ["0.0", "0.0", "-0.0", "-0.0"]


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
    rows = []
    for x in VALUES:
        for y in VALUES:
            a = math.nan if x < 0 or x == -math.inf else math.sqrt(x)
            b = math.nan if y < 0 or y == -math.inf else math.sqrt(y)
            if x == 0: a = x   # sqrt(-0) = -0
            if y == 0: b = y
            if prec == "single":
                a, b = f32(a), f32(b)
            rows.append([f(x, y, a, b) for _, f in OUTPUTS])
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

C_RUNNER = """
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "faust/gui/CInterface.h"
#include "generated.c"
int main(void) {
    static const double in[][2] = {%PAIRS%};
    const int n = sizeof(in) / sizeof(in[0]);
    static FAUSTFLOAT i0[64], i1[64], o[%N%][64];
    FAUSTFLOAT* ip[2] = {i0, i1}; FAUSTFLOAT* op[%N%];
    for (int k = 0; k < %N%; k++) op[k] = o[k];
    for (int i = 0; i < n; i++) { i0[i] = (FAUSTFLOAT)in[i][0]; i1[i] = (FAUSTFLOAT)in[i][1]; }
    mydsp* d = newmydsp(); initmydsp(d, 48000); computemydsp(d, n, ip, op); deletemydsp(d);
    for (int i = 0; i < n; i++) { for (int k = 0; k < %N%; k++) printf("%a ", (double)o[k][i]); printf("\\n"); }
    return 0;
}
""".replace("%PAIRS%", PAIRS).replace("%N%", str(N))

INTERP_RUNNER = """
#include <cmath>
#include <cstdio>
#include <string>
#include "faust/dsp/signal-dsp.h"
int main(int argc, char* argv[]) {
    static const double in[][2] = {%PAIRS%};
    const int n = sizeof(in) / sizeof(in[0]);
    std::string error;
    const char* options[] = {"-double"};
    signal_dsp_factory* factory = createSignalDSPFactoryFromString("minmax", argv[1], 1, options, error);
    if (!factory) { printf("no factory : %s\\n", error.c_str()); return 1; }
    dsp* d = factory->createDSPInstance(); d->init(48000);
    static FAUSTFLOAT i0[64], i1[64], o[%N%][64];
    FAUSTFLOAT* ip[2] = {i0, i1}; FAUSTFLOAT* op[%N%];
    for (int k = 0; k < %N%; k++) op[k] = o[k];
    for (int i = 0; i < n; i++) { i0[i] = FAUSTFLOAT(in[i][0]); i1[i] = FAUSTFLOAT(in[i][1]); }
    d->compute(n, ip, op);
    for (int i = 0; i < n; i++) { for (int k = 0; k < %N%; k++) printf("%a ", double(o[k][i])); printf("\\n"); }
    delete d; deleteSignalDSPFactory(factory);
    return 0;
}
""".replace("%PAIRS%", PAIRS).replace("%N%", str(N))


def run(command, work, show=True):
    r = subprocess.run([str(c) for c in command], cwd=work, capture_output=True, text=True)
    if r.returncode != 0 and show:
        print("+", " ".join(map(str, command)))
        print((r.stdout + r.stderr).strip()[:2000])
    return r


def compute_code(text):
    m = re.search(r"(virtual void compute\s*\(|void computemydsp\s*\()", text)
    if m is None:
        raise RuntimeError("no compute function in the generated code")
    return text[m.start():]


def check_forms(args, work):
    fails = []
    dsp = work / "forms.dsp"
    dsp.write_text("process(x, y) = " + ", ".join(e for e, _ in FORMS) + ";\n")
    suffix = {"single": "f", "double": "", "quad": "l"}
    for lang in ("ocpp", "cpp", "c"):
        for prec in ("single", "double") + (("quad",) if lang != "c" else ()):
            r = run([args.faust, "-lang", lang, "-" + prec, dsp], work)
            if r.returncode:
                fails.append(f"forms {lang} {prec}")
                continue
            code = compute_code(r.stdout)
            got = re.findall(r"output(\d+)\[i0?\] = [^;]*?\b(faustm(?:ax|in)[kn]?[fl]?)\(", code)
            got = {int(o): h for o, h in got}
            bad = [(e, got.get(k), h + suffix[prec]) for k, (e, h) in enumerate(FORMS) if got.get(k) != h + suffix[prec]]
            for e, g, w in bad:
                print(f"FAIL form   {lang:4s} {prec:6s} {e} : {g}, expected {w}")
            print(f"{'ok  ' if not bad else 'FAIL'} forms  {lang:4s} {prec:6s} {len(FORMS) - len(bad)}/{len(FORMS)}")
            if bad:
                fails.append(f"forms {lang} {prec}")
    return fails


def check_rows(label, rows, expected):
    bad = 0
    for i, (got, want) in enumerate(zip(rows, expected)):
        for k, (g, w) in enumerate(zip(got, want)):
            if not same(float.fromhex(g), w):
                if bad < 4:
                    x, y = VALUES[i // len(VALUES)], VALUES[i % len(VALUES)]
                    print(f"FAIL {label} x={x!r} y={y!r} {OUTPUTS[k][0]} : {g}, expected {w!r}")
                bad += 1
    ok = bad == 0 and len(rows) == len(expected)
    print(f"{'ok  ' if ok else 'FAIL'} {label} : {len(rows)} pairs of inputs, {N} outputs, {bad} wrong")
    return ok


def check_values(args, work):
    fails = []
    for prec in ("single", "double"):
        expected = model(prec)
        fl = "float" if prec == "single" else "double"
        for lang in ("cpp", "ocpp", "c"):
            d = work / f"v-{lang}-{prec}"
            d.mkdir()
            (d / "values.dsp").write_text(VALUES_DSP)
            gen = d / ("generated.c" if lang == "c" else "generated.cpp")
            if run([args.faust, "-lang", lang, "-" + prec, d / "values.dsp", "-o", gen], d).returncode:
                fails.append(f"values {lang} {prec}")
                continue
            compilers = [args.cc, args.clang_c] if lang == "c" else [args.cxx, args.clang]
            for cc in [c for c in compilers if c and shutil.which(c)]:
                if lang == "c":
                    (d / "runner.c").write_text(C_RUNNER)
                    build = [cc, "-std=c11", "-O1", "-ffp-contract=off", f"-DFAUSTFLOAT={fl}",
                             "-I", args.arch, "runner.c", "-o", "runner", "-lm"]
                else:
                    (d / "runner.cpp").write_text(CPP_RUNNER)
                    build = [cc, "-std=c++17", "-O1", "-ffp-contract=off", f"-DFAUSTFLOAT={fl}",
                             "-I", args.arch, "runner.cpp", "-o", "runner"]
                label = f"values {lang:4s} {prec:6s} {Path(cc).name}"
                if run(build, d).returncode:
                    fails.append(label)
                    continue
                out = run([d / "runner"], d).stdout
                rows = [line.split() for line in out.split("\n") if line.strip()]
                if not check_rows(label, rows, expected):
                    fails.append(label)
    return fails


def check_folding(args, work):
    dsp = work / "fold.dsp"
    dsp.write_text(FOLD_DSP)
    fails = []
    # the folding is done once, in the normal form ; cpp writes every output (ocpp copies the equal ones)
    for lang in ("cpp",):
        code = compute_code(run([args.faust, "-lang", lang, "-double", dsp], work).stdout)
        got = re.findall(r"output\d\[i0?\] = \(?(?:static_cast<FAUSTFLOAT>|\(FAUSTFLOAT\))\(([^)]*)\)", code)
        ok = got == FOLD_EXPECTED
        print(f"{'ok  ' if ok else 'FAIL'} folding {lang:4s} max(-0, +0), max(+0, -0), min(-0, +0), min(+0, -0) : {got}")
        if not ok:
            fails.append(f"folding {lang}")
    return fails


def check_interpreter(args, work):
    if not args.libfaust.is_file():
        print(f"skip interpreter : no {args.libfaust} (build the static library, or pass --libfaust)")
        return []
    (work / "interp.cpp").write_text(INTERP_RUNNER)
    build = [args.cxx, "-std=c++17", "-O1", "-DFAUSTFLOAT=double", "-I", args.arch, "interp.cpp",
             args.libfaust.resolve(), "-lpthread", "-ldl", "-o", "interp"]
    if run(build, work).returncode:
        return ["interpreter build"]
    out = run([work / "interp", VALUES_DSP], work).stdout
    rows = [line.split() for line in out.split("\n") if line.strip()]
    return [] if check_rows("values interpreter double", rows, model("double")) else ["interpreter"]


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    parser.add_argument("--libfaust", type=Path, default=repo / "build/lib/libfaust.a")
    parser.add_argument("--cxx", default="g++")
    parser.add_argument("--cc", default="gcc")
    parser.add_argument("--clang", default="clang++", help="also compiled by clang, when installed")
    parser.add_argument("--clang-c", default="clang", help="the C compiler of clang, when installed")
    parser.add_argument("--arch", type=Path, default=repo / "architecture")
    args, _ = parser.parse_known_args()
    args.faust = args.faust.resolve()
    print(subprocess.run([args.faust, "--version"], capture_output=True, text=True).stdout.splitlines()[1])
    with tempfile.TemporaryDirectory(prefix="faust-minmax-ieee-") as temp:
        work = Path(temp)
        fails = check_forms(args, work) + check_values(args, work) + check_folding(args, work) + \
                check_interpreter(args, work)
    if fails:
        print(f"{len(fails)} failures : {', '.join(fails)}")
        sys.exit(1)
    print("max and min are maximumNumber and minimumNumber, in every form and every generator tested.")


if __name__ == "__main__":
    main()
