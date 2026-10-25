/* Copyright 2026 Yann Orlarey, Stéphane Letz
 * Licensed under the Apache License, Version 2.0 (see LICENSE).
 */
#include "interval_algebra.hh"
#include "validity.hh"

namespace itv {

// Public API: validity-aware transfers. Numeric kernels retain their existing
// enclosure algorithms. Sticky alerts are attached AFTER every early return,
// including an empty result, and domain checks use the original operands.

// Public API: ARsh encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::ARsh(const interval& input, const interval& counts) const
{
    if (movesAny(input, counts)) return withMotionFrom(ARsh(still(input), still(counts)), ARsh(forAllTime(input), forAllTime(counts)));
    return flushedToZero(numericARsh(input, counts).withInvalid(detail::shiftInvalid(input, counts)));
}

// Public API: Abs encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Abs(const interval& input) const
{
    if (movesAny(input)) return withMotionFrom(Abs(still(input)), Abs(forAllTime(input)));
    return flushedToZero(numericAbs(input).withInvalid(detail::inputInvalid(input)));
}

// Public API: Acos encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Acos(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(Acos(still(x)), Acos(forAllTime(x)));
    return flushedToZero(numericAcos(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Acos, x)));
}

// Public API: AcosBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::AcosBounds(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(AcosBounds(still(x)), AcosBounds(forAllTime(x)));
    return flushedToZero(numericAcosBounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Acos, x)));
}

// Public API: Acosh encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Acosh(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(Acosh(still(x)), Acosh(forAllTime(x)));
    return flushedToZero(numericAcosh(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Acosh, x)));
}

// Public API: AcoshBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::AcoshBounds(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(AcoshBounds(still(x)), AcoshBounds(forAllTime(x)));
    return flushedToZero(numericAcoshBounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Acosh, x)));
}

// Public API: Add encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Add(const interval& xIn, const interval& yIn) const
{
    if (movesAny(xIn, yIn)) return withMotionFrom(Add(still(xIn), still(yIn)), Add(forAllTime(xIn), forAllTime(yIn)));
    return flushedToZero(numericAdd(xIn, yIn).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Add, xIn, yIn)));
}

// Public API: And encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::And(const interval& xInput, const interval& yInput) const
{
    if (movesAny(xInput, yInput)) return withMotionFrom(And(still(xInput), still(yInput)), And(forAllTime(xInput), forAllTime(yInput)));
    return flushedToZero(numericAnd(xInput, yInput).withInvalid(detail::intCastInvalid(xInput) || detail::intCastInvalid(yInput)));
}

// Public API: Asin encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Asin(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(Asin(still(x)), Asin(forAllTime(x)));
    return flushedToZero(zeroSignFrom(numericAsin(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Asin, x)), x));
}

// Public API: AsinBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::AsinBounds(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(AsinBounds(still(x)), AsinBounds(forAllTime(x)));
    return flushedToZero(numericAsinBounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Asin, x)));
}

// Public API: Asinh encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Asinh(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(Asinh(still(x)), Asinh(forAllTime(x)));
    return flushedToZero(zeroSignFrom(numericAsinh(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Asinh, x)), x));
}

// Public API: AsinhBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::AsinhBounds(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(AsinhBounds(still(x)), AsinhBounds(forAllTime(x)));
    return flushedToZero(numericAsinhBounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Asinh, x)));
}

// Public API: AssertBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::AssertBounds(const interval& lo, const interval& hi, const interval& x) const
{
    if (movesAny(lo, hi, x)) return withMotionFrom(AssertBounds(still(lo), still(hi), still(x)), AssertBounds(forAllTime(lo), forAllTime(hi), forAllTime(x)));
    return flushedToZero(numericAssertBounds(lo, hi, x).withInvalid(detail::assertionInvalid(lo, hi, x)));
}

// Public API: Atan encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Atan(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(Atan(still(x)), Atan(forAllTime(x)));
    return flushedToZero(zeroSignFrom(numericAtan(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Atan, x)), x));
}

