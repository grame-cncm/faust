/************************************************************************
 ************************************************************************
    FAUST signal library
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include "sigattributes.hh"

#include <functional>
#include <iostream>
#include <unordered_set>
#include <utility>
#include <vector>

#include "ppsig.hh"
#include "signalAlgebra.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"

//----------------------------------------------------------------------------------------
// The five EXACT attributes of a Faust type, as signal algebras.
//
// All five carry a tiny lattice whose join is a bitwise OR, so ascending Kleene iteration
// from the bottom element settles a component in a couple of rounds: no widening, no
// probe, no iteration cap. They are pairwise independent -- no rule in sigtyperules.cpp
// reads one attribute to compute another -- and none depends on the interval, which is
// what makes them migrable one at a time and ahead of it.
//
// Every operation is listed in each algebra. The join is the common case, but it is
// written out rather than defaulted: an attribute is defined by the rules that DEPART
// from the join, and those are only legible against the ones that do not.
//----------------------------------------------------------------------------------------

namespace {

int join(const std::vector<int>& v)
{
    int r = 0;
    for (int x : v) {
        r |= x;
    }
    return r;
}

//========================================================================================
// nature : kInt (0) <= kReal (1)
//========================================================================================

class NatureAlgebra : public SignalAlgebra<int> {
   public:
    // bottom is the SEED of a recursive variable, which the current system takes from
    // TREC = (kInt, kSamp, kInit, kScal, kNum) -- not the bottom of each lattice.
    int  bottom(Tree /*var*/) const override { return kInt; }
    int  top(Tree /*var*/) const override { return kReal; }
    bool lessEqual(const int& x, const int& y) const override { return (x | y) == y; }
    // A projection keeps the nature of its own branch: inferProjType promotes
    // variability, computability and vectorability, but leaves nature alone.
    int project(Tree, int i, const std::vector<int>& row) const override { return row[i]; }

    //--- injections. Nil and Label answer for the syntax a walk meets but no operation
    // consumes; the bottom element is neutral for the join, so they never perturb one.
    int Nil() const override { return kInt; }
    int Label(const std::string&) const override { return kInt; }
    int IntNum(int) const override { return kInt; }
    int Int64Num(int64_t) const override { return kInt; }
    int FloatNum(double) const override { return kReal; }
    int FixPointUpdate(const int& x, const int& y) const override { return x | y; }

    int Input(const int&) const override { return kReal; }  // TINPUT is kReal
    int Output(const int&, const int& x) const override { return x; }

    //--- user interface: widgets are kReal whatever their range signals are; a bargraph
    // is transparent and reports the nature of the signal it displays.
    int Button(const int&) const override { return kReal; }
    int Checkbox(const int&) const override { return kReal; }
    int VSlider(const int&, const int&, const int&, const int&, const int&) const override
    {
        return kReal;
    }
    int HSlider(const int&, const int&, const int&, const int&, const int&) const override
    {
        return kReal;
    }
    int NumEntry(const int&, const int&, const int&, const int&, const int&) const override
    {
        return kReal;
    }
    int HBargraph(const int&, const int&, const int&, const int& s) const override { return s; }
    int VBargraph(const int&, const int&, const int&, const int& s) const override { return s; }

    // the second argument is a dependency, not a value
    int Attach(const int& x, const int&) const override { return x; }
    int Enable(const int& x, const int&) const override { return x; }
    int Control(const int& x, const int&) const override { return x; }

    //--- arithmetic
    int Add(const int& x, const int& y) const override { return x | y; }
    int Sub(const int& x, const int& y) const override { return x | y; }
    int Mul(const int& x, const int& y) const override { return x | y; }
    int Div(const int&, const int&) const override { return kReal; }  // division always floats
    int Mod(const int& x, const int& y) const override { return x | y; }
    int Neg(const int& x) const override { return x; }
    int Inv(const int&) const override { return kReal; }
    int Abs(const int& x) const override { return x; }
    // highest/lowest reduce to a constant bound, always real
    int Highest(const int&) const override { return kReal; }
    int Lowest(const int&) const override { return kReal; }

    //--- comparisons: a boolean result is an integer
    int Gt(const int&, const int&) const override { return kInt; }
    int Lt(const int&, const int&) const override { return kInt; }
    int Ge(const int&, const int&) const override { return kInt; }
    int Le(const int&, const int&) const override { return kInt; }
    int Eq(const int&, const int&) const override { return kInt; }
    int Ne(const int&, const int&) const override { return kInt; }
    int Not(const int&) const override { return kInt; }

    //--- bitwise and shifts: integer by construction
    int And(const int&, const int&) const override { return kInt; }
    int Or(const int&, const int&) const override { return kInt; }
    int Xor(const int&, const int&) const override { return kInt; }
    int Lsh(const int&, const int&) const override { return kInt; }
    int ARsh(const int&, const int&) const override { return kInt; }
    int LRsh(const int&, const int&) const override { return kInt; }

    //--- casts
    int IntCast(const int&) const override { return kInt; }
    int BitCast(const int&) const override { return kInt; }
    int FloatCast(const int&) const override { return kReal; }

    //--- transcendental and rounding: all float-valued, the rounding family included --
    // `round` of an integer is still a real, which is what roundprim's floatCast says.
    int Acos(const int&) const override { return kReal; }
    int Acosh(const int&) const override { return kReal; }
    int Asin(const int&) const override { return kReal; }
    int Asinh(const int&) const override { return kReal; }
    int Atan(const int&) const override { return kReal; }
    int Atan2(const int&, const int&) const override { return kReal; }
    int Atanh(const int&) const override { return kReal; }
    int Ceil(const int&) const override { return kReal; }
    int Cos(const int&) const override { return kReal; }
    int Cosh(const int&) const override { return kReal; }
    int Exp(const int&) const override { return kReal; }
    int Exp10(const int&) const override { return kReal; }
    int Floor(const int&) const override { return kReal; }
    int Log(const int&) const override { return kReal; }
    int Log10(const int&) const override { return kReal; }
    int Pow(const int& x, const int& y) const override { return x | y; }
    int Remainder(const int&, const int&) const override { return kReal; }
    int Rint(const int&) const override { return kReal; }
    int Round(const int&) const override { return kReal; }
    int Sin(const int&) const override { return kReal; }
    int Sinh(const int&) const override { return kReal; }
    int Sqrt(const int&) const override { return kReal; }
    int Tan(const int&) const override { return kReal; }
    int Tanh(const int&) const override { return kReal; }
    int Max(const int& x, const int& y) const override { return x | y; }
    int Min(const int& x, const int& y) const override { return x | y; }

    //--- selection: the SELECTOR does not contribute its nature
    int Select2(const int&, const int& x, const int& y) const override { return x | y; }

    //--- delays: the delay AMOUNT does not contribute its nature
    int Mem(const int& x) const override { return x; }
    int Delay(const int& x, const int&) const override { return x; }
    int Prefix(const int& x, const int& y) const override { return x | y; }
    int AssertBounds(const int&, const int&, const int& x) const override { return x; }

    //--- tables. A table node carries the nature of its CONTENT, which is what a read
    // returns. A written table unites the initial content with the written signal: the
    // TableType constructor computes `content->nature() | ws->nature()`.
    int Table(const int&, const int& content) const override { return content; }
    int WRTbl(const int&, const int& g, const int&, const int& ws) const override
    {
        return g | ws;
    }
    int RDTbl(const int& tbl, const int&) const override { return tbl; }
    int Gen(const int& x) const override { return x; }
    int Waveform(const std::vector<int>& w) const override { return join(w); }

    //--- soundfiles
    int SoundFile(const int&) const override { return kInt; }
    int SoundFileRate(const int&, const int&) const override { return kInt; }
    int SoundFileLength(const int&, const int&) const override { return kInt; }
    int SoundFileBuffer(const int&, const int&, const int&, const int&) const override
    {
        return kReal;
    }

    //--- foreign entities: the declaration decides
    int ForeignConst(int declared, const int&, const int&) const override { return declared; }
    int ForeignVar(int declared, const int&, const int&) const override { return declared; }
    int ForeignFunction(int result, const std::vector<int>&) const override { return result; }

    //--- signal-language-only constructors
    int DocConstantTbl(const int&, const int& init) const override { return init; }
    int DocWriteTbl(const int&, const int& init, const int&, const int& wsig) const override
    {
        return init | wsig;
    }
    int DocAccessTbl(const int& tbl, const int&) const override { return tbl; }
    int Register(int, const int& s) const override { return s; }
    int Tuple(int, const std::vector<int>& ls) const override { return join(ls); }
    int TupleAccess(const int& ts, const int&) const override { return ts; }
};

