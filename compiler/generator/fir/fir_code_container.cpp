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
#include "fir_to_fir.hh"
#include "instructions_complexity.hh"
#include "global.hh"

using namespace std;

dsp_factory_base* FirCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(fKlassName, "", "",
                                    gGlobal->gReader.listSrcFiles(),
                                    ((dynamic_cast<std::stringstream*>(fOut)) ? dynamic_cast<std::stringstream*>(fOut)->str() : ""), "");
}

CodeContainer* FirCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new FirScalarCodeContainer(name, 0, 1, sub_container_type, fOut, false);
}

CodeContainer* FirCodeContainer::createContainer(const string& name, int numInputs, int numOutputs, ostream* dst, bool top_level)
{
    CodeContainer* container;

    if (gGlobal->gOpenMPSwitch) {
        container = new FirOpenMPCodeContainer(name, numInputs, numOutputs, dst, top_level);
    } else if (gGlobal->gSchedulerSwitch) {
        container = new FirWorkStealingCodeContainer(name, numInputs, numOutputs, dst, top_level);
    } else if (gGlobal->gVectorSwitch) {
        container = new FirVectorCodeContainer(name, numInputs, numOutputs, dst, top_level);
    } else {
        container = new FirScalarCodeContainer(name, numInputs, numOutputs, kInt, dst, top_level);
    }

    return container;
}

void FirCodeContainer::dumpUserInterface(FIRInstVisitor& firvisitor, ostream* dst)
{
    // User Interface
    if (fUserInterfaceInstructions->fCode.size() > 0) {
        *dst << "======= User Interface ==========" << std::endl;
        *dst << std::endl;
        fUserInterfaceInstructions->accept(&firvisitor);
        *dst << std::endl;
    }
}

void FirCodeContainer::dumpSubContainers(FIRInstVisitor& firvisitor, ostream* dst)
{
    list<CodeContainer*>::const_iterator it;
    *dst << "======= Sub container begin ==========" << std::endl << std::endl;
    for (it = fSubContainers.begin(); it != fSubContainers.end(); it++) {
        (*it)->produceInternal();
        (*it)->dump(dst);
    }
    *dst << "======= Sub container end ==========" << std::endl << std::endl;
}

void FirCodeContainer::dumpGlobalsAndInit(FIRInstVisitor& firvisitor, ostream* dst)
{
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
    
    generateGetInputs(subst("$0::getNumInputs", fKlassName), "dsp", true, true)->accept(&firvisitor);
    *dst << std::endl;
    generateGetOutputs(subst("$0::getNumOutputs", fKlassName), "dsp", true, true)->accept(&firvisitor);
    *dst << std::endl;
    generateGetInputRate(subst("$0::getInputRate", fKlassName), "dsp", true, true)->accept(&firvisitor);
    *dst << std::endl;
    generateGetOutputRate(subst("$0::getOutputRate", fKlassName), "dsp", true, true)->accept(&firvisitor);
    *dst << std::endl;
 
    if (fStaticInitInstructions->fCode.size() > 0) {
        *dst << "======= Static Init ==========" << std::endl;
        *dst << std::endl;
        fStaticInitInstructions->accept(&firvisitor);
        if (fPostStaticInitInstructions->fCode.size() > 0) {
            fPostStaticInitInstructions->accept(&firvisitor);
        }
        *dst << std::endl;
    }
    
    if (fInitInstructions->fCode.size() > 0) {
        *dst << "======= Init ==========" << std::endl;
        *dst << std::endl;
        fInitInstructions->accept(&firvisitor);
        *dst << std::endl;
    }
    
    if (fResetUserInterfaceInstructions->fCode.size() > 0) {
        *dst << "======= ResetUI ==========" << std::endl;
        *dst << std::endl;
        fResetUserInterfaceInstructions->accept(&firvisitor);
        *dst << std::endl;
    }

    if (fClearInstructions->fCode.size() > 0) {
        *dst << "======= Clear ==========" << std::endl;
        *dst << std::endl;
        fClearInstructions->accept(&firvisitor);
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
        *dst << "======= Compute control ==========" << std::endl << std::endl;
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
            VariableSizeCounter heap_counter(Address::AccessType(Address::kStruct | Address::kStaticStruct));
            (*it)->generateDeclarations(&heap_counter);
            total_heap_size += heap_counter.fSizeBytes;
        }
        
        VariableSizeCounter heap_counter1(Address::AccessType(Address::kStruct | Address::kStaticStruct), Typed::kInt32);
        generateDeclarations(&heap_counter1);
        
        VariableSizeCounter heap_counter2(Address::AccessType(Address::kStruct | Address::kStaticStruct), Typed::kInt32_ptr);
        generateDeclarations(&heap_counter2);
        
        VariableSizeCounter heap_counter3(Address::AccessType(Address::kStruct | Address::kStaticStruct));
        generateDeclarations(&heap_counter3);
        
        VariableSizeCounter stack_counter(Address::kStack);
        generateComputeBlock(&stack_counter);
        
        *dst << "======= Object memory footprint ==========" << std::endl << std::endl;
        *dst << "Heap size int = " << heap_counter1.fSizeBytes << " bytes" << std::endl;
        *dst << "Heap size int* = " << heap_counter2.fSizeBytes << " bytes" << std::endl;
        *dst << "Heap size real = " << heap_counter3.fSizeBytes - (heap_counter1.fSizeBytes + heap_counter2.fSizeBytes) << " bytes" << std::endl;
        *dst << "Heap size = " << heap_counter3.fSizeBytes + total_heap_size << " bytes" << std::endl;
        *dst << "Stack size in compute = " << stack_counter.fSizeBytes << " bytes" << "\n\n";
    }
}

