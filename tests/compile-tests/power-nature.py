#!/usr/bin/env python3
"""The nature of a power of integers.

pow(x, k), x and k integers, abbreviates the product x * ... * x for k >= 0 and the
division 1 / (x * ... * x) for k < 0. It is an integer when the sign of k proves k >= 0
(constants, controls of declared minimum >= 0, conversions, remainders, comparisons,
max with a positive term : the sign, computed on the structure, not the intervals), a real
otherwise : the wrapped product converted to a real for k >= 0, 1 / the wrapped product
of |k| factors for k < 0, +inf when that product is 0.

1. Variable exponents : pow(2, n) * 2, n in [0, 100], is an integer (0 at n = 31) ;
   pow(2, m) * 2, m in [-1, 100], is a real (-4294967296.0 at m = 31, 0.5 * 2 at m = -1) ;
   pow(0, m) is a possible division by 0, not a certain one : it compiles, +inf at m = -1 ;
   an attach in the exponent keeps its sign ; the sign of a control is its declared
   minimum under -norui as well.
2. -fui writes the program with the values of the controls : pow(2, n - 3) * 2, n = 34,
   is pow(2, 31) * 2, an integer, 0.
3. Folding against execution : for two constants the compiler folds the power the code
   computes, in the precision of the program ; pow(3, 0) is the integer 1, pow(2, -1)
   0.5, pow(2, -31) 1 / -2147483648. The same powers computed with controls give the
   same values. pow(x, 0) is the integer 1 whatever x, pow(i, 1.0) is a real.
4. Refusals : pow(0, -1) and pow(2, -32), certain divisions by 0.
5. The sign at run time : for each rule that proves an exponent >= 0 (comparison, int of a
   value >= 0 or NaN, max, min, fmod, %, &, >>, select2, delays, recursion, controls), an
   exponent read from two inputs pushed to the hard points (NaN, -0.0, infinities, values
   beyond the integers, divisors 0 and -1) is never negative, and its power is the
   integer one.

Each value v is read through v * 2147483647 + 1 where the nature matters : an integer
wraps, a real does not. Legs : cpp, ocpp and c, single and double precision, under the
undefined-behaviour sanitizer.
"""

import argparse
from pathlib import Path
import subprocess
import sys
import tempfile

SANITIZE = ["-fsanitize=undefined,float-cast-overflow", "-fno-sanitize-recover=all"]

VARIABLE_DSP = """
w(v) = v * 2147483647 + 1;
n = int(hslider("n", 0, 0, 100, 1));
m = int(hslider("m", 0, -1, 100, 1));
process = pow(2, n) * 2, pow(2, m) * 2, pow(2, attach(n, n : hbargraph("g", 0, 100))) * 2, w(pow(1, m)), pow(0, m);
"""

# (n, m) -> outputs : pow(2, n) * 2 wraps as an integer, pow(2, m) * 2 is a real
VARIABLE_CASES = [(0, -1), (3, 0), (30, 30), (31, 31), (32, 32), (40, 40)]


def wrapped(v):
    v %= 2**32
    return v - 2**32 if v >= 2**31 else v


def c_double(v):
    return "INFINITY" if v == float("inf") else repr(float(v))


def variable_want(n, m):
    real_m = 2.0 * (0.5 if m < 0 else float(wrapped(2**m)))
    zero_m = float("inf") if m < 0 else (1.0 if m == 0 else 0.0)
    return [wrapped(2 * wrapped(2**n)), real_m, wrapped(2 * wrapped(2**n)), 2147483648.0, zero_m]


FUI_DSP = """
n = int(hslider("n", 34, 0, 40, 1));
process = pow(2, n - 3) * 2;
"""

