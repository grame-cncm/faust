/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2021 GRAME, Centre National de Creation Musicale
    Modified to C# from Java by Mike Oliphant
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

#include "csharp_code_container.hh"
#include "Text.hh"
#include "exception.hh"
#include "floats.hh"
#include "global.hh"

using namespace std;

map<string, bool>   CSharpInstVisitor::gFunctionSymbolTable;
map<string, string> CSharpInstVisitor::gMathLibTable;

dsp_factory_base* CSharpCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(
        fKlassName, "", "",
        ((dynamic_cast<ostringstream*>(fOut)) ? dynamic_cast<ostringstream*>(fOut)->str() : ""), "");
}

CodeContainer* CSharpCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new CSharpScalarCodeContainer(name, "", 0, 1, fOut, sub_container_type);
}

CodeContainer* CSharpCodeContainer::createContainer(const string& name, const string& super, int numInputs,
                                                  int numOutputs, ostream* dst)
{
    CodeContainer* container;

    if (gGlobal->gFloatSize == 3) {
        throw faustexception("ERROR : -quad format not supported for CSharp\n");
    }
    if (gGlobal->gOpenCLSwitch) {
        throw faustexception("ERROR : OpenCL not supported for CSharp\n");
    }
    if (gGlobal->gCUDASwitch) {
        throw faustexception("ERROR : CUDA not supported for CSharp\n");
    }

    if (gGlobal->gOpenMPSwitch) {
        throw faustexception("ERROR : OpenMP not supported for CSharp\n");
    } else if (gGlobal->gSchedulerSwitch) {
        throw faustexception("ERROR : Scheduler not supported for CSharp\n");
    } else if (gGlobal->gVectorSwitch) {
        throw faustexception("ERROR : Vector mode not supported for CSharp\n");
    } else {
        container = new CSharpScalarCodeContainer(name, super, numInputs, numOutputs, dst, kInt);
    }

    return container;
}

// Scalar
CSharpScalarCodeContainer::CSharpScalarCodeContainer(const string& name, const string& super, int numInputs,
                                                   int numOutputs,
                                                 std::ostream* out, int sub_container_type)
    : CSharpCodeContainer(name, super, numInputs, numOutputs, out)
{
    fSubContainerType = sub_container_type;
}

CSharpScalarCodeContainer::~CSharpScalarCodeContainer()
{
}

void CSharpCodeContainer::produceInternal()
{
    int n = 1;

    // Global declarations
    tab(n, *fOut);
    fCodeProducer.Tab(n);
    generateGlobalDeclarations(&fCodeProducer);

    tab(n, *fOut);
    *fOut << "class " << fKlassName;
    tab(n, *fOut);
    *fOut << "{";

    tab(n + 1, *fOut);
    tab(n + 1, *fOut);

    // Fields
    fCodeProducer.Tab(n + 1);
    generateDeclarations(&fCodeProducer);

    tab(n + 1, *fOut);
    // fKlassName used in method naming for subclasses
    produceInfoFunctions(n + 1, fKlassName, "dsp", true, FunTyped::kDefault, &fCodeProducer);

    // TODO
    // generateInstanceInitFun("instanceInit" + fKlassName, true, false)->accept(&fCodeProducer);

    // Inits
    tab(n + 1, *fOut);
    *fOut << "public void instanceInit" << fKlassName << "(int sample_rate) {";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateInit(&fCodeProducer);
    generateResetUserInterface(&fCodeProducer);
    generateClear(&fCodeProducer);
    tab(n + 1, *fOut);
    *fOut << "}";

    // Fill
    string counter = "count";
    if (fSubContainerType == kInt) {
        tab(n + 1, *fOut);
        *fOut << "public void fill" << fKlassName << subst("(int $0, int[] " + fTableName + ") { ", counter);
    } else {
        tab(n + 1, *fOut);
        *fOut << "public void fill" << fKlassName << subst("(int $0, $1[] " + fTableName + ") {", counter, ifloat());
    }
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateComputeBlock(&fCodeProducer);
    ForLoopInst* loop = fCurLoop->generateScalarLoop(counter);
    loop->accept(&fCodeProducer);
    tab(n + 1, *fOut);
    *fOut << "}";

    tab(n, *fOut);
    *fOut << "};" << endl;

    // Memory methods (as globals)
    tab(n, *fOut);
    *fOut << fKlassName << " new" << fKlassName << "() {"
          << "return new " << fKlassName << "()"
          << "; }";

    tab(n, *fOut);
    *fOut << "void delete" << fKlassName << "(" << fKlassName << " dsp) {}";
    tab(n, *fOut);
}

