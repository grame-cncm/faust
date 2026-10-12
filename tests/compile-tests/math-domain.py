#!/usr/bin/env python3
"""Run math functions out of their domain, and isnan/isinf, in Julia and Cmajor.

C returns NaN for sqrt(-2), log(-2), asin(-2), a negative base to a
fractional power...; Julia's functions throw DomainError there, which
stopped the generated code. Cmajor's isnan and isinf return a bool, which
the int32 Faust gives them does not take ("Cannot implicitly convert true
('bool') to 'int32'"), and the Cmajor backend printed -inf as inf.

The program reads -2 from its input:
sqrt, log, log10, asin, acos, acosh, atanh and pow(x, 0.5) must give NaN,
isnan(sqrt(x)) 1, and isinf(log(0)) 1 (log(0) is folded to the constant
-inf, assigned to an int32 in Cmajor); -inf itself must keep its sign.
"""
import argparse
import array
import json
import math
from pathlib import Path
import subprocess
import tempfile

SOURCE = """
isnan = ffunction(int isnanf|isnan|isnanl(float), <math.h>, "");
isinf = ffunction(int isinff|isinf|isinfl(float), <math.h>, "");
acosh = ffunction(float acoshf|acosh|acoshl(float), <math.h>, "");   // as in maths.lib
atanh = ffunction(float atanhf|atanh|atanhl(float), <math.h>, "");
process = _ <: sqrt, log, log10, asin, acos, acosh, atanh, pow(_, 0.5),
               (sqrt : isnan), isinf(log(0.0)), log(0.0);
"""
EXPECTED = ["nan"] * 8 + [1.0, 1.0, -math.inf]
FRAMES = 4
X = -2.0

JULIA_RUNNER = """
abstract type dsp end
abstract type FMeta end
abstract type UI end
const FAUSTFLOAT = SAMPLE
include("mydsp.jl")
d = mydsp{SAMPLE}()
init!(d, Int32(44100))
output = zeros(SAMPLE, FRAMES, 11)
compute!(d, Int32(FRAMES), fill(SAMPLE(X), FRAMES, 1), output)
println(join(output[FRAMES, :], " "))
""".replace("FRAMES", str(FRAMES)).replace("X)", f"{X})")

# cmaj render writes 20000 frames of silence, rounded up to the block size, before the patch
CMAJ_SILENCE = 20480


def run(command, work, **kw):
    print("+", " ".join(map(str, command)), flush=True)
    return subprocess.run(command, cwd=work, check=True, **kw)


def check(backend, precision, values):
    got = ["nan" if math.isnan(v) else v for v in values]
    if got != EXPECTED:
        raise SystemExit(f"FAIL {backend} {precision}: {got} instead of {EXPECTED}")
    print(f"PASS {backend} {precision}: NaN out of the domain, isnan/isinf as int, -inf", flush=True)


def write_wav(path, frames, value):
    """A mono 32-bit float WAV file of `frames` copies of `value`."""
    data = array.array("f", [value] * frames).tobytes()
    fmt = (3).to_bytes(2, "little") + (1).to_bytes(2, "little") + (48000).to_bytes(4, "little") \
        + (48000 * 4).to_bytes(4, "little") + (4).to_bytes(2, "little") + (32).to_bytes(2, "little")
    body = b"WAVE" + b"fmt " + len(fmt).to_bytes(4, "little") + fmt \
        + b"data" + len(data).to_bytes(4, "little") + data
    path.write_bytes(b"RIFF" + len(body).to_bytes(4, "little") + body)


def read_wav(path):
    w = path.read_bytes()
    i = w.index(b"data")
    a = array.array("f")
    a.frombytes(w[i + 8:i + 8 + int.from_bytes(w[i + 4:i + 8], "little")])
    return a


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    parser.add_argument("--julia", default="julia")
    parser.add_argument("--cmaj", default="cmaj")
    parser.add_argument("--backends", nargs="+", choices=["julia", "cmajor"],
                        default=["julia", "cmajor"])
    args = parser.parse_args()
    faust = args.faust.resolve()
    run([faust, "--version"], repo)
    for precision in ["single", "double"] if "julia" in args.backends else []:
        with tempfile.TemporaryDirectory(prefix="faust-math-domain-julia-") as temp:
            work = Path(temp)
            (work / "domain.dsp").write_text(SOURCE)
            run([faust, "-lang", "julia", "-" + precision, work / "domain.dsp",
                 "-o", work / "mydsp.jl"], work)
            sample = "Float32" if precision == "single" else "Float64"
            (work / "runner.jl").write_text(JULIA_RUNNER.replace("SAMPLE", sample))
            out = run([args.julia, "--startup-file=no", "runner.jl"], work,
                      capture_output=True, text=True).stdout
            check("julia", precision, [float(v) for v in out.split()])
    for precision in ["single", "double"] if "cmajor" in args.backends else []:
        with tempfile.TemporaryDirectory(prefix="faust-math-domain-cmajor-") as temp:
            work = Path(temp)
            (work / "domain.dsp").write_text(SOURCE)
            run([faust, "-lang", "cmajor", "-" + precision, work / "domain.dsp",
                 "-o", work / "domain.cmajor"], work)
            (work / "domain.cmajorpatch").write_text(json.dumps(
                {"CmajorVersion": 1, "ID": "dev.faust.domain", "version": "1.0",
                 "name": "domain", "source": "domain.cmajor"}))
            frames = CMAJ_SILENCE + FRAMES
            write_wav(work / "in.wav", frames, X)
            run([args.cmaj, "render", "--input=in.wav", "--channels=11", "--blockSize=512",
                 "--output=out.wav", "domain.cmajorpatch"], work)
            a = read_wav(work / "out.wav")
            check("cmajor", precision, list(a[(frames - 1) * 11:frames * 11]))


if __name__ == "__main__":
    main()
