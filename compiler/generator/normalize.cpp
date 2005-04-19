#include <stdio.h>
#include <assert.h>
#include "tlib.hh"
#include "signals.hh"
#include "sigprint.hh"
#include "simplify.hh"
#include "normalize.hh"
#include "sigorderrules.hh"
#include <map>

static void countAddTerm (map<Tree,Tree>& M, Tree t, bool invflag);
static void incTermCount (map<Tree,int>& M, Tree t, bool invflag);
static Tree buildPowTerm (Tree f, int q);
static Tree simplifyingAdd (Tree t1, Tree t2);
static Tree simplifyingMul (Tree t1, Tree t2);
static Tree simplifyingReorganizingMul(Tree t1, Tree t2);
static Tree reorganizingMul(Tree k, Tree t);

#undef TRACE

/**
 * Compute the Add-Normal form of a term t.
 * \param t the term to be normalized
 * \return the normalized term
 */	
Tree normalizeAddTerm(Tree t)
{
	assert(t!=0);
	map<Tree,Tree>	M;
	Tree			coef = tree(0);
	collectAddTerms(coef, M, t, false);
	Tree result = buildAddTerm(coef, M);
	//fprintf(stderr, "ADD Normalize -> "); printSignal(result, stderr); fputs("\n", stderr);
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
	
	map<Tree,int>	M;
	Tree			coef = tree(1);
	collectMulTerms(coef, M, t, false);
	Tree result = buildMulTerm(coef, M);
	//fprintf(stderr, "MUL Normalize -> "); printSignal(result, stderr); fputs("\n", stderr);
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
		// 0-x est equivalent -1*x est est traité de cette manière
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
		return pt;
	} else {
		return sigSub(pt,nt);
	}
}	

	
/**
 * Build an multiplicative term in normal form : (k*f1*f2*..fn)) / (g1*g2*...)
 * The terms are ordered so that constants are together, etc.
 */
Tree buildMulTerm(Tree k, map<Tree,int>& M)
{
	assert(k!=0);
	Tree t = tree(1.0);	// t will be ((F1.F2)..Fn)
	
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
		
	return simplifyingMul(k, t);
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
		
	} else {
		return sigAdd(t1, t2);
	}
}

static Tree reorganizingMul(Tree k, Tree t)
{
	Tree	x,y;
	if (isSigMul(t,x,y)) {
		return sigMul(reorganizingMul(k,x),y);
	} else if (isSigDiv(t,x,y)) {
		return sigDiv(reorganizingMul(k,x),y);
	} else {
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
	
	Tree result;
	
	if (isNum(t1) && isNum(t2)) {
		//fprintf(stderr, " [1] ");	
		result = mulNums(t1,t2);
		
	} else {
		// At most one number, makes sure it is t1
		if (isNum(t2)) {
			Tree tmp = t1; t1 = t2; t2 = tmp;
		}
		
		if (isNum(t1)) {
			if (isZero(t1)) {
				result = t1;

			} else if (isOne(t1)) {
				result = t2;
		
			} else {
				result = reorganizingMul(t1,t2);
			}

		} else {
			//fprintf(stderr, " [5] ");	
			result = sigMul(t1, t2);
		}
	}
	//printSignal(result, stderr); 
	//fprintf(stderr, " \n ");
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
		
	} else if (isZero(t1) || isZero(t1)) {
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
