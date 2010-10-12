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

/**********************************************************************
			- code_gen.h : generic code generator (projet FAUST) -


		Historique :
		-----------

***********************************************************************/
#include "cpp_code_container.hh"
#include "Text.hh"
#include "floats.hh"

using namespace std;

extern bool gUIMacroSwitch;
extern int gVectorLoopVariant;
extern bool gOpenMPLoop;
extern bool gVectorSwitch;

extern map<Tree, set<Tree> > gMetaDataSet;

CodeContainer* CPPCodeContainer::createScalarContainer(const string& name)
{
    return new CPPScalarCodeContainer(name, "", 0, 1, fOut);
}

void CPPCodeContainer::produceInternal()
{
    int n = 0;

    // Global declarations
    /*
    tab(n, *fOut);
    if (fGlobalDeclarationInstructions->fCode.size() > 0) {
        fCodeProducer.Tab(n);
        fGlobalDeclarationInstructions->accept(&fCodeProducer);
    }
    */

    tab(n, *fOut); *fOut << "class " << fKlassName << " {";

        tab(n+1, *fOut);

        if (gUIMacroSwitch) {
            tab(n, *fOut); *fOut << "  public:";
        } else {
            tab(n, *fOut); *fOut << "  private:";
        }
        tab(n+1, *fOut);
        tab(n+1, *fOut);

        // Fields
        if (fDeclarationInstructions->fCode.size() > 0) {
            fCodeProducer.Tab(n+1);

            // Sort arrays to be at the begining
            fDeclarationInstructions->fCode.sort(sortFunction1);

            fDeclarationInstructions->accept(&fCodeProducer);
        }

    tab(n, *fOut); *fOut << "  public:";

        // Input method
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "int getNumInputs" << fKlassName << "() { "
                            << "return " << fNumInputs
                            << "; }";

        // Output method
        tab(n+1, *fOut); *fOut << "int getNumOutputs" << fKlassName << "() { "
                            << "return " << fNumOutputs
                            << "; }";

        // Inits
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "void instanceInit" << fKlassName << "(int samplingFreq) {";
            if (fInitInstructions->fCode.size() > 0) {
                tab(n+2, *fOut);
                fCodeProducer.Tab(n+2);
                fInitInstructions->accept(&fCodeProducer);
            }
        tab(n+1, *fOut); *fOut << "}";

        // Fill
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "void fill" << fKlassName << subst("(int count, $0* output) {", ifloat());
        tab(n+2, *fOut);
        fCodeProducer.Tab(n+2);
        if (fComputeBlockInstructions->fCode.size() > 0) {
            fComputeBlockInstructions->accept(&fCodeProducer);
        }
        ForLoopInst* loop = fCurLoop->getScalarLoop();
        loop->accept(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";

    tab(n, *fOut); *fOut << "};" << endl;

    // Memory methods (as globals)
    tab(n, *fOut); *fOut << fKlassName << "* " << "new" <<  fKlassName << "() { "
                        << "return (" << fKlassName << "*) new "<< fKlassName << "()"
                        << "; }";

    tab(n, *fOut); *fOut << "void " << "delete" << fKlassName << "(" << fKlassName << "* dsp) { "
                        << "delete dsp"
                        << "; }";
    tab(n, *fOut);
}

void CPPCodeContainer::produceClass()
{
    // Initialize "fSamplingFreq" with the "samplingFreq" parameter of the init function
    pushFrontInitMethod(InstBuilder::genStoreVarInst(
                            InstBuilder::genNamedAddress("fSamplingFreq", Address::kGlobal),
                                InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("samplingFreq", Address::kFunArgs))));

    int n = 0;

    // Libraries
    printLibrary(*fOut);
    printIncludeFile(*fOut);

    // Sub containers
    generateSubContainers();

    // Functions
    tab(n, *fOut);
    if (fGlobalDeclarationInstructions->fCode.size() > 0) {
        fCodeProducer.Tab(n);
        fGlobalDeclarationInstructions->accept(&fCodeProducer);
    }

    tab(n, *fOut); *fOut << "class " << fKlassName << " : public " << fSuperKlassName << " {";

        tab(n+1, *fOut);

        if (gUIMacroSwitch) {
            tab(n, *fOut); *fOut << "  public:";
        } else {
            tab(n, *fOut); *fOut << "  private:";
        }
        tab(n+1, *fOut);

        // Fields
        if (fDeclarationInstructions->fCode.size() > 0) {
            fCodeProducer.Tab(n+1);
            tab(n+1, *fOut);

            // Sort arrays to be at the begining
            fDeclarationInstructions->fCode.sort(sortFunction1);

            fDeclarationInstructions->accept(&fCodeProducer);
        }

    tab(n, *fOut); *fOut << "  public:";

        // Print metadata declaration
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut   << "void static metadata(Meta* m) { ";

        for (map<Tree, set<Tree> >::iterator i = gMetaDataSet.begin(); i != gMetaDataSet.end(); i++) {
            if (i->first != tree("author")) {
                tab(n+2, *fOut); *fOut << "m->declare(\"" << *(i->first) << "\", " << **(i->second.begin()) << ");";
            } else {
                for (set<Tree>::iterator j = i->second.begin(); j != i->second.end(); j++) {
                    if (j == i->second.begin()) {
                        tab(n+2, *fOut); *fOut << "m->declare(\"" << *(i->first) << "\", " << **j << ");";
                    } else {
                        tab(n+2, *fOut); *fOut << "m->declare(\"" << "contributor" << "\", " << **j << ");";
                    }
                }
            }
        }

        tab(n+1, *fOut); *fOut << "}" << endl;

        tab(n+1, *fOut); *fOut << "virtual ~" << fKlassName << "() {";
            tab(n+2, *fOut); *fOut << "destroy();";
        tab(n+1, *fOut); *fOut << "}" << endl;

        tab(n+1, *fOut); *fOut << "void destroy() {";
            if (fDestroyInstructions->fCode.size() > 0) {
                tab(n+2, *fOut);
                fCodeProducer.Tab(n+2);
                fDestroyInstructions->accept(&fCodeProducer);
            }
        tab(n+1, *fOut);  *fOut << "}";
        tab(n+1, *fOut);

        // Input method
        tab(n+1, *fOut); *fOut << "virtual int getNumInputs() { "
                            << "return " << fNumInputs
                            << "; }";

        // Output method
        tab(n+1, *fOut); *fOut << "virtual int getNumOutputs() { "
                            << "return " << fNumOutputs
                            << "; }";

        // Inits
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "static void classInit(int samplingFreq) {";
            if (fStaticInitInstructions->fCode.size() > 0) {
                tab(n+2, *fOut);
                fCodeProducer.Tab(n+2);
                fStaticInitInstructions->accept(&fCodeProducer);
            }
        tab(n+1, *fOut); *fOut << "}";

        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "virtual void instanceInit(int samplingFreq) {";
            if (fInitInstructions->fCode.size() > 0) {
                tab(n+2, *fOut);
                fCodeProducer.Tab(n+2);
                fInitInstructions->accept(&fCodeProducer);
            }
        tab(n+1, *fOut); *fOut << "}";

        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "virtual void init(int samplingFreq) {";
            tab(n+2, *fOut); *fOut << "classInit(samplingFreq);";
            tab(n+2, *fOut); *fOut << "instanceInit(samplingFreq);";
        tab(n+1, *fOut); *fOut << "}";

        // User interface
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "virtual void buildUserInterface(UI* interface) {";
            if (fUserInterfaceInstructions->fCode.size() > 0) {
                tab(n+2, *fOut);
                fCodeProducer.Tab(n+2);
                fUserInterfaceInstructions->accept(&fCodeProducer);
            }
        tab(n+1, *fOut); *fOut << "}";

        // Compute
        generateCompute(n);
        tab(n, *fOut);

        // Possibly generate separated functions
        fCodeProducer.Tab(n+1);
        tab(n+1, *fOut);
        if (fComputeFunctions->fCode.size() > 0) {
            fComputeFunctions->accept(&fCodeProducer);
        }

    tab(n, *fOut); *fOut << "};\n" << endl;

    // Generate user interface macros if needed
	if (gUIMacroSwitch) {
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
CPPScalarCodeContainer::CPPScalarCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out)
    :CPPCodeContainer(name, super, numInputs, numOutputs, out)
{}

CPPScalarCodeContainer::~CPPScalarCodeContainer()
{}

void CPPScalarCodeContainer::generateCompute(int n)
{
    // Generates declaration
    tab(n+1, *fOut);
    tab(n+1, *fOut); *fOut << subst("virtual void compute(int count, $0** inputs, $0** outputs) {", xfloat());
    tab(n+2, *fOut);
    fCodeProducer.Tab(n+2);

    // Generates local variables declaration and setup
    fComputeBlockInstructions->accept(&fCodeProducer);

    // Generates one single scalar loop
    ForLoopInst* loop = fCurLoop->getScalarLoop();
    loop->accept(&fCodeProducer);

    tab(n+1, *fOut); *fOut << "}";
}

// Vector
CPPVectorCodeContainer::CPPVectorCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out)
    :CPPCodeContainer(name, super, numInputs, numOutputs, out)
{}

