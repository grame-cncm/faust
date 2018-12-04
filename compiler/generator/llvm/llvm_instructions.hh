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

#ifndef _LLVM_INSTRUCTIONS_H
#define _LLVM_INSTRUCTIONS_H

#ifdef WIN32
#pragma warning(disable : 4624 4291 4141)
#endif

#include <list>
#include <map>
#include <set>
#include <string>

#include "Text.hh"
#include "binop.hh"
#include "exception.hh"
#include "fir_to_fir.hh"
#include "global.hh"
#include "instructions.hh"

#if defined(LLVM_35) || defined(LLVM_38)
#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS
#endif

#include <llvm-c/BitWriter.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Transforms/Scalar.h>

#if defined(LLVM_40) || defined(LLVM_50) || defined(LLVM_60) || defined(LLVM_70) || defined(LLVM_80)
#include <llvm/Bitcode/BitcodeReader.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#else
#include <llvm/Bitcode/ReaderWriter.h>
#endif

#if defined(_WIN32) && defined(LLVM_MEM)
#define LLVM_CALLOC "llvm_calloc"
#define LLVM_FREE "llvm_free"
#else
#define LLVM_CALLOC "calloc"
#define LLVM_FREE "free"
#endif

#define GET_ITERATOR(it) &(*(it))
#define VECTOR_OF_TYPES vector<llvm::Type*>
#define MAP_OF_TYPES std::map<Typed::VarType, llvm::Type*>
#define LLVM_TYPE llvm::Type*
#define MAKE_VECTOR_OF_TYPES(vec) makeArrayRef(vec)
#define MAKE_IXD(beg, end) llvm::ArrayRef<llvm::Value*>(beg, end)
#define MAKE_ARGS(args) llvm::ArrayRef<llvm::Value*>(args)
#define CREATE_CALL(fun, args) fBuilder->CreateCall(fun, MAKE_VECTOR_OF_TYPES(args))
#define CREATE_CALL1(fun, args, str, block) CallInst::Create(fun, MAKE_VECTOR_OF_TYPES(args), str, block)
#define CREATE_PHI(type, name) fBuilder->CreatePHI(type, 0, name);
#define VECTOR_ALIGN 0

using namespace llvm;

typedef llvm::Value* LLVMValue;

#define dumpLLVM(val)                            \
    {                                            \
        string             res;                  \
        raw_string_ostream out_str(res);         \
        out_str << *val;                         \
        std::cout << out_str.str() << std::endl; \
    }

// Helper class

struct LLVMTypeHelper {
    MAP_OF_TYPES fTypeMap;

    LLVMTypeHelper() {}

    void initTypes(Module* module)
    {
        // LLVM type coding
        fTypeMap[Typed::kFloat]         = llvm::Type::getFloatTy(module->getContext());
        fTypeMap[Typed::kFloat_ptr]     = PointerType::get(fTypeMap[Typed::kFloat], 0);
        fTypeMap[Typed::kFloat_ptr_ptr] = PointerType::get(fTypeMap[Typed::kFloat_ptr], 0);
        fTypeMap[Typed::kFloat_vec]     = VectorType::get(fTypeMap[Typed::kFloat], gGlobal->gVecSize);
        fTypeMap[Typed::kFloat_vec_ptr] = PointerType::get(fTypeMap[Typed::kFloat_vec], 0);

        fTypeMap[Typed::kInt32]         = llvm::Type::getInt32Ty(module->getContext());
        fTypeMap[Typed::kInt32_ptr]     = PointerType::get(fTypeMap[Typed::kInt32], 0);
        fTypeMap[Typed::kInt32_vec]     = VectorType::get(fTypeMap[Typed::kInt32], gGlobal->gVecSize);
        fTypeMap[Typed::kInt32_vec_ptr] = PointerType::get(fTypeMap[Typed::kInt32_vec], 0);

        fTypeMap[Typed::kInt64]         = llvm::Type::getInt64Ty(module->getContext());
        fTypeMap[Typed::kInt64_ptr]     = PointerType::get(fTypeMap[Typed::kInt64], 0);
        fTypeMap[Typed::kInt64_vec]     = VectorType::get(fTypeMap[Typed::kInt64], gGlobal->gVecSize);
        fTypeMap[Typed::kInt64_vec_ptr] = PointerType::get(fTypeMap[Typed::kInt64_vec], 0);

        fTypeMap[Typed::kDouble]         = llvm::Type::getDoubleTy(module->getContext());
        fTypeMap[Typed::kDouble_ptr]     = PointerType::get(fTypeMap[Typed::kDouble], 0);
        fTypeMap[Typed::kDouble_ptr_ptr] = PointerType::get(fTypeMap[Typed::kDouble_ptr], 0);
        fTypeMap[Typed::kDouble_vec]     = VectorType::get(fTypeMap[Typed::kDouble], gGlobal->gVecSize);
        fTypeMap[Typed::kDouble_vec_ptr] = PointerType::get(fTypeMap[Typed::kDouble_vec], 0);

        fTypeMap[Typed::kBool]         = llvm::Type::getInt1Ty(module->getContext());
        fTypeMap[Typed::kBool_ptr]     = PointerType::get(fTypeMap[Typed::kBool], 0);
        fTypeMap[Typed::kBool_vec]     = VectorType::get(fTypeMap[Typed::kBool], gGlobal->gVecSize);
        fTypeMap[Typed::kBool_vec_ptr] = PointerType::get(fTypeMap[Typed::kBool_vec], 0);

        // Takes the type of internal real
        fTypeMap[Typed::kFloatMacro]         = fTypeMap[itfloat()];
        fTypeMap[Typed::kFloatMacro_ptr]     = PointerType::get(fTypeMap[Typed::kFloatMacro], 0);
        fTypeMap[Typed::kFloatMacro_ptr_ptr] = PointerType::get(fTypeMap[Typed::kFloatMacro_ptr], 0);

        fTypeMap[Typed::kVoid] = llvm::Type::getVoidTy(module->getContext());

        // void* must be defined as i8* type
        fTypeMap[Typed::kVoid_ptr]     = PointerType::get(llvm::Type::getInt8Ty(module->getContext()), 0);
        fTypeMap[Typed::kVoid_ptr_ptr] = PointerType::get(fTypeMap[Typed::kVoid_ptr], 0);

        // External structured type definition
        map<Typed::VarType, DeclareStructTypeInst*>::const_iterator it;
        for (it = gGlobal->gExternalStructTypes.begin(); it != gGlobal->gExternalStructTypes.end(); it++) {
            LLVM_TYPE new_type    = convertFIRType(module, ((*it).second)->fType);
            fTypeMap[(*it).first] = new_type;
            faustassert(Typed::getPtrFromType((*it).first));
            fTypeMap[Typed::getPtrFromType((*it).first)] = PointerType::get(new_type, 0);
        }
    }

    virtual ~LLVMTypeHelper() {}

    static LLVMValue genInt1(Module* module, int num)
    {
        return ConstantInt::get(llvm::Type::getInt1Ty(module->getContext()), num);
    }

    static LLVMValue genInt32(Module* module, int num)
    {
        return ConstantInt::get(llvm::Type::getInt32Ty(module->getContext()), num);
    }

    static LLVMValue genInt64(Module* module, long long num)
    {
        return ConstantInt::get(llvm::Type::getInt64Ty(module->getContext()), num);
    }

    static LLVMValue genFloat(Module* module, float num) { return ConstantFP::get(module->getContext(), APFloat(num)); }

    static LLVMValue genDouble(Module* module, double num)
    {
        return ConstantFP::get(module->getContext(), APFloat(num));
    }

    static LLVM_TYPE getFloatTy(Module* module) { return llvm::Type::getFloatTy(module->getContext()); }

    static LLVM_TYPE getInt32Ty(Module* module) { return llvm::Type::getInt32Ty(module->getContext()); }

    static LLVM_TYPE getInt64Ty(Module* module) { return llvm::Type::getInt64Ty(module->getContext()); }

    static LLVM_TYPE getInt1Ty(Module* module) { return llvm::Type::getInt1Ty(module->getContext()); }

    static LLVM_TYPE getDoubleTy(Module* module) { return llvm::Type::getDoubleTy(module->getContext()); }

    // Convert FIR types to LLVM types
    LLVM_TYPE convertFIRType(Module* module, Typed* type)
    {
        BasicTyped*  basic_typed  = dynamic_cast<BasicTyped*>(type);
        NamedTyped*  named_typed  = dynamic_cast<NamedTyped*>(type);
        ArrayTyped*  array_typed  = dynamic_cast<ArrayTyped*>(type);
        VectorTyped* vector_typed = dynamic_cast<VectorTyped*>(type);
        StructTyped* struct_typed = dynamic_cast<StructTyped*>(type);

        if (basic_typed) {
            return fTypeMap[basic_typed->fType];
        } else if (named_typed) {
            LLVM_TYPE type = module->getTypeByName("struct.dsp" + named_typed->fName);
            // Subcontainer type (RWTable...)
            return (type) ? PointerType::get(type, 0) : convertFIRType(module, named_typed->fType);
        } else if (array_typed) {
            // Arrays of 0 size are actually pointers on the type
            return (array_typed->fSize == 0)
                       ? fTypeMap[array_typed->getType()]
                       : ArrayType::get(fTypeMap[Typed::getTypeFromPtr(array_typed->getType())], array_typed->fSize);
        } else if (vector_typed) {
            return VectorType::get(fTypeMap[vector_typed->fType->fType], vector_typed->fSize);
        } else if (struct_typed) {
            VECTOR_OF_TYPES                     llvm_types;
            vector<NamedTyped*>::const_iterator it;
            for (it = struct_typed->fFields.begin(); it != struct_typed->fFields.end(); it++) {
                llvm_types.push_back(convertFIRType(module, *it));
            }
            return createStructType(module, "struct.dsp" + struct_typed->fName, llvm_types);
        } else {
            faustassert(false);
            return nullptr;
        }
    }

    static llvm::StructType* createStructType(Module* module, string name, VECTOR_OF_TYPES types)
    {
        // We want to have a unique creation for struct types: check if the given type has already been created
        StructType* struct_type = module->getTypeByName(name);
        if (!struct_type) {
            StructType* struct_type1 = StructType::create(module->getContext(), name);
            // Create "packed" struct type to match the size of C++ "packed" defined ones
            struct_type1->setBody(MAKE_VECTOR_OF_TYPES(types), true);
            return struct_type1;
        } else {
            return struct_type;
        }
    }
};

class LLVMTypeInstVisitor : public DispatchVisitor, public LLVMTypeHelper {
   protected:
    Module*      fModule;
    IRBuilder<>* fBuilder;

    // DSP struct size in bytes
    int fSize;

    // DSP structure creation
    std::map<string, int> fDSPFieldsNames;    // map of field names and indexes
    VECTOR_OF_TYPES       fDSPFields;         // vector of LLVM types (for each field)
    int                   fDSPFieldsCounter;  // fields counter

    string      fPrefix;
    DataLayout* fDataLayout;

    // Meta structure creation
    llvm::PointerType* fStructMetaPtr;

    // UI structure creation
    llvm::PointerType* fStructUIPtr;
    LLVMValue          fUIInterfacePtr;

