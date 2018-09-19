/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <fstream>

#include "ppsig.hh"
#include "sigprint.hh"
#include "sigtype.hh"
//#include "prim.hh"
#include "prim2.hh"
#include "recursivness.hh"
#include "xtended.hh"

#include "Text.hh"
#include "sigraterules.hh"
#include "sigtyperules.hh"

//--------------------------------------------------------------------------
// Uncomment to activate type inference tracing

//#define TRACE(x) x
#define TRACE(x) 0;

/**

========================================== RATE INFERENCE =========================================
                                         [Public functions]


*/

/**************************************************************************************************

                                        Internal prototypes

 **************************************************************************************************/

static Tree     inferreMultiRates(Tree lsig1, bool& success);
static ostream& printRateEnvironment(ostream& fout, Tree E);
static ostream& printRateEnvironmentList(ostream& fout, Tree LE);
static void     doInferreRate(Tree sig, int* rate, Tree& renv);
static void     inferreRate(Tree sig, int* rate, Tree& E);
static Tree     addToMultiRates(Tree E1, Tree LE, bool& success);
static Tree     listRecursiveSignals(Tree lsig);
static Tree     doAddRecursiveSignals(Tree sig, Tree accSig);
static Tree     flatRateEnvironmentList(Tree lre);

/**************************************************************************************************
 **************************************************************************************************
 **************************************************************************************************

                                        Public Functions

 **************************************************************************************************
 **************************************************************************************************
 **************************************************************************************************/

/**
 * Inferre the rate of a list of signals.
 */
Tree inferreMultiRates(Tree lsig1, bool& success)
{
    vector<Tree> sigs;
    vector<Tree> envs;
    vector<int>  rates;

    Tree lsig2 = listRecursiveSignals(lsig1);
    TRACE(cerr << "lsig2 = " << *lsig2 << endl);

    while (isList(lsig2)) {
        Tree s = hd(lsig2);
        lsig2  = tl(lsig2);
        Tree E;
        int  r;
        inferreRate(s, &r, E);
        if (r == 0) {
            success = false;
            cerr << "ERROR inferreMultiRates failed 1" << endl;
            return nil;
        }
        sigs.push_back(s);
        envs.push_back(E);
        rates.push_back(r);
    }

    // combines all the rate environements
    Tree LE = nil;
    success = true;
    for (unsigned int i = 0; success && i < envs.size(); i++) {
        LE = addToMultiRates(envs[i], LE, success);
    }
    TRACE(cerr << "***multirates :"; printRateEnvironmentList(cerr, LE); cerr << endl);
    Tree RE = flatRateEnvironmentList(LE);
    TRACE(cerr << "***flat rate  :"; printRateEnvironment(cerr, RE); cerr << endl);

    return RE;
}

/**
 * Print a rate environment
 */
ostream& printRateEnvironment(ostream& fout, Tree E)
{
    string sep = "";
    fout << "rates {";
    while (isList(E)) {
        fout << sep << ppsig(hd(hd(E))) << ":" << tree2int(tl(hd(E)));
        sep = ",";
        E   = tl(E);
    }
    fout << "}";
    return fout;
}

/**
 * Print a list of rate environments
 */
ostream& printRateEnvironmentList(ostream& fout, Tree LE)
{
    string sep = "";
    fout << "multi{";
    while (isList(LE)) {
        fout << sep;
        printRateEnvironment(fout, hd(LE));
        sep = "++";
        LE  = tl(LE);
    }
    fout << "}";
    return fout;
}

/**************************************************************************************************
 **************************************************************************************************
 **************************************************************************************************

                                        IMPLEMENTATION

 **************************************************************************************************
 **************************************************************************************************
 **************************************************************************************************/

/**
 * Greatest common divisor
 */
static int TRACED_gcd(int a, int b);

static int gcd(int a, int b)
{
    int r = TRACED_gcd(a, b);
    // cerr << TABBER << "gcd(" << a << ',' << b <<") = " << r << endl;
    return r;
}

static int TRACED_gcd(int a, int b)
{
    return (b == 0) ? a : gcd(b, a % b);
}

