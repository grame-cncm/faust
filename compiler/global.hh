/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
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

#include "smartpointer.hh"
#include "exception.hh"
#include "instructions_type.hh"
#include "loopDetector.hh"
#include "property.hh"
#include "sourcereader.hh"

class Occur;

class AudioType;
typedef P<AudioType> Type;

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
class JAXInstVisitor;
class JuliaInstVisitor;
class JSFXInstVisitor;
class TemplateInstVisitor;
class CodeboxInstVisitor;
struct TableSizeVisitor;
struct DeclareStructTypeInst;

struct Typed;
struct BasicTyped;

struct dsp_factory_base;

struct comp_str {
    bool operator()(Tree s1, Tree s2) const { return (strcmp(tree2str(s1), tree2str(s2)) < 0); }
};

typedef std::map<Tree, std::set<Tree>, comp_str> MetaDataSet;
typedef std::map<Tree, std::set<Tree>>           FunMDSet;  // foo -> {(file/foo/key,value)...}

// Global outside of the global context
extern std::vector<std::string> gWarningMessages;
extern bool           gAllWarning;

// Global singleton like compiler state
struct global {
    // Parsing
    SourceReader gReader;
    Tree         gExpandedDefList;
    std::string            gInputString;
    std::list<std::string> gInputFiles;
    tvec         gWaveForm;  // used in the parser to keep values parsed for a given waveform
    Tree         gResult;

    // Metadata handling
    MetaDataSet gMetaDataSet;
    FunMDSet    gFunMDSet;

    // File handling
    std::string gFaustSuperSuperDirectory;
    std::string gFaustSuperDirectory;
    std::string gFaustDirectory;
    std::string gFaustExeDir;
    std::string gFaustRootDir;  // abs path to Faust root directory
    std::string gMasterDocument;
    std::string gMasterDirectory;
    std::string gMasterName;
    std::vector<std::string> gImportDirList;        // dir list enrobage.cpp/fopensearch() searches for imports, etc.
    std::vector<std::string> gArchitectureDirList;  // dir list enrobage.cpp/fopensearch() searches for architecture files
    std::vector<std::string> gLibraryList;
    std::string         gOutputDir;
    std::string         gImportFilename;
    std::string         gOutputFile;
    std::string         gArchFile;         // -a option
    std::set<std::string>    gAlreadyIncluded;  // to keep track of already injected files

    // compilation options
    bool gDetailsSwitch;         // -d option
    bool gDrawSignals;           // -sg option
    bool gDrawRouteFrame;        // -drf option
    bool gShadowBlur;            // -blur option, note: svg2pdf doesn't like the blur filter
    bool gScaledSVG;             // -sc option, to draw scaled SVG files
    bool gStripDocSwitch;        // -stripmdoc option, Strip <mdoc> content from doc listings
    int  gFoldThreshold;         // -f option, global complexity threshold before activating folding
    int  gFoldComplexity;        // -fc option, individual complexity threshold before folding
    int  gMaxNameSize;           // -mns option
    bool gSimpleNames;           // -sn option
    bool gSimplifyDiagrams;      // -sd option
    bool gPrintFileListSwitch;   // -flist option
    bool gInlineArchSwitch;      // -i option
    bool gUIMacroSwitch;         // -uim option
    int  gDumpNorm;              // -norm option
    bool gMathExceptions;        // -me option, whether to check math functions domains
    bool gLocalCausalityCheck;   // -lcc option, when true trigs local causality errors (negative delay)
    bool gGraphSwitch;           // -tg option
    bool gDrawPSSwitch;          // -ps option
    bool gDrawSVGSwitch;         // -svg option
    bool gVHDLSwitch;            // -vhdl option
    bool gVHDLTrace;             // -vhdl-trace option
    int  gVHDLFloatType;         // -vhdl-type 0: sfixed(msb downto lsb) or 1: float(msb downto lsb)
    int  gVHDLFloatMSB;          // -vhdl-msb option
    int  gVHDLFloatLSB;          // -vhdl-lsb option
    int  gFPGAMemory;            // -fpga-mem option: FPGA block ram max size
    bool gPrintXMLSwitch;        // -xml option
    bool gPrintJSONSwitch;       // -json option
    bool gPrintDocSwitch;        // -mdoc option
    bool gExportDSP;             // -e option
  