//========================================================================================
// variability : kKonst (0) <= kBlock (1) <= kSamp (3) -- how fast a value changes
//========================================================================================

class VariabilityAlgebra : public SignalAlgebra<int> {
   public:
    int  bottom(Tree /*var*/) const override { return kSamp; }  // TREC
    int  top(Tree /*var*/) const override { return kSamp; }
    bool lessEqual(const int& x, const int& y) const override { return (x | y) == y; }
    // inferProjType promotes every branch to the variability of the WHOLE tuplet, so all
    // the branches of one recursive group end up sharing a single variability.
    int project(Tree, int, const std::vector<int>& row) const override { return join(row); }

    int Nil() const override { return kKonst; }
    int Label(const std::string&) const override { return kKonst; }
    int IntNum(int) const override { return kKonst; }
    int Int64Num(int64_t) const override { return kKonst; }
    int FloatNum(double) const override { return kKonst; }
    int FixPointUpdate(const int& x, const int& y) const override { return x | y; }

    int Input(const int&) const override { return kSamp; }
    int Output(const int&, const int&) const override { return kSamp; }  // sampCast

    //--- user interface: widgets change once per block; a bargraph is promoted to at
    // least kBlock but keeps the variability of the displayed signal if that is faster.
    int Button(const int&) const override { return kBlock; }
    int Checkbox(const int&) const override { return kBlock; }
    int VSlider(const int&, const int&, const int&, const int&, const int&) const override
    {
        return kBlock;
    }
    int HSlider(const int&, const int&, const int&, const int&, const int&) const override
    {
        return kBlock;
    }
    int NumEntry(const int&, const int&, const int&, const int&, const int&) const override
    {
        return kBlock;
    }
    int HBargraph(const int&, const int&, const int&, const int& s) const override
    {
        return s | kBlock;
    }
    int VBargraph(const int&, const int&, const int&, const int& s) const override
    {
        return s | kBlock;
    }

