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

#include "transformDelayToTable.hh"

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
class TransformDelayToTable : public SignalIdentity {

   public:
    TransformDelayToTable() {}

   protected:
    virtual Tree transformation(Tree sig)
    {
        faustassert(sig);
        
        Tree id, origin, dl, exp, idx;
        int  i, dmin, dmax;

        if (isSigDelayLineWrite(sig, id, origin, &dmax, exp)) {
            Tree tr = sigTableWrite(id, origin, dmax, sigInt(0),sigInt(0), exp);
            return tr;
        } else if (isSigDelayLineRead(sig, id, origin, &dmin, dl)) {
            Tree tr = sigTableRead(id, origin, dmin, dl);
            return tr;
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
set<Tree> transformDelayToTable(const set<Tree>& I)
{
    TransformDelayToTable d2t;

    set<Tree> R;
    for (Tree i : I) R.insert(d2t.self(i));
    return R;
}

