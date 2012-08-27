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
#include "cosprim.hh"
#include "ceilprim.hh"
#include "atanprim.hh"
#include "atan2prim.hh"
#include "asinprim.hh"

#include "binop.hh"
#include "instructions.hh"

list<Garbageable*> Garbageable::gObjectTable;
bool Garbageable::gCleanup = false;
  
global::global():TABBER(1),gLoopDetector(1024, 512)
{
    CTree::init();
    Symbol::init();
    
    strcpy(gErrorMsg, "");
    
    EVALPROPERTY = symbol("EvalProperty");
    PMPROPERTYNODE = symbol("PMPROPERTY");
    
    gResult             = 0;
    gResult2            = 0;
    gExpandedDefList    = 0;
    
    gDetailsSwitch  = false;
    gDrawSignals    = false;
    gShadowBlur     = false;	// note: svg2pdf doesn't like the blur filter
    gStripDocSwitch = false;	// Strip <mdoc> content from doc listings.
    gFoldThreshold 	= 25;
    gMaxNameSize 	= 40;
    gSimpleNames 	= false;
    gSimplifyDiagrams = false;
    gLessTempSwitch = false;
    gMaxCopyDelay	= 16;

    gVectorSwitch   = false;
    gDeepFirstSwitch = false;
    gVecSize        = 32;
    gVectorLoopVariant = 0;
    gVecLoopSize = 0;

    gOpenMPSwitch   = false;
    gOpenMPLoop     = false;
    gSchedulerSwitch  = false;
    gOpenCLSwitch  = false;
    gCUDASwitch = false;
    gGroupTaskSwitch = false;
    gFunTaskSwitch = false;

    gUIMacroSwitch  = false;
    gDumpNorm       = false;

    gFloatSize = 1;

    gPrintFileListSwitch = false;
    gInlineArchSwitch = true;

    gDSPStruct = false;

    gClassName = "mydsp";

    gModule = 0;
    gInputString = 0;
    
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
    gCosPrim = new CosPrim();
    gCeilPrim = new CeilPrim();
    gAtanPrim = new AtanPrim();
    gAtan2Prim = new Atan2Prim();
    gAsinPrim = new AsinPrim();
    
    BOXIDENT = symbol ("BoxIdent");
    BOXCUT = symbol ("BoxCut");
    BOXWIRE = symbol ("BoxWire");
    BOXSLOT = symbol ("BoxSlot");
    BOXSYMBOLIC = symbol ("BoxSymbolic");
    BOXSEQ = symbol ("BoxSeq");
    BOXPAR = symbol ("BoxPar");
    BOXREC = symbol ("BoxRec");
    BOXSPLIT = symbol ("BoxSplit");
    BOXMERGE = symbol ("BoxMerge");
    BOXIPAR = symbol ("BoxIPar");
    BOXISEQ = symbol ("BoxISeq");
    BOXISUM = symbol ("BoxISum");
    BOXIPROD = symbol ("BoxIProd");
    BOXABSTR = symbol ("BoxAbstr");
    BOXAPPL = symbol ("BoxAppl");
    CLOSURE = symbol ("Closure");
    BOXERROR = symbol ("BoxError");
    BOXACCESS = symbol ("BoxAccess");
    BOXWITHLOCALDEF = symbol ("BoxWithLocalDef");
    BOXMODIFLOCALDEF = symbol ("BoxModifLocalDef");
    BOXENVIRONMENT = symbol ("BoxEnvironment");
    BOXCOMPONENT = symbol ("BoxComponent");
    BOXLIBRARY = symbol ("BoxLibrary");
    IMPORTFILE = symbol ("ImportFile");
    BOXPRIM0 = symbol ("BoxPrim0");
    BOXPRIM1 = symbol ("BoxPrim1");
    BOXPRIM2 = symbol ("BoxPrim2");
    BOXPRIM3 = symbol ("BoxPrim3");
    BOXPRIM4 = symbol ("BoxPrim4");
    BOXPRIM5 = symbol ("BoxPrim5");
    BOXFFUN = symbol ("BoxFFun");
    BOXFCONST = symbol ("BoxFConst");
    BOXFVAR = symbol ("BoxFVar");
    BOXBUTTON = symbol ("BoxButton");
    BOXCHECKBOX = symbol ("BoxCheckbox");
    BOXHSLIDER = symbol ("BoxHSlider");
    BOXVSLIDER = symbol ("BoxVSlider");
    BOXNUMENTRY = symbol ("BoxNumEntry");
    BOXHGROUP = symbol ("BoxHGroup");
    BOXVGROUP = symbol ("BoxVGroup");
    BOXTGROUP = symbol ("BoxTGroup");
    BOXHBARGRAPH = symbol ("BoxHBargraph");
    BOXVBARGRAPH = symbol ("BoxVBargraph");
    BOXCASE = symbol ("BoxCase");
    BOXPATMATCHER = symbol ("BoxPatMatcher");
    BOXPATVAR = symbol ("BoxPatVar");
    DOCEQN = symbol ("DocEqn");
    DOCDGM = symbol ("DocDgm");
    DOCNTC = symbol ("DocNtc");
    DOCLST = symbol ("DocLst");
    DOCMTD = symbol ("DocMtd");
    DOCTXT = symbol ("DocTxt");
    BARRIER = symbol ("BARRIER");
    UIFOLDER = symbol ("uiFolder");
    UIWIDGET = symbol ("uiWidget");
    PATHROOT = symbol ("/");
    PATHPARENT = symbol ("..");
    PATHCURRENT = symbol (".");
    FFUN = symbol ("ForeignFunction");
    
    SIGINPUT = symbol ("sigInput");
    SIGOUTPUT = symbol ("sigOutput");
    SIGDELAY1 = symbol ("sigDelay1");
    SIGFIXDELAY = symbol ("sigFixDelay");
    SIGPREFIX = symbol ("sigPrefix");
    SIGIOTA = symbol ("sigIota");
    SIGRDTBL = symbol ("SigRDTbl");
    SIGWRTBL = symbol ("SigWRTbl");
    SIGTABLE = symbol ("SigTable");
    SIGGEN = symbol ("SigGen");
    SIGDOCONSTANTTBL = symbol ("SigDocConstantTbl");
    SIGDOCWRITETBL = symbol ("SigDocWriteTbl");
    SIGDOCACCESSTBL = symbol ("SigDocAccessTbl");
    SIGSELECT2 = symbol ("SigSelect2");
    SIGSELECT3 = symbol ("SigSelect3");
    SIGBINOP = symbol ("SigBinOp");
    SIGFFUN = symbol ("SigFFun");
    SIGFCONST = symbol ("SigFConst");
    SIGFVAR = symbol ("SigFVar");
    SIGPROJ = symbol ("SigProj");
    SIGINTCAST = symbol ("sigIntCast");
    SIGFLOATCAST = symbol ("sigFloatCast");
    SIGBUTTON = symbol ("SigButton");
    SIGCHECKBOX = symbol ("SigCheckbox");
    SIGHSLIDER = symbol ("SigHSlider");
    SIGVSLIDER = symbol ("SigVSlider");
    SIGNUMENTRY = symbol ("SigNumEntry");
    SIGHBARGRAPH = symbol ("SigHBargraph");
    SIGVBARGRAPH = symbol ("SigVBargraph");
    SIGATTACH = symbol ("sigAttach");
    SIGTUPLE = symbol ("SigTuple");
    SIGTUPLEACCESS = symbol ("SigTupleAccess");
    SIMPLETYPE = symbol ("SimpleType");
    TABLETYPE = symbol ("TableType");
    TUPLETTYPE = symbol ("TupletType");
      
    // recursive trees
    DEBRUIJN 	= symbol ("DEBRUIJN");
    DEBRUIJNREF = symbol ("DEBRUIJNREF");
    SUBSTITUTE  = symbol ("SUBSTITUTE");
  
    SYMREC 		= symbol ("SYMREC");
    SYMRECREF 	= symbol ("SYMRECREF");
    SYMLIFTN 	= symbol ("LIFTN");
}

