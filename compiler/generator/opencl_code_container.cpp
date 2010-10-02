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
using namespace std;

#include "opencl_code_container.hh"
#include "Text.hh"
#include "floats.hh"
#include "function_builder.hh"

extern int gVectorLoopVariant;
extern bool gUIMacroSwitch;

extern map<Tree, set<Tree> > gMetaDataSet;

CodeContainer* OpenCLCodeContainer::createScalarContainer(const string& name) 
{ 
    return new OpenCLCodeContainer(name, "", 0, 1, fOut);
}

void OpenCLCodeContainer::produceInternal()
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

void OpenCLCodeContainer::produceClass() 
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
        
        tab(n+1, *fOut); *fOut << "cl_device_id fOpenCLDeviceID;";
        tab(n+1, *fOut); *fOut << "cl_context fOpenCLContext;";
        tab(n+1, *fOut); *fOut << "cl_command_queue fOpenCLCommands;";
        tab(n+1, *fOut); *fOut << "cl_program fOpenCLProgram;";
        tab(n+1, *fOut); *fOut << "cl_kernel fOpenCLKernel;";
        tab(n+1, *fOut); *fOut << "cl_mem fOpenCLInput;";
        tab(n+1, *fOut); *fOut << "cl_mem fOpenCLOutput;";
        tab(n+1, *fOut);
            
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
        
        tab(n+1, *fOut); *fOut << fKlassName << "() {";
            tab(n+2, *fOut); *fOut << "int err;";
            tab(n+2, *fOut); *fOut << "int gpu = 1;"; 
            tab(n+2, *fOut); *fOut << "cl_uint num_devices;"; 
            
            // Creates device
            tab(n+2, *fOut); *fOut << "err = clGetDeviceIDs(NULL, gpu ? CL_DEVICE_TYPE_GPU : CL_DEVICE_TYPE_CPU, 1, &fOpenCLDeviceID, NULL);";   
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";
            
            // Creates context
            tab(n+2, *fOut); *fOut << "fOpenCLContext = clCreateContext(0, 1, &fOpenCLDeviceID, NULL, NULL, &err);";   
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";
            
            // Creates a command queue
            tab(n+2, *fOut); *fOut << "fOpenCLProgram = clCreateCommandQueue(fOpenCLContext, fOpenCLDeviceID, 0, &err);";   
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";
            
        tab(n+1, *fOut); *fOut << "error:";
            tab(n+2, *fOut); *fOut << "std::bad_alloc();" << endl;   
        tab(n+1, *fOut); *fOut << "}" << endl;

        
        tab(n+1, *fOut); *fOut << "virtual ~" << fKlassName << "() {";
            tab(n+2, *fOut); *fOut << "destroy();";
            // Shutdown and cleanup
            tab(n+2, *fOut); *fOut << "clReleaseMemObject(fOpenCLInput);";
            tab(n+2, *fOut); *fOut << "clReleaseMemObject(fOpenCLOutput);";
            tab(n+2, *fOut); *fOut << "clReleaseKernel(fOpenCLKernel);";
            tab(n+2, *fOut); *fOut << "clReleaseCommandQueue(fOpenCLCommands);";
            tab(n+2, *fOut); *fOut << "clReleaseContext(fOpenCLContext);";
      
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

void OpenCLCodeContainer::generateCompute(int n)
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
