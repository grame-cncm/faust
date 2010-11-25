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

#ifndef _C_INSTRUCTIONS_H
#define _C_INSTRUCTIONS_H

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

#include "instructions.hh"
#include "type_manager.hh"
#include "binop.hh"
#include "Text.hh"

#include <iostream>
#include <sstream>
#include <fstream>

class CInstVisitor : public InstVisitor, public StringTypeManager {

    private:

        int fTab;
        std::ostream* fOut;
        bool fFinishLine;
        static map <string, int> gGlobalTable;

    public:

        CInstVisitor(std::ostream* out, const string& structname, const string& prefix, int tab = 0)
            :fTab(tab), fOut(out), fFinishLine(true)
        {
            fTypeDirectTable[Typed::kObj] = prefix + structname;
            fTypeDirectTable[Typed::kObj_ptr] = prefix + structname + "*";
        }

        virtual ~CInstVisitor()
        {}

        void Tab(int n) {fTab = n;}

        void EndLine()
        {
            if (fFinishLine) {
                *fOut << ";";
                tab(fTab, *fOut);
            }
        }

        virtual void visit(AddMetaDeclareInst* inst)
        {
            *fOut << "interface->declare(" << "interface->uiInterface, " << "&dsp->" << inst->fZone <<", " << "\"" <<inst->fKey << "\"" << ", " <<  "\"" << inst->fValue << "\"" << ")"; EndLine();
        }

        virtual void visit(OpenboxInst* inst)
        {
            string name;
            switch (inst->fOrient) {
                case 0:
                    name = "interface->openVerticalBox"; break;
                case 1:
                    name = "interface->openHorizontalBox"; break;
                case 2:
                    name = "interface->openTabBox"; break;
            }
            *fOut << name << "(" << "interface->uiInterface, " << "\"" << inst->fName << "\"" << ")";
            EndLine();
        }

        virtual void visit(CloseboxInst* inst)
        {
            *fOut << "interface->closeBox(interface->uiInterface);"; tab(fTab, *fOut);
        }
        virtual void visit(AddButtonInst* inst)
        {
            if (inst->fType == AddButtonInst::kDefaultButton) {
                *fOut << "interface->addButton(" << "interface->uiInterface, " << "\"" << inst->fLabel << "\"" << ", " << "&dsp->" << inst->fZone << ")"; EndLine();
            } else {
                *fOut << "interface->addCheckButton(" << "interface->uiInterface, " << "\"" << inst->fLabel << "\"" << ", " << "&dsp->" << inst->fZone << ")"; EndLine();
            }
        }

        virtual void visit(AddSliderInst* inst)
        {
            string name;
            switch (inst->fType) {
                case AddSliderInst::kHorizontal:
                    name = "interface->addHorizontalSlider"; break;
                case AddSliderInst::kVertical:
                    name = "interface->addVerticalSlider"; break;
                case AddSliderInst::kNumEntry:
                    name = "interface->addNumEntry"; break;
            }
            if (strcmp(ifloat(), "float") == 0)
                *fOut << name << "(" << "interface->uiInterface, " << "\"" << inst->fLabel << "\"" << ", " << "&dsp->" << inst->fZone << ", " << checkFloat(inst->fInit) << ", " << checkFloat(inst->fMin) << ", " << checkFloat(inst->fMax) << ", " << checkFloat(inst->fStep) << ")";
            else
                *fOut << name << "(" << "interface->uiInterface, " << "\"" << inst->fLabel << "\"" << ", " << "&dsp->" << inst->fZone << ", " << inst->fInit << ", " << inst->fMin << ", " <<  inst->fMax << ", " << inst->fStep << ")";

            EndLine();
        }

        virtual void visit(AddBargraphInst* inst)
        {
            string name;
            switch (inst->fType) {
                case AddBargraphInst::kHorizontal:
                    name = "interface->addHorizontalBargraph"; break;
                case AddBargraphInst::kVertical:
                    name = "interface->addVerticalBargraph"; break;
            }
            if (strcmp(ifloat(), "float") == 0)
                *fOut << name << "(" << "interface->uiInterface, " << "\"" << inst->fLabel << "\"" << ", " << "&dsp->" << inst->fZone << ", "<< checkFloat(inst->fMin) << ", " << checkFloat(inst->fMax) << ")";
            else
                *fOut << name << "(" << "interface->uiInterface, " << "\"" << inst->fLabel << "\"" << ", " << "&dsp->" << inst->fZone << ", "<< inst->fMin << ", " << inst->fMax << ")";
            EndLine();
        }

        virtual void visit(LabelInst* inst)
        {
            *fOut << inst->fLabel;
            tab(fTab, *fOut);
        }

        virtual void visit(DeclareVarInst* inst)
        {
            if (inst->fAddress->getAccess() & Address::kGlobal) {
                if (gGlobalTable.find(inst->fAddress->getName()) == gGlobalTable.end()) {
                    // If global is not defined
                    gGlobalTable[inst->fAddress->getName()] = 1;
                } else {
                    return;
                }
            }

            if (inst->fAddress->getAccess() & Address::kStaticStruct) {
                 *fOut << "static ";
            }

            if (inst->fAddress->getAccess() & Address::kVolatile) {
                 *fOut << "volatile ";
            }

            if (inst->fValue) {
                *fOut << generateType(inst->fTyped, inst->fAddress->getName()) << " = "; inst->fValue->accept(this); EndLine();
            } else {
                *fOut << generateType(inst->fTyped, inst->fAddress->getName()); EndLine();
            }
        }

