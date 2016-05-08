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
#include "fir_to_fir.hh"

using namespace std;

/*
Interpretor : 
 
 - multiple unneeded cast are eliminated in CastNumInst
 - 'faustpower' recoded as pow(x,y) in powprim.hh

*/

template <class T> map <string, FIRInstruction::Opcode> InterpreterInstVisitor<T>::gMathLibTable;
template <class T> InterpreterInstVisitor<T>* InterpreterCodeContainer<T>::gInterpreterVisitor;

template <class T>
InterpreterCodeContainer<T>::InterpreterCodeContainer(const string& name, int numInputs, int numOutputs)
{
    initializeCodeContainer(numInputs, numOutputs);
    fKlassName = name;
    
    // Allocate one static visitor
    if (!gInterpreterVisitor) {
        gInterpreterVisitor = new InterpreterInstVisitor<T>();
    }
    
    FIRInstructionOptimizer<T>::initTables();
}

template <class T>
CodeContainer* InterpreterCodeContainer<T>::createScalarContainer(const string& name, int sub_container_type)
{
    return new InterpreterScalarCodeContainer<T>(name, 0, 1, sub_container_type);
}

template <class T>
CodeContainer* InterpreterCodeContainer<T>::createContainer(const string& name, int numInputs, int numOutputs)
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
        container = new InterpreterScalarCodeContainer<T>(name, numInputs, numOutputs, kInt);
    }

    return container;
}

// Scalar
template <class T>
InterpreterScalarCodeContainer<T>::InterpreterScalarCodeContainer(const string& name, int numInputs, int numOutputs, int sub_container_type)
    :InterpreterCodeContainer<T>(name, numInputs, numOutputs)
{
     this->fSubContainerType = sub_container_type;
}

template <class T>
InterpreterScalarCodeContainer<T>::~InterpreterScalarCodeContainer()
{}

template <class T>
FIRBlockInstruction<T>* InterpreterCodeContainer<T>::testOptimizer(FIRBlockInstruction<T>* block, int& size)
{
    
    cout << "fComputeDSPBlock size = " << block->size() << endl;
    
    // 1) optimize indexed 'heap' load/store in normal load/store
    FIRInstructionLoadStoreOptimizer<T> opt1;
    block = FIRInstructionOptimizer<T>::optimize(block, opt1);
    
    cout << "fComputeDSPBlock size = " << block->size() << endl;
    
    // 2) then pptimize simple 'heap' load/store in move
    FIRInstructionMoveOptimizer<T> opt2;
    block = FIRInstructionOptimizer<T>::optimize(block, opt2);
    
    cout << "fComputeDSPBlock size = " << block->size() << endl;
    
    // 3) optimize 'cast' in heap cast
    FIRInstructionCastOptimizer<T> opt3;
    block = FIRInstructionOptimizer<T>::optimize(block, opt3);
    
    cout << "fComputeDSPBlock size = " << block->size() << endl;
    
    // 4) them optimize 'heap' and 'Value' math operations
    FIRInstructionMathOptimizer<T> opt4;
    block = FIRInstructionOptimizer<T>::optimize(block, opt4);
    
    cout << "fComputeDSPBlock size = " << block->size() << endl << endl;
    
    size = block->size();
    return block;
}

template <class T>
void InterpreterCodeContainer<T>::produceInternal()
{
    cout << "InterpreterCodeContainer<T>::produceInternal" << endl;
    
    cout << "generateGlobalDeclarations" << endl;
    generateGlobalDeclarations(gInterpreterVisitor);
    
    cout << "generateDeclarations" << endl;
    generateDeclarations(gInterpreterVisitor);
    
    cout << "generateStaticInit" << endl;
    generateStaticInit(gInterpreterVisitor);
    
    cout << "generateInit" << endl;
    generateInit(gInterpreterVisitor);
    
    cout << "generateFill" << endl;
    string counter = "count";
    
    // Generates one single scalar loop and put is the the block
    ForLoopInst* loop = fCurLoop->generateScalarLoop(counter);
    loop->accept(gInterpreterVisitor);
    //fComputeBlockInstructions->pushBackInst(loop);
    
}

