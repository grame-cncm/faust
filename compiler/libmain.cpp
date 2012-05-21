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
#define FAUSTVERSION "2.0.a3"

#include <stdio.h>
#include <string.h>
#include <assert.h>

#ifndef WIN32
#include <sys/time.h>
#include "libgen.h"
#endif

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

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#ifndef WIN32
#include <unistd.h>
#endif

#include "sourcereader.hh"

#include "instructions_compiler.hh"
#include "dag_instructions_compiler.hh"
#include "c_code_container.hh"
#include "cpp_code_container.hh"
#include "cpp_gpu_code_container.hh"
#include "java_code_container.hh"
#include "js_code_container.hh"
#include "llvm_code_container.hh"
#include "fir_code_container.hh"

// Build graphical representations

#include "schema.h"
#include "drawschema.hh"
#include "timing.hh"
#include "ppsig.hh"

using namespace std;

/****************************************************************
 						Parser variables
*****************************************************************/

int             yyerr;

global*         gGlobal;

static string gOutputLang = "";

/****************************************************************
 				Command line tools and arguments
*****************************************************************/

//-- command line arguments

static bool			gLLVMSwitch 	= false;
static bool			gHelpSwitch 	= false;
static bool			gVersionSwitch 	= false;
static bool         gGraphSwitch 	= false;
static bool         gDrawPSSwitch 	= false;
static bool         gDrawSVGSwitch 	= false;
static bool         gPrintXMLSwitch = false;
static bool         gPrintDocSwitch = false;
static int          gBalancedSwitch = 0;
static string       gArchFile;
static list<string>	gInputFiles;

static int      gTimeout        = 120;            // time out to abort compiler (in seconds)
static bool		gPrintFileListSwitch = false;

//-- command line tools

static bool isCmd(const char* cmd, const char* kw1)
{
	return 	(strcmp(cmd, kw1) == 0);
}

static bool isCmd(const char* cmd, const char* kw1, const char* kw2)
{
	return 	(strcmp(cmd, kw1) == 0) || (strcmp(cmd, kw2) == 0);
}

