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
#include "signalSplitter.hh"

#include <stdlib.h>
#include <cstdlib>
#include <map>

#include "digraph.hh"
#include "digraphop.hh"
#include "global.hh"
#include "ppsig.hh"
#include "property.hh"
#include "signals.hh"
#include "sigtyperules.hh"
#include "tlib.hh"
#include "tree.hh"
#include "xtended.hh"

static Tree uniqueID(const char* prefix, Tree sig);

/********************************************************************
SignalSplitter: transforms a list of signals into a list of
"instructions".


Computes constant expressions
**********************************************************************/

Tree SignalSplitter::transformation(Tree sig)
{
    faustassert(sig);
    int             i;
    double          v;
    Tree            x, y;
    Type            t   = getCertifiedSigType(sig);
    old_Occurences* occ = fOccMarkup->retrieve(sig);

    if (isSigInt(sig, &i) || isSigReal(sig, &v)) {
        return sig;

    } else if (isSigOutput(sig, &i, x)) {
        Tree v = self(x);
        fSplittedSignals.insert(sigOutput(i, v));
        return sigOutput(i, v);

    } else if (isSigFixDelay(sig, x, y)) {
        int      dmax = fOccMarkup->retrieve(x)->getMaxDelay();
        interval i    = getCertifiedSigType(y)->getInterval();
        Tree     v    = self(x);
        Tree     w    = self(y);
        // we use x (the delayed signal) has unique identifier for the delay-line
        if (dmax == 0) {
            cerr << "STRANGE CASE DMAX=0 FOR " << ppsig(sig) << endl;
        }
        Tree id = uniqueID("D", x);
        fSplittedSignals.insert(sigDelayLineWrite(id, x, dmax, v));
        Tree inst = sigDelayLineRead(id, x, int(i.lo), w);
        return inst;

    } else if (occ->hasMultiOccurences() && (t->variability() < kSamp)) {
        Tree r  = SignalIdentity::transformation(sig);
        Tree id = uniqueID("C", sig);
        fSplittedSignals.insert(sigControlWrite(id, sig, r));
        Tree inst = sigControlRead(id, sig);
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

/**
 *
 */
Tree uniqueID(const char* prefix, Tree sig)
{
    Tree ID;
    Tree key = tree(symbol(prefix));
    if (getProperty(sig, key, ID)) {
        return ID;
    } else {
        ID = tree(unique(prefix));
        setProperty(sig, key, ID);
        return ID;
    }
}