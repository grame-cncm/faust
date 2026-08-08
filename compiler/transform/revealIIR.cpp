#include "revealIIR.hh"
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include "ppsig.hh"
#include "sigFIR.hh"
#include "sigIIR.hh"
#include "sigIdentity.hh"
#include "signals.hh"

#include "DirectedGraph.hh"
#include "DirectedGraphAlgorythm.hh"
#include "Schedule.hh"
#include "sigRecursiveDependencies.hh"
#include "global.hh"
#include "simplify.hh"

// simplify() exige des termes clos : pendant la descente du revelateur,
// les sous-arbres d'un groupe recursif portent des references ouvertes
// (ref sans rec rempli) que la machinerie de reecriture refuse
// (rewrite.hh, body != nullptr). La garde derive du contrat : un terme
// non rec-free reste tel quel -- la simplification est une optimisation.
static Tree recSafeSimplify(Tree t)
{
    return t->isRecFree() ? simplify(t) : t;
}


// ---- port shims : this branch has no clock system. The source branch
// wraps clocked signals in sigClocked and its reveal rules unwrap them ;
// here the clocked patterns never match and wrappers are identities.
static inline bool isSigClocked(Tree, Tree&, Tree&)
{
    return false;
}
static inline Tree sigClocked(Tree, Tree s)
{
    return s;
}
static inline bool hasClock(Tree, Tree&)
{
    return false;
}



#define TRACE false

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
    return recSafeSimplify(sigMul(sigInt(-1), sig));
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

// Exact reachability on the CLOSED input tree : does f reach sig,
// descending recursive bodies, cycles cut by the seen-set. Group
// granularity (a projection's group body covers all its definitions) :
// a sound over-approximation of per-definition dependency. Used instead
// of isDependingOn because sigDependencies caches, in its global table,
// results truncated by the underVisit cycle guard -- on mutually
// recursive definitions an entry of the cycle keeps an incomplete set
// forever, and a candidacy accepted on that false independence re-enters
// the projection in flight (infinite recursion, order-sensitive). The
// open-body case cannot occur here (the input is fully closed) ; it is
// kept as a conservative safety.
static bool reachesConservative(Tree f, Tree sig, std::set<Tree>& seen)
{
    if (f == sig) {
        return true;
    }
    if (!seen.insert(f).second) {
        return false;
    }
    if (Tree var, body; isRec(f, var, body)) {
        if (body == nullptr) {
            return true;  // open group : unknown, assume dependency
        }
        return reachesConservative(body, sig, seen);
    }
    for (int k = 0; k < f->arity(); k++) {
        if (reachesConservative(f->branch(k), sig, seen)) {
            return true;
        }
    }
    return false;
}

static bool dependsOnConservative(Tree f, Tree sig)
{
    std::set<Tree> seen;
    return reachesConservative(f, sig, seen);
}

class IIRRevealer : public SignalIdentity {
   protected:
    Tree transformation(Tree L) override;
};

static long gRevealDepth = 0, gRevealMaxDepth = 0;

Tree IIRRevealer::transformation(Tree sig)
{
    struct DepthGuard {
        DepthGuard()
        {
            if (++gRevealDepth > gRevealMaxDepth) {
                gRevealMaxDepth = gRevealDepth;
                if ((gRevealMaxDepth & (gRevealMaxDepth - 1)) == 0 && gRevealMaxDepth >= 262144 &&
                    getenv("FAUST_SS_FIRDEBUG")) {
                    std::cerr << "SS_DEPTH " << gRevealMaxDepth << std::endl;
                }
            }
        }
        ~DepthGuard() { --gRevealDepth; }
    } guard;


    Tree var, le;
    if (isRec(sig, var, le)) {
        // rec protocol : ref() creates the (unique) virgin group, mapself
        // runs with the open reference registered, ONE rec() closes it
        Tree var2 = tree(unique("WI"));
        Tree rec2 = ref(var2);
        fResult.set(sig, rec2);
        Tree l2 = mapself(le);
        return rec(var2, l2);
    }

    int p;
    if (Tree rgroup; isProj(sig, &p, rgroup) && isRec(rgroup, var, le) && !isNil(le)) {
        // Internal or external occurrence ? While a group is being
        // renamed the memo maps it to a still-open reference : its
        // self-references stay plain projections, only external
        // occurrences are IIR candidates.
        Tree g2, v2, b2;
        bool inside = fResult.get(rgroup, g2) && isRec(g2, v2, b2) && (b2 == nullptr);
        if (!inside && isSigSum(nth(le, p))) {
            // Candidacy analysis on the INPUT tree : it is fully closed
            // and already in Sum-of-FIR form (revealFIR ran before), so
            // the real dependency machinery (sigRecursiveDependencies)
            // applies, and its global cache only ever sees closed terms.
            Tree              def = nth(le, p);
            std::vector<Tree> R, D, L;
            for (Tree f : def->branches()) {
                // clock-free pattern : FIR[w, 0, c1, c2, ...] whose
                // source w IS the projection itself (pointer equality,
                // guaranteed by hash-consing)
                if (isSigFIR(f) && (f->branch(0) == sig)) {
                    R.push_back(f);
                }
            }
            if (R.size() == 1) {
                // only a plausible candidate is worth the dependency
                // analysis (a transitive walk of the whole graph)
                for (Tree f : def->branches()) {
                    if (isSigFIR(f) && (f->branch(0) == sig)) {
                        continue;
                    }
                    if (dependsOnConservative(f, sig)) {
                        D.push_back(f);
                    } else {
                        L.push_back(f);
                    }
                }
            }
            if ((R.size() == 1) && (D.size() == 0) && (L.size() > 0)) {
                // def(Wi) = x + FIR[Wi, 0, c1, c2, ...] with x proven
                // independent of Wi : IIR[nil, x, 0, c1, c2, ...]. The
                // pieces cross to the output tree through self().
                tvec coef1, coef2;
                faustassert(isSigFIR(R[0], coef1));
                faustassert(coef1[0] == sig);
                // The COEFFICIENTS must be independent of Wi too : a
                // kernel whose coefficients read the state (drumkit's
                // saturating counters, y = (y' <= 14)*(...)) is a
                // NONLINEAR feedback, not an IIR -- and rebuilding such
                // a coefficient through self() would re-enter the
                // projection in flight (infinite recursion). fir18's
                // clock typing enforced control-rate coefficients ; the
                // clock-free port checks explicitly.
                bool coefsFree = true;
                for (unsigned int i = 1; i < coef1.size(); i++) {
                    if (dependsOnConservative(coef1[i], sig)) {
                        coefsFree = false;
                        break;
                    }
                }
                if (!coefsFree) {
                    return SignalIdentity::transformation(sig);
                }
                Tree in = (L.size() == 1) ? L[0] : sigSum(L);
                coef2.push_back(gGlobal->nil);
                coef2.push_back(self(in));
                for (unsigned int i = 1; i < coef1.size(); i++) {
                    coef2.push_back(self(coef1[i]));
                }
                return sigIIR(coef2);
            }
        }
        return SignalIdentity::transformation(sig);
    }

    return SignalIdentity::transformation(sig);
}

// External API

Tree revealIIR(Tree L1)
{
    IIRRevealer R;
    R.trace(TRACE, "NEW revealIIR");
    Tree L2 = R.mapself(L1);
    return L2;
}