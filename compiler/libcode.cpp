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

#include <float.h>
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
#include "libfaust.h"
#include "ppbox.hh"
#include "ppsig.hh"
#include "privatise.hh"
#include "propagate.hh"
#include "recursivness.hh"
#include "rust_instructions_compiler.hh"
#include "schema.h"
#include "signals.hh"
#include "sigprint.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"
#include "simplify.hh"
#include "sourcereader.hh"
#include "timing.hh"

#ifdef C_BUILD
#include "c_code_container.hh"
#endif

#ifdef CPP_BUILD
#include "cpp_code_container.hh"
#include "cpp_gpu_code_container.hh"
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

#ifdef LLVM_BUILD
#include "clang_code_container.hh"
#include "llvm_code_container.hh"
#endif

#ifdef OCPP_BUILD
#include "compile_graph.hh"
#include "compile_scal.hh"
#include "compile_sched.hh"
#include "compile_vect.hh"
#endif

#ifdef RUST_BUILD
#include "rust_code_container.hh"
#endif

#ifdef WASM_BUILD
#include "wasm_code_container.hh"
#include "wast_code_container.hh"
#endif

#ifdef SOUL_BUILD
#include "soul_code_container.hh"
#endif

using namespace std;

extern const char* mathsuffix[4];
extern const char* numsuffix[4];
extern const char* floatname[4];
extern const char* castname[4];
extern double      floatmin[4];

static ifstream* injcode  = NULL;
static ifstream* enrobage = NULL;

#ifdef OCPP_BUILD
// Old CPP compiler
Compiler* old_comp = NULL;
#endif

// FIR container
InstructionsCompiler* new_comp  = NULL;
CodeContainer*        container = NULL;

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

#ifdef FIR_BUILD
    out << dspto << "FIR" << endl;
#endif

#ifdef INTERP_BUILD
    out << dspto << "Interpreter" << endl;
#endif

#ifdef JAVA_BUILD
    out << dspto << "Java" << endl;
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

#ifdef WASM_BUILD
    out << dspto << "WebAssembly (wast/wasm)" << endl;
#endif

#ifdef SOUL_BUILD
    out << dspto << "SOUL" << endl;
#endif
}

#ifdef _WIN32
static void callFun(compile_fun fun)
{
    fun(NULL);
}
#else
static void callFun(compile_fun fun)
{
#ifdef EMCC
    // No thread support in JS
    fun(NULL);
#else
    pthread_t      thread;
    pthread_attr_t attr;
    faustassert(pthread_attr_init(&attr) == 0);
    faustassert(pthread_attr_setstacksize(&attr, MAX_STACK_SIZE) == 0);
    faustassert(pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE) == 0);
    faustassert(pthread_create(&thread, &attr, fun, NULL) == 0);
    pthread_join(thread, NULL);
#endif
}
#endif

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

