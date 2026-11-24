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

#include "computeForm.hh"

#include <cstdlib>
#include <iostream>
#include <unordered_set>

#include "code_container.hh"
#include "approxRound.hh"
#include "computeSignals.hh"
#include "decisionCone.hh"
#include "global.hh"
#include "xtended.hh"
#include "definitionIndex.hh"
#include "irmErrorForm.hh"
#include "irm_weight.hh"
#include "mixForm.hh"
#include "ppsig.hh"
#include "sigtransform.hh"
#include "exactWeights.hh"
#include "factorSums.hh"
#include "families.hh"
#include "reciprocals.hh"
#include "shareSums.hh"
#include "slowPrefixes.hh"
#include "lowerComposites.hh"
#include "narrowIntegers.hh"
#include "sigtyperules.hh"
#include "timing.hh"
#include "typedAttributes.hh"

namespace {

/// The translation : the operations whose code the certification decides, with their
/// decision ; every other one rebuilt as it is
class Translation : public TransformAlgebra {
    Tree                              fProgram;  ///< for the cone of the decisions
    mutable std::unordered_set<Tree>  fCone;
    mutable bool                      fConeBuilt = false;

    /// sig may reach a decision (decisionCone.hh, with the discontinuities)
    bool reachesDecision(Tree sig) const
    {
        if (!fConeBuilt) {
            fCone      = decisionCone(fProgram, /*discontinuities*/ true);
            fConeBuilt = true;
        }
        return fCone.count(sig) > 0;
    }

    /// mix(c, a, b) : from the weight when c is written 1 - t (mixForm.hh), from b when c
    /// may be near 1, from a otherwise
    static MixForm mixForm(Tree c)
    {
        const itv::interval ic = getCertifiedSigType(c)->getInterval();
        if (Tree t; mixFromWeight(c, ic, t)) {
            return MixForm::kFromWeight;
        }
        return itv::mixFromB(ic) ? MixForm::kFromB : MixForm::kFromA;
    }

    /// IRM(x; p) : in single precision, a slow smoother written by its error, which reaches
    /// its target, even where the node reaches a decision (irmErrorForm.hh) ; the weighted
    /// sum when the source wrote the pole, and for a pole written 1 - w with a slow target
    /// and pole unless the node reaches a decision ; otherwise the interpolation from x when
    /// p may be below 1/2, from the state when not
    IrmForm irmForm(Tree sig, Tree x, Tree p) const
    {
        Tree       w    = irmInputWeight(p);
        const int  vr   = std::max(getCertifiedSigType(x)->variability(), getCertifiedSigType(p)->variability());
        const bool real = getCertifiedSigType(sig)->nature() == kReal;
        if (irmErrorFormApplies(sig, x, p)) {
            return IrmForm::kError;
        }
        if (real && (!w || (vr != kSamp && !reachesDecision(sig)))) {
            return IrmForm::kWeighted;
        }
        if (!w && !itv::mixFromB(getCertifiedSigType(p)->getInterval())) {
            return IrmForm::kFromX;
        }
        return IrmForm::kFromState;
    }

   public:
    explicit Translation(Tree program) : fProgram(program) {}

    XSig combine(Tree sig, const std::vector<XSig>& c, FixPointEvaluator<XSig>& ev) const override
    {
        Tree x, p, w, a, b;
        if (isSigPhase(sig, x, p)) {
            return o(cfPhase(c[0].out, c[1].out, phaseByReciprocal(p)));
        }
        if (isSigMix(sig, w, a, b)) {
            return o(cfMix(c[0].out, c[1].out, c[2].out, mixForm(w)));
        }
        if (isSigIRM(sig, x, p)) {
            return o(cfIrm(c[0].out, c[1].out, irmForm(sig, x, p)));
        }
        if (isSigFrac(sig, x)) {
            return o(cfFrac(c[0].out, approxRoundApplies(getCertifiedSigType(x))));
        }
        return TransformAlgebra::combine(sig, c, ev);
    }

    /// floor and ceil : their approximated primitive under -mapp, where the certified x lies
    /// in the int32 range (approxRound.hh)
    XSig xtdApp(Tree orig, xtended* prim, const std::vector<XSig>& c) const override
    {
        xtended* approx = (prim == gGlobal->gFloorPrim) ? gGlobal->gFloorApproxPrim
                          : (prim == gGlobal->gCeilPrim) ? gGlobal->gCeilApproxPrim
                                                         : nullptr;
        if (approx != nullptr && approxRoundApplies(getCertifiedSigType(orig->branch(0)))) {
            return o(tree(approx->symbol(), c[0].out));
        }
        return TransformAlgebra::xtdApp(orig, prim, c);
    }
};

}  // namespace

