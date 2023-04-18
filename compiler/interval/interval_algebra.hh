#pragma once

#include "interval_def.hh"

#include "faust_algebra.hh"

namespace itv {
class interval_algebra : public faust_algebra<interval> {
   private:
    interval iPow(const interval& x, const interval& y) const;  // integer power, when x can be negative
    interval fPow(const interval& x, const interval& y) const;  // float power, when x is positive

   public:
    // Injections of external values
    interval String(const std::string& x) const;
    interval IntNum(int x) const;
    interval Int64Num(int64_t x) const;
    interval FloatNum(double x) const;

    // User interface elements
    interval Button(const interval& name) const;
    interval Checkbox(const interval& name) const;
    interval VSlider(const interval& name, const interval& init, const interval& lo, const interval& hi,
                     const interval& step) const;
    interval HSlider(const interval& name, const interval& init, const interval& lo, const interval& hi,
                     const interval& step) const;
    interval NumEntry(const interval& name, const interval& init, const interval& lo, const interval& hi,
                      const interval& step) const;

    interval Abs(const interval& x) const;
    void     testAbs() const;
    //
    interval Add(const interval& x, const interval& y) const;
    void     testAdd() const;
    //
    interval Sub(const interval& x, const interval& y) const;
    void     testSub() const;
    //
    interval Mul(const interval& x, const interval& y) const;
    void     testMul() const;
    //
    interval Div(const interval& x, const interval& y) const;
    void     testDiv() const;
    //
    interval Inv(const interval& x) const;
    void     testInv() const;
    //
    interval Neg(const interval& x) const;
    void     testNeg() const;
    //
    interval Mod(const interval& x, double m) const;
    interval Mod(const interval& x, const interval& y) const;
    void     testMod() const;
    //

    interval Acos(const interval& x) const;
    void     testAcos() const;
    //
    interval Acosh(const interval& x) const;
    void     testAcosh() const;
    //
    interval And(const interval& x, const interval& y) const;
    void     testAnd() const;
    //
    interval Asin(const interval& x) const;
    void     testAsin() const;
    //
    interval Asinh(const interval& x) const;
    void     testAsinh() const;
    //
    interval Atan(const interval& x) const;
    void     testAtan() const;
    //
    interval Atan2(const interval& x, const interval& y) const;
    void     testAtan2() const;
    //
    interval Atanh(const interval& x) const;
    void     testAtanh() const;
    //
    interval Ceil(const interval& x) const;
    void     testCeil() const;
    interval Cos(const interval& x) const;
    void     testCos() const;
    interval Cosh(const interval& x) const;
    void     testCosh() const;
    interval Delay(const interval& x, const interval& y) const;
    void     testDelay() const;
    interval Eq(const interval& x, const interval& y) const;
    void     testEq() const;
    interval Exp(const interval& x) const;
    void     testExp() const;
    interval FloatCast(const interval& x) const;
    void     testFloatCast() const;
    interval Floor(const interval& x) const;
    void     testFloor() const;
    interval Ge(const interval& x, const interval& y) const;
    void     testGe() const;
    interval Gt(const interval& x, const interval& y) const;
    void     testGt() const;
    interval IntCast(const interval& x) const;
    void     testIntCast() const;
    interval Le(const interval& x, const interval& y) const;
    void     testLe() const;
    interval Log(const interval& x) const;
    void     testLog() const;
    interval Log10(const interval& x) const;
    void     testLog10() const;
    interval Lsh(const interval& x, const interval& y) const;
    void     testLsh() const;
    interval Lt(const interval& x, const interval& y) const;
    void     testLt() const;
    interval Max(const interval& x, const interval& y) const;
    void     testMax() const;
    interval Mem(const interval& x) const;
    void     testMem() const;
    interval Min(const interval& x, const interval& y) const;
    void     testMin() const;
    interval Ne(const interval& x, const interval& y) const;
    void     testNe() const;
    interval Not(const interval& x) const;
    void     testNot() const;
    interval Or(const interval& x, const interval& y) const;
    void     testOr() const;
    interval Pow(const interval& x, const interval& y) const;  // for all cases
    void     testPow() const;
    interval Remainder(const interval& x) const;
    void     testRemainder() const;
    interval Rint(const interval& x) const;
    void     testRint() const;
    interval Rsh(const interval& x, const interval& y) const;
    void     testRsh() const;
    interval Sin(const interval& x) const;
    void     testSin() const;
    interval Sinh(const interval& x) const;
    void     testSinh() const;
    interval Sqrt(const interval& x) const;
    void     testSqrt() const;
    interval Tan(const interval& x) const;
    void     testTan() const;
    interval Tanh(const interval& x) const;
    void     testTanh() const;
    interval Xor(const interval& x, const interval& y) const;
    void     testXor() const;

    void testAll() const;
};
}  // namespace itv
