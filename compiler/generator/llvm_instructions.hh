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

#ifndef _LLVM_INSTRUCTIONS_H
#define _LLVM_INSTRUCTIONS_H

/**********************************************************************

		Historique :
		-----------

***********************************************************************/

using namespace std;

#include <string>
#include <list>
#include <set>
#include <map>

#include "instructions.hh"
#include "binop.hh"

#include <llvm/DerivedTypes.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/PassManager.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Target/TargetData.h>
#include <llvm/Target/TargetSelect.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Support/IRBuilder.h>
#include <llvm-c/BitWriter.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

extern bool gVectorSwitch;
extern int gVecSize;

typedef llvm::Value* LlvmValue;

// Helper class

struct LLVMTypeHelper {

    std::map<Typed::VarType, const llvm::Type*> fTypeMap;

    LLVMTypeHelper()
    {
        // LLVM type coding
        fTypeMap[Typed::kFloat] = llvm::Type::getFloatTy(getGlobalContext());
        fTypeMap[Typed::kFloat_ptr] = PointerType::get(fTypeMap[Typed::kFloat], 0);
        fTypeMap[Typed::kFloat_vec] = VectorType::get(fTypeMap[Typed::kFloat], gVecSize);
        fTypeMap[Typed::kFloat_vec_ptr] = PointerType::get(fTypeMap[Typed::kFloat_vec], 0);

        fTypeMap[Typed::kInt] = llvm::Type::getInt32Ty(getGlobalContext());
        fTypeMap[Typed::kInt_ptr] = PointerType::get(fTypeMap[Typed::kInt], 0);
        fTypeMap[Typed::kInt_vec] = VectorType::get(fTypeMap[Typed::kInt], gVecSize);
        fTypeMap[Typed::kInt_vec_ptr] = PointerType::get(fTypeMap[Typed::kInt_vec], 0);

        fTypeMap[Typed::kDouble] = llvm::Type::getDoubleTy(getGlobalContext());
        fTypeMap[Typed::kDouble_ptr] = PointerType::get(fTypeMap[Typed::kDouble], 0);
        fTypeMap[Typed::kDouble_vec] = VectorType::get(fTypeMap[Typed::kDouble], gVecSize);
        fTypeMap[Typed::kDouble_vec_ptr] = PointerType::get(fTypeMap[Typed::kDouble_vec], 0);

        fTypeMap[Typed::kBool] = llvm::Type::getInt1Ty(getGlobalContext());
        fTypeMap[Typed::kBool_ptr] = PointerType::get(fTypeMap[Typed::kBool], 0);
        fTypeMap[Typed::kBool_vec] = VectorType::get(fTypeMap[Typed::kBool], gVecSize);
        fTypeMap[Typed::kBool_vec_ptr] = PointerType::get(fTypeMap[Typed::kBool_vec], 0);

        // Takes the type of internal real
        fTypeMap[Typed::kFloatMacro] = fTypeMap[itfloat()];
        fTypeMap[Typed::kFloatMacro_ptr] = PointerType::get(fTypeMap[Typed::kFloatMacro], 0);

        fTypeMap[Typed::kVoid] = llvm::Type::getVoidTy(getGlobalContext());
        // void* must be defined as i8* type
        fTypeMap[Typed::kVoid_ptr] = PointerType::get(llvm::Type::getInt8Ty(getGlobalContext()), 0);
        fTypeMap[Typed::kVoid_ptr_ptr] = PointerType::get(fTypeMap[Typed::kVoid_ptr], 0);
    }

    virtual ~LLVMTypeHelper()
    {}

    virtual LlvmValue genInt1(int number, int size = 1)
    {
        if (size > 1) {
            return ConstantInt::get(VectorType::get(llvm::Type::getInt1Ty(getGlobalContext()), size), number);
        } else {
            return ConstantInt::get(llvm::Type::getInt1Ty(getGlobalContext()), number);
        }
    }

    virtual LlvmValue genInt32(int number, int size = 1)
    {
        if (size > 1) {
            return ConstantInt::get(VectorType::get(llvm::Type::getInt32Ty(getGlobalContext()), size), number);
        } else {
            return ConstantInt::get(llvm::Type::getInt32Ty(getGlobalContext()), number);
        }
    }

    virtual LlvmValue genInt64(int number, int size = 1)
    {
        if (size > 1) {
            return ConstantInt::get(VectorType::get(llvm::Type::getInt64Ty(getGlobalContext()), size), number);
        } else {
            return ConstantInt::get(llvm::Type::getInt64Ty(getGlobalContext()), number);
        }
    }

    virtual LlvmValue genFloat(float number, int size = 1)
    {
        if (size > 1) {
            return ConstantFP::get(VectorType::get(llvm::Type::getFloatTy(getGlobalContext()), size), number);
        } else {
            return ConstantFP::get(getGlobalContext(), APFloat(number));
        }
    }

    virtual LlvmValue genDouble(double number, int size = 1)
    {
        if (size > 1) {
            return ConstantFP::get(VectorType::get(llvm::Type::getFloatTy(getGlobalContext()), size), number);
        } else {
            return ConstantFP::get(getGlobalContext(), APFloat(number));
        }
    }

    virtual const llvm::Type* getFloatTy(int size)
    {
        if (size > 1) {
            return VectorType::get(llvm::Type::getFloatTy(getGlobalContext()), size);
        } else {
            return llvm::Type::getFloatTy(getGlobalContext());
        }
    }

    virtual const llvm::Type* getInt32Ty(int size)
    {
        if (size > 1) {
            return VectorType::get(llvm::Type::getInt32Ty(getGlobalContext()), size);
        } else {
            return llvm::Type::getInt32Ty(getGlobalContext());
        }
    }

    virtual const llvm::Type* getInt1Ty(int size)
    {
        if (size > 1) {
            return VectorType::get(llvm::Type::getInt1Ty(getGlobalContext()), size);
        } else {
            return llvm::Type::getInt1Ty(getGlobalContext());
        }
    }

    virtual const llvm::Type* getDoubleTy(int size)
    {
        if (size > 1) {
            return VectorType::get(llvm::Type::getDoubleTy(getGlobalContext()), size);
        } else {
            return llvm::Type::getDoubleTy(getGlobalContext());
        }
    }

};

class LLVMTypeInstVisitor : public DispatchVisitor, public LLVMTypeHelper {

    protected:

        Module* fModule;
        IRBuilder<>* fBuilder;

        // DSP structure creation
        std::map<string, int> fDSPFieldsNames;
        vector<const llvm::Type*> fDSPFields;
        int fDSPFieldsCounter;
        string fPrefix;

        // UI structure creation
        llvm::PointerType* fStruct_UI_ptr;
        LlvmValue fUIInterface_ptr;

        virtual void generateFreeDsp(llvm::PointerType* dsp_type_ptr, bool internal)
        {
            // free
            PointerType* free_ptr = PointerType::get(fBuilder->getInt8Ty(), 0);
            vector<const llvm::Type*> free_args;
            free_args.push_back(free_ptr);
            FunctionType* free_type = FunctionType::get(fBuilder->getVoidTy(), free_args, false);

            Function* func_free = NULL;
            if (!fModule->getFunction("free")) {
                func_free = Function::Create(free_type, GlobalValue::ExternalLinkage, "free", fModule);
                func_free->setCallingConv(CallingConv::C);
            } else {
                func_free = fModule->getFunction("free");
            }

            // Generates llvm_free_dsp
            vector<const llvm::Type*> llvm_free_dsp_args;
            llvm_free_dsp_args.push_back(dsp_type_ptr);
            FunctionType* llvm_free_dsp_type = FunctionType::get(fBuilder->getVoidTy(), llvm_free_dsp_args, false);
            Function* func_llvm_free_dsp = Function::Create(llvm_free_dsp_type, (internal)? Function::InternalLinkage : Function::ExternalLinkage, "delete" + fPrefix, fModule);
            func_llvm_free_dsp->setCallingConv(CallingConv::C);

            // llvm_free_dsp block
            Function::arg_iterator args = func_llvm_free_dsp->arg_begin();
            Value* ptr_dsp = args++;
            ptr_dsp->setName("dsp");

            BasicBlock* entry_func_llvm_free_dsp = BasicBlock::Create(getGlobalContext(), "entry", func_llvm_free_dsp);
            Instruction* inst2 = new BitCastInst(ptr_dsp, PointerType::get(fBuilder->getInt8Ty(), 0), "", entry_func_llvm_free_dsp);

            CallInst* call_inst0 = CallInst::Create(func_free, inst2, "", entry_func_llvm_free_dsp);
            call_inst0->setCallingConv(CallingConv::C);

            ReturnInst::Create(getGlobalContext(), entry_func_llvm_free_dsp);
            verifyFunction(*func_llvm_free_dsp);
            fBuilder->ClearInsertionPoint();
        }

        void generateMemory(llvm::PointerType* dsp_type_ptr, bool internal)
        {
            // malloc
            PointerType* malloc_ptr = PointerType::get(fBuilder->getInt8Ty(), 0);
            vector<const llvm::Type*> malloc_args;
            malloc_args.push_back(IntegerType::get(getGlobalContext(), 64));
            FunctionType* malloc_type = FunctionType::get(malloc_ptr, malloc_args, false);

            Function* func_malloc = NULL;
            if (!fModule->getFunction("malloc")) {
                func_malloc = Function::Create(malloc_type, GlobalValue::ExternalLinkage, "malloc", fModule);
                func_malloc->setCallingConv(CallingConv::C);
            } else {
                func_malloc = fModule->getFunction("malloc");
            }

            // llvm_create_dsp
            vector<const llvm::Type*> llvm_create_dsp_args;
            FunctionType* llvm_create_dsp_type = FunctionType::get(dsp_type_ptr, llvm_create_dsp_args, false);
            Function* func_llvm_create_dsp = Function::Create(llvm_create_dsp_type, (internal) ? GlobalValue::InternalLinkage : GlobalValue::ExternalLinkage, "new" + fPrefix, fModule);
            func_llvm_create_dsp->setCallingConv(CallingConv::C);

            // llvm_create_dsp block
            BasicBlock* entry_func_llvm_create_dsp = BasicBlock::Create(getGlobalContext(), "entry", func_llvm_create_dsp);

            // Dynamically computed object size (see http://nondot.org/sabre/LLVMNotes/SizeOf-OffsetOf-VariableSizedStructs.txt)
            Value* ptr_size = GetElementPtrInst::Create(ConstantPointerNull::get(dsp_type_ptr), genInt64(1), "ptr_size", entry_func_llvm_create_dsp);
            CastInst* size = new PtrToIntInst(ptr_size, fBuilder->getInt64Ty(), "size", entry_func_llvm_create_dsp);
            CallInst* call_inst1 = CallInst::Create(func_malloc, size, "", entry_func_llvm_create_dsp);
            call_inst1->setCallingConv(CallingConv::C);
            CastInst* call_inst2 = new BitCastInst(call_inst1, dsp_type_ptr, "", entry_func_llvm_create_dsp);
            ReturnInst::Create(getGlobalContext(), call_inst2, entry_func_llvm_create_dsp);
            verifyFunction(*func_llvm_create_dsp);
            fBuilder->ClearInsertionPoint();
        }

