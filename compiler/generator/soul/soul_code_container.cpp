/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
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

#include "soul_code_container.hh"
#include "global.hh"

using namespace std;

/*
 SOUL backend description:

 - sub-containers are compiled as 'struct' with associated functions
 - classInit is a Processor method for now (waiting for the SOUL external model to be ready)
 - 'boolean' type:
    - are casted to 'int' (for indexes...) and kept for tests (in SelectInst...).
    - 'int' results are casted to 'bool' for tests (in SelectInst...).
    - see the SOULInstVisitor fIntAsBool variable.
 - the 'fillXXX' function needs to generate the actual size of the table argument type. This is done using the
 TableSizeVisitor class.
*/

dsp_factory_base* SOULCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(
        fKlassName, "", "", ((static_cast<stringstream*>(fOut)) ? static_cast<stringstream*>(fOut)->str() : ""), "");
}

CodeContainer* SOULCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new SOULScalarCodeContainer(name, 0, 1, sub_container_type, fOut);
}

CodeContainer* SOULCodeContainer::createContainer(const string& name, int numInputs, int numOutputs, ostream* dst)
{
    CodeContainer* container;

    if (gGlobal->gOpenMPSwitch) {
        throw faustexception("ERROR : OpenMP not supported for SOUL\n");
    } else if (gGlobal->gSchedulerSwitch) {
        throw faustexception("ERROR : Scheduler not supported for SOUL\n");
    } else if (gGlobal->gVectorSwitch) {
        throw faustexception("ERROR : Vector mode not supported for SOUL\n");
        // container = new SOULVectorCodeContainer(name, numInputs, numOutputs, dst);
    } else {
        container = new SOULScalarCodeContainer(name, numInputs, numOutputs, kInt, dst);
    }

    return container;
}

void SOULCodeContainer::produceInternal()
{
    int                         n = 0;
    SOULSubContainerInstVisitor struct_visitor(fOut);

    // Global declarations
    generateGlobalDeclarations(&struct_visitor);

    tab(n + 1, *fOut);
    *fOut << "struct " << fKlassName;
    tab(n + 1, *fOut);
    *fOut << "{";
    tab(n + 2, *fOut);

    // Fields
    struct_visitor.Tab(n + 2);
    generateDeclarations(&struct_visitor);

    tab(n + 1, *fOut);
    *fOut << "}" << endl;

    // Inits
    tab(n + 1, *fOut);
    *fOut << "void instanceInit" << fKlassName << " (" << fKlassName << "& this, int sample_rate)";
    tab(n + 1, *fOut);
    *fOut << "{";
    tab(n + 2, *fOut);
    struct_visitor.Tab(n + 2);
    generateInit(&struct_visitor);
    generateResetUserInterface(&struct_visitor);
    generateClear(&struct_visitor);
    tab(n + 1, *fOut);
    *fOut << "}";

    // Fill
    string counter = "count";

    // Retrieves the table size kept in gTableSizeVisitor to generate the correct table type
    string fun_name = "fill" + fKlassName;
    // We possibly have to generate several versions of the function with a different table size
    for (auto& it : gGlobal->gTableSizeVisitor->fSizeTable) {
        string fun_name_aux = it.first;
        int    table_size   = it.second;
        if (startWith(fun_name_aux, fun_name)) {
            tab(n + 1, *fOut);
            if (fSubContainerType == kInt) {
                tab(n + 1, *fOut);
                *fOut << "void " << fun_name_aux << " (" << fKlassName << "& this, "
                      << subst("int $0, int[" + to_string(table_size) + "]& " + fTableName + ")", counter);
                tab(n + 1, *fOut);
                *fOut << "{";
            } else {
                tab(n + 1, *fOut);
                *fOut << "void " << fun_name_aux << " (" << fKlassName << "& this, "
                      << subst("int $0, $1[" + to_string(table_size) + "]& " + fTableName + ")", counter,
                               struct_visitor.getTypeManager()->fTypeDirectTable[itfloat()]);
                tab(n + 1, *fOut);
                *fOut << "{";
            }
            tab(n + 2, *fOut);
            struct_visitor.Tab(n + 2);
            generateComputeBlock(&struct_visitor);
            ForLoopInst* loop = fCurLoop->generateScalarLoop(counter);
            loop->accept(&struct_visitor);
            tab(n + 1, *fOut);
            *fOut << "}";
        }
    }

    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << fKlassName << " new" << fKlassName << "() { " << fKlassName << " obj; return obj; }";
    tab(n + 1, *fOut);
    *fOut << "void delete" << fKlassName << " (" << fKlassName << "& this) {}";
    tab(n + 1, *fOut);
}