    int Attach(const int& x, const int&) const override { return x; }
    int Enable(const int& x, const int&) const override { return x; }
    int Control(const int& x, const int&) const override { return x; }

    //--- every arithmetic and logical operation simply joins its operands
    int Add(const int& x, const int& y) const override { return x | y; }
    int Sub(const int& x, const int& y) const override { return x | y; }
    int Mul(const int& x, const int& y) const override { return x | y; }
    int Div(const int& x, const int& y) const override { return x | y; }
    int Mod(const int& x, const int& y) const override { return x | y; }
    int Neg(const int& x) const override { return x; }
    int Inv(const int& x) const override { return x; }
    int Abs(const int& x) const override { return x; }
    int Highest(const int&) const override { return kKonst; }
    int Lowest(const int&) const override { return kKonst; }

    int Gt(const int& x, const int& y) const override { return x | y; }
    int Lt(const int& x, const int& y) const override { return x | y; }
    int Ge(const int& x, const int& y) const override { return x | y; }
    int Le(const int& x, const int& y) const override { return x | y; }
    int Eq(const int& x, const int& y) const override { return x | y; }
    int Ne(const int& x, const int& y) const override { return x | y; }
    int Not(const int& x) const override { return x; }

    int And(const int& x, const int& y) const override { return x | y; }
    int Or(const int& x, const int& y) const override { return x | y; }
    int Xor(const int& x, const int& y) const override { return x | y; }
    int Lsh(const int& x, const int& y) const override { return x | y; }
    int ARsh(const int& x, const int& y) const override { return x | y; }
    int LRsh(const int& x, const int& y) const override { return x | y; }

    int IntCast(const int& x) const override { return x; }
    int BitCast(const int& x) const override { return x; }
    int FloatCast(const int& x) const override { return x; }

    int Acos(const int& x) const override { return x; }
    int Acosh(const int& x) const override { return x; }
    int Asin(const int& x) const override { return x; }
    int Asinh(const int& x) const override { return x; }
    int Atan(const int& x) const override { return x; }
    int Atan2(const int& x, const int& y) const override { return x | y; }
    int Atanh(const int& x) const override { return x; }
    int Ceil(const int& x) const override { return x; }
    int Cos(const int& x) const override { return x; }
    int Cosh(const int& x) const override { return x; }
    int Exp(const int& x) const override { return x; }
    int Exp10(const int& x) const override { return x; }
    int Floor(const int& x) const override { return x; }
    int Log(const int& x) const override { return x; }
    int Log10(const int& x) const override { return x; }
    int Pow(const int& x, const int& y) const override { return x | y; }
    int Remainder(const int& x, const int& y) const override { return x | y; }
    int Rint(const int& x) const override { return x; }
    int Round(const int& x) const override { return x; }
    int Sin(const int& x) const override { return x; }
    int Sinh(const int& x) const override { return x; }
    int Sqrt(const int& x) const override { return x; }
    int Tan(const int& x) const override { return x; }
    int Tanh(const int& x) const override { return x; }
    int Max(const int& x, const int& y) const override { return x | y; }
    int Min(const int& x, const int& y) const override { return x | y; }

    //--- selection: here the SELECTOR does participate
    int Select2(const int& sel, const int& x, const int& y) const override
    {
        return sel | x | y;
    }

    //--- delays are what makes a signal sample-rate
    int Mem(const int&) const override { return kSamp; }
    int Delay(const int&, const int&) const override { return kSamp; }
    int Prefix(const int&, const int&) const override { return kSamp; }
    int AssertBounds(const int&, const int&, const int& x) const override { return x; }

    //--- tables. A read-only table is built once, so it RESETS variability to kKonst
    // rather than joining its content's. A written one takes the write index and the
    // written signal, and drops the content's variability too.
    int Table(const int&, const int&) const override { return kKonst; }
    int WRTbl(const int&, const int&, const int& wi, const int& ws) const override
    {
        return kKonst | wi | ws;
    }
    int RDTbl(const int& tbl, const int& ri) const override { return tbl | ri; }
    int Gen(const int& x) const override { return x; }
    int Waveform(const std::vector<int>&) const override { return kSamp; }

