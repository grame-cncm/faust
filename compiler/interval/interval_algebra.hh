#pragma once

#include <vector>
#include "interval_def.hh"

#include "FaustAlgebra.hh"

namespace itv {

/// A certified bound of the gain of the stable recursive filter
/// y(n) = x(n) + sum_j c[j] y(n-1-j) (intervalKernel.cpp) : L bounds the L1 norm of its
/// impulse response h ; pos and neg are the sums of the positive and negative computed
/// values of its first `block` samples, within `spread` (their error and the rest of h).
struct FilterGain {
    double L, pos, neg, spread;
    long   block;
};
/// false when no bound can be certified (an unstable, too slow or too imprecise filter)
bool filterGain(const std::vector<double>& c, FilterGain& gain);
/// mix(c, a, b) = (1 - c) * a + c * b is computed as an interpolation from the operand
/// whose weight may be near 1 : b + (1 - c) * (a - b) when c >= 1/2 (1 - c is then exact,
/// Sterbenz), a + c * (b - a) otherwise. The generators and the interval of the node apply
/// this same rule to the interval of c.
inline bool mixFromB(const interval& c)
{
    return !c.isEmpty() && c.lo() >= 0.5;
}

class interval_algebra : public FaustAlgebra<interval> {
   private:
    interval iPow(const interval& x, const interval& y) const;  // integer power, when x can be negative
    interval fPow(const interval& x, const interval& y) const;  // float power, when x is positive

   public:
    // Public API: every transfer preserves incoming mayBeInvalid alerts and marks
    // possible domain violations. Numeric emptiness never clears those alerts.
    // Bounds remain conservative; the sign of LSB alone still identifies nature.
    // Injections of external values
    // Public API: IntNum encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval IntNum(int x) const override;
    // Public API: Int64Num encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Int64Num(int64_t x) const override;
    // Public API: inject a known literal as a point, rounded once to binary32 in float
    // mode. Float/double retain floating nature even for integral-looking literals;
    // quad/fixed keep legacy injection. Explicit literals need no analyzer-error widening.
    // NaN literals have empty numeric bounds and mayBeInvalid set.
    // Public API: FloatNum encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval FloatNum(double x) const override;
    // Public API: Label encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Label(const std::string& x) const override;

