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
 
    1) in -os mode:
        - subcontainers are merged in the main class: in -os0 mode,  static tables are allocated as global, and in iZone/fZone in -os(1|2|3) modes
        - CPPScalarOneSampleCodeContainer1 (used in -os0) separates the DSP control state in iControl/fControl (possibly to be allocated elsewhere)
        - CPPScalarOneSampleCodeContainer2 (used in -os1) separates the DSP control state in iControl/fControl and the DSP state in iZone/fZone (possibly to be allocated elsewhere)
        - CPPScalarOneSampleCodeContainer3 (used in -os2) separates the DSP control state in iControl/fControl and the DSP state in iZone/fZone (possibly to be allocated elsewhere). Short delay lines remain in DSP struct, long delay lines are moved in iZone/fZone.
        Additional functions 'instanceConstantsFromMem' and 'instanceConstantsToMem' to copy iConst/fConst variables from/to memory are generated.
        - CPPScalarOneSampleCodeContainer4 (used in -os3) is similar to CPPScalarOneSampleCodeContainer3, but iControl/fControl and iZone/fZone pointers stay in the DSP class. The -mem option uses the memory manager to allocate/destroy the iControl/fControl and iZone/fZone pointers
 
    2) in -fx mode:
        - then/else branches of 'select2' are explicitly casted to 'float', otherwise AP_fixed compilation may trigger "ambigous type" errors
        - all math operators are named "FOOfx" and are supposed to be implemented in the architecture file (doing the proper cast on arguments and return value when needed)
 */

map<string, bool> CPPInstVisitor::gFunctionSymbolTable;

dsp_factory_base* CPPCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(
        fKlassName, "", "",
        ((dynamic_cast<ostringstream*>(fOut)) ? dynamic_cast<ostringstream*>(fOut)->str() : ""), "");
}

CodeContainer* CPPCodeContainer::createScalarContainer(const std::string& name, const std::string& super, int numInputs, int numOutputs, ostream* dst, int sub_container_type)
{
    if (gGlobal->gOneSample == 0) {
        return new CPPScalarOneSampleCodeContainer1(name,super, numInputs, numOutputs, dst, sub_container_type);
    } else if (gGlobal->gOneSample == 1) {
        return new CPPScalarOneSampleCodeContainer2(name, super, numInputs, numOutputs, dst, sub_container_type);
    } else if (gGlobal->gOneSample == 2) {
        return new CPPScalarOneSampleCodeContainer3(name, super, numInputs, numOutputs, dst, sub_container_type);
    } else if (gGlobal->gOneSample == 3) {
        return new CPPScalarOneSampleCodeContainer4(name, super, numInputs, numOutputs, dst, sub_container_type);
    } else {
        return new CPPScalarCodeContainer(name, super, numInputs, numOutputs, dst, sub_container_type);
    }
}

