/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2022 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifndef _TEMPLATE_INSTRUCTIONS_H
#define _TEMPLATE_INSTRUCTIONS_H

#include <string>

#include "text_instructions.hh"
#include "struct_manager.hh"

using namespace std;

class TemplateInstVisitor : public TextInstVisitor {
   private:
    
    /*
     Global functions names table as a static variable in the visitor
     so that each function prototype is generated as most once in the module.
     */
    static map<string, bool> gFunctionSymbolTable;
    
   public:
    using TextInstVisitor::visit;

    TemplateInstVisitor(std::ostream* out, const string& struct_name, int tab = 0)
        : TextInstVisitor(out, ".", new TemplateStringTypeManager(xfloat(), "*", struct_name), tab)
    {}

    virtual ~TemplateInstVisitor() {}

    virtual void visit(AddMetaDeclareInst* inst)
    {}

    virtual void visit(OpenboxInst* inst)
    {}

    virtual void visit(CloseboxInst* inst)
    {}
    
    virtual void visit(AddButtonInst* inst)
    {}

    virtual void visit(AddSliderInst* inst)
    {}

    virtual void visit(AddBargraphInst* inst)
    {}

    virtual void visit(AddSoundfileInst* inst)
    {
        // Not supported for now
        throw faustexception("ERROR : 'soundfile' primitive not yet supported for Template\n");
    }
    
    virtual void visit(Int32NumInst* inst) {}
    
    virtual void visit(Int64NumInst* inst) {}
    
    virtual void visit(Int32ArrayNumInst* inst)
    {}
    
    virtual void visit(FloatArrayNumInst* inst)
    {}
    
    virtual void visit(DoubleArrayNumInst* inst)
    {}
    
    virtual void visit(BinopInst* inst)
    {}
   
    virtual void visit(DeclareVarInst* inst)
    {}

    virtual void visit(DropInst* inst)
    {}
    
    virtual void visit(DeclareFunInst* inst)
    {}
        
    virtual void generateFunDefBody(DeclareFunInst* inst)
    {}

    virtual void visit(NamedAddress* named)
    {}
    
    /*
    Indexed address can actually be values in an array or fields in a struct type
    */
    virtual void visit(IndexedAddress* indexed)
    {}
      
    virtual void visit(::CastInst* inst)
    {}

    virtual void visit(BitcastInst* inst)
    {}
    
    virtual void visitCond(ValueInst* cond)
    {}
    
    // Generate standard funcall (not 'method' like funcall...)
    virtual void visit(FunCallInst* inst)
    {}
    
    virtual void visit(IfInst* inst)
    {}
  
    virtual void visit(ForLoopInst* inst)
    {}

    static void cleanup() { gFunctionSymbolTable.clear(); }
};

#endif

