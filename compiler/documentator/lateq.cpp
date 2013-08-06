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
#include <set>
#include <sstream>

#include "lateq.hh"
#include "Text.hh"
#include "exception.hh"
#include "global.hh"

static int	getLateqIndex(const string& s);
static bool compLateqIndexes(const string& s1, const string& s2);
static void initDocMathKeySet();

template <class T>
inline std::string to_string (const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

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
 */
void Lateq::println(ostream& docout)
{	
	/* 1. Make titles of sub-sets of formulas. */
	string suchthat		= gGlobal->gDocMathStringMap["suchthat"];
	
	string sInputs		= makeItemTitle((const unsigned int)fInputSigsFormulas.size(), "inputsigtitle") + makeSignamesList(fInputSigsFormulas, "");
	string sOutputs		= makeItemTitle((const unsigned int)fOutputSigsFormulas.size(), "outputsigtitle") + makeSignamesList(fOutputSigsFormulas, suchthat);
	string sConstants	= makeItemTitle((const unsigned int)fConstSigsFormulas.size(), "constsigtitle") + makeSignamesList(fConstSigsFormulas, suchthat);
	
	vector<list<string> > UISignamesVector = makeUISignamesVector(fUISigsFormulas);
	string sUIElements	= makeItemTitle((const unsigned int)fUISigsFormulas.size(), "uisigtitle") + makeSignamesList(UISignamesVector, suchthat);

	unsigned int internalSigsCount = (unsigned int)(fParamSigsFormulas.size() + fStoreSigsFormulas.size() + fRecurSigsFormulas.size() + fRDTblSigsFormulas.size() + fRWTblSigsFormulas.size() + fSelectSigsFormulas.size() + fPrefixSigsFormulas.size());
	
	vector<list<string> > internalSigsFormulasList;
	if( ! fParamSigsFormulas.empty() )	internalSigsFormulasList.push_back(fParamSigsFormulas);
	if( ! fStoreSigsFormulas.empty() )	internalSigsFormulasList.push_back(fStoreSigsFormulas);
	if( ! fRecurSigsFormulas.empty() )	internalSigsFormulasList.push_back(fRecurSigsFormulas);
	if( ! fRDTblSigsFormulas.empty() )	internalSigsFormulasList.push_back(fRDTblSigsFormulas);
	if( ! fRWTblSigsFormulas.empty() )	internalSigsFormulasList.push_back(fRWTblSigsFormulas);
	if( ! fSelectSigsFormulas.empty() )	internalSigsFormulasList.push_back(fSelectSigsFormulas);
	if( ! fPrefixSigsFormulas.empty() )	internalSigsFormulasList.push_back(fPrefixSigsFormulas);
	
	string sInternals	= makeItemTitle(internalSigsCount, "intermedsigtitle") + makeSignamesList(internalSigsFormulasList, suchthat);
	
	/* 2. Successively print each Lateq field containing LaTeX formulas, with a title. */
	
	docout << endl << gGlobal->gDocMathStringMap["lateqcomment"] << endl;
	docout << "\\begin{enumerate}" << endl << endl;
	
	printDGroup		(sOutputs, fOutputSigsFormulas, docout);
	printOneLine	(sInputs, docout);
	const string outputsTitle = "\\item " + sOutputs + "\\ $y_i$\\ " + gGlobal->gDocMathStringMap["for"] + " $i \\in [1," + to_string(fOutputSigsFormulas.size()) + "]$: ";
	printHierarchy	(sUIElements, fUISigsFormulas, docout);
	
	/* The "Internal signals" item gather several fields, like a "super-item"... */
	if( internalSigsCount > 0 ) {
		docout << sInternals;
	}
	fStoreSigsFormulas.sort(compLateqIndexes);
	printDGroup		("", fParamSigsFormulas, docout);
	printDGroup		("", fStoreSigsFormulas, docout);
	printDGroup		("", fRecurSigsFormulas, docout);
	printDGroup		("", fRDTblSigsFormulas, docout);
	printMath		("", fRWTblSigsFormulas, docout);
	printMath		("", fSelectSigsFormulas, docout);
	printMath		("", fPrefixSigsFormulas, docout);

	printDGroup		(sConstants, fConstSigsFormulas, docout);
	
	docout << "\\end{enumerate}" << endl << endl;
}

/****************************************************************
				Item title making functions (public).
 *****************************************************************/

string Lateq::makeItemTitle(const unsigned int formulasListSize, const string& titleName)
{
	string item		= "\\item ";
	
	/* Plural handling for titles of sub-sets of formulas. */
	string title	= formulasListSize > 1 ? gGlobal->gDocMathStringMap[titleName + "2"] : gGlobal->gDocMathStringMap[titleName + "1"];
	
	return item + title;
}

string Lateq::makeSigDomain(const list<string>& formulasList)
{
	string signame = "";
	string sigDomain = "";
	
	if (formulasList.size() > 0) {
		string firstEq = *(formulasList.begin());
		signame = getSigName(firstEq);
		
		if(formulasList.size() > 1) {
			sigDomain = " $" + signame + "_i$ " + gGlobal->gDocMathStringMap["for"] + " $i \\in [1," + to_string(formulasList.size()) + "]$";
		} else {
			if(signame == "x" || signame == "y") {
				sigDomain = " $" + signame + "$"; ///< No indices for single input neither single output.
			} else {
				sigDomain = " $" + signame + "_1$"; ///< Indices "1" for all other single signal.
			}
		}
	} else {
		sigDomain = gGlobal->gDocMathStringMap["emptyformulafield"];
	}
	return sigDomain;
}

string Lateq::makeSignamesList(const list<string>& formulasList, const string& ending)
{
	if (formulasList.size() > 0) {
		return makeSigDomain(formulasList) + " " + ending;
	} else {
		return " (" + gGlobal->gDocMathStringMap["emptyformulafield"] + ")";
	}
}

string Lateq::makeSignamesList(const vector<list<string> >& formulasListsVector, const string& ending)
{
	if (formulasListsVector.size() > 0) {
		vector<list<string> >::const_iterator it;
		string signames = "";
		string sep = " ";
		for (it = formulasListsVector.begin(); it != formulasListsVector.end(); ++it) {
			signames += sep + makeSigDomain(*it);
			(it != (formulasListsVector.end() - 2)) ? sep = ", " : sep = " " + gGlobal->gDocMathStringMap["and"] + " ";
		}
		return signames + " " + ending;
	} else {
		return " (" + gGlobal->gDocMathStringMap["emptyformulafield"] + ")";
	}
}

string Lateq::getSigName(const string& s)
{
	size_t found;
	string signame;
	
	found = s.find(" =");
	if (found != string::npos) { ///< Looking for a left member.
		signame = s.substr (0, found);
	}
	found = s.find("(t)");
	if (found != string::npos) { ///< Strip "(t)" argument if exists.
		signame = s.substr (0, found);
	}
	found = signame.find("[t]");
	if (found != string::npos) { ///< Strip "[t]" argument if exists (for tables).
		signame = s.substr (0, found);
	}
	found = signame.find_last_of("_");
	if (found != string::npos) { ///< Strip indice if exists.
		signame = signame.substr (0, found);
	}
	
	return signame;
}

vector<list<string> > Lateq::makeUISignamesVector(const multimap<string,string>& field)
{
	map<char,unsigned int> uiTypesMap;
	vector<list<string> > uiSignamesVector;
	unsigned int vIndex = 0;
	
	multimap<string,string>::const_iterator it;
	
	for (it = field.begin(); it != field.end(); ++it) {
		char type		= getUISigType(it->second);
		string signame	= getUISigName(it->second);
		
		map<char,unsigned int>::iterator uiTypesIt;
		uiTypesIt = uiTypesMap.find(type);
		if( uiTypesIt != uiTypesMap.end()) {
			uiSignamesVector[uiTypesMap[uiTypesIt->second]].push_back(signame);
		} else {
			++vIndex;
			uiTypesMap.insert(pair<char,unsigned int>(type, vIndex));
            list<string> tmpList;
			tmpList.push_back(signame);
			uiSignamesVector.push_back(tmpList);
		}
	}
	
	return uiSignamesVector;
}

string Lateq::getUISigName(const string& s)
{
	size_t found;
	string signame;
	
	found = s.find("${u_");
	if (found != string::npos) { ///< Looking for a UI signal name "{u_?}_{i}(t)".
		signame = s.substr (found+1, 12);
	}
	
	return signame;
}

char Lateq::getUISigType(const string& s)
{
	size_t found;
	char sigtype = '0';
	
	found = s.find("${u_");
	if (found != string::npos) { ///< Looking for a UI signal name "{u_?}_{i}".
		sigtype = s.at (found+4);
	}
	
	return sigtype;
}

/****************************************************************
				Secondary printing methods (private).
 *****************************************************************/
/**
 * Print a sorted list of input signals names ("x_i"),
 * on a single line, separated by commas.
 *
 * @param[in]	section		The title to print for these formulas.
 * @param[out]	docout		The LaTeX output file to print into.
 */
void Lateq::printOneLine(const string& section, ostream& docout)
{
	docout << section << endl << endl;
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
						tab(n+0,docout); docout << "\\item \\emph{" << gGlobal->gDocMathStringMap["rootlevel"] << "}" << endl;
					}
				}
				tab(n+1,docout); docout << "\\begin{center}" << endl;
				tab(n+2,docout); docout << "\\begin{supertabular}{lll}" << endl;
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

