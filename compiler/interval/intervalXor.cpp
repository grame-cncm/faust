#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Xor
// interval Xor(const interval& x, const interval& y) const;
// void testXor() const;
static double myXor(double x, double y)
{
    auto a = int(x);
    auto b = int(y);
    int  c = a ^ b;
    return double(c);
}

// BRUTE FORCE
interval interval_algebra::Xor(const interval& x, const interval& y) const
{
    if (x.isEmpty() || y.isEmpty()) return {};
    auto x0 = int(x.lo());
    auto x1 = int(x.hi());
    auto y0 = int(y.lo());
    auto y1 = int(y.hi());

    int z0 = INT32_MAX;
    int z1 = INT32_MIN;

    for (int i = x0; i <= x1; i++) {
        for (int j = y0; j <= y1; j++) {
            int z = i ^ j;
            if (z < z0) z0 = z;
            if (z > z1) z1 = z;
        }
    }
    return interval(double(z0), double(z1));
}

void interval_algebra::testXor() const
{
    analyzeBinaryMethod(10, 2000, "Xor", interval(-1000, -800), interval(127), myXor, &interval_algebra::Xor);
    analyzeBinaryMethod(10, 2000, "Xor", interval(-1000, -800), interval(123), myXor, &interval_algebra::Xor);
    analyzeBinaryMethod(10, 2000, "Xor", interval(-128, 128), interval(127), myXor, &interval_algebra::Xor);
    analyzeBinaryMethod(10, 2000, "Xor", interval(0, 1000), interval(63, 127), myXor, &interval_algebra::Xor);
    analyzeBinaryMethod(10, 2000, "Xor", interval(-1000, 1000), interval(63, 127), myXor, &interval_algebra::Xor);
}
}  // namespace itv
