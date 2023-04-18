#pragma once

#include "interval_def.hh"

namespace itv {

// A faust algebra is the set of primitive operations available in Faust on signals for example
template <typename T>
class faust_algebra {
   public:
    // Injections of external values
    T String(const std::string& x) const;
    T IntNum(int x) const;
    T Int64Num(int64_t x) const;
    T FloatNum(double x) const;

    // User interface elements
    T Button(const T& name) const;
    T Checkbox(const T& name) const;
    T VSlider(const T& name, const T& init, const T& lo, const T& hi, const T& step) const;
    T HSlider(const T& name, const T& init, const T& lo, const T& hi, const T& step) const;
    T NumEntry(const T& name, const T& init, const T& lo, const T& hi, const T& step) const;

    // Operations
    T Abs(const T& x) const;
    T Add(const T& x, const T& y) const;
    T Sub(const T& x, const T& y) const;
    T Mul(const T& x, const T& y) const;
    T Div(const T& x, const T& y) const;
    T Inv(const T& x) const;
    T Neg(const T& x) const;
    T Mod(const T& x, const T& y) const;
    T Acos(const T& x) const;
    T Acosh(const T& x) const;
    T And(const T& x, const T& y) const;
    T Asin(const T& x) const;
    T Asinh(const T& x) const;
    T Atan(const T& x) const;
    T Atan2(const T& x, const T& y) const;
    T Atanh(const T& x) const;
    T Ceil(const T& x) const;
    T Cos(const T& x) const;
    T Cosh(const T& x) const;
    T Delay(const T& x, const T& y) const;
    T Eq(const T& x, const T& y) const;
    T Exp(const T& x) const;
    T FloatCast(const T& x) const;
    T Floor(const T& x) const;
    T Ge(const T& x, const T& y) const;
    T Gt(const T& x, const T& y) const;
    T IntCast(const T& x) const;
    T Le(const T& x, const T& y) const;
    T Log(const T& x) const;
    T Log10(const T& x) const;
    T Lsh(const T& x, const T& y) const;
    T Lt(const T& x, const T& y) const;
    T Max(const T& x, const T& y) const;
    T Mem(const T& x) const;
    T Min(const T& x, const T& y) const;
    T Ne(const T& x, const T& y) const;
    T Not(const T& x) const;
    T Or(const T& x, const T& y) const;
    T Pow(const T& x, const T& y) const;
    T Remainder(const T& x) const;
    T Rint(const T& x) const;
    T Rsh(const T& x, const T& y) const;
    T Sin(const T& x) const;
    T Sinh(const T& x) const;
    T Sqrt(const T& x) const;
    T Tan(const T& x) const;
    T Tanh(const T& x) const;
    T Xor(const T& x, const T& y) const;
};
}  // namespace itv

