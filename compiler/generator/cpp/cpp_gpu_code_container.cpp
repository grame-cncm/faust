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

#include "cpp_gpu_code_container.hh"
#include "fir_to_fir.hh"

static void tab1(int n, ostream& fout)
{
    fout << "  \\n\"  \\\n";
    fout << "\"";
    while (n--) fout << '\t';
}

void CPPGPUCodeContainer::prepareFIR(void)
{
    // Sort arrays to be at the begining
    fDeclarationInstructions->fCode.sort(sortArrayDeclarations);
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

        // Input method
        tab(n+1, *fOut);
        // TO CHECK
        produceInfoFunctions(n+1, fKlassName, "dsp", false, false, &fCodeProducer);

        // Inits
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "void instanceInit" << fKlassName << "(int samplingFreq) {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateInit(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";

        // Fill
        string counter = "count";
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "void fill" << fKlassName << subst("(int $0, $1* output) {", counter, ifloat());
        tab(n+2, *fOut);
        fCodeProducer.Tab(n+2);
        generateComputeBlock(&fCodeProducer);
        ForLoopInst* loop = fCurLoop->generateScalarLoop(counter);
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
    int n = 0;

    // Initialize "fSamplingFreq" with the "samplingFreq" parameter of the init function
    // Generates fSamplingFreq field and initialize it with the "samplingFreq" parameter of the init function
    pushDeclare(InstBuilder::genDecStructVar("fSamplingFreq", InstBuilder::genBasicTyped(Typed::kInt32)));
    pushFrontInitMethod(InstBuilder::genStoreStructVar("fSamplingFreq", InstBuilder::genLoadFunArgsVar("samplingFreq")));

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
    fCodeProducer.Tab(n);
    generateGlobalDeclarations(&fCodeProducer);

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
        DSPOpenCLInstVisitor dsp_visitor(fGPUOut, n+1);
        fDeclarationInstructions->accept(&dsp_visitor);
    tab1(n, *fGPUOut); *fGPUOut << "} faustdsp;";
    tab1(n, *fGPUOut);

    tab1(n, *fGPUOut); *fGPUOut << "typedef struct {";
        ControlOpenCLInstVisitor control_visitor(fGPUOut, n+1);
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
    tab(n, *fOut); *fOut << dynamic_cast<ostringstream*>(fGPUOut)->str();

    tab(n, *fOut);
    tab(n, *fOut); *fOut << "class " << fKlassName << " : public " << fSuperKlassName << " {";

        tab(n+1, *fOut);
        if (gGlobal->gUIMacroSwitch) {
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
            tab(n+1, *fOut); *fOut << "faustcontrol* fHostControl;";
            tab(n+1, *fOut); *fOut << "cl_mem fDeviceDSP;";
            tab(n+1, *fOut); *fOut << "cl_mem fDeviceControl;";
        }

        tab(n+1, *fOut); *fOut << "cl_device_id fDeviceID;";
        tab(n+1, *fOut); *fOut << "cl_context fContext;";
        tab(n+1, *fOut); *fOut << "cl_command_queue fCommands;";
        tab(n+1, *fOut); *fOut << "cl_program fProgram;";
        tab(n+1, *fOut); *fOut << "cl_kernel fComputeKernel;";
        tab(n+1, *fOut); *fOut << "cl_kernel fInstanceInitKernel;";
        tab(n+1, *fOut); *fOut << "cl_device_id* fDevicesTable;";
        tab(n+1, *fOut); *fOut << "RunThread* fRunThread;";
        tab(n+1, *fOut); *fOut << "int fCount;";
        if (fNumInputs > 0) {
            tab(n+1, *fOut); *fOut << "float** fHostInputs;";
            tab(n+1, *fOut); *fOut << "cl_mem* fDeviceInputs;";
        }
        if (fNumOutputs > 0) {
            tab(n+1, *fOut); *fOut << "float** fHostOutputs;";
            tab(n+1, *fOut); *fOut << "cl_mem* fDeviceOutputs;";
        }
        tab(n+1, *fOut);

    tab(n, *fOut); *fOut << "  public:";

        // Print metadata declaration
        tab(n+1, *fOut);
        produceMetadata(n+1);

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
                tab(n+3, *fOut); *fOut << "setRealTime();";
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

                if (gGlobal->gVectorSwitch) {
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
                tab(n+3, *fOut); *fOut << "if (getenv(\"OCL_GPU_LOAD\") && strtol(getenv(\"OCL_GPU_LOAD\"), NULL, 10)) {";
                    tab(n+4, *fOut); *fOut << "int val = strtol(getenv(\"OCL_GPU_LOAD\"), NULL, 10);";
                    tab(n+4, *fOut); *fOut << "int gpu_load = 100 * executionTime(dsp_execution) * double(dsp->fSamplingFreq) / (double(dsp->fCount) * 1000);";
                    tab(n+4, *fOut); *fOut << "if (gpu_load > val) {";
                        tab(n+5, *fOut); *fOut << "cout << \"Execution time = \" <<  gpu_load << \"%\" << endl;";
                    tab(n+4, *fOut); *fOut << "}" << endl;
                tab(n+3, *fOut); *fOut << "}" << endl;

            tab(n+2, *fOut); *fOut << "}";
            tab(n+2, *fOut); *fOut << "return NULL;";
        tab(n+1, *fOut); *fOut << "}" << endl;


        tab(n+1, *fOut); *fOut << fKlassName << "() {";
            tab(n+2, *fOut); *fOut << "int err;";
            tab(n+2, *fOut); *fOut << "int gpu = (getenv(\"OCL_GPU\") ? strtol(getenv(\"OCL_GPU\"), NULL, 10) : 0);";
            tab(n+2, *fOut); *fOut << "cl_uint num_devices;";
            tab(n+2, *fOut); *fOut << "char* program_src;";

            if (fNumInputs > 0) {
                tab(n+2, *fOut); *fOut << "fDeviceInputs = new cl_mem["<< fNumInputs << "];";
                tab(n+2, *fOut); *fOut << "fHostInputs = new float*["<< fNumInputs << "];";
            }
            if (fNumOutputs > 0) {
                tab(n+2, *fOut); *fOut << "fDeviceOutputs = new cl_mem["<< fNumOutputs << "];";
                tab(n+2, *fOut); *fOut << "fHostOutputs = new float*["<< fNumOutputs << "];";
            }

            // Creates device
            tab(n+2, *fOut); *fOut << "err = clGetDeviceIDs(NULL, gpu ? CL_DEVICE_TYPE_GPU : CL_DEVICE_TYPE_CPU, 0, NULL, &num_devices);";
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot count GPU devices err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";

            tab(n+2, *fOut); *fOut << "if (num_devices == 0) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"There is no GPU devices\"<< endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";

            tab(n+2, *fOut); *fOut << "fDevicesTable = new cl_device_id[num_devices];";

            tab(n+2, *fOut); *fOut << "err = clGetDeviceIDs(NULL, gpu ? CL_DEVICE_TYPE_GPU : CL_DEVICE_TYPE_CPU, num_devices, fDevicesTable, NULL);";
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot get CPU devices err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";

            tab(n+2, *fOut); *fOut << "fDeviceID = fDevicesTable[(getenv(\"OCL_GPU_DEVICE\") ? strtol(getenv(\"OCL_GPU_DEVICE\"), NULL, 10) : 0)];";

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

            // Create the instanceInit kernel
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
                    tab(n+3, *fOut); *fOut << subst("fHostInputs[i] = new $0[sizeof($0) * 8192];", xfloat());
                    tab(n+3, *fOut); *fOut << subst("fDeviceInputs[i] = clCreateBuffer(fContext, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof($0) * 8192, fHostInputs[i], &err);", xfloat());
                    tab(n+3, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                        tab(n+4, *fOut); *fOut << "std::cerr << \"Cannot allocate input buffer err = \" << err << endl;";
                        tab(n+4, *fOut); *fOut << "goto error;";
                    tab(n+3, *fOut); *fOut << "}";
                tab(n+2, *fOut); *fOut << "}";
            }

            // Allocate kernel output buffers (shared between CPU and GPU)
            if (fNumOutputs > 0) {
                tab(n+2, *fOut); *fOut << "for (int i = 0; i < " << fNumOutputs << "; i++) {";
                    tab(n+3, *fOut); *fOut << subst("fHostOutputs[i] = new $0[sizeof($0) * 8192];", xfloat());
                    tab(n+3, *fOut); *fOut << subst("fDeviceOutputs[i] = clCreateBuffer(fContext, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, sizeof($0) * 8192, fHostOutputs[i], &err);", xfloat());

                    tab(n+3, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                        tab(n+4, *fOut); *fOut << "std::cerr << \"Cannot allocate output buffer err = \" << err << endl;";
                        tab(n+4, *fOut); *fOut << "goto error;";
                    tab(n+3, *fOut); *fOut << "}";
                tab(n+2, *fOut); *fOut << "}";
            }

            // Allocate control on CPU, map it on GPU
             tab(n+2, *fOut); *fOut << "fHostControl = (faustcontrol*)calloc(1, sizeof(faustcontrol));";
            tab(n+2, *fOut); *fOut << "if (fHostControl == NULL) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot allocate control err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";

            tab(n+2, *fOut); *fOut << "fDeviceControl = clCreateBuffer(fContext, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, sizeof(faustcontrol), fHostControl, &err);";
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot map control err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";

            // Allocate DSP on GPU
            tab(n+2, *fOut); *fOut << "fDeviceDSP = clCreateBuffer(fContext, CL_MEM_READ_WRITE, sizeof(faustdsp), NULL, &err);";
            tab(n+2, *fOut); *fOut << "if (err != CL_SUCCESS) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot allocate DSP err = \" << err << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";

            // Pass parameters that do not change between kernel invocations
            tab(n+2, *fOut); *fOut << "err = 0;" << endl;
            if (fNumInputs > 0) {
                tab(n+2, *fOut); *fOut << "for (int i = 0; i < " << fNumInputs << "; i++) {";
                    tab(n+3, *fOut); *fOut << "err |= clSetKernelArg(fComputeKernel, i+1, sizeof(cl_mem), &fDeviceInputs[i]);";
                tab(n+2, *fOut); *fOut << "}";
            }
            if (fNumOutputs > 0) {
                tab(n+2, *fOut); *fOut << "for (int i = 0; i < " << fNumOutputs << "; i++) {";
                    tab(n+3, *fOut); *fOut << "err |= clSetKernelArg(fComputeKernel, " << fNumInputs << "+i+1, sizeof(cl_mem), &fDeviceOutputs[i]);";
                tab(n+2, *fOut); *fOut << "}";
            }

            tab(n+2, *fOut); *fOut << "err |= clSetKernelArg(fComputeKernel, " << (fNumInputs + fNumOutputs) << "+1, sizeof(cl_mem), &fDeviceDSP);";
            tab(n+2, *fOut); *fOut << "err |= clSetKernelArg(fComputeKernel, " << (fNumInputs + fNumOutputs) << "+2, sizeof(cl_mem), &fDeviceControl);";

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
                    tab(n+3, *fOut); *fOut << "clReleaseMemObject(fDeviceInputs[i]);";
                    tab(n+3, *fOut); *fOut << "delete[] fHostInputs[i];";
                tab(n+2, *fOut); *fOut << "}";
            }

            // Free kernel output buffers
            if (fNumOutputs > 0) {
                tab(n+2, *fOut); *fOut << "for (int i = 0; i < " << fNumOutputs << "; i++) {";
                    tab(n+3, *fOut); *fOut << "clReleaseMemObject(fDeviceOutputs[i]);";
                    tab(n+3, *fOut); *fOut << "delete[] fHostOutputs[i];";
                tab(n+2, *fOut); *fOut << "}";
            }

            if (fNumInputs > 0) {
                tab(n+2, *fOut); *fOut << "delete[] fDeviceInputs;";
                tab(n+2, *fOut); *fOut << "delete[] fHostInputs;";
            }
            if (fNumOutputs > 0) {
                tab(n+2, *fOut); *fOut << "delete[] fDeviceOutputs;";
                tab(n+2, *fOut); *fOut << "delete[] fHostOutputs;";
            }

            // Shutdown and cleanup
            tab(n+2, *fOut); *fOut << "free(fHostControl);";
            tab(n+2, *fOut); *fOut << "clReleaseMemObject(fDeviceControl);";
            tab(n+2, *fOut); *fOut << "clReleaseMemObject(fDeviceDSP);";
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

        // TO CHECK
        produceInfoFunctions(n+1, fKlassName, "dsp", false, true, &fCodeProducer);

        // Inits
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "static void classInit(int samplingFreq) {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateStaticInit(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";

        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "virtual void instanceInit(int samplingFreq) {";
            if (fInitInstructions->fCode.size() > 0) {

                tab(n+2, *fOut); *fOut << "fSamplingFreq = samplingFreq;";

                tab(n+2, *fOut); *fOut << "int err = 0;";
                tab(n+2, *fOut); *fOut << "err |= clSetKernelArg(fInstanceInitKernel, 0, sizeof(cl_mem), &fDeviceDSP);";
                tab(n+2, *fOut); *fOut << "err |= clSetKernelArg(fInstanceInitKernel, 1, sizeof(cl_mem), &fDeviceControl);";
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
        produceInit(n+1);

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
        generateComputeFunctions(&fCodeProducer);

    tab(n, *fOut); *fOut << "};" << endl;

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

void CPPOpenCLCodeContainer::generateCompute(int n)
{
    // Generates declaration
    tab(n+1, *fOut);
    tab(n+1, *fOut); *fOut << subst("virtual void compute(int count, $0** inputs, $0** outputs) {", xfloat());
    fCodeProducer.Tab(n+2);

    tab(n+2, *fOut); *fOut << "fCount = count;";
    tab(n+2, *fOut); *fOut << "getRealTime();";

    // Copy audio input buffer to temp buffers
    if (fNumInputs > 0) {
        tab(n+2, *fOut); *fOut << "for (int i = 0; i < " << fNumInputs << "; i++) {";
            tab(n+3, *fOut); *fOut << subst("memcpy(fHostInputs[i], inputs[i], sizeof($0) * count);", xfloat());
        tab(n+2, *fOut); *fOut << "}";
        tab(n+2, *fOut);
    }

    // Copy temp buffers to audio output buffers
    if (fNumOutputs > 0) {
        tab(n+2, *fOut); *fOut << "for (int i = 0; i < " << fNumOutputs << "; i++) {";
            tab(n+3, *fOut); *fOut << subst("memcpy(outputs[i], fHostOutputs[i], sizeof($0) * count);", xfloat());
        tab(n+2, *fOut); *fOut << "}";
        tab(n+2, *fOut);
    }
    tab(n+2, *fOut); *fOut << "fRunThread->Signal();";
    tab(n+1, *fOut); *fOut << "}";
}

void CPPOpenCLCodeContainer::generateComputeKernel(int n)
{
    // Generate compute kernel
    string counter = "count";
    tab1(n, *fGPUOut);
    *fGPUOut << subst("__kernel void computeKernel(int $0, ", counter);

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
    generateComputeBlock(fKernelCodeProducer);

    // Generates one single scalar loop
    ForLoopInst* loop = fCurLoop->generateScalarLoop(counter);
    loop->accept(fKernelCodeProducer);

    tab1(n, *fGPUOut);

    *fGPUOut << "}";
    tab1(n, *fGPUOut);
}

void CPPOpenCLVectorCodeContainer::generateComputeKernel(int n)
{
    // Generate compute kernel
    string counter = "fullcount";
    string index = "index";

    tab1(n, *fGPUOut);
    *fGPUOut << subst("__kernel void computeKernel(const int $0, ", counter);

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
    vector<int> ready_loop;
    int loop_count;
    CodeLoop::sortGraph(fCurLoop, dag);
    computeForwardDAG(dag, loop_count, ready_loop);

    BlockInst* loop_code = InstBuilder::genBlockInst();

    // Generate local input/output access
    //generateLocalInputs(loop_code);
    //generateLocalOutputs(loop_code);

    // Generate : int count = min(32, (fullcount - index))
    ValueInst* init1 = InstBuilder::genLoadFunArgsVar(counter);
    ValueInst* init2 = InstBuilder::genSub(init1, InstBuilder::genLoadLoopVar(index));
    list<ValueInst*> min_fun_args;
    min_fun_args.push_back(InstBuilder::genInt32NumInst(gGlobal->gVecSize));
    min_fun_args.push_back(init2);
    ValueInst* init3 = InstBuilder::genFunCallInst("min", min_fun_args);
    DeclareVarInst* count_dec = InstBuilder::genDecStackVar("count", InstBuilder::genBasicTyped(Typed::kInt32), init3);
    loop_code->pushBackInst(count_dec);

    // Generates get_global_id access
    list<ValueInst*> args;
    args.push_back(InstBuilder::genInt32NumInst(0));
    loop_code->pushBackInst(InstBuilder::genDecStackVar("tasknum", InstBuilder::genBasicTyped(Typed::kInt32), InstBuilder::genFunCallInst("get_global_id", args)));

    // Generate DAG
    for (int l = dag.size() - 1; l >= 0; l--) {

        ValueInst* switch_cond = InstBuilder::genLoadStackVar("tasknum");
        ::SwitchInst* switch_block = InstBuilder::genSwitchInst(switch_cond);

        if (dag[l].size() > 1) {
            int loop_num = 0;
            for (lclset::const_iterator p = dag[l].begin(); p != dag[l].end(); p++) {
                BlockInst* switch_case_block = InstBuilder::genBlockInst();
                generateDAGLoopAux(*p, switch_case_block, count_dec, loop_num);
                switch_block->addCase(loop_num, switch_case_block);
                loop_num++;
            }
        } else {
            BlockInst* single_case_block = InstBuilder::genBlockInst();
            generateDAGLoopAux(*dag[l].begin(), single_case_block, count_dec, 0);
            switch_block->addCase(0, single_case_block);
        }

        loop_code->pushBackInst(switch_block);
        loop_code->pushBackInst(InstBuilder::genLabelInst("barrier(CLK_LOCAL_MEM_FENCE);"));
    }

    // Generates the DAG enclosing loop
    DeclareVarInst* loop_init = InstBuilder::genDecLoopVar(index, InstBuilder::genBasicTyped(Typed::kInt32), InstBuilder::genInt32NumInst(0));
    ValueInst* loop_end = InstBuilder::genLessThan(loop_init->load(), InstBuilder::genLoadFunArgsVar(counter));
    StoreVarInst* loop_increment = loop_init->store(InstBuilder::genAdd(loop_init->load(), gGlobal->gVecSize));

    StatementInst* loop = InstBuilder::genForLoopInst(loop_init, loop_end, loop_increment, loop_code);

    // Generates the final loop
    loop->accept(fKernelCodeProducer);

    tab1(n, *fGPUOut);
    *fGPUOut << "}";
    tab1(n, *fGPUOut);
}

void CPPCUDACodeContainer::produceInternal()
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
        // TO CHECK
        produceInfoFunctions(n+1, fKlassName, "dsp", false, false, &fCodeProducer);

        // Inits
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "void instanceInit" << fKlassName << "(int samplingFreq) {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateInit(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";

        // Fill
        string counter = "count";
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "void fill" << fKlassName << subst("(int $0, $1* output) {", counter, ifloat());
        tab(n+2, *fOut);
        fCodeProducer.Tab(n+2);
        generateComputeBlock(&fCodeProducer);
        ForLoopInst* loop = fCurLoop->generateScalarLoop(counter);
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

void CPPCUDACodeContainer::generateInstanceInitKernelGlue(int n)
{
    tab(n, *fGPUOut); *fGPUOut << "void instanceInitKernelGlue(faustdsp* dsp, faustcontrol* control, int samplingFreq) {";
        tab(n+1, *fGPUOut); *fGPUOut << "dim3 block(1);";
        tab(n+1, *fGPUOut); *fGPUOut << "dim3 grid(1);";
        tab(n+1, *fGPUOut); *fGPUOut << "instanceInitKernel<<<grid, block>>>(dsp, control, samplingFreq);";
    tab(n, *fGPUOut); *fGPUOut << "}";
}

void CPPCUDACodeContainer::generateComputeKernelGlue(int n)
{
    *fGPUOut << "void computeKernelGlue(int count, ";

    for (int i = 0; i < fNumInputs; i++) {
        *fGPUOut <<  " float* input" << i << ", ";
    }

    for (int i = 0; i < fNumOutputs; i++) {
        if (i == fNumOutputs - 1) {
            *fGPUOut << "float* output" << i;
        } else {
            *fGPUOut << "float* output" << i << ", ";
        }
    }

    *fGPUOut << ", faustdsp* dsp, faustcontrol* control) {";

        tab(n+1, *fGPUOut); *fGPUOut << "dim3 block(1);";
        tab(n+1, *fGPUOut); *fGPUOut << "dim3 grid(1);";
        tab(n+1, *fGPUOut); *fGPUOut << "computeKernel<<<grid, block>>>(count, ";

        for (int i = 0; i < fNumInputs; i++) {
            *fGPUOut <<  "input" << i << ", ";
        }

        for (int i = 0; i < fNumOutputs; i++) {
            if (i == fNumOutputs - 1) {
                *fGPUOut << "output" << i;
            } else {
                *fGPUOut << "output" << i << ", ";
            }
        }

        *fGPUOut << ", dsp, control);";

    tab(n, *fGPUOut); *fGPUOut << "}";
}

void CPPCUDACodeContainer::produceClass()
{
    int n = 0;

    // Initialize "fSamplingFreq" with the "samplingFreq" parameter of the init function
    // Generates fSamplingFreq field and initialize it with the "samplingFreq" parameter of the init function
    pushDeclare(InstBuilder::genDecStructVar("fSamplingFreq", InstBuilder::genBasicTyped(Typed::kInt32)));
    pushFrontInitMethod(InstBuilder::genStoreStructVar("fSamplingFreq", InstBuilder::genLoadFunArgsVar("samplingFreq")));

    addIncludeFile("<iostream>");
    addIncludeFile("<fstream>");
    addIncludeFile("<cuda.h>");
    addIncludeFile("<cuda_runtime.h>");

    // Libraries
    printLibrary(*fOut);
    printIncludeFile(*fOut);

    // Sub containers
    generateSubContainers();

    // Functions
    tab(n, *fOut);
    fCodeProducer.Tab(n);
    generateGlobalDeclarations(&fCodeProducer);

    // Macro definition
    tab(n, *fGPUOut); *fGPUOut << "#define max(x,y) (((x)>(y)) ? (x) : (y))";
    tab(n, *fGPUOut); *fGPUOut << "#define min(x,y) (((x)<(y)) ? (x) : (y))";
    tab(n, *fGPUOut); *fGPUOut << "#ifndef " << FLOATMACRO;
    tab(n, *fGPUOut); *fGPUOut << "#define " << FLOATMACRO << " " << "float";
    tab(n, *fGPUOut); *fGPUOut << "#endif  ";

     // Separate control and non-controls fields in 2 separeted structures
    tab(n, *fGPUOut);
    tab(n, *fGPUOut); *fGPUOut << "typedef struct {";
        DSPInstVisitor dsp_visitor(fGPUOut, n+1);
        fDeclarationInstructions->accept(&dsp_visitor);
    tab(n, *fGPUOut); *fGPUOut << "} faustdsp;";
    tab(n, *fGPUOut);

    tab(n, *fGPUOut); *fGPUOut << "typedef struct {";
        ControlInstVisitor control_visitor(fGPUOut, n+1);
        fDeclarationInstructions->accept(&control_visitor);
    tab(n, *fGPUOut); *fGPUOut << "} faustcontrol;";
    tab(n, *fGPUOut);
    tab(n, *fGPUOut);

    // Generate instanceInit kernel
    if (fInitInstructions->fCode.size() > 0) {
        *fGPUOut << "__global__ void instanceInitKernel(faustdsp* dsp, faustcontrol* control, int samplingFreq) {";
        tab(n+1, *fGPUOut);
        fKernelCodeProducer->Tab(n+1);
        fInitInstructions->accept(fKernelCodeProducer);
        tab(n, *fGPUOut);
        *fGPUOut << "}";
    }

    // Generate compute kernel
    generateComputeKernel(n);

    // Generate glue functions
    generateInstanceInitKernelGlue(n);
    tab(n, *fGPUOut);
    generateComputeKernelGlue(n);

    // Generates CUDA code as a file
    fGPUOut->flush();

    // Separate control and non-controls fields in 2 structures
    tab(n, *fOut); *fOut << "typedef struct {";
        DSPInstVisitor dsp_visitor1(fOut, n+1);
        fDeclarationInstructions->accept(&dsp_visitor1);
    tab(n, *fOut); *fOut << "} faustdsp;";
    tab(n, *fOut);

    tab(n, *fOut); *fOut << "typedef struct {";
        ControlInstVisitor control_visitor1(fOut, n+1);
        fDeclarationInstructions->accept(&control_visitor1);
    tab(n, *fOut); *fOut << "} faustcontrol;";
    tab(n, *fOut);

    // CUDA kernel prototypes
    tab(n, *fOut); *fOut << "void instanceInitKernelGlue(faustdsp* dsp, faustcontrol* control, int samplingFreq);";

    tab(n, *fOut);
    *fOut << "void computeKernelGlue(int count, ";

    for (int i = 0; i < fNumInputs; i++) {
        *fOut <<  " float* input" << i << ", ";
    }

    for (int i = 0; i < fNumOutputs; i++) {
        if (i == fNumOutputs - 1) {
            *fOut << "float* output" << i;
        } else {
            *fOut << "float* output" << i << ", ";
        }
    }

    *fOut << ", faustdsp* dsp, faustcontrol* control);";

    tab(n, *fOut);
    tab(n, *fOut); *fOut << "class " << fKlassName << " : public " << fSuperKlassName << " {";

        tab(n+1, *fOut);

        if (gGlobal->gUIMacroSwitch) {
            tab(n, *fOut); *fOut << "  public:";
        } else {
            tab(n, *fOut); *fOut << "  private:";
        }

        if (fDeclarationInstructions->fCode.size() > 0) {
            fCodeProducer.Tab(n+1);

            tab(n+1, *fOut);
            tab(n+1, *fOut); *fOut << "faustdsp* fDeviceDSP;";
            tab(n+1, *fOut); *fOut << "faustcontrol* fHostControl;";
            tab(n+1, *fOut); *fOut << "faustcontrol* fDeviceControl;";
        }

        tab(n+1, *fOut); *fOut << "int fDeviceID;";
        tab(n+1, *fOut); *fOut << "volatile bool fDeviceRunning;";

        tab(n+1, *fOut); *fOut << "int fDeviceCount;";
        tab(n+1, *fOut); *fOut << "RunThread* fRunThread;";
        tab(n+1, *fOut); *fOut << "int fCount;";
        if (fNumInputs > 0) {
            tab(n+1, *fOut); *fOut << "float** fDeviceInputs;";
            tab(n+1, *fOut); *fOut << "float** fHostInputs;";
        }
        if (fNumOutputs > 0) {
            tab(n+1, *fOut); *fOut << "float** fDeviceOutputs;";
            tab(n+1, *fOut); *fOut << "float** fHostOutputs;";
        }

    tab(n, *fOut);
    tab(n, *fOut); *fOut << "  public:";

        // Print metadata declaration
        tab(n+1, *fOut);
        produceMetadata(n+1);

        tab(n+1, *fOut); *fOut << "static void* RunHandler(void* arg) {";
            tab(n+2, *fOut); *fOut << "mydsp* dsp = static_cast<mydsp*>(arg);";
            tab(n+2, *fOut); *fOut << "cudaError_t cudaResult;";

            tab(n+2, *fOut); *fOut << "cudaResult = cudaSetDeviceFlags(cudaDeviceMapHost);";
            tab(n+2, *fOut); *fOut << "if (cudaResult != cudaSuccess) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot set device properties cudaDeviceMapHost err = \" << cudaResult << endl;";
            tab(n+2, *fOut); *fOut << "}";


            tab(n+2, *fOut); *fOut << "if (!dsp->allocateCUDA())";
                tab(n+3, *fOut); *fOut << "return NULL;";


            tab(n+2, *fOut); *fOut << "if (dsp->fRunThread->fRealTime) {";
                tab(n+3, *fOut); *fOut << "dsp->fRunThread->Wait();";
                tab(n+3, *fOut); *fOut << "setRealTime();";
            tab(n+2, *fOut); *fOut << "}";

            tab(n+2, *fOut); *fOut << "while (dsp->fDeviceRunning) {";

                tab(n+3, *fOut); *fOut << "computeKernelGlue(dsp->fCount, ";
                if (fNumInputs > 0) {
                    for (int i = 0; i < fNumInputs; i++) {
                       *fOut << "dsp->fDeviceInputs[" << i << "], ";
                    }
                }
                if (fNumOutputs > 0) {
                    for (int i = 0; i < fNumOutputs; i++) {
                        if (i == fNumOutputs - 1)
                            *fOut << "dsp->fDeviceOutputs[" << i << "]";
                        else
                            *fOut << "dsp->fDeviceOutputs[" << i << "], ";
                    }
                }
                *fOut << ", dsp->fDeviceDSP, dsp->fDeviceControl);";

                // Wait for computation end
                tab(n+3, *fOut); *fOut << "cudaThreadSynchronize();";
                tab(n+3, *fOut); *fOut << "dsp->fRunThread->Wait();";
                /*
                tab(n+3, *fOut); *fOut << "if (getenv(\"OCL_GPU_LOAD\") && strtol(getenv(\"OCL_GPU_LOAD\"), NULL, 10)) {";
                    tab(n+4, *fOut); *fOut << "cout << \"Execution time = \" << 100 * executionTime(dsp_execution) * double(dsp->fSamplingFreq) / (double(dsp->fCount) * 1000) << \"%\" << endl;";
                tab(n+3, *fOut); *fOut << "}" << endl;
                */

            tab(n+2, *fOut); *fOut << "}";
            tab(n+2, *fOut); *fOut << "dsp->destroyCUDA();";
            tab(n+2, *fOut); *fOut << "return NULL;";
        tab(n+1, *fOut); *fOut << "}" << endl;

        tab(n+1, *fOut); *fOut << fKlassName << "() {";
            tab(n+2, *fOut); *fOut << "cudaError_t cudaResult;";

            if (fNumInputs > 0) {
                tab(n+2, *fOut); *fOut << "fHostInputs = new float*["<< fNumInputs << "];";
                tab(n+2, *fOut); *fOut << "fDeviceInputs = new float*["<< fNumInputs << "];";
            }
            if (fNumOutputs > 0) {
                tab(n+2, *fOut); *fOut << "fHostOutputs = new float*["<< fNumOutputs << "];";
                tab(n+2, *fOut); *fOut << "fDeviceOutputs = new float*["<< fNumOutputs << "];";
            }
            tab(n+2, *fOut); *fOut << "fHostControl = NULL;";

            // Creates device
            tab(n+2, *fOut); *fOut << "cudaResult = cudaGetDeviceCount(&fDeviceCount);";
            tab(n+2, *fOut); *fOut << "if (cudaResult != cudaSuccess) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot count GPU devices err = \" << cudaResult << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";

            tab(n+2, *fOut); *fOut << "if (fDeviceCount == 0) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"There is no GPU devices\"<< endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";

            /*
            tab(n+2, *fOut); *fOut << "if (!allocateCUDA())";
                tab(n+3, *fOut); *fOut << "goto error;";
            */

            // Allocate thread
            tab(n+2, *fOut); *fOut << "fRunThread = new RunThread();";
            tab(n+2, *fOut); *fOut << "if (fRunThread->Start(true, RunHandler, this) != 0) {";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";

            tab(n+2, *fOut); *fOut << "while(!fDeviceRunning) { usleep(100); }";

            tab(n+2, *fOut); *fOut << "return;" << endl;

        tab(n+1, *fOut); *fOut << "error:";
            tab(n+2, *fOut); *fOut << "throw std::bad_alloc();";
        tab(n+1, *fOut); *fOut << "}" << endl;

        tab(n+1, *fOut); *fOut << "virtual ~" << fKlassName << "() {";
            tab(n+2, *fOut); *fOut << "fDeviceRunning = false; ";
            //tab(n+2, *fOut); *fOut << "fRunThread->Stop();";

            tab(n+2, *fOut); *fOut << "fRunThread->Join();";
            //tab(n+2, *fOut); *fOut << "destroyCUDA();";
            tab(n+2, *fOut); *fOut << "delete fRunThread;";
            tab(n+2, *fOut); *fOut << "destroy();";

        tab(n+1, *fOut); *fOut << "}" << endl;

        tab(n+1, *fOut); *fOut << "bool allocateCUDA() {";

            tab(n+2, *fOut); *fOut << "cudaError_t cudaResult;";
            tab(n+2, *fOut); *fOut << "fDeviceID = 1;";
            tab(n+2, *fOut); *fOut << "cudaResult = cudaSetDevice(fDeviceID);";
            tab(n+2, *fOut); *fOut << "if (cudaResult != cudaSuccess) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot set GPU device err = \" << cudaResult << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";

            // Print device name
            tab(n+2, *fOut); *fOut << "cudaDeviceProp deviceProp;";
            tab(n+2, *fOut); *fOut << "cudaResult = cudaGetDeviceProperties(&deviceProp, fDeviceID);";
            tab(n+2, *fOut); *fOut << "if (cudaResult != cudaSuccess) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot get device properties err = \" << cudaResult << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";

            tab(n+2, *fOut); *fOut << "std::cerr << \"Device name: \" << deviceProp.name << endl;";

             tab(n+2, *fOut); *fOut << "if (!deviceProp.canMapHostMemory) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Device cannot map host memory \" << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";

            tab(n+2, *fOut); *fOut << "cudaResult = cudaSetDeviceFlags(cudaDeviceMapHost);";
            tab(n+2, *fOut); *fOut << "if (cudaResult != cudaSuccess) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot set device properties cudaDeviceMapHost err = \" << cudaResult << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";

           // Allocate kernel input buffers (shared between CPU and GPU)
            if (fNumInputs > 0) {
                tab(n+2, *fOut); *fOut << "for (int i = 0; i < " << fNumInputs << "; i++) {";
                    tab(n+3, *fOut); *fOut << subst("cudaResult = cudaHostAlloc((void **)&fHostInputs[i], sizeof($0) * 8192, cudaHostAllocMapped|cudaHostAllocPortable);", xfloat());
                    tab(n+3, *fOut); *fOut << "if (cudaResult != cudaSuccess) {";
                        tab(n+4, *fOut); *fOut << "std::cerr << \"Cannot allocate input buffer err = \" << cudaResult << endl;";
                        tab(n+4, *fOut); *fOut << "goto error;";
                    tab(n+3, *fOut); *fOut << "}";
                    tab(n+3, *fOut); *fOut << "cudaResult = cudaHostGetDevicePointer((void **)&fDeviceInputs[i], (void *)fHostInputs[i], 0);";
                    tab(n+3, *fOut); *fOut << "if (cudaResult != cudaSuccess) {";
                        tab(n+4, *fOut); *fOut << "std::cerr << \"Cannot map input buffer err = \" << cudaResult << endl;";
                        tab(n+4, *fOut); *fOut << "goto error;";
                    tab(n+3, *fOut); *fOut << "}";
                tab(n+2, *fOut); *fOut << "}";
            }

            // Allocate kernel output buffers (shared between CPU and GPU)
            if (fNumOutputs > 0) {
                tab(n+2, *fOut); *fOut << "for (int i = 0; i < " << fNumOutputs << "; i++) {";
                    tab(n+3, *fOut); *fOut << subst("cudaResult = cudaHostAlloc((void **)&fHostOutputs[i], sizeof($0) * 8192, cudaHostAllocMapped|cudaHostAllocPortable);", xfloat());
                    tab(n+3, *fOut); *fOut << "if (cudaResult != cudaSuccess) {";
                        tab(n+4, *fOut); *fOut << "std::cerr << \"Cannot allocate output buffer err = \" << cudaResult << endl;";
                        tab(n+4, *fOut); *fOut << "goto error;";
                    tab(n+3, *fOut); *fOut << "}";
                    tab(n+3, *fOut); *fOut << "cudaResult = cudaHostGetDevicePointer((void **)&fDeviceOutputs[i], (void *)fHostOutputs[i], 0);";
                    tab(n+3, *fOut); *fOut << "if (cudaResult != cudaSuccess) {";
                        tab(n+4, *fOut); *fOut << "std::cerr << \"Cannot map output buffer err = \" << cudaResult << endl;";
                        tab(n+4, *fOut); *fOut << "goto error;";
                    tab(n+3, *fOut); *fOut << "}";
                tab(n+2, *fOut); *fOut << "}";
            }

            // Allocate control on CPU, map it on GPU
            tab(n+2, *fOut); *fOut << "cudaResult = cudaHostAlloc((void **)&fHostControl, sizeof(faustcontrol), cudaHostAllocMapped);";
            tab(n+2, *fOut); *fOut << "if (cudaResult != cudaSuccess) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot allocate control err = \" << cudaResult << endl;";
                tab(n+3, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";

            tab(n+2, *fOut); *fOut << "cudaResult = cudaHostGetDevicePointer((void **)&fDeviceControl, (void *)fHostControl, 0);";
            tab(n+2, *fOut); *fOut << "if (cudaResult != cudaSuccess) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot map control err = \" << cudaResult << endl;";
                tab(n+4, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";

            // Allocate DSP on GPU
            tab(n+2, *fOut); *fOut << "cudaResult = cudaMalloc((void **)&fDeviceDSP, sizeof(faustdsp));";
            tab(n+2, *fOut); *fOut << "if (cudaResult != cudaResult) {";
                tab(n+3, *fOut); *fOut << "std::cerr << \"Cannot allocate DSP err = \" << cudaResult << endl;";
                tab(n+4, *fOut); *fOut << "goto error;";
            tab(n+2, *fOut); *fOut << "}";

            tab(n+2, *fOut); *fOut << "fDeviceRunning = true;";
            tab(n+2, *fOut); *fOut << "return true;";

        tab(n+1, *fOut); *fOut << "error:";
            tab(n+2, *fOut); *fOut << "return false;";

         tab(n+1, *fOut); *fOut << "}";

         tab(n+1, *fOut); *fOut << "void destroyCUDA() {";

            // Free kernel input buffers
            if (fNumInputs > 0) {
                tab(n+2, *fOut); *fOut << "for (int i = 0; i < " << fNumInputs << "; i++) {";
                    tab(n+3, *fOut); *fOut << "cudaFreeHost(fHostInputs[i]);";
                tab(n+2, *fOut); *fOut << "}";
            }

            // Free kernel output buffers
            if (fNumOutputs > 0) {
                tab(n+2, *fOut); *fOut << "for (int i = 0; i < " << fNumOutputs << "; i++) {";
                    tab(n+3, *fOut); *fOut << "cudaFreeHost(fHostOutputs[i]);";
                tab(n+2, *fOut); *fOut << "}";
            }

            if (fNumInputs > 0) {
                tab(n+2, *fOut); *fOut << "delete[] fHostInputs;";
                tab(n+2, *fOut); *fOut << "delete[] fDeviceInputs;";
            }
            if (fNumOutputs > 0) {
                tab(n+2, *fOut); *fOut << "delete[] fHostOutputs;";
                tab(n+2, *fOut); *fOut << "delete[] fDeviceOutputs;";
            }
            tab(n+2, *fOut); *fOut << "cudaFreeHost(fDeviceControl);";
            tab(n+2, *fOut); *fOut << "cudaFree(fDeviceDSP);";

            // Shutdown and cleanup
            tab(n+2, *fOut); *fOut << "cudaThreadExit();";

         tab(n+1, *fOut); *fOut << "}";


    tab(n+1, *fOut); *fOut << "void destroy() {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateDestroy(&fCodeProducer);
        tab(n+1, *fOut);  *fOut << "}";
        tab(n+1, *fOut);
    
        // TO CHECK
        produceInfoFunctions(n+1, fKlassName, "dsp", false, true, &fCodeProducer);

        // Inits
        tab(n+1, *fOut); *fOut << "static void classInit(int samplingFreq) {";
            tab(n+2, *fOut);
            fCodeProducer.Tab(n+2);
            generateStaticInit(&fCodeProducer);
        tab(n+1, *fOut); *fOut << "}";

        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "virtual void instanceInit(int samplingFreq) {";
            if (fInitInstructions->fCode.size() > 0) {

                tab(n+2, *fOut); *fOut << "fSamplingFreq = samplingFreq;";
                tab(n+2, *fOut); *fOut << "instanceInitKernelGlue(fDeviceDSP, fDeviceControl, samplingFreq);";

                // Wait for instanceInit end
                tab(n+2, *fOut); *fOut << "cudaThreadSynchronize();";
            }
        tab(n+1, *fOut); *fOut << "}";

        tab(n+1, *fOut);
        produceInit(n+1);

        // User interface
        tab(n+1, *fOut);
        tab(n+1, *fOut); *fOut << "virtual void buildUserInterface(UI* interface) {";
            tab(n+2, *fOut); *fOut << "faustassert(fHostControl);";
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
        generateComputeFunctions(&fCodeProducer);

    tab(n, *fOut); *fOut << "};" << endl;

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

void CPPCUDACodeContainer::generateCompute(int n)
{
    // Generates declaration
    tab(n+1, *fOut);
    tab(n+1, *fOut); *fOut << subst("virtual void compute(int count, $0** inputs, $0** outputs) {", xfloat());
    fCodeProducer.Tab(n+2);

    tab(n+2, *fOut); *fOut << "fCount = count;";
    tab(n+2, *fOut); *fOut << "getRealTime();";

    // Copy audio input buffer to temp buffers
    if (fNumInputs > 0) {
        tab(n+2, *fOut); *fOut << "for (int i = 0; i < " << fNumInputs << "; i++) {";
            tab(n+3, *fOut); *fOut << subst("memcpy(fHostInputs[i], inputs[i], sizeof($0) * count);", xfloat());
        tab(n+2, *fOut); *fOut << "}";
        tab(n+2, *fOut);
    }

    // Copy temp buffers to audio output buffers
    if (fNumOutputs > 0) {
        tab(n+2, *fOut); *fOut << "for (int i = 0; i < " << fNumOutputs << "; i++) {";
            tab(n+3, *fOut); *fOut << subst("memcpy(outputs[i], fHostOutputs[i], sizeof($0) * count);", xfloat());
        tab(n+2, *fOut); *fOut << "}";
        tab(n+2, *fOut);
    }
    tab(n+2, *fOut); *fOut << "fRunThread->Signal();";
    tab(n+1, *fOut); *fOut << "}";
}

void CPPCUDACodeContainer::generateComputeKernel(int n)
{
    // Generate compute kernel
    string counter = "count";
    tab(n, *fGPUOut);
    *fGPUOut << subst("__global__ void computeKernel(int $0, ", counter);

    for (int i = 0; i < fNumInputs; i++) {
        *fGPUOut <<  " float* input" << i << ", ";
    }

    for (int i = 0; i < fNumOutputs; i++) {
        if (i == fNumOutputs - 1) {
            *fGPUOut << "float* output" << i;
        } else {
            *fGPUOut << "float* output" << i << ", ";
        }
    }

    *fGPUOut << ", faustdsp* dsp, faustcontrol* control) {";
    tab(n+1, *fGPUOut);

    // Generates local variables declaration and setup
    generateComputeBlock(fKernelCodeProducer);

    // Generates one single scalar loop
    ForLoopInst* loop = fCurLoop->generateScalarLoop(counter);
    loop->accept(fKernelCodeProducer);

    tab(n, *fGPUOut);
    *fGPUOut << "}";
    tab(n, *fGPUOut);
}

void CPPCUDAVectorCodeContainer::generateComputeKernel(int n)
{
    // Generate compute kernel
    string counter = "fullcount";
    string index = "index";

    tab(n, *fGPUOut);
    *fGPUOut << subst("__global__ void computeKernel(const int $0, ", counter);

    for (int i = 0; i < fNumInputs; i++) {
        *fGPUOut <<  "float* input" << i << ", ";
    }

    for (int i = 0; i < fNumOutputs; i++) {
        if (i == fNumOutputs - 1) {
            *fGPUOut << "float* output" << i;
        } else {
            *fGPUOut << "float* output" << i << ", ";
        }
    }

    *fGPUOut << ", faustdsp* dsp, faustcontrol* control) {";
    tab(n+1, *fGPUOut);

    // Generates local variables declaration and setup
    BlockKernelInstVisitor block_visitor(fGPUOut, n+1);
    fComputeBlockInstructions->accept(&block_visitor);
  
    lclgraph dag;
    vector<int> ready_loop;
    int loop_count;
    CodeLoop::sortGraph(fCurLoop, dag);
    computeForwardDAG(dag, loop_count, ready_loop);

    BlockInst* loop_code = InstBuilder::genBlockInst();

    // Generate local input/output access
    //generateLocalInputs(loop_code);
    //generateLocalOutputs(loop_code);

    // Generate : int count = min(32, (fullcount - index))
    ValueInst* init1 = InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(counter, Address::kFunArgs));
    ValueInst* init2 = InstBuilder::genSub(init1, InstBuilder::genLoadLoopVar(index));
    list<ValueInst*> min_fun_args;
    min_fun_args.push_back(InstBuilder::genInt32NumInst(gGlobal->gVecSize));
    min_fun_args.push_back(init2);
    ValueInst* init3 = InstBuilder::genFunCallInst("min", min_fun_args);
    DeclareVarInst* count_dec = InstBuilder::genDecStackVar("count", InstBuilder::genBasicTyped(Typed::kInt32), init3);
    loop_code->pushBackInst(count_dec);

    // Generates get_global_id access
    list<ValueInst*> args;
    args.push_back(InstBuilder::genInt32NumInst(0));

    /*
    loop_code->pushBackInst(InstBuilder::genDeclareVarInst("tasknum",
        InstBuilder::genBasicTyped(Typed::kInt32), Address::kStack,
        InstBuilder::genFunCallInst("get_global_id", args)));
    */

    loop_code->pushBackInst(InstBuilder::genLabelInst("int tasknum = blockDim.x * blockIdx.x + threadIdx.x;"));

    // Generate DAG
    for (int l = dag.size() - 1; l >= 0; l--) {

        ValueInst* switch_cond = InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress("tasknum", Address::kStack));
        ::SwitchInst* switch_block = InstBuilder::genSwitchInst(switch_cond);

        if (dag[l].size() > 1) {
            int loop_num = 0;
            for (lclset::const_iterator p = dag[l].begin(); p != dag[l].end(); p++) {
                BlockInst* switch_case_block = InstBuilder::genBlockInst();
                generateDAGLoopAux(*p, switch_case_block, count_dec, loop_num);
                switch_block->addCase(loop_num, switch_case_block);
                loop_num++;
            }
        } else {
            BlockInst* single_case_block = InstBuilder::genBlockInst();
            generateDAGLoopAux(*dag[l].begin(), single_case_block, count_dec, 0);
            switch_block->addCase(0, single_case_block);
        }

        loop_code->pushBackInst(switch_block);
        loop_code->pushBackInst(InstBuilder::genLabelInst("__syncthreads();"));
    }

    // Generates the DAG enclosing loop
    DeclareVarInst* loop_decl = InstBuilder::genDecLoopVar(index, InstBuilder::genBasicTyped(Typed::kInt32), InstBuilder::genInt32NumInst(0));

    ValueInst* loop_end = InstBuilder::genLessThan(loop_decl->load(),
                                InstBuilder::genLoadVarInst(InstBuilder::genNamedAddress(counter, Address::kFunArgs)));
    StoreVarInst* loop_increment = loop_decl->store(InstBuilder::genAdd(loop_decl->load(), gGlobal->gVecSize));

    StatementInst* loop = InstBuilder::genForLoopInst(loop_decl, loop_end, loop_increment, loop_code);

    // Generates the final loop
    loop->accept(fKernelCodeProducer);

    tab(n, *fGPUOut);
    *fGPUOut << "}";
    tab(n, *fGPUOut);
}

void CPPCUDAVectorCodeContainer::generateInstanceInitKernelGlue(int n)
{
    tab(n, *fGPUOut); *fGPUOut << "void instanceInitKernelGlue(faustdsp* dsp, faustcontrol* control, int samplingFreq) {";
        tab(n+1, *fGPUOut); *fGPUOut << "dim3 block(16);";
        tab(n+1, *fGPUOut); *fGPUOut << "dim3 grid(16);";
        tab(n+1, *fGPUOut); *fGPUOut << "instanceInitKernel<<<grid, block>>>(dsp, control, samplingFreq);";
    tab(n, *fGPUOut); *fGPUOut << "}";
}

void CPPCUDAVectorCodeContainer::generateComputeKernelGlue(int n)
{
    *fGPUOut << "void computeKernelGlue(int count, ";

    for (int i = 0; i < fNumInputs; i++) {
        *fGPUOut <<  " float* input" << i << ", ";
    }

    for (int i = 0; i < fNumOutputs; i++) {
        if (i == fNumOutputs - 1) {
            *fGPUOut << "float* output" << i;
        } else {
            *fGPUOut << "float* output" << i << ", ";
        }
    }

    *fGPUOut << ", faustdsp* dsp, faustcontrol* control) {";

        tab(n+1, *fGPUOut); *fGPUOut << "dim3 block(16);";
        tab(n+1, *fGPUOut); *fGPUOut << "dim3 grid(16);";
        tab(n+1, *fGPUOut); *fGPUOut << "computeKernel<<<grid, block>>>(count, ";

        for (int i = 0; i < fNumInputs; i++) {
            *fGPUOut <<  "input" << i << ", ";
        }

        for (int i = 0; i < fNumOutputs; i++) {
            if (i == fNumOutputs - 1) {
                *fGPUOut << "output" << i;
            } else {
                *fGPUOut << "output" << i << ", ";
            }
        }

        *fGPUOut << ", dsp, control);";

    tab(n, *fGPUOut); *fGPUOut << "}";
}

