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
 
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <openssl/sha.h>

#include "global.hh"
#include "compatibility.hh"
#include "signals.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"
#include "sigprint.hh"
#include "simplify.hh"
#include "privatise.hh"
#include "recursivness.hh"
#include "propagate.hh"
#include "errormsg.hh"
#include "ppbox.hh"
#include "enrobage.hh"
#include "eval.hh"
#include "description.hh"
#include "floats.hh"
#include "doc.hh"
#include "sourcereader.hh"
#include "instructions_compiler.hh"
#include "dag_instructions_compiler.hh"
#include "c_code_container.hh"
#include "cpp_code_container.hh"
#include "cpp_gpu_code_container.hh"
#include "java_code_container.hh"
#include "js_code_container.hh"
#include "asmjs_code_container.hh"
#include "wasm_code_container.hh"
#include "clang_code_container.hh"
#if LLVM_BUILD
#include "llvm_code_container.hh"
#endif
#include "fir_code_container.hh"
#include "schema.h"
#include "drawschema.hh"
#include "timing.hh"
#include "ppsig.hh"
#include "garbageable.hh"
#include "exception.hh"
#include "libfaust.h"
#include "Text.hh"

using namespace std;

// Timing can be used outside of the scope of 'gGlobal'
extern bool gTimingSwitch;

static ifstream* injcode = 0;
static ifstream* enrobage = 0;
       
typedef void* (*compile_fun)(void* arg);

#ifdef _WIN32 

static void call_fun(compile_fun fun)
{
    fun(NULL);
}

#else

static void call_fun(compile_fun fun)
{
    if (gGlobal->gOutputLang == "ajs") {
        // No thread support in asm.js
        fun(NULL);
    } else {
        pthread_t thread;
        pthread_attr_t attr; 
        pthread_attr_init(&attr);
        pthread_attr_setstacksize(&attr, 524288 * 128);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
        pthread_create(&thread, &attr, fun, NULL);
        pthread_join(thread, NULL);
    }
}

#endif

EXPORT Module* load_module(const string& module_name, llvm::LLVMContext* context)
{
    // Try as a complete path
    if (Module* module = load_single_module(module_name, context)) {
        return module;
    } else {
    // Otherwise use import directories
        list<string>::iterator it;
        for (it = gGlobal->gImportDirList.begin(); it != gGlobal->gImportDirList.end(); it++) {
            string file_name = *it + '/' + module_name;
            if (Module* module = load_single_module(file_name, context)) {
                return module;
            }
        }
        return 0;
    }
}

#if LLVM_BUILD

static Module* link_all_modules(llvm::LLVMContext* context, Module* dst, char* error)
{
    list<string>::iterator it;
    
    for (it = gGlobal->gLibraryList.begin(); it != gGlobal->gLibraryList.end(); it++) {
        string module_name = *it;
        
        Module* src = load_module(module_name, context);
        if (!src) {
            sprintf(error, "cannot load module : %s", module_name.c_str());
            return 0;
        }
        
        if (!link_modules(dst, src, error)) {
            return 0;
        }
    }
        
    return dst;
}

#endif

//L ook for 'key' in 'options' and modify the parameter 'position' if found
static bool parseKey(vector<string> options, const string& key, int& position)
{
    for (size_t i = 0; i < options.size(); i++) {
        if (key == options[i]) {
            position = i;
            return true;
        }
    }
    
    return false;
}

// Add 'key' if existing in 'options', otherwise add 'defaultKey' (if different from "")
// #return true if 'key' was added
static bool addKeyIfExisting(vector<string>& options, vector<string>& newoptions, const string& key, const string& defaultKey, int& position)
{
    if (parseKey(options, key, position)) {        
        newoptions.push_back(options[position]);
        options.erase(options.begin()+position);
        position--;
        return true;
    } else if (defaultKey != "") {
        newoptions.push_back(defaultKey);
    }
    
    return false;
}

// Add 'key' & it's associated value if existing in 'options', otherwise add 'defaultValue' (if different from "")
static void addKeyValueIfExisting(vector<string>& options, vector<string>& newoptions, const string& key, const string& defaultValue)
{
    int position = 0;
    
    if (addKeyIfExisting(options, newoptions, key, "", position)) {
        if (position+1 < int(options.size()) && options[position+1][0] != '-') {
            newoptions.push_back(options[position+1]);
            options.erase(options.begin()+position+1);
            position--;
        } else {
            newoptions.push_back(defaultValue);
        }
    }
}

/* Reorganizes the compilation options
 * Following the tree of compilation (Faust_Compilation_Options.pdf in distribution)
 */
