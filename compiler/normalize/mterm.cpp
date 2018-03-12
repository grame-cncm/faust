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

#include "mterm.hh"
#include "signals.hh"
#include "ppsig.hh"
#include "xtended.hh"
#include "exception.hh"
#include "global.hh"

#undef TRACE

using namespace std;

typedef map<Tree,int> MP;

mterm::mterm ()            		: fCoef(sigInt(0)) {}
mterm::mterm (int k)            : fCoef(sigInt(k)) {}
mterm::mterm (double k)         : fCoef(sigReal(k)) {}	// cerr << "DOUBLE " << endl; }
mterm::mterm (const mterm& m)   : fCoef(m.fCoef), fFactors(m.fFactors) {}

/**
 * create a mterm from a tree sexpression
 */
mterm::mterm (Tree t) : fCoef(sigInt(1))
{
	#ifdef TRACE
    cerr << "mterm::mterm (Tree t) : " << ppsig(t) << endl;
	#endif
	*this *= t; 
	#ifdef TRACE
	cerr << "MTERM(" << ppsig(t) << ") -> " << *this << endl;
	#endif
}

/**
 * true if mterm doesn't represent number 0
 */
bool mterm::isNotZero() const
{
	return !isZero(fCoef);
}

/**
 * true if mterm doesn't represent number 0
 */
bool mterm::isNegative() const
{
	return !isGEZero(fCoef);
}

/**
 * print a mterm in a human readable format
 */
ostream& mterm::print(ostream& dst) const
{
	const char* sep = "";
	if (!isOne(fCoef) || fFactors.empty()) { dst << ppsig(fCoef); sep = " * "; }
	//if (true) { dst << ppsig(fCoef); sep = " * "; }
	for (MP::const_iterator p = fFactors.begin(); p != fFactors.end(); p++) {
		dst << sep << ppsig(p->first);
		if (p->second != 1) dst << "**" << p->second;
		sep = " * ";
	}
	return dst;
}

/**
 * Compute the "complexity" of a mterm, that is the number of
 * factors it contains (weighted by the importance of these factors)
 */
int mterm::complexity() const
{
    int c = isOne(fCoef) ? 0 : (isMinusOne(fCoef) ? 0 : 1);
	for (MP::const_iterator p = fFactors.begin(); p != fFactors.end(); ++p) {
		c += (1+getSigOrder(p->first))*abs(p->second);
	}
    //cerr << __LINE__ << ":" << __FUNCTION__ << "(" << *this << ") --> " << c << endl;
	return c;
}

/**
 * match x^p with p:int
 */
static bool isSigPow(Tree sig, Tree& x, int& n)
{
	//cerr << "isSigPow("<< *sig << ')' << endl;
	xtended* p = (xtended*) getUserData(sig);
	if (p == gGlobal->gPowPrim) {
       if (isSigInt(sig->branch(1), &n)) {
			x = sig->branch(0);
			//cerr << "factor of isSigPow " << *x << endl;
			return true;
		}
	}
	return false;
}

/**
 * produce x^p with p:int
 */
static Tree sigPow(Tree x, int p)
{
	return tree(gGlobal->gPowPrim->symbol(), x, sigInt(p));
}

/**
 * Multiple a mterm by an expression tree t. Go down recursively looking 
 * for multiplications and divisions
 */
const mterm& mterm::operator *= (Tree t)
{
	int		op, n;
	Tree	x,y;

	faustassert(t!=0);

	if (isNum(t)) {
		fCoef = mulNums(fCoef,t);

	} else if (isSigBinOp(t, &op, x, y) && (op == kMul)) {
		*this *= x;
		*this *= y;

	} else if (isSigBinOp(t, &op, x, y) && (op == kDiv)) {
		*this *= x;
		*this /= y;

	} else {
		if (isSigPow(t,x,n)) {
			fFactors[x] += n;
		} else {
			fFactors[t] += 1;
		}
	}
    return *this;
}

/**
 * Divide a mterm by an expression tree t. Go down recursively looking 
 * for multiplications and divisions
 */
const mterm& mterm::operator /= (Tree t)
{
	//cerr << "division en place : " << *this << " / " << ppsig(t) << endl;
	int		op,n;
	Tree	x,y;

	faustassert(t!=0);

	if (isNum(t)) {
        if (isZero(t)) {
            stringstream error;
            error << "ERROR : division by 0 in " << *this << " / " << ppsig(t) << endl;
            throw faustexception(error.str());
        }
		fCoef = divExtendedNums(fCoef,t);

	} else if (isSigBinOp(t, &op, x, y) && (op == kMul)) {
		*this /= x;
		*this /= y;

	} else if (isSigBinOp(t, &op, x, y) && (op == kDiv)) {
		*this /= x;
		*this *= y;

	} else {
		if (isSigPow(t,x,n)) {
			fFactors[x] -= n;
		} else {
			fFactors[t] -= 1;
		}
	}
    return *this;
}

