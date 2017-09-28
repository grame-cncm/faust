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

#ifndef _LOOP_H
#define _LOOP_H

/**********************************************************************
              - loop.hh : loop C++ à remplir (projet FAUST) -
 
 
                Historique :
                -----------
                21-01-2008 : implementation initiale (yo)
 
***********************************************************************/
namespace std{}
using namespace std;

#include <string>
#include <list>
#include <stack>
#include <set>
#include <map>
#include "tlib.hh"
#include "statement.hh"

#define kMaxCategory 32

/*
 * Loops are lines of code that correspond to a recursive expression or a vector expression.
 */

struct Loop
{
    const bool          fIsRecursive;       ///< recursive loops can't be SIMDed
    Tree                fRecSymbolSet;      ///< recursive loops define a set of recursive symbol
    Loop* const         fEnclosingLoop;     ///< Loop from which this one originated
    const string        fSize;              ///< number of iterations of the loop
    // fields concerned by absorbsion
    set<Loop*>          fBackwardLoopDependencies;  ///< Loops that must be computed before this one
    set<Loop*>          fForwardLoopDependencies;   ///< Loops that will be computed after this one
    list<Statement>     fPreCode;           ///< code to execute at the begin of the loop
    list<Statement>     fExecCode;          ///< code to execute in the loop
    list<Statement>     fPostCode;          ///< code to execute at the end of the loop
    // for topological sort
    int                 fOrder;             ///< used during topological sort
    int                 fIndex;             ///< used during scheduler mode code generation
    // new fields
    int					fUseCount;			///< how many loops depend on this one
    list<Loop*>			fExtraLoops;		///< extra loops that where in sequences

    int                 fPrinted;           ///< true when loop has been printed (to track multi-print errors)

public:
    Loop(Tree recsymbol, Loop* encl, const string& size);   ///< create a recursive loop
    Loop(Loop* encl, const string& size);   ///< create a non recursive loop

    bool isEmpty();                         ///< true when the loop doesn't contain any line of code
    bool hasRecDependencyIn(Tree S);        ///< returns true is this loop or its ancestors define a symbol in S

    void addPreCode (const Statement& str);        ///< add a line of C++ code pre code
    void addExecCode (const Statement& str);       ///< add a line of C++ code
    void addPostCode (const Statement& str);       ///< add a line of C++ post code
    void println (int n, ostream& fout);        ///< print the loop
    void printParLoopln(int n, ostream& fout);  ///< print the loop with a #pragma omp loop

    void printoneln (int n, ostream& fout);    ///< print the loop in scalar mode

    void absorb(Loop* l);                   ///< absorb a loop inside this one
    // new method
    void concat(Loop* l);
};

#endif
