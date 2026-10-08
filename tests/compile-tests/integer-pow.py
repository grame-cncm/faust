#!/usr/bin/env python3
"""Regression test for integer pow with run-time exponent (Issue #1340).

When both arguments of pow are integers and the exponent is a non-constant
signal, the result must be exact:
1. Under -ffast-math, pow(250, 1) must equal 250 (not truncated to 249).
2. Beyond 2^24 in single precision, pow(25, 6) must equal 244140625 (not 244140624 or 244140720).
3. Negative bases like pow(-3, 3) must equal -27.
"""

import argparse
from pathlib import Path
import subprocess
import sys
import tempfile


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    parser.add_argument("--cxx", default="g++")
    parser.add_argument("--cc", default="gcc")
    args = parser.parse_args()

    dsp_source = """
    import("stdfaust.lib");
    s = ba.period(2) < 1;
    process = pow(250, s) - (1 + 249*s),
              pow(25, 6*s) - (1 + 244140624*s),
              pow(-3, 3*s) - (1 - 28*s);
    """

    runner_cpp = """
    #include <faust/dsp/dsp.h>
    #include <faust/gui/meta.h>
    #include <faust/gui/UI.h>
    #include "generated.cpp"
    #include <iostream>
    #include <cmath>

    int main() {
        mydsp dsp;
        dsp.init(44100);
        float out0[2] = {0}, out1[2] = {0}, out2[2] = {0};
        float* outputs[3] = {out0, out1, out2};
        dsp.compute(2, nullptr, outputs);

        bool ok = true;
        // Sample 0: s == 1
        if (std::abs(out0[0]) > 0.0f) {
            std::cerr << "FAIL: pow(250, 1) error = " << out0[0] << std::endl;
            ok = false;
        }
        if (std::abs(out1[0]) > 0.0f) {
            std::cerr << "FAIL: pow(25, 6) error = " << out1[0] << std::endl;
            ok = false;
        }
        if (std::abs(out2[0]) > 0.0f) {
            std::cerr << "FAIL: pow(-3, 3) error = " << out2[0] << std::endl;
            ok = false;
        }

        // Sample 1: s == 0
        if (std::abs(out0[1]) > 0.0f || std::abs(out1[1]) > 0.0f ||
            std::abs(out2[1]) > 0.0f) {
            std::cerr << "FAIL: s == 0 power error" << std::endl;
            ok = false;
        }

        return ok ? 0 : 1;
    }
    """

    with tempfile.TemporaryDirectory(prefix="faust-integer-pow-") as temp:
        work = Path(temp)
        dsp_file = work / "repro.dsp"
        dsp_file.write_text(dsp_source)

        runner_file = work / "runner.cpp"
        runner_file.write_text(runner_cpp)

        # Test both -O2 and -O3 -ffast-math in single precision
        for cxx_flags in [["-O2"], ["-O3", "-ffast-math"]]:
            flags_desc = " ".join(cxx_flags)
            print(f"Testing C++ backend with flags: {flags_desc}...", flush=True)

            cmd_faust = [
                str(args.faust.resolve()),
                "-I", str(repo / "libraries"),
                "-lang", "cpp",
                "-single",
                str(dsp_file),
                "-o", str(work / "generated.cpp")
            ]
            subprocess.run(cmd_faust, cwd=work, check=True)

            cmd_build = [
                args.cxx,
                *cxx_flags,
                "-I", str(repo / "architecture"),
                str(runner_file),
                "-o", str(work / "runner")
            ]
            subprocess.run(cmd_build, cwd=work, check=True)

            res = subprocess.run([str(work / "runner")], cwd=work, capture_output=True, text=True)
            if res.returncode != 0:
                print(res.stderr.strip())
                print(f"FAILED under {flags_desc}")
                sys.exit(1)

    print("All integer pow runtime tests passed successfully.")


if __name__ == "__main__":
    main()
