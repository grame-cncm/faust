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
 
/**
 * \file eval.cpp
 * Implementation of the Block diagram evaluator.
 *
 * A strict lambda-calculus evaluator for block diagram expressions.
 *
 **/
 
 
#include "eval.hh"
#include <stdio.h>
#include "errormsg.hh"
#include "ppbox.hh"
#include "simplify.hh"
#include "propagate.hh"


// Private Declarations
//--------------
static Tree a2sb(int deep, Tree exp);
static Tree eval (Tree exp, Tree globalDefEnv, Tree visited, Tree localValEnv);
static Tree revEvalList (Tree lexp, Tree globalDefEnv, Tree visited, Tree localValEnv);
static Tree applyList (Tree fun, Tree larg);
static Tree iteratePar (Tree var, int num, Tree body, Tree globalDefEnv, Tree visited, Tree localValEnv);
static Tree iterateSeq (Tree id, int num, Tree body, Tree globalDefEnv, Tree visited, Tree localValEnv);
static Tree iterateSum (Tree id, int num, Tree body, Tree globalDefEnv, Tree visited, Tree localValEnv);
static Tree iterateProd (Tree id, int num, Tree body, Tree globalDefEnv, Tree visited, Tree localValEnv);
static Tree larg2par (Tree larg);
static int 	eval2int (Tree exp, Tree globalDefEnv, Tree visited, Tree localValEnv);
static const char * evalLabel (const char* l, Tree globalDefEnv, Tree visited, Tree localValEnv);


// Public Definitions
//----------------------


/**
 * Eval "process" from a list of definitions.
 * 
 * Strict evaluation of a block diagram expression by applying beta reduction.
 * @param eqlist a list of faust defintions forming the the global environment
 * @return the process block diagram in normal form
 */
Tree evalprocess (Tree eqlist)
{
	return a2sb(0, eval(boxIdent("process"), eqlist, nil, nil));
}
	

// Private Definitions
//--------------------

/**
 * Transform unused (unapplied) closures into symbolic boxes
 * 
 * @param exp the expression to transform
 * @return an expression where abstractions have been replaced by symbolic boxes
 */

static Tree a2sb(int deep, Tree exp)
{
	Tree abstr, globalDefEnv, visited, localValEnv, id, body;
	
	if (isClosure(exp, abstr, globalDefEnv, visited, localValEnv)) {
		if (!isBoxAbstr(abstr, id, body)) {
			evalerror(yyfilename, -1, " a2sb : internal error : not an abstraction inside closure ", exp);
			exit(1);
		}
		Tree slot = boxSlot(deep);
		return boxSymbolic(slot, a2sb(deep+1, eval(body, globalDefEnv, visited, pushEnv(id, slot, localValEnv))));
		
	} else {
		// it is a constructor : transform each branches
		Tree B[4]; 
		for (int i = 0; i < exp->arity(); i++) {
			B[i] = a2sb(deep, exp->branch(i));
		}
		
		return CTree::make(exp->node(), exp->arity(), B);
	}
}

/**
 * Eval a block diagram expression.
 * 
 * Strict evaluation of a block diagram expression by applying beta reduction.
 * @param exp the expression to evaluate
 * @param globalDefEnv the global environment
 * @param visited list of visited definition to detect recursive definitions
 * @param localValEnv the local environment
 * @return a block diagram in normal form
 */
