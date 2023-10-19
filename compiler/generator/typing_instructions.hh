/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#ifndef _TYPING_INSTRUCTIONS_H
#define _TYPING_INSTRUCTIONS_H

#include "instructions.hh"

/*
 Typing visitor: to be used when knowing the exact type of the currenty compiled value is needed.
 */

struct TypingVisitor : public InstVisitor {
    Typed::VarType fCurType;

    TypingVisitor() : fCurType(Typed::kNoType) {}

    virtual ~TypingVisitor() {}

    virtual void visit(LoadVarInst* inst)
    {
        std::string name = inst->getName();
        // Stack or struct variables
        if (gGlobal->hasVarType(name)) {
            fCurType                = gGlobal->getVarType(name);
            IndexedAddress* indexed = dynamic_cast<IndexedAddress*>(inst->fAddress);
            if (indexed) {
                // IndexedAddress is also used for struct type
                DeclareStructTypeInst* struct_type = isStructType(indexed->getName());
                if (struct_type) {
                    Int32NumInst* field_index = static_cast<Int32NumInst*>(indexed->getIndex());
                    fCurType                  = struct_type->fType->getType(field_index->fNum);
                } else {
                    fCurType = Typed::getTypeFromPtr(fCurType);
                }
            }
        } else {
            fCurType = Typed::kNoType;
            std::cerr << "ASSERT : TypingVisitor : variable '" << name << "' has Typed::kNoType" << std::endl;
            faustassert(false);
        }
    }

    virtual void visit(TeeVarInst* inst)
    {
        std::string name = inst->getName();
        if (gGlobal->hasVarType(name)) {
            fCurType = gGlobal->getVarType(name);
        } else {
            fCurType = Typed::kNoType;
            std::cerr << "ASSERT : TypingVisitor : variable '" << name << "' has Typed::kNoType" << std::endl;
            faustassert(false);
        }
    }

    virtual void visit(LoadVarAddressInst* inst)
    {
        // Not implemented
        faustassert(false);
    }

    virtual void visit(FloatNumInst* inst) { fCurType = Typed::kFloat; }

    virtual void visit(Int32NumInst* inst) { fCurType = Typed::kInt32; }

    virtual void visit(Int64NumInst* inst) { fCurType = Typed::kInt64; }

    virtual void visit(BoolNumInst* inst) { fCurType = Typed::kBool; }

    virtual void visit(DoubleNumInst* inst) { fCurType = Typed::kDouble; }
    
    virtual void visit(MinusInst* inst)
    {
        inst->fInst->accept(this);
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
                } else if (isInt32Type(type1) || isInt32Type(type2)) {
                    fCurType = Typed::kInt32;
                } else if (isInt64Type(type1) || isInt64Type(type2)) {
                    fCurType = Typed::kInt64;
                } else if (isBoolType(type1) && isBoolType(type2)) {
                    fCurType = Typed::kInt32;
                } else {
                    // Should never happen...
                    std::cerr << "ASSERT : TypingVisitor : BinopInst a1 = ";
                    std::cerr << Typed::gTypeString[type1] << " a2 = " << Typed::gTypeString[type2] << std::endl;
                    faustassert(false);
                }
            }
        }
    }

    virtual void visit(::CastInst* inst) { fCurType = inst->fType->getType(); }

    virtual void visit(BitcastInst* inst) { fCurType = inst->fType->getType(); }

    virtual void visit(Select2Inst* inst)
    {
        // Type is the one of 'then' or 'else'
        inst->fThen->accept(this);
    }

    virtual void visit(FunCallInst* inst)
    {
        if (gGlobal->hasVarType(inst->fName)) {
            fCurType = gGlobal->getVarType(inst->fName);
        } else {
            // Should never happen...
            std::cerr << "ASSERT : TypingVisitor::visit(FunCallInst* inst) name " << inst->fName << std::endl;
            faustassert(false);
        }
    }
    
    static Typed::VarType getType(ValueInst* value)
    {
        TypingVisitor typing;
        value->accept(&typing);
        return typing.fCurType;
    }
    
};

#endif
