/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2019-2020 GRAME, Centre National de Creation Musicale
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

#include "interpreter_bytecode.hh"
#include "fbc_executor.hh"

// FBC LLVM compiler
template <class REAL>
class FBCLLVMCompiler : public FBCExecuteFun<REAL> {

  private:
    typedef void (*compiledFun)(int* int_heap, REAL* real_heap, REAL** inputs, REAL** outputs);
    
    LLVMExecutionEngineRef fJIT;
    LLVMModuleRef          fModule;
    LLVMBuilderRef         fBuilder;
    LLVMBuilderRef         fAllocaBuilder;
    compiledFun            fCompiledFun;

    LLVMValueRef  fLLVMStack[512];
    int fLLVMStackIndex;
  
    LLVMValueRef fLLVMIntHeap;
    LLVMValueRef fLLVMRealHeap;
    LLVMValueRef fLLVMInputs;
    LLVMValueRef fLLVMOutputs;
    
    // Global variable for all soundfiles
    LLVMValueRef fLLVMSoundTable;
    // Associate the soundfile name with its index in fLLVMSoundTable
    std::map<std::string, LLVMValueRef> fSoundTableID;
    
    LLVMValueRef genFloat(float num) { return LLVMConstReal(LLVMFloatType(), num); }
    LLVMValueRef genDouble(double num) { return LLVMConstReal(LLVMDoubleType(), num); }
    LLVMValueRef genReal(double num) { return (sizeof(REAL) == sizeof(double)) ? genDouble(num) : genFloat(num); }
    LLVMValueRef genInt32(int num) { return LLVMConstInt(LLVMInt32Type(), num, true); }
    LLVMValueRef genInt64(int64_t num) { return LLVMConstInt(LLVMInt64Type(), num, true); }
    LLVMValueRef genUInt64(uint64_t num) { return LLVMConstInt(LLVMInt64Type(), num, true); }

    LLVMTypeRef getFloatTy() { return LLVMFloatType(); }
    LLVMTypeRef getDoubleTy() { return LLVMDoubleType(); }
    LLVMTypeRef getRealTy() { return (sizeof(REAL) == sizeof(double)) ? getDoubleTy() : getFloatTy(); }
    LLVMTypeRef getRealTyPtr() { return LLVMPointerType(getRealTy(), 0); }
    LLVMTypeRef getRealTyPtrPtr() { return LLVMPointerType(getRealTyPtr(), 0); }
    LLVMTypeRef getInt32Ty() { return LLVMInt32Type(); }
    LLVMTypeRef getInt32TyPtr() { return LLVMPointerType(getInt32Ty(), 0); }
    LLVMTypeRef getInt64Ty() { return LLVMInt64Type(); }
    LLVMTypeRef getBoolTy() { return LLVMInt1Type(); }
    LLVMTypeRef getInt8TyPtr() { return LLVMPointerType(LLVMInt8Type(), 0); }
    
    LLVMTypeRef genSoundFileTy()
    {
       LLVMTypeRef types[] = {
            getInt8TyPtr(),
            getInt32TyPtr(),
            getInt32TyPtr(),
            getInt32TyPtr(),
            getInt32Ty(),
            getInt32Ty(),
            getInt32Ty()
        };
        return LLVMStructType(types, 7, true);
    }
    
    LLVMTypeRef genSoundFileTyPtr() { return LLVMPointerType(genSoundFileTy(), 0); }
  
    std::string getMathName(const std::string& name) { return (sizeof(REAL) == sizeof(float)) ? (name + "f") : name; }

    void         pushValue(LLVMValueRef val) { fLLVMStack[fLLVMStackIndex++] = val; }
    LLVMValueRef popValue() { return fLLVMStack[--fLLVMStackIndex]; }

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

    void pushUnaryCall(const std::string& name_aux, LLVMTypeRef res_type, LLVMTypeRef atype, bool rename)
    {
        std::string  name        = (rename) ? getMathName(name_aux) : name_aux;
        LLVMValueRef function    = LLVMGetNamedFunction(fModule, name.c_str());
        LLVMTypeRef args_types[] = { atype };
        LLVMTypeRef rtype        = LLVMFunctionType(res_type, args_types, 1, false);
        if (!function) {
            // Define it
            function = LLVMAddFunction(fModule, name.c_str(), rtype);
        }
        // Create the function call
        LLVMValueRef fun_args[] = { popValue() };
        pushValue(LLVMBuildCall2(fBuilder, rtype, function, fun_args, 1, ""));
    }

