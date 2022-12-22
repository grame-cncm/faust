#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Lt
// interval Lt(const interval& x, const interval& y) const;
// void testLt() const;

interval interval_algebra::Lt(const interval& x, const interval& y) const
{
    return Gt(y, x);
}

void interval_algebra::testLt() const
{
    check("test algebra Lt", Lt(interval(5), interval(6, 10)), interval(1));
    check("test algebra Lt", Lt(interval(2, 5), interval(0, 2)), interval(0));
    check("test algebra Lt", Lt(interval(-1, 1), interval(0, 10)), interval(0, 1));
}
}  // namespace itv