// Done after contructor since part of the following allocations need the "global" object to be fully built

void global::init()
{
    gPureRoutingProperty = new property<bool>();
    gSymbolicBoxProperty = new property<Tree>();
    gSimplifiedBoxProperty = new property<Tree>();
    gSymListProp = new property<Tree>();
    gMemoizedTypes = new property<AudioType*>();

    TINT 	= makeSimpleType(kInt, kKonst, kComp, kVect, kNum, interval());
    TREAL 	= makeSimpleType(kReal, kKonst, kComp, kVect, kNum, interval());

    TKONST = makeSimpleType(kInt, kKonst, kComp, kVect, kNum, interval());
    TBLOCK = makeSimpleType(kInt, kBlock, kComp, kVect, kNum, interval());
    TSAMP 	= makeSimpleType(kInt, kSamp, kComp, kVect, kNum, interval());

    TCOMP 	= makeSimpleType(kInt, kKonst, kComp, kVect, kNum, interval());
    TINIT 	= makeSimpleType(kInt, kKonst, kInit, kVect, kNum, interval());
    TEXEC 	= makeSimpleType(kInt, kKonst, kExec, kVect, kNum, interval());

    // more predefined types

    TINPUT	= makeSimpleType(kReal, kSamp, kExec, kVect, kNum, interval());
    TGUI	= makeSimpleType(kReal, kBlock,kExec, kVect, kNum, interval());
    TGUI01	= makeSimpleType(kReal, kBlock,kExec, kVect, kNum, interval(0,1));
    INT_TGUI  = makeSimpleType(kInt,  kBlock,kExec, kVect, kNum, interval());

    TREC   = makeSimpleType(kInt, kSamp, kInit, kScal, kNum, interval());
    
    // predefined symbols CONS and NIL
    CONS = symbol ("cons");
    NIL  = symbol ("nil");
    
    // predefined nil tree
    nil = tree(NIL);
    
    PROCESS = symbol ("process"); 
      
    BOXTYPEPROP = tree(symbol("boxTypeProp"));
    NUMERICPROPERTY = tree(symbol("NUMERICPROPERTY"));
    DEFLINEPROP = tree(symbol("DefLineProp"));
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
}
    
