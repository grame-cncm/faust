// compiler/generator/mojo/mojo_instructions.cpp

#include "mojo_instructions.hh"

inline namespace mojo {

////////////////////////////////////////////////////////////////////////////////
// MojoInstVisitor implementation

MojoInstVisitor::MojoInstVisitor(OStream* out, String const& structName, i32 tab)
    : TextInstVisitor(out, ".", new MojoStringTypeManager(xfloat(), structName, ""), tab)
{   gMathLibTable = gCreateMathLibTable();   }

MojoInstVisitor::~MojoInstVisitor() {}

void MojoInstVisitor::visit(AddMetaDeclareInst* inst)
{
    String zone = (inst->fZone == "0") ? "null_val" : snakeCase(inst->fZone);
    *fOut << "ui.declare(";
    *fOut << "dsp." << zone << ", " << wlit(inst->fKey) << ", " << wlit(inst->fValue);
    *fOut << ")" << wnextl(fTab);
}

void MojoInstVisitor::visit(AddButtonInst* inst)
{
    String name;
    String zone = snakeCase(inst->fZone);
    if (inst->fType == AddButtonInst::kDefaultButton) {
        name = "add_button";
    } else {
        name = "add_check_button";
    }
    *fOut << "ui." << name << "(" << wlit(inst->fLabel) << ", dsp." << zone << ")";
    *fOut << wnextl(fTab);
}

void MojoInstVisitor::visit(AddSliderInst* inst)
{
    String name;
    switch (inst->fType) {
        case AddSliderInst::kHorizontal:
            name = "add_horizontal_slider";
            break;
        case AddSliderInst::kVertical:
            name = "add_vertical_slider";
            break;
        case AddSliderInst::kNumEntry:
            name = "add_num_entry";
            break;
    }

    *fOut << "ui." << name << "("
          << wlit(inst->fLabel) << ", "
          << "dsp." << snakeCase(inst->fZone) << ", "
          << gToFaustFloat(ensureReal(inst->fInit)) << ", "
          << gToFaustFloat(ensureReal(inst->fMin))  << ", "
          << gToFaustFloat(ensureReal(inst->fMax))  << ", "
          << gToFaustFloat(ensureReal(inst->fStep))
    << ")";
    *fOut << wnextl(fTab);
}

void MojoInstVisitor::visit(AddBargraphInst* inst)
{
    String name;
    switch (inst->fType) {
        case AddBargraphInst::kHorizontal:
            name = "add_horizontal_bargraph";
            break;
        case AddBargraphInst::kVertical:
            name = "add_vertical_bargraph";
            break;
    }
    *fOut << "ui." << name << "(" << wlit(inst->fLabel) << ", "
          << "dsp." << snakeCase(inst->fZone) << ", "
          << gToFaustFloat(ensureReal(inst->fMin)) << ", "
          << gToFaustFloat(ensureReal(inst->fMax)) << ")";
    *fOut << wnextl(fTab);
}

void MojoInstVisitor::visit(AddSoundfileInst* inst)
{
    mj_noimpl1(*fOut, "AddSoundfileInst", inst);
    faustassert(false);
}

void MojoInstVisitor::visit(BinopInst* inst)
{
    *fOut << "(";
    inst->fInst1->accept(this);
    *fOut << ") " << gBinOpTable[inst->fOpcode]->fName << " (";
    inst->fInst2->accept(this);
    *fOut << ")";
}

void MojoInstVisitor::visit(CastInst* inst)
{
    *fOut << fTypeManager->generateType(inst->fType) << "(";
    if (auto* float_inst = dycast(FloatNumInst*, inst->fInst)) {
        *fOut << ensureReal(float_inst->fNum);
        goto End_Inst;
    }
    if (auto* double_inst = dycast(DoubleNumInst*, inst->fInst)) {
        *fOut << ensureReal(double_inst->fNum);
        goto End_Inst;
    }

    inst->fInst->accept(this);
End_Inst:
    *fOut << ")";
}

void MojoInstVisitor::visit(CloseboxInst* inst)
{
    mj_unused(inst);
    *fOut << "ui.close_box()";
    *fOut << wnextl(fTab);
}

void MojoInstVisitor::visit(DeclareStructTypeInst* inst)
{
    StructTyped* type = inst->fType;
    *fOut << "struct " << type->fName << ":" << "\n";
    fTab += 1;
    for (NamedTyped* field : type->fFields) {
        *fOut << wtab(fTab) << fTypeManager->generateType(field, field->fName);
        *fOut << "\n";
    }
    fTab -= 1;
}

void MojoInstVisitor::visit(DeclareVarInst* inst)
{
    String name = snakeCase(inst->getName());
    *fOut << "var ";
    if (inst->fAddress->isStruct() || inst->fAddress->isStaticStruct()) {
        *fOut << fTypeManager->generateType(inst->fType, name);
        goto End_Inst;
    }
    if (!inst->fValue) {
        b32 is_arr_typed = dycast(ArrayTyped*, inst->fType) != nullptr;
        if (is_arr_typed) {
            *fOut << name << " = ";
            *fOut << fTypeManager->generateType(inst->fType);
            *fOut << "(uninitialized=True)";
            goto End_Inst;
        }
        *fOut << fTypeManager->generateType(inst->fType);
        goto End_Inst;
    }
    *fOut << name << " = ";
    if (dycast(LoadVarAddressInst*, inst->fValue)) {
        *fOut << "Ptr(to=";
        inst->fValue->accept(this);
        *fOut << ")";
        goto End_Inst;
    }
    inst->fValue->accept(this);
End_Inst:
    *fOut << wnextl(fTab);
}

void MojoInstVisitor::visit(DoubleArrayNumInst* inst)
{
    char sep = '[';
    for (size_t i = 0; i < inst->fNumTable.size(); i++) {
        *fOut << sep << checkDouble(inst->fNumTable[i]);
        sep = ',';
    }
    *fOut << ']';
}

void MojoInstVisitor::visit(DeclareFunInst* inst)
{
    if (gFuncSymTable.find(inst->fName) != gFuncSymTable.end()) {
        return;
    } 
    
    gFuncSymTable[inst->fName] = true;
    if (gMathLibTable.find(inst->fName) == gMathLibTable.end()) {
        writeFunDefHeader(inst);
        writeFunDefBody(inst);
        *fOut << "\n";
    }
}

void MojoInstVisitor::visit(DropInst* inst)
{
    if (inst->fResult) {
        inst->fResult->accept(this);
        *fOut << wnextl(fTab);
    }
}

void MojoInstVisitor::visit(FloatArrayNumInst* inst)
{
    char sep = '[';
    for (size_t i = 0; i < inst->fNumTable.size(); i++) {
        *fOut << sep << checkDouble(inst->fNumTable[i]);
        sep = ',';
    }
    *fOut << ']';
}

void MojoInstVisitor::visit(ForLoopInst* inst)
{
    if (inst->fCode->size() == 0) {
        return;
    }
    inst->fInit->accept(this);
    *fOut << "while ";
    inst->fEnd->accept(this);
    fTab += 1;
    *fOut << ": " << "\n" << wtab(fTab);
    inst->fCode->accept(this);
    inst->fIncrement->accept(this);
    fTab -= 1;
    *fOut << wrewind(fOut);
}

void MojoInstVisitor::visit(FunCallInst* inst)
{
    VString name = (gMathLibTable.find(inst->fName) != gMathLibTable.end())
                            ? gMathLibTable[inst->fName] : inst->fName;

    if (name == "pow") {
        ValueInst* inst_base = inst->fArgs.front();
        ValueInst* inst_exp = inst->fArgs.back();
        double e = 0.0;

        if (!inst_exp->isSimpleValue()) {
            goto MathLib_Call;
        }
        if (auto* float_inst = dycast(FloatNumInst*, inst_exp)) {
            e = float_inst->fNum;
        }
        if (auto* double_inst = dycast(DoubleNumInst*, inst_exp)) {
            e = double_inst->fNum;
        }
        if (e <= 0 || not isWhole(e)) {
            goto MathLib_Call;
        }

        String e_str = toStringTruncNullFraction(e);
        *fOut << "pow_unrolled[" << e_str << "](";
        inst_base->accept(this);
        goto End_Inst;
    }

MathLib_Call:
    *fOut << name << "(";
    generateFunCallArgs(inst->fArgs.begin(), inst->fArgs.end(), inst->fArgs.size());
End_Inst:
    *fOut << ")";
}

void MojoInstVisitor::visit(IfInst* inst)
{
    *fOut << "if (";
    inst->fCond->accept(this);
    fTab += 1;
    *fOut << " != 0):\n" << wtab(fTab);
    inst->fThen->accept(this);
    *fOut << wrewind(fOut); 
    if (inst->fElse->fCode.size() > 0)
    {
        *fOut << "elif";
        *fOut << wtab(fTab + 1) << "\n";
        inst->fElse->accept(this);
        *fOut << wrewind(fOut);
    }
    fTab -= 1;
    *fOut << "\n" << wtab(fTab);
}

void MojoInstVisitor::visit(IndexedAddress* indexed)
{
    indexed->fAddress->accept(this);
    DeclareStructTypeInst* struct_type = isStructType(indexed->getName());
    if (struct_type) {
        Int32NumInst* idx = dycast(Int32NumInst*, indexed->getIndex());
        faustassert(idx);
        String name = snakeCase(struct_type->fType->getName(idx->fNum));
        *fOut << "." << name;
        return;
    }  
    *fOut << "[";
    indexed->getIndex()->accept(this);
    *fOut << "]";
}

void MojoInstVisitor::visit(Int32NumInst* inst)
{
    *fOut << "S32(" << inst->fNum << ")";
}

void MojoInstVisitor::visit(Int64NumInst* inst)
{
    *fOut << "S64(" << inst->fNum << ")";
}

void MojoInstVisitor::visit(LabelInst* inst)
{
    mj_unused(inst);
}

void MojoInstVisitor::visit(LoadVarAddressInst* inst)
{
    inst->fAddress->accept(this);  // NOTE:(manu) value semantics (l-value ref)
}

void MojoInstVisitor::visit(NamedAddress* inst)
{
    if (inst->isStruct() || inst->isStaticStruct()) {
        *fOut << "dsp.";
    }
    String name = snakeCase(inst->fName);
    *fOut << name;
}

void MojoInstVisitor::visit(OpenboxInst* inst)
{
    String name;
    switch (inst->fOrient) {
        case OpenboxInst::kVerticalBox:
            name = "open_vertical_box";
            break;
        case OpenboxInst::kHorizontalBox:
            name = "open_horizontal_box";
            break;
        case OpenboxInst::kTabBox:
            name = "open_tab_box";
            break;
    }
    *fOut << "ui." << name << "(" << wlit(inst->fName) << ")";
    *fOut << wnextl(fTab);
}

void MojoInstVisitor::visit(Select2Inst* inst)
{
    inst->fThen->accept(this);
    *fOut << " if ";
    inst->fCond->accept(this);
    *fOut << " else ";
    inst->fElse->accept(this);
}

void MojoInstVisitor::visit(SimpleForLoopInst* inst)
{
    if (inst->fCode->size() == 0) {
        return;
    }
    *fOut << "for var " << inst->getName() << " in range(";
    Int32NumInst* lo = dycast(Int32NumInst*, inst->fLowerBound);
    Int32NumInst* up = dycast(Int32NumInst*, inst->fUpperBound);
    if (inst->fReverse) {
        faustassert(up);
        if (!lo) {
            *fOut << "S32(" <<up->fNum << "), ";
            inst->fLowerBound->accept(this);
            *fOut << " - 1, -1";
        } else {
            *fOut << "S32(" <<up->fNum << "), " << lo->fNum - 1 << ", -1";
        }
        goto Loop_Body;
    }
    faustassert(lo);
    if (!up) {
        *fOut << "S32(" << lo->fNum << "), ";
        inst->fUpperBound->accept(this);
    } else {
        *fOut << "S32(" <<lo->fNum << "), " << up->fNum;
    }
Loop_Body:
    fTab += 1;
    *fOut << "):\n" << wtab(fTab);
    inst->fCode->accept(this);
    fTab -= 1;
    *fOut << wrewind(fOut);
}

void MojoInstVisitor::visit(StoreVarInst* inst)
{
    inst->fAddress->accept(this);
    *fOut << " = ";
    // Is the lhs a field of the dsp and the rhs a cast to FaustFloat?
    if (auto* cast_inst = dycast(CastInst*, inst->fValue); cast_inst
        && (inst->fAddress->isStruct() || inst->fAddress->isStaticStruct())
        && (cast_inst->fType->getType() == Typed::VarType::kFloatMacro))
    {
        *fOut << "FaustFloat(";
        cast_inst->fInst->accept(this);
        *fOut << ")" << wnextl(fTab);
        return;
    }
    inst->fValue->accept(this);
    *fOut << wnextl(fTab);
}

void MojoInstVisitor::visitAux(RetInst* inst, bool genEmpty)
{

    if (inst->fResult) {
        *fOut << "return ";
        inst->fResult->accept(this);
        *fOut << wnextl(fTab - 1);
    } else if (genEmpty) {
        *fOut << "return";
        *fOut << wnextl(fTab - 1);
    }
}

void MojoInstVisitor::writeFunDefArgs(DeclareFunInst* inst)
{   
    usize size = inst->fType->fArgsTypes.size();
    usize i = 0;
    for (auto const& arg : inst->fType->fArgsTypes) {
        *fOut << fTypeManager->generateType(arg);
        if (i < size - 1) {
            *fOut << ", ";
            i += 1;
        }
    }
}

void MojoInstVisitor::writeFunDefHeader(DeclareFunInst* inst) {
    *fOut << "@always_inline" << "\n";
    *fOut << wtab(fTab) << "def " << inst->fName << "(";
    fTab += 1;
    writeFunDefArgs(inst);
    *fOut << ") -> " << fTypeManager->generateType(inst->fType->fResult) << ": "
          << "\n" << wtab(fTab);
}

void MojoInstVisitor::writeFunDefBody(DeclareFunInst* inst)
{
    if (inst->fCode->fCode.size() == 0) {
        *fOut << wtab(fTab) << "pass" << "\n";
    } else {
        inst->fCode->accept(this);
    }
    fTab -= 1;
}

////////////////////////////////////////////////////////////////////////////////
// MojoVecInstVisitor implementation

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
    // mj_debug_fir(std::cerr, inst, "visit(IndexedAddress*)");

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

    // mj_panic(idx, "visit(IndexedAddress*) - dycast(LoadVarInst*, indexed->fIndices[0])");
    // if (addr->isStack() && idx->fAddress->isLoop()) {

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

void MojoVecInstVisitor::visit(LabelInst* inst)
{
    auto label = String(inst->fLabel.begin() + 1, inst->fLabel.end() - 2);
    label[0] = '#';
    *fOut << label << wnextl(fTab);
}

void MojoVecInstVisitor::visit(ForLoopInst* inst)
{
    if (inst->fCode->size() == 0) {
        return;
    }
    if (inst->fIsRecursive) {
        return MojoInstVisitor::visit(inst);
    }

    auto [lhs, rhs, lhs_name]    = parseSingleStore(inst->fCode);  // Address*, ValueInst*, String
    auto [dvalue, dname, dwidth] = getDTypeProperties(rhs);   // String, String, String

    if (inst->fCode->size() > 2) {
        return writeMultiBargraph(inst, dname, dvalue, dwidth);
    }

    // mj_panic(inst->fCode->size() == 1 || inst->fCode->size() == 2, "Unexpected `ForLoopInst` size");

    if (inst->fCode->size() == 2) {
        return writeBargraphUpdate(inst, dname, dvalue, dwidth);
    }

    if (!isUnitStrideStore(lhs) || hasWrappedIndex(rhs)) {
        return MojoInstVisitor::visit(inst);
    }


    writeSIMDLoopHeader(inst, dname, dvalue, dwidth);
    fTab += 1;

    mj_emit_simd_set(true);

    auto rhs_type = Typed::kNoType;
    auto lhs_type = Typed::kNoType;
    mj_debug_fir(std::cerr, rhs, "rhs");
    // the casted expression defines the type of the lhs
    if (auto* cast_inst = dycast(CastInst*, rhs)) {
        lhs_type = TypingVisitor::getType(cast_inst);
        mj_debug_msg(std::cerr, "lhs_type: " << Typed::gTypeString[lhs_type]);
        // we want the temporary type of the rhs internal computation too
        if (auto* binop_inst = dycast(BinopInst*, cast_inst->fInst)) {
            rhs_type = TypingVisitor::getType(binop_inst);
            mj_debug_msg(std::cerr, "rhs_type: " << Typed::gTypeString[rhs_type]);
        }
    }

    // XXX:
    puts(Typed::gTypeString[lhs_type].c_str());
    puts(Typed::gTypeString[rhs_type].c_str());

    b32 lhs_small_width = (lhs_type == Typed::kDouble)
                        || (lhs_type == Typed::kFloatMacro && std::is_same_v<FAUSTFLOAT, float>);
    if (lhs_small_width && rhs_type == Typed::kDouble) {
        *fOut << wtab(fTab) << "var lo = ";
        rhs->accept(this);
        *fOut << wnextl(fTab) << "var hi = ";
        b32 old_emit_join = gEmitJoin;
        gEmitJoin = true;
        rhs->accept(this);
        gEmitJoin = old_emit_join;
        *fOut << wnextl(fTab) << "var values = lo.join(hi)";
        goto End_Loop;
    }

    *fOut << wtab(fTab) << "var values = ";
    rhs->accept(this);

End_Loop:
    mj_emit_simd_restore();
    String idx_name = getIndexName(inst);
    *fOut << wnextl(fTab) << "simd_store(" << lhs_name << ", " << idx_name << ", values)\n";
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

Tuple<Address*, ValueInst*, String> MojoVecInstVisitor::parseSingleStore(BlockInst* inst)
{
    auto* store = dycast(StoreVarInst*, inst->front());
    mj_panic(store, "The first instruction of the block is expected to be a `StoreVarInst`");
    Address*   lhs      = store->fAddress;
    ValueInst* rhs      = store->fValue;
    String     lhs_name = snakeCase(lhs->getName());
    if (lhs->isStruct() || lhs->isStaticStruct()) {
        lhs_name = "dsp." + lhs_name;
    }
    return {lhs, rhs, lhs_name};
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
    *fOut << " - " << dwidth << ":\n";
}

void MojoVecInstVisitor::writeSIMDLoopIncrement(String const& idx_name, String const& width_name)
{
    *fOut << wtab(fTab) << idx_name << " = " << idx_name << " + S32(" << width_name << ")\n";
}

Tuple<String, String, String> MojoVecInstVisitor::getDTypeProperties(ValueInst* rhs)
{
    return {getDTypeValue(rhs), gGlobal->getFreshID("dtype"), gGlobal->getFreshID("width")};
}

b32 MojoVecInstVisitor::hasWrappedIndex(Address* addr)
{
    mj_noimpl(std::cerr, "hasWrappedIndex(Adddress*)");
    return false;
}

b32 MojoVecInstVisitor::hasWrappedIndex(ValueInst* value)
{
    mj_noimpl1(std::cerr, "hasWrappedIndex(ValueInst*)", value);
    return false;
}

b32 MojoVecInstVisitor::isUnitStrideStore(Address* addr)
{

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

    // XXX: may remove this line and refactor the function to not take idx_name
    // mj_panic(idx_addr->getName() == idx_name, "Loop index name does not match the given `idx_name`");

    return true;
}

void MojoVecInstVisitor::writeBargraphUpdate(
    ForLoopInst* inst, String& dname, String& dvalue, String& dwidth
) {
    String idx_name = getIndexName(inst);
    ValueInst* end_val = getEndValue(inst);
    auto [lhs_1, rhs_1, lhs_name_1] = parseSingleStore(inst->fCode);
    inst->fCode->pop_front();
    auto [lhs_2, rhs_2, lhs_name_2] = parseSingleStore(inst->fCode);

    inst->fInit->accept(this);
    *fOut << "while " << idx_name << " <= ";
    end_val->accept(this);
    *fOut << " - S32(dfaust_width):\n";
    fTab += 1;

    mj_emit_simd_set(true);

    *fOut << wtab(fTab) << "var values = ";
    rhs_1->accept(this);
    *fOut << "\n";

    *fOut << wtab(fTab) << lhs_name_1 << " = values[Int(dfaust_width) - 1]\n";
    *fOut << wtab(fTab) << "simd_store(" << lhs_name_2 << ", " << idx_name << ", values)\n";

    writeSIMDLoopIncrement(idx_name, "dfaust_width");
    fTab -= 1;
    *fOut << wtab(fTab);

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

////////////////////////////////////////////////////////////////////////////////
// MojoInitFieldsVisitor implementation

MojoInitFieldsVisitor::MojoInitFieldsVisitor(OStream* out, i32 tab)
    : fOut(out), fTab(tab)
{}

void MojoInitFieldsVisitor::visit(DeclareVarInst* inst)
{
    *fOut << wtab(fTab);
    inst->fAddress->accept(this);
    *fOut << " = ";
    if (inst->fValue) {
        inst->fValue->accept(this);
        *fOut << "\n";
    } else {
        gZeroInitializer(fOut, inst->fType);
    }
}

void MojoInitFieldsVisitor::visit(NamedAddress* inst)
{
    if (inst->isStruct() || inst->isStaticStruct()) {
        *fOut << "dsp.";
    }
    *fOut << snakeCase(inst->fName);
}

void MojoInitFieldsVisitor::visit(Int32ArrayNumInst* inst)
{
    char sep = '[';
    for (size_t i = 0; i < inst->fNumTable.size(); i++) {
        *fOut << sep << "S32(" << inst->fNumTable[i] << ")";
        sep = ',';
    }
    *fOut << ']';
}

void MojoInitFieldsVisitor::visit(FloatArrayNumInst* inst)
{
    char sep = '[';
    for (size_t i = 0; i < inst->fNumTable.size(); i++) {
        *fOut << sep << checkFloat(inst->fNumTable[i]);
        sep = ',';
    }
    *fOut << ']';
}

void MojoInitFieldsVisitor::visit(DoubleArrayNumInst* inst)
{
    char sep = '[';
    for (size_t i = 0; i < inst->fNumTable.size(); i++) {
        *fOut << sep << checkDouble(inst->fNumTable[i]);
        sep = ',';
    }
    *fOut << ']';
}

void MojoInitFieldsVisitor::gZeroInitializer(OStream* out, Typed* typed) {
    ArrayTyped* array_type = dycast(ArrayTyped*, typed);
    Typed::VarType type = typed->getType();
    switch (type) {
    case Typed::kInt32_ptr:
        *out << "Arr[S32, " << array_type->fSize << "](fill=0)";
        break;
    case Typed::kInt64_ptr:
        *out << "Arr[S64, " << array_type->fSize << "](fill=0)";
        break;
    case Typed::kFloat_ptr:
        *out << "Arr[F32, " << array_type->fSize << "](fill=0.0)";
        break;
    case Typed::kDouble_ptr:
        *out << "Arr[F64, " << array_type->fSize << "](fill=0.0)";
        break;
    case Typed::kFloatMacro_ptr:
        *out << "Arr[FaustFloat, " << array_type->fSize << "](fill=0.0)";
        break;
    case Typed::kInt32:
        *out << "0";
        break;
    case Typed::kInt64:
        *out << "0";
        break;
    case Typed::kFloat:
        *out << "0.0";
        break;
    case Typed::kDouble:
        *out << "0.0";
        break;
    case Typed::kFloatMacro:
        *out << "0.0";
        break;
    default:
        mj_panic(false, "`typed` has unexpected type " << Typed::gTypeString[type]);
    }
    *out << "\n";
}

////////////////////////////////////////////////////////////////////////////////
// Global

String MojoInstVisitor::gToFaustFloat(String const& str)
{
    return "FaustFloat(" + str + ")";
}

void MojoInstVisitor::cleanup()
{
    gFuncSymTable.clear();
}

MathLibTable MojoInstVisitor::gCreateMathLibTable()
{
    return MathLibTable{
        { "abs",        "abs"       },
        { "fabs",       "abs"       },
        { "fabsf",      "abs"       },

        { "min_i",      "min"       },
        { "min_f",      "min"       },
        { "min_",       "min"       },
        { "max_i",      "max"       },
        { "max_f",      "max"       },
        { "max_",       "max"       },
        { "minmax",     "NIL"       },

        { "cos",        "cos"       },
        { "cosf",       "cos"       },
        { "acos",       "acos"      },
        { "acosf",      "acos"      },
        { "cosh",       "cosh"      },
        { "coshf",      "cosh"      },
        { "acosh",      "acosh"     },
        { "acoshf",     "acosh"     },

        { "sin",        "sin"       },
        { "sinf",       "sin"       },
        { "asin",       "asin"      },
        { "asinf",      "asin"      },
        { "sinh",       "sinh"      },
        { "sinhf",      "sinh"      },
        { "asinh",      "asinh"     },
        { "asinhf",     "asinh"     },

        { "tan",        "tan"       },
        { "tanf",       "tan"       },
        { "atan",       "atan"      },
        { "atanf",      "atan"      },
        { "atan2",      "atan2"     },
        { "atan2f",     "atan2"     },
        { "tanh",       "tanh"      },
        { "tanhf",      "tanh"      },
        { "atanh",      "atanh"     },
        { "atanhf",     "atanh"     },

        { "exp",        "exp"       },
        { "expf",       "exp"       },
        { "log",        "log"       },
        { "logf",       "log"       },
        { "log10",      "log10"     },
        { "log10f",     "log10"     },
        { "pow",        "pow"       },
        { "powf",       "pow"       },

        { "sqrt",       "sqrt"      },
        { "sqrtf",      "sqrt"      },
        { "cbrt",       "cbrt"      },
        { "cbrtf",      "cbrt"      },

        { "ceil",       "ceil"      },
        { "ceilf",      "ceil"      },
        { "floor",      "floor"     },
        { "floorf",     "floor"     },
        { "round",      "round"     },
        { "roundf",     "round"     },
        { "rint",       "rint"       },
        { "rintf",      "rint"       },

        { "fmod",       "mod"    },
        { "fmodf",      "mod"    },
        { "remainder",  "remainder" },
        { "remainderf", "remainder" },

        { "erf",        "erf"       },
        { "erff",       "erf"       },
        { "erfc",       "erfc"      },
        { "erfcf",      "erfc"      },

        { "copysign",   "copysign"  },
        { "copysignf",  "copysign"  },

        { "isnan",      "isnan"     },
        { "isnanf",     "isnan"     },
        { "isinf",      "isinf"     },
        { "isinff",     "isinf"     },
        { "isfinite",   "isfinite"  },
        { "isfinitef",  "isfinite"  },
    };
}

}  // namespace mojo

// TODO:(manu) Categorize non-recursive vec loops and emit SIMD accordingly.
//  Verified assumptions from inspected C++ vec code:
//  - recursive loops fall back to scalar;
//  - most non-recursive vec loops are single-store;
//  - multi-instruction non-recursive vec loops are UI/bargraph special cases;
//  - most store LHS forms are unit-stride;
//  - masked/ring-buffer accesses can appear in non-recursive vec loops;
//    they need fallback or a dedicated path.
//
//  Categories:
//  - loop-invariant RHS:
//      emit SIMD broadcast + `simd_store`;
//  - direct indexed copy/cast, e.g. `A[i] = B[i + k]`:
//      emit `simd_load` + `simd_store`;
//  - supported indexed expression:
//      emit SIMD expression with lane-wise loads;
//  - UI/bargraph multi-store:
//      scalarize UI updates and SIMD-store the normal output/store when supported;
//  - masked/ring-buffer LHS/RHS:
//      fall back for now;
//  - unsupported form:
//      fall back to the scalar Mojo visitor.
