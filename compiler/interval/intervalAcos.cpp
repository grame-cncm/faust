#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Acos
// interval Acos(const interval& x) const;
// void testAcos() const;

static const interval AcosDomain(-1, 1);

interval interval_algebra::Acos(const interval& x) const
{
    interval i = intersection(AcosDomain, x);
    if (i.isEmpty()) return i;
    return {acos(i.hi()), acos(i.lo())};
}

void interval_algebra::testAcos() const
{
    analyzeUnaryMethod(10, 1000, "acos", interval(-1, 1), acos, &interval_algebra::Acos);
}
}  // namespace itv