    // code generation options
    bool gVectorSwitch;          // -vec option
    bool gDeepFirstSwitch;       // -dfs option
    int  gVecSize;               // -vs option
    int  gVectorLoopVariant;     // -lv [0|1] option
    bool gOpenMPSwitch;          // -omp option
    bool gOpenMPLoop;            // -pl option
    bool gSchedulerSwitch;       // -sch option
    bool gOpenCLSwitch;          // -ocl option
    bool gCUDASwitch;            // -cuda option
    bool gGroupTaskSwitch;       // -g option
    bool gFunTaskSwitch;         // -fun option
    int gMaxCopyDelay;           // -mcd option
    int gFloatSize;              // -single/double/quad/fx option (1 for 'float', 2 for 'double', 3 for 'quad', 4 for 'fixed-point')
    int gMaskDelayLineThreshold; // -dlt <num> power-of-two and mask delay-lines treshold
    bool gEnableFlag;            // -es option (0/1: 0 by default)
    bool gNoVirtual;             // -nvi option, when compiled with the C++ backend, does not add the 'virtual' keyword
    bool gMemoryManager;         // -mem option
    bool gRangeUI;               // -rui option, whether to generate code to limit vslider/hslider/nentry values in [min..max] range
    bool gFreezeUI;              // -fui option, whether to freeze vslider/hslider/nentry to a given value (init value by default)
    int  gFTZMode;               // -ftz option, 0 = no (default), 1 = fabs based, 2 = mask based (fastest)
    bool gInPlace;               // -inpl option, add cache to input for correct in-place computations
    bool gStrictSelect;          // -sts option, generate strict code for 'selectX' even for stateless branches (both are computed)
    
    bool gDSPStruct;             // to control method generation in -fun mode
    bool gLightMode;             // -light option, do not generate the entire DSP API (to be used with Emscripten to generate a light DSP module for JavaScript)
    bool gClang;                 // -clang opttion, when compiled with clang/clang++, adds specific #pragma for auto-vectorization
    bool gFullParentheses;       // -fp option, generate less parenthesis in some textual backends: C/C++, Cmajor, Dlang, Rust
    bool gCheckIntRange;         // -cir option, check float to integer range conversion
    bool gReprC;                 // (Rust) Force dsp struct layout to follow C ABI

    std::string gClassName;      // -cn option, name of the generated dsp class, by default 'mydsp'
    std::string gProcessName;    // -pn option, name of the entry point of the Faust program, by default 'process'
    std::string gSuperClassName; // -scn option, name of the root class the generated dsp class inherits from, by default 'dsp'
    
    // Debug option
    bool gCheckTable;            // -ct to check rtable/rwtable index range and generate safe access code (0/1: 1 by default)

    // Backend configuration
    std::string gOutputLang;       // Chosen backend
    bool   gAllowForeignFunction;  // Can use foreign functions
    bool   gAllowForeignConstant;  // Can use foreign constant
    bool   gAllowForeignVar;       // Can use foreign variable
    bool   gComputeIOTA;           // Cache some computation done with IOTA variable
    bool   gFAUSTFLOAT2Internal;   // FAUSTFLOAT type (= kFloatMacro) forced to internal real
    bool   gHasExp10;              // -exp10, if the 'exp10' math function is available
    bool   gLoopVarInBytes;        // If the 'i' variable used in the scalar loop moves by bytes instead of frames
    bool   gUseMemmove;            // Use 'memmove' function to shift arrays
    bool   gWaveformInDSP;         // If waveform are allocated in the DSP and not as global data
    bool   gUseDefaultSound;       // If default global variable is used in 'soundfile' primitive generation
    bool   gHasTeeLocal;           // For wast/wasm backends
    std::string gFastMathLib;      // -fm faster version of some mathematical functions (pow/exp/log), the fastmath code mapping file
    bool   gMathApprox;            // -mapp option, simpler/faster versions of 'floor/fmod/remainder' functions
    bool   gNeedManualPow;         // If manual pow(x, y) generation when y is an integer is needed
    bool   gRemoveVarAddress;      // If use of variable addresses (like &foo or &foo[n]) have to be removed
    int    gOneSample;             // -osX options, generate one sample computation
    bool   gOneSampleControl;      // -osX options, generate one sample computation control structure in DSP module
    bool   gInlineTable;           // -it option, only in -cpp backend, to inline rdtable/rwtable code in the main class.
    bool   gComputeMix;            // -cm option, mix in outputs buffers
    bool   gBool2Int;              // Cast bool binary operations (comparison operations) to int
    std::string gNamespace;        // Wrapping namespace used with the C++ backend

