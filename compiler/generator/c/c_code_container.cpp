/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#include <climits>

#include "c_code_container.hh"
#include "Text.hh"
#include "exception.hh"
#include "fir_function_builder.hh"
#include "floats.hh"
#include "global.hh"

using namespace std;

/*
 C backend and module description:
 
    1) in -os mode:
        - subcontainers are merged in the main class: in -os0 mode,  static tables are allocated as global, and in iZone/fZone in -os(1|2|3) modes
        - CScalarOneSampleCodeContainer1 (used in -os0) separates the DSP control state in iControl/fControl (possibly to be allocated elsewhere)
        - CScalarOneSampleCodeContainer2 (used in -os1) separates the DSP control state in iControl/fControl and the DSP state in iZone/fZone (possibly to be allocated elsewhere)
        - CScalarOneSampleCodeContainer3 (used in -os2) separates the DSP control state in iControl/fControl and the DSP state in iZone/fZone (possibly to be allocated elsewhere). Short delay lines remain in DSP struct, long delay lines are moved in iZone/fZone.
        Additional functions 'instanceConstantsFromMem' and 'instanceConstantsToMem' to copy iConst/fConst variables from/to memory are generated.
        - CScalarOneSampleCodeContainer4 (used in -os3) is similar to CPPScalarOneSampleCodeContainer3, but iControl/fControl and iZone/fZone pointers stay in the DSP class. The -mem option uses the memory manager to allocate/destroy the iControl/fControl and iZone/fZone pointers
 
    2) in -fx mode:
         - then/else branches of 'select2' are explicitly casted to 'float', otherwise AP_fixed compilation may trigger "ambigous type" errors
         - all math operators are named "FOOfx" and are supposed to be implemented in the architecture file (doing the proper cast on arguments and return value when needed)

 */

map<string, bool> CInstVisitor::gFunctionSymbolTable;

dsp_factory_base* CCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(
        fKlassName, "", "",
        ((dynamic_cast<ostringstream*>(fOut)) ? dynamic_cast<ostringstream*>(fOut)->str() : ""), "");
}

CodeContainer* CCodeContainer::createScalarContainer(const std::string& name, int numInputs, int numOutputs, ostream* dst, int sub_container_type)
{
    if (gGlobal->gOneSample == 0) {
        return new CScalarOneSampleCodeContainer1(name, numInputs, numOutputs, dst, sub_container_type);
    } else if (gGlobal->gOneSample == 1) {
        return new CScalarOneSampleCodeContainer2(name, numInputs, numOutputs, dst, sub_container_type);
    } else if (gGlobal->gOneSample == 2) {
        return new CScalarOneSampleCodeContainer3(name, numInputs, numOutputs, dst, sub_container_type);
    } else if (gGlobal->gOneSample == 3) {
        return new CScalarOneSampleCodeContainer4(name, numInputs, numOutputs, dst, sub_container_type);
    } else {
        return new CScalarCodeContainer(name, numInputs, numOutputs, dst, sub_container_type);
    }
}

CodeContainer* CCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return createScalarContainer(name, 0, 1, fOut, sub_container_type);
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
        container = createScalarContainer(name, numInputs, numOutputs, dst, kInt);
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
    produceInfoFunctions(n, fKlassName, "dsp", false, FunTyped::kDefault, fCodeProducer);

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
 
    *fOut << "#if defined(_WIN32)" << endl;
    *fOut << "#define RESTRICT __restrict" << endl;
    *fOut << "#else" << endl;
    *fOut << "#define RESTRICT __restrict__" << endl;
    *fOut << "#endif" << endl;
    tab(n, *fOut);
    
  
    // Libraries
    printLibrary(*fOut);
    printIncludeFile(*fOut);

    // Generate gub containers
    generateSubContainers();

    // Global declarations
    tab(n, *fOut);
    fCodeProducer->Tab(n);
    generateGlobalDeclarations(fCodeProducer);

    tab(n, *fOut);
    *fOut << "#ifndef FAUSTCLASS " << endl;
    *fOut << "#define FAUSTCLASS " << fKlassName << endl;
    *fOut << "#endif" << endl;
    tab(n, *fOut);

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
        
        generateAllocateFun(n);
        tab(n, *fOut);
        generateDestroyFun(n);

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
    produceInfoFunctions(n, fKlassName, "dsp", false, FunTyped::kDefault, fCodeProducer);

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

