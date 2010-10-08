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



#include <stdio.h>
#include <assert.h>
#include "sigtype.hh"
#include "sigprint.hh"
#include "ppsig.hh"
//#include "prim.hh"
#include "prim2.hh"
#include "tlib.hh"
#include "sigtyperules.hh"
#include "xtended.hh"
#include "recursivness.hh"


//--------------------------------------------------------------------------
// prototypes

static Type getInferredType(Tree term, Tree env);
static Type infereSigType(Tree term, Tree env);
static Type infereFFType (Tree ff, Tree ls, Tree env);
static Type infereFConstType (Tree type);
static Type infereFVarType (Tree type);
static Type infereRecType (Tree var, Tree body, Tree env);
static Type infereReadTableType(Type tbl, Type ri);
static Type infereWriteTableType(Type tbl, Type wi, Type wd);
static Type infereProjType(Type t, int i, int vec);
static Type infereXType(Tree sig, Tree env);
static Type infereDocConstantTblType(Type size, Type init);
static Type infereDocWriteTblType(Type size, Type init, Type widx, Type wsig);
static Type infereDocAccessTblType(Type tbl, Type ridx);
static Type infereVectorizeType(Tree sig, Tree env, Tree s1, Tree s2);
static Type infereSerializeType(Tree sig, Tree env, Tree s);
static Type infereConcatType(Tree sig, Tree env, Tree s1, Tree s2);
static Type infereVectorAtType(Tree sig, Tree env, Tree s1, Tree s2);



//static Tree addEnv(Tree var, Tree tt, Tree env);
//static void markSigType(Tree sig, Tree env);

/***********************************************
 * Set and get the type property of a signal
 * (we suppose the signal have been previously
 * annotated with type information)
 ***********************************************/

Tree TYPEPROPERTY = tree(symbol("TypeProperty"));

/**
 * set the type annotation of sig
 * @param sig the signal we want to type
 * @param t the type of the signal
 */
void setSigType(Tree sig, Type t)
{
	//cerr << "setSigType(" << *sig << ", " << t << ")" << endl;
	//setProperty(sig, TYPEPROPERTY, tree((void*)t));
	sig->setType(t);
}


/**
 * retrieve the type annotation of sig
 * @param sig the signal we want to know the type
 */
Type getSigType(Tree sig)
{
	AudioType* t = (AudioType*) sig->getType();
	if (t==0) {
		cerr << "ERROR in getSigType : no type information available for signal :" << *sig << endl;
		exit(1);
	}
	return t;
}




/**************************************************************************
 	Type Environments : type environmpent are needed to correctly
	infere the type of an "open" term containing recursive references
	to an enclosing term. Type environments are also used as a property
	key to store already computed types
***************************************************************************/


/**
 * The empty type environment (also property key for closed term type)
 */
Tree NULLENV = tree(symbol("NullEnv"));



/**
 * add a new binding to a type environment
 * @param var the variable
 * @param type the type of the variable
 * @param env the type environment
 * @result a new environment : [(var,type):env]
 */
Tree addEnv(Tree var, Type tp, Tree env)
{
	Tree r = cons(cons(var,tree((AudioType*)tp)),env);
	return r;
}


/**
 * search for the type associated to a variable
 * @param env the type environment
 * @param var the variable to search
 * @result the type associated to var in env
 */
Type searchEnv(Tree env, Tree var)
{
	while ( (env != NULLENV) && (hd(hd(env)) != var) ) { env = tl(env); }
	if (env == NULLENV) {
		cerr << "Problem in searchEnv "; print(var, stderr);
		cerr << " was not found" << endl;
		assert(env != NULLENV);	// we should have found the data
	}

	return Type((AudioType*)tree2ptr(tl(hd(env))));
}



/**
 * search for the type associated to a variable
 * @param env the type environment (a list of pair(var,type))
 * @param var the variable to search
 * @param val where to put his type
 * @result true when var has an associated type in env
 */
static bool isInEnv(Tree env, Tree var, Type& val)
{
	while ( (env != NULLENV) && (hd(hd(env)) != var) ) { env = tl(env); }
	if (env == NULLENV) return false;
	val = Type((AudioType*)tree2ptr(tl(hd(env))));
	return true;
}


/**************************************************************************

 						Type Inference System

***************************************************************************/


/**
 * fully annotate every subtree of term with type information
 * @param sig the signal term tree to annotate
 */
void typeAnnotation(Tree sig)
{
	getInferredType(sig, NULLENV);
}



