/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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

#ifdef WIN32
#pragma warning(disable : 4996 4146 4244)
#endif

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

#include "Text.hh"
#include "compatibility.hh"
#include "dag_instructions_compiler.hh"
#include "description.hh"
#include "doc.hh"
#include "drawschema.hh"
#include "enrobage.hh"
#include "errormsg.hh"
#include "eval.hh"
#include "exception.hh"
#include "exepath.hh"
#include "floats.hh"
#include "garbageable.hh"
#include "global.hh"
#include "instructions_compiler.hh"
#include "instructions_compiler1.hh"
#include "labels.hh"
#include "instructions_compiler_jax.hh"
#include "libfaust.h"
#include "normalform.hh"
#include "ppbox.hh"
#include "ppsig.hh"
#include "privatise.hh"
#include "propagate.hh"
#include "recursivness.hh"
#include "schema.h"
#include "signalVisitor.hh"
#include "signals.hh"
#include "sigprint.hh"
#include "sigtype.hh"
#include "sourcereader.hh"
#include "timing.hh"
#include "xtended.hh"

#ifdef C_BUILD
#include "c_code_container.hh"
#endif

#ifdef CPP_BUILD
#include "cpp_code_container.hh"
#include "cpp_gpu_code_container.hh"
#endif

#ifdef CMAJOR_BUILD
#include "cmajor_code_container.hh"
#endif

#ifdef CSHARP_BUILD
#include "csharp_code_container.hh"
#endif

#ifdef DLANG_BUILD
#include "dlang_code_container.hh"
#endif

#ifdef FIR_BUILD
#include "fir_code_container.hh"
#endif

#ifdef INTERP_BUILD
#include "interpreter_code_container.cpp"
#endif

#ifdef JAVA_BUILD
#include "java_code_container.hh"
#endif

#ifdef JAX_BUILD
#include "jax_code_container.hh"
#endif

#ifdef JULIA_BUILD
#include "julia_code_container.hh"
#endif

#ifdef LLVM_BUILD
#include "clang_code_container.hh"
#include "llvm_code_container.hh"
#endif

#ifdef OCPP_BUILD
#include "compile_scal.hh"
#include "compile_sched.hh"
#include "compile_vect.hh"
#endif

#ifdef RUST_BUILD
#include "rust_code_container.hh"
#endif

#ifdef TEMPLATE_BUILD
#include "template_code_container.hh"
#endif

#ifdef WASM_BUILD
#include "wasm_code_container.hh"
#include "wast_code_container.hh"
#endif

using namespace std;

/****************************************************************
 Global context
 *****************************************************************/

static unique_ptr<ifstream> injcode;
static unique_ptr<ifstream> enrobage;
static unique_ptr<ostream>  helpers;

// Old CPP compiler
#ifdef OCPP_BUILD
static Compiler* old_comp = nullptr;
#endif

// FIR container
static InstructionsCompiler* new_comp  = nullptr;
static CodeContainer*        container = nullptr;

// Shared context
global* gGlobal = nullptr;

// Timing can be used outside of the scope of 'gGlobal'
extern bool gTimingSwitch;

string reorganizeCompilationOptions(int argc, const char* argv[]);

static void enumBackends(ostream& out)
{
    const char* dspto = "   DSP to ";
#ifdef C_BUILD
    out << dspto << "C" << endl;
#endif

#ifdef CPP_BUILD
    out << dspto << "C++" << endl;
#endif

#ifdef CMAJOR_BUILD
    out << dspto << "Cmajor" << endl;
#endif

#ifdef CSHARP_BUILD
    out << dspto << "CSharp" << endl;
#endif

#ifdef DLANG_BUILD
    out << dspto << "DLang" << endl;
#endif

#ifdef FIR_BUILD
    out << dspto << "FIR" << endl;
#endif

#ifdef INTERP_BUILD
    out << dspto << "Interpreter" << endl;
#endif

#ifdef JAVA_BUILD
    out << dspto << "Java" << endl;
#endif

#ifdef JAX_BUILD
    out << dspto << "JAX" << endl;
#endif
    
#ifdef JULIA_BUILD
    out << dspto << "Julia" << endl;
#endif

#ifdef LLVM_BUILD
    out << dspto << "LLVM IR" << endl;
#endif

#ifdef OCPP_BUILD
    out << dspto << "old C++" << endl;
#endif

#ifdef RUST_BUILD
    out << dspto << "Rust" << endl;
#endif
    
#ifdef TEMPLATE_BUILD
    out << dspto << "Template" << endl;
#endif

#ifdef WASM_BUILD
    out << dspto << "WebAssembly (wast/wasm)" << endl;
#endif
}

// Used to pass parameters and possibly return a result
struct CallContext {
    string fNameApp = "";
    string fDSPContent = "";
    int fArgc = 0;
    const char** fArgv = nullptr;
    bool fGenerate = false;
    int fNumInputs = -1;
    int fNumOutputs = -1;
    Tree fTree = nullptr;   // Used for in/out
    string fRes = "";       // Used for out
};

// Threaded function prototype
typedef void* (*threaded_fun)(void* arg);

static void callFun(threaded_fun fun, void* arg)
{
#if defined(EMCC)
    // No thread support in JavaScript
    fun(arg);
#elif defined(_WIN32)
    DWORD  id;
    HANDLE thread = CreateThread(NULL, MAX_STACK_SIZE, LPTHREAD_START_ROUTINE(fun), arg, 0, &id);
    faustassert(thread != NULL);
    WaitForSingleObject(thread, INFINITE);
#else
    pthread_t      thread;
    pthread_attr_t attr;
    faustassert(pthread_attr_init(&attr) == 0);
    faustassert(pthread_attr_setstacksize(&attr, MAX_STACK_SIZE) == 0);
    faustassert(pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE) == 0);
    faustassert(pthread_create(&thread, &attr, fun, arg) == 0);
    pthread_join(thread, nullptr);
#endif
}

/****************************************************************
                Command line tools and arguments
*****************************************************************/

//-- command line tools

static bool isCmd(const char* cmd, const char* kw1)
{
    return (strcmp(cmd, kw1) == 0);
}

static bool isCmd(const char* cmd, const char* kw1, const char* kw2)
{
    return (strcmp(cmd, kw1) == 0) || (strcmp(cmd, kw2) == 0);
}

static bool processCmdline(int argc, const char* argv[])
{
    int          i   = 1;
    int          err = 0;
    stringstream parse_error;
    bool         float_size = false;

    /*
    for (int i = 0; i < argc; i++) {
        cout << "processCmdline i = " << i << " cmd = " << argv[i] << "\n";
    }
    */

    while (i < argc) {
        if (isCmd(argv[i], "-h", "--help")) {
            gGlobal->gHelpSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-lang", "--language") && (i + 1 < argc)) {
            gGlobal->gOutputLang = argv[i + 1];
            i += 2;

        } else if (isCmd(argv[i], "-v", "--version")) {
            gGlobal->gVersionSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-libdir", "--libdir")) {
            gGlobal->gLibDirSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-includedir", "--includedir")) {
            gGlobal->gIncludeDirSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-archdir", "--archdir")) {
            gGlobal->gArchDirSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-dspdir", "--dspdir")) {
            gGlobal->gDspDirSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-pathslist", "--pathslist")) {
            gGlobal->gPathListSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-d", "--details")) {
            gGlobal->gDetailsSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-a", "--architecture") && (i + 1 < argc)) {
            gGlobal->gArchFile = argv[i + 1];
            i += 2;

        } else if (isCmd(argv[i], "-inj", "--inject") && (i + 1 < argc)) {
            gGlobal->gInjectFlag = true;
            gGlobal->gInjectFile = argv[i + 1];
            i += 2;

        } else if (isCmd(argv[i], "-o") && (i + 1 < argc)) {
            gGlobal->gOutputFile = argv[i + 1];
            i += 2;

        } else if (isCmd(argv[i], "-wi", "--widening-iterations") && (i + 1 < argc)) {
            gGlobal->gWideningLimit = std::atoi(argv[i + 1]);
            i += 2;

        } else if (isCmd(argv[i], "-ni", "--narrowing-iterations") && (i + 1 < argc)) {
            gGlobal->gNarrowingLimit = std::atoi(argv[i + 1]);
            i += 2;

        } else if (isCmd(argv[i], "-ps", "--postscript")) {
            gGlobal->gDrawPSSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-xml", "--xml")) {
            gGlobal->gPrintXMLSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-json", "--json")) {
            gGlobal->gPrintJSONSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-tg", "--task-graph")) {
            gGlobal->gGraphSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-sg", "--signal-graph")) {
            gGlobal->gDrawSignals = true;
            i += 1;

        } else if (isCmd(argv[i], "-drf", "--draw-route-frame")) {
            gGlobal->gDrawRouteFrame = true;
            i += 1;

        } else if (isCmd(argv[i], "-blur", "--shadow-blur")) {
            gGlobal->gShadowBlur = true;
            i += 1;

        } else if (isCmd(argv[i], "-sc", "--scaled-svg")) {
            gGlobal->gScaledSVG = true;
            i += 1;

        } else if (isCmd(argv[i], "-svg", "--svg")) {
            gGlobal->gDrawSVGSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-vhdl", "--vhdl")) {
            gGlobal->gVHDLSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-vhdl-trace", "--vhdl-trace")) {
            gGlobal->gVHDLTrace = true;
            i += 1;

        } else if (isCmd(argv[i], "-vhdl-type", "--vhdl-type") && (i + 1 < argc)) {
            gGlobal->gVHDLFloatType = std::atoi(argv[i + 1]);
            i += 2;

        } else if (isCmd(argv[i], "-vhdl-msb", "--vhdl-msb") && (i + 1 < argc)) {
            gGlobal->gVHDLFloatMSB = std::atoi(argv[i + 1]);
            i += 2;

        } else if (isCmd(argv[i], "-vhdl-lsb", "--vhdl-lsb") && (i + 1 < argc)) {
            gGlobal->gVHDLFloatLSB = std::atoi(argv[i + 1]);
            i += 2;

        } else if (isCmd(argv[i], "-f", "--fold") && (i + 1 < argc)) {
            gGlobal->gFoldThreshold = std::atoi(argv[i + 1]);
            i += 2;

        } else if (isCmd(argv[i], "-fc", "--fold-complexity") && (i + 1 < argc)) {
            gGlobal->gFoldComplexity = std::atoi(argv[i + 1]);
            i += 2;

        } else if (isCmd(argv[i], "-mns", "--max-name-size") && (i + 1 < argc)) {
            gGlobal->gMaxNameSize = std::atoi(argv[i + 1]);
            i += 2;

        } else if (isCmd(argv[i], "-sn", "--simple-names")) {
            gGlobal->gSimpleNames = true;
            i += 1;

        } else if (isCmd(argv[i], "-mcd", "--max-copy-delay") && (i + 1 < argc)) {
            gGlobal->gMaxCopyDelay = std::atoi(argv[i + 1]);
            i += 2;

        } else if (isCmd(argv[i], "-dlt", "-delay-line-threshold") && (i + 1 < argc)) {
            gGlobal->gMaskDelayLineThreshold = std::atoi(argv[i + 1]);
            i += 2;

        } else if (isCmd(argv[i], "-mem", "--memory-manager")) {
            gGlobal->gMemoryManager = true;
            i += 1;

        } else if (isCmd(argv[i], "-sd", "--simplify-diagrams")) {
            gGlobal->gSimplifyDiagrams = true;
            i += 1;

        } else if (isCmd(argv[i], "-vec", "--vectorize")) {
            gGlobal->gVectorSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-scal", "--scalar")) {
            gGlobal->gVectorSwitch = false;
            i += 1;

        } else if (isCmd(argv[i], "-dfs", "--deepFirstScheduling")) {
            gGlobal->gDeepFirstSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-vs", "--vec-size") && (i + 1 < argc)) {
            gGlobal->gVecSize = std::atoi(argv[i + 1]);
            i += 2;

        } else if (isCmd(argv[i], "-lv", "--loop-variant") && (i + 1 < argc)) {
            gGlobal->gVectorLoopVariant = std::atoi(argv[i + 1]);
            i += 2;

        } else if (isCmd(argv[i], "-omp", "--openmp")) {
            gGlobal->gOpenMPSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-pl", "--par-loop")) {
            gGlobal->gOpenMPLoop = true;
            i += 1;

        } else if (isCmd(argv[i], "-sch", "--scheduler")) {
            gGlobal->gSchedulerSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-ocl", "--openCL")) {
            gGlobal->gOpenCLSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-cuda", "--CUDA")) {
            gGlobal->gCUDASwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-g", "--groupTasks")) {
            gGlobal->gGroupTaskSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-fun", "--funTasks")) {
            gGlobal->gFunTaskSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-uim", "--user-interface-macros")) {
            gGlobal->gUIMacroSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-t", "--timeout") && (i + 1 < argc)) {
            gGlobal->gTimeout = std::atoi(argv[i + 1]);
            i += 2;

        } else if (isCmd(argv[i], "-time", "--compilation-time")) {
            gTimingSwitch = true;
            i += 1;

            // 'real' options
        } else if (isCmd(argv[i], "-single", "--single-precision-floats")) {
            if (float_size && gGlobal->gFloatSize != 1) {
                throw faustexception("ERROR : cannot using -single, -double, -quad or -fx at the same time\n");
            } else {
                float_size = true;
            }
            gGlobal->gFloatSize = 1;
            i += 1;

        } else if (isCmd(argv[i], "-double", "--double-precision-floats")) {
            if (float_size && gGlobal->gFloatSize != 2) {
                throw faustexception("ERROR : cannot using -single, -double, -quad or -fx at the same time\n");
            } else {
                float_size = true;
            }
            gGlobal->gFloatSize = 2;
            i += 1;

        } else if (isCmd(argv[i], "-quad", "--quad-precision-floats")) {
            if (float_size && gGlobal->gFloatSize != 3) {
                throw faustexception("ERROR : cannot using -single, -double, -quad or -fx at the same time\n");
            } else {
                float_size = true;
            }
            gGlobal->gFloatSize = 3;
            i += 1;

        } else if (isCmd(argv[i], "-fx", "--fixed-point")) {
            if (float_size && gGlobal->gFloatSize != 4) {
                throw faustexception("ERROR : cannot using -single, -double, -quad or -fx at the same time\n");
            } else {
                float_size = true;
            }
            gGlobal->gFloatSize = 4;
            i += 1;

        } else if (isCmd(argv[i], "-mdoc", "--mathdoc")) {
            gGlobal->gPrintDocSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-mdlang", "--mathdoc-lang") && (i + 1 < argc)) {
            gGlobal->gDocLang = argv[i + 1];
            i += 2;

        } else if (isCmd(argv[i], "-stripmdoc", "--strip-mdoc-tags")) {
            gGlobal->gStripDocSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-flist", "--file-list")) {
            gGlobal->gPrintFileListSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-norm", "--normalized-form")) {
            gGlobal->gDumpNorm = 0;
            i += 1;

        } else if (isCmd(argv[i], "-norm1", "--normalized-form1")) {
            gGlobal->gDumpNorm = 1;
            i += 1;

        } else if (isCmd(argv[i], "-cn", "--class-name") && (i + 1 < argc)) {
            vector<char> rep    = {'@', ' ', '(', ')', '/', '\\', '.'};
            gGlobal->gClassName = replaceCharList(argv[i + 1], rep, '_');
            i += 2;

        } else if (isCmd(argv[i], "-scn", "--super-class-name") && (i + 1 < argc)) {
            gGlobal->gSuperClassName = argv[i + 1];
            i += 2;

        } else if (isCmd(argv[i], "-pn", "--process-name") && (i + 1 < argc)) {
            gGlobal->gProcessName = argv[i + 1];
            i += 2;

        } else if (isCmd(argv[i], "-i", "--inline-architecture-files")) {
            gGlobal->gInlineArchSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-e", "--export-dsp")) {
            gGlobal->gExportDSP = true;
            i += 1;

        } else if (isCmd(argv[i], "-exp10", "--generate-exp10")) {
            gGlobal->gHasExp10 = true;
            i += 1;

        } else if (isCmd(argv[i], "-os", "--one-sample") || isCmd(argv[i], "-os0", "--one-sample0")) {
            gGlobal->gOneSample = 0;
            i += 1;

        } else if (isCmd(argv[i], "-os1", "--one-sample1")) {
            gGlobal->gOneSample = 1;
            i += 1;

        } else if (isCmd(argv[i], "-os2", "--one-sample2")) {
            gGlobal->gOneSample = 2;
            i += 1;

        } else if (isCmd(argv[i], "-os3", "--one-sample3")) {
            gGlobal->gOneSample = 3;
            i += 1;

        } else if (isCmd(argv[i], "-cm", "--compute-mix")) {
            gGlobal->gComputeMix = true;
            i += 1;

        } else if (isCmd(argv[i], "-ftz", "--flush-to-zero")) {
            gGlobal->gFTZMode = std::atoi(argv[i + 1]);
            if ((gGlobal->gFTZMode > 2) || (gGlobal->gFTZMode < 0)) {
                stringstream error;
                error << "ERROR : invalid -ftz option: " << gGlobal->gFTZMode << endl;
                throw faustexception(error.str());
            }
            i += 2;

        } else if (isCmd(argv[i], "-rui", "--range-ui")) {
            gGlobal->gRangeUI = true;
            i += 1;

        } else if (isCmd(argv[i], "-fm", "--fast-math")) {
            gGlobal->gFastMath    = true;
            gGlobal->gFastMathLib = argv[i + 1];
            i += 2;

        } else if (isCmd(argv[i], "-mapp", "--math-approximation")) {
            gGlobal->gMathApprox = true;
            i += 1;

        } else if (isCmd(argv[i], "-ns", "--namespace")) {
            gGlobal->gNamespace = argv[i + 1];
            i += 2;

        } else if (isCmd(argv[i], "-fp", "--full-parentheses")) {
            gGlobal->gFullParentheses = true;
            i += 1;

        } else if (isCmd(argv[i], "-I", "--import-dir") && (i + 1 < argc)) {
            if ((strstr(argv[i + 1], "http://") != 0) || (strstr(argv[i + 1], "https://") != 0)) {
                // We want to search user given directories *before* the standard ones, so insert at the beginning
                gGlobal->gImportDirList.insert(gGlobal->gImportDirList.begin(), argv[i + 1]);
            } else {
                char  temp[PATH_MAX + 1];
                char* path = realpath(argv[i + 1], temp);
                if (path) {
                    // We want to search user given directories *before* the standard ones, so insert at the beginning
                    gGlobal->gImportDirList.insert(gGlobal->gImportDirList.begin(), path);
                }
            }
            i += 2;

        } else if (isCmd(argv[i], "-A", "--architecture-dir") && (i + 1 < argc)) {
            if ((strstr(argv[i + 1], "http://") != 0) || (strstr(argv[i + 1], "https://") != 0)) {
                gGlobal->gArchitectureDirList.push_back(argv[i + 1]);
            } else {
                char  temp[PATH_MAX + 1];
                char* path = realpath(argv[i + 1], temp);
                if (path) {
                    gGlobal->gArchitectureDirList.push_back(path);
                }
            }
            i += 2;

        } else if (isCmd(argv[i], "-L", "--library") && (i + 1 < argc)) {
            gGlobal->gLibraryList.push_back(argv[i + 1]);
            i += 2;

        } else if (isCmd(argv[i], "-O", "--output-dir") && (i + 1 < argc)) {
            char  temp[PATH_MAX + 1];
            char* path = realpath(argv[i + 1], temp);
            if (path == 0) {
                stringstream error;
                error << "ERROR : invalid directory path " << argv[i + 1] << endl;
                throw faustexception(error.str());
            } else {
                gGlobal->gOutputDir = path;
            }
            i += 2;

        } else if (isCmd(argv[i], "-inpl", "--in-place")) {
            gGlobal->gInPlace = true;
            i += 1;

        } else if (isCmd(argv[i], "-sts", "--strict-select")) {
            gGlobal->gStrictSelect = true;
            i += 1;

        } else if (isCmd(argv[i], "-es", "--enable-semantics")) {
            gGlobal->gEnableFlag = std::atoi(argv[i + 1]) == 1;
            i += 2;

        } else if (isCmd(argv[i], "-lcc", "--local-causality-check")) {
            gGlobal->gLocalCausalityCheck = true;
            i += 1;

        } else if (isCmd(argv[i], "-light", "--light-mode")) {
            gGlobal->gLightMode = true;
            i += 1;

        } else if (isCmd(argv[i], "-clang", "--clang")) {
            gGlobal->gClang = true;
            i += 1;

        } else if (isCmd(argv[i], "-nvi", "--no-virtual")) {
            gGlobal->gNoVirtual = true;
            i += 1;

        } else if (isCmd(argv[i], "-ct", "--check-table")) {
            gGlobal->gCheckTable = "ct";
            i += 1;

        } else if (isCmd(argv[i], "-cat", "--check-all-table")) {
            gGlobal->gCheckTable = "cat";
            i += 1;

        } else if (isCmd(argv[i], "-me", "--math-exceptions")) {
            gGlobal->gMathExceptions = true;
            i += 1;

        } else if (isCmd(argv[i], "-lm", "--local-machine") || isCmd(argv[i], "-rm", "--remote-machine") ||
                   isCmd(argv[i], "-poly", "--polyphonic-mode") || isCmd(argv[i], "-voices", "--polyphonic-voices") ||
                   isCmd(argv[i], "-group", "--polyphonic-group")) {
            // Ignore arg
            i += 2;

        } else if (argv[i][0] != '-') {
            const char* url = argv[i];
            if (checkURL(url)) {
                gGlobal->gInputFiles.push_back(url);
            }
            i++;

        } else {
            if (err == 0) {
                parse_error << "unrecognized option(s) : \"" << argv[i] << "\"";
            } else {
                parse_error << ",\"" << argv[i] << "\"";
            }
            i++;
            err++;
        }
    }

    // Adjust related options
    if (gGlobal->gOpenMPSwitch || gGlobal->gSchedulerSwitch) gGlobal->gVectorSwitch = true;

    // Check options coherency
    if (gGlobal->gInPlace && gGlobal->gVectorSwitch) {
        throw faustexception("ERROR : '-inpl' option can only be used in scalar mode\n");
    }

#if 0
    if (gGlobal->gOutputLang == "ocpp" && gGlobal->gVectorSwitch) {
        throw faustexception("ERROR : 'ocpp' backend can only be used in scalar mode\n");
    }
#endif
    if (gGlobal->gOneSample >= 0 && gGlobal->gOutputLang != "cpp" && gGlobal->gOutputLang != "c" && gGlobal->gOutputLang != "dlang" &&
        !startWith(gGlobal->gOutputLang, "cmajor") && gGlobal->gOutputLang != "fir") {
        throw faustexception("ERROR : '-os' option cannot only be used with 'cpp', 'c', 'fir' or 'cmajor' backends\n");
    }

    if (gGlobal->gOneSample >= 0 && gGlobal->gVectorSwitch) {
        throw faustexception("ERROR : '-os' option cannot only be used in scalar mode\n");
    }

    if (gGlobal->gFTZMode == 2 && gGlobal->gOutputLang == "cmajor") {
        throw faustexception("ERROR : '-ftz 2' option cannot be used in 'cmajor' backend\n");
    }

    if (gGlobal->gVectorLoopVariant < 0 || gGlobal->gVectorLoopVariant > 1) {
        stringstream error;
        error << "ERROR : invalid loop variant [-lv = " << gGlobal->gVectorLoopVariant << "] should be 0 or 1" << endl;
        throw faustexception(error.str());
    }

    if (gGlobal->gVecSize < 4) {
        stringstream error;
        error << "ERROR : invalid vector size [-vs = " << gGlobal->gVecSize << "] should be at least 4" << endl;
        throw faustexception(error.str());
    }

    if (gGlobal->gFunTaskSwitch) {
        if (!(gGlobal->gOutputLang == "c" || gGlobal->gOutputLang == "cpp" || gGlobal->gOutputLang == "llvm" ||
              gGlobal->gOutputLang == "fir")) {
            throw faustexception("ERROR : -fun can only be used with 'c', 'cpp', 'llvm' or 'fir' backends\n");
        }
    }

    if (gGlobal->gFastMath) {
        if (!(gGlobal->gOutputLang == "c" || gGlobal->gOutputLang == "cpp" || gGlobal->gOutputLang == "llvm" ||
              startWith(gGlobal->gOutputLang, "wast") || startWith(gGlobal->gOutputLang, "wasm"))) {
            throw faustexception("ERROR : -fm can only be used with 'c', 'cpp', 'llvm' or 'wast/wast' backends\n");
        }
    }

    if (gGlobal->gNamespace != "" && gGlobal->gOutputLang != "cpp" && gGlobal->gOutputLang != "dlang") {
        throw faustexception("ERROR : -ns can only be used with the 'cpp' or 'dlang' backend\n");
    }

    if (gGlobal->gMaskDelayLineThreshold < INT_MAX && (gGlobal->gVectorSwitch || (gGlobal->gOutputLang == "ocpp"))) {
        throw faustexception(
            "ERROR : '-dlt < INT_MAX' option can only be used in scalar mode and not with the 'ocpp' backend\n");
    }

    // gComputeMix check
    if (gGlobal->gComputeMix && gGlobal->gOutputLang == "ocpp") {
        throw faustexception("ERROR : -cm cannot be used with the 'ocpp' backend\n");
    }

    if (gGlobal->gComputeMix && gGlobal->gOutputLang == "interp") {
        throw faustexception("ERROR : -cm cannot be used with the 'interp' backend\n");
    }

    if (gGlobal->gComputeMix && gGlobal->gOutputLang == "cmajor") {
        throw faustexception("ERROR : -cm cannot be used with the 'cmajor' backend\n");
    }

    if (gGlobal->gFloatSize == 4 && gGlobal->gOutputLang != "cpp" && gGlobal->gOutputLang != "ocpp" &&
        gGlobal->gOutputLang != "c") {
        throw faustexception("ERROR : -fx can only be used with 'c', 'cpp' or 'ocpp' backends\n");
    }

    if (gGlobal->gClang && gGlobal->gOutputLang != "cpp" && gGlobal->gOutputLang != "ocpp" &&
        gGlobal->gOutputLang != "c") {
        throw faustexception("ERROR : -clang can only be used with 'c', 'cpp' or 'ocpp' backends\n");
    }

    if (gGlobal->gNoVirtual && gGlobal->gOutputLang != "cpp" && gGlobal->gOutputLang != "ocpp" &&
        gGlobal->gOutputLang != "c") {
        throw faustexception("ERROR : -nvi can only be used with 'c', 'cpp' or 'ocpp' backends\n");
    }

    if (gGlobal->gMemoryManager && gGlobal->gOutputLang != "cpp" && gGlobal->gOutputLang != "ocpp") {
        throw faustexception("ERROR : -mem can only be used with 'cpp' or 'ocpp' backends\n");
    }

    if (gGlobal->gArchFile != "" &&
        ((gGlobal->gOutputLang == "wast") || (gGlobal->gOutputLang == "wasm") || (gGlobal->gOutputLang == "interp") ||
         (gGlobal->gOutputLang == "llvm") || (gGlobal->gOutputLang == "fir"))) {
        throw faustexception("ERROR : -a can only be used with 'c', 'cpp', 'ocpp', 'rust' and 'cmajor' backends\n");
    }

    if (gGlobal->gClassName == "") {
        throw faustexception("ERROR : -cn used with empty string \n");
    }

    if (err != 0) {
        stringstream error;
        error << "WARNING : " << parse_error.str() << endl;
        gGlobal->gErrorMessage = error.str();
    }

    return (err == 0);
}

