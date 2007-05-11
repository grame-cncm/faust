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

/*****************************************************************************
	HISTORY
	22/01/05 : corrected bug on bool signals cached in float variables
*****************************************************************************/


#include "compile_scal.hh"
#include "compile_scal.hh"

#include "compile.hh"
#include "sigtype.hh"

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>

#include "sigprint.hh"
#include "sigtyperules.hh"
#include "recursivness.hh"
#include "simplify.hh"
#include "privatise.hh"
#include "prim2.hh"
#include "xtended.hh"
#include "contextor.hh"
#include "compatibility.hh"
#include "ppsig.hh"

extern bool	gLessTempSwitch;
extern int		gMaxCopyDelay;

static void setVectorNameProperty(Tree sig, const string& vecname);
static bool getVectorNameProperty(Tree sig, string& vecname);
static int pow2limit(int x);

static Klass* signal2klass (const string& name, Tree sig)
{
	Type t = getSigType(sig); //, NULLENV);
	if (t->nature() == kInt) {

		ScalarCompiler C( new SigIntGenKlass(name) );
		C.compileSingleSignal(sig);
		return C.getClass();

	} else {

		ScalarCompiler C( new SigFloatGenKlass(name) );
		C.compileSingleSignal(sig);
		return C.getClass();

	}
}


/*****************************************************************************
						getFreshID
*****************************************************************************/

map<string, int>	ScalarCompiler::fIDCounters;

string ScalarCompiler::getFreshID(const string& prefix)
{
	if (fIDCounters.find(prefix) == fIDCounters.end()) {
		fIDCounters[prefix]=0;
	}
	int n = fIDCounters[prefix];
	fIDCounters[prefix] = n+1;
	return subst("$0$1", prefix, T(n));
}



/*****************************************************************************
						makeCompileKey
*****************************************************************************/

Tree ScalarCompiler::makeCompileKey(Tree t)
{
	char 	name[256];
	snprintf(name, 256, "COMPILED IN %p : ", (CTree*)t);
	return tree(unique(name));
}

/*****************************************************************************
						    prepare
*****************************************************************************/

Tree ScalarCompiler::prepare(Tree LS)
{
	Tree L1 = deBruijn2Sym(LS);   	// convert debruijn recursion into symbolic recursion
	Tree L2 = simplify(L1);			// simplify by executing every computable operation
	Tree L3 = privatise(L2);		// Un-share tables with multiple writers

	recursivnessAnnotation(L3);		// Annotate L3 with recursivness information
	typeAnnotation(L3);				// Annotate L3 with type information
	sharingAnalysis(L3);			// annotate L3 with sharing count
  	fOccMarkup.mark(L3);			// annotate L3 with occurences analysis

  	fCompileKey = makeCompileKey(L3);

  	return L3;
}

Tree ScalarCompiler::prepare2(Tree L0)
{
	recursivnessAnnotation(L0);		// Annotate L0 with recursivness information
	typeAnnotation(L0);				// Annotate L0 with type information	
	sharingAnalysis(L0);			// annotate L0 with sharing count
 	fOccMarkup.mark(L0);			// annotate L0 with occurences analysis

  	fCompileKey = makeCompileKey(L0);

  	return L0;
}

/*****************************************************************************
						    compileMultiSignal
*****************************************************************************/

void ScalarCompiler::compileMultiSignal (Tree L)
{
	contextor recursivness(0);
	L = prepare(L);		// optimize, share and annotate expression
	for (int i = 0; i < fClass->inputs(); i++) {
		fClass->addSlowCode(subst("float* input$0 = input[$0];", T(i)));
	}
	for (int i = 0; i < fClass->outputs(); i++) {
		fClass->addSlowCode(subst("float* output$0 = output[$0];", T(i)));
	}
	for (int i = 0; isList(L); L = tl(L), i++) {
		Tree sig = hd(L);
		fClass->addExecCode(subst("output$0[i] = $1;", T(i), CS(sig)));
	}
	generateUserInterfaceTree(prepareUserInterfaceTree(fUIRoot));
	if (fDescription) {
		fDescription->ui(prepareUserInterfaceTree(fUIRoot));
	}
}


/*****************************************************************************
						    compileSingleSignal
*****************************************************************************/

void ScalarCompiler::compileSingleSignal (Tree sig)
{
	//contextor recursivness(0);
	sig = prepare2(sig);		// optimize and annotate expression
	fClass->addExecCode(subst("output[i] = $0;", CS(sig)));
	generateUserInterfaceTree(prepareUserInterfaceTree(fUIRoot));
	if (fDescription) {
		fDescription->ui(prepareUserInterfaceTree(fUIRoot));
	}
}


/*****************************************************************************
							 CS : compile a signal
*****************************************************************************/

/**
 * Test if a signal is already compiled
 * @param sig the signal expression to compile.
 * @param name the string representing the compiled expression.
 * @return true is already compiled
 */
bool ScalarCompiler::getCompiledExpression(Tree sig, string& cexp)
{
	if (getProperty(sig, fCompileKey, sig)) {
		cexp = name(sig->node().getSym());
		return true;
	} else {
		return false;
	}
}

