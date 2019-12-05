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
 * @brief ReplaceDelay. When we have D1<dmax1>(0):=D2<dmin2>(dl2)
 * we replace all occurrences of D1<dmin1>(dl1) with equivalent
 * D2<dmin1+dmin2>(dl1+dl2)
 */
class ReplaceDelay : public SignalIdentity {
    Tree fID1;    // the ID of the delayline we want to replace
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
    static ReplaceDelay replacement(map<Tree, int> M, Tree instr)
    {
        Tree D1, origin1, exp, D2, origin2, dl2;
        int  nature1, nature2, dmax1, dmax2, dmin2;
        faustassert(isSigInstructionDelayLineWrite(instr, D1, origin1, &nature1, &dmax1, exp) &
                    isSigInstructionDelayLineRead(exp, D2, origin2, &nature2, &dmax2, &dmin2, dl2));
        cerr << "replacement rule for: " << ppsig(instr) << endl;
        return ReplaceDelay(D1, dmax1 + M[D2], D2, dmin2, dl2);
    }

   protected:
    Tree transformation(Tree sig) override
    {
        Tree ID1, ID2, origin, dl1, def;
        int  nature, dmin1, dmax2;

        if (isSigInstructionDelayLineRead(sig, ID1, origin, &nature, &dmax2, &dmin1, dl1) && (ID1 == fID1)) {
            // replace occurrences of ID1(dl)
            Tree r = sigInstructionDelayLineRead(fID2, origin, nature, dmax2, dmin1 + fDmin2, sigAdd(dl1, fDl2));
            cerr << "sigInstructionDelayLineRead: Replacement of " << ppsig(sig) << "\n\t by " << ppsig(r) << endl;
            return r;
        } else if (isSigInstructionDelayLineWrite(sig, ID2, origin, &nature, &dmax2, def) && (ID2 == fID2)) {
            // adjust definition of ID2 size
            Tree tdef = self(def);
            Tree r    = sigInstructionDelayLineWrite(fID2, origin, nature, std::max(fDmax1, dmax2), tdef);
            cerr << "isSigInstructionDelayLineWrite: Replacement of " << ppsig(sig) << "\n\t by " << ppsig(r) << endl;
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
    int  nature, dmax, dmin;

    return (isSigInstructionDelayLineWrite(instr, id1, origin1, &nature, &dmax, exp) &&
            isSigInstructionDelayLineRead(exp, id2, origin2, &nature, &dmax, &dmin, idx));
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
        int  nature, dmax;
        if (isSigInstructionDelayLineWrite(instr, id, origin, &nature, &dmax, def)) {
            M[id] = dmax;
        }
    }

    // Separate instructions I into substitutions S and normal instructions N
    for (Tree instr : I) {
        if (isSubstitution(instr)) {
            cerr << "Substituable def : " << ppsig(instr) << endl;
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
        ReplaceDelay rule = ReplaceDelay::replacement(M, S[n]);
        rule.trace(true, "ReplaceFusionDelay");

        // we update the remaining substitutions
        for (int i = 0; i < n; i++) {
            S[i] = rule.self(S[i]);
        }
        // we update the normal instructions
        for (int i = 0; i < m; i++) {
            N[i] = rule.self(N[i]);
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