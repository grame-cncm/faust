#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval FloatCast
// interval FloatCast(const interval& x) const;
// void testFloatCast() const;

interval interval_algebra::FloatCast(const interval& x) const
{
    return x;
}

void interval_algebra::testFloatCast() const
{
    std::cout << "OK: FloatCast no tests needed" << std::endl;
}
}  // namespace itv
