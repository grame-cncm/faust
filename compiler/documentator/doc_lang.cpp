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
#include <string>
#include <time.h>
#include <cstdlib>
#include <errno.h>

#include "doc_lang.hh"
#include "doc_notice.hh"
#include "doc_autodoc.hh"
#include "doc_metadatas.hh"
#include "lateq.hh"
#include "enrobage.hh"
#include "compatibility.hh"
#include "exception.hh"
#include "global.hh"

static void importDocStrings(const string& filename);
static void getKey(const string& s, string& key, size_t& pt1);
static void getText(const string& s, size_t pt1, string& text);
static void storePair(const string& key, const string& text);
static void printStringMapContent(map<string,string>& map, const string& name);
static istream* openArchFile(const string& filename);
static void getCurrentDir();
static int cholddir();

/*****************************************************************************
							Public functions
 *****************************************************************************/

void loadTranslationFile(const string& lang)
{
    initDocMath();
    initDocNotice();
    initDocAutodoc();
    initDocMetadatas();

    /** First ensure that the default file is loaded a least. */
    importDocStrings(gGlobal->gDocTextsDefaultFile);

    /** Then try and load the target file. */
    if (!lang.empty()) {
        importDocStrings("mathdoctexts-" + lang + ".txt");
    }
}

/*****************************************************************************
								Static functions
 *****************************************************************************/

/**
 * @brief Feed the content of doc texts maps from a file.
 *
 * This mecchanism allows to load different files for translation.
 *
 * "mathdoctexts" files must have been formatted as follows :
 * - a line beginning by ':' immediately declares a keyword,
 * - a line beginning by '"' contains text until the last '"',
 * - text can directly follow a keyword, if separated by one or
 * many separator characters (space or tab).
 * - a direct line break between two double quoted strings
 * will insert a '\n' line break in the resulting notice string.
 */
static void importDocStrings(const string& filename)
{	
	string s;
	string key, text;
	istream* file = openArchFile(filename);
	
	while (getline(*file, s)) {
		size_t pt1; // Text pointer.
		
		/* The first character determines whether will follow a key or a text. */
		switch (s[0]) {
			case ':':
				text = "";
				getKey(s, key, pt1);
				if (pt1==string::npos) continue;
				break;
			case '\"':
				pt1 = 0;
				break;
			default:
				continue;
		}
		getText(s, pt1, text);
		storePair(key, text);
	}
    
	printStringMapContent(gGlobal->gDocNoticeStringMap, "gGlobal->gDocNoticeStringMap");
	printStringMapContent(gGlobal->gDocAutodocStringMap, "gGlobal->gDocAutodocStringMap");
	printStringMapContent(gGlobal->gDocMathStringMap, "gGlobal->gDocMathStringMap");
	printStringMapContent(gGlobal->gDocMetadatasStringMap, "gGlobal->gDocMetadatasStringMap");
    
    delete(file);
}

static void getKey(const string& s, string& key, size_t& pt1)
{
	/* Initialisation. */
	key = "";
	string separators = " \t";
	size_t pk1 = 1;
	size_t pk2 = s.find_first_of(separators);
	
	/* Immediate '\n' after keyword case. */
	if (pk2 == string::npos) pk2 = s.size();
	
	/* Capture and check the keyword. */
	key = s.substr(pk1, pk2-1);
	
	/* Prepare text capture. */
	pt1 = s.find_first_of("\"", pk2);
}

static void getText(const string& s, size_t pt1, string& text)
{
	/* Capture the text on the current line. */
	size_t pt2 = s.find_last_not_of("\"");
	if (pt2 != string::npos) {
		if (text.size() > 0) text += "\n"; // Handle line breaks.
		text += s.substr(pt1+1, pt2-pt1);
	}
}

static void storePair(const string& key, const string& text)
{
	/* Store the current pair. */
	if (!key.empty() && !text.empty()) {
		
		if (gGlobal->gDocNoticeKeySet.find(key) != gGlobal->gDocNoticeKeySet.end()) {
			gGlobal->gDocNoticeStringMap[key] = text;
		} 
		else if (gGlobal->gDocAutodocKeySet.find(key) != gGlobal->gDocAutodocKeySet.end()) {
			gGlobal->gDocAutodocStringMap[key] = text;
		}
		else if (gGlobal->gDocMathKeySet.find(key) != gGlobal->gDocMathKeySet.end()) {
			gGlobal->gDocMathStringMap[key] = text;
		}
		else if (gGlobal->gDocMetadatasKeySet.find(key) != gGlobal->gDocMetadatasKeySet.end()) {
			gGlobal->gDocMetadatasStringMap[key] = text;
		}
		else {
			cerr << "Documentator : importDocStings : " << "warning : unknown key \"" << key << "\"" << endl;
		}
		//cerr << "gGlobal->gDocNoticeStringMap[\"" << key << "\"] = \"" << gGlobal->gDocNoticeStringMap[key] << "\"" << endl;
	}
}

/** 
 * Simple trace function.
 */
static void printStringMapContent(map<string,string>& m, const string& name) {
	bool trace = false;
	if (trace) {
		cout << name << ".size() = " << m.size() << endl;
		map<string,string>::iterator it;
		int i = 1;
		for (it = m.begin(); it != m.end(); ++it)
			cout << i++ << ".\t" << name << "[" << it->first << "] \t= '" << it->second << "'" << endl;
	}
}

//------------------------ file managment -------------------------

/**
 * Open architecture file.
 */
static istream* openArchFile(const string& filename)
{
    istream* file;
    getCurrentDir();	// Save the current directory.
    if ((file = openArchStream(filename.c_str()))) {
        //cerr << "Documentator : openArchFile : Opening '" << filename << "'" << endl;
    } else {
        stringstream error;
        error << "ERROR : can't open architecture file " << filename << endl;
        throw faustexception(error.str());
    }
    cholddir();			// Return to current directory.
    return file;
}

/**
 * Switch back to the previously stored current directory
 */
static int cholddir()
{
	if (chdir(gGlobal->gCurrentDir.c_str()) == 0) {
		return 0;
	} else {
        stringstream error;
        error << "ERROR in cholddir " << strerror(errno) << endl;
        throw faustexception(error.str());
	}
}

/**
 * Get current directory and store it in gCurrentDir.
 */
static void getCurrentDir()
{
	char buffer[FAUST_PATH_MAX];
    gGlobal->gCurrentDir = getcwd (buffer, FAUST_PATH_MAX);
}


