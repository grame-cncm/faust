#pragma once

#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "symbol.hh"

//=====================================================================================================================
// A Faust Algebra is a class grouping the set of primitive operations available
// on Faust signals. All these operations are callable directly or via dispatch
// tables according to their arity and name. The dispatch tables are typically
// used when recursively visiting an expressions tree while applying an algebra.
// Derived algebras just have to specify the type T and implement the primitive
// operations for this type T. Example of derived algebras are Interval
// Algebras, TypeInference Algebras, Expression Tree Algebras, Compiler
// Algebras, etc.
//=====================================================================================================================

template <typename T>
class FaustAlgebra
{
   public:
    //--------------------------------------------------------------------------------
    // Dispatch tables
    //--------------------------------------------------------------------------------

    // the various types of primitive operations
    using unfunc   = T (FaustAlgebra::*)(const T&);
    using binfunc  = T (FaustAlgebra::*)(const T&, const T&);
    using trifunc  = T (FaustAlgebra::*)(const T&, const T&, const T&);
    using quadfunc = T (FaustAlgebra::*)(const T&, const T&, const T&, const T&);
    using quinfunc = T (FaustAlgebra::*)(const T&, const T&, const T&, const T&, const T&);
    using varfunc  = T (FaustAlgebra::*)(const std::vector<T>& w);

    // The dispatch tables
    std::map<Sym, unfunc>   fUnFuncs;
    std::map<Sym, binfunc>  fBinFuncs;
    std::map<Sym, trifunc>  fTriFuncs;
    std::map<Sym, quadfunc> fQuadFuncs;
    std::map<Sym, quinfunc> fQuinFuncs;
    std::map<Sym, varfunc>  fVarFuncs;

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
    virtual T Button(const T& name)                                                           = 0;
    virtual T Checkbox(const T& name)                                                         = 0;
    virtual T VSlider(const T& name, const T& init, const T& lo, const T& hi, const T& step)  = 0;
    virtual T HSlider(const T& name, const T& init, const T& lo, const T& hi, const T& step)  = 0;
    virtual T HBargraph(const T& name, const T& lo, const T& hi)                              = 0;
    virtual T VBargraph(const T& name, const T& lo, const T& hi)                              = 0;
    virtual T NumEntry(const T& name, const T& init, const T& lo, const T& hi, const T& step) = 0;
    virtual T Attach(const T& x, const T& y)                                                  = 0;

    // Numerical Operations
    virtual T Abs(const T& x)                             = 0;
    virtual T Highest(const T& x)                         = 0;
    virtual T Lowest(const T& x)                          = 0;
    virtual T Add(const T& x, const T& y)                 = 0;
    virtual T Sub(const T& x, const T& y)                 = 0;
    virtual T Mul(const T& x, const T& y)                 = 0;
    virtual T Div(const T& x, const T& y)                 = 0;
    virtual T Inv(const T& x)                             = 0;
    virtual T Neg(const T& x)                             = 0;
    virtual T Mod(const T& x, const T& y)                 = 0;
    virtual T Acos(const T& x)                            = 0;
    virtual T Acosh(const T& x)                           = 0;
    virtual T And(const T& x, const T& y)                 = 0;
    virtual T Asin(const T& x)                            = 0;
    virtual T Asinh(const T& x)                           = 0;
    virtual T Atan(const T& x)                            = 0;
    virtual T Atan2(const T& x, const T& y)               = 0;
    virtual T Atanh(const T& x)                           = 0;
    virtual T Ceil(const T& x)                            = 0;
    virtual T Cos(const T& x)                             = 0;
    virtual T Cosh(const T& x)                            = 0;
    virtual T Eq(const T& x, const T& y)                  = 0;
    virtual T Exp(const T& x)                             = 0;
    virtual T FloatCast(const T& x)                       = 0;
    virtual T BitCast(const T& x)                         = 0;
    virtual T Floor(const T& x)                           = 0;
    virtual T Ge(const T& x, const T& y)                  = 0;
    virtual T Gt(const T& x, const T& y)                  = 0;
    virtual T IntCast(const T& x)                         = 0;
    virtual T Le(const T& x, const T& y)                  = 0;
    virtual T Log(const T& x)                             = 0;
    virtual T Log10(const T& x)                           = 0;
    virtual T Lsh(const T& x, const T& y)                 = 0;
    virtual T Lt(const T& x, const T& y)                  = 0;
    virtual T Max(const T& x, const T& y)                 = 0;
    virtual T Min(const T& x, const T& y)                 = 0;
    virtual T Ne(const T& x, const T& y)                  = 0;
    virtual T Not(const T& x)                             = 0;
    virtual T Or(const T& x, const T& y)                  = 0;
    virtual T Pow(const T& x, const T& y)                 = 0;
    virtual T Remainder(const T& x)                       = 0;
    virtual T Rint(const T& x)                            = 0;
    virtual T Rsh(const T& x, const T& y)                 = 0;
    virtual T Select2(const T& x, const T& y, const T& z) = 0;
    virtual T Sin(const T& x)                             = 0;
    virtual T Sinh(const T& x)                            = 0;
    virtual T Sqrt(const T& x)                            = 0;
    virtual T Tan(const T& x)                             = 0;
    virtual T Tanh(const T& x)                            = 0;
    virtual T Xor(const T& x, const T& y)                 = 0;