/**
 * Least common multiple
 */
static int lcm(int a, int b)
{
    int r = (a * b) / gcd(a, b);
    // cerr << TABBER << "lcm(" << a << ',' << b <<") = " << r << endl;
    return r;
}

/**
 * list all recursive signals apprearing in lsig
 */

static Tree listRecursiveSignals(Tree lsig)
{
    CTree::startNewVisit();

    Tree lsig2 = lsig;
    while (isList(lsig)) {
        lsig2 = doAddRecursiveSignals(hd(lsig), lsig2);
        lsig  = tl(lsig);
    }
    return lsig2;
}

/**
 * partial list of recursive signals
 */

static Tree doAddRecursiveSignals(Tree sig, Tree accSig)
{
    TRACE(cerr << ++TABBER << "doAddRecursiveSignals(" << *sig << ',' << *accSig << ')' << endl);
    if (!sig->isAlreadyVisited()) {
        int  i;
        Tree rsig, id, body;
        sig->setVisited();
        if (isProj(sig, &i, rsig) && isRec(rsig, id, body)) {
            Tree p = nth(body, i);
            accSig = doAddRecursiveSignals(p, cons(p, accSig));
        } else {
            assert(!isProj(sig, &i, rsig));

            vector<Tree> subsigs;
            getSubSignals(sig, subsigs, false);
            for (unsigned int i = 0; i < subsigs.size(); i++) {
                accSig = doAddRecursiveSignals(subsigs[i], accSig);
            }
        }
    }
    TRACE(cerr << --TABBER << "doAddRecursiveSignals(" << *sig << ',' << *accSig << ") -> " << *accSig << endl);
    return accSig;
}

/** *********************************** RATE ENVIRONMENTS ************************************************

A rate environement E = {(s1,r1), (s2,r2), ...} is a set of pairs associating a signal and a rate. The
signals are unique : if (s1,r1) and (s2,r2) are in E then s1=s2 => r1=r2.

The environment is kept ordered


**********************************************************************************************************/

/**
 * Add a pair signal s1 x rate r1 to rate environment E
 */
static Tree addRateEnv(Tree s1, int r1, Tree E)
{
    if (isList(E)) {
        Tree s2 = hd(hd(E));
        if (s1 < s2) {
            return cons(cons(s1, tree(r1)), E);
        } else if (s1 == s2) {
            return cons(cons(s1, tree(r1)), tl(E));
        } else {
            return cons(hd(E), addRateEnv(s1, r1, tl(E)));
        }
    } else {
        return cons(cons(s1, tree(r1)), nil);
    }
}

/**
 * multiply by n all the rates of rate environment E
 * E={(s1,r1),...} -> E'={(s1,n.r1),...}
 */
static Tree TRACED_multRateEnv(int n, Tree E);

static Tree multRateEnv(int n, Tree E)
{
    TRACE(cerr << ++TABBER << "multRateEnv(" << n << ", " << *E << ")" << endl);
    Tree result = TRACED_multRateEnv(n, E);
    TRACE(cerr << --TABBER << "multRateEnv(" << n << ", " << *E << ") -> " << *result << endl);
    return result;
}

static Tree TRACED_multRateEnv(int n, Tree E)
{
    if (isList(E)) {
        Tree p = hd(E);
        Tree k = hd(p);
        int  r = tree2int(tl(p));
        Tree q = cons(k, tree(r * n));
        return cons(q, multRateEnv(n, tl(E)));
    } else {
        return nil;
    }
}

/**
 * Get value associated to key k in "function" l
 * returns true if a value was found.
 */

static bool getRateEnv(Tree k, int* i, Tree l)
{
    if (isNil(l)) {
        return false;
    } else {
        assert(isList(l));
        Tree r = hd(hd(l));
        if (k < r) {
            return false;  // not found
        } else if (k == r) {
            *i = tree2int(tl(hd(l)));
            return true;
        } else {
            return getRateEnv(k, i, tl(l));
        }
    }
}

/**
 * two rate environments are compatible if common rates
 * are linked by the same ratio
 */

