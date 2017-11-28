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

#include <limits.h>

#include "global.hh"
#include "sourcereader.hh"
#include "tree.hh"
#include "absprim.hh"
#include "acosprim.hh"
#include "tanprim.hh"
#include "sqrtprim.hh"
#include "sinprim.hh"
#include "rintprim.hh"
#include "remainderprim.hh"
#include "powprim.hh"
#include "minprim.hh"
#include "maxprim.hh" 
#include "logprim.hh"
#include "log10prim.hh"
#include "fmodprim.hh" 
#include "floorprim.hh"
#include "expprim.hh"
#include "exp10prim.hh"
#include "cosprim.hh"
#include "ceilprim.hh"
#include "atanprim.hh"
#include "atan2prim.hh"
#include "asinprim.hh"
#include "ftzprim.hh"
#include "binop.hh"
#include "instructions.hh"

#ifdef WIN32
#pragma warning (disable: 4996)
#endif

#if ASMJS_BUILD
#include "asmjs_instructions.hh"
#endif

#if C_BUILD
#include "c_code_container.hh"
#endif

#if CPP_BUILD
#include "cpp_code_container.hh"
#endif

#if FIR_BUILD
#include "fir_code_container.hh"
#endif

#if INTERP_BUILD
#include "interpreter_instructions.hh"
#endif

#if JAVA_BUILD
#include "java_code_container.hh"
#endif

#if JS_BUILD
#include "js_code_container.hh"
#endif

#if RUST_BUILD
#include "rust_code_container.hh"
#endif

// Parser
extern FILE* yyin;
extern const char* yyfilename;

// CG globals
list<Garbageable*> global::gObjectTable;
bool global::gHeapCleanup = false;
  
/*
faust1 uses a loop size of 512, but 512 makes faust2 crash (stack allocation error).
So we use a lower value here.
*/

