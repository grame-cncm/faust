/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
#include "libfaust.h"
#include "ppbox.hh"
#include "ppsig.hh"
#include "privatise.hh"
#include "propagate.hh"
#include "recursivness.hh"
#include "schema.h"
#include "signals.hh"
#include "sigprint.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"
#include "simplify.hh"
#include "sourcereader.hh"
#include "timing.hh"
#include "labels.hh"
#include "xtended.hh"

#ifdef C_BUILD
#include "c_code_container.hh"
#endif

#ifdef CPP_BUILD
#include "cpp_code_container.hh"
#include "cpp_gpu_code_container.hh"
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

#ifdef SOUL_BUILD
#include "soul_code_container.hh"
#endif

#ifdef WASM_BUILD
#include "wasm_code_container.hh"
#include "wast_code_container.hh"
#endif

using namespace std;

static unique_ptr<ifstream> injcode;
static unique_ptr<ifstream> enrobage;

unique_ptr<ostream> helpers;

#ifdef OCPP_BUILD
// Old CPP compiler
Compiler* old_comp = nullptr;
#endif

// FIR container
InstructionsCompiler* new_comp  = nullptr;
CodeContainer*        container = nullptr;

typedef void* (*compile_fun)(void* arg);

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

#ifdef SOUL_BUILD
    out << dspto << "SOUL" << endl;
#endif

#ifdef WASM_BUILD
    out << dspto << "WebAssembly (wast/wasm)" << endl;
#endif
}

static void callFun(compile_fun fun)
{
#if defined(EMCC)
    // No thread support in JS or WIN32
    fun(NULL);
#elif defined(_WIN32)
    DWORD  id;
    HANDLE thread = CreateThread(NULL, MAX_STACK_SIZE, LPTHREAD_START_ROUTINE(fun), NULL, 0, &id);
    faustassert(thread != NULL);
    WaitForSingleObject(thread, INFINITE);
#else
    pthread_t      thread;
    pthread_attr_t attr;
    faustassert(pthread_attr_init(&attr) == 0);
    faustassert(pthread_attr_setstacksize(&attr, MAX_STACK_SIZE) == 0);
    faustassert(pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE) == 0);
    faustassert(pthread_create(&thread, &attr, fun, nullptr) == 0);
    pthread_join(thread, nullptr);
#endif
}

static Tree evaluateBlockDiagram(Tree expandedDefList, int& numInputs, int& numOutputs);

static void* threadEvaluateBlockDiagram(void* arg)
{
    try {
        gGlobal->gProcessTree =
            evaluateBlockDiagram(gGlobal->gExpandedDefList, gGlobal->gNumInputs, gGlobal->gNumOutputs);
    } catch (faustexception& e) {
        gGlobal->gErrorMessage = e.Message();
    }
    return 0;
}

static void* threadBoxPropagateSig(void* arg)
{
    try {
        gGlobal->gLsignalsTree =
            boxPropagateSig(gGlobal->nil, gGlobal->gProcessTree, makeSigInputList(gGlobal->gNumInputs));
    } catch (faustexception& e) {
        gGlobal->gErrorMessage = e.Message();
    }
    return 0;
}

/****************************************************************
                        Global context variable
*****************************************************************/

global* gGlobal = nullptr;

// Timing can be used outside of the scope of 'gGlobal'
extern bool gTimingSwitch;

/****************************************************************
                        Parser variables
*****************************************************************/

int yyerr;

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
            gGlobal->gWideningLimit = std::atoi(argv[i+1]);
            i += 2;
            
        } else if (isCmd(argv[i], "-ni", "--narrowing-iterations") && (i + 1 < argc)){
            gGlobal->gNarrowingLimit = std::atoi(argv[i+1]);
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

        } else if (isCmd(argv[i], "-trace", "--trace")) {
            gGlobal->gVHDLTrace = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-elm", "--elementary")) {
            gGlobal->gElementarySwitch = true;
            i += 1;

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
            gGlobal->gDumpNorm = true;
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
            gGlobal->gNameSpace = argv[i + 1];
            i += 2;

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
        !startWith(gGlobal->gOutputLang, "soul") && gGlobal->gOutputLang != "fir") {
        throw faustexception("ERROR : '-os' option cannot only be used with 'cpp', 'c', 'fir' or 'soul' backends\n");
    }

    if (gGlobal->gOneSample >= 0 && gGlobal->gVectorSwitch) {
        throw faustexception("ERROR : '-os' option cannot only be used in scalar mode\n");
    }

    if (gGlobal->gFTZMode == 2 && gGlobal->gOutputLang == "soul") {
        throw faustexception("ERROR : '-ftz 2' option cannot be used in 'soul' backend\n");
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

    if (gGlobal->gNameSpace != "" && gGlobal->gOutputLang != "cpp" && gGlobal->gOutputLang != "dlang") {
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

    if (gGlobal->gComputeMix && gGlobal->gOutputLang == "soul") {
        throw faustexception("ERROR : -cm cannot be used with the 'soul' backend\n");
    }

    if (gGlobal->gFloatSize == 4 && gGlobal->gOutputLang != "cpp" && gGlobal->gOutputLang != "ocpp" &&
        gGlobal->gOutputLang != "c") {
        throw faustexception("ERROR : -fx can ony be used with 'c', 'cpp' or 'ocpp' backends\n");
    }

    if (gGlobal->gMemoryManager && gGlobal->gOutputLang != "cpp" && gGlobal->gOutputLang != "ocpp") {
        throw faustexception("ERROR : -mem can ony be used with 'cpp' or 'ocpp' backends\n");
    }

    if (gGlobal->gArchFile != "" &&
        ((gGlobal->gOutputLang == "wast") || (gGlobal->gOutputLang == "wasm") || (gGlobal->gOutputLang == "interp") ||
         (gGlobal->gOutputLang == "llvm") || (gGlobal->gOutputLang == "fir"))) {
        throw faustexception("ERROR : -a can only be used with 'c', 'cpp', 'ocpp', 'rust' and 'soul' backends\n");
    }

    if (err != 0) {
        stringstream error;
        error << "WARNING : " << parse_error.str() << endl;
        gGlobal->gErrorMsg = error.str();
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
    for (auto path : gGlobal->gImportDirList) cout << path << endl;
    cout << "\nFAUST architectures paths:" << endl;
    for (auto path : gGlobal->gArchitectureDirList) cout << path << endl;
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
    cout << "Copyright (C) 2002-2021, GRAME - Centre National de Creation Musicale. All rights reserved. \n";
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
    cout << tab << "-I <dir>  --import-dir <dir>            add the directory <dir> to the import search path." << endl;
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
         << "                                        'lang' should be c, cpp (default), csharp, dlang, fir, interp, java, julia, llvm, "
            "ocpp, rust, soul or wast/wasm."
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
    cout << tab << "-exp10      --generate-exp10            pow(10,x) replaced by possibly faster exp10(x)." << endl;
    cout << tab << "-os         --one-sample                generate one sample computation (same as -os0)." << endl;
    cout << tab << "-os0        --one-sample0               generate one sample computation (0 = separated control)." << endl;
    cout << tab << "-os1        --one-sample1               generate one sample computation (1 = separated control and DSP struct)." << endl;
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
         << "-mem        --memory                    allocate static in global state using a custom memory manager."
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
    cout << tab << "-scal      --scalar                     generate non-vectorized code." << endl;
    cout << tab
         << "-inpl      --in-place                   generates code working when input and output buffers are the same "
            "(scalar mode only)."
         << endl;
    cout << tab << "-vec       --vectorize                  generate easier to vectorize code." << endl;
    cout << tab << "-vs <n>    --vec-size <n>               size of the vector (default 32 samples)." << endl;
    cout << tab << "-lv <n>    --loop-variant <n>           [0:fastest (default), 1:simple]." << endl;
    cout << tab << "-omp       --openmp                     generate OpenMP pragmas, activates --vectorize option."
         << endl;
    cout << tab << "-pl        --par-loop                   generate parallel loops in --openmp mode." << endl;
    cout << tab
         << "-sch       --scheduler                  generate tasks and use a Work Stealing scheduler, activates "
            "--vectorize option."
         << endl;
    cout << tab << "-ocl       --opencl                     generate tasks with OpenCL (experimental)." << endl;
    cout << tab << "-cuda      --cuda                       generate tasks with CUDA (experimental)." << endl;
    cout << tab << "-dfs       --deep-first-scheduling      schedule vector loops in deep first order." << endl;
    cout << tab
         << "-g         --group-tasks                group single-threaded sequential tasks together when -omp or -sch "
            "is used."
         << endl;
    cout << tab
         << "-fun       --fun-tasks                  separate tasks code as separated functions (in -vec, -sch, or "
            "-omp mode)."
         << endl;
    cout << tab
         << "-fm <file> --fast-math <file>           use optimized versions of mathematical functions implemented in "
            "<file>, use 'faust/dsp/fastmath.cpp' when file is 'def'."
         << endl;
    cout << tab

         << "-mapp      --math-approximation         simpler/faster versions of 'floor/ceil/fmod/remainder' functions." << endl;
    cout << tab
         << "-ns <name> --namespace <name>           generate C++ or D code in a namespace <name>." << endl;

    cout << tab << "-vhdl      --vhdl                       output vhdl file." << endl;
    
    cout << tab
         << "-wi <n>    --widening-iterations <n>    number of iterations before widening in signal bounding."
         << endl;

    cout << tab
         << "-ni <n>    --narrowing-iterations <n>   number of iterations before stopping narrowing in signal bounding."
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
    cout << tab << "-me         --math-exceptions           check / for 0 as denominator and remainder, fmod, sqrt, log10, log, acos, asin functions domain." << endl;

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
            vector<char> to_replace{'.', ':', '/'};
            dst << replaceCharList(key.str(), to_replace, '_');
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

/****************************************************************
                                MAIN
*****************************************************************/

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

#endif

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
    //    for (auto d : gGlobal->gArchitectureDirList) {
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
    gGlobal->gResult2 = gGlobal->nil;

    if (!gGlobal->gInjectFlag && gGlobal->gInputFiles.begin() == gGlobal->gInputFiles.end()) {
        throw faustexception("ERROR : no files specified; for help type \"faust --help\"\n");
    }
    for (s = gGlobal->gInputFiles.begin(); s != gGlobal->gInputFiles.end(); s++) {
        if (s == gGlobal->gInputFiles.begin()) {
            gGlobal->gMasterDocument = *s;
        }
        gGlobal->gResult2 = cons(importFile(tree(s->c_str())), gGlobal->gResult2);
    }

    gGlobal->gExpandedDefList = gGlobal->gReader.expandList(gGlobal->gResult2);

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
    if (file_include != nullptr) {
        streamCopyUntilEnd(*file_include.get(), dst);
    }
}

static void injectCode(unique_ptr<ifstream>& enrobage1, ostream& dst)
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
            streamCopyUntil(*enrobage1.get(), dst, "<<includeIntrinsic>>");
            container->printMacros(dst, 0);
            streamCopyUntil(*enrobage1.get(), dst, "<<includeclass>>");
            streamCopyUntilEnd(*injcode.get(), dst);
            streamCopyUntilEnd(*enrobage1.get(), dst);
        }
        throw faustexception("");
    }
}

