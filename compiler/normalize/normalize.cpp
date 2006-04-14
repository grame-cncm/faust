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

static void countAddTerm (map<Tree,Tree>& M, Tree t, bool invflag);
static void incTermCount (map<Tree,int>& M, Tree t, bool invflag);
static Tree buildPowTerm (Tree f, int q);
static Tree simplifyingAdd (Tree t1, Tree t2);
static Tree simplifyingMul (Tree t1, Tree t2);
static Tree simplifyingReorganizingMul(Tree t1, Tree t2);
static Tree reorganizingMul(Tree k, Tree t);
static void factorizeAddTerm(map<Tree,Tree>& M);

#undef TRACE

/**
 * Compute the Add-Normal form of a term t.
 * \param t the term to be normalized
 * \return the normalized term
 */
Tree normalizeAddTerm(Tree t)
{
#ifdef TRACE
	fprintf(stderr, "START ADD Normalize of : "); printSignal(t, stderr); fputs("\n", stderr);
#endif
	assert(t!=0);
	map<Tree,Tree>	M;
	Tree			coef = tree(0);
	collectAddTerms(coef, M, t, false);
	factorizeAddTerm(M);
	Tree result = buildAddTerm(coef, M);
#ifdef TRACE
	fprintf(stderr, "END ADD Normalize -> "); printSignal(result, stderr); fputs("\n", stderr);
#endif
	return result;
}


/**
 * Compute the Mul-Normal form of a term t.
 * \param t the term to be normalized
 * \return the normalized term
 */
Tree normalizeMulTerm(Tree t)
{
	assert(t!=0);
#ifdef TRACE
	fprintf(stderr, "START MUL Normalize of : "); printSignal(t, stderr); fputs("\n", stderr);
#endif

	map<Tree,int>	M;
	Tree			coef = tree(1);
	collectMulTerms(coef, M, t, false);
	Tree result = buildMulTerm(coef, M);
#ifdef TRACE
	fprintf(stderr, "END MUL Normalize -> "); printSignal(result, stderr); fputs("\n", stderr);
#endif
	return result;
}


/**
 * Collects the added terms in the form (k0 + k1*f1 + k2*f2, ...)
 */

void collectAddTerms (Tree& coef, map<Tree,Tree>& M, Tree t, bool invflag)
{
	int		op;
	Tree	x,y;

	assert(t!=0);
	if (isSigBinOp(t, &op, x, y) && (op == kAdd)) {
		collectAddTerms(coef, M, x, invflag);
		collectAddTerms(coef, M, y, invflag);
	} else if (isSigBinOp(t, &op, x, y) && (op == kSub)) {
		collectAddTerms(coef, M, x, invflag);
		collectAddTerms(coef, M, y, !invflag);
	} else if (isNum(t)) {
		coef = (invflag) ? subNums(coef,t) : addNums(coef,t);
	} else {
		countAddTerm(M, normalizeMulTerm(t), invflag);
	}
}


/**
 * Collects the multiplied terms in the form (k0 * f1**k1 * f2**k2 * ...)
 */
void collectMulTerms (Tree& coef, map<Tree,int>& M, Tree t, bool invflag)
{
	int		op;
	Tree	x,y;

	assert(t!=0);

	if (isSigBinOp(t, &op, x, y) && (op == kMul)) {
		collectMulTerms(coef, M, x, invflag);
		collectMulTerms(coef, M, y, invflag);

	} else if (isSigBinOp(t, &op, x, y) && (op == kDiv)) {
		collectMulTerms(coef, M, x, invflag);
		collectMulTerms(coef, M, y, !invflag);


	} else if (isSigBinOp(t, &op, x, y) && (op == kSub) && isZero(x)) {
		// 0-x est equivalent -1*x est est trait�de cette mani�e
		coef = minusNum(coef);
		collectMulTerms(coef, M, y, invflag);

	} else if (isNum(t)) {
		coef = (invflag) ? divExtendedNums(coef,t) : mulNums(coef,t);

	} else {
		#if 0
		// check if recursive call to normalizeAddTerm is needed
		int		op;
		Tree	x,y;
		if (isSigBinOp(t, &op, x, y) && ((op == kAdd) || (op == kSub))) {
			t = normalizeAddTerm(t);
		}
		#endif
		incTermCount(M,t,invflag);
	}
}

/**
 * make a flat list (in a vector) of all the added terms of t
 */