global::global():TABBER(1), gLoopDetector(1024, 400), gNextFreeColor(1)
{
    CTree::init();
    Symbol::init();
    
    EVALPROPERTY = symbol("EvalProperty");
    PMPROPERTYNODE = symbol("PMPROPERTY");
    
    gResult = 0;
    gResult2 = 0;
    gExpandedDefList = 0;
    
    gDetailsSwitch = false;
    gDrawSignals = false;
    gShadowBlur = false;        // note: svg2pdf doesn't like the blur filter
    gScaledSVG = false;
    gStripDocSwitch = false;	// Strip <mdoc> content from doc listings.
    gFoldThreshold = 25;
    gMaxNameSize = 40;
    gSimpleNames = false;
    gSimplifyDiagrams = false;
    gLessTempSwitch = false;
    gMaxCopyDelay = 16;

    gVectorSwitch = false;
    gDeepFirstSwitch = false;
    gVecSize = 32;
    gVectorLoopVariant = 0;
    gVecLoopSize = 0;

    gOpenMPSwitch = false;
    gOpenMPLoop = false;
    gSchedulerSwitch = false;
    gOpenCLSwitch = false;
    gCUDASwitch = false;
    gGroupTaskSwitch = false;
    gFunTaskSwitch = false;

    gUIMacroSwitch = false;
    gDumpNorm = false;
    gFTZMode = 0;

    gFloatSize = 1;

    gPrintFileListSwitch = false;
    gInlineArchSwitch = false;

    gDSPStruct = false;
    gLightMode = false;

    gClassName = "mydsp";
 
    gDSPFactory = 0;
    
    gInputString = 0;
    
    // Backend configuration : default values
    gGenerateSelectWithIf = true;
    gAllowForeignFunction = true;
    gComputeIOTA = false;
    gFAUSTFLOATToInternal = false;
    gInPlace = false;
    gHasExp10 = false;
    gLoopVarInBytes = false;
    gWaveformInDSP = false;
    gHasTeeLocal = false;
    gFastMath = false;
    gFastMathLib = "default";
    
    // Fastmath mapping float version
    gFastMathLibTable["acosf"] = "fast_acosf";
    gFastMathLibTable["asinf"] = "fast_asinf";
    gFastMathLibTable["atanf"] = "fast_atanf";
    gFastMathLibTable["atan2f"] = "fast_atan2f";
    gFastMathLibTable["ceilf"] = "fast_ceilf";
    gFastMathLibTable["cosf"] = "fast_cosf";
    gFastMathLibTable["expf"] = "fast_expf";
    gFastMathLibTable["exp2f"] = "fast_exp2f";
    gFastMathLibTable["exp10f"] = "fast_exp10f";
    gFastMathLibTable["floorf"] = "fast_floorf";
    gFastMathLibTable["fmodf"] = "fast_fmodf";
    gFastMathLibTable["logf"] = "fast_logf";
    gFastMathLibTable["log2f"] = "fast_log2f";
    gFastMathLibTable["log10f"] = "fast_log10f";
    gFastMathLibTable["powf"] = "fast_powf";
    gFastMathLibTable["remainderf"] = "fast_remainderf";
    gFastMathLibTable["roundf"] = "fast_roundf";
    gFastMathLibTable["sinf"] = "fast_sinf";
    gFastMathLibTable["sqrtf"] = "fast_sqrtf";
    gFastMathLibTable["tanf"] = "fast_tanf";
    
    // Fastmath mapping double version
    gFastMathLibTable["acos"] = "fast_acos";
    gFastMathLibTable["asin"] = "fast_asin";
    gFastMathLibTable["atan"] = "fast_atan";
    gFastMathLibTable["atan2"] = "fast_atan2";
    gFastMathLibTable["ceil"] = "fast_ceil";
    gFastMathLibTable["cos"] = "fast_cos";
    gFastMathLibTable["exp"] = "fast_exp";
    gFastMathLibTable["exp2"] = "fast_exp2";
    gFastMathLibTable["exp10"] = "fast_exp10";
    gFastMathLibTable["floor"] = "fast_floor";
    gFastMathLibTable["fmod"] = "fast_fmod";
    gFastMathLibTable["log"] = "fast_log";
    gFastMathLibTable["log2"] = "fast_log2";
    gFastMathLibTable["log10"] = "fast_log10";
    gFastMathLibTable["pow"] = "fast_pow";
    gFastMathLibTable["remainder"] = "fast_remainder";
    gFastMathLibTable["round"] = "fast_round";
    gFastMathLibTable["sin"] = "fast_sin";
    gFastMathLibTable["sqrt"] = "fast_sqrt";
    gFastMathLibTable["tan"] = "fast_tan";
    
    gLstDependenciesSwitch	= true; ///< mdoc listing management.
    gLstMdocTagsSwitch		= true; ///< mdoc listing management.
    gLstDistributedSwitch	= true; ///< mdoc listing management.
    
    gLatexDocSwitch = true;		// Only LaTeX outformat is handled for the moment.
    
    gErrorCount = 0;
    
    gFileNum = 0;
    
    gCountInferences = 0;
    gCountMaximal = 0;
    
    gDummyInput = 10000;
    
    gBoxSlotNumber = 0;
    gMemoryManager = false;

	gOccurrences = 0;
	gFoldingFlag = false;
	gDevSuffix = 0;
    
    gAbsPrim = new AbsPrim();
    gAcosPrim = new AcosPrim();
    gTanPrim = new TanPrim();
    gSqrtPrim = new SqrtPrim();
    gSinPrim = new SinPrim();
    gRintPrim = new RintPrim();
    gRemainderPrim = new RemainderPrim();
    gPowPrim = new PowPrim();
    gMinPrim = new MinPrim();
    gMaxPrim = new MaxPrim();
    gLogPrim = new LogPrim();
    gLog10Prim = new Log10Prim();
    gFmodPrim = new FmodPrim();
    gFloorPrim = new FloorPrim();
    gExpPrim = new ExpPrim();
    gExp10Prim = new Exp10Prim();
    gCosPrim = new CosPrim();
    gCeilPrim = new CeilPrim();
    gAtanPrim = new AtanPrim();
    gAtan2Prim = new Atan2Prim();
    gAsinPrim = new AsinPrim();
    gFtzPrim = new FtzPrim();
    
    BOXIDENT = symbol("BoxIdent");
    BOXCUT = symbol("BoxCut");
    BOXWAVEFORM = symbol("BoxWaveform");
    BOXWIRE = symbol("BoxWire");
    BOXSLOT = symbol("BoxSlot");
    BOXSYMBOLIC = symbol("BoxSymbolic");
    BOXSEQ = symbol("BoxSeq");
    BOXPAR = symbol("BoxPar");
    BOXREC = symbol("BoxRec");
    BOXSPLIT = symbol("BoxSplit");
    BOXMERGE = symbol("BoxMerge");
    BOXIPAR = symbol("BoxIPar");
    BOXISEQ = symbol("BoxISeq");
    BOXISUM = symbol("BoxISum");
    BOXIPROD = symbol("BoxIProd");
    BOXABSTR = symbol("BoxAbstr");
    BOXAPPL = symbol("BoxAppl");
    CLOSURE = symbol("Closure");
    BOXERROR = symbol("BoxError");
    BOXACCESS = symbol("BoxAccess");
    BOXWITHLOCALDEF = symbol("BoxWithLocalDef");
    BOXMODIFLOCALDEF = symbol("BoxModifLocalDef");
    BOXENVIRONMENT = symbol("BoxEnvironment");
    BOXCOMPONENT = symbol("BoxComponent");
    BOXLIBRARY = symbol("BoxLibrary");
    IMPORTFILE = symbol("ImportFile");
    BOXPRIM0 = symbol("BoxPrim0");
    BOXPRIM1 = symbol("BoxPrim1");
    BOXPRIM2 = symbol("BoxPrim2");
    BOXPRIM3 = symbol("BoxPrim3");
    BOXPRIM4 = symbol("BoxPrim4");
    BOXPRIM5 = symbol("BoxPrim5");
    BOXFFUN = symbol("BoxFFun");
    BOXFCONST = symbol("BoxFConst");
    BOXFVAR = symbol("BoxFVar");
    BOXBUTTON = symbol("BoxButton");
    BOXCHECKBOX = symbol("BoxCheckbox");
    BOXHSLIDER = symbol("BoxHSlider");
    BOXVSLIDER = symbol("BoxVSlider");
    BOXNUMENTRY = symbol("BoxNumEntry");
    BOXHGROUP = symbol("BoxHGroup");
    BOXVGROUP = symbol("BoxVGroup");
    BOXTGROUP = symbol("BoxTGroup");
    BOXHBARGRAPH = symbol("BoxHBargraph");
    BOXVBARGRAPH = symbol("BoxVBargraph");
    BOXCASE = symbol("BoxCase");
    BOXPATMATCHER = symbol("BoxPatMatcher");
    BOXPATVAR = symbol("BoxPatVar");
    BOXINPUTS = symbol("BoxInputs");
    BOXOUTPUTS = symbol("BoxOutputs");
    BOXSOUNDFILE = symbol("boxSoundfile");
 
    DOCEQN = symbol("DocEqn");
    DOCDGM = symbol("DocDgm");
    DOCNTC = symbol("DocNtc");
    DOCLST = symbol("DocLst");
    DOCMTD = symbol("DocMtd");
    DOCTXT = symbol("DocTxt");
    BARRIER = symbol("BARRIER");
    UIFOLDER = symbol("uiFolder");
    UIWIDGET = symbol("uiWidget");
    PATHROOT = symbol("/");
    PATHPARENT = symbol("..");
    PATHCURRENT = symbol(".");
    FFUN = symbol("ForeignFunction");
    
    SIGINPUT = symbol("sigInput");
    SIGOUTPUT = symbol("sigOutput");
    SIGDELAY1 = symbol("sigDelay1");
    SIGFIXDELAY = symbol("sigFixDelay");
    SIGPREFIX = symbol("sigPrefix");
    SIGIOTA = symbol("sigIota");
    SIGRDTBL = symbol("SigRDTbl");
    SIGWRTBL = symbol("SigWRTbl");
    SIGTABLE = symbol("SigTable");
    SIGGEN = symbol("SigGen");
    SIGDOCONSTANTTBL = symbol("SigDocConstantTbl");
    SIGDOCWRITETBL = symbol("SigDocWriteTbl");
    SIGDOCACCESSTBL = symbol("SigDocAccessTbl");
    SIGSELECT2 = symbol("SigSelect2");
    SIGSELECT3 = symbol("SigSelect3");
    SIGBINOP = symbol("SigBinOp");
    SIGFFUN = symbol("SigFFun");
    SIGFCONST = symbol("SigFConst");
    SIGFVAR = symbol("SigFVar");
    SIGPROJ = symbol("SigProj");
    SIGINTCAST = symbol("sigIntCast");
    SIGFLOATCAST = symbol("sigFloatCast");
    SIGBUTTON = symbol("SigButton");
    SIGCHECKBOX = symbol("SigCheckbox");
    SIGWAVEFORM = symbol("SigWaveform");
    SIGHSLIDER = symbol("SigHSlider");
    SIGVSLIDER = symbol("SigVSlider");
    SIGNUMENTRY = symbol("SigNumEntry");
    SIGHBARGRAPH = symbol("SigHBargraph");
    SIGVBARGRAPH = symbol("SigVBargraph");
    SIGATTACH = symbol("sigAttach");
    SIGENABLE = symbol("sigEnable");
    SIGCONTROL = symbol("sigControl");
    SIGSOUNDFILE = symbol("sigSoundfile");
    SIGSOUNDFILELENGTH = symbol("sigSoundfileLength");
    SIGSOUNDFILERATE = symbol("sigSoundfileRate");
    SIGSOUNDFILECHANNEL = symbol("sigSoundfileChannel");
    SIGTUPLE = symbol("SigTuple");
    SIGTUPLEACCESS = symbol("SigTupleAccess");
    SIMPLETYPE = symbol("SimpleType");
    TABLETYPE = symbol("TableType");
    TUPLETTYPE = symbol("TupletType");
      
    // recursive trees
    DEBRUIJN = symbol("DEBRUIJN");
    DEBRUIJNREF = symbol("DEBRUIJNREF");
    SUBSTITUTE = symbol("SUBSTITUTE");
  
    SYMREC = symbol("SYMREC");
    SYMRECREF = symbol("SYMRECREF");
    SYMLIFTN = symbol("LIFTN");
    
    // Use real values 
    gMachineFloatSize = sizeof(float);
    gMachineInt32Size = sizeof(int);
    gMachineInt64Size = sizeof(long int);
    gMachineDoubleSize = sizeof(double);
    gMachineBoolSize = sizeof(bool);
    gMachinePtrSize = sizeof(void*);
    
    gMachineMaxStackSize = MAX_STACK_SIZE;
    gOutputLang = "";
    
#if ASMJS_BUILD
    gASMJSVisitor = 0;  // Will be (possibly) allocated in ASMJS backend
#endif
    
#if WASM_BUILD
    gWASMVisitor = 0;   // Will be (possibly) allocated in WebAssembly backend
    gWASTVisitor = 0;   // Will be (possibly) allocated in WebAssembly backend
#endif
    
#if INTERP_BUILD
    gInterpreterVisitor = 0; // Will be (possibly) allocated in Interp backend
#endif
    
    gHelpSwitch = false;
    gVersionSwitch = false;
    gGraphSwitch = false;
    gDrawPSSwitch = false;
    gDrawSVGSwitch = false;
    gPrintXMLSwitch = false;
    gPrintJSONSwitch = false;
    gPrintDocSwitch = false;
    gBalancedSwitch = 0;
    gArchFile = "";
    gExportDSP = false;

    gTimeout = 120;            // time out to abort compiler (in seconds)
    
    // Globals to transfer results in thread based evaluation
    gProcessTree = 0;
    gLsignalsTree = 0;
    gNumInputs = 0;
    gNumOutputs = 0;
    gErrorMessage = "";
    
    // By default use "cpp" output
    gOutputLang = (getenv("FAUST_DEFAULT_BACKEND")) ? string(getenv("FAUST_DEFAULT_BACKEND")) : "cpp";
}

