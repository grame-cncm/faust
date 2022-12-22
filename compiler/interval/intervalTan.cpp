#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Tan
// interval Tan(const interval& x) const;
// void testTan() const;

interval interval_algebra::Tan(const interval& x) const
{
    double TWOPI = 2 * M_PI;

    if (x.isEmpty()) return x;
    if (x.size() >= TWOPI) return {};  // we have undefined values

    // normalize input interval between 0..4PI
    double l = fmod(x.lo(), TWOPI);
    if (l < 0) l += TWOPI;
    interval i(l, l + x.size());

    if (i.has(M_PI_2) || i.has(3 * M_PI_2) || i.has(5 * M_PI_2) || i.has(7 * M_PI_2)) {
        return {};  //  we have undefined values
    }

    double a  = tan(i.lo());
    double b  = tan(i.hi());
    double lo = std::min(a, b);
    double hi = std::max(a, b);
    return {lo, hi};
}

void interval_algebra::testTan() const
{
    analyzeUnaryMethod(20, 2000, "tan", interval(-M_PI_2, M_PI_2), tan, &interval_algebra::Tan);
}
}  // namespace itv