template <class T>
interpreter_dsp_factory* InterpreterCodeContainer<T>::produceFactory()
{
    // Add "fSamplingFreq" variable at offset 0 in HEAP
    if (!fGeneratedSR) {
        fDeclarationInstructions->pushBackInst(InstBuilder::genDecStructVar("fSamplingFreq", InstBuilder::genBasicTyped(Typed::kInt)));
    }
    
    // "count" variable
    fDeclarationInstructions->pushBackInst(InstBuilder::genDecStructVar("count", InstBuilder::genBasicTyped(Typed::kInt)));
    
    // Sub containers
    mergeSubContainers();
    
    //cout << "generateGlobalDeclarations" << endl;
    generateGlobalDeclarations(gInterpreterVisitor);

    //cout << "generateDeclarations" << endl;
    generateDeclarations(gInterpreterVisitor);
    
    // After field declaration...
    generateSubContainers();
    
    //generateAllocate(gInterpreterVisitor);
    //generateDestroy(gInterpreterVisitor);
    
    //cout << "generateStaticInit" << endl;
    //generateStaticInit(gInterpreterVisitor);
    
    //fStaticInitInstructions->accept(gInterpreterVisitor);
    //fPostStaticInitInstructions->accept(gInterpreterVisitor);
    
    // Rename 'sig' in 'dsp' and remove 'dsp' allocation
    DspRenamer renamer1;
    BlockInst* block1 = renamer1.getCode(fStaticInitInstructions);
    block1->accept(gInterpreterVisitor);
    
    
    // Keep "init_static_block"
    FIRBlockInstruction<T>* init_static_block = gInterpreterVisitor->fCurrentBlock;
    gInterpreterVisitor->fCurrentBlock = new FIRBlockInstruction<T>();
    
    /*
    //cout << "generateInit" << endl;
    generateInit(gInterpreterVisitor);
    */
    
    // Rename 'sig' in 'dsp' and remove 'dsp' allocation
    DspRenamer renamer2;
    BlockInst* block2 = renamer2.getCode(fInitInstructions);
    block2->accept(gInterpreterVisitor);
    
    
    FIRBlockInstruction<T>* init_block = gInterpreterVisitor->fCurrentBlock;
    gInterpreterVisitor->fCurrentBlock = new FIRBlockInstruction<T>();
    
    //cout << "generateUserInterface" << endl;
    generateUserInterface(gInterpreterVisitor);
    
    // Generates local variables declaration and setup
    //cout << "generateComputeBlock" << endl;
    generateComputeBlock(gInterpreterVisitor);
    
    FIRBlockInstruction<T>* compute_control_block = gInterpreterVisitor->fCurrentBlock;
    gInterpreterVisitor->fCurrentBlock = new FIRBlockInstruction<T>();

    // Generates one single scalar loop
    //cout << "generateScalarLoop" << endl;
    ForLoopInst* loop = fCurLoop->generateScalarLoop(fFullCount);
    
    loop->accept(gInterpreterVisitor);
    FIRBlockInstruction<T>* compute_dsp_block = gInterpreterVisitor->fCurrentBlock;
   
    //generateCompute(0);
    //generateComputeFunctions(gInterpreterVisitor);
    
    // Add kReturn in blocks
    init_static_block->push(new FIRBasicInstruction<T>(FIRInstruction::kReturn));
    init_block->push(new FIRBasicInstruction<T>(FIRInstruction::kReturn));
    compute_control_block->push(new FIRBasicInstruction<T>(FIRInstruction::kReturn));
    compute_dsp_block->push(new FIRBasicInstruction<T>(FIRInstruction::kReturn));
    
    // Bytecode optimization
    
    /*
    cout << "fComputeDSPBlock size = " << compute_dsp_block->size() << endl;
    
    FIRInstructionCopyOptimizer<T> opt0;
    init_block = FIRInstructionOptimizer<T>::optimize(init_block, opt0);
    compute_control_block = FIRInstructionOptimizer<T>::optimize(compute_control_block, opt0);
    compute_dsp_block = FIRInstructionOptimizer<T>::optimize(compute_dsp_block, opt0);
    */
    
    //cout << "fComputeDSPBlock size = " << compute_dsp_block->size() << endl;
   
    // 1) optimize indexed 'heap' load/store in normal load/store
    FIRInstructionLoadStoreOptimizer<T> opt1;
    init_static_block = FIRInstructionOptimizer<T>::optimize(init_static_block, opt1);
    init_block = FIRInstructionOptimizer<T>::optimize(init_block, opt1);
    compute_control_block = FIRInstructionOptimizer<T>::optimize(compute_control_block, opt1);
    compute_dsp_block = FIRInstructionOptimizer<T>::optimize(compute_dsp_block, opt1);
    
    //cout << "fComputeDSPBlock size = " << compute_dsp_block->size() << endl;
    
    // 2) then optimize simple 'heap' load/store in move
    FIRInstructionMoveOptimizer<T> opt2;
    init_static_block = FIRInstructionOptimizer<T>::optimize(init_static_block, opt2);
    init_block = FIRInstructionOptimizer<T>::optimize(init_block, opt2);
    compute_control_block = FIRInstructionOptimizer<T>::optimize(compute_control_block, opt2);
    compute_dsp_block = FIRInstructionOptimizer<T>::optimize(compute_dsp_block, opt2);
    
    //cout << "fComputeDSPBlock size = " << compute_dsp_block->size() << endl;
    
    // 3) then optimize moves in block move
    FIRInstructionBlockMoveOptimizer<T> opt3;
    init_static_block = FIRInstructionOptimizer<T>::optimize(init_static_block, opt3);
    init_block = FIRInstructionOptimizer<T>::optimize(init_block, opt3);
    compute_control_block = FIRInstructionOptimizer<T>::optimize(compute_control_block, opt3);
    compute_dsp_block = FIRInstructionOptimizer<T>::optimize(compute_dsp_block, opt3);
    
    //cout << "fComputeDSPBlock size = " << compute_dsp_block->size() << endl;
   
    // 4) then optimize 2 moves in pair move
    FIRInstructionPairMoveOptimizer<T> opt4;
    init_static_block = FIRInstructionOptimizer<T>::optimize(init_static_block, opt4);
    init_block = FIRInstructionOptimizer<T>::optimize(init_block, opt4);
    compute_control_block = FIRInstructionOptimizer<T>::optimize(compute_control_block, opt4);
    compute_dsp_block = FIRInstructionOptimizer<T>::optimize(compute_dsp_block, opt4);
    
    //cout << "fComputeDSPBlock size = " << compute_dsp_block->size() << endl;
    
    // 5) optimize 'cast' in heap cast
    FIRInstructionCastOptimizer<T> opt5;
    init_static_block = FIRInstructionOptimizer<T>::optimize(init_static_block, opt5);
    init_block = FIRInstructionOptimizer<T>::optimize(init_block, opt5);
    compute_control_block = FIRInstructionOptimizer<T>::optimize(compute_control_block, opt5);
    compute_dsp_block = FIRInstructionOptimizer<T>::optimize(compute_dsp_block, opt5);
 
    //cout << "fComputeDSPBlock size = " << compute_dsp_block->size() << endl;
    
    // 6) them optimize 'heap' and 'value' math operations
    FIRInstructionMathOptimizer<T> opt6;
    init_static_block = FIRInstructionOptimizer<T>::optimize(init_static_block, opt6);
    init_block = FIRInstructionOptimizer<T>::optimize(init_block, opt6);
    compute_control_block = FIRInstructionOptimizer<T>::optimize(compute_control_block, opt6);
    compute_dsp_block = FIRInstructionOptimizer<T>::optimize(compute_dsp_block, opt6);
    
    //cout << "fComputeDSPBlock size = " << compute_dsp_block->size() << endl << endl;
    
    /*
    init_block = FIRInstructionOptimizer<T>::optimizeBlock(init_block);
    compute_control_block = FIRInstructionOptimizer<T>::optimizeBlock(compute_control_block);
    compute_dsp_block = FIRInstructionOptimizer<T>::optimizeBlock(compute_dsp_block);
    */
    
    // TODO
    /*
    int int_index = 0;
    int real_index = 0;
    compute_dsp_block->stackMove(int_index, real_index);
    printf("fComputeDSPBlock int stack = %d real stack = %d\n", int_index, real_index);
    */
   
    // Test reader/writer
    /*
    interpreter_dsp_factory_aux<T>* factory = new interpreter_dsp_factory_aux<T>(fKlassName,
                                                                               INTERP_FILE_VERSION,
                                                                               fNumInputs, fNumOutputs,
                                                                               gInterpreterVisitor->fIntHeapOffset,
                                                                               gInterpreterVisitor->fRealHeapOffset,
                                                                               gInterpreterVisitor->fSROffset,
                                                                               gInterpreterVisitor->fCountOffset,
                                                                               produceMetadata(),
                                                                               gInterpreterVisitor->fUserInterfaceBlock,
                                                                               init_block,
                                                                               compute_control_block,
                                                                               compute_dsp_block);
    
    
    cout << "writeDSPInterpreterFactoryToMachine" << endl;
    string machine_code = writeDSPInterpreterFactoryToMachine(factory);
    
    cout << "readDSPInterpreterFactoryFromMachine" << endl;
    interpreter_dsp_factory* factory1 = readDSPInterpreterFactoryFromMachine(machine_code);
    
    return factory1;
    */
    
    return new interpreter_dsp_factory(new interpreter_dsp_factory_aux<T>(fKlassName,
                                            INTERP_FILE_VERSION,
                                            fNumInputs, fNumOutputs,
                                            gInterpreterVisitor->fIntHeapOffset,
                                            gInterpreterVisitor->fRealHeapOffset,
                                            gInterpreterVisitor->fSROffset,
                                            gInterpreterVisitor->fCountOffset,
                                            produceMetadata(),
                                            gInterpreterVisitor->fUserInterfaceBlock,
                                            init_static_block,
                                            init_block,
                                            compute_control_block,
                                            compute_dsp_block));
}

