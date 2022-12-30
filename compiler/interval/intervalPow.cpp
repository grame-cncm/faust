#include <algorithm>
#include <cassert>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Pow
// interval Pow(const interval& x, const interval& y) const;
// void testPow() const;

static interval ipow(const interval& x, int y)
{
    assert(y >= 0);
    if (y == 0) {
        return interval(1.0);
    }

    if ((y & 1) == 0) {
        // y is even
        double z0 = std::pow(x.lo(), y);
        double z1 = std::pow(x.hi(), y);
        return {0, std::max(z0, z1)};
    }

    // y is odd
    return {std::pow(x.lo(), y), std::pow(x.hi(), y)};
}

interval interval_algebra::Pow(const interval& x, const interval& y) const
{
    if (x.lo() > 0) {
        // x all positive
        return Exp(Mul(y, Log(x)));
    }

    int      y0 = std::max(0, saturatedIntCast(y.lo()));
    int      y1 = std::max(0, saturatedIntCast(y.hi()));
    interval z  = ipow(x, y0);
    for (int i = y0 + 1; i <= y1; ++i) {
        z = reunion(z, ipow(x, i));
    }
    return z;
}

static double myPow(double x, double y)
{
    return std::pow(x, y);
}

void interval_algebra::testPow() const
{
    analyzeBinaryMethod(10, 2000, "Pow2", interval(-1, 1), interval(1, 3), myPow, &interval_algebra::Pow);
    analyzeBinaryMethod(10, 2000, "Pow2", interval(-1, 1), interval(1, 10), myPow, &interval_algebra::Pow);
    analyzeBinaryMethod(10, 2000, "Pow2", interval(1, 1000), interval(-10, 10), myPow, &interval_algebra::Pow);
    analyzeBinaryMethod(10, 2000, "Pow2", interval(0.001, 1), interval(-10, 10), myPow, &interval_algebra::Pow);
    analyzeBinaryMethod(10, 2000, "Pow2", interval(0.001, 10), interval(-20, 20), myPow, &interval_algebra::Pow);
}
}  // namespace itv
