#!/usr/bin/env python3
"""Regression test: a negated constant or control-rate expression is hoisted.

The code generators compile -1*y (and y*-1) as -y and never cache the
product itself. The occurrence markup used to mark y in the context of the
product rather than in the context where the product is used, so a constant
y used once in a sample-rate context (a select2 branch) was not detected as
such, was not hoisted, and was recomputed at every sample:

    output0[i0] = ((iTemp1) ? 0.5f : -(std::exp(-(1e+01f / fConst0))));

instead of `fConst1 = std::exp(-(1e+01f / fConst0))` in instanceConstants.
This shows up with `0 - expm1(-x)`, the precise form of `1 - exp(-x)`.

For each backend, every call of exp/expm1 must be the right-hand side of a
constant (fConstN) or control-rate (fSlowN) variable, never inline in the
sample loop.
"""

import argparse
from pathlib import Path
import re
import subprocess
import sys
import tempfile

DSP = """
SR = fconstant(int fSamplingFreq, <math.h>);
e1 = ffunction(float expm1f|expm1|expm1l (float), <math.h>, "");
k(n) = 1.0/(0.1*n*SR);
t = hslider("t", 0.3, 0.01, 1, 0.01);
// one value per output, each used once in a select2 branch
process = _ <: select2(_ > 0, 0.0 - exp(-k(1)), 0.5),      // negated primitive
                select2(_ > 0, 0.0 - e1(-k(2)), 0.5),       // negated foreign function
                select2(_ > 0, e1(-k(3)) * -1.0, 0.5),      // y*-1
                select2(_ > 0, 0.0 - exp(-1.0/(t*SR)), 0.5); // control rate
"""

CALL = re.compile(r"\b(?:std::)?(?:expm1|exp)[fl]?\s*\(")
HOISTED = re.compile(r"\b(?:fConst|fSlow)\d+\s*=")


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    parser.add_argument("--langs", nargs="+", default=["cpp", "c", "ocpp"])
    args = parser.parse_args()

    failures = 0
    with tempfile.TemporaryDirectory(prefix="faust-hoist-negation-") as temp:
        work = Path(temp)
        dsp_file = work / "neg.dsp"
        dsp_file.write_text(DSP)
        for lang in args.langs:
            out = work / f"neg.{lang}"
            r = subprocess.run([str(args.faust), "-lang", lang, str(dsp_file), "-o", str(out)],
                               capture_output=True, text=True)
            if r.returncode != 0:
                print(f"FAIL [{lang}]: faust failed: {r.stderr.strip()}")
                failures += 1
                continue
            inline = [line.strip() for line in out.read_text().splitlines()
                      if CALL.search(line) and "dummy" not in line
                      and not HOISTED.search(line)]
            if inline:
                failures += 1
                print(f"FAIL [{lang}]: exp/expm1 not hoisted:")
                for line in inline:
                    print(f"    {line}")
            else:
                print(f"ok   [{lang}]")
    if failures:
        sys.exit(1)


if __name__ == "__main__":
    main()
