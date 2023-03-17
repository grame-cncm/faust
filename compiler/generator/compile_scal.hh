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

#ifndef _COMPILE_SCAL_
#define _COMPILE_SCAL_

#define _DNF_ 1

#include <map>
#include <utility>

#include "compile.hh"
#include "dcond.hh"
#include "occurrences.hh"
#include "property.hh"
#include "sigtyperules.hh"

////////////////////////////////////////////////////////////////////////
/**
 * Compile a list of FAUST signals into a scalar C++ class
 */
///////////////////////////////////////////////////////////////////////

class ScalarCompiler : public Compiler {
   protected:
    property<std::string>                fCompileProperty;
    property<std::string>                fSoundfileVariableProperty;  // variable associated to a soundfile
    property<std::string>                fVectorProperty;
    property<std::pair<std::string, std::string> > fStaticInitProperty;    // property added to solve 20101208 kjetil bug
    property<std::pair<std::string, std::string> > fInstanceInitProperty;  // property added to solve 20101208 kjetil bug

    std::map<Tree, Tree> fConditionProperty;  // used with the new X,Y:enable --> sigControl(X*Y,Y>0) primitive

    static std::map<std::string, int> fIDCounters;
    Tree                    fSharingKey;
    OccMarkup*              fOccMarkup;
    int                     fMaxIota;

   public:
    ScalarCompiler(const std::string& name, const std::string& super, int numInputs, int numOutputs)
        : Compiler(name, super, numInputs, numOutputs, false), fSharingKey(nullptr), fOccMarkup(nullptr), fMaxIota(-1)
    {
    }

    ScalarCompiler(Klass* k) : Compiler(k), fSharingKey(nullptr), fOccMarkup(nullptr), fMaxIota(-1) {}

    virtual void compileMultiSignal(Tree lsig);
    virtual void compileSingleSignal(Tree lsig);

   protected:
    virtual std::string CS(Tree sig);
    virtual std::string generateCode(Tree sig);
    virtual std::string generateCacheCode(Tree sig, const std::string& exp);
    virtual std::string forceCacheCode(Tree sig, const std::string& exp);
    virtual std::string generateVariableStore(Tree sig, const std::string& exp);

    std::string getFreshID(const std::string& prefix);

    void compilePreparedSignalList(Tree lsig);
    Tree prepare(Tree L0);
    Tree prepare2(Tree L0);

    bool   getCompiledExpression(Tree sig, std::string& name);
    std::string setCompiledExpression(Tree sig, const std::string& name);

    void setVectorNameProperty(Tree sig, const std::string& vecname);
    bool getVectorNameProperty(Tree sig, std::string& vecname);
  
    void   conditionAnnotation(Tree l);
    void   conditionAnnotation(Tree t, Tree nc);
    void   conditionStatistics(Tree l);
    std::string getConditionCode(Tree t);

    // code generation
    std::string         generateXtended(Tree sig);
    virtual std::string generateDelay(Tree sig, Tree arg, Tree size);
    std::string         generatePrefix(Tree sig, Tree x, Tree e);
    std::string         generateBinOp(Tree sig, int opcode, Tree arg1, Tree arg2);

    std::string         generateFFun(Tree sig, Tree ff, Tree largs);
    virtual std::string generateWaveform(Tree sig);

    std::string generateInput(Tree sig, const std::string& idx);
    std::string generateOutput(Tree sig, const std::string& idx, const std::string& arg1);

    std::string generateTable(Tree sig, Tree tsize, Tree content);
    std::string generateStaticTable(Tree sig, Tree tsize, Tree content);
    std::string generateWRTbl(Tree sig, Tree size, Tree gen, Tree wi, Tree ws);
    std::string generateRDTbl(Tree sig, Tree tbl, Tree ri);
    std::string generateSigGen(Tree sig, Tree content);
    std::string generateStaticSigGen(Tree sig, Tree content);

    std::string generateSelect2(Tree sig, Tree sel, Tree s1, Tree s2);
  
    std::string generateRecProj(Tree sig, Tree exp, int i);
    void   generateRec(Tree sig, Tree var, Tree le);

    std::string generateIntCast(Tree sig, Tree x);
    std::string generateBitCast(Tree sig, Tree x);
    std::string generateFloatCast(Tree sig, Tree x);

    std::string generateButton(Tree sig, Tree label);
    std::string generateCheckbox(Tree sig, Tree label);
    std::string generateVSlider(Tree sig, Tree label, Tree cur);
    std::string generateHSlider(Tree sig, Tree label, Tree cur);
    std::string generateNumEntry(Tree sig, Tree label, Tree cur);

    std::string generateVBargraph(Tree sig, Tree label, const std::string& exp);
    std::string generateHBargraph(Tree sig, Tree label, const std::string& exp);
    std::string generateSoundfile(Tree sig, Tree path);

    std::string generateNumber(Tree sig, const std::string& exp);
    std::string generateFConst(Tree sig, const std::string& file, const std::string& name);
    std::string generateFVar(Tree sig, const std::string& file, const std::string& name);

    virtual std::string generateDelayVec(Tree sig, const std::string& exp, const std::string& ctype, const std::string& vname, int mxd);
    std::string       generateDelayVecNoTemp(Tree sig, const std::string& exp, const std::string& ctype, const std::string& vname, int mxd);
    virtual void generateDelayLine(const std::string& ctype, const std::string& vname, int mxd, const std::string& exp,
                                   const std::string& ccs);

    void getTypedNames(::Type t, const std::string& prefix, std::string& ctype, std::string& vname);
    void ensureIotaCode();
  
    void declareWaveform(Tree sig, std::string& vname, int& size);

    virtual std::string generateControl(Tree sig, Tree x, Tree y);

    std::string cnf2code(Tree cc);
    std::string or2code(Tree oc);

    std::string dnf2code(Tree cc);
    std::string and2code(Tree oc);
};

#endif
