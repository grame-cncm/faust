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

#include "cpp_code_container.hh"
#include "Text.hh"
#include "cpp_gpu_code_container.hh"
#include "exception.hh"
#include "fir_to_fir.hh"
#include "floats.hh"
#include "global.hh"

using namespace std;

/*
 C++ backend and module description:
    - in -os mode:
        - subcontainers are merged in the main class
        - CPPScalarOneSampleCodeContainer1 (used in -os0) separates the DSP control state in iControl and fControl (possibly to be allocated elsewhere)
        - CPPScalarOneSampleCodeContainer2 (used in -os1) separates the DSP control state in iControl and fControl and the DSP state in iZone and fZone (possibly to be allocated elsewhere)
 */

map<string, bool> CPPInstVisitor::gFunctionSymbolTable;

dsp_factory_base* CPPCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(
        fKlassName, "", "",
        ((dynamic_cast<ostringstream*>(fOut)) ? dynamic_cast<ostringstream*>(fOut)->str() : ""), "");
}

CodeContainer* CPPCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    if (gGlobal->gOneSample == 0) {
        return new CPPScalarOneSampleCodeContainer1(name, "", 0, 1, fOut, sub_container_type);
    } else if (gGlobal->gOneSample == 1) {
        return new CPPScalarOneSampleCodeContainer1(name, "", 0, 1, fOut, sub_container_type);
    } else {
        return new CPPScalarCodeContainer(name, "", 0, 1, fOut, sub_container_type);
    }
 }

CodeContainer* CPPCodeContainer::createContainer(const string& name, const string& super, int numInputs, int numOutputs,
                                                 ostream* dst)
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
        if (gGlobal->gOneSample == 0) {
            container = new CPPScalarOneSampleCodeContainer1(name, super, numInputs, numOutputs, dst, kInt);
        } else if (gGlobal->gOneSample == 1) {
            container = new CPPScalarOneSampleCodeContainer2(name, super, numInputs, numOutputs, dst, kInt);
        } else {
            container = new CPPScalarCodeContainer(name, super, numInputs, numOutputs, dst, kInt);
        }
    }

    return container;
}

// Scalar
CPPScalarCodeContainer::CPPScalarCodeContainer(const string& name, const string& super, int numInputs, int numOutputs,
                                               std::ostream* out, int sub_container_type)
: CPPCodeContainer(name, super, numInputs, numOutputs, out)
{
    fSubContainerType = sub_container_type;
}