static void compileCLLVM(Tree signals, int numInputs, int numOutputs, bool generate)
{
#ifdef CLANG_BUILD
    // FIR is generated with internal real instead of FAUSTFLOAT (see InstBuilder::genBasicTyped)
    gGlobal->gFAUSTFLOAT2Internal = true;

    container = ClangCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs);
    
    if (generate) {
        // TO CHECK ?
    } else {
        // To trigger 'sig.dot' generation
        if (gGlobal->gVectorSwitch) {
            new_comp = new DAGInstructionsCompiler(container);
        } else {
            new_comp = new InstructionsCompiler(container);
        }
        new_comp->prepare(signals);
    }
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
    
    gGlobal->gUseDefaultSound = false;
    
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

static void compileInterp(Tree signals, int numInputs, int numOutputs, bool generate)
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

static void compileFIR(Tree signals, int numInputs, int numOutputs, bool generate, ostream* out)
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

static void compileC(Tree signals, int numInputs, int numOutputs, bool generate, ostream* out)
{
#ifdef C_BUILD
    container = CCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, out);
#else
    throw faustexception("ERROR : -lang c not supported since C backend is not built\n");
#endif
}

static void compileCPP(Tree signals, int numInputs, int numOutputs, bool generate, ostream* out)
{
#ifdef CPP_BUILD
    container = CPPCodeContainer::createContainer(gGlobal->gClassName, gGlobal->gSuperClassName, numInputs, numOutputs, out);
#else
    throw faustexception("ERROR : -lang cpp not supported since CPP backend is not built\n");
#endif
}

static void compileOCPP(Tree signals, int numInputs, int numOutputs, bool generate)
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

static void compileRust(Tree signals, int numInputs, int numOutputs, bool generate, ostream* out)
{
#ifdef RUST_BUILD
    // FIR is generated with internal real instead of FAUSTFLOAT (see InstBuilder::genBasicTyped)
    gGlobal->gFAUSTFLOAT2Internal = true;
    container = RustCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, out);
#else
    throw faustexception("ERROR : -lang rust not supported since Rust backend is not built\n");
#endif
}

static void compileJava(Tree signals, int numInputs, int numOutputs, bool generate, ostream* out)
{
#ifdef JAVA_BUILD
    gGlobal->gAllowForeignFunction = false;  // No foreign functions
    container = JAVACodeContainer::createContainer(gGlobal->gClassName, gGlobal->gSuperClassName, numInputs, numOutputs, out);
#else
    throw faustexception("ERROR : -lang java not supported since JAVA backend is not built\n");
#endif
}

static void compileJulia(Tree signals, int numInputs, int numOutputs, bool generate, ostream* out)
{
#ifdef JULIA_BUILD
    gGlobal->gAllowForeignFunction = false;  // No foreign functions
    container = JuliaCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, out);
#else
    throw faustexception("ERROR : -lang julia not supported since Julia backend is not built\n");
#endif
}

static void compileCSharp(Tree signals, int numInputs, int numOutputs, bool generate, ostream* out)
{
#ifdef CSHARP_BUILD
    gGlobal->gAllowForeignFunction = false;  // No foreign functions
    container = CSharpCodeContainer::createContainer(gGlobal->gClassName, gGlobal->gSuperClassName, numInputs, numOutputs, out);
#else
    throw faustexception("ERROR : -lang csharp not supported since CSharp backend is not built\n");
#endif
}

static void compileSOUL(Tree signals, int numInputs, int numOutputs, bool generate, ostream* out)
{
#ifdef SOUL_BUILD
    gGlobal->gAllowForeignFunction = false;  // No foreign functions
    gGlobal->gAllowForeignConstant = false;  // No foreign constant
    gGlobal->gAllowForeignVar      = false;  // No foreign variable
    
    // FIR is generated with internal real instead of FAUSTFLOAT (see InstBuilder::genBasicTyped)
    gGlobal->gFAUSTFLOAT2Internal = true;
    
    // "one sample control" model by default;
    gGlobal->gOneSampleControl = true;
    gGlobal->gNeedManualPow    = false;  // Standard pow function will be used in pow(x,y) when Y in an integer
    
    container = SOULCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, out);
#else
    throw faustexception("ERROR : -lang rust not supported since SOUL backend is not built\n");
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

static void compileWAST(Tree signals, int numInputs, int numOutputs, bool generate, ostream* out, const string& outpath)
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
    
    container = WASTCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, out,
                                                   ((gGlobal->gOutputLang == "wast") || (gGlobal->gOutputLang == "wast-i")));
    createHelperFile(outpath);
#else
    throw faustexception("ERROR : -lang wast not supported since WAST backend is not built\n");
#endif
}

static void compileWASM(Tree signals, int numInputs, int numOutputs, bool generate, ostream* out, const string& outpath)
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
    
    container = WASMCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, out,
                                                   ((gGlobal->gOutputLang == "wasm")
                                                    || (gGlobal->gOutputLang == "wasm-i")
                                                    || (gGlobal->gOutputLang == "wasm-ib")));
    createHelperFile(outpath);
 #else
    throw faustexception("ERROR : -lang wasm not supported since WASM backend is not built\n");
#endif
}