// Done after contructor since part of the following allocations need the "global" object to be fully built

void global::init()
{
    gPureRoutingProperty = new property<bool>();
    gSymbolicBoxProperty = new property<Tree>();
    gSimplifiedBoxProperty = new property<Tree>();
    gSymListProp = new property<Tree>();
    
    // Essential predefined types
    
    gMemoizedTypes = new property<AudioType*>();
    gAllocationCount = 0;
    gEnableFlag = true;
  
    TINT = makeSimpleType(kInt, kKonst, kComp, kVect, kNum, interval());
    TREAL = makeSimpleType(kReal, kKonst, kComp, kVect, kNum, interval());

    TKONST = makeSimpleType(kInt, kKonst, kComp, kVect, kNum, interval());
    TBLOCK = makeSimpleType(kInt, kBlock, kComp, kVect, kNum, interval());
    TSAMP = makeSimpleType(kInt, kSamp, kComp, kVect, kNum, interval());

    TCOMP = makeSimpleType(kInt, kKonst, kComp, kVect, kNum, interval());
    TINIT = makeSimpleType(kInt, kKonst, kInit, kVect, kNum, interval());
    TEXEC = makeSimpleType(kInt, kKonst, kExec, kVect, kNum, interval());

    // more predefined types

    TINPUT = makeSimpleType(kReal, kSamp, kExec, kVect, kNum, interval());
    TGUI = makeSimpleType(kReal, kBlock,kExec, kVect, kNum, interval());
    TGUI01 = makeSimpleType(kReal, kBlock,kExec, kVect, kNum, interval(0,1));
    INT_TGUI = makeSimpleType(kInt,  kBlock,kExec, kVect, kNum, interval());

    TREC = makeSimpleType(kInt, kSamp, kInit, kScal, kNum, interval());
    
    // predefined symbols CONS and NIL
    CONS = symbol("cons");
    NIL = symbol("nil");
    
    // predefined nil tree
    nil = tree(NIL);
    
    PROCESS = symbol("process"); 
      
    BOXTYPEPROP = tree(symbol("boxTypeProp"));
    NUMERICPROPERTY = tree(symbol("NUMERICPROPERTY"));
    DEFLINEPROP = tree(symbol("DefLineProp"));
    USELINEPROP = tree(symbol("UseLineProp"));
    SIMPLIFIED = tree(symbol("sigSimplifiedProp"));
    DOCTABLES = tree(symbol("DocTablesProp"));
    NULLENV = tree(symbol("NullRenameEnv"));
    COLORPROPERTY = tree(symbol("ColorProperty"));
    ORDERPROP = tree(symbol("OrderProp"));
    RECURSIVNESS = tree(symbol("RecursivnessProp"));
    NULLTYPEENV = tree(symbol("NullTypeEnv"));
    RECDEF = tree(symbol("RECDEF"));
    DEBRUIJN2SYM = tree(symbol("deBruijn2Sym"));
    DEFNAMEPROPERTY = tree(symbol("DEFNAMEPROPERTY"));
    NICKNAMEPROPERTY = tree(symbol("NICKNAMEPROPERTY"));
    BCOMPLEXITY = tree("BCOMPLEXITY");
    LETRECBODY = boxIdent("RECURSIVEBODY");
    
    PROPAGATEPROPERTY = symbol("PropagateProperty");
    
    // yyfilename is defined in errormsg.cpp but must be redefined at each compilation.
    yyfilename = "";
    yyin = 0;
    
    gLatexheaderfilename = "latexheader.tex";
    gDocTextsDefaultFile = "mathdoctexts-default.txt";
    
    // Init type size table
    gTypeSizeMap[Typed::kFloat] = gMachineFloatSize;
    gTypeSizeMap[Typed::kFloat_ptr] = gMachinePtrSize;
    gTypeSizeMap[Typed::kFloat_vec] = gMachineFloatSize * gVecSize;
    gTypeSizeMap[Typed::kFloat_vec_ptr] = gMachinePtrSize;
    
    gTypeSizeMap[Typed::kInt32] = gMachineInt32Size;
    gTypeSizeMap[Typed::kInt32_ptr] = gMachinePtrSize;
    gTypeSizeMap[Typed::kInt32_vec] = gMachineInt32Size * gVecSize;
    gTypeSizeMap[Typed::kInt32_vec_ptr] = gMachinePtrSize;
    
    gTypeSizeMap[Typed::kInt64] = gMachineInt64Size;
    gTypeSizeMap[Typed::kInt64_ptr] = gMachinePtrSize;
    gTypeSizeMap[Typed::kInt64_vec] = gMachineInt64Size * gVecSize;
    gTypeSizeMap[Typed::kInt64_vec_ptr] = gMachinePtrSize;
    
    gTypeSizeMap[Typed::kDouble] = gMachineDoubleSize;
    gTypeSizeMap[Typed::kDouble_ptr] = gMachinePtrSize;
    gTypeSizeMap[Typed::kDouble_vec] = gMachineDoubleSize * gVecSize;
    gTypeSizeMap[Typed::kDouble_vec_ptr] = gMachinePtrSize;
    
    gTypeSizeMap[Typed::kBool] = gMachineBoolSize;
    gTypeSizeMap[Typed::kBool_ptr] = gMachinePtrSize;
    gTypeSizeMap[Typed::kBool_vec] = gMachineBoolSize * gVecSize;
    gTypeSizeMap[Typed::kBool_vec_ptr] = gMachinePtrSize;
    
    // Takes the type of internal real
    gTypeSizeMap[Typed::kFloatMacro] = gTypeSizeMap[itfloat()];
    gTypeSizeMap[Typed::kFloatMacro_ptr] = gMachinePtrSize;
    
    gTypeSizeMap[Typed::kVoid_ptr] = gMachinePtrSize;
    gTypeSizeMap[Typed::kVoid_ptr_ptr] = gMachinePtrSize;
    
    gTypeSizeMap[Typed::kObj_ptr] = gMachinePtrSize;
    
    gCurrentLocal = setlocale(LC_ALL, NULL);
    if (gCurrentLocal != NULL) {
        gCurrentLocal = strdup(gCurrentLocal);
    }
    
    // Setup standard "C" local 
    // (workaround for a bug in bitcode generation : http://lists.cs.uiuc.edu/pipermail/llvmbugs/2012-May/023530.html)
    setlocale(LC_ALL, "C");
    
    // source file injection
    gInjectFlag = false;    // inject an external source file into the architecture file
    gInjectFile  = "";      // instead of a compiled dsp file
}