/****************************************************************
                     Faust directories information
*****************************************************************/
#ifdef WIN32
#define kPSEP '\\'
#else
#define kPSEP '/'
#endif

#ifndef LIBDIR
#define LIBDIR "lib"
#endif
static void printLibDir()
{
    cout << gGlobal->gFaustRootDir << kPSEP << LIBDIR << endl;
}
static void printIncludeDir()
{
    cout << gGlobal->gFaustRootDir << kPSEP << "include" << endl;
}
static void printArchDir()
{
    cout << gGlobal->gFaustRootDir << kPSEP << "share" << kPSEP << "faust" << endl;
}
static void printDspDir()
{
    cout << gGlobal->gFaustRootDir << kPSEP << "share" << kPSEP << "faust" << endl;
}
static void printPaths()
{
    cout << "FAUST dsp library paths:" << endl;
    for (const auto& path : gGlobal->gImportDirList) cout << path << endl;
    cout << "\nFAUST architectures paths:" << endl;
    for (const auto& path : gGlobal->gArchitectureDirList) cout << path << endl;
    cout << endl;
}

/****************************************************************
                     Help and Version information
*****************************************************************/

static void printVersion()
{
    cout << "FAUST Version " << FAUSTVERSION << "\n";
    cout << "Embedded backends: \n";
    enumBackends(cout);
#ifdef LLVM_BUILD
    cout << "Build with LLVM version " << LLVM_VERSION << "\n";
#endif
    cout << "Copyright (C) 2002-2022, GRAME - Centre National de Creation Musicale. All rights reserved. \n";
}

static void printHelp()
{
    const char* tab  = "  ";
    const char* line = "\n---------------------------------------\n";

    cout << "FAUST compiler version " << FAUSTVERSION << "\n";
    cout << "usage : faust [options] file1 [file2 ...]." << endl;
    cout << "        where options represent zero or more compiler options \n\tand fileN represents a Faust source "
            "file (.dsp extension)."
         << endl;

    cout << endl << "Input options:" << line;
    cout << tab << "-a <file>                               wrapper architecture file." << endl;
    cout << tab << "-i        --inline-architecture-files   inline architecture files." << endl;
    cout << tab << "-A <dir>  --architecture-dir <dir>      add the directory <dir> to the architecture search path."
         << endl;
    cout << tab << "-I <dir>  --import-dir <dir>            add the directory <dir> to the libraries search path."
         << endl;
    cout << tab << "-L <file> --library <file>              link with the LLVM module <file>." << endl;

    cout << tab << "-t <sec>  --timeout <sec>               abort compilation after <sec> seconds (default 120)."
         << endl;

    cout << endl << "Output options:" << line;
    cout << tab << "-o <file>                               the output file." << endl;
    cout << tab << "-e        --export-dsp                  export expanded DSP (with all included libraries)." << endl;
    cout << tab << "-uim      --user-interface-macros       add user interface macro definitions to the output code."
         << endl;
    cout << tab << "-xml                                    generate an XML description file." << endl;
    cout << tab << "-json                                   generate a JSON description file." << endl;
    cout << tab
         << "-O <dir>  --output-dir <dir>            specify the relative directory of the generated output code and "
            "of additional generated files (SVG, XML...)."
         << endl;

    cout << endl << "Code generation options:" << line;
    cout << tab << "-lang <lang> --language                 select output language," << endl;
    cout << tab
         << "                                        'lang' should be c, cpp (default), cmajor, csharp, dlang, fir, interp, java, jax, julia, llvm, "
            "ocpp, rust or wast/wasm."
         << endl;
    cout << tab
         << "-single     --single-precision-floats   use single precision floats for internal computations (default)."
         << endl;
    cout << tab << "-double     --double-precision-floats   use double precision floats for internal computations."
         << endl;
    cout << tab << "-quad       --quad-precision-floats     use quad precision floats for internal computations."
         << endl;
    cout << tab << "-fx         --fixed-point               use fixed-point for internal computations." << endl;
    cout << tab
         << "-es 1|0     --enable-semantics 1|0      use enable semantics when 1 (default), and simple multiplication "
            "otherwise."
         << endl;
    cout << tab << "-lcc        --local-causality-check     check causality also at local level." << endl;
    cout << tab << "-light      --light-mode                do not generate the entire DSP API." << endl;
    cout << tab
         << "-clang      --clang                     when compiled with clang/clang++, adds specific #pragma for "
            "auto-vectorization."
         << endl;
    cout << tab
         << "-nvi        --no-virtual                when compiled with the C++ backend, does not add the 'virtual' "
            "keyword."
         << endl;
    cout << tab << "-fp         --full-parentheses          always add parentheses around binops " << endl;
    cout << tab << "-exp10      --generate-exp10            pow(10,x) replaced by possibly faster exp10(x)." << endl;
    cout << tab << "-os         --one-sample                generate one sample computation (same as -os0)." << endl;
    cout << tab << "-os0        --one-sample0               generate one sample computation (0 = separated control)."
         << endl;
    cout << tab
         << "-os1        --one-sample1               generate one sample computation (1 = separated control and DSP "
            "struct)."
         << endl;
    cout << tab
         << "-os2        --one-sample2               generate one sample computation (2 = separated control and DSP "
            "struct. Separation in short and long delay lines)."
         << endl;
    cout << tab
         << "-os3        --one-sample3               generate one sample computation (3 = like 2 but with external "
            "memory pointers kept in the DSP struct)."
         << endl;

    cout << tab << "-cm         --compute-mix               mix in outputs buffers." << endl;
    cout << tab
         << "-cn <name>  --class-name <name>         specify the name of the dsp class to be used instead of mydsp."
         << endl;
    cout << tab
         << "-scn <name> --super-class-name <name>   specify the name of the super class to be used instead of dsp."
         << endl;
    cout << tab << "-pn <name>  --process-name <name>       specify the name of the dsp entry-point instead of process."
         << endl;
    cout << tab
         << "-mcd <n>    --max-copy-delay <n>        threshold between copy and ring buffer implementation (default 16 "
            "samples)."
         << endl;
    cout << tab
         << "-dlt <n>    --delay-line-threshold <n>  threshold between 'mask' and 'select' ring buffer implementation "
            "(default INT_MAX "
            "samples)."
         << endl;
    cout << tab
         << "-mem        --memory-manager            allocate static in global state using a custom memory manager."
         << endl;
    cout << tab
         << "-ftz <n>    --flush-to-zero <n>         code added to recursive signals [0:no (default), 1:fabs based, "
            "2:mask based (fastest)]."
         << endl;
    cout << tab
         << "-rui        --range-ui                  whether to generate code to limit vslider/hslider/nentry values "
            "in [min..max] range."
         << endl;
    cout
        << tab
        << "-inj <f>    --inject <f>                inject source file <f> into architecture file instead of compiling "
           "a dsp file."
        << endl;
    cout << tab << "-scal       --scalar                    generate non-vectorized code (default)." << endl;
    cout << tab
         << "-inpl       --in-place                  generates code working when input and output buffers are the same "
            "(scalar mode only)."
         << endl;
    cout << tab << "-vec        --vectorize                 generate easier to vectorize code." << endl;
    cout << tab << "-vs <n>     --vec-size <n>              size of the vector (default 32 samples)." << endl;
    cout << tab << "-lv <n>     --loop-variant <n>          [0:fastest (default), 1:simple]." << endl;
    cout << tab << "-omp        --openmp                    generate OpenMP pragmas, activates --vectorize option."
         << endl;
    cout << tab << "-pl         --par-loop                  generate parallel loops in --openmp mode." << endl;
    cout << tab
         << "-sch        --scheduler                 generate tasks and use a Work Stealing scheduler, activates "
            "--vectorize option."
         << endl;
    cout << tab << "-ocl        --opencl                    generate tasks with OpenCL (experimental)." << endl;
    cout << tab << "-cuda       --cuda                      generate tasks with CUDA (experimental)." << endl;
    cout << tab << "-dfs        --deep-first-scheduling     schedule vector loops in deep first order." << endl;
    cout << tab
         << "-g          --group-tasks               group single-threaded sequential tasks together when -omp or -sch "
            "is used."
         << endl;
    cout << tab
         << "-fun        --fun-tasks                 separate tasks code as separated functions (in -vec, -sch, or "
            "-omp mode)."
         << endl;
    cout << tab
         << "-fm <file>  --fast-math <file>          use optimized versions of mathematical functions implemented in "
            "<file>, use 'faust/dsp/fastmath.cpp' when file is 'def'."
         << endl;
    cout << tab

         << "-mapp       --math-approximation        simpler/faster versions of 'floor/ceil/fmod/remainder' functions."
         << endl;
    cout << tab << "-ns <name>  --namespace <name>          generate C++ or D code in a namespace <name>." << endl;

    cout << tab << "-vhdl          --vhdl                   output vhdl file." << endl;
    cout << tab << "-vhdl-trace    --vhdl-trace             activate trace." << endl;
    cout << tab << "-vhdl-type 0|1 --vhdl-type 0|1          sample format 0 = sfixed (default), 1 = float." << endl;
    cout << tab << "-vhdl-msb <n>  --vhdl-msb <n>           MSB number of bits." << endl;
    cout << tab << "-vhdl-lsb <n>  --vhdl-lsb <n>           LSB number of bits." << endl;

    cout << tab << "-wi <n>     --widening-iterations <n>   number of iterations before widening in signal bounding."
         << endl;

    cout << tab
         << "-ni <n>     --narrowing-iterations <n>  number of iterations before stopping narrowing in signal bounding."
         << endl;

    cout << endl << "Block diagram options:" << line;
    cout << tab << "-ps        --postscript                 print block-diagram to a postscript file." << endl;
    cout << tab << "-svg       --svg                        print block-diagram to a svg file." << endl;
    cout << tab << "-sd        --simplify-diagrams          try to further simplify diagrams before drawing." << endl;
    cout << tab << "-drf       --draw-route-frame           draw route frames instead of simple cables." << endl;
    cout << tab
         << "-f <n>     --fold <n>                   threshold to activate folding mode during block-diagram "
            "generation (default 25 elements)."
         << endl;
    cout << tab
         << "-fc <n>    --fold-complexity <n>        complexity threshold to fold an expression in folding mode "
            "(default 2)."
         << endl;
    cout << tab
         << "-mns <n>   --max-name-size <n>          threshold during block-diagram generation (default 40 char)."
         << endl;
    cout << tab
         << "-sn        --simple-names               use simple names (without arguments) during block-diagram "
            "generation."
         << endl;
    cout << tab << "-blur      --shadow-blur                add a shadow blur to SVG boxes." << endl;

    cout << endl << "Math doc options:" << line;
    cout << tab
         << "-mdoc       --mathdoc                   print math documentation of the Faust program in LaTeX format in "
            "a -mdoc folder."
         << endl;
    cout << tab << "-mdlang <l> --mathdoc-lang <l>          if translation file exists (<l> = en, fr, ...)." << endl;
    cout << tab << "-stripmdoc  --strip-mdoc-tags           strip mdoc tags when printing Faust -mdoc listings."
         << endl;

    cout << endl << "Debug options:" << line;
    cout << tab << "-d          --details                   print compilation details." << endl;
    cout << tab << "-time       --compilation-time          display compilation phases timing information." << endl;
    cout << tab << "-flist      --file-list                 print file list (including libraries) used to eval process."
         << endl;
    cout << tab << "-tg         --task-graph                print the internal task graph in dot format." << endl;
    cout << tab << "-sg         --signal-graph              print the internal signal graph in dot format." << endl;
    cout << tab << "-norm       --normalized-form           print signals in normalized form and exit." << endl;
    cout << tab << "-ct         --check-table               check table index range and exit at first failure." << endl;
    cout << tab << "-cat        --check-all-table           check all table index range." << endl;
    cout << tab
         << "-me         --math-exceptions           check / for 0 as denominator and remainder, fmod, sqrt, log10, "
            "log, acos, asin functions domain."
         << endl;
    cout << tab << "-sts        --strict-select             generate strict code for 'selectX' even for stateless branches (both are computed)." << endl;
    
    cout << endl << "Information options:" << line;
    cout << tab << "-h          --help                      print this help message." << endl;
    cout << tab << "-v          --version                   print version information and embedded backends list."
         << endl;
    cout << tab << "-libdir     --libdir                    print directory containing the Faust libraries." << endl;
    cout << tab << "-includedir --includedir                print directory containing the Faust headers." << endl;
    cout << tab << "-archdir    --archdir                   print directory containing the Faust architectures."
         << endl;
    cout << tab << "-dspdir     --dspdir                    print directory containing the Faust dsp libraries."
         << endl;
    cout << tab << "-pathslist  --pathslist                 print the architectures and dsp library paths." << endl;

    cout << endl << "Example:" << line;
    cout << "faust -a jack-gtk.cpp -o myfx.cpp myfx.dsp" << endl;
}

