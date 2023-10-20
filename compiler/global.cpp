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

#include <limits.h>
#include <cstdint>

#include "absprim.hh"
#include "acosprim.hh"
#include "asinprim.hh"
#include "atan2prim.hh"
#include "atanprim.hh"
#include "binop.hh"
#include "ceilprim.hh"
#include "cosprim.hh"
#include "exp10prim.hh"
#include "expprim.hh"
#include "floats.hh"
#include "floorprim.hh"
#include "fmodprim.hh"
#include "global.hh"
#include "instructions.hh"
#include "log10prim.hh"
#include "logprim.hh"
#include "maxprim.hh"
#include "minprim.hh"
#include "powprim.hh"
#include "remainderprim.hh"
#include "rintprim.hh"
#include "roundprim.hh"
#include "sinprim.hh"
#include "sourcereader.hh"
#include "sqrtprim.hh"
#include "tanprim.hh"
#include "tree.hh"
#include "occur.hh"
#include "enrobage.hh"
#include "exepath.hh"
#include "timing.hh"

#ifdef WIN32
#pragma warning(disable : 4996)
#endif

#ifdef C_BUILD
#include "c_code_container.hh"
#endif

#ifdef CODEBOX_BUILD
#include "codebox_code_container.hh"
#endif

#ifdef CPP_BUILD
#include "cpp_code_container.hh"
#include "cpp_gpu_code_container.hh"
#endif

#ifdef CSHARP_BUILD
#include "csharp_code_container.hh"
#endif

#ifdef FIR_BUILD
#include "fir_code_container.hh"
#endif

#ifdef LLVM_BUILD
#include "llvm_dsp_aux.hh"
#endif

#ifdef INTERP_BUILD
#include "interpreter_instructions.hh"
#endif

#ifdef JAVA_BUILD
#include "java_code_container.hh"
#endif

#ifdef RUST_BUILD
#include "rust_code_container.hh"
#endif

#ifdef DLANG_BUILD
#include "dlang_code_container.hh"
#endif

#ifdef JULIA_BUILD
#include "julia_code_container.hh"
#endif

#ifdef JSFX_BUILD
#include "jsfx_code_container.hh"
#endif

#ifdef JAX_BUILD
#include "jax_code_container.hh"
#endif

#ifdef TEMPLATE_BUILD
#include "template_code_container.hh"
#endif

using namespace std;

// Globals for flex/bison parser
extern FILE*       FAUSTin;
extern const char* FAUSTfilename;

// Garbageable globals
list<Garbageable*> global::gObjectTable;
bool               global::gHeapCleanup = false;

