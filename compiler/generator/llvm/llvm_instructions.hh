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

#ifndef _LLVM_INSTRUCTIONS_H
#define _LLVM_INSTRUCTIONS_H

#ifdef WIN32
#pragma warning(disable : 4624 4291 4141 4267)
#endif

#include <list>
#include <map>
#include <string>

#include "Text.hh"
#include "binop.hh"
#include "exception.hh"
#include "fir_to_fir.hh"
#include "global.hh"
#include "instructions.hh"
#include "struct_manager.hh"

#include <llvm/IR/DataLayout.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>
#if LLVM_VERSION_MAJOR >= 16
#include <llvm/TargetParser/Host.h>
#else
#include <llvm/Support/Host.h>
#endif

#define LLVMBuilder llvm::IRBuilder<>*
#define LLVMModule llvm::Module*
#define LLVMFun llvm::Function*
#define LLVMGVar llvm::GlobalVariable*
#define LLVMValue llvm::Value*
#define LLVMType llvm::Type*
#define LLVMBlock llvm::BasicBlock*
#define LLVMPtrType llvm::PointerType*
#define LLVMVecTypes std::vector<LLVMType>
#define MapOfTypes std::map<Typed::VarType, LLVMType>

#define dumpLLVM(val)                            \
    {                                            \
        std::string              res;            \
        llvm::raw_string_ostream out_str(res);   \
        out_str << *val;                         \
        std::cout << out_str.str() << std::endl; \
    }

#define MakeIdx(beg, end) llvm::ArrayRef<LLVMValue>(beg, end)

#if LLVM_VERSION_MAJOR >= 12
#define GetTypeByName(name) llvm::StructType::getTypeByName(fModule->getContext(), name);
#else
#define GetTypeByName(name) fModule->getTypeByName(name);
#endif

#if LLVM_VERSION_MAJOR >= 14
#define AddAttributeAtIndex(a, b, c) a->addAttributeAtIndex(b, c)
#define MakeCreateInBoundsGEP(type, v1, v2) fBuilder->CreateInBoundsGEP(type, v1, v2);
#define MakeCreateLoad(type, var, is_volatile) fBuilder->CreateLoad(type, var, is_volatile)
#define MakeCreateLoad1(type, var) fBuilder->CreateLoad(type, var)
#else
#define AddAttributeAtIndex(a, b, c) a->addAttribute(b, c)
#define MakeCreateInBoundsGEP(type, v1, v2) fBuilder->CreateInBoundsGEP(v1, v2);
#define MakeCreateLoad(type, var, is_volatile) fBuilder->CreateLoad(var, is_volatile)
#define MakeCreateLoad1(type, var) fBuilder->CreateLoad(var)
#endif

#define MakeConstGEP32(type, llvm_name) fBuilder->CreateConstGEP2_32(type, llvm_name, 0, 0);
#define MakeIntPtrType() fModule->getDataLayout().getIntPtrType(fModule->getContext())

#if LLVM_VERSION_MAJOR >= 16
#define makeArrayRef(args) llvm::ArrayRef<LLVMType>(args)
#define CreateFuncall(fun, args) fBuilder->CreateCall(fun, llvm::ArrayRef<LLVMValue>(args))
#define InsertBlock(fun, block) fun->insert(fun->end(), block);
#else
#define CreateFuncall(fun, args) fBuilder->CreateCall(fun, makeArrayRef(args))
#define InsertBlock(fun, block) fun->getBasicBlockList().push_back(block);
#endif

#define CreatePhi(type, name) fBuilder->CreatePHI(type, 0, name);
#define GetIterator(it) &(*(it))

//=============================
// Helper class handling types
//=============================

struct LLVMTypeHelper {
    MapOfTypes fTypeMap;
    LLVMModule fModule;

    LLVMTypeHelper(LLVMModule module) : fModule(module)
    {
        // LLVM type coding
        fTypeMap[Typed::kFloat]         = getFloatTy();
        fTypeMap[Typed::kFloat_ptr]     = getTyPtr(fTypeMap[Typed::kFloat]);
        fTypeMap[Typed::kFloat_ptr_ptr] = getTyPtr(fTypeMap[Typed::kFloat_ptr]);
#if LLVM_VERSION_MAJOR < 12
        fTypeMap[Typed::kFloat_vec] =
            llvm::VectorType::get(fTypeMap[Typed::kFloat], gGlobal->gVecSize);
        fTypeMap[Typed::kFloat_vec_ptr] = getTyPtr(fTypeMap[Typed::kFloat_vec]);
#endif
        fTypeMap[Typed::kDouble]         = getDoubleTy();
        fTypeMap[Typed::kDouble_ptr]     = getTyPtr(fTypeMap[Typed::kDouble]);
        fTypeMap[Typed::kDouble_ptr_ptr] = getTyPtr(fTypeMap[Typed::kDouble_ptr]);
#if LLVM_VERSION_MAJOR < 12
        fTypeMap[Typed::kDouble_vec] =
            llvm::VectorType::get(fTypeMap[Typed::kDouble], gGlobal->gVecSize);
        fTypeMap[Typed::kDouble_vec_ptr] = getTyPtr(fTypeMap[Typed::kDouble_vec]);
#endif
        fTypeMap[Typed::kInt32]     = getInt32Ty();
        fTypeMap[Typed::kInt32_ptr] = getTyPtr(fTypeMap[Typed::kInt32]);
#if LLVM_VERSION_MAJOR < 12
        fTypeMap[Typed::kInt32_vec] =
            llvm::VectorType::get(fTypeMap[Typed::kInt32], gGlobal->gVecSize);
        fTypeMap[Typed::kInt32_vec_ptr] = getTyPtr(fTypeMap[Typed::kInt32_vec]);
#endif
        fTypeMap[Typed::kInt64]     = getInt64Ty();
        fTypeMap[Typed::kInt64_ptr] = getTyPtr(fTypeMap[Typed::kInt64]);
#if LLVM_VERSION_MAJOR < 12
        fTypeMap[Typed::kInt64_vec] =
            llvm::VectorType::get(fTypeMap[Typed::kInt64], gGlobal->gVecSize);
        fTypeMap[Typed::kInt64_vec_ptr] = getTyPtr(fTypeMap[Typed::kInt64_vec]);
#endif
        fTypeMap[Typed::kBool]     = getInt1Ty();
        fTypeMap[Typed::kBool_ptr] = getTyPtr(fTypeMap[Typed::kBool]);
#if LLVM_VERSION_MAJOR < 12
        fTypeMap[Typed::kBool_vec] =
            llvm::VectorType::get(fTypeMap[Typed::kBool], gGlobal->gVecSize);
        fTypeMap[Typed::kBool_vec_ptr] = getTyPtr(fTypeMap[Typed::kBool_vec]);
#endif
        // Takes the type of internal real
        fTypeMap[Typed::kFloatMacro]         = fTypeMap[itfloat()];
        fTypeMap[Typed::kFloatMacro_ptr]     = getTyPtr(fTypeMap[Typed::kFloatMacro]);
        fTypeMap[Typed::kFloatMacro_ptr_ptr] = getTyPtr(fTypeMap[Typed::kFloatMacro_ptr]);

        fTypeMap[Typed::kVoid] = getVoidTy();

        // void* must be defined as i8* type
        fTypeMap[Typed::kVoid_ptr] = getInt8TyPtr();

        // External structured type definition
        for (const auto& it : gGlobal->gExternalStructTypes) {
            LLVMType new_type                         = fir2LLVMType(it.second->fType);
            fTypeMap[it.first]                        = new_type;
            fTypeMap[Typed::getPtrFromType(it.first)] = getTyPtr(new_type);
        }
    }

