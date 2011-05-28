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

#ifndef _JAVA_INSTRUCTIONS_H
#define _JAVA_INSTRUCTIONS_H

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



class JAVAInstVisitor : public InstVisitor, public StringTypeManager {

    private:

        int fTab;
        std::ostream* fOut;
        bool fFinishLine;

    public:

        JAVAInstVisitor(std::ostream* out, int tab = 0)
          :StringTypeManager(ifloat(), "[]"), fTab(tab), fOut(out), fFinishLine(true)
        {}

        virtual ~JAVAInstVisitor()
        {}

        void Tab(int n) {fTab = n;}

        void EndLine()
        {
            if (fFinishLine) {
                *fOut << ";";
                tab(fTab, *fOut);
            }
        }

        string createVarAccess(string varname){
          return "new FaustVarAccess(){public void set(float val){" + varname + "=val;}" +
                 "public float get(){return (float)" + varname + ";}}";
        }

        virtual void visit(AddMetaDeclareInst* inst)
        {
            // TODO
            // Special case
            if (inst->fZone == "0") {
                *fOut << "// ui_interface.declare(" << inst->fZone <<", " << inst->fKey << ", " <<  inst->fValue << ")";
            } else {
                *fOut << "// ui_interface.declare(" << "&" << inst->fZone <<", " << inst->fKey << ", " <<  inst->fValue << ")";
            }
            EndLine();
        }

        virtual void visit(OpenboxInst* inst)
        {
            string name;
            switch (inst->fOrient) {
                case 0:
                    name = "ui_interface.openVerticalBox"; break;
                case 1:
                    name = "ui_interface.openHorizontalBox"; break;
                case 2:
                    name = "ui_interface.openTabBox"; break;
            }
            *fOut << name << "(" << "\"" << inst->fName << "\"" << ")";
            EndLine();
        }

        virtual void visit(CloseboxInst* inst)
        {
            *fOut << "ui_interface.closeBox();"; tab(fTab, *fOut);
        }
        virtual void visit(AddButtonInst* inst)
        {
            if (inst->fType == AddButtonInst::kDefaultButton) {
                *fOut << "ui_interface.addButton(" << "\"" << inst->fLabel << "\"" << ", " << createVarAccess(inst->fZone) << ")"; EndLine();
            } else {
                *fOut << "ui_interface.addCheckButton(" << "\"" << inst->fLabel << "\"" << ", " << createVarAccess(inst->fZone) << ")"; EndLine();
            }
        }

        virtual void visit(AddSliderInst* inst)
        {
            string name;
            switch (inst->fType) {
                case AddSliderInst::kHorizontal:
                    name = "ui_interface.addHorizontalSlider"; break;
                case AddSliderInst::kVertical:
                    name = "ui_interface.addVerticalSlider"; break;
                case AddSliderInst::kNumEntry:
                    name = "ui_interface.addNumEntry"; break;
            }
            *fOut << name << "(" << "\"" << inst->fLabel << "\"" << ", " << createVarAccess(inst->fZone) << ", " << checkFloat(inst->fInit) << ", " << checkFloat(inst->fMin) << ", " << checkFloat(inst->fMax) << ", " << checkFloat(inst->fStep) << ")";
            EndLine();
        }

        virtual void visit(AddBargraphInst* inst)
        {
            string name;
            switch (inst->fType) {
                case AddBargraphInst::kHorizontal:
                    name = "ui_interface.addHorizontalBargraph"; break;
                case AddBargraphInst::kVertical:
                    name = "ui_interface.addVerticalBargraph"; break;
            }
            *fOut << name << "(" << "\"" << inst->fLabel << "\"" << ", " << createVarAccess(inst->fZone) << ", "<< checkFloat(inst->fMin) << ", " << checkFloat(inst->fMax) << ")";
            EndLine();
        }

        virtual void visit(LabelInst* inst)
        {
            *fOut << inst->fLabel;
            tab(fTab, *fOut);
        }

        virtual void visit(DeclareVarInst* inst)
        {
            if (inst->fAddress->getAccess() & Address::kVolatile) {
                 *fOut << "volatile ";
            }

            if (inst->fValue) {
                *fOut << generateType(inst->fTyped, inst->fAddress->getName()) << " = "; inst->fValue->accept(this); EndLine();
            } else {
              ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fTyped);
              if (array_typed && array_typed->fSize>1){
                string type = fTypeDirectTable[array_typed->fType->getType()];
                *fOut << "private " << type << " " << inst->fAddress->getName() << "[]";
                *fOut << " = new " << type << "[" << array_typed->fSize << "]";
              }else
                *fOut << "private " << generateType(inst->fTyped, inst->fAddress->getName());
              EndLine();
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
            // Prototype
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
        }

        virtual void visit(LoadVarInst* inst)
        {
            NamedAddress* named = dynamic_cast< NamedAddress*>(inst->fAddress);
            IndexedAddress* indexed = dynamic_cast< IndexedAddress*>(inst->fAddress);

            if (named) {
                *fOut << named->getName();
            } else {
                *fOut << indexed->getName() << "[";
                indexed->fIndex->accept(this);
                *fOut << "]";
            }
        }

        // TODO. This does not work in java.
        virtual void visit(LoadVarAddressInst* inst)
        {
            NamedAddress* named = dynamic_cast< NamedAddress*>(inst->fAddress);
            IndexedAddress* indexed = dynamic_cast< IndexedAddress*>(inst->fAddress);

            if (named) {
                *fOut << "&" << named->getName();
            } else {
                *fOut << "&" << indexed->getName() << "[";
                indexed->fIndex->accept(this);
                *fOut << "]";
            }
        }

        virtual void visit(StoreVarInst* inst)
        {
            NamedAddress* named = dynamic_cast< NamedAddress*>(inst->fAddress);
            IndexedAddress* indexed = dynamic_cast< IndexedAddress*>(inst->fAddress);

            if (named) {
                *fOut << named->getName() << " = ";
            } else {
                *fOut << indexed->getName() << "[";
                indexed->fIndex->accept(this);
                *fOut << "] = ";
            }
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

        virtual void visit(CastNumInst* inst)
        {
            *fOut << "(" << generateType(inst->fTyped) << ")";
            inst->fInst->accept(this);
        }

        virtual void visit(FunCallInst* inst)
        {
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
                        if (!((*it).second)->hasReturn())
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
