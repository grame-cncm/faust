/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
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
        17-10-2001 : (klass.hh) initial implementation  (yo)
        18-10-2001 : (klass.hh) add getFreshID (yo)
        02-11-2001 : (klass.hh) add sub-classes (yo)
        16-08-2009 : (lateq.hh) lateq creation from klass.cpp (kb)
        08-09-2009 : (lateq.hh) big cleanup (yo & kb)
        23-09-2009 : (lateq.hh) continue cleaning (kb)
        2009-11-23 : (lateq.hh) end of cleaning (kb)

***********************************************************************/

#include <list>
#include <map>
#include <string>
#include <vector>
#include "garbageable.hh"

class Lateq : public virtual Garbageable {
   public:
    Lateq(const int& numInputs, const int& numOutputs) : fNumInputs(numInputs), fNumOutputs(numOutputs) {}

    ~Lateq() {}

    /** Add a line of a latex equation code corresponding to a signal. */
    void addInputSigFormula(const std::string& str) { fInputSigsFormulas.push_back(str); }
    void addConstSigFormula(const std::string& str) { fConstSigsFormulas.push_back(str); }
    void addParamSigFormula(const std::string& str) { fParamSigsFormulas.push_back(str); }
    void addStoreSigFormula(const std::string& str) { fStoreSigsFormulas.push_back(str); }
    void addRecurSigFormula(const std::string& str) { fRecurSigsFormulas.push_back(str); }
    void addRDTblSigFormula(const std::string& str) { fRDTblSigsFormulas.push_back(str); }
    void addRWTblSigFormula(const std::string& str) { fRWTblSigsFormulas.push_back(str); }
    void addSelectSigFormula(const std::string& str) { fSelectSigsFormulas.push_back(str); }
    void addPrefixSigFormula(const std::string& str) { fPrefixSigsFormulas.push_back(str); }
    void addOutputSigFormula(const std::string& str) { fOutputSigsFormulas.push_back(str); }
    void addUISigFormula(const std::string& path, const std::string& str) { fUISigsFormulas.insert(make_pair(path, str)); };

    /** Top-level method to print a whole set of compiled LaTeX formulas. */
    void println(std::ostream& docout);

    int inputs() const { return fNumInputs; }
    int outputs() const { return fNumOutputs; }

   private:
    const int fNumInputs;
    const int fNumOutputs;

    /** LaTeX formulas to print. */
    std::list<std::string>             fInputSigsFormulas;
    std::list<std::string>             fConstSigsFormulas;
    std::list<std::string>             fParamSigsFormulas;
    std::list<std::string>             fStoreSigsFormulas;
    std::list<std::string>             fRecurSigsFormulas;
    std::list<std::string>             fRDTblSigsFormulas;
    std::list<std::string>             fRWTblSigsFormulas;
    std::list<std::string>             fSelectSigsFormulas;
    std::list<std::string>             fPrefixSigsFormulas;
    std::list<std::string>             fOutputSigsFormulas;
    std::multimap<std::string, std::string> fUISigsFormulas;

    std::string                makeItemTitle(size_t formulasListSize, const std::string& titleName);
    std::string                makeSignamesList(const std::list<std::string>& formulasList, const std::string& ending);
    std::string                makeSignamesList(const std::vector<std::list<std::string> >& formulasListsVector,
                                           const std::string& ending);  ///< For all "internal" signals.
    std::string                getSigName(const std::string& s);
    std::string                makeSigDomain(const std::list<std::string>& formulasList);
    std::string                getUISigName(const std::string& s);
    char                  getUISigType(const std::string& s);
    std::vector<std::list<std::string>> makeUISignamesVector(const std::multimap<std::string, std::string>& field);

    void printOneLine(const std::string& section, std::ostream& docout);
    void printHierarchy(const std::string& section, std::multimap<std::string, std::string>& field, std::ostream& docout);
    void printDGroup(const std::string& section, std::list<std::string>& field, std::ostream& docout);
    void printMath(const std::string& section, std::list<std::string>& field, std::ostream& docout);

    bool hasNotOnlyEmptyKeys(std::multimap<std::string, std::string>& mm);
    void tab(int n, std::ostream& docout) const;
};

void initDocMath();

#endif