static void compileDlang(Tree signals, int numInputs, int numOutputs, bool generate, ostream* out)
{
#ifdef DLANG_BUILD
    container = DLangCodeContainer::createContainer(gGlobal->gClassName, gGlobal->gSuperClassName, numInputs, numOutputs, out);
#else
    throw faustexception("ERROR : -lang dlang not supported since D backend is not built\n");
#endif
}

void generateCode(Tree signals, int numInputs, int numOutputs, bool generate)
{
    unique_ptr<ostream> dst;
    string              outpath;

    // MANDATORY: use ostringstream which is indeed a subclass of ostream (otherwise subtle dynamic_cast related crash
    // can occur...)

    // Finally output file
    if (gGlobal->gOutputFile == "string") {
        dst = unique_ptr<ostream>(new ostringstream());
    } else if (gGlobal->gOutputFile == "binary") {
        dst = unique_ptr<ostream>(new ostringstream(ostringstream::out | ostringstream::binary));
    } else if (gGlobal->gOutputFile != "") {
        outpath = (gGlobal->gOutputDir != "")
            ? (gGlobal->gOutputDir + "/" + gGlobal->gOutputFile) : gGlobal->gOutputFile;

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

    if (gGlobal->gOutputLang == "cllvm") {
        compileCLLVM(signals, numInputs, numOutputs, generate);
    } else if (gGlobal->gOutputLang == "llvm") {
        compileLLVM(signals, numInputs, numOutputs, generate);
    } else if (gGlobal->gOutputLang == "interp") {
        compileInterp(signals, numInputs, numOutputs, generate);
    } else if (gGlobal->gOutputLang == "fir") {
        compileFIR(signals, numInputs, numOutputs, generate, dst.get());
    } else {
        if (gGlobal->gOutputLang == "c") {
            compileC(signals, numInputs, numOutputs, generate, dst.get());
        } else if (gGlobal->gOutputLang == "cpp") {
            compileCPP(signals, numInputs, numOutputs, generate, dst.get());
        } else if (gGlobal->gOutputLang == "ocpp") {
            compileOCPP(signals, numInputs, numOutputs, generate);
        } else if (gGlobal->gOutputLang == "rust") {
            compileRust(signals, numInputs, numOutputs, generate, dst.get());
        } else if (gGlobal->gOutputLang == "java") {
            compileJava(signals, numInputs, numOutputs, generate, dst.get());
        } else if (gGlobal->gOutputLang == "julia") {
            compileJulia(signals, numInputs, numOutputs, generate, dst.get());
        } else if (gGlobal->gOutputLang == "csharp") {
            compileCSharp(signals, numInputs, numOutputs, generate, dst.get());
        } else if (startWith(gGlobal->gOutputLang, "soul")) {
            compileSOUL(signals, numInputs, numOutputs, generate, dst.get());
        } else if (startWith(gGlobal->gOutputLang, "wast")) {
            compileWAST(signals, numInputs, numOutputs, generate, dst.get(), outpath);
        } else if (startWith(gGlobal->gOutputLang, "wasm")) {
            compileWASM(signals, numInputs, numOutputs, generate, dst.get(), outpath);
        } else if (startWith(gGlobal->gOutputLang, "dlang")) {
            compileDlang(signals, numInputs, numOutputs, generate, dst.get());
        } else {
            stringstream error;
            error << "ERROR : cannot find backend for "
                  << "\"" << gGlobal->gOutputLang << "\"" << endl;
            throw faustexception(error.str());
        }
    
        // New compiler
        if (container) {
            
            if (gGlobal->gVectorSwitch) {
                new_comp = new DAGInstructionsCompiler(container);
            }
    #if defined(RUST_BUILD) || defined(JULIA_BUILD)
            else if (gGlobal->gOutputLang == "rust" || gGlobal->gOutputLang == "julia") {
                new_comp = new InstructionsCompiler1(container);
            }
    #endif
            else {
                new_comp = new InstructionsCompiler(container);
            }

            if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) new_comp->setDescription(new Description());
            new_comp->compileMultiSignal(signals);
        }
    }

    /****************************************************************
     * generate output file
     ****************************************************************/

    if (new_comp) {
        if (gGlobal->gArchFile != "") {
            // Keep current directory
            char  buffer[FAUST_PATH_MAX];
            char* current_directory = getcwd(buffer, FAUST_PATH_MAX);

            if ((enrobage = openArchStream(gGlobal->gArchFile.c_str())) != nullptr) {
                if (gGlobal->gNameSpace != "" && gGlobal->gOutputLang == "cpp")
                    *dst.get() << "namespace " << gGlobal->gNameSpace << " {" << endl;
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

                // Restore current_directory
                if (current_directory) {
                    if (chdir(current_directory)) {  // return code is 0 on successful completion
                        cerr << "can't restore current directory (" << current_directory << ")" << endl;
                    }
                }

                if (gGlobal->gNameSpace != "" && gGlobal->gOutputLang == "cpp")
                    *dst.get() << "} // namespace " << gGlobal->gNameSpace << endl;

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
                if (helpers != nullptr) gGlobal->gDSPFactory->writeHelper(helpers.get(), false, false);
            } else if (gGlobal->gOutputFile == "binary") {
                gGlobal->gDSPFactory->write(dst.get(), true, false);
                if (helpers != nullptr) gGlobal->gDSPFactory->writeHelper(helpers.get(), true, false);
            } else if (gGlobal->gOutputFile != "") {
                // Binary mode for LLVM backend if output different of 'cout'
                gGlobal->gDSPFactory->write(dst.get(), true, false);
                if (helpers != nullptr) gGlobal->gDSPFactory->writeHelper(helpers.get(), false, false);
            } else {
                gGlobal->gDSPFactory->write(&cout, false, false);
                if (helpers != nullptr) gGlobal->gDSPFactory->writeHelper(&cout, false, false);
            }
        }

        endTiming("generateCode");

#ifdef OCPP_BUILD
    } else if (old_comp) {
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

#endif
    } else {
        faustassert(false);
    }
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
#ifdef OCPP_BUILD
        } else if (old_comp) {
            printXML(old_comp->getDescription(), old_comp->getClass()->inputs(), old_comp->getClass()->outputs());
#endif
        } else {
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
#ifdef OCPP_BUILD
        } else if (old_comp) {
            old_comp->getClass()->printGraphDotFormat(dotfile);
#endif
        } else {
            faustassert(false);
        }
    }
}

static string expandDSPInternal(int argc, const char* argv[], const char* name, const char* dsp_content)
{
    /****************************************************************
     1 - process command line
    *****************************************************************/
    initFaustDirectories(argc, argv);
    processCmdline(argc, argv);

    /****************************************************************
     2 - parse source files
    *****************************************************************/
    if (dsp_content) {
        gGlobal->gInputString = dsp_content;
        gGlobal->gInputFiles.push_back(name);
    }
    initDocumentNames();
    initFaustFloat();

    parseSourceFiles();

    /****************************************************************
     3 - evaluate 'process' definition
    *****************************************************************/
    callFun(threadEvaluateBlockDiagram);  // In a thread with more stack size...
    if (!gGlobal->gProcessTree) {
        throw faustexception(gGlobal->gErrorMessage);
    }

    // Encode compilation options as a 'declare' : has to be located first in the string
    stringstream out;
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
    out << "process = " << boxpp(gGlobal->gProcessTree) << ';' << endl;
    return out.str();
}

