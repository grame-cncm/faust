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
#include "cpp_code_container.hh"
#include "cpp_gpu_code_container.hh"
#include "exception.hh"
#include "fir_to_fir.hh"
#include "floats.hh"
#include "global.hh"

using namespace std;

/*
 C++ backend and module description:

    1) in -os mode: a 'frame' function is generated
    2) in -ec mode: a 'control' function is generated, with a empty 'compute"
    3) in -fx mode:
        - then/else branches of 'select2' are explicitly casted to 'float', otherwise AP_fixed
 compilation may trigger "ambigous type" errors
        - all math operators are named "FOOfx" and are supposed to be implemented in the
 architecture file (doing the proper cast on arguments and return value when needed)
 */

map<string, bool> CPPInstVisitor::gFunctionSymbolTable;

dsp_factory_base* CPPCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(
        fKlassName, "", "",
        ((dynamic_cast<ostringstream*>(fOut)) ? dynamic_cast<ostringstream*>(fOut)->str() : ""),
        "");
}

CodeContainer* CPPCodeContainer::createScalarContainer(const std::string& name,
                                                       const std::string& super, int numInputs,
                                                       int numOutputs, ostream* dst,
                                                       int sub_container_type)
{
    return new CPPScalarCodeContainer(name, super, numInputs, numOutputs, dst, sub_container_type);
}

CodeContainer* CPPCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return createScalarContainer(name, "", 0, 1, fOut, sub_container_type);
}

CodeContainer* CPPCodeContainer::createContainer(const string& name, const string& super,
                                                 int numInputs, int numOutputs, ostream* dst)
{
    CodeContainer* container;

    if (gGlobal->gOpenCLSwitch) {
        if (gGlobal->gFunTaskSwitch) {
            throw faustexception("ERROR : -fun not yet supported in OpenCL mode\n");
        }
        if (gGlobal->gVectorSwitch) {
            container = new CPPOpenCLVectorCodeContainer(name, super, numInputs, numOutputs, dst);
        } else {
            container = new CPPOpenCLCodeContainer(name, super, numInputs, numOutputs, dst);
        }
    } else if (gGlobal->gCUDASwitch) {
        if (gGlobal->gFunTaskSwitch) {
            throw faustexception("ERROR : -fun not yet supported in CUDA mode\n");
        }
        if (gGlobal->gVectorSwitch) {
            container = new CPPCUDAVectorCodeContainer(name, super, numInputs, numOutputs, dst);
        } else {
            container = new CPPCUDACodeContainer(name, super, numInputs, numOutputs, dst);
        }
    } else if (gGlobal->gOpenMPSwitch) {
        container = new CPPOpenMPCodeContainer(name, super, numInputs, numOutputs, dst);
    } else if (gGlobal->gSchedulerSwitch) {
        container = new CPPWorkStealingCodeContainer(name, super, numInputs, numOutputs, dst);
    } else if (gGlobal->gVectorSwitch) {
        container = new CPPVectorCodeContainer(name, super, numInputs, numOutputs, dst);
    } else {
        container = createScalarContainer(name, super, numInputs, numOutputs, dst, kInt);
    }

    return container;
}

string CPPCodeContainer::genVirtual()
{
    return (gGlobal->gNoVirtual) ? "" : "virtual ";
}

string CPPCodeContainer::genFinal()
{
    return (gGlobal->gNoVirtual) ? " final" : "";
}

// Scalar
CPPScalarCodeContainer::CPPScalarCodeContainer(const string& name, const string& super,
                                               int numInputs, int numOutputs, std::ostream* out,
                                               int sub_container_type)
    : CPPCodeContainer(name, super, numInputs, numOutputs, out)
{
    fSubContainerType = sub_container_type;
}

