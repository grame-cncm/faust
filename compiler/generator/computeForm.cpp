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

#include <unordered_set>

#include "code_container.hh"
#include "approxRound.hh"
#include "computeSignals.hh"
#include "decisionCone.hh"
#include "global.hh"
#include "xtended.hh"
#include "definitionIndex.hh"
#include "irm_weight.hh"
#include "mixForm.hh"
#include "sigtransform.hh"
#include "exactWeights.hh"
#include "factorSums.hh"
#include "shareSums.hh"
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

    /// IRM(x; p) : the weighted sum when the source wrote the pole, and for a pole written
    /// 1 - w with a slow target and pole unless the node reaches a decision ; otherwise
    /// the interpolation from x when p may be below 1/2, from the state when not
    IrmForm irmForm(Tree sig, Tree x, Tree p) const
    {
        Tree       w    = irmInputWeight(p);
        const int  vr   = std::max(getCertifiedSigType(x)->variability(), getCertifiedSigType(p)->variability());
        const bool real = getCertifiedSigType(sig)->nature() == kReal;
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

ComputeForm::ComputeForm(Tree L, bool lower, LaneOrder order) : fSource(L)
{
    fProgram = translate(L);
    if (lower && gGlobal->gFloatSize != 4) {
        this->lower(order);
    }
}

void ComputeForm::lower(LaneOrder order)
{
    std::unordered_map<Tree, Tree> memo;
    if (gGlobal->gShareSums) {
        // the sums of products factored, then the dense sums factored by coefficient and
        // their common sub-sums shared (-noshs)
        startTiming("factorSums");
        fProgram = factorSums(fProgram, &memo);
        composeImage(fImage, memo);
        endTiming("factorSums");
        startTiming("shareSums");
        fProgram = shareSums(fProgram, &memo);
        composeImage(fImage, memo);
        endTiming("shareSums");
    }
    if (gGlobal->gExactWeights) {
        // (1 + w) * y written w * y + y, a small w read exactly, not through 1 + w rounded
        // (-noxw)
        startTiming("exactWeights");
        fProgram = exactWeights(fProgram, &memo);
        composeImage(fImage, memo);
        endTiming("exactWeights");
    }
    if (gGlobal->gSumLanes) {
        // the long sums in partial sums, interleaved or contiguous (-nosl)
        startTiming("sumLanes");
        fProgram = sumLanes(fProgram, order, &memo);
        composeImage(fImage, memo);
        endTiming("sumLanes");
    }
    if (gGlobal->gLateTaps) {
        // the late term of a filter added last (-nolt)
        markLateTaps(fProgram);
    }
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
