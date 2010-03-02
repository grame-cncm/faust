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


extern SourceReader				gReader;
extern string					gDocName;
extern map<Tree, set<Tree> > 	gMetaDataSet;
extern map<string, string>		gDocMetadatasStringMap;

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
 * if no <mdoc> tag was found in the input faust file,
 * and yet the '-mdoc' option was called, 
 * then print a complete 'process' doc. 
 */
void declareAutoDoc() 
{
	Tree autodoc = nil;
	Tree process = boxIdent("process");
	
	/** Autodoc's "head", with title, author, date, and metadatas. */
	
	/** The latex title macro is bound to the metadata "name" if it exists,
	 (corresponding to "declare name") or else just to the file name. */
	autodoc = cons(docTxt("\\title{"), autodoc);
	if (gMetaDataSet.count(tree("name"))) {
		autodoc = cons(docMtd(tree("name")), autodoc);
	} else {
		autodoc = cons(docTxt(gDocName.c_str()), autodoc);
	}
	autodoc = cons(docTxt("}\n"), autodoc);
	
	/** The latex author macro is bound to the metadata "author" if it exists,
	 (corresponding to "declare author") or else no author item is printed. */
	if (gMetaDataSet.count(tree("author"))) {
		autodoc = cons(docTxt("\\author{"), autodoc);
		autodoc = cons(docMtd(tree("author")), autodoc);
		autodoc = cons(docTxt("}\n"), autodoc);
	}
	
	/** The latex date macro is bound to the metadata "date" if it exists,
	 (corresponding to "declare date") or else to the today latex macro. */
	autodoc = cons(docTxt("\\date{"), autodoc);
	if (gMetaDataSet.count(tree("date"))) {
		autodoc = cons(docMtd(tree("date")), autodoc);
	} else {
		autodoc = cons(docTxt("\\today"), autodoc);
	}
	autodoc = cons(docTxt("}\n"), autodoc);
	
	/** The latex maketitle macro. */
	autodoc = cons(docTxt("\\maketitle\n"), autodoc);

	
	/** Insert all declared metadatas in a latex tabular environment. */
	if (! gMetaDataSet.empty()) {
		autodoc = cons(docTxt("\\begin{tabular}{ll}\n"), autodoc);
		autodoc = cons(docTxt("\t\\hline\n"), autodoc);
		for (map<Tree, set<Tree> >::iterator i = gMetaDataSet.begin(); i != gMetaDataSet.end(); i++) {
			string mtdkey = tree2str(i->first);
			string mtdTranslatedKey = gDocMetadatasStringMap[mtdkey];
			if (mtdTranslatedKey.empty()) {
				mtdTranslatedKey = mtdkey;
			}
			autodoc = cons(docTxt("\t\\textbf{"), autodoc);
			autodoc = cons(docTxt(mtdTranslatedKey.c_str()), autodoc);
			autodoc = cons(docTxt("} & "), autodoc);
			autodoc = cons(docMtd(tree(mtdkey.c_str())), autodoc);
			autodoc = cons(docTxt(" \\\\\n"), autodoc);
		}
		autodoc = cons(docTxt("\t\\hline\n"), autodoc);
		autodoc = cons(docTxt("\\end{tabular}\n"), autodoc);
		autodoc = cons(docTxt("\\bigskip\n"), autodoc);
	}


	/** Autodoc's "body", with equation and diagram of process, and notice and listing. */
	
	string autoPresentationTxt = "\n\\bigskip\n" + gDocAutodocStringMap["thisdoc"] + "\n\n";
	autodoc = cons(docTxt(autoPresentationTxt.c_str()), autodoc);
	
	string autoEquationTxt = "\n" + gDocAutodocStringMap["autoeqntitle"] + "\n\n";
	autoEquationTxt += gDocAutodocStringMap["autoeqntext"] + "\n";
	autodoc = cons(docTxt(autoEquationTxt.c_str()), autodoc);
	autodoc = cons(docEqn(process), autodoc);
	
	string autoDiagramTxt = "\n" + gDocAutodocStringMap["autodgmtitle"] + "\n\n";
	autoDiagramTxt += gDocAutodocStringMap["autodgmtext"] + "\n";
	autodoc = cons(docTxt(autoDiagramTxt.c_str()), autodoc);
	autodoc = cons(docDgm(process), autodoc);	
	
	string autoNoticeTxt = "\n" + gDocAutodocStringMap["autontctitle"] + "\n\n";
//	autoNoticeTxt += gDocAutodocStringMap["autontctext"] + "\n";
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
	
	gDocAutodocKeySet.insert("thisdoc");

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

