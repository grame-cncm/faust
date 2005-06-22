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
 #define TRACE

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

#include <assert.h>

// History
// 23/05/2005 : New environment management


//-------------- prototypes ---------------------------------------------------------
static Tree 	a2sb(int deep, Tree exp);
static Tree 	eval (Tree exp, Tree visited, Tree localValEnv);
static Tree 	revEvalList (Tree lexp, Tree visited, Tree localValEnv);
static Tree 	applyList (Tree fun, Tree larg);
static Tree 	iteratePar (Tree var, int num, Tree body, Tree visited, Tree localValEnv);
static Tree 	iterateSeq (Tree id, int num, Tree body, Tree visited, Tree localValEnv);
static Tree 	iterateSum (Tree id, int num, Tree body, Tree visited, Tree localValEnv);
static Tree 	iterateProd (Tree id, int num, Tree body, Tree visited, Tree localValEnv);
static Tree 	larg2par (Tree larg);
static int 		eval2int (Tree exp, Tree visited, Tree localValEnv);
static float	eval2float (Tree exp, Tree visited, Tree localValEnv);
static const char * evalLabel (const char* l, Tree visited, Tree localValEnv);

static Tree pushMultiClosureDefs(Tree ldefs, Tree visited, Tree lenv);
static Tree pushValueDef(Tree id, Tree def, Tree env);
static Tree evalIdDef(Tree id, Tree visited, Tree env);


// Public Interface
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
	//return a2sb(0, eval(boxIdent("process"), eqlist, nil, nil));
	return a2sb(0, eval(boxIdent("process"), nil, pushMultiClosureDefs(eqlist, nil, nil)));
}
	

// Private Implementation
//------------------------

/**
 * Transform unused (unapplied) closures into symbolic boxes
 * 
 * @param exp the expression to transform
 * @return an expression where abstractions have been replaced by symbolic boxes
 */

