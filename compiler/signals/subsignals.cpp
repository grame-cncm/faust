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

#include <property.hh>
#include <signals.hh>
#include <sstream>

#include "exception.hh"
#include "global.hh"

using namespace std;

/**
 * Extract the sub signals of a signal expression, that is not
 * necessarily all the subtrees.
 * @param sig the signals
 * @param vsigs a reference to the vector where the subsignals will be placed
 * @return the number of subsignals
 */
int getSubSignals(Tree sig, tvec& vsigs, bool visitgen)
{
    vsigs.clear();

    int     i;
    int64_t i64;
    double  r;
    Tree size, gen, wi, ws, tbl, ri, c, sel, x, y, z, u, v, var, le, label, ff, largs, type, name,
        file, sf;

    if (getUserData(sig)) {
        for (int i1 = 0; i1 < sig->arity(); i1++) {
            vsigs.push_back(sig->branch(i1));
        }
        return sig->arity();
    } else if (isSigInt(sig, &i)) {
        return 0;
    } else if (isSigInt64(sig, &i64)) {
        return 0;
    } else if (isSigReal(sig, &r)) {
        return 0;
    } else if (isSigWaveform(sig)) {
        vsigs = sig->branches();
        return int(vsigs.size());
    }

    else if (isSigInput(sig, &i)) {
        return 0;
    } else if (isSigOutput(sig, &i, x)) {
        vsigs.push_back(x);
        return 1;
    }

    else if (isSigDelay1(sig, x)) {
        vsigs.push_back(x);
        return 1;
    }

    else if (isSigDelay(sig, x, y)) {
        vsigs.push_back(x);
        vsigs.push_back(y);
        return 2;
    } else if (isSigPrefix(sig, x, y)) {
        vsigs.push_back(x);
        vsigs.push_back(y);
        return 2;
    } else if (isSigBinOp(sig, &i, x, y)) {
        vsigs.push_back(x);
        vsigs.push_back(y);
        return 2;
    } else if (isSigFFun(sig, ff, largs)) {
        int n = 0;
        while (!isNil(largs)) {
            vsigs.push_back(hd(largs));
            largs = tl(largs);
            n++;
        }
        return n;
    } else if (isSigFConst(sig, type, name, file)) {
        return 0;
    } else if (isSigFVar(sig, type, name, file)) {
        return 0;
    }

    else if (isSigWRTbl(sig, size, gen, wi, ws)) {
        vsigs.push_back(size);
        vsigs.push_back(gen);
        if (wi == gGlobal->nil) {
            // rdtable
            return 2;
        } else {
            // rwtable
            vsigs.push_back(wi);
            vsigs.push_back(ws);
            return 4;
        }
    } else if (isSigRDTbl(sig, tbl, ri)) {
        vsigs.push_back(tbl);
        vsigs.push_back(ri);
        return 2;
    }

    else if (isSigDocConstantTbl(sig, x, y)) {
        vsigs.push_back(x);
        vsigs.push_back(y);
        return 2;
    } else if (isSigDocWriteTbl(sig, x, y, u, v)) {
        vsigs.push_back(x);
        vsigs.push_back(y);
        vsigs.push_back(u);
        vsigs.push_back(v);
        return 4;
    } else if (isSigDocAccessTbl(sig, x, y)) {
        vsigs.push_back(x);
        vsigs.push_back(y);
        return 2;
    }

    else if (isSigSelect2(sig, sel, x, y)) {
        vsigs.push_back(sel);
        vsigs.push_back(x);
        vsigs.push_back(y);
        return 3;
    }

    else if (isSigGen(sig, x)) {
        if (visitgen) {
            vsigs.push_back(x);
            return 1;
        } else {
            return 0;
        }
    }

    else if (isProj(sig, &i, x)) {
        vsigs.push_back(x);
        return 1;
    } else if (isRec(sig, var, le)) {
        vsigs.push_back(le);
        return 1;
    }

    else if (isSigIntCast(sig, x)) {
        vsigs.push_back(x);
        return 1;
    } else if (isSigBitCast(sig, x)) {
        vsigs.push_back(x);
        return 1;
    } else if (isSigFloatCast(sig, x)) {
        vsigs.push_back(x);
        return 1;
    }

    else if (isSigButton(sig, label)) {
        return 0;
    } else if (isSigCheckbox(sig, label)) {
        return 0;
    } else if (isSigVSlider(sig, label, c, x, y, z)) {
        vsigs.push_back(c);
        vsigs.push_back(x);
        vsigs.push_back(y);
        vsigs.push_back(z);
        return 4;
    } else if (isSigHSlider(sig, label, c, x, y, z)) {
        vsigs.push_back(c);
        vsigs.push_back(x);
        vsigs.push_back(y);
        vsigs.push_back(z);
        return 4;
    } else if (isSigNumEntry(sig, label, c, x, y, z)) {
        vsigs.push_back(c);
        vsigs.push_back(x);
        vsigs.push_back(y);
        vsigs.push_back(z);
        return 4;
    }

    else if (isSigVBargraph(sig, label, x, y, z)) {
        vsigs.push_back(x);
        vsigs.push_back(y);
        vsigs.push_back(z);
        return 3;
    } else if (isSigHBargraph(sig, label, x, y, z)) {
        vsigs.push_back(x);
        vsigs.push_back(y);
        vsigs.push_back(z);
        return 3;
    }

    else if (isSigSoundfile(sig, label)) {
        return 0;
    } else if (isSigSoundfileLength(sig, sf, x)) {
        vsigs.push_back(sf);
        vsigs.push_back(x);
        return 2;
    } else if (isSigSoundfileRate(sig, sf, x)) {
        vsigs.push_back(sf);
        vsigs.push_back(x);
        return 2;
    } else if (isSigSoundfileBuffer(sig, sf, x, y, z)) {
        vsigs.push_back(sf);
        vsigs.push_back(x);
        vsigs.push_back(y);
        vsigs.push_back(z);
        return 4;
    }

    else if (isSigFIR(sig)) {
        vsigs = sig->branches();
        return int(vsigs.size());
    } else if (isSigIIR(sig)) {
        vsigs = sig->branches();
        return int(vsigs.size());
    }

    else if (isSigSum(sig)) {
        vsigs = sig->branches();
        return int(vsigs.size());
    }

    else if (isSigTempVar(sig, x)) {
        vsigs.push_back(x);
        return 1;
    } else if (isSigPermVar(sig, x)) {
        vsigs.push_back(x);
        return 1;
    } else if (isSigZeroPad(sig, x, y)) {
        vsigs.push_back(x);
        vsigs.push_back(y);
        return 2;
    } else if (isSigSeq(sig, x, y)) {
        vsigs.push_back(x);
        vsigs.push_back(y);
        return 2;
    } else if (isSigOD(sig)) {
        // TODO: check if this is correct
        // because of nil used to separate
        // inputs and outputs
        vsigs = sig->branches();
        return int(vsigs.size());
    } else if (isSigUS(sig)) {
        // TODO: check if this is correct
        // because of nil used to separate
        // inputs and outputs
        vsigs = sig->branches();
        return int(vsigs.size());
    } else if (isSigDS(sig)) {
        // TODO: check if this is correct
        // because of nil used to separate
        // inputs and outputs
        vsigs = sig->branches();
        return int(vsigs.size());
    } else if (isSigClocked(sig, x, y)) {
        // vsigs.push_back(x); // The clock context x is not a signal
        vsigs.push_back(y);
        return 1;
    }

    else if (isSigAttach(sig, x, y)) {
        vsigs.push_back(x);
        vsigs.push_back(y);
        return 2;
    } else if (isSigEnable(sig, x, y)) {
        vsigs.push_back(x);
        vsigs.push_back(y);
        return 2;
    } else if (isSigControl(sig, x, y)) {
        vsigs.push_back(x);
        vsigs.push_back(y);
        return 2;
    } else if (isList(sig)) {
        vsigs.push_back(hd(sig));
        vsigs.push_back(tl(sig));
        return 2;
    } else if (isNil(sig)) {
        return 0;

    } else if (isSigAssertBounds(sig, x, y, z)) {
        vsigs.push_back(x);
        vsigs.push_back(y);
        vsigs.push_back(z);
        return 3;
    } else if (isSigHighest(sig, x) || isSigLowest(sig, x)) {
        vsigs.push_back(x);
        return 1;
    }

    else if (isSigRegister(sig, &i, x)) {
        vsigs.push_back(x);
        return 1;
    }

    else {
        cerr << "ASSERT : getSubSignals unrecognized signal : " << *sig << endl;
        faustassert(false);
    }
    return 0;
}

