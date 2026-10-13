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
#include "directed_rounding.hh"
namespace itv {

//------------------------------------------------------------------------------------------
// Public numeric functions: *Bounds computes the reference image (native outward bounds
// in float/double mode); libmBounds then adds the historical two-ULP target margin.
// This empirical margin does not certify an arbitrary target libm. A caller can
// inspect the reference through *Bounds independently of libmCompensation.
//------------------------------------------------------------------------------------------
interval interval_algebra::numericAcos(const interval& x) const
{
    return libmBounds(AcosBounds(x), 0, detail::usesNativeBounds()
        ? detail::directedPi(detail::Direction::Up) : M_PI);
}
interval interval_algebra::numericAcosh(const interval& x) const
{
    return libmBounds(AcoshBounds(x), 0, HUGE_VAL);
}
interval interval_algebra::numericAsin(const interval& x) const
{
    return libmBounds(AsinBounds(x), -HUGE_VAL, HUGE_VAL);
}
interval interval_algebra::numericAsinh(const interval& x) const
{
    return libmBounds(AsinhBounds(x), -HUGE_VAL, HUGE_VAL);
}
interval interval_algebra::numericAtan(const interval& x) const
{
    return libmBounds(AtanBounds(x), -HUGE_VAL, HUGE_VAL);
}
interval interval_algebra::numericAtan2(const interval& x, const interval& y) const
{
    return libmBounds(Atan2Bounds(x, y), -HUGE_VAL, HUGE_VAL);
}
interval interval_algebra::numericAtanh(const interval& x) const
{
    return libmBounds(AtanhBounds(x), -HUGE_VAL, HUGE_VAL);
}
interval interval_algebra::numericCos(const interval& x) const
{
    return libmBounds(CosBounds(x), -1, 1);
}
interval interval_algebra::numericCosh(const interval& x) const
{
    return libmBounds(CoshBounds(x), 1, HUGE_VAL);
}
interval interval_algebra::numericExp(const interval& x) const
{
    return libmBounds(ExpBounds(x), 0, HUGE_VAL);
}
interval interval_algebra::numericLog(const interval& x) const
{
    return libmBounds(LogBounds(x), -HUGE_VAL, HUGE_VAL);
}
interval interval_algebra::numericLog10(const interval& x) const
{
    return libmBounds(Log10Bounds(x), -HUGE_VAL, HUGE_VAL);
}
interval interval_algebra::numericPow(const interval& x, const interval& y) const
{
    return libmBounds(PowBounds(x, y), -HUGE_VAL, HUGE_VAL);
}
interval interval_algebra::numericSin(const interval& x) const
{
    return libmBounds(SinBounds(x), -1, 1);
}
interval interval_algebra::numericSinh(const interval& x) const
{
    return libmBounds(SinhBounds(x), -HUGE_VAL, HUGE_VAL);
}
interval interval_algebra::numericTan(const interval& x) const
{
    return libmBounds(TanBounds(x), -HUGE_VAL, HUGE_VAL);
}
interval interval_algebra::numericTanh(const interval& x) const
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
