#!/usr/bin/env python3
"""Compile and execute non-finite constants (Julia).

The Julia backend printed an infinite constant as INFINITY, the C macro,
which is undefined in Julia: the generated code did not load
(UndefVarError: INFINITY not defined), and the sign of -inf was lost. The
Julia literals are Inf32 and NaN32 for Float32, Inf and NaN for Float64.

The program outputs +inf and -inf at its first sample, and 0 after; it is
generated in single and double precision, loaded and run in Julia.
"""
import argparse
from pathlib import Path
import subprocess
import tempfile

SOURCE = """
ma = library("maths.lib");
I = ma.MAX * 2;                  // +inf, folded to a constant
first = (+(1) ~ _) == 1;         // 1 at the first sample only
process = select2(first, 0.0, I), select2(first, 0.0, 0 - I);
"""

RUNNER = """
abstract type dsp end
abstract type FMeta end
abstract type UI end
const FAUSTFLOAT = SAMPLE
include("mydsp.jl")
d = mydsp{SAMPLE}()
init!(d, Int32(44100))
output = zeros(SAMPLE, 2, 2)
compute!(d, Int32(2), zeros(SAMPLE, 2, 0), output)
@assert output[1, 1] == SAMPLE(Inf) output
@assert output[1, 2] == SAMPLE(-Inf) output
@assert iszero(output[2, 1]) && iszero(output[2, 2]) output
"""


def run(command, work):
    print("+", " ".join(map(str, command)), flush=True)
    subprocess.run(command, cwd=work, check=True)


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    parser.add_argument("--julia", default="julia")
    args = parser.parse_args()
    faust = args.faust.resolve()
    run([faust, "--version"], repo)
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
            print(f"PASS julia {precision}: +inf and -inf constants", flush=True)


if __name__ == "__main__":
    main()
