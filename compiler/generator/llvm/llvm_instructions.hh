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

#if defined(LLVM_35) || defined(LLVM_38)
#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS
#endif

#include <llvm/IR/DataLayout.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>

#define LLVMValue llvm::Value*
#define LLVMType llvm::Type*
#define GetIterator(it) &(*(it))
#define LLVMVecTypes vector<LLVMType>
#define MapOfTtypes map<Typed::VarType, LLVMType>
#define MakeIdx(beg, end) llvm::ArrayRef<LLVMValue>(beg, end)
#define MakeArgs(args) llvm::ArrayRef<lLLVMValue>(args)
#define CreateCall(fun, args) fBuilder->CreateCall(fun, makeArrayRef(args))
#define CreatePhi(type, name) fBuilder->CreatePHI(type, 0, name);

#define dumpLLVM(val)                    \
    {                                    \
        string             res;          \
        raw_string_ostream out_str(res); \
        out_str << *val;                 \
        cout << out_str.str() << endl;   \
    }

using namespace llvm;

// Helper class

struct LLVMTypeHelper {
    MapOfTtypes fTypeMap;
    Module*     fModule;

    LLVMTypeHelper(Module* module) : fModule(module)
    {
        // LLVM type coding
        fTypeMap[Typed::kFloat]         = getFloatTy();
        fTypeMap[Typed::kFloat_ptr]     = getTyPtr(fTypeMap[Typed::kFloat]);
        fTypeMap[Typed::kFloat_ptr_ptr] = getTyPtr(fTypeMap[Typed::kFloat_ptr]);
        fTypeMap[Typed::kFloat_vec]     = VectorType::get(fTypeMap[Typed::kFloat], gGlobal->gVecSize);
        fTypeMap[Typed::kFloat_vec_ptr] = getTyPtr(fTypeMap[Typed::kFloat_vec]);

        fTypeMap[Typed::kDouble]         = getDoubleTy();
        fTypeMap[Typed::kDouble_ptr]     = getTyPtr(fTypeMap[Typed::kDouble]);
        fTypeMap[Typed::kDouble_ptr_ptr] = getTyPtr(fTypeMap[Typed::kDouble_ptr]);
        fTypeMap[Typed::kDouble_vec]     = VectorType::get(fTypeMap[Typed::kDouble], gGlobal->gVecSize);
        fTypeMap[Typed::kDouble_vec_ptr] = getTyPtr(fTypeMap[Typed::kDouble_vec]);

        fTypeMap[Typed::kInt32]         = getInt32Ty();
        fTypeMap[Typed::kInt32_ptr]     = getTyPtr(fTypeMap[Typed::kInt32]);
        fTypeMap[Typed::kInt32_vec]     = VectorType::get(fTypeMap[Typed::kInt32], gGlobal->gVecSize);
        fTypeMap[Typed::kInt32_vec_ptr] = getTyPtr(fTypeMap[Typed::kInt32_vec]);

        fTypeMap[Typed::kInt64]         = getInt64Ty();
        fTypeMap[Typed::kInt64_ptr]     = getTyPtr(fTypeMap[Typed::kInt64]);
        fTypeMap[Typed::kInt64_vec]     = VectorType::get(fTypeMap[Typed::kInt64], gGlobal->gVecSize);
        fTypeMap[Typed::kInt64_vec_ptr] = getTyPtr(fTypeMap[Typed::kInt64_vec]);

        fTypeMap[Typed::kBool]         = getInt1Ty();
        fTypeMap[Typed::kBool_ptr]     = getTyPtr(fTypeMap[Typed::kBool]);
        fTypeMap[Typed::kBool_vec]     = VectorType::get(fTypeMap[Typed::kBool], gGlobal->gVecSize);
        fTypeMap[Typed::kBool_vec_ptr] = getTyPtr(fTypeMap[Typed::kBool_vec]);

        // Takes the type of internal real
        fTypeMap[Typed::kFloatMacro]         = fTypeMap[itfloat()];
        fTypeMap[Typed::kFloatMacro_ptr]     = getTyPtr(fTypeMap[Typed::kFloatMacro]);
        fTypeMap[Typed::kFloatMacro_ptr_ptr] = getTyPtr(fTypeMap[Typed::kFloatMacro_ptr]);

        fTypeMap[Typed::kVoid] = llvm::Type::getVoidTy(module->getContext());

        // void* must be defined as i8* type
        fTypeMap[Typed::kVoid_ptr]     = getInt8TyPtr();
        fTypeMap[Typed::kVoid_ptr_ptr] = getTyPtr(fTypeMap[Typed::kVoid_ptr]);

        // External structured type definition
        for (auto& it : gGlobal->gExternalStructTypes) {
            LLVMType new_type                         = convertFIRType((it.second)->fType);
            fTypeMap[it.first]                        = new_type;
            fTypeMap[Typed::getPtrFromType(it.first)] = getTyPtr(new_type);
        }
    }

