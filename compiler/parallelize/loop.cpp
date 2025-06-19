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

#include "loop.hh"
#include "Text.hh"
#include "global.hh"

using namespace std;
#undef TRACE

/**
 * Print a list of lines.
 * @param n number of tabs of indentation
 * @param lines list of lines to be printed
 * @param fout output stream
 */
static void printlines(int n, list<Statement>& lines, ostream& fout)
{
    list<Statement>::iterator s;
    string                    ccond = "";
    for (s = lines.begin(); s != lines.end(); s++) {
        if (s->hasCondition(ccond)) {
            tab(n, fout);
            fout << s->code();
        } else if (ccond == "") {
            // debut d'une condition
            ccond = s->condition();
            tab(n, fout);
            fout << "if (" << ccond << ") {";
            n++;
            tab(n, fout);
            fout << s->code();
        } else {
            // fin précédente condition
            n--;
            tab(n, fout);
            fout << "}";
            // nouvelle condition courante
            ccond = s->condition();
            if (ccond != "") {
                tab(n, fout);
                fout << "if (" << ccond << ") {";
                n++;
            }
            tab(n, fout);
            fout << s->code();
        }
    }
    if (ccond != "") {
        n--;
        tab(n, fout);
        fout << "}";
    }
}

/**
 * Create a recursive loop.
 * @param recsymbol the recursive symbol defined in this loop
 * @param encl the enclosing loop
 * @param size the number of iterations of the loop
 */
Loop::Loop(Tree recsymbol, Loop* encl, const string& size)
    : fIsRecursive(true),
      fRecSymbolSet(singleton(recsymbol)),
      fEnclosingLoop(encl),
      fSize(size),
      fOrder(-1),
      fIndex(-1),
      fUseCount(0),
      fPrinted(0)
{
}

/**
 * Create a non recursive loop.
 * @param encl the enclosing loop
 * @param size the number of iterations of the loop
 */
Loop::Loop(Loop* encl, const string& size)
    : fIsRecursive(false),
      fRecSymbolSet(gGlobal->nil),
      fEnclosingLoop(encl),
      fSize(size),
      fOrder(-1),
      fIndex(-1),
      fUseCount(0),
      fPrinted(0)
{
}

/**
 * A loop with recursive dependencies can't be run alone.
 * It must be included into another loop.
 * returns true is this loop has recursive dependencies
 * and must be included in an enclosing loop
 */

bool Loop::hasRecDependencyIn(Tree S)
{
    Loop* l = this;
    while (l && isNil(setIntersection(l->fRecSymbolSet, S))) {
        l = l->fEnclosingLoop;
    }
    return l != 0;
}

/**
 * Test if a loop is empty that is if it contains no lines of code.
 * @return true if the loop is empty
 */
bool Loop::isEmpty()
{
    return fPreCode.empty() && fExecCode.empty() && fPostCode.empty() &&
           (fExtraLoops.begin() == fExtraLoops.end());
}

/**
 * Add a line of pre code (begin of the loop)
 */
void Loop::addPreCode(const Statement& stmt)
{
#ifdef TRACE
    cerr << this << "->addExecCode " << stmt.code() << endl;
#endif
    if (fCodeStack.size() > 0) {
        fCodeStack.top()->fPreCode.push_back(stmt);
    } else {
        fPreCode.push_back(stmt);
    }
}

/**
 * Add a line of exec code.
 */
void Loop::addExecCode(const Statement& stmt)
{
#ifdef TRACE
    cerr << this << "->addExecCode " << stmt.code() << endl;
#endif
    if (fCodeStack.size() > 0) {
        fCodeStack.top()->fExecCode.push_back(stmt);
    } else {
        fExecCode.push_back(stmt);
    }
}

/**
 * Add a line of post exec code (end of the loop).
 */
void Loop::addPostCode(const Statement& stmt)
{
#ifdef TRACE
    cerr << this << "->addPostCode " << stmt.code() << endl;
#endif
    if (fCodeStack.size() > 0) {
        fCodeStack.top()->fPostCode.push_front(stmt);
    } else {
        fPostCode.push_front(stmt);
    }
}

/**
 * Open a new IF block.
 * @param cond the condition of the OD block
 */
void Loop::openIFblock(const std::string& condition)
{
    CodeIFblock* b = new CodeIFblock(condition);
    fCodeStack.push(b);
}

/**
 * Open a new IF block.
 * @param cond the condition of the OD block
 */
