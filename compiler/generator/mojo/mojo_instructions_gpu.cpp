/*                                                                             *
*   SPDX-FileCopyrightText: 2026 GRAME, Centre National de Creation Musicale   *
*   SPDX-License-Identifier: LGPL-2.1-or-later                                 *
*                                                                             */

/** @file compiler/generator/mojo/mojo_instructions_gpu.cpp **/

#include "mojo_instructions.hh"

inline namespace mojo {

using BaseVisitor = MojoInstVisitor;
using GpuVisitor  = MojoGpuInstVisitor;

MojoGpuInstVisitor::MojoGpuInstVisitor(
    OStream* out, String const& name, s32 n_ins, s32 n_outs
) : MojoInstVisitor(out, name), fName(name), fInputs(n_ins), fOutputs(n_outs)
{
    fTypeManager->fTypeDirectTable[Typed::kFloatMacro] = "F32";
    fTypeManager->fTypeDirectTable[Typed::kFloatMacro_ptr] = "Ptr[F32]";
    fTypeManager->fTypeDirectTable[Typed::kFloatMacro_ptr_ptr] = "Ptr[Ptr[F32]]";
}

// Host UI zones use the same explicit type as device I/O.

void GpuVisitor::visit(AddSliderInst* inst)
{
    String name;
    switch (inst->fType) {
        case AddSliderInst::kHorizontal: name = "add_horizontal_slider"; break;
        case AddSliderInst::kVertical:   name = "add_vertical_slider";   break;
        case AddSliderInst::kNumEntry:   name = "add_num_entry";         break;
    }
    *fOut << "ui." << name << "(" << wlit(inst->fLabel) << ", dsp."
          << snakeCase(inst->fZone) << ", F32(" << ensureReal(inst->fInit)
          << "), F32(" << ensureReal(inst->fMin) << "), F32(" << ensureReal(inst->fMax)
          << "), F32(" << ensureReal(inst->fStep) << "))" << wnextl(fTab);
}

void GpuVisitor::visit(AddBargraphInst* inst)
{
    String name = inst->fType == AddBargraphInst::kHorizontal
        ? "add_horizontal_bargraph" : "add_vertical_bargraph";
    *fOut << "ui." << name << "(" << wlit(inst->fLabel) << ", dsp."
          << snakeCase(inst->fZone) << ", F32(" << ensureReal(inst->fMin)
          << "), F32(" << ensureReal(inst->fMax) << "))" << wnextl(fTab);
}

void GpuVisitor::visit(NamedAddress* inst)
{
    mj_gpu_emit_check();
    auto loop = fLoops.find(inst->fName);
    if (loop != fLoops.end()) {
        *fOut << loop->second;
        return;
    }
    if (inst->fName == "vsize") {
        *fOut << "count";
        return;
    }
    if (inst->fName == "vindex") {
        *fOut << "offset";
        return;
    }
    if (inst->isStruct() || inst->isStaticStruct()) {
        *fOut << "dsp[].";
    } else if (fWork.count(inst->fName)) {
        *fOut << "work[].";
    }
    *fOut << snakeCase(inst->fName);
}

void GpuVisitor::visit(DeclareVarInst* inst)
{
    mj_gpu_emit_check();
    if (isChannel(inst->getName()) || fViews.count(inst->getName())) {
        return;
    }
    if (not fWork.count(inst->getName())) {
        if (not inst->fValue && not dycast(ArrayTyped*, inst->fType)) {
            *fOut << "var " << snakeCase(inst->getName()) << ": "
                  << fTypeManager->generateType(inst->fType) << wnextl(fTab);
        } else {
            BaseVisitor::visit(inst);
        }
        return;
    }
    if (inst->fValue) {
        addResource(inst->fAddress, fWrites);
        inst->fAddress->accept(this);
        *fOut << " = ";
        inst->fValue->accept(this);
        *fOut << wnextl(fTab);
    }
}

void GpuVisitor::visit(IndexedAddress* inst)
{
    if (fKernel && isChannel(inst->getName())) {
        inst->fAddress->accept(this);
        *fOut << "[unsafe_offset=";
        inst->getIndex()->accept(this);
        *fOut << "]";
        return;
    }
    BaseVisitor::visit(inst);
}

void GpuVisitor::visit(FloatNumInst* inst)
{   *fOut << "F32(" << checkFloat(inst->fNum) << ")";   }

void GpuVisitor::visit(DoubleNumInst* inst)
{   *fOut << "F64(" << checkDouble(inst->fNum) << ")";   }

void GpuVisitor::visit(ForLoopInst* inst)
{
    mj_gpu_emit_check();
    if (inst->fCode->size() == 0) {
        return;
    }
    auto* init = dycast(DeclareVarInst*, inst->fInit);
    mj_panic(init && init->fValue, "Expected an initialized GPU loop index");

    String name = init->getName();
    String saved = fLoops.count(name) ? fLoops.at(name) : "";
    String local = snakeCase(name) + "_" + std::to_string(fLoopId++);
    // Evaluate the initializer before introducing the new binding.
    *fOut << "var " << local << " = ";
    init->fValue->accept(this);
    *fOut << wnextl(fTab);
    fLoops[name] = local;
    *fOut << "while ";
    inst->fEnd->accept(this);
    *fOut << ":" << wnextl(fTab += 1);
    inst->fCode->accept(this);
    inst->fIncrement->accept(this);
    fTab -= 1;
    *fOut << wrewind(fOut);
    if (saved.empty()) {
        fLoops.erase(name);
    } else {
        fLoops[name] = saved;
    }
}

void GpuVisitor::visit(FunCallInst* inst)
{
    if (fKernel && not gMathLibTable.count(inst->fName)) {
        throw faustexception(
            "ERROR : No Mojo GPU implementation for '" + inst->fName + "'\n"
        );
    }
    BaseVisitor::visit(inst);
}

void GpuVisitor::visit(LoadVarInst* inst)
{
    if (fKernel) {
        addResource(inst->fAddress, fReads);
    }
    BaseVisitor::visit(inst);
}

void GpuVisitor::visit(LoadVarAddressInst* inst)
{
    if (fKernel) {
        addResource(inst->fAddress, fReads);
    }
    BaseVisitor::visit(inst);
}

void GpuVisitor::visit(StoreVarInst* inst)
{
    if (fKernel) {
        addResource(inst->fAddress, fWrites);
    }
    BaseVisitor::visit(inst);
}

// Work storage and dependencies are derived from the existing FIR.

b32 GpuVisitor::isChannel(String const& name)
{
    usize pos = name.find_first_of("0123456789");
    if (pos == String::npos) {
        return false;
    }
    String prefix = name.substr(0, pos);
    if (prefix != "input" && prefix != "output") {
        return false;
    }
    usize end = name.find_first_not_of("0123456789", pos);
    return end == String::npos || name.substr(end) == "_ptr";
}

b32 GpuVisitor::isFlat(Typed* type)
{
    if (auto* array = dycast(ArrayTyped*, type)) {
        return array->fSize > 0 && isFlat(array->fType);
    }
    Typed::VarType kind = type->getType();
    return kind == Typed::kInt32 || kind == Typed::kInt64 || kind == Typed::kFloat
        || kind == Typed::kDouble || kind == Typed::kFloatMacro || kind == Typed::kBool;
}

void GpuVisitor::checkFields(BlockInst* block)
{
    for (StatementInst* inst : block->fCode) {
        if (auto* decl = dycast(DeclareVarInst*, inst); decl && not isFlat(decl->fType)) {
            throw faustexception(
                "ERROR : Mojo GPU requires inline device state: " + decl->getName() + "\n"
            );
        }
    }
}

void GpuVisitor::collectWork(BlockInst* block)
{
    // Declarations outside sample loops may be shared by different tasks.
    for (StatementInst* inst : block->fCode) {
        auto* decl = dycast(DeclareVarInst*, inst);
        if (not decl || isChannel(decl->getName()) || not decl->fAddress->isStack()) {
            continue;
        }
        String name = decl->getName();
        if (auto* array = dycast(ArrayTyped*, decl->fType); array && array->fSize == 0) {
            auto* view = dycast(LoadVarAddressInst*, decl->fValue);
            auto* addr = view ? dycast(IndexedAddress*, view->fAddress) : nullptr;
            auto* root = addr ? dycast(ArrayTyped*, gGlobal->findVarType(addr->getName()))
                              : nullptr;
            if (not root || root->fSize <= 0 || not dycast(Int32NumInst*, addr->getIndex())) {
                throw faustexception(
                    "ERROR : Mojo GPU views require inline arrays and constant offsets: "
                    + name + "\n"
                );
            }
            auto added = fViews.emplace(name, view);
            mj_panic(added.second, "Duplicate GPU pointer view: " << name);
            fViewNames.push_back(name);
            continue;
        }
        if (not isFlat(decl->fType)) {
            throw faustexception("ERROR : Unsupported Mojo GPU work field: " + name + "\n");
        }
        auto added = fWork.emplace(name, decl->fType);
        mj_panic(
            added.second || added.first->second->toString() == decl->fType->toString(),
            "Conflicting GPU work declarations: " << name
        );
        if (added.second) {
            fWorkNames.push_back(name);
        }
    }
}

void GpuVisitor::addResource(Address* addr, Binds& names)
{
    String name = addr->getName();
    auto view = fViews.find(name);
    if (view != fViews.end()) {
        names.insert(view->second->getName());
    } else if (addr->isStruct() || addr->isStaticStruct() || fWork.count(name)
               || isChannel(name)) {
        names.insert(name);
    }
}

b32 GpuVisitor::intersects(Binds const& lhs, Binds const& rhs)
{
    for (String const& name : lhs) {
        if (rhs.count(name)) {
            return true;
        }
    }
    return false;
}

void GpuVisitor::prepare(Stages const& levels, BlockInst* controls, BlockInst* post)
{
    fControls = controls;
    fPost = post;
    fWork.clear();
    fViews.clear();
    fWorkNames.clear();
    fViewNames.clear();
    fStages.clear();
    collectWork(controls);
    collectWork(post);
    for (Stage const& level : levels) {
        for (BlockInst* block : level) {
            collectWork(block);
        }
    }
    std::sort(fWorkNames.begin(), fWorkNames.end());
    std::sort(fViewNames.begin(), fViewNames.end());

    for (Stage const& level : levels) {
        Arr<GpuTask> tasks;
        for (BlockInst* block : level) {
            String text = taskText(block, 1);
            tasks.push_back({block, text, fReads, fWrites});
        }
        std::stable_sort(
            tasks.begin(), tasks.end(),
            [](GpuTask const& lhs, GpuTask const& rhs) { return lhs.text < rhs.text; }
        );
        Stage batch;
        Binds reads;
        Binds writes;
        for (GpuTask const& task : tasks) {
            if (intersects(task.writes, reads) || intersects(task.writes, writes)
                || intersects(task.reads, writes)) {
                fStages.push_back(batch);
                batch.clear();
                reads.clear();
                writes.clear();
            }
            batch.push_back(task.code);
            reads.insert(task.reads.begin(), task.reads.end());
            writes.insert(task.writes.begin(), task.writes.end());
        }
        if (not batch.empty()) {
            fStages.push_back(batch);
        }
    }
}

String GpuVisitor::taskText(BlockInst* block, s32 n)
{
    OString text;
    OStream* saved_out = fOut;
    s32 saved_tab = fTab;
    b32 saved_kernel = fKernel;
    fOut = &text;
    fTab = n;
    fKernel = true;
    fLoopId = 0;
    fLoops.clear();
    fReads.clear();
    fWrites.clear();
    *fOut << wtab(n);
    block->accept(this);
    fOut = saved_out;
    fTab = saved_tab;
    fKernel = saved_kernel;
    return text.str();
}

// Generated work state, initialization and GPU methods.

void GpuVisitor::writeWork(s32 n)
{
    *fOut << wtab(n) << "struct " << fName << "Work:" << wnextl(n + 1);
    if (fWork.empty()) {
        *fOut << "var unused: U8\n";
    }
    for (String const& name : fWorkNames) {
        *fOut << "var " << snakeCase(name) << ": "
              << fTypeManager->generateType(fWork.at(name)) << wnextl(n + 1);
    }
    if (not fWork.empty()) {
        *fOut << wrewind(fOut, n + 1);
    }
    *fOut << wblank();
}

void GpuVisitor::writeInitializers(BlockInst* block, s32 n)
{
    s32 saved_tab = fTab;
    fTab = n;
    for (StatementInst* inst : block->fCode) {
        auto* decl = dycast(DeclareVarInst*, inst);
        if (not decl) {
            continue;
        }
        *fOut << wtab(n) << "dsp." << snakeCase(decl->getName()) << " = ";
        if (decl->fValue) {
            decl->fValue->accept(this);
        } else if (auto* array = dycast(ArrayTyped*, decl->fType)) {
            *fOut << fTypeManager->generateType(array) << "(fill="
                  << fTypeManager->generateType(array->fType) << "(0))";
        } else {
            *fOut << fTypeManager->generateType(decl->fType) << "(0)";
        }
        *fOut << "\n";
    }
    fTab = saved_tab;
}

void GpuVisitor::writeCompute(s32 n)
{
    mj_panic(fControls && fPost, "Expected a prepared GPU schedule");
    *fOut << wtab(n) << "@staticmethod" << wnextl(n)
          << "def gpu_work_size(imm count: S32) -> Int:" << wnextl(n + 1)
          << "return size_of[" << fName << "Work]()" << wblank(2);
    *fOut << wtab(n) << "@staticmethod" << wnextl(n)
          << "def gpu_compute(" << wnextl(n + 1)
          << "mut ctx:       DeviceContext," << wnextl(n + 1)
          << "imm dsp_raw:   DeviceBuffer[u8]," << wnextl(n + 1)
          << "imm in_buf:    DeviceBuffer[f32]," << wnextl(n + 1)
          << "imm out_buf:   DeviceBuffer[f32]," << wnextl(n + 1)
          << "imm work_buf:  DeviceBuffer[u8]," << wnextl(n + 1)
          << "imm count:     S32" << wnextl(n)
          << ") raises -> None:" << wnextl(n + 1)
          << "if count <= 0:" << wnextl(n + 2) << "return\n";
    writeLaunch("gpu_controls", n + 1, 1, "count", "S32(0)");
    *fOut << wtab(n + 1) << "var offset = S32(0)" << wnextl(n + 1)
          << "while offset < count:" << wnextl(n + 2)
          << "var size = min(S32(" << gGlobal->gVecSize << "), count - offset)\n";
    for (ssize i = 0; i < ssize(fStages.size()); i++) {
        writeLaunch(
            "gpu_stage_" + std::to_string(i), n + 2, fStages[i].size(), "size", "offset"
        );
    }
    *fOut << wtab(n + 2) << "offset += size\n";
    if (not fPost->fCode.empty()) {
        writeLaunch("gpu_post", n + 1, 1, "count", "S32(0)");
    }
    *fOut << wblank();
    writeKernel("gpu_controls", n, true);
    writeBody(fControls, n + 1);
    for (ssize i = 0; i < ssize(fStages.size()); i++) {
        *fOut << wblank();
        writeKernel("gpu_stage_" + std::to_string(i), n, false);
        *fOut << wtab(n + 1) << "var task = Int(global_idx.x)\n";
        for (ssize j = 0; j < ssize(fStages[i].size()); j++) {
            *fOut << wtab(n + 1) << (j == 0 ? "if" : "elif") << " task == " << j << ":\n";
            writeBody(fStages[i][j], n + 2);
        }
    }
    if (not fPost->fCode.empty()) {
        *fOut << wblank();
        writeKernel("gpu_post", n, true);
        writeBody(fPost, n + 1);
    }
}

void GpuVisitor::writeLaunch(
    String const& name, s32 n, ssize tasks, String const& size, String const& offset
) {
    mj_panic(tasks > 0, "Expected at least one GPU task");
    ssize block = std::min(ssize(32), tasks);
    *fOut << wtab(n) << "ctx.enqueue_function[" << fName << "." << name << "]("
          << wnextl(n + 1) << "dsp_raw,"
          << wnextl(n + 1) << "in_buf,"
          << wnextl(n + 1) << "out_buf,"
          << wnextl(n + 1) << "work_buf,"
          << wnextl(n + 1) << "count,"
          << wnextl(n + 1) << size << ","
          << wnextl(n + 1) << offset << ","
          << wnextl(n + 1) << "grid_dim=" << (tasks + block - 1) / block << ","
          << wnextl(n + 1) << "block_dim=" << block
          << wnextl(n) << ")\n";
}

void GpuVisitor::writeKernel(String const& name, s32 n, b32 single)
{
    *fOut << wtab(n) << "@staticmethod" << wnextl(n)
          << "def " << name << "(" << wnextl(n + 1)
          << "dsp_raw:    Ptr[U8, MUT_ANY]," << wnextl(n + 1)
          << "ins:        Ptr[F32, MUT_ANY]," << wnextl(n + 1)
          << "outs:       Ptr[F32, MUT_ANY]," << wnextl(n + 1)
          << "work_raw:   Ptr[U8, MUT_ANY]," << wnextl(n + 1)
          << "fullcount:  S32," << wnextl(n + 1)
          << "count:      S32," << wnextl(n + 1)
          << "offset:     S32" << wnextl(n)
          << ") -> None:\n";
    if (single) {
        *fOut << wtab(n + 1) << "if Int(global_idx.x) != 0:"
              << wnextl(n + 2) << "return\n";
    }
    *fOut << wtab(n + 1) << "var dsp = dsp_raw.unsafe_bitcast[" << fName << "]()"
          << wnextl(n + 1) << "var work = work_raw.unsafe_bitcast[" << fName << "Work]()\n";
    b32 saved_kernel = fKernel;
    s32 saved_tab = fTab;
    fKernel = true;
    fTab = n + 1;
    for (String const& view : fViewNames) {
        *fOut << wtab(n + 1) << "var " << snakeCase(view) << " = Ptr(to=";
        fViews.at(view)->accept(this);
        *fOut << ")\n";
    }
    fKernel = saved_kernel;
    fTab = saved_tab;
    for (s32 i = 0; i < fInputs; i++) {
        *fOut << wtab(n + 1) << "var input" << i << " = Ptr(to=ins[unsafe_offset=" << i
              << " * Int(fullcount) + Int(offset)])\n";
    }
    for (s32 i = 0; i < fOutputs; i++) {
        *fOut << wtab(n + 1) << "var output" << i << " = Ptr(to=outs[unsafe_offset=" << i
              << " * Int(fullcount) + Int(offset)])\n";
    }
}

void GpuVisitor::writeBody(BlockInst* block, s32 n)
{
    String body = taskText(block, n);
    if (body.find_first_not_of(" \t\r\n") == String::npos) {
        *fOut << wtab(n) << "pass\n";
    } else {
        *fOut << body;
        if (body.back() != '\n') {
            *fOut << '\n';
        }
    }
}

}  // namespace mojo
