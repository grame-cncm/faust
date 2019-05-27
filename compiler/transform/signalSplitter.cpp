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

/********************************************************************
SignalSplitter::transformation(Tree sig) :

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
    } else if (isSigFixDelay(sig, x, y)) {
        int      dmax = fOccMarkup->retrieve(x)->getMaxDelay();
        interval i    = getCertifiedSigType(y)->getInterval();
        Tree     v    = self(x);
        Tree     w    = self(y);

        fSplittedSignals.insert(sigDelayLineWrite(v, dmax, v));
        return sigDelayLineRead(v, int(i.lo), w);
    } else if (occ->hasMultiOccurences() && (t->variability() < kSamp)) {
        Tree r = SignalIdentity::transformation(sig);
        fSplittedSignals.insert(sigControlWrite(sig, r));
        return sigControlRead(sig);
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
