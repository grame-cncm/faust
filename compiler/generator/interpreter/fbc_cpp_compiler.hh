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

#ifndef _FBC_CPP_COMPILER_H
#define _FBC_CPP_COMPILER_H

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#include "fbc_interpreter.hh"
#include "interpreter_bytecode.hh"

using namespace std;

#define dispatchReturn_() \
    {                     \
        it = popAddr();   \
    }
#define saveReturn()      \
    {                     \
        pushAddr(it + 1); \
    }

// C++ instructions container
struct CPPBlock : public std::vector<std::string> {
    
    std::string fNum;
    CPPBlock* fNext;
    
    static int gCurrentBlockIndex;
    
    CPPBlock():fNum(std::to_string(gCurrentBlockIndex++)), fNext(nullptr)
    {}
    
    void print(std::ostream& out)
    {
        // header
        out << "{" << std::endl;
        out << "label" << fNum << ":" << std::endl;
        
        // block
        if (this->size() == 0) {
            out << ";" << std::endl;
        } else {
            for (auto& it : *this) {
                out << it << std::endl;
            }
        }
        
        // footer
        out << "}" << std::endl;
        
        // next block
        if (this->fNext) { this->fNext->print(out); }
    }
    
    void endBlock()
    {}
};

// FBC C++ compiler
template <class T>
class FBCCPPCompiler {
    typedef void (*compiledFun)(int* int_heap, T* real_heap, T** inputs, T** outputs);
  protected:
    
    string        fExecute;
    string        fCPPStack[512];
    InstructionIT fAddressStack[64];
    compiledFun   fCompiledFun;

    int fCPPStackIndex;
    int fAddrStackIndex;
    
    CPPBlock* fCurrentBlock;
    
    void pushBinop(const std::string& op)
    {
        std::string v1 = popValue();
        std::string v2 = popValue();
        pushValue("(" + v1 + " " + op + " " + v2 + ")");
    }

    std::string genFloat(float num)     { return std::to_string(num); }
    std::string genDouble(double num)   { return std::to_string(num); }
    std::string genReal(double num)     { return (sizeof(T) == sizeof(double)) ? genDouble(num) : genFloat(num); }
    std::string genInt32(int num)       { return std::to_string(num); }
    std::string genInt64(long long num) { return std::to_string(num); }
    
    std::string getRealTy() { return (sizeof(T) == sizeof(double)) ? "double" : "float"; }

    void        pushValue(const std::string& val) { fCPPStack[fCPPStackIndex++] = val; }
    std::string popValue() { return fCPPStack[--fCPPStackIndex]; }

    void          pushAddr(InstructionIT addr) { fAddressStack[fAddrStackIndex++] = addr; }
    InstructionIT popAddr() { return fAddressStack[--fAddrStackIndex]; }
    bool          emptyReturn() { return (fAddrStackIndex == 0); }

    void pushUnaryCall(const std::string& name)
    {
        pushValue(name + "(" + popValue() + ")");
    }
    void pushBinaryCall(const std::string& name)
    {
        pushValue(name + "(" + popValue() + ", " + popValue() + ")");
    }

    void pushLoadArray(const std::string& array, int index)
    {
        pushValue(array + "[" + std::to_string(index) + "]");
    }
    void pushStoreArray(const std::string& array, int index)
    {
        fCurrentBlock->push_back(array + "[" + std::to_string(index) + "] = " + popValue() + ";");
    }
    void pushLoadArray(const std::string& array, const std::string& index)
    {
        pushValue(array + "[" + index + "]");
    }
    void pushStoreArray(const std::string& array,const std::string& index)
    {
        fCurrentBlock->push_back(array + "[" + index+ "] = " + popValue() + ";");
    }

    void pushLoadInput(int index)
    {
        pushValue("inputs[" + std::to_string(index) + "][" +  popValue() + "]");
    }
    void pushStoreOutput(int index)
    {
        fCurrentBlock->push_back("outputs[" + std::to_string(index) + "][" + popValue() + "] = " + popValue() + ";");
    }