    virtual void generateFreeDsp(llvm::PointerType* dsp_type_ptr, bool internal)
    {
        // free
        PointerType* free_ptr = PointerType::get(fBuilder->getInt8Ty(), 0);

        VECTOR_OF_TYPES free_args;
        free_args.push_back(free_ptr);
        FunctionType* free_type = FunctionType::get(fBuilder->getVoidTy(), MAKE_VECTOR_OF_TYPES(free_args), false);

        Function* func_free = nullptr;
        if (!fModule->getFunction(LLVM_FREE)) {
            func_free = Function::Create(free_type, GlobalValue::ExternalLinkage, LLVM_FREE, fModule);
            func_free->setCallingConv(CallingConv::C);
        } else {
            func_free = fModule->getFunction(LLVM_FREE);
        }

        // Generates llvm_free_dsp
        VECTOR_OF_TYPES llvm_free_dsp_args;
        llvm_free_dsp_args.push_back(dsp_type_ptr);
        FunctionType* llvm_free_dsp_type =
            FunctionType::get(fBuilder->getVoidTy(), MAKE_VECTOR_OF_TYPES(llvm_free_dsp_args), false);

        Function* func_llvm_free_dsp =
            Function::Create(llvm_free_dsp_type, (internal) ? Function::InternalLinkage : Function::ExternalLinkage,
                             "delete" + fPrefix, fModule);
        func_llvm_free_dsp->setCallingConv(CallingConv::C);

        // llvm_free_dsp block
        Function::arg_iterator args = func_llvm_free_dsp->arg_begin();
        Value*                 dsp  = GET_ITERATOR(args++);

        dsp->setName("dsp");

        BasicBlock*  entry_func_llvm_free_dsp = BasicBlock::Create(fModule->getContext(), "entry", func_llvm_free_dsp);
        Instruction* inst2 =
            new BitCastInst(dsp, PointerType::get(fBuilder->getInt8Ty(), 0), "", entry_func_llvm_free_dsp);

        CallInst* call_inst0 = CallInst::Create(func_free, inst2, "", entry_func_llvm_free_dsp);
        call_inst0->setCallingConv(CallingConv::C);

        ReturnInst::Create(fModule->getContext(), entry_func_llvm_free_dsp);
        verifyFunction(*func_llvm_free_dsp);
        fBuilder->ClearInsertionPoint();
    }

    void generateMemory(llvm::StructType* dsp_type, llvm::PointerType* dsp_type_ptr, bool internal)
    {
        // malloc
        PointerType*    calloc_ptr = PointerType::get(fBuilder->getInt8Ty(), 0);
        VECTOR_OF_TYPES calloc_args;
        calloc_args.push_back(llvm::Type::getInt64Ty(fModule->getContext()));
        calloc_args.push_back(llvm::Type::getInt64Ty(fModule->getContext()));
        FunctionType* calloc_type = FunctionType::get(calloc_ptr, MAKE_VECTOR_OF_TYPES(calloc_args), false);

        Function* func_calloc = nullptr;
        if (!fModule->getFunction(LLVM_CALLOC)) {
            func_calloc = Function::Create(calloc_type, GlobalValue::ExternalLinkage, LLVM_CALLOC, fModule);
            func_calloc->setCallingConv(CallingConv::C);
        } else {
            func_calloc = fModule->getFunction(LLVM_CALLOC);
        }

        VECTOR_OF_TYPES allocate_args;
        allocate_args.push_back(dsp_type_ptr);
        FunctionType* allocate_type =
            FunctionType::get(fBuilder->getVoidTy(), MAKE_VECTOR_OF_TYPES(allocate_args), false);

        Function* func_allocate = nullptr;
        // Only for global object
        if (!internal) {
            if (!fModule->getFunction("allocate" + fPrefix)) {
                func_allocate =
                    Function::Create(allocate_type, Function::ExternalLinkage, "allocate" + fPrefix, fModule);
                func_allocate->setCallingConv(CallingConv::C);
                func_allocate->setAlignment(2);
                Function::arg_iterator llvm_allocate_args_it = func_allocate->arg_begin();
                Value*                 dsp                   = GET_ITERATOR(llvm_allocate_args_it++);
                dsp->setName("dsp");
            } else {
                func_allocate = fModule->getFunction("allocate" + fPrefix);
            }
        }

        // llvm_create_dsp
        VECTOR_OF_TYPES llvm_create_dsp_args;
        FunctionType*   llvm_create_dsp_type =
            FunctionType::get(dsp_type_ptr, MAKE_VECTOR_OF_TYPES(llvm_create_dsp_args), false);
        Function* func_llvm_create_dsp = Function::Create(
            llvm_create_dsp_type, (internal) ? GlobalValue::InternalLinkage : GlobalValue::ExternalLinkage,
            "new" + fPrefix, fModule);
        func_llvm_create_dsp->setCallingConv(CallingConv::C);

        // llvm_create_dsp block
        BasicBlock* entry_func_llvm_create_dsp =
            BasicBlock::Create(fModule->getContext(), "entry", func_llvm_create_dsp);

        vector<LLVMValue> calloc_fun_args;
        calloc_fun_args.push_back(genInt64(fModule, 1));
        calloc_fun_args.push_back(genInt64(fModule, fSize));

        llvm::CallInst* call_inst1 = CREATE_CALL1(func_calloc, calloc_fun_args, "", entry_func_llvm_create_dsp);
        call_inst1->setCallingConv(CallingConv::C);
        llvm::CastInst* call_inst2 = new BitCastInst(call_inst1, dsp_type_ptr, "", entry_func_llvm_create_dsp);

        // Only for global object
        if (!internal) {
            llvm::CallInst* call_inst3 = CallInst::Create(func_allocate, call_inst2, "", entry_func_llvm_create_dsp);
            call_inst3->setCallingConv(CallingConv::C);
        }

        ReturnInst::Create(fModule->getContext(), call_inst2, entry_func_llvm_create_dsp);
        verifyFunction(*func_llvm_create_dsp);
        fBuilder->ClearInsertionPoint();
    }

    void generateMetaGlue()
    {
        // Struct Meta
        VECTOR_OF_TYPES fStructTy_struct_Meta_fields;
        PointerType*    PointerTy_0 = PointerType::get(IntegerType::get(fModule->getContext(), 8), 0);

        fStructTy_struct_Meta_fields.push_back(PointerTy_0);

        // Declare fun
        VECTOR_OF_TYPES FuncTy_2_args;
        FuncTy_2_args.push_back(PointerTy_0);
        FuncTy_2_args.push_back(PointerTy_0);
        FuncTy_2_args.push_back(PointerTy_0);
        FunctionType* FuncTy_2 = FunctionType::get(
            /*Result=*/llvm::Type::getVoidTy(fModule->getContext()),
            /*Params=*/MAKE_VECTOR_OF_TYPES(FuncTy_2_args),
            /*isVarArg=*/false);

        PointerType* PointerTy_1 = PointerType::get(FuncTy_2, 0);

        fStructTy_struct_Meta_fields.push_back(PointerTy_1);

        StructType* fStructTy_struct_Meta =
            LLVMTypeHelper::createStructType(fModule, "struct.MetaGlue", fStructTy_struct_Meta_fields);
        fStructMetaPtr = PointerType::get(fStructTy_struct_Meta, 0);
    }

    void generateUIGlue()
    {
        // Type Definitions
        VECTOR_OF_TYPES StructTy_struct_UIGlue_fields;
        PointerType*    PointerTy_0 = PointerType::get(IntegerType::get(fModule->getContext(), 8), 0);

        // uiInterface;
        StructTy_struct_UIGlue_fields.push_back(PointerTy_0);

        // Declare fun
        VECTOR_OF_TYPES FuncTy_2_args;
        FuncTy_2_args.push_back(PointerTy_0);
        FuncTy_2_args.push_back(PointerTy_0);
        FunctionType* FuncTy_2 = FunctionType::get(
            /*Result=*/llvm::Type::getVoidTy(fModule->getContext()),
            /*Params=*/MAKE_VECTOR_OF_TYPES(FuncTy_2_args),
            /*isVarArg=*/false);

        PointerType* PointerTy_1 = PointerType::get(FuncTy_2, 0);

        // openTabBoxFun/openHorizontalBoxFun/openVerticalBoxFun
        StructTy_struct_UIGlue_fields.push_back(PointerTy_1);
        StructTy_struct_UIGlue_fields.push_back(PointerTy_1);
        StructTy_struct_UIGlue_fields.push_back(PointerTy_1);

        VECTOR_OF_TYPES FuncTy_4_args;
        FuncTy_4_args.push_back(PointerTy_0);
        FunctionType* FuncTy_4 = FunctionType::get(
            /*Result=*/llvm::Type::getVoidTy(fModule->getContext()),
            /*Params=*/MAKE_VECTOR_OF_TYPES(FuncTy_4_args),
            /*isVarArg=*/false);

        PointerType* PointerTy_3 = PointerType::get(FuncTy_4, 0);

        // closeBoxFun
        StructTy_struct_UIGlue_fields.push_back(PointerTy_3);

        VECTOR_OF_TYPES FuncTy_6_args;
        FuncTy_6_args.push_back(PointerTy_0);
        FuncTy_6_args.push_back(PointerTy_0);
        LLVM_TYPE PointerTy_7 = fTypeMap[itfloatptr()];  // LLVM internal float is same as external

        FuncTy_6_args.push_back(PointerTy_7);
        FunctionType* FuncTy_6 = FunctionType::get(
            /*Result=*/llvm::Type::getVoidTy(fModule->getContext()),
            /*Params=*/MAKE_VECTOR_OF_TYPES(FuncTy_6_args),
            /*isVarArg=*/false);

        PointerType* PointerTy_5 = PointerType::get(FuncTy_6, 0);

        // addButtonFun/addCheckButtonFun
        StructTy_struct_UIGlue_fields.push_back(PointerTy_5);
        StructTy_struct_UIGlue_fields.push_back(PointerTy_5);

        VECTOR_OF_TYPES FuncTy_9_args;
        FuncTy_9_args.push_back(PointerTy_0);
        FuncTy_9_args.push_back(PointerTy_0);
        FuncTy_9_args.push_back(PointerTy_7);
        FuncTy_9_args.push_back(fTypeMap[itfloat()]);  // For internal float is same as external
        FuncTy_9_args.push_back(fTypeMap[itfloat()]);
        FuncTy_9_args.push_back(fTypeMap[itfloat()]);
        FuncTy_9_args.push_back(fTypeMap[itfloat()]);
        FunctionType* FuncTy_9 = FunctionType::get(
            /*Result=*/llvm::Type::getVoidTy(fModule->getContext()),
            /*Params=*/MAKE_VECTOR_OF_TYPES(FuncTy_9_args),
            /*isVarArg=*/false);

        PointerType* PointerTy_8 = PointerType::get(FuncTy_9, 0);

        // addVerticalSliderFun/addHorizontalSliderFun/addNumEntryFun
        StructTy_struct_UIGlue_fields.push_back(PointerTy_8);
        StructTy_struct_UIGlue_fields.push_back(PointerTy_8);
        StructTy_struct_UIGlue_fields.push_back(PointerTy_8);

        VECTOR_OF_TYPES FuncTy_16_args;
        FuncTy_16_args.push_back(PointerTy_0);
        FuncTy_16_args.push_back(PointerTy_0);
        FuncTy_16_args.push_back(PointerTy_7);
        FuncTy_16_args.push_back(fTypeMap[itfloat()]);  // LLVM internal float is same as external
        FuncTy_16_args.push_back(fTypeMap[itfloat()]);
        FunctionType* FuncTy_16 = FunctionType::get(
            /*Result=*/llvm::Type::getVoidTy(fModule->getContext()),
            /*Params=*/MAKE_VECTOR_OF_TYPES(FuncTy_16_args),
            /*isVarArg=*/false);

        PointerType* PointerTy_15 = PointerType::get(FuncTy_16, 0);

        // addHorizontalBargraphFun/addVerticalBargraphFun
        StructTy_struct_UIGlue_fields.push_back(PointerTy_15);
        StructTy_struct_UIGlue_fields.push_back(PointerTy_15);

        VECTOR_OF_TYPES FuncTy_19_args;
        FuncTy_19_args.push_back(PointerTy_0);
        FuncTy_19_args.push_back(PointerTy_0);
        FuncTy_19_args.push_back(PointerTy_0);
        FuncTy_19_args.push_back(PointerType::get(fTypeMap[Typed::kSound_ptr], 0));
        FunctionType* FuncTy_19 = FunctionType::get(
            /*Result=*/llvm::Type::getVoidTy(fModule->getContext()),
            /*Params=*/MAKE_VECTOR_OF_TYPES(FuncTy_19_args),
            /*isVarArg=*/false);

        PointerType* PointerTy_20 = PointerType::get(FuncTy_19, 0);

        // addSoundFileFun
        StructTy_struct_UIGlue_fields.push_back(PointerTy_20);

        VECTOR_OF_TYPES FuncTy_18_args;
        FuncTy_18_args.push_back(PointerTy_0);
        FuncTy_18_args.push_back(PointerTy_7);
        FuncTy_18_args.push_back(PointerTy_0);
        FuncTy_18_args.push_back(PointerTy_0);
        FunctionType* FuncTy_18 = FunctionType::get(
            /*Result=*/llvm::Type::getVoidTy(fModule->getContext()),
            /*Params=*/MAKE_VECTOR_OF_TYPES(FuncTy_18_args),
            /*isVarArg=*/false);

        PointerType* PointerTy_17 = PointerType::get(FuncTy_18, 0);

        // declareFun
        StructTy_struct_UIGlue_fields.push_back(PointerTy_17);

        llvm::StructType* struct_ui =
            LLVMTypeHelper::createStructType(fModule, "struct.UIGlue", StructTy_struct_UIGlue_fields);

        // dumpLLVM(fStructUI);

        fStructUIPtr = PointerType::get(struct_ui, 0);
    }