static vector<string> reorganizeCompilationOptionsAux(vector<string>& options)
{
    bool vectorize = false;
    int position = 0;
    
    vector<string> newoptions;
    
    //------STEP 1 - Single or Double ?
    addKeyIfExisting(options, newoptions, "-double", "-single", position);
    
    //------STEP 2 - Options Leading to -vec inclusion
    if (addKeyIfExisting(options, newoptions, "-sch", "", position)) {
        vectorize = true;
    }
    
    if (addKeyIfExisting(options, newoptions, "-omp", "", position)){
        vectorize = true;
        addKeyIfExisting(options, newoptions, "-pl", "", position);
    }
    
    if (vectorize) {
        newoptions.push_back("-vec");
    }
    
    //------STEP3 - Add options depending on -vec/-scal option
    if (vectorize || addKeyIfExisting(options, newoptions, "-vec", "", position)) {
        addKeyIfExisting(options, newoptions, "-dfs", "", position);
        addKeyIfExisting(options, newoptions, "-vls", "", position);
        addKeyIfExisting(options, newoptions, "-fun", "", position);
        addKeyIfExisting(options, newoptions, "-g", "", position);
        addKeyValueIfExisting(options, newoptions, "-vs", "32");
        addKeyValueIfExisting(options, newoptions, "-lv", "0");
    } else {
        addKeyIfExisting(options, newoptions, "-scal", "-scal", position);
        addKeyIfExisting(options, newoptions, "-inpl", "", position);
    }
    
    addKeyValueIfExisting(options, newoptions, "-mcd", "16");
    addKeyValueIfExisting(options, newoptions, "-cn", "");
    
    //------STEP4 - Add other types of Faust options
    /*
    addKeyIfExisting(options, newoptions, "-tg", "", position);
    addKeyIfExisting(options, newoptions, "-sg", "", position);
    addKeyIfExisting(options, newoptions, "-ps", "", position);    
    addKeyIfExisting(options, newoptions, "-svg", "", position);    
    
    if (addKeyIfExisting(options, newoptions, "-mdoc", "", position)) {
        addKeyValueIfExisting(options, newoptions, "-mdlang", "");
        addKeyValueIfExisting(options, newoptions, "-stripdoc", "");
    }
    
    addKeyIfExisting(options, newoptions, "-sd", "", position);
    addKeyValueIfExisting(options, newoptions, "-f", "25");
    addKeyValueIfExisting(options, newoptions, "-mns", "40"); 
    addKeyIfExisting(options, newoptions, "-sn", "", position);
    addKeyIfExisting(options, newoptions, "-xml", "", position);
    addKeyIfExisting(options, newoptions, "-blur", "", position);    
    addKeyIfExisting(options, newoptions, "-lb", "", position);
    addKeyIfExisting(options, newoptions, "-mb", "", position);
    addKeyIfExisting(options, newoptions, "-rb", "", position);    
    addKeyIfExisting(options, newoptions, "-lt", "", position);    
    addKeyValueIfExisting(options, newoptions, "-a", "");
    addKeyIfExisting(options, newoptions, "-i", "", position);
    addKeyValueIfExisting(options, newoptions, "-cn", "");    
    addKeyValueIfExisting(options, newoptions, "-t", "120");
    addKeyIfExisting(options, newoptions, "-time", "", position);
    addKeyValueIfExisting(options, newoptions, "-o", "");
    addKeyValueIfExisting(options, newoptions, "-lang", "cpp");
    addKeyIfExisting(options, newoptions, "-flist", "", position);
    addKeyValueIfExisting(options, newoptions, "-l", "");
    addKeyValueIfExisting(options, newoptions, "-O", "");
    
    //-------Add Other Options that are possibily passed to the compiler (-I, -blabla, ...)
    while (options.size() != 0) {
        if (options[0] != "faust") newoptions.push_back(options[0]); // "faust" first argument
        options.erase(options.begin());
    }
    */
    
    return newoptions;
}

EXPORT string reorganize_compilation_options(int argc, const char* argv[])
{
    vector<string> res1;
    for (int i = 0; i < argc; i++) {
        res1.push_back(argv[i]);
    }
    
    vector<string> res2 = reorganizeCompilationOptionsAux(res1);
    
    string res3;
    string sep;
    for (size_t i = 0; i < res2.size(); i++) {
        res3 = res3 + sep + res2[i];
        sep = " ";
    }
    
    return "\"" + res3 + "\"";
}

EXPORT std::string extract_compilation_options(const std::string& dsp_content)
{
    size_t pos1 = dsp_content.find(COMPILATION_OPTIONS_KEY);
    
    if (pos1 != string::npos) {
        size_t pos2 = dsp_content.find_first_of('"', pos1 + 1);
        size_t pos3 = dsp_content.find_first_of('"', pos2 + 1);
        if (pos2 != string::npos && pos3 != string::npos) {
            return dsp_content.substr(pos2, (pos3 - pos2) + 1);
         }
    }
    
    return "";
}

EXPORT string generateSHA1(const string& dsp_content)
{
    // compute SHA1 key
    unsigned char obuf[20];
    SHA1((const unsigned char*)dsp_content.c_str(), dsp_content.size(), obuf);
    
	// convert SHA1 key into hexadecimal string
    string sha1key;
    for (int i = 0; i < 20; i++) {
    	const char* H = "0123456789ABCDEF";
    	char c1 = H[(obuf[i] >> 4)];
    	char c2 = H[(obuf[i] & 15)];
        sha1key += c1;
        sha1key += c2;
    }
    
    return sha1key;
}

static Tree evaluateBlockDiagram(Tree expandedDefList, int& numInputs, int& numOutputs);

static void* thread_evaluateBlockDiagram(void* arg) 
{   
    try {
        gGlobal->gProcessTree = evaluateBlockDiagram(gGlobal->gExpandedDefList, gGlobal->gNumInputs, gGlobal->gNumOutputs);
    } catch (faustexception& e) {
        gGlobal->gErrorMessage = e.Message();
    }
    return 0;
}

static void* thread_boxPropagateSig(void* arg)
{
    try {
        gGlobal->gLsignalsTree = boxPropagateSig(gGlobal->nil, gGlobal->gProcessTree, makeSigInputList(gGlobal->gNumInputs));
    } catch (faustexception& e) {
        gGlobal->gErrorMessage = e.Message();
    }
    return 0;
}

/****************************************************************
 						Global context variable
*****************************************************************/

global* gGlobal = NULL;

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