void CPPCodeContainer::produceMetadata(int tabs)
{
    tab(tabs, *fOut);
    *fOut << "void metadata(Meta* m) { ";

    // We do not want to accumulate metadata from all hierachical levels, so the upper level only is
    // kept
    for (const auto& i : gGlobal->gMetaDataSet) {
        if (i.first != tree("author")) {
            tab(tabs + 1, *fOut);
            *fOut << "m->declare(\"" << *(i.first) << "\", " << **(i.second.begin()) << ");";
        } else {
            // But the "author" meta data is accumulated, the upper level becomes the main author
            // and sub-levels become "contributor"
            for (set<Tree>::iterator j = i.second.begin(); j != i.second.end(); j++) {
                if (j == i.second.begin()) {
                    tab(tabs + 1, *fOut);
                    *fOut << "m->declare(\"" << *(i.first) << "\", " << **j << ");";
                } else {
                    tab(tabs + 1, *fOut);
                    *fOut << "m->declare(\""
                          << "contributor"
                          << "\", " << **j << ");";
                }
            }
        }
    }

    tab(tabs, *fOut);
    *fOut << "}" << endl;
}

void CPPCodeContainer::produceInit(int tabs)
{
    if (gGlobal->gMemoryManager >= 0) {
        tab(tabs, *fOut);
        *fOut << genVirtual() << "void init(int sample_rate) {}";
    } else {
        tab(tabs, *fOut);
        *fOut << genVirtual() << "void init(int sample_rate) {";
        tab(tabs + 1, *fOut);
        // Replaced by staticInit called in instanceInit
        if (!gGlobal->gInlineTable) {
            *fOut << "classInit(sample_rate);";
            tab(tabs + 1, *fOut);
        }
        *fOut << "instanceInit(sample_rate);";
        tab(tabs, *fOut);
        *fOut << "}";
    }
    tab(tabs, *fOut);
    tab(tabs, *fOut);
    *fOut << genVirtual() << "void instanceInit(int sample_rate) {";
    tab(tabs + 1, *fOut);
    // staticInit has to be called for each instance since the tables are actually not shared
    // between instances
    if (gGlobal->gInlineTable) {
        *fOut << "staticInit(sample_rate);";
        tab(tabs + 1, *fOut);
    }
    *fOut << "instanceConstants(sample_rate);";
    tab(tabs + 1, *fOut);
    if (gGlobal->gMemoryManager == 2) {
        *fOut << "instanceConstantsToMem(sample_rate);";
        tab(tabs + 1, *fOut);
    }
    *fOut << "instanceResetUserInterface();";
    tab(tabs + 1, *fOut);
    *fOut << "instanceClear();";
    tab(tabs, *fOut);
    *fOut << "}";
}

void CPPCodeContainer::produceInternal()
{
    int n = 0;

    // Global declarations
    tab(n, *fOut);

    fCodeProducer->Tab(n);
    generateGlobalDeclarations(fCodeProducer);

    if (gGlobal->gUIMacroSwitch) {
        *fOut << "struct " << fKlassName << " {";
    } else {
        *fOut << "class " << fKlassName << " {";
    }
    tab(n + 1, *fOut);

    if (!gGlobal->gUIMacroSwitch) {
        tab(n, *fOut);
        *fOut << "  private:";
        tab(n + 1, *fOut);
        tab(n + 1, *fOut);
    }

    // Fields
    fCodeProducer->Tab(n + 1);
    generateDeclarations(fCodeProducer);

    if (!gGlobal->gUIMacroSwitch) {
        tab(n, *fOut);
        *fOut << "  public:";
        tab(n + 1, *fOut);
    }

    tab(n + 1, *fOut);

    // fKlassName used in method naming for subclasses
    produceInfoFunctions(n + 1, fKlassName, "dsp", true, FunTyped::kDefault, fCodeProducer);

    // TODO
    // generateInstanceInitFun("instanceInit" + fKlassName, true, false)->accept(fCodeProducer);

    // Inits
    tab(n + 1, *fOut);
    *fOut << "void instanceInit" << fKlassName << "(int sample_rate) {";
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    generateInit(fCodeProducer);
    generateResetUserInterface(fCodeProducer);
    generateClear(fCodeProducer);
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
        *fOut << "void fill" << fKlassName
              << subst("(int $0, $1* " + fTableName + ") {", counter, ifloat());
    }
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    generateComputeBlock(fCodeProducer);
    ForLoopInst* loop = fCurLoop->generateScalarLoop(counter);
    loop->accept(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";

    /*
    tab(n+1, *fOut);
    fCodeProducer->Tab(n+1);
    generateFillFun("fill" + fKlassName, true, false)->accept(fCodeProducer);
    */

    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "};" << endl;

    // Memory methods (as globals)
    if (gGlobal->gMemoryManager == 0 || gGlobal->gMemoryManager == 1) {
        tab(n, *fOut);
        *fOut << "static " << fKlassName << "* "
              << "new" << fKlassName << "(dsp_memory_manager* manager) {"
              << " return (" << fKlassName << "*)new(manager->allocate(sizeof(" << fKlassName
              << "))) " << fKlassName << "(); }";
        tab(n, *fOut);
        *fOut << "static void delete" << fKlassName << "(" << fKlassName
              << "* dsp, dsp_memory_manager* manager) { dsp->~" << fKlassName
              << "(); manager->destroy(dsp); }";
    } else {
        tab(n, *fOut);
        *fOut << "static " << fKlassName << "* "
              << "new" << fKlassName << "() {"
              << " return (" << fKlassName << "*)new " << fKlassName << "(); }";
        tab(n, *fOut);
        *fOut << "static void delete" << fKlassName << "(" << fKlassName
              << "* dsp) { delete dsp; }";
    }
    tab(n, *fOut);
}