static Tree a2sb(int deep, Tree exp)
{
	Tree abstr, visited, unusedEnv, localValEnv, id, body;
	
	if (isClosure(exp, abstr, unusedEnv, visited, localValEnv)) {
		if (!isBoxAbstr(abstr, id, body)) {
			evalerror(yyfilename, -1, " a2sb : internal error : not an abstraction inside closure ", exp);
			exit(1);
		}
		Tree slot = boxSlot(deep);
		return boxSymbolic(slot, a2sb(deep+1, eval(body, visited, pushValueDef(id, slot, localValEnv))));
		
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
 * @param visited list of visited definition to detect recursive definitions
 * @param localValEnv the local environment
 * @return a block diagram in normal form
 */
static Tree eval (Tree exp, Tree visited, Tree localValEnv)
{
	Tree 	def;
	Tree 	fun;
	Tree 	arg;
	Tree	var, num, body, ldef;
	Tree 	label;
	Tree	cur, lo, hi, step;
	Tree	exp2, notused, visited2, lenv2;
	
	//cerr << "EVAL " << *exp << " (visited : " << *visited << ")" << endl;
	if (isBoxIdent(exp)) {
		return evalIdDef(exp, visited, localValEnv);
		
	} else if (isBoxWithLocalDef(exp, body, ldef)) {
		return eval(body, visited, pushMultiClosureDefs(ldef, visited, localValEnv));
		
	} else if (isBoxFFun(exp)) {
		return exp;
		
	} else if (isBoxFConst(exp)) {
		return exp;
		
	} else if (isBoxButton(exp, label)) {
		const char* l1 = tree2str(label);
		const char* l2= evalLabel(l1, visited, localValEnv);
		//cout << "button label : " << l1 << " become " << l2 << endl;
		return (l1 == l2) ? exp : boxButton(tree(l2));
		
	} else if (isBoxCheckbox(exp, label)) {
		const char* l1 = tree2str(label);
		const char* l2= evalLabel(l1, visited, localValEnv);
		//cout << "check box label : " << l1 << " become " << l2 << endl;
		return (l1 == l2) ? exp : boxCheckbox(tree(l2));
		
	} else if (isBoxVSlider(exp, label, cur, lo, hi, step)) {
		const char* l1 = tree2str(label);
		const char* l2= evalLabel(l1, visited, localValEnv);
		return boxVSlider(tree(l2), 
					tree(eval2float(cur, visited, localValEnv)), 
					tree(eval2float(lo, visited, localValEnv)), 
					tree(eval2float(hi, visited, localValEnv)), 
					tree(eval2float(step, visited, localValEnv)));
		
	} else if (isBoxHSlider(exp, label, cur, lo, hi, step)) {
		const char* l1 = tree2str(label);
		const char* l2= evalLabel(l1, visited, localValEnv);
		return boxHSlider(tree(l2), 
					tree(eval2float(cur, visited, localValEnv)), 
					tree(eval2float(lo, visited, localValEnv)), 
					tree(eval2float(hi, visited, localValEnv)), 
					tree(eval2float(step, visited, localValEnv)));
		
	} else if (isBoxNumEntry(exp, label, cur, lo, hi, step)) {
		const char* l1 = tree2str(label);
		const char* l2= evalLabel(l1, visited, localValEnv);
		return boxNumEntry(tree(l2), 
					tree(eval2float(cur, visited, localValEnv)), 
					tree(eval2float(lo, visited, localValEnv)), 
					tree(eval2float(hi, visited, localValEnv)), 
					tree(eval2float(step, visited, localValEnv)));
		
	} else if (isBoxVGroup(exp, label, arg)) {
		const char* l1 = tree2str(label);
		const char* l2= evalLabel(l1, visited, localValEnv);
		return boxVGroup(tree(l2),	eval(arg, visited, localValEnv) );
		
	} else if (isBoxHGroup(exp, label, arg)) {
		const char* l1 = tree2str(label);
		const char* l2= evalLabel(l1, visited, localValEnv);
		return boxHGroup(tree(l2),	eval(arg, visited, localValEnv) );
		
	} else if (isBoxTGroup(exp, label, arg)) {
		const char* l1 = tree2str(label);
		const char* l2= evalLabel(l1, visited, localValEnv);
		return boxTGroup(tree(l2),	eval(arg, visited, localValEnv) );
		
	} else if (isBoxHBargraph(exp, label, lo, hi)) {
		const char* l1 = tree2str(label);
		const char* l2= evalLabel(l1, visited, localValEnv);
		return boxHBargraph(tree(l2), 
					tree(eval2float(lo, visited, localValEnv)), 
					tree(eval2float(hi, visited, localValEnv)));
		
	} else if (isBoxVBargraph(exp, label, lo, hi)) {
		const char* l1 = tree2str(label);
		const char* l2= evalLabel(l1, visited, localValEnv);
		return boxVBargraph(tree(l2), 
					tree(eval2float(lo, visited, localValEnv)), 
					tree(eval2float(hi, visited, localValEnv)));

	} else if (isBoxAppl(exp, fun, arg)) {
		return applyList(	eval(fun, visited, localValEnv),
							revEvalList(arg, visited, localValEnv) );
		
	} else if (isBoxAbstr(exp)) {
		// it is an abstraction : return a closure
		return closure(exp, nil, visited, localValEnv);
		
	} else if (isClosure(exp, exp2, notused, visited2, lenv2)) {
	
		if (isBoxAbstr(exp2)) {
			// a 'real' closure
			return closure(exp2, nil, setUnion(visited,visited2), lenv2);
		} else {
			// it was a suspended evaluation
			return eval(exp2, setUnion(visited,visited2), lenv2);
		}
		
	} else if (isBoxIPar(exp, var, num, body)) {
		int n = eval2int(num, visited, localValEnv);
		return iteratePar(var, n, body, visited, localValEnv);
		
	} else if (isBoxISeq(exp, var, num, body)) {
		int n = eval2int(num, visited, localValEnv);
		return iterateSeq(var, n, body, visited, localValEnv);
		
	} else if (isBoxISum(exp, var, num, body)) {
		int n = eval2int(num, visited, localValEnv);
		return iterateSum(var, n, body, visited, localValEnv);
		
	} else if (isBoxIProd(exp, var, num, body)) {
		int n = eval2int(num, visited, localValEnv);
		return iterateProd(var, n, body, visited, localValEnv);
		
	} else {
		// it is a constructor : evaluate each branches
		Tree B[4]; bool errflag = false;
		for (int i = 0; i < exp->arity(); i++) {
			B[i] = eval(exp->branch(i), visited, localValEnv);
			errflag |= isBoxError(B[i]);
		}
		
		return (errflag) ? boxError() : CTree::make(exp->node(), exp->arity(), B);
	}
}


/**
 * Eval a block diagram to a float.
 *
 * Eval a block diagram that represent a float constant. This function first eval 
 * a block diagram to its normal form, then check it represent a numerical value (a 
 * block diagram of type : 0->1) then do a symbolic propagation and try to convert the 
 * resulting signal to a float.
 * @param exp the expression to evaluate
 * @param globalDefEnv the global environment
 * @param visited list of visited definition to detect recursive definitions
 * @param localValEnv the local environment
 * @return a block diagram in normal form
 */
static float eval2float (Tree exp, Tree visited, Tree localValEnv)
{
	Tree diagram = eval(exp, visited, localValEnv);
	int numInputs, numOutputs;
	getBoxType(diagram, &numInputs, &numOutputs);
	if ( (numInputs > 0) || (numOutputs != 1) ) {
		evalerror (yyfilename, yylineno, "not a constant expression of type : (0->1)", exp);
		return 1;
	} else {
		Tree lsignals = boxPropagateSig(nil, diagram , makeSigInputList(numInputs) );
		Tree val = simplify(hd(lsignals));
		return tree2float(val);
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
static int eval2int (Tree exp, Tree visited, Tree localValEnv)
{
	Tree diagram = eval(exp, visited, localValEnv);
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

static char* writeIdentValue(char* dst, const char* ident, Tree visited, Tree localValEnv)
{
	int n = eval2int(boxIdent(ident), visited, localValEnv);
	return dst + sprintf(dst, "%d", n);
}

static const char * evalLabel (const char* label, Tree visited, Tree localValEnv)
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
				dst = writeIdentValue(dst, ident, visited, localValEnv);
				state = 0;
				src -= 1;
			}
		}
	}
	
	if (state == 1) {
		*id = 0;
		dst = writeIdentValue(dst, ident, visited, localValEnv);
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
static Tree iteratePar (Tree id, int num, Tree body, Tree visited, Tree localValEnv)
{
	assert (num>0);
	 
	Tree res = eval(body, visited, pushValueDef(id, tree(0), localValEnv));
	for (int i = 1; i < num; i++) {
		res = boxPar(res, eval(body, visited, pushValueDef(id, tree(i), localValEnv)));
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
static Tree iterateSeq (Tree id, int num, Tree body, Tree visited, Tree localValEnv)
{
	assert (num>0);
	 
	Tree res = eval(body, visited, pushValueDef(id, tree(0), localValEnv));
	
	for (int i = 1; i < num; i++) {
		res = boxSeq(res, eval(body, visited, pushValueDef(id, tree(i), localValEnv)));
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
static Tree iterateSum (Tree id, int num, Tree body, Tree visited, Tree localValEnv)
{
	assert (num>0);
	 
	Tree res = eval(body, visited, pushValueDef(id, tree(0), localValEnv));
	
	for (int i = 1; i < num; i++) {
		res = boxSeq(boxPar(res, eval(body, visited, pushValueDef(id, tree(i), localValEnv))),boxPrim2(sigAdd)) ;
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
static Tree iterateProd (Tree id, int num, Tree body, Tree visited, Tree localValEnv)
{
	assert (num>0);
	 
	Tree res = eval(body, visited, pushValueDef(id, tree(0), localValEnv));
	
	for (int i = 1; i < num; i++) {
		res = boxSeq(boxPar(res, eval(body, visited, pushValueDef(id, tree(i), localValEnv))),boxPrim2(sigMul)) ;
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
		evalerror(yyfilename, -1, "(internal) not an abstraction inside closure", fun);
		exit(1);
	}
	
	//return applyList(eval(body, visited, pushValueDef(id, hd(larg), localValEnv)), tl(larg));
	return applyList(eval(body, visited, pushValueDef(id, eval(hd(larg), visited, localValEnv), localValEnv)), tl(larg));
		
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
static Tree revEvalList (Tree lexp, Tree visited, Tree localValEnv)
{
	Tree result = nil;
	while (!isNil(lexp)) {
		result = cons(eval(hd(lexp), visited, localValEnv), result);
		lexp = tl(lexp);
	}
	return result;
}



/**
 * Transform a list of expressions in a parallel construction
 * 
 * @param larg list of expressions 
 * @return parallel construction
 */
static Tree larg2par (Tree larg)
{
	if (isNil(larg)) { 
		evalerror(yyfilename, -1, "empty list of arguments", larg);
		exit(1);
	}
	if (isNil(tl(larg))) {
		return hd(larg);
	} 		
	return boxPar(hd(larg), larg2par(tl(larg)));
}		



//-----------------------new environment management----------------------------
//
// The environement is made of layers. Each layer contains a set of definitions
// stored as properties of the layer. Each definition can refers to other
// definitions of the same layer or of subsequent layers. Recursive
// definitions are not allowed. Multiple defintions of the same symbol
// in a layer is allowed but generate a warning when the definition is
// different
//-----------------------------------------------------------------------------



/**
 * Push a new (unique) empty layer (where multiple definitions can be stored)
 * on top of an existing environment.
 * @param lenv the old environment 
 * @return the new environment 
*/
static Tree pushNewLayer(Tree lenv) 
{
	return tree(unique("ENV_LAYER"), lenv);
}


/**
 * Add a definition (as a property) to the current top level layer. Check
 * and warn for multiple definitions.
 * @param id the symbol id to be defined 
 * @param def the definition to be binded to the symbol id
 * @param lenv the environment where to add this new definition
*/
static void addLayerDef(Tree id, Tree def, Tree lenv)
{
	// check for multiple definitions of a symbol in the same layer
	Tree olddef;
	if (getProperty(lenv, id, olddef)) {
		if (def == olddef) {
			evalwarning(getDefFileProp(id), getDefLineProp(id), "equivalent re-definitions of", id);
		} else {
			evalwarning(getDefFileProp(id), getDefLineProp(id), "non-equivalent re-definition of", id);
		}
	}
	setProperty(lenv, id, def);
}


/**
 * Push a new layer and add a single definition.
 * @param id the symbol id to be defined 
 * @param def the definition to be binded to the symbol id
 * @param lenv the environment where to push the layer and add the definition
 * @return the new environment
 */
static Tree pushValueDef(Tree id, Tree def, Tree lenv)
{
	Tree lenv2 = pushNewLayer(lenv);
	addLayerDef(id, def, lenv2);
	return lenv2;
}


/**
 * Push a new layer with multiple definitions creating the appropriate closures
 * @param ldefs list of pairs (symbol id x definition) to be binded to the symbol id
 * @param visited set of visited symbols (used for recursive definition detection)
 * @param lenv the environment where to push the layer and add all the definitions
 * @return the new environment
*/
static Tree pushMultiClosureDefs(Tree ldefs, Tree visited, Tree lenv)
{
	Tree lenv2 = pushNewLayer(lenv);
	while (!isNil(ldefs)) {
		Tree def = hd(ldefs);
		addLayerDef( hd(def), closure(tl(def),nil,visited,lenv2), lenv2 );
		ldefs = tl(ldefs);
	}
	return lenv2;
}



/**
 * Search the environment for the definition of a symbol
 * ID and evaluate it. Detects recursive definitions using
 * a set of visited IDxENV.
 * @param id the symbol ID t-o search
 * @param visited set of visited symbols (used for recursive definition detection)
 * @param lenv the environment where to search
 * @return the evaluated definition of ID
 */
static Tree evalIdDef(Tree id, Tree visited, Tree lenv)
{
	Tree def;
	
	// search the environment env for a definition of symbol id
	while (!isNil(lenv) && !getProperty(lenv, id, def)) {
		lenv = lenv->branch(0);
	}
	
	// check that the definition exists
	if (isNil(lenv)) {
		evalerror(getDefFileProp(id), getDefLineProp(id), "undefined symbol ", id);
		exit(1);
	}
		
	// check that it is not a recursive definition
	Tree p = cons(id,lenv);
	if (isElement(p, visited)) {
		evalerror(getDefFileProp(id), getDefLineProp(id), "recursive definition of", id);
		exit(1);
	}
	
	// return the evaluated definition
	return eval(def, addElement(p,visited), nil);
}