/**
 * Set the string of a compiled expression is already compiled
 * @param sig the signal expression to compile.
 * @param cexp the string representing the compiled expression.
 * @return the cexp (for commodity)
 */
string ScalarCompiler::setCompiledExpression(Tree sig, const string& cexp)
{
	setProperty(sig, fCompileKey, tree(cexp.c_str()));
	return cexp;
}

/**
 * Compile a signal
 * @param sig the signal expression to compile.
 * @return the C code translation of sig as a string
 */

string	ScalarCompiler::CS (Tree sig)
{
	contextor	contextRecursivness;
	Tree t;
#if 0
	cerr << "ScalarCompiler::CS (" << *getSigType(sig) << ':' << ppsig(sig) << ")" << endl;
#endif

	if (getProperty(sig, fCompileKey, t)) {
		// terme deja visit�
#if 0
		fprintf(stderr, "RETURN of CS(");
			print(env, stderr);
			fprintf(stderr, ", ");
			printSignal(sig, stderr);
		fprintf(stderr, ") -found-> "); print(t, stderr); fputc('\n', stderr);
#endif
		return name(t->node().getSym());

	} else {

		if (getRecursivness(sig) != contextRecursivness.get()) {
		#if 0
			cerr << "changement de recursivit�: "
				 << contextRecursivness.get()
				 << " -> "
				 << getRecursivness(sig)
				 << " for expression "CS
				 << *sig
				 << endl;
		#endif
			contextRecursivness.set(getRecursivness(sig));
		}
		string s = generateCode(sig);
		const char * r = s.c_str();
		setProperty(sig, fCompileKey, tree(r));

#if 0
		cerr << "ScalarCompiler::CS (" << *sig << ") -computed-> " << *r << endl;
#endif
		return s;
	}
}


/*****************************************************************************
						generateCode : dispatch according to signal
*****************************************************************************/
/**
 * Main code generator dispatch.
 * @param sig the signal expression to compile.
 * @return the C code translation of sig
 */

string	ScalarCompiler::generateCode (Tree sig)
{
#if 0
	fprintf(stderr, "CALL generateCode(");
		print(env, stderr);
		fprintf(stderr, ", ");
		printSignal(sig, stderr);
	fprintf(stderr, ")\n");
#endif

	int 	i;
	float	r;
	//const char	*ct, *vn;
	Tree 	c, sel, x, y, z, /*var, le,*/ label, id, ff, largs, type, name, file;

	//printf("compilation of %p : ", sig); print(sig); printf("\n");

		 if ( getUserData(sig) ) 					{ return generateXtended(sig); }
	else if ( isSigInt(sig, &i) ) 					{ return generateNumber(sig, T(i)); }
	else if ( isSigReal(sig, &r) ) 				{ return generateNumber(sig, T(r)); }
	else if ( isSigInput(sig, &i) ) 				{ return generateInput 	(sig, T(i)); 			}
	else if ( isSigOutput(sig, &i, x) ) 			{ return generateOutput 	(sig, T(i), CS(x));}

	//else if ( isSigDelay1(sig, x) ) 				{ return generateDelay1 	(sig, x); 				}

	else if ( isSigFixDelay(sig, x, y) ) 			{ return generateFixDelay 	(sig, x, y); 			}
	else if ( isSigPrefix(sig, x, y) ) 			{ return generatePrefix 	(sig, x, y); 			}
	else if ( isSigIota(sig, x) ) 					{ return generateIota 		(sig, x); 				}

	else if ( isSigBinOp(sig, &i, x, y) )			{ return generateBinOp 	(sig, i, x, y); 		}
	else if ( isSigFFun(sig, ff, largs) )			{ return generateFFun 		(sig, ff, largs); 		}
	else if ( isSigFConst(sig, type, name, file) )	{ addIncludeFile(tree2str(file));	return tree2str(name); 	}

	else if ( isSigTable(sig, id, x, y) ) 			{ return generateTable 	(sig, x, y); 			}
	else if ( isSigWRTbl(sig, id, x, y, z) )		{ return generateWRTbl 	(sig, x, y, z); 		}
	else if ( isSigRDTbl(sig, x, y) ) 				{ return generateRDTbl 	(sig, x, y); 			}

	else if ( isSigSelect2(sig, sel, x, y) ) 		{ return generateSelect2 	(sig, sel, x, y); 		}
	else if ( isSigSelect3(sig, sel, x, y, z) ) 	{ return generateSelect3 	(sig, sel, x, y, z); 	}

	else if ( isSigGen(sig, x) ) 					{ return generateSigGen 	(sig, x); 				}

	else if ( isProj(sig, &i, x) ) 				{ return generateRecProj 	(sig, x, i); 	}

	else if ( isSigIntCast(sig, x) ) 				{ return generateIntCast   (sig, x); 				}
	else if ( isSigFloatCast(sig, x) ) 			{ return generateFloatCast (sig, x); 				}

	else if ( isSigButton(sig, label) ) 			{ return generateButton   	(sig, label); 			}
	else if ( isSigCheckbox(sig, label) ) 			{ return generateCheckbox 	(sig, label); 			}
	else if ( isSigVSlider(sig, label,c,x,y,z) )	{ return generateVSlider 	(sig, label, c,x,y,z); }
	else if ( isSigHSlider(sig, label,c,x,y,z) )	{ return generateHSlider 	(sig, label, c,x,y,z); }
	else if ( isSigNumEntry(sig, label,c,x,y,z) )	{ return generateNumEntry 	(sig, label, c,x,y,z); }

	else if ( isSigVBargraph(sig, label,x,y,z) )	{ return generateVBargraph 	(sig, label, x, y, CS(z)); }
	else if ( isSigHBargraph(sig, label,x,y,z) )	{ return generateHBargraph 	(sig, label, x, y, CS(z)); }
	else if ( isSigAttach(sig, x, y) )				{ CS(y); return CS(x); }

	else {
		printf("Error in compiling signal, unrecognized signal : ");
		print(sig);
		printf("\n");
		exit(1);
	}
	return "error in generate code";
}


