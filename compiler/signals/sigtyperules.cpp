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
//#include "prim.hh"
#include "prim2.hh"
#include "tlib.hh"
#include "sigtyperules.hh"

//--------------------------------------------------------------------------
// prototypes

static Type infereSigType(Tree term, Tree env);
static Type infereFFType (Tree ff, Tree ls, Tree env);
static Type infereFConstType (Tree type);
static Type infereRecType (Tree var, Tree body, Tree env);
static Type infereReadTableType(Type tbl, Type ri);
static Type infereWriteTableType(Type tbl, Type wi, Type wd);
static Type infereProjType(Type t, int i, int vec);
static Tree addEnv(Tree var, Tree tt, Tree env);
static void markSigType(Tree sig, Tree env);




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



/*
 * add a new binding to a type environment
 * @param var the variable
 * @param type the type of the variable
 * @param env the type environment
 * @result a new environment : [(var,type):env]
 */
Tree addEnv(Tree var, Type tp, Tree env)
{
	//cerr << "AddEnv " << tree2str(var) << " with type " << tp << endl;
	return cons(cons(var,tree((AudioType*)tp)),env);
}

static Tree addEnv(Tree var, Tree tt, Tree env)
{
	return cons(cons(var,tt),env);
}



/*
 * search for the type associated to a variable
 * @param env the type environment
 * @param var the variable to search
 * @result the type associated to var in env
 */
Type searchEnv(Tree env, Tree var)
{
	while ( (env != NULLENV) && (hd(hd(env)) != var) ) { env = tl(env); }
	assert(env != NULLENV);	// we should have found the data
	
// 	fprintf(stderr, "search env for "); printSignal(var, stderr); 
// 	cerr <<  " got " << Type((AudioType*)tree2ptr(tl(hd(env)))) << endl;
	
	return Type((AudioType*)tree2ptr(tl(hd(env))));
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
//	fprintf(stderr, "debut typeannotation\n");
	getSigType(sig, NULLENV);
//	fprintf(stderr, "millieu typeannotation\n");
	markSigType(sig, NULLENV);
//	fprintf(stderr, "fin typeannotation\n");
}


/**
 * retrieve the type annotation of sig
 * @param sig the signal we want to know the type
 */
Type sigType(Tree sig)
{
	Tree tt;
	if (!getProperty(sig, NULLENV, tt)) {
		fprintf(stderr, "ERROR in sigType : no type information avaliable for signal :");
		printSignal(sig, stderr);
		fprintf(stderr, "\n");
		exit(1);
	}
	return (AudioType*)tree2ptr(tt);
}		

/**
 * Mark every subtree with type information with key NULLENV instead of full env
 * @param sig the tree to mark
 * @param env the type environment
 */
static void markSigType(Tree sig, Tree env)
{
	Tree tt, var, body;
	
	if (getProperty(sig, NULLENV, tt)) return;
	if (!getProperty(sig, env, tt)) { 
		fprintf(stderr, "internal error 2\n");
		exit(1);
	}
	setProperty(sig, NULLENV, tt);
	
	if (isRef(sig, var)) {
		// nothing to do here but avoid going through var
	} else if (isRec(sig, var, body)) {
		markSigType(body, addEnv(var,tt,env));
	} else 	{
		int n = sig->arity();
		for (int i=0; i<n; i++) markSigType(sig->branch(i), env);
	}
}
		
	 


/**
 * Retrieve or infere the type of a term according to its surrounding type environment
 * @param sig the signal to analyze
 * @param env the type environment
 * @return the type of sig according to environment env
 */
