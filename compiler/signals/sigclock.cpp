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


#include "sigclock.hh"

#include <cstdlib>
#include <iostream>
#include <unordered_set>
#include <vector>

#include "ppsig.hh"
#include "signalAlgebra.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"

//----------------------------------------------------------------------------------------
// The clock calculus, step 0 : the rules of section 4.4 of clocks.md on the natural
// clocks.
//
// Every operation is listed. The clocks of the operands of a computation without memory
// always form a chain (the chain discipline) : on the three natural clocks any two are
// comparable, so the maximum is the bitwise OR and there is nothing to verify yet.
//----------------------------------------------------------------------------------------

namespace {

int join(const std::vector<int>& v)
{
    int r = kClkConst;
    for (int x : v) {
        r |= x;
    }
    return r;
}

class ClockAlgebra : public SignalAlgebra<int> {
    // The clock of the lexical context : the one a computation that counts time is
    // written under. Step 0 knows a single context, the sample clock.
    int context() const { return kClkSample; }

   public:
    // the least clock : a recursive variable is solved from below, and every recursive
    // reference crosses a delay, whose clock does not depend on its operand
    int  bottom(Tree /*var*/) const override { return kClkConst; }
    int  top(Tree /*var*/) const override { return kClkSample; }
    bool lessEqual(const int& x, const int& y) const override { return (x | y) == y; }
    // rule proj : the projections of one recursive group share the densest clock of its
    // definitions, as they share one variability. A definition that crosses no delay may
    // have a rarer clock of its own (a group is not always reduced to its cycles) :
    // reading it on the denser clock of the group is neutral.
    int project(Tree, int, const std::vector<int>& row) const override { return join(row); }

    int Label(const std::string&) const override { return kClkConst; }
    int IntNum(int) const override { return kClkConst; }
    int Int64Num(int64_t) const override { return kClkConst; }
    int FloatNum(double) const override { return kClkConst; }
    int FixPointUpdate(const int& x, const int& y) const override { return x | y; }

    int Input(const int&) const override { return kClkSample; }
    // an output of the program is sampled on the sample clock
    int Output(const int&, const int&) const override { return kClkSample; }

    //--- user interface: widgets are signals of the block clock; a bargraph samples the
    // signal it displays on a block clock, and passes it on unchanged.
    int Button(const int&) const override { return kClkBlock; }
    int Checkbox(const int&) const override { return kClkBlock; }
    int VSlider(const int&, const int&, const int&, const int&, const int&) const override
    {
        return kClkBlock;
    }
    int HSlider(const int&, const int&, const int&, const int&, const int&) const override
    {
        return kClkBlock;
    }
    int NumEntry(const int&, const int&, const int&, const int&, const int&) const override
    {
        return kClkBlock;
    }
    int HBargraph(const int&, const int&, const int&, const int& s) const override
    {
        return s | kClkBlock;
    }
    int VBargraph(const int&, const int&, const int&, const int& s) const override
    {
        return s | kClkBlock;
    }

    int Attach(const int& x, const int&) const override { return x; }
    int Enable(const int& x, const int&) const override { return x; }
    int Control(const int& x, const int&) const override { return x; }

    //--- rule op : a computation without memory has the densest clock of its operands
    int Add(const int& x, const int& y) const override { return x | y; }
    int Sub(const int& x, const int& y) const override { return x | y; }
    int Mul(const int& x, const int& y) const override { return x | y; }
    int Div(const int& x, const int& y) const override { return x | y; }
    int Mod(const int& x, const int& y) const override { return x | y; }
    int Fmod(const int& x, const int& y) const override { return Mod(x, y); }
    int Neg(const int& x) const override { return x; }
    int Inv(const int& x) const override { return x; }
    int Abs(const int& x) const override { return x; }
    int Highest(const int&) const override { return kClkConst; }
    int Lowest(const int&) const override { return kClkConst; }

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
    // the compound operations : the clocks of their operands (the constant 1.0 has none)
    int Frac(const int& x) const override { return x; }
    int Cfrac(const int& x) const override { return x; }
    int Mix(const int& c, const int& a, const int& b) const override { return kClkConst | c | a | b; }
    int Phase(const int& x, const int& p) const override { return kClkConst | x | p; }
    int Tpt(const int& x) const override { return x | kClkConst; }
    // the kernels : their definitions. A FIR of one coefficient has no memory, and an IIR
    // or an IRM reads its own past through a delay : the context
    int Sum(const std::vector<int>& t) const override { return sumDefinition(t); }
    int Prod(const std::vector<int>& t) const override { return prodDefinition(t); }
    int Fir(const int& x, const std::vector<int>& c) const override { return firDefinition(x, c); }
    int Iir(const int& x, const std::vector<int>& c) const override { return iirFeedforward(x, c); }
    int Irm(const int& x, const int& c) const override { return irmFeedforward(x, c); }
    int Bpf(const int& x, const std::vector<int>& t, const std::vector<int>& r) const override { return bpfDefinition(x, t, r); }
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

