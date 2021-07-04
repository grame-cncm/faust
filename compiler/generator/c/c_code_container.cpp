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

#include "c_code_container.hh"
#include "Text.hh"
#include "exception.hh"
#include "fir_function_builder.hh"
#include "floats.hh"
#include "global.hh"

using namespace std;

/*
 C backend and module description:
 - in -os mode, CScalarOneSampleCodeContainer2 separates part of the DSP state in iZone and fZone (possibly to be allocated elsewhere)
*/

map<string, bool> CInstVisitor::gFunctionSymbolTable;

dsp_factory_base* CCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(
        fKlassName, "", "",
        ((dynamic_cast<ostringstream*>(fOut)) ? dynamic_cast<ostringstream*>(fOut)->str() : ""), "");
}

CodeContainer* CCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    if (gGlobal->gOneSample == 0) {
        return new CScalarOneSampleCodeContainer1(name, 0, 1, fOut, sub_container_type);
    } else if (gGlobal->gOneSample == 1) {
        return new CScalarOneSampleCodeContainer2(name, 0, 1, fOut, sub_container_type);
    } else {
        return new CScalarCodeContainer(name, 0, 1, fOut, sub_container_type);
    }
}

CodeContainer* CCodeContainer::createContainer(const string& name, int numInputs, int numOutputs, ostream* dst)
{
    gGlobal->gDSPStruct = true;
    CodeContainer* container;

    if (gGlobal->gOpenCLSwitch) {
        throw faustexception("ERROR : OpenCL not supported for C\n");
    }
    if (gGlobal->gCUDASwitch) {
        throw faustexception("ERROR : CUDA not supported for C\n");
    }

    if (gGlobal->gOpenMPSwitch) {
        container = new COpenMPCodeContainer(name, numInputs, numOutputs, dst);
    } else if (gGlobal->gSchedulerSwitch) {
        container = new CWorkStealingCodeContainer(name, numInputs, numOutputs, dst);
    } else if (gGlobal->gVectorSwitch) {
        container = new CVectorCodeContainer(name, numInputs, numOutputs, dst);
    } else {
        if (gGlobal->gOneSample == 0) {
            container = new CScalarOneSampleCodeContainer1(name, numInputs, numOutputs, dst, kInt);
        } else if (gGlobal->gOneSample == 1) {
            container = new CScalarOneSampleCodeContainer2(name, numInputs, numOutputs, dst, kInt);
        } else {
            container = new CScalarCodeContainer(name, numInputs, numOutputs, dst, kInt);
        }
    }

    return container;
}

void CCodeContainer::produceInternal()
{
    int n = 0;

    // Global declarations
    tab(n, *fOut);
    fCodeProducer->Tab(n);
    generateGlobalDeclarations(fCodeProducer);

    *fOut << "typedef struct {";

    tab(n + 1, *fOut);
 
    // Fields
    fCodeProducer->Tab(n + 1);
    generateDeclarations(fCodeProducer);

    back(1, *fOut);
    *fOut << "} " << fKlassName << ";";

    if (!gGlobal->gLightMode) {
        // Memory methods
        tab(n, *fOut);
        tab(n, *fOut);
        *fOut << "static " << fKlassName << "* new" << fKlassName << "() {"
              << " return (" << fKlassName << "*)calloc(1, sizeof(" << fKlassName << ")); }";

        tab(n, *fOut);
        *fOut << "static void delete" << fKlassName << "(" << fKlassName << "* dsp) { free(dsp); }";

        tab(n, *fOut);
        tab(n, *fOut);
    }
    produceInfoFunctions(n, fKlassName, "dsp", false, false, fCodeProducer);

    // Init
    // TODO
    // generateInstanceInitFun("instanceInit" + fKlassName, false, false)->accept(fCodeProducer);

    tab(n, *fOut);
    *fOut << "static void instanceInit" << fKlassName << "(" << fKlassName << "* dsp, int sample_rate) {";
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);
    generateInit(fCodeProducer);
    generateResetUserInterface(fCodeProducer);
    generateClear(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";

    // Fill
    tab(n, *fOut);
    string counter = "count";
    if (fSubContainerType == kInt) {
        tab(n, *fOut);
        *fOut << "static void fill" << fKlassName << "(" << fKlassName
              << subst("* dsp, int $0, int* " + fTableName + ") {", counter);
    } else {
        tab(n, *fOut);
        *fOut << "static void fill" << fKlassName << "(" << fKlassName
              << subst("* dsp, int $0, $1* " + fTableName + ") {", counter, ifloat());
    }
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);
    generateComputeBlock(fCodeProducer);
    ForLoopInst* loop = fCurLoop->generateScalarLoop(counter);
    loop->accept(fCodeProducer);

    back(1, *fOut);
    *fOut << "}" << endl;
}

