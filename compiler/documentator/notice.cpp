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

#include "notice.hh"
#include "enrobage.hh"
#include "compatibility.hh"


map<string, bool>	gDocNoticeFlagMap;
const string		gDocNoticeDefaultFile = "notice-default.txt";

static map<string, string>	gDocNoticeStringMap;
static set<string>			gDocNoticeKeySet;

static void			initDocNoticeKeySet();
static void			initDocNoticeFlagMap();
static void			initCompilationDate();
static void			printDocNoticeStringMapContent();
static void			getCurrentDir();
static int			cholddir();
static istream*		openArchFile (const string& filename);

static string 		gCurrentDir;			///< Room to save current directory name.
static struct tm*	getCompilationDate();
static struct tm	gCompilationDate;




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
		
		/* Faust "compilation stamp" : version and date. */
		if(gDocNoticeFlagMap["compilstamp1"] && gDocNoticeFlagMap["compilstamp2"] && gDocNoticeFlagMap["compilstamp3"]) {
			char datebuf [150];
			strftime (datebuf, 150, "%B %d, %Y", getCompilationDate());
			docout << "\t\\item " << gDocNoticeStringMap["compilstamp1"] << faustversion;
			docout << gDocNoticeStringMap["compilstamp2"] << datebuf;
			docout << gDocNoticeStringMap["compilstamp3"] << endl;
		}
		
		/* Various warnings and remarks. */
		if(gDocNoticeFlagMap["svgdir"])		docout << "\t\\item " << gDocNoticeStringMap["svgdir"]	<< endl;
		if(gDocNoticeFlagMap["nameconflicts"])	docout << "\t\\item " << gDocNoticeStringMap["nameconflicts"]	<< endl;
		if(gDocNoticeFlagMap["causality"])		docout << "\t\\item " << gDocNoticeStringMap["causality"]	<< endl;
		
		/* Naming conventions of variables and functions. */
		if(gDocNoticeFlagMap["fsamp"])			docout << "\t\\item " << gDocNoticeStringMap["fsamp"]	<< endl;
		if(gDocNoticeFlagMap["foreignfun"])	docout << "\t\\item " << gDocNoticeStringMap["foreignfun"]	<< endl;
		if(gDocNoticeFlagMap["intcast"])		docout << "\t\\item " << gDocNoticeStringMap["intcast"]	<< endl;
		if(gDocNoticeFlagMap["cdot"])			docout << "\t\\item " << gDocNoticeStringMap["cdot"]	<< endl;
		
		/* Integer arithmetic. */
		if(gDocNoticeFlagMap["intplus"] || 
		   gDocNoticeFlagMap["intminus"] || 
		   gDocNoticeFlagMap["intmult"] || 
		   gDocNoticeFlagMap["intdiv"]) {
			
			if(gDocNoticeFlagMap["intplus"])	docout << "\t\\item " << gDocNoticeStringMap["intplus"]	<< endl;
			if(gDocNoticeFlagMap["intminus"])	docout << "\t\\item " << gDocNoticeStringMap["intminus"]	<< endl;
			if(gDocNoticeFlagMap["intmult"])	docout << "\t\\item " << gDocNoticeStringMap["intmult"]	<< endl;
			if(gDocNoticeFlagMap["intdiv"])	docout << "\t\\item " << gDocNoticeStringMap["intdiv"]	<< endl;
		}
		
		/* Signals naming conventions. */
		if(gDocNoticeFlagMap["inputsig"])		docout << "\t\\item " << gDocNoticeStringMap["inputsig"]	<< endl;
		if(gDocNoticeFlagMap["inputsigs"])		docout << "\t\\item " << gDocNoticeStringMap["inputsigs"]	<< endl;
		if(gDocNoticeFlagMap["outputsig"])		docout << "\t\\item " << gDocNoticeStringMap["outputsig"]	<< endl;
		if(gDocNoticeFlagMap["outputsigs"])	docout << "\t\\item " << gDocNoticeStringMap["outputsigs"]	<< endl;
		if(gDocNoticeFlagMap["constsigs"])		docout << "\t\\item " << gDocNoticeStringMap["constsigs"]	<< endl;
		if(gDocNoticeFlagMap["paramsigs"])		docout << "\t\\item " << gDocNoticeStringMap["paramsigs"]	<< endl;
		if(gDocNoticeFlagMap["storedsigs"])	docout << "\t\\item " << gDocNoticeStringMap["storedsigs"]	<< endl;
		if(gDocNoticeFlagMap["buttonsigs"])	docout << "\t\\item " << gDocNoticeStringMap["buttonsigs"]	<< endl;
		if(gDocNoticeFlagMap["checkboxsigs"])	docout << "\t\\item " << gDocNoticeStringMap["checkboxsigs"]	<< endl;
		if(gDocNoticeFlagMap["slidersigs"])	docout << "\t\\item " << gDocNoticeStringMap["slidersigs"]	<< endl;
		if(gDocNoticeFlagMap["nentrysigs"])	docout << "\t\\item " << gDocNoticeStringMap["nentrysigs"]	<< endl;
		if(gDocNoticeFlagMap["tablesigs"])		docout << "\t\\item " << gDocNoticeStringMap["tablesigs"]	<< endl;
		if(gDocNoticeFlagMap["recursigs"])		docout << "\t\\item " << gDocNoticeStringMap["recursigs"]	<< endl;
		if(gDocNoticeFlagMap["prefixsigs"])	docout << "\t\\item " << gDocNoticeStringMap["prefixsigs"]	<< endl;
		if(gDocNoticeFlagMap["selectionsig"])	docout << "\t\\item " << gDocNoticeStringMap["selectionsig"]	<< endl;
		if(gDocNoticeFlagMap["selectionsigs"])	docout << "\t\\item " << gDocNoticeStringMap["selectionsigs"]	<< endl;
		
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
	loadDocNoticeFile(gDocNoticeDefaultFile);
}



