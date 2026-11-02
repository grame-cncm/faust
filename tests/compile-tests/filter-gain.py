#!/usr/bin/env python3
"""The certified gain of a filter : a bound of its L1 norm, found over a short response.

filterGain (compiler/interval/intervalKernel.cpp) bounds the L1 norm L of the impulse
response h of y(n) = x(n) + sum_j c[j] y(n-1-j), from a block length m after which the
companion matrix contracts (||A^m|| <= 1/2), proved in double-word arithmetic
(LE-GAIN-DES-FILTRES.md). In double, the error bound of the squarings exploded for a
strongly non-normal matrix, and a NaN norm, read as 0, ended the search : the pink noise
filter was certified from a million-sample response (0.7 s of compilation).

For stable filters (pink noise, first order, resonators up to r = 0.999, a cascade), the
bound must exist, be at least the L1 norm (a partial sum computed here in rationals, a
lower bound since every |h| counts), stay within 1e-4 of it, and come from a response of
at most 65536 samples. For filters with a pole on or outside the unit circle, there must
be no bound.
"""

import argparse
from fractions import Fraction
import math
from pathlib import Path
import subprocess
import sys
import tempfile

TEST = r"""
#include "interval_algebra.hh"
#include <cstdio>
#include <cstdlib>
#include <vector>
int main(int argc, char* argv[])
{
    std::vector<double> c;
    for (int i = 1; i < argc; i++) c.push_back(std::strtod(argv[i], nullptr));
    itv::FilterGain g{};
    const bool ok = itv::filterGain(c, g);
    printf("%d %a %ld\n", ok, g.L, g.block);
    return 0;
}
"""


def resonator(r, theta):
    return [2 * r * math.cos(theta), -r * r]


def cascade(a, b):
    # the denominators multiply : (1 - a1 z - a2 z^2)(1 - b1 z - b2 z^2)
    pa = [1.0] + [-v for v in a]
    pb = [1.0] + [-v for v in b]
    prod = [0.0] * (len(pa) + len(pb) - 1)
    for i, u in enumerate(pa):
        for j, v in enumerate(pb):
            prod[i + j] += u * v
    return [-v for v in prod[1:]]


STABLE = {
    "pink noise": [2.4949560019999999, -2.0172658750000001, 0.52218940000000003],
    "first order 0.9": [0.9],
    "first order 0.999": [0.999],
    "first order -0.5": [-0.5],
    "resonator 0.9, 0.5": resonator(0.9, 0.5),
    "resonator 0.99, 0.01": resonator(0.99, 0.01),
    "resonator 0.999, 2.5": resonator(0.999, 2.5),
    "resonator 0.999, 0.01": resonator(0.999, 0.01),
    "cascade": cascade(resonator(0.95, 0.3), resonator(0.9, 1.2)),
}

UNSTABLE = {
    "first order 1.0001": [1.0001],
    "integrator": [1.0],
    "resonator on the unit circle": [2 * math.cos(0.3), -1.0],
    "resonator 1.00001, 0.01": resonator(1.00001, 0.01),
}


def l1_lower(c, samples):
    """A lower bound of the L1 norm : the sum of |h(n)| for n < samples, h in rationals
    rounded to 400 bits at each step (an error far below the tolerance)"""
    cs = [Fraction(v) for v in c]
    h = [Fraction(1)]
    total = Fraction(1)
    scale = 2 ** 400
    for n in range(1, samples):
        v = sum(cs[j] * h[n - 1 - j] for j in range(len(cs)) if n - 1 - j >= 0)
        v = Fraction(round(v * scale), scale)
        h.append(v)
        total += abs(v)
    return float(total), float(abs(h[-1]))


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust", help="unused : the test builds the library sources")
    parser.add_argument("--cxx", default="g++")
    args = parser.parse_args()
    interval = repo / "compiler/interval"
    ok = True
    with tempfile.TemporaryDirectory(prefix="faust-filter-gain-") as temp:
        work = Path(temp)
        (work / "test.cpp").write_text(TEST)
        build = [args.cxx, "-std=c++17", "-O2", "-fno-fast-math", "-ffp-contract=off", "-fwrapv", "-I", interval,
                 "-I", repo / "compiler/FaustAlgebra", "test.cpp", interval / "intervalKernel.cpp", interval / "directed_rounding.cpp",
                 interval / "reference_math.cpp", "-o", "test"]
        result = subprocess.run(build, cwd=work, capture_output=True, text=True)
        if result.returncode:
            print((result.stdout + result.stderr).strip())
            print("FAILED")
            sys.exit(1)

        def gain(c):
            out = subprocess.run([work / "test", *[repr(v) for v in c]], capture_output=True, text=True).stdout.split()
            return out[0] == "1", float.fromhex(out[1]), int(out[2])

        for name, c in STABLE.items():
            certified, L, block = gain(c)
            if not certified:
                print(f"FAIL  {name:28} no bound")
                ok = False
                continue
            lower, last = l1_lower(c, max(2 * block, 4096))
            good = math.isfinite(L) and L >= lower and L <= lower * (1 + 1e-4) and block <= 65536
            print(f"{'ok' if good else 'FAIL':5} {name:28} L = {L:.10g}, sum |h| >= {lower:.10g}, response of {block} samples")
            ok &= good
        for name, c in UNSTABLE.items():
            certified, L, block = gain(c)
            print(f"{'ok' if not certified else 'FAIL':5} {name:28} {'no bound' if not certified else f'certified L = {L}'}")
            ok &= not certified
    print("all legs passed" if ok else "FAILED")
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
