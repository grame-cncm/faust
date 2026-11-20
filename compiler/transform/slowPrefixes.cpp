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

#include "slowPrefixes.hh"

#include <cmath>
#include <unordered_set>
#include <vector>

#include "rewrite.hh"
#include "sigtype.hh"
#include "sumLayout.hh"
#include "typedAttributes.hh"

namespace {

int rateOf(Tree t)
{
    return getCertifiedSigType(t)->variability();
}

/// A cut of a chain : before its operand at, the chain so far is a prefix of its own, of
/// the given rate and, for an Int32 chain, range
struct Cut {
    size_t   at;
    int      variability;
    IntRange range;
};

/// The chain of Prod(fs) as emitProd computes it : the factors kept, and the prefixes
/// stored, in order. Reads the types only.
struct ProdPlan {
    std::vector<size_t> kept;
    std::vector<Cut>    cuts;
};

ProdPlan planProd(Tree sig, const tvec& fs)
{
    ProdPlan  plan;
    const int nprod = getCertifiedSigType(sig)->nature();
    const int vprod = rateOf(sig);
    bool      typed = false;
    for (size_t i = 0; i < fs.size(); i++) {
        if (!isOneAtPrecision(fs[i])) {
            plan.kept.push_back(i);
            typed = typed || getCertifiedSigType(fs[i])->nature() == nprod;
        }
    }
    if (plan.kept.empty() || !typed) {
        plan.kept.clear();
        for (size_t i = 0; i < fs.size(); i++) {
            plan.kept.push_back(i);
        }
    }
    const bool isInt       = nprod == kInt;
    int        variability = 0;
    int        count       = 0;
    IntRange   range;
    for (size_t k = 0; k < plan.kept.size(); k++) {
        Tree      f  = fs[plan.kept[k]];
        const int vf = rateOf(f);
        if (count >= 2 && variability < vf && variability < vprod) {
            plan.cuts.push_back({k, variability, range});
            count = 1;
        }
        const IntRange fr = isInt ? intRange(f) : IntRange{};
        if (count == 0) {
            range = fr;
        } else if (isInt) {
            intOpWraps(kMul, range, fr, range);
        }
        variability = std::max(variability, vf);
        count++;
    }
    return plan;
}

/// The chain of Sum(subs) as emitSum computes it : its signed terms, the prefixes of the
/// leading negated terms stored, the stored sum of those terms when subtracted, and the
/// prefixes of the chain stored. Reads the types only.
struct SumPlan {
    std::vector<size_t> index;  ///< the term of each signed term in subs
    std::vector<bool>   positive;
    size_t              first = 0;  ///< the first positive signed term
    std::vector<Cut>    leadCuts;   ///< in the leading negated terms
    bool                leadStored = false;
    Cut                 lead{0, 0, {}};  ///< the leading negated terms, when stored
    std::vector<Cut>    cuts;            ///< in the chain, at a signed term
    bool                any() const { return !leadCuts.empty() || leadStored || !cuts.empty(); }
};

/// the operand of a negated term, as signedTerms reads it ; nullptr for a positive term
Tree negatedOperand(Tree t)
{
    if (Tree x = negationOperand(t)) {
        return x;
    }
    tvec fc;
    if (isSigFIR(t, fc) && fc.size() == 2 && isMinusOne(fc[1])) {
        return fc[0];
    }
    return nullptr;
}

SumPlan planSum(Tree sig, const tvec& subs)
{
    SumPlan    plan;
    const int  vsum  = rateOf(sig);
    const bool isInt = getCertifiedSigType(sig)->nature() == kInt;
    std::vector<Tree> mag;  // the magnitude of each signed term
    for (size_t i = 0; i < subs.size(); i++) {
        if (isZero(subs[i])) {
            continue;
        }
        Tree x = negatedOperand(subs[i]);
        plan.index.push_back(i);
        plan.positive.push_back(x == nullptr);
        mag.push_back(x ? x : subs[i]);
    }
    if (mag.empty()) {
        return plan;
    }
    struct Acc {
        int      variability = 0;
        int      count       = 0;
        IntRange range;
    };
    auto extend = [&](Acc& acc, std::vector<Cut>& cuts, size_t k, bool positive) {
        const int vt = rateOf(mag[k]);
        if (acc.count >= 2 && acc.variability < vt && acc.variability < vsum) {
            cuts.push_back({k, acc.variability, acc.range});
            acc.count = 1;
        }
        const IntRange xr = isInt ? intRange(mag[k]) : IntRange{};
        if (acc.count == 0) {
            acc.range = xr;
        } else if (isInt) {
            intOpWraps(positive ? kAdd : kSub, acc.range, xr, acc.range);
        }
        acc.variability = std::max(acc.variability, vt);
        acc.count++;
    };
    while (plan.first < mag.size() && !plan.positive[plan.first]) {
        plan.first++;
    }
    Acc lead;
    for (size_t k = 0; k < plan.first; k++) {
        extend(lead, plan.leadCuts, k, true);
    }
    if (plan.first == mag.size()) {
        return plan;
    }
    Acc acc;
    extend(acc, plan.cuts, plan.first, true);
    if (lead.count > 0) {
        if (lead.count >= 2 && lead.variability < acc.variability && lead.variability < vsum) {
            plan.leadStored = true;
            plan.lead       = {plan.first, lead.variability, lead.range};
        }
        if (isInt) {
            intOpWraps(kSub, acc.range, lead.range, acc.range);
        }
        acc.variability = std::max(acc.variability, lead.variability);
        acc.count       = 2;
    }
    for (size_t k = plan.first + 1; k < mag.size(); k++) {
        extend(acc, plan.cuts, k, plan.positive[k]);
    }
    return plan;
}

/// a node of the pass, typed : the nature of its chain, the rate and range of its prefix,
/// the other attributes the union of its operands' (typedAttributes.hh)
Tree typed(Tree t, int nature, int variability, bool isInt, const IntRange& range, const tvec& operands)
{
    if (t->getType() != nullptr) {
        return t;  // a node of the program, or of another prefix : its type stands
    }
    int c = 0, vec = 0, b = 0;
    for (Tree o : operands) {
        Type to = getCertifiedSigType(o);
        c |= to->computability();
        vec |= to->vectorability();
        b |= to->boolean();
    }
    const itv::interval i = isInt ? itv::interval(double(range.lo), double(range.hi))
                                  : itv::interval(-HUGE_VAL, HUGE_VAL);
    setSigType(t, makeSimpleType(nature, variability, c, vec, b, i));
    return t;
}

/// Prod(fs) written with its stored prefixes as nodes : fs are the factors of the source,
/// typed, rs those of the rebuilt node, built
Tree buildProd(Tree sig, const ProdPlan& plan, const tvec& fs, const tvec& rs)
{
    const int  nature = getCertifiedSigType(sig)->nature();
    const bool isInt  = nature == kInt;
    tvec       acc, src;  // the chain built, and its operands typed
    size_t     c = 0;
    for (size_t k = 0; k < plan.kept.size(); k++) {
        if (c < plan.cuts.size() && plan.cuts[c].at == k) {
            Tree p = sigProd(acc);
            p      = typed(p, nature, plan.cuts[c].variability, isInt, plan.cuts[c].range, src);
            acc    = {p};
            src    = {p};
            c++;
        }
        acc.push_back(rs[plan.kept[k]]);
        src.push_back(fs[plan.kept[k]]);
    }
    return sigProd(acc);
}

/// Sum(subs) written with its stored prefixes as nodes : a stored sum of leading negated
/// terms is subtracted as neg(L), a stored prefix of the chain is its first term ; subs are
/// the terms of the source, typed, rs those of the rebuilt node, built
Tree buildSum(Tree sig, const SumPlan& plan, const tvec& subs, const tvec& rs)
{
    const int  nature = getCertifiedSigType(sig)->nature();
    const bool isInt  = nature == kInt;
    auto       magnitude = [&](const tvec& terms, size_t k) {
        Tree t = terms[plan.index[k]];
        Tree x = plan.positive[k] ? nullptr : negatedOperand(t);
        return x ? x : t;
    };
    auto negated = [&](Tree l, const Cut& cut) {
        IntRange r;
        if (isInt) {
            intOpWraps(kSub, IntRange{0, 0}, cut.range, r);
        }
        Tree n = sigNeg(l);
        return typed(n, nature, cut.variability, isInt, r, {l});
    };
    // the leading negated terms : their magnitudes summed, a stored prefix a term of its own
    tvec   mags, magsSrc;    // the magnitudes of the current prefix of the leading terms
    tvec   items, itemsSrc;  // the terms of the current prefix of the chain
    size_t c = 0;
    for (size_t k = 0; k < plan.first; k++) {
        if (c < plan.leadCuts.size() && plan.leadCuts[c].at == k) {
            Tree l = sigSum(mags);
            l      = typed(l, nature, plan.leadCuts[c].variability, isInt, plan.leadCuts[c].range, magsSrc);
            Tree n = negated(l, plan.leadCuts[c]);
            mags     = {l};
            magsSrc  = {l};
            items    = {n};
            itemsSrc = {n};
            c++;
        }
        mags.push_back(magnitude(rs, k));
        magsSrc.push_back(magnitude(subs, k));
        items.push_back(rs[plan.index[k]]);
        itemsSrc.push_back(subs[plan.index[k]]);
    }
    if (plan.leadStored) {
        Tree l   = sigSum(mags);
        l        = typed(l, nature, plan.lead.variability, isInt, plan.lead.range, magsSrc);
        Tree n   = negated(l, plan.lead);
        items    = {n};
        itemsSrc = {n};
    }
    // the chain : the leading terms, then the others in order
    c = 0;
    for (size_t k = plan.first; k < plan.index.size(); k++) {
        if (c < plan.cuts.size() && plan.cuts[c].at == k) {
            Tree a   = sigSum(items);
            a        = typed(a, nature, plan.cuts[c].variability, isInt, plan.cuts[c].range, itemsSrc);
            items    = {a};
            itemsSrc = {a};
            c++;
        }
        items.push_back(rs[plan.index[k]]);
        itemsSrc.push_back(subs[plan.index[k]]);
    }
    return sigSum(items);
}

}  // namespace

