/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#pragma once

#include "instructions.hh"

using namespace std;

/*
 Typing visitor: to be used when knowing the exact type of the currenty compiled value is needed.
 */

struct TypingVisitor : public InstVisitor {
    Typed::VarType fCurType{Typed::kNoType};

    TypingVisitor() = default;

    ~TypingVisitor() override = default;

    void visit(LoadVarInst* inst) override
    {
        // dump2FIR(inst);

        // Stack or struct variables
        if (gGlobal->hasVarType(inst->getName())) {
            fCurType      = gGlobal->getVarType(inst->getName());
            auto* indexed = dynamic_cast<IndexedAddress*>(inst->fAddress);
            if (indexed) {
                // IndexedAddress is also used for struct type
                DeclareStructTypeInst* struct_type = isStructType(indexed->getName());
                if (struct_type) {
                    auto* field_index = static_cast<Int32NumInst*>(indexed->fIndex);
                    fCurType          = struct_type->fType->getType(field_index->fNum);
                } else {
                    fCurType = Typed::getTypeFromPtr(fCurType);
                }
            }
            // Specific cases for FunArgs
        } else if (startWith(inst->getName(), "count") || startWith(inst->getName(), "sample_rate")) {
            fCurType = Typed::kInt32;
        } else {
            fCurType = Typed::kNoType;
        }
    }

    void visit(TeeVarInst* inst) override
    {
        if (gGlobal->hasVarType(inst->getName())) {
            fCurType = gGlobal->getVarType(inst->getName());
        } else {
            fCurType = Typed::kNoType;
        }
    }

    void visit(LoadVarAddressInst* inst) override
    {
        // Not implemented
        faustassert(false);
    }

    void visit(FloatNumInst* inst) override { fCurType = Typed::kFloat; }

    void visit(Int32NumInst* inst) override { fCurType = Typed::kInt32; }

    void visit(Int64NumInst* inst) override { fCurType = Typed::kInt64; }

    void visit(BoolNumInst* inst) override { fCurType = Typed::kBool; }

    void visit(DoubleNumInst* inst) override { fCurType = Typed::kDouble; }

    void visit(BinopInst* inst) override
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

    void visit(::CastInst* inst) override { fCurType = inst->fType->getType(); }

    void visit(BitcastInst* inst) override { fCurType = inst->fType->getType(); }

    void visit(Select2Inst* inst) override
    {
        // Type in the one of 'then' or 'else'
        inst->fThen->accept(this);
    }

    void visit(IfInst* inst) override
    {
        // Type in the one of 'then' or 'else'
        inst->fThen->accept(this);
    }

    void visit(FunCallInst* inst) override
    {
        if (gGlobal->hasVarType(inst->fName)) {
            fCurType = gGlobal->getVarType(inst->fName);
        } else {
            // Should never happen...
            faustassert(false);
        }
    }
};

struct BasicTypingCloneVisitor : public BasicCloneVisitor {
    TypingVisitor fTypingVisitor;

    BasicTypingCloneVisitor() = default;

    // Memory
    ValueInst* visit(LoadVarInst* inst) override
    {
        fTypingVisitor.visit(inst);
        return BasicCloneVisitor::visit(inst);
    }

    // Numbers
    ValueInst* visit(FloatNumInst* inst) override
    {
        fTypingVisitor.visit(inst);
        return BasicCloneVisitor::visit(inst);
    }
    ValueInst* visit(Int32NumInst* inst) override
    {
        fTypingVisitor.visit(inst);
        return BasicCloneVisitor::visit(inst);
    }
    ValueInst* visit(Int64NumInst* inst) override
    {
        fTypingVisitor.visit(inst);
        return BasicCloneVisitor::visit(inst);
    }
    ValueInst* visit(BoolNumInst* inst) override
    {
        fTypingVisitor.visit(inst);
        return BasicCloneVisitor::visit(inst);
    }
    ValueInst* visit(DoubleNumInst* inst) override
    {
        fTypingVisitor.visit(inst);
        return BasicCloneVisitor::visit(inst);
    }

    // Numerical computation
    ValueInst* visit(BinopInst* inst) override
    {
        fTypingVisitor.visit(inst);
        return BasicCloneVisitor::visit(inst);
    }

    // Cast
    ValueInst* visit(::CastInst* inst) override
    {
        fTypingVisitor.visit(inst);
        return BasicCloneVisitor::visit(inst);
    }
    ValueInst* visit(BitcastInst* inst) override
    {
        fTypingVisitor.visit(inst);
        return BasicCloneVisitor::visit(inst);
    }

    // Function call
    ValueInst* visit(FunCallInst* inst) override
    {
        fTypingVisitor.visit(inst);
        return BasicCloneVisitor::visit(inst);
    }

    // Conditionnal
    ValueInst* visit(Select2Inst* inst) override
    {
        fTypingVisitor.visit(inst);
        return BasicCloneVisitor::visit(inst);
    }
    StatementInst* visit(IfInst* inst) override
    {
        fTypingVisitor.visit(inst);
        return BasicCloneVisitor::visit(inst);
    }
};
