/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
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

/************************************************************************
 ************************************************************************
 * Split a list of signals into a set of instruction
 *
 *  USAGE : set<Tree> I = splitSignalsToInstr(fConditionProperty, L);
 *
 ************************************************************************
 ************************************************************************/

#include "splitAddBranches.hh"

#include <map>

#include "global.hh"
#include "old_occurences.hh"
#include "ppsig.hh"
#include "property.hh"
#include "sigIdentity.hh"
#include "sigtyperules.hh"

using namespace std;

static Tree           uniqueID(const char* prefix, Tree sig);
static map<Tree, int> countOccurrences(const set<Tree>& I);

/**
 * @brief Transformation class used internally to split a signal
 * into a set of instructions
 *
 */
class SplitAddBranches : public SignalIdentity {
   public:
    set<Tree> fSplittedSignals;

   public:
    explicit SplitAddBranches() {}

   protected:
    bool candidate(Tree sig)
    {
        Tree   id, origin, dl, idx, left, right;
        int    nature, i, dmax, dmin;
        double r;
        Tree   label, minv, maxv, val;
        return /*!(isSigInput(sig, &i)) && */ !isSigAdd(sig, left, right) &&
               !isSigInstructionControlRead(sig, id, origin, &nature) && !isSigTime(sig) &&
               !isSigInstructionDelayLineRead(sig, id, origin, &nature, &dmax, &dmin, dl) &&
               !isSigInstructionTableRead(sig, id, origin, &nature, &dmin, idx) &&
               !isSigInstructionShortDLineRead(sig, id, origin, &nature, &dmin) && !isSigGen(sig) &&
               !isSigInt(sig, &i) && !isSigReal(sig, &r);
    }

    Tree shareCandidate(Tree sig)
    {
        if (candidate(sig)) {
            Type t  = getSimpleType(sig);
            Tree r  = SignalIdentity::transformation(sig);
            Tree id = (t->nature() == kInt) ? uniqueID("AI", sig) : uniqueID("AF", sig);
            fSplittedSignals.insert(sigInstructionSharedWrite(id, sig, t->nature(), r));
            Tree inst = sigInstructionSharedRead(id, sig, t->nature());
            return inst;
        } else {
            return SignalIdentity::transformation(sig);
        }
    }

    Tree transformation(Tree sig) override
    {
        faustassert(sig);
        Type t = getSimpleType(sig);
        Tree id, origin, dl, idx, left, right;
        int  nature, i, dmax, dmin;
        Tree label, minv, maxv, val;

        if ((t->variability() >= kSamp) && isSigAdd(sig, left, right)) {
            // potential candidate
            Type t1 = getSimpleType(left);
            Type t2 = getSimpleType(right);

            if ((t1->variability() == kSamp) && (t2->variability() == kSamp)) {
                return sigAdd(shareCandidate(left), shareCandidate(right));
            } else {
                return SignalIdentity::transformation(sig);
            }

        } else {
            return SignalIdentity::transformation(sig);
        }
    }
};

/**
 * @brief Split common subexpressions into instructions
 *
 * @param I the initial set of instructions
 * @return set<Tree> the resulting set of instructions
 */
set<Tree> splitAddBranches(const set<Tree>& I)
{
    SplitAddBranches sab;
    sab.trace(gGlobal->gDebugSwitch, "splitAddBranches");

    set<Tree> R;
    for (Tree i : I) R.insert(sab.self(i));

    // insert the additional shared instructions
    for (Tree i : sab.fSplittedSignals) R.insert(i);
    return R;
}

/***************************************************************************************
 *                                  IMPLEMENTATION
 ***************************************************************************************/

/**
 * @brief associates a unique ID to a signal
 *
 * @param prefix the prefix of the ID
 * @param sig the signal that will be associated to the id
 * @return Tree always the same unique ID
 */
Tree uniqueID(const char* prefix, Tree sig)
{
    Tree ID;
    Tree key = tree(symbol(prefix));
    if (getProperty(sig, key, ID)) {
        return ID;
    } else {
        ID = tree(unique(prefix));
        setProperty(sig, key, ID);
        return ID;
    }
}
