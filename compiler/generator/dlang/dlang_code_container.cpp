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

#include "dlang_code_container.hh"
#include "Text.hh"
#include "exception.hh"
#include "fir_to_fir.hh"
#include "floats.hh"
#include "global.hh"

using namespace std;

map<string, bool> DLangInstVisitor::gFunctionSymbolTable;

dsp_factory_base* DLangCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(
        fKlassName, "", "",
        ((dynamic_cast<ostringstream*>(fOut)) ? dynamic_cast<ostringstream*>(fOut)->str() : ""), "");
}

CodeContainer* DLangCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return (gGlobal->gOneSample)
        ? new DLangScalarOneSampleCodeContainer(name, "", 0, 1, fOut, sub_container_type)
        : new DLangScalarCodeContainer(name, "", 0, 1, fOut, sub_container_type);
}

CodeContainer* DLangCodeContainer::createContainer(const string& name, const string& super, int numInputs, int numOutputs,
                                                 ostream* dst)
{
    CodeContainer* container;

    if (gGlobal->gOpenCLSwitch) {
        if (gGlobal->gFunTaskSwitch) {
            throw faustexception("ERROR : -fun not yet supported in OpenCL mode\n");
        }
        if (gGlobal->gVectorSwitch) {
            // container = new DLangOpenCLVectorCodeContainer(name, super, numInputs, numOutputs, dst);
        } else {
            // container = new DLangOpenCLCodeContainer(name, super, numInputs, numOutputs, dst);
        }
    } else if (gGlobal->gCUDASwitch) {
        if (gGlobal->gFunTaskSwitch) {
            throw faustexception("ERROR : -fun not yet supported in CUDA mode\n");
        }
        if (gGlobal->gVectorSwitch) {
            // container = new DLangCUDAVectorCodeContainer(name, super, numInputs, numOutputs, dst);
        } else {
            // container = new DLangCUDACodeContainer(name, super, numInputs, numOutputs, dst);
        }
    } else if (gGlobal->gOpenMPSwitch) {
        container = new DLangOpenMPCodeContainer(name, super, numInputs, numOutputs, dst);
    } else if (gGlobal->gSchedulerSwitch) {
        container = new DLangWorkStealingCodeContainer(name, super, numInputs, numOutputs, dst);
    } else if (gGlobal->gVectorSwitch) {
        container = new DLangVectorCodeContainer(name, super, numInputs, numOutputs, dst);
    } else {
        container = (gGlobal->gOneSample)
            ? new DLangScalarOneSampleCodeContainer(name, super, numInputs, numOutputs, dst, kInt)
            : new DLangScalarCodeContainer(name, super, numInputs, numOutputs, dst, kInt);
    }

    return container;
}

void DLangCodeContainer::produceMetadata(int tabs)
{
    tab(tabs, *fOut);
    *fOut << "void metadata(Meta* m) { ";

    // We do not want to accumulate metadata from all hierachical levels, so the upper level only is kept
    for (auto& i : gGlobal->gMetaDataSet) {
        if (i.first != tree("author")) {
            tab(tabs + 1, *fOut);
            *fOut << "m.declare(\"" << *(i.first) << "\", " << **(i.second.begin()) << ");";
        } else {
            // But the "author" meta data is accumulated, the upper level becomes the main author and sub-levels become
            // "contributor"
            for (set<Tree>::iterator j = i.second.begin(); j != i.second.end(); j++) {
                if (j == i.second.begin()) {
                    tab(tabs + 1, *fOut);
                    *fOut << "m.declare(\"" << *(i.first) << "\", " << **j << ");";
                } else {
                    tab(tabs + 1, *fOut);
                    *fOut << "m.declare(\""
                          << "contributor"
                          << "\", " << **j << ");";
                }
            }
        }
    }

    tab(tabs, *fOut);
    *fOut << "}" << endl;
}