    virtual ~LLVMTypeHelper() {}

    // Value generation
    LLVMValue genInt1(int num)
    {
        return llvm::ConstantInt::get(llvm::Type::getInt1Ty(fModule->getContext()), num);
    }
    LLVMValue genInt32(int num)
    {
        return llvm::ConstantInt::get(llvm::Type::getInt32Ty(fModule->getContext()), num);
    }
    LLVMValue genInt64(int64_t num)
    {
        return llvm::ConstantInt::get(llvm::Type::getInt64Ty(fModule->getContext()), num);
    }
    LLVMValue genFloat(float num)
    {
        return llvm::ConstantFP::get(fModule->getContext(), llvm::APFloat(num));
    }
    LLVMValue genDouble(double num)
    {
        return llvm::ConstantFP::get(fModule->getContext(), llvm::APFloat(num));
    }

    LLVMValue genArray(LLVMType type, const std::vector<llvm::Constant*>& num_array)
    {
        llvm::ArrayType* array_type = llvm::ArrayType::get(type, num_array.size());
        return llvm::ConstantArray::get(array_type, num_array);
    }

    LLVMGVar genGlobalVar(LLVMType type, bool is_const, const std::string& name)
    {
        return new llvm::GlobalVariable(*fModule, type, is_const,
                                        llvm::GlobalValue::InternalLinkage, 0, name);
    }

    // Type generation
    LLVMType getVoidTy() { return llvm::Type::getVoidTy(fModule->getContext()); }
    LLVMType getFloatTy() { return llvm::Type::getFloatTy(fModule->getContext()); }
    LLVMType getDoubleTy() { return llvm::Type::getDoubleTy(fModule->getContext()); }
    LLVMType getRealTy() { return fTypeMap[Typed::kFloatMacro]; }
    LLVMType getInt32Ty() { return llvm::Type::getInt32Ty(fModule->getContext()); }
    LLVMType getInt64Ty() { return llvm::Type::getInt64Ty(fModule->getContext()); }
    LLVMType getInt1Ty() { return llvm::Type::getInt1Ty(fModule->getContext()); }
    LLVMType getInt8Ty() { return llvm::Type::getInt8Ty(fModule->getContext()); }
    LLVMType getInt8TyPtr() { return llvm::PointerType::get(getInt8Ty(), 0); }
    LLVMType getTyPtr(LLVMType type) { return llvm::PointerType::get(type, 0); }

    /*
        Return the pointee type:
        - since LLVM ArrayType is not represented in FIR, the LLVM type is dereferenced
        - otherwise the FIR type is dereferenced
     */
    LLVMType getPtrTy(LLVMType llvm_type, Typed::VarType fir_type)
    {
        if (auto* ptr = llvm::dyn_cast<llvm::ArrayType>(llvm_type)) {
            return ptr->getElementType();
        } else if (isPtrType(fir_type)) {
            Typed::VarType fir_type1 = Typed::getTypeFromPtr(fir_type);
            faustassert(fTypeMap.find(fir_type1) != fTypeMap.end());
            return fTypeMap[fir_type1];
        } else {
            return fTypeMap[Typed::kVoid];
        }
    }

    LLVMType getStructType(const std::string& name, const LLVMVecTypes& types)
    {
        // We want to have a unique creation for struct types, so check if the given type has
        // already been created
        llvm::StructType* struct_type = GetTypeByName(name);
        if (!struct_type) {
            struct_type = llvm::StructType::create(fModule->getContext(), name);
            // Create "packed" struct type to match the size of C++ "packed" defined ones
            struct_type->setBody(makeArrayRef(types), true);
        }
        return struct_type;
    }

    // Convert FIR types to LLVM types
    LLVMType fir2LLVMType(Typed* ext_type)
    {
        BasicTyped*  basic_typed  = dynamic_cast<BasicTyped*>(ext_type);
        NamedTyped*  named_typed  = dynamic_cast<NamedTyped*>(ext_type);
        ArrayTyped*  array_typed  = dynamic_cast<ArrayTyped*>(ext_type);
        VectorTyped* vector_typed = dynamic_cast<VectorTyped*>(ext_type);
        StructTyped* struct_typed = dynamic_cast<StructTyped*>(ext_type);

        if (basic_typed) {
            return fTypeMap[basic_typed->fType];
        } else if (named_typed) {
            llvm::StructType* type = GetTypeByName(named_typed->fName);
            return (type) ? getTyPtr(type) : fir2LLVMType(named_typed->fType);
        } else if (array_typed) {
            // Arrays of 0 size are actually pointers on the type
            return (array_typed->fSize == 0)
                       ? fTypeMap[array_typed->getType()]
                       : llvm::ArrayType::get(
                             fTypeMap[Typed::getTypeFromPtr(array_typed->getType())],
                             array_typed->fSize);
        } else if (vector_typed) {
#if LLVM_VERSION_MAJOR < 12
            return llvm::VectorType::get(fTypeMap[vector_typed->fType->fType], vector_typed->fSize);
#else
            faustassert(false);
            return nullptr;
#endif
        } else if (struct_typed) {
            LLVMVecTypes llvm_types;
            for (const auto& it : struct_typed->fFields) {
                llvm_types.push_back(fir2LLVMType(it));
            }
            return getStructType("struct.dsp" + struct_typed->fName, llvm_types);
        } else {
            faustassert(false);
            return nullptr;
        }
    }
};

//=====================
// LLVM code generator
//=====================

