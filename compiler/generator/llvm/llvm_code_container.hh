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

#ifndef _LLVM_CODE_CONTAINER_H
#define _LLVM_CODE_CONTAINER_H

#include "code_container.hh"
#include "llvm_instructions.hh"
#include "vec_code_container.hh"
#include "omp_code_container.hh"
#include "wss_code_container.hh"
#include "llvm_dsp_aux.hh"

#if defined(LLVM_35) || defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)
    #include <llvm/Support/FileSystem.h>
    #define sysfs_binary_flag sys::fs::F_None
#elif defined(LLVM_34)
    #define sysfs_binary_flag sys::fs::F_Binary
#else
    #define sysfs_binary_flag raw_fd_ostream::F_Binary
#endif

#if defined(LLVM_36) || defined(LLVM_37) || defined(LLVM_38) || defined(LLVM_39) || defined(LLVM_40) || defined(LLVM_50)
    #define STREAM_ERROR std::error_code
#else
    #define STREAM_ERROR std::string
#endif

using namespace std;
using namespace llvm;

class LLVMCodeContainer : public virtual CodeContainer {

    protected:

        // UI structure creation
        llvm::PointerType* fStructDSP;

        IRBuilder<>* fBuilder;
        IRBuilder<>* fAllocaBuilder;    // To be used for "alloca", which have to be added in the first "entry" block of the function.
        LLVMInstVisitor* fCodeProducer;
      
        Module* fModule;
        LLVMContext* fContext;
    
        void generateComputeBegin(const string& counter);
        void generateComputeEnd();
        void generateComputeDouble();

        void generateFillBegin(const string& counter);
        void generateFillEnd();

        void generateGetSampleRate(int field_index);
  
        void generateInfoFunctions(const string& classname, bool isvirtual);

        void generateClassInitBegin();
        void generateClassInitEnd();
    
        void generateInitFun();
        void generateInstanceInitFun();

        void generateInstanceInitBegin(const string& funname, bool internal = false);
        void generateInstanceInitEnd(const string& funname);
    
        void generateInstanceResetUserInterfaceBegin(bool internal = false);
        void generateInstanceResetUserInterfaceEnd();
    
        void generateInstanceClearBegin(bool internal = false);
        void generateInstanceClearEnd();
    
        void generateAllocateBegin();
        void generateAllocateEnd();

        void generateDestroyBegin();
        void generateDestroyEnd();

        void generateMetadata(llvm::PointerType* meta_type_ptr);

        void generateBuildUserInterfaceBegin();
        void generateBuildUserInterfaceEnd();
    
        void generateGetSize(LlvmValue size);

        void addGenericButton(const string& label, const string& zone, const string& button_type);
        void addGenericSlider(const string& label,
                            const string& zone,
                            float init,
                            float min,
                            float max,
                            float step,
                            const string& type);
        void addGenericBargraph(const string& label,
                                const string& zone,
                                float min,
                                float max,
                                const string& type);

        LlvmValue genInt1(int number)
        {
            return ConstantInt::get(llvm::Type::getInt1Ty(getContext()), number);
        }

        LlvmValue genInt32(int number)
        {
            return ConstantInt::get(llvm::Type::getInt32Ty(getContext()), number);
        }

        LlvmValue genInt64(int number)
        {
            return ConstantInt::get(llvm::Type::getInt64Ty(getContext()), number);
        }

        LlvmValue genFloat(const string& number)
        {
        #if defined(LLVM_40) || defined(LLVM_50)
            return ConstantFP::get(getContext(), APFloat(APFloat::IEEEsingle(), number));
        #else
            return ConstantFP::get(getContext(), APFloat(APFloat::IEEEsingle, number));
        #endif
        }

        LlvmValue genFloat(float number)
        {
            return ConstantFP::get(getContext(), APFloat(number));
        }
        
        LLVMContext& getContext();
    
        // To be used for mathematical function mapping (-fm and exp10 on OSX)
        void generateFunMap(const string& fun1_aux, const string& fun2_aux, int num_args, bool body = false);
    
        void generateFunMaps();

    public:

        LLVMCodeContainer(const string& name, int numInputs, int numOutputs);
        LLVMCodeContainer(const string& name, int numInputs, int numOutputs, Module* module, LLVMContext* context);
        virtual ~LLVMCodeContainer();
      
        virtual dsp_factory_base* produceFactory();
    
        virtual void generateCompute() = 0;
        void produceInternal();

        CodeContainer* createScalarContainer(const string& name, int sub_container_type);

        static CodeContainer* createContainer(const string& name, int numInputs, int numOutputs);

};

class LLVMScalarCodeContainer : public LLVMCodeContainer {

    protected:

    public:

        LLVMScalarCodeContainer(const string& name, int numInputs, int numOutputs);
        LLVMScalarCodeContainer(const string& name, int numInputs, int numOutputs, Module* module, LLVMContext* context, int sub_container_type);
        virtual ~LLVMScalarCodeContainer();

        void generateCompute();

};

class LLVMVectorCodeContainer : public VectorCodeContainer, public LLVMCodeContainer {

    protected:

    public:

        LLVMVectorCodeContainer(const string& name, int numInputs, int numOutputs);
        virtual ~LLVMVectorCodeContainer();

        void generateCompute();

};

class LLVMOpenMPCodeContainer : public OpenMPCodeContainer, public LLVMCodeContainer {

    protected:

        void generateOMPDeclarations();
        void generateOMPCompute();

        void generateGOMP_parallel_start();
        void generateGOMP_parallel_end();
        LlvmValue generateGOMP_single_start();
        void generateGOMP_barrier();
        void generateGOMP_sections_start(LlvmValue number);
        void generateGOMP_sections_end();
        void generateGOMP_sections_next();

        void generateDSPOMPCompute();

    public:

        LLVMOpenMPCodeContainer(const string& name, int numInputs, int numOutputs);
        virtual ~LLVMOpenMPCodeContainer();

        void generateCompute();

};

class LLVMWorkStealingCodeContainer : public WSSCodeContainer, public LLVMCodeContainer {

    protected:

        void generateComputeThreadBegin();
        void generateComputeThreadEnd();
        void generateComputeThreadExternal();

    public:

        LLVMWorkStealingCodeContainer(const string& name, int numInputs, int numOutputs);
        virtual ~LLVMWorkStealingCodeContainer();

        void generateCompute();

};

#endif
