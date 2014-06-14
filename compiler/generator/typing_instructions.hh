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
                fCurType = Typed::kNoType;
            }
        }

        virtual void visit(LoadVarAddressInst* inst)
        {   
            // Not implemented in JAVA
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
    
        virtual void visit(BinopInst* inst)
        {
            if (inst->fOpcode >= kGT && inst->fOpcode < kAND) {
                fCurType = Typed::kBool;
            } else {
                
                inst->fInst1->accept(this);
                Typed::VarType type1 = fCurType;
                 
                inst->fInst2->accept(this);
                Typed::VarType type2 = fCurType;
                             
                if (type1 == Typed::kInt && type2 == Typed::kInt) {
                    fCurType = Typed::kInt;
                } else if (type1 == Typed::kInt && (type2 == Typed::kFloat || type2 == Typed::kFloatMacro || type2 == Typed::kDouble)) {
                    fCurType = Typed::kFloat;
                } else if ((type1 == Typed::kFloat || type1 == Typed::kFloatMacro || type1 == Typed::kDouble) && type2 == Typed::kInt) {
                    fCurType = Typed::kFloat;   
                } else if ((type1 == Typed::kFloat || type1 == Typed::kFloatMacro || type1 == Typed::kDouble) 
                           && (type2 == Typed::kFloat || type2 == Typed::kFloatMacro || type2 == Typed::kDouble)) {
                    fCurType = Typed::kFloat;
                } else if (type1 == Typed::kInt && type2 == Typed::kBool) {
                    fCurType = Typed::kInt;
                } else if (type1 == Typed::kBool && type2 == Typed::kInt) {
                    fCurType = Typed::kInt;
                } else if (type1 == Typed::kBool && type2 == Typed::kBool) {
                   fCurType = Typed::kInt;
                } else if ((type1 == Typed::kFloat || type1 == Typed::kFloatMacro || type1 == Typed::kDouble) && type2 == Typed::kBool) {
                    fCurType = Typed::kFloat;
                } else if (type1 == Typed::kBool && (type2 == Typed::kFloat || type2 == Typed::kFloatMacro || type2 == Typed::kDouble)) {
                    fCurType = Typed::kFloat;
                } else { // Default
                    fCurType = Typed::kNoType;
                }   
            }
        }

        virtual void visit(CastNumInst* inst)
        {
            fCurType = inst->fType->getType();
        }
      
        virtual void visit(Select2Inst* inst)
        {
            // Type in the one of then or else
            inst->fThen->accept(this);
        }
        
};

#endif
