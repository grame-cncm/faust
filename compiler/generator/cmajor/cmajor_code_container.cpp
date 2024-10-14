/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
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

#include "cmajor_code_container.hh"
#include "global.hh"

using namespace std;

/*
 Cmajor backend description:

 - sub-containers are compiled as 'struct' with associated functions
 - classInit is a Processor method for now (waiting for the Cmajor external model to be ready)
 - 'faustpower' function fallbacks to regular 'pow' (see powprim.h)
 - the 'fillXXX' function needs to generate the actual size of the table argument type. This is done
 using the TableSizeVisitor class.
 - bargraphs use 'output event' type and are outputting values at 50 Hz. The code is conditionally
 generated.
*/

dsp_factory_base* CmajorCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(
        fKlassName, "", "",
        ((static_cast<ostringstream*>(fOut)) ? static_cast<ostringstream*>(fOut)->str() : ""), "");
}

CodeContainer* CmajorCodeContainer::createScalarContainer(const string& name,
                                                          int           sub_container_type)
{
    return new CmajorScalarCodeContainer(name, 0, 1, sub_container_type, fOut);
}

CodeContainer* CmajorCodeContainer::createContainer(const string& name, int numInputs,
                                                    int numOutputs, ostream* dst)
{
    if (isdigit(name[0])) {
        stringstream error;
        error << "ERROR : processor '" << name << "' cannot start with a digit\n";
        throw faustexception(error.str());
    }

    CodeContainer* container;

    if (gGlobal->gOpenMPSwitch) {
        throw faustexception("ERROR : OpenMP not supported for Cmajor\n");
    } else if (gGlobal->gSchedulerSwitch) {
        throw faustexception("ERROR : Scheduler not supported for Cmajor\n");
    } else if (gGlobal->gVectorSwitch) {
        throw faustexception("ERROR : Vector mode not supported for Cmajor\n");
        // container = new CmajorVectorCodeContainer(name, numInputs, numOutputs, dst);
    } else {
        container = new CmajorScalarCodeContainer(name, numInputs, numOutputs, kInt, dst);
    }

    return container;
}

void CmajorCodeContainer::produceInternal()
{
    int                           n = 1;
    CmajorSubContainerInstVisitor struct_visitor(fOut);

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

    back(1, *fOut);
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
    back(1, *fOut);
    *fOut << "}";

    // Fill
    string counter = "count";

    // Retrieves the table size kept in gTableSizeVisitor to generate the correct table type
    string fun_name = "fill" + fKlassName;
    // We possibly have to generate several versions of the function with a different table size
    for (const auto& it : gGlobal->gTableSizeVisitor->fSizeTable) {
        string fun_name_aux = it.first;
        int    table_size   = it.second;
        if (startWith(fun_name_aux, fun_name)) {
            tab(n + 1, *fOut);
            if (fSubContainerType == kInt) {
                tab(n + 1, *fOut);
                *fOut << "void " << fun_name_aux << " (" << fKlassName << "& this, "
                      << subst("int $0, int[" + to_string(table_size) + "]& " + fTableName + ")",
                               counter);
                tab(n + 1, *fOut);
                *fOut << "{";
            } else {
                tab(n + 1, *fOut);
                *fOut << "void " << fun_name_aux << " (" << fKlassName << "& this, "
                      << subst("int $0, $1[" + to_string(table_size) + "]& " + fTableName + ")",
                               counter,
                               struct_visitor.getTypeManager()->fTypeDirectTable[itfloat()]);
                tab(n + 1, *fOut);
                *fOut << "{";
            }
            tab(n + 2, *fOut);
            struct_visitor.Tab(n + 2);
            generateComputeBlock(&struct_visitor);
            ForLoopInst* loop = fCurLoop->generateScalarLoop(counter);
            loop->accept(&struct_visitor);
            back(1, *fOut);
            *fOut << "}";
        }
    }

    tab(n + 1, *fOut);
    *fOut << fKlassName << " new" << fKlassName << "() { " << fKlassName << " obj; return obj; }";
    tab(n + 1, *fOut);
    *fOut << "void delete" << fKlassName << " (" << fKlassName << "& this) {}";
    tab(n + 1, *fOut);
}

