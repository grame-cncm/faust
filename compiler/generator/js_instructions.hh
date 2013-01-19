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

#ifndef _JAVASCRIPT_INSTRUCTIONS_H
#define _JAVASCRIPT_INSTRUCTIONS_H

using namespace std;

#include "instructions.hh"
#include "type_manager.hh"
#include "binop.hh"
#include "Text.hh"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

class JAVAScriptInstVisitor : public InstVisitor {

    private:

        int fTab;
        std::ostream* fOut;
        bool fFinishLine;
        map <string, string> fMathLibTable;

    public:

        JAVAScriptInstVisitor(std::ostream* out, int tab = 0):fTab(tab), fOut(out), fFinishLine(true)
        {
            fMathLibTable["abs"] = "Math.abs";
            fMathLibTable["absf"] = "Math.abs";
            fMathLibTable["fabsf"] = "Math.abs";
            fMathLibTable["acosf"] = "Math.acos";
            fMathLibTable["asinf"] = "Math.asin";
            fMathLibTable["atanf"] = "Math.atan";
            fMathLibTable["atan2f"] = "Math.atan2";
            fMathLibTable["ceilf"] = "Math.ceil";
            fMathLibTable["cosf"] = "Math.cos";
            fMathLibTable["expf"] = "Math.exp";
            fMathLibTable["floorf"] = "Math.floor";
            fMathLibTable["fmodf"] = "function fmod(a,b) {return a % b }";
            fMathLibTable["logf"] = "Math.log";
            fMathLibTable["log10f"] = "Math.log";
            fMathLibTable["max"] = "Math.max";
            fMathLibTable["min"] = "Math.min";
            fMathLibTable["powf"] = "Math.pow";
            fMathLibTable["roundf"] = "Math.round";
            fMathLibTable["sinf"] = "Math.sin";
            fMathLibTable["sqrtf"] = "Math.sqrt";
            fMathLibTable["tanf"] = "Math.tan";
        }

        virtual ~JAVAScriptInstVisitor()
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
            *fOut << "ui_interface.declare(\"" << inst->fZone << "\", \"" << inst->fKey << "\", \"" <<  inst->fValue << "\")";
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
                *fOut << "ui_interface.addButton(" << "\"" << inst->fLabel << "\"" << ", ";
            } else {
                *fOut << "ui_interface.addCheckButton(" << "\"" << inst->fLabel << "\"" << ", ";
            }
            
            *fOut << "function handler(obj) { function setval(val) { obj." << inst->fZone << " = val; } return setval; }(this))";
            EndLine();
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
            *fOut << name << "(" << "\"" << inst->fLabel << "\"" << ", ";
            *fOut << "function handler(obj) { function setval(val) { obj." << inst->fZone << " = val; } return setval; }(this)";
            *fOut << ", " << inst->fInit << ", " << inst->fMin << ", " << inst->fMax << ", " << inst->fStep << ")";
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
            *fOut << name << "(" << "\"" << inst->fLabel << "\"" << ", ";
            *fOut << "function handler(obj) { function setval(val) { obj." << inst->fZone << " = val; } return setval; }(this)";
            *fOut << ", " << inst->fMin << ", " << inst->fMax << ")";
            EndLine();
        }

        virtual void visit(LabelInst* inst)
        {
            // No generation
        }

        virtual void visit(DeclareVarInst* inst)
        {
            if (inst->fAddress->getAccess() & Address::kGlobal) {
                if (gGlobal->gGlobalTable.find(inst->fAddress->getName()) == gGlobal->gGlobalTable.end()) {
                    // If global is not defined
                    gGlobal->gGlobalTable[inst->fAddress->getName()] = 1;
                } else {
                    return;
                }
            }
   
            string prefix = (inst->fAddress->getAccess() & Address::kStruct) ? "this." : "var ";

            if (inst->fValue) {
                *fOut << prefix << inst->fAddress->getName() << " = "; inst->fValue->accept(this);
            } else {
                ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fType);
                if (array_typed && array_typed->fSize > 1) {
                    string type = (array_typed->fType->getType() == Typed::kFloat) ? "Float32Array" : "Int32Array";
                    *fOut << prefix << inst->fAddress->getName() << " = new " << type << "(" << array_typed->fSize << ")";
                } else {
                    *fOut << prefix << inst->fAddress->getName();
                }
            }
            EndLine();
        }

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

        virtual void visit(DeclareFunInst* inst)
        {
            // Do not declare Math library functions
            if (fMathLibTable.find(inst->fName) != fMathLibTable.end()) {
                return;
            }

            // Prototype
            *fOut << "function " << inst->fName << "(";
            list<NamedTyped*>::const_iterator it;
            int size = inst->fType->fArgsTypes.size(), i = 0;
            for (it = inst->fType->fArgsTypes.begin(); it != inst->fType->fArgsTypes.end(); it++, i++) {
                *fOut << (*it)->fName;
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
            if (inst->fAddress->getAccess() & Address::kStruct) {
                *fOut << "this.";
            }
            inst->fAddress->accept(this);
        }
        
        virtual void visit(LoadVarAddressInst* inst)
        {
           // Not implemented in JavaScript
            assert(false);
        }
        
        virtual void visit(StoreVarInst* inst)
        {
            if (inst->fAddress->getAccess() & Address::kStruct) {
                *fOut << "this.";
            }
            inst->fAddress->accept(this);
            *fOut << " = ";
            inst->fValue->accept(this);
            EndLine();
        }

        virtual void visit(FloatNumInst* inst)
        {
            *fOut << inst->fNum;
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
            // No explicit cast generation
            inst->fInst->accept(this);
        }
        
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
      
        virtual void visit(FunCallInst* inst)
        {
            string js_name = (fMathLibTable.find(inst->fName) != fMathLibTable.end()) ? fMathLibTable[inst->fName] : inst->fName;
                 
            if (inst->fMethod) {
                list<ValueInst*>::const_iterator it = inst->fArgs.begin();
                // Compile object arg
                (*it)->accept(this);
                // Compile parameters
                *fOut << "." << js_name << "(";
                compileArgs(++it, inst->fArgs.end(), inst->fArgs.size() - 1);
            } else {
                *fOut << js_name << "(";
                // Compile parameters
                compileArgs(inst->fArgs.begin(), inst->fArgs.end(), inst->fArgs.size());
            }
            *fOut << ")";
            
            // Special case
            if (inst->fName == "log10f") {
                *fOut << "/Math.log(10)";
            }
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
