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

#include "text_instructions.hh"
#include "dsp_factory.hh"

class JAVAScriptInstVisitor : public TextInstVisitor {

    private:

        /*
         Global functions names table as a static variable in the visitor
         so that each function prototype is generated as most once in the module.
         */
        static map <string, bool> gFunctionSymbolTable;
        static map <string, string> gMathLibTable;

    public:
		using TextInstVisitor::visit;

        JAVAScriptInstVisitor(std::ostream* out, int tab = 0)
            :TextInstVisitor(out, ".", tab)
        {
            initMathTable();
        }
    
        void initMathTable()
        {
            if (gMathLibTable.size()) {
                return;
            }
            gMathLibTable["abs"] = "Math.abs";
            gMathLibTable["absf"] = "Math.abs";
            gMathLibTable["fabsf"] = "Math.abs";
            gMathLibTable["acosf"] = "Math.acos";
            gMathLibTable["asinf"] = "Math.asin";
            gMathLibTable["atanf"] = "Math.atan";
            gMathLibTable["atan2f"] = "Math.atan2";
            gMathLibTable["ceilf"] = "Math.ceil";
            gMathLibTable["cosf"] = "Math.cos";
            gMathLibTable["expf"] = "Math.exp";
            gMathLibTable["floorf"] = "Math.floor";
            gMathLibTable["fmodf"] = "function fmod(a, b) { return a % b; }";
            gMathLibTable["logf"] = "Math.log";
            gMathLibTable["log10f"] = "function log10(a) { return Math.log(a)/Math.log(10); }";
            gMathLibTable["max"] = "Math.max";
            gMathLibTable["min"] = "Math.min";
            gMathLibTable["powf"] = "Math.pow";
            gMathLibTable["roundf"] = "Math.round";
            gMathLibTable["sinf"] = "Math.sin";
            gMathLibTable["sqrtf"] = "Math.sqrt";
            gMathLibTable["tanf"] = "Math.tan";
        }

        virtual ~JAVAScriptInstVisitor()
        {}

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
                    name = "ui_interface.openVerticalBox("; break;
                case 1:
                    name = "ui_interface.openHorizontalBox("; break;
                case 2:
                    name = "ui_interface.openTabBox("; break;
            }
            *fOut << name << quote(inst->fName) << ")";
            EndLine();
        }

        virtual void visit(CloseboxInst* inst)
        {
            *fOut << "ui_interface.closeBox();"; tab(fTab, *fOut);
        }
        
        virtual void visit(AddButtonInst* inst)
        {
            if (inst->fType == AddButtonInst::kDefaultButton) {
                *fOut << "ui_interface.addButton(" << quote(inst->fLabel) << ", ";
            } else {
                *fOut << "ui_interface.addCheckButton(" << quote(inst->fLabel) << ", ";
            }
            
            *fOut << "function handler(obj) { function setval(val) { obj." << inst->fZone << " = val; } return setval; }(this))";
            EndLine();
        }
        
        virtual void visit(AddSliderInst* inst)
        {
            string name;
            switch (inst->fType) {
                case AddSliderInst::kHorizontal:
                    name = "ui_interface.addHorizontalSlider("; break;
                case AddSliderInst::kVertical:
                    name = "ui_interface.addVerticalSlider("; break;
                case AddSliderInst::kNumEntry:
                    name = "ui_interface.addNumEntry("; break;
            }
            *fOut << name << quote(inst->fLabel) << ", ";
            *fOut << "function handler(obj) { function setval(val) { obj." << inst->fZone << " = val; } return setval; }(this)";
            *fOut << ", " << inst->fInit << ", " << inst->fMin << ", " << inst->fMax << ", " << inst->fStep << ")";
            EndLine();
        }

        virtual void visit(AddBargraphInst* inst)
        {
            string name;
            switch (inst->fType) {
                case AddBargraphInst::kHorizontal:
                    name = "ui_interface.addHorizontalBargraph("; break;
                case AddBargraphInst::kVertical:
                    name = "ui_interface.addVerticalBargraph("; break;
            }
            *fOut << name << quote(inst->fLabel) << ", ";
            *fOut << "function handler(obj) { function setval(val) { obj." << inst->fZone << " = val; } return setval; }(this)";
            *fOut << ", " << inst->fMin << ", " << inst->fMax << ")";
            EndLine();
        }

        virtual void visit(LabelInst* inst)
        {}

        virtual void visit(DeclareVarInst* inst)
        {
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
        
        virtual void generateFunDefArgs(DeclareFunInst* inst)
        {
            *fOut << "(";
            list<NamedTyped*>::const_iterator it;
            size_t size = inst->fType->fArgsTypes.size(), i = 0;
            for (it = inst->fType->fArgsTypes.begin(); it != inst->fType->fArgsTypes.end(); it++, i++) {
                // No type is generated...
                *fOut << (*it)->fName;
                if (i < size - 1) *fOut << ", ";
            }
        }
        
        virtual void visit(DeclareFunInst* inst)
        {
            // Already generated
            if (gFunctionSymbolTable.find(inst->fName) != gFunctionSymbolTable.end()) {
                return;
            } else {
                gFunctionSymbolTable[inst->fName] = true;
            }
            
            // Do not declare Math library functions
            if (gMathLibTable.find(inst->fName) != gMathLibTable.end()) {
                return;
            }
        
            // Prototype
            *fOut << "this." << generateFunName(inst->fName) << " = function";
            generateFunDefArgs(inst);
            generateFunDefBody(inst);
        }
        
        virtual void visit(NamedAddress* named)
        {   
            if (named->getAccess() & Address::kStruct) {
                *fOut << "this.";
            }
            *fOut << named->fName;
        }
  
        virtual void visit(LoadVarAddressInst* inst)
        {
           // Not implemented in JavaScript
            faustassert(false);
        }
                
        // No .f syntax for float in JS
        virtual void visit(FloatNumInst* inst)
        {
            *fOut << inst->fNum;
        }
        
        // No . syntax for double in JS
        virtual void visit(DoubleNumInst* inst)
        {
            *fOut << inst->fNum;
        }

        virtual void visit(::CastInst* inst)
        {
            // No explicit cast generation
            inst->fInst->accept(this);
        }
    
        virtual void visit(BitcastInst* inst) { faustassert(false); }
       
        virtual void visit(FunCallInst* inst)
        {
            string fun_name = (gMathLibTable.find(inst->fName) != gMathLibTable.end()) ? gMathLibTable[inst->fName] : inst->fName;
            generateFunCall(inst, fun_name);
        }
        
        static void cleanup() { gFunctionSymbolTable.clear(); gMathLibTable.clear(); }

};

#endif
