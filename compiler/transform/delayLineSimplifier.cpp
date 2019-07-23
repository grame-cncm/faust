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

/**
 * @brief Replace D1<dmin1>(dl1) occurrences
 * with D2<dmin1+dmin2>(dl1+dl2), where D1<dmax1>(0):=D2<dmin2>(dl2)
 *
 */
class ReplaceDelay : public SignalIdentity {
    Tree fID1;    // D1
    int  fDmax1;  // <dmax1> :=
    Tree fID2;    // D2
    int  fDmin2;  // <dmin2>
    Tree fDl2;    // (dl2)

   public:
    // based on definition D1<dmax1>(0) := D2<dmin2>(dl2)
    ReplaceDelay(Tree ID1, int dmax1, Tree ID2, int dmin2, Tree dl2)
        : fID1(ID1), fDmax1(dmax1), fID2(ID2), fDmin2(dmin2), fDl2(dl2)
    {
    }

    /**
     * @brief Creates a ReplaceDelay
     *
     * @param instr the definition we want to replace
     * @return ReplaceDelay*
     */
    static ReplaceDelay* replacement(map<Tree, int> M, Tree instr)
    {
        Tree D1, origin1, exp, D2, origin2, dl2;
        int  dmax1, dmin2;
        if (isSigDelayLineWrite(instr, D1, origin1, &dmax1, exp) && isSigDelayLineRead(exp, D2, origin2, &dmin2, dl2)) {
            // cerr << "replacement rule for: " << ppsig(instr) << endl;
            return new ReplaceDelay(D1, dmax1 + M[D2], D2, dmin2, dl2);
        } else {
            return NULL;
        }
    }

   protected:
    virtual Tree transformation(Tree sig)
    {
        Tree ID1, ID2, origin, dl1, def;
        int  dmin1, dmax2;

        if (isSigDelayLineRead(sig, ID1, origin, &dmin1, dl1) && (ID1 == fID1)) {
            // replace occurrences of ID1(dl)
            Tree r = sigDelayLineRead(fID2, origin, dmin1 + fDmin2, sigAdd(dl1, fDl2));
            // cerr << "sigDelayLineRead: Replacement of " << ppsig(sig) << "\n\t by " << ppsig(r) << endl;
            return r;
        } else if (isSigDelayLineWrite(sig, ID2, origin, &dmax2, def) && (ID2 == fID2)) {
            // adjust definition of ID2 size
            Tree tdef = self(def);
            Tree r    = sigDelayLineWrite(fID2, origin, std::max(fDmax1, dmax2), tdef);
            // cerr << "isSigDelayLineWrite: Replacement of " << ppsig(sig) << "\n\t by " << ppsig(r) << endl;
            return r;
        } else {
            return SignalIdentity::transformation(sig);
        }
    }
};

/**
 * @brief indicates if a definition can be susbtituted
 *
 * @param instr the instruction to test
 * @return true if instr is D1<N> := D2(E)
 * @return false otherwise
 */
static bool isSubstitution(Tree instr)
{
    Tree id1, id2, origin1, origin2, exp, idx;
    int  dmax, dmin;

    return (isSigDelayLineWrite(instr, id1, origin1, &dmax, exp) && isSigDelayLineRead(exp, id2, origin2, &dmin, idx));
}

/**
 * @brief Remove delay lines definitions of type D1<dmax1>(0) := D2<dmin2>(dl2)
 * by replacing occurrences of D1(dl1) with D2(dl1+dl2)
 *
 * @param I a set of instructions to simplify
 * @return set<Tree> the simplified instructions
 */
set<Tree> delayLineSimplifier(const set<Tree>& I)
{
    vector<Tree>   S;  // substituable delaylines definitions
    vector<Tree>   N;  // Normal instructions
    map<Tree, int> M;  // the size of all delay lines

    // cerr << "BEGIN Delay simplification " << endl;
    // Collect into M the size of all delay lines
    for (Tree instr : I) {
        Tree id, origin, def;
        int  dmax;
        if (isSigDelayLineWrite(instr, id, origin, &dmax, def)) {
            M[id] = dmax;
        }
    }

    // Separate instructions I into substitutions S and normal instructions N
    for (Tree instr : I) {
        if (isSubstitution(instr)) {
            // cerr << "Substituable def : " << ppsig(instr) << endl;
            S.push_back(instr);
        } else {
            // cerr << "Normal definition: " << ppsig(instr) << endl;
            N.push_back(instr);
        }
    }

    // loop while we have substitutions
    int m = N.size();
    int n = S.size();
    while (n > 0) {
        n = n - 1;
        // we create a substitution rule
        ReplaceDelay* rule = ReplaceDelay::replacement(M, S[n]);

        // we update the remaining substitutions
        for (int i = 0; i < n; i++) {
            S[i] = rule->self(S[i]);
        }
        // we update the normal instructions
        for (int i = 0; i < m; i++) {
            N[i] = rule->self(N[i]);
        }
    }

    // All substitutions have been applied,
    // convert vector N into a set R
    // cerr << endl << "Applying substitutions: " << endl;
    set<Tree> R;
    for (int i = 0; i < m; i++) {
        // cerr << i << " : " << ppsig(N[i]) << endl;
        R.insert(N[i]);
    }

    return R;
}