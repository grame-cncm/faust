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

		Historique :
		-----------

***********************************************************************/

#include "code_container.hh"
#include "llvm_instructions.hh"

#include "vec_code_container.hh"
#include "omp_code_container.hh"
#include "wss_code_container.hh"

#ifdef LLVM_28
#include <llvm/System/Host.h>
#endif

#ifdef LLVM_29
#include <llvm/Support/Host.h>
#endif

using namespace std;
using namespace llvm;

class LLVMCodeContainer : public virtual CodeContainer {

    protected:

        // UI structure creation
        llvm::PointerType* fStruct_DSP_ptr;

        Module* fModule;
        IRBuilder<>* fBuilder;
        LLVMInstVisitor* fCodeProducer;
        bool fNeedDelete;

        void generateComputeBegin(const string& counter);
        void generateComputeEnd();
        void generateComputeDouble();

        void generateFillBegin(const string& counter);
        void generateFillEnd();

        void generateGetSampleRate(int field_index);

        void generateGetNumInputs(bool internal = false);
        void generateGetNumOutputs(bool internal = false);

        //void generateGetInputRate();
        //void generateGetOutputRate();

        void generateClassInitBegin();
        void generateClassInitEnd();
        void generateInitFun();

        void generateInstanceInitBegin(bool internal = false);
        void generateInstanceInitEnd();

        void generateDestroyBegin();
        void generateDestroyEnd();

        void generateMetadata(llvm::PointerType* meta_type_ptr);

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

        LLVMCodeContainer(const string& name, int numInputs, int numOutputs)
        {
            initializeCodeContainer(numInputs, numOutputs);
            fKlassName = name;

            InitializeNativeTarget();
            fModule = new Module("Faust LLVM backend", getGlobalContext());
            fBuilder = new IRBuilder<>(getGlobalContext());
            fNeedDelete = true;

            // TODO
            fModule->setDataLayout("e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64");
        #if defined(LLVM_31)
            fModule->setTargetTriple(llvm::sys::getDefaultTargetTriple());
        #else
            fModule->setTargetTriple(llvm::sys::getHostTriple());
        #endif
            fNumInputs = numInputs;
            fNumOutputs = numOutputs;
            fInputRates.resize(numInputs);
            fOutputRates.resize(numOutputs);
        }

         LLVMCodeContainer(const string& name, int numInputs, int numOutputs, Module* module, IRBuilder<>* builder)
        {
            initializeCodeContainer(numInputs, numOutputs);
            fKlassName = name;
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

        static CodeContainer* createContainer(const string& name, int numInputs, int numOutputs);

};

class LLVMScalarCodeContainer : public LLVMCodeContainer {

    protected:

    public:

        LLVMScalarCodeContainer(const string& name, int numInputs, int numOutputs);
        LLVMScalarCodeContainer(const string& name, int numInputs, int numOutputs, Module* module, IRBuilder<>* builder, int sub_container_type);
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