void CCodeContainer::produceClass()
{
    int n = 0;

    tab(n, *fOut);
    *fOut << "#ifdef __cplusplus" << endl;
    *fOut << "extern \"C\" {" << endl;
    *fOut << "#endif" << endl;
    tab(n, *fOut);
  
    // Libraries
    printLibrary(*fOut);
    printIncludeFile(*fOut);

    // Sub containers
    generateSubContainers();

    // Functions
    tab(n, *fOut);
    fCodeProducer->Tab(n);
    generateGlobalDeclarations(fCodeProducer);

    tab(n, *fOut);
    *fOut << "#ifndef FAUSTCLASS " << endl;
    *fOut << "#define FAUSTCLASS " << fKlassName << endl;
    *fOut << "#endif" << endl;

    *fOut << "#ifdef __APPLE__ " << endl;
    *fOut << "#define exp10f __exp10f" << endl;
    *fOut << "#define exp10 __exp10" << endl;
    *fOut << "#endif" << endl;

    if (gGlobal->gLightMode) {
        tab(n, *fOut);
        *fOut << "#define max(a,b) ((a < b) ? b : a)\n";
        *fOut << "#define min(a,b) ((a < b) ? a : b)\n";
        tab(n, *fOut);
    }
 
    tab(n, *fOut);
    *fOut << "typedef struct {";
    tab(n + 1, *fOut);
 
    // Fields
    fCodeProducer->Tab(n + 1);
    generateDeclarations(fCodeProducer);
    back(1, *fOut);
    *fOut << "} " << fKlassName << ";";

    // Memory methods
    tab(n, *fOut);
    if (!gGlobal->gLightMode) {
        
        if (fAllocateInstructions->fCode.size() > 0) {
            tab(n, *fOut);
            *fOut << "static void allocate" << fKlassName << "(" << fKlassName << "* dsp) {";
            tab(n + 1, *fOut);
            generateAllocate(fCodeProducer);
            back(1, *fOut);
            *fOut << "}";
        }
        tab(n, *fOut);

        if (fDestroyInstructions->fCode.size() > 0) {
            tab(n, *fOut);
            *fOut << "static void destroy" << fKlassName << "(" << fKlassName << "* dsp) {";
            tab(n + 1, *fOut);
            generateDestroy(fCodeProducer);
            back(1, *fOut);
            *fOut << "}";
            tab(n, *fOut);
        }

        *fOut << fKlassName << "* new" << fKlassName << "() { ";
        tab(n + 1, *fOut);
        *fOut << fKlassName << "* dsp = (" << fKlassName << "*)calloc(1, sizeof(" << fKlassName << "));";
        if (fAllocateInstructions->fCode.size() > 0) {
            tab(n + 1, *fOut);
            *fOut << "allocate" << fKlassName << "(dsp);";
        }
        tab(n + 1, *fOut);
        *fOut << "return dsp;";
        tab(n, *fOut);
        *fOut << "}";

        tab(n, *fOut);
        tab(n, *fOut);
        *fOut << "void delete" << fKlassName << "(" << fKlassName << "* dsp) { ";
        if (fDestroyInstructions->fCode.size() > 0) {
            tab(n + 1, *fOut);
            *fOut << "destroy" << fKlassName << "(dsp);";
        }
        tab(n + 1, *fOut);
        *fOut << "free(dsp);";
        tab(n, *fOut);
        *fOut << "}";

        // Print metadata declaration
        tab(n, *fOut);
        produceMetadata(n);
    }

    // Get sample rate method
    tab(n, *fOut);
    fCodeProducer->Tab(n);
    generateGetSampleRate("getSampleRate" + fKlassName, "dsp", false, false)->accept(fCodeProducer);
  
    tab(n, *fOut);
    produceInfoFunctions(n, fKlassName, "dsp", false, false, fCodeProducer);

    // Inits

    // TODO
    /*
     CInstVisitor codeproducer1(fOut, "");
     codeproducer1.Tab(n+1);
     generateStaticInitFun("classInit" + fKlassName, false)->accept(&codeproducer1);
     generateInstanceInitFun("instanceInit" + fKlassName, false, false)->accept(&codeproducer2);
     */

    tab(n, *fOut);
    *fOut << "void classInit" << fKlassName << "(int sample_rate) {";
    {
        tab(n + 1, *fOut);
        // Local visitor here to avoid DSP object incorrect type generation
        CInstVisitor codeproducer(fOut, "");
        codeproducer.Tab(n + 1);
        generateStaticInit(&codeproducer);
    }
    back(1, *fOut);
    *fOut << "}";

    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "void instanceResetUserInterface" << fKlassName << "(" << fKlassName << "* dsp) {";
    {
        tab(n + 1, *fOut);
        // Local visitor here to avoid DSP object incorrect type generation
        CInstVisitor codeproducer(fOut, "");
        codeproducer.Tab(n + 1);
        generateResetUserInterface(&codeproducer);
    }
    back(1, *fOut);
    *fOut << "}";

    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "void instanceClear" << fKlassName << "(" << fKlassName << "* dsp) {";
    {
        tab(n + 1, *fOut);
        // Local visitor here to avoid DSP object incorrect type generation
        CInstVisitor codeproducer(fOut, "");
        codeproducer.Tab(n + 1);
        generateClear(&codeproducer);
    }
    back(1, *fOut);
    *fOut << "}";

    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "void instanceConstants" << fKlassName << "(" << fKlassName << "* dsp, int sample_rate) {";
    {
        tab(n + 1, *fOut);
        // Local visitor here to avoid DSP object incorrect type generation
        CInstVisitor codeproducer(fOut, "");
        codeproducer.Tab(n + 1);
        generateInit(&codeproducer);
    }
    back(1, *fOut);
    *fOut << "}";

    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "void instanceInit" << fKlassName << "(" << fKlassName << "* dsp, int sample_rate) {";
    tab(n + 1, *fOut);
    *fOut << "instanceConstants" << fKlassName << "(dsp, sample_rate);";
    tab(n + 1, *fOut);
    *fOut << "instanceResetUserInterface" << fKlassName << "(dsp);";
    tab(n + 1, *fOut);
    *fOut << "instanceClear" << fKlassName << "(dsp);";
    tab(n, *fOut);
    *fOut << "}";

    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "void init" << fKlassName << "(" << fKlassName << "* dsp, int sample_rate) {";
    tab(n + 1, *fOut);
    *fOut << "classInit" << fKlassName << "(sample_rate);";
    tab(n + 1, *fOut);
    *fOut << "instanceInit" << fKlassName << "(dsp, sample_rate);";
    tab(n, *fOut);
    *fOut << "}";

    if (!gGlobal->gLightMode) {
        // User interface
        tab(n, *fOut);
        tab(n, *fOut);
        *fOut << "void buildUserInterface" << fKlassName << "(" << fKlassName << "* dsp, UIGlue* ui_interface) {";
        tab(n + 1, *fOut);
        fCodeProducer->Tab(n + 1);
        generateUserInterface(fCodeProducer);
        back(1, *fOut);
        *fOut << "}";
    }

    // Compute
    generateCompute(n);
  
    // Generate user interface macros if needed
    printMacros(*fOut, n);

    tab(n, *fOut);
    *fOut << "#ifdef __cplusplus" << endl;
    *fOut << "}" << endl;
    *fOut << "#endif" << endl;
}

