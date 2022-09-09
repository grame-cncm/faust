/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include "sigIdentity.hh"

#include <stdlib.h>
#include <cstdlib>

#include "signals.hh"
#include "global.hh"
#include "ppsig.hh"
#include "Text.hh"

//-------------------------SignalIdentity-------------------------------
// An identity transformation on signals. Can be used to test
// that everything works, and as a pattern for real transformations.
//----------------------------------------------------------------------

void SignalIdentity::traceEnter(Tree t)
{
    tab(fIndent, cerr);
    cerr << fMessage << ": " << ppsig(t) << endl;
}

void SignalIdentity::traceExit(Tree t, Tree r)
{
    tab(fIndent, cerr);
    cerr << fMessage << ": " << ppsig(t) << " => " << ppsig(r) << endl;
}

Tree SignalIdentity::transformation(Tree sig)
{
    int    i;
    double r;
    Tree   c, sel, x, y, z, u, v, var, le, label, id, ff, largs, type, name, file, sf;

    if (getUserData(sig)) {
        vector<Tree> newBranches;
        for (Tree b : sig->branches()) {
            newBranches.push_back(self(b));
        }
        return tree(sig->node(), newBranches);
    } else if (isSigInt(sig, &i)) {
        return sig;
    } else if (isSigReal(sig, &r)) {
        return sig;
    } else if (isSigWaveform(sig)) {
        return sig;
    } else if (isSigInput(sig, &i)) {
        return sig;
    } else if (isSigOutput(sig, &i, x)) {
        return sigOutput(i, self(x));
    } else if (isSigDelay1(sig, x)) {
        return sigDelay1(self(x));
    } else if (isSigDelay(sig, x, y)) {
        return sigDelay(self(x), self(y));
    } else if (isSigPrefix(sig, x, y)) {
        return sigPrefix(self(x), self(y));
    } else if (isSigBinOp(sig, &i, x, y)) {
        return sigBinOp(i, self(x), self(y));
    }

    // Foreign functions
    else if (isSigFFun(sig, ff, largs)) {
        return sigFFun(ff, mapself(largs));
    } else if (isSigFConst(sig, type, name, file)) {
        return sig;
    } else if (isSigFVar(sig, type, name, file)) {
        return sig;
    }

    // Tables
    else if (isSigTable(sig, id, x, y)) {
        return sigTable(id, self(x), self(y));
    } else if (isSigWRTbl(sig, id, x, y, z)) {
        return sigWRTbl(id, self(x), self(y), self(z));
    } else if (isSigRDTbl(sig, x, y)) {
        return sigRDTbl(self(x), self(y));
    }

    // Doc
    else if (isSigDocConstantTbl(sig, x, y)) {
        return sigDocConstantTbl(self(x), self(y));
    } else if (isSigDocWriteTbl(sig, x, y, u, v)) {
        return sigDocWriteTbl(self(x), self(y), self(u), self(v));
    } else if (isSigDocAccessTbl(sig, x, y)) {
        return sigDocAccessTbl(self(x), self(y));
    }

    // Select2 and Select3
    else if (isSigSelect2(sig, sel, x, y)) {
        return sigSelect2(self(sel), self(x), self(y));
    }
    
    // Table sigGen
    else if (isSigGen(sig, x)) {
        if (fVisitGen) {
            return sigGen(self(x));
        } else {
            return sig;
        }
    }

    // recursive signals
    else if (isProj(sig, &i, x)) {
        return sigProj(i, self(x));
    } else if (isRec(sig, var, le)) {
        if (isNil(le)) {
            // we are already visiting this recursive group
            return sig;
        } else {
            // first visit
            rec(var, gGlobal->nil);  // to avoid infinite recursions
            return rec(var, mapself(le));
        }
    }

    // Int and Float Cast
    else if (isSigIntCast(sig, x)) {
        return sigIntCast(self(x));
    } else if (isSigFloatCast(sig, x)) {
        return sigFloatCast(self(x));
    }

    // UI
    else if (isSigButton(sig, label)) {
        return sig;
    } else if (isSigCheckbox(sig, label)) {
        return sig;
    } else if (isSigVSlider(sig, label, c, x, y, z)) {
        return sigVSlider(label, self(c), self(x), self(y), self(z));
    } else if (isSigHSlider(sig, label, c, x, y, z)) {
        return sigHSlider(label, self(c), self(x), self(y), self(z));
    } else if (isSigNumEntry(sig, label, c, x, y, z)) {
        return sigNumEntry(label, self(c), self(x), self(y), self(z));
    } else if (isSigVBargraph(sig, label, x, y, z)) {
        return sigVBargraph(label, self(x), self(y), self(z));
    } else if (isSigHBargraph(sig, label, x, y, z)) {
        return sigHBargraph(label, self(x), self(y), self(z));
    }

    // Soundfile length, rate, buffer
    else if (isSigSoundfile(sig, label)) {
        return sig;
    } else if (isSigSoundfileLength(sig, sf, x)) {
        return sigSoundfileLength(self(sf), self(x));
    } else if (isSigSoundfileRate(sig, sf, x)) {
        return sigSoundfileRate(self(sf), self(x));
    } else if (isSigSoundfileBuffer(sig, sf, x, y, z)) {
        return sigSoundfileBuffer(self(sf), self(x), self(y), self(z));
    }

    // Attach, Enable, Control
    else if (isSigAttach(sig, x, y)) {
        return sigAttach(self(x), self(y));
    } else if (isSigEnable(sig, x, y)) {
        return sigEnable(self(x), self(y));
    } else if (isSigControl(sig, x, y)) {
        return sigControl(self(x), self(y));
    }

    // Signal interval annotation
    else if (isSigAssertBounds(sig, x, y, z)) {
        return sigAssertBounds(self(x), self(y), self(z));
    }

    else if (isSigLowest(sig, x)) {
        return sigLowest(self(x));
    }
    
    else if (isSigHighest(sig, x)) {
        return sigHighest(self(x));
    }
    	
    else {
       cerr << "ERROR : unrecognized signal : " << *sig << endl;
        faustassert(false);
    }
    return 0;
}