static void printDeclareHeader(ostream& dst)
{
    for (const auto& i : gGlobal->gMetaDataSet) {
        if (i.first != tree("author")) {
            dst << "declare ";
            stringstream key;
            key << *(i.first);
            vector<char> rep{'.', ':', '/'};
            dst << replaceCharList(key.str(), rep, '_');
            dst << " " << **(i.second.begin()) << ";" << endl;
        } else {
            for (set<Tree>::iterator j = i.second.begin(); j != i.second.end(); ++j) {
                if (j == i.second.begin()) {
                    dst << "declare " << *(i.first) << " " << **j << ";" << endl;
                } else {
                    dst << "declare contributor " << **j << ";" << endl;
                }
            }
        }
    }
}

LIBFAUST_API const char* xtendedName(Tree tree)
{
    void* userData = getUserData(tree);
    faustassert(userData != nullptr);
    return ((xtended*)userData)->name();
}

LIBFAUST_API unsigned int xtendedArity(Tree tree)
{
    void* userData = getUserData(tree);
    faustassert(userData != nullptr);
    return ((xtended*)userData)->arity();
}

/****************************************************************
                                MAIN
*****************************************************************/

/**
 * transform a filename "faust/example/noise.dsp" into
 * the corresponding fx name "noise"
 */
static string fxName(const string& filename)
{
    // determine position right after the last '/' or 0
    size_t p1 = 0;
    for (size_t i = 0; i < filename.size(); i++) {
        if (filename[i] == '/') {
            p1 = i + 1;
        }
    }

    // determine position of the last '.'
    size_t p2 = filename.size();
    for (size_t i = p1; i < filename.size(); i++) {
        if (filename[i] == '.') {
            p2 = i;
        }
    }

    return filename.substr(p1, p2 - p1);
}

static void initFaustDirectories(int argc, const char* argv[])
{
#if !defined(FAUST_SELF_CONTAINED_LIB)
    char s[1024];
    getFaustPathname(s, 1024);

    gGlobal->gFaustExeDir              = exepath::get(argv[0]);
    gGlobal->gFaustRootDir             = exepath::dirup(gGlobal->gFaustExeDir);
    gGlobal->gFaustDirectory           = fileDirname(s);
    gGlobal->gFaustSuperDirectory      = fileDirname(gGlobal->gFaustDirectory);
    gGlobal->gFaustSuperSuperDirectory = fileDirname(gGlobal->gFaustSuperDirectory);

    //-------------------------------------------------------------------------------------
    // init gImportDirList : a list of path where to search .lib files
    //-------------------------------------------------------------------------------------
    if (char* envpath = getenv("FAUST_LIB_PATH")) {
        gGlobal->gImportDirList.push_back(envpath);
    }
#ifdef INSTALL_PREFIX
    gGlobal->gImportDirList.push_back(INSTALL_PREFIX "/share/faust");
#endif

    gGlobal->gImportDirList.push_back(exepath::dirup(gGlobal->gFaustExeDir) + "/share/faust");
    gGlobal->gImportDirList.push_back("/usr/local/share/faust");
    gGlobal->gImportDirList.push_back("/usr/share/faust");

    //-------------------------------------------------------------------------------------
    // init gArchitectureDirList : a list of path where to search architectures files
    //-------------------------------------------------------------------------------------
    if (char* envpath = getenv("FAUST_ARCH_PATH")) {
        gGlobal->gArchitectureDirList.push_back(envpath);
    }
    gGlobal->gArchitectureDirList.push_back(gGlobal->gFaustDirectory + "/architecture");
    gGlobal->gArchitectureDirList.push_back(gGlobal->gFaustSuperDirectory + "/architecture");
    gGlobal->gArchitectureDirList.push_back(gGlobal->gFaustSuperSuperDirectory + "/architecture");
#ifdef INSTALL_PREFIX
    gGlobal->gArchitectureDirList.push_back(INSTALL_PREFIX "/share/faust");
    gGlobal->gArchitectureDirList.push_back(INSTALL_PREFIX "/include");
#endif
    gGlobal->gArchitectureDirList.push_back(exepath::dirup(gGlobal->gFaustExeDir) + "/share/faust");
    gGlobal->gArchitectureDirList.push_back(exepath::dirup(gGlobal->gFaustExeDir) + "/include");
    gGlobal->gArchitectureDirList.push_back("/usr/local/share/faust");
    gGlobal->gArchitectureDirList.push_back("/usr/share/faust");
    gGlobal->gArchitectureDirList.push_back("/usr/local/include");
    gGlobal->gArchitectureDirList.push_back("/usr/include");

    // for debugging purposes
    //    cerr << "gArchitectureDirList:\n";
    //    for (const auto& d : gGlobal->gArchitectureDirList) {
    //        cerr << "\t" << d << "\n";
    //    }
    //    cerr << endl;
#endif
}

static void initDocumentNames()
{
    if (gGlobal->gInputFiles.empty()) {
        gGlobal->gMasterDocument  = "Unknown";
        gGlobal->gMasterDirectory = ".";
        gGlobal->gMasterName      = "faustfx";
        gGlobal->gDocName         = "faustdoc";
    } else {
        gGlobal->gMasterDocument  = *gGlobal->gInputFiles.begin();
        gGlobal->gMasterDirectory = fileDirname(gGlobal->gMasterDocument);
        gGlobal->gMasterName      = fxName(gGlobal->gMasterDocument);
        gGlobal->gDocName         = fxName(gGlobal->gMasterDocument);
    }

    // Add gMasterDirectory in gImportDirList and gArchitectureDirList
    gGlobal->gImportDirList.push_back(gGlobal->gMasterDirectory);
    gGlobal->gArchitectureDirList.push_back(gGlobal->gMasterDirectory);
}

static void parseSourceFiles()
{
    startTiming("parser");

    list<string>::iterator s;
    Tree result = gGlobal->nil;
    gGlobal->gReader.init();

    if (!gGlobal->gInjectFlag && gGlobal->gInputFiles.begin() == gGlobal->gInputFiles.end()) {
        throw faustexception("ERROR : no files specified; for help type \"faust --help\"\n");
    }
    for (s = gGlobal->gInputFiles.begin(); s != gGlobal->gInputFiles.end(); s++) {
        if (s == gGlobal->gInputFiles.begin()) {
            gGlobal->gMasterDocument = *s;
        }
        result = cons(importFile(tree(s->c_str())), result);
    }

    gGlobal->gExpandedDefList = gGlobal->gReader.expandList(result);
    endTiming("parser");
}

static Tree evaluateBlockDiagram(Tree expandedDefList, int& numInputs, int& numOutputs)
{
    startTiming("evaluation");

    Tree process = evalprocess(expandedDefList);
    if (gGlobal->gErrorCount > 0) {
        stringstream error;
        error << "ERROR : total of " << gGlobal->gErrorCount << " errors during the compilation of "
              << gGlobal->gMasterDocument << endl;
        throw faustexception(error.str());
    }

    if (gGlobal->gDetailsSwitch) {
        cout << "process = " << boxpp(process) << ";\n";
    }

    if (!getBoxType(process, &numInputs, &numOutputs)) {
        stringstream error;
        error << "ERROR during the evaluation of process : " << boxpp(process) << endl;
        throw faustexception(error.str());
    }

    if (gGlobal->gDrawPSSwitch) {
        drawSchema(process, subst("$0-ps", gGlobal->makeDrawPathNoExt()).c_str(), "ps");
    }

    if (gGlobal->gDrawSVGSwitch) {
        drawSchema(process, subst("$0-svg", gGlobal->makeDrawPathNoExt()).c_str(), "svg");
    }

    if (gGlobal->gDetailsSwitch) {
        cout << "process has " << numInputs << " inputs, and " << numOutputs << " outputs" << endl;
    }

    endTiming("evaluation");

    if (gGlobal->gPrintFileListSwitch) {
        cout << "---------------------------\n";
        cout << "List of file dependencies :\n";
        cout << "---------------------------\n";
        // print the pathnames of the files used to evaluate process
        vector<string> pathnames = gGlobal->gReader.listSrcFiles();
        for (size_t i = 0; i < pathnames.size(); i++) cout << pathnames[i] << endl;
        cout << "---------------------------\n";
        cout << endl;
    }

    return process;
}

static void includeFile(const string& file, ostream& dst)
{
    unique_ptr<ifstream> file_include = openArchStream(file.c_str());
    if (file_include) {
        streamCopyUntilEnd(*file_include.get(), dst);
    }
}

static void injectCode(unique_ptr<ifstream>& enrobage, ostream& dst)
{
    /****************************************************************
     1.7 - Inject code instead of compile
     *****************************************************************/

    // Check if this is a code injection
    if (gGlobal->gInjectFlag) {
        if (gGlobal->gArchFile == "") {
            stringstream error;
            error << "ERROR : no architecture file specified to inject \"" << gGlobal->gInjectFile << "\"" << endl;
            throw faustexception(error.str());
        } else {
            streamCopyUntil(*enrobage.get(), dst, "<<includeIntrinsic>>");
            container->printMacros(dst, 0);
            streamCopyUntil(*enrobage.get(), dst, "<<includeclass>>");
            streamCopyUntilEnd(*injcode.get(), dst);
            streamCopyUntilEnd(*enrobage.get(), dst);
        }
        throw faustexception("");
    }
}

static void compileCLLVM(Tree signals, int numInputs, int numOutputs)
{
#ifdef CLANG_BUILD
    // FIR is generated with internal real instead of FAUSTFLOAT (see InstBuilder::genBasicTyped)
    gGlobal->gFAUSTFLOAT2Internal = true;

    container = ClangCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs);

    // To trigger 'sig.dot' generation
    if (gGlobal->gVectorSwitch) {
        new_comp = new DAGInstructionsCompiler(container);
    } else {
        new_comp = new InstructionsCompiler(container);
    }
    new_comp->prepare(signals);
#else
    throw faustexception("ERROR : -lang cllcm not supported since LLVM backend is not built\n");
#endif
}

static void compileLLVM(Tree signals, int numInputs, int numOutputs, bool generate)
{
#ifdef LLVM_BUILD
    container = LLVMCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs);

    // libc functions will be found by the LLVM linker, but not user defined ones...
    gGlobal->gAllowForeignFunction = false;
    // FIR is generated with internal real instead of FAUSTFLOAT (see InstBuilder::genBasicTyped)
    gGlobal->gFAUSTFLOAT2Internal = true;
    gGlobal->gUseDefaultSound     = false;

    if (gGlobal->gVectorSwitch) {
        new_comp = new DAGInstructionsCompiler(container);
    } else {
        new_comp = new InstructionsCompiler(container);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) new_comp->setDescription(new Description());

    if (generate) {
        new_comp->compileMultiSignal(signals);
    } else {
        // To trigger 'sig.dot' generation
        new_comp->prepare(signals);
    }
#else
    throw faustexception("ERROR : -lang llvm not supported since LLVM backend is not built\n");
#endif
}

static void compileInterp(Tree signals, int numInputs, int numOutputs)
{
#ifdef INTERP_BUILD
    if (gGlobal->gFloatSize == 1) {
        container = InterpreterCodeContainer<float>::createContainer(gGlobal->gClassName, numInputs, numOutputs);
    } else if (gGlobal->gFloatSize == 2) {
        container = InterpreterCodeContainer<double>::createContainer(gGlobal->gClassName, numInputs, numOutputs);
    } else {
        throw faustexception("ERROR : quad format not supported in Interp\n");
    }
    gGlobal->gAllowForeignFunction = false;  // No foreign functions
    gGlobal->gAllowForeignConstant = false;  // No foreign constant
    gGlobal->gAllowForeignVar      = false;  // No foreign variable
    // gGlobal->gComputeIOTA       = true;   // Ensure IOTA base fixed delays are computed once

    // FIR is generated with internal real instead of FAUSTFLOAT (see InstBuilder::genBasicTyped)
    gGlobal->gFAUSTFLOAT2Internal = true;
    gGlobal->gNeedManualPow       = false;  // Standard pow function will be used in pow(x,y) when Y in an integer
    gGlobal->gRemoveVarAddress    = true;   // To be used in -vec mode

    if (gGlobal->gVectorSwitch) {
        new_comp = new DAGInstructionsCompiler(container);
    } else {
        new_comp = new InterpreterInstructionsCompiler(container);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) new_comp->setDescription(new Description());
    new_comp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang interp not supported since Interpreter backend is not built\n");
#endif
}

static void compileFIR(Tree signals, int numInputs, int numOutputs, ostream* out)
{
#ifdef FIR_BUILD
    container = FIRCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, out, true);

    if (gGlobal->gVectorSwitch) {
        new_comp = new DAGInstructionsCompiler(container);
    } else {
        new_comp = new InstructionsCompiler(container);
    }

    new_comp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang fir not supported since FIR backend is not built\n");
#endif
}

static void compileC(Tree signals, int numInputs, int numOutputs, ostream* out)
{
#ifdef C_BUILD
    container = CCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, out);

    if (gGlobal->gVectorSwitch) {
        new_comp = new DAGInstructionsCompiler(container);
    } else {
        new_comp = new InstructionsCompiler(container);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) new_comp->setDescription(new Description());
    new_comp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang c not supported since C backend is not built\n");
#endif
}

static void compileCPP(Tree signals, int numInputs, int numOutputs, ostream* out)
{
#ifdef CPP_BUILD
    container =
        CPPCodeContainer::createContainer(gGlobal->gClassName, gGlobal->gSuperClassName, numInputs, numOutputs, out);

    if (gGlobal->gVectorSwitch) {
        new_comp = new DAGInstructionsCompiler(container);
    } else {
        new_comp = new InstructionsCompiler(container);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) new_comp->setDescription(new Description());
    new_comp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang cpp not supported since CPP backend is not built\n");
#endif
}

static void compileOCPP(Tree signals, int numInputs, int numOutputs)
{
#ifdef OCPP_BUILD
    if (gGlobal->gSchedulerSwitch) {
        old_comp = new SchedulerCompiler(gGlobal->gClassName, gGlobal->gSuperClassName, numInputs, numOutputs);
    } else if (gGlobal->gVectorSwitch) {
        old_comp = new VectorCompiler(gGlobal->gClassName, gGlobal->gSuperClassName, numInputs, numOutputs);
    } else {
        old_comp = new ScalarCompiler(gGlobal->gClassName, gGlobal->gSuperClassName, numInputs, numOutputs);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) old_comp->setDescription(new Description());
    old_comp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang ocpp not supported since old CPP backend is not built\n");
#endif
}

static void compileRust(Tree signals, int numInputs, int numOutputs, ostream* out)
{
#ifdef RUST_BUILD
    // FIR is generated with internal real instead of FAUSTFLOAT (see InstBuilder::genBasicTyped)
    gGlobal->gFAUSTFLOAT2Internal = true;
    container                     = RustCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, out);

    if (gGlobal->gVectorSwitch) {
        new_comp = new DAGInstructionsCompiler(container);
    } else {
        new_comp = new InstructionsCompiler1(container);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) new_comp->setDescription(new Description());
    new_comp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang rust not supported since Rust backend is not built\n");
#endif
}

