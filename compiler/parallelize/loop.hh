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
using namespace std;

#include <string>
#include <list>
#include <stack>
#include <set>
#include <map>
//#include "sigtype.hh"
//#include "smartpointer.hh"
#include "tlib.hh"
//#include "uitree.hh"

#define kMaxCategory 32

/*
 * Loops are lines of code that correspond to a recursive expression or a vector expression.
 */

struct Loop
{
    const bool          fIsRecursive;       ///< recursive loops can't be SIMDed
    const Tree          fRecSymbol;         ///< recursive loops define a recursive symbol
    Loop* const         fEnclosingLoop;     ///< Loop from which this one originated
    const string        fSize;              ///< number of iterations of the loop
    // fields concerned by absorbsion
    set<Tree>           fRecDependencies;   ///< Loops having recursive dependencies must be merged
    set<Loop*>          fLoopDependencies;  ///< Loops that must be computed before this one
    list<string>        fPreCode;           ///< code to execute at the begin of the loop
    list<string>        fExecCode;          ///< code to execute in the loop
    list<string>        fPostCode;          ///< code to execute at the end of the loop
    // for topological sort
    int                 fOrder;             ///< used during topological sort

public:
    Loop(Tree recsymbol, Loop* encl, const string& size);   ///< create a recursive loop
    Loop(Loop* encl, const string& size);   ///< create a non recursive loop

    bool isEmpty();                         ///< true when the loop doesn't contain any line of code
    bool hasRecDependencies();              ///< returns true is this loop has recursive dependencies
    void addRecDependency(Tree t);          ///< Check for a recursive dependecy and add it if needed
    bool findRecDefinition(Tree t);         ///< indicates a dependency with an enclosing loop 

    void addPreCode (const string& str);   ///< add a line of C++ code pre code
    void addExecCode (const string& str);   ///< add a line of C++ code
    void addPostCode (const string& str);   ///< add a line of C++ post code 
    void println (int n, ostream& fout);    ///< print the loop
    void printoneln (int n, ostream& fout);    ///< print the loop in scalar mode

    void absorb(Loop* l);                   ///< absorb a loop inside this one
};

#endif
