/* Copyright 2023 Yann ORLAREY
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

#include "bitwiseOperations.hh"
#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Xor
// interval Xor(const interval& x, const interval& y) const;
// void testXor() const;
static double myXor(double x, double y)
{
    auto a = saturatedIntCast(x);
    auto b = saturatedIntCast(y);
    int  c = a ^ b;
    return double(c);
}

// BRUTE FORCE
interval interval_algebra::Xor(const interval& x, const interval& y) const
{
    if (x.isEmpty() || y.isEmpty()) return {};
    auto x0 = saturatedIntCast(x.lo());
    auto x1 = saturatedIntCast(x.hi());
    auto y0 = saturatedIntCast(y.lo());
    auto y1 = saturatedIntCast(y.hi());

    SInterval z = bitwiseSignedXOr({x0, x1}, {y0, y1});

    int precision = std::min(x.lsb(), y.lsb()); // output precision cannot be finer than that of the input intervals

    // if both intervals are singletons, the lsb is the least significant bit of the only element of the interval
    if (x0 == x1 and y0 == y1)
    {
        int v = x0^y0;
        precision = 0;    
        while ((v & 1) == 0 and v != 0) // while we encounter zeroes at the lower end of v
        {
            v = v/2;
            precision++;
        }
    }

    // if only one of the intervals is a singleton, all of the variation is due to the other interval, which transmits its lsb
    if (x0 == x1)
        precision = y.lsb();

    if (y1 == y0)
        precision = x.lsb();
        
    return {double(z.lo), double(z.hi), precision};
}

void interval_algebra::testXor() const
{
    std::random_device R;
    std::default_random_engine generator(R());
    std::uniform_int_distribution lx(0, 10);
    std::uniform_int_distribution ly(0, 10);

    analyzeBinaryMethod(10, 20000, "Xor", interval(-1000, -800, lx(generator)), interval(127, 127, ly(generator)), myXor, &interval_algebra::Xor);
    analyzeBinaryMethod(10, 20000, "Xor", interval(-1000, -800, lx(generator)), interval(127, 127, ly(generator)), myXor, &interval_algebra::Xor);
    
    analyzeBinaryMethod(10, 20000, "Xor", interval(-1000, -800, lx(generator)), interval(123, 123, ly(generator)), myXor, &interval_algebra::Xor);
    analyzeBinaryMethod(10, 20000, "Xor", interval(-1000, -800, lx(generator)), interval(123, 123, ly(generator)), myXor, &interval_algebra::Xor);

    analyzeBinaryMethod(10, 20000, "Xor", interval(-128, 128, lx(generator)), interval(127, 127, ly(generator)), myXor, &interval_algebra::Xor);
    analyzeBinaryMethod(10, 20000, "Xor", interval(-128, 128, lx(generator)), interval(127, 127, ly(generator)), myXor, &interval_algebra::Xor);

    analyzeBinaryMethod(10, 20000, "Xor", interval(0, 1000, lx(generator)), interval(63, 127, ly(generator)), myXor, &interval_algebra::Xor);
    analyzeBinaryMethod(10, 20000, "Xor", interval(0, 1000, lx(generator)), interval(63, 127, ly(generator)), myXor, &interval_algebra::Xor);

    analyzeBinaryMethod(10, 20000, "Xor", interval(-1000, 1000, lx(generator)), interval(63, 127, ly(generator)), myXor, &interval_algebra::Xor);
    analyzeBinaryMethod(10, 20000, "Xor", interval(-1000, 1000, lx(generator)), interval(63, 127, ly(generator)), myXor, &interval_algebra::Xor);

    analyzeBinaryMethod(10, 2000, "Xor", interval(10,20), interval(0), myXor, &interval_algebra::Xor);
    analyzeBinaryMethod(10, 2000, "Xor", interval(0), interval(15, 25), myXor, &interval_algebra::Xor);
    analyzeBinaryMethod(10, 2000, "Xor", interval(0), interval(0), myXor, &interval_algebra::Xor);
}
}  // namespace itv
