/*                                                                             *
*   SPDX-FileCopyrightText: 2026 GRAME, Centre National de Creation Musicale   *
*   SPDX-License-Identifier: LGPL-2.1-or-later                                 *
*                                                                             */

/** @file compiler/generator/mojo/mojo_code_container.cpp **/

// mojo
#include "mojo_code_container.hh"

inline namespace mojo {

// Mojo code container core interface implementation.

MojoCodeContainer::~MojoCodeContainer() {}

MojoCodeContainer::MojoCodeContainer(
    std::string const& name, int numInputs, int numOutputs, std::ostream* out
) {
    initialize(numInputs, numOutputs);
    fKlassName = name;
    fOut = out;
    if (!gGlobal->gMojoVisitor) {
        gGlobal->gMojoVisitor = new MojoInstVisitor(out, name);
    }
    gScalarProducer = gGlobal->gMojoVisitor;
}

void MojoCodeContainer::writeFaustHeader()
{
    std::set<Tree> selected_keys;
    selected_keys.insert(tree("name"));
    selected_keys.insert(tree("author"));
    selected_keys.insert(tree("copyright"));
    selected_keys.insert(tree("license"));
    selected_keys.insert(tree("version"));
    *fOut << wbanner() << "\n";
    *fOut << "# Code generated with Faust " << FAUSTVERSION
          << " (https://faust.grame.fr)\n";
    for (auto const& i : gGlobal->gMetaDataSet) {
        if (selected_keys.count(i.first)) {
            *fOut << "# " << *(i.first);
            char const* sep = ": ";
            for (auto const& j : i.second) {
                *fOut << sep << *j;
                sep = ", ";
            }
            *fOut << "\n";
        }
    }
    *fOut << "# Compilation options: " << "\n" << formatCompilerOptions(2, "# ");
    *fOut << "\n" << wbanner();
}

void MojoCodeContainer::writeGlobalVariablesInlined(int n)
{
    *fOut << wtab(n);
    for (StatementInst* inst : fGlobalDeclarationInstructions->fCode) {
        if (dycast(DeclareVarInst*, inst)) {
            inst->accept(gScalarProducer);
        }
    }
    wrewind(fOut, n);
}

void MojoCodeContainer::writeClassHeaderAndFields(int n)
{
    *fOut << "@fieldwise_init\n";
    *fOut << "struct " << fKlassName << "(FaustDsp):\n";
    *fOut << wtab(n) << "var null_val: FaustFloat\n" << wtab(n);
    generateDeclarations(gScalarProducer);
    *fOut << wrewind(fOut, n);
    writeGlobalVariablesInlined(n);
}

void MojoCodeContainer::writeGlobalVariablesInitializations(int n)
{
    MojoInitFieldsVisitor initializer(fOut, n);
    for (StatementInst* inst : fGlobalDeclarationInstructions->fCode) {
        if (dycast(DeclareVarInst*, inst)) {
            inst->accept(&initializer);
        }
    }
}

void MojoCodeContainer::writeDefaultConstructor(int n)
{
    *fOut << wtab(n) << "@always_inline\n";
    *fOut << wtab(n) << "def __init__(out dsp):\n";
    *fOut << wtab(n + 1) << "dsp.null_val = FaustFloat(0.0)\n";
    MojoInitFieldsVisitor initializer(fOut, n + 1);
    generateDeclarations(&initializer);
    writeGlobalVariablesInitializations(n + 1);
}

void MojoCodeContainer::writeGetSampleRate(int n)
{
    *fOut << wtab(n) << "@always_inline\n";
    *fOut << wtab(n) << "def get_sample_rate(imm dsp) -> S32:\n";
    *fOut << wtab(n + 1) << "return dsp.sample_rate\n";
}

void MojoCodeContainer::writeGetInputs(int n)
{
    *fOut << wtab(n) << "@always_inline\n";
    *fOut << wtab(n) << "def get_num_inputs(imm dsp) -> S32:\n";
    *fOut << wtab(n + 1) << "return " << fNumInputs << "\n";
}

void MojoCodeContainer::writeGetOutputs(int n)
{
    *fOut << wtab(n) << "@always_inline\n";
    *fOut << wtab(n) << "def get_num_outputs(imm dsp) -> S32:\n";
    *fOut << wtab(n + 1) << "return " << fNumOutputs << "\n";
}

void MojoCodeContainer::writeClassInit(int n)
{
    *fOut << wtab(n) << "@always_inline\n";
    *fOut << wtab(n) << "def class_init(mut dsp, imm sample_rate: S32) -> None:\n";
    *fOut << wtab(n + 1);
    if (fStaticInitInstructions->fCode.size() == 0) {
        *fOut << "pass" << "\n";
        return;
    }
    inlineSubcontainersFunCalls(fStaticInitInstructions)->accept(gScalarProducer);
    *fOut << wrewind(fOut, n + 1);
}

void MojoCodeContainer::writeInstanceConstants(int n)
{
    *fOut << wtab(n) << "@always_inline\n";
    *fOut << wtab(n) << "def instance_constants(mut dsp, imm sample_rate: S32) -> None:\n";
    *fOut << wtab(n + 1);
    inlineSubcontainersFunCalls(fInitInstructions)->accept(gScalarProducer);
    *fOut << wrewind(fOut, n + 1);
}

void MojoCodeContainer::writeInstanceResetUserInterface(int n)
{
    // NOTE:(manu) This note is outdated, I maintain it for documentation purpose.
    // Currently I am not using `fResetUserInterfaceInstructions->accept(fCodeProducer)`
    // because it would generate a cast to `SIMD[dtype, _]`. Then that value should be
    // cast back to FaustFloat or it will lead to compiler error.
    // This workaround is based on the assumption that `FAUST` compiler generates a cast
    // expression for every field to be initialized.

    *fOut << wtab(n) << "@always_inline\n";
    *fOut << wtab(n) << "def instance_reset_user_interface(mut dsp) -> None:\n";
    if (fResetUserInterfaceInstructions->fCode.size() == 0) {
        *fOut << wtab(n + 1) << "pass" << "\n";
        return;
    }

    for (StatementInst* line : fResetUserInterfaceInstructions->fCode) {
        auto store_inst = dycast(StoreVarInst*, line);
        auto* cast_inst = dycast(CastInst*, store_inst->fValue);
        faustassert(store_inst && cast_inst);

        std::string name = snakeCase(store_inst->getName());
        *fOut << wtab(n + 1) << "dsp." << name << " = ";

        Typed::VarType type = cast_inst->fType->getType();
        if (type == Typed::VarType::kFloatMacro) {
            if (auto* val = dycast(FloatNumInst*, cast_inst->fInst); val) {
                *fOut << ensureReal(val->fNum) << "\n";
                continue;
            }
            if (auto* val = dycast(DoubleNumInst*, cast_inst->fInst); val) {
                *fOut << ensureReal(val->fNum) << "\n";
                continue;
            }
            faustassert(false);
        }
        cast_inst->accept(gScalarProducer);
    }
}

void MojoCodeContainer::writeInstanceClear(int n)
{
    *fOut << wtab(n) << "@always_inline\n";
    *fOut << wtab(n) << "def instance_clear(mut dsp) -> None:\n";
    *fOut << wtab(n + 1);
    if (fClearInstructions->fCode.size() == 0) {
        *fOut << "pass" << "\n";
        return;
    }
    generateClear(gScalarProducer);
    *fOut << wrewind(fOut, n + 1);
}

void MojoCodeContainer::writeInstanceInit(int n)
{
    *fOut << wtab(n) << "@always_inline\n";
    *fOut << wtab(n) << "def instance_init(mut dsp, imm sample_rate: S32) -> None:\n";
    *fOut << wtab(n + 1) << "dsp.instance_constants(sample_rate)\n";
    *fOut << wtab(n + 1) << "dsp.instance_reset_user_interface()\n";
    *fOut << wtab(n + 1) << "dsp.instance_clear()\n";
}

void MojoCodeContainer::writeInit(int n)
{
    *fOut << wtab(n) << "@always_inline" << "\n";
    *fOut << wtab(n) << "def init(mut dsp, imm sample_rate: S32) -> None:\n";
    *fOut << wtab(n + 1) << "dsp.class_init(sample_rate)\n";
    *fOut << wtab(n + 1) << "dsp.instance_init(sample_rate)\n";
}

void MojoCodeContainer::writeInitFunctions(int n)
{
    gScalarProducer->Tab(n + 1);
    writeClassInit(n);
    *fOut << wblank();
    writeInstanceConstants(n);
    *fOut << wblank();
    writeInstanceResetUserInterface(n);
    *fOut << wblank();
    writeInstanceClear(n);
    *fOut << wblank();
    writeInstanceInit(n);
    *fOut << wblank();
    writeInit(n);
    gScalarProducer->Tab(n);
}

void MojoCodeContainer::writeGetJson(int n)
{
    std::string json = generateJSONAux();
    *fOut << wtab(n) << "@always_inline\n";
    *fOut << wtab(n) << "def get_json(imm dsp) -> String:\n";
    *fOut << wtab(n + 1) << "return " << wlit(flattenJSON(json)) << "\n";
}

void MojoCodeContainer::writeMetadataFunc(int n)
{
    *fOut << wtab(n) << "@always_inline\n";
    *fOut << wtab(n) << "def metadata(imm dsp, mut meta: Some[FaustMeta]) -> None:\n";
    for (auto const& i : gGlobal->gMetaDataSet) {
        if (i.first == tree("compile_options")) {
            *fOut << wtab(n + 1) << "meta.declare(" << wlit("compile_options") << ", "
                  << wlit(gGlobal->printCompilationOptions1()) << ")\n";
            continue;
        }
        if (i.first == tree("author")) {
            for (auto j = i.second.begin(); j != i.second.end(); j++) {
                if (j == i.second.begin()) {
                    *fOut << wtab(n + 1) << "meta.declare(" << wlit("author") << ", "
                          << **j << ")\n";
                } else {
                    *fOut << wtab(n + 1) << "meta.declare(" << wlit("contributor") << ", "
                          << **j << ")\n";
                }
            }
            continue;
        }
        *fOut << wtab(n + 1) << "meta.declare(" << wlit(format(*i.first)) << ", "
              << **(i.second.begin()) << ")\n";
    }
}

void MojoCodeContainer::writeBuildUserInterface(int n)
{
    *fOut << wtab(n) << "@always_inline\n";
    *fOut << wtab(n) << "def build_user_interface(mut dsp, mut ui: Some[FaustGui]) -> None:\n";
    *fOut << wtab(n + 1);
    if (fUserInterfaceInstructions->fCode.size() == 0) {
        *fOut << "pass" << "\n";
    }
    gScalarProducer->Tab(n + 1);
    generateUserInterface(gScalarProducer);
    gScalarProducer->Tab(n);
    *fOut << wrewind(fOut, n + 1);
}

void MojoScalarCodeContainer::writeCompute(int n)
{
    *fOut << wtab(n) << "@always_inline" << wnextl(n)
          << "def compute(mut dsp, var count: S32, var inputs: ImmStreams, var outputs: MutStreams) -> None:"
          << wnextl(n+1);
    gScalarProducer->Tab(n + 1);
    generateComputeBlock(gScalarProducer);
    SimpleForLoopInst* loop = fCurLoop->generateSimpleScalarLoop("count");
    loop->accept(gScalarProducer);
    generatePostComputeBlock(gScalarProducer);
    gScalarProducer->Tab(n);
    *fOut << wrewind(fOut, n + 1);
}

void MojoCodeContainer::produceClass()
{
    int n = 0;
    writeFaustHeader();
    *fOut << wblank();
    mergeSubContainers();
    n += 1;
    gScalarProducer->Tab(n);
    *fOut << wblank();
    // writeDRealDefinitions(); NOTE:(manu) currently non needed
    // *fOut << wblank();
    writeClassHeaderAndFields(n);
    *fOut << wblank();
    writeDefaultConstructor(n);
    *fOut << wblank();
    writeGetSampleRate(n);
    *fOut << wblank();
    writeGetOutputs(n);
    *fOut << wblank();
    writeGetInputs(n);
    *fOut << wblank();
    writeInitFunctions(n);
    *fOut << wblank();
    writeGetJson(n);
    *fOut << wblank();
    writeMetadataFunc(n);
    *fOut << wblank();
    writeBuildUserInterface(n);
    *fOut << wblank();
    writeCompute(n);
    *fOut << wblank();
    n -= 1;
    gScalarProducer->Tab(n);
}

void MojoCodeContainer::produceInternal()
{
    faustassert(false);
}

Factory* MojoCodeContainer::produceFactory()
{
    return new TextFactory(
        fKlassName, "", "",
        dycast(std::ostringstream*, fOut) ? dycast(std::ostringstream*, fOut)->str() : "",
        ""
    );
}

CodeContainer* MojoCodeContainer::createScalarContainer(std::string const& name, int subContKind)
{   return new MojoScalarCodeContainer(name, 0, 1, fOut, subContKind);   }

CodeContainer* MojoCodeContainer::createContainer(
    std::string const& name, int numInputs, int numOutputs, std::ostream* out
) {
    if (gGlobal->gOpenCLSwitch) {
        throw faustexception("ERROR : OpenCL not supported for Mojo\n");
    }
    if (gGlobal->gCUDASwitch) {
        throw faustexception("ERROR : CUDA not supported for Mojo\n");
    }
    if (gGlobal->gOpenMPSwitch) {
        throw faustexception("ERROR : OpenMP not supported for Mojo\n");
    }
    if (gGlobal->gSchedulerSwitch) {
        throw faustexception("ERROR : Scheduler not supported for Mojo\n");
    }
    if (gGlobal->gGPUSwitch) {
        return MojoGpuCodeContainer::createContainer(name, numInputs, numOutputs, out);
    }
    if (gGlobal->gVectorSwitch) {
        if (gGlobal->gFloatSize == 2) {
            return new MojoVecCodeContainer(name, numInputs, numOutputs, out);
        }
        throw faustexception("ERROR : Internal precision must be 64 bits in -vec mode\n");
    }
    if (not (gGlobal->gFloatSize == 1 || gGlobal->gFloatSize == 2)) {
        throw faustexception("ERROR : Unsupported internal precision format\n");
    }
    return new MojoScalarCodeContainer(name, numInputs, numOutputs, out, kInt);
}

// Mojo scalar code container implementation.

MojoScalarCodeContainer::~MojoScalarCodeContainer() {}

MojoScalarCodeContainer::MojoScalarCodeContainer(
    std::string const& name, int numInputs, int numOutputs, std::ostream* out, int subContKind
) : MojoCodeContainer(name, numInputs, numOutputs, out)
{   fSubContainerType = subContKind;   }


// Mojo vector code container implementation.

MojoVecCodeContainer::~MojoVecCodeContainer() {}

MojoVecCodeContainer::MojoVecCodeContainer(
    const std::string& name, int numInputs, int numOutputs, std::ostream* out
) : VectorCodeContainer(numInputs, numOutputs)
{
    fKlassName = name;
    fOut = out;
    if (!gGlobal->gMojoVisitor) {
        gGlobal->gMojoVisitor = new MojoInstVisitor(out, name);
    }
    gScalarProducer = gGlobal->gMojoVisitor;
    gVectorProducer = new MojoVecInstVisitor(out, name);
}

void MojoVecCodeContainer::writeCompute(int n)
{
    generateComputeFunctions(gVectorProducer);
    *fOut << wtab(n) << "@always_inline" << wnextl(n)
          << "def compute(mut dsp, var count: S32, var inputs: ImmStreams, var outputs: MutStreams) -> None:";
    n += 1;
    gVectorProducer->Tab(n);
    *fOut << wnextl(n) <<R"(comptime assert dfaust == DType.float32, "Expected 32 bit float driver precision.")";
    *fOut << wnextl(n) << "comptime vsize = S32(simd_width_of[f32]())";
    *fOut << wnextl(n) << "comptime hsize = S32(simd_width_of[f64]())";
    *fOut << wnextl(n) << "comptime H = simd_width_of[f64]()";
    *fOut << wnextl(n) << "var vindex = S32(0)";
    *fOut << wnextl(n) << "var end = count - vsize" << wnextl(n);
    fDAGBlock->pop_front();  // main loop index initalized manually above
    generateComputeBlock(gVectorProducer);
    fDAGBlock->accept(gVectorProducer);
    *fOut << "vindex += vsize\n";
}

// Mojo GPU code container implementation.

MojoGpuCodeContainer::MojoGpuCodeContainer(String const& name, s32 n_ins, s32 n_outs, OStream* out)
    : MojoCodeContainer(name, n_ins, n_outs, out)
{}

void MojoGpuCodeContainer::produceClass()
{
    if (!fSubContainers.empty()) {
        throw faustexception(
            "ERROR : Mojo GPU table subcontainers are not supported yet. "
            "Use direct sin/phasor arithmetic for this probe.\n");
    }
    mergeSubContainers();
    checkFields();
    planTasks();
    writeFaustHeader();
    *fOut << "\n\nfrom max.gpu.host import DeviceBuffer, DeviceContext\n"
          << "from gpu import global_idx\n"
          << "from dsp.gpu import FaustDspGpu\n\n";
    writeWork();
    *fOut << "\n\n@fieldwise_init\nstruct " << fKlassName << "(FaustDspGpu):\n";
    size_t width = String("null_val").size();
    for (auto* block : {fDeclarationInstructions, fGlobalDeclarationInstructions}) {
        for (auto* inst : block->fCode) {
            if (auto* decl = dynamic_cast<DeclareVarInst*>(inst)) {
                width = std::max(width, snakeCase(decl->getName()).size());
            }
        }
    }
    writeFields(fDeclarationInstructions, width);
    writeFields(fGlobalDeclarationInstructions, width);
    *fOut << "    var null_val:" << String(width - String("null_val").size() + 2, ' ')
          << "FaustFloat\n\n";
    gScalarProducer->Tab(1);
    writeDefaultConstructor(1);
    *fOut << wblank();
    writeGetSampleRate(1);
    *fOut << wblank();
    writeGetInputs(1);
    *fOut << wblank();
    writeGetOutputs(1);
    *fOut << wblank();
    writeInitFunctions(1);
    *fOut << wblank();
    writeGetJson(1);
    *fOut << wblank();
    writeMetadataFunc(1);
    *fOut << wblank();
    writeBuildUserInterface(1);
    *fOut << wblank();
    writeCompute(1);
    gScalarProducer->Tab(0);
}

void MojoGpuCodeContainer::writeCompute(s32 n)
{
    *fOut << wtab(n) << "@staticmethod\n"
          << wtab(n) << "def gpu_work_size(imm count: S32) -> Int:\n"
          << wtab(n + 1) << "return size_of[" << workName() << "]()\n\n";
    *fOut << wtab(n) << "@staticmethod\n"
          << wtab(n) << "def gpu_compute(\n"
          << wtab(n + 1) << "mut ctx:       DeviceContext,\n"
          << wtab(n + 1) << "imm dsp_raw:   DeviceBuffer[u8],\n"
          << wtab(n + 1) << "imm in_buf:    DeviceBuffer[dfaust],\n"
          << wtab(n + 1) << "imm out_buf:   DeviceBuffer[dfaust],\n"
          << wtab(n + 1) << "imm work_buf:  DeviceBuffer[u8],\n"
          << wtab(n + 1) << "imm count:     S32\n"
          << wtab(n) << ") raises -> None:\n";
    writeEvidence(n + 1);
    *fOut << wtab(n + 1) << "if count <= 0:\n" << wtab(n + 2) << "return\n";
    writeLaunch("gpu_controls", n + 1, 1, "count", "S32(0)");
    *fOut << wtab(n + 1) << "var offset = S32(0)\n"
          << wtab(n + 1) << "while offset < count:\n"
          << wtab(n + 2) << "var size = min(S32(" << gGlobal->gVecSize << "), count - offset)\n";
    for (size_t i = 0; i < fStages.size(); ++i) {
        writeLaunch("gpu_stage_" + std::to_string(i), n + 2, fStages[i].size(), "size", "offset");
    }
    *fOut << wtab(n + 2) << "offset += size\n";
    if (!fPostComputeBlockInstructions->fCode.empty()) {
        writeLaunch("gpu_post", n + 1, 1, "count", "S32(0)");
    }
    *fOut << "\n";
    writeKernelHeader("gpu_controls", n, true);
    writeBody(fComputeBlockInstructions, n + 1);
    *fOut << "\n";
    for (size_t i = 0; i < fStages.size(); ++i) {
        writeKernelHeader("gpu_stage_" + std::to_string(i), n, false);
        *fOut << wtab(n + 1) << "var task = Int(global_idx.x)\n";
        for (size_t j = 0; j < fStages[i].size(); ++j) {
            s32 indent = n + 1;
            *fOut << wtab(indent) << (j == 0 ? "if" : "elif") << " task == " << j << ":\n";
            ++indent;
            writeBody(fStages[i][j], indent);
        }
        *fOut << "\n";
    }
    if (!fPostComputeBlockInstructions->fCode.empty()) {
        writeKernelHeader("gpu_post", n, true);
        writeBody(fPostComputeBlockInstructions, n + 1);
    }
}

void MojoGpuCodeContainer::resources(String const& name, Names& result) const
{
    if (!result.insert(name).second) {
        return;
    }
    auto alias = fAliases.find(name);
    if (alias != fAliases.end()) {
        for (auto const& item : alias->second) {
            resources(item, result);
        }
    }
}

bool MojoGpuCodeContainer::intersects(Names const& lhs, Names const& rhs)
{
    for (auto const& name : lhs) {
        if (rhs.count(name)) {
            return true;
        }
    }
    return false;
}

bool MojoGpuCodeContainer::isFlat(Typed* type)
{
    if (auto* array = dynamic_cast<ArrayTyped*>(type)) {
        return array->fSize > 0 && isFlat(array->fType);
    }
    auto kind = type->getType();
    return kind == Typed::kInt32 || kind == Typed::kInt64 || kind == Typed::kFloat ||
           kind == Typed::kDouble || kind == Typed::kFloatMacro || kind == Typed::kBool;
}

void MojoGpuCodeContainer::checkFields()
{
    for (auto* block : {fDeclarationInstructions, fGlobalDeclarationInstructions}) {
        for (auto* inst : block->fCode) {
            if (auto* decl = dynamic_cast<DeclareVarInst*>(inst)) {
                if (!isFlat(decl->fType)) {
                    throw faustexception(
                        "ERROR : Mojo GPU requires inline device-copyable state: " +
                        decl->getName() + ".\n");
                }
            }
        }
    }
}

void MojoGpuCodeContainer::collectWork(BlockInst* block)
{
    // Only declarations outside sample loops have cross-task lifetimes.
    for (auto* inst : block->fCode) {
        auto* decl = dynamic_cast<DeclareVarInst*>(inst);
        if (!decl || MojoGpuInstVisitor::isChannel(decl->getName()) || !decl->fAddress->isStack()) {
            continue;
        }
        if (auto* array = dynamic_cast<ArrayTyped*>(decl->fType)) {
            if (array->fSize == 0) {
                auto* view = dynamic_cast<LoadVarAddressInst*>(decl->fValue);
                auto* addr = view ? dynamic_cast<IndexedAddress*>(view->fAddress) : nullptr;
                auto* root = addr ? dynamic_cast<ArrayTyped*>(gGlobal->findVarType(addr->getName()))
                                  : nullptr;
                if (!addr || !root || root->fSize <= 0 ||
                    !dynamic_cast<Int32NumInst*>(addr->getIndex())) {
                    throw faustexception(
                        "ERROR : GPU aliases require inline arrays "
                        "and constant offsets: " +
                        decl->getName() + ".\n");
                }
                AddressRefs refs;
                view->accept(&refs);
                fViews[decl->getName()]   = view;
                fAliases[decl->getName()] = refs.names;
                continue;
            }
        }
        if (!isFlat(decl->fType)) {
            throw faustexception("ERROR : unsupported GPU scratch field: " + decl->getName() +
                                 ".\n");
        }
        auto added = fWork.emplace(decl->getName(), decl->fType);
        if (!added.second && added.first->second->toString() != decl->fType->toString()) {
            throw faustexception("ERROR : incompatible GPU work declaration: " + decl->getName() +
                                 ".\n");
        }
    }
}

String MojoGpuCodeContainer::taskKey(BlockInst* block)
{
    OString            text;
    MojoGpuInstVisitor visitor(&text, fKlassName, fWork, fViews);
    block->accept(&visitor);
    return text.str();
}

void MojoGpuCodeContainer::planTasks()
{
    collectWork(fComputeBlockInstructions);
    collectWork(fPostComputeBlockInstructions);
    lclgraph graph;
    CodeLoop::sortGraph(fCurLoop, graph);
    std::vector<Stage> levels;
    for (auto level = graph.rbegin(); level != graph.rend(); ++level) {
        Stage tasks;
        for (auto* loop : *level) {
            BlockInst* block = IB::genBlockInst();
            loop->generateDAGScalarLoop(block, IB::genLoadFunArgsVar("count"), false);
            ControlExpander expand;
            block = expand.getCode(block);
            if (!block->fCode.empty()) {
                collectWork(block);
                tasks.push_back(block);
            }
        }
        levels.push_back(tasks);
    }
    for (auto& tasks : levels) {
        std::stable_sort(tasks.begin(), tasks.end(),
                         [this](auto* lhs, auto* rhs) { return taskKey(lhs) < taskKey(rhs); });
        Stage batch;
        Names reads;
        Names writes;
        for (auto* task : tasks) {
            Accesses access(*this);
            task->accept(&access);
            if (intersects(access.writes, reads) || intersects(access.writes, writes) ||
                intersects(access.reads, writes)) {
                fStages.push_back(batch);
                batch.clear();
                reads.clear();
                writes.clear();
            }
            batch.push_back(task);
            reads.insert(access.reads.begin(), access.reads.end());
            writes.insert(access.writes.begin(), access.writes.end());
        }
        if (!batch.empty()) {
            fStages.push_back(batch);
        }
    }
}

void MojoGpuCodeContainer::writeFields(BlockInst* block, size_t width)
{
    MojoStringTypeManager types(xfloat(), fKlassName);
    for (auto* inst : block->fCode) {
        if (auto* decl = dynamic_cast<DeclareVarInst*>(inst)) {
            String name = snakeCase(decl->getName());
            *fOut << "    var " << name << ":" << String(width - name.size() + 2, ' ')
                  << types.generateType(decl->fType) << "\n";
        }
    }
}

void MojoGpuCodeContainer::writeWork()
{
    MojoStringTypeManager types(xfloat(), fKlassName);
    *fOut << "# Device-only scratch shared by kernels of one DSP instance.\n"
          << "# Prepared once; chunk tasks initialize their temporary arrays.\n"
          << "struct " << workName() << ":\n";
    size_t width = 0;
    for (auto const& item : fWork) {
        width = std::max(width, snakeCase(item.first).size());
    }
    for (auto const& item : fWork) {
        String name = snakeCase(item.first);
        *fOut << "    var " << name << ":" << String(width - name.size() + 2, ' ')
              << types.generateType(item.second) << "\n";
    }
    if (fWork.empty()) {
        *fOut << "    var unused:  U8\n";
    }
}

void MojoGpuCodeContainer::writeEvidence(s32 n)
{
    *fOut << wtab(n) << "comptime assert dfaust == f32, "
          << "\"Expected 32-bit external audio precision.\"\n";
}

void MojoGpuCodeContainer::writeLaunch(
    String const& name, s32 n, size_t tasks, String const& size, String const& offset
) {
    size_t block = std::min(size_t(32), tasks);
    *fOut << wtab(n) << "ctx.enqueue_function[" << fKlassName << "." << name << "](\n"
          << wtab(n + 1) << "dsp_raw,\n"
          << wtab(n + 1) << "in_buf,\n"
          << wtab(n + 1) << "out_buf,\n"
          << wtab(n + 1) << "work_buf,\n"
          << wtab(n + 1) << "count,\n"
          << wtab(n + 1) << size << ",\n"
          << wtab(n + 1) << offset << ",\n"
          << wtab(n + 1) << "grid_dim=" << (tasks + block - 1) / block << ",\n"
          << wtab(n + 1) << "block_dim=" << block << "\n"
          << wtab(n) << ")\n";
}

void MojoGpuCodeContainer::writeKernelHeader(String const& name, s32 n, bool single)
{
    *fOut << wtab(n) << "@staticmethod\n"
          << wtab(n) << "def " << name << "(\n"
          << wtab(n + 1) << "dsp_raw:    Ptr[U8, MUT_ANY],\n"
          << wtab(n + 1) << "ins:        Ptr[FaustFloat, MUT_ANY],\n"
          << wtab(n + 1) << "outs:       Ptr[FaustFloat, MUT_ANY],\n"
          << wtab(n + 1) << "work_raw:   Ptr[U8, MUT_ANY],\n"
          << wtab(n + 1) << "fullcount:  S32,\n"
          << wtab(n + 1) << "count:      S32,\n"
          << wtab(n + 1) << "offset:     S32\n"
          << wtab(n) << ") -> None:\n";
    writeEvidence(n + 1);
    if (single) {
        *fOut << wtab(n + 1) << "if Int(global_idx.x) != 0:\n" << wtab(n + 2) << "return\n";
    }
    *fOut << wtab(n + 1) << "var dsp = dsp_raw.unsafe_bitcast[" << fKlassName << "]()\n"
          << wtab(n + 1) << "var work = work_raw.unsafe_bitcast[" << workName() << "]()\n";
    MojoGpuInstVisitor visitor(fOut, fKlassName, fWork, fViews, n + 1);
    for (auto const& view : fViews) {
        *fOut << wtab(n + 1) << "var " << snakeCase(view.first) << " = Ptr(to=";
        view.second->accept(&visitor);
        *fOut << ")\n";
    }
    for (s32 i = 0; i < fNumInputs; ++i) {
        *fOut << wtab(n + 1) << "var input" << i << " = Ptr(to=ins[unsafe_offset=" << i
              << " * Int(fullcount) + Int(offset)])\n";
    }
    for (s32 i = 0; i < fNumOutputs; ++i) {
        *fOut << wtab(n + 1) << "var output" << i << " = Ptr(to=outs[unsafe_offset=" << i
              << " * Int(fullcount) + Int(offset)])\n";
    }
}

void MojoGpuCodeContainer::writeBody(BlockInst* block, s32 n)
{
    OString text;
    MojoGpuInstVisitor visitor(&text, fKlassName, fWork, fViews, n);
    *fOut << wtab(n);
    block->accept(&visitor);
    String body = text.str();
    if (body.find_first_not_of(" \t\r\n") == String::npos) {
        *fOut << "pass\n";
    } else {
        *fOut << body;
        if (body.back() != '\n') {
            *fOut << '\n';
        }
    }
}

}  // namespace mojo
