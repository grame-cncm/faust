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
    return numericARsh(input, counts).withInvalid(detail::shiftInvalid(input, counts));
}

// Public API: Abs encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Abs(const interval& input) const
{
    return numericAbs(input).withInvalid(detail::inputInvalid(input));
}

// Public API: Acos encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Acos(const interval& x) const
{
    return numericAcos(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Acos, x));
}

// Public API: AcosBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::AcosBounds(const interval& x) const
{
    return numericAcosBounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Acos, x));
}

// Public API: Acosh encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Acosh(const interval& x) const
{
    return numericAcosh(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Acosh, x));
}

// Public API: AcoshBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::AcoshBounds(const interval& x) const
{
    return numericAcoshBounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Acosh, x));
}

// Public API: Add encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Add(const interval& xIn, const interval& yIn) const
{
    return numericAdd(xIn, yIn).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Add, xIn, yIn));
}

// Public API: And encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::And(const interval& xInput, const interval& yInput) const
{
    return numericAnd(xInput, yInput).withInvalid(detail::intCastInvalid(xInput) || detail::intCastInvalid(yInput));
}

// Public API: Asin encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Asin(const interval& x) const
{
    return numericAsin(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Asin, x));
}

// Public API: AsinBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::AsinBounds(const interval& x) const
{
    return numericAsinBounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Asin, x));
}

// Public API: Asinh encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Asinh(const interval& x) const
{
    return numericAsinh(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Asinh, x));
}

// Public API: AsinhBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::AsinhBounds(const interval& x) const
{
    return numericAsinhBounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Asinh, x));
}

// Public API: AssertBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::AssertBounds(const interval& lo, const interval& hi, const interval& x) const
{
    return numericAssertBounds(lo, hi, x).withInvalid(detail::assertionInvalid(lo, hi, x));
}

// Public API: Atan encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Atan(const interval& x) const
{
    return numericAtan(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Atan, x));
}

// Public API: Atan2 encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Atan2(const interval& x, const interval& y) const
{
    return numericAtan2(x, y).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Atan2, x, y));
}

// Public API: Atan2Bounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Atan2Bounds(const interval& y, const interval& x) const
{
    return numericAtan2Bounds(y, x).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Atan2, y, x));
}

// Public API: AtanBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::AtanBounds(const interval& x) const
{
    return numericAtanBounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Atan, x));
}

// Public API: Atanh encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Atanh(const interval& x) const
{
    return numericAtanh(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Atanh, x));
}

// Public API: AtanhBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::AtanhBounds(const interval& x) const
{
    return numericAtanhBounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Atanh, x));
}

// Public API: Attach encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Attach(const interval& x, const interval& y) const
{
    return numericAttach(x, y).withInvalid(detail::inputInvalid(x, y));
}

// Public API: BitCast encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::BitCast(const interval& x) const
{
    return numericBitCast(x).withInvalid(detail::inputInvalid(x));
}

// Public API: Button encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Button(const interval& name) const
{
    return numericButton(name).withInvalid(detail::inputInvalid(name));
}

// Public API: Ceil encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Ceil(const interval& input) const
{
    return numericCeil(input).withInvalid(detail::inputInvalid(input));
}

// Public API: Checkbox encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Checkbox(const interval& name) const
{
    return numericCheckbox(name).withInvalid(detail::inputInvalid(name));
}

// Public API: Control encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Control(const interval& x, const interval& control) const
{
    return numericControl(x, control).withInvalid(detail::inputInvalid(x, control));
}

// Public API: Cos encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Cos(const interval& x) const
{
    return numericCos(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Cos, x));
}

// Public API: CosBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::CosBounds(const interval& x) const
{
    return numericCosBounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Cos, x));
}

// Public API: Cosh encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Cosh(const interval& x) const
{
    return numericCosh(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Cosh, x));
}

// Public API: CoshBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::CoshBounds(const interval& x) const
{
    return numericCoshBounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Cosh, x));
}

// Public API: enclose Delay after int32 conversion of the sample count.
// Exactly zero preserves bounds and LSB; possibly positive counts include
// initial zero. Retain invalidity of either operand and the delay domain.
interval interval_algebra::Delay(const interval& x, const interval& y) const
{
    return numericDelay(x, y).withInvalid(detail::delayInvalid(x, y));
}

// Public API: Div encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Div(const interval& x, const interval& y) const
{
    return numericDiv(x, y).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Div, x, y));
}

