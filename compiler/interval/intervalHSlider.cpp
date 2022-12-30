#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval IntNum

interval interval_algebra::HSlider(const interval& name, const interval& init, const interval& lo, const interval& hi,
                                   const interval& step) const
{
    return {lo.lo(), hi.hi(), -24};  // TODO: step, init
}
}  // namespace itv
