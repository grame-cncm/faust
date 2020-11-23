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
    return new DLangScalarCodeContainer(name, "", 0, 1, fOut, sub_container_type);
}

CodeContainer* DLangCodeContainer::createContainer(const string& name, const string& super, int numInputs,
                                                  int numOutputs, ostream* dst)
{
    CodeContainer* container;

    if (gGlobal->gMemoryManager) {
        throw faustexception("ERROR : -mem not supported for D\n");
    }
    if (gGlobal->gFloatSize == 3) {
        throw faustexception("ERROR : quad format not supported for D\n");
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
        container = new DLangScalarCodeContainer(name, super, numInputs, numOutputs, dst, kInt);
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

    tab(tabs, *fOut);
    *fOut << "void init(int sample_rate) {";
    tab(tabs + 1, *fOut);
    *fOut << "classInit(sample_rate);";
    tab(tabs + 1, *fOut);
    *fOut << "instanceInit(sample_rate);";
    tab(tabs, *fOut);
    *fOut << "}";

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

void DLangCodeContainer::printHeader()
{ 
    int n = 0;
    tab(n, *fOut);
    // *fOut << "#!/usr/bin/env dub\n";
    *fOut << "/+ dub.sdl:";
    tab(n + 1, *fOut);
    *fOut << "name \"" << dModuleName(fKlassName) << "\"";
    tab(n + 1, *fOut);
    *fOut << "dependency \"dplug:core\" version=\"*\"";
    tab(n, *fOut);
    *fOut << "+/\n";
    CodeContainer::printHeader(*fOut); 
    *fOut << "module " << dModuleName(fKlassName) << ";\n";
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

string DLangCodeContainer::dModuleName(string fKlassName)
{
    string moduleName = fKlassName;
    transform(moduleName.begin(), moduleName.end(), moduleName.begin(), ::tolower);
    return moduleName;
}

void DLangCodeContainer::produceClass()
{
    int n = 0;

    // Libraries
    printLibrary(*fOut);

    generateImports(n);

    // Sub containers
    generateSubContainers();


    tab(n, *fOut);
    *fOut << "alias FAUSTFLOAT = " << ifloat() << ";" << endl;
    tab(n, *fOut);

    *fOut << "alias FAUSTCLASS = " << fKlassName << ";" << endl;
    tab(n, *fOut);

    // Global declarations
    tab(n, *fOut);
    fCodeProducer.Tab(n);
    generateGlobalDeclarations(&fCodeProducer);
    
    tab(n, *fOut);
    *fOut << "class " << fKlassName << " : " << fSuperKlassName << "\n{\n";
    *fOut << "nothrow:\n";
    *fOut << "@nogc:\n";
    
    
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
    *fOut << "void classInit(int sample_rate) {";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateStaticInit(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}";

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
    *fOut << "return cast(" << fKlassName << "*)(mallocNew!" << fKlassName << "());";
    tab(n + 1, *fOut);
    *fOut << "}";

    tab(n + 1, *fOut);
    fCodeProducer.Tab(n + 1);
    tab(n + 1, *fOut);
    generateGetSampleRate("getSampleRate", "dsp", true, true)->accept(&fCodeProducer);

    // User interface
    tab(n + 1, *fOut);
    *fOut << "void buildUserInterface(UI* uiInterface) {";
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

void DLangCodeContainer::generateImports(int n)
{
    *fOut << "import std.math;\n";
    *fOut << "import std.algorithm : min, max;\n";
    *fOut << "import dplug.core.nogc: mallocNew, mallocSlice, destroyFree, assumeNothrowNoGC;\n";
    tab(n, *fOut);
}

void DLangScalarCodeContainer::generateCompute(int n)
{
    // Generates declaration
    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << subst("void compute(int $0, $1*[] inputs, $1*[] outputs) {", fFullCount, xfloat());
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
    *fOut << subst("void compute(int $0, $1*[] inputs, $1*[] outputs) {", fFullCount, xfloat());
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);

    // Generates local variables declaration and setup
    generateComputeBlock(&fCodeProducer);

    // Generates the DSP loop
    fDAGBlock->accept(&fCodeProducer);

    back(1, *fOut);
    *fOut << "}";
}