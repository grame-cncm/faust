#pragma once

#include "interval_def.hh"

#include "FaustAlgebra.hh"

namespace itv {
class interval_algebra : public FaustAlgebra<interval> {
   private:
    interval iPow(const interval& x, const interval& y) const;  // integer power, when x can be negative
    interval fPow(const interval& x, const interval& y) const;  // float power, when x is positive

   public:
    // Injections of external values
    interval IntNum(int x) const override;
    interval Int64Num(int64_t x) const override;
    interval FloatNum(double x) const override;
    interval Label(const std::string& x) const override;

    // Missing operations
    interval FixPointUpdate(const interval& x, const interval& y) const override;
    interval Input(const interval& c) const override;
    interval Output(const interval& c, const interval& y) const override;
    interval HBargraph(const interval& name, const interval& lo, const interval& hi,
                       const interval& signal) const override;
    interval VBargraph(const interval& name, const interval& lo, const interval& hi,
                       const interval& signal) const override;
    interval Gen(const interval& x) const override;
    interval Attach(const interval& x, const interval& y) const override;
    interval Enable(const interval& x, const interval& control) const override;
    interval Control(const interval& x, const interval& control) const override;
    interval AssertBounds(const interval& lo, const interval& hi, const interval& x) const override;
    interval Highest(const interval& x) const override;
    interval Lowest(const interval& x) const override;
    interval BitCast(const interval& x) const override;
    interval Select2(const interval& x, const interval& y, const interval& z) const override;
    interval Prefix(const interval& x, const interval& y) const override;
    interval RDTbl(const interval& wtbl, const interval& ri) const override;
    interval WRTbl(const interval& n, const interval& g, const interval& wi,
                   const interval& ws) const override;
    interval SoundFile(const interval& label) const override;
    interval SoundFileRate(const interval& sf, const interval& x) const override;
    interval SoundFileLength(const interval& sf, const interval& x) const override;
    interval SoundFileBuffer(const interval& sf, const interval& x, const interval& y,
                             const interval& z) const override;
    interval Waveform(const std::vector<interval>& w) const override;

    // Foreign functions
    interval ForeignFunction(int resultNature, const std::vector<interval>& args) const override;
    interval ForeignVar(int declaredNature, const interval& name,
                        const interval& file) const override;
    interval ForeignConst(int declaredNature, const interval& name,
                          const interval& file) const override;

    // User interface elements
    interval Button(const interval& name) const override;
    interval Checkbox(const interval& name) const override;
    interval VSlider(const interval& name, const interval& init, const interval& lo,
                     const interval& hi, const interval& step) const override;
    interval HSlider(const interval& name, const interval& init, const interval& lo,
                     const interval& hi, const interval& step) const override;
    interval NumEntry(const interval& name, const interval& init, const interval& lo,
                      const interval& hi, const interval& step) const override;

    interval Abs(const interval& x) const override;
    void     testAbs();
    //
    interval Add(const interval& x, const interval& y) const override;
    void     testAdd();
    //
    interval Sub(const interval& x, const interval& y) const override;
    void     testSub();
    //
    interval Mul(const interval& x, const interval& y) const override;
    void     testMul();
    //
    interval Div(const interval& x, const interval& y) const override;
    void     testDiv();
    //
    interval Inv(const interval& x) const override;
    void     testInv();
    //
    interval Neg(const interval& x) const override;
    void     testNeg();
    //
    interval Mod(const interval& x, double m) const;
    interval Mod(const interval& x, const interval& y) const override;
    void     testMod();
    //

    interval Acos(const interval& x) const override;
    void     testAcos();
    //
    interval Acosh(const interval& x) const override;
    void     testAcosh();
    //
    interval And(const interval& x, const interval& y) const override;
    void     testAnd();
    //
    interval Asin(const interval& x) const override;
    void     testAsin();
    //
    interval Asinh(const interval& x) const override;
    void     testAsinh();
    //
    interval Atan(const interval& x) const override;
    void     testAtan();
    //
    interval Atan2(const interval& x, const interval& y) const override;
    void     testAtan2();
    //
    interval Atanh(const interval& x) const override;
    void     testAtanh();
    //
    interval Ceil(const interval& x) const override;
    void     testCeil();
    interval Cos(const interval& x) const override;
    void     testCos();
    interval Cosh(const interval& x) const override;
    void     testCosh();
    interval Delay(const interval& x, const interval& y) const override;
    void     testDelay();
    interval Eq(const interval& x, const interval& y) const override;
    void     testEq();
    interval Exp(const interval& x) const override;
    void     testExp();
    interval Exp10(const interval& x) const override;
    interval FloatCast(const interval& x) const override;
    void     testFloatCast();
    interval Floor(const interval& x) const override;
    void     testFloor();
    interval Ge(const interval& x, const interval& y) const override;
    void     testGe();
    interval Gt(const interval& x, const interval& y) const override;
    void     testGt();
    interval IntCast(const interval& x) const override;
    void     testIntCast();
    interval Le(const interval& x, const interval& y) const override;
    void     testLe();
    interval Log(const interval& x) const override;
    void     testLog();
    interval Log10(const interval& x) const override;
    void     testLog10();
    interval Lsh(const interval& x, const interval& y) const override;
    void     testLsh();
    interval Lt(const interval& x, const interval& y) const override;
    void     testLt();
    interval Max(const interval& x, const interval& y) const override;
    void     testMax();
    interval Mem(const interval& x) const override;
    void     testMem();
    interval Min(const interval& x, const interval& y) const override;
    void     testMin();
    interval Ne(const interval& x, const interval& y) const override;
    void     testNe();
    interval Not(const interval& x) const override;
    void     testNot();
    interval Or(const interval& x, const interval& y) const override;
    void     testOr();
    interval Pow(const interval& x, const interval& y) const override;  // for all cases
    void     testPow();
    interval Remainder(const interval& x, const interval& y) const override;
    void     testRemainder();
    interval Rint(const interval& x) const override;
    void     testRint();
    interval Round(const interval& x) const override;
    void     testRound();
    interval ARsh(const interval& x, const interval& y) const override;
    interval LRsh(const interval& x, const interval& y) const override;
    void     testRsh();
    interval Sin(const interval& x) const override;
    void     testSin();
    interval Sinh(const interval& x) const override;
    void     testSinh();
    interval Sqrt(const interval& x) const override;
    void     testSqrt();
    interval Tan(const interval& x) const override;
    void     testTan();
    interval Tanh(const interval& x) const override;
    void     testTanh();
    interval Xor(const interval& x, const interval& y) const override;
    void     testXor();

    void testAll();
};
}  // namespace itv
