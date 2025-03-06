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

#ifndef _LOOP_H
#define _LOOP_H

/**********************************************************************
        - loop.hh : loop C++ to be filled (projet FAUST) -

        Historique :
        -----------
        21-01-2008 : initial implementation (YO)

***********************************************************************/

#include <iostream>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <string>

#include "garbageable.hh"
#include "global.hh"
#include "statement.hh"
#include "tlib.hh"

struct Codeblock : public virtual Garbageable {
    std::list<Statement> fPreCode;   ///< code to execute at the begin of the loop
    std::list<Statement> fExecCode;  ///< code to execute in the loop
    std::list<Statement> fPostCode;  ///< code to execute at the end of the loop

    void addPreCode(const Statement& str);   ///< add a line of C++ code pre code
    void addExecCode(const Statement& str);  ///< add a line of C++ code
    void addPostCode(const Statement& str);  ///< add a line of C++ post code
};

struct CodeODblock : public Codeblock {
    std::string fODfactor;  ///< ondemand factor
    std::string fLoopIndex;

    CodeODblock(const std::string& od_factor) : Codeblock(), fODfactor(od_factor)
    {
        fLoopIndex = gGlobal->getFreshID("od");
    }
};

struct CodeUSblock : public Codeblock {
    std::string fUSfactor;  ///< upsampling factor
    std::string fLoopIndex;

    CodeUSblock(const std::string& us_factor) : Codeblock(), fUSfactor(us_factor)
    {
        fLoopIndex = gGlobal->getFreshID("us");
    }
};

struct CodeDSblock : public Codeblock {
    std::string fDSfactor;   ///< downsampling factor
    std::string fDSCounter;  ///< downsampling counter

    CodeDSblock(const std::string& ds_factor, const std::string& ds_counter)
        : Codeblock(), fDSfactor(ds_factor), fDSCounter(ds_counter)
    {
    }
};

/*
 * Loops are lines of code that correspond to a recursive expression or a vector expression.
 */

struct Loop : public virtual Garbageable {
    const bool        fIsRecursive;    ///< recursive loops can't be SIMDed
    Tree              fRecSymbolSet;   ///< recursive loops define a set of recursive symbol
    Loop* const       fEnclosingLoop;  ///< Loop from which this one originated
    const std::string fSize;           ///< number of iterations of the loop
    // fields concerned by absorbsion
    std::set<Loop*> fBackwardLoopDependencies;  ///< Loops that must be computed before this one
    std::set<Loop*> fForwardLoopDependencies;   ///< Loops that will be computed after this one
    std::list<Statement>   fPreCode;            ///< code to execute at the begin of the loop
    std::list<Statement>   fExecCode;           ///< code to execute in the loop
    std::list<Statement>   fPostCode;           ///< code to execute at the end of the loop
    std::stack<Codeblock*> fCodeStack;          ///< stack of OD/US/DS code blocks
    // for topological sort
    int fOrder;  ///< used during topological sort
    int fIndex;  ///< used during scheduler mode code generation
    // new fields
    int              fUseCount;    ///< how many loops depend on this one
    std::list<Loop*> fExtraLoops;  ///< extra loops that where in sequences

    int fPrinted;  ///< true when loop has been printed (to track multi-print errors)

   public:
    Loop(Tree recsymbol, Loop* encl, const std::string& size);  ///< create a recursive loop
    Loop(Loop* encl, const std::string& size);                  ///< create a non recursive loop

    bool isEmpty();  ///< true when the loop doesn't contain any line of code
    bool hasRecDependencyIn(
        Tree S);  ///< returns true is this loop or its ancestors define a symbol in S

    void addPreCode(const Statement& str);   ///< add a line of C++ code pre code
    void addExecCode(const Statement& str);  ///< add a line of C++ code
    void addPostCode(const Statement& str);  ///< add a line of C++ post code

    void openODblock(const std::string& od_factor);  ///< open an OD block
    void closeODblock();                             ///< close an OD block
    void openUSblock(const std::string& us_factor);  ///< open an US block
    void closeUSblock();                             ///< close an US block
    void openDSblock(const std::string& ds_factor,
                     const std::string& ds_counter);  ///< open an DS block
    void closeDSblock();                              ///< close an DS block

    void println(int n, std::ostream& fout);         ///< print the loop
    void printParLoopln(int n, std::ostream& fout);  ///< print the loop with a #pragma omp loop

    void printoneln(int n, std::ostream& fout);  ///< print the loop in scalar mode

    std::string getLoopIndex()
    {
        if (fCodeStack.size() > 0) {
            if (CodeUSblock* us_block = dynamic_cast<CodeUSblock*>(fCodeStack.top())) {
                return us_block->fLoopIndex;
            }
        }
        return "i";
    }

    void absorb(Loop* l);  ///< absorb a loop inside this one
    // new method
    void concat(Loop* l);
};

#endif
