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

#include "signalSplitter.hh"

#include "global.hh"
#include "old_occurences.hh"
#include "ppsig.hh"
#include "property.hh"
#include "sigIdentity.hh"
#include "signalDependencies.hh"
#include "sigtyperules.hh"

/**
 * @brief Transformation class used internally to split a signal
 * into a set of instructions
 *
 */
class SignalSplitter : public SignalIdentity {
    property<Tree> fDelayLineName;
    old_OccMarkup* fOccMarkup;

   public:
    std::set<Tree> fSplittedSignals;

   public:
    SignalSplitter(old_OccMarkup* om) : fOccMarkup(om) {}
    virtual ostream& print(ostream& dst) const;

   protected:
    Tree transformation(Tree sig) override;
};

/**
 * @brief Split a list of signals into a set of instructions
 *
 * @param conditionProperty
 * @param LS the list of signals to split
 * @return set<Tree> the set of instructions
 */
set<Tree> splitSignalsToInstr(const map<Tree, Tree>& conditionProperty, Tree LS)
{
    old_OccMarkup* fOccMarkup = new old_OccMarkup(conditionProperty);
    fOccMarkup->mark(LS);  // annotate L3 with occurrences analysis

    SignalSplitter SS(fOccMarkup);
    SS.trace(false, "Signal Splitter");
    SS.mapself(LS);
    return SS.fSplittedSignals;
}

/********************************************************************
                            IMPLEMENTATION
**********************************************************************/

// Make explicit automatic promotion to float

Tree SignalSplitter::transformation(Tree sig)
{
    faustassert(sig);
    int             n;
    double          v;
    Tree            id, x, y, tbl, tblsize, idx, widx, wsig;
    Type            t   = getCertifiedSigType(sig);
    old_Occurences* occ = fOccMarkup->retrieve(sig);

    if (isSigInt(sig, &n) || isSigReal(sig, &v)) {
        return sig;

    } else if (isSigOutput(sig, &n, x)) {
        Tree r = self(x);
        fSplittedSignals.insert(sigOutput(n, r));
        return sigOutput(n, r);

    } else if (isSigFixDelay(sig, x, y)) {
        int      dmax = fOccMarkup->retrieve(x)->getMaxDelay();
        Type     ty   = getCertifiedSigType(y);
        interval i    = ty->getInterval();
        Tree     rec, var, le;

        if (isProj(x, &n, rec)) {
            if (isRec(rec, var, le)) {
                if (dmax == 0) {
                    // cerr << "FALSE RECURSION " << endl;
                    return self(nth(le, n));
                }
                Tree id;
                if (!fDelayLineName.get(x, id)) {
                    // Never visited before, it is the first time for this branch
                    id = tree(unique("R"));     // we need a unique id for the recursive delay line
                    fDelayLineName.set(x, id);  // we save it for the next visit
                    fSplittedSignals.insert(sigInstructionDelayLineWrite(id, x, t->nature(), dmax, self(nth(le, n))));
                }
                Tree w = self(y);
                return sigInstructionDelayLineRead(id, x, t->nature(), dmax, int(i.lo), w);

            } else {
                // This case is impossible (in principle ;-))
                faustassert(0);
                return nullptr;  // needed to avoid compiler warning
            }
        } else {
            // Delay on a regular expression
            Tree id;
            if (!fDelayLineName.get(x, id)) {
                // The delayed signal was never visited before
                id = tree(unique("D"));     // we need a unique id for it
                fDelayLineName.set(x, id);  // we save it for the next visit
                fSplittedSignals.insert(sigInstructionDelayLineWrite(id, x, t->nature(), dmax, self(x)));
            }
            Tree w = self(y);
            return sigInstructionDelayLineRead(id, x, t->nature(), dmax, int(i.lo), w);
        }
    } else if (isSigRDTbl(sig, tbl, idx)) {
        cerr << " A sigRDTbl : " << ppsig(sig) << endl;
        Tree r = SignalIdentity::transformation(sig);
        cerr << "transformed into : " << ppsig(r) << endl;
        return r;

    } else if (isSigWRTbl(sig, id, tbl, widx, wsig)) {
        cerr << " A sigWRTbl : " << ppsig(sig) << endl;
        Tree r = SignalIdentity::transformation(sig);
        cerr << "transformed into : " << ppsig(r) << endl;
        return r;

    } else if (isSigTable(sig, id, tblsize, wsig)) {
        cerr << " A sigTable : " << ppsig(sig) << endl;
        Tree r = SignalIdentity::transformation(sig);
        cerr << "transformed into : " << ppsig(r) << endl;
        return r;

    } else if (occ->hasMultiOccurences() && (t->variability() < kSamp)) {
        Tree r  = SignalIdentity::transformation(sig);
        Tree id = uniqueID("C", sig);
        fSplittedSignals.insert(sigControlWrite(id, sig, t->nature(), r));
        Tree inst = sigControlRead(id, sig, t->nature());
        return inst;
    } else {
        return SignalIdentity::transformation(sig);
    }
}

ostream& SignalSplitter::print(ostream& dst) const
{
    string sep = "";
    dst << "Splitter::fSpittedSignals {\n\t";
    for (auto t : fSplittedSignals) {
        dst << sep << ppsig(t);
        sep = ",\n\t";
    }
    return dst << "\n}\n";
}
