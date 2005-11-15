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
#include "simplify.hh"
#include "privatise.hh"
#include "prim2.hh"
#include "xtended.hh"

static Klass* signal2klass (const string& name, Tree sig)
{
	Type t = getSigType(sig, NULLENV);
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

Tree ScalarCompiler::prepare(Tree L0)
{
  Tree L3 = Compiler::prepare(L0);

  sharingAnalysis(L3);			// annotate L3 with sharing count

  fCompileKey = makeCompileKey(L3);

  return L3;
}

Tree ScalarCompiler::prepare2(Tree L0)
{
  Tree L3 = Compiler::prepare2(L0);

  sharingAnalysis(L3);			// annotate L3 with sharing count

  fCompileKey = makeCompileKey(L3);

  return L3;
}

/*****************************************************************************
						    compileMultiSignal
*****************************************************************************/

void ScalarCompiler::compileMultiSignal (Tree L)
{	
	L = prepare(L);		// optimize, share and annotate expression
	for (int i = 0; i < fClass->inputs(); i++) {
		fClass->addSlowCode(subst("float* input$0 __attribute__ ((aligned(16))); input$0 = input[$0];", T(i)));
	}
	for (int i = 0; i < fClass->outputs(); i++) {
		fClass->addSlowCode(subst("float* output$0 __attribute__ ((aligned(16))); output$0 = output[$0];", T(i)));
	}
	for (int i = 0; isList(L); L = tl(L), i++) {
		Tree sig = hd(L);
		fClass->addExecCode(subst("output$0[i] = $1;", T(i), CS(NULLENV, sig)));
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
	fClass->addExecCode(subst("output[i] = $0;", CS(NULLENV, sig)));
	generateUserInterfaceTree(prepareUserInterfaceTree(fUIRoot));
	if (fDescription) {
		fDescription->ui(prepareUserInterfaceTree(fUIRoot));
	}
}


/*****************************************************************************
							 CS : compile a signal
*****************************************************************************/
/**
 * Compile a signal
 * @param env the type environment (enclosing recursions).
 * @param sig the signal expression to compile.
 * @return the C code translation of sig as a string
 */

string	ScalarCompiler::CS (Tree env, Tree sig, int ctxt)
{
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
		
		string s = generateCode(env, sig);
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
 * @param env the type environment.
 * @param sig the signal expression to compile.
 * @return the C code translation of sig
 */

string	ScalarCompiler::generateCode (Tree env, Tree sig)
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
	
		 if ( getUserData(sig) ) 					{ return generateXtended(env, sig); }
	else if ( isSigInt(sig, &i) ) 					{ return T(i); }
	else if ( isSigReal(sig, &r) ) 					{ return T(r); }
	else if ( isSigInput(sig, &i) ) 				{ return generateInput 		(env, sig, T(i)); 			}
	else if ( isSigOutput(sig, &i, x) ) 			{ return generateOutput 	(env, sig, T(i), CS(env,x));}
	
	else if ( isSigDelay1(sig, x) ) 				{ return generateDelay1 	(env, sig, x); 				}
	
	else if ( isSigFixDelay(sig, x, y) ) 			{ return generateFixDelay 	(env, sig, x, y); 			}
	else if ( isSigPrefix(sig, x, y) ) 				{ return generatePrefix 	(env, sig, x, y); 			}
	else if ( isSigIota(sig, x) ) 					{ return generateIota 		(env, sig, x); 				}

	else if ( isSigBinOp(sig, &i, x, y) )			{ return generateBinOp 		(env, sig, i, x, y); 		}
	else if ( isSigFFun(sig, ff, largs) )			{ return generateFFun 		(env, sig, ff, largs); 		}
	else if ( isSigFConst(sig, type, name, file) )	{ addIncludeFile(tree2str(file));	return tree2str(name); 	}
	
	else if ( isSigTable(sig, id, x, y) ) 			{ return generateTable 		(env, sig, x, y); 			}
	else if ( isSigWRTbl(sig, id, x, y, z) )		{ return generateWRTbl 		(env, sig, x, y, z); 		}
	else if ( isSigRDTbl(sig, x, y) ) 				{ return generateRDTbl 		(env, sig, x, y); 			}
	
	else if ( isSigSelect2(sig, sel, x, y) ) 		{ return generateSelect2 	(env, sig, sel, x, y); 		}
	else if ( isSigSelect3(sig, sel, x, y, z) ) 	{ return generateSelect3 	(env, sig, sel, x, y, z); 	}
	
	else if ( isSigGen(sig, x) ) 					{ return generateSigGen 	(env, sig, x); 				}

	else if ( isProj(sig, &i, x) ) 					{ return generateRecProj 	(env, sig, CS(env,x), i); 	}
	else if ( isRec(sig, var, le))					{ return generateRecGroup 	(env, sig, var, le); 		}
	//else if ( isRef(sig, var) ) 					{ return CS(env,var); } //compiled in enclosing rec
 
	else if ( isSigIntCast(sig, x) ) 				{ return generateIntCast   	(env, sig, x); 				}
	else if ( isSigFloatCast(sig, x) ) 				{ return generateFloatCast 	(env, sig, x); 				}
 
	else if ( isSigButton(sig, label) ) 			{ return generateButton   	(env, sig, label); 			}
	else if ( isSigCheckbox(sig, label) ) 			{ return generateCheckbox 	(env, sig, label); 			}	
	else if ( isSigVSlider(sig, label,c,x,y,z) )	{ return generateVSlider 	(env, sig, label, c,x,y,z); }
	else if ( isSigHSlider(sig, label,c,x,y,z) )	{ return generateHSlider 	(env, sig, label, c,x,y,z); }
	else if ( isSigNumEntry(sig, label,c,x,y,z) )	{ return generateNumEntry 	(env, sig, label, c,x,y,z); }
	
	else if ( isSigVBargraph(sig, label,x,y,z) )	{ return generateVBargraph 	(env, sig, label, x, y, CS(env,z)); }
	else if ( isSigHBargraph(sig, label,x,y,z) )	{ return generateHBargraph 	(env, sig, label, x, y, CS(env,z)); }
	else if ( isSigAttach(sig, x, y) )				{ CS(env,y); return CS(env,x); }
	
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


string ScalarCompiler::generateInput (Tree tEnv, Tree sig, const string& idx) 
{ 
	return generateCacheCode(tEnv, sig, subst("input$0[i]", idx));
}


string ScalarCompiler::generateOutput (Tree tEnv, Tree sig, const string& idx, const string& arg) 
{ 
	string dst = subst("output$0[i]", idx);
	fClass->addExecCode(subst("$0 = $1;", dst, arg));
	return dst;
}


/*****************************************************************************
							   BINARY OPERATION
*****************************************************************************/

string ScalarCompiler::generateBinOp(Tree tEnv, Tree sig, int opcode, Tree arg1, Tree arg2)
{
	return generateCacheCode(tEnv, sig, subst("($0 $1 $2)", CS(tEnv, arg1), gBinOpTable[opcode]->fName, CS(tEnv, arg2)));
}


/*****************************************************************************
							   Primitive Operations
*****************************************************************************/

string ScalarCompiler::generateFFun(Tree tEnv, Tree sig, Tree ff, Tree largs)
{
	addIncludeFile(ffincfile(ff)); 	//printf("inc file %s\n", ffincfile(ff));
	addLibrary(fflibfile(ff));		//printf("lib file %s\n", fflibfile(ff));
	switch (ffarity(ff)) {
		case 0 : return generateCacheCode(tEnv, sig, subst("$0()", ffname(ff)));
		case 1 : return generateCacheCode(tEnv, sig, subst("$0($1)", ffname(ff), CS(tEnv, nth(largs,0))));
		case 2 : return generateCacheCode(tEnv, sig, subst("$0($1, $2)", ffname(ff), CS(tEnv, nth(largs,0)), CS(tEnv, nth(largs,1))));
		case 3 : return generateCacheCode(tEnv, sig, subst("$0($1, $2, $3)", ffname(ff), CS(tEnv, nth(largs,0)), CS(tEnv, nth(largs,1)), CS(tEnv, nth(largs,2))));
		default : fprintf(stderr, "error inside generateFFun"); exit(1);
	}
	return "Arity Error in FFun";
}


/*****************************************************************************
							   CACHE CODE
*****************************************************************************/

string ScalarCompiler::generateCacheCode(Tree tEnv, Tree sig, const string& exp, int context)
{
	string 		vname, ctype;
	int 		sharing = shcount(fSharingKey, sig);
	
	
	if (sharing == 1) { 
// 		cerr << "pas de cache code pour : "; printSignal (sig, stderr); cerr << endl;
		
		return exp;
		
	} else if (sharing > 1) {
		Type t = getSigType(sig, tEnv);
// 		cerr << "generation du cache code pour : " ; printSignal(sig, stderr); cerr << " qui est de type " << t << endl;
		
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

		fprintf(stderr, "Error in sharing count\n");
		exit(1);
	}
	
	return "Error in generateCacheCode";
}

	


/*****************************************************************************
							   	    CASTING
*****************************************************************************/


string ScalarCompiler::generateIntCast(Tree tEnv, Tree sig, Tree x)
{
	return generateCacheCode(tEnv, sig, subst("int($0)", CS(tEnv, x)));
}
			
string ScalarCompiler::generateFloatCast (Tree tEnv, Tree sig, Tree x)
{
	return generateCacheCode(tEnv, sig, subst("float($0)", CS(tEnv, x)));
}

/*****************************************************************************
							user interface elements
*****************************************************************************/
		
string ScalarCompiler::generateButton(Tree tEnv, Tree sig, Tree path)
{
	string varname = getFreshID("fbutton");
	fClass->addDeclCode(subst("float \t$0;", varname));
	fClass->addInitCode(subst("$0 = 0.0;", varname));
	addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig)); 
	return generateCacheCode(tEnv, sig, varname);
}
		
string ScalarCompiler::generateCheckbox(Tree tEnv, Tree sig, Tree path)
{
	string varname = getFreshID("fcheckbox");
	fClass->addDeclCode(subst("float \t$0;", varname));
	fClass->addInitCode(subst("$0 = 0.0;", varname));
	addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig)); 
	return generateCacheCode(tEnv, sig, varname);
} 