global::global() : TABBER(1), gLoopDetector(1024, 400), gStackOverflowDetector(MAX_STACK_SIZE), gNextFreeColor(1)
{
    CTree::init();
    Symbol::init();
 
    // Part of the state that needs to be initialized between consecutive calls to Box/Signal API
    reset();

    EVALPROPERTY   = symbol("EvalProperty");
    PMPROPERTYNODE = symbol("PMPROPERTY");

    // Fastmath mapping float version
    gFastMathLibTable["fabsf"]      = "fast_fabsf";
    gFastMathLibTable["acosf"]      = "fast_acosf";
    gFastMathLibTable["asinf"]      = "fast_asinf";
    gFastMathLibTable["atanf"]      = "fast_atanf";
    gFastMathLibTable["atan2f"]     = "fast_atan2f";
    gFastMathLibTable["ceilf"]      = "fast_ceilf";
    gFastMathLibTable["cosf"]       = "fast_cosf";
    gFastMathLibTable["expf"]       = "fast_expf";
    gFastMathLibTable["exp2f"]      = "fast_exp2f";
    gFastMathLibTable["exp10f"]     = "fast_exp10f";
    gFastMathLibTable["floorf"]     = "fast_floorf";
    gFastMathLibTable["fmodf"]      = "fast_fmodf";
    gFastMathLibTable["logf"]       = "fast_logf";
    gFastMathLibTable["log2f"]      = "fast_log2f";
    gFastMathLibTable["log10f"]     = "fast_log10f";
    gFastMathLibTable["powf"]       = "fast_powf";
    gFastMathLibTable["remainderf"] = "fast_remainderf";
    gFastMathLibTable["rintf"]      = "fast_rintf";
    gFastMathLibTable["roundf"]     = "fast_roundf";
    gFastMathLibTable["sinf"]       = "fast_sinf";
    gFastMathLibTable["sqrtf"]      = "fast_sqrtf";
    gFastMathLibTable["tanf"]       = "fast_tanf";

    // Fastmath mapping double version
    gFastMathLibTable["fabs"]      = "fast_fabs";
    gFastMathLibTable["acos"]      = "fast_acos";
    gFastMathLibTable["asin"]      = "fast_asin";
    gFastMathLibTable["atan"]      = "fast_atan";
    gFastMathLibTable["atan2"]     = "fast_atan2";
    gFastMathLibTable["ceil"]      = "fast_ceil";
    gFastMathLibTable["cos"]       = "fast_cos";
    gFastMathLibTable["exp"]       = "fast_exp";
    gFastMathLibTable["exp2"]      = "fast_exp2";
    gFastMathLibTable["exp10"]     = "fast_exp10";
    gFastMathLibTable["floor"]     = "fast_floor";
    gFastMathLibTable["fmod"]      = "fast_fmod";
    gFastMathLibTable["log"]       = "fast_log";
    gFastMathLibTable["log2"]      = "fast_log2";
    gFastMathLibTable["log10"]     = "fast_log10";
    gFastMathLibTable["pow"]       = "fast_pow";
    gFastMathLibTable["remainder"] = "fast_remainder";
    gFastMathLibTable["rint"]      = "fast_rint";
    gFastMathLibTable["round"]     = "fast_round";
    gFastMathLibTable["sin"]       = "fast_sin";
    gFastMathLibTable["sqrt"]      = "fast_sqrt";
    gFastMathLibTable["tan"]       = "fast_tan";
    
    // Fastmath mapping quad version
    gFastMathLibTable["fabsl"]      = "fast_fabs";
    gFastMathLibTable["acosl"]      = "fast_acos";
    gFastMathLibTable["asinl"]      = "fast_asin";
    gFastMathLibTable["atanl"]      = "fast_atan";
    gFastMathLibTable["atan2l"]     = "fast_atan2";
    gFastMathLibTable["ceill"]      = "fast_ceil";
    gFastMathLibTable["cosl"]       = "fast_cos";
    gFastMathLibTable["expl"]       = "fast_exp";
    gFastMathLibTable["exp2l"]      = "fast_exp2";
    gFastMathLibTable["exp10l"]     = "fast_exp10";
    gFastMathLibTable["floorl"]     = "fast_floor";
    gFastMathLibTable["fmodl"]      = "fast_fmod";
    gFastMathLibTable["logl"]       = "fast_log";
    gFastMathLibTable["log2l"]      = "fast_log2";
    gFastMathLibTable["log10l"]     = "fast_log10";
    gFastMathLibTable["powl"]       = "fast_pow";
    gFastMathLibTable["remainderl"] = "fast_remainder";
    gFastMathLibTable["rintl"]      = "fast_rint";
    gFastMathLibTable["roundl"]     = "fast_round";
    gFastMathLibTable["sinl"]       = "fast_sin";
    gFastMathLibTable["sqrtl"]      = "fast_sqrt";
    gFastMathLibTable["tanl"]       = "fast_tan";
    
    // Fastmath mapping fx version
    gFastMathLibTable["fabsfx"]      = "fast_fabs";
    gFastMathLibTable["acosfx"]      = "fast_acos";
    gFastMathLibTable["asinfx"]      = "fast_asin";
    gFastMathLibTable["atanfx"]      = "fast_atan";
    gFastMathLibTable["atan2fx"]     = "fast_atan2";
    gFastMathLibTable["ceilfx"]      = "fast_ceil";
    gFastMathLibTable["cosfx"]       = "fast_cos";
    gFastMathLibTable["expfx"]       = "fast_exp";
    gFastMathLibTable["exp2fx"]      = "fast_exp2";
    gFastMathLibTable["exp10fx"]     = "fast_exp10";
    gFastMathLibTable["floorfx"]     = "fast_floor";
    gFastMathLibTable["fmodfx"]      = "fast_fmod";
    gFastMathLibTable["logfx"]       = "fast_log";
    gFastMathLibTable["log2fx"]      = "fast_log2";
    gFastMathLibTable["log10fx"]     = "fast_log10";
    gFastMathLibTable["powfx"]       = "fast_pow";
    gFastMathLibTable["remainderfx"] = "fast_remainder";
    gFastMathLibTable["rintfx"]      = "fast_rint";
    gFastMathLibTable["roundfx"]     = "fast_round";
    gFastMathLibTable["sinfx"]       = "fast_sin";
    gFastMathLibTable["sqrtfx"]      = "fast_sqrt";
    gFastMathLibTable["tanfx"]       = "fast_tan";

    gAbsPrim       = new AbsPrim();
    gAcosPrim      = new AcosPrim();
    gTanPrim       = new TanPrim();
    gSqrtPrim      = new SqrtPrim();
    gSinPrim       = new SinPrim();
    gRintPrim      = new RintPrim();
    gRoundPrim     = new RoundPrim();
    gRemainderPrim = new RemainderPrim();
    gPowPrim       = new PowPrim();
    gMinPrim       = new MinPrim();
    gMaxPrim       = new MaxPrim();
    gLogPrim       = new LogPrim();
    gLog10Prim     = new Log10Prim();
    gFmodPrim      = new FmodPrim();
    gFloorPrim     = new FloorPrim();
    gExpPrim       = new ExpPrim();
    gExp10Prim     = new Exp10Prim();
    gCosPrim       = new CosPrim();
    gCeilPrim      = new CeilPrim();
    gAtanPrim      = new AtanPrim();
    gAtan2Prim     = new Atan2Prim();
    gAsinPrim      = new AsinPrim();
  
    BOXIDENT         = symbol("BoxIdent");
    BOXCUT           = symbol("BoxCut");
    BOXWAVEFORM      = symbol("BoxWaveform");
    BOXROUTE         = symbol("BoxRoute");
    BOXWIRE          = symbol("BoxWire");
    BOXSLOT          = symbol("BoxSlot");
    BOXSYMBOLIC      = symbol("BoxSymbolic");
    BOXSEQ           = symbol("BoxSeq");
    BOXPAR           = symbol("BoxPar");
    BOXREC           = symbol("BoxRec");
    BOXSPLIT         = symbol("BoxSplit");
    BOXMERGE         = symbol("BoxMerge");
    BOXIPAR          = symbol("BoxIPar");
    BOXISEQ          = symbol("BoxISeq");
    BOXISUM          = symbol("BoxISum");
    BOXIPROD         = symbol("BoxIProd");
    BOXABSTR         = symbol("BoxAbstr");
    BOXAPPL          = symbol("BoxAppl");
    CLOSURE          = symbol("Closure");
    BOXERROR         = symbol("BoxError");
    BOXACCESS        = symbol("BoxAccess");
    BOXWITHLOCALDEF  = symbol("BoxWithLocalDef");
    BOXMODIFLOCALDEF = symbol("BoxModifLocalDef");
    BOXENVIRONMENT   = symbol("BoxEnvironment");
    BOXCOMPONENT     = symbol("BoxComponent");
    BOXLIBRARY       = symbol("BoxLibrary");
    IMPORTFILE       = symbol("ImportFile");
    BOXPRIM0         = symbol("BoxPrim0");
    BOXPRIM1         = symbol("BoxPrim1");
    BOXPRIM2         = symbol("BoxPrim2");
    BOXPRIM3         = symbol("BoxPrim3");
    BOXPRIM4         = symbol("BoxPrim4");
    BOXPRIM5         = symbol("BoxPrim5");
    BOXFFUN          = symbol("BoxFFun");
    BOXFCONST        = symbol("BoxFConst");
    BOXFVAR          = symbol("BoxFVar");
    BOXBUTTON        = symbol("BoxButton");
    BOXCHECKBOX      = symbol("BoxCheckbox");
    BOXHSLIDER       = symbol("BoxHSlider");
    BOXVSLIDER       = symbol("BoxVSlider");
    BOXNUMENTRY      = symbol("BoxNumEntry");
    BOXHGROUP        = symbol("BoxHGroup");
    BOXVGROUP        = symbol("BoxVGroup");
    BOXTGROUP        = symbol("BoxTGroup");
    BOXHBARGRAPH     = symbol("BoxHBargraph");
    BOXVBARGRAPH     = symbol("BoxVBargraph");
    BOXCASE          = symbol("BoxCase");
    BOXPATMATCHER    = symbol("BoxPatMatcher");
    BOXPATVAR        = symbol("BoxPatVar");
    BOXINPUTS        = symbol("BoxInputs");
    BOXOUTPUTS       = symbol("BoxOutputs");
    BOXSOUNDFILE     = symbol("boxSoundfile");
    BOXMETADATA      = symbol("boxMetadata");

    DOCEQN      = symbol("DocEqn");
    DOCDGM      = symbol("DocDgm");
    DOCNTC      = symbol("DocNtc");
    DOCLST      = symbol("DocLst");
    DOCMTD      = symbol("DocMtd");
    DOCTXT      = symbol("DocTxt");
    BARRIER     = symbol("BARRIER");
    UIFOLDER    = symbol("uiFolder");
    UIWIDGET    = symbol("uiWidget");
    PATHROOT    = symbol("/");
    PATHPARENT  = symbol("..");
    PATHCURRENT = symbol(".");
    FFUN        = symbol("ForeignFunction");

    SIGINPUT           = symbol("SigInput");
    SIGOUTPUT          = symbol("SigOutput");
    SIGDELAY1          = symbol("SigDelay1");
    SIGDELAY           = symbol("SigDelay");
    SIGPREFIX          = symbol("SigPrefix");
    SIGRDTBL           = symbol("SigRDTbl");
    SIGWRTBL           = symbol("SigWRTbl");
    SIGGEN             = symbol("SigGen");
    SIGDOCONSTANTTBL   = symbol("SigDocConstantTbl");
    SIGDOCWRITETBL     = symbol("SigDocWriteTbl");
    SIGDOCACCESSTBL    = symbol("SigDocAccessTbl");
    SIGSELECT2         = symbol("SigSelect2");
    SIGASSERTBOUNDS    = symbol("sigAssertBounds");
    SIGHIGHEST         = symbol("sigHighest");
    SIGLOWEST          = symbol("sigLowest");
    SIGBINOP           = symbol("SigBinOp");
    SIGFFUN            = symbol("SigFFun");
    SIGFCONST          = symbol("SigFConst");
    SIGFVAR            = symbol("SigFVar");
    SIGPROJ            = symbol("SigProj");
    SIGINTCAST         = symbol("SigIntCast");
    SIGBITCAST         = symbol("SigBitCast");
    SIGFLOATCAST       = symbol("SigFloatCast");
    SIGBUTTON          = symbol("SigButton");
    SIGCHECKBOX        = symbol("SigCheckbox");
    SIGWAVEFORM        = symbol("SigWaveform");
    SIGHSLIDER         = symbol("SigHSlider");
    SIGVSLIDER         = symbol("SigVSlider");
    SIGNUMENTRY        = symbol("SigNumEntry");
    SIGHBARGRAPH       = symbol("SigHBargraph");
    SIGVBARGRAPH       = symbol("SigVBargraph");
    SIGATTACH          = symbol("SigAttach");
    SIGENABLE          = symbol("SigEnable");
    SIGCONTROL         = symbol("SigControl");
    SIGSOUNDFILE       = symbol("SigSoundfile");
    SIGSOUNDFILELENGTH = symbol("SigSoundfileLength");
    SIGSOUNDFILERATE   = symbol("SigSoundfileRate");
    SIGSOUNDFILEBUFFER = symbol("SigSoundfileBuffer");
    SIGTUPLE           = symbol("SigTuple");
    SIGTUPLEACCESS     = symbol("SigTupleAccess");
    SIMPLETYPE         = symbol("SimpleType");
    TABLETYPE          = symbol("TableType");
    TUPLETTYPE         = symbol("TupletType");

    // recursive trees
    DEBRUIJN    = symbol("DEBRUIJN");
    DEBRUIJNREF = symbol("DEBRUIJNREF");
    SUBSTITUTE  = symbol("SUBSTITUTE");

    SYMREC    = symbol("SYMREC");
    SYMRECREF = symbol("SYMRECREF");
    SYMLIFTN  = symbol("LIFTN");

    gMachineFloatSize      = sizeof(float);
    gMachineInt32Size      = sizeof(int);
    gMachineInt64Size      = sizeof(long int);
    gMachineDoubleSize     = sizeof(double);
    gMachineQuadSize       = sizeof(long double);
    gMachineFixedPointSize = gMachineFloatSize;
    gMachineBoolSize       = sizeof(bool);

    // Assuming we are compiling for a 64 bits machine
    gMachinePtrSize = sizeof(nullptr);
#if defined(ANDROID) && INTPTR_MAX == INT32_MAX
    // Hack for 32Bit Android Architectures ; sizeof(nullptr) == 4 but LLVM DataLayout.GetPointerSize() == 8
    gMachinePtrSize *= 2;
#endif

    gMachineMaxStackSize = MAX_MACHINE_STACK_SIZE;
}

