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
       
    // Compile OpenCL kernel string
    OpenCLInstVisitor codeproducer(fComputeKernelStream);
    codeproducer.Tab(n+1);
    
    //*fComputeKernelStream << subst("const char* KernelSource = \"__kernel void computeKernel(const unsigned int count, __global $0** inputs, __global $0** outputs) \n", xfloat());
    
    *fComputeKernelStream << "const char* KernelSource = \"__kernel void computeKernel(const unsigned int count, ";
    for (int i = 0; i < fNumInputs; i++) {
        *fComputeKernelStream <<  "__global float* input" << i << ", ";
    }
    
    for (int i = 0; i < fNumOutputs; i++) {
        if (i == fNumOutputs - 1) {
            *fComputeKernelStream <<  "__global float* output" << i;
        }else {
            *fComputeKernelStream <<  "__global float* output" << i << ", ";
        }    
    }
    
    *fComputeKernelStream << ") {}\";";
     
    tab(n+1, *fComputeKernelStream);
    
   
    // Generates local variables declaration and setup
    fComputeBlockInstructions->accept(&codeproducer);
    
    // Generates one single scalar loop
    ForLoopInst* loop = fCurLoop->getScalarLoop();
    loop->accept(&codeproducer);
    
     /*
    tab(n, *fComputeKernelStream);
    *fComputeKernelStream << "\"";
    */
       
    // Generate OpenCL kernel string
    //tab(n, *fOut); *fOut << fComputeKernelStream->str() << ";";
    
    tab(n, *fOut); *fOut << fComputeKernelStream->str();
   
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
        tab(n+1, *fOut); *fOut << "cl_mem* fOpenCLInputs;";
        tab(n+1, *fOut); *fOut << "cl_mem* fOpenCLOutputs;";
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
        
        tab(n+1, *fOut); *fOut   << "static void* RunHandler(void* arg) {";
        
            tab(n+2, *fOut); *fOut << "mydsp* dsp = static_cast<mydsp*>(arg);";
            
            // Pass parameters that do not change between kernel invocations
            tab(n+2, *fOut); *fOut << "int err = 0;" << endl;
            if (fNumInputs > 0) {
                tab(n+2, *fOut); *fOut << "for (int i = 0; i < " << fNumInputs << "; i++) {";
                    tab(n+3, *fOut); *fOut << "err |= clSetKernelArg(dsp->fOpenCLKernel, i+1, sizeof(cl_mem), &dsp->fOpenCLInputs[i]);";
                tab(n+2, *fOut); *fOut << "}";
            }
            if (fNumOutputs > 0) {
                tab(n+2, *fOut); *fOut << "for (int i = 0; i < " << fNumOutputs << "; i++) {";
                    tab(n+3, *fOut); *fOut << "err |= clSetKernelArg(dsp->fOpenCLKernel, " << fNumInputs << "+i+1, sizeof(cl_mem), &dsp->fOpenCLOutputs[i]);";
                tab(n+2, *fOut); *fOut << "}";
            }
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"clSetKernelArg err = \" << err << endl;";
            tab(n+2, *fOut); *fOut << "}";
            
            tab(n+2, *fOut); *fOut << "while (true) {";
                tab(n+3, *fOut); *fOut << "dsp->fRunThread->Wait();";
                 
                // Pass variable parameters
                tab(n+3, *fOut); *fOut << "err = 0;";
                tab(n+3, *fOut); *fOut << "err |= clSetKernelArg(dsp->fOpenCLKernel, 0, sizeof(unsigned int), &dsp->fCount);";
                tab(n+3, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                    tab(n+4, *fOut); *fOut << "std::cerr << \"clSetKernelArg err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "}";
                
                tab(n+3, *fOut); *fOut << "size_t global, local;";
                tab(n+3, *fOut); *fOut << "err = clGetKernelWorkGroupInfo(dsp->fOpenCLKernel, dsp->fOpenCLDeviceID, CL_KERNEL_WORK_GROUP_SIZE, sizeof(local), &local, NULL);";
                tab(n+3, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                    tab(n+4, *fOut); *fOut << "std::cerr << \"clGetKernelWorkGroupInfo err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "}";
                
                tab(n+3, *fOut); *fOut << "global = dsp->fCount;";
                tab(n+3, *fOut); *fOut << "err = clEnqueueNDRangeKernel(dsp->fOpenCLCommands, dsp->fOpenCLKernel, 1, NULL, &global, &local, 0, NULL, NULL);";
                tab(n+3, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                    tab(n+4, *fOut); *fOut << "std::cerr << \"clEnqueueNDRangeKernel err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "}";
                
                // Wait for computation end
                tab(n+3, *fOut); *fOut << "err = clFinish(dsp->fOpenCLCommands);";
             
            tab(n+2, *fOut); *fOut << "}";
            
        tab(n+1, *fOut); *fOut << "}" << endl;
        
        
        tab(n+1, *fOut); *fOut << fKlassName << "() {";
            tab(n+2, *fOut); *fOut << "int err;";
            tab(n+2, *fOut); *fOut << "int gpu = 1;"; 
            tab(n+2, *fOut); *fOut << "cl_uint num_devices;"; 
            
            if (fNumInputs > 0) {
                tab(n+2, *fOut); *fOut << "fOpenCLInputs = new cl_mem["<< fNumInputs << "];";
                tab(n+2, *fOut); *fOut << "fTempInputs = new float*["<< fNumInputs << "];";
            }
            if (fNumOutputs > 0) {
                tab(n+2, *fOut); *fOut << "fOpenCLOutputs = new cl_mem["<< fNumOutputs << "];";
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
            
            tab(n+2, *fOut); *fOut << "fOpenCLDeviceID = fDevicesTable[0];";
            
            // Print device name
            tab(n+2, *fOut); *fOut << "char cDevName[1024];";
            tab(n+2, *fOut); *fOut << "err = clGetDeviceInfo(fOpenCLDeviceID, CL_DEVICE_NAME, sizeof(cDevName), &cDevName, NULL);";
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot get CPU devices err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";
            
            tab(n+2, *fOut); *fOut << "std::cerr << \"Device name: \" << cDevName << endl;";
            
            // Creates context
            tab(n+2, *fOut); *fOut << "fOpenCLContext = clCreateContext(0, 1, &fOpenCLDeviceID, NULL, NULL, &err);";   
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot create context err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";
            
            // Creates a command queue
            tab(n+2, *fOut); *fOut << "fOpenCLCommands = clCreateCommandQueue(fOpenCLContext, fOpenCLDeviceID, 0, &err);";   
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot create command queue err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";
            
            // Creates the compute program from the source buffer
            tab(n+2, *fOut); *fOut << "fOpenCLProgram = clCreateProgramWithSource(fOpenCLContext, 1, (const char**)&KernelSource, NULL, &err);";   
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot create program err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";
            
            // Build the program executable
            tab(n+2, *fOut); *fOut << "err = clBuildProgram(fOpenCLProgram, 0, NULL, NULL, NULL, NULL);";   
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot build program err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";
            
            // Create the compute kernel 
            tab(n+2, *fOut); *fOut << "fOpenCLKernel = clCreateKernel(fOpenCLProgram, \"computeKernel\", &err);";   
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot create kernel err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";
            
            // Allocate kernel input buffers
            if (fNumInputs > 0) {
                tab(n+2, *fOut); *fOut << "for (int i = 0; i < " << fNumInputs << "; i++) {";
                    tab(n+3, *fOut); *fOut << "fTempInputs[i] = new float[sizeof(float) * 8192];";
                    tab(n+3, *fOut); *fOut << "fOpenCLInputs[i] = clCreateBuffer(fOpenCLContext, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(float) * 8192, fTempInputs[i], &err);";
                    tab(n+3, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                        tab(n+4, *fOut); *fOut << "std::cerr << \"Cannot allocate input buffer err = \" << err << endl;";
                        tab(n+4, *fOut); *fOut << "goto error;";
                    tab(n+3, *fOut); *fOut << "}";
                tab(n+2, *fOut); *fOut << "}";
            }
            
            // Allocate kernel output buffers
            if (fNumOutputs > 0) {
                tab(n+2, *fOut); *fOut << "for (int i = 0; i < " << fNumOutputs << "; i++) {";
                    tab(n+3, *fOut); *fOut << "fTempOutputs[i] = new float[sizeof(float) * 8192];";
                    tab(n+3, *fOut); *fOut << "fOpenCLOutputs[i] = clCreateBuffer(fOpenCLContext, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, sizeof(float) * 8192, fTempOutputs[i], &err);";
                    
                    tab(n+3, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                        tab(n+4, *fOut); *fOut << "std::cerr << \"Cannot allocate output buffer err = \" << err << endl;";
                        tab(n+4, *fOut); *fOut << "goto error;";
                    tab(n+3, *fOut); *fOut << "}";
                tab(n+2, *fOut); *fOut << "}";
            }
            
            tab(n+2, *fOut); *fOut << "fRunThread = new RunThread();";
            tab(n+2, *fOut); *fOut << "err = fRunThread->Start(true, RunHandler, this);";
            tab(n+2, *fOut); *fOut << "if (err != 0) {";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";
            
            tab(n+2, *fOut); *fOut << "return;" << endl;
                    
        tab(n+1, *fOut); *fOut << "error:";
            tab(n+2, *fOut); *fOut << "throw std::bad_alloc();";   
        tab(n+1, *fOut); *fOut << "}" << endl;

        
        tab(n+1, *fOut); *fOut << "virtual ~" << fKlassName << "() {";
            tab(n+2, *fOut); *fOut << "fRunThread->Stop();";
            tab(n+2, *fOut); *fOut << "delete fRunThread;";
            // Free kernel input buffers
            if (fNumInputs > 0) {
                tab(n+2, *fOut); *fOut << "for (int i = 0; i < " << fNumInputs << "; i++) {";
                    tab(n+3, *fOut); *fOut << "clReleaseMemObject(fOpenCLInputs[i]);";
                     tab(n+3, *fOut); *fOut << "delete[] fTempInputs[i];";
                tab(n+2, *fOut); *fOut << "}";
            }
            
            // Free kernel output buffers
            if (fNumOutputs > 0) {
                tab(n+2, *fOut); *fOut << "for (int i = 0; i < " << fNumOutputs << "; i++) {";
                    tab(n+3, *fOut); *fOut << "clReleaseMemObject(fOpenCLOutputs[i]);";
                    tab(n+3, *fOut); *fOut << "delete[] fTempOutputs[i];";
                tab(n+2, *fOut); *fOut << "}";
            }
            
            if (fNumInputs > 0) {
                tab(n+2, *fOut); *fOut << "delete[] fOpenCLInputs;";
                tab(n+2, *fOut); *fOut << "delete[] fTempInputs;";
            }
            if (fNumOutputs > 0) {
                tab(n+2, *fOut); *fOut << "delete[] fOpenCLOutputs;";
                tab(n+2, *fOut); *fOut << "delete[] fTempOutputs;";
            }
            
            // Shutdown and cleanup
            tab(n+2, *fOut); *fOut << "clReleaseKernel(fOpenCLKernel);";
            tab(n+2, *fOut); *fOut << "clReleaseCommandQueue(fOpenCLCommands);";
            tab(n+2, *fOut); *fOut << "clReleaseContext(fOpenCLContext);";
            
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

void OpenCLCodeContainer::generateCompute(int n)
{
    // Generates declaration
    tab(n+1, *fOut);
    tab(n+1, *fOut); *fOut << subst("virtual void compute(int count, $0** inputs, $0** outputs) {", xfloat());
    fCodeProducer.Tab(n+2);
   
    tab(n+2, *fOut); *fOut << "fCount = count;";
    
    // Copy audio input buffer to temp buffers
    if (fNumInputs > 0) {
        tab(n+2, *fOut); *fOut << "for (int i = 0; i < " << fNumInputs << "; i++) {";
            tab(n+3, *fOut); *fOut << "memcpy(fTempInputs[i], inputs[i], sizeof(float) * count);";
        tab(n+2, *fOut); *fOut << "}";
        tab(n+2, *fOut);
    }
    
    // Copy temp buffers to audio output buffers
    if (fNumOutputs > 0) {
        tab(n+2, *fOut); *fOut << "for (int i = 0; i < " << fNumOutputs << "; i++) {";
            tab(n+3, *fOut); *fOut << "memcpy(outputs[i], fTempOutputs[i], sizeof(float) * count);";
        tab(n+2, *fOut); *fOut << "}";
        tab(n+2, *fOut);
    }
    tab(n+2, *fOut); *fOut << "fRunThread->Signal();";
    tab(n+1, *fOut); *fOut << "}";
}