/** 
 * Dispatch initialization of autodoc container.
 */
void initDocMath() 
{
	initDocMathKeySet();
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
	if (p1 == string::npos) {
        throw faustexception("ERROR : getLateqIndex found no \"{_\" substring.\n");
    }
	p1 += 2;
	
	p2 = s.find("}", p1); 
	if (p2 == string::npos) {
		throw faustexception("ERROR : getLateqIndex found no \"{_\" substring.\n");
    }
	p2 -= 3;
	
	sIndex = s.substr (p1, p2);

	return atoi(sIndex.c_str());
}

/** 
 * Initialize gGlobal->gDocMathKeySet, a set containing all the keywords.
 */
static void initDocMathKeySet()
{
	gGlobal->gDocMathKeySet.insert("inputsigtitle1");
	gGlobal->gDocMathKeySet.insert("inputsigtitle2");
	gGlobal->gDocMathKeySet.insert("outputsigtitle1");
	gGlobal->gDocMathKeySet.insert("outputsigtitle2");
	gGlobal->gDocMathKeySet.insert("constsigtitle1");
	gGlobal->gDocMathKeySet.insert("constsigtitle2");
	gGlobal->gDocMathKeySet.insert("uisigtitle1");
	gGlobal->gDocMathKeySet.insert("uisigtitle2");
	gGlobal->gDocMathKeySet.insert("intermedsigtitle1");
	gGlobal->gDocMathKeySet.insert("intermedsigtitle2");
	gGlobal->gDocMathKeySet.insert("lateqcomment");
	gGlobal->gDocMathKeySet.insert("emptyformulafield");
	gGlobal->gDocMathKeySet.insert("defaultvalue");
	gGlobal->gDocMathKeySet.insert("suchthat");
	gGlobal->gDocMathKeySet.insert("and");
	gGlobal->gDocMathKeySet.insert("for");
	gGlobal->gDocMathKeySet.insert("rootlevel");

	gGlobal->gDocMathKeySet.insert("dgmcaption");
}


