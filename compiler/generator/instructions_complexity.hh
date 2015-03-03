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

#ifndef _INSTRUCTIONS_COMPLEXITY_H
#define _INSTRUCTIONS_COMPLEXITY_H

using namespace std;

#include <string>
#include <list>
#include <set>
#include <map>
#include <vector>

#include <iostream>
#include <sstream>
#include <assert.h>

#include "instructions.hh"

class InstComplexityVisitor : public InstVisitor {

    private:

        int fLoad;
        int fStore;
        int fBinop;
        int fNumbers;
        int fDeclare;
        int fCast;
        int fSelect;
        int fLoop;

    public:

        InstComplexityVisitor()
            :fLoad(0), fStore(0), fBinop(0), fNumbers(0);
            fDeclare(0), fCast(0), fSelect(0), fLoop(0)
        {}
        virtual ~InstComplexityVisitor()
        {}

        virtual void visit(Printable* inst) {}

        virtual void visit(DeclareVarInst* inst) { fDeclare++; inst->fValue->accept(this); }
        virtual void visit(DeclareFunInst* inst) {}

        virtual void visit(LoadVarInst* inst) { fLoad++; }
        virtual void visit(StoreVarInst* inst) { fStore++; inst->fValue->accept(this);}

        virtual void visit(FloatNumInst* inst) { fNumbers++; }
        virtual void visit(IntNumInst* inst) { fNumbers++; }
        virtual void visit(BoolNumInst* inst) { fNumbers++; }
        virtual void visit(DoubleNumInst* inst) { fNumbers++; }

        virtual void visit(BinopInst* inst) { fBinop++; inst->fInst1->accept(this); inst->fInst2->accept(this);}
        virtual void visit(CastNumInst* inst) { fCast++; inst->fInst->accept(this); }

        virtual void visit(FunCallInst* inst) {}    // Needs a cost table for a set of standard functions?

        virtual void visit(IfInst* inst)
        {
            fSelect++;
            inst->fCond->accept(this);

            // Max of the 2 branch cast
            InstComplexityVisitor then_branch
            inst->fThen->accept(&then_branch);

            InstComplexityVisitor else_branch
            inst->fThen->accept(&else_branch);

            if (then_branch.cost() > else_branch.cost()) {
                fLoad += then_branch.fLoad;
                fStore += then_branch.fStore;
                fBinop += then_branch.fBinop;
                fNumbers += then_branch.fNumbers;
                fDeclare += then_branch.fDeclare;
                fCast += then_branch.fCast;
                fSelect += then_branch.fSelect;
                fLoop += then_branch.fLoop;
            } else {
                fLoad += else_branch.fLoad;
                fStore += else_branch.fStore;
                fBinop += else_branch.fBinop;
                fNumbers += else_branch.fNumbers;
                fDeclare += else_branch.fDeclare;
                fCast += else_branch.fCast;
                fSelect += else_branch.fSelect;
                fLoop += else_branch.fLoop;
            }
        }

        virtual void visit(LoopInst* inst)
        {
            fLoop++;

            std::list<Inst*>::const_iterator it;
            for (it = inst->fInstructions.begin(); it != inst->fInstructions.end(); it++) {
                (*it)->accept(this);
            }
        }

        int cost()
        {
            // Un polynome basé sur toutes les valeurs mesurées
            return 0;
        }

};

#endif
