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
 ********************************************f****************************
 ************************************************************************/

#include "transformTime.hh"

#include <map>

#include "global.hh"
#include "old_occurences.hh"
#include "ppsig.hh"
#include "property.hh"
#include "sigIdentity.hh"
#include "signalDependencies.hh"
#include "sigtyperules.hh"

using namespace std;

/**
 * @brief Transformation class used internally to split a signal
 * into a set of instructions
 *
 */
class TransformTime : public SignalIdentity {
    bool fHasTime = false;

   public:
    TransformTime() = default;
    bool hasTime() { return fHasTime; }

   protected:
    Tree transformation(Tree sig) override
    {
        faustassert(sig);

        if (isSigTime(sig)) {
            fHasTime = true;
            return sigInstructionTimeRead();
        } else {
            return SignalIdentity::transformation(sig);
        }
    }
};

/**
 * @brief Transform time into time instructions
 *
 * @return set<Tree> the resulting set of instructions
 */
set<Tree> transformTime(const set<Tree>& I)
{
    TransformTime TT;
    TT.trace(gGlobal->gDebugSwitch, "transformTime");

    set<Tree> R;
    for (Tree i : I) R.insert(TT.self(i));
    if (TT.hasTime()) R.insert(sigInstructionTimeWrite());
    return R;
}