static void createFactoryAux(const char* name, const char* dsp_content, int argc, const char* argv[], bool generate)
{
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
        injcode = unique_ptr<ifstream>(new ifstream());
        injcode->open(gGlobal->gInjectFile.c_str(), ifstream::in);
        if (!injcode->is_open()) {
            stringstream error;
            error << "ERROR : can't inject \"" << gGlobal->gInjectFile << "\" external code file, file not found"
                  << endl;
            throw faustexception(error.str());
        }
    }

    /****************************************************************
     2 - parse source files
    *****************************************************************/
    if (dsp_content) {
        gGlobal->gInputString = dsp_content;
        gGlobal->gInputFiles.push_back(name);
    }
    initDocumentNames();
    initFaustFloat();

    parseSourceFiles();

    /****************************************************************
     3 - evaluate 'process' definition
    *****************************************************************/

    callFun(threadEvaluateBlockDiagram);  // In a thread with more stack size...
    if (!gGlobal->gProcessTree) {
        throw faustexception(gGlobal->gErrorMessage);
    }
    Tree process    = gGlobal->gProcessTree;
    int  numInputs  = gGlobal->gNumInputs;
    int  numOutputs = gGlobal->gNumOutputs;

    if (gGlobal->gExportDSP) {
        string outpath =
            (gGlobal->gOutputDir != "") ? (gGlobal->gOutputDir + "/" + gGlobal->gOutputFile) : gGlobal->gOutputFile;
        ofstream out(outpath.c_str());

        // Encode compilation options as a 'declare' : has to be located first in the string
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
        out << "process = " << boxpp(process) << ";" << endl;
        return;
    }

    /****************************************************************
     4 - compute output signals of 'process'
    *****************************************************************/
    startTiming("propagation");

    callFun(threadBoxPropagateSig);  // In a thread with more stack size...
    if (!gGlobal->gLsignalsTree) {
        throw faustexception(gGlobal->gErrorMessage);
    }
    Tree lsignals = gGlobal->gLsignalsTree;

    if (gGlobal->gDetailsSwitch) {
        cout << "output signals are : " << endl;
        printSignal(lsignals, stdout);
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
}

static void createFactoryAux(const char* name, Tree signals, int argc, const char* argv[], int numInputs, int numOutputs, bool generate)
{
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
    
    gGlobal->gMetaDataSet[tree("name")].insert(tree(quote(name)));
    generateCode(signals, numInputs, numOutputs, generate);
}

// ============
// Backend API
// ============

dsp_factory_base* createFactory(const char* name, const char* dsp_content,
                                int argc, const char* argv[],
                                string& error_msg, bool generate)
{
    gGlobal                   = nullptr;
    dsp_factory_base* factory = nullptr;
    
    try {
        global::allocate();
        createFactoryAux(name, dsp_content, argc, argv, generate);
        error_msg = gGlobal->gErrorMsg;
        factory   = gGlobal->gDSPFactory;
    } catch (faustexception& e) {
        error_msg = e.Message();
    }
    
    global::destroy();
    return factory;
}

dsp_factory_base* createFactory(const char* name, tvec signals,
                                int argc, const char* argv[],
                                std::string& error_msg)
{
    dsp_factory_base* factory = nullptr;
    
    try {
        createFactoryAux(name, listConvert(signals), argc, argv, gGlobal->gMaxInputs, signals.size(), true);
        error_msg = gGlobal->gErrorMsg;
        factory   = gGlobal->gDSPFactory;
    } catch (faustexception& e) {
        error_msg = e.Message();
    }
    
    return factory;
}

string expandDSP(int argc, const char* argv[], const char* name, const char* dsp_content, string& sha_key,
                 string& error_msg)
{
    gGlobal    = nullptr;
    string res = "";
    
    try {
        global::allocate();
        res       = expandDSPInternal(argc, argv, name, dsp_content);
        sha_key   = generateSHA1(res);
        error_msg = gGlobal->gErrorMsg;
    } catch (faustexception& e) {
        error_msg = e.Message();
    }
    
    global::destroy();
    return res;
}

// ===============
// Signal C++ API
// ===============

EXPORT dsp_factory_base* createCPPDSPFactoryFromSignals(const std::string& name_app, tvec signals,
                                                        int argc, const char* argv[],
                                                        std::string& error_msg)
{
    dsp_factory_base* factory = nullptr;
    
    int         argc1 = 0;
    const char* argv1[64];
    argv1[argc1++] = "faust";
    argv1[argc1++] = "-o";
    argv1[argc1++] = "string";
    
    // Copy arguments
    for (int i = 0; i < argc; i++) {
        argv1[argc1++] = argv[i];
    }
    argv1[argc1] = nullptr;  // NULL terminated argv
  
    try {
        createFactoryAux(name_app.c_str(), listConvert(signals), argc1, argv1, gGlobal->gMaxInputs, signals.size(), true);
        error_msg = gGlobal->gErrorMsg;
        factory   = gGlobal->gDSPFactory;
    } catch (faustexception& e) {
        error_msg = e.Message();
    }
    
    return factory;
}

// Foreign

EXPORT Tree sigFFun(Tree ff, tvec largs)
{
    return sigFFun(ff, listConvert(largs));
}

enum SType { kSInt, kSReal };

EXPORT Tree sigFConst(SType type, const string& name, const string& file)
{
    return sigFConst(tree(type), tree(name), tree(file));
}

EXPORT Tree sigFVar(SType type, const string& name, const string& file)
{
    return sigFVar(tree(type), tree(name), tree(file));
}

// User Interface

EXPORT Tree sigButton(const std::string& label)
{
    return sigButton(normalizePath(cons(tree(label), gGlobal->nil)));
}

EXPORT Tree sigCheckbox(const std::string& label)
{
    return sigCheckbox(normalizePath(cons(tree(label), gGlobal->nil)));
}

EXPORT Tree sigVSlider(const std::string& label, Tree cur, Tree min, Tree max, Tree step)
{
    return sigVSlider(normalizePath(cons(tree(label), gGlobal->nil)), cur, min, max, step);
}

EXPORT Tree sigHSlider(const std::string& label, Tree cur, Tree min, Tree max, Tree step)
{
    return sigHSlider(normalizePath(cons(tree(label), gGlobal->nil)), cur, min, max, step);
}

EXPORT Tree sigNumEntry(const std::string& label, Tree cur, Tree min, Tree max, Tree step)
{
    return sigNumEntry(normalizePath(cons(tree(label), gGlobal->nil)), cur, min, max, step);
}

EXPORT Tree sigVBargraph(const std::string& label, Tree min, Tree max, Tree x)
{
    return sigVBargraph(normalizePath(cons(tree(label), gGlobal->nil)), min, max, x);
}

EXPORT Tree sigHBargraph(const std::string& label, Tree min, Tree max, Tree x)
{
    return sigHBargraph(normalizePath(cons(tree(label), gGlobal->nil)), min, max, x);
}

EXPORT Tree sigSoundfile(const std::string& label)
{
    return sigSoundfile(normalizePath(cons(tree(label), gGlobal->nil)));
}

EXPORT Tree sigSelf()
{
    return sigDelay1(sigProj(0, ref(1)));
}

//Tree liftn(Tree t, int threshold);

EXPORT Tree sigRecursion(Tree s)
{
    //return sigDelay0(sigProj(0, rec(cons(liftn(s, 0), gGlobal->nil))));
    return sigDelay0(sigProj(0, rec(cons(s, gGlobal->nil))));
}

// Global context, to be used in C and C++ API

extern "C" EXPORT void createLibContext()
{
    gGlobal = nullptr;
    global::allocate();
}

extern "C" EXPORT void destroyLibContext()
{
    global::destroy();
}

// =============
// Signal C API
// =============

