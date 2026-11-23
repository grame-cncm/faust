/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.
 ************************************************************************
 ************************************************************************/

#include "narrowIntegers.hh"

#include <algorithm>
#include <cmath>
#include <unordered_set>
#include <vector>

#include "global.hh"
#include "interval.hh"
#include "rewrite.hh"
#include "sigtype.hh"
#include "typedAttributes.hh"
#include "xtended.hh"

namespace {

/// the integers every real of the program's precision holds exactly, within the int32
/// range : 2^24 in single precision, the int32 range in double and quad
double exactBound()
{
    return (gGlobal->gFloatSize == 1) ? 16777216.0 : 2147483647.0;
}

/// a bound that holds at every sample, of a value that is never a NaN
bool firm(const itv::interval& i)
{
    return i.isValid() && !i.loMoves() && !i.hiMoves();
}

double magnitude(const itv::interval& i)
{
    return std::max(std::fabs(i.lo()), std::fabs(i.hi()));
}

bool isMinMax(Tree t, bool& isMin)
{
    xtended* p = (xtended*)sigXtendedData(t);
    if (t->arity() != 2 || (p != gGlobal->gMinPrim && p != gGlobal->gMaxPrim)) {
        return false;
    }
    isMin = (p == gGlobal->gMinPrim);
    return true;
}

/// a value the program reads from outside : its interval is a convention the program
/// enforces after the read (-rui), or none, never a bound of the value read
bool isExternal(Tree t)
{
    int  i;
    Tree l, init, lo, hi, st, sf, chan, part, ridx;
    return isSigHSlider(t, l, init, lo, hi, st) || isSigVSlider(t, l, init, lo, hi, st) ||
           isSigNumEntry(t, l, init, lo, hi, st) || isSigButton(t, l) || isSigCheckbox(t, l) ||
           isSigInput(t, &i) || isSigSoundfileBuffer(t, sf, chan, part, ridx);
}

/// max(lo, min(hi, w)), w read from outside, lo and hi numbers : the clamp of a control
/// (-rui), whose bounds hold after it only, NaN included
bool isClampOfExternal(Tree t)
{
    bool isMin, innerMin;
    if (!isMinMax(t, isMin)) {
        return false;
    }
    for (int k = 0; k < 2; k++) {
        Tree inner = t->branch(1 - k);
        if (isNum(t->branch(k)) && isMinMax(inner, innerMin) && innerMin != isMin) {
            for (int j = 0; j < 2; j++) {
                if (isNum(inner->branch(j)) && isExternal(inner->branch(1 - j))) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool atSampleRate(Tree t)
{
    return getCertifiedSigType(t)->variability() == kSamp;
}

/// the rewriting of a conversion to int, built on the rewritten operands : the memo of the
/// rewrite gives the image of every node of the source below the conversion. Planned first,
/// on the source, building no tree : the serial numbers of the trees order the emission, and
/// a tree built for a rewriting not kept would reorder the code of the whole program
class Narrowing {
    const std::unordered_map<Tree, Tree>& fMemo;
    const double                          fBound = exactBound();
    bool                                  fPlan    = false;  ///< t stands for every node to build
    int                                   fRemoved = 0;      ///< conversions at the sample rate removed
    int                                   fBuilt   = 0;      ///< conversions to int at the sample rate built

    Tree image(Tree t) const
    {
        auto it = fMemo.find(t);
        return (it == fMemo.end()) ? t : it->second;
    }

    /// r, an integer node built of the operands of the source node t, of interval i : the
    /// other attributes of t
    static Tree typedAs(Tree r, Tree t, const itv::interval& i)
    {
        if (isNum(r) || (r->getType() != nullptr && !getSigType(r)->hasDeferredInterval())) {
            return r;  // a number, or a node of the program : its type stands
        }
        Type ty = getCertifiedSigType(t);
        setSigType(r, makeSimpleType(kInt, ty->variability(), ty->computability(), ty->vectorability(),
                                     ty->boolean(), i));
        return r;
    }

    /// r, an integer node standing for the source node t : the interval of int(t)
    static Tree typedAs(Tree r, Tree t)
    {
        return typedAs(r, t, gAlgebra.IntCast(getCertifiedSigType(t)->getInterval()));
    }

    /// every partial result of an exact sum or product of the lifted operands lies in
    /// [-B, B] : their magnitudes summed, or multiplied
    bool exactOperation(const tvec& xs, bool product) const
    {
        double m = product ? 1.0 : 0.0;
        for (Tree x : xs) {
            const itv::interval i = getCertifiedSigType(x)->getInterval();
            if (!firm(i)) {
                return false;
            }
            m = product ? m * std::max(1.0, magnitude(i)) : m + magnitude(i);
        }
        return m <= fBound;
    }

   public:
    explicit Narrowing(const std::unordered_map<Tree, Tree>& memo) : fMemo(memo) {}

    /// k, an integer node with float(k) = t exactly ; nullptr when there is none
    Tree lift(Tree t)
    {
        double r;
        int    op;
        Tree   x, y;
        tvec   xs;
        bool   isMin;
        if (isSigReal(t, &r)) {
            if (r != std::floor(r) || std::fabs(r) > fBound) {
                return nullptr;
            }
            return fPlan ? t : sigInt(int(r));
        }
        if (isSigFloatCast(t, x)) {
            const itv::interval i = getCertifiedSigType(x)->getInterval();
            if (getCertifiedSigType(x)->nature() != kInt || !firm(i) || magnitude(i) > fBound) {
                return nullptr;
            }
            fRemoved += atSampleRate(t) ? 1 : 0;
            return image(x);
        }
        if (isMinMax(t, isMin)) {
            Tree a = lift(t->branch(0));
            if (a == nullptr) {
                return nullptr;
            }
            Tree b = lift(t->branch(1));
            if (b == nullptr) {
                return nullptr;
            }
            return fPlan ? t : typedAs(isMin ? sigMin(a, b) : sigMax(a, b), t);
        }
        if (isSigBinOp(t, &op, x, y) && (op == kAdd || op == kSub || op == kMul)) {
            if (!exactOperation({x, y}, op == kMul)) {
                return nullptr;
            }
            Tree a = lift(x);
            if (a == nullptr) {
                return nullptr;
            }
            Tree b = lift(y);
            if (b == nullptr) {
                return nullptr;
            }
            return fPlan ? t : typedAs(sigBinOp(op, a, b), t);
        }
        if (isSigSum(t, xs)) {
            // the sum of the code, from left to right
            if (!exactOperation(xs, false)) {
                return nullptr;
            }
            Tree          s = nullptr;
            itv::interval si;
            for (Tree u : xs) {
                Tree a = lift(u);
                if (a == nullptr) {
                    return nullptr;
                }
                if (fPlan) {
                    continue;
                }
                const itv::interval ui = getCertifiedSigType(u)->getInterval();
                if (s == nullptr) {
                    s  = a;
                    si = ui;
                } else {
                    si = gAlgebra.Add(si, ui);
                    s  = typedAs(sigAdd(s, a), t, gAlgebra.IntCast(si));
                }
            }
            return fPlan ? t : s;
        }
        if (isSigNeg(t, x)) {
            Tree a = lift(x);
            if (a == nullptr) {
                return nullptr;
            }
            if (fPlan) {
                return t;
            }
            Tree zero = sigInt(0);
            return typedAs(sigSub(zero, a), t);
        }
        return nullptr;
    }

    /// an integer node equal to int(t) ; nullptr when there is none
    Tree push(Tree t)
    {
        const int removed = fRemoved;
        if (Tree k = lift(t)) {
            return k;
        }
        fRemoved              = removed;  // the conversions of a lift that failed stay
        const itv::interval i = getCertifiedSigType(t)->getInterval();
        if (!firm(i)) {
            return nullptr;
        }
        bool isMin;
        if (isMinMax(t, isMin) && !isClampOfExternal(t)) {
            Tree a = push(t->branch(0));
            if (a == nullptr) {
                return nullptr;
            }
            Tree b = push(t->branch(1));
            if (b == nullptr) {
                return nullptr;
            }
            return fPlan ? t : typedAs(isMin ? sigMin(a, b) : sigMax(a, b), t);
        }
        // the conversion stays, on a value where it is defined, computed by the program
        if (isExternal(t) || i.lo() < -2147483648.0 || i.hi() > 2147483647.0) {
            return nullptr;
        }
        double r;
        if (isSigReal(t, &r)) {
            return fPlan ? t : sigInt(int(r));
        }
        fBuilt += atSampleRate(t) ? 1 : 0;
        return fPlan ? t : typedAs(sigIntCast(image(t)), t);
    }

    /// int(x), the source node conv : rewritten when the rewriting leaves fewer conversions
    /// at the sample rate ; no tree built
    bool narrows(Tree conv, Tree x)
    {
        fPlan    = true;
        fRemoved = atSampleRate(conv) ? 1 : 0;
        fBuilt   = 0;
        Tree r   = push(x);
        fPlan    = false;
        return r != nullptr && fBuilt < fRemoved;
    }

    /// the rewriting of int(x), the source node conv, that narrows
    Tree narrow(Tree x)
    {
        Tree r = push(x);
        faustassert(r != nullptr);
        return r;
    }
};

/// a conversion to int of L narrows
bool anyNarrows(Tree L, Narrowing& narrowing)
{
    std::unordered_set<Tree> seen;
    std::vector<Tree>        work{L};
    while (!work.empty()) {
        Tree t = work.back();
        work.pop_back();
        if (!seen.insert(t).second) {
            continue;
        }
        Tree var, body, x;
        if (isRec(t, var, body)) {
            if (body != nullptr) {
                work.push_back(body);
            }
            continue;
        }
        if (isSigIntCast(t, x) && getCertifiedSigType(x)->nature() == kReal && narrowing.narrows(t, x)) {
            return true;
        }
        for (int i = 0; i < t->arity(); i++) {
            work.push_back(t->branch(i));
        }
    }
    return false;
}

}  // namespace

Tree narrowIntegers(Tree L, std::unordered_map<Tree, Tree>* image)
{
    // a rewrite rebuilds the recursions with fresh variables : none without a conversion
    // that narrows
    std::unordered_map<Tree, Tree> memo;
    Narrowing                      narrowing(memo);
    if (gGlobal->gFloatSize < 1 || gGlobal->gFloatSize > 3 || !anyNarrows(L, narrowing)) {
        if (image != nullptr) {
            image->clear();
        }
        return L;
    }
    auto                           rule = [&](Tree orig, Tree rebuilt) -> Tree {
        Tree x;
        if (!isSigIntCast(orig, x) || getCertifiedSigType(x)->nature() != kReal || !narrowing.narrows(orig, x)) {
            return rebuilt;
        }
        // a node built is typed by its operation, a node of the program keeps its type
        return narrowing.narrow(x);
    };
    Tree r = treeRewritePaired(L, rule, memo);
    completeTypes(r, memo);
    if (image != nullptr) {
        *image = memo;
    }
    return r;
}