/**
 * replace the content with a copy of m
 */
const mterm& mterm::operator = (const mterm& m)
{
	fCoef = m.fCoef;
	fFactors = m.fFactors;
    return *this;
}

/**
 * Clean a mterm by removing x**0 factors 
 */
void mterm::cleanup()
{
	if (isZero(fCoef)) {
		fFactors.clear();
	} else {
		for (MP::iterator p = fFactors.begin(); p != fFactors.end(); ) {
			if (p->second == 0) {
				fFactors.erase(p++);
			} else {
				p++;
			}
		}
	}
}

/**
 * Add in place an mterm. As we want the result to be
 * a mterm therefore essentially mterms of same signature can be added
 */
const mterm& mterm::operator += (const mterm& m)
{
	if (isZero(m.fCoef)) {
		// nothing to do
	} else if (isZero(fCoef)) 	{
		// copy of m
		fCoef = m.fCoef;
		fFactors = m.fFactors;
	} else {
		// only add mterms of same signature
		faustassert(signatureTree() == m.signatureTree());
		fCoef = addNums(fCoef, m.fCoef);
	}
	cleanup();
    return *this;
}

/**
 * Substract in place an mterm. As we want the result to be
 * a mterm therefore essentially mterms of same signature can be substracted
 */
const mterm& mterm::operator -= (const mterm& m)
{
	if (isZero(m.fCoef)) {
		// nothing to do
	} else if (isZero(fCoef)) 	{
		// minus of m
		fCoef = minusNum(m.fCoef);
		fFactors = m.fFactors;
	} else {
		// only add mterms of same signature
		faustassert(signatureTree() == m.signatureTree());
		fCoef = subNums(fCoef, m.fCoef);
	}
	cleanup();
    return *this;
}

/**
 * Multiply a mterm by the content of another mterm
 */
const mterm& mterm::operator *= (const mterm& m)
{
	fCoef = mulNums(fCoef,m.fCoef);
	for (MP::const_iterator p = m.fFactors.begin(); p != m.fFactors.end(); p++) {
		fFactors[p->first] += p->second;
	}
	cleanup();
    return *this;
}

/**
 * Divide a mterm by the content of another mterm
 */
const mterm& mterm::operator /= (const mterm& m)
{
	//cerr << "division en place : " << *this << " / " << m << endl;
	fCoef = divExtendedNums(fCoef,m.fCoef);
	for (MP::const_iterator p = m.fFactors.begin(); p != m.fFactors.end(); p++) {
		fFactors[p->first] -= p->second;
	}
	cleanup();
    return *this;
}

/**
 * Multiply two mterms
 */
mterm mterm::operator * (const mterm& m) const
{
    mterm r(*this);
    r *= m;
    return r;
}

/**
 * Divide two mterms
 */
mterm mterm::operator / (const mterm& m) const
{
    mterm r(*this);
    r /= m;
    return r;
}

/**
 * return the "common quantity" of two numbers
 */
static int common(int a, int b)
{
    if (a > 0 & b > 0) {
        return min(a,b);
    } else if (a < 0 & b < 0) {
        return max(a,b);
    } else {
        return 0;
    }
}

/**
 * return a mterm that is the greatest common divisor of two mterms
 */
mterm gcd (const mterm& m1, const mterm& m2)
{
	//cerr << "GCD of " << m1 << " and " << m2 << endl;

	Tree c = (sameMagnitude(m1.fCoef, m2.fCoef)) ? m1.fCoef : tree(1);		// common coefficient (real gcd not needed)
	mterm R(c);
	for (MP::const_iterator p1 = m1.fFactors.begin(); p1 != m1.fFactors.end(); p1++) {
        Tree t = p1->first;
		MP::const_iterator p2 = m2.fFactors.find(t);
		if (p2 != m2.fFactors.end()) {
			int v1 = p1->second;
			int v2 = p2->second;
            int c = common(v1,v2);
            if (c != 0) {
                R.fFactors[t] = c;
            }
        }
    }
	//cerr << "GCD of " << m1 << " and " << m2 << " is : " << R << endl;
	return R;
}

/**
 * We say that a "contains" b if a/b > 0. For example 3 contains 2 and
 * -4 contains -2, but 3 doesn't contains -2 and -3 doesn't contains 1
 */
static bool contains(int a, int b)
{
	return (b == 0) || (a/b > 0);
}

/**
 * Check if M accept N has a divisor. We can say that N is
 * a divisor of M if M = N*Q and the complexity is preserved :
 * complexity(M) = complexity(N)+complexity(Q)
 * x**u has divisor x**v if u >= v
 * x**-u has divisor x**-v if -u <= -v
 */
