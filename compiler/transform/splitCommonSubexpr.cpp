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

/**
 * @brief Recursively visit expressions and count occurrences. We suppose expressions have been transformed into
 * instructions and no recursion remain.
 *
 */

class ExprOccurrences {
    map<Tree, int> fOccurrences;

    void countOccurrences(Tree e)
    {
        int n = ++fOccurrences[e];
        if (n == 1) {
            // first occurrence of e, we visit its subexpressions
            tvec S;
            getSubSignals(e, S, false);
            for (Tree f : S) {
                countOccurrences(f);
            }
        }
    }

   public:
    ExprOccurrences(const set<Tree>& I)
    {
        for (Tree i : I) countOccurrences(i);
    }

    int getOccurrences(Tree e) { return fOccurrences[e]; }
};

/**
 * @brief Transformation class used internally to split a signal
 * into a set of instructions
 *
 */
class CommonSubexpr : public SignalIdentity {
    ExprOccurrences& fOcc;

   public:
    set<Tree> fSplittedSignals;

   public:
    CommonSubexpr(ExprOccurrences& occ) : fOcc(occ) {}

   protected:
    virtual Tree transformation(Tree sig)
    {
        faustassert(sig);
        Type t = getSimpleType(sig);
        int  n = fOcc.getOccurrences(sig);
        Tree id, origin, dl;
        int  i, dmin;

        if ((n > 1) && (t->variability() >= kSamp) && !(isSigInput(sig, &i)) && !(isSigControlRead(sig, id, origin)) &&
            !(isSigDelayLineRead(sig, id, origin, &dmin, dl))) {
            cerr << "Candidate for Sharing: "
                 << " --" << ppsig(sig) << endl;
            return SignalIdentity::transformation(sig);
        } else {
            return SignalIdentity::transformation(sig);
        }
    }
};

set<Tree> splitCommonSubexpr(const set<Tree>& I)
{
    ExprOccurrences occ(I);

    CommonSubexpr cs(occ);

    set<Tree> R;
    for (Tree i : I) {
        R.insert(cs.self(i));
    }

    return R;
}