#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Max
// interval Max(const interval& x) const;
// void testMax() const;

interval interval_algebra::Max(const interval& x, const interval& y) const
{
    if (x.isEmpty() || y.isEmpty()) return {};

    return {std::max(x.lo(), y.lo()), std::max(x.hi(), y.hi())};
}

void interval_algebra::testMax() const
{
    check("test algebra Max", Max(interval(0, 5), interval(-3, 10)), interval(0, 10));
    check("test algebra Max", Max(interval(0, 5), interval(-3, -3)), interval(0, 5));
}
}  // namespace itv
