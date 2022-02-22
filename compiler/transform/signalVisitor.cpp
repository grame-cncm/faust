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

#include "signalVisitor.hh"

#include <cstdlib>
#include <map>
#include "Text.hh"
#include "global.hh"
#include "ppsig.hh"
#include "property.hh"
#include "signalVisitor.hh"
#include "signals.hh"
#include "sigtyperules.hh"
#include "tlib.hh"
#include "tree.hh"

//-------------------------SignalVisitor-------------------------------
// An identity transformation on signals. Can be used to test
// that everything works, and as a pattern for real transformations.
//----------------------------------------------------------------------

void SignalVisitor::visit(Tree sig)
{
    int    i;
    double r;
    Tree   c, sel, x, y, z, u, v, var, le, label, id, ff, largs, type, name, file, sf;

    if (getUserData(sig)) {
        for (Tree b : sig->branches()) {
            self(b);
        }
        return;
    } else if (isSigInt(sig, &i)) {
        return;
    } else if (isSigReal(sig, &r)) {
        return;
    } else if (isSigWaveform(sig)) {
        return;
    } else if (isSigInput(sig, &i)) {
        return;
    } else if (isSigOutput(sig, &i, x)) {
        self(x);
        return;
    } else if (isSigDelay1(sig, x)) {
        self(x);
        return;
    } else if (isSigDelay(sig, x, y)) {
        self(x);
        self(y);
        return;
    } else if (isSigPrefix(sig, x, y)) {
        self(x);
        self(y);
        return;
    } else if (isSigBinOp(sig, &i, x, y)) {
        self(x);
        self(y);
        return;
    }

    // Foreign functions
    else if (isSigFFun(sig, ff, largs)) {
        mapself(largs);
        return;
    } else if (isSigFConst(sig, type, name, file)) {
        return;
    } else if (isSigFVar(sig, type, name, file)) {
        return;
    }

    // Tables
    else if (isSigTable(sig, id, x, y)) {
        self(x);
        self(y);
        return;
    } else if (isSigWRTbl(sig, id, x, y, z)) {
        self(x);
        self(y);
        self(z);
        return;
    } else if (isSigRDTbl(sig, x, y)) {
        self(x);
        self(y);
        return;
    }

    // Doc
    else if (isSigDocConstantTbl(sig, x, y)) {
        self(x);
        self(y);
        return;
    } else if (isSigDocWriteTbl(sig, x, y, u, v)) {
        self(x);
        self(y);
        self(u);
        self(v);
        return;
    } else if (isSigDocAccessTbl(sig, x, y)) {
        self(x);
        self(y);
        return;
    }

    // Select2 (and Select3 expressed with Select2)
    else if (isSigSelect2(sig, sel, x, y)) {
        self(sel);
        self(x);
        self(y);
        return;
    }

    // Table sigGen
    else if (isSigGen(sig, x)) {
        if (fVisitGen) {
            self(x);
            return;
        } else {
            return;
        }
    }

    // recursive signals
    else if (isProj(sig, &i, x)) {
        self(x);
        return;
    } else if (isRec(sig, var, le)) {
        mapself(le);
        return;
    }

    // Int and Float Cast
    else if (isSigIntCast(sig, x)) {
        self(x);
        return;
    } else if (isSigFloatCast(sig, x)) {
        self(x);
        return;
    }

    // UI
    else if (isSigButton(sig, label)) {
        return;
    } else if (isSigCheckbox(sig, label)) {
        return;
    } else if (isSigVSlider(sig, label, c, x, y, z)) {
        self(c), self(x), self(y), self(z);
        return;
    } else if (isSigHSlider(sig, label, c, x, y, z)) {
        self(c), self(x), self(y), self(z);
        return;
    } else if (isSigNumEntry(sig, label, c, x, y, z)) {
        self(c), self(x), self(y), self(z);
        return;
    } else if (isSigVBargraph(sig, label, x, y, z)) {
        self(x), self(y), self(z);
        return;
    } else if (isSigHBargraph(sig, label, x, y, z)) {
        self(x), self(y), self(z);
        return;
    }

    // Soundfile length, rate, buffer
    else if (isSigSoundfile(sig, label)) {
        return;
    } else if (isSigSoundfileLength(sig, sf, x)) {
        self(sf), self(x);
        return;
    } else if (isSigSoundfileRate(sig, sf, x)) {
        self(sf), self(x);
        return;
    } else if (isSigSoundfileBuffer(sig, sf, x, y, z)) {
        self(sf), self(x), self(y), self(z);
        return;
    }

    // Attach, Enable, Control
    else if (isSigAttach(sig, x, y)) {
        self(x), self(y);
        return;
    } else if (isSigEnable(sig, x, y)) {
        self(x), self(y);
        return;
    } else if (isSigControl(sig, x, y)) {
        self(x), self(y);
        return;
    }

    else if (isNil(sig)) {
        // now nil can appear in table write instructions
        return;
    } else {
        stringstream error;
        error << __FILE__ << ":" << __LINE__ << " ERROR : unrecognized signal : " << *sig << endl;
        throw faustexception(error.str());
    }
}
