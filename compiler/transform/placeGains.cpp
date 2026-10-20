/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2026 GRAME, Centre National de Creation Musicale
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

#include "placeGains.hh"

#include <optional>
#include <unordered_map>
#include <unordered_set>

#include "aterm.hh"
#include "global.hh"
#include "mterm.hh"
#include "rewrite.hh"
#include "signals.hh"
#include "sigs-state.hh"

namespace {

// the trees the rules of the current pass produced : a sum is written again only when one
// of its own terms is one of them
std::unordered_set<Tree>* gPlaced = nullptr;

Tree placed(Tree t)
{
    gPlaced->insert(t);
    return t;
}

// x as gain * rest : the gain, the factors of order 1 or less with the coefficient ; the
// rest, the other factors
void splitGain(Tree x, mterm& gain, mterm& rest)
{
    const mterm m(x);
    gain = mterm(m.coefficient());
    rest = mterm(1);
    for (const auto& p : m.factors()) {
        mterm& dst = (sigs::sigOrder(p.first) <= 1) ? gain : rest;
        for (int k = 0; k < p.second; k++) {
            dst *= p.first;
        }
        for (int k = 0; k > p.second; k--) {
            dst /= p.first;
        }
    }
}

bool isUnit(const mterm& m)
{
    return m.factors().empty() && isOne(m.coefficient());
}

// g * t, written as the normal form writes a product
Tree times(const mterm& g, Tree t)
{
    mterm m(g);
    m *= t;
    return m.normalizedTree();
}

// the coefficients of a FIR multiplied by the number k, its source replaced by x : each
// coefficient written as the gathering of the taps writes it (writeFirs)
Tree scaledFIR(Tree k, Tree x, const tvec& fir)
{
    tvec v{x};
    for (size_t j = 1; j < fir.size(); j++) {
        if (isZero(fir[j]) || isOne(k)) {
            v.push_back(fir[j]);
            continue;
        }
        aterm a;
        a += sigMul(k, fir[j]);
        v.push_back(a.normalizedTree());
    }
    return sigFIR(v);
}

// IRM(g*x; c) is g*IRM(x; c), x a signal : a constant input (all gain) stays, since a
// recursion of a constant is not the scaled recursion of 1 in the precision of the code
// (a float accumulator stalls where a count by 1 would not)
Tree placeIRM(Tree x, Tree c)
{
    mterm gain, rest;
    splitGain(x, gain, rest);
    if (isUnit(gain) || isUnit(rest)) {
        return sigIRM(x, c);
    }
    Tree irm = sigIRM(rest.normalizedTree(), c);
    return times(gain, irm);
}

// the weight w of the input of an IIR of order 1 of coefficient c : c = 1 - w
bool inputWeight(Tree c, Tree& w)
{
    tvec fs;
    return isSigSum(c, fs) && fs.size() == 2 && isOne(fs[0]) && isSigNeg(fs[1], w);
}

Tree ruleAux(Tree orig, Tree rebuilt);

Tree rule(Tree orig, Tree rebuilt)
{
    Tree r = ruleAux(orig, rebuilt);
    return (r != rebuilt) ? placed(r) : r;
}

// 1 - c as the normal form writes it : t when c is 1 - t
Tree complementOf(Tree c)
{
    tvec ws;
    Tree x;
    if (isSigSum(c, ws) && ws.size() == 2 && isOne(ws[0]) && isSigNeg(ws[1], x)) {
        return x;
    }
    aterm complement(sigReal(1.0));
    complement -= c;
    return complement.normalizedTree();
}

Tree ruleAux(Tree orig, Tree rebuilt)
{
    if (Tree c, a, b; isSigMix(rebuilt, c, a, b)) {
        // mix(c, 1, b) is mix(1 - c, b, 1), and mix(c, a, 1) = a + c - a c is symmetric :
        // the weight is the first of a and c in the order of the normal form
        if (isOne(a) && !isOne(b)) {
            c = complementOf(c);
            a = b;
            b = sigReal(1.0);
        }
        if (isOne(b) && !isNum(a) && !isNum(c) && NormalFormTreeLess()(a, c)) {
            std::swap(a, c);
        }
        // mix(c, a, b) = mix(1 - c, b, a) : one orientation, its operands in the order of
        // the normal form, whatever the writing (after the reveals, which read the mixes
        // in the orientation they were built in)
        if (NormalFormTreeLess()(b, a)) {
            Tree cc = complementOf(c);
            Tree bb = b;
            b       = a;
            a       = bb;
            c       = cc;
        }
        Tree m = sigMix(c, a, b);
        return (m == rebuilt) ? rebuilt : m;
    }
    if (Tree x, c; isSigIRM(rebuilt, x, c)) {
        return placeIRM(x, c);
    }
    if (tvec v; isSigIIR(rebuilt, v)) {
        // as for the IRM, a constant input stays
        mterm gain, rest;
        splitGain(v[0], gain, rest);
        if (isUnit(gain) || isUnit(rest)) {
            return rebuilt;
        }
        v[0]     = rest.normalizedTree();
        Tree iir = sigIIR(v);
        return times(gain, iir);
    }
    if (tvec v; isSigFIR(rebuilt, v)) {
        // the number into the coefficients, the other gains to the output
        mterm gain, rest;
        splitGain(v[0], gain, rest);
        if (isUnit(gain)) {
            return rebuilt;
        }
        Tree        k   = gain.coefficient();
        const mterm gs  = gain / mterm(k);
        Tree        src = rest.normalizedTree();
        Tree        fir = scaledFIR(k, src, v);
        return isUnit(gs) ? fir : times(gs, fir);
    }
    if (Tree a, b; isSigProd(rebuilt) || isSigMul(rebuilt, a, b)) {
        const mterm m(rebuilt);
        // the factor of power 1 that is a FIR, or an IIR of order 1, when it is the only one
        Tree fir = nullptr, iir = nullptr;
        int  nfir = 0, niir = 0;
        for (const auto& p : m.factors()) {
            tvec v;
            if (p.second == 1 && isSigFIR(p.first, v)) {
                fir = p.first;
                nfir++;
            } else if (p.second == 1 && isSigIIR(p.first, v) && v.size() == 2) {
                iir = p.first;
                niir++;
            }
        }
        Tree k = m.coefficient();
        if (nfir == 1 && !isOne(k) && !isZero(k)) {
            // k * FIR(x; b) is FIR(x; k*b)
            tvec v;
            isSigFIR(fir, v);
            Tree  scaled = scaledFIR(k, v[0], v);
            mterm others = m / mterm(fir);
            others /= mterm(k);
            others *= scaled;
            return others.normalizedTree();
        }
        if (niir == 1) {
            // g * IIR(x; 1 - w) with g = q * w, q a gain : q * IRM(x; 1 - w)
            tvec v;
            isSigIIR(iir, v);
            Tree w;
            if (inputWeight(v[1], w) && w->isRecFree()) {
                const mterm g = m / mterm(iir);
                const mterm mw(w);
                if (mw.isNotZero() && !mw.factors().empty() && g.hasDivisor(mw)) {
                    const mterm q = g / mw;
                    bool        gain = true;
                    for (const auto& p : q.factors()) {
                        gain = gain && sigs::sigOrder(p.first) <= 1;
                    }
                    if (gain) {
                        Tree irm = placeIRM(v[0], v[1]);
                        return times(q, irm);
                    }
                }
            }
        }
        return rebuilt;
    }
    if (tvec terms; isSigSum(rebuilt, terms) && rebuilt != orig) {
        // one of its terms was placed : the sum written again, the contributions of a
        // source gathered
        for (Tree t : terms) {
            Tree x;
            if (gPlaced->count(t) || (isSigNeg(t, x) && gPlaced->count(x))) {
                return aterm(rebuilt).normalizedTree();
            }
        }
    }
    return rebuilt;
}

}  // namespace

Tree placeGains(Tree L)
{
    std::unordered_map<Tree, Tree> memo;
    std::unordered_set<Tree>       placedTrees;
    gPlaced = &placedTrees;

    auto pre     = [](Tree) -> std::optional<Tree> { return std::nullopt; };
    auto defRule = [](Tree, Tree rebuilt) -> Tree { return rebuilt; };
    auto r       = [](Tree orig, Tree rebuilt) -> Tree { return rule(orig, rebuilt); };

    Tree res = treeRewritePairedMemo(L, pre, r, memo, defRule);
    gPlaced  = nullptr;
    return res;
}
