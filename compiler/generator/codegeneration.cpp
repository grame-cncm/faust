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
******************************************************************************
							FAUST SIGNAL COMPILER 
						Y. Orlarey, (c) Grame 2002
------------------------------------------------------------------------------
Compile a list of FAUST signals into a C++ class .

 History :
 ---------
 	2002-02-08 : First version
	
******************************************************************************
*****************************************************************************/

 

#include <assert.h>
#include "compile.hh"
#include "sigtype.hh"

#include <stdio.h>

#include "sigprint.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"
#include "prim2.hh"



/*****************************************************************************
******************************************************************************

						   CODE GENERATION METHODS
	
******************************************************************************
*****************************************************************************/


/*****************************************************************************
							   	utilities
*****************************************************************************/
/*
static Klass* signal2klass (const string& name, Tree sig) 
{ 
	Type t = getSigType(sig, NULLENV);
	if (t->nature() == kInt) {
		
		Compiler C( new SigIntGenKlass(name) );
		C.compileSingleSignal(sig); 
		return C.getClass();
		
	} else {
		
		Compiler C( new SigFloatGenKlass(name) );
		C.compileSingleSignal(sig); 
		return C.getClass();
		
	}		
}
*/
/*****************************************************************************
							   INPUTS - OUTPUTS
*****************************************************************************/

/*
string Compiler::generateInput (Tree tEnv, Tree sig, const string& idx) 
{ 
	return subst("input$0[i]", idx);
}


string Compiler::generateOutput (Tree tEnv, Tree sig, const string& idx, const string& arg) 
{ 
	string dst = subst("output$0[i]", idx);
	fClass->addExecCode(subst("$0 = $1;", dst, arg));
	return dst;
}
*/

/*****************************************************************************
							   BINARY OPERATION
*****************************************************************************/
/*
string Compiler::generateBinOp(Tree tEnv, Tree sig, int opcode, Tree arg1, Tree arg2)
{
	return generateCacheCode(tEnv, sig, subst("($0 $1 $2)", CS(tEnv, arg1), gBinOpTable[opcode]->fName, CS(tEnv, arg2)));
}
*/

/*****************************************************************************
							   Primitive Operations
*****************************************************************************/
/*
string Compiler::generateFFun(Tree tEnv, Tree sig, Tree ff, Tree largs)
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
*/

/*****************************************************************************
							   CACHE CODE
*****************************************************************************/
/*
string Compiler::generateCacheCode(Tree tEnv, Tree sig, const string& exp)
{
	string 		vname, ctype;
	int 		sharing = shcount(fSharingKey, sig);
	
	
	if (sharing == 1) { 
		
		return exp;
		
	} else if (sharing > 1) {
		Type t = getSigType(sig, tEnv);
//		cerr << "generation du cache code pour : " << exp << " qui est de type " << t << endl;
		
		switch (t->variability()) {
			
			case kKonst :

				if (t->nature() == kInt) {
					vname = getFreshID("idata");
					ctype = "int";
				} else {
					vname = getFreshID("fdata");
					ctype = "float";
				}

				fClass->addDeclCode(subst("$0 \t$1;", ctype, vname)); 
				fClass->addInitCode(subst("$0 = $1;", vname, exp)); 
				break;
			
			case kBlock :
				
				if (t->nature() == kInt) {
					vname = getFreshID("itemp");
					ctype = "int";
				} else {
					vname = getFreshID("ftemp");
					ctype = "float";
				}

				fClass->addSlowCode(subst("$0 $1 = $2;", ctype, vname, exp)); 
				break;
			
			case kSamp :

				if (t->nature() == kInt) {
					vname = getFreshID("itemp");
					ctype = "int";
				} else {
					vname = getFreshID("ftemp");
					ctype = "float";
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
*/
	


