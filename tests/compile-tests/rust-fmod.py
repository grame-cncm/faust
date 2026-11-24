#!/usr/bin/env python3
"""Check the value of a Faust fmod call nested in multiplication in Rust."""
import argparse
from pathlib import Path
import subprocess
import tempfile

SOURCE = 'process = hslider("a", 2, 0, 10, 1) * fmod(hslider("b", 8, 0, 10, 1), 3);\n'
RUNNER = """
fn main() {
    let mut dsp = mydsp::new();
    dsp.init(44100);
    let mut output = [0.0; 1];
    let inputs: [&[FaustFloat]; 0] = [];
    dsp.compute(1, &inputs, &mut [&mut output]);
    println!("{}", output[0]);
}
"""


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    parser.add_argument("--rustc", default="rustc")
    args = parser.parse_args()
    faust = args.faust.resolve()
    subprocess.run([faust, "--version"], check=True)
    subprocess.run([args.rustc, "--version"], check=True)

    architecture = (repo / "architecture/rust/minimal.rs").read_text().split("fn main() {")[0]
    # This DSP uses no functions from the optional math crates.
    for line in ("extern crate libm;", "extern crate num_traits;",
                 "use num_traits::{cast::FromPrimitive, float::Float};"):
        architecture = architecture.replace(line + "\n", "")
    failed = False
    for precision, scalar in [("single", "F32"), ("double", "F64")]:
        with tempfile.TemporaryDirectory(prefix="faust-rust-fmod-") as temp:
            work = Path(temp)
            (work / "fmod.dsp").write_text(SOURCE)
            (work / "runner.rs").write_text(
                architecture.replace("type FaustFloat = F32;", f"type FaustFloat = {scalar};") + RUNNER
            )
            subprocess.run([faust, "-lang", "rust", "-" + precision, "-a", "runner.rs",
                            "fmod.dsp", "-o", "mydsp.rs"], cwd=work, check=True)
            subprocess.run([args.rustc, "--edition=2024", "mydsp.rs", "-o", "fmod-test"],
                           cwd=work, check=True)
            exe = work / ("fmod-test.exe" if (work / "fmod-test.exe").exists() else "fmod-test")
            value = float(subprocess.check_output([exe], text=True))
            print(f"Rust {precision}: expected 4, got {value:g}")
            failed |= value != 4.0
    raise SystemExit(int(failed))


if __name__ == "__main__":
    main()
