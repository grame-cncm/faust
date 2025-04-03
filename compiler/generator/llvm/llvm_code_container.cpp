/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#ifdef WIN32
#pragma warning(disable : 4146 4244 4275)
#endif

#include "llvm_code_container.hh"
#include "compatibility.hh"
#include "exception.hh"
#include "fir_to_fir.hh"
#include "global.hh"
#include "llvm_dynamic_dsp_aux.hh"
#include "llvm_instructions.hh"

using namespace llvm;
using namespace std;

/*
 LLVM module description:

 - several init and 'clone' methods are implemented in the 'llvm_dsp' wrapping code
 - starting with LLVM 15, the LLVMInstVisitor::fVarTypes keeps association of address and types

 TODO: in -mem mode, classInit and classDestroy will have to be called once at factory init and
 destroy time
*/

// Helper functions
bool      linkModules(Module* dst, ModulePTR src, string& error);
ModulePTR loadModule(const string& module_name, LLVMContext* context);
Module*   linkAllModules(LLVMContext* context, Module* dst, string& error);

CodeContainer* LLVMCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new LLVMScalarCodeContainer(name, 0, 1, fModule, fContext, sub_container_type);
}

LLVMCodeContainer::LLVMCodeContainer(const string& name, int numInputs, int numOutputs)
{
    LLVMContext* context = new LLVMContext();
    Module*      module =
        new Module(gGlobal->printCompilationOptions1() + ", v" + string(FAUSTVERSION), *context);

    init(name, numInputs, numOutputs, module, context);
}

LLVMCodeContainer::LLVMCodeContainer(const string& name, int numInputs, int numOutputs,
                                     Module* module, LLVMContext* context)
{
    init(name, numInputs, numOutputs, module, context);
}

void LLVMCodeContainer::init(const string& name, int numInputs, int numOutputs, Module* module,
                             LLVMContext* context)
{
    initialize(numInputs, numOutputs);

    fKlassName = name;
    fModule    = module;
    fContext   = context;
    fBuilder   = new IRBuilder<>(*fContext);

    if (!gGlobal->isOpt("FAUST_LLVM_NO_FM")) {
        // Set "-fast-math"
        FastMathFlags FMF;
#if LLVM_VERSION_MAJOR >= 8
        FMF.setFast();  // has replaced the following function
#else
        FMF.setUnsafeAlgebra();
#endif
        fBuilder->setFastMathFlags(FMF);
    }

    fModule->setTargetTriple(sys::getDefaultTargetTriple());
}

LLVMCodeContainer::~LLVMCodeContainer()
{
    delete fBuilder;
}

CodeContainer* LLVMCodeContainer::createContainer(const string& name, int numInputs, int numOutputs)
{
    gGlobal->gDSPStruct = true;  // for -vec -fun mode
    CodeContainer* container;

    if (gGlobal->gFloatSize == 3) {
        throw faustexception("ERROR : -quad format not supported for LLVM\n");
    }
    if (gGlobal->gOpenCLSwitch) {
        throw faustexception("ERROR : OpenCL not supported for LLVM\n");
    }
    if (gGlobal->gCUDASwitch) {
        throw faustexception("ERROR : CUDA not supported for LLVM\n");
    }

    if (gGlobal->gOpenMPSwitch) {
        throw faustexception("ERROR : OpenMP not supported for LLVM\n");
    } else if (gGlobal->gSchedulerSwitch) {
        container = new LLVMWorkStealingCodeContainer(name, numInputs, numOutputs);
    } else if (gGlobal->gVectorSwitch) {
        container = new LLVMVectorCodeContainer(name, numInputs, numOutputs);
    } else {
        container = new LLVMScalarCodeContainer(name, numInputs, numOutputs);
    }

    return container;
}