// Public API: Atan2 encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Atan2(const interval& x, const interval& y) const
{
    if (movesAny(x, y)) return withMotionFrom(Atan2(still(x), still(y)), Atan2(forAllTime(x), forAllTime(y)));
    return flushedToZero(zeroSignFrom(numericAtan2(x, y).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Atan2, x, y)), x));
}

// Public API: Atan2Bounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Atan2Bounds(const interval& y, const interval& x) const
{
    if (movesAny(y, x)) return withMotionFrom(Atan2Bounds(still(y), still(x)), Atan2Bounds(forAllTime(y), forAllTime(x)));
    return flushedToZero(numericAtan2Bounds(y, x).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Atan2, y, x)));
}

// Public API: AtanBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::AtanBounds(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(AtanBounds(still(x)), AtanBounds(forAllTime(x)));
    return flushedToZero(numericAtanBounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Atan, x)));
}

// Public API: Atanh encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Atanh(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(Atanh(still(x)), Atanh(forAllTime(x)));
    return flushedToZero(zeroSignFrom(numericAtanh(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Atanh, x)), x));
}

// Public API: AtanhBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::AtanhBounds(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(AtanhBounds(still(x)), AtanhBounds(forAllTime(x)));
    return flushedToZero(numericAtanhBounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Atanh, x)));
}

// Public API: Attach encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Attach(const interval& x, const interval& y) const
{
    if (movesAny(x, y)) return withMotionFrom(Attach(still(x), still(y)), Attach(forAllTime(x), forAllTime(y)));
    return flushedToZero(numericAttach(x, y).withInvalid(detail::inputInvalid(x, y)));
}

// Public API: BitCast encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::BitCast(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(BitCast(still(x)), BitCast(forAllTime(x)));
    return flushedToZero(numericBitCast(x).withInvalid(detail::inputInvalid(x)));
}

// Public API: Button encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Button(const interval& name) const
{
    if (movesAny(name)) return withMotionFrom(Button(still(name)), Button(forAllTime(name)));
    return flushedToZero(numericButton(name).withInvalid(detail::inputInvalid(name)));
}

// Public API: Ceil encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Ceil(const interval& input) const
{
    if (movesAny(input)) return withMotionFrom(Ceil(still(input)), Ceil(forAllTime(input)));
    return flushedToZero(numericCeil(input).withInvalid(detail::inputInvalid(input)));
}

// Public API: Checkbox encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Checkbox(const interval& name) const
{
    if (movesAny(name)) return withMotionFrom(Checkbox(still(name)), Checkbox(forAllTime(name)));
    return flushedToZero(numericCheckbox(name).withInvalid(detail::inputInvalid(name)));
}

// Public API: Control encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Control(const interval& x, const interval& control) const
{
    if (movesAny(x, control)) return withMotionFrom(Control(still(x), still(control)), Control(forAllTime(x), forAllTime(control)));
    return flushedToZero(numericControl(x, control).withInvalid(detail::inputInvalid(x, control)));
}

// Public API: Cos encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Cos(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(Cos(still(x)), Cos(forAllTime(x)));
    return flushedToZero(numericCos(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Cos, x)));
}

// Public API: CosBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::CosBounds(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(CosBounds(still(x)), CosBounds(forAllTime(x)));
    return flushedToZero(numericCosBounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Cos, x)));
}

// Public API: Cosh encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Cosh(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(Cosh(still(x)), Cosh(forAllTime(x)));
    return flushedToZero(numericCosh(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Cosh, x)));
}

// Public API: CoshBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::CoshBounds(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(CoshBounds(still(x)), CoshBounds(forAllTime(x)));
    return flushedToZero(numericCoshBounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Cosh, x)));
}

// Public API: enclose Delay after int32 conversion of the sample count.
// Exactly zero preserves bounds and LSB; possibly positive counts include
// initial zero. Retain invalidity of either operand and the delay domain.
interval interval_algebra::Delay(const interval& x, const interval& y) const
{
    if (movesAny(x, y)) return withMotionFrom(Delay(still(x), still(y)), Delay(forAllTime(x), forAllTime(y)));
    return flushedToZero(numericDelay(x, y).withInvalid(detail::delayInvalid(x, y)));
}

