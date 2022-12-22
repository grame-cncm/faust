#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Min
// interval Min(const interval& x) const;
// void testMin() const;

interval interval_algebra::Min(const interval& x, const interval& y) const
{
    if (x.isEmpty() || y.isEmpty()) return {};

    return {std::min(x.lo(), y.lo()), std::min(x.hi(), y.hi())};
}

void interval_algebra::testMin() const
{
    check("test algebra Min", Min(interval(0, 5), interval(-3, 10)), interval(-3, 5));
    check("test algebra Min", Min(interval(0, 5), interval(-3, -3)), interval(-3, -3));
}
}  // namespace itv
