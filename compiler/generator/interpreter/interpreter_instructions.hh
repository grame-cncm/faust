/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2015 GRAME, Centre National de Creation Musicale
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

#ifndef _INTERPRETER_INSTRUCTIONS_H
#define _INTERPRETER_INSTRUCTIONS_H

using namespace std;

#include "instructions.hh"
#include "typing_instructions.hh"

class InterpreterInstVisitor {

    private:
    
        /*
         Global functions names table as a static variable in the visitor
         so that each function prototype is generated as most once in the module.
         */
        static map <string, int> gFunctionSymbolTable;      
        static map <string, string> gMathLibTable;
    
        TypingVisitor fTypingVisitor;
   
    public:
     
        InterpreterInstVisitor()
        {
        }
        
        void initMathTable()
        {
            
        }

        virtual ~InterpreterInstVisitor()
        {}
   
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

        virtual void visit(LabelInst* inst)
        {
            // Empty
        }
      
        virtual void visit(DeclareVarInst* inst)
        {
            
        }

        virtual void visit(DeclareFunInst* inst)
        {
            
        }
        
        virtual void visit(LoadVarInst* inst)
        {
            
        }

        virtual void visit(LoadVarAddressInst* inst)
        {   
            // Not implemented in Interpreter
            assert(false);
        }
   
        virtual void visit(FloatNumInst* inst)
        {
        
        }

        virtual void visit(IntNumInst* inst)
        {
            
        }

        virtual void visit(BoolNumInst* inst)
        {
            
        }

        virtual void visit(DoubleNumInst* inst)
        {
           
        }
    
        virtual void visit(BinopInst* inst)
        {
            
        }

        virtual void visit(CastNumInst* inst)
        {
            
        }
    
        virtual void visit(FunCallInst* inst)
        {
        }
      
        virtual void visit(Select2Inst* inst)
        {
            
        }
        

};

#endif