CPPVectorCodeContainer::~CPPVectorCodeContainer()
{}

void CPPVectorCodeContainer::generateCompute(int n)
{
    // Generates declaration
    tab(n+1, *fOut);
    tab(n+1, *fOut); *fOut << subst("virtual void compute(int fullcount, $0** inputs, $0** outputs) {", xfloat());
    tab(n+2, *fOut);
    fCodeProducer.Tab(n+2);

    // Sort arrays to be at the begining
    fComputeBlockInstructions->fCode.sort(sortFunction1);

    // Generates local variables declaration and setup
    fComputeBlockInstructions->accept(&fCodeProducer);

    // Prepare global loop
    StatementInst* block = NULL;
    if (gVectorLoopVariant == 0) {
        block = generateDAGLoopVariant0();
    } else if (gVectorLoopVariant == 1) {
        block = generateDAGLoopVariant1();
    }

    // Generate it
    assert(block);
    block->accept(&fCodeProducer);

    tab(n+1, *fOut); *fOut << "}";
}

// OpenMP
CPPOpenMPCodeContainer::CPPOpenMPCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out)
    :CPPCodeContainer(name, super, numInputs, numOutputs, out)
{}

CPPOpenMPCodeContainer::~CPPOpenMPCodeContainer()
{}

void CPPOpenMPCodeContainer::generateCompute(int n)
{
    // Compute declaration
    tab(n+1, *fOut);
    tab(n+1, *fOut); *fOut << subst("virtual void compute(int fullcount, $0** inputs, $0** outputs) {", xfloat());
    tab(n+2, *fOut);
    fCodeProducer.Tab(n+2);

    // Transform stack array variables in struct variables
    //MoveStackArray2Struct();

    // Sort arrays to be at the begining
    fComputeBlockInstructions->fCode.sort(sortFunction1);

    // Generates local variables declaration and setup
    fComputeBlockInstructions->accept(&fCodeProducer);

    // Prepare global loop
    StatementInst* block = generateDAGLoopOMP();

    // Generate it
    assert(block);
    block->accept(&fCodeProducer);

    tab(n+1, *fOut); *fOut << "}";
}

// Works stealing scheduler
CPPWorkStealingCodeContainer::CPPWorkStealingCodeContainer(const string& name, const string& super, int numInputs, int numOutputs, std::ostream* out)
    :CPPCodeContainer(name, super, numInputs, numOutputs, out)
{}

CPPWorkStealingCodeContainer::~CPPWorkStealingCodeContainer()
{}

void CPPWorkStealingCodeContainer::produceClass()
{
    /*
    // Transform stack array variables in struct variables
    MoveStackArray2Struct();

    // Transform stack slow variables in struct variables
    MoveStackSlow2Struct();
    */

    // Transform some stack variables in struct variables
    MoveStack2Struct();

    // Specific init code
    CodeContainer::generateDAGLoopWSSAux3();

    // Inherited method
    CPPCodeContainer::produceClass();

    int n = 0;
    //tab(n, *fOut);
    *fOut << "void computeThreadExternal(void* dsp, int num_thread) {";
        tab(n+1, *fOut); *fOut << "static_cast<" << fKlassName << "*>(dsp)->computeThread(num_thread);";
    tab(n, *fOut); *fOut << "}" << endl;
}