// Public API: Enable encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Enable(const interval& x, const interval& control) const
{
    return numericEnable(x, control).withInvalid(detail::inputInvalid(x, control));
}

// Public API: Eq encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Eq(const interval& xInput, const interval& yInput) const
{
    return numericEq(xInput, yInput).withInvalid(detail::inputInvalid(xInput, yInput));
}

// Public API: Exp encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Exp(const interval& x) const
{
    return numericExp(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Exp, x));
}

// Public API: Exp10 encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Exp10(const interval& x) const
{
    return numericExp10(x).withInvalid(detail::inputInvalid(x));
}

// Public API: ExpBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::ExpBounds(const interval& x) const
{
    return numericExpBounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Exp, x));
}

// Public API: FixPointUpdate encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::FixPointUpdate(const interval& x, const interval& y) const
{
    return numericFixPointUpdate(x, y).withInvalid(detail::inputInvalid(x, y));
}

// Public API: FloatCast encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::FloatCast(const interval& input) const
{
    return numericFloatCast(input).withInvalid(detail::inputInvalid(input));
}

// Public API: FloatNum encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::FloatNum(double x) const
{
    return numericFloatNum(x).withInvalid(std::isnan(x));
}

// Public API: Floor encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Floor(const interval& input) const
{
    return numericFloor(input).withInvalid(detail::inputInvalid(input));
}

// Public API: Fmod encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Fmod(const interval& x, const interval& y) const
{
    return numericFmod(x, y).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Fmod, x, y));
}

// Public API: ForeignConst encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::ForeignConst(int declaredNature, const interval& name, const interval& file) const
{
    return numericForeignConst(declaredNature, name, file).withInvalid(detail::inputInvalid(name, file));
}

// Public API: ForeignFunction encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::ForeignFunction(int resultNature, const std::vector<interval>& args) const
{
    return numericForeignFunction(resultNature, args).withInvalid(std::any_of(args.begin(), args.end(), [](const interval& x) { return x.mayBeInvalid(); }));
}

// Public API: ForeignVar encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::ForeignVar(int declaredNature, const interval& name, const interval& file) const
{
    return numericForeignVar(declaredNature, name, file).withInvalid(detail::inputInvalid(name, file));
}

// Public API: Ge encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Ge(const interval& xInput, const interval& yInput) const
{
    return numericGe(xInput, yInput).withInvalid(detail::inputInvalid(xInput, yInput));
}

// Public API: Gen encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Gen(const interval& x) const
{
    return numericGen(x).withInvalid(detail::inputInvalid(x));
}

// Public API: Gt encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Gt(const interval& xInput, const interval& yInput) const
{
    return numericGt(xInput, yInput).withInvalid(detail::inputInvalid(xInput, yInput));
}

// Public API: HBargraph encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::HBargraph(const interval& name, const interval& lo, const interval& hi, const interval& signal) const
{
    return numericHBargraph(name, lo, hi, signal).withInvalid(detail::inputInvalid(name, lo, hi, signal));
}

// Public API: HSlider encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::HSlider(const interval& name, const interval& init, const interval& lo, const interval& hi, const interval& step) const
{
    return numericHSlider(name, init, lo, hi, step).withInvalid(name.mayBeInvalid() || detail::widgetInvalid(init, lo, hi, step));
}

// Public API: Highest encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Highest(const interval& x) const
{
    return numericHighest(x).withInvalid(detail::inputInvalid(x));
}

// Public API: Input encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Input(const interval& c) const
{
    return numericInput(c).withInvalid(detail::inputInvalid(c));
}

// Public API: Int64Num encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Int64Num(int64_t x) const
{
    return numericInt64Num(x).withInvalid(detail::inputInvalid());
}

// Public API: IntCast encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
// Truncation must fit int32; invalid-only inputs give numeric bottom with an
// alert, and partially invalid inputs keep their valid truncated image.
interval interval_algebra::IntCast(const interval& x) const
{
    return numericIntCast(x).withInvalid(detail::intCastInvalid(x));
}

// Public API: IntNum encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::IntNum(int x) const
{
    return numericIntNum(x).withInvalid(detail::inputInvalid());
}

// Public API: Inv encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Inv(const interval& input) const
{
    return numericInv(input).withInvalid(detail::inputInvalid(input));
}

// Public API: LRsh encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::LRsh(const interval& input, const interval& counts) const
{
    return numericLRsh(input, counts).withInvalid(detail::shiftInvalid(input, counts));
}