// Public API: Div encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Div(const interval& x, const interval& y) const
{
    if (movesAny(x, y)) return withMotionFrom(Div(still(x), still(y)), Div(forAllTime(x), forAllTime(y)));
    return flushedToZero(numericDiv(x, y).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Div, x, y)));
}

// Public API: Enable encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Enable(const interval& x, const interval& control) const
{
    if (movesAny(x, control)) return withMotionFrom(Enable(still(x), still(control)), Enable(forAllTime(x), forAllTime(control)));
    return flushedToZero(numericEnable(x, control).withInvalid(detail::inputInvalid(x, control)));
}

// Public API: Eq encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Eq(const interval& xInput, const interval& yInput) const
{
    if (movesAny(xInput, yInput)) return withMotionFrom(Eq(still(xInput), still(yInput)), Eq(forAllTime(xInput), forAllTime(yInput)));
    return flushedToZero(numericEq(xInput, yInput).withInvalid(detail::inputInvalid(xInput, yInput)));
}

// Public API: Exp encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Exp(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(Exp(still(x)), Exp(forAllTime(x)));
    return flushedToZero(numericExp(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Exp, x)));
}

// Public API: Exp10 encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Exp10(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(Exp10(still(x)), Exp10(forAllTime(x)));
    return flushedToZero(numericExp10(x).withInvalid(detail::inputInvalid(x)));
}

// Public API: ExpBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::ExpBounds(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(ExpBounds(still(x)), ExpBounds(forAllTime(x)));
    return flushedToZero(numericExpBounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Exp, x)));
}

// Public API: FixPointUpdate encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::FixPointUpdate(const interval& x, const interval& y) const
{
    if (movesAny(x, y)) return withMotionFrom(FixPointUpdate(still(x), still(y)), FixPointUpdate(forAllTime(x), forAllTime(y)));
    return flushedToZero(numericFixPointUpdate(x, y).withInvalid(detail::inputInvalid(x, y)));
}

// Public API: FloatCast encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::FloatCast(const interval& input) const
{
    if (movesAny(input)) return withMotionFrom(FloatCast(still(input)), FloatCast(forAllTime(input)));
    return flushedToZero(numericFloatCast(input).withInvalid(detail::inputInvalid(input)));
}

// Public API: FloatNum encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::FloatNum(double x) const
{
    return flushedToZero(numericFloatNum(x).withInvalid(std::isnan(x)));
}

// Public API: Floor encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Floor(const interval& input) const
{
    if (movesAny(input)) return withMotionFrom(Floor(still(input)), Floor(forAllTime(input)));
    return flushedToZero(numericFloor(input).withInvalid(detail::inputInvalid(input)));
}

// Public API: Fmod encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Fmod(const interval& x, const interval& y) const
{
    if (movesAny(x, y)) return withMotionFrom(Fmod(still(x), still(y)), Fmod(forAllTime(x), forAllTime(y)));
    return flushedToZero(zeroSignFrom(numericFmod(x, y).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Fmod, x, y)), x));
}

// Public API: ForeignConst encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::ForeignConst(int declaredNature, const interval& name, const interval& file) const
{
    if (movesAny(name, file)) return withMotionFrom(ForeignConst(declaredNature, still(name), still(file)), ForeignConst(declaredNature, forAllTime(name), forAllTime(file)));
    return flushedToZero(numericForeignConst(declaredNature, name, file).withInvalid(detail::inputInvalid(name, file)));
}

// Public API: ForeignFunction encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::ForeignFunction(int resultNature, const std::vector<interval>& args) const
{
    if (movesAny(args)) return withMotionFrom(ForeignFunction(resultNature, still(args)), ForeignFunction(resultNature, forAllTime(args)));
    return flushedToZero(numericForeignFunction(resultNature, args).withInvalid(std::any_of(args.begin(), args.end(), [](const interval& x) { return x.mayBeInvalid(); })));
}