#ifdef __cplusplus
extern "C"
{
#endif
    
    EXPORT Tree CsigInt(int n)
    {
        return sigInt(n);
    }
    
    EXPORT Tree CsigReal(double n)
    {
        return sigReal(n);
    }
    
    EXPORT Tree CsigInput(int idx)
    {
        return sigInput(idx);
    }
    
    EXPORT Tree CsigDelay(Tree t0, Tree del)
    {
        return sigDelay(t0, del);
    }
    
    EXPORT Tree CsigIntCast(Tree s)
    {
        return sigIntCast(s);
    }
    
    EXPORT Tree CsigFloatCast(Tree s)
    {
        return sigFloatCast(s);
    }
    
    EXPORT Tree CsigReadOnlyTable(Tree n, Tree init, Tree ridx)
    {
        return sigReadOnlyTable(n, init, ridx);
    }
    
    EXPORT Tree CsigWriteReadTable(Tree n, Tree init, Tree widx, Tree wsig, Tree ridx)
    {
        return sigWriteReadTable(n, init, widx, wsig,ridx);
    }
    
    EXPORT Tree CsigWaveform(Tree* wf_aux)
    {
        tvec wf;
        int i = 0;
        while (wf_aux[i]) { wf.push_back(wf_aux[i]); i++; }
        return sigWaveform(wf);
    }
    
    EXPORT Tree CsigSoundfile(const char* label)
    {
        return sigSoundfile(label);
    }
    
    EXPORT Tree CsigSoundfileLength(Tree sf, Tree part)
    {
        return sigSoundfileLength(sf, part);
    }
    
    EXPORT Tree CsigSoundfileRate(Tree sf, Tree part)
    {
        return sigSoundfileRate(sf, part);
    }
    
    EXPORT Tree CsigSoundfileBuffer(Tree sf, Tree chan, Tree part, Tree ridx)
    {
        return sigSoundfileBuffer(sf, chan, part, ridx);
    }
    
    EXPORT Tree CsigSelect2(Tree selector, Tree s1, Tree s2)
    {
        return sigSelect2(selector, s1, s2);
    }
    
    EXPORT Tree CsigSelect3(Tree selector, Tree s1, Tree s2, Tree s3)
    {
        return sigSelect3(selector, s1, s2, s3);
    }
    
    EXPORT Tree CsigFConst(SType type, const char* name, const char* file)
    {
        return sigFConst(type, name, file);
    }
    
    EXPORT Tree CsigFVar(SType type, const char* name, const char* file)
    {
        return sigFVar(type, name, file);
    }
 
    EXPORT Tree CsigBinOp(SOperator op, Tree x, Tree y)
    {
        return sigBinOp(op, x, y);
    }
    
    EXPORT Tree CsigAdd(Tree x, Tree y)
    {
        return sigAdd(x, y);
    }
    EXPORT Tree CsigSub(Tree x, Tree y)
    {
        return sigSub(x, y);
    }
    EXPORT Tree CsigMul(Tree x, Tree y)
    {
        return sigMul(x, y);
    }
    EXPORT Tree CsigDiv(Tree x, Tree y)
    {
        return sigDiv(x, y);
    }
    EXPORT Tree CsigRem(Tree x, Tree y)
    {
        return sigRem(x, y);
    }
    
    EXPORT Tree CsigLeftShift(Tree x, Tree y)
    {
        return sigLeftShift(x, y);
    }
    EXPORT Tree CsigLRightShift(Tree x, Tree y)
    {
        return sigLRightShift(x, y);
    }
    EXPORT Tree CsigARightShift(Tree x, Tree y)
    {
        return sigARightShift(x, y);
    }
    
    EXPORT Tree CsigGT(Tree x, Tree y)
    {
        return sigGT(x, y);
    }
    EXPORT Tree CsigLT(Tree x, Tree y)
    {
        return sigLT(x, y);
    }
    EXPORT Tree CsigGE(Tree x, Tree y)
    {
        return sigGE(x, y);
    }
    EXPORT Tree CsigLE(Tree x, Tree y)
    {
        return sigLE(x, y);
    }
    EXPORT Tree CsigEQ(Tree x, Tree y)
    {
        return sigEQ(x, y);
    }
    EXPORT Tree CsigNE(Tree x, Tree y)
    {
        return sigNE(x, y);
    }
    
    EXPORT Tree CsigAND(Tree x, Tree y)
    {
        return sigAND(x, y);
    }
    EXPORT Tree CsigOR(Tree x, Tree y)
    {
        return sigOR(x, y);
    }
    EXPORT Tree CsigXOR(Tree x, Tree y)
    {
        return sigXOR(x, y);
    }
    
    EXPORT Tree CsigAbs(Tree x)
    {
        return sigAbs(x);
    }
    EXPORT Tree CsigAcos(Tree x)
    {
        return sigAcos(x);
    }
    EXPORT Tree CsigTan(Tree x)
    {
        return sigTan(x);
    }
    EXPORT Tree CsigSqrt(Tree x)
    {
        return sigSqrt(x);
    }
    EXPORT Tree CsigSin(Tree x)
    {
        return sigSin(x);
    }
    EXPORT Tree CsigRint(Tree x)
    {
        return sigRint(x);
    }
    EXPORT Tree CsigRemainder(Tree x, Tree y)
    {
        return sigRemainder(x, y);
    }
    EXPORT Tree CsigPow(Tree x, Tree y)
    {
        return sigPow(x, y);
    }
    EXPORT Tree CsigMin(Tree x, Tree y)
    {
        return sigMin(x, y);
    }
    EXPORT Tree CsigMax(Tree x, Tree y)
    {
        return sigMax(x, y);
    }
    EXPORT Tree CsigLog(Tree x)
    {
        return sigLog(x);
    }
    EXPORT Tree CsigLog10(Tree x)
    {
        return sigLog10(x);
    }
    EXPORT Tree CsigFmod(Tree x, Tree y)
    {
        return sigFmod(x, y);
    }
    EXPORT Tree CsigFloor(Tree x)
    {
        return sigFloor(x);
    }
    EXPORT Tree CsigExp(Tree x)
    {
        return sigExp(x);
    }
    EXPORT Tree CsigExp10(Tree x)
    {
        return sigExp10(x);
    }
    EXPORT Tree CsigCos(Tree x)
    {
        return sigCos(x);
    }
    EXPORT Tree CsigCeil(Tree x)
    {
        return sigCeil(x);
    }
    EXPORT Tree CsigAtan(Tree x)
    {
        return sigAtan(x);
    }
    EXPORT Tree CsigAtan2(Tree x, Tree y)
    {
        return sigAtan2(x, y);
    }
    EXPORT Tree CsigAsin(Tree x)
    {
        return sigAsin(x);
    }
    
    EXPORT Tree CsigSelf()
    {
        return sigSelf();
    }
    
    EXPORT Tree CsigRecursion(Tree s1)
    {
        return sigRecursion(s1);
    }
    
    EXPORT Tree CsigButton(const char* label)
    {
        return sigButton(label);
    }
    
    EXPORT Tree CsigCheckbox(const char* label)
    {
        return sigCheckbox(label);
    }
    
    EXPORT Tree CsigVSlider(const char* label, Tree init, Tree min, Tree max, Tree step)
    {
        return sigVSlider(label, init, min, max, step);
    }
    
    EXPORT Tree CsigHSlider(const char* label, Tree init, Tree min, Tree max, Tree step)
    {
        return sigHSlider(label, init, min, max, step);
    }
    
    EXPORT Tree CsigNumEntry(const char* label, Tree init, Tree min, Tree max, Tree step)
    {
        return sigNumEntry(label, init, min, max, step);
    }
    
    EXPORT Tree CsigVBargraph(const char* label, Tree min, Tree max, Tree x)
    {
        return sigVBargraph(label, min, max, x);
    }
    
    EXPORT Tree CsigHBargraph(const char* label, Tree min, Tree max, Tree x)
    {
        return sigHBargraph(label, min, max, x);
    }
    
    EXPORT Tree CsigAttach(Tree x, Tree y)
    {
        return sigAttach(y, y);
    }
    
#ifdef __cplusplus
}
#endif

// ============
// Box C++ API
// ============

// Can generate faustexception
tvec boxesToSignalsAux(Tree box)
{
    int numInputs, numOutputs;
  
    if (!getBoxType(box, &numInputs, &numOutputs)) {
        stringstream error;
        error << "ERROR during the evaluation of process : " << boxpp(box) << endl;
        throw faustexception(error.str());
    }
     
    return propagate(gGlobal->nil, gGlobal->nil, box, makeSigInputList(numInputs));
}

EXPORT tvec boxesToSignals(Tree box, std::string& error_msg)
{
    try {
        return boxesToSignalsAux(box);
    } catch (faustexception& e) {
        error_msg = e.Message();
        return {};
    }
}

EXPORT dsp_factory_base* createCPPDSPFactoryFromBoxes(const std::string& name_app,
                                                      Tree box,
                                                      int argc, const char* argv[],
                                                      std::string& error_msg)
{
    try {
        tvec signals = boxesToSignalsAux(box);
        return createCPPDSPFactoryFromSignals(name_app, signals, argc, argv, error_msg);
    } catch (faustexception& e) {
        error_msg = e.Message();
        return nullptr;
    }
}

EXPORT Tree boxDelay()
{
    return boxPrim2(sigDelay);
}

EXPORT Tree boxIntCast()
{
    return boxPrim1(sigIntCast);
}

EXPORT Tree boxFloatCast()
{
    return boxPrim1(sigFloatCast);
}

EXPORT Tree boxReadOnlyTable()
{
    return boxPrim3(sigReadOnlyTable);
}

