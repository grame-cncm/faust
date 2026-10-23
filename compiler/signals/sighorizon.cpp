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

#include <limits>

#include "sighorizon.hh"
#include "mixForm.hh"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "affine_ops.hh"  // the numeric core: AffItv, AffineOps (interval library)
#include "ppsig.hh"
#include "signalAlgebra.hh"
#include "sigattributes.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"

//----------------------------------------------------------------------------------------
// The tree-aware layer of THE interval domain (design decision, 2026-07-25: the affine
// domain is the interval domain; the ordinary one survives inside it as the rate-0
// subdomain and as the oracle of the nonlinear operations).
//
// Everything numeric lives in the interval library (affint.hh, affine_ops.hh). This file
// adds only what needs trees: the FixPointDomain glue, the probe (Tree-keyed), the
// signal-only constructors, and the analyses (horizon dating, reader).
//----------------------------------------------------------------------------------------

namespace {

using itv::AffItv;
using itv::interval;

class HorizonAlgebra : public itv::AffineOps<SignalAlgebra<AffItv>> {
    static constexpr double kBig = 1073741824.0;  // 2^30

    /// Probe results, keyed by proj(b, var). Mutable: engine feedback, not denotation.
    mutable std::unordered_map<Tree, std::pair<AffItv, bool>> fProbe;

    /// Widening history, keyed by proj(b, var): the previous iterate and the number of
    /// extrapolation rounds spent. Mutable: engine feedback, not denotation.
    struct Extrapolation {
        AffItv old, fresh;  ///< the previous widening call : an iterate and its image
        int    rounds = 0;
    };
    mutable std::unordered_map<Tree, Extrapolation> fExtrapolation;

    /// The content of the tables generated at init, analysed apart (tableContent)
    mutable std::unordered_map<Tree, AffItv> fTableContent;
    /// The exact attributes of the root, when known : the nature of a value
    const ExactSolvers* fExact = nullptr;
    /// Memos of the cheap filters of the sum rules (hasRoundingTerm, hasComplementTerm) :
    /// flattening every node of a long sum chain would be quadratic.
    mutable std::unordered_map<Tree, bool> fHasRoundingTerm, fHasComplementTerm;
    static constexpr int kExtrapolationRounds = 4;  // one to record, three to extrapolate

    static double horizonFromEnv()
    {
        return 2147483648.0;  // default: 2^31 samples
    }

   public:
    //--- helpers : the shapes the rules recognize -------------------------------------

    /// t is a numeric constant, integer or real
    static bool constNum(Tree t, double& v)
    {
        int    i;
        double r;
        if (isSigInt(t, &i)) {
            v = i;
            return true;
        }
        if (isSigReal(t, &r)) {
            v = r;
            return true;
        }
        return false;
    }

    /// t is the constant 1, integer or real
    static bool isOneConst(Tree t)
    {
        double r;
        int    i;
        return (isSigReal(t, &r) && r == 1.0) || (isSigInt(t, &i) && i == 1);
    }

    /// a and b are the same expression, a numeric constant matching its value whatever
    /// its type (the normal form may write -1 and -1.0 for one value)
    static bool sameValue(Tree a, Tree b, int depth = 0)
    {
        if (a == b) return true;
        double x, y;
        if (constNum(a, x) && constNum(b, y)) return x == y;
        if (depth > 32 || a->node() != b->node() || a->arity() != b->arity()) return false;
        for (int i = 0; i < a->arity(); i++) {
            if (!sameValue(a->branch(i), b->branch(i), depth + 1)) return false;
        }
        return true;
    }

    /// t is a product of two factors : a binary *, or the two-factor Prod of the normal form
    static bool twoFactors(Tree t, Tree& a, Tree& b)
    {
        int  op;
        tvec fs;
        if (isSigBinOp(t, &op, a, b) && op == kMul) return true;
        if (isSigProd(t, fs) && fs.size() == 2) {
            a = fs[0];
            b = fs[1];
            return true;
        }
        return false;
    }

    /// t is a product : a binary *, or the Prod of the normal form
    static bool isProduct(Tree t)
    {
        int  op;
        Tree a, b;
        return (isSigBinOp(t, &op, a, b) && op == kMul) || isSigProd(t);
    }

    /// t is *(-1, x) : a negation, in the -fir form
    static bool negationOf(Tree t, Tree& x)
    {
        Tree   a, b;
        double k;
        if (isSigNeg(t, x)) return true;
        if (!twoFactors(t, a, b)) return false;
        if (constNum(a, k) && k == -1) {
            x = b;
            return true;
        }
        if (constNum(b, k) && k == -1) {
            x = a;
            return true;
        }
        return false;
    }

    /// t is x + k, k a number : a binary + or -, or the two-term Sum of the normal form,
    /// whose number follows the term ; x - k gives -k, and k - x gives x negated (sign -1)
    static bool shiftOf(Tree t, Tree& x, double& k, int& sign)
    {
        int  op;
        Tree a, b;
        tvec subs;
        if (isSigBinOp(t, &op, a, b) && (op == kAdd || op == kSub)) {
            if (constNum(b, k)) {
                x    = a;
                k    = (op == kAdd) ? k : -k;
                sign = 1;
                return true;
            }
            if (constNum(a, k)) {
                x    = b;
                sign = (op == kAdd) ? 1 : -1;
                return true;
            }
            return false;
        }
        if (isSigSum(t, subs) && subs.size() == 2) {
            Tree u;
            if (constNum(subs[1], k)) {
                u = subs[0];
            } else if (constNum(subs[0], k)) {
                u = subs[1];
            } else {
                return false;
            }
            sign = negationOf(u, x) ? -1 : 1;
            if (sign > 0) x = u;
            return true;
        }
        return false;
    }

    /// t is a sum : a binary + or -, or the n-ary Sum of the normal form
    static bool isSum(Tree t)
    {
        int  op;
        Tree a, b;
        return (isSigBinOp(t, &op, a, b) && (op == kAdd || op == kSub)) || isSigSum(t);
    }

    /// the terms of a sum (binary +, -, the n-ary Sum of the -fir form, negations),
    /// flattened with their signs
    static void sumTerms(Tree t, int sign, std::vector<std::pair<Tree, int>>& out)
    {
        int  op;
        Tree a, b;
        tvec subs;
        if (isSigBinOp(t, &op, a, b) && (op == kAdd || op == kSub)) {
            sumTerms(a, sign, out);
            sumTerms(b, op == kAdd ? sign : -sign, out);
            return;
        }
        if (isSigSum(t, subs)) {
            for (Tree u : subs) sumTerms(u, sign, out);
            return;
        }
        if (negationOf(t, a)) {
            sumTerms(a, -sign, out);
            return;
        }
        out.push_back({t, sign});
    }

    /// the factors of a product (binary * and Prod), flattened
    static void productFactors(Tree t, std::vector<Tree>& out)
    {
        int  op;
        Tree x, y;
        tvec fs;
        if (isSigBinOp(t, &op, x, y) && op == kMul) {
            productFactors(x, out);
            productFactors(y, out);
            return;
        }
        if (isSigProd(t, fs)) {
            for (Tree f : fs) productFactors(f, out);
            return;
        }
        out.push_back(t);
    }

    /// t is 1 - c : a binary -, or the Sum 1 + neg(c) of the normal form
    static bool complementOf(Tree t, Tree& c)
    {
        int  op;
        Tree a, b;
        tvec subs;
        if (isSigBinOp(t, &op, a, b) && op == kSub && isOneConst(a)) {
            c = b;
            return true;
        }
        return isSigSum(t, subs) && subs.size() == 2 && isOneConst(subs[0]) && isSigNeg(subs[1], c);
    }

    /// w is 1 - c : a binary 1 - c, or the Sum(1, neg(t1), ..., neg(tn)) of the normal
    /// form, c being t1 or the Sum(t1, ..., tn) of the same terms
    static bool complementPair(Tree w, Tree c)
    {
        Tree x;
        tvec ws, cs;
        if (complementOf(w, x) && sameValue(x, c)) return true;
        if (!isSigSum(w, ws) || ws.size() < 3 || !isOneConst(ws[0])) return false;
        if (!isSigSum(c, cs) || cs.size() != ws.size() - 1) return false;
        for (size_t i = 1; i < ws.size(); i++) {
            if (!isSigNeg(ws[i], x) || !sameValue(x, cs[i - 1])) return false;
        }
        return true;
    }

    /// w is 1 - c for some c, in either writing
    static bool isComplement(Tree w)
    {
        Tree x;
        tvec ws;
        if (complementOf(w, x)) return true;
        if (!isSigSum(w, ws) || ws.size() < 3 || !isOneConst(ws[0])) return false;
        for (size_t i = 1; i < ws.size(); i++) {
            if (!isSigNeg(ws[i], x)) return false;
        }
        return true;
    }

    /// does the product t (flattened) hold a factor 1 - c
    static bool hasComplementFactor(Tree t)
    {
        int  op;
        Tree a, b;
        tvec fs;
        if (isSigBinOp(t, &op, a, b) && op == kMul) return hasComplementFactor(a) || hasComplementFactor(b);
        if (isSigProd(t, fs)) {
            for (Tree f : fs) {
                if (hasComplementFactor(f)) return true;
            }
            return false;
        }
        return isComplement(t);
    }

    /// t is abs(x)
    static bool absArg(Tree t, Tree& x)
    {
        if (t->arity() == 1 && sigs::g.gAbsPrim != nullptr &&
            getUserData(t) == static_cast<void*>(sigs::g.gAbsPrim)) {
            x = t->branch(0);
            return true;
        }
        return false;
    }

    /// t is prim(x)
    static bool primArg(Tree t, xtended* prim, Tree& x)
    {
        if (t->arity() == 1 && prim != nullptr && getUserData(t) == static_cast<void*>(prim)) {
            x = t->branch(0);
            return true;
        }
        return false;
    }

    /// t is floor(x), rint(x) or ceil(x)
    static bool roundingOf(Tree t, Tree& x)
    {
        double lo, hi;
        return roundingArg(t, x, lo, hi);
    }

    // the roundings of the rule : X - floor(X) lies in [0, 1], X - rint(X) in
    // [-1/2, 1/2], X - ceil(X) in [-1, 0] ; the subtraction is exact in all three
    // (Sterbenz : the rounded value is within a factor 2 of X, or 0)
    static bool roundingArg(Tree t, Tree& x, double& lo, double& hi)
    {
        if (t->arity() != 1) return false;
        void* p = getUserData(t);
        if (p == nullptr) return false;
        if (p == static_cast<void*>(sigs::g.gFloorPrim)) {
            lo = 0;
            hi = 1;
        } else if (p == static_cast<void*>(sigs::g.gRintPrim)) {
            lo = -0.5;
            hi = 0.5;
        } else if (p == static_cast<void*>(sigs::g.gCeilPrim)) {
            lo = -1;
            hi = 0;
        } else {
            return false;
        }
        x = t->branch(0);
        return true;
    }

    //--- the remainder of a rounding --------------------------------------------------