/*****************************************************************************
							   NUMBERS
*****************************************************************************/


string ScalarCompiler::generateNumber (Tree sig, const string& exp)
{
	string		ctype, vname;
	Occurences* o = fOccMarkup.retrieve(sig);
	
	// check for number occuring in delays
	if (o->getMaxDelay()>0) {
		//cerr << "generate number with delay" << endl;
		getTypedNames(getSigType(sig), "Vec", ctype, vname);
		return generateDelayVec(sig, exp, ctype, vname, o->getMaxDelay());
	} else {
		//cerr << "generate number without delay" << endl;
		return exp;
	}
}


/*****************************************************************************
							   INPUTS - OUTPUTS
*****************************************************************************/


string ScalarCompiler::generateInput (Tree sig, const string& idx)
{
	return generateCacheCode(sig, subst("input$0[i]", idx));
}


string ScalarCompiler::generateOutput (Tree sig, const string& idx, const string& arg)
{
	string dst = subst("output$0[i]", idx);
	fClass->addExecCode(subst("$0 = $1;", dst, arg));
	return dst;
}


/*****************************************************************************
							   BINARY OPERATION
*****************************************************************************/

string ScalarCompiler::generateBinOp(Tree sig, int opcode, Tree arg1, Tree arg2)
{
	return generateCacheCode(sig, subst("($0 $1 $2)", CS(arg1), gBinOpTable[opcode]->fName, CS(arg2)));
}


/*****************************************************************************
							   Primitive Operations
*****************************************************************************/

string ScalarCompiler::generateFFun(Tree sig, Tree ff, Tree largs)
{
	addIncludeFile(ffincfile(ff)); 	//printf("inc file %s\n", ffincfile(ff));
	addLibrary(fflibfile(ff));		//printf("lib file %s\n", fflibfile(ff));
	switch (ffarity(ff)) {
		case 0 : return generateCacheCode(sig, subst("$0()", ffname(ff)));
		case 1 : return generateCacheCode(sig, subst("$0($1)", ffname(ff), CS(nth(largs,0))));
		case 2 : return generateCacheCode(sig, subst("$0($1, $2)", ffname(ff), CS(nth(largs,0)), CS(nth(largs,1))));
		case 3 : return generateCacheCode(sig, subst("$0($1, $2, $3)", ffname(ff), CS(nth(largs,0)), CS(nth(largs,1)), CS(nth(largs,2))));
		default : fprintf(stderr, "error inside generateFFun"); exit(1);
	}
	return "Arity Error in FFun";
}


/*****************************************************************************
							   CACHE CODE
*****************************************************************************/

void ScalarCompiler::getTypedNames(Type t, const string& prefix, string& ctype, string& vname)
{
	if (t->nature() == kInt) {
		ctype = "int"; vname = subst("i$0", getFreshID(prefix));
	} else {
		ctype = "float"; vname = subst("f$0", getFreshID(prefix));
	}
} 

string ScalarCompiler::generateCacheCode(Tree sig, const string& exp)
{
	string 		vname, ctype;
	int 		sharing = getSharingCount(sig);
	Tree		result;
	Occurences* o = fOccMarkup.retrieve(sig);

	// check reentrance
	if (getProperty(sig, fCompileKey, result)) {
		//cerr << "reentrance cache pour : "; printSignal (sig, stderr); cerr << endl;
		return name(result->node().getSym());
	}
	
	// check for expression occuring in delays
	if (o->getMaxDelay()>0) {
		getTypedNames(getSigType(sig), "Vec", ctype, vname);
		return generateDelayVec(sig, exp, ctype, vname, o->getMaxDelay());

	} else if (sharing == 1) {
		return exp;

	} else if (sharing > 1) {

		Type t = getSigType(sig);

		switch (t->variability()) {

			case kKonst :

				getTypedNames(getSigType(sig), "Const", ctype, vname);
				fClass->addDeclCode(subst("$0 \t$1;", ctype, vname));
				fClass->addInitCode(subst("$0 = $1;", vname, exp));
				break;

			case kBlock :

				getTypedNames(getSigType(sig), "Slow", ctype, vname);
				fClass->addSlowCode(subst("$0 $1 = $2;", ctype, vname, exp));
				break;

			case kSamp :

				getTypedNames(getSigType(sig), "Temp", ctype, vname);
				fClass->addExecCode(subst("$0 $1 = $2;", ctype, vname, exp));
				break;
		}
		return vname;

	} else {
        cerr << "Error in sharing count (" << sharing << ") for " << *sig << endl;
		exit(1);
	}

	return "Error in generateCacheCode";
}