    void pushUnaryIntCall(const std::string& name, bool rename = true)
    {
        return pushUnaryCall(name, getInt32Ty(), getInt32Ty(), rename);
    }
    
    void pushUnaryRealCall(const std::string& name, bool rename = true)
    {
        return pushUnaryCall(name, getRealTy(), getRealTy(), rename);
    }

    void pushBinaryCall(const std::string& name_aux, LLVMTypeRef res_type, LLVMTypeRef arg1_type, LLVMTypeRef arg2_type)
    {
        std::string  name        = getMathName(name_aux);
        LLVMValueRef function    = LLVMGetNamedFunction(fModule, name.c_str());
        LLVMTypeRef args_types[] = { arg1_type, arg2_type };
        LLVMTypeRef rtype        = LLVMFunctionType(res_type, args_types, 2, false);
        if (!function) {
            // Define it
            function = LLVMAddFunction(fModule, name.c_str(), rtype);
        }
        // Create the function call
        LLVMValueRef fun_args[] = { popValue(), popValue() };
        pushValue(LLVMBuildCall2(fBuilder, rtype, function, fun_args, 2, ""));
    }

    void pushBinaryIntCall(const std::string& name) { pushBinaryCall(name, getInt32Ty(), getInt32Ty(), getInt32Ty()); }

    void pushBinaryRealCall(const std::string& name) { pushBinaryCall(name, getRealTy(), getRealTy(), getRealTy()); }

    void pushLoadArray(LLVMValueRef array, int index, LLVMTypeRef type) { pushLoadArray(array, genInt32(index), type); }

    void pushStoreArray(LLVMValueRef array, int index, LLVMTypeRef type) { pushStoreArray(array, genInt32(index), type); }

    void pushLoadArray(LLVMValueRef array, LLVMValueRef index, LLVMTypeRef type)
    {
        LLVMValueRef idx[]    = { index };
        LLVMValueRef load_ptr = LLVMBuildInBoundsGEP2(fBuilder, type, array, idx, 1, "");
        pushValue(LLVMBuildLoad2(fBuilder, type, load_ptr, ""));
    }
    
    void pushLoadIndexedArray(LLVMValueRef array, LLVMValueRef index, int shift, LLVMTypeRef type)
    {
        LLVMValueRef offset = LLVMBuildAdd(fBuilder, genInt32(shift), index, "");
        pushLoadArray(array, offset, type);
    }

    void pushStoreArray(LLVMValueRef array, LLVMValueRef index, LLVMTypeRef type)
    {
        LLVMValueRef idx[]     = { index };
        LLVMValueRef store_ptr = LLVMBuildInBoundsGEP2(fBuilder, type, array, idx, 1, "");
        LLVMBuildStore(fBuilder, popValue(), store_ptr);
    }
    
    void pushStoreIndexedArray(LLVMValueRef array, LLVMValueRef index, int shift, LLVMTypeRef type)
    {
        LLVMValueRef offset = LLVMBuildAdd(fBuilder, genInt32(shift), index, "");
        pushStoreArray(array, offset, type);
    }

    void pushLoadInput(int index)
    {
        LLVMTypeRef type           = getRealTy();
        LLVMTypeRef type_ptr       = LLVMPointerType(type, 0);
        LLVMValueRef idx1[]        = { genInt32(index) };
        LLVMValueRef input_ptr_ptr = LLVMBuildInBoundsGEP2(fBuilder, type_ptr, fLLVMInputs, idx1, 1, "");
        LLVMValueRef input_ptr     = LLVMBuildLoad2(fBuilder, type_ptr, input_ptr_ptr, "");
        LLVMValueRef idx2[]        = { popValue() };
        LLVMValueRef input         = LLVMBuildInBoundsGEP2(fBuilder, type, input_ptr, idx2, 1, "");
        pushValue(LLVMBuildLoad2(fBuilder, type, input, ""));
    }

    void pushStoreOutput(int index)
    {
        LLVMTypeRef type            = getRealTy();
        LLVMTypeRef type_ptr        = LLVMPointerType(type, 0);
        LLVMValueRef idx1[]         = { genInt32(index) };
        LLVMValueRef output_ptr_ptr = LLVMBuildInBoundsGEP2(fBuilder, type_ptr, fLLVMOutputs, idx1, 1, "");
        LLVMValueRef output_ptr     = LLVMBuildLoad2(fBuilder, type_ptr, output_ptr_ptr, "");
        LLVMValueRef idx2[]         = { popValue() };
        LLVMValueRef output         = LLVMBuildInBoundsGEP2(fBuilder, type, output_ptr, idx2, 1, "");
        LLVMBuildStore(fBuilder, popValue(), output);
    }
    
