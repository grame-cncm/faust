#include <algorithm>
#include <functional>
#include <random>

#include "bitwiseOperations.hh"
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
    int x0 = int(x.lo());
    int x1 = int(x.hi());
    int y0 = int(y.lo());
    int y1 = int(y.hi());

    SInterval z = bitwiseSignedOr({x0, x1}, {y0, y1});
    return {double(z.lo), double(z.hi)};
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
