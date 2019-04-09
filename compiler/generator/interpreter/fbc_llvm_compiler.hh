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

#ifndef _FBC_LLVM_COMPILER_H
#define _FBC_LLVM_COMPILER_H

#include <map>
#include <string>
#include <vector>

#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Initialization.h>
#include <llvm-c/Target.h>
#include <llvm-c/Transforms/PassManagerBuilder.h>
#include <llvm-c/Transforms/Vectorize.h>

#include "fbc_interpreter.hh"
#include "interpreter_bytecode.hh"

#define dispatchReturn() \
    {                    \
        it = popAddr();  \
    }
#define saveReturn()      \
    {                     \
        pushAddr(it + 1); \
    }

// FBC LLVM compiler
template <class T>
class FBCLLVMCompiler {
    typedef void (*compiledFun)(int* int_heap, T* real_heap, T** inputs, T** outputs);

   protected:
    LLVMExecutionEngineRef fJIT;
    LLVMModuleRef          fModule;
    LLVMBuilderRef         fBuilder;
    compiledFun            fCompiledFun;

    LLVMValueRef  fLLVMStack[512];
    InstructionIT fAddressStack[64];

    int fLLVMStackIndex;
    int fAddrStackIndex;

    LLVMValueRef fLLVMIntHeap;
    LLVMValueRef fLLVMRealHeap;
    LLVMValueRef fLLVMInputs;
    LLVMValueRef fLLVMOutputs;

    LLVMValueRef genFloat(float num) { return LLVMConstReal(LLVMFloatType(), num); }
    LLVMValueRef genDouble(double num) { return LLVMConstReal(LLVMDoubleType(), num); }
    LLVMValueRef genReal(double num) { return (sizeof(T) == sizeof(double)) ? genDouble(num) : genFloat(num); }
    LLVMValueRef genInt32(int num) { return LLVMConstInt(LLVMInt32Type(), num, true); }
    LLVMValueRef genInt64(long long num) { return LLVMConstInt(LLVMInt64Type(), num, true); }

    LLVMTypeRef getFloatTy() { return LLVMFloatType(); }
    LLVMTypeRef getInt32Ty() { return LLVMInt32Type(); }
    LLVMTypeRef getInt64Ty() { return LLVMInt64Type(); }
    LLVMTypeRef getInt1Ty() { return LLVMInt1Type(); }
    LLVMTypeRef getDoubleTy() { return LLVMDoubleType(); }
    LLVMTypeRef getRealTy() { return (sizeof(T) == sizeof(double)) ? getDoubleTy() : getFloatTy(); }

    std::string getMathName(const std::string& name) { return (sizeof(T) == sizeof(float)) ? (name + "f") : name; }

    void         pushValue(LLVMValueRef val) { fLLVMStack[fLLVMStackIndex++] = val; }
    LLVMValueRef popValue() { return fLLVMStack[--fLLVMStackIndex]; }

    void          pushAddr(InstructionIT addr) { fAddressStack[fAddrStackIndex++] = addr; }
    InstructionIT popAddr() { return fAddressStack[--fAddrStackIndex]; }
    bool          emptyReturn() { return (fAddrStackIndex == 0); }

    void pushBinop(LLVMOpcode op)
    {
        LLVMValueRef v1 = popValue();
        LLVMValueRef v2 = popValue();
        pushValue(LLVMBuildBinOp(fBuilder, op, v1, v2, ""));
    }

    void pushRealComp(LLVMRealPredicate op)
    {
        LLVMValueRef v1         = popValue();
        LLVMValueRef v2         = popValue();
        LLVMValueRef cond_value = LLVMBuildFCmp(fBuilder, op, v1, v2, "");
        pushValue(LLVMBuildSelect(fBuilder, cond_value, genInt32(1), genInt32(0), ""));
    }

