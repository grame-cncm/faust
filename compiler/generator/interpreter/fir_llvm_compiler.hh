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

#ifndef _FIR_LLVM_COMPILER_H
#define _FIR_LLVM_COMPILER_H

#include <string>
#include <vector>

#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/LegacyPassNameParser.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/IR/PassManager.h>
#include <llvm/Transforms/IPO/PassManagerBuilder.h>

#include "interpreter_bytecode.hh"
#include "interpreter_optimizer.hh"

using namespace llvm;

typedef llvm::Value* LLVMValue;

#define dumpLLVM1(val)                           \
    {                                            \
        std::string res;                         \
        raw_string_ostream out_str(res);         \
        out_str << *val;                         \
        std::cout << out_str.str() << std::endl; \
    }

#define pushLLVMBinop(op)                              \
    {                                                  \
        LLVMValue v1 = popLLVM();                      \
        LLVMValue v2 = popLLVM();                      \
        pushLLVM(fBuilder->CreateBinOp((op), v1, v2)); \
    }

#define pushLLVMRealComp(op)                          \
    {                                                 \
        LLVMValue v1 = popLLVM();                     \
        LLVMValue v2 = popLLVM();                     \
        LLVMValue cond_value = fBuilder->CreateFCmp((op), v1, v2);              \
        pushLLVM(fBuilder->CreateSelect(cond_value, genInt32(1), genInt32(0))); \
    }

#define pushLLVMIntComp(op)                           \
    {                                                 \
        LLVMValue v1 = popLLVM();                     \
        LLVMValue v2 = popLLVM();                     \
        LLVMValue cond_value = fBuilder->CreateICmp((op), v1, v2);              \
        pushLLVM(fBuilder->CreateSelect(cond_value, genInt32(1), genInt32(0))); \
    }

#define dispatchReturn() { it = popAddr(); }
#define saveReturn() { pushAddr(it + 1); }

// FIR bytecode compiler
template <class T>
class FIRLLVMCompiler {
    
    typedef void (* llvmComputeFun) (int* int_heap, T* real_heap, T** inputs, T** outputs);

    protected:
        llvm::ExecutionEngine* fJIT;
        llvm::Module* fModule;
        llvm::IRBuilder<>* fBuilder;
        LLVMContext* fContext;
        llvmComputeFun fCompute;
    
        LLVMValue fLLVMStack[1024];
        InstructionIT fAddressStack[64];
    
        int fLLVMStackIndex;
        int fAddrStackIndex;
    
        LLVMValue fLLVMIntHeap;
        LLVMValue fLLVMRealHeap;
        LLVMValue fLLVMInputs;
        LLVMValue fLLVMOutputs;

        LLVMContext& getContext() { return *fContext; }
    
        LLVMValue genFloat(float num) { return ConstantFP::get(fModule->getContext(), APFloat(num)); }
        LLVMValue genDouble(double num) { return ConstantFP::get(fModule->getContext(), APFloat(num)); }
        LLVMValue genReal(double num) { return  (sizeof(T) == sizeof(double)) ? genDouble(num) : genFloat(num); }
        LLVMValue genInt32(int num) { return ConstantInt::get(llvm::Type::getInt32Ty(fModule->getContext()), num); }
        LLVMValue genInt64(long long num) { return ConstantInt::get(llvm::Type::getInt64Ty(fModule->getContext()), num); }

        llvm::Type* getFloatTy() { return llvm::Type::getFloatTy(fModule->getContext()); }
        llvm::Type* getInt32Ty() { return llvm::Type::getInt32Ty(fModule->getContext()); }
        llvm::Type* getInt64Ty() { return llvm::Type::getInt64Ty(fModule->getContext()); }
        llvm::Type* getInt1Ty() { return llvm::Type::getInt1Ty(fModule->getContext()); }
        llvm::Type* getDoubleTy() { return llvm::Type::getDoubleTy(fModule->getContext()); }
        llvm::Type* getRealTy() { return (sizeof(T) == sizeof(double)) ? getDoubleTy() : getFloatTy(); }
    
        void pushLLVM(LLVMValue val) { fLLVMStack[fLLVMStackIndex++] = val; }
        LLVMValue popLLVM() { return fLLVMStack[--fLLVMStackIndex]; }
    