static void flatListTerms(int op, vector<Tree>& v, Tree t)
{
	Tree	x, y;
	int		opcode;


	assert(t);

	if (isSigBinOp(t, &opcode, x, y) && opcode==op) {
		flatListTerms(op,v,x); flatListTerms(op,v,y);
	} else {
		v.push_back(t);
	}
}


/**
 * recursive build of a mid balanced tree of terms for operation op
 * between [lo..hi[ (hi excluded)
 */
static Tree buildMidBalancedTerm(int op, vector<Tree>& v, int lo, int hi)
{
	int q = hi-lo;
	assert(q>0);
	if (q == 1) {
		assert(lo < int(v.size()));
		return v[lo];
	} else {
		int mi = (hi+lo)/2;
		return sigBinOp( op, buildMidBalancedTerm(op,v,lo,mi), buildMidBalancedTerm(op,v,mi,hi) );
	}
}

/**
 * recursive build of a right balanced tree of terms for operation op
 * between [lo..hi[ (hi excluded)
 */
static Tree buildRightBalancedTerm(int op, vector<Tree>& v, int lo, int hi)
{
	int q = hi-lo;
	assert(q>0);
	if (q == 1) {
		assert(lo < int(v.size()));
		return v[lo];
	} else {
		return sigBinOp( op, v[lo], buildRightBalancedTerm(op,v,lo+1,hi));
	}
}

/**
 * recursive build of a left balanced tree of terms for operation op
 * between [lo..hi[ (hi excluded)
 */
static Tree buildLeftBalancedTerm(int op, vector<Tree>& v, int lo, int hi)
{
	int q = hi-lo;
	assert(q>0);
	if (q == 1) {
		assert(lo < int(v.size()));
		return v[lo];
	} else {
		return sigBinOp( op, buildLeftBalancedTerm(op,v,lo,hi-1), v[hi-1]);
	}
}


/**
 * create a balanced term for a certain binary operation op
 */
extern bool gBalancedSwitch;

static Tree balanceTerm(int op, Tree t)
{

	vector<Tree> v;

	flatListTerms(op, v, t);
	if (v.size() == 0) {
		return t;
	} else {
		switch (gBalancedSwitch) {
			case 0 : return buildLeftBalancedTerm(op, v, 0, v.size());
			case 1 : return buildMidBalancedTerm(op, v, 0, v.size());
			case 2 : return buildRightBalancedTerm(op, v, 0, v.size());

			default: return buildLeftBalancedTerm(op, v, 0, v.size());
		}
	}
}

/**
 * Build an additive term in normal form : (k+f1+f2+..fn) - (g1+g2+...)
 * The terms are ordered so that constants are together, etc.
 */
Tree buildAddTerm(Tree k, map<Tree,Tree>& M)
{
	Tree pt, nt;

	assert(k!=0);

	if (isGEZero(k)) {
		pt = k; nt = tree(0);
	} else {
		pt = tree(0); nt = minusNum(k);
	}

	for (int order = 0; order < 4; order++) {

		for (map<Tree,Tree>::iterator F = M.begin(); F != M.end(); F++) {
			Tree 	f = F->first;		// f = factor
			Tree	q = F->second;		// q = quantity

			if (getSigOrder(f)==order) {
				if (isGEZero(q)) {
					pt = simplifyingAdd(pt, simplifyingReorganizingMul(q,f));
				} else {
					nt = simplifyingAdd(nt, simplifyingReorganizingMul(minusNum(q),f));
				}
			}
		}
	}

	if (isZero(nt)) {
		return balanceTerm(kAdd, pt);
	} else {
		return sigSub(balanceTerm(kAdd, pt),balanceTerm(kAdd, nt));
	}
}


/**
 * Build an multiplicative term in normal form : (k*f1*f2*..fn)) / (g1*g2*...)
 * The terms are ordered so that constants are together, etc.
 */
Tree buildMulTerm(Tree k, map<Tree,int>& M)
{
	assert(k!=0);
	Tree t = tree(1.0f);	// t will be ((F1.F2)..Fn)

	for (int order = 0; order < 4; order++) {

		for (map<Tree,int>::iterator F = M.begin(); F != M.end(); F++) {
			Tree 	f = F->first;		// f = factor
			int		q = F->second;		// q = power of f

			if (getSigOrder(f)==order) {

				if (q > 0) {
					t = simplifyingMul(t, buildPowTerm(f,q));
				} else  if (q < 0) {
					t = sigDiv(t, buildPowTerm(f,-q));
				} else {
					// (q == 0), no changes in t
				}
			}
		}
	}

//	return simplifyingMul(k, t);
	return simplifyingMul(k, balanceTerm(kMul,t));
}


