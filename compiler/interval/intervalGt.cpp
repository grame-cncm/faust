#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Gt
// interval Gt(const interval& x, const interval& y) const;
// void testGt() const;

interval interval_algebra::Gt(const interval& x, const interval& y) const
{
    if (x.isEmpty() || y.isEmpty()) return interval{};
    if (x.lo() > y.hi()) return interval{1};
    if (x.hi() <= y.lo()) return interval{0};
    return interval{0, 1};
}

void interval_algebra::testGt() const
{
    check("test algebra Gt", Gt(interval(5), interval(5)), interval(0));
    check("test algebra Gt", Gt(interval(2, 5), interval(0, 1)), interval(1));
    check("test algebra Gt", Gt(interval(2, 5), interval(0, 2)), interval(0, 1));
    check("test algebra Gt", Gt(interval(2, 5), interval(5, 20)), interval(0));
    check("test algebra Gt", Gt(interval(2, 5), interval(0, 20)), interval(0, 1));
}
}  // namespace itv