    void pushIntComp(LLVMIntPredicate op)
    {
        LLVMValueRef v1         = popValue();
        LLVMValueRef v2         = popValue();
        LLVMValueRef cond_value = LLVMBuildICmp(fBuilder, op, v1, v2, "");
        pushValue(LLVMBuildSelect(fBuilder, cond_value, genInt32(1), genInt32(0), ""));
    }

    // Min/max
    void pushIntMax()
    {
        LLVMValueRef v1         = popValue();
        LLVMValueRef v2         = popValue();
        LLVMValueRef cond_value = LLVMBuildICmp(fBuilder, LLVMIntSLT, v1, v2, "");
        pushValue(LLVMBuildSelect(fBuilder, cond_value, v2, v1, ""));
    }

    void pushIntMin()
    {
        LLVMValueRef v1         = popValue();
        LLVMValueRef v2         = popValue();
        LLVMValueRef cond_value = LLVMBuildICmp(fBuilder, LLVMIntSLT, v1, v2, "");
        pushValue(LLVMBuildSelect(fBuilder, cond_value, v1, v2, ""));
    }

    void pushRealMax()
    {
        LLVMValueRef v1         = popValue();
        LLVMValueRef v2         = popValue();
        LLVMValueRef cond_value = LLVMBuildFCmp(fBuilder, LLVMRealOLT, v1, v2, "");
        pushValue(LLVMBuildSelect(fBuilder, cond_value, v2, v1, ""));
    }

    void pushRealMin()
    {
        LLVMValueRef v1         = popValue();
        LLVMValueRef v2         = popValue();
        LLVMValueRef cond_value = LLVMBuildFCmp(fBuilder, LLVMRealOLT, v1, v2, "");
        pushValue(LLVMBuildSelect(fBuilder, cond_value, v1, v2, ""));
    }

    void pushUnaryCall(const std::string& name_aux, LLVMTypeRef type, bool rename)
    {
        std::string  name     = (rename) ? getMathName(name_aux) : name_aux;
        LLVMValueRef function = LLVMGetNamedFunction(fModule, name.c_str());
        if (!function) {
            // Define it
            LLVMTypeRef param_types[] = {type};
            LLVMTypeRef ret_type      = LLVMFunctionType(type, param_types, 1, false);
            function                  = LLVMAddFunction(fModule, name.c_str(), ret_type);
        }
        // Create the function call
        LLVMValueRef fun_args[] = {popValue()};
        pushValue(LLVMBuildCall(fBuilder, function, fun_args, 1, ""));
    }

    void pushUnaryIntCall(const std::string& name, bool rename = true)
    {
        return pushUnaryCall(name, getInt32Ty(), rename);
    }
    void pushUnaryRealCall(const std::string& name, bool rename = true)
    {
        return pushUnaryCall(name, getRealTy(), rename);
    }

    void pushBinaryCall(const std::string& name_aux, LLVMTypeRef type)
    {
        std::string  name     = getMathName(name_aux);
        LLVMValueRef function = LLVMGetNamedFunction(fModule, name.c_str());
        if (!function) {
            // Define it
            LLVMTypeRef param_types[] = {type, type};
            LLVMTypeRef ret_type      = LLVMFunctionType(type, param_types, 2, false);
            function                  = LLVMAddFunction(fModule, name.c_str(), ret_type);
        }
        // Create the function call
        LLVMValueRef fun_args[] = {popValue(), popValue()};
        pushValue(LLVMBuildCall(fBuilder, function, fun_args, 2, ""));
    }

    void pushBinaryIntCall(const std::string& name) { pushBinaryCall(name, getInt32Ty()); }

    void pushBinaryRealCall(const std::string& name) { pushBinaryCall(name, getRealTy()); }

    void pushLoadArray(LLVMValueRef array, int index) { pushLoadArray(array, genInt32(index)); }

    void pushStoreArray(LLVMValueRef array, int index) { pushStoreArray(array, genInt32(index)); }

