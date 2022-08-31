#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Le
// interval Le(const interval& x, const interval& y) const;
// void testLe() const;

interval interval_algebra::Le(const interval& x, const interval& y) const
{
    return Ge(y, x);
}

void interval_algebra::testLe() const
{
    check("test algebra Le", Le(interval(5), interval(5)), interval(1));
    check("test algebra Le", Le(interval(2, 5), interval(0, 1)), interval(0));
    check("test algebra Le", Le(interval(-1, 1), interval(0, 10)), interval(0, 1));
}
}  // namespace itv
