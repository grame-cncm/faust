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


#include <iostream>
#include <fstream>
#include <set>
#include <time.h>
#include <cstdlib>
#include <errno.h>

#include "doc_notice.hh"
#include "doc_lang.hh"
#include "enrobage.hh"
#include "compatibility.hh"
#include "global.hh"

static void			initDocNoticeKeySet();
static void			initDocNoticeFlagMap();

/*****************************************************************************
							Public functions
 *****************************************************************************/

/** 
 * Print the content of the notice (a string map),
 * as LaTeX items inside an itemize environment.
 *
 * @remark 
 * This function is meant to make it easier to reorder
 * the notice printing by gathering all the items.
 *
 * @param[in]	notice			The set containing the strings to print as items.
 * @param[in]	faustversion	The current version of this Faust compiler.
 * @param[out]	docout			The LaTeX output file to print into.
 */
void printDocNotice(const string& faustversion, ostream& docout) {
	
	if (! gGlobal->gDocNoticeStringMap.empty() ) {
		
		//cerr << "Documentator : printDocNotice : printing..." << endl;
		
		docout << endl << "\\begin{itemize}" << endl;
		
		/* Presentations. */
		docout << "\t\\item " << gGlobal->gDocAutodocStringMap["autontctext"]	<< endl;
		if(gGlobal->gDocNoticeFlagMap["faustapply"])			docout << "\t\\item " << gGlobal->gDocNoticeStringMap["faustapply"]	<< endl;
		if(gGlobal->gDocNoticeFlagMap["faustpresentation"])	docout << "\t\\item " << gGlobal->gDocNoticeStringMap["faustpresentation"]	<< endl;
		if(gGlobal->gDocNoticeFlagMap["causality"])			docout << "\t\\item " << gGlobal->gDocNoticeStringMap["causality"]	<< endl;
		if(gGlobal->gDocNoticeFlagMap["blockdiagrams"])		docout << "\t\\item " << gGlobal->gDocNoticeStringMap["blockdiagrams"]	<< endl;
		
		/* Naming conventions of variables and functions. */
		if(gGlobal->gDocNoticeFlagMap["foreignfun"])		docout << "\t\\item " << gGlobal->gDocNoticeStringMap["foreignfun"]	<< endl;
		if(gGlobal->gDocNoticeFlagMap["intcast"])		docout << "\t\\item " << gGlobal->gDocNoticeStringMap["intcast"]	<< endl;
		
		/* Integer arithmetic into a tabular environment. */
		if(gGlobal->gDocNoticeFlagMap["intplus"] || 
		   gGlobal->gDocNoticeFlagMap["intminus"] || 
		   gGlobal->gDocNoticeFlagMap["intmult"] || 
		   gGlobal->gDocNoticeFlagMap["intdiv"] || 
		   gGlobal->gDocNoticeFlagMap["intand"] || 
		   gGlobal->gDocNoticeFlagMap["intor"] || 
		   gGlobal->gDocNoticeFlagMap["intxor"])
		{
			gGlobal->gDocNoticeFlagMap["operators"]		= true;
			gGlobal->gDocNoticeFlagMap["optabtitle"]		= true;
			gGlobal->gDocNoticeFlagMap["integerops"]		= true;
			
			docout << "\t\\item " << endl;
			docout << "\t\t" << gGlobal->gDocNoticeStringMap["operators"] << endl;
			docout << "\t\\begin{center}" << endl;
			docout << "\t\\begin{tabular}{|c|l|l|} " << endl;
			docout << "\t\t\\hline " << endl;
			docout << "\t\t" << gGlobal->gDocNoticeStringMap["optabtitle"]	<< endl;
			docout << "\t\t\\hline " << endl;
			if(gGlobal->gDocNoticeFlagMap["intplus"])	docout << "\t\t" << gGlobal->gDocNoticeStringMap["intplus"]	<< endl;
			if(gGlobal->gDocNoticeFlagMap["intminus"])	docout << "\t\t" << gGlobal->gDocNoticeStringMap["intminus"]	<< endl;
			if(gGlobal->gDocNoticeFlagMap["intmult"])	docout << "\t\t" << gGlobal->gDocNoticeStringMap["intmult"]	<< endl;
			if(gGlobal->gDocNoticeFlagMap["intdiv"])		docout << "\t\t" << gGlobal->gDocNoticeStringMap["intdiv"]	<< endl;
			if(gGlobal->gDocNoticeFlagMap["intand"])		docout << "\t\t" << gGlobal->gDocNoticeStringMap["intand"]	<< endl;
			if(gGlobal->gDocNoticeFlagMap["intor"])		docout << "\t\t" << gGlobal->gDocNoticeStringMap["intor"]	<< endl;
			if(gGlobal->gDocNoticeFlagMap["intxor"])		docout << "\t\t" << gGlobal->gDocNoticeStringMap["intxor"]	<< endl;
			docout << "\t\t\\hline " << endl;
			docout << "\t\\end{tabular} " << endl;
			docout << "\t\\end{center}" << endl;
			docout << "\t\t" << gGlobal->gDocNoticeStringMap["integerops"]	<< endl;
		}

		if(gGlobal->gDocNoticeFlagMap["faustdocdir"])		docout << "\t\\item " << gGlobal->gDocNoticeStringMap["faustdocdir"]	<< endl;

		docout << "\\end{itemize}" << endl << endl;
	}
	//cerr << "  ... Documentator : printDocNotice : end of printing." << endl;
}