bool mterm::hasDivisor (const mterm& n) const
{
    if ( n.fFactors.size() == 0 ) {
        // n is a pure number
        return sameMagnitude(fCoef,n.fCoef);
    }
	for (MP::const_iterator p1 = n.fFactors.begin(); p1 != n.fFactors.end(); p1++) {
		// for each factor f**q of m
        Tree 	f = p1->first; 	
		int 	v = p1->second;
		
		// check that f is also a factor of *this
		MP::const_iterator p2 = fFactors.find(f);
		if (p2 == fFactors.end()) return false;
		
		// analyze quantities
		int u = p2->second;
		if (! contains(u,v) ) return false;
    }
    //cerr << __LINE__ << ":" << __func__ << *this << " is divisible by " << n << endl;
	return true;
}

/**
 * produce the canonical tree correspoding to a mterm
 */
 
/**
 * Build a power term of type f**q -> (((f.f).f)..f) with q>0
 */
static Tree buildPowTerm(Tree f, int q)
{
	faustassert(f);
	faustassert(q>0);
	if (q>1) {
		return sigPow(f, q);
	} else {
		return f;
	}
}

/**
 * Combine R and A doing R = R*A or R = A
 */
static void combineMulLeft(Tree& R, Tree A)
{
	if (R && A) 	R = sigMul(R,A);
	else if (A)		R = A;
    else throw faustexception("ERROR in combineMulLeft\n");
}

/**
 * Combine R and A doing R = R*A or R = A
 */
static void combineDivLeft(Tree& R, Tree A)
{
	if (R && A) 	R = sigDiv(R,A);
	else if (A)		R = sigDiv(tree(1.0f),A);
    else throw faustexception("ERROR in combineDivLeft\n");
}

/**	
 * Do M = M * f**q or D = D * f**-q
 */
static void combineMulDiv(Tree& M, Tree& D, Tree f, int q)
{
	#ifdef TRACE
	cerr << "combineMulDiv (" << M << "/"  << D << "*" << ppsig(f)<< "**" << q << endl;
	#endif
	if (f) {
        faustassert(q != 0);
		if (q > 0) {
			combineMulLeft(M, buildPowTerm(f,q));
		} else if (q < 0) {
			combineMulLeft(D, buildPowTerm(f,-q));
		}
	}
}	
	
/**
 * returns a normalized (canonical) tree expression of structure :
 * 		((v1/v2)*(c1/c2))*(s1/s2)
 */
Tree mterm::signatureTree() const
{
	return normalizedTree(true);
}
	
/**
 * returns a normalized (canonical) tree expression of structure :
 * 		((k*(v1/v2))*(c1/c2))*(s1/s2)
 * In signature mode the fCoef factor is ommited
 * In negativeMode the sign of the fCoef factor is inverted
 */
Tree mterm::normalizedTree(bool signatureMode, bool negativeMode) const
{
#ifdef TRACE
	cout << "normalizedTree " << *this << endl;
#endif

	if (fFactors.empty() || isZero(fCoef))
	{
		// it's a pure number
		if (signatureMode) 	return tree(1);
		if (negativeMode)	return minusNum(fCoef);
		else				return fCoef;
	} else {
		// it's not a pure number, it has factors
		Tree A[4], B[4];
		
		// group by order
		for (int order = 0; order < 4; order++) {
			A[order] = 0; B[order] = 0;
			for (auto p : fFactors)
			{
				Tree 	f = p.first;		// f = factor
				int		q = p.second;		// q = power of f
				if (f && q && getSigOrder(f)==order) {
					
					combineMulDiv (A[order], B[order], f, q);
				}
			}
		}
		#if 1
		if (A[0] != 0) cerr << "A[0] == " << *A[0] << endl; 
		if (B[0] != 0) cerr << "B[0] == " << *B[0] << endl; 
		// en principe ici l'order zero est vide car il correspond au coef numerique
		faustassert(A[0] == 0);
		faustassert(B[0] == 0);
		#endif
		
		// we only use a coeficient if it differes from 1 and if we are not in signature mode
		if (! (signatureMode || isOne(fCoef))) {
			A[0] = (negativeMode) ? minusNum(fCoef) : fCoef;
		}
		
		if (signatureMode) {
			A[0] = 0;
		} else if (negativeMode) {
			if (isMinusOne(fCoef)) { A[0] = 0; } else { A[0] = minusNum(fCoef); }
		} else if (isOne(fCoef)) {
			A[0] = 0;
		} else {
			A[0] = fCoef;
		}
					
		// combine each order separately : R[i] = A[i]/B[i]
		Tree RR = 0;
		for (int order = 0; order < 4; order++) {
			if (A[order] && B[order]) 	combineMulLeft(RR,sigDiv(A[order],B[order]));
			else if (A[order])			combineMulLeft(RR,A[order]);
			else if (B[order])			combineDivLeft(RR,B[order]);
		}
		if (RR == 0) RR = tree(1); // a verifier *******************
			
		faustassert(RR);
    #ifdef TRACE
        cout << "Normalized Tree of " << *this << " is " << ppsig(RR) << endl;
    #endif
		return RR;
	}
}

