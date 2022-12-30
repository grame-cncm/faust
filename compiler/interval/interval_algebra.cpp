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
