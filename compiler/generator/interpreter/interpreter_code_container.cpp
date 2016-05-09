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
 
 - a single global visitor for main and sub-containers
 - multiple unneeded cast are eliminated in CastNumInst
 - 'faustpower' recoded as pow(x,y) in powprim.hh
 - sub-containers code is 'inlined' : fields declarations (using the  global visitor) and code 'classInit', and 'instanceInit' of the main container
*/

template <class T> map <string, FIRInstruction::Opcode> InterpreterInstVisitor<T>::gMathLibTable;

template <class T>
static FIRBlockInstruction<T>* getCurrentBlock()
{
    return dynamic_cast<InterpreterInstVisitor<T>*>(gGlobal->gInterpreterVisitor)->fCurrentBlock;
}

template <class T>
static InterpreterInstVisitor<T>* getInterpreterVisitor()
{
    return dynamic_cast<InterpreterInstVisitor<T>*>(gGlobal->gInterpreterVisitor);
}

template <class T>
static void setCurrentBlock(FIRBlockInstruction<T>* block)
{
    dynamic_cast<InterpreterInstVisitor<T>*>(gGlobal->gInterpreterVisitor)->fCurrentBlock = block;
}

template <class T>
InterpreterCodeContainer<T>::InterpreterCodeContainer(const string& name, int numInputs, int numOutputs)
{
    initializeCodeContainer(numInputs, numOutputs);
    fKlassName = name;
    
    // Allocate one static visitor
    if (!gGlobal->gInterpreterVisitor) {
        gGlobal->gInterpreterVisitor = new InterpreterInstVisitor<T>();
        cout << "InterpreterCodeContainer<T>::InterpreterCodeContainer INIT" << endl;
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
    //cout << "generateGlobalDeclarations" << endl;
    generateGlobalDeclarations(gGlobal->gInterpreterVisitor);
    
    //cout << "generateDeclarations" << endl;
    generateDeclarations(gGlobal->gInterpreterVisitor);
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
    generateGlobalDeclarations(gGlobal->gInterpreterVisitor);

    //cout << "generateDeclarations" << endl;
    generateDeclarations(gGlobal->gInterpreterVisitor);
    
    // After field declaration...
    generateSubContainers();
    
    // Rename 'sig' in 'dsp' and remove 'dsp' allocation and inline
    {
        DspRenamer renamer;
        BlockInst* res1 = renamer.getCode(fStaticInitInstructions);
        
        list<CodeContainer*>::const_iterator it;
        for (it = fSubContainers.begin(); it != fSubContainers.end(); it++) {
            DeclareFunInst* inst_init_fun = (*it)->generateInstanceInitFun("instanceInit" + (*it)->getClassName(), true, false);
            InlineVoidFunctionCall inliner1(inst_init_fun);
            res1 = inliner1.getCode(res1);
            DeclareFunInst* fill_fun = (*it)->generateFillFun("fill" + (*it)->getClassName(), true, false);
            InlineVoidFunctionCall inliner2(fill_fun);
            res1 = inliner2.getCode(res1);
        }
        
        res1->accept(gGlobal->gInterpreterVisitor);
    }
    // End inline
    
    // Keep "init_static_block"
    FIRBlockInstruction<T>* init_static_block = getCurrentBlock<T>();
    setCurrentBlock<T>(new FIRBlockInstruction<T>());
    
    // Rename 'sig' in 'dsp' and remove 'dsp' allocation and inline
    {
        DspRenamer renamer;
        BlockInst* res1 = renamer.getCode(fInitInstructions);
        
        list<CodeContainer*>::const_iterator it;
        for (it = fSubContainers.begin(); it != fSubContainers.end(); it++) {
            DeclareFunInst* inst_init_fun = (*it)->generateInstanceInitFun("instanceInit" + (*it)->getClassName(), true, false);
            InlineVoidFunctionCall inliner1(inst_init_fun);
            res1 = inliner1.getCode(res1);
            DeclareFunInst* fill_fun = (*it)->generateFillFun("fill" + (*it)->getClassName(), true, false);
            InlineVoidFunctionCall inliner2(fill_fun);
            res1 = inliner2.getCode(res1);
        }
        
        res1->accept(gGlobal->gInterpreterVisitor);
    }
    // End inline
    
    FIRBlockInstruction<T>* init_block = getCurrentBlock<T>();
    setCurrentBlock<T>(new FIRBlockInstruction<T>);
    
    //cout << "generateUserInterface" << endl;
    generateUserInterface(gGlobal->gInterpreterVisitor);
    
    // Generates local variables declaration and setup
    //cout << "generateComputeBlock" << endl;
    generateComputeBlock(gGlobal->gInterpreterVisitor);
    
    FIRBlockInstruction<T>* compute_control_block = getCurrentBlock<T>();
    setCurrentBlock<T>(new FIRBlockInstruction<T>);

    // Generates one single scalar loop
    //cout << "generateScalarLoop" << endl;
    ForLoopInst* loop = fCurLoop->generateScalarLoop(fFullCount);
    
    loop->accept(gGlobal->gInterpreterVisitor);
    FIRBlockInstruction<T>* compute_dsp_block = getCurrentBlock<T>();
    
    // Add kReturn in generated blocks
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
    interpreter_dsp_factory* factory = new interpreter_dsp_factory(new interpreter_dsp_factory_aux<T>(fKlassName,
                                                                                                       INTERP_FILE_VERSION,
                                                                                                       fNumInputs, fNumOutputs,
                                                                                                       gGlobal->gInterpreterVisitor->fIntHeapOffset,
                                                                                                       gGlobal->gInterpreterVisitor->fRealHeapOffset,
                                                                                                       gGlobal->gInterpreterVisitor->fSROffset,
                                                                                                       gGlobal->gInterpreterVisitor->fCountOffset,
                                                                                                       produceMetadata(),
                                                                                                       gGlobal->gInterpreterVisitor->fUserInterfaceBlock,
                                                                                                       init_static_block,
                                                                                                       init_block,
                                                                                                       compute_control_block,
                                                                                                       compute_dsp_block));
    
    cout << "writeInterpreterDSPFactoryToMachine" << endl;
    string machine_code = writeInterpreterDSPFactoryToMachine(factory);
    
    cout << "readInterpreterDSPFactoryFromMachine" << endl;
    interpreter_dsp_factory* factory1 = readInterpreterDSPFactoryFromMachine(machine_code);
    
    return factory1;
    */
    
    return new interpreter_dsp_factory(new interpreter_dsp_factory_aux<T>(fKlassName,
                                                                        INTERP_FILE_VERSION,
                                                                        fNumInputs, fNumOutputs,
                                                                        getInterpreterVisitor<T>()->fIntHeapOffset,
                                                                        getInterpreterVisitor<T>()->fRealHeapOffset,
                                                                        getInterpreterVisitor<T>()->fSROffset,
                                                                        getInterpreterVisitor<T>()->fCountOffset,
                                                                        produceMetadata(),
                                                                        getInterpreterVisitor<T>()->fUserInterfaceBlock,
                                                                        init_static_block,
                                                                        init_block,
                                                                        compute_control_block,
                                                                        compute_dsp_block));
    
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

