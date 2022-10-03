#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Cos
// interval Cos(const interval& x) const;
// void testCos() const;

interval interval_algebra::Cos(const interval& x) const
{
    double TWOPI = 2 * M_PI;

    if (x.isEmpty()) return {};
    if (x.size() >= TWOPI) return {-1, 1};

    // normalize input interval between 0..4PI
    double l = fmod(x.lo(), TWOPI);
    if (l < 0) l += TWOPI;
    interval i(l, l + x.size());

    // compute the default boundaries
    double a  = cos(i.lo());
    double b  = cos(i.hi());
    double lo = std::min(a, b);
    double hi = std::max(a, b);

    // check if n*PI are included
    if (i.has(0) || i.has(2 * M_PI)) hi = 1;
    if (i.has(M_PI) || i.has(3 * M_PI)) lo = -1;

    return {lo, hi};
}

void interval_algebra::testCos() const
{
    analyzeUnaryMethod(20, 2000, "cos", interval(-10 * M_PI, 10 * M_PI), cos, &interval_algebra::Cos);
}
}  // namespace itv