        void generateUIGlue()
        {
            // Type Definitions
            std::vector<const llvm::Type*>StructTy_struct_UIGlue_fields;
            PointerType* PointerTy_0 = PointerType::get(IntegerType::get(fModule->getContext(), 8), 0);

            StructTy_struct_UIGlue_fields.push_back(PointerTy_0);
            std::vector<const llvm::Type*>FuncTy_2_args;
            FuncTy_2_args.push_back(PointerTy_0);
            FuncTy_2_args.push_back(PointerTy_0);
            FunctionType* FuncTy_2 = FunctionType::get(
            /*Result=*/llvm::Type::getVoidTy(fModule->getContext()),
            /*Params=*/FuncTy_2_args,
            /*isVarArg=*/false);

            PointerType* PointerTy_1 = PointerType::get(FuncTy_2, 0);

            StructTy_struct_UIGlue_fields.push_back(PointerTy_1);
            StructTy_struct_UIGlue_fields.push_back(PointerTy_1);
            StructTy_struct_UIGlue_fields.push_back(PointerTy_1);
            StructTy_struct_UIGlue_fields.push_back(PointerTy_1);
            std::vector<const llvm::Type*>FuncTy_4_args;
            FuncTy_4_args.push_back(PointerTy_0);
            FunctionType* FuncTy_4 = FunctionType::get(
            /*Result=*/llvm::Type::getVoidTy(fModule->getContext()),
            /*Params=*/FuncTy_4_args,
            /*isVarArg=*/false);

            PointerType* PointerTy_3 = PointerType::get(FuncTy_4, 0);

            StructTy_struct_UIGlue_fields.push_back(PointerTy_3);
            std::vector<const llvm::Type*>FuncTy_6_args;
            FuncTy_6_args.push_back(PointerTy_0);
            FuncTy_6_args.push_back(PointerTy_0);
            const llvm::Type* PointerTy_7 = fTypeMap[Typed::kFloatMacro_ptr];  // For LLVM internal float is same as external

            FuncTy_6_args.push_back(PointerTy_7);
            FunctionType* FuncTy_6 = FunctionType::get(
            /*Result=*/llvm::Type::getVoidTy(fModule->getContext()),
            /*Params=*/FuncTy_6_args,
            /*isVarArg=*/false);

            PointerType* PointerTy_5 = PointerType::get(FuncTy_6, 0);

            StructTy_struct_UIGlue_fields.push_back(PointerTy_5);
            StructTy_struct_UIGlue_fields.push_back(PointerTy_5);
            StructTy_struct_UIGlue_fields.push_back(PointerTy_5);
            std::vector<const llvm::Type*>FuncTy_9_args;
            FuncTy_9_args.push_back(PointerTy_0);
            FuncTy_9_args.push_back(PointerTy_0);
            FuncTy_9_args.push_back(PointerTy_7);
            FuncTy_9_args.push_back(fTypeMap[Typed::kFloatMacro]);  // For LLVM internal float is same as external
            FuncTy_9_args.push_back(fTypeMap[Typed::kFloatMacro]);
            FuncTy_9_args.push_back(fTypeMap[Typed::kFloatMacro]);
            FuncTy_9_args.push_back(fTypeMap[Typed::kFloatMacro]);
            FunctionType* FuncTy_9 = FunctionType::get(
            /*Result=*/llvm::Type::getVoidTy(fModule->getContext()),
            /*Params=*/FuncTy_9_args,
            /*isVarArg=*/false);

            PointerType* PointerTy_8 = PointerType::get(FuncTy_9, 0);

            StructTy_struct_UIGlue_fields.push_back(PointerTy_8);
            StructTy_struct_UIGlue_fields.push_back(PointerTy_8);
            StructTy_struct_UIGlue_fields.push_back(PointerTy_8);
            std::vector<const llvm::Type*>FuncTy_11_args;
            FuncTy_11_args.push_back(PointerTy_0);
            FuncTy_11_args.push_back(PointerTy_0);
            FuncTy_11_args.push_back(PointerTy_7);
            FuncTy_11_args.push_back(IntegerType::get(fModule->getContext(), 32));
            FunctionType* FuncTy_11 = FunctionType::get(
            /*Result=*/llvm::Type::getVoidTy(fModule->getContext()),
            /*Params=*/FuncTy_11_args,
            /*isVarArg=*/false);

            PointerType* PointerTy_10 = PointerType::get(FuncTy_11, 0);

            StructTy_struct_UIGlue_fields.push_back(PointerTy_10);
            std::vector<const llvm::Type*>FuncTy_13_args;
            FuncTy_13_args.push_back(PointerTy_0);
            FuncTy_13_args.push_back(PointerTy_0);
            FuncTy_13_args.push_back(PointerTy_7);
            PointerType* PointerTy_14 = PointerType::get(PointerTy_0, 0);

            FuncTy_13_args.push_back(PointerTy_14);
            FuncTy_13_args.push_back(fTypeMap[Typed::kFloatMacro]);  // For LLVM internal float is same as external
            FuncTy_13_args.push_back(fTypeMap[Typed::kFloatMacro]);
            FunctionType* FuncTy_13 = FunctionType::get(
            /*Result=*/llvm::Type::getVoidTy(fModule->getContext()),
            /*Params=*/FuncTy_13_args,
            /*isVarArg=*/false);

            PointerType* PointerTy_12 = PointerType::get(FuncTy_13, 0);

            StructTy_struct_UIGlue_fields.push_back(PointerTy_12);
            std::vector<const llvm::Type*>FuncTy_16_args;
            FuncTy_16_args.push_back(PointerTy_0);
            FuncTy_16_args.push_back(PointerTy_0);
            FuncTy_16_args.push_back(PointerTy_7);
            FuncTy_16_args.push_back(fTypeMap[Typed::kFloatMacro]);  // For LLVM internal float is same as external
            FuncTy_16_args.push_back(fTypeMap[Typed::kFloatMacro]);
            FunctionType* FuncTy_16 = FunctionType::get(
            /*Result=*/llvm::Type::getVoidTy(fModule->getContext()),
            /*Params=*/FuncTy_16_args,
            /*isVarArg=*/false);

            PointerType* PointerTy_15 = PointerType::get(FuncTy_16, 0);

            StructTy_struct_UIGlue_fields.push_back(PointerTy_15);
            StructTy_struct_UIGlue_fields.push_back(PointerTy_15);
            std::vector<const llvm::Type*>FuncTy_18_args;
            FuncTy_18_args.push_back(PointerTy_0);
            FuncTy_18_args.push_back(PointerTy_7);
            FuncTy_18_args.push_back(PointerTy_0);
            FuncTy_18_args.push_back(PointerTy_0);
            FunctionType* FuncTy_18 = FunctionType::get(
            /*Result=*/llvm::Type::getVoidTy(fModule->getContext()),
            /*Params=*/FuncTy_18_args,
            /*isVarArg=*/false);

            PointerType* PointerTy_17 = PointerType::get(FuncTy_18, 0);

            StructTy_struct_UIGlue_fields.push_back(PointerTy_17);
            llvm::StructType* fStruct_UI = StructType::get(fModule->getContext(), StructTy_struct_UIGlue_fields, /*isPacked=*/false);
            fStruct_UI_ptr = PointerType::get(fStruct_UI, 0);
            fModule->addTypeName("struct.UIGlue", fStruct_UI);
        }

        void generateDataStruct(llvm::PointerType* dsp_type_ptr, bool generate_ui)
        {
            // Struct Meta
            vector<const llvm::Type*>StructTy_struct_Meta_fields;
            StructTy_struct_Meta_fields.push_back(IntegerType::get(fModule->getContext(), 8));
            StructType* StructTy_struct_Meta = StructType::get(fModule->getContext(), StructTy_struct_Meta_fields, /*isPacked=*/true);
            fModule->addTypeName("struct.Meta", StructTy_struct_Meta);

            // Struct UI
            generateUIGlue();

            if (generate_ui) {
                // Creates llvm_buildUserInterface function
                vector<const llvm::Type*> llvm_buildUserInterface_args;
                llvm_buildUserInterface_args.push_back(dsp_type_ptr);
                llvm_buildUserInterface_args.push_back(fStruct_UI_ptr);
                FunctionType* llvm_buildUserInterface_type = FunctionType::get(fBuilder->getVoidTy(), llvm_buildUserInterface_args, false);

                Function* llvm_buildUserInterface = Function::Create(llvm_buildUserInterface_type, GlobalValue::ExternalLinkage, "buildUserInterface" + fPrefix, fModule);
                llvm_buildUserInterface->setCallingConv(CallingConv::C);
                llvm_buildUserInterface->setAlignment(2);

                // Name arguments
                Function::arg_iterator func_llvm_buildUserInterface_args_it = llvm_buildUserInterface->arg_begin();
                Value* dsp = func_llvm_buildUserInterface_args_it++;
                dsp->setName("dsp");
                Value* interface = func_llvm_buildUserInterface_args_it++;
                interface->setName("interface");

                // Create init block
                BasicBlock* init_block = BasicBlock::Create(getGlobalContext(), "init", llvm_buildUserInterface);
                fBuilder->SetInsertPoint(init_block);

                // Genererates access to "interface" pointer just once
                Value* idx[2];
                idx[0] = genInt64(0);
                idx[1] = genInt32(0);
                Value* ui_ptr = fBuilder->CreateGEP(interface, idx, idx+2);
                fUIInterface_ptr = fBuilder->CreateLoad(ui_ptr);

                //fStruct_UI_ptr->dump();
                //llvm_buildUserInterface->dump();
            }
        }

    public:

        LLVMTypeInstVisitor(Module* module, const string& prefix = "")
                            :fModule(module),
                            fDSPFieldsCounter(0),
                            fPrefix(prefix)
        {
            fBuilder = new IRBuilder<>(getGlobalContext());
        }

        virtual ~LLVMTypeInstVisitor()
        {
            delete fBuilder;
        }

        virtual void visit(DeclareVarInst* inst)
        {
            // Not supposed to declare var with value here
            assert(inst->fValue == NULL);

            BasicTyped* basic_typed = dynamic_cast<BasicTyped*>(inst->fTyped);
            ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fTyped);
            VectorTyped* vector_typed = dynamic_cast<VectorTyped*>(inst->fTyped);

            if (basic_typed) {
                fDSPFields.push_back(fTypeMap[basic_typed->fType]);
            } else if (array_typed) {
                if (array_typed->fSize == 0) {
                    // Array of zero size are treated as pointer in the corresponding type
                    fDSPFields.push_back(fTypeMap[array_typed->getType()]);
                } else {
                    fDSPFields.push_back(ArrayType::get(fTypeMap[Typed::getTypeFromPtr(array_typed->getType())], array_typed->fSize));
                }
            } else if (vector_typed) {
                fDSPFields.push_back(VectorType::get(fTypeMap[vector_typed->fType->fType], vector_typed->fSize));
            }

            fDSPFieldsNames[inst->fAddress->getName()] = fDSPFieldsCounter++;
        }

        virtual void visit(DeclareFunInst* inst)
        {
            Function* function = fModule->getFunction(inst->fName);

            if (!function) {  // Define it

                // Return type
                const llvm::Type* return_type = fTypeMap[inst->fType->fResult->getType()];

                // Prepare vector of LLVM types for args
                vector<const llvm::Type*> fun_args_type;
                list<NamedTyped*>::const_iterator it;
                for (it = inst->fType->fArgsTypes.begin(); it != inst->fType->fArgsTypes.end(); it++) {
                    fun_args_type.push_back(fTypeMap[(*it)->getType()]);
                }

                // Creates function
                FunctionType* fun_type = FunctionType::get(return_type, fun_args_type, false);
                function = Function::Create(fun_type, GlobalValue::ExternalLinkage, inst->fName, fModule);
                function->setCallingConv(CallingConv::C);

                // Set name for function arguments
                Function::arg_iterator args = function->arg_begin();
                for (it = inst->fType->fArgsTypes.begin(); it != inst->fType->fArgsTypes.end(); it++) {
                    Value* llvm_arg = args++;
                    llvm_arg->setName((*it)->fName);
                }
            }

            // If there is a body, compile it
            if (inst->fCode->fCode.size() > 0) {

                // Prepare a block to insert into
                BasicBlock* code_block = BasicBlock::Create(getGlobalContext(), "code_block", function);
                fBuilder->SetInsertPoint(code_block);

                // Compile code in this block
                inst->fCode->accept(this);
                verifyFunction(*function);
                fBuilder->ClearInsertionPoint();
            }
        }

        llvm::PointerType* getDSPType(bool internal, bool generate_ui = true)
        {
            llvm::StructType* dsp_type;
            llvm::PointerType* dsp_type_ptr;

            dsp_type = StructType::get(fModule->getContext(), fDSPFields, false);
            dsp_type_ptr = PointerType::get(dsp_type, 0);
            fModule->addTypeName("struct.dsp" + fPrefix, dsp_type);
            const llvm::Type* type = fModule->getTypeByName("struct.dsp" + fPrefix);
            assert(type);
            // type->dump();

            // Create llvm_free_dsp function
            generateFreeDsp(dsp_type_ptr, internal);

            // Creates DSP free/delete functions
            generateMemory(dsp_type_ptr, internal);

            // Creates struct.Meta and struct.UI and prepare llvm_buildUserInterface
            generateDataStruct(dsp_type_ptr, generate_ui);

            return dsp_type_ptr;
        }

        std::map<string, int> getFieldNames()
        {
            return fDSPFieldsNames;
        }

        llvm::PointerType* getUIType()
        {
            return fStruct_UI_ptr;
        }

        LlvmValue getUIPtr()
        {
            return fUIInterface_ptr;
        }

};

// Special version for DSP code (add call to "destroy" function)

class LLVMTypeInstVisitor1 : public LLVMTypeInstVisitor {

    protected:

        void generateFreeDsp(llvm::PointerType* dsp_type_ptr, bool internal)
        {
            // free
            PointerType* free_ptr = PointerType::get(fBuilder->getInt8Ty(), 0);
            vector<const llvm::Type*> free_args;
            free_args.push_back(free_ptr);
            FunctionType* free_type = FunctionType::get(fBuilder->getVoidTy(), free_args, false);

            Function* func_free = NULL;
            if (!fModule->getFunction("free")) {
                func_free = Function::Create(free_type, GlobalValue::ExternalLinkage, "free", fModule);
                func_free->setCallingConv(CallingConv::C);
                func_free->setAlignment(2);
            } else {
                func_free = fModule->getFunction("free");
            }

            vector<const llvm::Type*> destroy_args;
            destroy_args.push_back(dsp_type_ptr);
            FunctionType* destroy_type = FunctionType::get(fBuilder->getVoidTy(), destroy_args, false);

            Function* func_destroy = NULL;
            if (!fModule->getFunction("destroy" + fPrefix)) {
                func_destroy = Function::Create(destroy_type, Function::ExternalLinkage, "destroy" + fPrefix, fModule);
                func_destroy->setCallingConv(CallingConv::C);
                func_destroy->setAlignment(2);
                Function::arg_iterator llvm_destroy_args_it = func_destroy->arg_begin();
                Value* dsp = llvm_destroy_args_it++;
                dsp->setName("dsp");
            } else {
                func_destroy = fModule->getFunction("destroy" + fPrefix);
            }

            // Generates llvm_free_dsp
            vector<const llvm::Type*> llvm_free_dsp_args;
            llvm_free_dsp_args.push_back(dsp_type_ptr);
            FunctionType* llvm_free_dsp_type = FunctionType::get(fBuilder->getVoidTy(), llvm_free_dsp_args, false);
            Function* func_llvm_free_dsp = Function::Create(llvm_free_dsp_type, (internal)? Function::InternalLinkage : Function::ExternalLinkage, "delete" + fPrefix, fModule);
            func_llvm_free_dsp->setCallingConv(CallingConv::C);

            // llvm_free_dsp block
            Function::arg_iterator args = func_llvm_free_dsp->arg_begin();
            Value* ptr_dsp = args++;
            ptr_dsp->setName("dsp");

            BasicBlock* entry_func_llvm_free_dsp = BasicBlock::Create(getGlobalContext(), "entry", func_llvm_free_dsp);
            Instruction* inst2 = new BitCastInst(ptr_dsp, PointerType::get(fBuilder->getInt8Ty(), 0), "", entry_func_llvm_free_dsp);

            CallInst* call_inst1 = CallInst::Create(func_destroy, ptr_dsp, "", entry_func_llvm_free_dsp);
            call_inst1->setCallingConv(CallingConv::C);

            CallInst* call_inst0 = CallInst::Create(func_free, inst2, "", entry_func_llvm_free_dsp);
            call_inst0->setCallingConv(CallingConv::C);

            ReturnInst::Create(getGlobalContext(), entry_func_llvm_free_dsp);
            verifyFunction(*func_llvm_free_dsp);
            fBuilder->ClearInsertionPoint();
        }

    public:

        LLVMTypeInstVisitor1(Module* module, const string& prefix = "")
            :LLVMTypeInstVisitor(module, prefix)
        {}
};

// LLVM loop code generator

class LLVMInstVisitor : public InstVisitor, public LLVMTypeHelper {

    protected:

        Module* fModule;
        IRBuilder<>* fBuilder;

        map<string, LlvmValue> fUICallTable;

        // UI structure creation
        llvm::PointerType* fStruct_UI_ptr;
        LlvmValue fUIInterface_ptr;                 // Pointer on the UI

        llvm::PointerType* fDSP_ptr;

        std::map<string, int> fDSPFieldsNames;      // Computed by LLVMTypeInstVisitor, used to access struct fields
        std::map<string, LlvmValue> fDSPStackVars;  // Variables on the stack

        LlvmValue fCurValue;                        // Current result of the compilation
        string fPrefix;                             // Prefix for function name

        map <string, GlobalVariable*> fGlobalStringTable;

    public:

        LLVMInstVisitor(Module* module, IRBuilder<>* builder,
                        const std::map<string, int>& field_names,
                        llvm::PointerType* ui_type,
                        LlvmValue ui_ptr,
                        llvm::PointerType* dsp_ptr,
                        const string& prefix = "")
                        :fModule(module),
                        fBuilder(builder),
                        fStruct_UI_ptr(ui_type),
                        fUIInterface_ptr(ui_ptr),
                        fDSP_ptr(dsp_ptr),
                        fDSPFieldsNames(field_names),
                        fCurValue(NULL),
                        fPrefix(prefix)
        {
            // UI call table : indexes of method calls
            fUICallTable["openFrameBox"] = genInt32(1);
            fUICallTable["openTabBox"] = genInt32(2);
            fUICallTable["openHorizontalBox"] = genInt32(3);
            fUICallTable["openVerticalBox"] = genInt32(4);
            fUICallTable["closeBox"] = genInt32(5);

            fUICallTable["addButton"] = genInt32(6);
            fUICallTable["addToggleButton"] = genInt32(7);
            fUICallTable["addCheckButton"] = genInt32(8);
            fUICallTable["addVerticalSlider"] = genInt32(9);
            fUICallTable["addHorizontalSlider"] = genInt32(10);
            fUICallTable["addNumEntry"] = genInt32(11);

            fUICallTable["addNumDisplay"] = genInt32(12);
            fUICallTable["addTextDisplay"] = genInt32(13);
            fUICallTable["addHorizontalBargraph"] = genInt32(14);
            fUICallTable["addVerticalBargraph"] = genInt32(15);

            fUICallTable["declare"] = genInt32(16);

            fTypeMap[Typed::kObj_ptr] = fDSP_ptr;
        }

        LLVMInstVisitor(const string& prefix = "")
                        :fBuilder(NULL),
                        fCurValue(NULL),
                        fPrefix(prefix)
        {}

        virtual ~LLVMInstVisitor()
        {}

        void setBuilder(IRBuilder<>* builder) {fBuilder = builder; }
        IRBuilder<>* getBuilder() { return fBuilder; }

         // User interface

        string replaceSpacesWithUnderscore(const string& str)
        {
            string res = str;
            for (size_t i = 0; i < res.size(); i++) {
                if (res[i] == ' ') res[i] = '_';
            }
            return res;
        }

        void printVarTable()
        {
            std::map<string, LlvmValue>::const_iterator it;

             for (it = fDSPStackVars.begin(); it != fDSPStackVars.end(); it++) {
                printf("stack var = %s \n", (*it).first.c_str());
             }
        }

        GlobalVariable* addStringConstant(const string& str)
        {
            if (fGlobalStringTable.find(str) == fGlobalStringTable.end()) {
                ArrayType* array_type = ArrayType::get(fBuilder->getInt8Ty(), str.size() + 1);
                GlobalVariable* gvar_array_string0 = new GlobalVariable(*fModule, array_type, true, GlobalValue::PrivateLinkage, 0, str);
                gvar_array_string0->setInitializer(ConstantArray::get(getGlobalContext(), str, true));
                fGlobalStringTable[str] = gvar_array_string0;
                return gvar_array_string0;
            } else {
                return fGlobalStringTable[str];
            }
        }

        Value* LoadArrayAsPointer(Value* variable, bool isvolatile = false)
        {
            Value* load_ptr;
            LoadInst* tmp_load = new LoadInst(variable);
            if (isa<ArrayType>(tmp_load->getType())) {
                Value* idx[2];
                idx[0] = genInt64(0);
                idx[1] = genInt64(0);
                load_ptr = fBuilder->CreateGEP(variable, idx, idx+2);
            } else {
                load_ptr = fBuilder->CreateLoad(variable, isvolatile);
            }
            delete tmp_load;
            return load_ptr;
        }

        // Visit methods for all instructions
        virtual void visit(AddMetaDeclareInst* inst)
        {
            Function* llvm_buildUserInterface = fModule->getFunction("buildUserInterface" + fPrefix);
            Function::arg_iterator func_llvm_buildUserInterface_args_it = llvm_buildUserInterface->arg_begin();
            Value* dsp = func_llvm_buildUserInterface_args_it++;
            Value* ui = func_llvm_buildUserInterface_args_it++;

            Value* idx[2];
            idx[0] = genInt64(0);
            idx[1] = fUICallTable["declare"];
            Value* mth_ptr = fBuilder->CreateGEP(ui, idx, idx+2);
            LoadInst* mth = fBuilder->CreateLoad(mth_ptr);

            // Get LLVM constant string
            GlobalVariable* llvm_key = addStringConstant(inst->fKey);
            Value* const_string1 = fBuilder->CreateConstGEP2_32(llvm_key, 0, 0);
            GlobalVariable* llvm_value = addStringConstant(inst->fValue);
            Value* const_string2 = fBuilder->CreateConstGEP2_32(llvm_value, 0, 0);

            // Generates access to zone
            Value* zone_ptr;
            if (inst->fZone == "0") {
                zone_ptr = Constant::getNullValue((itfloat() == Typed::kFloat) ? fTypeMap[Typed::kFloat_ptr] : fTypeMap[Typed::kDouble_ptr]);
            } else {
                int field_index = fDSPFieldsNames[inst->fZone];
                zone_ptr = fBuilder->CreateStructGEP(dsp, field_index);
            }

            Value* idx2[4];
            idx2[0] = fUIInterface_ptr;
            idx2[1] = zone_ptr;
            idx2[2] = const_string1;
            idx2[3] = const_string2;

            CallInst* call_inst = fBuilder->CreateCall(mth, idx2, idx2+4);
            call_inst->setCallingConv(CallingConv::C);
        }

        virtual void visit(OpenboxInst* inst)
        {
            Function* llvm_buildUserInterface = fModule->getFunction("buildUserInterface" + fPrefix);
            Function::arg_iterator func_llvm_buildUserInterface_args_it = llvm_buildUserInterface->arg_begin();
            func_llvm_buildUserInterface_args_it++;
            Value* ui = func_llvm_buildUserInterface_args_it++;

            // Get LLVM constant string
            string name = replaceSpacesWithUnderscore(inst->fName);
            GlobalVariable* llvm_name = addStringConstant(inst->fName);
            Value* const_string = fBuilder->CreateConstGEP2_32(llvm_name, 0, 0);

            LlvmValue mth_index;
            switch (inst->fOrient) {
                case 0: mth_index = fUICallTable["openVerticalBox"]; break;
                case 1: mth_index = fUICallTable["openHorizontalBox"];  break;
                case 2: mth_index = fUICallTable["openTabBox"]; break;
                default:
                    fprintf(stderr, "error in user interface generation %d\n", inst->fOrient);
                    exit(1);
            }

            Value* idx[2];
            idx[0] = genInt64(0);
            idx[1] = mth_index;
            Value* mth_ptr = fBuilder->CreateGEP(ui, idx, idx+2);
            LoadInst* mth = fBuilder->CreateLoad(mth_ptr);

            CallInst* call_inst = fBuilder->CreateCall2(mth, fUIInterface_ptr, const_string);
            call_inst->setCallingConv(CallingConv::C);
        }

        virtual void visit(CloseboxInst* inst)
        {
            Function* llvm_buildUserInterface = fModule->getFunction("buildUserInterface" + fPrefix);
            Function::arg_iterator func_llvm_buildUserInterface_args_it = llvm_buildUserInterface->arg_begin();
            func_llvm_buildUserInterface_args_it++;
            Value* ui = func_llvm_buildUserInterface_args_it++;

            Value* idx[2];
            idx[0] = genInt64(0);
            idx[1] = fUICallTable["closeBox"];
            Value* mth_ptr = fBuilder->CreateGEP(ui, idx, idx+2);
            LoadInst* mth = fBuilder->CreateLoad(mth_ptr);

            CallInst* call_inst = fBuilder->CreateCall(mth, fUIInterface_ptr);
            call_inst->setCallingConv(CallingConv::C);
        }

        void addGenericButton(const string& label, const string& zone, const string& button_type)
        {
            Function* llvm_buildUserInterface = fModule->getFunction("buildUserInterface" + fPrefix);
            Function::arg_iterator func_llvm_buildUserInterface_args_it = llvm_buildUserInterface->arg_begin();
            Value* dsp = func_llvm_buildUserInterface_args_it++;
            Value* ui = func_llvm_buildUserInterface_args_it++;

            // Get LLVM constant string
            string name = replaceSpacesWithUnderscore(label);
            GlobalVariable* llvm_label = addStringConstant(label);
            Value* const_string = fBuilder->CreateConstGEP2_32(llvm_label, 0, 0);

            Value* idx[2];
            idx[0] = genInt64(0);
            idx[1] = fUICallTable[button_type];
            Value* mth_ptr = fBuilder->CreateGEP(ui, idx, idx+2);
            LoadInst* mth = fBuilder->CreateLoad(mth_ptr);

            // Generates access to zone
            int field_index = fDSPFieldsNames[zone];
            Value* zone_ptr = fBuilder->CreateStructGEP(dsp, field_index);

            CallInst* call_inst = fBuilder->CreateCall3(mth, fUIInterface_ptr, const_string, zone_ptr);
            call_inst->setCallingConv(CallingConv::C);
        }

