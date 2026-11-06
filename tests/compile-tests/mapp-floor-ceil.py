#!/usr/bin/env python3
"""Check floor and ceil under -mapp.

-mapp rewrote floor and ceil as signals (`r = T(int(n)); (r == n) ? n : ...`)
before typing: the type of the rewriting joins both branches of a select2, so
`int(floor(sr/2)) % 2` was found possibly negative and rejected as a delay,
while the default compilation accepts it (impulse test constant.dsp). The
primitives now keep their own type and are rewritten by the code generation,
only when int(n) is exact (n within the int range); libm is called otherwise.

This checks that such delays compile with -mapp, that the generated code uses
the rewriting for a bounded argument and libm for an unbounded one, and that
the rewriting gives the values of std::floor and std::ceil, in float and double.
"""
import argparse
from pathlib import Path
import re
import subprocess
import tempfile

SR = "sr = min(192000.0, max(1.0, fconstant(int fSamplingFreq, <math.h>)));\n"
DELAYS = {
    "floor": SR + "process = _ @ (1*(int(floor(sr/1))%2) + 2*(int(floor(sr/2))%2));\n",
    "ceil": SR + "process = _ @ (int(0 - ceil(0 - sr/2)) % 2);\n",
}
BOUNDED = "process = max(-1e6) : min(1e6) <: floor, ceil;\n"
UNBOUNDED = "process = *(1e10) <: floor, ceil;\n"

RUNNER = r"""
#include <cmath>
#include <cstdio>
#include <random>
#include <vector>
#include "faust/gui/meta.h"
#include "faust/gui/UI.h"
#include "faust/dsp/dsp.h"
#include "mapp.h"

int main()
{
    std::vector<FAUSTFLOAT> in;
    for (int i = -4000; i <= 4000; i++) in.push_back(FAUSTFLOAT(i * 0.25));
    for (double v : {0.0, -0.0, 1e-30, -1e-30, 1e6, -1e6, 999999.5, -999999.5}) in.push_back(FAUSTFLOAT(v));
    std::mt19937 g(1);
    std::uniform_real_distribution<double> wide(-1e6, 1e6), narrow(-3, 3);
    while (in.size() < 200000) in.push_back(FAUSTFLOAT(in.size() % 2 ? wide(g) : narrow(g)));
    const int n = int(in.size());
    std::vector<FAUSTFLOAT> f(n), c(n);
    mapp d;
    d.init(48000);
    FAUSTFLOAT* ins[] = {in.data()};
    FAUSTFLOAT* outs[] = {f.data(), c.data()};
    d.compute(n, ins, outs);
    long bad = 0;
    for (int i = 0; i < n; i++) {
        FAUSTFLOAT x = std::fmin(std::fmax(in[i], FAUSTFLOAT(-1e6)), FAUSTFLOAT(1e6));
        bad += (f[i] != std::floor(x)) || (c[i] != std::ceil(x));
    }
    std::printf("%d inputs, %ld mismatches\n", n, bad);
    return bad != 0;
}
"""


def run(command, work):
    print("+", " ".join(map(str, command)), flush=True)
    return subprocess.run(command, cwd=work, check=True, capture_output=True, text=True)


def libm_calls(code):
    return len(re.findall(r"\b(?:std::)?(?:floor|ceil)[fl]?\(", code))


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    parser.add_argument("--cxx", default="c++")
    args = parser.parse_args()
    faust = args.faust.resolve()
    print(run([faust, "--version"], repo).stdout, flush=True)
    with tempfile.TemporaryDirectory(prefix="faust-mapp-floor-ceil-") as temp:
        work = Path(temp)
        for name, code in DELAYS.items():
            (work / f"{name}.dsp").write_text(code)
            for lang in ["cpp", "ocpp", "c"]:
                run([faust, "-lang", lang, "-double", "-mapp", f"{name}.dsp", "-o", f"{name}.out"], work)
                print(f"PASS {name} delay compiles with -lang {lang} -mapp", flush=True)

        (work / "bounded.dsp").write_text(BOUNDED)
        (work / "unbounded.dsp").write_text(UNBOUNDED)
        for name, expected in [("bounded", 0), ("unbounded", 2)]:
            for lang in ["cpp", "ocpp"]:
                run([faust, "-lang", lang, "-double", "-mapp", f"{name}.dsp", "-o", f"{name}.cpp"], work)
                calls = libm_calls((work / f"{name}.cpp").read_text())
                assert calls == expected, (name, lang, calls)
                print(f"PASS {name} argument, -lang {lang}: {calls} libm calls", flush=True)

        (work / "runner.cpp").write_text(RUNNER)
        for precision, faustfloat in [("single", "float"), ("double", "double")]:
            run([faust, "-lang", "cpp", "-" + precision, "-mapp", "-cn", "mapp", "bounded.dsp",
                 "-o", "mapp.h"], work)
            run([args.cxx, "-std=c++17", "-O2", f"-DFAUSTFLOAT={faustfloat}",
                 "-I", repo / "architecture", "runner.cpp", "-o", "runner"], work)
            print(f"PASS {precision}: " + run([work / "runner"], work).stdout.strip(), flush=True)


if __name__ == "__main__":
    main()