    // The fractional part x - floor(x) of a finite x lies in [0, 1]. The subtraction
    // of two intervals forgets that both terms read the same x (the dependency
    // problem) : a phase accumulator ma.frac(x' + inc) widened to [-inf, +inf], and
    // with it every conversion and table index it feeds. The normal form may have
    // spread x over the enclosing sum ((inc - floor(inc + x')) + x') : the rule reads
    // the sum flattened into signed terms, and counts a term floor(X) together with
    // all the terms of X, of the opposite sign, as frac(X) (or -frac(X)). The same
    // holds for the remainders of the other roundings, X - rint(X) in [-1/2, 1/2]
    // (the fixed-point phasor of the libraries) and X - ceil(X) in [-1, 0].
    //
    // The interval holds the values the program computes, not the real fractional
    // part. Computed as X - floor(X) with X rounded once, the result is exact (floor(X)
    // is 0 below 1, and within a factor 2 of X above : Sterbenz) and lies in [0, 1[,
    // [0, 1] for a negative X. But the program may compute the terms of X in another
    // order than the one inside floor, and a multiply-add contraction may round a
    // product inside floor and not outside : the two readings of X then differ by
    // a few rounding errors, and the result may leave [0, 1] by as much (a phase just
    // below 0 when X rounds up to an integer). The rule widens [0, 1] by that bound :
    // three times the error of a sum of n terms, gamma(n) * sum |t_i|, plus the loss
    // of a flush to zero on each addition. In the plain form X - floor(X), X one
    // term, only a contraction of the product computing X is left : half an ulp of X.
    // An X that may be infinite or invalid gives a possible NaN (inf - inf).

    /// frac(X) recognized in the sum sig, or nothing ; the remaining terms are added
    bool fractionalSum(Tree sig, FixPointEvaluator<AffItv>& ev, AffItv& result) const
    {
        std::vector<std::pair<Tree, int>> terms;
        sumTerms(sig, 1, terms);
        for (size_t i = 0; i < terms.size(); i++) {
            Tree   x;
            double rlo, rhi;
            if (!roundingArg(terms[i].first, x, rlo, rhi)) continue;
            const int                         s = terms[i].second;
            std::vector<std::pair<Tree, int>> xs;
            sumTerms(x, 1, xs);
            std::vector<char> used(terms.size(), 0);
            used[i]  = 1;
            bool all = true;
            for (const auto& [u, e] : xs) {
                bool found = false;
                for (size_t j = 0; j < terms.size(); j++) {
                    if (!used[j] && terms[j].first == u && terms[j].second == -s * e) {
                        used[j] = 1;
                        found   = true;
                        break;
                    }
                }
                if (!found) {
                    all = false;
                    break;
                }
            }
            if (!all) continue;

            const AffItv ax = ev.eval(x);
            if (ax.isEmpty()) return false;
            const interval ix = itv::toItv(ax, fT);
            // the magnitude of every term of the sum, floor(X) included
            double mag = std::max(std::abs(ix.lo()), std::abs(ix.hi())) + 1;
            for (size_t j = 0; j < terms.size(); j++) {
                if (j == i) continue;
                const interval it = itv::toItv(ev.eval(terms[j].first), fT);
                if (it.isEmpty()) return false;
                mag += std::max(std::abs(it.lo()), std::abs(it.hi()));
            }
            if (!std::isfinite(mag)) return false;
            const double n     = double(terms.size());
            const double u     = itv::modelPrecision() == 2 ? std::ldexp(1.0, -53) : std::ldexp(1.0, -24);
            const double gamma = n * u / (1 - n * u);
            double       eps   = (3 * gamma * mag + n * std::ldexp(1.0, -125)) * (1 + std::ldexp(1.0, -20));
            // The plain form X - floor(X), X one term : the subtraction is exact (Sterbenz,
            // for X >= 0 and X <= -1 ; between, the result rounds within [0, 1]). The
            // only error left is a multiply-add contraction of the product that computes
            // X, taken exactly on one side and rounded inside floor : half an ulp of X.
            if (terms.size() == 2 && xs.size() == 1) {
                const bool product = isProduct(x);
                const double xmag  = std::max(std::abs(ix.lo()), std::abs(ix.hi()));
                eps = product ? u * xmag * (1 + std::ldexp(1.0, -20)) + std::ldexp(1.0, -125) : 0;
            }
            const bool   ok    = !ax.mayBeInvalid && std::isfinite(ix.lo()) && std::isfinite(ix.hi());

            AffItv acc = itv::fromItv(interval(rlo - eps, rhi + eps, std::min(ix.lsb(), -1), !ok));
            if (s > 0) acc = this->Neg(acc);  // round(X) - X = -(X - round(X))
            for (size_t j = 0; j < terms.size(); j++) {
                if (used[j]) continue;
                const AffItv v = ev.eval(terms[j].first);
                acc            = terms[j].second > 0 ? this->Add(acc, v) : this->Sub(acc, v);
            }
            result = acc;
            return true;
        }
        return false;
    }

    /// Cheap filter of the fractional rule, memoized : does the sum rooted at t hold a
    /// rounding (floor, rint or ceil) term ? The rule flattens a sum only when it does.
    bool hasRoundingTerm(Tree t) const
    {
        auto it = fHasRoundingTerm.find(t);
        if (it != fHasRoundingTerm.end()) return it->second;
        int  op;
        Tree a, b;
        bool r;
        tvec subs;
        if (isSigBinOp(t, &op, a, b) && (op == kAdd || op == kSub)) {
            r = hasRoundingTerm(a) || hasRoundingTerm(b);
        } else if (isSigSum(t, subs)) {
            r = false;
            for (Tree u : subs) r = r || hasRoundingTerm(u);
        } else if (negationOf(t, a)) {
            r = hasRoundingTerm(a);
        } else {
            r = roundingOf(t, a);
        }
        return fHasRoundingTerm[t] = r;
    }

    //--- the convex mix ---------------------------------------------------------------

    // A convex mix (1 - c) * A + c * B with c in [0, 1] lies between A and B : the
    // one-pole smoother y = (1 - p) * x + p * y' and every crossfade. The product of
    // two intervals forgets that both weights read the same c, and a smoother of a
    // control in [-12, 12] widened to [-2^30, 2^30]. The rule finds, in the sum
    // flattened into signed terms, two products whose weights are c and 1 - c (the
    // same tree c), and types them together : for a fixed c the mix is linear in c,
    // so its extremes over c are reached at the two ends of c's interval. Both ends
    // are computed in double ; a margin of 3 rounding errors of the largest operand
    // covers the program, which rounds 1 - c, the two products and the sum in its own
    // precision, at any value of c. The rule needs bounded A and B (an infinite
    // operand times a zero weight is a NaN).

    /// t1 is (1 - c) * A and t2 is c * B, the products flattened into factors (the normal
    /// form gathers constants : 440 * (pow(..) * (1 - c))) ; A and B are the remaining
    /// factors of each product
    static bool mixWeights(Tree t1, Tree t2, Tree& c, std::vector<Tree>& a, std::vector<Tree>& b)
    {
        std::vector<Tree> f1, f2;
        productFactors(t1, f1);
        productFactors(t2, f2);
        if (f1.size() < 2 || f2.size() < 2) return false;
        for (size_t i = 0; i < f1.size(); i++) {
            if (!isComplement(f1[i])) continue;
            for (size_t j = 0; j < f2.size(); j++) {
                if (!complementPair(f1[i], f2[j])) continue;
                c = f2[j];
                a.clear();
                b.clear();
                for (size_t m = 0; m < f1.size(); m++) {
                    if (m != i) a.push_back(f1[m]);
                }
                for (size_t m = 0; m < f2.size(); m++) {
                    if (m != j) b.push_back(f2[m]);
                }
                return true;
            }
        }
        return false;
    }

    /// the product of the factors' values
    AffItv productOf(const std::vector<Tree>& fs, FixPointEvaluator<AffItv>& ev) const
    {
        AffItv r = ev.eval(fs[0]);
        for (size_t i = 1; i < fs.size(); i++) r = this->Mul(r, ev.eval(fs[i]));
        return r;
    }

    /// the mix (1 - c) A + c B over c in ic, with the rounding of the program
    AffItv mixOf(const interval& ic, const AffItv& aa, const AffItv& ab) const
    {
        const interval ia = itv::toItv(aa, fT), ib = itv::toItv(ab, fT);
        // The exact mix at the two ends of c, computed in double : the weights are
        // nonnegative, so the extremes take the extreme operands. Its own rounding
        // (two products and a sum in double) is covered by a 2^-50 relative slack.
        double lo = HUGE_VAL, hi = -HUGE_VAL;
        for (double e : {ic.lo(), ic.hi()}) {
            const double w = 1 - e;
            lo             = std::min(lo, w * ia.lo() + e * ib.lo());
            hi             = std::max(hi, w * ia.hi() + e * ib.hi());
        }
        // The program computes 1 - c, two products and a sum in its own precision : at
        // most 3 rounding errors of the largest operand, once (the double slack covers
        // the exact ends, this margin covers the program and the values of c in between).
        const double mag = std::max({std::abs(ia.lo()), std::abs(ia.hi()), std::abs(ib.lo()), std::abs(ib.hi())});
        const double u   = itv::modelPrecision() == 2 ? std::ldexp(1.0, -53) : std::ldexp(1.0, -24);
        const double eps = (3 * u + std::ldexp(1.0, -50)) * mag + std::ldexp(1.0, -122);
        // the weights are nonnegative floats : a mix of nonnegative operands stays
        // nonnegative whatever the rounding (and symmetrically), so the margin never
        // crosses zero
        double rlo = lo - eps, rhi = hi + eps;
        if (ia.lo() >= 0 && ib.lo() >= 0) rlo = std::max(rlo, 0.0);
        if (ia.hi() <= 0 && ib.hi() <= 0) rhi = std::min(rhi, 0.0);
        const int lsb = std::min({ic.lsb(), ia.lsb(), ib.lsb()});
        // between its operands : a bound drifts where one of them moves past the horizon
        return itv::hullDrift(itv::fromItv(interval(rlo, rhi, lsb, aa.mayBeInvalid || ab.mayBeInvalid || ic.mayBeInvalid())),
                              {aa, ab});
    }

    /// a convex mix recognized in the sum sig, or nothing ; the remaining terms are added
    bool mixSum(Tree sig, FixPointEvaluator<AffItv>& ev, AffItv& result) const
    {
        std::vector<std::pair<Tree, int>> terms;
        sumTerms(sig, 1, terms);
        for (size_t i = 0; i < terms.size(); i++) {
            for (size_t j = 0; j < terms.size(); j++) {
                if (i == j || terms[i].second != terms[j].second) continue;
                Tree              c;
                std::vector<Tree> a, b;
                if (!mixWeights(terms[i].first, terms[j].first, c, a, b)) continue;
                const interval ic = itv::toItv(ev.eval(c), fT);
                if (ic.isEmpty() || ic.lo() < 0 || ic.hi() > 1) continue;
                const AffItv   aa = productOf(a, ev), ab = productOf(b, ev);
                const interval ia = itv::toItv(aa, fT), ib = itv::toItv(ab, fT);
                if (ia.isEmpty() || ib.isEmpty() || !ia.isBounded() || !ib.isBounded()) continue;
                AffItv acc = mixOf(ic, aa, ab);
                if (terms[i].second < 0) acc = this->Neg(acc);
                for (size_t k = 0; k < terms.size(); k++) {
                    if (k == i || k == j) continue;
                    const AffItv v = ev.eval(terms[k].first);
                    acc            = terms[k].second > 0 ? this->Add(acc, v) : this->Sub(acc, v);
                }
                result = acc;
                return true;
            }
        }
        return false;
    }