FOLD_DSP = """
w(v) = v * 2147483647 + 1;
x = hslider("x", 1, -10, 10, 0.5);
i = int(nentry("i", 1, -10, 10, 1));
b = int(nentry("b", 0, -10, 10, 1));
k = int(nentry("k", 0, -40, 40, 1));
process = w(pow(3, 0)), pow(2, -1), pow(-2, -1), pow(1, -5), pow(2, -31), pow(3, -7), pow(-7, -3),
          w(pow(x, 0)), w(pow(i, 1.0)), w(pow(i, 0)), pow(b, k);
"""

# the constant powers, folded by the compiler, and the same bases and exponents computed
# with the controls b and k : (base, exponent)
FOLD_CONSTANTS = [(3, 0), (2, -1), (-2, -1), (1, -5), (2, -31), (3, -7), (-7, -3)]

UI_CPP = """
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <map>
#include <string>
#include "faust/dsp/dsp.h"
#include "faust/gui/UI.h"
#include "faust/gui/meta.h"
#include "generated.cpp"
struct RUI : public UI {
    std::map<std::string, FAUSTFLOAT*> z;
    void openTabBox(const char*) override {} void openHorizontalBox(const char*) override {}
    void openVerticalBox(const char*) override {} void closeBox() override {}
    void addButton(const char* l, FAUSTFLOAT* p) override { z[l] = p; }
    void addCheckButton(const char* l, FAUSTFLOAT* p) override { z[l] = p; }
    void addVerticalSlider(const char* l, FAUSTFLOAT* p, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT) override { z[l] = p; }
    void addHorizontalSlider(const char* l, FAUSTFLOAT* p, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT) override { z[l] = p; }
    void addNumEntry(const char* l, FAUSTFLOAT* p, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT) override { z[l] = p; }
    void addHorizontalBargraph(const char*, FAUSTFLOAT*, FAUSTFLOAT, FAUSTFLOAT) override {}
    void addVerticalBargraph(const char*, FAUSTFLOAT*, FAUSTFLOAT, FAUSTFLOAT) override {}
    void addSoundfile(const char*, const char*, Soundfile**) override {}
    void declare(FAUSTFLOAT*, const char*, const char*) override {}
};
// the power of the specification : the product of |k| factors wrapped on 32 bits, an
// integer for k >= 0 (converted here, as the outputs are), its inverse for k < 0
static FAUSTFLOAT power(int x, int k) {
    uint32_t p = 1;
    for (int64_t j = 0; j < (k < 0 ? -int64_t(k) : int64_t(k)); j++) p *= uint32_t(x);
    return k < 0 ? FAUSTFLOAT(1) / FAUSTFLOAT(int32_t(p)) : FAUSTFLOAT(int32_t(p));
}
static int bad = 0, cases = 0;
static void check(const char* what, int j, double got, double want) {
    cases++;
    if (got != want && !(std::isnan(got) && std::isnan(want))) {
        if (bad < 8) printf("%s, output %d : got %.17g, want %.17g\\n", what, j, got, want);
        bad++;
    }
}
"""

VARIABLE_CPP = UI_CPP + """
int main() {
    static const int cs[][2] = {%s};
    static const double want[][5] = {%s};
    for (int c = 0; c < %d; c++) {
        mydsp d; RUI ui; d.init(48000); d.buildUserInterface(&ui);
        *ui.z["n"] = FAUSTFLOAT(cs[c][0]); *ui.z["m"] = FAUSTFLOAT(cs[c][1]);
        FAUSTFLOAT in[1] = {0}, o[5][1]; FAUSTFLOAT* ip[1] = {in}; FAUSTFLOAT* op[5] = {o[0], o[1], o[2], o[3], o[4]};
        d.compute(1, ip, op);
        char what[64]; snprintf(what, sizeof what, "n = %%d, m = %%d", cs[c][0], cs[c][1]);
        for (int j = 0; j < 5; j++) check(what, j, double(o[j][0]), double(FAUSTFLOAT(want[c][j])));
    }
    printf("%%d cases, %%d differ\\n", cases, bad);
    return bad != 0;
}
""" % (", ".join("{%d, %d}" % c for c in VARIABLE_CASES),
       ", ".join("{" + ", ".join(c_double(v) for v in variable_want(*c)) + "}" for c in VARIABLE_CASES),
       len(VARIABLE_CASES))