// Public API: ForeignVar encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::ForeignVar(int declaredNature, const interval& name, const interval& file) const
{
    if (movesAny(name, file)) return withMotionFrom(ForeignVar(declaredNature, still(name), still(file)), ForeignVar(declaredNature, forAllTime(name), forAllTime(file)));
    return flushedToZero(numericForeignVar(declaredNature, name, file).withInvalid(detail::inputInvalid(name, file)));
}

// Public API: Ge encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Ge(const interval& xInput, const interval& yInput) const
{
    if (movesAny(xInput, yInput)) return withMotionFrom(Ge(still(xInput), still(yInput)), Ge(forAllTime(xInput), forAllTime(yInput)));
    return flushedToZero(numericGe(xInput, yInput).withInvalid(detail::inputInvalid(xInput, yInput)));
}

// Public API: Gen encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Gen(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(Gen(still(x)), Gen(forAllTime(x)));
    return flushedToZero(numericGen(x).withInvalid(detail::inputInvalid(x)));
}

// Public API: Gt encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Gt(const interval& xInput, const interval& yInput) const
{
    if (movesAny(xInput, yInput)) return withMotionFrom(Gt(still(xInput), still(yInput)), Gt(forAllTime(xInput), forAllTime(yInput)));
    return flushedToZero(numericGt(xInput, yInput).withInvalid(detail::inputInvalid(xInput, yInput)));
}

// Public API: HBargraph encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::HBargraph(const interval& name, const interval& lo, const interval& hi, const interval& signal) const
{
    if (movesAny(name, lo, hi, signal)) return withMotionFrom(HBargraph(still(name), still(lo), still(hi), still(signal)), HBargraph(forAllTime(name), forAllTime(lo), forAllTime(hi), forAllTime(signal)));
    return flushedToZero(numericHBargraph(name, lo, hi, signal).withInvalid(detail::inputInvalid(name, lo, hi, signal)));
}

// Public API: HSlider encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::HSlider(const interval& name, const interval& init, const interval& lo, const interval& hi, const interval& step) const
{
    if (movesAny(name, init, lo, hi, step)) return withMotionFrom(HSlider(still(name), still(init), still(lo), still(hi), still(step)), HSlider(forAllTime(name), forAllTime(init), forAllTime(lo), forAllTime(hi), forAllTime(step)));
    return flushedToZero(numericHSlider(name, init, lo, hi, step).withInvalid(name.mayBeInvalid() || detail::widgetInvalid(init, lo, hi, step)));
}

// Public API: Highest encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Highest(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(Highest(still(x)), Highest(forAllTime(x)));
    return flushedToZero(numericHighest(x).withInvalid(detail::inputInvalid(x)));
}

// Public API: Input encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Input(const interval& c) const
{
    if (movesAny(c)) return withMotionFrom(Input(still(c)), Input(forAllTime(c)));
    return flushedToZero(numericInput(c).withInvalid(detail::inputInvalid(c)));
}

// Public API: Int64Num encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Int64Num(int64_t x) const
{
    return flushedToZero(numericInt64Num(x).withInvalid(detail::inputInvalid()));
}

// Public API: IntCast encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
// Truncation must fit int32; invalid-only inputs give numeric bottom with an
// alert, and partially invalid inputs keep their valid truncated image.
interval interval_algebra::IntCast(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(IntCast(still(x)), IntCast(forAllTime(x)));
    return flushedToZero(numericIntCast(x).withInvalid(detail::intCastInvalid(x)));
}

// Public API: IntNum encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::IntNum(int x) const
{
    return flushedToZero(numericIntNum(x).withInvalid(detail::inputInvalid()));
}

// Public API: Inv encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Inv(const interval& input) const
{
    if (movesAny(input)) return withMotionFrom(Inv(still(input)), Inv(forAllTime(input)));
    return flushedToZero(numericInv(input).withInvalid(detail::inputInvalid(input)));
}

// Public API: LRsh encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::LRsh(const interval& input, const interval& counts) const
{
    if (movesAny(input, counts)) return withMotionFrom(LRsh(still(input), still(counts)), LRsh(forAllTime(input), forAllTime(counts)));
    return flushedToZero(numericLRsh(input, counts).withInvalid(detail::shiftInvalid(input, counts)));
}

