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



#include <stdio.h>
#include <assert.h>
#include <fstream>
#include <time.h>


#include "sigtype.hh"
#include "sigprint.hh"
#include "ppsig.hh"
//#include "prim.hh"
#include "prim2.hh"
#include "xtended.hh"
#include "recursivness.hh"

#include "sigtyperules.hh"
#include "sigraterules.hh"



/**

========================================== RATE INFERENCE =========================================


*/


/**
  * Greatest common divisor
  */
int gcd(int a, int b)
{
    return (b==0) ? a : gcd (b, a%b);
}

/**
  * Least common multiple
  */
int lcm(int a, int b)
{
    return (a*b)/gcd(a,b);
}




/**

========================================== RATE ENVIRONMENTS =========================================

A rate environement E = {(s1,r1), (s2,r2), ...} is a set of pairs associating a signal and a rate. The
signals are unique : if (s1,r1) and (s2,r2) are in E then s1=s2 => r1=r2.

The environment is kept ordered


*/




/**
  * Add a pair signal s1 x rate r1 to rate environment E
  */
Tree addRateEnv(Tree s1, int r1, Tree E)
{
    if (isList(E)) {
        Tree s2 = hd(hd(E));
        if (s1 < s2) {
            return cons(cons(s1,tree(r1)),E);
        } else if (s1 == s2) {
            return cons(cons(s1,tree(r1)),tl(E));
        } else {
            return cons(hd(E), addRateEnv(s1,r1,tl(E)));
        }
    } else {
        return cons(cons(s1,tree(r1)),nil);
    }
}


/**
  * multiply by n all the rates of rate environment E
  * E={(s1,r1),...} -> E'={(s1,n.r1),...}
  */
Tree multRateEnv(int n, Tree E)
{
    if (isList(E)) {
        Tree p = hd(E);
        Tree k = hd(p);
        int  r = tree2int(tl(p));
        Tree q = cons(k, tree(r*n));
        return cons(q, multRateEnv(n, tl(E)));
    } else {
        return nil;
    }
}


/**
  * Get value associated to key k in "function" l
  * returns true if a value was found.
  */

bool getRateEnv(Tree k, int* i, Tree l)
{
    if (isNil(l)) {
        return false;
    } else {
        assert (isList(l));
        Tree r = hd(hd(l));
        if (k < r) {
            return false;   // not found
        } else if (k == r) {
            *i = tree2int(tl(hd(l)));
            return true;
        } else {
            return getRateEnv(k,i,tl(l));
        }
    }
}



/**
  * two rate environments are compatible if common rates
  * are linked by the same ratio
  */

