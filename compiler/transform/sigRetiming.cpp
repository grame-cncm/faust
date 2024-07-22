
#include <stdlib.h>
#include <cstdlib>
#include <sstream>
#include <vector>

#include "floats.hh"
#include "global.hh"
#include "ppsig.hh"
#include "prim2.hh"
#include "sigPromotion.hh"
#include "signals.hh"
#include "sigtyperules.hh"
#include "xtended.hh"

class SignalRetimer final : public SignalIdentity {
    std::unordered_map<Tree, int>  fTiming;
    std::unordered_map<Tree, Tree> fRecVar;

   public:
    SignalRetimer() {}

   protected:
    Tree transformation(Tree sig);
    int  tmaxList(Tree l);
};

/**
 * @brief add registers to a list of signal to balance timing
 *
 * @param lsig a list of signals without registers
 * @param trace optional trace flag
 * @return Tree a list of signals with registers
 */
Tree sigRetiming(Tree lsig, bool trace)
{
    SignalRetimer SR;
    if (trace) {
        SR.trace(true, "Retiming");
    }
    return SR.mapself(lsig);
}

static Tree addRegisters(Tree sig, int delay)
{
    if (delay == 0) {
        return sig;
    } else {
        return sigRegister(addRegisters(sig, delay - 1));
    }
}

int SignalRetimer::tmaxList(Tree l)
{
    int tmax = 0;
    while (!isNil(l)) {
        tmax = std::max(tmax, fTiming[hd(l)]);
        l    = tl(l);
    }
    return tmax;
}

