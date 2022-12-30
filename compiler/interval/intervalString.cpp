#include <string>
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval IntNum

interval interval_algebra::String(const std::string& x) const
{
    return {NAN, NAN, 0};  // a string don't represent numbers, therefore the interval is empty
}
}  // namespace itv
