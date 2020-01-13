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

/*
 We simplify delay lines based on the equivalence rule: @(k):@(d) = @(k+d)
 For every definition of type <dmax1>DL1:=<dmax2>DL2(k) we replace
 all occurrences <dmax1>DL1(d) with <(dmax2,k+dmax1)>DL2(k+d)
 */

// Make explicit automatic promotion to float

/**
 * @brief ReplaceDelay. An expression tranformation that removes
 * all definitions of type <dmax1>DL1:=<dmax2>DL2(k) and replaces
 * all occurrences <dmax1>DL1(d) with <(dmax2,k+dmax1)>DL2(k+d).
 * Please note that k must be constant for the substitution to be
 * correct.
 */
class ReplaceDelay : public SignalIdentity {
    bool fValid;
    Tree fID1;    // the ID of the delayline we want to replace
    int  fDmax1;  //
    Tree fID2;    // the ID of the delayline we will reuse
    int  fDmax2;  //
    int  fDmin2;  //
    Tree fDl2;    // its delay, must be constant and equal to fDmin2
    int  fDmaxm;  // the new fDmax2

   public:
    /**
     * @brief Construct a new Replace Delay object
     *
     * @param instr
     */
    ReplaceDelay(Tree instr)
    {
        Tree origin1, origin2, exp;
        int  nature1, nature2;

        if (isSigInstructionDelayLineWrite(instr, fID1, origin1, &nature1, &fDmax1, exp) &&
            isSigInstructionDelayLineRead(exp, fID2, origin2, &nature2, &fDmax2, &fDmin2, fDl2)) {
            // we check that dl2 is a constant delay
            Type     t = getSimpleType(fDl2);
            interval I = t->getInterval();
            if ((I.lo == I.hi) && (int(I.lo) == fDmin2)) {
                // dl2 is a constant delay, it is a valid substituition
                fValid = true;
                fDmaxm = std::max(fDmax2, fDmax1 + fDmin2);
            } else {
                fValid = false;  // not a constant delay;
            }
        } else {
            fValid = false;  // not a replaceable delay line
        }
    }

    /**
     * @brief we should always check that the rule is valid before using it
     *
     * @return true
     * @return false
     */
    bool valid() { return fValid; }

   protected:
    Tree transformation(Tree sig) override
    {
        Tree ID1, ID2, origin, dl1, def;
        int  nature, dmax1, dmin1, dmax2;

        faustassert(fValid);  // we should only apply valid transformations

        if (isSigInstructionDelayLineRead(sig, ID1, origin, &nature, &dmax1, &dmin1, dl1) && (ID1 == fID1)) {
            SignalConstantPropagation T;
            T.trace(gGlobal->gDebugSwitch, "delayline index simplification");
            Tree dl = T.self(sigAdd(dl1, fDl2));
            return sigInstructionDelayLineRead(fID2, origin, nature, fDmaxm, dmin1 + fDmin2, dl);
        } else if (isSigInstructionDelayLineWrite(sig, ID2, origin, &nature, &dmax2, def) && (ID2 == fID2)) {
            return sigInstructionDelayLineWrite(fID2, origin, nature, fDmaxm, self(def));
        } else {
            return SignalIdentity::transformation(sig);
        }
    }
};

/**
 * @brief Remove delay lines definitions of type DL1 := DL2(k)
 * by replacing occurrences of DL1(d1) with DL2(k+d1)
 *
 * @param I a set of instructions to simplify
 * @return set<Tree> the simplified instructions
 */
set<Tree> delayLineSimplifier(const set<Tree>& I)
{
    vector<Tree> S;  // substituable delaylines definitions
    vector<Tree> N;  // Normal instructions

    // Separate instructions I into substitutions S and normal instructions N
    for (Tree instr : I) {
        ReplaceDelay rule(instr);
        if (rule.valid()) {
            cerr << "Substituable def : " << ppsig(instr) << endl;
            S.push_back(instr);
        } else {
            // cerr << "Normal definition: " << ppsig(instr) << endl;
            N.push_back(instr);
        }
    }

    // loop while we have substitutions
    const int m = N.size();
    int       n = S.size();
    while (n > 0) {
        // we start from the bottom of the delaylines
        n = n - 1;
        // we create a substitution rule
        ReplaceDelay rule{S[n]};
        rule.trace(gGlobal->gDebugSwitch, "ReplaceFusionDelay");

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

class removeFalseSDL : public SignalVisitor {
    bool       fInsideDef;
    Tree       fID;
    set<Tree>& fCandidates;

   public:
    /**
     * @brief Construct a new Replace Delay object
     *
     * @param instr
     */
    removeFalseSDL(bool b, Tree ID, set<Tree>& candidates) : fInsideDef(b), fID(ID), fCandidates(candidates) {}

   protected:
    void visit(Tree sig) override
    {
        Tree ID1, origin, dl1;
        int  nature, dmax1, dmin1;

        if (isSigInstructionDelayLineRead(sig, ID1, origin, &nature, &dmax1, &dmin1, dl1) && (ID1 != fID) &&
            (dmax1 == 1) && !isZero(dl1)) {
            fCandidates.erase(ID1);  // ID1 can't be compiled as a short dline (used delayed outside its definition)
            cerr << "ID removed from candidates: " << *ID1 << endl;
            self(dl1);
        } else {
            SignalVisitor::visit(sig);
        }
    }
};

/**
 * @brief isSDLCandidate(exp)
 *
 * @param exp
 * @return true
 * @return false
 */
static bool isSDLCandidate(Tree exp, Tree& id)
{
    Tree origin, content;
    int  nature, dmax;

    return (isSigInstructionDelayLineWrite(exp, id, origin, &nature, &dmax, content) && (dmax == 1));
}

/**
 * @brief
 *
 * @param i instruction to visite
 * @param C set of candidate to filter
 */
static void filterCandidate(Tree i, set<Tree>& C)
{
    Tree id;
    if (isSDLCandidate(i, id)) {
        removeFalseSDL rfsdl(true, id, C);
        rfsdl.self(i);
    } else {
        removeFalseSDL rfsdl(false, gGlobal->nil, C);
        rfsdl.self(i);
    }
}

/**
 * @brief
 *
 * @param I
 * @return set<Tree>
 */
void ShortDelayLineSimplifier(const set<Tree>& I, set<Tree>& C)
{
    for (Tree i : I) {
        Tree id;
        if (isSDLCandidate(i, id)) {
            cerr << "Add potential candidate: " << *id << endl;
            C.insert(id);  // candidate for a shortDLine
        }
    }

    for (Tree i : I) {
        filterCandidate(i, C);
    }
    cerr << "Remaining candidates {";
    for (Tree idd : C) cerr << *idd << " ";
    cerr << "}" << endl;
}
