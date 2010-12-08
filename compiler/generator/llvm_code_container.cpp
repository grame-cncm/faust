/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
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

/**********************************************************************
			- code_gen.h : generic code generator (projet FAUST) -


		Historique :
		-----------

***********************************************************************/
#include "llvm_code_container.hh"

#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Analysis/Passes.h>
#include <llvm/Support/StandardPasses.h>

using namespace std;

extern bool gVectorSwitch;
extern int gVectorLoopVariant;
extern int gVecSize;

CodeContainer* LLVMCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new LLVMScalarCodeContainer(0, 1, fModule, fBuilder, sub_container_type, name);
}

// Generic
class PrintVisitor : public InstVisitor {

    virtual void visit(DeclareVarInst* inst)
    {
        printf("visit DeclareVarInst\n");
    }

};

void LLVMCodeContainer::generateFillBegin()
{
    vector<const llvm::Type*> llvm_fill_args;
    llvm_fill_args.push_back(fDSP_ptr);
    llvm_fill_args.push_back(fBuilder->getInt32Ty());

    const llvm::Type* buffer_type;

    if (fSubContainerType == kInt) {
        // int* type
        buffer_type = fBuilder->getInt32Ty();
    } else {
        // real* output
        buffer_type = (itfloat() == Typed::kFloat) ? fBuilder->getFloatTy() : fBuilder->getDoubleTy();
    }

    llvm_fill_args.push_back(PointerType::get(buffer_type, 0));
    FunctionType* llvm_fill_type = FunctionType::get(fBuilder->getVoidTy(), llvm_fill_args, false);

    Function* llvm_fill = Function::Create(llvm_fill_type, GlobalValue::ExternalLinkage, "fill" + fPrefix, fModule);
    llvm_fill->setCallingConv(CallingConv::C);
    llvm_fill->setAlignment(2);

    Function::arg_iterator llvm_fill_args_it = llvm_fill->arg_begin();
    Value* arg1 = llvm_fill_args_it++;
    arg1->setName("dsp");
    Value* arg2 = llvm_fill_args_it++;
    arg2->setName("count");
    Value* arg4 = llvm_fill_args_it++;
    arg4->setName("output");

    //llvm_fill->dump();

    // Add a first block
    fBuilder->SetInsertPoint(BasicBlock::Create(getGlobalContext(), "block_code", llvm_fill));
}

void LLVMCodeContainer::generateFillEnd()
{
    Function* llvm_fill = fModule->getFunction("fill" + fPrefix);
    assert(llvm_fill);
    BasicBlock* return_block = BasicBlock::Create(getGlobalContext(), "return", llvm_fill);
    ReturnInst::Create(getGlobalContext(), return_block);

    // If previous block branch from previous to current
    if (fBuilder->GetInsertBlock())
        fBuilder->CreateBr(return_block);

    //llvm_fill->dump();
    verifyFunction(*llvm_fill);
}

void LLVMCodeContainer::generateComputeBegin(const string& counter)
{
    vector<const llvm::Type*> llvm_compute_args;
    llvm_compute_args.push_back(fDSP_ptr);
    llvm_compute_args.push_back(fBuilder->getInt32Ty());

    //if (!gVectorSwitch) {
        const llvm::Type* buffer_type = (itfloat() == Typed::kFloat) ? fBuilder->getFloatTy() : fBuilder->getDoubleTy();
        llvm_compute_args.push_back(PointerType::get(PointerType::get(buffer_type, 0), 0));
        llvm_compute_args.push_back(PointerType::get(PointerType::get(buffer_type, 0), 0));
    /*
    } else {
        llvm_compute_args.push_back(PointerType::get(PointerType::get(VectorType::get(fBuilder->getFloatTy(), gVecSize), 0), 0));
        llvm_compute_args.push_back(PointerType::get(PointerType::get(VectorType::get(fBuilder->getFloatTy(), gVecSize), 0), 0));
    }
    */

    FunctionType* llvm_compute_type = FunctionType::get(fBuilder->getVoidTy(), llvm_compute_args, false);

    Function* llvm_compute = Function::Create(llvm_compute_type, GlobalValue::ExternalLinkage, "compute" + fPrefix, fModule);
    llvm_compute->setCallingConv(CallingConv::C);
    llvm_compute->setAlignment(2);

    SmallVector<AttributeWithIndex, 4> attributes;
    AttributeWithIndex PAWI;
    PAWI.Index = 3U; PAWI.Attrs = 0 | Attribute::NoAlias;
    attributes.push_back(PAWI);
    PAWI.Index = 4U; PAWI.Attrs = 0 | Attribute::NoAlias;
    attributes.push_back(PAWI);
    llvm_compute->setAttributes( AttrListPtr::get(attributes.begin(), attributes.end()));

    Function::arg_iterator llvm_compute_args_it = llvm_compute->arg_begin();
    Value* arg1 = llvm_compute_args_it++;
    arg1->setName("dsp");
    Value* arg2 = llvm_compute_args_it++;
    arg2->setName(counter);
    Value* arg3 = llvm_compute_args_it++;
    arg3->setName("inputs");
    Value* arg4 = llvm_compute_args_it++;
    arg4->setName("outputs");

    // Add a first block
    fBuilder->SetInsertPoint(BasicBlock::Create(getGlobalContext(), "block_code", llvm_compute));
}