        void pushAddr(InstructionIT addr) { fAddressStack[fAddrStackIndex++] = addr; }
        InstructionIT popAddr() { return fAddressStack[--fAddrStackIndex]; }
        bool emptyReturn() { return fAddrStackIndex == 0; }

        void pushLLVMUnaryCallAux(std::string name, llvm::Type* type)
        {
            llvm::Function* function = fModule->getFunction(name);
            if (!function) {
                // Define it
                std::vector<llvm::Type*> fun_args_type;
                fun_args_type.push_back(type);
                llvm::FunctionType* fun_type = FunctionType::get(type, makeArrayRef(fun_args_type), false);
                function = Function::Create(fun_type, GlobalValue::ExternalLinkage, name, fModule);
                function->setCallingConv(CallingConv::C);
            }
            // Create the function call
            std::vector<LLVMValue> fun_args;
            fun_args.push_back(popLLVM());
            llvm::CallInst* call_inst = fBuilder->CreateCall(function, makeArrayRef(fun_args));
            call_inst->setCallingConv(CallingConv::C);
            pushLLVM(call_inst);
        }
    
        void pushLLVMUnaryIntCall(std::string name) { return pushLLVMUnaryCallAux(name, getInt32Ty()); }
        void pushLLVMUnaryRealCall(std::string name) { return pushLLVMUnaryCallAux(name, getRealTy()); }
    
        void pushLLVMBinaryCall(std::string name, llvm::Type* res_type)
        {
            llvm::Function* function = fModule->getFunction(name);
            if (!function) {
                // Define it
                std::vector<llvm::Type*> fun_args_type;
                fun_args_type.push_back(res_type);
                fun_args_type.push_back(res_type);
                llvm::FunctionType* fun_type = FunctionType::get(res_type, makeArrayRef(fun_args_type), false);
                function = Function::Create(fun_type, GlobalValue::ExternalLinkage, name, fModule);
                function->setCallingConv(CallingConv::C);
            }
            // Create the function call
            std::vector<LLVMValue> fun_args;
            fun_args.push_back(popLLVM());
            fun_args.push_back(popLLVM());
            llvm::CallInst* call_inst = fBuilder->CreateCall(function, makeArrayRef(fun_args));
            call_inst->setCallingConv(CallingConv::C);
            pushLLVM(call_inst);
        }
    
        void pushLLVMBinaryIntCall(std::string name)
        {
            pushLLVMBinaryCall(name, getInt32Ty());
        }
    
        void pushLLVMBinaryRealCall(std::string name)
        {
            pushLLVMBinaryCall(name, getRealTy());
        }

        void pushLoadArray(LLVMValue array, int index)
        {
            pushLoadArray(array, genInt32(index));
        }
    
        void pushStoreArray(LLVMValue array, int index)
        {
            pushStoreArray(array, genInt32(index));
        }
    
        void pushLoadArray(LLVMValue array, LLVMValue index)
        {
            LLVMValue load_ptr = fBuilder->CreateInBoundsGEP(array, index);
            pushLLVM(fBuilder->CreateLoad(load_ptr));
        }
    
        void pushStoreArray(LLVMValue array, LLVMValue index)
        {
            LLVMValue store_ptr = fBuilder->CreateInBoundsGEP(array, index);
            fBuilder->CreateStore(popLLVM(), store_ptr);
        }
    
        void pushLoadInput(int index)
        {
            LLVMValue input_ptr_ptr = fBuilder->CreateInBoundsGEP(fLLVMInputs, genInt32(index));
            LLVMValue input_ptr = fBuilder->CreateLoad(input_ptr_ptr);
            LLVMValue input = fBuilder->CreateInBoundsGEP(input_ptr, popLLVM());
            pushLLVM(fBuilder->CreateLoad(input));
        }
    
        void pushStoreOutput(int index)
        {
            LLVMValue output_ptr_ptr = fBuilder->CreateInBoundsGEP(fLLVMOutputs, genInt32(index));
            LLVMValue output_ptr = fBuilder->CreateLoad(output_ptr_ptr);
            LLVMValue output = fBuilder->CreateInBoundsGEP(output_ptr, popLLVM());
            fBuilder->CreateStore(popLLVM(), output);
        }
    