static bool checkRatesCompatible(Tree R1, Tree R2, int n1, int n2)
{
    if (isNil(R1) || isNil(R2)) {
        return true;
    } else {
        Tree p1 = hd(R1);
        Tree p2 = hd(R2);

        Tree k1 = hd(p1);
        Tree k2 = hd(p2);

        if (k1 < k2) {
            return checkRatesCompatible(tl(R1), R2, n1, n2);
        } else if (k1 > k2) {
            return checkRatesCompatible(R1, tl(R2), n1, n2);
        } else {
            Tree v1 = tl(p1);
            Tree v2 = tl(p2);

            if (tree2int(v1) * n1 == tree2int(v2) * n2) {
                return checkRatesCompatible(tl(R1), tl(R2), n1, n2);
            } else {
                return false;
            }
        }
    }
}

/**
 * Two rate environments are independent if they don't have any
 * signals in common
 */

static bool areRatesIndependent(Tree R1, Tree R2)
{
    if (isNil(R1) || isNil(R2)) {
        return true;
    } else {
        Tree p1 = hd(R1);
        Tree p2 = hd(R2);

        Tree s1 = hd(p1);
        Tree s2 = hd(p2);

        if (s1 < s2) {
            return areRatesIndependent(tl(R1), R2);
        } else if (s2 < s1) {
            return areRatesIndependent(R1, tl(R2));
        } else {
            return false;  // s1 and s2 are in common
        }
    }
}

/**
 * Two rate environments are compatible if common rates
 * are linked by the same ratio
 */

static bool areRatesCompatible(Tree R1, Tree R2, int& n1, int& n2)
{
    if (isNil(R1) || isNil(R2)) {
        n1 = 1;
        n2 = 1;
        return true;

    } else {
        Tree p1 = hd(R1);
        Tree p2 = hd(R2);

        Tree k1 = hd(p1);
        Tree k2 = hd(p2);

        if (k1 < k2) {
            return areRatesCompatible(tl(R1), R2, n1, n2);

        } else if (k1 > k2) {
            return areRatesCompatible(R1, tl(R2), n1, n2);

        } else {
            // we have a common expression
            Tree v1 = tl(p1);
            Tree v2 = tl(p2);

            int r1 = tree2int(v1);
            int r2 = tree2int(v2);

            int m = lcm(r1, r2);

            // we update the n1 and n2 coefficients
            n1 = m / r1;
            n2 = m / r2;

            // and we check that the rest of the environments are compatible
            return checkRatesCompatible(tl(R1), tl(R2), n1, n2);
        }
    }
}

/**
 * Merge two compatible rate environments.  Rate environments are
 * compatible if common expressions have same rate.
 * Returns the merge environment and success flag
 */
static Tree TRACED_mergeRateEnvironment(Tree R1, Tree R2, bool& success);

static Tree mergeRateEnvironment(Tree R1, Tree R2, bool& success)
{
    TRACE(cerr << ++TABBER << "mergeRateEnvironment(" << *R1 << ", " << *R2 << ")" << endl);
    Tree result = TRACED_mergeRateEnvironment(R1, R2, success);
    if (success) {
        TRACE(cerr << --TABBER << "mergeRateEnvironment(" << *R1 << ", " << *R2 << ") -> " << *result << endl);
    } else {
        TRACE(cerr << --TABBER << "mergeRateEnvironment(" << *R1 << ", " << *R2 << ") -> FAILED" << endl);
    }
    return result;
}

static Tree TRACED_mergeRateEnvironment(Tree R1, Tree R2, bool& success)
{
    if (isNil(R1)) {
        success = true;
        return R2;

    } else if (isNil(R2)) {
        success = true;
        return R1;

    } else {
        Tree p1 = hd(R1);
        Tree p2 = hd(R2);

        Tree k1 = hd(p1);
        Tree k2 = hd(p2);

        if (k1 < k2) {
            return cons(p1, mergeRateEnvironment(tl(R1), R2, success));

        } else if (k2 < k1) {
            return cons(p2, mergeRateEnvironment(R1, tl(R2), success));

        } else {
            // we have a common expression
            Tree r1 = tl(p1);
            Tree r2 = tl(p2);

            if (r1 == r2) {
                // fine, same rate
                return cons(p2, mergeRateEnvironment(tl(R1), tl(R2), success));
            } else {
                success = false;
                return nil;
            }
        }
    }
}