static Tree eval (Tree exp, Tree globalDefEnv, Tree visited, Tree localValEnv)
{
	Tree 	val;
	Tree 	def;
	Tree 	fun;
	Tree 	arg;
	Tree	var, num, body, ldef;
	Tree 	label;
	Tree	cur, lo, hi, step;
	
	if (isBoxIdent(exp)) {
		
		if (searchEnv(exp, val, localValEnv)) {
			return val;
			
		} else if (isElement(exp, visited)) {
			evalerror(getDefFileProp(hd(visited)), getDefLineProp(hd(visited)), "recursive definition of ", exp);
			return boxError();
			
		} if (searchEnv(exp, def, globalDefEnv)) {
			//return eval(def, globalDefEnv, cons(exp,visited), nil);
			return eval(def, globalDefEnv, cons(exp,visited), localValEnv);
			
		} else {
			if (isNil(visited)) {
				evalerror(yyfilename, -1, "undefined symbol ", exp);
			} else {
				evalerror(getDefFileProp(hd(visited)), getDefLineProp(hd(visited)), "undefined symbol ", exp);
			}
			return boxError();
		}
	
	} else if (isBoxWithLocalDef(exp, body, ldef)) {
		return eval(body, concat(ldef, globalDefEnv), visited, localValEnv);
		
	} else if (isBoxFFun(exp)) {
		return exp;
		
	} else if (isBoxFConst(exp)) {
		return exp;
		
	} else if (isBoxButton(exp, label)) {
		const char* l1 = tree2str(label);
		const char* l2= evalLabel(l1, globalDefEnv, visited, localValEnv);
		//cout << "button label : " << l1 << " become " << l2 << endl;
		return (l1 == l2) ? exp : boxButton(tree(l2));
		
	} else if (isBoxCheckbox(exp, label)) {
		const char* l1 = tree2str(label);
		const char* l2= evalLabel(l1, globalDefEnv, visited, localValEnv);
		//cout << "check box label : " << l1 << " become " << l2 << endl;
		return (l1 == l2) ? exp : boxCheckbox(tree(l2));
		
	} else if (isBoxVSlider(exp, label, cur, lo, hi, step)) {
		const char* l1 = tree2str(label);
		const char* l2= evalLabel(l1, globalDefEnv, visited, localValEnv);
		//cout << "vslider label : " << l1 << " become " << l2 << endl;
		return (l1 == l2) ? exp : boxVSlider(tree(l2), cur, lo, hi, step);
		
	} else if (isBoxHSlider(exp, label, cur, lo, hi, step)) {
		const char* l1 = tree2str(label);
		const char* l2= evalLabel(l1, globalDefEnv, visited, localValEnv);
		//cout << "hslider label : " << l1 << " become " << l2 << endl;
		return (l1 == l2) ? exp : boxHSlider(tree(l2), cur, lo, hi, step);
		
	} else if (isBoxNumEntry(exp, label, cur, lo, hi, step)) {
		const char* l1 = tree2str(label);
		const char* l2= evalLabel(l1, globalDefEnv, visited, localValEnv);
		//cout << "num entry label : " << l1 << " become " << l2 << endl;
		return (l1 == l2) ? exp : boxNumEntry(tree(l2), cur, lo, hi, step);
		
	} else if (isBoxVGroup(exp, label, arg)) {
		const char* l1 = tree2str(label);
		const char* l2= evalLabel(l1, globalDefEnv, visited, localValEnv);
		//cout << "vgroup label : " << l1 << " become " << l2 << endl;
		return boxVGroup(tree(l2),	eval(arg, globalDefEnv, visited, localValEnv) );
		
	} else if (isBoxHGroup(exp, label, arg)) {
		const char* l1 = tree2str(label);
		const char* l2= evalLabel(l1, globalDefEnv, visited, localValEnv);
		//cout << "hgroup label : " << l1 << " become " << l2 << endl;
		return boxHGroup(tree(l2),	eval(arg, globalDefEnv, visited, localValEnv) );
		
	} else if (isBoxTGroup(exp, label, arg)) {
		const char* l1 = tree2str(label);
		const char* l2= evalLabel(l1, globalDefEnv, visited, localValEnv);
		//cout << "tgroup label : " << l1 << " become " << l2 << endl;
		return boxTGroup(tree(l2),	eval(arg, globalDefEnv, visited, localValEnv) );

	} else if (isBoxAppl(exp, fun, arg)) {
		// it is an application : do a strict evaluation
		return applyList(	eval(fun, globalDefEnv, visited, localValEnv),
							revEvalList(arg, globalDefEnv, visited, localValEnv) );
		
	} else if (isBoxAbstr(exp)) {
		// it is an abstraction : return a closure
		return closure(exp, globalDefEnv, visited, localValEnv);
		
	} else if (isBoxIPar(exp, var, num, body)) {
		int n = eval2int(num, globalDefEnv, visited, localValEnv);
		return iteratePar(var, n, body, globalDefEnv, visited, localValEnv);
		
	} else if (isBoxISeq(exp, var, num, body)) {
		int n = eval2int(num, globalDefEnv, visited, localValEnv);
		return iterateSeq(var, n, body, globalDefEnv, visited, localValEnv);
		
	} else if (isBoxISum(exp, var, num, body)) {
		int n = eval2int(num, globalDefEnv, visited, localValEnv);
		return iterateSum(var, n, body, globalDefEnv, visited, localValEnv);
		
	} else if (isBoxIProd(exp, var, num, body)) {
		int n = eval2int(num, globalDefEnv, visited, localValEnv);
		return iterateProd(var, n, body, globalDefEnv, visited, localValEnv);
		
	} else {
		// it is a constructor : evaluate each branches
		Tree B[4]; bool errflag = false;
		for (int i = 0; i < exp->arity(); i++) {
			B[i] = eval(exp->branch(i), globalDefEnv, visited, localValEnv);
			errflag |= isBoxError(B[i]);
		}
		
		return (errflag) ? boxError() : CTree::make(exp->node(), exp->arity(), B);
	}
}


