#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval IntNum

interval interval_algebra::FloatNum(double x) const
{
    return {x, x, -24};
}
}  // namespace itv
