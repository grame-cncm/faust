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
    *fOut << "struct " << fKlassName << "(" << fDspType << "):\n";
    *fOut << wtab(n) << "var null_val: " << fFloatType << "\n" << wtab(n);
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
    *fOut << wtab(n + 1) << "dsp.null_val = " << fFloatType << "(0.0)\n";
    writeFieldInitializers(n + 1);
}

void MojoCodeContainer::writeFieldInitializers(s32 n)
{
    MojoInitFieldsVisitor initializer(fOut, n);
    generateDeclarations(&initializer);
    writeGlobalVariablesInitializations(n);
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
    writeSupport(n);
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
        if (gGlobal->gFloatSize != 1) {
            throw faustexception("ERROR : Internal precision must be 32 bits in -gpu mode\n");
        }
        if (gGlobal->gFunTaskSwitch || gGlobal->gMemoryManager >= 0 || gGlobal->gExtControl
            || gGlobal->gComputeMix || gGlobal->gVectorLoopVariant == 2) {
            throw faustexception("ERROR : Unsupported execution option for Mojo GPU\n");
        }
        return new MojoGpuCodeContainer(name, numInputs, numOutputs, out);
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

MojoGpuCodeContainer::MojoGpuCodeContainer(
    String const& name, s32 n_ins, s32 n_outs, OStream* out
) : MojoCodeContainer(name, n_ins, n_outs, out)
{
    fDspType = "FaustDspGpu";
    fVisitor = new MojoGpuInstVisitor(out, name, n_ins, n_outs);
    gScalarProducer = fVisitor;
}

void MojoGpuCodeContainer::writeSupport(s32 n)
{
    if (not fSubContainers.empty()) {
        throw faustexception("ERROR : Table subcontainers are not supported for Mojo GPU\n");
    }
    fVisitor->checkFields(fDeclarationInstructions);
    fVisitor->checkFields(fGlobalDeclarationInstructions);

    lclgraph graph;
    Stages levels;
    CodeLoop::sortGraph(fCurLoop, graph);
    for (auto level = graph.rbegin(); level != graph.rend(); level++) {
        Stage tasks;
        for (CodeLoop* loop : *level) {
            BlockInst* block = IB::genBlockInst();
            loop->generateDAGScalarLoop(block, IB::genLoadFunArgsVar("count"), false);
            ControlExpander expand;
            block = expand.getCode(block);
            if (not block->fCode.empty()) {
                tasks.push_back(block);
            }
        }
        levels.push_back(tasks);
    }
    fVisitor->prepare(levels, fComputeBlockInstructions, fPostComputeBlockInstructions);
    fVisitor->writeWork(n);
}

void MojoGpuCodeContainer::writeFieldInitializers(s32 n)
{
    fVisitor->writeInitializers(fDeclarationInstructions, n);
    fVisitor->writeInitializers(fGlobalDeclarationInstructions, n);
}

void MojoGpuCodeContainer::writeCompute(s32 n)
{   fVisitor->writeCompute(n);   }

}  // namespace mojo
