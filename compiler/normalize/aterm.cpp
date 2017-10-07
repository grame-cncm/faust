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
 
#include "aterm.hh"
#include "ppsig.hh"
//static void collectMulTerms (Tree& coef, map<Tree,int>& M, Tree t, bool invflag=false);

#undef TRACE

using namespace std;

typedef map<Tree,mterm> SM;

aterm::aterm ()            
{}


/**
 * create a aterm from a tree expression
 */
aterm::aterm (Tree t)
{
#ifdef TRACE
	cerr << "aterm::aterm (" << ppsig(t)<< ")" << endl;
#endif
	*this += t;
#ifdef TRACE
    cerr << "aterm::aterm (" << ppsig(t)<< ") : -> " << *this << endl;
#endif
}
	

/**
 * Add two terms trying to simplify the result 
 */
static Tree simplifyingAdd(Tree t1, Tree t2)
{
	faustassert(t1!=0);
	faustassert(t2!=0);

	if (isNum(t1) && isNum(t2)) {
		return addNums(t1,t2);

	} else if (isZero(t1)) {
		return t2;

	} else if (isZero(t2)) {
		return t1;

	} else if (t1 <= t2) {
		return sigAdd(t1, t2);

	} else {
		return sigAdd(t2, t1);
	}
}

/**
 * return the corresponding normalized expression tree
 */

/*====================================================
 
 addTermsWithSign:
 
 (s1 v1 s2 v2) -> (s3 v3)
 
 (s1  0 s2 v2) -> (s2 v2)
 (s1 v1 s2  0) -> (s1 v1)
 (+  v1 +  v2) -> (+ (v1+v2))
 (+  v1 -  v2) -> (+ (v1-v2))
 (-  v1 +  v2) -> (+ (v2-v1))
 (-  v1 -  v2) -> (- (v1+v2))

 */

static void addTermsWithSign(bool p1, Tree v1, bool p2, Tree v2, bool& p3, Tree& v3)
{
    if (isZero(v1)) { p3=p2; v3=v2; return; }
    if (isZero(v2)) { p3=p1; v3=v1; return; }
    if (p1 & p2)    { p3=true;  v3=sigAdd(v1,v2); return; }
    if (p1)         { p3=true;  v3=sigSub(v1,v2); return; }
    if (p2)         { p3=true;  v3=sigSub(v2,v1); return; }
    else            { p3=false; v3=sigAdd(v1,v2); return; }
}

Tree aterm::normalizedTree() const
{
	// store positive and negative tems by order and sign
	// positive terms are stored in P[]
	// negative terms are inverted (made positive) and stored in N[]
	Tree    P[4], N[4];
    bool    hasPositiveTerm = false;
    bool    hasNegativeTerm = false;
	
    
	// prepare
	for (int order = 0; order < 4; order++) 	P[order] = N[order] = tree(0);
	
	// sum by order and sign
	for (SM::const_iterator p = fSig2MTerms.begin(); p != fSig2MTerms.end(); p++) {
		const mterm& m = p->second;	
		if (m.isNegative()) {
			Tree t = m.normalizedTree(false, true);
			int order = getSigOrder(t);
			N[order] = simplifyingAdd(N[order],t);
            hasNegativeTerm = true;
		} else {
			Tree t = m.normalizedTree();
			int order = getSigOrder(t);
			P[order] = simplifyingAdd(P[order],t);
            hasPositiveTerm = true;
		}
	}
    
    Tree SUM = subNums(P[0], N[0]);
    bool signe = true;
    Tree R;
    bool s;
    
    for (int order = 3; order > 0; order--) {
        
        addTermsWithSign(false, N[order], signe, SUM, s, R);
        signe=s;
        SUM=R;
        
        addTermsWithSign(true, P[order], signe, SUM, s, R);
        signe=s;
        SUM=R;
        
    }
    
    if (!signe) { SUM = sigSub(sigInt(0), SUM); }
#ifdef TRACE
    cerr << __LINE__ << ":" << __FUNCTION__ << "(" << *this << ") ---> " << ppsig(SUM) << endl;
#endif
	return SUM;
}
	

/**
 * print an aterm in a human readable format
 */
ostream& aterm::print(ostream& dst) const
{
    if (fSig2MTerms.empty()) {
        dst << "AZERO";
    } else {
        const char* sep = "";
        for (SM::const_iterator p = fSig2MTerms.begin(); p != fSig2MTerms.end(); p++) {
	        dst << sep << p->second;
	        sep = " + ";
        }
    }
 
	return dst;
}


