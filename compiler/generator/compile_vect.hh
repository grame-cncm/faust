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
 
 
 
#ifndef _COMPILE_VEC_
#define _COMPILE_VEC_

#include "compile.hh"

////////////////////////////////////////////////////////////////////////
/**
 * Compile a list of FAUST signals into a vector C++ class
 */
///////////////////////////////////////////////////////////////////////

class VectorCompiler : public Compiler
{
private:
  Tree                          fCompileScalKey[4];
  Tree                          fCompileScalarVecKey[4];
  Tree                          fCompileVecKey;

  Tree				fSharingKeyScal;
  Tree				fSharingKeyVec;
  Tree				fSharingKeyTrueScal;
  //Tree fSharingKey;


  Tree                          fIDKey;
  Tree                          fRDTblGenerate;
  /*static*/ map<string, int>	        fIDCounters;

  map<string, int>              rec_var_map;

  int                           loop_unroll;
  //bool                          MMX;

public:
  VectorCompiler ( const string& name, const string& super, int numInputs, int numOutputs) : Compiler(name,super,numInputs,numOutputs,true),
											   loop_unroll(0)//,MMX(false)
  {
    fCompileScalKey[0] = fCompileScalKey[1] = fCompileScalKey[2] = fCompileScalKey[3] = nil;
    fCompileScalarVecKey[0] = fCompileScalarVecKey[1] = fCompileScalarVecKey[2] = fCompileScalarVecKey[3] = nil;
    fCompileVecKey = nil;

    fSharingKeyScal = nil;
    fSharingKeyVec = nil;
    fSharingKeyTrueScal = nil;
    //fSharingKey = nil;

    fIDKey = nil;
    fRDTblGenerate = nil;

  }
  VectorCompiler ( Klass* k) : Compiler(k),loop_unroll(0)//,MMX(false)
  {
    fCompileScalKey[0] = fCompileScalKey[1] = fCompileScalKey[2] = fCompileScalKey[3] = nil;
    fCompileScalarVecKey[0] = fCompileScalarVecKey[1] = fCompileScalarVecKey[2] = fCompileScalarVecKey[3] = nil;
    fCompileVecKey = nil;

    fSharingKeyScal = nil;
    fSharingKeyVec = nil;
    fSharingKeyTrueScal = nil;
    //fSharingKey = nil;

    fIDKey = nil;
    fRDTblGenerate = nil;
  }

  void 		compileMultiSignal  (Tree lsig);
  void		compileSingleSignal (Tree lsig);

private:
  string 	getFreshID (const char* prefix);
  Tree 		makeCompileKey(Tree t, int unroll);
  void 		compilePreparedSignalList (Tree lsig);
  Tree          prepare(Tree L0);
  //Tree 		prepare2 (Tree L0);


  int 		getSharingCount(Tree t, int ctxt);
  void 		sharingAnalysis(Tree t);
  void 		sharingAnnotation(int vctxt, Tree t, int ctxt);



  string	CS (Tree tEnv, Tree sig, int context);

  bool          DynamicCasting(Tree env, int nature_sig, int nature_arg1, int nature_arg2, Tree arg1, Tree arg2, string* cast_arg1, string* cast_arg2);
  bool          TrinaryOperationAccVec(Tree env, Tree arg1,Tree arg2,string* result);
  bool          TrinaryOperationAccScal(Tree env, Tree arg1,Tree arg2,string* result);
  




  //string		generateCode (Tree tEnv,Tree sig, int context) ;

  //string              generateVec(Tree tEnv,string Scal0, string Scal1, string Scal2, string Scal3);
  //string              generateScalarVec(Tree tEnv,string Vec);
  //string              generateScal(Tree tEnv,string exp);
  string                generateVec(Tree tEnv,Tree sig);
  string                generateScalarVec(Tree tEnv,Tree sig);
  string                generateScal(Tree tEnv,Tree sig);

  string 		generateCacheCode(Tree tEnv,Tree sig, const string& exp, int context) ;

  string 		generateInput (Tree tEnv,Tree sig, const string& idx, int context) ;
  string 		generateOutput(Tree tEnv,Tree sig, const string& idx, Tree arg, int context) ;

  string 		generateBinOp (Tree tEnv,Tree sig, int opcode, Tree arg1, Tree arg2, int context) ;

  string 		generateDelay1(Tree tEnv,Tree sig, Tree arg, int context) ;

  string                generateSelect2(Tree tEnv,Tree sig, Tree selector, Tree s1, Tree s2, int context);
  //string                generateSelect3(Tree tEnv,Tree sig, Tree selector, Tree s1, Tree s2, Tree s3, int context);

  string 		generateFFun  (Tree tEnv,Tree sig, Tree ff, Tree largs) ;


  string 		generateRecProj (Tree tEnv,Tree sig, const string& vname, int i) ;
  string 		generateRecRef (Tree tEnv,Tree sig, Tree label) ;
  string 		generateRecGroup (Tree tEnv,Tree sig, Tree label, Tree le) ;

  bool                  heuristiqueRec (Tree tEnv,Tree sig, string* result) ;

  string 		generateTable (Tree tEnv,Tree sig, Tree tsize, Tree content) ;
  string 		generateSigGen(Tree tEnv,Tree sig, Tree content) ;
  //string                generateRDOnlyTbl(Tree tEnv,Tree sig, Tree tbl, Tree idx) ;
  string 		generateWRTbl (Tree tEnv,Tree sig, Tree tbl, Tree idx, Tree data) ;
  string 		generateRDTbl (Tree tEnv,Tree sig, Tree tbl, Tree idx) ;

  

  string 		generateIntCast   	(Tree tEnv,Tree sig, Tree x, int context) ;
  string 		generateFloatCast 	(Tree tEnv,Tree sig, Tree x, int context) ;

  string 		generateButton 		(Tree tEnv,Tree sig, Tree label) ;
  string 		generateCheckbox 	(Tree tEnv,Tree sig, Tree label) ;
  string 		generateVSlider 	(Tree tEnv,Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step) ;
  string 		generateHSlider	 	(Tree tEnv,Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step) ;
  string 		generateNumEntry 	(Tree tEnv,Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step) ;
};


#endif