    // Delays, Tables and SoundFiles
    virtual T Mem(const T& x)                                                  = 0;
    virtual T Delay(const T& x, const T& y)                                    = 0;
    virtual T Prefix(const T& x, const T& y)                                   = 0;
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

    //--------------------------------------------------------------------------------
    // Calling the various operations according to the opcode symbol
    // and the number of arguments
    //--------------------------------------------------------------------------------

    // Call unary opcode
    [[nodiscard]] T operator()(Sym n, const T& a)
    {
        auto p = fUnFuncs.find(n);
        if (p == fUnFuncs.end()) {
            std::cerr << "Unknown unary opcode " << n << std::endl;
            exit(-1);
        }
        return std::invoke(p->second, this, a);
    }

    // Call binary opcode
    [[nodiscard]] T operator()(Sym n, const T& a, const T& b)
    {
        auto p = fBinFuncs.find(n);
        if (p == fBinFuncs.end()) {
            std::cerr << "Unknown binary opcode " << n << std::endl;
            exit(-1);
        }
        return std::invoke(p->second, this, a, b);
    }

    // Call ternary opcode
    [[nodiscard]] T operator()(Sym n, const T& a, const T& b, const T& c)
    {
        auto p = fTriFuncs.find(n);
        if (p == fTriFuncs.end()) {
            std::cerr << "Unknown quinary opcode " << n << std::endl;
            exit(-1);
        }
        return std::invoke(p->second, this, a, b, c);
    }

    // Call quaternary opcode
    [[nodiscard]] T operator()(Sym n, const T& a, const T& b, const T& c, const T& d)
    {
        auto p = fQuadFuncs.find(n);
        if (p == fQuadFuncs.end()) {
            std::cerr << "Unknown quaternary opcode " << n << std::endl;
            exit(-1);
        }
        return std::invoke(p->second, this, a, b, c, d);
    }

    // Call quinary opcodes
    [[nodiscard]] T operator()(Sym n, const T& a, const T& b, const T& c, const T& d, const T& e)
    {
        auto p = fQuinFuncs.find(n);
        if (p == fQuinFuncs.end()) {
            std::cerr << "Unknown quinary opcode " << n << std::endl;
            exit(-1);
        }
        return std::invoke(p->second, this, a, b, c, d, e);
    }

    // Call variadic opcodes
    [[nodiscard]] T operator()(Sym n, const std::vector<T>& v)
    {
        auto p = fVarFuncs.find(n);
        if (p == fVarFuncs.end()) {
            std::cerr << "Unknown variadic opcode " << n << std::endl;
            exit(-1);
        }
        return std::invoke(p->second, this, v);
    }

    virtual ~FaustAlgebra() = default;

    //--------------------------------------------------------------------------------
    // The role of the constructor is to build the various dispatch tables.
    //
    //--------------------------------------------------------------------------------

