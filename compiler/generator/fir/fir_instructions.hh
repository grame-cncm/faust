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

#ifndef _FIR_INSTRUCTIONS_H
#define _FIR_INSTRUCTIONS_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <list>
#include <set>
#include <map>

#include "instructions.hh"
#include "type_manager.hh"
#include "binop.hh"
#include "Text.hh"
#include "dsp_factory.hh"

using namespace std;

class FIRInstVisitor : public InstVisitor, public CStringTypeManager {

    private:

        int fTab;
        std::ostream* fOut;
        bool fFinishLine;
        map <string, bool> gFunctionSymbolTable;
    
        void generateAccess(Address* address)
        {
            if (address->getAccess() & Address::kGlobal) {
                *fOut << "global, ";
            }
            if (address->getAccess() & Address::kStaticStruct) {
                *fOut << "static, ";
            }
            if (address->getAccess() & Address::kVolatile) {
                *fOut << "volatile, ";
            }
            if (address->getAccess() & Address::kStruct) {
                *fOut << "struct, ";
            } else if (address->getAccess() & Address::kStack) {
                *fOut << "stack, ";
            } else if (address->getAccess() & Address::kLink) {
                *fOut << "link, ";
            } else if (address->getAccess() & Address::kLoop) {
                *fOut << "loop, ";
            } else if (address->getAccess() & Address::kFunArgs) {
                *fOut << "kFunArgs, ";
            }
        }
   
    public:

        FIRInstVisitor(std::ostream* out, int tab = 0)
            :CStringTypeManager(FLOATMACRO, "*"), fTab(tab), fOut(out), fFinishLine(true)
        {}

        virtual ~FIRInstVisitor()
        {}
       
        void Tab(int n) {fTab = n;}

        void EndLine()
        {
            if (fFinishLine) {
                tab(fTab, *fOut);
            }
        }

        virtual string generateType(Typed* type)
        {
            BasicTyped* basic_typed = dynamic_cast<BasicTyped*>(type);
            NamedTyped* named_typed = dynamic_cast<NamedTyped*>(type);
            FunTyped* fun_typed = dynamic_cast<FunTyped*>(type);
            ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(type);
            VectorTyped* vector_typed = dynamic_cast<VectorTyped*>(type);

            if (basic_typed) {
                faustassert(fTypeDirectTable.find(basic_typed->fType) != fTypeDirectTable.end());
                return "\"" + fTypeDirectTable[basic_typed->fType] + "\"";
            } else if (named_typed) {
                return generateType(named_typed->fType) + ", " + named_typed->fName;
            } else if (fun_typed) {
                return "Function type";
            } else if (array_typed) {
                BasicTyped* basic_typed1 = dynamic_cast<BasicTyped*>(array_typed->fType);
                ArrayTyped* array_typed1 = dynamic_cast<ArrayTyped*>(array_typed->fType);
                NamedTyped* named_typed1 = dynamic_cast<NamedTyped*>(array_typed->fType);
                std::ostringstream num_str;
                num_str << array_typed->fSize;
                if (basic_typed1) {
                    /*
                    return (array_typed->fSize == 0)
                        ? "\"" + fTypeDirectTable[basic_typed1->fType] + "*\""
                        : "\"" + fTypeDirectTable[basic_typed1->fType] + "[" + num_str.str() + "]" + "\"";
                    */
                    faustassert(fTypeDirectTable.find(basic_typed1->fType) != fTypeDirectTable.end());
                    return (array_typed->fSize == 0)
                        ? fTypeDirectTable[basic_typed1->fType]
                        : fTypeDirectTable[basic_typed1->fType] + "[" + num_str.str() + "]";
                } else if (array_typed1) {
                    return generateType(array_typed1) + "[" + num_str.str() + "]";
                } else if (named_typed1) {
                    return named_typed1->fName + "[" + num_str.str() + "]";
                } else {
                    faustassert(false);
                    return "";
                }
            } else if (vector_typed) {
                std::ostringstream num_str;
                num_str << vector_typed->fSize;
                faustassert(fTypeDirectTable.find(vector_typed->fType->fType) != fTypeDirectTable.end());
                return (vector_typed->fSize == 0)
                    ? "Type<" + fTypeDirectTable[vector_typed->fType->fType] + ">" + "()"
                    : "VecType<" + fTypeDirectTable[vector_typed->fType->fType] + ">" + "(" + num_str.str() + ")";
            } else {
                faustassert(false);
                return "";
            }
        }