void Loop::closeIFblock()
{
    CodeIFblock* b = dynamic_cast<CodeIFblock*>(fCodeStack.top());
    faustassert(b);
    fCodeStack.pop();

    addExecCode(Statement("", subst("if ($0) {", b->fCondition)));
    for (Statement s : b->fPreCode) {
        addExecCode(s.indent());
    }
    for (Statement s : b->fExecCode) {
        addExecCode(s.indent());
    }
    for (Statement s : b->fPostCode) {
        addExecCode(s.indent());
    }
    addExecCode(Statement("", "}"));
}

/**
 * Open a new OD block.
 * @param cond the condition of the OD block
 */
void Loop::openODblock(const string& od_factor)
{
    CodeODblock* b = new CodeODblock(od_factor);
    fCodeStack.push(b);
}

/**
 * Close the current/top OD block.
 */
void Loop::closeODblock()
{
    CodeODblock* b = dynamic_cast<CodeODblock*>(fCodeStack.top());
    faustassert(b);
    fCodeStack.pop();

    // addExecCode(Statement("", subst("if ($0) {", b->fODfactor)));
    addExecCode(Statement("", subst("for (int $0=0; $0<$1; $0++) {", b->fLoopIndex, b->fODfactor)));
    for (Statement s : b->fPreCode) {
        addExecCode(s.indent());
    }
    for (Statement s : b->fExecCode) {
        addExecCode(s.indent());
    }
    for (Statement s : b->fPostCode) {
        addExecCode(s.indent());
    }
    addExecCode(Statement("", "}"));
}

/**
 * Open a new US block.
 * @param cond the condition of the US block
 */
void Loop::openUSblock(const string& us_factor)
{
    CodeUSblock* b = new CodeUSblock(us_factor);
    fCodeStack.push(b);
}

/**
 * Close the current/top US block.
 */
void Loop::closeUSblock()
{
    CodeUSblock* b = dynamic_cast<CodeUSblock*>(fCodeStack.top());
    faustassert(b);
    fCodeStack.pop();

    addExecCode(Statement("", subst("for (int $0=0; $0<$1; $0++) {", b->fLoopIndex, b->fUSfactor)));
    for (Statement s : b->fPreCode) {
        addExecCode(s.indent());
    }
    for (Statement s : b->fExecCode) {
        addExecCode(s.indent());
    }
    for (Statement s : b->fPostCode) {
        addExecCode(s.indent());
    }
    addExecCode(Statement("", "}"));
}

/**
 * Open a new DS block.
 * @param cond the condition of the DS block
 */
void Loop::openDSblock(const string& ds_factor, const std::string& ds_counter)
{
    CodeDSblock* b = new CodeDSblock(ds_factor, ds_counter);
    fCodeStack.push(b);
}

/**
 * Close the current/top DS block.
 */
void Loop::closeDSblock()
{
    CodeDSblock* b = dynamic_cast<CodeDSblock*>(fCodeStack.top());
    faustassert(b);
    fCodeStack.pop();

    addExecCode(
        Statement("", subst("if (($1 != 0) & ($0 % $1) == 0) {", b->fDSCounter, b->fDSfactor)));
    for (Statement s : b->fPreCode) {
        addExecCode(s.indent());
    }
    for (Statement s : b->fExecCode) {
        addExecCode(s.indent());
    }
    for (Statement s : b->fPostCode) {
        addExecCode(s.indent());
    }
    addExecCode(Statement("", "}"));
}

/**
 * Absorb a loop by copying its recursive dependencies, its loop dependencies
 * and its lines of exec and post exec code.
 * @param l the Loop to be absorbed
 */
void Loop::absorb(Loop* l)
{
    // the loops must have the same number of iterations
    // cerr << "Loop absorbtion : " << this << " absorb " << l << endl;
    faustassert(fSize == l->fSize);
    fRecSymbolSet = setUnion(fRecSymbolSet, l->fRecSymbolSet);

    // update loop dependencies by adding those from the absorbed loop
    fBackwardLoopDependencies.insert(l->fBackwardLoopDependencies.begin(),
                                     l->fBackwardLoopDependencies.end());

    // add the line of code of the absorbed loop
    fPreCode.insert(fPreCode.end(), l->fPreCode.begin(), l->fPreCode.end());
    fExecCode.insert(fExecCode.end(), l->fExecCode.begin(), l->fExecCode.end());
    fPostCode.insert(fPostCode.begin(), l->fPostCode.begin(), l->fPostCode.end());
}

/**
 * Print a loop (unless it is empty)
 * @param n number of tabs of indentation
 * @param fout output stream
 */
