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
#include "llvm_code_container.hh"
#include "fir_code_container.hh"

// Build graphical representations

#include "schema.h"
#include "drawschema.hh"
#include "timing.hh"
#include "ppsig.hh"

using namespace std ;

/****************************************************************
 						Parser variables
*****************************************************************/

int yyparse();

int 			yyerr;
extern int 	    yydebug;
extern FILE*	yyin;
Tree 			gResult;
Tree 			gResult2;

SourceReader	gReader;

map<Tree, set<Tree> > gMetaDataSet;
extern vector<Tree> gDocVector;
extern string gDocLang;
extern bool gDumpNorm;

string gOutputLang = "";

/****************************************************************
 				Command line tools and arguments
*****************************************************************/

//-- globals
string          gFaustSuperSuperDirectory;
string          gFaustSuperDirectory;
string          gFaustDirectory;
string          gMasterDocument;
string          gMasterDirectory;
string          gMasterName;
string          gDocName;
Tree			gExpandedDefList;

//-- command line arguments

bool			gLLVMSwitch 	= false;
bool			gLLVM64         = true;
bool			gHelpSwitch 	= false;
bool			gVersionSwitch 	= false;
bool            gDetailsSwitch  = false;
bool            gDrawSignals    = false;
bool            gShadowBlur     = false;	// note: svg2pdf doesn't like the blur filter
bool            gGraphSwitch 	= false;
bool            gDrawPSSwitch 	= false;
bool            gDrawSVGSwitch 	= false;
bool            gPrintXMLSwitch = false;
bool            gPrintDocSwitch = false;
bool            gLatexDocSwitch = true;		// Only LaTeX outformat is handled for the moment.
bool			gStripDocSwitch = false;	// Strip <mdoc> content from doc listings.
int            	gBalancedSwitch = 0;
int            	gFoldThreshold 	= 25;
int            	gMaxNameSize 	= 40;
bool			gSimpleNames 	= false;
bool            gSimplifyDiagrams = false;
bool			gLessTempSwitch = false;
int				gMaxCopyDelay	= 16;
string			gArchFile;
string			gOutputFile;
list<string>	gInputFiles;

bool            gPatternEvalMode = false;

bool            gVectorSwitch   = false;
bool            gDeepFirstSwitch = false;
int             gVecSize        = 32;
int             gVectorLoopVariant = 0;
int             gVecLoopSize = 0;

bool            gOpenMPSwitch   = false;
bool            gOpenMPLoop     = false;
bool            gSchedulerSwitch  = false;
bool            gOpenCLSwitch  = false;
bool            gCUDASwitch = false;
bool			gGroupTaskSwitch = false;
bool			gFunTaskSwitch = false;


bool            gUIMacroSwitch  = false;
bool            gDumpNorm       = false;

int             gTimeout        = 120;            // time out to abort compiler (in seconds)

int             gFloatSize = 1;

bool			gPrintFileListSwitch = false;

bool			gDSPStruct = false;

string			gClassName = "mydsp";

//-- command line tools

static bool isCmd(const char* cmd, const char* kw1)
{
	return 	(strcmp(cmd, kw1) == 0);
}

static bool isCmd(const char* cmd, const char* kw1, const char* kw2)
{
	return 	(strcmp(cmd, kw1) == 0) || (strcmp(cmd, kw2) == 0);
}

