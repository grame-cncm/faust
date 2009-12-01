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



 /**********************************************************************
		- lateq.cpp : the Lateq methods definition (FAUST project) -
		- for automatic generation of documentation -
		- "lateq" stands for "LaTeX equations" -
		- The crucial method here is println -

		Historique :
		-----------
		17-10-2001 : (klass.cpp) implementation initiale (yo)
		18-10-2001 : (klass.cpp) Ajout de getFreshID (yo)
		02-11-2001 : (klass.cpp) Ajout de sous classes (yo)
		06-11-2001 : (klass.cpp) modif impression des classes (yo)
		16-08-2009 : (lateq.cpp) Creation de lateq depuis klass.cpp (kb)
		2009-11-21 : (lateq.cpp) Remodelage et documentation doxygen (kb)

***********************************************************************/

#include <stdio.h>
#include <iostream>
#include <cstdlib>

#include "lateq.hh"
#include "Text.hh"


static int	getLateqIndex(const string& s);
static bool compLateqIndexes(const string& s1, const string& s2);



/****************************************************************
				Top-level "println" method (public).
 *****************************************************************/


/**
 * @brief 
 * Top-level method to print a whole set of compiled LaTeX formulas,
 * corresponding to an <equation> faustdoc tag.
 *
 * @remark
 * These formulas must have been previously compiled, 
 * via the DocCompile class,
 * and stored in Lateq fields as LaTeX strings.
 * 
 * @remark 
 * A printed set of formulas is terminated by three printed stars.
 */
void Lateq::println(ostream& docout)
{	
	docout << endl << "% Set of Faust formulas (corresponding to an <equation> tag)." << endl;
	docout << "\\begin{enumerate}" << endl << endl;
	
	/* Plural handling for titles of sub-sets of formulas. */
	string sInputs		= fInputSigsFormulas.size()	> 1 ? "s" : "";
	string sOutputs		= fOutputSigsFormulas.size()	> 1 ? "s" : "";
	string sConstants	= fConstSigsFormulas.size()	> 1 ? "s" : "";
	string sUIElements	= fUISigsFormulas.size()		> 1 ? "s" : "";
	string sParameters	= fParamSigsFormulas.size()	> 1 ? "s" : "";
	unsigned int internalSigsCount = fStoreSigsFormulas.size() + fRecurSigsFormulas.size() + fTableSigsFormulas.size() + fSelectSigsFormulas.size() + fPrefixSigsFormulas.size();
	string sInternals	= (internalSigsCount) > 1 ? "s" : "";
	
	/* Successively print each Lateq field containing LaTeX formulas, with a title. */
	printOneLine	(subst("\\item Input signal$0 : ", sInputs), fInputSigsFormulas, docout);
	printDGroup		(subst("\\item Output signal$0 : ", sOutputs), fOutputSigsFormulas, docout);
	printDGroup		(subst("\\item Constant$0 : ", sConstants), fConstSigsFormulas, docout);
	printHierarchy	(subst("\\item User interface element$0 : ", sUIElements), fUISigsFormulas, docout);
	printDGroup		(subst("\\item Parameter signal$0 : ", sParameters), fParamSigsFormulas, docout);
	
	/* The "Internal signals" item gather several fields, like a "super-item"... */
	if( internalSigsCount > 0 ) {
		docout << subst("\\item Internal signal$0 : ", sInternals);
	}
	fStoreSigsFormulas.sort(compLateqIndexes);
	printDGroup		("", fStoreSigsFormulas, docout);
	printDGroup		("", fRecurSigsFormulas, docout);
	printDGroup		("", fTableSigsFormulas, docout);
	printMath		("", fSelectSigsFormulas, docout);
	printMath		("", fPrefixSigsFormulas, docout);
	
	docout << "\\end{enumerate}" << endl << endl;
}




/****************************************************************
				Secondary printing methods (private).
 *****************************************************************/


/**
 * Print a sorted list of input signals names ("x_i(t)"),
 * on a single line, separated by commas.
 *
 * @param[in]	section		The title to print for these formulas.
 * @param[in]	field		The list of LaTeX input signals names.
 * @param[out]	docout		The LaTeX output file to print into.
 */
void Lateq::printOneLine(const string& section, list<string>& field, ostream& docout)
{
	if (field.size() > 0) {
		field.sort(compLateqIndexes);
		docout << section << "\t ";
		list<string>::const_iterator s;
		string sep = "";
		for (s = field.begin(); s != field.end(); ++s) {
			docout << sep << "$" << *s << "$" << endl;
			sep = ", ";
		}
	} else {
		docout << section << "\t none" << endl << endl;
	}
}


/**
 * @brief Print a dgroup environment to auto-break long formulas.
 *
 * @remark
 * The "dgroup" and "dmath" environments belong to the "breqn" LaTeX package.
 * The stared variants "dgroup*" and "dmath*" force unnumbered equations.
 *
 * @param[in]	section		The title to print for these formulas.
 * @param[in]	field		The list of LaTeX formulas.
 * @param[out]	docout		The LaTeX output file to print into.
 */
void Lateq::printDGroup(const string& section, list<string>& field, ostream& docout)
{
	if (field.size() > 0) {
		docout << section << endl;
		tab(1,docout); docout << "\\begin{dgroup*}" << endl;
		list<string>::const_iterator s;
		for (s = field.begin(); s != field.end(); ++s) {
			tab(2,docout); docout << "\\begin{" << "dmath*" << "}" << endl;
			tab(3,docout); docout << "\t" << *s << endl;
			tab(2,docout); docout << "\\end{" << "dmath*" << "}" << endl;
		}
		tab(1,docout); docout << "\\end{dgroup*}" << endl;
		docout << endl;
	}
}


