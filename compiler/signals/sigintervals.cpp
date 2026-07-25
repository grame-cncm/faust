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

#include "sigintervals.hh"

#include <climits>
#include <cmath>
#include <cstdint>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <iostream>
#include <vector>

#include "interval.hh"  // gAlgebra and the free interval operators
#include "ppsig.hh"
#include "sigattributes.hh"  // collectTypedSignals
#include "signalAlgebra.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"

//----------------------------------------------------------------------------------------
// The interval attribute as a signal algebra.
//
// The interval is a VALUE attribute (see ATTRIBUTES.md): it describes the codomain, so
// a projection reads its own branch, a selector is excluded from select2, the delay
// amount is excluded from the delay's value. But unlike nature or booleanity its lattice
// is unbounded, so this is the first domain to engage the engine's approximate
// machinery: per-bound widening after a configurable number of rounds, then bounded
// narrowing. (The descending probe is deliberately NOT enabled yet: first measure the
// baseline strategy, then add the probe and measure its own contribution.)
//
// THE OBJECTIVE IS THE COMPUTATIONAL INTERVAL (Yann, 2026-07-25): the range of values
// the COMPILED program can actually produce for a signal -- int32 wrap-around included --
// not the mathematical range of the ideal formula. This is why [-2^31, 2^31] for an LCG
// noise generator is the right answer where the current system's [0,+inf) is not.
//
// TRANSFER FUNCTIONS ARE MIRRORED, NOT REDESIGNED. Every rule reproduces what
// inferSigType computes for the same constructor -- same gAlgebra calls, same special
// cases -- so that any difference observed against the current system is attributable
// to the iteration strategy alone. Known quirks are reproduced on purpose, e.g. foreign
// entities yield interval() ("unknown", = the NaN empty) which reunion then treats as
// NEUTRAL -- unsound if "unknown" means "any value", but faithful to the current system.
//
// Lattice conventions (interval_def.hh): empty = NaN bounds, reunion(empty, x) = x,
// so empty is a workable bottom; top is [-HUGE_VAL, HUGE_VAL] (the TRECMAX of the
// current system). The seed of a recursive variable is BOTTOM, not the current system's
// TREC [0,0]: the initial condition enters through the delay rule (Y@1 = Y ∪ α(0)),
// which is the temporal foundation of FIXPOINT-SPEC.md applied literally.
//----------------------------------------------------------------------------------------

namespace {

using itv::interval;

/// Bottom of the lattice: no values yet.
inline interval bot()
{
    return itv::empty();
}

/// Top of the lattice: any value (the current system's TRECMAX interval).
inline interval top_()
{
    return interval(-HUGE_VAL, HUGE_VAL);
}

/// x ⊑ y with the empty (NaN) conventions made explicit.
inline bool leq(const interval& x, const interval& y)
{
    if (x.isEmpty()) return true;
    if (y.isEmpty()) return false;
    return (y.lo() <= x.lo()) && (x.hi() <= y.hi());
}

class IntervalAlgebra : public SignalAlgebra<interval> {
   public:
    explicit IntervalAlgebra(int widenAfter = 8, int narrowFor = 3)
        : fWidenAfter(widenAfter), fNarrowFor(narrowFor)
    {
    }

    //--- the lattice ------------------------------------------------------------------
    interval bottom(Tree /*var*/) const override { return bot(); }
    interval top(Tree /*var*/) const override { return top_(); }
    bool lessEqual(const interval& x, const interval& y) const override { return leq(x, y); }

    // The interval is a value attribute: a projection reads its own branch.
    interval project(Tree, int i, const std::vector<interval>& row) const override
    {
        return row[i];
    }

    // Stationary OR DESCENDING stops the iteration. Ascending from ∅ the iterates grow
    // strictly, so this changes nothing before widening. After a widen-to-threshold,
    // though, the iterates DESCEND from the certified post-fixpoint -- soundly (lfp =
    // F(lfp) ⊑ F(p) by monotonicity, so every descending iterate still bounds the least
    // fixpoint) but geometrically: a leaky integrator contracts by ×0.9999 per round and
    // would burn the iteration cap without ever reaching equality, tripping the top
    // fallback. Accepting descent as convergence keeps the sound value instead.
    bool converged(const interval& prev, const interval& cur) const override
    {
        return leq(cur, prev);
    }

