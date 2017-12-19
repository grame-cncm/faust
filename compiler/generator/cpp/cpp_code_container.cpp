/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
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
#include "cpp_gpu_code_container.hh"
#include "Text.hh"
#include "floats.hh"
#include "exception.hh"
#include "global.hh"
#include "fir_to_fir.hh"

using namespace std;

map <string, bool> CPPInstVisitor::gFunctionSymbolTable;

dsp_factory_base* CPPCodeContainer::produceFactory()
{
    return new text_dsp_factory_aux(fKlassName, "", "",
                                    gGlobal->gReader.listSrcFiles(),
                                    ((dynamic_cast<std::stringstream*>(fOut)) ? dynamic_cast<std::stringstream*>(fOut)->str() : ""), "");
}

CodeContainer* CPPCodeContainer::createScalarContainer(const string& name, int sub_container_type)
{
    return new CPPScalarCodeContainer(name, "", 0, 1, fOut, sub_container_type);
}

CodeContainer* CPPCodeContainer::createContainer(const string& name, const string& super, int numInputs, int numOutputs, ostream* dst)
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
        container = new CPPScalarCodeContainer(name, super, numInputs, numOutputs, dst, kInt);
    }

    return container;
}

void CPPCodeContainer::produceMetadata(int tabs)
{
    tab(tabs, *fOut); *fOut << "void metadata(Meta* m) { ";
    
    // We do not want to accumulate metadata from all hierachical levels, so the upper level only is kept
    for (MetaDataSet::iterator i = gGlobal->gMetaDataSet.begin(); i != gGlobal->gMetaDataSet.end(); i++) {
        if (i->first != tree("author")) {
            tab(tabs+1, *fOut); *fOut << "m->declare(\"" << *(i->first) << "\", " << **(i->second.begin()) << ");";
        } else {
            // But the "author" meta data is accumulated, the upper level becomes the main author and sub-levels become "contributor"
            for (set<Tree>::iterator j = i->second.begin(); j != i->second.end(); j++) {
                if (j == i->second.begin()) {
                    tab(tabs+1, *fOut); *fOut << "m->declare(\"" << *(i->first) << "\", " << **j << ");";
                } else {
                    tab(tabs+1, *fOut); *fOut << "m->declare(\"" << "contributor" << "\", " << **j << ");";
                }
            }
        }
    }

    tab(tabs, *fOut); *fOut << "}" << endl;
}

void CPPCodeContainer::produceInit(int tabs)
{
    if (gGlobal->gMemoryManager) {
         tab(tabs, *fOut); *fOut << "virtual void init(int samplingFreq) {}";
    } else {
        tab(tabs, *fOut); *fOut << "virtual void init(int samplingFreq) {";
            tab(tabs+1, *fOut); *fOut << "classInit(samplingFreq);";
            tab(tabs+1, *fOut); *fOut << "instanceInit(samplingFreq);";
        tab(tabs, *fOut); *fOut << "}";
    }
    
    tab(tabs, *fOut); *fOut << "virtual void instanceInit(int samplingFreq) {";
        tab(tabs+1, *fOut); *fOut << "instanceConstants(samplingFreq);";
        tab(tabs+1, *fOut); *fOut << "instanceResetUserInterface();";
        tab(tabs+1, *fOut); *fOut << "instanceClear();";
    tab(tabs, *fOut); *fOut << "}";
}