static bool process_cmdline(int argc, char* argv[])
{
	int	i=1; int err=0;

	while (i<argc) {

		if (isCmd(argv[i], "-h", "--help")) {
			gHelpSwitch = true;
			i += 1;
        } else if (isCmd(argv[i], "-llvm", "--LLVM")) {
			gLLVMSwitch = true;
			i += 1;
        } else if (isCmd(argv[i], "-lang", "--language")) {
			gOutputLang = argv[i+1];
			i += 2;
        } else if (isCmd(argv[i], "-v", "--version")) {
			gVersionSwitch = true;
			i += 1;

		} else if (isCmd(argv[i], "-d", "--details")) {
			gGlobal->gDetailsSwitch = true;
			i += 1;

		} else if (isCmd(argv[i], "-a", "--architecture")) {
			gArchFile = argv[i+1];
			i += 2;

		} else if (isCmd(argv[i], "-o")) {
			gGlobal->gOutputFile = argv[i+1];
			i += 2;

		} else if (isCmd(argv[i], "-ps", "--postscript")) {
			gDrawPSSwitch = true;
			i += 1;

        } else if (isCmd(argv[i], "-xml", "--xml")) {
            gPrintXMLSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-tg", "--task-graph")) {
            gGraphSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-sg", "--signal-graph")) {
            gGlobal->gDrawSignals = true;
            i += 1;

        } else if (isCmd(argv[i], "-blur", "--shadow-blur")) {
            gGlobal->gShadowBlur = true;
            i += 1;

		} else if (isCmd(argv[i], "-svg", "--svg")) {
			gDrawSVGSwitch = true;
			i += 1;

		} else if (isCmd(argv[i], "-f", "--fold")) {
			gGlobal->gFoldThreshold = atoi(argv[i+1]);
			i += 2;

		} else if (isCmd(argv[i], "-mns", "--max-name-size")) {
			gGlobal->gMaxNameSize = atoi(argv[i+1]);
			i += 2;

		} else if (isCmd(argv[i], "-sn", "--simple-names")) {
			gGlobal->gSimpleNames = true;
			i += 1;

		} else if (isCmd(argv[i], "-lb", "--left-balanced")) {
			gBalancedSwitch = 0;
			i += 1;

		} else if (isCmd(argv[i], "-mb", "--mid-balanced")) {
			gBalancedSwitch = 1;
			i += 1;

		} else if (isCmd(argv[i], "-rb", "--right-balanced")) {
			gBalancedSwitch = 2;
			i += 1;

		} else if (isCmd(argv[i], "-lt", "--less-temporaries")) {
			gGlobal->gLessTempSwitch = true;
			i += 1;

		} else if (isCmd(argv[i], "-mcd", "--max-copy-delay")) {
			gGlobal->gMaxCopyDelay = atoi(argv[i+1]);
			i += 2;

		} else if (isCmd(argv[i], "-sd", "--simplify-diagrams")) {
			gGlobal->gSimplifyDiagrams = true;
			i += 1;

        } else if (isCmd(argv[i], "-vec", "--vectorize")) {
            gGlobal->gVectorSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-vls", "--vec-loop-size")) {
            gGlobal->gVecLoopSize = atoi(argv[i+1]);
            i += 2;

        } else if (isCmd(argv[i], "-scal", "--scalar")) {
            gGlobal->gVectorSwitch = false;
            i += 1;

        } else if (isCmd(argv[i], "-dfs", "--deepFirstScheduling")) {
            gGlobal->gDeepFirstSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-vs", "--vec-size")) {
            gGlobal->gVecSize = atoi(argv[i+1]);
            i += 2;

        } else if (isCmd(argv[i], "-lv", "--loop-variant")) {
            gGlobal->gVectorLoopVariant = atoi(argv[i+1]);
            if (gGlobal->gVectorLoopVariant < 0 ||
                gGlobal->gVectorLoopVariant > 1) {
                stringstream error;
                error << "faust: invalid loop variant: \"" << gGlobal->gVectorLoopVariant <<"\"" << endl;
                throw faustexception(error.str());
            }
            i += 2;

        } else if (isCmd(argv[i], "-omp", "--openMP")) {
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

        } else if (isCmd(argv[i], "-t", "--timeout")) {
            gTimeout = atoi(argv[i+1]);
            i += 2;

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
            gPrintDocSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-mdlang", "--mathdoc-lang")) {
            gGlobal->gDocLang = argv[i+1];
            i += 2;

        } else if (isCmd(argv[i], "-stripmdoc", "--strip-mdoc-tags")) {
            gGlobal->gStripDocSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-flist", "--file-list")) {
            gPrintFileListSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-norm", "--normalized-form")) {
            gGlobal->gDumpNorm = true;
            i += 1;

		} else if (isCmd(argv[i], "-cn", "--class-name")) {
			gGlobal->gClassName = argv[i+1];
			i += 2;

        } else if (isCmd(argv[i], "-i", "--inline-architecture-files")) {
            gGlobal->gInlineArchSwitch = false;
            i += 1;
			
       } else if (argv[i][0] != '-') {
			if (check_file(argv[i])) {
				gInputFiles.push_back(argv[i]);
			}
			i++;

		} else {
			cerr << "faust: unrecognized option \"" << argv[i] <<"\"" << endl;
			i++;
			err++;
		}
	}

    // adjust related options
    if (gGlobal->gOpenMPSwitch || gGlobal->gSchedulerSwitch) gGlobal->gVectorSwitch = true;

    if (gGlobal->gVecLoopSize > gGlobal->gVecSize) {
        stringstream error;
        error << "[-vls = "<< gGlobal->gVecLoopSize << "] has to be <= [-vs = " << gGlobal->gVecSize << "]" << endl;
        throw faustexception(error.str());
    }

	return err == 0;
}

/****************************************************************
 					 Help and Version information
*****************************************************************/

static void printversion()
{
	cout << "FAUST: DSP to C, C++, JAVA, JavaScript, LLVM compiler, Version " << FAUSTVERSION << "\n";
	cout << "Copyright (C) 2002-2012, GRAME - Centre National de Creation Musicale. All rights reserved. \n\n";
}

