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


map<string, bool>	gDocNoticeFlagMap;

map<string, string>	gDocNoticeStringMap;
set<string>			gDocNoticeKeySet;

extern map<string, string>		gDocAutodocStringMap;

extern string		gMasterName;

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
	
	if (! gDocNoticeStringMap.empty() ) {
		
		//cerr << "Documentator : printDocNotice : printing..." << endl;
		
		docout << endl << "\\begin{itemize}" << endl;
		
		/* Presentations. */
		docout << "\t\\item " << gDocAutodocStringMap["autontctext"]	<< endl;
		if(gDocNoticeFlagMap["faustapply"])			docout << "\t\\item " << gDocNoticeStringMap["faustapply"]	<< endl;
		if(gDocNoticeFlagMap["faustpresentation"])	docout << "\t\\item " << gDocNoticeStringMap["faustpresentation"]	<< endl;
		if(gDocNoticeFlagMap["causality"])			docout << "\t\\item " << gDocNoticeStringMap["causality"]	<< endl;
		if(gDocNoticeFlagMap["blockdiagrams"])		docout << "\t\\item " << gDocNoticeStringMap["blockdiagrams"]	<< endl;
		
		/* Naming conventions of variables and functions. */
		if(gDocNoticeFlagMap["foreignfun"])		docout << "\t\\item " << gDocNoticeStringMap["foreignfun"]	<< endl;
		if(gDocNoticeFlagMap["intcast"])		docout << "\t\\item " << gDocNoticeStringMap["intcast"]	<< endl;
		
		/* Integer arithmetic into a tabular environment. */
		if(gDocNoticeFlagMap["intplus"] || 
		   gDocNoticeFlagMap["intminus"] || 
		   gDocNoticeFlagMap["intmult"] || 
		   gDocNoticeFlagMap["intdiv"] || 
		   gDocNoticeFlagMap["intand"] || 
		   gDocNoticeFlagMap["intor"] || 
		   gDocNoticeFlagMap["intxor"])
		{
			gDocNoticeFlagMap["operators"]		= true;
			gDocNoticeFlagMap["optabtitle"]		= true;
			gDocNoticeFlagMap["integerops"]		= true;
			
			docout << "\t\\item " << endl;
			docout << "\t\t" << gDocNoticeStringMap["operators"] << endl;
			docout << "\t\\begin{center}" << endl;
			docout << "\t\\begin{tabular}{|c|l|l|} " << endl;
			docout << "\t\t\\hline " << endl;
			docout << "\t\t" << gDocNoticeStringMap["optabtitle"]	<< endl;
			docout << "\t\t\\hline " << endl;
			if(gDocNoticeFlagMap["intplus"])	docout << "\t\t" << gDocNoticeStringMap["intplus"]	<< endl;
			if(gDocNoticeFlagMap["intminus"])	docout << "\t\t" << gDocNoticeStringMap["intminus"]	<< endl;
			if(gDocNoticeFlagMap["intmult"])	docout << "\t\t" << gDocNoticeStringMap["intmult"]	<< endl;
			if(gDocNoticeFlagMap["intdiv"])		docout << "\t\t" << gDocNoticeStringMap["intdiv"]	<< endl;
			if(gDocNoticeFlagMap["intand"])		docout << "\t\t" << gDocNoticeStringMap["intand"]	<< endl;
			if(gDocNoticeFlagMap["intor"])		docout << "\t\t" << gDocNoticeStringMap["intor"]	<< endl;
			if(gDocNoticeFlagMap["intxor"])		docout << "\t\t" << gDocNoticeStringMap["intxor"]	<< endl;
			docout << "\t\t\\hline " << endl;
			docout << "\t\\end{tabular} " << endl;
			docout << "\t\\end{center}" << endl;
			docout << "\t\t" << gDocNoticeStringMap["integerops"]	<< endl;
		}

		if(gDocNoticeFlagMap["faustdocdir"])		docout << "\t\\item " << gDocNoticeStringMap["faustdocdir"]	<< endl;

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
 * Initialize gDocNoticeKeySet, a set containing all the keywords.
 */
static void initDocNoticeKeySet() {
	
	gDocNoticeKeySet.insert("faustpresentation");
	gDocNoticeKeySet.insert("faustapply");
	gDocNoticeKeySet.insert("faustdocdir");
	gDocNoticeKeySet.insert("causality");
	gDocNoticeKeySet.insert("blockdiagrams");
	
	gDocNoticeKeySet.insert("foreignfun");
	gDocNoticeKeySet.insert("intcast");
	
	gDocNoticeKeySet.insert("operators");
	gDocNoticeKeySet.insert("optabtitle");
	gDocNoticeKeySet.insert("integerops");
	gDocNoticeKeySet.insert("intplus");
	gDocNoticeKeySet.insert("intminus");
	gDocNoticeKeySet.insert("intmult");
	gDocNoticeKeySet.insert("intdiv");
	gDocNoticeKeySet.insert("intand");
	gDocNoticeKeySet.insert("intor");
	gDocNoticeKeySet.insert("intxor");
}


/** 
 * Initialize gDocNoticeFlagMap, a map containing all the flags.
 */
static void initDocNoticeFlagMap() {
	
	for (set<string>::iterator it=gDocNoticeKeySet.begin(); it != gDocNoticeKeySet.end() ; ++it ) {
		gDocNoticeFlagMap[*it] = false;
	}
	gDocNoticeFlagMap["faustpresentation"]	= true;
	gDocNoticeFlagMap["faustapply"]			= true;
	gDocNoticeFlagMap["faustdocdir"]		= true;
	gDocNoticeFlagMap["causality"]			= true;
	gDocNoticeFlagMap["blockdiagrams"]		= true;
}

