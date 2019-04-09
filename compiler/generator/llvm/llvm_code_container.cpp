/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
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

#define ModulePTR std::unique_ptr<Module>
#define MovePTR(ptr) std::move(ptr)

using namespace std;

/*
 LLVM module description:

- 'clone' method is implemented in the 'llvm_dsp' wrapping code

 TODO: in -mem mode, classInit and classDestroy will have to be called once at factory init and destroy time
*/

// Helper functions
bool      linkModules(Module* dst, ModulePTR src, string& error);
ModulePTR loadModule(const string& module_name, llvm::LLVMContext* context);
Module*   linkAllModules(llvm::LLVMContext* context, Module* dst, string& error);

list<string> LLVMInstVisitor::gMathLibTable;

CodeContainer* LLVMCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new LLVMScalarCodeContainer(name, 0, 1, fModule, fContext, sub_container_type);
}

LLVMCodeContainer::LLVMCodeContainer(const string& name, int numInputs, int numOutputs)
{
    initialize(numInputs, numOutputs);
    fKlassName = name;
    fContext   = new LLVMContext();
    stringstream compile_options;
    gGlobal->printCompilationOptions(compile_options);
    fModule = new Module(compile_options.str() + ", v" + string(FAUSTVERSION), *fContext);
    fBuilder = new IRBuilder<>(*fContext);

    // Check pointer size
    faustassert((gGlobal->gMachinePtrSize == int(fModule->getDataLayout().getPointerSize())));

    // Set "-fast-math"
    FastMathFlags FMF;
#if defined(LLVM_60) || defined(LLVM_70) || defined(LLVM_80)
    FMF.setFast();  // has replaced the below function
#else
    FMF.setUnsafeAlgebra();
#endif
    fBuilder->setFastMathFlags(FMF);
    fModule->setTargetTriple(llvm::sys::getDefaultTargetTriple());
}

LLVMCodeContainer::LLVMCodeContainer(const string& name, int numInputs, int numOutputs, Module* module,
                                     LLVMContext* context)
{
    initialize(numInputs, numOutputs);
    fKlassName = name;
    fModule    = module;
    fContext   = context;
    fBuilder   = new IRBuilder<>(*fContext);

    // Set "-fast-math"
    FastMathFlags FMF;
#if defined(LLVM_60) || defined(LLVM_70) || defined(LLVM_80)
    FMF.setFast();  // has replaced the below function
#else
    FMF.setUnsafeAlgebra();
#endif
    fBuilder->setFastMathFlags(FMF);
}

LLVMCodeContainer::~LLVMCodeContainer()
{
    delete fBuilder;
}