// Public API: Label encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Label(const std::string& x) const
{
    return flushedToZero(numericLabel(x).withInvalid(detail::inputInvalid()));
}

// Public API: Le encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Le(const interval& xInput, const interval& yInput) const
{
    if (movesAny(xInput, yInput)) return withMotionFrom(Le(still(xInput), still(yInput)), Le(forAllTime(xInput), forAllTime(yInput)));
    return flushedToZero(numericLe(xInput, yInput).withInvalid(detail::inputInvalid(xInput, yInput)));
}

// Public API: Log encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Log(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(Log(still(x)), Log(forAllTime(x)));
    return flushedToZero(numericLog(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Log, x)));
}

// Public API: Log10 encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Log10(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(Log10(still(x)), Log10(forAllTime(x)));
    return flushedToZero(numericLog10(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Log10, x)));
}

// Public API: Log10Bounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Log10Bounds(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(Log10Bounds(still(x)), Log10Bounds(forAllTime(x)));
    return flushedToZero(numericLog10Bounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Log10, x)));
}

// Public API: LogBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::LogBounds(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(LogBounds(still(x)), LogBounds(forAllTime(x)));
    return flushedToZero(numericLogBounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Log, x)));
}

// Public API: Lowest encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Lowest(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(Lowest(still(x)), Lowest(forAllTime(x)));
    return flushedToZero(numericLowest(x).withInvalid(detail::inputInvalid(x)));
}

// Public API: Lsh encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Lsh(const interval& input, const interval& counts) const
{
    if (movesAny(input, counts)) return withMotionFrom(Lsh(still(input), still(counts)), Lsh(forAllTime(input), forAllTime(counts)));
    return flushedToZero(numericLsh(input, counts).withInvalid(detail::shiftInvalid(input, counts)));
}

// Public API: Lt encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Lt(const interval& xInput, const interval& yInput) const
{
    if (movesAny(xInput, yInput)) return withMotionFrom(Lt(still(xInput), still(yInput)), Lt(forAllTime(xInput), forAllTime(yInput)));
    return flushedToZero(numericLt(xInput, yInput).withInvalid(detail::inputInvalid(xInput, yInput)));
}

// Public API: Max encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Max(const interval& xInput, const interval& yInput) const
{
    if (movesAny(xInput, yInput)) return withMotionFrom(Max(still(xInput), still(yInput)), Max(forAllTime(xInput), forAllTime(yInput)));
    return flushedToZero(numericMax(xInput, yInput).withInvalid(detail::inputInvalid(xInput, yInput)));
}

// Public API: Mem encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Mem(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(Mem(still(x)), Mem(forAllTime(x)));
    return flushedToZero(numericMem(x).withInvalid(detail::inputInvalid(x)));
}

// Public API: Min encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Min(const interval& xInput, const interval& yInput) const
{
    if (movesAny(xInput, yInput)) return withMotionFrom(Min(still(xInput), still(yInput)), Min(forAllTime(xInput), forAllTime(yInput)));
    return flushedToZero(numericMin(xInput, yInput).withInvalid(detail::inputInvalid(xInput, yInput)));
}

// Public API: Mod encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Mod(const interval& xIn, const interval& yIn) const
{
    if (movesAny(xIn, yIn)) return withMotionFrom(Mod(still(xIn), still(yIn)), Mod(forAllTime(xIn), forAllTime(yIn)));
    return flushedToZero(zeroSignFrom(numericMod(xIn, yIn).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Mod, xIn, yIn)), xIn));
}

// Public API: Mul encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Mul(const interval& xIn, const interval& yIn) const
{
    if (movesAny(xIn, yIn)) return withMotionFrom(Mul(still(xIn), still(yIn)), Mul(forAllTime(xIn), forAllTime(yIn)));
    return flushedToZero(numericMul(xIn, yIn).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Mul, xIn, yIn)));
}

