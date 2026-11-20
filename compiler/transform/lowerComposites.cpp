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

#include "lowerComposites.hh"

#include <cmath>
#include <unordered_set>
#include <vector>

#include "computeSignals.hh"
#include "definitionIndex.hh"
#include "global.hh"
#include "irm_weight.hh"
#include "mixForm.hh"
#include "rewrite.hh"
#include "sigtype.hh"
#include "typedAttributes.hh"
#include "xtended.hh"

namespace {

bool isComposite(Tree t)
{
    Tree    x, y, z;
    bool    b;
    MixForm mf;
    IrmForm rf;
    return isCfMix(t, x, y, z, mf) || isCfPhase(t, x, y, b) || isCfFrac(t, x, b) || isSigCfrac(t, x) ||
           isSigTpt(t, x) || (isCfIrm(t, x, y, rf) && (rf == IrmForm::kWeighted || rf == IrmForm::kFromState));
}

/// a node the arithmetic of the typed attributes does not type (a rounding, a remainder, a
/// conversion) : the given nature, the rate and the other attributes of its operands, read
/// in the source program
Tree typed(Tree t, int nature, const tvec& operands)
{
    if (isNum(t) || (t->getType() != nullptr && !getSigType(t)->hasDeferredInterval())) {
        return t;  // a node of the program, or a number (completeTypes) : its type stands
    }
    int v = 0, c = 0, vec = 0, b = 0;
    for (Tree o : operands) {
        Type to = getCertifiedSigType(o);
        v |= to->variability();
        c |= to->computability();
        vec |= to->vectorability();
        b |= to->boolean();
    }
    setSigType(t, makeSimpleType(nature, v, c, vec, b, itv::interval(-HUGE_VAL, HUGE_VAL)));
    return t;
}

/// the subterm h of the source program, on the operands of the rewritten one : the same
/// operation, xs its operands rebuilt (h reads the operands of the compound node)
Tree onOperands(Tree h, const tvec& xs)
{
    int  op;
    Tree x, y;
    if (isSigBinOp(h, &op, x, y)) {
        faustassert(xs.size() == 2);
        return sigBinOp(op, xs[0], xs[1]);
    }
    return tree(h->node(), xs);
}

/// x + 1 as the program writes it in h (Sum(x, 1), Sum(1, x), x + 1 or 1 + x), on x rebuilt
Tree plusOneOn(Tree h, Tree x)
{
    tvec subs;
    int  op;
    Tree a, b;
    if (isSigSum(h, subs)) {
        return isOne(subs[1]) ? sigSum({x, subs[1]}) : sigSum({subs[0], x});
    }
    faustassert(isSigBinOp(h, &op, a, b) && op == kAdd);
    return isOne(b) ? sigAdd(x, b) : sigAdd(a, x);
}

}  // namespace