ComputeForm::ComputeForm(Tree L, bool lower, LaneOrder order, bool families) : fSource(L)
{
    fProgram = translate(L);
    if (lower && gGlobal->gFloatSize != 4) {
        this->lower(order, families);
    } else {
        if (gGlobal->gFloatSize != 4) {
            lowerCompounds();
        }
        cutSlowPrefixes();
    }
}

void ComputeForm::lowerCompounds()
{
    // the compound operations written as the operations their code computes : the emission
    // then translates the form as it is (lowerComposites.hh)
    std::unordered_map<Tree, Tree> memo;
    startTiming("lowerComposites");
    fProgram = lowerComposites(fProgram, &memo);
    composeImage(fImage, memo);
    endTiming("lowerComposites");
    if (gGlobal->gIntNarrowing) {
        // the conversions to int of reals computed from integers, written in integers : the
        // same values (narrowIntegers.hh, -noin)
        memo.clear();
        startTiming("narrowIntegers");
        fProgram = narrowIntegers(fProgram, &memo);
        composeImage(fImage, memo);
        endTiming("narrowIntegers");
    }
}

void ComputeForm::cutSlowPrefixes()
{
    // the prefixes of the chains computed at their own rate, nodes of their own : the
    // emission then translates the form as it is (slowPrefixes.hh)
    std::unordered_map<Tree, Tree> memo;
    startTiming("slowPrefixes");
    fProgram = slowPrefixes(fProgram, &memo);
    composeImage(fImage, memo);
    endTiming("slowPrefixes");
}

void ComputeForm::lower(LaneOrder order, bool families)
{
    std::unordered_map<Tree, Tree> memo;
    std::unordered_map<Tree, Tree> frozen;  // opaque leaf -> the node of a family it stands for
    if (families) {
        // the sum families are found before the rewrites that change the rounding, and
        // frozen through them : a family split into partial sums, or sharing a sub-sum with
        // another member, would no longer be one
        startTiming("families");
        std::vector<FamilyPlan> families;
        {
            std::unordered_map<Tree, Tree> flat;
            Tree                           P = flattenFamilyHosts(fProgram, families, flat);
            if (P != fProgram) {
                fProgram = P;
                composeImage(fImage, flat);
            }
        }
        const TreeSet nodes = familyFrozenSet(fProgram, families);
        if (!nodes.empty()) {
            fProgram = freezeFamilies(fProgram, nodes, frozen, memo);
            composeImage(fImage, memo);
        }
        endTiming("families");
    }
    if (gGlobal->gShareSums) {
        if (gGlobal->gSumLanes) {
            // the nested sums gathered and their like terms merged first : the sharing
            // reads flat rows (sumLanes.hh)
            startTiming("gatherSums");
            fProgram = gatherSums(fProgram, &memo);
            composeImage(fImage, memo);
            endTiming("gatherSums");
        }
        // the dense sums factored by coefficient and their common sub-sums shared, then the
        // sums of products factored : a term read only by the sub-sum the sharing extracted
        // is no longer read twice (-noshs)
        startTiming("shareSums");
        fProgram = shareSums(fProgram, &memo);
        composeImage(fImage, memo);
        endTiming("shareSums");
        startTiming("factorSums");
        fProgram = factorSums(fProgram, &memo);
        composeImage(fImage, memo);
        endTiming("factorSums");
    }
    if (gGlobal->gExactWeights) {
        // (1 + w) * y written w * y + y, a small w read exactly, not through 1 + w rounded
        // (-noxw)
        startTiming("exactWeights");
        fProgram = exactWeights(fProgram, &memo);
        composeImage(fImage, memo);
        endTiming("exactWeights");
    }
    if (gGlobal->gReciprocals) {
        // x / d written x * (1 / d), d slower than the division or shared (-norcp)
        startTiming("reciprocals");
        fProgram = reciprocals(fProgram, &memo);
        composeImage(fImage, memo);
        endTiming("reciprocals");
    }
    if (gGlobal->gSumLanes) {
        // the long sums in partial sums, interleaved or contiguous (-nosl)
        startTiming("sumLanes");
        fProgram = sumLanes(fProgram, order, &memo);
        composeImage(fImage, memo);
        endTiming("sumLanes");
    }
    if (!frozen.empty()) {
        memo.clear();
        fProgram = thawFamilies(fProgram, frozen, memo);
        composeImage(fImage, memo);
    }
    // after every rewrite of the chains, the families thawed : the compound operations
    // written out and the cuts change no rounding, and the members of a family change alike
    lowerCompounds();
    cutSlowPrefixes();
    if (gGlobal->gLateTaps) {
        // the late term of a filter added last (-nolt)
        markLateTaps(fProgram);
    }
    if (gGlobal->gCallMemo) {
        // the costly calls whose arguments settle, called again only when one changed (-nomc)
        markSettlingCalls(fProgram);
    }
}