/*****************************************************************************
							   	    CASTING
*****************************************************************************/


string ScalarCompiler::generateIntCast(Tree sig, Tree x)
{
	return generateCacheCode(sig, subst("int($0)", CS(x)));
}

string ScalarCompiler::generateFloatCast (Tree sig, Tree x)
{
	return generateCacheCode(sig, subst("float($0)", CS(x)));
}

/*****************************************************************************
							user interface elements
*****************************************************************************/

string ScalarCompiler::generateButton(Tree sig, Tree path)
{
	string varname = getFreshID("fbutton");
	fClass->addDeclCode(subst("float \t$0;", varname));
	fClass->addInitCode(subst("$0 = 0.0;", varname));
	addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));
	return generateCacheCode(sig, varname);
}

string ScalarCompiler::generateCheckbox(Tree sig, Tree path)
{
	string varname = getFreshID("fcheckbox");
	fClass->addDeclCode(subst("float \t$0;", varname));
	fClass->addInitCode(subst("$0 = 0.0;", varname));
	addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));
	return generateCacheCode(sig, varname);
}


string ScalarCompiler::generateVSlider(Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
	string varname = getFreshID("fslider");
	fClass->addDeclCode(subst("float \t$0;", varname));
	fClass->addInitCode(subst("$0 = $1;", varname, T(tree2float(cur))));
	addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));
	return generateCacheCode(sig, varname);
}

string ScalarCompiler::generateHSlider(Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
	string varname = getFreshID("fslider");
	fClass->addDeclCode(subst("float \t$0;", varname));
	fClass->addInitCode(subst("$0 = $1;", varname, T(tree2float(cur))));
	addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));
	return generateCacheCode(sig, varname);
}

string ScalarCompiler::generateNumEntry(Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
	string varname = getFreshID("fentry");
	fClass->addDeclCode(subst("float \t$0;", varname));
	fClass->addInitCode(subst("$0 = $1;", varname, T(tree2float(cur))));
	addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));
	return generateCacheCode(sig, varname);
}


string ScalarCompiler::generateVBargraph(Tree sig, Tree path, Tree min, Tree max, const string& exp)
{
	string varname = getFreshID("fbargraph");
	fClass->addDeclCode(subst("float \t$0;", varname));
	addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

	Type t = getSigType(sig);
	switch (t->variability()) {

		case kKonst :
			fClass->addInitCode(subst("$0 = $1;", varname, exp));
			break;

		case kBlock :
			fClass->addSlowCode(subst("$0 = $1;", varname, exp));
			break;

		case kSamp :
			fClass->addExecCode(subst("$0 = $1;", varname, exp));
			break;
	}

	return varname;
}


string ScalarCompiler::generateHBargraph(Tree sig, Tree path, Tree min, Tree max, const string& exp)
{
	string varname = getFreshID("fbargraph");
	fClass->addDeclCode(subst("float \t$0;", varname));
	addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig));

	Type t = getSigType(sig);
	switch (t->variability()) {

		case kKonst :
			fClass->addInitCode(subst("$0 = $1;", varname, exp));
			break;

		case kBlock :
			fClass->addSlowCode(subst("$0 = $1;", varname, exp));
			break;

		case kSamp :
			fClass->addExecCode(subst("$0 = $1;", varname, exp));
			break;
	}

	return varname;
}




/*****************************************************************************
							   	    TABLES
*****************************************************************************/



/*----------------------------------------------------------------------------
						sigGen : initial table content
----------------------------------------------------------------------------*/

string ScalarCompiler::generateSigGen(Tree sig, Tree content)
{
	string klassname = getFreshID("SIG");
	string signame = getFreshID("sig");

	fClass->addSubKlass(signal2klass(klassname, content));
	fClass->addInitCode(subst("$0 $1;", klassname, signame));

	return signame;
}

string ScalarCompiler::generateStaticSigGen(Tree sig, Tree content)
{
	string klassname = getFreshID("SIG");
	string signame = getFreshID("sig");

	fClass->addSubKlass(signal2klass(klassname, content));
	fClass->addStaticInitCode(subst("$0 $1;", klassname, signame));

	return signame;
}


/*----------------------------------------------------------------------------
						sigTable : table declaration
----------------------------------------------------------------------------*/