void global::printCompilationOptions(ostream& dst)
{
    dst << gOutputLang << ", ";
    if (gSchedulerSwitch) {
        dst << "-sch"
        << " -vs " << gVecSize
        << ((gFunTaskSwitch) ? " -fun" : "")
        << ((gGroupTaskSwitch) ? " -g" : "")
        << ((gDeepFirstSwitch) ? " -dfs" : "")
        << ((gFloatSize == 2) ? " -double" : (gFloatSize == 3) ? " -quad" : "")
        << " -ftz " << gFTZMode
        << ((gMemoryManager) ? " -mem" : "");
    } else if (gVectorSwitch) {
        dst << "-vec" << " -lv " << gVectorLoopVariant
        << " -vs " << gVecSize
        << ((gFunTaskSwitch) ? " -fun" : "")
        << ((gGroupTaskSwitch) ? " -g" : "")
        << ((gDeepFirstSwitch) ? " -dfs" : "")
        << ((gFloatSize == 2) ? " -double" : (gFloatSize == 3) ? " -quad" : "")
        << " -ftz " << gFTZMode
        << ((gMemoryManager) ? " -mem" : "");
    } else if (gOpenMPSwitch) {
        dst << "-omp" << " -vs " << gVecSize
        << " -vs " << gVecSize
        << ((gFunTaskSwitch) ? " -fun" : "")
        << ((gGroupTaskSwitch) ? " -g" : "")
        << ((gDeepFirstSwitch) ? " -dfs" : "")
        << ((gFloatSize == 2) ? " -double" : (gFloatSize == 3) ? " -quad" : "")
        << " -ftz " << gFTZMode
        << ((gMemoryManager) ? " -mem" : "");
    } else {
        dst << ((gFloatSize == 1) ? "-scal" : ((gFloatSize == 2) ? "-double" : (gFloatSize == 3) ? "-quad" : ""))
        << " -ftz " << gFTZMode
        << ((gMemoryManager) ? " -mem" : "");
    }
}


