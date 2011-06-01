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



#ifndef _KLASS_H
#define _KLASS_H

/**********************************************************************
			- klass.h : class C++ � remplir (projet FAUST) -


		Historique :
		-----------
		17-10-2001 : implementation initiale (yo)
		18-10-2001 : Ajout de getFreshID (yo)
		02-11-2001 : Ajout de sous classes (yo)

***********************************************************************/
using namespace std;

#include <string>
#include <list>
#include <set>
#include <map>
#include "sigtype.hh"
#include "smartpointer.hh"
#include "tlib.hh"
#include "uitree.hh"
#include "property.hh"

#define kMaxCategory 32

#include "loop.hh"
#include "graphSorting.hh"

class Klass //: public Target
{

protected:
    // we make it global because several classes may need
    // power def but we want the code to be generated only once
    static bool     fNeedPowerDef;              ///< true when faustpower definition is needed


 protected:
    
	string			fKlassName;
	string			fSuperKlassName;
	int				fNumInputs;
	int				fNumOutputs;
    int             fNumActives;                ///< number of active controls in the UI (sliders, buttons, etc.)
    int             fNumPassives;               ///< number of passive widgets in the UI (bargraphs, etc.)

    set<string>			fIncludeFileSet;
	set<string>			fLibrarySet;

	list<Klass* >		fSubClassList;

	list<string>		fDeclCode;
	list<string>		fStaticInitCode;		///< static init code for class constant tables
	list<string>		fStaticFields;			///< static fields after class
	list<string>		fInitCode;
	list<string>		fUICode;
	list<string>		fUIMacro;

#if 0
    list<string>        fSlowDecl;
    list<string>        fSharedDecl;            ///< declare shared variables for openMP
    list<string>        fCommonCode;            ///< code executed by all threads
    list<string>        fSlowCode;
    list<string>        fEndCode;
#endif
    list<string>        fSharedDecl;            ///< shared declarations
    list<string>        fFirstPrivateDecl;      ///< first private declarations

    list<string>        fZone1Code;              ///< shared vectors
    list<string>        fZone2Code;              ///< first private
    list<string>        fZone2bCode;             ///< single once per block
    list<string>        fZone2cCode;             ///< single once per block
    list<string>        fZone3Code;             ///< private every sub block
  
    Loop*               fTopLoop;               ///< active loops currently open
    property<Loop*>     fLoopProperty;          ///< loops used to compute some signals

    bool                fVec;

 public:

	Klass (const string& name, const string& super, int numInputs, int numOutputs, bool __vec = false)
	  : 	fKlassName(name), fSuperKlassName(super), fNumInputs(numInputs), fNumOutputs(numOutputs),
            fNumActives(0), fNumPassives(0),
            fTopLoop(new Loop(0, "count")), fVec(__vec)
	{}

	virtual ~Klass() 						{}

    void    openLoop(const string& size);
    void    openLoop(Tree recsymbol, const string& size);
    void    closeLoop(Tree sig);

    void    setLoopProperty(Tree sig, Loop* l);     ///< Store the loop used to compute a signal
    bool    getLoopProperty(Tree sig, Loop*& l);    ///< Returns the loop used to compute a signal
    const string&    getClassName() const { return fKlassName; }    ///< Returns the name of the class

    Loop*   topLoop()   { return fTopLoop; }
    
    void buildTasksList();
    
	void addIncludeFile (const string& str) { fIncludeFileSet.insert(str); }

	void addLibrary (const string& str) 	{ fLibrarySet.insert(str); }

    void rememberNeedPowerDef ()            { fNeedPowerDef = true; }

	void collectIncludeFile(set<string>& S);

	void collectLibrary(set<string>& S);

	void addSubKlass (Klass* son)			{ fSubClassList.push_back(son); }

	void addDeclCode (const string& str) 	{ fDeclCode.push_back(str); }

	void addInitCode (const string& str)	{ fInitCode.push_back(str); }

	void addStaticInitCode (const string& str)	{ fStaticInitCode.push_back(str); }

	void addStaticFields (const string& str)	{ fStaticFields.push_back(str); }

	void addUICode (const string& str)		{ fUICode.push_back(str); }

    void addUIMacro (const string& str)     { fUIMacro.push_back(str); }

    void incUIActiveCount ()                { fNumActives++; }
    void incUIPassiveCount ()               { fNumPassives++; }


    void addSharedDecl (const string& str)          { fSharedDecl.push_back(str); }
    void addFirstPrivateDecl (const string& str)    { fFirstPrivateDecl.push_back(str); }

    void addZone1 (const string& str)  { fZone1Code.push_back(str); }
    void addZone2 (const string& str)  { fZone2Code.push_back(str); }
    void addZone2b (const string& str)  { fZone2bCode.push_back(str); }
    void addZone2c (const string& str)  { fZone2cCode.push_back(str); }
    void addZone3 (const string& str)  { fZone3Code.push_back(str); }
 
    void addPreCode ( const string& str)   { fTopLoop->addPreCode(str); }
    void addExecCode ( const string& str)   { fTopLoop->addExecCode(str); }
	void addPostCode (const string& str)	{ fTopLoop->addPostCode(str); }

	virtual void println(int n, ostream& fout);
    
    virtual void printComputeMethod (int n, ostream& fout);
    virtual void printComputeMethodScalar (int n, ostream& fout);
    virtual void printComputeMethodVectorFaster (int n, ostream& fout);
    virtual void printComputeMethodVectorSimple (int n, ostream& fout);
    virtual void printComputeMethodOpenMP (int n, ostream& fout);
    virtual void printComputeMethodScheduler (int n, ostream& fout);

    virtual void printLoopGraphScalar(int n, ostream& fout);
    virtual void printLoopGraphVector(int n, ostream& fout);
    virtual void printLoopGraphOpenMP(int n, ostream& fout);
    virtual void printLoopGraphScheduler(int n, ostream& fout);
    virtual void printLoopGraphInternal(int n, ostream& fout);
    virtual void printGraphDotFormat(ostream& fout);

    // experimental
	virtual void printLoopDeepFirst(int n, ostream& fout, Loop* l, set<Loop*>& visited);

    virtual void printLastLoopLevelScheduler(int n, int lnum, const lset& L, ostream& fout);
    virtual void printLoopLevelScheduler(int n, int lnum, const lset& L, ostream& fout);
    virtual void printOneLoopScheduler(lset::const_iterator p, int n, ostream& fout);
    virtual void printLoopLevelOpenMP(int n, int lnum, const lset& L, ostream& fout);

    virtual void printMetadata(int n, const map<Tree, set<Tree> >& S, ostream& fout);

	virtual void printIncludeFile(ostream& fout);

  	virtual void printLibrary(ostream& fout);
    virtual void printAdditionalCode(ostream& fout);

	int	inputs() 	{ return fNumInputs; }
	int outputs()	{ return fNumOutputs; }
};

class SigIntGenKlass : public Klass {
    
 public:

	SigIntGenKlass (const string& name) : Klass(name, "", 0, 1, false)	{}

	virtual void println(int n, ostream& fout);
};

class SigFloatGenKlass : public Klass {
    
 public:

	SigFloatGenKlass (const string& name) : Klass(name, "", 0, 1, false)	{}

	virtual void println(int n, ostream& fout);
};


#endif