static bool process_cmdline(int argc, const char* argv[])
{
	int	i = 1; 
    int err = 0;
    stringstream parse_error;
    
    /*
    for (int i = 0; i < argc; i++) {
        printf("process_cmdline i = %d cmd = %s\n", i, argv[i]);
    }
    */

	while (i < argc) {

		if (isCmd(argv[i], "-h", "--help")) {
			gGlobal->gHelpSwitch = true;
			i += 1;
            
        } else if (isCmd(argv[i], "-lang", "--language") && (i+1 < argc)) {
			gGlobal->gOutputLang = argv[i+1];
			i += 2;
            
        } else if (isCmd(argv[i], "-v", "--version")) {
			gGlobal->gVersionSwitch = true;
			i += 1;

		} else if (isCmd(argv[i], "-d", "--details")) {
			gGlobal->gDetailsSwitch = true;
			i += 1;

		} else if (isCmd(argv[i], "-a", "--architecture") && (i+1 < argc)) {
			gGlobal->gArchFile = argv[i+1];
			i += 2;
            
         } else if (isCmd(argv[i], "-inj", "--inject")) {
            gGlobal->gInjectFlag = true;
            gGlobal->gInjectFile = argv[i+1];
            i += 2;

		} else if (isCmd(argv[i], "-o") && (i+1 < argc)) {
			gGlobal->gOutputFile = argv[i+1];
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

        } else if (isCmd(argv[i], "-blur", "--shadow-blur")) {
            gGlobal->gShadowBlur = true;
            i += 1;
            
         } else if (isCmd(argv[i], "-sc", "--scaled-svg")) {
            gGlobal->gScaledSVG = true;
            i += 1;

		} else if (isCmd(argv[i], "-svg", "--svg")) {
			gGlobal->gDrawSVGSwitch = true;
			i += 1;

		} else if (isCmd(argv[i], "-f", "--fold") && (i+1 < argc)) {
			gGlobal->gFoldThreshold = atoi(argv[i+1]);
			i += 2;

		} else if (isCmd(argv[i], "-mns", "--max-name-size") && (i+1 < argc)) {
			gGlobal->gMaxNameSize = atoi(argv[i+1]);
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

		} else if (isCmd(argv[i], "-mcd", "--max-copy-delay") && (i+1 < argc)) {
			gGlobal->gMaxCopyDelay = atoi(argv[i+1]);
			i += 2;

		} else if (isCmd(argv[i], "-sd", "--simplify-diagrams")) {
			gGlobal->gSimplifyDiagrams = true;
			i += 1;

        } else if (isCmd(argv[i], "-vec", "--vectorize")) {
            gGlobal->gVectorSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-vls", "--vec-loop-size") && (i+1 < argc)) {
            gGlobal->gVecLoopSize = atoi(argv[i+1]);
            i += 2;

        } else if (isCmd(argv[i], "-scal", "--scalar")) {
            gGlobal->gVectorSwitch = false;
            i += 1;

        } else if (isCmd(argv[i], "-dfs", "--deepFirstScheduling")) {
            gGlobal->gDeepFirstSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-vs", "--vec-size") && (i+1 < argc)) {
            gGlobal->gVecSize = atoi(argv[i+1]);
            i += 2;

        } else if (isCmd(argv[i], "-lv", "--loop-variant") && (i+1 < argc)) {
            gGlobal->gVectorLoopVariant = atoi(argv[i+1]);
            i += 2;

        } else if (isCmd(argv[i], "-omp", "--openMP")) {
            gGlobal->gOpenMPSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-pl", "--par-loop")) {
            gGlobal->gOpenMPLoop = true;
            i += 1;

        } else if (isCmd(argv[i], "-sch", "--scheduler")) {
			gGlobal->gSchedulerSwitch = true;
            gGlobal->gLibraryList.push_back("scheduler.ll");
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

        } else if (isCmd(argv[i], "-t", "--timeout") && (i+1 < argc)) {
            gGlobal->gTimeout = atoi(argv[i+1]);
            i += 2;
            
        } else if (isCmd(argv[i], "-time", "--compilation-time")) {
            gTimingSwitch = true;
            i += 1;

        // double float options
        } else if (isCmd(argv[i], "-single", "--single-precision-floats")) {
            gGlobal->gFloatSize = 1;
            i += 1;

        } else if (isCmd(argv[i], "-double", "--double-precision-floats")) {
            gGlobal->gFloatSize = 2;
            i += 1;

        } else if (isCmd(argv[i], "-quad", "--quad-precision-floats")) {
            gGlobal->gFloatSize = 3;
            i += 1;

        } else if (isCmd(argv[i], "-mdoc", "--mathdoc")) {
            gGlobal->gPrintDocSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-mdlang", "--mathdoc-lang") && (i+1 < argc)) {
            gGlobal->gDocLang = argv[i+1];
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

		} else if (isCmd(argv[i], "-cn", "--class-name") && (i+1 < argc)) {
			gGlobal->gClassName = argv[i+1];
			i += 2;

        } else if (isCmd(argv[i], "-i", "--inline-architecture-files")) {
            gGlobal->gInlineArchSwitch = true;
            i += 1;
        
        } else if (isCmd(argv[i], "-e", "--export-dsp")) {
            gGlobal->gExportDSP = true;
            i += 1;
         
        } else if (isCmd(argv[i], "-I", "--import-dir")) {
            char temp[PATH_MAX+1];
            if (strstr(argv[i+1], "http://") != 0) {
                gGlobal->gImportDirList.push_back(argv[i+1]);
            } else {
                char* path = realpath(argv[i+1], temp);
                if (path) {
                    gGlobal->gImportDirList.push_back(path);
                }
            }
            i += 2;
            
        } else if (isCmd(argv[i], "-l", "--library") && (i+1 < argc)) {
            gGlobal->gLibraryList.push_back(argv[i+1]);
            i += 2;
           
        } else if (isCmd(argv[i], "-O", "--output-dir")) {
            char temp[PATH_MAX+1];
            char* path = realpath(argv[i+1], temp);
            if (path) {
                gGlobal->gOutputDir = path;
            }
            i += 2;
            
        } else if (isCmd(argv[i], "-inpl", "--in-place")) {
             gGlobal->gInPlace = true;
             i += 1;
             
        } else if (isCmd(argv[i], "-lm", "--local-machine") || isCmd(argv[i], "-rm", "--remote-machine")) {
             // Ignore arg
             i += 2;

        } else if (argv[i][0] != '-') {
            const char* url = argv[i];
            if (check_url(url)) {
				gGlobal->gInputFiles.push_back(url);
			}
			i++;

		} else {
            if (err == 0) {
                parse_error << "unrecognized option(s) : \"" << argv[i] <<"\"";
            } else {
                parse_error << ",\"" << argv[i] <<"\"";
            }
            i++;
			err++;
		}
	}

    // Adjust related options
    if (gGlobal->gOpenMPSwitch || gGlobal->gSchedulerSwitch) gGlobal->gVectorSwitch = true;
    
    // Check options
    if (gGlobal->gInPlace && gGlobal->gVectorSwitch) {
        throw faustexception("ERROR : 'in-place' option can only be used in scalar mode\n");
    }  
    
    if (gGlobal->gVectorLoopVariant < 0 || gGlobal->gVectorLoopVariant > 1) {
        stringstream error;
        error << "ERROR : invalid loop variant [-lv = " << gGlobal->gVectorLoopVariant << "] should be 0 or 1" << endl;
        throw faustexception(error.str());
    }
    
    if (gGlobal->gVecSize < 4) {
        stringstream error;
        error << "ERROR : invalid vector size [-vs = "<< gGlobal->gVecSize << "] should be at least 4" << endl;
        throw faustexception(error.str());
    }

    if (gGlobal->gVecLoopSize > gGlobal->gVecSize) {
        stringstream error;
        error << "ERROR : invalid vector loop size [-vls = "<< gGlobal->gVecLoopSize << "] has to be <= [-vs = " << gGlobal->gVecSize << "]" << endl;
        throw faustexception(error.str());
    }
    
    if (err != 0) {
        stringstream error;
        error << "WARNING : " << parse_error.str() << endl;
        gGlobal->gErrorMsg = error.str();
    }

	return (err == 0);
}

