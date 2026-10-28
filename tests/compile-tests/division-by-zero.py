#!/usr/bin/env python3
"""Regression test: a certain division by 0 is refused, written as a division or as a power.

A division by a constant 0 stops the compilation ("ERROR : division by 0"). A power of 0
with a negative exponent is 1 / 0^|k|, the same certain division : pow(0.0, -1) was folded
to INFINITY. Each program of REFUSED must stop with that error ; each program of ACCEPTED
must compile : a power of 0 with an exponent >= 0, and a power whose base may be 0 only at
run time (a possible division by 0, whose code is defined).
"""

import argparse
from pathlib import Path
import subprocess
import sys
import tempfile

REFUSED = [
    "process = 1/0;",
    "process = 1.0/0.0;",
    "process = _/0.0;",
    "process = pow(0.0, -1);",
    "process = pow(0, -1);",
    "process = pow(-0.0, -1);",
    "process = pow(0.0, -0.5);",
    "process = pow(0.5 - 0.5, -2);",
]

ACCEPTED = [
    "process = pow(0.0, 0);",
    "process = pow(0, 2);",
    "process = pow(2, -1);",
    'process = pow(int(nentry("x", 0, -1, 1, 1)), -1);',
    'process = pow(hslider("x", 0, -1, 1, 0.1), -0.5);',
]


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    args = parser.parse_args()
    faust = args.faust.resolve()

    failures = 0
    with tempfile.TemporaryDirectory(prefix="faust-division-by-zero-") as temp:
        work = Path(temp)
        for want, programs in (("refused", REFUSED), ("accepted", ACCEPTED)):
            for program in programs:
                (work / "prog.dsp").write_text(program + "\n")
                r = subprocess.run([faust, "-lang", "cpp", "prog.dsp", "-o", "prog.cpp"],
                                   cwd=work, capture_output=True, text=True)
                if want == "refused":
                    ok = r.returncode != 0 and "ERROR : division by 0" in r.stderr and "ASSERT" not in r.stderr
                else:
                    ok = r.returncode == 0
                got = "accepted" if r.returncode == 0 else (r.stderr.strip().splitlines() or ["?"])[0]
                print(f"{'ok' if ok else 'FAIL':5} {want:9} {program}   [{got}]")
                failures += not ok
    print("all programs passed" if failures == 0 else f"{failures} program(s) FAILED")
    sys.exit(1 if failures else 0)


if __name__ == "__main__":
    main()