/**
 * Eval a block diagram to an int.
 *
 * Eval a block diagram that represent an integer constant. This function first eval 
 * a block diagram to its normal form, then check it represent a numerical value (a 
 * block diagram of type : 0->1) then do a symbolic propagation and try to convert the 
 * resulting signal to an int.
 * @param exp the expression to evaluate
 * @param globalDefEnv the global environment
 * @param visited list of visited definition to detect recursive definitions
 * @param localValEnv the local environment
 * @return a block diagram in normal form
 */
static int eval2int (Tree exp, Tree globalDefEnv, Tree visited, Tree localValEnv)
{
	Tree diagram = eval(exp, globalDefEnv, visited, localValEnv);
	int numInputs, numOutputs;
	getBoxType(diagram, &numInputs, &numOutputs);
	if ( (numInputs > 0) || (numOutputs != 1) ) {
		evalerror (yyfilename, yylineno, "not a constant expression of type : (0->1)", exp);
		return 1;
	} else {
		Tree lsignals = boxPropagateSig(nil, diagram , makeSigInputList(numInputs) );
		Tree val = simplify(hd(lsignals));
		return tree2int(val);
	}
}

static bool isIdentChar(char c) 
{
	return (c >= 'a' & c <= 'z') || (c >= 'A' & c <= 'Z') || (c >= '0' & c <= '9') || (c == '_');
}

static char* writeIdentValue(char* dst, const char* ident, Tree globalDefEnv, Tree visited, Tree localValEnv)
{
	int n = eval2int(boxIdent(ident), globalDefEnv, visited, localValEnv);
	return dst + sprintf(dst, "%d", n);
}

static const char * evalLabel (const char* label, Tree globalDefEnv, Tree visited, Tree localValEnv)
{
	char 		res[2000];
	char 		ident[64];
	
	const char* src = &label[0];
	char*		dst = &res[0];
	char*		id  = &ident[0];
	
	bool		parametric = false;
	int 		state = 0;
	char		c;
	
	while ((c=*src++)) {
		if (state == 0) {
			if (c == '%') {
				state = 1;
				parametric = true;
				id  = &ident[0];
			} else {
				*dst++ = c;
			}
		} else {
			if (isIdentChar(c)) {
				*id++ = c;
			} else {
				*id = 0;
				dst = writeIdentValue(dst, ident, globalDefEnv, visited, localValEnv);
				state = 0;
				src -= 1;
			}
		}
	}
	
	if (state == 1) {
		*id = 0;
		dst = writeIdentValue(dst, ident, globalDefEnv, visited, localValEnv);
	}
	*dst = 0;
	return (parametric) ? strdup(res) : label;	
}



/**
 * Iterate a parallel construction
 *
 * Iterate a parallel construction such that : 
 * par(i,10,E) --> E(i<-0),E(i<-1),...,E(i<-9)
 * @param id the formal parameter of the iteration
 * @param num the number of iterartions
 * @param body the body expression of the iteration
 * @param globalDefEnv the global environment
 * @param visited list of visited definition to detect recursive definitions
 * @param localValEnv the local environment
 * @return a block diagram in normal form
 */
static Tree iteratePar (Tree id, int num, Tree body, Tree globalDefEnv, Tree visited, Tree localValEnv)
{
	Tree 	res;
	int 	i = 0;
	 
	if (i < num) {
		res = eval(body, globalDefEnv, visited, pushEnv(id, tree(i), localValEnv));
	}
	for (int i = 1; i < num; i++) {
		res = boxPar(res, eval(body, globalDefEnv, visited, pushEnv(id, tree(i), localValEnv)));
	}
		
	return res;
}



/**
 * Iterate a sequential construction
 *
 * Iterate a sequential construction such that : 
 * seq(i,10,E) --> E(i<-0):E(i<-1):...:E(i<-9)
 * @param id the formal parameter of the iteration
 * @param num the number of iterartions
 * @param body the body expression of the iteration
 * @param globalDefEnv the global environment
 * @param visited list of visited definition to detect recursive definitions
 * @return a block diagram in normal form
 */
static Tree iterateSeq (Tree id, int num, Tree body, Tree globalDefEnv, Tree visited, Tree localValEnv)
{
	Tree 	res;
	int 	i = 0;
	 
	if (i < num) {
		res = eval(body, globalDefEnv, visited, pushEnv(id, tree(i), localValEnv));
	}
	for (int i = 1; i < num; i++) {
		res = boxSeq(res, eval(body, globalDefEnv, visited, pushEnv(id, tree(i), localValEnv)));
	}
		
	return res;
}



