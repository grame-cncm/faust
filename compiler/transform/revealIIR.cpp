#include "revealIIR.hh"
#include <iostream>
#include <sstream>
#include <string>
#include "ppsig.hh"
#include "sigFIR.hh"
#include "sigIIR.hh"
#include "sigIdentity.hh"
#include "signals.hh"
#include "simplify.hh"

#include "DirectedGraph.hh"
#include "DirectedGraphAlgorythm.hh"
#include "Schedule.hh"
#include "sigRecursiveDependencies.hh"

#define TRACE false

//----------------------------------------------------------------------
// IIR part
//----------------------------------------------------------------------
Tree proj2IIR(int indentation, Tree rt);

//----------------------------------------------------------------------
// IIRevealer : reveal IIR structures
//----------------------------------------------------------------------

class IIRRevealer : public SignalIdentity {
   protected:
    Tree transformation(Tree L);
};

Tree IIRRevealer::transformation(Tree sig)
{
    Tree rgroup, var, le;
    int  p;

    if (isProj(sig, &p, rgroup) && isRec(rgroup, var, le)) {
        traceMsg("We have a recursive projection", sig);
        // we have a candidate for an IIR
        if (!isNil(le)) {
            Tree iir = proj2IIR(getIndentation(), sig);
            if (isNil(iir)) {
                return SignalIdentity::transformation(sig);
            } else {
                tvec coef;
                faustassert(isSigIIR(iir, coef));
                coef[0] = gGlobal->nil;  // anonymize the recursive projection
                for (unsigned int i = 1; i < coef.size(); i++) {
                    coef[i] = self(coef[i]);
                }
                return sigIIR(coef);
            }
        } else {
            traceMsg("We have a recursive projection, but definitions are nil", sig);
            return sig;  // SignalIdentity::transformation(sig);
        }
    } else {
        return SignalIdentity::transformation(sig);
    }
}

//----------------------------------------------------------------------
// Projection2IIR : reveal IIR structure of a recursive projection
//----------------------------------------------------------------------

class Projection2IIR : public SignalIdentity {
   protected:
    Tree fRecGroup;  // W, the recursive group
    int  fRecIndex;  // i, index in the recursive group
    Tree fRecProj;   // Wi, the recursive projection

   public:
    Projection2IIR(Tree recgroup, int recindex)
        : SignalIdentity(),
          fRecGroup(recgroup),
          fRecIndex(recindex),
          fRecProj(sigProj(recindex, recgroup))
    {
    }

   protected:
    virtual Tree transformation(Tree t);
    virtual Tree postprocess(Tree L);
};

// We intercept recursive projections to avoid visiting their definition
Tree Projection2IIR::transformation(Tree sig)
{
    Tree x, var, ldef;
    int  i;
    if (isProj(sig, &i, x) && isRec(x, var, ldef)) {
        traceMsg("WARNING: we are transforming a projection", sig);
        traceMsg("with list of definitions", ldef);
        return sig;
    }
    return SignalIdentity::transformation(sig);
}

