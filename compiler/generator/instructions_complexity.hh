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

#ifndef _INSTRUCTIONS_COMPLEXITY_H
#define _INSTRUCTIONS_COMPLEXITY_H

#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "exception.hh"
#include "instructions.hh"
#include "typing_instructions.hh"
#include "faust/gui/JSONUI.h"

class InstComplexityVisitor : public DispatchVisitor {
   private:
    InstComplexity fIComp;
 
   public:
    using DispatchVisitor::visit;

    InstComplexityVisitor()
    {}
    
    virtual ~InstComplexityVisitor() {}

    virtual void visit(Printable* inst) {}

    virtual void visit(DeclareVarInst* inst)
    {
        fIComp.fDeclare++;
        DispatchVisitor::visit(inst);
    }

    virtual void visit(LoadVarInst* inst)
    {
        fIComp.fLoad++;
        DispatchVisitor::visit(inst);
    }
    virtual void visit(StoreVarInst* inst)
    {
        fIComp.fStore++;
        DispatchVisitor::visit(inst);
    }

    virtual void visit(FloatNumInst* inst) { fIComp.fNumbers++; }
    virtual void visit(Int32NumInst* inst) { fIComp.fNumbers++; }
    virtual void visit(BoolNumInst* inst) { fIComp.fNumbers++; }
    virtual void visit(DoubleNumInst* inst) { fIComp.fNumbers++; }

    virtual void visit(BinopInst* inst)
    {
        fIComp.fBinop++;
        Typed::VarType type1 = TypingVisitor::getType(inst->fInst1);
        Typed::VarType type2 = TypingVisitor::getType(inst->fInst2);
        if (isRealType(type1) || isRealType(type2)) {
            fIComp.fBinopSymbolTable["Real(" + std::string(gBinOpTable[inst->fOpcode]->fName) + ")"]++;
        } else {
            fIComp.fBinopSymbolTable["Int(" + std::string(gBinOpTable[inst->fOpcode]->fName) + ")"]++;
        }
        DispatchVisitor::visit(inst);
    }
    virtual void visit(CastInst* inst)
    {
        fIComp.fCast++;
        DispatchVisitor::visit(inst);
    }
    virtual void visit(Select2Inst* inst)
    {
        fIComp.fSelect++;
        DispatchVisitor::visit(inst);
    }

    // Needs a cost table for a set of standard functions?
    virtual void visit(FunCallInst* inst)
    {
        fIComp.fFunctionSymbolTable[inst->fName]++;
        fIComp.fMathop++;
        DispatchVisitor::visit(inst);
    }

    virtual void visit(IfInst* inst)
    {
        fIComp.fSelect++;
        inst->fCond->accept(this);

        // Max of the 2 branches
        InstComplexityVisitor then_branch;
        inst->fThen->accept(&then_branch);

        InstComplexityVisitor else_branch;
        inst->fThen->accept(&else_branch);

        // Takes the max of both then/else branches
        if (then_branch.cost() > else_branch.cost()) {
            fIComp = fIComp + then_branch.fIComp;
        } else {
            fIComp = fIComp + else_branch.fIComp;
        }
    }

    virtual void visit(ForLoopInst* inst)
    {
        fIComp.fLoop++;
        DispatchVisitor::visit(inst);
    }

    void dump(std::ostream* dst)
    {
        *dst << "Instructions complexity : ";
        *dst << "Load = " << fIComp.fLoad << " Store = " << fIComp.fStore;
        *dst << " Binop = " << fIComp.fBinop;
        if (fIComp.fBinop > 0) {
            *dst << " [ ";
            for (const auto& it : fIComp.fBinopSymbolTable) {
                if (it.second > 0) {
                    *dst << "{ " << it.first << " = " << it.second << " } ";
                }
            }
            *dst << "]";
        }
        *dst << " Mathop = " << fIComp.fMathop;
        if (fIComp.fMathop > 0) {
            *dst << " [ ";
            for (const auto& it : fIComp.fFunctionSymbolTable) {
                if (it.second > 0) {
                    *dst << "{ " << it.first << " = " << it.second << " } ";
                }
            }
            *dst << "]";
        }
        *dst << " Numbers = " << fIComp.fNumbers << " Declare = " << fIComp.fDeclare;
        *dst << " Cast = " << fIComp.fCast << " Select = " << fIComp.fSelect << " Loop = " << fIComp.fLoop << "\n";
    }

    int cost()
    {
        // A polynom based on measured values
        return 0;
    }
    
    InstComplexity getInstComplexity() { return fIComp; }
};

#endif
