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

#include "llvm_code_container.hh"
#include "exception.hh"
#include "global.hh"

#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Analysis/Passes.h>

using namespace std;

#ifdef LLVM_29
#include <llvm/Support/StandardPasses.h>
   #define VECTOR_OF_TYPES vector<const llvm::Type*>
   #define MAP_OF_TYPES std::map<Typed::VarType, const llvm::Type*>
   #define LLVM_TYPE const llvm::Type*
   #define MAKE_VECTOR_OF_TYPES(vec) vec
   #define MAKE_IXD(beg, end) beg, end
   #define MAKE_ARGS(args) args
   #define CREATE_CALL(fun, args) fBuilder->CreateCall(fun, args.begin(), args.end())
   #define CREATE_CALL1(fun, args, str, block) CallInst::Create(fun, args.begin(), args.end(), str, block)
#endif

#if defined(LLVM_30) || defined(LLVM_31)
   #define VECTOR_OF_TYPES vector<llvm::Type*>
   #define MAP_OF_TYPES std::map<Typed::VarType, llvm::Type*>
   #define LLVM_TYPE llvm::Type*
   #define MAKE_VECTOR_OF_TYPES(vec) makeArrayRef(vec)
   #define MAKE_IXD(beg, end) llvm::ArrayRef<llvm::Value*>(beg, end)
   #define MAKE_ARGS(args) llvm::ArrayRef<llvm::Value*>(args)
   #define CREATE_CALL(fun, args) fBuilder->CreateCall(fun, MAKE_VECTOR_OF_TYPES(args))
   #define CREATE_CALL1(fun, args, str, block) CallInst::Create(fun, MAKE_VECTOR_OF_TYPES(args), str, block)
#endif

CodeContainer* LLVMCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new LLVMScalarCodeContainer(name, 0, 1, fModule, sub_container_type);
}

