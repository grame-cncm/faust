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
#include <iostream>
#include <fstream>
#include <time.h>

#include "sigtype.hh"
#include "sigprint.hh"
#include "ppsig.hh"
#include "prim2.hh"
#include "tlib.hh"
#include "sigtyperules.hh"
#include "xtended.hh"
#include "recursivness.hh"
#include "exception.hh"
#include "global.hh"

//--------------------------------------------------------------------------
// prototypes

static void setSigType(Tree sig, Type t);
static Type getSigType(Tree sig);
static Type initialRecType(Tree t);

static Type T(Tree term, Tree env);

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
static Type infereWaveformType (Tree lv, Tree env);

static interval arithmetic (int opcode, const interval& x, const interval& y);

// Uncomment to activate type inferrence tracing
//#define TRACE(x) x
#define TRACE(x);

/**
 * The empty type environment (also property key for closed term type)
 */

/**
 * Fully annotate every subtree of term with type information.
 * @param sig the signal term tree to annotate
 */

void typeAnnotation(Tree sig)
{
    Tree            sl = symlist(sig);
    int             n = len(sl);

    vector<Tree>    vrec, vdef;
    vector<Type>    vtype;

    //cerr << "Symlist " << *sl << endl;
    for (Tree l=sl; isList(l); l=tl(l)) {
        Tree    id, body;
		faustassert(isRec(hd(l), id, body));
		if (!isRec(hd(l), id, body)) {
			continue;
		}

        vrec.push_back(hd(l));
        vdef.push_back(body);
    }

    // init recursive types
    for (int i=0; i<n; i++) {
        vtype.push_back(initialRecType(vdef[i]));
    }

    faustassert(int(vrec.size())==n);
    faustassert(int(vdef.size())==n);
    faustassert(int(vtype.size())==n);

    // find least fixpoint
    for (bool finished = false; !finished; ) {

        // init recursive types
        CTree::startNewVisit();
        for (int i=0; i<n; i++) {
            setSigType(vrec[i], vtype[i]);
            vrec[i]->setVisited();
        }

        // compute recursive types
        for (int i=0; i<n; i++) {
            vtype[i] = T(vdef[i], gGlobal->NULLTYPEENV);
        }

        // check finished
        finished = true;
        for (int i=0; i<n; i++) {
            //cerr << i << "-" << *vrec[i] << ":" << *getSigType(vrec[i]) << " => " << *vtype[i] << endl;
            finished =  finished & (getSigType(vrec[i]) == vtype[i]);
        }
    }

    // type full term
    T(sig, gGlobal->NULLTYPEENV);
}

void annotationStatistics()
{
    cerr << gGlobal->TABBER << "COUNT INFERENCE  " << gGlobal->gCountInferences << " AT TIME " << clock()/CLOCKS_PER_SEC << 's' << endl;
    cerr << gGlobal->TABBER << "COUNT ALLOCATION " << gGlobal->gAllocationCount << endl;
    cerr << gGlobal->TABBER << "COUNT MAXIMAL " << gGlobal->gCountMaximal << endl;
}

/**
 * Retrieve the type of sig and check it exists. Produces an
 * error if the signal has no type associated
 * @param sig the signal we want to know the type
 * @return the type of the signal
 */
::Type getCertifiedSigType(Tree sig)
{
    Type ty = getSigType(sig);
    faustassert(ty);
    return ty;
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
    TRACE(cerr << gGlobal->TABBER << "SET FIX TYPE OF " << *sig << " TO TYPE " << *t << endl;)
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
        TRACE(cerr << gGlobal->TABBER << "GET FIX TYPE OF " << *sig << " HAS NO TYPE YET" << endl;)
    else
        TRACE(cerr << gGlobal->TABBER << "GET FIX TYPE OF " << *sig << " IS TYPE " << *ty << endl;)
    return ty;
}

/**************************************************************************

 						Type Inference System

***************************************************************************/

