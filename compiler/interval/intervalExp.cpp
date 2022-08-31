#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Exp
// interval Exp(const interval& x) const;
// void testExp() const;

interval interval_algebra::Exp(const interval& x) const
{
    if (x.isEmpty()) return x;
    return {exp(x.lo()), exp(x.hi())};
}

void interval_algebra::testExp() const
{
    analyzeUnaryMethod(10, 1000, "exp", interval(-100, 10), exp, &interval_algebra::Exp);
}
}  // namespace itv