    virtual ~LLVMTypeHelper() {}

    LLVMValue genInt1(int num) { return ConstantInt::get(llvm::Type::getInt1Ty(fModule->getContext()), num); }

    LLVMValue genInt32(int num) { return ConstantInt::get(llvm::Type::getInt32Ty(fModule->getContext()), num); }

    LLVMValue genInt64(long long num) { return ConstantInt::get(llvm::Type::getInt64Ty(fModule->getContext()), num); }

    LLVMValue genFloat(float num) { return ConstantFP::get(fModule->getContext(), APFloat(num)); }

    LLVMValue genDouble(double num) { return ConstantFP::get(fModule->getContext(), APFloat(num)); }

    LLVMType getFloatTy() { return llvm::Type::getFloatTy(fModule->getContext()); }
    LLVMType getDoubleTy() { return llvm::Type::getDoubleTy(fModule->getContext()); }
    LLVMType getInt32Ty() { return llvm::Type::getInt32Ty(fModule->getContext()); }
    LLVMType getInt64Ty() { return llvm::Type::getInt64Ty(fModule->getContext()); }
    LLVMType getInt1Ty() { return llvm::Type::getInt1Ty(fModule->getContext()); }
    LLVMType getInt8Ty() { return llvm::Type::getInt8Ty(fModule->getContext()); }
    LLVMType getInt8TyPtr() { return PointerType::get(getInt8Ty(), 0); }
    LLVMType getTyPtr(LLVMType type) { return PointerType::get(type, 0); }

    LLVMValue genArray(LLVMType type, const vector<Constant*>& num_array)
    {
        ArrayType* array_type = ArrayType::get(type, num_array.size());
        return ConstantArray::get(array_type, num_array);
    }

    GlobalVariable* genGlovalVar(LLVMType type, bool is_const, const string& name)
    {
        return new GlobalVariable(*fModule, type, is_const, GlobalValue::InternalLinkage, 0, name);
    }

    // Convert FIR types to LLVM types
    LLVMType convertFIRType(Typed* type)
    {
        BasicTyped*  basic_typed  = dynamic_cast<BasicTyped*>(type);
        NamedTyped*  named_typed  = dynamic_cast<NamedTyped*>(type);
        ArrayTyped*  array_typed  = dynamic_cast<ArrayTyped*>(type);
        VectorTyped* vector_typed = dynamic_cast<VectorTyped*>(type);
        StructTyped* struct_typed = dynamic_cast<StructTyped*>(type);

        if (basic_typed) {
            return fTypeMap[basic_typed->fType];
        } else if (named_typed) {
            LLVMType type = fModule->getTypeByName("struct.dsp" + named_typed->fName);
            // Subcontainer type (RWTable...)
            return (type) ? getTyPtr(type) : convertFIRType(named_typed->fType);
        } else if (array_typed) {
            // Arrays of 0 size are actually pointers on the type
            return (array_typed->fSize == 0)
                       ? fTypeMap[array_typed->getType()]
                       : ArrayType::get(fTypeMap[Typed::getTypeFromPtr(array_typed->getType())], array_typed->fSize);
        } else if (vector_typed) {
            return VectorType::get(fTypeMap[vector_typed->fType->fType], vector_typed->fSize);
        } else if (struct_typed) {
            LLVMVecTypes llvm_types;
            for (auto& it : struct_typed->fFields) {
                llvm_types.push_back(convertFIRType(it));
            }
            return createStructType("struct.dsp" + struct_typed->fName, llvm_types);
        } else {
            faustassert(false);
            return nullptr;
        }
    }