        virtual void visit(AddButtonInst* inst)
        {
            if (inst->fType == AddButtonInst::kDefaultButton) {
                addGenericButton(inst->fLabel, inst->fZone, "addButton");
            } else {
                addGenericButton(inst->fLabel, inst->fZone, "addCheckButton");
            }
        }

        void addGenericSlider(const string& label,
                            const string& zone,
                            double init,
                            double min,
                            double max,
                            double step,
                            const string& slider_type)
        {
            Function* llvm_buildUserInterface = fModule->getFunction("buildUserInterface" + fPrefix);
            Function::arg_iterator func_llvm_buildUserInterface_args_it = llvm_buildUserInterface->arg_begin();
            Value* dsp = func_llvm_buildUserInterface_args_it++;
            Value* ui = func_llvm_buildUserInterface_args_it++;

            // Get LLVM constant string
            string name = replaceSpacesWithUnderscore(label);
            GlobalVariable* llvm_label = addStringConstant(label);
            Value* const_string = fBuilder->CreateConstGEP2_32(llvm_label, 0, 0);

            Value* idx[2];
            idx[0] = genInt64(0);
            idx[1] = fUICallTable[slider_type];
            Value* mth_ptr = fBuilder->CreateGEP(ui, idx, idx+2);
            LoadInst* mth = fBuilder->CreateLoad(mth_ptr);

            // Generates access to zone
            int field_index = fDSPFieldsNames[zone];
            Value* zone_ptr = fBuilder->CreateStructGEP(dsp, field_index);

            Value* idx2[7];
            idx2[0] = fUIInterface_ptr;
            idx2[1] = const_string;
            idx2[2] = zone_ptr;
            idx2[3] = (itfloat() == Typed::kFloat) ? genFloat(init) : genDouble(init);
            idx2[4] = (itfloat() == Typed::kFloat) ? genFloat(min) : genDouble(min);
            idx2[5] = (itfloat() == Typed::kFloat) ? genFloat(max) : genDouble(max);
            idx2[6] = (itfloat() == Typed::kFloat) ? genFloat(step) : genDouble(step);

            CallInst* call_inst = fBuilder->CreateCall(mth, idx2, idx2+7);
            call_inst->setCallingConv(CallingConv::C);
        }

        virtual void visit(AddSliderInst* inst)
        {
            string name;
            switch (inst->fType) {
                case AddSliderInst::kHorizontal:
                    name = "addHorizontalSlider"; break;
                case AddSliderInst::kVertical:
                    name = "addVerticalSlider"; break;
                case AddSliderInst::kNumEntry:
                    name = "addNumEntry"; break;
            }
            addGenericSlider(inst->fLabel, inst->fZone, inst->fInit, inst->fMin, inst->fMax, inst->fStep, name);
        }

        void addGenericBargraph(const string& label, const string& zone, double min, double max, const string& bargraph_type)
        {
            Function* llvm_buildUserInterface = fModule->getFunction("buildUserInterface" + fPrefix);
            Function::arg_iterator func_llvm_buildUserInterface_args_it = llvm_buildUserInterface->arg_begin();
            Value* dsp = func_llvm_buildUserInterface_args_it++;
            Value* ui = func_llvm_buildUserInterface_args_it++;

            // Get LLVM constant string
            string name = replaceSpacesWithUnderscore(label);
            GlobalVariable* llvm_label = addStringConstant(label);
            Value* const_string = fBuilder->CreateConstGEP2_32(llvm_label, 0, 0);

            Value* idx[2];
            idx[0] = genInt64(0);
            idx[1] = fUICallTable[bargraph_type];
            Value* mth_ptr = fBuilder->CreateGEP(ui, idx, idx+2);
            LoadInst* mth = fBuilder->CreateLoad(mth_ptr);

            // Generates access to zone
            int field_index = fDSPFieldsNames[zone];
            Value* zone_ptr = fBuilder->CreateStructGEP(dsp, field_index);

            Value* idx2[5];
            idx2[0] = fUIInterface_ptr;
            idx2[1] = const_string;
            idx2[2] = zone_ptr;
            idx2[3] = (itfloat() == Typed::kFloat) ? genFloat(min) : genDouble(min);
            idx2[4] = (itfloat() == Typed::kFloat) ? genFloat(max) : genDouble(max);

            CallInst* call_inst = fBuilder->CreateCall(mth, idx2, idx2+5);
            call_inst->setCallingConv(CallingConv::C);
        }

        virtual void visit(AddBargraphInst* inst)
        {
            string name;
            switch (inst->fType) {
                case AddBargraphInst::kHorizontal:
                    name = "addHorizontalBargraph"; break;
                case AddBargraphInst::kVertical:
                    name = "addVerticalBargraph"; break;
            }
            addGenericBargraph(inst->fLabel, inst->fZone, inst->fMin, inst->fMax, name);
        }

        virtual void visit(DeclareVarInst* inst)
        {
            BasicTyped* basic_typed = dynamic_cast<BasicTyped*>(inst->fTyped);
            NamedTyped* named_typed = dynamic_cast<NamedTyped*>(inst->fTyped);
            ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fTyped);
            VectorTyped* vector_typed = dynamic_cast<VectorTyped*>(inst->fTyped);

            if (inst->fAddress->getAccess() & Address::kStruct) {
                // Not supposed to happen
                //cerr << "DeclareVarInst " << inst->fName << endl;
                assert(false);
            } else if (inst->fAddress->getAccess() & Address::kFunArgs) {
                // Not supposed to happen
                assert(false);
                // Direct access Declare/Store ==> Load
            } else if (inst->fAddress->getAccess() & Address::kLink) {
                if (inst->fValue) {
                    // Result is in fCurValue;
                    inst->fValue->accept(this);
                    fDSPStackVars[inst->fAddress->getName()] = fCurValue;
                }
            } else if (inst->fAddress->getAccess() & Address::kStack || inst->fAddress->getAccess() & Address::kLoop) {

                if (basic_typed) {
                    fCurValue = fBuilder->CreateAlloca(fTypeMap[basic_typed->fType]);
                } else if (named_typed) {
                    // Used for internal structures (RWTable... etc...)
                    const llvm::Type* type = fModule->getTypeByName("struct.dsp" + named_typed->fName);
                    fCurValue = fBuilder->CreateAlloca(PointerType::get(type, 0));
                } else if (array_typed) {
                    // Arrays of 0 size are actually pointers on the type
                    if (array_typed->fSize == 0) {
                        fCurValue = fBuilder->CreateAlloca(fTypeMap[array_typed->getType()]);
                    } else {
                        fCurValue = fBuilder->CreateAlloca(ArrayType::get(fTypeMap[Typed::getTypeFromPtr(array_typed->getType())], array_typed->fSize));
                    }
                } else if (vector_typed) {
                    fCurValue = fBuilder->CreateAlloca(VectorType::get(fTypeMap[vector_typed->fType->fType], vector_typed->fSize));
                }

                //fCurValue->dump();
                fDSPStackVars[inst->fAddress->getName()] = fCurValue; // Keep var
                fDSPStackVars[inst->fAddress->getName()]->setName(inst->fAddress->getName());
                //cout << "DeclareVarInst " << inst->fAccess << " " << inst->fName << endl;

                // Declaration with a value
                if (inst->fValue) {
                    // Result is in fCurValue;
                    inst->fValue->accept(this);
                    //fCurValue->dump();
                    //fDSPStackVars[inst->fName]->dump();
                    fBuilder->CreateStore(fCurValue, fDSPStackVars[inst->fAddress->getName()]);
                }
                //fModule->dump();
            } else if (inst->fAddress->getAccess() & Address::kGlobal || inst->fAddress->getAccess() & Address::kStaticStruct) {
                if (!fModule->getGlobalVariable(inst->fAddress->getName(), true)) {
                    GlobalVariable* global_var = NULL;

                    if (basic_typed) {
                        global_var = new GlobalVariable(*fModule, fTypeMap[basic_typed->getType()], false, GlobalValue::PrivateLinkage, 0, inst->fAddress->getName());
                    } else if (array_typed) {
                        global_var = new GlobalVariable(*fModule, ArrayType::get(fTypeMap[Typed::getTypeFromPtr(array_typed->getType())], array_typed->fSize),
                            false, GlobalValue::PrivateLinkage, 0, inst->fAddress->getName());
                    } else if (vector_typed) {
                        // TO CHECK
                        global_var = new GlobalVariable(*fModule, fTypeMap[vector_typed->getType()], false, GlobalValue::PrivateLinkage, 0, inst->fAddress->getName());
                    }

                    // Declaration with a value
                    if (inst->fValue) {
                        // Result is in fCurValue;
                        inst->fValue->accept(this);
                        global_var->setInitializer(static_cast<Constant*>(fCurValue));
                    } else {
                        // Init with 0
                        if (basic_typed) {
                            Value* value = (inst->fTyped->getType() == Typed::kFloat) ? genFloat(0.f) : genInt32(0);
                            global_var->setInitializer(static_cast<Constant*>(value));
                        } else if (array_typed) {
                             global_var->setInitializer(ConstantAggregateZero::get(ArrayType::get(fTypeMap[Typed::getTypeFromPtr(array_typed->getType())],
                                array_typed->fSize)));
                        } else if (vector_typed) {

                        }
                    }

                    //global_var->dump();
                }
            };