    // Structural operations
    // Public API: FixPointUpdate encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval FixPointUpdate(const interval& x, const interval& y) const override;
    // Public API: Input encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Input(const interval& c) const override;
    // Public API: Output encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Output(const interval& c, const interval& y) const override;
    // Public API: HBargraph encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval HBargraph(const interval& name, const interval& lo, const interval& hi,
                       const interval& signal) const override;
    // Public API: VBargraph encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval VBargraph(const interval& name, const interval& lo, const interval& hi,
                       const interval& signal) const override;
    // Public API: Gen encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Gen(const interval& x) const override;
    // Public API: Attach encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Attach(const interval& x, const interval& y) const override;
    // Public API: Enable encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Enable(const interval& x, const interval& control) const override;
    // Public API: Control encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Control(const interval& x, const interval& control) const override;
    // Public API: AssertBounds encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval AssertBounds(const interval& lo, const interval& hi, const interval& x) const override;
    // Public API: Highest encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Highest(const interval& x) const override;
    // Public API: Lowest encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Lowest(const interval& x) const override;
    // Public API: BitCast encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval BitCast(const interval& x) const override;
    // Public API: Select2 encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Select2(const interval& x, const interval& y, const interval& z) const override;
    // Public API: Prefix encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Prefix(const interval& x, const interval& y) const override;
    // Public API: RDTbl encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval RDTbl(const interval& wtbl, const interval& ri) const override;
    // Public API: WRTbl encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval WRTbl(const interval& n, const interval& g, const interval& wi,
                   const interval& ws) const override;
    // Public API: SoundFile encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval SoundFile(const interval& label) const override;
    // Public API: SoundFileRate encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval SoundFileRate(const interval& sf, const interval& x) const override;
    // Public API: SoundFileLength encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval SoundFileLength(const interval& sf, const interval& x) const override;
    // Public API: SoundFileBuffer encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval SoundFileBuffer(const interval& sf, const interval& x, const interval& y,
                             const interval& z) const override;
    // Public API: Waveform encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Waveform(const std::vector<interval>& w) const override;

    // Foreign functions
    // Public API: ForeignFunction encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval ForeignFunction(int resultNature, const std::vector<interval>& args) const override;
    // Public API: ForeignVar encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval ForeignVar(int declaredNature, const interval& name,
                        const interval& file) const override;
    // Public API: ForeignConst encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval ForeignConst(int declaredNature, const interval& name,
                          const interval& file) const override;

    // User interface elements
    // Public API: Button encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Button(const interval& name) const override;
    // Public API: Checkbox encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Checkbox(const interval& name) const override;
    // Public API: VSlider encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval VSlider(const interval& name, const interval& init, const interval& lo,
                     const interval& hi, const interval& step) const override;
    // Public API: HSlider encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval HSlider(const interval& name, const interval& init, const interval& lo,
                     const interval& hi, const interval& step) const override;
    // Public API: NumEntry encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval NumEntry(const interval& name, const interval& init, const interval& lo,
                      const interval& hi, const interval& step) const override;

    // Public API: enclose wrapping int32 absolute value or floating absolute value.
    // Empty stays empty. Normalize widened integer corridors before endpoint work;
    // the result retains the input nature, including integral-valued floating zero.
    // Public API: Abs encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Abs(const interval& x) const override;
    void     testAbs();
    //
    // Public API: enclose addition; float/double floating bounds round outward at each
    // endpoint, while the existing int32 wrapping and other precision paths remain.
    // Public API: Add encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Add(const interval& x, const interval& y) const override;
    void     testAdd();
    //
    // Public API: enclose subtraction; float/double floating bounds round outward at each
    // endpoint, while the existing int32 wrapping and other precision paths remain.
    // Public API: Sub encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Sub(const interval& x, const interval& y) const override;
    void     testSub();
    //
    // Public API: enclose multiplication; float/double floating corners round outward.
    // Zero times an unbounded endpoint keeps the historical numeric-hull convention;
    // possible NaN values are additionally marked by mayBeInvalid.
    // Public API: Mul encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Mul(const interval& x, const interval& y) const override;
    void     testMul();
    //
    // Public API: enclose floating division with directly divided endpoints. Float/double
    // bounds round outward; quad/fixed retain their previous evaluation.
    // Empty operands yield empty; zero or an indeterminate infinite corner gives
    // [-inf, +inf]. The LSB estimate remains separate from numeric bound inclusion.
    // Public API: Div encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Div(const interval& x, const interval& y) const override;
    void     testDiv();
    //
    // Public API: reciprocal bounds and their LSB estimate; empty stays empty.
    // Zero gives both signed infinities in float/double (signed zero is not tracked).
    // Float/double reciprocal endpoints
    // round outward; LSB remains an estimate.
    // Public API: Inv encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Inv(const interval& x) const override;
    void     testInv();
    //
    // Public API: enclose wrapping int32 negation or floating sign reversal.
    // Empty stays empty. Normalize widened integer corridors before endpoint work;
    // the result retains the input nature, including integral-valued floating zero.
    // Public API: Neg encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Neg(const interval& x) const override;
    void     testNeg();
    //
    // Public API: Mod encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Mod(const interval& x, double m) const;
    // Public API: integer C modulo for integer operands, otherwise numeric fmod.
    // Float/double floating bounds avoid rounded quotient tests and unsafe int casts;
    // invalid-only domains yield empty; possible domain violations set mayBeInvalid.
    interval Mod(const interval& x, const interval& y) const override;
    // Public API: floating modulo; in float/double, even integer-looking inputs
    // follow fmod rather than C integer modulo. Possible domain violations set mayBeInvalid.
    // Public API: Fmod encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Fmod(const interval& x, const interval& y) const override;
    void     testMod();
    //

    // Public API: Acos encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Acos(const interval& x) const override;
    // Public API: numeric acos image on its valid domain. In float/double,
    // the native kernel encloses endpoints and extrema; quad/fixed retain
    // their historical rule. LSB is an estimate; Possible domain violations set mayBeInvalid.
    // Public API: AcosBounds encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval AcosBounds(const interval& x) const;
    void     testAcos();
    //
    // Public API: Acosh encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Acosh(const interval& x) const override;
    // Public API: numeric acosh image on its valid domain. In float/double,
    // the native kernel encloses endpoints and extrema; quad/fixed retain
    // their historical rule. LSB is an estimate; Possible domain violations set mayBeInvalid.
    // Public API: AcoshBounds encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval AcoshBounds(const interval& x) const;
    void     testAcosh();
    //
    // Public API: enclose int32 bitwise operations after integer conversion.
    // Normalize widened integers before bit analysis; empty stays empty.
    // Floating inputs are truncated and nonempty results remain integer.
    // Public API: And encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval And(const interval& x, const interval& y) const override;
    void     testAnd();
    //
    // Public API: Asin encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Asin(const interval& x) const override;
    // Public API: numeric asin image on its valid domain. In float/double,
    // the native kernel encloses endpoints and extrema; quad/fixed retain
    // their historical rule. LSB is an estimate; Possible domain violations set mayBeInvalid.
    // Public API: AsinBounds encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval AsinBounds(const interval& x) const;
    void     testAsin();
    //
    // Public API: Asinh encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Asinh(const interval& x) const override;
    // Public API: numeric asinh image on its valid domain. In float/double,
    // the native kernel encloses endpoints and extrema; quad/fixed retain
    // their historical rule. LSB is an estimate; Possible domain violations set mayBeInvalid.
    // Public API: AsinhBounds encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval AsinhBounds(const interval& x) const;
    void     testAsinh();
    //
    // Public API: Atan encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Atan(const interval& x) const override;
    // Public API: numeric atan image on its valid domain. In float/double,
    // the native kernel encloses endpoints and extrema; quad/fixed retain
    // their historical rule. LSB is an estimate; Possible domain violations set mayBeInvalid.
    // Public API: AtanBounds encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval AtanBounds(const interval& x) const;
    void     testAtan();
    //
    // Public API: Atan2 encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Atan2(const interval& x, const interval& y) const override;
    // Public API: numeric atan2(y, x) image. Float/double endpoints round outward and a
    // possible negative-axis cut covers both signs of pi. Quad/fixed retain
    // their historical rule; LSB is an estimate and Possible domain violations set mayBeInvalid.
    // Public API: Atan2Bounds encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Atan2Bounds(const interval& y, const interval& x) const;
    void     testAtan2();
    //
    // Public API: Atanh encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Atanh(const interval& x) const override;
    // Public API: numeric atanh image on its valid domain. In float/double,
    // the native kernel encloses endpoints and extrema; quad/fixed retain
    // their historical rule. LSB is an estimate; Possible domain violations set mayBeInvalid.
    // Public API: AtanhBounds encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval AtanhBounds(const interval& x) const;
    void     testAtanh();
    //
    // Public API: numeric ceil image; empty stays empty, and integer inputs
    // first convert to the target float. Results keep floating nature in every precision,
    // so subsequent operations cannot incorrectly enter the int32 wrapping branch.
    // Public API: Ceil encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Ceil(const interval& x) const override;
    void     testCeil();
    // Public API: Cos encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Cos(const interval& x) const override;
    // Public API: numeric cos image on its valid domain. In float/double,
    // the native kernel encloses endpoints and extrema; quad/fixed retain
    // their historical rule. LSB is an estimate; Possible domain violations set mayBeInvalid.
    // Public API: CosBounds encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval CosBounds(const interval& x) const;
    void     testCos();
    // Public API: Cosh encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Cosh(const interval& x) const override;
    // Public API: numeric cosh image on its valid domain. In float/double,
    // the native kernel encloses endpoints and extrema; quad/fixed retain
    // their historical rule. LSB is an estimate; Possible domain violations set mayBeInvalid.
    // Public API: CoshBounds encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval CoshBounds(const interval& x) const;
    void     testCosh();
    // Public API: enclose Delay after int32 conversion of the sample count.
    // Exactly zero preserves bounds and LSB; possibly positive counts include
    // initial zero. Retain invalidity of either operand and the delay domain.
    interval Delay(const interval& x, const interval& y) const override;
    void     testDelay();
    // Public API: enclose comparison after target operand conversions.
    // Normalize widened integers before deciding a predicate.
    // Empty stays empty; a nonempty result is integer zero, one or both.
    // Public API: Eq encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Eq(const interval& x, const interval& y) const override;
    void     testEq();
    // Public API: Exp encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Exp(const interval& x) const override;
    // Public API: numeric exp image on its valid domain. In float/double,
    // the native kernel encloses endpoints and extrema; quad/fixed retain
    // their historical rule. LSB is an estimate; Possible domain violations set mayBeInvalid.
    // Public API: ExpBounds encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval ExpBounds(const interval& x) const;
    void     testExp();
    // Public API: Exp10 encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Exp10(const interval& x) const override;
    // Public API: enclose conversion to the program's floating type. In float mode,
    // convert the source endpoints once; IEEE narrowing is monotone. This is a known
    // conversion, not a bound calculation with an unknown analyzer rounding residual.
    // Normalize widened integer sources before conversion, retaining a negative
    // floating LSB in every precision. Invalidity is retained independently of the numeric bounds.
    // Public API: FloatCast encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval FloatCast(const interval& x) const override;
    void     testFloatCast();
    // Public API: numeric floor image; empty stays empty, and integer inputs
    // first convert to the target float. Results keep floating nature in every precision,
    // so subsequent operations cannot incorrectly enter the int32 wrapping branch.
    // Public API: Floor encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Floor(const interval& x) const override;
    void     testFloor();
    // Public API: enclose comparison after target operand conversions.
    // Normalize widened integers before deciding a predicate.
    // Empty stays empty; a nonempty result is integer zero, one or both.
    // Public API: Ge encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Ge(const interval& x, const interval& y) const override;
    void     testGe();
    // Public API: enclose comparison after target operand conversions.
    // Normalize widened integers before deciding a predicate.
    // Empty stays empty; a nonempty result is integer zero, one or both.
    // Public API: Gt encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Gt(const interval& x, const interval& y) const override;
    void     testGt();
    // Public API: IntCast encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    // Truncation must fit int32; invalid-only inputs give numeric bottom with an
    // alert, and partially invalid inputs keep their valid truncated image.
    interval IntCast(const interval& x) const override;
    void     testIntCast();
    // Public API: enclose comparison after target operand conversions.
    // Normalize widened integers before deciding a predicate.
    // Empty stays empty; a nonempty result is integer zero, one or both.
    // Public API: Le encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Le(const interval& x, const interval& y) const override;
    void     testLe();
    // Public API: Log encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Log(const interval& x) const override;
    // Public API: numeric log image on its valid domain. In float/double,
    // the native kernel encloses endpoints and extrema; quad/fixed retain
    // their historical rule. LSB is an estimate; Possible domain violations set mayBeInvalid.
    // Public API: LogBounds encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval LogBounds(const interval& x) const;
    void     testLog();
    // Public API: Log10 encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Log10(const interval& x) const override;
    // Public API: numeric log10 image on its valid domain. In float/double,
    // the native kernel encloses endpoints and extrema; quad/fixed retain
    // their historical rule. LSB is an estimate; Possible domain violations set mayBeInvalid.
    // Public API: Log10Bounds encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Log10Bounds(const interval& x) const;
    void     testLog10();
    // Public API: enclose wrapping int32 left shift for counts in [0,31].
    // Convert operands to integers first. Invalid counts have no portable execution
    // contract and conservatively return full int32; this does not define such shifts.
    // Public API: Lsh encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Lsh(const interval& x, const interval& y) const override;
    void     testLsh();
    // Public API: enclose comparison after target operand conversions.
    // Normalize widened integers before deciding a predicate.
    // Empty stays empty; a nonempty result is integer zero, one or both.
    // Public API: Lt encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Lt(const interval& x, const interval& y) const override;
    void     testLt();
    // Public API: enclose maximum after target operand conversions.
    // Empty stays empty; widened integers recover their signed hull.
    // The result is floating exactly when either operand is floating.
    // Public API: Max encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Max(const interval& x, const interval& y) const override;
    void     testMax();
    // Public API: Mem encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Mem(const interval& x) const override;
    void     testMem();
    // Public API: enclose minimum after target operand conversions.
    // Empty stays empty; widened integers recover their signed hull.
    // The result is floating exactly when either operand is floating.
    // Public API: Min encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Min(const interval& x, const interval& y) const override;
    void     testMin();
    // Public API: enclose comparison after target operand conversions.
    // Normalize widened integers before deciding a predicate.
    // Empty stays empty; a nonempty result is integer zero, one or both.
    // Public API: Ne encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Ne(const interval& x, const interval& y) const override;
    void     testNe();
    // Public API: enclose int32 bitwise complement after integer conversion.
    // ~x = -1-x reverses signed order, so endpoints suffice even for full int32;
    // enumerating that range would not terminate. The low bit is always significant.
    // Public API: Not encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Not(const interval& x) const override;
    void     testNot();
    // Public API: enclose int32 bitwise operations after integer conversion.
    // Normalize widened integers before bit analysis; empty stays empty.
    // Floating inputs are truncated and nonempty results remain integer.
    // Public API: Or encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Or(const interval& x, const interval& y) const override;
    void     testOr();
    // Public API: Pow encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Pow(const interval& x, const interval& y) const override;  // for all cases
    // Public API: numeric power image. Float/double floating powers round outward; negative
    // bases use integer exponents by parity. The existing nonnegative integer-power
    // path retains wrapping and LSB estimates. Possible domain violations set mayBeInvalid.
    // Public API: PowBounds encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval PowBounds(const interval& x, const interval& y) const;
    void     testPow();
    // Public API: numeric IEEE remainder image. Float/double half-divisor bounds round
    // outward, including subnormals; invalid-only domains yield empty. Invalidity is
    // tracked by mayBeInvalid; LSB remains an estimate.
    // Public API: Remainder encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Remainder(const interval& x, const interval& y) const override;
    void     testRemainder();
    // Public API: numeric rint image; empty stays empty, and integer inputs
    // first convert to the target float. Results keep floating nature in every precision,
    // so subsequent operations cannot incorrectly enter the int32 wrapping branch.
    // Public API: Rint encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Rint(const interval& x) const override;
    // Public API : the compound operations (FaustAlgebra), each bounded as one
    // operation : Frac(x) = x - floor(x) in [0, 1], Cfrac(x) = x - rint(x) in [-1/2, 1/2],
    // Mix(c, a, b) = (1 - c) a + c b between a and b for c in [0, 1] (intervalCompound.cpp)
    interval Frac(const interval& x) const override;
    interval Cfrac(const interval& x) const override;
    interval Mix(const interval& c, const interval& a, const interval& b) const override;
    // Tpt(x) = x / (x + 1), increasing on ]-1, +inf[ : its image there, the definition
    // elsewhere
    interval Tpt(const interval& x) const override;
    // Phase(x, p) = (x % p) / p : |x % p| < |p| for the same p, so the ratio lies in
    // [0, 1] (x >= 0, p > 0), [-1, 0] or [-1, 1] by the signs, when p excludes 0
    interval Phase(const interval& x, const interval& p) const override;
    // Public API : the kernels (intervalKernel.cpp) : Sum, Prod and Fir as their
    // definitions (a sum and a product from left to right, the association of the code),
    // Iir by the certified gain of a stable filter with constant coefficients, rounding
    // included ; anything, NaN included, otherwise
    interval Sum(const std::vector<interval>& terms) const override;
    interval Prod(const std::vector<interval>& factors) const override;
    interval Fir(const interval& x, const std::vector<interval>& coefs) const override;
    interval Iir(const interval& x, const std::vector<interval>& coefs) const override;
    // Irm(x, c) : the smallest of two intervals that hold 0 (the state before the first
    // sample) and that the mix maps into themselves, Mix(c, x, Y) within Y : the hull of x
    // and 0 widened by a margin, the power-of-two envelope ; anything, NaN included, for a
    // pole beyond [0, 1] or an unbounded x
    interval Irm(const interval& x, const interval& c) const override;
    // Bpf(x, t, r) : the hull of the regions r[i] whose range [t[i-1], t[i][ meets x, the
    // last one also when x may be NaN (every comparison false)
    interval Bpf(const interval& x, const std::vector<interval>& t, const std::vector<interval>& r) const override;
    void     testRint();
    // Public API: numeric round image; empty stays empty, and integer inputs
    // first convert to the target float. Results keep floating nature in every precision,
    // so subsequent operations cannot incorrectly enter the int32 wrapping branch.
    // Public API: Round encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Round(const interval& x) const override;
    void     testRound();
    // Public API: enclose arithmetic int32 right shift for counts in [0,31].
    // Arithmetic shifts round negative quotients downward; real scaling alone can
    // miss the actual integer result. Invalid counts conservatively return full int32.
    // Public API: ARsh encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval ARsh(const interval& x, const interval& y) const override;
    // Public API: enclose logical int32 right shift for counts in [0,31].
    // A positive shift sees the uint32 bit pattern; shift zero retains the original
    // signed value. Split at zero to handle the unsigned ordering discontinuity.
    // Public API: LRsh encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval LRsh(const interval& x, const interval& y) const override;
    void     testRsh();
    // Public API: Sin encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Sin(const interval& x) const override;
    // Public API: numeric sin image on its valid domain. In float/double,
    // the native kernel encloses endpoints and extrema; quad/fixed retain
    // their historical rule. LSB is an estimate; Possible domain violations set mayBeInvalid.
    // Public API: SinBounds encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval SinBounds(const interval& x) const;
    void     testSin();
    // Public API: Sinh encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Sinh(const interval& x) const override;
    // Public API: numeric sinh image on its valid domain. In float/double,
    // the native kernel encloses endpoints and extrema; quad/fixed retain
    // their historical rule. LSB is an estimate; Possible domain violations set mayBeInvalid.
    // Public API: SinhBounds encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval SinhBounds(const interval& x) const;
    void     testSinh();
    // Public API: square-root bounds over x intersected with [0, +inf], with an LSB
    // estimate. An empty domain yields empty; a zero-only domain yields exact zero.
    // Float/double bounds round outward independently of the host libm and rounding mode.
    // Public API: Sqrt encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Sqrt(const interval& x) const override;
    void     testSqrt();
    // Public API: Tan encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Tan(const interval& x) const override;
    // Public API: numeric tan image on its valid domain. In float/double,
    // the native kernel encloses endpoints and extrema; quad/fixed retain
    // their historical rule. LSB is an estimate; Possible domain violations set mayBeInvalid.
    // Public API: TanBounds encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval TanBounds(const interval& x) const;
    void     testTan();
    // Public API: Tanh encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Tanh(const interval& x) const override;
    // Public API: numeric tanh image on its valid domain. In float/double,
    // the native kernel encloses endpoints and extrema; quad/fixed retain
    // their historical rule. LSB is an estimate; Possible domain violations set mayBeInvalid.
    // Public API: TanhBounds encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval TanhBounds(const interval& x) const;
    void     testTanh();
    // Public API: enclose int32 bitwise operations after integer conversion.
    // Normalize widened integers before bit analysis; empty stays empty.
    // Floating inputs are truncated and nonempty results remain integer.
    // Public API: Xor encloses valid numeric results and conservatively retains
    // input invalidity and any possible operation-domain violation.
    interval Xor(const interval& x, const interval& y) const override;
    void     testXor();

    void testAll();

   private:
    // Internal numeric kernels; public transfers add sticky input invalidity and
    // domain checks centrally, so early numeric returns cannot erase an alert.
    interval numericARsh(const interval& input, const interval& counts) const;
    interval numericAbs(const interval& input) const;
    interval numericAcos(const interval& x) const;
    interval numericAcosBounds(const interval& x) const;
    interval numericAcosh(const interval& x) const;
    interval numericAcoshBounds(const interval& x) const;
    interval numericAdd(const interval& xIn, const interval& yIn) const;
    interval numericAnd(const interval& xInput, const interval& yInput) const;
    interval numericAsin(const interval& x) const;
    interval numericAsinBounds(const interval& x) const;
    interval numericAsinh(const interval& x) const;
    interval numericAsinhBounds(const interval& x) const;
    interval numericAssertBounds(const interval& lo, const interval& hi, const interval& x) const;
    interval numericAtan(const interval& x) const;
    interval numericAtan2(const interval& x, const interval& y) const;
    interval numericAtan2Bounds(const interval& y, const interval& x) const;
    interval numericAtanBounds(const interval& x) const;
    interval numericAtanh(const interval& x) const;
    interval numericAtanhBounds(const interval& x) const;
    interval numericAttach(const interval& x, const interval& y) const;
    interval numericBitCast(const interval& x) const;
    interval numericButton(const interval& name) const;
    interval numericCeil(const interval& input) const;
    interval numericCheckbox(const interval& name) const;
    interval numericControl(const interval& x, const interval& control) const;
    interval numericCos(const interval& x) const;
    interval numericCosBounds(const interval& x) const;
    interval numericCosh(const interval& x) const;
    interval numericCoshBounds(const interval& x) const;
    interval numericDelay(const interval& x, const interval& y) const;
    interval numericDiv(const interval& x, const interval& y) const;
    interval numericEnable(const interval& x, const interval& control) const;
    interval numericEq(const interval& xInput, const interval& yInput) const;
    interval numericExp(const interval& x) const;
    interval numericExp10(const interval& x) const;
    interval numericExpBounds(const interval& x) const;
    interval numericFixPointUpdate(const interval& x, const interval& y) const;
    interval numericFloatCast(const interval& input) const;
    interval numericFloatNum(double x) const;
    interval numericFloor(const interval& input) const;
    interval numericFmod(const interval& x, const interval& y) const;
    interval numericForeignConst(int declaredNature, const interval& name, const interval& file) const;
    interval numericForeignFunction(int resultNature, const std::vector<interval>& args) const;
    interval numericForeignVar(int declaredNature, const interval& name, const interval& file) const;
    interval numericGe(const interval& xInput, const interval& yInput) const;
    interval numericGen(const interval& x) const;
    interval numericGt(const interval& xInput, const interval& yInput) const;
    interval numericHBargraph(const interval& name, const interval& lo, const interval& hi, const interval& signal) const;
    interval numericHSlider(const interval& name, const interval& init, const interval& lo, const interval& hi, const interval& step) const;
    interval numericHighest(const interval& x) const;
    interval numericInput(const interval& c) const;
    interval numericInt64Num(int64_t x) const;
    interval numericIntCast(const interval& x) const;
    interval numericIntNum(int x) const;
    interval numericInv(const interval& input) const;
    interval numericLRsh(const interval& input, const interval& counts) const;
    interval numericLabel(const std::string& x) const;
    interval numericLe(const interval& xInput, const interval& yInput) const;
    interval numericLog(const interval& x) const;
    interval numericLog10(const interval& x) const;
    interval numericLog10Bounds(const interval& x) const;
    interval numericLogBounds(const interval& x) const;
    interval numericLowest(const interval& x) const;
    interval numericLsh(const interval& input, const interval& counts) const;
    interval numericLt(const interval& xInput, const interval& yInput) const;
    interval numericMax(const interval& xInput, const interval& yInput) const;
    interval numericMem(const interval& x) const;
    interval numericMin(const interval& xInput, const interval& yInput) const;
    interval numericMod(const interval& xIn, const interval& yIn) const;
    interval numericMul(const interval& xIn, const interval& yIn) const;
    interval numericNe(const interval& xInput, const interval& yInput) const;
    interval numericNeg(const interval& input) const;
    interval numericNot(const interval& input) const;
    interval numericNumEntry(const interval& name, const interval& init, const interval& lo, const interval& hi, const interval& step) const;
    interval numericOr(const interval& xInput, const interval& yInput) const;
    interval numericOutput(const interval& c, const interval& y) const;
    interval numericPow(const interval& x, const interval& y) const;
    interval numericPowBounds(const interval& xIn, const interval& yIn) const;
    interval numericPrefix(const interval& x, const interval& y) const;
    interval numericRDTbl(const interval& wtbl, const interval& ri) const;
    interval numericRemainder(const interval& xInput, const interval& yInput) const;
    interval numericRint(const interval& input) const;
    interval numericFrac(const interval& x) const;
    interval numericCfrac(const interval& x) const;
    interval numericTpt(const interval& x) const;
    // the definitions, operation by operation (their operands then read as independent) :
    // the bounds outside of the premise of Mix and of the domain of Tpt
    interval mixDefinition(const interval& c, const interval& a, const interval& b) const;
    interval tptDefinition(const interval& x) const;
    interval phaseDefinition(const interval& x, const interval& p) const;
    interval numericPhase(const interval& x, const interval& p) const;
    interval numericMix(const interval& c, const interval& a, const interval& b) const;
    // numericMix with the rounding of any form of a recursive mix : either interpolation
    // (from a or from b), or the weighted sum (1 - c) a + c b of a slow smoother
    interval numericMixAnyForm(const interval& c, const interval& a, const interval& b) const;
    interval numericMixWeight(const interval& c, const interval& a, const interval& b, double w,
                              bool weightedSum = false) const;
    interval numericRound(const interval& input) const;
    interval numericSelect2(const interval& x, const interval& y, const interval& z) const;
    interval numericSin(const interval& x) const;
    interval numericSinBounds(const interval& x) const;
    interval numericSinh(const interval& x) const;
    interval numericSinhBounds(const interval& x) const;
    interval numericSoundFile(const interval& label) const;
    interval numericSoundFileBuffer(const interval& sf, const interval& x, const interval& y, const interval& z) const;
    interval numericSoundFileLength(const interval& sf, const interval& x) const;
    interval numericSoundFileRate(const interval& sf, const interval& x) const;
    interval numericSqrt(const interval& x) const;
    interval numericSub(const interval& xIn, const interval& yIn) const;
    interval numericTan(const interval& x) const;
    interval numericTanBounds(const interval& x) const;
    interval numericTanh(const interval& x) const;
    interval numericTanhBounds(const interval& x) const;
    interval numericVBargraph(const interval& name, const interval& lo, const interval& hi, const interval& signal) const;
    interval numericVSlider(const interval& name, const interval& init, const interval& lo, const interval& hi, const interval& step) const;
    interval numericWRTbl(const interval& n, const interval& g, const interval& wi, const interval& ws) const;
    interval numericWaveform(const std::vector<interval>& w) const;
    interval numericXor(const interval& xInput, const interval& yInput) const;
    interval numericfPow(const interval& x, const interval& y) const;
    interval numericiPow(const interval& x, const interval& y) const;

};
}  // namespace itv