    //--- rule mem : a computation that counts time has the clock of its context, whatever
    // the clocks of its operands, which it reads at the tops of its own
    int Mem(const int&) const override { return context(); }
    int Delay(const int&, const int&) const override { return context(); }
    int Prefix(const int&, const int&) const override { return context(); }
    int AssertBounds(const int&, const int&, const int& x) const override { return x; }

    //--- tables. A read-only table is filled in deferred time, before the instant 0 : a
    // constant for the real time. Rule wrtbl : a written table does not count time, it
    // changes only when its write index or its written signal does, and has the densest
    // of their two clocks. Step 0 does not tell the deferred clock of a generator from
    // the sample clock : the content keeps the clock its delays give it.
    int Table(const int&, const int&) const override { return kClkConst; }
    int WRTbl(const int&, const int&, const int& wi, const int& ws) const override
    {
        return kClkConst | wi | ws;
    }
    int RDTbl(const int& tbl, const int& ri) const override { return tbl | ri; }
    int Gen(const int& x) const override { return x; }
    int Waveform(const std::vector<int>&) const override { return kClkSample; }

    int SoundFile(const int&) const override { return kClkBlock; }
    int SoundFileRate(const int&, const int& part) const override { return kClkBlock | part; }
    int SoundFileLength(const int&, const int& part) const override { return kClkBlock | part; }
    int SoundFileBuffer(const int&, const int&, const int&, const int&) const override
    {
        return kClkSample;
    }

    //--- foreign entities: a constant is a constant, a variable is a signal of the block
    // clock like a widget, and a NULLARY function is a source of the sample clock.
    int ForeignConst(int, const int&, const int&) const override { return kClkConst; }
    int ForeignVar(int, const int&, const int&) const override { return kClkBlock; }
    int ForeignFunction(int, const std::vector<int>& args) const override
    {
        return args.empty() ? kClkSample : join(args);
    }

    // the tables of the documentation generator are outside the calculus : the rules of
    // the variability, as they are
    int DocConstantTbl(const int&, const int& init) const override { return init; }
    int DocWriteTbl(const int&, const int& init, const int&, const int&) const override
    {
        return init | kClkSample;
    }
    int DocAccessTbl(const int& tbl, const int& ridx) const override { return tbl | ridx; }
    int Register(int, const int& s) const override { return s; }
};

}  // namespace

int clockVariability(int clock)
{
    switch (clock) {
        case kClkConst:
            return kKonst;
        case kClkBlock:
            return kBlock;
        default:
            return kSamp;  // the sample clock, and every clock derived from it
    }
}

struct ClockSolver::Impl {
    const RecPlan&        plan;
    ClockAlgebra          clk;
    FixPointIterator<int> it;

    explicit Impl(Tree root) : plan(getRecPlan(root)), it(plan, clk) {}
};

ClockSolver::ClockSolver(Tree root) : fImpl(new Impl(root)) {}

ClockSolver::~ClockSolver()
{
    delete fImpl;
}

int ClockSolver::clock(Tree sig) const
{
    return fImpl->it.value(sig);
}

void checkClockConcordance(Tree L)
{
    if (getenv("FAUST_CHECK_CLOCKS") == nullptr) {
        return;
    }
    const ClockSolver        clocks(L);
    std::unordered_set<Tree> seen;
    std::vector<Tree>        work{L};
    int                      signals = 0, differ = 0;
    while (!work.empty()) {
        Tree t = work.back();
        work.pop_back();
        if (!seen.insert(t).second) continue;
        Tree var, body;
        if (isRec(t, var, body)) {
            if (body) work.push_back(body);
            continue;
        }
        for (int i = 0; i < t->arity(); i++) work.push_back(t->branch(i));
        ::Type ty = getSigType(t);
        if (!ty) continue;
        signals++;
        const int clock = clocks.clock(t);
        if (clockVariability(clock) != ty->variability()) {
            if (differ < 10) {
                std::cerr << "clock differs : clock " << clock << ", variability " << ty->variability()
                          << " : " << ppsig(t, 10) << std::endl;
            }
            differ++;
        }
    }
    std::cerr << "clocks : " << signals << " signals, " << differ << " differ" << std::endl;
}
