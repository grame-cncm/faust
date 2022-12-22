#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Float
// interval Float(const interval& x) const;
// void testFloat() const;

interval interval_algebra::Float(const interval& x) const
{
    return x;
}

void interval_algebra::testFloat() const
{
    std::cout << "OK: Float no tests needed" << std::endl;
}
}  // namespace itv