void CSharpCodeContainer::produceClass()
{
    int n = 0;

    // Libraries
    printLibrary(*fOut);
    tab(n, *fOut);
        
    tab(n, *fOut);
    *fOut << "public class " << fKlassName << " : " << fSuperKlassName << ", " << "IFaustDSP";
    tab(n, *fOut);
    *fOut << "{";

    // Global declarations
    tab(n + 1, *fOut);
    fCodeProducer.Tab(n + 1);
    generateGlobalDeclarations(&fCodeProducer);

    // Generate gub containers
    generateSubContainers();

    // Fields
    tab(n + 1, *fOut);
    fCodeProducer.Tab(n + 1);
    generateDeclarations(&fCodeProducer);

    if (fAllocateInstructions->fCode.size() > 0) {
        tab(n + 1, *fOut);
        *fOut << "void allocate() {";
        tab(n + 2, *fOut);
        fCodeProducer.Tab(n + 2);
        generateAllocate(&fCodeProducer);
        tab(n + 1, *fOut);
        *fOut << "}";
        tab(n + 1, *fOut);
    }

    if (fDestroyInstructions->fCode.size() > 0) {
        tab(n + 1, *fOut);
        *fOut << "void destroy() {";
        tab(n + 2, *fOut);
        fCodeProducer.Tab(n + 2);
        generateDestroy(&fCodeProducer);
        tab(n + 1, *fOut);
        *fOut << "}";
        tab(n + 1, *fOut);
    }

    tab(n + 1, *fOut);
    *fOut << "public " << fKlassName << "()";
    tab(n + 1, *fOut);
    *fOut << "{";
    tab(n + 2, *fOut);
    *fOut << "SetMetaData();";
    tab(n + 2, *fOut);
    *fOut << "BuildUserInterface();";
    tab(n + 1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    tab(n + 1, *fOut);
    produceInfoFunctions(n + 1, "", "dsp", true, FunTyped::kVirtual, &fCodeProducer);

    // Print metadata declaration
    tab(n + 1, *fOut);
    *fOut << "void SetMetaData()";
    tab(n + 1, *fOut);
    *fOut << "{";

    for (auto& i : gGlobal->gMetaDataSet) {
        if (i.first != tree("author")) {
            tab(n + 2, *fOut);
            *fOut << "MetaData.Declare(\"" << *(i.first) << "\", " << **(i.second.begin()) << ");";
        } else {
            for (set<Tree>::iterator j = i.second.begin(); j != i.second.end(); j++) {
                if (j == i.second.begin()) {
                    tab(n + 2, *fOut);
                    *fOut << "MetaData.Declare(\"" << *(i.first) << "\", " << **j << ");";
                } else {
                    tab(n + 2, *fOut);
                    *fOut << "MetaData.Declare(\""
                          << "contributor"
                          << "\", " << **j << ");";
                }
            }
        }
    }

    tab(n + 1, *fOut);
    *fOut << "}" << endl;

    // User interface
    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << "void BuildUserInterface()";
    tab(n + 1, *fOut);
    *fOut << "{";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateUserInterface(&fCodeProducer);
    printlines(n + 2, fUICode, *fOut);
    back(1, *fOut);
    *fOut << "}" << endl;

    // Inits

    // TODO
    /*
    generateStaticInitFun("classInit", false)->accept(&fCodeProducer);
    generateInstanceInitFun("instanceInit", true, true)->accept(&fCodeProducer);
    */

    tab(n + 1, *fOut);
    *fOut << "public void ClassInit(int sample_rate)";
    tab(n + 1, *fOut);
    *fOut << "{";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateStaticInit(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}";

    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << "public void InstanceConstants(int sample_rate)";
    tab(n + 1, *fOut);
    *fOut << "{";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateInit(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}";

    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << "public void InstanceResetUserInterface()";
    tab(n + 1, *fOut);
    *fOut << "{";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateResetUserInterface(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}";

    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << "public void InstanceClear()";
    tab(n + 1, *fOut);
    *fOut << "{";
    tab(n + 2, *fOut);
    fCodeProducer.Tab(n + 2);
    generateClear(&fCodeProducer);
    back(1, *fOut);
    *fOut << "}";

    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << "public void Init(int sample_rate)";
    tab(n + 1, *fOut);
    *fOut << "{";
    tab(n + 2, *fOut);
    *fOut << "ClassInit(sample_rate);";
    tab(n + 2, *fOut);
    *fOut << "InstanceInit(sample_rate);";
    tab(n + 1, *fOut);
    *fOut << "}";

    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << "public void InstanceInit(int sample_rate)";
    tab(n + 1, *fOut);
    *fOut << "{";
    tab(n + 2, *fOut);
    *fOut << "InstanceConstants(sample_rate);";
    tab(n + 2, *fOut);
    *fOut << "InstanceResetUserInterface();";
    tab(n + 2, *fOut);
    *fOut << "InstanceClear();";
    tab(n + 1, *fOut);
    *fOut << "}";

    // Compute
    generateCompute(n);

    // Possibly generate separated functions
    fCodeProducer.Tab(n + 1);
    tab(n + 1, *fOut);
    generateComputeFunctions(&fCodeProducer);

    back(1, *fOut);
    *fOut << "};\n" << endl;
}

void CSharpCodeContainer::produceInfoFunctions(int tabs, const string& classname, const string& obj, bool ismethod,
                                            FunTyped::FunAttribute funtype, TextInstVisitor* producer)
{
    // Input/Output method
    producer->Tab(tabs);
    generateGetInputs(subst("GetNumInputs$0", classname), obj, ismethod, funtype)->accept(producer);
    generateGetOutputs(subst("GetNumOutputs$0", classname), obj, ismethod, funtype)->accept(producer);
}

void CSharpScalarCodeContainer::generateCompute(int n)
{
    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << subst("public void Compute(int $0, $1[][] inputs, $1[][] outputs)", fFullCount, ifloat());
    tab(n + 1, *fOut);
    *fOut << "{";
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
