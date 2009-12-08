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
#include <string>
#include <set>
#include <map>
#include <cstdlib>

#include "doc_autodoc.hh"
#include "tlib.hh"
#include "boxes.hh"
#include "doc.hh"


extern SourceReader		gReader;

map<string, string>		gDocAutodocStringMap;
set<string>				gDocAutodocKeySet;

static void				initDocAutodocKeySet();




/*****************************************************************************
						Public functions
 *****************************************************************************/


/** 
 * @brief Declare an automatic documentation.
 *
 * This function simulates a default documentation : 
 * if no <doc> tag was found in the input faust file,
 * and yet the '-math' option was called, 
 * then print a complete 'process' doc. 
 */
void declareAutoDoc() 
{
	Tree autodoc = nil;
	Tree process = boxIdent("process");
	
	string autoEquationTxt = "\n" + gDocAutodocStringMap["autoeqntitle"] + "\n\n";
	autoEquationTxt += gDocAutodocStringMap["autoeqntext"] + "\n";
	autodoc = cons(docTxt(autoEquationTxt.c_str()), autodoc);
	autodoc = cons(docEqn(process), autodoc);
	
	string autoDiagramTxt = "\n" + gDocAutodocStringMap["autodgmtitle"] + "\n\n";
	autoDiagramTxt += gDocAutodocStringMap["autodgmtext"] + "\n";
	autodoc = cons(docTxt(autoDiagramTxt.c_str()), autodoc);
	autodoc = cons(docDgm(process), autodoc);	
	
	string autoNoticeTxt = "\n" + gDocAutodocStringMap["autontctitle"] + "\n\n";
	autoNoticeTxt += gDocAutodocStringMap["autontctext"] + "\n";
	autodoc = cons(docTxt(autoNoticeTxt.c_str()), autodoc);
	autodoc = cons(docNtc(), autodoc);
	
	string autoListingTxt;
	vector<string> pathnames = gReader.listSrcFiles();
	if(pathnames.size() > 1) {
		autoListingTxt = "\n" + gDocAutodocStringMap["autolsttitle2"] + "\n\n";
		autoListingTxt += gDocAutodocStringMap["autolsttext2"] + "\n";
	} else {
		autoListingTxt = "\n" + gDocAutodocStringMap["autolsttitle1"] + "\n\n";
		autoListingTxt += gDocAutodocStringMap["autolsttext1"] + "\n";
	}
	autodoc = cons(docTxt(autoListingTxt.c_str()), autodoc);
	autodoc = cons(docLst(), autodoc);
	
	declareDoc(autodoc);
}


/** 
 * Dispatch initialization of autodoc container.
 */
void initDocAutodoc() 
{
	initDocAutodocKeySet();
}



/*****************************************************************************
						Static functions
 *****************************************************************************/


/** 
 * Initialize gDocAutodocKeySet, a set containing all the keywords.
 */
static void initDocAutodocKeySet() {
	
	gDocAutodocKeySet.insert("autoeqntitle");
	gDocAutodocKeySet.insert("autoeqntext");
	
	gDocAutodocKeySet.insert("autodgmtitle");
	gDocAutodocKeySet.insert("autodgmtext");
	
	gDocAutodocKeySet.insert("autontctitle");
	gDocAutodocKeySet.insert("autontctext");
	
	gDocAutodocKeySet.insert("autolsttitle1");	
	gDocAutodocKeySet.insert("autolsttext1");
	
	gDocAutodocKeySet.insert("autolsttitle2");
	gDocAutodocKeySet.insert("autolsttext2");
}


/** 
 * Simple trace function.
 */
static void printDocAutodocStringMapContent() {
	bool trace = false;
	if(trace) {
		cout << "gDocAutodocStringMap.size() = " << gDocAutodocStringMap.size() << endl;
		map<string,string>::iterator it;
		int i = 1;
		for(it = gDocAutodocStringMap.begin(); it!=gDocAutodocStringMap.end(); ++it)
			cout << i++ << ".\tgDocNoticeStringMap[" << it->first << "] \t= '" << it->second << "'" << endl;
	}
}