global::~global()
{
    Garbageable::cleanup();
    BasicTyped::cleanup();
    DeclareVarInst::cleanup();
    setlocale(LC_ALL, gCurrentLocal);
    free(gCurrentLocal);
    
    // Cleanup
#if C_BUILD
    CInstVisitor::cleanup();
#endif
#if CPP_BUILD
    CPPInstVisitor::cleanup();
#endif
#if FIR_BUILD
    FIRInstVisitor::cleanup();
#endif
#if JAVA_BUILD
    JAVAInstVisitor::cleanup();
#endif
#if JS_BUILD
    JAVAScriptInstVisitor::cleanup();
#endif
#if RUST_BUILD
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
        faustexception::gJSExceptionMsg = NULL;
    }
#endif
    delete gGlobal;
    gGlobal = NULL;
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
	int n = gIDCounters[prefix];
	gIDCounters[prefix] = n+1;
	return subst("$0$1", prefix, T(n));
}

Garbageable::Garbageable()
{}

Garbageable::~Garbageable()
{}

void Garbageable::cleanup()
{
    std::list<Garbageable*>::iterator it;

    // Here removing the deleted pointer from the list is pointless 
    // and takes time, thus we don't do it.
    
    global::gHeapCleanup = true;
    for (it = global::gObjectTable.begin(); it != global::gObjectTable.end(); it++) {
	#ifdef _WIN32
		// Hack : "this" and actual pointer are not the same: destructor cannot be called...
		Garbageable::operator delete(*it);
	#else
		delete(*it);
  	#endif
    }
    
    global::gObjectTable.clear();
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

