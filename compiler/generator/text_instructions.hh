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

#ifndef _TEXT_INSTRUCTIONS_H
#define _TEXT_INSTRUCTIONS_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "Text.hh"
#include "fir_to_fir.hh"
#include "instructions.hh"
#include "type_manager.hh"

class TextInstVisitor : public InstVisitor {
   protected:
    int                fTab;
    std::ostream*      fOut;
    bool               fFinishLine;
    std::string        fObjectAccess;
    StringTypeManager* fTypeManager;

    virtual void EndLine(char end_line = ';')
    {
        if (fFinishLine) {
            *fOut << end_line;
            tab(fTab, *fOut);
        }
    }
    
    // To be adapted in subclasses
    virtual void visitCond(ValueInst* cond)
    {
        cond->accept(this);
    }
  
   public:
    using InstVisitor::visit;

    TextInstVisitor(std::ostream* out, const std::string& object_access, int tab = 0)
        : fTab(tab), fOut(out), fFinishLine(true), fObjectAccess(object_access)
    {
        fTypeManager = new CStringTypeManager(xfloat(), "*");
    }

    TextInstVisitor(std::ostream* out, const std::string& object_access, const std::string& float_macro_name,
                    const std::string& ptr_postfix, int tab = 0)
        : fTab(tab), fOut(out), fFinishLine(true), fObjectAccess(object_access)
    {
        fTypeManager = new CStringTypeManager(float_macro_name, ptr_postfix);
    }

    TextInstVisitor(std::ostream* out, const std::string& object_access, StringTypeManager* manager, int tab = 0)
        : fTab(tab), fOut(out), fFinishLine(true), fObjectAccess(object_access), fTypeManager(manager)
    {
    }

    virtual ~TextInstVisitor() { delete fTypeManager; }

    void Tab(int n) { fTab = n; }

    virtual void visit(LabelInst* inst)
    {
        *fOut << inst->fLabel;
        tab(fTab, *fOut);
    }

    virtual void visit(DeclareVarInst* inst) { faustassert(false); }

    virtual void visit(RetInst* inst) { visitAux(inst, true); }

    virtual void visitAux(RetInst* inst, bool gen_empty)
    {
        if (inst->fResult) {
            *fOut << "return ";
            inst->fResult->accept(this);
            EndLine();
        } else if (gen_empty) {
            *fOut << "return";
            EndLine();
        }
    }

    virtual void visit(DropInst* inst)
    {
        if (inst->fResult) {
            inst->fResult->accept(this);
            EndLine();
        }
    }

    virtual void visit(DeclareFunInst* inst) { faustassert(false); }

    virtual void visit(NamedAddress* named) { *fOut << named->fName; }

    /*
     Indexed address can actually be values in an array or fields in a struct type
     */
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

    virtual void visit(LoadVarInst* inst) { inst->fAddress->accept(this); }

    virtual void visit(LoadVarAddressInst* inst) { faustassert(false); }

    virtual void visit(StoreVarInst* inst)
    {
        inst->fAddress->accept(this);
        *fOut << " = ";
        inst->fValue->accept(this);
        EndLine();
    }

    virtual void visit(FloatNumInst* inst) { *fOut << checkFloat(inst->fNum); }