CodeContainer* LLVMCodeContainer::createContainer(const string& name, int numInputs, int numOutputs)
{
    gGlobal->gDSPStruct = true;
    CodeContainer* container;

    if (gGlobal->gMemoryManager) {
        throw faustexception("ERROR : -mem not supported for LLVM\n");
    }
    if (gGlobal->gFloatSize == 3) {
        throw faustexception("ERROR : quad format not supported for LLVM\n");
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

llvm::PointerType* LLVMCodeContainer::generateDspStruct()
{
    // Generate DSP structure
    LLVMTypeHelper type_helper(fModule);
    generateDeclarations(&fStructVisitor);

    DeclareStructTypeInst* dec_type = fStructVisitor.getStructType(fKlassName);
  
    LLVMType dsp_type = type_helper.convertFIRType(dec_type->fType);
    return PointerType::get(dsp_type, 0);
}

void LLVMCodeContainer::generateGetJSON()
{
    PointerType*  string_ptr = PointerType::get(fBuilder->getInt8Ty(), 0);
    LLVMVecTypes  getJSON_args;
    FunctionType* getJSON_type = FunctionType::get(string_ptr, makeArrayRef(getJSON_args), false);
    Function* getJSON = Function::Create(getJSON_type, GlobalValue::ExternalLinkage, "getJSON" + fKlassName, fModule);

    // Prepare compilation options
    stringstream compile_options;
    gGlobal->printCompilationOptions(compile_options, false);

    // JSON generation
    JSONInstVisitor json_visitor1;
    generateUserInterface(&json_visitor1);

    map<string, int> path_index_table;
    for (auto& it : json_visitor1.fPathTable) {
        // Get field index
        path_index_table[it.second] = fStructVisitor.getFieldOffset(it.first);
    }

    faustassert(fStructVisitor.getFieldOffset("fSampleRate") != -1);

    JSONInstVisitor json_visitor("", "", fNumInputs, fNumOutputs, fStructVisitor.getFieldOffset("fSampleRate"), "", "",
                                 FAUSTVERSION, compile_options.str(), gGlobal->gReader.listLibraryFiles(),
                                 gGlobal->gImportDirList, to_string(fStructVisitor.getStructSize()), path_index_table);
    generateUserInterface(&json_visitor);
    generateMetaData(&json_visitor);

    BasicBlock* return_block = BasicBlock::Create(*fContext, "return_block", getJSON);
    ReturnInst::Create(*fContext, fCodeProducer->genStringConstant(json_visitor.JSON(true)), return_block);

    verifyFunction(*getJSON);
    fBuilder->ClearInsertionPoint();
}

void LLVMCodeContainer::generateFunMaps()
{
    if (gGlobal->gFastMath) {
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

void LLVMCodeContainer::generateFunMap(const string& fun1_aux, const string& fun2_aux, int num_args, bool body)
{
    Typed::VarType type = itfloat();
    string fun1 = fun1_aux + isuffix();
    string fun2 = fun2_aux + isuffix();

    list<NamedTyped*> args1;
    list<ValueInst*>  args2;
    for (int i = 0; i < num_args; i++) {
        string var = gGlobal->getFreshID("val");
        args1.push_back(InstBuilder::genNamedTyped(var, type));
        args2.push_back(InstBuilder::genLoadFunArgsVar(var));
    }

    // Creates function
    FunTyped* fun_type = InstBuilder::genFunTyped(args1, InstBuilder::genBasicTyped(type), FunTyped::kDefault);

    InstBuilder::genDeclareFunInst(fun2, fun_type)->accept(fCodeProducer);
    if (body) {
        BlockInst* block = InstBuilder::genBlockInst();
        block->pushBackInst(InstBuilder::genRetInst(InstBuilder::genFunCallInst(fun2, args2)));
        InstBuilder::genDeclareFunInst(fun1, fun_type, block)->accept(fCodeProducer);
    }
}

void LLVMCodeContainer::produceInternal()
{
    // Generate DSP structure
    llvm::PointerType* dsp_ptr = generateDspStruct();
    fCodeProducer = new LLVMInstVisitor(fModule, fBuilder, &fStructVisitor, dsp_ptr);

    /// Memory methods
    generateCalloc()->accept(fCodeProducer);
    generateFree()->accept(fCodeProducer);

    generateNewDsp("new" + fKlassName, fStructVisitor.getStructSize())->accept(fCodeProducer);
    generateDeleteDsp("delete" + fKlassName, "dsp")->accept(fCodeProducer);

    generateFunMaps();

    // Global declarations
    generateExtGlobalDeclarations(fCodeProducer);
    generateGlobalDeclarations(fCodeProducer);

    generateInstanceInitFun("instanceInit" + fKlassName, "dsp", false, false)->accept(fCodeProducer);
    generateFillFun("fill" + fKlassName, "dsp", false, false)->accept(fCodeProducer);
}

dsp_factory_base* LLVMCodeContainer::produceFactory()
{
    // Sub containers
    generateSubContainers();

    llvm::PointerType* dsp_ptr = generateDspStruct();
    fCodeProducer = new LLVMInstVisitor(fModule, fBuilder, &fStructVisitor, dsp_ptr);

    generateFunMaps();

    // Global declarations
    generateExtGlobalDeclarations(fCodeProducer);
    generateGlobalDeclarations(fCodeProducer);

    generateStaticInitFun("classInit" + fKlassName, false)->accept(fCodeProducer);
    generateInstanceClear("instanceClear" + fKlassName, "dsp", false, false)->accept(fCodeProducer);
    generateInstanceConstants("instanceConstants" + fKlassName, "dsp", false, false)->accept(fCodeProducer);
    generateAllocate("allocate" + fKlassName, "dsp", false, false)->accept(fCodeProducer);
    generateDestroy("destroy" + fKlassName, "dsp", false, false)->accept(fCodeProducer);

    generateGetJSON();

    // Compute
    generateCompute();

    // Link LLVM modules defined in 'ffunction'
    set<string> S;
    string      error;

    collectLibrary(S);
    if (S.size() > 0) {
        for (auto& f : S) {
            string module_name = unquote(f);
            if (endWith(module_name, ".bc") || endWith(module_name, ".ll")) {
                ModulePTR module = loadModule(module_name, fContext);
                if (module) {
                    bool res = linkModules(fModule, MovePTR(module), error);
                    if (!res) cerr << "WARNING : " << error << endl;
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

// Scalar
LLVMScalarCodeContainer::LLVMScalarCodeContainer(const string& name, int numInputs, int numOutputs)
    : LLVMCodeContainer(name, numInputs, numOutputs)
{
}

LLVMScalarCodeContainer::LLVMScalarCodeContainer(const string& name, int numInputs, int numOutputs, Module* module,
                                                 LLVMContext* context, int sub_container_type)
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
    BlockInst* block = InstBuilder::genBlockInst();
    // Control
    block->pushBackInst(fComputeBlockInstructions);
    // Generates the DSP loop
    block->pushBackInst(fCurLoop->generateScalarLoop(fFullCount));
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
    BlockInst* block = InstBuilder::genBlockInst();
    // Control
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
LLVMWorkStealingCodeContainer::LLVMWorkStealingCodeContainer(const string& name, int numInputs, int numOutputs)
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
    BlockInst* block = InstBuilder::genBlockInst();
    // Control
    block->pushBackInst(fComputeBlockInstructions);
    return block;
}