class LLVMInstVisitor : public InstVisitor, public LLVMTypeHelper {
   private:
    // To be used for "alloca", which have to be added in the first "entry" block of the function
    LLVMBuilder fAllocaBuilder;
    // Regular buider
    LLVMBuilder fBuilder;

    // Map of [address (name), LLVMType, LLVMType pointee] containing struct fields, stack variables
    // and funArgs
    std::map<std::string, std::pair<LLVMType, LLVMType>> fVarTypes;

    StructInstVisitor* fStructVisitor;  // Contains offset of each field in the DSP struct
    LLVMValue          fCurValue;       // Current compilation result

    std::map<std::string, LLVMValue> fStackVars;    // Variables on the stack
    std::map<std::string, LLVMGVar>  fStringTable;  // Global strings

    std::list<std::string> fMathLibTable;  // All standard math functions

#if LLVM_VERSION_MAJOR >= 8
    std::map<std::string, llvm::Intrinsic::ID> fUnaryIntrinsicTable;   // LLVM unary intrinsic
    std::map<std::string, llvm::Intrinsic::ID> fBinaryIntrinsicTable;  // LLVM binary intrinsic
#endif

    void printVarTable()
    {
        for (const auto& it : fStackVars) {
            std::cout << "Stack var = " << it.first << std::endl;
        }
    }

    LLVMType getCurType() { return fCurValue->getType(); }

    LLVMValue genTypedZero() { return (getCurType() == getInt32Ty()) ? genInt32(0) : genInt64(0); }

    LLVMValue genTypedNum(LLVMType type, double num)
    {
        if (type == getInt32Ty()) {
            return genInt32(num);
        }
        if (type == getInt64Ty()) {
            return genInt64(num);
        }
        if (type == getFloatTy()) {
            return genFloat(num);
        }
        if (type == getDoubleTy()) {
            return genDouble(num);
        }
        faustassert(false);
        return nullptr;
    }

    LLVMBlock genBlock(const std::string& name, LLVMFun fun = nullptr)
    {
        return llvm::BasicBlock::Create(fModule->getContext(), name, fun);
    }

    LLVMGVar addStringConstant(std::string arg, LLVMType& type_def)
    {
        std::string str = replaceChar(unquote(arg), '@', '_');
        type_def        = llvm::ArrayType::get(getInt8Ty(), str.size() + 1);

        if (fStringTable.find(str) == fStringTable.end()) {
            fStringTable[str] = genGlobalVar(type_def, true, str);
            fStringTable[str]->setInitializer(
                llvm::ConstantDataArray::getString(fModule->getContext(), str, true));
        }

        return fStringTable[str];
    }

    // Load a struct field
    LLVMValue loadStructField(const std::string& name)
    {
        int       field_index = fStructVisitor->getFieldIndex(name);
        LLVMValue idx[]       = {genInt32(0), genInt32(field_index)};
        return MakeCreateInBoundsGEP(fTypeMap[Typed::kObj], loadFunArg("dsp"),
                                     MakeIdx(idx, idx + 2));
    }

    LLVMValue loadArrayAsPointer(LLVMValue var, LLVMType type, bool is_volatile = false)
    {
        if (llvm::isa<llvm::ArrayType>(type)) {
            LLVMValue idx[] = {genInt32(0), genInt32(0)};
            return MakeCreateInBoundsGEP(type, var, MakeIdx(idx, idx + 2));
        } else {
            return MakeCreateLoad(type, var, is_volatile);
        }
    }

    LLVMValue loadFunArg(const std::string& name)
    {
        // Get the enclosing function
        LLVMFun function = fBuilder->GetInsertBlock()->getParent();

        for (llvm::Function::arg_iterator it = function->arg_begin(); it != function->arg_end();
             ++it) {
            LLVMValue arg = GetIterator(it);
            if (arg->getName() == name) {
                return arg;
            }
        }

        faustassert(false);
        return nullptr;
    }

   public:
    LLVMInstVisitor(LLVMModule module, LLVMBuilder builder, StructInstVisitor* struct_visitor,
                    DeclareStructTypeInst* dec_type)
        : LLVMTypeHelper(module),
          fBuilder(builder),
          fStructVisitor(struct_visitor),
          fCurValue(nullptr)
    {
        // Keep [name, [type, type_pointee]]
        for (const auto& it : dec_type->fType->fFields) {
            LLVMType type            = fir2LLVMType(it);
            fVarTypes[it->getName()] = std::make_pair(type, getPtrTy(type, it->getType()));
        }

        fTypeMap[Typed::kObj]     = fir2LLVMType(dec_type->fType);
        fTypeMap[Typed::kObj_ptr] = getTyPtr(fTypeMap[Typed::kObj]);
        fAllocaBuilder            = new llvm::IRBuilder<>(fModule->getContext());

#if LLVM_VERSION_MAJOR >= 8
        /*
         This does not work in visit(FunCallInst* inst) for intrinsic, which are deactivated for now
         call_inst->addAttribute(AttributeList::FunctionIndex, Attribute::Builtin);
        */

        /*
        // Float version
        fUnaryIntrinsicTable["ceilf"] = Intrinsic::ceil;
        fUnaryIntrinsicTable["cosf"] = Intrinsic::cos;
        fUnaryIntrinsicTable["expf"] = Intrinsic::exp;
        fUnaryIntrinsicTable["floorf"] = Intrinsic::floor;
        fUnaryIntrinsicTable["logf"] = Intrinsic::log;
        fUnaryIntrinsicTable["log10f"] = Intrinsic::log10;
        fUnaryIntrinsicTable["rintf"] = Intrinsic::rint;
        fUnaryIntrinsicTable["roundf"] = Intrinsic::round;
        fUnaryIntrinsicTable["sqrtf"] = Intrinsic::sqrt;
        fBinaryIntrinsicTable["powf"] = Intrinsic::pow;
        fUnaryIntrinsicTable["sinf"] = Intrinsic::sin;

        // Double version
        fUnaryIntrinsicTable["ceil"] = Intrinsic::ceil;
        fUnaryIntrinsicTable["cos"] = Intrinsic::cos;
        fUnaryIntrinsicTable["exp"] = Intrinsic::exp;
        fUnaryIntrinsicTable["floor"] = Intrinsic::floor;
        fUnaryIntrinsicTable["log"] = Intrinsic::log;
        fUnaryIntrinsicTable["log10"] = Intrinsic::log10;
        fUnaryIntrinsicTable["rint"] = Intrinsic::rint;
        fUnaryIntrinsicTable["round"] = Intrinsic::round;
        fUnaryIntrinsicTable["sqrt"] = Intrinsic::sqrt;
        fBinaryIntrinsicTable["pow"] = Intrinsic::pow;
        fUnaryIntrinsicTable["sin"] = Intrinsic::sin;
        */
#endif

        fMathLibTable = {
            // Integer version
            "abs",

            // Float version
            "fabsf", "acosf", "asinf", "atanf", "atan2f", "ceilf", "cosf", "expf", "exp10f",
            "floorf", "fmodf", "logf", "log10f", "powf", "rintf", "roundf", "sinf", "sqrtf", "tanf",
            "acoshf", "asinhf", "atanhf", "coshf", "sinhf", "tanhf",

            // Double version
            "fabs", "acos", "asin", "atan", "atan2", "ceil", "cos", "exp", "exp10", "floor", "fmod",
            "log", "log10f", "pow", "rint", "round", "sin", "sqrt", "tan", "acosh", "asinh",
            "atanh", "cosh", "sinh", "tanh"};
    }