namespace {

/// t settles : it depends only on values slower than the sample, and on smoothers of a slow target
/// and pole (an IRM), which reach their target and then stay constant
bool settles(Tree t, std::unordered_map<Tree, bool>& memo)
{
    auto it = memo.find(t);
    if (it != memo.end()) {
        return it->second;
    }
    memo[t]     = false;  // a cycle does not settle
    bool    r   = false;
    Type    ty  = t->getType() ? getCertifiedSigType(t) : nullptr;
    Tree    x, p, d;
    IrmForm f;
    int     i;
    Tree    g;
    if (ty && ty->variability() <= kBlock) {
        r = true;
    } else if (isSigIRM(t, x, p) || isCfIrm(t, x, p, f)) {
        r = getCertifiedSigType(x)->variability() <= kBlock && getCertifiedSigType(p)->variability() <= kBlock;
    } else if (isProj(t, &i, g) || isSigInput(t, &i) || isRec(t, x, p)) {
        r = false;
    } else if (tvec V; isSigIIR(t, V)) {
        r = false;  // a recursion, even of a constant input and constant coefficients
    } else if (isSigDelay(t, x, d)) {
        r = settles(x, memo) && settles(d, memo);
    } else if (t->arity() > 0 && ty) {
        r = true;
        for (Tree b : t->branches()) {
            if (isSigInput(b, &i)) {
                r = false;  // an input, which may be left without a type here
                break;
            }
            if (isList(b)) {
                // the arguments of a foreign function, a list without a type : each must settle
                for (Tree l = b; r && isList(l); l = tl(l)) {
                    r = isNum(hd(l)) || settles(hd(l), memo);
                }
                if (!r) {
                    break;
                }
                continue;
            }
            if (b->getType() == nullptr && !isNum(b)) {
                continue;  // the opcode of a binary operation, a label
            }
            if (!isNum(b) && !settles(b, memo)) {
                r = false;
                break;
            }
        }
    }
    memo[t] = r;
    return r;
}

}  // namespace

static Tree settlingCallKey()
{
    static Tree key = tree(symbol("SETTLINGCALL"));
    return key;
}

bool isSettlingCall(Tree t)
{
    Tree v;
    return getProperty(t, settlingCallKey(), v);
}

void ComputeForm::markSettlingCalls(Tree L)
{
    // the costly calls computed at the sample rate, and those whose arguments settle, marked ;
    // FAUST_TRACE_MEMO prints their counts
    const std::unordered_set<xtended*> costly = {gGlobal->gPowPrim,  gGlobal->gExpPrim,  gGlobal->gExp10Prim,
                                                 gGlobal->gLogPrim,  gGlobal->gLog10Prim, gGlobal->gSinPrim,
                                                 gGlobal->gCosPrim,  gGlobal->gTanPrim,  gGlobal->gAtanPrim,
                                                 gGlobal->gAtan2Prim, gGlobal->gAsinPrim, gGlobal->gAcosPrim};
    std::unordered_map<Tree, bool> memo;
    std::unordered_set<Tree>       seen;
    std::vector<Tree>              work{L};
    int                            samp = 0, settling = 0;
    while (!work.empty()) {
        Tree t = work.back();
        work.pop_back();
        if (!seen.insert(t).second) {
            continue;
        }
        Tree var, body;
        if (isRec(t, var, body)) {
            if (body != nullptr) work.push_back(body);
            continue;
        }
        for (Tree b : t->branches()) work.push_back(b);
        xtended* p = (xtended*)sigXtendedData(t);
        if (p && costly.count(p) && t->getType() && getCertifiedSigType(t)->variability() == kSamp) {
            samp++;
            bool all = true;
            for (Tree b : t->branches()) all = all && (isNum(b) || settles(b, memo));
            if (all && getCertifiedSigType(t)->nature() == kReal) {
                Tree key = settlingCallKey();
                setProperty(t, key, key);
                settling++;
            }
        }
    }
    if (getenv("FAUST_TRACE_MEMO")) {
        std::cerr << "MEMO-TRACE costly-samp " << samp << " settling " << settling << std::endl;
    }
    if (getenv("FAUST_TRACE_SETTLE")) {
        censusSettlingCone(L, costly);
    }
}

