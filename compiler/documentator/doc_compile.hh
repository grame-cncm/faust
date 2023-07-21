/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifndef _DOC_COMPILE_SCAL_
#define _DOC_COMPILE_SCAL_

#include <list>
#include <map>
#include <string>

#include "Text.hh"
#include "description.hh"
#include "doc_Text.hh"
#include "garbageable.hh"
#include "lateq.hh"
#include "occurrences.hh"
#include "property.hh"
#include "signals.hh"
#include "sigtyperules.hh"

///////////////////////////////////////////////////////////////////////
/**
 * Compile a list of FAUST signals into a list of LaTeX formulas.
 */
///////////////////////////////////////////////////////////////////////

class DocCompiler : public virtual Garbageable {
   protected:
    property<std::string> fCompileProperty;
    property<std::string> fVectorProperty;

    Lateq*       fLateq;
    Description* fDescription;

    Tree      fSharingKey;
    OccMarkup fOccMarkup;
    int       fPriority;  ///< math priority context

   public:
    DocCompiler(int numInputs, int numOutputs) : fLateq(new Lateq(numInputs, numOutputs)), fDescription(0), fPriority(0)
    {
    }

    DocCompiler(Lateq* k, int priority) : fLateq(k), fDescription(0), fPriority(priority) {}

    virtual ~DocCompiler() {}

    Lateq* compileLateq(Tree L, Lateq* compiledEqn);
    Tree   annotate(Tree L0);

    Lateq*       getLateq() { return (Lateq*)fLateq; }
    void         setDescription(Description* descr) { fDescription = descr; }
    Description* getDescription() { return fDescription; }

   protected:
    std::string CS(Tree sig, int priority);
    std::string generateCode(Tree sig, int priority);
    std::string generateCacheCode(Tree sig, const std::string& exp);
    std::string generateVariableStore(Tree sig, const std::string& exp);

    std::string getFreshID(const std::string& prefix);

    bool   getCompiledExpression(Tree sig, std::string& name);
    std::string setCompiledExpression(Tree sig, const std::string& name);

    void setVectorNameProperty(Tree sig, const std::string& vecname);
    bool getVectorNameProperty(Tree sig, std::string& vecname);

    int  getSharingCount(Tree t);
    void setSharingCount(Tree t, int count);
    void sharingAnalysis(Tree t);
    void sharingAnnotation(int vctxt, Tree t);

    bool isShortEnough(std::string& s, unsigned int max);

    /* Code generation. */

    std::string generateXtended(Tree sig, int priority);
    std::string generateDelayAccess(Tree sig, Tree arg, Tree size, int priority);
    std::string generatePrefix(Tree sig, Tree x, Tree e, int priority);
    std::string generateBinOp(Tree sig, int opcode, Tree arg1, Tree arg2, int priority);

    std::string generateFFun(Tree sig, Tree ff, Tree largs, int priority);

    std::string generateInput(Tree sig, const std::string& idx);
    std::string generateOutput(Tree sig, const std::string& idx, const std::string& arg1);

    std::string generateDocConstantTbl(Tree sig, Tree size, Tree content);
    std::string generateDocWriteTbl(Tree sig, Tree size, Tree content, Tree widx, Tree wsig);
    std::string generateDocAccessTbl(Tree sig, Tree tbl, Tree ridx);

    std::string generateSelect2(Tree sig, Tree sel, Tree s1, Tree s2, int priority);
   
    std::string generateRecProj(Tree sig, Tree exp, int i, int priority);
    void   generateRec(Tree sig, Tree var, Tree le, int priority);

    std::string generateIntCast(Tree sig, Tree x, int priority);
    std::string generateFloatCast(Tree sig, Tree x, int priority);

    std::string generateButton(Tree sig, Tree label);
    std::string generateCheckbox(Tree sig, Tree label);
    std::string generateVSlider(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
    std::string generateHSlider(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
    std::string generateNumEntry(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);

    std::string generateVBargraph(Tree sig, Tree label, Tree min, Tree max, const std::string& exp);
    std::string generateHBargraph(Tree sig, Tree label, Tree min, Tree max, const std::string& exp);
    std::string generateAttach(Tree sig, Tree x, Tree y, int priority);
    std::string generateControl(Tree sig, Tree arg1, Tree arg2, int priority);
    std::string generateNumber(Tree sig, const std::string& exp);
    std::string generateFConst(Tree sig, const std::string& file, const std::string& name);
    std::string generateFVar(Tree sig, const std::string& file, const std::string& name);

    std::string generateDelayVec(Tree sig, const std::string& exp, const std::string& ctype, const std::string& vname, int mxd);
    std::string generateDelayVecNoTemp(Tree sig, const std::string& exp, const std::string& ctype, const std::string& vname, int mxd);
    void   generateDelayLine(const std::string& ctype, const std::string& vname, int mxd, const std::string& exp);

    void getTypedNames(Type t, const std::string& prefix, std::string& ctype, std::string& vname);
    void printGCCall(Tree sig, const std::string& calledFunction);

    /* Managment of user interface elements. */

    void   getUIDocInfos(Tree path, std::string& label, std::string& unit);
    std::string getUIDir(Tree pathname);
    std::string prepareBinaryUI(const std::string& name, Tree pathname);
    std::string prepareIntervallicUI(const std::string& name, Tree path, Tree tcur, Tree tmin, Tree tmax);
};

#endif
