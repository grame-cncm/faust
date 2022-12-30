#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval IntNum

interval interval_algebra::Checkbox(const interval& name) const
{
    return {0, 1, 0};
}
}  // namespace itv