static void printhelp()
{
	printversion();
	cout << "usage: faust [options] file1 [file2 ...]\n";
	cout << "\twhere options represent zero or more compiler options \n\tand fileN represents a faust source file (.dsp extension).\n";

	cout << "\noptions :\n";
	cout << "---------\n";

	cout << "-h \t\tprint this --help message\n";
	cout << "-v \t\tprint compiler --version information\n";
	cout << "-d \t\tprint compilation --details\n";
    cout << "-tg \t\tprint the internal --task-graph in dot format file\n";
    cout << "-sg \t\tprint the internal --signal-graph in dot format file\n";
    cout << "-ps \t\tprint block-diagram --postscript file\n";
    cout << "-svg \tprint block-diagram --svg file\n";
    cout << "-mdoc \tprint --mathdoc of a Faust program in LaTeX format in a -mdoc directory\n";
    cout << "-mdlang <l>\t\tload --mathdoc-lang <l> if translation file exists (<l> = en, fr, ...)\n";
    cout << "-stripdoc \t\tapply --strip-mdoc-tags when printing Faust -mdoc listings\n";
    cout << "-sd \t\ttry to further --simplify-diagrams before drawing them\n";
	cout << "-f <n> \t\t--fold <n> threshold during block-diagram generation (default 25 elements) \n";
	cout << "-mns <n> \t--max-name-size <n> threshold during block-diagram generation (default 40 char)\n";
	cout << "-sn \t\tuse --simple-names (without arguments) during block-diagram generation\n";
	cout << "-xml \t\tgenerate an --xml description file\n";
    cout << "-blur \t\tadd a --shadow-blur to SVG boxes\n";
	cout << "-lb \t\tgenerate --left-balanced expressions\n";
	cout << "-mb \t\tgenerate --mid-balanced expressions (default)\n";
	cout << "-rb \t\tgenerate --right-balanced expressions\n";
	cout << "-lt \t\tgenerate --less-temporaries in compiling delays\n";
	cout << "-mcd <n> \t--max-copy-delay <n> threshold between copy and ring buffer implementation (default 16 samples)\n";
	cout << "-a <file> \tC++ architecture file\n";
	cout << "-i \t--inline-architecture-files \n";
	cout << "-cn <name> \t--class-name <name> specify the name of the dsp class to be used instead of mydsp \n";
	cout << "-t <sec> \t--timeout <sec>, abort compilation after <sec> seconds (default 120)\n";
    cout << "-o <file> \tC++ output file\n";
    cout << "-scal   \t--scalar generate non-vectorized code\n";
    cout << "-vec    \t--vectorize generate easier to vectorize code\n";
    cout << "-vls <n>  \t--vec-loop-size  size of the vector DSP loop \n";
    cout << "-vs <n> \t--vec-size <n> size of the vector (default 32 samples)\n";
    cout << "-lv <n> \t--loop-variant [0:fastest (default), 1:simple] \n";
    cout << "-omp    \t--openMP generate OpenMP pragmas, activates --vectorize option\n";
    cout << "-pl     \t--par-loop generate parallel loops in --openMP mode\n";
    cout << "-sch    \t--scheduler generate tasks and use a Work Stealing scheduler, activates --vectorize option\n";
    cout << "-ocl    \t--openCL generate tasks with OpenCL \n";
    cout << "-cuda   \t--cuda generate tasks with CUDA \n";
	cout << "-dfs    \t--deepFirstScheduling schedule vector loops in deep first order\n";
    cout << "-g    \t\t--groupTasks group single-threaded sequential tasks together when -omp or -sch is used\n";
    cout << "-fun  \t\t--funTasks separate tasks code as separated functions (in -vec, -sch, or -omp mode)\n";
    cout << "-lang <lang> \t--language generate various output formats : c, cpp, java, js, llvm, fir (default cpp)\n";
    cout << "-uim    \t--user-interface-macros add user interface macro definitions in the C++ code\n";
    cout << "-single \tuse --single-precision-floats for internal computations (default)\n";
    cout << "-double \tuse --double-precision-floats for internal computations\n";
    cout << "-quad \t\tuse --quad-precision-floats for internal computations\n";
    cout << "-flist \t\tuse --file-list used to eval process\n";
    cout << "-norm \t\t--normalized-form prints signals in normalized form and exits\n";

	cout << "\nexample :\n";
	cout << "---------\n";

	cout << "faust -a jack-gtk.cpp -o myfx.cpp myfx.dsp\n";
}

