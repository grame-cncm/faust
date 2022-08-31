#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Asinh
// interval Asinh(const interval& x) const;
// void testAsinh() const;
static const interval domain(-HUGE_VAL, HUGE_VAL);

interval interval_algebra::Asinh(const interval& x) const
{
    return {asinh(x.lo()), asinh(x.hi())};
}

void interval_algebra::testAsinh() const
{
    analyzeUnaryMethod(10, 1000, "asinh", interval(-10, 10), asinh, &interval_algebra::Asinh);
}
}  // namespace itv