    void pushLoadArray(LLVMValueRef array, LLVMValueRef index)
    {
        LLVMValueRef idx[]    = {index};
        LLVMValueRef load_ptr = LLVMBuildInBoundsGEP(fBuilder, array, idx, 1, "");
        pushValue(LLVMBuildLoad(fBuilder, load_ptr, ""));
    }

    void pushStoreArray(LLVMValueRef array, LLVMValueRef index)
    {
        LLVMValueRef idx[]     = {index};
        LLVMValueRef store_ptr = LLVMBuildInBoundsGEP(fBuilder, array, idx, 1, "");
        LLVMBuildStore(fBuilder, popValue(), store_ptr);
    }

    void pushLoadInput(int index)
    {
        LLVMValueRef idx1[]        = {genInt32(index)};
        LLVMValueRef input_ptr_ptr = LLVMBuildInBoundsGEP(fBuilder, fLLVMInputs, idx1, 1, "");
        LLVMValueRef input_ptr     = LLVMBuildLoad(fBuilder, input_ptr_ptr, "");
        LLVMValueRef idx2[]        = {popValue()};
        LLVMValueRef input         = LLVMBuildInBoundsGEP(fBuilder, input_ptr, idx2, 1, "");
        pushValue(LLVMBuildLoad(fBuilder, input, ""));
    }

    void pushStoreOutput(int index)
    {
        LLVMValueRef idx1[]         = {genInt32(index)};
        LLVMValueRef output_ptr_ptr = LLVMBuildInBoundsGEP(fBuilder, fLLVMOutputs, idx1, 1, "");
        LLVMValueRef output_ptr     = LLVMBuildLoad(fBuilder, output_ptr_ptr, "");
        LLVMValueRef idx2[]         = {popValue()};
        LLVMValueRef output         = LLVMBuildInBoundsGEP(fBuilder, output_ptr, idx2, 1, "");
        LLVMBuildStore(fBuilder, popValue(), output);
    }

