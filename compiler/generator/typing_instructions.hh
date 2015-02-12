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

using namespace std;

#include "instructions.hh"

struct TypingVisitor : public InstVisitor {

        Typed::VarType fCurType;
    
        TypingVisitor():fCurType(Typed::kNoType)
        {}
       
        virtual ~TypingVisitor()
        {}
 
        virtual void visit(LoadVarInst* inst)
        {
            if (gGlobal->gVarTypeTable.find(inst->getName()) != gGlobal->gVarTypeTable.end()) {
                fCurType = gGlobal->gVarTypeTable[inst->getName()]->getType();
                if (dynamic_cast<IndexedAddress*>(inst->fAddress)) {
                    fCurType = Typed::getTypeFromPtr(fCurType);
                }
            } else {
                //printf("LoadVarInst : %s\n", inst->getName().c_st()): 
                fCurType = Typed::kNoType;
            }
        }
    
        virtual void visit(LoadVarAddressInst* inst)
        {   
            // Not implemented
            assert(false);
        }
   
        virtual void visit(FloatNumInst* inst)
        {
            fCurType = Typed::kFloat;
        }

        virtual void visit(IntNumInst* inst)
        {
            fCurType = Typed::kInt;
        }

        virtual void visit(BoolNumInst* inst)
        {
            fCurType = Typed::kBool;
        }

        virtual void visit(DoubleNumInst* inst)
        {
            fCurType = Typed::kDouble;
        }
        
        inline bool isRealType(Typed::VarType type) 
        { 
            return (type == Typed::kFloat 
                || type == Typed::kFloatMacro 
                || type == Typed::kDouble); 
        }
   
        virtual void visit(BinopInst* inst)
        {
            if (isBoolOpcode(inst->fOpcode)) {
                fCurType = Typed::kBool;
            } else {
                inst->fInst1->accept(this);
                Typed::VarType type1 = fCurType;
                
                if (isRealType(type1)) {
                    fCurType = Typed::kFloat;
                } else {
                    inst->fInst2->accept(this);
                    Typed::VarType type2 = fCurType;
                    if (isRealType(type2)) {
                        fCurType = Typed::kFloat;
                    } else if (type1 == Typed::kInt || type2 == Typed::kInt) {
                         fCurType = Typed::kInt;
                    } else if (type1 == Typed::kBool && type2 == Typed::kBool) {
                        fCurType = Typed::kBool;
                    } else {
                        fCurType = Typed::kNoType;
                    }
                }
            }
        }

        virtual void visit(CastNumInst* inst)
        {
            fCurType = inst->fType->getType();
        }
      
        virtual void visit(Select2Inst* inst)
        {
            // Type in the one of 'then' or 'else'
            inst->fThen->accept(this);
        }
        
        virtual void visit(FunCallInst* inst) 
        { 
            if (gGlobal->gVarTypeTable.find(inst->fName) != gGlobal->gVarTypeTable.end()) {
                fCurType = gGlobal->gVarTypeTable[inst->fName]->getType();
            } else {
                //printf("FunCallInst : %s\n", inst->fName.c_st()): 
                fCurType = Typed::kNoType;
            }
        }
        
};

#endif
