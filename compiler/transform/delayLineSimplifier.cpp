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

#include "delayLineSimplifier.hh"
#include <stdlib.h>
#include <cstdlib>
#include <map>
#include <set>
#include "global.hh"
#include "ppsig.hh"
#include "property.hh"
#include "sigIdentity.hh"
#include "signals.hh"
#include "sigtyperules.hh"
#include "tlib.hh"
#include "tree.hh"
#include "xtended.hh"

/*
 USELESS DELAY LINES

 - delayline defined in termes of another delayline:
    D1<dmax1> = D2<dmin2>(E); =>
        remove D1 definition
        replace occurrences of D1<dmin1>(F) by D2<dmin2+dmin1>(E+F)
        replace definition of D2<dmax2> = G; by D2<dmax2+dmax1> = G;
 - useless delay:
    D1<0> = E; =>
        remove D1 definition
        replace occurrences of D1(_) by E

 */

// Make explicit automatic promotion to float
class ReplaceDelay : public SignalIdentity {
    Tree fID1;
    Tree fID2;
    int  fDmin;
    Tree fIdx;

   public:
    ReplaceDelay(Tree ID1, Tree ID2, int dmin, Tree Idx) : fID1(ID1), fID2(ID2), fDmin(dmin), fIdx(Idx) {}

   protected:
    virtual Tree transformation(Tree sig)
    {
        Tree ID, origin, dl;
        int  dmin;
        if (isSigDelayLineRead(sig, ID, origin, &dmin, dl) && (ID == fID1)) {
            return sigDelayLineRead(fID2, origin, dmin + fDmin, sigAdd(dl, fIdx));
        } else {
            return SignalIdentity::transformation(sig);
        }
    }
};

class substitution {
    Tree          D1, D2, Idx;
    int           dmax1, dmin2;
    ReplaceDelay* fReplaceDelay;

   public:
    substitution(Tree instr)
    {
        Tree origin1, origin2, exp;
        if (isSigDelayLineWrite(instr, D1, origin1, &dmax1, exp) && isSigDelayLineRead(exp, D2, origin2, &dmin2, Idx)) {
            fReplaceDelay = new ReplaceDelay(D1, D2, dmin2, Idx);
        } else {
            cerr << "IMPOSSIBLE ERROR" << endl;
            fReplaceDelay = NULL;
        }
    }
    /**
     * @brief  return a modified instruction where id1(f) occurrences are replaced by id2(f+idx)
     *
     * @param instr the instruction to modify
     * @return Tree the modified instruction
     */
    Tree substitute(Tree instr) { return fReplaceDelay->self(instr); }
    // and id2<M> := def; by id2<M+dmax> := def;
};

/**
 * @brief indicates if a definition can be susbtituted
 *
 * @param instr the instruction to test
 * @return true if instr is D1<N> := D2(E)
 * @return false otherwise
 */
bool isSubstitution(Tree instr)
{
    Tree id1, id2, origin1, origin2, exp, idx;
    int  dmax, dmin;

    return (isSigDelayLineWrite(instr, id1, origin1, &dmax, exp) && isSigDelayLineRead(exp, id2, origin2, &dmin, idx));
}

set<Tree> delayLineSimplifier(const set<Tree>& I)
{
    // separate I into substitution instructions S and normal instructions N
    vector<Tree> S;
    vector<Tree> N;
    for (Tree instr : I) {
        if (isSubstitution(instr)) {
            S.push_back(instr);
        } else {
            N.push_back(instr);
        }
    }

    // loop while we have substitutions
    int m = N.size();
    int n = S.size();
    while (n > 0) {
        n = n - 1;
        // we create a substitution rule s
        substitution s(S[n]);
        // we update the remaining substitutions
        for (int i = 0; i < n; i++) {
            S[i] = s.substitute(S[i]);
        }
        // we update the normal instructions
        for (int i = 0; i < m; i++) {
            N[i] = s.substitute(N[i]);
        }
    }

    // All substitutions have been applied,
    // convert vector N into a set R
    set<Tree> R;
    for (int i = 0; i < m; i++) {
        R.insert(N[i]);
    }

    return R;
}