void CScalarOneSampleCodeContainer1::produceClass()
{
    int n = 0;
    
    tab(n, *fOut);
    *fOut << "#ifdef __cplusplus" << endl;
    *fOut << "extern \"C\" {" << endl;
    *fOut << "#endif" << endl;
    tab(n, *fOut);
    
    *fOut << "#if defined(_WIN32)" << endl;
    *fOut << "#define RESTRICT __restrict" << endl;
    *fOut << "#else" << endl;
    *fOut << "#define RESTRICT __restrict__" << endl;
    *fOut << "#endif" << endl;
    tab(n, *fOut);
    
    // Libraries
    printLibrary(*fOut);
    printIncludeFile(*fOut);
    
    // Sub containers
    mergeSubContainers();
    
    // Functions
    tab(n, *fOut);
    fCodeProducer->Tab(n);
    
    generateGlobalDeclarations(fCodeProducer);
    
    tab(n, *fOut);
    *fOut << "#ifndef FAUSTCLASS " << endl;
    *fOut << "#define FAUSTCLASS " << fKlassName << endl;
    *fOut << "#endif" << endl;
    
    *fOut << "#ifdef __APPLE__ " << endl;
    *fOut << "#define exp10f __exp10f" << endl;
    *fOut << "#define exp10 __exp10" << endl;
    *fOut << "#endif" << endl;
    
    if (gGlobal->gLightMode) {
        tab(n, *fOut);
        *fOut << "#define max(a,b) ((a < b) ? b : a)\n";
        *fOut << "#define min(a,b) ((a < b) ? a : b)\n";
        tab(n, *fOut);
    }
    
    tab(n, *fOut);
    *fOut << "typedef struct {";
    tab(n + 1, *fOut);
    
    // Fields
    fCodeProducer->Tab(n + 1);
    generateDeclarations(fCodeProducer);
    
    back(1, *fOut);
    *fOut << "} " << fKlassName << ";";
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "#define FAUST_INT_CONTROLS " << fInt32ControlNum << endl;
    *fOut << "#define FAUST_REAL_CONTROLS " << fRealControlNum << endl;
    
    tab(n, *fOut);
    *fOut << "#ifndef TESTBENCH";
    
    // Memory methods
    tab(n, *fOut);
    if (!gGlobal->gLightMode) {
        
        if (fAllocateInstructions->fCode.size() > 0) {
            tab(n, *fOut);
            *fOut << "static void allocate" << fKlassName << "(" << fKlassName << "* dsp) {";
            tab(n + 1, *fOut);
            generateAllocate(fCodeProducer);
            tab(n, *fOut);
            *fOut << "}";
        }
        tab(n, *fOut);
        
        if (fDestroyInstructions->fCode.size() > 0) {
            tab(n, *fOut);
            *fOut << "static void destroy" << fKlassName << "(" << fKlassName << "* dsp) {";
            tab(n + 1, *fOut);
            generateDestroy(fCodeProducer);
            tab(n, *fOut);
            *fOut << "}";
            tab(n, *fOut);
        }
        
        *fOut << fKlassName << "* new" << fKlassName << "() { ";
        tab(n + 1, *fOut);
        *fOut << fKlassName << "* dsp = (" << fKlassName << "*)calloc(1, sizeof(" << fKlassName << "));";
        if (fAllocateInstructions->fCode.size() > 0) {
            tab(n + 1, *fOut);
            *fOut << "allocate" << fKlassName << "(dsp);";
        }
        tab(n + 1, *fOut);
        *fOut << "return dsp;";
        tab(n, *fOut);
        *fOut << "}";
        
        tab(n, *fOut);
        tab(n, *fOut);
        *fOut << "void delete" << fKlassName << "(" << fKlassName << "* dsp) { ";
        if (fDestroyInstructions->fCode.size() > 0) {
            tab(n + 1, *fOut);
            *fOut << "destroy" << fKlassName << "(dsp);";
        }
        tab(n + 1, *fOut);
        *fOut << "free(dsp);";
        tab(n, *fOut);
        *fOut << "}";
        
        // Print metadata declaration
        tab(n, *fOut);
        produceMetadata(n);
    }
    
    // Get sample rate method
    tab(n, *fOut);
    fCodeProducer->Tab(n);
    generateGetSampleRate("getSampleRate" + fKlassName, "dsp", false, false)->accept(fCodeProducer);
    
    tab(n, *fOut);
    produceInfoFunctions(n, fKlassName, "dsp", false, false, fCodeProducer);
    
    // Inits
    
    // TODO
    /*
     CInstVisitor codeproducer1(fOut, "");
     codeproducer1.Tab(n+1);
     generateStaticInitFun("classInit" + fKlassName, false)->accept(&codeproducer1);
     generateInstanceInitFun("instanceInit" + fKlassName, false, false)->accept(&codeproducer2);
     */
    
    // Dummy
    tab(n, *fOut);
    *fOut << "void classInit" << fKlassName << "(int sample_rate) {}";
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "void staticInit" << fKlassName << "(" << fKlassName << "* dsp, int sample_rate) {";
    {
        tab(n + 1, *fOut);
        fCodeProducer->Tab(n + 1);
        // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
        inlineSubcontainersFunCalls(fStaticInitInstructions)->accept(fCodeProducer);
    }
    back(1, *fOut);
    *fOut << "}";
    
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "void instanceResetUserInterface" << fKlassName << "(" << fKlassName << "* dsp) {";
    {
        tab(n + 1, *fOut);
        fCodeProducer->Tab(n + 1);
        generateResetUserInterface(fCodeProducer);
    }
    back(1, *fOut);
    *fOut << "}";
    
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "void instanceClear" << fKlassName << "(" << fKlassName << "* dsp) {";
    {
        tab(n + 1, *fOut);
        fCodeProducer->Tab(n + 1);
        generateClear(fCodeProducer);
    }
    back(1, *fOut);
    *fOut << "}";
    
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "void instanceConstants" << fKlassName << "(" << fKlassName << "* dsp, int sample_rate) {";
    {
        tab(n + 1, *fOut);
        fCodeProducer->Tab(n + 1);
        // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
        inlineSubcontainersFunCalls(fInitInstructions)->accept(fCodeProducer);
    }
    back(1, *fOut);
    *fOut << "}";
    
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "void instanceInit" << fKlassName << "(" << fKlassName << "* dsp, int sample_rate) {";
    // staticInit has to be called for each instance since the tables are actually not shared between instances
    tab(n + 1, *fOut);
    *fOut << "staticInit" << fKlassName << "(dsp, sample_rate);";
    tab(n + 1, *fOut);
    *fOut << "instanceConstants" << fKlassName << "(dsp, sample_rate);";
    tab(n + 1, *fOut);
    *fOut << "instanceResetUserInterface" << fKlassName << "(dsp);";
    tab(n + 1, *fOut);
    *fOut << "instanceClear" << fKlassName << "(dsp);";
    tab(n, *fOut);
    *fOut << "}";
    
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "void init" << fKlassName << "(" << fKlassName << "* dsp, int sample_rate) {";
    tab(n + 1, *fOut);
    *fOut << "instanceInit" << fKlassName << "(dsp, sample_rate);";
    tab(n, *fOut);
    *fOut << "}";
    
    if (!gGlobal->gLightMode) {
        // User interface
        tab(n, *fOut);
        tab(n, *fOut);
        *fOut << "void buildUserInterface" << fKlassName << "(" << fKlassName << "* dsp, UIGlue* ui_interface) {";
        tab(n + 1, *fOut);
        fCodeProducer->Tab(n + 1);
        generateUserInterface(fCodeProducer);
        back(1, *fOut);
        *fOut << "}";
    }
    
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "void control" << fKlassName << "(" << fKlassName << "* dsp, " << subst("int* RESTRICT iControl, $0* RESTRICT fControl) {", xfloat());
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);
    // Generates local variables declaration and setup
    generateComputeBlock(fCodeProducer);
    back(1, *fOut);
    *fOut << "}" << endl;
    
    tab(n, *fOut);
    *fOut << "int getNumIntControls" << fKlassName << "(" << fKlassName << "* dsp) { return "
          << fInt32ControlNum << "; }";
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "int getNumRealControls" << fKlassName << "(" << fKlassName << "* dsp) { return "
          << fRealControlNum << "; }";
    
    // Compute
    generateCompute(n);
    
    tab(n, *fOut);
    *fOut << "#endif // TESTBENCH" << endl;
    tab(n, *fOut);
    
    // Generate user interface macros if needed
    printMacros(*fOut, n);
    
    *fOut << "#ifdef __cplusplus" << endl;
    *fOut << "}" << endl;
    *fOut << "#endif" << endl;
}

