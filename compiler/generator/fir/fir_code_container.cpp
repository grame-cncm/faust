/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
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

#include "fir_code_container.hh"
#include "instructions_complexity.hh"
#include "global.hh"

using namespace std;

map <string, int> FIRInstVisitor::gFunctionSymbolTable;      

CodeContainer* FirCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new FirScalarCodeContainer(name, 0, 1, sub_container_type, false);
}

CodeContainer* FirCodeContainer::createContainer(const string& name, int numInputs, int numOutputs, bool top_level)
{
    CodeContainer* container;

    if (gGlobal->gOpenMPSwitch) {
        container = new FirOpenMPCodeContainer(name, numInputs, numOutputs, top_level);
    } else if (gGlobal->gSchedulerSwitch) {
        container = new FirWorkStealingCodeContainer(name,numInputs, numOutputs, top_level);
    } else if (gGlobal->gVectorSwitch) {
        container = new FirVectorCodeContainer(name,numInputs, numOutputs, top_level);
    } else {
        container = new FirScalarCodeContainer(name,numInputs, numOutputs, kInt, top_level);
    }

    return container;
}

void FirCodeContainer::dumpGlobalsAndInit(FIRInstVisitor& firvisitor, ostream* dst)
{
    // Subclasses
    list<CodeContainer*>::const_iterator it;
    for (it = fSubContainers.begin(); it != fSubContainers.end(); it++) {
        *dst << "======= Sub classes begin ==========" << std::endl << std::endl;
        (*it)->dump(dst);
        *dst << "======= Sub classes end ==========" << std::endl << std::endl;
    }

    // User Interface
    if (fUserInterfaceInstructions->fCode.size() > 0) {
        *dst << "======= User Interface ==========" << std::endl;
        *dst << std::endl;
        fUserInterfaceInstructions->accept(&firvisitor);
        *dst << std::endl;
    }

    if (fExtGlobalDeclarationInstructions->fCode.size() > 0) {
        *dst << "======= Global external declarations ==========" << std::endl;
        *dst << std::endl;
        fExtGlobalDeclarationInstructions->accept(&firvisitor);
        *dst << std::endl;
    }

    if (fGlobalDeclarationInstructions->fCode.size() > 0) {
        *dst << "======= Global declarations ==========" << std::endl;
        *dst << std::endl;
        fGlobalDeclarationInstructions->accept(&firvisitor);
        *dst << std::endl;
    }

    if (fDeclarationInstructions->fCode.size() > 0) {
        *dst << "======= Declarations ==========" << std::endl;
        *dst << std::endl;
        fDeclarationInstructions->accept(&firvisitor);
        *dst << std::endl;
    }
    
    generateGetInputs(subst("$0::getNumInputs", fKlassName), true, true)->accept(&firvisitor);
    *dst << std::endl;
    generateGetOutputs(subst("$0::getNumOutputs", fKlassName), true, true)->accept(&firvisitor);
    *dst << std::endl;
    generateGetInputRate(subst("$0::getInputRate", fKlassName), true, true)->accept(&firvisitor);
    *dst << std::endl;
    generateGetOutputRate(subst("$0::getOutputRate", fKlassName), true, true)->accept(&firvisitor);
    *dst << std::endl;
 
    if (fInitInstructions->fCode.size() > 0) {
        *dst << "======= Init ==========" << std::endl;
        *dst << std::endl;
        fInitInstructions->accept(&firvisitor);
        *dst << std::endl;
    }

    if (fStaticInitInstructions->fCode.size() > 0) {
        *dst << "======= Static Init ==========" << std::endl;
        *dst << std::endl;
        fStaticInitInstructions->accept(&firvisitor);
        if (fPostStaticInitInstructions->fCode.size() > 0) {
            fPostStaticInitInstructions->accept(&firvisitor);
        }
        *dst << std::endl;
    }

    if (fDestroyInstructions->fCode.size() > 0) {
        *dst << "======= Destroy ==========" << std::endl;
        *dst << std::endl;
        fDestroyInstructions->accept(&firvisitor);
        *dst << std::endl;
    }
    
    if (fAllocateInstructions->fCode.size() > 0) {
        *dst << "======= Allocate ==========" << std::endl;
        *dst << std::endl;
        fAllocateInstructions->accept(&firvisitor);
        *dst << std::endl;
    }
}

static void dumpCost(StatementInst* inst, ostream* dst)
{
    InstComplexityVisitor complexity;
    inst->accept(&complexity);
    complexity.dump(dst);
    *dst << std::endl;
}

void FirCodeContainer::dumpComputeBlock(FIRInstVisitor& firvisitor, ostream* dst)
{
    if (fComputeBlockInstructions->fCode.size() > 0) {
        *dst << "======= Compute Block ==========" << std::endl;
        // Complexity estimation
        dumpCost(fComputeBlockInstructions, dst);
        fComputeBlockInstructions->accept(&firvisitor);
        *dst << std::endl;
    }
}

void FirCodeContainer::dumpFlatten(ostream* dst)
{
    *dst << "======= Flatten FIR ==========" << std::endl;
    *dst << std::endl;
    FIRInstVisitor firvisitor(dst);
    flattenFIR()->accept(&firvisitor);
    *dst << std::endl;
}