void CmajorCodeContainer::produceInit(int tabs)
{
    tab(tabs, *fOut);
    *fOut << "void init()";
    tab(tabs, *fOut);
    *fOut << "{";
    tab(tabs + 1, *fOut);
    *fOut << "let sample_rate = int(processor.frequency);";
    tab(tabs + 1, *fOut);
    if (fUIVisitor.fHasBargraph) {
        *fOut << "fControlSlice = int (processor.frequency) / 50;";
        tab(tabs + 1, *fOut);
    }
    *fOut << "// classInit is not called here since the tables are actually not shared between "
             "instances";
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
    *fOut << "// classInit has to be called for each instance since the tables are actually not "
             "shared between instances";
    tab(tabs + 1, *fOut);
    *fOut << "classInit (sample_rate);";
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

void CmajorCodeContainer::produceClass()
{
    int n = 1;

    // Start of namespace
    *fOut << "namespace faust \n{";
    fCodeProducer.Tab(n + 1);

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

    if (gGlobal->gOutputLang == "cmajor-dsp") {
        string json = generateJSONAux();
        *fOut << "// Event used to call additional methods";
        tab(n + 1, *fOut);
        *fOut << "input event int eventbuildUserInterface [[json: \"" << flattenJSON(json)
              << "\"]];";
        tab(n + 1, *fOut);
        *fOut << "input event int eventclassInit;";
        tab(n + 1, *fOut);
        *fOut << "input event int eventinstanceConstants;";
        tab(n + 1, *fOut);
        *fOut << "input event int eventinstanceResetUserInterface;";
        tab(n + 1, *fOut);
        *fOut << "input event int eventinstanceClear;";
        tab(n + 1, *fOut);
        tab(n + 1, *fOut);
    }

    fUIVisitor.Tab(n + 1);
    // First pass to build shortnames
    generateUserInterface(&fUIVisitor);
    // Second pass to generate
    generateUserInterface(&fUIVisitor);
    *fOut << fUIVisitor.fOut.str();
    generateDeclarations(&fCodeProducer);

    // Control
    *fOut << "bool fUpdated;";
    tab(n + 1, *fOut);
    if (fUIVisitor.fHasBargraph) {
        *fOut << "int fControlSlice;";
        tab(n + 1, *fOut);
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
        // First pass to build shortnames
        generateUserInterface(&fCodeProducer);
        // Second pass to generate
        generateUserInterface(&fCodeProducer);
    }

    /*
    // Debug version
    if (gGlobal->gOutputLang == "cmajor-dsp") {
        *fOut << "// Event handler used to call additional methods";
        tab(n + 1, *fOut);
        *fOut << "event eventbuildUserInterface (int dummy) { console <<
    \"eventbuildUserInterface\n\"; }"; tab(n + 1, *fOut); *fOut << "event eventclassInit (int
    sample_rate) { console << \"eventclassInit\n\"; classInit(sample_rate); }"; tab(n + 1, *fOut);
        *fOut << "event eventinstanceConstants (int sample_rate) { console <<
    \"eventinstanceConstants\n\"; instanceConstants(sample_rate); }"; tab(n + 1, *fOut); *fOut <<
    "event eventinstanceResetUserInterface (int dummy) { console <<
    \"eventinstanceResetUserInterface\n\"; instanceResetUserInterface(); }"; tab(n + 1, *fOut);
        *fOut << "event eventinstanceClear (int dummy) { console << \"eventinstanceClear\n\";
    instanceClear(); }"; tab(n + 1, *fOut); tab(n + 1, *fOut);
    }
    */

    if (gGlobal->gOutputLang == "cmajor-dsp") {
        *fOut << "// Event handler used to call additional methods";
        tab(n + 1, *fOut);
        *fOut << "event eventbuildUserInterface (int dummy) {}";
        tab(n + 1, *fOut);
        *fOut << "event eventclassInit (int sample_rate) { classInit(sample_rate); }";
        tab(n + 1, *fOut);
        *fOut
            << "event eventinstanceConstants (int sample_rate) { instanceConstants(sample_rate); }";
        tab(n + 1, *fOut);
        *fOut << "event eventinstanceResetUserInterface (int dummy) { "
                 "instanceResetUserInterface(); }";
        tab(n + 1, *fOut);
        *fOut << "event eventinstanceClear (int dummy) { instanceClear(); }";
        tab(n + 1, *fOut);
        tab(n + 1, *fOut);
    }

    // Generate gub containers
    generateSubContainers();

    // Missing math functions
    tab(n + 1, *fOut);
    if (gGlobal->gFloatSize == 1) {
        *fOut << "float32 copysign(float32 x, float32 y) { return abs(x) * ((y < 0.0f) ? -1.0f : "
                 "1.0f); }";
        tab(n + 1, *fOut);
        *fOut << "float32 round(float32 x) { return float32(roundToInt(x)); }";
    } else if (gGlobal->gFloatSize == 2) {
        *fOut << "float64 copysign(float64 x, float64 y) { return abs(x) * ((y < 0.0) ? -1.0 : "
                 "1.0); }";
        tab(n + 1, *fOut);
        *fOut << "float64 round(float64 x) { return float64(roundToInt(x)); }";
    }
    tab(n + 1, *fOut);

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
    back(1, *fOut);
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
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    tab(n + 1, *fOut);
    *fOut << "void instanceResetUserInterface()";
    tab(n + 1, *fOut);
    *fOut << "{";
    tab(n + 2, *fOut);

    // Control
    *fOut << "fUpdated = true;";
    tab(n + 2, *fOut);

    fCodeProducer.Tab(n + 2);
    generateResetUserInterface(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    tab(n + 1, *fOut);
    *fOut << "void instanceClear()";
    tab(n + 1, *fOut);
    *fOut << "{";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateClear(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    // Init
    produceInit(n + 1);

    // Control
    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << "void control()";
    tab(n + 1, *fOut);
    *fOut << "{";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    // First generate values (for bargraph)
    generateComputeBlock(&fCodeProducer);
    // Then generate iSlow/fSlow variables
    generateControlDeclarations(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}" << endl;

    // Compute
    generateCompute(n + 1);
    back(1, *fOut);
    tab(n, *fOut);
    *fOut << "}" << endl;

    // End of namespace
    *fOut << "}" << endl;
}

void CmajorScalarCodeContainer::generateCompute(int n)
{
    tab(n, *fOut);
    *fOut << "void main()";
    tab(n, *fOut);
    *fOut << "{";
    tab(n + 1, *fOut);
    *fOut << "// DSP loop running forever...";
    tab(n + 1, *fOut);
    *fOut << "loop";
    tab(n + 1, *fOut);
    *fOut << "{";
    tab(n + 2, *fOut);
    *fOut << "if (fUpdated) { fUpdated = false; control(); }";
    tab(n + 2, *fOut);
    tab(n + 2, *fOut);

    // Generates one sample computation
    fCodeProducer.Tab(n + 2);
    *fOut << "// Computes one sample";
    tab(n + 2, *fOut);
    BlockInst* block = fCurLoop->generateOneSample();
    block->accept(&fCodeProducer);

    // Currently for soundfile management
    generatePostComputeBlock(&fCodeProducer);

    tab(n + 2, *fOut);
    if (fUIVisitor.fHasBargraph) {
        *fOut << "// Updates fControlSlice once per sample";
        tab(n + 2, *fOut);
        *fOut << "if (fControlSlice-- == 0) { fControlSlice = int (processor.frequency) / 50; }";
        tab(n + 2, *fOut);
    }
    *fOut << "// Moves all streams forward by one 'tick'";
    tab(n + 2, *fOut);
    *fOut << "advance();";
    tab(n + 1, *fOut);
    *fOut << "}";

    tab(n, *fOut);
    *fOut << "}" << endl;
}

void CmajorVectorCodeContainer::generateCompute(int n)
{
    tab(n, *fOut);
    *fOut << "void main()";
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

    tab(n + 2, *fOut);
    *fOut << "if (fUpdated) { fUpdated = false; control(); }";
    tab(n + 2, *fOut);
    tab(n + 2, *fOut);

    // TODO
    fCodeProducer.Tab(n + 2);

    tab(n + 2, *fOut);
    *fOut << "// Move all streams forward by one 'tick'";
    tab(n + 2, *fOut);
    *fOut << "advance();";
    tab(n + 1, *fOut);
    *fOut << "}";

    tab(n, *fOut);
    *fOut << "}" << endl << endl;
}