CodeContainer* CPPCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return createScalarContainer(name, "", 0, 1, fOut, sub_container_type);
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
        *fOut << genVirtual() << "void init(int sample_rate) {}";
    } else {
        tab(tabs, *fOut);
        *fOut << genVirtual() << "void init(int sample_rate) {";
        tab(tabs + 1, *fOut);
        *fOut << "classInit(sample_rate);";
        tab(tabs + 1, *fOut);
        *fOut << "instanceInit(sample_rate);";
        tab(tabs, *fOut);
        *fOut << "}";
    }

    tab(tabs, *fOut);
    *fOut << genVirtual() << "void instanceInit(int sample_rate) {";
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
    
    if (gGlobal->gNamespace != "" && gGlobal->gArchFile == "") {
        tab(n, *fOut);
        *fOut << "namespace " << gGlobal->gNamespace << " {" << endl;
    }
 
    generateHeader(n);

    // Generate gub containers
    generateSubContainers();
    
    // Global declarations
    tab(n, *fOut);
    fCodeProducer->Tab(n);
    generateGlobalDeclarations(fCodeProducer);
    
    tab(n, *fOut);
    if (fSuperKlassName != "") {
        *fOut << "class " << fKlassName << genFinal() << " : public " << fSuperKlassName << " {";
    } else {
        *fOut << "class " << fKlassName << genFinal() << " {";
    }
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
    
    // DSP fields as flat arrays are rewritten as pointers
    if (gGlobal->gMemoryManager) {
        ArrayToPointer array_pointer;
        array_pointer.getCode(fDeclarationInstructions)->accept(fCodeProducer);
    } else {
        generateDeclarations(fCodeProducer);
    }

    generateAllocateFun(n);
    generateDestroyFun(n);

    tab(n, *fOut);
    *fOut << " public:";

    if (gGlobal->gMemoryManager) {
        tab(n + 1, *fOut);
        *fOut << "static dsp_memory_manager* fManager;";
    }
    
    // Default constructor
    string fun_proto1 = fKlassName + "()";
    generateConstructor(fun_proto1, n);
   
    generateDestructor(n);
 
    // Print metadata declaration
    produceMetadata(n + 1);

    // No class name for main class
    tab(n + 1, *fOut);
    if (gGlobal->gNoVirtual) {
        produceInfoFunctions(n + 1, "", "dsp", true, FunTyped::kStaticConstExpr, fCodeProducer, "getStaticNumInputs", "getStaticNumOutputs");
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
    *fOut << "static void classInit(int sample_rate) {";
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    generateStaticInit(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";

    if (gGlobal->gMemoryManager) {
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
    *fOut << genVirtual() << "void instanceConstants(int sample_rate) {";
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    generateInit(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);

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
    *fOut << genVirtual() << fKlassName << "* clone() {";
    tab(n + 2, *fOut);
    if (gGlobal->gMemoryManager) {
        *fOut << "return create();";
   } else {
        *fOut << "return new " << fKlassName << "();";
    }
    tab(n + 1, *fOut);
    *fOut << "}";

    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);
    tab(n + 1, *fOut);
    generateGetSampleRate("getSampleRate", "dsp", true, !gGlobal->gNoVirtual)->accept(fCodeProducer);

    // User interface
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "void buildUserInterface(UI* ui_interface) {";
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    generateUserInterface(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";

    // Compute
    generateCompute(n);
    
    if (gGlobal->gMemoryManager) {
        
        // 'memoryInfo' method generation
        tab(n + 1, *fOut);
        tab(n + 1, *fOut);
        *fOut << "static void memoryInfo() {";
        tab(n + 2, *fOut);
        
        // Count arrays
        int ptr_count = 0;
        for (const auto& it : fMemoryLayout) {
            if (isPtr(get<1>(it))) {
                ptr_count++;
            }
        }
        
        *fOut << "fManager->begin(" << ptr_count << ");";
        tab(n + 2, *fOut);
        
        for (size_t i = 0; i < fMemoryLayout.size(); i++) {
            // DSP or field name, type, size, size-in-bytes, reads, write
            MemoryLayoutItem item = fMemoryLayout[i];
            if (isPtr(get<1>(item))) {
                *fOut << "// " << get<0>(item);
                tab(n + 2, *fOut);
                *fOut << "fManager->info(" << get<3>(item) << ", " << get<4>(item) << ", " << get<5>(item) << ");";
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
            // DSP or field name, type, size, sizeBytes, reads, wri
            MemoryLayoutItem item = fMemoryLayout[i];
            if (get<2>(item) > 1) {
                if (get<1>(item) == "kInt32_ptr") {
                    *fOut << get<0>(item) << " = static_cast<int*>(fManager->allocate(" << get<3>(item) << "));";
                } else {
                    *fOut << get<0>(item) << " = static_cast<" << ifloat() << "*>(fManager->allocate(" << get<3>(item) << "));";
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
            // DSP or field name, type, size, sizeBytes, reads, wri
            MemoryLayoutItem item = fMemoryLayout[i];
            if (get<2>(item) > 1) {
                *fOut << "fManager->destroy(" << get<0>(item) << ");";
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
        *fOut << fKlassName << "* dsp = new (fManager->allocate(sizeof(" << fKlassName << "))) " << fKlassName << "();";
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
        *fOut << "fManager->destroy(dsp);";
        tab(n + 1, *fOut);
        *fOut << "}";
    
        tab(n, *fOut);
        tab(n, *fOut);
    } else {
        tab(n, *fOut);
        tab(n, *fOut);
    }
    
    *fOut << "};" << endl;

    // To improve (generalization for all backends...)
    if (gGlobal->gMemoryManager) {
        tab(n, *fOut);
        *fOut << "dsp_memory_manager* " << fKlassName << "::fManager = nullptr;" << endl;
    }

    // Generate user interface macros if needed
    printMacros(*fOut, n);
    
    if (gGlobal->gNamespace != "" && gGlobal->gArchFile == "") {
        tab(n, *fOut);
        *fOut << "} // namespace " << gGlobal->gNamespace << endl;
    }
}

// Used with -os0 option
void CPPScalarOneSampleCodeContainer1::produceClass()
{
    int n = 0;
   
    // Libraries
    printLibrary(*fOut);
    printIncludeFile(*fOut);
    
    if (gGlobal->gNamespace != "" && gGlobal->gArchFile == "") {
        tab(n, *fOut);
        *fOut << "namespace " << gGlobal->gNamespace << " {" << endl;
    }
 
    // Sub containers are merged in the main class
    mergeSubContainers();
    
    // Global declarations
    tab(n, *fOut);
    fCodeProducer->Tab(n);
    generateGlobalDeclarations(fCodeProducer);
    
    generateHeader(n);
    
    tab(n, *fOut);
    *fOut << "#define FAUST_INT_CONTROLS " << fIntControl->fCurIndex  << endl;
    *fOut << "#define FAUST_REAL_CONTROLS " << fRealControl->fCurIndex;
    tab(n, *fOut);
    
    tab(n, *fOut);
    fSuperKlassName = "one_sample_dsp<" + string(ifloat()) + ">";
    *fOut << "class " << fKlassName << genFinal() << " : public " << fSuperKlassName << " {";
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
    
    generateAllocateFun(n);
    generateDestroyFun(n);
    
    tab(n, *fOut);
    *fOut << " public:";
    
    if (gGlobal->gMemoryManager) {
        tab(n + 1, *fOut);
        *fOut << "static dsp_memory_manager* fManager;";
    }
    
    // Default constructor
    string fun_proto1 = fKlassName + "()";
    generateConstructor(fun_proto1, n);
    
    // Constructor
    stringstream fun_proto2;
    fun_proto2 << fKlassName << "(int* icontrol, " << ifloat() << "* fcontrol):one_sample_dsp(icontrol, fcontrol)";
    generateConstructor(fun_proto2.str(), n);
    
    generateDestructor(n);
   
    // Print metadata declaration
    produceMetadata(n + 1);
    
    // No class name for main class
    tab(n + 1, *fOut);
    if (gGlobal->gNoVirtual) {
        produceInfoFunctions(n + 1, "", "dsp", true, FunTyped::kStaticConstExpr, fCodeProducer, "getStaticNumInputs", "getStaticNumOutputs");
        produceInfoFunctions(n + 1, "", "dsp", true, FunTyped::kDefault, fCodeProducer);
    } else {
        produceInfoFunctions(n + 1, "", "dsp", true, FunTyped::kVirtual, fCodeProducer);
    }
    
    // Dummy
    tab(n + 1, *fOut);
    *fOut << "static void classInit(int sample_rate) {}";
    tab(n + 1, *fOut);
    
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
    *fOut << genVirtual() << "void instanceConstants(int sample_rate) {";
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
    inlineSubcontainersFunCalls(fInitInstructions)->accept(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
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
    
    // Init
    if (gGlobal->gMemoryManager) {
        tab(n + 1, *fOut);
        *fOut << genVirtual() << "void init(int sample_rate) {}";
    } else {
        tab(n + 1, *fOut);
        *fOut << genVirtual() << "void init(int sample_rate) {";
        tab(n + 2, *fOut);
        *fOut << "instanceInit(sample_rate);";
        tab(n + 1, *fOut);
        *fOut << "}";
    }
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "void instanceInit(int sample_rate) {";
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
    *fOut << genVirtual() << fKlassName << "* clone() {";
    tab(n + 2, *fOut);
    *fOut << "return new " << fKlassName << "();";
    tab(n + 1, *fOut);
    *fOut << "}";
    
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);
    tab(n + 1, *fOut);
    generateGetSampleRate("getSampleRate", "dsp", true, !gGlobal->gNoVirtual)->accept(fCodeProducer);
    
    // User interface
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "void buildUserInterface(UI* ui_interface) {";
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    generateUserInterface(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << subst("void control(int* RESTRICT iControl, $0* RESTRICT fControl) {", ifloat());
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    // Generates local variables declaration and setup
    generateComputeBlock(fCodeProducer);
    back(1, *fOut);
    *fOut << "}" << endl;
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "int getNumIntControls() { return " << fIntControl->fCurIndex << "; }";
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "int getNumRealControls() { return " << fRealControl->fCurIndex << "; }";
    
    // Compute
    generateCompute(n);
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "};" << endl;
    
    // To improve (generalization for all backends...)
    if (gGlobal->gMemoryManager) {
        tab(n, *fOut);
        *fOut << "dsp_memory_manager* " << fKlassName << "::fManager = nullptr;" << endl;
    }
    
    // Generate user interface macros if needed
    printMacros(*fOut, n);
    
    if (gGlobal->gNamespace != "" && gGlobal->gArchFile == "") {
        tab(n, *fOut);
        *fOut << "} // namespace " << gGlobal->gNamespace << endl;
    }
}

// Used with -os1 option
void CPPScalarOneSampleCodeContainer2::produceClass()
{
    int n = 0;
    
    // Libraries
    printLibrary(*fOut);
    printIncludeFile(*fOut);
    
    if (gGlobal->gNamespace != "" && gGlobal->gArchFile == "") {
        tab(n, *fOut);
        *fOut << "namespace " << gGlobal->gNamespace << " {" << endl;
    }
    
    // Sub containers are merged in the main class
    mergeSubContainers();
    
    // Global declarations
    tab(n, *fOut);
    fCodeProducer->Tab(n);
    generateGlobalDeclarations(fCodeProducer);
    
    generateHeader(n);
    
    tab(n, *fOut);
    fSuperKlassName = "one_sample_dsp_real<" + string(ifloat()) + ">";
    *fOut << "class " << fKlassName << genFinal() << " : public " << fSuperKlassName << " {";
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
    
    generateAllocateFun(n);
    generateDestroyFun(n);
    
    tab(n, *fOut);
    *fOut << " public:";
    
    if (gGlobal->gMemoryManager) {
        tab(n + 1, *fOut);
        *fOut << "static dsp_memory_manager* fManager;";
    }
    
    // Default constructor
    string fun_proto1 = fKlassName + "()";
    generateConstructor(fun_proto1, n);
    
    // Constructor
    stringstream fun_proto2;
    fun_proto2 << fKlassName << "(int* icontrol, " << ifloat() << "* fcontrol, int* izone, " << ifloat() << "* fzone)";
    fun_proto2 << ":one_sample_dsp_real(icontrol, fcontrol, izone, fzone)";
    generateConstructor(fun_proto2.str(), n);
    
    generateDestructor(n);
     
    // Print metadata declaration
    produceMetadata(n + 1);
    
    // No class name for main class
    tab(n + 1, *fOut);
    if (gGlobal->gNoVirtual) {
        produceInfoFunctions(n + 1, "", "dsp", true, FunTyped::kStaticConstExpr, fCodeProducer, "getStaticNumInputs", "getStaticNumOutputs");
        produceInfoFunctions(n + 1, "", "dsp", true, FunTyped::kDefault, fCodeProducer);
    } else {
        produceInfoFunctions(n + 1, "", "dsp", true, FunTyped::kVirtual, fCodeProducer);
    }
    
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
    *fOut << genVirtual() << "void instanceConstants(int sample_rate, " << subst("int* iZone, $0* fZone) {", ifloat());
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
    inlineSubcontainersFunCalls(fInitInstructions)->accept(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "void instanceResetUserInterface() {";
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    generateResetUserInterface(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "void instanceClear(" << subst("int* iZone, $0* fZone) {", ifloat());
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    generateClear(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    // Init
    if (gGlobal->gMemoryManager) {
        tab(n + 1, *fOut);
        *fOut << genVirtual() << "void init(int sample_rate, " << subst("int* iZone, $0* fZone) {", ifloat());
    } else {
        tab(n + 1, *fOut);
        *fOut << genVirtual() << "void init(int sample_rate, " << subst("int* iZone, $0* fZone) {", ifloat());
        tab(n + 2, *fOut);
        *fOut << "instanceInit(sample_rate, iZone, fZone);";
        tab(n + 1, *fOut);
        *fOut << "}";
    }
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "void instanceInit(int sample_rate, " << subst("int* iZone, $0* fZone) {", ifloat());
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
    *fOut << genVirtual() << fKlassName << "* clone() {";
    tab(n + 2, *fOut);
    *fOut << "return new " << fKlassName << "();";
    tab(n + 1, *fOut);
    *fOut << "}";
    
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);
    tab(n + 1, *fOut);
    generateGetSampleRate("getSampleRate", "dsp", true, !gGlobal->gNoVirtual)->accept(fCodeProducer);
    
    // User interface
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "void buildUserInterface(UI* ui_interface) {";
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    generateUserInterface(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << subst("void control(int* RESTRICT iControl, $0* RESTRICT fControl, int* RESTRICT iZone, $0* RESTRICT fZone) {", ifloat());
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    // Generates local variables declaration and setup
    generateComputeBlock(fCodeProducer);
    back(1, *fOut);
    *fOut << "}" << endl;
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "int getNumIntControls() { return " << fIntControl->fCurIndex << "; }";
    tab(n + 1, *fOut);
    
    *fOut << genVirtual() << "int getNumRealControls() { return " << fRealControl->fCurIndex << "; }";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "int getiZoneSize() { return " << int_zone_size << "; }";
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "int getfZoneSize() { return " << real_zone_size << "; }";
    
    // Compute
    generateCompute(n);
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "};" << endl;
    
    tab(n, *fOut);
    *fOut << "#define FAUST_INT_CONTROLS " << fIntControl->fCurIndex << endl;
    *fOut << "#define FAUST_REAL_CONTROLS " << fRealControl->fCurIndex << endl;
    
    tab(n, *fOut);
    *fOut << "#define FAUST_INT_ZONE " << int_zone_size << endl;
    *fOut << "#define FAUST_FLOAT_ZONE " << real_zone_size;
    tab(n, *fOut);
    
    // To improve (generalization for all backends...)
    if (gGlobal->gMemoryManager) {
        tab(n, *fOut);
        *fOut << "dsp_memory_manager* " << fKlassName << "::fManager = nullptr;" << endl;
    }
    
    // Generate user interface macros if needed
    printMacros(*fOut, n);
    
    if (gGlobal->gNamespace != "" && gGlobal->gArchFile == "") {
        tab(n, *fOut);
        *fOut << "} // namespace " << gGlobal->gNamespace << endl;
    }
}

// Used with -os2 option
void CPPScalarOneSampleCodeContainer3::produceClass()
{
    // Allocate fCodeProducer here
    VariableSizeCounter heap_counter(Address::kStruct);
    generateDeclarations(&heap_counter);
    fCodeProducer = new CPPInstVisitor2(fOut, std::max(0, heap_counter.fSizeBytes - gGlobal->gFPGAMemory));
    
    int n = 0;
    
    // Libraries
    printLibrary(*fOut);
    printIncludeFile(*fOut);
    
    if (gGlobal->gNamespace != "" && gGlobal->gArchFile == "") {
        tab(n, *fOut);
        *fOut << "namespace " << gGlobal->gNamespace << " {" << endl;
    }
    
    // Sub containers are merged in the main class
    mergeSubContainers();
    
    // Global declarations
    tab(n, *fOut);
    fCodeProducer->Tab(n);
    generateGlobalDeclarations(fCodeProducer);
    
    generateHeader(n);
    
    tab(n, *fOut);
    fSuperKlassName = "one_sample_dsp_real<" + string(ifloat()) + ">";
    *fOut << "class " << fKlassName << genFinal() << " : public " << fSuperKlassName << " {";
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
    
    generateAllocateFun(n);
    generateDestroyFun(n);
    
    tab(n, *fOut);
    *fOut << " public:";
    
    if (gGlobal->gMemoryManager) {
        tab(n + 1, *fOut);
        *fOut << "static dsp_memory_manager* fManager;";
    }
    
    // Default constructor
    string fun_proto1 = fKlassName + "()";
    generateConstructor(fun_proto1, n);
    
    stringstream fun_proto2;
    fun_proto2 << fKlassName << "(int* icontrol, " << ifloat() << "* fcontrol, int* izone, " << ifloat() << "* fzone)";
    fun_proto2 << ":one_sample_dsp_real(icontrol, fcontrol, izone, fzone)";
    generateConstructor(fun_proto2.str(), n);
    
    generateDestructor(n);
    
    // Print metadata declaration
    produceMetadata(n + 1);
    
    // No class name for main class
    tab(n + 1, *fOut);
    if (gGlobal->gNoVirtual) {
        produceInfoFunctions(n + 1, "", "dsp", true, FunTyped::kStaticConstExpr, fCodeProducer, "getStaticNumInputs", "getStaticNumOutputs");
        produceInfoFunctions(n + 1, "", "dsp", true, FunTyped::kDefault, fCodeProducer);
    } else {
        produceInfoFunctions(n + 1, "", "dsp", true, FunTyped::kVirtual, fCodeProducer);
    }
    
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
    *fOut << genVirtual() << "void instanceConstants(int sample_rate, " << subst("int* iZone, $0* fZone) {", ifloat());
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
    inlineSubcontainersFunCalls(fInitInstructions)->accept(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "void instanceConstantsFromMem(int sample_rate, " << subst("int* iZone, $0* fZone) {", ifloat());
    tab(n + 2, *fOut);
    // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
    BlockInst* block1 = inlineSubcontainersFunCalls(fInitInstructions);
    ConstantsCopyFromMemory copy_from_mem(int_zone_size, real_zone_size);
    CPPInstVisitor visitor1(fOut, n + 2);
    copy_from_mem.getCode(block1)->accept(&visitor1);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "void instanceConstantsToMem(int sample_rate, " << subst("int* iZone, $0* fZone) {", ifloat());
    tab(n + 2, *fOut);
    // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
    BlockInst* block2 = inlineSubcontainersFunCalls(fInitInstructions);
    ConstantsCopyToMemory copy_to_mem(int_zone_size, real_zone_size);
    CPPInstVisitor visitor2(fOut, n + 2);
    copy_to_mem.getCode(block2)->accept(&visitor2);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "void instanceResetUserInterface() {";
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    generateResetUserInterface(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "void instanceClear(" << subst("int* iZone, $0* fZone) {", ifloat());
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    generateClear(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    // Init
    if (gGlobal->gMemoryManager) {
        tab(n + 1, *fOut);
        *fOut << genVirtual() << "void init(int sample_rate, " << subst("int* iZone, $0* fZone) {", ifloat());
    } else {
        tab(n + 1, *fOut);
        *fOut << genVirtual() << "void init(int sample_rate, " << subst("int* iZone, $0* fZone) {", ifloat());
        tab(n + 2, *fOut);
        *fOut << "instanceInit(sample_rate, iZone, fZone);";
        tab(n + 1, *fOut);
        *fOut << "}";
    }
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "void instanceInit(int sample_rate, " << subst("int* iZone, $0* fZone) {", ifloat());
    // staticInit has to be called for each instance since the tables are actually not shared between instances
    tab(n + 2, *fOut);
    *fOut << "staticInit(sample_rate, iZone, fZone);";
    tab(n + 2, *fOut);
    *fOut << "instanceConstants(sample_rate, iZone, fZone);";
    tab(n + 2, *fOut);
    *fOut << "instanceConstantsToMem(sample_rate, iZone, fZone);";
    tab(n + 2, *fOut);
    *fOut << "instanceResetUserInterface();";
    tab(n + 2, *fOut);
    *fOut << "instanceClear(iZone, fZone);";
    tab(n + 1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << fKlassName << "* clone() {";
    tab(n + 2, *fOut);
    *fOut << "return new " << fKlassName << "();";
    tab(n + 1, *fOut);
    *fOut << "}";
    
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);
    tab(n + 1, *fOut);
    generateGetSampleRate("getSampleRate", "dsp", true, !gGlobal->gNoVirtual)->accept(fCodeProducer);
    
    // User interface
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "void buildUserInterface(UI* ui_interface) {";
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    generateUserInterface(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << subst("void control(int* RESTRICT iControl, $0* RESTRICT fControl, int* RESTRICT iZone, $0* RESTRICT fZone) {", ifloat());
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    // Generates local variables declaration and setup
    generateComputeBlock(fCodeProducer);
    back(1, *fOut);
    *fOut << "}" << endl;
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "int getNumIntControls() { return " << fIntControl->fCurIndex << "; }";
    tab(n + 1, *fOut);
    
    *fOut << genVirtual() << "int getNumRealControls() { return " << fRealControl->fCurIndex << "; }";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "int getiZoneSize() { return " << copy_from_mem.fIntIndex  << "; }";
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "int getfZoneSize() { return " << copy_from_mem.fRealIndex << "; }";
    
    // Compute
    generateCompute(n);
    tab(n, *fOut);
    tab(n, *fOut);
    *fOut << "};" << endl;
    
    tab(n, *fOut);
    *fOut << "#define FAUST_INT_CONTROLS " << fIntControl->fCurIndex << endl;
    *fOut << "#define FAUST_REAL_CONTROLS " << fRealControl->fCurIndex << endl;
    
    tab(n, *fOut);
    // copy_from_mem.fIntIndex and copy_from_mem.fRealIndex contains the size used for tables, DLs and iConst/fConst variables
    *fOut << "#define FAUST_INT_ZONE " << copy_from_mem.fIntIndex << endl;
    *fOut << "#define FAUST_FLOAT_ZONE " << copy_from_mem.fRealIndex;
    tab(n, *fOut);
    
    // To improve (generalization for all backends...)
    if (gGlobal->gMemoryManager) {
        tab(n, *fOut);
        *fOut << "dsp_memory_manager* " << fKlassName << "::fManager = nullptr;" << endl;
    }
    
    // Generate user interface macros if needed
    printMacros(*fOut, n);
    
    if (gGlobal->gNamespace != "" && gGlobal->gArchFile == "") {
        tab(n, *fOut);
        *fOut << "} // namespace " << gGlobal->gNamespace << endl;
    }
}

// Used with -os3 option
void CPPScalarOneSampleCodeContainer4::produceClass()
{
    // Allocate fCodeProducer here
    VariableSizeCounter heap_counter(Address::kStruct);
    generateDeclarations(&heap_counter);
    fCodeProducer = new CPPInstVisitor3(fOut, std::max(0, heap_counter.fSizeBytes - gGlobal->gFPGAMemory));
    
    int n = 0;
    
    // Libraries
    printLibrary(*fOut);
    printIncludeFile(*fOut);
    
    if (gGlobal->gNamespace != "" && gGlobal->gArchFile == "") {
        tab(n, *fOut);
        *fOut << "namespace " << gGlobal->gNamespace << " {" << endl;
    }
    
    // Sub containers are merged in the main class
    mergeSubContainers();
    
    // Global declarations
    tab(n, *fOut);
    fCodeProducer->Tab(n);
    generateGlobalDeclarations(fCodeProducer);
    
    generateHeader(n);
    
    tab(n, *fOut);
    fSuperKlassName = "one_sample_dsp_real1<" + string(ifloat()) + ">";
    *fOut << "class " << fKlassName << genFinal() << " : public " << fSuperKlassName << " {";
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
    
    // Additional fields
    pushDeclare(InstBuilder::genDecStructVar("iControl", InstBuilder::genArrayTyped(InstBuilder::genInt32Typed(), 0)));
    pushDeclare(InstBuilder::genDecStructVar("fControl", InstBuilder::genArrayTyped(InstBuilder::genItFloatTyped(), 0)));
    pushDeclare(InstBuilder::genDecStructVar("iZone", InstBuilder::genArrayTyped(InstBuilder::genInt32Typed(), 0)));
    pushDeclare(InstBuilder::genDecStructVar("fZone", InstBuilder::genArrayTyped(InstBuilder::genItFloatTyped(), 0)));
    generateDeclarations(fCodeProducer);
    
    // Kept here because staticInit incorrectly change the size later on
    int int_zone_size = static_cast<CPPInstVisitor1*>(fCodeProducer)->getIntZoneSize();
    int real_zone_size = static_cast<CPPInstVisitor1*>(fCodeProducer)->getRealZoneSize();
    
    generateAllocateFun(n);
    generateDestroyFun(n);
    
    tab(n, *fOut);
    *fOut << " public:";
    
    if (gGlobal->gMemoryManager) {
        tab(n + 1, *fOut);
        *fOut << "static dsp_memory_manager* fManager;";
    }
    
    // Print metadata declaration
    produceMetadata(n + 1);
    
    // No class name for main class
    tab(n + 1, *fOut);
    if (gGlobal->gNoVirtual) {
        produceInfoFunctions(n + 1, "", "dsp", true, FunTyped::kStaticConstExpr, fCodeProducer, "getStaticNumInputs", "getStaticNumOutputs");
        produceInfoFunctions(n + 1, "", "dsp", true, FunTyped::kDefault, fCodeProducer);
    } else {
        produceInfoFunctions(n + 1, "", "dsp", true, FunTyped::kVirtual, fCodeProducer);
    }
    
    // Dummy
    tab(n + 1, *fOut);
    *fOut << "static void classInit(int sample_rate) {}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << "void staticInit(int sample_rate) {";
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
    *fOut << genVirtual() << "void instanceConstants(int sample_rate) {";
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
    inlineSubcontainersFunCalls(fInitInstructions)->accept(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "void instanceConstantsFromMem(int sample_rate) {";
    tab(n + 2, *fOut);
    // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
    BlockInst* block1 = inlineSubcontainersFunCalls(fInitInstructions);
    ConstantsCopyFromMemory1 copy_from_mem(int_zone_size, real_zone_size);
    CPPInstVisitor visitor1(fOut, n + 2);
    copy_from_mem.getCode(block1)->accept(&visitor1);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "void instanceConstantsToMem(int sample_rate) {";
    tab(n + 2, *fOut);
    // Rename 'sig' in 'dsp', remove 'dsp' allocation, inline subcontainers 'instanceInit' and 'fill' function call
    BlockInst* block2 = inlineSubcontainersFunCalls(fInitInstructions);
    ConstantsCopyToMemory1 copy_to_mem(int_zone_size, real_zone_size);
    CPPInstVisitor visitor2(fOut, n + 2);
    copy_to_mem.getCode(block2)->accept(&visitor2);
    // Keep the updated values
    int_zone_size = copy_from_mem.fIntIndex;
    real_zone_size = copy_from_mem.fRealIndex;
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
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
    
    /*
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
    */
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "void init(int sample_rate) {";
    tab(n + 2, *fOut);
    *fOut << "instanceInit(sample_rate);";
    tab(n + 1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "void instanceInit(int sample_rate) {";
    // staticInit has to be called for each instance since the tables are actually not shared between instances
    tab(n + 2, *fOut);
    *fOut << "staticInit(sample_rate);";
    tab(n + 2, *fOut);
    *fOut << "instanceConstants(sample_rate);";
    tab(n + 2, *fOut);
    *fOut << "instanceConstantsToMem(sample_rate);";
    tab(n + 2, *fOut);
    *fOut << "instanceResetUserInterface();";
    tab(n + 2, *fOut);
    *fOut << "instanceClear();";
    tab(n + 1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << fKlassName << "* clone() {";
    tab(n + 2, *fOut);
    if (gGlobal->gMemoryManager) {
        *fOut << "return new " << fKlassName << "();";
    } else {
        // Use the same memory for now
        *fOut << "return new " << fKlassName << "(iControl, fControl, iZone, fZone);";
    }
    tab(n + 1, *fOut);
    *fOut << "}";
    
    tab(n + 1, *fOut);
    fCodeProducer->Tab(n + 1);
    tab(n + 1, *fOut);
    generateGetSampleRate("getSampleRate", "dsp", true, !gGlobal->gNoVirtual)->accept(fCodeProducer);
    
    // User interface
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "void buildUserInterface(UI* ui_interface) {";
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    generateUserInterface(fCodeProducer);
    back(1, *fOut);
    *fOut << "}";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << subst("void control() {", xfloat(), ifloat());
    tab(n + 2, *fOut);
    fCodeProducer->Tab(n + 2);
    // Generates local variables declaration and setup
    generateComputeBlock(fCodeProducer);
    back(1, *fOut);
    *fOut << "}" << endl;
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "int getNumIntControls() { return " << fIntControl->fCurIndex << "; }";
    tab(n + 1, *fOut);
    
    *fOut << genVirtual() << "int getNumRealControls() { return " << fRealControl->fCurIndex << "; }";
    tab(n + 1, *fOut);
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "int getiZoneSize() { return " << int_zone_size  << "; }";
    
    tab(n + 1, *fOut);
    *fOut << genVirtual() << "int getfZoneSize() { return " << real_zone_size << "; }";
    
    // Compute
    generateCompute(n);
    tab(n, *fOut);
    
    tab(n + 1, *fOut);
    if (gGlobal->gMemoryManager) {
        // Constructor
        *fOut << fKlassName << "() {";
        tab(n + 2, *fOut);
        *fOut << "iControl = static_cast<int*>(fManager->allocate(" << fIntControl->fCurIndex * sizeof(int) << "));";
        tab(n + 2, *fOut);
        *fOut << "fControl = static_cast<" << ifloat() << "*>(fManager->allocate(" << fRealControl->fCurIndex * gGlobal->audioSampleSize() << "));";
        tab(n + 2, *fOut);
        *fOut << "iZone = static_cast<int*>(fManager->allocate(" << int_zone_size * sizeof(int) << "));";
        tab(n + 2, *fOut);
        *fOut << "fZone = static_cast<" << ifloat() << "*>(fManager->allocate(" << real_zone_size * gGlobal->audioSampleSize() << "));";
        tab(n + 1, *fOut);
        *fOut << "}";
        tab(n + 1, *fOut);
        // Destructor
        tab(n + 1, *fOut);
        *fOut << "virtual ~" << fKlassName << "() {";
        tab(n + 2, *fOut);
        *fOut << "fManager->destroy(iControl);";
        tab(n + 2, *fOut);
        *fOut << "fManager->destroy(fControl);";
        tab(n + 2, *fOut);
        *fOut << "fManager->destroy(iZone);";
        tab(n + 2, *fOut);
        *fOut << "fManager->destroy(fZone);";
        tab(n + 1, *fOut);
        *fOut << "}";
    } else {
        // setMemory
        *fOut << "void setMemory(int* icontrol, " << ifloat() << "* fcontrol, int* izone, " << ifloat() << "* fzone) {";
        tab(n + 2, *fOut);
        *fOut << "iControl = icontrol;";
        tab(n + 2, *fOut);
        *fOut << "fControl = fcontrol;";
        tab(n + 2, *fOut);
        *fOut << "iZone = izone;";
        tab(n + 2, *fOut);
        *fOut << "fZone = fzone;";
        tab(n + 1, *fOut);
        *fOut << "}";
        // Default constructor
        tab(n + 1, *fOut);
        stringstream fun_proto1;
        fun_proto1 << fKlassName << "():iControl(nullptr), fControl(nullptr), iZone(nullptr), fZone(nullptr)";
        generateConstructor(fun_proto1.str(), n);
        // Constructor
        stringstream fun_proto2;
        fun_proto2 << fKlassName << "(int* icontrol, " << ifloat() << "* fcontrol, int* izone, " << ifloat() << "* fzone)";
        fun_proto2 << ":iControl(icontrol), fControl(fcontrol), iZone(izone), fZone(fzone)";
        generateConstructor(fun_proto2.str(), n);
    }
    
    tab(n, *fOut);
    *fOut << "};" << endl;
    
    tab(n, *fOut);
    *fOut << "#define FAUST_INT_CONTROLS " << fIntControl->fCurIndex << endl;
    *fOut << "#define FAUST_REAL_CONTROLS " << fRealControl->fCurIndex << endl;
    
    tab(n, *fOut);
    // int_zone_size and real_zone_size contains the size used for tables, DLs and iConst/fConst variables
    *fOut << "#define FAUST_INT_ZONE " << int_zone_size << endl;
    *fOut << "#define FAUST_FLOAT_ZONE " << real_zone_size;
    tab(n, *fOut);
     
    // To improve (generalization for all backends...)
    if (gGlobal->gMemoryManager) {
        tab(n, *fOut);
        *fOut << "dsp_memory_manager* " << fKlassName << "::fManager = nullptr;" << endl;
    }
    
    // Generate user interface macros if needed
    printMacros(*fOut, n);
    
    if (gGlobal->gNamespace != "" && gGlobal->gArchFile == "") {
        tab(n, *fOut);
        *fOut << "} // namespace " << gGlobal->gNamespace << endl;
    }
}

void CPPScalarCodeContainer::generateCompute(int n)
{
    // Generates declaration
    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    if (gGlobal->gInPlace) {
        *fOut << genVirtual() << subst("void compute(int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
    } else {
        *fOut << genVirtual() << subst("void compute(int $0, $1** RESTRICT inputs, $1** RESTRICT outputs) {", fFullCount, xfloat());
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

// Used with -os0 option
void CPPScalarOneSampleCodeContainer1::generateCompute(int n)
{
    // Generates declaration
    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    if (gGlobal->gInPlace) {
        *fOut << genVirtual() << subst("void compute($0* inputs, $0* outputs, int* RESTRICT iControl, $1* RESTRICT fControl) {", xfloat(), ifloat());
    } else {
        *fOut << genVirtual() << subst("void compute($0* RESTRICT inputs, $0* RESTRICT outputs, int* RESTRICT iControl, $1* RESTRICT fControl) {", xfloat(), ifloat());
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

// Used with -os1 and -os2 option
void CPPScalarOneSampleCodeContainer2::generateCompute(int n)
{
    // Generates declaration
    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    if (gGlobal->gInPlace) {
        *fOut << genVirtual() << subst("void compute($0* inputs, $0* outputs, int* RESTRICT iControl, $1* RESTRICT fControl, int* RESTRICT iZone, $1* RESTRICT fZone) {", xfloat(), ifloat());
    } else {
        *fOut << genVirtual() << subst("void compute($0* RESTRICT inputs, $0* RESTRICT outputs, int* RESTRICT iControl, $1* RESTRICT fControl, int* RESTRICT iZone, $1* RESTRICT fZone) {", xfloat(), ifloat());
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

// Used with -os3 option
void CPPScalarOneSampleCodeContainer4::generateCompute(int n)
{
    // Generates declaration
    tab(n + 1, *fOut);
    tab(n + 1, *fOut);
    if (gGlobal->gInPlace) {
        *fOut << genVirtual() << subst("void compute($0* inputs, $0* outputs) {", xfloat());
    } else {
        *fOut << genVirtual() << subst("void compute($0* RESTRICT inputs, $0* RESTRICT outputs) {", xfloat());
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
    if (gGlobal->gInPlace) {
        *fOut << genVirtual() << subst("void compute(int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
    } else {
        *fOut << genVirtual() << subst("void compute(int $0, $1** RESTRICT inputs, $1** RESTRICT outputs) {", fFullCount, xfloat());
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
    if (gGlobal->gInPlace) {
        *fOut << genVirtual() << subst("void compute(int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
    } else {
        *fOut << genVirtual() << subst("void compute(int $0, $1** RESTRICT inputs, $1** RESTRICT outputs) {", fFullCount, xfloat());
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
    if (gGlobal->gInPlace) {
        *fOut << genVirtual() << subst("void compute(int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
    } else {
        *fOut << genVirtual() << subst("void compute(int $0, $1** RESTRICT inputs, $1** RESTRICT outputs) {", fFullCount, xfloat());
    }
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
