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

#include "transformOld2NewTables.hh"
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
// static map<Tree, int> countOccurrences(const set<Tree>& I);

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
        Tree tbl, ridx, id, itbl, widx, wsig, tblsize, tblinit;

        if (isSigRDTbl(sig, tbl, ridx)) {
            Type t   = getSimpleType(sig);
            int  nat = t->nature();

            if (isSigTable(tbl, id, tblsize, tblinit)) {
                // Case of a readonly table
                Tree id2   = uniqueID("TRO", tbl);  // the name of the table. It will be shared if we have several readers
                Tree instr = sigInstructionTableWrite(id2, tbl, nat, tree2int(tblsize), tblinit, gGlobal->nil, gGlobal->nil);
                fSplittedSignals.insert(instr);  // This instruction will only be used to init the table
                return sigInstructionTableRead(id2, sig, nat, 0, self(ridx));
            } else if (isSigWRTbl(tbl, id, itbl, widx, wsig)) {
                // Case of a readwrite table
                if (isSigTable(itbl, id, tblsize, tblinit)) {
                    // The id should be the same TODO
                    Tree id2   = uniqueID("TRW", sig);
                    Tree instr = sigInstructionTableWrite(id2, tbl, nat, tree2int(tblsize), tblinit, self(widx), self(wsig));
                    fSplittedSignals.insert(instr);
                    // Cache table read
                    if (t->variability() == kBlock) {
                        Tree wid    = (nat == kInt) ? uniqueID("CI", sig) : uniqueID("CF", sig);
                        Tree winstr = sigInstructionControlWrite(wid, sig, nat, sigInstructionTableRead(id2, sig, nat, 0, self(ridx)));
                        Tree rinstr = sigInstructionControlRead(wid, sig, nat);
                        fSplittedSignals.insert(winstr);
                        return rinstr;
                    } else if (t->variability() == kSamp) {
                        Tree wid    = (nat == kInt) ? uniqueID("VI", sig) : uniqueID("VF", sig);
                        Tree winstr = sigInstructionSharedWrite(wid, sig, nat, sigInstructionTableRead(id2, sig, nat, 0, self(ridx)));
                        Tree rinstr = sigInstructionSharedRead(wid, sig, nat);
                        fSplittedSignals.insert(winstr);
                        return rinstr;
                    } else {
                        std::cerr << "NOT SUPPOSED TO HAPPEN" << std::endl;
                        return nullptr;
                        exit(1);
                    }
                } else {
                    std::cerr << "NOT SUPPOSED TO HAPPEN 1" << std::endl;
                    exit(1);
                    return nullptr;
                }
            } else {
                std::cerr << "NOT SUPPOSED TO HAPPEN 2" << std::endl;
                exit(1);
                return nullptr;
            }
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
set<Tree> transformOld2NewTables(const set<Tree>& I)
{
    TransformTables tt;

    tt.trace(gGlobal->gDebugSwitch, "transformOld2NewTables");

    // cerr << "\n\nENTER TRANSFORM OLD RD/RW TABLES\n" << endl;

    set<Tree> R;
    for (Tree i : I) R.insert(tt.self(i));
    // cerr << "\nEXIT TRANSFORM OLD RD/RW TABLES\n" << endl;

    // insert the additional shared instructions
    for (Tree i : tt.fSplittedSignals) R.insert(i);
    return R;
}