    int SoundFile(const int&) const override { return kBlock; }
    int SoundFileRate(const int&, const int& part) const override { return kBlock | part; }
    int SoundFileLength(const int&, const int& part) const override { return kBlock | part; }
    int SoundFileBuffer(const int&, const int&, const int&, const int&) const override
    {
        return kSamp;
    }

    //--- foreign entities: a constant is constant, a variable changes by blocks like a
    // widget, and a NULLARY function is treated as rand() -- it varies at every call.
    int ForeignConst(int, const int&, const int&) const override { return kKonst; }
    int ForeignVar(int, const int&, const int&) const override { return kBlock; }
    int ForeignFunction(int, const std::vector<int>& args) const override
    {
        return args.empty() ? kSamp : join(args);
    }

    int DocConstantTbl(const int&, const int& init) const override { return init; }
    int DocWriteTbl(const int&, const int& init, const int&, const int&) const override
    {
        return init | kSamp;  // difficult to tell, therefore kSamp to be safe
    }
    int DocAccessTbl(const int& tbl, const int& ridx) const override { return tbl | ridx; }
    int Register(int, const int& s) const override { return s; }
    int Tuple(int, const std::vector<int>& ls) const override { return join(ls); }
    int TupleAccess(const int& ts, const int& idx) const override { return ts | idx; }
};

//========================================================================================
// computability : kComp (0) <= kInit (1) <= kExec (3) -- how early a value is known
//========================================================================================

class ComputabilityAlgebra : public SignalAlgebra<int> {
   public:
    int  bottom(Tree /*var*/) const override { return kInit; }  // TREC
    int  top(Tree /*var*/) const override { return kExec; }
    bool lessEqual(const int& x, const int& y) const override { return (x | y) == y; }
    int project(Tree, int, const std::vector<int>& row) const override { return join(row); }

    int Nil() const override { return kComp; }
    int Label(const std::string&) const override { return kComp; }
    int IntNum(int) const override { return kComp; }
    int Int64Num(int64_t) const override { return kComp; }
    int FloatNum(double) const override { return kComp; }
    int FixPointUpdate(const int& x, const int& y) const override { return x | y; }

    int Input(const int&) const override { return kExec; }
    int Output(const int&, const int& x) const override { return x; }

    int Button(const int&) const override { return kExec; }
    int Checkbox(const int&) const override { return kExec; }
    int VSlider(const int&, const int&, const int&, const int&, const int&) const override
    {
        return kExec;
    }
    int HSlider(const int&, const int&, const int&, const int&, const int&) const override
    {
        return kExec;
    }
    int NumEntry(const int&, const int&, const int&, const int&, const int&) const override
    {
        return kExec;
    }
    int HBargraph(const int&, const int&, const int&, const int& s) const override { return s; }
    int VBargraph(const int&, const int&, const int&, const int& s) const override { return s; }

    int Attach(const int& x, const int&) const override { return x; }
    int Enable(const int& x, const int&) const override { return x; }
    int Control(const int& x, const int&) const override { return x; }

    int Add(const int& x, const int& y) const override { return x | y; }
    int Sub(const int& x, const int& y) const override { return x | y; }
    int Mul(const int& x, const int& y) const override { return x | y; }
    int Div(const int& x, const int& y) const override { return x | y; }
    int Mod(const int& x, const int& y) const override { return x | y; }
    int Neg(const int& x) const override { return x; }
    int Inv(const int& x) const override { return x; }
    int Abs(const int& x) const override { return x; }
    int Highest(const int&) const override { return kComp; }
    int Lowest(const int&) const override { return kComp; }

    int Gt(const int& x, const int& y) const override { return x | y; }
    int Lt(const int& x, const int& y) const override { return x | y; }
    int Ge(const int& x, const int& y) const override { return x | y; }
    int Le(const int& x, const int& y) const override { return x | y; }
    int Eq(const int& x, const int& y) const override { return x | y; }
    int Ne(const int& x, const int& y) const override { return x | y; }
    int Not(const int& x) const override { return x; }

    int And(const int& x, const int& y) const override { return x | y; }
    int Or(const int& x, const int& y) const override { return x | y; }
    int Xor(const int& x, const int& y) const override { return x | y; }
    int Lsh(const int& x, const int& y) const override { return x | y; }
    int ARsh(const int& x, const int& y) const override { return x | y; }
    int LRsh(const int& x, const int& y) const override { return x | y; }

    int IntCast(const int& x) const override { return x; }
    int BitCast(const int& x) const override { return x; }
    int FloatCast(const int& x) const override { return x; }