string ScalarCompiler::generateTable(Tree sig, Tree tsize, Tree content)
{
	string 		generator(CS(content));
	string		ctype, vname;
	int 		size;

	if (!isSigInt(tsize, &size)) {
		//fprintf(stderr, "error in ScalarCompiler::generateTable()\n"); exit(1);
		cerr << "error in ScalarCompiler::generateTable() : "
			 << *tsize
			 << " is not an integer expression "
			 << endl;
	}
	// definition du nom et du type de la table
	// A REVOIR !!!!!!!!!
	Type t = getSigType(content);//, tEnv);
	if (t->nature() == kInt) {
		vname = getFreshID("itbl");
		ctype = "int";
	} else {
		vname = getFreshID("ftbl");
		ctype = "float";
	}

	// declaration de la table
	fClass->addDeclCode(subst("$0 \t$1[$2];", ctype, vname, T(size)));

	// initialisation du generateur de contenu
	fClass->addInitCode(subst("$0.init(samplingFreq);", generator));
	// remplissage de la table
	fClass->addInitCode(subst("$0.fill($1,$2);", generator, T(size), vname));

	// on retourne le nom de la table
	return vname;
}

string ScalarCompiler::generateStaticTable(Tree sig, Tree tsize, Tree content)
{
	//string 		generator(CS(content));
	Tree		g;
	string 		cexp;
	string		ctype, vname;
	int 		size;

	assert ( isSigGen(content, g) );
	if (!getCompiledExpression(content, cexp)) {
		cexp = setCompiledExpression(content, generateStaticSigGen(content, g));
	}

	if (!isSigInt(tsize, &size)) {
		//fprintf(stderr, "error in ScalarCompiler::generateTable()\n"); exit(1);
		cerr << "error in ScalarCompiler::generateTable() : "
			 << *tsize
			 << " is not an integer expression "
			 << endl;
	}
	// definition du nom et du type de la table
	// A REVOIR !!!!!!!!!
	Type t = getSigType(content);//, tEnv);
	if (t->nature() == kInt) {
		vname = getFreshID("itbl");
		ctype = "int";
	} else {
		vname = getFreshID("ftbl");
		ctype = "float";
	}

	// declaration de la table
	fClass->addDeclCode(subst("static $0 \t$1[$2];", ctype, vname, T(size)));
	fClass->addStaticFields(subst("$0 \tmydsp::$1[$2];", ctype, vname, T(size)));

	// initialisation du generateur de contenu
	fClass->addStaticInitCode(subst("$0.init(samplingFreq);", cexp));
	// remplissage de la table
	fClass->addStaticInitCode(subst("$0.fill($1,$2);", cexp, T(size), vname));

	// on retourne le nom de la table
	return vname;
}


/*----------------------------------------------------------------------------
						sigWRTable : table assignement
----------------------------------------------------------------------------*/

string ScalarCompiler::generateWRTbl(Tree sig, Tree tbl, Tree idx, Tree data)
{
	string tblName(CS(tbl));
	fClass->addExecCode(subst("$0[$1] = $2;", tblName, CS(idx), CS(data)));
	return tblName;
}


/*----------------------------------------------------------------------------
						sigRDTable : table access
----------------------------------------------------------------------------*/

string ScalarCompiler::generateRDTbl(Tree sig, Tree tbl, Tree idx)
{
	// YO le 21/04/05 : La lecture des tables n'�ait pas mise dans le cache
	// et donc le code �ait dupliqu�(dans tester.dsp par exemple)
	//return subst("$0[$1]", CS(tEnv, tbl), CS(tEnv, idx));

	//cerr << "generateRDTable " << *sig << endl;
	// test the special case of a read only table that can be compiled
	// has a static member
	Tree 	id, size, content;
	if(	isSigTable(tbl, id, size, content) ) {
		string tblname;
		if (!getCompiledExpression(tbl, tblname)) {
			tblname = setCompiledExpression(tbl, generateStaticTable(tbl, size, content));
		}
		return generateCacheCode(sig, subst("$0[$1]", tblname, CS(idx)));
	} else {
		return generateCacheCode(sig, subst("$0[$1]", CS(tbl), CS(idx)));
	}
}



/*****************************************************************************
							   RECURSIONS
*****************************************************************************/


/*---------------------------------------------------------------------------
							fonctions auxilliaires
----------------------------------------------------------------------------*/


// Projection : selection du iem signal d'un groupe recursif
string ScalarCompiler::generateRecProj(Tree sig, Tree x, int i)
{
	//cerr << "generateRecProj : " << *sig << endl;
	Tree 	var, le;
	int		mxd;

	mxd = fOccMarkup.retrieve(sig)->getMaxDelay();
	if ( isRec(x, var, le) )	{
		string	ctype, vname;
		if (getVectorNameProperty(sig, vname)) {
			return subst("$0[0]", vname);
		} else if (mxd == 0) {
			// branche d'une expression récursive qui ne fait pas 
			// appel à elle-même (donc son mxd == 0);
			//cerr << "mxd = 0 for " << *sig << endl;
			return generateCacheCode(sig, CS(nth(le,i)));
		} else {

			getTypedNames(getSigType(sig), "Rec", ctype, vname);
			setVectorNameProperty(sig, vname);
			return generateDelayVec(sig, CS(nth(le,i)), ctype, vname, mxd);
		}
	} else {
		cerr << "generateRecProj error : " << *sig << endl;
		exit(1);
		return "error";
	}
}