void CPPCodeContainer::produceMetadata(int tabs)
{
    tab(tabs, *fOut);
    *fOut << "void metadata(Meta* m) { ";

    // We do not want to accumulate metadata from all hierachical levels, so the upper level only is kept
    for (const auto& i : gGlobal->gMetaDataSet) {
        if (i.first != tree("author")) {
            tab(tabs + 1, *fOut);
            *fOut << "m->declare(\"" << *(i.first) << "\", " << **(i.second.begin()) << ");";
        } else {
            // But the "author" meta data is accumulated, the upper level becomes the main author and sub-levels become
            // "contributor"
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
    if (gGlobal->gMemoryManager) {
        tab(tabs, *fOut);
        *fOut << "virtual void init(int sample_rate) {}";
    } else {
        tab(tabs, *fOut);
        *fOut << "virtual void init(int sample_rate) {";
        tab(tabs + 1, *fOut);
        *fOut << "classInit(sample_rate);";
        tab(tabs + 1, *fOut);
        *fOut << "instanceInit(sample_rate);";
        tab(tabs, *fOut);
        *fOut << "}";
    }

    tab(tabs, *fOut);
    *fOut << "virtual void instanceInit(int sample_rate) {";
    tab(tabs + 1, *fOut);
    *fOut << "instanceConstants(sample_rate);";
    tab(tabs + 1, *fOut);
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
    fCodeProducer->Tab(n + 1);
    generateDeclarations(fCodeProducer);

    tab(n, *fOut);
    *fOut << "  public:";

    tab(n + 1, *fOut);
    tab(n + 1, *fOut);

    // fKlassName used in method naming for subclasses
    produceInfoFunctions(n + 1, fKlassName, "dsp", true, false, fCodeProducer);
    
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
        *fOut << "void fill" << fKlassName << subst("(int $0, $1* " + fTableName + ") {", counter, ifloat());
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

void CPPCodeContainer::produceClass()
{
    int n = 0;
   
    // Libraries
    printLibrary(*fOut);
    printIncludeFile(*fOut);
    
    if (gGlobal->gNameSpace != "" && gGlobal->gArchFile == "") {
        tab(n, *fOut);
        *fOut << "namespace " << gGlobal->gNameSpace << " {" << endl;
    }

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
    fCodeProducer->Tab(n + 1);
    tab(n + 1, *fOut);
    generateDeclarations(fCodeProducer);

    if (fAllocateInstructions->fCode.size() > 0) {
        tab(n + 1, *fOut);
        *fOut << "void allocate() {";
        tab(n + 2, *fOut);
        fCodeProducer->Tab(n + 2);
        generateAllocate(fCodeProducer);
        back(1, *fOut);
        *fOut << "}";
        tab(n + 1, *fOut);
    }

    if (fDestroyInstructions->fCode.size() > 0) {
        tab(n + 1, *fOut);
        *fOut << "void destroy() {";
        tab(n + 2, *fOut);
        fCodeProducer->Tab(n + 2);
        generateDestroy(fCodeProducer);
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
        *fOut << "virtual ~" << fKlassName << "() {";
        tab(n + 2, *fOut);
        *fOut << "destroy();";
        tab(n + 1, *fOut);
        *fOut << "}" << endl;
    }

    tab(n + 1, *fOut);
    // No class name for main class
    produceInfoFunctions(n + 1, "", "dsp", true, true, fCodeProducer);  // Inits

    // TODO
    /*
    generateStaticInitFun("classInit", true)->accept(fCodeProducer);
    generateInstanceInitFun("instanceInit", true, true)->accept(fCodeProducer);
    */

    tab(n + 1, *fOut);
    *fOut << "static void classInit(int sample_rate) {";
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    generateStaticInit(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";

    if (gGlobal->gMemoryManager) {
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
            DeclareFunInst* inst_init_fun = (*it)->generateInstanceInitFun("instanceInit" + (*it)->getClassName(), true,
            false);
            InlineVoidFunctionCall inliner1(inst_init_fun); 
            res1 = inliner1.getCode(res1); 
            DeclareFunInst* fill_fun = (*it)->generateFillFun("fill" + (*it)->getClassName(), true, false); 
            InlineVoidFunctionCall inliner2(fill_fun); 
            res1 = inliner2.getCode(res1);
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
    *fOut << "virtual void instanceConstants(int sample_rate) {";
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    generateInit(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    tab(n + 1, *fOut);
    *fOut << "virtual void instanceResetUserInterface() {";
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    generateResetUserInterface(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

    tab(n + 1, *fOut);
    *fOut << "virtual void instanceClear() {";
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
            DeclareFunInst* inst_init_fun = (*it)->generateInstanceInitFun("instanceInit" + (*it)->getClassName(), true,false);
            InlineVoidFunctionCall inliner1(inst_init_fun);
            res1 = inliner1.getCode(res1);
            res2 = inliner1.getCode(res2);
            DeclareFunInst* fill_fun = (*it)->generateFillFun("fill" + (*it)->getClassName(), true, false);
            InlineVoidFunctionCall inliner2(fill_fun);
            res1 = inliner2.getCode(res1);
            res2 = inliner2.getCode(res2);
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
    tab(n + 1, *fOut);
    *fOut << "virtual " << fKlassName << "* clone() {";
    tab(n + 2, *fOut);
    *fOut << "return new " << fKlassName << "();";
    tab(n + 1, *fOut);
    *fOut << "}";

    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);
    tab(n + 1, *fOut);
    generateGetSampleRate("getSampleRate", "dsp", true, true)->accept(fCodeProducer);

    // User interface
    tab(n + 1, *fOut);
    *fOut << "virtual void buildUserInterface(UI* ui_interface) {";
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    generateUserInterface(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";

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

// Used with -os0 option
void CPPScalarOneSampleCodeContainer1::produceClass()
{
    int n = 0;
   
    // Libraries
    printLibrary(*fOut);
    printIncludeFile(*fOut);
    
    if (gGlobal->gNameSpace != "" && gGlobal->gArchFile == "") {
        tab(n, *fOut);
        *fOut << "namespace " << gGlobal->gNameSpace << " {" << endl;
    }
 
    // Sub containers are merged in the main class
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
    tab(n, *fOut);
    
    *fOut << "#if defined(_WIN32)" << endl;
    *fOut << "#define RESTRICT __restrict" << endl;
    *fOut << "#else" << endl;
    *fOut << "#define RESTRICT __restrict__" << endl;
    *fOut << "#endif" << endl;
    tab(n, *fOut);
    
    *fOut << "#define FAUST_INT_CONTROLS " << fInt32ControlNum  << endl;
    *fOut << "#define FAUST_REAL_CONTROLS " << fRealControlNum;
    tab(n, *fOut);
    
    tab(n, *fOut);
    fSuperKlassName = "one_sample_dsp";
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
    fCodeProducer->Tab(n + 1);
    tab(n + 1, *fOut);
    generateDeclarations(fCodeProducer);
    
    if (fAllocateInstructions->fCode.size() > 0) {
        tab(n + 1, *fOut);
        *fOut << "void allocate() {";
        tab(n + 2, *fOut);
        fCodeProducer->Tab(n + 2);
        generateAllocate(fCodeProducer);
        back(1, *fOut);
        *fOut << "}";
        tab(n + 1, *fOut);
    }
    
    if (fDestroyInstructions->fCode.size() > 0) {
        tab(n + 1, *fOut);
        *fOut << "void destroy() {";
        tab(n + 2, *fOut);
        fCodeProducer->Tab(n + 2);
        generateDestroy(fCodeProducer);
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
        *fOut << "virtual ~" << fKlassName << "() {";
        tab(n + 2, *fOut);
        *fOut << "destroy();";
        tab(n + 1, *fOut);
        *fOut << "}" << endl;
    }
    
    // Constructor
    tab(n + 1, *fOut);
    *fOut << fKlassName << "() {}";
    tab(n + 1, *fOut);
    *fOut << fKlassName << "(int* icontrol, FAUSTFLOAT* fcontrol)";
    *fOut << ":one_sample_dsp(icontrol, fcontrol) {}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    // No class name for main class
    produceInfoFunctions(n + 1, "", "dsp", true, true, fCodeProducer);  // Inits
    
    // Dummy
    tab(n + 1, *fOut);
    *fOut << "static void classInit(int sample_rate) {}";
    tab(n, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << "void staticInit(int sample_rate) {";
    {
        tab(n + 2, *fOut);
        fCodeProducer->Tab(n + 2);
        // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
        inlineSubcontainersFunCalls(fStaticInitInstructions)->accept(fCodeProducer);
    }
    back(1, *fOut);
    *fOut << "}";
    
    if (gGlobal->gMemoryManager) {
        tab(n + 1, *fOut);
        *fOut << "static void classDestroy() {";
        tab(n + 2, *fOut);
        fCodeProducer->Tab(n + 2);
        generateStaticDestroy(fCodeProducer);
        back(1, *fOut);
        *fOut << "}";
    }
  
    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << "virtual void instanceConstants(int sample_rate) {";
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    generateInit(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << "virtual void instanceResetUserInterface() {";
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    generateResetUserInterface(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << "virtual void instanceClear() {";
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    generateClear(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    // Init
    if (gGlobal->gMemoryManager) {
        tab(n + 1, *fOut);
        *fOut << "virtual void init(int sample_rate) {}";
    } else {
        tab(n + 1, *fOut);
        *fOut << "virtual void init(int sample_rate) {";
        tab(n + 2, *fOut);
        *fOut << "instanceInit(sample_rate);";
        tab(n + 1, *fOut);
        *fOut << "}";
    }
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << "virtual void instanceInit(int sample_rate) {";
    // staticInit has to be called for each instance since the tables are actually not shared between instances
    tab(n + 2, *fOut);
    *fOut << "staticInit(sample_rate);";
    tab(n + 2, *fOut);
    *fOut << "instanceConstants(sample_rate);";
    tab(n + 2, *fOut);
    *fOut << "instanceResetUserInterface();";
    tab(n + 2, *fOut);
    *fOut << "instanceClear();";
    tab(n + 1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << "virtual " << fKlassName << "* clone() {";
    tab(n + 2, *fOut);
    *fOut << "return new " << fKlassName << "();";
    tab(n + 1, *fOut);
    *fOut << "}";
    
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);
    tab(n + 1, *fOut);
    generateGetSampleRate("getSampleRate", "dsp", true, true)->accept(fCodeProducer);
    
    // User interface
    tab(n + 1, *fOut);
    *fOut << "virtual void buildUserInterface(UI* ui_interface) {";
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    generateUserInterface(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << subst("virtual void control(int* RESTRICT iControl, $0* RESTRICT fControl) {", xfloat());
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    // Generates local variables declaration and setup
    generateComputeBlock(fCodeProducer);
    back(1, *fOut);
    *fOut << "}" << endl;
    
    tab(n + 1, *fOut);
    *fOut << "virtual int getNumIntControls() { return " << fInt32ControlNum << "; }";
    tab(n + 1, *fOut);
    *fOut << "virtual int getNumRealControls() { return " << fRealControlNum << "; }";
    
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

// Used with -os1 option
void CPPScalarOneSampleCodeContainer2::produceClass()
{
    int n = 0;
    
    // Libraries
    printLibrary(*fOut);
    printIncludeFile(*fOut);
    
    if (gGlobal->gNameSpace != "" && gGlobal->gArchFile == "") {
        tab(n, *fOut);
        *fOut << "namespace " << gGlobal->gNameSpace << " {" << endl;
    }
    
    // Sub containers are merged in the main class
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
    tab(n, *fOut);
    
    *fOut << "#if defined(_WIN32)" << endl;
    *fOut << "#define RESTRICT __restrict" << endl;
    *fOut << "#else" << endl;
    *fOut << "#define RESTRICT __restrict__" << endl;
    *fOut << "#endif" << endl;
    
    tab(n, *fOut);
    fSuperKlassName = "one_sample_dsp_real<" + string(ifloat()) + ">";
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
    fCodeProducer->Tab(n + 1);
    tab(n + 1, *fOut);
    generateDeclarations(fCodeProducer);
    
    // Kept here because staticInit incorrectly change the size later on
    int int_zone_size = static_cast<CPPInstVisitor1*>(fCodeProducer)->getIntZoneSize();
    int real_zone_size = static_cast<CPPInstVisitor1*>(fCodeProducer)->getRealZoneSize();
    
    if (fAllocateInstructions->fCode.size() > 0) {
        tab(n + 1, *fOut);
        *fOut << "void allocate() {";
        tab(n + 2, *fOut);
        fCodeProducer->Tab(n + 2);
        generateAllocate(fCodeProducer);
        back(1, *fOut);
        *fOut << "}";
        tab(n + 1, *fOut);
    }
    
    if (fDestroyInstructions->fCode.size() > 0) {
        tab(n + 1, *fOut);
        *fOut << "void destroy() {";
        tab(n + 2, *fOut);
        fCodeProducer->Tab(n + 2);
        generateDestroy(fCodeProducer);
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
        *fOut << "virtual ~" << fKlassName << "() {";
        tab(n + 2, *fOut);
        *fOut << "destroy();";
        tab(n + 1, *fOut);
        *fOut << "}" << endl;
    }
    
    // Constructor
    tab(n + 1, *fOut);
    *fOut << fKlassName << "() {}";
    tab(n + 1, *fOut);
    *fOut << fKlassName << "(int* icontrol, FAUSTFLOAT* fcontrol, int* izone, " << ifloat() << "* fzone)";
    *fOut << ":one_sample_dsp_real(icontrol, fcontrol, izone, fzone) {}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    // No class name for main class
    produceInfoFunctions(n + 1, "", "dsp", true, true, fCodeProducer);  // Inits
    
    // Dummy
    tab(n + 1, *fOut);
    *fOut << "static void classInit(int sample_rate) {}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << "void staticInit(int sample_rate, " << subst("int* iZone, $0* fZone) {", ifloat());
    {
        tab(n + 2, *fOut);
        fCodeProducer->Tab(n + 2);
        // For waveform
        MoveVariablesInFront3().getCode(fGlobalDeclarationInstructions)->accept(fCodeProducer);
        // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
        inlineSubcontainersFunCalls(fStaticInitInstructions)->accept(fCodeProducer);
    }
    back(1, *fOut);
    *fOut << "}";
    
    if (gGlobal->gMemoryManager) {
        tab(n + 1, *fOut);
        *fOut << "static void classDestroy() {";
        tab(n + 2, *fOut);
        fCodeProducer->Tab(n + 2);
        generateStaticDestroy(fCodeProducer);
        back(1, *fOut);
        *fOut << "}";
    }
    
    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << "virtual void instanceConstants(int sample_rate, " << subst("int* iZone, $0* fZone) {", ifloat());
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    generateInit(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << "virtual void instanceResetUserInterface() {";
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    generateResetUserInterface(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << "virtual void instanceClear(" << subst("int* iZone, $0* fZone) {", ifloat());
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    generateClear(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    // Init
    if (gGlobal->gMemoryManager) {
        tab(n + 1, *fOut);
        *fOut << "virtual void init(int sample_rate, " << subst("int* iZone, $0* fZone) {", ifloat());
    } else {
        tab(n + 1, *fOut);
        *fOut << "virtual void init(int sample_rate, " << subst("int* iZone, $0* fZone) {", ifloat());
        tab(n + 2, *fOut);
        *fOut << "instanceInit(sample_rate, iZone, fZone);";
        tab(n + 1, *fOut);
        *fOut << "}";
    }
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << "virtual void instanceInit(int sample_rate, " << subst("int* iZone, $0* fZone) {", ifloat());
    // staticInit has to be called for each instance since the tables are actually not shared between instances
    tab(n + 2, *fOut);
    *fOut << "staticInit(sample_rate, iZone, fZone);";
    tab(n + 2, *fOut);
    *fOut << "instanceConstants(sample_rate, iZone, fZone);";
    tab(n + 2, *fOut);
    *fOut << "instanceResetUserInterface();";
    tab(n + 2, *fOut);
    *fOut << "instanceClear(iZone, fZone);";
    tab(n + 1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << "virtual " << fKlassName << "* clone() {";
    tab(n + 2, *fOut);
    *fOut << "return new " << fKlassName << "();";
    tab(n + 1, *fOut);
    *fOut << "}";
    
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);
    tab(n + 1, *fOut);
    generateGetSampleRate("getSampleRate", "dsp", true, true)->accept(fCodeProducer);
    
    // User interface
    tab(n + 1, *fOut);
    *fOut << "virtual void buildUserInterface(UI* ui_interface) {";
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    generateUserInterface(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << subst("virtual void control(int* RESTRICT iControl, $0* RESTRICT fControl, int* RESTRICT iZone, $1* RESTRICT fZone) {", xfloat(), ifloat());
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    // Generates local variables declaration and setup
    generateComputeBlock(fCodeProducer);
    back(1, *fOut);
    *fOut << "}" << endl;
    
    tab(n + 1, *fOut);
    *fOut << "virtual int getNumIntControls() { return " << fInt32ControlNum << "; }";
    tab(n + 1, *fOut);
    
    *fOut << "virtual int getNumRealControls() { return " << fRealControlNum << "; }";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << "virtual int getiZoneSize() { return " << int_zone_size << "; }";
    
    tab(n + 1, *fOut);
    *fOut << "virtual int getfZoneSize() { return " << real_zone_size << "; }";
    
    // Compute
    generateCompute(n);
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "};" << endl;
    
    tab(n, *fOut);
    *fOut << "#define FAUST_INT_CONTROLS " << fInt32ControlNum << endl;
    *fOut << "#define FAUST_REAL_CONTROLS " << fRealControlNum << endl;
    
    tab(n, *fOut);
    *fOut << "#define FAUST_INT_ZONE " << int_zone_size << endl;
    *fOut << "#define FAUST_FLOAT_ZONE " << real_zone_size;
    tab(n, *fOut);
    
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

void CPPScalarCodeContainer::generateCompute(int n)
{
    // Generates declaration
    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    *fOut << subst("virtual void compute(int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
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

// Used with -os0 option
void CPPScalarOneSampleCodeContainer1::generateCompute(int n)
{
    // Generates declaration
    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    if (gGlobal->gInPlace) {
        *fOut << subst("virtual void compute($0* inputs, $0* outputs, int* RESTRICT iControl, $0* RESTRICT fControl) {", xfloat());
    } else {
        *fOut << subst("virtual void compute($0* RESTRICT inputs, $0* RESTRICT outputs, int* RESTRICT iControl, $0* RESTRICT fControl) {", xfloat());
    }
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    
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
}

// Used with -os1 option
void CPPScalarOneSampleCodeContainer2::generateCompute(int n)
{
    // Generates declaration
    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    if (gGlobal->gInPlace) {
        *fOut << subst("virtual void compute($0* inputs, $0* outputs, int* RESTRICT iControl, $0* RESTRICT fControl, int* RESTRICT iZone, $1* RESTRICT fZone) {", xfloat(), ifloat());
    } else {
        *fOut << subst("virtual void compute($0* RESTRICT inputs, $0* RESTRICT outputs, int* RESTRICT iControl, $0* RESTRICT fControl, int* RESTRICT iZone, $1* RESTRICT fZone) {", xfloat(), ifloat());
    }
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    
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
}

// Vector
CPPVectorCodeContainer::CPPVectorCodeContainer(const string& name, const string& super, int numInputs, int numOutputs,
                                               std::ostream* out)
    : VectorCodeContainer(numInputs, numOutputs), CPPCodeContainer(name, super, numInputs, numOutputs, out)
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
    *fOut << subst("virtual void compute(int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
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
CPPOpenMPCodeContainer::CPPOpenMPCodeContainer(const string& name, const string& super, int numInputs, int numOutputs,
                                               std::ostream* out)
    : OpenMPCodeContainer(numInputs, numOutputs), CPPCodeContainer(name, super, numInputs, numOutputs, out)
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
    *fOut << subst("virtual void compute(int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
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
CPPWorkStealingCodeContainer::CPPWorkStealingCodeContainer(const string& name, const string& super, int numInputs,
                                                           int numOutputs, std::ostream* out)
    : WSSCodeContainer(numInputs, numOutputs, "this"), CPPCodeContainer(name, super, numInputs, numOutputs, out)
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
    *fOut << "static_cast<" << fKlassName << "*>(dsp)->computeThread" << fKlassName << "(num_thread);";
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
    *fOut << subst("virtual void compute(int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);

    // Generates local variables declaration and setup
    generateComputeBlock(fCodeProducer);

    //tab(n + 1, *fOut);
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
