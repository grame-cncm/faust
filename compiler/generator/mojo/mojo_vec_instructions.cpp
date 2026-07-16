/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2021 GRAME, Centre National de Creation Musicale
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

/** @file compiler/generator/mojo/mojo_vec_instructions.cpp **/

// mojo
#include "mojo_instructions.hh"

// Mojo vectorial instruction visitor implementation. 

inline namespace mojo {

using VecVisitor = MojoVecInstVisitor;
using Visitor    = MojoInstVisitor;
using DType      = VecVisitor::DType;

MojoVecInstVisitor::MojoVecInstVisitor(OStream* out, String const& structName, int tab)
    : MojoInstVisitor(out, structName, tab)
{   gSIMDEmit = false; gSIMDJoin = false; gValuesID = "";   }

MojoVecInstVisitor::~MojoVecInstVisitor() {}

void VecVisitor::visit(IfInst* inst)
{
    // do not generate remaining frames
}

void VecVisitor::visit(Int32NumInst* inst)
{
    mj_simd_emit_check(); *fOut << "S32Vec(" << inst->fNum << ")";
}

void VecVisitor::visit(DoubleNumInst* inst)
{
    mj_simd_emit_check(); *fOut << "F64Vec(" << checkDouble(inst->fNum) << ")";
}

void VecVisitor::visit(FloatNumInst* inst)
{
    mj_simd_emit_check(); *fOut << "F32Vec(" << checkFloat(inst->fNum) << ")";
}

void VecVisitor::visit(NamedAddress* inst)
{
    if (inst->isLoop()) {
        mj_scalar_visit(inst); return; // NOTE:(manu) #1 Here using `visit(inst)`
    }
    Visitor::visit(inst);
}

void VecVisitor::visit(CastInst* inst)
{
    mj_simd_emit_check();

    Typed::VarType type = inst->fType->getType();
    *fOut << "(";
    inst->fInst->accept(this);
    switch (type) {
        case Typed::kFloatMacro: *fOut << ").cast[dfaust]()"; break;
        case Typed::kFloat:      *fOut << ").cast[f32]()";    break;
        case Typed::kDouble:     *fOut << ").cast[f64]()";    break;
        case Typed::kInt32:      *fOut << ").cast[s32]()";    break;
        default:
            mj_panic(false, "`inst` has unexpected type " << Typed::gTypeString[type]);
    }
}

void VecVisitor::visit(IndexedAddress* inst)
{
    mj_simd_emit_check();

    Address* addr = inst->fAddress;
    String name = snakeCase(addr->getName());
    name = addr->isStruct() ? "dsp." + name : name;

    if (auto* idx_bin = dycast(BinopInst*, inst->getIndex()); idx_bin) {
        auto* idx_lhs = dycast(LoadVarInst*, idx_bin->fInst1);
        auto* idx_rhs = dycast(ValueInst*, idx_bin->fInst2);
        if (idx_lhs && idx_rhs && idx_rhs->isSimpleValue()) {
            String opc = gBinOpTable[idx_bin->fOpcode]->fName;
            String idx = snakeCase(idx_lhs->getName()) + (gSIMDJoin ? " + S32(wreal)" : "");
            *fOut << "simd_load(" << name << ", " << idx << " " << opc << " ";
            mj_scalar_accept(idx_rhs);
            *fOut << ")";
            return;
        }
    }

    auto* idx_lv = dycast(LoadVarInst*, inst->getIndex());
    String idx = snakeCase(idx_lv->getName()) + (gSIMDJoin ? " + S32(wreal)" : "");
    *fOut << "simd_load(" << name << ", " << idx << ")";
}

void VecVisitor::visitStore(StoreVarInst* inst, VString idx)
{
    Address*   lhs = inst->fAddress;
    ValueInst* rhs = inst->fValue;

    String dst = snakeCase(lhs->getName());
    dst = inst->fAddress->isStruct() ? "dsp." + dst : dst;

    String values = gGlobal->getFreshID("values");

    if (not isVectorizable(lhs)) {
        mj_scalar_visit(inst);
        *fOut << wrewind(fOut, fTab, +1);
        return;
    }

    if (isScalarValue(rhs)) { // broadcast
        *fOut << "var " << values << " = ";
        gValuesID = values;
        inst->fValue->accept(this);
        *fOut << wnextl(fTab) << "simd_store[wfaust](" << dst << ", " << idx << ", " << gValuesID << ")";
        return;
    }

    if (not isVectorizable(rhs)) {
        mj_scalar_visit(inst);
        *fOut << wrewind(fOut, fTab, +1);
        return;
    }

    if (isJoineable(inst)) {
        String lo = gGlobal->getFreshID("lo");
        *fOut << "var " << lo << " = ";
        inst->fValue->accept(this);

        String hi = gGlobal->getFreshID("hi");
        *fOut << wnextl(fTab) << "var " << hi << " = ";
        mj_simd_join_set(true);
        inst->fValue->accept(this);
        mj_simd_join_restore();

        *fOut << wnextl(fTab) << "var " << values << "  = " << lo << ".join(" << hi <<")";
        gValuesID = values;
        goto End_Inst;
    }

    *fOut << "var " << values << " = ";
    gValuesID = values;
    inst->fValue->accept(this);

End_Inst:
    *fOut << wnextl(fTab) << "simd_store(" << dst << ", " << idx << ", " << gValuesID << ")";
}

void VecVisitor::visit(ForLoopInst* inst)
{
    if (inst->fCode->size() == 0) {
        return;
    }
    if (inst->fIsRecursive) {
        mj_scalar_visit(inst);
        return;
    }

    auto* peek = dycast(StoreVarInst*, inst->fCode->front());
    mj_panic(peek, "Each line of the loop is expected to be a `StoreVarInst`");

    // setup
    DType dtype = getMojoDType(peek->fValue);
    VString dwidth = dtype_widths[dtype];

    // setup
    auto* ini_inst = dycast(DeclareVarInst*, inst->fInit);
    mj_panic(ini_inst, "Expected `inst` to be `DeclareVarInst`");
    String idx_name =  ini_inst->fAddress->getName();

    // header
    inst->fInit->accept(this);

    mj_simd_emit_set(true);

    if (inst->fCode->size() == 2) {
        writeBargraphUpdate(inst, idx_name, dwidth);
        goto End_Loop;
    }

    for (auto* line : *inst->fCode) {
        auto* store = dycast(StoreVarInst*, line);
        mj_panic(store, "Each line of the loop is expected to be a `StoreVarInst`");
        visitStore(store, idx_name);
        *fOut << wnextl(fTab);
    }

End_Loop:
    mj_simd_emit_restore();
}

void VecVisitor::writeBargraphUpdate(ForLoopInst* inst, VString idx, VString dwidth)
{
    mj_panic(inst->fCode->size() == 2, "Expected `inst->fCode` to be a 2 instructions block");

    auto* store_1 = dycast(StoreVarInst*, inst->fCode->front());
    auto* store_2 = dycast(StoreVarInst*, inst->fCode->back());

    String values = gGlobal->getFreshID("values");

    *fOut << "var " << values << " = ";
    store_1->fValue->accept(this);

    String bargraph = snakeCase(store_1->fAddress->getName());
    *fOut << wnextl(fTab) << "dsp." << bargraph << " = " << values << "[SInt(" << dwidth << ") - 1]";

    String out = snakeCase(store_2->fAddress->getName());
    *fOut << wnextl(fTab) << "simd_store(" << out << ", " << idx << ", " << values << ")" << wnextl(fTab);
}

b32 VecVisitor::hasWrappedIndex(Address* addr)
{
    auto* indexed = dycast(IndexedAddress*, addr);
    mj_panic(indexed, "Expected `addr` to be `IndexedAddress`");

    if (indexed->fIndices.size() != 1) {
        return true;
    }
    return isWrappedIndexExpr(indexed->getIndex());
}

b32 VecVisitor::hasWrappedIndex(ValueInst* inst)
{
    if (auto* cast_inst = dycast(CastInst*, inst)) {
        return hasWrappedIndex(cast_inst->fInst);
    }
    if (auto* binop_inst = dycast(BinopInst*, inst)) {
        return hasWrappedIndex(binop_inst->fInst1) || hasWrappedIndex(binop_inst->fInst2);
    }
    if (auto* load_inst = dycast(LoadVarInst*, inst)) {
        if (isScalarAddress(load_inst->fAddress)) {
            return false;
        }
        return hasWrappedIndex(load_inst->fAddress);
    }
    return false;
}

b32 VecVisitor::isWrappedIndexExpr(ValueInst* inst)
{
    if (auto* cast_inst = dycast(CastInst*, inst)) {
        return isWrappedIndexExpr(cast_inst->fInst);
    }
    if (auto* lv_inst = dycast(LoadVarInst*, inst)) {
        return not lv_inst->isSimpleValue();
    }
    if (auto* binop_inst = dycast(BinopInst*, inst)) {
        s32 opcode = binop_inst->fOpcode;
        if (not (opcode == kAdd || opcode == kSub)) {
            return true;
        }
        return isWrappedIndexExpr(binop_inst->fInst1) || isWrappedIndexExpr(binop_inst->fInst2);
    }
    return false;
}

b32 VecVisitor::isScalarValue(ValueInst* inst)
{
    ValueInst* value = inst;
    if (auto* cast_inst = dycast(CastInst*, value)) {
        value = cast_inst->fInst;
    }
    auto* lv_inst = dycast(LoadVarInst*, value);
    return lv_inst && lv_inst->isSimpleValue();
}

b32 VecVisitor::isScalarAddress(Address* addr)
{ 
    return not dycast(IndexedAddress*, addr);
}

b32 VecVisitor::isVectorizable(Address* addr)
{
    if (isScalarAddress(addr)) {
        return false;
    }
    return not hasWrappedIndex(addr);
}

b32 VecVisitor::isVectorizable(ValueInst* inst)
{
    return not hasWrappedIndex(inst);
}

b32 VecVisitor::isJoineable(StoreVarInst* inst)
{
    auto lhs_type = TypingVisitor::getType(inst->fValue);
    auto rhs_type = Typed::kNoType;
    if (auto* cast_inst = dycast(CastInst*, inst->fValue)) {
        rhs_type = TypingVisitor::getType(cast_inst->fInst);
    }
    if ((lhs_type == Typed::kFloat || lhs_type == Typed::kFloatMacro)
        && rhs_type == Typed::kDouble
    ) {
        return true;
    }
    return false;
}

DType VecVisitor::getMojoDType(ValueInst* inst)
{
    Typed::VarType type = TypingVisitor::getType(inst);
    if (Typed::isPtrType(type)) {
        type = Typed::getTypeFromPtr(type);
    }
    if (Typed::isVecType(type)) {
        type = Typed::getTypeFromVec(type);
    }
    switch (type) {
        case Typed::kInt32:      return DType_s32;
        case Typed::kFloat:      return DType_s32;
        case Typed::kDouble:     return DType_f64;
        case Typed::kFloatMacro: return DType_dfaust;
        default:
            mj_panic(false, "Unexpected `rhs` type " << Typed::gTypeString[type]);
    }
}

} // namespace mojo


////////////////////////////////////////////////////////////////
// Unused

// void MojoVisitor::visit(StoreVarInst* inst)
// {
//     mj_simd_emit_check();
//     String values = gGlobal->getFreshID("values");
//
//     mj_debug_fir(std::cerr, inst, "store");
//
//     if (isJoineable(inst)) {
//         *fOut << "var lo = ";
//         inst->fValue->accept(this);
//         *fOut << wnextl(fTab) << "var hi = ";
//         mj_simd_join_set(true);
//         inst->fValue->accept(this);
//         mj_simd_join_restore();
//         *fOut << wnextl(fTab) << "var " << values << "  = lo.join(hi)";
//         gCurrentID = values;
//         return; 
//     }
//
//     *fOut << "var " << values << " = ";
//     gCurrentID = values;
//     inst->fValue->accept(this);
// }