bool process_cmdline(int argc, char* argv[])
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
			gDetailsSwitch = true;
			i += 1;

		} else if (isCmd(argv[i], "-a", "--architecture")) {
			gArchFile = argv[i+1];
			i += 2;

		} else if (isCmd(argv[i], "-o")) {
			gOutputFile = argv[i+1];
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
            gDrawSignals = true;
            i += 1;

        } else if (isCmd(argv[i], "-blur", "--shadow-blur")) {
            gShadowBlur = true;
            i += 1;

		} else if (isCmd(argv[i], "-svg", "--svg")) {
			gDrawSVGSwitch = true;
			i += 1;

		} else if (isCmd(argv[i], "-f", "--fold")) {
			gFoldThreshold = atoi(argv[i+1]);
			i += 2;

		} else if (isCmd(argv[i], "-mns", "--max-name-size")) {
			gMaxNameSize = atoi(argv[i+1]);
			i += 2;

		} else if (isCmd(argv[i], "-sn", "--simple-names")) {
			gSimpleNames = true;
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
			gLessTempSwitch = true;
			i += 1;

		} else if (isCmd(argv[i], "-mcd", "--max-copy-delay")) {
			gMaxCopyDelay = atoi(argv[i+1]);
			i += 2;

		} else if (isCmd(argv[i], "-sd", "--simplify-diagrams")) {
			gSimplifyDiagrams = true;
			i += 1;

        } else if (isCmd(argv[i], "-vec", "--vectorize")) {
            gVectorSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-vls", "--vec-loop-size")) {
            gVecLoopSize = atoi(argv[i+1]);
            i += 2;

        } else if (isCmd(argv[i], "-scal", "--scalar")) {
            gVectorSwitch = false;
            i += 1;

        } else if (isCmd(argv[i], "-dfs", "--deepFirstScheduling")) {
            gDeepFirstSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-vs", "--vec-size")) {
            gVecSize = atoi(argv[i+1]);
            i += 2;

        } else if (isCmd(argv[i], "-lv", "--loop-variant")) {
            gVectorLoopVariant = atoi(argv[i+1]);
            if (gVectorLoopVariant < 0 ||
                gVectorLoopVariant > 1) {
                cerr << "faust: invalid loop variant: \"" << gVectorLoopVariant <<"\"" << endl;
                exit(1);
            }
            i += 2;

        } else if (isCmd(argv[i], "-omp", "--openMP")) {
            gOpenMPSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-pl", "--par-loop")) {
            gOpenMPLoop = true;
            i += 1;

        } else if (isCmd(argv[i], "-sch", "--scheduler")) {
			gSchedulerSwitch = true;
			i += 1;

         } else if (isCmd(argv[i], "-ocl", "--openCL")) {
			gOpenCLSwitch = true;
			i += 1;

        } else if (isCmd(argv[i], "-cuda", "--CUDA")) {
			gCUDASwitch = true;
			i += 1;

        } else if (isCmd(argv[i], "-g", "--groupTasks")) {
			gGroupTaskSwitch = true;
			i += 1;

        } else if (isCmd(argv[i], "-fun", "--funTasks")) {
			gFunTaskSwitch = true;
			i += 1;

        } else if (isCmd(argv[i], "-uim", "--user-interface-macros")) {
			gUIMacroSwitch = true;
			i += 1;

        } else if (isCmd(argv[i], "-t", "--timeout")) {
            gTimeout = atoi(argv[i+1]);
            i += 2;

        // double float options
        } else if (isCmd(argv[i], "-single", "--single-precision-floats")) {
            gFloatSize = 1;
            i += 1;

        } else if (isCmd(argv[i], "-double", "--double-precision-floats")) {
            gFloatSize = 2;
            i += 1;

        } else if (isCmd(argv[i], "-quad", "--quad-precision-floats")) {
            gFloatSize = 3;
            i += 1;

        } else if (isCmd(argv[i], "-mdoc", "--mathdoc")) {
            gPrintDocSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-mdlang", "--mathdoc-lang")) {
            gDocLang = argv[i+1];
            i += 2;

        } else if (isCmd(argv[i], "-stripmdoc", "--strip-mdoc-tags")) {
            gStripDocSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-flist", "--file-list")) {
            gPrintFileListSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-norm", "--normalized-form")) {
            gDumpNorm = true;
            i += 1;

		} else if (isCmd(argv[i], "-cn", "--class-name")) {
			gClassName = argv[i+1];
			i += 2;

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
    if (gOpenMPSwitch || gSchedulerSwitch) gVectorSwitch = true;

    if (gVecLoopSize > gVecSize) {
        cerr << "[-vls = "<< gVecLoopSize << "] has to be <= [-vs = " << gVecSize << "]" << endl;
        exit(1);
    }

	return err == 0;
}

/****************************************************************
 					 Help and Version information
*****************************************************************/

void printversion()
{
	cout << "FAUST: DSP to C, C++, JAVA, LLVM compiler, Version " << FAUSTVERSION << "\n";
	cout << "Copyright (C) 2002-2011, GRAME - Centre National de Creation Musicale. All rights reserved. \n\n";
}

void printhelp()
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
    cout << "-lang <lang> \t--language generate various output formats : c, cpp, java, llvm, fir (default cpp)\n";
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