    virtual ~LLVMInstVisitor() { delete fAllocaBuilder; }

    //========
    // String
    //========

    LLVMValue genStringConstant(const std::string& label)
    {
        // Gen LLVM constant string
        LLVMType type = nullptr;
        LLVMGVar var  = addStringConstant(label, type);
        return MakeConstGEP32(type, var);
    }

    //==============
    // Declarations
    //==============

    virtual void visit(DeclareVarInst* inst)
    {
        std::string         name   = inst->fAddress->getName();
        Address::AccessType access = inst->fAddress->getAccess();
        LLVMType            type   = fir2LLVMType(inst->fType);

        if (access & Address::kStack || access & Address::kLoop) {
            // Always at the begining since the block is already branched to next one...
            fAllocaBuilder->SetInsertPoint(
                GetIterator(fAllocaBuilder->GetInsertBlock()->getFirstInsertionPt()));
            fCurValue = fAllocaBuilder->CreateAlloca(type);

            fCurValue->setName(name);
            fStackVars[name] = fCurValue;  // Keep stack variables

            // Declaration with a value
            if (inst->fValue) {
                // Result is in fCurValue;
                inst->fValue->accept(this);
                genStore(fStackVars[name], fCurValue, false);
            }

        } else if (access & Address::kGlobal || access & Address::kStaticStruct) {
            LLVMGVar gvalue = genGlobalVar(type, (access & Address::kConst), name);

            // Declaration with a value
            if (inst->fValue) {
                // Result is in fCurValue;
                inst->fValue->accept(this);
                gvalue->setInitializer(static_cast<llvm::Constant*>(fCurValue));
            } else {
                // Init with typed zero
                gvalue->setInitializer(llvm::Constant::getNullValue(type));
            }

        } else {
            faustassert(false);
        }

        // Keep [name, [type, type_pointee]]
        fVarTypes[name] = std::make_pair(type, getPtrTy(type, inst->fType->getType()));

        // No result in fCurValue
        fCurValue = nullptr;
    }

    virtual void visit(DeclareFunInst* inst)
    {
        LLVMFun function = fModule->getFunction(inst->fName);

        // Define it
        if (!function) {
            // Min/max are internally generated
            if (checkMinMax(inst->fName)) {
                goto end;
            }

            // Return type
            LLVMType return_type = fTypeMap[inst->getResType()];

            // Prepare vector of LLVM types for args
            LLVMVecTypes fun_args_type;
            for (const auto& it : inst->fType->fArgsTypes) {
                LLVMType type = fTypeMap[it->getType()];
                fun_args_type.push_back(type);
                // Keep [name, [type, type_pointee]]
                fVarTypes[it->getName()] = std::make_pair(type, getPtrTy(type, it->getType()));
            }

            // Creates function
            llvm::FunctionType* fun_type =
                llvm::FunctionType::get(return_type, makeArrayRef(fun_args_type), false);
            function = llvm::Function::Create(fun_type,
                                              (inst->fType->fAttribute & FunTyped::kLocal ||
                                               inst->fType->fAttribute & FunTyped::kStatic)
                                                  ? llvm::GlobalValue::InternalLinkage
                                                  : llvm::GlobalValue::ExternalLinkage,
                                              inst->fName, fModule);

            // In order for auto-vectorization to correctly work with vectorizable math functions
            if (find(fMathLibTable.begin(), fMathLibTable.end(), inst->fName) !=
                fMathLibTable.end()) {
                function->setDoesNotAccessMemory();
            }
            function->setDoesNotThrow();

            // Set name and 'noalias' (on pointers) for function arguments
            llvm::Function::arg_iterator args      = function->arg_begin();
            int                          arg_index = 0;
            for (const auto& it : inst->fType->fArgsTypes) {
                LLVMValue arg = GetIterator(args++);
                arg->setName(it->fName);
                // Pointers are set with 'noalias' for non paired arguments, which are garantied to
                // be unique
                // TODO: better associate a proper kNoalias atribute at FIR creation time
                if (isPtrType(it->getType()) && !inst->fType->isPairedFunArg(it->fName)) {
                    function->addParamAttr(arg_index, llvm::Attribute::NoAlias);
                }
                arg_index++;
            }

            // If there is a body, compile it
            if (inst->fCode->fCode.size() > 0) {
                // Prepare a entry_block to insert into
                LLVMBlock entry_block = genBlock("entry_block", function);

                fBuilder->SetInsertPoint(entry_block);
                // "Alloca" in first "entry_bock" are mandatory so that vectorization passes
                // correctly work
                fAllocaBuilder->SetInsertPoint(entry_block);

                // Compile code in this block
                inst->fCode->accept(this);
                verifyFunction(*function);

                // Clear inserting points
                fBuilder->ClearInsertionPoint();
                fAllocaBuilder->ClearInsertionPoint();
            }
        }

    end:
        // No result in fCurValue
        fCurValue = nullptr;
    }

    //==========
    // Adresses
    //==========

    LLVMValue visitNameAddress(NamedAddress* named_address)
    {
        std::string         name   = named_address->fName;
        Address::AccessType access = named_address->fAccess;

        if (access & Address::kStruct) {
            return loadStructField(name);
        } else if (access & Address::kFunArgs) {
            return loadFunArg(name);
        } else if (access & Address::kStack || access & Address::kLoop) {
            faustassert(fStackVars.find(name) != fStackVars.end());
            return fStackVars[name];
        } else if ((access & Address::kGlobal) || (access & Address::kStaticStruct)) {
            return fModule->getGlobalVariable(name, true);
        } else {
            faustassert(false);
            return nullptr;
        }
    }