    //--- approximation control --------------------------------------------------------
    int widenAfter() const override { return fWidenAfter; }
    int maxNarrowingIterations() const override { return fNarrowFor; }
    int maxIterations() const override { return 1000; }  // guard-rail, top fallback

    //--- the descending probe ---------------------------------------------------------
    // Every recursive variable is probed with the seed [0, 2^30]: one descending step,
    // certification at SCC level (F#(seed) ⊑ seed on EVERY branch), bounded narrowing if
    // certified. A certified value is a POST-fixpoint, hence a sound ceiling: the least
    // fixpoint lies below it. The engine records the (narrowed) result per branch, and
    // widen() then jumps to that threshold instead of blowing the bound to infinity --
    // this is what turns a mod-counter's [0,+inf) (or worse) into the exact [0, N-1].
    //
    // The seed's integer lsb is deliberate: certification must run under the
    // COMPUTATIONAL semantics, wrap included. An LCG probe overflows, wraps, and fails
    // certification -- correctly, since an LCG is not non-negative.
    // Two attempts, in order of informativeness: the positivity seed [0, 2^30] first
    // (its certificate carries the sign, which mod-counters and envelopes want), then
    // the symmetric [-2^30, 2^30] that a CONTRACTING signed loop still satisfies -- a
    // Karplus-Strong string averages two past samples and attenuates, so
    // F([-B,B]) ⊑ [-B,B] holds even though the excitation is signed noise. The
    // certificate is weaker (no sign) but its threshold is finite, where widening alone
    // would blow the loop to (-inf,+inf).
    std::vector<interval> probeSeeds(Tree /*var*/) const override
    {
        if (getenv("FAUST_ITV_NOPROBE") != nullptr) return {};  // measurement A/B
        return {interval(0, kProbeBig, 0), interval(-kProbeBig, kProbeBig, 0)};
    }

    void recordProbe(Tree var, const interval& probed, bool sccCertified) const override
    {
        fProbe[var] = {probed, sccCertified};
        if (getenv("FAUST_ITV_TRACE") != nullptr && sccCertified) {
            std::cerr << "PROBE CERTIFIED " << probed << " : " << ppsig(var, 30) << std::endl;
        }
    }

    // Per-bound widening: only a bound that is still moving is touched, the stable one
    // keeps its value. A moving bound jumps to the certified probe threshold when there
    // is one; otherwise to the TOP OF ITS WORLD -- and the two worlds have different
    // tops. An INTEGER interval (lsb >= 0) saturates at [INT_MIN, INT_MAX]: that is the
    // computational truth (an unbounded int counter wraps, its values span the int32
    // range and no more), and it keeps the trajectory inside gAlgebra's integer
    // semantics, where +-inf is not a legal value. A FLOAT interval widens to +-inf with
    // the float lsb stamp. (The current system escapes to the float path uniformly via
    // TRECMAX's lsb; under the computational-interval doctrine we keep the int world
    // honest instead.) A probe-widened interval keeps its lsb: its bounds are finite.
    interval widen(Tree var, const interval& old, const interval& fresh) const override
    {
        if (old.isEmpty() || fresh.isEmpty()) return fresh;
        const bool wlo = fresh.lo() < old.lo();
        const bool whi = fresh.hi() > old.hi();
        if (!wlo && !whi) return fresh;

        auto it = fProbe.find(var);
        if (it != fProbe.end() && it->second.second) {
            const interval& p = it->second.first;
            // the threshold must actually bound the iterate (guards rounding surprises)
            if (!p.isEmpty() && p.lo() <= fresh.lo() && fresh.hi() <= p.hi()) {
                return {wlo ? p.lo() : fresh.lo(), whi ? p.hi() : fresh.hi(),
                        std::min(fresh.lsb(), p.lsb())};
            }
        }
        if (fresh.lsb() >= 0) {  // integer world: saturate at its computational top
            return {wlo ? double(INT_MIN) : fresh.lo(), whi ? double(INT_MAX) : fresh.hi(),
                    fresh.lsb()};
        }
        return {wlo ? -HUGE_VAL : fresh.lo(), whi ? HUGE_VAL : fresh.hi(),
                std::min(fresh.lsb(), -24)};
    }

