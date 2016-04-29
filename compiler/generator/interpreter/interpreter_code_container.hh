/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2015 GRAME, Centre National de Creation Musicale
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

#ifndef _INTERPRETER_CODE_CONTAINER_H
#define _INTERPRETER_CODE_CONTAINER_H

#include "code_container.hh"
#include "interpreter_instructions.hh"
#include "interpreter_dsp_aux.hh"

using namespace std;           

class InterpreterCodeContainer : public virtual CodeContainer {

    protected:

        // TODO : use template
        InterpreterInstVisitor<float> fCodeProducer;
        
        void produceInfoFunctions(int tabs, const string& classname, bool isvirtual);

    public:

        InterpreterCodeContainer(const string& name, int numInputs, int numOutputs)
        {
            initializeCodeContainer(numInputs, numOutputs);
            fKlassName = name;
            
            // Initializations for FIRInstructionMathOptimizer pass
            
            // Init heap opcode
            for (int i = FIRInstruction::kAddReal; i <= FIRInstruction::kXORInt; i++) {
                FIRInstruction::gFIRMath2Heap[FIRInstruction::Opcode(i)]
                = FIRInstruction::Opcode(i + (FIRInstruction::kAddRealHeap - FIRInstruction::kAddReal));
                //std::cout << gFIRInstructionTable[i + (FIRInstruction::kAddRealHeap - FIRInstruction::kAddReal)] << std::endl;
            }
            
            // Init direct opcode
            for (int i = FIRInstruction::kAddReal; i <= FIRInstruction::kXORInt; i++) {
                FIRInstruction::gFIRMath2Direct[FIRInstruction::Opcode(i)]
                = FIRInstruction::Opcode(i + (FIRInstruction::kAddRealDirect - FIRInstruction::kAddReal));
                //std::cout << gFIRInstructionTable[i + (FIRInstruction::kAddRealDirect - FIRInstruction::kAddReal)] << std::endl;
            }
            
            // Init direct opcode (non commutative operation)
            for (int i = FIRInstruction::kAddReal; i <= FIRInstruction::kXORInt; i++) {
                FIRInstruction::gFIRMath2DirectInvert[FIRInstruction::Opcode(i)]
                = FIRInstruction::Opcode(i + (FIRInstruction::kAddRealDirect - FIRInstruction::kAddReal));
                //std::cout << gFIRInstructionTable[i + (FIRInstruction::kAddRealDirect - FIRInstruction::kAddReal)] << std::endl;
            }
            
            FIRInstruction::gFIRMath2DirectInvert[FIRInstruction::kSubReal] = FIRInstruction::kSubRealDirectInvert;
            FIRInstruction::gFIRMath2DirectInvert[FIRInstruction::kSubInt] = FIRInstruction::kSubIntDirectInvert;
            FIRInstruction::gFIRMath2DirectInvert[FIRInstruction::kDivReal] = FIRInstruction::kDivRealDirectInvert;
            FIRInstruction::gFIRMath2DirectInvert[FIRInstruction::kDivInt] = FIRInstruction::kDivIntDirectInvert;
            FIRInstruction::gFIRMath2DirectInvert[FIRInstruction::kRemReal] = FIRInstruction::kRemRealDirectInvert;
            FIRInstruction::gFIRMath2DirectInvert[FIRInstruction::kRemInt] = FIRInstruction::kRemIntDirectInvert;
            FIRInstruction::gFIRMath2DirectInvert[FIRInstruction::kLshInt] = FIRInstruction::kLshIntDirectInvert;
            FIRInstruction::gFIRMath2DirectInvert[FIRInstruction::kRshInt] = FIRInstruction::kRshIntDirectInvert;
            FIRInstruction::gFIRMath2DirectInvert[FIRInstruction::kGTInt] = FIRInstruction::kGTIntDirectInvert;
            FIRInstruction::gFIRMath2DirectInvert[FIRInstruction::kLTInt] = FIRInstruction::kLTIntDirectInvert;
            FIRInstruction::gFIRMath2DirectInvert[FIRInstruction::kGEInt] = FIRInstruction::kGEIntDirectInvert;
            FIRInstruction::gFIRMath2DirectInvert[FIRInstruction::kLEInt] = FIRInstruction::kLEIntDirectInvert;
            FIRInstruction::gFIRMath2DirectInvert[FIRInstruction::kGTReal] = FIRInstruction::kGTRealDirectInvert;
            FIRInstruction::gFIRMath2DirectInvert[FIRInstruction::kLTReal] = FIRInstruction::kLTRealDirectInvert;
            FIRInstruction::gFIRMath2DirectInvert[FIRInstruction::kGEReal] = FIRInstruction::kGERealDirectInvert;
            FIRInstruction::gFIRMath2DirectInvert[FIRInstruction::kLEReal] = FIRInstruction::kLERealDirectInvert;
            
            // Init heap opcode
            /*
            for (int i = FIRInstruction::kAddReal; i <= FIRInstruction::kXORInt; i++) {
                FIRInstruction::gFIRMath2Heap[FIRInstruction::Opcode(i)]
                = FIRInstruction::Opcode(i + (FIRInstruction::kAddRealHeap - FIRInstruction::kAddReal));
                //std::cout << gFIRInstructionTable[i + (FIRInstruction::kAddRealHeap - FIRInstruction::kAddReal)] << std::endl;
            }
             */
        }
    
        virtual ~InterpreterCodeContainer()
        {}

        virtual void produceClass();
        virtual void generateCompute(int tab) = 0;
        void produceInternal();
        
        interpreter_dsp_factory* produceModuleFloat();
        //interpreter_dsp_factory<double>* produceModuleDouble();
        //interpreter_dsp_factory<quad>* produceModuleQuad();

        CodeContainer* createScalarContainer(const string& name, int sub_container_type);

        static CodeContainer* createContainer(const string& name, int numInputs, int numOutputs);
};

class InterpreterScalarCodeContainer : public InterpreterCodeContainer {

    protected:

    public:

        InterpreterScalarCodeContainer(const string& name, int numInputs, int numOutputs, int sub_container_type);
        virtual ~InterpreterScalarCodeContainer();

        void generateCompute(int tab);

};

#endif