static void compileJava(Tree signals, int numInputs, int numOutputs, ostream* out)
{
#ifdef JAVA_BUILD
    gGlobal->gAllowForeignFunction = false;  // No foreign functions
    container =
        JAVACodeContainer::createContainer(gGlobal->gClassName, gGlobal->gSuperClassName, numInputs, numOutputs, out);

    if (gGlobal->gVectorSwitch) {
        new_comp = new DAGInstructionsCompiler(container);
    } else {
        new_comp = new InstructionsCompiler(container);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) new_comp->setDescription(new Description());
    new_comp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang java not supported since JAVA backend is not built\n");
#endif
}

static void compileJulia(Tree signals, int numInputs, int numOutputs, ostream* out)
{
#ifdef JULIA_BUILD
    gGlobal->gAllowForeignFunction = false;  // No foreign functions
    container = JuliaCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, out);

    if (gGlobal->gVectorSwitch) {
        new_comp = new DAGInstructionsCompiler(container);
    } else {
        new_comp = new InstructionsCompiler1(container);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) new_comp->setDescription(new Description());
    new_comp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang julia not supported since Julia backend is not built\n");
#endif
}

static void compileJAX(Tree signals, int numInputs, int numOutputs, ostream* out)
{
#ifdef JAX_BUILD
    gGlobal->gAllowForeignFunction = true;  // foreign functions are supported (we use jax.random.PRNG for example)
    gGlobal->gNeedManualPow        = false;
    gGlobal->gFAUSTFLOAT2Internal  = true;
    container = JAXCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, out);
    
    if (gGlobal->gVectorSwitch) {
        new_comp = new DAGInstructionsCompiler(container);
    } else {
        new_comp = new InstructionsCompilerJAX(container);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) new_comp->setDescription(new Description());
    new_comp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang jax not supported since JAX backend is not built\n");
#endif
}

static void compileTemplate(Tree signals, int numInputs, int numOutputs, ostream* out)
{
#ifdef TEMPLATE_BUILD
    // Backend configuration
    gGlobal->gAllowForeignFunction = true;
    gGlobal->gNeedManualPow        = false;
    gGlobal->gFAUSTFLOAT2Internal  = true;
    container = TemplateCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, out);
    
    if (gGlobal->gVectorSwitch) {
        new_comp = new DAGInstructionsCompiler(container);
    } else {
        new_comp = new InstructionsCompiler(container);
    }
    
    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) new_comp->setDescription(new Description());
    new_comp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang temp not supported since Template backend is not built\n");
#endif
}

static void compileCSharp(Tree signals, int numInputs, int numOutputs, ostream* out)
{
#ifdef CSHARP_BUILD
    gGlobal->gAllowForeignFunction = false;  // No foreign functions
    container =
        CSharpCodeContainer::createContainer(gGlobal->gClassName, gGlobal->gSuperClassName, numInputs, numOutputs, out);

    if (gGlobal->gVectorSwitch) {
        new_comp = new DAGInstructionsCompiler(container);
    } else {
        new_comp = new InstructionsCompiler(container);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) new_comp->setDescription(new Description());
    new_comp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang csharp not supported since CSharp backend is not built\n");
#endif
}

static void compileCmajor(Tree signals, int numInputs, int numOutputs, ostream* out)
{
#ifdef CMAJOR_BUILD
    gGlobal->gAllowForeignFunction = false;  // No foreign functions
    gGlobal->gAllowForeignConstant = false;  // No foreign constant
    gGlobal->gAllowForeignVar      = false;  // No foreign variable

    // FIR is generated with internal real instead of FAUSTFLOAT (see InstBuilder::genBasicTyped)
    gGlobal->gFAUSTFLOAT2Internal = true;

    // "one sample control" model by default;
    gGlobal->gOneSampleControl = true;
    gGlobal->gNeedManualPow    = false;  // Standard pow function will be used in pow(x,y) when Y in an integer
    container = CmajorCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, out);
    if (gGlobal->gVectorSwitch) {
        new_comp = new DAGInstructionsCompiler(container);
    } else {
        new_comp = new InstructionsCompiler(container);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) new_comp->setDescription(new Description());
    new_comp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang cmajor not supported since Cmajor backend is not built\n");
#endif
}

static void createHelperFile(const string& outpath)
{
    // Additional file with JS code
    if (gGlobal->gOutputFile == "binary") {
        // Nothing
    } else if (gGlobal->gOutputFile != "") {
        string outpath_js;
        bool   res = replaceExtension(outpath, ".js", outpath_js);
        if (res) {
            helpers = unique_ptr<ostream>(new ofstream(outpath_js.c_str()));
        } else {
            cerr << "WARNING : cannot generate helper JS file, outpath is incorrect : \"" << outpath << "\"" << endl;
        }
    } else {
        helpers = unique_ptr<ostream>(new ostringstream());
    }
}

static void compileWAST(Tree signals, int numInputs, int numOutputs, ostream* out, const string& outpath)
{
#ifdef WASM_BUILD
    gGlobal->gAllowForeignFunction = false;  // No foreign functions
    gGlobal->gAllowForeignConstant = false;  // No foreign constant
    gGlobal->gAllowForeignVar      = false;  // No foreign variable

    // FIR is generated with internal real instead of FAUSTFLOAT (see InstBuilder::genBasicTyped)
    gGlobal->gFAUSTFLOAT2Internal = true;
    // the 'i' variable used in the scalar loop moves by bytes instead of frames
    gGlobal->gLoopVarInBytes   = true;
    gGlobal->gWaveformInDSP    = true;   // waveform are allocated in the DSP and not as global data
    gGlobal->gMachinePtrSize   = 4;      // WASM is currently 32 bits
    gGlobal->gNeedManualPow    = false;  // Standard pow function will be used in pow(x,y) when Y in an integer
    gGlobal->gRemoveVarAddress = true;   // To be used in -vec mode
                                       // gGlobal->gHasTeeLocal = true;     // combined store/load

    gGlobal->gUseDefaultSound = false;

    // This speedup (freeverb for instance) ==> to be done at signal level
    // gGlobal->gComputeIOTA = true;     // Ensure IOTA base fixed delays are computed once

    container =
        WASTCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, out,
                                           ((gGlobal->gOutputLang == "wast") || (gGlobal->gOutputLang == "wast-i")));
    createHelperFile(outpath);

    if (gGlobal->gVectorSwitch) {
        new_comp = new DAGInstructionsCompiler(container);
    } else {
        new_comp = new InstructionsCompiler(container);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) new_comp->setDescription(new Description());
    new_comp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang wast not supported since WAST backend is not built\n");
#endif
}

static void compileWASM(Tree signals, int numInputs, int numOutputs, ostream* out, const string& outpath)
{
#ifdef WASM_BUILD
    gGlobal->gAllowForeignFunction = false;  // No foreign functions
    gGlobal->gAllowForeignConstant = false;  // No foreign constant
    gGlobal->gAllowForeignVar      = false;  // No foreign variable

    // FIR is generated with internal real instead of FAUSTFLOAT (see InstBuilder::genBasicTyped)
    gGlobal->gFAUSTFLOAT2Internal = true;
    // the 'i' variable used in the scalar loop moves by bytes instead of frames
    gGlobal->gLoopVarInBytes   = true;
    gGlobal->gWaveformInDSP    = true;   // waveform are allocated in the DSP and not as global data
    gGlobal->gMachinePtrSize   = 4;      // WASM is currently 32 bits
    gGlobal->gNeedManualPow    = false;  // Standard pow function will be used in pow(x,y) when Y in an integer
    gGlobal->gRemoveVarAddress = true;   // To be used in -vec mode
                                       // gGlobal->gHasTeeLocal = true;     // combined store/load

    gGlobal->gUseDefaultSound = false;

    // This speedup (freeverb for instance) ==> to be done at signal level
    // gGlobal->gComputeIOTA = true;     // Ensure IOTA base fixed delays are computed once

    container =
        WASMCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, out,
                                           ((gGlobal->gOutputLang == "wasm") || (gGlobal->gOutputLang == "wasm-i") ||
                                            (gGlobal->gOutputLang == "wasm-ib")));
    createHelperFile(outpath);

    if (gGlobal->gVectorSwitch) {
        new_comp = new DAGInstructionsCompiler(container);
    } else {
        new_comp = new InstructionsCompiler(container);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) new_comp->setDescription(new Description());
    new_comp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang wasm not supported since WASM backend is not built\n");
#endif
}

static void compileDlang(Tree signals, int numInputs, int numOutputs, ostream* out)
{
#ifdef DLANG_BUILD
    container =
        DLangCodeContainer::createContainer(gGlobal->gClassName, gGlobal->gSuperClassName, numInputs, numOutputs, out);

    if (gGlobal->gVectorSwitch) {
        new_comp = new DAGInstructionsCompiler(container);
    } else {
        new_comp = new InstructionsCompiler(container);
    }

    if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) new_comp->setDescription(new Description());
    new_comp->compileMultiSignal(signals);
#else
    throw faustexception("ERROR : -lang dlang not supported since D backend is not built\n");
#endif
}

static void generateCodeAux1(unique_ptr<ostream>& dst)
{
    if (gGlobal->gArchFile != "") {
        if ((enrobage = openArchStream(gGlobal->gArchFile.c_str()))) {
            if (gGlobal->gNamespace != "" && gGlobal->gOutputLang == "cpp")
                *dst.get() << "namespace " << gGlobal->gNamespace << " {" << endl;
#ifdef DLANG_BUILD
            else if (gGlobal->gOutputLang == "dlang") {
                DLangCodeContainer::printDRecipeComment(*dst.get(), container->getClassName());
                DLangCodeContainer::printDModuleStmt(*dst.get(), container->getClassName());
            }
#endif

            // Possibly inject code
            injectCode(enrobage, *dst.get());

            container->printHeader();

            streamCopyUntil(*enrobage.get(), *dst.get(), "<<includeIntrinsic>>");
            streamCopyUntil(*enrobage.get(), *dst.get(), "<<includeclass>>");

            if (gGlobal->gOpenCLSwitch || gGlobal->gCUDASwitch) {
                includeFile("thread.h", *dst.get());
            }

            container->printFloatDef();
            container->produceClass();

            streamCopyUntilEnd(*enrobage.get(), *dst.get());

            if (gGlobal->gSchedulerSwitch) {
                includeFile("scheduler.cpp", *dst.get());
            }

            container->printFooter();

            // Generate factory
            gGlobal->gDSPFactory = container->produceFactory();

            if (gGlobal->gOutputFile == "string") {
                gGlobal->gDSPFactory->write(dst.get(), false, false);
            } else if (gGlobal->gOutputFile == "binary") {
                gGlobal->gDSPFactory->write(dst.get(), true, false);
            } else if (gGlobal->gOutputFile != "") {
                // Binary mode for LLVM backend if output different of 'cout'
                gGlobal->gDSPFactory->write(dst.get(), true, false);
            } else {
                gGlobal->gDSPFactory->write(&cout, false, false);
            }

            if (gGlobal->gNamespace != "" && gGlobal->gOutputLang == "cpp") {
                *dst.get() << "} // namespace " << gGlobal->gNamespace << endl;
            }

        } else {
            stringstream error;
            error << "ERROR : can't open architecture file " << gGlobal->gArchFile << endl;
            throw faustexception(error.str());
        }

    } else {
        container->printHeader();
        container->printFloatDef();
        container->produceClass();
        container->printFooter();

        // Generate factory
        gGlobal->gDSPFactory = container->produceFactory();

        if (gGlobal->gOutputFile == "string") {
            gGlobal->gDSPFactory->write(dst.get(), false, false);
            if (helpers) gGlobal->gDSPFactory->writeHelper(helpers.get(), false, false);
        } else if (gGlobal->gOutputFile == "binary") {
            gGlobal->gDSPFactory->write(dst.get(), true, false);
            if (helpers) gGlobal->gDSPFactory->writeHelper(helpers.get(), true, false);
        } else if (gGlobal->gOutputFile != "") {
            // Binary mode for LLVM backend if output different of 'cout'
            gGlobal->gDSPFactory->write(dst.get(), true, false);
            if (helpers) gGlobal->gDSPFactory->writeHelper(helpers.get(), false, false);
        } else {
            gGlobal->gDSPFactory->write(&cout, false, false);
            if (helpers) gGlobal->gDSPFactory->writeHelper(&cout, false, false);
        }
    }
}

#ifdef OCPP_BUILD

static void printHeader(ostream& dst)
{
    // defines the metadata we want to print as comments at the begin of in the C++ file
    set<Tree> selectedKeys;
    selectedKeys.insert(tree("name"));
    selectedKeys.insert(tree("author"));
    selectedKeys.insert(tree("copyright"));
    selectedKeys.insert(tree("license"));
    selectedKeys.insert(tree("version"));

    dst << "//----------------------------------------------------------" << endl;
    for (const auto& i : gGlobal->gMetaDataSet) {
        if (selectedKeys.count(i.first)) {
            dst << "// " << *(i.first);
            const char* sep = ": ";
            for (const auto& j : i.second) {
                dst << sep << *j;
                sep = ", ";
            }
            dst << endl;
        }
    }

    dst << "//" << endl;
    dst << "// Code generated with Faust " << FAUSTVERSION << " (https://faust.grame.fr)" << endl;
    dst << "//----------------------------------------------------------" << endl << endl;
}

static void generateCodeAux2(unique_ptr<ostream>& dst)
{
    // Check for architecture file
    if (gGlobal->gArchFile != "") {
        if ((enrobage = openArchStream(gGlobal->gArchFile.c_str())) == nullptr) {
            stringstream error;
            error << "ERROR : can't open architecture file " << gGlobal->gArchFile << endl;
            throw faustexception(error.str());
        }
    }

    // Possibly inject code
    injectCode(enrobage, *dst.get());

    printHeader(*dst);
    old_comp->getClass()->printLibrary(*dst.get());
    old_comp->getClass()->printIncludeFile(*dst.get());
    old_comp->getClass()->printAdditionalCode(*dst.get());

    if (gGlobal->gArchFile != "") {
        streamCopyUntil(*enrobage.get(), *dst.get(), "<<includeIntrinsic>>");

        if (gGlobal->gSchedulerSwitch) {
            unique_ptr<ifstream> scheduler_include = openArchStream("old-scheduler.cpp");
            if (scheduler_include) {
                streamCopyUntilEnd(*scheduler_include, *dst.get());
            } else {
                throw("ERROR : can't include \"old-scheduler.cpp\", file not found>\n");
            }
        }

        streamCopyUntil(*enrobage.get(), *dst.get(), "<<includeclass>>");
        printfloatdef(*dst.get());
        old_comp->getClass()->println(0, *dst.get());
        streamCopyUntilEnd(*enrobage.get(), *dst.get());

    } else {
        printfloatdef(*dst.get());
        old_comp->getClass()->println(0, *dst.get());
    }

    /****************************************************************
     9 - generate the task graph file in dot format
     *****************************************************************/

    if (gGlobal->gGraphSwitch) {
        ofstream dotfile(subst("$0.dot", gGlobal->makeDrawPath()).c_str());
        old_comp->getClass()->printGraphDotFormat(dotfile);
    }

    if (gGlobal->gOutputFile == "") {
        cout << dynamic_cast<ostringstream*>(dst.get())->str();
    }
}

#endif

static void generateCode(Tree signals, int numInputs, int numOutputs, bool generate)
{
    /*******************************************************************
     MANDATORY: use ostringstream which is indeed a subclass of ostream
     (otherwise subtle dynamic_cast related crash can occur...)
    *******************************************************************/

    unique_ptr<ostream> dst;
    string              outpath;

    if (gGlobal->gOutputFile == "string") {
        dst = unique_ptr<ostream>(new ostringstream());
    } else if (gGlobal->gOutputFile == "binary") {
        dst = unique_ptr<ostream>(new ostringstream(ostringstream::out | ostringstream::binary));
    } else if (gGlobal->gOutputFile != "") {
        outpath =
            (gGlobal->gOutputDir != "") ? (gGlobal->gOutputDir + "/" + gGlobal->gOutputFile) : gGlobal->gOutputFile;

        unique_ptr<ofstream> fdst = unique_ptr<ofstream>(new ofstream(outpath.c_str()));
        if (!fdst->is_open()) {
            stringstream error;
            error << "ERROR : file '" << outpath << "' cannot be opened\n";
            throw faustexception(error.str());
        } else {
            dst = move(fdst);
        }

    } else {
        dst = unique_ptr<ostream>(new ostringstream());
    }

    startTiming("generateCode");

    /****************************************************************
     * create container
     ****************************************************************/

    if (gGlobal->gOutputLang == "cllvm") {
        compileCLLVM(signals, numInputs, numOutputs);
    } else if (gGlobal->gOutputLang == "llvm") {
        compileLLVM(signals, numInputs, numOutputs, generate);
    } else if (gGlobal->gOutputLang == "interp") {
        compileInterp(signals, numInputs, numOutputs);
    } else if (gGlobal->gOutputLang == "fir") {
        compileFIR(signals, numInputs, numOutputs, dst.get());
    } else if (gGlobal->gOutputLang == "c") {
        compileC(signals, numInputs, numOutputs, dst.get());
    } else if (gGlobal->gOutputLang == "cpp") {
        compileCPP(signals, numInputs, numOutputs, dst.get());
    } else if (gGlobal->gOutputLang == "ocpp") {
        compileOCPP(signals, numInputs, numOutputs);
    } else if (gGlobal->gOutputLang == "rust") {
        compileRust(signals, numInputs, numOutputs, dst.get());
    } else if (gGlobal->gOutputLang == "java") {
        compileJava(signals, numInputs, numOutputs, dst.get());
    } else if (gGlobal->gOutputLang == "jax") {
        compileJAX(signals, numInputs, numOutputs, dst.get());
    } else if (gGlobal->gOutputLang == "temp") {
        compileTemplate(signals, numInputs, numOutputs, dst.get());
    } else if (gGlobal->gOutputLang == "julia") {
        compileJulia(signals, numInputs, numOutputs, dst.get());
    } else if (gGlobal->gOutputLang == "csharp") {
        compileCSharp(signals, numInputs, numOutputs, dst.get());
    } else if (startWith(gGlobal->gOutputLang, "cmajor")) {
        compileCmajor(signals, numInputs, numOutputs, dst.get());
    } else if (startWith(gGlobal->gOutputLang, "wast")) {
        compileWAST(signals, numInputs, numOutputs, dst.get(), outpath);
    } else if (startWith(gGlobal->gOutputLang, "wasm")) {
        compileWASM(signals, numInputs, numOutputs, dst.get(), outpath);
    } else if (startWith(gGlobal->gOutputLang, "dlang")) {
        compileDlang(signals, numInputs, numOutputs, dst.get());
    } else {
        stringstream error;
        error << "ERROR : cannot find backend for "
              << "\"" << gGlobal->gOutputLang << "\"" << endl;
        throw faustexception(error.str());
    }

    /****************************************************************
     * generate output file
     ****************************************************************/

    if (new_comp) {
        generateCodeAux1(dst);
    }
#ifdef OCPP_BUILD
    else if (old_comp) {
        generateCodeAux2(dst);
    }
#endif
    else {
        faustassert(false);
    }

    endTiming("generateCode");
}

