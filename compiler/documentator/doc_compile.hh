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

#ifndef _DOC_COMPILE_SCAL_
#define _DOC_COMPILE_SCAL_

#include <string>
#include <list>
#include <map>

#include "sigtyperules.hh"
#include "occurences.hh"
#include "property.hh"
#include "signals.hh"
#include "lateq.hh"
#include "Text.hh"
#include "doc_Text.hh"
#include "description.hh"
#include "garbageable.hh"

///////////////////////////////////////////////////////////////////////
/**
 * Compile a list of FAUST signals into a list of LaTeX formulas.
 */
///////////////////////////////////////////////////////////////////////

class DocCompiler : public virtual Garbageable
{
  protected:
	
    property<string>            fCompileProperty;
    property<string>            fVectorProperty;

	Lateq*			fLateq;
	Description*	fDescription;

	Tree                      	fSharingKey;
    OccMarkup					fOccMarkup;
	int							fPriority;	///< math priority context

  public:

	DocCompiler (int numInputs, int numOutputs) 
	:fLateq(new Lateq(numInputs, numOutputs)),
        fDescription(0), 
        fPriority(0)
	{}
	
	DocCompiler ( Lateq* k, int priority) 
	:fLateq(k), fDescription(0), fPriority(priority)
	{}
	
	virtual ~DocCompiler()
	{}
	
	Lateq*			compileLateq (Tree L, Lateq* compiledEqn);
	Tree			annotate(Tree L0);	
	
	Lateq*			getLateq()							{ return (Lateq*)fLateq; }
	void			setDescription(Description* descr)	{ fDescription = descr; }
	Description*	getDescription()					{ return fDescription; }
	
	
  protected:

    string      CS (Tree sig, int priority);
    string      generateCode (Tree sig, int priority);
    string      generateCacheCode(Tree sig, const string& exp) ;
    string      generateVariableStore(Tree sig, const string& exp);

	string 		getFreshID (const string& prefix);
	
	bool 		getCompiledExpression(Tree sig, string& name);
	string		setCompiledExpression(Tree sig, const string& name);
		
	void 		setVectorNameProperty(Tree sig, const string& vecname);
	bool 		getVectorNameProperty(Tree sig, string& vecname);

	int 		getSharingCount(Tree t);
	void 		setSharingCount(Tree t, int count);
	void 		sharingAnalysis(Tree t);
	void 		sharingAnnotation(int vctxt, Tree t);
	
	bool		isShortEnough(string& s, unsigned int max);

	
	/* Code generation. */
	
	string 		generateXtended		(Tree sig, int priority);
	string 		generateFixDelay	(Tree sig, Tree arg, Tree size, int priority);
	string 		generatePrefix 		(Tree sig, Tree x, Tree e, int priority);
	string 		generateIota		(Tree sig, Tree arg);
	string 		generateBinOp 		(Tree sig, int opcode, Tree arg1, Tree arg2, int priority);
	
	string 		generateFFun  		(Tree sig, Tree ff, Tree largs, int priority);
	
	string 		generateInput 		(Tree sig, const string& idx);
	string 		generateOutput		(Tree sig, const string& idx, const string& arg1);

//    string      generateDocReadOnlyTbl  (Tree sig, Tree size, Tree content, Tree ridx);
//    string      generateDocReadWriteTbl (Tree sig, Tree size, Tree content, Tree widx, Tree wsig, Tree ridx);
    string      generateDocConstantTbl  (Tree sig, Tree size, Tree content);
    string      generateDocWriteTbl     (Tree sig, Tree size, Tree content, Tree widx, Tree wsig);
    string      generateDocAccessTbl    (Tree sig, Tree tbl, Tree ridx);

	string 		generateSelect2 	(Tree sig, Tree sel, Tree s1, Tree s2, int priority);
	string 		generateSelect3 	(Tree sig, Tree sel, Tree s1, Tree s2, Tree s3, int priority);
	
	string 		generateRecProj 	(Tree sig, Tree exp, int i, int priority);
    void        generateRec         (Tree sig, Tree var, Tree le, int priority);
	
	string 		generateIntCast   	(Tree sig, Tree x, int priority);
	string 		generateFloatCast 	(Tree sig, Tree x, int priority);
	
	string 		generateButton 		(Tree sig, Tree label);
	string 		generateCheckbox 	(Tree sig, Tree label);
	string 		generateVSlider 	(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
	string 		generateHSlider	 	(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
	string 		generateNumEntry 	(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
	
	string 		generateVBargraph 	(Tree sig, Tree label, Tree min, Tree max, const string& exp);
	string 		generateHBargraph	(Tree sig, Tree label, Tree min, Tree max, const string& exp);
	string		generateAttach		(Tree sig, Tree x, Tree y, int priority);
    string      generateEnable        (Tree sig, Tree arg1, Tree arg2, int priority);
	string		generateNumber(Tree sig, const string& exp);
    string      generateFConst (Tree sig, const string& file, const string& name);
    string      generateFVar (Tree sig, const string& file, const string& name);
	
	string		generateDelayVec(Tree sig, const string& exp, const string& ctype, const string& vname, int mxd);
	string		generateDelayVecNoTemp(Tree sig, const string& exp, const string& ctype, const string& vname, int mxd);
    void        generateDelayLine(const string& ctype, const string& vname, int mxd, const string& exp);

	void 		getTypedNames(Type t, const string& prefix, string& ctype, string& vname);
	void		printGCCall(Tree sig, const string& calledFunction);

		
	/* Managment of user interface elements. */

	void		getUIDocInfos(Tree path, string& label, string& unit);
	string		getUIDir (Tree pathname);
	string		prepareBinaryUI(const string& name, Tree pathname);
	string		prepareIntervallicUI(const string& name, Tree path, Tree tcur, Tree tmin, Tree tmax);
};

#endif