            // No result in fCurValue
            fCurValue = NULL;
        }

        virtual void visit(RetInst* inst)
        {
            if (inst->fResult) {
                // Add a return instruction
                inst->fResult->accept(this);
                fBuilder->CreateRet(fCurValue);
            } else {
                // Add a return void instruction
                fBuilder->CreateRetVoid();
            }
        }

        virtual void visit(DropInst* inst)
        {
            if (inst->fResult) {
                // Result is in fCurValue;
                inst->fResult->accept(this);
            }

            // Drop it
            fCurValue = NULL;
        }

        virtual void visit(DeclareFunInst* inst)
        {
            Function* function = fModule->getFunction(inst->fName);

            if (!function) {  // Define it

                // Special cases for min/max
                if (inst->fName == "min" || inst->fName == "max") {
                    fCurValue = NULL;
                    return;
                }

                // Return type
                assert(fTypeMap.find(inst->fType->fResult->getType()) != fTypeMap.end());
                const llvm::Type* return_type = fTypeMap[inst->fType->fResult->getType()];

                // Prepare vector of LLVM types for args
                vector<const llvm::Type*> fun_args_type;
                list<NamedTyped*>::const_iterator it;
                for (it = inst->fType->fArgsTypes.begin(); it != inst->fType->fArgsTypes.end(); it++) {
                    //cerr << "DeclareFunInst " << (*it)->getType() << endl;
                    assert(fTypeMap.find((*it)->getType()) != fTypeMap.end());
                    fun_args_type.push_back(fTypeMap[(*it)->getType()]);
                }

                // Creates function
                FunctionType* fun_type = FunctionType::get(return_type, fun_args_type, false);
                function = Function::Create(fun_type, (inst->fType->fAttribute & FunTyped::kLocal) ? GlobalValue::InternalLinkage : GlobalValue::ExternalLinkage, inst->fName, fModule);
                function->setCallingConv(CallingConv::C);

                // Set name for function arguments
                Function::arg_iterator args = function->arg_begin();
                for (it = inst->fType->fArgsTypes.begin(); it != inst->fType->fArgsTypes.end(); it++) {
                    Value* llvm_arg = args++;
                    llvm_arg->setName((*it)->fName);
                }
            }
            //function->dump();

            // If there is a body, compile it
            if (inst->fCode->fCode.size() > 0) {

                // Prepare a block to insert into
                BasicBlock* code_block = BasicBlock::Create(getGlobalContext(), "code_block", function);
                fBuilder->SetInsertPoint(code_block);

                // Compile code in this block
                inst->fCode->accept(this);

                //function->dump();
                verifyFunction(*function);
                fBuilder->ClearInsertionPoint();
            }

            // No result
            fCurValue = NULL;
        }

        Value* genPointer2VectorLoad(Value* load_ptr, Value* load, int size)
        {
            if (size > 1) {
                //cerr << "genPointer2VectorLoad" << endl;
                //load_ptr->dump();
                //load->dump();
                //load->getType()->dump();
                //VectorType::get(load->getType(), size)->dump();
                Value* casted_load_ptr = fBuilder->CreateBitCast(load_ptr, PointerType::get(VectorType::get(load->getType(), size), 0));
                return fBuilder->CreateLoad(casted_load_ptr);
            } else {
                return load;
            }
        }

        Value* genScalar2VectorLoad(Value* load, int size)
        {
            if (size > 1) {
                //cerr << "genScalar2VectorLoad" << endl;
                //load->dump();
                //load->getType()->dump();
                /*
                Value* vector = fBuilder->CreateAlloca(VectorType::get(load->getType(), size));
                for (int i = 0; i < size; i++) {
                    vector = fBuilder->CreateInsertElement(vector, load, genInt32(i));
                }
                */

                Value* vector = UndefValue::get(VectorType::get(load->getType(), size));
                Value* idx = genInt32(0);
               // vector->dump();
                vector = fBuilder->CreateInsertElement(vector, load, idx);
                SmallVector<Constant*, 16> args;
                for (int i = 0; i < size; i++) {
                    args.push_back(static_cast<Constant*>(genInt32(0)));
                }
            #ifdef LLVM_28
                Constant* mask = ConstantVector::get(&args[0], size);
            #endif
                Constant* mask = ConstantVector::get(args);
                return fBuilder->CreateShuffleVector(vector, vector, mask, "splat");
            } else {
                return load;
            }
        }

        Value* genVectorLoad(Value* load_ptr, Value* load, int size)
        {
            if (isa<PointerType>(load->getType())) {
                return genPointer2VectorLoad(load_ptr, load, size);
            } else {
                return genScalar2VectorLoad(load, size);
            }
        }

        virtual void visit(LoadVarInst* inst)
        {
            NamedAddress* named_address =  dynamic_cast<NamedAddress*>(inst->fAddress);
            IndexedAddress* indexed_address =  dynamic_cast<IndexedAddress*>(inst->fAddress);

            if (named_address) {

                if (named_address->fAccess & Address::kStruct) {

                   // cerr << named_address->fName << endl;
                    assert(fDSPFieldsNames.find(named_address->fName) != fDSPFieldsNames.end());
                    int field_index = fDSPFieldsNames[named_address->fName];

                    // Get the enclosing function
                    Function* function = fBuilder->GetInsertBlock()->getParent();
                    Function::arg_iterator function_args_it = function->arg_begin();
                    Value* dsp = function_args_it++;
                    Value* zone_ptr = fBuilder->CreateStructGEP(dsp, field_index);

                    // We want to see array like [256 x float] as a float*
                    fCurValue = LoadArrayAsPointer(zone_ptr, inst->fAddress->getAccess() & Address::kVolatile);

                    fCurValue = genVectorLoad(zone_ptr, fCurValue, inst->fSize);

                } else if (named_address->fAccess & Address::kFunArgs) {
                    // Get the enclosing function
                    Function* function = fBuilder->GetInsertBlock()->getParent();
                    Function::arg_iterator function_args_it = function->arg_begin();
                    // Get arg with inst name
                    Value* arg;
                    bool found = false;
                    do {
                        arg = function_args_it++;
                        if (arg->getName() == named_address->fName) {
                            found = true;
                            break;
                        }
                    } while (function_args_it != function->arg_end());
                    //cerr << "named_address->fName " << named_address->fName << endl;
                    assert(found);
                    fCurValue = arg;
                    // Direct access Declare/Store ==> Load
                } else if (named_address->fAccess & Address::kLink) {
                    fCurValue = fDSPStackVars[named_address->fName];
                } else if (named_address->fAccess & Address::kStack || named_address->fAccess & Address::kLoop) {
                    //cerr << named_address->fName << endl;
                    assert(fDSPStackVars.find(named_address->fName) != fDSPStackVars.end());
                    // We want to see array like [256 x float] as a float*
                    fCurValue = LoadArrayAsPointer(fDSPStackVars[named_address->fName], inst->fAddress->getAccess() & Address::kVolatile);

                    fCurValue = genVectorLoad(fDSPStackVars[named_address->fName], fCurValue, inst->fSize);

                } else if (named_address->fAccess & Address::kGlobal || named_address->fAccess & Address::kStaticStruct) {

                    Function* function = fModule->getFunction(named_address->fName);
                    if (function) {
                        fCurValue = function;
                        //fCurValue->dump();
                    } else {
                        assert(fModule->getGlobalVariable(named_address->fName, true));
                        // We want to see array like [256 x float] as a float*
                        fCurValue = LoadArrayAsPointer(fModule->getGlobalVariable(named_address->fName, true), inst->fAddress->getAccess() & Address::kVolatile);

                        fCurValue = genVectorLoad(fModule->getGlobalVariable(named_address->fName, true), fCurValue, inst->fSize);
                    }
                }
            }

            if (indexed_address) {

                named_address =  dynamic_cast<NamedAddress*>(indexed_address->fAddress);
                assert(named_address); // One level indexation for now

                if (named_address->fAccess & Address::kStruct) {
                    //cout << "LoadVarInst " << named_address->fName << endl;
                    //fModule->dump();
                    assert(fDSPFieldsNames.find(named_address->fName) != fDSPFieldsNames.end());
                    int field_index = fDSPFieldsNames[named_address->fName];

                    // Get the enclosing function
                    Function* function = fBuilder->GetInsertBlock()->getParent();
                    Function::arg_iterator function_args_it = function->arg_begin();
                    Value* dsp = function_args_it++;
                    //dsp->dump();

                    // Compute index, result is in fCurValue
                    indexed_address->fIndex->accept(this);

                    Value* idx[2];
                    idx[0] = genInt64(0);
                    idx[1] = genInt32(field_index);

                    Value* load_ptr1 = fBuilder->CreateGEP(dsp, idx, idx+2);
                    Value* load_ptr2 = LoadArrayAsPointer(load_ptr1);
                    Value* load_ptr3 = fBuilder->CreateGEP(load_ptr2, fCurValue);
                    fCurValue = fBuilder->CreateLoad(load_ptr3);

                    fCurValue = genPointer2VectorLoad(load_ptr3, fCurValue, inst->fSize);

                } else if (named_address->fAccess & Address::kFunArgs) {
                    // Get the enclosing function
                    Function* function = fBuilder->GetInsertBlock()->getParent();
                    Function::arg_iterator function_args_it = function->arg_begin();
                    // Get arg with inst name
                    Value* arg;
                    bool found = false;
                    do {
                        arg = function_args_it++;
                        if (arg->getName() == named_address->fName) {
                            string name = arg->getName();
                            found = true;
                            break;
                        }
                    } while (function_args_it != function->arg_end());
                    assert(found);

                    // Result is in fCurValue
                    indexed_address->fIndex->accept(this);
                    Value* load_ptr = fBuilder->CreateGEP(arg, fCurValue);
                    fCurValue = fBuilder->CreateLoad(load_ptr);

                    fCurValue = genPointer2VectorLoad(load_ptr, fCurValue, inst->fSize);

                } else if (named_address->fAccess & Address::kStack || named_address->fAccess & Address::kLoop) {
                    // Compute index, result is in fCurValue
                    indexed_address->fIndex->accept(this);

                    // We want to see array like [256 x float] as a float*
                    assert(fDSPStackVars[named_address->fName]);
                    Value* load_ptr1 = LoadArrayAsPointer(fDSPStackVars[named_address->fName]);
                    Value* load_ptr2 = fBuilder->CreateGEP(load_ptr1, fCurValue);
                    fCurValue = fBuilder->CreateLoad(load_ptr2);

                    fCurValue = genPointer2VectorLoad(load_ptr2, fCurValue, inst->fSize);

                } else if (named_address->fAccess & Address::kGlobal || named_address->fAccess & Address::kStaticStruct) {
                   // Compute index, result is in fCurValue
                    indexed_address->fIndex->accept(this);
                    assert(fModule->getGlobalVariable(named_address->fName, true));

                    // We want to see array like [256 x float] as a float*
                    Value* load_ptr1 = LoadArrayAsPointer(fModule->getGlobalVariable(named_address->fName, true));
                    Value* load_ptr2 = fBuilder->CreateGEP(load_ptr1, fCurValue);
                    fCurValue = fBuilder->CreateLoad(load_ptr2);

                    fCurValue = genPointer2VectorLoad(load_ptr2, fCurValue, inst->fSize);

                } else {
                    // Default
                }
            }
        }

        virtual void visit(LoadVarAddressInst* inst)
        {
            NamedAddress* named_address =  dynamic_cast<NamedAddress*>(inst->fAddress);
            IndexedAddress* indexed_address =  dynamic_cast<IndexedAddress*>(inst->fAddress);

            if (named_address) {

                if (named_address->fAccess & Address::kStruct) {

                    assert(fDSPFieldsNames.find(named_address->fName) != fDSPFieldsNames.end());
                    int field_index = fDSPFieldsNames[named_address->fName];

                    // Get the enclosing function
                    Function* function = fBuilder->GetInsertBlock()->getParent();
                    Function::arg_iterator function_args_it = function->arg_begin();
                    Value* dsp = function_args_it++;
                    Value* zone_ptr = fBuilder->CreateStructGEP(dsp, field_index);
                    fCurValue = zone_ptr;

                } else if (named_address->fAccess & Address::kFunArgs) {
                    // Not supported
                    assert(false);
                } else if (named_address->fAccess & Address::kLink) {
                    // Not supported
                    assert(false);
                } else if (named_address->fAccess & Address::kStack || named_address->fAccess & Address::kLoop) {
                    // cerr << named_address->fName << endl;
                    assert(fDSPStackVars.find(named_address->fName) != fDSPStackVars.end());
                    fCurValue = fDSPStackVars[named_address->fName];
                } else if (named_address->fAccess & Address::kGlobal || named_address->fAccess & Address::kStaticStruct) {
                    assert(fModule->getGlobalVariable(named_address->fName, true));
                    fCurValue = fModule->getGlobalVariable(named_address->fName, true);
                }
            }

            if (indexed_address) {

                named_address =  dynamic_cast<NamedAddress*>(indexed_address->fAddress);
                assert(named_address); // One level indexation for now

                if (named_address->fAccess & Address::kStruct) {
                    // cout << "LoadVarAddressInst " << named_address->fName << endl;
                    //fModule->dump();
                    assert(fDSPFieldsNames.find(named_address->fName) != fDSPFieldsNames.end());
                    int field_index = fDSPFieldsNames[named_address->fName];
                    // cout << "LoadVarAddressInst " << field_index  << endl;

                    // Get the enclosing function
                    Function* function = fBuilder->GetInsertBlock()->getParent();
                    Function::arg_iterator function_args_it = function->arg_begin();
                    Value* dsp = function_args_it++;

                    // Result is in fCurValue;
                    indexed_address->fIndex->accept(this);

                    Value* idx[2];
                    idx[0] = genInt64(0);
                    idx[1] = genInt32(field_index);

                    Value* load_ptr1 = fBuilder->CreateGEP(dsp, idx, idx+2);
                    Value* load_ptr2 = LoadArrayAsPointer(load_ptr1);
                    Value* load_ptr3 = fBuilder->CreateGEP(load_ptr2, fCurValue);
                    fCurValue = load_ptr3;

                } else if (named_address->fAccess & Address::kFunArgs) {
                    // Get the enclosing function
                    Function* function = fBuilder->GetInsertBlock()->getParent();
                    Function::arg_iterator function_args_it = function->arg_begin();
                    // Get arg with inst name
                    Value* arg;
                    bool found = false;
                    do {
                        arg = function_args_it++;
                        if (arg->getName() == named_address->fName) {
                            string name = arg->getName();
                            found = true;
                            break;
                        }
                    } while (function_args_it != function->arg_end());
                    assert(found);

                    // Result is in fCurValue
                    indexed_address->fIndex->accept(this);
                    Value* load_ptr = fBuilder->CreateGEP(arg, fCurValue);
                    fCurValue = load_ptr;
                } else if (named_address->fAccess & Address::kStack || named_address->fAccess & Address::kLoop) {
                    // Compute index, result is in fCurValue
                    indexed_address->fIndex->accept(this);

                    //cout << "Address::kStack " << named_address->fName << endl;
                    assert(fDSPStackVars.find(named_address->fName) != fDSPStackVars.end());

                    // We want to see array like [256 x float] as a float*
                    Value* load_ptr1 = LoadArrayAsPointer(fDSPStackVars[named_address->fName]);
                    Value* load_ptr2 = fBuilder->CreateGEP(load_ptr1, fCurValue);
                    fCurValue = load_ptr2;
                } else if (named_address->fAccess & Address::kGlobal || named_address->fAccess & Address::kStaticStruct) {
                   // Compute index, result is in fCurValue
                    indexed_address->fIndex->accept(this);
                    assert(fModule->getGlobalVariable(named_address->fName, true));

                    // We want to see array like [256 x float] as a float*
                    Value* load_ptr1 = LoadArrayAsPointer(fModule->getGlobalVariable(named_address->fName, true));
                    Value* load_ptr2 = fBuilder->CreateGEP(load_ptr1, fCurValue);
                    fCurValue = load_ptr2;
                } else {
                    // Default
                }
            }
        }

        void genVectorStore(Value* store_ptr, Value* store, int size, bool vola = false)
        {
            if (size > 1) {
                //cerr << "genVectorStore vector" << endl;
                //store_ptr->dump();
                //store->dump();
                //store->getType()->dump();
                Value* casted_store_ptr = fBuilder->CreateBitCast(store_ptr, PointerType::get(store->getType(), 0));
                fBuilder->CreateStore(store, casted_store_ptr, vola);
            } else {
                //cerr << "genVectorStore scalar" << endl;
                //store_ptr->dump();
                //store->dump();
                fBuilder->CreateStore(store, store_ptr, vola);
            }
        }

        virtual void visit(StoreVarInst* inst)
        {
            NamedAddress* named_address =  dynamic_cast<NamedAddress*>(inst->fAddress);
            IndexedAddress* indexed_address =  dynamic_cast<IndexedAddress*>(inst->fAddress);

            if (named_address) {

               if (named_address->fAccess & Address::kStruct) {
                    // Result is in fCurValue;
                    inst->fValue->accept(this);

                    assert(fDSPFieldsNames.find(named_address->fName) != fDSPFieldsNames.end());
                    int field_index = fDSPFieldsNames[named_address->fName];

                    // Get the enclosing function
                    Function* function = fBuilder->GetInsertBlock()->getParent();
                    Function::arg_iterator function_args_it = function->arg_begin();
                    Value* dsp = function_args_it++;
                    Value* store_ptr = fBuilder->CreateStructGEP(dsp, field_index);

                    //fBuilder->CreateStore(fCurValue, store_ptr, inst->fAddress->getAccess() & Address::kVolatile);
                    genVectorStore(store_ptr, fCurValue, inst->fAddress->getAccess() & Address::kVolatile);

                 } else if (named_address->fAccess & Address::kFunArgs) {
                    // Result is in fCurValue
                    inst->fValue->accept(this);

                    // Get the enclosing function
                    Function* function = fBuilder->GetInsertBlock()->getParent();
                    Function::arg_iterator function_args_it = function->arg_begin();
                    // Get arg with inst name
                    Value* arg;
                    bool found = false;
                    do {
                        arg = function_args_it++;
                        if (arg->getName() == named_address->fName) {
                            found = true;
                            break;
                        }
                    } while (function_args_it != function->arg_end());
                    assert(found);

                    // fBuilder->CreateStore(fCurValue, arg);
                    genVectorStore(arg, fCurValue, inst->fValue->fSize);

                // Direct access Declare/Store ==> Load
                } else if (named_address->fAccess & Address::kLink) {
                    // Result is in fCurValue
                    inst->fValue->accept(this);
                    fDSPStackVars[named_address->fName] = fCurValue;

                 } else if (named_address->fAccess & Address::kStack || named_address->fAccess & Address::kLoop) {
                    assert(fDSPStackVars.find(named_address->fName) != fDSPStackVars.end());
                    // Result is in fCurValue
                    inst->fValue->accept(this);

                    //fBuilder->CreateStore(fCurValue, fDSPStackVars[named_address->fName], inst->fAddress->getAccess() & Address::kVolatile);
                    genVectorStore(fDSPStackVars[named_address->fName], fCurValue, inst->fValue->fSize, inst->fAddress->getAccess() & Address::kVolatile);

                 } else if (named_address->fAccess & Address::kGlobal || named_address->fAccess & Address::kStaticStruct) {
                    // Result is in fCurValue
                    inst->fValue->accept(this);
                    //fCurValue->dump();
                    assert(fModule->getGlobalVariable(named_address->fName, true));

                    //fBuilder->CreateStore(fCurValue, fModule->getGlobalVariable(named_address->fName, true), inst->fAddress->getAccess() & Address::kVolatile);
                    //fCurValue->dump();
                    genVectorStore(fModule->getGlobalVariable(named_address->fName, true), fCurValue, inst->fValue->fSize, inst->fAddress->getAccess() & Address::kVolatile);
                }
            }

            if (indexed_address) {

                named_address =  dynamic_cast<NamedAddress*>(indexed_address->fAddress);
                assert(named_address); // One level indexation for now

                if (named_address->fAccess & Address::kStruct) {

                    assert(fDSPFieldsNames.find(named_address->fName) != fDSPFieldsNames.end());
                    int field_index = fDSPFieldsNames[named_address->fName];

                    // Get the enclosing function
                    Function* function = fBuilder->GetInsertBlock()->getParent();
                    Function::arg_iterator function_args_it = function->arg_begin();
                    Value* dsp = function_args_it++;

                    // Compute index, result is in fCurValue
                    indexed_address->fIndex->accept(this);

                    Value* idx[2];
                    idx[0] = genInt64(0);
                    idx[1] = genInt32(field_index);

                    Value* store_ptr1 = fBuilder->CreateGEP(dsp, idx, idx+2);
                    Value* store_ptr2 = LoadArrayAsPointer(store_ptr1);
                    Value* store_ptr = fBuilder->CreateGEP(store_ptr2, fCurValue);

                    // Compute value to be stored, result is in fCurValue
                    inst->fValue->accept(this);

                    //fBuilder->CreateStore(fCurValue, store_ptr);
                    genVectorStore(store_ptr, fCurValue, inst->fValue->fSize);

                } else if (named_address->fAccess & Address::kFunArgs) {
                    // Get the enclosing function
                    Function* function = fBuilder->GetInsertBlock()->getParent();
                    Function::arg_iterator function_args_it = function->arg_begin();
                    // Get arg with inst name
                    Value* arg;
                    bool found = false;
                    do {
                        arg = function_args_it++;
                        string name = arg->getName();
                        //printf("arg %s \n", name.c_str());
                        if (arg->getName() == named_address->fName) {
                            found = true;
                            break;
                        }
                    } while (function_args_it != function->arg_end());
                    assert(found);

                    // Compute index, result is in fCurValue
                    indexed_address->fIndex->accept(this);
                    Value* store_ptr = fBuilder->CreateGEP(arg, fCurValue);

                    // Compute value to be stored, result is in fCurValue
                    inst->fValue->accept(this);

                    //fBuilder->CreateStore(fCurValue, store_ptr);
                    genVectorStore(store_ptr, fCurValue, inst->fValue->fSize);

                } else if (named_address->fAccess & Address::kStack || named_address->fAccess & Address::kLoop) {
                    //cout <<  "named_address->fName " << named_address->fName.c_str() << endl;
                    assert(fDSPStackVars.find(named_address->fName) != fDSPStackVars.end());

                    // Compute index, result is in fCurValue
                    indexed_address->fIndex->accept(this);

                    // We want to see array like [256 x float] as a float*
                    Value* store_ptr1 = LoadArrayAsPointer(fDSPStackVars[named_address->fName]);
                    Value* store_ptr2 = fBuilder->CreateGEP(store_ptr1, fCurValue);

                    // Compute value to be stored, result is in fCurValue
                    inst->fValue->accept(this);

                    //fBuilder->CreateStore(fCurValue, store_ptr2);
                    genVectorStore(store_ptr2, fCurValue, inst->fValue->fSize);

                } else if (named_address->fAccess & Address::kGlobal || named_address->fAccess & Address::kStaticStruct) {
                    // Compute index, result is in fCurValue
                    indexed_address->fIndex->accept(this);
                    assert(fModule->getGlobalVariable(named_address->fName, true));

                    // We want to see array like [256 x float] as a float*
                    Value* store_ptr1 = LoadArrayAsPointer(fModule->getGlobalVariable(named_address->fName, true));
                    Value* store_ptr2 = fBuilder->CreateGEP(store_ptr1, fCurValue);

                    // Compute value to be stored, result is in fCurValue
                    inst->fValue->accept(this);

                    //fBuilder->CreateStore(fCurValue, store_ptr2);
                    genVectorStore(store_ptr2, fCurValue, inst->fValue->fSize);

                } else {
                    // default
                }
            }

            // No result in fCurValue
            fCurValue = NULL;
        }

        virtual void visit(FloatNumInst* inst)
        {
            fCurValue = genFloat(inst->fNum, inst->fSize);
        }

        virtual void visit(DoubleNumInst* inst)
        {
            fCurValue = genDouble(inst->fNum, inst->fSize);
        }

        virtual void visit(BoolNumInst* inst)
        {
            fCurValue = genInt1(inst->fNum, inst->fSize);
        }

        virtual void visit(IntNumInst* inst)
        {
            fCurValue = genInt32(inst->fNum, inst->fSize);
        }

        virtual void visit(BinopInst* inst)
        {
            // Keep result of first arg compilation
            inst->fInst1->accept(this);
            LlvmValue res1 = fCurValue;

            // Keep result of second arg compilation
            inst->fInst2->accept(this);
            LlvmValue res2 = fCurValue;

            fCurValue = generateBinopAux(inst->fOpcode, res1, res2, inst->fSize);
        }

        virtual void visit(CastNumInst* inst)
        {
            // Compile exp to cast, result in fCurValue
            inst->fInst->accept(this);

            BasicTyped* basic_typed = dynamic_cast<BasicTyped*>(inst->fTyped);

            if (basic_typed) {

                switch (basic_typed->fType) {

                    // Takes the type of internal real
                    case Typed::kFloatMacro:
                        visitAux(itfloat(), inst->fSize);
                        break;

                    default:
                        visitAux(basic_typed->fType, inst->fSize);
                        break;
                }

            } else {
                // No yet
                assert(false);
            }
        }

        void visitAux(Typed::VarType type, int size)
        {
            switch (type) {

                case Typed::kFloat:
                    if (fCurValue->getType() == getInt32Ty(size)) {
                         fCurValue = fBuilder->CreateSIToFP(fCurValue, getFloatTy(size));
                    } else if (fCurValue->getType() == getFloatTy(size))  {
                        // Nothing to do
                    } else if (fCurValue->getType() == getDoubleTy(size))  {
                        fCurValue = fBuilder->CreateFPTrunc(fCurValue, getFloatTy(size));
                    }
                    break;

                case Typed::kInt:
                    if (fCurValue->getType() == getInt32Ty(size)) {
                        // Nothing to do
                    } else if (fCurValue->getType() == getFloatTy(size))  {
                         fCurValue = fBuilder->CreateFPToSI(fCurValue, getInt32Ty(size));
                    } else if (fCurValue->getType() == getDoubleTy(size))  {
                         fCurValue = fBuilder->CreateFPToSI(fCurValue, getInt32Ty(size));
                    }
                    break;

                case Typed::kDouble:
                    if (fCurValue->getType() == getInt32Ty(size)) {
                        fCurValue = fBuilder->CreateSIToFP(fCurValue, getDoubleTy(size));
                    } else if (fCurValue->getType() == getFloatTy(size))  {
                        fCurValue = fBuilder->CreateFPExt(fCurValue, getDoubleTy(size));
                    } else if (fCurValue->getType() == getDoubleTy(size))  {
                       // Nothing to do
                    }
                    break;

                case Typed::kQuad:
                    // No supposed to happen
                    assert(false);
                    break;

                default:
                    // No supposed to happen
                    assert(false);
                    break;

            }
        }

        void generateFunMinMax(FunCallInst* inst)
        {
            vector<LlvmValue> fun_args;

            for (list<ValueInst*>::const_iterator it = inst->fArgs.begin(); it != inst->fArgs.end(); it++) {
                // Each argument is compiled and result is in fCurValue
                (*it)->accept(this);
                //fCurValue->dump();
                fun_args.push_back(fCurValue);
            }

            if (inst->fName == "min") {
                fCurValue = generateFunMinMaxAux(fun_args[0], fun_args[1], inst->fSize, kLT);
            } else if (inst->fName == "max") {
                fCurValue = generateFunMinMaxAux(fun_args[0], fun_args[1], inst->fSize, kGT);
            }
        }

        virtual void visit(FunCallInst* inst)
        {
            // Special case
            if (inst->fName == "min" || inst->fName == "max") {
                generateFunMinMax(inst);
                return;
            }

            // Compile arguments
            vector<LlvmValue> fun_args;
            list<ValueInst*>::const_iterator it;

            Function* function = fModule->getFunction(inst->fName);
            //cerr << "FunCallInst " << inst->fName << endl;
            assert(function);

            //cout << "FunCallInst " << inst->fName << endl;
            Function::arg_iterator args = function->arg_begin();
            for (it = inst->fArgs.begin(); it != inst->fArgs.end(); it++, args++) {
                // Each argument is compiled and result is in fCurValue
                (*it)->accept(this);
                //fCurValue->dump();
                // Cast any struct* type to void* if needed
                if (args->getType() == PointerType::get(llvm::Type::getInt8Ty(getGlobalContext()), 0)) {
                    Value* casted = fBuilder->CreateBitCast(fCurValue, PointerType::get(llvm::Type::getInt8Ty(getGlobalContext()), 0));
                    fun_args.push_back(casted);
                } else {
                    fun_args.push_back(fCurValue);
                }
            }

            //cerr << "Size " << fun_args.size() << endl;
            //function->dump();

            CallInst* call_inst = fBuilder->CreateCall(function, fun_args.begin(), fun_args.end());
            call_inst->setCallingConv(CallingConv::C);

            //fModule->dump();

            // Result is function call
            fCurValue = call_inst;
        }

        /*
        virtual void visit(Select2Inst* inst)
        {
            // Compile condition, result in fCurValue
            inst->fCond->accept(this);

            // Convert condition to a bool by comparing to 1
            Value* cond_value = fBuilder->CreateICmpEQ(fCurValue, genInt32(1, inst->fSize), "ifcond");

            // Compile then branch, result in fCurValue
            inst->fThen->accept(this);
            Value* then_value = fCurValue;

            // Compile else branch, result in fCurValue
            inst->fElse->accept(this);
            Value* else_value = fCurValue;

            // Creates the result
            fCurValue = fBuilder->CreateSelect(cond_value, then_value, else_value);
        }
        */

        virtual void visit(Select2Inst* inst)
        {
            // Select vector mode X86 code generator sill not implemented, generates the code in scalar for now
            if (inst->fSize > 1) {

                // Compile condition, result in fCurValue
                inst->fCond->accept(this);
                Value* cond_value = fCurValue;

                // Compile then branch, result in fCurValue
                inst->fThen->accept(this);
                Value* then_value = fCurValue;

                // Compile else branch, result in fCurValue
                inst->fElse->accept(this);
                Value* else_value = fCurValue;

                // Create resulting vector
                Value* select_vector = UndefValue::get(then_value->getType());

                for (int i = 0; i < inst->fSize; i++) {

                    Value* scalar_cond_value1 = fBuilder->CreateExtractElement(cond_value, genInt32(i));
                    Value* scalar_cond_value2 = fBuilder->CreateICmpEQ(scalar_cond_value1, genInt32(1), "ifcond");
                    Value* scalar_then_value = fBuilder->CreateExtractElement(then_value, genInt32(i));
                    Value* scalar_else_value = fBuilder->CreateExtractElement(else_value, genInt32(i));

                    // Scalar select
                    Value* scalar_res = fBuilder->CreateSelect(scalar_cond_value2, scalar_then_value, scalar_else_value);

                    // Fill resulting vector
                    select_vector = fBuilder->CreateInsertElement(select_vector, scalar_res, genInt32(i));
                }

                // Final result
                fCurValue = select_vector;

            } else {

                // Compile condition, result in fCurValue
                inst->fCond->accept(this);

                // Convert condition to a bool by comparing to 1
                Value* cond_value = fBuilder->CreateICmpEQ(fCurValue, genInt32(1, inst->fSize), "ifcond");

                // Compile then branch, result in fCurValue
                inst->fThen->accept(this);
                Value* then_value = fCurValue;

                // Compile else branch, result in fCurValue
                inst->fElse->accept(this);
                Value* else_value = fCurValue;

                // Creates the result
                fCurValue = fBuilder->CreateSelect(cond_value, then_value, else_value);
            }
        }

        virtual void visit(IfInst* inst)
        {
            // Compile condition, result in fCurValue
            inst->fCond->accept(this);

            // Convert condition to a bool by comparing equal to comp_val value
            Value* cond_value = fBuilder->CreateICmpEQ(fCurValue, genInt32(1), "ifcond");

            Function* function = fBuilder->GetInsertBlock()->getParent();

            // Create blocks for the then and else cases.  Insert the 'then' block at the end of the function
            BasicBlock* then_block = BasicBlock::Create(getGlobalContext(), "then_code", function);
            BasicBlock* else_block = BasicBlock::Create(getGlobalContext(), "else_code");
            BasicBlock* merge_block = BasicBlock::Create(getGlobalContext(), "ifcont");

            fBuilder->CreateCondBr(cond_value, then_block, else_block);

            // Emit then value.
            fBuilder->SetInsertPoint(then_block);

            // Compile then branch, result in fCurValue
            inst->fThen->accept(this);
            // "Then" is a BlockInst so no result in fCurValue

            fBuilder->CreateBr(merge_block);
            // Codegen of 'Then' can change the current block, update then_block for the PHI
            then_block = fBuilder->GetInsertBlock();

            // Emit else block.
            function->getBasicBlockList().push_back(else_block);
            fBuilder->SetInsertPoint(else_block);

             // Compile else branch, result in fCurValue
            inst->fElse->accept(this);
            // "Else" is a BlockInst so no result in fCurValue

            fBuilder->CreateBr(merge_block);
            // Codegen of 'Else' can change the current block, update else_block for the PHI
            else_block = fBuilder->GetInsertBlock();

            // Emit merge block
            function->getBasicBlockList().push_back(merge_block);
            fBuilder->SetInsertPoint(merge_block);

            // No result in fCurValue
            fCurValue = NULL;
        }

        virtual void visit(ForLoopInst* inst)
        {
            Function* function = fBuilder->GetInsertBlock()->getParent();
            assert(function);

            // Prepare init_code block
            BasicBlock* init_block = BasicBlock::Create(getGlobalContext(), "init_block", function);

            // Link previous_block and init_block
            fBuilder->CreateBr(init_block);

            // Start insertion in init_block
            fBuilder->SetInsertPoint(init_block);

            // Compute init value, now loop counter is allocated
            inst->fInit->accept(this);

            // Get loop counter local variable
            DeclareVarInst* declare_inst = dynamic_cast<DeclareVarInst*>(inst->fInit);
            StoreVarInst* store_inst = dynamic_cast<StoreVarInst*>(inst->fInit);
            string loop_counter_name;

            if (declare_inst) {
                loop_counter_name = declare_inst->fAddress->getName();
            } else if (store_inst) {
                loop_counter_name = store_inst->fAddress->getName();
            } else {
                cerr << "Error in ForLoopInst "<< endl;
                assert(false);
            }

            assert(fDSPStackVars.find(loop_counter_name) != fDSPStackVars.end());
            Value* loop_counter = fBuilder->CreateLoad(fDSPStackVars[loop_counter_name]);

            // Prepare exec_code block
            BasicBlock* exec_block = BasicBlock::Create(getGlobalContext(), "exec_code", function);

            // Link init_block and exec_block
            fBuilder->CreateBr(exec_block);

            // Start insertion in exec_block
            fBuilder->SetInsertPoint(exec_block);

            // Start the PHI node with an entry for start
            PHINode* phi_node = fBuilder->CreatePHI(fBuilder->getInt32Ty(), loop_counter_name);
            phi_node->addIncoming(loop_counter, init_block);

            // Generates loop internal code
            inst->fCode->accept(this);

            // Get last block of post code section
            BasicBlock* current_block = fBuilder->GetInsertBlock();

            // Compute next index, result in fCurValue
            StoreVarInst* store_inst1 = dynamic_cast<StoreVarInst*>(inst->fIncrement);
            assert(store_inst1);
            store_inst1->fValue->accept(this);
            Value* next_index = fCurValue;
            next_index->setName("nextindex");

            // Store the next value
            fBuilder->CreateStore(next_index, fDSPStackVars[loop_counter_name]);

            // Compute end condition, result in fCurValue
            inst->fEnd->accept(this);

            // Convert condition to a bool
            Value* end_cond = fBuilder->CreateTrunc(fCurValue, fBuilder->getInt1Ty());

            // Add a new entry to the PHI node for the backedge
            phi_node->addIncoming(next_index, current_block);

            // Create the exit_block and insert it
            BasicBlock* exit_block = BasicBlock::Create(getGlobalContext(), "exit_block", function);

            // Insert the conditional branch into the end of loopend_block
            fBuilder->CreateCondBr(end_cond, exec_block, exit_block);

            // Move insertion in exit_block
            fBuilder->SetInsertPoint(exit_block);

            // No result in fCurValue
            fCurValue = NULL;
        }

        virtual void visit(WhileLoopInst* inst)
        {
            Function* function = fBuilder->GetInsertBlock()->getParent();
            assert(function);

            // Prepare cond_block block
            BasicBlock* cond_block = BasicBlock::Create(getGlobalContext(), "cond_block", function);

            // Link previous_block and cond_block
            fBuilder->CreateBr(cond_block);

            // Start insertion in cond_block
            fBuilder->SetInsertPoint(cond_block);

            // Compile condition, result in fCurValue
            inst->fCond->accept(this);

            // Create the exec_block and insert it
            BasicBlock* exec_block = BasicBlock::Create(getGlobalContext(), "exec_block", function);

            // Create the exit_block and insert it
            BasicBlock* exit_block = BasicBlock::Create(getGlobalContext(), "exit_block", function);

            // Convert condition to a bool
            Value* end_cond = fBuilder->CreateTrunc(fCurValue, fBuilder->getInt1Ty());

            // Insert the conditional branch into the end of cond_block
            fBuilder->CreateCondBr(end_cond, exec_block, exit_block);

             // Move insertion in exec_block
            fBuilder->SetInsertPoint(exec_block);

            // Compiles internal block
            inst->fCode->accept(this);

            // Branch back to cond block
            fBuilder->CreateBr(cond_block);

            // Move insertion in exit_block
            fBuilder->SetInsertPoint(exit_block);

            // No result in fCurValue
            fCurValue = NULL;
        }

        virtual void visit(BlockInst* inst)
        {
            if (fBuilder->GetInsertBlock()) {
                Function* function = fBuilder->GetInsertBlock()->getParent();
                assert(function);

                // Prepare code_block block
                BasicBlock* code_block = BasicBlock::Create(getGlobalContext(), "block_code", function);

                // Link previous_block and code_block
                fBuilder->CreateBr(code_block);

                // Start insertion in code_block
                fBuilder->SetInsertPoint(code_block);
            }

            // Generates block internal code
            list<StatementInst*>::const_iterator it;
            for (it = inst->fCode.begin(); it != inst->fCode.end(); it++) {
                (*it)->accept(this);
            }

            // No result in fCurValue
            fCurValue = NULL;
        }

        virtual void visit(::SwitchInst* inst)
        {
            Function* function = fBuilder->GetInsertBlock()->getParent();
            assert(function);

            // Prepare init_code block
            BasicBlock* init_block = BasicBlock::Create(getGlobalContext(), "init_block", function);

            // Prepare exit_block block
            BasicBlock* exit_block = BasicBlock::Create(getGlobalContext(), "exit_block", function);

            // Link previous_block and init_block
            fBuilder->CreateBr(init_block);

            // Start insertion in init_block
            fBuilder->SetInsertPoint(init_block);

            // Compile condition, result in fCurValue
            inst->fCond->accept(this);

            list<pair<int, BlockInst*> >::const_iterator it;
            for (it = inst->fCode.begin(); it != inst->fCode.end(); it++) {
                if ((*it).first == -1) // Default case found
                    break;
            }

            // Creates "default" block
            BasicBlock* default_block = BasicBlock::Create(getGlobalContext(), "default", function);

            // Link init_block and default_block (that is switch block)
            fBuilder->CreateBr(default_block);

            // Move insertion in default_block
            fBuilder->SetInsertPoint(default_block);

            // Compiles "default" block
            if (it != inst->fCode.end()) {
                (*it).second->accept(this);
                // Link init_block and exit_block
                fBuilder->CreateBr(exit_block);
            }

            // Creates switch
            llvm::SwitchInst* switch_inst = fBuilder->CreateSwitch(fCurValue, default_block, inst->fCode.size());

            for (it = inst->fCode.begin(); it != inst->fCode.end(); it++) {
                if ((*it).first != -1)  { // All cases but "default"
                    // Creates "case" block
                    BasicBlock* case_block = BasicBlock::Create(getGlobalContext(), "case", function);
                    // Move insertion in case_block
                    fBuilder->SetInsertPoint(case_block);
                    // Compiles "case" block
                    (*it).second->accept(this);
                    // Link init_block and exit_block
                    fBuilder->CreateBr(exit_block);
                    // Add it into the switch
                    switch_inst->addCase(static_cast<ConstantInt*>(genInt32((*it).first)), case_block);
                }
            }

            // Move insertion in exit_block
            fBuilder->SetInsertPoint(exit_block);

            // No result in fCurValue
            fCurValue = NULL;
        }

        //==============
        // Helper code
        //==============

        LlvmValue generateScalarSelect(int opcode, LlvmValue cond_value, LlvmValue then_value, LlvmValue else_value, int size)
        {
            if (size == 1) {
                return fBuilder->CreateSelect(cond_value, then_value, else_value);
            } else {

                // Select vector mode X86 code generator sill not implemented, generates the code in scalar for now

                // Create resulting vector
                Value* select_vector = UndefValue::get(then_value->getType());

                for (int i = 0; i < size; i++) {

                    Value* scalar_cond_value = fBuilder->CreateExtractElement(cond_value, genInt32(i));
                    Value* scalar_then_value = fBuilder->CreateExtractElement(then_value, genInt32(i));
                    Value* scalar_else_value = fBuilder->CreateExtractElement(else_value, genInt32(i));

                    // Scalar select
                    Value* scalar_res = fBuilder->CreateSelect(scalar_cond_value, scalar_then_value, scalar_else_value);

                    // Fill resulting vector
                    select_vector = fBuilder->CreateInsertElement(select_vector, scalar_res, genInt32(i));
                }

                // Final result
                return select_vector;
            }
        }

        LlvmValue generateBinOpFloat(int opcode, LlvmValue arg1, LlvmValue arg2, int size)
        {
            if (opcode >= kGT && opcode < kAND) {
                Value* comp_value = fBuilder->CreateFCmp((CmpInst::Predicate)gBinOpTable[opcode]->fLlvmFloatInst, arg1, arg2);
                //return fBuilder->CreateSelect(comp_value, genFloat(1.0f, size), genFloat(0.0f, size));
                return generateScalarSelect(opcode, comp_value, genFloat(1.0f, size), genFloat(0.0f, size), size);
            } else {
                return fBuilder->CreateBinOp((Instruction::BinaryOps)gBinOpTable[opcode]->fLlvmFloatInst, arg1, arg2);
            }
        }

        LlvmValue generateBinOpDouble(int opcode, LlvmValue arg1, LlvmValue arg2, int size)
        {
            if (opcode >= kGT && opcode < kAND) {
                Value* comp_value = fBuilder->CreateFCmp((CmpInst::Predicate)gBinOpTable[opcode]->fLlvmFloatInst, arg1, arg2);
                //return fBuilder->CreateSelect(comp_value, genDouble(1.0, size), genDouble(0.0, size));
                return generateScalarSelect(opcode, comp_value, genDouble(1.0, size), genDouble(0.0, size), size);
            } else {
                return fBuilder->CreateBinOp((Instruction::BinaryOps)gBinOpTable[opcode]->fLlvmFloatInst, arg1, arg2);
            }
        }

        LlvmValue generateBinOpInt32(int opcode, LlvmValue arg1, LlvmValue arg2, int size)
        {
            if (opcode >= kGT && opcode < kAND) {
                Value* comp_value = fBuilder->CreateICmp((CmpInst::Predicate)gBinOpTable[opcode]->fLlvmIntInst, arg1, arg2);
                //return fBuilder->CreateSelect(comp_value, genInt32(1, size), genInt32(0, size));
                return generateScalarSelect(opcode, comp_value, genInt32(1, size), genInt32(0, size), size);
            } else {
                return fBuilder->CreateBinOp((Instruction::BinaryOps)gBinOpTable[opcode]->fLlvmIntInst, arg1, arg2);
            }
        }

        LlvmValue generateBinopAux(int opcode, LlvmValue arg1, LlvmValue arg2, int size)
        {
            assert(arg1);
            assert(arg2);
            //cerr << "generateBinopAux ARGS" << endl;
            //arg1->dump();
            //arg2->dump();

            assert(fBuilder);

            // Arguments are casted if needed in InstructionsCompiler::generateBinOp
            assert(arg1->getType() == arg2->getType());

            if (arg1->getType() == getFloatTy(size)) {
                return generateBinOpFloat(opcode, arg1, arg2, size);
            } else if (arg1->getType() == getInt32Ty(size)) {
                return generateBinOpInt32(opcode, arg1, arg2, size);
            } else if (arg1->getType() == getDoubleTy(size)) {
                return generateBinOpDouble(opcode, arg1, arg2, size);
            } else {
                // Should not happen
                cerr << "generateBinopAux" << endl;
                //arg1->getType()->dump();
                //arg2->getType()->dump();
                assert(false);
                return NULL;
            }

            /*
            if (arg1->getType() == getFloatTy(size) && arg2->getType() == getFloatTy(size)) {

                return generateBinOpFloat(opcode, arg1, arg2, size);

            } else if (arg1->getType() == getFloatTy(size) && arg2->getType() == getDoubleTy(size)) {

                // Generates cast arg1 to double
                Value* cast_value = fBuilder->CreateFPExt(arg1, getDoubleTy(size));
                return generateBinOpDouble(opcode, cast_value, arg2, size);

            } else if (arg1->getType() == getFloatTy(size) && arg2->getType() == getInt32Ty(size)) {

                // Generates cast arg2 to float
                Value* cast_value = fBuilder->CreateSIToFP(arg2, getFloatTy(size));
                return generateBinOpFloat(opcode, arg1, cast_value, size);

            } else if (arg1->getType() == getDoubleTy(size) && arg2->getType() == getFloatTy(size)) {

                // Generates cast arg2 to double
                Value* cast_value = fBuilder->CreateFPExt(arg2, getDoubleTy(size));
                return generateBinOpDouble(opcode, arg1, cast_value, size);

            } else if (arg1->getType() == getDoubleTy(size) && arg2->getType() == getDoubleTy(size)) {

                return generateBinOpDouble(opcode, arg1, arg2, size);

            } else if (arg1->getType() == getDoubleTy(size) && arg2->getType() == getInt32Ty(size)) {

                // Generates cast to double
                Value* cast_value = fBuilder->CreateSIToFP(arg2, getDoubleTy(size));
                return generateBinOpDouble(opcode, arg1, cast_value, size);

            } else if (arg1->getType() == getInt32Ty(size) && arg2->getType() == getFloatTy(size)) {

                // Generates cast to float
                Value* cast_value = fBuilder->CreateSIToFP(arg1, getFloatTy(size));
                return generateBinOpFloat(opcode, cast_value, arg2, size);

            } else if (arg1->getType() == getInt32Ty(size) && arg2->getType() == getDoubleTy(size)) {

                // Generates cast to double
                Value* cast_value = fBuilder->CreateSIToFP(arg1, getDoubleTy(size));
                return generateBinOpDouble(opcode, cast_value, arg2, size);

            } else if (arg1->getType() == getInt32Ty(size) && arg2->getType() == getInt32Ty(size)) {

                return generateBinOpInt32(opcode, arg1, arg2, size);

            } else {
                // Should not happen
                cerr << "generateBinopAux" << endl;
                arg1->getType()->dump();
                arg2->getType()->dump();
                assert(false);
                return NULL;
            }
            */
        }

        LlvmValue generateFunMinMaxAux(Value* arg1, Value* arg2, int size, int comparator)
        {
            if (arg1->getType() == getFloatTy(size) && arg2->getType() == getFloatTy(size)) {

                Value* comp_value = fBuilder->CreateFCmp((llvm::CmpInst::Predicate)gBinOpTable[comparator]->fLlvmFloatInst, arg1, arg2);
                //return fBuilder->CreateSelect(comp_value, arg1, arg2);
                return generateScalarSelect(comparator, comp_value, arg1, arg2, size);

            } else if (arg1->getType() == getFloatTy(size) && arg2->getType() == getDoubleTy(size)) {

                // Generates cast arg1 to double
                Value* cast_value = fBuilder->CreateFPExt(arg1, getDoubleTy(size));
                Value* comp_value = fBuilder->CreateFCmp((llvm::CmpInst::Predicate)gBinOpTable[comparator]->fLlvmFloatInst, cast_value, arg2);
                //return fBuilder->CreateSelect(comp_value, cast_value, arg2);
                return generateScalarSelect(comparator, comp_value, arg1, arg2, size);

            } else if (arg1->getType() == getFloatTy(size) && arg2->getType() == getInt32Ty(size)) {

                // Generates cast arg2 to float
                Value* cast_value = fBuilder->CreateSIToFP(arg2, getFloatTy(size));
                Value* comp_value = fBuilder->CreateFCmp((llvm::CmpInst::Predicate)gBinOpTable[comparator]->fLlvmFloatInst, arg1, cast_value);
                //return fBuilder->CreateSelect(comp_value, arg1, cast_value);
                return generateScalarSelect(comparator, comp_value, arg1, cast_value, size);

            } else if (arg1->getType() == getDoubleTy(size) && arg2->getType() == getFloatTy(size)) {

                // Generates cast arg2 to double
                Value* cast_value = fBuilder->CreateFPExt(arg2, getDoubleTy(size));
                Value* comp_value = fBuilder->CreateFCmp((llvm::CmpInst::Predicate)gBinOpTable[comparator]->fLlvmFloatInst, arg1, cast_value);
                //return fBuilder->CreateSelect(comp_value, arg1, cast_value);
                return generateScalarSelect(comparator, comp_value, arg1, cast_value, size);

            } else if (arg1->getType() == getDoubleTy(size) && arg2->getType() == getDoubleTy(size)) {

                Value* comp_value = fBuilder->CreateFCmp((llvm::CmpInst::Predicate)gBinOpTable[comparator]->fLlvmFloatInst, arg1, arg2);
                //return fBuilder->CreateSelect(comp_value, arg1, arg2);
                return generateScalarSelect(comparator, comp_value, arg1, arg2, size);

            } else if (arg1->getType() == getDoubleTy(size) && arg2->getType() == getInt32Ty(size)) {

                // Generates cast arg2 to double
                Value* cast_value = fBuilder->CreateSIToFP(arg2, getDoubleTy(size));
                Value* comp_value = fBuilder->CreateFCmp((llvm::CmpInst::Predicate)gBinOpTable[comparator]->fLlvmFloatInst, arg1, cast_value);
                //return fBuilder->CreateSelect(comp_value, arg1, cast_value);
                return generateScalarSelect(comparator, comp_value, arg1, cast_value, size);

            } else if (arg1->getType() == getInt32Ty(size) && arg2->getType() == getFloatTy(size)) {

                // Generates cast arg1 to float
                Value* cast_value = fBuilder->CreateSIToFP(arg1, getFloatTy(size));
                Value* comp_value = fBuilder->CreateFCmp((llvm::CmpInst::Predicate)gBinOpTable[comparator]->fLlvmFloatInst, cast_value, arg2);
                //return fBuilder->CreateSelect(comp_value, cast_value, arg2);
                return generateScalarSelect(comparator, comp_value, cast_value, arg2, size);

            } else if (arg1->getType() == getInt32Ty(size) && arg2->getType() == getDoubleTy(size)) {

                // Generates cast arg1 to double
                Value* cast_value = fBuilder->CreateSIToFP(arg1, getDoubleTy(size));
                Value* comp_value = fBuilder->CreateFCmp((llvm::CmpInst::Predicate)gBinOpTable[comparator]->fLlvmFloatInst, cast_value, arg2);
                //return fBuilder->CreateSelect(comp_value, cast_value, arg2);
                return generateScalarSelect(comparator, comp_value, cast_value, arg2, size);

            } else if (arg1->getType() == getInt32Ty(size) && arg2->getType() == getInt32Ty(size)) {

                Value* comp_value = fBuilder->CreateICmp((llvm::CmpInst::Predicate)gBinOpTable[comparator]->fLlvmIntInst, arg1, arg2);
                //return fBuilder->CreateSelect(comp_value, arg1, arg2);
                return generateScalarSelect(comparator, comp_value, arg1, arg2, size);

             } else {
                // Should not happen
                cerr << "generateFunMinMaxAux" << endl;
                //arg1->getType()->dump();
                //arg2->getType()->dump();
                assert(false);
                return NULL;
            }
        }

};

#endif