// IIR structure [v,x,c1,c2,...] ==> v = x +c1*v@1 + c2*v@2 + ...
Tree Projection2IIR::postprocess(Tree sig)
{
    Tree x, y;
    int  d;

    if (hasNonValidArgs(sig)) {
        traceMsg("WARNING: We have non valid arguments in", sig);
        return gGlobal->nil;

    } else if (tvec coef; isSigFIR(sig, coef)) {
        traceMsg("FIR in Projection2IIR::postprocess", sig);
        if (tvec coef2; isSigIIR(coef[0], coef2) && (coef2[0] == fRecProj)) {
            traceMsg("We have a concerned IIR inside a FIR ", sig);
            return embeddedIIR(fRecProj, sig);
        } else {
            traceMsg("We have an unrelated IIR inside a FIR ", sig);
            return sig;  // unrelated FIR, stay FIR
        }

    } else if (isProj(sig, &d, x)) {
        return proj2SigIIR(fRecProj, sig);

    } else if (isSigDelay(sig, x, y)) {
        return delaySigIIR(fRecProj, x, y);

    } else if (isSigAdd(sig, x, y)) {
        return addSigIIR(fRecProj, x, y);

    } else if (isSigSub(sig, x, y)) {
        return subSigIIR(fRecProj, x, y);

    } else if (isSigMul(sig, x, y)) {
        return mulSigIIR(fRecProj, x, y);

    } else if (isSigDiv(sig, x, y)) {
        return divSigIIR(fRecProj, x, y);

    } else if (hasConcernedIIRArgs(fRecProj, sig)) {
        // the only valid combinations of IIRs are the ones above.
        // Therefore sig can't be represented by an IIR
        return gGlobal->nil;

    } else {
        return sig;
    }
}
#if 0
// Internal API
Tree proj2IIR(int indentation, Tree rt)
{
    int  i;
    Tree x, var, le;

    faustassert(isProj(rt, &i, x));
    faustassert(isRec(x, var, le));
    Tree              def = nth(le, i);
    Projection2IIR    R(x, i);
    std::stringstream ss(std::stringstream::out | std::stringstream::in);
    ss << "proj2IIR[" << *var << '_' << i << "]";
    R.trace(TRACE, ss.str(), indentation);

    // std::cerr << "def: " << *def << "\n";
    // std::cerr << "def: " << ppsig(def) << "\n";
    Tree result = R.self(def);
    // std::cerr << "result: " << ppsig(result) << "\n";

    if (result == def) {
        // we where not able to transform the definition into an IIR
        return gGlobal->nil;
    }
    return result;
}
#endif

/**
 * @brief Transform a FIR and an input signal into an IIR
 *
 * @param fcs: [W,c0,c1,...,cn]
 * @param input signal: x
 * @return IIR [W,x,c0,c1,...,cn]
 */
static Tree makeIIR(Tree fir, Tree in)
{
    tvec coef1, coef2;
    faustassert(isSigFIR(fir, coef1));
    coef2.push_back(coef1[0]);
    coef2.push_back(in);
    for (unsigned int i = 1; i < coef1.size(); i++) {
        coef2.push_back(coef1[i]);
    }
    Tree iir = sigIIR(coef2);
    // std::cerr << "makeIIR1: " << *iir << "\n";
    // std::cerr << "makeIIR2: " << ppsig(iir) << "\n";
    return iir;
}

//-------------------------------------------------------------------------
// Negate a signal: S -> -S
static Tree sigNeg(Tree sig)
{
    return simplify(sigMul(sigInt(-1), sig));
}

#if 1
/**
 * @brief Check if a recursive projection is a FIR that can
 * be transformed into an IIR
 *
 * @param indentation
 * @param proj: proj(i,rec(var,le))
 * @return an IIR or nil
 */
Tree proj2IIR(int indentation, Tree proj)
{
    int  i;
    Tree rg, var, le, x, y;

    faustassert(isProj(proj, &i, rg));
    faustassert(isRec(rg, var, le));
    Tree def = nth(le, i);
    if (isSigAdd(def, x, y)) {
        if (tvec cy; isSigFIR(y, cy) && cy[0] == proj) {
            if (!isDependingOn(x, proj)) {
                return makeIIR(y, x);
            } else {
                return gGlobal->nil;
            }
        } else if (tvec cx; isSigFIR(x, cx) && cx[0] == proj) {
            if (!isDependingOn(y, proj)) {
                return makeIIR(x, y);
            } else {
                return gGlobal->nil;
            }
        } else {
            return gGlobal->nil;
        }
    } else if (isSigSub(def, x, y)) {
        if (tvec cy; isSigFIR(y, cy) && cy[0] == proj) {
            if (!isDependingOn(x, proj)) {
                return makeIIR(negSigFIR(y), x);
            } else {
                return gGlobal->nil;
            }
        } else if (tvec cx; isSigFIR(x, cx) && cx[0] == proj) {
            if (!isDependingOn(y, proj)) {
                return makeIIR(x, sigNeg(y));
            } else {
                return gGlobal->nil;
            }
        } else {
            return gGlobal->nil;
        }
    } else {
        return gGlobal->nil;
    }
}
#endif

// External API

Tree revealIIR(Tree L1)
{
    IIRRevealer R;
    R.trace(TRACE, "revealIIR");
    Tree L2 = R.mapself(L1);
    return L2;
}