    //--- injections -------------------------------------------------------------------
    // Nil and Label answer for syntax no operation consumes; empty is neutral in every
    // reunion, so they never perturb a value.
    interval Nil() const override { return bot(); }
    interval Label(const std::string&) const override { return bot(); }
    interval IntNum(int x) const override { return gAlgebra.IntNum(x); }
    interval Int64Num(int64_t x) const override { return gAlgebra.Int64Num(x); }
    interval FloatNum(double x) const override { return gAlgebra.FloatNum(x); }
    interval FixPointUpdate(const interval& x, const interval& y) const override
    {
        return itv::reunion(x, y);  // unreachable from the dense switch
    }

    //--- input / output ---------------------------------------------------------------
    interval Input(const interval&) const override { return {-1, 1}; }  // TINPUT
    interval Output(const interval&, const interval& x) const override { return x; }

    //--- user interface: mirrored on inferSigType, dummy name argument included --------
    interval Button(const interval&) const override { return gAlgebra.Button(interval(0, 0)); }
    interval Checkbox(const interval&) const override
    {
        return gAlgebra.Checkbox(interval(0, 0));
    }
    interval VSlider(const interval&, const interval& cur, const interval& lo,
                     const interval& hi, const interval& step) const override
    {
        return gAlgebra.VSlider(interval(0, 0), cur, lo, hi, step);
    }
    interval HSlider(const interval&, const interval& cur, const interval& lo,
                     const interval& hi, const interval& step) const override
    {
        return gAlgebra.HSlider(interval(0, 0), cur, lo, hi, step);
    }
    interval NumEntry(const interval&, const interval& cur, const interval& lo,
                      const interval& hi, const interval& step) const override
    {
        return gAlgebra.NumEntry(interval(0, 0), cur, lo, hi, step);
    }
    // A bargraph reports the displayed signal; the range bounds do not participate.
    interval HBargraph(const interval&, const interval&, const interval&,
                       const interval& s) const override
    {
        return s;
    }
    interval VBargraph(const interval&, const interval&, const interval&,
                       const interval& s) const override
    {
        return s;
    }

    interval Attach(const interval& x, const interval&) const override { return x; }
    interval Enable(const interval& x, const interval&) const override { return x; }
    interval Control(const interval& x, const interval&) const override { return x; }

    //--- arithmetic: exactly the calls sigtyperules' arithmetic() makes ---------------
    // The empty guard makes the strict "no values in, no values out" explicit: not every
    // gAlgebra operation checks it, and NaN through min/max games is not trustworthy.
    interval Add(const interval& x, const interval& y) const override
    {
        return g2(x, y, [](const interval& a, const interval& b) { return gAlgebra.Add(a, b); });
    }
    interval Sub(const interval& x, const interval& y) const override
    {
        return g2(x, y, [](const interval& a, const interval& b) { return gAlgebra.Sub(a, b); });
    }
    interval Mul(const interval& x, const interval& y) const override
    {
        return g2(x, y, [](const interval& a, const interval& b) { return gAlgebra.Mul(a, b); });
    }
    interval Div(const interval& x, const interval& y) const override
    {
        return g2(x, y, [](const interval& a, const interval& b) { return gAlgebra.Div(a, b); });
    }
    interval Mod(const interval& x, const interval& y) const override
    {
        return g2(x, y, [](const interval& a, const interval& b) { return gAlgebra.Mod(a, b); });
    }
    interval Neg(const interval& x) const override
    {
        return g1(x, [](const interval& a) { return gAlgebra.Neg(a); });
    }
    interval Inv(const interval& x) const override
    {
        return g1(x, [](const interval& a) { return gAlgebra.Inv(a); });
    }
    interval Abs(const interval& x) const override
    {
        return g1(x, [](const interval& a) { return gAlgebra.Abs(a); });
    }
    // highest / lowest reduce a signal to one of its constant bounds
    interval Highest(const interval& x) const override { return interval(x.hi()); }
    interval Lowest(const interval& x) const override { return interval(x.lo()); }

