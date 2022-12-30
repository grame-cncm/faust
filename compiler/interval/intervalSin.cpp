#include <algorithm>
#include <cmath>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Sin
// interval Sin(const interval& x) const;
// void testSin() const;

interval interval_algebra::Sin(const interval& x) const
{
    double TWOPI = 2 * M_PI;
    if (x.size() >= TWOPI) return {-1, 1};

    // normalize input interval between 0..4PI
    double l = fmod(x.lo(), TWOPI);
    if (l < 0) l += TWOPI;
    interval i(l, l + x.size());

    // compute the default boundaries
    double a  = sin(i.lo());
    double b  = sin(i.hi());
    double lo = std::min(a, b);
    double hi = std::max(a, b);

    // check if n*PI are included
    if (i.has(M_PI_2) || i.has(5 * M_PI_2)) hi = 1;
    if (i.has(3 * M_PI_2) || i.has(7 * M_PI_2)) lo = -1;

    return {lo, hi};
}

void interval_algebra::testSin() const
{
    analyzeUnaryMethod(20, 2000, "sin", interval(-10 * M_PI, 10 * M_PI), sin, &interval_algebra::Sin);
}
}  // namespace itv