    LLVMValue visitIndexedAddress(IndexedAddress* indexed_address, LLVMType& res_type)
    {
        NamedAddress* named_address = dynamic_cast<NamedAddress*>(indexed_address->fAddress);
        faustassert(named_address);  // One level indexation for now

        // Compute index, result is in fCurValue
        indexed_address->getIndex()->accept(this);
        Address::AccessType access = named_address->fAccess;
        std::string         name   = named_address->fName;

        faustassert(fVarTypes.find(name) != fVarTypes.end());

        LLVMValue load_ptr;
        LLVMType  type1 = fVarTypes[name].first;
        LLVMType  type2 = fVarTypes[name].second;

        if (access & Address::kStruct) {
            load_ptr = loadArrayAsPointer(loadStructField(name), type1);
        } else if (access & Address::kFunArgs) {
            load_ptr = loadFunArg(name);
        } else if (access & Address::kStack || access & Address::kLoop) {
            // We want to see array like [256 x float] as a float*
            load_ptr = loadArrayAsPointer(fStackVars[name], type1);
        } else if (access & Address::kGlobal || access & Address::kStaticStruct) {
            // We want to see array like [256 x float] as a float*
            load_ptr = loadArrayAsPointer(fModule->getGlobalVariable(name, true), type1);
        } else {
            faustassert(false);
            return nullptr;
        }

        // Indexed adresses can actually be values in an array or fields in a struct type
        if (isStructType(indexed_address->getName())) {
            /*
                We only have external soundfile structure for now, the struct field type is
               returned.
             */
            res_type = llvm::dyn_cast<llvm::StructType>(fTypeMap[Typed::kSound])
                           ->getTypeAtIndex(fCurValue);
            LLVMValue idx[] = {genInt32(0), fCurValue};
            return MakeCreateInBoundsGEP(type2, load_ptr, MakeIdx(idx, idx + 2));
        } else {
            res_type = type2;
            return MakeCreateInBoundsGEP(type2, load_ptr, fCurValue);
        }
    }

    virtual LLVMValue visit(Address* address)
    {
        NamedAddress*   named_address   = dynamic_cast<NamedAddress*>(address);
        IndexedAddress* indexed_address = dynamic_cast<IndexedAddress*>(address);

        if (named_address) {
            return visitNameAddress(named_address);
        } else if (indexed_address) {
            LLVMType unused = nullptr;
            return visitIndexedAddress(indexed_address, unused);
        } else {
            faustassert(false);
            return nullptr;
        }
    }

    //=============
    // LoadVarInst
    //=============

    virtual void visit(LoadVarInst* inst)
    {
        NamedAddress*   named_address   = dynamic_cast<NamedAddress*>(inst->fAddress);
        IndexedAddress* indexed_address = dynamic_cast<IndexedAddress*>(inst->fAddress);

        if (named_address) {
            LLVMValue value = visitNameAddress(named_address);
            if (named_address->isFunArgs()) {
                fCurValue = value;
            } else {
                std::string name = named_address->fName;
                faustassert(fVarTypes.find(name) != fVarTypes.end());
                // We want to see array like [256 x float] as a float*
                fCurValue =
                    loadArrayAsPointer(value, fVarTypes[name].first, named_address->isVolatile());
            }
        } else if (indexed_address) {
            faustassert(fVarTypes.find(indexed_address->getName()) != fVarTypes.end());
            LLVMType  type     = nullptr;
            LLVMValue load_ptr = visitIndexedAddress(indexed_address, type);
            fCurValue          = MakeCreateLoad1(type, load_ptr);
        } else {
            faustassert(false);
        }
    }

    //====================
    // LoadVarAddressInst
    //====================

    virtual void visit(LoadVarAddressInst* inst) { fCurValue = visit(inst->fAddress); }

    //==============
    // StoreVarInst
    //==============

    void genStore(LLVMValue store_ptr, LLVMValue store, bool is_volatile)
    {
        // HACK : special case if we store a 0 (null pointer) in an address
        // (used in vec mode and in "allocate" function in scheduler mode...)
        LLVMType type = store_ptr->getType();
        if ((type != getTyPtr(store->getType())) &&
            (type == getInt32Ty() || type == getInt64Ty())) {
            store =
                llvm::ConstantPointerNull::get(static_cast<LLVMPtrType>(type->getContainedType(0)));
        }
        fBuilder->CreateStore(store, store_ptr, is_volatile);
    }

    virtual void visit(StoreVarInst* inst)
    {
        LLVMValue store_ptr = visit(inst->fAddress);

        // Result is in fCurValue;
        inst->fValue->accept(this);
        genStore(store_ptr, fCurValue, inst->fAddress->isVolatile());

        // No result in fCurValue
        fCurValue = nullptr;
    }

    //=========
    // Numbers
    //=========

    virtual void visit(FloatNumInst* inst) { fCurValue = genFloat(inst->fNum); }