void printheader(ostream& dst)
{
    // defines the metadata we want to print as comments at the begin of in the C++ file
    set<Tree> selectedKeys;
    selectedKeys.insert(tree("name"));
    selectedKeys.insert(tree("author"));
    selectedKeys.insert(tree("copyright"));
    selectedKeys.insert(tree("license"));
    selectedKeys.insert(tree("version"));

    dst << "//-----------------------------------------------------" << endl;
    for (map<Tree, set<Tree> >::iterator i = gMetaDataSet.begin(); i != gMetaDataSet.end(); i++) {
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

    gFaustDirectory = filedirname(s);
    gFaustSuperDirectory = filedirname(gFaustDirectory);
    gFaustSuperSuperDirectory = filedirname(gFaustSuperDirectory);
    if (gInputFiles.empty()) {
        gMasterDocument = "Unknown";
        gMasterDirectory = ".";
		gMasterName = "faustfx";
		gDocName = "faustdoc";
    } else {
        gMasterDocument = *gInputFiles.begin();
        gMasterDirectory = filedirname(gMasterDocument);
		gMasterName = fxname(gMasterDocument);
		gDocName = fxname(gMasterDocument);
    }
}

static void parseSourceFiles()
{
    startTiming("parser");

    list<string>::iterator s;
    gResult2 = nil;
    yyerr = 0;

    if (gInputFiles.begin() == gInputFiles.end()) {
        cerr << "ERROR: no files specified; for help type \"faust --help\"" << endl;
        exit(1);
    }
    for (s = gInputFiles.begin(); s != gInputFiles.end(); s++) {
        if (s == gInputFiles.begin()) gMasterDocument = *s;
        gResult2 = cons(importFile(tree(s->c_str())), gResult2);
    }
    if (yyerr > 0) {
        //fprintf(stderr, "Erreur de parsing 2, count = %d \n", yyerr);
        exit(1);
    }
    gExpandedDefList = gReader.expandlist(gResult2);

    endTiming("parser");
}

static Tree evaluateBlockDiagram(Tree expandedDefList, int & numInputs, int & numOutputs)
{
    startTiming("evaluation");

    Tree process = evalprocess(expandedDefList);
    if (gErrorCount > 0) {
       // cerr << "Total of " << gErrorCount << " errors during evaluation of : process = " << boxpp(process) << ";\n";
        cerr << "Total of " << gErrorCount << " errors during the compilation of  " << gMasterDocument << ";\n";
        exit(1);
    }

    if (gDetailsSwitch) { cerr << "process = " << boxpp(process) << ";\n"; }

    if (gDrawPSSwitch || gDrawSVGSwitch) {
        string projname = gMasterDocument;
        if( gMasterDocument.substr(gMasterDocument.length()-4) == ".dsp" ) {
            projname = gMasterDocument.substr(0, gMasterDocument.length()-4);
        }
        if (gDrawPSSwitch)  { drawSchema( process, subst("$0-ps",  projname).c_str(), "ps" ); }
        if (gDrawSVGSwitch) { drawSchema( process, subst("$0-svg", projname).c_str(), "svg" ); }
    }

    if (!getBoxType(process, &numInputs, &numOutputs)) {
        cerr << "ERROR during the evaluation of  process : "
             << boxpp(process) << endl;
        exit(1);
    }

    if (gDetailsSwitch) {
        cerr <<"process has " << numInputs <<" inputs, and " << numOutputs <<" outputs" << endl;
    }

    endTiming("evaluation");

    if (gPrintFileListSwitch) {
        cout << "******* ";
        // print the pathnames of the files used to evaluate process
        vector<string> pathnames = gReader.listSrcFiles();
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

    if (gOutputFile != "") {
        dst = new ofstream(gOutputFile.c_str());
    } else {
        dst = &cout;
    }

    if (gOutputLang == "llvm") {

        container = LLVMCodeContainer::createContainer(gClassName, numInputs, numOutputs, dst);

        if (gVectorSwitch) {
            comp = new DAGInstructionsCompiler(container);
        } else {
            comp = new InstructionsCompiler(container);
        }

        if (gPrintXMLSwitch) comp->setDescription(new Description());
        if (gPrintDocSwitch) comp->setDescription(new Description());

        // Prepare signals
        comp->prepare(signals);

        comp->compileMultiSignal(signals);
        dynamic_cast<LLVMCodeContainer*>(container)->produceModule(gOutputFile.c_str());

    } else {
        if (gOutputLang == "c") {

            container = CCodeContainer::createContainer(gClassName, numInputs, numOutputs, dst);

        } else if (gOutputLang == "cpp") {

            container = CPPCodeContainer::createContainer(gClassName, "dsp", numInputs, numOutputs, dst);

        } else if (gOutputLang == "java") {

            container = JAVACodeContainer::createContainer(gClassName, "dsp", numInputs, numOutputs, dst);

       } else if (gOutputLang == "fir") {

            container = FirCodeContainer::createContainer(numInputs, numOutputs);

            if (gVectorSwitch) {
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
             cerr << "ERROR : cannot find compiler for " << "\"" << gOutputLang  << "\"" << endl;
             exit(1);
        }
        if (gVectorSwitch) {
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

                if (gOutputLang == "c" || gOutputLang == "cpp") {
                    tab(0, *dst); *dst << "#ifndef  __" << gClassName << "_H__";
                    tab(0, *dst); *dst << "#define  __" << gClassName << "_H__" << std::endl;
                }

                streamCopyUntil(*enrobage, *dst, "<<includeIntrinsic>>");
                streamCopyUntil(*enrobage, *dst, "<<includeclass>>");

                if (gOpenCLSwitch || gCUDASwitch) {
                    istream* thread_include = open_arch_stream("thread.h");
                    if (thread_include) {
                        streamCopy(*thread_include, *dst);
                    }
                }

                if (gOutputLang != "java") {
                    printfloatdef(*dst);
                }

                if (gOutputLang == "c") {
                    *dst << "#include <stdlib.h>"<< std::endl;
                }

                container->produceClass();
                streamCopyUntilEnd(*enrobage, *dst);
                if (gSchedulerSwitch) {
                    istream* scheduler_include = open_arch_stream("scheduler.h");
                    if (scheduler_include) {
                        streamCopy(*scheduler_include, *dst);
                    }
                }

                if (gOutputLang == "c" || gOutputLang == "cpp") {
                    tab(0, *dst); *dst << "#endif"<< std::endl;
                }

            } else {
                cerr << "ERROR : can't open architecture file " << gArchFile << endl;
                exit(1);
            }
        } else {
            if (gOutputLang != "java") {
                printfloatdef(*dst);
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
        ofstream        xout(subst("$0.xml", gMasterDocument).c_str());

        if (gMetaDataSet.count(tree("name")) > 0)          D->name(tree2str(*(gMetaDataSet[tree("name")].begin())));
        if (gMetaDataSet.count(tree("author")) > 0)        D->author(tree2str(*(gMetaDataSet[tree("author")].begin())));
        if (gMetaDataSet.count(tree("copyright")) > 0)     D->copyright(tree2str(*(gMetaDataSet[tree("copyright")].begin())));
        if (gMetaDataSet.count(tree("license")) > 0)       D->license(tree2str(*(gMetaDataSet[tree("license")].begin())));
        if (gMetaDataSet.count(tree("version")) > 0)       D->version(tree2str(*(gMetaDataSet[tree("version")].begin())));

        D->inputs(container->inputs());
        D->outputs(container->outputs());

        D->print(0, xout);
    }

    /****************************************************************
     2 - generate documentation from Faust comments (if required)
    *****************************************************************/

    if (gPrintDocSwitch) {
        if (gLatexDocSwitch) {
            string projname = gMasterDocument;
            if (gMasterDocument.substr(gMasterDocument.length()-4) == ".dsp") {
                projname = gMasterDocument.substr(0, gMasterDocument.length() - 4); }
            printDoc( subst("$0-mdoc", projname).c_str(), "tex", FAUSTVERSION );
        }
    }

    /****************************************************************
     3 - generate the task graph file in dot format
    *****************************************************************/

    if (gGraphSwitch) {
        ofstream dotfile(subst("$0.dot", gMasterDocument).c_str());
        container->printGraphDotFormat(dotfile);
    }
}

int main (int argc, char* argv[])
{
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
    parseSourceFiles();

	/****************************************************************
	 3 - evaluate 'process' definition
	*****************************************************************/
    int numInputs, numOutputs;
    Tree process = evaluateBlockDiagram(gExpandedDefList, numInputs, numOutputs);

	/****************************************************************
	 4 - compute output signals of 'process'
	*****************************************************************/
	startTiming("propagation");

	Tree lsignals = boxPropagateSig(nil, process , makeSigInputList(numInputs) );

	if (gDetailsSwitch) {
		cerr << "output signals are : " << endl;
		Tree ls =  lsignals;
		while (! isNil(ls)) {
			cerr << ppsig(hd(ls)) << endl;
			ls = tl(ls);
		}
	}

	endTiming("propagation");

	/****************************************************************
	5 - preparation of the signal tree and translate output signals into C, C++, JAVA or LLVM code
	*****************************************************************/
    pair<InstructionsCompiler*, CodeContainer*> comp_container = generateCode(lsignals, numInputs, numOutputs);

    /****************************************************************
     6 - generate xml description, documentation or dot files
    *****************************************************************/
    generateOutputFiles(comp_container.first, comp_container.second);

	return 0;
}
