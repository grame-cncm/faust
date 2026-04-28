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

// mojo
#include "mojo_code_container.hh"

namespace mojo {

/*                                                             *
* Mojo code container base interface                           *
*                                                             */

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
    fCodeProducer = gGlobal->gMojoVisitor;
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
    *fOut << "# Code generated with Faust " << FAUSTVERSION
          << " (https://faust.grame.fr)\n";
    *fOut << "# Compilation options: " << "\n" << formatCompilerOptions(4, "# ");
    *fOut << "\n" << wbanner() << "\n\n";
}

void MojoCodeContainer::writeMissingMathFunctions()
{
    *fOut << 
R"(@always_inline
def mod[dtype: DType](num: SIMD[dtype, 1], den: SIMD[dtype, 1]) -> SIMD[dtype, 1]:
    return num % den


@always_inline
def rint(var x: SIMD[F64.dtype, 1]) -> SIMD[F64.dtype, 1]:
    return external_call["rint", c_double, c_double](c_double(x))


@always_inline
def rint(var x: SIMD[F32.dtype, 1]) -> SIMD[F32.dtype, 1]:
    return external_call["rint", c_float, c_float](c_float(x))

)";
}

void MojoCodeContainer::writeGlobalVariablesInlined(int n)
{
    *fOut << wtab(n);
    for (StatementInst* inst : fGlobalDeclarationInstructions->fCode) {
        if (dycast(DeclareVarInst*, inst)) {
            inst->accept(fCodeProducer);
        }
    }
    wrewind(fOut, n);
}

void MojoCodeContainer::writeClassHeaderAndFields(int n)
{
    *fOut << "@fieldwise_init\n";
    *fOut << "struct " << fKlassName << "(FaustDsp):\n";
    *fOut << wtab(n) << "var null_val: FaustFloat\n" << wtab(n);
    generateDeclarations(fCodeProducer);
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
    *fOut << wtab(n) << "def get_sample_rate(read dsp) -> S32:\n";
    *fOut << wtab(n + 1) << "return dsp.sample_rate\n";
}

void MojoCodeContainer::writeGetInputs(int n)
{
    *fOut << wtab(n) << "@always_inline\n";
    *fOut << wtab(n) << "def get_num_inputs(read dsp) -> S32:\n";
    *fOut << wtab(n + 1) << "return " << fNumInputs << "\n";
}

void MojoCodeContainer::writeGetOutputs(int n)
{
    *fOut << wtab(n) << "@always_inline\n";
    *fOut << wtab(n) << "def get_num_outputs(read dsp) -> S32:\n";
    *fOut << wtab(n + 1) << "return " << fNumOutputs << "\n";
}

void MojoCodeContainer::writeInitClass(int n)
{
    *fOut << wtab(n) << "@always_inline\n";
    *fOut << wtab(n) << "def init_class(mut dsp, sample_rate: S32) -> None:\n";
    *fOut << wtab(n + 1);
    if (fStaticInitInstructions->fCode.size() == 0) {
        *fOut << "pass" << "\n";
        return;
    }

    // // TEST:
    // auto block = inlineSubcontainersFunCalls(fStaticInitInstructions);
    // mj_debug_fir(block, "");
    // // TEST:

    inlineSubcontainersFunCalls(fStaticInitInstructions)->accept(fCodeProducer);
    *fOut << wrewind(fOut, n + 1);
}

void MojoCodeContainer::writeSetInstanceConstants(int n)
{
    *fOut << wtab(n) << "@always_inline\n";
    *fOut << wtab(n) << "def set_instance_constants(mut dsp, sample_rate: S32) -> None:\n";
    *fOut << wtab(n + 1);
    inlineSubcontainersFunCalls(fInitInstructions)->accept(fCodeProducer);
    *fOut << wrewind(fOut, n + 1);
}

void MojoCodeContainer::writeResetInstanceUI(int n)
{
    *fOut << wtab(n) << "@always_inline\n";
    *fOut << wtab(n) << "def reset_instance_ui(mut dsp) -> None:\n";
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

        // XXX:(manu)
        // I am not using fResetUserInterfaceInstructions->accept(fCodeProducer)
        // because I need to avoid the cast to SIMD[dtype..] since it is not needed
        // and leads to compiler errors. The following can be wrong if the faust
        // compiler does not generate a cast expression for some field.
        cast_inst->accept(fCodeProducer);
    }
}

