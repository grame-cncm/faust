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

#include "Text.hh"
#include "c_code_container.hh"
#include "exception.hh"
#include "fir_function_builder.hh"
#include "floats.hh"
#include "global.hh"

using namespace std;

/*
 C backend and module description:

    1) in -os mode: a 'frame' function is generated
    2) in -ec mode: a 'control' function is generated, with a empty 'compute'
    3) in -mem3 mode: a minimal subset of functions are generated
    4) in -fx mode:
         - then/else branches of 'select2' are explicitly casted to 'float', otherwise AP_fixed
 compilation may trigger "ambigous type" errors
         - all math operators are named "FOOfx" and are supposed to be implemented in the
 architecture file (doing the proper cast on arguments and return value when needed)
 */

map<string, bool> CInstVisitor::gFunctionSymbolTable;

dsp_factory_base* CCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(
        fKlassName, "", "",
        ((dynamic_cast<ostringstream*>(fOut)) ? dynamic_cast<ostringstream*>(fOut)->str() : ""),
        "");
}

CodeContainer* CCodeContainer::createScalarContainer(const std::string& name, int numInputs,
                                                     int numOutputs, ostream* dst,
                                                     int sub_container_type)
{
    return new CScalarCodeContainer(name, numInputs, numOutputs, dst, sub_container_type);
}

CodeContainer* CCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return createScalarContainer(name, 0, 1, fOut, sub_container_type);
}

CodeContainer* CCodeContainer::createContainer(const string& name, int numInputs, int numOutputs,
                                               ostream* dst)
{
    gGlobal->gDSPStruct = true;  // for -vec -fun mode
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
        if (gGlobal->gMemoryManager == 3) {
            // Special version for SYFALA
            container = new CVectorCodeContainer1(name, numInputs, numOutputs, dst);
        } else {
            container = new CVectorCodeContainer(name, numInputs, numOutputs, dst);
        }
    } else if (gGlobal->gMemoryManager == 3) {
        // Special version for SYFALA
        container = new CScalarCodeContainer1(name, numInputs, numOutputs, dst, kInt);
    } else {
        container = createScalarContainer(name, numInputs, numOutputs, dst, kInt);
    }

    return container;
}