/**************************************************************************

                        Infered Type property

***************************************************************************/

/**
 * Shortcut to getOrInferType, retrieve or infere the type of a term according to its surrounding type environment
 * @param sig the signal to analyze
 * @param env the type environment
 * @return the type of sig according to environment env
 * @see getCertifiedSigType
 */
static Type T(Tree term, Tree ignoreenv)
{
    TRACE(cerr << ++gGlobal->TABBER << "ENTER T() " << *term << endl;)

    if (term->isAlreadyVisited()) {
        Type    ty =  getSigType(term);
        TRACE(cerr << --gGlobal->TABBER << "EXIT 1 T() " << *term << " AS TYPE " << *ty << endl);
        return ty;

    } else {
        Type ty = infereSigType(term, ignoreenv);
        setSigType(term,ty);
        term->setVisited();
        TRACE(cerr << --gGlobal->TABBER << "EXIT 2 T() " << *term << " AS TYPE " << *ty << endl);
        return ty;
    }
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
    Tree		sel, s1, s2, s3, ff, id, ls, l, x, y, z, u, var, body, type, name, file, sf;
	Tree		label, cur, min, max, step;

    gGlobal->gCountInferences++;

		 if ( getUserData(sig) ) 			return infereXType(sig, env);

    else if (isSigInt(sig, &i))             {   Type t = makeSimpleType(kInt, kKonst, kComp, kVect, kNum, interval(i));
                                                /*sig->setType(t);*/ return t; }

    else if (isSigReal(sig, &r)) 			{   Type t = makeSimpleType(kReal, kKonst, kComp, kVect, kNum, interval(r));
                                                /*sig->setType(t);*/ return t; }

    else if (isSigWaveform(sig))            {   return infereWaveformType(sig, env); }

    else if (isSigInput(sig, &i))			{   /*sig->setType(TINPUT);*/ return gGlobal->TINPUT; }

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
            stringstream error;
            error << "ERROR : can't compute the min and max values of : " << ppsig(s2) << endl
                    << "        used in delay expression : " << ppsig(sig) << endl
                    << "        (probably a recursive signal)" << endl;
            throw faustexception(error.str());
		} else if (i.lo < 0) {
            stringstream error;
            error << "ERROR : possible negative values of : " << ppsig(s2) << endl
                    << "        used in delay expression : " << ppsig(sig) << endl
                    << "        " << i << endl;
            throw faustexception(error.str());
		}

		return castInterval(sampCast(t1), reunion(t1->getInterval(), interval(0,0)));
	}

	else if (isSigBinOp(sig, &i, s1, s2)) {
		//Type t = T(s1,env)|T(s2,env);
		Type t1 = T(s1,env);
		Type t2 = T(s2,env);
		Type t3 = castInterval(t1 | t2, arithmetic(i, t1->getInterval(), t2->getInterval()));
		//cerr <<"type rule for : " << ppsig(sig) << " -> " << *t3 << endl;

        if (i == kDiv) {
            return floatCast(t3);            // division always result in a float even with int arguments
        } else if ((i>=kGT) && (i<=kNE)) {
            return boolCast(t3);             // comparison always result in a boolean int
        } else {
            return t3;                       //  otherwise most general of t1 and t2
        }
	}

    else if (isSigIntCast(sig, s1))             return intCast(T(s1,env));

	else if (isSigFloatCast(sig, s1)) 			return floatCast(T(s1,env));

	else if (isSigFFun(sig, ff, ls)) 			return infereFFType(ff,ls,env);

    else if (isSigFConst(sig,type,name,file))   return infereFConstType(type);

    else if (isSigFVar(sig,type,name,file))     return infereFVarType(type);

    else if (isSigButton(sig))                  { /*sig->setType(TGUI01);*/ return gGlobal->TGUI01; }

    else if (isSigCheckbox(sig))				{ /*sig->setType(TGUI01);*/ return gGlobal->TGUI01; }

	else if (isSigVSlider(sig,label,cur,min,max,step))
												return castInterval(gGlobal->TGUI,interval(tree2float(min),tree2float(max)));

	else if (isSigHSlider(sig,label,cur,min,max,step))
												return castInterval(gGlobal->TGUI,interval(tree2float(min),tree2float(max)));

	else if (isSigNumEntry(sig,label,cur,min,max,step))
												return castInterval(gGlobal->TGUI,interval(tree2float(min),tree2float(max)));

    else if (isSigHBargraph(sig, l, x, y, s1))  return T(s1, env)->promoteVariability(kBlock);

    else if (isSigVBargraph(sig, l, x, y, s1))  return T(s1, env)->promoteVariability(kBlock);


	else if ( isSigSoundfile(sig,l) )		        { return makeSimpleType(kInt, kBlock, kExec, kVect, kNum, interval(0,0x7FFFFFFF));	}
	else if ( isSigSoundfileLength(sig,sf) )		{ T(sf,env); return makeSimpleType(kInt, kBlock, kExec, kVect, kNum, interval(0,0x7FFFFFFF));	}
	else if ( isSigSoundfileRate(sig,sf) )		    { T(sf,env); return makeSimpleType(kInt, kBlock, kExec, kVect, kNum, interval(0,0x7FFFFFFF));	}
	else if ( isSigSoundfileChannel(sig,sf,x,s1))   { T(sf,env); T(x,env); T(s1,env); return makeSimpleType(kReal, kSamp, kExec, kVect, kNum, interval());	}


    else if (isSigAttach(sig, s1, s2))          { T(s2,env); return T(s1,env); }

    else if (isSigEnable(sig, s1, s2))          { T(s2,env); return T(s1,env); }

    else if (isSigControl(sig, s1, s2))         { T(s2,env); return T(s1,env); }

    else if (isRec(sig, var, body))             return infereRecType(sig, body, env);

	else if (isProj(sig, &i, s1))				return infereProjType(T(s1,env),i,kScal);

    else if (isSigTable(sig, id, s1, s2)) 		{ checkInt(checkInit(T(s1,env))); return makeTableType(checkInit(T(s2,env))); }

	else if (isSigWRTbl(sig, id, s1, s2, s3)) 	return infereWriteTableType(T(s1,env), T(s2,env), T(s3,env));

	else if (isSigRDTbl(sig, s1, s2)) 			return infereReadTableType(T(s1,env), T(s2,env));

    else if (isSigGen(sig, s1)) 				return T(s1,gGlobal->NULLTYPEENV);

    else if ( isSigDocConstantTbl(sig, x, y) )	return infereDocConstantTblType(T(x,env), T(y,env));
    else if ( isSigDocWriteTbl(sig,x,y,z,u) )	return infereDocWriteTblType(T(x,env), T(y,env), T(z,env), T(u,env));
    else if ( isSigDocAccessTbl(sig, x, y) )    return infereDocAccessTblType(T(x,env), T(y,env));

	else if (isSigSelect2(sig,sel,s1,s2)) 		{
                                                  SimpleType *st1, *st2, *stsel;

                                                  st1 = isSimpleType(T(s1,env));
                                                  st2 = isSimpleType(T(s2,env));
                                                  stsel = isSimpleType(T(sel,env));

                                                  return makeSimpleType( st1->nature()|st2->nature(),
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

	// unrecognized signal here
    throw faustexception("ERROR inferring signal type : unrecognized signal\n");
	return 0;
}

/**
 *	Infere the type of a projection (selection) of a tuplet element
 */
static Type infereProjType(Type t, int i, int vec)
{
	TupletType* tt = isTupletType(t);
	if (tt == 0) {
	    stringstream error;
        error << "ERROR inferring projection type, not a tuplet type : " << t << endl;
        throw faustexception(error.str());
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
        stringstream error;
        error << "ERROR inferring write table type, wrong table type : " << tbl << endl;
        throw faustexception(error.str());
	}
	SimpleType* st = isSimpleType(wi);
	if (st == 0 || st->nature() > kInt) {
	    stringstream error;
        error << "ERROR infering write table type, wrong write index type : " << wi << endl;
        throw faustexception(error.str());
	}

	int n = tt->nature();
	int v = wi->variability() | wd->variability();
	int c = wi->computability() | wd->computability();
	int vec = wi->vectorability() | wd->vectorability();

    return makeTableType(tt->content(), n, v, c, vec);
}

/**
 *	Infere the type of the result of reading a table
 */
static Type infereReadTableType(Type tbl, Type ri)
{
	TableType*	tt = isTableType(tbl);
	if (tt == 0) {
        stringstream error;
        error << "ERROR inferring read table type, wrong table type : " << tbl << endl;
        throw faustexception(error.str());
	}
	SimpleType* st = isSimpleType(ri);
	if (st == 0 || st->nature() > kInt) {
        stringstream error;
        error << "ERROR infering read table type, wrong write index type : " << ri << endl;
        throw faustexception(error.str());
	}
    Type temp = makeSimpleType(
        tbl->nature(),
        ri->variability(),
        kInit | ri->computability(),
        ri->vectorability(),
        tbl->boolean(),
        tbl->getInterval());

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
    faustassert(isList(t));

    vector<Type> v;
    while (isList(t)) { v.push_back(gGlobal->TREC); t = tl(t); };
    return new TupletType(v);
}

/**
 * Infere the type of e recursive block by trying solutions of
 * increasing generality
 */
static Type infereRecType (Tree sig, Tree body, Tree env)
{
    faustassert(false); // we should not come here
    return 0;
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
        return makeSimpleType(ffrestype(ff),kSamp,kInit,kVect,kNum, interval());
	} else {
		// otherwise variability and computability depends
		// arguments (OR of all arg types)
        Type t = makeSimpleType(kInt,kKonst,kInit,kVect,kNum, interval());
		while (isList(ls)) { t = t|T(hd(ls),env); ls=tl(ls); }
		// but the result type is defined by the function

		//return t;
        return makeSimpleType(	ffrestype(ff),
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
    return makeSimpleType(tree2int(type),kKonst,kInit,kVect,kNum, interval());
}

/**
 *  Infere the type of a foreign variable
 */
static Type infereFVarType (Tree type)
{
    // une variable externe ne peut pas se calculer au plus tot qu'a
    // l'execution. Elle est varie par blocs comme les éléments d'interface utilisateur.
    return makeSimpleType(tree2int(type),kBlock,kExec,kVect,kNum, interval());
}

/**
 *  Infere the type of a waveform:
 *  - the nature is int if all values are int, otherwise it is float
 *  - the variability is by samples
 *  - the waveform is known at compile time
 *  - it can be vectorized because all values are known
 *  - knum ???
 *  - the interval is min and max of values
 */
static Type infereWaveformType (Tree wfsig, Tree env)
{
    bool    iflag = true;
    int     n = wfsig->arity();
    double  lo, hi;

    if (n == 0) {
        throw faustexception("ERROR, empty waveform");
    }

    lo = hi = tree2float(wfsig->branch(0));
    iflag = isInt(wfsig->branch(0)->node());
    T(wfsig->branch(0), env);

    for (int i = 1; i < n; i++)  {
        Tree v = wfsig->branch(i);
        T(v,env);
        // compute range
        double f = tree2float(v);
        if (f < lo) {
            lo = f;
        } else if (f > hi) {
            hi = f;
        }
        iflag &= isInt(v->node());
    }

    return makeSimpleType((iflag)?kInt:kReal, kSamp, kComp, kScal, kNum, interval(lo,hi));
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
            stringstream error;
            error << "ERROR : unrecognized opcode : " << opcode << endl;
            throw faustexception(error.str());
    }

    return interval();
}
