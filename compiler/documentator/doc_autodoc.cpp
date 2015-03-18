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
#include "global.hh"

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
	Tree autodoc = gGlobal->nil;
	Tree process = boxIdent("process");
	
	/** Autodoc's "head", with title, author, date, and metadatas. */
	
	/** The latex title macro is bound to the metadata "name" if it exists,
	 (corresponding to "declare name") or else just to the file name. */
	autodoc = cons(docTxt("\\title{"), autodoc);
	if (gGlobal->gMetaDataSet.count(tree("name"))) {
		autodoc = cons(docMtd(tree("name")), autodoc);
	} else {
		autodoc = cons(docTxt(gGlobal->gDocName.c_str()), autodoc);
	}
	autodoc = cons(docTxt("}\n"), autodoc);
	
	/** The latex author macro is bound to the metadata "author" if it exists,
	 (corresponding to "declare author") or else no author item is printed. */
	if (gGlobal->gMetaDataSet.count(tree("author"))) {
		autodoc = cons(docTxt("\\author{"), autodoc);
		autodoc = cons(docMtd(tree("author")), autodoc);
		autodoc = cons(docTxt("}\n"), autodoc);
	}
	
	/** The latex date macro is bound to the metadata "date" if it exists,
	 (corresponding to "declare date") or else to the today latex macro. */
	autodoc = cons(docTxt("\\date{"), autodoc);
	if (gGlobal->gMetaDataSet.count(tree("date"))) {
		autodoc = cons(docMtd(tree("date")), autodoc);
	} else {
		autodoc = cons(docTxt("\\today"), autodoc);
	}
	autodoc = cons(docTxt("}\n"), autodoc);
	
	/** The latex maketitle macro. */
	autodoc = cons(docTxt("\\maketitle\n"), autodoc);

	/** Insert all declared metadatas in a latex tabular environment. */
	if (! gGlobal->gMetaDataSet.empty()) {
		autodoc = cons(docTxt("\\begin{tabular}{ll}\n"), autodoc);
		autodoc = cons(docTxt("\t\\hline\n"), autodoc);
		for (MetaDataSet::iterator i = gGlobal->gMetaDataSet.begin(); i != gGlobal->gMetaDataSet.end(); i++) {
			string mtdkey = tree2str(i->first);
			string mtdTranslatedKey = gGlobal->gDocMetadatasStringMap[mtdkey];
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
	
	string autoPresentationTxt = "\n\\bigskip\n" + gGlobal->gDocAutodocStringMap["thisdoc"] + "\n\n";
	autodoc = cons(docTxt(autoPresentationTxt.c_str()), autodoc);
	
	string autoEquationTxt = "\n" + gGlobal->gDocAutodocStringMap["autoeqntitle"] + "\n\n";
	autoEquationTxt += gGlobal->gDocAutodocStringMap["autoeqntext"] + "\n";
	autodoc = cons(docTxt(autoEquationTxt.c_str()), autodoc);
	autodoc = cons(docEqn(process), autodoc);
	
	string autoDiagramTxt = "\n" + gGlobal->gDocAutodocStringMap["autodgmtitle"] + "\n\n";
	autoDiagramTxt += gGlobal->gDocAutodocStringMap["autodgmtext"] + "\n";
	autodoc = cons(docTxt(autoDiagramTxt.c_str()), autodoc);
	autodoc = cons(docDgm(process), autodoc);	
	
	string autoNoticeTxt = "\n" + gGlobal->gDocAutodocStringMap["autontctitle"] + "\n\n";
//	autoNoticeTxt += gGlobal->gDocAutodocStringMap["autontctext"] + "\n";
	autodoc = cons(docTxt(autoNoticeTxt.c_str()), autodoc);
	autodoc = cons(docNtc(), autodoc);
	
	string autoListingTxt;
	vector<string> pathnames = gGlobal->gReader.listSrcFiles();
	if(pathnames.size() > 1) {
		autoListingTxt = "\n" + gGlobal->gDocAutodocStringMap["autolsttitle2"] + "\n\n";
		autoListingTxt += gGlobal->gDocAutodocStringMap["autolsttext2"] + "\n";
	} else {
		autoListingTxt = "\n" + gGlobal->gDocAutodocStringMap["autolsttitle1"] + "\n\n";
		autoListingTxt += gGlobal->gDocAutodocStringMap["autolsttext1"] + "\n";
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
 * Initialize gGlobal->gDocAutodocKeySet, a set containing all the keywords.
 */
static void initDocAutodocKeySet() {
	
	gGlobal->gDocAutodocKeySet.insert("thisdoc");

	gGlobal->gDocAutodocKeySet.insert("autoeqntitle");
	gGlobal->gDocAutodocKeySet.insert("autoeqntext");
	
	gGlobal->gDocAutodocKeySet.insert("autodgmtitle");
	gGlobal->gDocAutodocKeySet.insert("autodgmtext");
	
	gGlobal->gDocAutodocKeySet.insert("autontctitle");
	gGlobal->gDocAutodocKeySet.insert("autontctext");
	
	gGlobal->gDocAutodocKeySet.insert("autolsttitle1");	
	gGlobal->gDocAutodocKeySet.insert("autolsttext1");
	
	gGlobal->gDocAutodocKeySet.insert("autolsttitle2");
	gGlobal->gDocAutodocKeySet.insert("autolsttext2");
}

#if 0
/** 
 * Simple trace function.
 */
static void printDocAutodocStringMapContent() {
	bool trace = false;
	if(trace) {
		cout << "gGlobal->gDocAutodocStringMap.size() = " << gGlobal->gDocAutodocStringMap.size() << endl;
		map<string,string>::iterator it;
		int i = 1;
		for(it = gGlobal->gDocAutodocStringMap.begin(); it!=gGlobal->gDocAutodocStringMap.end(); ++it)
			cout << i++ << ".\tgGlobal->gDocNoticeStringMap[" << it->first << "] \t= '" << it->second << "'" << endl;
	}
}
#endif