/*****************************************************************************
							   PREFIX, DELAY A PREFIX VALUE
*****************************************************************************/

string ScalarCompiler::generatePrefix (Tree sig, Tree x, Tree e)
{
	Type te = getSigType(sig);//, tEnv);

	string vperm = getFreshID("M");
	string vtemp = getFreshID("T");

	string type = cType(te);

	fClass->addDeclCode(subst("$0 \t$1;", type, vperm));
	fClass->addInitCode(subst("$0 = $1;", vperm, CS(x)));

	fClass->addExecCode(subst("$0 $1 = $2;", type, vtemp, vperm));
	fClass->addExecCode(subst("$0 = $1;", vperm, CS(e)));
	return vtemp;
}


/*****************************************************************************
							   IOTA(n)
*****************************************************************************/
static bool isPowerOf2(int n)
{
	return !(n & (n - 1));
}

string ScalarCompiler::generateIota (Tree sig, Tree n)
{
	int size;
	if (!isSigInt(n, &size)) { fprintf(stderr, "error in generateIota\n"); exit(1); }

	string vperm = getFreshID("iota");

	fClass->addDeclCode(subst("int \t$0;",  vperm));
	fClass->addInitCode(subst("$0 = 0;", vperm));

	if (isPowerOf2(size)) {
		fClass->addExecCode(subst("$0 = ($0+1)&$1;", vperm, T(size-1)));
	} else {
		fClass->addExecCode(subst("if (++$0 == $1) $0=0;", vperm, T(size)));
	}
	return vperm;
}



// a revoir en utilisant la lecture de table et en partageant la construction de la paire de valeurs
// il faudrait egalement tenir compte de la computability et de la variability

string ScalarCompiler::generateSelect2 (Tree sig, Tree sel, Tree s1, Tree s2)
{
	Type t   = getSigType(sig);//, tEnv);
	//Type u1  = getSigType(s1, tEnv);
	//Type u2  = getSigType(s2, tEnv);

	string type = cType(t);
	string var  = getFreshID("S");

	//cerr << "compile a select2 of type = " << t << endl;
	switch (t->variability())
	{
		case kKonst :
			fClass->addDeclCode(subst("$0 \t$1[2];", type, var));
			fClass->addInitCode(subst("$0[0] = $1;", var, CS(s1)));
			fClass->addInitCode(subst("$0[1] = $1;", var, CS(s2)));
			return generateCacheCode(sig, subst("$0[$1]", var, CS(sel)));

		case kBlock :
			fClass->addSlowCode(subst("$0 \t$1[2];", type, var));
			fClass->addSlowCode(subst("$0[0] = $1;", var, CS(s1)));
			fClass->addSlowCode(subst("$0[1] = $1;", var, CS(s2)));
			return generateCacheCode(sig, subst("$0[$1]", var, CS(sel)));

		case kSamp :
			fClass->addExecCode(subst("$0 \t$1[2];", type, var));
			fClass->addExecCode(subst("$0[0] = $1;", var, CS(s1)));
			fClass->addExecCode(subst("$0[1] = $1;", var, CS(s2)));
			return generateCacheCode(sig, subst("$0[$1]", var, CS(sel)));
	}
	return "ScalarCompiler::generateSelect2";
}

string ScalarCompiler::generateSelect3 	(Tree sig, Tree sel, Tree s1, Tree s2, Tree s3)
{
	Type t  = getSigType(sig);//, tEnv);

	string type = cType(t);
	string var  = getFreshID("S");

//	cerr << "compile a select3 of type = " << t << endl;
	fClass->addExecCode(subst("$0 \t$1[3];", type, var));
	fClass->addExecCode(subst("$0[0] = $1;", var, CS(s1)));
	fClass->addExecCode(subst("$0[1] = $2;", var, CS(s2)));
	fClass->addExecCode(subst("$0[2] = $3;", var, CS(s3)));
	return subst("$0[$1]", var, CS(sel));
}

/**
 * retrieve the type annotation of sig
 * @param sig the signal we want to know the type
 */
string ScalarCompiler::generateXtended 	(Tree sig)
{
	xtended* 		p = (xtended*) getUserData(sig);
	vector<string> 	args;
	vector<Type> 	types;

	for (int i=0; i<sig->arity(); i++) {
		args.push_back(CS(sig->branch(i)));
		types.push_back(getSigType(sig->branch(i)));
		//auditSigType(sig->branch(i));
		//types.push_back(TINPUT);
	}

	if (p->needCache()) {
		return generateCacheCode(sig, p->generateCode(fClass, args, types));
	} else {
		return p->generateCode(fClass, args, types);
	}
}



//------------------------------------------------------------------------------------------------


/*****************************************************************************
						vector name property
*****************************************************************************/
static Tree VECTORPROPERTY = tree(symbol("VECTORPROPERTY"));


