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
Interpreter backend description:
 
 - a single global visitor for main and sub-containers
 - 'fSamplingFreq' and 'count' variable manually added in the IntHeap to be setup in 'instanceInit' and 'compute'
 - multiple unneeded cast are eliminated in CastInst
 - 'faustpower' function directly inlined in the code (see CodeContainer::pushFunction)
 - sub-containers code is 'inlined' : fields declarations (using the global visitor) and code 'classInit', and 'instanceInit' of the main container
 - 'clone' method is implemented in the 'interpreter_dsp' wrapping code
 
 TODO: in -mem mode, classInit and classDestroy will have to be called once at factory init and destroy time (after global memory allocation is implemented)
*/

template <class T> map <string, FIRInstruction::Opcode> InterpreterInstVisitor<T>::gMathLibTable;

template <class T>
static FIRBlockInstruction<T>* getCurrentBlock()
{
    FIRBlockInstruction<T>* block = dynamic_cast<InterpreterInstVisitor<T>*>(gGlobal->gInterpreterVisitor)->fCurrentBlock;
    // Add kReturn in generated block
    block->push(new FIRBasicInstruction<T>(FIRInstruction::kReturn));
    return block;
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
    }    
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

    if (gGlobal->gMemoryManager) {
        throw faustexception("ERROR : -mem not suported for Interpreter\n");
    }
    if (gGlobal->gOpenCLSwitch) {
        throw faustexception("ERROR : OpenCL not supported for Interpreter\n");
    }
    if (gGlobal->gCUDASwitch) {
        throw faustexception("ERROR : CUDA not supported for Interpreter\n");
    }

    if (gGlobal->gOpenMPSwitch) {
        throw faustexception("ERROR : OpenMP not supported for Interpreter\n");
    } else if (gGlobal->gSchedulerSwitch) {
        throw faustexception("ERROR : Scheduler mode not supported for Interpreter\n");
    } else if (gGlobal->gVectorSwitch) {
        throw faustexception("ERROR : Vector mode not supported for Interpreter\n");
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
void InterpreterCodeContainer<T>::produceInternal()
{
    // Fields generation
    generateGlobalDeclarations(gGlobal->gInterpreterVisitor);
    generateDeclarations(gGlobal->gInterpreterVisitor);
}

template <class T>
dsp_factory_base* InterpreterCodeContainer<T>::produceFactory()
{
    // "count" variable added to be set up later by 'compute'
    fDeclarationInstructions->pushBackInst(InstBuilder::genDecStructVar("count", InstBuilder::genBasicTyped(Typed::kInt32)));
    
    // Sub containers
    mergeSubContainers();
    
    generateGlobalDeclarations(gGlobal->gInterpreterVisitor);
    generateDeclarations(gGlobal->gInterpreterVisitor);
    
    // After field declaration...
    generateSubContainers();
    
    // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
    inlineSubcontainersFunCalls(fStaticInitInstructions)->accept(gGlobal->gInterpreterVisitor);
    // Keep "init_static_block"
    FIRBlockInstruction<T>* init_static_block = getCurrentBlock<T>();
    setCurrentBlock<T>(new FIRBlockInstruction<T>());
    
    // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
    inlineSubcontainersFunCalls(fInitInstructions)->accept(gGlobal->gInterpreterVisitor);
    // Keep "init_block"
    FIRBlockInstruction<T>* init_block = getCurrentBlock<T>();
    setCurrentBlock<T>(new FIRBlockInstruction<T>);
    
    // Keep "resetui_block"
    generateResetUserInterface(gGlobal->gInterpreterVisitor);
    FIRBlockInstruction<T>* resetui_block = getCurrentBlock<T>();
    setCurrentBlock<T>(new FIRBlockInstruction<T>);
    
    // Keep "clear_block"
    generateClear(gGlobal->gInterpreterVisitor);
    FIRBlockInstruction<T>* clear_block = getCurrentBlock<T>();
    setCurrentBlock<T>(new FIRBlockInstruction<T>);
    
    // Generate UI
    generateUserInterface(gGlobal->gInterpreterVisitor);
    
    // Generate local variables declaration and setup
    generateComputeBlock(gGlobal->gInterpreterVisitor);
    
    // Keep "compute_control_block"
    FIRBlockInstruction<T>* compute_control_block = getCurrentBlock<T>();
    setCurrentBlock<T>(new FIRBlockInstruction<T>);

    // Generate one single scalar loop
    ForLoopInst* loop = fCurLoop->generateScalarLoop(fFullCount);
    
    loop->accept(gGlobal->gInterpreterVisitor);
    FIRBlockInstruction<T>* compute_dsp_block = getCurrentBlock<T>();
    
    // Generate metadata block and name
    string name;
    FIRMetaBlockInstruction* metadata_block = produceMetadata(name);
    
    // Then create factory depending of the trace mode
    const char* trace = getenv("FAUST_INTERP_TRACE");
    int mode = (trace) ? atoi(trace) : 0;
    
    if (mode == 1) {
        return new interpreter_dsp_factory_aux<T, 1>(name, "",
                                                     gGlobal->gReader.listSrcFiles(),
                                                     INTERP_FILE_VERSION,
                                                     fNumInputs, fNumOutputs,
                                                     getInterpreterVisitor<T>()->fIntHeapOffset,
                                                     getInterpreterVisitor<T>()->fRealHeapOffset,
                                                     getInterpreterVisitor<T>()->getFieldOffset("fSamplingFreq"),
                                                     getInterpreterVisitor<T>()->getFieldOffset("count"),
                                                     getInterpreterVisitor<T>()->getFieldOffset("IOTA"),
                                                     INTER_MAX_OPT_LEVEL,
                                                     metadata_block,
                                                     getInterpreterVisitor<T>()->fUserInterfaceBlock,
                                                     init_static_block,
                                                     init_block,
                                                     resetui_block,
                                                     clear_block,
                                                     compute_control_block,
                                                     compute_dsp_block);
        
    } else if (mode == 2) {
        return new interpreter_dsp_factory_aux<T, 2>(name, "",
                                                     gGlobal->gReader.listSrcFiles(),
                                                     INTERP_FILE_VERSION,
                                                     fNumInputs, fNumOutputs,
                                                     getInterpreterVisitor<T>()->fIntHeapOffset,
                                                     getInterpreterVisitor<T>()->fRealHeapOffset,
                                                     getInterpreterVisitor<T>()->getFieldOffset("fSamplingFreq"),
                                                     getInterpreterVisitor<T>()->getFieldOffset("count"),
                                                     getInterpreterVisitor<T>()->getFieldOffset("IOTA"),
                                                     INTER_MAX_OPT_LEVEL,
                                                     metadata_block,
                                                     getInterpreterVisitor<T>()->fUserInterfaceBlock,
                                                     init_static_block,
                                                     init_block,
                                                     resetui_block,
                                                     clear_block,
                                                     compute_control_block,
                                                     compute_dsp_block);
        
    } else if (mode == 3) {
        return new interpreter_dsp_factory_aux<T, 3>(name, "",
                                                     gGlobal->gReader.listSrcFiles(),
                                                     INTERP_FILE_VERSION,
                                                     fNumInputs, fNumOutputs,
                                                     getInterpreterVisitor<T>()->fIntHeapOffset,
                                                     getInterpreterVisitor<T>()->fRealHeapOffset,
                                                     getInterpreterVisitor<T>()->getFieldOffset("fSamplingFreq"),
                                                     getInterpreterVisitor<T>()->getFieldOffset("count"),
                                                     getInterpreterVisitor<T>()->getFieldOffset("IOTA"),
                                                     INTER_MAX_OPT_LEVEL,
                                                     metadata_block,
                                                     getInterpreterVisitor<T>()->fUserInterfaceBlock,
                                                     init_static_block,
                                                     init_block,
                                                     resetui_block,
                                                     clear_block,
                                                     compute_control_block,
                                                     compute_dsp_block);
        
    } else if (mode == 4) {
        return new interpreter_dsp_factory_aux<T, 4>(name, "",
                                                     gGlobal->gReader.listSrcFiles(),
                                                     INTERP_FILE_VERSION,
                                                     fNumInputs, fNumOutputs,
                                                     getInterpreterVisitor<T>()->fIntHeapOffset,
                                                     getInterpreterVisitor<T>()->fRealHeapOffset,
                                                     getInterpreterVisitor<T>()->getFieldOffset("fSamplingFreq"),
                                                     getInterpreterVisitor<T>()->getFieldOffset("count"),
                                                     getInterpreterVisitor<T>()->getFieldOffset("IOTA"),
                                                     INTER_MAX_OPT_LEVEL,
                                                     metadata_block,
                                                     getInterpreterVisitor<T>()->fUserInterfaceBlock,
                                                     init_static_block,
                                                     init_block,
                                                     resetui_block,
                                                     clear_block,
                                                     compute_control_block,
                                                     compute_dsp_block);
        
    } else if (mode == 5) {
        return new interpreter_dsp_factory_aux<T, 5>(name, "",
                                                     gGlobal->gReader.listSrcFiles(),
                                                     INTERP_FILE_VERSION,
                                                     fNumInputs, fNumOutputs,
                                                     getInterpreterVisitor<T>()->fIntHeapOffset,
                                                     getInterpreterVisitor<T>()->fRealHeapOffset,
                                                     getInterpreterVisitor<T>()->getFieldOffset("fSamplingFreq"),
                                                     getInterpreterVisitor<T>()->getFieldOffset("count"),
                                                     getInterpreterVisitor<T>()->getFieldOffset("IOTA"),
                                                     INTER_MAX_OPT_LEVEL,
                                                     metadata_block,
                                                     getInterpreterVisitor<T>()->fUserInterfaceBlock,
                                                     init_static_block,
                                                     init_block,
                                                     resetui_block,
                                                     clear_block,
                                                     compute_control_block,
                                                     compute_dsp_block);
        
    } else {
        // Default case, no trace...
        return new interpreter_dsp_factory_aux<T, 0>(name, "",
                                                     gGlobal->gReader.listSrcFiles(),
                                                     INTERP_FILE_VERSION,
                                                     fNumInputs, fNumOutputs,
                                                     getInterpreterVisitor<T>()->fIntHeapOffset,
                                                     getInterpreterVisitor<T>()->fRealHeapOffset,
                                                     getInterpreterVisitor<T>()->getFieldOffset("fSamplingFreq"),
                                                     getInterpreterVisitor<T>()->getFieldOffset("count"),
                                                     getInterpreterVisitor<T>()->getFieldOffset("IOTA"),
                                                     INTER_MAX_OPT_LEVEL,
                                                     metadata_block,
                                                     getInterpreterVisitor<T>()->fUserInterfaceBlock,
                                                     init_static_block,
                                                     init_block,
                                                     resetui_block,
                                                     clear_block,
                                                     compute_control_block,
                                                     compute_dsp_block);
    }
}

template <class T>
FIRMetaBlockInstruction* InterpreterCodeContainer<T>::produceMetadata(string& name)
{
    FIRMetaBlockInstruction* block = new FIRMetaBlockInstruction();
    
    // Add global metadata
    for (MetaDataSet::iterator i = gGlobal->gMetaDataSet.begin(); i != gGlobal->gMetaDataSet.end(); i++) {
        if (i->first != tree("author")) {
            stringstream str1, str2;
            str1 << *(i->first);
            str2 << **(i->second.begin());
            if (str1.str() == "name") name = unquote(str2.str());
            block->push(new FIRMetaInstruction(str1.str(), unquote(str2.str())));
        } else {
            for (set<Tree>::iterator j = i->second.begin(); j != i->second.end(); j++) {
                if (j == i->second.begin()) {
                    stringstream str1, str2;
                    str1 << *(i->first);
                    str2 << **j;
                    if (str1.str() == "name") name = unquote(str2.str());
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
