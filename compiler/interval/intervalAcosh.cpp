#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Acosh
// interval Acosh(const interval& x) const;
// void testAcosh() const;

static const interval domain(1, HUGE_VAL);

interval interval_algebra::Acosh(const interval& x) const
{
    interval i = intersection(domain, x);
    if (i.isEmpty()) return i;
    return {acosh(i.lo()), acosh(i.hi())};
}

void interval_algebra::testAcosh() const
{
    analyzeUnaryMethod(10, 1000, "acosh", interval(1, 1000), acosh, &interval_algebra::Acosh);
    analyzeUnaryMethod(10, 1000, "acosh", interval(0, 10), acosh, &interval_algebra::Acosh);
}
}  // namespace itv