template <class T>
void InterpreterCodeContainer<T>::produceClass()
{
    /*
    printf("InterpreterCodeContainer<T>::produceClass\n");
    
    // Add "fSamplingFreq" variable at offset 0 in HEAP
    pushDeclare(InstBuilder::genDecStructVar("fSamplingFreq", InstBuilder::genBasicTyped(Typed::kInt)));
    
    generateGlobalDeclarations(gInterpreterVisitor);

    generateDeclarations(gInterpreterVisitor);
    
    //generateAllocate(gInterpreterVisitor);
    //generateDestroy(gInterpreterVisitor);
    
    generateStaticInit(gInterpreterVisitor);
    
    //generateInit(gInterpreterVisitor);
    
    generateUserInterface(gInterpreterVisitor);
    
    generateCompute(0);
    
    //generateComputeFunctions(gInterpreterVisitor);
    */
}

template <class T>
void InterpreterCodeContainer<T>::produceInfoFunctions(int tabs, const string& classname, bool isvirtual)
{}

template <class T>
void InterpreterScalarCodeContainer<T>::generateCompute(int n)
{
    // Generates local variables declaration and setup
    //generateComputeBlock(gInterpreterVisitor);

    // Generates one single scalar loop
    ForLoopInst* loop = this->fCurLoop->generateScalarLoop(this->fFullCount);
    loop->accept(this->gInterpreterVisitor);
}

template <class T>
FIRMetaBlockInstruction* InterpreterCodeContainer<T>::produceMetadata()
{
    FIRMetaBlockInstruction* block = new FIRMetaBlockInstruction();
    
    // Add global metadata
    for (MetaDataSet::iterator i = gGlobal->gMetaDataSet.begin(); i != gGlobal->gMetaDataSet.end(); i++) {
        if (i->first != tree("author")) {
            stringstream str1, str2;
            str1 << *(i->first);
            str2 << **(i->second.begin());
            block->push(new FIRMetaInstruction(str1.str(), unquote(str2.str())));
        } else {
            for (set<Tree>::iterator j = i->second.begin(); j != i->second.end(); j++) {
                if (j == i->second.begin()) {
                    stringstream str1, str2;
                    str1 << *(i->first);
                    str2 << **j;
                    block->push(new FIRMetaInstruction(str1.str(), unquote(str2.str())));
                } else {
                    stringstream str2;
                    str2 << **j;
                    block->push(new FIRMetaInstruction("contributor", unquote(str2.str())));
                }
            }
        }
    }
    
    return block;
}