static void printXML(Description* D, int inputs, int outputs)
{
    faustassert(D);
    ofstream xout(subst("$0.xml", gGlobal->makeDrawPath()).c_str());

    MetaDataSet::const_iterator it1;
    set<Tree>::const_iterator   it2;
    for (const auto& it1 : gGlobal->gMetaDataSet) {
        const string key = tree2str(it1.first);
        for (it2 = it1.second.begin(); it2 != it1.second.end(); ++it2) {
            const string value = tree2str(*it2);
            if (key == "name") {
                D->name(value);
            } else if (key == "author") {
                D->author(value);
            } else if (key == "copyright") {
                D->copyright(value);
            } else if (key == "license") {
                D->license(value);
            } else if (key == "version") {
                D->version(value);
            } else {
                D->declare(key, value);
            }
        }
    }

    D->className(gGlobal->gClassName);
    D->inputs(inputs);
    D->outputs(outputs);
    D->print(0, xout);
}

static void generateOutputFiles()
{
    /****************************************************************
     1 - generate XML description (if required)
    *****************************************************************/

    if (gGlobal->gPrintXMLSwitch) {
        if (new_comp) {
            printXML(new_comp->getDescription(), container->inputs(), container->outputs());
        }
#ifdef OCPP_BUILD
        else if (old_comp) {
            printXML(old_comp->getDescription(), old_comp->getClass()->inputs(), old_comp->getClass()->outputs());
        }
#endif
        else {
            faustassert(false);
        }
    }

    /****************************************************************
     2 - generate documentation from Faust comments (if required)
    *****************************************************************/

    if (gGlobal->gPrintDocSwitch && gGlobal->gLatexDocSwitch) {
        printDoc(subst("$0-mdoc", gGlobal->makeDrawPathNoExt()).c_str(), "tex", FAUSTVERSION);
    }

    /****************************************************************
     3 - generate the task graph file in dot format
    *****************************************************************/

    if (gGlobal->gGraphSwitch) {
        ofstream dotfile(subst("$0.dot", gGlobal->makeDrawPath()).c_str());
        if (new_comp) {
            container->printGraphDotFormat(dotfile);
        }
#ifdef OCPP_BUILD
        else if (old_comp) {
            old_comp->getClass()->printGraphDotFormat(dotfile);
        }
#endif
        else {
            faustassert(false);
        }
    }
}

static void expandDSPInternalAux(Tree process_tree, int argc, const char* argv[], ostream& out)
{
    // Encode compilation options as a 'declare' : has to be located first in the string
    out << "declare version \"" << FAUSTVERSION << "\";" << endl;
    out << COMPILATION_OPTIONS << reorganizeCompilationOptions(argc, argv) << ';' << endl;

    // Encode all libraries paths as 'declare'
    vector<string> pathnames = gGlobal->gReader.listSrcFiles();
    // Remove DSP filename
    pathnames.erase(pathnames.begin());
    int i = 0;
    for (const auto& it : pathnames) {
        out << "declare library_path" << to_string(i++) << " \"" << it << "\";" << endl;
    }

    printDeclareHeader(out);
    boxppShared(process_tree, out);
}

static void* expandDSPInternal(void* arg)
{
    try {
        CallContext* context = static_cast<CallContext*>(arg);
        string name_app = context->fNameApp;
        string dsp_content = context->fDSPContent;
        int argc = context->fArgc;
        const char** argv = context->fArgv;
        
        /****************************************************************
         1 - process command line
        *****************************************************************/
        initFaustDirectories(argc, argv);
        processCmdline(argc, argv);

        /****************************************************************
         2 - parse source files
        *****************************************************************/
        if (dsp_content != "") {
            gGlobal->gInputString = dsp_content;
            gGlobal->gInputFiles.push_back(name_app);
        }
        initDocumentNames();
        initFaustFloat();

        parseSourceFiles();

        /****************************************************************
         3 - evaluate 'process' definition
        *****************************************************************/
        int numInputs;
        int numOutputs;
        Tree processTree = evaluateBlockDiagram(gGlobal->gExpandedDefList, numInputs, numOutputs);
        
        stringstream out;
        expandDSPInternalAux(processTree, argc, argv, out);
        context->fRes = out.str();
        return nullptr;
        
    } catch (faustexception& e) {
        gGlobal->gErrorMessage = e.Message();
        return nullptr;
    }
}

static void* evaluateBlockDiagram2(void* arg)
{
    CallContext* context = static_cast<CallContext*>(arg);
    try {
        context->fTree = evaluateBlockDiagram(gGlobal->gExpandedDefList, context->fNumInputs, context->fNumOutputs);
        return nullptr;
    } catch (faustexception& e) {
        context->fTree = nullptr;
        gGlobal->gErrorMessage = e.Message();
        return nullptr;
    }
}

LIBFAUST_API Tree DSPToBoxes(const string& name_app, const string& dsp_content, int argc, const char* argv[], int* inputs, int* outputs, string& error_msg)
{
    int argc1 = 0;
    const char* argv1[64];
    argv1[argc1++] = "faust";
    
    // Copy arguments
    for (int i = 0; i < argc; i++) {
        argv1[argc1++] = argv[i];
    }
    argv1[argc1] = nullptr;  // NULL terminated argv
    
    /****************************************************************
     1 - process command line
     *****************************************************************/
    initFaustDirectories(argc1, argv1);
    processCmdline(argc1, argv1);

    faust_alarm(gGlobal->gTimeout);

    /****************************************************************
     2 - parse source files
     *****************************************************************/
    if (dsp_content.c_str()) {
        gGlobal->gInputString = dsp_content;
        gGlobal->gInputFiles.push_back(name_app);
    }
    initDocumentNames();
    initFaustFloat();

    try {
        parseSourceFiles();
    } catch (faustexception& e) {
        error_msg = e.what();
        return nullptr;
    }

    /****************************************************************
     3 - evaluate 'process' definition
     *****************************************************************/
    CallContext context;
    callFun(evaluateBlockDiagram2, &context);
    if (context.fTree) {
        *inputs = context.fNumInputs;
        *outputs = context.fNumOutputs;
        return context.fTree;
    } else {
        return nullptr;
    }
}

static void* createFactoryAux1(void* arg)
{
    try {
        CallContext* context = static_cast<CallContext*>(arg);
        string name_app = context->fNameApp;
        string dsp_content = context->fDSPContent;
        int argc = context->fArgc;
        const char** argv = context->fArgv;
        bool generate = context->fGenerate;
        
        /****************************************************************
         1 - process command line
        *****************************************************************/
        initFaustDirectories(argc, argv);
        processCmdline(argc, argv);

        if (gGlobal->gHelpSwitch) {
            printHelp();
            throw faustexception("");
        }
        if (gGlobal->gVersionSwitch) {
            printVersion();
            throw faustexception("");
        }
        if (gGlobal->gLibDirSwitch) {
            printLibDir();
            throw faustexception("");
        }
        if (gGlobal->gIncludeDirSwitch) {
            printIncludeDir();
            throw faustexception("");
        }
        if (gGlobal->gArchDirSwitch) {
            printArchDir();
            throw faustexception("");
        }
        if (gGlobal->gDspDirSwitch) {
            printDspDir();
            throw faustexception("");
        }
        if (gGlobal->gPathListSwitch) {
            printPaths();
            throw faustexception("");
        }

        faust_alarm(gGlobal->gTimeout);

        /****************************************************************
         1.5 - Check and open some input files
        *****************************************************************/
        // Check for injected code (before checking for architectures)
        if (gGlobal->gInjectFlag) {
            injcode = openArchStream(gGlobal->gInjectFile.c_str());
            if (!injcode) {
                stringstream error;
                error << "ERROR : can't inject \"" << gGlobal->gInjectFile << "\" external code file, file not found\n";
                throw faustexception(error.str());
            }
        }

        /****************************************************************
         2 - parse source files
        *****************************************************************/
        if (dsp_content != "") {
            gGlobal->gInputString = dsp_content;
            gGlobal->gInputFiles.push_back(name_app);
        }
        initDocumentNames();
        initFaustFloat();

        parseSourceFiles();

        /****************************************************************
         3 - evaluate 'process' definition
        *****************************************************************/
        int numInputs;
        int numOutputs;
        Tree processTree = evaluateBlockDiagram(gGlobal->gExpandedDefList, numInputs, numOutputs);
        if (numOutputs == 0) {
            throw faustexception("ERROR : the Faust program has no output signal\n");
        }

        /****************************************************************
         3.1 - possibly expand the DSP and return
         *****************************************************************/
        if (gGlobal->gExportDSP) {
            string outpath =
                (gGlobal->gOutputDir != "") ? (gGlobal->gOutputDir + "/" + gGlobal->gOutputFile) : gGlobal->gOutputFile;
            ofstream out(outpath.c_str());
            expandDSPInternalAux(processTree, argc, argv, out);
            return nullptr;
        }

        /****************************************************************
         4 - compute output signals of 'process'
        *****************************************************************/
        startTiming("propagation");

        Tree lsignals = boxPropagateSig(gGlobal->nil, processTree, makeSigInputList(numInputs));

        if (gGlobal->gDetailsSwitch) {
            cout << "output signals are : " << endl;
            printSignal(lsignals, stdout);
            cout << endl << ppsig(lsignals) << endl;
            cout << "\n\n";
        }

        endTiming("propagation");

        /*************************************************************************
        5 - preparation of the signal tree and translate output signals
        **************************************************************************/
        generateCode(lsignals, numInputs, numOutputs, generate);

        /****************************************************************
         6 - generate xml description, documentation or dot files
        *****************************************************************/
        generateOutputFiles();
        
        return nullptr;
        
    } catch (faustexception& e) {
        gGlobal->gErrorMessage = e.Message();
        return nullptr;
    }
}

// Keep the maximum index of inputs signals
struct MaxInputsCounter : public SignalVisitor {
    int fMaxInputs = 0;
    
    MaxInputsCounter(Tree L)
    {
        // L is in normal form
        while (!isNil(L)) {
            self(hd(L));
            L = tl(L);
        }
    }
    
    void visit(Tree sig)
    {
        int input;
        if (isSigInput(sig, &input)) {
            fMaxInputs = std::max(fMaxInputs, input + 1);
        } else {
            SignalVisitor::visit(sig);
        }
    }
};

static void* createFactoryAux2(void* arg)
{
    try {
        CallContext* context = static_cast<CallContext*>(arg);
        string name_app = context->fNameApp;
        Tree signals1 = context->fTree;
        int argc = context->fArgc;
        const char** argv = context->fArgv;
        bool generate = context->fGenerate;
        
        Tree signals2 = simplifyToNormalForm(signals1);
        MaxInputsCounter counter(signals2);
        int numInputs = counter.fMaxInputs;
        int numOutputs = context->fNumOutputs;
        
        /****************************************************************
         1 - process command line
         *****************************************************************/
        initFaustDirectories(argc, argv);
        processCmdline(argc, argv);

        initDocumentNames();
        initFaustFloat();

        /*************************************************************************
         5 - preparation of the signal tree and translate output signals
         **************************************************************************/
        gGlobal->gMetaDataSet[tree("name")].insert(tree(quote(name_app)));
        generateCode(signals2, numInputs, numOutputs, generate);
        
        return nullptr;
        
    } catch (faustexception& e) {
        gGlobal->gErrorMessage = e.Message();
        return nullptr;
    }
}

// ============
// Backend API
// ============

dsp_factory_base* createFactory(const string& name_app,
                                const string& dsp_content,
                                int argc, const char* argv[],
                                string& error_msg,
                                bool generate)
{
    gGlobal = nullptr;
    global::allocate();
    
    // Threaded call
    CallContext context;
    context.fNameApp = name_app;
    context.fDSPContent = dsp_content;
    context.fArgc = argc;
    context.fArgv = argv;
    context.fGenerate = generate;
    callFun(createFactoryAux1, &context);
    dsp_factory_base* factory = gGlobal->gDSPFactory;
    error_msg = gGlobal->gErrorMessage;
   
    global::destroy();
    return factory;
}

dsp_factory_base* createFactory(const string& name_app, tvec signals, int argc, const char* argv[], string& error_msg)
{
    Tree outputs = listConvert(signals);
    // Threaded call
    CallContext context;
    context.fNameApp = name_app;
    context.fTree = outputs;
    context.fArgc = argc;
    context.fArgv = argv;
    context.fNumOutputs = signals.size();
    context.fGenerate = true;
    callFun(createFactoryAux2, &context);
    error_msg = gGlobal->gErrorMessage;
    return gGlobal->gDSPFactory;
}

string expandDSP(const string& name_app,
                 const string& dsp_content,
                 int argc, const char* argv[],
                 string& sha_key,
                 string& error_msg)
{
    gGlobal = nullptr;
    global::allocate();
    
    // Threaded call
    CallContext context;
    context.fNameApp = name_app;
    context.fDSPContent = dsp_content;
    context.fArgc = argc;
    context.fArgv = argv;
    callFun(expandDSPInternal, &context);
    string res = context.fRes;
    sha_key   = generateSHA1(res);
    error_msg = gGlobal->gErrorMessage;
  
    global::destroy();
    return res;
}

// ===============
// Signal C++ API
// ===============

LIBFAUST_API string createSourceFromSignals(const string& name_app, tvec signals,
                                         const string& lang,
                                         int argc, const char* argv[],
                                         string& error_msg)
{
    int         argc1 = 0;
    const char* argv1[64];
    argv1[argc1++] = "faust";
    argv1[argc1++] = "-lang";
    argv1[argc1++] = lang.c_str();
    argv1[argc1++] = "-o";
    argv1[argc1++] = "string";
    
    // Copy arguments
    for (int i = 0; i < argc; i++) {
        argv1[argc1++] = argv[i];
    }
    argv1[argc1] = nullptr;  // NULL terminated argv
    
    dsp_factory_base* factory = createFactory(name_app, signals, argc1, argv1, error_msg);
    if (factory) {
        // Print the textual class
        stringstream str;
        factory->write(&str);
        delete factory;
        return str.str();
    } else {
        // the caller of this function should check that error_msg is blank.
        return "";
    }
}

// Foreign

LIBFAUST_API Tree sigFFun(Tree ff, tvec largs)
{
    return sigFFun(ff, listConvert(largs));
}

enum SType { kSInt, kSReal };

LIBFAUST_API Tree sigFConst(SType type, const string& name, const string& file)
{
    return sigFConst(tree(type), tree(name), tree(file));
}

LIBFAUST_API Tree sigFVar(SType type, const string& name, const string& file)
{
    return sigFVar(tree(type), tree(name), tree(file));
}

// User Interface

LIBFAUST_API Tree sigButton(const string& label)
{
    return sigButton(normalizePath(cons(tree(label), gGlobal->nil)));
}

LIBFAUST_API Tree sigCheckbox(const string& label)
{
    return sigCheckbox(normalizePath(cons(tree(label), gGlobal->nil)));
}

LIBFAUST_API Tree sigVSlider(const string& label, Tree cur, Tree min, Tree max, Tree step)
{
    return sigVSlider(normalizePath(cons(tree(label), gGlobal->nil)), cur, min, max, step);
}

LIBFAUST_API Tree sigHSlider(const string& label, Tree cur, Tree min, Tree max, Tree step)
{
    return sigHSlider(normalizePath(cons(tree(label), gGlobal->nil)), cur, min, max, step);
}

LIBFAUST_API Tree sigNumEntry(const string& label, Tree cur, Tree min, Tree max, Tree step)
{
    return sigNumEntry(normalizePath(cons(tree(label), gGlobal->nil)), cur, min, max, step);
}

LIBFAUST_API Tree sigVBargraph(const string& label, Tree min, Tree max, Tree x)
{
    return sigVBargraph(normalizePath(cons(tree(label), gGlobal->nil)), min, max, x);
}

LIBFAUST_API Tree sigHBargraph(const string& label, Tree min, Tree max, Tree x)
{
    return sigHBargraph(normalizePath(cons(tree(label), gGlobal->nil)), min, max, x);
}

LIBFAUST_API Tree sigSoundfile(const string& label)
{
    return sigSoundfile(normalizePath(cons(tree(label), gGlobal->nil)));
}

LIBFAUST_API Tree sigSelf()
{
    return sigDelay1(sigProj(0, ref(1)));
}

// Tree liftn(Tree t, int threshold);

LIBFAUST_API Tree sigRecursion(Tree s)
{
    // return sigDelay0(sigProj(0, rec(cons(liftn(s, 0), gGlobal->nil))));
    return sigDelay0(sigProj(0, rec(cons(s, gGlobal->nil))));
}

// Global context, to be used in C and C++ API

extern "C" LIBFAUST_API void createLibContext()
{
    gGlobal = nullptr;
    global::allocate();
}

extern "C" LIBFAUST_API void destroyLibContext()
{
    global::destroy();
}

// =============
// Signal C API
// =============