void LLVMCodeContainer::generateComputeEnd()
{
    Function* llvm_compute = fModule->getFunction("compute" + fPrefix);
    assert(llvm_compute);
    BasicBlock* return_block = BasicBlock::Create(getGlobalContext(), "return", llvm_compute);
    ReturnInst::Create(getGlobalContext(), return_block);

    // If previous block branch from previous to current
    if (fBuilder->GetInsertBlock())
        fBuilder->CreateBr(return_block);

    llvm_compute->dump();
    verifyFunction(*llvm_compute);
}

void LLVMCodeContainer::generateGetNumInputs()
{
    vector<const llvm::Type*> llvm_getNumInputs_args;
    llvm_getNumInputs_args.push_back(fDSP_ptr);
    FunctionType* llvm_getNumInputs_type = FunctionType::get(fBuilder->getInt32Ty(), llvm_getNumInputs_args, false);

    Function* input_fun = Function::Create(llvm_getNumInputs_type, Function::ExternalLinkage, "getNumInputs" + fPrefix, fModule);
    input_fun->setCallingConv(CallingConv::C);
    BasicBlock* block = BasicBlock::Create(getGlobalContext(), "entry", input_fun);
    ReturnInst::Create(getGlobalContext(), genInt32(fNumInputs), block);
    verifyFunction(*input_fun);
}

void LLVMCodeContainer::generateGetNumOutputs()
{
    vector<const llvm::Type*> llvm_getNumOutputs_args;
    llvm_getNumOutputs_args.push_back(fDSP_ptr);
    FunctionType* llvm_getNumOuputs_type = FunctionType::get(fBuilder->getInt32Ty(), llvm_getNumOutputs_args, false);

    Function* output_fun = Function::Create(llvm_getNumOuputs_type, Function::ExternalLinkage, "getNumOutputs" + fPrefix, fModule);
    output_fun->setCallingConv(CallingConv::C);
    BasicBlock* block = BasicBlock::Create(getGlobalContext(), "entry", output_fun);
    ReturnInst::Create(getGlobalContext(), genInt32(fNumOutputs), block);
    verifyFunction(*output_fun);
}

void LLVMCodeContainer::generateClassInitBegin()
{
    vector<const llvm::Type*> llvm_classInit_args;
    llvm_classInit_args.push_back(fBuilder->getInt32Ty());
    FunctionType* llvm_classInit_type = FunctionType::get(fBuilder->getVoidTy(), llvm_classInit_args, false);

    Function* llvm_classInit = Function::Create(llvm_classInit_type, Function::ExternalLinkage, "classInit" + fPrefix, fModule);
    llvm_classInit->setCallingConv(CallingConv::C);
    llvm_classInit->setAlignment(2);

    Function::arg_iterator llvm_classInit_args_it = llvm_classInit->arg_begin();
    Value* sample_freq = llvm_classInit_args_it++;
    sample_freq->setName("samplingFreq");

    // Add a first block
    fBuilder->SetInsertPoint(BasicBlock::Create(getGlobalContext(), "entry", llvm_classInit));
}

void LLVMCodeContainer::generateClassInitEnd()
{
    Function* llvm_classInit = fModule->getFunction("classInit" + fPrefix);
    assert(llvm_classInit);
    BasicBlock* return_block = BasicBlock::Create(getGlobalContext(), "return", llvm_classInit);
    ReturnInst::Create(getGlobalContext(), return_block);

    // If previous block branch from previous to current
    if (fBuilder->GetInsertBlock())
        fBuilder->CreateBr(return_block);

    //llvm_classInit->dump();
    verifyFunction(*llvm_classInit);
}

void LLVMCodeContainer::generateInstanceInitBegin(int sample_freq_field)
{
    vector<const llvm::Type*> llvm_instanceInit_args;
    llvm_instanceInit_args.push_back(fDSP_ptr);
    llvm_instanceInit_args.push_back(fBuilder->getInt32Ty());
    FunctionType* llvm_instanceInit_type = FunctionType::get(fBuilder->getVoidTy(), llvm_instanceInit_args, false);

    Function* llvm_instanceInit = Function::Create(llvm_instanceInit_type, Function::ExternalLinkage, "instanceInit" + fPrefix, fModule);
    llvm_instanceInit->setCallingConv(CallingConv::C);
    llvm_instanceInit->setAlignment(2);

    Function::arg_iterator llvm_instanceInit_args_it = llvm_instanceInit->arg_begin();
    Value* dsp = llvm_instanceInit_args_it++;
    dsp->setName("dsp");
    Value* sample_freq = llvm_instanceInit_args_it++;
    sample_freq->setName("samplingFreq");

    // Add a first block
    fBuilder->SetInsertPoint(BasicBlock::Create(getGlobalContext(), "entry", llvm_instanceInit));
}

