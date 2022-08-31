#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Atan
// Calculates the principal value of the arc tangent of x; that is the value whose tangent is x.
// The return value is in the range [-pi/2, pi/2].

// interval Atan(const interval& x) const;
// void testAtan() const;

interval interval_algebra::Atan(const interval& x) const
{
    if (x.isEmpty()) return x;
    return {atan(x.lo()), atan(x.hi())};
}

void interval_algebra::testAtan() const
{
    analyzeUnaryMethod(10, 1000, "atan", interval(-100, 100), atan, &interval_algebra::Atan);
}
}  // namespace itv
