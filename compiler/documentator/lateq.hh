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
 
#ifndef _LATEQ_H
#define _LATEQ_H

/**********************************************************************
		- lateq.hh : the Lateq class definition (FAUST project) -
		- for automatic generation of documentation -
		- "lateq" stands for "LaTeX equations" -
		- Several containers store LaTeX formulas by type of signals -
		- Formulas usually are signal definitions, 
			except for input signals (only names). -


		Historique :
		-----------
		17-10-2001 : (klass.hh) implementation initiale (yo)
		18-10-2001 : (klass.hh) Ajout de getFreshID (yo)
		02-11-2001 : (klass.hh) Ajout de sous classes (yo)
		16-08-2009 : (lateq.hh) Création de lateq depuis klass.hh (kb)
		08-09-2009 : (lateq.hh) Grand nettoyage par le vide (yo & kb)
		23-09-2009 : (lateq.hh) Poursuite du nettoyage (kb)
		2009-11-23 : (lateq.hh) End of cleaning (kb)

***********************************************************************/

using namespace std;

#include "garbageable.hh"
#include <string>
#include <list>
#include <vector>
#include <map>

class Lateq : public virtual Garbageable {
	
public:
	
	Lateq (const int& numInputs, const int& numOutputs)
	:	fNumInputs(numInputs), fNumOutputs(numOutputs)
	{}
	
	~Lateq() {}
	
	/** Add a line of a latex equation code corresponding to a signal. */
	void addInputSigFormula (const string& str)		{ fInputSigsFormulas.push_back(str); }
	void addConstSigFormula (const string& str)		{ fConstSigsFormulas.push_back(str); }
	void addParamSigFormula (const string& str)		{ fParamSigsFormulas.push_back(str); }
	void addStoreSigFormula (const string& str)		{ fStoreSigsFormulas.push_back(str); }
	void addRecurSigFormula (const string& str)		{ fRecurSigsFormulas.push_back(str); }
	void addRDTblSigFormula (const string& str)		{ fRDTblSigsFormulas.push_back(str); }
	void addRWTblSigFormula (const string& str)		{ fRWTblSigsFormulas.push_back(str); }
	void addSelectSigFormula (const string& str)	{ fSelectSigsFormulas.push_back(str); }
	void addPrefixSigFormula (const string& str)	{ fPrefixSigsFormulas.push_back(str); }
	void addOutputSigFormula (const string& str)	{ fOutputSigsFormulas.push_back(str); }
	void addUISigFormula (const string& path, const string& str)	{ fUISigsFormulas.insert(make_pair(path, str)); };
	
	/** Top-level method to print a whole set of compiled LaTeX formulas. */
	void println(ostream& docout);
	
    int inputs()  const     { return fNumInputs; }
    int outputs() const 	{ return fNumOutputs; }
	
	
private:
	
	const int	fNumInputs;
	const int	fNumOutputs;
	
	/** LaTeX formulas to print. */
	list<string>			fInputSigsFormulas;
	list<string>			fConstSigsFormulas;
	list<string>			fParamSigsFormulas;
	list<string>			fStoreSigsFormulas;
	list<string>			fRecurSigsFormulas;
	list<string>			fRDTblSigsFormulas;
	list<string>			fRWTblSigsFormulas;
	list<string>			fSelectSigsFormulas;
	list<string>			fPrefixSigsFormulas;
	list<string>			fOutputSigsFormulas;
	multimap<string,string>	fUISigsFormulas;
	
	string makeItemTitle(const unsigned int formulasListSize, const string& titleName);
	string makeSignamesList(const list<string>& formulasList, const string& ending);
	string makeSignamesList(const vector<list<string> >& formulasListsVector, const string& ending); ///< For all "internal" signals.
	string getSigName(const string& s);
	string makeSigDomain(const list<string>& formulasList);
	string getUISigName(const string& s);
	char   getUISigType(const string& s);
	vector<list<string> > makeUISignamesVector(const multimap<string,string>& field);
	
	void printOneLine	(const string& section, ostream& docout);
	void printHierarchy		(const string& section, multimap<string,string>& field, ostream& docout);
	void printDGroup		(const string& section, list<string>& field, ostream& docout);
	void printMath		(const string& section, list<string>& field, ostream& docout);
	
	bool hasNotOnlyEmptyKeys(multimap<string,string>& mm);
	void tab(int n, ostream& docout) const;
};

void initDocMath();


#endif