/**
 * Iterate an addition construction
 *
 * Iterate an addition construction such that : 
 * par(i,10,E) --> E(i<-0)+E(i<-1)+...+E(i<-9)
 * @param id the formal parameter of the iteration
 * @param num the number of iterartions
 * @param body the body expression of the iteration
 * @param globalDefEnv the global environment
 * @param visited list of visited definition to detect recursive definitions
 * @param localValEnv the local environment
 * @return a block diagram in normal form
 */
static Tree iterateSum (Tree id, int num, Tree body, Tree globalDefEnv, Tree visited, Tree localValEnv)
{
	Tree 	res;
	int 	i = 0;
	 
	if (i < num) {
		res = eval(body, globalDefEnv, visited, pushEnv(id, tree(i), localValEnv));
	}
	for (int i = 1; i < num; i++) {
		res = boxSeq(boxPar(res, eval(body, globalDefEnv, visited, pushEnv(id, tree(i), localValEnv))),boxPrim2(sigAdd)) ;
	}
		
	return res;
}



/**
 * Iterate a product construction
 *
 * Iterate a product construction such that : 
 * par(i,10,E) --> E(i<-0)*E(i<-1)*...*E(i<-9)
 * @param id the formal parameter of the iteration
 * @param num the number of iterartions
 * @param body the body expression of the iteration
 * @param globalDefEnv the global environment
 * @param visited list of visited definition to detect recursive definitions
 * @param localValEnv the local environment
 * @return a block diagram in normal form
 */
static Tree iterateProd (Tree id, int num, Tree body, Tree globalDefEnv, Tree visited, Tree localValEnv)
{
	Tree 	res;
	int 	i = 0;
	 
	if (i < num) {
		res = eval(body, globalDefEnv, visited, pushEnv(id, tree(i), localValEnv));
	}
	for (int i = 1; i < num; i++) {
		res = boxSeq(boxPar(res, eval(body, globalDefEnv, visited, pushEnv(id, tree(i), localValEnv))),boxPrim2(sigMul)) ;
	}
		
	return res;
}



/**
 * Apply a function to a list of arguments
 *
 * Apply a function f to a list of arguments (a,b,c,...). 
 * If f is not an abstraction then we have :
 * f(a,b,c,...) ==> (a,b,c,...):f 
 * 
 * @param fun the function to apply
 * @param larg the list of arguments
 * @return the resulting expression in normal form
 */
static Tree applyList (Tree fun, Tree larg)
{
	Tree abstr;
	Tree globalDefEnv;
	Tree visited;
	Tree localValEnv;
	
	Tree id;
	Tree body;
	
	prim2	p2;
	
	if (isNil(larg)) return fun;
	
	if (isBoxError(fun) || isBoxError(larg)) { 
		return boxError();
	}
	
	if (!isClosure(fun, abstr, globalDefEnv, visited, localValEnv)) {
		if (isNil(tl(larg)) && isBoxPrim2(fun, &p2) && (p2 != sigPrefix)) {
			return boxSeq(boxPar(boxWire(), hd(larg)), fun);
		}
		return boxSeq(larg2par(larg), fun);
	}
	
	if (!isBoxAbstr(abstr, id, body)) {
		evalerror(yyfilename, -1, " not an abstraction inside closure ", fun);
		exit(1);
	}
	
	return applyList(eval(body, globalDefEnv, visited, pushEnv(id, hd(larg), localValEnv)), tl(larg));
		
}



/**
 * Eval a list of expression in reverse order
 *
 * Eval a list of expressions returning the list of results in reverse order.  
 * 
 * @param lexp list of expressions to evaluate
 * @param globalDefEnv the global environment
 * @param visited list of visited definition to detect recursive definitions
 * @param localValEnv the local environment
 * @return list of evaluated expressions in reverse order
 */
static Tree revEvalList (Tree lexp, Tree globalDefEnv, Tree visited, Tree localValEnv)
{
	Tree result = nil;
	while (!isNil(lexp)) {
		result = cons(eval(hd(lexp), globalDefEnv, visited, localValEnv), result);
		lexp = tl(lexp);
	}
	return result;
}



/**
 * Transform a list of expressions in a parallel construction
 *
 * Transform a list of expressions in a parallel construction  
 * 
 * @param larg list of expressions 
 * @return parallel construction
 */
static Tree larg2par (Tree larg)
{
	if (isNil(larg)) { 
		evalerror(yyfilename, -1, " empty list of arguments ", larg);
		exit(1);
	}
	if (isNil(tl(larg))) {
		return hd(larg);
	} 		
	return boxPar(hd(larg), larg2par(tl(larg)));
}		
