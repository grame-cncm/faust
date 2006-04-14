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


#include "compile.hh"
#include "sigtype.hh"

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>

#include "sigprint.hh"
#include "sigtyperules.hh"
#include "recursivness.hh"
#include "simplify.hh"
#include "privatise.hh"
#include "prim2.hh"
#include "xtended.hh"
#include "contextor.hh"

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

string ScalarCompiler::getFreshID(const char* prefix)
{
	char c[64];

	if (fIDCounters.find(prefix) == fIDCounters.end()) {
		fIDCounters[prefix]=0;
	}
	int n = fIDCounters[prefix];
	fIDCounters[prefix] = n+1;

	snprintf(c, 63, "%s%d", prefix, n);
	return string(c);
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

  	fCompileKey = makeCompileKey(L3);

  	return L3;
}

Tree ScalarCompiler::prepare2(Tree L0)
{
  //Tree L3 = Compiler::prepare2(L0);

  sharingAnalysis(L0);			// annotate L3 with sharing count

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
		fClass->addSlowCode(subst("float* input$0 __attribute__ ((aligned(16))); input$0 = input[$0];", T(i)));
	}
	for (int i = 0; i < fClass->outputs(); i++) {
		fClass->addSlowCode(subst("float* output$0 __attribute__ ((aligned(16))); output$0 = output[$0];", T(i)));
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
	cerr << "ScalarCompiler::CS (" << *sig << ") with env " << *env << endl;
#endif

	if (getProperty(sig, fCompileKey, t)) {
		// terme deja visité

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
			cerr << "changement de recursivité : "
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
		cerr << "ScalarCompiler::CS (" << *sig << ") with env " << *env << " -computed-> " << *r << endl;
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
	Tree 	c, sel, x, y, z, var, le, label, id, ff, largs, type, name, file;

	//printf("compilation of %p : ", sig); print(sig); printf("\n");

		 if ( getUserData(sig) ) 					{ return generateXtended(sig); }
	else if ( isSigInt(sig, &i) ) 					{ return T(i); }
	else if ( isSigReal(sig, &r) ) 					{ return T(r); }
	else if ( isSigInput(sig, &i) ) 				{ return generateInput 		(sig, T(i)); 			}
	else if ( isSigOutput(sig, &i, x) ) 			{ return generateOutput 	(sig, T(i), CS(x));}

	else if ( isSigDelay1(sig, x) ) 				{ return generateDelay1 	(sig, x); 				}

	else if ( isSigFixDelay(sig, x, y) ) 			{ return generateFixDelay 	(sig, x, y); 			}
	else if ( isSigPrefix(sig, x, y) ) 				{ return generatePrefix 	(sig, x, y); 			}
	else if ( isSigIota(sig, x) ) 					{ return generateIota 		(sig, x); 				}

	else if ( isSigBinOp(sig, &i, x, y) )			{ return generateBinOp 		(sig, i, x, y); 		}
	else if ( isSigFFun(sig, ff, largs) )			{ return generateFFun 		(sig, ff, largs); 		}
	else if ( isSigFConst(sig, type, name, file) )	{ addIncludeFile(tree2str(file));	return tree2str(name); 	}

	else if ( isSigTable(sig, id, x, y) ) 			{ return generateTable 		(sig, x, y); 			}
	else if ( isSigWRTbl(sig, id, x, y, z) )		{ return generateWRTbl 		(sig, x, y, z); 		}
	else if ( isSigRDTbl(sig, x, y) ) 				{ return generateRDTbl 		(sig, x, y); 			}

	else if ( isSigSelect2(sig, sel, x, y) ) 		{ return generateSelect2 	(sig, sel, x, y); 		}
	else if ( isSigSelect3(sig, sel, x, y, z) ) 	{ return generateSelect3 	(sig, sel, x, y, z); 	}

	else if ( isSigGen(sig, x) ) 					{ return generateSigGen 	(sig, x); 				}

	else if ( isProj(sig, &i, x) ) 					{ return generateRecProj 	(sig, CS(x), i); 	}
	else if ( isRec(sig, var, le))					{ return generateRecGroup 	(sig, var, le); 		}
	//else if ( isRef(sig, var) ) 					{ return CS(var); } //compiled in enclosing rec

	else if ( isSigIntCast(sig, x) ) 				{ return generateIntCast   	(sig, x); 				}
	else if ( isSigFloatCast(sig, x) ) 				{ return generateFloatCast 	(sig, x); 				}

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

string ScalarCompiler::generateCacheCode(Tree sig, const string& exp)
{
	string 		vname, ctype;
	int 		sharing = getSharingCount(sig);
	Tree		t;

	// check reentrance
	if (getProperty(sig, fCompileKey, t)) {
		//cerr << "reentrance cache pour : "; printSignal (sig, stderr); cerr << endl;
		return name(t->node().getSym());
	}

	if (sharing == 1) {
 		//cerr << "pas de cache code pour : "; printSignal (sig, stderr); cerr << endl;

		return exp;

	} else if (sharing > 1) {
		Type t = getSigType(sig);
 		//cerr << "generation du cache code pour : " ; printSignal(sig, stderr); cerr << " qui est de type " << t << endl;

		switch (t->variability()) {

			case kKonst :

				if (t->nature() == kInt) {
					ctype = "int"; vname = getFreshID("idata");

				} else {
					ctype = "float"; vname = getFreshID("fdata");

				}

				fClass->addDeclCode(subst("$0 \t$1;", ctype, vname));
				fClass->addInitCode(subst("$0 = $1;", vname, exp));
				break;

			case kBlock :

				if (t->nature() == kInt) {
					ctype = "int"; vname = getFreshID("itemp");

				} else {
					ctype = "float"; vname = getFreshID("ftemp");

				}

				fClass->addSlowCode(subst("$0 $1 = $2;", ctype, vname, exp));
				break;

			case kSamp :

				if (t->nature() == kInt) {
					ctype = "int"; vname = getFreshID("itemp");

				} else {
					ctype = "float"; vname = getFreshID("ftemp");

				}

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
	// YO le 21/04/05 : La lecture des tables n'était pas mise dans le cache
	// et donc le code était dupliqué (dans tester.dsp par exemple)
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

// Genere le nom d'une variable recursive permanente
static string makeRecVarPermName(const string& groupID, int i)
{
	return subst("$0_$1", groupID, T(i));
}

// Genere le nom d'une variable recursive temporaire
static string makeRecVarTempName(const string& groupID, int i)
{
	return subst("$0temp$1", groupID, T(i));
}

// Donne le nom du type C correspondant à la nature d'un signal
static string cType (Type t)
{
	return (t->nature() == kInt) ? "int" : "float";
}

// Donne le nom zero correspondant à la nature d'un signal
static string cZero (Type t)
{
	return (t->nature() == kInt) ? "0" : "0.0";
}


/*--------------------------------------------------------------------------
							   Fonctions de génération
----------------------------------------------------------------------------*/

// Groupe de signaux mutuellement recursifs


string ScalarCompiler::generateRecGroup(Tree sig, Tree var, Tree le)
{
	Type 	t 	= getSigType(sig);//, tEnv);
	int 	n 	= len(le);
	string 	ID 	= getFreshID("R");

	// store the variable name associated with this recursive group
	setProperty(ref(var), fCompileKey, tree(ID.c_str()));

	// test
	for (int i=0; i<n; i++) {
		Tree e = nth(le, i);

		// audit des expressions recursives
		Tree pr0 = sigProj(i,sig);			// P_i(X)
		Tree pr1 = sigDelay1(pr0);			// Z(P_i(X))
		int s0 = getSharingCount(pr0);
		int s1 = getSharingCount(pr1);
		//cerr << "Projection " << i << " s0=" << s0 << ", s1=" << s1 << endl;
		if (s0==0) {
			//cerr << "Projection " << i << " non utilisée, ne pas la compiler" << endl;
			assert(s1==0);

		} else if (s1==0) {
			//cerr << "Projection " << i << " est une fausse récursion" << endl;
			string c;
			if (s0>1 && getSharingCount(e) == 1) {
				//cerr << "we need to cache the value" << endl;
				c = generateCacheCode(pr0, CS(e));
			} else {
				//cerr << "we don't need to cache the value" << endl;
				c = CS(e);
			}
			setProperty(pr0, fCompileKey, tree(c.c_str()));

		} else {
			//cerr << "Projection " << i << " est une récursion normale" << endl;

			Type te = getSigType(e);//, tEnv2);
			string vperm = makeRecVarPermName(ID, i);
			string vtemp = makeRecVarTempName(ID, i);
			string type = cType(te);
			string zero = cZero(te);
			fClass->addDeclCode(subst("$0 \t$1;", type, vperm));
			fClass->addInitCode(subst("$0 = $1;", vperm, zero));
			fClass->addExecCode(subst("$0 $1 = $2;", type, vtemp, CS(e)));
			fClass->addPostCode(subst("$0 = $1;", vperm, vtemp));
		}
	}
	return ID;
}


// Projection : selection du ième signal d'un groupe recursif
string ScalarCompiler::generateRecProj(Tree sig, const string& ID, int i)
{
	Tree t;
	if (getProperty(sig, fCompileKey, t)) {
		//cerr << "projection has been optimized " << *t << endl;
		return name(t->node().getSym());
	} else {
		return makeRecVarTempName(ID, i);
	}
}


/*****************************************************************************
							   1-SAMPLE DELAY
*****************************************************************************/

string ScalarCompiler::generateDelay1 (Tree sig, Tree e)
{
	//cerr << "generate delay 1 : " << *sig << endl;
	{// check for possible optimisation
		int i;
		Tree f, var, le;
		if (isProj(e, &i, f) && isRec(f, var, le)) {
			string ID = CS(f);
			string var = makeRecVarPermName(ID,i);
			//cerr << "delay of recursive signal optimisation : " << var << endl;
			return var;
		}
	}

	string res = CS(e);


	// check reentrance
	Tree t; if (getProperty(sig, fCompileKey, t)) {
		//cerr << "reentrance cache pour : "; printSignal (sig, stderr); cerr << endl;
		return name(t->node().getSym());
	}

	Type te = getSigType(e);

	string vperm = getFreshID("M");
	string vtemp = getFreshID("T");

	string type = cType(te);
	string zero = cZero(te);

	fClass->addDeclCode(subst("$0 \t$1;", type, vperm));
	fClass->addInitCode(subst("$0 = $1;", vperm, zero));

	fClass->addExecCode(subst("$0 $1 = $2;", type, vtemp, res));
	fClass->addPostCode(subst("$0 = $1;", vperm, vtemp));
	return vperm;
}


/*****************************************************************************
							   N-SAMPLE FIXED DELAY
*****************************************************************************/

string ScalarCompiler::generateFixDelay (Tree sig, Tree e, Tree n)
{
	int size;
	if (!isSigInt(n, &size)) { fprintf(stderr, "error in generateFixDelay\n"); exit(1); }
	// ajout YO
	Tree iota = sigIota(n);
	recursivnessAnnotation(iota);

	string idx = CS(sigIota(n));
	Type te = getSigType(e);

	string vperm = getFreshID("dline");
	string vtemp = getFreshID("T");

	string ct = cType(te);
	string cz = cZero(te);

	fClass->addDeclCode(subst("$0 \t$1[$2];", ct, vperm, T(size) ));
	fClass->addInitCode(subst("for(int i=0; i<$0; i++) $1[i]=$2;", T(size), vperm, cz));

	fClass->addExecCode(subst("$0 $1 = $2[$3];", ct, vtemp, vperm, idx));
	fClass->addExecCode(subst("$0[$1] = $2;", vperm, idx, CS(e)));
	return vtemp;
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

string ScalarCompiler::generateIota (Tree sig, Tree n)
{
	int size;
	if (!isSigInt(n, &size)) { fprintf(stderr, "error in generateIota\n"); exit(1); }

	string vperm = getFreshID("iota");

	fClass->addDeclCode(subst("int \t$0;",  vperm));
	fClass->addInitCode(subst("$0 = 0;", vperm));

#if 0
	fClass->addExecCode(subst("$0 = ($0+1)%$1;", vperm, T(size)));
#else
	fClass->addExecCode(subst("if (++$0 == $1) $0=0;", vperm, T(size)));
#endif
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
