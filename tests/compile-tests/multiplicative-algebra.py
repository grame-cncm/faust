#!/usr/bin/env python3
"""The multiplicative algebra, before the natures.

Products, quotients and powers of an integer exponent are simplified in exact algebra
before the natures are known, their results literals typed by their form : x/x is the
integer 1, (n*4)/(n*2) is 2, n*4/2 is 2*n. A real literal keeps its nature : (n*1.0)/n is
1.0. The algebra does not create a product of integer factors the program did not write :
(0.5*r)*(0.5*r), r an integer that wraps (a noise generator), stays a real product, not
0.25 * r^2 with r^2 an integer square that would wrap.

Each value is read through * 2147483647 + 1, which wraps when it is an integer :
an integer 1 gives -2147483648, a real 1.0 gives 2147483648.0. Legs : cpp and ocpp, single
and double precision, under the undefined-behaviour sanitizer.
"""

import argparse
from pathlib import Path
import subprocess
import sys
import tempfile

SANITIZE = ["-fsanitize=undefined,float-cast-overflow", "-fno-sanitize-recover=all"]

DSP = """
n = int(nentry("n", 1, -10, 10, 1));
x = hslider("x", 1.5, -10, 10, 0.1);
r = +(12345) ~ *(1103515245);
process = n/n * 2147483647 + 1, x/x * 2147483647 + 1, (n*4)/(n*2) * 2147483647 + 1,
          n*4/2 * 2147483647 + 1, (n*1.0)/n * 2147483647 + 1, (0.5*r) * (0.5*r);
"""

RUNNER = """
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
static int32_t wrap(int64_t v) { return int32_t(uint32_t(uint64_t(v))); }
int main() {
    const int K = 8;
    int bad = 0, cases = 0;
    for (int n : {1, 2, -3, 7}) {
        mydsp d; RUI ui; d.init(48000); d.buildUserInterface(&ui);
        *ui.z["n"] = FAUSTFLOAT(n);
        FAUSTFLOAT o[6][K]; FAUSTFLOAT* op[6] = {o[0], o[1], o[2], o[3], o[4], o[5]};
        d.compute(K, nullptr, op);
        uint32_t r = 0;
        for (int i = 0; i < K; i++) {
            r = 12345u + 1103515245u * r;
            double rr = double(int32_t(r)) * 0.5;
            double want[6] = {double(INT32_MIN), double(INT32_MIN), -1.0,
                              double(wrap(int64_t(2 * n) * 2147483647 + 1)), 2147483648.0, rr * rr};
            for (int j = 0; j < 6; j++) {
                cases++;
                double got = double(o[j][i]), w = double(FAUSTFLOAT(want[j]));
                double tol = (j == 5) ? std::fabs(w) * (sizeof(FAUSTFLOAT) == 4 ? 1e-6 : 1e-12) : 0.0;
                if (std::fabs(got - w) > tol) {
                    if (bad < 6) printf("n = %d, sample %d, output %d : got %.17g, want %.17g\\n", n, i, j, got, w);
                    bad++;
                }
            }
        }
    }
    printf("%d cases, %d differ\\n", cases, bad);
    return bad != 0;
}
"""


def run(command, work):
    result = subprocess.run(command, cwd=work, capture_output=True, text=True)
    if result.returncode != 0:
        print("+", " ".join(map(str, command)))
        print((result.stdout + result.stderr).strip())
    return result


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    parser.add_argument("--cxx", default="g++")
    args = parser.parse_args()
    args.faust = args.faust.resolve()

    ok = True
    with tempfile.TemporaryDirectory(prefix="faust-multiplicative-") as temp:
        work = Path(temp)
        (work / "prog.dsp").write_text(DSP)
        (work / "runner.cpp").write_text(RUNNER)
        for precision in ["single", "double"]:
            flt = "float" if precision == "single" else "double"
            for lang in ["cpp", "ocpp"]:
                if run([args.faust, "-lang", lang, "-" + precision, "prog.dsp", "-o", "generated.cpp"], work).returncode:
                    ok = False
                    continue
                build = [args.cxx, "-std=c++17", "-O1", *SANITIZE, "-DFAUSTFLOAT=" + flt, "-I",
                         repo / "architecture", "runner.cpp", "-o", "runner"]
                if run(build, work).returncode:
                    ok = False
                    continue
                result = run([work / "runner"], work)
                lines = (result.stdout + result.stderr).strip().splitlines()
                print(f"{lang:5} {precision:7} {lines[-1] if lines else 'no output'}")
                ok &= result.returncode == 0
    print("all legs passed" if ok else "FAILED")
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