Tree slowPrefixes(Tree L, std::unordered_map<Tree, Tree>* image)
{
    // a rewrite rebuilds the recursions with fresh variables : none when no chain stores a
    // prefix
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
            tvec ops;
            if (isSigProd(t, ops)) {
                any = !planProd(t, ops).cuts.empty();
            } else if (isSigSum(t, ops)) {
                any = planSum(t, ops).any();
            }
        }
    }
    if (!any) {
        if (image != nullptr) {
            image->clear();
        }
        return L;
    }

    std::unordered_map<Tree, Tree> memo;
    auto rule = [&](Tree orig, Tree rebuilt) -> Tree {
        tvec ops, rops;
        if (isSigProd(orig, ops) && isSigProd(rebuilt, rops) && ops.size() == rops.size()) {
            ProdPlan plan = planProd(orig, ops);
            return plan.cuts.empty() ? rebuilt : buildProd(orig, plan, ops, rops);
        }
        if (isSigSum(orig, ops) && isSigSum(rebuilt, rops) && ops.size() == rops.size()) {
            SumPlan plan = planSum(orig, ops);
            return plan.any() ? buildSum(orig, plan, ops, rops) : rebuilt;
        }
        return rebuilt;
    };
    Tree r = treeRewritePaired(L, rule, memo);
    completeTypes(r, memo);
    if (image != nullptr) {
        *image = memo;
    }
    return r;
}