/**
 * @brief Print formulas for user interface signals.
 *
 * @param[in]	section		The title to print for these formulas.
 * @param[in]	field		This multimap contains pairs :
 * 1. the path_string is printed as a sub-title item, when new;
 * 2. each latex_string is printed as a preformated row of the  
 * supertabular environment (needed to handle long tables).
 * @param[out]	docout		The LaTeX output file to print into.
 *
 * @remark
 * To decide when one should avoid to print an itemize environment, 
 * a "global" strategy is applied : in the particular case where 
 * ONLY empty paths were detected in the WHOLE container (all UIs
 * are at the top level).
 * In this particular case, UI strings are directly printed, 
 * and their (empty!) path is ignored...
 * In the other case, we have to print an itemize environment
 * and manage paths printing (empty AND non-empty paths) as items.
 *
 * @see DocCompiler::prepareIntervallicUI
 * @see DocCompiler::prepareBinaryUI
 */
void Lateq::printHierarchy(const string& section, multimap<string,string>& field, ostream& docout)
{
	if (field.size() > 0) {
		docout << section << endl;

		bool hasSomePaths = hasNotOnlyEmptyKeys(field);	///< Manage itemize printing for pathnames.
		unsigned int n;	///< Manage latex indentation offset.
				
		if (hasSomePaths) {
			tab(0,docout); docout << "\\begin{itemize}" << endl;
			n = 1;
		} else {
			n = 0;
		}

		multimap<string,string>::iterator it;
		string uidir = "improbable_starting_dirname";
		bool startFlag = true;

		for (it = field.begin(); it != field.end(); ++it) {
			/* Manage supertabular environment bounds and pathname printing. */
			if (it->first != uidir) {
				if (!startFlag) {
					tab(n+2,docout); docout << "\\end{supertabular}" << endl;
					tab(n+1,docout); docout << "\\end{center}" << endl;
				} else { 
					startFlag = false; 
				}
				if (hasSomePaths) {
					/* Print the current pathname if new and if pathnames requested. */
					if (it->first != "") {
						tab(n+0,docout); docout << "\\item \\textsf{" << it->first << "}" << endl;
					} else { 
						tab(n+0,docout); docout << "\\item \\textit{" << "(at root level)" << "}" << endl;
					}
				}
				tab(n+1,docout); docout << "\\begin{center}" << endl;
				tab(n+2,docout); docout << "\\begin{supertabular}{rllll}" << endl;
			}
			/* Print the current formula. */
			tab(n+3,docout); docout << it->second << endl;
			uidir = it->first;
		}
		tab(n+2,docout); docout << "\\end{supertabular}" << endl;
		tab(n+1,docout); docout << "\\end{center}" << endl;
		if (hasSomePaths) {
			tab(n+0,docout); docout << "\\end{itemize}" << endl;
		}
		docout << endl;
	}
}


/**
 * @brief Print formulas for select2, select3 and prefix signals.
 *
 * @param[in]	section		The title to print for these formulas.
 * @param[in]	field		The list of LaTeX arrays (for braces with two lines).
 * @param[out]	docout		The LaTeX output file to print into.
 * 
 * @see DocCompiler::generateSelect2
 * @see DocCompiler::generateSelect3
 * @see DocCompiler::generatePrefix
 */
void Lateq::printMath(const string& section, list<string>& field, ostream& docout)
{
	if (field.size() > 0) {
		docout << section;
		docout << "\\begin{displaymath}" << endl;
		list<string>::iterator s;
		for (s = field.begin(); s != field.end(); ++s) {
			docout << *s << endl;		
		}
		docout << "\\end{displaymath}" << endl;
		docout << endl;		
	}
}


/** Simple handling of indentation. */
void Lateq::tab (int n, ostream& docout) const
{ 
	while (n--) docout << '\t'; 
}


/**
 * @brief Find out whether all keys of the multimap are empty or not.
 * 
 * In other words :
 * Check that some UIs have a path (non empty). 
 *
 * In other other words :
 * Check that all UIs are not at top-level.
 */
bool Lateq::hasNotOnlyEmptyKeys(multimap<string,string>& mm) 
{
	typedef multimap<string,string>::iterator MMIT;
	pair<MMIT,MMIT> range;
	range = mm.equal_range("");	///< Look for pairs with empty keys.
	bool hasOnlyEmptyPaths = (range.first == mm.begin()) && (range.second == mm.end());
	return !hasOnlyEmptyPaths;
}



/****************************************************************
				Internal static functions.
 *****************************************************************/


/**
 * Compare indexes of two LaTeX strings, 
 * for the sort() method applied on list<string> fields.
 */
static bool compLateqIndexes(const string& s1, const string& s2)
{
	return getLateqIndex(s1) < getLateqIndex(s2);
}


/**
 * Find out the index of signals in LaTeX signal definition strings,
 * between the first "_{" and "}" patterns.
 *
 * @param[in]	s		A LaTeX string to parse.
 * @return		<int>	The index found, as an integer.
 */
static int getLateqIndex(const string& s)
{
	size_t p1;
	size_t p2;
	string sIndex;
		
	p1 = s.find("_{"); 
	if (p1==string::npos) {
		cerr << "Error : getLateqIndex found no \"{_\" substring.\n";
		exit(1); }
	p1 += 2;
	
	p2 = s.find("}", p1); 
	if (p2==string::npos) {
		cerr << "Error : getLateqIndex found no \"}\" substring\n.";
		exit(1); }
	p2 -= 3;
	
	sIndex = s.substr (p1, p2);

	return atoi(sIndex.c_str());
}

