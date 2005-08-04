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
 
 
 
#ifndef _COMPILE_
#define _COMPILE_


#include "signals.hh"
#include "klass.hh"
#include "Text.hh"
#include "uitree.hh"
#include <string>
#include <list>
#include <stack>
#include <map>

////////////////////////////////////////////////////////////////////////
/**
 * compileSignals : listOfSignal -> klass
 *
 * Compile a list of FAUST signals into a C++ class 
 */
///////////////////////////////////////////////////////////////////////

#define kMaxHeight 1024

class Compiler
{
protected:
	Klass*			fClass;
  //Tree				fSharingKey;
  //Tree				fCompileKey;
  //static map<string, int>	fIDCounters;
	Tree				fUIRoot;

public:
	Compiler (const string& name, const string& super, int numInputs, int numOutputs, bool vec);
	Compiler (Klass* k);
	
        virtual ~Compiler();

	virtual void		compileMultiSignal  (Tree lsig) = 0;
	virtual void		compileSingleSignal (Tree lsig) = 0;
  	virtual string		CS (Tree tEnv, Tree sig, int ctx = 0) = 0;
	virtual string 		generateCacheCode(Tree tEnv, Tree sig, const string& exp, int context=0)=0;
	
	Klass*				getClass() { return (Klass*)fClass; }	
		
protected:
  //string 		getFreshID (const char* prefix);
  //Tree 		makeCompileKey(Tree t); 
  virtual Tree 		prepare (Tree L0);
  virtual Tree 		prepare2 (Tree L0);
  //void 		compilePreparedSignalList (Tree lsig);
	
 // analyse du partage des expressions
  //virtual int 		getSharingCount(Tree t) = 0;
  //virtual void 		sharingAnalysis(Tree t) = 0;
  //virtual void 		sharingAnnotation(int vctxt, Tree t) = 0;
  

 // generation du code 
  //string		generateCode (Tree tEnv, Tree sig);
	
  //string 		generateCacheCode	(Tree tEnv, Tree sig, const string& exp);
	
  //string 		generateDelay1		(Tree tEnv, Tree sig, Tree arg);
  //string 		generateBinOp 		(Tree tEnv, Tree sig, int opcode, Tree arg1, Tree arg2);
	
  //string 		generateFFun  		(Tree tEnv, Tree sig, Tree ff, Tree largs);
	
  //string 		generateInput 		(Tree tEnv, Tree sig, const string& idx);
  //string 		generateOutput		(Tree tEnv, Tree sig, const string& idx, const string& arg1);

  //string 		generateTable 		(Tree tEnv, Tree sig, Tree tsize, Tree content);
  //string 		generateWRTbl 		(Tree tEnv, Tree sig, Tree tbl, Tree idx, Tree data);
  //string 		generateRDTbl 		(Tree tEnv, Tree sig, Tree tbl, Tree idx);
  //string 		generateSigGen		(Tree tEnv, Tree sig, Tree content);

  //string 		generateSelect2 	(Tree tEnv, Tree sig, Tree sel, Tree s1, Tree s2);
  //string 		generateSelect3 	(Tree tEnv, Tree sig, Tree sel, Tree s1, Tree s2, Tree s3);
	
  //string 		generateRecProj 	(Tree tEnv, Tree sig, const string& vname, int i);
  //string 		generateRecRef 		(Tree tEnv, Tree sig, Tree var);
  //string 		generateRecGroup 	(Tree tEnv, Tree sig, Tree var, Tree le);
	
  //string 		generateIntCast   	(Tree tEnv, Tree sig, Tree x);
  //string 		generateFloatCast 	(Tree tEnv, Tree sig, Tree x);

  //string 		generateButton 		(Tree tEnv, Tree sig, Tree label);
  //string 		generateCheckbox 	(Tree tEnv, Tree sig, Tree label);
  //string 		generateVSlider 	(Tree tEnv, Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
  //string 		generateHSlider	 	(Tree tEnv, Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
  //string 		generateNumEntry 	(Tree tEnv, Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
	
	
// gestion des includes et librairies
	void 		addIncludeFile (const string& str) 	{ fClass->addIncludeFile(str); 	}
	void 		addLibrary (const string& str) 		{ fClass->addLibrary(str); 		}

// gestion de la description arborescente de l'IU
	void 		addUIWidget(Tree path, Tree widget);
	void 		generateWidgetCode(Tree label, Tree varname, Tree sig);
	void 		generateUserInterfaceTree(Tree t);
	void 		generateUserInterfaceElements(Tree elements);
	Tree 		prepareUserInterfaceTree(Tree t);

};
#define generateEquivRecGroup generateRecGroup


void compileSignals (const string& name, const string& super, int numInputs, int numOutputs, Tree lsig);

#endif
