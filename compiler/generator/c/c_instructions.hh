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

using namespace std;

#include "text_instructions.hh"

class CInstVisitor : public TextInstVisitor {
    
    private:
    
        /*
         Global functions names table as a static variable in the visitor
         so that each function prototype is generated as most once in the module.
         */
        static map <string, bool> gFunctionSymbolTable;
    
    public:

        CInstVisitor(std::ostream* out, const string& structname, int tab = 0)
            :TextInstVisitor(out, "->", new CStringTypeManager(FLOATMACRO, "*"), tab)
        {
            fTypeManager->fTypeDirectTable[Typed::kObj] = structname;
            fTypeManager->fTypeDirectTable[Typed::kObj_ptr] = structname + "*";
            
            // Mark all math.h functions as generated...
            gFunctionSymbolTable["abs"] = true;
            
            gFunctionSymbolTable["max"] = true;
            gFunctionSymbolTable["min"] = true;
            
            // Float version
            gFunctionSymbolTable["absf"] = true;
            gFunctionSymbolTable["fabsf"] = true;
            gFunctionSymbolTable["acosf"] = true;
            gFunctionSymbolTable["asinf"] = true;
            gFunctionSymbolTable["atanf"] = true;
            gFunctionSymbolTable["atan2f"] = true;
            gFunctionSymbolTable["ceilf"] = true;
            gFunctionSymbolTable["cosf"] = true;
            gFunctionSymbolTable["expf"] = true;
            gFunctionSymbolTable["exp10f"] = true;
            gFunctionSymbolTable["floorf"] = true;
            gFunctionSymbolTable["fmodf"] = true;
            gFunctionSymbolTable["logf"] = true;
            gFunctionSymbolTable["log10f"] = true;
            gFunctionSymbolTable["powf"] = true;
            gFunctionSymbolTable["remainderf"] = true;
            gFunctionSymbolTable["roundf"] = true;
            gFunctionSymbolTable["sinf"] = true;
            gFunctionSymbolTable["sqrtf"] = true;
            gFunctionSymbolTable["tanf"] = true;
            
            // Double version
            gFunctionSymbolTable["abs"] = true;
            gFunctionSymbolTable["fabs"] = true;
            gFunctionSymbolTable["acos"] = true;
            gFunctionSymbolTable["asin"] = true;
            gFunctionSymbolTable["atan"] = true;
            gFunctionSymbolTable["atan2"] = true;
            gFunctionSymbolTable["ceil"] = true;
            gFunctionSymbolTable["cos"] = true;
            gFunctionSymbolTable["exp"] = true;
            gFunctionSymbolTable["exp10"] = true;
            gFunctionSymbolTable["floor"] = true;
            gFunctionSymbolTable["fmod"] = true;
            gFunctionSymbolTable["log"] = true;
            gFunctionSymbolTable["log10"] = true;
            gFunctionSymbolTable["pow"] = true;
            gFunctionSymbolTable["remainder"] = true;
            gFunctionSymbolTable["round"] = true;
            gFunctionSymbolTable["sin"] = true;
            gFunctionSymbolTable["sqrt"] = true;
            gFunctionSymbolTable["tan"] = true;
        }

        virtual ~CInstVisitor()
        {}

        virtual void visit(AddMetaDeclareInst* inst)
        {
            // Special case
            if (inst->fZone == "0") {
                *fOut << "ui_interface->declare(ui_interface->uiInterface, " << inst->fZone << ", " << quote(inst->fKey) << ", " << quote(inst->fValue) << ")";
            } else {
                *fOut << "ui_interface->declare(ui_interface->uiInterface, &dsp->" << inst->fZone <<", " << quote(inst->fKey) << ", " << quote(inst->fValue) << ")";
            }
            EndLine();
        }

        virtual void visit(OpenboxInst* inst)
        {
            string name;
            switch (inst->fOrient) {
                case 0:
                    name = "ui_interface->openVerticalBox("; break;
                case 1:
                    name = "ui_interface->openHorizontalBox("; break;
                case 2:
                    name = "ui_interface->openTabBox("; break;
            }
            *fOut << name << "ui_interface->uiInterface, " << quote(inst->fName) << ")";
            EndLine();
        }

        virtual void visit(CloseboxInst* inst)
        {
            *fOut << "ui_interface->closeBox(ui_interface->uiInterface);"; tab(fTab, *fOut);
        }
        virtual void visit(AddButtonInst* inst)
        {
            string name;
            if (inst->fType == AddButtonInst::kDefaultButton) {
                name = "ui_interface->addButton("; 
            } else {
                name = "ui_interface->addCheckButton("; 
            }
            *fOut << name << "ui_interface->uiInterface, " << quote(inst->fLabel) << ", &dsp->" << inst->fZone << ")";
            EndLine();
        }

        virtual void visit(AddSliderInst* inst)
        {
            string name;
            switch (inst->fType) {
                case AddSliderInst::kHorizontal:
                    name = "ui_interface->addHorizontalSlider("; break;
                case AddSliderInst::kVertical:
                    name = "ui_interface->addVerticalSlider("; break;
                case AddSliderInst::kNumEntry:
                    name = "ui_interface->addNumEntry("; break;
            }
            *fOut << name << "ui_interface->uiInterface, " << quote(inst->fLabel)
            << ", &dsp->" << inst->fZone
            << ", " << checkReal(inst->fInit)
            << ", " << checkReal(inst->fMin)
            << ", " << checkReal(inst->fMax)
            << ", " << checkReal(inst->fStep) << ")";
            EndLine();
        }