void CCodeContainer::produceInit(int tabs)
{
    tab(tabs, *fOut);
    *fOut << "void instanceInit" << fKlassName << "(" << fKlassName << "* dsp, int sample_rate) {";
    tab(tabs + 1, *fOut);
    // staticInit has to be called for each instance since the tables are actually not shared
    // between instances
    if (gGlobal->gInlineTable) {
        *fOut << "staticInit" << fKlassName << "(dsp, sample_rate);";
        tab(tabs + 1, *fOut);
    }
    *fOut << "instanceConstants" << fKlassName << "(dsp, sample_rate);";
    tab(tabs + 1, *fOut);
    if (gGlobal->gMemoryManager == 2) {
        *fOut << "instanceConstantsToMem" << fKlassName << "(dsp, sample_rate);";
        tab(tabs + 1, *fOut);
    }
    *fOut << "instanceResetUserInterface" << fKlassName << "(dsp);";
    tab(tabs + 1, *fOut);
    *fOut << "instanceClear" << fKlassName << "(dsp);";
    tab(tabs, *fOut);
    *fOut << "}";

    tab(tabs, *fOut);
    if (gGlobal->gMemoryManager >= 0) {
        tab(tabs, *fOut);
        *fOut << "void init" << fKlassName << "(" << fKlassName << "* dsp, int sample_rate) {}";
    } else {
        tab(tabs, *fOut);
        *fOut << "void init" << fKlassName << "(" << fKlassName << "* dsp, int sample_rate) {";
        tab(tabs + 1, *fOut);
        // Replaced by staticInit called in instanceInit
        if (!gGlobal->gInlineTable) {
            *fOut << "classInit" << fKlassName << "(sample_rate);";
            tab(tabs + 1, *fOut);
        }
        *fOut << "instanceInit" << fKlassName << "(dsp, sample_rate);";
        tab(tabs, *fOut);
        *fOut << "}";
    }
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
    *fOut << "static void instanceInit" << fKlassName << "(" << fKlassName
          << "* dsp, int sample_rate) {";
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

    if (gGlobal->gInlineTable) {
        // Sub containers are merged in the main class
        mergeSubContainers();
    } else {
        // Generate sub containers
        generateSubContainers();
    }

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
    }

    tab(n, *fOut);
    *fOut << "typedef struct {";
    tab(n + 1, *fOut);
    // Fields
    fCodeProducer->Tab(n + 1);
    // DSP fields as flat arrays are rewritten as pointers
    if (gGlobal->gMemoryManager == 0) {
        // All arrays are rewritten as pointers
        ArrayToPointer array_pointer;
        array_pointer.getCode(fDeclarationInstructions)->accept(fCodeProducer);
    } else if (gGlobal->gMemoryManager >= 1) {
        // Only "iControl", "fControl", "iZone", "fZone" are rewritten as pointers
        ArrayToPointer1 array_pointer;
        array_pointer.getCode(fDeclarationInstructions)->accept(fCodeProducer);
    } else {
        generateDeclarations(fCodeProducer);
    }
    back(1, *fOut);
    *fOut << "} " << fKlassName << ";";

    // Memory methods
    tab(n, *fOut);

    generateAllocateFun(n);
    tab(n, *fOut);
    generateDestroyFun(n);

    // iControl/fControl and iZone/fZone are given as parameters,
    // in the constructors and in an additional setMemory method.
    // The really needed one only will be set.

    if (gGlobal->gMemoryManager == 2) {
        bool int_control  = (fIntControl) ? fIntControl->getSize() > 0 : false;
        bool real_control = (fRealControl) ? fRealControl->getSize() > 0 : false;
        bool int_zone     = gGlobal->gIntZone->getSize() > 0;
        bool real_zone    = gGlobal->gRealZone->getSize() > 0;

        // Constructor
        *fOut << fKlassName << "* new" << fKlassName << "(int* icontrol, " << ifloat()
              << "* fcontrol, int* izone, " << ifloat() << "* fzone) {";
        tab(n + 1, *fOut);
        *fOut << fKlassName << "* dsp = (" << fKlassName << "*)calloc(1, sizeof(" << fKlassName
              << "));";
        if (fAllocateInstructions->fCode.size() > 0) {
            tab(n + 1, *fOut);
            *fOut << "allocate" << fKlassName << "(dsp);";
        }
        if (int_control) {
            tab(n + 1, *fOut);
            *fOut << "dsp->iControl = icontrol;";
        }
        if (real_control) {
            tab(n + 1, *fOut);
            *fOut << "dsp->fControl = fcontrol;";
        }
        if (int_zone) {
            tab(n + 1, *fOut);
            *fOut << "dsp->iZone = izone;";
        }
        if (real_zone) {
            tab(n + 1, *fOut);
            *fOut << "dsp->fZone = fzone;";
        }
        tab(n + 1, *fOut);
        *fOut << "return dsp;";
        tab(n, *fOut);
        *fOut << "}";

        // setMemory
        tab(n, *fOut);
        *fOut << "void setMemory" << fKlassName << "(" << fKlassName << "* dsp, int* icontrol, "
              << ifloat() << "* fcontrol, int* izone, " << ifloat() << "* fzone) {";
        if (int_control) {
            tab(n + 1, *fOut);
            *fOut << "dsp->iControl = icontrol;";
        }
        if (real_control) {
            tab(n + 1, *fOut);
            *fOut << "dsp->fControl = fcontrol;";
        }
        if (int_zone) {
            tab(n + 1, *fOut);
            *fOut << "dsp->iZone = izone;";
        }
        if (real_zone) {
            tab(n + 1, *fOut);
            *fOut << "dsp->fZone = fzone;";
        }
        tab(n, *fOut);
        *fOut << "}";

    } else {
        // Default constructor
        *fOut << fKlassName << "* new" << fKlassName << "() { ";
        tab(n + 1, *fOut);
        *fOut << fKlassName << "* dsp = (" << fKlassName << "*)calloc(1, sizeof(" << fKlassName
              << "));";
        if (fAllocateInstructions->fCode.size() > 0) {
            tab(n + 1, *fOut);
            *fOut << "allocate" << fKlassName << "(dsp);";
        }
        tab(n + 1, *fOut);
        *fOut << "return dsp;";
        tab(n, *fOut);
        *fOut << "}";
    }

    // Destructor
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
    if (gGlobal->gInlineTable) {
        // Empty classInit
        *fOut << "void classInit" << fKlassName << "(int sample_rate) {}";
        tab(n, *fOut);
        // To be used in instanceInit
        tab(n, *fOut);
        *fOut << "void staticInit" << fKlassName << "(" << fKlassName
              << "* dsp, int sample_rate) {";
        {
            tab(n + 1, *fOut);
            // Local visitor here to avoid DSP object incorrect type generation
            CInstVisitor codeproducer(fOut, "");
            codeproducer.Tab(n + 1);
            fStaticInitInstructions->accept(&codeproducer);
        }
        back(1, *fOut);
        *fOut << "}";
    } else {
        *fOut << "void classInit" << fKlassName << "(int sample_rate) {";
        tab(n + 1, *fOut);
        // Local visitor here to avoid DSP object incorrect type generation
        CInstVisitor codeproducer(fOut, "");
        codeproducer.Tab(n + 1);
        generateStaticInit(&codeproducer);
        back(1, *fOut);
        *fOut << "}";
    }

    if (gGlobal->gMemoryManager >= 0) {
        tab(n, *fOut);
        tab(n, *fOut);
        *fOut << "void classDestroy" << fKlassName << "() {";
        tab(n + 1, *fOut);
        fCodeProducer->Tab(n + 2);
        generateStaticDestroy(fCodeProducer);
        back(1, *fOut);
        *fOut << "}";
    }

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
    *fOut << "void instanceConstants" << fKlassName << "(" << fKlassName
          << "* dsp, int sample_rate) {";
    {
        tab(n + 1, *fOut);
        // Local visitor here to avoid DSP object incorrect type generation
        CInstVisitor codeproducer(fOut, "");
        codeproducer.Tab(n + 1);
        if (gGlobal->gInlineTable) {
            // 'delete' instruction which are in fPostInitInstructions are not generated
            fInitInstructions->accept(&codeproducer);
        } else {
            generateInit(&codeproducer);
        }
    }
    back(1, *fOut);
    *fOut << "}";

    if (gGlobal->gMemoryManager == 2) {
        tab(n, *fOut);
        *fOut << "void instanceConstantsFromMem" << fKlassName << "(" << fKlassName
              << "* dsp, int sample_rate) {";
        tab(n + 1, *fOut);
        faustassert(fConstantFromMem);
        fCodeProducer->Tab(n + 1);
        fConstantFromMem->accept(fCodeProducer);
        back(1, *fOut);
        *fOut << "}";

        tab(n, *fOut);
        *fOut << "void instanceConstantsToMem" << fKlassName << "(" << fKlassName
              << "* dsp, int sample_rate) {";
        tab(n + 1, *fOut);
        faustassert(fConstantToMem);
        fCodeProducer->Tab(n + 1);
        fConstantToMem->accept(fCodeProducer);
        back(1, *fOut);
        *fOut << "}";
    }
    tab(n + 1, *fOut);

    // Init
    produceInit(n);

    // User interface
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "void buildUserInterface" << fKlassName << "(" << fKlassName
          << "* dsp, UIGlue* ui_interface) {";
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);
    generateUserInterface(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";

    // Control
    if (gGlobal->gExtControl) {
        tab(n, *fOut);
        tab(n, *fOut);
        *fOut << "void control" << fKlassName << "(" << fKlassName << "* dsp) {";
        tab(n + 1, *fOut);
        fCodeProducer->Tab(n + 1);
        generateControlDeclarations(fCodeProducer);
        back(1, *fOut);
        *fOut << "}";
    }

    // Frame
    if (gGlobal->gOneSample) {
        // Generates declaration
        tab(n, *fOut);
        tab(n, *fOut);
        if (gGlobal->gInPlace) {
            *fOut << "void frame" << fKlassName << "(" << fKlassName
                  << subst("* dsp, $0* inputs, $0* outputs) {", xfloat());
        } else {
            *fOut << "void frame" << fKlassName << "(" << fKlassName
                  << subst("* dsp, $0* RESTRICT inputs, $0* RESTRICT outputs) {", xfloat());
        }

        tab(n + 1, *fOut);
        fCodeProducer->Tab(n + 1);

        if (!gGlobal->gExtControl) {
            // Generates local variables declaration and setup
            generateComputeBlock(fCodeProducer);
        }

        // Generates one sample computation
        BlockInst* block = fCurLoop->generateOneSample();
        block->accept(fCodeProducer);

        /*
         // TODO : atomic switch
         // Currently for soundfile management
         */
        generatePostComputeBlock(fCodeProducer);

        back(1, *fOut);
        *fOut << "}";
        tab(n, *fOut);

        // Empty compute
        tab(n, *fOut);
        if (gGlobal->gInPlace) {
            *fOut << "void compute" << fKlassName << "(" << fKlassName
                  << subst("* dsp, int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
            *fOut << "}" << endl;
        } else {
            *fOut << "void compute" << fKlassName << "(" << fKlassName
                  << subst("* dsp, int $0, $1** RESTRICT inputs, $1** RESTRICT outputs) {",
                           fFullCount, xfloat());
            *fOut << "}" << endl;
        }
    } else {
        // Compute
        generateCompute(n);
    }

    if (gGlobal->gMemoryManager == 2) {
        tab(n, *fOut);
        *fOut << "#define FAUST_INT_CONTROLS " << ((fIntControl) ? fIntControl->getSize() : 0)
              << endl;
        *fOut << "#define FAUST_REAL_CONTROLS " << ((fRealControl) ? fRealControl->getSize() : 0)
              << endl;

        tab(n, *fOut);
        // gIntZone and gRealZone contain the size used for tables, DLs and iConst/fConst variables
        *fOut << "#define FAUST_INT_ZONE " << gGlobal->gIntZone->getSize() << endl;
        *fOut << "#define FAUST_FLOAT_ZONE " << gGlobal->gRealZone->getSize();
        tab(n, *fOut);
    }

    // Generate user interface macros if needed
    printMacros(*fOut, n);

    tab(n, *fOut);
    *fOut << "#ifdef __cplusplus" << endl;
    *fOut << "}" << endl;
    *fOut << "#endif" << endl;
}

void CScalarCodeContainer1::produceClass()
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

    // Sub containers are merged in the main class
    faustassert(gGlobal->gInlineTable);
    mergeSubContainers();

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

    // Generate user interface macros if needed
    printMacros(*fOut, n);

    tab(n, *fOut);
    *fOut << "typedef struct {";
    tab(n + 1, *fOut);
    // Fields
    fCodeProducer->Tab(n + 1);
    // Only "iControl", "fControl", "iZone", "fZone" are rewritten as pointers, remove input
    // controls
    NoControlArrayToPointer array_pointer;
    array_pointer.getCode(fDeclarationInstructions)->accept(fCodeProducer);
    back(1, *fOut);
    *fOut << "} " << fKlassName << ";";

    // Memory methods
    tab(n, *fOut);

    generateAllocateFun(n);
    tab(n, *fOut);
    generateDestroyFun(n);

    *fOut << "void instanceConstantsFromMem" << fKlassName << "(" << fKlassName
          << "* dsp, int sample_rate, "
          << subst("int* RESTRICT iZone, $0* RESTRICT fZone) {", ifloat());
    tab(n + 1, *fOut);
    faustassert(fConstantFromMem);
    fCodeProducer->Tab(n + 1);
    fConstantFromMem->accept(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n, *fOut);

    // Frame
    if (gGlobal->gOneSample) {
        // Generates declaration
        tab(n, *fOut);
        if (gGlobal->gInPlace) {
            *fOut << "void frame" << fKlassName << "(" << fKlassName
                  << subst("* dsp, $0* inputs, $0* outputs) {", xfloat());
        } else {  // SYFALA mode
            *fOut
                << "void frame" << fKlassName << "(" << fKlassName
                << subst(
                       "* dsp, $0* RESTRICT inputs, $0* RESTRICT outputs, int* RESTRICT iControl, "
                       "$0* RESTRICT fControl, int* RESTRICT iZone, $0* RESTRICT fZone) {",
                       xfloat());
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
        *fOut << "}";
        tab(n, *fOut);

    } else {
        // Compute
        generateCompute(n);
    }

    tab(n, *fOut);
    *fOut << "#define FAUST_INT_CONTROLS " << ((fIntControl) ? fIntControl->getSize() : 0) << endl;
    *fOut << "#define FAUST_REAL_CONTROLS " << ((fRealControl) ? fRealControl->getSize() : 0)
          << endl;

    tab(n, *fOut);
    // gIntZone and gRealZone contain the size used for tables, DLs and iConst/fConst variables
    *fOut << "#define FAUST_INT_ZONE " << gGlobal->gIntZone->getSize() << endl;
    *fOut << "#define FAUST_FLOAT_ZONE " << gGlobal->gRealZone->getSize();
    tab(n, *fOut);

    tab(n, *fOut);
    *fOut << "#ifdef __cplusplus" << endl;
    *fOut << "}" << endl;
    *fOut << "#endif" << endl;
}

void CCodeContainer::produceMetadata(int tabs)
{
    tab(tabs, *fOut);
    *fOut << "void metadata" << fKlassName << "(MetaGlue* m) { ";

    // We do not want to accumulate metadata from all hierachical levels, so the upper level only is
    // kept
    for (const auto& i : gGlobal->gMetaDataSet) {
        if (i.first != tree("author")) {
            tab(tabs + 1, *fOut);
            *fOut << "m->declare(m->metaInterface, \"" << *(i.first) << "\", "
                  << **(i.second.begin()) << ");";
        } else {
            // But the "author" meta data is accumulated, the upper level becomes the main author
            // and sub-levels become "contributor"
            for (set<Tree>::iterator j = i.second.begin(); j != i.second.end(); j++) {
                if (j == i.second.begin()) {
                    tab(tabs + 1, *fOut);
                    *fOut << "m->declare(m->metaInterface, \"" << *(i.first) << "\", " << **j
                          << ");";
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
CScalarCodeContainer::CScalarCodeContainer(const string& name, int numInputs, int numOutputs,
                                           std::ostream* out, int sub_container_type)
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
              << subst("* dsp, int $0, $1** RESTRICT inputs, $1** RESTRICT outputs) {", fFullCount,
                       xfloat());
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

void CScalarCodeContainer1::generateComputeAux(int n)
{
    // Generates declaration
    *fOut << "void computeBlock" << fKlassName << "(" << fKlassName
          << subst(
                 "* dsp, $0 inputs[FAUST_INPUTS][$1], $0 "
                 "outputs[FAUST_OUTPUTS][$1], int* RESTRICT iControl, $0* RESTRICT "
                 "fControl, int* RESTRICT iZone, $0* RESTRICT fZone) {",
                 xfloat(), std::to_string(gGlobal->gVecSize));

    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);

    // Generates local variables declaration and setup
    generateComputeBlock(fCodeProducer);

    // Generates one single scalar loop
    ForLoopInst* loop = fCurLoop->generateFixedScalarLoop();
    loop->accept(fCodeProducer);

    /*
     // TODO : atomic switch
     // Currently for soundfile management
     */
    generatePostComputeBlock(fCodeProducer);

    back(1, *fOut);
    *fOut << "}" << endl;
}

// Vector
CVectorCodeContainer::CVectorCodeContainer(const string& name, int numInputs, int numOutputs,
                                           std::ostream* out)
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
              << subst("* dsp, int $0, $1** RESTRICT inputs, $1** RESTRICT outputs) {", fFullCount,
                       xfloat());
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

CVectorCodeContainer1::CVectorCodeContainer1(const string& name, int numInputs, int numOutputs,
                                             std::ostream* out)
    : VectorCodeContainer(numInputs, numOutputs),
      CScalarCodeContainer1(name, numInputs, numOutputs, out, kInt)
{
}

void CVectorCodeContainer1::generateComputeAux(int n)
{
    // Generates declaration
    *fOut << "void computeBlock" << fKlassName << "(" << fKlassName
          << subst(
                 "* dsp, $0 inputs[FAUST_INPUTS][$1], $0 "
                 "outputs[FAUST_OUTPUTS][$1], int* RESTRICT iControl, $0* RESTRICT "
                 "fControl, int* RESTRICT iZone, $0* RESTRICT fZone) {",
                 xfloat(), std::to_string(gGlobal->gVecSize));

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
COpenMPCodeContainer::COpenMPCodeContainer(const string& name, int numInputs, int numOutputs,
                                           std::ostream* out)
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
              << subst("* dsp, int $0, $1** RESTRICT inputs, $1** RESTRICT outputs) {", fFullCount,
                       xfloat());
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
CWorkStealingCodeContainer::CWorkStealingCodeContainer(const string& name, int numInputs,
                                                       int numOutputs, std::ostream* out)
    : WSSCodeContainer(numInputs, numOutputs, "dsp"),
      CCodeContainer(name, numInputs, numOutputs, out)
{
}

void CWorkStealingCodeContainer::generateComputeAux(int n)
{
    // Generates "computeThread" code
    tab(n, *fOut);
    *fOut << "static void computeThread" << fKlassName << "(" << fKlassName
          << "* dsp, int num_thread) {";
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
              << subst("* dsp, int $0, $1** RESTRICT inputs, $1** RESTRICT outputs) {", fFullCount,
                       xfloat());
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