    int Acos(const int& x) const override { return x; }
    int Acosh(const int& x) const override { return x; }
    int Asin(const int& x) const override { return x; }
    int Asinh(const int& x) const override { return x; }
    int Atan(const int& x) const override { return x; }
    int Atan2(const int& x, const int& y) const override { return x | y; }
    int Atanh(const int& x) const override { return x; }
    int Ceil(const int& x) const override { return x; }
    int Cos(const int& x) const override { return x; }
    int Cosh(const int& x) const override { return x; }
    int Exp(const int& x) const override { return x; }
    int Exp10(const int& x) const override { return x; }
    int Floor(const int& x) const override { return x; }
    int Log(const int& x) const override { return x; }
    int Log10(const int& x) const override { return x; }
    int Pow(const int& x, const int& y) const override { return x | y; }
    int Remainder(const int& x, const int& y) const override { return x | y; }
    int Rint(const int& x) const override { return x; }
    int Round(const int& x) const override { return x; }
    int Sin(const int& x) const override { return x; }
    int Sinh(const int& x) const override { return x; }
    int Sqrt(const int& x) const override { return x; }
    int Tan(const int& x) const override { return x; }
    int Tanh(const int& x) const override { return x; }
    int Max(const int& x, const int& y) const override { return x | y; }
    int Min(const int& x, const int& y) const override { return x | y; }

    int Select2(const int& sel, const int& x, const int& y) const override
    {
        return sel | x | y;
    }

    // a delay does not change WHEN a value can be computed, only how fast it changes
    int Mem(const int& x) const override { return x; }
    int Delay(const int& x, const int&) const override { return x; }
    int Prefix(const int& x, const int& y) const override { return x | y; }
    int AssertBounds(const int&, const int&, const int& x) const override { return x; }

    // a table is filled at init, a floor its content cannot lower
    int Table(const int&, const int&) const override { return kInit; }
    int WRTbl(const int&, const int&, const int& wi, const int& ws) const override
    {
        return kInit | wi | ws;
    }
    int RDTbl(const int& tbl, const int& ri) const override { return tbl | ri; }
    int Gen(const int& x) const override { return x; }
    int Waveform(const std::vector<int>&) const override { return kComp; }

    int SoundFile(const int&) const override { return kInit; }
    int SoundFileRate(const int&, const int&) const override { return kInit; }
    int SoundFileLength(const int&, const int&) const override { return kInit; }
    int SoundFileBuffer(const int&, const int&, const int&, const int&) const override
    {
        return kInit;
    }

    // an external constant cannot be computed before initialization; an external
    // variable not before execution
    int ForeignConst(int, const int&, const int&) const override { return kInit; }
    int ForeignVar(int, const int&, const int&) const override { return kExec; }
    int ForeignFunction(int, const std::vector<int>& args) const override
    {
        return kInit | join(args);
    }

    int DocConstantTbl(const int&, const int& init) const override { return init; }
    int DocWriteTbl(const int&, const int& init, const int& widx,
                    const int& wsig) const override
    {
        return init | widx | wsig;
    }
    int DocAccessTbl(const int& tbl, const int& ridx) const override { return tbl | ridx; }
    int Register(int, const int& s) const override { return s; }
    int Tuple(int, const std::vector<int>& ls) const override { return join(ls); }
    int TupleAccess(const int& ts, const int& idx) const override { return ts | idx; }
};

//========================================================================================
// vectorability : kVect (0) <= kScal (1) <= kTrueScal (3) -- when a signal vectorizes
//========================================================================================

class VectorabilityAlgebra : public SignalAlgebra<int> {
   public:
    int  bottom(Tree /*var*/) const override { return kScal; }  // TREC
    int  top(Tree /*var*/) const override { return kTrueScal; }
    bool lessEqual(const int& x, const int& y) const override { return (x | y) == y; }
    // Every projection out of a recursive group is forced to kScal: a feedback loop does
    // not vectorize. This is the reason the domain gets a say in projection at all --
    // no branch value implies it.
    int project(Tree, int i, const std::vector<int>& row) const override
    {
        return row[i] | kScal;
    }

    int Nil() const override { return kVect; }
    int Label(const std::string&) const override { return kVect; }
    int IntNum(int) const override { return kVect; }
    int Int64Num(int64_t) const override { return kVect; }
    int FloatNum(double) const override { return kVect; }
    int FixPointUpdate(const int& x, const int& y) const override { return x | y; }

    int Input(const int&) const override { return kVect; }
    int Output(const int&, const int& x) const override { return x; }

    int Button(const int&) const override { return kVect; }
    int Checkbox(const int&) const override { return kVect; }
    int VSlider(const int&, const int&, const int&, const int&, const int&) const override
    {
        return kVect;
    }
    int HSlider(const int&, const int&, const int&, const int&, const int&) const override
    {
        return kVect;
    }
    int NumEntry(const int&, const int&, const int&, const int&, const int&) const override
    {
        return kVect;
    }
    int HBargraph(const int&, const int&, const int&, const int& s) const override { return s; }
    int VBargraph(const int&, const int&, const int&, const int& s) const override { return s; }

    int Attach(const int& x, const int&) const override { return x; }
    int Enable(const int& x, const int&) const override { return x; }
    int Control(const int& x, const int&) const override { return x; }

