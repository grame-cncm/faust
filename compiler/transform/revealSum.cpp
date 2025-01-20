#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "ppsig.hh"
#include "revealSum.hh"
#include "sigIdentity.hh"
#include "simplify.hh"

#define TRACE false

// Negate a signal: S -> -S
static Tree sigNeg(Tree sig)
{
    Tree z = simplify(sigMul(sigInt(-1), sig));
    if (TRACE) {
        std::cerr << "Negating " << ppsig(sig) << "into " << z << "\n";
    }
    return z;
}

// If needed, wrap a signal into a sum
static Tree ensureSum(Tree x, bool invertSecondTerm)
{
    if (!invertSecondTerm) {
        // no invertion needed
        if (isSigSum(x)) {
            // already a sum
            return x;
        } else {
            // we need to create a sum
            tvec subs{x};
            return sigSum(subs);
        }
    } else {
        // we need to invert the subsignals
        if (tvec subs; isSigSum(x, subs)) {
            tvec invsubs;
            for (Tree s : subs) {
                invsubs.push_back(sigNeg(s));
            }
            return sigSum(invsubs);
        } else {
            tvec invsubs{sigNeg(x)};
            return sigSum(invsubs);
        }
    }
}

// Transform a signal expression by revealing SUM structures

// Tree revealIIR(Tree rt, Tree def);

class SumRevealer : public SignalIdentity {
   protected:
    Tree postprocess(Tree L);
    Tree transformation(Tree L);
};

Tree SumRevealer::transformation(Tree sig)
{
    Tree var, le;
    if (isRec(sig, var, le)) {
        Tree var2 = tree(unique("WS"));
        Tree rec2 = rec(var2, gGlobal->nil);
        traceMsg("WARNING: We have set the definitions to nil for group", rec2);
        fResult.set(sig, rec2);     // We rename the recgroup
        Tree l2   = mapself(le);    // We transfom its definitions
        Tree rec3 = rec(var2, l2);  // We update the definition
        traceMsg("WARNING: We have updated the definitions of group", rec3);
        return rec3;

    } else {
        return SignalIdentity::transformation(sig);
    }
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
    } else if (isSigSub(sig, x, y)) {
        Tree sx = ensureSum(x, false);
        Tree sy = ensureSum(y, true);
        tvec xsubs, ysubs;
        faustassert(isSigSum(sx, xsubs) && isSigSum(sy, ysubs));
        tvec zsubs;
        zsubs.insert(zsubs.end(), xsubs.begin(), xsubs.end());
        zsubs.insert(zsubs.end(), ysubs.begin(), ysubs.end());
        return sigSum(zsubs);
    } else {
        return sig;
    }
}

// External API

Tree revealSum(Tree L1)
{
    SumRevealer R;
    R.trace(TRACE, "revealSUM");
    Tree L2 = R.mapself(L1);
    return L2;
}