/*****************************************************************************
							   	    CASTING
*****************************************************************************/
/*

string Compiler::generateIntCast(Tree tEnv, Tree sig, Tree x)
{
	return generateCacheCode(tEnv, sig, subst("int($0)", CS(tEnv, x)));
}
			
string Compiler::generateFloatCast (Tree tEnv, Tree sig, Tree x)
{
	return generateCacheCode(tEnv, sig, subst("float($0)", CS(tEnv, x)));
}
*/
/*****************************************************************************
							user interface elements
*****************************************************************************/
/*		
string Compiler::generateButton(Tree tEnv, Tree sig, Tree path)
{
	string varname = getFreshID("fbutton");
	fClass->addDeclCode(subst("float \t$0;", varname));
	fClass->addInitCode(subst("$0 = 0.0;", varname));
	addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig)); 
	return generateCacheCode(tEnv, sig, varname);
}
		
string Compiler::generateCheckbox(Tree tEnv, Tree sig, Tree path)
{
	string varname = getFreshID("fcheckbox");
	fClass->addDeclCode(subst("float \t$0;", varname));
	fClass->addInitCode(subst("$0 = 0.0;", varname));
	addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig)); 
	return generateCacheCode(tEnv, sig, varname);
} 


string Compiler::generateVSlider(Tree tEnv, Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
	string varname = getFreshID("fslider");
	fClass->addDeclCode(subst("float \t$0;", varname));
	fClass->addInitCode(subst("$0 = $1;", varname, T(tree2float(cur))));
	addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig)); 
	return generateCacheCode(tEnv, sig, varname);
}

string Compiler::generateHSlider(Tree tEnv, Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
	string varname = getFreshID("fslider");
	fClass->addDeclCode(subst("float \t$0;", varname));
	fClass->addInitCode(subst("$0 = $1;", varname, T(tree2float(cur))));
	addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig)); 
	return generateCacheCode(tEnv, sig, varname);
}

string Compiler::generateNumEntry(Tree tEnv, Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step)
{
	string varname = getFreshID("fentry");
	fClass->addDeclCode(subst("float \t$0;", varname));
	fClass->addInitCode(subst("$0 = $1;", varname, T(tree2float(cur))));
	addUIWidget(reverse(tl(path)), uiWidget(hd(path), tree(varname), sig)); 
	return generateCacheCode(tEnv, sig, varname);
}
		

void Compiler::addUIWidget(Tree path, Tree widget)
{
	fUIRoot = putSubFolder(fUIRoot, path, widget);
}

void Compiler::generateWidgetCode(Tree label, Tree varname, Tree sig)
{
	Tree path, c, x, y, z;
	
	if ( isSigButton(sig, path) ) 					{ 
		fClass->addUICode(subst("interface->addButton($0, &$1);", tree2str(label), tree2str(varname))); 
			
	} else if ( isSigCheckbox(sig, path) ) 			{ 
		fClass->addUICode(subst("interface->addCheckbox($0, &$1);", tree2str(label), tree2str(varname))); 
			
	} else if ( isSigVSlider(sig, path,c,x,y,z) )	{ 
		fClass->addUICode(subst("interface->addVerticalSlider($0, &$1, $2, $3, $4, $5);", 
				tree2str(label), 
				tree2str(varname), 
				T(tree2float(c)), 
				T(tree2float(x)),
				T(tree2float(y)), 
				T(tree2float(z)))); 
		
	} else if ( isSigHSlider(sig, path,c,x,y,z) )	{ 
		fClass->addUICode(subst("interface->addHorizontalSlider($0, &$1, $2, $3, $4, $5);", 
				tree2str(label), 
				tree2str(varname), 
				T(tree2float(c)), 
				T(tree2float(x)),
				T(tree2float(y)), 
				T(tree2float(z)))); 
		
	} else if ( isSigNumEntry(sig, path,c,x,y,z) )	{ 
		fClass->addUICode(subst("interface->addNumEntry($0, &$1, $2, $3, $4, $5);", 
				tree2str(label), 
				tree2str(varname), 
				T(tree2float(c)), 
				T(tree2float(x)),
				T(tree2float(y)), 
				T(tree2float(z)))); 
		
	} else {
		fprintf(stderr, "Error in generating widget code\n");
		exit(1);
	}
}

 
void Compiler::generateUserInterfaceTree(Tree t)
{
	Tree 	label, elements, varname, sig;
	
	if (isUiFolder(t, label, elements)) {
		const int		orient = tree2int(left(label));
		const char * 	str = tree2str(right(label));
		const char * 	model;
		
		switch (orient) {
			case 0 : model = "interface->openVerticalBox($0);"; break;
			case 1 : model = "interface->openHorizontalBox($0);"; break;
			case 2 : model = "interface->openTabBox($0);"; break;
			default : 
					fprintf(stderr, "error in user interface generation 1\n");
				exit(1);
		}
		fClass->addUICode(subst(model, str));
		generateUserInterfaceElements(elements);
		fClass->addUICode("interface->closeBox();");
		
	} else if (isUiWidget(t, label, varname, sig)) {
			
		generateWidgetCode(label, varname, sig);
		
	} else {
		
		fprintf(stderr, "error in user interface generation 2\n");
		exit(1);
		
	}
}
 
void Compiler::generateUserInterfaceElements(Tree elements)
{
	while (!isNil(elements)) {
		generateUserInterfaceTree(right(hd(elements)));
		elements = tl(elements);
	}		
}
*/

