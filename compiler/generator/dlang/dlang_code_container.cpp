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
    return (gGlobal->gOneSample >= 0)
        ? new DLangScalarOneSampleCodeContainer(name, "", 0, 1, fOut, sub_container_type)
        : new DLangScalarCodeContainer(name, "", 0, 1, fOut, sub_container_type);
}

CodeContainer* DLangCodeContainer::createContainer(const string& name, const string& super, int numInputs,
                                                  int numOutputs, ostream* dst)
{
    CodeContainer* container;

    if (gGlobal->gFloatSize == 3) {
        throw faustexception("ERROR : -quad format not supported for D\n");
    }
    if (gGlobal->gOpenCLSwitch) {
        throw faustexception("ERROR : OpenCL not supported for D\n");
    }
    if (gGlobal->gCUDASwitch) {
        throw faustexception("ERROR : CUDA not supported for D\n");
    }

    if (gGlobal->gOpenMPSwitch) {
        throw faustexception("ERROR : OpenMP not supported for D\n");
    } else if (gGlobal->gSchedulerSwitch) {
        throw faustexception("ERROR : Scheduler not supported for D\n");
    } else if (gGlobal->gVectorSwitch) {
        container = new DLangVectorCodeContainer(name, super, numInputs, numOutputs, dst);
    } else {
        container = (gGlobal->gOneSample >= 0)
            ? new DLangScalarOneSampleCodeContainer(name, super, numInputs, numOutputs, dst, kInt)
            : new DLangScalarCodeContainer(name, super, numInputs, numOutputs, dst, kInt);
    }

    return container;
}

void DLangCodeContainer::produceMetadata(int tabs)
{
    tab(tabs, *fOut);
    *fOut << "void metadata(Meta* m) nothrow @nogc { ";

    // We do not want to accumulate metadata from all hierachical levels, so the upper level only is kept
    for (const auto& i : gGlobal->gMetaDataSet) {
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

    tab(tabs, *fOut);
    *fOut << "void initialize(int sample_rate) nothrow @nogc {";
    tab(tabs + 1, *fOut);
    *fOut << "classInit(sample_rate);";
    tab(tabs + 1, *fOut);
    *fOut << "instanceInit(sample_rate);";
    tab(tabs, *fOut);
    *fOut << "}";

    tab(tabs, *fOut);
    *fOut << "void instanceInit(int sample_rate) nothrow @nogc {";
    tab(tabs + 1, *fOut);
    *fOut << "instanceConstants(sample_rate);";
    tab(tabs + 1, *fOut);
    *fOut << "instanceResetUserInterface();";
    tab(tabs + 1, *fOut);
    *fOut << "instanceClear();";
    tab(tabs, *fOut);
    *fOut << "}";
}

void DLangCodeContainer::printHeader()
{
    if (gGlobal->gArchFile == "")
        printDRecipeComment(*fOut, fKlassName);
    CodeContainer::printHeader(*fOut);
    if (gGlobal->gArchFile == "")
        printDModuleStmt(*fOut, fKlassName);
}

void DLangCodeContainer::printDRecipeComment(ostream& dst, const string& klassName)
{
    int n = 0;
    tab(n, dst);
    // dst << "#!/usr/bin/env dub\n";
    dst << "/+ dub.sdl:";
    tab(n + 1, dst);
    dst << "name \"" << dModuleName(klassName) << "\"";
    tab(n + 1, dst);
    dst << "dependency \"dplug:core\" version=\"*\"";
    tab(n, dst);
    dst << "+/\n";
}

void DLangCodeContainer::printDModuleStmt(ostream& dst, const string& klassName)
{
    dst << "module " << dModuleName(klassName) << ";\n";
}

void DLangCodeContainer::produceInternal()
{
    int n = 0;

    // Global declarations
    tab(n, *fOut);

    fCodeProducer.Tab(n);
    generateGlobalDeclarations(&fCodeProducer);

    *fOut << "struct " << fKlassName << " {\n";
    *fOut << "nothrow:\n";
    *fOut << "@nogc:";
    tab(n + 1, *fOut);

    tab(n, *fOut);
    *fOut << "  private:";
    
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
    produceInfoFunctions(n + 1, fKlassName, "dsp", true, FunTyped::kDefault, &fCodeProducer);

    // TODO
    // generateInstanceInitFun("instanceInit" + fKlassName, true, false)->accept(&fCodeProducer);

    // Inits
    tab(n + 1, *fOut);
    *fOut << "void instanceInit" << fKlassName << "(int sample_rate) nothrow @nogc {";
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
        *fOut << "void fill" << fKlassName << subst("(int $0, int[] " + fTableName + ") nothrow @nogc {", counter);
    } else {
        tab(n + 1, *fOut);
        *fOut << "void fill" << fKlassName << subst("(int $0, $1[] " + fTableName + ") nothrow @nogc {", counter, ifloat());
    }
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateComputeBlock(&fCodeProducer);
    ForLoopInst* loop = fCurLoop->generateScalarLoop(counter);
    loop->accept(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}";

    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "};" << endl;

    tab(n, *fOut);
    *fOut << fKlassName << "* "
            << "new" << fKlassName << "() nothrow @nogc {"
            << " return assumeNothrowNoGC(&mallocNew!(" << fKlassName << "))(); }";
    tab(n, *fOut);
    *fOut << "void delete" << fKlassName << "(" << fKlassName << "* dsp) nothrow @nogc { destroyFree(dsp); }";

    tab(n, *fOut);
}