    /// The interpolation A + c * (B - A) : a sum of exactly two terms, A and a product whose
    /// last factor is the difference B - A, the weight c being the product of the other
    /// factors, computed first (a product associates from left to right). A is read twice,
    /// and the sum rule forgets it : for c in [0, 1] the value lies between A and B, the
    /// bound of mix (c, A, B), with the rounding of this very computation and its envelope.
    /// The library computes a mix from B when c is at least 1/2 (mixFromB) : the rule
    /// applies only below, where its model is the program's. The state of a TPT one-pole
    /// filter, s' = s + 2g * (x - s), is such an interpolation.
    bool interpolationSum(Tree sig, FixPointEvaluator<AffItv>& ev, AffItv& result) const
    {
        std::vector<std::pair<Tree, int>> terms;
        sumTerms(sig, 1, terms);
        if (terms.size() != 2) return false;
        for (int i = 0; i < 2; i++) {
            Tree a = terms[i].first, t = terms[1 - i].first;
            if (terms[i].second < 0 || terms[1 - i].second < 0) return false;
            // the product : its factors, the difference last
            std::vector<Tree> fs;
            int               op;
            Tree              x, y;
            tvec              subs;
            if (isSigProd(t, subs) && subs.size() >= 2) {
                fs.assign(subs.begin(), subs.end());
            } else if (isSigBinOp(t, &op, x, y) && op == kMul) {
                fs = {x, y};
            } else {
                continue;
            }
            Tree d = fs.back();
            fs.pop_back();
            std::vector<std::pair<Tree, int>> diff;
            sumTerms(d, 1, diff);
            if (diff.size() != 2) continue;
            Tree b = nullptr;
            for (int k = 0; k < 2; k++) {
                if (diff[k].first == a && diff[k].second < 0 && diff[1 - k].second > 0) b = diff[1 - k].first;
            }
            if (b == nullptr) continue;
            const AffItv   ac = productOf(fs, ev);
            const interval ic = itv::toItv(ac, fT);
            if (ic.isEmpty() || ic.lo() < 0 || ic.hi() > 1 || itv::mixFromB(ic)) continue;
            result = this->Mix(ac, ev.eval(a), ev.eval(b));
            return true;
        }
        return false;
    }

    /// Cheap filter of the mix rule, memoized : does the sum rooted at t hold a product
    /// with a factor 1 - c ?
    bool hasComplementTerm(Tree t) const
    {
        auto it = fHasComplementTerm.find(t);
        if (it != fHasComplementTerm.end()) return it->second;
        int  op;
        Tree a, b;
        bool r;
        tvec subs;
        if (isSigBinOp(t, &op, a, b) && (op == kAdd || op == kSub)) {
            r = hasComplementTerm(a) || hasComplementTerm(b);
        } else if (isSigSum(t, subs)) {
            r = false;
            for (Tree u : subs) r = r || hasComplementTerm(u);
        } else {
            r = hasComplementFactor(t);
        }
        return fHasComplementTerm[t] = r;
    }

    //--- select2 typed under its condition --------------------------------------------

    // A select2 whose condition compares a value with a constant guards one branch
    // with that comparison : select2(abs(t) < eps, t, 1) never divides by a t near
    // zero, select2(T60 > 0, 0, exp(-1/T60)) never reads the pole of a zero T60. The
    // join of the two branches forgets the guard. The rule types each branch under
    // its side of the condition : the constraint on the compared value is carried
    // backwards to the values it is computed from (through a product or a quotient
    // by a constant, a sum with a constant, abs), and the branch is evaluated again
    // with these refined values. The condition holds at the current sample only : the
    // evaluation never refines through a delay, a recursion or a table, which read
    // the past ; nor through integer arithmetic, which may wrap. A NaN fails every
    // comparison : the false side is refined only for a value that cannot be NaN.
    // Both branches are computed by the program whichever is chosen : the validity
    // alert stays the one of the unrefined branches.
    using Overrides = std::unordered_map<Tree, AffItv>;

    /// the next program value after k in the direction dir (integers step by one)
    static double step(double k, bool integer, double dir)
    {
        if (integer) return dir > 0 ? std::floor(k) + 1 : std::ceil(k) - 1;
        if (itv::modelPrecision() == 2) return std::nextafter(k, dir * HUGE_VAL);
        return double(std::nextafter(float(k), float(dir * HUGE_VAL)));
    }

    /// the values of L for which (L op k) has the given truth, or nothing (no refinement)
    static std::optional<interval> sideOf(int op, double k, bool truth, bool integer)
    {
        const double inf = HUGE_VAL;
        switch (op) {
            case kGT: return truth ? interval(step(k, integer, 1), inf) : interval(-inf, k);
            case kGE: return truth ? interval(k, inf) : interval(-inf, step(k, integer, -1));
            case kLT: return truth ? interval(-inf, step(k, integer, -1)) : interval(k, inf);
            case kLE: return truth ? interval(-inf, k) : interval(step(k, integer, 1), inf);
            case kEQ: if (truth) return interval(k, k); return std::nullopt;
            case kNE: if (!truth) return interval(k, k); return std::nullopt;
            default: return std::nullopt;
        }
    }

    static int mirror(int op)
    {
        switch (op) {
            case kGT: return kLT;
            case kLT: return kGT;
            case kGE: return kLE;
            case kLE: return kGE;
            default: return op;
        }
    }

    /// x such that x * k lies in n, for a float x : a relative margin covers the
    /// rounding of the product, and the sign survives it (a product by a nonzero k
    /// never changes sign, it may only underflow to zero)
    static interval inverseScale(const interval& n, double k)
    {
        double       lo = n.lo() / k, hi = n.hi() / k;
        if (k < 0) std::swap(lo, hi);
        const double m  = std::ldexp(1.0, -20);
        double       rl = lo - std::abs(lo) * m, rh = hi + std::abs(hi) * m;
        const double tiny = itv::modelPrecision() == 2 ? std::numeric_limits<double>::denorm_min()
                                                         : double(std::numeric_limits<float>::denorm_min());
        if (lo > 0) rl = std::max(rl, tiny);
        if (hi < 0) rh = std::min(rh, -tiny);
        return interval(rl, rh);
    }

    void narrowTo(Tree t, const interval& target, Overrides& ov, FixPointEvaluator<AffItv>& ev,
                  int depth) const
    {
        auto           known = ov.find(t);
        const AffItv   orig  = known != ov.end() ? known->second : ev.eval(t);
        const interval cur   = itv::toItv(orig, fT);
        if (cur.isEmpty()) return;
        interval n = itv::intersection(cur, interval(target.lo(), target.hi(), cur.lsb()));
        n          = interval(n.lo(), n.hi(), cur.lsb(), cur.mayBeInvalid());
        if (target.lo() > target.hi() || n.lo() > n.hi()) {
            ov[t] = itv::aempty();
            return;
        }
        // a bound the guard sets holds for all time ; one the value sets keeps its motion
        AffItv narrowed = itv::fromItv(n);
        narrowed.loDrifts = target.lo() < cur.lo() && itv::loFalls(orig);
        narrowed.hiDrifts = target.hi() > cur.hi() && itv::hiRises(orig);
        ov[t] = narrowed;
        if (depth >= 8 || integerValue(t, cur)) return;  // integer arithmetic may wrap
        int    op;
        Tree   x, y;
        double k;
        if (isSigBinOp(t, &op, x, y)) {
            if (op == kMul && constNum(y, k) && k != 0) narrowTo(x, inverseScale(n, k), ov, ev, depth + 1);
            if (op == kMul && constNum(x, k) && k != 0) narrowTo(y, inverseScale(n, k), ov, ev, depth + 1);
            if (op == kDiv && constNum(y, k) && k != 0 && std::isfinite(1 / k)) {
                narrowTo(x, inverseScale(n, 1 / k), ov, ev, depth + 1);
            }
            const double m = std::ldexp(1.0, -20);
            auto shifted = [m](double lo, double hi) {
                return interval(lo - std::abs(lo) * m - std::ldexp(1.0, -1000), hi + std::abs(hi) * m + std::ldexp(1.0, -1000));
            };
            if (op == kAdd && constNum(y, k)) narrowTo(x, shifted(n.lo() - k, n.hi() - k), ov, ev, depth + 1);
            if (op == kAdd && constNum(x, k)) narrowTo(y, shifted(n.lo() - k, n.hi() - k), ov, ev, depth + 1);
            if (op == kSub && constNum(y, k)) narrowTo(x, shifted(n.lo() + k, n.hi() + k), ov, ev, depth + 1);
            if (op == kSub && constNum(x, k)) narrowTo(y, shifted(k - n.hi(), k - n.lo()), ov, ev, depth + 1);
            return;
        }
        if (isSigProd(t) && twoFactors(t, x, y)) {
            // k * x as the normal form writes it : the same steps as the binary writing
            if (constNum(y, k) && k != 0) narrowTo(x, inverseScale(n, k), ov, ev, depth + 1);
            if (constNum(x, k) && k != 0) narrowTo(y, inverseScale(n, k), ov, ev, depth + 1);
            return;
        }
        if (int sign; isSigSum(t) && shiftOf(t, x, k, sign)) {
            // x + k, or k - x : the same steps as the binary writing
            const double m = std::ldexp(1.0, -20);
            auto shifted = [m](double lo, double hi) {
                return interval(lo - std::abs(lo) * m - std::ldexp(1.0, -1000), hi + std::abs(hi) * m + std::ldexp(1.0, -1000));
            };
            if (sign > 0) {
                narrowTo(x, shifted(n.lo() - k, n.hi() - k), ov, ev, depth + 1);
            } else {
                narrowTo(x, shifted(k - n.hi(), k - n.lo()), ov, ev, depth + 1);
            }
            return;
        }
        if (isSigNeg(t, x)) {
            narrowTo(x, interval(-n.hi(), -n.lo()), ov, ev, depth + 1);
            return;
        }
        if (absArg(t, x)) {
            // abs is the value itself on a nonnegative x, its opposite on a nonpositive
            // one ; otherwise the value or its opposite
            const interval ix = itv::toItv(ev.eval(x), fT);
            if (ix.isEmpty()) return;
            if (ix.lo() >= 0) {
                narrowTo(x, n, ov, ev, depth + 1);
            } else if (ix.hi() <= 0) {
                narrowTo(x, interval(-n.hi(), -n.lo()), ov, ev, depth + 1);
            } else {
                narrowTo(x, interval(-n.hi(), n.hi()), ov, ev, depth + 1);
            }
        }
    }

    /// the trees narrowTo may refine below v : the structure of the backward steps
    static void chainOf(Tree t, std::unordered_set<Tree>& keys, int depth)
    {
        keys.insert(t);
        if (depth >= 8) return;
        int    op;
        Tree   x, y;
        double k;
        if (isSigBinOp(t, &op, x, y)) {
            if ((op == kMul || op == kAdd) && constNum(y, k)) chainOf(x, keys, depth + 1);
            if ((op == kMul || op == kAdd) && constNum(x, k)) chainOf(y, keys, depth + 1);
            if ((op == kDiv || op == kSub) && constNum(y, k)) chainOf(x, keys, depth + 1);
            if (op == kSub && constNum(x, k)) chainOf(y, keys, depth + 1);
            return;
        }
        if (isSigProd(t) && twoFactors(t, x, y)) {
            if (constNum(y, k)) chainOf(x, keys, depth + 1);
            if (constNum(x, k)) chainOf(y, keys, depth + 1);
            return;
        }
        if (int sign; isSigSum(t) && shiftOf(t, x, k, sign)) {
            chainOf(x, keys, depth + 1);
            return;
        }
        if (isSigNeg(t, x)) {
            chainOf(x, keys, depth + 1);
            return;
        }
        if (absArg(t, x)) chainOf(x, keys, depth + 1);
    }