/**
 * Add a term k*f in additive map M and update its count M[f]+=k
 */
static void countAddTerm(map<Tree,Tree>& M, Tree t, bool invflag)
{
	assert(t!=0);
	Tree k, F;
	if (isSigMul(t, k, F) && isNum(k)) {
		//
	} else {
		k = tree(1);
		F = t;
	}
	if (invflag) { k = minusNum(k); }
	if (M.find(F) == M.end()) {
		M[F] = k;
	} else {
		M[F] = addNums(M[F],k);
	}
#ifdef TRACE
	fprintf(stderr, "countAddTerm of  ");
	printSignal(F, stderr);
	fprintf(stderr, " is ");
	printSignal(M[F], stderr);
	fprintf(stderr, "\n");
#endif
}


/**
 * Add a term p in the multiplicative map M and update its count M[f]+=1
 */
static void incTermCount(map<Tree,int>& M, Tree t, bool invflag)
{
	assert(t!=0);
	int c = (invflag) ? -1 : 1;
	if (M.find(t) == M.end()) {
		M[t] = c;
	} else {
		M[t] += c;
	}
#ifdef TRACE
	fprintf(stderr, "mult term coef of  ");
	printSignal(t, stderr);
	fprintf(stderr, " is *(%d) \n", M[t]);
#endif

}

// transform f**q into (((f.f).f)..f) with q>0
static Tree buildPowTerm(Tree f, int q)
{
	assert(f!=0);
	assert(q>0);
	Tree r = f;
	for (int c=2; c<=q; c++) { r = sigMul(r,f); }
	return r;
}


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

static Tree reorganizingMul(Tree k, Tree t)
{
	Tree	x,y;

	if (isNum(k) && isNum(t)) {
	#ifdef TRACE
		cerr << *k << " [[0]] " << *t << endl;
	#endif
		return mulNums(k,t);

	} else if (isSigMul(t,x,y)) {
	#ifdef TRACE
		cerr << " [[1]] " << endl;
	#endif
		return sigMul(reorganizingMul(k,x),y);
	} else if (isSigDiv(t,x,y)) {
	#ifdef TRACE
		cerr << *k << " [[2]] " << *t << endl;
	#endif
		return sigDiv(reorganizingMul(k,x),y);
	} else {
	#ifdef TRACE
		cerr << " [[end]] " << endl;
	#endif
		return sigMul(k,t);
	}
}

static Tree simplifyingReorganizingMul(Tree t1, Tree t2)
{
	assert(t1!=0);
	assert(t2!=0);
	#ifdef TRACE
	fprintf(stderr, "simplifying reorganizing Mul of  ");
	printSignal(t1, stderr);
	fprintf(stderr, " and ");
	printSignal(t2, stderr);
	fprintf(stderr, " -> ");
	#endif

	Tree result,x,y;

	if (isNum(t1) && isNum(t2)) {
		#ifdef TRACE
		fprintf(stderr, " [1] ");
		#endif
		result = mulNums(t1,t2);

	} else {
		// At most one number, makes sure it is t1
		if (isNum(t2)) {
			Tree tmp = t1; t1 = t2; t2 = tmp;
		}

		if (isNum(t1)) {
			if (isZero(t1)) {
				#ifdef TRACE
				fprintf(stderr, " [2] ");
				#endif
				result = t1;

			} else if (isOne(t1)) {
				#ifdef TRACE
				fprintf(stderr, " [3] ");
				#endif
				result = t2;

			} else if (isSigDiv(t2,x,y) && isNum(x)){
				#ifdef TRACE
				fprintf(stderr, " [4a] ");
				#endif
				result = sigDiv(simplifyingReorganizingMul(t1,x),y);

			} else {
				#ifdef TRACE
				fprintf(stderr, " [4b] ");
				#endif
				result = reorganizingMul(t1,t2);
			}

		} else {
			#ifdef TRACE
			fprintf(stderr, " [5] ");
			#endif
			result = sigMul(t1, t2);
		}
	}
	#ifdef TRACE
	printSignal(result, stderr);
	fprintf(stderr, " \n ");
	#endif
	return result;
}