global::~global()
{
    Garbageable::cleanup();
    
    CTree::init();
    Symbol::init();
    
    BasicTyped::gTypeTable.clear();
    DeclareVarInst::gVarTable.clear();
}

void global::allocate()
{
    gGlobal = new global();
    gGlobal->init();
}

void global::destroy()
{
    delete gGlobal;
}

Garbageable::Garbageable()
{
    //printf("Garbageable allocator\n");
}

Garbageable::~Garbageable()
{
    //printf("Garbageable deallocator\n");
}

void Garbageable::cleanup()
{
    //printf("Garbageable cleanup = %d \n", gObjectTable.size());
    std::list<Garbageable*>::iterator it;
    /*
    Here removing the deleted pointer from the list is pointless and takes time,
    thus we don't do it.
    */
    gCleanup = true;
    for (it = gObjectTable.begin(); it != gObjectTable.end(); it++) {
        delete(*it);
    }
    gObjectTable.clear();
}

void* Garbageable::operator new(size_t size)
{
    //printf("Garbageable new\n");
    void* res = calloc(1, size);
    gObjectTable.push_front(static_cast<Garbageable*>(res));
    return res;
}

void Garbageable::operator delete(void* ptr)
{
    //printf("Garbageable delete %x\n", ptr);
    /*
    We may have cases when a pointer will be deleted during a compilation, 
    thus the pointer has to be removed from the list.
    */
    if (!gCleanup) {
        gObjectTable.remove(static_cast<Garbageable*>(ptr));
    }
    free(ptr);
}

void* Garbageable::operator new[](size_t size)
{
    //printf("Garbageable new[]\n");
    void* res = calloc(1, size);
    gObjectTable.push_front(static_cast<Garbageable*>(res));
    return res;
}

void Garbageable::operator delete[](void* ptr)
{
    //printf("Garbageable delete[] %x\n", ptr);
    if (!gCleanup) {
        gObjectTable.remove(static_cast<Garbageable*>(ptr));
    }
    free(ptr);
}

