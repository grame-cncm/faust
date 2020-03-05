/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#include "shortDelayLineSimplifier.hh"
#include <cstdlib>
#include <map>
#include <set>
#include "global.hh"
#include "interval.hh"
#include "ppsig.hh"
#include "property.hh"
#include "sigConstantPropagation.hh"
#include "sigIdentity.hh"
#include "signalVisitor.hh"
#include "signals.hh"
#include "sigtyperules.hh"
#include "tlib.hh"
#include "tree.hh"
#include "xtended.hh"
/**
 * A visitor that removes candidates that can't be simplified as short dlines
 *
 */
class removeFalseSDL : public SignalVisitor {
    Tree       fID;
    set<Tree>& fCandidates;

   public:
    /**
     * @brief Construct a new Replace Delay object
     *
     * @param instr
     */
    removeFalseSDL(Tree ID, set<Tree>& candidates) : fID(ID), fCandidates(candidates) {}

   protected:
    void visit(Tree sig) override
    {
        Tree ID1, origin, dl1;
        int  nature, dmax1, dmin1;

        if (isSigInstructionDelayLineRead(sig, ID1, origin, &nature, &dmax1, &dmin1, dl1) && (ID1 != fID) &&
            (dmax1 == 1) && !isZero(dl1)) {
            fCandidates.erase(ID1);
            // cerr << "ID removed from candidates (used delayed outside its definition): " << *ID1 << endl;
            self(dl1);
        } else {
            SignalVisitor::visit(sig);
        }
    }
};

class replaceShortDLine : public SignalIdentity {
    const set<Tree>& fCandidates;

   public:
    /**
     * @brief Construct a new Replace Delay object
     *
     * @param instr
     */
    replaceShortDLine(const set<Tree>& candidates) : fCandidates(candidates) {}

   protected:
    bool isCandidate(Tree ID) { return fCandidates.find(ID) != fCandidates.end(); }

    Tree transformation(Tree sig) override
    {
        Tree ID1, origin, dl1, content;
        int  nature, dmax1, dmin1;

        if (isSigInstructionDelayLineRead(sig, ID1, origin, &nature, &dmax1, &dmin1, dl1) && isCandidate(ID1)) {
            return sigInstructionShortDLineRead(ID1, origin, nature, dmin1);
        } else if (isSigInstructionDelayLineWrite(sig, ID1, origin, &nature, &dmax1, content) && isCandidate(ID1)) {
            return sigInstructionShortDLineWrite(ID1, origin, nature, self(content));
        } else {
            return SignalIdentity::transformation(sig);
        }
    }
};

/**
 * @brief Indicates if an expression is a potential candidate for
 * short delay line optimization
 *
 * @param exp the expression to test
 * @param id the delay line ID if candidate
 * @return true it is a potential candidate
 * @return false not a candidate
 */
static bool isSDLCandidate(Tree exp, Tree& id)
{
    Tree origin, content;
    int  nature, dmax;
    return (isSigInstructionDelayLineWrite(exp, id, origin, &nature, &dmax, content) && (dmax == 1));
}

/**
 * @brief filter out candidate used delayed outside their definition
 *
 * @param i instruction to visite
 * @param C set of candidate to filter
 */
static void filterCandidate(Tree i, set<Tree>& C)
{
    Tree id;
    bool indef = isSDLCandidate(i, id);
    if (!indef) id = gGlobal->nil;
    removeFalseSDL rfsdl(id, C);
    rfsdl.trace(gGlobal->gDebugSwitch, "removeFalseSDL");
    rfsdl.self(i);
}

/**
 * @brief Simplifies short dlines
 *
 * @param I the set of instructions to tranform
 * @return set<Tree> of transformed instructions
 */
set<Tree> ShortDelayLineSimplifier(const set<Tree>& I)
{
    set<Tree> C;
    Tree      id;
    set<Tree> J;

    // compute the set of potential candidates
    for (Tree i : I)
        if (isSDLCandidate(i, id)) C.insert(id);

// remove false candidates
#if 1
    for (Tree i : I) filterCandidate(i, C);
#endif

    // print ID of remaining candidates for short dlines
    if (C.size() > 0) {
        cerr << ">>>>Short dlines: ";
        for (Tree i : C) cerr << *i << " ";
        cerr << endl;
    }

    // create a transformation to replace the short dlines
    replaceShortDLine rsdl(C);
    rsdl.trace(gGlobal->gDebugSwitch, "replaceShortDLine");

    // replace the short dlines by applying the transformation
    for (Tree i : I) J.insert(rsdl.self(i));

    return J;
}
