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

/**********************************************************************
			- code_gen.h : generic code generator (projet FAUST) -


		Historique :
		-----------

***********************************************************************/

#include "code_container.hh"
#include "llvm_instructions.hh"

#include "vec_code_container.hh"
#include "omp_code_container.hh"
#include "wss_code_container.hh"

#include <llvm/System/Host.h>

using namespace std;
using namespace llvm;

class LLVMCodeContainer : public virtual CodeContainer {

    protected:

        // UI structure creation
        llvm::PointerType* fDSP_ptr;
        llvm::PointerType* fStruct_UI_ptr;

        Module* fModule;
        IRBuilder<>* fBuilder;
        LLVMInstVisitor* fCodeProducer;
        string fPrefix;   // Prefix for function name
        bool fNeedDelete;

        void generateComputeBegin(const string& counter);
        void generateComputeEnd();
        void generateComputeDouble();

        void generateFillBegin();
        void generateFillEnd();

        void generateGetNumInputs();
        void generateGetNumOutputs();

        void generateClassInitBegin();
        void generateClassInitEnd();
        void generateInitFun();

        void generateInstanceInitBegin(int sample_freq_field);
        void generateInstanceInitEnd();

        void generateDestroyBegin();
        void generateDestroyEnd();

        void generateMetadata();

        void generateBuildUserInterfaceBegin();
        void generateBuildUserInterfaceEnd();

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
            return ConstantInt::get(llvm::Type::getInt1Ty(getGlobalContext()), number);
        }

        LlvmValue genInt32(int number)
        {
            return ConstantInt::get(llvm::Type::getInt32Ty(getGlobalContext()), number);
        }

        LlvmValue genInt64(int number)
        {
            return ConstantInt::get(llvm::Type::getInt64Ty(getGlobalContext()), number);
        }

        LlvmValue genFloat(const string& number)
        {
            return ConstantFP::get(getGlobalContext(), APFloat(APFloat::IEEEsingle, number));
        }

        LlvmValue genFloat(float number)
        {
            return ConstantFP::get(getGlobalContext(), APFloat(number));
        }

    public:

        LLVMCodeContainer(int numInputs, int numOutputs, const string& prefix = "")
            :CodeContainer(numInputs, numOutputs), fPrefix(prefix)
        {
            InitializeNativeTarget();
            fModule = new Module("Faust LLVM backend", getGlobalContext());
            fBuilder = new IRBuilder<>(getGlobalContext());
            fNeedDelete = true;

            // TODO
            fModule->setDataLayout("e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64");
            fModule->setTargetTriple(llvm::sys::getHostTriple());
            fNumInputs = numInputs;
            fNumOutputs = numOutputs;
        }

         LLVMCodeContainer(int numInputs, int numOutputs, Module* module, IRBuilder<>* builder, const string& prefix = "")
            :CodeContainer(numInputs, numOutputs), fPrefix(prefix)
        {
            fModule = module;
            fBuilder = builder;
            fNeedDelete = false;
        }

        virtual ~LLVMCodeContainer()
        {
            if (fNeedDelete) {
                delete fModule;
                delete fBuilder;
            }
        }

        virtual Module* produceModule(const string& filename);
        virtual void generateCompute() = 0;
        void produceInternal();

        CodeContainer* createScalarContainer(const string& name, int sub_container_type);

};

class LLVMScalarCodeContainer : public LLVMCodeContainer {

    protected:


    public:

        LLVMScalarCodeContainer(int numInputs, int numOutputs, const string& module_name = "");
        LLVMScalarCodeContainer(int numInputs, int numOutputs, Module* module, IRBuilder<>* builder, int sub_container_type, const string& prefix = "");
        virtual ~LLVMScalarCodeContainer();

        void generateCompute();

};

class LLVMVectorCodeContainer : public VectorCodeContainer, public LLVMCodeContainer {

    protected:


    public:

        LLVMVectorCodeContainer(int numInputs, int numOutputs, const string& module_name = "");
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

        LLVMOpenMPCodeContainer(int numInputs, int numOutputs, const string& module_name = "");
        virtual ~LLVMOpenMPCodeContainer();

        void generateCompute();

};

class LLVMWorkStealingCodeContainer : public WSSCodeContainer, public LLVMCodeContainer {

    protected:

        void generateComputeThreadBegin();
        void generateComputeThreadEnd();
        void generateComputeThreadExternal();

    public:

        LLVMWorkStealingCodeContainer(int numInputs, int numOutputs, const string& module_name = "");
        virtual ~LLVMWorkStealingCodeContainer();

        Module* produceModule(const string& filename);
        void generateCompute();

};

#endif
