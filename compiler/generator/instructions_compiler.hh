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

#ifndef _INSTRUCTION_COMPILER_H
#define _INSTRUCTION_COMPILER_H

#include <string>
#include <list>
#include <set>
#include <map>
#include <vector>

#include "global.hh"
#include "instructions.hh"
#include "code_container.hh"
#include "occurences.hh"
#include "property.hh"
#include "Text.hh"
#include "garbageable.hh"

using namespace std;

typedef ValueInst* InstType;

class InstructionsCompiler : public virtual Garbageable {

    protected:

        CodeContainer* fContainer;

        property<ValueInst*> fCompileProperty;
        property<string> fVectorProperty;
        property<pair<string, string> > fStaticInitProperty;
        property<pair<string, string> > fInstanceInitProperty;
        property<string> fTableProperty;
        Tree fSharingKey;
        OccMarkup fOccMarkup;
    
        std::map<int, std::string> fIOTATable; // Ensure IOTA base fixed delays are computed once
    
        Tree fUIRoot;
        Description* fDescription;
        bool fLoadedIota;
    
        void getTypedNames(::Type t, const string& prefix, Typed::VarType& ctype, string& vname);

        bool getCompiledExpression(Tree sig, InstType& cexp);
        InstType setCompiledExpression(Tree sig, const InstType& cexp);

        void setVectorNameProperty(Tree sig, const string& vecname);
        bool getVectorNameProperty(Tree sig, string& vecname);

        void setTableNameProperty(Tree sig, const string& vecname);
        bool getTableNameProperty(Tree sig, string& vecname);

        StatementInst* generateInitArray(const string& vname, Typed::VarType ctype, int delay);
        StatementInst* generateCopyArray(const string& vname, int index_from, int index_to);
        StatementInst* generateCopyArray(const string& vname_to, const string& vname_from, int size);
        virtual StatementInst* generateShiftArray(const string& vname, int delay);  // Redefined in InterpreterInstructionsCompiler

        ValueInst* generateButtonAux(Tree sig, Tree path, const string& name);
        ValueInst* generateSliderAux(Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step, const string& name);
        ValueInst* generateBargraphAux(Tree sig, Tree path, Tree min, Tree max, ValueInst* exp, const string& name);
   
        ValueInst* generateSelect2WithSelect(Tree sig, ValueInst* sel, ValueInst* val1, ValueInst* val2);
        ValueInst* generateSelect2WithIf(Tree sig, Typed::VarType type, ValueInst* sel, ValueInst* val1, ValueInst* val2);
   
        /* wrapper functions to access code container */
        StatementInst* pushInitMethod(StatementInst* inst)              { return fContainer->pushInitMethod(inst); }
        StatementInst* pushResetUIInstructions(StatementInst* inst)     { return fContainer->pushResetUIInstructions(inst); }
        StatementInst* pushClearMethod(StatementInst* inst)             { return fContainer->pushClearMethod(inst); }
        StatementInst* pushPostInitMethod(StatementInst* inst)          { return fContainer->pushPostInitMethod(inst); }
        StatementInst* pushFrontInitMethod(StatementInst* inst)         { return fContainer->pushFrontInitMethod(inst); }
        StatementInst* pushDestroyMethod(StatementInst* inst)           { return fContainer->pushDestroyMethod(inst); }
        StatementInst* pushStaticInitMethod(StatementInst* inst)        { return fContainer->pushStaticInitMethod(inst); }
        StatementInst* pushPostStaticInitMethod(StatementInst* inst)    { return fContainer->pushPostStaticInitMethod(inst); }
        StatementInst* pushStaticDestroyMethod(StatementInst* inst)     { return fContainer->pushStaticDestroyMethod(inst); }
        StatementInst* pushComputeBlockMethod(StatementInst* inst)      { return fContainer->pushComputeBlockMethod(inst); }
        StatementInst* pushPostComputeBlockMethod(StatementInst* inst)  { return fContainer->pushPostComputeBlockMethod(inst); }
        StatementInst* pushUserInterfaceMethod(StatementInst* inst)     { return fContainer->pushUserInterfaceMethod(inst); }

        StatementInst* pushDeclare(StatementInst* inst)                 { return fContainer->pushDeclare(inst); }
        StatementInst* pushGlobalDeclare(StatementInst* inst)           { return fContainer->pushGlobalDeclare(inst); }
        StatementInst* pushExtGlobalDeclare(StatementInst* inst)        { return fContainer->pushExtGlobalDeclare(inst); }

        StatementInst* pushComputePreDSPMethod(StatementInst* inst)     { return fContainer->pushComputePreDSPMethod(inst); }
        StatementInst* pushComputeDSPMethod(StatementInst* inst)        { return fContainer->pushComputeDSPMethod(inst); }
        StatementInst* pushComputePostDSPMethod(StatementInst* inst)    { return fContainer->pushComputePostDSPMethod(inst); }

        void ensureIotaCode();

        int pow2limit(int x)
        {
            int n = 2;
            while (n < x) { n = 2 * n; }
            return n;
        }

        CodeContainer* signal2Container(const string& name, Tree sig);