void LLVMCodeContainer::generateFunMaps()
{
    if (gGlobal->gFastMathLib != "") {
        generateFunMap("fabs", "fast_fabs", 1);
        generateFunMap("acos", "fast_acos", 1);
        generateFunMap("asin", "fast_asin", 1);
        generateFunMap("atan", "fast_atan", 1);
        generateFunMap("atan2", "fast_atan2", 2);
        generateFunMap("ceil", "fast_ceil", 1);
        generateFunMap("cos", "fast_cos", 1);
        generateFunMap("exp", "fast_exp", 1);
        generateFunMap("exp2", "fast_exp2", 1);
        generateFunMap("exp10", "fast_exp10", 1);
        generateFunMap("floor", "fast_floor", 1);
        generateFunMap("fmod", "fast_fmod", 2);
        generateFunMap("log", "fast_log", 1);
        generateFunMap("log2", "fast_log2", 1);
        generateFunMap("log10", "fast_log10", 1);
        generateFunMap("pow", "fast_pow", 2);
        generateFunMap("remainder", "fast_remainder", 2);
        generateFunMap("rint", "fast_rint", 1);
        generateFunMap("round", "fast_round", 1);
        generateFunMap("sin", "fast_sin", 1);
        generateFunMap("sqrt", "fast_sqrt", 1);
        generateFunMap("tan", "fast_tan", 1);
    } else {
#ifdef __APPLE__
        generateFunMap("exp10", "__exp10", 1, true);
#endif
    }
}

void LLVMCodeContainer::generateFunMap(const string& fun1_aux, const string& fun2_aux, int num_args,
                                       bool body)
{
    Typed::VarType type = itfloat();
    string         fun1 = fun1_aux + isuffix();
    string         fun2 = fun2_aux + isuffix();

    list<NamedTyped*> args1;
    list<ValueInst*>  args2;
    for (int i = 0; i < num_args; i++) {
        string var = gGlobal->getFreshID("val");
        args1.push_back(IB::genNamedTyped(var, type));
        args2.push_back(IB::genLoadFunArgsVar(var));
    }

    // Creates function
    FunTyped* fun_type1 = IB::genFunTyped(args1, IB::genBasicTyped(type), FunTyped::kLocal);
    FunTyped* fun_type2 = IB::genFunTyped(args1, IB::genBasicTyped(type), FunTyped::kDefault);

    IB::genDeclareFunInst(fun2, fun_type2)->accept(fCodeProducer);
    if (body) {
        BlockInst* block = IB::genBlockInst();
        block->pushBackInst(IB::genRetInst(IB::genFunCallInst(fun2, args2)));
        IB::genDeclareFunInst(fun1, fun_type1, block)->accept(fCodeProducer);
    }
}

void LLVMCodeContainer::produceInternal()
{
    // Build DSP struct
    generateDeclarations(&fStructVisitor);
    DeclareStructTypeInst* dec_type = fStructVisitor.getStructType(fKlassName);

    // Generate DSP structure
    fCodeProducer = new LLVMInstVisitor(fModule, fBuilder, &fStructVisitor, dec_type);

    // Memory methods
    generateCalloc()->accept(fCodeProducer);
    generateFree()->accept(fCodeProducer);

    generateNewDsp("new" + fKlassName, fStructVisitor.getStructSize())->accept(fCodeProducer);
    generateDeleteDsp("delete" + fKlassName, "dsp")->accept(fCodeProducer);

    generateFunMaps();

    // Global declarations
    generateExtGlobalDeclarations(fCodeProducer);
    generateGlobalDeclarations(fCodeProducer);

    generateInstanceInitFun("instanceInit" + fKlassName, "dsp", false, false)
        ->accept(fCodeProducer);
    generateFillFun("fill" + fKlassName, "dsp", false, false)->accept(fCodeProducer);
}

