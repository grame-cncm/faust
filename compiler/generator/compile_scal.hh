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
#include "property.hh"

////////////////////////////////////////////////////////////////////////
/**
 * Compile a list of FAUST signals into a scalar C++ class
 */
///////////////////////////////////////////////////////////////////////

class ScalarCompiler : public Compiler
{
  protected:
    property<string>            fCompileProperty;
    property<string>            fVectorProperty;

	static map<string, int>		fIDCounters;
	Tree                      	fSharingKey;
	OccMarkup					fOccMarkup;
    bool						fHasIota;


  public:

	ScalarCompiler ( const string& name, const string& super, int numInputs, int numOutputs) :
		Compiler(name,super,numInputs,numOutputs,false),
        fHasIota(false)
	{}
	
	ScalarCompiler ( Klass* k) : 
		Compiler(k),
        fHasIota(false)
	{}
	
	virtual void 		compileMultiSignal  (Tree lsig);
	virtual void		compileSingleSignal (Tree lsig);


  protected:

    virtual string      CS (Tree sig);
    virtual string      generateCode (Tree sig);
    virtual string      generateCacheCode(Tree sig, const string& exp) ;

    virtual string      generateVariableStore(Tree sig, const string& exp);

	string 		getFreshID (const string& prefix);

	void 		compilePreparedSignalList (Tree lsig);
	Tree      	prepare(Tree L0);
	Tree 		prepare2 (Tree L0);
	
	
	bool 		getCompiledExpression(Tree sig, string& name);
	string		setCompiledExpression(Tree sig, const string& name);

	void 		setVectorNameProperty(Tree sig, const string& vecname);
	bool 		getVectorNameProperty(Tree sig, string& vecname);

	int 		getSharingCount(Tree t);
	void 		setSharingCount(Tree t, int count);
	void 		sharingAnalysis(Tree t);
	void 		sharingAnnotation(int vctxt, Tree t);
	
	
	// generation du code
	
	virtual string 		generateXtended		(Tree sig);
	virtual string 		generateFixDelay	(Tree sig, Tree arg, Tree size);
	virtual string 		generatePrefix 		(Tree sig, Tree x, Tree e);
	virtual string 		generateIota		(Tree sig, Tree arg);
	virtual string 		generateBinOp 		(Tree sig, int opcode, Tree arg1, Tree arg2);
	
	virtual string 		generateFFun  		(Tree sig, Tree ff, Tree largs);
	
	virtual string 		generateInput 		(Tree sig, const string& idx);
	virtual string 		generateOutput		(Tree sig, const string& idx, const string& arg1);
	
	virtual string 		generateTable 		(Tree sig, Tree tsize, Tree content);
	virtual string 		generateStaticTable	(Tree sig, Tree tsize, Tree content);
	virtual string 		generateWRTbl 		(Tree sig, Tree tbl, Tree idx, Tree data);
	virtual string 		generateRDTbl 		(Tree sig, Tree tbl, Tree idx);
	virtual string 		generateSigGen		(Tree sig, Tree content);
	virtual string		generateStaticSigGen(Tree sig, Tree content);
	
	virtual string 		generateSelect2 	(Tree sig, Tree sel, Tree s1, Tree s2);
	virtual string 		generateSelect3 	(Tree sig, Tree sel, Tree s1, Tree s2, Tree s3);
	
	virtual string 		generateRecProj 	(Tree sig, Tree exp, int i);
    virtual void        generateRec         (Tree sig, Tree var, Tree le);
	
	virtual string 		generateIntCast   	(Tree sig, Tree x);
	virtual string 		generateFloatCast 	(Tree sig, Tree x);
	
	virtual string 		generateButton 		(Tree sig, Tree label);
	virtual string 		generateCheckbox 	(Tree sig, Tree label);
	virtual string 		generateVSlider 	(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
	virtual string 		generateHSlider	 	(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
	virtual string 		generateNumEntry 	(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
	
	virtual string 		generateVBargraph 	(Tree sig, Tree label, Tree min, Tree max, const string& exp);
	virtual string 		generateHBargraph	(Tree sig, Tree label, Tree min, Tree max, const string& exp);

	virtual string		generateNumber(Tree sig, const string& exp);
    virtual string      generateFConst (Tree sig, const string& file, const string& name);
    virtual string      generateFVar (Tree sig, const string& file, const string& name);
	
	virtual string		generateDelayVec(Tree sig, const string& exp, const string& ctype, const string& vname, int mxd);
	virtual string		generateDelayVecNoTemp(Tree sig, const string& exp, const string& ctype, const string& vname, int mxd);
	//string		generateDelayVecWithTemp(Tree sig, const string& exp, const string& ctype, const string& vname, int mxd);
    virtual void        generateDelayLine(const string& ctype, const string& vname, int mxd, const string& exp);

	void 		getTypedNames(Type t, const string& prefix, string& ctype, string& vname);
	void 		ensureIotaCode();
    int         pow2limit(int x);



};

#endif
