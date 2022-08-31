#include <algorithm>
#include <cmath>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Lsh
// interval Lsh(const interval& x, const interval& y) const;
// void testLsh() const;

interval interval_algebra::Lsh(const interval& x, const interval& y) const
{
    interval j{pow(2, y.lo()), pow(2, y.hi())};
    return Mul(x, j);
}

void interval_algebra::testLsh() const
{
    check("test algebra Lsh", Lsh(interval(0, 1), interval(4)), interval(0, 16));
    check("test algebra Lsh", Lsh(interval(0.5, 1), interval(-1, 4)), interval(0.25, 16));
    check("test algebra Lsh", Lsh(interval(-10, 10), interval(-1, 4)), interval(-160, 160));
}
}  // namespace itv
