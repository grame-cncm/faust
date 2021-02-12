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

#include "transformDelayToTable.hh"

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
class TransformDelayToTable : public SignalIdentity {
    set<Tree> fInstr;  // the resulting set of instructions
   public:
    TransformDelayToTable() = default;
    set<Tree> operator()(const set<Tree>& I)
    {
        for (Tree i : I) fInstr.insert(self(i));
        return std::move(fInstr);
    }

   protected:
    /**
     * @brief compute the size 2^p of a delayline large enough for dmax+1 samples
     *
     * @param dmax the max delay
     * @return int 2^p >= dmax+1
     */
    static int dmax2size(int dmax)
    {
        int x = dmax + 1;
        int p = int(log2(x));
        int v = 1 << p;
        while (v < x) v = v << 1;
        faustassert(v >= x);
        return v;
    }
#if 0
    Tree transformation(Tree sig) override
    {
        faustassert(sig);

        Tree id, origin, dl, exp;
        int  nature, dmin, dmax;

        if (isSigInstructionDelayLineWrite(sig, id, origin, &nature, &dmax, exp)) {
            int  size = dmax2size(dmax);
            Tree tr   = sigInstructionTableWrite(id, origin, nature, size, sigGen(sigInt(0)),
                                               sigAND(sigTime(), sigInt(size - 1)), self(exp));
            fInstr.insert(tr);
            return tr;
        } else if (isSigInstructionDelayLineRead(sig, id, origin, &nature, &dmax, &dmin, dl)) {
            Tree wid  = (nature == kInt) ? uniqueID("W", sig) : uniqueID("W", sig);
            int  mask = dmax2size(dmax) - 1;
            if (isZero(dl)) {
                fInstr.insert(
                    sigInstructionTableAccessWrite(wid, origin, nature, dmin, id, sigAND(sigTime(), sigInt(mask))));
                return sigInstructionSharedRead(wid, sig, nature);
            } else {
                fInstr.insert(sigInstructionTableAccessWrite(wid, origin, nature, dmin, id,
                                                             sigAND(sigSub(sigTime(), self(dl)), sigInt(mask))));
                return sigInstructionSharedRead(wid, sig, nature);
            }
        } else {
            return SignalIdentity::transformation(sig);
        }
    }
#else
    Tree transformation(Tree sig) override
    {
        faustassert(sig);

        Tree id, origin, dl, exp;
        int  nature, dmin, dmax;

        if (isSigInstructionDelayLineWrite(sig, id, origin, &nature, &dmax, exp)) {
            int  size = dmax2size(dmax);
            Tree tr   = sigInstructionTableWrite(id, origin, nature, size, sigGen(sigInt(0)),
                                               sigAND(sigTime(), sigInt(size - 1)), self(exp));
            fInstr.insert(tr);
            return tr;
        } else if (isSigInstructionDelayLineRead(sig, id, origin, &nature, &dmax, &dmin, dl)) {
            int mask = dmax2size(dmax) - 1;
            if (isZero(dl)) {
                return sigInstructionTableRead(id, sig, nature, dmin, sigAND(sigTime(), sigInt(mask)));
            } else {
                return sigInstructionTableRead(id, sig, nature, dmin,
                                               sigAND(sigSub(sigTime(), self(dl)), sigInt(mask)));
            }
        } else {
            return SignalIdentity::transformation(sig);
        }
    }
#endif
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

    return d2t(I);
}
