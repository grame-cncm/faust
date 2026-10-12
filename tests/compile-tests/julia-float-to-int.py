#!/usr/bin/env python3
"""Compile and execute float-to-integer conversions in Julia.

The Julia backend converted a float to an integer with trunc(Int32, x),
which throws InexactError for a NaN or a value out of the Int32 range:
`int()` of a NaN stopped the computation. The conversion now saturates,
as the C++ backend does on arm64 and the WebAssembly one does with
i32.trunc_sat: 0 for a NaN, the nearest bound of the range beyond it.

`process = _ : int;` is run on 0.5, -2.7, NaN, 1e10, -1e10 and 3e9, in
single and double precision.
"""
import argparse
from pathlib import Path
import subprocess
import tempfile

SOURCE = "process = _ : int;\n"

RUNNER = """
abstract type dsp end
abstract type FMeta end
abstract type UI end
const FAUSTFLOAT = SAMPLE
include("mydsp.jl")
d = mydsp{SAMPLE}()
init!(d, Int32(44100))
x = SAMPLE[0.5, -2.7, NaN, 1e10, -1e10, 3e9]
expected = SAMPLE[0, -2, 0, typemax(Int32), typemin(Int32), typemax(Int32)]
output = zeros(SAMPLE, length(x), 1)
compute!(d, Int32(length(x)), reshape(x, :, 1), output)
@assert vec(output) == expected (vec(output), expected)
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
        with tempfile.TemporaryDirectory(prefix="faust-float-to-int-julia-") as temp:
            work = Path(temp)
            (work / "int.dsp").write_text(SOURCE)
            run([faust, "-lang", "julia", "-" + precision, work / "int.dsp",
                 "-o", work / "mydsp.jl"], work)
            sample = "Float32" if precision == "single" else "Float64"
            (work / "runner.jl").write_text(RUNNER.replace("SAMPLE", sample))
            run([args.julia, "--startup-file=no", "runner.jl"], work)
            print(f"PASS julia {precision}: NaN and out-of-range conversions saturate", flush=True)


if __name__ == "__main__":
    main()