        virtual void visit(RetInst* inst)
        {
            if (inst->fResult) {
                *fOut << "return "; inst->fResult->accept(this); EndLine();
            }
        }

        virtual void visit(DropInst* inst)
        {
            if (inst->fResult) {
                inst->fResult->accept(this); EndLine();
            }
        }

        virtual void visit(DeclareFunInst* inst)
        {
            if (gGlobalTable.find(inst->fName) != gGlobalTable.end())
                return;  // already declared

            // Defined as macro in the architecture file...
            if (inst->fName == "min" || inst->fName == "max") {
                return;
            }

            // Prototype
            if (inst->fType->fAttribute & FunTyped::kLocal)
                 *fOut << "static inline ";

            *fOut << generateType(inst->fType->fResult, inst->fName);
            *fOut << "(";
            list<NamedTyped*>::const_iterator it;
            int size = inst->fType->fArgsTypes.size(), i = 0;
            for (it = inst->fType->fArgsTypes.begin(); it != inst->fType->fArgsTypes.end(); it++, i++) {
                *fOut << generateType((*it));
                if (i < size - 1) *fOut << ", ";
            }

            if (inst->fCode->fCode.size() == 0) {
                *fOut << ");" << endl;  // Pure prototype
            } else {
                // Function body
                *fOut << ") {";
                    fTab++;
                    tab(fTab, *fOut);
                    inst->fCode->accept(this);
                    fTab--;
                    tab(fTab, *fOut);
                *fOut << "}";
                tab(fTab, *fOut);
            }

            gGlobalTable[inst->fName] = 1;
        }

        virtual void visit(LoadVarInst* inst)
        {
            NamedAddress* named = dynamic_cast<NamedAddress*>(inst->fAddress);
            IndexedAddress* indexed = dynamic_cast<IndexedAddress*>(inst->fAddress);
            string access = "";

            if (inst->fAddress->getAccess() & Address::kStruct)
                access = "dsp->";

            if (named) {
                *fOut << access << named->getName();
            } else {
                *fOut << access << indexed->getName() << "[";
                indexed->fIndex->accept(this);
                *fOut << "]";
            }
        }

        virtual void visit(LoadVarAddressInst* inst)
        {
            NamedAddress* named = dynamic_cast<NamedAddress*>(inst->fAddress);
            IndexedAddress* indexed = dynamic_cast<IndexedAddress*>(inst->fAddress);
            string access = "&";

            if (inst->fAddress->getAccess() & Address::kStruct)
                access += "dsp->";

            if (named) {
                *fOut << access << named->getName();
            } else {
                *fOut << access << indexed->getName() << "[";
                indexed->fIndex->accept(this);
                *fOut << "]";
            }
        }

        virtual void visit(StoreVarInst* inst)
        {
            NamedAddress* named = dynamic_cast<NamedAddress*>(inst->fAddress);
            IndexedAddress* indexed = dynamic_cast<IndexedAddress*>(inst->fAddress);
            string access = "";

            if (inst->fAddress->getAccess() & Address::kStruct)
                access = "dsp->";

            if (named) {
                *fOut << access << named->getName() << " = ";
            } else {
                *fOut << access << indexed->getName() << "[";
                indexed->fIndex->accept(this);
                *fOut << "] = ";
            }
            assert( inst->fValue);
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
            assert(inst->fInst1);
            inst->fInst1->accept(this);
            *fOut << " ";
            *fOut << gBinOpTable[inst->fOpcode]->fName;
            *fOut << " ";
            assert(inst->fInst2);
            inst->fInst2->accept(this);
            *fOut << ")";
        }

        virtual void visit(CastNumInst* inst)
        {
            *fOut << "(" << generateType(inst->fTyped) << ")";
            inst->fInst->accept(this);
        }

        void generateFaustPower(ValueInst* arg1, ValueInst* arg2)
        {}

         void generateFaustPowerAux(ValueInst* arg1, int arg2)
        {}

        virtual void visit(FunCallInst* inst)
        {
            if (inst->fName == "faustpower") {
                list<ValueInst*>::const_iterator it = inst->fArgs.begin();
                ValueInst* arg1 = (*it);
                it++;
                ValueInst* arg2 = (*it);
                generateFaustPower(arg1, arg2);
                return;
            }

            *fOut << inst->fName << "(";
            list<ValueInst*>::const_iterator it;

            int size = inst->fArgs.size(), i = 0;
            for (it = inst->fArgs.begin(); it != inst->fArgs.end(); it++, i++) {
                // Compile argument
                (*it)->accept(this);
                if (i < size - 1) *fOut << ", ";
            }
            *fOut << ")";
        }

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

        virtual void visit(SwitchInst* inst)
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
                        *fOut << "break;";
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
