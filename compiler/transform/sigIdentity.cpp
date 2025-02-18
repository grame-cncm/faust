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

#include "Text.hh"
#include "global.hh"
#include "ppsig.hh"
#include "signals.hh"

using namespace std;

//-------------------------SignalIdentityImp-------------------------------
// An identity transformation on signals. Can be used to test
// that everything works, and as a pattern for real transformations.
//----------------------------------------------------------------------

template <bool CACHE>
void SignalIdentityImp<CACHE>::traceEnter(Tree t)
{
    tab(this->fIndent, cerr);
    cerr << this->fMessage << ": " << ppsig(t, MAX_ERROR_SIZE) << endl;
}

template <bool CACHE>
void SignalIdentityImp<CACHE>::traceExit(Tree t, Tree r)
{
    tab(this->fIndent, cerr);
    cerr << this->fMessage << ": " << ppsig(t, MAX_ERROR_SIZE) << " => " << ppsig(r, MAX_ERROR_SIZE)
         << endl;
}

template <bool CACHE>
void SignalIdentityImp<CACHE>::myTraceEnter(Tree t)
{
    if (this->fTrace) {
        tab(this->fIndent, cerr);
        cerr << this->fMessage << " ENTER: " << ppsig(t, MAX_ERROR_SIZE) << endl;
        this->fIndent++;
    }
}

template <bool CACHE>
void SignalIdentityImp<CACHE>::myTraceContinue(Tree t, Tree w)
{
    if (this->fTrace) {
        tab(this->fIndent - 1, cerr);
        cerr << this->fMessage << " CONT : " << ppsig(t, MAX_ERROR_SIZE) << " --> "
             << ppsig(w, MAX_ERROR_SIZE) << endl;
    }
}

template <bool CACHE>
void SignalIdentityImp<CACHE>::myTraceExit(Tree t, Tree w, Tree r)
{
    if (this->fTrace) {
        this->fIndent--;
        tab(this->fIndent, cerr);
        cerr << this->fMessage << " EXIT : " << ppsig(t, MAX_ERROR_SIZE) << " --> "
             << ppsig(w, MAX_ERROR_SIZE) << " ==> " << ppsig(r, MAX_ERROR_SIZE) << endl;
    }
}

