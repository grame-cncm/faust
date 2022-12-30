#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval IntCast
// interval IntCast(const interval& x) const;
// void testIntCast() const;

// restrict to integer range

interval interval_algebra::IntCast(const interval& x) const
{
    if (x.isEmpty()) return {};
    return {double(saturatedIntCast(x.lo())), double(saturatedIntCast(x.hi())), 0};  // integer intervals have 0 bits of precision
}

void interval_algebra::testIntCast() const
{
    check("test algebra IntCast", IntCast(interval{-3.8, 4.9}), interval{-3.0, 4.0, 0});
    check("test algebra IntCast", IntCast(interval{-HUGE_VAL, HUGE_VAL}), interval{-2147483648.0, 2147483647.0, 0});
}
}  // namespace itv