string ScalarCompiler::generateVSlider(Tree tEnv, Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
	string varname = getFreshID("fslider");
	fClass->addDeclCode(subst("float \t$0;", varname));
	fClass->addInitCode(subst("$0 = $1;", varname, T(tree2float(cur))));
	addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig)); 
	return generateCacheCode(tEnv, sig, varname);
}

string ScalarCompiler::generateHSlider(Tree tEnv, Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
	string varname = getFreshID("fslider");
	fClass->addDeclCode(subst("float \t$0;", varname));
	fClass->addInitCode(subst("$0 = $1;", varname, T(tree2float(cur))));
	addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig)); 
	return generateCacheCode(tEnv, sig, varname);
}

string ScalarCompiler::generateNumEntry(Tree tEnv, Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
	string varname = getFreshID("fentry");
	fClass->addDeclCode(subst("float \t$0;", varname));
	fClass->addInitCode(subst("$0 = $1;", varname, T(tree2float(cur))));
	addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig)); 
	return generateCacheCode(tEnv, sig, varname);
}


string ScalarCompiler::generateVBargraph(Tree tEnv, Tree sig, Tree path, Tree min, Tree max, const string& exp)
{
	string varname = getFreshID("fbargraph");
	fClass->addDeclCode(subst("float \t$0;", varname));
	addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig)); 
	
	Type t = getSigType(sig, tEnv);
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