/**
 * Add in place an additive expression tree Go down t recursively looking 
 * for additions and substractions
 */
const aterm& aterm::operator += (Tree t)
{
	int		op;
	Tree	x,y;

	faustassert(t!=0);

	if (isSigBinOp(t, &op, x, y) && (op == kAdd)) {
		*this += x;
		*this += y;

	} else if (isSigBinOp(t, &op, x, y) && (op == kSub)) {
		*this += x;
		*this -= y;

	} else {
		mterm m(t);
		*this += m;
	}
    return *this;
}


/**
 * Substract in place an additive expression tree Go down t recursively looking 
 * for additions and substractions
 */
const aterm& aterm::operator -= (Tree t)
{
	int		op;
	Tree	x,y;

	faustassert(t!=0);

	if (isSigBinOp(t, &op, x, y) && (op == kAdd)) {
		*this -= x;
		*this -= y;

	} else if (isSigBinOp(t, &op, x, y) && (op == kSub)) {
		*this -= x;
		*this += y;

	} else {
		mterm m(t);
		*this -= m;
	}
    return *this;
}


/**
 * Add in place an mterm
 */
const aterm& aterm::operator += (const mterm& m)
{
#ifdef TRACE
    cerr << *this << " aterm::+= " << m << endl;
#endif
	Tree signature = m.signatureTree();
#ifdef TRACE
    cerr << "signature " << *signature << endl;
#endif
	SM::const_iterator p = fSig2MTerms.find(signature);
	if (p == fSig2MTerms.end()) {
		// its a new mterm
		fSig2MTerms.insert(make_pair(signature,m));
	} else {
        // we already have a mterm of same signature, we add them together
		fSig2MTerms[signature] += m;
	}
	return *this;
}


/**
 * Substract in place an mterm
 */
const aterm& aterm::operator -= (const mterm& m)
{
    //cerr << *this << " aterm::-= " << m << endl;
	Tree sig = m.signatureTree();
    //cerr << "signature " << *sig << endl;
	SM::const_iterator p = fSig2MTerms.find(sig);
	if (p == fSig2MTerms.end()) {
		// its a new mterm
		fSig2MTerms.insert(make_pair(sig,m*mterm(-1)));
	} else {
		fSig2MTerms[sig] -= m;
	}
	return *this;
}
	
mterm aterm::greatestDivisor() const
{
	int maxComplexity = 0;
	mterm maxGCD(1);
    //cerr << "greatestDivisor of " << *this << endl;
    
	for (SM::const_iterator p1 = fSig2MTerms.begin(); p1 != fSig2MTerms.end(); p1++) {
		for (SM::const_iterator p2 = p1; p2 != fSig2MTerms.end(); p2++) {
			if (p2 != p1) {
				mterm g = gcd(p1->second,p2->second);
                //cerr << "TRYING " << g << " of complexity " << g.complexity() << " (max complexity so far " << maxComplexity << ")" << endl;
				if (g.complexity()>maxComplexity) {
					maxComplexity = g.complexity();
					maxGCD = g;
				}
			}
		}
	}
	//cerr << "greatestDivisor of " << *this << " --> " << maxGCD << endl;
	return maxGCD;
}

/**
 * reorganize the aterm by factorizing d
 */
aterm aterm::factorize(const mterm& d)
{
	//cerr << "factorize : " << *this << " with " << d << endl;
	aterm A;
	aterm Q;
	
	// separate the multiple of m from the others
	for (SM::const_iterator p1 = fSig2MTerms.begin(); p1 != fSig2MTerms.end(); p1++) {
		mterm t = p1->second;
		if (t.hasDivisor(d)) {
			mterm q = t/d;
			//cerr << "q = " << q << endl;
			Q += q;
			//cerr << "step Q = " << Q << endl;
		} else {
			A += t;
			//cerr << "step A = " << A << endl;
		}
	}
	
	// combines the two parts
	//cerr << "d.normalizedTree() " << ppsig(d.normalizedTree()) << endl;
	//cerr << "Q.normalizedTree() " << ppsig(Q.normalizedTree()) << endl;
	//Tree tt = sigMul(d.normalizedTree(), Q.normalizedTree());
	//cerr << "tt " << *tt << endl;
	
	//Tree ttt = sigAdd(
	A += sigMul(d.normalizedTree(), Q.normalizedTree());
	//cerr << "Final A = " << A << endl;
	//cerr << "Final Tree " << *(A.normalizedTree()) << endl;
	return A;
}