void ComputeForm::censusSettlingCone(Tree L, const std::unordered_set<xtended*>& costly)
{
    // the census of the regime where every smoother of a slow target and pole has reached it :
    // the operations computed at the sample rate, those of the cone that then stays constant
    // (settles), the smoothers, the costly calls, the frontier (the values of the cone read
    // outside it) and the delays inside the cone
    std::unordered_map<Tree, bool> memo, viaIrm;
    std::unordered_set<Tree>       seen, frontier;
    std::vector<Tree>              work{L};
    int ops = 0, cone = 0, irms = 0, costlyOps = 0, costlyCone = 0, delays = 0, coneIrm = 0, costlyIrm = 0;
    // a node of the cone reaches a smoother ; the others settle only through delays of slow values
    std::function<bool(Tree)> reachesIrm = [&](Tree t) {
        auto it = viaIrm.find(t);
        if (it != viaIrm.end()) {
            return it->second;
        }
        viaIrm[t] = false;
        Tree    x, p;
        IrmForm f;
        bool    r = isSigIRM(t, x, p) || isCfIrm(t, x, p, f);
        if (!r && t->getType() && getCertifiedSigType(t)->variability() == kSamp) {
            for (Tree b : t->branches()) {
                if (b->getType() && reachesIrm(b)) {
                    r = true;
                    break;
                }
            }
        }
        viaIrm[t] = r;
        return r;
    };
    auto isOp = [](Tree t) {
        int  i;
        Tree g;
        return t->arity() > 0 && t->getType() && getCertifiedSigType(t)->variability() == kSamp && !isProj(t, &i, g) &&
               !isSigInput(t, &i);
    };
    while (!work.empty()) {
        Tree t = work.back();
        work.pop_back();
        if (!seen.insert(t).second) {
            continue;
        }
        Tree var, body;
        if (isRec(t, var, body)) {
            if (body != nullptr) work.push_back(body);
            continue;
        }
        for (Tree b : t->branches()) work.push_back(b);
        if (!isOp(t)) {
            continue;
        }
        Tree     x, p, d;
        IrmForm  f;
        xtended* xt   = (xtended*)sigXtendedData(t);
        bool     c    = settles(t, memo);
        bool     cost = xt && costly.count(xt);
        bool     irm  = isSigIRM(t, x, p) || isCfIrm(t, x, p, f);
        ops++;
        costlyOps += cost;
        if (c) {
            cone++;
            costlyCone += cost;
            if (std::string(getenv("FAUST_TRACE_SETTLE")) == "2") {
                std::cerr << "SETTLE-NODE " << ppsig(t, 3) << std::endl;
            }
            if (reachesIrm(t)) {
                coneIrm++;
                costlyIrm += cost;
            }
            irms += irm;
            delays += isSigDelay(t, x, d);
        } else {
            for (Tree b : t->branches()) {
                if (b->getType() && isOp(b) && settles(b, memo)) {
                    frontier.insert(b);
                }
            }
        }
    }
    std::cerr << "SETTLE-TRACE samp-ops " << ops << " cone " << cone << " irm " << irms << " costly " << costlyOps
              << " costly-cone " << costlyCone << " frontier " << frontier.size() << " cone-delays " << delays
              << " cone-irm " << coneIrm << " costly-irm " << costlyIrm << std::endl;
}

Tree ComputeForm::translate(Tree t)
{
    Tree r = signalTransform(t, Translation(fSource), fImage);
    annotate();
    return r;
}

void ComputeForm::annotate()
{
    for (const auto& [src, dst] : fImage) {
        if (dst == src) {
            continue;
        }
        // the type of the source : the same value
        if (src->getType() != nullptr && dst->getType() == nullptr) {
            setSigType(dst, getSigType(src));
        }
    }
}

Tree ComputeForm::remap(Tree t)
{
    if (t == nullptr) {
        return t;
    }
    auto it = fImage.find(t);
    if (it != fImage.end()) {
        return it->second;
    }
    if (t->arity() == 0) {
        return t;
    }
    tvec br;
    br.reserve(t->arity());
    bool changed = false;
    for (Tree b : t->branches()) {
        br.push_back(remap(b));
        changed = changed || br.back() != b;
    }
    if (!changed) {
        return t;
    }
    Tree r = tree(t->node(), br);
    if (t->getType() != nullptr && r->getType() == nullptr) {
        setSigType(r, getSigType(t));
    }
    return r;
}