// Used with -os0 option
void CScalarOneSampleCodeContainer1::produceClass()
{
    int n = 0;
    
    generateHeader1(n);
     
    // Libraries
    printLibrary(*fOut);
    printIncludeFile(*fOut);
    
    // Sub containers are merged in the main class
    mergeSubContainers();
    
    // Global declarations
    tab(n, *fOut);
    fCodeProducer->Tab(n);
    generateGlobalDeclarations(fCodeProducer);
    
    generateHeader2(n);
    
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
    *fOut << "#define FAUST_INT_CONTROLS " << fIntControl->fCurIndex << endl;
    *fOut << "#define FAUST_REAL_CONTROLS " << fRealControl->fCurIndex << endl;
    tab(n, *fOut);
    
    *fOut << "#ifndef TESTBENCH";
    
    // Memory methods
    tab(n, *fOut);
    if (!gGlobal->gLightMode) {
        
        generateAllocateFun(n);
        tab(n, *fOut);
        generateDestroyFun(n);
         
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
    produceInfoFunctions(n, fKlassName, "dsp", false, FunTyped::kDefault, fCodeProducer);
    
    // Inits
    
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
    *fOut << "void control" << fKlassName << "(" << fKlassName << "* dsp, " << subst("int* RESTRICT iControl, $0* RESTRICT fControl) {", ifloat());
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);
    // Generates local variables declaration and setup
    generateComputeBlock(fCodeProducer);
    back(1, *fOut);
    *fOut << "}" << endl;
    
    tab(n, *fOut);
    *fOut << "int getNumIntControls" << fKlassName << "(" << fKlassName << "* dsp) { return "
    << fIntControl->fCurIndex << "; }";
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "int getNumRealControls" << fKlassName << "(" << fKlassName << "* dsp) { return "
    << fRealControl->fCurIndex << "; }";
    
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

// Used with -os1 option
void CScalarOneSampleCodeContainer2::produceClass()
{
    int n = 0;
    
    generateHeader1(n);
      
    // Libraries
    printLibrary(*fOut);
    printIncludeFile(*fOut);
    
    // Sub containers are merged in the main class
    mergeSubContainers();
    
    // Global declarations
    tab(n, *fOut);
    fCodeProducer->Tab(n);
    generateGlobalDeclarations(fCodeProducer);
    
    generateHeader2(n);
    
    tab(n, *fOut);
    *fOut << "typedef struct {";
    tab(n + 1, *fOut);
    
    // Fields
    fCodeProducer->Tab(n + 1);
    generateDeclarations(fCodeProducer);
    
    // Kept here because staticInit incorrectly change the size later on
    int int_zone_size = static_cast<CInstVisitor1*>(fCodeProducer)->getIntZoneSize();
    int real_zone_size = static_cast<CInstVisitor1*>(fCodeProducer)->getRealZoneSize();
    
    back(1, *fOut);
    *fOut << "} " << fKlassName << ";";
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "#ifndef TESTBENCH";
    
    // Memory methods
    tab(n, *fOut);
    if (!gGlobal->gLightMode) {
        
        generateAllocateFun(n);
        tab(n, *fOut);
        generateDestroyFun(n);
       
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
    produceInfoFunctions(n, fKlassName, "dsp", false, FunTyped::kDefault, fCodeProducer);
    
    // Inits
    
    // Dummy
    tab(n, *fOut);
    *fOut << "void classInit" << fKlassName << "(int sample_rate) {}";
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "void staticInit" << fKlassName << "(" << fKlassName << "* dsp, int sample_rate, " << subst("int* iZone, $0* fZone) {", ifloat());
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
    *fOut << "void instanceConstants" << fKlassName << "(" << fKlassName << "* dsp, int sample_rate, " << subst("int* iZone, $0* fZone) {", ifloat());
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
    *fOut << "void instanceClear" << fKlassName << "(" << fKlassName << "* dsp, " << subst("int* iZone, $0* fZone) {", ifloat());
    {
        tab(n + 1, *fOut);
        fCodeProducer->Tab(n + 1);
        generateClear(fCodeProducer);
    }
    back(1, *fOut);
    *fOut << "}";
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "void instanceInit" << fKlassName << "(" << fKlassName << "* dsp, int sample_rate, " << subst("int* iZone, $0* fZone) {", ifloat());
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
    *fOut << "void init" << fKlassName << "(" << fKlassName << "* dsp, int sample_rate, " << subst("int* iZone, $0* fZone) {", ifloat());
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
    *fOut << "void control" << fKlassName << "(" << fKlassName << "* dsp, " << subst("int* RESTRICT iControl, $0* RESTRICT fControl, int* RESTRICT iZone, $0* RESTRICT fZone) {", ifloat());
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);
    // Generates local variables declaration and setup
    generateComputeBlock(fCodeProducer);
    back(1, *fOut);
    *fOut << "}" << endl;
    
    tab(n, *fOut);
    *fOut << "int getNumIntControls" << fKlassName << "(" << fKlassName << "* dsp) { return "
    << fIntControl->fCurIndex << "; }";
    tab(n, *fOut);
    
    *fOut << "int getNumRealControls" << fKlassName << "(" << fKlassName << "* dsp) { return "
    << fRealControl->fCurIndex << "; }";
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "int getiZoneSize" << fKlassName << "(" << fKlassName << "* dsp) { return " << int_zone_size << "; }";
    tab(n, *fOut);
    
    *fOut << "int getfZoneSize" << fKlassName << "(" << fKlassName << "* dsp) { return " << real_zone_size << "; }";
    
    // Compute
    generateCompute(n);
    
    tab(n, *fOut);
    *fOut << "#define FAUST_INT_CONTROLS " << fIntControl->fCurIndex << endl;
    *fOut << "#define FAUST_REAL_CONTROLS " << fRealControl->fCurIndex << endl;
    
    tab(n, *fOut);
    *fOut << "#define FAUST_INT_ZONE " << int_zone_size << endl;
    *fOut << "#define FAUST_FLOAT_ZONE " << real_zone_size;
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "#endif // TESTBENCH" << endl;
    tab(n, *fOut);
    
    // Generate user interface macros if needed
    printMacros(*fOut, n);
    
    *fOut << "#ifdef __cplusplus" << endl;
    *fOut << "}" << endl;
    *fOut << "#endif" << endl;
}

// Used with -os2 option
void CScalarOneSampleCodeContainer3::produceClass()
{
    // Allocate fCodeProducer here
    VariableSizeCounter heap_counter(Address::kStruct);
    generateDeclarations(&heap_counter);
    fCodeProducer = new CInstVisitor2(fOut, fKlassName, std::max(0, heap_counter.fSizeBytes - gGlobal->gFPGAMemory));
    
    int n = 0;
    
    generateHeader1(n);
       
    // Libraries
    printLibrary(*fOut);
    printIncludeFile(*fOut);
    
    // Sub containers are merged in the main class
    mergeSubContainers();
    
    // Global declarations
    tab(n, *fOut);
    fCodeProducer->Tab(n);
    generateGlobalDeclarations(fCodeProducer);
    
    generateHeader2(n);
    
    tab(n, *fOut);
    *fOut << "typedef struct {";
    tab(n + 1, *fOut);
    
    // Fields
    fCodeProducer->Tab(n + 1);
    generateDeclarations(fCodeProducer);
    
    // Kept here because staticInit incorrectly change the size later on
    int int_zone_size = static_cast<CInstVisitor1*>(fCodeProducer)->getIntZoneSize();
    int real_zone_size = static_cast<CInstVisitor1*>(fCodeProducer)->getRealZoneSize();
    
    back(1, *fOut);
    *fOut << "} " << fKlassName << ";";
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "#ifndef TESTBENCH";
    
    // Memory methods
    tab(n, *fOut);
    if (!gGlobal->gLightMode) {
        
        generateAllocateFun(n);
        tab(n, *fOut);
        generateDestroyFun(n);
    
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
    produceInfoFunctions(n, fKlassName, "dsp", false, FunTyped::kDefault, fCodeProducer);
    
    // Inits
    
    // Dummy
    tab(n, *fOut);
    *fOut << "void classInit" << fKlassName << "(int sample_rate) {}";
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "void staticInit" << fKlassName << "(" << fKlassName << "* dsp, int sample_rate, " << subst("int* iZone, $0* fZone) {", ifloat());
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
    *fOut << "void instanceConstants" << fKlassName << "(" << fKlassName << "* dsp, int sample_rate, " << subst("int* iZone, $0* fZone) {", ifloat());
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
    *fOut << "void instanceConstantsFromMem" << fKlassName << "(" << fKlassName << "* dsp, int sample_rate, " << subst("int* iZone, $0* fZone) {", ifloat());
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);
    // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
    BlockInst* block1 = inlineSubcontainersFunCalls(fInitInstructions);
    ConstantsCopyFromMemory copy_from_mem(int_zone_size, real_zone_size);
    CInstVisitor visitor1(fOut, fKlassName, n + 1);
    copy_from_mem.getCode(block1)->accept(&visitor1);
    back(1, *fOut);
    *fOut << "}";
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "void instanceConstantsToMem" << fKlassName << "(" << fKlassName << "* dsp, int sample_rate, " << subst("int* iZone, $0* fZone) {", ifloat());
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);
    // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
    BlockInst* block2 = inlineSubcontainersFunCalls(fInitInstructions);
    ConstantsCopyToMemory copy_to_mem(int_zone_size, real_zone_size);
    CInstVisitor visitor(fOut, fKlassName, n + 1);
    copy_to_mem.getCode(block2)->accept(&visitor);
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
    *fOut << "void instanceClear" << fKlassName << "(" << fKlassName << "* dsp, " << subst("int* iZone, $0* fZone) {", ifloat());
    {
        tab(n + 1, *fOut);
        fCodeProducer->Tab(n + 1);
        generateClear(fCodeProducer);
    }
    back(1, *fOut);
    *fOut << "}";
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "void instanceInit" << fKlassName << "(" << fKlassName << "* dsp, int sample_rate, " << subst("int* iZone, $0* fZone) {", ifloat());
    // staticInit has to be called for each instance since the tables are actually not shared between instances
    tab(n + 1, *fOut);
    *fOut << "staticInit" << fKlassName << "(dsp, sample_rate, iZone, fZone);";
    tab(n + 1, *fOut);
    *fOut << "instanceConstants" << fKlassName << "(dsp, sample_rate, iZone, fZone);";
    tab(n + 1, *fOut);
    *fOut << "instanceConstantsToMem" << fKlassName << "(dsp, sample_rate, iZone, fZone);";
    tab(n + 1, *fOut);
    *fOut << "instanceResetUserInterface" << fKlassName << "(dsp);";
    tab(n + 1, *fOut);
    *fOut << "instanceClear" << fKlassName << "(dsp, iZone, fZone);";
    tab(n, *fOut);
    *fOut << "}";
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "void init" << fKlassName << "(" << fKlassName << "* dsp, int sample_rate, " << subst("int* iZone, $0* fZone) {", ifloat());
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
    *fOut << "void control" << fKlassName << "(" << fKlassName << "* dsp, " << subst("int* RESTRICT iControl, $0* RESTRICT fControl, int* RESTRICT iZone, $0* RESTRICT fZone) {", ifloat());
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);
    // Generates local variables declaration and setup
    generateComputeBlock(fCodeProducer);
    back(1, *fOut);
    *fOut << "}" << endl;
    
    tab(n, *fOut);
    *fOut << "int getNumIntControls" << fKlassName << "(" << fKlassName << "* dsp) { return "
    << fIntControl->fCurIndex << "; }";
    tab(n, *fOut);
    
    *fOut << "int getNumRealControls" << fKlassName << "(" << fKlassName << "* dsp) { return "
    << fRealControl->fCurIndex << "; }";
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "int getiZoneSize" << fKlassName << "(" << fKlassName << "* dsp) { return "
    << copy_from_mem.fIntIndex << "; }";
    tab(n, *fOut);
    
    *fOut << "int getfZoneSize" << fKlassName << "(" << fKlassName << "* dsp) { return "
    << copy_from_mem.fRealIndex << "; }";
    
    // Compute
    generateCompute(n);
    
    tab(n, *fOut);
    *fOut << "#define FAUST_INT_CONTROLS " << fIntControl->fCurIndex << endl;
    *fOut << "#define FAUST_REAL_CONTROLS " << fRealControl->fCurIndex << endl;
    
    tab(n, *fOut);
    // copy_from_mem.fIntIndex and copy_from_mem.fRealIndex contains the size used for tables, DLs and iConst/fConst variables
    *fOut << "#define FAUST_INT_ZONE " << copy_from_mem.fIntIndex << endl;
    *fOut << "#define FAUST_FLOAT_ZONE " << copy_from_mem.fRealIndex;
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "#endif // TESTBENCH" << endl;
    tab(n, *fOut);
    
    // Generate user interface macros if needed
    printMacros(*fOut, n);
    
    *fOut << "#ifdef __cplusplus" << endl;
    *fOut << "}" << endl;
    *fOut << "#endif" << endl;
}

