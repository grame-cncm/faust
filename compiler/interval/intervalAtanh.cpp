#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Atanh
// Calculates the inverse hyperbolic tangent of x; that is the value whose hyperbolic tangent is x.
// interval Atanh(const interval& x) const;
// void testAtanh() const;

static const interval domain(std::nexttoward(-1, 0), std::nexttoward(1, 0));  // interval ]-1,1[

interval interval_algebra::Atanh(const interval& x) const
{
    interval i = intersection(domain, x);
    if (i.isEmpty()) return i;
    return {atanh(i.lo()), atanh(i.hi())};
}

void interval_algebra::testAtanh() const
{
    analyzeUnaryMethod(10, 1000, "atanh", interval(-0.999, 0.999), atanh, &interval_algebra::Atanh);
}
}  // namespace itv