void CScalarOneSampleCodeContainer2::produceClass()
{
    int n = 0;
    
    tab(n, *fOut);
    *fOut << "#ifdef __cplusplus" << endl;
    *fOut << "extern \"C\" {" << endl;
    *fOut << "#endif" << endl;
    tab(n, *fOut);
    
    *fOut << "#if defined(_WIN32)" << endl;
    *fOut << "#define RESTRICT __restrict" << endl;
    *fOut << "#else" << endl;
    *fOut << "#define RESTRICT __restrict__" << endl;
    *fOut << "#endif" << endl;
    tab(n, *fOut);
    
    // Libraries
    printLibrary(*fOut);
    printIncludeFile(*fOut);
    
    // Sub containers
    mergeSubContainers();
    
    // Functions
    tab(n, *fOut);
    fCodeProducer->Tab(n);
    
    generateGlobalDeclarations(fCodeProducer);
    
    tab(n, *fOut);
    *fOut << "#ifndef FAUSTCLASS " << endl;
    *fOut << "#define FAUSTCLASS " << fKlassName << endl;
    *fOut << "#endif" << endl;
    
    *fOut << "#ifdef __APPLE__ " << endl;
    *fOut << "#define exp10f __exp10f" << endl;
    *fOut << "#define exp10 __exp10" << endl;
    *fOut << "#endif" << endl;
    
    if (gGlobal->gLightMode) {
        tab(n, *fOut);
        *fOut << "#define max(a,b) ((a < b) ? b : a)\n";
        *fOut << "#define min(a,b) ((a < b) ? a : b)\n";
        tab(n, *fOut);
    }
    
    tab(n, *fOut);
    *fOut << "typedef struct {";
    tab(n + 1, *fOut);
    
    // Fields
    fCodeProducer->Tab(n + 1);
    generateDeclarations(fCodeProducer);
    
    back(1, *fOut);
    *fOut << "} " << fKlassName << ";";
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "#define FAUST_INT_CONTROLS " << fInt32ControlNum << endl;
    *fOut << "#define FAUST_REAL_CONTROLS " << fRealControlNum << endl;
    
    tab(n, *fOut);
    *fOut << "#define FAUST_INT_ZONE " << static_cast<CInstVisitor1*>(fCodeProducer)->getIntZoneSize() << endl;
    *fOut << "#define FAUST_FLOAT_ZONE " << static_cast<CInstVisitor1*>(fCodeProducer)->getRealZoneSize();
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "#ifndef TESTBENCH";
    
    // Memory methods
    tab(n, *fOut);
    if (!gGlobal->gLightMode) {
        
        if (fAllocateInstructions->fCode.size() > 0) {
            tab(n, *fOut);
            *fOut << "static void allocate" << fKlassName << "(" << fKlassName << "* dsp) {";
            tab(n + 1, *fOut);
            generateAllocate(fCodeProducer);
            tab(n, *fOut);
            *fOut << "}";
        }
        tab(n, *fOut);
        
        if (fDestroyInstructions->fCode.size() > 0) {
            tab(n, *fOut);
            *fOut << "static void destroy" << fKlassName << "(" << fKlassName << "* dsp) {";
            tab(n + 1, *fOut);
            generateDestroy(fCodeProducer);
            tab(n, *fOut);
            *fOut << "}";
            tab(n, *fOut);
        }
        
        *fOut << fKlassName << "* new" << fKlassName << "() { ";
        tab(n + 1, *fOut);
        *fOut << fKlassName << "* dsp = (" << fKlassName << "*)calloc(1, sizeof(" << fKlassName << "));";
        if (fAllocateInstructions->fCode.size() > 0) {
            tab(n + 1, *fOut);
            *fOut << "allocate" << fKlassName << "(dsp);";
        }
        tab(n + 1, *fOut);
        *fOut << "return dsp;";
        tab(n, *fOut);
        *fOut << "}";
        
        tab(n, *fOut);
        tab(n, *fOut);
        *fOut << "void delete" << fKlassName << "(" << fKlassName << "* dsp) { ";
        if (fDestroyInstructions->fCode.size() > 0) {
            tab(n + 1, *fOut);
            *fOut << "destroy" << fKlassName << "(dsp);";
        }
        tab(n + 1, *fOut);
        *fOut << "free(dsp);";
        tab(n, *fOut);
        *fOut << "}";
        
        // Print metadata declaration
        tab(n, *fOut);
        produceMetadata(n);
    }
    
    // Get sample rate method
    tab(n, *fOut);
    fCodeProducer->Tab(n);
    generateGetSampleRate("getSampleRate" + fKlassName, "dsp", false, false)->accept(fCodeProducer);
    
    tab(n, *fOut);
    produceInfoFunctions(n, fKlassName, "dsp", false, false, fCodeProducer);
    
    // Inits
    
    // TODO
    /*
     CInstVisitor codeproducer1(fOut, "");
     codeproducer1.Tab(n+1);
     generateStaticInitFun("classInit" + fKlassName, false)->accept(&codeproducer1);
     generateInstanceInitFun("instanceInit" + fKlassName, false, false)->accept(&codeproducer2);
     */
    
    // Dummy
    tab(n, *fOut);
    *fOut << "void classInit" << fKlassName << "(int sample_rate) {}";
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "void staticInit" << fKlassName << "(" << fKlassName << "* dsp, int sample_rate, " << subst("int* iZone, $0* fZone) {", xfloat());
    {
        tab(n + 1, *fOut);
        fCodeProducer->Tab(n + 1);
        // For waveform
        MoveVariablesInFront3().getCode(fGlobalDeclarationInstructions)->accept(fCodeProducer);
        // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
        inlineSubcontainersFunCalls(fStaticInitInstructions)->accept(fCodeProducer);
    }
    back(1, *fOut);
    *fOut << "}";
    
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "void instanceResetUserInterface" << fKlassName << "(" << fKlassName << "* dsp) {";
    {
        tab(n + 1, *fOut);
        fCodeProducer->Tab(n + 1);
        generateResetUserInterface(fCodeProducer);
    }
    back(1, *fOut);
    *fOut << "}";
    
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "void instanceClear" << fKlassName << "(" << fKlassName << "* dsp, " << subst("int* iZone, $0* fZone) {", xfloat());
    {
        tab(n + 1, *fOut);
        fCodeProducer->Tab(n + 1);
        generateClear(fCodeProducer);
    }
    back(1, *fOut);
    *fOut << "}";
    
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "void instanceConstants" << fKlassName << "(" << fKlassName << "* dsp, int sample_rate, " << subst("int* iZone, $0* fZone) {", xfloat());
    {
        tab(n + 1, *fOut);
        fCodeProducer->Tab(n + 1);
        // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
        inlineSubcontainersFunCalls(fInitInstructions)->accept(fCodeProducer);
    }
    back(1, *fOut);
    *fOut << "}";
    
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "void instanceInit" << fKlassName << "(" << fKlassName << "* dsp, int sample_rate, " << subst("int* iZone, $0* fZone) {", xfloat());
    // staticInit has to be called for each instance since the tables are actually not shared between instances
    tab(n + 1, *fOut);
    *fOut << "staticInit" << fKlassName << "(dsp, sample_rate, iZone, fZone);";
    tab(n + 1, *fOut);
    *fOut << "instanceConstants" << fKlassName << "(dsp, sample_rate, iZone, fZone);";
    tab(n + 1, *fOut);
    *fOut << "instanceResetUserInterface" << fKlassName << "(dsp);";
    tab(n + 1, *fOut);
    *fOut << "instanceClear" << fKlassName << "(dsp, iZone, fZone);";
    tab(n, *fOut);
    *fOut << "}";
    
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "void init" << fKlassName << "(" << fKlassName << "* dsp, int sample_rate, " << subst("int* iZone, $0* fZone) {", xfloat());
    tab(n + 1, *fOut);
    *fOut << "instanceInit" << fKlassName << "(dsp, sample_rate, iZone, fZone);";
    tab(n, *fOut);
    *fOut << "}";
    
    if (!gGlobal->gLightMode) {
        // User interface
        tab(n, *fOut);
        tab(n, *fOut);
        *fOut << "void buildUserInterface" << fKlassName << "(" << fKlassName << "* dsp, UIGlue* ui_interface) {";
        tab(n + 1, *fOut);
        fCodeProducer->Tab(n + 1);
        generateUserInterface(fCodeProducer);
        back(1, *fOut);
        *fOut << "}";
    }
    
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "void control" << fKlassName << "(" << fKlassName << "* dsp, " << subst("int* RESTRICT iControl, $0* RESTRICT fControl, int* RESTRICT iZone, $0* RESTRICT fZone) {", xfloat());
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);
    // Generates local variables declaration and setup
    generateComputeBlock(fCodeProducer);
    back(1, *fOut);
    *fOut << "}" << endl;
    
    tab(n, *fOut);
    *fOut << "int getNumIntControls" << fKlassName << "(" << fKlassName << "* dsp) { return "
          << fInt32ControlNum << "; }";
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "int getNumRealControls" << fKlassName << "(" << fKlassName << "* dsp) { return "
          << fRealControlNum << "; }";
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "int getiZoneSize" << fKlassName << "(" << fKlassName << "* dsp) { return "
          << static_cast<CInstVisitor1*>(fCodeProducer)->getIntZoneSize() << "; }";
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "int getfZoneSize" << fKlassName << "(" << fKlassName << "* dsp) { return "
          << static_cast<CInstVisitor1*>(fCodeProducer)->getRealZoneSize() << "; }";
    
    // Compute
    generateCompute(n);
    
    tab(n, *fOut);
    *fOut << "#endif // TESTBENCH" << endl;
    tab(n, *fOut);
    
    // Generate user interface macros if needed
    printMacros(*fOut, n);
    
    *fOut << "#ifdef __cplusplus" << endl;
    *fOut << "}" << endl;
    *fOut << "#endif" << endl;
}