    void CompileBlock(FBCBlockInstruction<T>* block, LLVMBasicBlockRef code_block)
    {
        InstructionIT it  = block->fInstructions.begin();
        bool          end = false;

        // Insert in the current block
        LLVMPositionBuilderAtEnd(fBuilder, code_block);

        while ((it != block->fInstructions.end()) && !end) {
            //(*it)->write(&std::cout);

            switch ((*it)->fOpcode) {
                    // Numbers
                case FBCInstruction::kRealValue:
                    pushValue(genReal((*it)->fRealValue));
                    it++;
                    break;

                case FBCInstruction::kInt32Value:
                    pushValue(genInt32((*it)->fIntValue));
                    it++;
                    break;

                    // Memory load/store
                case FBCInstruction::kLoadReal:
                    pushLoadArray(fLLVMRealHeap, (*it)->fOffset1);
                    it++;
                    break;

                case FBCInstruction::kLoadInt:
                    pushLoadArray(fLLVMIntHeap, (*it)->fOffset1);
                    it++;
                    break;

                case FBCInstruction::kStoreReal:
                    pushStoreArray(fLLVMRealHeap, (*it)->fOffset1);
                    it++;
                    break;

                case FBCInstruction::kStoreInt:
                    pushStoreArray(fLLVMIntHeap, (*it)->fOffset1);
                    it++;
                    break;

                    // Indexed memory load/store: constant values are added at generation time by CreateBinOp...
                case FBCInstruction::kLoadIndexedReal: {
                    LLVMValueRef offset = LLVMBuildAdd(fBuilder, genInt32((*it)->fOffset1), popValue(), "");
                    pushLoadArray(fLLVMRealHeap, offset);
                    it++;
                    break;
                }

                case FBCInstruction::kLoadIndexedInt: {
                    LLVMValueRef offset = LLVMBuildAdd(fBuilder, genInt32((*it)->fOffset1), popValue(), "");
                    pushLoadArray(fLLVMIntHeap, offset);
                    it++;
                    break;
                }

                case FBCInstruction::kStoreIndexedReal: {
                    LLVMValueRef offset = LLVMBuildAdd(fBuilder, genInt32((*it)->fOffset1), popValue(), "");
                    pushStoreArray(fLLVMRealHeap, offset);
                    it++;
                    break;
                }

                case FBCInstruction::kStoreIndexedInt: {
                    LLVMValueRef offset = LLVMBuildAdd(fBuilder, genInt32((*it)->fOffset1), popValue(), "");
                    pushStoreArray(fLLVMIntHeap, offset);
                    it++;
                    break;
                }

                    // Memory shift
                case FBCInstruction::kBlockShiftReal: {
                    for (int i = (*it)->fOffset1; i > (*it)->fOffset2; i -= 1) {
                        pushLoadArray(fLLVMRealHeap, i - 1);
                        pushStoreArray(fLLVMRealHeap, i);
                    }
                    it++;
                    break;
                }

                case FBCInstruction::kBlockShiftInt: {
                    for (int i = (*it)->fOffset1; i > (*it)->fOffset2; i -= 1) {
                        pushLoadArray(fLLVMIntHeap, i - 1);
                        pushStoreArray(fLLVMIntHeap, i);
                    }
                    it++;
                    break;
                }

                    // Input/output
                case FBCInstruction::kLoadInput:
                    pushLoadInput((*it)->fOffset1);
                    it++;
                    break;

                case FBCInstruction::kStoreOutput:
                    pushStoreOutput((*it)->fOffset1);
                    it++;
                    break;

                    // Cast
                case FBCInstruction::kCastReal: {
                    LLVMValueRef val = popValue();
                    pushValue(LLVMBuildSIToFP(fBuilder, val, getRealTy(), ""));
                    it++;
                    break;
                }

                case FBCInstruction::kCastInt: {
                    LLVMValueRef val = popValue();
                    pushValue(LLVMBuildFPToSI(fBuilder, val, getInt32Ty(), ""));
                    it++;
                    break;
                }

                case FBCInstruction::kBitcastInt: {
                    LLVMValueRef val = popValue();
                    pushValue(LLVMBuildBitCast(fBuilder, val, getInt32Ty(), ""));
                    it++;
                    break;
                }

                case FBCInstruction::kBitcastReal: {
                    LLVMValueRef val = popValue();
                    pushValue(LLVMBuildBitCast(fBuilder, val, getRealTy(), ""));
                    it++;
                    break;
                }

                    // Binary math
                case FBCInstruction::kAddReal:
                    pushBinop(LLVMFAdd);
                    it++;
                    break;

                case FBCInstruction::kAddInt:
                    pushBinop(LLVMAdd);
                    it++;
                    break;

                case FBCInstruction::kSubReal:
                    pushBinop(LLVMFSub);
                    it++;
                    break;

                case FBCInstruction::kSubInt:
                    pushBinop(LLVMSub);
                    it++;
                    break;

                case FBCInstruction::kMultReal:
                    pushBinop(LLVMFMul);
                    it++;
                    break;

                case FBCInstruction::kMultInt:
                    pushBinop(LLVMMul);
                    it++;
                    break;

                case FBCInstruction::kDivReal:
                    pushBinop(LLVMFDiv);
                    it++;
                    break;

                case FBCInstruction::kDivInt:
                    pushBinop(LLVMSDiv);
                    it++;
                    break;

                case FBCInstruction::kRemReal:
                    pushBinaryRealCall("remainder");
                    it++;
                    break;

                case FBCInstruction::kRemInt:
                    pushBinop(LLVMSRem);
                    it++;
                    break;

                case FBCInstruction::kLshInt:
                    pushBinop(LLVMShl);
                    it++;
                    break;

                case FBCInstruction::kRshInt:
                    pushBinop(LLVMLShr);
                    it++;
                    break;

                case FBCInstruction::kGTInt:
                    pushIntComp(LLVMIntSGT);
                    it++;
                    break;

                case FBCInstruction::kLTInt:
                    pushIntComp(LLVMIntSLT);
                    it++;
                    break;

                case FBCInstruction::kGEInt:
                    pushIntComp(LLVMIntSGE);
                    it++;
                    break;

                case FBCInstruction::kLEInt:
                    pushIntComp(LLVMIntSLE);
                    it++;
                    break;

                case FBCInstruction::kEQInt:
                    pushIntComp(LLVMIntEQ);
                    it++;
                    break;

                case FBCInstruction::kNEInt:
                    pushIntComp(LLVMIntNE);
                    it++;
                    break;

                case FBCInstruction::kGTReal:
                    pushRealComp(LLVMRealOGT);
                    it++;
                    break;

                case FBCInstruction::kLTReal:
                    pushRealComp(LLVMRealOLT);
                    it++;
                    break;

                case FBCInstruction::kGEReal:
                    pushRealComp(LLVMRealOGE);
                    it++;
                    break;

                case FBCInstruction::kLEReal:
                    pushRealComp(LLVMRealOLE);
                    it++;
                    break;

                case FBCInstruction::kEQReal:
                    pushRealComp(LLVMRealOEQ);
                    it++;
                    break;

                case FBCInstruction::kNEReal:
                    pushRealComp(LLVMRealONE);
                    it++;
                    break;

                case FBCInstruction::kANDInt:
                    pushBinop(LLVMAnd);
                    it++;
                    break;

                case FBCInstruction::kORInt:
                    pushBinop(LLVMOr);
                    it++;
                    break;

                case FBCInstruction::kXORInt:
                    pushBinop(LLVMXor);
                    it++;
                    break;

                    // Extended unary math
                case FBCInstruction::kAbs:
                    pushUnaryIntCall("abs", false);
                    it++;
                    break;

                case FBCInstruction::kAbsf:
                    pushUnaryRealCall("fabs");
                    it++;
                    break;

                case FBCInstruction::kAcosf:
                    pushUnaryRealCall("acos");
                    it++;
                    break;

                case FBCInstruction::kAsinf:
                    pushUnaryRealCall("asin");
                    it++;
                    break;

                case FBCInstruction::kAtanf:
                    pushUnaryRealCall("atan");
                    it++;
                    break;

                case FBCInstruction::kCeilf:
                    pushUnaryRealCall("ceil");
                    it++;
                    break;

                case FBCInstruction::kCosf:
                    pushUnaryRealCall("cos");
                    it++;
                    break;

                case FBCInstruction::kCoshf:
                    pushUnaryRealCall("cosh");
                    it++;
                    break;

                case FBCInstruction::kExpf:
                    pushUnaryRealCall("exp");
                    it++;
                    break;

                case FBCInstruction::kFloorf:
                    pushUnaryRealCall("floor");
                    it++;
                    break;

                case FBCInstruction::kLogf:
                    pushUnaryRealCall("log");
                    it++;
                    break;

                case FBCInstruction::kLog10f:
                    pushUnaryRealCall("log10");
                    it++;
                    break;

                case FBCInstruction::kRoundf:
                    pushUnaryRealCall("round");
                    it++;
                    break;

                case FBCInstruction::kSinf:
                    pushUnaryRealCall("sin");
                    it++;
                    break;

                case FBCInstruction::kSinhf:
                    pushUnaryRealCall("sinh");
                    it++;
                    break;

                case FBCInstruction::kSqrtf:
                    pushUnaryRealCall("sqrt");
                    it++;
                    break;

                case FBCInstruction::kTanf:
                    pushUnaryRealCall("tan");
                    it++;
                    break;

                case FBCInstruction::kTanhf:
                    pushUnaryRealCall("tanh");
                    it++;
                    break;

                    // Extended binary math
                case FBCInstruction::kAtan2f:
                    pushBinaryRealCall("atan2");
                    it++;
                    break;

                case FBCInstruction::kFmodf:
                    pushBinaryRealCall("fmod");
                    it++;
                    break;

                case FBCInstruction::kPowf:
                    pushBinaryRealCall("pow");
                    it++;
                    break;

                case FBCInstruction::kMax: {
                    pushIntMax();
                    it++;
                    break;
                }

                case FBCInstruction::kMaxf: {
                    pushRealMax();
                    it++;
                    break;
                }

                case FBCInstruction::kMin: {
                    pushIntMin();
                    it++;
                    break;
                }

                case FBCInstruction::kMinf: {
                    pushRealMin();
                    it++;
                    break;
                }

                    // Control
                case FBCInstruction::kReturn:
                    // Empty addr stack = end of computation
                    if (emptyReturn()) {
                        end = true;
                    } else {
                        dispatchReturn();
                    }
                    break;

                case FBCInstruction::kIf: {
                    saveReturn();

                    // Prepare condition
                    LLVMValueRef cond_value =
                        LLVMBuildICmp(fBuilder, LLVMIntEQ, popValue(), genInt32(1), "select_cond");
                    LLVMValueRef function = LLVMGetBasicBlockParent(LLVMGetInsertBlock(fBuilder));

                    // Create blocks for the then and else cases. Insert the 'then' block at the end of the function
                    LLVMBasicBlockRef then_block  = LLVMAppendBasicBlock(function, "then_block");
                    LLVMBasicBlockRef else_block  = LLVMAppendBasicBlock(function, "else_block");
                    LLVMBasicBlockRef merge_block = LLVMAppendBasicBlock(function, "merge_block");

                    LLVMBuildCondBr(fBuilder, cond_value, then_block, else_block);

                    // Compile then branch (= branch1)
                    CompileBlock((*it)->fBranch1, then_block);
                    LLVMBuildBr(fBuilder, merge_block);

                    // Compile else branch (= branch2)
                    CompileBlock((*it)->fBranch2, else_block);
                    LLVMBuildBr(fBuilder, merge_block);

                    // Insert in next_block
                    LLVMPositionBuilderAtEnd(fBuilder, merge_block);

                    it++;
                    break;
                }

                case FBCInstruction::kSelectReal:
                case FBCInstruction::kSelectInt: {
                    // Prepare condition
                    LLVMValueRef cond_value =
                        LLVMBuildICmp(fBuilder, LLVMIntNE, popValue(), genInt32(0), "select_cond");

                    // Compile then branch (= branch1)
                    CompileBlock((*it)->fBranch1, code_block);

                    // Compile else branch (= branch2)
                    CompileBlock((*it)->fBranch2, code_block);

                    // Create the result (= branch2)
                    LLVMValueRef then_value = popValue();
                    LLVMValueRef else_value = popValue();
                    // Inverted here
                    pushValue(LLVMBuildSelect(fBuilder, cond_value, else_value, then_value, ""));

                    it++;
                    break;
                }

                case FBCInstruction::kCondBranch: {
                    // Prepare condition
                    LLVMValueRef cond_value = LLVMBuildTrunc(fBuilder, popValue(), getInt1Ty(), "");

                    LLVMValueRef      function   = LLVMGetBasicBlockParent(LLVMGetInsertBlock(fBuilder));
                    LLVMBasicBlockRef next_block = LLVMAppendBasicBlock(function, "next_block");

                    // Branch to current block
                    LLVMBuildCondBr(fBuilder, cond_value, code_block, next_block);

                    // Insert in next_block
                    LLVMPositionBuilderAtEnd(fBuilder, next_block);

                    it++;
                    break;
                }

                case FBCInstruction::kLoop: {
                    LLVMValueRef      function        = LLVMGetBasicBlockParent(LLVMGetInsertBlock(fBuilder));
                    LLVMBasicBlockRef init_block      = LLVMAppendBasicBlock(function, "init_block");
                    LLVMBasicBlockRef loop_body_block = LLVMAppendBasicBlock(function, "loop_body_block");

                    // Link previous_block and init_block
                    LLVMBuildBr(fBuilder, init_block);

                    // Compile init branch (= branch1)
                    CompileBlock((*it)->fBranch1, init_block);

                    // Link previous_block and loop_body_block
                    LLVMBuildBr(fBuilder, loop_body_block);

                    // Compile loop branch (= branch2)
                    CompileBlock((*it)->fBranch2, loop_body_block);

                    it++;
                    break;
                }

                default:
                    (*it)->write(&std::cout);
                    faustassert(false);
                    break;
            }
        }
    }