    FaustAlgebra()
    {
        // building the dispatch tables
        // UNARY METHODS

        // Unary user interface methods
        fUnFuncs[symbol("SigButton")]   = &FaustAlgebra::Button;
        fUnFuncs[symbol("SigCheckbox")] = &FaustAlgebra::Checkbox;

        // Unary Methods
        fUnFuncs[symbol("SigHighest")]   = &FaustAlgebra::Highest;
        fUnFuncs[symbol("SigLowest")]    = &FaustAlgebra::Lowest;
        fUnFuncs[symbol("SigIntCast")]   = &FaustAlgebra::IntCast;
        fUnFuncs[symbol("SigBitCast")]   = &FaustAlgebra::BitCast;
        fUnFuncs[symbol("SigFloatCast")] = &FaustAlgebra::FloatCast;

        fUnFuncs[symbol("inv")]       = &FaustAlgebra::Inv;
        fUnFuncs[symbol("abs")]       = &FaustAlgebra::Abs;
        fUnFuncs[symbol("neg")]       = &FaustAlgebra::Neg;
        fUnFuncs[symbol("acos")]      = &FaustAlgebra::Acos;
        fUnFuncs[symbol("acosh")]     = &FaustAlgebra::Acosh;
        fUnFuncs[symbol("asin")]      = &FaustAlgebra::Asin;
        fUnFuncs[symbol("asinh")]     = &FaustAlgebra::Asinh;
        fUnFuncs[symbol("atan")]      = &FaustAlgebra::Atan;
        fUnFuncs[symbol("atanh")]     = &FaustAlgebra::Atanh;
        fUnFuncs[symbol("ceil")]      = &FaustAlgebra::Ceil;
        fUnFuncs[symbol("cos")]       = &FaustAlgebra::Cos;
        fUnFuncs[symbol("cosh")]      = &FaustAlgebra::Cosh;
        fUnFuncs[symbol("exp")]       = &FaustAlgebra::Exp;
        fUnFuncs[symbol("floor")]     = &FaustAlgebra::Floor;
        fUnFuncs[symbol("log")]       = &FaustAlgebra::Log;
        fUnFuncs[symbol("log10")]     = &FaustAlgebra::Log10;
        fUnFuncs[symbol("not")]       = &FaustAlgebra::Not;
        fUnFuncs[symbol("remainder")] = &FaustAlgebra::Remainder;
        fUnFuncs[symbol("rint")]      = &FaustAlgebra::Rint;
        fUnFuncs[symbol("sin")]       = &FaustAlgebra::Sin;
        fUnFuncs[symbol("sinh")]      = &FaustAlgebra::Sinh;
        fUnFuncs[symbol("sqrt")]      = &FaustAlgebra::Sqrt;
        fUnFuncs[symbol("tan")]       = &FaustAlgebra::Tan;
        fUnFuncs[symbol("tanh")]      = &FaustAlgebra::Tanh;

        // Binary Methods
        fBinFuncs[symbol("add")]   = &FaustAlgebra::Add;
        fBinFuncs[symbol("sub")]   = &FaustAlgebra::Sub;
        fBinFuncs[symbol("mul")]   = &FaustAlgebra::Mul;
        fBinFuncs[symbol("div")]   = &FaustAlgebra::Div;
        fBinFuncs[symbol("mod")]   = &FaustAlgebra::Mod;
        fBinFuncs[symbol("and")]   = &FaustAlgebra::And;
        fBinFuncs[symbol("atan2")] = &FaustAlgebra::Atan2;
        fBinFuncs[symbol("eq")]    = &FaustAlgebra::Eq;
        fBinFuncs[symbol("ge")]    = &FaustAlgebra::Ge;
        fBinFuncs[symbol("gt")]    = &FaustAlgebra::Gt;
        fBinFuncs[symbol("lsh")]   = &FaustAlgebra::Lsh;
        fBinFuncs[symbol("lt")]    = &FaustAlgebra::Lt;
        fBinFuncs[symbol("max")]   = &FaustAlgebra::Max;
        fBinFuncs[symbol("min")]   = &FaustAlgebra::Min;
        fBinFuncs[symbol("ne")]    = &FaustAlgebra::Ne;
        fBinFuncs[symbol("or")]    = &FaustAlgebra::Or;
        fBinFuncs[symbol("pow")]   = &FaustAlgebra::Pow;
        fBinFuncs[symbol("le")]    = &FaustAlgebra::Le;
        fBinFuncs[symbol("rsh")]   = &FaustAlgebra::Rsh;
        fBinFuncs[symbol("xor")]   = &FaustAlgebra::Xor;

        fBinFuncs[symbol("SigAttach")] = &FaustAlgebra::Attach;

        // Ternary Methods
        fTriFuncs[symbol("SigSelect2")]   = &FaustAlgebra::Select2;
        fTriFuncs[symbol("SigHBargraph")] = &FaustAlgebra::HBargraph;
        fTriFuncs[symbol("SigVBargraph")] = &FaustAlgebra::VBargraph;

        // Quintary Methods
        fQuinFuncs[symbol("SigVSlider")]  = &FaustAlgebra::VSlider;
        fQuinFuncs[symbol("SigHSlider")]  = &FaustAlgebra::HSlider;
        fQuinFuncs[symbol("SigNumEntry")] = &FaustAlgebra::NumEntry;

        // Input and output

        fUnFuncs[symbol("SigInput")]   = &FaustAlgebra::Input;
        fBinFuncs[symbol("SigOutput")] = &FaustAlgebra::Output;

        // Delays, Tables and SoundFiles
        fUnFuncs[symbol("SigDelay1")]  = &FaustAlgebra::Mem;
        fBinFuncs[symbol("SigDelay")]  = &FaustAlgebra::Delay;
        fBinFuncs[symbol("SigPrefix")] = &FaustAlgebra::Prefix;
        fBinFuncs[symbol("SigRDTbl")]  = &FaustAlgebra::RDTbl;
        fQuadFuncs[symbol("SigWRTbl")] = &FaustAlgebra::WRTbl;
        fUnFuncs[symbol("SigGen")]     = &FaustAlgebra::Gen;

        fUnFuncs[symbol("SigSoundfile")]         = &FaustAlgebra::SoundFile;
        fBinFuncs[symbol("SigSoundfileRate")]    = &FaustAlgebra::SoundFileRate;
        fBinFuncs[symbol("SigSoundfileLength")]  = &FaustAlgebra::SoundFileLength;
        fQuadFuncs[symbol("SigSoundfileBuffer")] = &FaustAlgebra::SoundFileBuffer;
        fVarFuncs[symbol("SigWaveform")]         = &FaustAlgebra::Waveform;

        // Foreign functions
        fVarFuncs[symbol("SigFFun")]   = &FaustAlgebra::ForeignFunction;
        fTriFuncs[symbol("SigFVar")]   = &FaustAlgebra::ForeignVar;
        fTriFuncs[symbol("SigFConst")] = &FaustAlgebra::ForeignConst;
    }
};