Tree lowerComposites(Tree L, std::unordered_map<Tree, Tree>* image)
{
    // a rewrite rebuilds the recursions with fresh variables : none without a compound node
    bool any = false;
    {
        std::unordered_set<Tree> seen;
        std::vector<Tree>        work{L};
        while (!work.empty() && !any) {
            Tree t = work.back();
            work.pop_back();
            if (!seen.insert(t).second) {
                continue;
            }
            Tree var, body;
            if (isRec(t, var, body)) {
                if (body != nullptr) {
                    work.push_back(body);
                }
                continue;
            }
            for (int i = 0; i < t->arity(); i++) {
                work.push_back(t->branch(i));
            }
            any = isComposite(t);
        }
    }
    if (!any) {
        if (image != nullptr) {
            image->clear();
        }
        return L;
    }

    DefinitionIndex defs;
    defs.build(L);
    std::unordered_map<Tree, Tree> memo;
    auto rule = [&](Tree orig, Tree rebuilt) -> Tree {
        Tree    c, a, b, x, p, xo, po;
        MixForm form;
        bool    flag;
        if (isCfMix(rebuilt, c, a, b, form)) {
            if (form == MixForm::kFromWeight) {
                // c written 1 - t : b + t * (a - b), 1 - t never computed
                Tree t;
                faustassert(mixComplementOf(c, t));
                Tree d = sigSub(a, b);
                Tree m = sigMul(t, d);
                return sigAdd(b, m);
            }
            if (form == MixForm::kFromB) {
                // b + (1 - c) * (a - b), 1 - c exact when c >= 1/2
                Tree one = sigReal(1.0);
                Tree w   = sigSub(one, c);
                Tree d   = sigSub(a, b);
                Tree m   = sigMul(w, d);
                return sigAdd(b, m);
            }
            Tree d = sigSub(b, a);
            Tree m = sigMul(c, d);
            return sigAdd(a, m);
        }
        if (isCfPhase(rebuilt, x, p, flag)) {
            isCfPhase(orig, xo, po, flag);
            const bool isInt = getCertifiedSigType(xo)->nature() == kInt && getCertifiedSigType(po)->nature() == kInt;
            Tree       r;
            if (Tree held = defs.remOf(xo, po)) {
                // the program's own remainder (a counter, ba.period)
                r = onOperands(held, {x, p});
            } else if (isInt) {
                r = sigBinOp(kRem, x, p);
            } else {
                r = tree(gGlobal->gFmodPrim->symbol(), x, p);
            }
            r = typed(r, isInt ? kInt : kReal, {xo, po});
            if (!isInt) {
                return sigDiv(r, p);
            }
            Tree fr = typed(sigFloatCast(r), kReal, {xo, po});
            Tree fp = typed(sigFloatCast(p), kReal, {po});
            if (flag) {
                // a product by 1 / p, computed at the rate of p (phaseByReciprocal)
                Tree one = sigReal(1.0);
                Tree inv = sigDiv(one, fp);
                return sigMul(fr, inv);
            }
            return sigDiv(fr, fp);
        }
        if (isCfFrac(rebuilt, x, flag) || isSigCfrac(rebuilt, x)) {
            const bool cfrac = isSigCfrac(rebuilt, x);
            Tree       xs;
            if (cfrac) {
                isSigCfrac(orig, xs);
            } else {
                bool approx;
                isCfFrac(orig, xs, approx);
            }
            Tree held = cfrac ? defs.rintOf(xs) : defs.floorOf(xs);
            Tree r;
            if (held != nullptr) {
                // the program's own rounding of x
                r = onOperands(held, {x});
            } else {
                xtended* round = cfrac ? gGlobal->gRintPrim : (flag ? gGlobal->gFloorApproxPrim : gGlobal->gFloorPrim);
                r              = tree(round->symbol(), x);
            }
            r = typed(r, getCertifiedSigType(orig)->nature(), {xs});
            return sigSub(x, r);
        }
        if (IrmForm irmf; isCfIrm(rebuilt, x, p, irmf)) {
            if (irmf == IrmForm::kWeighted) {
                // u + p * y@1, u = (1 - p) * x : 1 - p from p rounded, even when p is
                // written 1 - w (for p in [1/2, 1], 1 - p is exact)
                Tree one = sigReal(1.0);
                Tree w   = sigSub(one, p);
                Tree u   = sigMul(w, x);
                return cfIrm(u, p, IrmForm::kWeightedInput);
            }
            if (irmf == IrmForm::kFromState) {
                // y@1 + w * (x - y@1), w read as it is when p is written 1 - w
                Tree w = irmInputWeight(p);
                if (w == nullptr) {
                    Tree one = sigReal(1.0);
                    w        = sigSub(one, p);
                }
                return cfIrm(x, w, IrmForm::kFromStateWeight);
            }
            return rebuilt;
        }
        if (isSigTpt(rebuilt, x)) {
            isSigTpt(orig, xo);
            Tree d;
            if (Tree held = defs.plusOneOf(xo)) {
                d = plusOneOn(held, x);  // the program's own x + 1
            } else {
                Tree one = sigReal(1.0);
                d        = sigAdd(x, one);
            }
            return sigDiv(x, d);
        }
        return rebuilt;
    };
    // the node written out has the value of its source : its type, the interval the reads of
    // the node take (a min or a max of it, an integer conversion), even on a tree an earlier
    // stage of the program had typed otherwise
    auto typedRule = [&](Tree orig, Tree rebuilt) -> Tree {
        Tree r = rule(orig, rebuilt);
        if (r != rebuilt) {
            setSigType(r, getSigType(orig));
        }
        return r;
    };
    Tree r = treeRewritePaired(L, typedRule, memo);
    completeTypes(r, memo);
    if (image != nullptr) {
        *image = memo;
    }
    return r;
}