EXPORT Tree boxWriteReadTable()
{
    return boxPrim5(sigWriteReadTable);
}

EXPORT Tree boxSoundfile(const std::string& label, Tree chan)
{
    return boxSoundfile(tree(label), chan);
}

EXPORT Tree boxSelect2()
{
    return boxPrim3(sigSelect2);
}

EXPORT Tree boxSelect3()
{
    return boxPrim4(sigSelect3);
}

EXPORT Tree boxFConst(SType type, const std::string& name, const std::string& file)
{
    return boxFConst(tree(type), tree(name), tree(file));
}

EXPORT Tree boxFVar(SType type, const std::string& name, const std::string& file)
{
    return boxFVar(tree(type), tree(name), tree(file));
}

EXPORT Tree boxBinOp(SOperator op)
{
    static sigFun fun [] = {
        sigAdd, sigSub, sigMul, sigDiv, sigRem,
        sigLeftShift, sigLRightShift, sigARightShift,
        sigGT, sigLT, sigGE, sigLE, sigEQ, sigNE,
        sigAND, sigOR, sigXOR
    };
    faustassert(op >= kAdd && op <= kXOR);
    return boxPrim2(fun[op]);
}

// Specific binary mathematical functions

EXPORT Tree boxAdd()
{
    return boxPrim2(sigAdd);
}
EXPORT Tree boxSub()
{
    return boxPrim2(sigSub);
}
EXPORT Tree boxMul()
{
    return boxPrim2(sigMul);
}
EXPORT Tree boxDiv()
{
    return boxPrim2(sigDiv);
}
EXPORT Tree boxRem()
{
    return boxPrim2(sigRem);
}

EXPORT Tree boxLeftShift()
{
    return boxPrim2(sigLeftShift);
}
EXPORT Tree boxLRightShift()
{
    return boxPrim2(sigLRightShift);
}
EXPORT Tree boxARightShift()
{
    return boxPrim2(sigARightShift);
}

EXPORT Tree boxGT()
{
    return boxPrim2(sigGT);
}
EXPORT Tree boxLT()
{
    return boxPrim2(sigLT);
}
EXPORT Tree boxGE()
{
    return boxPrim2(sigGE);
}
EXPORT Tree boxLE()
{
    return boxPrim2(sigLE);
}
EXPORT Tree boxEQ()
{
    return boxPrim2(sigEQ);
}
EXPORT Tree boxNE()
{
    return boxPrim2(sigNE);
}

EXPORT Tree boxAND()
{
    return boxPrim2(sigAND);
}
EXPORT Tree boxOR()
{
    return boxPrim2(sigOR);
}
EXPORT Tree boxXOR()
{
    return boxPrim2(sigXOR);
}

// Extended unary of binary mathematical functions

EXPORT Tree boxAbs()
{
    return gGlobal->gAbsPrim->box();
}
EXPORT Tree boxAcos()
{
    return gGlobal->gAcosPrim->box();
}
EXPORT Tree boxTan()
{
    return gGlobal->gTanPrim->box();
}
EXPORT Tree boxSqrt()
{
    return gGlobal->gSqrtPrim->box();
}
EXPORT Tree boxSin()
{
    return gGlobal->gSinPrim->box();
}
EXPORT Tree boxRint()
{
    return gGlobal->gRintPrim->box();
}
EXPORT Tree boxRemainder()
{
    return gGlobal->gRemainderPrim->box();
}
EXPORT Tree boxPow()
{
    return gGlobal->gPowPrim->box();
}
EXPORT Tree boxMin()
{
    return gGlobal->gMinPrim->box();
}
EXPORT Tree boxMax()
{
    return gGlobal->gMaxPrim->box();
}
EXPORT Tree boxLog()
{
    return gGlobal->gLogPrim->box();
}
EXPORT Tree boxLog10()
{
    return gGlobal->gLog10Prim->box();
}
EXPORT Tree boxFmod()
{
    return gGlobal->gAbsPrim->box();
}
EXPORT Tree boxFloor()
{
    return gGlobal->gFloorPrim->box();
}
EXPORT Tree boxExp()
{
    return gGlobal->gExpPrim->box();
}
EXPORT Tree boxExp10()
{
    return gGlobal->gExp10Prim->box();
}
EXPORT Tree boxCos()
{
    return gGlobal->gAbsPrim->box();
}
EXPORT Tree boxCeil()
{
    return gGlobal->gCeilPrim->box();
}
EXPORT Tree boxAtan()
{
    return gGlobal->gAtanPrim->box();
}
EXPORT Tree boxAtan2()
{
    return gGlobal->gAtan2Prim->box();
}
EXPORT Tree boxAsin()
{
    return gGlobal->gAsinPrim->box();
}

// User Interface

EXPORT Tree boxButton(const std::string& label)
{
    return boxButton(tree(label));
}

EXPORT Tree boxCheckbox(const std::string& label)
{
    return boxButton(tree(label));
}

EXPORT Tree boxVSlider(const std::string& label, Tree init, Tree min, Tree max, Tree step)
{
    return boxVSlider(tree(label), init, min, max, step);
}

EXPORT Tree boxHSlider(const std::string& label, Tree init, Tree min, Tree max, Tree step)
{
    return boxHSlider(tree(label), init, min, max, step);
}

EXPORT Tree boxNumEntry(const std::string& label, Tree init, Tree min, Tree max, Tree step)
{
    return boxNumEntry(tree(label), init, min, max, step);
}

EXPORT Tree boxVBargraph(const std::string& label, Tree min, Tree max)
{
    return boxVBargraph(tree(label), min, max);
}

EXPORT Tree boxHBargraph(const std::string& label, Tree min, Tree max)
{
    return boxHBargraph(tree(label), min, max);
}

EXPORT Tree boxAttach()
{
    return boxPrim2(sigAttach);
}

// Helpers

EXPORT Tree boxPar3(Tree x, Tree y, Tree z)
{
    return boxPar(x, boxPar(y, z));
}

EXPORT Tree boxPar4(Tree a, Tree b, Tree c, Tree d)
{
    return boxPar(a, boxPar3(b, c, d));
}

EXPORT Tree boxPar5(Tree a, Tree b, Tree c, Tree d, Tree e)
{
    return boxPar(a, boxPar4(b, c, d, e));
}

EXPORT Tree boxDelay(Tree s, Tree del)
{
    return boxSeq(boxPar(s, del), boxDelay());
}

EXPORT Tree boxIntCast(Tree s)
{
    return boxSeq(s, boxIntCast());
}

EXPORT Tree boxFloatCast(Tree s)
{
    return boxSeq(s, boxFloatCast());
}

EXPORT Tree boxReadOnlyTable(Tree n, Tree init, Tree ridx)
{
    return boxSeq(boxPar3(n, init, ridx), boxReadOnlyTable());
}

EXPORT Tree boxWriteReadTable(Tree n, Tree init, Tree widx, Tree wsig, Tree ridx)
{
    return boxSeq(boxPar5(n, init, widx, wsig, ridx), boxWriteReadTable());
}

EXPORT Tree boxSoundfile(const std::string& label, Tree chan, Tree part, Tree ridx)
{
    return boxSeq(boxPar(part, ridx), boxSoundfile(label, chan));
}

EXPORT Tree boxSelect2(Tree selector, Tree s1, Tree s2)
{
    return boxSeq(boxPar3(selector, s1, s2), boxSelect2());
}

EXPORT Tree boxSelect3(Tree selector, Tree s1, Tree s2, Tree s3)
{
    return boxSeq(boxPar4(selector, s1, s2, s3), boxSelect3());
}

EXPORT Tree boxBinOp(SOperator op, Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxBinOp(op));
}

EXPORT Tree boxAdd(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxAdd());
}

EXPORT Tree boxSub(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxSub());
}

EXPORT Tree boxMul(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxMul());
}

EXPORT Tree boxDiv(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxDiv());
}

EXPORT Tree boxRem(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxRem());
}

EXPORT Tree boxLeftShift(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxLeftShift());
}

EXPORT Tree boxLRightShift(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxLRightShift());
}

EXPORT Tree boxARightShift(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxARightShift());
}

EXPORT Tree boxGT(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxGT());
}

EXPORT Tree boxLT(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxLT());
}

EXPORT Tree boxGE(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxGE());
}