    /// Per compared value v, the structural part of a refinement : the trees a
    /// condition on v may refine, and which trees read them (memoized across rounds and
    /// shared by every select2 comparing v : the walk does not depend on the values).
    struct SelectReads {
        std::unordered_set<Tree>       keys;
        std::unordered_map<Tree, bool> reads;
    };
    mutable std::unordered_map<Tree, SelectReads> fSelectReads;

    /// does t read a refined value, through instantaneous operations only
    static bool readsRefined(Tree t, const std::unordered_set<Tree>& keys,
                             std::unordered_map<Tree, bool>& memo)
    {
        if (keys.count(t)) return true;
        auto it = memo.find(t);
        if (it != memo.end()) return it->second;
        bool r = false;
        int  op;
        Tree x, y, z, w;
        // the operations of the current sample : the binary ones, casts, select2, the
        // primitives, and the compound operations of the normal form (sum, product,
        // negation, remainders, tpt, mix) ; a FIR or an IIR reads the past and stops the walk
        const bool instantaneous = isSigBinOp(t, &op, x, y) || isSigIntCast(t, x) ||
                                   isSigFloatCast(t, x) || isSigSelect2(t, x, y, z) ||
                                   isSigSum(t) || isSigProd(t) || isSigNeg(t, x) || isSigFrac(t, x) ||
                                   isSigCfrac(t, x) || isSigTpt(t, x) || isSigMix(t, x, y, w) ||
                                   isSigPhase(t, x, y) ||
                                   getUserData(t) != nullptr;
        if (instantaneous) {
            for (int j = 0; j < t->arity() && !r; j++) r = readsRefined(t->branch(j), keys, memo);
        }
        memo[t] = r;
        return r;
    }

    AffItv evalUnder(Tree t, const Overrides& ov, FixPointEvaluator<AffItv>& ev,
                     SelectReads& sr, Overrides& memo) const
    {
        auto o = ov.find(t);
        if (o != ov.end()) return o->second;
        if (!readsRefined(t, sr.keys, sr.reads)) return ev.eval(t);
        auto m = memo.find(t);
        if (m != memo.end()) return m->second;
        std::vector<AffItv> kids;
        kids.reserve(t->arity());
        for (int j = 0; j < t->arity(); j++) kids.push_back(evalUnder(t->branch(j), ov, ev, sr, memo));
        // the refined children alone : the rules that read the evaluator directly
        // (fractional part, mix) are bypassed here, the generic rules are sound
        const AffItv v = itv::AffineOps<SignalAlgebra<AffItv>>::combine(t, kids, ev);
        memo[t]        = v;
        return v;
    }

    /// the intersection of two sound bounds of a value, as one constant interval over the
    /// horizon ; the first one when they are disjoint (none is then reached), invalid only
    /// when both may be
    AffItv meet(const AffItv& a, const AffItv& b) const
    {
        if (a.isEmpty() || b.isEmpty()) return a;
        const interval ia = itv::toItv(a, fT), ib = itv::toItv(b, fT);
        const double   lo = std::max(ia.lo(), ib.lo()), hi = std::min(ia.hi(), ib.hi());
        if (lo > hi) return a;
        AffItv r       = itv::meetDrift(itv::fromItv(interval(lo, hi, std::min(ia.lsb(), ib.lsb()))), a, b);
        r.mayBeInvalid = a.mayBeInvalid && b.mayBeInvalid;
        return r;
    }

    /// a comparison of a value with a number, asserted true (or false) by a guard
    struct Comparison {
        int    op;
        Tree   value;
        double k;
        bool   truth;
    };

    /// g is a guard, a value 0 or 1 : a comparison, a conjunction (& or a product) of
    /// guards, the negation 1 - c of a guard, or the float or the int of a guard ; the
    /// comparisons of a value with a number it asserts when it is 1 are added to cmps (the
    /// other ones hold too, but restrict nothing ; a negated conjunction asserts none)
    static bool guardOf(Tree g, std::vector<Comparison>& cmps, int depth, bool truth = true)
    {
        Tree   x, y, u;
        int    op;
        double k;
        tvec   fs;
        if (depth > 8) return false;
        if (isSigFloatCast(g, x) || isSigIntCast(g, x)) return guardOf(x, cmps, depth + 1, truth);
        // 1 - c : the negation of a guard c, true when c is false (an n-ary sum of the
        // normal form, or a binary subtraction)
        const bool negation = (isSigSum(g, fs) && fs.size() == 2 && constNum(fs[0], k) && k == 1 && isSigNeg(fs[1], u)) ||
                              (isSigBinOp(g, &op, x, y) && op == kSub && constNum(x, k) && k == 1 && (u = y));
        if (negation) {
            std::vector<Comparison> inner;
            if (!guardOf(u, inner, depth + 1, !truth)) return false;
            if (inner.size() == 1) cmps.push_back(inner[0]);  // a single comparison, negated
            return true;
        }
        // a conjunction : & of guards, or their product (1 only when every factor is 1) ;
        // negated, it asserts nothing about its factors
        if ((isSigBinOp(g, &op, x, y) && (op == kAND || op == kMul)) || isSigProd(g, fs)) {
            if (!isSigProd(g, fs)) fs = {x, y};
            std::vector<Comparison> inner;
            for (Tree f : fs) {
                if (!guardOf(f, inner, depth + 1, true)) return false;
            }
            if (truth) cmps.insert(cmps.end(), inner.begin(), inner.end());
            return true;
        }
        if (!isSigBinOp(g, &op, x, y) || op < kGT || op > kNE) return false;
        if (constNum(y, k)) {
            cmps.push_back({op, x, k, truth});
        } else if (constNum(x, k)) {
            cmps.push_back({mirror(op), y, k, truth});
        }
        return true;
    }

    /// A sum whose terms are multiplied by guards, typed in each case of its guards : a
    /// guard is 0 or 1 ; at 0 its term is 0 (or invalid, when the term may be) ; at 1 the
    /// comparisons it asserts hold, and the values they compare are restricted to their
    /// true side, in every term of the sum (the release of an envelope y * (1 - p * w)
    /// plus its attack [y < 1] * inc stays below 1 + inc). At most two guarded terms, the
    /// others read as values in [0, 1]. Nothing when the sum has no guarded term.
    bool guardedSum(Tree sig, FixPointEvaluator<AffItv>& ev, AffItv& result) const
    {
        struct Guarded {
            std::vector<Tree>       nodes;
            std::vector<Comparison> cmps;
        };
        std::vector<Guarded> gs;
        for (int i = 0; i < sig->arity() && gs.size() < 2; i++) {
            Tree t = sig->branch(i), u, a, b;
            int  op;
            if (isSigNeg(t, u)) t = u;
            tvec fs;
            if (!isSigProd(t, fs)) {
                if (isSigBinOp(t, &op, a, b) && op == kMul) {
                    fs = {a, b};
                } else {
                    continue;
                }
            }
            Guarded g;
            for (Tree f : fs) {
                std::vector<Comparison> cm;
                if (guardOf(f, cm, 0)) {
                    g.nodes.push_back(f);
                    g.cmps.insert(g.cmps.end(), cm.begin(), cm.end());
                }
            }
            if (!g.nodes.empty() && !g.cmps.empty()) gs.push_back(g);
        }
        if (gs.empty()) return false;
        // the trees the cases override : the guards, and the values a comparison restricts
        SelectReads sr;
        for (const Guarded& g : gs) {
            for (Tree n : g.nodes) sr.keys.insert(n);
            for (const Comparison& cm : g.cmps) chainOf(cm.value, sr.keys, 0);
        }
        const int m   = int(gs.size());
        AffItv    acc = itv::aempty();
        bool      any = false;
        for (int mask = 0; mask < (1 << m); mask++) {
            Overrides ov;
            bool      impossible = false;
            for (int j = 0; j < m && !impossible; j++) {
                const bool truth = (mask >> j) & 1;
                for (Tree n : gs[j].nodes) {
                    const int lsb = itv::toItv(ev.eval(n), fT).lsb();
                    ov[n]         = itv::fromItv(interval(truth, truth, lsb));
                }
                if (!truth) continue;
                for (const Comparison& cm : gs[j].cmps) {
                    const interval                iv   = itv::toItv(ev.eval(cm.value), fT);
                    const std::optional<interval> side = sideOf(cm.op, cm.k, cm.truth, integerValue(cm.value, iv));
                    if (!side || iv.isEmpty()) continue;
                    narrowTo(cm.value, *side, ov, ev, 0);
                    auto o = ov.find(cm.value);
                    if (o != ov.end() && itv::toItv(o->second, fT).isEmpty()) impossible = true;
                }
            }
            if (impossible) continue;  // this case never holds
            Overrides           memo;
            std::vector<AffItv> kids;
            kids.reserve(sig->arity());
            for (int i = 0; i < sig->arity(); i++) kids.push_back(evalUnder(sig->branch(i), ov, ev, sr, memo));
            const AffItv r = itv::AffineOps<SignalAlgebra<AffItv>>::combine(sig, kids, ev);
            acc            = any ? itv::ajoin(acc, r, fT) : r;
            any            = true;
        }
        if (!any) return false;
        result = acc;
        return true;
    }

    /// Bpf typed region by region : the expression of each region that x may reach,
    /// evaluated with x restricted to the range of the region (closed : a sound hull of the
    /// half-open range) ; a NaN x reaches the last region with x unrestricted
    bool regionBpf(Tree sig, FixPointEvaluator<AffItv>& ev, AffItv& result) const
    {
        Tree x;
        tvec t, rs;
        if (!isSigBpf(sig, x, t, rs) || rs.size() != t.size() + 1) return false;
        std::vector<double> th;
        for (Tree ti : t) {
            double k;
            if (!constNum(ti, k)) return false;
            th.push_back(k);
        }
        const AffItv   ax = ev.eval(x);
        const interval ix = itv::toItv(ax, fT);
        if (ix.isEmpty()) return false;
        // past the horizon, a moving x may reach regions it does not reach over [0, T]
        const interval fx    = itv::forever(ax, fT);
        bool           later = false;
        auto known = fSelectReads.find(x);
        if (known == fSelectReads.end()) {
            known = fSelectReads.emplace(x, SelectReads()).first;
            chainOf(x, known->second.keys, 0);
        }
        SelectReads& sr  = known->second;
        AffItv       acc;
        bool         any = false;
        for (size_t i = 0; i < rs.size(); i++) {
            const double lo   = (i == 0) ? -HUGE_VAL : th[i - 1];
            const double hi   = (i == th.size()) ? HUGE_VAL : th[i];
            const bool   last = (i == th.size());
            const bool   inRange = ix.hi() >= lo && ix.lo() < hi;
            later                = later || (!inRange && fx.hi() >= lo && fx.lo() < hi);
            AffItv       ri;
            bool         reached = false;
            if (inRange) {
                Overrides ov;
                narrowTo(x, interval(std::max(lo, ix.lo()), std::min(hi, ix.hi()), ix.lsb()), ov, ev, 0);
                Overrides memo;
                ri      = itv::toItv(ov[x], fT).isEmpty() ? itv::aempty() : evalUnder(rs[i], ov, ev, sr, memo);
                reached = !ri.isEmpty();
            }
            if (last && ix.mayBeInvalid()) {
                const AffItv u = ev.eval(rs[i]);
                ri             = reached ? itv::ajoin(ri, u, fT) : u;
                reached        = true;
            }
            if (!reached) continue;
            acc = any ? itv::ajoin(acc, ri, fT) : ri;
            any = true;
        }
        if (!any) return false;
        if (later) acc.loDrifts = acc.hiDrifts = true;
        result = acc;
        return true;
    }