global* gGlobal = NULL;

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
        printf("processCmdline i = %d cmd = %s\n", i, argv[i]);
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

        } else if (isCmd(argv[i], "-lb", "--left-balanced")) {
            gGlobal->gBalancedSwitch = 0;
            i += 1;

        } else if (isCmd(argv[i], "-mb", "--mid-balanced")) {
            gGlobal->gBalancedSwitch = 1;
            i += 1;

        } else if (isCmd(argv[i], "-rb", "--right-balanced")) {
            gGlobal->gBalancedSwitch = 2;
            i += 1;

        } else if (isCmd(argv[i], "-lt", "--less-temporaries")) {
            gGlobal->gLessTempSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-mcd", "--max-copy-delay") && (i + 1 < argc)) {
            gGlobal->gMaxCopyDelay = std::atoi(argv[i + 1]);
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

            // double float options
        } else if (isCmd(argv[i], "-single", "--single-precision-floats")) {
            if (float_size) {
                throw faustexception("ERROR : cannot using -single, -double or -quad at the same time\n");
            } else {
                float_size = true;
            }
            gGlobal->gFloatSize = 1;
            i += 1;

        } else if (isCmd(argv[i], "-double", "--double-precision-floats")) {
            if (float_size) {
                throw faustexception("ERROR : cannot using -single, -double or -quad at the same time\n");
            } else {
                float_size = true;
            }
            gGlobal->gFloatSize = 2;
            i += 1;

        } else if (isCmd(argv[i], "-quad", "--quad-precision-floats")) {
            if (float_size) {
                throw faustexception("ERROR : cannot using -single, -double or -quad at the same time\n");
            } else {
                float_size = true;
            }
            gGlobal->gFloatSize = 3;
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
            gGlobal->gClassName = argv[i + 1];
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

        } else if (isCmd(argv[i], "-os", "--one-sample")) {
            gGlobal->gOneSample = true;
            i += 1;

        } else if (isCmd(argv[i], "-ftz", "--flush-to-zero")) {
            gGlobal->gFTZMode = std::atoi(argv[i + 1]);
            if ((gGlobal->gFTZMode > 2) || (gGlobal->gFTZMode < 0)) {
                stringstream error;
                error << "ERROR : invalid -ftz option: " << gGlobal->gFTZMode << endl;
                throw faustexception(error.str());
            }
            i += 2;

        } else if (isCmd(argv[i], "-fm", "--fast-math")) {
            gGlobal->gFastMath    = true;
            gGlobal->gFastMathLib = argv[i + 1];
            i += 2;

        } else if (isCmd(argv[i], "-I", "--import-dir") && (i + 1 < argc)) {
            if ((strstr(argv[i + 1], "http://") != 0) || (strstr(argv[i + 1], "https://") != 0)) {
                gGlobal->gImportDirList.push_back(argv[i + 1]);
            } else {
                char  temp[PATH_MAX + 1];
                char* path = realpath(argv[i + 1], temp);
                if (path) {
                    gGlobal->gImportDirList.push_back(path);
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
        throw faustexception("ERROR : 'in-place' option can only be used in scalar mode\n");
    }
#if 0
    if (gGlobal->gOutputLang == "ocpp" && gGlobal->gVectorSwitch) {
        throw faustexception("ERROR : 'ocpp' backend can only be used in scalar mode\n");
    }
#endif
    if (gGlobal->gOneSample && gGlobal->gOutputLang != "cpp" && gGlobal->gOutputLang != "c" &&
        startWith(gGlobal->gOutputLang, "soul") && gGlobal->gOutputLang != "fir") {
        throw faustexception("ERROR : '-os' option cannot only be used with 'cpp', 'c', 'fir' or 'soul' backends\n");
    }

    if (gGlobal->gOneSample && gGlobal->gVectorSwitch) {
        throw faustexception("ERROR : '-os' option cannot only be used in scalar mode\n");
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

    if (gGlobal->gFastMath) {
        if (!(gGlobal->gOutputLang == "c" || gGlobal->gOutputLang == "cpp" || gGlobal->gOutputLang == "llvm" ||
              startWith(gGlobal->gOutputLang, "wast") || startWith(gGlobal->gOutputLang, "wasm"))) {
            stringstream error;
            error << "ERROR : -fm can only be used with c, cpp, or llvm backends" << endl;
            throw faustexception(error.str());
        }
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

static void printLibDir()
{
    cout << gGlobal->gFaustRootDir << kPSEP << "lib" << endl;
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
    cout << "Copyright (C) 2002-2019, GRAME - Centre National de Creation Musicale. All rights reserved. \n";
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
    cout << tab << "-e        --export-dsp                  export expanded DSP (all included libraries)." << endl;
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
         << "                                        'lang' should be in c, ocpp, cpp (default), rust, java, "
            "llvm, cllvm, fir, wast/wasm, soul, interp."
         << endl;
    cout << tab
         << "-single     --single-precision-floats   use single precision floats for internal computations (default)."
         << endl;
    cout << tab << "-double     --double-precision-floats   use double precision floats for internal computations."
         << endl;
    cout << tab << "-quad       --quad-precision-floats     use quad precision floats for internal computations."
         << endl;
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
    cout << tab << "-flist      --file-list                 use file list used to eval process." << endl;
    cout << tab << "-exp10      --generate-exp10            function call instead of pow(10) function." << endl;
    cout << tab << "-os         --one-sample                generate one sample computation." << endl;
    cout << tab
         << "-cn <name>  --class-name <name>         specify the name of the dsp class to be used instead of mydsp."
         << endl;
    cout << tab
         << "-scn <name> --super-class-name <name>   specify the name of the super class to be used instead of dsp."
         << endl;
    cout << tab << "-pn <name>  --process-name <name>       specify the name of the dsp entry-point instead of process."
         << endl;
    cout << tab << "-lb         --left-balanced             generate left balanced expressions." << endl;
    cout << tab << "-mb         --mid-balanced              generate mid balanced expressions (default)." << endl;
    cout << tab << "-rb         --right-balanced            generate right balanced expressions." << endl;
    cout << tab << "-lt         --less-temporaries          generate less temporaries in compiling delays." << endl;
    cout << tab
         << "-mcd <n>    --max-copy-delay <n>        threshold between copy and ring buffer implementation (default 16 "
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
         << "-inj <f>    --inject <f>                inject source file <f> into architecture file instead of compile "
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
            "<file>,"
         << endl;
    cout << tab << "                                        use 'faust/dsp/fastmath.cpp' when file is 'def'." << endl;

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
         << "-fc <n>    --fold-complexity <n>       complexity threshold to fold an expression in folding mode "
            "(default 2)"
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
    cout << tab << "-tg         --task-graph                print the internal task graph in dot format." << endl;
    cout << tab << "-sg         --signal-graph              print the internal signal graph in dot format." << endl;
    cout << tab << "-norm       --normalized-form           print signals in normalized form and exit." << endl;

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
    for (MetaDataSet::iterator i = gGlobal->gMetaDataSet.begin(); i != gGlobal->gMetaDataSet.end(); i++) {
        if (i->first != tree("author")) {
            dst << "declare ";
            stringstream key;
            key << *(i->first);
            std::vector<char> to_replace{'.', ':', '/'};
            dst << replaceCharList(key.str(), to_replace, '_');
            dst << " " << **(i->second.begin()) << ";" << endl;
        } else {
            for (set<Tree>::iterator j = i->second.begin(); j != i->second.end(); ++j) {
                if (j == i->second.begin()) {
                    dst << "declare " << *(i->first) << " " << **j << ";" << endl;
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
    for (map<Tree, set<Tree> >::iterator i = gGlobal->gMetaDataSet.begin(); i != gGlobal->gMetaDataSet.end(); i++) {
        if (selectedKeys.count(i->first)) {
            dst << "// " << *(i->first);
            const char* sep = ": ";
            for (set<Tree>::iterator j = i->second.begin(); j != i->second.end(); ++j) {
                dst << sep << **j;
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
    unsigned int p1 = 0;
    for (unsigned int i = 0; i < filename.size(); i++) {
        if (filename[i] == '/') {
            p1 = i + 1;
        }
    }

    // determine position of the last '.'
    size_t p2 = filename.size();
    for (unsigned int i = p1; i < filename.size(); i++) {
        if (filename[i] == '.') {
            p2 = i;
        }
    }

    return filename.substr(p1, p2 - p1);
}

static void initFaustFloat()
{
    // Using in FIR code generation to code math functions type (float/double/quad), same for Rust and C/C++ backends
    mathsuffix[0] = "";
    mathsuffix[1] = "f";
    mathsuffix[2] = "";
    mathsuffix[3] = "l";

    // Specific for Rust backend
    if (gGlobal->gOutputLang == "rust") {
        numsuffix[0] = "";
        numsuffix[1] = "";
        numsuffix[2] = "";
        numsuffix[3] = "";

        floatname[0] = FLOATMACRO;
        floatname[1] = "f32";
        floatname[2] = "f64";
        floatname[3] = "dummy";

        castname[0] = FLOATCASTER;
        castname[1] = "as f32";
        castname[2] = "as f64";
        castname[3] = "(dummy)";

        floatmin[0] = 0;
        floatmin[1] = FLT_MIN;
        floatmin[2] = DBL_MIN;
        floatmin[3] = LDBL_MIN;

        // Specific for C/C++ backends
    } else {
        numsuffix[0] = "";
        numsuffix[1] = "f";
        numsuffix[2] = "";
        numsuffix[3] = "L";

        floatname[0] = FLOATMACRO;
        floatname[1] = "float";
        floatname[2] = "double";
        floatname[3] = "quad";

        castname[0] = FLOATCASTER;
        castname[1] = "(float)";
        castname[2] = "(double)";
        castname[3] = "(quad)";

        floatmin[0] = 0;
        floatmin[1] = FLT_MIN;
        floatmin[2] = DBL_MIN;
        floatmin[3] = LDBL_MIN;
    }
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
    // cout << "expandedDefList " << *expandedDefList << endl;

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

    if (gGlobal->gDrawPSSwitch || gGlobal->gDrawSVGSwitch) {
        string projname = gGlobal->makeDrawPathNoExt();
        if (gGlobal->gDrawPSSwitch) {
            drawSchema(process, subst("$0-ps", projname).c_str(), "ps");
        }
        if (gGlobal->gDrawSVGSwitch) {
            drawSchema(process, subst("$0-svg", projname).c_str(), "svg");
        }
    }

    if (!getBoxType(process, &numInputs, &numOutputs)) {
        stringstream error;
        error << "ERROR during the evaluation of process : " << boxpp(process) << endl;
        throw faustexception(error.str());
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
        for (unsigned int i = 0; i < pathnames.size(); i++) cout << pathnames[i] << endl;
        cout << "---------------------------\n";
        cout << endl;
    }

    return process;
}

static void includeFile(const string& file, ostream* dst)
{
    istream* file_include = openArchStream(file.c_str());
    if (file_include) {
        streamCopyUntilEnd(*file_include, *dst);
    }
    delete file_include;
}

static void injectCode(ifstream* enrobage, ostream* dst)
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
            streamCopyUntil(*enrobage, *dst, "<<includeIntrinsic>>");
            streamCopyUntil(*enrobage, *dst, "<<includeclass>>");
            streamCopyUntilEnd(*injcode, *dst);
            streamCopyUntilEnd(*enrobage, *dst);
        }
        delete injcode;
        throw faustexception("");
    }
}

static void generateCode(Tree signals, int numInputs, int numOutputs, bool generate)
{
    ostream* dst     = NULL;
    ostream* helpers = NULL;
    string   outpath = "";

    // Finally output file
    if (gGlobal->gOutputFile == "string") {
        dst = new stringstream();
    } else if (gGlobal->gOutputFile == "binary") {
        dst = new stringstream(stringstream::out | stringstream::binary);
    } else if (gGlobal->gOutputFile != "") {
        outpath =
            (gGlobal->gOutputDir != "") ? (gGlobal->gOutputDir + "/" + gGlobal->gOutputFile) : gGlobal->gOutputFile;
        ofstream* fdst = new ofstream(outpath.c_str());
        if (!fdst->is_open()) {
            stringstream error;
            error << "ERROR : file '" << outpath << "' cannot be opened\n";
            throw faustexception(error.str());
        } else {
            dst = fdst;
        }
    } else {
        dst = &cout;
    }

    startTiming("generateCode");

#ifdef LLVM_BUILD
    if (gGlobal->gOutputLang == "cllvm") {
        // FIR is generated with internal real instead of FAUSTFLOAT (see InstBuilder::genBasicTyped)
        gGlobal->gFAUSTFLOATToInternal = true;
#ifdef CLANG_BUILD
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
#endif

    } else if (gGlobal->gOutputLang == "llvm") {
        container = LLVMCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs);

        // libc functions will be found by the LLVM linker, but not user defined ones...
        gGlobal->gAllowForeignFunction = true;
        // FIR is generated with internal real instead of FAUSTFLOAT (see InstBuilder::genBasicTyped)
        gGlobal->gFAUSTFLOATToInternal = true;

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
    if (gGlobal->gOutputLang == "llvm" || gGlobal->gOutputLang == "cllvm") {
        throw faustexception("ERROR : -lang llvm/cllvm not supported since LLVM backend is not built\n");
#endif

    } else if (gGlobal->gOutputLang == "interp") {
#ifdef INTERP_BUILD
        if (gGlobal->gFloatSize == 1) {
            container = InterpreterCodeContainer<float>::createContainer(gGlobal->gClassName, numInputs, numOutputs);
        } else if (gGlobal->gFloatSize == 2) {
            container = InterpreterCodeContainer<double>::createContainer(gGlobal->gClassName, numInputs, numOutputs);
        } else {
            throw faustexception("ERROR : quad format not supported in Interp\n");
        }

        gGlobal->gAllowForeignFunction = false;  // No foreign functions
        gGlobal->gGenerateSelectWithIf = false;  // No 'select with if',
        gGlobal->gComputeIOTA          = true;   // Ensure IOTA base fixed delays are computed once
        // FIR is generated with internal real instead of FAUSTFLOAT (see InstBuilder::genBasicTyped)
        gGlobal->gFAUSTFLOATToInternal = true;
        gGlobal->gNeedManualPow        = false;  // Standard pow function will be used in pow(x,y) when Y in an integer
        gGlobal->gRemoveVarAddress     = true;   // To be used in -vec mode

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
    } else if (gGlobal->gOutputLang == "fir") {
#ifdef FIR_BUILD
        gGlobal->gGenerateSelectWithIf = false;

        container = FIRCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, dst, true);

        if (gGlobal->gVectorSwitch) {
            new_comp = new DAGInstructionsCompiler(container);
        } else {
            new_comp = new InstructionsCompiler(container);
        }

        new_comp->compileMultiSignal(signals);
#else
        throw faustexception("ERROR : -lang fir not supported since FIR backend is not built\n");
#endif
    } else {
        gGlobal->gGenerateSelectWithIf = false;

        if (gGlobal->gOutputLang == "c") {
#ifdef C_BUILD
            container = CCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, dst);
#else
            throw faustexception("ERROR : -lang c not supported since C backend is not built\n");
#endif

        } else if (gGlobal->gOutputLang == "cpp") {
#ifdef CPP_BUILD
            container = CPPCodeContainer::createContainer(gGlobal->gClassName, gGlobal->gSuperClassName, numInputs,
                                                          numOutputs, dst);
#else
            throw faustexception("ERROR : -lang cpp not supported since CPP backend is not built\n");
#endif

        } else if (gGlobal->gOutputLang == "ocpp") {
#ifdef OCPP_BUILD
            if (gGlobal->gSchedulerSwitch)
                old_comp = new SchedulerCompiler(gGlobal->gClassName, gGlobal->gSuperClassName, numInputs, numOutputs);
            else if (gGlobal->gVectorSwitch)
                old_comp = new VectorCompiler(gGlobal->gClassName, gGlobal->gSuperClassName, numInputs, numOutputs);
            else
                old_comp = new GraphCompiler(gGlobal->gClassName, gGlobal->gSuperClassName, numInputs, numOutputs);

            if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) old_comp->setDescription(new Description());

            old_comp->compileMultiSignal(signals);
#else
            throw faustexception("ERROR : -lang ocpp not supported since old CPP backend is not built\n");
#endif

        } else if (gGlobal->gOutputLang == "rust") {
#ifdef RUST_BUILD
            // FIR is generated with internal real instead of FAUSTFLOAT (see InstBuilder::genBasicTyped)
            gGlobal->gFAUSTFLOATToInternal = true;
            container = RustCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, dst);
#else
            throw faustexception("ERROR : -lang rust not supported since Rust backend is not built\n");
#endif

        } else if (gGlobal->gOutputLang == "java") {
#ifdef JAVA_BUILD
            gGlobal->gAllowForeignFunction = false;  // No foreign functions
            container = JAVACodeContainer::createContainer(gGlobal->gClassName, gGlobal->gSuperClassName, numInputs,
                                                           numOutputs, dst);
#else
            throw faustexception("ERROR : -lang java not supported since JAVA backend is not built\n");
#endif
        } else if (startWith(gGlobal->gOutputLang, "soul")) {
#ifdef SOUL_BUILD
            gGlobal->gAllowForeignFunction = false;  // No foreign functions
            // FIR is generated with internal real instead of FAUSTFLOAT (see InstBuilder::genBasicTyped)
            gGlobal->gFAUSTFLOATToInternal = true;

            // "one sample control" model by default;
            gGlobal->gOneSampleControl = true;
            gGlobal->gNeedManualPow    = false;  // Standard pow function will be used in pow(x,y) when Y in an integer

            container = SOULCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, dst);
#else
            throw faustexception("ERROR : -lang rust not supported since SOUL backend is not built\n");
#endif
        } else if (startWith(gGlobal->gOutputLang, "wast")) {
#ifdef WASM_BUILD
            gGlobal->gAllowForeignFunction = false;  // No foreign functions
            // FIR is generated with internal real instead of FAUSTFLOAT (see InstBuilder::genBasicTyped)
            gGlobal->gFAUSTFLOATToInternal = true;
            // the 'i' variable used in the scalar loop moves by bytes instead of frames
            gGlobal->gLoopVarInBytes   = true;
            gGlobal->gWaveformInDSP    = true;   // waveform are allocated in the DSP and not as global data
            gGlobal->gMachinePtrSize   = 4;      // WASM is currently 32 bits
            gGlobal->gNeedManualPow    = false;  // Standard pow function will be used in pow(x,y) when Y in an integer
            gGlobal->gRemoveVarAddress = true;   // To be used in -vec mode
            // gGlobal->gHasTeeLocal = true;   // combined store/load

            gGlobal->gUseDefaultSound = false;

            // This speedup (freeverb for instance) ==> to be done at signal level
            // gGlobal->gComputeIOTA = true;         // Ensure IOTA base fixed delays are computed once

            container = WASTCodeContainer::createContainer(
                gGlobal->gClassName, numInputs, numOutputs, dst,
                ((gGlobal->gOutputLang == "wast") || (gGlobal->gOutputLang == "wast-i")));

            // Additional file with JS code
            if (gGlobal->gOutputFile == "binary") {
                // Nothing
            } else if (gGlobal->gOutputFile != "") {
                string outpath_js;
                bool   res = replaceExtension(outpath, ".js", outpath_js);
                if (res) {
                    helpers = new ofstream(outpath_js.c_str());
                } else {
                    cerr << "WARNING : cannot generate helper JS file, outpath is incorrect : \"" << outpath << "\""
                         << endl;
                }
            } else {
                helpers = &cout;
            }
#else
            throw faustexception("ERROR : -lang wast not supported since WAST backend is not built\n");
#endif
        } else if (startWith(gGlobal->gOutputLang, "wasm")) {
#ifdef WASM_BUILD
            gGlobal->gAllowForeignFunction = false;  // No foreign functions
            // FIR is generated with internal real instead of FAUSTFLOAT (see InstBuilder::genBasicTyped)
            gGlobal->gFAUSTFLOATToInternal = true;
            // the 'i' variable used in the scalar loop moves by bytes instead of frames
            gGlobal->gLoopVarInBytes   = true;
            gGlobal->gWaveformInDSP    = true;   // waveform are allocated in the DSP and not as global data
            gGlobal->gMachinePtrSize   = 4;      // WASM is currently 32 bits
            gGlobal->gNeedManualPow    = false;  // Standard pow function will be used in pow(x,y) when Y in an integer
            gGlobal->gRemoveVarAddress = true;   // To be used in -vec mode
            // gGlobal->gHasTeeLocal = true;   // combined store/load

            gGlobal->gUseDefaultSound = false;

            // This speedup (freeverb for instance) ==> to be done at signal level
            // gGlobal->gComputeIOTA = true;         // Ensure IOTA base fixed delays are computed once

            container = WASMCodeContainer::createContainer(
                gGlobal->gClassName, numInputs, numOutputs, dst,
                ((gGlobal->gOutputLang == "wasm") || (gGlobal->gOutputLang == "wasm-i") ||
                 (gGlobal->gOutputLang == "wasm-ib")));

            // Additional file with JS code
            if (gGlobal->gOutputFile == "binary") {
                // Nothing
            } else if (gGlobal->gOutputFile != "") {
                string outpath_js;
                bool   res = replaceExtension(outpath, ".js", outpath_js);
                if (res) {
                    helpers = new ofstream(outpath_js.c_str());
                } else {
                    cerr << "WARNING : cannot generate helper JS file, outpath is incorrect : \"" << outpath << "\""
                         << endl;
                }
            } else {
                helpers = &cout;
            }
#else
            throw faustexception("ERROR : -lang wasm not supported since WASM backend is not built\n");
#endif
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
#ifdef RUST_BUILD
            else if (gGlobal->gOutputLang == "rust") {
                new_comp = new RustInstructionsCompiler(container);
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

            if ((enrobage = openArchStream(gGlobal->gArchFile.c_str()))) {
                // Possibly inject code
                injectCode(enrobage, dst);

                container->printHeader();

                streamCopyUntil(*enrobage, *dst, "<<includeIntrinsic>>");
                streamCopyUntil(*enrobage, *dst, "<<includeclass>>");

                if (gGlobal->gOpenCLSwitch || gGlobal->gCUDASwitch) {
                    includeFile("thread.h", dst);
                }

                container->printFloatDef();
                container->produceClass();

                streamCopyUntilEnd(*enrobage, *dst);

                if (gGlobal->gSchedulerSwitch) {
                    includeFile("scheduler.cpp", dst);
                }

                container->printFooter();

                // Force flush since the stream is not closed...
                dst->flush();

                // Restore current_directory
                if (current_directory) {
                    if (chdir(current_directory)) {  // return code is 0 on successful completion
                        cerr << "can't restore current directory (" << current_directory << ")" << endl;
                    }
                }
                delete enrobage;

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

            // Binary mode for LLVM backend if output different of 'cout'
            gGlobal->gDSPFactory->write(dst, (dst != &cout), false);

            // Force flush since the stream is not closed...
            dst->flush();

            if (helpers) {
                // Possibly helper code
                gGlobal->gDSPFactory->writeAux(helpers, (helpers != &cout), false);
                // Force flush since the stream is not closed...
                helpers->flush();
            }
        }

        endTiming("generateCode");

        // Delete streams if they were allocated
        if (dst != &cout) delete dst;
        if (helpers != &cout) delete helpers;

#ifdef OCPP_BUILD
    } else if (old_comp) {
        // Check for architecture file
        if (gGlobal->gArchFile != "") {
            if (!(enrobage = openArchStream(gGlobal->gArchFile.c_str()))) {
                stringstream error;
                error << "ERROR : can't open architecture file " << gGlobal->gArchFile << endl;
                throw faustexception(error.str());
            }
        }

        // Possibly inject code
        injectCode(enrobage, dst);

        printHeader(*dst);
        old_comp->getClass()->printLibrary(*dst);
        old_comp->getClass()->printIncludeFile(*dst);
        old_comp->getClass()->printAdditionalCode(*dst);

        if (gGlobal->gArchFile != "") {
            streamCopyUntil(*enrobage, *dst, "<<includeIntrinsic>>");

            if (gGlobal->gSchedulerSwitch) {
                istream* scheduler_include = openArchStream("old-scheduler.cpp");
                if (scheduler_include) {
                    streamCopyUntilEnd(*scheduler_include, *dst);
                } else {
                    throw("ERROR : can't include \"old-scheduler.cpp\", file not found>\n");
                }
            }

            streamCopyUntil(*enrobage, *dst, "<<includeclass>>");
            printfloatdef(*dst, gGlobal->gFloatSize == 3);
            old_comp->getClass()->println(0, *dst);
            streamCopyUntilEnd(*enrobage, *dst);

        } else {
            printfloatdef(*dst, gGlobal->gFloatSize == 3);
            old_comp->getClass()->println(0, *dst);
        }

        /****************************************************************
         9 - generate the task graph file in dot format
         *****************************************************************/

        if (gGlobal->gGraphSwitch) {
            ofstream dotfile(subst("$0.dot", gGlobal->makeDrawPath()).c_str());
            old_comp->getClass()->printGraphDotFormat(dotfile);
        }

        delete old_comp;
#endif
    } else {
        faustassert(false);
    }
}

static void generateOutputFiles()
{
    /****************************************************************
     1 - generate XML description (if required)
    *****************************************************************/

    if (gGlobal->gPrintXMLSwitch) {
        if (new_comp) {
            Description* D = new_comp->getDescription();
            faustassert(D);
            ofstream xout(subst("$0.xml", gGlobal->makeDrawPath()).c_str());

            const MetaDataSet&          mds = gGlobal->gMetaDataSet;
            MetaDataSet::const_iterator it1;
            set<Tree>::const_iterator   it2;

            for (it1 = mds.begin(); it1 != mds.end(); ++it1) {
                const std::string key = tree2str(it1->first);
                for (it2 = it1->second.begin(); it2 != it1->second.end(); ++it2) {
                    const std::string value = tree2str(*it2);
                    if (key == "name")
                        D->name(value);
                    else if (key == "author")
                        D->author(value);
                    else if (key == "copyright")
                        D->copyright(value);
                    else if (key == "license")
                        D->license(value);
                    else if (key == "version")
                        D->version(value);
                    else
                        D->declare(key, value);
                }
            }

            D->className(gGlobal->gClassName);
            D->inputs(container->inputs());
            D->outputs(container->outputs());

            D->print(0, xout);
#ifdef OCPP_BUILD
        } else if (old_comp) {
            Description* D = old_comp->getDescription();
            faustassert(D);
            ofstream xout(subst("$0.xml", gGlobal->makeDrawPath()).c_str());

            if (gGlobal->gMetaDataSet.count(tree("name")) > 0)
                D->name(tree2str(*(gGlobal->gMetaDataSet[tree("name")].begin())));
            if (gGlobal->gMetaDataSet.count(tree("author")) > 0)
                D->author(tree2str(*(gGlobal->gMetaDataSet[tree("author")].begin())));
            if (gGlobal->gMetaDataSet.count(tree("copyright")) > 0)
                D->copyright(tree2str(*(gGlobal->gMetaDataSet[tree("copyright")].begin())));
            if (gGlobal->gMetaDataSet.count(tree("license")) > 0)
                D->license(tree2str(*(gGlobal->gMetaDataSet[tree("license")].begin())));
            if (gGlobal->gMetaDataSet.count(tree("version")) > 0)
                D->version(tree2str(*(gGlobal->gMetaDataSet[tree("version")].begin())));

            D->className(gGlobal->gClassName);
            D->inputs(old_comp->getClass()->inputs());
            D->outputs(old_comp->getClass()->outputs());

            D->print(0, xout);
#endif
        } else {
            faustassert(false);
        }
    }

    /****************************************************************
     2 - generate documentation from Faust comments (if required)
    *****************************************************************/

    if (gGlobal->gPrintDocSwitch) {
        if (gGlobal->gLatexDocSwitch) {
            printDoc(subst("$0-mdoc", gGlobal->makeDrawPathNoExt()).c_str(), "tex", FAUSTVERSION);
        }
    }

    /****************************************************************
     3 - generate the task graph file in dot format
    *****************************************************************/

    if (gGlobal->gGraphSwitch) {
        if (new_comp) {
            ofstream dotfile(subst("$0.dot", gGlobal->makeDrawPath()).c_str());
            container->printGraphDotFormat(dotfile);
#ifdef OCPP_BUILD
        } else if (old_comp) {
            ofstream dotfile(subst("$0.dot", gGlobal->makeDrawPath()).c_str());
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
    for (vector<string>::iterator it = pathnames.begin(); it != pathnames.end(); it++) {
        out << "declare "
            << "library_path " << '"' << *it << "\";" << endl;
    }

    printDeclareHeader(out);
    out << "process = " << boxpp(gGlobal->gProcessTree) << ';' << endl;
    return out.str();
}

static void compileFaustFactoryAux(int argc, const char* argv[], const char* name, const char* dsp_content,
                                   bool generate)
{
    gGlobal->gPrintFileListSwitch = false;

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
        injcode = new ifstream();
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
        ofstream* out = new ofstream(outpath.c_str());

        // Encode compilation options as a 'declare' : has to be located first in the string
        *out << COMPILATION_OPTIONS << reorganizeCompilationOptions(argc, argv) << ';' << endl;

        // Encode all libraries paths as 'declare'
        vector<string> pathnames = gGlobal->gReader.listSrcFiles();
        for (vector<string>::iterator it = pathnames.begin(); it != pathnames.end(); it++) {
            *out << "declare "
                 << "library_path " << '"' << *it << "\";" << endl;
        }

        printDeclareHeader(*out);

        *out << "process = " << boxpp(process) << ';' << endl;
        delete out;
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

// Backend API

dsp_factory_base* compileFaustFactory(int argc, const char* argv[], const char* name, const char* dsp_content,
                                      string& error_msg, bool generate)
{
    gGlobal                   = NULL;
    dsp_factory_base* factory = NULL;

    try {
        global::allocate();
        compileFaustFactoryAux(argc, argv, name, dsp_content, generate);
        error_msg = gGlobal->gErrorMsg;
        factory   = gGlobal->gDSPFactory;
    } catch (faustexception& e) {
        error_msg = e.Message();
    }

    global::destroy();
    return factory;
}

string expandDSP(int argc, const char* argv[], const char* name, const char* dsp_content, string& sha_key,
                 string& error_msg)
{
    gGlobal    = NULL;
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