// Part of the state that needs to be initialized between consecutive calls to Box/Signal API
void global::reset()
{
    gAllWarning = false;
    gWarningMessages.clear();

    gResult          = nullptr;
    gExpandedDefList = nullptr;

    gDetailsSwitch    = false;
    gDrawSignals      = false;
    gDrawRouteFrame   = false;
    gShadowBlur       = false;  // note: svg2pdf doesn't like the blur filter
    gScaledSVG        = false;
    gStripDocSwitch   = false;  // Strip <mdoc> content from doc listings.
    gFoldThreshold    = 25;
    gFoldComplexity   = 2;
    gMaxNameSize      = 40;
    gSimpleNames      = false;
    gSimplifyDiagrams = false;
    gMaxCopyDelay     = 16;

    gVectorSwitch      = false;
    gDeepFirstSwitch   = false;
    gVecSize           = 32;
    gVectorLoopVariant = 0;

    gOpenMPSwitch    = false;
    gOpenMPLoop      = false;
    gSchedulerSwitch = false;
    gOpenCLSwitch    = false;
    gCUDASwitch      = false;
    gGroupTaskSwitch = false;
    gFunTaskSwitch   = false;

    gUIMacroSwitch = false;
    gDumpNorm      = -1;
    gFTZMode       = 0;
    gRangeUI       = false;
    gFreezeUI      = false;

    gFloatSize = 1;  // -single by default

    gPrintFileListSwitch = false;
    gInlineArchSwitch    = false;

    gDSPStruct  = false;
    gLightMode  = false;
    gClang      = false;
    gNoVirtual  = false;
    gCheckTable = true;

    gMathExceptions = false;

    gClassName      = "mydsp";
    gSuperClassName = "dsp";
    gProcessName    = "process";

    gDSPFactory = nullptr;

    gInputString = "";
    gInputFiles.clear();
    gMetaDataSet.clear();

    // Backend configuration : default values
    gAllowForeignFunction = true;
    gAllowForeignConstant = true;
    gAllowForeignVar      = true;
    gComputeIOTA          = false;
    gFAUSTFLOAT2Internal  = false;
    gInPlace              = false;
    gStrictSelect         = false;
    gHasExp10             = false;
    gLoopVarInBytes       = false;
    gUseMemmove           = false;
    gWaveformInDSP        = false;
    gUseDefaultSound      = true;
    gHasTeeLocal          = false;
    gMathApprox           = false;
    gNeedManualPow        = true;
    gRemoveVarAddress     = false;
    gOneSample            = -1;
    gOneSampleControl     = false;
    gInlineTable          = false;
    gComputeMix           = false;
    gBool2Int             = false;
    gFastMathLib          = "";
    gNamespace            = "";
    gFullParentheses      = false;
    gCheckIntRange        = false;
    gReprC                = true;

    gNarrowingLimit = 0;
    gWideningLimit  = 0;

    gLstDependenciesSwitch = true;  // mdoc listing management.
    gLstMdocTagsSwitch     = true;  // mdoc listing management.
    gLstDistributedSwitch  = true;  // mdoc listing management.
    
    gAutoDifferentiate = false;

    gLatexDocSwitch = true;  // Only LaTeX outformat is handled for the moment.

    gFileNum = 0;

    gBoxCounter    = 0;
    gSignalCounter = 0;

    gCountInferences = 0;
    gCountMaximal    = 0;

    gDummyInput = 10000;

    gBoxSlotNumber = 0;
    gMemoryManager = false;

    gLocalCausalityCheck = false;
    gCausality           = false;

    gOccurrences = nullptr;
    gFoldingFlag = false;
    gDevSuffix   = nullptr;

    gOutputLang = "";

#ifdef WASM_BUILD
    gWASMVisitor = nullptr;  // Will be (possibly) allocated in WebAssembly backend
    gWASTVisitor = nullptr;  // Will be (possibly) allocated in WebAssembly backend
#endif

#if defined(INTERP_BUILD) || defined(INTERP_COMP_BUILD)
    gInterpreterVisitor = nullptr;  // Will be (possibly) allocated in Interp backend
#endif

#ifdef JULIA_BUILD
    gJuliaVisitor = nullptr;  // Will be (possibly) allocated in Julia backend
#endif

#ifdef JSFX_BUILD
    gJSFXVisitor = nullptr;  // Will be (possibly) allocated in JSFX backend
#endif

#ifdef CMAJOR_BUILD
    gTableSizeVisitor = nullptr;  // Will be (possibly) allocated in Cmajor backend
#endif

#ifdef JAX_BUILD
    gJAXVisitor = nullptr;  // Will be (possibly) allocated in JAX backend
#endif

#ifdef TEMPLATE_BUILD
    gTemplateVisitor = nullptr;  // Will be (possibly) allocated in Template backend
#endif

#ifdef CODEBOX_BUILD
    gCodeboxVisitor = nullptr;  // Will be (possibly) allocated in Codebox backend
#endif

    gHelpSwitch        = false;
    gVersionSwitch     = false;
    gLibDirSwitch      = false;
    gIncludeDirSwitch  = false;
    gArchDirSwitch     = false;
    gDspDirSwitch      = false;
    gPathListSwitch    = false;
    gGraphSwitch       = false;
    gDrawPSSwitch      = false;
    gDrawSVGSwitch     = false;
    gVHDLTrace         = false;
    gVHDLFloatEncoding = false;
    gFPGAMemory        = 10000;
    gPrintXMLSwitch    = false;
    gPrintJSONSwitch   = false;
    gPrintDocSwitch    = false;
    gArchFile          = "";
    gExportDSP         = false;

    gTimeout = 120;  // Time out to abort compiler (in seconds)

    gErrorCount   = 0;
    gErrorMessage = "";

    // By default use "cpp" output
    gOutputLang = (getenv("FAUST_DEFAULT_BACKEND")) ? string(getenv("FAUST_DEFAULT_BACKEND")) : "cpp";
}

// Done after contructor since part of the following allocations need the "global" object to be fully built
void global::init()
{
    // Default init
    initFaustFloat();
    
    gPureRoutingProperty   = new property<bool>();
    gSymbolicBoxProperty   = new property<Tree>();
    gSimplifiedBoxProperty = new property<Tree>();
    gSymListProp           = new property<Tree>();

    // Essential predefined types
    gMemoizedTypes          = new property<AudioType*>();
    gAllocationCount        = 0;
    gMaskDelayLineThreshold = INT_MAX;

    // True by default but only usable with -lang ocpp backend
    gEnableFlag = true;

    // Essential predefined types
    TINPUT = makeSimpleType(kReal, kSamp, kExec, kVect, kNum, interval(-1, 1));
    TGUI   = makeSimpleType(kReal, kBlock, kExec, kVect, kNum, interval());
   
    TREC = makeSimpleType(kInt, kSamp, kInit, kScal, kNum, interval(0, 0));
    // !!! TRECMAX Maximal only in the last component of the type lattice
    TRECMAX = makeSimpleType(kInt, kSamp, kInit, kScal, kNum, interval(-HUGE_VAL, HUGE_VAL));

    // Predefined symbols CONS and NIL
    CONS = symbol("cons");
    NIL  = symbol("nil");
    // Predefined nil tree
    nil = tree(NIL);

    PROCESS = symbol("process");

    BOXTYPEPROP      = tree(symbol("boxTypeProp"));
    NUMERICPROPERTY  = tree(symbol("NUMERICPROPERTY"));
    DEFLINEPROP      = tree(symbol("DefLineProp"));
    USELINEPROP      = tree(symbol("UseLineProp"));
    SIMPLIFIED       = tree(symbol("sigSimplifiedProp"));
    DOCTABLES        = tree(symbol("DocTablesProp"));
    NULLENV          = tree(symbol("NullRenameEnv"));
    COLORPROPERTY    = tree(symbol("ColorProperty"));
    ORDERPROP        = tree(symbol("OrderProp"));
    RECURSIVNESS     = tree(symbol("RecursivnessProp"));
    NULLTYPEENV      = tree(symbol("NullTypeEnv"));
    RECDEF           = tree(symbol("RECDEF"));
    DEBRUIJN2SYM     = tree(symbol("deBruijn2Sym"));
    NORMALFORM       = tree(symbol("NormalForm"));
    DEFNAMEPROPERTY  = tree(symbol("DEFNAMEPROPERTY"));
    NICKNAMEPROPERTY = tree(symbol("NICKNAMEPROPERTY"));
    BCOMPLEXITY      = tree("BCOMPLEXITY");
    LETRECBODY       = boxIdent("RECURSIVEBODY");

    PROPAGATEPROPERTY = symbol("PropagateProperty");
 
    // FAUSTfilename is defined in errormsg.cpp but must be redefined at each compilation.
    FAUSTfilename = "";
    FAUSTin       = nullptr;

    gLatexheaderfilename = "latexheader.tex";
    gDocTextsDefaultFile = "mathdoctexts-default.txt";

    gCurrentLocal = setlocale(LC_ALL, NULL);
    if (gCurrentLocal != NULL) {
        gCurrentLocal = strdup(gCurrentLocal);
    }

    // Setup standard "C" local
    // (workaround for a bug in bitcode generation : http://lists.cs.uiuc.edu/pipermail/llvmbugs/2012-May/023530.html)
    setlocale(LC_ALL, "C");

    // Source file injection
    gInjectFlag = false;  // inject an external source file into the architecture file
    gInjectFile = "";     // instead of a compiled dsp file

    // Create type declaration for external 'soundfile' type
    vector<NamedTyped*> sf_type_fields;
    sf_type_fields.push_back(InstBuilder::genNamedTyped("fBuffers", InstBuilder::genBasicTyped(Typed::kVoid_ptr)));
    sf_type_fields.push_back(InstBuilder::genNamedTyped("fLength", InstBuilder::genBasicTyped(Typed::kInt32_ptr)));
    sf_type_fields.push_back(InstBuilder::genNamedTyped("fSR", InstBuilder::genBasicTyped(Typed::kInt32_ptr)));
    sf_type_fields.push_back(InstBuilder::genNamedTyped("fOffset", InstBuilder::genBasicTyped(Typed::kInt32_ptr)));
    sf_type_fields.push_back(InstBuilder::genNamedTyped("fChannels", InstBuilder::genInt32Typed()));
    sf_type_fields.push_back(InstBuilder::genNamedTyped("fParts", InstBuilder::genInt32Typed()));
    sf_type_fields.push_back(InstBuilder::genNamedTyped("fIsDouble", InstBuilder::genInt32Typed()));
    gExternalStructTypes[Typed::kSound] =
        InstBuilder::genDeclareStructTypeInst(InstBuilder::genStructTyped("Soundfile", sf_type_fields));

    // Foreign math functions supported by the Interp, Cmajor, codebox, wasm/wast backends
    gMathForeignFunctions["acoshf"] = true;
    gMathForeignFunctions["acosh"]  = true;
    gMathForeignFunctions["acoshl"] = true;

    gMathForeignFunctions["asinhf"] = true;
    gMathForeignFunctions["asinh"]  = true;
    gMathForeignFunctions["asinhl"] = true;

    gMathForeignFunctions["atanhf"] = true;
    gMathForeignFunctions["atanh"]  = true;
    gMathForeignFunctions["atanhl"] = true;

    gMathForeignFunctions["coshf"] = true;
    gMathForeignFunctions["cosh"]  = true;
    gMathForeignFunctions["coshl"] = true;

    gMathForeignFunctions["sinhf"] = true;
    gMathForeignFunctions["sinh"]  = true;
    gMathForeignFunctions["sinhl"] = true;

    gMathForeignFunctions["tanhf"] = true;
    gMathForeignFunctions["tanh"]  = true;
    gMathForeignFunctions["tanhl"] = true;

    gMathForeignFunctions["isnanf"] = true;
    gMathForeignFunctions["isnan"]  = true;
    gMathForeignFunctions["isnanl"] = true;

    gMathForeignFunctions["isinff"] = true;
    gMathForeignFunctions["isinf"]  = true;
    gMathForeignFunctions["isinfl"] = true;

    gMathForeignFunctions["copysignf"] = true;
    gMathForeignFunctions["copysign"]  = true;
    gMathForeignFunctions["copysignl"] = true;

    // internal state during drawing
    gInverter[0] = boxSeq(boxPar(boxWire(), boxInt(-1)), boxPrim2(sigMul));
    gInverter[1] = boxSeq(boxPar(boxInt(-1), boxWire()), boxPrim2(sigMul));
    gInverter[2] = boxSeq(boxPar(boxWire(), boxReal(-1.0)), boxPrim2(sigMul));
    gInverter[3] = boxSeq(boxPar(boxReal(-1.0), boxWire()), boxPrim2(sigMul));
    gInverter[4] = boxSeq(boxPar(boxInt(0), boxWire()), boxPrim2(sigSub));
    gInverter[5] = boxSeq(boxPar(boxReal(0.0), boxWire()), boxPrim2(sigSub));
}