    /// select2 typed under its condition, or nothing
    bool guardedSelect(Tree sig, const std::vector<AffItv>& c, FixPointEvaluator<AffItv>& ev,
                       AffItv& result) const
    {
        Tree sel, s0, s1, l, r;
        int  op;
        if (!isSigSelect2(sig, sel, s0, s1)) return false;
        // the int or the float of a comparison is the comparison, a value 0 or 1 (the
        // backends that convert a boolean condition explicitly, Cmajor)
        for (Tree x; isSigIntCast(sel, x) || isSigFloatCast(sel, x);) sel = x;
        if (!isSigBinOp(sel, &op, l, r) || op < kGT || op > kNE) return false;
        double k;
        Tree   v;
        if (constNum(r, k)) {
            v = l;
        } else if (constNum(l, k)) {
            v  = r;
            op = mirror(op);
        } else {
            return false;
        }
        const interval iv = itv::toItv(ev.eval(v), fT);
        if (iv.isEmpty()) return false;
        auto known = fSelectReads.find(v);
        if (known == fSelectReads.end()) {
            known = fSelectReads.emplace(v, SelectReads()).first;
            chainOf(v, known->second.keys, 0);
        }
        SelectReads& sr = known->second;
        AffItv branch[2];
        bool   refined = false;
        for (int truth = 0; truth < 2; truth++) {
            Tree                    s    = truth ? s1 : s0;
            std::optional<interval> side = sideOf(op, k, truth, integerValue(v, iv));
            if (!side || (!truth && iv.mayBeInvalid())) {
                branch[truth] = ev.eval(s);
                continue;
            }
            Overrides ov;
            narrowTo(v, *side, ov, ev, 0);
            if (itv::toItv(ov[v], fT).isEmpty()) {
                branch[truth] = itv::aempty();  // this side of the condition never holds
            } else {
                Overrides memo;
                branch[truth] = evalUnder(s, ov, ev, sr, memo);
            }
            refined = true;
        }
        if (!refined) return false;
        const bool invalid = c[0].mayBeInvalid || c[1].mayBeInvalid || c[2].mayBeInvalid;
        result             = itv::ajoin(branch[0], branch[1], fT).withInvalid(invalid);
        return true;
    }

    //--- the rotation oscillator ------------------------------------------------------

    // A rotation oscillator : a recursive pair v = (x, y) whose two bodies are
    //     x = r0 * ( cos(t) * x' + sin(t) * y') + input0
    //     y = r1 * (-sin(t) * x' + cos(t) * y') + input1
    // (os.oscrs, nlf2), cos and sin of the same tree t. A box cannot hold a circle : the
    // smallest box around a rotated box is up to sqrt(2) wider, and the fixpoint of the
    // two intervals runs away. The rule bounds the RADIUS |v| instead. In exact
    // arithmetic the rotation keeps it ; in the program, cos and sin are rounded (one
    // rounding error each, the libm being faithful), and so are the two products,
    // the sum and the addition of the input : the error of one step is at most
    // 8 u |v| (u the unit roundoff of the program), the radius grows at most by
    // rho = max(|r0|, |r1|) * (1 + 8u) per sample. With impulse inputs (k * (1 - 1'))
    // of norm A and no other input, |v_n| <= rho^n A. If rho < 1 (a damped resonator),
    // bounded inputs of norm U add at most U / (1 - rho). If rho >= 1 the bound holds
    // for a limited time : the rule certifies the oscillator until its radius may
    // have doubled, and records that duration when it is shorter than the horizon (a
    // single-precision oscillator : about 30 seconds at 48 kHz).
    struct Rotation {
        bool   ok = false;
        double radius = 0;  ///< bound of |x| and |y|
        bool   invalid = false;
        bool   moves = false;  ///< the bound holds for a limited time, or an input moves past the horizon
    };
    mutable std::unordered_map<Tree, Rotation> fRotations;  ///< per recursive group

    /// a coefficient : a constant times a symbolic factor (or none)
    struct Coef {
        double k = 1;
        Tree   f = nullptr;
    };

    /// the terms of a branch body : the scale r, the coefficient of x' and y', the inputs
    static bool linearBody(Tree body, Tree group, double& r, Coef coef[2], bool seen[2],
                           std::vector<std::pair<Tree, int>>& inputs)
    {
        int    op;
        Tree   a, b;
        double k;
        r          = 1;
        Tree inner = body;
        if (twoFactors(body, a, b) && constNum(b, k)) {
            r     = k;
            inner = a;
        } else if (twoFactors(body, a, b) && constNum(a, k)) {
            r     = k;
            inner = b;
        }
        std::vector<std::pair<Tree, int>> terms;
        sumTerms(inner, 1, terms);
        seen[0] = seen[1] = false;
        for (const auto& [t, sign] : terms) {
            std::vector<Tree> fs;
            productFactors(t, fs);
            int    which = -1;
            Coef   c;
            bool   simple = true;
            c.k           = sign;
            for (Tree f : fs) {
                Tree d, n, g, z, x;
                int  i;
                if (isSigDelay(f, d, n) && constNum(n, k) && k == 1 && isProj(d, &i, g) && g == group) {
                    if (which >= 0) return false;  // x' * y' : not linear
                    which = i;
                } else if (constNum(f, k)) {
                    c.k *= k;
                } else if ((isSigBinOp(f, &op, z, x) && op == kSub && constNum(z, k) && k == 0) ||
                           isSigNeg(f, x)) {
                    c.k = -c.k;  // 0 - s, or neg(s)
                    if (c.f) simple = false;
                    c.f = x;
                } else {
                    if (c.f) simple = false;
                    c.f = f;
                }
            }
            if (which < 0) {
                inputs.push_back({t, sign});
                continue;
            }
            if (which > 1 || seen[which] || !simple || !c.f) return false;
            seen[which] = true;
            coef[which] = c;
        }
        return seen[0] && seen[1];
    }

    /// k * (1 - 1') : an impulse of amplitude k
    static bool impulseAmplitude(Tree t, double& amp)
    {
        std::vector<Tree> fs;
        productFactors(t, fs);
        double k   = 1, v;
        bool   imp = false;
        for (Tree f : fs) {
            Tree b, d, n, x;
            if (isSigFloatCast(f, x)) f = x;  // float(1 - 1') is still the impulse
            tvec fir;
            double c0, c1;
            if (!imp && isSigFIR(f, fir) && fir.size() == 3 && constNum(fir[0], v) &&
                constNum(fir[1], c0) && constNum(fir[2], c1) && c1 == -c0) {
                k *= v * c0;  // FIR[v, c, -c] : c v (1 - 1'), the -fir form
                imp = true;
                continue;
            }
            if (constNum(f, v)) {
                k *= v;
            } else if (!imp && complementOf(f, b) && isSigDelay(b, d, n) && constNum(d, v) && v == 1 &&
                       constNum(n, v) && v == 1) {
                imp = true;
            } else {
                return false;
            }
        }
        amp = std::abs(k);
        return imp;
    }

    /// t reads the group : one of its projections is reachable from t, through any
    /// operation (a delay, a filter, another recursion)
    static bool readsGroup(Tree t, Tree group)
    {
        std::unordered_set<Tree> seen;
        std::vector<Tree>        todo{t};
        while (!todo.empty()) {
            Tree u = todo.back();
            todo.pop_back();
            if (u == group) return true;
            if (!seen.insert(u).second) continue;
            for (int j = 0; j < u->arity(); j++) todo.push_back(u->branch(j));
        }
        return false;
    }

    /// the closed bound of the rotation group, or nothing (ok false)
    Rotation rotationOf(Tree group, FixPointEvaluator<AffItv>& ev) const
    {
        Rotation rot;
        Tree     var, body;
        if (!isRec(group, var, body) || len(body) != 2) return rot;
        double                            r[2];
        Coef                              m[2][2];
        bool                              seen[2];
        std::vector<std::pair<Tree, int>> inputs[2];
        for (int i = 0; i < 2; i++) {
            if (!linearBody(nth(body, i), group, r[i], m[i], seen, inputs[i])) return rot;
        }
        // m[i][j] : coefficient of v_j' in branch i ; rotation : cos on the diagonal,
        // sin with opposite signs off it, the same angle everywhere
        Tree t0, t1, t2, t3;
        if (!primArg(m[0][0].f, sigs::g.gCosPrim, t0) || !primArg(m[1][1].f, sigs::g.gCosPrim, t1) ||
            !primArg(m[0][1].f, sigs::g.gSinPrim, t2) || !primArg(m[1][0].f, sigs::g.gSinPrim, t3)) {
            return rot;
        }
        if (t0 != t1 || t0 != t2 || t0 != t3) return rot;
        if (m[0][0].k != 1 || m[1][1].k != 1 || std::abs(m[0][1].k) != 1 || m[1][0].k != -m[0][1].k) {
            return rot;
        }
        double amp2 = 0, u2 = 0;
        bool   invalid = false;
        for (int i = 0; i < 2; i++) {
            // the flattened sum may have split an impulse k - k' into a constant k and a
            // constant delayed by one sample : they cancel from the second sample on
            double a = 0, uu = 0, cst = 0, late = 0;
            for (const auto& [t, sign] : inputs[i]) {
                double k;
                Tree   d, n;
                if (impulseAmplitude(t, k)) {
                    a += k;
                } else if (constNum(t, k)) {
                    cst += sign * k;
                } else if (isSigDelay(t, d, n) && constNum(n, k) && k == 1 && constNum(d, k)) {
                    late += sign * k;
                } else {
                    // an input is bounded apart from the oscillator : a term that reads the
                    // group again is part of the recursion, and the rotation alone no
                    // longer bounds the radius
                    if (readsGroup(t, group)) return rot;
                    const AffItv   v  = ev.eval(t);
                    const interval iv = itv::toItv(v, fT);
                    if (iv.isEmpty() || !iv.isBounded()) return rot;
                    invalid   = invalid || v.mayBeInvalid;
                    rot.moves = rot.moves || v.moving();
                    uu += std::max(std::abs(iv.lo()), std::abs(iv.hi()));
                }
            }
            if (cst + late == 0) {
                a += std::abs(cst);  // the impulse cst at the first sample, 0 after
            } else {
                uu += std::abs(cst) + std::abs(late);
            }
            amp2 += a * a;
            u2 += uu * uu;
        }
        const AffItv ct = ev.eval(t0);
        invalid         = invalid || ct.mayBeInvalid;
        const double u   = itv::modelPrecision() == 2 ? std::ldexp(1.0, -53) : std::ldexp(1.0, -24);
        const double rho = std::max(std::abs(r[0]), std::abs(r[1])) * (1 + 8 * u);
        const double A = std::sqrt(amp2) * (1 + u), U = std::sqrt(u2) * (1 + u);
        if (rho < 1) {
            rot.radius = A + U / (1 - rho);
        } else {
            if (U > 0) return rot;  // a driven undamped resonator grows even exactly
            rot.moves             = true;  // the radius may grow past the certified duration
            const double doubling = std::log(2.0) / std::log(rho);
            const double n        = std::min(doubling, fT);
            rot.radius            = A * std::pow(rho, n);
            if (doubling < fT) {
                std::string& reason = rotationReason();
                auto         known  = sigs::g.gCertifiedSamples.find(reason);
                if (known == sigs::g.gCertifiedSamples.end() || doubling < known->second) {
                    sigs::g.gCertifiedSamples[reason] = doubling;
                }
            }
        }
        rot.radius  = std::nextafter(rot.radius * (1 + std::ldexp(1.0, -40)), HUGE_VAL);
        rot.ok      = std::isfinite(rot.radius);
        rot.invalid = invalid;
        return rot;
    }