/**
 * Retrieve or infere the type of a term according to its surrounding type environment
 * @param sig the signal to analyze
 * @param env the type environment
 * @return the type of sig according to environment env
 */
Type getInferredType(Tree term, Tree env)
{
    AudioType* at = (AudioType*) term->getType();
    if (at) {
        return at;
    } else {
        Tree    tt;
		if (!getProperty(term, env, tt)) {
			Type tp;
			if (!isInEnv(env, term, tp)) {
				Type t = infereSigType(term, env);
				if (env == NULLENV) {
					setSigType(term, t);					// the result is sure
				} else {
					setProperty(term, env, tree((void*)t));	// the result depends of hypothesis
				}
				return t;
			} else {
				return tp;
			}
		}
	    Type rt((AudioType*)tree2ptr(tt));
	    return rt;
    }
}


/**
 * Shortcut to getSigType, retrieve or infere the type of a term according to its surrounding type environment
 * @param sig the signal to analyze
 * @param env the type environment
 * @return the type of sig according to environment env
 * @see getSigType
 */
Type T(Tree term, Tree env)
{
	Type t = getInferredType(term, env);
	return t;
}



/**
 * Compute the resulting interval of an arithmetic operation
 * @param op code of the operation
 * @param s1 interval of the left operand
 * @param s2 interval of the right operand
 * @return the resulting interval
 */

static interval __arithmetic (int opcode, const interval& x, const interval& y)
{
	switch (opcode) {
		case kAdd: return x+y;
		case kSub: return x-y;
		case kMul:	return x*y;
		case kDiv: return x/y;
		case kRem: return x%y;
		case kLsh: return x<<y;
		case kRsh: return x>>y;
		case kGT:  return x>y;
		case kLT:  return x<y;
		case kGE:  return x>=y;
		case kLE:  return x<=y;
		case kEQ:  return x==y;
		case kNE:	return x!=y;
		case kAND:	return x&y;
		case kOR:  return x|y;
		case kXOR: return x^y;
		default:
			cerr << "Unrecognized opcode : " << opcode << endl;
			exit(1);
	}

	return interval();
}

static interval arithmetic (int opcode, const interval& x, const interval& y)
{
	interval r = __arithmetic(opcode,x,y);
	return r;
}


/**
 * Infere the type of a term according to its surrounding type environment
 * @param sig the signal to aanlyze
 * @param env the type environment
 * @return the type of sig according to environment env
 */

