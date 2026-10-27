#!/usr/bin/env python3
"""The integer operations of the C and C++ backends are defined for every value the
analysis allows.

1. A conversion to an integer of a value that may be NaN gives 0 : int(fmod(1/x, 7)) and
   int(9*sqrt(x)) at x = 0 and x = -1.
2. An integer power of variable exponent is the integer power of the analysis : x^k by
   products wrapping on 32 bits ; for k < 0, 1/x^k truncated toward 0, and 0 for x = 0.
   Compared, for 15 bases and 111 exponents, with the same model computed here.
3. An integer remainder whose divisor may be 0 or -1 : x % 0 gives 0, and
   -2147483648 % -1 its exact value, 0. Compared with the exact remainder otherwise.

Each program runs under the undefined-behaviour sanitizer (with float-cast-overflow,
which GCC leaves out of -fsanitize=undefined) : a conversion out of the integers stops it.
Legs : cpp, ocpp and c (the remainder and the power), single and double precision.
"""

import argparse
from pathlib import Path
import subprocess
import sys
import tempfile

SANITIZE = ["-fsanitize=undefined,float-cast-overflow", "-fno-sanitize-recover=all"]

BASES = [0, 1, -1, 2, -2, 3, -3, 7, 25, 46340, 46341, -46341, 65536, 69999, -70000]
EXPONENTS = range(-40, 71)

CAST_DSP = """
process = int(fmod(1.0/_, 7.0)), int(sqrt(hslider("x", 0, -1, 1, 0.01)) * 9);
"""

REM_DSP = """
process = int(nentry("x", 0, -2147483648, 1000000, 1)) % int(nentry("k", 1, -2, 7, 1));
"""

REM_DIVIDENDS = [-2147483648, -7, -1, 0, 5, 1000000]
REM_DIVISORS = [-2, -1, 0, 1, 3, 7]

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
    for (double x : {0.0, -1.0}) {
        mydsp d; RUI ui; d.init(48000); d.buildUserInterface(&ui);
        *ui.z["x"] = FAUSTFLOAT(x);
        FAUSTFLOAT in[1] = {FAUSTFLOAT(0)}, o0[1], o1[1];
        FAUSTFLOAT* ip[1] = {in}; FAUSTFLOAT* op[2] = {o0, o1};
        d.compute(1, ip, op);
        if (o0[0] != 0 || o1[0] != 0) { printf("x = %g : got %g %g, want 0 0\\n", x, double(o0[0]), double(o1[0])); bad++; }
    }
    printf("2 cases, %d differ\\n", bad);
    return bad != 0;
}
"""

MODEL = """
static int model(int x, int k) {
    if (k < 0) return (x == 1) ? 1 : (x == -1) ? ((k & 1) ? -1 : 1) : 0;
    unsigned int p = 1; for (int i = 0; i < k; i++) p *= (unsigned int)x; return (int)p;
}
"""

LOOP_HEAD = """
    static const int bases[] = {%s};
    long bad = 0, n = 0;
    for (int i = 0; i < %d; i++) for (int k = %d; k <= %d; k++) {
""" % (", ".join(map(str, BASES)), len(BASES), EXPONENTS[0], EXPONENTS[-1])

LOOP_TAIL = """
        n++;
        if (o[0] != (FAUSTFLOAT)model(bases[i], k)) { if (bad < 5) printf("b = %d, k = %d : got %.17g\\n", bases[i], k, (double)o[0]); bad++; }
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
        d->fEntry0 = bases[i]; d->fEntry1 = k;
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
        d->fEntry0 = xs[i]; d->fEntry1 = ks[j];
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


def run(command, work):
    result = subprocess.run(command, cwd=work, capture_output=True, text=True)
    if result.returncode != 0:
        print("+", " ".join(map(str, command)))
        print((result.stdout + result.stderr).strip())
    return result


def leg(args, repo, work, dsp, runner, lang, precision):
    flt = "float" if precision == "single" else "double"
    (work / "prog.dsp").write_text(dsp)
    is_c = lang == "c"
    generated = work / ("generated.c" if is_c else "generated.cpp")
    source = work / ("runner.c" if is_c else "runner.cpp")
    source.write_text(runner)
    if run([args.faust, "-lang", lang, "-" + precision, "prog.dsp", "-o", generated], work).returncode:
        return False
    compiler = [args.cc, "-std=c11"] if is_c else [args.cxx, "-std=c++17"]
    build = compiler + ["-O1", *SANITIZE, "-DFAUSTFLOAT=" + flt, "-I", repo / "architecture",
                        source, "-o", work / "runner"] + (["-lm"] if is_c else [])
    if run(build, work).returncode:
        return False
    result = run([work / "runner"], work)
    lines = (result.stdout + result.stderr).strip().splitlines()
    print(f"{lang:5} {precision:7} {lines[-1] if lines else 'no output'}")
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
    print("all legs passed" if ok else "FAILED")
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
