#!/usr/bin/env python3
"""Compile and execute non-finite constants (C++ and Julia).

An infinite constant was printed as INFINITY whatever its sign, so the C++
code computed +inf where the program has -inf. The ocpp backend tested the
constant in double precision: in -single, 1e38 * 10 (folded in double, a
finite 1e39) became "inf.0f", which does not compile. The Julia backend printed
it the same way, but INFINITY is the C macro, undefined in Julia: the
generated code did not load (UndefVarError: INFINITY not defined). The
Julia literals are Inf32 and NaN32 for Float32, Inf and NaN for Float64.

The program outputs +inf, -inf and 1e38 * 10 (+inf in single precision) at
its first sample, and 0 after; it is generated in single and double
precision for each backend and run.
"""
import argparse
from pathlib import Path
import subprocess
import tempfile

SOURCE = """
ma = library("maths.lib");
I = ma.MAX * 2;                  // +inf, folded to a constant
first = (+(1) ~ _) == 1;         // 1 at the first sample only
process = select2(first, 0.0, I), select2(first, 0.0, 0 - I), select2(first, 0.0, 1e38 * 10.0);
"""

CPP_RUNNER = """
#include <cmath>
#include <cstdio>
#include <faust/dsp/dsp.h>
#include <faust/gui/meta.h>
#include <faust/gui/UI.h>
#include "generated.cpp"

int main() {
    FAUSTFLOAT out[3][2];
    FAUSTFLOAT* outputs[3] = {out[0], out[1], out[2]};
    mydsp dsp;
    dsp.init(44100);
    dsp.compute(2, nullptr, outputs);
    bool ok = std::isinf(out[0][0]) && out[0][0] > 0 && std::isinf(out[1][0]) && out[1][0] < 0
              && out[0][1] == 0 && out[1][1] == 0 && out[2][1] == 0
              && (sizeof(FAUSTFLOAT) == 4 ? (std::isinf(out[2][0]) && out[2][0] > 0) : out[2][0] == 1e39);
    if (!ok) std::printf("    got %g %g %g, then %g %g %g\\n", double(out[0][0]), double(out[1][0]),
                         double(out[2][0]), double(out[0][1]), double(out[1][1]), double(out[2][1]));
    return ok ? 0 : 1;
}
"""

RUNNER = """
abstract type dsp end
abstract type FMeta end
abstract type UI end
const FAUSTFLOAT = SAMPLE
include("mydsp.jl")
d = mydsp{SAMPLE}()
init!(d, Int32(44100))
output = zeros(SAMPLE, 2, 3)
compute!(d, Int32(2), zeros(SAMPLE, 2, 0), output)
@assert output[1, 1] == SAMPLE(Inf) output
@assert output[1, 2] == SAMPLE(-Inf) output
@assert output[1, 3] == (SAMPLE == Float32 ? Inf32 : 1e39) output
@assert all(iszero, output[2, :]) output
"""


def run(command, work):
    print("+", " ".join(map(str, command)), flush=True)
    subprocess.run(command, cwd=work, check=True)


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    parser.add_argument("--julia", default="julia")
    parser.add_argument("--cxx", default="c++")
    parser.add_argument("--backends", nargs="+", choices=["cpp", "ocpp", "julia"],
                        default=["cpp", "ocpp", "julia"])
    args = parser.parse_args()
    faust = args.faust.resolve()
    run([faust, "--version"], repo)
    for lang in [b for b in args.backends if b in ("cpp", "ocpp")]:
        for precision in ["single", "double"]:
            with tempfile.TemporaryDirectory(prefix="faust-nonfinite-cpp-") as temp:
                work = Path(temp)
                (work / "nonfinite.dsp").write_text(SOURCE)
                run([faust, "-I", repo / "libraries", "-lang", lang, "-" + precision,
                     work / "nonfinite.dsp", "-o", work / "generated.cpp"], work)
                (work / "runner.cpp").write_text(CPP_RUNNER)
                define = ["-DFAUSTFLOAT=double"] if precision == "double" else []
                run([args.cxx, "-std=c++17", "-O1", *define, "-I", repo / "architecture",
                     "runner.cpp", "-o", "runner"], work)
                run([work / "runner"], work)
                print(f"PASS {lang} {precision}: non-finite constants", flush=True)
    if "julia" not in args.backends:
        return
    run([args.julia, "--version"], repo)
    for precision in ["single", "double"]:
        with tempfile.TemporaryDirectory(prefix="faust-nonfinite-julia-") as temp:
            work = Path(temp)
            (work / "nonfinite.dsp").write_text(SOURCE)
            run([faust, "-I", repo / "libraries", "-lang", "julia", "-" + precision,
                 work / "nonfinite.dsp", "-o", work / "mydsp.jl"], work)
            sample = "Float32" if precision == "single" else "Float64"
            (work / "runner.jl").write_text(RUNNER.replace("SAMPLE", sample))
            run([args.julia, "--startup-file=no", "runner.jl"], work)
            print(f"PASS julia {precision}: non-finite constants", flush=True)


if __name__ == "__main__":
    main()