/****************************************************************
 					 Help and Version information
*****************************************************************/

static void printversion()
{
	cout << "FAUST : DSP to C, C++, JAVA, JavaScript/ASMJavaScript, WebAssembly, LLVM IR version " << FAUSTVERSION << "\n";
	cout << "Copyright (C) 2002-2015, GRAME - Centre National de Creation Musicale. All rights reserved. \n\n";
}

static void printhelp()
{
	printversion();
	cout << "usage : faust [options] file1 [file2 ...]\n";
	cout << "\twhere options represent zero or more compiler options \n\tand fileN represents a Faust source file (.dsp extension).\n";

	cout << "\noptions :\n";
	cout << "---------\n";

	cout << "-h \t\tprint this --help message\n";
	cout << "-v \t\tprint compiler --version information\n";
	cout << "-d \t\tprint compilation --details\n";
    cout << "-tg \t\tprint the internal --task-graph in dot format file\n";
    cout << "-sg \t\tprint the internal --signal-graph in dot format file\n";
    cout << "-ps \t\tprint block-diagram --postscript file\n";
    cout << "-svg \t\tprint block-diagram --svg file\n";
    cout << "-mdoc \t\tprint --mathdoc of a Faust program in LaTeX format in a -mdoc directory\n";
    cout << "-mdlang <l>\tload --mathdoc-lang <l> if translation file exists (<l> = en, fr, ...)\n";
    cout << "-stripdoc \tapply --strip-mdoc-tags when printing Faust -mdoc listings\n";
    cout << "-sd \t\ttry to further --simplify-diagrams before drawing them\n";
	cout << "-f <n> \t\t--fold <n> threshold during block-diagram generation (default 25 elements) \n";
	cout << "-mns <n> \t--max-name-size <n> threshold during block-diagram generation (default 40 char)\n";
	cout << "-sn \t\tuse --simple-names (without arguments) during block-diagram generation\n";
	cout << "-xml \t\tgenerate an XML description file\n";
    cout << "-json \t\tgenerate a JSON description file\n";
    cout << "-blur \t\tadd a --shadow-blur to SVG boxes\n";
	cout << "-lb \t\tgenerate --left-balanced expressions\n";
	cout << "-mb \t\tgenerate --mid-balanced expressions (default)\n";
	cout << "-rb \t\tgenerate --right-balanced expressions\n";
	cout << "-lt \t\tgenerate --less-temporaries in compiling delays\n";
	cout << "-mcd <n> \t--max-copy-delay <n> threshold between copy and ring buffer implementation (default 16 samples)\n";
	cout << "-a <file> \twrapper architecture file\n";
	cout << "-i \t\t--inline-architecture-files \n";
	cout << "-cn <name> \t--class-name <name> specify the name of the dsp class to be used instead of mydsp \n";
	cout << "-t <sec> \t--timeout <sec>, abort compilation after <sec> seconds (default 120)\n";
    cout << "-time \t\t--compilation-time, flag to display compilation phases timing information\n";
    cout << "-o <file> \tC, C++, JAVA, JavaScript/ASMJavaScript or LLVM IR output file\n";
    cout << "-scal   \t--scalar generate non-vectorized code\n";
    cout << "-vec    \t--vectorize generate easier to vectorize code\n";
    cout << "-vls <n>  \t--vec-loop-size size of the vector DSP loop for auto-vectorization (experimental) \n";
    cout << "-vs <n> \t--vec-size <n> size of the vector (default 32 samples)\n";
    cout << "-lv <n> \t--loop-variant [0:fastest (default), 1:simple] \n";
    cout << "-omp    \t--openMP generate OpenMP pragmas, activates --vectorize option\n";
    cout << "-pl     \t--par-loop generate parallel loops in --openMP mode\n";
    cout << "-sch    \t--scheduler generate tasks and use a Work Stealing scheduler, activates --vectorize option\n";
    cout << "-ocl    \t--openCL generate tasks with OpenCL (experimental) \n";
    cout << "-cuda   \t--cuda generate tasks with CUDA (experimental) \n";
    cout << "-dfs    \t--deepFirstScheduling schedule vector loops in deep first order\n";
    cout << "-g    \t\t--groupTasks group single-threaded sequential tasks together when -omp or -sch is used\n";
    cout << "-fun  \t\t--funTasks separate tasks code as separated functions (in -vec, -sch, or -omp mode)\n";
    cout << "-lang <lang> \t--language generate various output formats : c, cpp, java, js, ajs, llvm, cllvm, fir (default cpp)\n";
    cout << "-uim    \t--user-interface-macros add user interface macro definitions in the output code\n";
    cout << "-single \tuse --single-precision-floats for internal computations (default)\n";
    cout << "-double \tuse --double-precision-floats for internal computations\n";
    cout << "-quad \t\tuse --quad-precision-floats for internal computations\n";
    cout << "-flist \t\tuse --file-list used to eval process\n";
    cout << "-norm \t\t--normalized-form prints signals in normalized form and exits\n";
    cout << "-I <dir> \t--import-dir <dir> add the directory <dir> to the import search path\n";
    cout << "-l <file> \t--library <file> link with the LLVM module <file>\n";
    cout << "-O <dir> \t--output-dir <dir> specify the relative directory of the generated output code, and the output directory of additional generated files (SVG, XML...)\n";
    cout << "-e       \t--export-dsp export expanded DSP (all included libraries) \n";
    cout << "-inpl    \t--in-place generates code working when input and output buffers are the same (in scalar mode only) \n";
    cout << "-inj <f> \t--inject source file <f> into architecture file instead of compile a dsp file\n";
	cout << "\nexample :\n";
	cout << "---------\n";

	cout << "faust -a jack-gtk.cpp -o myfx.cpp myfx.dsp\n";
}