        virtual string generateType(Typed* type, const string& name)
        {
            BasicTyped* basic_typed = dynamic_cast<BasicTyped*>(type);
            NamedTyped* named_typed = dynamic_cast<NamedTyped*>(type);
            FunTyped* fun_typed = dynamic_cast<FunTyped*>(type);
            ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(type);
            VectorTyped* vector_typed = dynamic_cast<VectorTyped*>(type);

            if (basic_typed) {
                return "\"" + fTypeDirectTable[basic_typed->fType] + "\", " + name;
            } else if (named_typed) {
                // TODO : break code with subclasses
                //return named_typed->fName + generateType(named_typed->fType) + ", " + name;
                return named_typed->fName + ", " + name;
            } else if (fun_typed) {
                return "Function type";
            } else if (array_typed) {
                BasicTyped* basic_typed1 = dynamic_cast<BasicTyped*>(array_typed->fType);
                ArrayTyped* array_typed1 = dynamic_cast<ArrayTyped*>(array_typed->fType);
                NamedTyped* named_typed1 = dynamic_cast<NamedTyped*>(array_typed->fType);
                std::ostringstream num_str;
                num_str << array_typed->fSize;
                if (basic_typed1) {
                    return (array_typed->fSize == 0)
                        /*
                        ? "\"" + fTypeDirectTable[basic_typed1->fType] + "*\", " + name
                        : "\"" + fTypeDirectTable[basic_typed1->fType] + "\", " + name + "[" + num_str.str() + "]";
                        */
                        ? fTypeDirectTable[basic_typed1->fType] + "*, " + name
                        : fTypeDirectTable[basic_typed1->fType] + ", " + name + "[" + num_str.str() + "]";
                        //: "\"" + fTypeDirectTable[basic_typed1->fType] + "[" + num_str.str() + "]" + "\", " + name;
                } else if (array_typed1) {
                    return generateType(array_typed1) + "[" + num_str.str() + "]";
                } else if (named_typed1) {
                    return named_typed1->fName + "[" + num_str.str() + "]";
                } else {
                    faustassert(false);
                    return "";
                }
            } else if (vector_typed) {
                std::ostringstream num_str;
                num_str << vector_typed->fSize;
                return (vector_typed->fSize == 0)
                    ? "Type<" + fTypeDirectTable[vector_typed->fType->fType] + ">" + "()"
                    : "VecType<" + fTypeDirectTable[vector_typed->fType->fType] + ">" + "(" + num_str.str() + ")";
            } else {
                faustassert(false);
                return "";
            }
        }

        virtual void visit(AddMetaDeclareInst* inst)
        {
            *fOut << "AddMetaDeclareInst(" << inst->fZone <<", " << quote(inst->fKey) << ", " << quote(inst->fValue) << ")"; EndLine();
        }

        virtual void visit(OpenboxInst* inst)
        {
            string name;
            switch (inst->fOrient) {
                case 0:
                    name = "OpenVerticalBox("; break;
                case 1:
                    name = "OpenHorizontalBox("; break;
                case 2:
                    name = "OpenTabBox("; break;
            }
            *fOut << name << "\"" << inst->fName << "\"";
            *fOut << ")";
            EndLine();
        }

        virtual void visit(CloseboxInst* inst)
        {
            *fOut << "CloseboxInst"; tab(fTab, *fOut);
        }
        virtual void visit(AddButtonInst* inst)
        {
            if (inst->fType == AddButtonInst::kDefaultButton) {
                *fOut << "AddButtonInst(" << quote(inst->fLabel) << inst->fZone;
            } else {
                *fOut << "AddCheckButtonInst(" << quote(inst->fLabel) << inst->fZone;
            }
            *fOut << ")";
            EndLine();
        }