void DLangCodeContainer::produceInit(int tabs)
{
    if (gGlobal->gMemoryManager) {
        tab(tabs, *fOut);
        *fOut << "void init(int sample_rate) {}";
    } else {
        tab(tabs, *fOut);
        *fOut << "void init(int sample_rate) {";
        tab(tabs + 1, *fOut);
        *fOut << "classInit(sample_rate);";
        tab(tabs + 1, *fOut);
        *fOut << "instanceInit(sample_rate);";
        tab(tabs, *fOut);
        *fOut << "}";
    }

    tab(tabs, *fOut);
    *fOut << "void instanceInit(int sample_rate) {";
    tab(tabs + 1, *fOut);
    *fOut << "instanceConstants(sample_rate);";
    tab(tabs + 1, *fOut);
    *fOut << "instanceResetUserInterface();";
    tab(tabs + 1, *fOut);
    *fOut << "instanceClear();";
    tab(tabs, *fOut);
    *fOut << "}";
}

void DLangCodeContainer::produceInternal()
{
    int n = 0;

    // Global declarations
    tab(n, *fOut);

    fCodeProducer.Tab(n);
    generateGlobalDeclarations(&fCodeProducer);

    *fOut << "class " << fKlassName << " {";

    tab(n + 1, *fOut);

    if (gGlobal->gUIMacroSwitch) {
        tab(n, *fOut);
        *fOut << "  public:";
    } else {
        tab(n, *fOut);
        *fOut << "  private:";
    }
    tab(n + 1, *fOut);
    tab(n + 1, *fOut);

    // Fields
    fCodeProducer.Tab(n + 1);
    generateDeclarations(&fCodeProducer);

    tab(n, *fOut);
    *fOut << "  public:";

    tab(n + 1, *fOut);
    tab(n + 1, *fOut);

    // fKlassName used in method naming for subclasses
    produceInfoFunctions(n + 1, fKlassName, "dsp", true, false, &fCodeProducer);
    
    // TODO
    // generateInstanceInitFun("instanceInit" + fKlassName, true, false)->accept(&fCodeProducer);

    // Inits
    tab(n + 1, *fOut);
    *fOut << "void instanceInit" << fKlassName << "(int sample_rate) {";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateInit(&fCodeProducer);
    generateResetUserInterface(&fCodeProducer);
    generateClear(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}";

    // Fill
    string counter = "count";
    tab(n + 1, *fOut);
    if (fSubContainerType == kInt) {
        tab(n + 1, *fOut);
        *fOut << "void fill" << fKlassName << subst("(int $0, int* " + fTableName + ") {", counter);
    } else {
        tab(n + 1, *fOut);
        *fOut << "void fill" << fKlassName << subst("(int $0, $1* " + fTableName + ") {", counter, ifloat());
    }
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateComputeBlock(&fCodeProducer);
    ForLoopInst* loop = fCurLoop->generateScalarLoop(counter);
    loop->accept(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}";

    /*
    tab(n+1, *fOut);
    fCodeProducer.Tab(n+1);
    generateFillFun("fill" + fKlassName, true, false)->accept(&fCodeProducer);
    */

    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "};" << endl;

    // Memory methods (as globals)
    if (gGlobal->gMemoryManager) {
        tab(n, *fOut);
        *fOut << "static " << fKlassName << "* "
              << "new" << fKlassName << "(dsp_memory_manager* manager) {"
              << " return (" << fKlassName << "*)new(manager->allocate(sizeof(" << fKlassName << "))) " << fKlassName
              << "(); }";
        tab(n, *fOut);
        *fOut << "static void delete" << fKlassName << "(" << fKlassName << "* dsp, dsp_memory_manager* manager) { dsp->~"
              << fKlassName << "(); manager->destroy(dsp); }";
    } else {
        tab(n, *fOut);
        *fOut << "static " << fKlassName << "* "
              << "new" << fKlassName << "() {"
              << " return (" << fKlassName << "*)new " << fKlassName << "(); }";
        tab(n, *fOut);
        *fOut << "static void delete" << fKlassName << "(" << fKlassName << "* dsp) { delete dsp; }";
    }
    tab(n, *fOut);
}

