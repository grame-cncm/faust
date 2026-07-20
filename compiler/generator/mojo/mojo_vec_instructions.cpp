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

using namespace std;

using VecVisitor  = MojoVecInstVisitor;
using BaseVisitor = MojoInstVisitor;
using DType       = VecVisitor::DType;

MojoVecInstVisitor::MojoVecInstVisitor(OStream* out, String const& structName, int tab)
    : MojoInstVisitor(out, structName, tab)
{
    gSIMDEmit = false;
    gSIMDJoin = false;
    gSIMDSize  = gGlobal->gVecSize;
    gCurValue = "";
    gCurWidth = "";
    gCurIndex = "";
}

MojoVecInstVisitor::~MojoVecInstVisitor() {}

void VecVisitor::visit(IfInst* inst)
{   /* do not generate remaining frames */   }

void VecVisitor::visit(Int32NumInst* inst)
{
    mj_simd_emit_check(); *fOut << "S32Vec(" << inst->fNum << ")";
}

void VecVisitor::visit(DoubleNumInst* inst)
{
    mj_simd_emit_check(); *fOut << "F64Vec(" << checkDouble(inst->fNum) << ")";
}

void MojoVecInstVisitor::visit(DeclareVarInst* inst)
{
    String name = inst->getName();
    if (name.find("vsize") != String::npos) {
        *fOut << "comptime " << name << " = " << "S32(" << gSIMDSize << ")" << wnextl(fTab);
        return;
    }
    MojoInstVisitor::visit(inst);
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
    BaseVisitor::visit(inst);
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
    String idx = gSIMDJoin ? ", S32(w64)" : "";
    String func = "vload" + (gCurWidth != "" ? "[" + gCurWidth + "]" : "");

    if (auto* idx_bin = dycast(BinopInst*, inst->getIndex()); idx_bin) {
        auto* idx_lhs = dycast(LoadVarInst*, idx_bin->fInst1);
        auto* idx_rhs = dycast(ValueInst*, idx_bin->fInst2);
        if (idx_lhs && idx_rhs && idx_rhs->isSimpleValue()) {
            String opc = gBinOpTable[idx_bin->fOpcode]->fName;
            *fOut << func << "(" << name << idx << " " << opc << " ";
            mj_scalar_accept(idx_rhs);
            *fOut << ")";
            return;
        }
    }

    *fOut << func << "(" << name << idx << ")";
}

void VecVisitor::visitStore(StoreVarInst* inst)

void VecVisitor::visit(StoreVarInst* inst)
{
    Address*   lhs = inst->fAddress;
    ValueInst* rhs = inst->fValue;

    String dst = snakeCase(lhs->getName());
    dst = inst->fAddress->isStruct() ? "dsp." + dst : dst;

    String value = gGlobal->getFreshID("value");
    gCurValue = value;

    if (not isVectorizable(lhs)) {
        mj_scalar_visit(inst);
        *fOut << wrewind(fOut, fTab, +1);
        return;
    }

    if (isScalarValue(rhs)) { // broadcast
        *fOut << "var " << value << " = ";
        gCurValue = value;
        inst->fValue->accept(this);
        *fOut << wnextl(fTab) << "vstore[wfaust](" << dst << ", " << gCurIndex << ", " << gCurValue << ")";
        return;
    }

    if (not isVectorizable(rhs)) {
        mj_scalar_visit(inst);
        *fOut << wrewind(fOut, fTab, +1);
        return;
    }

    if (isJoinable(inst)) {
        gCurWidth = "w64";
        *fOut << "lo = ";
        inst->fValue->accept(this);
        *fOut << wnextl(fTab) << "hi = ";
        mj_simd_join_set(true);
        inst->fValue->accept(this);
        mj_simd_join_restore();
        *fOut << wnextl(fTab) << "var " << value << " = lo.join(hi)";
        *fOut << wnextl(fTab) << "vstore(" << dst << ", S32(0), " << value << ")";
        return;
    }

    *fOut << "var " << value << " = ";
    inst->fValue->accept(this);
    *fOut << wnextl(fTab) << "vstore(" << dst << ", " << gCurIndex << ", " << value << ")";
}

