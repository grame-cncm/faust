/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2021 GRAME, Centre National de Creation Musicale
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

#ifndef _JULIA_INSTRUCTIONS_H
#define _JULIA_INSTRUCTIONS_H

#include <string>

#include "text_instructions.hh"
#include "struct_manager.hh"

using namespace std;

class JuliaInstVisitor : public TextInstVisitor {
   private:
    /*
     Global functions names table as a static variable in the visitor
     so that each function prototype is generated as most once in the module.
     */
    static map<string, bool> gFunctionSymbolTable;

    // Polymorphic math functions
    map<string, string> gPolyMathLibTable;
    
   public:
    using TextInstVisitor::visit;

    JuliaInstVisitor(std::ostream* out, const string& struct_name, int tab = 0)
        : TextInstVisitor(out, ".", new JuliaStringTypeManager(xfloat(), "*", struct_name), tab)
    {
        
    }

    virtual ~JuliaInstVisitor() {}

    virtual void visit(AddMetaDeclareInst* inst)
    {
        
    }

    virtual void visit(OpenboxInst* inst)
    {
        
    }

    virtual void visit(CloseboxInst* inst)
    {
       
    }
    
    virtual void visit(AddButtonInst* inst)
    {
       
    }

    virtual void visit(AddSliderInst* inst)
    {
        
    }

    virtual void visit(AddBargraphInst* inst)
    {
        
    }

    virtual void visit(AddSoundfileInst* inst)
    {
        
    }

    virtual void visit(DeclareVarInst* inst)
    {
        /*
        // TODO
        if (inst->fAddress->getAccess() & Address::kStaticStruct) {
            *fOut << "static ";
        }

        if (inst->fAddress->getAccess() & Address::kVolatile) {
            *fOut << "volatile ";
        }
        */

        *fOut << fTypeManager->generateType(inst->fType, inst->fAddress->getName());
        if (inst->fValue) {
            *fOut << " = ";
            inst->fValue->accept(this);
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
        
        *fOut << "function " << inst->fName;
        generateFunDefArgs(inst);
        generateFunDefBody(inst);
    }

    virtual void visit(NamedAddress* named)
    {
       if (named->getAccess() & Address::kStruct) {
           *fOut << "dsp.";
       }
       *fOut << named->fName;
    }

    virtual void visit(LoadVarAddressInst* inst)
    {
        
    }
    
    /*
    virtual void visit(BinopInst* inst)
    {
       
    }
    */
    
    virtual void visit(::CastInst* inst)
    {
        
    }

    // TODO : does not work, put this code in a function
    virtual void visit(BitcastInst* inst)
    {
        
    }

    // Generate standard funcall (not 'method' like funcall...)
    
    virtual void visit(FunCallInst* inst)
    {
        string name = gGlobal->getMathFunction(inst->fName);
        name = (gPolyMathLibTable.find(name) != gPolyMathLibTable.end()) ? gPolyMathLibTable[name] : name;
        generateFunCall(inst, name);
    }
  
    /*
    virtual void visit(ForLoopInst* inst)
    {
       
    }
    */
    
    static void cleanup() { gFunctionSymbolTable.clear(); }
};

#endif