    llvm::StructType* createStructType(const string& name, const LLVMVecTypes& types)
    {
        // We want to have a unique creation for struct types: check if the given type has already been created
        StructType* struct_type = fModule->getTypeByName(name);
        if (!struct_type) {
            struct_type = StructType::create(fModule->getContext(), name);
            // Create "packed" struct type to match the size of C++ "packed" defined ones
            struct_type->setBody(makeArrayRef(types), true);
        }
        return struct_type;
    }
};

// LLVM code generator

class LLVMInstVisitor : public InstVisitor, public LLVMTypeHelper {
   protected:
    // To be used for "alloca", which have to be added
    // in the first "entry" block of the function
    IRBuilder<>* fAllocaBuilder;
    IRBuilder<>* fBuilder;

    StructInstVisitor* fStructVisitor;
    LLVMValue          fCurValue;  // Current compilation result

    map<string, LLVMValue>       fStackVars;    // Variables on the stack
    map<string, GlobalVariable*> fStringTable;  // Global strings

    static list<string> gMathLibTable;

    LLVMType getCurType() { return fCurValue->getType(); }

    void printVarTable()
    {
        for (auto& it : fStackVars) {
            cout << "Stack var = " << it.first << endl;
        }
    }

    GlobalVariable* addStringConstant(string arg, LLVMType& type_def)
    {
        string str = replaceChar(unquote(arg), '@', '_');
        type_def   = ArrayType::get(getInt8Ty(), str.size() + 1);

        if (fStringTable.find(str) == fStringTable.end()) {
            fStringTable[str] = genGlovalVar(type_def, true, str);
            fStringTable[str]->setInitializer(ConstantDataArray::getString(fModule->getContext(), str, true));
        }

        return fStringTable[str];
    }

    LLVMValue loadStructVarAddress(const string& name)
    {
        int field_index = fStructVisitor->getFieldIndex(name);
#if defined(LLVM_35)
        return fBuilder->CreateStructGEP(loadFunArg("dsp"), field_index);
#else
        return fBuilder->CreateStructGEP(0, loadFunArg("dsp"), field_index);
#endif
    }

    LLVMValue loadStructArrayVarAddress(const string& name)
    {
        int       field_index = fStructVisitor->getFieldIndex(name);
        LLVMValue idx[]       = {genInt32(0), genInt32(field_index)};
        return fBuilder->CreateInBoundsGEP(loadFunArg("dsp"), MakeIdx(idx, idx + 2));
    }

    LLVMValue loadArrayAsPointer(LLVMValue variable, bool isvolatile = false)
    {
        LoadInst* tmp_load = new LoadInst(variable);
        bool      is_array = isa<ArrayType>(tmp_load->getType());
        delete tmp_load;
        if (is_array) {
            LLVMValue idx[] = {genInt32(0), genInt32(0)};
            return fBuilder->CreateInBoundsGEP(variable, MakeIdx(idx, idx + 2));
        } else {
            return fBuilder->CreateLoad(variable, isvolatile);
        }
    }

    LLVMValue loadFunArg(const string& name)
    {
        // Get the enclosing function
        Function* function = fBuilder->GetInsertBlock()->getParent();

        for (Function::arg_iterator it = function->arg_begin(); it != function->arg_end(); ++it) {
            LLVMValue arg = GetIterator(it);
            if (arg->getName() == name) return arg;
        }

        faustassert(false);
        return nullptr;
    }