// Public API: Label encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Label(const std::string& x) const
{
    return numericLabel(x).withInvalid(detail::inputInvalid());
}

// Public API: Le encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Le(const interval& xInput, const interval& yInput) const
{
    return numericLe(xInput, yInput).withInvalid(detail::inputInvalid(xInput, yInput));
}

// Public API: Log encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Log(const interval& x) const
{
    return numericLog(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Log, x));
}

// Public API: Log10 encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Log10(const interval& x) const
{
    return numericLog10(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Log10, x));
}

// Public API: Log10Bounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Log10Bounds(const interval& x) const
{
    return numericLog10Bounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Log10, x));
}

// Public API: LogBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::LogBounds(const interval& x) const
{
    return numericLogBounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Log, x));
}

// Public API: Lowest encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Lowest(const interval& x) const
{
    return numericLowest(x).withInvalid(detail::inputInvalid(x));
}

// Public API: Lsh encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Lsh(const interval& input, const interval& counts) const
{
    return numericLsh(input, counts).withInvalid(detail::shiftInvalid(input, counts));
}

// Public API: Lt encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Lt(const interval& xInput, const interval& yInput) const
{
    return numericLt(xInput, yInput).withInvalid(detail::inputInvalid(xInput, yInput));
}

// Public API: Max encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Max(const interval& xInput, const interval& yInput) const
{
    return numericMax(xInput, yInput).withInvalid(detail::inputInvalid(xInput, yInput));
}

// Public API: Mem encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Mem(const interval& x) const
{
    return numericMem(x).withInvalid(detail::inputInvalid(x));
}

// Public API: Min encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Min(const interval& xInput, const interval& yInput) const
{
    return numericMin(xInput, yInput).withInvalid(detail::inputInvalid(xInput, yInput));
}

// Public API: Mod encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Mod(const interval& xIn, const interval& yIn) const
{
    return numericMod(xIn, yIn).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Mod, xIn, yIn));
}

// Public API: Mul encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Mul(const interval& xIn, const interval& yIn) const
{
    return numericMul(xIn, yIn).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Mul, xIn, yIn));
}

// Public API: Ne encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Ne(const interval& xInput, const interval& yInput) const
{
    return numericNe(xInput, yInput).withInvalid(detail::inputInvalid(xInput, yInput));
}

// Public API: Neg encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Neg(const interval& input) const
{
    return numericNeg(input).withInvalid(detail::inputInvalid(input));
}

// Public API: Not encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Not(const interval& input) const
{
    return numericNot(input).withInvalid(detail::intCastInvalid(input));
}

// Public API: NumEntry encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::NumEntry(const interval& name, const interval& init, const interval& lo, const interval& hi, const interval& step) const
{
    return numericNumEntry(name, init, lo, hi, step).withInvalid(name.mayBeInvalid() || detail::widgetInvalid(init, lo, hi, step));
}

// Public API: Or encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Or(const interval& xInput, const interval& yInput) const
{
    return numericOr(xInput, yInput).withInvalid(detail::intCastInvalid(xInput) || detail::intCastInvalid(yInput));
}

// Public API: Output encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Output(const interval& c, const interval& y) const
{
    return numericOutput(c, y).withInvalid(detail::inputInvalid(c, y));
}

// Public API: Pow encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Pow(const interval& x, const interval& y) const
{
    return numericPow(x, y).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Pow, x, y));
}

// Public API: PowBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::PowBounds(const interval& xIn, const interval& yIn) const
{
    return numericPowBounds(xIn, yIn).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Pow, xIn, yIn));
}

// Public API: Prefix encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Prefix(const interval& x, const interval& y) const
{
    return numericPrefix(x, y).withInvalid(detail::inputInvalid(x, y));
}

// Table extent is absent from the value attribute; the compiler must supply
// a domain-aware read rule to prove an index safe.
// Public API: RDTbl encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::RDTbl(const interval& wtbl, const interval& ri) const
{
    return numericRDTbl(wtbl, ri).withInvalid(detail::inputInvalid(wtbl, ri));
}

// Public API: Remainder encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Remainder(const interval& xInput, const interval& yInput) const
{
    return numericRemainder(xInput, yInput).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Remainder, xInput, yInput));
}

// Public API: Rint encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Rint(const interval& input) const
{
    return numericRint(input).withInvalid(detail::inputInvalid(input));
}

