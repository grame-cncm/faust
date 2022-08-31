#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Eq
// interval Eq(const interval& x, const interval& y) const;
// void testEq() const;

interval interval_algebra::Eq(const interval& x, const interval& y) const
{
    if (x.isEmpty() || y.isEmpty()) return interval{};
    if (x.lo() == x.hi() && x.lo() == y.lo() && x.lo() == y.hi()) return interval{1};
    if (x.hi() < y.lo() || x.lo() > y.hi()) return interval{0};
    return interval{0, 1};
}

void interval_algebra::testEq() const
{
    check("test algebra Eq", Eq(interval(5), interval(5)), interval(1));
    check("test algebra Eq", Eq(interval(2, 5), interval(0, 1)), interval(0));
    check("test algebra Eq", Eq(interval(-1, 1), interval(0, 10)), interval(0, 1));
}
}  // namespace itv