    /// the reason recorded with the certified duration
    static std::string& rotationReason()
    {
        static std::string single = "rounding drift of a rotation oscillator, in single precision";
        static std::string other  = "rounding drift of a rotation oscillator";
        return itv::programPrecision() == 1 ? single : other;
    }

    /// sig is a branch body of a rotation oscillator : its closed bound
    bool rotationBody(Tree sig, FixPointEvaluator<AffItv>& ev, AffItv& result) const
    {
        // find the group through a delayed projection among the terms
        std::vector<std::pair<Tree, int>> terms;
        Tree                              a, b;
        double                            k;
        Tree                              inner = sig;
        if (twoFactors(sig, a, b) && (constNum(a, k) || constNum(b, k))) {
            inner = constNum(a, k) ? b : a;
        }
        if (!isSum(inner)) return false;
        sumTerms(inner, 1, terms);
        Tree group = nullptr;
        for (const auto& [t, sign] : terms) {
            std::vector<Tree> fs;
            productFactors(t, fs);
            for (Tree f : fs) {
                Tree d, n, g;
                int  i;
                if (isSigDelay(f, d, n) && isProj(d, &i, g)) {
                    group = g;
                    break;
                }
            }
            if (group) break;
        }
        Tree var, body;
        if (!group || !isRec(group, var, body) || len(body) != 2) return false;
        if (nth(body, 0) != sig && nth(body, 1) != sig) return false;
        auto it = fRotations.find(group);
        if (it == fRotations.end()) it = fRotations.emplace(group, rotationOf(group, ev)).first;
        const Rotation& rot = it->second;
        if (!rot.ok) return false;
        result = itv::fromItv(interval(-rot.radius, rot.radius, -24, rot.invalid));
        if (rot.moves) result.loDrifts = result.hiDrifts = true;
        return true;
    }

    //--- the one-pole smoother and the accumulator of the -fir form -------------------

    // The one-pole smoother as an IIR, IIR[(1 - a) * A, a] : y(n) = (1 - a) A(n)
    // + a y(n-1), y(-1) = 0, a convex mix of A and of the previous output, so y stays
    // between 0 and the extremes of A. In the program each step adds at most 3 rounding
    // errors of its operands while the pole contracts the excess by 1 - a : the excess
    // stays below kappa = 3u / (1 - a - 3u) of the magnitude of A (a pole closer to 1
    // than 3u gives no bound).
    bool firstOrderMix(Tree sig, const std::vector<AffItv>& c, FixPointEvaluator<AffItv>& ev,
                       AffItv& result) const
    {
        if (c.size() != 2) return false;
        Tree              a = sig->branch(1);
        std::vector<Tree> fs;
        productFactors(sig->branch(0), fs);
        int found = -1;
        for (size_t i = 0; i < fs.size(); i++) {
            if (complementPair(fs[i], a)) {
                found = int(i);
                break;
            }
        }
        if (found < 0 || fs.size() < 2) return false;
        const interval ia = itv::toItv(c[1], fT);
        if (ia.isEmpty() || ia.lo() < 0 || ia.hi() >= 1) return false;
        // A : the product of the other factors of the input, evaluated directly
        interval iA;
        bool     first = true;
        AffItv   prod;
        for (size_t i = 0; i < fs.size(); i++) {
            if (int(i) == found) continue;
            const AffItv v = ev.eval(fs[i]);
            prod           = first ? v : this->Mul(prod, v);
            first          = false;
        }
        iA = itv::toItv(prod, fT);
        if (iA.isEmpty() || !iA.isBounded()) return false;
        const double u     = itv::modelPrecision() == 2 ? std::ldexp(1.0, -53) : std::ldexp(1.0, -24);
        const double room  = 1 - ia.hi() - 3 * u;
        if (!(room > 0)) return false;
        const double mag   = std::max(std::abs(iA.lo()), std::abs(iA.hi()));
        const double kappa = 3 * u / room * (1 + std::ldexp(1.0, -20));
        double       lo = std::min(iA.lo(), 0.0) - kappa * mag, hi = std::max(iA.hi(), 0.0) + kappa * mag;
        // y(n) = sum (1 - a) a^(n-k) A(k) holds at least its newest term (1 - a) A(n) : a
        // nonnegative A keeps y above (1 - a) min A from the first sample on (and
        // symmetrically), less the rounding of that term
        const double shrink = 1 - 4 * u;
        if (iA.lo() >= 0) lo = (1 - ia.hi()) * iA.lo() * shrink;
        if (iA.hi() <= 0) hi = (1 - ia.hi()) * iA.hi() * shrink;
        result = itv::fromItv(interval(lo, hi, std::min(iA.lsb(), ia.lsb()),
                                       prod.mayBeInvalid || c[0].mayBeInvalid || c[1].mayBeInvalid));
        // a smoothing of A : a bound drifts where A moves ; a moving pole may leave [0, 1)
        result = itv::hullDrift(result, {prod});
        if (c[1].moving()) result.loDrifts = result.hiDrifts = true;
        return true;
    }

    // The integer accumulator as an IIR, IIR[x, 1] : y(n) = x(n) + y(n-1), the
    // time counter among them. An exact integer sum of a constant x in [xl, xh] lies in
    // [xl (t+1), xh (t+1)] at time t : the affine corridor the recursive form gets, read
    // over the horizon and capped at the int32 range past its wrap date (toItv).
    bool integerAccumulator(Tree sig, const std::vector<AffItv>& c, AffItv& result) const
    {
        int k;
        if (c.size() != 2 || !isSigInt(sig->branch(1), &k) || k != 1) return false;
        const AffItv& x = c[0];
        // x constant for all time : a moving x is left to the other rules
        if (x.isEmpty() || x.moving() || x.lsb < 0 || !std::isfinite(x.a0) || !std::isfinite(x.b0)) {
            return false;
        }
        result      = x;
        result.a1   = x.a0;
        result.b1   = x.b0;
        result.lsb  = 0;
        // a sum that keeps adding a non null x leaves the int32 range one day : it may wrap
        result      = result.withOverflow(x.a0 < 0 || x.b0 > 0);
        return true;
    }

    //--- the compound operations : the operand seen ---------------------------------
    // The library bounds frac(x) and cfrac(x) with a margin of half an ulp of x : a
    // compiler may contract the product computing x with the subtraction, reading x
    // exactly on one side and rounded on the other. Seeing the tree, the margin goes
    // when no contraction can happen : x is not a real product, or a product by a
    // power of 2 (exact, so both readings agree) -- the scaled phase 2^30 (d - rint d)
    // of the fixed-point phasor. The result is then exactly within its range.
    static bool powerOfTwo(Tree t)
    {
        double v;
        if (!constNum(t, v) || v == 0 || !std::isfinite(v)) return false;
        int e;
        return std::frexp(std::abs(v), &e) == 0.5;
    }

    /// x may be a product a compiler contracts with the subtraction that follows
    bool contractible(Tree x, FixPointEvaluator<AffItv>& ev) const
    {
        Tree a, b;
        tvec fs;
        if (isSigProd(x, fs) && fs.size() > 2) {
            // the last product, (f0 * ... * fn-1) * fn, is the one a compiler contracts
            if (ev.eval(x).lsb >= 0) return false;
            return !powerOfTwo(fs.back());
        }
        if (!twoFactors(x, a, b)) return false;
        if (ev.eval(x).lsb >= 0) return false;  // integer arithmetic does not round
        return !(powerOfTwo(a) || powerOfTwo(b));
    }

    bool exactRemainder(Tree sig, const std::vector<AffItv>& c, FixPointEvaluator<AffItv>& ev,
                        AffItv& result) const
    {
        Tree x;
        bool frac = isSigFrac(sig, x);
        if (!frac && !isSigCfrac(sig, x)) return false;
        if (contractible(x, ev)) return false;
        result = itv::AffineOps<SignalAlgebra<AffItv>>::combine(sig, c, ev);
        if (result.isEmpty() || !result.isConst()) return true;
        const interval ix = itv::toItv(c[0], fT);
        double         lo = -0.5, hi = 0.5;
        if (frac) {
            lo = 0;
            hi = 1;
            if (!ix.isEmpty() && ix.lo() >= 0) {
                hi = itv::programPrecision() == 1 ? double(std::nextafter(1.0f, 0.0f))
                     : itv::modelPrecision() == 2 ? std::nextafter(1.0, 0.0)
                                                    : 1.0;
            }
        }
        result.a0 = std::max(result.a0, lo);
        result.b0 = std::min(result.b0, hi);
        return true;
    }

    //--- the rules, in order ----------------------------------------------------------

