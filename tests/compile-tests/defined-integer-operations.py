#!/usr/bin/env python3
"""The integer operations of the C and C++ backends are defined for every value the
analysis allows.

1. A conversion to an integer of a value that may be NaN gives 0 : int(fmod(1/x, 7)) and
   int(9*sqrt(x)) at x = 0 and x = -1. A NaN operand makes min return the other one :
   int(min(3e10, sqrt(x))) at x = -1 converts 3e10, which saturates.
2. A power of integers whose exponent may be negative is a real (power-nature.py) : the
   product of k factors wrapping on 32 bits, converted, for k >= 0 ; 1 / the wrapped
   product of |k| factors for k < 0, +inf when it is 0. Compared, for 15 bases and 111
   exponents, with the same model computed here.
3. An integer remainder whose divisor may be 0 or -1 : x % 0 gives 0, and
   -2147483648 % -1 its exact value, 0. Compared with the exact remainder otherwise.
5. Extreme and negative constant exponents : pow(x, -2147483648), pow(x, 2147483647) * x
   and pow(x, 65536) * pow(x, 65536) (powers of a product beyond 32 bits, once an assertion
   of the normal form), and pow(x, k) with k = int(hslider(0..0.5)) - 2, a negative
   constant that the constant propagation leaves after the normal form (once an invalid C++
   name, mydsp_faustpower-2_i, and an endless faustpower<-2> in ocpp). Compared with the
   same model, for x in [-1, 3] : the first and the last are real inverses.
4. The selector of -selectn, a real converted to the index of a leaf : a value beyond the
   integers saturates into the first or the last leaf, NaN reaches the leaf its failed
   comparisons give it. Compared with the tree of comparisons, for NaN, both infinities,
   values beyond the integers and each leaf.

Each program runs under the undefined-behaviour sanitizer (with float-cast-overflow,
which GCC leaves out of -fsanitize=undefined) : a conversion out of the integers stops it.
Legs : cpp, ocpp and c (the remainder and the power), ocpp -selectn (the selector),
single and double precision.
"""

import argparse
from pathlib import Path
import re
import subprocess
import sys
import tempfile

SANITIZE = ["-fsanitize=undefined,float-cast-overflow", "-fno-sanitize-recover=all"]

BASES = [0, 1, -1, 2, -2, 3, -3, 7, 25, 46340, 46341, -46341, 65536, 69999, -70000]
EXPONENTS = range(-40, 71)

CAST_DSP = """
x = hslider("x", 0, -1, 1, 0.01);
process = int(fmod(1.0/_, 7.0)), int(sqrt(x) * 9), int(min(3e10, sqrt(x)));
"""

REM_DSP = """
process = int(nentry("x", 0, -2147483648, 1000000, 1)) % int(nentry("k", 1, -2, 7, 1));
"""

REM_DIVIDENDS = [-2147483648, -7, -1, 0, 5, 1000000]
REM_DIVISORS = [-2, -1, 0, 1, 3, 7]

EXPONENT_DSP = """
x = int(nentry("x", 2, -10, 10, 1));
k = int(hslider("a", 0, 0, 0.5, 0.01)) - 2;
process = pow(x, -2147483648), pow(x, 2147483647) * x, pow(x, 65536) * pow(x, 65536), pow(x, k);
"""


def int_power(x, k):
    """The product of |k| factors wrapping on 32 bits : the integer power for k >= 0, the
    denominator of the real one for k < 0"""
    p = pow(x % 2**32, abs(k), 2**32)
    return p - 2**32 if p >= 2**31 else p


def wrapped(v):
    v %= 2**32
    return v - 2**32 if v >= 2**31 else v


EXPONENT_CASES = [(x, [int_power(x, -2147483648), wrapped(int_power(x, 2147483647) * x),
                       wrapped(int_power(x, 65536) * int_power(x, 65536)), int_power(x, -2)])
                  for x in range(-1, 4)]