    void pushLoadSoundFieldInt(const std::string& sf_name)
    {
        faustassert(this->fSoundTable.find(sf_name) != this->fSoundTable.end());
        
        // Load SoundFile
        LLVMValueRef idx0[]  = { fSoundTableID[sf_name] };
        LLVMValueRef gsf_ptr = LLVMBuildInBoundsGEP2(fBuilder, genSoundFileTyPtr(), fLLVMSoundTable, idx0, 1, "");
        LLVMValueRef sf_ptr  = LLVMBuildLoad2(fBuilder, genSoundFileTyPtr(), gsf_ptr, "");
        
        // Load SoundFile field
        LLVMValueRef field_index = popValue();
        LLVMValueRef idx1[]      = { field_index };
        LLVMValueRef field_ptr   = LLVMBuildInBoundsGEP2(fBuilder, getInt32TyPtr(), sf_ptr, idx1, 1, "");
        LLVMValueRef field       = LLVMBuildLoad2(fBuilder, getInt32TyPtr(), field_ptr, "");
        
        // Load SoundFile part in the field
        LLVMValueRef part        = popValue();
        LLVMValueRef idx2[]      = { part };
        LLVMValueRef part_ptr    = LLVMBuildInBoundsGEP2(fBuilder, getInt32Ty(), field, idx2, 1, "");
        pushValue(LLVMBuildLoad2(fBuilder, getInt32Ty(), part_ptr, ""));
    }
    
    void pushLoadSoundFieldReal(const std::string& sf_name)
    {
        faustassert(this->fSoundTable.find(sf_name) != this->fSoundTable.end());
        
        // Load SoundFile
        LLVMValueRef idx0[]  = { fSoundTableID[sf_name] };
        LLVMValueRef gsf_ptr = LLVMBuildInBoundsGEP2(fBuilder, genSoundFileTyPtr(), fLLVMSoundTable, idx0, 1, "");
        LLVMValueRef sf_ptr  = LLVMBuildLoad2(fBuilder, genSoundFileTyPtr(), gsf_ptr, "");
        
        // Load SoundFile buffer
        LLVMValueRef field_index = popValue();
        LLVMValueRef idx1[]      = { field_index };
        LLVMValueRef field_ptr   = LLVMBuildInBoundsGEP2(fBuilder, getInt8TyPtr(), sf_ptr, idx1, 1, "");
        LLVMValueRef field       = LLVMBuildLoad2(fBuilder, getInt8TyPtr(), field_ptr, "");
        LLVMValueRef real_field  = LLVMBuildBitCast(fBuilder, field, getRealTyPtr(), "");
        
        // Load SoundFile channel from the buffer
        LLVMValueRef chan        = popValue();
        LLVMValueRef idx2[]      = { chan };
        LLVMValueRef buffer_ptr  = LLVMBuildInBoundsGEP2(fBuilder, getRealTyPtr(), real_field, idx2, 1, "");
        LLVMValueRef buffer      = LLVMBuildLoad2(fBuilder, getRealTyPtr(), buffer_ptr, "");
        
        // Load SoundFile sample from the channel
        LLVMValueRef offset      = popValue();
        LLVMValueRef idx3[]      = { offset };
        LLVMValueRef sample_ptr  = LLVMBuildInBoundsGEP2(fBuilder, getRealTy(), buffer, idx3, 1, "");
        pushValue(LLVMBuildLoad2(fBuilder, getRealTy(), sample_ptr, ""));
    }
    
    // Select that computes both branches
    void createSelectBlock0(InstructionIT it, LLVMBasicBlockRef code_block)
    {
        // Prepare condition: compare condition to 0
        LLVMValueRef cond_value = LLVMBuildICmp(fBuilder, LLVMIntNE, popValue(), genInt32(0), "select_cond");
        
        // Compile then branch (= branch1)
        CompileBlock((*it)->fBranch1, code_block);
        
        // Compile else branch (= branch2)
        CompileBlock((*it)->fBranch2, code_block);
        
        // Create the result (= branch2)
        LLVMValueRef then_value = popValue();
        LLVMValueRef else_value = popValue();
        // Inverted here
        pushValue(LLVMBuildSelect(fBuilder, cond_value, else_value, then_value, ""));
    }
   