// Public API: Ne encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Ne(const interval& xInput, const interval& yInput) const
{
    if (movesAny(xInput, yInput)) return withMotionFrom(Ne(still(xInput), still(yInput)), Ne(forAllTime(xInput), forAllTime(yInput)));
    return flushedToZero(numericNe(xInput, yInput).withInvalid(detail::inputInvalid(xInput, yInput)));
}

// Public API: Neg encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Neg(const interval& input) const
{
    if (movesAny(input)) return withMotionFrom(Neg(still(input)), Neg(forAllTime(input)));
    return flushedToZero(numericNeg(input).withInvalid(detail::inputInvalid(input)));
}

// Public API: Not encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Not(const interval& input) const
{
    if (movesAny(input)) return withMotionFrom(Not(still(input)), Not(forAllTime(input)));
    return flushedToZero(numericNot(input).withInvalid(detail::intCastInvalid(input)));
}

// Public API: NumEntry encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::NumEntry(const interval& name, const interval& init, const interval& lo, const interval& hi, const interval& step) const
{
    if (movesAny(name, init, lo, hi, step)) return withMotionFrom(NumEntry(still(name), still(init), still(lo), still(hi), still(step)), NumEntry(forAllTime(name), forAllTime(init), forAllTime(lo), forAllTime(hi), forAllTime(step)));
    return flushedToZero(numericNumEntry(name, init, lo, hi, step).withInvalid(name.mayBeInvalid() || detail::widgetInvalid(init, lo, hi, step)));
}

// Public API: Or encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Or(const interval& xInput, const interval& yInput) const
{
    if (movesAny(xInput, yInput)) return withMotionFrom(Or(still(xInput), still(yInput)), Or(forAllTime(xInput), forAllTime(yInput)));
    return flushedToZero(numericOr(xInput, yInput).withInvalid(detail::intCastInvalid(xInput) || detail::intCastInvalid(yInput)));
}

// Public API: Output encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Output(const interval& c, const interval& y) const
{
    if (movesAny(c, y)) return withMotionFrom(Output(still(c), still(y)), Output(forAllTime(c), forAllTime(y)));
    return flushedToZero(numericOutput(c, y).withInvalid(detail::inputInvalid(c, y)));
}

// Public API: Pow encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Pow(const interval& x, const interval& y) const
{
    if (movesAny(x, y)) return withMotionFrom(Pow(still(x), still(y)), Pow(forAllTime(x), forAllTime(y)));
    return flushedToZero(zeroSignFrom(numericPow(x, y).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Pow, x, y)), x));
}

// Public API: PowBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::PowBounds(const interval& xIn, const interval& yIn) const
{
    if (movesAny(xIn, yIn)) return withMotionFrom(PowBounds(still(xIn), still(yIn)), PowBounds(forAllTime(xIn), forAllTime(yIn)));
    return flushedToZero(numericPowBounds(xIn, yIn).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Pow, xIn, yIn)));
}

// Public API: Prefix encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Prefix(const interval& x, const interval& y) const
{
    if (movesAny(x, y)) return withMotionFrom(Prefix(still(x), still(y)), Prefix(forAllTime(x), forAllTime(y)));
    return flushedToZero(numericPrefix(x, y).withInvalid(detail::inputInvalid(x, y)));
}

// Table extent is absent from the value attribute; the compiler must supply
// a domain-aware read rule to prove an index safe.
// Public API: RDTbl encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::RDTbl(const interval& wtbl, const interval& ri) const
{
    if (movesAny(wtbl, ri)) return withMotionFrom(RDTbl(still(wtbl), still(ri)), RDTbl(forAllTime(wtbl), forAllTime(ri)));
    return flushedToZero(numericRDTbl(wtbl, ri).withInvalid(detail::inputInvalid(wtbl, ri)));
}

// Public API: Remainder encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Remainder(const interval& xInput, const interval& yInput) const
{
    if (movesAny(xInput, yInput)) return withMotionFrom(Remainder(still(xInput), still(yInput)), Remainder(forAllTime(xInput), forAllTime(yInput)));
    return flushedToZero(numericRemainder(xInput, yInput).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Remainder, xInput, yInput)));
}