void CCodeContainer::produceMetadata(int tabs)
{
    tab(tabs, *fOut);
    *fOut << "void metadata" << fKlassName << "(MetaGlue* m) { ";

    // We do not want to accumulate metadata from all hierachical levels, so the upper level only is kept
    for (const auto& i : gGlobal->gMetaDataSet) {
        if (i.first != tree("author")) {
            tab(tabs + 1, *fOut);
            *fOut << "m->declare(m->metaInterface, \"" << *(i.first) << "\", " << **(i.second.begin()) << ");";
        } else {
            // But the "author" meta data is accumulated, the upper level becomes the main author and sub-levels become
            // "contributor"
            for (set<Tree>::iterator j = i.second.begin(); j != i.second.end(); j++) {
                if (j == i.second.begin()) {
                    tab(tabs + 1, *fOut);
                    *fOut << "m->declare(m->metaInterface, \"" << *(i.first) << "\", " << **j << ");";
                } else {
                    tab(tabs + 1, *fOut);
                    *fOut << "m->declare(m->metaInterface, \""
                          << "contributor"
                          << "\", " << **j << ");";
                }
            }
        }
    }

    tab(tabs, *fOut);
    *fOut << "}" << endl;
}

// Scalar
CScalarCodeContainer::CScalarCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out,
                                           int sub_container_type)
    : CCodeContainer(name, numInputs, numOutputs, out)
{
    fSubContainerType = sub_container_type;
}

