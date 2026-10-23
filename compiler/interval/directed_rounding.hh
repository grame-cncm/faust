/* Copyright 2020-2026 Yann Orlarey, Agathe Herrou, Stéphane Letz
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <utility>

#include "interval_def.hh"

namespace itv::detail {

// Internal numerical kernel. Inputs are exact binary64 values; directed results
// enclose the mathematical operation, including binary64 underflow and overflow.
// Exact dyadic comparisons and bounded reference series do not change host fenv.
enum class Direction { Down, Up };
enum class BinaryOp { Add, Sub, Mul, Div, Pow, Atan2, Fmod, Remainder };
enum class UnaryOp {
    Sqrt, Acos, Acosh, Asin, Asinh, Atan, Atanh, Cos, Cosh,
    Exp, Log, Log10, Sin, Sinh, Tan, Tanh
};

// Float reuses the binary64 proof, then interval construction narrows outward.
// Quad/fixed keep their old rules; the analyzer never narrows a reference step.
inline bool usesNativeBounds() { return modelPrecision() == 1 || modelPrecision() == 2; }

// LSB is the nature marker independently of the program's floating precision.
// Only bounded int32 corridors may reach the integer rules' C++ endpoint casts.
inline bool hasInt32Bounds(const interval& x)
{
    return x.lsb() >= 0 && x.lo() >= -2147483648.0 && x.hi() <= 2147483647.0;
}

// Under wrapping semantics an integer corridor outside int32, including an
// infinite widening or an affine horizon overflow, has lost its signed range.
// Use the full int32 hull before ANY operation or conversion, retaining nature.
inline interval int32Hull(const interval& x)
{
    if (x.isEmpty() || x.lsb() < 0 || hasInt32Bounds(x)) return x;
    return {-2147483648.0, 2147483647.0, x.lsb(), x.mayBeInvalid()};
}

// Normalize each integer even in a mixed expression: conversion to floating
// point must include negative states reachable through an earlier integer wrap.
inline std::pair<interval, interval> int32Operands(const interval& x, const interval& y)
{
    return {int32Hull(x), int32Hull(y)};
}

// Floating results never become int32 because their values happen to be integral.
// The sign convention applies in double as well as single precision.
inline int floatingLSB(int lsb) { return std::min(lsb, -1); }

// Convert an integer operand once to the target floating type before evaluation.
// Nearest rounding is monotone; already-floating corridors are unchanged. A
// widened integer first recovers its signed hull, then loses the integer marker.
inline interval floatingOperand(const interval& input)
{
    const interval x = int32Hull(input);
    return x.isEmpty() || x.lsb() < 0 ? x
        : interval(programBound(x.lo()), programBound(x.hi()), -24, x.mayBeInvalid());
}

// Comparisons and min/max convert both operands when either is floating. Pure
// integer comparisons keep exact endpoints, notably above 2^24 in float mode.
inline std::pair<interval, interval> comparisonOperands(const interval& x, const interval& y)
{
    const auto operands = int32Operands(x, y);
    if (x.lsb() < 0 || y.lsb() < 0)
        return {floatingOperand(operands.first), floatingOperand(operands.second)};
    return operands;
}

// Metadata must not overflow signed int when an underflowed power already has
// an extreme grid exponent. INT_MIN is reserved by interval's constructor.
inline int sumLSB(int a, int b)
{
    return static_cast<int>(std::clamp<int64_t>(int64_t(a) + int64_t(b), INT_MIN + 1LL, INT_MAX));
}

double directedBinary(BinaryOp op, double x, double y, Direction direction);

// The exact sum x + y rounded once to nearest, ties to even, in the program's precision
// (float or double) : what the program computes for the operands x and y. Rounding to
// nearest is nondecreasing, so for program values u <= x and v <= y the program's
// u + v is at most nearestSum(x, y) (and symmetrically). Without a nearest host
// rounding mode, the outward bound in the given direction.
double nearestSum(double x, double y, Direction fallback);
double directedUnary(UnaryOp op, double x, Direction direction);
double directedPi(Direction direction);

// Internal exact power-of-two scaling, rounded outward including subnormals.
// The exponent is a bounded internal range-reduction exponent, not arbitrary int.
double directedScale(double x, int exponent, Direction direction);

// Numeric image on the valid real domain: outward binary64 reference steps,
// then interval construction narrows outward in float mode. NaN is
// still represented by the library's historical empty convention, not tracked.
// The LSB stamp is a fallback estimate, separate from the bound inclusion proof.
interval doubleUnaryBounds(UnaryOp op, const interval& x);
interval doubleAtan2Bounds(const interval& y, const interval& x);
interval doublePowBounds(const interval& x, const interval& y);
interval doubleFmodBounds(const interval& x, const interval& y);

}  // namespace itv::detail
