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

#ifndef interpreter_dsp_aux_pe_h
#define interpreter_dsp_aux_pe_h

#include "interpreter_dsp_aux.h"

// Specialization using partial evaluation: making controllers constant and optimizing the code.

template <class REAL, int TRACE>
class interpreter_dsp_aux_pe : public interpreter_dsp_aux<REAL, TRACE> {
    protected:
        FBCBlockInstruction<REAL>* fStaticInitBlock;
        FBCBlockInstruction<REAL>* fInitBlock;
        FBCBlockInstruction<REAL>* fResetUIBlock;
        FBCBlockInstruction<REAL>* fClearBlock;
        FBCBlockInstruction<REAL>* fComputeBlock;
        FBCBlockInstruction<REAL>* fComputeDSPBlock;
    
        std::map<int, int>  fIntMap;
        std::map<int, REAL> fRealMap;
    
    public:
        interpreter_dsp_aux_pe(interpreter_dsp_factory_aux<REAL, TRACE>* factory)
        {
            std::cout << "interpreter_dsp_aux_pe\n";
            /*
             if (this->fFactory->getMemoryManager()) {
             this->fInputs  = static_cast<T**>(this->fFactory->allocate(sizeof(T*) * this->fFactory->fNumInputs));
             this->fOutputs = static_cast<T**>(this->fFactory->allocate(sizeof(T*) * this->fFactory->fNumOutputs));
             } else {
             this->fInputs  = new T*[this->fFactory->fNumInputs];
             this->fOutputs = new T*[this->fFactory->fNumOutputs];
             }
             */
            
            /*
             fFactory->fStaticInitBlock->write(&std::cout, false);
             fFactory->fInitBlock->write(&std::cout, false);
             fFactory->fResetUIBlock->write(&std::cout, false);
             fFactory->fClearBlock->write(&std::cout, false);
             fFactory->fComputeBlock->write(&std::cout, false);
             fFactory->fComputeDSPBlock->write(&std::cout, false);
             std::cout << "size " << fFactory->fComputeDSPBlock->size() << std::endl;
             */
            
            this->fFactory     = factory;
            this->fFBCExecutor = factory->createFBCExecutor();
            
            fStaticInitBlock = nullptr;
            fInitBlock       = nullptr;
            fResetUIBlock    = nullptr;
            fClearBlock      = nullptr;
            fComputeBlock    = nullptr;
            fComputeDSPBlock = nullptr;
        }
    
        virtual ~interpreter_dsp_aux_pe()
        {
            /*
             if (this->fFactory->getMemoryManager()) {
             this->fFactory->destroy(this->fInputs);
             this->fFactory->destroy(this->fOutputs);
             } else {
             delete[] this->fInputs;
             delete[] this->fOutputs;
             }
             */
            
            delete this->fStaticInitBlock;
            delete this->fInitBlock;
            delete this->fResetUIBlock;
            delete this->fClearBlock;
            delete this->fComputeBlock;
            delete this->fComputeDSPBlock;
        }
    
        virtual void instanceConstants(int sample_rate)
        {
            // Store sample_rate in specialization fIntMap
            fIntMap[this->fFactory->fSROffset] = sample_rate;
            
            // Store sample_rate in 'fSampleate' variable at correct offset in fIntHeap
            this->fFBCExecutor->setIntValue(this->fFactory->fSROffset, sample_rate);
            
            // Execute state init instructions
            this->fFBCExecutor->ExecuteBlock(this->fFactory->fInitBlock);
        }
    