Type getSigType(Tree term, Tree env)
{
#if 0
	fprintf(stderr, "CALL getSigType("); 
		printSignal(term, stderr); 
		fprintf(stderr, ", ");
		print(env, stderr);  
	fprintf(stderr, ")\n");
#endif
	
	Tree 	tt;
	//cerr << "toto1\n";
	if (isClosed(term)) env = NULLENV;

	if (!getProperty(term, env, tt)) 
	{
		//cerr << "toto2b\n";
		Type t = infereSigType(term, env);
		//cerr << "infered type is " << t << endl;
		setProperty(term, env, tree((AudioType*)t));
		//cerr << "toto2f\n";
		return t;
	}
	//cerr << "toto3\n";
	//print(tt, stderr);
	//cerr << "toto4\n";
	Type rt((AudioType*)tree2ptr(tt));
	//cerr << "toto5 : " << rt << "\n";
	return rt;
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
	Type t = getSigType(term, env); 
	return t;
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
	float 		r;
	Tree		sel, s1, s2, s3, ff, id, ls, var, body, type, name, file;
	
	if (isSigInt(sig, &i))					return TINT;
		
	else if (isSigReal(sig, &r)) 				return TREAL;
		
	else if (isSigInput(sig, &i))				return TINPUT;
		
	else if (isSigOutput(sig, &i, s1)) 			return T(s1,env);
		
	else if (isSigDelay1(sig, s1)) 				return sampCast(T(s1,env));
	
	else if (isSigFixDelay(sig, s1, s2)) 		{ checkIntParam(T(s2,env)); return sampCast(T(s1,env)); }
/*		
	else if (isSigBinOp(sig, &i, s1, s2)) 		        { 
	  if((i>=7) && (i<=12))  return boolCast(T(s1,env)|T(s2,env)); //comparaison operation the result is boolean
	  else return T(s1,env)|T(s2,env) ;
	  //return T(s1,env)|T(s2,env) ;
*/		
	else if (isSigBinOp(sig, &i, s1, s2)) { 
		Type t = T(s1,env)|T(s2,env);
	  	return ((i>=7) && (i<=12)) ?  boolCast(t) : t; // for comparaison operation the result is boolean
	} 
		
	else if (isSigIntCast(sig, s1))				return intCast(T(s1,env));
	
	else if (isSigFloatCast(sig, s1)) 			return floatCast(T(s1,env));

	else if (isSigFFun(sig, ff, ls)) 			return infereFFType(ff,ls,env);

	else if (isSigFConst(sig,type,name,file))return infereFConstType(type);
		
	else if (isSigButton(sig)) 				return /*INT_*/TGUI; //return TGUI;
	
	else if (isSigCheckbox(sig))				return /*INT_*/TGUI; //return TGUI;
	
	else if (isSigVSlider(sig))				return TGUI;
	 
	else if (isSigHSlider(sig))				return TGUI;
	
	else if (isSigNumEntry(sig))				return TGUI;
				
	else if (isRec(sig, var, body))				return infereRecType(var, body, env);
				
	else if (isRef(sig, var))					{ Type t =  searchEnv(env, var); return t->promoteVectorability(kScal); } 

	else if (isProj(sig, &i, s1))				{ 
		// a revoir 
		static Tree rec_being_defined;
		static bool Vectorisation = true;
		Type t;
		int vec;

		if(isRef(s1,var)) {
			if(rec_being_defined!=var) Vectorisation = false;
			t = T(s1,env);
			vec = kScal;
		} else if (isRec(s1,var,body)) {

		  Tree temp_rec_being_defined = rec_being_defined;
		  rec_being_defined = var;

		  t = T(s1,env);

		  rec_being_defined = temp_rec_being_defined;

		  if(Vectorisation) vec = kVect;
		  else vec = kScal;

		  Vectorisation = true;

		} else { fprintf(stderr,"Bizarre\n"); t = T(s1,env); }


		//fprintf(stderr,"rec_being_defined: %p\n", rec_being_defined);
		//fprintf(stderr,"var: %p\n", var);

		//fprintf(stderr,"projection arg vec: %d\n", vec);

		return infereProjType(t,i,vec);

		//return infereProjType(T(s1,env),i,kScal);
	}   
	                                                
				
	else if (isSigTable(sig, id, s1, s2)) 		{ checkInt(checkInit(T(s1,env))); return new TableType(checkInit(T(s2,env))); }
		
	else if (isSigWRTbl(sig, id, s1, s2, s3)) 	return infereWriteTableType(T(s1,env), T(s2,env), T(s3,env)); 
			
	else if (isSigRDTbl(sig, s1, s2)) 			return infereReadTableType(T(s1,env), T(s2,env));  
		
	else if (isSigGen(sig, s1)) 				return T(s1,NULLENV);
		
	else if (isSigSelect2(sig,sel,s1,s2)) 		{ 

	  SimpleType *st1, *st2, *stsel;

	  st1 = isSimpleType(T(s1,env));
	  st2 = isSimpleType(T(s2,env));
	  stsel = isSimpleType(T(sel,env)); 
	  
	  return new SimpleType( st1->nature()|st2->nature(),
				 st1->variability()|st2->variability()|stsel->variability(),
				 st1->computability()|st2->computability()|stsel->computability(),
				 st1->vectorability()|st2->vectorability()|stsel->vectorability(),
				 st1->boolean()|st2->boolean()
				 );

	  //return T(sel,env)|T(s1,env)|T(s2,env);

	}
		
	else if (isSigSelect3(sig,sel,s1,s2,s3)) 	{ /*checkInt(T(sel,env));*/ return T(sel,env)|T(s1,env)|T(s2,env)|T(s3,env); }		
	
	else if (isList(sig)) 
	{
		vector<Type> v;
		while (isList(sig)) { v.push_back(T(hd(sig),env)); sig = tl(sig); }
		return new TupletType(v);
	}
	
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
	//cerr<<"Write table apès promotion: "<<tempbis<<endl;

	//return tempbis;

	//return new TableType(/*tt->content()*/temp, v, c);

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
//	cerr << "try first : " << t1 << endl;
	do {
		t0 = t1;
		t1 = T(body, addEnv(var, t0, env));
		if (t1 < t0)  { 
			cerr << "situation anormale : t1 = " << t1 << " alors que t0 = " << t0 << endl;
			fprintf(stderr, "dans le typage de "); printSignal(body, stderr); fputc('\n', stderr);
		}
//		if (t1 != t0) cerr << "try then : " << t1 << endl;
	} while (t1 != t0);
//	cerr << "converge : " << t1 << endl;
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
		return new SimpleType(ffrestype(ff),kSamp,kInit,kVect,kNum);
	} else {
		// otherwise variability and computability depends 
		// arguments (OR of all arg types)
		Type t = new SimpleType(kInt,kKonst,kInit,kVect,kNum); 
		while (isList(ls)) { t = t|T(hd(ls),env); ls=tl(ls); }
		return t;
	}
}

/**
 *	Infere the type of a foreign constant
 */
static Type infereFConstType (Tree type)
{
	// une constante externe ne peut pas se calculer au plus tot qu'a
	// l'initialisation. Elle est constante, auquel cas on considere que c'est comme
	// rand() c'est a dire que le resultat varie a chaque appel. 
	return new SimpleType(tree2int(type),kKonst,kInit,kVect,kNum);
}

