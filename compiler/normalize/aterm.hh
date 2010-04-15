#ifndef __ATERM__
#define __ATERM__

#include <stdio.h>
#include <assert.h>
#include "tlib.hh"
#include "signals.hh"
#include "sigprint.hh"
#include "simplify.hh"
#include "normalize.hh"
#include "sigorderrules.hh"
#include <map>
#include <list>

#include "mterm.hh"

using namespace std;

/**
 * Implements a additive term, a set of mterms added together
 * m1 + m2 + m3 + ...
 */
class aterm
{

    map<Tree,mterm> fSig2MTerms;     			///< mapping between signatures and corresponding mterms

 public:
    aterm ();									///< create an empty aterm (equivalent to 0)
    aterm (Tree t);								///< create a aterm from an additive exp
    //aterm (const aterm& a);						///< create a copy of an aterm

    const aterm& operator += (Tree t);			///< add in place an additive expression tree
    const aterm& operator -= (Tree t);			///< add in place an additive expression tree
	
    const aterm& operator += (const mterm& m);	///< add in place an mterm
    const aterm& operator -= (const mterm& m);	///< add in place an mterm
	Tree normalizedTree() const;				///< return the corresponding normalized expression tree
	
	ostream& print(ostream& dst) const;			///< print a aterm m1 + m2 + m3 +...
	mterm greatestDivisor() const;				///< return the greatest divisor of any two mterms
	aterm factorize(const mterm& d);			///< reorganize the aterm by factorizing d
};

inline ostream& operator << (ostream& s, const aterm& a) { return a.print(s); }


#endif
