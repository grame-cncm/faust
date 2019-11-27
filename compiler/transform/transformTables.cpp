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

#include "transformTables.hh"
#include <map>
#include "global.hh"
#include "old_occurences.hh"
#include "ppsig.hh"
#include "property.hh"
#include "sigIdentity.hh"
#include "signalDependencies.hh"
#include "sigtyperules.hh"

using namespace std;

// static Tree           uniqueID(const char* prefix, Tree sig);
static map<Tree, int> countOccurrences(const set<Tree>& I);

/**
 * @brief Transforms old rd/rw tables into sigInstructionTableRead/Write pairs
 *
 */
class TransformTables : public SignalIdentity {
   public:
    set<Tree> fSplittedSignals;

   public:
    explicit TransformTables() = default;

   protected:
    Tree transformation(Tree sig) override
    {
        Tree tbl, ridx, id, itbl, widx, wsig, tblsize, init;

        if (isSigRDTbl(sig, tbl, ridx)) {
            Type t   = getSimpleType(sig);
            int  nat = t->nature();
            Tree id2, instr;
            cerr << "TRANFORMATION " << ppsig(sig) << endl;
            if (isSigWRTbl(tbl, id, itbl, widx, wsig)) {
                faustassert(isSigTable(itbl, id, tblsize, init));
                cerr << "We have a read-write table to tranform: " << ppsig(sig) << endl;
                id2   = uniqueID("RWT", tbl);
                instr = sigInstructionTableWrite(id2, tbl, nat, tree2int(tblsize), init, self(widx), self(wsig));

            } else {
                faustassert(isSigTable(tbl, id, tblsize, init));
                cerr << "We have a read-only table to tranform: " << ppsig(sig) << endl;
                id2   = uniqueID("RDT", tbl);
                instr = sigInstructionTableWrite(id2, tbl, nat, tree2int(tblsize), init, gGlobal->nil, gGlobal->nil);
            }
            fSplittedSignals.insert(instr);
            return sigInstructionTableRead(id2, sig, nat, 0, self(ridx));
        } else {
            return SignalIdentity::transformation(sig);
        }
    }
};

/**
 * @brief transform old rd/rw tables into sigInstructionTableRead/Write pairs
 *
 * @param I the initial set of instructions
 * @return set<Tree> the resulting set of instructions
 */
set<Tree> transformTables(const set<Tree>& I)
{
    TransformTables tt;

    set<Tree> R;
    for (Tree i : I) R.insert(tt.self(i));

    // insert the additional shared instructions
    for (Tree i : tt.fSplittedSignals) R.insert(i);
    return R;
}