CodeContainer* LLVMCodeContainer::createContainer(const string& name, int numInputs, int numOutputs)
{
    CodeContainer* container;

    if (gGlobal->gFloatSize == 3) {
        throw faustexception("ERROR : quad format not supported in LLVM\n");
    }
    gGlobal->gDSPStruct = true;

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

// Generic
class PrintVisitor : public InstVisitor {

    virtual void visit(DeclareVarInst* inst)
    {
        printf("visit DeclareVarInst\n");
    }

};

void LLVMCodeContainer::generateFillBegin(const string& counter)
{
    VECTOR_OF_TYPES llvm_fill_args;
    llvm_fill_args.push_back(fStruct_DSP_ptr);
    llvm_fill_args.push_back(fBuilder->getInt32Ty());

    LLVM_TYPE buffer_type;

    if (fSubContainerType == kInt) {
        // int* type
        buffer_type = fBuilder->getInt32Ty();
    } else {
        // real* output
        buffer_type = (itfloat() == Typed::kFloat) ? fBuilder->getFloatTy() : fBuilder->getDoubleTy();
    }

    llvm_fill_args.push_back(PointerType::get(buffer_type, 0));
    FunctionType* llvm_fill_type = FunctionType::get(fBuilder->getVoidTy(), MAKE_VECTOR_OF_TYPES(llvm_fill_args), false);
    Function* llvm_fill = Function::Create(llvm_fill_type, GlobalValue::InternalLinkage, "fill" + fKlassName, fModule);
    llvm_fill->setCallingConv(CallingConv::C);

    Function::arg_iterator llvm_fill_args_it = llvm_fill->arg_begin();
    Value* arg1 = llvm_fill_args_it++;
    arg1->setName("dsp");
    Value* arg2 = llvm_fill_args_it++;
    arg2->setName(counter);
    Value* arg4 = llvm_fill_args_it++;
    arg4->setName("output");

    //llvm_fill->dump();

    // Add a first block
    fBuilder->SetInsertPoint(BasicBlock::Create(getGlobalContext(), "block_code", llvm_fill));
}

void LLVMCodeContainer::generateFillEnd()
{
    Function* llvm_fill = fModule->getFunction("fill" + fKlassName);
    assert(llvm_fill);
    BasicBlock* return_block = BasicBlock::Create(getGlobalContext(), "return", llvm_fill);
    ReturnInst::Create(getGlobalContext(), return_block);

    // If previous block branch from previous to current
    if (fBuilder->GetInsertBlock()) {
        fBuilder->CreateBr(return_block);
    }

    //llvm_fill->dump();
    verifyFunction(*llvm_fill);
    fBuilder->ClearInsertionPoint();
}

void LLVMCodeContainer::generateComputeBegin(const string& counter)
{
    VECTOR_OF_TYPES llvm_compute_args;
    llvm_compute_args.push_back(fStruct_DSP_ptr);
    llvm_compute_args.push_back(fBuilder->getInt32Ty());

    //if (!gGlobal->gVectorSwitch) {
        LLVM_TYPE buffer_type = (itfloat() == Typed::kFloat) ? fBuilder->getFloatTy() : fBuilder->getDoubleTy();
        llvm_compute_args.push_back(PointerType::get(PointerType::get(buffer_type, 0), 0));
        llvm_compute_args.push_back(PointerType::get(PointerType::get(buffer_type, 0), 0));
    /*
    } else {
        llvm_compute_args.push_back(PointerType::get(PointerType::get(VectorType::get(fBuilder->getFloatTy(), gGlobal->gVecSize), 0), 0));
        llvm_compute_args.push_back(PointerType::get(PointerType::get(VectorType::get(fBuilder->getFloatTy(), gGlobal->gVecSize), 0), 0));
    }
    */

    FunctionType* llvm_compute_type = FunctionType::get(fBuilder->getVoidTy(), llvm_compute_args, false);

    Function* llvm_compute = Function::Create(llvm_compute_type, GlobalValue::ExternalLinkage, "compute" + fKlassName, fModule);
    llvm_compute->setCallingConv(CallingConv::C);

    SmallVector<AttributeWithIndex, 4> attributes;
    AttributeWithIndex PAWI;
    PAWI.Index = 3U; PAWI.Attrs = Attribute::NoAlias;
    attributes.push_back(PAWI);
    PAWI.Index = 4U; PAWI.Attrs = Attribute::NoAlias;
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
    Function* llvm_compute = fModule->getFunction("compute" + fKlassName);
    assert(llvm_compute);
    BasicBlock* return_block = BasicBlock::Create(getGlobalContext(), "return", llvm_compute);
    ReturnInst::Create(getGlobalContext(), return_block);

    // If previous block branch from previous to current
    if (fBuilder->GetInsertBlock()) {
        fBuilder->CreateBr(return_block);
    }

    //llvm_compute->dump();
    verifyFunction(*llvm_compute);
    fBuilder->ClearInsertionPoint();
}

void LLVMCodeContainer::generateGetSampleRate(int field_index)
{
    VECTOR_OF_TYPES llvm_getSR_args;
    llvm_getSR_args.push_back(fStruct_DSP_ptr);

    FunctionType* llvm_getSR_type = FunctionType::get(fBuilder->getInt32Ty(), MAKE_VECTOR_OF_TYPES(llvm_getSR_args), false);

    Function* sr_fun = Function::Create(llvm_getSR_type, Function::ExternalLinkage, "getSampleRate" + fKlassName, fModule);
    sr_fun->setCallingConv(CallingConv::C);

    Function::arg_iterator llvm_SR_args_it = sr_fun->arg_begin();
    Value* dsp = llvm_SR_args_it++;
    dsp->setName("dsp");

    BasicBlock* block = BasicBlock::Create(getGlobalContext(), "entry", sr_fun);
    fBuilder->SetInsertPoint(block);

    Value* zone_ptr = fBuilder->CreateStructGEP(dsp, field_index);
    Value* load_ptr = fBuilder->CreateLoad(zone_ptr);

    ReturnInst::Create(getGlobalContext(), load_ptr, block); verifyFunction(*sr_fun);
    fBuilder->ClearInsertionPoint();
 }

void LLVMCodeContainer::generateGetNumInputs(bool internal)
{
    VECTOR_OF_TYPES llvm_getNumInputs_args;
    llvm_getNumInputs_args.push_back(fStruct_DSP_ptr);
    FunctionType* llvm_getNumInputs_type = FunctionType::get(fBuilder->getInt32Ty(), MAKE_VECTOR_OF_TYPES(llvm_getNumInputs_args), false);

    Function* input_fun = Function::Create(llvm_getNumInputs_type, (internal) ? Function::InternalLinkage : Function::ExternalLinkage, "getNumInputs" + fKlassName, fModule);
    input_fun->setCallingConv(CallingConv::C);
    BasicBlock* block = BasicBlock::Create(getGlobalContext(), "entry", input_fun);
    ReturnInst::Create(getGlobalContext(), genInt32(fNumInputs), block);

    verifyFunction(*input_fun);
    fBuilder->ClearInsertionPoint();
}

void LLVMCodeContainer::generateGetNumOutputs(bool internal)
{
    VECTOR_OF_TYPES llvm_getNumOutputs_args;
    llvm_getNumOutputs_args.push_back(fStruct_DSP_ptr);
    FunctionType* llvm_getNumOuputs_type = FunctionType::get(fBuilder->getInt32Ty(), MAKE_VECTOR_OF_TYPES(llvm_getNumOutputs_args), false);

    Function* output_fun = Function::Create(llvm_getNumOuputs_type, (internal) ? Function::InternalLinkage : Function::ExternalLinkage, "getNumOutputs" + fKlassName, fModule);
    output_fun->setCallingConv(CallingConv::C);
    BasicBlock* block = BasicBlock::Create(getGlobalContext(), "entry", output_fun);
    ReturnInst::Create(getGlobalContext(), genInt32(fNumOutputs), block);

    verifyFunction(*output_fun);
    fBuilder->ClearInsertionPoint();
}

void LLVMCodeContainer::generateClassInitBegin()
{
    VECTOR_OF_TYPES llvm_classInit_args;
    llvm_classInit_args.push_back(fBuilder->getInt32Ty());
    FunctionType* llvm_classInit_type = FunctionType::get(fBuilder->getVoidTy(), MAKE_VECTOR_OF_TYPES(llvm_classInit_args), false);

    Function* llvm_classInit = Function::Create(llvm_classInit_type, Function::ExternalLinkage, "classInit" + fKlassName, fModule);
    llvm_classInit->setCallingConv(CallingConv::C);

    Function::arg_iterator llvm_classInit_args_it = llvm_classInit->arg_begin();
    Value* sample_freq = llvm_classInit_args_it++;
    sample_freq->setName("samplingFreq");

    // Add a first block
    fBuilder->SetInsertPoint(BasicBlock::Create(getGlobalContext(), "entry", llvm_classInit));
}

void LLVMCodeContainer::generateClassInitEnd()
{
    Function* llvm_classInit = fModule->getFunction("classInit" + fKlassName);
    assert(llvm_classInit);
    BasicBlock* return_block = BasicBlock::Create(getGlobalContext(), "return", llvm_classInit);
    ReturnInst::Create(getGlobalContext(), return_block);

    // If previous block branch from previous to current
    if (fBuilder->GetInsertBlock()) {
        fBuilder->CreateBr(return_block);
    }

    //llvm_classInit->dump();
    verifyFunction(*llvm_classInit);
    fBuilder->ClearInsertionPoint();
}

void LLVMCodeContainer::generateInstanceInitBegin(bool internal)
{
    VECTOR_OF_TYPES llvm_instanceInit_args;
    llvm_instanceInit_args.push_back(fStruct_DSP_ptr);
    llvm_instanceInit_args.push_back(fBuilder->getInt32Ty());
    FunctionType* llvm_instanceInit_type = FunctionType::get(fBuilder->getVoidTy(), MAKE_VECTOR_OF_TYPES(llvm_instanceInit_args), false);

    Function* llvm_instanceInit = Function::Create(llvm_instanceInit_type, (internal) ? Function::InternalLinkage : Function::ExternalLinkage, "instanceInit" + fKlassName, fModule);
    llvm_instanceInit->setCallingConv(CallingConv::C);

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
    Function* llvm_instanceInit = fModule->getFunction("instanceInit" + fKlassName);
    assert(llvm_instanceInit);
    BasicBlock* return_block = BasicBlock::Create(getGlobalContext(), "return", llvm_instanceInit);
    ReturnInst::Create(getGlobalContext(), return_block);

    // If previous block branch from previous to current
    if (fBuilder->GetInsertBlock()) {
        fBuilder->CreateBr(return_block);
    }

    //llvm_instanceInit->dump();
    verifyFunction(*llvm_instanceInit);
    fBuilder->ClearInsertionPoint();
}

void LLVMCodeContainer::generateDestroyBegin()
{
    Function* llvm_destroy = fModule->getFunction("destroy" + fKlassName);
    assert(llvm_destroy);

    // Add a first block
    fBuilder->SetInsertPoint(BasicBlock::Create(getGlobalContext(), "entry", llvm_destroy));
}

void LLVMCodeContainer::generateDestroyEnd()
{
    Function* llvm_destroy = fModule->getFunction("destroy" + fKlassName);
    assert(llvm_destroy);
    BasicBlock* return_block = BasicBlock::Create(getGlobalContext(), "return", llvm_destroy);
    ReturnInst::Create(getGlobalContext(), return_block);

    // If previous block branch from previous to current
    if (fBuilder->GetInsertBlock()) {
        fBuilder->CreateBr(return_block);
    }

    //llvm_destroy->dump();
    verifyFunction(*llvm_destroy);
    fBuilder->ClearInsertionPoint();
}

void LLVMCodeContainer::generateAllocateBegin()
{
    Function* llvm_allocate = fModule->getFunction("allocate" + fKlassName);
    assert(llvm_allocate);

    // Add a first block
    fBuilder->SetInsertPoint(BasicBlock::Create(getGlobalContext(), "entry", llvm_allocate));
}

void LLVMCodeContainer::generateAllocateEnd()
{
    Function* llvm_allocate = fModule->getFunction("allocate" + fKlassName);
    assert(llvm_allocate);
    BasicBlock* return_block = BasicBlock::Create(getGlobalContext(), "return", llvm_allocate);
    ReturnInst::Create(getGlobalContext(), return_block);

    // If previous block branch from previous to current
    if (fBuilder->GetInsertBlock()) {
        fBuilder->CreateBr(return_block);
    }

    //llvm_allocate->dump();
    verifyFunction(*llvm_allocate);
    fBuilder->ClearInsertionPoint();
}

void LLVMCodeContainer::generateInitFun()
{
    VECTOR_OF_TYPES llvm_init_args;
    llvm_init_args.push_back(fStruct_DSP_ptr);
    llvm_init_args.push_back(fBuilder->getInt32Ty());
    FunctionType* llvm_init_type = FunctionType::get(fBuilder->getVoidTy(), MAKE_VECTOR_OF_TYPES(llvm_init_args), false);

    Function* llvm_init = Function::Create(llvm_init_type, Function::ExternalLinkage, "init" + fKlassName, fModule);
    llvm_init->setCallingConv(CallingConv::C);

    Function::arg_iterator llvm_init_args_it = llvm_init->arg_begin();
    Value* arg1 = llvm_init_args_it++;
    arg1->setName("dsp");
    Value* arg2 = llvm_init_args_it++;
    arg2->setName("samplingFreq");

    /// llvm_init block
    BasicBlock* return_block2 = BasicBlock::Create(getGlobalContext(), "entry", llvm_init);
    vector<Value*> params1;
    params1.push_back(arg2);

    Function* llvm_classInit = fModule->getFunction("classInit" + fKlassName);
    assert(llvm_classInit);
    CallInst* call_inst1 = CREATE_CALL1(llvm_classInit, params1, "", return_block2);
    call_inst1->setCallingConv(CallingConv::C);

    vector<Value*> params2;
    params2.push_back(arg1);
    params2.push_back(arg2);

    Function* llvm_instanceInit = fModule->getFunction("instanceInit" + fKlassName);
    assert(llvm_instanceInit);
    CallInst* call_inst2 = CREATE_CALL1(llvm_instanceInit, params2, "", return_block2);
    call_inst2->setCallingConv(CallingConv::C);

    ReturnInst::Create(getGlobalContext(), return_block2);
    verifyFunction(*llvm_init);
    fBuilder->ClearInsertionPoint();
}

void LLVMCodeContainer::generateMetadata(llvm::PointerType* meta_type_ptr)
{
    VECTOR_OF_TYPES llvm_metaData_args;
    llvm_metaData_args.push_back(meta_type_ptr);
    FunctionType* llvm_metaData_type = FunctionType::get(fBuilder->getVoidTy(), MAKE_VECTOR_OF_TYPES(llvm_metaData_args), false);

    Function* llvm_metaData = Function::Create(llvm_metaData_type, GlobalValue::ExternalLinkage, "metadata" + fKlassName, fModule);
    llvm_metaData->setCallingConv(CallingConv::C);

    // Name arguments
    Function::arg_iterator llvm_metaData_args_it = llvm_metaData->arg_begin();
    Value* meta = llvm_metaData_args_it++;
    meta->setName("m");

    BasicBlock* init_block = BasicBlock::Create(getGlobalContext(), "init", llvm_metaData);
    fBuilder->SetInsertPoint(init_block);
    
    Value* idx0[2];
    idx0[0] = genInt64(0);
    idx0[1] = genInt32(0);
    Value* meta_ptr = fBuilder->CreateGEP(meta, MAKE_IXD(idx0, idx0+2));
    LoadInst* load_meta_ptr = fBuilder->CreateLoad(meta_ptr);

    Value* idx1[2];
    idx1[0] = genInt64(0);
    idx1[1] = genInt32(1);
    Value* mth_ptr = fBuilder->CreateGEP(meta, MAKE_IXD(idx1, idx1+2));
    LoadInst* mth = fBuilder->CreateLoad(mth_ptr);

    for (map<Tree, set<Tree> >::iterator i = gGlobal->gMetaDataSet.begin(); i != gGlobal->gMetaDataSet.end(); i++) {
        GlobalVariable* llvm_label1;
        GlobalVariable* llvm_label2;
        if (i->first != tree("author")) {
            llvm_label1 = fCodeProducer->addStringConstant(tree2str(i->first));
            llvm_label2 = fCodeProducer->addStringConstant(tree2str(*(i->second.begin())));
        } else {
            for (set<Tree>::iterator j = i->second.begin(); j != i->second.end(); j++) {
                if (j == i->second.begin()) {
                    llvm_label1 = fCodeProducer->addStringConstant(tree2str(i->first));
                    llvm_label2 = fCodeProducer->addStringConstant(tree2str(*j));
                } else {
                    llvm_label1 = fCodeProducer->addStringConstant("contributor");
                    llvm_label2 = fCodeProducer->addStringConstant(tree2str(*j));
                }
            }
        }
    
        Value* idx2[3];
        idx2[0] = load_meta_ptr;
        idx2[1] = fBuilder->CreateConstGEP2_32(llvm_label1, 0, 0);
        idx2[2] = fBuilder->CreateConstGEP2_32(llvm_label2, 0, 0);
        CallInst* call_inst = fBuilder->CreateCall(mth, MAKE_IXD(idx2, idx2+3));
        call_inst->setCallingConv(CallingConv::C);
    }

    // Create return block
    BasicBlock* return_block = BasicBlock::Create(getGlobalContext(), "return", llvm_metaData);
    ReturnInst::Create(getGlobalContext(), return_block);

    // Insert return block
    fBuilder->CreateBr(return_block);
    verifyFunction(*llvm_metaData);
    fBuilder->ClearInsertionPoint();
}

void LLVMCodeContainer::generateBuildUserInterfaceBegin()
{
    // Function is actually created in LLVMTypeInstVisitor::generateDataStruct
    Function* llvm_buildUserInterface = fModule->getFunction("buildUserInterface" + fKlassName);

    // Get the already created init block and insert in it.
    BasicBlock* init_block = llvm_buildUserInterface->getBasicBlockList().begin();
    fBuilder->SetInsertPoint(init_block);
}

void LLVMCodeContainer::generateBuildUserInterfaceEnd()
{
    Function* llvm_buildUserInterface = fModule->getFunction("buildUserInterface" + fKlassName);
    BasicBlock* return_block = BasicBlock::Create(getGlobalContext(), "return", llvm_buildUserInterface);
    ReturnInst::Create(getGlobalContext(), return_block);

    // Insert return block
    fBuilder->CreateBr(return_block);
    verifyFunction(*llvm_buildUserInterface);
    fBuilder->ClearInsertionPoint();
}

void LLVMCodeContainer::produceInternal()
{
    // Creates DSP structure
    LLVMTypeInstVisitor fTypeBuilder(fModule, fKlassName);

    // Sort arrays to be at the begining
    generateDeclarations(&fTypeBuilder);

    // Now we can create the DSP type
    fStruct_DSP_ptr = fTypeBuilder.getDSPType(true, false);

    generateGetNumInputs(true);
    generateGetNumOutputs(true);

    // TODO : Input and output rates

    // Init code generator with fields_names
    //if (gGlobal->gVectorSwitch) {
        //fCodeProducer = new LLVMVectorInstVisitor(fModule, fBuilder, fields_names, fStruct_UI_ptr, fUIInterface_ptr, gGlobal->gVecSize);
    //    fCodeProducer = new LLVMInstVisitor(fModule, fBuilder, fields_names, fStruct_UI_ptr, fUIInterface_ptr, fKlassName);
    //} else {
        fCodeProducer = new LLVMInstVisitor(fModule, fBuilder, fTypeBuilder.getFieldNames(), fTypeBuilder.getUIPtr(), fStruct_DSP_ptr, fKlassName);
    //}

    // Global declarations
    generateExtGlobalDeclarations(fCodeProducer);
    generateGlobalDeclarations(fCodeProducer);

    generateInstanceInitBegin(true);
    generateInit(fCodeProducer);
    generateInstanceInitEnd();

    // Fill
    string counter = "count";
    generateFillBegin(counter);

    generateComputeBlock(fCodeProducer);

    ForLoopInst* loop = fCurLoop->generateScalarLoop(counter);
    loop->accept(fCodeProducer);

    generateFillEnd();
}

Module* LLVMCodeContainer::produceModule(const string& filename)
{
    // Initialize "fSamplingFreq" with the "samplingFreq" parameter of the init function
    if (!fGeneratedSR)
        pushDeclare(InstBuilder::genDecStructVar("fSamplingFreq", InstBuilder::genBasicTyped(Typed::kInt)));
    pushFrontInitMethod(InstBuilder::genStoreStructVar("fSamplingFreq", InstBuilder::genLoadFunArgsVar("samplingFreq")));

    fKlassName = "_" + fKlassName;

    // Sub containers
    generateSubContainers();

    // Creates DSP structure
    LLVMTypeInstVisitor1 fTypeBuilder(fModule, fKlassName);

    // Sort arrays to be at the begining
    generateDeclarations(&fTypeBuilder);

    // Now we can create the DSP type
    fStruct_DSP_ptr = fTypeBuilder.getDSPType(false);

    std::map<string, int> fields_names = fTypeBuilder.getFieldNames();
    generateGetSampleRate(fields_names["fSamplingFreq"]);

    generateGetNumInputs();
    generateGetNumOutputs();

    // Init code generator with fields_names
    //if (gGlobal->gVectorSwitch) {
        //fCodeProducer = new LLVMVectorInstVisitor(fModule, fBuilder, fields_names, fStruct_UI_ptr, fUIInterface_ptr, gGlobal->gVecSize);
      //  fCodeProducer = new LLVMInstVisitor(fModule, fBuilder, fields_names, fStruct_UI_ptr, fUIInterface_ptr, fKlassName);
    //} else {
        fCodeProducer = new LLVMInstVisitor(fModule, fBuilder, fields_names, fTypeBuilder.getUIPtr(), fStruct_DSP_ptr, fKlassName);
    //}

    // Global declarations
    generateExtGlobalDeclarations(fCodeProducer);
    generateGlobalDeclarations(fCodeProducer);

    generateClassInitBegin();
    generateStaticInit(fCodeProducer);
    generateClassInitEnd();

    generateInstanceInitBegin();
    generateInit(fCodeProducer);
    generateInstanceInitEnd();
    
    generateAllocateBegin();
    generateAllocate(fCodeProducer);
    generateAllocateEnd();

    generateDestroyBegin();
    generateDestroy(fCodeProducer);
    generateDestroyEnd();

    generateMetadata(fTypeBuilder.getMetaType());

    generateBuildUserInterfaceBegin();
    generateUserInterface(fCodeProducer);
    generateBuildUserInterfaceEnd();

    // Compute
    generateCompute();

    // Has to be done *after* generateInstanceInitBegin/generateInstanceInitEnd
    generateInitFun();
    
    if (filename != "") {
        std::string err;
        raw_fd_ostream out(filename.c_str(), err, raw_fd_ostream::F_Binary);
        WriteBitcodeToFile(fModule, out);
    }

    return fModule;
}

// Scalar
LLVMScalarCodeContainer::LLVMScalarCodeContainer(const string& name, int numInputs, int numOutputs)
    :LLVMCodeContainer(name, numInputs, numOutputs)
{}

LLVMScalarCodeContainer::LLVMScalarCodeContainer(const string& name, int numInputs, int numOutputs, Module* module, int sub_container_type)
    :LLVMCodeContainer(name, numInputs, numOutputs, module)
{
    fSubContainerType = sub_container_type;
}

LLVMScalarCodeContainer::~LLVMScalarCodeContainer()
{}

void LLVMScalarCodeContainer::generateCompute()
{
    generateComputeBegin(fFullCount);

    // Generates local variables declaration and setup
    generateComputeBlock(fCodeProducer);

    // Optimize Declare/Store/Load for fTemp variables
    ForLoopInst* loop = fCurLoop->generateScalarLoop(fFullCount);
    LLVMStackVariableRemover remover;
    remover.Mark(loop, "Temp");
    remover.Finish(loop);

    // Generates one single scalar loop
    remover.fResultLoop->accept(fCodeProducer);

    generateComputeEnd();
}

// Vector
LLVMVectorCodeContainer::LLVMVectorCodeContainer(const string& name, int numInputs, int numOutputs)
    :VectorCodeContainer(numInputs, numOutputs), LLVMCodeContainer(name, numInputs, numOutputs)
{}

LLVMVectorCodeContainer::~LLVMVectorCodeContainer()
{}

void LLVMVectorCodeContainer::generateCompute()
{
    // Possibly generate separated functions
    generateComputeFunctions(fCodeProducer);

    generateComputeBegin(fFullCount);

    // Generates local variables declaration and setup
    generateComputeBlock(fCodeProducer);

    // Generate it
    fDAGBlock->accept(fCodeProducer);

    generateComputeEnd();
}

// OpenMP
LLVMOpenMPCodeContainer::LLVMOpenMPCodeContainer(const string& name, int numInputs, int numOutputs)
    :OpenMPCodeContainer(numInputs, numOutputs), LLVMCodeContainer(name, numInputs, numOutputs)
{}

LLVMOpenMPCodeContainer::~LLVMOpenMPCodeContainer()
{}

void LLVMOpenMPCodeContainer::generateCompute()
{
    generateOMPDeclarations();
    generateComputeBegin(fFullCount);

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
    CallInst* call_inst = CREATE_CALL(dsp_omp_compute, fun_args);
    call_inst->setCallingConv(CallingConv::C);
}

void LLVMOpenMPCodeContainer::generateGOMP_parallel_start()
{
    vector<LlvmValue> fun_args;
    Function* GOMP_parallel_start = fModule->getFunction("GOMP_parallel_start");
    CallInst* call_inst = CREATE_CALL(GOMP_parallel_start, fun_args);
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
    CallInst* call_inst = CREATE_CALL(GOMP_sections_start, fun_args);
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
    VECTOR_OF_TYPES FuncTy_0_args;
    VECTOR_OF_TYPES FuncTy_2_args;
    PointerType* PointerTy_3 = PointerType::get(IntegerType::get(getGlobalContext(), 8), 0);

    FuncTy_2_args.push_back(PointerTy_3);
    FunctionType* FuncTy_2 = FunctionType::get(
    /*Result=*/llvm::Type::getVoidTy(getGlobalContext()),
    /*Params=*/MAKE_VECTOR_OF_TYPES(FuncTy_2_args),
    /*isVarArg=*/false);

    PointerType* PointerTy_1 = PointerType::get(FuncTy_2, 0);

    FuncTy_0_args.push_back(PointerTy_1);
    FuncTy_0_args.push_back(PointerTy_3);
    FuncTy_0_args.push_back(IntegerType::get(getGlobalContext(), 32));
    FunctionType* FuncTy_0 = FunctionType::get(
    /*Result=*/llvm::Type::getVoidTy(getGlobalContext()),
    /*Params=*/MAKE_VECTOR_OF_TYPES(FuncTy_0_args),
    /*isVarArg=*/false);

    VECTOR_OF_TYPES FuncTy_4_args;
    FunctionType* FuncTy_4 = FunctionType::get(
    /*Result=*/llvm::Type::getVoidTy(getGlobalContext()),
    /*Params=*/MAKE_VECTOR_OF_TYPES(FuncTy_4_args),
    /*isVarArg=*/false);

    VECTOR_OF_TYPES FuncTy_5_args;
    FunctionType* FuncTy_5 = FunctionType::get(
    /*Result=*/IntegerType::get(getGlobalContext(), 8),
    /*Params=*/MAKE_VECTOR_OF_TYPES(FuncTy_5_args),
    /*isVarArg=*/false);

    VECTOR_OF_TYPES FuncTy_6_args;
    FuncTy_6_args.push_back(IntegerType::get(getGlobalContext(), 32));
    FunctionType* FuncTy_6 = FunctionType::get(
    /*Result=*/IntegerType::get(getGlobalContext(), 32),
    /*Params=*/MAKE_VECTOR_OF_TYPES(FuncTy_6_args),
    /*isVarArg=*/false);

    VECTOR_OF_TYPES FuncTy_7_args;
    FunctionType* FuncTy_7 = FunctionType::get(
    /*Result=*/IntegerType::get(getGlobalContext(), 32),
    /*Params=*/MAKE_VECTOR_OF_TYPES(FuncTy_7_args),
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
LLVMWorkStealingCodeContainer::LLVMWorkStealingCodeContainer(const string& name, int numInputs, int numOutputs)
    :WSSCodeContainer(numInputs, numOutputs, "dsp"), LLVMCodeContainer(name, numInputs, numOutputs)
{}

LLVMWorkStealingCodeContainer::~LLVMWorkStealingCodeContainer()
{}

void LLVMWorkStealingCodeContainer::generateComputeThreadBegin()
{
    VECTOR_OF_TYPES llvm_computethread_args;
    llvm_computethread_args.push_back(fStruct_DSP_ptr);
    llvm_computethread_args.push_back(fBuilder->getInt32Ty());

    FunctionType* llvm_computethread_type = FunctionType::get(fBuilder->getVoidTy(), MAKE_VECTOR_OF_TYPES(llvm_computethread_args), false);

    Function* llvm_computethread = Function::Create(llvm_computethread_type, GlobalValue::ExternalLinkage, "computeThread", fModule);
    llvm_computethread->setCallingConv(CallingConv::C);

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
    if (fBuilder->GetInsertBlock()) {
        fBuilder->CreateBr(return_block);
    }

    //llvm_computethread->dump();
    verifyFunction(*llvm_computethread);
    fBuilder->ClearInsertionPoint();
}

void LLVMWorkStealingCodeContainer::generateComputeThreadExternal()
{
    VECTOR_OF_TYPES llvm_computethread_args;
    llvm_computethread_args.push_back(PointerType::get(llvm::Type::getInt8Ty(getGlobalContext()), 0));
    llvm_computethread_args.push_back(fBuilder->getInt32Ty());

    FunctionType* llvm_computethread_type = FunctionType::get(fBuilder->getVoidTy(), MAKE_VECTOR_OF_TYPES(llvm_computethread_args), false);

    Function* llvm_computethread = Function::Create(llvm_computethread_type, GlobalValue::ExternalLinkage, "computeThreadExternal", fModule);
    llvm_computethread->setCallingConv(CallingConv::C);

    Function::arg_iterator llvm_computethread_args_it = llvm_computethread->arg_begin();
    Value* arg1 = llvm_computethread_args_it++;
    arg1->setName("dsp");
    Value* arg2 = llvm_computethread_args_it++;
    arg2->setName("num_thread");

    // Add a first block
    fBuilder->SetInsertPoint(BasicBlock::Create(getGlobalContext(), "block_code", llvm_computethread));

    Function* llvm_computethreadInternal = fModule->getFunction("computeThread");
    assert(llvm_computethreadInternal);

    CallInst* call_inst = fBuilder->CreateCall2(llvm_computethreadInternal, fBuilder->CreateBitCast(arg1, fStruct_DSP_ptr), arg2);
    call_inst->setCallingConv(CallingConv::C);
    fBuilder->CreateRetVoid();

    //llvm_computethread->dump();
    verifyFunction(*llvm_computethread);
    fBuilder->ClearInsertionPoint();
}

void LLVMWorkStealingCodeContainer::generateCompute()
{
    // Possibly generate separated functions
    generateComputeFunctions(fCodeProducer);

    // Generates "computeThread" code
    generateComputeThreadBegin();

    // Generate it
    fThreadLoopBlock->accept(fCodeProducer);

    generateComputeThreadEnd();

    // Generates "compute" code
    generateComputeBegin(fFullCount);

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

manager.run(*fModule->getFunction("compute" + fKlassName));
manager.run(*fModule->getFunction("init" + fKlassName));
*/
