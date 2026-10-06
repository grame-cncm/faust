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
#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"
namespace itv {

//------------------------------------------------------------------------------------------
// The functions of the libm. Their bounds are computed by the libm of the machine that
// computes the intervals ; the program calls the libm of its target. Neither is
// guaranteed correctly rounded (IEEE 754 requires it of +, -, *, /, sqrt only) : the
// bounds widen by 2 ulps of the program's precision (libmBounds), within the image of
// the function, unless the user declares correctly rounded libms (libmCompensation).
//------------------------------------------------------------------------------------------
interval interval_algebra::Acos(const interval& x) const
{
    return libmBounds(AcosBounds(x), 0, M_PI);
}
interval interval_algebra::Acosh(const interval& x) const
{
    return libmBounds(AcoshBounds(x), 0, HUGE_VAL);
}
interval interval_algebra::Asin(const interval& x) const
{
    return libmBounds(AsinBounds(x), -HUGE_VAL, HUGE_VAL);
}
interval interval_algebra::Asinh(const interval& x) const
{
    return libmBounds(AsinhBounds(x), -HUGE_VAL, HUGE_VAL);
}
interval interval_algebra::Atan(const interval& x) const
{
    return libmBounds(AtanBounds(x), -HUGE_VAL, HUGE_VAL);
}
interval interval_algebra::Atan2(const interval& x, const interval& y) const
{
    return libmBounds(Atan2Bounds(x, y), -HUGE_VAL, HUGE_VAL);
}
interval interval_algebra::Atanh(const interval& x) const
{
    return libmBounds(AtanhBounds(x), -HUGE_VAL, HUGE_VAL);
}
interval interval_algebra::Cos(const interval& x) const
{
    return libmBounds(CosBounds(x), -1, 1);
}
interval interval_algebra::Cosh(const interval& x) const
{
    return libmBounds(CoshBounds(x), 1, HUGE_VAL);
}
interval interval_algebra::Exp(const interval& x) const
{
    return libmBounds(ExpBounds(x), 0, HUGE_VAL);
}
interval interval_algebra::Log(const interval& x) const
{
    return libmBounds(LogBounds(x), -HUGE_VAL, HUGE_VAL);
}
interval interval_algebra::Log10(const interval& x) const
{
    return libmBounds(Log10Bounds(x), -HUGE_VAL, HUGE_VAL);
}
interval interval_algebra::Pow(const interval& x, const interval& y) const
{
    return libmBounds(PowBounds(x, y), -HUGE_VAL, HUGE_VAL);
}
interval interval_algebra::Sin(const interval& x) const
{
    return libmBounds(SinBounds(x), -1, 1);
}
interval interval_algebra::Sinh(const interval& x) const
{
    return libmBounds(SinhBounds(x), -HUGE_VAL, HUGE_VAL);
}
interval interval_algebra::Tan(const interval& x) const
{
    return libmBounds(TanBounds(x), -HUGE_VAL, HUGE_VAL);
}
interval interval_algebra::Tanh(const interval& x) const
{
    return libmBounds(TanhBounds(x), -1, 1);
}
void interval_algebra::testAll()
{
    testAbs();
    testAcos();
    testAcosh();
    testAdd();
    testAnd();
    testAsin();
    testAsinh();
    testAtan();
    testAtanh();
    testCeil();
    testCos();
    testCosh();
    testDelay();
    testDiv();
    testEq();
    testExp();
    testFloatCast();
    testFloor();
    testGe();
    testGt();
    testIntCast();
    testInv();
    testLog();
    testLog10();
    testLsh();
    testLt();
    testMax();
    testMem();
    testMin();
    testMod();
    testMul();
    testNe();
    testNeg();
    testNot();
    testOr();
    testPow();
    testRint();
    testRound();
    testRsh();
    testSin();
    testSinh();
    testSqrt();
    testSub();
    testTan();
    testTanh();
    testXor();
}
}  // namespace itv