static Tree simplifyingMul(Tree t1, Tree t2)
{
	assert(t1!=0);
	assert(t2!=0);
	#ifdef TRACE
	fprintf(stderr, "simplifying mult of  ");
	printSignal(t1, stderr);
	fprintf(stderr, " and ");
	printSignal(t2, stderr);
	fprintf(stderr, " -> ");
	#endif

	Tree result;

	if (isNum(t1) && isNum(t2)) {
		//fprintf(stderr, " [1] ");
		result = mulNums(t1,t2);

	} else if (isZero(t1) || isZero(t2)) {
		//fprintf(stderr, " [2] ");
		result = tree(0);

	} else if (isOne(t1)) {
		//fprintf(stderr, " [3] ");
		result = t2;

	} else if (isOne(t2)) {
		//fprintf(stderr, " [4] ");
		result = t1;

	} else {
		//fprintf(stderr, " [5] ");
		result = sigMul(t1, t2);
	}
	//printSignal(result, stderr);
	//fprintf(stderr, " \n ");
	return result;
}

typedef map<Tree,int> MT;

/*
static int intersectMapTerm(MT& M1, MT& M2, MT& R)
{
	int count = 0;
	for (MT::const_iterator e = M1.begin(); e != M1.end(); e++) {
		Tree t = e->first;
		if (M2.find(t) != M2.end() && !isOne(t) && !isMinusOne(t)) {
			int v1 = M1[t];
			int v2 = M2[t];
			if (v1*v2 > 0) {
				int c = min(v1,v2);
				count += c;
				R[t] = c;
			}
		}
	}
	return count;
}
*/

/*
static void divideMapTerm(MT& M1, MT& M2, MT& R)
{
	for (MT::const_iterator e = M2.begin(); e != M2.end(); e++) {
		Tree t = e->first;
		if (M1[t] > M2[t]) {
			R[t] = M1[t] - M2[t];
		}
	}
}
*/

/*
static int maxIntersect(list<MT>& LM, MT& E1, MT& E2, MT& I)
{
	int	Cmax = 0;
	for (list<MT>::iterator P1 = LM.begin(); P1 != LM.end(); P1++) {
		for (list<MT>::iterator P2 = P1; P2 != LM.end(); P2++) {
			if (P1 != P2) {
				MT 	J;
				int	c = intersectMapTerm(*P1, *P2, J);
				if (c > Cmax) {
					I = J;
					E1 = *P1;
					E2 = *P2;
					Cmax = c;
				}
			}
		}
	}

	return Cmax;
}
*/

/**
 * Factorize add terms : k1.k2.k4 + k2.k3.k4 -> (k1+k3).k2.k4
 * This is a very simple algorithm that factorise only common constants
 */

static void factorizeAddTerm(map<Tree,Tree>& MAT)
{
	map<Tree,Tree> 	INV;
	bool 			run;
	int				factorCount = 0;

	do {
		run = false;

		// clear INV and copy MAT inverted into INV
		INV.clear();
		for (map<Tree,Tree>::iterator i = MAT.begin(); i != MAT.end(); i++)
		{
			Tree f = i->first;
			Tree q = i->second;

			if (INV.find(q) == INV.end()) {
				INV[q] = f;
			} else {
				INV[q] 	= simplifyingAdd(INV[q], f);
#ifdef TRACE
				fprintf(stderr, "factor of : ");
				printSignal(q, stderr);
				fprintf(stderr, " is now : ");
				printSignal(INV[q], stderr);
				fputs("\n", stderr);
#endif
				factorCount++;
			}
		}

		// clear MAT and copy INV into MAT inverted
		MAT.clear();

		for (map<Tree,Tree>::iterator i = INV.begin(); i != INV.end(); i++)
		{
			Tree f = i->first;
			Tree q = i->second;

			if (MAT.find(q) == MAT.end()) {
				MAT[q] = f;
			} else {
				MAT[q] 	= simplifyingAdd(MAT[q], f);
				factorCount++;
				run 	= true;
			}
		}

	} while (run);
//
// 	if (factorCount > 0) {
// 		fprintf(stderr, "Factorisations achieved : %d\n", factorCount);
// 	}
}


