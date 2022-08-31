#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Or
// interval Or(const interval& x, const interval& y) const;
// void testOr() const;
static double myOr(double x, double y)
{
    int a = int(x);
    int b = int(y);
    int c = a | b;
    return double(c);
}

// BRUTE FORCE
interval interval_algebra::Or(const interval& x, const interval& y) const
{
    if (x.isEmpty() || y.isEmpty()) return {};
    int x0 = x.lo();
    int x1 = x.hi();
    int y0 = y.lo();
    int y1 = y.hi();

    int z0 = INT32_MAX;
    int z1 = INT32_MIN;

    for (int i = x0; i <= x1; i++) {
        for (int j = y0; j <= y1; j++) {
            int z = i | j;
            if (z < z0) z0 = z;
            if (z > z1) z1 = z;
        }
    }
    return interval(double(z0), double(z1));
}

void interval_algebra::testOr() const
{
    analyzeBinaryMethod(10, 2000, "Or", interval(-1000, -800), interval(127), myOr, &interval_algebra::Or);
    analyzeBinaryMethod(10, 2000, "Or", interval(-1000, -800), interval(123), myOr, &interval_algebra::Or);
    analyzeBinaryMethod(10, 2000, "Or", interval(-128, 128), interval(127), myOr, &interval_algebra::Or);
    analyzeBinaryMethod(10, 2000, "Or", interval(0, 1000), interval(63, 127), myOr, &interval_algebra::Or);
    analyzeBinaryMethod(10, 2000, "Or", interval(-1000, 1000), interval(63, 127), myOr, &interval_algebra::Or);
}
}  // namespace itv
