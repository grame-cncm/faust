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

#pragma once

using namespace std;

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
    int fFunCall;

    map<string, bool> gFunctionSymbolTable;

   public:
    using DispatchVisitor::visit;

    InstComplexityVisitor()
        : fLoad(0), fStore(0), fBinop(0), fMathop(0), fNumbers(0), fDeclare(0), fCast(0), fSelect(0), fLoop(0), fFunCall(0)
    {
        // Mark all math.h functions as generated...
        gFunctionSymbolTable["abs"] = true;

        gFunctionSymbolTable["max_i"] = true;
        gFunctionSymbolTable["min_i"] = true;

        gFunctionSymbolTable["max_f"] = true;
        gFunctionSymbolTable["min_f"] = true;

        // Float version
        gFunctionSymbolTable["absf"]       = true;
        gFunctionSymbolTable["fabsf"]      = true;
        gFunctionSymbolTable["acosf"]      = true;
        gFunctionSymbolTable["asinf"]      = true;
        gFunctionSymbolTable["atanf"]      = true;
        gFunctionSymbolTable["atan2f"]     = true;
        gFunctionSymbolTable["ceilf"]      = true;
        gFunctionSymbolTable["cosf"]       = true;
        gFunctionSymbolTable["expf"]       = true;
        gFunctionSymbolTable["exp10f"]     = true;
        gFunctionSymbolTable["floorf"]     = true;
        gFunctionSymbolTable["fmodf"]      = true;
        gFunctionSymbolTable["logf"]       = true;
        gFunctionSymbolTable["log10f"]     = true;
        gFunctionSymbolTable["powf"]       = true;
        gFunctionSymbolTable["remainderf"] = true;
        gFunctionSymbolTable["roundf"]     = true;
        gFunctionSymbolTable["sinf"]       = true;
        gFunctionSymbolTable["sqrtf"]      = true;
        gFunctionSymbolTable["tanf"]       = true;
    }
    virtual ~InstComplexityVisitor() {}

    virtual void visit(Printable* inst) {}

    virtual void visit(DeclareVarInst* inst)
    {
        fDeclare++;
        DispatchVisitor::visit(inst);
    }

    virtual void visit(LoadVarInst* inst) { fLoad++; }
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
        DispatchVisitor::visit(inst);
    }
    virtual void visit(CastInst* inst)
    {
        fCast++;
        DispatchVisitor::visit(inst);
    }

    // Needs a cost table for a set of standard functions?
    virtual void visit(FunCallInst* inst)
    {
        fFunCall++;
        if (gFunctionSymbolTable.find(inst->fName) != gFunctionSymbolTable.end()) {
            fMathop++;
        }
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

    void dump(ostream* dst)
    {
        *dst << "Instructions complexity : ";
        *dst << "Load = " << fLoad << " Store = " << fStore << " Binop = " << fBinop;
        *dst << " Mathop = " << fMathop << " Numbers = " << fNumbers << " Declare = " << fDeclare;
        *dst << " Cast = " << fCast << " Select = " << fSelect << " Loop = " << fLoop << " FunCall = " << fFunCall << "\n";
    }

    void operator+(const InstComplexityVisitor& visitor)
    {
        fLoad += visitor.fLoad;
        fStore += visitor.fStore;
        fBinop += visitor.fBinop;
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
