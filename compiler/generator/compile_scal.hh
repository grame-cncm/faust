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
#include "sigtyperules.hh"
#include "occurences.hh"

////////////////////////////////////////////////////////////////////////
/**
 * Compile a list of FAUST signals into a scalar C++ class
 */
///////////////////////////////////////////////////////////////////////

class ScalarCompiler : public Compiler
{
  private:
	Tree						fCompileKey;
	static map<string, int>		fIDCounters;
	Tree                      	fSharingKey;
	OccMarkup					fOccMarkup;
	bool						fHasIota;


  public:

	ScalarCompiler ( const string& name, const string& super, int numInputs, int numOutputs) :
		Compiler(name,super,numInputs,numOutputs,false),fCompileKey(nil),fSharingKey(nil), fHasIota(false)
	{}
	
	ScalarCompiler ( Klass* k) : Compiler(k),fCompileKey(nil),fSharingKey(nil)
	{}
	
	virtual void 		compileMultiSignal  (Tree lsig);
	virtual void		compileSingleSignal (Tree lsig);
	virtual string		CS (Tree sig);
	virtual string 	generateCacheCode(Tree sig, const string& exp) ;


  private:

	string 		getFreshID (const string& prefix);
	Tree 		makeCompileKey(Tree t);
	void 		compilePreparedSignalList (Tree lsig);
	Tree      	prepare(Tree L0);
	Tree 		prepare2 (Tree L0);
	
	
	bool 		getCompiledExpression(Tree sig, string& name);
	string		setCompiledExpression(Tree sig, const string& name);
	
	int 		getSharingCount(Tree t);
	void 		setSharingCount(Tree t, int count);
	void 		sharingAnalysis(Tree t);
	void 		sharingAnnotation(int vctxt, Tree t);
	
	
	// generation du code
	string		generateCode (Tree sig);
	
	string 		generateXtended		(Tree sig);
	string 		generateFixDelay	(Tree sig, Tree arg, Tree size);
	string 		generatePrefix 		(Tree sig, Tree x, Tree e);
	string 		generateIota		(Tree sig, Tree arg);
	string 		generateBinOp 		(Tree sig, int opcode, Tree arg1, Tree arg2);
	
	string 		generateFFun  		(Tree sig, Tree ff, Tree largs);
	
	string 		generateInput 		(Tree sig, const string& idx);
	string 		generateOutput		(Tree sig, const string& idx, const string& arg1);
	
	string 		generateTable 		(Tree sig, Tree tsize, Tree content);
	string 		generateStaticTable	(Tree sig, Tree tsize, Tree content);
	string 		generateWRTbl 		(Tree sig, Tree tbl, Tree idx, Tree data);
	string 		generateRDTbl 		(Tree sig, Tree tbl, Tree idx);
	string 		generateSigGen		(Tree sig, Tree content);
	string		generateStaticSigGen(Tree sig, Tree content);
	
	string 		generateSelect2 	(Tree sig, Tree sel, Tree s1, Tree s2);
	string 		generateSelect3 	(Tree sig, Tree sel, Tree s1, Tree s2, Tree s3);
	
	string 		generateRecProj 	(Tree sig, Tree exp, int i);
	
	string 		generateIntCast   	(Tree sig, Tree x);
	string 		generateFloatCast 	(Tree sig, Tree x);
	
	string 		generateButton 		(Tree sig, Tree label);
	string 		generateCheckbox 	(Tree sig, Tree label);
	string 		generateVSlider 	(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
	string 		generateHSlider	 	(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
	string 		generateNumEntry 	(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
	
	string 		generateVBargraph 	(Tree sig, Tree label, Tree min, Tree max, const string& exp);
	string 		generateHBargraph	(Tree sig, Tree label, Tree min, Tree max, const string& exp);

	string		generateNumber(Tree sig, const string& exp);
	
	string		generateDelayVec(Tree sig, const string& exp, const string& ctype, const string& vname, int mxd);
	string		generateDelayVecNoTemp(Tree sig, const string& exp, const string& ctype, const string& vname, int mxd);
	string		generateDelayVecWithTemp(Tree sig, const string& exp, const string& ctype, const string& vname, int mxd);
	void 		getTypedNames(Type t, const string& prefix, string& ctype, string& vname);
	void 		ensureIotaCode();


};

#endif