void CPPCodeContainer::produceClass()
{
    int n = 0;

    // Libraries
    printLibrary(*fOut);
    printIncludeFile(*fOut);

    if (gGlobal->gNamespace != "" && gGlobal->gArchFile == "") {
        tab(n, *fOut);
        *fOut << "namespace " << gGlobal->gNamespace << " {" << endl;
    }

    generateHeader(n);

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
    if (gGlobal->gUIMacroSwitch) {
        if (fSuperKlassName != "") {
            *fOut << "struct " << fKlassName << genFinal() << " : public " << fSuperKlassName
                  << " {";
        } else {
            *fOut << "struct " << fKlassName << genFinal() << " {";
        }
    } else {
        if (fSuperKlassName != "") {
            *fOut << "class " << fKlassName << genFinal() << " : public " << fSuperKlassName
                  << " {";
        } else {
            *fOut << "class " << fKlassName << genFinal() << " {";
        }
    }
    tab(n + 1, *fOut);

    if (!gGlobal->gUIMacroSwitch) {
        tab(n, *fOut);
        *fOut << " private:";
        tab(n + 1, *fOut);
    }

    // Fields
    fCodeProducer->Tab(n + 1);
    tab(n + 1, *fOut);
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

    generateAllocateFun(n);
    generateDestroyFun(n);

    if (!gGlobal->gUIMacroSwitch) {
        tab(n, *fOut);
        *fOut << " public:";
    }

    if (gGlobal->gMemoryManager == 0 || gGlobal->gMemoryManager == 1) {
        tab(n + 1, *fOut);
        *fOut << "static dsp_memory_manager* fManager;";
        tab(n + 1, *fOut);
    }

    // iControl/fControl and iZone/fZone are given as parameters,
    // in the constructors and in an additional setMemory method.
    // The really needed one only will be set.

    if (gGlobal->gMemoryManager == 2) {
        tab(n + 1, *fOut);
        bool int_control  = (fIntControl) ? fIntControl->getSize() > 0 : false;
        bool real_control = (fRealControl) ? fRealControl->getSize() > 0 : false;
        bool int_zone     = gGlobal->gIntZone->getSize() > 0;
        bool real_zone    = gGlobal->gRealZone->getSize() > 0;

        // Default constructor
        stringstream fun_proto1;
        fun_proto1 << fKlassName << "()";
        generateConstructor(fun_proto1.str(), n);
        if (int_control) {
            tab(n + 2, *fOut);
            *fOut << "iControl = nullptr;";
        }
        if (real_control) {
            tab(n + 2, *fOut);
            *fOut << "fControl = nullptr;";
        }
        if (int_zone) {
            tab(n + 2, *fOut);
            *fOut << "iZone = nullptr;";
        }
        if (real_zone) {
            tab(n + 2, *fOut);
            *fOut << "fZone = nullptr;";
        }
        tab(n + 1, *fOut);
        *fOut << "}";

        // Constructor
        stringstream fun_proto2;
        fun_proto2 << fKlassName << "(int* icontrol, " << ifloat() << "* fcontrol, int* izone, "
                   << ifloat() << "* fzone)";
        generateConstructor(fun_proto2.str(), n);
        if (int_control) {
            tab(n + 2, *fOut);
            *fOut << "iControl = icontrol;";
        }
        if (real_control) {
            tab(n + 2, *fOut);
            *fOut << "fControl = fcontrol;";
        }
        if (int_zone) {
            tab(n + 2, *fOut);
            *fOut << "iZone = izone;";
        }
        if (real_zone) {
            tab(n + 2, *fOut);
            *fOut << "fZone = fzone;";
        }
        tab(n + 1, *fOut);
        *fOut << "}";

        // setMemory
        tab(n + 1, *fOut);
        *fOut << "void setMemory(int* icontrol, " << ifloat() << "* fcontrol, int* izone, "
              << ifloat() << "* fzone) {";
        if (int_control) {
            tab(n + 2, *fOut);
            *fOut << "iControl = icontrol;";
        }
        if (real_control) {
            tab(n + 2, *fOut);
            *fOut << "fControl = fcontrol;";
        }
        if (int_zone) {
            tab(n + 2, *fOut);
            *fOut << "iZone = izone;";
        }
        if (real_zone) {
            tab(n + 2, *fOut);
            *fOut << "fZone = fzone;";
        }
        tab(n + 1, *fOut);
        *fOut << "}";
        tab(n + 1, *fOut);
    } else {
        // Default constructor
        string fun_proto = fKlassName + "()";
        generateConstructor(fun_proto, n);
        tab(n + 1, *fOut);
        *fOut << "}";
        tab(n + 1, *fOut);
    }

    generateDestructor(n);

    // Print metadata declaration
    produceMetadata(n + 1);

    // No class name for main class
    tab(n + 1, *fOut);
    if (gGlobal->gNoVirtual) {
        produceInfoFunctions(n + 1, "", "dsp", true, FunTyped::kStaticConstExpr, fCodeProducer,
                             "getStaticNumInputs", "getStaticNumOutputs");
        produceInfoFunctions(n + 1, "", "dsp", true, FunTyped::kDefault, fCodeProducer);
    } else {
        produceInfoFunctions(n + 1, "", "dsp", true, FunTyped::kVirtual, fCodeProducer);
    }

    // TODO
    /*
    generateStaticInitFun("classInit", true)->accept(fCodeProducer);
    generateInstanceInitFun("instanceInit", true, true)->accept(fCodeProducer);
    */

    tab(n + 1, *fOut);
    if (gGlobal->gInlineTable) {
        // Empty classInit
        *fOut << "static void classInit(int sample_rate) {}";
        tab(n + 1, *fOut);
        // To be used in instanceInit
        tab(n + 1, *fOut);
        *fOut << "void staticInit(int sample_rate) {";
        {
            tab(n + 2, *fOut);
            fCodeProducer->Tab(n + 2);
            fStaticInitInstructions->accept(fCodeProducer);
        }
        back(1, *fOut);
        *fOut << "}";
    } else {
        *fOut << "static void classInit(int sample_rate) {";
        tab(n + 2, *fOut);
        fCodeProducer->Tab(n + 2);
        generateStaticInit(fCodeProducer);
        back(1, *fOut);
        *fOut << "}";
    }

    if (gGlobal->gMemoryManager >= 0) {
        tab(n + 1, *fOut);
        tab(n + 1, *fOut);
        *fOut << "static void classDestroy() {";
        tab(n + 2, *fOut);
        fCodeProducer->Tab(n + 2);
        generateStaticDestroy(fCodeProducer);
        back(1, *fOut);
        *fOut << "}";
    }

    // TEST
    /*
    // Start inline
    {
        DspRenamer renamer;
        BlockInst* res1 = renamer.getCode(fStaticInitInstructions);

        list<CodeContainer*>::const_iterator it;
        for (it = fSubContainers.begin(); it != fSubContainers.end(); it++) {
            DeclareFunInst* inst_init_fun = (*it)->generateInstanceInitFun("instanceInit" +
    (*it)->getClassName(), true, false); InlineVoidFunctionCall inliner1(inst_init_fun); res1 =
    inliner1.getCode(res1); DeclareFunInst* fill_fun = (*it)->generateFillFun("fill" +
    (*it)->getClassName(), true, false); InlineVoidFunctionCall inliner2(fill_fun); res1 =
    inliner2.getCode(res1);
        }

        tab(n+1, *fOut);
        *fOut << "static void classInit(int sample_rate) {";
            tab(n+2, *fOut);
            fCodeProducer->Tab(n+2);
            res1->accept(fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";
    }
    // End inline
    */

    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "void instanceConstants(int sample_rate) {";
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    if (gGlobal->gInlineTable) {
        // 'delete' instruction which are in fPostInitInstructions are not generated
        fInitInstructions->accept(fCodeProducer);
    } else {
        generateInit(fCodeProducer);
    }
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    if (gGlobal->gMemoryManager == 2) {
        tab(n + 1, *fOut);
        *fOut << genVirtual() << "void instanceConstantsFromMem(int sample_rate) {";
        tab(n + 2, *fOut);
        faustassert(fConstantFromMem);
        fConstantFromMem->accept(fCodeProducer);
        back(1, *fOut);
        *fOut << "}";
        tab(n + 1, *fOut);

        tab(n + 1, *fOut);
        *fOut << genVirtual() << "void instanceConstantsToMem(int sample_rate) {";
        tab(n + 2, *fOut);
        faustassert(fConstantToMem);
        fConstantToMem->accept(fCodeProducer);
        back(1, *fOut);
        *fOut << "}";
        tab(n + 1, *fOut);
    }

    tab(n + 1, *fOut);
    *fOut << genVirtual() << "void instanceResetUserInterface() {";
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    generateResetUserInterface(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    tab(n + 1, *fOut);
    *fOut << genVirtual() << "void instanceClear() {";
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    generateClear(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    // TEST
    /*
    // Start inline
    {
        DspRenamer renamer;
        BlockInst* res1 = renamer.getCode(fInitInstructions);
        BlockInst* res2 = renamer.getCode(fPostInitInstructions);

        list<CodeContainer*>::const_iterator it;
        for (it = fSubContainers.begin(); it != fSubContainers.end(); it++) {
            DeclareFunInst* inst_init_fun = (*it)->generateInstanceInitFun("instanceInit" +
    (*it)->getClassName(), true,false); InlineVoidFunctionCall inliner1(inst_init_fun); res1 =
    inliner1.getCode(res1); res2 = inliner1.getCode(res2); DeclareFunInst* fill_fun =
    (*it)->generateFillFun("fill" + (*it)->getClassName(), true, false); InlineVoidFunctionCall
    inliner2(fill_fun); res1 = inliner2.getCode(res1); res2 = inliner2.getCode(res2);
        }

        tab(n+1, *fOut);
        *fOut << "virtual void instanceInit(int sample_rate) {";
        tab(n+2, *fOut);
        fCodeProducer->Tab(n+2);
        res1->accept(fCodeProducer);
        res2->accept(fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";
    }
    // End inline
    */

    // Init
    produceInit(n + 1);
    tab(n + 1, *fOut);

    // Clone
    tab(n + 1, *fOut);
    *fOut << genVirtual() << fKlassName << "* clone() {";
    tab(n + 2, *fOut);
    if (gGlobal->gMemoryManager == 0 || gGlobal->gMemoryManager == 1) {
        *fOut << "return create();";
    } else if (gGlobal->gMemoryManager == 2) {
        // TODO: use the same memory for now...
        *fOut << "return new " << fKlassName << "(";
        *fOut << (fIntControl && (fIntControl->getSize() > 0) ? "iControl, " : "nullptr, ");
        *fOut << (fRealControl && (fRealControl->getSize() > 0) ? "fControl, " : "nullptr, ");
        *fOut << ((gGlobal->gIntZone->getSize() > 0) ? "iZone, " : "nullptr, ");
        *fOut << ((gGlobal->gRealZone->getSize() > 0) ? "fZone);" : "nullptr);");
    } else {
        *fOut << "return new " << fKlassName << "();";
    }
    tab(n + 1, *fOut);
    *fOut << "}";

    // getSampleRate
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);
    tab(n + 1, *fOut);
    generateGetSampleRate("getSampleRate", "dsp", true, !gGlobal->gNoVirtual)
        ->accept(fCodeProducer);

    // User interface
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "void buildUserInterface(UI* ui_interface) {";
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    generateUserInterface(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";

    // Control
    if (gGlobal->gExtControl) {
        tab(n + 1, *fOut);
        tab(n + 1, *fOut);
        *fOut << "void control() {";
        tab(n + 2, *fOut);
        generateControlDeclarations(fCodeProducer);
        back(1, *fOut);
        *fOut << "}";
    }

    // Frame
    if (gGlobal->gOneSample) {
        // Generates declaration
        tab(n + 1, *fOut);
        tab(n + 1, *fOut);
        if (gGlobal->gInPlace) {
            *fOut << genVirtual()
                  << subst("void frame($0* inputs, $0* outputs) {", xfloat(), ifloat());
        } else {
            *fOut << genVirtual()
                  << subst("void frame($0* RESTRICT inputs, $0* RESTRICT outputs) {", xfloat(),
                           ifloat());
        }
        tab(n + 2, *fOut);
        fCodeProducer->Tab(n + 2);

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
        tab(n + 1, *fOut);

        // Empty compute
        tab(n + 1, *fOut);
        if (gGlobal->gInPlace) {
            *fOut << genVirtual()
                  << subst("void compute(int $0, $1** inputs, $1** outputs) {}", fFullCount,
                           xfloat());
        } else {
            *fOut << genVirtual()
                  << subst("void compute(int $0, $1** RESTRICT inputs, $1** RESTRICT outputs) {}",
                           fFullCount, xfloat());
        }
    } else {
        // Compute
        generateCompute(n);
    }

    // Interaction with the MemoryManager
    if (gGlobal->gMemoryManager == 0 || gGlobal->gMemoryManager == 1) {
        // 'memoryInfo' method generation
        tab(n + 1, *fOut);
        tab(n + 1, *fOut);
        *fOut << "static void memoryInfo() {";
        tab(n + 2, *fOut);

        // Count arrays
        int ptr_count = 0;
        for (const auto& it : fMemoryLayout) {
            bool do_count = (gGlobal->gMemoryManager == 0)
                                ? isPtr(it.type)
                                : (isPtr(it.type) || isControlOrZone(it.name));
            if (do_count) {
                ptr_count++;
            }
        }

        *fOut << "fManager->begin(" << ptr_count << ");";
        tab(n + 2, *fOut);

        for (size_t i = 0; i < fMemoryLayout.size(); i++) {
            // DSP or field name, type, size, size-in-bytes, reads, write
            MemoryLayoutItem item   = fMemoryLayout[i];
            bool             do_gen = (gGlobal->gMemoryManager == 0)
                                          ? isPtr(item.type)
                                          : (isPtr(item.type) || isControlOrZone(item.name));
            if (do_gen) {
                *fOut << "// " << item.name;
                tab(n + 2, *fOut);
                *fOut << "fManager->info(" << item.size_bytes << ", " << item.read << ", "
                      << item.write << ");";
                tab(n + 2, *fOut);
            }
        }

        *fOut << "fManager->end();";
        tab(n + 2, *fOut);
        back(1, *fOut);
        *fOut << "}";

        // memoryCreate
        tab(n + 1, *fOut);
        tab(n + 1, *fOut);
        *fOut << "void memoryCreate() {";
        tab(n + 2, *fOut);
        for (size_t i = 0; i < fMemoryLayout.size(); i++) {
            // DSP or field name, type, size, sizeBytes, reads, writes
            MemoryLayoutItem item = fMemoryLayout[i];
            bool do_gen = (gGlobal->gMemoryManager == 0) ? (isPtr(item.type) && item.size > 0)
                                                         : isControlOrZone(item.name);
            if (do_gen) {
                if (item.type == "kInt32_ptr") {
                    *fOut << item.name << " = static_cast<int*>(fManager->allocate("
                          << item.size_bytes << "));";
                } else {
                    *fOut << item.name << " = static_cast<" << ifloat() << "*>(fManager->allocate("
                          << item.size_bytes << "));";
                }
                tab(n + 2, *fOut);
            }
        }
        back(1, *fOut);
        *fOut << "}";

        // memoryDestroy
        tab(n + 1, *fOut);
        tab(n + 1, *fOut);
        *fOut << "void memoryDestroy() {";
        tab(n + 2, *fOut);
        for (size_t i = 0; i < fMemoryLayout.size(); i++) {
            // DSP or field name, type, size, sizeBytes, reads, writes
            MemoryLayoutItem item = fMemoryLayout[i];
            bool do_gen = (gGlobal->gMemoryManager == 0) ? (isPtr(item.type) && item.size > 0)
                                                         : isControlOrZone(item.name);
            if (do_gen) {
                *fOut << "fManager->destroy(" << item.name << ");";
                tab(n + 2, *fOut);
            }
        }
        back(1, *fOut);
        *fOut << "}";
        tab(n, *fOut);

        // Static constructor
        tab(n + 1, *fOut);
        *fOut << "static " << fKlassName << "* create() {";
        tab(n + 2, *fOut);
        *fOut << fKlassName << "* dsp = new (fManager->allocate(sizeof(" << fKlassName << "))) "
              << fKlassName << "();";
        tab(n + 2, *fOut);
        *fOut << "dsp->memoryCreate();";
        tab(n + 2, *fOut);
        *fOut << "return dsp;";
        tab(n + 1, *fOut);
        *fOut << "}";

        // Static destructor
        tab(n + 1, *fOut);
        tab(n + 1, *fOut);
        *fOut << "static void destroy(dsp* dsp) {";
        tab(n + 2, *fOut);
        *fOut << "static_cast<" << fKlassName << "*>(dsp)->memoryDestroy();";
        tab(n + 2, *fOut);
        *fOut << "static_cast<" << fKlassName << "*>(dsp)->~" << fKlassName << "();";
        tab(n + 2, *fOut);
        *fOut << "fManager->destroy(dsp);";
        tab(n + 1, *fOut);
        *fOut << "}";
    }

    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "};" << endl;

    // To improve (generalization for all backends...)
    if (gGlobal->gMemoryManager == 0 || gGlobal->gMemoryManager == 1) {
        tab(n, *fOut);
        *fOut << "dsp_memory_manager* " << fKlassName << "::fManager = nullptr;" << endl;
    }

    // Generate user interface macros if needed
    printMacros(*fOut, n);

    if (gGlobal->gNamespace != "" && gGlobal->gArchFile == "") {
        tab(n, *fOut);
        *fOut << "} // namespace " << gGlobal->gNamespace << endl;
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
}

void CPPScalarCodeContainer::generateCompute(int n)
{
    // Generates declaration
    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    if (gGlobal->gInPlace) {
        *fOut << genVirtual()
              << subst("void compute(int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
    } else {
        *fOut << genVirtual()
              << subst("void compute(int $0, $1** RESTRICT inputs, $1** RESTRICT outputs) {",
                       fFullCount, xfloat());
    }
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);

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
    *fOut << "}";
}

// Vector
CPPVectorCodeContainer::CPPVectorCodeContainer(const string& name, const string& super,
                                               int numInputs, int numOutputs, std::ostream* out)
    : VectorCodeContainer(numInputs, numOutputs),
      CPPCodeContainer(name, super, numInputs, numOutputs, out)
{
}

void CPPVectorCodeContainer::generateCompute(int n)
{
    // Possibly generate separated functions
    fCodeProducer->Tab(n + 1);
    tab(n + 1, *fOut);
    generateComputeFunctions(fCodeProducer);

    // Generates declaration
    tab(n + 1, *fOut);
    if (gGlobal->gInPlace) {
        *fOut << genVirtual()
              << subst("void compute(int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
    } else {
        *fOut << genVirtual()
              << subst("void compute(int $0, $1** RESTRICT inputs, $1** RESTRICT outputs) {",
                       fFullCount, xfloat());
    }
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);

    // Generates local variables declaration and setup
    generateComputeBlock(fCodeProducer);

    // Generates the DSP loop
    fDAGBlock->accept(fCodeProducer);

    back(1, *fOut);
    *fOut << "}";
}

// OpenMP
CPPOpenMPCodeContainer::CPPOpenMPCodeContainer(const string& name, const string& super,
                                               int numInputs, int numOutputs, std::ostream* out)
    : OpenMPCodeContainer(numInputs, numOutputs),
      CPPCodeContainer(name, super, numInputs, numOutputs, out)
{
}

void CPPOpenMPCodeContainer::generateCompute(int n)
{
    // Possibly generate separated functions
    fCodeProducer->Tab(n + 1);
    tab(n + 1, *fOut);
    generateComputeFunctions(fCodeProducer);

    // Generates declaration
    tab(n + 1, *fOut);
    if (gGlobal->gInPlace) {
        *fOut << genVirtual()
              << subst("void compute(int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
    } else {
        *fOut << genVirtual()
              << subst("void compute(int $0, $1** RESTRICT inputs, $1** RESTRICT outputs) {",
                       fFullCount, xfloat());
    }
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);

    // Generates local variables declaration and setup
    generateComputeBlock(fCodeProducer);

    // Generate DSP loop
    fGlobalLoopBlock->accept(fCodeProducer);

    back(1, *fOut);
    *fOut << "}";
}

// Works stealing scheduler
CPPWorkStealingCodeContainer::CPPWorkStealingCodeContainer(const string& name, const string& super,
                                                           int numInputs, int numOutputs,
                                                           std::ostream* out)
    : WSSCodeContainer(numInputs, numOutputs, "this"),
      CPPCodeContainer(name, super, numInputs, numOutputs, out)
{
}

void CPPWorkStealingCodeContainer::produceClass()
{
    int n = 0;

    // Inherited method
    CPPCodeContainer::produceClass();

    tab(n, *fOut);
    *fOut << "extern \"C\" void computeThreadExternal(void* dsp, int num_thread) {";
    tab(n + 1, *fOut);
    *fOut << "static_cast<" << fKlassName << "*>(dsp)->computeThread" << fKlassName
          << "(num_thread);";
    tab(n, *fOut);
    *fOut << "}" << endl;
}

void CPPWorkStealingCodeContainer::generateCompute(int n)
{
    // Possibly generate separated functions
    fCodeProducer->Tab(n + 1);
    tab(n + 1, *fOut);
    generateComputeFunctions(fCodeProducer);

    // Generates declaration
    tab(n + 1, *fOut);
    if (gGlobal->gInPlace) {
        *fOut << genVirtual()
              << subst("void compute(int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
    } else {
        *fOut << genVirtual()
              << subst("void compute(int $0, $1** RESTRICT inputs, $1** RESTRICT outputs) {",
                       fFullCount, xfloat());
    }
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);

    // Generates local variables declaration and setup
    generateComputeBlock(fCodeProducer);

    // tab(n + 1, *fOut);
    back(1, *fOut);
    *fOut << "}" << endl;

    // Generates "computeThread" code
    tab(n + 1, *fOut);
    *fOut << "void computeThread" << fKlassName << "(int num_thread) {";
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);

    // Generate it
    faustassert(fThreadLoopBlock);
    fThreadLoopBlock->accept(fCodeProducer);

    back(1, *fOut);
    *fOut << "}";
}