void VecVisitor::visit(ForLoopInst* inst)
{
    if (inst->fCode->size() == 0) {
        return;
    }
    if (inst->fIsRecursive) {
        mj_scalar_visit(inst); return;
    }

    auto* ini_inst = dycast(DeclareVarInst*, inst->fInit);
    mj_panic(ini_inst, "Expected `inst` to be `DeclareVarInst`");
    gCurIndex = ini_inst->fAddress->getName();
    gCurValue = gGlobal->getFreshID("value");


    if (inst->fCode->size() > 2) {
        return visitBargraphMulti(inst);
    }

    if (inst->fCode->size() == 2) {
        return visitBargraphUpdate(inst);
    }

    auto* store = dycast(StoreVarInst*, inst->fCode->back());
    mj_panic(store, "Expected final instruction to be a `StoreVarInst`");

    Address* lhs = store->fAddress;
    ValueInst* rhs = store->fValue;
    gCurAddrs = snakeCase(lhs->getName());
    gCurAddrs = lhs->isStruct() ? "dsp." + gCurAddrs : gCurAddrs;
    DType lhs_type = getMojoDType(rhs);
    DType rhs_type = lhs_type;
    if (auto* cast_inst = dycast(CastInst*, rhs)) {
        rhs_type = getMojoDType(cast_inst->fInst);
    }

    if (not isVectorizable(lhs)) {
        mj_scalar_visit(inst); return;
    }

    if (isScalarValue(rhs)) {
        inst->fInit->accept(this);
        visitBroadcast(store);
        goto End_Loop;
    }

    if (not isVectorizable(rhs)) {
        mj_scalar_visit(inst); return;
    }

    inst->fInit->accept(this);

    if (lhs_type == DType_f64) {
        // TODO:
        // visitUnroll(store); goto End_Loop;
        return;
    }

    if (rhs_type == DType_f64) {
        visitJoin(store); goto End_Loop;
    }

    *fOut << "var " << gCurValue << " = ";
    store->fValue->accept(this);
    *fOut << wnextl(fTab) << "vstore(" << gCurAddrs << ", " << gCurIndex << ", " << gCurValue << ")";

End_Loop:
    *fOut << wnextl(fTab);
    gCurIndex.clear();
    gCurWidth.clear();
    gCurValue.clear();
}

void VecVisitor::visitLoop(ForLoopInst* inst)
{
    if (inst->fCode->size() == 0) {
        return;
    }
    if (inst->fIsRecursive) {
        mj_scalar_visit(inst); return;
    }

    // setup
    auto* ini_inst = dycast(DeclareVarInst*, inst->fInit);
    mj_panic(ini_inst, "Expected `inst` to be `DeclareVarInst`");
    gCurIndex = ini_inst->fAddress->getName();

    // single bargraph + single store
    if (inst->fCode->size() == 2) {
        return visitBargraphUpdate(inst);
    }

    Arr<StoreVarInst*> bars;
    StoreVarInst* store = dycast(StoreVarInst*, inst->fCode->back());

    if (inst->fCode->size() > 2) {
        for (auto* line : *inst->fCode) {
            auto* sv_inst = dycast(StoreVarInst*, line);
            mj_panic(sv_inst, "Each line of the loop is expected to be a `StoreVarInst`");
            String name = sv_inst->fAddress->getName();
            if (name.find("bargraph") != String::npos) {
                bars.push_back(sv_inst);
            }
        }
    }

    if (bars.size() > 0) {
        fTab += 1;
        *fOut << "comptime for " << gCurIndex + " in range(" << "S32(0), S32(" << gSIMDSize << ")):" << wnextl(fTab);
        for (auto* bar : bars) {
            mj_scalar_visit(bar);
        }
        fTab -= 1;
        wrewind(fOut, 1);
    }

    // header
    inst->fInit->accept(this);

    mj_simd_emit_set(true);

    // if (inst->fCode->size() == 2) {
    //     writeBargraphUpdate(inst, idx, dwidth);
    //     goto End_Loop;
    // }

    // for (auto* line : *inst->fCode) {
    //     auto* store = dycast(StoreVarInst*, line);
    //     mj_panic(store, "Each line of the loop is expected to be a `StoreVarInst`");
    //     visitStore(store, idx);
    //     *fOut << wnextl(fTab);
    // }

    visitStore(store);
    *fOut << wnextl(fTab);
        
// End_Loop:
    gCurIndex = "";
    mj_simd_emit_restore();
}