    void generateBuildUserInterface(llvm::PointerType* dsp_type_ptr)
    {
        // Creates llvm_buildUserInterface function
        VECTOR_OF_TYPES llvm_buildUserInterface_args;
        llvm_buildUserInterface_args.push_back(dsp_type_ptr);
        llvm_buildUserInterface_args.push_back(fStructUIPtr);
        FunctionType* llvm_buildUserInterface_type =
            FunctionType::get(fBuilder->getVoidTy(), MAKE_VECTOR_OF_TYPES(llvm_buildUserInterface_args), false);

        Function* llvm_buildUserInterface = Function::Create(llvm_buildUserInterface_type, GlobalValue::ExternalLinkage,
                                                             "buildUserInterface" + fPrefix, fModule);
        llvm_buildUserInterface->setCallingConv(CallingConv::C);
        llvm_buildUserInterface->setAlignment(2);

        // Name arguments
        Function::arg_iterator func_llvm_buildUserInterface_args_it = llvm_buildUserInterface->arg_begin();
        Value*                 dsp = GET_ITERATOR(func_llvm_buildUserInterface_args_it++);
        dsp->setName("dsp");
        Value* interface1 = GET_ITERATOR(func_llvm_buildUserInterface_args_it++);
        interface1->setName("interface");

        // Create init block
        BasicBlock* init_block = BasicBlock::Create(fModule->getContext(), "init", llvm_buildUserInterface);
        fBuilder->SetInsertPoint(init_block);

        // Genererates access to "interface" pointer just once
        Value* idx[2];
        idx[0]          = genInt64(fModule, 0);
        idx[1]          = genInt32(fModule, 0);
        Value* ui_ptr   = fBuilder->CreateInBoundsGEP(interface1, MAKE_IXD(idx, idx + 2));
        fUIInterfacePtr = fBuilder->CreateLoad(ui_ptr);
    }

   public:
    LLVMTypeInstVisitor(Module* module, const string& prefix = "")
        : fModule(module), fDSPFieldsCounter(0), fPrefix(prefix)
    {
        fSize    = -1;
        fBuilder = new IRBuilder<>(fModule->getContext());

        initTypes(module);
#if defined(LLVM_35)
        fDataLayout = new DataLayout(*module->getDataLayout());
#else
        fDataLayout = new DataLayout(module->getDataLayout());
#endif
        // dumpLLVM(fDataLayout);
    }

    virtual ~LLVMTypeInstVisitor()
    {
        // External object not covered by Garbageable, so delete it here
        delete fBuilder;
        delete fDataLayout;
    }

    int getSize() { return fSize; }

    virtual void visit(DeclareVarInst* inst)
    {
        // Not supposed to declare var with value here
        faustassert(inst->fValue == nullptr);
        fDSPFields.push_back(convertFIRType(fModule, inst->fType));
        fDSPFieldsNames[inst->fAddress->getName()] = fDSPFieldsCounter++;
    }

    virtual void visit(DeclareFunInst* inst)
    {
        Function* function = fModule->getFunction(inst->fName);

        if (!function) {  // Define it

            // Return type
            LLVM_TYPE return_type = fTypeMap[inst->fType->fResult->getType()];

            // Prepare vector of LLVM types for args
            VECTOR_OF_TYPES                   fun_args_type;
            list<NamedTyped*>::const_iterator it;
            for (it = inst->fType->fArgsTypes.begin(); it != inst->fType->fArgsTypes.end(); it++) {
                fun_args_type.push_back(fTypeMap[(*it)->getType()]);
            }

            // Creates function
            FunctionType* fun_type = FunctionType::get(return_type, MAKE_VECTOR_OF_TYPES(fun_args_type), false);
            function               = Function::Create(fun_type, GlobalValue::ExternalLinkage, inst->fName, fModule);
            function->setCallingConv(CallingConv::C);

            // Set name for function arguments
            Function::arg_iterator args = function->arg_begin();
            for (it = inst->fType->fArgsTypes.begin(); it != inst->fType->fArgsTypes.end(); it++) {
                Value* llvm_arg = GET_ITERATOR(args++);
                llvm_arg->setName((*it)->fName);
            }
        }

        // If there is a body, compile it
        if (inst->fCode->fCode.size() > 0) {
            // Prepare a block to insert into
            BasicBlock* code_block = BasicBlock::Create(fModule->getContext(), "code_block", function);
            fBuilder->SetInsertPoint(code_block);

            // Compile code in this block
            inst->fCode->accept(this);
            verifyFunction(*function);
            fBuilder->ClearInsertionPoint();
        }
    }

    void generateSetDefaultSound()
    {
        VECTOR_OF_TYPES llvm_setDefault_args;
        llvm_setDefault_args.push_back(fTypeMap[Typed::kSound_ptr]);  // TODO
        FunctionType* llvm_setDefault_type =
            FunctionType::get(fBuilder->getVoidTy(), MAKE_VECTOR_OF_TYPES(llvm_setDefault_args), false);

        Function* llvm_setDefault =
            Function::Create(llvm_setDefault_type, Function::ExternalLinkage, "setDefaultSound" + fPrefix, fModule);
        llvm_setDefault->setCallingConv(CallingConv::C);

        Function::arg_iterator llvm_setDefault_args_it = llvm_setDefault->arg_begin();
        Value*                 arg1                    = GET_ITERATOR(llvm_setDefault_args_it++);
        arg1->setName("default_sound");

        BasicBlock* entry_block = BasicBlock::Create(fModule->getContext(), "entry_block", llvm_setDefault);
        fBuilder->SetInsertPoint(entry_block);

        // Set global 'defaultsound' variable

        LLVMValue defaultsound = fModule->getGlobalVariable("defaultsound", true);
        faustassert(defaultsound);
        fBuilder->CreateStore(arg1, defaultsound);

        ReturnInst::Create(fModule->getContext(), entry_block);
        verifyFunction(*llvm_setDefault);
    }

    llvm::PointerType* getDSPType(bool internal, bool generate_ui = true)
    {
        llvm::StructType*  dsp_type     = LLVMTypeHelper::createStructType(fModule, "struct.dsp" + fPrefix, fDSPFields);
        llvm::PointerType* dsp_type_ptr = PointerType::get(dsp_type, 0);

        fSize = fDataLayout->getTypeSizeInBits(dsp_type) / 8;

        // Create llvm_free_dsp function
        generateFreeDsp(dsp_type_ptr, internal);

        // Creates DSP free/delete functions
        generateMemory(dsp_type, dsp_type_ptr, internal);

        // Struct Meta
        generateMetaGlue();

        // Struct UI
        generateUIGlue();

        // prepare llvm_buildUserInterface
        if (generate_ui) {
            generateBuildUserInterface(dsp_type_ptr);
        }

        // dumpLLVM(dsp_type);
        return dsp_type_ptr;
    }

    llvm::PointerType* getUIType() { return fStructUIPtr; }

    llvm::PointerType* getMetaType() { return fStructMetaPtr; }

    LLVMValue getUIPtr() { return fUIInterfacePtr; }

    std::map<string, int> getFieldNames() { return fDSPFieldsNames; }
};

// Special version for DSP code (add call to "destroy" function)

class LLVMTypeInstVisitor1 : public LLVMTypeInstVisitor {
   protected:
    void generateFreeDsp(llvm::PointerType* dsp_type_ptr, bool internal)
    {
        // free
        PointerType*    free_ptr = PointerType::get(fBuilder->getInt8Ty(), 0);
        VECTOR_OF_TYPES free_args;
        free_args.push_back(free_ptr);
        FunctionType* free_type = FunctionType::get(fBuilder->getVoidTy(), MAKE_VECTOR_OF_TYPES(free_args), false);

        Function* func_free = nullptr;
        if (!fModule->getFunction(LLVM_FREE)) {
            func_free = Function::Create(free_type, GlobalValue::ExternalLinkage, LLVM_FREE, fModule);
            func_free->setCallingConv(CallingConv::C);
            func_free->setAlignment(2);
        } else {
            func_free = fModule->getFunction(LLVM_FREE);
        }

        VECTOR_OF_TYPES destroy_args;
        destroy_args.push_back(dsp_type_ptr);
        FunctionType* destroy_type =
            FunctionType::get(fBuilder->getVoidTy(), MAKE_VECTOR_OF_TYPES(destroy_args), false);

        Function* func_destroy = nullptr;
        if (!fModule->getFunction("destroy" + fPrefix)) {
            func_destroy = Function::Create(destroy_type, Function::ExternalLinkage, "destroy" + fPrefix, fModule);
            func_destroy->setCallingConv(CallingConv::C);
            func_destroy->setAlignment(2);
            Function::arg_iterator llvm_destroy_args_it = func_destroy->arg_begin();
            Value*                 dsp                  = GET_ITERATOR(llvm_destroy_args_it++);
            dsp->setName("dsp");
        } else {
            func_destroy = fModule->getFunction("destroy" + fPrefix);
        }

        // Generates llvm_free_dsp
        VECTOR_OF_TYPES llvm_free_dsp_args;
        llvm_free_dsp_args.push_back(dsp_type_ptr);
        FunctionType* llvm_free_dsp_type =
            FunctionType::get(fBuilder->getVoidTy(), MAKE_VECTOR_OF_TYPES(llvm_free_dsp_args), false);
        Function* func_llvm_free_dsp =
            Function::Create(llvm_free_dsp_type, (internal) ? Function::InternalLinkage : Function::ExternalLinkage,
                             "delete" + fPrefix, fModule);
        func_llvm_free_dsp->setCallingConv(CallingConv::C);

        // llvm_free_dsp block
        Function::arg_iterator args = func_llvm_free_dsp->arg_begin();
        Value*                 dsp  = GET_ITERATOR(args++);
        dsp->setName("dsp");

        BasicBlock*  entry_func_llvm_free_dsp = BasicBlock::Create(fModule->getContext(), "entry", func_llvm_free_dsp);
        Instruction* inst2 =
            new BitCastInst(dsp, PointerType::get(fBuilder->getInt8Ty(), 0), "", entry_func_llvm_free_dsp);

        CallInst* call_inst1 = CallInst::Create(func_destroy, dsp, "", entry_func_llvm_free_dsp);
        call_inst1->setCallingConv(CallingConv::C);

        CallInst* call_inst0 = CallInst::Create(func_free, inst2, "", entry_func_llvm_free_dsp);
        call_inst0->setCallingConv(CallingConv::C);

        ReturnInst::Create(fModule->getContext(), entry_func_llvm_free_dsp);
        verifyFunction(*func_llvm_free_dsp);
        fBuilder->ClearInsertionPoint();
    }

   public:
    LLVMTypeInstVisitor1(Module* module, const string& prefix = "") : LLVMTypeInstVisitor(module, prefix) {}
};

// LLVM loop code generator

class LLVMInstVisitor : public InstVisitor, public LLVMTypeHelper {
   protected:
    Module*      fModule;
    IRBuilder<>* fBuilder;
    IRBuilder<>*
        fAllocaBuilder;  // To be used for "alloca", which have to be added in the first "entry" block of the function.