    // Select that only computes one branch
    void createSelectBlock1(InstructionIT it, LLVMValueRef typed_res, LLVMTypeRef type)
    {
        // Prepare condition: compare condition to 0
        LLVMValueRef cond_value = LLVMBuildICmp(fBuilder, LLVMIntNE, popValue(), genInt32(0), "select_cond");
        
        // Get enclosing function
        LLVMValueRef function = LLVMGetBasicBlockParent(LLVMGetInsertBlock(fBuilder));
        
        // Create blocks for the then and else cases. Insert the 'then' block at the end of the function
        LLVMBasicBlockRef then_block  = LLVMAppendBasicBlock(function, "select_then_block");
        LLVMBasicBlockRef else_block  = LLVMAppendBasicBlock(function, "select_else_block");
        LLVMBasicBlockRef merge_block = LLVMAppendBasicBlock(function, "select_merge_block");
        
        LLVMBuildCondBr(fBuilder, cond_value, then_block, else_block);
        
        // Compile then branch (= branch1)
        CompileBlock((*it)->fBranch1, then_block);
        
        // Store the result
        LLVMBuildStore(fBuilder, popValue(), typed_res);
        
        // Branch in merge_block
        LLVMBuildBr(fBuilder, merge_block);
        
        // Compile else branch (= branch2)
        CompileBlock((*it)->fBranch2, else_block);
        
        // Store the result
        LLVMBuildStore(fBuilder, popValue(), typed_res);
        
        // Branch in merge_block
        LLVMBuildBr(fBuilder, merge_block);
        
        // Insert in merge_block
        LLVMPositionBuilderAtEnd(fBuilder, merge_block);
        
        // Load the result
        pushValue(LLVMBuildLoad2(fBuilder, type, typed_res, ""));
    }

    void CompileBlock(FBCBlockInstruction<REAL>* block, LLVMBasicBlockRef code_block)
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
                 case FBCInstruction::kLoadSoundFieldInt: {
                    pushLoadSoundFieldInt((*it)->fName);
                    it++;
                    break;
                }
                    
                case FBCInstruction::kLoadSoundFieldReal: {
                    pushLoadSoundFieldReal((*it)->fName);
                    it++;
                    break;
                }
                    
                case FBCInstruction::kLoadReal:
                    pushLoadArray(fLLVMRealHeap, (*it)->fOffset1, getRealTy());
                    it++;
                    break;
                    
                case FBCInstruction::kLoadInt:
                    pushLoadArray(fLLVMIntHeap, (*it)->fOffset1, getInt32Ty());
                    it++;
                    break;
                    
                case FBCInstruction::kStoreReal:
                    pushStoreArray(fLLVMRealHeap, (*it)->fOffset1, getRealTy());
                    it++;
                    break;
                    
                case FBCInstruction::kStoreInt:
                    pushStoreArray(fLLVMIntHeap, (*it)->fOffset1, getInt32Ty());
                    it++;
                    break;
                    
                    // Indexed memory load/store: constant values are added at generation time by CreateBinOp...
                case FBCInstruction::kLoadIndexedReal: {
                    pushLoadIndexedArray(fLLVMRealHeap, popValue(), (*it)->fOffset1, getRealTy());
                    it++;
                    break;
                }
                    
                case FBCInstruction::kLoadIndexedInt: {
                    pushLoadIndexedArray(fLLVMIntHeap, popValue(), (*it)->fOffset1, getInt32Ty());
                    it++;
                    break;
                }

                case FBCInstruction::kStoreIndexedReal: {
                    pushStoreIndexedArray(fLLVMRealHeap, popValue(), (*it)->fOffset1, getRealTy());
                    it++;
                    break;
                }

                case FBCInstruction::kStoreIndexedInt: {
                    pushStoreIndexedArray(fLLVMIntHeap, popValue(), (*it)->fOffset1, getInt32Ty());
                    it++;
                    break;
                }

                    // Memory shift
                case FBCInstruction::kBlockShiftReal: {
                    for (int i = (*it)->fOffset1; i > (*it)->fOffset2; i -= 1) {
                        pushLoadArray(fLLVMRealHeap, i - 1, getRealTy());
                        pushStoreArray(fLLVMRealHeap, i, getRealTy());
                    }
                    it++;
                    break;
                }

