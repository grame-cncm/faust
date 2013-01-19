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

#ifndef _TEXT_INSTRUCTIONS_H
#define _TEXT_INSTRUCTIONS_H

using namespace std;

#include <string>
#include <list>
#include <set>
#include <map>

#include "instructions.hh"
#include "type_manager.hh"
#include "binop.hh"
#include "Text.hh"
#include "global.hh"

#include <iostream>
#include <sstream>
#include <fstream>

class TextInstVisitor : public InstVisitor {

    protected:

        int fTab;
        std::ostream* fOut;
        bool fFinishLine;

    public:

        TextInstVisitor(std::ostream* out, int tab = 0)
            :fTab(tab), fOut(out), fFinishLine(true)
        {}

        virtual ~TextInstVisitor()
        {}

        void Tab(int n) { fTab = n; }

        void EndLine()
        {
            if (fFinishLine) {
                *fOut << ";";
                tab(fTab, *fOut);
            }
        }

        virtual void visit(AddMetaDeclareInst* inst) { assert(false); }
        virtual void visit(OpenboxInst* inst) { assert(false); }
        virtual void visit(CloseboxInst* inst) { assert(false); }
        virtual void visit(AddButtonInst* inst) { assert(false); }
        virtual void visit(AddSliderInst* inst) { assert(false); }
        virtual void visit(AddBargraphInst* inst) { assert(false); }
      
        virtual void visit(LabelInst* inst)
        {
            *fOut << inst->fLabel;
            tab(fTab, *fOut);
        }

        virtual void visit(DeclareVarInst* inst) { assert(false); }

        virtual void visit(RetInst* inst)
        {
            if (inst->fResult) {
                *fOut << "return ";
                inst->fResult->accept(this); 
            } else {
                *fOut << "return";
            }
            EndLine();
        }

        virtual void visit(DropInst* inst)
        {
            if (inst->fResult) {
                inst->fResult->accept(this); 
                EndLine();
            }
        }

        virtual void visit(DeclareFunInst* inst) { assert(false); }
           
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
            inst->fAddress->accept(this);
        }
     
        virtual void visit(LoadVarAddressInst* inst) { assert(false); }
       
        virtual void visit(StoreVarInst* inst)
        {
            inst->fAddress->accept(this);
            *fOut << " = ";
            inst->fValue->accept(this);
            EndLine();
        }

        virtual void visit(FloatNumInst* inst)
        {
            *fOut << checkFloat(inst->fNum);
        }

        virtual void visit(IntNumInst* inst)
        {
            *fOut << inst->fNum;
        }

        virtual void visit(BoolNumInst* inst)
        {
            *fOut << inst->fNum;
        }

        virtual void visit(DoubleNumInst* inst)
        {
            *fOut << inst->fNum;
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

        virtual void visit(CastNumInst* inst) { assert(false); }
        
        void compileArgs(list<ValueInst*>::const_iterator beg, list<ValueInst*>::const_iterator end, int size)
        {   
            list<ValueInst*>::const_iterator it = beg;
            int i = 0;
            for (it = beg; it != end; it++, i++) {
                // Compile argument
                (*it)->accept(this);
                if (i < size - 1) *fOut << ", ";
            }
        }

        virtual void visit(FunCallInst* inst) { assert(false); }
           
        virtual void visit(Select2Inst* inst)
        {
            *fOut << "(";
            inst->fCond->accept(this);
            *fOut << "?";
            inst->fThen->accept(this);
            *fOut << ":";
            inst->fElse->accept(this);
            *fOut << ")";
        }

        virtual void visit(IfInst* inst)
        {
            *fOut << "if ";
            inst->fCond->accept(this);
            *fOut << " {";
                fTab++;
                tab(fTab, *fOut);
                inst->fThen->accept(this);
                fTab--;
                tab(fTab, *fOut);
            if (inst->fElse->fCode.size() > 0) {
                *fOut << "} else {";
                    fTab++;
                    tab(fTab, *fOut);
                    inst->fElse->accept(this);
                    fTab--;
                    tab(fTab, *fOut);
                *fOut << "}";
            } else {
                *fOut << "}";
            }
            tab(fTab, *fOut);
        }

        virtual void visit(ForLoopInst* inst)
        {
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
                tab(fTab, *fOut);
            *fOut << "}";
            tab(fTab, *fOut);
        }

        virtual void visit(WhileLoopInst* inst)
        {
            *fOut << "while ("; inst->fCond->accept(this); *fOut << ") {";
                fTab++;
                tab(fTab, *fOut);
                inst->fCode->accept(this);
                fTab--;
                tab(fTab, *fOut);
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
            list<StatementInst*>::const_iterator it;
            for (it = inst->fCode.begin(); it != inst->fCode.end(); it++) {
                (*it)->accept(this);
            }
            if (inst->fIndent) {
                fTab--;
                tab(fTab, *fOut);
                *fOut << "}";
                tab(fTab, *fOut);
            }
        }

        virtual void visit(::SwitchInst* inst)
        {
            *fOut << "switch ("; inst->fCond->accept(this); *fOut << ") {";
                fTab++;
                tab(fTab, *fOut);
                list<pair <int, BlockInst*> >::const_iterator it;
                for (it = inst->fCode.begin(); it != inst->fCode.end(); it++) {
                    if ((*it).first == -1) { // -1 used to code "default" case
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
                tab(fTab, *fOut);
            *fOut << "}";
            tab(fTab, *fOut);
        }

};

#endif