    map<string, LLVMValue> fUICallTable;

    // UI structure creation
    LLVMValue fUIInterfacePtr;  // Pointer on the UI

    std::map<string, int> fDSPFieldsNames;      // Computed by LLVMTypeInstVisitor, used to access the DSP struct fields
    std::map<string, LLVMValue> fDSPStackVars;  // Variables on the stack

    LLVMValue fCurValue;  // Current result of the compilation
    string    fPrefix;    // Prefix for function name

    map<string, GlobalVariable*> fGlobalStringTable;

    static list<string> gMathLibTable;

    LLVMValue genReal(double val)
    {
        return (itfloat() == Typed::kFloat) ? genFloat(fModule, val) : genDouble(fModule, val);
    }

   public:
    LLVMInstVisitor(Module* module, IRBuilder<>* builder, IRBuilder<>* alloca_builder,
                    const std::map<string, int>& field_names, LLVMValue ui_ptr, llvm::PointerType* dsp_ptr,
                    const string& prefix = "")
        : fModule(module),
          fBuilder(builder),
          fAllocaBuilder(alloca_builder),
          fUIInterfacePtr(ui_ptr),
          fDSPFieldsNames(field_names),
          fCurValue(nullptr),
          fPrefix(prefix)
    {
        // UI call table : indexes of method calls
        fUICallTable["openTabBox"]        = genInt32(fModule, 1);
        fUICallTable["openHorizontalBox"] = genInt32(fModule, 2);
        fUICallTable["openVerticalBox"]   = genInt32(fModule, 3);
        fUICallTable["closeBox"]          = genInt32(fModule, 4);

        fUICallTable["addButton"]           = genInt32(fModule, 5);
        fUICallTable["addCheckButton"]      = genInt32(fModule, 6);
        fUICallTable["addVerticalSlider"]   = genInt32(fModule, 7);
        fUICallTable["addHorizontalSlider"] = genInt32(fModule, 8);
        fUICallTable["addNumEntry"]         = genInt32(fModule, 9);

        fUICallTable["addHorizontalBargraph"] = genInt32(fModule, 10);
        fUICallTable["addVerticalBargraph"]   = genInt32(fModule, 11);

        fUICallTable["addSoundfile"] = genInt32(fModule, 12);

        fUICallTable["declare"] = genInt32(fModule, 13);

        fTypeMap[Typed::kObj_ptr] = dsp_ptr;

        initTypes(module);

        if (gMathLibTable.size()) {
            return;
        }

        // Integer version
        gMathLibTable.push_back("abs");

        // Float version
        gMathLibTable.push_back("fabsf");
        gMathLibTable.push_back("acosf");
        gMathLibTable.push_back("asinf");
        gMathLibTable.push_back("atanf");
        gMathLibTable.push_back("atan2f");
        gMathLibTable.push_back("ceilf");
        gMathLibTable.push_back("cosf");
        gMathLibTable.push_back("coshf");
        gMathLibTable.push_back("expf");
        gMathLibTable.push_back("exp10f");
        gMathLibTable.push_back("floorf");
        gMathLibTable.push_back("fmodf");
        gMathLibTable.push_back("logf");
        gMathLibTable.push_back("log10f");
        gMathLibTable.push_back("powf");
        gMathLibTable.push_back("roundf");
        gMathLibTable.push_back("sinf");
        gMathLibTable.push_back("sinhf");
        gMathLibTable.push_back("sqrtf");
        gMathLibTable.push_back("tanf");
        gMathLibTable.push_back("tanhf");

        // Double version
        gMathLibTable.push_back("fabs");
        gMathLibTable.push_back("acos");
        gMathLibTable.push_back("asin");
        gMathLibTable.push_back("atan");
        gMathLibTable.push_back("atan2");
        gMathLibTable.push_back("ceil");
        gMathLibTable.push_back("cos");
        gMathLibTable.push_back("cosh");
        gMathLibTable.push_back("exp");
        gMathLibTable.push_back("exp10");
        gMathLibTable.push_back("floor");
        gMathLibTable.push_back("fmod");
        gMathLibTable.push_back("log");
        gMathLibTable.push_back("log10");
        gMathLibTable.push_back("pow");
        gMathLibTable.push_back("round");
        gMathLibTable.push_back("sin");
        gMathLibTable.push_back("sinh");
        gMathLibTable.push_back("sqrt");
        gMathLibTable.push_back("tan");
        gMathLibTable.push_back("tanh");
    }

    LLVMInstVisitor(const string& prefix = "") : fBuilder(nullptr), fCurValue(nullptr), fPrefix(prefix) {}

    virtual ~LLVMInstVisitor() {}

    // User interface

    void printVarTable()
    {
        std::map<string, LLVMValue>::const_iterator it;
        for (it = fDSPStackVars.begin(); it != fDSPStackVars.end(); it++) {
            std::cout << "stack var = " << (*it).first << endl;
        }
    }

    GlobalVariable* addStringConstant(string arg, llvm::Type*& type_def)
    {
        string     str        = replaceChar(unquote(arg), '@', '_');
        ArrayType* array_type = ArrayType::get(fBuilder->getInt8Ty(), str.size() + 1);
        type_def              = array_type;

        if (fGlobalStringTable.find(str) == fGlobalStringTable.end()) {
            fGlobalStringTable[str] =
                new GlobalVariable(*fModule, array_type, true, GlobalValue::InternalLinkage, 0, str);
            fGlobalStringTable[str]->setInitializer(ConstantDataArray::getString(fModule->getContext(), str, true));
        }

        return fGlobalStringTable[str];
    }

    Value* getStringConstant(const string& label)
    {
        // Get LLVM constant string
        llvm::Type*     type_def  = 0;
        GlobalVariable* llvm_name = addStringConstant(label, type_def);
#if defined(LLVM_35)
        return fBuilder->CreateConstGEP2_32(llvm_name, 0, 0);
#else
        return fBuilder->CreateConstGEP2_32(type_def, llvm_name, 0, 0);
#endif
    }

    Value* loadArrayAsPointer(Value* variable, bool isvolatile = false)
    {
        Value*    load_ptr;
        LoadInst* tmp_load = new LoadInst(variable);

        if (isa<ArrayType>(tmp_load->getType())) {
            Value* idx[2];
            idx[0]   = genInt64(fModule, 0);
            idx[1]   = genInt64(fModule, 0);
            load_ptr = fBuilder->CreateInBoundsGEP(variable, MAKE_IXD(idx, idx + 2));
        } else {
            load_ptr = fBuilder->CreateLoad(variable, isvolatile);
        }
        delete tmp_load;
        return load_ptr;
    }

    // Visit methods for all instructions
    virtual void visit(AddMetaDeclareInst* inst)
    {
        Function*              llvm_buildUserInterface = fModule->getFunction("buildUserInterface" + fPrefix);
        Function::arg_iterator func_llvm_buildUserInterface_args_it = llvm_buildUserInterface->arg_begin();
        Value*                 dsp = GET_ITERATOR(func_llvm_buildUserInterface_args_it++);
        Value*                 ui  = GET_ITERATOR(func_llvm_buildUserInterface_args_it++);

        Value* idx[2];
        idx[0]            = genInt64(fModule, 0);
        idx[1]            = fUICallTable["declare"];
        Value*    mth_ptr = fBuilder->CreateInBoundsGEP(ui, MAKE_IXD(idx, idx + 2));
        LoadInst* mth     = fBuilder->CreateLoad(mth_ptr);

        // Get LLVM constant string
        llvm::Type*     type_def1  = 0;
        llvm::Type*     type_def2  = 0;
        GlobalVariable* llvm_key   = addStringConstant(inst->fKey, type_def1);
        GlobalVariable* llvm_value = addStringConstant(inst->fValue, type_def2);

#if defined(LLVM_35)
        Value* const_string1 = fBuilder->CreateConstGEP2_32(llvm_key, 0, 0);
        Value* const_string2 = fBuilder->CreateConstGEP2_32(llvm_value, 0, 0);
#else
        Value* const_string1 = fBuilder->CreateConstGEP2_32(type_def1, llvm_key, 0, 0);
        Value* const_string2 = fBuilder->CreateConstGEP2_32(type_def2, llvm_value, 0, 0);
#endif
        // Generates access to zone
        Value* zone_ptr;
        if (inst->fZone == "0") {
            zone_ptr = Constant::getNullValue((itfloat() == Typed::kFloat) ? fTypeMap[Typed::kFloat_ptr]
                                                                           : fTypeMap[Typed::kDouble_ptr]);
        } else {
            int field_index = fDSPFieldsNames[inst->fZone];
#if defined(LLVM_35)
            zone_ptr = fBuilder->CreateStructGEP(dsp, field_index);
#else
            zone_ptr = fBuilder->CreateStructGEP(0, dsp, field_index);
#endif
        }

        Value* idx2[4];
        idx2[0] = fUIInterfacePtr;
        idx2[1] = zone_ptr;
        idx2[2] = const_string1;
        idx2[3] = const_string2;

        CallInst* call_inst = fBuilder->CreateCall(mth, MAKE_IXD(idx2, idx2 + 4));
        call_inst->setCallingConv(CallingConv::C);
    }

    virtual void visit(OpenboxInst* inst)
    {
        Function*              llvm_buildUserInterface = fModule->getFunction("buildUserInterface" + fPrefix);
        Function::arg_iterator func_llvm_buildUserInterface_args_it = llvm_buildUserInterface->arg_begin();
        func_llvm_buildUserInterface_args_it++;
        Value* ui = GET_ITERATOR(func_llvm_buildUserInterface_args_it++);

        LLVMValue mth_index;
        switch (inst->fOrient) {
            case 0:
                mth_index = fUICallTable["openVerticalBox"];
                break;
            case 1:
                mth_index = fUICallTable["openHorizontalBox"];
                break;
            case 2:
                mth_index = fUICallTable["openTabBox"];
                break;
            default:
                stringstream error;
                error << "ERROR : in user interface generation" << inst->fOrient << endl;
                throw faustexception(error.str());
        }

        Value* idx[2];
        idx[0]               = genInt64(fModule, 0);
        idx[1]               = mth_index;
        Value*    mth_ptr    = fBuilder->CreateInBoundsGEP(ui, MAKE_IXD(idx, idx + 2));
        LoadInst* mth        = fBuilder->CreateLoad(mth_ptr);
        Value*    fun_args[] = {fUIInterfacePtr, getStringConstant(inst->fName)};
        CallInst* call_inst  = fBuilder->CreateCall(mth, fun_args);
        call_inst->setCallingConv(CallingConv::C);
    }

    virtual void visit(CloseboxInst* inst)
    {
        Function*              llvm_buildUserInterface = fModule->getFunction("buildUserInterface" + fPrefix);
        Function::arg_iterator func_llvm_buildUserInterface_args_it = llvm_buildUserInterface->arg_begin();
        func_llvm_buildUserInterface_args_it++;
        Value* ui = GET_ITERATOR(func_llvm_buildUserInterface_args_it++);

        Value* idx[2];
        idx[0]            = genInt64(fModule, 0);
        idx[1]            = fUICallTable["closeBox"];
        Value*    mth_ptr = fBuilder->CreateInBoundsGEP(ui, MAKE_IXD(idx, idx + 2));
        LoadInst* mth     = fBuilder->CreateLoad(mth_ptr);

        CallInst* call_inst = fBuilder->CreateCall(mth, fUIInterfacePtr);
        call_inst->setCallingConv(CallingConv::C);
    }

