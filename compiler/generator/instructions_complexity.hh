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

#ifndef _INSTRUCTIONS_COMPLEXITY_H
#define _INSTRUCTIONS_COMPLEXITY_H

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

    map<string, int> gFunctionSymbolTable;

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
          fLoop(0),
          fFunCall(0)
    {
        gFunctionSymbolTable["abs"] = 0;

        gFunctionSymbolTable["max_i"] = 0;
        gFunctionSymbolTable["min_i"] = 0;

        gFunctionSymbolTable["max_f"] = 0;
        gFunctionSymbolTable["min_f"] = 0;

        // Float version
        gFunctionSymbolTable["absf"]       = 0;
        gFunctionSymbolTable["fabsf"]      = 0;
        gFunctionSymbolTable["acosf"]      = 0;
        gFunctionSymbolTable["asinf"]      = 0;
        gFunctionSymbolTable["atanf"]      = 0;
        gFunctionSymbolTable["atan2f"]     = 0;
        gFunctionSymbolTable["ceilf"]      = 0;
        gFunctionSymbolTable["cosf"]       = 0;
        gFunctionSymbolTable["expf"]       = 0;
        gFunctionSymbolTable["exp10f"]     = 0;
        gFunctionSymbolTable["floorf"]     = 0;
        gFunctionSymbolTable["fmodf"]      = 0;
        gFunctionSymbolTable["logf"]       = 0;
        gFunctionSymbolTable["log10f"]     = 0;
        gFunctionSymbolTable["powf"]       = 0;
        gFunctionSymbolTable["remainderf"] = 0;
        gFunctionSymbolTable["roundf"]     = 0;
        gFunctionSymbolTable["sinf"]       = 0;
        gFunctionSymbolTable["sqrtf"]      = 0;
        gFunctionSymbolTable["tanf"]       = 0;
        
        // Double version
        gFunctionSymbolTable["abs"]       = 0;
        gFunctionSymbolTable["fabs"]      = 0;
        gFunctionSymbolTable["acos"]      = 0;
        gFunctionSymbolTable["asin"]      = 0;
        gFunctionSymbolTable["atan"]      = 0;
        gFunctionSymbolTable["atan2"]     = 0;
        gFunctionSymbolTable["ceil"]      = 0;
        gFunctionSymbolTable["cos"]       = 0;
        gFunctionSymbolTable["exp"]       = 0;
        gFunctionSymbolTable["exp10"]     = 0;
        gFunctionSymbolTable["floor"]     = 0;
        gFunctionSymbolTable["fmod"]      = 0;
        gFunctionSymbolTable["log"]       = 0;
        gFunctionSymbolTable["log10"]     = 0;
        gFunctionSymbolTable["pow"]       = 0;
        gFunctionSymbolTable["remainder"] = 0;
        gFunctionSymbolTable["round"]     = 0;
        gFunctionSymbolTable["sin"]       = 0;
        gFunctionSymbolTable["sqrt"]      = 0;
        gFunctionSymbolTable["tan"]       = 0;
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
            gFunctionSymbolTable[inst->fName]++;
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
        *dst << " Mathop = " << fMathop;
        if (fMathop > 0) {
            *dst << " [ ";
            for (const auto& it : gFunctionSymbolTable) {
                if (it.second > 0) {
                    *dst << it.first << " = " << it.second << " ";
                }
            }
            *dst << "]";
        }
        *dst << " Numbers = " << fNumbers << " Declare = " << fDeclare;
        *dst << " Cast = " << fCast << " Select = " << fSelect << " Loop = " << fLoop << " FunCall = " << fFunCall
             << "\n";
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