    //--- comparisons ------------------------------------------------------------------
    interval Gt(const interval& x, const interval& y) const override
    {
        return g2(x, y, [](const interval& a, const interval& b) { return gAlgebra.Gt(a, b); });
    }
    interval Lt(const interval& x, const interval& y) const override
    {
        return g2(x, y, [](const interval& a, const interval& b) { return gAlgebra.Lt(a, b); });
    }
    interval Ge(const interval& x, const interval& y) const override
    {
        return g2(x, y, [](const interval& a, const interval& b) { return gAlgebra.Ge(a, b); });
    }
    interval Le(const interval& x, const interval& y) const override
    {
        return g2(x, y, [](const interval& a, const interval& b) { return gAlgebra.Le(a, b); });
    }
    interval Eq(const interval& x, const interval& y) const override
    {
        return g2(x, y, [](const interval& a, const interval& b) { return gAlgebra.Eq(a, b); });
    }
    interval Ne(const interval& x, const interval& y) const override
    {
        return g2(x, y, [](const interval& a, const interval& b) { return gAlgebra.Ne(a, b); });
    }
    interval Not(const interval& x) const override
    {
        return g1(x, [](const interval& a) { return gAlgebra.Not(a); });
    }

    //--- bitwise and shifts -----------------------------------------------------------
    // Mirrored on the binop rule's `intCast(t3)`: shifts and bitwise operations always
    // result in an int, so their interval is truncated to integers. Without it, a shift
    // by 4 divides by 16 with REAL semantics and produces fractional bounds ([0, 6.1875]
    // where the compiled program can only reach [0, 6] -- the dx7 root divergence).
    interval And(const interval& x, const interval& y) const override
    {
        return g2(x, y, [](const interval& a, const interval& b) {
            return gAlgebra.IntCast(gAlgebra.And(a, b));
        });
    }
    interval Or(const interval& x, const interval& y) const override
    {
        return g2(x, y, [](const interval& a, const interval& b) {
            return gAlgebra.IntCast(gAlgebra.Or(a, b));
        });
    }
    interval Xor(const interval& x, const interval& y) const override
    {
        return g2(x, y, [](const interval& a, const interval& b) {
            return gAlgebra.IntCast(gAlgebra.Xor(a, b));
        });
    }
    interval Lsh(const interval& x, const interval& y) const override
    {
        return g2(x, y, [](const interval& a, const interval& b) {
            return gAlgebra.IntCast(gAlgebra.Lsh(a, b));
        });
    }
    interval ARsh(const interval& x, const interval& y) const override
    {
        return g2(x, y, [](const interval& a, const interval& b) {
            return gAlgebra.IntCast(gAlgebra.ARsh(a, b));
        });
    }
    interval LRsh(const interval& x, const interval& y) const override
    {
        return g2(x, y, [](const interval& a, const interval& b) {
            return gAlgebra.IntCast(gAlgebra.LRsh(a, b));
        });
    }

    //--- casts. The type combinators keep the interval except intCast -----------------
    interval IntCast(const interval& x) const override
    {
        return g1(x, [](const interval& a) { return gAlgebra.IntCast(a); });
    }
    interval BitCast(const interval& x) const override { return x; }
    interval FloatCast(const interval& x) const override { return x; }

