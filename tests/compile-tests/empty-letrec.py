#!/usr/bin/env python3
"""Regression test (issue #416): an empty letrec defines nothing.

`e letrec { }` is `e`, as `e with { }` is: the `where` definitions are only
visible inside the recursive bodies, so they add nothing either. The
expansion (boxWithRecDef) used to build an empty parallel list and a bus of
0 wires, and the compiler crashed (a segmentation fault). A symbol that the
letrec does not define stays undefined: a compilation error, not a crash.
"""

import argparse
from pathlib import Path
import subprocess
import sys
import tempfile

# (program, expected exit code, expected text in the generated C++ or the error ; a tuple
# when the text has several spellings)
CASES = [
    ("process = 1 letrec { };", 0, "output0[i0] = static_cast<FAUSTFLOAT>(1);"),
    ("process = _ letrec { } : +(1);", 0, "getNumInputs() {\n\t\treturn 1;"),
    ("process = 1 letrec { where f = 2; };", 0, "output0[i0] = static_cast<FAUSTFLOAT>(1);"),
    ("process = v letrec { } with { v = 1; };", 0, "output0[i0] = static_cast<FAUSTFLOAT>(1);"),
    # the state of the recursion : fRec0, or fIIR0 where the normal form reveals the
    # recursion 1 + 0.5 * x' as a filter kernel
    ("process = (x letrec { }) letrec { 'x = x * 0.5 + 1; };", 0, ("fRec0", "fIIR0")),
    ("process = v letrec { };", 1, "undefined symbol : v"),
]


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    args = parser.parse_args()
    faust = args.faust.resolve()

    failures = 0
    with tempfile.TemporaryDirectory(prefix="faust-empty-letrec-") as temp:
        work = Path(temp)
        for program, code, expected in CASES:
            (work / "t.dsp").write_text(program + "\n")
            r = subprocess.run([str(faust), "t.dsp"], cwd=work, capture_output=True, text=True)
            text = r.stdout if code == 0 else r.stderr
            if r.returncode != code:
                failures += 1
                print(f"FAIL {program}: exit {r.returncode}, expected {code}\n    {r.stderr.strip()[:300]}")
            elif not any(e in text for e in (expected if isinstance(expected, tuple) else (expected,))):
                failures += 1
                print(f"FAIL {program}: {expected!r} not in the output")
            else:
                print(f"PASS {program}")
    return 1 if failures else 0


if __name__ == "__main__":
    sys.exit(main())