/*****************************************************************************
							   	    TABLES
*****************************************************************************/



/*----------------------------------------------------------------------------
						sigGen : initial table content
----------------------------------------------------------------------------*/
/*
string Compiler::generateSigGen(Tree tEnv, Tree sig, Tree content)
{
	string klassname = getFreshID("SIG");
	string signame = getFreshID("sig");
	
	fClass->addSubKlass(signal2klass(klassname, content));
	fClass->addInitCode(subst("$0 $1;", klassname, signame));
	
	return signame; 
}
*/

/*----------------------------------------------------------------------------
						sigTable : table declaration
----------------------------------------------------------------------------*/
/*
string Compiler::generateTable(Tree tEnv, Tree sig, Tree tsize, Tree content) 
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
	fClass->addInitCode(subst("$0.init(samplingRate);", generator));
	// remplissage de la table
	fClass->addInitCode(subst("$0.fill($1,$2);", generator, T(size), vname));
	
	// on retourne le nom de la table
	return vname;
}
*/

/*----------------------------------------------------------------------------
						sigWRTable : table assignement
----------------------------------------------------------------------------*/
/*
string Compiler::generateWRTbl(Tree tEnv, Tree sig, Tree tbl, Tree idx, Tree data)
{ 
	string tblName(CS(tEnv, tbl));
	fClass->addExecCode(subst("$0[$1] = $2;", tblName, CS(tEnv, idx), CS(tEnv, data)));
	return tblName;
}
*/

/*----------------------------------------------------------------------------
						sigRDTable : table access
----------------------------------------------------------------------------*/
/*
string Compiler::generateRDTbl(Tree tEnv, Tree sig, Tree tbl, Tree idx)
{ 
	return subst("$0[$1]", CS(tEnv, tbl), CS(tEnv, idx));
}

*/

/*****************************************************************************
							   RECURSIONS
*****************************************************************************/


/*---------------------------------------------------------------------------
							fonctions auxilliaires
----------------------------------------------------------------------------*/
/*
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
Tree RECNAMEPROP = tree(symbol("sigRecNameProp"));

*/
/*--------------------------------------------------------------------------
							   Fonctions de génération
----------------------------------------------------------------------------*/

// Groupe de signaux mutuellement recursifs

/*
string Compiler::generateRecGroup(Tree tEnv, Tree sig, Tree var, Tree le) 
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
string Compiler::generateRecProj(Tree tEnv, Tree sig, const string& ID, int i) 
{ 
	return makeRecVarPermName(ID, i); 
}


//--------------a supprimer
// Variable : référence au ième signal d'un groupe recursif englobant
string Compiler::generateRecRef(Tree tEnv, Tree sig, Tree var) 
{ 
	Tree code;
	if (!getProperty(var, fCompileKey, code)) {
		fprintf(stderr, "ERROR in generateRecRef\n");
		exit(1);
	}
	return name(code->node().getSym());
}

*/
/*****************************************************************************
							   1-SAMPLE DELAY
*****************************************************************************/
/*
string Compiler::generateDelay1 (Tree tEnv, Tree sig, Tree e)
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



// a revoir en utilisant la lecture de table et en partageant la construction de la paire de valeurs
// il faudrait egalement tenir compte de la computability et de la variability

string Compiler::generateSelect2 (Tree tEnv, Tree sig, Tree sel, Tree s1, Tree s2)
{
	Type t  = getSigType(sig, tEnv);
	
	string type = cType(t);
	string var  = getFreshID("S");
	
	fClass->addExecCode(subst("$0 \t$1[2];", type, var));
	fClass->addExecCode(subst("$0[0] = $1;", var, CS(tEnv, s1)));
	fClass->addExecCode(subst("$0[1] = $1;", var, CS(tEnv, s2)));
	return subst("$0[$1]", var, CS(tEnv, sel));
}

string Compiler::generateSelect3 	(Tree tEnv, Tree sig, Tree sel, Tree s1, Tree s2, Tree s3)
{
	Type t  = getSigType(sig, tEnv);
	
	string type = cType(t);
	string var  = getFreshID("S");
	
	fClass->addExecCode(subst("$0 \t$1[3];", type, var));
	fClass->addExecCode(subst("$0[0] = $1;", var, CS(tEnv, s1)));
	fClass->addExecCode(subst("$0[1] = $2;", var, CS(tEnv, s2)));
	fClass->addExecCode(subst("$0[2] = $3;", var, CS(tEnv, s3)));
	return subst("$0[$1]", var, CS(tEnv, sel));
}
*/