static void printheader(ostream& dst)
{
    // defines the metadata we want to print as comments at the begin of in the C++ file
    set<Tree> selectedKeys;
    selectedKeys.insert(tree("name"));
    selectedKeys.insert(tree("author"));
    selectedKeys.insert(tree("copyright"));
    selectedKeys.insert(tree("license"));
    selectedKeys.insert(tree("version"));

    dst << "//-----------------------------------------------------" << endl;
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
    dst << "// Code generated with Faust " << FAUSTVERSION << " (http://faust.grame.fr)" << endl;
    dst << "//-----------------------------------------------------" << endl;
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
    for (unsigned int i=0; i<filename.size(); i++) {
        if (filename[i] == '/')  { p1 = i+1; }
    }

	// determine position of the last '.'
	unsigned int p2 = filename.size();
    for (unsigned int i=p1; i<filename.size(); i++) {
        if (filename[i] == '.')  { p2 = i; }
    }

    return filename.substr(p1, p2-p1);
}

static void initFaustDirectories()
{
    char s[1024];
    getFaustPathname(s, 1024);

    gGlobal->gFaustDirectory = filedirname(s);
    gGlobal->gFaustSuperDirectory = filedirname(gGlobal->gFaustDirectory);
    gGlobal->gFaustSuperSuperDirectory = filedirname(gGlobal->gFaustSuperDirectory);
    if (gInputFiles.empty()) {
        gGlobal->gMasterDocument = "Unknown";
        gGlobal->gMasterDirectory = ".";
		gGlobal->gMasterName = "faustfx";
		gGlobal->gDocName = "faustdoc";
    } else {
        gGlobal->gMasterDocument = *gInputFiles.begin();
        gGlobal->gMasterDirectory = filedirname(gGlobal->gMasterDocument);
		gGlobal->gMasterName = fxname(gGlobal->gMasterDocument);
		gGlobal->gDocName = fxname(gGlobal->gMasterDocument);
    }
}

static void parseSourceFiles()
{
    startTiming("parser");

    list<string>::iterator s;
    gGlobal->gResult2 = nil;

    if (gInputFiles.begin() == gInputFiles.end()) {
        stringstream error;
        error << "ERROR: no files specified; for help type \"faust --help\"" << endl;
        throw faustexception(error.str());
    }
    for (s = gInputFiles.begin(); s != gInputFiles.end(); s++) {
        if (s == gInputFiles.begin()) gGlobal->gMasterDocument = *s;
        gGlobal->gResult2 = cons(importFile(tree(s->c_str())), gGlobal->gResult2);
    }
   
    gGlobal->gExpandedDefList = gGlobal->gReader.expandlist(gGlobal->gResult2);

    endTiming("parser");
}


static Tree evaluateBlockDiagram(Tree expandedDefList, int& numInputs, int& numOutputs)
{
    startTiming("evaluation");

    Tree process = evalprocess(expandedDefList);
    if (gErrorCount > 0) {
        stringstream error;
        error << "Total of " << gErrorCount << " errors during the compilation of  " << gGlobal->gMasterDocument << ";\n";
        throw faustexception(error.str());
    }

    if (gGlobal->gDetailsSwitch) { cerr << "process = " << boxpp(process) << ";\n"; }

    if (gDrawPSSwitch || gDrawSVGSwitch) {
        string projname = gGlobal->gMasterDocument;
        if( gGlobal->gMasterDocument.substr(gGlobal->gMasterDocument.length()-4) == ".dsp" ) {
            projname = gGlobal->gMasterDocument.substr(0, gGlobal->gMasterDocument.length()-4);
        }
        if (gDrawPSSwitch)  { drawSchema(process, subst("$0-ps",  projname).c_str(), "ps"); }
        if (gDrawSVGSwitch) { drawSchema(process, subst("$0-svg", projname).c_str(), "svg"); }
    }

    if (!getBoxType(process, &numInputs, &numOutputs)) {
        stringstream error;
        error << "ERROR during the evaluation of  process : " << boxpp(process) << endl;
        throw faustexception(error.str());
    }

    if (gGlobal->gDetailsSwitch) {
        cerr <<"process has " << numInputs <<" inputs, and " << numOutputs <<" outputs" << endl;
    }

    endTiming("evaluation");

    if (gPrintFileListSwitch) {
        cout << "******* ";
        // print the pathnames of the files used to evaluate process
        vector<string> pathnames = gGlobal->gReader.listSrcFiles();
        for (unsigned int i=0; i< pathnames.size(); i++) cout << pathnames[i] << ' ';
        cout << endl;
    }

    return process;
}