    //--- transcendental and rounding: one gAlgebra call each, as the xtended prims do --
    interval Acos(const interval& x) const override
    {
        return g1(x, [](const interval& a) { return gAlgebra.Acos(a); });
    }
    interval Acosh(const interval& x) const override
    {
        return g1(x, [](const interval& a) { return gAlgebra.Acosh(a); });
    }
    interval Asin(const interval& x) const override
    {
        return g1(x, [](const interval& a) { return gAlgebra.Asin(a); });
    }
    interval Asinh(const interval& x) const override
    {
        return g1(x, [](const interval& a) { return gAlgebra.Asinh(a); });
    }
    interval Atan(const interval& x) const override
    {
        return g1(x, [](const interval& a) { return gAlgebra.Atan(a); });
    }
    interval Atan2(const interval& x, const interval& y) const override
    {
        return g2(x, y,
                  [](const interval& a, const interval& b) { return gAlgebra.Atan2(a, b); });
    }
    interval Atanh(const interval& x) const override
    {
        return g1(x, [](const interval& a) { return gAlgebra.Atanh(a); });
    }
    interval Ceil(const interval& x) const override
    {
        return g1(x, [](const interval& a) { return gAlgebra.Ceil(a); });
    }
    interval Cos(const interval& x) const override
    {
        return g1(x, [](const interval& a) { return gAlgebra.Cos(a); });
    }
    interval Cosh(const interval& x) const override
    {
        return g1(x, [](const interval& a) { return gAlgebra.Cosh(a); });
    }
    interval Exp(const interval& x) const override
    {
        return g1(x, [](const interval& a) { return gAlgebra.Exp(a); });
    }
    interval Exp10(const interval& x) const override
    {
        // exp10prim: gAlgebra.Pow(interval(10, 10, 0), x)
        return g1(x, [](const interval& a) { return gAlgebra.Pow(interval(10, 10, 0), a); });
    }
    interval Floor(const interval& x) const override
    {
        return g1(x, [](const interval& a) { return gAlgebra.Floor(a); });
    }
    interval Log(const interval& x) const override
    {
        return g1(x, [](const interval& a) { return gAlgebra.Log(a); });
    }
    interval Log10(const interval& x) const override
    {
        return g1(x, [](const interval& a) { return gAlgebra.Log10(a); });
    }
    interval Pow(const interval& x, const interval& y) const override
    {
        return g2(x, y, [](const interval& a, const interval& b) { return gAlgebra.Pow(a, b); });
    }
    interval Remainder(const interval& x, const interval& y) const override
    {
        return g2(x, y,
                  [](const interval& a, const interval& b) { return gAlgebra.Remainder(a, b); });
    }
    interval Rint(const interval& x) const override
    {
        return g1(x, [](const interval& a) { return gAlgebra.Rint(a); });
    }
    interval Round(const interval& x) const override
    {
        // roundprim delegates to Rint ("Round is missing in interval library")
        return g1(x, [](const interval& a) { return gAlgebra.Rint(a); });
    }
    interval Sin(const interval& x) const override
    {
        return g1(x, [](const interval& a) { return gAlgebra.Sin(a); });
    }
    interval Sinh(const interval& x) const override
    {
        return g1(x, [](const interval& a) { return gAlgebra.Sinh(a); });
    }
    interval Sqrt(const interval& x) const override
    {
        return g1(x, [](const interval& a) { return gAlgebra.Sqrt(a); });
    }
    interval Tan(const interval& x) const override
    {
        return g1(x, [](const interval& a) { return gAlgebra.Tan(a); });
    }
    interval Tanh(const interval& x) const override
    {
        return g1(x, [](const interval& a) { return gAlgebra.Tanh(a); });
    }
    interval Max(const interval& x, const interval& y) const override
    {
        return g2(x, y, [](const interval& a, const interval& b) { return gAlgebra.Max(a, b); });
    }
    interval Min(const interval& x, const interval& y) const override
    {
        return g2(x, y, [](const interval& a, const interval& b) { return gAlgebra.Min(a, b); });
    }

    //--- selection: value attribute, the selector is excluded -------------------------
    interval Select2(const interval&, const interval& x, const interval& y) const override
    {
        return itv::reunion(x, y);
    }

    //--- delays: THE temporal rule, Y@n = Y ∪ α(0) -------------------------------------
    // The delay amount is excluded from the value. reunion treats empty as neutral, so
    // the seed ∅ of a recursive variable becomes [0,0] through its first delayed read --
    // the initial condition enters here and nowhere else.
    // (The zero singleton is always integer-lsb by construction -- the interval ctor
    // forces lsb 0 on [0,0] -- so recursive integer chains stay on gAlgebra's integer
    // path until they widen; see widen() for the float switch that mirrors TRECMAX.)
    interval Mem(const interval& x) const override { return itv::reunion(x, interval(0, 0)); }
    interval Delay(const interval& x, const interval&) const override
    {
        return itv::reunion(x, interval(0, 0));
    }
    interval Prefix(const interval& x, const interval& y) const override
    {
        return itv::reunion(x, y);
    }
    // assertbounds: clip to the declared range; an unknown candidate takes the range.
    interval AssertBounds(const interval& lo, const interval& hi,
                          const interval& x) const override
    {
        if (lo.isEmpty() || hi.isEmpty()) return x;
        if (x.isEmpty()) return {lo.lo(), hi.hi()};
        return {std::max(x.lo(), lo.lo()), std::min(x.hi(), hi.hi())};
    }