        void CompileBlock(FIRBlockInstruction<T>* block, BasicBlock* code_block)
        {
            std::cout << "========= CompileBlock =========\n";
            InstructionIT it = block->fInstructions.begin();
            bool end = false;
            
            // Insert in the current block
            fBuilder->SetInsertPoint(code_block);
            
            while ((it != block->fInstructions.end()) && !end) {
                
                std::cout << "CompileInst \n";
                (*it)->write(&std::cout);
                //dumpLLVM1(code_block);
                
                switch ((*it)->fOpcode) {
                        
                        // Numbers
                    case FIRInstruction::kRealValue:
                        pushLLVM(genReal((*it)->fRealValue));
                        it++;
                        break;
                        
                    case FIRInstruction::kInt32Value:
                        pushLLVM(genInt32((*it)->fIntValue));
                        it++;
                        break;
                        
                        // Memory load/store
                    case FIRInstruction::kLoadReal:
                        pushLoadArray(fLLVMRealHeap,(*it)->fOffset1);
                        it++;
                        break;
                        
                    case FIRInstruction::kLoadInt:
                        pushLoadArray(fLLVMIntHeap,(*it)->fOffset1);
                        it++;
                        break;
         
                    case FIRInstruction::kStoreReal:
                        pushStoreArray(fLLVMRealHeap, (*it)->fOffset1);
                        it++;
                        break;
                        
                    case FIRInstruction::kStoreInt:
                        pushStoreArray(fLLVMIntHeap, (*it)->fOffset1);
                        it++;
                        break;
                        
                        // Indexed memory load/store
                    case FIRInstruction::kLoadIndexedReal: {
                        LLVMValue offset = fBuilder->CreateBinOp(Instruction::Add, genInt32((*it)->fOffset1), popLLVM());
                        pushLoadArray(fLLVMRealHeap, offset);
                        it++;
                        break;
                    }
                         
                    case FIRInstruction::kLoadIndexedInt: {
                        LLVMValue offset = fBuilder->CreateBinOp(Instruction::Add, genInt32((*it)->fOffset1), popLLVM());
                        pushLoadArray(fLLVMIntHeap, offset);
                        it++;
                        break;
                    }
                         
                    case FIRInstruction::kStoreIndexedReal: {
                        LLVMValue offset = fBuilder->CreateBinOp(Instruction::Add, genInt32((*it)->fOffset1), popLLVM());
                        pushStoreArray(fLLVMRealHeap, offset);
                        it++;
                        break;
                    }
                         
                    case FIRInstruction::kStoreIndexedInt: {
                        LLVMValue offset = fBuilder->CreateBinOp(Instruction::Add, genInt32((*it)->fOffset1), popLLVM());
                        pushStoreArray(fLLVMIntHeap, offset);
                        it++;
                        break;
                    }
                        
                        // Input/output
                    case FIRInstruction::kLoadInput:
                        pushLoadInput((*it)->fOffset1);
                        it++;
                        break;
                        
                    case FIRInstruction::kStoreOutput:
                        pushStoreOutput((*it)->fOffset1);
                        it++;
                        break;
                        
                        // Cast
                    case FIRInstruction::kCastReal: {
                        LLVMValue val = popLLVM();
                        pushLLVM(fBuilder->CreateSIToFP(val, getRealTy()));
                        it++;
                        break;
                    }
                        
                    case FIRInstruction::kCastInt: {
                        LLVMValue val = popLLVM();
                        pushLLVM(fBuilder->CreateFPToSI(val, getInt32Ty()));
                        it++;
                        break;
                    }
                        
                    case FIRInstruction::kBitcastInt: {
                        LLVMValue val = popLLVM();
                        pushLLVM(fBuilder->CreateBitCast(val, getInt32Ty()));
                        it++;
                        break;
                    }
                        
                    case FIRInstruction::kBitcastReal: {
                        LLVMValue val = popLLVM();
                        pushLLVM(fBuilder->CreateBitCast(val, getRealTy()));
                        it++;
                        break;
                    }
                        
                        // Binary math
                    case FIRInstruction::kAddReal:
                        pushLLVMBinop(Instruction::FAdd);
                        it++;
                        break;
                        
                    case FIRInstruction::kAddInt:
                        pushLLVMBinop(Instruction::Add);
                        it++;
                        break;
                        
                    case FIRInstruction::kSubReal:
                        pushLLVMBinop(Instruction::FSub);
                        it++;
                        break;
                        
                    case FIRInstruction::kSubInt:
                        pushLLVMBinop(Instruction::Sub);
                        it++;
                        break;
                        
                    case FIRInstruction::kMultReal:
                        pushLLVMBinop(Instruction::FMul);
                        it++;
                        break;
                        
                    case FIRInstruction::kMultInt:
                        pushLLVMBinop(Instruction::Mul);
                        it++;
                        break;
                        
                    case FIRInstruction::kDivReal:
                        pushLLVMBinop(Instruction::FDiv);
                        it++;
                        break;
                        
                    case FIRInstruction::kDivInt:
                        pushLLVMBinop(Instruction::SDiv);
                        it++;
                        break;
                        
                    case FIRInstruction::kRemReal:
                        pushLLVMBinop(Instruction::FRem);
                        it++;
                        break;
                        
                    case FIRInstruction::kRemInt:
                        pushLLVMBinop(Instruction::SRem);
                        it++;
                        break;
                        
                    case FIRInstruction::kLshInt:
                        pushLLVMBinop(Instruction::Shl);
                        it++;
                        break;
                        
                    case FIRInstruction::kRshInt:
                        pushLLVMBinop(Instruction::LShr);
                        it++;
                        break;
                        
                    case FIRInstruction::kGTInt:
                        pushLLVMIntComp(ICmpInst::ICMP_SGT);
                        it++;
                        break;
                        
                    case FIRInstruction::kLTInt:
                        pushLLVMIntComp(ICmpInst::ICMP_SLT);
                        it++;
                        break;
                        
                    case FIRInstruction::kGEInt:
                        pushLLVMIntComp(ICmpInst::ICMP_SGE);
                        it++;
                        break;
                        
                    case FIRInstruction::kLEInt:
                        pushLLVMIntComp(ICmpInst::ICMP_SLE);
                        it++;
                        break;
                        
                    case FIRInstruction::kEQInt:
                        pushLLVMIntComp(ICmpInst::ICMP_EQ);
                        it++;
                        break;
                        
                    case FIRInstruction::kNEInt:
                        pushLLVMIntComp(ICmpInst::ICMP_NE);
                        it++;
                        break;
                        
                    case FIRInstruction::kGTReal:
                        pushLLVMRealComp(FCmpInst::FCMP_OGT);
                        it++;
                        break;
                        
                    case FIRInstruction::kLTReal:
                        pushLLVMRealComp(FCmpInst::FCMP_OLT);
                        it++;
                        break;
                        
                    case FIRInstruction::kGEReal:
                        pushLLVMRealComp(FCmpInst::FCMP_OGE);
                        it++;
                        break;
                        
                    case FIRInstruction::kLEReal:
                        pushLLVMRealComp(FCmpInst::FCMP_OLE);
                        it++;
                        break;
                        
                    case FIRInstruction::kEQReal:
                        pushLLVMRealComp(FCmpInst::FCMP_OEQ);
                        it++;
                        break;
                        
                    case FIRInstruction::kNEReal:
                        pushLLVMRealComp(FCmpInst::FCMP_ONE);
                        it++;
                        break;
                        
                    case FIRInstruction::kANDInt:
                        pushLLVMBinop(Instruction::And);
                        it++;
                        break;
                        
                    case FIRInstruction::kORInt:
                        pushLLVMBinop(Instruction::Or);
                        it++;
                        break;
                        
                    case FIRInstruction::kXORInt:
                        pushLLVMBinop(Instruction::Xor);
                        it++;
                        break;
                        
                         // Extended unary math
                    case FIRInstruction::kAbs:
                        pushLLVMUnaryIntCall("abs");
                        it++;
                        break;
                        
                    case FIRInstruction::kAbsf:
                        pushLLVMUnaryRealCall("fabs");
                        it++;
                        break;
  
                    case FIRInstruction::kAcosf:
                        pushLLVMUnaryRealCall("acos");
                        it++;
                        break;

                    case FIRInstruction::kAsinf:
                        pushLLVMUnaryRealCall("asin");
                        it++;
                        break;

                    case FIRInstruction::kAtanf:
                        pushLLVMUnaryRealCall("atan");
                        it++;
                        break;

                    case FIRInstruction::kCeilf:
                        pushLLVMUnaryRealCall("ceil");
                        it++;
                        break;

                    case FIRInstruction::kCosf:
                        pushLLVMUnaryRealCall("cos");
                        it++;
                        break;

                    case FIRInstruction::kCoshf:
                        pushLLVMUnaryRealCall("cosh");
                        it++;
                        break;

                    case FIRInstruction::kExpf:
                        pushLLVMUnaryRealCall("exp");
                        it++;
                        break;

                    case FIRInstruction::kFloorf:
                        pushLLVMUnaryRealCall("floor");
                        it++;
                        break;

                    case FIRInstruction::kLogf:
                        pushLLVMUnaryRealCall("log");
                        it++;
                        break;

                    case FIRInstruction::kLog10f:
                        pushLLVMUnaryRealCall("log10");
                        it++;
                        break;

                    case FIRInstruction::kRoundf:
                        pushLLVMUnaryRealCall("round");
                        it++;
                        break;

                    case FIRInstruction::kSinf:
                        pushLLVMUnaryRealCall("sin");
                        it++;
                        break;

                    case FIRInstruction::kSinhf:
                        pushLLVMUnaryRealCall("sinh");
                        it++;
                        break;

                    case FIRInstruction::kSqrtf:
                        pushLLVMUnaryRealCall("sqrt");
                        it++;
                        break;

                    case FIRInstruction::kTanf:
                        pushLLVMUnaryRealCall("tan");
                        it++;
                        break;

                    case FIRInstruction::kTanhf:
                        pushLLVMUnaryRealCall("tanh");
                        it++;
                        break;

                        // Extended binary math
                    case FIRInstruction::kAtan2f:
                        pushLLVMBinaryRealCall("atan2");
                        it++;
                        break;

                    case FIRInstruction::kFmodf:
                        pushLLVMBinaryRealCall("fmod");
                        it++;
                        break;

                    case FIRInstruction::kPowf:
                        pushLLVMBinaryRealCall("pow");
                        it++;
                        break;

                    case FIRInstruction::kMax: {
                        LLVMValue v1 = popLLVM();
                        LLVMValue v2 = popLLVM();
                        LLVMValue cond_value = fBuilder->CreateICmp(ICmpInst::ICMP_SLT, v1, v2);
                        pushLLVM(fBuilder->CreateSelect(cond_value, v2, v1));
                        it++;
                        break;
                    }
                        
                    case FIRInstruction::kMaxf: {
                        LLVMValue v1 = popLLVM();
                        LLVMValue v2 = popLLVM();
                        LLVMValue cond_value = fBuilder->CreateFCmp(FCmpInst::FCMP_OLT, v1, v2);
                        pushLLVM(fBuilder->CreateSelect(cond_value, v2, v1));
                        it++;
                        break;
                    }

                    case FIRInstruction::kMin: {
                        LLVMValue v1 = popLLVM();
                        LLVMValue v2 = popLLVM();
                        LLVMValue cond_value = fBuilder->CreateICmp(ICmpInst::ICMP_SLT, v1, v2);
                        pushLLVM(fBuilder->CreateSelect(cond_value, v1, v2));
                        it++;
                        break;
                    }
                        
                    case FIRInstruction::kMinf: {
                        LLVMValue v1 = popLLVM();
                        LLVMValue v2 = popLLVM();
                        LLVMValue cond_value = fBuilder->CreateFCmp(FCmpInst::FCMP_OLT, v1, v2);
                        pushLLVM(fBuilder->CreateSelect(cond_value, v1, v2));
                        it++;
                        break;
                    }
                        
                        // Control
                    case FIRInstruction::kReturn:
                        // Empty addr stack = end of computation
                        if (emptyReturn()) {
                            end = true;
                            std::cout << "End of block\n";
                        } else {
                            dispatchReturn();
                        }
                        break;
                        
                    case FIRInstruction::kIf: {
                        saveReturn();
                        LLVMValue cond_value = fBuilder->CreateICmpEQ(popLLVM(), genInt32(1), "ifcond");
                        Function* function = fBuilder->GetInsertBlock()->getParent();
                        
                        // Create blocks for the then and else cases.  Insert the 'then' block at the end of the function
                        BasicBlock* then_block  = BasicBlock::Create(fModule->getContext(), "then_code", function);
                        BasicBlock* else_block  = BasicBlock::Create(fModule->getContext(), "else_code");
                        BasicBlock* merge_block = BasicBlock::Create(fModule->getContext(), "merge_block");
                        
                        pushLLVM(fBuilder->CreateCondBr(cond_value, then_block, else_block));
                        
                        // Compile then branch (= branch1)
                        CompileBlock((*it)->fBranch1, then_block);
                        
                        fBuilder->CreateBr(merge_block);
                        // Codegen of 'Then' can change the current block, update then_block for the PHI
                        then_block = fBuilder->GetInsertBlock();
                        
                        // Emit else block
                        function->getBasicBlockList().push_back(else_block);
                        
                        // Compile else branch (= branch2)
                        CompileBlock((*it)->fBranch2, else_block);
                        
                        pushLLVM(fBuilder->CreateBr(merge_block));
                        // Codegen of 'Else' can change the current block, update else_block for the PHI
                        else_block = fBuilder->GetInsertBlock();
                        
                        // Emit merge block
                        function->getBasicBlockList().push_back(merge_block);
                        fBuilder->SetInsertPoint(merge_block);
                        break;
                    }
                        
                    case FIRInstruction::kSelectReal:
                    case FIRInstruction::kSelectInt: {
                        
                        // Prepare condition
                        LLVMValue cond_value = fBuilder->CreateICmpNE(popLLVM(), genInt32(0), "ifcond");
                    
                        // Compile then branch (= branch1)
                        CompileBlock((*it)->fBranch1, code_block);
                        
                        // Compile else branch (= branch2)
                        CompileBlock((*it)->fBranch2, code_block);
                        
                        // Create the result (= branch2)
                        LLVMValue then_value = popLLVM();
                        LLVMValue else_value = popLLVM();
                        pushLLVM(fBuilder->CreateSelect(cond_value, then_value, else_value));
                        
                        it++;
                        break;
                    }
                        
                    case FIRInstruction::kCondBranch: {
                        
                        // Prepare condition
                        LLVMValue cond_value = fBuilder->CreateTrunc(popLLVM(), fBuilder->getInt1Ty());
                        
                        Function* function = fBuilder->GetInsertBlock()->getParent();
                        BasicBlock* next_block = BasicBlock::Create(fModule->getContext(), "next_block", function);
                        
                        // Branch to current block
                        fBuilder->CreateCondBr(cond_value, code_block, next_block);
                        
                        // Insert in next_block
                        fBuilder->SetInsertPoint(next_block);
                        
                        it++;
                        break;
                    }
                        
                    case FIRInstruction::kLoop: {
                        
                        Function* function = fBuilder->GetInsertBlock()->getParent();
                        BasicBlock* init_block = BasicBlock::Create(fModule->getContext(), "init_block", function);
                        BasicBlock* loop_block = BasicBlock::Create(fModule->getContext(), "loop_block", function);
                        
                        // Link previous_block and init_block
                        fBuilder->CreateBr(init_block);
                        
                        // Compile init branch (= branch1)
                        CompileBlock((*it)->fBranch1, init_block);
                        
                        // Link previous_block and loop_block
                        fBuilder->CreateBr(loop_block);
                        
                        // Compile loop branch (= branch2)
                        CompileBlock((*it)->fBranch2, loop_block);

                        it++;
                        break;
                    }
                        
                    default:
                        // should not happen
                        (*it)->write(&std::cout);
                        faustassert(false);
                        break;
                }
            }
        }
   