                case FBCInstruction::kBlockShiftInt: {
                    for (int i = (*it)->fOffset1; i > (*it)->fOffset2; i -= 1) {
                        pushLoadArray(fLLVMIntHeap, i - 1, getInt32Ty());
                        pushStoreArray(fLLVMIntHeap, i, getInt32Ty());
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

                case FBCInstruction::kARshInt:
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
                    
                case FBCInstruction::kAcoshf:
                    pushUnaryRealCall("acosh");
                    it++;
                    break;

                case FBCInstruction::kAsinf:
                    pushUnaryRealCall("asin");
                    it++;
                    break;
                    
                case FBCInstruction::kAsinhf:
                    pushUnaryRealCall("asinh");
                    it++;
                    break;

                case FBCInstruction::kAtanf:
                    pushUnaryRealCall("atan");
                    it++;
                    break;
                    
                case FBCInstruction::kAtanhf:
                    pushUnaryRealCall("atanh");
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
                    
                case FBCInstruction::kRintf:
                    pushUnaryRealCall("rint");
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
                    
                case FBCInstruction::kIsnanf:
                    pushUnaryCall("isnan", getInt32Ty(), getRealTy(), true);
                    it++;
                    break;
                    
                case FBCInstruction::kIsinff:
                    pushUnaryCall("isinf", getInt32Ty(), getRealTy(), true);
                    it++;
                    break;
                    
                case FBCInstruction::kCopysignf:
                    pushBinaryRealCall("copysign");
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
                    end = true;
                    break;

                case FBCInstruction::kIf: {
                    
                    // Prepare condition: compare condition to 0
                    LLVMValueRef cond_value = LLVMBuildICmp(fBuilder, LLVMIntNE, popValue(), genInt32(0), "if_cond");
                    
                    // Get enclosing function
                    LLVMValueRef function = LLVMGetBasicBlockParent(LLVMGetInsertBlock(fBuilder));

                    // Create blocks for the then and else cases. Insert the 'then' block at the end of the function
                    LLVMBasicBlockRef then_block  = LLVMAppendBasicBlock(function, "if_then_block");
                    LLVMBasicBlockRef else_block  = LLVMAppendBasicBlock(function, "if_else_block");
                    LLVMBasicBlockRef merge_block = LLVMAppendBasicBlock(function, "if_merge_block");

                    LLVMBuildCondBr(fBuilder, cond_value, then_block, else_block);

                    // Compile then branch (= branch1)
                    CompileBlock((*it)->fBranch1, then_block);
                    LLVMBuildBr(fBuilder, merge_block);

                    // Compile else branch (= branch2)
                    CompileBlock((*it)->fBranch2, else_block);
                    LLVMBuildBr(fBuilder, merge_block);

                    // Insert in merge_block
                    LLVMPositionBuilderAtEnd(fBuilder, merge_block);

                    it++;
                    break;
                }
                    
                /*
                 This could be implemented using a PHY node (to group the result of the 'then' and 'else' blocks)
                 but is more complicated to do when hierarchical 'select' are compiled.
                 
                 Thus we create a local variable that is written in 'then' and 'else' blocks,
                 and loaded in the 'merge' block.
                 
                 LLVM passes will later one create a unique PHY node that groups all results,
                 especially when hierarchical 'select' are compiled.
                 */
                case FBCInstruction::kSelectInt: {
                    // Create typed local variable
                    createSelectBlock1(it, LLVMBuildAlloca(fAllocaBuilder, getInt32Ty(), "select_int"), getInt32Ty());
                    it++;
                    break;
                }
                    
                case FBCInstruction::kSelectReal: {
                    // Create typed local variable
                    createSelectBlock1(it, LLVMBuildAlloca(fAllocaBuilder, getRealTy(), "select_real"), getRealTy());
                    it++;
                    break;
                }

                case FBCInstruction::kCondBranch: {
                    // Prepare condition: compare condition to 0
                    LLVMValueRef cond_value = LLVMBuildICmp(fBuilder, LLVMIntNE, popValue(), genInt32(0), "");
               
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
                    
                    // Get enclosing function
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
    FBCLLVMCompiler(FBCBlockInstruction<REAL>* fbc_block, soundTable& sound_table)
    :FBCExecuteFun<REAL>(fbc_block, sound_table)
    {
        fLLVMStackIndex = 0;
      
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

        fBuilder       = LLVMCreateBuilder();
        fAllocaBuilder = LLVMCreateBuilder();
     
        fModule      = LLVMModuleCreateWithName(FAUSTVERSION);
        char* triple = LLVMGetDefaultTargetTriple();
        LLVMSetTarget(fModule, triple);
        LLVMDisposeMessage(triple);
        
        // Prepare global soundfile table
        if (this->fSoundTable.size() > 0) {
            LLVMTypeRef sf_types[this->fSoundTable.size()];
            LLVMValueRef sf_ptrs[this->fSoundTable.size()];
            int i = 0;
            for (const auto& it : this->fSoundTable) {
                sf_types[i] = genSoundFileTyPtr();
                // C++ pointer is first seen as an Int64 then casted as a pointer
                LLVMValueRef sf_ref = genUInt64(uint64_t(it.second));
                sf_ptrs[i] = LLVMConstIntToPtr(sf_ref, genSoundFileTyPtr());
                // Keep the soundfile index in fLLVMSoundTable
                fSoundTableID[it.first] = genInt32(i);
                i++;
            }
            // Create the global soundfile table
            LLVMTypeRef sound_table1 = LLVMStructType(sf_types, this->fSoundTable.size(), false);
            fLLVMSoundTable = LLVMAddGlobal(fModule, sound_table1, "sound_table");
            // Init it with C++ soundfile pointers
            LLVMValueRef initializer = LLVMConstNamedStruct(sound_table1, sf_ptrs, this->fSoundTable.size());
            LLVMSetInitializer(fLLVMSoundTable, initializer);
        } else {
            fLLVMSoundTable = nullptr;
        }
         
        // Compile compute function
        LLVMTypeRef args_types[] = { getInt32TyPtr(), getRealTyPtr(), getRealTyPtrPtr(), getRealTyPtrPtr() };

        LLVMTypeRef  execute_type = LLVMFunctionType(LLVMVoidType(), args_types, 4, false);
        LLVMValueRef execute      = LLVMAddFunction(fModule, "execute", execute_type);
        
        LLVMBasicBlockRef alloca_block = LLVMAppendBasicBlock(execute, "alloca_block");
        LLVMBasicBlockRef entry_block  = LLVMAppendBasicBlock(execute, "entry_block");
        
        // Always insert alloca in the alloca_block
        LLVMPositionBuilderAtEnd(fAllocaBuilder, alloca_block);
        
        fLLVMIntHeap  = LLVMGetParam(execute, 0);
        fLLVMRealHeap = LLVMGetParam(execute, 1);
        fLLVMInputs   = LLVMGetParam(execute, 2);
        fLLVMOutputs  = LLVMGetParam(execute, 3);

#if (LLVM_VERSION_MAJOR == 5) || (LLVM_VERSION_MAJOR == 6)
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
        CompileBlock(fbc_block, entry_block);

        // Add return
        LLVMBuildRetVoid(fBuilder);
        
        // Link alloca_block and entry_block
        LLVMPositionBuilderAtEnd(fBuilder, alloca_block);
        LLVMBuildBr(fBuilder, entry_block);
      
        //LLVMDumpModule(fModule);

        // For host target support
        LLVMLinkInMCJIT();
        LLVMInitializeNativeTarget();
        LLVMInitializeNativeAsmPrinter();
        LLVMInitializeNativeAsmParser();

        char* error;
        if (LLVMCreateJITCompilerForModule(&fJIT, fModule, LLVMCodeGenLevelAggressive, &error)) {
            std::string err = error;
            LLVMDisposeMessage(error);
            throw faustexception(std::string(error));
        }
     
        // Setup optimizations
        LLVMPassManagerBuilderRef pass_buider = LLVMPassManagerBuilderCreate();
        LLVMPassManagerBuilderSetOptLevel(pass_buider, 3);
        LLVMPassManagerBuilderSetSizeLevel(pass_buider, 0);

        LLVMPassManagerRef function_passes = LLVMCreateFunctionPassManagerForModule(fModule);
        LLVMPassManagerBuilderPopulateFunctionPassManager(pass_buider, function_passes);

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

        //LLVMDumpModule(fModule);

        // Get 'execute' entry point
        fCompiledFun = (compiledFun)LLVMGetFunctionAddress(fJIT, "execute");
    }

    virtual ~FBCLLVMCompiler()
    {
        // fModule is deallocated by fJIT
        LLVMDisposeExecutionEngine(fJIT);
        LLVMDisposeBuilder(fBuilder);
        LLVMDisposeBuilder(fAllocaBuilder);
        LLVMShutdown();
    }

    void execute(int* int_heap, REAL* real_heap, REAL** inputs, REAL** outputs)
    {
        fCompiledFun(int_heap, real_heap, inputs, outputs);
    }
};

#endif