   public:
    FBCLLVMCompiler(FBCBlockInstruction<T>* fbc_block)
    {
        fLLVMStackIndex = 0;
        fAddrStackIndex = 0;

        LLVMInitializeCore(LLVMGetGlobalPassRegistry());

        /*
        LLVMInitializeTransformUtils(LLVMGetGlobalPassRegistry());
        LLVMInitializeScalarOpts(LLVMGetGlobalPassRegistry());
        LLVMInitializeObjCARCOpts(LLVMGetGlobalPassRegistry());
        LLVMInitializeVectorization(LLVMGetGlobalPassRegistry());
        LLVMInitializeInstCombine(LLVMGetGlobalPassRegistry());
        LLVMInitializeIPO(LLVMGetGlobalPassRegistry());
        LLVMInitializeInstrumentation(LLVMGetGlobalPassRegistry());
        LLVMInitializeAnalysis(LLVMGetGlobalPassRegistry());
        LLVMInitializeIPA(LLVMGetGlobalPassRegistry());
        LLVMInitializeCodeGen(LLVMGetGlobalPassRegistry());
        LLVMInitializeTarget(LLVMGetGlobalPassRegistry());
        */

        fBuilder     = LLVMCreateBuilder();
        fModule      = LLVMModuleCreateWithName(FAUSTVERSION);
        char* triple = LLVMGetDefaultTargetTriple();
        LLVMSetTarget(fModule, triple);

        // Compile compute function
        LLVMTypeRef param_types[] = {LLVMPointerType(getInt32Ty(), 0), LLVMPointerType(getRealTy(), 0),
                                     LLVMPointerType(LLVMPointerType(getRealTy(), 0), 0),
                                     LLVMPointerType(LLVMPointerType(getRealTy(), 0), 0)};

        LLVMTypeRef  execute_type = LLVMFunctionType(LLVMVoidType(), param_types, 4, false);
        LLVMValueRef execute      = LLVMAddFunction(fModule, "execute", execute_type);

        LLVMBasicBlockRef code_block = LLVMAppendBasicBlock(execute, "entry_block");

        fLLVMIntHeap  = LLVMGetParam(execute, 0);
        fLLVMRealHeap = LLVMGetParam(execute, 1);
        fLLVMInputs   = LLVMGetParam(execute, 2);
        fLLVMOutputs  = LLVMGetParam(execute, 3);

#if defined(LLVM_50) || defined(LLVM_60)
        LLVMSetValueName(fLLVMIntHeap, "int_heap");
        LLVMSetValueName(fLLVMRealHeap, "real_heap");
        LLVMSetValueName(fLLVMInputs, "inputs");
        LLVMSetValueName(fLLVMOutputs, "outputs");
#else
        LLVMSetValueName2(fLLVMIntHeap, "int_heap", 8);
        LLVMSetValueName2(fLLVMRealHeap, "real_heap", 9);
        LLVMSetValueName2(fLLVMInputs, "inputs", 6);
        LLVMSetValueName2(fLLVMOutputs, "outputs", 7);
#endif

        // fbc_block->write(&std::cout);

        // Compile compute body
        CompileBlock(fbc_block, code_block);

        // Add return
        LLVMBuildRetVoid(fBuilder);

        // LLVMDumpModule(fModule);

        // For host target support
        LLVMLinkInMCJIT();
        LLVMInitializeNativeTarget();
        LLVMInitializeNativeAsmPrinter();
        LLVMInitializeNativeAsmParser();

        char* error;
        LLVMCreateJITCompilerForModule(&fJIT, fModule, LLVMCodeGenLevelAggressive, &error);

        /*
        // Setup optimizations
        LLVMPassManagerBuilderRef pass_buider = LLVMPassManagerBuilderCreate();
        LLVMPassManagerBuilderSetOptLevel(pass_buider, 3);
        LLVMPassManagerBuilderSetSizeLevel(pass_buider, 0);

        LLVMPassManagerRef function_passes = LLVMCreateFunctionPassManagerForModule(fModule);

        LLVMPassManagerBuilderPopulateFunctionPassManager(pass_buider, function_passes);

        LLVMAddSLPVectorizePass(function_passes);
        LLVMAddSLPVectorizePass(function_passes);

        LLVMPassManagerRef module_passes = LLVMCreatePassManager();
        LLVMPassManagerBuilderPopulateModulePassManager(pass_buider, module_passes);

        LLVMInitializeFunctionPassManager(function_passes);
        LLVMRunFunctionPassManager(function_passes, execute);
        LLVMFinalizeFunctionPassManager(function_passes);

        LLVMRunPassManager(module_passes, fModule);

        LLVMDisposePassManager(function_passes);
        LLVMDisposePassManager(module_passes);
        LLVMPassManagerBuilderDispose(pass_buider);
        */

        // LLVMDumpModule(fModule);

        // Get 'execute' entry point
        fCompiledFun = (compiledFun)LLVMGetFunctionAddress(fJIT, "execute");

        LLVMDisposeMessage(triple);
    }