void DLangCodeContainer::produceClass()
{
    int n = 0;
   
    // Libraries
    printLibrary(*fOut);
    *fOut << "module " << fKlassName << ";\n";
    tab(n, *fOut);

    *fOut << "import std.math;\n";
    tab(n, *fOut);

    // Sub containers
    generateSubContainers();

    // Global declarations
    tab(n, *fOut);
    fCodeProducer.Tab(n);
    generateGlobalDeclarations(&fCodeProducer);

    tab(n, *fOut);
    *fOut << "alias FAUSTFLOAT = float;" << endl;
    tab(n, *fOut);

    *fOut << "alias FAUSTCLASS = " << fKlassName << ";" << endl;
    tab(n, *fOut);
    
    tab(n, *fOut);
    *fOut << "class " << fKlassName << " : " << fSuperKlassName << " {";
    
    tab(n + 1, *fOut);

    if (gGlobal->gUIMacroSwitch) {
        tab(n, *fOut);
        *fOut << " public:";
    } else {
        tab(n, *fOut);
        *fOut << " private:";
    }
    tab(n + 1, *fOut);

    // Fields
    fCodeProducer.Tab(n + 1);
    tab(n + 1, *fOut);
    generateDeclarations(&fCodeProducer);

    if (fAllocateInstructions->fCode.size() > 0) {
        tab(n + 1, *fOut);
        *fOut << "void allocate() {";
        tab(n + 2, *fOut);
        fCodeProducer.Tab(n + 2);
        generateAllocate(&fCodeProducer);
        back(1, *fOut);
        *fOut << "}";
        tab(n + 1, *fOut);
    }

    if (fDestroyInstructions->fCode.size() > 0) {
        tab(n + 1, *fOut);
        *fOut << "void destroy() {";
        tab(n + 2, *fOut);
        fCodeProducer.Tab(n + 2);
        generateDestroy(&fCodeProducer);
        back(1, *fOut);
        *fOut << "}";
        tab(n + 1, *fOut);
    }

    tab(n, *fOut);
    *fOut << " public:";

    if (gGlobal->gMemoryManager) {
        tab(n + 1, *fOut);
        *fOut << "static dsp_memory_manager* fManager;";
    }

    // Print metadata declaration
    tab(n + 1, *fOut);
    produceMetadata(n + 1);

    if (fAllocateInstructions->fCode.size() > 0) {
        tab(n + 1, *fOut);
        *fOut << fKlassName << "() {";
        tab(n + 2, *fOut);
        *fOut << "allocate();";
        tab(n + 1, *fOut);
        *fOut << "}" << endl;
    }

    if (fDestroyInstructions->fCode.size() > 0) {
        tab(n + 1, *fOut);
        *fOut << "~" << fKlassName << "() {";
        tab(n + 2, *fOut);
        *fOut << "destroy();";
        tab(n + 1, *fOut);
        *fOut << "}" << endl;
    }

    tab(n + 1, *fOut);
    // No class name for main class
    produceInfoFunctions(n + 1, "", "dsp", true, true, &fCodeProducer);  // Inits

    tab(n + 1, *fOut);
    *fOut << "static void classInit(int sample_rate) {";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateStaticInit(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}";

    if (gGlobal->gMemoryManager) {
        tab(n + 1, *fOut);
        *fOut << "static void classDestroy() {";
        tab(n + 2, *fOut);
        fCodeProducer.Tab(n + 2);
        generateStaticDestroy(&fCodeProducer);
        back(1, *fOut);
        *fOut << "}";
    }

    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << "void instanceConstants(int sample_rate) {";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateInit(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    tab(n + 1, *fOut);
    *fOut << "void instanceResetUserInterface() {";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateResetUserInterface(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    tab(n + 1, *fOut);
    *fOut << "void instanceClear() {";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateClear(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    // Init
    produceInit(n + 1);

    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << fKlassName << "* clone() {";
    tab(n + 2, *fOut);
    *fOut << "return new " << fKlassName << "();";
    tab(n + 1, *fOut);
    *fOut << "}";

    tab(n + 1, *fOut);
    fCodeProducer.Tab(n + 1);
    tab(n + 1, *fOut);
    generateGetSampleRate("getSampleRate", "dsp", true, true)->accept(&fCodeProducer);

    // User interface
    tab(n + 1, *fOut);
    *fOut << "void buildUserInterface(UI* ui_interface) {";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateUserInterface(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}";

    // Compute
    generateCompute(n);
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "}" << endl;

    // To improve (generalization for all backends...)
    if (gGlobal->gMemoryManager) {
        tab(n, *fOut);
        *fOut << "dsp_memory_manager* " << fKlassName << "::fManager = 0;" << endl;
    }

    // Generate user interface macros if needed
    printMacros(*fOut, n);
    
    if (gGlobal->gNameSpace != "" && gGlobal->gArchFile == "") {
        tab(n, *fOut);
        *fOut << "} // namespace " << gGlobal->gNameSpace << endl;
    }
}

// Scalar
DLangScalarCodeContainer::DLangScalarCodeContainer(const string& name, const string& super, int numInputs, int numOutputs,
                                               std::ostream* out, int sub_container_type)
    : DLangCodeContainer(name, super, numInputs, numOutputs, out)
{
    fSubContainerType = sub_container_type;
}

void DLangScalarCodeContainer::generateCompute(int n)
{
    // Generates declaration
    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << subst("void compute(int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);

    // Generates local variables declaration and setup
    generateComputeBlock(&fCodeProducer);
   
    // Generates one single scalar loop
    ForLoopInst* loop = fCurLoop->generateScalarLoop(fFullCount);
    loop->accept(&fCodeProducer);
   
    /*
     // TODO : atomic switch
     // Currently for soundfile management
     */
    generatePostComputeBlock(&fCodeProducer);

    back(1, *fOut);
    *fOut << "}";
}

// One Sample Scalar

void DLangScalarOneSampleCodeContainer::generateCompute(int n)
{
    // Generates declaration
    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << subst("void compute($0* inputs, $0* outputs, int* iControl, $0* fControl) {", xfloat());
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    
    // Generates one sample computation
    BlockInst* block = fCurLoop->generateOneSample();
    block->accept(&fCodeProducer);
    
    /*
     // TODO : atomic switch
     // Currently for soundfile management
     */
    generatePostComputeBlock(&fCodeProducer);
    
    back(1, *fOut);
    *fOut << "}";
}

void DLangScalarOneSampleCodeContainer::produceClass()
{
    int n = 0;
   
    // Libraries
    printLibrary(*fOut);
    printIncludeFile(*fOut);
    
    if (gGlobal->gNameSpace != "" && gGlobal->gArchFile == "") {
        tab(n, *fOut);
        *fOut << "namespace " << gGlobal->gNameSpace << " {" << endl;
    }
 
    // Sub containers
    generateSubContainers();
    
    // Global declarations
    tab(n, *fOut);
    fCodeProducer.Tab(n);
    generateGlobalDeclarations(&fCodeProducer);
    
    tab(n, *fOut);
    *fOut << "#alias FAUSTCLASS = " << fKlassName << endl;
    tab(n, *fOut);
    
    *fOut << "enum FAUST_INPUTS = " << fNumInputs << endl;
    *fOut << "enum FAUST_OUTPUTS = " << fNumOutputs << endl;
    *fOut << "enum FAUST_INT_CONTROLS = " << fInt32ControlNum  << endl;
    *fOut << "enum FAUST_REAL_CONTROLS = " << fRealControlNum;
    tab(n, *fOut);
    fSuperKlassName = "one_sample_dsp";
    
    tab(n, *fOut);
    *fOut << "class " << fKlassName << " : public " << fSuperKlassName << " {";
    tab(n + 1, *fOut);
    
    if (gGlobal->gUIMacroSwitch) {
        tab(n, *fOut);
        *fOut << " public:";
    } else {
        tab(n, *fOut);
        *fOut << " private:";
    }
    tab(n + 1, *fOut);
    
    // Fields
    fCodeProducer.Tab(n + 1);
    tab(n + 1, *fOut);
    generateDeclarations(&fCodeProducer);
    
    if (fAllocateInstructions->fCode.size() > 0) {
        tab(n + 1, *fOut);
        *fOut << "void allocate() {";
        tab(n + 2, *fOut);
        fCodeProducer.Tab(n + 2);
        generateAllocate(&fCodeProducer);
        back(1, *fOut);
        *fOut << "}";
        tab(n + 1, *fOut);
    }
    
    if (fDestroyInstructions->fCode.size() > 0) {
        tab(n + 1, *fOut);
        *fOut << "void destroy() {";
        tab(n + 2, *fOut);
        fCodeProducer.Tab(n + 2);
        generateDestroy(&fCodeProducer);
        back(1, *fOut);
        *fOut << "}";
        tab(n + 1, *fOut);
    }
    
    tab(n, *fOut);
    *fOut << " public:";
    
    if (gGlobal->gMemoryManager) {
        tab(n + 1, *fOut);
        *fOut << "static dsp_memory_manager* fManager;";
    }
    
    // Print metadata declaration
    tab(n + 1, *fOut);
    produceMetadata(n + 1);
    
    if (fAllocateInstructions->fCode.size() > 0) {
        tab(n + 1, *fOut);
        *fOut << fKlassName << "() {";
        tab(n + 2, *fOut);
        *fOut << "allocate();";
        tab(n + 1, *fOut);
        *fOut << "}" << endl;
    }
    
    if (fDestroyInstructions->fCode.size() > 0) {
        tab(n + 1, *fOut);
        *fOut << "~" << fKlassName << "() {";
        tab(n + 2, *fOut);
        *fOut << "destroy();";
        tab(n + 1, *fOut);
        *fOut << "}" << endl;
    }
    
    tab(n + 1, *fOut);
    // No class name for main class
    produceInfoFunctions(n + 1, "", "dsp", true, true, &fCodeProducer);  // Inits
    
    tab(n + 1, *fOut);
    *fOut << "static void classInit(int sample_rate) {";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateStaticInit(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    
    if (gGlobal->gMemoryManager) {
        tab(n + 1, *fOut);
        *fOut << "static void classDestroy() {";
        tab(n + 2, *fOut);
        fCodeProducer.Tab(n + 2);
        generateStaticDestroy(&fCodeProducer);
        back(1, *fOut);
        *fOut << "}";
    }
  
    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << "void instanceConstants(int sample_rate) {";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateInit(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << "void instanceResetUserInterface() {";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateResetUserInterface(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << "void instanceClear() {";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateClear(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    // Init
    produceInit(n + 1);
    
    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << fKlassName << "* clone() {";
    tab(n + 2, *fOut);
    *fOut << "return new " << fKlassName << "();";
    tab(n + 1, *fOut);
    *fOut << "}";
    
    tab(n + 1, *fOut);
    fCodeProducer.Tab(n + 1);
    tab(n + 1, *fOut);
    generateGetSampleRate("getSampleRate", "dsp", true, true)->accept(&fCodeProducer);
    
    // User interface
    tab(n + 1, *fOut);
    *fOut << "void buildUserInterface(UI* ui_interface) {";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateUserInterface(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    
    tab(n + 1, *fOut);
    *fOut << subst("void control(int* iControl, $0* fControl) {", xfloat());
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    // Generates local variables declaration and setup
    generateComputeBlock(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}" << endl;
    
    tab(n + 1, *fOut);
    *fOut << "int getNumIntControls() { return " << fInt32ControlNum << "; }";
    tab(n + 1, *fOut);
    *fOut << "int getNumRealControls() { return " << fRealControlNum << "; }";
    
    // Compute
    generateCompute(n);
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "};" << endl;
    
    // To improve (generalization for all backends...)
    if (gGlobal->gMemoryManager) {
        tab(n, *fOut);
        *fOut << "dsp_memory_manager* " << fKlassName << "::fManager = 0;" << endl;
    }
    
    // Generate user interface macros if needed
    printMacros(*fOut, n);
    
    if (gGlobal->gNameSpace != "" && gGlobal->gArchFile == "") {
        tab(n, *fOut);
        *fOut << "} // namespace " << gGlobal->gNameSpace << endl;
    }
}

// Vector
DLangVectorCodeContainer::DLangVectorCodeContainer(const string& name, const string& super, int numInputs, int numOutputs,
                                               std::ostream* out)
    : VectorCodeContainer(numInputs, numOutputs), DLangCodeContainer(name, super, numInputs, numOutputs, out)
{
}

void DLangVectorCodeContainer::generateCompute(int n)
{
    // Possibly generate separated functions
    fCodeProducer.Tab(n + 1);
    tab(n + 1, *fOut);
    generateComputeFunctions(&fCodeProducer);

    // Generates declaration
    tab(n + 1, *fOut);
    *fOut << subst("void compute(int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);

    // Generates local variables declaration and setup
    generateComputeBlock(&fCodeProducer);

    // Generates the DSP loop
    fDAGBlock->accept(&fCodeProducer);

    back(1, *fOut);
    *fOut << "}";
}

// OpenMP
DLangOpenMPCodeContainer::DLangOpenMPCodeContainer(const string& name, const string& super, int numInputs, int numOutputs,
                                               std::ostream* out)
    : OpenMPCodeContainer(numInputs, numOutputs), DLangCodeContainer(name, super, numInputs, numOutputs, out)
{
}

void DLangOpenMPCodeContainer::generateCompute(int n)
{
    // Possibly generate separated functions
    fCodeProducer.Tab(n + 1);
    tab(n + 1, *fOut);
    generateComputeFunctions(&fCodeProducer);

    // Generates declaration
    tab(n + 1, *fOut);
    *fOut << subst("void compute(int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);

    // Generates local variables declaration and setup
    generateComputeBlock(&fCodeProducer);

    // Generate DSP loop
    fGlobalLoopBlock->accept(&fCodeProducer);

    back(1, *fOut);
    *fOut << "}";
}

// Works stealing scheduler
DLangWorkStealingCodeContainer::DLangWorkStealingCodeContainer(const string& name, const string& super, int numInputs,
                                                           int numOutputs, std::ostream* out)
    : WSSCodeContainer(numInputs, numOutputs, "this"), DLangCodeContainer(name, super, numInputs, numOutputs, out)
{
}

void DLangWorkStealingCodeContainer::produceClass()
{
    int n = 0;

    // Inherited method
    DLangCodeContainer::produceClass();

    tab(n, *fOut);
    *fOut << "extern \"C\" void computeThreadExternal(void* dsp, int num_thread) {";
    tab(n + 1, *fOut);
    *fOut << "static_cast<" << fKlassName << "*>(dsp)->computeThread" << fKlassName << "(num_thread);";
    tab(n, *fOut);
    *fOut << "}" << endl;
}

void DLangWorkStealingCodeContainer::generateCompute(int n)
{
    // Possibly generate separated functions
    fCodeProducer.Tab(n + 1);
    tab(n + 1, *fOut);
    generateComputeFunctions(&fCodeProducer);

    // Generates declaration
    tab(n + 1, *fOut);
    *fOut << subst("void compute(int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);

    // Generates local variables declaration and setup
    generateComputeBlock(&fCodeProducer);

    //tab(n + 1, *fOut);
    back(1, *fOut);
    *fOut << "}" << endl;

    // Generates "computeThread" code
    tab(n + 1, *fOut);
    *fOut << "void computeThread" << fKlassName << "(int num_thread) {";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);

    // Generate it
    faustassert(fThreadLoopBlock);
    fThreadLoopBlock->accept(&fCodeProducer);

    back(1, *fOut);
    *fOut << "}";
}