void MojoCodeContainer::writeClearInstance(int n)
{
    *fOut << wtab(n) << "@always_inline\n";
    *fOut << wtab(n) << "def clear_instance(mut dsp) -> None:\n";
    *fOut << wtab(n + 1);
    if (fClearInstructions->fCode.size() == 0) {
        *fOut << "pass" << "\n";
        return;
    }
    generateClear(fCodeProducer);
    *fOut << wrewind(fOut, n + 1);
}

void MojoCodeContainer::writeInitInstance(int n)
{
    *fOut << wtab(n) << "@always_inline\n";
    *fOut << wtab(n) << "def init_instance(mut dsp, sample_rate: S32) -> None:\n";
    *fOut << wtab(n + 1) << "dsp.set_instance_constants(sample_rate)\n";
    *fOut << wtab(n + 1) << "dsp.reset_instance_ui()\n";
    *fOut << wtab(n + 1) << "dsp.clear_instance()\n";
}

void MojoCodeContainer::writeInit(int n)
{
    *fOut << wtab(n) << "@always_inline" << "\n";
    *fOut << wtab(n) << "def init(mut dsp, sample_rate: S32) -> None:\n";
    *fOut << wtab(n + 1) << "dsp.init_class(sample_rate)\n";
    *fOut << wtab(n + 1) << "dsp.init_instance(sample_rate)\n";
}

void MojoCodeContainer::writeInitFunctions(int n)
{
    fCodeProducer->Tab(n + 1);
    writeInitClass(n);
    *fOut << wblank();
    writeSetInstanceConstants(n);
    *fOut << wblank();
    writeResetInstanceUI(n);
    *fOut << wblank();
    writeClearInstance(n);
    *fOut << wblank();
    writeInitInstance(n);
    *fOut << wblank();
    writeInit(n);
    fCodeProducer->Tab(n);
}

void MojoCodeContainer::writeGetJson(int n)
{
    std::string json = generateJSONAux();
    *fOut << wtab(n) << "@always_inline\n";
    *fOut << wtab(n) << "def get_json(read dsp) -> String:\n";
    *fOut << wtab(n + 1) << "return " << wlit(flattenJSON(json)) << "\n";
}

