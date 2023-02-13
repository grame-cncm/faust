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
void interval_algebra::testAll() const
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