void CScalarCodeContainer::generateComputeAux(int n)
{
    // Generates declaration
    tab(n, *fOut);
    *fOut << "void compute" << fKlassName << "(" << fKlassName
          << subst("* dsp, int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);

    // Generates local variables declaration and setup
    generateComputeBlock(fCodeProducer);
  
    // Generates one single scalar loop
    ForLoopInst* loop = fCurLoop->generateScalarLoop(fFullCount);
    loop->accept(fCodeProducer);
  
    /*
     // TODO : atomic switch
     // Currently for soundfile management
     */
    generatePostComputeBlock(fCodeProducer);
    
    back(1, *fOut);
    *fOut << "}" << endl;
}

// Special version for -os generation mode
void CScalarOneSampleCodeContainer1::generateComputeAux(int n)
{
    // Generates declaration
    tab(n, *fOut);
    if (gGlobal->gInPlace) {
        *fOut << "void compute" << fKlassName << "(" << fKlassName
        << subst("* dsp, $0* inputs, $0* outputs, int* RESTRICT iControl, $0* RESTRICT fControl) {", xfloat());
    } else {
        *fOut << "void compute" << fKlassName << "(" << fKlassName
        << subst("* dsp, $0* RESTRICT inputs, $0* RESTRICT outputs, int* RESTRICT iControl, $0* RESTRICT fControl) {", xfloat());
    }
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);
    
    // Generates one sample computation
    BlockInst* block = fCurLoop->generateOneSample();
    block->accept(fCodeProducer);
    
    /*
     // TODO : atomic switch
     // Currently for soundfile management
     */
    generatePostComputeBlock(fCodeProducer);
    
    back(1, *fOut);
    *fOut << "}" << endl;
}