static void printDeclareHeader(ostream& dst)
{
    for (MetaDataSet::iterator i = gGlobal->gMetaDataSet.begin(); i != gGlobal->gMetaDataSet.end(); i++) {
        if (i->first != tree("author")) {
            dst << "declare ";
            stringstream key; key << *(i->first);
            dst << replaceChar(replaceChar(key.str(), '.', '_'), '/', '_');
            dst << " " << **(i->second.begin());
        } else {
            for (set<Tree>::iterator j = i->second.begin(); j != i->second.end(); ++j) {
                if (j == i->second.begin()) {
                    dst << "declare " << *(i->first) << " " << **j;
                } else {
                    dst << "declare contributor " << **j;
                }
            }
        }
        dst << ";" << endl;
    }
}

void printHeader(ostream& dst)
{
    // defines the metadata we want to print as comments at the begin of in the file
    set<Tree> selectedKeys;
    selectedKeys.insert(tree("name"));
    selectedKeys.insert(tree("author"));
    selectedKeys.insert(tree("copyright"));
    selectedKeys.insert(tree("license"));
    selectedKeys.insert(tree("version"));

    dst << "/* ------------------------------------------------------------" << endl;
    for (MetaDataSet::iterator i = gGlobal->gMetaDataSet.begin(); i != gGlobal->gMetaDataSet.end(); i++) {
        if (selectedKeys.count(i->first)) {
            dst << *(i->first);
            const char* sep = ": ";
            for (set<Tree>::iterator j = i->second.begin(); j != i->second.end(); ++j) {
                dst << sep << **j;
                sep = ", ";
            }
            dst << endl;
        }
    }

    dst << "Code generated with Faust " << FAUSTVERSION << " (http://faust.grame.fr)" << endl;
    dst << "------------------------------------------------------------ */" << endl;
}

/****************************************************************
 					 			MAIN
*****************************************************************/

/**
 * transform a filename "faust/example/noise.dsp" into
 * the corresponding fx name "noise"
 */
static string fxname(const string& filename)
{
	// determine position right after the last '/' or 0
	unsigned int p1 = 0;
    for (unsigned int i = 0; i < filename.size(); i++) {
        if (filename[i] == '/')  { p1 = i+1; }
    }

	// determine position of the last '.'
	unsigned int p2 = filename.size();
    for (unsigned int i = p1; i < filename.size(); i++) {
        if (filename[i] == '.')  { p2 = i; }
    }

    return filename.substr(p1, p2-p1);
}

string makeDrawPath()
{
    if (gGlobal->gOutputDir != "") {
        return gGlobal->gOutputDir + "/" + gGlobal->gMasterName + ".dsp";
    } else {
        return gGlobal->gMasterDocument;
    }
}

static string makeDrawPathNoExt()
{
    if (gGlobal->gOutputDir != "") {
        return gGlobal->gOutputDir + "/" + gGlobal->gMasterName;
    } else if (gGlobal->gMasterDocument.length() >= 4 && gGlobal->gMasterDocument.substr(gGlobal->gMasterDocument.length() - 4) == ".dsp") {
        return gGlobal->gMasterDocument.substr(0, gGlobal->gMasterDocument.length() - 4);
    } else {
        return gGlobal->gMasterDocument;
    }
}

static void initFaustDirectories()
{
    char s[1024];
    getFaustPathname(s, 1024);

    gGlobal->gFaustDirectory = filedirname(s);
    gGlobal->gFaustSuperDirectory = filedirname(gGlobal->gFaustDirectory);
    gGlobal->gFaustSuperSuperDirectory = filedirname(gGlobal->gFaustSuperDirectory);
    if (gGlobal->gInputFiles.empty()) {
        gGlobal->gMasterDocument = "Unknown";
        gGlobal->gMasterDirectory = ".";
		gGlobal->gMasterName = "faustfx";
		gGlobal->gDocName = "faustdoc";
    } else {
        gGlobal->gMasterDocument = *gGlobal->gInputFiles.begin();
        gGlobal->gMasterDirectory = filedirname(gGlobal->gMasterDocument);
		gGlobal->gMasterName = fxname(gGlobal->gMasterDocument);
		gGlobal->gDocName = fxname(gGlobal->gMasterDocument);
    }
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
   
    gGlobal->gExpandedDefList = gGlobal->gReader.expandlist(gGlobal->gResult2);

    endTiming("parser");
}

static Tree evaluateBlockDiagram(Tree expandedDefList, int& numInputs, int& numOutputs)
{
    startTiming("evaluation");

    Tree process = evalprocess(expandedDefList);
    if (gGlobal->gErrorCount > 0) {
        stringstream error;
        error << "ERROR : total of " << gGlobal->gErrorCount << " errors during the compilation of " << gGlobal->gMasterDocument << ";\n";
        throw faustexception(error.str());
    }

    if (gGlobal->gDetailsSwitch) { cout << "process = " << boxpp(process) << ";\n"; }

    if (gGlobal->gDrawPSSwitch || gGlobal->gDrawSVGSwitch) {
        string projname = makeDrawPathNoExt();
        if (gGlobal->gDrawPSSwitch)  { drawSchema(process, subst("$0-ps",  projname).c_str(), "ps"); }
        if (gGlobal->gDrawSVGSwitch) { drawSchema(process, subst("$0-svg", projname).c_str(), "svg"); }
    }

    if (!getBoxType(process, &numInputs, &numOutputs)) {
        stringstream error;
        error << "ERROR during the evaluation of process : " << boxpp(process) << endl;
        throw faustexception(error.str());
    }

    if (gGlobal->gDetailsSwitch) {
        cout <<"process has " << numInputs <<" inputs, and " << numOutputs <<" outputs" << endl;
    }

    endTiming("evaluation");

    if (gGlobal->gPrintFileListSwitch) {
        cout << "---------------------------\n";
        cout << "List of file dependencies :\n";
        cout << "---------------------------\n";
        // print the pathnames of the files used to evaluate process
        vector<string> pathnames = gGlobal->gReader.listSrcFiles();
        for (unsigned int i = 0; i< pathnames.size(); i++) cout << pathnames[i] << std::endl;
        cout << "---------------------------\n";
        cout << endl;
    }

    return process;
}