/**
 * @brief Feed the content of the notice map from a file.
 *
 * This mecchanism allows to load different files for 
 * translation of the notice.
 *
 * Notice files must have been formatted as follows :
 * - a line begining by ':' immediately declares a keyword,
 * - a line begining by '"' contains text until the last '"',
 * - text can directly follow a keyword, if separated by one or
 * many separator characters (space or tab).
 * - a direct line break between two double quoted strings
 * will insert a '\n' line break in the resulting notice string.
 */
void loadDocNoticeFile(const string& noticefilename) {
	
	string s;
	string key, text;
	string noticeSeparators = " \t";
	
	istream* noticefile = openArchFile(noticefilename);
	
	while ( getline(*noticefile, s) ) {
		size_t pt1, pt2; // Text pointers.
		
		/* The first character determines whether follows a key or a text. */
		switch (s[0]) {
			case ':':
				key = ""; text = "";
				size_t pk1, pk2; // Key pointers.
				pk1 = 1;
				pk2 = s.find_first_of(noticeSeparators);
				/* Immediate '\n' after keyword case. */
				if (pk2==string::npos) pk2 = s.size();
				/* Capture and check the keyword. */
				key = s.substr(pk1, pk2-1);
				if (gDocNoticeKeySet.find(key) == gDocNoticeKeySet.end()) {
					cerr << "Documentator : loadDocNoticeFile : " << "warning : key not found (\"" << key << "\")";
				}
				/* Prepare text capture. */
				pt1 = s.find_first_of("\"", pk2);
				if (pt1==string::npos) continue;
				break;
			case '\"':
				pt1 = 0;
				break;
			default:
				continue;
		}
		
		/* Capture the text on the current line. */
		pt2 = s.find_last_not_of("\"");
		if (pt2!=string::npos) {
			if (text.size() > 0) // Handle line breaks.
				text += "\n";
			text += s.substr(pt1+1, pt2-pt1);
		}
		/* Store the current pair. */
		if(!key.empty() && !text.empty()) {
			gDocNoticeStringMap[key] = text;
			//cerr << "gDocNoticeStringMap[\"" << key << "\"] = \"" << gDocNoticeStringMap[key] << "\"" << endl;
		}
	}
	printDocNoticeStringMapContent();
}



/*****************************************************************************
								Static functions
 *****************************************************************************/


/** 
 * Initialize gDocNoticeKeySet, a set containing all the keywords.
 */
