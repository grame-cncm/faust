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

#ifndef _INSTRUCTION_COMPILER_H
#define _INSTRUCTION_COMPILER_H

#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "Text.hh"
#include "code_container.hh"
#include "garbageable.hh"
#include "global.hh"
#include "instructions.hh"
#include "dcond.hh"
#include "occurrences.hh"
#include "property.hh"

#define _DNF_ 1

class InstructionsCompiler : public virtual Garbageable {
   protected:
    CodeContainer* fContainer;

    property<ValueInst*>  fCompileProperty;
    property<std::string> fVectorProperty;
    property<std::pair<std::string, std::string>>  fStaticInitProperty;
    property<std::pair<std::string, std::string>>  fInstanceInitProperty;
    property<std::string> fTableProperty;
    
    std::map<Tree, Tree> fConditionProperty;  // used with the new X,Y:enable --> sigControl(X*Y,Y>0) primitive
    
    Tree        fSharingKey;
    OccMarkup*  fOccMarkup;

    // Ensure IOTA base fixed delays are computed once
    std::map<int, std::string> fIOTATable;
    
    // Several 'IOTA' variables may be needed when subcontainers are inlined in the main module
    std::string fCurrentIOTA;

    UITree       fUITree;
    Description* fDescription;
    
    /*
     -dlt <N> : threshold between 'mask' and 'select' based ring-buffer delay line model.
     'mask' delay-lines use the next power-of-two value size and a mask (faster but use more memory)
     'select' delay-line use N+1 and use select to wrap the read/write indexes (use less memory but slower)
    */
  
    void getTypedNames(::Type t, const std::string& prefix, Typed::VarType& ctype, std::string& vname);

    bool getCompiledExpression(Tree sig, ValueType& cexp);
    ValueType setCompiledExpression(Tree sig, const ValueType& cexp);

    bool getVectorNameProperty(Tree sig, std::string& vecname);
    void setVectorNameProperty(Tree sig, const std::string& vecname);
    
    bool getTableNameProperty(Tree sig, std::string& vecname);
    void setTableNameProperty(Tree sig, const std::string& vecname);
  
    // Redefined by RustInstructionsCompiler
    virtual StatementInst* generateInitArray(const std::string& vname, Typed::VarType ctype, int delay);
    virtual StatementInst* generateCopyArray(const std::string& vname, int index_from, int index_to);
    virtual StatementInst* generateCopyArray(const std::string& vname_to, const std::string& vname_from, int size);
    
    // Redefined in InterpreterInstructionsCompiler
    virtual StatementInst* generateShiftArray(const std::string& vname, int delay);

    ValueInst* generateButtonAux(Tree sig, Tree path, const std::string& name);
    ValueInst* generateSliderAux(Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step, const std::string& name);
    ValueInst* generateBargraphAux(Tree sig, Tree path, Tree min, Tree max, ValueInst* exp, const std::string& name);

    // Wrapper functions to access code container
    StatementInst* pushInitMethod(StatementInst* inst) { return fContainer->pushInitMethod(inst); }
    StatementInst* pushResetUIInstructions(StatementInst* inst) { return fContainer->pushResetUIInstructions(inst); }
    StatementInst* pushClearMethod(StatementInst* inst) { return fContainer->pushClearMethod(inst); }
    StatementInst* pushPostInitMethod(StatementInst* inst) { return fContainer->pushPostInitMethod(inst); }
    StatementInst* pushPreInitMethod(StatementInst* inst) { return fContainer->pushPreInitMethod(inst); }
    StatementInst* pushAllocateMethod(StatementInst* inst) { return fContainer->pushAllocateMethod(inst); }
    StatementInst* pushDestroyMethod(StatementInst* inst) { return fContainer->pushDestroyMethod(inst); }
    StatementInst* pushStaticInitMethod(StatementInst* inst) { return fContainer->pushStaticInitMethod(inst); }
    StatementInst* pushPostStaticInitMethod(StatementInst* inst) { return fContainer->pushPostStaticInitMethod(inst); }
    StatementInst* pushStaticDestroyMethod(StatementInst* inst) { return fContainer->pushStaticDestroyMethod(inst); }
    StatementInst* pushComputeBlockMethod(StatementInst* inst) { return fContainer->pushComputeBlockMethod(inst); }
    StatementInst* pushPostComputeBlockMethod(StatementInst* inst)
    {
        return fContainer->pushPostComputeBlockMethod(inst);
    }
    StatementInst* pushUserInterfaceMethod(StatementInst* inst) { return fContainer->pushUserInterfaceMethod(inst); }
  
    StatementInst* pushDeclare(StatementInst* inst) { return fContainer->pushDeclare(inst); }
    StatementInst* pushGlobalDeclare(StatementInst* inst) { return fContainer->pushGlobalDeclare(inst); }
    StatementInst* pushExtGlobalDeclare(StatementInst* inst) { return fContainer->pushExtGlobalDeclare(inst); }

    StatementInst* pushPreComputeDSPMethod(StatementInst* inst) { return fContainer->pushPreComputeDSPMethod(inst); }
    StatementInst* pushComputeDSPMethod(StatementInst* inst) { return fContainer->pushComputeDSPMethod(inst); }
    StatementInst* pushPostComputeDSPMethod(StatementInst* inst) { return fContainer->pushPostComputeDSPMethod(inst); }

    void ensureIotaCode();
 
    CodeContainer* signal2Container(const std::string& name, Tree sig);

