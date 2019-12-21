/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>

#include "Text.hh"
#include "binop.hh"
#include "dsp_factory.hh"
#include "instructions.hh"
#include "type_manager.hh"

using namespace std;

class FIRInstVisitor : public InstVisitor, public CStringTypeManager {
   private:
    int               fTab;
    std::ostream*     fOut;
    bool              fFinishLine;
    map<string, bool> gFunctionSymbolTable;

   public:
    FIRInstVisitor(std::ostream* out, int tab = 0)
        : CStringTypeManager(FLOATMACRO, "*"), fTab(tab), fOut(out), fFinishLine(true)
    {
    }

    virtual ~FIRInstVisitor() {}

    void Tab(int n) { fTab = n; }

    void EndLine()
    {
        if (fFinishLine) {
            tab(fTab, *fOut);
        }
    }

    virtual string generateType(Typed* type)
    {
        BasicTyped*  basic_typed  = dynamic_cast<BasicTyped*>(type);
        NamedTyped*  named_typed  = dynamic_cast<NamedTyped*>(type);
        FunTyped*    fun_typed    = dynamic_cast<FunTyped*>(type);
        ArrayTyped*  array_typed  = dynamic_cast<ArrayTyped*>(type);
        VectorTyped* vector_typed = dynamic_cast<VectorTyped*>(type);
        StructTyped* struct_typed = dynamic_cast<StructTyped*>(type);

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
            std::string num_size     = std::to_string(array_typed->fSize);
            if (basic_typed1) {
                faustassert(fTypeDirectTable.find(basic_typed1->fType) != fTypeDirectTable.end());
                return (array_typed->fSize == 0)
                           ? "\"" + fTypeDirectTable[basic_typed1->fType] + "*\""
                           : "\"" + fTypeDirectTable[basic_typed1->fType] + "[" + num_size + "]" + "\"";
            } else if (array_typed1) {
                return generateType(array_typed1) + "[" + num_size + "]";
            } else if (named_typed1) {
                return named_typed1->fName + "[" + num_size + "]";
            } else {
                faustassert(false);
                return "";
            }
        } else if (vector_typed) {
            std::string num_size = std::to_string(vector_typed->fSize);
            faustassert(fTypeDirectTable.find(vector_typed->fType->fType) != fTypeDirectTable.end());
            return (vector_typed->fSize == 0)
                       ? "Type<" + fTypeDirectTable[vector_typed->fType->fType] + ">" + "()"
                       : "VecType<" + fTypeDirectTable[vector_typed->fType->fType] + ">" + "(" + num_size + ")";
        } else if (struct_typed) {
            std::stringstream res;
            res << "StructType<\"" << struct_typed->fName << "\",";
            for (auto& it : struct_typed->fFields) {
                res << "(" << generateType(it) << ")";
            }
            res << ">";
            return res.str();
        } else {
            faustassert(false);
            return "";
        }
    }

    virtual string generateType(Typed* type, const string& name)
    {
        BasicTyped*  basic_typed  = dynamic_cast<BasicTyped*>(type);
        NamedTyped*  named_typed  = dynamic_cast<NamedTyped*>(type);
        FunTyped*    fun_typed    = dynamic_cast<FunTyped*>(type);
        ArrayTyped*  array_typed  = dynamic_cast<ArrayTyped*>(type);
        VectorTyped* vector_typed = dynamic_cast<VectorTyped*>(type);
        StructTyped* struct_typed = dynamic_cast<StructTyped*>(type);

        if (basic_typed) {
            return "\"" + fTypeDirectTable[basic_typed->fType] + "\", " + name;
        } else if (named_typed) {
            // TODO : break code with subclasses
            // return named_typed->fName + generateType(named_typed->fType) + ", " + name;
            return "\"" + named_typed->fName + "\", " + name;
        } else if (fun_typed) {
            return "Function type";
        } else if (array_typed) {
            BasicTyped* basic_typed1 = dynamic_cast<BasicTyped*>(array_typed->fType);
            ArrayTyped* array_typed1 = dynamic_cast<ArrayTyped*>(array_typed->fType);
            NamedTyped* named_typed1 = dynamic_cast<NamedTyped*>(array_typed->fType);
            std::string num_size     = std::to_string(array_typed->fSize);
            if (basic_typed1) {
                return (array_typed->fSize == 0)
                           ? "\"" + fTypeDirectTable[basic_typed1->fType] + "*\", " + name
                           : "\"" + fTypeDirectTable[basic_typed1->fType] + "\", " + name + "[" + num_size + "]";
            } else if (array_typed1) {
                return generateType(array_typed1) + "[" + num_size + "]";
            } else if (named_typed1) {
                return named_typed1->fName + "[" + num_size + "]";
            } else {
                faustassert(false);
                return "";
            }
        } else if (vector_typed) {
            std::string num_size = std::to_string(vector_typed->fSize);
            return (vector_typed->fSize == 0)
                       ? "Type<" + fTypeDirectTable[vector_typed->fType->fType] + ">" + "()"
                       : "VecType<" + fTypeDirectTable[vector_typed->fType->fType] + ">" + "(" + num_size + ")";
        } else if (struct_typed) {
            std::stringstream res;
            res << "StructType<\"" << struct_typed->fName << "\",";
            for (auto& it : struct_typed->fFields) {
                res << "(" << generateType(it) << ")";
            }
            res << ">";
            return res.str();
        } else {
            faustassert(false);
            return "";
        }
    }

    virtual void visit(AddMetaDeclareInst* inst)
    {
        *fOut << "AddMetaDeclareInst(" << inst->fZone << ", " << quote(inst->fKey) << ", " << quote(inst->fValue)
              << ")";
        EndLine();
    }

    virtual void visit(OpenboxInst* inst)
    {
        string name;
        switch (inst->fOrient) {
            case OpenboxInst::kVerticalBox:
                name = "OpenVerticalBox(";
                break;
            case OpenboxInst::kHorizontalBox:
                name = "OpenHorizontalBox(";
                break;
            case OpenboxInst::kTabBox:
                name = "OpenTabBox(";
                break;
        }
        *fOut << name << "\"" << inst->fName << "\"";
        *fOut << ")";
        EndLine();
    }

    virtual void visit(CloseboxInst* inst)
    {
        *fOut << "CloseboxInst";
        tab(fTab, *fOut);
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
                name = "AddHorizontalSlider(";
                break;
            case AddSliderInst::kVertical:
                name = "AddVerticalSlider(";
                break;
            case AddSliderInst::kNumEntry:
                name = "AddNumEntry";
                break;
        }
        *fOut << name << quote(inst->fLabel) << ", " << inst->fZone << ", " << checkReal(inst->fInit) << ", "
              << checkReal(inst->fMin) << ", " << checkReal(inst->fMax) << ", " << checkReal(inst->fStep) << ")";
        EndLine();
    }

    virtual void visit(AddBargraphInst* inst)
    {
        string name;
        switch (inst->fType) {
            case AddBargraphInst::kHorizontal:
                name = "AddHorizontalBargraph(";
                break;
            case AddBargraphInst::kVertical:
                name = "AddVerticalBargraph(";
                break;
        }
        *fOut << name << quote(inst->fLabel) << ", " << inst->fZone << ", " << checkReal(inst->fMin) << ", "
              << checkReal(inst->fMax) << ")";
        EndLine();
    }

    virtual void visit(AddSoundfileInst* inst)
    {
        *fOut << "AddSoundfile(" << quote(inst->fLabel) << ", " << quote(inst->fURL) << ", &" << inst->fSFZone << ")";
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
        *fOut << generateType(inst->fType, inst->fAddress->getName());
        *fOut << ", " << Address::dumpString(inst->fAddress->getAccess());
        if (inst->fValue) {
            *fOut << ", ";
            inst->fValue->accept(this);
        }
        *fOut << ")";
        EndLine();
    }

    virtual void visit(DeclareStructTypeInst* inst)
    {
        *fOut << "DeclareStructTypeInst(" << generateType(inst->fType) << ")";
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

        // If function is actually a method (that is "xx::name"), then keep "xx::name" in gSymbolGlobalsTable but print
        // "name"
        string fun_name = inst->fName;
        size_t pos;
        if ((pos = inst->fName.find("::")) != string::npos) {
            fun_name = inst->fName.substr(pos + 2);  // After the "::"
        }

        // Prototype
        *fOut << "DeclareFunInst(";
        size_t size = inst->fType->fArgsTypes.size(), i = 0;
        *fOut << generateType(inst->fType->fResult, "\"" + fun_name + "\"");
        if (size > 0) {  // Has more arguments...
            *fOut << ", ";
        }
        for (auto& it : inst->fType->fArgsTypes) {
            *fOut << generateType(it);
            if (i++ < size - 1) *fOut << ", ";
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
            back(1, *fOut);
            *fOut << "EndDeclare";
            tab(fTab, *fOut);
        }
    }

    virtual void visit(NamedAddress* named)
    {
        *fOut << "Address(" << named->fName << ", " << Address::dumpString(named->fAccess) << ")";
    }

    virtual void visit(IndexedAddress* indexed)
    {
        indexed->fAddress->accept(this);
        DeclareStructTypeInst* struct_type = isStructType(indexed->getName());
        if (struct_type) {
            Int32NumInst* field_index = static_cast<Int32NumInst*>(indexed->fIndex);
            *fOut << "->" << struct_type->fType->getName(field_index->fNum);
        } else {
            *fOut << "[";
            indexed->fIndex->accept(this);
            *fOut << "]";
        }
    }

    virtual void visit(LoadVarInst* inst)
    {
        *fOut << "LoadVarInst(";
        inst->fAddress->accept(this);
        *fOut << ")";
    }

    virtual void visit(LoadVarAddressInst* inst)
    {
        *fOut << "LoadVarAddressInst(";
        inst->fAddress->accept(this);
        *fOut << ")";
    }

    virtual void visit(StoreVarInst* inst)
    {
        *fOut << "StoreVarInst(";
        inst->fAddress->accept(this);
        *fOut << ", ";
        inst->fValue->accept(this);
        *fOut << ")";
        EndLine();
    }

    virtual void visit(FloatNumInst* inst) { *fOut << "Float(" << checkFloat(inst->fNum) << ")"; }

    virtual void visit(FloatArrayNumInst* inst)
    {
        *fOut << "FloatArrayNumInst";
        char sep = '{';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << checkFloat(inst->fNumTable[i]);
            sep = ',';
        }
        *fOut << '}';
    }

    virtual void visit(Int32NumInst* inst) { *fOut << "Int32(" << inst->fNum << ")"; }

    virtual void visit(Int64NumInst* inst) { *fOut << "Int64(" << inst->fNum << ")"; }

    virtual void visit(Int32ArrayNumInst* inst)
    {
        *fOut << "Int32ArrayNumInst";
        char sep = '{';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << inst->fNumTable[i];
            sep = ',';
        }
        *fOut << '}';
    }

    virtual void visit(BoolNumInst* inst) { *fOut << "Bool(" << inst->fNum << ")"; }

    virtual void visit(DoubleNumInst* inst) { *fOut << "Double(" << checkDouble(inst->fNum) << ")"; }

    virtual void visit(DoubleArrayNumInst* inst)
    {
        *fOut << "DoubleArrayNumInst";
        char sep = '{';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << checkDouble(inst->fNumTable[i]);
            sep = ',';
        }
        *fOut << '}';
    }

    virtual void visit(BinopInst* inst)
    {
        *fOut << "BinopInst(";
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
        *fOut << "CastInst(";
        *fOut << generateType(inst->fType);
        *fOut << ", ";
        inst->fInst->accept(this);
        *fOut << ")";
    }

    virtual void visit(BitcastInst* inst)
    {
        *fOut << "Bitcast(";
        *fOut << generateType(inst->fType);
        *fOut << ", ";
        inst->fInst->accept(this);
        *fOut << ")";
    }

    virtual void visit(FunCallInst* inst)
    {
        string fun_name = (inst->fMethod) ? "MethodFunCallInst(" : "FunCallInst(";
        *fOut << fun_name;

        *fOut << "\"" << inst->fName << "\"";

        size_t size = inst->fArgs.size(), i = 0;
        if (size > 0) *fOut << ", ";
        for (auto& it : inst->fArgs) {
            // Compile argument
            it->accept(this);
            if (i++ < size - 1) *fOut << ", ";
        }
        *fOut << ")";
    }

    virtual void visit(Select2Inst* inst)
    {
        *fOut << "Select2Inst(";
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
        back(1, *fOut);
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
        back(1, *fOut);
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
        back(1, *fOut);
        *fOut << "EndWhileLoop";
        tab(fTab, *fOut);
    }

    virtual void visit(BlockInst* inst)
    {
        *fOut << "BlockInst ";
        fTab++;
        tab(fTab, *fOut);
        for (auto& it : inst->fCode) {
            it->accept(this);
        }
        fTab--;
        back(1, *fOut);
        *fOut << "EndBlock";
        tab(fTab, *fOut);
    }

    virtual void visit(::SwitchInst* inst)
    {
        *fOut << "SwitchInst ";
        inst->fCond->accept(this);
        fTab++;
        tab(fTab, *fOut);
        for (auto& it : inst->fCode) {
            if (it.first == -1) {  // -1 used to code "default" case
                *fOut << "Default ";
            } else {
                *fOut << "Case " << it.first;
            }
            fTab++;
            tab(fTab, *fOut);
            (it.second)->accept(this);
            fTab--;
            back(1, *fOut);
            *fOut << "EndCase";
            tab(fTab, *fOut);
        }
        fTab--;
        back(1, *fOut);
        *fOut << "EndSWitch";
        tab(fTab, *fOut);
    }
};

#endif
