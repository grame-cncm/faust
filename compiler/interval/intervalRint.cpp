#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Rint
// interval Rint(const interval& x) const;
// void testRint() const;

interval interval_algebra::Rint(const interval& x) const
{
    return {rint(x.lo()), rint(x.hi())};
}

void interval_algebra::testRint() const
{
    check("test algebra Rint", Rint(interval(-3.1, 5.9)), interval(-3, 6));
}
}  // namespace itv