    FIRIndex getCurrentLoopIndex() { return FIRIndex(fContainer->getCurLoop()->getLoopIndex()); }
    
    void declareWaveform(Tree sig, std::string& vname, int& size);
    
    // Enable/control
    void conditionAnnotation(Tree l);
    void conditionAnnotation(Tree t, Tree nc);
    void conditionStatistics(Tree l);
    
    ValueInst* cnf2code(Tree cc);
    ValueInst* or2code(Tree oc);
    
    ValueInst* dnf2code(Tree cc);
    ValueInst* and2code(Tree oc);
    
    ValueInst* getConditionCode(Tree sig);
    
    ValueInst* genCastedOutput(int type, ValueInst* value);
    ValueInst* genCastedInput(ValueInst* value);
 
   public:
    InstructionsCompiler(CodeContainer* container);

    virtual ~InstructionsCompiler() {}

    virtual ValueInst* CS(Tree sig);

    virtual void compileMultiSignal(Tree sig);
    virtual void compileSingleSignal(Tree sig);

    virtual ValueInst* generateVariableStore(Tree sig, ValueInst* inst);
    virtual ValueInst* generateCacheCode(Tree sig, ValueInst* inst);
    virtual ValueInst* forceCacheCode(Tree sig, ValueInst* inst);

    // Code generation
    virtual ValueInst* generateCode(Tree sig);

    virtual ValueInst* generateXtended(Tree sig);
    virtual ValueInst* generateDelayAccess(Tree sig, Tree arg, Tree size);
    virtual ValueInst* generatePrefix(Tree sig, Tree x, Tree e);
    virtual ValueInst* generateBinOp(Tree sig, int opcode, Tree arg1, Tree arg2);

    virtual ValueInst* generateFFun(Tree sig, Tree ff, Tree largs);
    virtual ValueInst* generateWaveform(Tree sig);

    virtual ValueInst* generateInput(Tree sig, int idx);

    virtual ValueInst* generateTable(Tree sig, Tree tsize, Tree content);
    virtual ValueInst* generateStaticTable(Tree sig, Tree tsize, Tree content);
    virtual ValueInst* generateWRTbl(Tree sig, Tree size, Tree gen, Tree wi, Tree ws);
    virtual ValueInst* generateRDTbl(Tree sig, Tree tbl, Tree ri);
    virtual ValueInst* generateSigGen(Tree sig, Tree content);
    virtual ValueInst* generateStaticSigGen(Tree sig, Tree content);

    virtual ValueInst* generateSelect2(Tree sig, Tree sel, Tree s1, Tree s2);

    virtual ValueInst* generateRecProj(Tree sig, Tree exp, int i);
    virtual ValueInst* generateRec(Tree sig, Tree var, Tree le, int index = -1);

    virtual ValueInst* generateIntCast(Tree sig, Tree x);
    virtual ValueInst* generateBitCast(Tree sig, Tree x);
    virtual ValueInst* generateFloatCast(Tree sig, Tree x);

    virtual ValueInst* generateButton(Tree sig, Tree label);
    virtual ValueInst* generateCheckbox(Tree sig, Tree label);
    virtual ValueInst* generateVSlider(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
    virtual ValueInst* generateHSlider(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
    virtual ValueInst* generateNumEntry(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);

    virtual ValueInst* generateVBargraph(Tree sig, Tree label, Tree min, Tree max, ValueInst* exp);
    virtual ValueInst* generateHBargraph(Tree sig, Tree label, Tree min, Tree max, ValueInst* exp);

    virtual ValueInst* generateSoundfile(Tree sig, Tree label);
    virtual ValueInst* generateSoundfileLength(Tree sig, ValueInst* sf, ValueInst* part);
    virtual ValueInst* generateSoundfileRate(Tree sig, ValueInst* sf, ValueInst* part);
    virtual ValueInst* generateSoundfileBuffer(Tree sig, ValueInst* sf, ValueInst* x, ValueInst* y, ValueInst* z);

    virtual ValueInst* generateIntNumber(Tree sig, int num);
    virtual ValueInst* generateInt64Number(Tree sig, int64_t num);
    virtual ValueInst* generateRealNumber(Tree sig, double num);
    virtual ValueInst* generateFConst(Tree sig, Tree type, const std::string& file, const std::string& name);
    virtual ValueInst* generateFVar(Tree sig, Tree type, const std::string& file, const std::string& name);

    virtual ValueInst* generateDelayVec(Tree sig, ValueInst* exp, Typed::VarType ctype, const std::string& vname, int mxd);
    virtual ValueInst* generateDelayLine(ValueInst* exp, Typed::VarType ctype, const std::string& vname, int mxd,
                                         Address::AccessType& access, ValueInst* ccs);
    
    virtual ValueInst* generateControl(Tree sig, Tree x, Tree y);

    // UI hierachy description
    void generateUserInterfaceTree(Tree t, bool root = false);
    void generateUserInterfaceElements(Tree elements);
    void generateWidgetCode(Tree fulllabel, Tree varname, Tree sig);

    void generateMacroInterfaceTree(const std::string& pathname, Tree t);
    void generateMacroInterfaceElements(const std::string& pathname, Tree elements);
    void generateWidgetMacro(const std::string& pathname, Tree fulllabel, Tree varname, Tree sig);

    void setDescription(Description* descr) { fDescription = descr; }
    Description* getDescription() { return fDescription; }
    
    Tree prepare(Tree LS);
    Tree prepare2(Tree L0);
  
};

#endif