    public:
        FIRLLVMCompiler(FIRBlockInstruction<T>* compute_block)
        {
            fLLVMStackIndex = 0;
            fAddrStackIndex = 0;
            
            fContext = new LLVMContext();
            fBuilder = new IRBuilder<>(getContext());
            fModule = new Module(std::string(FAUSTVERSION), getContext());
            fModule->setTargetTriple(llvm::sys::getDefaultTargetTriple());
        
            // Compile compute function
            std::vector<llvm::Type*> llvm_compute_args;
            llvm_compute_args.push_back(PointerType::get(getInt32Ty(), 0));
            llvm_compute_args.push_back(PointerType::get(getRealTy(), 0));
            llvm_compute_args.push_back(PointerType::get(PointerType::get(getRealTy(), 0), 0));
            llvm_compute_args.push_back(PointerType::get(PointerType::get(getRealTy(), 0), 0));
            
            FunctionType* llvm_compute_type = FunctionType::get(fBuilder->getVoidTy(), llvm_compute_args, false);
            Function* llvm_compute = Function::Create(llvm_compute_type, GlobalValue::ExternalLinkage, "compute", fModule);
            llvm_compute->setCallingConv(CallingConv::C);
            
            BasicBlock* code_block = BasicBlock::Create(fModule->getContext(), "entry_block", llvm_compute);
            
            Function::arg_iterator llvm_compute_args_it = llvm_compute->arg_begin();
            llvm_compute_args_it->setName("int_heap");
            fLLVMIntHeap = llvm_compute_args_it++;
            llvm_compute_args_it->setName("real_heap");
            fLLVMRealHeap = llvm_compute_args_it++;
            llvm_compute_args_it->setName("inputs");
            fLLVMInputs = llvm_compute_args_it++;
            llvm_compute_args_it->setName("outputs");
            fLLVMOutputs = llvm_compute_args_it++;
            
            // Optimize indexed load/store
            /*
            this->fFactory->fStaticInitBlock = FIRInstructionOptimizer<T>::optimizeBlock(this->fFactory->fStaticInitBlock, 1, 1);
            this->fFactory->fInitBlock = FIRInstructionOptimizer<T>::optimizeBlock(this->fFactory->fInitBlock, 1, 1);
            this->fFactory->fResetUIBlock = FIRInstructionOptimizer<T>::optimizeBlock(this->fFactory->fResetUIBlock, 1, 1);
            this->fFactory->fClearBlock = FIRInstructionOptimizer<T>::optimizeBlock(this->fFactory->fClearBlock, 1, 1);
            this->fFactory->fComputeBlock = FIRInstructionOptimizer<T>::optimizeBlock(this->fFactory->fComputeBlock, 1, 1);
            this->fFactory->fComputeDSPBlock = FIRInstructionOptimizer<T>::optimizeBlock(this->fFactory->fComputeDSPBlock, 1, 1);
            */
            
            compute_block->write(&std::cout);
            
            // Compile compute body
            CompileBlock(compute_block, code_block);
            
            // Get last block of post code section
            BasicBlock* last_block = fBuilder->GetInsertBlock();
            // Add return
            ReturnInst::Create(fModule->getContext(), last_block);
            
            // Check function
            verifyFunction(*llvm_compute);
            
            dumpLLVM1(fModule);
            
            // For host target support
            InitializeNativeTarget();
            InitializeNativeTargetAsmPrinter();
            InitializeNativeTargetAsmParser();
            
            EngineBuilder builder((std::unique_ptr<Module>(fModule)));
            TargetMachine* tm = builder.selectTarget();
            builder.setOptLevel(CodeGenOpt::Aggressive);
            builder.setEngineKind(EngineKind::JIT);
            
            fJIT = builder.create(tm);
            legacy::PassManager pm;
            pm.add(createVerifierPass());
            pm.run(*fModule);
            
            // Get 'compute' entry point
            fCompute = (llvmComputeFun)fJIT->getFunctionAddress("compute");
        }
    
        virtual ~FIRLLVMCompiler()
        {
            // fModule is kept and deleted by fJIT
            delete fJIT;
            delete fBuilder;
            delete fContext;
        }
    
        void Compute(int* int_heap, T* real_heap, T** inputs, T** outputs)
        {
            fCompute(int_heap, real_heap, inputs, outputs);
        }

};

#endif
