#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Rsh
// interval Rsh(const interval& x, const interval& y) const;
// void testRsh() const;

interval interval_algebra::Rsh(const interval& x, const interval& y) const
{
    interval j{pow(2, -y.hi()), pow(2, -y.lo())};
    return Mul(x, j);
}

void interval_algebra::testRsh() const
{
    check("test algebra Rsh", Rsh(interval(8, 16), interval(4)), interval(0.5, 1));
}
}  // namespace itv