void CPPCodeContainer::produceInternal()
{
    int n = 0;

    // Global declarations
    tab(n, *fOut);

    fCodeProducer.Tab(n);
    generateGlobalDeclarations(&fCodeProducer);

    tab(n, *fOut); *fOut << "class " << fKlassName << " {";

        tab(n+1, *fOut);

        if (gGlobal->gUIMacroSwitch) {
            tab(n, *fOut); *fOut << "  public:";
        } else {
            tab(n, *fOut); *fOut << "  private:";
        }
        tab(n+1, *fOut);
        tab(n+1, *fOut);

        // Fields
        fCodeProducer.Tab(n+1);
        generateDeclarations(&fCodeProducer);

    tab(n, *fOut); *fOut << "  public:";

        tab(n+1, *fOut);
        tab(n+1, *fOut);
    
        // fKlassName used in method naming for subclasses
        produceInfoFunctions(n+1, fKlassName, "dsp", true, false, &fCodeProducer);
    
        // TODO
        //generateInstanceInitFun("instanceInit" + fKlassName, true, false)->accept(&fCodeProducer);

        // Inits
        tab(n+1, *fOut); *fOut << "void instanceInit" << fKlassName << "(int samplingFreq) {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateInit(&fCodeProducer);
            generateResetUserInterface(&fCodeProducer);
            generateClear(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";
    
    
        // Fill
        string counter = "count";
        tab(n+1, *fOut);
        if (fSubContainerType == kInt) {
            tab(n+1, *fOut); *fOut << "void fill" << fKlassName << subst("(int $0, int* output) {", counter);
        } else {
            tab(n+1, *fOut); *fOut << "void fill" << fKlassName << subst("(int $0, $1* output) {", counter, ifloat());
        }
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateComputeBlock(&fCodeProducer);
            ForLoopInst* loop = fCurLoop->generateScalarLoop(counter);
            loop->accept(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";
    
        /*
        tab(n+1, *fOut);
        fCodeProducer.Tab(n+1);
        generateFillFun("fill" + fKlassName, true, false)->accept(&fCodeProducer);
        */

    tab(n, *fOut); *fOut << "};" << endl;
  
    // Memory methods (as globals)
    if (gGlobal->gMemoryManager) {
        tab(n, *fOut); *fOut << fKlassName << "* " << "new" <<  fKlassName << "(dsp_memory_manager* manager) {"
                            << " return (" << fKlassName << "*)new(manager->allocate(sizeof("<< fKlassName << "))) " << fKlassName << "()"
                            << "; }";
        tab(n, *fOut); *fOut << "void delete" << fKlassName << "(" << fKlassName << "* dsp, dsp_memory_manager* manager) { dsp->~" << fKlassName << "(); manager->destroy(dsp); }" ;
    } else {
        tab(n, *fOut); *fOut << fKlassName << "* " << "new" <<  fKlassName << "() {"
                            << " return (" << fKlassName << "*)new "<< fKlassName << "()"
                            << "; }";
        tab(n, *fOut); *fOut << "void delete" << fKlassName << "(" << fKlassName << "* dsp) { delete dsp; }";
    }
    tab(n, *fOut);
}

void CPPCodeContainer::produceClass()
{
    int n = 0;

    // Libraries
    printLibrary(*fOut);
    printIncludeFile(*fOut);

    // Sub containers
    generateSubContainers();

    // Global declarations
    tab(n, *fOut);
    fCodeProducer.Tab(n);
    generateGlobalDeclarations(&fCodeProducer);
   
    tab(n, *fOut); 
    *fOut << "#ifndef FAUSTCLASS " << endl;
    *fOut << "#define FAUSTCLASS "<< fKlassName << endl;
    *fOut << "#endif" << endl;
    
    *fOut << "#ifdef __APPLE__ " << endl;
    *fOut << "#define exp10f __exp10f" << endl;
    *fOut << "#define exp10 __exp10" << endl;
    *fOut << "#endif" << endl;
    
    tab(n, *fOut); *fOut << "class " << fKlassName << " : public " << fSuperKlassName << " {";

        tab(n+1, *fOut);

        if (gGlobal->gUIMacroSwitch) {
            tab(n, *fOut); *fOut << " public:";
        } else {
            tab(n, *fOut); *fOut << " private:";
        }
        tab(n+1, *fOut);

        // Fields
        fCodeProducer.Tab(n+1);
        tab(n+1, *fOut);
        generateDeclarations(&fCodeProducer);
    
        if (fAllocateInstructions->fCode.size() > 0) {
            tab(n+1, *fOut); *fOut << "void allocate() {";
                tab(n+2, *fOut);
                fCodeProducer.Tab(n+2);
                generateAllocate(&fCodeProducer);
            tab(n+1, *fOut);  *fOut << "}";
            tab(n+1, *fOut);
        }

        if (fDestroyInstructions->fCode.size() > 0) {
            tab(n+1, *fOut); *fOut << "void destroy() {";
                tab(n+2, *fOut);
                fCodeProducer.Tab(n+2);
                generateDestroy(&fCodeProducer);
            tab(n+1, *fOut);  *fOut << "}";
            tab(n+1, *fOut);
        }

    tab(n, *fOut); *fOut << " public:";

        if (gGlobal->gMemoryManager) {
            tab(n+1, *fOut); *fOut << "static dsp_memory_manager* fManager;" << endl;
        }
    
        // Print metadata declaration
        tab(n+1, *fOut);
        produceMetadata(n+1);
    
        if (fAllocateInstructions->fCode.size() > 0) {
            tab(n+1, *fOut); *fOut << fKlassName << "() {";
                tab(n+2, *fOut); *fOut << "allocate();";
            tab(n+1, *fOut); *fOut << "}" << endl;
        }

        if (fDestroyInstructions->fCode.size() > 0) {
            tab(n+1, *fOut); *fOut << "virtual ~" << fKlassName << "() {";
                tab(n+2, *fOut); *fOut << "destroy();";
            tab(n+1, *fOut); *fOut << "}" << endl;
        }
        
        tab(n+1, *fOut);
        // No class name for main class
        produceInfoFunctions(n+1, "", "dsp", true, true, &fCodeProducer);  // Inits
    
        // TODO
        /*
        generateStaticInitFun("classInit", true)->accept(&fCodeProducer);
        generateInstanceInitFun("instanceInit", true, true)->accept(&fCodeProducer);
        */
    
        tab(n+1, *fOut); *fOut << "static void classInit(int samplingFreq) {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateStaticInit(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";
    
        if (gGlobal->gMemoryManager) {
            tab(n+1, *fOut); *fOut << "static void classDestroy() {";
                tab(n+2, *fOut);
                fCodeProducer.Tab(n+2);
                generateStaticDestroy(&fCodeProducer);
            tab(n+1, *fOut); *fOut << "}";
        }
 
        // TEST
        /*
        // Start inline
        {
            DspRenamer renamer;
            BlockInst* res1 = renamer.getCode(fStaticInitInstructions);
         
            list<CodeContainer*>::const_iterator it;
            for (it = fSubContainers.begin(); it != fSubContainers.end(); it++) {
                DeclareFunInst* inst_init_fun = (*it)->generateInstanceInitFun("instanceInit" + (*it)->getClassName(), true, false);
                InlineVoidFunctionCall inliner1(inst_init_fun);
                res1 = inliner1.getCode(res1);
                DeclareFunInst* fill_fun = (*it)->generateFillFun("fill" + (*it)->getClassName(), true, false);
                InlineVoidFunctionCall inliner2(fill_fun);
                res1 = inliner2.getCode(res1);
            }
        
            tab(n+1, *fOut); *fOut << "static void classInit(int samplingFreq) {";
                tab(n+2, *fOut);
                fCodeProducer.Tab(n+2);
                res1->accept(&fCodeProducer);
            tab(n+1, *fOut); *fOut << "}";
        }
        // End inline
        */
    
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "virtual void instanceConstants(int samplingFreq) {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateInit(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";
        tab(n+1, *fOut);
    
        tab(n+1, *fOut); *fOut << "virtual void instanceResetUserInterface() {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateResetUserInterface(&fCodeProducer);
            tab(n+1, *fOut); *fOut << "}";
        tab(n+1, *fOut);

        tab(n+1, *fOut); *fOut << "virtual void instanceClear() {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateClear(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";
        tab(n+1, *fOut);
    
        // TEST
        /*
        // Start inline
        {
            DspRenamer renamer;
            BlockInst* res1 = renamer.getCode(fInitInstructions);
            BlockInst* res2 = renamer.getCode(fPostInitInstructions);
            
            list<CodeContainer*>::const_iterator it;
            for (it = fSubContainers.begin(); it != fSubContainers.end(); it++) {
                DeclareFunInst* inst_init_fun = (*it)->generateInstanceInitFun("instanceInit" + (*it)->getClassName(), true, false);
                InlineVoidFunctionCall inliner1(inst_init_fun);
                res1 = inliner1.getCode(res1);
                res2 = inliner1.getCode(res2);
                DeclareFunInst* fill_fun = (*it)->generateFillFun("fill" + (*it)->getClassName(), true, false);
                InlineVoidFunctionCall inliner2(fill_fun);
                res1 = inliner2.getCode(res1);
                res2 = inliner2.getCode(res2);
            }
            
            tab(n+1, *fOut); *fOut << "virtual void instanceInit(int samplingFreq) {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            res1->accept(&fCodeProducer);
            res2->accept(&fCodeProducer);
            tab(n+1, *fOut); *fOut << "}";
        }
        // End inline
        */
    
        // Init
        produceInit(n+1);
    
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "virtual "<< fKlassName <<"* clone() {";
            tab(n+2, *fOut); *fOut << "return new " << fKlassName << "();";
        tab(n+1, *fOut); *fOut << "}";
    
        tab(n+1, *fOut);
        fCodeProducer.Tab(n+1);
        generateGetSampleRate("dsp", true, true)->accept(&fCodeProducer);
    
        // User interface
        tab(n+1, *fOut); *fOut << "virtual void buildUserInterface(UI* ui_interface) {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateUserInterface(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";

        // Compute
        generateCompute(n);
        tab(n, *fOut);

        // Possibly generate separated functions
        fCodeProducer.Tab(n+1);
        tab(n+1, *fOut);
        generateComputeFunctions(&fCodeProducer);

    tab(n, *fOut); *fOut << "};" << endl;
    
    // To improve (generalization for all backend...)
    if (gGlobal->gMemoryManager) {
        tab(n, *fOut); *fOut << "dsp_memory_manager* " << fKlassName <<"::fManager = 0;" << endl;
    }

    // Generate user interface macros if needed
	if (gGlobal->gUIMacroSwitch) {
		tab(n, *fOut); *fOut << "#ifdef FAUST_UIMACROS";
            tab(n+1, *fOut); *fOut << "#define FAUST_INPUTS " << fNumInputs;
            tab(n+1, *fOut); *fOut << "#define FAUST_OUTPUTS " << fNumOutputs;
            tab(n+1, *fOut); *fOut << "#define FAUST_ACTIVES " << fNumActives;
            tab(n+1, *fOut); *fOut << "#define FAUST_PASSIVES " << fNumPassives;
			printlines(n+1, fUIMacro, *fOut);
		tab(n, *fOut); *fOut << "#endif";
        tab(n, *fOut);
	}
}

// Scalar
CPPScalarCodeContainer::CPPScalarCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out, int sub_container_type)
    :CPPCodeContainer(name, super, numInputs, numOutputs, out)
{
    fSubContainerType = sub_container_type;
}

CPPScalarCodeContainer::~CPPScalarCodeContainer()
{}

void CPPScalarCodeContainer::generateCompute(int n)
{
    // Generates declaration
    tab(n+1, *fOut);
    tab(n+1, *fOut); *fOut << subst("virtual void compute(int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
        tab(n+2, *fOut);
        fCodeProducer.Tab(n+2);

        // Generates local variables declaration and setup
        generateComputeBlock(&fCodeProducer);

        // Generates one single scalar loop
        ForLoopInst* loop = fCurLoop->generateScalarLoop(fFullCount);
        loop->accept(&fCodeProducer);
    
        // Currently for soundfile management
        generatePostComputeBlock(&fCodeProducer);

    tab(n+1, *fOut); *fOut << "}";
}

// Vector
CPPVectorCodeContainer::CPPVectorCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out)
    :VectorCodeContainer(numInputs, numOutputs), CPPCodeContainer(name, super, numInputs, numOutputs, out)
{}

CPPVectorCodeContainer::~CPPVectorCodeContainer()
{}

void CPPVectorCodeContainer::generateCompute(int n)
{
    // Generates declaration
    tab(n+1, *fOut);
    tab(n+1, *fOut); *fOut << subst("virtual void compute(int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
        tab(n+2, *fOut);
        fCodeProducer.Tab(n+2);
     
        // Generates local variables declaration and setup
        generateComputeBlock(&fCodeProducer);
     
        // Generates DSP loop
        fDAGBlock->accept(&fCodeProducer);
    
    tab(n+1, *fOut); *fOut << "}";
}

// OpenMP
CPPOpenMPCodeContainer::CPPOpenMPCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out)
    :OpenMPCodeContainer(numInputs, numOutputs), CPPCodeContainer(name, super, numInputs, numOutputs, out)
{}

CPPOpenMPCodeContainer::~CPPOpenMPCodeContainer()
{}

void CPPOpenMPCodeContainer::generateCompute(int n)
{
    // Generates declaration
    tab(n+1, *fOut);
    tab(n+1, *fOut); *fOut << subst("virtual void compute(int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
        tab(n+2, *fOut);
        fCodeProducer.Tab(n+2);

        // Generates local variables declaration and setup
        generateComputeBlock(&fCodeProducer);

        // Generate DSP loop
        fGlobalLoopBlock->accept(&fCodeProducer);

    tab(n+1, *fOut); *fOut << "}";
}

// Works stealing scheduler
CPPWorkStealingCodeContainer::CPPWorkStealingCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out)
    :WSSCodeContainer(numInputs, numOutputs, "this"), CPPCodeContainer(name, super, numInputs, numOutputs, out)
{}

CPPWorkStealingCodeContainer::~CPPWorkStealingCodeContainer()
{}

void CPPWorkStealingCodeContainer::produceClass()
{
    int n = 0;

    // Inherited method
    CPPCodeContainer::produceClass();

    *fOut << "extern \"C\" void computeThreadExternal(void* dsp, int num_thread) {";
        tab(n+1, *fOut); *fOut << "static_cast<" << fKlassName << "*>(dsp)->computeThread(num_thread);";
    tab(n, *fOut); *fOut << "}" << endl;
}

void CPPWorkStealingCodeContainer::generateCompute(int n)
{
    // Generates "compute" declaration
    tab(n+1, *fOut);
    tab(n+1, *fOut); *fOut << subst("virtual void compute(int $0, $1** inputs, $1** outputs) {", fFullCount, xfloat());
        tab(n+2, *fOut);
        fCodeProducer.Tab(n+2);

        // Generates local variables declaration and setup
        generateComputeBlock(&fCodeProducer);

    tab(n+1, *fOut); *fOut << "}" << endl;

    // Generates "computeThread" code
    tab(n+1, *fOut); *fOut << "void computeThread(int num_thread) {";
        tab(n+2, *fOut);
        fCodeProducer.Tab(n+2);

        // Generate it
        faustassert(fThreadLoopBlock);
        fThreadLoopBlock->accept(&fCodeProducer);

    tab(n+1, *fOut); *fOut << "}";
}