/** 
 * Dispatch initialization of notice containers,
 * after default notice file loading.
 *
 * @remark
 * The default (english) notice is already loaded at this stage
 * to ensure that all keywords will receive a definition.
 */
void initDocNotice() 
{
	initDocNoticeKeySet();
	initDocNoticeFlagMap();
}




/*****************************************************************************
								Static functions
 *****************************************************************************/


/** 
 * Initialize gGlobal->gDocNoticeKeySet, a set containing all the keywords.
 */
static void initDocNoticeKeySet() {
	
	gGlobal->gDocNoticeKeySet.insert("faustpresentation");
	gGlobal->gDocNoticeKeySet.insert("faustapply");
	gGlobal->gDocNoticeKeySet.insert("faustdocdir");
	gGlobal->gDocNoticeKeySet.insert("causality");
	gGlobal->gDocNoticeKeySet.insert("blockdiagrams");
	
	gGlobal->gDocNoticeKeySet.insert("foreignfun");
	gGlobal->gDocNoticeKeySet.insert("intcast");
	
	gGlobal->gDocNoticeKeySet.insert("operators");
	gGlobal->gDocNoticeKeySet.insert("optabtitle");
	gGlobal->gDocNoticeKeySet.insert("integerops");
	gGlobal->gDocNoticeKeySet.insert("intplus");
	gGlobal->gDocNoticeKeySet.insert("intminus");
	gGlobal->gDocNoticeKeySet.insert("intmult");
	gGlobal->gDocNoticeKeySet.insert("intdiv");
	gGlobal->gDocNoticeKeySet.insert("intand");
	gGlobal->gDocNoticeKeySet.insert("intor");
	gGlobal->gDocNoticeKeySet.insert("intxor");
}


/** 
 * Initialize gGlobal->gDocNoticeFlagMap, a map containing all the flags.
 */
static void initDocNoticeFlagMap() {
	
	for (set<string>::iterator it=gGlobal->gDocNoticeKeySet.begin(); it != gGlobal->gDocNoticeKeySet.end() ; ++it ) {
		gGlobal->gDocNoticeFlagMap[*it] = false;
	}
	gGlobal->gDocNoticeFlagMap["faustpresentation"]	= true;
	gGlobal->gDocNoticeFlagMap["faustapply"]			= true;
	gGlobal->gDocNoticeFlagMap["faustdocdir"]		= true;
	gGlobal->gDocNoticeFlagMap["causality"]			= true;
	gGlobal->gDocNoticeFlagMap["blockdiagrams"]		= true;
}