        virtual void visit(AddSliderInst* inst)
        {
            string name;
            switch (inst->fType) {
                case AddSliderInst::kHorizontal:
                    name = "AddHorizontalSlider("; break;
                case AddSliderInst::kVertical:
                    name = "AddVerticalSlider("; break;
                case AddSliderInst::kNumEntry:
                    name = "AddNumEntry"; break;
            }
            *fOut << name  << quote(inst->fLabel) << ", " 
            << inst->fZone << ", " << checkReal(inst->fInit) << ", " 
            << checkReal(inst->fMin) << ", " << checkReal(inst->fMax) 
            << ", " << checkReal(inst->fStep) << ")";
            EndLine();
        }

        virtual void visit(AddBargraphInst* inst)
        {
            string name;
            switch (inst->fType) {
                case AddBargraphInst::kHorizontal:
                    name = "AddHorizontalBargraph("; break;
                case AddBargraphInst::kVertical:
                    name = "AddVerticalBargraph("; break;
            }
            *fOut << name << quote(inst->fLabel) << ", " 
            << inst->fZone << ", "<< checkReal(inst->fMin) 
            << ", " << checkReal(inst->fMax) << ")";
            EndLine();
        }

        virtual void visit(LabelInst* inst)
        {
            *fOut << inst->fLabel;
            tab(fTab, *fOut);
        }
    
        virtual void visit(DeclareVarInst* inst)
        {
            *fOut << "DeclareVarInst(";
            generateAccess(inst->fAddress);
            *fOut << generateType(inst->fType, inst->fAddress->getName());
            if (inst->fValue) {
                *fOut << ", "; inst->fValue->accept(this);
            } 
            *fOut << ")";
            EndLine();
        }

        virtual void visit(DeclareTypeInst* inst)
        {
            *fOut << "DeclareTypeInst(" << generateType(inst->fType) << ")";
            EndLine();
        }

        virtual void visit(RetInst* inst)
        {
            if (inst->fResult) {
                *fOut << "RetInst(";
                inst->fResult->accept(this);
                *fOut << ")";
                EndLine();
            }
        }

        virtual void visit(DropInst* inst)
        {
            if (inst->fResult) {
                *fOut << "DropInst(";
                inst->fResult->accept(this);
                *fOut << ")";
                EndLine();
            }
        }

        virtual void visit(DeclareFunInst* inst)
        {
            // Already generated
            if (gFunctionSymbolTable.find(inst->fName) != gFunctionSymbolTable.end()) {
                return;
            } else {
                gFunctionSymbolTable[inst->fName] = true;
            }
            
            // If function is actually a method (that is "xx::name"), then keep "xx::name" in gSymbolGlobalsTable but print "name"
            string fun_name = inst->fName;
            size_t pos;
            if ((pos = inst->fName.find("::")) != string::npos) {
                fun_name = inst->fName.substr(pos + 2); // After the "::"
            }

            // Prototype
            *fOut << "DeclareFunInst(";
            int size = inst->fType->fArgsTypes.size(), i = 0;
            *fOut << generateType(inst->fType->fResult, "\"" + fun_name + "\"");
            if (size > 0) { // Has more arguments...
                *fOut << ", ";
            } 
            list<NamedTyped*>::const_iterator it;
            for (it = inst->fType->fArgsTypes.begin(); it != inst->fType->fArgsTypes.end(); it++, i++) {
                *fOut << generateType((*it));
                if (i < size - 1) *fOut << ", ";
            }

            if (inst->fCode->fCode.size() == 0) {
                *fOut << ")";  // Pure prototype
                tab(fTab, *fOut);
            } else {
                // Function body
                *fOut << ")";
                fTab++;
                tab(fTab, *fOut);
                inst->fCode->accept(this);
                fTab--;
                *fOut << "EndDeclare";
                tab(fTab, *fOut);
            }
        }
        
        virtual void visit(NamedAddress* named)
        {
            *fOut << named->fName;
        }

        virtual void visit(IndexedAddress* indexed)
        {
            indexed->fAddress->accept(this);
            *fOut << "["; indexed->fIndex->accept(this); *fOut << "]";
        }

        virtual void visit(LoadVarInst* inst)
        {
            if (inst->fSize > 1) {
                *fOut << "LoadVarInstVec<" << inst->fSize << ">(";
            } else {
                *fOut << "LoadVarInst(";
            }
            generateAccess(inst->fAddress);
            inst->fAddress->accept(this);
            *fOut << ")";
        }