template <bool CACHE>
Tree SignalIdentityImp<CACHE>::transformation(Tree sig)
{
    int     i;
    int64_t i64;
    double  r;
    Tree    c, sel, w, x, y, z, u, v, var, le, label, ff, largs, type, name, file, sf;

    if (getUserData(sig)) {
        vector<Tree> newBranches;
        for (Tree b : sig->branches()) {
            newBranches.push_back(this->self(b));
        }
        return tree(sig->node(), newBranches);
    } else if (isSigInt(sig, &i)) {
        return sig;
    } else if (isSigInt64(sig, &i64)) {
        return sig;
    } else if (isSigReal(sig, &r)) {
        return sig;
    } else if (isSigWaveform(sig)) {
        return sig;
    } else if (isSigInput(sig, &i)) {
        return sig;
    } else if (isSigOutput(sig, &i, x)) {
        return sigOutput(i, this->self(x));
    } else if (isSigDelay1(sig, x)) {
        return sigDelay1(this->self(x));
    } else if (isSigDelay(sig, x, y)) {
        return sigDelay(this->self(x), this->self(y));
    } else if (isSigPrefix(sig, x, y)) {
        return sigPrefix(this->self(x), this->self(y));
    } else if (isSigBinOp(sig, &i, x, y)) {
        return sigBinOp(i, this->self(x), this->self(y));
    }

    // Foreign functions
    else if (isSigFFun(sig, ff, largs)) {
        return sigFFun(ff, this->mapself(largs));
    } else if (isSigFConst(sig, type, name, file)) {
        return sig;
    } else if (isSigFVar(sig, type, name, file)) {
        return sig;
    }

    // Tables
    else if (isSigWRTbl(sig, w, x, y, z)) {
        if (y == gGlobal->nil) {
            // rdtable
            return sigWRTbl(this->self(w), this->self(x));
        } else {
            // rwtable
            return sigWRTbl(this->self(w), this->self(x), this->self(y), this->self(z));
        }
    } else if (isSigRDTbl(sig, x, y)) {
        return sigRDTbl(this->self(x), this->self(y));
    }

    // Doc
    else if (isSigDocConstantTbl(sig, x, y)) {
        return sigDocConstantTbl(this->self(x), this->self(y));
    } else if (isSigDocWriteTbl(sig, x, y, u, v)) {
        return sigDocWriteTbl(this->self(x), this->self(y), this->self(u), this->self(v));
    } else if (isSigDocAccessTbl(sig, x, y)) {
        return sigDocAccessTbl(this->self(x), this->self(y));
    }

    // Select2 and Select3
    else if (isSigSelect2(sig, sel, x, y)) {
        return sigSelect2(this->self(sel), this->self(x), this->self(y));
    }

    // Table sigGen
    else if (isSigGen(sig, x)) {
        if (fVisitGen) {
            return sigGen(this->self(x));
        } else {
            return sig;
        }
    }

    // FIR and IIR
    else if (isSigFIR(sig)) {
        tvec c = sig->branches();
        for (unsigned int i = 0; i < c.size(); i++) {
            c[i] = this->self(c[i]);
        }
        return sigFIR(c);
    } else if (isSigIIR(sig)) {
        tvec c = sig->branches();
        for (unsigned int i = 1; i < c.size(); i++) {
            c[i] = this->self(c[i]);
        }
        return sigIIR(c);
    }

    else if (isSigSum(sig)) {
        tvec c = sig->branches();
        for (unsigned int i = 0; i < c.size(); i++) {
            c[i] = this->self(c[i]);
        }
        return sigSum(c);
    }

    else if (isSigTempVar(sig, x)) {
        return sigTempVar(this->self(x));
    }

    else if (isSigPermVar(sig, x)) {
        return sigPermVar(this->self(x));
    }

    else if (isSigZeroPad(sig, x, y)) {
        return sigZeroPad(this->self(x), this->self(y));
    }

    else if (isSigDecimate(sig, x, y)) {
        return sigDecimate(this->self(x), this->self(y));
    }

    else if (isSigSeq(sig, x, y)) {
        // std::cerr << "identity sigSeq " << ppsig(sig) << std::endl;
        Tree x2 = this->self(x);
        // std::cerr << "identity sigSeq x2 " << ppsig(x2) << std::endl;
        faustassert(!isZero(x2));
        return sigSeq(x2, this->self(y));
    }

    else if (tvec w1; isSigOD(sig, w1)) {
        tvec w2;
        for (Tree s : w1) {
            if (s == gGlobal->nil) {
                w2.push_back(gGlobal->nil);
            } else {
                w2.push_back(this->self(s));
            }
        }
        return sigOD(w2);
    }

    else if (tvec w1; isSigUS(sig, w1)) {
        tvec w2;
        for (Tree s : w1) {
            if (s == gGlobal->nil) {
                w2.push_back(gGlobal->nil);
            } else {
                w2.push_back(this->self(s));
            }
        }
        return sigUS(w2);
    }

    else if (tvec w1; isSigDS(sig, w1)) {
        tvec w2;
        for (Tree s : w1) {
            if (s == gGlobal->nil) {
                w2.push_back(gGlobal->nil);
            } else {
                w2.push_back(this->self(s));
            }
        }
        return sigDS(w2);
    }

    else if (isSigClocked(sig, x, y)) {
        return sigClocked(x, this->self(y));  // do we need to transform the clock signal ?
    }

    else if (isSigGen(sig, x)) {
        if (fVisitGen) {
            return sigGen(this->self(x));
        } else {
            return sig;
        }
    }

    // recursive signals
    else if (isProj(sig, &i, x)) {
        return sigProj(i, this->self(x));
    } else if (isRec(sig, var, le)) {
        if (isNil(le)) {
            // we are already visiting this recursive group
            return sig;
        } else {
            // first visit
            rec(var, gGlobal->nil);  // to avoid infinite recursions
            return rec(var, this->mapselfRec(le));
        }
    }

    // Int and Float Cast
    else if (isSigIntCast(sig, x)) {
        return sigIntCast(this->self(x));
    } else if (isSigBitCast(sig, x)) {
        return sigBitCast(this->self(x));
    } else if (isSigFloatCast(sig, x)) {
        return sigFloatCast(this->self(x));
    }

    // UI
    else if (isSigButton(sig, label)) {
        return sig;
    } else if (isSigCheckbox(sig, label)) {
        return sig;
    } else if (isSigVSlider(sig, label, c, x, y, z)) {
        return sigVSlider(label, this->self(c), this->self(x), this->self(y), this->self(z));
    } else if (isSigHSlider(sig, label, c, x, y, z)) {
        return sigHSlider(label, this->self(c), this->self(x), this->self(y), this->self(z));
    } else if (isSigNumEntry(sig, label, c, x, y, z)) {
        return sigNumEntry(label, this->self(c), this->self(x), this->self(y), this->self(z));
    } else if (isSigVBargraph(sig, label, x, y, z)) {
        return sigVBargraph(label, this->self(x), this->self(y), this->self(z));
    } else if (isSigHBargraph(sig, label, x, y, z)) {
        return sigHBargraph(label, this->self(x), this->self(y), this->self(z));
    }

    // Soundfile length, rate, buffer
    else if (isSigSoundfile(sig, label)) {
        return sig;
    } else if (isSigSoundfileLength(sig, sf, x)) {
        return sigSoundfileLength(this->self(sf), this->self(x));
    } else if (isSigSoundfileRate(sig, sf, x)) {
        return sigSoundfileRate(this->self(sf), this->self(x));
    } else if (isSigSoundfileBuffer(sig, sf, x, y, z)) {
        return sigSoundfileBuffer(this->self(sf), this->self(x), this->self(y), this->self(z));
    }

    // Attach, Enable, Control
    else if (isSigAttach(sig, x, y)) {
        return sigAttach(this->self(x), this->self(y));
    } else if (isSigEnable(sig, x, y)) {
        return sigEnable(this->self(x), this->self(y));
    } else if (isSigControl(sig, x, y)) {
        return sigControl(this->self(x), this->self(y));
    }

    // Signal interval annotation
    else if (isSigAssertBounds(sig, x, y, z)) {
        return sigAssertBounds(this->self(x), this->self(y), this->self(z));
    } else if (isSigLowest(sig, x)) {
        return sigLowest(this->self(x));
    } else if (isSigHighest(sig, x)) {
        return sigHighest(this->self(x));
    }

    else if (isSigRegister(sig, &i, x)) {
        return sigRegister(i, this->self(x));
    }

    else {
        cerr << "ASSERT : unrecognized signal : " << *sig << endl;
        faustassert(false);
    }
    return nullptr;
}

    // Explicit instanciation for CACHE = true and false
template class SignalIdentityImp<true>;
template class SignalIdentityImp<false>;