    virtual void visit(FloatArrayNumInst* inst)
    {
        std::vector<llvm::Constant*> num_array;
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            num_array.push_back(static_cast<llvm::ConstantFP*>(genFloat(inst->fNumTable[i])));
        }
        fCurValue = genArray(getFloatTy(), num_array);
    }

    virtual void visit(DoubleNumInst* inst) { fCurValue = genDouble(inst->fNum); }

    virtual void visit(DoubleArrayNumInst* inst)
    {
        std::vector<llvm::Constant*> num_array;
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            num_array.push_back(static_cast<llvm::ConstantFP*>(genDouble(inst->fNumTable[i])));
        }
        fCurValue = genArray(getDoubleTy(), num_array);
    }

    virtual void visit(Int32NumInst* inst) { fCurValue = genInt32(inst->fNum); }

    virtual void visit(Int32ArrayNumInst* inst)
    {
        std::vector<llvm::Constant*> num_array;
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            num_array.push_back(static_cast<llvm::ConstantFP*>(genInt32(inst->fNumTable[i])));
        }
        fCurValue = genArray(getInt32Ty(), num_array);
    }

    virtual void visit(BoolNumInst* inst) { fCurValue = genInt1(inst->fNum); }

    virtual void visit(Int64NumInst* inst) { fCurValue = genInt64(inst->fNum); }

    //======
    // Unop
    //======

    virtual void visit(MinusInst* inst)
    {
        inst->fInst->accept(this);
        if (getCurType() == getInt32Ty()) {
            fCurValue = fBuilder->CreateNeg(fCurValue);
        } else if (getCurType() == getFloatTy() || getCurType() == getDoubleTy()) {
            fCurValue = fBuilder->CreateFNeg(fCurValue);
        } else {
            // Simply multiply the value by -1 here
            fCurValue = generateBinop(kMul, genTypedNum(getCurType(), -1.), fCurValue);
        }
    }

    //=======
    // Binop
    //=======

    virtual void visit(BinopInst* inst)
    {
        // Keep result of first arg compilation
        inst->fInst1->accept(this);
        LLVMValue res1 = fCurValue;

        // Keep result of second arg compilation
        inst->fInst2->accept(this);
        LLVMValue res2 = fCurValue;

        fCurValue = generateBinop(inst->fOpcode, res1, res2);
    }

    //======
    // Cast
    //======

    virtual void visit(::CastInst* inst)
    {
        // Compile instruction to be casted, result in fCurValue
        inst->fInst->accept(this);
        visitCast(inst->fType->getType());
    }

    void visitCast(Typed::VarType type)
    {
        switch (type) {
            case Typed::kInt32:
                if (getCurType() == getInt32Ty()) {
                    // Nothing to do
                } else if (getCurType() == getFloatTy() || getCurType() == getDoubleTy()) {
                    fCurValue = fBuilder->CreateFPToSI(fCurValue, getInt32Ty());
                } else if (getCurType() == getInt64Ty()) {
                    fCurValue = fBuilder->CreateTrunc(fCurValue, getInt32Ty());
                } else if (getCurType()->isPointerTy()) {
                    // Use BitCast for pointer to kInt32
                    fCurValue = fBuilder->CreateBitCast(fCurValue, getInt32Ty());
                } else {
                    faustassert(false);
                }
                break;

            case Typed::kFloat:
                if (getCurType() == getInt32Ty() || getCurType() == getInt64Ty()) {
                    fCurValue = fBuilder->CreateSIToFP(fCurValue, getFloatTy());
                } else if (getCurType() == getFloatTy()) {
                    // Nothing to do
                } else if (getCurType() == getDoubleTy()) {
                    fCurValue = fBuilder->CreateFPTrunc(fCurValue, getFloatTy());
                } else {
                    faustassert(false);
                }
                break;

            case Typed::kDouble:
                if (getCurType() == getInt32Ty() || getCurType() == getInt64Ty()) {
                    fCurValue = fBuilder->CreateSIToFP(fCurValue, getDoubleTy());
                } else if (getCurType() == getFloatTy()) {
                    fCurValue = fBuilder->CreateFPExt(fCurValue, getDoubleTy());
                } else if (getCurType() == getDoubleTy()) {
                    // Nothing to do
                } else {
                    faustassert(false);
                }
                break;

            case Typed::kFloat_ptr:
            case Typed::kFloat_ptr_ptr:
            case Typed::kDouble_ptr:
            case Typed::kDouble_ptr_ptr:
            case Typed::kInt32_ptr:
            case Typed::kFloatMacro_ptr:
            case Typed::kFloatMacro_ptr_ptr:
            case Typed::kObj_ptr:
            case Typed::kVoid_ptr:
                fCurValue = fBuilder->CreateBitCast(fCurValue, fTypeMap[type]);
                break;

            case Typed::kUint_ptr:
                fCurValue = fBuilder->CreatePtrToInt(fCurValue, MakeIntPtrType());
                break;

            case Typed::kQuad:
            case Typed::kInt64:
            default:
                faustassert(false);
                break;
        }
    }

    virtual void visit(::BitcastInst* inst)
    {
        // Compile exp to bitcast, result in fCurValue
        inst->fInst->accept(this);
        fCurValue = fBuilder->CreateBitCast(fCurValue, fTypeMap[inst->fType->getType()]);
    }

    //=========
    // Control
    //=========

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

    virtual void visit(FunCallInst* inst)
    {
        // Compile function arguments
        std::vector<LLVMValue> fun_args;
        for (const auto& it : inst->fArgs) {
            // Each argument is compiled and result is in fCurValue
            it->accept(this);
            fun_args.push_back(fCurValue);
        }

        // Min/max are internally generated
        if (checkMin(inst->fName) && fun_args.size() == 2) {
            fCurValue = generateFunPolymorphicMinMax(fun_args[0], fun_args[1], kLT);
        } else if (checkMax(inst->fName) && fun_args.size() == 2) {
            fCurValue = generateFunPolymorphicMinMax(fun_args[0], fun_args[1], kGT);
#if LLVM_VERSION_MAJOR >= 8
            // LLVM unary intrinsic
        } else if (fUnaryIntrinsicTable.find(inst->fName) != fUnaryIntrinsicTable.end()) {
            llvm::CallInst* call_inst =
                fBuilder->CreateUnaryIntrinsic(fUnaryIntrinsicTable[inst->fName], fun_args[0]);
            AddAttributeAtIndex(call_inst, llvm::AttributeList::FunctionIndex,
                                llvm::Attribute::Builtin);
            fCurValue = call_inst;

            // LLVM binary intrinsic
        } else if (fBinaryIntrinsicTable.find(inst->fName) != fBinaryIntrinsicTable.end()) {
            llvm::Value* value_inst = fBuilder->CreateBinaryIntrinsic(
                fBinaryIntrinsicTable[inst->fName], fun_args[0], fun_args[1]);
            llvm::CallInst* call_inst = llvm::dyn_cast<llvm::CallInst>(value_inst);
            if (call_inst) {
                AddAttributeAtIndex(call_inst, llvm::AttributeList::FunctionIndex,
                                    llvm::Attribute::Builtin);
            } else {
                faustassert(false);
            }
            fCurValue = value_inst;
#endif
        } else {
            // Get function in the module
            LLVMFun function = fModule->getFunction(gGlobal->getMathFunction(inst->fName));
            faustassert(function);

            // Result is function call
            llvm::CallInst* call_inst = CreateFuncall(function, fun_args);
            AddAttributeAtIndex(call_inst, llvm::AttributeList::FunctionIndex,
                                llvm::Attribute::Builtin);
            fCurValue = call_inst;
        }
    }

    /*
    // Strict select
    virtual void visit(Select2Inst* inst)
    {
        visitSelect(inst);
    }
    */

    // Non-strict select
    virtual void visit(Select2Inst* inst) { visitIf(inst); }

    // Select that computes both branches
    void visitSelect(Select2Inst* inst)
    {
        // Compile condition, result in fCurValue
        inst->fCond->accept(this);

        // Compare condition to 0
        LLVMValue cond_value =
            fBuilder->CreateICmp(llvm::ICmpInst::ICMP_NE, fCurValue, genTypedZero());

        // Compile then branch, result in fCurValue
        inst->fThen->accept(this);
        LLVMValue then_value = fCurValue;

        // Compile else branch, result in fCurValue
        inst->fElse->accept(this);
        LLVMValue else_value = fCurValue;

        // Creates the result
        fCurValue = fBuilder->CreateSelect(cond_value, then_value, else_value);
    }

    /*
     Select that only computes one branch.

     This could be implemented using a PHI node (to group the result of the 'then' and 'else'
     blocks) but is more complicated to do when hierarchical 'select' are compiled.

     Thus we create a local variable that is written in 'then' and 'else' blocks,
     and loaded in the 'merge' block.

     LLVM passes will later one create a unique PHI node that groups all results,
     especially when hierarchical 'select' are compiled.
    */
    virtual void visitIf(Select2Inst* inst)
    {
        // Compile condition, result in fCurValue
        inst->fCond->accept(this);

        // Compare condition to 0
        LLVMValue cond_value =
            fBuilder->CreateICmp(llvm::ICmpInst::ICMP_NE, fCurValue, genTypedZero());

        // Get enclosing function
        LLVMFun function = fBuilder->GetInsertBlock()->getParent();

        // Create blocks for the then and else cases. Insert the 'merge_block' block at the end of
        // the function
        LLVMBlock then_block  = genBlock("select_then_block", function);
        LLVMBlock else_block  = genBlock("select_else_block");
        LLVMBlock merge_block = genBlock("select_merge_block");

        fBuilder->CreateCondBr(cond_value, then_block, else_block);

        // Emit then block
        fBuilder->SetInsertPoint(then_block);

        // Compile then branch
        inst->fThen->accept(this);

        // Create typed local variable

        // Always at the begining since the block is already branched to next one...
        fAllocaBuilder->SetInsertPoint(
            GetIterator(fAllocaBuilder->GetInsertBlock()->getFirstInsertionPt()));
        LLVMType  cur_type  = getCurType();
        LLVMValue typed_res = fAllocaBuilder->CreateAlloca(cur_type, nullptr, "select_res");

        // "Then" is a BlockInst, result is in fCurValue
        fBuilder->CreateStore(fCurValue, typed_res);

        // Branch in merge_block
        fBuilder->CreateBr(merge_block);

        // Emit else block
        InsertBlock(function, else_block);
        fBuilder->SetInsertPoint(else_block);

        // Compile else branch
        inst->fElse->accept(this);

        // "Else" is a BlockInst, result is in fCurValue
        fBuilder->CreateStore(fCurValue, typed_res);

        // Branch in merge_block
        fBuilder->CreateBr(merge_block);

        // Emit merge block
        InsertBlock(function, merge_block);
        fBuilder->SetInsertPoint(merge_block);
        fCurValue = MakeCreateLoad1(cur_type, typed_res);
    }

    virtual void visit(IfInst* inst)
    {
        // Compile condition, result in fCurValue
        inst->fCond->accept(this);

        // Compare condition to 0
        LLVMValue cond_value =
            fBuilder->CreateICmp(llvm::ICmpInst::ICMP_NE, fCurValue, genTypedZero());

        // Get enclosing function
        LLVMFun function = fBuilder->GetInsertBlock()->getParent();

        // Create blocks for the then and else cases. Insert the 'merge_block' block at the end of
        // the function
        LLVMBlock then_block  = genBlock("if_then_block", function);
        LLVMBlock else_block  = genBlock("if_else_block");
        LLVMBlock merge_block = genBlock("if_merge_block");

        fBuilder->CreateCondBr(cond_value, then_block, else_block);

        // Emit then block
        fBuilder->SetInsertPoint(then_block);

        // Compile then branch
        inst->fThen->accept(this);
        // "Then" is a BlockInst, so no result in fCurValue

        // Branch in merge_block
        fBuilder->CreateBr(merge_block);

        // Emit else block
        InsertBlock(function, else_block);
        fBuilder->SetInsertPoint(else_block);

        // Compile else branch
        inst->fElse->accept(this);
        // "Else" is a BlockInst, so no result in fCurValue

        // Branch in merge_block
        fBuilder->CreateBr(merge_block);

        // Emit merge block
        InsertBlock(function, merge_block);
        fBuilder->SetInsertPoint(merge_block);

        // No result in fCurValue
        fCurValue = nullptr;
    }

    virtual void visit(ForLoopInst* inst)
    {
        // Don't generate empty loops...
        if (inst->fCode->size() == 0) {
            return;
        }

        LLVMFun function = fBuilder->GetInsertBlock()->getParent();
        faustassert(function);

        // Create init_block
        LLVMBlock init_block = genBlock("init_block", function);

        // Create test_block
        LLVMBlock test_block = genBlock("test_block", function);

        // Create loop_body_block
        LLVMBlock loop_body_block = genBlock("loop_body_block", function);

        // Create exit_block
        LLVMBlock exit_block = genBlock("exit_block", function);

        // Init condition section
        {
            // Link previous_block and init_block
            fBuilder->CreateBr(init_block);

            // Start insertion in init_block
            fBuilder->SetInsertPoint(init_block);

            // Compute init value, now loop counter is allocated
            inst->fInit->accept(this);

            // Link init_block and test_block
            fBuilder->CreateBr(test_block);

            // Start insertion in test_block
            fBuilder->SetInsertPoint(test_block);
        }

        // Get loop counter local variable
        std::string loop_counter_name = inst->getName();

        // Start the PHI node with an entry for start
        llvm::PHINode* phi_node = CreatePhi(getInt32Ty(), loop_counter_name);
        phi_node->addIncoming(genInt32(0), init_block);

        // End condition section
        {
            // Compute end condition, result in fCurValue
            inst->fEnd->accept(this);

            // Compare condition to 0
            LLVMValue end_cond =
                fBuilder->CreateICmp(llvm::ICmpInst::ICMP_NE, fCurValue, genTypedZero());

            // Insert the conditional branch into the last block of loop
            fBuilder->CreateCondBr(end_cond, loop_body_block, exit_block);
        }

        // Loop body section
        {
            // Start insertion in loop_body_block
            fBuilder->SetInsertPoint(loop_body_block);

            // Generates loop internal code
            inst->fCode->accept(this);
        }

        // Get last block of post code section
        LLVMBlock current_block = fBuilder->GetInsertBlock();

        // Increment section
        {
            // Compile increment, result in fCurValue
            StoreVarInst* store_inst1 = dynamic_cast<StoreVarInst*>(inst->fIncrement);
            store_inst1->fValue->accept(this);
            LLVMValue next_index = fCurValue;
            next_index->setName("next_index");

            // Store the next value
            fBuilder->CreateStore(next_index, fStackVars[loop_counter_name]);

            // Add a new entry to the PHI node for the backedge
            phi_node->addIncoming(next_index, current_block);

            // Back to start of loop
            fBuilder->CreateBr(test_block);
        }

        // Move insertion in exit_block
        fBuilder->SetInsertPoint(exit_block);

        // No result in fCurValue
        fCurValue = nullptr;
    }

    virtual void visit(WhileLoopInst* inst)
    {
        LLVMFun function = fBuilder->GetInsertBlock()->getParent();
        faustassert(function);

        // Prepare cond_block block
        LLVMBlock cond_block = genBlock("cond_block", function);

        // Link previous_block and cond_block
        fBuilder->CreateBr(cond_block);

        // Start insertion in cond_block
        fBuilder->SetInsertPoint(cond_block);

        // Compile condition, result in fCurValue
        inst->fCond->accept(this);

        // Create the test_block and insert it
        LLVMBlock test_block = genBlock("test_block", function);

        // Create the exit_block and insert it
        LLVMBlock exit_block = genBlock("exit_block", function);

        // Compare condition to 0
        LLVMValue end_cond =
            fBuilder->CreateICmp(llvm::ICmpInst::ICMP_NE, fCurValue, genTypedZero());

        // Insert the conditional branch into the end of cond_block
        fBuilder->CreateCondBr(end_cond, test_block, exit_block);

        // Move insertion in test_block
        fBuilder->SetInsertPoint(test_block);

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
            LLVMFun function = fBuilder->GetInsertBlock()->getParent();
            faustassert(function);

            // Prepare code_block block
            LLVMBlock code_block = genBlock("code_block", function);

            // Link previous_block and code_block
            fBuilder->CreateBr(code_block);

            // Start insertion in code_block
            fBuilder->SetInsertPoint(code_block);
        }

        // Generates block internal code
        for (const auto& it : inst->fCode) {
            it->accept(this);
        }

        // No result in fCurValue
        fCurValue = nullptr;
    }

    virtual void visit(::SwitchInst* inst)
    {
        LLVMFun function = fBuilder->GetInsertBlock()->getParent();
        faustassert(function);

        // Prepare init_code block
        LLVMBlock init_block = genBlock("init_block", function);

        // Prepare exit_block block
        LLVMBlock exit_block = genBlock("exit_block", function);

        // Link previous_block and init_block
        fBuilder->CreateBr(init_block);

        // Start insertion in init_block
        fBuilder->SetInsertPoint(init_block);

        // Compile condition, result in fCurValue
        inst->fCond->accept(this);

        // Creates "default" block
        LLVMBlock default_block = genBlock("default_block", function);

        // Creates switch
        llvm::SwitchInst* switch_inst =
            fBuilder->CreateSwitch(fCurValue, default_block, inst->fCode.size());

        std::list<std::pair<int, BlockInst*>>::const_iterator it;
        for (it = inst->fCode.begin(); it != inst->fCode.end(); it++) {
            if ((*it).first != -1) {  // All cases but "default"
                // Creates "case" block
                LLVMBlock case_block = genBlock("case_block", function);
                // Move insertion in case_block
                fBuilder->SetInsertPoint(case_block);
                // Compiles "case" block
                (*it).second->accept(this);
                // Link init_block and exit_block
                fBuilder->CreateBr(exit_block);
                // Add it into the switch
                switch_inst->addCase(static_cast<llvm::ConstantInt*>(genInt32((*it).first)),
                                     case_block);
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

    //=============
    // Helper code
    //=============

    LLVMValue generateBinop(int opcode, LLVMValue arg1, LLVMValue arg2)
    {
        // Arguments are casted if needed in InstructionsCompiler::generateBinOp
        faustassert(arg1->getType() == arg2->getType());

        if (arg1->getType() == getFloatTy() || arg1->getType() == getDoubleTy()) {
            return generateBinOpReal(opcode, arg1, arg2);
        } else if (arg1->getType() == getInt32Ty() || arg1->getType() == getInt64Ty()) {
            return generateBinOpInt(opcode, arg1, arg2);
        } else {
            faustassert(false);
            return nullptr;
        }
    }

    LLVMValue generateBinOpReal(int opcode, LLVMValue arg1, LLVMValue arg2)
    {
        if (isBoolOpcode(opcode)) {
            LLVMValue comp_value = fBuilder->CreateFCmp(
                (llvm::CmpInst::Predicate)gBinOpTable[opcode]->fLLVMFloatInst, arg1, arg2);
            // Inst result for comparison
            return fBuilder->CreateSelect(comp_value, genInt32(1), genInt32(0));
        } else {
            LLVMValue value = fBuilder->CreateBinOp(
                (llvm::Instruction::BinaryOps)gBinOpTable[opcode]->fLLVMFloatInst, arg1, arg2);
            llvm::Instruction* inst = llvm::cast<llvm::Instruction>(value);
            if (!gGlobal->isOpt("FAUST_LLVM_NO_FM")) {
                inst->setMetadata(llvm::LLVMContext::MD_fpmath, fBuilder->getDefaultFPMathTag());
                inst->setFastMathFlags(fBuilder->getFastMathFlags());
            }
            return inst;
        }
    }

    LLVMValue generateBinOpInt(int opcode, LLVMValue arg1, LLVMValue arg2)
    {
        if (isBoolOpcode(opcode)) {
            LLVMValue comp_value = fBuilder->CreateICmp(
                (llvm::CmpInst::Predicate)gBinOpTable[opcode]->fLLVMIntInst, arg1, arg2);
            // Inst result for comparison
            return fBuilder->CreateSelect(comp_value, genInt32(1), genInt32(0));
        } else {
            return fBuilder->CreateBinOp(
                (llvm::Instruction::BinaryOps)gBinOpTable[opcode]->fLLVMIntInst, arg1, arg2);
        }
    }

    LLVMValue generateFunPolymorphicMinMax(LLVMValue arg1, LLVMValue arg2, int comp)
    {
        faustassert(arg1->getType() == arg2->getType());

        if (arg1->getType() == getFloatTy() || arg1->getType() == getDoubleTy()) {
            return (comp == kLT) ? fBuilder->CreateMinNum(arg1, arg2)
                                 : fBuilder->CreateMaxNum(arg1, arg2);
        } else if (arg1->getType() == getInt32Ty()) {
            LLVMValue comp_value = fBuilder->CreateICmp(
                (llvm::CmpInst::Predicate)gBinOpTable[comp]->fLLVMIntInst, arg1, arg2);
            return fBuilder->CreateSelect(comp_value, arg1, arg2);
        } else {
            faustassert(false);
            return nullptr;
        }
    }
};

#endif