Tree SignalRetimer::transformation(Tree sig)
{
    int     i;
    int64_t i64;
    double  r;
    Tree    c, sel, w, x, y, z, u, v, var, le, label, ff, largs, type, name, file, sf;

    if (getUserData(sig)) {
        std::vector<Tree> nb1, nb2;
        int               tmax = 0;
        for (Tree b : sig->branches()) {
            Tree b2 = self(b);
            tmax    = std::max(tmax, fTiming[b2]);
            nb1.push_back(self(b));
        }
        for (Tree c : nb1) {
            nb2.push_back(addRegisters(c, tmax - fTiming[c]));
        }
        Tree res     = sigRegister(tree(sig->node(), nb2));
        fTiming[res] = tmax + 1;
        return res;

    } else if (isSigInt(sig, &i)) {
        fTiming[sig] = 0;
        return sig;
    } else if (isSigInt64(sig, &i64)) {
        fTiming[sig] = 0;
        return sig;
    } else if (isSigReal(sig, &r)) {
        fTiming[sig] = 0;
        return sig;
    } else if (isSigWaveform(sig)) {
        fTiming[sig] = 0;
        return sig;
    } else if (isSigInput(sig, &i)) {
        fTiming[sig] = 0;
        return sig;
    } else if (isSigOutput(sig, &i, x)) {
        Tree x2      = self(x);
        Tree res     = sigOutput(i, x2);
        fTiming[res] = fTiming[x2];  // no register here
        return res;
    } else if (isSigDelay1(sig, x)) {
        Tree v       = self(x);
        Tree res     = sigRegister(sigDelay1(v));
        fTiming[res] = fTiming[v] + 1;
        return res;
    } else if (isSigDelay(sig, x, y)) {
        Tree v   = self(x);
        Tree w   = self(y);
        int  tm  = std::max(fTiming[v], fTiming[w]);
        Tree res = sigRegister(
            sigDelay(addRegisters(v, tm - fTiming[v]), addRegisters(w, tm - fTiming[w])));
        fTiming[res] = tm + 1;
        return res;
    } else if (isSigPrefix(sig, x, y)) {
        Tree x2  = self(x);
        Tree y2  = self(y);
        int  tm  = std::max(fTiming[x2], fTiming[y2]);
        Tree res = sigRegister(
            sigPrefix(addRegisters(x2, tm - fTiming[x2]), addRegisters(y2, tm - fTiming[y2])));
        fTiming[res] = tm + 1;
        return res;
    } else if (isSigBinOp(sig, &i, x, y)) {
        Tree x2  = self(x);
        Tree y2  = self(y);
        int  tm  = std::max(fTiming[x2], fTiming[y2]);
        Tree res = sigRegister(
            sigBinOp(i, addRegisters(x2, tm - fTiming[x2]), addRegisters(y2, tm - fTiming[y2])));
        fTiming[res] = tm + 1;
        return res;
    }

    // Foreign functions
    else if (isSigFFun(sig, ff, largs)) {
        Tree largs2  = mapself(largs);
        int  tmax    = tmaxList(largs2);
        Tree res     = sigRegister(sigFFun(ff, mapself(largs)));
        fTiming[res] = tmax + 1;
        return res;
    } else if (isSigFConst(sig, type, name, file)) {
        fTiming[sig] = 0;
        return sig;
    } else if (isSigFVar(sig, type, name, file)) {
        fTiming[sig] = 0;
        return sig;
    }

    // Tables
    else if (isSigWRTbl(sig, w, x, y, z)) {
        if (y == gGlobal->nil) {
            // rdtable
            Tree w2      = self(w);
            Tree x2      = self(x);
            int  tmax    = std::max(fTiming[w2], fTiming[x2]);
            Tree res     = sigRegister(sigWRTbl(addRegisters(w2, tmax - fTiming[w2]),
                                                addRegisters(x2, tmax - fTiming[x2])));
            fTiming[res] = tmax + 1;
            return res;
        } else {
            // rwtable
            Tree w2 = self(w);
            Tree x2 = self(x);
            Tree y2 = self(y);
            Tree z2 = self(z);
            int  tmax =
                std::max(fTiming[w2], std::max(fTiming[x2], std::max(fTiming[y2], fTiming[z2])));
            Tree res     = sigRegister(sigWRTbl(
                addRegisters(w2, tmax - fTiming[w2]), addRegisters(x2, tmax - fTiming[x2]),
                addRegisters(y2, tmax - fTiming[y2]), addRegisters(z2, tmax - fTiming[z2])));
            fTiming[res] = tmax + 1;
            return res;
        }
    } else if (isSigRDTbl(sig, x, y)) {
        Tree x2   = self(x);
        Tree y2   = self(y);
        int  tmax = std::max(fTiming[x2], fTiming[y2]);
        Tree res  = sigRegister(
            sigRDTbl(addRegisters(x2, tmax - fTiming[x2]), addRegisters(y2, tmax - fTiming[y2])));
        fTiming[res] = tmax + 1;
        return res;
    }
#if 0
    // Doc
    else if (isSigDocConstantTbl(sig, x, y)) {
        return sigDocConstantTbl(self(x), self(y));
    } else if (isSigDocWriteTbl(sig, x, y, u, v)) {
        return sigDocWriteTbl(self(x), self(y), self(u), self(v));
    } else if (isSigDocAccessTbl(sig, x, y)) {
        return sigDocAccessTbl(self(x), self(y));
    }
#endif

    // Select2 and Select3
    else if (isSigSelect2(sig, sel, x, y)) {
        Tree sel2    = self(sel);
        Tree x2      = self(x);
        Tree y2      = self(y);
        int  tmax    = std::max(fTiming[sel2], std::max(fTiming[x2], fTiming[y2]));
        Tree res     = sigRegister(sigSelect2(addRegisters(sel2, tmax - fTiming[sel2]),
                                              addRegisters(x2, tmax - fTiming[x2]),
                                              addRegisters(y2, tmax - fTiming[y2])));
        fTiming[res] = tmax + 1;
        return res;
    }

    // Table sigGen
    else if (isSigGen(sig, x)) {
        if (fVisitGen) {
            Tree res     = sigGen(self(x));
            fTiming[res] = 0;
            return res;
        } else {
            fTiming[sig] = 0;
            return sig;
        }
    }

    // recursive signals
    else if (isProj(sig, &i, x)) {
        Tree res     = sigProj(i, self(x));
        fTiming[res] = 0;
        return res;
    } else if (isRec(sig, var, le)) {
        if (fRecVar.count(sig)) {
            // we have/are already visiting this recursive group
            Tree res = fRecVar[sig];
            return res;
        } else {
            // first visit
            Tree var2    = tree(Node(unique("RT")));  // New name for the transformed rec group
            fRecVar[sig] = rec(var2, gGlobal->nil);   // temporary result to avoid infinite loops
            Tree le2     = mapself(le);
            Tree res     = rec(var2, le2);
            fRecVar[sig] = res;  // not needed, but for clarity
            return res;
        }
    }

    // Int and Float Cast
    else if (isSigIntCast(sig, x)) {
        Tree x2      = self(x);
        Tree res     = sigRegister(sigIntCast(x2));
        fTiming[res] = fTiming[x2] + 1;
        return res;
    } else if (isSigBitCast(sig, x)) {
        Tree x2      = self(x);
        Tree res     = sigRegister(sigBitCast(x2));
        fTiming[res] = fTiming[x2] + 1;
        return res;
    } else if (isSigFloatCast(sig, x)) {
        Tree x2      = self(x);
        Tree res     = sigRegister(sigFloatCast(x2));
        fTiming[res] = fTiming[x2] + 1;
        return res;
    }

    // UI
    else if (isSigButton(sig, label)) {
        fTiming[sig] = 0;
        return sig;
    } else if (isSigCheckbox(sig, label)) {
        fTiming[sig] = 0;
        return sig;
    } else if (isSigVSlider(sig, label, c, x, y, z)) {
        fTiming[sig] = 0;
        return sig;
    } else if (isSigHSlider(sig, label, c, x, y, z)) {
        fTiming[sig] = 0;
        return sig;
    } else if (isSigNumEntry(sig, label, c, x, y, z)) {
        fTiming[sig] = 0;
        return sig;
    } else if (isSigVBargraph(sig, label, x, y, z)) {
        Tree z2      = self(z);
        Tree res     = sigRegister(sigVBargraph(label, x, y, z2));
        fTiming[res] = fTiming[z2] + 1;
        return res;
    } else if (isSigHBargraph(sig, label, x, y, z)) {
        Tree z2      = self(z);
        Tree res     = sigRegister(sigHBargraph(label, x, y, z2));
        fTiming[res] = fTiming[z2] + 1;
        return res;
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
        Tree x2      = self(x);
        Tree y2      = self(y);
        Tree res     = sigRegister(sigAttach(x2, y2));
        fTiming[res] = std::max(fTiming[x2], fTiming[y2]) + 1;
        return res;
    } else if (isSigEnable(sig, x, y)) {
        Tree x2      = self(x);
        Tree y2      = self(y);
        Tree res     = sigRegister(sigEnable(x2, y2));
        fTiming[res] = std::max(fTiming[x2], fTiming[y2]) + 1;
        return res;
    } else if (isSigControl(sig, x, y)) {
        Tree x2      = self(x);
        Tree y2      = self(y);
        Tree res     = sigRegister(sigControl(x2, y2));
        fTiming[res] = std::max(fTiming[x2], fTiming[y2]) + 1;
        return res;
    }

    // Signal interval annotation
    /*else if (isSigAssertBounds(sig, x, y, z)) {
        return sigAssertBounds(self(x), self(y), self(z));
    }*/
    else if (isSigLowest(sig, x)) {
        fTiming[sig] = 0;
        return sig;
    } else if (isSigHighest(sig, x)) {
        fTiming[sig] = 0;
        return sig;
    }

    else if (isSigRegister(sig, x)) {
        std::cerr << "ASSERT : already retimed : " << *sig << std::endl;
        faustassert(false);
    }

    else {
        std::cerr << "ASSERT : unrecognized signal : " << *sig << std::endl;
        faustassert(false);
    }
    return 0;
}