// Public API: Round encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Round(const interval& input) const
{
    return numericRound(input).withInvalid(detail::inputInvalid(input));
}

// Public API: Select2 encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Select2(const interval& x, const interval& y, const interval& z) const
{
    return numericSelect2(x, y, z).withInvalid(detail::inputInvalid(x, y, z));
}

// Public API: Sin encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Sin(const interval& x) const
{
    return numericSin(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Sin, x));
}

// Public API: SinBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::SinBounds(const interval& x) const
{
    return numericSinBounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Sin, x));
}

// Public API: Sinh encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Sinh(const interval& x) const
{
    return numericSinh(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Sinh, x));
}

// Public API: SinhBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::SinhBounds(const interval& x) const
{
    return numericSinhBounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Sinh, x));
}

// Public API: SoundFile encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::SoundFile(const interval& label) const
{
    return numericSoundFile(label).withInvalid(detail::inputInvalid(label));
}

// Public API: SoundFileBuffer encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::SoundFileBuffer(const interval& sf, const interval& x, const interval& y, const interval& z) const
{
    return numericSoundFileBuffer(sf, x, y, z).withInvalid(true);
}

// Public API: SoundFileLength encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::SoundFileLength(const interval& sf, const interval& x) const
{
    return numericSoundFileLength(sf, x).withInvalid(true);
}

// Soundfile extents are absent here, so indexed metadata/sample access remains
// uncertified until the compiler checks its resource-specific domain.
// Public API: SoundFileRate encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::SoundFileRate(const interval& sf, const interval& x) const
{
    return numericSoundFileRate(sf, x).withInvalid(true);
}

// Public API: Sqrt encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Sqrt(const interval& x) const
{
    return numericSqrt(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Sqrt, x));
}

// Public API: Sub encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Sub(const interval& xIn, const interval& yIn) const
{
    return numericSub(xIn, yIn).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Sub, xIn, yIn));
}

// Public API: Tan encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Tan(const interval& x) const
{
    return numericTan(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Tan, x));
}

// Public API: TanBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::TanBounds(const interval& x) const
{
    return numericTanBounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Tan, x));
}

// Public API: Tanh encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Tanh(const interval& x) const
{
    return numericTanh(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Tanh, x));
}

// Public API: TanhBounds encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::TanhBounds(const interval& x) const
{
    return numericTanhBounds(x).withInvalid(detail::unaryInvalid(detail::UnaryOp::Tanh, x));
}

// Public API: VBargraph encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::VBargraph(const interval& name, const interval& lo, const interval& hi, const interval& signal) const
{
    return numericVBargraph(name, lo, hi, signal).withInvalid(detail::inputInvalid(name, lo, hi, signal));
}

// Public API: VSlider encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::VSlider(const interval& name, const interval& init, const interval& lo, const interval& hi, const interval& step) const
{
    return numericVSlider(name, init, lo, hi, step).withInvalid(name.mayBeInvalid() || detail::widgetInvalid(init, lo, hi, step));
}

// Public API: WRTbl encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::WRTbl(const interval& n, const interval& g, const interval& wi, const interval& ws) const
{
    return numericWRTbl(n, g, wi, ws).withInvalid(detail::inputInvalid(n, g, wi, ws));
}

// Public API: Waveform encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Waveform(const std::vector<interval>& w) const
{
    return numericWaveform(w).withInvalid(std::any_of(w.begin(), w.end(), [](const interval& x) { return x.mayBeInvalid(); }));
}

// Public API: Xor encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::Xor(const interval& xInput, const interval& yInput) const
{
    return numericXor(xInput, yInput).withInvalid(detail::intCastInvalid(xInput) || detail::intCastInvalid(yInput));
}

// Internal transfer: fPow encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::fPow(const interval& x, const interval& y) const
{
    return numericfPow(x, y).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Pow, x, y));
}

// Internal transfer: iPow encloses valid numeric results and conservatively retains
// input invalidity and any possible operation-domain violation.
interval interval_algebra::iPow(const interval& x, const interval& y) const
{
    return numericiPow(x, y).withInvalid(detail::binaryInvalid(detail::ValidityBinary::Pow, x, y));
}

// Public API: scalar modulo forwards to the typed interval transfer; its domain
// checks and invalidity propagation are identical to the two-interval overload.
interval interval_algebra::Mod(const interval& x, double m) const
{
    return Mod(x, interval(m));
}

}  // namespace itv
