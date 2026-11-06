/************************************************************************
 ************************************************************************
    FAUST signal library
    Copyright (C) 2026 GRAME, Centre National de Creation Musicale
    SPDX-License-Identifier: LGPL-2.1-or-later
 ************************************************************************
 ************************************************************************/

#include "computeSignals.hh"

#include "sigs-state.hh"

namespace sigs {

Signature computeSignature()
{
    return signature("Faust.Compute");
}

void initComputeSymbols()
{
    const Signature compute_signature = computeSignature();
    // the kinds of a constructor are those of its normal-form source
    g.CFPHASE = compute_signature.add("CfPhase");
    g.CFMIX   = compute_signature.add("CfMix");
    // the smoother reads its own past : audio rate whatever its operands, as SigIRM
    g.CFIRM = compute_signature.add("CfIRM", kAudioRate);
    g.CFFRAC  = compute_signature.add("CfFrac");
}

}  // namespace sigs

namespace {

/// the data child of a node : a number, never a signal
Tree datum(int v)
{
    return tree(v);
}

bool datumOf(Tree d, int& v)
{
    return isInt(d->node(), &v);
}

}  // namespace

SIGS_API bool isComputeSignal(Tree t)
{
    Sym       s;
    SymbolTag tag;
    return isSym(t->node(), &s) && getSymbolTag(s, tag) &&
           tag.signature == sigs::computeSignature().identity();
}

SIGS_API Tree cfPhase(Tree x, Tree p, bool byInverse)
{
    return tree(sigs::g.CFPHASE, x, p, datum(byInverse ? 1 : 0));
}

SIGS_API bool isCfPhase(Tree s, Tree& x, Tree& p, bool& byInverse)
{
    Tree d;
    int  v;
    if (!isTree(s, sigs::g.CFPHASE, x, p, d) || !datumOf(d, v)) {
        return false;
    }
    byInverse = v != 0;
    return true;
}

SIGS_API Tree cfMix(Tree c, Tree a, Tree b, MixForm form)
{
    return tree(sigs::g.CFMIX, c, a, b, datum(int(form)));
}

SIGS_API bool isCfMix(Tree s, Tree& c, Tree& a, Tree& b, MixForm& form)
{
    Tree d;
    int  v;
    if (!isTree(s, sigs::g.CFMIX, c, a, b, d) || !datumOf(d, v)) {
        return false;
    }
    form = MixForm(v);
    return true;
}

SIGS_API Tree cfIrm(Tree x, Tree c, IrmForm form)
{
    return tree(sigs::g.CFIRM, x, c, datum(int(form)));
}

SIGS_API bool isCfIrm(Tree s, Tree& x, Tree& c, IrmForm& form)
{
    Tree d;
    int  v;
    if (!isTree(s, sigs::g.CFIRM, x, c, d) || !datumOf(d, v)) {
        return false;
    }
    form = IrmForm(v);
    return true;
}

SIGS_API Tree cfFrac(Tree x, bool approx)
{
    return tree(sigs::g.CFFRAC, x, datum(approx ? 1 : 0));
}

SIGS_API bool isCfFrac(Tree s, Tree& x, bool& approx)
{
    Tree d;
    int  v;
    if (!isTree(s, sigs::g.CFFRAC, x, d) || !datumOf(d, v)) {
        return false;
    }
    approx = v != 0;
    return true;
}

SIGS_API bool isFracNode(Tree s, Tree& x)
{
    bool approx;
    return isSigFrac(s, x) || isCfFrac(s, x, approx);
}

SIGS_API bool isPhaseNode(Tree s, Tree& x, Tree& p)
{
    bool inv;
    return isSigPhase(s, x, p) || isCfPhase(s, x, p, inv);
}

SIGS_API bool isMixNode(Tree s, Tree& c, Tree& a, Tree& b)
{
    MixForm f;
    return isSigMix(s, c, a, b) || isCfMix(s, c, a, b, f);
}

SIGS_API bool isIrmNode(Tree s, Tree& x, Tree& c)
{
    IrmForm f;
    return isSigIRM(s, x, c) || isCfIrm(s, x, c, f);
}

SIGS_API bool isIrmNode(Tree s)
{
    Tree x, c;
    return isIrmNode(s, x, c);
}
