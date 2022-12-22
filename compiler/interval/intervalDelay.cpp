#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Delay
// interval Delay(const interval& x) const;
// void testDelay() const;

interval interval_algebra::Delay(const interval& x, const interval& y) const
{
    if (x.isEmpty() || y.isEmpty()) return {};
    if (y.isZero()) return x;
    return reunion(x, interval{0});
}

void interval_algebra::testDelay() const
{
    check("test algebra Delay", Delay(interval(5), interval(0, 10)), interval(0, 5));
    check("test algebra Delay", Delay(interval(5), interval(0)), interval(5));
    check("test algebra Delay", Delay(interval(-1, 1), interval(0, 10)), interval(-1, 1));
}
}  // namespace itv