// Special version for -os generation mode with iZone and fZone
void CScalarOneSampleCodeContainer2::generateComputeAux(int n)
{
    // Generates declaration
    tab(n, *fOut);
    if (gGlobal->gInPlace) {
        *fOut << "void compute" << fKlassName << "(" << fKlassName
        << subst("* dsp, $0* inputs, $0* outputs, int* RESTRICT iControl, $0* RESTRICT fControl, int* RESTRICT iZone, $0* RESTRICT fZone) {", xfloat());
        
    } else {
        *fOut << "void compute" << fKlassName << "(" << fKlassName
        << subst("* dsp, $0* RESTRICT inputs, $0* RESTRICT outputs, int* RESTRICT iControl, $0* RESTRICT fControl, int* RESTRICT iZone, $0* RESTRICT fZone) {", xfloat());
    }
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);
    
    // Generates one sample computation
    BlockInst* block = fCurLoop->generateOneSample();
    block->accept(fCodeProducer);
    
    /*
     // TODO : atomic switch
     // Currently for soundfile management
     */
    generatePostComputeBlock(fCodeProducer);
    
    back(1, *fOut);
    *fOut << "}" << endl;
}

// Vector
CVectorCodeContainer::CVectorCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out)
    : VectorCodeContainer(numInputs, numOutputs), CCodeContainer(name, numInputs, numOutputs, out)
{
}

