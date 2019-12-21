/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#ifndef __FAUST_GLOBAL__
#define __FAUST_GLOBAL__

#include <stdio.h>
#include <string.h>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <vector>

#ifndef _WIN32
#include <unistd.h>
#endif

#include "exception.hh"
#include "instructions_type.hh"
#include "loopDetector.hh"
#include "occurrences.hh"
#include "property.hh"
#include "sigtype.hh"
#include "sourcereader.hh"

class CTree;
typedef CTree* Tree;

class Symbol;
typedef Symbol* Sym;

class xtended;
class AudioType;

class Garbageable;

struct DispatchVisitor;
class WASTInstVisitor;
class WASMInstVisitor;
struct TableSizeVisitor;
struct DeclareStructTypeInst;

struct Typed;
struct BasicTyped;

class dsp_factory_base;

typedef long double quad;

struct comp_str {
    bool operator()(Tree s1, Tree s2) const { return (strcmp(tree2str(s1), tree2str(s2)) < 0); }
};

typedef map<Tree, set<Tree>, comp_str> MetaDataSet;

typedef map<Tree, set<Tree>> FunMDSet;  // foo -> {(file/foo/key,value)...}

struct global {
    Tree gResult;
    Tree gResult2;

    SourceReader gReader;

    MetaDataSet gMetaDataSet;
    FunMDSet    gFunMDSet;
    string      gDocLang;
    tvec        gWaveForm;

    //-- globals
    string         gFaustSuperSuperDirectory;
    string         gFaustSuperDirectory;
    string         gFaustDirectory;
    string         gFaustExeDir;
    string         gFaustRootDir;  // abs path to faust root directory
    string         gMasterDocument;
    string         gMasterDirectory;
    string         gMasterName;
    string         gDocName;
    vector<string> gImportDirList;        // dir list enrobage.cpp/fopensearch() searches for imports, etc.
    vector<string> gArchitectureDirList;  // dir list enrobage.cpp/fopensearch() searches for architecture files
    vector<string> gLibraryList;
    string         gOutputDir;
    string         gImportFilename;
    Tree           gExpandedDefList;

    //-- command line arguments
    bool   gDetailsSwitch;
    bool   gDrawSignals;
    bool   gDrawRouteFrame;
    bool   gShadowBlur;      // note: svg2pdf doesn't like the blur filter
    bool   gScaledSVG;       // to draw scaled SVG files
    bool   gStripDocSwitch;  // Strip <mdoc> content from doc listings.
    int    gFoldThreshold;   // global complexity threshold before activating folding
    int    gFoldComplexity;  // individual complexity threshold before folding
    int    gMaxNameSize;
    bool   gSimpleNames;
    bool   gSimplifyDiagrams;
    bool   gLessTempSwitch;
    int    gMaxCopyDelay;
    string gOutputFile;

    bool gVectorSwitch;
    bool gDeepFirstSwitch;
    int  gVecSize;
    int  gVectorLoopVariant;

    bool gOpenMPSwitch;
    bool gOpenMPLoop;
    bool gSchedulerSwitch;
    bool gOpenCLSwitch;
    bool gCUDASwitch;
    bool gGroupTaskSwitch;
    bool gFunTaskSwitch;

    bool gUIMacroSwitch;
    bool gDumpNorm;
    int  gFTZMode;

    int gFloatSize;

    bool gPrintFileListSwitch;
    bool gInlineArchSwitch;

    bool gDSPStruct;
    bool gLightMode;  // do not generate the entire DSP API (to be used with Emscripten to generate a light DSP module
                      // for JavaScript)
    bool gClang;      // when compiled with clang/clang++, adds specific #pragma for auto-vectorization
    bool gCheckTable; // whether to check RDTable and RWTable index range

    string gClassName;       // name of the generated dsp class, by default 'mydsp'
    string gSuperClassName;  // name of the root class the generated dsp class inherits from, by default 'dsp'
    string gProcessName;     // name of the entry point of the Faust program, by default 'process'