    int gWideningLimit;   // Max number of iterations before interval widening
    int gNarrowingLimit;  // Max number of iterations to compute interval widener

    std::map<std::string, std::string> gFastMathLibTable;      // Mapping table for fastmath functions
    std::map<std::string, bool>        gMathForeignFunctions;  // Map of math foreign functions

    dsp_factory_base* gDSPFactory;  // compiled factory

    bool gLstDependenciesSwitch;  // mdoc listing management
    bool gLstMdocTagsSwitch;      // mdoc listing management
    bool gLstDistributedSwitch;   // mdoc listing management

    // Automatic documentation
    std::string         gDocLang;
    std::string         gDocName;
    std::map<std::string, std::string>  gDocMetadatasStringMap;
    std::set<std::string>               gDocMetadatasKeySet;
    std::map<std::string, std::string>  gDocAutodocStringMap;
    std::set<std::string>               gDocAutodocKeySet;
    std::map<std::string, bool>         gDocNoticeFlagMap;
    std::map<std::string, std::string>  gDocMathStringMap;
    std::vector<Tree>                   gDocVector;     //< Contains <mdoc> parsed trees: DOCTXT, DOCEQN, DOCDGM
    std::map<std::string, std::string>  gDocNoticeStringMap;
    std::set<std::string>               gDocNoticeKeySet;
    std::set<std::string>               gDocMathKeySet;
    const char*         gDocDevSuffix;   //< ".tex" (or .??? - used to choose output device)
    std::string         gCurrentDir;     //< Room to save current directory name
    std::string         gLatexheaderfilename;
    struct tm           gCompilationDate;
    int                 gFileNum;
    bool                gLatexDocSwitch;  // Only LaTeX outformat is handled for the moment
    std::string         gDocTextsDefaultFile;

    // Error handling
    int gErrorCount;
    std::string gErrorMessage;
    Tabber TABBER;

    // ------------
    // boxppShared
    // ------------
    // Tree is used to identify the same nodes during Box tree traversal,
    // but gBoxCounter is then used to generate unique IDs
    std::map<Tree, std::pair<int, std::string>> gBoxTable;
    int                                         gBoxCounter;
    // To keep the box tree traversing trace
    std::vector<std::string> gBoxTrace;

    // ------------
    // ppsigShared
    // ------------
    // Tree is used to identify the same nodes during Signal tree traversal,
    // but gSignalCounter is then used to generate unique IDs
    std::map<Tree, std::pair<int, std::string>> gSignalTable;
    int                                         gSignalCounter;
    // To keep the signal tree traversing trace
    std::vector<std::string> gSignalTrace;

    // Typing
    int gCountInferences;
    int gCountMaximal;
    int gAllocationCount;  // Internal signal types counter

    // Used in propagation
    int gDummyInput;

    // Used in eval
    int gBoxSlotNumber;  // counter for unique slot number

    bool gCausality;  // FIXME: global used as a parameter of typeAnnotation when true trigs causality errors (negative
                      // delay)

    // Properties
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
    Tree NORMALFORM;
    Tree DEFNAMEPROPERTY;
    Tree NICKNAMEPROPERTY;
    Tree BCOMPLEXITY;  // Node used for memoization purposes
    Tree LETRECBODY;
    Node PROPAGATEPROPERTY;
    
    // Extended math
    xtended* gAbsPrim;
    xtended* gAcosPrim;
    xtended* gTanPrim;
    xtended* gSqrtPrim;
    xtended* gSinPrim;
    xtended* gRintPrim;
    xtended* gRoundPrim;
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
 
