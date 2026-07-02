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
    case Typed::kFloatMacro:
        *fOut << ").cast[dfaust]()";
        break;
    case Typed::kFloat:
    case Typed::kDouble:
        *fOut << ").cast[dreal]()";
        break;
    case Typed::kInt32:
        *fOut << ").cast[s32]()";
        break;
    default:
        mj_panic(false, "`inst` has unexpected type " << Typed::gTypeString[type]);
    }
}

void MojoVecInstVisitor::visit(IndexedAddress* inst)
{
    mj_emit_simd_check();

    Address* addr = inst->fAddress;
    String src_name = snakeCase(addr->getName());
    src_name = addr->isStruct() ? "dsp." + src_name : src_name;

    // XXX:(manu) assumings a shape like A[i] or A[i + off]
    // at this point should be already checked.
    if (auto* idx = dycast(BinopInst*, inst->fIndices[0]); idx) {
        auto* idx_lhs = dycast(LoadVarInst*, idx->fInst1);
        auto* idx_rhs = dycast(ValueInst*, idx->fInst2);
        if (idx_lhs && idx_rhs && idx_rhs->isSimpleValue()) {
            String idx_name = idx_lhs->getName() + (gEmitJoin ? " + S32(dreal_width)" : "");
            *fOut << "simd_load(" << src_name << ", " << idx_name << " " << gBinOpTable[idx->fOpcode]->fName << " ";
            idx_rhs->accept(this);
            *fOut << ")";        
            return;
        }
    }

    auto* idx = dycast(LoadVarInst*, inst->fIndices[0]);
    String idx_name = snakeCase(idx->getName()) + (gEmitJoin ? " + S32(dreal_width)" : "");
    *fOut << "simd_load(" << src_name << ", " << idx_name << ")";

    // fallback?
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
void MojoVecInstVisitor::visit(StoreVarInst* inst)
{
    mj_emit_simd_check();
    auto* lhs = inst->fAddress;
    auto* rhs = inst->fValue;
    if (not isUnitStride(lhs) || hasWrappedIndex(rhs)) {
        MojoInstVisitor::visit(inst);
    }
    mj_emit_simd_set(true);
    lhs->accept(this);
    *fOut << " = ";
    rhs->accept(this);
    mj_emit_simd_restore();
    *fOut << wnextl(fTab);
}

void MojoVecInstVisitor::visit(LabelInst* inst)
{
    auto label = String(inst->fLabel.begin() + 1, inst->fLabel.end() - 2);
    label[0] = '#';
    *fOut << label << wnextl(fTab);
}

String getAddressName(Address* addr) {
    String name = snakeCase(addr->getName());
    return addr->isStruct() ? "dsp." + name : name;
}

void MojoVecInstVisitor::visit(ForLoopInst* inst)
{
    if (inst->fCode->size() == 0) {
        return;
    }
    if (inst->fIsRecursive) {
        return MojoInstVisitor::visit(inst);
    }

    auto* store = dycast(StoreVarInst*, inst->fCode->front());
    mj_panic(store, "The first instruction of the loop is expected to be a `StoreVarInst`");

    auto dvalue = getDTypeValue(store->fValue); 
    auto dname  = gGlobal->getFreshID("dtype");
    auto dwidth = gGlobal->getFreshID("width");

    writeSIMDLoopHeader(inst, dname, dvalue, dwidth);
    fTab += 1;

    // auto [lhs, rhs, lhs_name]    = parseSingleStore(store);  // Address*, ValueInst*, String

    if (inst->fCode->size() > 2) {
        return writeMultiBargraph(inst);
    } else {
        // mj_panic(inst->fCode->size() == 1 || inst->fCode->size() == 2, "Unexpected `ForLoopInst`
        // size");

        // if (inst->fCode->size() == 2) {
        //     return writeBargraphUpdate(inst, dname, dvalue, dwidth);
        // }

        // if ( !isUnitStride(lhs) ||  hasWrappedIndex(rhs)) {
        //     return MojoInstVisitor::visit(inst);
        // }

        mj_emit_simd_set(true);

        auto rhs_type = Typed::kNoType;
        auto lhs_type = Typed::kNoType;
        // mj_debug_fir(std::cerr, rhs, "rhs");
        // the casted expression defines the type of the lhs
        if (auto* cast_inst = dycast(CastInst*, store->fValue)) {
            lhs_type = TypingVisitor::getType(cast_inst);
            // mj_debug_msg(std::cerr, "lhs_type: " << Typed::gTypeString[lhs_type]);
            // we want the temporary type of the rhs internal computation too
            if (auto* binop_inst = dycast(BinopInst*, cast_inst->fInst)) {
                rhs_type = TypingVisitor::getType(binop_inst);
                // mj_debug_msg(std::cerr, "rhs_type: " << Typed::gTypeString[rhs_type]);
            }
        }

        // XXX:
        puts(Typed::gTypeString[lhs_type].c_str());
        puts(Typed::gTypeString[rhs_type].c_str());

        b32 lhs_small_width = (lhs_type == Typed::kDouble) ||
                              (lhs_type == Typed::kFloatMacro && std::is_same_v<FAUSTFLOAT, float>);
        if (lhs_small_width && rhs_type == Typed::kDouble) {
            *fOut << wtab(fTab) << "var lo = ";
            store->fValue->accept(this);
            *fOut << wnextl(fTab) << "var hi = ";
            b32 old_emit_join = gEmitJoin;
            gEmitJoin         = true;
            store->fValue->accept(this);
            gEmitJoin = old_emit_join;
            *fOut << wnextl(fTab) << "var values = lo.join(hi)";
            goto End_Loop;
        }

        *fOut << wtab(fTab) << "var values = ";
        store->fValue->accept(this);
        mj_emit_simd_restore();
    }

End_Loop:
    String idx_name = getIndexName(inst);
    *fOut << wnextl(fTab) << "simd_store(" << getAddressName(store->fAddress) << ", " << idx_name << ", values)\n";
    writeSIMDLoopIncrement(idx_name, dwidth);
    fTab -= 1;
    *fOut << wtab(fTab);
}

String MojoVecInstVisitor::getIndexName(ForLoopInst* inst)
{
    auto* ini_inst = dycast(DeclareVarInst*, inst->fInit);
    mj_panic(ini_inst, "Expected `inst` to be `DeclareVarInst`");
    return ini_inst->fAddress->getName();
}

ValueInst* MojoVecInstVisitor::getEndValue(ForLoopInst* inst)
{
    auto* end_inst = dycast(BinopInst*, inst->fEnd);
    mj_panic(end_inst, "Expected `inst` to be `BinopInst`");
    return end_inst->fInst2;
}

void MojoVecInstVisitor::writeSIMDLoopHeader( 
    ForLoopInst* inst, String& dname, String& dvalue, String& dwidth
) {
    auto idx_name = getIndexName(inst);
    auto end_val  = getEndValue(inst);
    inst->fInit->accept(this);
    *fOut << "comptime " << dname << " = " << dvalue << wnextl(fTab);
    *fOut << "comptime " << dwidth << " = S32(simd_width_of[" << dname << "]())" << wnextl(fTab);
    *fOut << "while " << idx_name << " <= ";
    end_val->accept(this);
    *fOut << " - " << dwidth << ":" << wnextl(fTab);
}

void MojoVecInstVisitor::writeSIMDLoopIncrement(String const& idx_name, String const& width_name)
{ 
    *fOut << wtab(fTab) << idx_name << " = " << idx_name << " + S32(" << width_name << ")\n";
}

b32 MojoVecInstVisitor::hasWrappedIndex(Address* addr)
{
    IndexedAddress* indexed = dycast(IndexedAddress*, addr);
    if (not(indexed)) {
        return false;
    }
    if (indexed->fIndices.size() != 1) {
        puts("(indices_size != 1)");
        return true;
    }
    auto* idx = dycast(LoadVarInst*, indexed->fIndices[0]);
    if (not(idx && idx->isSimpleValue())) {
        return true;
    }
    return false;
}

b32 MojoVecInstVisitor::hasWrappedIndex(ValueInst* inst)
{ 
    // XXX:(manu) should accept also `A[i + off]` ?
    mj_debug_fir(std::cerr, inst, "rhs");
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
    // XXX:(manu) should accept also `A[i + off]` ? am I matching too strictly the lhs shape?
    if (not addr->isStack()) {
        return false;
    }
    IndexedAddress* indexed = dycast(IndexedAddress*, addr);
    if (not (indexed && indexed->fIndices.size() == 1)) {
       return false; 
    }
    auto* idx = dycast(LoadVarInst*, indexed->fIndices[0]);
    if (not (idx && idx->isSimpleValue())) {
       return false; 
    }
    auto* idx_addr = dycast(Address*, idx->fAddress);
    if (not (idx_addr && idx_addr->isLoop())) {
        return false;
    }
    return true;
}

void MojoVecInstVisitor::writeMultiBargraph(
    ForLoopInst* inst
) {
    // fTab += 1;
    // *fOut << wtab(fTab);
    mj_emit_simd_set(true);
    for (auto* line : *inst->fCode) {
        line->accept(this);
    }
    mj_emit_simd_restore();
    // writeSIMDLoopIncrement(getIndexName(inst), dwidth);
    // fTab -= 1;
    *fOut << wtab(fTab);
}

void MojoVecInstVisitor::writeBargraphUpdate(
    ForLoopInst* inst, String& dname, String& dvalue, String& dwidth
) {
    String idx_name = getIndexName(inst);
    auto* store_1 = dycast(StoreVarInst*, inst->fCode->front());
    // auto [lhs_1, rhs_1, lhs_name_1] = parseSingleStore(store_1);
    inst->fCode->pop_front();
    auto* store_2 = dycast(StoreVarInst*, inst->fCode->front());
    // auto [lhs_2, rhs_2, lhs_name_2] = parseSingleStore(store_2);

    mj_emit_simd_set(true);
    store_1->accept(this);
    *fOut << wnextl(fTab);
    store_2->accept(this);
    *fOut << wnextl(fTab);
    mj_emit_simd_restore();
}

String MojoVecInstVisitor::getDTypeValue(ValueInst* rhs) {
    Typed::VarType type = TypingVisitor::getType(rhs);
    if (Typed::isPtrType(type)) {
        type = Typed::getTypeFromPtr(type);
    }
    if (Typed::isVecType(type)) {
        type = Typed::getTypeFromVec(type);
    }
    String dtype_value;
    switch (type) {
    case Typed::kInt32:
        dtype_value = "s32";
        break;
    case Typed::kFloat:
        dtype_value = "f32";
        break;
    case Typed::kDouble:
        dtype_value = "f64";
        break;
    case Typed::kFloatMacro:
        dtype_value = "dfaust";
        break;
    default:
        mj_panic(false, "Unexpected `rhs` type " << Typed::gTypeString[type]);
    }
    return dtype_value;
}

} // namespace mojo