void LLVMCodeContainer::generateInstanceInitEnd()
{
    Function* llvm_instanceInit = fModule->getFunction("instanceInit" + fPrefix);
    assert(llvm_instanceInit);
    BasicBlock* return_block = BasicBlock::Create(getGlobalContext(), "return", llvm_instanceInit);
    ReturnInst::Create(getGlobalContext(), return_block);

    // If previous block branch from previous to current
    if (fBuilder->GetInsertBlock())
        fBuilder->CreateBr(return_block);

    //llvm_instanceInit->dump();
    verifyFunction(*llvm_instanceInit);
}

void LLVMCodeContainer::generateDestroyBegin()
{
    Function* llvm_destroy = fModule->getFunction("destroy" + fPrefix);
    assert(llvm_destroy);

    // Add a first block
    fBuilder->SetInsertPoint(BasicBlock::Create(getGlobalContext(), "entry", llvm_destroy));
}

void LLVMCodeContainer::generateDestroyEnd()
{
    Function* llvm_destroy = fModule->getFunction("destroy" + fPrefix);
    assert(llvm_destroy);
    BasicBlock* return_block = BasicBlock::Create(getGlobalContext(), "return", llvm_destroy);
    ReturnInst::Create(getGlobalContext(), return_block);

    // If previous block branch from previous to current
    if (fBuilder->GetInsertBlock())
        fBuilder->CreateBr(return_block);

    //llvm_destroy->dump();
    verifyFunction(*llvm_destroy);
}

void LLVMCodeContainer::generateInitFun()
{
    vector<const llvm::Type*> llvm_init_args;
    llvm_init_args.push_back(fDSP_ptr);
    llvm_init_args.push_back(fBuilder->getInt32Ty());
    FunctionType* llvm_init_type = FunctionType::get(fBuilder->getVoidTy(), llvm_init_args, false);

    Function* llvm_init = Function::Create(llvm_init_type, Function::ExternalLinkage, "init" + fPrefix, fModule);
    llvm_init->setCallingConv(CallingConv::C);
    llvm_init->setAlignment(2);

    Function::arg_iterator llvm_init_args_it = llvm_init->arg_begin();
    Value* arg1 = llvm_init_args_it++;
    arg1->setName("dsp");
    Value* arg2 = llvm_init_args_it++;
    arg2->setName("samplingFreq");

    /// llvm_init block
    BasicBlock* return_block2 = BasicBlock::Create(getGlobalContext(), "entry", llvm_init);
    vector<Value*> params1;
    params1.push_back(arg2);

    Function* llvm_classInit = fModule->getFunction("classInit" + fPrefix);
    assert(llvm_classInit);
    CallInst* call_inst1 = CallInst::Create(llvm_classInit, params1.begin(), params1.end(), "", return_block2);
    call_inst1->setCallingConv(CallingConv::C);
    call_inst1->setTailCall(true);

    vector<Value*> params2;
    params2.push_back(arg1);
    params2.push_back(arg2);

    Function* llvm_instanceInit = fModule->getFunction("instanceInit" + fPrefix);
    assert(llvm_instanceInit);
    CallInst* call_inst2 = CallInst::Create(llvm_instanceInit, params2.begin(), params2.end(), "", return_block2);
    call_inst2->setCallingConv(CallingConv::C);
    call_inst2->setTailCall(true);

    ReturnInst::Create(getGlobalContext(), return_block2);
    verifyFunction(*llvm_init);
}

void LLVMCodeContainer::generateMetadata()
{
    /*
    vector<const llvm::Type*> llvm_metaData_args;
    llvm_metaData_args.push_back(fStruct_Meta_ptr);
    FunctionType* llvm_metaData_type = FunctionType::get(fBuilder->getVoidTy(), llvm_metaData_args, false);

    Function* llvm_metaData = Function::Create(llvm_metaData_type, GlobalValue::ExternalLinkage, fPrefix + "llvm_metadata", fModule);
    llvm_metaData->setCallingConv(CallingConv::C);
    llvm_metaData->setAlignment(2);

    // Name arguments
    Function::arg_iterator llvm_metaData_args_it = llvm_metaData->arg_begin();
    Value* meta = llvm_metaData_args_it++;
    meta->setName("m");
    */
}

void LLVMCodeContainer::generateBuildUserInterfaceBegin()
{
    // Function is actually created in LLVMTypeInstVisitor::generateDataStruct
    Function* llvm_buildUserInterface = fModule->getFunction("buildUserInterface" + fPrefix);

    // Get the already created init block and insert in it.
    BasicBlock* init_block = llvm_buildUserInterface->getBasicBlockList().begin();
    fBuilder->SetInsertPoint(init_block);
}

void LLVMCodeContainer::generateBuildUserInterfaceEnd()
{
    Function* llvm_buildUserInterface = fModule->getFunction("buildUserInterface" + fPrefix);
    BasicBlock* return_block = BasicBlock::Create(getGlobalContext(), "return", llvm_buildUserInterface);
    ReturnInst::Create(getGlobalContext(), return_block);

    // Insert return block
    fBuilder->CreateBr(return_block);
    verifyFunction(*llvm_buildUserInterface);
}

