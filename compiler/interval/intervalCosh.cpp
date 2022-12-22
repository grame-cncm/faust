#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Cosh
// interval Cosh(const interval& x) const;
// void testCosh() const;

interval interval_algebra::Cosh(const interval& x) const
{
    if (x.isEmpty()) return x;
    if (x.hasZero()) return {1, std::max(cosh(x.lo()), cosh(x.hi()))};

    return {std::min(cosh(x.lo()), cosh(x.hi())), std::max(cosh(x.lo()), cosh(x.hi()))};
}

void interval_algebra::testCosh() const
{
    analyzeUnaryMethod(10, 1000, "cosh", interval(-10, 10), cosh, &interval_algebra::Cosh);
}
}  // namespace itv
