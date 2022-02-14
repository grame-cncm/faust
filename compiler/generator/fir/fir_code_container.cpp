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

#include "fir_code_container.hh"
#include "fir_to_fir.hh"
#include "global.hh"
#include "instructions_complexity.hh"
#include "struct_manager.hh"

using namespace std;

dsp_factory_base* FIRCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(
        fKlassName, "", "", ((static_cast<ostringstream*>(fOut)) ? static_cast<ostringstream*>(fOut)->str() : ""), "");
}

CodeContainer* FIRCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new FIRScalarCodeContainer(name, 0, 1, sub_container_type, fOut, false);
}

CodeContainer* FIRCodeContainer::createContainer(const string& name, int numInputs, int numOutputs, ostream* dst,
                                                 bool top_level)
{
    CodeContainer* container;

    if (gGlobal->gOpenMPSwitch) {
        container = new FIROpenMPCodeContainer(name, numInputs, numOutputs, dst, top_level);
    } else if (gGlobal->gSchedulerSwitch) {
        container = new FIRWorkStealingCodeContainer(name, numInputs, numOutputs, dst, top_level);
    } else if (gGlobal->gVectorSwitch) {
        container = new FIRVectorCodeContainer(name, numInputs, numOutputs, dst, top_level);
    } else {
        container = new FIRScalarCodeContainer(name, numInputs, numOutputs, kInt, dst, top_level);
    }

    return container;
}

void FIRCodeContainer::dumpUserInterface(FIRInstVisitor& firvisitor, ostream* dst)
{
    // User Interface
    if (fUserInterfaceInstructions->fCode.size() > 0) {
        *dst << "======= User Interface begin ==========" << endl << endl;
        fUserInterfaceInstructions->accept(&firvisitor);
        *dst << endl << "======= User Interface end ==========" << endl << endl;
    }
}

void FIRCodeContainer::dumpSubContainers(FIRInstVisitor& firvisitor, ostream* dst)
{
    *dst << "======= Sub container begin ==========" << endl << endl;
    for (const auto& it : fSubContainers) {
        it->produceInternal();
        it->dump(dst);
    }
    *dst << "======= Sub container end ==========" << endl << endl;
}

void FIRCodeContainer::dumpGlobalsAndInit(FIRInstVisitor& firvisitor, ostream* dst)
{
    if (fExtGlobalDeclarationInstructions->fCode.size() > 0) {
        *dst << "======= Global external declarations begin ==========" << endl << endl;
        fExtGlobalDeclarationInstructions->accept(&firvisitor);
        *dst << endl << "======= Global external declarations end ==========" << endl << endl;
    }

    if (fGlobalDeclarationInstructions->fCode.size() > 0) {
        *dst << "======= Global declarations begin ==========" << endl << endl;
        fGlobalDeclarationInstructions->accept(&firvisitor);
        *dst << endl << "======= Global declarations end ==========" << endl << endl;
    }

    if (fDeclarationInstructions->fCode.size() > 0) {
        *dst << "======= DSP struct begin ==========" << endl << endl;
        StructInstVisitor visitor;
        fDeclarationInstructions->accept(&visitor);
        visitor.getStructType(fKlassName)->accept(&firvisitor);
        *dst << endl << "======= DSP struct end ==========" << endl << endl;
    }

    generateGetInputs(subst("$0::getNumInputs", fKlassName), "dsp", true, true)->accept(&firvisitor);
    *dst << endl;
    generateGetOutputs(subst("$0::getNumOutputs", fKlassName), "dsp", true, true)->accept(&firvisitor);
    *dst << endl;
   
    if (fStaticInitInstructions->fCode.size() > 0) {
        *dst << "======= Static Init begin ==========" << endl << endl;
        fStaticInitInstructions->accept(&firvisitor);
        if (fPostStaticInitInstructions->fCode.size() > 0) {
            fPostStaticInitInstructions->accept(&firvisitor);
        }
        *dst << endl << "======= Static Init end ==========" << endl << endl;
    }

    if (fInitInstructions->fCode.size() > 0) {
        *dst << "======= Init begin ==========" << endl << endl;
        fInitInstructions->accept(&firvisitor);
        *dst << endl << "======= Init end ==========" << endl << endl;
    }

    if (fResetUserInterfaceInstructions->fCode.size() > 0) {
        *dst << "======= ResetUI begin ==========" << endl << endl;
        fResetUserInterfaceInstructions->accept(&firvisitor);
        *dst << endl << "======= ResetUI end ==========" << endl << endl;
    }

    if (fClearInstructions->fCode.size() > 0) {
        *dst << "======= Clear begin ==========" << endl << endl;
        fClearInstructions->accept(&firvisitor);
        *dst << endl << "======= Clear end ==========" << endl << endl;
    }

    if (fDestroyInstructions->fCode.size() > 0) {
        *dst << "======= Destroy begin ==========" << endl << endl;
        fDestroyInstructions->accept(&firvisitor);
        *dst << endl << "======= Destroy end ==========" << endl << endl;
    }

    if (fAllocateInstructions->fCode.size() > 0) {
        *dst << "======= Allocate begin ==========" << endl << endl;
        fAllocateInstructions->accept(&firvisitor);
        *dst << endl << "======= Allocate end ==========" << endl << endl;
    }
}