    // Signals
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
    // Used in environment layering
    Sym BARRIER;

    property<bool>* gPureRoutingProperty;
    property<Tree>* gSymbolicBoxProperty;

    Node EVALPROPERTY;
    Node PMPROPERTYNODE;

    property<Tree>* gSimplifiedBoxProperty;

    // The property used to memoize the results
    property<Tree>* gSymListProp;

    // Memoized type contruction
    property<AudioType*>* gMemoizedTypes;

    // Symbols
    Sym UIFOLDER;
    Sym UIWIDGET;
    Sym PATHROOT;
    Sym PATHPARENT;
    Sym PATHCURRENT;
    Sym FFUN;
    Sym SIGINPUT;
    Sym SIGOUTPUT;
    Sym SIGDELAY1;
    Sym SIGDELAY;
    Sym SIGPREFIX;
    Sym SIGRDTBL;
    Sym SIGWRTBL;
    Sym SIGGEN;
    Sym SIGDOCONSTANTTBL;
    Sym SIGDOCWRITETBL;
    Sym SIGDOCACCESSTBL;
    Sym SIGSELECT2;
    Sym SIGASSERTBOUNDS;
    Sym SIGHIGHEST;
    Sym SIGLOWEST;
    Sym SIGBINOP;
    Sym SIGFFUN;
    Sym SIGFCONST;
    Sym SIGFVAR;
    Sym SIGPROJ;
    Sym SIGINTCAST;
    Sym SIGBITCAST;
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

    // Types
    Sym SIMPLETYPE;
    Sym TABLETYPE;
    Sym TUPLETTYPE;

    // The map of types and associated Structured types
    std::map<Typed::VarType, DeclareStructTypeInst*> gExternalStructTypes;

    // Essential predefined types
    Type TINPUT;
    Type TGUI;
  
    // Trying to accelerate type convergence
    Type TREC;  // kVect ou kScal ?
    Type TRECMAX;

    // Predefined symbols CONS and NIL
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

    // Evaluation overflow
    loopDetector          gLoopDetector;
    stackOverflowDetector gStackOverflowDetector;

    int gMachineFloatSize;
    int gMachineInt32Size;
    int gMachineInt64Size;
    int gMachineDoubleSize;
    int gMachineQuadSize;
    int gMachineFixedPointSize;
    int gMachineBoolSize;
    int gMachinePtrSize;

    int gMachineMaxStackSize;

    // To generate unique identifiers
    std::map<std::string, int> gIDCounters;

    // Internal state during drawing
    Occur*            gOccurrences;
    bool              gFoldingFlag;     // true with complex block-diagrams
    std::stack<Tree>  gPendingExp;      // Expressions that need to be drawn
    std::set<Tree>    gDrawnExp;        // Expressions drawn or scheduled so far
    const char*        gDevSuffix;       // .svg or .ps used to choose output device
    std::string       gSchemaFileName;  // name of schema file beeing generated
    Tree              gInverter[6];
    std::map<Tree, std::string> gBackLink;  // link to enclosing file for sub schema

    // FIR
    std::map<Typed::VarType, BasicTyped*> gTypeTable;     // To share a unique BasicTyped* object for a given type
    std::map<std::string, Typed*>         gVarTypeTable;  // Types of variables or functions
    std::map<Typed::VarType, int>         gTypeSizeMap;   // Size of types in bytes
    std::map<std::string, std::pair<std::string, int>>   gTablesSize;    // Global tables size in bytes: class name, <table name, size>

    // Colorize
    std::map<Tree, int> gColorMap;
    int gNextFreeColor;

