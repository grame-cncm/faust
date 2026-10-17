#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Structural value attributes. Unknown external domains must remain visible
// as invalidity; value passthrough and joins must not invent zero constants.

interval interval_algebra::numericFixPointUpdate(const interval& x, const interval& y) const
{
    return reunion(x, y);
}
// An audio input has no assumed range : a host may send any value through it (a control
// voltage, a frequency, a phase), and the intervals state what is guaranteed, never a
// convention. Sound files, normally bounded, keep [-1, 1] (SoundFileBuffer).
interval interval_algebra::numericInput(const interval& c) const
{
    return interval(-HUGE_VAL, HUGE_VAL);
}
interval interval_algebra::numericOutput(const interval& c, const interval& y) const
{
    return y;
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
interval interval_algebra::numericHBargraph(const interval& name, const interval& lo, const interval& hi,
                                     const interval& signal) const
{
    return signal;
}
interval interval_algebra::numericVBargraph(const interval& name, const interval& lo, const interval& hi,
                                     const interval& signal) const
{
    return signal;
}
// Effect and control operands influence scheduling but not the values produced
// by the first operand, so all three wrappers preserve its range.
interval interval_algebra::numericAttach(const interval& x, const interval& y) const
{
    return x;
}
interval interval_algebra::numericEnable(const interval& x, const interval& control) const
{
    return x;
}
interval interval_algebra::numericControl(const interval& x, const interval& control) const
{
    return x;
}
interval interval_algebra::numericAssertBounds(const interval& lo, const interval& hi, const interval& x) const
{
    if (lo.isEmpty() || hi.isEmpty() || x.isEmpty()) {
        return empty();
    }
    // Every admissible bound lies inside [lo.lo(), hi.hi()], so intersecting
    // that envelope with the candidate range remains a sound refinement.
    return intersection(x, interval(lo.lo(), hi.hi(), std::min(lo.lsb(), hi.lsb())));
}
interval interval_algebra::numericHighest(const interval& x) const
{
    return x.isEmpty() ? empty() : interval(x.hi());
}
interval interval_algebra::numericLowest(const interval& x) const
{
    return x.isEmpty() ? empty() : interval(x.lo());
}
interval interval_algebra::numericBitCast(const interval& x) const
{
    return x.isEmpty() ? empty() : interval(-2147483648.0, 2147483647.0, 0);
}
interval interval_algebra::numericSelect2(const interval& x, const interval& y, const interval& z) const
{
    // a selector of one value chooses its branch : the program converts it to an integer
    if (!x.isEmpty() && x.lo() == x.hi()) return (std::trunc(x.lo()) == 0) ? y : z;
    return reunion(y, z);
}
interval interval_algebra::numericPrefix(const interval& x, const interval& y) const
{
    return reunion(x, y);
}
interval interval_algebra::numericRDTbl(const interval& wtbl, const interval& ri) const
{
    // This value domain does not retain table extent. Without that metadata,
    // the upper index bound cannot be certified; the compiler must supply it.
    return wtbl.withInvalid(true);
}
interval interval_algebra::numericWRTbl(const interval& n, const interval& g, const interval& wi,
                                 const interval& ws) const
{
    // Table values are initialized by g and subsequently written from ws.
    // Validate the write against the size before certifying this value attribute.
    const interval indices = IntCast(wi);
    const bool bad = n.isEmpty() || !n.isconst() || n.lo() <= 0 ||
                     n.lsb() < 0 || indices.isEmpty() || indices.lo() < 0 ||
                     indices.hi() >= n.lo();
    return reunion(g, ws).withInvalid(bad || indices.mayBeInvalid());
}
interval interval_algebra::numericGen(const interval& x) const
{
    return x;
}

interval interval_algebra::numericSoundFile(const interval& label) const
{
    return interval(0, 2147483647.0, 0);
}
interval interval_algebra::numericSoundFileRate(const interval& sf, const interval& x) const
{
    return interval(0, 2147483647.0, 0);
}
interval interval_algebra::numericSoundFileLength(const interval& sf, const interval& x) const
{
    return interval(0, 2147483647.0, 0);
}
interval interval_algebra::numericSoundFileBuffer(const interval& sf, const interval& x, const interval& y,
                                           const interval& z) const
{
    return interval(-1, 1);  // the declared soundfile sample domain
}
interval interval_algebra::numericWaveform(const std::vector<interval>& w) const
{
    interval result = empty();
    for (const interval& value : w) result = reunion(result, value);
    return result;
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
interval interval_algebra::numericForeignFunction(int resultNature,
                                          const std::vector<interval>& args) const
{
    // A foreign function has no domain/result contract in this interface.
    return interval(resultNature == 0 ? -2147483648.0 : -HUGE_VAL,
                    resultNature == 0 ? 2147483647.0 : HUGE_VAL,
                    resultNature == 0 ? 0 : -24, true);
}
interval interval_algebra::numericForeignVar(int declaredNature, const interval& name,
                                      const interval& file) const
{
    // Integer storage cannot contain NaN; unknown floating storage can.
    return interval(declaredNature == 0 ? -2147483648.0 : -HUGE_VAL,
                    declaredNature == 0 ? 2147483647.0 : HUGE_VAL,
                    declaredNature == 0 ? 0 : -24, declaredNature != 0);
}
interval interval_algebra::numericForeignConst(int declaredNature, const interval& name,
                                        const interval& file) const
{
    return interval(declaredNature == 0 ? -2147483648.0 : -HUGE_VAL,
                    declaredNature == 0 ? 2147483647.0 : HUGE_VAL,
                    declaredNature == 0 ? 0 : -24, declaredNature != 0);
}

}  // namespace itv