string global::printFloat()
{
    switch (gFloatSize) {
        case 1:
            return "-single ";
        case 2:
            return "-double ";
        case 3:
            return "-quad ";
        case 4:
            return "-fx ";
        default:
            faustassert(false);
            return "";
    }
}

void global::printCompilationOptions(stringstream& dst, bool backend)
{
    if (gAutoDifferentiate) dst << "-diff ";
    if (gArchFile != "") dst << "-a " << gArchFile << " ";
    if (backend) {
#ifdef LLVM_BUILD
        if (gOutputLang == "llvm") {
            dst << "-lang " << gOutputLang << " " << LLVM_VERSION << " ";
        } else {
            dst << "-lang " << gOutputLang << " ";
        }
#else
        dst << "-lang " << gOutputLang << " ";
#endif
    }
    if (gInlineArchSwitch) dst << "-i ";
    if (gInPlace) dst << "-inpl ";
    if (gStrictSelect) dst << "-sts ";
    if (gOneSample >= 0) {
        dst << "-os" << gOneSample << " ";
        dst << "-fpga-mem " << gFPGAMemory << " ";
    }
    if (gLightMode) dst << "-light ";
    if (gMemoryManager) dst << "-mem ";
    if (gComputeMix) dst << "-cm ";
    if (gInlineTable) dst << "-it ";
    if (gRangeUI) dst << "-rui ";
    if (gNoVirtual) dst << "-nvi ";
    if (gFullParentheses) dst << "-fp ";
    if (gCheckIntRange) dst << "-cir ";
    dst << "-ct " << gCheckTable << " ";
    if (gMathApprox) dst << "-mapp ";
    if (gMathExceptions) dst << "-me ";
    if (gFastMathLib != "") dst << "-fm " << gFastMathLib << " ";
    if (gVHDLTrace) dst << "-vhdl-trace";
    if (gVHDLFloatEncoding) dst << "-vhdl-float";
    if (gClassName != "mydsp") dst << "-cn " << gClassName << " ";
    if (gSuperClassName != "dsp") dst << "-scn " << gSuperClassName << " ";
    if (gProcessName != "process") dst << "-pn " << gProcessName << " ";
    if (gMaskDelayLineThreshold != INT_MAX) dst << "-dtl " << gMaskDelayLineThreshold << " ";
    dst << "-es " << gEnableFlag << " ";
    if (gHasExp10) dst << "-exp10 ";
    if (gSchedulerSwitch) dst << "-sch ";
    if (gOpenMPSwitch) dst << "-omp " << ((gOpenMPLoop) ? "-pl " : "");
    dst << "-mcd " << gMaxCopyDelay << " ";
    if (gUIMacroSwitch) dst << "-uim ";
    dst << printFloat();
    dst << "-ftz " << gFTZMode << " ";
    if (gVectorSwitch) {
        dst << "-vec "
            << "-lv " << gVectorLoopVariant << " "
            << "-vs " << gVecSize << " " << ((gFunTaskSwitch) ? "-fun " : "") << ((gGroupTaskSwitch) ? "-g " : "")
            << ((gDeepFirstSwitch) ? "-dfs " : "");
    }

    // Add 'compile_options' metadata
    string res = dst.str();
    gMetaDataSet[tree("compile_options")].insert(tree("\"" + res.substr(0, res.size() - 1) + "\""));
}

string global::printCompilationOptions1()
{
    stringstream dst;
    printCompilationOptions(dst, true);
    string res = dst.str();
    return res.substr(0, res.size() - 1);
}

void global::initTypeSizeMap()
{
    // Init type size table (in bytes)
    gTypeSizeMap[Typed::kFloat]         = gMachineFloatSize;
    gTypeSizeMap[Typed::kFloat_ptr]     = gMachinePtrSize;
    gTypeSizeMap[Typed::kFloat_ptr_ptr] = gMachinePtrSize;
    gTypeSizeMap[Typed::kFloat_vec]     = gMachineFloatSize * gVecSize;
    gTypeSizeMap[Typed::kFloat_vec_ptr] = gMachinePtrSize;

    gTypeSizeMap[Typed::kDouble]         = gMachineDoubleSize;
    gTypeSizeMap[Typed::kDouble_ptr]     = gMachinePtrSize;
    gTypeSizeMap[Typed::kDouble_ptr_ptr] = gMachinePtrSize;
    gTypeSizeMap[Typed::kDouble_vec]     = gMachineDoubleSize * gVecSize;
    gTypeSizeMap[Typed::kDouble_vec_ptr] = gMachinePtrSize;

    gTypeSizeMap[Typed::kQuad]         = gMachineQuadSize;
    gTypeSizeMap[Typed::kQuad_ptr]     = gMachinePtrSize;
    gTypeSizeMap[Typed::kQuad_ptr_ptr] = gMachinePtrSize;
    gTypeSizeMap[Typed::kQuad_vec]     = gMachineQuadSize * gVecSize;
    gTypeSizeMap[Typed::kQuad_vec_ptr] = gMachinePtrSize;

    gTypeSizeMap[Typed::kFixedPoint]         = gMachineFixedPointSize;
    gTypeSizeMap[Typed::kFixedPoint_ptr]     = gMachinePtrSize;
    gTypeSizeMap[Typed::kFixedPoint_ptr_ptr] = gMachinePtrSize;
    gTypeSizeMap[Typed::kFixedPoint_vec]     = gMachineFixedPointSize * gVecSize;
    gTypeSizeMap[Typed::kFixedPoint_vec_ptr] = gMachinePtrSize;

    gTypeSizeMap[Typed::kInt32]         = gMachineInt32Size;
    gTypeSizeMap[Typed::kInt32_ptr]     = gMachinePtrSize;
    gTypeSizeMap[Typed::kInt32_vec]     = gMachineInt32Size * gVecSize;
    gTypeSizeMap[Typed::kInt32_vec_ptr] = gMachinePtrSize;

    gTypeSizeMap[Typed::kInt64]         = gMachineInt64Size;
    gTypeSizeMap[Typed::kInt64_ptr]     = gMachinePtrSize;
    gTypeSizeMap[Typed::kInt64_vec]     = gMachineInt64Size * gVecSize;
    gTypeSizeMap[Typed::kInt64_vec_ptr] = gMachinePtrSize;

    gTypeSizeMap[Typed::kBool]         = gMachineBoolSize;
    gTypeSizeMap[Typed::kBool_ptr]     = gMachinePtrSize;
    gTypeSizeMap[Typed::kBool_vec]     = gMachineBoolSize * gVecSize;
    gTypeSizeMap[Typed::kBool_vec_ptr] = gMachinePtrSize;

    // Takes the type of internal real
    gTypeSizeMap[Typed::kFloatMacro]         = gTypeSizeMap[itfloat()];
    gTypeSizeMap[Typed::kFloatMacro_ptr]     = gMachinePtrSize;
    gTypeSizeMap[Typed::kFloatMacro_ptr_ptr] = gMachinePtrSize;

    gTypeSizeMap[Typed::kVoid_ptr] = gMachinePtrSize;

    gTypeSizeMap[Typed::kObj_ptr]   = gMachinePtrSize;
    gTypeSizeMap[Typed::kSound_ptr] = gMachinePtrSize;
    gTypeSizeMap[Typed::kUint_ptr]  = gMachinePtrSize;
}

