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

#include "exception.hh"
#include "Text.hh"
#include "floats.hh"
#include "global.hh"
#include "interpreter_code_container.hh"
#include "interpreter_optimizer.hh"
#include "interpreter_instructions.hh"

using namespace std;

/*
Interpretor : 
 
 - multiple unneeded cast are eliminated in CastNumInst
 - 'faustpower' recoded as pow(x,y)

*/

template <class T> map <string, FIRInstruction::Opcode> InterpreterInstVisitor<T>::gMathLibTable;

InterpreterCodeContainer::InterpreterCodeContainer(const string& name, int numInputs, int numOutputs)
{
    initializeCodeContainer(numInputs, numOutputs);
    fKlassName = name;
    
    // Allocate one static visitor
    if (!gGlobal->gInterpreterVisitor) {
        gGlobal->gInterpreterVisitor = new InterpreterInstVisitor<float>();
    }
    
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
    
    // Manually set inverted versions
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
    
    // Init unary math heap opcode
    for (int i = FIRInstruction::kAbs; i <= FIRInstruction::kMinf; i++) {
        FIRInstruction::gFIRExtendedMath2Heap[FIRInstruction::Opcode(i)]
            = FIRInstruction::Opcode(i + (FIRInstruction::kAbsHeap - FIRInstruction::kAbs));
        //std::cout << gFIRInstructionTable[i + (FIRInstruction::kAddRealHeap - FIRInstruction::kAddReal)] << std::endl;
    }
    
    // Init unary math direct opcode
    for (int i = FIRInstruction::kAtan2f; i <= FIRInstruction::kMinf; i++) {
        FIRInstruction::gFIRExtendedMath2Direct[FIRInstruction::Opcode(i)]
            = FIRInstruction::Opcode(i + (FIRInstruction::kAtan2fDirect - FIRInstruction::kAtan2f));
        //std::cout << gFIRInstructionTable[i + (FIRInstruction::kAddRealHeap - FIRInstruction::kAddReal)] << std::endl;
    }
    
    // Init unary math direct opcode : non commutative operations
    for (int i = FIRInstruction::kAtan2f; i <= FIRInstruction::kPowf; i++) {
        FIRInstruction::gFIRExtendedMath2DirectInvert[FIRInstruction::Opcode(i)]
            = FIRInstruction::Opcode(i + (FIRInstruction::kAtan2fDirectInvert - FIRInstruction::kAtan2f));
        //std::cout << gFIRInstructionTable[i + (FIRInstruction::kAddRealHeap - FIRInstruction::kAddReal)] << std::endl;
    }
}

CodeContainer* InterpreterCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new InterpreterScalarCodeContainer(name, 0, 1, sub_container_type);
}

CodeContainer* InterpreterCodeContainer::createContainer(const string& name, int numInputs, int numOutputs)
{
    CodeContainer* container;

    if (gGlobal->gOpenCLSwitch) {
        throw faustexception("ERROR : OpenCL not supported for Interpreter\n");
    }
    if (gGlobal->gCUDASwitch) {
        throw faustexception("ERROR : CUDA not supported for Interpreter\n");
    }

    if (gGlobal->gOpenMPSwitch) {
        throw faustexception("ERROR : OpenMP not supported for Interpreter\n");
    } else if (gGlobal->gSchedulerSwitch) {
        throw faustexception("ERROR : Scheduler not supported for Interpreter\n");
    } else if (gGlobal->gVectorSwitch) {
        throw faustexception("ERROR : Vector not supported for Interpreter\n");
    } else {
        container = new InterpreterScalarCodeContainer(name, numInputs, numOutputs, kInt);
    }

    return container;
}

// Scalar
InterpreterScalarCodeContainer::InterpreterScalarCodeContainer(const string& name,  int numInputs, int numOutputs, int sub_container_type)
    :InterpreterCodeContainer(name, numInputs, numOutputs)
{
     fSubContainerType = sub_container_type;
}

InterpreterScalarCodeContainer::~InterpreterScalarCodeContainer()
{}

void InterpreterCodeContainer::produceInternal()
{
    
}

