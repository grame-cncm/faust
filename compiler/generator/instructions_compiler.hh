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

/**********************************************************************
			- code_gen.h : generic code generator (projet FAUST) -


		Historique :
		-----------

***********************************************************************/
using namespace std;

#include <string>
#include <list>
#include <set>
#include <map>
#include <vector>

#include "instructions.hh"
#include "code_container.hh"
#include "occurences.hh"
#include "property.hh"
#include "Text.hh"

extern string gMasterName;

class CompilerContext {

};

typedef ValueInst* InstType;

class InstructionsCompiler {

    protected:
    
        CodeContainer* fContainer;
        
        property<ValueInst*> fCompileProperty;
        property<string> fVectorProperty;
        property<string> fTableProperty;
        static map<string, int>	fIDCounters;
        Tree fSharingKey;
        OccMarkup fOccMarkup;
        
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
        StatementInst* generateCopyBackArray(const string& vname_to, const string& vname_from, int size);
        StatementInst* generateShiftArray(const string& vname, int delay);
        
        ValueInst* generateButtonAux(int variability, Tree sig, Tree path, const string& name);
        ValueInst* generateSliderAux(int variability, Tree sig, Tree path, Tree cur, Tree min, Tree max, Tree step, const string& name);
        ValueInst* generateBargraphAux(int variability, Tree sig, Tree path, Tree min, Tree max, ValueInst* exp, const string& name);
        
        void ensureIotaCode();
        
        int pow2limit(int x)
        {
            int n = 2;
            while (n < x) { n = 2*n; }
            return n;
        }
        
        CodeContainer* signal2Container(const string& name, Tree sig);
          
        string getFreshID(const string& prefix);
        int getSharingCount(Tree sig);
        void setSharingCount(Tree sig, int count);
        void sharingAnalysis(Tree t);
        void sharingAnnotation(int vctxt, Tree sig);
        Tree prepare(Tree LS);
        Tree prepare2(Tree L0);
       
    public:
    
        InstructionsCompiler(CodeContainer* container)
            :fContainer(container), fUIRoot(uiFolder(cons(tree(0), 
            tree(subst("$0", gMasterName))))), fDescription(0),
            fLoadedIota(false)
        {}
        virtual ~InstructionsCompiler()
        {}
        
        virtual ValueInst* CS(int variability, Tree sig);
        
        virtual void compileMultiSignal(Tree sig);
        virtual void compileSingleSignal(Tree sig);
        
        virtual ValueInst* generateVariableStore(Tree sig, ValueInst* inst);
        virtual ValueInst* generateCacheCode(Tree sig, ValueInst* inst);
              
        // Code generation
        virtual ValueInst* generateCode(int variability, Tree sig);
      
        virtual ValueInst* generateXtended(int variability, Tree sig);
        virtual ValueInst* generateFixDelay(int variability, Tree sig, Tree arg, Tree size);
        virtual ValueInst* generatePrefix(int variability, Tree sig, Tree x, Tree e);
        virtual ValueInst* generateIota(int variability, Tree sig, Tree arg);
        virtual ValueInst* generateBinOp (int variability, Tree sig, int opcode, Tree arg1, Tree arg2);
        
        virtual ValueInst* generateFFun(int variability, Tree sig, Tree ff, Tree largs);
        
        virtual ValueInst* generateInput(int variability, Tree sig, int idx);
        virtual ValueInst* generateOutput(int variability, Tree sig, int idx, Tree arg1);
        
        virtual ValueInst* generateTable(int variability, Tree sig, Tree tsize, Tree content);
        virtual ValueInst* generateStaticTable(int variability, Tree sig, Tree tsize, Tree content);
        virtual ValueInst* generateWRTbl(int variability, Tree sig, Tree tbl, Tree idx, Tree data);
        virtual ValueInst* generateRDTbl(int variability, Tree sig, Tree tbl, Tree idx);
        virtual ValueInst* generateSigGen(int variability, Tree sig, Tree content);
        virtual ValueInst* generateStaticSigGen(int variability, Tree sig, Tree content);
        
        virtual ValueInst* generateSelect2(int variability, Tree sig, Tree sel, Tree s1, Tree s2);
        virtual ValueInst* generateSelect3(int variability, Tree sig, Tree sel, Tree s1, Tree s2, Tree s3);
        
        virtual ValueInst* generateRecProj(int variability, Tree sig, Tree exp, int i);
        virtual ValueInst* generateRec(int variability, Tree sig, Tree var, Tree le, int index);
        
        virtual ValueInst* generateIntCast(int variability, Tree sig, Tree x);
        virtual ValueInst* generateFloatCast(int variability, Tree sig, Tree x);
        
        virtual ValueInst* generateButton(int variability, Tree sig, Tree label);
        virtual ValueInst* generateCheckbox(int variability, Tree sig, Tree label);
        virtual ValueInst* generateVSlider(int variability, Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
        virtual ValueInst* generateHSlider(int variability, Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
        virtual ValueInst* generateNumEntry(int variability, Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step);
        
        virtual ValueInst* generateVBargraph(int variability, Tree sig, Tree label, Tree min, Tree max, ValueInst* exp);
        virtual ValueInst* generateHBargraph(int variability, Tree sig, Tree label, Tree min, Tree max, ValueInst* exp);

        virtual ValueInst* generateIntNumber(int variability, Tree sig, int num);
        virtual ValueInst* generateRealNumber(int variability, Tree sig, double num);
        virtual ValueInst* generateFConst(int variability, Tree sig, Tree type, const string& file, const string& name);
        virtual ValueInst* generateFVar(int variability, Tree sig, Tree type, const string& file, const string& name);
        
        virtual ValueInst* generateDelayVec(Tree sig, ValueInst* exp, Typed::VarType ctype, const string& vname, int mxd);
        virtual ValueInst* generateDelayLine(ValueInst* exp, Typed::VarType ctype, const string& vname, int mxd, Address::AccessType& var_access);
        
        // Gestion de la description arborescente de l'IU
        void addUIWidget(Tree path, Tree widget);
        Tree prepareUserInterfaceTree(Tree t);
        void generateUserInterfaceTree(Tree t);
        void generateUserInterfaceElements(Tree elements);
        void generateWidgetCode(Tree fulllabel, Tree varname, Tree sig);
        
        void generateMacroInterfaceTree(const string& pathname, Tree t);
        void generateMacroInterfaceElements(const string& pathname, Tree elements);
        void generateWidgetMacro(const string& pathname, Tree fulllabel, Tree varname, Tree sig);

};


#endif