static Type infereSigType(Tree sig, Tree env)
{
	int 		i;
	double 		r;
    Tree		sel, s1, s2, s3, ff, id, ls, l, x, y, z, u, var, body, type, name, file;
	Tree		label, cur, min, max, step;


		 if ( getUserData(sig) ) 			return infereXType(sig, env);

	else if (isSigInt(sig, &i))			return new SimpleType(kInt, kKonst, kComp, kVect, kNum, interval(i));

	else if (isSigReal(sig, &r)) 			return new SimpleType(kReal, kKonst, kComp, kVect, kNum, interval(r));

	else if (isSigInput(sig, &i))			return new SimpleType(kReal, kSamp, kExec, kVect, kNum, interval());

	else if (isSigDelay1(sig, s1)) 			{
		Type t = T(s1,env);
		return castInterval(sampCast(t), reunion(t->getInterval(), interval(0,0)));
	}

	else if (isSigPrefix(sig, s1, s2)) 		{
		Type t1 = T(s1,env);
		Type t2 = T(s2,env);
		checkInit(t1);
		return castInterval(sampCast(t1|t2), reunion(t1->getInterval(), t2->getInterval()));
	}

	else if (isSigFixDelay(sig, s1, s2)) 		{
		Type t1 = T(s1,env);
		Type t2 = T(s2,env);
		interval i = t2->getInterval();

/*		cerr << "for sig fix delay : s1 = "
				<< t1 << ':' << ppsig(s1) << ", s2 = "
				<< t2 << ':' << ppsig(s2) << endl; */
		if (!i.valid) {
			cerr << "ERROR : can't compute the min and max values of : " << ppsig(s2) << endl;
			cerr << "        used in delay expression : " << ppsig(sig) << endl;
			cerr << "        (probably a recursive signal)" << endl;
			exit(1);
		} else if (i.lo < 0) {
			cerr << "ERROR : possible negative values of : " << ppsig(s2) << endl;
			cerr << "        used in delay expression : " << ppsig(sig) << endl;
			cerr << "        " << i << endl;
			exit(1);
		}

		return castInterval(sampCast(t1), reunion(t1->getInterval(), interval(0,0)));
	}

	else if (isSigBinOp(sig, &i, s1, s2)) {
		//Type t = T(s1,env)|T(s2,env);
		Type t1 = T(s1,env);
		Type t2 = T(s2,env);
		Type t3 = castInterval(t1 | t2, arithmetic(i, t1->getInterval(), t2->getInterval()));
		//cerr <<"type rule for : " << ppsig(sig) << " -> " << *t3 << endl;
	  	//return (!gVectorSwitch && (i>=kGT) && (i<=kNE)) ?  intCast(t3) : t3; // for comparaison operation the result is int
	  	return ((i>=kGT) && (i<=kNE)) ?  intCast(t3) : t3; // for comparaison operation the result is int
	}

	else if (isSigIntCast(sig, s1))			return intCast(T(s1,env));

	else if (isSigFloatCast(sig, s1)) 			return floatCast(T(s1,env));

	else if (isSigFFun(sig, ff, ls)) 			return infereFFType(ff,ls,env);

    else if (isSigFConst(sig,type,name,file))   return infereFConstType(type);

    else if (isSigFVar(sig,type,name,file))   return infereFVarType(type);

	else if (isSigButton(sig)) 				return castInterval(TGUI,interval(0,1));

	else if (isSigCheckbox(sig))				return castInterval(TGUI,interval(0,1));

	else if (isSigVSlider(sig,label,cur,min,max,step))
												return castInterval(TGUI,interval(tree2float(min),tree2float(max)));

	else if (isSigHSlider(sig,label,cur,min,max,step))
												return castInterval(TGUI,interval(tree2float(min),tree2float(max)));

	else if (isSigNumEntry(sig,label,cur,min,max,step))
												return castInterval(TGUI,interval(tree2float(min),tree2float(max)));

	else if (isSigHBargraph(sig, l, x, y, s1)) return T(s1,env);

	else if (isSigVBargraph(sig, l, x, y, s1)) return T(s1,env);

	else if (isSigAttach(sig, s1, s2)) 		{ T(s2,env); return T(s1,env); }

	else if (isRec(sig, var, body))			return infereRecType(sig, body, env);

	else if (isProj(sig, &i, s1))				return infereProjType(T(s1,env),i,kScal);

	else if (isSigTable(sig, id, s1, s2)) 		{ checkInt(checkInit(T(s1,env))); return new TableType(checkInit(T(s2,env))); }

	else if (isSigWRTbl(sig, id, s1, s2, s3)) 	return infereWriteTableType(T(s1,env), T(s2,env), T(s3,env));

	else if (isSigRDTbl(sig, s1, s2)) 			return infereReadTableType(T(s1,env), T(s2,env));

	else if (isSigGen(sig, s1)) 				return T(s1,NULLENV);

    else if ( isSigDocConstantTbl(sig, x, y) )	return infereDocConstantTblType(T(x,env), T(y,env));
    else if ( isSigDocWriteTbl(sig,x,y,z,u) )	return infereDocWriteTblType(T(x,env), T(y,env), T(z,env), T(u,env));
    else if ( isSigDocAccessTbl(sig, x, y) )    return infereDocAccessTblType(T(x,env), T(y,env));

	else if (isSigSelect2(sig,sel,s1,s2)) 		{

	  SimpleType *st1, *st2, *stsel;

	  st1 = isSimpleType(T(s1,env));
	  st2 = isSimpleType(T(s2,env));
	  stsel = isSimpleType(T(sel,env));

	  return new SimpleType( st1->nature()|st2->nature(),
				 st1->variability()|st2->variability()|stsel->variability(),
				 st1->computability()|st2->computability()|stsel->computability(),
				 st1->vectorability()|st2->vectorability()|stsel->vectorability(),
				 st1->boolean()|st2->boolean(),
				 reunion(st1->getInterval(), st2->getInterval())
				 );

	  //return T(sel,env)|T(s1,env)|T(s2,env);

	}

	else if (isSigSelect3(sig,sel,s1,s2,s3)) 	{ return T(sel,env)|T(s1,env)|T(s2,env)|T(s3,env); }

	else if (isList(sig))
	{
		vector<Type> v;
		while (isList(sig)) { v.push_back(T(hd(sig),env)); sig = tl(sig); }
		return new TupletType(v);
	}
	else if (isSigVectorize(sig, s1, s2))   return infereVectorizeType(sig, env, s1, s2);
    else if (isSigSerialize(sig, s1))       return infereSerializeType(sig, env, s1);
    else if (isSigConcat(sig, s1, s2))      return infereConcatType(sig, env, s1, s2);
    else if (isSigVectorAt(sig, s1, s2))    return infereVectorAtType(sig, env, s1, s2);

	// unrecognized signal here
	fprintf(stderr, "ERROR infering signal type : unrecognized signal  : "); print(sig, stderr); fprintf(stderr, "\n");
	exit(1);
	return 0;
}