void CPPWorkStealingCodeContainer::generateCompute(int n)
{
    lclgraph dag;
    CodeLoop::sortGraph(fCurLoop, dag);
    computeForwardDAG(dag);

    // Compute "compute" declaration
    tab(n+1, *fOut);
    tab(n+1, *fOut); *fOut << subst("virtual void compute(int fullcount, $0** inputs, $0** outputs) {", xfloat());
    tab(n+2, *fOut);
    fCodeProducer.Tab(n+2);

    generateDAGLoopWSSAux2(fComputeBlockInstructions, false);

    // Sort arrays to be at the begining
    fComputeBlockInstructions->fCode.sort(sortFunction1);

    // Generates local variables declaration and setup
    fComputeBlockInstructions->accept(&fCodeProducer);

    tab(n+1, *fOut); *fOut << "}" << endl;

    // Generates "computeThread" code
    tab(n+1, *fOut); *fOut << "void computeThread(int num_thread) {";
    tab(n+2, *fOut);
    fCodeProducer.Tab(n+2);

    // Prepare global loop
    StatementInst* block = generateDAGLoopWSS(dag);

    // Generate it
    assert(block);
    block->accept(&fCodeProducer);

    tab(n+1, *fOut); *fOut << "}";
}

static void tab1(int n, ostream& fout)
{
    fout << "  \\n\"  \\\n";
    fout << "\"";
    while (n--) fout << '\t';
}