    int Add(const int& x, const int& y) const override { return x | y; }
    int Sub(const int& x, const int& y) const override { return x | y; }
    int Mul(const int& x, const int& y) const override { return x | y; }
    int Div(const int& x, const int& y) const override { return x | y; }
    int Mod(const int& x, const int& y) const override { return x | y; }
    int Neg(const int& x) const override { return x; }
    int Inv(const int& x) const override { return x; }
    int Abs(const int& x) const override { return x; }
    int Highest(const int&) const override { return kVect; }
    int Lowest(const int&) const override { return kVect; }

    int Gt(const int& x, const int& y) const override { return x | y; }
    int Lt(const int& x, const int& y) const override { return x | y; }
    int Ge(const int& x, const int& y) const override { return x | y; }
    int Le(const int& x, const int& y) const override { return x | y; }
    int Eq(const int& x, const int& y) const override { return x | y; }
    int Ne(const int& x, const int& y) const override { return x | y; }
    int Not(const int& x) const override { return x; }

    int And(const int& x, const int& y) const override { return x | y; }
    int Or(const int& x, const int& y) const override { return x | y; }
    int Xor(const int& x, const int& y) const override { return x | y; }
    int Lsh(const int& x, const int& y) const override { return x | y; }
    int ARsh(const int& x, const int& y) const override { return x | y; }
    int LRsh(const int& x, const int& y) const override { return x | y; }

    int IntCast(const int& x) const override { return x; }
    int BitCast(const int& x) const override { return x; }
    int FloatCast(const int& x) const override { return x; }

    int Acos(const int& x) const override { return x; }
    int Acosh(const int& x) const override { return x; }
    int Asin(const int& x) const override { return x; }
    int Asinh(const int& x) const override { return x; }
    int Atan(const int& x) const override { return x; }
    int Atan2(const int& x, const int& y) const override { return x | y; }
    int Atanh(const int& x) const override { return x; }
    int Ceil(const int& x) const override { return x; }
    int Cos(const int& x) const override { return x; }
    int Cosh(const int& x) const override { return x; }
    int Exp(const int& x) const override { return x; }
    int Exp10(const int& x) const override { return x; }
    int Floor(const int& x) const override { return x; }
    int Log(const int& x) const override { return x; }
    int Log10(const int& x) const override { return x; }
    int Pow(const int& x, const int& y) const override { return x | y; }
    int Remainder(const int& x, const int& y) const override { return x | y; }
    int Rint(const int& x) const override { return x; }
    int Round(const int& x) const override { return x; }
    int Sin(const int& x) const override { return x; }
    int Sinh(const int& x) const override { return x; }
    int Sqrt(const int& x) const override { return x; }
    int Tan(const int& x) const override { return x; }
    int Tanh(const int& x) const override { return x; }
    int Max(const int& x, const int& y) const override { return x | y; }
    int Min(const int& x, const int& y) const override { return x | y; }

    int Select2(const int& sel, const int& x, const int& y) const override
    {
        return sel | x | y;
    }

    int Mem(const int& x) const override { return x; }
    int Delay(const int& x, const int&) const override { return x; }
    int Prefix(const int& x, const int& y) const override { return x | y; }
    int AssertBounds(const int&, const int&, const int& x) const override { return x; }

    int Table(const int&, const int&) const override { return kVect; }
    int WRTbl(const int&, const int&, const int& wi, const int& ws) const override
    {
        return kVect | wi | ws;
    }
    int RDTbl(const int& tbl, const int& ri) const override { return tbl | ri; }
    int Gen(const int& x) const override { return x; }
    int Waveform(const std::vector<int>&) const override { return kScal; }

    int SoundFile(const int&) const override { return kVect; }
    int SoundFileRate(const int&, const int&) const override { return kVect; }
    int SoundFileLength(const int&, const int&) const override { return kVect; }
    int SoundFileBuffer(const int&, const int&, const int&, const int&) const override
    {
        return kVect;
    }

    int ForeignConst(int, const int&, const int&) const override { return kVect; }
    int ForeignVar(int, const int&, const int&) const override { return kVect; }
    int ForeignFunction(int, const std::vector<int>& args) const override
    {
        return kVect | join(args);
    }

    int DocConstantTbl(const int&, const int& init) const override { return init; }
    int DocWriteTbl(const int&, const int& init, const int&, const int&) const override
    {
        return init | kScal;  // difficult to tell, therefore kScal to be safe
    }
    int DocAccessTbl(const int& tbl, const int& ridx) const override { return tbl | ridx; }
    int Register(int, const int& s) const override { return s; }
    int Tuple(int, const std::vector<int>& ls) const override { return join(ls); }
    int TupleAccess(const int& ts, const int& idx) const override { return ts | idx; }
};

//========================================================================================
// boolean : kNum (0) <= kBool (1) -- whether a value is a truth value
//========================================================================================

class BooleanAlgebra : public SignalAlgebra<int> {
   public:
    int  bottom(Tree /*var*/) const override { return kNum; }
    int  top(Tree /*var*/) const override { return kBool; }
    bool lessEqual(const int& x, const int& y) const override { return (x | y) == y; }
    int project(Tree, int i, const std::vector<int>& row) const override { return row[i]; }