void CVectorCodeContainer::generateComputeAux(int n)
{
    // Generates declaration
    tab(n, *fOut);
    *fOut << "void compute" << fKlassName << "(" << fKlassName
          << subst("* dsp, int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);

    // Generates local variables declaration and setup
    generateComputeBlock(fCodeProducer);

    // Generates the DSP loop
    fDAGBlock->accept(fCodeProducer);

    back(1, *fOut);
    *fOut << "}" << endl;
}

// OpenMP
COpenMPCodeContainer::COpenMPCodeContainer(const string& name, int numInputs, int numOutputs, std::ostream* out)
    : OpenMPCodeContainer(numInputs, numOutputs), CCodeContainer(name, numInputs, numOutputs, out)
{
}

void COpenMPCodeContainer::generateComputeAux(int n)
{
    // Compute declaration
    tab(n, *fOut);
    *fOut << "void compute" << fKlassName << "(" << fKlassName
          << subst("* dsp, int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);

    // Generates local variables declaration and setup
    generateComputeBlock(fCodeProducer);

    // Generate it
    fGlobalLoopBlock->accept(fCodeProducer);

    back(1, *fOut);
    *fOut << "}" << endl;
}

// Works stealing scheduler
CWorkStealingCodeContainer::CWorkStealingCodeContainer(const string& name, int numInputs, int numOutputs,
                                                       std::ostream* out)
    : WSSCodeContainer(numInputs, numOutputs, "dsp"), CCodeContainer(name, numInputs, numOutputs, out)
{
}

void CWorkStealingCodeContainer::generateComputeAux(int n)
{
    // Generates "computeThread" code
    tab(n, *fOut);
    *fOut << "static void computeThread" << fKlassName << "(" << fKlassName << "* dsp, int num_thread) {";
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);

    // Generate it
    fThreadLoopBlock->accept(fCodeProducer);

    back(1, *fOut);
    *fOut << "}" << endl;

    // Compute "compute" declaration
    tab(n, *fOut);
    *fOut << "void compute" << fKlassName << "(" << fKlassName
          << subst("* dsp, int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);

    // Generates local variables declaration and setup
    generateComputeBlock(fCodeProducer);

    back(1, *fOut);
    *fOut << "}" << endl;

    tab(n, *fOut);
    *fOut << "extern \"C\" void computeThreadExternal(void* dsp, int num_thread) {";
    tab(n + 1, *fOut);
    *fOut << "computeThread" << fKlassName << "((" << fKlassName << "*)dsp, num_thread);";
    tab(n, *fOut);
    *fOut << "}" << endl;
}
