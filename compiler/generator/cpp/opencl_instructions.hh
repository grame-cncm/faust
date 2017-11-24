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

#ifndef _OPENCL_INSTRUCTIONS_H
#define _OPENCL_INSTRUCTIONS_H

using namespace std;

#include "text_instructions.hh"

class OpenCLInstVisitor : public TextInstVisitor {

    private:

        map <string, int> fGlobalTable;

    public:
		using TextInstVisitor::visit;

        OpenCLInstVisitor(std::ostream* out, int tab = 0)
            :TextInstVisitor(out, "->", new CStringTypeManager(FLOATMACRO, "*"), tab)
        {}

        virtual ~OpenCLInstVisitor()
        {}

        virtual void visit(AddMetaDeclareInst* inst)
        {
            *fOut << "interface->declare(" << "&" << inst->fZone <<", " << "\"" <<inst->fKey << "\"" << ", " <<  "\"" << inst->fValue << "\"" << ")"; EndLine();
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
            *fOut << name << "(" << "\"" << inst->fName << "\"" << ")";
            EndLine();
        }

        virtual void visit(CloseboxInst* inst)
        {
            *fOut << "interface->closeBox();"; tab(fTab, *fOut);
        }
        
        virtual void visit(AddButtonInst* inst)
        {
            if (inst->fType == AddButtonInst::kDefaultButton) {
                *fOut << "interface->addButton(" << "\"" << inst->fLabel << "\"" << "," << "&" << inst->fZone << ")"; EndLine();
            } else {
                *fOut << "interface->addCheckButton(" << "\"" << inst->fLabel << "\"" << "," << "&" << inst->fZone << ")"; EndLine();
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
            *fOut << name << "(" << "\"" << inst->fLabel << "\"" << ", " << "&" << inst->fZone << ", " << checkReal(inst->fInit) << ", " << checkReal(inst->fMin) << ", " << checkReal(inst->fMax) << ", " << checkReal(inst->fStep) << ")";
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
            *fOut << name << "(" << "\"" << inst->fLabel << "\"" << ", " << "&" << inst->fZone << ", "<< checkReal(inst->fMin) << ", " << checkReal(inst->fMax) << ")";
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
            // Defined as macro in the architecture file...
            if (startWith(inst->fName, "min") || startWith(inst->fName, "max")) {
                return;
            }

            // Prototype
            if (inst->fType->fAttribute & FunTyped::kLocal) {
                 *fOut << "inline ";
            }

            *fOut << fTypeManager->generateType(inst->fType->fResult, inst->fName);
            generateFunDefArgs(inst);
            generateFunDefBody(inst);
       }

        virtual void visit(LoadVarAddressInst* inst)
        {
            *fOut << "&"; inst->fAddress->accept(this);
        }

        virtual void visit(::CastInst* inst)
        {
            *fOut << "(" << fTypeManager->generateType(inst->fType) << ")";
            *fOut << "("; inst->fInst->accept(this);  *fOut << ")";
        }
        
        virtual void visit(FunCallInst* inst)
        {
            generateFunCall(inst, inst->fName);
        }

};

#endif