/**
 *	Infere the type of a projection (selection) of a tuplet element
 */
static Type infereProjType(Type t, int i, int vec)
{
	TupletType* tt = isTupletType(t);
	if (tt == 0) {
		cerr << "ERROR infering projection type, not a tuplet type : " << t << endl;
		exit(1);
	}
	//return (*tt)[i]	->promoteVariability(t->variability())
	//		->promoteComputability(t->computability());
	Type temp = (*tt)[i]	->promoteVariability(t->variability())
	  ->promoteComputability(t->computability())
	  ->promoteVectorability(vec/*t->vectorability()*/);
	//->promoteBooleanity(t->boolean());

	if(vec==kVect) return vecCast(temp);
	else return temp;
}



/**
 *	Infere the type of the result of writing into a table
 */
static Type infereWriteTableType(Type tbl, Type wi, Type wd)
{
	TableType* tt = isTableType(tbl);
	if (tt == 0) {
		cerr << "ERROR infering write table type, wrong table type : " << tbl << endl;
		exit(1);
	}
	SimpleType* st = isSimpleType(wi);
	if (st == 0 || st->nature() > kInt) {
		cerr << "ERROR infering write table type, wrong write index type : " << wi << endl;
		exit(1);
	}

	int n = tt->nature();
	int v = wi->variability() | wd->variability();
	int c = wi->computability() | wd->computability();
	int vec = wi->vectorability() | wd->vectorability();

	//Type temp = tt->content();
	//cerr<<"Write table content: "<<temp<<endl;

	//Type tempbis = new TableType(/*tt->content()*/temp, v, c);
	//cerr<<"Write table ap� promotion: "<<tempbis<<endl;

	//return tempbis;

	//return new TableType(/*tt->content()*/temp, v, c);

	return new TableType(tt->content(), n, v, c, vec, tt->boolean());
}



/**
 *	Infere the type of the result of reading a table
 */
static Type infereReadTableType(Type tbl, Type ri)
{
	TableType*	tt = isTableType(tbl);
	if (tt == 0) {
		cerr << "ERROR infering read table type, wrong table type : " << tbl << endl;
		exit(1);
	}
	SimpleType* st = isSimpleType(ri);
	if (st == 0 || st->nature() > kInt) {
		cerr << "ERROR infering read table type, wrong write index type : " << ri << endl;
		exit(1);
	}

	//cerr<<"Read Table type avant promote: "<<*tt<<endl;
	//cerr<<"Indice avant promote: "<<ri<<endl;

	//Type temp =  tt->content()->promoteVariability(ri->variability()|tt->variability())
	//  ->promoteComputability(ri->computability()|tt->computability());

	//cerr<<"Read Table type: "<<temp<<endl;

	//return temp;

	Type temp =  tt->content()->promoteVariability(ri->variability()|tt->variability())
	  ->promoteComputability(ri->computability()|tt->computability())
	  ->promoteVectorability(ri->vectorability()|tt->vectorability())
	  ->promoteBoolean(ri->boolean()|tt->boolean())
	  ;

	//cerr<<"Read Table type: "<<temp<<endl;


	return temp;

	//return tt->content(); // pas completement correct !!!
	//return tt->content()->promoteVariability(ri->variability())
	//         	->promoteComputability(ri->computability())
	  //->promoteVectorability(ri->vectorability())
	  //           ->promoteBoolean(ri->boolean())
	  //             ;
}


static Type infereDocConstantTblType(Type size, Type init)
{
    checkKonst(checkInt(checkInit(size)));

    return init;
}