void VecVisitor::visitBargraphUpdate(ForLoopInst* inst)
{
    mj_panic(inst->fCode->size() == 2, "Expected `inst->fCode` to be a 2 instructions block");

    auto* store_1 = dycast(StoreVarInst*, inst->fCode->front());
    auto* store_2 = dycast(StoreVarInst*, inst->fCode->back());
    String bargraph = snakeCase(store_1->fAddress->getName());
    String out = snakeCase(store_2->fAddress->getName());
    String value = gGlobal->getFreshID("value");

    inst->fInit->accept(this);
    *fOut << "var " << value << " = ";
    mj_simd_emit_set(true);
    store_1->fValue->accept(this);
    mj_simd_emit_restore();
    *fOut << wnextl(fTab) << "dsp." << bargraph << " = " << value << "[wfaust - 1]";
    *fOut << wnextl(fTab) << "vstore(" << out << ", " << gCurIndex << ", " << value << ")" << wnextl(fTab);
}

void MojoVecInstVisitor::visitBargraphMulti(ForLoopInst* inst)
{
    Arr<StoreVarInst*> bars;
    auto* store = dycast(StoreVarInst*, inst->fCode->back());
    mj_panic(store, "Expected final instruction to be a `StoreVarInst`");
    for (auto* line : *inst->fCode) {
        auto* sv_inst = dycast(StoreVarInst*, line);
        mj_panic(sv_inst, "Expected each loop instruction to be a `StoreVarInst`");
        if (sv_inst->fAddress->getName().find("bargraph") != String::npos) {
            bars.push_back(sv_inst);
        }
    }
    mj_panic(bars.size() > 1, "Expected at least two bargraph instruction");
    fTab += 1;
    *fOut << "comptime for " << gCurIndex << " in range(S32(0), S32(" << gSIMDSize
          << ")):" << wnextl(fTab);
    for (auto* bar : bars) {
        mj_scalar_visit(bar);
    }
    fTab -= 1;
    wrewind(fOut, 1);
}

void MojoVecInstVisitor::visitJoin(StoreVarInst* inst)
{
    gCurWidth = "w64";
    *fOut << "lo = ";
    inst->fValue->accept(this);
    *fOut << wnextl(fTab) << "hi = ";
    mj_simd_join_set(true);
    inst->fValue->accept(this);
    mj_simd_join_restore();
    *fOut << wnextl(fTab) << "var " << gCurValue << " = lo.join(hi)";
    *fOut << wnextl(fTab) << "vstore(" << gCurAddrs << ", S32(0), " << gCurValue << ")";
    return;
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
    while (auto cast_inst = dycast(CastInst*, value)) {
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

b32 VecVisitor::isJoinable(StoreVarInst* inst)
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
//     String value = gGlobal->getFreshID("value");
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
//         *fOut << wnextl(fTab) << "var " << value << "  = lo.join(hi)";
//         gCurrentID = value;
//         return; 
//     }
//
//     *fOut << "var " << value << " = ";
//     gCurrentID = value;
//     inst->fValue->accept(this);
// }