static pair<InstructionsCompiler*, CodeContainer*> generateCode(Tree signals, int numInputs, int numOutputs, bool generate)
{
    // By default use "cpp" output
    if (gGlobal->gOutputLang == "") {
        gGlobal->gOutputLang = "cpp";
    }

    InstructionsCompiler* comp = NULL;
    CodeContainer* container = NULL;

    startTiming("generateCode");
    
#if LLVM_BUILD
    if (gGlobal->gOutputLang == "cllvm") {
    
    #if CLANG_BUILD
        container = ClangCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs);

        if (generate) {
        
            ClangCodeContainer* clang_container = dynamic_cast<ClangCodeContainer*>(container);
            gGlobal->gLLVMResult = clang_container->produceModule(signals, gGlobal->gOutputFile);
            if (!gGlobal->gLLVMResult) {
                throw faustexception("Cannot compile C generated code to LLVM IR\n");
            }
            gGlobal->gLLVMResult->fPathnameList = gGlobal->gReader.listSrcFiles();
           
            // Possibly link with additional LLVM modules
            char error[256];
            if (!link_all_modules(gGlobal->gLLVMResult->fContext, gGlobal->gLLVMResult->fModule, error)) {
                stringstream llvm_error;
                llvm_error << "ERROR : " << error << endl;
                throw faustexception(llvm_error.str());
            }
            
            if (gGlobal->gLLVMOut && gGlobal->gOutputFile == "") {
                outs() << *gGlobal->gLLVMResult->fModule;
            }
            
        } else {
            // To trigger 'sig.dot' generation
            if (gGlobal->gVectorSwitch) {
                comp = new DAGInstructionsCompiler(container);
            } else {
                comp = new InstructionsCompiler(container);
            }
            comp->prepare(signals);
        }
    #endif

    } else if (gGlobal->gOutputLang == "llvm") {
   
        container = LLVMCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs);

        if (gGlobal->gVectorSwitch) {
            comp = new DAGInstructionsCompiler(container);
        } else {
            comp = new InstructionsCompiler(container);
        }

        if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) comp->setDescription(new Description());
         
        if (generate) {
            comp->compileMultiSignal(signals);
            LLVMCodeContainer* llvm_container = dynamic_cast<LLVMCodeContainer*>(container);
            gGlobal->gLLVMResult = llvm_container->produceModule(gGlobal->gOutputFile);
            gGlobal->gLLVMResult->fPathnameList = gGlobal->gReader.listSrcFiles();
             
            // Possibly link with additional LLVM modules
            char error[256];
            if (!link_all_modules(gGlobal->gLLVMResult->fContext, gGlobal->gLLVMResult->fModule, error)) {
                stringstream llvm_error;
                llvm_error << "ERROR : " << error << endl;
                throw faustexception(llvm_error.str());
            }
            
            if (gGlobal->gLLVMOut && gGlobal->gOutputFile == "") {
                outs() << *gGlobal->gLLVMResult->fModule;
            }
            
        } else {
            // To trigger 'sig.dot' generation
            comp->prepare(signals);
        }
    