void LLVMCodeContainer::produceInternal()
{
    // Creates DSP structure
    LLVMTypeInstVisitor fTypeBuilder(fModule, fPrefix);

    // Sort arrays to be at the begining
    generateDeclarations(&fTypeBuilder);

    // Now we can create the DSP type
    fDSP_ptr = fTypeBuilder.getDSPType(false);
    std::map<string, int> fields_names = fTypeBuilder.getFieldNames();
    fStruct_UI_ptr = fTypeBuilder.getUIType();
    LlvmValue fUIInterface_ptr = fTypeBuilder.getUIPtr();

    generateGetNumInputs();
    generateGetNumOutputs();

    // Init code generator with fields_names
    //if (gVectorSwitch) {
        //fCodeProducer = new LLVMVectorInstVisitor(fModule, fBuilder, fields_names, fStruct_UI_ptr, fUIInterface_ptr, gVecSize);
    //    fCodeProducer = new LLVMInstVisitor(fModule, fBuilder, fields_names, fStruct_UI_ptr, fUIInterface_ptr, fPrefix);
    //} else {
        fCodeProducer = new LLVMInstVisitor(fModule, fBuilder, fields_names, fStruct_UI_ptr, fUIInterface_ptr, fDSP_ptr, fPrefix);
    //}

    // Global declarations
    generateExtGlobalDeclarations(fCodeProducer);
    generateGlobalDeclarations(fCodeProducer);

    generateInstanceInitBegin(fields_names["fSamplingFreq"]);
    generateInit(fCodeProducer);
    generateInstanceInitEnd();

    // Fill
    generateFillBegin();

    generateComputeBlock(fCodeProducer);

    ForLoopInst* loop = fCurLoop->generateScalarLoop();
    loop->accept(fCodeProducer);

    generateFillEnd();
}

Module* LLVMCodeContainer::produceModule(const string& filename)
{
    // Always generates fSamplingFreq field and initialize it with the "samplingFreq" parameter of the init function
    pushGlobalDeclare(InstBuilder::genDecGlobalVar("fSamplingFreq", InstBuilder::genBasicTyped(Typed::kInt)));
    pushFrontInitMethod(InstBuilder::genStoreGlobalVar("fSamplingFreq", InstBuilder::genLoadFunArgsVar("samplingFreq")));

    fPrefix = "_llvm";

    // Sub containers
    generateSubContainers();

    // Creates DSP structure
    LLVMTypeInstVisitor1 fTypeBuilder(fModule, fPrefix);

    // Sort arrays to be at the begining
    generateDeclarations(&fTypeBuilder);

    // Now we can create the DSP type
    fDSP_ptr = fTypeBuilder.getDSPType();
    std::map<string, int> fields_names = fTypeBuilder.getFieldNames();
    fStruct_UI_ptr = fTypeBuilder.getUIType();
    LlvmValue fUIInterface_ptr = fTypeBuilder.getUIPtr();

    generateGetNumInputs();
    generateGetNumOutputs();

    // Init code generator with fields_names
    //if (gVectorSwitch) {
        //fCodeProducer = new LLVMVectorInstVisitor(fModule, fBuilder, fields_names, fStruct_UI_ptr, fUIInterface_ptr, gVecSize);
      //  fCodeProducer = new LLVMInstVisitor(fModule, fBuilder, fields_names, fStruct_UI_ptr, fUIInterface_ptr, fPrefix);
    //} else {
        fCodeProducer = new LLVMInstVisitor(fModule, fBuilder, fields_names, fStruct_UI_ptr, fUIInterface_ptr, fDSP_ptr, fPrefix);
    //}

    // Global declarations
    generateExtGlobalDeclarations(fCodeProducer);
    generateGlobalDeclarations(fCodeProducer);

    generateClassInitBegin();
    generateStaticInit(fCodeProducer);
    generateClassInitEnd();

    generateInstanceInitBegin(fields_names["fSamplingFreq"]);
    generateInit(fCodeProducer);
    generateInstanceInitEnd();

    generateDestroyBegin();
    generateDestroy(fCodeProducer);
    generateDestroyEnd();

    generateBuildUserInterfaceBegin();
    generateUserInterface(fCodeProducer);
    generateBuildUserInterfaceEnd();

    // Compute
    generateCompute();

    // Has to be done *after* generateInstanceInitBegin/generateInstanceInitEnd
    generateInitFun();

    if (filename == "") {
        fModule->dump();
    } else {
        std::string ErrorInfo;
        raw_fd_ostream Out(filename.c_str(), ErrorInfo, raw_fd_ostream::F_Binary);
        WriteBitcodeToFile(fModule, Out);
    }

    return fModule;
}

// Scalar
LLVMScalarCodeContainer::LLVMScalarCodeContainer(int numInputs, int numOutputs, const string& prefix)
    :LLVMCodeContainer(numInputs, numOutputs, prefix)
{}

LLVMScalarCodeContainer::LLVMScalarCodeContainer(int numInputs, int numOutputs, Module* module, IRBuilder<>* builder,  int sub_container_type, const string& prefix)
    :LLVMCodeContainer(numInputs, numOutputs, module, builder, prefix)
{
    fSubContainerType = sub_container_type;
}

