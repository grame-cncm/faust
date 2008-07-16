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
	assert(t1!=0);
	assert(t2!=0);

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

Tree aterm::normalizedTree() const
{
	// store positive and negative tems by order and sign
	// positive terms are stored in P[]
	// negative terms are inverted (made positive) and stored in N[]
	Tree P[4], N[4];
	
	// prepare
	for (int order = 0; order < 4; order++) 	P[order] = N[order] = tree(0);
	
	// sum by order and sign
	for (SM::const_iterator p = fSig2MTerms.begin(); p != fSig2MTerms.end(); p++) {
		const mterm& m = p->second;	
		if (m.isNegative()) {
			Tree t = m.normalizedTree(false, true);
			int order = getSigOrder(t);
			N[order] = simplifyingAdd(N[order],t);
		} else {
			Tree t = m.normalizedTree();
			int order = getSigOrder(t);
			P[order] = simplifyingAdd(P[order],t);
		}
	}
	
	// combine sums
	Tree SUM = tree(0);
	for (int order = 0; order < 4; order++) {
		if (!isZero(P[order]))	{
			SUM = simplifyingAdd(SUM,P[order]);
		}
		if (!isZero(N[order])) 	{	// we have to substract
			if (isZero(SUM) && (order < 3)) {
				// we postpone substraction
				N[order+1] = simplifyingAdd(N[order], N[order+1]);
			} else {
				SUM = sigSub(SUM, N[order]);
			}
		}
	}
	
	assert(SUM);
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

	assert(t!=0);

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

	assert(t!=0);

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
	Tree sig = m.signatureTree();
	#ifdef TRACE
    cerr << "signature " << *sig << endl;
	#endif
	SM::const_iterator p = fSig2MTerms.find(sig);
	if (p == fSig2MTerms.end()) {
		// its a new mterm
		fSig2MTerms.insert(make_pair(sig,m));
	} else {
		fSig2MTerms[sig] += m;
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
	
	for (SM::const_iterator p1 = fSig2MTerms.begin(); p1 != fSig2MTerms.end(); p1++) {
		for (SM::const_iterator p2 = p1; p2 != fSig2MTerms.end(); p2++) {
			if (p2 != p1) {
				mterm g = gcd(p1->second,p2->second);
				if (g.complexity()>maxComplexity) {
					maxComplexity = g.complexity();
					maxGCD = g;
				}
			}
		}
	}
	//cerr << "greatestDivisor of " << *this << " is " << maxGCD << endl;
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



