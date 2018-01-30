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

#ifndef _TYPING_INSTRUCTIONS_H
#define _TYPING_INSTRUCTIONS_H

#include "instructions.hh"

using namespace std;

/*
 Typing visitor: to be used when knowing the exact type of the currenty compiled value is needed.
 */

struct TypingVisitor : public InstVisitor {

        Typed::VarType fCurType;
    
        TypingVisitor():fCurType(Typed::kNoType)
        {}
       
        virtual ~TypingVisitor()
        {}
    
        virtual void visit(LoadVarInst* inst)
        {
            //dump2FIR(inst);
            
            // Stack or struct variables
            if (gGlobal->hasVarType(inst->getName())) {
                fCurType = gGlobal->getVarType(inst->getName());
                if (dynamic_cast<IndexedAddress*>(inst->fAddress)) {
                    fCurType = Typed::getTypeFromPtr(fCurType);
                }
            // Specific cases for FunArgs
            } else if (startWith(inst->getName(), "count") || startWith(inst->getName(), "samplingFreq")) {
                fCurType = Typed::kInt32;
            } else {
                fCurType = Typed::kNoType;
            }
        }
    
        virtual void visit(TeeVarInst* inst)
        {
            if (gGlobal->hasVarType(inst->getName())) {
                fCurType = gGlobal->getVarType(inst->getName());
            } else {
                fCurType = Typed::kNoType;
            }
        }
    
        virtual void visit(LoadVarAddressInst* inst)
        {
            // Not implemented
            faustassert(false);
        }
   
        virtual void visit(FloatNumInst* inst)
        {
            fCurType = Typed::kFloat;
        }

        virtual void visit(Int32NumInst* inst)
        {
            fCurType = Typed::kInt32;
        }
    
        virtual void visit(Int64NumInst* inst)
        {
            fCurType = Typed::kInt64;
        }

        virtual void visit(BoolNumInst* inst)
        {
            fCurType = Typed::kBool;
        }

        virtual void visit(DoubleNumInst* inst)
        {
            fCurType = Typed::kDouble;
        }
    
        virtual void visit(BinopInst* inst)
        {
            if (isBoolOpcode(inst->fOpcode)) {
                fCurType = Typed::kBool;
            } else {
                inst->fInst1->accept(this);
                Typed::VarType type1 = fCurType;
                if (isRealType(type1)) {
                    fCurType = type1;
                } else {
                    inst->fInst2->accept(this);
                    Typed::VarType type2 = fCurType;
                    if (isRealType(type2)) {
                        fCurType = type2;
                    } else if (isIntType32(type1) || isIntType32(type2)) {
                        fCurType = Typed::kInt32;
                    } else if (isIntType64(type1) || isIntType64(type2)) {
                        fCurType = Typed::kInt64;
                    } else if (isBoolType(type1) && isBoolType(type2)) {
                        fCurType = Typed::kBool;
                    } else {
                        // Should never happen...
                        faustassert(false);
                    }
                }
            }
        }

        virtual void visit(::CastInst* inst)
        {
            fCurType = inst->fType->getType();
        }
    
        virtual void visit(BitcastInst* inst)
        {
            fCurType = inst->fType->getType();
        }
    
        virtual void visit(Select2Inst* inst)
        {
            // Type in the one of 'then' or 'else'
            inst->fThen->accept(this);
        }
    
        virtual void visit(IfInst* inst)
        {
            // Type in the one of 'then' or 'else'
            inst->fThen->accept(this);
        }
    
        virtual void visit(FunCallInst* inst)
        { 
            if (gGlobal->hasVarType(inst->fName)) {
                fCurType = gGlobal->getVarType(inst->fName);
            } else {
                // Should never happen...
                faustassert(false);
            }
        }
        
};

class BasicTypingCloneVisitor : public BasicCloneVisitor {
    
    protected:
    
        TypingVisitor fTypingVisitor;
    
    public:
        
        BasicTypingCloneVisitor()
        {}
    
        // Memory
        virtual ValueInst* visit(LoadVarInst* inst)
        {
            fTypingVisitor.visit(inst);
            return BasicCloneVisitor::visit(inst);
        }
       
        // Numbers
        virtual ValueInst* visit(FloatNumInst* inst)
        {
            fTypingVisitor.visit(inst);
            return BasicCloneVisitor::visit(inst);
        }
        virtual ValueInst* visit(Int32NumInst* inst)
        {
            fTypingVisitor.visit(inst);
            return BasicCloneVisitor::visit(inst);
        }
        virtual ValueInst* visit(Int64NumInst* inst)
        {
            fTypingVisitor.visit(inst);
            return BasicCloneVisitor::visit(inst);
        }
        virtual ValueInst* visit(BoolNumInst* inst)
        {
            fTypingVisitor.visit(inst);
            return BasicCloneVisitor::visit(inst);
        }
        virtual ValueInst* visit(DoubleNumInst* inst)
        {
            fTypingVisitor.visit(inst);
            return BasicCloneVisitor::visit(inst);
        }

        // Numerical computation
        virtual ValueInst* visit(BinopInst* inst)
        {
            fTypingVisitor.visit(inst);
            return BasicCloneVisitor::visit(inst);
        }
        
        // Cast
        virtual ValueInst* visit(::CastInst* inst)
        {
            fTypingVisitor.visit(inst);
            return BasicCloneVisitor::visit(inst);
        }
        virtual ValueInst* visit(BitcastInst* inst)
        {
            fTypingVisitor.visit(inst);
            return BasicCloneVisitor::visit(inst);
        }
        
        // Function call
        virtual ValueInst* visit(FunCallInst* inst)
        {
            fTypingVisitor.visit(inst);
            return BasicCloneVisitor::visit(inst);
        }

        // Conditionnal
        virtual ValueInst* visit(Select2Inst* inst)
        {
            fTypingVisitor.visit(inst);
            return BasicCloneVisitor::visit(inst);
        }
        virtual StatementInst* visit(IfInst* inst)
        {
            fTypingVisitor.visit(inst);
            return BasicCloneVisitor::visit(inst);
        }

};

#endif
