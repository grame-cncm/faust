#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Atan2
// interval Atan2(const interval& x, const interval& y) const;
// void testAtan2() const;

interval interval_algebra::Atan2(const interval& x, const interval& y) const
{
    return {};
}

void interval_algebra::testAtan2() const
{
    std::cout << "Atan2 not implemented" << std::endl;
}
}  // namespace itv