        virtual void visit(LoadVarAddressInst* inst)
        {
            if (inst->fSize > 1) {
                *fOut << "LoadVarAddressInstVec<" << inst->fSize << ">(";
            } else {
                *fOut << "LoadVarAddressInst(";
            }
            generateAccess(inst->fAddress);
            inst->fAddress->accept(this);
            *fOut << ")";
        }

        virtual void visit(StoreVarInst* inst)
        {
            if (inst->fValue->fSize > 1) {
                *fOut << "StoreVarInstVec<" << inst->fValue->fSize << ">(";
            } else {
                *fOut << "StoreVarInst(";
            }
            generateAccess(inst->fAddress);
            inst->fAddress->accept(this);
            *fOut << ", ";
            inst->fValue->accept(this);
            *fOut << ")";
            EndLine();
        }

        virtual void visit(FloatNumInst* inst)
        {
            if (inst->fSize > 1) {
                *fOut << "FloatVec<" << inst->fSize << ">(" << checkFloat(inst->fNum) << ")";
            } else {
                *fOut << "Float(" << checkFloat(inst->fNum) << ")";
            }
        }
        
        virtual void visit(FloatArrayNumInst* inst)
        {
            char sep = '{';
            for (unsigned int i = 0; i < inst->fNumTable.size(); i++) {
                *fOut << sep << checkFloat(inst->fNumTable[i]);
                 sep = ',';
            }
            *fOut << '}';
        }

        virtual void visit(Int32NumInst* inst)
        {
            if (inst->fSize > 1) {
                *fOut << "Int32Vec<" << inst->fSize << ">(" << inst->fNum  << ")";
            } else {
                *fOut << "Int32(" << inst->fNum  << ")";
            }
        }
    
        virtual void visit(Int64NumInst* inst)
        {
            if (inst->fSize > 1) {
                *fOut << "Int64Vec<" << inst->fSize << ">(" << inst->fNum  << ")";
            } else {
                *fOut << "Int64(" << inst->fNum  << ")";
            }
        }
    
        virtual void visit(Int32ArrayNumInst* inst)
        {
            char sep = '{';
            for (unsigned int i = 0; i < inst->fNumTable.size(); i++) {
                *fOut << sep << inst->fNumTable[i];
                 sep = ',';
            }
            *fOut << '}';
        }

        virtual void visit(BoolNumInst* inst)
        {
            if (inst->fSize > 1) {
                *fOut << "BoolVec<" << inst->fSize << ">(" << inst->fNum  << ")";
            } else {
                *fOut << "Bool(" << inst->fNum  << ")";
            }
        }

        virtual void visit(DoubleNumInst* inst)
        {
            if (inst->fSize > 1) {
                *fOut << "DoubleVec<" << inst->fSize << ">(" << checkDouble(inst->fNum) << ")";
            } else {
                *fOut << "Double(" << checkDouble(inst->fNum) << ")";
            }
        }
        
        virtual void visit(DoubleArrayNumInst* inst)
        {
            char sep = '{';
            for (unsigned int i = 0; i < inst->fNumTable.size(); i++) {
                *fOut << sep << checkDouble(inst->fNumTable[i]);
                 sep = ',';
            }
            *fOut << '}';
        }

        virtual void visit(BinopInst* inst)
        {
            if (inst->fSize > 1) {
                *fOut << "BinopInstVec<" << inst->fSize << ">(";
            } else {
                *fOut << "BinopInst(";
            }
            *fOut << "\"";
            *fOut << gBinOpTable[inst->fOpcode]->fName;
            *fOut << "\"";
            *fOut << ", ";
            faustassert(inst->fInst1);
            inst->fInst1->accept(this);
            *fOut << ", ";
            faustassert(inst->fInst2);
            inst->fInst2->accept(this);
            *fOut << ")";
        }

        virtual void visit(::CastInst* inst)
        {
            if (inst->fSize > 1) {
                *fOut << "CastInstVec<" << inst->fSize << ">(";
            } else {
                *fOut << "CastInst(";
            }
            *fOut << generateType(inst->fType);
            *fOut << ", ";
            inst->fInst->accept(this);
            *fOut << ")";
        }
    