void FirCodeContainer::produceInternal()
{
    FIRInstVisitor firvisitor(fOut);
    *fOut << "======= Sub container \"" << fKlassName << "\" ==========" << std::endl;
    *fOut << std::endl;
    
    dumpGlobalsAndInit(firvisitor, fOut);
    dumpComputeBlock(firvisitor, fOut);
    dumpCompute(firvisitor, fOut);
}

void FirCodeContainer::produceClass()
{
    FIRInstVisitor firvisitor(fOut);
    *fOut << "======= Container \"" << fKlassName << "\" ==========" << std::endl;
    *fOut << std::endl;
    
    *fOut << "======= External types declaration ==========" << std::endl;
    *fOut << std::endl;
    map<Typed::VarType, DeclareStructTypeInst*>::const_iterator it;
    for (it = gGlobal->gExternalStructTypes.begin(); it != gGlobal->gExternalStructTypes.end(); it++) {
        ((*it).second)->accept(&firvisitor);
        *fOut << std::endl;
    }
    *fOut << std::endl;
    
    dumpSubContainers(firvisitor, fOut);
    dumpUserInterface(firvisitor, fOut);
    dumpGlobalsAndInit(firvisitor, fOut);
    dumpThread(firvisitor, fOut);
    dumpComputeBlock(firvisitor, fOut);
    dumpCompute(firvisitor, fOut);
    dumpPostCompute(firvisitor, fOut);
    dumpFlatten(fOut);
    dumpMemory(fOut);
}

void FirCodeContainer::dumpPostCompute(FIRInstVisitor& firvisitor, ostream* dst)
{
    *dst << "======= Post compute DSP ==========" << std::endl;
    fPostComputeBlockInstructions->accept(&firvisitor);
    *dst << std::endl;
}

void FirScalarCodeContainer::dumpCompute(FIRInstVisitor& firvisitor, ostream* dst)
{
    *dst << "======= Compute DSP ==========" << std::endl;
    ForLoopInst* loop = fCurLoop->generateScalarLoop("count");
    // Complexity estimation
    dumpCost(loop, dst);
    loop->accept(&firvisitor);
    
    // Currently for soundfile management
    generatePostComputeBlock(&firvisitor);
    
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
            VariableSizeCounter heap_counter(Address::AccessType(Address::kStruct | Address::kStaticStruct));
            (*it)->generateDeclarations(&heap_counter);
            total_heap_size += heap_counter.fSizeBytes;
        }
        
        VariableSizeCounter heap_counter(Address::AccessType(Address::kStruct | Address::kStaticStruct));
        generateDeclarations(&heap_counter);
        
        VariableSizeCounter stack_counter_compute(Address::kStack);
        generateComputeBlock(&stack_counter_compute);
        
        VariableSizeCounter stack_counter_compute_thread(Address::kStack);
        fComputeThreadBlockInstructions->accept(&stack_counter_compute_thread);
        
        *dst << "======= Object memory footprint ==========\n\n";
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
