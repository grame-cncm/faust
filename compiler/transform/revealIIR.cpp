#include "revealIIR.hh"
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
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

#define TRACE true

#if 0
//----------------------------------------------------------------------
// IIR part
//----------------------------------------------------------------------

/**
 * @brief Transform a FIR on a rec variable and an input signal into an IIR
 *
 * @param fir: [W,c0,c1,...,cn]
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

/**
 * @brief indicate if x and/or y are clocked and return the clock and the unclocked signals
 * Trig an exception if x and y have different clocks
 *
 * @param x a potentially clocked signal
 * @param y a potentially clocked signal
 * @return std::tuple<bool, Tree, Tree, Tree> = (clocked, clock, unclocked x, unclocked y)
 */
static std::tuple<bool, Tree, Tree, Tree> unclock(Tree x, Tree y)
{
    Tree clock, clockx, x1, clocky, y1;
    bool clockedx = false;
    bool clockedy = false;
    bool clocked  = false;

    if (isSigClocked(x, clockx, x1)) {
        clockedx = true;
        clocked  = true;
        clock    = clockx;
    } else {
        x1 = x;
    }

    if (isSigClocked(y, clocky, y1)) {
        clockedy = true;
        clocked  = true;
        clock    = clocky;
    } else {
        y1 = y;
    }

    // if the two signals are clocked, they must be clocked by the same clock
    if (clockedx & clockedy) {
        faustassert(clockx == clocky);
    }

    return std::make_tuple(clocked, clock, x1, y1);
}

/**
 * @brief Check if a recursive projection is a FIR that can
 * be transformed into an IIR:
 *
 * def(Wi) = x + c1*Wi@1 + c2*Wi@2 + ...
 * def(Wi) = x + FIR[Wi, 0, c1, c2, ...]
 * IIR[nil, x, 0, c1, c2, ...]
 * (assuming, x doesn't depend on Wi)
 *
 * @param indentation
 * @param proj: proj(i,rec(var,le))
 * @return an IIR or nil
 */
static Tree recdef2IIR(int indentation, Tree proj, Tree def)
{
    // std::cerr << std::string(indentation, '\t') << "proj2IIR: " << ppsig(def) << "\n";
    if (Tree x, y; isSigAdd(def, x, y)) {
        if (tvec cy; isSigFIR(y, cy) && !isDependingOn(x, proj)) {
            if (Tree h, p; isSigClocked(cy[0], h, p) && p == proj) {
                return makeIIR(y, sigClocked(h, x));
            } else {
                return gGlobal->nil;
            }
        }
        if (tvec cx; isSigFIR(x, cx) && !isDependingOn(y, proj)) {
            if (Tree h, p; isSigClocked(cx[0], h, p) && p == proj) {
                return makeIIR(x, sigClocked(h, y));
            } else {
                return gGlobal->nil;
            }
        }
        return gGlobal->nil;
    }

    if (Tree x, y; isSigSub(def, x, y)) {
        // We don't handle this case directly, we transform it into an addition
        if (isSigFIR(y)) {
            return recdef2IIR(indentation, proj, sigAdd(x, negSigFIR(y)));
        }
        if (isSigFIR(x)) {
            return recdef2IIR(indentation, proj, sigAdd(x, sigNeg(y)));
        }
        return gGlobal->nil;
    }

    // the recursive definition can't be transformed into an IIR
    return gGlobal->nil;
}

static Tree proj2IIR(int indentation, Tree proj)
{
    int  i;
    Tree rg, var, le;

    faustassert(isProj(proj, &i, rg));
    faustassert(isRec(rg, var, le));
    Tree def = nth(le, i);
    return recdef2IIR(indentation, proj, def);
}
#endif
//----------------------------------------------------------------------
// IIRevealer : reveal IIR structures
//----------------------------------------------------------------------

class IIRRevealer : public SignalIdentity {
   protected:
    Tree postprocess(Tree L) override;
};

Tree IIRRevealer::postprocess(Tree sig)
{
    int p;

    if (Tree rgroup, var, le; isProj(sig, &p, rgroup) && isRec(rgroup, var, le) && !isNil(le)) {
        // we have a candidate for an IIR; ajouter une seul definition ???
        Tree def = nth(le, p);
        std::cerr << "def: " << *def << "\n";
        faustassert(isSigSum(def));
        std::vector<Tree> R, D, L;
        // We analyze the various terms of the sum
        for (Tree f : def->branches()) {
            // FIR[CLK(h,w), 0, c1, c2, ...]
            if (Tree h, w; isSigFIR(f) && isSigClocked(f->branch(0), h, w) && (w == sig)) {
                R.push_back(f);
            } else if (isDependingOn(f, sig)) {
                D.push_back(f);
            } else {
                L.push_back(f);
            }
        }
        if ((R.size() == 1) && (D.size() == 0) && (L.size() > 0)) {
            // we have a candidate for an IIR
            std::cerr << "we have a candidate1 for an IIRA!\n";
            tvec coef1, coef2;
            Tree ck, w;
            faustassert(isSigFIR(R[0], coef1));
            faustassert(isSigClocked(coef1[0], ck, w));
            Tree in = (L.size() == 1) ? L[0] : sigSum(L);
            coef2.push_back(gGlobal->nil);
            coef2.push_back(sigClocked(ck, in));
            for (unsigned int i = 1; i < coef1.size(); i++) {
                coef2.push_back(coef1[i]);
            }
            Tree iir = sigIIR(coef2);
            std::cerr << "makeIIRA1: " << *iir << "\n";
            std::cerr << "makeIIRA2: " << ppsig(iir) << "\n";
            return iir;
        }
    }
    return sig;
}

// External API

Tree revealIIR(Tree L1)
{
    IIRRevealer R;
    R.trace(TRACE, "NEW revealIIR");
    Tree L2 = R.mapself(L1);
    return L2;
}