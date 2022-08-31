#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Ge
// interval Ge(const interval& x, const interval& y) const;
// void testGe() const;

interval interval_algebra::Ge(const interval& x, const interval& y) const
{
    if (x.isEmpty() || y.isEmpty()) return interval{};
    if (x.lo() >= y.hi()) return interval{1};
    if (x.hi() < y.lo()) return interval{0};
    return interval{0, 1};
}

void interval_algebra::testGe() const
{
    check("test algebra Ge", Ge(interval(5), interval(5)), interval(1));
    check("test algebra Ge", Ge(interval(2, 5), interval(0, 1)), interval(1));
    check("test algebra Ge", Ge(interval(-1, 1), interval(0, 10)), interval(0, 1));
}
}  // namespace itv