interpreter_dsp_factory* InterpreterCodeContainer::produceFactoryFloat()
{
    cout << "InterpreterCodeContainer::produceModuleFloat() " << fNumInputs << " " << fNumOutputs << endl;
    
    /*
    for (int i = 0; i < (int)FIRInstruction::kDeclare; i++) {
        std::cout << gFIRInstructionTable[i] << std::endl;
    }
    */
    
    // Add "fSamplingFreq" variable at offset 0 in HEAP
    if (!fGeneratedSR) {
        fDeclarationInstructions->pushBackInst(InstBuilder::genDecStructVar("fSamplingFreq", InstBuilder::genBasicTyped(Typed::kInt)));
    }
    
    cout << "-----generateGlobalDeclarations-----" << endl;
    generateGlobalDeclarations(gGlobal->gInterpreterVisitor);

    cout << "-----generateDeclarations-----" << endl;
    generateDeclarations(gGlobal->gInterpreterVisitor);
    
    //generateAllocate(gGlobal->gInterpreterVisitor);
    //generateDestroy(gGlobal->gInterpreterVisitor);
    
    cout << "-----generateStaticInit-----" << endl;
    generateStaticInit(gGlobal->gInterpreterVisitor);
    
    cout << "-----generateInit-----" << endl;
    generateInit(gGlobal->gInterpreterVisitor);
    
    FIRBlockInstruction<float>* init_block = gGlobal->gInterpreterVisitor->fCurrentBlock;
    gGlobal->gInterpreterVisitor->fCurrentBlock = new FIRBlockInstruction<float>();
    
    cout << "-----generateUserInterface-----" << endl;
    generateUserInterface(gGlobal->gInterpreterVisitor);
    
    // Generates local variables declaration and setup
    cout << "-----generateComputeBlock-----" << endl;
    generateComputeBlock(gGlobal->gInterpreterVisitor);
    
    FIRBlockInstruction<float>* compute_control_block = gGlobal->gInterpreterVisitor->fCurrentBlock;
    gGlobal->gInterpreterVisitor->fCurrentBlock = new FIRBlockInstruction<float>();

    // Generates one single scalar loop
    cout << "-----generateScalarLoop-----" << endl;
    ForLoopInst* loop = fCurLoop->generateScalarLoop(fFullCount);
    loop->accept(gGlobal->gInterpreterVisitor);
    
    FIRBlockInstruction<float>* compute_dsp_block = gGlobal->gInterpreterVisitor->fCurrentBlock;
    
    // generateCompute(0);
    
    //generateComputeFunctions(gGlobal->gInterpreterVisitor);
    
    
    // Add kHalt in blocks
    init_block->push(new FIRBasicInstruction<float>(FIRInstruction::kHalt));
    compute_control_block->push(new FIRBasicInstruction<float>(FIRInstruction::kHalt));
    compute_dsp_block->push(new FIRBasicInstruction<float>(FIRInstruction::kHalt));
    
    // Bytecode optimization
    
    printf("fComputeDSPBlock size = %d\n", compute_dsp_block->size());
    
    // 1) optimize indexed 'heap' load/store in normal load/store
    FIRInstructionLoadStoreOptimizer<float> opt1;
    init_block = FIRInstructionOptimizer<float>::optimize(init_block, opt1);
    compute_control_block = FIRInstructionOptimizer<float>::optimize(compute_control_block, opt1);
    compute_dsp_block = FIRInstructionOptimizer<float>::optimize(compute_dsp_block, opt1);
    
    printf("fComputeDSPBlock size = %d\n", compute_dsp_block->size());
    
    // 2) then pptimize simple 'heap' load/store in move
    FIRInstructionMoveOptimizer<float> opt2;
    init_block = FIRInstructionOptimizer<float>::optimize(init_block, opt2);
    compute_control_block = FIRInstructionOptimizer<float>::optimize(compute_control_block, opt2);
    compute_dsp_block = FIRInstructionOptimizer<float>::optimize(compute_dsp_block, opt2);
    
    printf("fComputeDSPBlock size = %d\n", compute_dsp_block->size());
    
    // 3) them optimize 'heap' and 'direct' math operations
    FIRInstructionMathOptimizer<float> opt3;
    init_block = FIRInstructionOptimizer<float>::optimize(init_block, opt3);
    compute_control_block = FIRInstructionOptimizer<float>::optimize(compute_control_block, opt3);
    compute_dsp_block = FIRInstructionOptimizer<float>::optimize(compute_dsp_block, opt3);
    
    printf("fComputeDSPBlock size = %d\n", compute_dsp_block->size());
    
    // TODO
    /*
    int int_index = 0;
    int real_index = 0;
    compute_dsp_block->stackMove(int_index, real_index);
    printf("fComputeDSPBlock int stack = %d real stack = %d\n", int_index, real_index);
    */
   
    return new interpreter_dsp_factory(fNumInputs, fNumOutputs,
                                        gGlobal->gInterpreterVisitor->fRealHeapOffset,
                                        gGlobal->gInterpreterVisitor->fIntHeapOffset,
                                        gGlobal->gInterpreterVisitor->fSROffset,
                                        gGlobal->gInterpreterVisitor->fUserInterfaceBlock,
                                        init_block,
                                        compute_control_block,
                                        compute_dsp_block);
}

/*
interpreter_dsp_aux<double>* InterpreterCodeContainer::produceModuleDouble()
{
    cout << "InterpreterCodeContainer::produceModuleDouble()" << endl;
    //return new interpreter_dsp_aux<double>(fNumInputs, fNumOutputs, 0, 0, NULL, NULL, NULL, NULL);
    return NULL;
}

interpreter_dsp_aux<quad>* InterpreterCodeContainer::produceModuleQuad()
{
    cout << "InterpreterCodeContainer::produceModuleQuad()" << endl;
    //return new interpreter_dsp_aux<quad>(fNumInputs, fNumOutputs, 0, 0, NULL, NULL, NULL, NULL);
    return NULL;
}
*/

void InterpreterCodeContainer::produceClass()
{
    /*
    printf("InterpreterCodeContainer::produceClass\n");
    
    // Add "fSamplingFreq" variable at offset 0 in HEAP
    pushDeclare(InstBuilder::genDecStructVar("fSamplingFreq", InstBuilder::genBasicTyped(Typed::kInt)));
    
    generateGlobalDeclarations(gGlobal->gInterpreterVisitor);

    generateDeclarations(gGlobal->gInterpreterVisitor);
    
    //generateAllocate(gGlobal->gInterpreterVisitor);
    //generateDestroy(gGlobal->gInterpreterVisitor);
    
    generateStaticInit(gGlobal->gInterpreterVisitor);
    
    //generateInit(gGlobal->gInterpreterVisitor);
    
    generateUserInterface(gGlobal->gInterpreterVisitor);
    
    generateCompute(0);
    
    //generateComputeFunctions(gGlobal->gInterpreterVisitor);
    */
}

void InterpreterCodeContainer::produceInfoFunctions(int tabs, const string& classname, bool isvirtual)
{}

void InterpreterScalarCodeContainer::generateCompute(int n)
{
    // Generates local variables declaration and setup
    //generateComputeBlock(gGlobal->gInterpreterVisitor);

    // Generates one single scalar loop
    ForLoopInst* loop = fCurLoop->generateScalarLoop(fFullCount);
    loop->accept(gGlobal->gInterpreterVisitor);
}

