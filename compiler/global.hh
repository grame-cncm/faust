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
#include "tree.hh"

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
  
    global():TABBER(1)
    {
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
    }
    
    ~global()
    {
        delete gResult;
        delete gResult2;
        CTree::cleanup();
        Symbol::cleanup();
    }

};

extern global* gGlobal;

#endif