static pair<InstructionsCompiler*, CodeContainer*> generateCode(Tree signals, int numInputs, int numOutputs)
{
    // By default use "cpp" output
    if (gOutputLang == "") {
        gOutputLang = "cpp";
    }

    InstructionsCompiler* comp;
    CodeContainer* container = NULL;

    startTiming("compilation");

    istream* enrobage;
    ostream* dst;

    if (gGlobal->gOutputFile != "") {
        dst = new ofstream(gGlobal->gOutputFile.c_str());
    } else {
        dst = &cout;
    }

    if (gOutputLang == "llvm") {

        container = LLVMCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, dst);

        if (gGlobal->gVectorSwitch) {
            comp = new DAGInstructionsCompiler(container);
        } else {
            comp = new InstructionsCompiler(container);
        }

        if (gPrintXMLSwitch) comp->setDescription(new Description());
        if (gPrintDocSwitch) comp->setDescription(new Description());

        // Prepare signals
        comp->prepare(signals);
     
        comp->compileMultiSignal(signals);
        gGlobal->gModule = dynamic_cast<LLVMCodeContainer*>(container)->produceModule(gGlobal->gOutputFile.c_str());
  
    } else {
        if (gOutputLang == "c") {

            container = CCodeContainer::createContainer(gGlobal->gClassName, numInputs, numOutputs, dst);

        } else if (gOutputLang == "cpp") {

            container = CPPCodeContainer::createContainer(gGlobal->gClassName, "dsp", numInputs, numOutputs, dst);

        } else if (gOutputLang == "java") {

            container = JAVACodeContainer::createContainer(gGlobal->gClassName, "dsp", numInputs, numOutputs, dst);
            
        } else if (gOutputLang == "js") {

            container = JAVAScriptCodeContainer::createContainer(gGlobal->gClassName, "dsp", numInputs, numOutputs, dst);

        } else if (gOutputLang == "fir") {

            container = FirCodeContainer::createContainer(numInputs, numOutputs);

            if (gGlobal->gVectorSwitch) {
                comp = new DAGInstructionsCompiler(container);
            } else {
                comp = new InstructionsCompiler(container);
            }

            // Prepare signals
            comp->prepare(signals);

            comp->compileMultiSignal(signals);
            container->dump(dst);
            exit(0);
        }
        if (!container) {
            stringstream error;
            error << "ERROR : cannot find compiler for " << "\"" << gOutputLang  << "\"" << endl;
            throw faustexception(error.str());
        }
        if (gGlobal->gVectorSwitch) {
            comp = new DAGInstructionsCompiler(container);
        } else {
            comp = new InstructionsCompiler(container);
        }

        if (gPrintXMLSwitch) comp->setDescription(new Description());
        if (gPrintDocSwitch) comp->setDescription(new Description());

        // Prepare signals
        comp->prepare(signals);

        comp->compileMultiSignal(signals);

        /****************************************************************
         * generate output file
         ****************************************************************/
        if (gArchFile != "") {
            if ((enrobage = open_arch_stream(gArchFile.c_str()))) {
            
                if (gOutputLang != "js") {
                    printheader(*dst);
                }
                
                if (gOutputLang == "c" || gOutputLang == "cpp") {
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
                }

                if (gOutputLang != "java" && gOutputLang != "js") {
                    printfloatdef(*dst, (gGlobal->gFloatSize == 3));
                }

                if (gOutputLang == "c") {
                    *dst << "#include <stdlib.h>"<< std::endl;
                }

                container->produceClass();
                streamCopyUntilEnd(*enrobage, *dst);
                if (gGlobal->gOpenCLSwitch) {
                    istream* scheduler_include = open_arch_stream("scheduler.cpp");
                    if (scheduler_include) {
                        streamCopy(*scheduler_include, *dst);
                    }
                }

                if (gOutputLang == "c" || gOutputLang == "cpp") {
                    tab(0, *dst); *dst << "#endif"<< std::endl;
                }

            } else {
                stringstream error;
                error << "ERROR : can't open architecture file " << gArchFile << endl;
                throw faustexception(error.str());
            }
        } else {
            if (gOutputLang != "js") {
                printheader(*dst);
            }
            if (gOutputLang != "java" && gOutputLang != "js") {
                printfloatdef(*dst, (gGlobal->gFloatSize == 3));
            }
            if (gOutputLang == "c") {
                *dst << "#include <stdlib.h>"<< std::endl;
            }
            container->produceClass();
        }
    }
    endTiming("compilation");

    return make_pair(comp, container);
}