        virtual void init(int sample_rate)
        {
            this->fInitialized = true;
            
            // Store sample_rate in specialization fIntMap
            fIntMap[this->fFactory->fSROffset] = sample_rate;
            
            // Store sample_rate in 'fSampleRate' variable at correct offset in fIntHeap
            this->fFBCExecutor->setIntValue(this->fFactory->fSROffset, sample_rate);
            
            this->classInit(sample_rate);
            this->instanceInit(sample_rate);
            
            // Propagate constant values stored in the code into the heap
            this->fStaticInitBlock =
            FBCInstructionOptimizer<T>::specialize2Heap(this->fFactory->fStaticInitBlock->copy(), fIntMap, fRealMap);
            this->fInitBlock =
            FBCInstructionOptimizer<T>::specialize2Heap(this->fFactory->fInitBlock->copy(), fIntMap, fRealMap);
            this->fResetUIBlock =
            FBCInstructionOptimizer<T>::specialize2Heap(this->fFactory->fResetUIBlock->copy(), fIntMap, fRealMap);
            this->fClearBlock =
            FBCInstructionOptimizer<T>::specialize2Heap(this->fFactory->fClearBlock->copy(), fIntMap, fRealMap);
            
            // Suppress IOTA from fIntMap since we don't want specialization to use it
            if (fIntMap.find(this->fFactory->fIOTAOffset) != fIntMap.end()) {
                fIntMap.erase(fIntMap.find(this->fFactory->fIOTAOffset));
            }
            
            // Freeze all controllers
            this->fFactory->fUserInterfaceBlock->freezeDefaultValues(fRealMap);
            
            // To test : unfreeze "freg, gate, gain" controllers
            std::map<std::string, int>& map = this->fFactory->fUserInterfaceBlock->getPathMap();
            for (auto& it : map) {
                if ((it.first.find("freq") != std::string::npos) || (it.first.find("gate") != std::string::npos) ||
                    (it.first.find("gain") != std::string::npos)) {
                    this->fFactory->fUserInterfaceBlock->unFreezeValue(fRealMap, it.first);
                }
            }
            // Keep button on
            // this->fFactory->fUserInterfaceBlock->unFreezeValue(fRealMap, FBCInstruction::kAddButton);
            
            // Specialization by partial evaluation
            this->fComputeBlock =
            FBCInstructionOptimizer<T>::specialize(this->fFactory->fComputeBlock->copy(), fIntMap, fRealMap);
            
        #ifdef MACHINE
            // LLVM JIT only works on unoptimized FBC
            this->fComputeDSPBlock = this->fFactory->fComputeDSPBlock->copy();
        #else
            this->fComputeDSPBlock =
            FBCInstructionOptimizer<T>::optimizeBlock(this->fFactory->fComputeDSPBlock->copy(), 1, 4);
        #endif
            
            // To test C++ generation
            // this->fComputeDSPBlock = this->fFactory->fComputeDSPBlock->copy();
            
            this->fComputeDSPBlock = FBCInstructionOptimizer<T>::specialize(this->fComputeDSPBlock, fIntMap, fRealMap);
            
        #ifndef MACHINE
            // // LLVM JIT only works on unoptimized FBC
            this->fComputeBlock    = FBCInstructionOptimizer<T>::optimizeBlock(this->fComputeBlock, 5, 6);
            this->fComputeDSPBlock = FBCInstructionOptimizer<T>::optimizeBlock(this->fComputeDSPBlock, 5, 6);
        #endif
            
            /*
             this->fStaticInitBlock->write(&std::cout, false);
             this->fInitBlock->write(&std::cout, false);
             this->fResetUIBlock->write(&std::cout, false);
             this->fClearBlock->write(&std::cout, false);
             this->fComputeBlock->write(&std::cout, false);
             this->fComputeDSPBlock->write(&std::cout, false);
             */
            /*
             #ifdef MACHINE
             FBCCPPGenerator<T> cpp_generator(this->fFactory);
             cpp_generator.generateCode(std::cout, this->fComputeBlock, this->fComputeDSPBlock);
             #endif
             */
        }
    
        virtual void compute(int count, FAUSTFLOAT** inputs_aux, FAUSTFLOAT** outputs_aux)
        {
            if (count == 0) return;  // Beware: compiled loop don't work with an index of 0
            
            if (TRACE > 0 && !this->fInitialized) {
                std::cout << "======== DSP is not initialized ! ========" << std::endl;
            } else {
                // std::cout << "compute " << count << std::endl;
                T** inputs  = reinterpret_cast<T**>(inputs_aux);
                T** outputs = reinterpret_cast<T**>(outputs_aux);
                
                // Prepare in/out buffers
                for (int i = 0; i < this->fFactory->fNumInputs; i++) {
                    this->fFBCExecutor->setInput(i, inputs[i]);
                }
                for (int i = 0; i < this->fFactory->fNumOutputs; i++) {
                    this->fFBCExecutor->setOutput(i, outputs[i]);
                }
                
                // Set count in 'count' variable at the correct offset in fIntHeap
                this->fFBCExecutor->setIntValue(this->fFactory->fCountOffset, count);
                
                // Executes the specialized 'control' block
                this->fFBCExecutor->ExecuteBlock(this->fComputeBlock);
                
                // Executes the specialized 'DSP' block
        #ifdef MACHINE
                this->fFBCExecutor->ExecuteBlock(this->fComputeDSPBlock, true);
        #else
                this->fFBCExecutor->ExecuteBlock(this->fComputeDSPBlock);
        #endif
            }
        }
};

#endif