/**
 * Merge a list of independent rate environments into a single rate environment
 */
static Tree flatRateEnvironmentList(Tree lre)
{
    Tree e       = nil;
    bool success = true;
    while (isList(lre)) {
        e = mergeRateEnvironment(hd(lre), e, success);
        assert(success);  // can't failed if environments are independant
        lre = tl(lre);
    }
    return e;
}

/**

========================================== RATE INFERENCE =========================================


*/

property<Tree> gInferreRateProperty;

static void setInferreRateProperty(Tree sig, int rate, Tree renv)
{
    gInferreRateProperty.set(sig, cons(tree(rate), renv));
}

static bool getInferreRateProperty(Tree sig, int* rate, Tree& renv)
{
    Tree p;
    if (gInferreRateProperty.get(sig, p)) {
        *rate = tree2int(hd(p));
        renv  = tl(p);
        return true;
    } else {
        return false;
    }
}

/**
 * Inferre rate (and rate environment) of a single signal.
 * Use a property to cache previous results
 */
static void inferreRate(Tree sig, int* rate, Tree& E)
{
    TRACE(cerr << ++TABBER << "inferreRate(" << ppsig(sig) << ")" << endl);
    if (!getInferreRateProperty(sig, rate, E)) {
        doInferreRate(sig, rate, E);
        setInferreRateProperty(sig, *rate, E);
    }
    TRACE(cerr << --TABBER << "inferreRate(" << ppsig(sig) << ") = " << *rate << " with " << *E << endl);
}

/**
 * Checks that w denotes a positive constant integer signal n
 * returns n or exit
 */
static int checkSignalDenotesSize(Tree w, Tree sig)
{
    // checks that w denotes a positive constant integer signal n
    SimpleType* st = isSimpleType(getCertifiedSigType(w));

    if (st && st->nature() == kInt) {
        interval i = st->getInterval();
        if (i.valid && i.lo >= 0 && i.lo == i.hi) {
            return int(i.lo);
        }
    }
    cerr << "ERROR in expression : " << ppsig(sig) << endl;
    cerr << *w << " is not a positive constant integer" << endl;
    exit(1);
}

/**
 * Inferre the rate (and the rate environment) of a signal.
 * A zero rate indicates an impossibility
 */