static void generateOutputFiles(InstructionsCompiler * comp, CodeContainer * container)
{
    /****************************************************************
     1 - generate XML description (if required)
    *****************************************************************/

    if (gPrintXMLSwitch) {
        Description*    D = comp->getDescription(); assert(D);
        ofstream        xout(subst("$0.xml", gGlobal->gMasterDocument).c_str());

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

    if (gPrintDocSwitch) {
        if (gGlobal->gLatexDocSwitch) {
            string projname = gGlobal->gMasterDocument;
            if (gGlobal->gMasterDocument.substr(gGlobal->gMasterDocument.length()-4) == ".dsp") {
                projname = gGlobal->gMasterDocument.substr(0, gGlobal->gMasterDocument.length() - 4); }
            printDoc( subst("$0-mdoc", projname).c_str(), "tex", FAUSTVERSION );
        }
    }

    /****************************************************************
     3 - generate the task graph file in dot format
    *****************************************************************/

    if (gGraphSwitch) {
        ofstream dotfile(subst("$0.dot", gGlobal->gMasterDocument).c_str());
        container->printGraphDotFormat(dotfile);
    }
}

#ifdef __cplusplus
extern "C" int compile_faust(int argc, char* argv[], const char* input);
extern "C" Module* compile_faust_llvm(int argc, char* argv[], const char* input);
#endif

int compile_faust(int argc, char* argv[], const char* input = NULL)
{
    try {
    
        gGlobal = new global();
        
        /****************************************************************
         1 - process command line
        *****************************************************************/
        process_cmdline(argc, argv);

        if (gHelpSwitch) 		{ printhelp(); exit(0); }
        if (gVersionSwitch) 	{ printversion(); exit(0); }

        initFaustDirectories();
    #ifndef WIN32
        alarm(gTimeout);
    #endif

        /****************************************************************
         2 - parse source files
        *****************************************************************/
        if (input) {
            gGlobal->gInputString = input;
            gInputFiles.push_back("input_string");
        }
        parseSourceFiles();

        /****************************************************************
         3 - evaluate 'process' definition
        *****************************************************************/
        int numInputs, numOutputs;
        Tree process = evaluateBlockDiagram(gGlobal->gExpandedDefList, numInputs, numOutputs);

        /****************************************************************
         4 - compute output signals of 'process'
        *****************************************************************/
        startTiming("propagation");

        Tree lsignals = boxPropagateSig(nil, process , makeSigInputList(numInputs));

        if (gGlobal->gDetailsSwitch) {
            cerr << "output signals are : " << endl;
            Tree ls =  lsignals;
            while (! isNil(ls)) {
                cerr << ppsig(hd(ls)) << endl;
                ls = tl(ls);
            }
        }

        endTiming("propagation");

        /****************************************************************
        5 - preparation of the signal tree and translate output signals into C, C++, JAVA, JavaScript or LLVM code
        *****************************************************************/
        pair<InstructionsCompiler*, CodeContainer*> comp_container = generateCode(lsignals, numInputs, numOutputs);

        /****************************************************************
         6 - generate xml description, documentation or dot files
        *****************************************************************/
        generateOutputFiles(comp_container.first, comp_container.second);
        
        delete gGlobal;
    
    } catch (faustexception& e) {
        e.PrintMessage();
        return -1;
    }
    
	return 0;
}

Module* compile_faust_llvm(int argc, char* argv[], const char* input)
{
    compile_faust(argc, argv, input);
    return gGlobal->gModule;
}