// Public API: Rint encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Rint(const interval& input) const
{
    if (movesAny(input)) return withMotionFrom(Rint(still(input)), Rint(forAllTime(input)));
    return flushedToZero(numericRint(input).withInvalid(detail::inputInvalid(input)));
}

// Public API: Round encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Round(const interval& input) const
{
    if (movesAny(input)) return withMotionFrom(Round(still(input)), Round(forAllTime(input)));
    return flushedToZero(numericRound(input).withInvalid(detail::inputInvalid(input)));
}

// Public API: Select2 encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Select2(const interval& x, const interval& y, const interval& z) const
{
    if (movesAny(x, y, z)) return withMotionFrom(Select2(still(x), still(y), still(z)), Select2(forAllTime(x), forAllTime(y), forAllTime(z)));
    return flushedToZero(numericSelect2(x, y, z).withInvalid(detail::inputInvalid(x, y, z)));
}

// Public API: Sin encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Sin(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(Sin(still(x)), Sin(forAllTime(x)));
    return flushedToZero(zeroSignFrom(numericSin(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Sin, x)), x));
}

// Public API: SinBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::SinBounds(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(SinBounds(still(x)), SinBounds(forAllTime(x)));
    return flushedToZero(numericSinBounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Sin, x)));
}

// Public API: Sinh encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Sinh(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(Sinh(still(x)), Sinh(forAllTime(x)));
    return flushedToZero(zeroSignFrom(numericSinh(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Sinh, x)), x));
}

// Public API: SinhBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::SinhBounds(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(SinhBounds(still(x)), SinhBounds(forAllTime(x)));
    return flushedToZero(numericSinhBounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Sinh, x)));
}

// Public API: SoundFile encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::SoundFile(const interval& label) const
{
    if (movesAny(label)) return withMotionFrom(SoundFile(still(label)), SoundFile(forAllTime(label)));
    return flushedToZero(numericSoundFile(label).withInvalid(detail::inputInvalid(label)));
}

// Public API: SoundFileBuffer encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::SoundFileBuffer(const interval& sf, const interval& x, const interval& y, const interval& z) const
{
    if (movesAny(sf, x, y, z)) return withMotionFrom(SoundFileBuffer(still(sf), still(x), still(y), still(z)), SoundFileBuffer(forAllTime(sf), forAllTime(x), forAllTime(y), forAllTime(z)));
    return flushedToZero(numericSoundFileBuffer(sf, x, y, z).withInvalid(true));
}

// Public API: SoundFileLength encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::SoundFileLength(const interval& sf, const interval& x) const
{
    if (movesAny(sf, x)) return withMotionFrom(SoundFileLength(still(sf), still(x)), SoundFileLength(forAllTime(sf), forAllTime(x)));
    return flushedToZero(numericSoundFileLength(sf, x).withInvalid(true));
}

// Soundfile extents are absent here, so indexed metadata/sample access remains
// uncertified until the compiler checks its resource-specific domain.
// Public API: SoundFileRate encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::SoundFileRate(const interval& sf, const interval& x) const
{
    if (movesAny(sf, x)) return withMotionFrom(SoundFileRate(still(sf), still(x)), SoundFileRate(forAllTime(sf), forAllTime(x)));
    return flushedToZero(numericSoundFileRate(sf, x).withInvalid(true));
}

// Public API: Sqrt encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Sqrt(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(Sqrt(still(x)), Sqrt(forAllTime(x)));
    return flushedToZero(numericSqrt(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Sqrt, x)));
}

// Public API: Sub encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Sub(const interval& xIn, const interval& yIn) const
{
    if (movesAny(xIn, yIn)) return withMotionFrom(Sub(still(xIn), still(yIn)), Sub(forAllTime(xIn), forAllTime(yIn)));
    return flushedToZero(numericSub(xIn, yIn).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Sub, xIn, yIn)));
}

// Public API: Tan encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Tan(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(Tan(still(x)), Tan(forAllTime(x)));
    return flushedToZero(zeroSignFrom(numericTan(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Tan, x)), x));
}

