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

#ifndef _LLVM_CODE_CONTAINER_H
#define _LLVM_CODE_CONTAINER_H

#include "code_container.hh"
#include "llvm_instructions.hh"
#include "omp_code_container.hh"
#include "struct_manager.hh"
#include "vec_code_container.hh"
#include "wss_code_container.hh"

using namespace std;
using namespace llvm;

class LLVMCodeContainer : public virtual CodeContainer {
   protected:
    using CodeContainer::generateFillFun;
    using CodeContainer::generateInstanceInitFun;

    IRBuilder<>*      fBuilder;
    LLVMInstVisitor*  fCodeProducer;
    StructInstVisitor fStructVisitor;

    Module*      fModule;
    LLVMContext* fContext;

    // To be used for mathematical function mapping (-fm and exp10 on OSX)
    void generateFunMap(const string& fun1_aux, const string& fun2_aux, int num_args, bool body = false);
    void generateFunMaps();

    PointerType* generateDspStruct();

    // To be implemented in each LLVMScalarCodeContainer, LLVMVectorCodeContainer
    // and LLVMWorkStealingCodeContainer classes
    virtual void generateCompute() = 0;
    
    template <typename REAL>
    void generateGetJSON()
    {
        PointerType*  string_ptr = PointerType::get(fBuilder->getInt8Ty(), 0);
        LLVMVecTypes  getJSON_args;
        FunctionType* getJSON_type = FunctionType::get(string_ptr, makeArrayRef(getJSON_args), false);
        Function* getJSON = Function::Create(getJSON_type, GlobalValue::ExternalLinkage, "getJSON" + fKlassName, fModule);

        // JSON generation
        JSONInstVisitor<REAL> json_visitor1;
        generateUserInterface(&json_visitor1);

        map<string, int> path_index_table;
        for (const auto& it : json_visitor1.fPathTable) {
            // Get field index
            path_index_table[it.second] = fStructVisitor.getFieldOffset(it.first);
        }

        faustassert(fStructVisitor.getFieldOffset("fSampleRate") != -1);

        JSONInstVisitor<REAL> json_visitor2("", "", fNumInputs, fNumOutputs, fStructVisitor.getFieldOffset("fSampleRate"), "", "",
                                            FAUSTVERSION, gGlobal->printCompilationOptions1(), gGlobal->gReader.listLibraryFiles(),
                                            gGlobal->gImportDirList, fStructVisitor.getStructSize(), path_index_table, MemoryLayoutType());
        generateUserInterface(&json_visitor2);
        generateMetaData(&json_visitor2);

        BasicBlock* return_block = BasicBlock::Create(*fContext, "return_block", getJSON);
        ReturnInst::Create(*fContext, fCodeProducer->genStringConstant(json_visitor2.JSON(true)), return_block);
        
        verifyFunction(*getJSON);
        fBuilder->ClearInsertionPoint();
    }
 
    void init(const string& name, int numInputs, int numOutputs, Module* module, LLVMContext* context);

   public:
    LLVMCodeContainer(const string& name, int numInputs, int numOutputs);
    LLVMCodeContainer(const string& name, int numInputs, int numOutputs, Module* module, LLVMContext* context);
    virtual ~LLVMCodeContainer();

    virtual dsp_factory_base* produceFactory();
    void                      produceInternal();

    CodeContainer* createScalarContainer(const string& name, int sub_container_type);

    static CodeContainer* createContainer(const string& name, int numInputs, int numOutputs);
};

class LLVMScalarCodeContainer : public LLVMCodeContainer {
   protected:
    void       generateCompute();
    BlockInst* generateComputeAux();

   public:
    LLVMScalarCodeContainer(const string& name, int numInputs, int numOutputs);
    LLVMScalarCodeContainer(const string& name, int numInputs, int numOutputs, Module* module, LLVMContext* context,
                            int sub_container_type);
    virtual ~LLVMScalarCodeContainer();
};

class LLVMVectorCodeContainer : public VectorCodeContainer, public LLVMCodeContainer {
   protected:
    void       generateCompute();
    BlockInst* generateComputeAux();

   public:
    LLVMVectorCodeContainer(const string& name, int numInputs, int numOutputs);
    virtual ~LLVMVectorCodeContainer();
};

class LLVMOpenMPCodeContainer : public OpenMPCodeContainer, public LLVMCodeContainer {
   protected:
    void       generateOMPDeclarations();
    void       generateOMPCompute();
    void       generateCompute();
    BlockInst* generateComputeAux();

    void      generateGOMP_parallel_start();
    void      generateGOMP_parallel_end();
    LLVMValue generateGOMP_single_start();
    void      generateGOMP_barrier();
    void      generateGOMP_sections_start(LLVMValue num);
    void      generateGOMP_sections_end();
    void      generateGOMP_sections_next();

    void generateDSPOMPCompute();

   public:
    LLVMOpenMPCodeContainer(const string& name, int numInputs, int numOutputs);
    virtual ~LLVMOpenMPCodeContainer();
};

class LLVMWorkStealingCodeContainer : public WSSCodeContainer, public LLVMCodeContainer {
   protected:
    void       generateCompute();
    BlockInst* generateComputeAux();

   public:
    LLVMWorkStealingCodeContainer(const string& name, int numInputs, int numOutputs);
    virtual ~LLVMWorkStealingCodeContainer();
};

#endif