    void CompileBlock(FBCBlockInstruction<T>* block, CPPBlock* code_block)
    {
        InstructionIT it  = block->fInstructions.begin();
        bool          end = false;

        // Insert in the current block
        fCurrentBlock = code_block;
      
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
                    pushLoadArray("real_heap", (*it)->fOffset1);
                    it++;
                    break;

                case FBCInstruction::kLoadInt:
                    pushLoadArray("int_heap", (*it)->fOffset1);
                    it++;
                    break;

                case FBCInstruction::kStoreReal:
                    pushStoreArray("real_heap", (*it)->fOffset1);
                    it++;
                    break;

                case FBCInstruction::kStoreInt:
                    pushStoreArray("int_heap", (*it)->fOffset1);
                    it++;
                    break;

                    // Indexed memory load/store: constant values are added at generation time by CreateBinOp...
                case FBCInstruction::kLoadIndexedReal: {
                    std::string offset = genInt32((*it)->fOffset1) + "+" + popValue();
                    pushLoadArray("real_heap", offset);
                    it++;
                    break;
                }

                case FBCInstruction::kLoadIndexedInt: {
                    std::string offset = genInt32((*it)->fOffset1) + "+" + popValue();
                    pushLoadArray("int_heap", offset);
                    it++;
                    break;
                }

                case FBCInstruction::kStoreIndexedReal: {
                    std::string offset = genInt32((*it)->fOffset1) + "+" + popValue();
                    pushStoreArray("real_heap", offset);
                    it++;
                    break;
                }

                case FBCInstruction::kStoreIndexedInt: {
                    std::string offset = genInt32((*it)->fOffset1) + "+" + popValue();
                    pushStoreArray("int_heap", offset);
                    it++;
                    break;
                }

                    // Memory shift (TODO : use memmove ?)
                case FBCInstruction::kBlockShiftReal: {
                    for (int i = (*it)->fOffset1; i > (*it)->fOffset2; i -= 1) {
                        pushLoadArray("real_heap", i - 1);
                        pushStoreArray("real_heap", i);
                    }
                    it++;
                    break;
                }

                case FBCInstruction::kBlockShiftInt: {
                    for (int i = (*it)->fOffset1; i > (*it)->fOffset2; i -= 1) {
                        pushLoadArray("int_heap", i - 1);
                        pushStoreArray("int_heap", i);
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
                    std::string val = popValue();
                    pushValue(getRealTy() + "(" + val + ")");
                    it++;
                    break;
                }

                case FBCInstruction::kCastInt: {
                    std::string val = popValue();
                    pushValue("int(" + val + ")");
                    it++;
                    break;
                }

                case FBCInstruction::kBitcastInt: {
                    std::string val = popValue();
                    pushValue("*reinterpret_cast<int*>(" + val + ")");
                    it++;
                    break;
                }

                case FBCInstruction::kBitcastReal: {
                    std::string val = popValue();
                    pushValue("*reinterpret_cast<" + getRealTy() + "*>(" + val + ")");
                    it++;
                    break;
                }

                    // Binary math
                case FBCInstruction::kAddReal:
                case FBCInstruction::kAddInt:
                    pushBinop("+");
                    it++;
                    break;

                case FBCInstruction::kSubReal:
                    case FBCInstruction::kSubInt:
                    pushBinop("-");
                    it++;
                    break;

                case FBCInstruction::kMultReal:
                case FBCInstruction::kMultInt:
                    pushBinop("*");
                    it++;
                    break;

                case FBCInstruction::kDivReal:
                    case FBCInstruction::kDivInt:
                    pushBinop("/");
                    it++;
                    break;

                case FBCInstruction::kRemReal:
                    pushBinaryCall("std::remainder");
                    it++;
                    break;

                case FBCInstruction::kRemInt:
                    pushBinop("%");
                    it++;
                    break;

                case FBCInstruction::kLshInt:
                    pushBinop("<<");
                    it++;
                    break;

                case FBCInstruction::kRshInt:
                    pushBinop(">>");
                    it++;
                    break;

                case FBCInstruction::kGTInt:
                case FBCInstruction::kGTReal:
                    pushBinop(">");
                    it++;
                    break;

                case FBCInstruction::kLTInt:
                case FBCInstruction::kLTReal:
                    pushBinop("<");
                    it++;
                    break;

                case FBCInstruction::kGEInt:
                case FBCInstruction::kGEReal:
                    pushBinop(">=");
                    it++;
                    break;

                case FBCInstruction::kLEInt:
                case FBCInstruction::kLEReal:
                    pushBinop("<=");
                    it++;
                    break;

                case FBCInstruction::kEQInt:
                case FBCInstruction::kEQReal:
                    pushBinop("==");
                    it++;
                    break;

                case FBCInstruction::kNEInt:
                case FBCInstruction::kNEReal:
                    pushBinop("!=");
                    it++;
                    break;

                case FBCInstruction::kANDInt:
                    pushBinop("&");
                    it++;
                    break;

                case FBCInstruction::kORInt:
                    pushBinop("|");
                    it++;
                    break;

                case FBCInstruction::kXORInt:
                    pushBinop("^");
                    it++;
                    break;

                    // Extended unary math
                case FBCInstruction::kAbs:
                    pushUnaryCall("std::abs");
                    it++;
                    break;

                case FBCInstruction::kAbsf:
                    pushUnaryCall("std::fabs");
                    it++;
                    break;

                case FBCInstruction::kAcosf:
                    pushUnaryCall("std::acos");
                    it++;
                    break;

                case FBCInstruction::kAsinf:
                    pushUnaryCall("std::asin");
                    it++;
                    break;

                case FBCInstruction::kAtanf:
                    pushUnaryCall("std::atan");
                    it++;
                    break;

                case FBCInstruction::kCeilf:
                    pushUnaryCall("std::ceil");
                    it++;
                    break;

                case FBCInstruction::kCosf:
                    pushUnaryCall("std::cos");
                    it++;
                    break;

                case FBCInstruction::kCoshf:
                    pushUnaryCall("std::cosh");
                    it++;
                    break;

                case FBCInstruction::kExpf:
                    pushUnaryCall("std::exp");
                    it++;
                    break;

                case FBCInstruction::kFloorf:
                    pushUnaryCall("std::floor");
                    it++;
                    break;

                case FBCInstruction::kLogf:
                    pushUnaryCall("std::log");
                    it++;
                    break;

                case FBCInstruction::kLog10f:
                    pushUnaryCall("std::log10");
                    it++;
                    break;

                case FBCInstruction::kRoundf:
                    pushUnaryCall("std::round");
                    it++;
                    break;

                case FBCInstruction::kSinf:
                    pushUnaryCall("std::sin");
                    it++;
                    break;

                case FBCInstruction::kSinhf:
                    pushUnaryCall("std::sinh");
                    it++;
                    break;

                case FBCInstruction::kSqrtf:
                    pushUnaryCall("sstd::qrt");
                    it++;
                    break;

                case FBCInstruction::kTanf:
                    pushUnaryCall("std::tan");
                    it++;
                    break;

                case FBCInstruction::kTanhf:
                    pushUnaryCall("std::tanh");
                    it++;
                    break;

                    // Extended binary math
                case FBCInstruction::kAtan2f:
                    pushBinaryCall("std::atan2");
                    it++;
                    break;

                case FBCInstruction::kFmodf:
                    pushBinaryCall("std::fmod");
                    it++;
                    break;

                case FBCInstruction::kPowf:
                    pushBinaryCall("std::pow");
                    it++;
                    break;

                case FBCInstruction::kMax:
                    pushBinaryCall("std::max<int>");
                    it++;
                    break;
                    
                case FBCInstruction::kMaxf:
                    pushBinaryCall("std::max<" + getRealTy() + ">");
                    it++;
                    break;

                case FBCInstruction::kMin:
                    pushBinaryCall("std::min<int>");
                    it++;
                    break;

                case FBCInstruction::kMinf:
                    pushBinaryCall("std::min<" + getRealTy() + ">");
                    it++;
                    break;
 
                    // Control
                case FBCInstruction::kReturn:
                    // Empty addr stack = end of computation
                    if (emptyReturn()) {
                        fCurrentBlock->endBlock();
                        end = true;
                    } else {
                        dispatchReturn_();
                    }
                    break;

                // TO CHECK
                case FBCInstruction::kIf: {
                    /*
                    saveReturn();
                    LLVMValue cond_value = fBuilder->CreateICmpEQ(popValue(), genInt32(1), "ifcond");
                    Function* function   = fBuilder->GetInsertBlock()->getParent();

                    // Create blocks for the then and else cases.  Insert the 'then' block at the end of the function
                    BasicBlock* then_block  = BasicBlock::Create(fModule->getContext(), "then_code", function);
                    BasicBlock* else_block  = BasicBlock::Create(fModule->getContext(), "else_code");
                    BasicBlock* merge_block = BasicBlock::Create(fModule->getContext(), "merge_block");

                    pushValue(fBuilder->CreateCondBr(cond_value, then_block, else_block));

                    // Compile then branch (= branch1)
                    CompileBlock((*it)->fBranch1, then_block);

                    fBuilder->CreateBr(merge_block);
                    // Codegen of 'Then' can change the current block, update then_block for the PHI
                    then_block = fBuilder->GetInsertBlock();

                    // Emit else block
                    function->getBasicBlockList().push_back(else_block);

                    // Compile else branch (= branch2)
                    CompileBlock((*it)->fBranch2, else_block);

                    pushValue(fBuilder->CreateBr(merge_block));
                    // Codegen of 'Else' can change the current block, update else_block for the PHI
                    else_block = fBuilder->GetInsertBlock();

                    // Emit merge block
                    function->getBasicBlockList().push_back(merge_block);
                    fBuilder->SetInsertPoint(merge_block);
                    */
                    
                    break;
                }

                case FBCInstruction::kSelectReal:
                case FBCInstruction::kSelectInt: {
                    // Prepare condition
                    std::string cond_value = popValue();

                    // Compile then branch (= branch1)
                    CompileBlock((*it)->fBranch1, code_block);

                    // Compile else branch (= branch2)
                    CompileBlock((*it)->fBranch2, code_block);

                    // Create the result (= branch2)
                    std::string then_value = popValue();
                    std::string else_value = popValue();
                    pushValue("(" + cond_value + ") ? " + else_value + " : " + then_value);

                    it++;
                    break;
                }

                case FBCInstruction::kCondBranch: {
                    
                    // Prepare condition
                    std::string cond_value = popValue();

                    // New block for loop
                    CPPBlock* next_block = new CPPBlock();

                    // Branch to current block
                    fCurrentBlock->push_back("if " + cond_value + " { goto label" + code_block->fNum + "; } else { goto label" + next_block->fNum + "; }");
                    
                    // Link previous_block and next_block
                    fCurrentBlock->fNext = next_block;
                    
                    // Insert in next_block
                    fCurrentBlock = next_block;

                    it++;
                    break;
                }

                case FBCInstruction::kLoop: {

                    // New block for condition
                    CPPBlock* init_block = new CPPBlock();
                    
                    // Link previous_block and init_block
                    fCurrentBlock->fNext = init_block;
                    
                    // Compile init branch (= branch1)
                    CompileBlock((*it)->fBranch1, init_block);

                    // New block for loop
                    CPPBlock* loop_block = new CPPBlock();
                    
                    // Link previous_block and loop_block
                    fCurrentBlock->fNext = loop_block;
                    
                    // Compile loop branch (= branch2)
                    CompileBlock((*it)->fBranch2, loop_block);

                    it++;
                    break;
                }

                default:
                    // Should not happen
                    (*it)->write(&std::cout);
                    faustassert(false);
                    break;
            }
        }
    }

   public:
    FBCCPPCompiler(FBCBlockInstruction<T>* fbc_block)
    {
        fCPPStackIndex = 0;
        fAddrStackIndex = 0;
       
        // fbc_block->write(&std::cout);
        
        // Compile compute body
        CPPBlock* code_block = new CPPBlock();
        CompileBlock(fbc_block, code_block);
        code_block->endBlock();
        
        std::stringstream execute;
        
        execute << "void Execute(int* int_heap, "
                << getRealTy() << "* real_heap, "
                << getRealTy() << "** inputs, "
                << getRealTy() << "** outputs)" << std::endl;
        
        execute << "{" << std::endl;
        code_block->print(execute);
        execute << "}" << std::endl;
     
        // Keep function
        fExecute = execute.str();
        fCompiledFun = nullptr;
    }

    virtual ~FBCCPPCompiler()
    {}
    
    void Execute(int* int_heap, T* real_heap, T** inputs, T** outputs)
    {
        if (fCompiledFun) {
            fCompiledFun(int_heap, real_heap, inputs, outputs);
        } else {
            std::cout << fExecute;
            exit(1);
        }
    }
    
    /*
    // Compiled bells.dsp
    void Execute(int* int_heap, float* real_heap, float** inputs, float** outputs)
    {
        {
        label0:
            ;
        }
        {
        label1:
            int_heap[86] = 0;
        }
        {
        label2:
            real_heap[2801+0] = real_heap[2800];
            int_heap[1+0] = (12345 + (int_heap[1+1] * 1103515245));
            real_heap[2813+0] = ((float(int_heap[1+0]) * 0.000000) - (real_heap[2808] * ((real_heap[2813+1] * real_heap[2812]) + (real_heap[2813+2] * real_heap[2811]))));
            real_heap[2819+0] = ((real_heap[2808] * ((real_heap[2813+2] * real_heap[2810]) + ((real_heap[2813+1] * real_heap[2816]) + (real_heap[2813+0] * real_heap[2810])))) - (real_heap[2805] * ((real_heap[2819+1] * real_heap[2818]) + (real_heap[2819+2] * real_heap[2817]))));
            real_heap[3119] = (real_heap[2819+2] + (real_heap[2819+0] + (real_heap[2819+1] * 2.000000)));
            int_heap[3+0] = int_heap[72];
            real_heap[3120] = (0.002000 * (real_heap[2800] - real_heap[2801+1]));
            real_heap[2824+0] = ((((int_heap[72] - int_heap[3+1]) > 0) > 0)) ? 0.000000 : std::min<float>(real_heap[2823], (1.000000 + (real_heap[3120] + real_heap[2824+1])));
            int_heap[87] = (real_heap[2824+0] < real_heap[2826]);
            real_heap[3121] = (real_heap[2805] * (real_heap[3119] * (int_heap[87]) ? ((real_heap[2824+0] < 0.000000)) ? 0.000000 : (int_heap[87]) ? (real_heap[2824+0] * real_heap[2827]) : 1.000000 : ((real_heap[2824+0] < real_heap[2823])) ? (1.000000 + (real_heap[2827] * (0.000000 - (real_heap[2824+0] - real_heap[2826])))) : 0.000000));
            real_heap[2831+0] = (real_heap[3121] - ((real_heap[2831+2] * real_heap[2830]) + (real_heap[2831+1] * real_heap[2829])));
            real_heap[2839+0] = (real_heap[3121] - ((real_heap[2839+2] * real_heap[2838]) + (real_heap[2839+1] * real_heap[2837])));
            real_heap[2845+0] = (real_heap[3121] - ((real_heap[2845+2] * real_heap[2844]) + (real_heap[2845+1] * real_heap[2843])));
            real_heap[2851+0] = (real_heap[3121] - ((real_heap[2851+2] * real_heap[2850]) + (real_heap[2851+1] * real_heap[2849])));
            real_heap[2857+0] = (real_heap[3121] - ((real_heap[2857+2] * real_heap[2856]) + (real_heap[2857+1] * real_heap[2855])));
            real_heap[2863+0] = (real_heap[3121] - ((real_heap[2863+2] * real_heap[2862]) + (real_heap[2863+1] * real_heap[2861])));
            real_heap[2869+0] = (real_heap[3121] - ((real_heap[2869+2] * real_heap[2868]) + (real_heap[2869+1] * real_heap[2867])));
            real_heap[2875+0] = (real_heap[3121] - ((real_heap[2875+2] * real_heap[2874]) + (real_heap[2875+1] * real_heap[2873])));
            real_heap[2881+0] = (real_heap[3121] - ((real_heap[2881+2] * real_heap[2880]) + (real_heap[2881+1] * real_heap[2879])));
            real_heap[2887+0] = (real_heap[3121] - ((real_heap[2887+2] * real_heap[2886]) + (real_heap[2887+1] * real_heap[2885])));
            int_heap[5+0] = int_heap[83];
            real_heap[2891+0] = ((((int_heap[83] - int_heap[5+1]) > 0) > 0)) ? 0.000000 : std::min<float>(real_heap[2823], (1.000000 + (real_heap[2891+1] + real_heap[3120])));
            int_heap[88] = (real_heap[2891+0] < real_heap[2826]);
            real_heap[3122] = (real_heap[2805] * (real_heap[3119] * (int_heap[88]) ? ((real_heap[2891+0] < 0.000000)) ? 0.000000 : (int_heap[88]) ? (real_heap[2891+0] * real_heap[2827]) : 1.000000 : ((real_heap[2891+0] < real_heap[2823])) ? (1.000000 + (real_heap[2827] * (0.000000 - (real_heap[2891+0] - real_heap[2826])))) : 0.000000));
            real_heap[2896+0] = (real_heap[3122] - ((real_heap[2896+2] * real_heap[2895]) + (real_heap[2896+1] * real_heap[2894])));
            real_heap[2902+0] = (real_heap[3122] - ((real_heap[2902+2] * real_heap[2901]) + (real_heap[2902+1] * real_heap[2900])));
            real_heap[2908+0] = (real_heap[3122] - ((real_heap[2908+2] * real_heap[2907]) + (real_heap[2908+1] * real_heap[2906])));
            real_heap[2914+0] = (real_heap[3122] - ((real_heap[2914+2] * real_heap[2913]) + (real_heap[2914+1] * real_heap[2912])));
            real_heap[2920+0] = (real_heap[3122] - ((real_heap[2920+2] * real_heap[2919]) + (real_heap[2920+1] * real_heap[2918])));
            real_heap[2926+0] = (real_heap[3122] - ((real_heap[2926+2] * real_heap[2925]) + (real_heap[2926+1] * real_heap[2924])));
            real_heap[2932+0] = (real_heap[3122] - ((real_heap[2932+2] * real_heap[2931]) + (real_heap[2932+1] * real_heap[2930])));
            real_heap[2938+0] = (real_heap[3122] - ((real_heap[2938+2] * real_heap[2937]) + (real_heap[2938+1] * real_heap[2936])));
            real_heap[2944+0] = (real_heap[3122] - ((real_heap[2944+2] * real_heap[2943]) + (real_heap[2944+1] * real_heap[2942])));
            real_heap[2950+0] = (real_heap[3122] - ((real_heap[2950+2] * real_heap[2949]) + (real_heap[2950+1] * real_heap[2948])));
            int_heap[7+0] = int_heap[84];
            real_heap[2954+0] = ((((int_heap[84] - int_heap[7+1]) > 0) > 0)) ? 0.000000 : std::min<float>(real_heap[2823], (1.000000 + (real_heap[2954+1] + real_heap[3120])));
            int_heap[89] = (real_heap[2954+0] < real_heap[2826]);
            real_heap[3123] = (real_heap[2805] * (real_heap[3119] * (int_heap[89]) ? ((real_heap[2954+0] < 0.000000)) ? 0.000000 : (int_heap[89]) ? (real_heap[2954+0] * real_heap[2827]) : 1.000000 : ((real_heap[2954+0] < real_heap[2823])) ? (1.000000 + (real_heap[2827] * (0.000000 - (real_heap[2954+0] - real_heap[2826])))) : 0.000000));
            real_heap[2959+0] = (real_heap[3123] - ((real_heap[2959+2] * real_heap[2958]) + (real_heap[2959+1] * real_heap[2957])));
            real_heap[2965+0] = (real_heap[3123] - ((real_heap[2965+2] * real_heap[2964]) + (real_heap[2965+1] * real_heap[2963])));
            real_heap[2971+0] = (real_heap[3123] - ((real_heap[2971+2] * real_heap[2970]) + (real_heap[2971+1] * real_heap[2969])));
            real_heap[2977+0] = (real_heap[3123] - ((real_heap[2977+2] * real_heap[2976]) + (real_heap[2977+1] * real_heap[2975])));
            real_heap[2983+0] = (real_heap[3123] - ((real_heap[2983+2] * real_heap[2982]) + (real_heap[2983+1] * real_heap[2981])));
            real_heap[2989+0] = (real_heap[3123] - ((real_heap[2989+2] * real_heap[2988]) + (real_heap[2989+1] * real_heap[2987])));
            real_heap[2995+0] = (real_heap[3123] - ((real_heap[2995+2] * real_heap[2994]) + (real_heap[2995+1] * real_heap[2993])));
            real_heap[3001+0] = (real_heap[3123] - ((real_heap[3001+2] * real_heap[3000]) + (real_heap[3001+1] * real_heap[2999])));
            real_heap[3007+0] = (real_heap[3123] - ((real_heap[3007+2] * real_heap[3006]) + (real_heap[3007+1] * real_heap[3005])));
            real_heap[3013+0] = (real_heap[3123] - ((real_heap[3013+2] * real_heap[3012]) + (real_heap[3013+1] * real_heap[3011])));
            int_heap[9+0] = int_heap[85];
            real_heap[3017+0] = ((((int_heap[85] - int_heap[9+1]) > 0) > 0)) ? 0.000000 : std::min<float>(real_heap[2823], (1.000000 + (real_heap[3017+1] + real_heap[3120])));
            int_heap[90] = (real_heap[3017+0] < real_heap[2826]);
            real_heap[3124] = (real_heap[2805] * (real_heap[3119] * (int_heap[90]) ? ((real_heap[3017+0] < 0.000000)) ? 0.000000 : (int_heap[90]) ? (real_heap[3017+0] * real_heap[2827]) : 1.000000 : ((real_heap[3017+0] < real_heap[2823])) ? (1.000000 + (real_heap[2827] * (0.000000 - (real_heap[3017+0] - real_heap[2826])))) : 0.000000));
            real_heap[3022+0] = (real_heap[3124] - ((real_heap[3022+2] * real_heap[3021]) + (real_heap[3022+1] * real_heap[3020])));
            real_heap[3028+0] = (real_heap[3124] - ((real_heap[3028+2] * real_heap[3027]) + (real_heap[3028+1] * real_heap[3026])));
            real_heap[3034+0] = (real_heap[3124] - ((real_heap[3034+2] * real_heap[3033]) + (real_heap[3034+1] * real_heap[3032])));
            real_heap[3040+0] = (real_heap[3124] - ((real_heap[3040+2] * real_heap[3039]) + (real_heap[3040+1] * real_heap[3038])));
            real_heap[3046+0] = (real_heap[3124] - ((real_heap[3046+2] * real_heap[3045]) + (real_heap[3046+1] * real_heap[3044])));
            real_heap[3052+0] = (real_heap[3124] - ((real_heap[3052+2] * real_heap[3051]) + (real_heap[3052+1] * real_heap[3050])));
            real_heap[3058+0] = (real_heap[3124] - ((real_heap[3058+2] * real_heap[3057]) + (real_heap[3058+1] * real_heap[3056])));
            real_heap[3064+0] = (real_heap[3124] - ((real_heap[3064+2] * real_heap[3063]) + (real_heap[3064+1] * real_heap[3062])));
            real_heap[3070+0] = (real_heap[3124] - ((real_heap[3070+2] * real_heap[3069]) + (real_heap[3070+1] * real_heap[3068])));
            real_heap[3076+0] = (real_heap[3124] - ((real_heap[3076+2] * real_heap[3075]) + (real_heap[3076+1] * real_heap[3074])));
            real_heap[3125] = (0.020000 * (((real_heap[3118] * (real_heap[3076+0] - real_heap[3076+2])) + ((real_heap[3117] * (real_heap[3070+0] - real_heap[3070+2])) + ((real_heap[3116] * (real_heap[3064+0] - real_heap[3064+2])) + ((real_heap[3115] * (real_heap[3058+0] - real_heap[3058+2])) + ((real_heap[3114] * (real_heap[3052+0] - real_heap[3052+2])) + ((real_heap[3113] * (real_heap[3046+0] - real_heap[3046+2])) + ((real_heap[3112] * (real_heap[3040+0] - real_heap[3040+2])) + ((real_heap[3111] * (real_heap[3034+0] - real_heap[3034+2])) + ((real_heap[3110] * (real_heap[3028+0] - real_heap[3028+2])) + (real_heap[3109] * (real_heap[3022+0] - real_heap[3022+2]))))))))))) + (((real_heap[3108] * (real_heap[3013+0] - real_heap[3013+2])) + ((real_heap[3107] * (real_heap[3007+0] - real_heap[3007+2])) + ((real_heap[3106] * (real_heap[3001+0] - real_heap[3001+2])) + ((real_heap[3105] * (real_heap[2995+0] - real_heap[2995+2])) + ((real_heap[3104] * (real_heap[2989+0] - real_heap[2989+2])) + ((real_heap[3103] * (real_heap[2983+0] - real_heap[2983+2])) + ((real_heap[3102] * (real_heap[2977+0] - real_heap[2977+2])) + ((real_heap[3101] * (real_heap[2971+0] - real_heap[2971+2])) + ((real_heap[3100] * (real_heap[2965+0] - real_heap[2965+2])) + (real_heap[3099] * (real_heap[2959+0] - real_heap[2959+2]))))))))))) + (((real_heap[3098] * (real_heap[2950+0] - real_heap[2950+2])) + ((real_heap[3097] * (real_heap[2944+0] - real_heap[2944+2])) + ((real_heap[3096] * (real_heap[2938+0] - real_heap[2938+2])) + ((real_heap[3095] * (real_heap[2932+0] - real_heap[2932+2])) + ((real_heap[3094] * (real_heap[2926+0] - real_heap[2926+2])) + ((real_heap[3093] * (real_heap[2920+0] - real_heap[2920+2])) + ((real_heap[3092] * (real_heap[2914+0] - real_heap[2914+2])) + ((real_heap[3091] * (real_heap[2908+0] - real_heap[2908+2])) + ((real_heap[3090] * (real_heap[2902+0] - real_heap[2902+2])) + (real_heap[3089] * (real_heap[2896+0] - real_heap[2896+2]))))))))))) + ((real_heap[3088] * (real_heap[2887+0] - real_heap[2887+2])) + ((real_heap[3087] * (real_heap[2881+0] - real_heap[2881+2])) + ((real_heap[3086] * (real_heap[2875+0] - real_heap[2875+2])) + ((real_heap[3085] * (real_heap[2869+0] - real_heap[2869+2])) + ((real_heap[3084] * (real_heap[2863+0] - real_heap[2863+2])) + ((real_heap[3083] * (real_heap[2857+0] - real_heap[2857+2])) + ((real_heap[3082] * (real_heap[2851+0] - real_heap[2851+2])) + ((real_heap[3081] * (real_heap[2845+0] - real_heap[2845+2])) + ((real_heap[3080] * (real_heap[2839+0] - real_heap[2839+2])) + (real_heap[3079] * (real_heap[2831+0] - real_heap[2831+2])))))))))))))));
            outputs[0][int_heap[86]] = real_heap[3125];
            outputs[1][int_heap[86]] = real_heap[3125];
            real_heap[2801+1] = real_heap[2801+0];
            int_heap[1+1] = int_heap[1+0];
            real_heap[2813+2] = real_heap[2813+1];
            real_heap[2813+1] = real_heap[2813+0];
            real_heap[2819+2] = real_heap[2819+1];
            real_heap[2819+1] = real_heap[2819+0];
            int_heap[3+1] = int_heap[3+0];
            real_heap[2824+1] = real_heap[2824+0];
            real_heap[2831+2] = real_heap[2831+1];
            real_heap[2831+1] = real_heap[2831+0];
            real_heap[2839+2] = real_heap[2839+1];
            real_heap[2839+1] = real_heap[2839+0];
            real_heap[2845+2] = real_heap[2845+1];
            real_heap[2845+1] = real_heap[2845+0];
            real_heap[2851+2] = real_heap[2851+1];
            real_heap[2851+1] = real_heap[2851+0];
            real_heap[2857+2] = real_heap[2857+1];
            real_heap[2857+1] = real_heap[2857+0];
            real_heap[2863+2] = real_heap[2863+1];
            real_heap[2863+1] = real_heap[2863+0];
            real_heap[2869+2] = real_heap[2869+1];
            real_heap[2869+1] = real_heap[2869+0];
            real_heap[2875+2] = real_heap[2875+1];
            real_heap[2875+1] = real_heap[2875+0];
            real_heap[2881+2] = real_heap[2881+1];
            real_heap[2881+1] = real_heap[2881+0];
            real_heap[2887+2] = real_heap[2887+1];
            real_heap[2887+1] = real_heap[2887+0];
            int_heap[5+1] = int_heap[5+0];
            real_heap[2891+1] = real_heap[2891+0];
            real_heap[2896+2] = real_heap[2896+1];
            real_heap[2896+1] = real_heap[2896+0];
            real_heap[2902+2] = real_heap[2902+1];
            real_heap[2902+1] = real_heap[2902+0];
            real_heap[2908+2] = real_heap[2908+1];
            real_heap[2908+1] = real_heap[2908+0];
            real_heap[2914+2] = real_heap[2914+1];
            real_heap[2914+1] = real_heap[2914+0];
            real_heap[2920+2] = real_heap[2920+1];
            real_heap[2920+1] = real_heap[2920+0];
            real_heap[2926+2] = real_heap[2926+1];
            real_heap[2926+1] = real_heap[2926+0];
            real_heap[2932+2] = real_heap[2932+1];
            real_heap[2932+1] = real_heap[2932+0];
            real_heap[2938+2] = real_heap[2938+1];
            real_heap[2938+1] = real_heap[2938+0];
            real_heap[2944+2] = real_heap[2944+1];
            real_heap[2944+1] = real_heap[2944+0];
            real_heap[2950+2] = real_heap[2950+1];
            real_heap[2950+1] = real_heap[2950+0];
            int_heap[7+1] = int_heap[7+0];
            real_heap[2954+1] = real_heap[2954+0];
            real_heap[2959+2] = real_heap[2959+1];
            real_heap[2959+1] = real_heap[2959+0];
            real_heap[2965+2] = real_heap[2965+1];
            real_heap[2965+1] = real_heap[2965+0];
            real_heap[2971+2] = real_heap[2971+1];
            real_heap[2971+1] = real_heap[2971+0];
            real_heap[2977+2] = real_heap[2977+1];
            real_heap[2977+1] = real_heap[2977+0];
            real_heap[2983+2] = real_heap[2983+1];
            real_heap[2983+1] = real_heap[2983+0];
            real_heap[2989+2] = real_heap[2989+1];
            real_heap[2989+1] = real_heap[2989+0];
            real_heap[2995+2] = real_heap[2995+1];
            real_heap[2995+1] = real_heap[2995+0];
            real_heap[3001+2] = real_heap[3001+1];
            real_heap[3001+1] = real_heap[3001+0];
            real_heap[3007+2] = real_heap[3007+1];
            real_heap[3007+1] = real_heap[3007+0];
            real_heap[3013+2] = real_heap[3013+1];
            real_heap[3013+1] = real_heap[3013+0];
            int_heap[9+1] = int_heap[9+0];
            real_heap[3017+1] = real_heap[3017+0];
            real_heap[3022+2] = real_heap[3022+1];
            real_heap[3022+1] = real_heap[3022+0];
            real_heap[3028+2] = real_heap[3028+1];
            real_heap[3028+1] = real_heap[3028+0];
            real_heap[3034+2] = real_heap[3034+1];
            real_heap[3034+1] = real_heap[3034+0];
            real_heap[3040+2] = real_heap[3040+1];
            real_heap[3040+1] = real_heap[3040+0];
            real_heap[3046+2] = real_heap[3046+1];
            real_heap[3046+1] = real_heap[3046+0];
            real_heap[3052+2] = real_heap[3052+1];
            real_heap[3052+1] = real_heap[3052+0];
            real_heap[3058+2] = real_heap[3058+1];
            real_heap[3058+1] = real_heap[3058+0];
            real_heap[3064+2] = real_heap[3064+1];
            real_heap[3064+1] = real_heap[3064+0];
            real_heap[3070+2] = real_heap[3070+1];
            real_heap[3070+1] = real_heap[3070+0];
            real_heap[3076+2] = real_heap[3076+1];
            real_heap[3076+1] = real_heap[3076+0];
            int_heap[86] = (1 + int_heap[86]);
            if (int_heap[86] < int_heap[11]) { goto label2; } else { goto label3; }
        }
        {
        label3:
            ;
        }
    }
    
    void Execute(int* int_heap, double* real_heap, double** inputs, double** outputs)
    {
        {
        label0:
            ;
        }
        {
        label1:
            int_heap[86] = 0;
        }
        {
        label2:
            real_heap[2801+0] = real_heap[2800];
            int_heap[1+0] = (12345 + (int_heap[1+1] * 1103515245));
            real_heap[2813+0] = ((double(int_heap[1+0]) * 0.000000) - (real_heap[2808] * ((real_heap[2813+1] * real_heap[2812]) + (real_heap[2813+2] * real_heap[2811]))));
            real_heap[2819+0] = ((real_heap[2808] * ((real_heap[2813+2] * real_heap[2810]) + ((real_heap[2813+1] * real_heap[2816]) + (real_heap[2813+0] * real_heap[2810])))) - (real_heap[2805] * ((real_heap[2819+1] * real_heap[2818]) + (real_heap[2819+2] * real_heap[2817]))));
            real_heap[3119] = (real_heap[2819+2] + (real_heap[2819+0] + (real_heap[2819+1] * 2.000000)));
            int_heap[3+0] = int_heap[72];
            real_heap[3120] = (0.002000 * (real_heap[2800] - real_heap[2801+1]));
            real_heap[2824+0] = ((((int_heap[72] - int_heap[3+1]) > 0) > 0)) ? 0.000000 : std::min<double>(real_heap[2823], (1.000000 + (real_heap[3120] + real_heap[2824+1])));
            int_heap[87] = (real_heap[2824+0] < real_heap[2826]);
            real_heap[3121] = (real_heap[2805] * (real_heap[3119] * (int_heap[87]) ? ((real_heap[2824+0] < 0.000000)) ? 0.000000 : (int_heap[87]) ? (real_heap[2824+0] * real_heap[2827]) : 1.000000 : ((real_heap[2824+0] < real_heap[2823])) ? (1.000000 + (real_heap[2827] * (0.000000 - (real_heap[2824+0] - real_heap[2826])))) : 0.000000));
            real_heap[2831+0] = (real_heap[3121] - ((real_heap[2831+2] * real_heap[2830]) + (real_heap[2831+1] * real_heap[2829])));
            real_heap[2839+0] = (real_heap[3121] - ((real_heap[2839+2] * real_heap[2838]) + (real_heap[2839+1] * real_heap[2837])));
            real_heap[2845+0] = (real_heap[3121] - ((real_heap[2845+2] * real_heap[2844]) + (real_heap[2845+1] * real_heap[2843])));
            real_heap[2851+0] = (real_heap[3121] - ((real_heap[2851+2] * real_heap[2850]) + (real_heap[2851+1] * real_heap[2849])));
            real_heap[2857+0] = (real_heap[3121] - ((real_heap[2857+2] * real_heap[2856]) + (real_heap[2857+1] * real_heap[2855])));
            real_heap[2863+0] = (real_heap[3121] - ((real_heap[2863+2] * real_heap[2862]) + (real_heap[2863+1] * real_heap[2861])));
            real_heap[2869+0] = (real_heap[3121] - ((real_heap[2869+2] * real_heap[2868]) + (real_heap[2869+1] * real_heap[2867])));
            real_heap[2875+0] = (real_heap[3121] - ((real_heap[2875+2] * real_heap[2874]) + (real_heap[2875+1] * real_heap[2873])));
            real_heap[2881+0] = (real_heap[3121] - ((real_heap[2881+2] * real_heap[2880]) + (real_heap[2881+1] * real_heap[2879])));
            real_heap[2887+0] = (real_heap[3121] - ((real_heap[2887+2] * real_heap[2886]) + (real_heap[2887+1] * real_heap[2885])));
            int_heap[5+0] = int_heap[83];
            real_heap[2891+0] = ((((int_heap[83] - int_heap[5+1]) > 0) > 0)) ? 0.000000 : std::min<double>(real_heap[2823], (1.000000 + (real_heap[2891+1] + real_heap[3120])));
            int_heap[88] = (real_heap[2891+0] < real_heap[2826]);
            real_heap[3122] = (real_heap[2805] * (real_heap[3119] * (int_heap[88]) ? ((real_heap[2891+0] < 0.000000)) ? 0.000000 : (int_heap[88]) ? (real_heap[2891+0] * real_heap[2827]) : 1.000000 : ((real_heap[2891+0] < real_heap[2823])) ? (1.000000 + (real_heap[2827] * (0.000000 - (real_heap[2891+0] - real_heap[2826])))) : 0.000000));
            real_heap[2896+0] = (real_heap[3122] - ((real_heap[2896+2] * real_heap[2895]) + (real_heap[2896+1] * real_heap[2894])));
            real_heap[2902+0] = (real_heap[3122] - ((real_heap[2902+2] * real_heap[2901]) + (real_heap[2902+1] * real_heap[2900])));
            real_heap[2908+0] = (real_heap[3122] - ((real_heap[2908+2] * real_heap[2907]) + (real_heap[2908+1] * real_heap[2906])));
            real_heap[2914+0] = (real_heap[3122] - ((real_heap[2914+2] * real_heap[2913]) + (real_heap[2914+1] * real_heap[2912])));
            real_heap[2920+0] = (real_heap[3122] - ((real_heap[2920+2] * real_heap[2919]) + (real_heap[2920+1] * real_heap[2918])));
            real_heap[2926+0] = (real_heap[3122] - ((real_heap[2926+2] * real_heap[2925]) + (real_heap[2926+1] * real_heap[2924])));
            real_heap[2932+0] = (real_heap[3122] - ((real_heap[2932+2] * real_heap[2931]) + (real_heap[2932+1] * real_heap[2930])));
            real_heap[2938+0] = (real_heap[3122] - ((real_heap[2938+2] * real_heap[2937]) + (real_heap[2938+1] * real_heap[2936])));
            real_heap[2944+0] = (real_heap[3122] - ((real_heap[2944+2] * real_heap[2943]) + (real_heap[2944+1] * real_heap[2942])));
            real_heap[2950+0] = (real_heap[3122] - ((real_heap[2950+2] * real_heap[2949]) + (real_heap[2950+1] * real_heap[2948])));
            int_heap[7+0] = int_heap[84];
            real_heap[2954+0] = ((((int_heap[84] - int_heap[7+1]) > 0) > 0)) ? 0.000000 : std::min<double>(real_heap[2823], (1.000000 + (real_heap[2954+1] + real_heap[3120])));
            int_heap[89] = (real_heap[2954+0] < real_heap[2826]);
            real_heap[3123] = (real_heap[2805] * (real_heap[3119] * (int_heap[89]) ? ((real_heap[2954+0] < 0.000000)) ? 0.000000 : (int_heap[89]) ? (real_heap[2954+0] * real_heap[2827]) : 1.000000 : ((real_heap[2954+0] < real_heap[2823])) ? (1.000000 + (real_heap[2827] * (0.000000 - (real_heap[2954+0] - real_heap[2826])))) : 0.000000));
            real_heap[2959+0] = (real_heap[3123] - ((real_heap[2959+2] * real_heap[2958]) + (real_heap[2959+1] * real_heap[2957])));
            real_heap[2965+0] = (real_heap[3123] - ((real_heap[2965+2] * real_heap[2964]) + (real_heap[2965+1] * real_heap[2963])));
            real_heap[2971+0] = (real_heap[3123] - ((real_heap[2971+2] * real_heap[2970]) + (real_heap[2971+1] * real_heap[2969])));
            real_heap[2977+0] = (real_heap[3123] - ((real_heap[2977+2] * real_heap[2976]) + (real_heap[2977+1] * real_heap[2975])));
            real_heap[2983+0] = (real_heap[3123] - ((real_heap[2983+2] * real_heap[2982]) + (real_heap[2983+1] * real_heap[2981])));
            real_heap[2989+0] = (real_heap[3123] - ((real_heap[2989+2] * real_heap[2988]) + (real_heap[2989+1] * real_heap[2987])));
            real_heap[2995+0] = (real_heap[3123] - ((real_heap[2995+2] * real_heap[2994]) + (real_heap[2995+1] * real_heap[2993])));
            real_heap[3001+0] = (real_heap[3123] - ((real_heap[3001+2] * real_heap[3000]) + (real_heap[3001+1] * real_heap[2999])));
            real_heap[3007+0] = (real_heap[3123] - ((real_heap[3007+2] * real_heap[3006]) + (real_heap[3007+1] * real_heap[3005])));
            real_heap[3013+0] = (real_heap[3123] - ((real_heap[3013+2] * real_heap[3012]) + (real_heap[3013+1] * real_heap[3011])));
            int_heap[9+0] = int_heap[85];
            real_heap[3017+0] = ((((int_heap[85] - int_heap[9+1]) > 0) > 0)) ? 0.000000 : std::min<double>(real_heap[2823], (1.000000 + (real_heap[3017+1] + real_heap[3120])));
            int_heap[90] = (real_heap[3017+0] < real_heap[2826]);
            real_heap[3124] = (real_heap[2805] * (real_heap[3119] * (int_heap[90]) ? ((real_heap[3017+0] < 0.000000)) ? 0.000000 : (int_heap[90]) ? (real_heap[3017+0] * real_heap[2827]) : 1.000000 : ((real_heap[3017+0] < real_heap[2823])) ? (1.000000 + (real_heap[2827] * (0.000000 - (real_heap[3017+0] - real_heap[2826])))) : 0.000000));
            real_heap[3022+0] = (real_heap[3124] - ((real_heap[3022+2] * real_heap[3021]) + (real_heap[3022+1] * real_heap[3020])));
            real_heap[3028+0] = (real_heap[3124] - ((real_heap[3028+2] * real_heap[3027]) + (real_heap[3028+1] * real_heap[3026])));
            real_heap[3034+0] = (real_heap[3124] - ((real_heap[3034+2] * real_heap[3033]) + (real_heap[3034+1] * real_heap[3032])));
            real_heap[3040+0] = (real_heap[3124] - ((real_heap[3040+2] * real_heap[3039]) + (real_heap[3040+1] * real_heap[3038])));
            real_heap[3046+0] = (real_heap[3124] - ((real_heap[3046+2] * real_heap[3045]) + (real_heap[3046+1] * real_heap[3044])));
            real_heap[3052+0] = (real_heap[3124] - ((real_heap[3052+2] * real_heap[3051]) + (real_heap[3052+1] * real_heap[3050])));
            real_heap[3058+0] = (real_heap[3124] - ((real_heap[3058+2] * real_heap[3057]) + (real_heap[3058+1] * real_heap[3056])));
            real_heap[3064+0] = (real_heap[3124] - ((real_heap[3064+2] * real_heap[3063]) + (real_heap[3064+1] * real_heap[3062])));
            real_heap[3070+0] = (real_heap[3124] - ((real_heap[3070+2] * real_heap[3069]) + (real_heap[3070+1] * real_heap[3068])));
            real_heap[3076+0] = (real_heap[3124] - ((real_heap[3076+2] * real_heap[3075]) + (real_heap[3076+1] * real_heap[3074])));
            real_heap[3125] = (0.020000 * (((real_heap[3118] * (real_heap[3076+0] - real_heap[3076+2])) + ((real_heap[3117] * (real_heap[3070+0] - real_heap[3070+2])) + ((real_heap[3116] * (real_heap[3064+0] - real_heap[3064+2])) + ((real_heap[3115] * (real_heap[3058+0] - real_heap[3058+2])) + ((real_heap[3114] * (real_heap[3052+0] - real_heap[3052+2])) + ((real_heap[3113] * (real_heap[3046+0] - real_heap[3046+2])) + ((real_heap[3112] * (real_heap[3040+0] - real_heap[3040+2])) + ((real_heap[3111] * (real_heap[3034+0] - real_heap[3034+2])) + ((real_heap[3110] * (real_heap[3028+0] - real_heap[3028+2])) + (real_heap[3109] * (real_heap[3022+0] - real_heap[3022+2]))))))))))) + (((real_heap[3108] * (real_heap[3013+0] - real_heap[3013+2])) + ((real_heap[3107] * (real_heap[3007+0] - real_heap[3007+2])) + ((real_heap[3106] * (real_heap[3001+0] - real_heap[3001+2])) + ((real_heap[3105] * (real_heap[2995+0] - real_heap[2995+2])) + ((real_heap[3104] * (real_heap[2989+0] - real_heap[2989+2])) + ((real_heap[3103] * (real_heap[2983+0] - real_heap[2983+2])) + ((real_heap[3102] * (real_heap[2977+0] - real_heap[2977+2])) + ((real_heap[3101] * (real_heap[2971+0] - real_heap[2971+2])) + ((real_heap[3100] * (real_heap[2965+0] - real_heap[2965+2])) + (real_heap[3099] * (real_heap[2959+0] - real_heap[2959+2]))))))))))) + (((real_heap[3098] * (real_heap[2950+0] - real_heap[2950+2])) + ((real_heap[3097] * (real_heap[2944+0] - real_heap[2944+2])) + ((real_heap[3096] * (real_heap[2938+0] - real_heap[2938+2])) + ((real_heap[3095] * (real_heap[2932+0] - real_heap[2932+2])) + ((real_heap[3094] * (real_heap[2926+0] - real_heap[2926+2])) + ((real_heap[3093] * (real_heap[2920+0] - real_heap[2920+2])) + ((real_heap[3092] * (real_heap[2914+0] - real_heap[2914+2])) + ((real_heap[3091] * (real_heap[2908+0] - real_heap[2908+2])) + ((real_heap[3090] * (real_heap[2902+0] - real_heap[2902+2])) + (real_heap[3089] * (real_heap[2896+0] - real_heap[2896+2]))))))))))) + ((real_heap[3088] * (real_heap[2887+0] - real_heap[2887+2])) + ((real_heap[3087] * (real_heap[2881+0] - real_heap[2881+2])) + ((real_heap[3086] * (real_heap[2875+0] - real_heap[2875+2])) + ((real_heap[3085] * (real_heap[2869+0] - real_heap[2869+2])) + ((real_heap[3084] * (real_heap[2863+0] - real_heap[2863+2])) + ((real_heap[3083] * (real_heap[2857+0] - real_heap[2857+2])) + ((real_heap[3082] * (real_heap[2851+0] - real_heap[2851+2])) + ((real_heap[3081] * (real_heap[2845+0] - real_heap[2845+2])) + ((real_heap[3080] * (real_heap[2839+0] - real_heap[2839+2])) + (real_heap[3079] * (real_heap[2831+0] - real_heap[2831+2])))))))))))))));
            outputs[0][int_heap[86]] = real_heap[3125];
            outputs[1][int_heap[86]] = real_heap[3125];
            real_heap[2801+1] = real_heap[2801+0];
            int_heap[1+1] = int_heap[1+0];
            real_heap[2813+2] = real_heap[2813+1];
            real_heap[2813+1] = real_heap[2813+0];
            real_heap[2819+2] = real_heap[2819+1];
            real_heap[2819+1] = real_heap[2819+0];
            int_heap[3+1] = int_heap[3+0];
            real_heap[2824+1] = real_heap[2824+0];
            real_heap[2831+2] = real_heap[2831+1];
            real_heap[2831+1] = real_heap[2831+0];
            real_heap[2839+2] = real_heap[2839+1];
            real_heap[2839+1] = real_heap[2839+0];
            real_heap[2845+2] = real_heap[2845+1];
            real_heap[2845+1] = real_heap[2845+0];
            real_heap[2851+2] = real_heap[2851+1];
            real_heap[2851+1] = real_heap[2851+0];
            real_heap[2857+2] = real_heap[2857+1];
            real_heap[2857+1] = real_heap[2857+0];
            real_heap[2863+2] = real_heap[2863+1];
            real_heap[2863+1] = real_heap[2863+0];
            real_heap[2869+2] = real_heap[2869+1];
            real_heap[2869+1] = real_heap[2869+0];
            real_heap[2875+2] = real_heap[2875+1];
            real_heap[2875+1] = real_heap[2875+0];
            real_heap[2881+2] = real_heap[2881+1];
            real_heap[2881+1] = real_heap[2881+0];
            real_heap[2887+2] = real_heap[2887+1];
            real_heap[2887+1] = real_heap[2887+0];
            int_heap[5+1] = int_heap[5+0];
            real_heap[2891+1] = real_heap[2891+0];
            real_heap[2896+2] = real_heap[2896+1];
            real_heap[2896+1] = real_heap[2896+0];
            real_heap[2902+2] = real_heap[2902+1];
            real_heap[2902+1] = real_heap[2902+0];
            real_heap[2908+2] = real_heap[2908+1];
            real_heap[2908+1] = real_heap[2908+0];
            real_heap[2914+2] = real_heap[2914+1];
            real_heap[2914+1] = real_heap[2914+0];
            real_heap[2920+2] = real_heap[2920+1];
            real_heap[2920+1] = real_heap[2920+0];
            real_heap[2926+2] = real_heap[2926+1];
            real_heap[2926+1] = real_heap[2926+0];
            real_heap[2932+2] = real_heap[2932+1];
            real_heap[2932+1] = real_heap[2932+0];
            real_heap[2938+2] = real_heap[2938+1];
            real_heap[2938+1] = real_heap[2938+0];
            real_heap[2944+2] = real_heap[2944+1];
            real_heap[2944+1] = real_heap[2944+0];
            real_heap[2950+2] = real_heap[2950+1];
            real_heap[2950+1] = real_heap[2950+0];
            int_heap[7+1] = int_heap[7+0];
            real_heap[2954+1] = real_heap[2954+0];
            real_heap[2959+2] = real_heap[2959+1];
            real_heap[2959+1] = real_heap[2959+0];
            real_heap[2965+2] = real_heap[2965+1];
            real_heap[2965+1] = real_heap[2965+0];
            real_heap[2971+2] = real_heap[2971+1];
            real_heap[2971+1] = real_heap[2971+0];
            real_heap[2977+2] = real_heap[2977+1];
            real_heap[2977+1] = real_heap[2977+0];
            real_heap[2983+2] = real_heap[2983+1];
            real_heap[2983+1] = real_heap[2983+0];
            real_heap[2989+2] = real_heap[2989+1];
            real_heap[2989+1] = real_heap[2989+0];
            real_heap[2995+2] = real_heap[2995+1];
            real_heap[2995+1] = real_heap[2995+0];
            real_heap[3001+2] = real_heap[3001+1];
            real_heap[3001+1] = real_heap[3001+0];
            real_heap[3007+2] = real_heap[3007+1];
            real_heap[3007+1] = real_heap[3007+0];
            real_heap[3013+2] = real_heap[3013+1];
            real_heap[3013+1] = real_heap[3013+0];
            int_heap[9+1] = int_heap[9+0];
            real_heap[3017+1] = real_heap[3017+0];
            real_heap[3022+2] = real_heap[3022+1];
            real_heap[3022+1] = real_heap[3022+0];
            real_heap[3028+2] = real_heap[3028+1];
            real_heap[3028+1] = real_heap[3028+0];
            real_heap[3034+2] = real_heap[3034+1];
            real_heap[3034+1] = real_heap[3034+0];
            real_heap[3040+2] = real_heap[3040+1];
            real_heap[3040+1] = real_heap[3040+0];
            real_heap[3046+2] = real_heap[3046+1];
            real_heap[3046+1] = real_heap[3046+0];
            real_heap[3052+2] = real_heap[3052+1];
            real_heap[3052+1] = real_heap[3052+0];
            real_heap[3058+2] = real_heap[3058+1];
            real_heap[3058+1] = real_heap[3058+0];
            real_heap[3064+2] = real_heap[3064+1];
            real_heap[3064+1] = real_heap[3064+0];
            real_heap[3070+2] = real_heap[3070+1];
            real_heap[3070+1] = real_heap[3070+0];
            real_heap[3076+2] = real_heap[3076+1];
            real_heap[3076+1] = real_heap[3076+0];
            int_heap[86] = (1 + int_heap[86]);
            if (int_heap[86] < int_heap[11]) { goto label2; } else { goto label3; }
        }
        {
        label3:
            ;
        }
    }
    */
    
    std::string getExecute()
    {
        return fExecute;
    }
};

