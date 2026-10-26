#!/usr/bin/env python3
"""Regression test: a sum with infinite coefficients is normalized in finite time.

The normal form factors the common divisor of the terms of a sum, keeping its symbols
only : the coefficient of the divisor is dropped. It was divided out, and an infinite
coefficient divided by itself is NaN, a divisor that never leaves the sum : the
factorization looped forever on

    i = 1e308*10;
    process = _,_,_ : *(i), *(i), _ :> _;

and on ma.INFINITY*2 in double. Each program must compile within the time limit.
"""

import argparse
from pathlib import Path
import subprocess
import sys
import tempfile

PROGRAMS = {
    "float overflow": ("i = 1e308*10;\nprocess = _,_,_ : *(i), *(i), _ :> _;\n", []),
    "ma.INFINITY": ('import("stdfaust.lib");\nprocess = _,_,_ : *(ma.INFINITY*2), *(ma.INFINITY*2), _ :> _;\n', []),
    "ma.INFINITY, double": ('import("stdfaust.lib");\nprocess = _,_,_ : *(ma.INFINITY*2), *(ma.INFINITY*2), _ :> _;\n', ["-double"]),
}
TIMEOUT = 30


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    args = parser.parse_args()

    failures = 0
    for name, (source, options) in PROGRAMS.items():
        with tempfile.TemporaryDirectory(prefix="faust-infinite-") as temp:
            work = Path(temp)
            (work / "p.dsp").write_text(source)
            try:
                r = subprocess.run([str(args.faust), "-t", "0", *options, str(work / "p.dsp"), "-o", str(work / "p.cpp")],
                                   capture_output=True, text=True, timeout=TIMEOUT)
            except subprocess.TimeoutExpired:
                print(f"FAIL [{name}]: faust did not finish in {TIMEOUT} s")
                failures += 1
                continue
            if r.returncode != 0:
                print(f"FAIL [{name}]: faust failed: {r.stderr.strip()}")
                failures += 1
                continue
            print(f"ok   [{name}]")
    if failures:
        sys.exit(1)


if __name__ == "__main__":
    main()