void Loop::println(int n, ostream& fout)
{
    for (Loop* l : fExtraLoops) {
        l->println(n, fout);
    }

    if (fExtraLoops.size() > 0) {
        tab(n, fout);
        fout << "// Extra loops: ";
        for (Loop* l : fExtraLoops) {
            fout << l << " ";
        }
    }

    tab(n, fout);
    fout << "// Backward loops: ";
    bool emptyflag = true;
    for (Loop* l : fBackwardLoopDependencies) {
        emptyflag = false;
        fout << l << " ";
    }  ///< Loops that must be computed before this one
    if (emptyflag) {
        fout << "WARNING empty";
    }

    if (fForwardLoopDependencies.size() > 0) {
        tab(n, fout);
        fout << "// Forward loops: ";
        for (Loop* l : fForwardLoopDependencies) {
            fout << l << " ";
        }
    }

    tab(n, fout);
    fout << "// " << ((fIsRecursive) ? "Recursive" : "Vectorizable") << " loop: " << this;

    if (fPreCode.size() + fExecCode.size() + fPostCode.size() > 0) {
        if (fPreCode.size() > 0) {
            tab(n, fout);
            fout << "// pre processing";
            printlines(n, fPreCode, fout);
        }

        tab(n, fout);
        fout << "// exec code";
        tab(n, fout);
        fout << "for (int i=0; i<" << fSize << "; i++) {";
        printlines(n + 1, fExecCode, fout);
        tab(n, fout);
        fout << "}";

        if (fPostCode.size() > 0) {
            tab(n, fout);
            fout << "// post processing";
            printlines(n, fPostCode, fout);
        }
        tab(n, fout);
    } else {
        fout << "// empty loop " << this;
    }
}

/**
 * Print a parallel loop (unless it is empty). Should be called only for loop.
 * without pre and post processing
 * @param n number of tabs of indentation
 * @param fout output stream
 */
void Loop::printParLoopln(int n, ostream& fout)
{
    for (list<Loop*>::const_iterator s = fExtraLoops.begin(); s != fExtraLoops.end(); s++) {
        tab(n, fout);
        fout << "#pragma omp single";
        tab(n, fout);
        fout << "{";
        (*s)->println(n + 1, fout);
        tab(n, fout);
        fout << "}";
    }

    if (fPreCode.size() + fExecCode.size() + fPostCode.size() > 0) {
        tab(n, fout);
        fout << "// LOOP " << this;
        if (fPreCode.size() > 0) {
            tab(n, fout);
            fout << "#pragma omp single";
            tab(n, fout);
            fout << "{";
            tab(n + 1, fout);
            fout << "// pre processing";
            printlines(n + 1, fPreCode, fout);
            tab(n, fout);
            fout << "}";
        }

        tab(n, fout);
        fout << "// exec code";
        tab(n, fout);
        fout << "#pragma omp for";
        tab(n, fout);
        fout << "for (int i=0; i<" << fSize << "; i++) {";
        printlines(n + 1, fExecCode, fout);
        tab(n, fout);
        fout << "}";

        if (fPostCode.size() > 0) {
            tab(n, fout);
            fout << "#pragma omp single";
            tab(n, fout);
            fout << "{";
            tab(n + 1, fout);
            fout << "// post processing";
            printlines(n + 1, fPostCode, fout);
            tab(n, fout);
            fout << "}";
        }
        tab(n, fout);
    }
}

/**
 * Print a single loop (unless it is empty).
 * @param n number of tabs of indentation
 * @param fout output stream
 */
void Loop::printoneln(int n, ostream& fout)
{
    if (fPreCode.size() + fExecCode.size() + fPostCode.size() > 0) {
        tab(n, fout);
        fout << "for (int i=0; i<" << fSize << "; i++) {";
        if (fPreCode.size() > 0) {
            tab(n + 1, fout);
            fout << "// pre processing";
            printlines(n + 1, fPreCode, fout);
        }
        printlines(n + 1, fExecCode, fout);
        if (fPostCode.size() > 0) {
            tab(n + 1, fout);
            fout << "// post processing";
            printlines(n + 1, fPostCode, fout);
        }
        tab(n, fout);
        fout << "}";
    }
}

//-------------------------------------------------------
void Loop::concat(Loop* l)
{
    faustassert(l->fUseCount == 1);
    faustassert(fBackwardLoopDependencies.size() == 1);
    faustassert((*fBackwardLoopDependencies.begin()) == l);

    fExtraLoops.push_front(l);
    fBackwardLoopDependencies = l->fBackwardLoopDependencies;
}
