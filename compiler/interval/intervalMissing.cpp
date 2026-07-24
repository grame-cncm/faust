#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Missing operations. A default implementation is provided for the code to compile. A real
// implementation has to be provided.

interval interval_algebra::Nil() const
{
    return interval(0);
}
interval interval_algebra::FixPointUpdate(const interval& x, const interval& y) const
{
    return interval(0);
}
interval interval_algebra::Input(const interval& c) const
{
    return interval(0);
}
interval interval_algebra::Output(const interval& c, const interval& y) const
{
    return interval(0);
}
/*
interval interval_algebra::Button(const interval& name) const
{
    return interval(0);
}
interval interval_algebra::Checkbox(const interval& name) const
{
    return interval(0);
}
*/
// Bargraphs observe a signal without changing its possible values; their UI
// bounds constrain display only and therefore do not intersect the range.
interval interval_algebra::HBargraph(const interval& name, const interval& lo, const interval& hi,
                                     const interval& signal) const
{
    return signal;
}
interval interval_algebra::VBargraph(const interval& name, const interval& lo, const interval& hi,
                                     const interval& signal) const
{
    return signal;
}
// Effect and control operands influence scheduling but not the values produced
// by the first operand, so all three wrappers preserve its range.
interval interval_algebra::Attach(const interval& x, const interval& y) const
{
    return x;
}
interval interval_algebra::Enable(const interval& x, const interval& control) const
{
    return x;
}
interval interval_algebra::Control(const interval& x, const interval& control) const
{
    return x;
}
interval interval_algebra::AssertBounds(const interval& lo, const interval& hi, const interval& x) const
{
    if (lo.isEmpty() || hi.isEmpty() || x.isEmpty()) {
        return empty();
    }
    // Every admissible bound lies inside [lo.lo(), hi.hi()], so intersecting
    // that envelope with the candidate range remains a sound refinement.
    return intersection(x, interval(lo.lo(), hi.hi(), std::min(lo.lsb(), hi.lsb())));
}
interval interval_algebra::Highest(const interval& x) const
{
    return interval(0);
}
interval interval_algebra::Lowest(const interval& x) const
{
    return interval(0);
}
interval interval_algebra::BitCast(const interval& x) const
{
    return interval(0);
}
interval interval_algebra::Select2(const interval& x, const interval& y, const interval& z) const
{
    return interval(0);
}
interval interval_algebra::Prefix(const interval& x, const interval& y) const
{
    return interval(0);
}
interval interval_algebra::RDTbl(const interval& wtbl, const interval& ri) const
{
    return interval(0);
}
interval interval_algebra::WRTbl(const interval& n, const interval& g, const interval& wi,
                                 const interval& ws) const
{
    return interval(0);
}
interval interval_algebra::Gen(const interval& x) const
{
    return interval(0);
}

interval interval_algebra::SoundFile(const interval& label) const
{
    return interval(0);
}
interval interval_algebra::SoundFileRate(const interval& sf, const interval& x) const
{
    return interval(0);
}
interval interval_algebra::SoundFileLength(const interval& sf, const interval& x) const
{
    return interval(0);
}
interval interval_algebra::SoundFileBuffer(const interval& sf, const interval& x, const interval& y,
                                           const interval& z) const
{
    return interval(0);
}
interval interval_algebra::Waveform(const std::vector<interval>& w) const
{
    return interval(0);
}
/*
interval interval_algebra::VSlider(const interval& name, const interval& init, const interval& lo,
const interval& hi, const interval& step) const
{
    return interval(0);
}
interval interval_algebra::HSlider(const interval& name, const interval& init, const interval& lo,
const interval& hi, const interval& step) const
{
    return interval(0);
}
interval interval_algebra::NumEntry(const interval& name, const interval& init, const interval& lo,
const interval& hi, const interval& step) const
{
    return interval(0);
}

interval interval_algebra::IntNum(int x) const
{
    return interval(0);
}
interval interval_algebra::Int64Num(int64_t x) const
{
    return interval(0);
}
interval interval_algebra::FloatNum(double x) const
{
    return interval(0);
}
interval interval_algebra::Label(const std::string& x) const
{
    return interval(0);
}
*/
// Foreign functions
interval interval_algebra::ForeignFunction(int resultNature,
                                          const std::vector<interval>& args) const
{
    return interval(0);
}
interval interval_algebra::ForeignVar(int declaredNature, const interval& name,
                                      const interval& file) const
{
    return interval(0);
}
interval interval_algebra::ForeignConst(int declaredNature, const interval& name,
                                        const interval& file) const
{
    return interval(0);
}

}  // namespace itv