/**
 * Set the vector name property of a signal, the name of the vector used to
 * store the previous values of the signal to implement a delay.
 * @param sig the signal expression.
 * @param vecname the string representing the vector name.
 * @return true is already compiled
 */
static void setVectorNameProperty(Tree sig, const string& vecname)
{
		const char * r = vecname.c_str();
		setProperty(sig, VECTORPROPERTY, tree(r));
}
	

/**
 * Get the vector name property of a signal, the name of the vector used to
 * store the previous values of the signal to implement a delay.
 * @param sig the signal expression.
 * @param vecname the string where to store the vector name.
 * @return true if the signal has this property, false otherwise
 */

static bool getVectorNameProperty(Tree sig, string& vecname)
{
	if (getProperty(sig, VECTORPROPERTY, sig)) {
		vecname = name(sig->node().getSym());
		return true;
	} else {
		return false;
	}
}


/**
 * Compute the minimal power of 2 greater than x
 */

static int pow2limit(int x)
{
	int n = 2;
	while (n < x) { n = 2*n; }
	return n;
}

/*****************************************************************************
							   N-SAMPLE FIXED DELAY : sig = exp@delay

	case 1-sample max delay :
		Y(t-0)	Y(t-1)
		Temp	Var						gLessTempSwitch = false		
		V[0]	V[1]					gLessTempSwitch = true

	case max delay < gMaxCopyDelay :
		Y(t-0)	Y(t-1)	Y(t-2)  ...
		Temp	V[0]	V[1]	...		gLessTempSwitch = false
		V[0]	V[1]	V[2]	...		gLessTempSwitch = true

	case max delay >= gMaxCopyDelay :
		Y(t-0)	Y(t-1)	Y(t-2)  ...
		Temp	V[0]	V[1]	...
		V[0]	V[1]	V[2]	...

		
*****************************************************************************/

/**
 * Generate code for accessing a delayed signal. The generated code depend of 
 * the maximum delay attached to exp and the gLessTempSwitch. 
 */

string ScalarCompiler::generateFixDelay (Tree sig, Tree exp, Tree delay)
{
	int 	mxd; 
	string 	vecname;
 
	CS(exp); // ensure exp is compiled to have a vector name

	mxd = fOccMarkup.retrieve(exp)->getMaxDelay();

	assert(getVectorNameProperty(exp, vecname));

	if (mxd < gMaxCopyDelay) {

		return generateCacheCode(sig, subst("$0[$1]", vecname, CS(delay)));

	} else {

		// long delay : we use a ring buffer of size 2^x
		int 	N 	= pow2limit( mxd+1 );
		return generateCacheCode(sig, subst("$0[(IOTA-$1)&$2]", vecname, CS(delay), T(N-1))); 
	}
}

#if 0
string ScalarCompiler::generateFixDelay (Tree sig, Tree exp, Tree delay)
{
	int 	mxd, d; 
	string 	vecname;
 
	CS(exp); // ensure exp is compiled to have a vector name

	mxd = fOccMarkup.retrieve(exp)->getMaxDelay();

	assert(isSigInt(delay, &d));
	assert(getVectorNameProperty(exp, vecname));
	assert(d > 0);
	assert(d <= mxd);

	if (mxd == 1) {
		
		// one sample delay
		assert (d == 1);
		if (gLessTempSwitch) {
			return subst("$0[$1]", vecname, T(d));
		} else {
			return vecname;
		}

	} else if (mxd < gMaxCopyDelay) {

		// short delay : we use a table
		if (gLessTempSwitch) {
			return subst("$0[$1]", vecname, T(d));
		} else {
			return subst("$0[$1]", vecname, T(d-1));
		}

	} else {

		// long delay : we use a ring buffer of size 2^x
		int 	N 	= pow2limit( mxd+1 );
		return subst("$0[(IOTA-$1)&$2]", vecname, T(d), T(N-1)); 
	}
}
#endif



/**
 * Generate code for the delay mecchanism. The generated code depend of the
 * maximum delay attached to exp and the "less temporaries" switch
 */

string ScalarCompiler::generateDelayVec(Tree sig, const string& exp, const string& ctype, const string& vname, int mxd)
{
	return generateDelayVecNoTemp(sig, exp, ctype, vname, mxd);
}

#if 0
string ScalarCompiler::generateDelayVec(Tree sig, const string& exp, const string& ctype, const string& vname, int mxd)
{
	if (gLessTempSwitch) {
		return generateDelayVecNoTemp(sig, exp, ctype, vname, mxd);
	} else {
		return generateDelayVecWithTemp(sig, exp, ctype, vname, mxd);
	}
}
#endif



/**
 * Generate code for the delay mecchanism using temporary variables
 */