   public:
    LLVMInstVisitor(Module* module, IRBuilder<>* builder, StructInstVisitor* struct_visitor, llvm::PointerType* dsp_ptr)
        : LLVMTypeHelper(module), fBuilder(builder), fStructVisitor(struct_visitor), fCurValue(nullptr)
    {
        fTypeMap[Typed::kObj_ptr] = dsp_ptr;
        fAllocaBuilder            = new IRBuilder<>(fModule->getContext());

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

    virtual ~LLVMInstVisitor() { delete fAllocaBuilder; }

    //========
    // String
    //========

    LLVMValue genStringConstant(const string& label)
    {
        // Get LLVM constant string
        LLVMType        type_def  = nullptr;
        GlobalVariable* llvm_name = addStringConstant(label, type_def);
#if defined(LLVM_35)
        return fBuilder->CreateConstGEP2_32(llvm_name, 0, 0);
#else
        return fBuilder->CreateConstGEP2_32(type_def, llvm_name, 0, 0);
#endif
    }

    //==============
    // Declarations
    //==============

    virtual void visit(DeclareVarInst* inst)
    {
        string              name   = inst->fAddress->getName();
        Address::AccessType access = inst->fAddress->getAccess();

        if (access & Address::kStack || access & Address::kLoop) {
            // If we have an explicit alloca builder, use it
            if (fAllocaBuilder->GetInsertBlock()) {
                // Always at the begining since the block is already branched to next one...
                fAllocaBuilder->SetInsertPoint(GetIterator(fAllocaBuilder->GetInsertBlock()->getFirstInsertionPt()));
                fCurValue = fAllocaBuilder->CreateAlloca(convertFIRType(inst->fType));
            } else {
                fCurValue = fBuilder->CreateAlloca(convertFIRType(inst->fType));
            }

            fCurValue->setName(name);
            fStackVars[name] = fCurValue;  // Keep stack variables

            // Declaration with a value
            if (inst->fValue) {
                // Result is in fCurValue;
                inst->fValue->accept(this);
                genStore(fStackVars[name], fCurValue, false);
            }

        } else if (access & Address::kGlobal || access & Address::kStaticStruct) {
            if (!fModule->getGlobalVariable(name, true)) {
                GlobalVariable* gv = genGlovalVar(convertFIRType(inst->fType), (access & Address::kConst), name);
                // Declaration with a value
                if (inst->fValue) {
                    // Result is in fCurValue;
                    inst->fValue->accept(this);
                    gv->setInitializer(static_cast<Constant*>(fCurValue));
                } else {
                    // Init with typed zero
                    gv->setInitializer(Constant::getNullValue(convertFIRType(inst->fType)));
                }
            }

        } else {
            faustassert(false);
        }

        // No result in fCurValue
        fCurValue = nullptr;
    }

    virtual void visit(DeclareFunInst* inst)
    {
        Function* function = fModule->getFunction(inst->fName);

        // Define it
        if (!function) {
            // Special cases for min/max
            if (checkMinMax(inst->fName)) {
                fCurValue = nullptr;
                return;
            }

            // Return type
            LLVMType return_type = fTypeMap[inst->fType->fResult->getType()];

            // Prepare vector of LLVM types for args
            LLVMVecTypes fun_args_type;
            for (auto& it : inst->fType->fArgsTypes) {
                fun_args_type.push_back(fTypeMap[it->getType()]);
            }

            // Creates function
            FunctionType* fun_type = FunctionType::get(return_type, makeArrayRef(fun_args_type), false);
            function               = Function::Create(
                fun_type,
                (inst->fType->fAttribute & FunTyped::kLocal || inst->fType->fAttribute & FunTyped::kStatic)
                    ? GlobalValue::InternalLinkage
                    : GlobalValue::ExternalLinkage,
                inst->fName, fModule);

            // In order for auto-vectorization to correctly work with vectorizable math functions
            if (find(gMathLibTable.begin(), gMathLibTable.end(), inst->fName) != gMathLibTable.end()) {
                function->setDoesNotAccessMemory();
            }
            function->setDoesNotThrow();

            // Set name for function arguments
            Function::arg_iterator args = function->arg_begin();
            for (auto& it : inst->fType->fArgsTypes) {
                LLVMValue arg = GetIterator(args++);
                arg->setName(it->fName);
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

        // No result in fCurValue
        fCurValue = nullptr;
    }

    //=============
    // LoadVarInst
    //=============

    LLVMValue visitNameAddressAux(NamedAddress* named_address)
    {
        // dump2FIR(named_address);
        string              name   = named_address->fName;
        Address::AccessType access = named_address->fAccess;

        if (access & Address::kStruct) {
            return loadStructVarAddress(name);
        } else if (access & Address::kFunArgs) {
            return loadFunArg(name);
        } else if (access & Address::kStack || access & Address::kLoop) {
            return fStackVars[name];
        } else if ((access & Address::kGlobal) || (access & Address::kStaticStruct)) {
            return fModule->getGlobalVariable(name, true);
        } else {
            faustassert(false);
            return nullptr;
        }
    }

    LLVMValue visitIndexedAddressAux(IndexedAddress* indexed_address)
    {
        NamedAddress* named_address = dynamic_cast<NamedAddress*>(indexed_address->fAddress);
        faustassert(named_address);  // One level indexation for now

        // Compute index, result is in fCurValue
        indexed_address->fIndex->accept(this);
        Address::AccessType access = named_address->fAccess;
        string              name   = named_address->fName;
        LLVMValue           load_ptr;

        if (access & Address::kStruct) {
            load_ptr = loadArrayAsPointer(loadStructArrayVarAddress(name));
        } else if (access & Address::kFunArgs) {
            load_ptr = loadFunArg(name);
        } else if (access & Address::kStack || access & Address::kLoop) {
            // We want to see array like [256 x float] as a float*
            load_ptr = loadArrayAsPointer(fStackVars[name]);
        } else if (access & Address::kGlobal || access & Address::kStaticStruct) {
            // We want to see array like [256 x float] as a float*
            load_ptr = loadArrayAsPointer(fModule->getGlobalVariable(name, true));
        } else {
            // Default
            faustassert(false);
            return nullptr;
        }

        // Indexed adresses can actually be values in an array or fields in a struct type
        if (isStructType(indexed_address->getName())) {
            LLVMValue idx[2];
            idx[0] = genInt64(0);
            idx[1] = fCurValue;
            return fBuilder->CreateInBoundsGEP(load_ptr, MakeIdx(idx, idx + 2));
        } else {
            return fBuilder->CreateInBoundsGEP(load_ptr, fCurValue);
        }
    }

    void visitNameAddress(LoadVarInst* inst, NamedAddress* named_address)
    {
        LLVMValue           load_ptr = visitNameAddressAux(named_address);
        Address::AccessType access   = named_address->fAccess;

        if (access & Address::kStruct || access & Address::kStack || access & Address::kLoop ||
            access & Address::kGlobal || access & Address::kStaticStruct) {
            // We want to see array like [256 x float] as a float*
            fCurValue = loadArrayAsPointer(load_ptr, access & Address::kVolatile);
        } else {
            fCurValue = load_ptr;
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

    //====================
    // LoadVarAddressInst
    //====================

    virtual void visit(LoadVarAddressInst* inst)
    {
        NamedAddress*   named_address   = dynamic_cast<NamedAddress*>(inst->fAddress);
        IndexedAddress* indexed_address = dynamic_cast<IndexedAddress*>(inst->fAddress);

        if (named_address) {
            fCurValue = visitNameAddressAux(named_address);
        } else if (indexed_address) {
            fCurValue = visitIndexedAddressAux(indexed_address);
        } else {
            faustassert(false);
        }
    }

    //==============
    // StoreVarInst
    //==============

    void genStore(LLVMValue store_ptr, LLVMValue store, bool is_volatile)
    {
        // HACK : special case if we store a 0 (null pointer) in an address
        // (used in vec mode and in "allocate" function in scheduler mode...)
        if ((store_ptr->getType() != getTyPtr(store->getType())) &&
            (store->getType() == getInt32Ty() || store->getType() == getInt64Ty())) {
            store =
                ConstantPointerNull::get(static_cast<llvm::PointerType*>(store_ptr->getType()->getContainedType(0)));
        }
        fBuilder->CreateStore(store, store_ptr, is_volatile);
    }

    void visitNameAddress(StoreVarInst* inst, NamedAddress* named_address)
    {
        // dump2FIR(inst);
        LLVMValue store_ptr = visitNameAddressAux(named_address);

        // Result is in fCurValue;
        inst->fValue->accept(this);
        genStore(store_ptr, fCurValue, named_address->fAccess & Address::kVolatile);
    }

    void visitIndexedAddress(StoreVarInst* inst, IndexedAddress* indexed_address)
    {
        // dump2FIR(inst);
        LLVMValue store_ptr = visitIndexedAddressAux(indexed_address);

        // Result is in fCurValue;
        inst->fValue->accept(this);
        genStore(store_ptr, fCurValue, indexed_address->fAddress->getAccess() & Address::kVolatile);
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

    //=========
    // Numbers
    //=========

    virtual void visit(FloatNumInst* inst) { fCurValue = genFloat(inst->fNum); }

    virtual void visit(FloatArrayNumInst* inst)
    {
        vector<Constant*> num_array;
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            num_array.push_back(static_cast<ConstantFP*>(genFloat(inst->fNumTable[i])));
        }
        fCurValue = genArray(getFloatTy(), num_array);
    }

    virtual void visit(DoubleNumInst* inst) { fCurValue = genDouble(inst->fNum); }

    virtual void visit(DoubleArrayNumInst* inst)
    {
        vector<Constant*> num_array;
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            num_array.push_back(static_cast<ConstantFP*>(genDouble(inst->fNumTable[i])));
        }
        fCurValue = genArray(getDoubleTy(), num_array);
    }

    virtual void visit(Int32NumInst* inst) { fCurValue = genInt32(inst->fNum); }

    virtual void visit(Int32ArrayNumInst* inst)
    {
        vector<Constant*> num_array;
        for (size_t i = 0; i < inst->fNumTable.size(); i++) {
            num_array.push_back(static_cast<ConstantFP*>(genInt32(inst->fNumTable[i])));
        }
        fCurValue = genArray(getInt32Ty(), num_array);
    }

    virtual void visit(BoolNumInst* inst) { fCurValue = genInt1(inst->fNum); }

    virtual void visit(Int64NumInst* inst) { fCurValue = genInt64(inst->fNum); }

    virtual void visit(BinopInst* inst)
    {
        // dump2FIR(inst);

        // Keep result of first arg compilation
        inst->fInst1->accept(this);
        LLVMValue res1 = fCurValue;

        // Keep result of second arg compilation
        inst->fInst2->accept(this);
        LLVMValue res2 = fCurValue;

        fCurValue = generateBinopAux(inst->fOpcode, res1, res2);
    }

    //======
    // Cast
    //======

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
        fCurValue = fBuilder->CreateBitCast(fCurValue, fTypeMap[inst->fType->getType()]);
    }

    void visitCastAux(Typed::VarType type)
    {
        switch (type) {
            case Typed::kFloat:
                if (getCurType() == getInt32Ty()) {
                    fCurValue = fBuilder->CreateSIToFP(fCurValue, getFloatTy());
                } else if (getCurType() == getFloatTy()) {
                    // Nothing to do
                } else if (getCurType() == getDoubleTy()) {
                    fCurValue = fBuilder->CreateFPTrunc(fCurValue, getFloatTy());
                } else {
                    faustassert(false);
                }
                break;

            case Typed::kInt32:
                if (getCurType() == getInt32Ty()) {
                    // Nothing to do
                } else if (getCurType() == getFloatTy() || getCurType() == getDoubleTy()) {
                    fCurValue = fBuilder->CreateFPToSI(fCurValue, getInt32Ty());
                } else if (getCurType()->isPointerTy()) {
                    // Use BitCast for pointer to kInt32
                    fCurValue = fBuilder->CreateBitCast(fCurValue, getInt32Ty());
                } else {
                    faustassert(false);
                }
                break;

            case Typed::kDouble:
                if (getCurType() == getInt32Ty()) {
                    fCurValue = fBuilder->CreateSIToFP(fCurValue, getDoubleTy());
                } else if (getCurType() == getFloatTy()) {
                    fCurValue = fBuilder->CreateFPExt(fCurValue, getDoubleTy());
                } else if (getCurType() == getDoubleTy()) {
                    // Nothing to do
                } else {
                    faustassert(false);
                }
                break;

            case Typed::kObj_ptr:
                fCurValue = fBuilder->CreateBitCast(fCurValue, fTypeMap[Typed::kObj_ptr]);
                break;

            case Typed::kVoid_ptr:
                fCurValue = fBuilder->CreateBitCast(fCurValue, fTypeMap[Typed::kVoid_ptr]);
                break;

            case Typed::kUint_ptr:
#ifndef LLVM_35
                fCurValue =
                    fBuilder->CreatePtrToInt(fCurValue, fModule->getDataLayout().getIntPtrType(fModule->getContext()));
#else
                fCurValue =
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
        // Compile all arguments
        vector<LLVMValue> fun_args;
        for (auto& it : inst->fArgs) {
            // Each argument is compiled and result is in fCurValue
            it->accept(this);
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
        // Special case
        if (checkMinMax(inst->fName)) {
            generateFunPolymorphicMinMax(inst);
            return;
        }

        // Compile arguments
        Function* function = fModule->getFunction(gGlobal->getMathFunction(inst->fName));
        faustassert(function);

        Function::arg_iterator arg = function->arg_begin();
        vector<LLVMValue>      fun_args;
        for (auto& it : inst->fArgs) {
            // Each argument is compiled and result is in fCurValue
            it->accept(this);
            fun_args.push_back(fCurValue);
        }

        // Result is function call
        fCurValue = CreateCall(function, fun_args);
    }

    virtual void visit(Select2Inst* inst)
    {
        // Compile condition, result in fCurValue
        inst->fCond->accept(this);

        // Convert condition to a bool by comparing to 0
        LLVMValue cond_value =
            fBuilder->CreateICmpNE(fCurValue, (getCurType() == getInt64Ty()) ? genInt64(0) : genInt32(0), "ifcond");

        // Compile then branch, result in fCurValue
        inst->fThen->accept(this);
        LLVMValue then_value = fCurValue;

        // Compile else branch, result in fCurValue
        inst->fElse->accept(this);
        LLVMValue else_value = fCurValue;

        // Creates the result
        fCurValue = fBuilder->CreateSelect(cond_value, then_value, else_value);
    }

    virtual void visit(IfInst* inst)
    {
        // Compile condition, result in fCurValue
        inst->fCond->accept(this);

        // Convert condition to a bool by comparing equal to comp_val value
        LLVMValue cond_value = fBuilder->CreateICmpEQ(fCurValue, genInt32(1), "ifcond");

        Function* function = fBuilder->GetInsertBlock()->getParent();

        // Create blocks for the then and else cases. Insert the 'then' block at the end of the function
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

        Function* function = fBuilder->GetInsertBlock()->getParent();
        faustassert(function);

        // Create init_block
        BasicBlock* init_block = BasicBlock::Create(fModule->getContext(), "init_block", function);

        // Create test_block
        BasicBlock* test_block = BasicBlock::Create(fModule->getContext(), "test_block", function);

        // Create loop_body_block
        BasicBlock* loop_body_block = BasicBlock::Create(fModule->getContext(), "loop_body_block", function);

        // Create exit_block
        BasicBlock* exit_block = BasicBlock::Create(fModule->getContext(), "exit_block", function);

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
        string loop_counter_name = inst->getName();

        // Start the PHI node with an entry for start
        PHINode* phi_node = CreatePhi(getInt32Ty(), loop_counter_name);
        phi_node->addIncoming(genInt32(0), init_block);

        // End condition section
        {
            // Compute end condition, result in fCurValue
            inst->fEnd->accept(this);

            // Convert condition to a bool
            LLVMValue end_cond = fBuilder->CreateTrunc(fCurValue, fBuilder->getInt1Ty());

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
        BasicBlock* current_block = fBuilder->GetInsertBlock();

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

        // Create the test_block and insert it
        BasicBlock* test_block = BasicBlock::Create(fModule->getContext(), "test_block", function);

        // Create the exit_block and insert it
        BasicBlock* exit_block = BasicBlock::Create(fModule->getContext(), "exit_block", function);

        // Convert condition to a bool
        LLVMValue end_cond = fBuilder->CreateTrunc(fCurValue, fBuilder->getInt1Ty());

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
                switch_inst->addCase(static_cast<ConstantInt*>(genInt32((*it).first)), case_block);
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

    LLVMValue generateBinOpReal(int op, LLVMValue arg1, LLVMValue arg2)
    {
        if (isBoolOpcode(op)) {
            LLVMValue comp_value =
                fBuilder->CreateFCmp((CmpInst::Predicate)gBinOpTable[op]->fLLVMFloatInst, arg1, arg2);
            // Inst result for comparison
            return fBuilder->CreateSelect(comp_value, genInt32(1), genInt32(0));
        } else {
            LLVMValue value =
                fBuilder->CreateBinOp((Instruction::BinaryOps)gBinOpTable[op]->fLLVMFloatInst, arg1, arg2);
            Instruction* inst = cast<Instruction>(value);
            inst->setMetadata(LLVMContext::MD_fpmath, fBuilder->getDefaultFPMathTag());
            inst->setFastMathFlags(fBuilder->getFastMathFlags());
            return inst;
        }
    }

    LLVMValue generateBinOpInt(int opcode, LLVMValue arg1, LLVMValue arg2)
    {
        if (isBoolOpcode(opcode)) {
            LLVMValue comp_value =
                fBuilder->CreateICmp((CmpInst::Predicate)gBinOpTable[opcode]->fLLVMIntInst, arg1, arg2);
            // Inst result for comparison
            return fBuilder->CreateSelect(comp_value, genInt32(1), genInt32(0));
        } else {
            return fBuilder->CreateBinOp((Instruction::BinaryOps)gBinOpTable[opcode]->fLLVMIntInst, arg1, arg2);
        }
    }

    LLVMValue generateBinopAux(int opcode, LLVMValue arg1, LLVMValue arg2)
    {
        // Arguments are casted if needed in InstructionsCompiler::generateBinOp
        faustassert(arg1->getType() == arg2->getType());

        if (arg1->getType() == getFloatTy() || arg1->getType() == getDoubleTy()) {
            return generateBinOpReal(opcode, arg1, arg2);
        } else if (arg1->getType() == getInt32Ty() || arg1->getType() == getInt64Ty()) {
            return generateBinOpInt(opcode, arg1, arg2);
        } else {
            // Should not happen
            cerr << "generateBinopAux" << endl;
            faustassert(false);
            return nullptr;
        }
    }

    LLVMValue generateFunPolymorphicMinMaxAux(LLVMValue arg1, LLVMValue arg2, int comp)
    {
        faustassert(arg1->getType() == arg2->getType());

        if (arg1->getType() == getFloatTy() || arg1->getType() == getDoubleTy()) {
            LLVMValue comp_value =
                fBuilder->CreateFCmp((llvm::CmpInst::Predicate)gBinOpTable[comp]->fLLVMFloatInst, arg1, arg2);
            return fBuilder->CreateSelect(comp_value, arg1, arg2);
        } else if (arg1->getType() == getInt32Ty()) {
            LLVMValue comp_value =
                fBuilder->CreateICmp((llvm::CmpInst::Predicate)gBinOpTable[comp]->fLLVMIntInst, arg1, arg2);
            return fBuilder->CreateSelect(comp_value, arg1, arg2);
        } else {
            // Should not happen
            cerr << "generateFunPolymorphicMinMaxAux" << endl;
            faustassert(false);
            return nullptr;
        }
    }
};

#endif
