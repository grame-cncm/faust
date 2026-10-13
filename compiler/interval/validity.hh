/* Copyright 2026 Yann Orlarey, Stéphane Letz
 * Licensed under the Apache License, Version 2.0 (see LICENSE).
 */
#pragma once

#include "directed_rounding.hh"

namespace itv {
namespace detail {

enum class ValidityBinary { Add, Sub, Mul, Div, Mod, Fmod, Remainder, Pow, Atan2 };

// Internal domain predicates: flags are independent of numeric emptiness. The
// predicates inspect target operands, after any implicit integer-to-float cast.
// IEEE infinities are valid unless an operation turns them into NaN; undefined
// casts, integer remainder and shifts are invalid under the declared contract.
template <typename... Inputs>
inline bool inputInvalid(const Inputs&... inputs)
{
    return (false || ... || inputs.mayBeInvalid());
}

inline bool unaryInvalid(UnaryOp op, const interval& input)
{
    if (input.isEmpty()) return input.mayBeInvalid();
    const interval x = floatingOperand(input);
    bool outside = false;
    switch (op) {
        case UnaryOp::Sqrt: outside = x.lo() < 0; break;
        case UnaryOp::Log:
        case UnaryOp::Log10: outside = x.lo() < 0; break;  // log(0) is -infinity
        case UnaryOp::Acos:
        case UnaryOp::Asin:
        case UnaryOp::Atanh: outside = x.lo() < -1 || x.hi() > 1; break;
        case UnaryOp::Acosh: outside = x.lo() < 1; break;
        case UnaryOp::Sin:
        case UnaryOp::Cos:
        case UnaryOp::Tan: outside = x.isUnbounded(); break;
        default: break;
    }
    return input.mayBeInvalid() || outside;
}

inline bool intCastInvalid(const interval& x)
{
    if (x.isEmpty() || x.lsb() >= 0) return x.mayBeInvalid();
    // The truncated integer, rather than the original real value, must fit.
    // These integer thresholds are exactly representable in binary64.
    return x.mayBeInvalid() || x.lo() <= -2147483649.0 || x.hi() >= 2147483648.0;
}

inline bool hasFiniteNonInteger(const interval& x)
{
    if (x.isEmpty() || x.lsb() >= 0) return false;
    if (x.lo() == x.hi()) return std::isfinite(x.lo()) && std::trunc(x.lo()) != x.lo();
    // Beyond the significand's integer threshold, every representable value is
    // integral. Inside it, conservatively include fractional values in a corridor.
    const double threshold = programPrecision() == 1 ? 0x1p23 : 0x1p52;
    return x.lo() < threshold && x.hi() > -threshold;
}

inline bool binaryInvalid(ValidityBinary op, const interval& xInput, const interval& yInput)
{
    const bool inherited = inputInvalid(xInput, yInput);
    if (xInput.isEmpty() || yInput.isEmpty()) return inherited;
    const bool integers = xInput.lsb() >= 0 && yInput.lsb() >= 0;
    if (integers && (op == ValidityBinary::Add || op == ValidityBinary::Sub || op == ValidityBinary::Mul))
        return inherited;  // int32 wrapping is defined by this library's contract
    if (integers && op == ValidityBinary::Mod) {
        const interval x = int32Hull(xInput), y = int32Hull(yInput);
        return inherited || y.hasZero() || (x.has(-2147483648.0) && y.has(-1));
    }
    if (integers && op == ValidityBinary::Pow)
        return inherited || int32Hull(yInput).lo() < 0;  // integer powers require nonnegative exponents
    const interval x = floatingOperand(xInput), y = floatingOperand(yInput);
    bool outside = false;
    switch (op) {
        case ValidityBinary::Add:
            outside = (x.has(HUGE_VAL) && y.has(-HUGE_VAL)) ||
                      (x.has(-HUGE_VAL) && y.has(HUGE_VAL));
            break;
        case ValidityBinary::Sub:
            outside = (x.has(HUGE_VAL) && y.has(HUGE_VAL)) ||
                      (x.has(-HUGE_VAL) && y.has(-HUGE_VAL));
            break;
        case ValidityBinary::Mul:
            outside = (x.hasZero() && y.isUnbounded()) || (y.hasZero() && x.isUnbounded());
            break;
        case ValidityBinary::Div:
            outside = (x.hasZero() && y.hasZero()) || (x.isUnbounded() && y.isUnbounded());
            break;
        case ValidityBinary::Mod:
        case ValidityBinary::Fmod:
        case ValidityBinary::Remainder:
            outside = x.isUnbounded() || y.hasZero();
            break;
        case ValidityBinary::Pow:
            // pow(-infinity, noninteger) is an IEEE special case with a numeric
            // result. Only negative FINITE bases with noninteger exponents fail.
            outside = x.lo() < 0 && x.hi() > -HUGE_VAL && hasFiniteNonInteger(y);
            break;
        default: break;  // atan2 handles zero and infinite arguments
    }
    return inherited || outside;
}

inline bool shiftInvalid(const interval& x, const interval& counts)
{
    if (x.isEmpty() || counts.isEmpty()) return inputInvalid(x, counts);
    if (intCastInvalid(x) || intCastInvalid(counts)) return true;
    const interval k = int32Hull(counts);
    return std::trunc(k.lo()) < 0 || std::trunc(k.hi()) > 31;
}

inline bool delayInvalid(const interval& signal, const interval& amount)
{
    if (signal.isEmpty() || amount.isEmpty()) return inputInvalid(signal, amount);
    const interval k = int32Hull(amount);
    return inputInvalid(signal, amount) || intCastInvalid(amount) || std::trunc(k.lo()) < 0;
}

inline bool assertionInvalid(const interval& lo, const interval& hi, const interval& x)
{
    if (lo.isEmpty() || hi.isEmpty() || x.isEmpty()) return inputInvalid(lo, hi, x);
    // A range assertion can refine numeric bounds only under its stated premise.
    // Keep a violated or unproved premise visible instead of certifying the crop.
    return inputInvalid(lo, hi, x) || lo.hi() > hi.lo() ||
           x.lo() < lo.hi() || x.hi() > hi.lo();
}

inline bool tableWriteInvalid(const interval& size, const interval& index)
{
    if (size.isEmpty() || index.isEmpty()) return inputInvalid(size, index);
    const interval i = int32Hull(index);
    return inputInvalid(size, index) || !size.isconst() || size.lsb() < 0 ||
           size.lo() <= 0 || intCastInvalid(index) || std::trunc(i.lo()) < 0 ||
           std::trunc(i.hi()) >= size.lo();
}

inline bool widgetInvalid(const interval& init, const interval& lo,
                          const interval& hi, const interval& step)
{
    if (init.isEmpty() || lo.isEmpty() || hi.isEmpty() || step.isEmpty())
        return inputInvalid(init, lo, hi, step);
    // The declared finite range includes initialization. A contradictory widget
    // declaration cannot justify certifying the advertised bounds.
    return inputInvalid(init, lo, hi, step) || !init.isBounded() || !lo.isBounded() ||
           !hi.isBounded() || !step.isBounded() || lo.hi() > hi.lo() ||
           init.lo() < lo.hi() || init.hi() > hi.lo() || step.lo() < 0;
}

}  // namespace detail
}  // namespace itv
