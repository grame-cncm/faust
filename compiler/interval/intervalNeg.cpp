#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// negation, invert sign of an interval

interval interval_algebra::Neg(const interval& x) const
{
    if (x.isEmpty()) return {};

    return {-x.hi(), -x.lo()};
}

void interval_algebra::testNeg() const
{
    check("test algebra Neg", Neg(interval(-1, 1)), interval(-1, 1));
    check("test algebra Neg", Neg(interval(-10, 1)), interval(-1, 10));
}
}  // namespace itv