        virtual void visit(BitcastInst* inst)
        {
            if (inst->fSize > 1) {
                *fOut << "BitcastInstVec<" << inst->fSize << ">(";
            } else {
                *fOut << "Bitcast(";
            }
            *fOut << generateType(inst->fType);
            *fOut << ", ";
            inst->fInst->accept(this);
            *fOut << ")";
        }

        virtual void visit(FunCallInst* inst)
        {
            if (inst->fSize > 1) {
                string fun_name = (inst->fMethod) ? "MethodFunCallInstVec<" : "FunCallInstVec<";
                *fOut << fun_name << inst->fSize << ">(";
            } else {
                string fun_name = (inst->fMethod) ? "MethodFunCallInst(" : "FunCallInst(";
                *fOut << fun_name;
            }

            *fOut << "\"" <<inst->fName << "\"";
            list<ValueInst*>::const_iterator it;

            int size = inst->fArgs.size(), i = 0;
            if (size > 0) *fOut << ", ";
            for (it = inst->fArgs.begin(); it != inst->fArgs.end(); it++, i++) {
                // Compile argument
                (*it)->accept(this);
                if (i < size - 1) *fOut << ", ";
            }
            *fOut << ")";
        }

        virtual void visit(Select2Inst* inst)
        {
            if (inst->fSize > 1) {
                *fOut << "Select2InstVec<" << inst->fSize << ">(";
            } else {
                *fOut << "Select2Inst(";
            }
            inst->fCond->accept(this);
            *fOut << " ";
            inst->fThen->accept(this);
            *fOut << " ";
            inst->fElse->accept(this);
            *fOut << ")";
        }

        virtual void visit(IfInst* inst)
        {
            *fOut << "IfInst ";
                fTab++;
                tab(fTab, *fOut);
                inst->fCond->accept(this);
                tab(fTab, *fOut);
                inst->fThen->accept(this);
                fTab--;
            if (inst->fElse->fCode.size() > 0) {
                fTab++;
                tab(fTab, *fOut);
                inst->fElse->accept(this);
                fTab--;
            }
            *fOut << "EndIf";
            tab(fTab, *fOut);
        }

        virtual void visit(ForLoopInst* inst)
        {
            *fOut << "ForLoopInst ";
                fFinishLine = false;
                fTab++;
                tab(fTab, *fOut);
                inst->fInit->accept(this);
                tab(fTab, *fOut);
                inst->fEnd->accept(this);
                tab(fTab, *fOut);
                inst->fIncrement->accept(this);
                fFinishLine = true;
                tab(fTab, *fOut);
                inst->fCode->accept(this);
                fTab--;
            *fOut << "EndForLoop";
            tab(fTab, *fOut);
        }

        virtual void visit(WhileLoopInst* inst)
        {
            *fOut << "WhileLoopInst ";
            inst->fCond->accept(this);
                fTab++;
                tab(fTab, *fOut);
                inst->fCode->accept(this);
                fTab--;
            *fOut << "EndWhileLoop";
            tab(fTab, *fOut);
        }

        virtual void visit(BlockInst* inst)
        {
            *fOut << "BlockInst ";
            fTab++;
            tab(fTab, *fOut);
                list<StatementInst*>::const_iterator it;
                for (it = inst->fCode.begin(); it != inst->fCode.end(); it++) {
                    (*it)->accept(this);
                }
            fTab--;
            *fOut << "EndBlock";
            tab(fTab, *fOut);
        }

        virtual void visit(::SwitchInst* inst)
        {
            *fOut << "SwitchInst ";
            inst->fCond->accept(this);
                fTab++;
                tab(fTab, *fOut);
                list<pair <int, BlockInst*> >::const_iterator it;
                for (it = inst->fCode.begin(); it != inst->fCode.end(); it++) {
                    if ((*it).first == -1) { // -1 used to code "default" case
                        *fOut << "Default ";
                    } else {
                         *fOut << "Case " << (*it).first;
                    }
                        fTab++;
                        tab(fTab, *fOut);
                        ((*it).second)->accept(this);
                        *fOut << "EndCase";
                        fTab--;
                    tab(fTab, *fOut);
                }
                fTab--;
            *fOut << "EndSWitch";
            tab(fTab, *fOut);
        }

};

#endif
