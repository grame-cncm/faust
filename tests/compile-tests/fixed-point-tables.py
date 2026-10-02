#!/usr/bin/env python3
"""Compile generated C++ table fills against the Xilinx fixed-point types."""

import argparse
from pathlib import Path
import subprocess
import tempfile


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    parser.add_argument("--cxx", default="c++")
    parser.add_argument("--ap-fixed-include", type=Path,
                        help="directory containing the Xilinx ap_fixed.h header")
    args = parser.parse_args()

    cases = {
        "static": "process = rdtable(8, 0.25, 0);",
        "dynamic": "process = rwtable(8, -16.5, 0, _, 1);",
        "mixed": ("process = rdtable(8, 0.25, 0), "
                  "rdtable(16, -16.5, 0), rdtable(8, +(1)~_, 0);"),
    }
    options = [
        [], ["-fx-size", "16"], ["-fx-size", "32"], ["-fx-size", "64"],
        ["-fx-size", "32", "-it"], ["-fx-size", "32", "-mem"],
    ]
    with tempfile.TemporaryDirectory(prefix="faust-fixed-point-tables-") as temp:
        work = Path(temp)
        wrapper = work / "test.cpp"
        wrapper.write_text(
            '#include "faust/dsp/fixed-point.h"\n'
            '#include "faust/dsp/dsp.h"\n'
            '#include "faust/gui/UI.h"\n'
            '#include "faust/gui/meta.h"\n'
            '#include "generated.cpp"\n'
        )
        compile_cmd = [args.cxx, "-std=c++17", "-fsyntax-only",
                       "-I" + str(repo / "architecture")]
        if args.ap_fixed_include:
            compile_cmd.append("-I" + str(args.ap_fixed_include.resolve()))
        compile_cmd.append(str(wrapper))
        count = 0
        for name, source in cases.items():
            dsp = work / (name + ".dsp")
            dsp.write_text(source)
            for extra in options:
                print(name, "-fx", *extra, flush=True)
                subprocess.run(
                    [str(args.faust.resolve()), "-lang", "cpp", "-cn", "testdsp",
                     "-fx", *extra, str(dsp), "-o", str(work / "generated.cpp")],
                    cwd=work, check=True,
                )
                subprocess.run(compile_cmd, cwd=work, check=True)
                count += 1
        print(f"Passed {count} fixed-point table compilation checks.")


if __name__ == "__main__":
    main()
