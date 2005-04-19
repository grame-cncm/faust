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
 
 
 
#ifndef _COMPILE_SCAL_
#define _COMPILE_SCAL_

#include "compile.hh"
#include "sigtyperules.hh"

////////////////////////////////////////////////////////////////////////
/**
 * Compile a list of FAUST signals into a scalar C++ class
 */
///////////////////////////////////////////////////////////////////////

class ScalarCompiler : public Compiler
{
private:
  Tree						fCompileKey;
  static map<string, int>	fIDCounters;
  Tree                      fSharingKey;


public:

  ScalarCompiler ( const string& name, const string& super, int numInputs, int numOutputs) :
    Compiler(name,super,numInputs,numOutputs,false),fCompileKey(nil),fSharingKey(nil)
  {}

  ScalarCompiler ( Klass* k) : Compiler(k),fCompileKey(nil),fSharingKey(nil)
  {}

  void 		compileMultiSignal  (Tree lsig);
  void		compileSingleSignal (Tree lsig);


private:
  string 	getFreshID (const char* prefix);
  string	CS (Tree tEnv, Tree sig);
  Tree 		makeCompileKey(Tree t);
  void 		compilePreparedSignalList (Tree lsig);
  Tree          prepare(Tree L0);
  Tree 		prepare2 (Tree L0);

  int 		getSharingCount(Tree t);
  void 		sharingAnalysis(Tree t);
  void 		sharingAnnotation(int vctxt, Tree t);
  

  // generation du code 
  string		generateCode (Tree tEnv, Tree sig);
	
  string 		generateCacheCode	(Tree tEnv, Tree sig, const string& exp);
	
  string 		generateDelay1		(Tree tEnv, Tree sig, Tree arg);
  string 		generateFixDelay	(Tree tEnv, Tree sig, Tree arg, Tree size);
  string 		generatePrefix 		(Tree tEnv, Tree sig, Tree x, Tree e);
  string 		generateIota		(Tree tEnv, Tree sig, Tree arg);
  string 		generateBinOp 		(Tree tEnv, Tree sig, int opcode, Tree arg1, Tree arg2);
	
  string 		generateFFun  		(Tree tEnv, Tree sig, Tree ff, Tree largs);

  string 		generateInput 		(Tree tEnv, Tree sig, const string& idx);
  string 		generateOutput		(Tree tEnv, Tree sig, const string& idx, const string& arg1);

  string 		generateTable 		(Tree tEnv, Tree sig, Tree tsize, Tree content);
  string 		generateWRTbl 		(Tree tEnv, Tree sig, Tree tbl, Tree idx, Tree data);
  string 		generateRDTbl 		(Tree tEnv, Tree sig, Tree tbl, Tree idx);
  string 		generateSigGen		(Tree tEnv, Tree sig, Tree content);

  string 		generateSelect2 	(Tree tEnv, Tree sig, Tree sel, Tree s1, Tree s2);
  string 		generateSelect3 	(Tree tEnv, Tree sig, Tree sel, Tree s1, Tree s2, Tree s3);

  string 		generateRecProj 	(Tree tEnv, Tree sig, const string& vname, int i);
  string 		generateRecRef 		(Tree tEnv, Tree sig, Tree var);
  string 		generateRecGroup 	(Tree tEnv, Tree sig, Tree var, Tree le);
	
  string 		generateIntCast   	(Tree tEnv, Tree sig, Tree x);
  string 		generateFloatCast 	(Tree tEnv, Tree sig, Tree x);

  string 		generateButton 		(Tree tEnv, Tree sig, Tree label);
  string 		generateCheckbox 	(Tree tEnv, Tree sig, Tree label);
  string 		generateVSlider 	(Tree tEnv, Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
  string 		generateHSlider	 	(Tree tEnv, Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
  string 		generateNumEntry 	(Tree tEnv, Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
  
  string 		generateVBargraph 	(Tree tEnv, Tree sig, Tree label, Tree min, Tree max, const string& exp);
  string 		generateHBargraph	(Tree tEnv, Tree sig, Tree label, Tree min, Tree max, const string& exp);
};

/*****************************************************************************
							   	utilities
*****************************************************************************/

#if 0
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
#endif

#endif
