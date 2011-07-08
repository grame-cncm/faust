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
#include <iostream>
#include <fstream>
#include <time.h>


#include "sigtype.hh"
#include "sigprint.hh"
#include "ppsig.hh"
//#include "prim.hh"
#include "prim2.hh"
#include "tlib.hh"
#include "sigtyperules.hh"
#include "xtended.hh"
#include "recursivness.hh"
#include "sigraterules.hh"


//--------------------------------------------------------------------------
// prototypes

static void setSigType(Tree sig, Type t);
static Type getSigType(Tree sig);


static void setInferredTypeProperty(Tree term, Tree env, Type ty);
static Type getInferredTypeProperty(Tree term, Tree env);

static Type T(Tree term, Tree env);

static Type getOrInferType(Tree term, Tree env);
static void fixInferredType(Tree term, Tree env);

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
static interval arithmetic (int opcode, const interval& x, const interval& y);
static Tree pushTypeEnv(Tree var, Type tp, Tree env);


static Type infereVectorizeType(Type T, Type Tsize);
static Type infereSerializeType(Type Tvec);
static Type infereConcatType(Type Tvec1, Type Tvec2);
static Type infereVectorAtType(Type Tvec, Type Tidx);



// Uncomment to activate type inference tracing
//#define TRACE(x) x
#define TRACE(x) 0;


/**
 * The empty type environment (also property key for closed term type)
 */
static Tree NULLTYPEENV = tree(symbol("NullTypeEnv"));

static int countInferences;



/**
 * Fully annotate every subtree of term with type information.
 * In a first step types are inferred with the help of type
 * environments. Then type informations are fixed by removing
 * type environments.
 * @param sig the signal term tree to annotate
 */
void typeAnnotation(Tree sig)
{
    countInferences = 0;

    //cerr << ++TABBER << "ENTER TYPE ANNOTATION OF " << *sig << " AT TIME " << clock()/CLOCKS_PER_SEC << 's' << endl;
    T(sig, NULLTYPEENV);
    //cerr << TABBER << "COUNT INFERENCE " << countInferences << " AT TIME " << clock()/CLOCKS_PER_SEC << 's' << endl;
    fixInferredType(sig, NULLTYPEENV);
    //cerr << --TABBER << "EXIT TYPE ANNOTATION OF " << *sig << " AT TIME " << clock()/CLOCKS_PER_SEC << 's' << endl;

    bool    success;
    Tree    ME = inferreMultiRates(sig, success);
    if (success) {
        printRateEnvironmentList(cerr, ME); cerr << endl;
    } else {
        cerr << "ERROR can't inferre rate environment of " << ppsig(sig) << endl;
    }
}



/**
 * Retrieve the type of sig and check it exists. Produces an
 * error if the signal has no type associated
 * @param sig the signal we want to know the type
 * @return the type of the signal
 */
Type getCertifiedSigType(Tree sig)
{
    TRACE(cerr << "[c]" << endl;)
    AudioType* t = getSigType(sig);
    if (t==0) {
        cerr << "ERROR in getCertifiedSigType : no type information available for signal :" << *sig << endl;
        exit(1);
    }
    return t;
}



/***********************************************
 * Set and get the type property of a signal
 * (we suppose the signal have been previously
 * annotated with type information)
 ***********************************************/

/**
 * Set the type annotation of sig
 * @param sig the signal we want to type
 * @param t the type of the signal
 */
static void setSigType(Tree sig, Type t)
{
    TRACE(cerr << TABBER << "SET FIX TYPE OF " << *sig << " TO TYPE " << *t << endl;)
	sig->setType(t);
}


/**
 * Retrieve the type annotation of sig
 * @param sig the signal we want to know the type
 */
static Type getSigType(Tree sig)
{
    AudioType* ty = (AudioType*) sig->getType();
    if (ty == 0)
        TRACE(cerr << TABBER << "GET FIX TYPE OF " << *sig << " HAS NO TYPE YET" << endl;)
    else
        TRACE(cerr << TABBER << "GET FIX TYPE OF " << *sig << " IS TYPE " << *ty << endl;)
    return ty;
}




/**************************************************************************
 	Type Environments : type environmpent are needed to correctly
	infere the type of an "open" term containing recursive references
	to an enclosing term. Type environments are also used as a property
	key to store already computed types
***************************************************************************/



/**
 * Add a new binding to a type environment. The type is coded as
 * a tree in order to benefit of memoization
 * @param var the variable
 * @param type the type of the variable
 * @param env the type environment
 * @result a new environment : [(var,type):env]
 */