    // Backend configuration
    string gOutputLang;            // Chosen backend
    bool   gAllowForeignFunction;  // Can use foreign functions
    bool   gComputeIOTA;           // Cache some computation done with IOTA variable
    bool   gFAUSTFLOATToInternal;  // FAUSTFLOAT type (= kFloatMacro) forced to internal real
    bool   gInPlace;               // Add cache to input for correct in-place computations
    bool   gHasExp10;              // If the 'exp10' math function is available
    bool   gLoopVarInBytes;        // If the 'i' variable used in the scalar loop moves by bytes instead of frames
    bool   gWaveformInDSP;         // If waveform are allocated in the DSP and not as global data
    bool   gUseDefaultSound;       // If default global variable is used in 'soundfile' primitive generation
    bool   gHasTeeLocal;           // For wast/wasm backends
    bool   gFastMath;              // Faster version of some mathematical functions (pow/exp/log)
    bool   gNeedManualPow;         // If manual pow(x, y) generation when y is an integer is needed
    bool   gRemoveVarAddress;      // If used of variable addresses (like &foo or &foo[n]) have to be removed
    bool   gOneSample;             // Generate one sample computation
    bool   gOneSampleControl;      // Generate one sample computation control structure in DSP module
    string gFastMathLib;           // The fastmath code mapping file
    string gNameSpace;             // Wrapping namespace used with the C++ backend

    map<string, string> gFastMathLibTable;      // Mapping table for fastmath functions
    map<string, bool>   gMathForeignFunctions;  // Map of math foreign functions

    dsp_factory_base* gDSPFactory;

    const char* gInputString;

    bool gLstDependenciesSwitch;  ///< mdoc listing management.
    bool gLstMdocTagsSwitch;      ///< mdoc listing management.
    bool gLstDistributedSwitch;   ///< mdoc listing management.

    map<string, string> gDocMetadatasStringMap;
    set<string>         gDocMetadatasKeySet;

    map<string, string> gDocAutodocStringMap;
    set<string>         gDocAutodocKeySet;

    map<string, bool> gDocNoticeFlagMap;

    map<string, string> gDocMathStringMap;

    vector<Tree> gDocVector;  ///< Contains <mdoc> parsed trees: DOCTXT, DOCEQN, DOCDGM.

    map<string, string> gDocNoticeStringMap;
    set<string>         gDocNoticeKeySet;

    set<string> gDocMathKeySet;

    bool gLatexDocSwitch;  // Only LaTeX outformat is handled for the moment.

    int gErrorCount;

    string gErrorMsg;

    Tabber TABBER;

    list<string> gInputFiles;

    int gFileNum;

    int gCountInferences;
    int gCountMaximal;
    int gDummyInput;

    int gBoxSlotNumber;  ///< counter for unique slot number

    bool gMemoryManager;

    bool gLocalCausalityCheck;  ///< when true trigs local causality errors (negative delay)

    bool gCausality;  ///< (FIXME: global used as a parameter of typeAnnotation) when true trigs causality errors
                      ///< (negative delay)

    Tree BOXTYPEPROP;
    Tree NUMERICPROPERTY;
    Tree DEFLINEPROP;
    Tree USELINEPROP;
    Tree SIMPLIFIED;
    Tree DOCTABLES;
    Tree NULLENV;
    Tree COLORPROPERTY;
    Tree ORDERPROP;
    Tree RECURSIVNESS;
    Tree NULLTYPEENV;
    Tree RECDEF;
    Tree DEBRUIJN2SYM;
    Tree DEFNAMEPROPERTY;
    Tree NICKNAMEPROPERTY;
    Tree BCOMPLEXITY;  // Node used for memoization purposes
    Tree LETRECBODY;

    Node PROPAGATEPROPERTY;

    xtended* gAbsPrim;
    xtended* gAcosPrim;
    xtended* gTanPrim;
    xtended* gSqrtPrim;
    xtended* gSinPrim;
    xtended* gRintPrim;
    xtended* gRemainderPrim;
    xtended* gPowPrim;
    xtended* gMinPrim;
    xtended* gMaxPrim;
    xtended* gLogPrim;
    xtended* gLog10Prim;
    xtended* gFmodPrim;
    xtended* gFloorPrim;
    xtended* gExpPrim;
    xtended* gExp10Prim;
    xtended* gCosPrim;
    xtended* gCeilPrim;
    xtended* gAtanPrim;
    xtended* gAtan2Prim;
    xtended* gAsinPrim;
    xtended* gFtzPrim;