static void doInferreRate(Tree sig, int* rate, Tree& E)
{
    Tree w, x, rsig, id, body;
    int  i, in;

    if (isSigVectorize(sig, w, x)) {
        // -- rate(vectorize(n,x)) = rate(x)/n

        VectorType* vt = isVectorType(getCertifiedSigType(sig));
        assert(vt);
        int n = vt->size();
        assert(n > 0);

        int r;
        inferreRate(x, &r, E);
        if ((r % n) == 0) {
            // fine, the rate of x can be divided by n
            // (note: this is compatible with r==0 indicating that x has no rate)
            *rate = r / n;
        } else {
            // we need to scale the rates involved in x
            int m = lcm(n, r);
            *rate = m / n;
            E     = multRateEnv(m / r, E);
        }

    } else if (isSigDownSample(sig, x, w)) {
        // -- rate(down(n,x) = rate(x)/n

        int n = checkSignalDenotesSize(w, sig);

        int r;
        inferreRate(x, &r, E);

        if ((r % n) == 0) {
            // fine, the rate of x can be divided by n
            // (note: this is compatible with r==0 indicating that x has no rate)
            *rate = r / n;
        } else {
            // we need to scale the rates involved in x
            int m = lcm(n, r);
            *rate = m / n;
            E     = multRateEnv(m / r, E);
        }

    } else if (isSigUpSample(sig, x, w)) {
        // -- rate(up(x,n) = rate(x)*n

        int n = checkSignalDenotesSize(w, sig);
        int r;
        inferreRate(x, &r, E);
        *rate = r * n;

    } else if (isSigSerialize(sig, x)) {
        // -- rate(serialize(x) = rate(x)*n    [with Type(x) = vector(n,T)]

        VectorType* vt = isVectorType(getCertifiedSigType(x));
        assert(vt);

        int r;
        inferreRate(x, &r, E);
        *rate = vt->size() * r;

    } else if (isSigInput(sig, &in)) {
        // -- rate(input(x)) = 1

        *rate = 1;
        E     = addRateEnv(sig, 1, nil);

    } else if (isProj(sig, &i, rsig) && isRec(rsig, id, body)) {
        // -- rate(proj(i, x=(E0,E1,...))) = 1

        *rate = 1;
        E     = addRateEnv(sig, 1, nil);

    } else {
        // -- rate(op())        = 1
        // -- rate(op(s1, s2))  = lcm(rate(s1), rate(s2))

        vector<Tree> subsigs;
        unsigned int n = getSubSignals(sig, subsigs, false);

        if (n == 0) {
            // -- rate(op())        = 1
            *rate = 1;
            E     = nil;

        } else {
            // -- rate(op(s1, s2))  = lcm(rate(s1), rate(s2))

            vector<int>  subrates(n);
            vector<Tree> subenvs(n);

            int lcmrate = 1;
            for (unsigned int i = 0; i < n; i++) {
                inferreRate(subsigs[i], &subrates[i], subenvs[i]);
                lcmrate = lcm(subrates[i], lcmrate);
            }

            // Try to merge all (scaled) rate environments
            Tree M       = nil;
            bool success = false;

            for (unsigned int i = 0; i < n; i++) {
                M = mergeRateEnvironment(M, multRateEnv(lcmrate / subrates[i], subenvs[i]), success);
                if (!success) {
                    // merge failed
                    *rate = 0;
                    E     = nil;
                    return;
                }
            }
            // merge successful
            *rate = lcmrate;
            E     = M;
        }
    }
}

/**
 * Try to add a rate environment E1 to a list of independent rate environments LE
 * Returns a list of independent rate environments
 */
static Tree addToMultiRates(Tree E1, Tree LE, bool& success);
static Tree TRACED_addToMultiRates(Tree E1, Tree LE, bool& success);

static Tree addToMultiRates(Tree E1, Tree LE, bool& success)
{
    TRACE(cerr << ++TABBER << "addToMultiRates(" << *E1 << ", " << *LE << ")" << endl);
    Tree result = TRACED_addToMultiRates(E1, LE, success);
    if (success) {
        TRACE(cerr << --TABBER << "addToMultiRates(" << *E1 << ", " << *LE << ") -> " << *result << endl);
    } else {
        TRACE(cerr << --TABBER << "addToMultiRates(" << *E1 << ", " << *LE << ") -> FAILED" << endl);
    }
    return result;
}

static Tree TRACED_addToMultiRates(Tree E1, Tree LE, bool& success)
{
    if (isNil(LE)) {
        success = true;
        return cons(E1, nil);
    } else {
        Tree E2 = hd(LE);
        if (areRatesIndependent(E1, E2)) {
            return cons(E2, addToMultiRates(E1, tl(LE), success));
        } else {
            int n1, n2;
            if (areRatesCompatible(E1, E2, n1, n2)) {
                Tree M = mergeRateEnvironment(multRateEnv(n1, E1), multRateEnv(n2, E2), success);
                if (success) {
                    return addToMultiRates(M, tl(LE), success);
                } else {
                    return nil;
                }
            } else {
                return nil;
            }
        }
    }
}