static Tree pushTypeEnv(Tree var, Type tp, Tree env)
{
    //cerr << "PUSH " << *var << " OF TYPE " << *tp << " IN ENV " << *env << endl;
    Tree r = cons(cons(var,codeAudioType(tp)),env);
    return r;
}


/**
 * Search for the type associated to a variable. Return the associated type
 * or 0 if var is not in the environment.
 * @param var the variable to search
 * @param env the type environment
 * @return the type associated to var in env
 */
static Type searchTypeEnv(Tree var, Tree env)
{
    while ( (env != NULLTYPEENV) && (hd(hd(env)) != var) ) { env = tl(env); }

    if (env == NULLTYPEENV) {
        return 0;
    } else {
        return (AudioType*) tl(hd(env))->getType();
    }
}


/**************************************************************************

 						Type Inference System

***************************************************************************/



/**
 * Once type inference has been done we can fix the type of a signal term
 * because type environments are not needed anymore.
 * @param sig the signal term tree to annotate
 * @param env the type environment
 */
static void fixInferredType(Tree sig, Tree env)
{
    TRACE(cerr << ++TABBER << "ENTER FIX INFERRED TYPE OF " << *sig << " WITH ENV " << *env << endl;)
    if ((AudioType*)getSigType(sig) == 0) {
        // the term must have a type for the corresponding env
        AudioType* ty = getInferredTypeProperty(sig, env);
        if (ty == (AudioType*)0) {
            cerr << "ERROR in fixInferredType : NO TYPE PROPERTY FOR " <<  *sig << " WITH ENV " << *env << endl;
            assert(ty);
        }

        setSigType(sig, ty);

        // now we must visit its subtrees taking into account
        // the special cases of recursions and signal generators

        Tree    var, body, x;

        if (isRec(sig, var, body))  {
            fixInferredType(body, pushTypeEnv(sig, ty, env));

        } else if ( isSigGen(sig, x) ) {
            fixInferredType(x, NULLTYPEENV);

        } else {
            // general case we fix the subtrees with the same environment
            vector<Tree> subsig; int n = getSubSignals(sig, subsig);
            for (int i = 0; i<n; i++) {
                fixInferredType(subsig[i], env);
            }
        }
    }
    TRACE(cerr << --TABBER << "EXIT FIX INFERRED TYPE OF " << *sig << " WITH ENV " << *env << endl;)
}


/**************************************************************************

                        Infered Type property

***************************************************************************/


/**
 * Store the infered type of a signal term as a property using the type environment as a key.
 * @param term the signal to annotate
 * @param env the type environment
 * @param the type of term according to the type environment env
 */

static void setInferredTypeProperty(Tree term, Tree env, Type ty)
{
    TRACE(cerr << TABBER << "SET INFERRED TYPE PROPERTY OF  " << *term << " IN ENV " << *env << " IS TYPE " <<  *ty << endl;)
    setProperty(term, env, tree((void*)ty));
}


/**
 * Retrieve the infered type property of a term using the type environment as a key.
 * @param term the signal to annotate
 * @param env the type environment
 * @return the type of sig according to environment env
 */

static Type getInferredTypeProperty(Tree term, Tree env)
{
    Tree    tt;


    if (getProperty(term, env, tt)) {
        TRACE(cerr << TABBER << "GET INFERRED TYPE PROPERTY  OF " << *term << " IN ENV " << *env << " IS TYPE " << *(AudioType*)tree2ptr(tt) << endl;)
        return (AudioType*)tree2ptr(tt);
    } else {
        return 0;
    }
}



/**
 * Check if there is no intersection between a set of variables
 * {X1, X2, ...} and a type environment [(Y1,T1), (Y2,T2), ...]
 * return true when there is no intersection (no Yi in {X1, X2, ...}
 */
static bool isFreeInEnv(Tree set, Tree env)
{
    if (env == NULLTYPEENV) {
        return true;
    } else if (isElement(hd(hd(env)), set)) {
        return false;
    } else {
        return isFreeInEnv(set, tl(env));
    }
}




/**
 * Retrieve or infere the type of a term according to its surrounding type environment
 * @param sig the signal to analyze
 * @param env the type environment
 * @return the type of sig according to environment env
 * @see getCertifiedSigType
 */