# a tree whose failed comparisons lead NaN to the second leaf, on the selector a*1e10 + sqrt(b)
SELECTN_DSP = """
g(x) = select2(x >= 2, select2(x < 1, 0.2, 0.1), select2(x >= 3, 0.3, 0.4));
process = _, _ : *(1e10), sqrt : + : g;
"""

POW_DSP = """
process = pow(int(nentry("b", 0, -70000, 70000, 1)), int(nentry("k", 0, -40, 70, 1)));
"""

UI_CPP = """
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
"""

CAST_CPP = UI_CPP + """
int main() {
    int bad = 0;
    // the largest integer the conversion saturates to : 2^31 - 128 in single precision
    const FAUSTFLOAT high = FAUSTFLOAT(sizeof(FAUSTFLOAT) == 4 ? 2147483520 : 2147483647);
    for (double x : {0.0, -1.0}) {
        mydsp d; RUI ui; d.init(48000); d.buildUserInterface(&ui);
        *ui.z["x"] = FAUSTFLOAT(x);
        FAUSTFLOAT in[1] = {FAUSTFLOAT(0)}, o0[1], o1[1], o2[1];
        FAUSTFLOAT* ip[1] = {in}; FAUSTFLOAT* op[3] = {o0, o1, o2};
        d.compute(1, ip, op);
        FAUSTFLOAT want = (x < 0) ? high : 0;
        if (o0[0] != 0 || o1[0] != 0 || o2[0] != want) { printf("x = %g : got %g %g %g, want 0 0 %g\\n", x, double(o0[0]), double(o1[0]), double(o2[0]), double(want)); bad++; }
    }
    printf("2 cases, %d differ\\n", bad);
    return bad != 0;
}
"""

MODEL = """
static FAUSTFLOAT model(int x, int k) {
    unsigned int p = 1; long long n = (k < 0) ? -(long long)k : k;
    for (long long i = 0; i < n; i++) p *= (unsigned int)x;
    return (k < 0) ? (FAUSTFLOAT)1 / (FAUSTFLOAT)(int)p : (FAUSTFLOAT)(int)p;
}
"""

LOOP_HEAD = """
    static const int bases[] = {%s};
    long bad = 0, n = 0;
    for (int i = 0; i < %d; i++) for (int k = %d; k <= %d; k++) {
""" % (", ".join(map(str, BASES)), len(BASES), EXPONENTS[0], EXPONENTS[-1])

LOOP_TAIL = """
        n++;
        if (o[0] != model(bases[i], k)) { if (bad < 5) printf("b = %d, k = %d : got %.17g\\n", bases[i], k, (double)o[0]); bad++; }
    }
    printf("%ld cases, %ld differ\\n", n, bad);
    return bad != 0;
}
"""

POW_CPP = UI_CPP + MODEL + "int main() {" + LOOP_HEAD + """
        mydsp d; RUI ui; d.init(48000); d.buildUserInterface(&ui);
        *ui.z["b"] = FAUSTFLOAT(bases[i]); *ui.z["k"] = FAUSTFLOAT(k);
        FAUSTFLOAT o[1]; FAUSTFLOAT* op[1] = {o}; d.compute(1, nullptr, op);
""" + LOOP_TAIL

POW_C = """
#include <stdio.h>
#include <stdlib.h>
#include "faust/gui/CInterface.h"
#include "generated.c"
""" + MODEL + "int main() {" + LOOP_HEAD + """
        mydsp* d = newmydsp(); initmydsp(d, 48000);
        d->FIELD_b = bases[i]; d->FIELD_k = k;
        FAUSTFLOAT o[1]; FAUSTFLOAT* op[1] = {o}; computemydsp(d, 1, NULL, op);
        deletemydsp(d);
""" + LOOP_TAIL