string ScalarCompiler::generateDelayVecWithTemp(Tree sig, const string& exp, const string& ctype, const string& vname, int mxd)
{
	assert(mxd > 0);
	bool odocc = fOccMarkup.retrieve(sig)->hasOutDelayOccurences();

	if (mxd == 1) {

		// generate code for a one sample delay
		string tname;
		fClass->addDeclCode(subst("$0 \t$1;", ctype, vname));
		fClass->addInitCode(subst("$0 = 0;", vname));
		if (odocc) {
			// y(t) is used, a temporary variable is used
			tname = subst("$0Temp", vname);
			fClass->addExecCode(subst("$0 $1 = $2;", ctype, tname, exp));
			fClass->addPostCode(subst("$0 = $1;", vname, tname));
		} else {
			// y(t) is not used directly, therfore we don't need a temp variable
			tname = "no temporary";
			fClass->addPostCode(subst("$0 = $1;", vname, exp));
		}	
		setVectorNameProperty(sig, vname);	
		return tname;

	} else if (mxd < gMaxCopyDelay) {

		// generate code for a short delay, we copy the delayed samples each time
		string tname = subst("$0Temp", vname);
		
		fClass->addDeclCode(subst("$0 \t$1[$2];", ctype, vname, T(mxd)));
		fClass->addInitCode(subst("for (int i=0; i<$1; i++) $0[i] = 0;", vname, T(mxd)));

		
		// if it is only 2 samples we don't need a loop
		if (mxd == 2) {
			fClass->addPostCode(subst("$0[1] = $0[0]; $0[0] = $1;", vname, tname));
		} else {
			fClass->addPostCode(subst("for (int i=$0; i>0; i--) $1[i] = $1[i-1]; $1[0] = $2;", T(mxd-1), vname, tname));
		} 

		// if y(t) is not used directly we can postpone its computation 
		// in order to use the temp variable for a shorter period
		if (odocc) {
			fClass->addExecCode(subst("$0 $1 = $2;", ctype, tname, exp));
		} else {
			fClass->addPostCode(subst("$0 $1 = $2;", ctype, tname, exp));
		}
			
		setVectorNameProperty(sig, vname);	
		return tname;

	} else {

		// generate code for a long delay : we use a ring buffer of size N = 2**x > mxd
		int 	N = pow2limit(mxd+1);

		// we need a iota index
		ensureIotaCode();

		// declare and init
		fClass->addDeclCode(subst("$0 \t$1[$2];", ctype, vname, T(N)));
		fClass->addInitCode(subst("for (int i=0; i<$1; i++) $0[i] = 0;", vname, T(N)));

		// execute
		string tname;

		if (odocc) {
			tname = subst("$0Temp", vname);
			fClass->addExecCode(subst("$0 $1 = $2;", ctype, tname, exp));
			fClass->addPostCode(subst("$0[IOTA&$1] = $2;", vname, T(N-1), tname));
		} else {
			fClass->addPostCode(subst("$0[IOTA&$1] = $2;", vname, T(N-1), exp));
		}
		setVectorNameProperty(sig, vname);	
		return tname; 
	}
}


/**
 * Generate code for the delay mecchanism without using temporary variables
 */

string ScalarCompiler::generateDelayVecNoTemp(Tree sig, const string& exp, const string& ctype, const string& vname, int mxd)
{
	assert(mxd > 0);

	//bool odocc = fOccMarkup.retrieve(sig)->hasOutDelayOccurences();

	if (mxd < gMaxCopyDelay) {

		// short delay : we copy
		fClass->addDeclCode(subst("$0 \t$1[$2];", ctype, vname, T(mxd+1)));
		fClass->addInitCode(subst("for (int i=0; i<$1; i++) $0[i] = 0;", vname, T(mxd+1)));
		fClass->addExecCode(subst("$0[0] = $1;", vname, exp));
		
		// generate post processing copy code to update delay values
		if (mxd == 1) {
			fClass->addPostCode(subst("$0[1] = $0[0];", vname));
		} else if (mxd == 2) {
			//fClass->addPostCode(subst("$0[2] = $0[1];", vname));
			fClass->addPostCode(subst("$0[2] = $0[1]; $0[1] = $0[0];", vname));
		} else {
			fClass->addPostCode(subst("for (int i=$0; i>0; i--) $1[i] = $1[i-1];", T(mxd), vname));
		} 
		setVectorNameProperty(sig, vname);	
		return subst("$0[0]", vname);

	} else {

		// generate code for a long delay : we use a ring buffer of size N = 2**x > mxd
		int 	N = pow2limit(mxd+1);

		// we need a iota index
		ensureIotaCode();

		// declare and init
		fClass->addDeclCode(subst("$0 \t$1[$2];", ctype, vname, T(N)));
		fClass->addInitCode(subst("for (int i=0; i<$1; i++) $0[i] = 0;", vname, T(N)));

		// execute
		fClass->addExecCode(subst("$0[IOTA&$1] = $2;", vname, T(N-1), exp));
		setVectorNameProperty(sig, vname);	
		return subst("$0[IOTA&$1]", vname, T(N-1)); 
	}
}



/**
 * Generate code for a unique IOTA variable increased at each sample
 * and used to index ring buffers. 
 */
void ScalarCompiler::ensureIotaCode()
{
	if (!fHasIota) {
		fHasIota = true;
		fClass->addDeclCode("int \tIOTA;");
		fClass->addInitCode("IOTA = 0;");
		fClass->addPostCode("IOTA = IOTA+1;");
	}
}