static Type infereDocWriteTblType(Type size, Type init, Type widx, Type wsig)
{
    checkKonst(checkInt(checkInit(size)));

    Type temp =  init
      ->promoteVariability(kSamp)       // difficult to tell, therefore kSamp to be safe
      ->promoteComputability(widx->computability()|wsig->computability())
      ->promoteVectorability(kScal)     // difficult to tell, therefore kScal to be safe
      ->promoteNature(wsig->nature())   // nature of the initial and written signal
      ->promoteBoolean(wsig->boolean()) // booleanity of the initial and written signal
      ;
    return temp;
}

static Type infereDocAccessTblType(Type tbl, Type ridx)
{
    Type temp =  tbl
      ->promoteVariability(ridx->variability())
      ->promoteComputability(ridx->computability())
      ->promoteVectorability(ridx->vectorability())
      ;
    return temp;
}

/**
 *	Compute an initial type solution for a recursive block
 */
static Type initialRecType(Tree t)
{
	if (isList(t)) {
		vector<Type> v;
		do { v.push_back(initialRecType(hd(t))); t = tl(t); }  while (isList(t));
		return new TupletType(v);
	} else {
		return TREC;
	}
}



/**
 * Infere the type of e recursive block by trying solutions of
 * increasing generality
 */
static Type infereRecType (Tree var, Tree body, Tree env)
{
	Type t0, t1;

	t1 = initialRecType(body);
	do {
		t0 = t1;
		setProperty(var, env, tree((void*)t0));
		t1 = T(body, addEnv(var, t0, env));
    } while (t1 > t0);

    assert (t1 == t0);

	if (getRecursivness(body) == 1 || env == NULLENV) {
        setSigType(var, t1);
		T(body, NULLENV);
	}
	return t1;
}


/**
 *	Infere the type of a foreign function call
 */
static Type infereFFType (Tree ff, Tree ls, Tree env)
{
	// une primitive externe ne peut pas se calculer au plus tot qu'a
	// l'initialisation. Sa variabilite depend de celle de ses arguments
	// sauf si elle n'en pas, auquel cas on considere que c'est comme
	// rand() c'est a dire que le resultat varie a chaque appel.
	if (ffarity(ff)==0) {
		// case of functions like rand()
		return new SimpleType(ffrestype(ff),kSamp,kInit,kVect,kNum, interval());
	} else {
		// otherwise variability and computability depends
		// arguments (OR of all arg types)
		Type t = new SimpleType(kInt,kKonst,kInit,kVect,kNum, interval());
		while (isList(ls)) { t = t|T(hd(ls),env); ls=tl(ls); }
		// but the result type is defined by the function

		//return t;
		return new SimpleType(	ffrestype(ff),
								t->variability(),
								t->computability(),
								t->vectorability(),
								t->boolean(),
								interval() );
	}
}

/**
 *  Infere the type of a foreign constant
 */
static Type infereFConstType (Tree type)
{
    // une constante externe ne peut pas se calculer au plus tot qu'a
    // l'initialisation. Elle est constante, auquel cas on considere que c'est comme
    // rand() c'est a dire que le resultat varie a chaque appel.
    return new SimpleType(tree2int(type),kKonst,kInit,kVect,kNum, interval());
}

/**
 *  Infere the type of a foreign variable
 */
static Type infereFVarType (Tree type)
{
    // une variable externe ne peut pas se calculer au plus tot qu'a
    // l'execution. Elle est varie par blocs comme les éléments d'interface utilisateur.
    return new SimpleType(tree2int(type),kBlock,kExec,kVect,kNum, interval());
}




/**
 *	Infere the type of an extended (primitive) block
 */
static Type infereXType(Tree sig, Tree env)
{
	//cerr << "infereXType :" << endl;
	//cerr << "infereXType of " << *sig << endl;
	xtended* p = (xtended*) getUserData(sig);
	vector<Type> vt;

	for (int i = 0; i < sig->arity(); i++) vt.push_back(T(sig->branch(i), env));
	return p->infereSigType(vt);
}

static Type infereVectorizeType(Tree sig, Tree env, Tree s1, Tree s2)
{
    checkIntParam(T(s2, env));
    printf("vectorize not implemented\n");
    exit (0);
}

static Type infereSerializeType(Tree sig, Tree env, Tree s)
{
    printf("serialize not implemented\n");
    exit (0);
}

static Type infereConcatType(Tree sig, Tree env, Tree s1, Tree s2)
{
    printf("concatenation not implemented\n");
    exit (0);
}

static Type infereVectorAtType(Tree sig, Tree env, Tree s1, Tree s2)
{
    checkIntParam(T(s2, env));
    printf("vector at not implemented\n");
    exit (0);
}