    //--- tables. A table's interval is its content's; a read returns it ---------------
    interval Table(const interval&, const interval& content) const override { return content; }
    interval WRTbl(const interval&, const interval& g, const interval&,
                   const interval& ws) const override
    {
        return itv::reunion(g, ws);
    }
    interval RDTbl(const interval& tbl, const interval&) const override { return tbl; }
    interval Gen(const interval& x) const override { return x; }
    interval Waveform(const std::vector<interval>& w) const override
    {
        interval r = bot();
        for (const interval& x : w) {
            r = itv::reunion(r, x);
        }
        return r;
    }

    //--- soundfiles -------------------------------------------------------------------
    interval SoundFile(const interval&) const override { return {0, double(INT32_MAX)}; }
    interval SoundFileRate(const interval&, const interval&) const override
    {
        return {0, double(INT32_MAX)};
    }
    interval SoundFileLength(const interval&, const interval&) const override
    {
        return {0, double(INT32_MAX)};
    }
    interval SoundFileBuffer(const interval&, const interval&, const interval&,
                             const interval&) const override
    {
        return {-1, 1};
    }

    //--- foreign entities: interval() = "unknown", exactly as the current system ------
    interval ForeignConst(int, const interval&, const interval&) const override
    {
        return interval();
    }
    interval ForeignVar(int, const interval&, const interval&) const override
    {
        return interval();
    }
    interval ForeignFunction(int, const std::vector<interval>&) const override
    {
        return interval();
    }

    //--- signal-language-only constructors --------------------------------------------
    interval DocConstantTbl(const interval&, const interval& init) const override
    {
        return init;
    }
    interval DocWriteTbl(const interval&, const interval& init, const interval&,
                         const interval&) const override
    {
        return init;  // inferDocWriteTblType promotes temporality only
    }
    interval DocAccessTbl(const interval& tbl, const interval&) const override { return tbl; }
    interval Register(int, const interval& s) const override { return s; }
    interval Tuple(int, const std::vector<interval>&) const override
    {
        return interval();  // never typed by the current system
    }
    interval TupleAccess(const interval& ts, const interval&) const override { return ts; }

   private:
    // Empty guards for the value operations: no values in, no values out. Centralized
    // because not every gAlgebra operation checks emptiness itself, and NaN bounds
    // surviving min/max arithmetic are implementation-defined.
    template <typename F>
    static interval g1(const interval& x, F f)
    {
        return x.isEmpty() ? itv::empty() : f(x);
    }
    template <typename F>
    static interval g2(const interval& x, const interval& y, F f)
    {
        return (x.isEmpty() || y.isEmpty()) ? itv::empty() : f(x, y);
    }

    static constexpr double kProbeBig = 1073741824.0;  // 2^30 : headroom under INT_MAX

    int fWidenAfter;
    int fNarrowFor;

    /// Probe results, keyed by proj(b, var) as the engine hands them out. Mutable: the
    /// probe table is engine feedback, not part of the denotation (same convention as
    /// the toy domains in tlib's tests).
    mutable std::unordered_map<Tree, std::pair<interval, bool>> fProbe;
};

}  // namespace

//----------------------------------------------------------------------------------------
// Shadow comparison: classify, don't equate -- there is no exact oracle here.
//----------------------------------------------------------------------------------------

namespace {

// Under FAUST_ITV_EXPLAIN, dump the operand intervals (ours vs the reference's) of a
// diverging binop: divergences on comparisons are usually CASCADES from an operand
// classified elsewhere, and this shows which operand and by how much.
void explainBinOp(FixPointIterator<interval>& it, Tree sig)
{
    if (getenv("FAUST_ITV_EXPLAIN") == nullptr) return;
    int  op;
    Tree x, y;
    if (!isSigBinOp(sig, &op, x, y)) return;
    for (Tree operand : {x, y}) {
        AudioType*  ty = getSigType(operand);
        SimpleType* st = ty ? isSimpleType(ty) : nullptr;
        std::cerr << "    operand " << it.value(operand) << " vs ref "
                  << (st ? st->getInterval() : itv::interval()) << " : " << ppsig(operand, 25)
                  << std::endl;
    }
}

}  // namespace

