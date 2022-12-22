#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Floor
// interval Floor(const interval& x) const;
// void testFloor() const;

interval interval_algebra::Floor(const interval& x) const
{
    if (x.isEmpty()) return {};
    return {floor(x.lo()), floor(x.hi())};
}

void interval_algebra::testFloor() const
{
    analyzeUnaryMethod(10, 1000, "floor", interval(-10, 10), floor, &interval_algebra::Floor);
}
}  // namespace itv
