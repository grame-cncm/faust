#pragma once

#include "interval_def.hh"

#include "FaustAlgebra.hh"

namespace itv
{
class interval_algebra : public FaustAlgebra<interval>
{
   private:
    interval iPow(const interval& x, const interval& y);  // integer power, when x can be negative
    interval fPow(const interval& x, const interval& y);  // float power, when x is positive

   public:
    // Injections of external values
    interval Nil() override;
    interval IntNum(int x) override;
    interval Int64Num(int64_t x) override;
    interval FloatNum(double x) override;
    interval Label(const std::string& x) override;

    // Missing operations
    interval FixPointUpdate(const interval& x, const interval& y) override;
    interval Input(const interval& c) override;
    interval Output(const interval& c, const interval& y) override;
    interval HBargraph(const interval& name, const interval& lo, const interval& hi) override;
    interval VBargraph(const interval& name, const interval& lo, const interval& hi) override;
    interval Gen(const interval& x) override;
    interval Attach(const interval& x, const interval& y) override;
    interval Highest(const interval& x) override;
    interval Lowest(const interval& x) override;
    interval BitCast(const interval& x) override;
    interval Select2(const interval& x, const interval& y, const interval& z) override;
    interval Prefix(const interval& x, const interval& y) override;
    interval RDTbl(const interval& wtbl, const interval& ri) override;
    interval WRTbl(const interval& n, const interval& g, const interval& wi, const interval& ws) override;
    interval SoundFile(const interval& label) override;
    interval SoundFileRate(const interval& sf, const interval& x) override;
    interval SoundFileLength(const interval& sf, const interval& x) override;
    interval SoundFileBuffer(const interval& sf, const interval& x, const interval& y, const interval& z) override;
    interval Waveform(const std::vector<interval>& w) override;

    // Foreign functions
    interval ForeignFunction(const std::vector<interval>& ff) override;
    interval ForeignVar(const interval& type, const interval& name, const interval& file) override;
    interval ForeignConst(const interval& type, const interval& name, const interval& file) override;

    // User interface elements
    interval Button(const interval& name) override;
    interval Checkbox(const interval& name) override;
    interval VSlider(const interval& name, const interval& init, const interval& lo, const interval& hi,
                     const interval& step) override;
    interval HSlider(const interval& name, const interval& init, const interval& lo, const interval& hi,
                     const interval& step) override;
    interval NumEntry(const interval& name, const interval& init, const interval& lo, const interval& hi,
                      const interval& step) override;

    interval Abs(const interval& x) override;
    void     testAbs();
    //
    interval Add(const interval& x, const interval& y) override;
    void     testAdd();
    //
    interval Sub(const interval& x, const interval& y) override;
    void     testSub();
    //
    interval Mul(const interval& x, const interval& y) override;
    void     testMul();
    //
    interval Div(const interval& x, const interval& y) override;
    void     testDiv();
    //
    interval Inv(const interval& x) override;
    void     testInv();
    //
    interval Neg(const interval& x) override;
    void     testNeg();
    //
    interval Mod(const interval& x, double m);
    interval Mod(const interval& x, const interval& y) override;
    void     testMod();
    //

    interval Acos(const interval& x) override;
    void     testAcos();
    //
    interval Acosh(const interval& x) override;
    void     testAcosh();
    //
    interval And(const interval& x, const interval& y) override;
    void     testAnd();
    //
    interval Asin(const interval& x) override;
    void     testAsin();
    //
    interval Asinh(const interval& x) override;
    void     testAsinh();
    //
    interval Atan(const interval& x) override;
    void     testAtan();
    //
    interval Atan2(const interval& x, const interval& y) override;
    void     testAtan2();
    //
    interval Atanh(const interval& x) override;
    void     testAtanh();
    //
    interval Ceil(const interval& x) override;
    void     testCeil();
    interval Cos(const interval& x) override;
    void     testCos();
    interval Cosh(const interval& x) override;
    void     testCosh();
    interval Delay(const interval& x, const interval& y) override;
    void     testDelay();
    interval Eq(const interval& x, const interval& y) override;
    void     testEq();
    interval Exp(const interval& x) override;
    void     testExp();
    interval FloatCast(const interval& x) override;
    void     testFloatCast();
    interval Floor(const interval& x) override;
    void     testFloor();
    interval Ge(const interval& x, const interval& y) override;
    void     testGe();
    interval Gt(const interval& x, const interval& y) override;
    void     testGt();
    interval IntCast(const interval& x) override;
    void     testIntCast();
    interval Le(const interval& x, const interval& y) override;
    void     testLe();
    interval Log(const interval& x) override;
    void     testLog();
    interval Log10(const interval& x) override;
    void     testLog10();
    interval Lsh(const interval& x, const interval& y) override;
    void     testLsh();
    interval Lt(const interval& x, const interval& y) override;
    void     testLt();
    interval Max(const interval& x, const interval& y) override;
    void     testMax();
    interval Mem(const interval& x) override;
    void     testMem();
    interval Min(const interval& x, const interval& y) override;
    void     testMin();
    interval Ne(const interval& x, const interval& y) override;
    void     testNe();
    interval Not(const interval& x) override;
    void     testNot();
    interval Or(const interval& x, const interval& y) override;
    void     testOr();
    interval Pow(const interval& x, const interval& y) override;  // for all cases
    void     testPow();
    interval Remainder(const interval& x) override;
    void     testRemainder();
    interval Rint(const interval& x) override;
    void     testRint();
    interval Rsh(const interval& x, const interval& y) override;
    void     testRsh();
    interval Sin(const interval& x) override;
    void     testSin();
    interval Sinh(const interval& x) override;
    void     testSinh();
    interval Sqrt(const interval& x) override;
    void     testSqrt();
    interval Tan(const interval& x) override;
    void     testTan();
    interval Tanh(const interval& x) override;
    void     testTanh();
    interval Xor(const interval& x, const interval& y) override;
    void     testXor();

    void testAll();
};
}  // namespace itv