FUI_CPP = UI_CPP + """
int main() {
    mydsp d; d.init(48000);
    FAUSTFLOAT o[1]; FAUSTFLOAT* op[1] = {o};
    d.compute(1, nullptr, op);
    check("-fui, n = 34", 0, double(o[0]), 0.0);
    printf("%d cases, %d differ\\n", cases, bad);
    return bad != 0;
}
"""

FOLD_CPP = UI_CPP + """
int main() {
    static const int cs[][2] = {%s};
    const int nc = %d;
    for (int c = 0; c < nc; c++) {
        mydsp d; RUI ui; d.init(48000); d.buildUserInterface(&ui);
        *ui.z["b"] = FAUSTFLOAT(cs[c][0]); *ui.z["k"] = FAUSTFLOAT(cs[c][1]);
        FAUSTFLOAT o[11][1]; FAUSTFLOAT* op[11];
        for (int j = 0; j < 11; j++) op[j] = o[j];
        d.compute(1, nullptr, op);
        char what[64]; snprintf(what, sizeof what, "b = %%d, k = %%d", cs[c][0], cs[c][1]);
        // the folded constant equals the power the controls compute
        check(what, 10, double(o[10][0]), double(power(cs[c][0], cs[c][1])));
        if (c > 0) check("folded", c, double(o[c][0]), double(o[10][0]));
        if (c == 0) {
            check("pow(3, 0), an integer", 0, double(o[0][0]), double(FAUSTFLOAT(-2147483648.0)));
            check("pow(x, 0), an integer", 7, double(o[7][0]), double(FAUSTFLOAT(-2147483648.0)));
            check("pow(i, 1.0), a real", 8, double(o[8][0]), double(FAUSTFLOAT(2147483648.0)));
            check("pow(i, 0), an integer", 9, double(o[9][0]), double(FAUSTFLOAT(-2147483648.0)));
        }
    }
    printf("%%d cases, %%d differ\\n", cases, bad);
    return bad != 0;
}
""" % (", ".join("{%d, %d}" % c for c in FOLD_CONSTANTS), len(FOLD_CONSTANTS))

SIGN_DSP = """
s(a) = sqrt(a);
E(a, b) = a > b, int(s(a)), int(max(a, 0.0)), int(min(s(a), s(b))), int(fmod(s(a), b)), int(s(a)) % int(b),
          int(s(a)) & int(b), int(b) & int(s(a)), int(s(a)) >> 3, select2(a > b, int(s(a)), 3),
          int(s(a))@2, int(s(a))', (int(s(a)) : (max ~ _)), int(nentry("n", 3, 0, 10, 1)),
          int(button("g")), int(checkbox("c"));
process(a, b) = E(a, b) : par(i, 16, \\(e).(e >> 16, e & 65535, pow(3, e) * 2147483647 + 1));
"""

