#include <stdio.h>
#include <assert.h>
#include "tlib.hh"
#include "signals.hh"
#include "sigprint.hh"
#include "ppsig.hh"
#include "simplify.hh"
#include "normalize.hh"
#include "sigorderrules.hh"
#include <map>
#include <list>

#include "mterm.hh"
#include "aterm.hh"

#if 0
static void countAddTerm (map<Tree,Tree>& M, Tree t, bool invflag);
static void incTermCount (map<Tree,int>& M, Tree t, bool invflag);
static Tree buildPowTerm (Tree f, int q);
static Tree simplifyingReorganizingMul(Tree t1, Tree t2);
static Tree reorganizingMul(Tree k, Tree t);
static void factorizeAddTerm(map<Tree,Tree>& M);
#endif

#undef TRACE

/**
 * Compute the Add-Normal form of a term t.
 * \param t the term to be normalized
 * \return the normalized term
 */
Tree normalizeAddTerm(Tree t)
{
#ifdef TRACE
	cerr << "START normalizeAddTerm : " << ppsig(t) << endl;
#endif
	
	aterm A(t);
	//cerr << "ATERM IS : " << A << endl;
	mterm D = A.greatestDivisor();
	while (D.isNotZero() && D.complexity() > 0) {
		//cerr << "GREAT DIV : " << D << endl;
		A = A.factorize(D);
		D = A.greatestDivisor();
	}
	return A.normalizedTree();
}


/**
 * Compute the normal form of a 1-sample delay term s'.
 * The normalisation rules are :
 *     	0' -> 0 /// INACTIVATE dec07 bug recursion
 *     	(k*s)' -> k*s'
 *		(s/k)' -> s'/k
 * \param s the term to be delayed by 1 sample
 * \return the normalized term
 */
Tree normalizeDelay1Term(Tree s)
{
	return normalizeFixedDelayTerm(s, tree(1));
}


/**
 * Compute the normal form of a fixed delay term (s@d).
 * The normalisation rules are :
 *		s@0 -> s
 *     	0@d -> 0
 *     	(k*s)@d -> k*(s@d)
 *		(s/k)@d -> (s@d)/k
 * 		(s@n)@m -> s@(n+m)
 * Note that the same rules can't be applied to
 * + et - becaue the value of the first d samples
 * would be wrong. We could also add delays such that
 * \param s the term to be delayed
 * \param d the value of the delay
 * \return the normalized term
 */

Tree normalizeFixedDelayTerm(Tree s, Tree d)
{
	Tree x, y, r;
	int i;

	if (isZero(d) && ! isProj(s, &i, r)) {

        return s;

	} else if (isZero(s)) {

        return s;

	} else if (isSigMul(s, x, y)) {

		if (getSigOrder(x) < 2) {
            return /*simplify*/(sigMul(x,normalizeFixedDelayTerm(y,d)));
		} else if (getSigOrder(y) < 2) {
            return /*simplify*/(sigMul(y,normalizeFixedDelayTerm(x,d)));
		} else {
			return sigFixDelay(s,d);
		}

	} else if (isSigDiv(s, x, y)) {

		if (getSigOrder(y) < 2) {
            return /*simplify*/(sigDiv(normalizeFixedDelayTerm(x,d),y));
		} else {
			return sigFixDelay(s,d);
		}

	} else if (isSigFixDelay(s, x, y)) {
		// (x@n)@m = x@(n+m)
//		return sigFixDelay(x,tree(tree2int(d)+tree2int(y)));
		return normalizeFixedDelayTerm(x,simplify(sigAdd(d,y))); 

	} else {

		return sigFixDelay(s,d);
	}
}