        virtual void visit(AddBargraphInst* inst)
        {
            string name;
            switch (inst->fType) {
                case AddBargraphInst::kHorizontal:
                    name = "ui_interface->addHorizontalBargraph("; break;
                case AddBargraphInst::kVertical:
                    name = "ui_interface->addVerticalBargraph("; break;
            }
            *fOut << name << "ui_interface->uiInterface, " << quote(inst->fLabel) 
            << ", &dsp->" << inst->fZone
            << ", " << checkReal(inst->fMin)
            << ", " << checkReal(inst->fMax) << ")";          
            EndLine();
        }

        virtual void visit(DeclareVarInst* inst)
        {
            if (inst->fAddress->getAccess() & Address::kStaticStruct) {
                 *fOut << "static ";
            }

            if (inst->fAddress->getAccess() & Address::kVolatile) {
                 *fOut << "volatile ";
            }

            *fOut << fTypeManager->generateType(inst->fType, inst->fAddress->getName());
            if (inst->fValue) {
                *fOut << " = "; inst->fValue->accept(this); 
            }
            EndLine();
        }

        virtual void visit(DeclareFunInst* inst)
        {
            // Already generated
            if (gFunctionSymbolTable.find(inst->fName) != gFunctionSymbolTable.end()) {
                return;
            } else {
                gFunctionSymbolTable[inst->fName] = true;
            }
            
            // Defined as macro in the architecture file...
            if (startWith(inst->fName, "min") || startWith(inst->fName, "max")) {
                return;
            }
      
            // Prototype
            if (inst->fType->fAttribute & FunTyped::kInline) {
                *fOut << "inline ";
            }
            
            if (inst->fType->fAttribute & FunTyped::kLocal
                || inst->fType->fAttribute & FunTyped::kStatic) {
                *fOut << "static ";
            }

            *fOut << fTypeManager->generateType(inst->fType->fResult, inst->fName);
            generateFunDefArgs(inst);
            generateFunDefBody(inst);
        }
        
        virtual void visit(NamedAddress* named)
        {   
            if (named->getAccess() & Address::kStruct) {
                *fOut << "dsp->";
            }
            *fOut << named->fName;
        }
      
        virtual void visit(LoadVarAddressInst* inst)
        {
            *fOut << "&"; inst->fAddress->accept(this);
        }
  
        virtual void visit(::CastInst* inst)
        {
            *fOut << "(" << fTypeManager->generateType(inst->fType) << ")";
            inst->fInst->accept(this);
        }
    
        // TODO : does not work, put this code in a function
        virtual void visit(BitcastInst* inst)
        {
            switch (inst->fType->getType()) {
                case Typed::kInt32:
                    *fOut << "*((int*)&"; inst->fInst->accept(this); *fOut << ")";
                    break;
                case Typed::kInt64:
                    *fOut << "*((long long*)&"; inst->fInst->accept(this); *fOut << ")";
                    break;
                case Typed::kFloat:
                    *fOut << "*((float*)&"; inst->fInst->accept(this); *fOut << ")";
                    break;
                case Typed::kDouble:
                    *fOut << "*((double*)&"; inst->fInst->accept(this); *fOut << ")";
                    break;
                default:
                    faustassert(false);
                    break;
            }
        }

        // Generate standard funcall (not 'method' like funcall...)
        virtual void visit(FunCallInst* inst)
        {
            // Integer and real min/max are mapped on polymorphic ones
            string name;
            if (startWith(inst->fName, "min")) {
                name = "min";
            } else if (startWith(inst->fName, "max")) {
                name = "max";
            } else {
                name = inst->fName;
            }
            
            *fOut << gGlobal->getMathFunction(name) << "(";
           
            // Compile parameters
            generateFunCallArgs(inst->fArgs.begin(), inst->fArgs.end(), inst->fArgs.size());
            *fOut << ")";
        }
        
        virtual void visit(ForLoopInst* inst)
        {
            // Don't generate empty loops...
            if (inst->fCode->size() == 0) return;
            
            DeclareVarInst* c99_declare_inst = dynamic_cast<DeclareVarInst*>(inst->fInit);
            StoreVarInst* c99_init_inst = NULL;

            if (c99_declare_inst) {
                InstBuilder::genLabelInst("/* C99 loop */")->accept(this);
                *fOut << "{";
                fTab++;
                tab(fTab, *fOut);

                // To generate C99 compatible loops...
                c99_init_inst = InstBuilder::genStoreStackVar(c99_declare_inst->getName(), c99_declare_inst->fValue);
                c99_declare_inst = InstBuilder::genDecStackVar(c99_declare_inst->getName(), InstBuilder::genBasicTyped(Typed::kInt32));
                // C99 loop variable declared outside the loop
                c99_declare_inst->accept(this);
            }

            *fOut << "for (";
                fFinishLine = false;
                if (c99_declare_inst) {
                    // C99 loop initialized here
                    c99_init_inst->accept(this);
                } else {
                    // Index already defined
                    inst->fInit->accept(this);
                }
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

             if (c99_declare_inst) {
                fTab--;
                tab(fTab, *fOut);
                *fOut << "}";
                tab(fTab, *fOut);
             }
        }
        
        static void cleanup() { gFunctionSymbolTable.clear(); }
};

#endif
