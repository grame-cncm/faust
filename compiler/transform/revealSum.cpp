#include <vector>

#include "global.hh"
#include "revealSum.hh"
#include "rewrite.hh"
#include "simplify.hh"

// simplify() exige des termes clos : pendant la reecriture, les sous-arbres
// d'un groupe recursif portent des references ouvertes (ref sans rec rempli)
// que la machinerie de reecriture refuse (rewrite.hh, body != nullptr). La
// garde derive du contrat : un terme non rec-free reste tel quel -- la
// simplification est une optimisation.
static Tree recSafeSimplify(Tree t)
{
    return t->isRecFree() ? simplify(t) : t;
}

// Negate a signal: S -> -S
static Tree sigNeg(Tree sig)
{
    return recSafeSimplify(sigMul(sigInt(-1), sig));
}

// If needed, wrap a signal into a sum
static Tree ensureSum(Tree x, bool invertSecondTerm)
{
    if (!invertSecondTerm) {
        if (isSigSum(x)) {
            return x;
        }
        tvec subs{x};
        return sigSum(subs);
    }
    // we need to invert the subsignals
    if (tvec subs; isSigSum(x, subs)) {
        tvec invsubs;
        for (Tree s : subs) {
            invsubs.push_back(sigNeg(s));
        }
        return sigSum(invsubs);
    }
    tvec invsubs{sigNeg(x)};
    return sigSum(invsubs);
}

// The local rule : adds and subs become n-ary SigSum nodes. Bottom-up on the
// rebuilt node, per the generic tlib rewrite (rec renaming is the traversal's
// business, not ours).
static Tree sumRule(Tree sig)
{
    Tree x, y;
    if (isSigAdd(sig, x, y)) {
        Tree sx = ensureSum(x, false);
        Tree sy = ensureSum(y, false);
        tvec xsubs, ysubs;
        faustassert(isSigSum(sx, xsubs) && isSigSum(sy, ysubs));
        tvec zsubs;
        zsubs.insert(zsubs.end(), xsubs.begin(), xsubs.end());
        zsubs.insert(zsubs.end(), ysubs.begin(), ysubs.end());
        return sigSum(zsubs);
    }
    if (isSigSub(sig, x, y)) {
        Tree sx = ensureSum(x, false);
        Tree sy = ensureSum(y, true);
        tvec xsubs, ysubs;
        faustassert(isSigSum(sx, xsubs) && isSigSum(sy, ysubs));
        tvec zsubs;
        zsubs.insert(zsubs.end(), xsubs.begin(), xsubs.end());
        zsubs.insert(zsubs.end(), ysubs.begin(), ysubs.end());
        return sigSum(zsubs);
    }
    return sig;
}

// External API

Tree revealSum(Tree L1)
{
    return treeRewrite(L1, sumRule);
}