void MojoCodeContainer::writeMetadataFunc(int n)
{
    *fOut << wtab(n) << "@always_inline\n";
    *fOut << wtab(n) << "def metadata(dsp, mut meta: Some[FaustMeta]) -> None:\n";
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

void MojoCodeContainer::writeBuildUI(int n)
{
    *fOut << wtab(n) << "@always_inline\n";
    *fOut << wtab(n) << "def build_ui(mut dsp, mut ui: Some[FaustGui]) -> None:\n";
    *fOut << wtab(n + 1);
    if (fUserInterfaceInstructions->fCode.size() == 0) {
        *fOut << "pass" << "\n";
    }
    fCodeProducer->Tab(n + 1);
    generateUserInterface(fCodeProducer);
    fCodeProducer->Tab(n);
    *fOut << wrewind(fOut, n + 1);
}

void MojoScalarCodeContainer::writeCompute(int n)
{
    *fOut << wtab(n)   << "@always_inline\n"
          << wtab(n)   << "def compute[dtype: DType](\n"
          << wtab(n+1) <<     "mut dsp,\n"
          << wtab(n+1) <<     "var count:      S32,\n"
          << wtab(n+1) <<     "var inputs:     ReadStreams[dtype],\n"
          << wtab(n+1) <<     "var outputs:    MutaStreams[dtype]\n"
          << wtab(n)   << ") -> None:\n" << wtab(n+1);
    fCodeProducer->Tab(n + 1);
    generateComputeBlock(fCodeProducer);
    SimpleForLoopInst* loop = fCurLoop->generateSimpleScalarLoop("count");
    loop->accept(fCodeProducer);
    generatePostComputeBlock(fCodeProducer);
    fCodeProducer->Tab(n);
    *fOut << wrewind(fOut, n + 1) << "\n";
}

void MojoCodeContainer::produceClass()
{
    int n = 0;
    writeFaustHeader();
    *fOut << wblank();
    writeMissingMathFunctions();
    *fOut << wblank();
    mergeSubContainers();
    n += 1;
    fCodeProducer->Tab(n);
    // writeGlobalFunctions(n);
    *fOut << wblank();
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
    writeBuildUI(n);
    *fOut << wblank();
    writeCompute(n);
    n -= 1;
    fCodeProducer->Tab(n);
}

void MojoCodeContainer::produceInternal()
{
    faustassert(false);
}

DspFactory* MojoCodeContainer::produceFactory()
{
    return new TextDspFactory(
        fKlassName, "", "",
        dycast(std::ostringstream*, fOut) ? dycast(std::ostringstream*, fOut)->str() : "",
        ""
    );
}

CodeContainer* MojoCodeContainer::createScalarContainer(
    std::string const& name, int subContKind
) {
    return new MojoScalarCodeContainer(name, 0, 1, fOut, subContKind);
}

CodeContainer* MojoCodeContainer::createContainer(
    std::string const& name, int numInputs, int numOutputs, std::ostream* out
) {
    if (gGlobal->gFloatSize == 3) {
        throw faustexception("ERROR : -quad format not supported for Mojo\n");
    }
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
    if (gGlobal->gVectorSwitch) {
        return (CodeContainer*) new MojoVectorCodeContainer(name, numInputs, numOutputs, out);
    }
    return (CodeContainer*) new MojoScalarCodeContainer(name, numInputs, numOutputs, out, kInt);
}

/*                                                             *
* Mojo scalar code container                                   *
*                                                             */

MojoScalarCodeContainer::~MojoScalarCodeContainer() {}

MojoScalarCodeContainer::MojoScalarCodeContainer(
    std::string const& name, int numInputs, int numOutputs, std::ostream* out, int subContKind
)
    : MojoCodeContainer(name, numInputs, numOutputs, out)
{
    fSubContainerType = subContKind;
}

/*                                                             *
* Mojo vector code container                                   *
*                                                             */

MojoVectorCodeContainer::~MojoVectorCodeContainer() {}

MojoVectorCodeContainer::MojoVectorCodeContainer(
    const std::string& name, int numInputs, int numOutputs, std::ostream* out
)
    : VectorCodeContainer(numInputs, numOutputs)
    , MojoCodeContainer(name, numInputs, numOutputs, out)
{}

void MojoVectorCodeContainer::writeCompute(int n)
{
    generateComputeFunctions(fCodeProducer);
    *fOut << "\n" << wtab(n) << "@always_inline\n"
          << wtab(n)   << "def compute[dtype: DType](\n"
          << wtab(n+1) <<     "mut dsp,\n"
          << wtab(n+1) <<     "var count:      S32,\n"
          << wtab(n+1) <<     "var inputs:     ReadStreams[dtype],\n"
          << wtab(n+1) <<     "var outputs:    MutaStreams[dtype]\n"
          << wtab(n)   << ") -> None:\n" << wtab(n+1);
    fCodeProducer->Tab(n + 1);
    generateComputeBlock(fCodeProducer);
    fDAGBlock->accept(fCodeProducer);
    *fOut << wrewind(fOut, n) << "\n";
}

//     back(1, *fOut);
//     *fOut << "end";

}  // namespace mojo

/*                                                             *
* Unused                                                       *
*                                                             */

// XXX: Is this useless after merging the sub containers? All tests pass
//
// void MojoCodeContainer::writeGlobalFunctions(int n)
// {
//     mj_unused(n);
//     isize t = 0;
//     for (auto const& inst : fGlobalDeclarationInstructions->fCode) {
//         if (dycast(DeclareFunInst*, inst)) {
//             inst->accept(fCodeProducer);
//             t++;
//         }
//     }
//     if (t != 0) {
//         fOut->seekp(isize(fOut->tellp()) - 1);
//     }
// }
