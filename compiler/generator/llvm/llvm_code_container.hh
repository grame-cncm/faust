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

#ifndef _LLVM_CODE_CONTAINER_H
#define _LLVM_CODE_CONTAINER_H

#include "code_container.hh"
#include "llvm_instructions.hh"
#include "omp_code_container.hh"
#include "struct_manager.hh"
#include "vec_code_container.hh"
#include "wss_code_container.hh"

#include <llvm/Support/FileSystem.h>

#define sysfs_binary_flag sys::fs::F_None

#if defined(LLVM_35)
#define STREAM_ERROR string
#define ModulePTR Module*
#define MovePTR(ptr) ptr
#else
#define STREAM_ERROR std::error_code
#define ModulePTR std::unique_ptr<Module>
#define MovePTR(ptr) std::move(ptr)
#endif

using namespace std;
using namespace llvm;

class LLVMCodeContainer : public virtual CodeContainer {
   protected:
    using CodeContainer::generateFillFun;
    using CodeContainer::generateInstanceInitFun;

    IRBuilder<>* fBuilder;

    LLVMInstVisitor* fCodeProducer;

    StructInstVisitor fStructVisitor;

    Module*      fModule;
    LLVMContext* fContext;

    void generateGetJSON();

    // To be used for mathematical function mapping (-fm and exp10 on OSX)
    void generateFunMap(const string& fun1_aux, const string& fun2_aux, int num_args, bool body = false);
    void generateFunMaps();

    llvm::PointerType* generateDspStruct();

    // To be implemented in each LLVMScalarCodeContainer, LLVMVectorCodeContainer and LLVMWorkStealingCodeContainer
    // classes
    virtual void generateCompute() = 0;

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