    Sym BOXIDENT;
    Sym BOXCUT;
    Sym BOXWAVEFORM;
    Sym BOXROUTE;
    Sym BOXWIRE;
    Sym BOXSLOT;
    Sym BOXSYMBOLIC;
    Sym BOXSEQ;
    Sym BOXPAR;
    Sym BOXREC;
    Sym BOXSPLIT;
    Sym BOXMERGE;
    Sym BOXIPAR;
    Sym BOXISEQ;
    Sym BOXISUM;
    Sym BOXIPROD;
    Sym BOXABSTR;
    Sym BOXAPPL;
    Sym CLOSURE;
    Sym BOXERROR;
    Sym BOXACCESS;
    Sym BOXWITHLOCALDEF;
    Sym BOXMODIFLOCALDEF;
    Sym BOXENVIRONMENT;
    Sym BOXCOMPONENT;
    Sym BOXLIBRARY;
    Sym IMPORTFILE;
    Sym BOXPRIM0;
    Sym BOXPRIM1;
    Sym BOXPRIM2;
    Sym BOXPRIM3;
    Sym BOXPRIM4;
    Sym BOXPRIM5;
    Sym BOXFFUN;
    Sym BOXFCONST;
    Sym BOXFVAR;
    Sym BOXBUTTON;
    Sym BOXCHECKBOX;
    Sym BOXHSLIDER;
    Sym BOXVSLIDER;
    Sym BOXNUMENTRY;
    Sym BOXHGROUP;
    Sym BOXVGROUP;
    Sym BOXTGROUP;
    Sym BOXHBARGRAPH;
    Sym BOXVBARGRAPH;
    Sym BOXCASE;
    Sym BOXPATMATCHER;
    Sym BOXPATVAR;
    Sym BOXINPUTS;
    Sym BOXOUTPUTS;
    Sym BOXSOUNDFILE;
    Sym BOXMETADATA;
    Sym DOCEQN;
    Sym DOCDGM;
    Sym DOCNTC;
    Sym DOCLST;
    Sym DOCMTD;
    Sym DOCTXT;
    Sym BARRIER;

    property<bool>* gPureRoutingProperty;
    property<Tree>* gSymbolicBoxProperty;

    Node EVALPROPERTY;
    Node PMPROPERTYNODE;

    property<Tree>* gSimplifiedBoxProperty;

    Sym UIFOLDER;
    Sym UIWIDGET;

    Sym PATHROOT;
    Sym PATHPARENT;
    Sym PATHCURRENT;

    Sym FFUN;

    // the property used to memoize the results
    property<Tree>* gSymListProp;

    Sym SIGINPUT;
    Sym SIGOUTPUT;
    Sym SIGDELAY1;
    Sym SIGFIXDELAY;
    Sym SIGPREFIX;
    Sym SIGIOTA;
    Sym SIGRDTBL;
    Sym SIGWRTBL;
    Sym SIGTABLE;
    Sym SIGGEN;
    Sym SIGDOCONSTANTTBL;
    Sym SIGDOCWRITETBL;
    Sym SIGDOCACCESSTBL;
    Sym SIGSELECT2;
    Sym SIGSELECT3;
    Sym SIGBINOP;
    Sym SIGFFUN;
    Sym SIGFCONST;
    Sym SIGFVAR;
    Sym SIGPROJ;
    Sym SIGINTCAST;
    Sym SIGFLOATCAST;
    Sym SIGBUTTON;
    Sym SIGCHECKBOX;
    Sym SIGWAVEFORM;
    Sym SIGHSLIDER;
    Sym SIGVSLIDER;
    Sym SIGNUMENTRY;
    Sym SIGHBARGRAPH;
    Sym SIGVBARGRAPH;
    Sym SIGATTACH;
    Sym SIGENABLE;
    Sym SIGCONTROL;
    Sym SIGSOUNDFILE;
    Sym SIGSOUNDFILELENGTH;
    Sym SIGSOUNDFILERATE;
    Sym SIGSOUNDFILEBUFFER;
    Sym SIGTUPLE;
    Sym SIGTUPLEACCESS;

    Sym SIMPLETYPE;
    Sym TABLETYPE;
    Sym TUPLETTYPE;

    // Memoized type contruction
    property<AudioType*>* gMemoizedTypes;

    // The map of types and associated Structured types
    map<Typed::VarType, DeclareStructTypeInst*> gExternalStructTypes;

    // Essential predefined types
    Type TINT;
    Type TREAL;

    Type TKONST;
    Type TBLOCK;
    Type TSAMP;

    Type TCOMP;
    Type TINIT;
    Type TEXEC;

    // More predefined types
    Type TINPUT;
    Type TGUI;
    Type TGUI01;
    Type INT_TGUI;

    // Trying to accelerate type convergence
    Type TREC;  // kVect ou kScal ?

    Sym  CONS;
    Sym  NIL;
    Tree nil;

    Sym PROCESS;

    Sym DEBRUIJN;
    Sym DEBRUIJNREF;
    Sym SUBSTITUTE;