SIGN_CPP = UI_CPP + """
int main() {
    const double inf = INFINITY, nan = NAN;
    static const double vs[] = {nan, -1.0, -0.0, 0.0, 0.5, 400.0, 1e10, inf, -inf, -1e10};
    const int nv = 10, n = nv * nv, E = 16;
    mydsp d; d.init(48000);
    FAUSTFLOAT a[n], b[n], o[3 * E][n]; FAUSTFLOAT* ip[2] = {a, b}; FAUSTFLOAT* op[3 * E];
    for (int j = 0; j < 3 * E; j++) op[j] = o[j];
    for (int i = 0; i < n; i++) { a[i] = FAUSTFLOAT(vs[i / nv]); b[i] = FAUSTFLOAT(vs[i % nv]); }
    d.compute(n, ip, op);
    for (int i = 0; i < n; i++) for (int j = 0; j < E; j++) {
        char what[64]; snprintf(what, sizeof what, "a = %g, b = %g, exponent", double(a[i]), double(b[i]));
        // the exponent, from its two halves : negative if its high half is
        double hi = double(o[3 * j][i]), lo = double(o[3 * j + 1][i]);
        check(what, j, hi < 0 ? -1.0 : 0.0, 0.0);
        uint32_t e = uint32_t(int32_t(hi) * 65536 + int32_t(lo)), p = 1, z = 3;
        for (; e; e >>= 1, z *= z) if (e & 1) p *= z;
        check(what, j, double(o[3 * j + 2][i]), double(FAUSTFLOAT(int32_t(p * 2147483647u + 1u))));
    }
    printf("%d cases, %d differ\\n", cases, bad);
    return bad != 0;
}
"""

REFUSED = {"pow(0, -1)": "process = pow(0, -1);",
           "pow(2, -32)": "process = pow(2, -32);",
           "pow(0.0, -1)": "process = pow(0.0, -1);"}


def run(command, work):
    result = subprocess.run(command, cwd=work, capture_output=True, text=True)
    return result


def show(result, command):
    print("+", " ".join(map(str, command)))
    print((result.stdout + result.stderr).strip())


def leg(args, repo, work, dsp, runner, lang, precision, options=[]):
    flt = "float" if precision == "single" else "double"
    (work / "prog.dsp").write_text(dsp)
    (work / "runner.cpp").write_text(runner)
    command = [args.faust, "-lang", lang, "-" + precision, *options, "prog.dsp", "-o", "generated.cpp"]
    result = run(command, work)
    if result.returncode:
        show(result, command)
        return False
    build = [args.cxx, "-std=c++17", "-O1", *SANITIZE, "-DFAUSTFLOAT=" + flt, "-I", repo / "architecture",
             "runner.cpp", "-o", "runner"]
    result = run(build, work)
    if result.returncode:
        show(result, build)
        return False
    result = run([work / "runner"], work)
    lines = (result.stdout + result.stderr).strip().splitlines()
    for line in lines[:-1]:
        print("   ", line)
    print(f"{' '.join([lang, *options]):12} {precision:7} {lines[-1] if lines else 'no output'}")
    return result.returncode == 0


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    parser.add_argument("--cxx", default="g++")
    args = parser.parse_args()
    args.faust = args.faust.resolve()

    ok = True
    with tempfile.TemporaryDirectory(prefix="faust-power-nature-") as temp:
        work = Path(temp)
        for precision in ["single", "double"]:
            print("variable exponents")
            for lang in ["cpp", "ocpp"]:
                for options in [[], ["-norui"]]:
                    ok &= leg(args, repo, work, VARIABLE_DSP, VARIABLE_CPP, lang, precision, options)
            print("-fui writes the program with the values of the controls")
            for lang in ["cpp", "ocpp"]:
                ok &= leg(args, repo, work, FUI_DSP, FUI_CPP, lang, precision, ["-fui"])
            print("folding against execution")
            for lang in ["cpp", "ocpp"]:
                ok &= leg(args, repo, work, FOLD_DSP, FOLD_CPP, lang, precision)
        for precision in ["single", "double"]:
            print("the sign at run time")
            for lang in ["cpp", "ocpp"]:
                ok &= leg(args, repo, work, SIGN_DSP, SIGN_CPP, lang, precision)
        print("certain divisions by 0, refused")
        for name, dsp in REFUSED.items():
            (work / "prog.dsp").write_text(dsp)
            result = run([args.faust, "prog.dsp"], work)
            refused = result.returncode != 0 and "division by 0" in result.stderr
            print(f"{name:12} {'refused' if refused else 'NOT REFUSED : ' + (result.stdout + result.stderr).strip()[:200]}")
            ok &= refused
    print("all legs passed" if ok else "FAILED")
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