// FBC compiler
template <class T>
class FBCCompiler : public FBCInterpreter<T, 0> {
   public:
    typedef typename std::map<FBCBlockInstruction<T>*, FBCCPPCompiler<T>*>           CompiledBlocksType;
    typedef typename std::map<FBCBlockInstruction<T>*, FBCCPPCompiler<T>*>::iterator CompiledBlocksTypeIT;

    FBCCompiler(interpreter_dsp_factory_aux<T, 0>* factory, CompiledBlocksType* map)
        : FBCInterpreter<T, 0>(factory)
    {
        fCompiledBlocks = map;

        // FBC blocks compilation
        // CompileBlock(factory->fComputeBlock);
        CompileBlock(factory->fComputeDSPBlock);
    }
    
    virtual ~FBCCompiler()
    {}

    void ExecuteBlock(FBCBlockInstruction<T>* block)
    {
        // The 'DSP' compute block only is compiled..
        if (fCompiledBlocks->find(block) != fCompiledBlocks->end()) {
            ((*fCompiledBlocks)[block])->Execute(this->fIntHeap, this->fRealHeap, this->fInputs, this->fOutputs);
        } else {
            FBCInterpreter<T, 0>::ExecuteBlock(block);
        }
    }

   protected:
    CompiledBlocksType* fCompiledBlocks;

    void CompileBlock(FBCBlockInstruction<T>* fbc_block)
    {
        if (fCompiledBlocks->find(fbc_block) == fCompiledBlocks->end()) {
            (*fCompiledBlocks)[fbc_block] = new FBCCPPCompiler<T>(fbc_block);
        } else {
            // std::cout << "FBCCompiler : reuse compiled block" << std::endl;
        }
    }
};

#endif