    // To keep current local
    char* gCurrentLocal;

#ifdef WASM_BUILD
    // One single global visitor for WebAssembly, so that sub-containers and the global container use the same heap
    WASMInstVisitor* gWASMVisitor;
    WASTInstVisitor* gWASTVisitor;
#endif

#if defined(INTERP_BUILD) || defined(INTERP_COMP_BUILD)
    // One single global visitor Interpreter backend, so that sub-containers and the global container use the same heap
    DispatchVisitor* gInterpreterVisitor;
#endif

#ifdef JULIA_BUILD
    // One single global visitor Julia backend, so that sub-containers and the global container use the same heap
    JuliaInstVisitor* gJuliaVisitor;
#endif

#ifdef JSFX_BUILD
    // One single global visitor JSFX backend, so that sub-containers and the global container use the same heap
    JSFXInstVisitor* gJSFXVisitor;
#endif

#ifdef CMAJOR_BUILD
    TableSizeVisitor* gTableSizeVisitor;
#endif

#ifdef JAX_BUILD
    JAXInstVisitor* gJAXVisitor;
#endif

#ifdef TEMPLATE_BUILD
    TemplateInstVisitor* gTemplateVisitor;
#endif
    
#ifdef CODEBOX_BUILD
    CodeboxInstVisitor* gCodeboxVisitor;
#endif

    // Info on the compiler
    bool gHelpSwitch;
    bool gVersionSwitch;
    bool gLibDirSwitch;
    bool gIncludeDirSwitch;
    bool gArchDirSwitch;
    bool gDspDirSwitch;
    bool gPathListSwitch;

    // Source file injection
    bool gInjectFlag;
    std::string gInjectFile;

    int gTimeout;  // Time out to abort compiler (in seconds)

    // Garbage collection
    static std::list<Garbageable*> gObjectTable;
    static bool                    gHeapCleanup;

    global();
    ~global();

    // Done after contructor since part of the following allocations need the "global" object to be fully built
    void init();

    // Part of the state that needs to be initialized between consecutive calls to Box/Signal API
    void reset();

    // For box/sig generation
    void clear();

    static void allocate();
    static void destroy();

    std::string printFloat();

    std::string getFreshID(const std::string& prefix);

    std::string makeDrawPath();
    std::string makeDrawPathNoExt();

    std::string getMathFunction(const std::string& name)
    {
        if (gFastMathLib != "" && (gFastMathLibTable.find(name) != gFastMathLibTable.end())) {
            return gFastMathLibTable[name];
        } else {
            return name;
        }
    }

    bool hasVarType(const std::string& name) { return gVarTypeTable.find(name) != gVarTypeTable.end(); }

    BasicTyped* genBasicTyped(Typed::VarType type);

    Typed::VarType getVarType(const std::string& name);

    void setVarType(const std::string& name, Typed::VarType type);

    inline bool startWith(const std::string& str, const std::string& prefix) { return (str.substr(0, prefix.size()) == prefix); }

    // Some backends have an internal implementation of foreign functions like acos, asinh...
    bool hasForeignFunction(const std::string& name, const std::string& inc_file);

    void printCompilationOptions(std::stringstream& dst, bool backend = true);
    std::string printCompilationOptions1();

    void initTypeSizeMap();

    int audioSampleSize();

    // Allows to test if a given debug environment variable is set
    static bool isDebug(const std::string& debug_val);
    
    bool processCmdline(int argc, const char* argv[]);
    void initDocumentNames();
    void initDirectories(int argc, const char* argv[]);
    void printDeclareHeader(std::ostream& dst);
    void parseSourceFiles();
    
    void printLibDir();
    void printIncludeDir();
    void printArchDir();
    void printDspDir();
    void printPaths();
    
    void printDirectories();
};

// Unique shared global pointer
extern global* gGlobal;

#define FAUST_LIB_PATH "FAUST_LIB_PATH"
#define MAX_MACHINE_STACK_SIZE 65536 * 16
#define MAX_SOUNDFILE_PARTS 256

#define MAX_ERROR_SIZE 192

// Threaded calls API
typedef void* (*threaded_fun)(void* arg);
void callFun(threaded_fun fun, void* arg);

// Used to pass parameters and possibly return a result
struct CallContext {
    std::string fNameApp = "";
    std::string fDSPContent = "";
    int fArgc = 0;
    const char** fArgv = nullptr;
    bool fGenerate = false;
    int fNumInputs = -1;
    int fNumOutputs = -1;
    Tree fTree = nullptr;   // Used for in/out
    std::string fRes = "";  // Used for out
};

#endif
