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

#ifndef __FAUST_GLOBAL__
#define __FAUST_GLOBAL__

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <set>
#include <map>
#include <list>

#ifndef WIN32
#include <unistd.h>
#endif

#include <llvm/Module.h>
#include "sourcereader.hh"
#include "property.hh"
#include "sigtype.hh"

//#include "tree.hh"

/*
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
*/

class 	CTree;
typedef CTree* Tree;

class Symbol;
typedef Symbol* Sym;

class xtended;

class AudioType;

struct global {

    Tree 			gResult;
    Tree 			gResult2;

    SourceReader	gReader;

    map<Tree, set<Tree> >   gMetaDataSet;
    string                  gDocLang;

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
    bool            gDetailsSwitch;
    bool            gDrawSignals;
    bool            gShadowBlur;        // note: svg2pdf doesn't like the blur filter
    bool			gStripDocSwitch;	// Strip <mdoc> content from doc listings.
    int            	gFoldThreshold;
    int            	gMaxNameSize;
    bool			gSimpleNames;
    bool            gSimplifyDiagrams;
    bool			gLessTempSwitch;
    int				gMaxCopyDelay;
    string			gOutputFile;
  
    bool            gVectorSwitch;
    bool            gDeepFirstSwitch;
    int             gVecSize;
    int             gVectorLoopVariant;
    int             gVecLoopSize;

    bool            gOpenMPSwitch;
    bool            gOpenMPLoop;
    bool            gSchedulerSwitch;
    bool            gOpenCLSwitch;
    bool            gCUDASwitch;
    bool			gGroupTaskSwitch;
    bool			gFunTaskSwitch;

    bool            gUIMacroSwitch;
    bool            gDumpNorm;

    int             gFloatSize;

    bool			gPrintFileListSwitch;
    bool			gInlineArchSwitch;

    bool			gDSPStruct;

    string			gClassName;

    llvm::Module*   gModule;
    const char*     gInputString;
    
    bool			gLstDependenciesSwitch;     ///< mdoc listing management.
    bool			gLstMdocTagsSwitch;         ///< mdoc listing management.
    bool			gLstDistributedSwitch;      ///< mdoc listing management.
    
    map<string, string>		gDocMetadatasStringMap;
    set<string>				gDocMetadatasKeySet;
    
    map<string, string>		gDocAutodocStringMap;
    set<string>				gDocAutodocKeySet;
    
    map<string, bool>       gDocNoticeFlagMap;
    
    map<string, string>		gDocMathStringMap;
    
    vector<Tree>            gDocVector;				///< Contains <mdoc> parsed trees: DOCTXT, DOCEQN, DOCDGM.
    
    map<string, string>     gDocNoticeStringMap;
    set<string>             gDocNoticeKeySet;
    
    set<string>				gDocMathKeySet;
    
    bool                    gLatexDocSwitch;		// Only LaTeX outformat is handled for the moment.
    
    int                     gErrorCount;
    
    char                    gErrorMsg[256];
  
    Tabber                  TABBER;
    
    list<string>            gInputFiles;
    
    int                     gFileNum;
    
    int                     gCountInferences;
    int                     gCountMaximal;
    int                     gDummyInput;
    
    int                     gBoxSlotNumber;     ///< counter for unique slot number
    
    Tree                    BOXTYPEPROP;
    Tree                    NUMERICPROPERTY;
    Tree                    DEFLINEPROP;
    Tree                    SIMPLIFIED;
    Tree                    DOCTABLES;
    Tree                    NULLENV;
    Tree                    COLORPROPERTY;
    Tree                    ORDERPROP;
    Tree                    RECURSIVNESS;
    Tree                    NULLTYPEENV;
    Tree                    RECDEF;
    Tree                    DEBRUIJN2SYM;
    Tree                    DEFNAMEPROPERTY;
    Tree                    NICKNAMEPROPERTY;
    Tree                    BCOMPLEXITY;
    
    xtended*                gAbsPrim;
    xtended*                gAcosPrim;
    xtended*                gTanPrim;
    xtended*                gSqrtPrim;
    xtended*                gSinPrim;
    xtended*                gRintPrim;
    xtended*                gRemainderPrim;
    xtended*                gPowPrim;
    xtended*                gMinPrim;
    xtended*                gMaxPrim;
    xtended*                gLogPrim;
    xtended*                gLog10Prim;
    xtended*                gFmodPrim;
    xtended*                gFloorPrim;
    xtended*                gExpPrim;
    xtended*                gCosPrim;
    xtended*                gCeilPrim;
    xtended*                gAtanPrim;
    xtended*                gAtan2Prim;
    xtended*                gAsinPrim;
    
    Sym BOXIDENT;
    Sym BOXCUT;
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
    property<Tree>*  gSymListProp;
    
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
    Sym SIGHSLIDER;
    Sym SIGVSLIDER;
    Sym SIGNUMENTRY;
    Sym SIGHBARGRAPH;
    Sym SIGVBARGRAPH;
    Sym SIGATTACH;
    Sym SIGTUPLE;
    Sym SIGTUPLEACCESS;
    
    Sym SIMPLETYPE;
    Sym TABLETYPE;
    Sym TUPLETTYPE;
    // memoized type contruction
    property<AudioType*>* gMemoizedTypes;
    
    // Essential predefined types
    
    Type TINT;
    Type TREAL;

    Type TKONST;
    Type TBLOCK;
    Type TSAMP;

    Type TCOMP;
    Type TINIT;
    Type TEXEC;

    // more predefined types

    Type TINPUT;
    Type TGUI;
    Type TGUI01;
    Type INT_TGUI;
    
    // trying to accelerate type convergence
    Type TREC; // kVect ou kScal ?
    
    Sym CONS;
    Sym NIL;
    Tree nil;
    
    Sym PROCESS;
    
    Sym 	DEBRUIJN;
    Sym 	DEBRUIJNREF;
    Sym 	SUBSTITUTE;

    Sym 	SYMREC;
    Sym 	SYMRECREF;
    Sym 	SYMLIFTN;

  
    global();
    ~global();
    
    void init();
    
    static void allocate();
    static void destroy();
};

extern global* gGlobal;

#endif