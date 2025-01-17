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

#define TRACE false

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
 * be transformed into an IIR
 *
 * @param indentation
 * @param proj: proj(i,rec(var,le))
 * @return an IIR or nil
 */
static Tree proj2IIR(int indentation, Tree proj)
{
    int  i;
    Tree rg, var, le, x0, y0;

    faustassert(isProj(proj, &i, rg));
    faustassert(isRec(rg, var, le));
    Tree def = nth(le, i);
    // std::cerr << std::string(indentation, '\t') << "proj2IIR: " << ppsig(def) << "\n";
    if (isSigAdd(def, x0, y0)) {
        auto [clocked, clock, x1, y1] = unclock(x0, y0);

        if (tvec cy; isSigFIR(y1, cy) && cy[0] == proj) {
            if (!isDependingOn(x1, proj)) {
                if (clocked) {
                    return makeIIR(y1, sigClocked(clock, x1));
                }
                return makeIIR(y1, x1);
            } else {
                return gGlobal->nil;
            }
        } else if (tvec cx; isSigFIR(x1, cx) && cx[0] == proj) {
            if (!isDependingOn(y1, proj)) {
                if (clocked) {
                    return makeIIR(x1, sigClocked(clock, y1));
                }
                return makeIIR(x1, y1);
            } else {
                return gGlobal->nil;
            }
        } else {
            return gGlobal->nil;
        }
    }

    else if (isSigSub(def, x0, y0)) {
        auto [clocked, clock, x1, y1] = unclock(x0, y0);

        if (tvec cy; isSigFIR(y1, cy) && cy[0] == proj) {
            if (!isDependingOn(x1, proj)) {
                if (clocked) {
                    return makeIIR(negSigFIR(y1), sigClocked(clock, x1));
                }
                return makeIIR(negSigFIR(y1), x1);
            } else {
                return gGlobal->nil;
            }
        } else if (tvec cx; isSigFIR(x1, cx) && cx[0] == proj) {
            if (!isDependingOn(y1, proj)) {
                if (clocked) {
                    return makeIIR(x1, sigClocked(clock, sigNeg(y1)));
                }
                return makeIIR(x1, sigNeg(y1));
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
        traceMsg("T1 We have a recursive projection", sig);
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
            traceMsg("T2 We have a recursive projection, but definitions are nil", sig);
            return sig;  // SignalIdentity::transformation(sig);
        }
    } else {
        return SignalIdentity::transformation(sig);
    }
}

// External API

Tree revealIIR(Tree L1)
{
    IIRRevealer R;
    R.trace(TRACE, "NEW revealIIR");
    Tree L2 = R.mapself(L1);
    return L2;
}