string DLangCodeContainer::dModuleName(const string& klassName)
{
    string moduleName = klassName;
    transform(moduleName.begin(), moduleName.end(), moduleName.begin(), ::tolower);
    if (gGlobal->gNamespace != "") {
        moduleName = gGlobal->gNamespace + "." + moduleName;
    }
    return moduleName;
}

void DLangCodeContainer::produceClass()
{
    int n = 0;

    // Libraries
    printLibrary(*fOut);

    generateImports();

    // Generate gub containers
    generateSubContainers();

    *fOut << "alias FAUSTCLASS = " << fKlassName << ";" << endl;
  
    // Global declarations
    fCodeProducer.Tab(n);
    generateGlobalDeclarations(&fCodeProducer);

    tab(n, *fOut);
    *fOut << "class " << fKlassName << " : " << fSuperKlassName << "\n{\n";
    *fOut << "nothrow:\n";
    *fOut << "@nogc:";
    tab(n + 1, *fOut);

    tab(n, *fOut);
    *fOut << " private:";
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
    produceInfoFunctions(n + 1, "", "dsp", true, FunTyped::kVirtual, &fCodeProducer);  // Inits

    tab(n + 1, *fOut);
    *fOut << "static void classInit(int sample_rate) nothrow @nogc {";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateStaticInit(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}";

    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << "void instanceConstants(int sample_rate) nothrow @nogc {";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateInit(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    tab(n + 1, *fOut);
    *fOut << "void instanceResetUserInterface() nothrow @nogc {";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateResetUserInterface(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    tab(n + 1, *fOut);
    *fOut << "void instanceClear() nothrow @nogc {";
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
    *fOut << fKlassName << " clone() {";
    tab(n + 2, *fOut);
    *fOut << "return (mallocNew!" << fKlassName << "());";
    tab(n + 1, *fOut);
    *fOut << "}";

    tab(n + 1, *fOut);
    fCodeProducer.Tab(n + 1);
    tab(n + 1, *fOut);
    generateGetSampleRate("getSampleRate", "dsp", true, true)->accept(&fCodeProducer);

    // User interface
    tab(n + 1, *fOut);
    *fOut << "void buildUserInterface(UI* uiInterface) nothrow @nogc {";
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
}

// Scalar
DLangScalarCodeContainer::DLangScalarCodeContainer(const string& name, const string& super, int numInputs, int numOutputs,
                                               std::ostream* out, int sub_container_type)
    : DLangCodeContainer(name, super, numInputs, numOutputs, out)
{
    fSubContainerType = sub_container_type;
}

void DLangCodeContainer::generateImports()
{
    *fOut << "import std.math;\n";
    *fOut << "import std.algorithm : min, max;\n";
    *fOut << "import dplug.core.nogc: mallocNew, mallocSlice, destroyFree, assumeNothrowNoGC;\n";
}

void DLangScalarCodeContainer::generateCompute(int n)
{
    // Generates declaration
    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << subst("void compute(int $0, $1*[] inputs, $1*[] outputs) nothrow @nogc {", fFullCount, xfloat());
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);

    // Generates local variables declaration and setup
    generateComputeBlock(&fCodeProducer);

    // Generates one single scalar loop
    ForLoopInst* loop = fCurLoop->generateScalarLoop(fFullCount);
    loop->accept(&fCodeProducer);

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
    *fOut << subst("void compute($0[] inputs, $0[] outputs, int[] iControl, $0[] fControl) nothrow @nogc {", xfloat());
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

    generateImports();

    // Sub containers
    generateSubContainers();

    *fOut << "alias FAUSTCLASS = " << fKlassName << ";" << endl;
  
    // Global declarations
    fCodeProducer.Tab(n);
    generateGlobalDeclarations(&fCodeProducer);

    *fOut << "enum FAUST_INPUTS = " << fNumInputs << ";" << endl;
    *fOut << "enum FAUST_OUTPUTS = " << fNumOutputs << ";" << endl;
    *fOut << "enum FAUST_INT_CONTROLS = " << fIntControl->fCurIndex << ";" << endl;
    *fOut << "enum FAUST_REAL_CONTROLS = " << fRealControl->fCurIndex << ";" << endl;
    fSuperKlassName = "one_sample_dsp";

    tab(n, *fOut);
    *fOut << "class " << fKlassName << " : " << fSuperKlassName << "\n{\n";
    *fOut << "nothrow:\n";
    *fOut << "@nogc:";
    tab(n + 1, *fOut);

    tab(n, *fOut);
    *fOut << " private:";
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
    produceInfoFunctions(n + 1, "", "dsp", true, FunTyped::kVirtual, &fCodeProducer);  // Inits

    tab(n + 1, *fOut);
    *fOut << "static void classInit(int sample_rate) nothrow @nogc {";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateStaticInit(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}";

    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << "void instanceConstants(int sample_rate) nothrow @nogc {";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateInit(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    tab(n + 1, *fOut);
    *fOut << "void instanceResetUserInterface() nothrow @nogc {";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateResetUserInterface(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    tab(n + 1, *fOut);
    *fOut << "void instanceClear() nothrow @nogc {";
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
    *fOut << fKlassName << " clone() {";
    tab(n + 2, *fOut);
    *fOut << "return (mallocNew!" << fKlassName << "());";
    tab(n + 1, *fOut);
    *fOut << "}";

    tab(n + 1, *fOut);
    fCodeProducer.Tab(n + 1);
    tab(n + 1, *fOut);
    generateGetSampleRate("getSampleRate", "dsp", true, true)->accept(&fCodeProducer);

    // User interface
    tab(n + 1, *fOut);
    *fOut << "void buildUserInterface(UI* uiInterface) nothrow @nogc {";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateUserInterface(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}";

    tab(n + 1, *fOut);
    *fOut << subst("void control(int[] iControl, $0[] fControl) nothrow @nogc {", xfloat());
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    // Generates local variables declaration and setup
    generateComputeBlock(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}" << endl;

    tab(n + 1, *fOut);
    *fOut << "int getNumIntControls() nothrow @nogc { return " << fIntControl->fCurIndex << "; }";
    tab(n + 1, *fOut);
    *fOut << "int getNumRealControls() nothrow @nogc { return " << fRealControl->fCurIndex << "; }";

    // Compute
    generateCompute(n);
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "}" << endl;
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
    *fOut << subst("void compute(int $0, $1*[] inputs, $1*[] outputs) nothrow @nogc {", fFullCount, xfloat());
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);

    // Generates local variables declaration and setup
    generateComputeBlock(&fCodeProducer);

    // Generates the DSP loop
    fDAGBlock->accept(&fCodeProducer);

    back(1, *fOut);
    *fOut << "}";
}