    int Nil() const override { return kNum; }
    int Label(const std::string&) const override { return kNum; }
    int IntNum(int) const override { return kNum; }
    int Int64Num(int64_t) const override { return kNum; }
    int FloatNum(double) const override { return kNum; }
    int FixPointUpdate(const int& x, const int& y) const override { return x | y; }

    int Input(const int&) const override { return kNum; }
    int Output(const int&, const int& x) const override { return x; }

    int Button(const int&) const override { return kNum; }
    int Checkbox(const int&) const override { return kNum; }
    int VSlider(const int&, const int&, const int&, const int&, const int&) const override
    {
        return kNum;
    }
    int HSlider(const int&, const int&, const int&, const int&, const int&) const override
    {
        return kNum;
    }
    int NumEntry(const int&, const int&, const int&, const int&, const int&) const override
    {
        return kNum;
    }
    int HBargraph(const int&, const int&, const int&, const int& s) const override { return s; }
    int VBargraph(const int&, const int&, const int&, const int& s) const override { return s; }

    int Attach(const int& x, const int&) const override { return x; }
    int Enable(const int& x, const int&) const override { return x; }
    int Control(const int& x, const int&) const override { return x; }

    //--- arithmetic carries booleanity through, since intCast and floatCast leave it
    // untouched; only a comparison MAKES a boolean.
    int Add(const int& x, const int& y) const override { return x | y; }
    int Sub(const int& x, const int& y) const override { return x | y; }
    int Mul(const int& x, const int& y) const override { return x | y; }
    int Div(const int& x, const int& y) const override { return x | y; }
    int Mod(const int& x, const int& y) const override { return x | y; }
    int Neg(const int& x) const override { return x; }
    int Inv(const int& x) const override { return x; }
    int Abs(const int& x) const override { return x; }
    int Highest(const int&) const override { return kNum; }
    int Lowest(const int&) const override { return kNum; }

    //--- comparisons: boolCast
    int Gt(const int&, const int&) const override { return kBool; }
    int Lt(const int&, const int&) const override { return kBool; }
    int Ge(const int&, const int&) const override { return kBool; }
    int Le(const int&, const int&) const override { return kBool; }
    int Eq(const int&, const int&) const override { return kBool; }
    int Ne(const int&, const int&) const override { return kBool; }
    int Not(const int&) const override { return kBool; }

    int And(const int& x, const int& y) const override { return x | y; }
    int Or(const int& x, const int& y) const override { return x | y; }
    int Xor(const int& x, const int& y) const override { return x | y; }
    int Lsh(const int& x, const int& y) const override { return x | y; }
    int ARsh(const int& x, const int& y) const override { return x | y; }
    int LRsh(const int& x, const int& y) const override { return x | y; }

    int IntCast(const int& x) const override { return x; }
    int BitCast(const int& x) const override { return x; }
    int FloatCast(const int& x) const override { return x; }

    int Acos(const int& x) const override { return x; }
    int Acosh(const int& x) const override { return x; }
    int Asin(const int& x) const override { return x; }
    int Asinh(const int& x) const override { return x; }
    int Atan(const int& x) const override { return x; }
    int Atan2(const int& x, const int& y) const override { return x | y; }
    int Atanh(const int& x) const override { return x; }
    int Ceil(const int& x) const override { return x; }
    int Cos(const int& x) const override { return x; }
    int Cosh(const int& x) const override { return x; }
    int Exp(const int& x) const override { return x; }
    int Exp10(const int& x) const override { return x; }
    int Floor(const int& x) const override { return x; }
    int Log(const int& x) const override { return x; }
    int Log10(const int& x) const override { return x; }
    int Pow(const int& x, const int& y) const override { return x | y; }
    int Remainder(const int& x, const int& y) const override { return x | y; }
    int Rint(const int& x) const override { return x; }
    int Round(const int& x) const override { return x; }
    int Sin(const int& x) const override { return x; }
    int Sinh(const int& x) const override { return x; }
    int Sqrt(const int& x) const override { return x; }
    int Tan(const int& x) const override { return x; }
    int Tanh(const int& x) const override { return x; }
    int Max(const int& x, const int& y) const override { return x | y; }
    int Min(const int& x, const int& y) const override { return x | y; }

    //--- selection: like nature, the SELECTOR is excluded
    int Select2(const int&, const int& x, const int& y) const override { return x | y; }

    int Mem(const int& x) const override { return x; }
    int Delay(const int& x, const int&) const override { return x; }
    int Prefix(const int& x, const int& y) const override { return x | y; }
    int AssertBounds(const int&, const int&, const int& x) const override { return x; }

    int Table(const int&, const int& content) const override { return content; }
    int WRTbl(const int&, const int& g, const int&, const int& ws) const override
    {
        return g | ws;
    }
    int RDTbl(const int& tbl, const int&) const override { return tbl; }
    int Gen(const int& x) const override { return x; }
    int Waveform(const std::vector<int>&) const override { return kNum; }