/**
 * Reconstruct a signal with new sub signals. This is the inverse operation of getSubSignals.
 * @param sig the original signal
 * @param vsigs the vector of new subsignals
 * @param visitgen true if we want to visit generator signals
 * @return the reconstructed signal
 */
Tree setSubSignals(Tree sig, const tvec& vsigs, bool visitgen)
{
    int     i;
    int64_t i64;
    double  r;
    Tree size, gen, wi, ws, tbl, ri, c, sel, x, y, z, u, v, var, le, label, ff, largs, type, name,
        file, sf;

    if (getUserData(sig)) {
        vector<Tree> newBranches;
        for (size_t i1 = 0; i1 < vsigs.size(); i1++) {
            newBranches.push_back(vsigs[i1]);
        }
        return tree(sig->node(), newBranches);
    } else if (isSigInt(sig, &i)) {
        return sig; // No subsignals
    } else if (isSigInt64(sig, &i64)) {
        return sig; // No subsignals
    } else if (isSigReal(sig, &r)) {
        return sig; // No subsignals
    } else if (isSigWaveform(sig)) {
        return tree(sig->node(), vsigs);
    }

    else if (isSigInput(sig, &i)) {
        return sig; // No subsignals
    } else if (isSigOutput(sig, &i, x)) {
        faustassert(vsigs.size() == 1);
        return sigOutput(i, vsigs[0]);
    }

    else if (isSigDelay1(sig, x)) {
        faustassert(vsigs.size() == 1);
        return sigDelay1(vsigs[0]);
    }

    else if (isSigDelay(sig, x, y)) {
        faustassert(vsigs.size() == 2);
        return sigDelay(vsigs[0], vsigs[1]);
    } else if (isSigPrefix(sig, x, y)) {
        faustassert(vsigs.size() == 2);
        return sigPrefix(vsigs[0], vsigs[1]);
    } else if (isSigBinOp(sig, &i, x, y)) {
        faustassert(vsigs.size() == 2);
        return sigBinOp(i, vsigs[0], vsigs[1]);
    } else if (isSigFFun(sig, ff, largs)) {
        Tree newArgs = gGlobal->nil;
        for (int idx = int(vsigs.size()) - 1; idx >= 0; idx--) {
            newArgs = cons(vsigs[idx], newArgs);
        }
        return sigFFun(ff, newArgs);
    } else if (isSigFConst(sig, type, name, file)) {
        return sig; // No subsignals
    } else if (isSigFVar(sig, type, name, file)) {
        return sig; // No subsignals
    }

    else if (isSigWRTbl(sig, size, gen, wi, ws)) {
        if (wi == gGlobal->nil) {
            // rdtable
            faustassert(vsigs.size() == 2);
            return sigWRTbl(vsigs[0], vsigs[1]);
        } else {
            // rwtable
            faustassert(vsigs.size() == 4);
            return sigWRTbl(vsigs[0], vsigs[1], vsigs[2], vsigs[3]);
        }
    } else if (isSigRDTbl(sig, tbl, ri)) {
        faustassert(vsigs.size() == 2);
        return sigRDTbl(vsigs[0], vsigs[1]);
    }

    else if (isSigDocConstantTbl(sig, x, y)) {
        faustassert(vsigs.size() == 2);
        return sigDocConstantTbl(vsigs[0], vsigs[1]);
    } else if (isSigDocWriteTbl(sig, x, y, u, v)) {
        faustassert(vsigs.size() == 4);
        return sigDocWriteTbl(vsigs[0], vsigs[1], vsigs[2], vsigs[3]);
    } else if (isSigDocAccessTbl(sig, x, y)) {
        faustassert(vsigs.size() == 2);
        return sigDocAccessTbl(vsigs[0], vsigs[1]);
    }

    else if (isSigSelect2(sig, sel, x, y)) {
        faustassert(vsigs.size() == 3);
        return sigSelect2(vsigs[0], vsigs[1], vsigs[2]);
    }

    else if (isSigGen(sig, x)) {
        if (visitgen) {
            faustassert(vsigs.size() == 1);
            return sigGen(vsigs[0]);
        } else {
            return sig; // No subsignals visited
        }
    }

    else if (isProj(sig, &i, x)) {
        faustassert(vsigs.size() == 1);
        return sigProj(i, vsigs[0]);
    } else if (isRec(sig, var, le)) {
        faustassert(vsigs.size() == 1);
        return rec(var, vsigs[0]);
    }

    else if (isSigIntCast(sig, x)) {
        faustassert(vsigs.size() == 1);
        return sigIntCast(vsigs[0]);
    } else if (isSigBitCast(sig, x)) {
        faustassert(vsigs.size() == 1);
        return sigBitCast(vsigs[0]);
    } else if (isSigFloatCast(sig, x)) {
        faustassert(vsigs.size() == 1);
        return sigFloatCast(vsigs[0]);
    }

    else if (isSigButton(sig, label)) {
        return sig; // No subsignals
    } else if (isSigCheckbox(sig, label)) {
        return sig; // No subsignals
    } else if (isSigVSlider(sig, label, c, x, y, z)) {
        faustassert(vsigs.size() == 4);
        return sigVSlider(label, vsigs[0], vsigs[1], vsigs[2], vsigs[3]);
    } else if (isSigHSlider(sig, label, c, x, y, z)) {
        faustassert(vsigs.size() == 4);
        return sigHSlider(label, vsigs[0], vsigs[1], vsigs[2], vsigs[3]);
    } else if (isSigNumEntry(sig, label, c, x, y, z)) {
        faustassert(vsigs.size() == 4);
        return sigNumEntry(label, vsigs[0], vsigs[1], vsigs[2], vsigs[3]);
    }

    else if (isSigVBargraph(sig, label, x, y, z)) {
        faustassert(vsigs.size() == 3);
        return sigVBargraph(label, vsigs[0], vsigs[1], vsigs[2]);
    } else if (isSigHBargraph(sig, label, x, y, z)) {
        faustassert(vsigs.size() == 3);
        return sigHBargraph(label, vsigs[0], vsigs[1], vsigs[2]);
    }

    else if (isSigSoundfile(sig, label)) {
        return sig; // No subsignals
    } else if (isSigSoundfileLength(sig, sf, x)) {
        faustassert(vsigs.size() == 2);
        return sigSoundfileLength(vsigs[0], vsigs[1]);
    } else if (isSigSoundfileRate(sig, sf, x)) {
        faustassert(vsigs.size() == 2);
        return sigSoundfileRate(vsigs[0], vsigs[1]);
    } else if (isSigSoundfileBuffer(sig, sf, x, y, z)) {
        faustassert(vsigs.size() == 4);
        return sigSoundfileBuffer(vsigs[0], vsigs[1], vsigs[2], vsigs[3]);
    }

    else if (isSigAssertBounds(sig, x, y, z)) {
        faustassert(vsigs.size() == 3);
        return sigAssertBounds(vsigs[0], vsigs[1], vsigs[2]);
    } else if (isSigHighest(sig, x)) {
        faustassert(vsigs.size() == 1);
        return sigHighest(vsigs[0]);
    } else if (isSigLowest(sig, x)) {
        faustassert(vsigs.size() == 1);
        return sigLowest(vsigs[0]);
    }

    else if (isSigFIR(sig)) {
        return tree(sig->node(), vsigs);
    } else if (isSigIIR(sig)) {
        return tree(sig->node(), vsigs);
    } else if (isSigSum(sig)) {
        return tree(sig->node(), vsigs);
    } else if (isSigTempVar(sig, x)) {
        faustassert(vsigs.size() == 1);
        return sigTempVar(vsigs[0]);
    } else if (isSigPermVar(sig, x)) {
        faustassert(vsigs.size() == 1);
        return sigPermVar(vsigs[0]);
    } else if (isSigZeroPad(sig, x, y)) {
        faustassert(vsigs.size() == 2);
        return sigZeroPad(vsigs[0], vsigs[1]);
    } else if (isSigSeq(sig, x, y)) {
        faustassert(vsigs.size() == 2);
        return sigSeq(vsigs[0], vsigs[1]);
    } else if (isSigOD(sig)) {
        return tree(sig->node(), vsigs);
    } else if (isSigUS(sig)) {
        return tree(sig->node(), vsigs);
    } else if (isSigDS(sig)) {
        return tree(sig->node(), vsigs);
    } else if (isSigClocked(sig, x, y)) {
        faustassert(vsigs.size() == 1);
        return sigClocked(x, vsigs[0]); // x is the clock context, vsigs[0] is the signal
    } else if (isSigAttach(sig, x, y)) {
        faustassert(vsigs.size() == 2);
        return sigAttach(vsigs[0], vsigs[1]);
    } else if (isSigEnable(sig, x, y)) {
        faustassert(vsigs.size() == 2);
        return sigEnable(vsigs[0], vsigs[1]);
    } else if (isSigControl(sig, x, y)) {
        faustassert(vsigs.size() == 2);
        return sigControl(vsigs[0], vsigs[1]);
    } else if (isList(sig)) {
        faustassert(vsigs.size() == 2);
        return cons(vsigs[0], vsigs[1]);
    } else if (isNil(sig)) {
        return sig; // No subsignals

    } else if (isSigRegister(sig, &i, x)) {
        faustassert(vsigs.size() == 1);
        return sigRegister(i, vsigs[0]);
    }

    else {
        cerr << "ASSERT : setSubSignals unrecognized signal : " << *sig << endl;
        faustassert(false);
    }
    return sig; // Fallback
}