EXPORT Tree boxLE(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxLE());
}

EXPORT Tree boxEQ(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxEQ());
}

EXPORT Tree boxNE(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxNE());
}

EXPORT Tree boxAND(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxAND());
}

EXPORT Tree boxOR(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxOR());
}

EXPORT Tree boxXOR(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxXOR());
}

EXPORT Tree boxAbs(Tree x)
{
    return boxSeq(x, boxAbs());
}

EXPORT Tree boxAcos(Tree x)
{
    return boxSeq(x, boxAcos());
}

EXPORT Tree boxTan(Tree x)
{
    return boxSeq(x, boxTan());
}

EXPORT Tree boxSqrt(Tree x)
{
    return boxSeq(x, boxSqrt());
}

EXPORT Tree boxSin(Tree x)
{
    return boxSeq(x, boxSin());
}

EXPORT Tree boxRint(Tree x)
{
    return boxSeq(x, boxRint());
}

EXPORT Tree boxLog(Tree x)
{
    return boxSeq(x, boxLog());
}

EXPORT Tree boxLog10(Tree x)
{
    return boxSeq(x, boxLog10());
}

EXPORT Tree boxFloor(Tree x)
{
    return boxSeq(x, boxFloor());
}

EXPORT Tree boxExp(Tree x)
{
    return boxSeq(x, boxExp());
}

EXPORT Tree boxExp10(Tree x)
{
    return boxSeq(x, boxExp10());
}

EXPORT Tree boxCos(Tree x)
{
    return boxSeq(x, boxCos());
}

EXPORT Tree boxCeil(Tree x)
{
    return boxSeq(x, boxCeil());
}

EXPORT Tree boxAtan(Tree x)
{
    return boxSeq(x, boxAtan());
}

EXPORT Tree boxAsin(Tree x)
{
    return boxSeq(x, boxAsin());
}

EXPORT Tree boxRemainder(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxRemainder());
}

EXPORT Tree boxPow(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxPow());
}

EXPORT Tree boxMin(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxMin());
}

EXPORT Tree boxMax(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxMax());
}

EXPORT Tree boxFmod(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxFmod());
}

EXPORT Tree boxAtan2(Tree b1, Tree b2)
{
    return boxSeq(boxPar(b1, b2), boxAtan2());
}

EXPORT Tree boxVBargraph(const std::string& label, Tree min, Tree max, Tree x)
{
    return boxSeq( x, boxVBargraph(label, min, max));
}

EXPORT Tree boxHBargraph(const std::string& label, Tree min, Tree max, Tree x)
{
    return boxSeq(x, boxHBargraph(label, min, max));
}

EXPORT Tree boxAttach(Tree s1, Tree s2)
{
    return boxSeq(boxPar(s1, s2), boxAttach());
}

// ==========
// Box C API
// ==========

