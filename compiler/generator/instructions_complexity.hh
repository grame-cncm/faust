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

class InstComplexityVisitor : public DispatchVisitor {
   private:
    int fLoad;
    int fStore;
    int fBinop;
    int fMathop;
    int fNumbers;
    int fDeclare;
    int fCast;
    int fSelect;
    int fLoop;
  
    std::map<std::string, int> gFunctionSymbolTable;
    std::map<std::string, int> gBinopSymbolTable;

   public:
    using DispatchVisitor::visit;

    InstComplexityVisitor()
        : fLoad(0),
          fStore(0),
          fBinop(0),
          fMathop(0),
          fNumbers(0),
          fDeclare(0),
          fCast(0),
          fSelect(0),
          fLoop(0)
    {}
    
    virtual ~InstComplexityVisitor() {}

    virtual void visit(Printable* inst) {}

    virtual void visit(DeclareVarInst* inst)
    {
        fDeclare++;
        DispatchVisitor::visit(inst);
    }

    virtual void visit(LoadVarInst* inst)
    {
        fLoad++;
        DispatchVisitor::visit(inst);
    }
    virtual void visit(StoreVarInst* inst)
    {
        fStore++;
        DispatchVisitor::visit(inst);
    }

    virtual void visit(FloatNumInst* inst) { fNumbers++; }
    virtual void visit(Int32NumInst* inst) { fNumbers++; }
    virtual void visit(BoolNumInst* inst) { fNumbers++; }
    virtual void visit(DoubleNumInst* inst) { fNumbers++; }

    virtual void visit(BinopInst* inst)
    {
        fBinop++;
        Typed::VarType type1 = TypingVisitor::getType(inst->fInst1);
        Typed::VarType type2 = TypingVisitor::getType(inst->fInst2);
        if (isRealType(type1) || isRealType(type2)) {
            gBinopSymbolTable["Real(" + std::string(gBinOpTable[inst->fOpcode]->fName) + ")"]++;
        } else {
            gBinopSymbolTable["Int(" + std::string(gBinOpTable[inst->fOpcode]->fName) + ")"]++;
        }
        DispatchVisitor::visit(inst);
    }
    virtual void visit(CastInst* inst)
    {
        fCast++;
        DispatchVisitor::visit(inst);
    }
    virtual void visit(Select2Inst* inst)
    {
        fSelect++;
        DispatchVisitor::visit(inst);
    }

    // Needs a cost table for a set of standard functions?
    virtual void visit(FunCallInst* inst)
    {
        gFunctionSymbolTable[inst->fName]++;
        fMathop++;
        DispatchVisitor::visit(inst);
    }

    virtual void visit(IfInst* inst)
    {
        fSelect++;
        inst->fCond->accept(this);

        // Max of the 2 branches
        InstComplexityVisitor then_branch;
        inst->fThen->accept(&then_branch);

        InstComplexityVisitor else_branch;
        inst->fThen->accept(&else_branch);

        // Takes the max of both then/else branches
        if (then_branch.cost() > else_branch.cost()) {
            fLoad += then_branch.fLoad;
            fStore += then_branch.fStore;
            fBinop += then_branch.fBinop;
            fMathop += then_branch.fMathop;
            fNumbers += then_branch.fNumbers;
            fDeclare += then_branch.fDeclare;
            fCast += then_branch.fCast;
            fSelect += then_branch.fSelect;
            fLoop += then_branch.fLoop;
        } else {
            fLoad += else_branch.fLoad;
            fStore += else_branch.fStore;
            fBinop += else_branch.fBinop;
            fMathop += else_branch.fMathop;
            fNumbers += else_branch.fNumbers;
            fDeclare += else_branch.fDeclare;
            fCast += else_branch.fCast;
            fSelect += else_branch.fSelect;
            fLoop += else_branch.fLoop;
        }
    }

    virtual void visit(ForLoopInst* inst)
    {
        fLoop++;
        DispatchVisitor::visit(inst);
    }

    void dump(std::ostream* dst)
    {
        *dst << "Instructions complexity : ";
        *dst << "Load = " << fLoad << " Store = " << fStore;
        *dst << " Binop = " << fBinop;
        if (fBinop > 0) {
            *dst << " [ ";
            for (const auto& it : gBinopSymbolTable) {
                if (it.second > 0) {
                    *dst << "{ " << it.first << " = " << it.second << " } ";
                }
            }
            *dst << "]";
        }
        *dst << " Mathop = " << fMathop;
        if (fMathop > 0) {
            *dst << " [ ";
            for (const auto& it : gFunctionSymbolTable) {
                if (it.second > 0) {
                    *dst << "{ " << it.first << " = " << it.second << " } ";
                }
            }
            *dst << "]";
        }
        *dst << " Numbers = " << fNumbers << " Declare = " << fDeclare;
        *dst << " Cast = " << fCast << " Select = " << fSelect << " Loop = " << fLoop << "\n";
    }

    void operator+(const InstComplexityVisitor& visitor)
    {
        fLoad += visitor.fLoad;
        fStore += visitor.fStore;
        fBinop += visitor.fBinop;
        fMathop += visitor.fMathop;
        fNumbers += visitor.fNumbers;
        fDeclare += visitor.fDeclare;
        fCast += visitor.fCast;
        fSelect += visitor.fSelect;
        fLoop += visitor.fLoop;
    }

    int cost()
    {
        // A polynom based on measured values
        return 0;
    }
};

#endif