dsp_factory_base* LLVMCodeContainer::produceFactory()
{
    if (gGlobal->gInlineTable) {
        // Sub containers are merged in the main class
        mergeSubContainers();
    } else {
        // Generate sub containers
        generateSubContainers();
    }

    // Build DSP struct
    generateDeclarations(&fStructVisitor);
    DeclareStructTypeInst* dec_type = fStructVisitor.getStructType(fKlassName);

    // Generate DSP structure
    fCodeProducer = new LLVMInstVisitor(fModule, fBuilder, &fStructVisitor, dec_type);

    generateFunMaps();

    // Global declarations
    generateExtGlobalDeclarations(fCodeProducer);
    generateGlobalDeclarations(fCodeProducer);

    if (gGlobal->gInlineTable) {
        generateStaticInitFun("staticInit" + fKlassName, false)->accept(fCodeProducer);
    } else {
        generateStaticInitFun("classInit" + fKlassName, false)->accept(fCodeProducer);
    }
    generateInstanceClear("instanceClear" + fKlassName, "dsp", false, false)->accept(fCodeProducer);
    generateInstanceConstants("instanceConstants" + fKlassName, "dsp", false, false)
        ->accept(fCodeProducer);
    generateAllocate("allocate" + fKlassName, "dsp", false, false)->accept(fCodeProducer);
    generateDestroy("destroy" + fKlassName, "dsp", false, false)->accept(fCodeProducer);

    // generateGetJSON generation
    if (gGlobal->gFloatSize == 1) {
        generateGetJSON<float>();
    } else {
        generateGetJSON<double>();
    }

    // Compute
    generateCompute();

    // Link LLVM modules defined in 'ffunction'
    set<string> S;
    collectLibrary(S);
    string error;

    if (S.size() > 0) {
        for (const auto& f : S) {
            string module_name = unquote(f);
            if (endWith(module_name, ".bc") || endWith(module_name, ".ll")) {
                ModulePTR module = loadModule(module_name, fContext);
                if (module) {
                    bool res = linkModules(fModule, MovePTR(module), error);
                    if (!res) {
                        cerr << "WARNING : " << error << endl;
                    }
                }
            }
        }
    }

    // Possibly link with additional LLVM modules
    if (!linkAllModules(fContext, fModule, error)) {
        throw faustexception("ERROR : " + error);
    }

    return new llvm_dynamic_dsp_factory_aux("", fModule, fContext, "", -1);
}

DeclareFunInst* LLVMCodeContainer::generateStaticInitFun(const string& name, bool isstatic)
{
    Names args;
    if (gGlobal->gInlineTable) {
        args.push_back(IB::genNamedTyped("dsp", Typed::kObj_ptr));
    }
    args.push_back(IB::genNamedTyped("sample_rate", Typed::kInt32));

    BlockInst* block = IB::genBlockInst();

    if (gGlobal->gInlineTable) {
        BlockInst* inlined = inlineSubcontainersFunCalls(fStaticInitInstructions);
        block->pushBackInst(inlined);
    } else {
        block->pushBackInst(fStaticInitInstructions);
        block->pushBackInst(fPostStaticInitInstructions);
    }

    //  20/11/16 : added in generateInstanceInitFun, is this needed here ?
    /*
     init_block->pushBackInst(fResetUserInterfaceInstructions);
     init_block->pushBackInst(fClearInstructions);
     */

    // Explicit return
    block->pushBackInst(IB::genRetInst());

    // Creates function
    FunTyped* fun_type = IB::genFunTyped(args, IB::genVoidTyped(),
                                         (isstatic) ? FunTyped::kStatic : FunTyped::kDefault);
    return IB::genDeclareFunInst(name, fun_type, block);
}

// Scalar
LLVMScalarCodeContainer::LLVMScalarCodeContainer(const string& name, int numInputs, int numOutputs)
    : LLVMCodeContainer(name, numInputs, numOutputs)
{
}

LLVMScalarCodeContainer::LLVMScalarCodeContainer(const string& name, int numInputs, int numOutputs,
                                                 Module* module, LLVMContext* context,
                                                 int sub_container_type)
    : LLVMCodeContainer(name, numInputs, numOutputs, module, context)
{
    fSubContainerType = sub_container_type;
}

LLVMScalarCodeContainer::~LLVMScalarCodeContainer()
{
}

void LLVMScalarCodeContainer::generateCompute()
{
    generateComputeFun("compute" + fKlassName, "dsp", false, false)->accept(fCodeProducer);
}

BlockInst* LLVMScalarCodeContainer::generateComputeAux()
{
    BlockInst* block = IB::genBlockInst();
    // Generates control
    block->pushBackInst(fComputeBlockInstructions);
    // Generates the DSP loop
    block->pushBackInst(fCurLoop->generateScalarLoop(fFullCount));
    // Generates post DSP loop code
    block->pushBackInst(fPostComputeBlockInstructions);
    return block;
}