LLVMScalarCodeContainer::~LLVMScalarCodeContainer()
{}

void LLVMScalarCodeContainer::generateCompute()
{
    generateComputeBegin("count");

    // Generates local variables declaration and setup
    generateComputeBlock(fCodeProducer);

    // Optimize Declare/Store/Load for fTemp variables
    ForLoopInst* loop = fCurLoop->generateScalarLoop();
    LLVMStackVariableRemover remover;
    remover.Mark(loop, "Temp");
    remover.Finish(loop);

    // Generates one single scalar loop
    remover.fResultLoop->accept(fCodeProducer);

    generateComputeEnd();
}

// Vector
LLVMVectorCodeContainer::LLVMVectorCodeContainer(int numInputs, int numOutputs, const string& prefix)
    :VectorCodeContainer(numInputs, numOutputs), LLVMCodeContainer(numInputs, numOutputs, prefix)
{}

LLVMVectorCodeContainer::~LLVMVectorCodeContainer()
{}

void LLVMVectorCodeContainer::generateCompute()
{
    // Prepare global loop
    StatementInst* block = NULL;
    if (gVectorLoopVariant == 0) {
        block = generateDAGLoopVariant0();
    } else {
        block = generateDAGLoopVariant1();
    }

    // Possibly generate separated functions
    generateComputeFunctions(fCodeProducer);

    generateComputeBegin("fullcount");

    // Sort arrays to be at the begining
    fComputeBlockInstructions->fCode.sort(sortFunction1);

    // Generates local variables declaration and setup
    generateComputeBlock(fCodeProducer);

    // Generate it
    assert(block);
    block->accept(fCodeProducer);

    generateComputeEnd();
}

// OpenMP
LLVMOpenMPCodeContainer::LLVMOpenMPCodeContainer(int numInputs, int numOutputs, const string& prefix)
    :OpenMPCodeContainer(numInputs, numOutputs), LLVMCodeContainer(numInputs, numOutputs, prefix)
{}

LLVMOpenMPCodeContainer::~LLVMOpenMPCodeContainer()
{}

void LLVMOpenMPCodeContainer::generateCompute()
{
    generateOMPDeclarations();

    generateComputeBegin("fullcount");

    // Generates OMP thread function
    generateOMPCompute();

    // Generates OMP data struct

    // Generates OMP thread function call
    generateGOMP_parallel_start(); // TODO : add parameters
    generateDSPOMPCompute();
    generateGOMP_parallel_end();

    generateComputeEnd();
}

void LLVMOpenMPCodeContainer::generateOMPCompute()
{
    // TODO
}

void LLVMOpenMPCodeContainer::generateDSPOMPCompute()
{
    vector<LlvmValue> fun_args;
    Function* dsp_omp_compute = fModule->getFunction("dsp_omp_compute");
    CallInst* call_inst = fBuilder->CreateCall(dsp_omp_compute, fun_args.begin(), fun_args.end());
    call_inst->setCallingConv(CallingConv::C);
}

void LLVMOpenMPCodeContainer::generateGOMP_parallel_start()
{
    vector<LlvmValue> fun_args;
    Function* GOMP_parallel_start = fModule->getFunction("GOMP_parallel_start");
    CallInst* call_inst = fBuilder->CreateCall(GOMP_parallel_start, fun_args.begin(), fun_args.end());
    call_inst->setCallingConv(CallingConv::C);
}

void LLVMOpenMPCodeContainer::generateGOMP_parallel_end()
{
    Function* GOMP_parallel_end = fModule->getFunction("GOMP_parallel_end");
    CallInst* call_inst = fBuilder->CreateCall(GOMP_parallel_end);
    call_inst->setCallingConv(CallingConv::C);
}

LlvmValue LLVMOpenMPCodeContainer::generateGOMP_single_start()
{
    Function* GOMP_single_start = fModule->getFunction("GOMP_single_start");
    CallInst* call_inst = fBuilder->CreateCall(GOMP_single_start);
    call_inst->setCallingConv(CallingConv::C);
    return call_inst;
}

void LLVMOpenMPCodeContainer::generateGOMP_barrier()
{
    Function* GOMP_barrier = fModule->getFunction("GOMP_barrier");
    CallInst* call_inst = fBuilder->CreateCall(GOMP_barrier);
    call_inst->setCallingConv(CallingConv::C);
}

void LLVMOpenMPCodeContainer::generateGOMP_sections_start(LlvmValue number)
{
    vector<LlvmValue> fun_args;
    fun_args[0] = number;
    Function* GOMP_sections_start = fModule->getFunction("GOMP_sections_start");
    CallInst* call_inst = fBuilder->CreateCall(GOMP_sections_start, fun_args.begin(), fun_args.end());
    call_inst->setCallingConv(CallingConv::C);
}

void LLVMOpenMPCodeContainer::generateGOMP_sections_end()
{
    Function* GOMP_sections_end = fModule->getFunction("GOMP_sections_end");
    CallInst* call_inst = fBuilder->CreateCall(GOMP_sections_end);
    call_inst->setCallingConv(CallingConv::C);
}