    void addGenericButton(const string& label, const string& zone, const string& button_type)
    {
        Function*              llvm_buildUserInterface = fModule->getFunction("buildUserInterface" + fPrefix);
        Function::arg_iterator func_llvm_buildUserInterface_args_it = llvm_buildUserInterface->arg_begin();
        Value*                 dsp = GET_ITERATOR(func_llvm_buildUserInterface_args_it++);
        Value*                 ui  = GET_ITERATOR(func_llvm_buildUserInterface_args_it++);

        Value* idx[2];
        idx[0]            = genInt64(fModule, 0);
        idx[1]            = fUICallTable[button_type];
        Value*    mth_ptr = fBuilder->CreateInBoundsGEP(ui, MAKE_IXD(idx, idx + 2));
        LoadInst* mth     = fBuilder->CreateLoad(mth_ptr);

        // Generates access to zone
        int field_index = fDSPFieldsNames[zone];
#if defined(LLVM_35)
        Value* zone_ptr = fBuilder->CreateStructGEP(dsp, field_index);
#else
        Value* zone_ptr      = fBuilder->CreateStructGEP(0, dsp, field_index);
#endif
        Value*    fun_args[] = {fUIInterfacePtr, getStringConstant(label), zone_ptr};
        CallInst* call_inst  = fBuilder->CreateCall(mth, fun_args);
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

    void addGenericSlider(const string& label, const string& zone, double init, double min, double max, double step,
                          const string& slider_type)
    {
        Function*              llvm_buildUserInterface = fModule->getFunction("buildUserInterface" + fPrefix);
        Function::arg_iterator func_llvm_buildUserInterface_args_it = llvm_buildUserInterface->arg_begin();
        Value*                 dsp = GET_ITERATOR(func_llvm_buildUserInterface_args_it++);
        Value*                 ui  = GET_ITERATOR(func_llvm_buildUserInterface_args_it++);

        Value* idx[2];
        idx[0]            = genInt64(fModule, 0);
        idx[1]            = fUICallTable[slider_type];
        Value*    mth_ptr = fBuilder->CreateInBoundsGEP(ui, MAKE_IXD(idx, idx + 2));
        LoadInst* mth     = fBuilder->CreateLoad(mth_ptr);

        // Generates access to zone
        int field_index = fDSPFieldsNames[zone];
#if defined(LLVM_35)
        Value* zone_ptr = fBuilder->CreateStructGEP(dsp, field_index);
#else
        Value* zone_ptr      = fBuilder->CreateStructGEP(0, dsp, field_index);
#endif

        Value* idx2[7];
        idx2[0] = fUIInterfacePtr;
        idx2[1] = getStringConstant(label);
        idx2[2] = zone_ptr;
        idx2[3] = genReal(init);
        idx2[4] = genReal(min);
        idx2[5] = genReal(max);
        idx2[6] = genReal(step);

        CallInst* call_inst = fBuilder->CreateCall(mth, MAKE_IXD(idx2, idx2 + 7));
        call_inst->setCallingConv(CallingConv::C);
    }

    virtual void visit(AddSliderInst* inst)
    {
        string name;
        switch (inst->fType) {
            case AddSliderInst::kHorizontal: {
                name = "addHorizontalSlider";
                break;
            }
            case AddSliderInst::kVertical: {
                name = "addVerticalSlider";
                break;
            }
            case AddSliderInst::kNumEntry: {
                name = "addNumEntry";
                break;
            }
        }
        addGenericSlider(inst->fLabel, inst->fZone, inst->fInit, inst->fMin, inst->fMax, inst->fStep, name);
    }

    void addGenericBargraph(const string& label, const string& zone, double min, double max,
                            const string& bargraph_type)
    {
        Function*              llvm_buildUserInterface = fModule->getFunction("buildUserInterface" + fPrefix);
        Function::arg_iterator func_llvm_buildUserInterface_args_it = llvm_buildUserInterface->arg_begin();
        Value*                 dsp = GET_ITERATOR(func_llvm_buildUserInterface_args_it++);
        Value*                 ui  = GET_ITERATOR(func_llvm_buildUserInterface_args_it++);

        Value* idx[2];
        idx[0]            = genInt64(fModule, 0);
        idx[1]            = fUICallTable[bargraph_type];
        Value*    mth_ptr = fBuilder->CreateInBoundsGEP(ui, MAKE_IXD(idx, idx + 2));
        LoadInst* mth     = fBuilder->CreateLoad(mth_ptr);

        // Generates access to zone
        int field_index = fDSPFieldsNames[zone];
#if defined(LLVM_35)
        Value* zone_ptr = fBuilder->CreateStructGEP(dsp, field_index);
#else
        Value* zone_ptr      = fBuilder->CreateStructGEP(0, dsp, field_index);
#endif

        Value* idx2[5];
        idx2[0] = fUIInterfacePtr;
        idx2[1] = getStringConstant(label);
        idx2[2] = zone_ptr;
        idx2[3] = genReal(min);
        idx2[4] = genReal(max);

        CallInst* call_inst = fBuilder->CreateCall(mth, MAKE_IXD(idx2, idx2 + 5));
        call_inst->setCallingConv(CallingConv::C);
    }

    virtual void visit(AddBargraphInst* inst)
    {
        string name;
        switch (inst->fType) {
            case AddBargraphInst::kHorizontal: {
                name = "addHorizontalBargraph";
                break;
            }
            case AddBargraphInst::kVertical: {
                name = "addVerticalBargraph";
                break;
            }
        }
        addGenericBargraph(inst->fLabel, inst->fZone, inst->fMin, inst->fMax, name);
    }

    virtual void visit(AddSoundfileInst* inst)
    {
        Function*              llvm_buildUserInterface = fModule->getFunction("buildUserInterface" + fPrefix);
        Function::arg_iterator func_llvm_buildUserInterface_args_it = llvm_buildUserInterface->arg_begin();
        Value*                 dsp = GET_ITERATOR(func_llvm_buildUserInterface_args_it++);
        Value*                 ui  = GET_ITERATOR(func_llvm_buildUserInterface_args_it++);

        Value* idx[2];
        idx[0]            = genInt64(fModule, 0);
        idx[1]            = fUICallTable["addSoundfile"];
        Value*    mth_ptr = fBuilder->CreateInBoundsGEP(ui, MAKE_IXD(idx, idx + 2));
        LoadInst* mth     = fBuilder->CreateLoad(mth_ptr);

        // Generates access to zone
        int field_index = fDSPFieldsNames[inst->fSFZone];
#if defined(LLVM_35)
        Value* soundfile_ptr = fBuilder->CreateStructGEP(dsp, field_index);
#else
        Value* soundfile_ptr = fBuilder->CreateStructGEP(0, dsp, field_index);
#endif

        Value* idx2[4];
        idx2[0] = fUIInterfacePtr;
        idx2[1] = getStringConstant(inst->fLabel);
        idx2[2] = getStringConstant(inst->fURL);
        idx2[3] = soundfile_ptr;

        CallInst* call_inst = fBuilder->CreateCall(mth, MAKE_IXD(idx2, idx2 + 4));
        call_inst->setCallingConv(CallingConv::C);
    }

    virtual void visit(DeclareVarInst* inst)
    {
        BasicTyped* basic_typed = dynamic_cast<BasicTyped*>(inst->fType);
        ArrayTyped* array_typed = dynamic_cast<ArrayTyped*>(inst->fType);
        string      name        = inst->fAddress->getName();

        if (inst->fAddress->getAccess() & Address::kStruct) {
            // Not supposed to happen
            faustassert(false);
        } else if (inst->fAddress->getAccess() & Address::kFunArgs) {
            // Not supposed to happen
            faustassert(false);
            // Direct access Declare/Store ==> Load
        } else if (inst->fAddress->getAccess() & Address::kLink) {
            if (inst->fValue) {
                // Result is in fCurValue;
                inst->fValue->accept(this);
                fDSPStackVars[name] = fCurValue;
            }
        } else if (inst->fAddress->getAccess() & Address::kStack || inst->fAddress->getAccess() & Address::kLoop) {
            // If we have an explicit alloca builder, use it
            if (fAllocaBuilder->GetInsertBlock()) {
                // Always at the begining since the block is already branched to next one...
                fAllocaBuilder->SetInsertPoint(GET_ITERATOR(fAllocaBuilder->GetInsertBlock()->getFirstInsertionPt()));
                fCurValue = fAllocaBuilder->CreateAlloca(convertFIRType(fModule, inst->fType));
            } else {
                fCurValue = fBuilder->CreateAlloca(convertFIRType(fModule, inst->fType));
            }

            fCurValue->setName(name);
            fDSPStackVars[name] = fCurValue;  // Keep var

            // Declaration with a value
            if (inst->fValue) {
                // Result is in fCurValue;
                inst->fValue->accept(this);
                genVectorStore(fDSPStackVars[name], fCurValue, false);
            }

        } else if (inst->fAddress->getAccess() & Address::kGlobal ||
                   inst->fAddress->getAccess() & Address::kStaticStruct) {
            if (!fModule->getGlobalVariable(name, true)) {
                GlobalVariable* global_var = new GlobalVariable(
                    *fModule, convertFIRType(fModule, inst->fType), false,
                    ((inst->fAddress->getAccess() & Address::kExternal) ? GlobalValue::ExternalLinkage
                                                                        : GlobalValue::InternalLinkage),
                    0, name);

                // Declaration with a value
                if (inst->fValue) {
                    // Result is in fCurValue;
                    inst->fValue->accept(this);

                    // HACK : special case if we store a 0 (null pointer) in an address
                    if ((global_var->getType() != PointerType::get(fCurValue->getType(), 0)) &&
                        (fCurValue->getType() == llvm::Type::getInt32Ty(fModule->getContext()) ||
                         fCurValue->getType() == llvm::Type::getInt64Ty(fModule->getContext()))) {
                        global_var->setInitializer((Constant*)ConstantPointerNull::get(
                            (llvm::PointerType*)(global_var->getType()->getContainedType(0))));
                    } else {
                        global_var->setInitializer(static_cast<Constant*>(fCurValue));
                    }

                } else {
                    // Init with 0
                    if (basic_typed) {
                        global_var->setInitializer(static_cast<Constant*>(
                            (inst->fType->getType() == Typed::kFloat) ? genFloat(fModule, 0.f) : genInt32(fModule, 0)));
                    } else if (array_typed) {
                        global_var->setInitializer(ConstantAggregateZero::get(convertFIRType(fModule, inst->fType)));
                    } else {
                        faustassert(false);
                    }
                }
            }
        }

        // No result in fCurValue
        fCurValue = nullptr;
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
        fCurValue = nullptr;
    }

    virtual void visit(DeclareFunInst* inst)
    {
        Function* function = fModule->getFunction(inst->fName);

        if (!function) {  // Define it

            // Special cases for min/max
            if (checkMinMax(inst->fName)) {
                fCurValue = nullptr;
                return;
            }

            // Return type
            faustassert(fTypeMap.find(inst->fType->fResult->getType()) != fTypeMap.end());
            LLVM_TYPE return_type = fTypeMap[inst->fType->fResult->getType()];

            // Prepare vector of LLVM types for args
            VECTOR_OF_TYPES                   fun_args_type;
            list<NamedTyped*>::const_iterator it;
            for (it = inst->fType->fArgsTypes.begin(); it != inst->fType->fArgsTypes.end(); it++) {
                // cerr << "DeclareFunInst " << (*it)->getType() << endl;
                faustassert(fTypeMap.find((*it)->getType()) != fTypeMap.end());
                fun_args_type.push_back(fTypeMap[(*it)->getType()]);
            }

            // Creates function
            FunctionType* fun_type = FunctionType::get(return_type, MAKE_VECTOR_OF_TYPES(fun_args_type), false);
            function               = Function::Create(
                fun_type,
                (inst->fType->fAttribute & FunTyped::kLocal || inst->fType->fAttribute & FunTyped::kStatic)
                    ? GlobalValue::InternalLinkage
                    : GlobalValue::ExternalLinkage,
                inst->fName, fModule);
            function->setCallingConv(CallingConv::C);

            // In order for auto-vectorization to correctly work with vectorizable math functions
            if (find(gMathLibTable.begin(), gMathLibTable.end(), inst->fName) != gMathLibTable.end()) {
                function->setDoesNotAccessMemory();
                // printf("inst->fName YES %s\n", inst->fName.c_str());
            } else {
                // printf("inst->fName NO %s\n", inst->fName.c_str());
            }
            function->setDoesNotThrow();

            // Set name for function arguments
            Function::arg_iterator args = function->arg_begin();
            for (it = inst->fType->fArgsTypes.begin(); it != inst->fType->fArgsTypes.end(); it++) {
                Value* llvm_arg = GET_ITERATOR(args++);
                llvm_arg->setName((*it)->fName);
            }

            // If there is a body, compile it
            if (inst->fCode->fCode.size() > 0) {
                // Prepare a entry_block to insert into
                BasicBlock* entry_block = BasicBlock::Create(fModule->getContext(), "entry_block", function);

                fBuilder->SetInsertPoint(entry_block);
                // "Alloca" in first "entry_bock" are mandatory so that vectorization passes correctly work.
                fAllocaBuilder->SetInsertPoint(entry_block);

                // Compile code in this block
                inst->fCode->accept(this);
                verifyFunction(*function);

                // Clear inserting points
                fBuilder->ClearInsertionPoint();
                fAllocaBuilder->ClearInsertionPoint();
            }
        }

        // No result
        fCurValue = nullptr;
    }

    Value* getDSPArg(const string& name)
    {
        // Get the enclosing function
        Function*              function         = fBuilder->GetInsertBlock()->getParent();
        Function::arg_iterator function_args_it = function->arg_begin();
        // Get arg with inst name
        Value* arg = nullptr;
        do {
            arg = GET_ITERATOR(function_args_it++);
            if (arg->getName() == name) {
                return arg;
            }
        } while (function_args_it != function->arg_end());
        faustassert(false);
        return arg;
    }

    // LoadVarInst

    Value* visitNameAddressAux(NamedAddress* named_address)
    {
        // dump2FIR(named_address);
        if (named_address->fAccess & Address::kStruct) {
            int field_index = fDSPFieldsNames[named_address->fName];
#if defined(LLVM_35)
            return fBuilder->CreateStructGEP(getDSPArg("dsp"), field_index);
#else
            return fBuilder->CreateStructGEP(0, getDSPArg("dsp"), field_index);
#endif
        } else if (named_address->fAccess & Address::kFunArgs) {
            return getDSPArg(named_address->fName);
            // Direct access Declare/Store ==> Load
        } else if (named_address->fAccess & Address::kLink || named_address->fAccess & Address::kStack ||
                   named_address->fAccess & Address::kLoop) {
            return fDSPStackVars[named_address->fName];
        } else if ((named_address->fAccess & Address::kGlobal) || (named_address->fAccess & Address::kStaticStruct)) {
            return fModule->getGlobalVariable(named_address->fName, true);
        } else {
            faustassert(false);
            return nullptr;
        }
    }

    void visitNameAddress(LoadVarInst* inst, NamedAddress* named_address)
    {
        Value* load_ptr = visitNameAddressAux(named_address);
        // dumpLLVM(load_ptr);

        if (named_address->fAccess & Address::kStruct || named_address->fAccess & Address::kStack ||
            named_address->fAccess & Address::kLoop || named_address->fAccess & Address::kGlobal ||
            named_address->fAccess & Address::kStaticStruct) {
            // We want to see array like [256 x float] as a float*
            fCurValue = loadArrayAsPointer(load_ptr, inst->fAddress->getAccess() & Address::kVolatile);
        } else {
            fCurValue = load_ptr;
        }
    }

    Value* visitIndexedAddressAux(IndexedAddress* indexed_address)
    {
        NamedAddress* named_address = dynamic_cast<NamedAddress*>(indexed_address->fAddress);
        faustassert(named_address);  // One level indexation for now

        // Compute index, result is in fCurValue
        indexed_address->fIndex->accept(this);
        Value* res_load_ptr;

        if (named_address->fAccess & Address::kStruct) {
            int field_index = fDSPFieldsNames[named_address->fName];

            Value* idx[2];
            idx[0] = genInt64(fModule, 0);
            idx[1] = genInt32(fModule, field_index);

            Value* load_ptr1 = fBuilder->CreateInBoundsGEP(getDSPArg("dsp"), MAKE_IXD(idx, idx + 2));
            res_load_ptr     = loadArrayAsPointer(load_ptr1);

        } else if (named_address->fAccess & Address::kFunArgs) {
            res_load_ptr = getDSPArg(named_address->fName);
        } else if (named_address->fAccess & Address::kStack || named_address->fAccess & Address::kLoop) {
            // We want to see array like [256 x float] as a float*
            res_load_ptr = loadArrayAsPointer(fDSPStackVars[named_address->fName]);
        } else if (named_address->fAccess & Address::kGlobal || named_address->fAccess & Address::kStaticStruct) {
            // We want to see array like [256 x float] as a float*
            faustassert(fModule->getGlobalVariable(named_address->fName, true));
            res_load_ptr = loadArrayAsPointer(fModule->getGlobalVariable(named_address->fName, true));
        } else {
            // Default
            faustassert(false);
            return nullptr;
        }

        /*
         Indexed adresses can actually be values in an array or fields in a struct type
         */
        if (isStructType(indexed_address->getName())) {
            Value* idx[2];
            idx[0] = genInt64(fModule, 0);
            idx[1] = fCurValue;
            return fBuilder->CreateInBoundsGEP(res_load_ptr, MAKE_IXD(idx, idx + 2));
        } else {
            return fBuilder->CreateInBoundsGEP(res_load_ptr, fCurValue);
        }
    }

    void visitIndexedAddress(LoadVarInst* inst, IndexedAddress* indexed_address)
    {
        fCurValue = fBuilder->CreateLoad(visitIndexedAddressAux(indexed_address));
    }

    virtual void visit(LoadVarInst* inst)
    {
        NamedAddress*   named_address   = dynamic_cast<NamedAddress*>(inst->fAddress);
        IndexedAddress* indexed_address = dynamic_cast<IndexedAddress*>(inst->fAddress);

        if (named_address) {
            visitNameAddress(inst, named_address);
        } else if (indexed_address) {
            visitIndexedAddress(inst, indexed_address);
        } else {
            faustassert(false);
        }
    }

    // LoadVarAddressInst

    void visitNameAddress(LoadVarAddressInst* inst, NamedAddress* named_address)
    {
        if (named_address->fAccess & Address::kStruct || named_address->fAccess & Address::kLink ||
            named_address->fAccess & Address::kStack || named_address->fAccess & Address::kLoop ||
            named_address->fAccess & Address::kGlobal || named_address->fAccess & Address::kStaticStruct) {
            fCurValue = visitNameAddressAux(named_address);
        } else {
            // Not supported
            faustassert(false);
        }
    }

    void visitIndexedAddress(LoadVarAddressInst* inst, IndexedAddress* indexed_address)
    {
        fCurValue = visitIndexedAddressAux(indexed_address);
    }

    virtual void visit(LoadVarAddressInst* inst)
    {
        NamedAddress*   named_address   = dynamic_cast<NamedAddress*>(inst->fAddress);
        IndexedAddress* indexed_address = dynamic_cast<IndexedAddress*>(inst->fAddress);

        if (named_address) {
            visitNameAddress(inst, named_address);
        } else if (indexed_address) {
            visitIndexedAddress(inst, indexed_address);
        } else {
            faustassert(false);
        }
    }

    // StoreVarInst

    void genVectorStore(Value* store_ptr, Value* store, bool isvolatile)
    {
        // HACK : special case if we store a 0 (null pointer) in an address
        // (used in vec mode and in "allocate" function in scheduler mode...)
        if ((store_ptr->getType() != PointerType::get(store->getType(), 0)) &&
            (store->getType() == llvm::Type::getInt32Ty(fModule->getContext()) ||
             store->getType() == llvm::Type::getInt64Ty(fModule->getContext()))) {
            Value* casted_store =
                ConstantPointerNull::get(static_cast<llvm::PointerType*>(store_ptr->getType()->getContainedType(0)));
            fBuilder->CreateStore(casted_store, store_ptr, isvolatile);
        } else {
            fBuilder->CreateStore(store, store_ptr, isvolatile);
        }
    }

    void visitNameAddress(StoreVarInst* inst, NamedAddress* named_address)
    {
        // dump2FIR(inst);

        // Result is in fCurValue;
        inst->fValue->accept(this);

        if (named_address->fAccess & Address::kStruct) {
            int field_index = fDSPFieldsNames[named_address->fName];
#if defined(LLVM_35)
            Value* store_ptr = fBuilder->CreateStructGEP(getDSPArg("dsp"), field_index);
#else
            Value* store_ptr = fBuilder->CreateStructGEP(0, getDSPArg("dsp"), field_index);
#endif
            genVectorStore(store_ptr, fCurValue, named_address->fAccess & Address::kVolatile);
        } else if (named_address->fAccess & Address::kFunArgs) {
            genVectorStore(getDSPArg(named_address->fName), fCurValue, named_address->fAccess & Address::kVolatile);
            // Direct access Declare/Store ==> Load
        } else if (named_address->fAccess & Address::kLink) {
            fDSPStackVars[named_address->fName] = fCurValue;
        } else if (named_address->fAccess & Address::kStack || named_address->fAccess & Address::kLoop) {
            faustassert(fDSPStackVars.find(named_address->fName) != fDSPStackVars.end());
            genVectorStore(fDSPStackVars[named_address->fName], fCurValue,
                           inst->fAddress->getAccess() & Address::kVolatile);
        } else if (named_address->fAccess & Address::kGlobal || named_address->fAccess & Address::kStaticStruct) {
            faustassert(fModule->getGlobalVariable(named_address->fName, true));
            genVectorStore(fModule->getGlobalVariable(named_address->fName, true), fCurValue,
                           inst->fAddress->getAccess() & Address::kVolatile);
        }
    }

    void visitIndexedAddress(StoreVarInst* inst, IndexedAddress* indexed_address)
    {
        NamedAddress* named_address = dynamic_cast<NamedAddress*>(indexed_address->fAddress);
        faustassert(named_address);  // One level indexation for now

        // Compute index, result is in fCurValue
        indexed_address->fIndex->accept(this);
        Value* store_ptr;

        if (named_address->fAccess & Address::kStruct) {
            int    field_index = fDSPFieldsNames[named_address->fName];
            Value* idx[2];
            idx[0] = genInt64(fModule, 0);
            idx[1] = genInt32(fModule, field_index);

            Value* store_ptr1 = fBuilder->CreateInBoundsGEP(getDSPArg("dsp"), MAKE_IXD(idx, idx + 2));
            Value* store_ptr2 = loadArrayAsPointer(store_ptr1);
            store_ptr         = fBuilder->CreateInBoundsGEP(store_ptr2, fCurValue);

        } else if (named_address->fAccess & Address::kFunArgs) {
            store_ptr = fBuilder->CreateInBoundsGEP(getDSPArg(named_address->fName), fCurValue);
        } else if (named_address->fAccess & Address::kStack || named_address->fAccess & Address::kLoop) {
            faustassert(fDSPStackVars.find(named_address->fName) != fDSPStackVars.end());
            // We want to see array like [256 x float] as a float*
            Value* store_ptr1 = loadArrayAsPointer(fDSPStackVars[named_address->fName]);
            store_ptr         = fBuilder->CreateInBoundsGEP(store_ptr1, fCurValue);
        } else if (named_address->fAccess & Address::kGlobal || named_address->fAccess & Address::kStaticStruct) {
            faustassert(fModule->getGlobalVariable(named_address->fName, true));
            // We want to see array like [256 x float] as a float*
            Value* store_ptr1 = loadArrayAsPointer(fModule->getGlobalVariable(named_address->fName, true));
            store_ptr         = fBuilder->CreateInBoundsGEP(store_ptr1, fCurValue);
        } else {
            // default
            faustassert(false);
            return;
        }

        // Compute value to be stored, result is in fCurValue
        inst->fValue->accept(this);
        genVectorStore(store_ptr, fCurValue, named_address->fAccess & Address::kVolatile);
    }

    virtual void visit(StoreVarInst* inst)
    {
        // dump2FIR(inst);

        NamedAddress*   named_address   = dynamic_cast<NamedAddress*>(inst->fAddress);
        IndexedAddress* indexed_address = dynamic_cast<IndexedAddress*>(inst->fAddress);

        if (named_address) {
            visitNameAddress(inst, named_address);
        } else if (indexed_address) {
            visitIndexedAddress(inst, indexed_address);
        } else {
            faustassert(false);
        }

        // No result in fCurValue
        fCurValue = nullptr;
    }

    virtual void visit(FloatNumInst* inst) { fCurValue = genFloat(fModule, inst->fNum); }

    virtual void visit(FloatArrayNumInst* inst)
    {
        std::vector<Constant*> num_array;
        for (unsigned int i = 0; i < inst->fNumTable.size(); i++) {
            num_array.push_back(static_cast<ConstantFP*>(genFloat(fModule, inst->fNumTable[i])));
        }
        ArrayType* array_type = ArrayType::get(getFloatTy(fModule), inst->fNumTable.size());
        fCurValue             = ConstantArray::get(array_type, num_array);
    }

    virtual void visit(DoubleNumInst* inst) { fCurValue = genDouble(fModule, inst->fNum); }

    virtual void visit(DoubleArrayNumInst* inst)
    {
        std::vector<Constant*> num_array;
        for (unsigned int i = 0; i < inst->fNumTable.size(); i++) {
            num_array.push_back(static_cast<ConstantFP*>(genDouble(fModule, inst->fNumTable[i])));
        }
        ArrayType* array_type = ArrayType::get(getDoubleTy(fModule), inst->fNumTable.size());
        fCurValue             = ConstantArray::get(array_type, num_array);
    }

    virtual void visit(BoolNumInst* inst) { fCurValue = genInt1(fModule, inst->fNum); }

    virtual void visit(Int32NumInst* inst) { fCurValue = genInt32(fModule, inst->fNum); }

    virtual void visit(Int64NumInst* inst) { fCurValue = genInt64(fModule, inst->fNum); }

    virtual void visit(Int32ArrayNumInst* inst)
    {
        std::vector<Constant*> num_array;
        for (unsigned int i = 0; i < inst->fNumTable.size(); i++) {
            num_array.push_back(static_cast<ConstantFP*>(genInt32(fModule, inst->fNumTable[i])));
        }
        ArrayType* array_type = ArrayType::get(getInt32Ty(fModule), inst->fNumTable.size());
        fCurValue             = ConstantArray::get(array_type, num_array);
    }

    virtual void visit(BinopInst* inst)
    {
        // dump2FIR(inst);

        // Keep result of first arg compilation
        inst->fInst1->accept(this);
        LLVMValue res1 = fCurValue;
        // dumpLLVM(res1);

        // Keep result of second arg compilation
        inst->fInst2->accept(this);
        LLVMValue res2 = fCurValue;
        // dumpLLVM(res2);

        fCurValue = generateBinopAux(inst->fOpcode, res1, res2);
    }

    virtual void visit(::CastInst* inst)
    {
        // dump2FIR(inst);

        // Compile instruction to be casted, result in fCurValue
        inst->fInst->accept(this);
        visitCastAux(inst->fType->getType());
    }

    virtual void visit(::BitcastInst* inst)
    {
        // Compile exp to bitcast, result in fCurValue
        inst->fInst->accept(this);

        switch (inst->fType->getType()) {
            case Typed::kInt32:
                fCurValue = fBuilder->CreateBitCast(fCurValue, fBuilder->getInt32Ty());
                break;
            case Typed::kInt64:
                fCurValue = fBuilder->CreateBitCast(fCurValue, fBuilder->getInt64Ty());
                break;
            case Typed::kFloat:
                fCurValue = fBuilder->CreateBitCast(fCurValue, fBuilder->getFloatTy());
                break;
            case Typed::kDouble:
                fCurValue = fBuilder->CreateBitCast(fCurValue, fBuilder->getDoubleTy());
                break;
            default:
                faustassert(false);
                break;
        }
    }

    void visitCastAux(Typed::VarType type)
    {
        // dumpLLVM(fModule);

        switch (type) {
            case Typed::kFloat:
                if (fCurValue->getType() == getInt32Ty(fModule)) {
                    fCurValue = fBuilder->CreateSIToFP(fCurValue, getFloatTy(fModule));
                } else if (fCurValue->getType() == getFloatTy(fModule)) {
                    // Nothing to do
                } else if (fCurValue->getType() == getDoubleTy(fModule)) {
                    fCurValue = fBuilder->CreateFPTrunc(fCurValue, getFloatTy(fModule));
                } else {
                    faustassert(false);
                }
                break;

            case Typed::kInt32:
                if (fCurValue->getType() == getInt32Ty(fModule)) {
                    // Nothing to do
                } else if (fCurValue->getType() == getFloatTy(fModule)) {
                    fCurValue = fBuilder->CreateFPToSI(fCurValue, getInt32Ty(fModule));
                } else if (fCurValue->getType() == getDoubleTy(fModule)) {
                    fCurValue = fBuilder->CreateFPToSI(fCurValue, getInt32Ty(fModule));
                } else if (fCurValue->getType()->isPointerTy()) {
                    // Use BitCast for pointer to kInt32
                    fCurValue = fBuilder->CreateBitCast(fCurValue, fBuilder->getInt32Ty());
                } else {
                    faustassert(false);
                }
                break;

            case Typed::kDouble:
                if (fCurValue->getType() == getInt32Ty(fModule)) {
                    fCurValue = fBuilder->CreateSIToFP(fCurValue, getDoubleTy(fModule));
                } else if (fCurValue->getType() == getFloatTy(fModule)) {
                    fCurValue = fBuilder->CreateFPExt(fCurValue, getDoubleTy(fModule));
                } else if (fCurValue->getType() == getDoubleTy(fModule)) {
                    // Nothing to do
                } else {
                    faustassert(false);
                }
                break;

            case Typed::kUint_ptr:
                fCurValue =
#ifndef LLVM_35
                    fBuilder->CreatePtrToInt(fCurValue, fModule->getDataLayout().getIntPtrType(fModule->getContext()));
#else
                    fBuilder->CreatePtrToInt(fCurValue, fModule->getDataLayout()->getIntPtrType(fModule->getContext()));
#endif
                break;

            case Typed::kQuad:
            default:
                // No supposed to happen
                faustassert(false);
                break;
        }
    }

    void generateFunPolymorphicMinMax(FunCallInst* inst)
    {
        vector<LLVMValue> fun_args;

        // Compile all arguments
        for (list<ValueInst*>::const_iterator it = inst->fArgs.begin(); it != inst->fArgs.end(); it++) {
            // Each argument is compiled and result is in fCurValue
            (*it)->accept(this);
            fun_args.push_back(fCurValue);
        }

        if (checkMin(inst->fName) && fun_args.size() == 2) {
            fCurValue = generateFunPolymorphicMinMaxAux(fun_args[0], fun_args[1], kLT);
        } else if (checkMax(inst->fName) && fun_args.size() == 2) {
            fCurValue = generateFunPolymorphicMinMaxAux(fun_args[0], fun_args[1], kGT);
        } else {
            faustassert(false);
        }
    }

    virtual void visit(FunCallInst* inst)
    {
        // Special case
        if (checkMinMax(inst->fName)) {
            generateFunPolymorphicMinMax(inst);
            return;
        }

        // Compile arguments
        vector<LLVMValue>                fun_args;
        list<ValueInst*>::const_iterator it;
        Function*                        function = fModule->getFunction(gGlobal->getMathFunction(inst->fName));

        // cerr << "FunCallInst " << inst->fName << endl;
        faustassert(function);

        // cout << "FunCallInst " << inst->fName << endl;
        Function::arg_iterator arg = function->arg_begin();
        for (it = inst->fArgs.begin(); it != inst->fArgs.end(); it++, arg++) {
            // Each argument is compiled and result is in fCurValue
            (*it)->accept(this);
            // Cast any struct* type to void* if needed
            if (arg->getType() == PointerType::get(llvm::Type::getInt8Ty(fModule->getContext()), 0)) {
                Value* casted = fBuilder->CreateBitCast(
                    fCurValue, PointerType::get(llvm::Type::getInt8Ty(fModule->getContext()), 0));
                fun_args.push_back(casted);
            } else {
                fun_args.push_back(fCurValue);
            }
        }

        CallInst* call_inst = CREATE_CALL(function, fun_args);
        call_inst->setCallingConv(CallingConv::C);

        // Result is function call
        fCurValue = call_inst;
    }

    virtual void visit(Select2Inst* inst)
    {
        // Compile condition, result in fCurValue
        inst->fCond->accept(this);

        // Convert condition to a bool by comparing to 0
        Value* cond_value;
        if (fCurValue->getType() == getInt64Ty(fModule)) {
            cond_value = fBuilder->CreateICmpNE(fCurValue, genInt64(fModule, 0), "ifcond");
        } else {
            cond_value = fBuilder->CreateICmpNE(fCurValue, genInt32(fModule, 0), "ifcond");
        }

        // Compile then branch, result in fCurValue
        inst->fThen->accept(this);
        Value* then_value = fCurValue;

        // Compile else branch, result in fCurValue
        inst->fElse->accept(this);
        Value* else_value = fCurValue;

        // Creates the result
        fCurValue = fBuilder->CreateSelect(cond_value, then_value, else_value);
    }

    virtual void visit(IfInst* inst)
    {
        // Compile condition, result in fCurValue
        inst->fCond->accept(this);

        // Convert condition to a bool by comparing equal to comp_val value
        Value* cond_value = fBuilder->CreateICmpEQ(fCurValue, genInt32(fModule, 1), "ifcond");

        Function* function = fBuilder->GetInsertBlock()->getParent();

        // Create blocks for the then and else cases.  Insert the 'then' block at the end of the function
        BasicBlock* then_block  = BasicBlock::Create(fModule->getContext(), "then_code", function);
        BasicBlock* else_block  = BasicBlock::Create(fModule->getContext(), "else_code");
        BasicBlock* merge_block = BasicBlock::Create(fModule->getContext(), "if_end_code");

        fBuilder->CreateCondBr(cond_value, then_block, else_block);

        // Emit then block
        fBuilder->SetInsertPoint(then_block);

        // Compile then branch, result in fCurValue
        inst->fThen->accept(this);
        // "Then" is a BlockInst so no result in fCurValue

        fBuilder->CreateBr(merge_block);
        // Codegen of 'Then' can change the current block, update then_block for the PHI
        then_block = fBuilder->GetInsertBlock();

        // Emit else block
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
        fCurValue = nullptr;
    }

    virtual void visit(ForLoopInst* inst)
    {
        // Don't generate empty loops...
        if (inst->fCode->size() == 0) return;

        string    loop_counter_name;
        Function* function = fBuilder->GetInsertBlock()->getParent();
        faustassert(function);

        // Prepare init_block
        BasicBlock* init_block = BasicBlock::Create(fModule->getContext(), "init_block", function);

        // Prepare exec_block
        BasicBlock* exec_block = BasicBlock::Create(fModule->getContext(), "exec_block", function);

        // Prepare loop_body_block
        BasicBlock* loop_body_block = BasicBlock::Create(fModule->getContext(), "loop_body_block", function);

        // Create the exit_block
        BasicBlock* exit_block = BasicBlock::Create(fModule->getContext(), "exit_block", function);

        // Init section
        {
            // Link previous_block and init_block
            fBuilder->CreateBr(init_block);

            // Start insertion in init_block
            fBuilder->SetInsertPoint(init_block);

            // Compute init value, now loop counter is allocated
            inst->fInit->accept(this);

            // Get loop counter local variable
            DeclareVarInst* declare_inst = dynamic_cast<DeclareVarInst*>(inst->fInit);
            StoreVarInst*   store_inst   = dynamic_cast<StoreVarInst*>(inst->fInit);

            if (declare_inst) {
                loop_counter_name = declare_inst->getName();
            } else if (store_inst) {
                loop_counter_name = store_inst->getName();
            } else {
                cerr << "Error in ForLoopInst " << endl;
                faustassert(false);
            }

            faustassert(fDSPStackVars.find(loop_counter_name) != fDSPStackVars.end());

            // Link init_block and exec_block
            fBuilder->CreateBr(exec_block);

            // Start insertion in exec_block
            fBuilder->SetInsertPoint(exec_block);
        }

        // Start the PHI node with an entry for start
        PHINode* phi_node = CREATE_PHI(fBuilder->getInt32Ty(), loop_counter_name);
        phi_node->addIncoming(genInt32(fModule, 0), init_block);

        // End condition
        {
            // Compute end condition, result in fCurValue
            inst->fEnd->accept(this);

            // Convert condition to a bool
            Value* end_cond = fBuilder->CreateTrunc(fCurValue, fBuilder->getInt1Ty());

            // Insert the conditional branch into the last block of loop
            fBuilder->CreateCondBr(end_cond, loop_body_block, exit_block);
        }

        // Loop body
        {
            // Start insertion in loop_body_block
            fBuilder->SetInsertPoint(loop_body_block);

            // Generates loop internal code
            inst->fCode->accept(this);
        }

        // Get last block of post code section
        BasicBlock* current_block = fBuilder->GetInsertBlock();

        // Next index computation
        {
            // Compute next index, result in fCurValue
            StoreVarInst* store_inst1 = dynamic_cast<StoreVarInst*>(inst->fIncrement);
            faustassert(store_inst1);
            store_inst1->fValue->accept(this);
            Value* next_index = fCurValue;
            next_index->setName("next_index");

            // Store the next value
            fBuilder->CreateStore(next_index, fDSPStackVars[loop_counter_name]);

            // Add a new entry to the PHI node for the backedge
            phi_node->addIncoming(next_index, current_block);

            // Back to start of loop
            fBuilder->CreateBr(exec_block);
        }

        // Move insertion in exit_block
        fBuilder->SetInsertPoint(exit_block);

        // No result in fCurValue
        fCurValue = nullptr;
    }

    virtual void visit(WhileLoopInst* inst)
    {
        Function* function = fBuilder->GetInsertBlock()->getParent();
        faustassert(function);

        // Prepare cond_block block
        BasicBlock* cond_block = BasicBlock::Create(fModule->getContext(), "cond_block", function);

        // Link previous_block and cond_block
        fBuilder->CreateBr(cond_block);

        // Start insertion in cond_block
        fBuilder->SetInsertPoint(cond_block);

        // Compile condition, result in fCurValue
        inst->fCond->accept(this);

        // Create the exec_block and insert it
        BasicBlock* exec_block = BasicBlock::Create(fModule->getContext(), "exec_block", function);

        // Create the exit_block and insert it
        BasicBlock* exit_block = BasicBlock::Create(fModule->getContext(), "exit_block", function);

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
        fCurValue = nullptr;
    }

    virtual void visit(BlockInst* inst)
    {
        if (fBuilder->GetInsertBlock()) {
            Function* function = fBuilder->GetInsertBlock()->getParent();
            faustassert(function);

            // Prepare code_block block
            BasicBlock* code_block = BasicBlock::Create(fModule->getContext(), "code_block", function);

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
        fCurValue = nullptr;
    }

    virtual void visit(::SwitchInst* inst)
    {
        Function* function = fBuilder->GetInsertBlock()->getParent();
        faustassert(function);

        // Prepare init_code block
        BasicBlock* init_block = BasicBlock::Create(fModule->getContext(), "init_block", function);

        // Prepare exit_block block
        BasicBlock* exit_block = BasicBlock::Create(fModule->getContext(), "exit_block", function);

        // Link previous_block and init_block
        fBuilder->CreateBr(init_block);

        // Start insertion in init_block
        fBuilder->SetInsertPoint(init_block);

        // Compile condition, result in fCurValue
        inst->fCond->accept(this);

        list<pair<int, BlockInst*> >::const_iterator it;

        // Creates "default" block
        BasicBlock* default_block = BasicBlock::Create(fModule->getContext(), "default", function);

        // Creates switch
        llvm::SwitchInst* switch_inst = fBuilder->CreateSwitch(fCurValue, default_block, inst->fCode.size());

        for (it = inst->fCode.begin(); it != inst->fCode.end(); it++) {
            if ((*it).first != -1) {  // All cases but "default"
                // Creates "case" block
                BasicBlock* case_block = BasicBlock::Create(fModule->getContext(), "case", function);
                // Move insertion in case_block
                fBuilder->SetInsertPoint(case_block);
                // Compiles "case" block
                (*it).second->accept(this);
                // Link init_block and exit_block
                fBuilder->CreateBr(exit_block);
                // Add it into the switch
                switch_inst->addCase(static_cast<ConstantInt*>(genInt32(fModule, (*it).first)), case_block);
            }
        }

        for (it = inst->fCode.begin(); it != inst->fCode.end(); it++) {
            if ((*it).first == -1) {  // Default case found
                break;
            }
        }

        // Move insertion in default_block
        fBuilder->SetInsertPoint(default_block);

        // Compiles "default" block if one has been found
        if (it != inst->fCode.end()) {
            (*it).second->accept(this);
        }

        // Link init_block and exit_block
        fBuilder->CreateBr(exit_block);

        // Move insertion in exit_block
        fBuilder->SetInsertPoint(exit_block);

        // No result in fCurValue
        fCurValue = nullptr;
    }

    //==============
    // Helper code
    //==============

    LLVMValue generateScalarSelect(int opcode, LLVMValue cond_value, LLVMValue then_value, LLVMValue else_value)
    {
        return fBuilder->CreateSelect(cond_value, then_value, else_value);
    }

    LLVMValue generateBinOpReal(int opcode, LLVMValue arg1, LLVMValue arg2)
    {
        if (isBoolOpcode(opcode)) {
            Value* comp_value =
                fBuilder->CreateFCmp((CmpInst::Predicate)gBinOpTable[opcode]->fLLVMFloatInst, arg1, arg2);
            // Inst result for comparison
            return generateScalarSelect(opcode, comp_value, genInt32(fModule, 1), genInt32(fModule, 0));
        } else {
            LLVMValue value =
                fBuilder->CreateBinOp((Instruction::BinaryOps)gBinOpTable[opcode]->fLLVMFloatInst, arg1, arg2);
            Instruction* inst = cast<Instruction>(value);
            inst->setMetadata(LLVMContext::MD_fpmath, fBuilder->getDefaultFPMathTag());
            inst->setFastMathFlags(fBuilder->getFastMathFlags());
            return inst;
        }
    }

    LLVMValue generateBinOpInt32_64(int opcode, LLVMValue arg1, LLVMValue arg2)
    {
        if (isBoolOpcode(opcode)) {
            Value* comp_value = fBuilder->CreateICmp((CmpInst::Predicate)gBinOpTable[opcode]->fLLVMIntInst, arg1, arg2);
            // Inst result for comparison
            return generateScalarSelect(opcode, comp_value, genInt32(fModule, 1), genInt32(fModule, 0));
        } else {
            return fBuilder->CreateBinOp((Instruction::BinaryOps)gBinOpTable[opcode]->fLLVMIntInst, arg1, arg2);
        }
    }

    LLVMValue generateBinopAux(int opcode, LLVMValue arg1, LLVMValue arg2)
    {
        faustassert(arg1);
        faustassert(arg2);

        // Arguments are casted if needed in InstructionsCompiler::generateBinOp
        faustassert(arg1->getType() == arg2->getType());

        if (arg1->getType() == getFloatTy(fModule) || arg1->getType() == getDoubleTy(fModule)) {
            return generateBinOpReal(opcode, arg1, arg2);
        } else if (arg1->getType() == getInt32Ty(fModule) || arg1->getType() == getInt64Ty(fModule)) {
            return generateBinOpInt32_64(opcode, arg1, arg2);
        } else {
            // Should not happen
            cerr << "generateBinopAux" << endl;
            faustassert(false);
            return nullptr;
        }
    }

    LLVMValue generateFunPolymorphicMinMaxAux(Value* arg1, Value* arg2, int comparator)
    {
        if (arg1->getType() == getFloatTy(fModule) && arg2->getType() == getFloatTy(fModule)) {
            Value* comp_value =
                fBuilder->CreateFCmp((llvm::CmpInst::Predicate)gBinOpTable[comparator]->fLLVMFloatInst, arg1, arg2);
            return generateScalarSelect(comparator, comp_value, arg1, arg2);

        } else if (arg1->getType() == getFloatTy(fModule) && arg2->getType() == getDoubleTy(fModule)) {
            // Generates cast arg1 to double
            Value* cast_value = fBuilder->CreateFPExt(arg1, getDoubleTy(fModule));
            Value* comp_value = fBuilder->CreateFCmp((llvm::CmpInst::Predicate)gBinOpTable[comparator]->fLLVMFloatInst,
                                                     cast_value, arg2);
            return generateScalarSelect(comparator, comp_value, arg1, arg2);

        } else if (arg1->getType() == getFloatTy(fModule) && arg2->getType() == getInt32Ty(fModule)) {
            // Generates cast arg2 to float
            Value* cast_value = fBuilder->CreateSIToFP(arg2, getFloatTy(fModule));
            Value* comp_value = fBuilder->CreateFCmp((llvm::CmpInst::Predicate)gBinOpTable[comparator]->fLLVMFloatInst,
                                                     arg1, cast_value);
            return generateScalarSelect(comparator, comp_value, arg1, cast_value);

        } else if (arg1->getType() == getDoubleTy(fModule) && arg2->getType() == getFloatTy(fModule)) {
            // Generates cast arg2 to double
            Value* cast_value = fBuilder->CreateFPExt(arg2, getDoubleTy(fModule));
            Value* comp_value = fBuilder->CreateFCmp((llvm::CmpInst::Predicate)gBinOpTable[comparator]->fLLVMFloatInst,
                                                     arg1, cast_value);
            return generateScalarSelect(comparator, comp_value, arg1, cast_value);

        } else if (arg1->getType() == getDoubleTy(fModule) && arg2->getType() == getDoubleTy(fModule)) {
            Value* comp_value =
                fBuilder->CreateFCmp((llvm::CmpInst::Predicate)gBinOpTable[comparator]->fLLVMFloatInst, arg1, arg2);
            return generateScalarSelect(comparator, comp_value, arg1, arg2);

        } else if (arg1->getType() == getDoubleTy(fModule) && arg2->getType() == getInt32Ty(fModule)) {
            // Generates cast arg2 to double
            Value* cast_value = fBuilder->CreateSIToFP(arg2, getDoubleTy(fModule));
            Value* comp_value = fBuilder->CreateFCmp((llvm::CmpInst::Predicate)gBinOpTable[comparator]->fLLVMFloatInst,
                                                     arg1, cast_value);
            return generateScalarSelect(comparator, comp_value, arg1, cast_value);

        } else if (arg1->getType() == getInt32Ty(fModule) && arg2->getType() == getFloatTy(fModule)) {
            // Generates cast arg1 to float
            Value* cast_value = fBuilder->CreateSIToFP(arg1, getFloatTy(fModule));
            Value* comp_value = fBuilder->CreateFCmp((llvm::CmpInst::Predicate)gBinOpTable[comparator]->fLLVMFloatInst,
                                                     cast_value, arg2);
            return generateScalarSelect(comparator, comp_value, cast_value, arg2);

        } else if (arg1->getType() == getInt32Ty(fModule) && arg2->getType() == getDoubleTy(fModule)) {
            // Generates cast arg1 to double
            Value* cast_value = fBuilder->CreateSIToFP(arg1, getDoubleTy(fModule));
            Value* comp_value = fBuilder->CreateFCmp((llvm::CmpInst::Predicate)gBinOpTable[comparator]->fLLVMFloatInst,
                                                     cast_value, arg2);
            return generateScalarSelect(comparator, comp_value, cast_value, arg2);

        } else if (arg1->getType() == getInt32Ty(fModule) && arg2->getType() == getInt32Ty(fModule)) {
            Value* comp_value =
                fBuilder->CreateICmp((llvm::CmpInst::Predicate)gBinOpTable[comparator]->fLLVMIntInst, arg1, arg2);
            return generateScalarSelect(comparator, comp_value, arg1, arg2);

        } else {
            // Should not happen
            cerr << "generateFunPolymorphicMinMaxAux" << endl;
            faustassert(false);
            return nullptr;
        }
    }
};

#endif