void SOULCodeContainer::produceInit(int tabs)
{
    tab(tabs, *fOut);
    *fOut << "void init (int sample_rate)";
    tab(tabs, *fOut);
    *fOut << "{";
    tab(tabs + 1, *fOut);
    *fOut << "classInit (sample_rate);";
    tab(tabs + 1, *fOut);
    *fOut << "instanceInit (sample_rate);";
    tab(tabs, *fOut);
    *fOut << "}";
    tab(tabs, *fOut);

    tab(tabs, *fOut);
    *fOut << "void instanceInit (int sample_rate)";
    tab(tabs, *fOut);
    *fOut << "{";
    tab(tabs + 1, *fOut);
    *fOut << "instanceConstants (sample_rate);";
    tab(tabs + 1, *fOut);
    *fOut << "instanceResetUserInterface();";
    tab(tabs + 1, *fOut);
    *fOut << "instanceClear();";
    tab(tabs, *fOut);
    *fOut << "}";
    tab(tabs, *fOut);
}

void SOULCodeContainer::produceClass()
{
    int n = 0;

    // Look for the "fillXXX" function
    generateStaticInit(gGlobal->gTableSizeVisitor);
    generateInit(gGlobal->gTableSizeVisitor);

    // Processor generation
    tab(n, *fOut);
    *fOut << "processor " << fKlassName;
    tab(n, *fOut);
    *fOut << "{";

    // Fields
    tab(n + 1, *fOut);
    fCodeProducer.Tab(n + 1);
    SOULInstUIVisitor ui_visitor(n + 1);
    generateUserInterface(&ui_visitor);
    *fOut << ui_visitor.fOut.str();
    generateDeclarations(&fCodeProducer);

    // Control
    if (fComputeBlockInstructions->fCode.size() > 0) {
        *fOut << "bool fUpdated; ";
        tab(n + 1, *fOut);
    }

    // For control computation
    if (fInt32ControlNum > 0) {
        *fOut << "int32[" << fInt32ControlNum << "] icontrol;";
        tab(n + 1, *fOut);
    }
    if (fRealControlNum > 0) {
        *fOut << fCodeProducer.getTypeManager()->fTypeDirectTable[itfloat()] << "[" << fRealControlNum << "] fcontrol;";
    }

    // Global declarations
    if (fGlobalDeclarationInstructions->fCode.size() > 0) {
        tab(n + 1, *fOut);
        fCodeProducer.Tab(n + 1);
        generateGlobalDeclarations(&fCodeProducer);
    }

    // UI
    if (fUserInterfaceInstructions->fCode.size() > 0) {
        tab(n + 1, *fOut);
        fCodeProducer.Tab(n + 1);
        generateUserInterface(&fCodeProducer);
    }

    // Sub containers
    generateSubContainers();

    // inputs/outputs
    tab(n + 1, *fOut);
    *fOut << "int getNumInputs() { return " << fNumInputs << "; }";
    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << "int getNumOuputs() { return " << fNumOutputs << "; }";
    tab(n + 1, *fOut);

    tab(n + 1, *fOut);
    *fOut << "void classInit (int sample_rate)";
    tab(n + 1, *fOut);
    *fOut << "{";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    // Rename the 'fillXXX' function with the proper table size
    {
        TableSizeCloneVisitor fill_funcall;
        BlockInst*            block1 = fill_funcall.getCode(fStaticInitInstructions);
        block1->accept(&fCodeProducer);
        BlockInst* block2 = fill_funcall.getCode(fPostStaticInitInstructions);
        block2->accept(&fCodeProducer);
    }
    tab(n + 1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    tab(n + 1, *fOut);
    *fOut << "void instanceConstants (int sample_rate)";
    tab(n + 1, *fOut);
    *fOut << "{";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    // Rename the 'fillXXX' function with the proper table size
    {
        TableSizeCloneVisitor fill_funcall;
        BlockInst*            block1 = fill_funcall.getCode(fInitInstructions);
        block1->accept(&fCodeProducer);
        BlockInst* block2 = fill_funcall.getCode(fPostInitInstructions);
        block2->accept(&fCodeProducer);
    }
    tab(n + 1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    tab(n + 1, *fOut);
    *fOut << "void instanceResetUserInterface()";
    tab(n + 1, *fOut);
    *fOut << "{";
    tab(n + 2, *fOut);

    // Control
    if (fComputeBlockInstructions->fCode.size() > 0) {
        *fOut << "fUpdated = true;";
        tab(n + 2, *fOut);
    }

    fCodeProducer.Tab(n + 2);
    generateResetUserInterface(&fCodeProducer);
    tab(n + 1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    tab(n + 1, *fOut);
    *fOut << "void instanceClear()";
    tab(n + 1, *fOut);
    *fOut << "{";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateClear(&fCodeProducer);
    tab(n + 1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    // Init
    produceInit(n + 1);

    // Control
    if (fComputeBlockInstructions->fCode.size() > 0) {
        tab(n + 1, *fOut);
        *fOut << "void control()";
        tab(n + 1, *fOut);
        *fOut << "{";
        tab(n + 2, *fOut);
        fCodeProducer.Tab(n + 2);
        // Generates local variables declaration and setup
        generateComputeBlock(&fCodeProducer);
        tab(n + 1, *fOut);
        *fOut << "}" << endl;
    }

    // Compute
    generateCompute(n + 1);
    *fOut << "}" << endl;
}

void SOULScalarCodeContainer::generateCompute(int n)
{
    tab(n, *fOut);
    *fOut << "void run()";
    tab(n, *fOut);
    *fOut << "{";
    tab(n + 1, *fOut);
    *fOut << "// 'init' called once before starting the DSP loop";
    tab(n + 1, *fOut);
    *fOut << "init (int(processor.frequency));";

    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << "// DSP loop running forever...";
    tab(n + 1, *fOut);
    *fOut << "loop";
    tab(n + 1, *fOut);
    *fOut << "{";
    tab(n + 2, *fOut);

    if (fComputeBlockInstructions->fCode.size() > 0) {
        *fOut << "// Updates control only if needed";
        tab(n + 2, *fOut);
        *fOut << "if (fUpdated) { fUpdated = false; control(); }";
        tab(n + 2, *fOut);
        tab(n + 2, *fOut);
    }

    // Generates one sample computation
    fCodeProducer.Tab(n + 2);
    *fOut << "// Computes one sample";
    tab(n + 2, *fOut);
    BlockInst* block = fCurLoop->generateOneSample();
    block->accept(&fCodeProducer);

    // Currently for soundfile management
    generatePostComputeBlock(&fCodeProducer);

    tab(n + 2, *fOut);
    *fOut << "// Moves all streams forward by one 'tick'";
    tab(n + 2, *fOut);
    *fOut << "advance();";
    tab(n + 1, *fOut);
    *fOut << "}";

    tab(n, *fOut);
    *fOut << "}" << endl;
}

void SOULVectorCodeContainer::generateCompute(int n)
{
    tab(n, *fOut);
    *fOut << "void run()";
    tab(n, *fOut);
    *fOut << "{";
    tab(n + 1, *fOut);
    *fOut << "// 'init' called once before starting the DSP loop";
    tab(n + 1, *fOut);
    *fOut << "init (int(processor.frequency));";

    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << "// DSP loop running forever...";
    tab(n + 1, *fOut);
    *fOut << "loop";
    *fOut << "{";
    tab(n + 2, *fOut);

    if (fComputeBlockInstructions->fCode.size() > 0) {
        *fOut << "// Updates control only if needed";
        tab(n + 2, *fOut);
        *fOut << "if (fUpdated) { fUpdated = false; control(); }";
        tab(n + 2, *fOut);
        tab(n + 2, *fOut);
    }

    // TODO
    fCodeProducer.Tab(n + 2);

    tab(n + 2, *fOut);
    *fOut << "// Move all streams forward by one 'tick'";
    tab(n + 2, *fOut);
    *fOut << "advance();";
    tab(n + 1, *fOut);
    *fOut << "}";

    tab(n, *fOut);
    *fOut << "}" << endl;
}