void LLVMOpenMPCodeContainer::generateGOMP_sections_next()
{
    Function* GOMP_sections_next = fModule->getFunction("GOMP_sections_next");
    CallInst* call_inst = fBuilder->CreateCall(GOMP_sections_next);
    call_inst->setCallingConv(CallingConv::C);
}

void LLVMOpenMPCodeContainer::generateOMPDeclarations()
{
    // Type Definitions
    vector<const llvm::Type*>FuncTy_0_args;
    vector<const llvm::Type*>FuncTy_2_args;
    PointerType* PointerTy_3 = PointerType::get(IntegerType::get(getGlobalContext(), 8), 0);

    FuncTy_2_args.push_back(PointerTy_3);
    FunctionType* FuncTy_2 = FunctionType::get(
    /*Result=*/llvm::Type::getVoidTy(getGlobalContext()),
    /*Params=*/FuncTy_2_args,
    /*isVarArg=*/false);

    PointerType* PointerTy_1 = PointerType::get(FuncTy_2, 0);

    FuncTy_0_args.push_back(PointerTy_1);
    FuncTy_0_args.push_back(PointerTy_3);
    FuncTy_0_args.push_back(IntegerType::get(getGlobalContext(), 32));
    FunctionType* FuncTy_0 = FunctionType::get(
    /*Result=*/llvm::Type::getVoidTy(getGlobalContext()),
    /*Params=*/FuncTy_0_args,
    /*isVarArg=*/false);

    vector<const llvm::Type*>FuncTy_4_args;
    FunctionType* FuncTy_4 = FunctionType::get(
    /*Result=*/llvm::Type::getVoidTy(getGlobalContext()),
    /*Params=*/FuncTy_4_args,
    /*isVarArg=*/false);

    vector<const llvm::Type*>FuncTy_5_args;
    FunctionType* FuncTy_5 = FunctionType::get(
    /*Result=*/IntegerType::get(getGlobalContext(), 8),
    /*Params=*/FuncTy_5_args,
    /*isVarArg=*/false);

    vector<const llvm::Type*>FuncTy_6_args;
    FuncTy_6_args.push_back(IntegerType::get(getGlobalContext(), 32));
    FunctionType* FuncTy_6 = FunctionType::get(
    /*Result=*/IntegerType::get(getGlobalContext(), 32),
    /*Params=*/FuncTy_6_args,
    /*isVarArg=*/false);

    vector<const llvm::Type*>FuncTy_7_args;
    FunctionType* FuncTy_7 = FunctionType::get(
    /*Result=*/IntegerType::get(getGlobalContext(), 32),
    /*Params=*/FuncTy_7_args,
    /*isVarArg=*/false);

    // Function Declarations
    Function* func_GOMP_parallel_start = Function::Create(
    /*Type=*/FuncTy_0,
    /*Linkage=*/GlobalValue::ExternalLinkage,
    /*Name=*/"GOMP_parallel_start", fModule); // (external, no body)
    func_GOMP_parallel_start->setCallingConv(CallingConv::C);

    Function* func_GOMP_parallel_end = Function::Create(
    /*Type=*/FuncTy_4,
    /*Linkage=*/GlobalValue::ExternalLinkage,
    /*Name=*/"GOMP_parallel_end", fModule); // (external, no body)
    func_GOMP_parallel_end->setCallingConv(CallingConv::C);

    Function* func_GOMP_single_start = Function::Create(
    /*Type=*/FuncTy_5,
    /*Linkage=*/GlobalValue::ExternalLinkage,
    /*Name=*/"GOMP_single_start", fModule); // (external, no body)
    func_GOMP_single_start->setCallingConv(CallingConv::C);

    Function* func_GOMP_barrier = Function::Create(
    /*Type=*/FuncTy_4,
    /*Linkage=*/GlobalValue::ExternalLinkage,
    /*Name=*/"GOMP_barrier", fModule); // (external, no body)
    func_GOMP_barrier->setCallingConv(CallingConv::C);

    Function* func_GOMP_sections_start = Function::Create(
    /*Type=*/FuncTy_6,
    /*Linkage=*/GlobalValue::ExternalLinkage,
    /*Name=*/"GOMP_sections_start", fModule); // (external, no body)
    func_GOMP_sections_start->setCallingConv(CallingConv::C);

    Function* func_GOMP_sections_end = Function::Create(
    /*Type=*/FuncTy_4,
    /*Linkage=*/GlobalValue::ExternalLinkage,
    /*Name=*/"GOMP_sections_end", fModule); // (external, no body)
    func_GOMP_sections_end->setCallingConv(CallingConv::C);

    Function* func_GOMP_sections_next = Function::Create(
    /*Type=*/FuncTy_7,
    /*Linkage=*/GlobalValue::ExternalLinkage,
    /*Name=*/"GOMP_sections_next", fModule); // (external, no body)
    func_GOMP_sections_next->setCallingConv(CallingConv::C);

    // DSP
    Function* func_dsp_omp_compute = Function::Create(
    /*Type=*/FuncTy_2,
    /*Linkage=*/GlobalValue::ExternalLinkage,
    /*Name=*/"dsp_omp_compute", fModule); // (external, no body)
    func_dsp_omp_compute->setCallingConv(CallingConv::C);
}

