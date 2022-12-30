#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval IntNum

interval interval_algebra::IntNum(int x) const
{
    return {double(x), double(x), 0};
}
}  // namespace itv
