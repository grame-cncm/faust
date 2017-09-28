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

#define _DNF_ 1

#include <utility>
#include <map>

#include "compile.hh"
#include "sigtyperules.hh"
#include "sigtyperules.hh"
#include "old_occurences.hh"
#include "property.hh"
#include "dcond.hh"

////////////////////////////////////////////////////////////////////////
/**
 * Compile a list of FAUST signals into a scalar C++ class
 */
///////////////////////////////////////////////////////////////////////

class ScalarCompiler : public Compiler
{
  protected:
    
    property<string> fCompileProperty;
    property<string> fSoundfileVariableProperty;            // variable associated to a soundfile
    property<string> fVectorProperty;
    property<pair<string,string> > fStaticInitProperty;     // property added to solve 20101208 kjetil bug
    property<pair<string,string> > fInstanceInitProperty;   // property added to solve 20101208 kjetil bug

    map<Tree, Tree> fConditionProperty;    // used with the new X,Y:enable --> sigEnable(X*Y,Y>0) primitive

    static map<string, int> fIDCounters;
    Tree fSharingKey;
    old_OccMarkup* fOccMarkup;
    bool fHasIota;

  public:

	ScalarCompiler(const string& name, const string& super, int numInputs, int numOutputs) :
		Compiler(name,super,numInputs,numOutputs,false),
        fOccMarkup(0),
        fHasIota(false)
	{}
	
	ScalarCompiler(Klass* k) :
		Compiler(k),
        fOccMarkup(0),
        fHasIota(false)
	{}
	
	virtual void compileMultiSignal  (Tree lsig);
	virtual void compileSingleSignal (Tree lsig);

  protected:

    virtual string CS (Tree sig);
    virtual string generateCode (Tree sig);
    virtual string generateCacheCode(Tree sig, const string& exp) ;
    virtual string forceCacheCode(Tree sig, const string& exp) ;
    virtual string generateVariableStore(Tree sig, const string& exp);

	string getFreshID (const string& prefix);

	void compilePreparedSignalList (Tree lsig);
	Tree prepare(Tree L0);
	Tree prepare2 (Tree L0);
	
	bool getCompiledExpression(Tree sig, string& name);
	string setCompiledExpression(Tree sig, const string& name);

	void setVectorNameProperty(Tree sig, const string& vecname);
	bool getVectorNameProperty(Tree sig, string& vecname);

	int getSharingCount(Tree t);
	void setSharingCount(Tree t, int count);
	void sharingAnalysis(Tree t);
	void sharingAnnotation(int vctxt, Tree t);

    void conditionAnnotation(Tree l);
    void conditionAnnotation(Tree t, Tree nc);
    void conditionStatistics(Tree l);
    string getConditionCode(Tree t);

    // signal drawing
    /*
    SL : 28/09/17 : deactivated for now
    void sigToGraph (Tree sig, ofstream& fout);
    void recdraw(Tree sig, set<Tree>& drawn, ofstream& fout);
    */

	// generation du code
	
    string generateXtended (Tree sig);
    virtual string generateFixDelay(Tree sig, Tree arg, Tree size);
    string generatePrefix(Tree sig, Tree x, Tree e);
    string generateIota(Tree sig, Tree arg);
    string generateBinOp(Tree sig, int opcode, Tree arg1, Tree arg2);
	
    string generateFFun(Tree sig, Tree ff, Tree largs);
    virtual string generateWaveform(Tree sig);

    string generateInput(Tree sig, const string& idx);
    string generateOutput(Tree sig, const string& idx, const string& arg1);
	
    string generateTable(Tree sig, Tree tsize, Tree content);
    string generateStaticTable(Tree sig, Tree tsize, Tree content);
    string generateWRTbl(Tree sig, Tree tbl, Tree idx, Tree data);
    string generateRDTbl(Tree sig, Tree tbl, Tree idx);
    string generateSigGen(Tree sig, Tree content);
    string generateStaticSigGen(Tree sig, Tree content);
	
    string generateSelect2(Tree sig, Tree sel, Tree s1, Tree s2);
    string generateSelect3(Tree sig, Tree sel, Tree s1, Tree s2, Tree s3);
	
    string generateRecProj(Tree sig, Tree exp, int i);
    void   generateRec(Tree sig, Tree var, Tree le);
	
    string generateIntCast(Tree sig, Tree x);
    string generateFloatCast(Tree sig, Tree x);
	
    string generateButton(Tree sig, Tree label);
    string generateCheckbox(Tree sig, Tree label);
    string generateVSlider(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
    string generateHSlider(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
    string generateNumEntry(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
	
    string generateVBargraph(Tree sig, Tree label, Tree min, Tree max, const string& exp);
    string generateHBargraph(Tree sig, Tree label, Tree min, Tree max, const string& exp);
    string generateSoundfile(Tree sig, Tree path);

    string generateNumber(Tree sig, const string& exp);
    string generateFConst(Tree sig, const string& file, const string& name);
    string generateFVar(Tree sig, const string& file, const string& name);
	
    virtual string generateDelayVec(Tree sig, const string& exp, const string& ctype, const string& vname, int mxd);
    string generateDelayVecNoTemp(Tree sig, const string& exp, const string& ctype, const string& vname, int mxd);
	//string generateDelayVecWithTemp(Tree sig, const string& exp, const string& ctype, const string& vname, int mxd);
    virtual void generateDelayLine(const string& ctype, const string& vname, int mxd, const string& exp, const string &ccs);

    void getTypedNames(::Type t, const string& prefix, string& ctype, string& vname);
    void ensureIotaCode();
    int pow2limit(int x);

    void declareWaveform(Tree sig, string& vname, int& size);

    virtual string generateEnable (Tree sig, Tree x, Tree y);

    string cnf2code(Tree cc);
    string or2code(Tree oc);

    string dnf2code(Tree cc);
    string and2code(Tree oc);

};

#endif