static void dumpCost(StatementInst* inst, ostream* dst)
{
    InstComplexityVisitor complexity;
    inst->accept(&complexity);
    complexity.dump(dst);
    *dst << endl;
}

void FIRCodeContainer::dumpComputeBlock(FIRInstVisitor& firvisitor, ostream* dst)
{
    if (fComputeBlockInstructions->fCode.size() > 0) {
        *dst << "======= Compute control begin ==========" << endl << endl;
        // Complexity estimation
        dumpCost(fComputeBlockInstructions, dst);
        fComputeBlockInstructions->accept(&firvisitor);
        *dst << endl << "======= Compute control end ==========" << endl << endl;
    }
}

void FIRCodeContainer::dumpFlatten(ostream* dst)
{
    *dst << "======= Flatten FIR begin ==========" << endl << endl;
    FIRInstVisitor firvisitor(dst);
    flattenFIR()->accept(&firvisitor);
    *dst << endl << "======= Flatten FIR end ==========" << endl << endl;
}

void FIRCodeContainer::dumpMemory(ostream* dst)
{
    // Compute memory footprint
    if (fTopLevel) {
        int total_heap_size = 0;
        for (const auto& it : fSubContainers) {
            VariableSizeCounter heap_counter(Address::AccessType(Address::kStruct | Address::kStaticStruct));
            it->generateDeclarations(&heap_counter);
            total_heap_size += heap_counter.fSizeBytes;
        }

        VariableSizeCounter heap_counter1(Address::AccessType(Address::kStruct | Address::kStaticStruct),
                                          Typed::kInt32);
        generateDeclarations(&heap_counter1);

        VariableSizeCounter heap_counter2(Address::AccessType(Address::kStruct | Address::kStaticStruct),
                                          Typed::kInt32_ptr);
        generateDeclarations(&heap_counter2);

        VariableSizeCounter heap_counter3(Address::AccessType(Address::kStruct | Address::kStaticStruct));
        generateDeclarations(&heap_counter3);

        VariableSizeCounter stack_counter(Address::kStack);
        generateComputeBlock(&stack_counter);

        *dst << "======= Object memory footprint ==========" << endl << endl;
        *dst << "Heap size int = " << heap_counter1.fSizeBytes << " bytes" << endl;
        *dst << "Heap size int* = " << heap_counter2.fSizeBytes << " bytes" << endl;
        *dst << "Heap size real = " << heap_counter3.fSizeBytes - (heap_counter1.fSizeBytes + heap_counter2.fSizeBytes)
             << " bytes" << endl;
        *dst << "Total heap size = " << heap_counter3.fSizeBytes + total_heap_size << " bytes" << endl;
        *dst << "Stack size in compute = " << stack_counter.fSizeBytes << " bytes"
             << "\n\n";
        
        *dst << "======= Variable access in compute control ==========" << endl << endl;
        {
            StructInstVisitor struct_visitor;
            fDeclarationInstructions->accept(&struct_visitor);
            fComputeBlockInstructions->accept(&struct_visitor);
            
            for (const auto& it : struct_visitor.getFieldTable()) {
                *dst << "Field = " << it.first << " size = " << it.second.fSize;
                *dst << " r_count = " << it.second.fRAccessCount;
                *dst << " w_count = " << it.second.fWAccessCount;
                *dst << " ratio = " << float(it.second.fRAccessCount + it.second.fWAccessCount) / float(it.second.fSize) << endl;
            }
        }
        
        *dst << endl << "======= Variable access in compute DSP ==========" << endl << endl;
        {
            StructInstVisitor struct_visitor;
            fDeclarationInstructions->accept(&struct_visitor);
            
            ForLoopInst* loop = fCurLoop->generateScalarLoop("count");
            loop->accept(&struct_visitor);
            
            for (const auto& it : struct_visitor.getFieldTable()) {
                *dst << "Field = " << it.first << " size = " << it.second.fSize;
                *dst << " r_count = " << it.second.fRAccessCount;
                *dst << " w_count = " << it.second.fWAccessCount;
                *dst << " ratio = " << float(it.second.fRAccessCount + it.second.fWAccessCount) / float(it.second.fSize) << endl;
            }
        }
    }
}

void FIRCodeContainer::produceInternal()
{
    FIRInstVisitor firvisitor(fOut);
    *fOut << "======= Sub container \"" << fKlassName << "\" ==========" << endl;
    *fOut << endl;

    dumpGlobalsAndInit(firvisitor, fOut);
    dumpComputeBlock(firvisitor, fOut);
    dumpCompute(firvisitor, fOut);
}