int global::audioSampleSize()
{
    return int(pow(2.f, float(gFloatSize + 1)));
}

bool global::hasForeignFunction(const string& name, const string& inc_file)
{
#ifdef LLVM_BUILD
    // LLVM backend can use 'standard' foreign linked functions
    static vector<string> inc_list = {"<math.h>", "<cmath>", "<stdlib.h>"};
    bool                  is_inc   = find(begin(inc_list), end(inc_list), inc_file) != inc_list.end();
    // or custom added ones
    bool is_ff       = llvm_dsp_factory_aux::gForeignFunctions.count(name) > 0;
    bool is_linkable = (gOutputLang == "llvm") && (is_inc || is_ff);
#else
    bool is_linkable = false;
#endif
    bool internal_math_ff =
        ((gOutputLang == "llvm")
         || startWith(gOutputLang, "wast")
         || startWith(gOutputLang, "wasm")
         || (gOutputLang == "interp")
         || startWith(gOutputLang, "cmajor")
         || startWith(gOutputLang, "codebox")
         || (gOutputLang == "dlang")
         || (gOutputLang == "csharp")
         || (gOutputLang == "rust")
         || (gOutputLang == "julia")
         || startWith(gOutputLang, "jsfx")
         || (gOutputLang == "jax"));

    return (internal_math_ff && (gMathForeignFunctions.find(name) != gMathForeignFunctions.end())) || is_linkable;
}

BasicTyped* global::genBasicTyped(Typed::VarType type)
{
    // Possibly force FAUSTFLOAT type (= kFloatMacro) to internal real
    Typed::VarType new_type = ((type == Typed::kFloatMacro) && gFAUSTFLOAT2Internal) ? itfloat() : type;

    // If not defined, add the type in the table
    if (gTypeTable.find(new_type) == gTypeTable.end()) {
        gTypeTable[new_type] = new BasicTyped(new_type);
    }
    return gTypeTable[new_type];
}

void global::setVarType(const string& name, Typed::VarType type)
{
    gVarTypeTable[name] = genBasicTyped(type);
}

Typed::VarType global::getVarType(const string& name)
{
    return gVarTypeTable[name]->getType();
}

global::~global()
{
    Garbageable::cleanup();
    BasicTyped::cleanup();
    DeclareVarInst::cleanup();
    setlocale(LC_ALL, gCurrentLocal);
    free(gCurrentLocal);

    // Cleanup
#ifdef C_BUILD
    CInstVisitor::cleanup();
#endif
#ifdef CPP_BUILD
    CPPInstVisitor::cleanup();
#endif
#ifdef CODEBOX_BUILD
    CodeboxInstVisitor::cleanup();
#endif
#ifdef CSHARP_BUILD
    CSharpInstVisitor::cleanup();
#endif
#ifdef DLANG_BUILD
    DLangInstVisitor::cleanup();
#endif
#ifdef FIR_BUILD
    FIRInstVisitor::cleanup();
#endif
#ifdef JAVA_BUILD
    JAVAInstVisitor::cleanup();
#endif
#ifdef JULIA_BUILD
    JuliaInstVisitor::cleanup();
#endif
#ifdef JSFX_BUILD
    JSFXInstVisitor::cleanup();
#endif
#ifdef JAX_BUILD
    JAXInstVisitor::cleanup();
#endif
#ifdef TEMPLATE_BUILD
    TemplateInstVisitor::cleanup();
#endif
#ifdef RUST_BUILD
    RustInstVisitor::cleanup();
#endif
}

void global::allocate()
{
    gGlobal = new global();
    gGlobal->init();
}

void global::destroy()
{
#ifdef EMCC
    if (faustexception::gJSExceptionMsg) {
        free((void*)faustexception::gJSExceptionMsg);
        faustexception::gJSExceptionMsg = nullptr;
    }
#endif
    delete gGlobal;
    gGlobal = nullptr;
}

string global::makeDrawPath()
{
    if (gOutputDir != "") {
        return gOutputDir + "/" + gMasterName + ".dsp";
    } else {
        return gMasterDocument;
    }
}

string global::makeDrawPathNoExt()
{
    if (gOutputDir != "") {
        return gOutputDir + "/" + gMasterName;
    } else if (gMasterDocument.length() >= 4 && gMasterDocument.substr(gMasterDocument.length() - 4) == ".dsp") {
        return gMasterDocument.substr(0, gMasterDocument.length() - 4);
    } else {
        return gMasterDocument;
    }
}

/*****************************************************************************
                        getFreshID
*****************************************************************************/

string global::getFreshID(const string& prefix)
{
    if (gIDCounters.find(prefix) == gIDCounters.end()) {
        gIDCounters[prefix] = 0;
    }
    int n               = gIDCounters[prefix];
    gIDCounters[prefix] = n + 1;
    return subst("$0$1", prefix, T(n));
}

bool global::isDebug(const string& debug_val)
{
    string debug_var = (getenv("FAUST_DEBUG")) ? string(getenv("FAUST_DEBUG")) : "";
    return debug_var == debug_val;
}

/****************************************************************
 Command line tools and arguments
 *****************************************************************/

// Timing can be used outside of the scope of 'gGlobal'
extern bool gTimingSwitch;

static bool isCmd(const char* cmd, const char* kw1)
{
    return (strcmp(cmd, kw1) == 0);
}

static bool isCmd(const char* cmd, const char* kw1, const char* kw2)
{
    return (strcmp(cmd, kw1) == 0) || (strcmp(cmd, kw2) == 0);
}