    AffItv combine(Tree sig, const std::vector<AffItv>& c,
                   FixPointEvaluator<AffItv>& ev) const override
    {
        // The rules that see more than one node at a time (the dependency problem),
        // each one sound on its own ; a node they do not recognize gets the
        // library's rule.
        AffItv r;
        if (exactRemainder(sig, c, ev, r)) return r;
        if (guardedSelect(sig, c, ev, r)) return r;
        if (isSigBpf(sig) && regionBpf(sig, ev, r)) return r;
        if (rotationBody(sig, ev, r)) return r;
        if (isSigIIR(sig) && firstOrderMix(sig, c, ev, r)) return r;
        if (isSigIIR(sig) && integerAccumulator(sig, c, r)) return r;
        if (isSigIIR(sig)) return iirBound(sig, c);
        // a mix computed from the weight t of its complement c = 1 - t (mixForm.hh) : the
        // interval of that computation
        if (Tree mc, ma, mb, t; isSigMix(sig, mc, ma, mb) && c.size() == 3 &&
                                mixFromWeight(mc, itv::toItv(c[0], fT), t)) {
            const AffItv at = ev.eval(t);
            AffItv       r  = itv::hullDrift(itv::fromItv(fItv.MixOfComplement(itv::toItv(at, fT), itv::toItv(c[1], fT),
                                                                         itv::toItv(c[2], fT))),
                                             {c[1], c[2]});
            // a moving weight may leave [0, 1] past the horizon
            if (at.moving()) r.loDrifts = r.hiDrifts = true;
            return r;
        }
        // a sum typed in the cases of its guards, and by the sum rules : two sound bounds,
        // intersected
        AffItv     guarded;
        const bool hasGuards = isSum(sig) && guardedSum(sig, ev, guarded);
        if (isSum(sig) && hasRoundingTerm(sig) && fractionalSum(sig, ev, r)) return hasGuards ? meet(r, guarded) : r;
        if (isSum(sig) && hasComplementTerm(sig) && mixSum(sig, ev, r)) return hasGuards ? meet(r, guarded) : r;
        if (isSum(sig) && interpolationSum(sig, ev, r)) {
            r = meet(r, itv::AffineOps<SignalAlgebra<AffItv>>::combine(sig, c, ev));
            return hasGuards ? meet(r, guarded) : r;
        }
        if (hasGuards) return meet(guarded, itv::AffineOps<SignalAlgebra<AffItv>>::combine(sig, c, ev));
        // A table generated at init : its content is the generator over n samples
        {
            Tree size, gen, wi, ws, content;
            int  n;
            if (isSigWRTbl(sig, size, gen, wi, ws) && isSigGen(gen, content) && !isSigWaveform(content) &&
                isSigInt(size, &n) && c.size() == 4) {
                const AffItv g = tableContent(sig, content, n);
                if (!g.isEmpty()) return this->WRTbl(c[0], g, c[2], c[3]);
            }
        }
        // A table read : the library cannot certify it (the table extent is not part
        // of the value), the compiler can. Promotion clamps every index it does not
        // prove within [0, size-1] by exact integer reasoning (sigPromotion), so the
        // read returns an element of the table : the read is valid when the table and
        // the index are (an index that may be NaN or overflow is not).
        Tree tbl, ri, size, gen, wi, ws;
        if (isSigRDTbl(sig, tbl, ri) && isSigWRTbl(tbl, size, gen, wi, ws)) {
            // A read at a constant index of a table filled by a literal waveform is that
            // element : the waveform is the generator, its value at time k is element k
            // (cyclically), and a read-only table keeps it. The join of all the elements
            // made the difference of two neighbours of an interpolation contain zero.
            Tree           w;
            const interval ix = itv::toItv(c[1], fT);
            if (wi == ::nil() && isSigGen(gen, w) && isSigWaveform(w) && w->arity() > 0 &&
                !ix.isEmpty() && ix.lo() == ix.hi() && ix.lo() >= 0 && ix.lsb() >= 0 &&
                !c[1].mayBeInvalid) {
                const int k = int(ix.lo()) % w->arity();
                return ev.eval(w->branch(k)).withInvalid(c[0].mayBeInvalid);
            }
            AffItv r       = itv::AffineOps<SignalAlgebra<AffItv>>::combine(sig, c, ev);
            r.mayBeInvalid = c[0].mayBeInvalid || c[1].mayBeInvalid;
            return r;
        }
        return itv::AffineOps<SignalAlgebra<AffItv>>::combine(sig, c, ev);
    }

    //--- the IIR : two sound bounds, intersected ---------------------------------------
    // IIR[nil, x, 0, C1, ..., Cn] : y = x + sum C_k y@k. Its certified gain (the intervals'
    // Iir) bounds a stable filter with constant coefficients ; its definition, iterated as
    // the fixpoint of a recursive group (probe, ascending Kleene with widening,
    // narrowing), gives the bound the recursion had before the reveal. Both enclose the
    // values of the program : so does their intersection, never worse than either.
    AffItv iirDefinition(Tree sig, const AffItv& x, const std::vector<AffItv>& cs) const
    {
        auto step = [&](const AffItv& y) {
            AffItv acc = x;
            for (size_t k = 0; k < cs.size(); k++) {
                const AffItv& ck = cs[k];
                if (!ck.moving() && ck.a0 == 0 && ck.b0 == 0 && !ck.mayBeInvalid) continue;
                acc = this->Add(acc, this->Mul(ck, this->Delay(y, this->IntNum(int(k) + 1))));
            }
            return acc;
        };
        fExtrapolation.erase(sig);  // the widening state of this node, afresh
        // the probe : the first seed of the ladder that the definition maps into itself
        bool   certified = false;
        AffItv probed    = bottom(sig);
        for (const AffItv& s : probeSeeds(sig)) {
            const AffItv f = step(s);
            if (probeLessEqual(f, s)) {
                certified = true;
                probed    = f;
                for (int n = 0; n < maxNarrowingIterations(); n++) {
                    const AffItv g = step(probed);
                    const bool   d = converged(probed, g);
                    probed         = g;
                    if (d) break;
                }
                break;
            }
        }
        recordProbe(sig, probed, certified);
        // the ascending pass, widened beyond widenAfter, then narrowed
        AffItv y    = bottom(sig);
        bool   done = false;
        for (int it = 1; !done && it <= maxIterations(); it++) {
            AffItv f = step(y);
            if (it > widenAfter()) f = widen(sig, y, f);
            done = converged(y, f);
            y    = f;
        }
        if (!done) return top(sig);
        for (int n = 0; n < maxNarrowingIterations(); n++) {
            const AffItv g = step(y);
            const bool   d = converged(y, g);
            y              = g;
            if (d) break;
        }
        return y;
    }

    AffItv iirBound(Tree sig, const std::vector<AffItv>& c) const
    {
        const std::vector<AffItv> cs(c.begin() + 1, c.end());
        const AffItv              gain = this->Iir(c[0], cs);
        const AffItv              def  = iirDefinition(sig, c[0], cs);
        if (gain.isEmpty() || def.isEmpty()) return itv::aempty();
        const interval ig = itv::toItv(gain, fT), id = itv::toItv(def, fT);
        const bool     gb = ig.isBounded(), db = id.isBounded();
        // the recursion may wrap when either reading says so
        const bool overflow = gain.mayOverflow || def.mayOverflow;
        if (!gb && !db) return def.withInvalid(gain.mayBeInvalid && def.mayBeInvalid).withOverflow(overflow);
        if (!gb) return def.withOverflow(overflow);
        if (!db) return gain.withOverflow(overflow);
        // both bounded : their intersection ; NaN only when both allow it
        const double lo = std::max(ig.lo(), id.lo()), hi = std::min(ig.hi(), id.hi());
        AffItv       r  = (ig.hi() - ig.lo() <= id.hi() - id.lo()) ? gain : def;
        if (lo <= hi) r = itv::meetDrift(itv::fromItv(interval(lo, hi, std::min(ig.lsb(), id.lsb()))), gain, def);
        r.mayBeInvalid = gain.mayBeInvalid && def.mayBeInvalid;
        return r.withOverflow(overflow);
    }

    /// defaultParams: parameters held at their DEFAULT values (nominal reading) instead
    /// of their full declared ranges (worst case). Buttons and checkboxes read released.
    explicit HorizonAlgebra(bool defaultParams = false)
        : itv::AffineOps<SignalAlgebra<AffItv>>(horizonFromEnv(), defaultParams)
    {
    }

    /// The same analysis over a horizon of the given number of samples
    HorizonAlgebra(double horizon, bool defaultParams)
        : itv::AffineOps<SignalAlgebra<AffItv>>(horizon, defaultParams)
    {
    }

    void setExact(const ExactSolvers* exact) { fExact = exact; }

    /// t is an integer value : its nature when the exact attributes are known, its lsb
    /// otherwise (a probe seed has the lsb of an integer, whatever its variable)
    bool integerValue(Tree t, const interval& i) const
    {
        if (fExact) return fExact->nature(t) == kInt;
        return i.lsb() >= 0;
    }

    /// The content of a table of n elements filled at init by the generator gen : the
    /// generator runs n samples from its own initial state (it is compiled apart, with its
    /// own recursions), so its values are those of a separate analysis over its samples 0
    /// to n - 1 (the horizon is the last sample), collapsed to one constant interval. A generator shares its nodes with the
    /// program (the time counter IIR[1, 1] is one node) : the separate analysis keeps their
    /// intervals over the program's horizon as they are. Empty when it does not apply.
    AffItv tableContent(Tree table, Tree gen, int n) const
    {
        auto it = fTableContent.find(table);
        if (it != fTableContent.end()) return it->second;
        AffItv r = itv::aempty();
        if (n > 0 && double(n - 1) < fT) {
            HorizonAlgebra           sub(double(n - 1), fDefaults);
            sub.setExact(fExact);
            FixPointIterator<AffItv> iter(getRecPlan(gen), sub);
            const AffItv             g = iter.value(gen);
            if (!g.isEmpty()) {
                r              = itv::fromItv(itv::toItv(g, double(n - 1)));
                r.mayBeInvalid = g.mayBeInvalid;
            }
        }
        fTableContent[table] = r;
        return r;
    }

    //--- the lattice ------------------------------------------------------------------
    AffItv bottom(Tree) const override { return itv::aempty(); }
    /// unknown : any value of the nature of var, and possibly an invalid execution (a
    /// NaN, an integer division by zero) -- without the alert, the fallback would claim
    /// a validity that nothing proved
    AffItv top(Tree var) const override
    {
        if (fExact && fExact->nature(var) == kInt) {
            return itv::fromItv(interval(-2147483648.0, 2147483647.0, 0, true));
        }
        return itv::fromItv(interval(-HUGE_VAL, HUGE_VAL, -24, true));
    }
    bool   lessEqual(const AffItv& x, const AffItv& y) const override
    {
        return itv::aleq(x, y, fT);
    }
    // a probe seed claims a bound over [0, T] : its image keeps its own drifts
    bool probeLessEqual(const AffItv& x, const AffItv& y) const override
    {
        return itv::aleqWithin(x, y, fT);
    }
    bool converged(const AffItv& prev, const AffItv& cur) const override
    {
        return itv::aleq(cur, prev, fT);  // stationary OR descending stops
    }
    AffItv project(Tree, int i, const std::vector<AffItv>& row) const override
    {
        return row[i];  // the interval is a value attribute
    }

    int widenAfter() const override { return 8; }
    int maxNarrowingIterations() const override { return 3; }
    int maxIterations() const override { return 1000; }

    //--- probe: a ladder of magnitudes, positivity seed first at each rung ------------
    // The first certified seed is the threshold : a ladder (1, 16, 256 ... 2^28, then
    // 2^30) finds a bound within a factor 16 for a slowly contracting recursion (a
    // smoother whose pole is a few ulps below 1), that a single 2^30 seed would leave
    // at 2^30 : the narrowing steps cannot descend from it. Each rung also tries a seed
    // bounded above only, [-inf, m] : an accumulator that stops growing in float but may
    // decrease without bound (a max bounds it below afterwards).
    std::vector<AffItv> probeSeeds(Tree) const override
    {
        const int           lsb = 0;
        std::vector<AffItv> seeds;
        for (int e = 0; e <= 28; e += 4) {
            const double m = std::ldexp(1.0, e);
            seeds.push_back(itv::fromItv(interval(0, m, lsb)));
            seeds.push_back(itv::fromItv(interval(-m, m, lsb)));
            seeds.push_back(itv::fromItv(interval(-HUGE_VAL, m, lsb)));
        }
        seeds.push_back(itv::fromItv(interval(0, kBig, lsb)));
        seeds.push_back(itv::fromItv(interval(-kBig, kBig, lsb)));
        return seeds;
    }
    void recordProbe(Tree var, const AffItv& probed, bool certified) const override
    {
        fProbe[var] = {probed, certified};
    }