void CPPOpenCLCodeContainer::produceInternal()
{
    int n = 0;
    
    // Global declarations
    /*
    tab(n, *fOut); 
    if (fGlobalDeclarationInstructions->fCode.size() > 0) {
        fCodeProducer.Tab(n);
        fGlobalDeclarationInstructions->accept(&fCodeProducer);
    }
    */
    
    tab(n, *fOut); *fOut << "class " << fKlassName << " {";
    
        tab(n+1, *fOut); 
        
        if (gUIMacroSwitch) {
            tab(n, *fOut); *fOut << "  public:";
        } else {
            tab(n, *fOut); *fOut << "  private:";
        }
        tab(n+1, *fOut); 
        tab(n+1, *fOut); 
        
        // Fields
        if (fDeclarationInstructions->fCode.size() > 0) {
            fCodeProducer.Tab(n+1);
            
            // Sort arrays to be at the begining
            fDeclarationInstructions->fCode.sort(sortFunction1);
            
            fDeclarationInstructions->accept(&fCodeProducer);
        }
            
    tab(n, *fOut); *fOut << "  public:";
     
        // Input method
        tab(n+1, *fOut); 
        tab(n+1, *fOut); *fOut << "int getNumInputs" << fKlassName << "() { "
                            << "return " << fNumInputs
                            << "; }";
        
        // Output method
        tab(n+1, *fOut); *fOut << "int getNumOutputs" << fKlassName << "() { "
                            << "return " << fNumOutputs
                            << "; }";
       
        // Inits
        tab(n+1, *fOut); 
        tab(n+1, *fOut); *fOut << "void instanceInit" << fKlassName << "(int samplingFreq) {";
            if (fInitInstructions->fCode.size() > 0) {
                tab(n+2, *fOut);
                fCodeProducer.Tab(n+2);
                fInitInstructions->accept(&fCodeProducer);
            }
        tab(n+1, *fOut); *fOut << "}";
     
        // Fill
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "void fill" << fKlassName << subst("(int count, $0* output) {", ifloat());
        tab(n+2, *fOut);
        fCodeProducer.Tab(n+2);
        if (fComputeBlockInstructions->fCode.size() > 0) {
            fComputeBlockInstructions->accept(&fCodeProducer);
        }
        ForLoopInst* loop = fCurLoop->getScalarLoop();
        loop->accept(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";
    
    tab(n, *fOut); *fOut << "};" << endl;
    
    // Memory methods (as globals)
    tab(n, *fOut); *fOut << fKlassName << "* " << "new" <<  fKlassName << "() { "
                        << "return (" << fKlassName << "*) new "<< fKlassName << "()"
                        << "; }";
                        
    tab(n, *fOut); *fOut << "void " << "delete" << fKlassName << "(" << fKlassName << "* dsp) { "
                        << "delete dsp"
                        << "; }";
    tab(n, *fOut);
}
        
void CPPOpenCLCodeContainer::produceClass() 
{
    // Initialize "fSamplingFreq" with the "samplingFreq" parameter of the init function
    // Generates fSamplingFreq field and initialize it with the "samplingFreq" parameter of the init function
    pushDeclare(InstBuilder::genDeclareVarInst("fSamplingFreq",
        InstBuilder::genBasicTyped(Typed::kInt), Address::kStruct));
   
    pushFrontInitMethod(InstBuilder::genStoreVarInst(
                            InstBuilder::genNamedAddress("fSamplingFreq", Address::kStruct), 
                                InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("samplingFreq", Address::kFunArgs))));
    
    int n = 0;
    addIncludeFile("<iostream>");
    addIncludeFile("<fstream>");
    addIncludeFile("<OpenCL/opencl.h>");
     
    // Libraries
    printLibrary(*fOut);
    printIncludeFile(*fOut);
   
    // Sub containers
    generateSubContainers();
        
    // Functions
    tab(n, *fOut); 
    if (fGlobalDeclarationInstructions->fCode.size() > 0) {
        fCodeProducer.Tab(n);
        fGlobalDeclarationInstructions->accept(&fCodeProducer);
    }
    
    // Sort arrays to be at the begining
    fDeclarationInstructions->fCode.sort(sortFunction1);
       
    // Compile OpenCL kernel string
    *fGPUOut << "const char* KernelSource = \"";
    
    // Macro definition
    tab1(n, *fGPUOut); *fGPUOut << "#define max(x,y) (((x)>(y)) ? (x) : (y))";
    tab1(n, *fGPUOut); *fGPUOut << "#define min(x,y) (((x)<(y)) ? (x) : (y))";
    tab1(n, *fGPUOut); *fGPUOut << "#ifndef " << FLOATMACRO;
    tab1(n, *fGPUOut); *fGPUOut << "#define " << FLOATMACRO << " " << "float";
    tab1(n, *fGPUOut); *fGPUOut << "#endif  ";
     
    // Separate control and non-controls fields in 2 separeted structures
    tab1(n, *fGPUOut); *fGPUOut << "typedef struct {";
        DSPGPUInstVisitor dsp_visitor(fGPUOut, n+1);
        fDeclarationInstructions->accept(&dsp_visitor);
    tab1(n, *fGPUOut); *fGPUOut << "} faustdsp;";
    tab1(n, *fGPUOut);
    
    tab1(n, *fGPUOut); *fGPUOut << "typedef struct {";
        ControlGPUInstVisitor control_visitor(fGPUOut, n+1);
        fDeclarationInstructions->accept(&control_visitor);
    tab1(n, *fGPUOut); *fGPUOut << "} faustcontrol;";
    tab1(n, *fGPUOut);
    tab1(n, *fGPUOut);
    
    // Generate instanceInit kernel
    if (fInitInstructions->fCode.size() > 0) {
        *fGPUOut << "__kernel void instanceInitKernel(__global faustdsp* dsp, __global faustcontrol* control, __global int samplingFreq) {";
        tab1(n+1, *fGPUOut);
        fKernelCodeProducer->Tab(n+1);
        fInitInstructions->accept(fKernelCodeProducer);
        tab1(n, *fGPUOut);
        *fGPUOut << "}";
    }
    
    // Generate compute kernel
    generateComputeKernel(n);
    *fGPUOut << "\\n\";";
    
    // Insert OpenCL code as a string
    tab(n, *fOut); *fOut << fGPUOut->str();
   
    tab(n, *fOut);
    tab(n, *fOut); *fOut << "class " << fKlassName << " : public " << fSuperKlassName << " {";
    
        tab(n+1, *fOut); 
        
        if (gUIMacroSwitch) {
            tab(n, *fOut); *fOut << "  public:";
        } else {
            tab(n, *fOut); *fOut << "  private:";
        }
        tab(n+1, *fOut); 
       
        // Fields
        if (fDeclarationInstructions->fCode.size() > 0) {
            fCodeProducer.Tab(n+1);
            
            // Separate control and non-controls fields in 2 structures
            tab(n+1, *fOut); *fOut << "typedef struct {";
                DSPInstVisitor dsp_visitor(fOut, n+2);
                fDeclarationInstructions->accept(&dsp_visitor);
            tab(n+1, *fOut); *fOut << "} faustdsp;";
            tab(n+1, *fOut);
            
            tab(n+1, *fOut); *fOut << "typedef struct {";
                ControlInstVisitor control_visitor(fOut, n+2);
                fDeclarationInstructions->accept(&control_visitor);
            tab(n+1, *fOut); *fOut << "} faustcontrol;";
            
            tab(n+1, *fOut);
            tab(n+1, *fOut); *fOut << "faustcontrol fControl;";
            tab(n+1, *fOut); *fOut << "cl_mem fGPUDSP;";
            tab(n+1, *fOut); *fOut << "cl_mem fGPUControl;";
        }
        
        tab(n+1, *fOut); *fOut << "cl_device_id fDeviceID;";
        tab(n+1, *fOut); *fOut << "cl_context fContext;";
        tab(n+1, *fOut); *fOut << "cl_command_queue fCommands;";
        tab(n+1, *fOut); *fOut << "cl_program fProgram;";
        tab(n+1, *fOut); *fOut << "cl_kernel fComputeKernel;";
        tab(n+1, *fOut); *fOut << "cl_kernel fInstanceInitKernel;";
        
        tab(n+1, *fOut); *fOut << "cl_mem* fInputs;";
        tab(n+1, *fOut); *fOut << "cl_mem* fOutputs;";
        tab(n+1, *fOut); *fOut << "cl_device_id* fDevicesTable;";
        tab(n+1, *fOut); *fOut << "RunThread* fRunThread;";
        tab(n+1, *fOut); *fOut << "int fCount;";
        if (fNumInputs > 0) {
            tab(n+1, *fOut); *fOut << "float** fTempInputs;";
        }
        if (fNumOutputs > 0) {
            tab(n+1, *fOut); *fOut << "float** fTempOutputs;";
        }
        tab(n+1, *fOut);
            
    tab(n, *fOut); *fOut << "  public:";
    
        // Print metadata declaration
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "void static metadata(Meta* m) { ";
        
        for (map<Tree, set<Tree> >::iterator i = gMetaDataSet.begin(); i != gMetaDataSet.end(); i++) {
            if (i->first != tree("author")) {
                tab(n+2, *fOut); *fOut << "m->declare(\"" << *(i->first) << "\", " << **(i->second.begin()) << ");";
            } else {
                for (set<Tree>::iterator j = i->second.begin(); j != i->second.end(); j++) {
                    if (j == i->second.begin()) {
                        tab(n+2, *fOut); *fOut << "m->declare(\"" << *(i->first) << "\", " << **j << ");";
                    } else {
                        tab(n+2, *fOut); *fOut << "m->declare(\"" << "contributor" << "\", " << **j << ");";
                    }
                }
            }
        }
    
        tab(n+1, *fOut); *fOut << "}" << endl;
        
        tab(n+1, *fOut); *fOut << "static double executionTime(cl_event &event) {";
            tab(n+2, *fOut); *fOut << "cl_ulong start, end;";
            tab(n+2, *fOut); *fOut << "clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end, NULL);";
            tab(n+2, *fOut); *fOut << "clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start, NULL);";
            tab(n+2, *fOut); *fOut << "return (double)1.0e-6 * (end - start); // Convert nanoseconds to milliseconds on return";
        tab(n+1, *fOut); *fOut << "}" << endl;
        
        tab(n+1, *fOut); *fOut << "static void* RunHandler(void* arg) {";
            tab(n+2, *fOut); *fOut << "mydsp* dsp = static_cast<mydsp*>(arg);";
            
            tab(n+2, *fOut); *fOut << "if (dsp->fRunThread->fRealTime) {";
                tab(n+3, *fOut); *fOut << "dsp->fRunThread->Wait();";
                tab(n+3, *fOut); *fOut << "SetRealTime();";
            tab(n+2, *fOut); *fOut << "}";
        
            tab(n+2, *fOut); *fOut << "while (true) {";
                tab(n+3, *fOut); *fOut << "dsp->fRunThread->Wait();";
                 
                // Pass variable parameters
                tab(n+3, *fOut); *fOut << "int err = 0;";
                tab(n+3, *fOut); *fOut << "err |= clSetKernelArg(dsp->fComputeKernel, 0, sizeof(int), &dsp->fCount);";
                tab(n+3, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                    tab(n+4, *fOut); *fOut << "std::cerr << \"clSetKernelArg err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "}";
                
                tab(n+3, *fOut); *fOut << "size_t global, local;";
                tab(n+3, *fOut); *fOut << "err = clGetKernelWorkGroupInfo(dsp->fComputeKernel, dsp->fDeviceID, CL_KERNEL_WORK_GROUP_SIZE, sizeof(local), &local, NULL);";
                tab(n+3, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                    tab(n+4, *fOut); *fOut << "std::cerr << \"clGetKernelWorkGroupInfo err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "}";
                
                tab(n+3, *fOut); *fOut << "cl_event dsp_execution;";
                
                if (gVectorSwitch) {
                    //tab(n+3, *fOut); *fOut << "global = dsp->fCount;";
                    tab(n+3, *fOut); *fOut << "global = local = 32;";
                    tab(n+3, *fOut); *fOut << "err = clEnqueueNDRangeKernel(dsp->fCommands, dsp->fComputeKernel, 1, NULL, &global, &local, 0, NULL, &dsp_execution);";
                    tab(n+3, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                        tab(n+4, *fOut); *fOut << "std::cerr << \"clEnqueueNDRangeKernel compute err = \" << err << endl;";
                    tab(n+3, *fOut); *fOut << "}";
                } else {
                    // Only one kernel
                    tab(n+3, *fOut); *fOut << "err = clEnqueueTask(dsp->fCommands, dsp->fComputeKernel, 0, NULL, &dsp_execution);";
                    tab(n+3, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                        tab(n+4, *fOut); *fOut << "std::cerr << \"clEnqueueTask compute err = \" << err << endl;";
                    tab(n+3, *fOut); *fOut << "}";
                }
               		         
                // Wait for computation end
                tab(n+3, *fOut); *fOut << "err = clFinish(dsp->fCommands);";
                tab(n+3, *fOut); *fOut << "cout << \"Execution time = \" << 100 * executionTime(dsp_execution) * double(dsp->fSamplingFreq) / (double(dsp->fCount) * 1000) << \"%\" << endl;";
             
            tab(n+2, *fOut); *fOut << "}";
            tab(n+2, *fOut); *fOut << "return NULL;";
        tab(n+1, *fOut); *fOut << "}" << endl;
        
        
        tab(n+1, *fOut); *fOut << fKlassName << "() {";
            tab(n+2, *fOut); *fOut << "int err;";
            tab(n+2, *fOut); *fOut << "int gpu = 1;"; 
            tab(n+2, *fOut); *fOut << "cl_uint num_devices;"; 
            tab(n+2, *fOut); *fOut << "char* program_src;"; 
            
            if (fNumInputs > 0) {
                tab(n+2, *fOut); *fOut << "fInputs = new cl_mem["<< fNumInputs << "];";
                tab(n+2, *fOut); *fOut << "fTempInputs = new float*["<< fNumInputs << "];";
            }
            if (fNumOutputs > 0) {
                tab(n+2, *fOut); *fOut << "fOutputs = new cl_mem["<< fNumOutputs << "];";
                tab(n+2, *fOut); *fOut << "fTempOutputs = new float*["<< fNumOutputs << "];";
            }
            
            // Creates device
            tab(n+2, *fOut); *fOut << "err = clGetDeviceIDs(NULL, gpu ? CL_DEVICE_TYPE_GPU : CL_DEVICE_TYPE_CPU, 0, NULL, &num_devices);";   
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot count CPU devices err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";
            
            tab(n+2, *fOut); *fOut << "fDevicesTable = new cl_device_id[num_devices];";
            
            tab(n+2, *fOut); *fOut << "err = clGetDeviceIDs(NULL, gpu ? CL_DEVICE_TYPE_GPU : CL_DEVICE_TYPE_CPU, num_devices, fDevicesTable, NULL);";   
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot get CPU devices err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";
            
            tab(n+2, *fOut); *fOut << "fDeviceID = fDevicesTable[0];";
            
            // Print device name
            tab(n+2, *fOut); *fOut << "char cDevName[1024];";
            tab(n+2, *fOut); *fOut << "err = clGetDeviceInfo(fDeviceID, CL_DEVICE_NAME, sizeof(cDevName), &cDevName, NULL);";
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot get CPU devices err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";
            
            tab(n+2, *fOut); *fOut << "std::cerr << \"Device name: \" << cDevName << endl;";
            
            // Creates context
            tab(n+2, *fOut); *fOut << "fContext = clCreateContext(0, 1, &fDeviceID, clLogMessagesToStdoutAPPLE, NULL, &err);";   
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot create context err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";
            
            // Creates a command queue
            tab(n+2, *fOut); *fOut << "fCommands = clCreateCommandQueue(fContext, fDeviceID, CL_QUEUE_PROFILING_ENABLE, &err);";   
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot create command queue err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";
            
            // Creates the compute program from the source buffer
            tab(n+2, *fOut); *fOut << "fProgram = clCreateProgramWithSource(fContext, 1, (const char**)&KernelSource, NULL, &err);";  
            
            /*
            tab(n+2, *fOut); *fOut << "program_src = load_program_source(\"tmp.cl\");"; 
            tab(n+2, *fOut); *fOut << "fProgram = clCreateProgramWithSource(fContext, 1, (const char**)&program_src, NULL, &err);";  
            */
            
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot create program err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";
            
            // Build the program executable
            tab(n+2, *fOut); *fOut << "err = clBuildProgram(fProgram, 0, NULL, \"-cl-denorms-are-zero\", NULL, NULL);";   
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot build program err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "goto error_build;";
            tab(n+2, *fOut); *fOut << "}";
            
            // Create the compute kernel 
            tab(n+2, *fOut); *fOut << "fComputeKernel = clCreateKernel(fProgram, \"computeKernel\", &err);";   
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot create compute kernel err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";
            
            // Create the nstanceInit kernel 
            tab(n+2, *fOut); *fOut << "fInstanceInitKernel = clCreateKernel(fProgram, \"instanceInitKernel\", &err);";   
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot create instanceInit kernel err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";
            
            // Get infos
            tab(n+2, *fOut); *fOut << "size_t local;";
			tab(n+2, *fOut); *fOut << "err = clGetKernelWorkGroupInfo(fComputeKernel, fDeviceID, CL_KERNEL_WORK_GROUP_SIZE, sizeof(local), &local, NULL);";
			tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"clGetKernelWorkGroupInfo CL_KERNEL_WORK_GROUP_SIZE err = \" << err << endl;";
			tab(n+2, *fOut); *fOut << "} else {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"CL_KERNEL_WORK_GROUP_SIZE = \" << err << local << endl;";
            tab(n+2, *fOut); *fOut << "}";
            
            tab(n+2, *fOut); *fOut << "cl_ulong local_mem;";
            tab(n+2, *fOut); *fOut << "err = clGetKernelWorkGroupInfo(fComputeKernel, fDeviceID, CL_KERNEL_LOCAL_MEM_SIZE, sizeof(local_mem), &local_mem, NULL);";
			tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"clGetKernelWorkGroupInfo CL_KERNEL_LOCAL_MEM_SIZE err = \" << err << endl;";
			tab(n+2, *fOut); *fOut << "} else {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"CL_KERNEL_LOCAL_MEM_SIZE = \" << err << local_mem << endl;";
            tab(n+2, *fOut); *fOut << "}";
            
            // Allocate kernel input buffers (shared between CPU and GPU)
            if (fNumInputs > 0) {
                tab(n+2, *fOut); *fOut << "for (int i = 0; i < " << fNumInputs << "; i++) {";
                    tab(n+3, *fOut); *fOut << subst("fTempInputs[i] = new $0[sizeof($0) * 8192];", xfloat());
                    tab(n+3, *fOut); *fOut << subst("fInputs[i] = clCreateBuffer(fContext, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof($0) * 8192, fTempInputs[i], &err);", xfloat());
                    tab(n+3, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                        tab(n+4, *fOut); *fOut << "std::cerr << \"Cannot allocate input buffer err = \" << err << endl;";
                        tab(n+4, *fOut); *fOut << "goto error;";
                    tab(n+3, *fOut); *fOut << "}";
                tab(n+2, *fOut); *fOut << "}";
            }
            
            // Allocate kernel output buffers (shared between CPU and GPU)
            if (fNumOutputs > 0) {
                tab(n+2, *fOut); *fOut << "for (int i = 0; i < " << fNumOutputs << "; i++) {";
                    tab(n+3, *fOut); *fOut << subst("fTempOutputs[i] = new $0[sizeof($0) * 8192];", xfloat());
                    tab(n+3, *fOut); *fOut << subst("fOutputs[i] = clCreateBuffer(fContext, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, sizeof($0) * 8192, fTempOutputs[i], &err);", xfloat());
                    
                    tab(n+3, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                        tab(n+4, *fOut); *fOut << "std::cerr << \"Cannot allocate output buffer err = \" << err << endl;";
                        tab(n+4, *fOut); *fOut << "goto error;";
                    tab(n+3, *fOut); *fOut << "}";
                tab(n+2, *fOut); *fOut << "}";
            }
            
            // Allocate control on CPU, map it on GPU
            tab(n+2, *fOut); *fOut << "fGPUControl = clCreateBuffer(fContext, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, sizeof(faustcontrol), &fControl, &err);";
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot allocate control err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";
            
             // Allocate DSP  on GPU
            tab(n+2, *fOut); *fOut << "fGPUDSP = clCreateBuffer(fContext, CL_MEM_READ_WRITE, sizeof(faustdsp), NULL, &err);";
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot allocate DSP err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";
               
            // Pass parameters that do not change between kernel invocations
            tab(n+2, *fOut); *fOut << "err = 0;" << endl;
            if (fNumInputs > 0) {
                tab(n+2, *fOut); *fOut << "for (int i = 0; i < " << fNumInputs << "; i++) {";
                    tab(n+3, *fOut); *fOut << "err |= clSetKernelArg(fComputeKernel, i+1, sizeof(cl_mem), &fInputs[i]);";
                tab(n+2, *fOut); *fOut << "}";
            }
            if (fNumOutputs > 0) {
                tab(n+2, *fOut); *fOut << "for (int i = 0; i < " << fNumOutputs << "; i++) {";
                    tab(n+3, *fOut); *fOut << "err |= clSetKernelArg(fComputeKernel, " << fNumInputs << "+i+1, sizeof(cl_mem), &fOutputs[i]);";
                tab(n+2, *fOut); *fOut << "}";
            }
            
            tab(n+2, *fOut); *fOut << "err |= clSetKernelArg(fComputeKernel, " << (fNumInputs + fNumOutputs) << "+1, sizeof(cl_mem), &fGPUDSP);";
            tab(n+2, *fOut); *fOut << "err |= clSetKernelArg(fComputeKernel, " << (fNumInputs + fNumOutputs) << "+2, sizeof(cl_mem), &fGPUControl);";
        
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"clSetKernelArg err = \" << err << endl;";
            tab(n+2, *fOut); *fOut << "}";
            
            tab(n+2, *fOut); *fOut << "fRunThread = new RunThread();";
            tab(n+2, *fOut); *fOut << "err = fRunThread->Start(true, RunHandler, this);";
            tab(n+2, *fOut); *fOut << "if (err != 0) {";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";
            
            tab(n+2, *fOut); *fOut << "return;" << endl;
            
         tab(n+1, *fOut); *fOut << "error_build:";
            tab(n+2, *fOut); *fOut << "cl_build_status build_status;";
            tab(n+2, *fOut); *fOut << "err = clGetProgramBuildInfo(fProgram, fDeviceID, CL_PROGRAM_BUILD_STATUS, sizeof(cl_build_status), &build_status, NULL);";
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"clGetProgramBuildInfo CL_PROGRAM_BUILD_STATUS err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";
            
            tab(n+2, *fOut); *fOut << "char* build_log;";
            tab(n+2, *fOut); *fOut << "size_t ret_val_size;";
            tab(n+2, *fOut); *fOut << "err = clGetProgramBuildInfo(fProgram, fDeviceID, CL_PROGRAM_BUILD_LOG, 0, NULL, &ret_val_size);";
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"clGetProgramBuildInfo CL_PROGRAM_BUILD_LOG err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";
            
            tab(n+2, *fOut); *fOut << "char build_log1[ret_val_size + 1];";
            tab(n+2, *fOut); *fOut << "err = clGetProgramBuildInfo(fProgram, fDeviceID, CL_PROGRAM_BUILD_LOG, ret_val_size, build_log1, NULL);";
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"clGetProgramBuildInfo CL_PROGRAM_BUILD_LOG err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";
            tab(n+2, *fOut); *fOut << "build_log1[ret_val_size] = '\\0';";
            tab(n+2, *fOut); *fOut << "std::cerr << \"BUILD LOG\" << std::endl;";
            tab(n+2, *fOut); *fOut << "std::cerr << build_log1 << std::endl;";
                    
        tab(n+1, *fOut); *fOut << "error:";
            tab(n+2, *fOut); *fOut << "throw std::bad_alloc();";   
        tab(n+1, *fOut); *fOut << "}" << endl;

        
        tab(n+1, *fOut); *fOut << "virtual ~" << fKlassName << "() {";
            tab(n+2, *fOut); *fOut << "fRunThread->Stop();";
            tab(n+2, *fOut); *fOut << "delete fRunThread;";
            
            // Free kernel input buffers
            if (fNumInputs > 0) {
                tab(n+2, *fOut); *fOut << "for (int i = 0; i < " << fNumInputs << "; i++) {";
                    tab(n+3, *fOut); *fOut << "clReleaseMemObject(fInputs[i]);";
                     tab(n+3, *fOut); *fOut << "delete[] fTempInputs[i];";
                tab(n+2, *fOut); *fOut << "}";
            }
            
            // Free kernel output buffers
            if (fNumOutputs > 0) {
                tab(n+2, *fOut); *fOut << "for (int i = 0; i < " << fNumOutputs << "; i++) {";
                    tab(n+3, *fOut); *fOut << "clReleaseMemObject(fOutputs[i]);";
                    tab(n+3, *fOut); *fOut << "delete[] fTempOutputs[i];";
                tab(n+2, *fOut); *fOut << "}";
            }
            
            if (fNumInputs > 0) {
                tab(n+2, *fOut); *fOut << "delete[] fInputs;";
                tab(n+2, *fOut); *fOut << "delete[] fTempInputs;";
            }
            if (fNumOutputs > 0) {
                tab(n+2, *fOut); *fOut << "delete[] fOutputs;";
                tab(n+2, *fOut); *fOut << "delete[] fTempOutputs;";
            }
            
            // Shutdown and cleanup
            tab(n+2, *fOut); *fOut << "clReleaseMemObject(fGPUControl);";
            tab(n+2, *fOut); *fOut << "clReleaseMemObject(fGPUDSP);";
            tab(n+2, *fOut); *fOut << "clReleaseKernel(fComputeKernel);";
            tab(n+2, *fOut); *fOut << "clReleaseKernel(fInstanceInitKernel);";
            tab(n+2, *fOut); *fOut << "clReleaseCommandQueue(fCommands);";
            tab(n+2, *fOut); *fOut << "clReleaseContext(fContext);";
            
            tab(n+2, *fOut); *fOut << "destroy();";
      
        tab(n+1, *fOut); *fOut << "}" << endl;
        
        tab(n+1, *fOut); *fOut << "void destroy() {";
            if (fDestroyInstructions->fCode.size() > 0) {
                tab(n+2, *fOut); 
                fCodeProducer.Tab(n+2);
                fDestroyInstructions->accept(&fCodeProducer);
            }
        tab(n+1, *fOut);  *fOut << "}";
        tab(n+1, *fOut); 
            
        // Input method
        tab(n+1, *fOut); *fOut << "virtual int getNumInputs() { "
                            << "return " << fNumInputs << "; }";
        
        // Output method
        tab(n+1, *fOut); *fOut << "virtual int getNumOutputs() { "
                            << "return " << fNumOutputs << "; }";
       
        // Inits
        tab(n+1, *fOut); 
        tab(n+1, *fOut); *fOut << "static void classInit(int samplingFreq) {";
            if (fStaticInitInstructions->fCode.size() > 0) {
                tab(n+2, *fOut);
                fCodeProducer.Tab(n+2);
                fStaticInitInstructions->accept(&fCodeProducer);
            }
        tab(n+1, *fOut); *fOut << "}";

        tab(n+1, *fOut); 
        tab(n+1, *fOut); *fOut << "virtual void instanceInit(int samplingFreq) {";
            if (fInitInstructions->fCode.size() > 0) {
                
                tab(n+2, *fOut); *fOut << "fSamplingFreq = samplingFreq;";
                
                tab(n+2, *fOut); *fOut << "int err = 0;";
                tab(n+2, *fOut); *fOut << "err |= clSetKernelArg(fInstanceInitKernel, 0, sizeof(cl_mem), &fGPUDSP);";
                tab(n+2, *fOut); *fOut << "err |= clSetKernelArg(fInstanceInitKernel, 1, sizeof(cl_mem), &fGPUControl);";
                tab(n+2, *fOut); *fOut << "err |= clSetKernelArg(fInstanceInitKernel, 2, sizeof(int), &samplingFreq);";
                tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                    tab(n+3, *fOut); *fOut << "std::cerr << \"clSetKernelArg instanceInit err = \" << err << endl;";
                tab(n+2, *fOut); *fOut << "}";
                
                tab(n+2, *fOut); *fOut << "err = clEnqueueTask(fCommands, fInstanceInitKernel, 0, NULL, NULL);";
                tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                    tab(n+3, *fOut); *fOut << "std::cerr << \"clEnqueueTask instanceInit err = \" << err << endl;";
                tab(n+2, *fOut); *fOut << "}";
                
                // Wait for instanceInit end
                tab(n+2, *fOut); *fOut << "err = clFinish(fCommands);";
                tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                    tab(n+3, *fOut); *fOut << "std::cerr << \"clFinish instanceInit err = \" << err << endl;";
                tab(n+2, *fOut); *fOut << "}";

            }
        tab(n+1, *fOut); *fOut << "}";

        tab(n+1, *fOut); 
        tab(n+1, *fOut); *fOut << "virtual void init(int samplingFreq) {";
            tab(n+2, *fOut); *fOut << "classInit(samplingFreq);";
            tab(n+2, *fOut); *fOut << "instanceInit(samplingFreq);";
        tab(n+1, *fOut); *fOut << "}";
        
        // User interface
        tab(n+1, *fOut); 
        tab(n+1, *fOut); *fOut << "virtual void buildUserInterface(UI* interface) {";
            if (fUserInterfaceInstructions->fCode.size() > 0) {
                tab(n+2, *fOut);
                fCodeProducer.Tab(n+2);
                UIInstVisitor ui_visitor(fOut, n+2);
                fUserInterfaceInstructions->accept(&ui_visitor);
            }
        tab(n+1, *fOut); *fOut << "}";
        
        // Compute
        generateCompute(n);
        tab(n, *fOut);
        
        // Possibly generate separated functions
        fCodeProducer.Tab(n+1);
        tab(n+1, *fOut);
        if (fComputeFunctions->fCode.size() > 0) {    
            fComputeFunctions->accept(&fCodeProducer);
        }
    
    tab(n, *fOut); *fOut << "};" << endl;
    
    // Generate user interface macros if needed
	if (gUIMacroSwitch) {
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

void CPPOpenCLCodeContainer::generateCompute(int n)
{
    // Generates declaration
    tab(n+1, *fOut);
    tab(n+1, *fOut); *fOut << subst("virtual void compute(int count, $0** inputs, $0** outputs) {", xfloat());
    fCodeProducer.Tab(n+2);
   
    tab(n+2, *fOut); *fOut << "fCount = count;";
    tab(n+2, *fOut); *fOut << "GetRealTime();";
    
    // Copy audio input buffer to temp buffers
    if (fNumInputs > 0) {
        tab(n+2, *fOut); *fOut << "for (int i = 0; i < " << fNumInputs << "; i++) {";
            tab(n+3, *fOut); *fOut << subst("memcpy(fTempInputs[i], inputs[i], sizeof($0) * count);", xfloat());
        tab(n+2, *fOut); *fOut << "}";
        tab(n+2, *fOut);
    }
    
    // Copy temp buffers to audio output buffers
    if (fNumOutputs > 0) {
        tab(n+2, *fOut); *fOut << "for (int i = 0; i < " << fNumOutputs << "; i++) {";
            tab(n+3, *fOut); *fOut << subst("memcpy(outputs[i], fTempOutputs[i], sizeof($0) * count);", xfloat());
        tab(n+2, *fOut); *fOut << "}";
        tab(n+2, *fOut);
    }
    tab(n+2, *fOut); *fOut << "fRunThread->Signal();";
    tab(n+1, *fOut); *fOut << "}";
}

void CPPOpenCLCodeContainer::generateComputeKernel(int n)
{
    // Generate compute kernel
    tab1(n, *fGPUOut);
    *fGPUOut << "__kernel void computeKernel(const unsigned int count, ";
    
    for (int i = 0; i < fNumInputs; i++) {
        *fGPUOut <<  "__global float* input" << i << ", ";
    }
    
    for (int i = 0; i < fNumOutputs; i++) {
        if (i == fNumOutputs - 1) {
            *fGPUOut << "__global float* output" << i;
        } else {
            *fGPUOut << "__global float* output" << i << ", ";
        }    
    }
    
    *fGPUOut << ", __global faustdsp* dsp, __global faustcontrol* control) {";
    tab1(n+1, *fGPUOut);
   
    // Generates local variables declaration and setup
    fComputeBlockInstructions->accept(fKernelCodeProducer);
    
    // Generates one single scalar loop
    ForLoopInst* loop = fCurLoop->getScalarLoop();
    loop->accept(fKernelCodeProducer);
      
    tab1(n, *fGPUOut);
    
    *fGPUOut << "}";
    tab1(n, *fGPUOut);
}

void CPPOpenCLVectorCodeContainer::generateComputeKernel(int n)
{
    // Generate compute kernel
    tab1(n, *fGPUOut);
    *fGPUOut << "__kernel void computeKernel(const int fullcount, ";
    
    for (int i = 0; i < fNumInputs; i++) {
        *fGPUOut <<  "__global float* input" << i << ", ";
    }
    
    for (int i = 0; i < fNumOutputs; i++) {
        if (i == fNumOutputs - 1) {
            *fGPUOut << "__global float* output" << i;
        } else {
            *fGPUOut << "__global float* output" << i << ", ";
        }    
    }
    
    *fGPUOut << ", __global faustdsp* dsp, __global faustcontrol* control) {";
    tab1(n+1, *fGPUOut);
    
    // Generates local variables declaration and setup
    BlockKernelInstVisitor block_visitor(fGPUOut, n+1);
    fComputeBlockInstructions->accept(&block_visitor);
    
    lclgraph dag;
    CodeLoop::sortGraph(fCurLoop, dag);
    computeForwardDAG(dag);
    
    BlockInst* loop_code = InstBuilder::genBlockInst();
    
    // Generate local input/output access
    //generateLocalInputs(loop_code);
    //generateLocalOutputs(loop_code);
    
    // Generate : int count = min(32, (fullcount - index))
    ValueInst* init1 = InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fullcount", Address::kFunArgs));
    ValueInst* init2 = InstBuilder::genBinopInst(kSub, init1, InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("index", Address::kLoop)));
    list<ValueInst*> min_fun_args;
    min_fun_args.push_back(InstBuilder::genIntNumInst(gVecSize));
    min_fun_args.push_back(init2);
    ValueInst* init3 = InstBuilder::genFunCallInst("min", min_fun_args);
    StatementInst* count_dec = InstBuilder::genDeclareVarInst("count", InstBuilder::genBasicTyped(Typed::kInt), Address::kStack, init3);
    loop_code->pushBackInst(count_dec);
    
    // Generates get_global_id access
    list<ValueInst*> args;
    args.push_back(InstBuilder::genIntNumInst(0));
    loop_code->pushBackInst(InstBuilder::genDeclareVarInst("tasknum", 
        InstBuilder::genBasicTyped(Typed::kInt), Address::kStack, 
        InstBuilder::genFunCallInst("get_global_id", args)));
    
    // Generate DAG
    for (int l = dag.size() - 1; l >= 0; l--) {
    
        ValueInst* switch_cond = InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("tasknum", Address::kStack));
        SwitchInst* switch_block = InstBuilder::genSwitchInst(switch_cond);
    
        if (dag[l].size() > 1) {
            int loop_num = 0;
            for (lclset::const_iterator p = dag[l].begin(); p != dag[l].end(); p++) {
                BlockInst* switch_case_block = InstBuilder::genBlockInst();
                generateLoopNode(*p, switch_case_block, loop_num);
                switch_block->addCase(loop_num, switch_case_block);
                loop_num++;
            }
        } else {
            BlockInst* single_case_block = InstBuilder::genBlockInst();
            generateLoopNode(*dag[l].begin(), single_case_block, 0);
            switch_block->addCase(0, single_case_block);
        }
        
        loop_code->pushBackInst(switch_block);
        loop_code->pushBackInst(InstBuilder::genLabelInst("barrier(CLK_LOCAL_MEM_FENCE|CLK_GLOBAL_MEM_FENCE);"));
    }
    
    // Generates the DAG enclosing loop
    string index = "index";
    DeclareVarInst* loop_init = InstBuilder::genDeclareVarInst(index, InstBuilder::genBasicTyped(Typed::kInt), Address::kLoop, InstBuilder::genIntNumInst(0));

    ValueInst* loop_end = InstBuilder::genBinopInst(kLT,
                                InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop)),
                                InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("fullcount", Address::kFunArgs)));
    StoreVarInst* loop_increment = InstBuilder::genStoreVarInst(InstBuilder::genNamedAddress(index, Address::kLoop),
                        InstBuilder::genBinopInst(kAdd,
                                    InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(index, Address::kLoop)),
                                    InstBuilder::genIntNumInst(gVecSize)));

    StatementInst* loop = InstBuilder::genForLoopInst(loop_init, loop_end, loop_increment, loop_code);

    // Generates the final loop
    loop->accept(fKernelCodeProducer);
    
    *fGPUOut << "}";
    tab1(n, *fGPUOut);
}
