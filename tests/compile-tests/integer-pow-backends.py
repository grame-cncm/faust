#!/usr/bin/env python3
"""Compile and execute integer-power regressions in Rust and Julia.

Subtract in integer arithmetic before converting DSP outputs to sample floats:
25**6 cannot be represented exactly in Float32. Negative exponents also check
round-to-nearest, ties-to-even (2**-1 and (-2)**-1 must both convert to zero).
"""
import argparse
from pathlib import Path
import subprocess
import tempfile

SOURCE = """
import("stdfaust.lib");
s = ba.period(2) < 1;
process = pow(250, s) - (1 + 249*s),
          pow(25, 6*s) - (1 + 244140624*s),
          pow(-3, 3*s) - (1 - 28*s),
          pow(2, 2*s-1) - 2*s,
          pow(-2, 2*s-1) + 2*s,
          pow(46340, 2*s) - (1 + 2147395599*s);
"""


def run(command, work):
    print("+", " ".join(map(str, command)), flush=True)
    subprocess.run(command, cwd=work, check=True)


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    parser.add_argument("--backends", nargs="+", choices=["rust", "julia"],
                        default=["rust", "julia"])
    parser.add_argument("--cargo", default="cargo")
    parser.add_argument("--offline", action="store_true", help="use cached Cargo dependencies")
    parser.add_argument("--julia", default="julia")
    args = parser.parse_args()
    faust = args.faust.resolve()
    run([faust, "--version"], repo)
    for backend in args.backends:
        tool = {"rust": args.cargo, "julia": args.julia}[backend]
        run([tool, "--version"], repo)
        for precision in ["single", "double"]:
            with tempfile.TemporaryDirectory(prefix="faust-pow-" + backend + "-") as temp:
                work = Path(temp)
                (work / "pow.dsp").write_text(SOURCE)
                extension = {"rust": "rs", "julia": "jl"}[backend]
                generated = work / ("mydsp." + extension)
                command = [faust, "-I", repo / "libraries", "-lang", backend,
                           "-" + precision, work / "pow.dsp", "-o", generated]
                if backend == "rust":
                    architecture = (repo / "architecture/rust/minimal.rs").read_text()
                    architecture = architecture.split("fn main() {")[0]
                    if precision == "double":
                        architecture = architecture.replace("type FaustFloat = F32;", "type FaustFloat = F64;")
                    architecture += """
fn main() {
    let mut dsp = mydsp::new();
    dsp.init(44100);
    let mut a = [0.0; 2]; let mut b = [0.0; 2]; let mut c = [0.0; 2];
    let mut d = [0.0; 2]; let mut e = [0.0; 2]; let mut f = [0.0; 2];
    let inputs: [&[FaustFloat]; 0] = [];
    dsp.compute(2, &inputs, &mut [&mut a, &mut b, &mut c, &mut d, &mut e, &mut f]);
    for channel in [a, b, c, d, e, f] {
        for value in channel { assert_eq!(value, 0.0); }
    }
}
"""
                    (work / "runner.rs").write_text(architecture)
                    command += ["-a", work / "runner.rs"]
                run(command, work)
                if backend == "rust":
                    (work / "Cargo.toml").write_text("""[package]
name = "faust-integer-pow"
version = "0.1.0"
edition = "2024"
[[bin]]
name = "pow-test"
path = "mydsp.rs"
[dependencies]
libm = "0.2"
num-traits = "0.2"
""")
                    run([args.cargo, "run", "--quiet"] + (["--offline"] if args.offline else []), work)
                else:
                    sample = "Float32" if precision == "single" else "Float64"
                    (work / "runner.jl").write_text("""
abstract type dsp end
abstract type FMeta end
abstract type UI end
const FAUSTFLOAT = SAMPLE
include("mydsp.jl")
d = mydsp{SAMPLE}()
init!(d, Int32(44100))
output = zeros(SAMPLE, 6, 2)
compute!(d, Int32(2), zeros(SAMPLE, 0, 2), output)
@assert all(iszero, output) output
""".replace("SAMPLE", sample))
                    run([args.julia, "--startup-file=no", "runner.jl"], work)
                print(f"PASS {backend} {precision}: 6 integer powers, 2 samples", flush=True)


if __name__ == "__main__":
    main()