    int SoundFile(const int&) const override { return kNum; }
    int SoundFileRate(const int&, const int&) const override { return kNum; }
    int SoundFileLength(const int&, const int&) const override { return kNum; }
    int SoundFileBuffer(const int&, const int&, const int&, const int&) const override
    {
        return kNum;
    }

    int ForeignConst(int, const int&, const int&) const override { return kNum; }
    int ForeignVar(int, const int&, const int&) const override { return kNum; }
    int ForeignFunction(int, const std::vector<int>& args) const override
    {
        return join(args);
    }

    int DocConstantTbl(const int&, const int& init) const override { return init; }
    int DocWriteTbl(const int&, const int& init, const int&, const int& wsig) const override
    {
        return init | wsig;
    }
    int DocAccessTbl(const int& tbl, const int&) const override { return tbl; }
    int Register(int, const int& s) const override { return s; }
    int Tuple(int, const std::vector<int>& ls) const override { return join(ls); }
    int TupleAccess(const int& ts, const int&) const override { return ts; }
};

//----------------------------------------------------------------------------------------
// Shadow comparison
//----------------------------------------------------------------------------------------

/// One comparable node: a signal and the SimpleType inferSigType stored on it.
using TypedNodes = std::vector<std::pair<Tree, SimpleType*>>;

/// Every annotated signal reachable from L that carries a SimpleType. Recursive groups
/// (tuplet type) and the syntax a walk also meets (opcode leaves, labels) are skipped.
/// Collected ONCE and shared by all five passes.
TypedNodes collectTypedSignals(Tree L)
{
    TypedNodes               nodes;
    std::unordered_set<Tree> visited;
    std::vector<Tree>        work{L};

    while (!work.empty()) {
        Tree t = work.back();
        work.pop_back();
        if (!visited.insert(t).second) continue;

        Tree var, body;
        if (isRec(t, var, body)) {
            // the body hangs off a property, not a branch, so the walk must cross it
            if (body) work.push_back(body);
            continue;
        }
        AudioType* ty = getSigType(t);
        if (ty != nullptr) {
            SimpleType* st = isSimpleType(ty);
            if (st != nullptr) nodes.emplace_back(t, st);
        }
        for (int i = 0; i < t->arity(); i++) {
            work.push_back(t->branch(i));
        }
    }
    return nodes;
}

template <typename ALG>
int runPass(const RecPlan& plan, const TypedNodes& nodes, bool verbose, const char* attr,
            const std::function<int(SimpleType*)>& expected)
{
    ALG                   algebra;
    FixPointIterator<int> it(plan, algebra);

    int agree = 0, disagree = 0;
    for (const auto& n : nodes) {
        const int computed = it.value(n.first);
        const int wanted   = expected(n.second);
        if (computed == wanted) {
            agree++;
        } else {
            disagree++;
            if (verbose) {
                std::cerr << "ATTR MISMATCH [" << attr << "] : fixpoint " << computed
                          << ", type system " << wanted << " : " << ppsig(n.first, 40)
                          << std::endl;
            }
        }
    }
    if (verbose) {
        std::cerr << "ATTR SHADOW [" << attr << "] : " << agree << " agree, " << disagree
                  << " disagree" << std::endl;
    }
    return disagree;
}

}  // namespace

int shadowCheckExactAttributes(Tree L, bool verbose)
{
    // Décision A: five INDEPENDENT passes sharing one RecPlan -- the V-independent
    // structure -- rather than one pass over a tuple, which would couple their
    // convergences and let a slow attribute hold back a fast one.
    RecPlan          plan(L);
    const TypedNodes nodes = collectTypedSignals(L);

    int d = 0;
    d += runPass<NatureAlgebra>(plan, nodes, verbose, "nature",
                                [](SimpleType* st) { return st->nature(); });
    d += runPass<VariabilityAlgebra>(plan, nodes, verbose, "variability",
                                     [](SimpleType* st) { return st->variability(); });
    d += runPass<ComputabilityAlgebra>(plan, nodes, verbose, "computability",
                                       [](SimpleType* st) { return st->computability(); });
    d += runPass<VectorabilityAlgebra>(plan, nodes, verbose, "vectorability",
                                       [](SimpleType* st) { return st->vectorability(); });
    d += runPass<BooleanAlgebra>(plan, nodes, verbose, "boolean",
                                 [](SimpleType* st) { return st->boolean(); });
    if (verbose) {
        std::cerr << "ATTR SHADOW [total] : " << d << " disagree over " << nodes.size()
                  << " signals x 5 attributes" << std::endl;
    }
    return d;
}

int shadowCheckNature(Tree L, bool verbose)
{
    RecPlan          plan(L);
    const TypedNodes nodes = collectTypedSignals(L);
    return runPass<NatureAlgebra>(plan, nodes, verbose, "nature",
                                  [](SimpleType* st) { return st->nature(); });
}