static Type getOrInferType(Tree term, Tree env)
{
    Type ty;

    if ((ty = getSigType(term))) {

        // we have already a fix type that doesn't depend on any hypothesis
        return ty;

    } else if ( (env == NULLTYPEENV) ||  isFreeInEnv(symlist(term),env) ) {

        if (env != NULLTYPEENV) {
            TRACE(cerr << TABBER << "NOTE : We can forget hypothesis environment here " << endl;)
        }
        // we don't have a type but we don't depend of any hypothesis
        ty = infereSigType(term, NULLTYPEENV);
        setInferredTypeProperty(term, NULLTYPEENV, ty);
        fixInferredType(term,NULLTYPEENV);
        return ty;

    } else {

        // we have hypothesis and we depend on them
        if ( (ty = getInferredTypeProperty(term, env)) ) {
            // but we have already typed this term with this hypothesis
             return ty;
         } else {
             // we never typed this term with these hypothesis
             ty = infereSigType(term, env);
             setInferredTypeProperty(term, env, ty);
             return ty;
         }
    }
}


/**
 * Shortcut to getOrInferType, retrieve or infere the type of a term according to its surrounding type environment
 * @param sig the signal to analyze
 * @param env the type environment
 * @return the type of sig according to environment env
 * @see getCertifiedSigType
 */
static Type T(Tree term, Tree env)
{
    TRACE(cerr << ++TABBER << "ENTER T() " << *term << " WITH ENV " << *env << endl;)
    Type ty = getOrInferType(term, env);
    TRACE(cerr << --TABBER << "EXIT T() " << *term << " AS TYPE " << *ty << " WITH ENV " << *env << endl;)

    return ty;
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

    countInferences++;

		 if ( getUserData(sig) ) 			return infereXType(sig, env);

    else if (isSigInt(sig, &i))             {   Type t = new SimpleType(kInt, kKonst, kComp, kVect, kNum, interval(i));
                                                /*sig->setType(t);*/ return t; }

    else if (isSigReal(sig, &r)) 			{   Type t = new SimpleType(kReal, kKonst, kComp, kVect, kNum, interval(r));
                                                /*sig->setType(t);*/ return t; }

    else if (isSigInput(sig, &i))			{   /*sig->setType(TINPUT);*/ return TINPUT; }

    else if (isSigOutput(sig, &i, s1))      return sampCast(T(s1,env));

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
 
//        cerr << "for sig fix delay : s1 = "
//				<< t1 << ':' << ppsig(s1) << ", s2 = "
//                << t2 << ':' << ppsig(s2) << endl;
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

    else if (isSigIntCast(sig, s1))             return intCast(T(s1,env));

	else if (isSigFloatCast(sig, s1)) 			return floatCast(T(s1,env));

	else if (isSigFFun(sig, ff, ls)) 			return infereFFType(ff,ls,env);

    else if (isSigFConst(sig,type,name,file))   return infereFConstType(type);

    else if (isSigFVar(sig,type,name,file))     return infereFVarType(type);

    else if (isSigButton(sig))                  { /*sig->setType(TGUI01);*/ return TGUI01; }

    else if (isSigCheckbox(sig))				{ /*sig->setType(TGUI01);*/ return TGUI01; }

	else if (isSigVSlider(sig,label,cur,min,max,step))		
												return castInterval(TGUI,interval(tree2float(min),tree2float(max)));

	else if (isSigHSlider(sig,label,cur,min,max,step))				
												return castInterval(TGUI,interval(tree2float(min),tree2float(max)));

	else if (isSigNumEntry(sig,label,cur,min,max,step))				
												return castInterval(TGUI,interval(tree2float(min),tree2float(max)));

    else if (isSigHBargraph(sig, l, x, y, s1))  return T(s1,env);

    else if (isSigVBargraph(sig, l, x, y, s1))  return T(s1,env);

    else if (isSigAttach(sig, s1, s2))          { T(s2,env); return T(s1,env); }

    else if (isRec(sig, var, body))             return infereRecType(sig, body, env);

	else if (isProj(sig, &i, s1))				return infereProjType(T(s1,env),i,kScal);

	else if (isSigTable(sig, id, s1, s2)) 		{ checkInt(checkInit(T(s1,env))); return new TableType(checkInit(T(s2,env))); }

	else if (isSigWRTbl(sig, id, s1, s2, s3)) 	return infereWriteTableType(T(s1,env), T(s2,env), T(s3,env));

	else if (isSigRDTbl(sig, s1, s2)) 			return infereReadTableType(T(s1,env), T(s2,env));

    else if (isSigGen(sig, s1)) 				return T(s1,NULLTYPEENV);

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
                                                }

	else if (isSigSelect3(sig,sel,s1,s2,s3)) 	{ return T(sel,env)|T(s1,env)|T(s2,env)|T(s3,env); }

    else if (isNil(sig))                        { Type t = new TupletType(); /*sig->setType(t);*/ return t; }

    else if (isList(sig))                       { return T( hd(sig),env ) * T( tl(sig),env ); }

    else if ( isSigVectorize(sig, x, y) )      return infereVectorizeType(T(x,env), T(y,env));
    else if ( isSigSerialize(sig, x) )         return infereSerializeType(T(x,env));
    else if ( isSigConcat(sig, x, y) )         return infereConcatType(T(x,env), T(y,env));
    else if ( isSigVectorAt(sig, x, y) )       return infereVectorAtType(T(x,env), T(y,env));

	// unrecognized signal here
    fprintf(stderr, "ERROR in ***infereSigType()***, unrecognized signal  : "); print(sig, stderr); fprintf(stderr, "\n");
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

    if(vec==kVect) temp = vecCast(temp);
    //cerr << "infereProjType(" << t << ',' << i << ',' << vec << ")" << " -> " << temp << endl;

    return temp;
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

	return new TableType(tt->content(), n, v, c, vec);

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

	Type temp =  tt->content()->promoteVariability(ri->variability()|tt->variability())
	  ->promoteComputability(ri->computability()|tt->computability())
	  ->promoteVectorability(ri->vectorability()|tt->vectorability())
	  ->promoteBoolean(ri->boolean()|tt->boolean())
	  ;

	return temp;

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
 * Compute an initial type solution for a recursive block
 * E1,E2,...En -> TREC,TREC,...TREC
 */