#else
    if (gGlobal->gOutputLang == "llvm" || gGlobal->gOutputLang == "cllvm") {
        throw faustexception("ERROR : -lang llvm not supported since LLVM backend is not built\n");
#endif
 
    } else {
    
        ostream* dst;

        if (gGlobal->gOutputFile != "") {
            string outpath = (gGlobal->gOutputDir != "") ? (gGlobal->gOutputDir + "/" + gGlobal->gOutputFile) : gGlobal->gOutputFile;
            if (gGlobal->gOutputFile == "asmjs") {
                dst = new stringstream(outpath.c_str());
                gGlobal->gStringResult = dst;
            } else {
                dst = new ofstream(outpath.c_str());
            }
        } else {
            dst = &cout;
        }
        
        if (gGlobal->gOutputLang == "c") {

            container = CCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, dst);

        } else if (gGlobal->gOutputLang == "cpp") {

            container = CPPCodeContainer::createContainer(gGlobal->gClassName, "dsp", numInputs, numOutputs, dst);

        } else if (gGlobal->gOutputLang == "java") {

            container = JAVACodeContainer::createContainer(gGlobal->gClassName, "dsp", numInputs, numOutputs, dst);
            
        } else if (gGlobal->gOutputLang == "js") {

            container = JAVAScriptCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, dst);
        
        } else if (gGlobal->gOutputLang == "ajs") {

            container = ASMJAVAScriptCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, dst);

        } else if (gGlobal->gOutputLang == "wasm") {

            container = WASMCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, dst);

        } else if (gGlobal->gOutputLang == "fir") {
       
            container = FirCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, true);

            if (gGlobal->gVectorSwitch) {
                comp = new DAGInstructionsCompiler(container);
            } else {
                comp = new InstructionsCompiler(container);
            }

            comp->compileMultiSignal(signals);
            container->dump(dst);
            throw faustexception("");
        }
        if (!container) {
            stringstream error;
            error << "ERROR : cannot find compiler for " << "\"" << gGlobal->gOutputLang  << "\"" << endl;
            throw faustexception(error.str());
        }
        if (gGlobal->gVectorSwitch) {
            comp = new DAGInstructionsCompiler(container);
        } else {
            comp = new InstructionsCompiler(container, (gGlobal->gOutputLang != "ajs"));
        }

        if (gGlobal->gPrintXMLSwitch || gGlobal->gPrintDocSwitch) comp->setDescription(new Description());

        comp->compileMultiSignal(signals);

        /****************************************************************
         * generate output file
         ****************************************************************/
         
        if (gGlobal->gArchFile != "") {
        
            // Keep current directory
            char current_directory[FAUST_PATH_MAX];
            getcwd(current_directory, FAUST_PATH_MAX);
            
            if ((enrobage = open_arch_stream(gGlobal->gArchFile.c_str()))) {
            
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
                        streamCopy(*injcode, *dst);
                        streamCopyUntilEnd(*enrobage, *dst);
                    }
                    delete injcode;
                    throw faustexception("");
                }
       
                if (gGlobal->gOutputLang != "js") {
                    printHeader(*dst);
                }
                
                if ((gGlobal->gOutputLang == "c") || (gGlobal->gOutputLang == "cpp")) {
                    tab(0, *dst); *dst << "#ifndef  __" << gGlobal->gClassName << "_H__";
                    tab(0, *dst); *dst << "#define  __" << gGlobal->gClassName << "_H__" << std::endl;
                }

                streamCopyUntil(*enrobage, *dst, "<<includeIntrinsic>>");
                streamCopyUntil(*enrobage, *dst, "<<includeclass>>");

                if (gGlobal->gOpenCLSwitch || gGlobal->gCUDASwitch) {
                    istream* thread_include = open_arch_stream("thread.h");
                    if (thread_include) {
                        streamCopy(*thread_include, *dst);
                    }
                    delete(thread_include);
                }

                if ((gGlobal->gOutputLang != "java") 
                    && (gGlobal->gOutputLang != "js") 
                    && (gGlobal->gOutputLang != "ajs")
                    && (gGlobal->gOutputLang != "wasm")) {
                    printfloatdef(*dst, (gGlobal->gFloatSize == 3));
                }

                if (gGlobal->gOutputLang == "c") {
                    *dst << "#include <stdlib.h>"<< std::endl;
                }

                container->produceClass();
                streamCopyUntilEnd(*enrobage, *dst);
                if (gGlobal->gSchedulerSwitch) {
                    istream* scheduler_include = open_arch_stream("scheduler.cpp");
                    if (scheduler_include) {
                        streamCopy(*scheduler_include, *dst);
                    }
                    delete(scheduler_include);
                }

                if ((gGlobal->gOutputLang == "c") || (gGlobal->gOutputLang == "cpp")) {
                    tab(0, *dst); *dst << "#endif"<< std::endl;
                }
                
                // Restore current_directory
                chdir(current_directory);
                delete enrobage;
                 
            } else {
                stringstream error;
                error << "ERROR : can't open architecture file " << gGlobal->gArchFile << endl;
                throw faustexception(error.str());
            }
            
        } else {
            if (gGlobal->gOutputLang != "js") {
                printHeader(*dst);
            }
            if ((gGlobal->gOutputLang != "java") 
                && (gGlobal->gOutputLang != "js") 
                && (gGlobal->gOutputLang != "ajs")
                && (gGlobal->gOutputLang != "wasm")) {
                printfloatdef(*dst, (gGlobal->gFloatSize == 3));
            }
            if (gGlobal->gOutputLang == "c") {
                *dst << "#include <stdlib.h>"<< std::endl;
            }
            container->produceClass();
        }
    }
    
    endTiming("generateCode");

    return make_pair(comp, container);
}

static void generateOutputFiles(InstructionsCompiler * comp, CodeContainer * container)
{
    /****************************************************************
     1 - generate XML description (if required)
    *****************************************************************/
  
    if (gGlobal->gPrintXMLSwitch) {
        Description* D = comp->getDescription(); assert(D);
        ofstream xout(subst("$0.xml", makeDrawPath()).c_str());
      
        if (gGlobal->gMetaDataSet.count(tree("name")) > 0)          D->name(tree2str(*(gGlobal->gMetaDataSet[tree("name")].begin())));
        if (gGlobal->gMetaDataSet.count(tree("author")) > 0)        D->author(tree2str(*(gGlobal->gMetaDataSet[tree("author")].begin())));
        if (gGlobal->gMetaDataSet.count(tree("copyright")) > 0)     D->copyright(tree2str(*(gGlobal->gMetaDataSet[tree("copyright")].begin())));
        if (gGlobal->gMetaDataSet.count(tree("license")) > 0)       D->license(tree2str(*(gGlobal->gMetaDataSet[tree("license")].begin())));
        if (gGlobal->gMetaDataSet.count(tree("version")) > 0)       D->version(tree2str(*(gGlobal->gMetaDataSet[tree("version")].begin())));

        D->className(gGlobal->gClassName);
		D->inputs(container->inputs());
		D->outputs(container->outputs());

        D->print(0, xout);
    }

    /****************************************************************
     2 - generate documentation from Faust comments (if required)
    *****************************************************************/

    if (gGlobal->gPrintDocSwitch) {
        if (gGlobal->gLatexDocSwitch) {
            printDoc(subst("$0-mdoc", makeDrawPathNoExt()).c_str(), "tex", FAUSTVERSION);
        }
    }

    /****************************************************************
     3 - generate the task graph file in dot format
    *****************************************************************/

    if (gGlobal->gGraphSwitch) {
        ofstream dotfile(subst("$0.dot", makeDrawPath()).c_str());
        container->printGraphDotFormat(dotfile);
    }
}

static string expand_dsp_internal(int argc, const char* argv[], const char* name, const char* dsp_content)
{
    /****************************************************************
     1 - process command line
    *****************************************************************/
    process_cmdline(argc, argv);
   
    /****************************************************************
     2 - parse source files
    *****************************************************************/
    if (dsp_content) {
        gGlobal->gInputString = dsp_content;
        gGlobal->gInputFiles.push_back(name);
    }
    parseSourceFiles();
    
    initFaustDirectories();

    /****************************************************************
     3 - evaluate 'process' definition
    *****************************************************************/
    
    // int numInputs, numOutputs;
    // Tree process = evaluateBlockDiagram(gGlobal->gExpandedDefList, numInputs, numOutputs);
    
    call_fun(thread_evaluateBlockDiagram); // In a thread with more stack size...
    if (!gGlobal->gProcessTree) {
        throw faustexception(gGlobal->gErrorMessage);
    }
    stringstream out;
    
    // Encode compilation options as a 'declare' : has to be located first in the string
    out << COMPILATION_OPTIONS << reorganize_compilation_options(argc, argv) << ';' << endl;
    
    // Encode all libraries paths as 'declare'
    vector<string> pathnames = gGlobal->gReader.listSrcFiles();
    for (vector<string>::iterator it = pathnames.begin(); it != pathnames.end(); it++) {
        out << "declare " << "library_path " << '"' << *it << "\";" << endl;
    }
    
    printDeclareHeader(out);
    out << "process = " << boxpp(gGlobal->gProcessTree) << ';' << endl;
    return out.str();
}

