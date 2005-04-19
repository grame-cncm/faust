#ifndef __FACTORIZE2__
#define __FACTORIZE2__

Tree normalizeAddTerm(Tree t);
Tree normalizeMulTerm(Tree t);

void collectAddTerms (Tree& coef, map<Tree,Tree>& M, Tree t, bool invflag);
void collectMulTerms (Tree& coef, map<Tree,int>& M, Tree t, bool invflag);

Tree buildAddTerm(Tree k, map<Tree,Tree>& M);
Tree buildMulTerm(Tree k, map<Tree,int>& M);

#endif