bool checkRatesCompatible(Tree R1, Tree R2, int n1, int n2)
{
    if (isNil(R1) || isNil(R2)) {
        return true;
    } else {
        Tree p1 = hd (R1);
        Tree p2 = hd (R2);

        Tree k1 = hd (p1);
        Tree k2 = hd (p2);

        if (k1 < k2) {
            return checkRatesCompatible(tl(R1), R2, n1, n2);
        } else if (k1 > k2) {
            return checkRatesCompatible(R1, tl(R2), n1, n2);
        } else {
            Tree v1 = tl (p1);
            Tree v2 = tl (p2);

            if (tree2int(v1)*n1 == tree2int(v2)*n2) {
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

bool areRatesIndependent(Tree R1, Tree R2)
{
    if (isNil(R1) || isNil(R2)) {
        return true;
    } else {
        Tree p1 = hd (R1);
        Tree p2 = hd (R2);

        Tree s1 = hd (p1);
        Tree s2 = hd (p2);

        if (s1 < s2) {
            return areRatesIndependent(tl(R1), R2);
        } else if (s2 < s1) {
            return areRatesIndependent(R1, tl(R2));
        } else {
            return false; // s1 and s2 are in common
        }
    }
}




/**
  * Two rate environments are compatible if common rates
  * are linked by the same ratio
  */

bool areRatesCompatible(Tree R1, Tree R2, int& n1, int& n2)
{
    if (isNil(R1) || isNil(R2)) {

        n1 = 1; n2 = 1;
        return true;

    } else {

        Tree p1 = hd (R1);
        Tree p2 = hd (R2);

        Tree k1 = hd (p1);
        Tree k2 = hd (p2);

        if (k1 < k2) {

            return areRatesCompatible(tl(R1), R2, n1, n2);

        } else if (k1 > k2) {

            return areRatesCompatible(R1, tl(R2), n1, n2);

        } else {

            // we have a common expression
            Tree v1 = tl (p1);
            Tree v2 = tl (p2);

            int  r1 = tree2int(v1);
            int  r2 = tree2int(v2);

            int  m = lcm(r1, r2);

            return checkRatesCompatible(tl(R1), tl(R2), m/r1, m/r2);
        }
    }
}


/**
  * Merge two compatible rate environments.  Rate environments are
  * compatible if common expressions have same rate.
  * Returns the merge environment and success flag
  */

Tree mergeRateEnvironment(Tree R1, Tree R2, bool& success)
{
    //cerr << ++TABBER << "mergeRateEnvironment (" << *R1 << ", " << *R2 << ")" << endl;

    if (isNil(R1)) {

        success = true;
        return R2;

    } else if (isNil(R2)) {

            success = true;
            return R1;

    } else {

        Tree p1 = hd (R1);
        Tree p2 = hd (R2);

        Tree k1 = hd (p1);
        Tree k2 = hd (p2);

        if (k1 < k2) {

            return cons(p1, mergeRateEnvironment(tl(R1), R2, success));

        } else if (k2 < k1) {

            return cons(p2, mergeRateEnvironment(R1, tl(R2), success));

        } else {

            // we have a common expression
            Tree r1 = tl (p1);
            Tree r2 = tl (p2);

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




property<int>   gComputeRateProperty;

static void setComputeRateProperty(Tree sig, Tree renv, int rate)
{
    gComputeRateProperty.set(cons(sig,renv),rate);
}

static bool getComputeRateProperty(Tree sig, Tree renv, int& rate)
{
    return gComputeRateProperty.get(cons(sig,renv),rate);
}


/**
 * Compute the rate of a signal according to a rate environment indicating rates for input signals
 * @param sig the signal we want to compute the rate
 * @param renv the rate environment
 * @return the type of sig according to environment env
 */
static int doComputeRate(Tree sig, Tree renv);

static int computeRate(Tree sig, Tree renv)
{
    int r;
    if (getComputeRateProperty(sig,renv,r)) {
        return r;
    } else {
        r = doComputeRate(sig, renv);
        setComputeRateProperty(sig, renv, r);
        return r;
    }
}

/**
  * We assume types have been computed. We will use them to compute the rates.
  */
static int doComputeRate(Tree sig, Tree renv)
{
    Tree    n, x;

    if ( isSigVectorize(sig, n, x) )  {

        VectorType* vt = isVectorType(getCertifiedSigType(sig));
        assert(vt);
        return computeRate(x,renv) / vt->size();

    } else if ( isSigSerialize(sig, x)) {

        VectorType* vt = isVectorType(getCertifiedSigType(x));
        assert(vt);
        return vt->size() * computeRate(x,renv);

    } else {

        vector<Tree> subsigs;
        vector<int> subrates;
        int n = getSubSignals(sig, subsigs, false);
        if (n == 0) {
            // we don't depend of any subsignals, then the rate is 1
            return 1;
        } else {
            // we depend on subsignals, the rate is the highest one
            // moreover the highest one is a multiple of all other
            // rates
            int maxrate = 1;
            int lcmrate = 1;
            for (unsigned int i=0; i<subsigs.size(); i++) {
                int r = computeRate(subsigs[i], renv);
                maxrate = max(r, maxrate);
                lcmrate = lcm(r, lcmrate);
                if (lcmrate != maxrate) {
                    return 0; // rates of arguments are incompatible
                }
            }
            return maxrate;
        }
    }
}



/**

========================================== RATE INFERENCE =========================================


*/


property<Tree>   gInferreRateProperty;

static void setInferreRateProperty(Tree sig, int rate, Tree renv)
{
    gInferreRateProperty.set(sig, cons(tree(rate),renv));
}

static bool getInferreRateProperty(Tree sig, int* rate, Tree& renv)
{
    Tree p;
    if (gInferreRateProperty.get(sig, p)) {
        *rate = tree2int(hd(p));
        renv = tl(p);
        return true;
    } else {
        return false;
    }
}

static void doInferreRate(Tree sig, int* rate, Tree& renv);

/**
  * Inferre rate (and rate environment) of a single signal.
  * Use a property to cache previous results
  */
static void inferreRate(Tree sig, int* rate, Tree& E)
{
    cerr << ++TABBER << "inferreRate(" << ppsig(sig) << ")" << endl;
    if (! getInferreRateProperty(sig, rate, E)) {
        doInferreRate(sig, rate, E);
        setInferreRateProperty(sig, *rate, E);
    }
    cerr << --TABBER << "inferreRate(" << ppsig(sig) << ") = " << *rate << " with " << *E << endl;
}


/**
  * Inferre the rate (and the rate environment) of a signal.
  * A zero rate indicates an impossibility
  */
static void doInferreRate(Tree sig, int* rate, Tree& E)
{
    Tree    w, x;
    int     in;

    if ( isSigVectorize(sig, w, x) )  {

        // -- rate(vectorize(n,x) = rate(x)/n

        VectorType* vt  = isVectorType(getCertifiedSigType(sig)); assert(vt);
        int         n   = vt->size(); assert(n>0);

        int r; inferreRate(x, &r, E);
        if ((r%n) == 0) {
            // fine, the rate of x can be divided by n
            // (note: this is compatible with r==0 indicating that x has no rate)
            *rate = r/n;
        } else {
            // we need to scale the rates involved in x
            int m = lcm(n,r);
            *rate = m/n;
            E = multRateEnv(m/r, E);
        }

    } else if ( isSigSerialize(sig, x)) {

        // -- rate(serialize(x) = rate(x)*n    [with Type(x) = vector(n,T)]

        VectorType* vt = isVectorType(getCertifiedSigType(x)); assert(vt);

        int r; inferreRate(x, &r, E);
        *rate = vt->size() * r;

    } else if ( isSigInput(sig, &in)) {

        // -- rate(input(x)) = 1

        *rate   = 1;
        E       = addRateEnv(sig,1,nil);

    } else {

        // -- rate(op())        = 1
        // -- rate(op(s1, s2))  = lcm(rate(s1), rate(s2))

        vector<Tree> subsigs;
        unsigned int n = getSubSignals(sig, subsigs, false);

        if (n == 0) {
            // -- rate(op())        = 1
           *rate = 1;
           E  = nil;

        } else {
            // -- rate(op(s1, s2))  = lcm(rate(s1), rate(s2))

            vector<int>     subrates(n);
            vector<Tree>    subenvs(n);

            int lcmrate = 1;
            for (unsigned int i=0; i<n; i++) {
                inferreRate(subsigs[i], &subrates[i], subenvs[i]);
                lcmrate = lcm(subrates[i], lcmrate);
            }

            // Try to merge all (scaled) rate environments
            Tree M = nil;
            bool success = false;

            for (unsigned int i=0; i<n; i++) {
                M = mergeRateEnvironment(M, multRateEnv(lcmrate/subrates[i], subenvs[i]), success);
                if (! success) {
                    // merge failed
                    *rate = 0; E = nil;
                    return;
                }
            }
            // merge successful
            *rate = lcmrate; E = M;
        }
    }
}


/**
  * Try to add a rate environment E1 to a list of independent rate environments LE
  * Returns a list of independent rate environments
  */
static Tree addToMultiRates(Tree E1, Tree LE, bool& success)
{
    if (isNil(LE)) {
        success = true;
        return cons(E1,nil);
    } else {
        Tree E2 = hd(LE);
        if (areRatesIndependent(E1,E2)) {
            return cons(E2, addToMultiRates(E1, tl(LE), success));
        } else {
            int n1, n2;
            if (areRatesCompatible(E1, E2, n1, n2)) {
                Tree M = mergeRateEnvironment(multRateEnv(n1,E1), multRateEnv(n2,E2), success);
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


/**
  * Print a rate environment
  */
ostream&  printRateEnvironment(ostream& fout, Tree E)
{
    string sep = "";
    fout << "rates{";
    while (isList(E)) {
        fout << sep << ppsig(hd(hd(E))) << ":" << tree2int(tl(hd(E)));
        sep=",";
        E = tl(E);
    }
    fout << "}";
    return fout;
}


/**
  * Print a list of rate environments
  */
ostream&  printRateEnvironmentList(ostream& fout, Tree LE)
{
    string sep = "";
    fout << "multi{";
    while (isList(LE)) {
        fout << sep; printRateEnvironment(fout, hd(LE));
        sep="++";
        LE = tl(LE);
    }
    fout << "}";
    return fout;
}


/**
  * Inferre the rate of a list of signals.
  */
Tree inferreMultiRates(Tree lsig, bool& success)
{
    vector<Tree>    sigs;
    vector<Tree>    envs;
    vector<int>     rates;

    while (isList(lsig)) {
        Tree s = hd(lsig); lsig = tl(lsig);
        Tree E; int r; inferreRate(s, &r, E);
        if (r==0) {
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
    for (unsigned int i=0; success && i<envs.size(); i++) {
        LE = addToMultiRates(envs[i], LE, success);
    }
    cerr << "multirates :" << *LE << endl;
    return LE;
}