static void initDocNoticeKeySet() {
	
	gDocNoticeKeySet.insert("causality");
	gDocNoticeKeySet.insert("compilstamp1");
	gDocNoticeKeySet.insert("compilstamp2");
	gDocNoticeKeySet.insert("compilstamp3");
	gDocNoticeKeySet.insert("nameconflicts");
	gDocNoticeKeySet.insert("svgdir");
	
	gDocNoticeKeySet.insert("fsamp");
	gDocNoticeKeySet.insert("foreignfun");
	gDocNoticeKeySet.insert("cdot");
	gDocNoticeKeySet.insert("intcast");
	
	gDocNoticeKeySet.insert("intplus");
	gDocNoticeKeySet.insert("intminus");
	gDocNoticeKeySet.insert("intmult");
	gDocNoticeKeySet.insert("intdiv");
	
	gDocNoticeKeySet.insert("inputsig");
	gDocNoticeKeySet.insert("inputsigs");
	gDocNoticeKeySet.insert("outputsig");
	gDocNoticeKeySet.insert("outputsigs");
	gDocNoticeKeySet.insert("constsigs");
	gDocNoticeKeySet.insert("paramsigs");
	gDocNoticeKeySet.insert("storedsigs");
	gDocNoticeKeySet.insert("recursigs");
	gDocNoticeKeySet.insert("prefixsigs");
	gDocNoticeKeySet.insert("selectionsig");
	gDocNoticeKeySet.insert("selectionsigs");
	
	gDocNoticeKeySet.insert("buttonsigs");
	gDocNoticeKeySet.insert("checkboxsigs");
	gDocNoticeKeySet.insert("slidersigs");
	gDocNoticeKeySet.insert("nentrysigs");
	gDocNoticeKeySet.insert("tablesigs");
}


/** 
 * Initialize gDocNoticeFlagMap, a map containing all the flags.
 */
static void initDocNoticeFlagMap() {
	
	for (set<string>::iterator it=gDocNoticeKeySet.begin(); it != gDocNoticeKeySet.end() ; ++it ) {
		gDocNoticeFlagMap[*it] = false;
	}
	
	gDocNoticeFlagMap["compilstamp1"]	= true;
	gDocNoticeFlagMap["compilstamp2"]	= true;
	gDocNoticeFlagMap["compilstamp3"]	= true;
	gDocNoticeFlagMap["causality"]		= true;
}


/** 
 * Simple trace function.
 */
static void printDocNoticeStringMapContent() {
	bool trace = false;
	if(trace) {
		cout << "gDocNoticeStringMap.size() = " << gDocNoticeStringMap.size() << endl;
		map<string,string>::iterator it;
		int i = 1;
		for(it = gDocNoticeStringMap.begin(); it!=gDocNoticeStringMap.end(); ++it)
			cout << i++ << ".\tgDocNoticeStringMap[" << it->first << "] \t= '" << it->second << "'" << endl;
	}
}




//------------------------ file managment -------------------------


/**
 * Open architecture file.
 */
static istream* openArchFile (const string& filename)
{
	istream* file;
	getCurrentDir();	// Save the current directory.
	if ( (file = open_arch_stream(filename.c_str())) ) {
		//cerr << "Documentator : openArchFile : Opening '" << filename << "'" << endl;
	} else {
		cerr << "ERROR : can't open architecture file " << filename << endl;
		exit(1);
	}
	cholddir();			// Return to current directory.
	return file;
}


/**
 * Switch back to the previously stored current directory
 */
static int cholddir ()
{
	if (chdir(gCurrentDir.c_str()) == 0) {
		return 0;
	} else {
		perror("cholddir");
		exit(errno);
	}
}


/**
 * Get current directory and store it in gCurrentDir.
 */
static void getCurrentDir ()
{
	char	buffer[FAUST_PATH_MAX];
    gCurrentDir = getcwd (buffer, FAUST_PATH_MAX);
}



//------------------------ date managment -------------------------


static struct tm* getCompilationDate()
{
	initCompilationDate();
	return &gCompilationDate;
}


static void initCompilationDate()
{
	time_t now;
	
	time(&now);
	gCompilationDate = *localtime(&now);
}

