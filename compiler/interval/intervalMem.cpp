#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Mem
// interval Mem(const interval& x) const;
// void testMem() const;

interval interval_algebra::Mem(const interval& x) const
{
    if (x.isEmpty()) return {};
    return reunion(x, interval{0});
}

void interval_algebra::testMem() const
{
    check("test algebra Mem", Mem(interval(5)), interval(0, 5));
    check("test algebra Mem", Mem(interval(-1, 1)), interval(-1, 1));
}
}  // namespace itv
