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

MojoVecInstVisitor::MojoVecInstVisitor(OStream* out, const String& structName, int tab)
    : MojoInstVisitor(out, structName, tab)
{   
    gEmitSIMD = false;   
    gEmitJoin = false;
}

void MojoVecInstVisitor::visit(CastInst* inst)
{
    mj_emit_simd_check();

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
void MojoVecInstVisitor::visit(DoubleNumInst* inst)
{
    mj_emit_simd_check();
    *fOut << "F64Vec(" << checkDouble(inst->fNum) << ")";
}
void MojoVecInstVisitor::visit(FloatNumInst* inst)
{
    mj_emit_simd_check();
    *fOut << "F32Vec(" << checkFloat(inst->fNum) << ")";
}

void MojoVecInstVisitor::visit(IndexedAddress* inst)
{
    mj_emit_simd_check();

    Address* addr = inst->fAddress;
    String src_name = snakeCase(addr->getName());
    src_name = addr->isStruct() ? "dsp." + src_name : src_name;

    // XXX:(manu) 
    // - Should the index shape be already checked here?
    //   > I am assuming it is.
    if (auto* idx = dycast(BinopInst*, inst->fIndices[0]); idx) {
        auto* idx_lhs = dycast(LoadVarInst*, idx->fInst1);
        auto* idx_rhs = dycast(ValueInst*, idx->fInst2);
        if (idx_lhs && idx_rhs && idx_rhs->isSimpleValue()) {
            String idx_name = idx_lhs->getName() + (gEmitJoin ? " + S32(wreal)" : "");
            *fOut << "simd_load(" << src_name << ", " << idx_name << " " << gBinOpTable[idx->fOpcode]->fName << " ";
            mj_emit_simd_set(false);
            idx_rhs->accept(this);
            mj_emit_simd_restore();
            *fOut << ")";
            return;
        }
    }

    auto* idx = dycast(LoadVarInst*, inst->fIndices[0]);
    String idx_name = snakeCase(idx->getName()) + (gEmitJoin ? " + S32(wreal)" : "");
    *fOut << "simd_load(" << src_name << ", " << idx_name << ")";

    // XXX:(manu) Do I need a fallback?
}

void MojoVecInstVisitor::visit(Int32NumInst* inst)
{
    mj_emit_simd_check();
    *fOut << "S32Vec(" << inst->fNum << ")";
}

void MojoVecInstVisitor::visit(NamedAddress* inst)
{
    if (inst->isLoop()) {
        mj_emit_simd_set(false);
        MojoInstVisitor::visit(inst);
        mj_emit_simd_restore();
        return;
    }
    MojoInstVisitor::visit(inst);
}

b32 MojoVecInstVisitor::mustEmitJoin(StoreVarInst* inst)
{
    // auto rhs_type = Typed::kNoType;
    // auto lhs_type = Typed::kNoType;
    // if (auto* cast_inst = dycast(CastInst*, inst->fValue)) {
    //     lhs_type = TypingVisitor::getType(cast_inst);
    //     if (auto* binop_inst = dycast(BinopInst*, cast_inst->fInst)) {
    //         rhs_type = TypingVisitor::getType(binop_inst);
    //     }
    // }

    auto lhs_type = TypingVisitor::getType(inst->fValue);
    auto rhs_type = Typed::kNoType;
    if (auto* cast_inst = dycast(CastInst*, inst->fValue)) {
        rhs_type = TypingVisitor::getType(cast_inst->fInst);
    }
    b32 lhs_small_width = (lhs_type == Typed::kDouble) ||
                          (lhs_type == Typed::kFloatMacro && std::is_same_v<FAUSTFLOAT, float>);
    if (lhs_small_width && rhs_type == Typed::kDouble) {
        return true;
    }
    printf("%d\n", lhs_type);
    printf("%d\n", rhs_type);
    return false;
}

void MojoVecInstVisitor::visit(StoreVarInst* inst)
{
    mj_emit_simd_check();
    String values = gGlobal->getFreshID("values");

    // mj_debug_fir(std::cerr, inst->fAddress, "StoreVarInst");
    // mj_debug_fir(std::cerr, inst->fValue, "StoreVarInst");

    if (mustEmitJoin(inst)) {
        *fOut << "var lo = ";
        inst->fValue->accept(this);
        gEmitJoin = true;
        *fOut << wnextl(fTab) << "var hi = ";
        inst->fValue->accept(this);
        *fOut << wnextl(fTab) << "var " << values << "  = lo.join(hi)";
        gLastValueID = values;
        gEmitJoin = false;
        return; 
    }

    *fOut << "var " << values << " = ";
    gLastValueID = values;
    inst->fValue->accept(this);
}

void MojoVecInstVisitor::visit(IfInst* inst)
{
    // stop generation of remaining frames
}

void MojoVecInstVisitor::visitStore(StoreVarInst* inst, String& idx_name)
{
    if (not isUnitStride(inst->fAddress) || hasWrappedIndex(inst->fValue)) {
        mj_emit_scalar(inst);
        *fOut << wrewind(fOut, fTab, +1);
        return;
    }
    inst->accept(this);
    String dst_name = snakeCase(inst->fAddress->getName());
    dst_name = inst->fAddress->isStruct() ? "dsp." + dst_name : dst_name;
    *fOut << wnextl(fTab) << "simd_store(" << dst_name << ", "
          << idx_name << ", " << gLastValueID << ")";
}

void MojoVecInstVisitor::writeBargraphUpdate(ForLoopInst* inst, String& idx_name, String& dwidth)
{
    mj_panic(inst->fCode->size() == 2, "Expected `inst->fCode` to be a 2 instructions block");

    auto* store_1 = dycast(StoreVarInst*, inst->fCode->front());
    auto* store_2 = dycast(StoreVarInst*, inst->fCode->back());

    String values = gGlobal->getFreshID("values");

    *fOut << wnextl(fTab) << "var " << values << " = ";
    store_1->fValue->accept(this);

    String bargraph_name = snakeCase(store_1->fAddress->getName());
    *fOut << wnextl(fTab) << "dsp." << bargraph_name << " = "
          << values << "[SInt(" << dwidth << ") - 1]";

    String output_name = snakeCase(store_2->fAddress->getName());
    *fOut << wnextl(fTab) << "simd_store(" << output_name << ", " << idx_name << ", " << values << ")";
}

void MojoVecInstVisitor::visit(ForLoopInst* inst)
{
    if (inst->fCode->size() == 0) {
        return;
    }
    if (inst->fIsRecursive) {
        mj_emit_scalar(inst);
        return;
    }

    auto* peek = dycast(StoreVarInst*, inst->fCode->front());
    mj_panic(peek, "Each line of the loop is expected to be a `StoreVarInst`");

    // setup
    auto dtype = getDType(peek->fValue);
    auto dwidth = dtype_widths[dtype];

    // setup
    auto* ini_inst = dycast(DeclareVarInst*, inst->fInit);
    mj_panic(ini_inst, "Expected `inst` to be `DeclareVarInst`");
    String idx_name =  ini_inst->fAddress->getName();
    auto* end_inst = dycast(BinopInst*, inst->fEnd);
    mj_panic(end_inst, "Expected `inst` to be `BinopInst`");
    auto end_val = end_inst->fInst2;

    // header
    inst->fInit->accept(this);
    *fOut << "while " << idx_name << " <= ";
    end_val->accept(this);
    *fOut << " - " << dwidth << ":";

    mj_emit_simd_set(true);

    // body
    fTab += 1;

    if (inst->fCode->size() == 2) {
        writeBargraphUpdate(inst, idx_name, dwidth);
        goto End_Loop;
    }

    for (auto* line : *inst->fCode) {
        auto* store = dycast(StoreVarInst*, line);
        mj_panic(store, "Each line of the loop is expected to be a `StoreVarInst`");
        *fOut << wnextl(fTab);
        visitStore(store, idx_name);
    }

End_Loop:
    // increment
    *fOut << wnextl(fTab) << idx_name << " = " << idx_name << " + " << dwidth;

    // end
    mj_emit_simd_restore();
    fTab -= 1;
    *fOut << wnextl(fTab);
}

b32 MojoVecInstVisitor::hasWrappedIndex(Address* addr)
{
    auto* indexed = dycast(IndexedAddress*, addr);
    if (not (indexed)) {
        // return true; // TODO:
        return false;   // What should I do for scalars?
    }

    Arr<ValueInst*>& indices = indexed->fIndices;
    if (indices.size() != 1) {
        return true;
    }

    auto* idx = dycast(LoadVarInst*, indices[0]);
    if (idx && not idx->isSimpleValue()) {
        return true;
    }

    auto* cast_inst = dycast(BinopInst*, indices[0]);
    if (cast_inst) {
        s32 opcode = cast_inst->fOpcode;
        if (not (opcode == kAdd || opcode == kSub)) {
            return true; 
        }
        return hasWrappedIndex(cast_inst->fInst1) || hasWrappedIndex(cast_inst->fInst2);
    }

    return false;
}

b32 MojoVecInstVisitor::hasWrappedIndex(ValueInst* inst)
{ 
    if (auto* cast_inst = dycast(CastInst*, inst)) {
        return hasWrappedIndex(cast_inst->fInst);
    }
    if (auto* binop_inst = dycast(BinopInst*, inst)) {
        return hasWrappedIndex(binop_inst->fInst1) || hasWrappedIndex(binop_inst->fInst2);
    }
    if (auto* load_inst = dycast(LoadVarInst*, inst)) {
        // XXX:(manu) should I handle LoadVarAddressInst?
        return hasWrappedIndex(load_inst->fAddress);
    }
    return false;
}

// actual shape only works with expected lhs of store
b32 MojoVecInstVisitor::isUnitStride(Address* addr)
{
    // TODO:(manu)
    // ! should accept also `A[i + off]`
    // ? probably I am matching the lhs shape too strictly

    IndexedAddress* indexed = dycast(IndexedAddress*, addr);
    if (not(indexed && indexed->fIndices.size() == 1)) {
        return false;
    }
    auto* idx = dycast(LoadVarInst*, indexed->fIndices[0]);
    if (not(idx && idx->isSimpleValue())) {
        return false;
    }
    auto* idx_addr = dycast(Address*, idx->fAddress);
    if (not(idx_addr && idx_addr->isLoop())) {
        return false;
    }
    return true;
} 

DType MojoVecInstVisitor::getDType(ValueInst* inst)
{
    ValueInst* value = inst;
    mj_debug_fir(std::cerr, inst, "getDType");
    // if (auto* cast_inst = dycast(CastInst*, inst)) {
    //     value = cast_inst->fInst;
    // }

    Typed::VarType type = TypingVisitor::getType(value);
    if (Typed::isPtrType(type)) {
        type = Typed::getTypeFromPtr(type);
    }
    if (Typed::isVecType(type)) {
        type = Typed::getTypeFromVec(type);
    }
    String dtype_value;
    switch (type) {
        case Typed::kInt32:      return DType_s32;
        case Typed::kFloat:      return DType_f32;
        case Typed::kDouble:     return DType_f64;
        case Typed::kFloatMacro: return DType_dfaust;
        default:
            mj_panic(false, "Unexpected `rhs` type " << Typed::gTypeString[type]);
    }
}

} // namespace mojo


////////////////////////////////////////////
// Unused

// void MojoVecInstVisitor::writeMultiBargraph(
//     ForLoopInst* inst
// ) {
//     mj_emit_simd_set(true);
//     for (auto* line : *inst->fCode) {
//         line->accept(this);
//     }
//     mj_emit_simd_restore();
// }
