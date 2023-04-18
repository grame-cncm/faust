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

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Acos
// interval Acos(const interval& x) const;
// void testAcos() const;

interval interval_algebra::Abs(const interval& x) const
{
    // precision stays the same
    if (x.lo() >= 0) return x; 
    if (x.hi() <= 0) return {-x.hi(), -x.lo(), x.lsb()}; 
    return {0, std::max(std::abs(x.lo()), std::abs(x.hi())), x.lsb()};
}

void interval_algebra::testAbs() const
{
    analyzeUnaryMethod(10, 10000, "abs", interval(-10, 10, 0), [](double x){
        return std::abs(x);}, &interval_algebra::Abs);
    analyzeUnaryMethod(10, 10000, "abs", interval(-10, 10, -15), [](double x){
        return std::abs(x);}, &interval_algebra::Abs);
        
}
}  // namespace itv