void FIRCodeContainer::produceClass()
{
    FIRInstVisitor firvisitor(fOut);
    *fOut << "======= Container \"" << fKlassName << "\" ==========" << endl;
    *fOut << endl;

    *fOut << "======= External types declaration ==========" << endl;
    *fOut << endl;
    for (const auto& it : gGlobal->gExternalStructTypes) {
        (it.second)->accept(&firvisitor);
        *fOut << endl;
    }
   
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

void FIRCodeContainer::dumpPostCompute(FIRInstVisitor& firvisitor, ostream* dst)
{
    *dst << "======= Post compute DSP begin ==========" << endl << endl;
    fPostComputeBlockInstructions->accept(&firvisitor);
    *dst << endl << "======= Post compute DSP end ==========" << endl << endl;
}

void FIRScalarCodeContainer::dumpCompute(FIRInstVisitor& firvisitor, ostream* dst)
{
    *dst << "======= Compute DSP begin ==========" << endl << endl;
    ForLoopInst* loop = fCurLoop->generateScalarLoop("count");
    // Complexity estimation
    dumpCost(loop, dst);
    loop->accept(&firvisitor);
    // Currently for soundfile management
    generatePostComputeBlock(&firvisitor);
    *dst << endl << "======= Compute DSP end ==========" << endl << endl;
}

void FIRVectorCodeContainer::dumpCompute(FIRInstVisitor& firvisitor, ostream* dst)
{
    *dst << "======= Compute DSP begin ==========" << endl << endl;
    // Complexity estimation
    dumpCost(fDAGBlock, dst);
    // Generates the DSP loop
    fDAGBlock->accept(&firvisitor);
    *dst << endl << "======= Compute DSP end ==========" << endl << endl;

    // Possibly generate separated functions
    if (fComputeFunctions->fCode.size() > 0) {
        *dst << "======= Separated functions begin ==========" << endl;
        *dst << endl;
        // Complexity estimation
        dumpCost(fComputeFunctions, dst);
        fComputeFunctions->accept(&firvisitor);
        *dst << endl << "======= Separated functions end ==========" << endl << endl;
    }
}

void FIROpenMPCodeContainer::dumpCompute(FIRInstVisitor& firvisitor, ostream* dst)
{
    *dst << "======= Compute DSP begin ==========" << endl << endl;
    // Complexity estimation
    dumpCost(fGlobalLoopBlock, dst);
    // Generate it
    fGlobalLoopBlock->accept(&firvisitor);
    *dst << endl << "======= Compute DSP end ==========" << endl << endl;

    // Possibly generate separated functions
    if (fComputeFunctions->fCode.size() > 0) {
        *dst << "======= Separated functions begin ==========" << endl;
        *dst << endl;
        // Complexity estimation
        dumpCost(fComputeFunctions, dst);
        fComputeFunctions->accept(&firvisitor);
        *dst << endl << "======= Separated functions end ==========" << endl << endl;
    }
}

void FIRWorkStealingCodeContainer::dumpCompute(FIRInstVisitor& firvisitor, ostream* dst)
{
    // Possibly generate separated functions
    if (fComputeFunctions->fCode.size() > 0) {
        *dst << "======= Separated functions begin ==========" << endl;
        *dst << endl;
        // Complexity estimation
        dumpCost(fComputeFunctions, dst);
        fComputeFunctions->accept(&firvisitor);
        *dst << endl << "======= Separated functions end ==========" << endl << endl;
    }
}

void FIRWorkStealingCodeContainer::dumpMemory(ostream* dst)
{
    // Compute memory footprint
    if (fTopLevel) {
        int total_heap_size = 0;
        for (const auto& it : fSubContainers) {
            VariableSizeCounter heap_counter(Address::AccessType(Address::kStruct | Address::kStaticStruct));
            it->generateDeclarations(&heap_counter);
            total_heap_size += heap_counter.fSizeBytes;
        }

        VariableSizeCounter heap_counter(Address::AccessType(Address::kStruct | Address::kStaticStruct));
        generateDeclarations(&heap_counter);

        VariableSizeCounter stack_counter_compute(Address::kStack);
        generateComputeBlock(&stack_counter_compute);

        VariableSizeCounter stack_counter_compute_thread(Address::kStack);
        fComputeThreadBlockInstructions->accept(&stack_counter_compute_thread);

        *dst << "======= Object memory footprint ==========\n\n";
        *dst << "Total heap size = " << heap_counter.fSizeBytes + total_heap_size << " bytes" << endl;
        *dst << "Stack size in compute = " << stack_counter_compute.fSizeBytes << " bytes" << endl;
        *dst << "Stack size in computeThread = " << stack_counter_compute_thread.fSizeBytes << " bytes"
             << "\n\n";
    }
}

void FIRWorkStealingCodeContainer::dumpThread(FIRInstVisitor& firvisitor, ostream* dst)
{
    // Generate it
    *dst << "======= Compute Thread begin ==========" << endl << endl;
    // Complexity estimation
    dumpCost(fThreadLoopBlock, dst);
    fThreadLoopBlock->accept(&firvisitor);
    *dst << endl << "======= Compute Thread end ==========" << endl << endl;
}