    Sym SYMREC;
    Sym SYMRECREF;
    Sym SYMLIFTN;

    loopDetector          gLoopDetector;
    stackOverflowDetector gStackOverflowDetector;

    string gDrawPath;

    int gMachineFloatSize;
    int gMachineInt32Size;
    int gMachineInt64Size;
    int gMachineDoubleSize;
    int gMachineBoolSize;
    int gMachinePtrSize;

    int gMachineMaxStackSize;

    const char* gDocDevSuffix;  ///< ".tex" (or .??? - used to choose output device).
    string      gCurrentDir;    ///< Room to save current directory name.
    string      gLatexheaderfilename;

    struct tm gCompilationDate;

    map<string, int> gIDCounters;

    string gDocTextsDefaultFile;

    // internal state during drawing
    Occurrences*      gOccurrences;
    bool              gFoldingFlag;     // true with complex block-diagrams
    stack<Tree>       gPendingExp;      // Expressions that need to be drawn
    set<Tree>         gDrawnExp;        // Expressions drawn or scheduled so far
    const char*       gDevSuffix;       // .svg or .ps used to choose output device
    string            gSchemaFileName;  // name of schema file beeing generated
    map<Tree, string> gBackLink;        // link to enclosing file for sub schema

    // FIR
    map<Typed::VarType, BasicTyped*> gTypeTable;     // To share a unique BasicTyped* object for a given type
    map<string, Typed*>              gVarTypeTable;  // Types of variables or functions
    map<Typed::VarType, int>         gTypeSizeMap;   // Size of types in bytes

    // colorize
    map<Tree, int> gColorMap;
    int            gNextFreeColor;

    // to keep track of already injected files
    set<string> gAlreadyIncluded;

    char* gCurrentLocal;

    int gAllocationCount;  // Internal signal types counter

    bool gEnableFlag;

#ifdef WASM_BUILD
    // One single global visitor for WebAssembly, so that sub-containers and the global container use the same heap
    WASMInstVisitor* gWASMVisitor;
    WASTInstVisitor* gWASTVisitor;
#endif

#ifdef INTERP_BUILD
    // One single global visitor Interpreter backend, so that sub-containers and the global container use the same heap
    DispatchVisitor* gInterpreterVisitor;
#endif

#ifdef SOUL_BUILD
    TableSizeVisitor* gTableSizeVisitor;
#endif

    bool gHelpSwitch;
    bool gVersionSwitch;
    bool gLibDirSwitch;
    bool gIncludeDirSwitch;
    bool gArchDirSwitch;
    bool gDspDirSwitch;
    bool gPathListSwitch;

    bool   gGraphSwitch;
    bool   gDrawPSSwitch;
    bool   gDrawSVGSwitch;
    bool   gPrintXMLSwitch;
    bool   gPrintJSONSwitch;
    bool   gPrintDocSwitch;
    int    gBalancedSwitch;
    string gArchFile;
    bool   gExportDSP;

    // Source file injection
    bool   gInjectFlag;
    string gInjectFile;

    int gTimeout;  // Time out to abort compiler (in seconds)

    // Globals to transfer results in thread based evaluation
    Tree   gProcessTree;
    Tree   gLsignalsTree;
    int    gNumInputs;
    int    gNumOutputs;
    string gErrorMessage;

    // GC
    static list<Garbageable*> gObjectTable;
    static bool               gHeapCleanup;

    global();
    ~global();

    void init();

    static void allocate();
    static void destroy();

    string getFreshID(const string& prefix);

    string makeDrawPath();
    string makeDrawPathNoExt();

    string getMathFunction(const string& name)
    {
        if (gFastMath && (gFastMathLibTable.find(name) != gFastMathLibTable.end())) {
            return gFastMathLibTable[name];
        } else {
            return name;
        }
    }

    bool hasVarType(const string& name) { return gVarTypeTable.find(name) != gVarTypeTable.end(); }

    Typed::VarType getVarType(const string& name) { return gVarTypeTable[name]->getType(); }

    bool isMathForeignFunction(const string& name)
    {
        return (gMathForeignFunctions.find(name) != gMathForeignFunctions.end());
    }

    void printCompilationOptions(ostream& dst, bool backend = true);

    void initTypeSizeMap();

    int audioSampleSize();
};

// Unique shared global pointer
extern global* gGlobal;

#define FAUST_LIB_PATH "FAUST_LIB_PATH"
#define MAX_MACHINE_STACK_SIZE 65536
#define MAX_SOUNDFILE_PARTS 256

#endif