void FirCodeContainer::dumpMemory(ostream* dst)
{
    // Compute memory footprint
    if (fTopLevel) {
    
        int total_heap_size = 0;
        list<CodeContainer*>::const_iterator it;
        
        for (it = fSubContainers.begin(); it != fSubContainers.end(); it++) {
            StackVariableSizeCounter heap_counter;
            (*it)->handleDeclarations(&heap_counter);
            total_heap_size += heap_counter.fSizeBytes;
        }
        
        StackVariableSizeCounter heap_counter;
        handleDeclarations(&heap_counter);
        
        StackVariableSizeCounter stack_counter;
        handleComputeBlock(&stack_counter);
        
        *dst << "======= Object memory footprint ==========" << std::endl << std::endl;
        *dst << "Heap size = " << heap_counter.fSizeBytes + total_heap_size << " bytes" << std::endl;
        *dst << "Stack size in compute = " << stack_counter.fSizeBytes << " bytes" << "\n\n";
    }
}

void FirCodeContainer::dump(ostream* dst)
{
    FIRInstVisitor firvisitor(dst);
    *dst << "======= Container \"" << fKlassName << "\" ==========" << std::endl;
    *dst << std::endl;
    dumpGlobalsAndInit(firvisitor, dst);
    dumpThread(firvisitor, dst);
    dumpComputeBlock(firvisitor, dst);
    dumpCompute(firvisitor, dst);
    
    dumpFlatten(dst);
    dumpMemory(dst);
    
    dst->flush();
}

void FirScalarCodeContainer::dumpCompute(FIRInstVisitor& firvisitor, ostream* dst)
{
    *dst << "======= Compute DSP ==========" << std::endl;
    ForLoopInst* loop = fCurLoop->generateScalarLoop("count");
    // Complexity estimation
    dumpCost(loop, dst);
    loop->accept(&firvisitor);
    *dst << std::endl;
}

void FirVectorCodeContainer::dumpCompute(FIRInstVisitor& firvisitor, ostream* dst)
{
    // Complexity estimation
    dumpCost(fDAGBlock, dst);
    // Generates DSP loop
    fDAGBlock->accept(&firvisitor);

    // Possibly generate separated functions
    if (fComputeFunctions->fCode.size() > 0) {
        *dst << std::endl;
        *dst << "======= Separated functions ==========" << std::endl;
        *dst << std::endl;
        // Complexity estimation
        dumpCost(fComputeFunctions, dst);
        fComputeFunctions->accept(&firvisitor);
        *dst << std::endl;
    } else {
        *dst << std::endl;
    }
}

void FirOpenMPCodeContainer::dumpCompute(FIRInstVisitor& firvisitor, ostream* dst)
{
    // Complexity estimation
    dumpCost(fGlobalLoopBlock, dst);
    // Generate it
    fGlobalLoopBlock->accept(&firvisitor);
 
    // Possibly generate separated functions
    if (fComputeFunctions->fCode.size() > 0) {
        *dst << std::endl;
        *dst << "======= Separated functions ==========" << std::endl;
        *dst << std::endl;
        // Complexity estimation
        dumpCost(fComputeFunctions, dst);
        fComputeFunctions->accept(&firvisitor);
        *dst << std::endl;
    }
}

void FirWorkStealingCodeContainer::dumpCompute(FIRInstVisitor& firvisitor, ostream* dst)
{
    // Possibly generate separated functions
    if (fComputeFunctions->fCode.size() > 0) {
        *dst << std::endl;
        *dst << "======= Separated functions ==========" << std::endl;
        *dst << std::endl;
        // Complexity estimation
        dumpCost(fComputeFunctions, dst);
        fComputeFunctions->accept(&firvisitor);
        *dst << std::endl;
    }
}

void FirWorkStealingCodeContainer::dumpMemory(ostream* dst)
{
    // Compute memory footprint
    if (fTopLevel) {
    
        int total_heap_size = 0;
        list<CodeContainer*>::const_iterator it;
        
        for (it = fSubContainers.begin(); it != fSubContainers.end(); it++) {
            StackVariableSizeCounter heap_counter;
            (*it)->handleDeclarations(&heap_counter);
            total_heap_size += heap_counter.fSizeBytes;
        }
        
        StackVariableSizeCounter heap_counter;
        handleDeclarations(&heap_counter);
        
        StackVariableSizeCounter stack_counter_compute;
        handleComputeBlock(&stack_counter_compute);
        
        StackVariableSizeCounter stack_counter_compute_thread;
        fComputeThreadBlockInstructions->accept(&stack_counter_compute_thread);
        
        *dst << "======= Object memory footprint ==========" << std::endl << std::endl;
        *dst << "Heap size = " << heap_counter.fSizeBytes + total_heap_size << " bytes" << std::endl;
        *dst << "Stack size in compute = " << stack_counter_compute.fSizeBytes << " bytes"<< std::endl;
        *dst << "Stack size in computeThread = " << stack_counter_compute_thread.fSizeBytes << " bytes" << "\n\n";
    }
}

void FirWorkStealingCodeContainer::dumpThread(FIRInstVisitor& firvisitor, ostream* dst)
{
    // Generate it
    *dst << "======= Compute Thread ==========" << std::endl;
    *dst << std::endl;
    // Complexity estimation
    dumpCost(fThreadLoopBlock, dst);
    fThreadLoopBlock->accept(&firvisitor);
    *dst << std::endl;
}