string ScalarCompiler::generateHBargraph(Tree tEnv, Tree sig, Tree path, Tree min, Tree max, const string& exp)
{
	string varname = getFreshID("fbargraph");
	fClass->addDeclCode(subst("float \t$0;", varname));
	addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig)); 
	
	Type t = getSigType(sig, tEnv);
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

string ScalarCompiler::generateSigGen(Tree tEnv, Tree sig, Tree content)
{
	string klassname = getFreshID("SIG");
	string signame = getFreshID("sig");
	
	fClass->addSubKlass(signal2klass(klassname, content));
	fClass->addInitCode(subst("$0 $1;", klassname, signame));
	
	return signame; 
}


/*----------------------------------------------------------------------------
						sigTable : table declaration
----------------------------------------------------------------------------*/

string ScalarCompiler::generateTable(Tree tEnv, Tree sig, Tree tsize, Tree content) 
{
	string 		generator(CS(tEnv, content));
	string		ctype, vname;
	int 		size;
	
	if (!isSigInt(tsize, &size)) { fprintf(stderr, "error\n"); exit(1); }
	// definition du nom et du type de la table
	// A REVOIR !!!!!!!!!
	Type t = getSigType(content, tEnv);
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


/*----------------------------------------------------------------------------
						sigWRTable : table assignement
----------------------------------------------------------------------------*/

string ScalarCompiler::generateWRTbl(Tree tEnv, Tree sig, Tree tbl, Tree idx, Tree data)
{ 
	string tblName(CS(tEnv, tbl));
	fClass->addExecCode(subst("$0[$1] = $2;", tblName, CS(tEnv, idx), CS(tEnv, data)));
	return tblName;
}


/*----------------------------------------------------------------------------
						sigRDTable : table access
----------------------------------------------------------------------------*/

string ScalarCompiler::generateRDTbl(Tree tEnv, Tree sig, Tree tbl, Tree idx)
{ 
	// YO le 21/04/05 : La lecture des tables n'était pas mise dans le cache
	// et donc le code était dupliqué (dans tester.dsp par exemple)
	//return subst("$0[$1]", CS(tEnv, tbl), CS(tEnv, idx));
	return generateCacheCode(tEnv, sig, subst("$0[$1]", CS(tEnv, tbl), CS(tEnv, idx)));
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

// Clef de proprieté associant un nom au label d'un groupe recursif
//Tree RECNAMEPROP = tree(symbol("sigRecNameProp"));


/*--------------------------------------------------------------------------
							   Fonctions de génération
----------------------------------------------------------------------------*/

// Groupe de signaux mutuellement recursifs


string ScalarCompiler::generateRecGroup(Tree tEnv, Tree sig, Tree var, Tree le) 
{ 	
	Type 	t 	= getSigType(sig, tEnv);
	int 	n 	= len(le);
	string 	ID 	= getFreshID("R");
	
	
	// prepare the environments for the subtermes
	Tree	tEnv2	= addEnv(var,t,tEnv);
	
	// store the variable name associated with this recursive group
	setProperty(ref(var), fCompileKey, tree(ID.c_str()));
	
	
	if (n==1) {
		
		Tree e = nth(le, 0);
		Type te = getSigType(e, tEnv2);

		
		string vperm = makeRecVarPermName(ID, 0);
		string type = cType(te);
		string zero = cZero(te);
		fClass->addDeclCode(subst("$0 \t$1;", type, vperm));
		fClass->addInitCode(subst("$0 = $1;", vperm, zero));
		fClass->addExecCode(subst("$0 = $1;", vperm, CS(tEnv2, e)));		
		
	} else {
		
		for (int i=0; i<n; i++) {
			Tree e = nth(le, i);
			Type te = getSigType(e, tEnv2);
			string vperm = makeRecVarPermName(ID, i);
			string vtemp = makeRecVarTempName(ID, i);
			string type = cType(te);
			string zero = cZero(te);
			fClass->addDeclCode(subst("$0 \t$1;", type, vperm));
			fClass->addInitCode(subst("$0 = $1;", vperm, zero));
			fClass->addExecCode(subst("$0 $1 = $2;", type, vtemp, CS(tEnv2, e)));		
		}

		for (int i=0; i<n; i++) {
			fClass->addExecCode(subst("$0 = $1;", makeRecVarPermName(ID, i), makeRecVarTempName(ID, i)));
		}
	}
	return ID; 
}


// Projection : selection du ième signal d'un groupe recursif
string ScalarCompiler::generateRecProj(Tree tEnv, Tree sig, const string& ID, int i) 
{ 
	return makeRecVarPermName(ID, i); 
}


/*****************************************************************************
							   1-SAMPLE DELAY
*****************************************************************************/

string ScalarCompiler::generateDelay1 (Tree tEnv, Tree sig, Tree e)
{
	Type te = getSigType(e, tEnv);

	string vperm = getFreshID("M");
	string vtemp = getFreshID("T");
	
	string type = cType(te);
	string zero = cZero(te);
	
	fClass->addDeclCode(subst("$0 \t$1;", type, vperm));
	fClass->addInitCode(subst("$0 = $1;", vperm, zero));
	
	fClass->addExecCode(subst("$0 $1 = $2;", type, vtemp, vperm));		
	fClass->addExecCode(subst("$0 = $1;", vperm, CS(tEnv, e)));
	return vtemp;		
} 


/*****************************************************************************
							   N-SAMPLE FIXED DELAY
*****************************************************************************/

string ScalarCompiler::generateFixDelay (Tree tEnv, Tree sig, Tree e, Tree n)
{
	int size;
	if (!isSigInt(n, &size)) { fprintf(stderr, "error in generateFixDelay\n"); exit(1); }
	
	string idx = CS(tEnv, sigIota(n));
	Type te = getSigType(e, tEnv);

	string vperm = getFreshID("dline");
	string vtemp = getFreshID("T");
	
	string ct = cType(te);
	string cz = cZero(te);
	
	fClass->addDeclCode(subst("$0 \t$1[$2];", ct, vperm, T(size) ));
	fClass->addInitCode(subst("for(int i=0; i<$0; i++) $1[i]=$2;", T(size), vperm, cz));
	
	fClass->addExecCode(subst("$0 $1 = $2[$3];", ct, vtemp, vperm, idx));		
	fClass->addExecCode(subst("$0[$1] = $2;", vperm, idx, CS(tEnv, e)));
	return vtemp;		
} 


/*****************************************************************************
							   PREFIX, DELAY A PREFIX VALUE
*****************************************************************************/

string ScalarCompiler::generatePrefix (Tree tEnv, Tree sig, Tree x, Tree e)
{
	Type te = getSigType(sig, tEnv);

	string vperm = getFreshID("M");
	string vtemp = getFreshID("T");
	
	string type = cType(te);
	
	fClass->addDeclCode(subst("$0 \t$1;", type, vperm));
	fClass->addInitCode(subst("$0 = $1;", vperm, CS(tEnv, x)));
	
	fClass->addExecCode(subst("$0 $1 = $2;", type, vtemp, vperm));		
	fClass->addExecCode(subst("$0 = $1;", vperm, CS(tEnv, e)));
	return vtemp;		
} 


/*****************************************************************************
							   IOTA(n)
*****************************************************************************/

string ScalarCompiler::generateIota (Tree tEnv, Tree sig, Tree n)
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

string ScalarCompiler::generateSelect2 (Tree tEnv, Tree sig, Tree sel, Tree s1, Tree s2)
{
	Type t   = getSigType(sig, tEnv);
	//Type u1  = getSigType(s1, tEnv);
	//Type u2  = getSigType(s2, tEnv);
	
	string type = cType(t);
	string var  = getFreshID("S");
	
	//cerr << "compile a select2 of type = " << t << endl;
	switch (t->variability()) 
	{
		case kKonst : 
			fClass->addDeclCode(subst("$0 \t$1[2];", type, var));
			fClass->addInitCode(subst("$0[0] = $1;", var, CS(tEnv, s1)));
			fClass->addInitCode(subst("$0[1] = $1;", var, CS(tEnv, s2)));
			return generateCacheCode(tEnv, sig, subst("$0[$1]", var, CS(tEnv, sel)));
			
		case kBlock :
			fClass->addSlowCode(subst("$0 \t$1[2];", type, var));
			fClass->addSlowCode(subst("$0[0] = $1;", var, CS(tEnv, s1)));
			fClass->addSlowCode(subst("$0[1] = $1;", var, CS(tEnv, s2)));
			return generateCacheCode(tEnv, sig, subst("$0[$1]", var, CS(tEnv, sel)));
			
		case kSamp :
			fClass->addExecCode(subst("$0 \t$1[2];", type, var));
			fClass->addExecCode(subst("$0[0] = $1;", var, CS(tEnv, s1)));
			fClass->addExecCode(subst("$0[1] = $1;", var, CS(tEnv, s2)));
			return generateCacheCode(tEnv, sig, subst("$0[$1]", var, CS(tEnv, sel)));
	}
	return "ScalarCompiler::generateSelect2";
}

string ScalarCompiler::generateSelect3 	(Tree tEnv, Tree sig, Tree sel, Tree s1, Tree s2, Tree s3)
{
	Type t  = getSigType(sig, tEnv);
	
	string type = cType(t);
	string var  = getFreshID("S");
	
//	cerr << "compile a select3 of type = " << t << endl;
	fClass->addExecCode(subst("$0 \t$1[3];", type, var));
	fClass->addExecCode(subst("$0[0] = $1;", var, CS(tEnv, s1)));
	fClass->addExecCode(subst("$0[1] = $2;", var, CS(tEnv, s2)));
	fClass->addExecCode(subst("$0[2] = $3;", var, CS(tEnv, s3)));
	return subst("$0[$1]", var, CS(tEnv, sel));
}

/**
 * retrieve the type annotation of sig
 * @param sig the signal we want to know the type
 */
 
/*
void auditSigType(Tree sig)
{
	Tree tt;
	if (!getProperty(sig, NULLENV, tt)) {
		cerr << "AUDIT SIG TYPE : No type info for : " << *sig << endl;
	} else {
		AudioType* type = (AudioType*)tree2ptr(tt);
		cerr << "AUDIT SIG TYPE : Signal " << *sig << " has type " << *type << endl;
	}
}		
*/

string ScalarCompiler::generateXtended 	(Tree tEnv, Tree sig)
{
	xtended* 		p = (xtended*) getUserData(sig);
	vector<string> 	args;
	vector<Type> 	types;
	
	for (int i=0; i<sig->arity(); i++) {
		args.push_back(CS(tEnv, sig->branch(i)));
		types.push_back(getSigType(sig->branch(i), tEnv));
		//auditSigType(sig->branch(i));
		//types.push_back(TINPUT);
	}
	
	if (p->needCache()) {
		return generateCacheCode(tEnv, sig, p->generateCode(fClass, args, types)); 
	} else {
		return p->generateCode(fClass, args, types);
	}
		
}