    // Widening: a certified rate-0 probe threshold absorbs the move; otherwise the
    // numeric two-stage awiden (rate proposal, then escalation to the world's top).
    AffItv widen(Tree var, const AffItv& old, const AffItv& fresh) const override
    {
        if (old.isEmpty() || fresh.isEmpty()) return fresh;
        const bool wlo = fresh.lo(0) < old.lo(0) || fresh.lo(fT) < old.lo(fT);
        const bool whi = fresh.hi(0) > old.hi(0) || fresh.hi(fT) > old.hi(fT);
        if (!wlo && !whi) return fresh;

        // A contracting recursion (a smoother, a leaky integrator) approaches its
        // bound geometrically and never settles in a handful of rounds. Before the
        // probe threshold or the escalation, guess the limit of each moving bound : the
        // fixed point of the secant through the last two (iterate, image) pairs, plus a
        // margin, when the secant contracts (slope below 1) ; a relative jump, when the
        // bound only creeps by a few rounding errors. A bound that grows for real (an
        // accumulator) is left to the rate proposal below, which dates it.
        // The guess is only a guess : the iteration goes on from it, and stops there
        // only if it is a post-fixpoint (F(guess) within the guess), which is what makes
        // the result sound. A guess that fails gives way to the rules below.
        if (fresh.isConst() && old.isConst() && std::isfinite(fresh.a0) && std::isfinite(fresh.b0)) {
            Extrapolation& h = fExtrapolation[var];
            if (h.rounds < kExtrapolationRounds) {
                const bool   first = h.rounds == 0 || h.old.isEmpty() || !h.old.isConst() || !h.fresh.isConst();
                const AffItv po = h.old, pf = h.fresh;
                h.old           = old;
                h.fresh         = fresh;
                ++h.rounds;
                if (first) return fresh;
                const double mag = std::max({std::abs(fresh.a0), std::abs(fresh.b0), std::ldexp(1.0, -60)});
                // x0 -> f0 and x1 -> f1 : the bound's image, dir = +1 for hi, -1 for lo ;
                // NAN when the secant does not contract
                bool contracting = true;
                const double ladder = mag * std::ldexp(1.0, 6 * h.rounds - 18);  // 2^-6, 1, 2^6
                auto guess = [mag, ladder, &contracting](double x0, double f0, double x1, double f1, double dir) {
                    const double move = (f1 - x1) * dir;
                    if (!(move > 0)) return f1;
                    if (x1 != x0) {
                        const double slope = (f1 - f0) / (x1 - x0);
                        if (slope >= 0 && slope < 1) {
                            const double l    = x1 + (f1 - x1) / (1 - slope);
                            const double jump = std::max((l - f1) * dir, 0.0) + std::abs(l) * std::ldexp(1.0, -20) +
                                                mag * std::ldexp(1.0, -40) + move;
                            return std::nextafter(f1 + dir * jump, dir * HUGE_VAL);
                        }
                    }
                    // a creep of a few rounding errors per round (a smoother whose pole
                    // is a few ulps below 1) gets a relative jump, larger at each round ;
                    // a real growth (an accumulator) is left to the rate proposal
                    if (move <= mag * std::ldexp(1.0, -16)) {
                        return std::nextafter(f1 + dir * (ladder + 16 * move), dir * HUGE_VAL);
                    }
                    contracting = false;
                    return f1;
                };
                AffItv r = fresh;
                if (whi) r.b0 = std::max(fresh.b0, guess(po.b0, pf.b0, old.b0, fresh.b0, 1));
                if (wlo) r.a0 = std::min(fresh.a0, guess(po.a0, pf.a0, old.a0, fresh.a0, -1));
                // never beyond a certified probe threshold that already holds the image
                auto pt = fProbe.find(var);
                if (pt != fProbe.end() && pt->second.second && pt->second.first.isConst()) {
                    const AffItv&  p = pt->second.first;
                    const interval f = itv::toItv(fresh, fT);
                    if (!p.isEmpty() && p.a0 <= f.lo() && f.hi() <= p.b0) {
                        r.a0 = std::max(r.a0, p.a0);
                        r.b0 = std::min(r.b0, p.b0);
                    }
                }
                if (contracting && std::isfinite(r.a0) && std::isfinite(r.b0)) return r;
            }
        }

        auto it = fProbe.find(var);
        if (it != fProbe.end() && it->second.second && fresh.isConst() && old.isConst()) {
            const AffItv&  p = it->second.first;
            const interval f = itv::toItv(fresh, fT);
            if (!p.isEmpty() && p.isConst() && p.a0 <= f.lo() && f.hi() <= p.b0) {
                AffItv r = fresh;
                if (wlo) r.a0 = p.a0;
                if (whi) r.b0 = p.b0;
                r.lsb = std::min(fresh.lsb, p.lsb);
                return r;
            }
        }
        return itv::awiden(old, fresh, fT);
    }

    //--- signal-language-only constructors --------------------------------------------
    AffItv Table(const AffItv&, const AffItv& content) const override { return content; }
    AffItv DocConstantTbl(const AffItv&, const AffItv& init) const override
    {
        return init;
    }
    AffItv DocWriteTbl(const AffItv&, const AffItv& init, const AffItv&,
                       const AffItv&) const override
    {
        return init;
    }
    AffItv DocAccessTbl(const AffItv& tbl, const AffItv&) const override { return tbl; }
    AffItv Register(int, const AffItv& s) const override { return s; }
};

//----------------------------------------------------------------------------------------
// The report: date every rate-carrying accumulator.
//----------------------------------------------------------------------------------------

std::string fmtSamples(double s)
{
    std::ostringstream o;
    if (!std::isfinite(s)) {
        o << "jamais";
        return o.str();
    }
    const double sec = s / 48000.0;  // display convention: 48 kHz
    o.precision(3);
    if (sec < 60) {
        o << sec << " s";
    } else if (sec < 3600) {
        o << sec / 60 << " min";
    } else if (sec < 86400) {
        o << sec / 3600 << " h";
    } else {
        o << sec / 86400 << " j";
    }
    o << " @48kHz (" << std::scientific << s << " samples)";
    return o.str();
}

/// One dated pass over the recursive variables with a given parameter policy.
std::pair<std::vector<HorizonEvent>, double> datePass(const RecPlan& plan,
                                                      HorizonAlgebra& algebra, bool verbose,
                                                      const char* tag)
{
    FixPointIterator<AffItv> it(plan, algebra);

    std::vector<HorizonEvent> events;
    double                    horizon = -1;
    const double              INF     = HUGE_VAL;

    for (const std::vector<Tree>& comp : plan.components()) {
        for (Tree var : comp) {
            const std::vector<AffItv>& row = it.variableValue(var);
            for (int b = 0; b < static_cast<int>(row.size()); ++b) {
                const AffItv& v = row[b];
                if (v.isEmpty() || (v.a1 == 0 && v.b1 == 0)) continue;
                if (!std::isfinite(v.a0) || !std::isfinite(v.b0)) continue;

                HorizonEvent e;
                {
                    std::ostringstream name;
                    name << ppsig(proj(b, var), 30);
                    e.signal = name.str();
                }
                e.rate = std::max(std::fabs(v.a1), std::fabs(v.b1));

                // int32 wrap: the growing bound reaches the int range's edge
                e.wrapAt = INF;
                if (v.lsb >= 0) {
                    if (v.b1 > 0) e.wrapAt = std::min(e.wrapAt, (2147483647.0 - v.b0) / v.b1);
                    if (v.a1 < 0) e.wrapAt = std::min(e.wrapAt, (-2147483648.0 - v.a0) / v.a1);
                }

                // float absorption: |value| reaches 2^p * increment, the add is absorbed
                e.absorb32At = INF;
                e.absorb53At = INF;
                if (v.lsb < 0) {
                    auto absorb = [&](double p) {
                        double t = INF;
                        if (v.b1 > 0) t = std::min(t, p - v.b0 / v.b1);
                        if (v.a1 < 0) t = std::min(t, p - v.a0 / v.a1);
                        return std::max(0.0, t);
                    };
                    e.absorb32At = absorb(16777216.0);          // 2^24
                    e.absorb53At = absorb(9007199254740992.0);  // 2^53
                }

                const double first = std::min(e.wrapAt, e.absorb32At);
                if (horizon < 0 || first < horizon) horizon = first;

                if (verbose) {
                    std::cerr << "HORIZON " << tag << " : rate " << e.rate << "/sample";
                    if (e.wrapAt != INF) std::cerr << ", int32 wrap at " << fmtSamples(e.wrapAt);
                    if (e.absorb32At != INF) {
                        std::cerr << ", float absorption at " << fmtSamples(e.absorb32At)
                                  << " (double : " << fmtSamples(e.absorb53At) << ")";
                    }
                    std::cerr << " : " << e.signal << std::endl;
                }
                events.push_back(std::move(e));
            }
        }
    }
    return {std::move(events), horizon};
}

}  // namespace

HorizonReport horizonAnalysis(Tree L, bool verbose)
{
    const RecPlan& plan = getRecPlan(L);

    // Worst case: parameters anywhere in their declared ranges.
    HorizonAlgebra worst(/*defaultParams*/ false);
    auto [wev, wt] = datePass(plan, worst, verbose, "pire-cas");

    // Nominal: parameters at their default values, buttons released.
    HorizonAlgebra nominal(/*defaultParams*/ true);
    auto [nev, nt] = datePass(plan, nominal, verbose, "defaults ");

    HorizonReport report;
    report.events                = std::move(wev);
    report.horizonSamples        = wt;
    report.horizonDefaultSamples = nt;
    report.defaultEventCount     = int(nev.size());

    if (verbose) {
        auto line = [](const char* tag, double t, std::size_t n) {
            std::cerr << "HORIZON T* " << tag << " : ";
            if (n == 0) {
                std::cerr << "no dated accumulator (exact semantics, no limit)";
            } else {
                std::cerr << fmtSamples(t) << " (" << n << " dated accumulator(s))";
            }
            std::cerr << std::endl;
        };
        line("(pire-cas)", wt, report.events.size());
        line("(defaults) ", nt, std::size_t(report.defaultEventCount));
    }
    return report;
}

//----------------------------------------------------------------------------------------
// HorizonReader: the horizon-bounded interval of any signal, for the shadow and roles
// reports. toItv caps integer chains at the int32 range past their wrap date.
//----------------------------------------------------------------------------------------

struct HorizonReader::Impl {
    const RecPlan&           plan;  ///< shared, memoized (getRecPlan)
    HorizonAlgebra           algebra;
    FixPointIterator<AffItv> it;

    Impl(Tree L, const ExactSolvers* exact, bool lazy)
        : plan(getRecPlan(L)), algebra(/*defaultParams*/ false), it(plan, algebra, lazy)
    {
        algebra.setExact(exact);
    }
};

HorizonReader::HorizonReader(Tree L, const ExactSolvers* exact, bool lazy)
    : fImpl(new Impl(L, exact, lazy))
{
}

HorizonReader::~HorizonReader()
{
    delete fImpl;
}

itv::interval HorizonReader::at(Tree sig) const
{
    // each bound says whether it holds for all time or over the horizon only
    return itv::hullWithMotion(fImpl->it.value(sig), fImpl->algebra.horizon());
}