REM_CPP = UI_CPP + """
int main() {
    static const long long xs[] = {%s};
    static const long long ks[] = {%s};
    long bad = 0, n = 0;
    for (long long x : xs) for (long long k : ks) {
        mydsp d; RUI ui; d.init(48000); d.buildUserInterface(&ui);
        *ui.z["x"] = FAUSTFLOAT(x); *ui.z["k"] = FAUSTFLOAT(k);
        FAUSTFLOAT o[1]; FAUSTFLOAT* op[1] = {o}; d.compute(1, nullptr, op);
        long long want = (k == 0) ? 0 : x %% k;
        n++;
        if (o[0] != (FAUSTFLOAT)want) { printf("x = %%lld, k = %%lld : got %%.17g\\n", x, k, (double)o[0]); bad++; }
    }
    printf("%%ld cases, %%ld differ\\n", n, bad);
    return bad != 0;
}
""" % (", ".join(map(str, REM_DIVIDENDS)), ", ".join(map(str, REM_DIVISORS)))


REM_C = """
#include <stdio.h>
#include <stdlib.h>
#include "faust/gui/CInterface.h"
#include "generated.c"
int main() {
    static const long long xs[] = {%s};
    static const long long ks[] = {%s};
    long bad = 0, n = 0;
    for (int i = 0; i < %d; i++) for (int j = 0; j < %d; j++) {
        mydsp* d = newmydsp(); initmydsp(d, 48000);
        d->FIELD_x = xs[i]; d->FIELD_k = ks[j];
        FAUSTFLOAT o[1]; FAUSTFLOAT* op[1] = {o}; computemydsp(d, 1, NULL, op);
        deletemydsp(d);
        long long want = (ks[j] == 0) ? 0 : xs[i] %% ks[j];
        n++;
        if (o[0] != (FAUSTFLOAT)want) { printf("x = %%lld, k = %%lld : got %%.17g\\n", xs[i], ks[j], (double)o[0]); bad++; }
    }
    printf("%%ld cases, %%ld differ\\n", n, bad);
    return bad != 0;
}
""" % (", ".join(map(str, REM_DIVIDENDS)), ", ".join(map(str, REM_DIVISORS)), len(REM_DIVIDENDS), len(REM_DIVISORS))


SELECTN_CPP = "#include <cmath>\n" + UI_CPP + """
int main() {
    static const double as[] = {0, 0, 0, 0, 0, 0, 0, 1, -1, INFINITY, -INFINITY};
    static const double bs[] = {-1, 0, 1, 2.25, 4, 9, 16, 0, 0, 0, 0};
    const int n = 11;
    mydsp d; d.init(48000);
    FAUSTFLOAT a[n], b[n], o[n]; FAUSTFLOAT* ip[2] = {a, b}; FAUSTFLOAT* op[1] = {o};
    for (int i = 0; i < n; i++) { a[i] = FAUSTFLOAT(as[i]); b[i] = FAUSTFLOAT(bs[i]); }
    d.compute(n, ip, op);
    int bad = 0;
    for (int i = 0; i < n; i++) {
        FAUSTFLOAT x = a[i] * FAUSTFLOAT(1e10) + std::sqrt(b[i]);
        double want = (x >= 2) ? ((x >= 3) ? 0.4 : 0.3) : ((x < 1) ? 0.1 : 0.2);
        if (o[i] != FAUSTFLOAT(want)) { printf("a = %g, b = %g : got %g, want %g\\n", as[i], bs[i], double(o[i]), want); bad++; }
    }
    printf("%d cases, %d differ\\n", n, bad);
    return bad != 0;
}
"""


EXPONENT_CPP = UI_CPP + """
int main() {
    static const int xs[] = {%s};
    static const long long want[][4] = {%s};
    // the real powers of a negative exponent : the inverse of the wrapped product
    static const bool inverse[4] = {true, false, false, true};
    int bad = 0, n = 0;
    for (int i = 0; i < %d; i++) {
        mydsp d; RUI ui; d.init(48000); d.buildUserInterface(&ui);
        *ui.z["x"] = FAUSTFLOAT(xs[i]);
        FAUSTFLOAT o[4][1]; FAUSTFLOAT* op[4] = {o[0], o[1], o[2], o[3]};
        d.compute(1, nullptr, op);
        for (int j = 0; j < 4; j++) {
            n++;
            FAUSTFLOAT w = inverse[j] ? FAUSTFLOAT(1) / FAUSTFLOAT(want[i][j]) : FAUSTFLOAT(want[i][j]);
            if (o[j][0] != w) { printf("x = %%d, output %%d : got %%.17g, want %%.17g\\n", xs[i], j, double(o[j][0]), double(w)); bad++; }
        }
    }
    printf("%%d cases, %%d differ\\n", n, bad);
    return bad != 0;
}
""" % (", ".join(str(x) for x, _ in EXPONENT_CASES),
       ", ".join("{" + ", ".join(str(v) for v in w) + "}" for _, w in EXPONENT_CASES), len(EXPONENT_CASES))


