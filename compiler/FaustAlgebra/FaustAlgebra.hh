#ifndef FAUSTALGEBRA_HH
#define FAUSTALGEBRA_HH

#include <cstdint>
#include <string>
#include <vector>

//=====================================================================================================================
// A Faust Algebra is a class grouping the set of primitive operations available
// on Faust signals. Derived algebras specify the carrier type T and implement
// each primitive operation for that type. Examples include interval, type
// inference, expression tree and compiler algebras.
//=====================================================================================================================

template <typename T>
class FaustAlgebra
{
   public:
    //--------------------------------------------------------------------------------
    // List of all the primitive operations
    //--------------------------------------------------------------------------------

    // Injections of external values (numbers and strings)
    virtual T Nil()                       = 0;
    virtual T IntNum(int x)               = 0;
    virtual T Int64Num(int64_t x)         = 0;
    virtual T FloatNum(double x)          = 0;
    virtual T Label(const std::string& s) = 0;

    // Used when searching for fixpoint
    virtual T FixPointUpdate(const T& x, const T& y) = 0;

    // Input Output Operations
    virtual T Input(const T& chan)              = 0;
    virtual T Output(const T& chan, const T& x) = 0;

    // User Interface Elements
    virtual T Button(const T& name)                                                          = 0;
    virtual T Checkbox(const T& name)                                                        = 0;
    virtual T VSlider(const T& name, const T& init, const T& lo, const T& hi, const T& step) = 0;
    virtual T HSlider(const T& name, const T& init, const T& lo, const T& hi, const T& step) = 0;
    // Bargraphs are signal nodes, so the displayed signal must participate in
    // every interpretation rather than being supplied by an implicit caller.
    virtual T HBargraph(const T& name, const T& lo, const T& hi, const T& signal)             = 0;
    virtual T VBargraph(const T& name, const T& lo, const T& hi, const T& signal)             = 0;
    virtual T NumEntry(const T& name, const T& init, const T& lo, const T& hi, const T& step) = 0;
    // Effect and control wrappers expose both dependencies even when an
    // interpretation ultimately preserves the value carried by x.
    virtual T Attach(const T& x, const T& y)        = 0;
    virtual T Enable(const T& x, const T& control)  = 0;
    virtual T Control(const T& x, const T& control) = 0;

    // Numerical Operations
    virtual T Abs(const T& x)               = 0;
    virtual T Highest(const T& x)           = 0;
    virtual T Lowest(const T& x)            = 0;
    virtual T Add(const T& x, const T& y)   = 0;
    virtual T Sub(const T& x, const T& y)   = 0;
    virtual T Mul(const T& x, const T& y)   = 0;
    virtual T Div(const T& x, const T& y)   = 0;
    virtual T Inv(const T& x)               = 0;
    virtual T Neg(const T& x)               = 0;
    virtual T Mod(const T& x, const T& y)   = 0;
    virtual T Acos(const T& x)              = 0;
    virtual T Acosh(const T& x)             = 0;
    virtual T And(const T& x, const T& y)   = 0;
    virtual T Asin(const T& x)              = 0;
    virtual T Asinh(const T& x)             = 0;
    virtual T Atan(const T& x)              = 0;
    virtual T Atan2(const T& x, const T& y) = 0;
    virtual T Atanh(const T& x)             = 0;
    virtual T Ceil(const T& x)              = 0;
    virtual T Cos(const T& x)               = 0;
    virtual T Cosh(const T& x)              = 0;
    virtual T Eq(const T& x, const T& y)    = 0;
    virtual T Exp(const T& x)               = 0;
    virtual T Exp10(const T& x)             = 0;
    virtual T FloatCast(const T& x)         = 0;
    virtual T BitCast(const T& x)           = 0;
    virtual T Floor(const T& x)             = 0;
    virtual T Ge(const T& x, const T& y)    = 0;
    virtual T Gt(const T& x, const T& y)    = 0;
    virtual T IntCast(const T& x)           = 0;
    virtual T Le(const T& x, const T& y)    = 0;
    virtual T Log(const T& x)               = 0;
    virtual T Log10(const T& x)             = 0;
    virtual T Lsh(const T& x, const T& y)   = 0;
    virtual T Lt(const T& x, const T& y)    = 0;
    virtual T Max(const T& x, const T& y)   = 0;
    virtual T Min(const T& x, const T& y)   = 0;
    virtual T Ne(const T& x, const T& y)    = 0;
    virtual T Not(const T& x)               = 0;
    virtual T Or(const T& x, const T& y)    = 0;
    virtual T Pow(const T& x, const T& y)   = 0;
    // IEEE remainder is binary; the previous unary signature lost its divisor.
    virtual T Remainder(const T& x, const T& y) = 0;
    virtual T Rint(const T& x)                  = 0;
    virtual T Round(const T& x)                 = 0;
    // Signed and logical right shifts have different semantics for negative
    // operands and therefore cannot share one algebra operation.
    virtual T ARsh(const T& x, const T& y)                = 0;
    virtual T LRsh(const T& x, const T& y)                = 0;
    virtual T Select2(const T& x, const T& y, const T& z) = 0;
    virtual T Sin(const T& x)                             = 0;
    virtual T Sinh(const T& x)                            = 0;
    virtual T Sqrt(const T& x)                            = 0;
    virtual T Tan(const T& x)                             = 0;
    virtual T Tanh(const T& x)                            = 0;
    virtual T Xor(const T& x, const T& y)                 = 0;

    // Delays, Tables and SoundFiles
    virtual T Mem(const T& x)                = 0;
    virtual T Delay(const T& x, const T& y)  = 0;
    virtual T Prefix(const T& x, const T& y) = 0;
    // Bounds refine numeric values but must still be visible to analyses that
    // validate their constancy and ordering.
    virtual T AssertBounds(const T& lo, const T& hi, const T& x)               = 0;
    virtual T RDTbl(const T& wtbl, const T& ri)                                = 0;
    virtual T WRTbl(const T& n, const T& g, const T& wi, const T& ws)          = 0;
    virtual T Gen(const T& x)                                                  = 0;
    virtual T SoundFile(const T& label)                                        = 0;
    virtual T SoundFileRate(const T& sf, const T& x)                           = 0;
    virtual T SoundFileLength(const T& sf, const T& x)                         = 0;
    virtual T SoundFileBuffer(const T& sf, const T& x, const T& y, const T& z) = 0;
    virtual T Waveform(const std::vector<T>& w)                                = 0;

    // Foreign functions
    virtual T ForeignFunction(const std::vector<T>& ff)                 = 0;
    virtual T ForeignVar(const T& type, const T& name, const T& file)   = 0;
    virtual T ForeignConst(const T& type, const T& name, const T& file) = 0;

    virtual ~FaustAlgebra() = default;

   protected:
    //--------------------------------------------------------------------------------
    // Copy and move operations are protected: derived algebras keep theirs, but
    // copying through a FaustAlgebra& (which would slice) is not allowed.
    //--------------------------------------------------------------------------------
    FaustAlgebra()                                   = default;
    FaustAlgebra(const FaustAlgebra&)                = default;
    FaustAlgebra& operator=(const FaustAlgebra&)     = default;
    FaustAlgebra(FaustAlgebra&&) noexcept            = default;
    FaustAlgebra& operator=(FaustAlgebra&&) noexcept = default;
};

#endif