#ifdef __cplusplus
extern "C" {
#endif

LIBFAUST_API bool CisNil(Tree s)
{
    return isNil(s);
}

LIBFAUST_API const char* Ctree2str(Tree s)
{
    return tree2str(s);
}

LIBFAUST_API int Ctree2int(Tree s)
{
    return tree2int(s);
}

LIBFAUST_API void* CgetUserData(Tree s)
{
    return getUserData(s);
}

LIBFAUST_API Tree CsigInt(int n)
{
    return sigInt(n);
}

LIBFAUST_API Tree CsigReal(double n)
{
    return sigReal(n);
}

LIBFAUST_API Tree CsigInput(int idx)
{
    return sigInput(idx);
}

LIBFAUST_API Tree CsigDelay(Tree t0, Tree del)
{
    return sigDelay(t0, del);
}

LIBFAUST_API Tree CsigIntCast(Tree s)
{
    return sigIntCast(s);
}

LIBFAUST_API Tree CsigFloatCast(Tree s)
{
    return sigFloatCast(s);
}

LIBFAUST_API Tree CsigReadOnlyTable(Tree n, Tree init, Tree ridx)
{
    return sigReadOnlyTable(n, init, ridx);
}

LIBFAUST_API Tree CsigWriteReadTable(Tree n, Tree init, Tree widx, Tree wsig, Tree ridx)
{
    return sigWriteReadTable(n, init, widx, wsig, ridx);
}

LIBFAUST_API Tree CsigWaveform(Tree* wf_aux)
{
    tvec wf;
    int  i = 0;
    while (wf_aux[i]) {
        wf.push_back(wf_aux[i]);
        i++;
    }
    return sigWaveform(wf);
}

LIBFAUST_API Tree CsigSoundfile(const char* label)
{
    return sigSoundfile(label);
}

LIBFAUST_API Tree CsigSoundfileLength(Tree sf, Tree part)
{
    return sigSoundfileLength(sf, part);
}

LIBFAUST_API Tree CsigSoundfileRate(Tree sf, Tree part)
{
    return sigSoundfileRate(sf, part);
}

LIBFAUST_API Tree CsigSoundfileBuffer(Tree sf, Tree chan, Tree part, Tree ridx)
{
    return sigSoundfileBuffer(sf, chan, part, ridx);
}

LIBFAUST_API Tree CsigSelect2(Tree selector, Tree s1, Tree s2)
{
    return sigSelect2(selector, s1, s2);
}

LIBFAUST_API Tree CsigSelect3(Tree selector, Tree s1, Tree s2, Tree s3)
{
    return sigSelect3(selector, s1, s2, s3);
}

LIBFAUST_API Tree CsigFConst(SType type, const char* name, const char* file)
{
    return sigFConst(type, name, file);
}

LIBFAUST_API Tree CsigFVar(SType type, const char* name, const char* file)
{
    return sigFVar(type, name, file);
}

LIBFAUST_API Tree CsigBinOp(SOperator op, Tree x, Tree y)
{
    return sigBinOp(op, x, y);
}

LIBFAUST_API Tree CsigAdd(Tree x, Tree y)
{
    return sigAdd(x, y);
}
LIBFAUST_API Tree CsigSub(Tree x, Tree y)
{
    return sigSub(x, y);
}
LIBFAUST_API Tree CsigMul(Tree x, Tree y)
{
    return sigMul(x, y);
}
LIBFAUST_API Tree CsigDiv(Tree x, Tree y)
{
    return sigDiv(x, y);
}
LIBFAUST_API Tree CsigRem(Tree x, Tree y)
{
    return sigRem(x, y);
}

LIBFAUST_API Tree CsigLeftShift(Tree x, Tree y)
{
    return sigLeftShift(x, y);
}
LIBFAUST_API Tree CsigLRightShift(Tree x, Tree y)
{
    return sigLRightShift(x, y);
}
LIBFAUST_API Tree CsigARightShift(Tree x, Tree y)
{
    return sigARightShift(x, y);
}

LIBFAUST_API Tree CsigGT(Tree x, Tree y)
{
    return sigGT(x, y);
}
LIBFAUST_API Tree CsigLT(Tree x, Tree y)
{
    return sigLT(x, y);
}
LIBFAUST_API Tree CsigGE(Tree x, Tree y)
{
    return sigGE(x, y);
}
LIBFAUST_API Tree CsigLE(Tree x, Tree y)
{
    return sigLE(x, y);
}
LIBFAUST_API Tree CsigEQ(Tree x, Tree y)
{
    return sigEQ(x, y);
}
LIBFAUST_API Tree CsigNE(Tree x, Tree y)
{
    return sigNE(x, y);
}

LIBFAUST_API Tree CsigAND(Tree x, Tree y)
{
    return sigAND(x, y);
}
LIBFAUST_API Tree CsigOR(Tree x, Tree y)
{
    return sigOR(x, y);
}
LIBFAUST_API Tree CsigXOR(Tree x, Tree y)
{
    return sigXOR(x, y);
}

LIBFAUST_API Tree CsigAbs(Tree x)
{
    return sigAbs(x);
}
LIBFAUST_API Tree CsigAcos(Tree x)
{
    return sigAcos(x);
}
LIBFAUST_API Tree CsigTan(Tree x)
{
    return sigTan(x);
}
LIBFAUST_API Tree CsigSqrt(Tree x)
{
    return sigSqrt(x);
}
LIBFAUST_API Tree CsigSin(Tree x)
{
    return sigSin(x);
}
LIBFAUST_API Tree CsigRint(Tree x)
{
    return sigRint(x);
}
LIBFAUST_API Tree CsigRemainder(Tree x, Tree y)
{
    return sigRemainder(x, y);
}
LIBFAUST_API Tree CsigPow(Tree x, Tree y)
{
    return sigPow(x, y);
}
LIBFAUST_API Tree CsigMin(Tree x, Tree y)
{
    return sigMin(x, y);
}
LIBFAUST_API Tree CsigMax(Tree x, Tree y)
{
    return sigMax(x, y);
}
LIBFAUST_API Tree CsigLog(Tree x)
{
    return sigLog(x);
}
LIBFAUST_API Tree CsigLog10(Tree x)
{
    return sigLog10(x);
}
LIBFAUST_API Tree CsigFmod(Tree x, Tree y)
{
    return sigFmod(x, y);
}
LIBFAUST_API Tree CsigFloor(Tree x)
{
    return sigFloor(x);
}
LIBFAUST_API Tree CsigExp(Tree x)
{
    return sigExp(x);
}
LIBFAUST_API Tree CsigExp10(Tree x)
{
    return sigExp10(x);
}
LIBFAUST_API Tree CsigCos(Tree x)
{
    return sigCos(x);
}
LIBFAUST_API Tree CsigCeil(Tree x)
{
    return sigCeil(x);
}
LIBFAUST_API Tree CsigAtan(Tree x)
{
    return sigAtan(x);
}
LIBFAUST_API Tree CsigAtan2(Tree x, Tree y)
{
    return sigAtan2(x, y);
}
LIBFAUST_API Tree CsigAsin(Tree x)
{
    return sigAsin(x);
}

LIBFAUST_API Tree CsigSelf()
{
    return sigSelf();
}

LIBFAUST_API Tree CsigRecursion(Tree s1)
{
    return sigRecursion(s1);
}

LIBFAUST_API Tree CsigButton(const char* label)
{
    return sigButton(label);
}

LIBFAUST_API Tree CsigCheckbox(const char* label)
{
    return sigCheckbox(label);
}

LIBFAUST_API Tree CsigVSlider(const char* label, Tree init, Tree min, Tree max, Tree step)
{
    return sigVSlider(label, init, min, max, step);
}

LIBFAUST_API Tree CsigHSlider(const char* label, Tree init, Tree min, Tree max, Tree step)
{
    return sigHSlider(label, init, min, max, step);
}

LIBFAUST_API Tree CsigNumEntry(const char* label, Tree init, Tree min, Tree max, Tree step)
{
    return sigNumEntry(label, init, min, max, step);
}

LIBFAUST_API Tree CsigVBargraph(const char* label, Tree min, Tree max, Tree x)
{
    return sigVBargraph(label, min, max, x);
}

LIBFAUST_API Tree CsigHBargraph(const char* label, Tree min, Tree max, Tree x)
{
    return sigHBargraph(label, min, max, x);
}

LIBFAUST_API Tree CsigAttach(Tree x, Tree y)
{
    return sigAttach(y, y);
}

// Signal test API
LIBFAUST_API bool CisSigInt(Tree t, int* i)
{
    return isSigInt(t, i);
}
LIBFAUST_API bool CisSigReal(Tree t, double* r)
{
    return isSigReal(t, r);
}
LIBFAUST_API bool CisSigInput(Tree t, int* i)
{
    return isSigInput(t, i);
}
LIBFAUST_API bool CisSigOutput(Tree t, int* i, Tree* t0_aux)
{
    Tree t0;
    if (isSigOutput(t, i, t0)) {
        *t0_aux = t0;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigDelay1(Tree t, Tree* t0_aux)
{
    Tree t0;
    if (isSigDelay1(t, t0)) {
        *t0_aux = t0;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigDelay(Tree t, Tree* t0_aux, Tree* t1_aux)
{
    Tree t0, t1;
    if (isSigDelay(t, t0, t1)) {
        *t0_aux = t0;
        *t1_aux = t1;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigPrefix(Tree t, Tree* t0_aux, Tree* t1_aux)
{
    Tree t0, t1;
    if (isSigPrefix(t, t0, t1)) {
        *t0_aux = t0;
        *t1_aux = t1;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigRDTbl(Tree s, Tree* t_aux, Tree* i_aux)
{
    Tree t, i;
    if (isSigRDTbl(s, t, i)) {
        *t_aux = t;
        *i_aux = i;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigWRTbl(Tree u, Tree* id_aux, Tree* t_aux, Tree* i_aux, Tree* s_aux)
{
    Tree id, t, i, s;
    if (isSigWRTbl(u, id, t, i, s)) {
        *id_aux = id;
        *t_aux  = t;
        *i_aux  = i;
        *s_aux  = s;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigTable(Tree t, Tree* id_aux, Tree* n_aux, Tree* sig_aux)
{
    Tree id, n, sig;
    if (isSigTable(t, id, n, sig)) {
        *id_aux  = id;
        *n_aux   = n;
        *sig_aux = sig;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigGen(Tree t, Tree* x_aux)
{
    Tree x;
    if (isSigGen(t, x)) {
        *x_aux = x;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigDocConstantTbl(Tree t, Tree* n_aux, Tree* sig_aux)
{
    Tree n, sig;
    if (isSigDocConstantTbl(t, n, sig)) {
        *n_aux   = n;
        *sig_aux = sig;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigDocWriteTbl(Tree t, Tree* n_aux, Tree* sig_aux, Tree* widx_aux, Tree* wsig_aux)
{
    Tree n, sig, widx, wsig;
    if (isSigDocWriteTbl(t, n, sig, widx, wsig)) {
        *n_aux    = n;
        *sig_aux  = sig;
        *widx_aux = widx;
        *wsig_aux = wsig;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigDocAccessTbl(Tree t, Tree* tbl_aux, Tree* ridx_aux)
{
    Tree tbl, ridx;
    if (isSigDocAccessTbl(t, tbl, ridx)) {
        *tbl_aux  = tbl;
        *ridx_aux = ridx;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigSelect2(Tree t, Tree* selector_aux, Tree* s1_aux, Tree* s2_aux)
{
    Tree selector, s1, s2;
    if (isSigSelect2(t, selector, s1, s2)) {
        *selector_aux = selector;
        *s1_aux       = s1;
        *s2_aux       = s2;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigAssertBounds(Tree t, Tree* s1_aux, Tree* s2_aux, Tree* s3_aux)
{
    Tree s1, s2, s3;
    if (isSigAssertBounds(t, s1, s2, s3)) {
        *s1_aux = s1;
        *s2_aux = s2;
        *s2_aux = s2;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigHighest(Tree t, Tree* s_aux)
{
    Tree s;
    if (isSigHighest(t, s)) {
        *s_aux = s;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigLowest(Tree t, Tree* s_aux)
{
    Tree s;
    if (isSigLowest(t, s)) {
        *s_aux = s;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisSigBinOp(Tree s, int* op, Tree* x_aux, Tree* y_aux)
{
    Tree x, y;
    if (isSigBinOp(s, op, x, y)) {
        *x_aux = x;
        *y_aux = y;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigFFun(Tree s, Tree* ff_aux, Tree* largs_aux)
{
    Tree ff, largs;
    if (isSigFFun(s, ff, largs)) {
        *ff_aux    = ff;
        *largs_aux = largs;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisSigFConst(Tree s, Tree* type_aux, Tree* name_aux, Tree* file_aux)
{
    Tree type, name, file;
    if (isSigFConst(s, type, name, file)) {
        *type_aux = type;
        *name_aux = name;
        *file_aux = file;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigFVar(Tree s, Tree* type_aux, Tree* name_aux, Tree* file_aux)
{
    Tree type, name, file;
    if (isSigFVar(s, type, name, file)) {
        *type_aux = type;
        *name_aux = name;
        *file_aux = file;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisProj(Tree s, int* i, Tree* rgroup_aux)
{
    Tree rgroup;
    if (isProj(s, i, rgroup)) {
        *rgroup_aux = rgroup;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisRec(Tree s, Tree* var_aux, Tree* body_aux)
{
    Tree var, body;
    if (isRec(s, var, body)) {
        *var_aux  = var;
        *body_aux = body;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisSigIntCast(Tree s, Tree* x_aux)
{
    Tree x;
    if (isSigIntCast(s, x)) {
        *x_aux = x;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigFloatCast(Tree s, Tree* x_aux)
{
    Tree x;
    if (isSigFloatCast(s, x)) {
        *x_aux = x;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisSigButton(Tree s, Tree* lbl_aux)
{
    Tree lbl;
    if (isSigButton(s, lbl)) {
        *lbl_aux = lbl;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigCheckbox(Tree s, Tree* lbl_aux)
{
    Tree lbl;
    if (isSigCheckbox(s, lbl)) {
        *lbl_aux = lbl;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisSigWaveform(Tree s)
{
    return isSigWaveform(s);
}

LIBFAUST_API bool CisSigHSlider(Tree s, Tree* lbl_aux, Tree* init_aux, Tree* min_aux, Tree* max_aux, Tree* step_aux)
{
    Tree lbl, init, min, max, step;
    if (isSigHSlider(s, lbl, init, min, max, step)) {
        *lbl_aux  = lbl;
        *init_aux = init;
        *min_aux  = min;
        *max_aux  = max;
        *step_aux = step;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigVSlider(Tree s, Tree* lbl_aux, Tree* init_aux, Tree* min_aux, Tree* max_aux, Tree* step_aux)
{
    Tree lbl, init, min, max, step;
    if (isSigVSlider(s, lbl, init, min, max, step)) {
        *lbl_aux  = lbl;
        *init_aux = init;
        *min_aux  = min;
        *max_aux  = max;
        *step_aux = step;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigNumEntry(Tree s, Tree* lbl_aux, Tree* init_aux, Tree* min_aux, Tree* max_aux, Tree* step_aux)
{
    Tree lbl, init, min, max, step;
    if (isSigNumEntry(s, lbl, init, min, max, step)) {
        *lbl_aux  = lbl;
        *init_aux = init;
        *min_aux  = min;
        *max_aux  = max;
        *step_aux = step;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisSigHBargraph(Tree s, Tree* lbl_aux, Tree* min_aux, Tree* max_aux, Tree* x_aux)
{
    Tree lbl, min, max, x0;
    if (isSigHBargraph(s, lbl, min, max, x0)) {
        *lbl_aux = lbl;
        *min_aux = min;
        *max_aux = max;
        *x_aux   = x0;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigVBargraph(Tree s, Tree* lbl_aux, Tree* min_aux, Tree* max_aux, Tree* x_aux)
{
    Tree lbl, min, max, x0;
    if (isSigVBargraph(s, lbl, min, max, x0)) {
        *lbl_aux = lbl;
        *min_aux = min;
        *max_aux = max;
        *x_aux   = x0;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisSigAttach(Tree s, Tree* s0_aux, Tree* s1_aux)
{
    Tree s0, s1;
    if (isSigAttach(s, s0, s1)) {
        *s0_aux = s0;
        *s1_aux = s1;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisSigEnable(Tree s, Tree* s0_aux, Tree* s1_aux)
{
    Tree s0, s1;
    if (isSigEnable(s, s0, s1)) {
        *s0_aux = s0;
        *s1_aux = s1;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigControl(Tree s, Tree* s0_aux, Tree* s1_aux)
{
    Tree s0, s1;
    if (isSigControl(s, s0, s1)) {
        *s0_aux = s0;
        *s1_aux = s1;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisSigSoundfile(Tree s, Tree* label_aux)
{
    Tree label;
    if (isSigSoundfile(s, label)) {
        *label_aux = label;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigSoundfileLength(Tree s, Tree* sf_aux, Tree* part_aux)
{
    Tree sf, part;
    if (isSigSoundfileLength(s, sf, part)) {
        *sf_aux   = sf;
        *part_aux = part;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigSoundfileRate(Tree s, Tree* sf_aux, Tree* part_aux)
{
    Tree sf, part;
    if (isSigSoundfileRate(s, sf, part)) {
        *sf_aux   = sf;
        *part_aux = part;
        return true;
    } else {
        return false;
    }
}
LIBFAUST_API bool CisSigSoundfileBuffer(Tree s, Tree* sf_aux, Tree* chan_aux, Tree* part_aux, Tree* ridx_aux)
{
    Tree sf, chan, part, ridx;
    if (isSigSoundfileBuffer(s, sf, chan, part, ridx)) {
        *sf_aux   = sf;
        *chan_aux = chan;
        *part_aux = part;
        *ridx_aux = ridx;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API Tree CsimplifyToNormalForm(Tree s)
{
    return simplifyToNormalForm(s);
}

LIBFAUST_API Tree* CsimplifyToNormalForm2(Tree* s)
{
    tvec inputs;
    int  in = 0;
    while (s[in]) {
        inputs.push_back(s[in]);
        in++;
    }
    tvec outputs = simplifyToNormalForm2(inputs);
    if (outputs.size() > 0) {
        Tree*  res = (Tree*)malloc(sizeof(Tree) * (outputs.size() + 1));
        size_t i;
        for (i = 0; i < outputs.size(); i++) res[i] = outputs[i];
        res[i] = nullptr;
        return res;
    } else {
        return nullptr;
    }
}

#ifdef __cplusplus
}
#endif

// ============
// Box C++ API
// ============

static void* boxesToSignalsAux2(void* arg)
{
    CallContext* context = static_cast<CallContext*>(arg);
    try {
        Tree outputs = boxPropagateSig(gGlobal->nil, context->fTree, makeSigInputList(context->fNumInputs));
        context->fTree = simplifyToNormalForm(outputs);
        return nullptr;
    } catch (faustexception& e) {
        context->fTree = nullptr;
        gGlobal->gErrorMessage = e.Message();
        return nullptr;
    }
}

// Can generate faustexception, used in createDSPFactoryFromBoxes and createInterpreterDSPFactoryFromBoxes
tvec boxesToSignalsAux(Tree box)
{
    // Cleanup all variables and reset gGlobal state
    DeclareVarInst::cleanup();
    gGlobal->reset();
    
    int numInputs, numOutputs;
    if (!getBoxType(box, &numInputs, &numOutputs)) {
        stringstream error;
        error << "ERROR during the evaluation of process : " << boxpp(box) << endl;
        throw faustexception(error.str());
    }
    
    // Threaded call
    CallContext context;
    context.fTree = box;
    context.fNumInputs = numInputs;
    callFun(boxesToSignalsAux2, &context);
    if (context.fTree) {
        return treeConvert(context.fTree);
    } else {
        throw faustexception(gGlobal->gErrorMessage);
    }
}

LIBFAUST_API tvec boxesToSignals(Tree box, string& error_msg)
{
    try {
        return boxesToSignalsAux(box);
    } catch (faustexception& e) {
        error_msg = e.Message();
        return {};
    }
}

LIBFAUST_API string createSourceFromBoxes(const string& name_app,
                                        Tree box,
                                        const string& lang,
                                        int argc, const char* argv[],
                                        string& error_msg)
{
    try {
        tvec signals = boxesToSignalsAux(box);
        return createSourceFromSignals(name_app, signals, lang, argc, argv, error_msg);
    } catch (faustexception& e) {
        return e.Message();
    }
}

LIBFAUST_API Tree boxDelay()
{
    return boxPrim2(sigDelay);
}

LIBFAUST_API Tree boxIntCast()
{
    return boxPrim1(sigIntCast);
}

LIBFAUST_API Tree boxFloatCast()
{
    return boxPrim1(sigFloatCast);
}

LIBFAUST_API Tree boxReadOnlyTable()
{
    return boxPrim3(sigReadOnlyTable);
}

LIBFAUST_API Tree boxWriteReadTable()
{
    return boxPrim5(sigWriteReadTable);
}

LIBFAUST_API Tree boxSoundfile(const string& label, Tree chan)
{
    return boxSoundfile(tree(label), chan);
}

LIBFAUST_API Tree boxSelect2()
{
    return boxPrim3(sigSelect2);
}

LIBFAUST_API Tree boxSelect3()
{
    return boxPrim4(sigSelect3);
}

LIBFAUST_API Tree boxFConst(SType type, const string& name, const string& file)
{
    return boxFConst(tree(type), tree(name), tree(file));
}

LIBFAUST_API Tree boxFVar(SType type, const string& name, const string& file)
{
    return boxFVar(tree(type), tree(name), tree(file));
}

LIBFAUST_API Tree boxBinOp(SOperator op)
{
    static sigFun fun[] = {sigAdd, sigSub, sigMul, sigDiv, sigRem, sigLeftShift, sigLRightShift, sigARightShift, sigGT,
                           sigLT,  sigGE,  sigLE,  sigEQ,  sigNE,  sigAND,       sigOR,          sigXOR};
    faustassert(op >= kAdd && op <= kXOR);
    return boxPrim2(fun[op]);
}

// Specific binary mathematical functions

LIBFAUST_API Tree boxAdd()
{
    return boxPrim2(sigAdd);
}
LIBFAUST_API Tree boxSub()
{
    return boxPrim2(sigSub);
}
LIBFAUST_API Tree boxMul()
{
    return boxPrim2(sigMul);
}
LIBFAUST_API Tree boxDiv()
{
    return boxPrim2(sigDiv);
}
LIBFAUST_API Tree boxRem()
{
    return boxPrim2(sigRem);
}

LIBFAUST_API Tree boxLeftShift()
{
    return boxPrim2(sigLeftShift);
}
LIBFAUST_API Tree boxLRightShift()
{
    return boxPrim2(sigLRightShift);
}
LIBFAUST_API Tree boxARightShift()
{
    return boxPrim2(sigARightShift);
}

LIBFAUST_API Tree boxGT()
{
    return boxPrim2(sigGT);
}
LIBFAUST_API Tree boxLT()
{
    return boxPrim2(sigLT);
}
LIBFAUST_API Tree boxGE()
{
    return boxPrim2(sigGE);
}
LIBFAUST_API Tree boxLE()
{
    return boxPrim2(sigLE);
}
LIBFAUST_API Tree boxEQ()
{
    return boxPrim2(sigEQ);
}
LIBFAUST_API Tree boxNE()
{
    return boxPrim2(sigNE);
}

LIBFAUST_API Tree boxAND()
{
    return boxPrim2(sigAND);
}
LIBFAUST_API Tree boxOR()
{
    return boxPrim2(sigOR);
}
LIBFAUST_API Tree boxXOR()
{
    return boxPrim2(sigXOR);
}

// Extended unary of binary mathematical functions

LIBFAUST_API Tree boxAbs()
{
    return gGlobal->gAbsPrim->box();
}
LIBFAUST_API Tree boxAcos()
{
    return gGlobal->gAcosPrim->box();
}
LIBFAUST_API Tree boxTan()
{
    return gGlobal->gTanPrim->box();
}
LIBFAUST_API Tree boxSqrt()
{
    return gGlobal->gSqrtPrim->box();
}
LIBFAUST_API Tree boxSin()
{
    return gGlobal->gSinPrim->box();
}
LIBFAUST_API Tree boxRint()
{
    return gGlobal->gRintPrim->box();
}
LIBFAUST_API Tree boxRemainder()
{
    return gGlobal->gRemainderPrim->box();
}
LIBFAUST_API Tree boxPow()
{
    return gGlobal->gPowPrim->box();
}
LIBFAUST_API Tree boxMin()
{
    return gGlobal->gMinPrim->box();
}
LIBFAUST_API Tree boxMax()
{
    return gGlobal->gMaxPrim->box();
}
LIBFAUST_API Tree boxLog()
{
    return gGlobal->gLogPrim->box();
}
LIBFAUST_API Tree boxLog10()
{
    return gGlobal->gLog10Prim->box();
}
LIBFAUST_API Tree boxFmod()
{
    return gGlobal->gAbsPrim->box();
}
LIBFAUST_API Tree boxFloor()
{
    return gGlobal->gFloorPrim->box();
}
LIBFAUST_API Tree boxExp()
{
    return gGlobal->gExpPrim->box();
}
LIBFAUST_API Tree boxExp10()
{
    return gGlobal->gExp10Prim->box();
}
LIBFAUST_API Tree boxCos()
{
    return gGlobal->gAbsPrim->box();
}
LIBFAUST_API Tree boxCeil()
{
    return gGlobal->gCeilPrim->box();
}
LIBFAUST_API Tree boxAtan()
{
    return gGlobal->gAtanPrim->box();
}
LIBFAUST_API Tree boxAtan2()
{
    return gGlobal->gAtan2Prim->box();
}
LIBFAUST_API Tree boxAsin()
{
    return gGlobal->gAsinPrim->box();
}

// User Interface

LIBFAUST_API Tree boxButton(const string& label)
{
    return boxButton(tree(label));
}

LIBFAUST_API Tree boxCheckbox(const string& label)
{
    return boxButton(tree(label));
}

LIBFAUST_API Tree boxVSlider(const string& label, Tree init, Tree min, Tree max, Tree step)
{
    return boxVSlider(tree(label), init, min, max, step);
}

LIBFAUST_API Tree boxHSlider(const string& label, Tree init, Tree min, Tree max, Tree step)
{
    return boxHSlider(tree(label), init, min, max, step);
}

LIBFAUST_API Tree boxNumEntry(const string& label, Tree init, Tree min, Tree max, Tree step)
{
    return boxNumEntry(tree(label), init, min, max, step);
}

LIBFAUST_API Tree boxVBargraph(const string& label, Tree min, Tree max)
{
    return boxVBargraph(tree(label), min, max);
}

LIBFAUST_API Tree boxHBargraph(const string& label, Tree min, Tree max)
{
    return boxHBargraph(tree(label), min, max);
}

LIBFAUST_API Tree boxAttach()
{
    return boxPrim2(sigAttach);
}

// Helpers

LIBFAUST_API Tree boxPar3(Tree x, Tree y, Tree z)
{
    return boxPar(x, boxPar(y, z));
}

LIBFAUST_API Tree boxPar4(Tree a, Tree b, Tree c, Tree d)
{
    return boxPar(a, boxPar3(b, c, d));
}

LIBFAUST_API Tree boxPar5(Tree a, Tree b, Tree c, Tree d, Tree e)
{
    return boxPar(a, boxPar4(b, c, d, e));
}

LIBFAUST_API Tree boxDelay(Tree s, Tree del)
{
    return boxSeq(boxPar(s, del), boxDelay());
}

LIBFAUST_API Tree boxIntCast(Tree s)
{
    return boxSeq(s, boxIntCast());
}

LIBFAUST_API Tree boxFloatCast(Tree s)
{
    return boxSeq(s, boxFloatCast());
}

LIBFAUST_API Tree boxReadOnlyTable(Tree n, Tree init, Tree ridx)
{
    return boxSeq(boxPar3(n, init, ridx), boxReadOnlyTable());
}

LIBFAUST_API Tree boxWriteReadTable(Tree n, Tree init, Tree widx, Tree wsig, Tree ridx)
{
    return boxSeq(boxPar5(n, init, widx, wsig, ridx), boxWriteReadTable());
}

LIBFAUST_API Tree boxSoundfile(const string& label, Tree chan, Tree part, Tree ridx)
{
    return boxSeq(boxPar(part, ridx), boxSoundfile(label, chan));
}

LIBFAUST_API Tree boxSelect2(Tree selector, Tree s1, Tree s2)
{
    return boxSeq(boxPar3(selector, s1, s2), boxSelect2());
}

LIBFAUST_API Tree boxSelect3(Tree selector, Tree s1, Tree s2, Tree s3)
{
    return boxSeq(boxPar4(selector, s1, s2, s3), boxSelect3());
}

LIBFAUST_API Tree boxBinOp(SOperator op, Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxBinOp(op));
}

LIBFAUST_API Tree boxAdd(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxAdd());
}

LIBFAUST_API Tree boxSub(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxSub());
}

LIBFAUST_API Tree boxMul(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxMul());
}

LIBFAUST_API Tree boxDiv(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxDiv());
}

LIBFAUST_API Tree boxRem(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxRem());
}

LIBFAUST_API Tree boxLeftShift(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxLeftShift());
}

LIBFAUST_API Tree boxLRightShift(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxLRightShift());
}

LIBFAUST_API Tree boxARightShift(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxARightShift());
}

LIBFAUST_API Tree boxGT(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxGT());
}

LIBFAUST_API Tree boxLT(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxLT());
}

LIBFAUST_API Tree boxGE(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxGE());
}

LIBFAUST_API Tree boxLE(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxLE());
}

LIBFAUST_API Tree boxEQ(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxEQ());
}

LIBFAUST_API Tree boxNE(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxNE());
}

LIBFAUST_API Tree boxAND(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxAND());
}

LIBFAUST_API Tree boxOR(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxOR());
}

LIBFAUST_API Tree boxXOR(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxXOR());
}

LIBFAUST_API Tree boxAbs(Tree x)
{
    return boxSeq(x, boxAbs());
}

LIBFAUST_API Tree boxAcos(Tree x)
{
    return boxSeq(x, boxAcos());
}

LIBFAUST_API Tree boxTan(Tree x)
{
    return boxSeq(x, boxTan());
}

LIBFAUST_API Tree boxSqrt(Tree x)
{
    return boxSeq(x, boxSqrt());
}

LIBFAUST_API Tree boxSin(Tree x)
{
    return boxSeq(x, boxSin());
}

LIBFAUST_API Tree boxRint(Tree x)
{
    return boxSeq(x, boxRint());
}

LIBFAUST_API Tree boxLog(Tree x)
{
    return boxSeq(x, boxLog());
}

LIBFAUST_API Tree boxLog10(Tree x)
{
    return boxSeq(x, boxLog10());
}

LIBFAUST_API Tree boxFloor(Tree x)
{
    return boxSeq(x, boxFloor());
}

LIBFAUST_API Tree boxExp(Tree x)
{
    return boxSeq(x, boxExp());
}

LIBFAUST_API Tree boxExp10(Tree x)
{
    return boxSeq(x, boxExp10());
}

LIBFAUST_API Tree boxCos(Tree x)
{
    return boxSeq(x, boxCos());
}

LIBFAUST_API Tree boxCeil(Tree x)
{
    return boxSeq(x, boxCeil());
}

LIBFAUST_API Tree boxAtan(Tree x)
{
    return boxSeq(x, boxAtan());
}

LIBFAUST_API Tree boxAsin(Tree x)
{
    return boxSeq(x, boxAsin());
}

LIBFAUST_API Tree boxRemainder(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxRemainder());
}

LIBFAUST_API Tree boxPow(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxPow());
}

LIBFAUST_API Tree boxMin(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxMin());
}

LIBFAUST_API Tree boxMax(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxMax());
}

LIBFAUST_API Tree boxFmod(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxFmod());
}

LIBFAUST_API Tree boxAtan2(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxAtan2());
}

LIBFAUST_API Tree boxVBargraph(const string& label, Tree min, Tree max, Tree x)
{
    return boxSeq(x, boxVBargraph(label, min, max));
}

LIBFAUST_API Tree boxHBargraph(const string& label, Tree min, Tree max, Tree x)
{
    return boxSeq(x, boxHBargraph(label, min, max));
}

LIBFAUST_API Tree boxAttach(Tree s1, Tree s2)
{
    return boxSeq(boxPar(s1, s2), boxAttach());
}

// ==========
// Box C API
// ==========

#ifdef __cplusplus
extern "C" {
#endif

LIBFAUST_API Tree CDSPToBoxes(const char* name_app, const char* dsp_content, int argc, const char* argv[], int* inputs, int* outputs, char* error_msg)
{
    string error_msg_aux;
    Tree   box = DSPToBoxes(name_app, dsp_content, argc, argv, inputs, outputs, error_msg_aux);
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    return box;
}

LIBFAUST_API bool CgetBoxType(Tree box, int* inputs, int* outputs)
{
    return getBoxType(box, inputs, outputs);
}

LIBFAUST_API Tree* CboxesToSignals(Tree box, char* error_msg)
{
    string error_msg_aux;
    tvec   signals = boxesToSignals(box, error_msg_aux);
    strncpy(error_msg, error_msg_aux.c_str(), 4096);
    if (signals.size() > 0) {
        Tree*  res = (Tree*)malloc(sizeof(Tree) * (signals.size() + 1));
        size_t i;
        for (i = 0; i < signals.size(); i++) res[i] = signals[i];
        res[i] = nullptr;
        return res;
    } else {
        return nullptr;
    }
}
    
LIBFAUST_API char* CcreateSourceFromBoxes(const char* name_app, Tree box,
                                        const char* lang,
                                        int argc, const char* argv[],
                                        char* error_msg)
{
    string error_msg_aux;
    string source = createSourceFromBoxes(name_app, box, lang, argc, argv, error_msg_aux);
    if (source.size() > 0) {
        return strdup(source.c_str());
    } else {
        strncpy(error_msg, error_msg_aux.c_str(), 4096);
        return nullptr;
    }
}

LIBFAUST_API Tree CboxInt(int n)
{
    return boxInt(n);
}

LIBFAUST_API Tree CboxReal(double n)
{
    return boxReal(n);
}

LIBFAUST_API Tree CboxWire()
{
    return boxWire();
}

LIBFAUST_API Tree CboxCut()
{
    return boxCut();
}

LIBFAUST_API Tree CboxSeq(Tree x, Tree y)
{
    return boxSeq(x, y);
}

LIBFAUST_API Tree CboxPar(Tree x, Tree y)
{
    return boxPar(x, y);
}

LIBFAUST_API Tree CboxSplit(Tree x, Tree y)
{
    return boxSplit(x, y);
}

LIBFAUST_API Tree CboxMerge(Tree x, Tree y)
{
    return boxMerge(x, y);
}

LIBFAUST_API Tree CboxRec(Tree x, Tree y)
{
    return boxRec(x, y);
}

LIBFAUST_API Tree CboxRoute(Tree n, Tree m, Tree r)
{
    return boxRoute(n, m, r);
}

LIBFAUST_API Tree CboxDelay()
{
    return boxDelay();
}

LIBFAUST_API Tree CboxIntCast()
{
    return boxIntCast();
}

LIBFAUST_API Tree CboxFloatCast()
{
    return boxFloatCast();
}

LIBFAUST_API Tree CboxReadOnlyTable()
{
    return boxReadOnlyTable();
}

LIBFAUST_API Tree CboxWriteReadTable()
{
    return boxWriteReadTable();
}

LIBFAUST_API Tree CboxWaveform(Tree* wf_aux)
{
    tvec wf;
    int  i = 0;
    while (wf_aux[i]) {
        wf.push_back(wf_aux[i]);
        i++;
    }
    return boxWaveform(wf);
}

LIBFAUST_API Tree CboxSoundfile(const char* label, Tree chan)
{
    return boxSoundfile(label, chan);
}

LIBFAUST_API Tree CboxSelect2()
{
    return boxSelect2();
}

LIBFAUST_API Tree CboxSelect3()
{
    return boxSelect3();
}

LIBFAUST_API Tree CboxFConst(SType type, const char* name, const char* file)
{
    return boxFConst(type, name, file);
}

LIBFAUST_API Tree CboxFVar(SType type, const char* name, const char* file)
{
    return boxFVar(type, name, file);
}

LIBFAUST_API Tree CboxBinOp(SOperator op)
{
    return boxBinOp(op);
}

// Specific binary mathematical functions

LIBFAUST_API Tree CboxAdd()
{
    return boxAdd();
}
LIBFAUST_API Tree CboxSub()
{
    return boxSub();
}
LIBFAUST_API Tree CboxMul()
{
    return boxMul();
}
LIBFAUST_API Tree CboxDiv()
{
    return boxDiv();
}
LIBFAUST_API Tree CboxRem()
{
    return boxRem();
}

LIBFAUST_API Tree CboxLeftShift()
{
    return boxLeftShift();
}
LIBFAUST_API Tree CboxLRightShift()
{
    return boxLRightShift();
}
LIBFAUST_API Tree CboxARightShift()
{
    return boxARightShift();
}

LIBFAUST_API Tree CboxGT()
{
    return boxGT();
}
LIBFAUST_API Tree CboxLT()
{
    return boxLT();
}
LIBFAUST_API Tree CboxGE()
{
    return boxGE();
}
LIBFAUST_API Tree CboxLE()
{
    return boxLE();
}
LIBFAUST_API Tree CboxEQ()
{
    return boxEQ();
}
LIBFAUST_API Tree CboxNE()
{
    return boxNE();
}

LIBFAUST_API Tree CboxAND()
{
    return boxAND();
}
LIBFAUST_API Tree CboxOR()
{
    return boxOR();
}
LIBFAUST_API Tree CboxXOR()
{
    return boxXOR();
}

// Extended unary of binary mathematical functions

LIBFAUST_API Tree CboxAbs()
{
    return boxAbs();
}
LIBFAUST_API Tree CboxAcos()
{
    return boxAcos();
}
LIBFAUST_API Tree CboxTan()
{
    return boxTan();
}
LIBFAUST_API Tree CboxSqrt()
{
    return boxSqrt();
}
LIBFAUST_API Tree CboxSin()
{
    return boxSin();
}
LIBFAUST_API Tree CboxRint()
{
    return boxRint();
}
LIBFAUST_API Tree CboxRemainder()
{
    return boxRemainder();
}
LIBFAUST_API Tree CboxPow()
{
    return boxPow();
}
LIBFAUST_API Tree CboxMin()
{
    return boxMin();
}
LIBFAUST_API Tree CboxMax()
{
    return boxMax();
}
LIBFAUST_API Tree CboxLog()
{
    return boxLog();
}
LIBFAUST_API Tree CboxLog10()
{
    return boxLog10();
}
LIBFAUST_API Tree CboxFmod()
{
    return boxFmod();
}
LIBFAUST_API Tree CboxFloor()
{
    return boxFloor();
}
LIBFAUST_API Tree CboxExp()
{
    return boxExp();
}
LIBFAUST_API Tree CboxExp10()
{
    return boxExp10();
}
LIBFAUST_API Tree CboxCos()
{
    return boxCos();
}
LIBFAUST_API Tree CboxCeil()
{
    return boxCeil();
}
LIBFAUST_API Tree CboxAtan()
{
    return boxAtan();
}
LIBFAUST_API Tree CboxAtan2()
{
    return boxAtan2();
}
LIBFAUST_API Tree CboxAsin()
{
    return boxAsin();
}

// User Interface

LIBFAUST_API Tree CboxButton(const char* label)
{
    return boxButton(label);
}

LIBFAUST_API Tree CboxCheckbox(const char* label)
{
    return boxButton(label);
}

LIBFAUST_API Tree CboxVSlider(const char* label, Tree init, Tree min, Tree max, Tree step)
{
    return boxVSlider(label, init, min, max, step);
}

LIBFAUST_API Tree CboxHSlider(const char* label, Tree init, Tree min, Tree max, Tree step)
{
    return boxHSlider(label, init, min, max, step);
}

LIBFAUST_API Tree CboxNumEntry(const char* label, Tree init, Tree min, Tree max, Tree step)
{
    return boxNumEntry(label, init, min, max, step);
}

LIBFAUST_API Tree CboxVBargraph(const char* label, Tree min, Tree max)
{
    return boxVBargraph(label, min, max);
}

LIBFAUST_API Tree CboxHBargraph(const char* label, Tree min, Tree max)
{
    return boxHBargraph(label, min, max);
}

LIBFAUST_API Tree CboxAttach()
{
    return boxAttach();
}

// Box test API

LIBFAUST_API bool CisBoxAbstr(Tree t, Tree* x_aux, Tree* y_aux)
{
    Tree x, y;
    if (isBoxAbstr(t, x, y)) {
        *x_aux = x;
        *y_aux = y;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxAccess(Tree t, Tree* exp_aux, Tree* id_aux)
{
    Tree exp, id;
    if (isBoxAccess(t, exp, id)) {
        *exp_aux = exp;
        *id_aux = id;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxAppl(Tree t, Tree* x_aux, Tree* y_aux)
{
    Tree x, y;
    if (isBoxAppl(t, x, y)) {
        *x_aux = x;
        *y_aux = y;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxButton(Tree t, Tree* lbl_aux)
{
    Tree lbl;
    if (isBoxButton(t, lbl)) {
        *lbl_aux = lbl;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxCase(Tree t, Tree* rules_aux)
{
    Tree rules;
    if (isBoxCase(t, rules)) {
        *rules_aux = rules;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxCheckbox(Tree t, Tree* lbl_aux)
{
    Tree lbl;
    if (isBoxCheckbox(t, lbl)) {
        *lbl_aux = lbl;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxComponent(Tree t, Tree* filename_aux)
{
    Tree filename;
    if (isBoxComponent(t, filename)) {
        *filename_aux = filename;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxCut(Tree t)
{
    return isBoxCut(t);
}

LIBFAUST_API bool CisBoxEnvironment(Tree t)
{
    return isBoxEnvironment(t);
}

LIBFAUST_API bool CisBoxError(Tree t)
{
    return isBoxError(t);
}

LIBFAUST_API bool CisBoxFConst(Tree t, Tree* type_aux, Tree* name_aux, Tree* file_aux)
{
    Tree type, name, file;
    if (isBoxFConst(t, type, name, file)) {
        *type_aux = type;
        *name_aux = name;
        *file_aux = file;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxFFun(Tree t, Tree* ff_aux)
{
    Tree ff;
    if (isBoxFFun(t, ff)) {
        *ff_aux = ff;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxFVar(Tree t, Tree* type_aux, Tree* name_aux, Tree* file_aux)
{
    Tree type, name, file;
    if (isBoxFVar(t, type, name, file)) {
        *type_aux = type;
        *name_aux = name;
        *file_aux = file;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxHBargraph(Tree t, Tree* lbl_aux, Tree* min_aux, Tree* max_aux)
{
    Tree lbl, min, max;
    if (isBoxHBargraph(t, lbl, min, max)) {
        *lbl_aux = lbl;
        *min_aux = min;
        *max_aux = max;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxHGroup(Tree t, Tree* lbl_aux, Tree* x_aux)
{
    Tree lbl, x;
    if (isBoxHGroup(t, lbl, x)) {
        *lbl_aux = lbl;
        *x_aux = x;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxHSlider(Tree t, Tree* lbl_aux, Tree* cur_aux, Tree* min_aux, Tree* max_aux, Tree* step_aux)
{
    Tree lbl, cur, min, max, step;
    if (isBoxHSlider(t, lbl, cur, min, max, step)) {
        *lbl_aux = lbl;
        *cur_aux = cur;
        *min_aux = min;
        *max_aux = max;
        *step_aux = step;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxIdent(Tree t, const char** str)
{
    return isBoxIdent(t, str);
}

LIBFAUST_API bool CisBoxInputs(Tree t, Tree* x_aux)
{
    Tree x;
    if (isBoxInputs(t, x)) {
        *x_aux = x;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxInt(Tree t, int* i)
{
    return isBoxInt(t, i);
}

LIBFAUST_API bool CisBoxIPar(Tree t, Tree* x_aux, Tree* y_aux, Tree* z_aux)
{
    Tree x, y, z;
    if (isBoxIPar(t, x, y, z)) {
        *x_aux = x;
        *y_aux = y;
        *z_aux = z;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxIProd(Tree t, Tree* x_aux, Tree* y_aux, Tree* z_aux)
{
    Tree x, y, z;
    if (isBoxIProd(t, x, y, z)) {
        *x_aux = x;
        *y_aux = y;
        *z_aux = z;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxISeq(Tree t, Tree* x_aux, Tree* y_aux, Tree* z_aux)
{
    Tree x, y, z;
    if (isBoxISeq(t, x, y, z)) {
        *x_aux = x;
        *y_aux = y;
        *z_aux = z;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxISum(Tree t, Tree* x_aux, Tree* y_aux, Tree* z_aux)
{
    Tree x, y, z;
    if (isBoxISum(t, x, y, z)) {
        *x_aux = x;
        *y_aux = y;
        *z_aux = z;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxLibrary(Tree t, Tree* filename_aux)
{
    Tree filename;
    if (isBoxLibrary(t, filename)) {
        *filename_aux = filename;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxMerge(Tree t, Tree* x_aux, Tree* y_aux)
{
    Tree x, y;
    if (isBoxMerge(t, x, y)) {
        *x_aux = x;
        *y_aux = y;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxMetadata(Tree t, Tree* exp_aux, Tree* mdlist_aux)
{
    Tree exp, mdlist;
    if (isBoxMetadata(t, exp, mdlist)) {
        *exp_aux = exp;
        *mdlist_aux = mdlist;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxNumEntry(Tree t, Tree* lbl_aux, Tree* cur_aux, Tree* min_aux, Tree* max_aux, Tree* step_aux)
{
    Tree lbl, cur, min, max, step;
    if (isBoxNumEntry(t, lbl, cur, min, max, step)) {
        *lbl_aux = lbl;
        *cur_aux = cur;
        *min_aux = min;
        *max_aux = max;
        *step_aux = step;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxOutputs(Tree t, Tree* x_aux)
{
    Tree x;
    if (isBoxOutputs(t, x)) {
        *x_aux = x;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxPar(Tree t, Tree* x_aux, Tree* y_aux)
{
    Tree x, y;
    if (isBoxPar(t, x, y)) {
        *x_aux = x;
        *y_aux = y;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxPrim0(Tree t)
{
    return isBoxPrim0(t);
}

LIBFAUST_API bool CisBoxPrim1(Tree t)
{
    return isBoxPrim1(t);
}

LIBFAUST_API bool CisBoxPrim2(Tree t)
{
    return isBoxPrim2(t);
}

LIBFAUST_API bool CisBoxPrim3(Tree t)
{
    return isBoxPrim3(t);
}

LIBFAUST_API bool CisBoxPrim4(Tree t)
{
    return isBoxPrim4(t);
}

LIBFAUST_API bool CisBoxPrim5(Tree t)
{
    return isBoxPrim5(t);
}

LIBFAUST_API bool CisBoxReal(Tree t, double* r)
{
    return isBoxReal(t, r);
}

LIBFAUST_API bool CisBoxRec(Tree t, Tree* x_aux, Tree* y_aux)
{
    Tree x, y;
    if (isBoxRec(t, x, y)) {
        *x_aux = x;
        *y_aux = y;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxRoute(Tree t, Tree* n_aux, Tree* m_aux, Tree* r_aux)
{
    Tree n, m, r;
    if (isBoxRoute(t, n, m, r)) {
        *n_aux = n;
        *m_aux = m;
        *r_aux = r;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxSeq(Tree t, Tree* x_aux, Tree* y_aux)
{
    Tree x, y;
    if (isBoxSeq(t, x, y)) {
        *x_aux = x;
        *y_aux = y;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxSlot(Tree t, int* id)
{
    return isBoxSlot(t, id);
}

LIBFAUST_API bool CisBoxSoundfile(Tree t, Tree* label_aux, Tree* chan_aux)
{
    Tree label, chan;
    if (isBoxSoundfile(t, label, chan)) {
        *label_aux = label;
        *chan_aux = chan;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxSplit(Tree t, Tree* x_aux, Tree* y_aux)
{
    Tree x, y;
    if (isBoxSplit(t, x, y)) {
        *x_aux = x;
        *y_aux = y;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxSymbolic(Tree t, Tree* slot_aux, Tree* body_aux)
{
    Tree slot, body;
    if (isBoxSymbolic(t, slot, body)) {
        *slot_aux = slot;
        *body_aux = body;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxTGroup(Tree t, Tree* lbl_aux, Tree* x_aux)
{
    Tree lbl, x;
    if (isBoxTGroup(t, lbl, x)) {
        *lbl_aux = lbl;
        *x_aux = x;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxVBargraph(Tree t, Tree* lbl_aux, Tree* min_aux, Tree* max_aux)
{
    Tree lbl, min, max;
    if (isBoxVBargraph(t, lbl, min, max)) {
        *lbl_aux = lbl;
        *min_aux = min;
        *max_aux = max;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxVGroup(Tree t, Tree* lbl_aux, Tree* x_aux)
{
    Tree lbl, x;
    if (isBoxVGroup(t, lbl, x)) {
        *lbl_aux = lbl;
        *x_aux = x;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxVSlider(Tree t, Tree* lbl_aux, Tree* cur_aux, Tree* min_aux, Tree* max_aux, Tree* step_aux)
{
    Tree lbl, cur, min, max, step;
    if (isBoxVSlider(t, lbl, cur, min, max, step)) {
        *lbl_aux = lbl;
        *cur_aux = cur;
        *min_aux = min;
        *max_aux = max;
        *step_aux = step;
        return true;
    } else {
        return false;
    }
}

LIBFAUST_API bool CisBoxWaveform(Tree t)
{
    return isBoxWaveform(t);
}

LIBFAUST_API bool CisBoxWire(Tree t)
{
    return isBoxWire(t);
}

LIBFAUST_API bool CisBoxWithLocalDef(Tree t, Tree* body_aux, Tree* ldef_aux)
{
    Tree body, ldef;
    if (isBoxWithLocalDef(t, body, ldef)) {
        *body_aux = body;
        *ldef_aux = ldef;
        return true;
    } else {
        return false;
    }
}

// Helpers

LIBFAUST_API Tree CboxPar3(Tree x, Tree y, Tree z)
{
    return CboxPar(x, CboxPar(y, z));
}

LIBFAUST_API Tree CboxPar4(Tree a, Tree b, Tree c, Tree d)
{
    return CboxPar(a, CboxPar3(b, c, d));
}

LIBFAUST_API Tree CboxPar5(Tree a, Tree b, Tree c, Tree d, Tree e)
{
    return CboxPar(a, CboxPar4(b, c, d, e));
}

LIBFAUST_API Tree CboxDelayAux(Tree s, Tree del)
{
    return CboxSeq(CboxPar(s, del), CboxDelay());
}

LIBFAUST_API Tree CboxIntCastAux(Tree s)
{
    return CboxSeq(s, CboxIntCast());
}

LIBFAUST_API Tree CboxFloatCastAux(Tree s)
{
    return CboxSeq(s, CboxFloatCast());
}

LIBFAUST_API Tree CboxReadOnlyTableAux(Tree n, Tree init, Tree ridx)
{
    return CboxSeq(CboxPar3(n, init, ridx), CboxReadOnlyTable());
}

LIBFAUST_API Tree CboxWriteReadTableAux(Tree n, Tree init, Tree widx, Tree wsig, Tree ridx)
{
    return CboxSeq(boxPar5(n, init, widx, wsig, ridx), CboxWriteReadTable());
}

LIBFAUST_API Tree CoxSoundfileAux(const char* label, Tree chan, Tree part, Tree ridx)
{
    return CboxSeq(CboxPar(part, ridx), CboxSoundfile(label, chan));
}

LIBFAUST_API Tree CboxSelect2Aux(Tree selector, Tree s1, Tree s2)
{
    return CboxSeq(CboxPar3(selector, s1, s2), CboxSelect2());
}

LIBFAUST_API Tree CboxSelect3Aux(Tree selector, Tree s1, Tree s2, Tree s3)
{
    return CboxSeq(CboxPar4(selector, s1, s2, s3), CboxSelect3());
}

LIBFAUST_API Tree CboxBinOpAux(SOperator op, Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxBinOp(op));
}

LIBFAUST_API Tree CboxAddAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxAdd());
}

LIBFAUST_API Tree CboxSubAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxSub());
}

LIBFAUST_API Tree CboxMulAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxMul());
}

LIBFAUST_API Tree CboxDivAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxDiv());
}

LIBFAUST_API Tree CboxRemAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxRem());
}

LIBFAUST_API Tree CboxLeftShiftAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxLeftShift());
}

LIBFAUST_API Tree CboxLRightShiftAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxLRightShift());
}

LIBFAUST_API Tree CboxARightShiftAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxARightShift());
}

LIBFAUST_API Tree CboxGTAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxGT());
}

LIBFAUST_API Tree CboxLTAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxLT());
}

LIBFAUST_API Tree CboxGEAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxGE());
}

LIBFAUST_API Tree CboxLEAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxLE());
}

LIBFAUST_API Tree CboxEQAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxEQ());
}

LIBFAUST_API Tree CboxNEAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxNE());
}

LIBFAUST_API Tree CboxANDAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxAND());
}

LIBFAUST_API Tree CboxORAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxOR());
}

LIBFAUST_API Tree CboxXORAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxXOR());
}

LIBFAUST_API Tree CboxAbsAux(Tree x)
{
    return CboxSeq(x, CboxAbs());
}

LIBFAUST_API Tree CboxAcosAux(Tree x)
{
    return CboxSeq(x, CboxAcos());
}

LIBFAUST_API Tree CboxTanAux(Tree x)
{
    return CboxSeq(x, CboxTan());
}

LIBFAUST_API Tree CboxSqrtAux(Tree x)
{
    return CboxSeq(x, CboxSqrt());
}

LIBFAUST_API Tree CboxSinAux(Tree x)
{
    return CboxSeq(x, CboxSin());
}

LIBFAUST_API Tree CboxRintAux(Tree x)
{
    return CboxSeq(x, CboxRint());
}

LIBFAUST_API Tree CboxLogAux(Tree x)
{
    return CboxSeq(x, CboxLog());
}

LIBFAUST_API Tree CboxLog10Aux(Tree x)
{
    return CboxSeq(x, CboxLog10());
}

LIBFAUST_API Tree CboxFloorAux(Tree x)
{
    return CboxSeq(x, CboxFloor());
}

LIBFAUST_API Tree CboxExpAux(Tree x)
{
    return CboxSeq(x, CboxExp());
}

LIBFAUST_API Tree CboxExp10Aux(Tree x)
{
    return CboxSeq(x, CboxExp10());
}

LIBFAUST_API Tree CboxCosAux(Tree x)
{
    return CboxSeq(x, CboxCos());
}

LIBFAUST_API Tree CboxCeilAux(Tree x)
{
    return CboxSeq(x, CboxCeil());
}

LIBFAUST_API Tree CboxAtanAux(Tree x)
{
    return CboxSeq(x, CboxAtan());
}

LIBFAUST_API Tree CboxAsinAux(Tree x)
{
    return CboxSeq(x, CboxAsin());
}

LIBFAUST_API Tree CboxRemainderAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxRemainder());
}

LIBFAUST_API Tree CboxPowAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxPow());
}

LIBFAUST_API Tree CboxMinAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxMin());
}

LIBFAUST_API Tree CboxMaxAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxMax());
}

LIBFAUST_API Tree CboxFmodAux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxFmod());
}

LIBFAUST_API Tree CboxAtan2Aux(Tree b1, Tree b2)
{
    return CboxSeq(CboxPar(b1, b2), CboxAtan2());
}

LIBFAUST_API Tree CboxVBargraphAux(const char* label, Tree min, Tree max, Tree x)
{
    return CboxSeq(x, CboxVBargraph(label, min, max));
}

LIBFAUST_API Tree CboxHBargraphAux(const char* label, Tree min, Tree max, Tree x)
{
    return CboxSeq(x, CboxHBargraph(label, min, max));
}

LIBFAUST_API Tree CboxAttachAux(Tree s1, Tree s2)
{
    return CboxSeq(CboxPar(s1, s2), CboxAttach());
}

#ifdef __cplusplus
}
#endif