def run(command, work):
    result = subprocess.run(command, cwd=work, capture_output=True, text=True)
    if result.returncode != 0:
        print("+", " ".join(map(str, command)))
        print((result.stdout + result.stderr).strip())
    return result


def leg(args, repo, work, dsp, runner, lang, precision, options=[], marker=None):
    flt = "float" if precision == "single" else "double"
    (work / "prog.dsp").write_text(dsp)
    is_c = lang == "c"
    generated = work / ("generated.c" if is_c else "generated.cpp")
    source = work / ("runner.c" if is_c else "runner.cpp")
    source.write_text(runner)
    if run([args.faust, "-lang", lang, "-" + precision, *options, "prog.dsp", "-o", generated], work).returncode:
        return False
    if marker and marker not in generated.read_text():
        print(f"{lang:5} {precision:7} the generated code has no {marker} : -selectn does not take the tree")
        return False
    compiler = [args.cc, "-std=c11"] if is_c else [args.cxx, "-std=c++17"]
    # the C runner sets the controls through their fields, named in the order the code
    # reads them : FIELD_<label>, found from the user interface the code builds
    fields = ["-DFIELD_%s=%s" % (label, field) for label, field in
              re.findall(r'add\w+\(ui_interface->uiInterface, "(\w+)", &dsp->(\w+)', generated.read_text())]
    build = compiler + ["-O1", *SANITIZE, "-DFAUSTFLOAT=" + flt, *fields, "-I", repo / "architecture",
                        source, "-o", work / "runner"] + (["-lm"] if is_c else [])
    if run(build, work).returncode:
        return False
    result = run([work / "runner"], work)
    lines = (result.stdout + result.stderr).strip().splitlines()
    print(f"{' '.join([lang, *options]):5} {precision:7} {lines[-1] if lines else 'no output'}")
    return result.returncode == 0


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    parser.add_argument("--cxx", default="g++")
    parser.add_argument("--cc", default="gcc")
    args = parser.parse_args()
    args.faust = args.faust.resolve()
    print(subprocess.run([args.faust, "--version"], capture_output=True, text=True).stdout.splitlines()[1])

    ok = True
    with tempfile.TemporaryDirectory(prefix="faust-defined-int-") as temp:
        work = Path(temp)
        for precision in ["single", "double"]:
            print("conversion of a value that may be NaN")
            for lang in ["cpp", "ocpp"]:
                ok &= leg(args, repo, work, CAST_DSP, CAST_CPP, lang, precision)
            print("integer remainder by a divisor that may be 0 or -1")
            for lang in ["cpp", "ocpp"]:
                ok &= leg(args, repo, work, REM_DSP, REM_CPP, lang, precision)
            ok &= leg(args, repo, work, REM_DSP, REM_C, "c", precision)
            print("integer power of variable exponent")
            for lang in ["cpp", "ocpp"]:
                ok &= leg(args, repo, work, POW_DSP, POW_CPP, lang, precision)
            ok &= leg(args, repo, work, POW_DSP, POW_C, "c", precision)
            print("extreme and negative constant exponents")
            for lang in ["cpp", "ocpp"]:
                ok &= leg(args, repo, work, EXPONENT_DSP, EXPONENT_CPP, lang, precision)
            print("selector of -selectn that may be NaN or beyond the integers")
            ok &= leg(args, repo, work, SELECTN_DSP, SELECTN_CPP, "ocpp", precision, ["-selectn"], "fSel")
    print("all legs passed" if ok else "FAILED")
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