// Works stealing scheduler
LLVMWorkStealingCodeContainer::LLVMWorkStealingCodeContainer(int numInputs, int numOutputs, const string& prefix)
    :WSSCodeContainer(numInputs, numOutputs), LLVMCodeContainer(numInputs, numOutputs, prefix)
{}

LLVMWorkStealingCodeContainer::~LLVMWorkStealingCodeContainer()
{}

void LLVMWorkStealingCodeContainer::generateComputeThreadBegin()
{
    vector<const llvm::Type*> llvm_computethread_args;
    llvm_computethread_args.push_back(fDSP_ptr);
    llvm_computethread_args.push_back(fBuilder->getInt32Ty());

    FunctionType* llvm_computethread_type = FunctionType::get(fBuilder->getVoidTy(), llvm_computethread_args, false);

    Function* llvm_computethread = Function::Create(llvm_computethread_type, GlobalValue::ExternalLinkage, "computeThread", fModule);
    llvm_computethread->setCallingConv(CallingConv::C);
    llvm_computethread->setAlignment(2);

    Function::arg_iterator llvm_computethread_args_it = llvm_computethread->arg_begin();
    Value* arg1 = llvm_computethread_args_it++;
    arg1->setName("dsp");
    Value* arg2 = llvm_computethread_args_it++;
    arg2->setName("num_thread");

    // Add a first block
    fBuilder->SetInsertPoint(BasicBlock::Create(getGlobalContext(), "block_code", llvm_computethread));
}

void LLVMWorkStealingCodeContainer::generateComputeThreadEnd()
{
    Function* llvm_computethread = fModule->getFunction("computeThread");
    assert(llvm_computethread);
    BasicBlock* return_block = BasicBlock::Create(getGlobalContext(), "return", llvm_computethread);
    ReturnInst::Create(getGlobalContext(), return_block);

    // If previous block branch from previous to current
    if (fBuilder->GetInsertBlock())
        fBuilder->CreateBr(return_block);

    //llvm_computethread->dump();
    verifyFunction(*llvm_computethread);
}

void LLVMWorkStealingCodeContainer::generateComputeThreadExternal()
{
    vector<const llvm::Type*> llvm_computethread_args;
    llvm_computethread_args.push_back(PointerType::get(llvm::Type::getInt8Ty(getGlobalContext()), 0));
    llvm_computethread_args.push_back(fBuilder->getInt32Ty());

    FunctionType* llvm_computethread_type = FunctionType::get(fBuilder->getVoidTy(), llvm_computethread_args, false);

    Function* llvm_computethread = Function::Create(llvm_computethread_type, GlobalValue::ExternalLinkage, "computeThreadExternal", fModule);
    llvm_computethread->setCallingConv(CallingConv::C);
    llvm_computethread->setAlignment(2);

    Function::arg_iterator llvm_computethread_args_it = llvm_computethread->arg_begin();
    Value* arg1 = llvm_computethread_args_it++;
    arg1->setName("dsp");
    Value* arg2 = llvm_computethread_args_it++;
    arg2->setName("num_thread");

    // Add a first block
    fBuilder->SetInsertPoint(BasicBlock::Create(getGlobalContext(), "block_code", llvm_computethread));

    Function* llvm_computethreadInternal = fModule->getFunction("computeThread");
    assert(llvm_computethreadInternal);

    CallInst* call_inst = fBuilder->CreateCall2(llvm_computethreadInternal, fBuilder->CreateBitCast(arg1, fDSP_ptr), arg2);
    call_inst->setCallingConv(CallingConv::C);
    call_inst->setTailCall(true);
    fBuilder->CreateRetVoid();

    //llvm_computethread->dump();
    verifyFunction(*llvm_computethread);
}

Module* LLVMWorkStealingCodeContainer::produceModule(const string& filename)
{
    // Transform some stack variables in struct variables
    MoveStack2Struct();

    // Specific init code
    generateDAGLoopWSSAux3();

    // Inherited method
    return LLVMCodeContainer::produceModule(filename);
}

void LLVMWorkStealingCodeContainer::generateCompute()
{
    lclgraph dag;
    CodeLoop::sortGraph(fCurLoop, dag);
    computeForwardDAG(dag);

    // Prepare global loop
    StatementInst* block = generateDAGLoopWSS(dag);

    // Possibly generate separated functions
    generateComputeFunctions(fCodeProducer);

    // Generates "computeThread" code
    generateComputeThreadBegin();

    // Generate it
    block->accept(fCodeProducer);

    generateComputeThreadEnd();

    // Generates "compute" code
    generateDAGLoopWSSAux2(fComputeBlockInstructions);

    generateComputeBegin("fullcount");

    // Sort arrays to be at the begining
    fComputeBlockInstructions->fCode.sort(sortFunction1);

    // Generates local variables declaration and setup
    fComputeBlockInstructions->accept(fCodeProducer);

    generateComputeEnd();

    // Generates prototype to be used by worker threads
    generateComputeThreadExternal();
}