    virtual ~FBCLLVMCompiler()
    {
        LLVMDisposeBuilder(fBuilder);
        // fModule is deallocated by fJIT
        LLVMDisposeExecutionEngine(fJIT);
        LLVMShutdown();
    }

    void Execute(int* int_heap, T* real_heap, T** inputs, T** outputs)
    {
        fCompiledFun(int_heap, real_heap, inputs, outputs);
    }
};

// FBC compiler
template <class T>
class FBCCompiler : public FBCInterpreter<T, 0> {
   public:
    typedef typename std::map<FBCBlockInstruction<T>*, FBCLLVMCompiler<T>*>           CompiledBlocksType;
    typedef typename std::map<FBCBlockInstruction<T>*, FBCLLVMCompiler<T>*>::iterator CompiledBlocksTypeIT;

    FBCCompiler(interpreter_dsp_factory_aux<T, 0>* factory, CompiledBlocksType* map) : FBCInterpreter<T, 0>(factory)
    {
        fCompiledBlocks = map;

        // FBC blocks compilation
        // CompileBlock(factory->fComputeBlock);
        CompileBlock(factory->fComputeDSPBlock);
    }

    virtual ~FBCCompiler() {}

    void ExecuteBlock(FBCBlockInstruction<T>* block, bool compile)
    {
        if (compile && fCompiledBlocks->find(block) == fCompiledBlocks->end()) {
            CompileBlock(block);
        }

        // The 'DSP' compute block only is compiled..
        if (fCompiledBlocks->find(block) != fCompiledBlocks->end()) {
            ((*fCompiledBlocks)[block])->Execute(this->fIntHeap, this->fRealHeap, this->fInputs, this->fOutputs);
        } else {
            FBCInterpreter<T, 0>::ExecuteBlock(block);
        }
    }

   protected:
    CompiledBlocksType* fCompiledBlocks;

    void CompileBlock(FBCBlockInstruction<T>* block)
    {
        if (fCompiledBlocks->find(block) == fCompiledBlocks->end()) {
            (*fCompiledBlocks)[block] = new FBCLLVMCompiler<T>(block);
        } else {
            // std::cout << "FBCCompiler: reuse compiled block" << std::endl;
        }
    }
};

#endif
