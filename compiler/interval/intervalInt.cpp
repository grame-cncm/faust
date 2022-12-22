#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Int
// interval Int(const interval& x) const;
// void testInt() const;

interval interval_algebra::Int(const interval& x) const
{
    if (x.isEmpty()) return {};
    auto a = int(x.lo());
    auto b = int(x.hi());
    return {double(a), double(b)};
}

void interval_algebra::testInt() const
{
    std::cout << "OK: Int no tests needed" << std::endl;
}
}  // namespace itv