/*
// Transform the loop in a function + function call
ForLoopInst* loop = fCurLoop->generateScalarLoop();

BasicCloneVisitor cloner;

Loop2FunctionBuider builder("fun_loop1", dynamic_cast<ForLoopInst*>(loop->clone(&cloner)));
builder.fFunctionDef->dump();
builder.fFunctionDef->accept(fCodeProducer);

SeqLoopBuilderVisitor loop_sequencer(dynamic_cast<ForLoopInst*>(loop->clone(&cloner)), dynamic_cast<ForLoopInst*>(loop->clone(&cloner)));
Loop2FunctionBuider builder1("combined1", loop_sequencer.fResultLoop);
builder1.fFunctionDef->accept(fCodeProducer);

builder1.fFunctionCall->dump();
*/

// Function definition test
/*
list<StatementInst*> code;
list<StatementInst*> code2;
list<NamedTyped*> types;
list<NamedTyped*> types1;

list<ValueInst*> args1;
list<ValueInst*> args2;

types.push_back(InstBuilder::genNamedTyped("arg1", InstBuilder::genBasicTyped(Typed::kFloat)));
types.push_back(InstBuilder::genNamedTyped("arg2", InstBuilder::genArrayTyped(InstBuilder::genBasicTyped(Typed::kFloat), 0)));

types1.push_back(InstBuilder::genNamedTyped("arg1", InstBuilder::genBasicTyped(Typed::kFloat)));
types1.push_back(InstBuilder::genNamedTyped("arg2", InstBuilder::genArrayTyped(InstBuilder::genBasicTyped(Typed::kFloat), 0)));

args1.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("temp1", Address::kStack)));
args1.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("arg2", Address::kFunArgs)));

args2.push_back(InstBuilder::genFloatNumInst(60));
args2.push_back(InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("arg2", Address::kFunArgs)));

StatementInst* fun2 = InstBuilder::genDeclareFunInst("fun2", InstBuilder::genFunTyped(types1, InstBuilder::genBasicTyped(Typed::kFloat)), code2);
fun2->accept(fCodeProducer);

StatementInst* fun3 = InstBuilder::genDeclareFunInst("fun3", InstBuilder::genFunTyped(types1, InstBuilder::genBasicTyped(Typed::kVoid)), code2);
fun3->accept(fCodeProducer);

fModule->dump();

StatementInst* inst1 = InstBuilder::genDeclareVarInst("temp1", InstBuilder::genBasicTyped(Typed::kFloat), Address::kStack, InstBuilder::genFloatNumInst(3));
StatementInst* inst2 = InstBuilder::genDeclareVarInst("temp2", InstBuilder::genBasicTyped(Typed::kFloat), Address::kStack,
    InstBuilder::genBinopInst(0, InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("arg1", Address::kFunArgs)), InstBuilder::genFloatNumInst(60)));
StatementInst* inst3 = InstBuilder::genDeclareVarInst("temp3", InstBuilder::genBasicTyped(Typed::kFloat), Address::kStack,
    InstBuilder::genBinopInst(0, InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("temp1", Address::kStack)), InstBuilder::genFloatNumInst(60)));
StatementInst* inst4 = InstBuilder::genDeclareVarInst("temp4", InstBuilder::genBasicTyped(Typed::kFloat), Address::kStack,
    InstBuilder::genBinopInst(2, InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("temp3", Address::kStack)),
        InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("temp1", Address::kStack))));

StatementInst* inst5 = InstBuilder::genDeclareVarInst("temp5", InstBuilder::genBasicTyped(Typed::kFloat), Address::kStack, InstBuilder::genFunCallInst("fun2", args1));
//StatementInst* inst6 = InstBuilder::genFunCallInst("fun3", args2);

code.push_back(inst1);
code.push_back(inst2);
code.push_back(inst3);
code.push_back(inst4);

code.push_back(inst5);
code.push_back(InstBuilder::genRetInst());  // Mandatory
//code.push_back(inst6);

StatementInst* fun1 = InstBuilder::genDeclareFunInst("fun1", InstBuilder::genFunTyped(types, InstBuilder::genBasicTyped(Typed::kVoid)), code);
fun1->accept(fCodeProducer);
*/

/*
ExecutionEngine* fJIT;
std::string ErrorMessage;
fJIT = EngineBuilder(fModule).setErrorStr(&ErrorMessage).create();
cout << ErrorMessage;
assert(fJIT);

getNumInputsFun fGetNumInputs = (getNumInputsFun)(intptr_t)fJIT->getPointerToFunction(fModule->getFunction("getNumInputs_llvm"));
printf("function %x\n", fGetNumInputs);
llvm_dsp dsp;
int num = fGetNumInputs(&dsp);
printf("module num %d\n", num);
*/

/*
TargetData* target = new TargetData(fModule->getDataLayout());
FunctionPassManager manager(fModule);
manager.add(target);
manager.add(createInstructionCombiningPass());

manager.add(createCFGSimplificationPass());
// Promote allocas to registers.
//manager.add(createPromoteMemoryToRegisterPass());

createStandardFunctionPasses(&manager, 3);

manager.run(*fModule->getFunction("compute" + fPrefix));
manager.run(*fModule->getFunction("init" + fPrefix));
*/