IntervalShadowStats shadowCheckInterval(Tree L, bool verbose)
{
    RecPlan                    plan(L);
    IntervalAlgebra            algebra;
    FixPointIterator<interval> it(plan, algebra);

    IntervalShadowStats stats;
    const TypedNodes    nodes = collectTypedSignals(L);

    int shownWider = 0, shownIncomp = 0, shownEmpty = 0;
    for (const auto& n : nodes) {
        const interval mine = it.value(n.first);
        const interval ref  = n.second->getInterval();

        const bool mEmpty = mine.isEmpty();
        const bool rEmpty = ref.isEmpty();

        if (mEmpty && rEmpty) {
            stats.equal++;
        } else if (mEmpty) {
            stats.toEmpty++;
            if (verbose && shownEmpty++ < 5) {
                std::cerr << "ITV EMPTY   : ref " << ref << " : " << ppsig(n.first, 40)
                          << std::endl;
            }
        } else if (rEmpty) {
            stats.fromTop++;  // bounded where the current system had no information
        } else if (mine.lo() == ref.lo() && mine.hi() == ref.hi()) {
            stats.equal++;
        } else if (leq(mine, ref)) {
            stats.tighter++;
        } else if (mine.lo() < ref.lo() && mine.hi() <= ref.hi()) {
            // floor-only disagreement: the reference asserts a floor we refute
            stats.floorRefuted++;
        } else if (leq(ref, mine)) {
            stats.wider++;
            if (verbose && shownWider++ < 5) {
                std::cerr << "ITV WIDER   : " << mine << " vs ref " << ref << " : "
                          << ppsig(n.first, 40) << std::endl;
                explainBinOp(it, n.first);
            }
        } else {
            stats.incomparable++;
            if (verbose && shownIncomp++ < 5) {
                std::cerr << "ITV INCOMP  : " << mine << " vs ref " << ref << " : "
                          << ppsig(n.first, 40) << std::endl;
            }
        }
    }

    if (verbose) {
        std::cerr << "ITV SHADOW : " << stats.total() << " signals, eq=" << stats.equal
                  << " tighter=" << stats.tighter << " fromTop=" << stats.fromTop
                  << " floorRefuted=" << stats.floorRefuted << " wider=" << stats.wider
                  << " toEmpty=" << stats.toEmpty << " incomp=" << stats.incomparable
                  << std::endl;
    }
    return stats;
}


//----------------------------------------------------------------------------------------
// The two roles, measured on their consumption sites.
//----------------------------------------------------------------------------------------

namespace {

/// Integer bits needed to represent the range (the msb of a fixed-point format),
/// capped at 64: beyond that a fixed-point format is fiction anyway, and the cap keeps
/// one pathological bound from dominating a corpus-wide sum.
int msbOf(const interval& x)
{
    const double m = std::max(std::fabs(x.lo()), std::fabs(x.hi()));
    if (m < 1) return 0;
    return std::min(64, int(std::ceil(std::log2(m + 1))));
}

bool boundedItv(const interval& x)
{
    return !x.isEmpty() && std::isfinite(x.lo()) && std::isfinite(x.hi());
}

}  // namespace