RateInferrer::RateInferrer(Tree lsig)
{
    TRACE(cerr << "ENTRE RateInferrer constructor of " << *lsig << endl);
    if (!(isList(lsig) | isNil(lsig))) {
        lsig = cons(lsig, nil);
    }
    fFullList = listRecursiveSignals(lsig);
    fRateEnv  = inferreMultiRates(lsig, fSuccess);
    if (fSuccess) {
        fCommonRate = 1;
        // set the rate properties for the expressions in the environment
        // in order to be able to compute the other rates
        for (Tree L = fRateEnv; isList(L); L = tl(L)) {
            Tree p = hd(L);
            int  r = tree2int(tl(p));
            fRateProperty.set(hd(p), r);
            fCommonRate = lcm(fCommonRate, r);
        }

        // force computation of common rate
        for (Tree L = lsig; isList(L); L = tl(L)) {
            (void)rate(hd(L));
        }
        TRACE(std : cerr << "common rate is : " << fCommonRate << std::endl);

    } else {
        // rate inference failed
        fCommonRate = -1;
    }
    TRACE(cerr << "EXIT RateInferrer constructor" << *lsig << endl);
}

// returns the rate of sig assuming that sig is a subexpression of lsig
int RateInferrer::rate(Tree sig)
{
    int r;

    if (!fSuccess) {
        return 0;
    } else if (fRateProperty.get(sig, r)) {
        return r;
    } else {
        r = computeRate(sig);
        fRateProperty.set(sig, r);
        fCommonRate = lcm(fCommonRate, r);
        return r;
    }
}

int RateInferrer::computeRate(Tree sig)
{
    Tree n, x, rsig, id, body;
    int  i;

    if (isSigInput(sig, &i)) {
        TRACE(cerr << "ERROR: Input " << i << " should have a rate" << endl);
        return 0;

    } else if (isProj(sig, &i, rsig) && isRec(rsig, id, body)) {
        TRACE(cerr << "ERROR: Recursive signal " << *sig << " should have a rate" << endl);
        return 0;

    } else if (isSigVectorize(sig, n, x)) {
        VectorType* vt = isVectorType(getCertifiedSigType(sig));
        assert(vt);
        int rx = rate(x);
        int ry = vt->size();
        if ((rx % ry) != 0) {
            std::cerr << "ERROR : non integer rate " << rx << '/' << ry << " for signal " << ppsig(sig) << std::endl;
            exit(1);
        }
        return rx / ry;

    } else if (isSigSerialize(sig, x)) {
        VectorType* vt = isVectorType(getCertifiedSigType(x));
        assert(vt);
        return vt->size() * rate(x);

    } else if (isSigUpSample(sig, x, n)) {
        int i = checkSignalDenotesSize(n, sig);
        return rate(x) * i;

    } else if (isSigDownSample(sig, x, n)) {
        int i = checkSignalDenotesSize(n, sig);
        int r = rate(x);
        if ((r % i != 0)) {
            std::cerr << "DOWNSAMPLING ERROR : non integer rate " << r << '/' << i << " for signal " << ppsig(sig)
                      << std::endl;
            exit(1);
        }
        assert(r % i == 0);
        return r / i;

    } else {
        vector<Tree> subsigs;
        vector<int>  subrates;
        int          n = getSubSignals(sig, subsigs, false);
        if (n == 0) {
            // we don't depend of any subsignals, then the rate is 1
            return 1;
        } else {
            // we depend on subsignals, the rate is the highest one
            // moreover the highest one is a multiple of all other
            // rates
            int maxrate = 1;
            int lcmrate = 1;
            for (unsigned int i = 0; i < subsigs.size(); i++) {
                int r   = rate(subsigs[i]);
                maxrate = max(r, maxrate);
                lcmrate = lcm(r, lcmrate);
                if (lcmrate != maxrate) {
                    return 0;  // rates of arguments are incompatible
                }
            }
            return maxrate;
        }
    }
}

int RateInferrer::commonRate()
{
    return fCommonRate;
}

string RateInferrer::clock(Tree sig)  ///< returns sig's C clock expression : C_{r_i}(t) = (t*r_i)/r_c
{
    int p = periodicity(sig);
    if (p > 1) {
        return subst("(i/$0)", T(p));
    } else {
        return "i";
    }
}

string RateInferrer::tick(Tree sig)  ///< returns sig's C tick expression  : T_{r_i}(t) = ((t % (r_c/r_i)) == 0)
{
    int p = periodicity(sig);
    if (p > 1) {
        return subst("((i%$0)==0)", T(p));
    } else {
        return "true";
    }
}