    virtual void visit(FloatArrayNumInst* inst)
    {
        char sep = '{';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << checkFloat(inst->fNumTable[i]);
            sep = ',';
        }
        *fOut << '}';
    }

    virtual void visit(Int32NumInst* inst) { *fOut << inst->fNum; }

    virtual void visit(Int64NumInst* inst) { *fOut << inst->fNum; }

    virtual void visit(Int32ArrayNumInst* inst)
    {
        char sep = '{';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << inst->fNumTable[i];
            sep = ',';
        }
        *fOut << '}';
    }

    virtual void visit(BoolNumInst* inst) { *fOut << ((inst->fNum) ? "true" : "false"); }

    virtual void visit(DoubleNumInst* inst) { *fOut << checkDouble(inst->fNum); }

    virtual void visit(DoubleArrayNumInst* inst)
    {
        char sep = '{';
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            *fOut << sep << checkDouble(inst->fNumTable[i]);
            sep = ',';
        }
        *fOut << '}';
    }

    virtual void visit(BinopInst* inst)
    {
        *fOut << "(";
        inst->fInst1->accept(this);
        *fOut << " ";
        *fOut << gBinOpTable[inst->fOpcode]->fName;
        *fOut << " ";
        inst->fInst2->accept(this);
        *fOut << ")";
    }

    virtual void visit(::CastInst* inst) { faustassert(false); }

    virtual std::string generateFunName(const std::string& name)
    {
        // If function is actually a method (that is "xx::name"), then keep "xx::name" in gGlobalTable but print "name"
        size_t pos;
        if ((pos = name.find("::")) != std::string::npos) {
            return name.substr(pos + 2);  // After the "::"
        } else {
            return name;
        }
    }

    virtual void generateFunCallArgs(list<ValueInst*>::const_iterator beg,
                                     list<ValueInst*>::const_iterator end,
                                     size_t size)
    {
        list<ValueInst*>::const_iterator it = beg;
        size_t                           i  = 0;
        for (it = beg; it != end; it++, i++) {
            // Compile argument
            (*it)->accept(this);
            if (i < size - 1) *fOut << ", ";
        }
    }

    virtual void generateFunDefArgs(DeclareFunInst* inst)
    {
        *fOut << "(";
        
        list<NamedTyped*>::const_iterator it;
        
        size_t size = inst->fType->fArgsTypes.size(), i = 0;
        for (it = inst->fType->fArgsTypes.begin(); it != inst->fType->fArgsTypes.end(); it++, i++) {
            *fOut << fTypeManager->generateType((*it));
            if (i < size - 1) *fOut << ", ";
        }
    }

    virtual void generateFunDefBody(DeclareFunInst* inst)
    {
        if (inst->fCode->fCode.size() == 0) {
            *fOut << ");" << endl;  // Pure prototype
        } else {
            // Function body
            *fOut << ") {";
            fTab++;
            tab(fTab, *fOut);
            inst->fCode->accept(this);
            fTab--;
            back(1, *fOut);
            *fOut << "}";
            tab(fTab, *fOut);
        }
    }

    virtual void generateFunCall(FunCallInst* inst, const std::string& fun_name)
    {
        if (inst->fMethod) {
            list<ValueInst*>::const_iterator it = inst->fArgs.begin();
            // Compile object arg
            (*it)->accept(this);
            // Compile parameters
            *fOut << fObjectAccess << fun_name << "(";
            generateFunCallArgs(++it, inst->fArgs.end(), int(inst->fArgs.size()) - 1);
        } else {
            *fOut << fun_name << "(";
            // Compile parameters
            generateFunCallArgs(inst->fArgs.begin(), inst->fArgs.end(), int(inst->fArgs.size()));
        }
        *fOut << ")";
    }

    virtual void visit(FunCallInst* inst) { faustassert(false); }

    virtual void visit(Select2Inst* inst)
    {
        *fOut << "(";
        inst->fCond->accept(this);
        *fOut << " ? ";
        inst->fThen->accept(this);
        *fOut << " : ";
        inst->fElse->accept(this);
        *fOut << ")";
    }

    virtual void visit(IfInst* inst)
    {
        *fOut << "if (";
        visitCond(inst->fCond);
        *fOut << ") {";
        fTab++;
        tab(fTab, *fOut);
        inst->fThen->accept(this);
        fTab--;
        back(1, *fOut);
        if (inst->fElse->fCode.size() > 0) {
            *fOut << "} else {";
            fTab++;
            tab(fTab, *fOut);
            inst->fElse->accept(this);
            fTab--;
            back(1, *fOut);
            *fOut << "}";
        } else {
            *fOut << "}";
        }
        tab(fTab, *fOut);
    }

    virtual void visit(ForLoopInst* inst)
    {
        // Don't generate empty loops...
        if (inst->fCode->size() == 0) return;

        *fOut << "for (";
        fFinishLine = false;
        inst->fInit->accept(this);
        *fOut << "; ";
        inst->fEnd->accept(this);
        *fOut << "; ";
        inst->fIncrement->accept(this);
        fFinishLine = true;
        *fOut << ") {";
        fTab++;
        tab(fTab, *fOut);
        inst->fCode->accept(this);
        fTab--;
        back(1, *fOut);
        *fOut << "}";
        tab(fTab, *fOut);
    }

    virtual void visit(WhileLoopInst* inst)
    {
        *fOut << "while (";
        visitCond(inst->fCond);
        *fOut << ") {";
        fTab++;
        tab(fTab, *fOut);
        inst->fCode->accept(this);
        fTab--;
        back(1, *fOut);
        *fOut << "}";
        tab(fTab, *fOut);
    }

    virtual void visit(BlockInst* inst)
    {
        if (inst->fIndent) {
            *fOut << "{";
            fTab++;
            tab(fTab, *fOut);
        }
        RetInst* ret_inst = nullptr;
        for (auto& it : inst->fCode) {
            // Special case for "return" as last instruction
            if ((it == *inst->fCode.rbegin()) && (ret_inst = dynamic_cast<RetInst*>(it))) {
                visitAux(ret_inst, false);
            } else {
                it->accept(this);
            }
        }
        if (inst->fIndent) {
            fTab--;
            back(1, *fOut);
            *fOut << "}";
            tab(fTab, *fOut);
        }
    }

    virtual void visit(::SwitchInst* inst)
    {
        *fOut << "switch (";
        inst->fCond->accept(this);
        *fOut << ") {";
        fTab++;
        tab(fTab, *fOut);
        list<pair<int, BlockInst*> >::const_iterator it;
        for (it = inst->fCode.begin(); it != inst->fCode.end(); it++) {
            if ((*it).first == -1) {  // -1 used to code "default" case
                *fOut << "default: {";
            } else {
                *fOut << "case " << (*it).first << ": {";
            }
            fTab++;
            tab(fTab, *fOut);
            ((*it).second)->accept(this);
            if (!((*it).second)->hasReturn()) {
                *fOut << "break;";
            }
            fTab--;
            tab(fTab, *fOut);
            *fOut << "}";
            tab(fTab, *fOut);
        }
        fTab--;
        back(1, *fOut);
        *fOut << "}";
        tab(fTab, *fOut);
    }

    StringTypeManager* getTypeManager() { return fTypeManager; }
    
};

// Mathematical functions are declared as variables, they have to be generated before any other function (like
// 'faustpower')
struct sortDeclareFunctions {
    std::map<std::string, std::string> fMathLibTable;

    sortDeclareFunctions(const std::map<std::string, std::string>& table) : fMathLibTable(table) {}

    bool operator()(StatementInst* a, StatementInst* b)
    {
        DeclareFunInst* inst1 = dynamic_cast<DeclareFunInst*>(a);
        DeclareFunInst* inst2 = dynamic_cast<DeclareFunInst*>(b);

        if (inst1) {
            if (inst2) {
                if (fMathLibTable.find(inst1->fName) != fMathLibTable.end()) {
                    if (fMathLibTable.find(inst2->fName) != fMathLibTable.end()) {
                        return inst1->fName < inst2->fName;
                    } else {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

#endif