// Vector
LLVMVectorCodeContainer::LLVMVectorCodeContainer(const string& name, int numInputs, int numOutputs)
    : VectorCodeContainer(numInputs, numOutputs), LLVMCodeContainer(name, numInputs, numOutputs)
{
}

LLVMVectorCodeContainer::~LLVMVectorCodeContainer()
{
}

void LLVMVectorCodeContainer::generateCompute()
{
    // Possibly generate separated functions
    generateComputeFunctions(fCodeProducer);

    generateComputeFun("compute" + fKlassName, "dsp", false, false)->accept(fCodeProducer);
}

BlockInst* LLVMVectorCodeContainer::generateComputeAux()
{
    BlockInst* block = IB::genBlockInst();
    // Generates control
    block->pushBackInst(fComputeBlockInstructions);
    // Generates the DSP loop
    block->pushBackInst(fDAGBlock);
    return block;
}

// OpenMP
LLVMOpenMPCodeContainer::LLVMOpenMPCodeContainer(const string& name, int numInputs, int numOutputs)
    : OpenMPCodeContainer(numInputs, numOutputs), LLVMCodeContainer(name, numInputs, numOutputs)
{
}

LLVMOpenMPCodeContainer::~LLVMOpenMPCodeContainer()
{
}

void LLVMOpenMPCodeContainer::generateCompute()
{
    generateOMPDeclarations();

    // Generates OMP thread function
    generateOMPCompute();

    // Generates OMP data struct

    // Generates OMP thread function call
    generateGOMP_parallel_start();  // TODO : add parameters
    generateDSPOMPCompute();
    generateGOMP_parallel_end();
}

BlockInst* LLVMOpenMPCodeContainer::generateComputeAux()
{
    // TODO
    return nullptr;
}

void LLVMOpenMPCodeContainer::generateOMPCompute()
{
    // TODO
}

void LLVMOpenMPCodeContainer::generateDSPOMPCompute()
{
}

void LLVMOpenMPCodeContainer::generateGOMP_parallel_start()
{
}

void LLVMOpenMPCodeContainer::generateGOMP_parallel_end()
{
}

LLVMValue LLVMOpenMPCodeContainer::generateGOMP_single_start()
{
    return nullptr;
}

void LLVMOpenMPCodeContainer::generateGOMP_barrier()
{
}

void LLVMOpenMPCodeContainer::generateGOMP_sections_start(LLVMValue num)
{
}

void LLVMOpenMPCodeContainer::generateGOMP_sections_end()
{
}

void LLVMOpenMPCodeContainer::generateGOMP_sections_next()
{
}

void LLVMOpenMPCodeContainer::generateOMPDeclarations()
{
}

// Works stealing scheduler
LLVMWorkStealingCodeContainer::LLVMWorkStealingCodeContainer(const string& name, int numInputs,
                                                             int numOutputs)
    : WSSCodeContainer(numInputs, numOutputs, "dsp"), LLVMCodeContainer(name, numInputs, numOutputs)
{
}

LLVMWorkStealingCodeContainer::~LLVMWorkStealingCodeContainer()
{
}

void LLVMWorkStealingCodeContainer::generateCompute()
{
    // Possibly generate separated functions
    generateComputeFunctions(fCodeProducer);

    // Generates "computeThread" code
    generateComputeThread("computeThread" + fKlassName, "dsp", false, false)->accept(fCodeProducer);

    // Generates prototype to be used by worker threads
    generateComputeThreadExternal("computeThreadExternal", "dsp")->accept(fCodeProducer);

    // Generates compute
    generateComputeFun("compute" + fKlassName, "dsp", false, false)->accept(fCodeProducer);
}

BlockInst* LLVMWorkStealingCodeContainer::generateComputeAux()
{
    BlockInst* block = IB::genBlockInst();
    // Generates control
    block->pushBackInst(fComputeBlockInstructions);
    return block;
}