// Public API: TanBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::TanBounds(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(TanBounds(still(x)), TanBounds(forAllTime(x)));
    return flushedToZero(numericTanBounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Tan, x)));
}

// Public API: Tanh encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Tanh(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(Tanh(still(x)), Tanh(forAllTime(x)));
    return flushedToZero(zeroSignFrom(numericTanh(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Tanh, x)), x));
}

// Public API: TanhBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::TanhBounds(const interval& x) const
{
    if (movesAny(x)) return withMotionFrom(TanhBounds(still(x)), TanhBounds(forAllTime(x)));
    return flushedToZero(numericTanhBounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Tanh, x)));
}

// Public API: VBargraph encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::VBargraph(const interval& name, const interval& lo, const interval& hi, const interval& signal) const
{
    if (movesAny(name, lo, hi, signal)) return withMotionFrom(VBargraph(still(name), still(lo), still(hi), still(signal)), VBargraph(forAllTime(name), forAllTime(lo), forAllTime(hi), forAllTime(signal)));
    return flushedToZero(numericVBargraph(name, lo, hi, signal).withInvalid(detail::inputInvalid(name, lo, hi, signal)));
}

// Public API: VSlider encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::VSlider(const interval& name, const interval& init, const interval& lo, const interval& hi, const interval& step) const
{
    if (movesAny(name, init, lo, hi, step)) return withMotionFrom(VSlider(still(name), still(init), still(lo), still(hi), still(step)), VSlider(forAllTime(name), forAllTime(init), forAllTime(lo), forAllTime(hi), forAllTime(step)));
    return flushedToZero(numericVSlider(name, init, lo, hi, step).withInvalid(name.mayBeInvalid() || detail::widgetInvalid(init, lo, hi, step)));
}

// Public API: WRTbl encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::WRTbl(const interval& n, const interval& g, const interval& wi, const interval& ws) const
{
    if (movesAny(n, g, wi, ws)) return withMotionFrom(WRTbl(still(n), still(g), still(wi), still(ws)), WRTbl(forAllTime(n), forAllTime(g), forAllTime(wi), forAllTime(ws)));
    return flushedToZero(numericWRTbl(n, g, wi, ws).withInvalid(detail::inputInvalid(n, g, wi, ws)));
}

// Public API: Waveform encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Waveform(const std::vector<interval>& w) const
{
    if (movesAny(w)) return withMotionFrom(Waveform(still(w)), Waveform(forAllTime(w)));
    return flushedToZero(numericWaveform(w).withInvalid(std::any_of(w.begin(), w.end(), [](const interval& x) { return x.mayBeInvalid(); })));
}

// Public API: Xor encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Xor(const interval& xInput, const interval& yInput) const
{
    if (movesAny(xInput, yInput)) return withMotionFrom(Xor(still(xInput), still(yInput)), Xor(forAllTime(xInput), forAllTime(yInput)));
    return flushedToZero(numericXor(xInput, yInput).withInvalid(detail::intCastInvalid(xInput) || detail::intCastInvalid(yInput)));
}

// Internal transfer: fPow encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::fPow(const interval& x, const interval& y) const
{
    if (movesAny(x, y)) return withMotionFrom(fPow(still(x), still(y)), fPow(forAllTime(x), forAllTime(y)));
    return flushedToZero(numericfPow(x, y).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Pow, x, y)));
}

// Internal transfer: iPow encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::iPow(const interval& x, const interval& y) const
{
    if (movesAny(x, y)) return withMotionFrom(iPow(still(x), still(y)), iPow(forAllTime(x), forAllTime(y)));
    return flushedToZero(numericiPow(x, y).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Pow, x, y)));
}

// Public API: scalar modulo forwards to the typed interval transfer; its domain
// checks and invalidity propagation are identical to the two-interval overload.
interval interval_algebra::Mod(const interval& x, double m) const
{
    if (movesAny(x)) return withMotionFrom(Mod(still(x), m), Mod(forAllTime(x), m));
    return Mod(x, interval(m));
}

}  // namespace itv