bool global::processCmdline(int argc, const char* argv[])
{
    int          i   = 1;
    int          err = 0;
    stringstream parse_error;
    bool         float_size = false;
    
    /*
        for (int i = 0; i < argc; i++) {
        cerr << "processCmdline i = " << i << " cmd = " << argv[i] << "\n";
     }
    */
    
    while (i < argc) {
        if (isCmd(argv[i], "-h", "--help")) {
            gHelpSwitch = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-lang", "--language") && (i + 1 < argc)) {
            gOutputLang = argv[i + 1];
            i += 2;
            
        } else if (isCmd(argv[i], "-v", "--version")) {
            gVersionSwitch = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-libdir", "--libdir")) {
            gLibDirSwitch = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-includedir", "--includedir")) {
            gIncludeDirSwitch = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-archdir", "--archdir")) {
            gArchDirSwitch = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-dspdir", "--dspdir")) {
            gDspDirSwitch = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-pathslist", "--pathslist")) {
            gPathListSwitch = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-d", "--details")) {
            gDetailsSwitch = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-a", "--architecture") && (i + 1 < argc)) {
            gArchFile = argv[i + 1];
            i += 2;
            
        } else if (isCmd(argv[i], "-inj", "--inject") && (i + 1 < argc)) {
            gInjectFlag = true;
            gInjectFile = argv[i + 1];
            i += 2;
            
        } else if (isCmd(argv[i], "-o") && (i + 1 < argc)) {
            gOutputFile = argv[i + 1];
            i += 2;
            
        } else if (isCmd(argv[i], "-wi", "--widening-iterations") && (i + 1 < argc)) {
            gWideningLimit = std::atoi(argv[i + 1]);
            i += 2;
            
        } else if (isCmd(argv[i], "-ni", "--narrowing-iterations") && (i + 1 < argc)) {
            gNarrowingLimit = std::atoi(argv[i + 1]);
            i += 2;
            
        } else if (isCmd(argv[i], "-ps", "--postscript")) {
            gDrawPSSwitch = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-xml", "--xml")) {
            gPrintXMLSwitch = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-json", "--json")) {
            gPrintJSONSwitch = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-tg", "--task-graph")) {
            gGraphSwitch = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-sg", "--signal-graph")) {
            gDrawSignals = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-drf", "--draw-route-frame")) {
            gDrawRouteFrame = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-blur", "--shadow-blur")) {
            gShadowBlur = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-sc", "--scaled-svg")) {
            gScaledSVG = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-svg", "--svg")) {
            gDrawSVGSwitch = true;
            i += 1;

        } else if (isCmd(argv[i], "-vhdl-trace", "--vhdl-trace")) {
            gVHDLTrace = true;
            i += 1;

        } else if (isCmd(argv[i], "-vhdl-float", "--vhdl-float")) {
            gVHDLFloatEncoding = true;
            i += 1;

        } else if (isCmd(argv[i], "-vhdl-components", "--vhdl-components") && (i + 1 < argc)) {
            gVHDLComponentsFile = std::string(argv[i + 1]);
            i += 2;

        } else if (isCmd(argv[i], "-fpga-mem", "-fpga-mem") && (i + 1 < argc)) {
            gFPGAMemory = std::atoi(argv[i + 1]);
            i += 2;
            
        } else if (isCmd(argv[i], "-f", "--fold") && (i + 1 < argc)) {
            gFoldThreshold = std::atoi(argv[i + 1]);
            i += 2;
            
        } else if (isCmd(argv[i], "-fc", "--fold-complexity") && (i + 1 < argc)) {
            gFoldComplexity = std::atoi(argv[i + 1]);
            i += 2;
            
        } else if (isCmd(argv[i], "-mns", "--max-name-size") && (i + 1 < argc)) {
            gMaxNameSize = std::atoi(argv[i + 1]);
            i += 2;
            
        } else if (isCmd(argv[i], "-sn", "--simple-names")) {
            gSimpleNames = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-mcd", "--max-copy-delay") && (i + 1 < argc)) {
            gMaxCopyDelay = std::atoi(argv[i + 1]);
            i += 2;
            
        } else if (isCmd(argv[i], "-dlt", "-delay-line-threshold") && (i + 1 < argc)) {
            gMaskDelayLineThreshold = std::atoi(argv[i + 1]);
            i += 2;
            
        } else if (isCmd(argv[i], "-mem", "--memory-manager")) {
            gMemoryManager = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-sd", "--simplify-diagrams")) {
            gSimplifyDiagrams = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-vec", "--vectorize")) {
            gVectorSwitch = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-scal", "--scalar")) {
            gVectorSwitch = false;
            i += 1;
            
        } else if (isCmd(argv[i], "-dfs", "--deepFirstScheduling")) {
            gDeepFirstSwitch = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-vs", "--vec-size") && (i + 1 < argc)) {
            gVecSize = std::atoi(argv[i + 1]);
            i += 2;
            
        } else if (isCmd(argv[i], "-lv", "--loop-variant") && (i + 1 < argc)) {
            gVectorLoopVariant = std::atoi(argv[i + 1]);
            i += 2;
            
        } else if (isCmd(argv[i], "-omp", "--openmp")) {
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
            
        } else if (isCmd(argv[i], "-t", "--timeout") && (i + 1 < argc)) {
            gTimeout = std::atoi(argv[i + 1]);
            i += 2;
            
        } else if (isCmd(argv[i], "-time", "--compilation-time")) {
            gTimingSwitch = true;
            i += 1;
            
        // 'real' options
        } else if (isCmd(argv[i], "-single", "--single-precision-floats")) {
            if (float_size && gFloatSize != 1) {
                throw faustexception("ERROR : cannot using -single, -double, -quad or -fx at the same time\n");
            } else {
                float_size = true;
            }
            gFloatSize = 1;
            i += 1;
            
        } else if (isCmd(argv[i], "-double", "--double-precision-floats")) {
            if (float_size && gFloatSize != 2) {
                throw faustexception("ERROR : cannot using -single, -double, -quad or -fx at the same time\n");
            } else {
                float_size = true;
            }
            gFloatSize = 2;
            i += 1;
            
        } else if (isCmd(argv[i], "-quad", "--quad-precision-floats")) {
            if (float_size && gFloatSize != 3) {
                throw faustexception("ERROR : cannot using -single, -double, -quad or -fx at the same time\n");
            } else {
                float_size = true;
            }
            gFloatSize = 3;
            i += 1;
            
        } else if (isCmd(argv[i], "-fx", "--fixed-point")) {
            if (float_size && gFloatSize != 4) {
                throw faustexception("ERROR : cannot using -single, -double, -quad or -fx at the same time\n");
            } else {
                float_size = true;
            }
            gFloatSize = 4;
            i += 1;
            
        } else if (isCmd(argv[i], "-mdoc", "--mathdoc")) {
            gPrintDocSwitch = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-mdlang", "--mathdoc-lang") && (i + 1 < argc)) {
            gDocLang = argv[i + 1];
            i += 2;
            
        } else if (isCmd(argv[i], "-stripmdoc", "--strip-mdoc-tags")) {
            gStripDocSwitch = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-flist", "--file-list")) {
            gPrintFileListSwitch = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-norm", "--normalized-form")) {
            gDumpNorm = 0;
            i += 1;
            
        } else if (isCmd(argv[i], "-norm1", "--normalized-form1")) {
            gDumpNorm = 1;
            i += 1;
            
        } else if (isCmd(argv[i], "-norm2", "--normalized-form2")) {
            gDumpNorm = 2;
            i += 1;
            
        } else if (isCmd(argv[i], "-cn", "--class-name") && (i + 1 < argc)) {
            vector<char> rep    = {'@', ' ', '(', ')', '/', '\\', '.'};
            gClassName = replaceCharList(argv[i + 1], rep, '_');
            i += 2;
            
        } else if (isCmd(argv[i], "-scn", "--super-class-name") && (i + 1 < argc)) {
            gSuperClassName = argv[i + 1];
            i += 2;
            
        } else if (isCmd(argv[i], "-pn", "--process-name") && (i + 1 < argc)) {
            gProcessName = argv[i + 1];
            i += 2;
            
        } else if (isCmd(argv[i], "-i", "--inline-architecture-files")) {
            gInlineArchSwitch = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-e", "--export-dsp")) {
            gExportDSP = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-exp10", "--generate-exp10")) {
            gHasExp10 = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-os", "--one-sample") || isCmd(argv[i], "-os0", "--one-sample0")) {
            gOneSample = 0;
            i += 1;
            
        } else if (isCmd(argv[i], "-os1", "--one-sample1")) {
            gOneSample = 1;
            i += 1;
            
        } else if (isCmd(argv[i], "-os2", "--one-sample2")) {
            gOneSample = 2;
            i += 1;
            
        } else if (isCmd(argv[i], "-os3", "--one-sample3")) {
            gOneSample = 3;
            i += 1;
            
        } else if (isCmd(argv[i], "-it", "--inline-table")) {
            gInlineTable = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-cm", "--compute-mix")) {
            gComputeMix = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-ftz", "--flush-to-zero")) {
            gFTZMode = std::atoi(argv[i + 1]);
            if ((gFTZMode > 2) || (gFTZMode < 0)) {
                stringstream error;
                error << "ERROR : invalid -ftz option: " << gFTZMode << endl;
                throw faustexception(error.str());
            }
            i += 2;
            
        } else if (isCmd(argv[i], "-rui", "--range-ui")) {
            gRangeUI = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-fui", "--freeze-ui")) {
            gFreezeUI = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-fm", "--fast-math")) {
            gFastMathLib = argv[i + 1];
            i += 2;
            
        } else if (isCmd(argv[i], "-mapp", "--math-approximation")) {
            gMathApprox = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-ns", "--namespace")) {
            gNamespace = argv[i + 1];
            i += 2;
            
        } else if (isCmd(argv[i], "-fp", "--full-parentheses")) {
            gFullParentheses = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-cir", "--check-integer-range")) {
            gCheckIntRange = true;
            i += 1;
        } else if (isCmd(argv[i], "-noreprc", "--no-reprc")) {
            gReprC = false;
            i += 1;
        } else if (isCmd(argv[i], "-I", "--import-dir") && (i + 1 < argc)) {
            if ((strstr(argv[i + 1], "http://") != 0) || (strstr(argv[i + 1], "https://") != 0)) {
                // We want to search user given directories *before* the standard ones, so insert at the beginning
                gImportDirList.insert(gImportDirList.begin(), argv[i + 1]);
            } else {
                char  temp[PATH_MAX + 1];
                char* path = realpath(argv[i + 1], temp);
                if (path) {
                    // We want to search user given directories *before* the standard ones, so insert at the beginning
                    gImportDirList.insert(gImportDirList.begin(), path);
                }
            }
            i += 2;
            
        } else if (isCmd(argv[i], "-A", "--architecture-dir") && (i + 1 < argc)) {
            if ((strstr(argv[i + 1], "http://") != 0) || (strstr(argv[i + 1], "https://") != 0)) {
                gArchitectureDirList.push_back(argv[i + 1]);
            } else {
                char  temp[PATH_MAX + 1];
                char* path = realpath(argv[i + 1], temp);
                if (path) {
                    gArchitectureDirList.push_back(path);
                }
            }
            i += 2;
            
        } else if (isCmd(argv[i], "-L", "--library") && (i + 1 < argc)) {
            gLibraryList.push_back(argv[i + 1]);
            i += 2;
            
        } else if (isCmd(argv[i], "-O", "--output-dir") && (i + 1 < argc)) {
            char  temp[PATH_MAX + 1];
            char* path = realpath(argv[i + 1], temp);
            if (path == 0) {
                stringstream error;
                error << "ERROR : invalid directory path " << argv[i + 1] << endl;
                throw faustexception(error.str());
            } else {
                gOutputDir = path;
            }
            i += 2;
            
        } else if (isCmd(argv[i], "-inpl", "--in-place")) {
            gInPlace = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-sts", "--strict-select")) {
            gStrictSelect = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-es", "--enable-semantics")) {
            gEnableFlag = (std::atoi(argv[i + 1]) == 1);
            i += 2;
            
        } else if (isCmd(argv[i], "-lcc", "--local-causality-check")) {
            gLocalCausalityCheck = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-light", "--light-mode")) {
            gLightMode = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-clang", "--clang")) {
            gClang = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-nvi", "--no-virtual")) {
            gNoVirtual = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-ct", "--check-table")) {
            gCheckTable = (std::atoi(argv[i + 1]) == 1);
            i += 2;
            
        } else if (isCmd(argv[i], "-wall", "--warning-all")) {
            gAllWarning = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-me", "--math-exceptions")) {
            gMathExceptions = true;
            i += 1;
    
        } else if (isCmd(argv[i], "-diff", "--auto-differentiate")) {
            gAutoDifferentiate = true;
            i += 1;
            
        } else if (isCmd(argv[i], "-lm", "--local-machine") || isCmd(argv[i], "-rm", "--remote-machine") ||
                   isCmd(argv[i], "-poly", "--polyphonic-mode") || isCmd(argv[i], "-voices", "--polyphonic-voices") ||
                   isCmd(argv[i], "-group", "--polyphonic-group")) {
            // Ignore arg
            i += 2;
            
        } else if (argv[i][0] != '-') {
            const char* url = argv[i];
            if (checkURL(url)) {
                gInputFiles.push_back(url);
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
    if (gOpenMPSwitch || gSchedulerSwitch) gVectorSwitch = true;
    
    // ========================
    // Check options coherency
    // ========================
    
    if (gInPlace && gVectorSwitch) {
        throw faustexception("ERROR : '-inpl' option can only be used in scalar mode\n");
    }
    
#if 0
    if (gOutputLang == "ocpp" && gVectorSwitch) {
        throw faustexception("ERROR : 'ocpp' backend can only be used in scalar mode\n");
    }
#endif
    if (gOneSample >= 0 && gOutputLang != "cpp" && gOutputLang != "c" && gOutputLang != "dlang" &&
        !startWith(gOutputLang, "cmajor") && gOutputLang != "fir") {
        throw faustexception("ERROR : '-os' option cannot only be used with 'cpp', 'c', 'fir' or 'cmajor' backends\n");
    }
    
    if (gOneSample >= 0 && gVectorSwitch) {
        throw faustexception("ERROR : '-os' option cannot only be used in scalar mode\n");
    }
    
    if (gVectorLoopVariant < 0 || gVectorLoopVariant > 1) {
        stringstream error;
        error << "ERROR : invalid loop variant [-lv = " << gVectorLoopVariant << "] should be 0 or 1" << endl;
        throw faustexception(error.str());
    }
    
    if (gVecSize < 4) {
        stringstream error;
        error << "ERROR : invalid vector size [-vs = " << gVecSize << "] should be at least 4" << endl;
        throw faustexception(error.str());
    }
    
    if (gFunTaskSwitch) {
        if (!(gOutputLang == "c" || gOutputLang == "cpp" || gOutputLang == "llvm" ||
              gOutputLang == "fir")) {
            throw faustexception("ERROR : -fun can only be used with 'c', 'cpp', 'llvm' or 'fir' backends\n");
        }
    }
    
    if (gFastMathLib != "") {
        if (!(gOutputLang == "c" || gOutputLang == "cpp" || gOutputLang == "llvm" ||
              startWith(gOutputLang, "wast") || startWith(gOutputLang, "wasm"))) {
            throw faustexception("ERROR : -fm can only be used with 'c', 'cpp', 'llvm' or 'wast/wast' backends\n");
        }
    }
    
    if (gNamespace != "" && gOutputLang != "cpp" && gOutputLang != "dlang") {
        throw faustexception("ERROR : -ns can only be used with the 'cpp' or 'dlang' backend\n");
    }
    
    if (gMaskDelayLineThreshold < INT_MAX && (gVectorSwitch || (gOutputLang == "ocpp"))) {
        throw faustexception(
                             "ERROR : '-dlt < INT_MAX' option can only be used in scalar mode and not with the 'ocpp' backend\n");
    }
    
    // gInlinetable check
    if (gInlineTable && gOutputLang != "cpp") {
        throw faustexception("ERROR : -it can only be used with 'cpp' backend\n");
    }
    
    // gComputeMix check
    if (gComputeMix && gOutputLang == "ocpp") {
        throw faustexception("ERROR : -cm cannot be used with the 'ocpp' backend\n");
    }
    
    if (gComputeMix && gOutputLang == "interp") {
        throw faustexception("ERROR : -cm cannot be used with the 'interp' backend\n");
    }
    
    if (gComputeMix && gOutputLang == "cmajor") {
        throw faustexception("ERROR : -cm cannot be used with the 'cmajor' backend\n");
    }
    
    if (gFloatSize == 4
        && gOutputLang != "cpp"
        && gOutputLang != "ocpp"
        && gOutputLang != "c"
        && gOutputLang != "fir") {
        throw faustexception("ERROR : -fx can only be used with 'c', 'cpp', 'ocpp' or 'fir' backends\n");
    }
    
    if (gFTZMode == 2
        && gOutputLang != "cpp"
        && gOutputLang != "ocpp"
        && gOutputLang != "c"
        && gOutputLang != "llvm"
        && startWith(gOutputLang, "wast")
        && startWith(gOutputLang,  "wasm")) {
        throw faustexception("ERROR : -ftz 2 can only be used with 'c', 'cpp', 'ocpp', 'llvm' or wast/wasm backends\n");
    }
    
    if (gClang && gOutputLang != "cpp" && gOutputLang != "ocpp" &&
        gOutputLang != "c") {
        throw faustexception("ERROR : -clang can only be used with 'c', 'cpp' or 'ocpp' backends\n");
    }
    
    if (gNoVirtual && gOutputLang != "cpp" && gOutputLang != "ocpp" &&
        gOutputLang != "c") {
        throw faustexception("ERROR : -nvi can only be used with 'c', 'cpp' or 'ocpp' backends\n");
    }
    
    if (gMemoryManager && gOutputLang != "cpp" && gOutputLang != "ocpp") {
        throw faustexception("ERROR : -mem can only be used with 'cpp' or 'ocpp' backends\n");
    }
    
    if (gArchFile != "" &&
        ((gOutputLang == "wast") || (gOutputLang == "wasm") || (gOutputLang == "interp") ||
         (gOutputLang == "llvm") || (gOutputLang == "fir"))) {
        throw faustexception("ERROR : -a can only be used with 'c', 'cpp', 'ocpp', 'rust' and 'cmajor' backends\n");
    }
    
    if (gClassName == "") {
        throw faustexception("ERROR : -cn used with empty string \n");
    }
    
    if (err != 0) {
        stringstream error;
        error << "WARNING : " << parse_error.str() << endl;
        gErrorMessage = error.str();
    }
    
    // When -lang has been set
    initFaustFloat();
    
    return (err == 0);
}

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

void global::initDocumentNames()
{
    if (gInputFiles.empty()) {
        gMasterDocument  = "Unknown";
        gMasterDirectory = ".";
        gMasterName      = "faustfx";
        gDocName         = "faustdoc";
    } else {
        gMasterDocument  = *gInputFiles.begin();
        gMasterDirectory = fileDirname(gMasterDocument);
        gMasterName      = fxName(gMasterDocument);
        gDocName         = fxName(gMasterDocument);
    }
    
    // Add gMasterDirectory in gImportDirList and gArchitectureDirList
    gImportDirList.push_back(gMasterDirectory);
    gArchitectureDirList.push_back(gMasterDirectory);
}

void global::initDirectories(int argc, const char* argv[])
{
#if !defined(FAUST_SELF_CONTAINED_LIB)
    char s[1024];
    getFaustPathname(s, 1024);
    
    gFaustExeDir              = exepath::get(argv[0]);
    gFaustRootDir             = exepath::dirup(gFaustExeDir);
    gFaustDirectory           = fileDirname(s);
    gFaustSuperDirectory      = fileDirname(gFaustDirectory);
    gFaustSuperSuperDirectory = fileDirname(gFaustSuperDirectory);
    
    //-------------------------------------------------------------------------------------
    // init gImportDirList : a list of path where to search .lib files
    //-------------------------------------------------------------------------------------
    if (char* envpath = getenv("FAUST_LIB_PATH")) {
        gImportDirList.push_back(envpath);
    }
#ifdef INSTALL_PREFIX
    gImportDirList.push_back(INSTALL_PREFIX "/share/faust");
#endif
    
    gImportDirList.push_back(exepath::dirup(gFaustExeDir) + "/share/faust");
    gImportDirList.push_back("/usr/local/share/faust");
    gImportDirList.push_back("/usr/share/faust");
    
    //-------------------------------------------------------------------------------------
    // init gArchitectureDirList : a list of path where to search architectures files
    //-------------------------------------------------------------------------------------
    if (char* envpath = getenv("FAUST_ARCH_PATH")) {
        gArchitectureDirList.push_back(envpath);
    }
    gArchitectureDirList.push_back(gFaustDirectory + "/architecture");
    gArchitectureDirList.push_back(gFaustSuperDirectory + "/architecture");
    gArchitectureDirList.push_back(gFaustSuperSuperDirectory + "/architecture");
#ifdef INSTALL_PREFIX
    gArchitectureDirList.push_back(INSTALL_PREFIX "/share/faust");
    gArchitectureDirList.push_back(INSTALL_PREFIX "/include");
#endif
    gArchitectureDirList.push_back(exepath::dirup(gFaustExeDir) + "/share/faust");
    gArchitectureDirList.push_back(exepath::dirup(gFaustExeDir) + "/include");
    gArchitectureDirList.push_back("/usr/local/share/faust");
    gArchitectureDirList.push_back("/usr/share/faust");
    gArchitectureDirList.push_back("/usr/local/include");
    gArchitectureDirList.push_back("/usr/include");
    
    // for debugging purposes
    //    cerr << "gArchitectureDirList:\n";
    //    for (const auto& d : gArchitectureDirList) {
    //        cerr << "\t" << d << "\n";
    //    }
    //    cerr << endl;
#endif
}

void global::printDeclareHeader(ostream& dst)
{
    for (const auto& i : gMetaDataSet) {
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

void global::parseSourceFiles()
{
    startTiming("parser");
    list<string>::iterator s;
    Tree result = nil;
    gReader.init();
    
    if (!gInjectFlag && gInputFiles.begin() == gInputFiles.end()) {
        throw faustexception("ERROR : no files specified; for help type \"faust --help\"\n");
    }
    for (s = gInputFiles.begin(); s != gInputFiles.end(); s++) {
        if (s == gInputFiles.begin()) {
            gMasterDocument = *s;
        }
        result = cons(importFile(tree(s->c_str())), result);
    }
    
    gExpandedDefList = gReader.expandList(result);
    endTiming("parser");
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
    
#ifdef CODEBOX_BUILD
    out << dspto << "Codebox" << endl;
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
    
#if defined(INTERP_BUILD) || defined(INTERP_COMP_BUILD)
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
    
#ifdef JSFX_BUILD
    out << dspto << "JSFX" << endl;
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
    
#ifdef VHDL_BUILD
    out << dspto << "VHDL" << endl;
#endif
    
#ifdef WASM_BUILD
    out << dspto << "WebAssembly (wast/wasm)" << endl;
#endif
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
    cout << "Copyright (C) 2002-2023, GRAME - Centre National de Creation Musicale. All rights reserved. \n";
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
         << "                                        'lang' should be c, cpp (default), cmajor, codebox, csharp, dlang, fir, interp, java, jax, jsfx, julia, llvm, "
         "ocpp, rust, vhdl or wast/wasm."
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
    cout << tab << "-fp         --full-parentheses          always add parentheses around binops." << endl;
    cout << tab << "-cir        --check-integer-range       check float to integer range conversion." << endl;
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
    cout << tab << "-it         --inline-table              inline rdtable/rwtable code in the main class." << endl;
    
    cout << tab << "-cm         --compute-mix               mix in outputs buffers." << endl;
    cout << tab << "-ct         --check-table               check rtable/rwtable index range and generate safe access code [0/1: 1 by default]." << endl;
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
         << "-rui        --range-ui                  whether to generate code to constraint vslider/hslider/nentry values "
    "in [min..max] range."
        << endl;
    cout << tab
         << "-fui        --freeze-ui                 whether to freeze vslider/hslider/nentry to a given value (init value by default)."
         << endl;
    cout << tab
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
    cout << tab << "-lv <n>     --loop-variant <n>          [0:fastest, fixed vector size and a remaining loop (default), 1:simple, variable vector size]."    << endl;
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
         "<file>, use 'faust/dsp/fastmath.cpp' when file is 'def', assume functions are defined in the architecture file when file is 'arch'."
         << endl;
    cout << tab
         << "-mapp       --math-approximation        simpler/faster versions of 'floor/ceil/fmod/remainder' functions."
         << endl;
    cout << tab
         << "-noreprc    --no-reprc                  (Rust only) Don't force dsp struct layout to follow C ABI."
         << endl;
    cout << tab << "-ns <name>  --namespace <name>          generate C++ or D code in a namespace <name>." << endl;
    
    cout << tab << "-vhdl-trace    --vhdl-trace             activate trace." << endl;
    cout << tab << "-vhdl-float    --vhdl-float             uses IEEE-754 format for samples instead of fixed point." << endl;
    cout << tab << "-vhdl-components <file> --vhdl-components <file>    path to a file describing custom components for the VHDL backend." << endl;
    cout << tab << "-fpga-mem <n>  --fpga-mem <n>           FPGA block ram max size, used in -os2/-os3 mode." << endl;
    
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
    cout << tab << "-sc        --scaled-svg                 automatic scalable SVG." << endl;
    
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
    cout << tab
         << "-me         --math-exceptions           check / for 0 as denominator and remainder, fmod, sqrt, log10, "
         "log, acos, asin functions domain."
         << endl;
    cout << tab << "-sts        --strict-select             generate strict code for 'selectX' even for stateless branches (both are computed)." << endl;
    cout << tab << "-wall       --warning-all               print all warnings." << endl;
    cout << tab << "-t <sec>    --timeout <sec>             abort compilation after <sec> seconds (default 120)."
         << endl;
    
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

void global::printLibDir()
{
    cout << gFaustRootDir << kPSEP << LIBDIR << endl;
}
void global::printIncludeDir()
{
    cout << gFaustRootDir << kPSEP << "include" << endl;
}
void global::printArchDir()
{
    cout << gFaustRootDir << kPSEP << "share" << kPSEP << "faust" << endl;
}
void global::printDspDir()
{
    cout << gFaustRootDir << kPSEP << "share" << kPSEP << "faust" << endl;
}
void global::printPaths()
{
    cout << "FAUST dsp library paths:" << endl;
    for (const auto& path : gImportDirList) cout << path << endl;
    cout << "\nFAUST architectures paths:" << endl;
    for (const auto& path : gArchitectureDirList) cout << path << endl;
    cout << endl;
}

void global::printDirectories()
{
    if (gHelpSwitch) {
        printHelp();
        throw faustexception();
    }
    if (gVersionSwitch) {
        printVersion();
        throw faustexception();
    }
    if (gLibDirSwitch) {
        printLibDir();
        throw faustexception();
    }
    if (gIncludeDirSwitch) {
        printIncludeDir();
        throw faustexception();
    }
    if (gArchDirSwitch) {
        printArchDir();
        throw faustexception();
    }
    if (gDspDirSwitch) {
        printDspDir();
        throw faustexception();
    }
    if (gPathListSwitch) {
        printPaths();
        throw faustexception();
    }
}

// For box/sig generation
void global::clear()
{
    gBoxCounter = 0;
    gBoxTable.clear();
    gBoxTrace.clear();
    
    gSignalCounter = 0;
    gSignalTable.clear();
    gSignalTrace.clear();
}

// Memory management
void Garbageable::cleanup()
{
    list<Garbageable*>::iterator it;

    // Here removing the deleted pointer from the list is pointless
    // and takes time, thus we don't do it.
    global::gHeapCleanup = true;
    for (it = global::gObjectTable.begin(); it != global::gObjectTable.end(); it++) {
#ifdef _WIN32
        // Hack : "this" and actual pointer are not the same: destructor cannot be called...
        Garbageable::operator delete(*it);
#else
        delete (*it);
#endif
    }

    // Reset to default state
    global::gObjectTable.clear();
    global::gHeapCleanup = false;
}

void* Garbageable::operator new(size_t size)
{
    // HACK : add 16 bytes to avoid unsolved memory smashing bug...
    Garbageable* res = (Garbageable*)malloc(size + 16);
    global::gObjectTable.push_front(res);
    return res;
}

void Garbageable::operator delete(void* ptr)
{
    // We may have cases when a pointer will be deleted during
    // a compilation, thus the pointer has to be removed from the list.
    if (!global::gHeapCleanup) {
        global::gObjectTable.remove(static_cast<Garbageable*>(ptr));
    }
    free(ptr);
}

void* Garbageable::operator new[](size_t size)
{
    // HACK : add 16 bytes to avoid unsolved memory smashing bug...
    Garbageable* res = (Garbageable*)malloc(size + 16);
    global::gObjectTable.push_front(res);
    return res;
}

void Garbageable::operator delete[](void* ptr)
{
    // We may have cases when a pointer will be deleted during
    // a compilation, thus the pointer has to be removed from the list.
    if (!global::gHeapCleanup) {
        global::gObjectTable.remove(static_cast<Garbageable*>(ptr));
    }
    free(ptr);
}

// Threaded calls API
void callFun(threaded_fun fun, void* arg)
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
    faustassert(pthread_join(thread, nullptr) == 0);
    faustassert(pthread_attr_destroy(&attr) == 0);
#endif
}