// Used with -os3 option
void CScalarOneSampleCodeContainer4::produceClass()
{
    // Allocate fCodeProducer here
    VariableSizeCounter heap_counter(Address::kStruct);
    generateDeclarations(&heap_counter);
    fCodeProducer = new CInstVisitor3(fOut, fKlassName, std::max(0, heap_counter.fSizeBytes - gGlobal->gFPGAMemory));
     
    int n = 0;
    
    generateHeader1(n);
    
    // Libraries
    printLibrary(*fOut);
    printIncludeFile(*fOut);
    
    // Sub containers are merged in the main class
    mergeSubContainers();
    
    // Global declarations
    tab(n, *fOut);
    fCodeProducer->Tab(n);
    generateGlobalDeclarations(fCodeProducer);
    
    generateHeader2(n);
    
    tab(n, *fOut);
    *fOut << "typedef struct {";
    tab(n + 1, *fOut);
    
    // Fields
    fCodeProducer->Tab(n + 1);
    
    // Additional fields
    pushDeclare(InstBuilder::genDecStructVar("iControl", InstBuilder::genArrayTyped(InstBuilder::genInt32Typed(), 0)));
    pushDeclare(InstBuilder::genDecStructVar("fControl", InstBuilder::genArrayTyped(InstBuilder::genItFloatTyped(), 0)));
    pushDeclare(InstBuilder::genDecStructVar("iZone", InstBuilder::genArrayTyped(InstBuilder::genInt32Typed(), 0)));
    pushDeclare(InstBuilder::genDecStructVar("fZone", InstBuilder::genArrayTyped(InstBuilder::genItFloatTyped(), 0)));
    generateDeclarations(fCodeProducer);
    
    // Kept here because staticInit incorrectly change the size later on
    int int_zone_size = static_cast<CInstVisitor1*>(fCodeProducer)->getIntZoneSize();
    int real_zone_size = static_cast<CInstVisitor1*>(fCodeProducer)->getRealZoneSize();
    
    back(1, *fOut);
    *fOut << "} " << fKlassName << ";";
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "#ifndef TESTBENCH";
    
    // Memory methods
    tab(n, *fOut);
    if (!gGlobal->gLightMode) {
        
        generateAllocateFun(n);
        tab(n, *fOut);
        generateDestroyFun(n);
        
        *fOut << fKlassName << "* new" << fKlassName << "(int* icontrol, " << ifloat() << "* fcontrol, int* izone, " << ifloat() << "* fzone) {";
        tab(n + 1, *fOut);
        *fOut << fKlassName << "* dsp = (" << fKlassName << "*)calloc(1, sizeof(" << fKlassName << "));";
        if (fAllocateInstructions->fCode.size() > 0) {
            tab(n + 1, *fOut);
            *fOut << "allocate" << fKlassName << "(dsp);";
        }
        tab(n + 1, *fOut);
        *fOut << "dsp->iControl = icontrol;";
        tab(n + 1, *fOut);
        *fOut << "dsp->fControl = fcontrol;";
        tab(n + 1, *fOut);
        *fOut << "dsp->iZone = izone;";
        tab(n + 1, *fOut);
        *fOut << "dsp->fZone = fzone;";
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
        
        // setMemory
        tab(n, *fOut);
        tab(n, *fOut);
        *fOut << "void setMemory" << fKlassName << "(" << fKlassName << "* dsp, int* icontrol, " << ifloat() << "* fcontrol, int* izone, " << ifloat() << "* fzone) {";
        tab(n + 1, *fOut);
        *fOut << "dsp->iControl = icontrol;";
        tab(n + 1, *fOut);
        *fOut << "dsp->fControl = fcontrol;";
        tab(n + 1, *fOut);
        *fOut << "dsp->iZone = izone;";
        tab(n + 1, *fOut);
        *fOut << "dsp->fZone = fzone;";
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
    produceInfoFunctions(n, fKlassName, "dsp", false, FunTyped::kDefault, fCodeProducer);
    
    // Inits
    
    // Dummy
    tab(n, *fOut);
    *fOut << "void classInit" << fKlassName << "(int sample_rate) {}";
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "void staticInit" << fKlassName << "(" << fKlassName << "* dsp, int sample_rate) {";
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
    *fOut << "void instanceConstantsFromMem" << fKlassName << "(" << fKlassName << "* dsp, int sample_rate) {";
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);
    // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
    BlockInst* block1 = inlineSubcontainersFunCalls(fInitInstructions);
    ConstantsCopyFromMemory1 copy_from_mem(int_zone_size, real_zone_size);
    CInstVisitor visitor1(fOut, fKlassName, n + 1);
    copy_from_mem.getCode(block1)->accept(&visitor1);
    back(1, *fOut);
    *fOut << "}";
    
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "void instanceConstantsToMem" << fKlassName << "(" << fKlassName << "* dsp, int sample_rate) {";
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);
    // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
    BlockInst* block2 = inlineSubcontainersFunCalls(fInitInstructions);
    ConstantsCopyToMemory1 copy_to_mem(int_zone_size, real_zone_size);
    CInstVisitor visitor(fOut, fKlassName, n + 1);
    copy_to_mem.getCode(block2)->accept(&visitor);
    // Keep the updated values
    int_zone_size = copy_from_mem.fIntIndex;
    real_zone_size = copy_from_mem.fRealIndex;
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
    *fOut << "instanceConstantsToMem" << fKlassName << "(dsp, sample_rate);";
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
    *fOut << "void control" << fKlassName << "(" << fKlassName << "* dsp) {";
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);
    // Generates local variables declaration and setup
    generateComputeBlock(fCodeProducer);
    back(1, *fOut);
    *fOut << "}" << endl;
    
    tab(n, *fOut);
    *fOut << "int getNumIntControls" << fKlassName << "(" << fKlassName << "* dsp) { return "
    << fIntControl->fCurIndex << "; }";
    tab(n, *fOut);
    
    *fOut << "int getNumRealControls" << fKlassName << "(" << fKlassName << "* dsp) { return "
    << fRealControl->fCurIndex << "; }";
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "int getiZoneSize" << fKlassName << "(" << fKlassName << "* dsp) { return " << int_zone_size << "; }";
    tab(n, *fOut);
    
    *fOut << "int getfZoneSize" << fKlassName << "(" << fKlassName << "* dsp) { return " << real_zone_size << "; }";
    
    // Compute
    generateCompute(n);
    
    tab(n, *fOut);
    *fOut << "#define FAUST_INT_CONTROLS " << fIntControl->fCurIndex << endl;
    *fOut << "#define FAUST_REAL_CONTROLS " << fRealControl->fCurIndex << endl;
    
    tab(n, *fOut);
    // int_zone_size and real_zone_size contains the size used for tables, DLs and iConst/fConst variables
    *fOut << "#define FAUST_INT_ZONE " << int_zone_size << endl;
    *fOut << "#define FAUST_FLOAT_ZONE " << real_zone_size;
    tab(n, *fOut);
    
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
    if (gGlobal->gInPlace) {
        *fOut << "void compute" << fKlassName << "(" << fKlassName
              << subst("* dsp, int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
    } else {
        *fOut << "void compute" << fKlassName << "(" << fKlassName
              << subst("* dsp, int $0, $1** RESTRICT inputs, $1** RESTRICT outputs) {", fFullCount, xfloat());
    }
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

// Used with -os0 option
void CScalarOneSampleCodeContainer1::generateComputeAux(int n)
{
    // Generates declaration
    tab(n, *fOut);
    if (gGlobal->gInPlace) {
        *fOut << "void compute" << fKlassName << "(" << fKlassName
        << subst("* dsp, $0* inputs, $0* outputs, int* RESTRICT iControl, $1* RESTRICT fControl) {", xfloat(), ifloat());
    } else {
        *fOut << "void compute" << fKlassName << "(" << fKlassName
        << subst("* dsp, $0* RESTRICT inputs, $0* RESTRICT outputs, int* RESTRICT iControl, $1* RESTRICT fControl) {", xfloat(), ifloat());
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

// Used with -os1 and -os2 option
void CScalarOneSampleCodeContainer2::generateComputeAux(int n)
{
    // Generates declaration
    tab(n, *fOut);
    if (gGlobal->gInPlace) {
        *fOut << "void compute" << fKlassName << "(" << fKlassName
        << subst("* dsp, $0* inputs, $0* outputs, int* RESTRICT iControl, $1* RESTRICT fControl, int* RESTRICT iZone, $1* RESTRICT fZone) {", xfloat(), ifloat());
        
    } else {
        *fOut << "void compute" << fKlassName << "(" << fKlassName
        << subst("* dsp, $0* RESTRICT inputs, $0* RESTRICT outputs, int* RESTRICT iControl, $1* RESTRICT fControl, int* RESTRICT iZone, $1* RESTRICT fZone) {", xfloat(), ifloat());
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

// Used with -os3 option
void CScalarOneSampleCodeContainer4::generateComputeAux(int n)
{
    // Generates declaration
    tab(n, *fOut);
    if (gGlobal->gInPlace) {
        *fOut << "void compute" << fKlassName << "(" << fKlassName
              << subst("* dsp, $0* inputs, $0* outputs) {", xfloat());
        
    } else {
        *fOut << "void compute" << fKlassName << "(" << fKlassName
              << subst("* dsp, $0* RESTRICT inputs, $0* RESTRICT outputs) {", xfloat());
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
    if (gGlobal->gInPlace) {
        *fOut << "void compute" << fKlassName << "(" << fKlassName
              << subst("* dsp, int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
    } else {
        *fOut << "void compute" << fKlassName << "(" << fKlassName
              << subst("* dsp, int $0, $1** RESTRICT inputs, $1** RESTRICT outputs) {", fFullCount, xfloat());
    }
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
    if (gGlobal->gInPlace) {
        *fOut << "void compute" << fKlassName << "(" << fKlassName
        << subst("* dsp, int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
    } else {
        *fOut << "void compute" << fKlassName << "(" << fKlassName
        << subst("* dsp, int $0, $1** RESTRICT inputs, $1** RESTRICT outputs) {", fFullCount, xfloat());
    }
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
    if (gGlobal->gInPlace) {
        *fOut << "void compute" << fKlassName << "(" << fKlassName
        << subst("* dsp, int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
    } else {
        *fOut << "void compute" << fKlassName << "(" << fKlassName
        << subst("* dsp, int $0, $1** RESTRICT inputs, $1** RESTRICT outputs) {", fFullCount, xfloat());
    }
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
