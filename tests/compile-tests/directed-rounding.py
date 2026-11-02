#!/usr/bin/env python3
"""The directed rounding of the interval library : the fused fast path decides as the exact one.

directedBinary rounds a product or a quotient up or down from the sign of its residual :
x*y - r, or x - r*y, r rounded to nearest. A fused multiply-add gives that residual
exactly when nothing underflows (|r| >= 2^-960 for a product ; |x|, |y|, |r| >= 2^-900
for a quotient, LE-GAIN-DES-FILTRES.md) ; elsewhere the exact comparison of 128-bit
significands decides. The test compares directedBinary with directedBinaryExact, the
exact comparison alone, bit for bit, on millions of operand pairs : random bit patterns
over every exponent, operands whose result lands near the two thresholds and in the
subnormals, powers of two and exact products, signed zeros, the largest doubles. Both
directions, products and quotients ; sums and differences, whose path is unchanged, as a
control. The sources are compiled as the build compiles them, without contraction.
"""

import argparse
from pathlib import Path
import subprocess
import sys
import tempfile

TEST = r"""
#include "directed_rounding.hh"
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <random>
using namespace itv::detail;

static uint64_t bits(double x) { uint64_t b; std::memcpy(&b, &x, 8); return b; }
static double fromBits(uint64_t b) { double x; std::memcpy(&x, &b, 8); return x; }
static bool same(double a, double b) { return (std::isnan(a) && std::isnan(b)) || bits(a) == bits(b); }

static long cases = 0, bad = 0, fused = 0;
static void check(double x, double y)
{
    static const BinaryOp ops[] = {BinaryOp::Add, BinaryOp::Sub, BinaryOp::Mul, BinaryOp::Div};
    static const char* names[] = {"add", "sub", "mul", "div"};
    for (int o = 0; o < 4; o++) {
        for (Direction d : {Direction::Down, Direction::Up}) {
            const double fast = directedBinary(ops[o], x, y, d);
            const double exact = directedBinaryExact(ops[o], x, y, d);
            cases++;
            if (o == 2 && std::isfinite(x * y) && std::fabs(x * y) >= 0x1p-960) fused++;
            if (o == 3 && y != 0 && std::fabs(x) >= 0x1p-900 && std::fabs(y) >= 0x1p-900 && std::fabs(x / y) >= 0x1p-900 && std::isfinite(x / y)) fused++;
            if (!same(fast, exact)) {
                if (bad < 10) printf("%s %s %a %a : fast %a, exact %a\n", names[o], d == Direction::Up ? "up" : "down", x, y, fast, exact);
                bad++;
            }
        }
    }
}

int main()
{
    std::mt19937_64 g(20261102);
    auto anyDouble = [&]() {
        for (;;) {
            const double x = fromBits(g());
            if (std::isfinite(x)) return x;
        }
    };
    // a double of random significand and sign, of binary exponent e
    auto withExponent = [&](int e) {
        const double m = 1.0 + double(g() >> 12) * 0x1p-52;
        return ((g() & 1) ? -1.0 : 1.0) * std::ldexp(m, e);
    };
    for (int i = 0; i < 1000000; i++) check(anyDouble(), anyDouble());
    // results around the thresholds 2^-960 and 2^-900 and in the subnormals
    for (int i = 0; i < 1000000; i++) {
        const int target = int(g() % 200) - 1080;  // the exponent of the result, -1080 to -881
        const int ex = int(g() % 1900) - 950;
        const double x = withExponent(ex);
        check(x, withExponent(target - ex));             // the product near 2^target
        check(x, withExponent(ex - target));             // the quotient near 2^target
    }
    // operands near the quotient threshold
    for (int i = 0; i < 200000; i++) check(withExponent(int(g() % 40) - 920), withExponent(int(g() % 40) - 20));
    for (int i = 0; i < 200000; i++) check(withExponent(int(g() % 40) + 100), withExponent(int(g() % 40) - 920));
    // exact and small cases, powers of two, signed zeros, extremes
    const double special[] = {0.0, -0.0, 1.0, -1.0, 3.0, 0.1, 1.0 / 3.0, 0x1p-1074, -0x1p-1074, 0x1p-1022,
                              0x1.fffffffffffffp-1023, 0x1p-960, 0x1.0000000000001p-960, 0x1.fffffffffffffp-961,
                              0x1p-900, 0x1.fffffffffffffp-901, 0x1p-480, 0x1p-450, 0x1p511, 0x1p512,
                              0x1.fffffffffffffp+1023, -0x1.fffffffffffffp+1023, 0x1p1023, 6.0, 7.0, 1e308, 1e-308};
    for (double x : special) {
        for (double y : special) check(x, y);
    }
    for (int i = 0; i < 200000; i++) check(double(int64_t(g() % 2000001) - 1000000), double(int64_t(g() % 2000001) - 1000000));
    printf("%ld cases, %ld by the fused path, %ld differ\n", cases, fused, bad);
    return bad != 0;
}
"""


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust", help="unused : the test builds the library sources")
    parser.add_argument("--cxx", default="g++")
    args = parser.parse_args()
    interval = repo / "compiler/interval"
    with tempfile.TemporaryDirectory(prefix="faust-directed-rounding-") as temp:
        work = Path(temp)
        (work / "test.cpp").write_text(TEST)
        build = [args.cxx, "-std=c++17", "-O2", "-fno-fast-math", "-ffp-contract=off", "-fwrapv", "-I", interval,
                 "test.cpp", interval / "directed_rounding.cpp", interval / "reference_math.cpp", "-o", "test"]
        result = subprocess.run(build, cwd=work, capture_output=True, text=True)
        if result.returncode:
            print((result.stdout + result.stderr).strip())
            print("FAILED")
            sys.exit(1)
        result = subprocess.run([work / "test"], cwd=work, capture_output=True, text=True)
        print((result.stdout + result.stderr).strip())
    print("all legs passed" if result.returncode == 0 else "FAILED")
    sys.exit(result.returncode)


if __name__ == "__main__":
    main()