        int getSharingCount(Tree sig);
        void setSharingCount(Tree sig, int count);
        void sharingAnalysis(Tree t);
        void sharingAnnotation(int vctxt, Tree sig);

        FIRIndex getCurrentLoopIndex()
        {
            return FIRIndex(fContainer->getCurLoop()->getLoopIndex());
        }

    public:

        InstructionsCompiler(CodeContainer* container);
      
        virtual ~InstructionsCompiler()
        {}

        virtual ValueInst* CS(Tree sig);

        virtual void compileMultiSignal(Tree sig);
        virtual void compileSingleSignal(Tree sig);

        virtual ValueInst* generateVariableStore(Tree sig, ValueInst* inst);
        virtual ValueInst* generateCacheCode(Tree sig, ValueInst* inst);
        virtual ValueInst* forceCacheCode(Tree sig, ValueInst* inst);

        // Code generation
        virtual ValueInst* generateCode(Tree sig);

        virtual ValueInst* generateXtended(Tree sig);
        virtual ValueInst* generateFixDelay(Tree sig, Tree arg, Tree size);
        virtual ValueInst* generatePrefix(Tree sig, Tree x, Tree e);
        virtual ValueInst* generateIota(Tree sig, Tree arg);
        virtual ValueInst* generateBinOp (Tree sig, int opcode, Tree arg1, Tree arg2);

        virtual ValueInst* generateFFun(Tree sig, Tree ff, Tree largs);
        virtual ValueInst* generateWaveform(Tree sig);

        virtual ValueInst* generateInput(Tree sig, int idx);

        virtual ValueInst* generateTable(Tree sig, Tree tsize, Tree content);
        virtual ValueInst* generateStaticTable(Tree sig, Tree tsize, Tree content);
        virtual ValueInst* generateWRTbl(Tree sig, Tree tbl, Tree idx, Tree data);
        virtual ValueInst* generateRDTbl(Tree sig, Tree tbl, Tree idx);
        virtual ValueInst* generateSigGen(Tree sig, Tree content);
        virtual ValueInst* generateStaticSigGen(Tree sig, Tree content);

        virtual ValueInst* generateSelect2(Tree sig, Tree sel, Tree s1, Tree s2);
        virtual ValueInst* generateSelect3(Tree sig, Tree sel, Tree s1, Tree s2, Tree s3);

        virtual ValueInst* generateRecProj(Tree sig, Tree exp, int i);
        virtual ValueInst* generateRec(Tree sig, Tree var, Tree le, int index = -1);

        virtual ValueInst* generateIntCast(Tree sig, Tree x);
        virtual ValueInst* generateFloatCast(Tree sig, Tree x);

        virtual ValueInst* generateButton(Tree sig, Tree label);
        virtual ValueInst* generateCheckbox(Tree sig, Tree label);
        virtual ValueInst* generateVSlider(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
        virtual ValueInst* generateHSlider(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
        virtual ValueInst* generateNumEntry(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);

        virtual ValueInst* generateVBargraph(Tree sig, Tree label, Tree min, Tree max, ValueInst* exp);
        virtual ValueInst* generateHBargraph(Tree sig, Tree label, Tree min, Tree max, ValueInst* exp);
    
        virtual ValueInst* generateSoundfile(Tree sig, Tree label);
        virtual ValueInst* generateSoundfileLength(Tree sig, ValueInst* sf);
        virtual ValueInst* generateSoundfileRate(Tree sig, ValueInst* sf);
        virtual ValueInst* generateSoundfileChannels(Tree sig, ValueInst* sf);
        virtual ValueInst* generateSoundfileBuffer(Tree sig, ValueInst* sf, ValueInst* x, ValueInst* y);

        virtual ValueInst* generateIntNumber(Tree sig, int num);
        virtual ValueInst* generateRealNumber(Tree sig, double num);
        virtual ValueInst* generateFConst(Tree sig, Tree type, const string& file, const string& name);
        virtual ValueInst* generateFVar(Tree sig, Tree type, const string& file, const string& name);

        virtual ValueInst* generateDelayVec(Tree sig, ValueInst* exp, Typed::VarType ctype, const string& vname, int mxd);
        virtual ValueInst* generateDelayLine(ValueInst* exp, Typed::VarType ctype, const string& vname, int mxd, Address::AccessType& var_access);

        // Gestion de la description arborescente de l'IU
        void addUIWidget(Tree path, Tree widget);
        Tree prepareUserInterfaceTree(Tree t);
        void generateUserInterfaceTree(Tree t, bool root = false);
        void generateUserInterfaceElements(Tree elements);
        void generateWidgetCode(Tree fulllabel, Tree varname, Tree sig);

        void generateMacroInterfaceTree(const string& pathname, Tree t);
        void generateMacroInterfaceElements(const string& pathname, Tree elements);
        void generateWidgetMacro(const string& pathname, Tree fulllabel, Tree varname, Tree sig);

        void setDescription(Description* descr)	{ fDescription = descr; }
        Description* getDescription() { return fDescription; }

        Tree prepare(Tree LS);
        Tree prepare2(Tree L0);
        
        void declareWaveform(Tree sig, string& vname, int& size);

};

#endif