static Type initialRecType(Tree t)
{
    assert (isList(t));

    vector<Type> v;
    while (isList(t)) { v.push_back(TREC); t = tl(t); };
    return new TupletType(v);
}


/**
 * Infere the type of e recursive block by trying solutions of
 * increasing generality
 */
static Type infereRecType (Tree sig, Tree body, Tree env)
{
	Type t0, t1;

    if ((t1 =  searchTypeEnv(sig, env))) {

        // we have already an hypothesis for this recursive term
        return t1;

    } else {

        // we don't have an hypothesis, we search the smallest fix point
        t1 = initialRecType(body);
        do {
            t0 = t1;
            t1 = T(body, pushTypeEnv(sig, t0, env));
        } while (t1 != t0);

        //assert (t1 == t0);
        return t1;
    }
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





/**
 * Compute the resulting interval of an arithmetic operation
 * @param op code of the operation
 * @param s1 interval of the left operand
 * @param s2 interval of the right operand
 * @return the resulting interval
 */

static interval arithmetic (int opcode, const interval& x, const interval& y)
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



static Type infereVectorizeType(Type Tsize, Type T)
{
    SimpleType*  st = isSimpleType(Tsize);
    if (st && st->nature()==kInt) {
        interval i = Tsize->getInterval();
        if (i.valid && i.lo >= 0 && i.lo == i.hi) {
            return new VectorType(int(i.lo+0.5), T);
        }
    }
    cerr << "ERROR infering vectorize type, the size of the vector is not of a valide type : " << *Tsize << endl;
    exit(1);
}

static Type infereSerializeType(Type Tvec)
{
    VectorType*  vt =  isVectorType(Tvec);
    if (vt) {
        return vt->content();
    } else {
        cerr << "ERROR infering serialize type, the signal is not of type vector : " << *Tvec << endl;
        exit(1);
    }
}

static Type infereConcatType(Type Tvec1, Type Tvec2)
{
    VectorType*  vt1 =  isVectorType(Tvec1);
    VectorType*  vt2 =  isVectorType(Tvec2);

    if (vt1 && vt2) {
        Type ct1 = vt1->content();
        Type ct2 = vt2->content();
        if (ct1 == ct2) {
            return new VectorType(vt1->size()+vt2->size(), ct1);
        }
    }
    cerr << "ERROR in vector concatenation, the types : " << Tvec1 << " and " << Tvec2 << " are incompatible" << endl;
    exit(1);
}

static Type infereVectorAtType(Type Tvec, Type Tidx)
{
    VectorType*  vt =  isVectorType(Tvec);
    SimpleType*  it = isSimpleType(Tidx);

    if (vt && it) {
        Type ct = vt->content();
        int  n = vt->size();
        interval i = it->getInterval();
        if (i.valid && i.lo >= 0 && i.hi <= n) {
            return ct;
        }
    }
    cerr << "ERROR in vector access, with types : " << Tvec << " and " << Tidx << endl;
    exit(1);
}
