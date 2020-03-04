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

#include "splitCommonSubexpr.hh"

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
class CommonSubexpr : public SignalIdentity {
   private:
    map<Tree, int> fOcc;

   public:
    set<Tree> fSplittedSignals;

   public:
    explicit CommonSubexpr(const map<Tree, int>& occ) : fOcc(occ) {}

   protected:
    bool needCache(Tree sig)
    {
        Tree   id, origin, dl, idx;
        int    nature, i, dmax, dmin;
        double r;

        return /*!(isSigInput(sig, &i)) && */ !isSigInstructionSharedRead(sig, id, origin, &nature) &&
               !isSigInstructionVectorRead(sig, id, origin, &nature) &&
               !isSigInstructionControlRead(sig, id, origin, &nature) && !isSigTime(sig) &&
               !isSigInstructionDelayLineRead(sig, id, origin, &nature, &dmax, &dmin, dl) &&
               !isSigInstructionTableRead(sig, id, origin, &nature, &dmin, idx) &&
               !isSigInstructionShortDLineRead(sig, id, origin, &nature, &dmin) && !isSigGen(sig) &&
               !isSigInt(sig, &i) && !isSigReal(sig, &r) && !isSigInstructionTimeRead(sig);
    }

    Tree transformation(Tree sig) override
    {
        faustassert(sig);
        Type t = getSimpleType(sig);
        int  n = fOcc[sig];

        if ((n > 1) && (t->variability() >= kSamp) && needCache(sig)) {
            Tree r  = SignalIdentity::transformation(sig);
            Tree id = (t->nature() == kInt) ? uniqueID("iVar", sig) : uniqueID("fVar", sig);
#if 1
            fSplittedSignals.insert(sigInstructionSharedWrite(id, sig, t->nature(), r));
            Tree inst = sigInstructionSharedRead(id, sig, t->nature());
#else
            // simulation of future vector mode
            fSplittedSignals.insert(sigInstructionVectorWrite(id, sig, t->nature(), r));
            Tree inst = sigInstructionVectorRead(id, sig, t->nature());
#endif
            return inst;
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
set<Tree> splitCommonSubexpr(const set<Tree>& I)
{
    CommonSubexpr cs(countOccurrences(I));

    set<Tree> R;
    for (Tree i : I) R.insert(cs.self(i));

    // insert the additional shared instructions
    for (Tree i : cs.fSplittedSignals) R.insert(i);
    return R;
}

/***************************************************************************************
 *                                  IMPLEMENTATION
 ***************************************************************************************/

/**
 * @brief add the occurrences of e and all its subexpressions
 *
 * @param O the occurrence count
 * @param e the expression
 */
void addOccurrences(map<Tree, int>& O, Tree e)
{
    Tree id, origin, idx;
    int  nature, dmin;
    int  n = ++O[e];

    if ((n == 1) || isSigInstructionTableRead(e, id, origin, &nature, &dmin, idx)) {
        // first occurrence of e or e is tableRead (tableread are not cached)
        // we visit its subexpressions
        tvec S;
        getSubSignals(e, S, false);
        for (Tree f : S) addOccurrences(O, f);
    }
}

/**
 * @brief Count the occurrences of every expression in I
 *
 * @param I a set of instructions
 * @return map<Tree,int> the occurrences
 */
map<Tree, int> countOccurrences(const set<Tree>& I)
{
    map<Tree, int> O;
    for (Tree i : I) addOccurrences(O, i);
    return O;
}

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