IntervalRolesStats intervalRolesReport(Tree L, bool verbose)
{
    RecPlan                    plan(L);
    IntervalAlgebra            algebra;
    FixPointIterator<interval> it(plan, algebra);

    IntervalRolesStats st;
    std::unordered_set<Tree> visited;
    std::vector<Tree>        work{L};

    auto refItv = [](Tree t) -> interval {
        AudioType*  ty = getSigType(t);
        SimpleType* s  = ty ? isSimpleType(ty) : nullptr;
        return s ? s->getInterval() : itv::interval();
    };

    while (!work.empty()) {
        Tree t = work.back();
        work.pop_back();
        if (!visited.insert(t).second) continue;

        Tree var, body;
        if (isRec(t, var, body)) {
            if (body) work.push_back(body);
            continue;
        }

        Tree x, n, tbl, ri, size, gen, wi, ws;

        // --- correctness: delay-line allocation, driven by the amount's hi ------------
        if (isSigDelay(t, x, n)) {
            const interval r = refItv(n);
            const interval m = it.value(n);
            const bool     rb = boundedItv(r), mb = boundedItv(m);
            if (rb || mb) st.delaySites++;
            if (mb && !rb) {
                st.delayOnlyUs++;
            } else if (rb && !mb) {
                st.delayOnlyRef++;
                if (verbose) {
                    std::cerr << "ROLES delay : réf bornée " << r << ", nous non : "
                              << ppsig(n, 30) << std::endl;
                }
            } else if (rb && mb) {
                if (m.hi() < r.hi()) {
                    st.delayTighter++;
                } else if (m.hi() == r.hi()) {
                    st.delayEqual++;
                } else {
                    st.delayWider++;
                    if (verbose) {
                        std::cerr << "ROLES delay : nous " << m.hi() << " vs réf " << r.hi()
                                  << " : " << ppsig(n, 30) << std::endl;
                    }
                }
            }
        }

        // --- correctness: table accesses provably inside [0, size) --------------------
        auto checkAccess = [&](Tree table, Tree index) {
            int  sz;
            Tree s1, s2, s3, s4;
            if (!isSigWRTbl(table, s1, s2, s3, s4)) return;
            if (!isSigInt(s1, &sz)) return;  // dynamic sizes: skip
            const interval r  = refItv(index);
            const interval m  = it.value(index);
            const auto     ok = [&](const interval& i) {
                return boundedItv(i) && i.lo() >= 0 && i.hi() < double(sz);
            };
            st.tableAccesses++;
            const bool ro = ok(r), mo = ok(m);
            if (ro && mo) {
                st.tableSafeBoth++;
            } else if (mo) {
                st.tableSafeUsOnly++;
            } else if (ro) {
                st.tableSafeRefOnly++;
                if (verbose) {
                    std::cerr << "ROLES table : réf prouve " << r << ", nous " << m << " : "
                              << ppsig(index, 30) << std::endl;
                }
            } else {
                st.tableSafeNone++;
            }
        };
        if (isSigRDTbl(t, tbl, ri)) checkAccess(tbl, ri);
        if (isSigWRTbl(t, size, gen, wi, ws) && wi != ::nil()) checkAccess(t, wi);

        // --- quality: integer bits of the fixed-point format --------------------------
        // Only signals the current system typed with a SimpleType: the same comparison
        // set as the shadow, free of walk artifacts (opcode leaves, list spines).
        {
            AudioType*  ty = getSigType(t);
            SimpleType* sy = ty ? isSimpleType(ty) : nullptr;
            if (sy != nullptr) {
                const interval r  = sy->getInterval();
                const interval m  = it.value(t);
                const bool     rb = boundedItv(r), mb = boundedItv(m);
                if (rb && mb) {
                    st.formatSites++;
                    st.formatBitsSaved += msbOf(r) - msbOf(m);
                } else if (mb) {
                    st.formatOnlyUs++;
                } else if (rb) {
                    st.formatOnlyRef++;
                    if (verbose && st.formatOnlyRef <= 3) {
                        std::cerr << "ROLES format : réf bornée " << r << ", nous " << m
                                  << " : " << ppsig(t, 30) << std::endl;
                    }
                }
            }
        }

        for (int i = 0; i < t->arity(); i++) {
            work.push_back(t->branch(i));
        }
    }

    if (verbose) {
        std::cerr << "ROLES delay : sites=" << st.delaySites << " serrés=" << st.delayTighter
                  << " égaux=" << st.delayEqual << " larges=" << st.delayWider
                  << " bornés-par-nous-seuls=" << st.delayOnlyUs
                  << " par-réf-seule=" << st.delayOnlyRef << std::endl;
        std::cerr << "ROLES table : accès=" << st.tableAccesses
                  << " prouvés-les-deux=" << st.tableSafeBoth
                  << " nous-seuls=" << st.tableSafeUsOnly
                  << " réf-seule=" << st.tableSafeRefOnly << " aucun=" << st.tableSafeNone
                  << std::endl;
        std::cerr << "ROLES format : sites=" << st.formatSites
                  << " bits-gagnés=" << st.formatBitsSaved
                  << " bornés-par-nous-seuls=" << st.formatOnlyUs
                  << " par-réf-seule=" << st.formatOnlyRef << std::endl;
    }
    return st;
}