/*
static void disabledfactorizeAddTerm(map<Tree,Tree>& MAT)
{
	list<MT>	L;
	MT			E1;
	MT			E2;
	MT			I;

	//Cree la liste des facteurs [q.f]
	for (map<Tree,Tree>::iterator F = MAT.begin(); F != MAT.end(); F++) {
		Tree f = F->first;
		Tree q = F->second;
		map<Tree,int> M;
		collectMulTerms(q, M, f, false);
// YO (21/04/05) : verification supprim� car les diff�ences relev� portaient
// essentiellement sur le type (1.000 != 1)
// 		if (q != F->second) {
// 			fprintf(stderr, "WARNING q!=F->second : ");
// 			printSignal(q, stderr); fprintf(stderr, " != ");
// 			printSignal(F->second, stderr); fprintf(stderr, "\n");
// 		}
//
//		//assert(q==F->second);

		if (!isOne(q)) {
			M[q] = 1;				// ajoute q aux facteurs
		}
		L.push_back(M);
	}

	// calcul l'intersection la plus grande
	int cmax = maxIntersect(L, E1, E2, I);
	if (cmax > 0) {
		//il y a une intersection
		fprintf(stderr, "Found intersection of size %d\n", cmax);
#if 0
		fprintf(stderr, " between : ");
		printSignal ( buildMulTerm(tree(1), E1), stderr );
		fprintf(stderr, "\n     and : ");
		printSignal ( buildMulTerm(tree(1), E2), stderr );
		fprintf(stderr, "\n     is  : ");
		printSignal ( buildMulTerm(tree(1), I), stderr );
		fprintf(stderr, "\n");
#endif
#if 0
		MT R1, R2;
		divideMapTerm(E1,I,R1);
		divideMapTerm(E2,I,R2);

		fprintf(stderr, "factorize 1 : ");
		printSignal ( buildMulTerm(tree(1), E1), stderr );
		fprintf(stderr, "\n");

		fprintf(stderr, "      as : ");
		printSignal ( buildMulTerm(tree(1), R1), stderr  );
		fprintf(stderr, " <times> ");
		printSignal ( buildMulTerm(tree(1), I), stderr  );
		fprintf(stderr, "\n\n");

		fprintf(stderr, "and factorize 2 : ");
		printSignal ( buildMulTerm(tree(1), E2), stderr  );
		fprintf(stderr, "\n");

		fprintf(stderr, "      as : ");
		printSignal ( buildMulTerm(tree(1), R2), stderr  );
		fprintf(stderr, " <times> ");
		printSignal ( buildMulTerm(tree(1), I), stderr  );
		fprintf(stderr, "\n");
#endif
	}

}
*/

/**
 * Compute the normal form of a fixed delay term (s@d).
 * The normalisation rules are :
 *		s@0 -> s
 *     	0@d -> 0
 *     	(k*s)@d -> k*(s@d)
 *		(s/k)@d -> (s@d)/k
 * Note that the same rules can't be applied to
 * + et - becaue the value of the first d samples
 * would be wrong. Would could also add delays such that
 * 		(s@d)@d' -> s@(d+d')
 * \param sig the whole term
 * \param s the term to be delayed
 * \param d the value of the delay
 * \return the normalized term
 */
Tree normalizeDelay1Term(Tree s)
{
	Tree x, y;

	if (isZero(s)) {

		return s;

	} else if (isSigMul(s, x, y)) {

		if (getSigOrder(x) < 2) {
			return simplify(sigMul(x,normalizeDelay1Term(y)));
		} else if (getSigOrder(y) < 2) {
			return simplify(sigMul(y,normalizeDelay1Term(x)));
		} else {
			return sigDelay1(s);
		}

	} else if (isSigDiv(s, x, y)) {

		if (getSigOrder(y) < 2) {
			return simplify(sigDiv(normalizeDelay1Term(x),y));
		} else {
			return sigDelay1(s);
		}

	} else {

		return sigDelay1(s);
	}
}

Tree normalizeFixedDelayTerm(Tree s, Tree d)
{
	Tree x, y;

	if (isZero(d)) {

		return s;

	} else if (isZero(s)) {

		return s;

	} else if (isSigMul(s, x, y)) {

		if (getSigOrder(x) < 2) {
			return simplify(sigMul(x,normalizeFixedDelayTerm(y,d)));
		} else if (getSigOrder(y) < 2) {
			return simplify(sigMul(y,normalizeFixedDelayTerm(x,d)));
		} else {
			return sigFixDelay(s,d);
		}

	} else if (isSigDiv(s, x, y)) {

		if (getSigOrder(y) < 2) {
			return simplify(sigDiv(normalizeFixedDelayTerm(x,d),y));
		} else {
			return sigFixDelay(s,d);
		}

	} else {

		return sigFixDelay(s,d);
	}
}


