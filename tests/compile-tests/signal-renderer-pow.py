#!/usr/bin/env python3
"""The power of integers in the interpreter of the signals (signalRenderer).

The interpreter computes pow(x, k) of two integers as the code does : the product of k
factors wrapping on 32 bits for k >= 0. It used std::pow in double then a conversion to
int, undefined beyond the integers (INT_MIN on x86 for pow(3, 21), whose wrapped product
is 1870418611) and inexact beyond 2^53. A power of integers whose exponent may be negative
is real (power-nature.py) : the wrapped product converted, or its inverse.

The interpreter is part of libfaust (createSignalDSPFactoryFromString) : the runner is
linked with the static library of the same build as faust, build/lib/libfaust.a by default
(--libfaust). Compared, for 15 bases and the exponents of [0, 70] (an integer power) and
[-40, 70] (a real power), with the same model computed here.
"""

import argparse
from pathlib import Path
import subprocess
import sys
import tempfile

BASES = [0, 1, -1, 2, -2, 3, -3, 7, 25, 46340, 46341, -46341, 65536, 69999, -70000]

DSP = """
b = int(nentry("b", 0, -70000, 70000, 1));
process = pow(b, int(nentry("k", 0, 0, 70, 1))), pow(b, int(nentry("m", 0, -40, 70, 1)));
"""

RUNNER = """
#include <cstdint>
#include <cstdio>
#include <map>
#include <string>
#include "faust/dsp/signal-dsp.h"
#include "faust/gui/UI.h"
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
// the product of |k| factors wrapped on 32 bits : the integer power for k >= 0, the
// denominator of the real one for k < 0
static int32_t wrapped(int x, int k) {
    uint32_t p = 1;
    for (int64_t j = 0; j < (k < 0 ? -int64_t(k) : int64_t(k)); j++) p *= uint32_t(x);
    return int32_t(p);
}
int main(int argc, char* argv[]) {
    static const int bases[] = {%s};
    std::string error;
    const char* options[] = {"-double"};
    signal_dsp_factory* factory = createSignalDSPFactoryFromString("pow", argv[1], 1, options, error);
    if (!factory) { printf("no factory : %%s\\n", error.c_str()); return 1; }
    long n = 0, bad = 0;
    for (int b : bases) for (int k = -40; k <= 70; k++) {
        dsp* d = factory->createDSPInstance(); d->init(48000);
        RUI ui; d->buildUserInterface(&ui);
        *ui.z["b"] = FAUSTFLOAT(b); *ui.z["k"] = FAUSTFLOAT(k < 0 ? 0 : k); *ui.z["m"] = FAUSTFLOAT(k);
        FAUSTFLOAT o[2][1]; FAUSTFLOAT* op[2] = {o[0], o[1]};
        d->compute(1, nullptr, op);
        delete d;
        double want[2] = {double(wrapped(b, k < 0 ? 0 : k)),
                          k < 0 ? 1.0 / double(wrapped(b, k)) : double(wrapped(b, k))};
        for (int j = 0; j < 2; j++) {
            n++;
            if (double(o[j][0]) != want[j]) {
                if (bad < 6) printf("b = %%d, k = %%d, output %%d : got %%.17g, want %%.17g\\n", b, k, j, double(o[j][0]), want[j]);
                bad++;
            }
        }
    }
    deleteSignalDSPFactory(factory);
    printf("%%ld cases, %%ld differ\\n", n, bad);
    return bad != 0;
}
""" % ", ".join(map(str, BASES))


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
    parser.add_argument("--libfaust", type=Path, default=repo / "build/lib/libfaust.a")
    parser.add_argument("--cxx", default="g++")
    args = parser.parse_args()
    if not args.libfaust.is_file():
        print(f"NOT A VERDICT : no {args.libfaust} (build the static library, or pass --libfaust)")
        sys.exit(2)

    with tempfile.TemporaryDirectory(prefix="faust-signal-renderer-pow-") as temp:
        work = Path(temp)
        (work / "runner.cpp").write_text(RUNNER)
        build = [args.cxx, "-std=c++17", "-O1", "-DFAUSTFLOAT=double", "-I", repo / "architecture",
                 "runner.cpp", args.libfaust.resolve(), "-lpthread", "-ldl", "-o", "runner"]
        if run(build, work).returncode:
            print("FAILED")
            sys.exit(1)
        result = run([work / "runner", DSP], work)
        lines = (result.stdout + result.stderr).strip().splitlines()
        for line in lines[:-1]:
            print("   ", line)
        print(f"signalRenderer double {lines[-1] if lines else 'no output'}")
    ok = result.returncode == 0
    print("all legs passed" if ok else "FAILED")
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