void compile_faust_internal(int argc, const char* argv[], const char* name, const char* dsp_content, bool generate)
{
    gGlobal->gPrintFileListSwitch = false;
  
    /****************************************************************
     1 - process command line
    *****************************************************************/
    process_cmdline(argc, argv);
    
    if (gGlobal->gHelpSwitch) { 
        printhelp(); 
        throw faustexception("");
    }
    if (gGlobal->gVersionSwitch) { 
        printversion(); 
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
            error << "ERROR : can't inject \"" << gGlobal->gInjectFile << "\" external code file, file not found" << endl;
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
    parseSourceFiles();
    
    initFaustDirectories();

    /****************************************************************
     3 - evaluate 'process' definition
    *****************************************************************/
    
    // int numInputs, numOutputs;
    // Tree process = evaluateBlockDiagram(gGlobal->gExpandedDefList, numInputs, numOutputs);
    
    call_fun(thread_evaluateBlockDiagram); // In a thread with more stack size...
    if (!gGlobal->gProcessTree) {
        throw faustexception(gGlobal->gErrorMessage);
    }
    Tree process = gGlobal->gProcessTree;
    int numInputs = gGlobal->gNumInputs;
    int numOutputs = gGlobal->gNumOutputs;
    
    if (gGlobal->gExportDSP) {
        ofstream out(subst("$0_exp.dsp", makeDrawPathNoExt()).c_str());
        
        // Encode compilation options as a 'declare' : has to be located first in the string
        out << COMPILATION_OPTIONS << reorganize_compilation_options(argc, argv) << ';' << endl;
   
        // Encode all libraries paths as 'declare'
        vector<string> pathnames = gGlobal->gReader.listSrcFiles();
        for (vector<string>::iterator it = pathnames.begin(); it != pathnames.end(); it++) {
            out << "declare " << "library_path " << '"' << *it << "\";" << endl;
        }
        
        printDeclareHeader(out);
        out << "process = " << boxpp(process) << ';' << endl;
        return;
    }

    /****************************************************************
     4 - compute output signals of 'process'
    *****************************************************************/
    startTiming("propagation");

    //Tree lsignals = boxPropagateSig(gGlobal->nil, process, makeSigInputList(numInputs));
    
    call_fun(thread_boxPropagateSig); // In a thread with more stack size...
    if (!gGlobal->gLsignalsTree) {
        throw faustexception(gGlobal->gErrorMessage);
    }
    Tree lsignals = gGlobal->gLsignalsTree;
 
    if (gGlobal->gDetailsSwitch) {
        cout << "output signals are : " << endl;
        Tree ls = lsignals;
        while (! isNil(ls)) {
            cout << ppsig(hd(ls)) << endl;
            ls = tl(ls);
        }
    }

    endTiming("propagation");

    /****************************************************************
    5 - preparation of the signal tree and translate output signals into C, C++, JAVA, JavaScript/ASMJavaScript or LLVM IR
    *****************************************************************/
    pair<InstructionsCompiler*, CodeContainer*> comp_container = generateCode(lsignals, numInputs, numOutputs, generate);

    /****************************************************************
     6 - generate xml description, documentation or dot files
    *****************************************************************/
    generateOutputFiles(comp_container.first, comp_container.second);
}

#if LLVM_BUILD

EXPORT LLVMResult* compile_faust_llvm(int argc, const char* argv[], const char* name, const char* dsp_content, char* error_msg)
{
    gGlobal = NULL;
    LLVMResult* res;
    
    try {
    
        // Compile module
        global::allocate();
        gGlobal->gLLVMOut = false;
        compile_faust_internal(argc, argv, name, dsp_content, true);
        strncpy(error_msg, gGlobal->gErrorMsg.c_str(), 256);  
        res = gGlobal->gLLVMResult;
            
    } catch (faustexception& e) {
        strncpy(error_msg, e.Message().c_str(), 256);
        res = NULL;
    }
    
    global::destroy();
    return res;
}

#endif

EXPORT int compile_faust(int argc, const char* argv[], const char* name, const char* dsp_content, char* error_msg, bool generate)
{
    gGlobal = NULL;
    int res;
    
    try {
        global::allocate();  
        gGlobal->gLLVMOut = true;   
        compile_faust_internal(argc, argv, name, dsp_content, generate);
        strncpy(error_msg, gGlobal->gErrorMsg.c_str(), 256);
        res = 0;
    } catch (faustexception& e) {
        strncpy(error_msg, e.Message().c_str(), 256);
        res = -1;
    }
    
    global::destroy();
    return res;
}

EXPORT string compile_faust_asmjs(int argc, const char* argv[], const char* name, const char* dsp_content, char* error_msg)
{
    gGlobal = NULL;
    string res;
    
    try {
        global::allocate(); 
        gGlobal->gLLVMOut = true;    
        compile_faust_internal(argc, argv, name, dsp_content, true);
        strncpy(error_msg, gGlobal->gErrorMsg.c_str(), 256);
        res = dynamic_cast<stringstream*>(gGlobal->gStringResult)->str();
    } catch (faustexception& e) {
        strncpy(error_msg, e.Message().c_str(), 256);
        res = "";
    }
    
    global::destroy();
    return res;
}

EXPORT string expand_dsp(int argc, const char* argv[], const char* name, const char* dsp_content, char* sha_key, char* error_msg)
{
    string res;
    gGlobal = NULL;
    
    try {
        global::allocate();       
        res = expand_dsp_internal(argc, argv, name, dsp_content);
        strcpy(sha_key, generateSHA1(res).c_str());
        strncpy(error_msg, gGlobal->gErrorMsg.c_str(), 256);
    } catch (faustexception& e) {
        strncpy(error_msg, e.Message().c_str(), 256);
        res = "";
    }
    
    global::destroy();
    return res;
}

