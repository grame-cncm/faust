#include <vector>

#include "global.hh"
#include "revealSum.hh"
#include "sigIdentity.hh"
#include "simplify.hh"

#define TRACE false

// simplify() exige des termes clos : pendant la descente du revelateur,
// les sous-arbres d'un groupe recursif portent des references ouvertes
// (ref sans rec rempli) que la machinerie de reecriture refuse
// (rewrite.hh, body != nullptr). La garde derive du contrat : un terme
// non rec-free reste tel quel -- la simplification est une optimisation.
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

// Transform a signal expression by revealing SUM structures

class SumRevealer : public SignalIdentity {
   protected:
    Tree postprocess(Tree L);
    Tree transformation(Tree L);
};

Tree SumRevealer::transformation(Tree sig)
{
    Tree var, le;
    if (isRec(sig, var, le)) {
        // rec protocol : ref() creates the (unique) virgin group, mapself
        // runs with the open reference registered, ONE rec() closes it
        Tree var2 = tree(unique("WS"));
        Tree rec2 = ref(var2);
        fResult.set(sig, rec2);
        Tree l2 = mapself(le);
        return rec(var2, l2);
    }
    return SignalIdentity::transformation(sig);
}

Tree SumRevealer::postprocess(Tree sig)
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
    SumRevealer R;
    R.trace(TRACE, "revealSUM");
    return R.mapself(L1);
}