#ifdef __cplusplus
extern "C"
{
#endif
    
    EXPORT Tree* CboxesToSignals(Tree box, char* error_msg)
    {
        string error_msg_aux;
        tvec signals = boxesToSignals(box, error_msg_aux);
        strncpy(error_msg, error_msg_aux.c_str(), 4096);
        if (signals.size() > 0) {
            Tree* res = (Tree*)malloc(sizeof(Tree) * (signals.size() + 1));
            size_t i;
            for (i = 0; i < signals.size(); i++) res[i] = signals[i];
            res[i] = NULL;
            return res;
        } else {
            return NULL;
        }
    }
    
    EXPORT Tree CboxInt(int n)
    {
        return boxInt(n);
    }
    
    EXPORT Tree CboxReal(double n)
    {
        return boxReal(n);
    }
    
    EXPORT Tree CboxWire()
    {
        return boxWire();
    }
    
    EXPORT Tree CboxCut()
    {
        return boxCut();
    }
    
    EXPORT Tree CboxSeq(Tree x, Tree y)
    {
        return boxSeq(x, y);
    }
    
    EXPORT Tree CboxPar(Tree x, Tree y)
    {
        return boxPar(x, y);
    }
    
    EXPORT Tree CboxSplit(Tree x, Tree y)
    {
        return boxSplit(x, y);
    }
    
    EXPORT Tree CboxMerge(Tree x, Tree y)
    {
        return boxMerge(x, y);
    }
    
    EXPORT Tree CboxRec(Tree x, Tree y)
    {
        return boxRec(x, y);
    }
    
    EXPORT Tree CboxRoute(Tree n, Tree m, Tree r)
    {
        return boxRoute(n, m, r);
    }
    
    EXPORT Tree CboxDelay()
    {
        return boxDelay();
    }
    
    EXPORT Tree CboxIntCast()
    {
        return boxIntCast();
    }
    
    EXPORT Tree CboxFloatCast()
    {
        return boxFloatCast();
    }
    
    EXPORT Tree CboxReadOnlyTable()
    {
        return boxReadOnlyTable();
    }
    
    EXPORT Tree CboxWriteReadTable()
    {
        return boxWriteReadTable();
    }
    
    EXPORT Tree CboxWaveform(Tree* wf_aux)
    {
        tvec wf;
        int i = 0;
        while (wf_aux[i]) { wf.push_back(wf_aux[i]); i++; }
        return boxWaveform(wf);
    }
    
    EXPORT Tree CboxSoundfile(const char* label, Tree chan)
    {
        return boxSoundfile(label, chan);
    }
    
    EXPORT Tree CboxSelect2()
    {
        return boxSelect2();
    }
    
    EXPORT Tree CboxSelect3()
    {
        return boxSelect3();
    }
    
    EXPORT Tree CboxFConst(SType type, const char* name, const char* file)
    {
        return boxFConst(type, name, file);
    }
    
    EXPORT Tree CboxFVar(SType type, const char* name, const char* file)
    {
        return boxFVar(type, name, file);
    }
    
    EXPORT Tree CboxBinOp(SOperator op)
    {
        return boxBinOp(op);
    }
    
    // Specific binary mathematical functions
    
    EXPORT Tree CboxAdd()
    {
        return boxAdd();
    }
    EXPORT Tree CboxSub()
    {
        return boxSub();
    }
    EXPORT Tree CboxMul()
    {
        return boxMul();
    }
    EXPORT Tree CboxDiv()
    {
        return boxDiv();
    }
    EXPORT Tree CboxRem()
    {
        return boxRem();
    }
    
    EXPORT Tree CboxLeftShift()
    {
        return boxLeftShift();
    }
    EXPORT Tree CboxLRightShift()
    {
        return boxLRightShift();
    }
    EXPORT Tree CboxARightShift()
    {
        return boxARightShift();
    }
    
    EXPORT Tree CboxGT()
    {
        return boxGT();
    }
    EXPORT Tree CboxLT()
    {
        return boxLT();
    }
    EXPORT Tree CboxGE()
    {
        return boxGE();
    }
    EXPORT Tree CboxLE()
    {
        return boxLE();
    }
    EXPORT Tree CboxEQ()
    {
        return boxEQ();
    }
    EXPORT Tree CboxNE()
    {
        return boxNE();
    }
    
    EXPORT Tree CboxAND()
    {
        return boxAND();
    }
    EXPORT Tree CboxOR()
    {
        return boxOR();
    }
    EXPORT Tree CboxXOR()
    {
        return boxXOR();
    }
    
    // Extended unary of binary mathematical functions
    
    EXPORT Tree CboxAbs()
    {
        return boxAbs();
    }
    EXPORT Tree CboxAcos()
    {
        return boxAcos();
    }
    EXPORT Tree CboxTan()
    {
        return boxTan();
    }
    EXPORT Tree CboxSqrt()
    {
        return boxSqrt();
    }
    EXPORT Tree CboxSin()
    {
        return boxSin();
    }
    EXPORT Tree CboxRint()
    {
        return boxRint();
    }
    EXPORT Tree CboxRemainder()
    {
        return boxRemainder();
    }
    EXPORT Tree CboxPow()
    {
        return boxPow();
    }
    EXPORT Tree CboxMin()
    {
        return boxMin();
    }
    EXPORT Tree CboxMax()
    {
        return boxMax();
    }
    EXPORT Tree CboxLog()
    {
        return boxLog();
    }
    EXPORT Tree CboxLog10()
    {
        return boxLog10();
    }
    EXPORT Tree CboxFmod()
    {
        return boxFmod();
    }
    EXPORT Tree CboxFloor()
    {
        return boxFloor();
    }
    EXPORT Tree CboxExp()
    {
        return boxExp();
    }
    EXPORT Tree CboxExp10()
    {
        return boxExp10();
    }
    EXPORT Tree CboxCos()
    {
        return boxCos();
    }
    EXPORT Tree CboxCeil()
    {
        return boxCeil();
    }
    EXPORT Tree CboxAtan()
    {
        return boxAtan();
    }
    EXPORT Tree CboxAtan2()
    {
        return boxAtan2();
    }
    EXPORT Tree CboxAsin()
    {
        return boxAsin();
    }
    
    // User Interface
    
    EXPORT Tree CboxButton(const char* label)
    {
        return boxButton(label);
    }
    
    EXPORT Tree CboxCheckbox(const char* label)
    {
        return boxButton(label);
    }
    
    EXPORT Tree CboxVSlider(const char* label, Tree init, Tree min, Tree max, Tree step)
    {
        return boxVSlider(label, init, min, max, step);
    }
    
    EXPORT Tree CboxHSlider(const char* label, Tree init, Tree min, Tree max, Tree step)
    {
        return boxHSlider(label, init, min, max, step);
    }
    
    EXPORT Tree CboxNumEntry(const char* label, Tree init, Tree min, Tree max, Tree step)
    {
        return boxNumEntry(label, init, min, max, step);
    }
    
    EXPORT Tree CboxVBargraph(const char* label, Tree min, Tree max)
    {
        return boxVBargraph(label, min, max);
    }
    
    EXPORT Tree CboxHBargraph(const char* label, Tree min, Tree max)
    {
        return boxHBargraph(label, min, max);
    }
    
    EXPORT Tree CboxAttach()
    {
        return boxAttach();
    }
    
    // Helpers
    
    Tree CboxPar3(Tree x, Tree y, Tree z)
    {
        return CboxPar(x, CboxPar(y, z));
    }
    
    Tree CboxPar4(Tree a, Tree b, Tree c, Tree d)
    {
        return CboxPar(a, CboxPar3(b, c, d));
    }
    
    Tree CboxPar5(Tree a, Tree b, Tree c, Tree d, Tree e)
    {
        return CboxPar(a, CboxPar4(b, c, d, e));
    }
    
    Tree CboxDelayAux(Tree s, Tree del)
    {
        return CboxSeq(CboxPar(s, del), CboxDelay());
    }
    
    Tree CboxIntCastAux(Tree s)
    {
        return CboxSeq(s, CboxIntCast());
    }
    
    Tree CboxFloatCastAux(Tree s)
    {
        return CboxSeq(s, CboxFloatCast());
    }
    
    Tree CboxReadOnlyTableAux(Tree n, Tree init, Tree ridx)
    {
        return CboxSeq(CboxPar3(n, init, ridx), CboxReadOnlyTable());
    }
    
    Tree CboxWriteReadTableAux(Tree n, Tree init, Tree widx, Tree wsig, Tree ridx)
    {
        return CboxSeq(boxPar5(n, init, widx, wsig, ridx), CboxWriteReadTable());
    }
    
    Tree CoxSoundfileAux(const char* label, Tree chan, Tree part, Tree ridx)
    {
        return CboxSeq(CboxPar(part, ridx), CboxSoundfile(label, chan));
    }
    
    Tree CboxSelect2Aux(Tree selector, Tree s1, Tree s2)
    {
        return CboxSeq(CboxPar3(selector, s1, s2), CboxSelect2());
    }
    
    Tree CboxSelect3Aux(Tree selector, Tree s1, Tree s2, Tree s3)
    {
        return CboxSeq(CboxPar4(selector, s1, s2, s3), CboxSelect3());
    }
    
    Tree CboxBinOpAux(SOperator op, Tree b1, Tree b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxBinOp(op));
    }
    
    Tree CboxAddAux(Tree b1, Tree b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxAdd());
    }
    
    Tree CboxSubAux(Tree b1, Tree b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxSub());
    }
    
    Tree CboxMulAux(Tree b1, Tree b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxMul());
    }
    
    Tree CboxDivAux(Tree b1, Tree b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxDiv());
    }
    
    Tree CboxRemAux(Tree b1, Tree b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxRem());
    }
    
    Tree CboxLeftShiftAux(Tree b1, Tree b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxLeftShift());
    }
    
    Tree CboxLRightShiftAux(Tree b1, Tree b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxLRightShift());
    }
    
    Tree CboxARightShiftAux(Tree b1, Tree b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxARightShift());
    }
    
    Tree CboxGTAux(Tree b1, Tree b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxGT());
    }
    
    Tree CboxLTAux(Tree b1, Tree b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxLT());
    }
    
    Tree CboxGEAux(Tree b1, Tree b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxGE());
    }
    
    Tree CboxLEAux(Tree b1, Tree b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxLE());
    }
    
    Tree CboxEQAux(Tree b1, Tree b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxEQ());
    }
    
    Tree CboxNEAux(Tree b1, Tree b2)
    {
    return CboxSeq(CboxPar(b1, b2), CboxNE());
    }
    
    Tree CboxANDAux(Tree b1, Tree b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxAND());
    }
    
    Tree CboxORAux(Tree b1, Tree b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxOR());
    }
    
    Tree CboxXORAux(Tree b1, Tree b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxXOR());
    }
    
    Tree CboxAbsAux(Tree x)
    {
        return CboxSeq(x, CboxAbs());
    }
    
    Tree CboxAcosAux(Tree x)
    {
        return CboxSeq(x, CboxAcos());
    }
    
    Tree CboxTanAux(Tree x)
    {
        return CboxSeq(x, CboxTan());
    }
    
    Tree CboxSqrtAux(Tree x)
    {
        return CboxSeq(x, CboxSqrt());
    }
    
    Tree CboxSinAux(Tree x)
    {
        return CboxSeq(x, CboxSin());
    }
    
    Tree CboxRintAux(Tree x)
    {
        return CboxSeq(x, CboxRint());
    }
    
    Tree CboxLogAux(Tree x)
    {
        return CboxSeq(x, CboxLog());
    }
    
    Tree CboxLog10Aux(Tree x)
    {
        return CboxSeq(x, CboxLog10());
    }
    
    Tree CboxFloorAux(Tree x)
    {
        return CboxSeq(x, CboxFloor());
    }
    
    Tree CboxExpAux(Tree x)
    {
        return CboxSeq(x, CboxExp());
    }
    
    Tree CboxExp10Aux(Tree x)
    {
        return CboxSeq(x, CboxExp10());
    }
    
    Tree CboxCosAux(Tree x)
    {
        return CboxSeq(x, CboxCos());
    }
    
    Tree CboxCeilAux(Tree x)
    {
        return CboxSeq(x, CboxCeil());
    }
    
    Tree CboxAtanAux(Tree x)
    {
        return CboxSeq(x, CboxAtan());
    }
    
    Tree CboxAsinAux(Tree x)
    {
        return CboxSeq(x, CboxAsin());
    }
    
    Tree CboxRemainderAux(Tree b1, Tree b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxRemainder());
    }
    
    Tree CboxPowAux(Tree b1, Tree b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxPow());
    }
    
    Tree CboxMinAux(Tree b1, Tree b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxMin());
    }
    
    Tree CboxMaxAux(Tree b1, Tree b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxMax());
    }
    
    Tree CboxFmodAux(Tree b1, Tree b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxFmod());
    }
    
    Tree CboxAtan2Aux(Tree b1, Tree b2)
    {
        return CboxSeq(CboxPar(b1, b2), CboxAtan2());
    }
    
    Tree CboxVBargraphAux(const char* label, Tree min, Tree max, Tree x)
    {
        return CboxSeq(x, CboxVBargraph(label, min, max));
    }
    
    Tree CboxHBargraphAux(const char* label, Tree min, Tree max, Tree x)
    {
        return CboxSeq(x, CboxHBargraph(label, min, max));
    }
    
    Tree CboxAttachAux(Tree s1, Tree s2)
    {
        return CboxSeq(CboxPar(s1, s2), CboxAttach());
    }

#ifdef __cplusplus
}
#endif
