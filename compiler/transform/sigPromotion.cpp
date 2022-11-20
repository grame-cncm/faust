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

#include "sigPromotion.hh"
#include <stdlib.h>
#include <cstdlib>

#include "signals.hh"
#include "prim2.hh"
#include "global.hh"
#include "xtended.hh"
#include "sigtyperules.hh"

void SignalTreeChecker::visit(Tree sig)
{
    int  opnum;
    Tree id, x, y, sel, sf, ff, largs, chan, part, idx, tb, ws, label, min, max, t0;

    // Extended
    xtended* p = (xtended*)getUserData(sig);
    if (p) {
        vector<Type> vt;
        for (Tree b : sig->branches()) {
            vt.push_back(getCertifiedSigType(b));
        }
        Type tx = p->infereSigType(vt);
        for (Tree b : sig->branches()) {
            if (tx->nature() != getCertifiedSigType(b)->nature()) {
                cerr << "ERROR : xtended wih args of incorrect types : " << ppsig(sig) << endl;
                faustassert(false);
            }
        }
        
    // Binary operations
    } else if (isSigBinOp(sig, &opnum, x, y)) {
        Type tx = getCertifiedSigType(x);
        Type ty = getCertifiedSigType(y);
        if (tx->nature() != ty->nature()) {
            cerr << "ERROR : isSigBinOp of args with different types : " << ppsig(sig) << endl;
            faustassert(false);
        }
        
    // Foreign functions
    } else if (isSigFFun(sig, ff, largs)) {
        int len = ffarity(ff) - 1;
        for (int i = 0; i < ffarity(ff); i++) {
            int type = ffargtype(ff, len - i);
            if (getCertifiedSigType(nth(largs, i))->nature() != type && type != kAny) {
                cerr << "ERROR : isSigFFun of args with incoherent types : " << ppsig(sig) << endl;
                faustassert(false);
            }
        }
        if (ffrestype(ff) != getCertifiedSigType(sig)->nature()) {
            cerr << "ERROR : isSigFFun of res with incoherent type : " << ppsig(sig) << endl;
            faustassert(false);
        }
        
    // Select2 (and Select3 expressed with Select2)
    } else if (isSigSelect2(sig, sel, x, y)) {
        if (getCertifiedSigType(sel)->nature() != kInt) {
            cerr << "ERROR : isSigSelect2 with wrong typed selector : " << ppsig(sig) << endl;
            faustassert(false);
        }

    // Delay
    } else if (isSigDelay(sig, x, y)) {
        if (getCertifiedSigType(y)->nature() != kInt) {
            cerr << "ERROR : isSigDelay with a wrong typed delay : " << ppsig(sig) << endl;
            faustassert(false);
        }

    // Int and Float Cast
    } else if (isSigIntCast(sig, x)) {
        if (getCertifiedSigType(x)->nature() == kInt) {
            cerr << "ERROR : isSigIntCast of a kInt signal : " << ppsig(sig) << endl;
            faustassert(false);
        }

    } else if (isSigFloatCast(sig, x)) {
        if (getCertifiedSigType(x)->nature() == kReal) {
            cerr << "ERROR : isSigFloatCast of a kReal signal : " << ppsig(sig) << endl;
            faustassert(false);
        }
        
    // Tables
    } else if (isSigRDTbl(sig, tb, idx)) {
        if (getCertifiedSigType(idx)->nature() != kInt) {
            cerr << "ERROR : isSigRDTbl with a wrong typed rdx : " << ppsig(sig) << endl;
            faustassert(false);
        }
        
    } else if (isSigWRTbl(sig, id, tb, idx, ws)) {
        if (getCertifiedSigType(idx)->nature() != kInt) {
            cerr << "ERROR : isSigWRTbl with a wrong typed wdx : " << ppsig(sig) << endl;
            faustassert(false);
        }
        if (getCertifiedSigType(tb)->nature() != getCertifiedSigType(ws)->nature()) {
            cerr << "ERROR : isSigWRTbl with non matching tb and ws types : " << ppsig(sig) << endl;
            faustassert(false);
        }
 
    // Soundfiles
    } else if (isSigSoundfileLength(sig, sf, part)) {
        if (getCertifiedSigType(part)->nature() != kInt) {
            cerr << "ERROR : isSigSoundfileLength with a wrong typed part : " << ppsig(sig) << endl;
            faustassert(false);
        }

    } else if (isSigSoundfileRate(sig, sf, part)) {
        if (getCertifiedSigType(part)->nature() != kInt) {
            cerr << "ERROR : isSigSoundfileRate with a wrong typed part : " << ppsig(sig) << endl;
            faustassert(false);
        }

    } else if (isSigSoundfileBuffer(sig, sf, chan, part, idx)) {
        if (getCertifiedSigType(part)->nature() != kInt) {
            cerr << "ERROR : isSigSoundfileBuffer with a wrong typed part : " << ppsig(sig) << endl;
            faustassert(false);
        }
        if (getCertifiedSigType(idx)->nature() != kInt) {
            cerr << "ERROR : isSigSoundfileBuffer with a wrong typed ridx : " << ppsig(sig) << endl;
            faustassert(false);
        }
        
    // Bargraph
    } else if (isSigHBargraph(sig, label, min, max, t0)) {
        if (getCertifiedSigType(t0)->nature() == kInt) {
            cerr << "ERROR : isSigHBargraph of a kInt signal : " << ppsig(sig) << endl;
            faustassert(false);
        }
        
    } else if (isSigVBargraph(sig, label, min, max, t0)) {
        if (getCertifiedSigType(t0)->nature() == kInt) {
            cerr << "ERROR : isSigVBargraph of a kInt signal : " << ppsig(sig) << endl;
            faustassert(false);
        }
 
    }
        
    // Default case and recursion
    SignalVisitor::visit(sig);
}

//-------------------------SignalPromotion-------------------------------
// Adds explicit int or float cast when needed. This is needed prior
// to any optimisations to avoid to scramble int and float expressions.
// The signal has to be properly typed with 'typeAnnotation'.
//----------------------------------------------------------------------

Tree SignalPromotion::transformation(Tree sig)
{
    int  op;
    Tree id, sel, x, y, ff, largs, sf, chan, part, tb, idx, ws, min, max, label, t0;

    // Extended
    xtended* p = (xtended*)getUserData(sig);
    if (p) {
        vector<Type> vt;
        for (Tree b : sig->branches()) {
            vt.push_back(getCertifiedSigType(b));
        }
        Type tr = p->infereSigType(vt);

        vector<Tree> new_branches;
        for (Tree b : sig->branches()) {
            new_branches.push_back(smartCast(tr, getCertifiedSigType(b), self(b)));
        }
        return tree(sig->node(), new_branches);
    }

    // Delay
    else if (isSigDelay(sig, x, y)) {
        return sigDelay(self(x), smartIntCast(getCertifiedSigType(y), self(y)));
    }

    // Binary operations
    // kAdd, kSub, kMul, kDiv, kRem, kLsh, kARsh, kLRsh, kGT, kLT, kGE, kLE, kEQ, kNE, kAND, kOR, kXOR };
    else if (isSigBinOp(sig, &op, x, y)) {
        Type tx = getCertifiedSigType(x);
        Type ty = getCertifiedSigType(y);

        switch (op) {
            case kAdd:
            case kSub:
            case kMul:
            case kGT:
            case kLT:
            case kGE:
            case kLE:
            case kEQ:
            case kNE:
                if (tx->nature() == ty->nature()) {
                    // same nature => no promotion needed
                    return sigBinOp(op, self(x), self(y));
                } else {
                    // float promotion needed
                    return sigBinOp(op, smartFloatCast(tx, self(x)), smartFloatCast(ty, self(y)));
                }

            case kRem:
                if (tx->nature() == kInt && ty->nature() == kInt) {
                    // int arguments => no promotion needed
                    return sigBinOp(op, self(x), self(y));
                } else {
                    // float promotion needed, rem (%) replaced by fmod
                    vector<Tree> lsig = {smartFloatCast(tx, self(x)), smartFloatCast(ty, self(y))};
                    return gGlobal->gFmodPrim->computeSigOutput(lsig);
                }

            case kDiv: {
                // done here instead of 'simplify' to be sure the signals are correctly typed
                interval i1 = tx->getInterval();
                interval j1 = ty->getInterval();
                if (i1.valid & j1.valid && gGlobal->gMathExceptions && j1.haszero()) {
                    cerr << "WARNING : potential division by zero (" << i1 << "/" << j1 << ")" << endl;
                }
                // the result of a division is always a float
                return sigBinOp(op, smartFloatCast(tx, self(x)), smartFloatCast(ty, self(y)));
            }

            case kAND:
            case kOR:
            case kXOR:
            case kLsh:
            case kARsh:
            case kLRsh:
                // these operations require integers
                return sigBinOp(op, smartIntCast(tx, self(x)), smartIntCast(ty, self(y)));

            default:
                return sigBinOp(op, self(x), self(y));
        }
    }

    // Foreign functions
    else if (isSigFFun(sig, ff, largs)) {
        siglist clargs;
        int     len = ffarity(ff) - 1;
        for (int i = 0; i < ffarity(ff); i++) {
            Tree arg = nth(largs, i);
            Type ta  = getCertifiedSigType(arg);
            clargs.push_back(smartCast(ffargtype(ff, len - i), ta->nature(), self(arg)));
        }
        return sigFFun(ff, listConvert(clargs));
    }

    // Select2 (and Select3 expressed with Select2)
    else if (isSigSelect2(sig, sel, x, y)) {
        Type ts = getCertifiedSigType(sel);
        Type tx = getCertifiedSigType(x);
        Type ty = getCertifiedSigType(y);

        if (tx->nature() == ty->nature()) {
            // same nature => no promotion needed
            return sigSelect2(smartIntCast(ts, self(sel)), self(x), self(y));
        } else {
            // float promotion needed
            return sigSelect2(smartIntCast(ts, self(sel)), smartFloatCast(tx, self(x)), smartFloatCast(ty, self(y)));
        }
    }

    // Int and Float Cast
    else if (isSigIntCast(sig, x)) {
        return smartIntCast(getCertifiedSigType(x), self(x));
    } else if (isSigFloatCast(sig, x)) {
        return smartFloatCast(getCertifiedSigType(x), self(x));
    }

    // Tables
    else if (isSigRDTbl(sig, tb, idx)) {
        Type tx = getCertifiedSigType(idx);
        return sigRDTbl(self(tb), smartIntCast(tx, self(idx)));
    }

    else if (isSigWRTbl(sig, id, tb, idx, ws)) {
        Type tx = getCertifiedSigType(idx);
        Type t1 = getCertifiedSigType(tb);
        Type t2 = getCertifiedSigType(ws);
        return sigWRTbl(id, self(tb), smartIntCast(tx, self(idx)), smartCast(t1, t2, self(ws)));
    }

    // Soundfiles
    else if (isSigSoundfileLength(sig, sf, part)) {
        return sigSoundfileLength(self(sf), smartIntCast(getCertifiedSigType(part), self(part)));
    } else if (isSigSoundfileRate(sig, sf, part)) {
        return sigSoundfileRate(self(sf), smartIntCast(getCertifiedSigType(part), self(part)));
    } else if (isSigSoundfileBuffer(sig, sf, chan, part, idx)) {
        return sigSoundfileBuffer(self(sf), self(chan),
                                  smartIntCast(getCertifiedSigType(part), self(part)),
                                  smartIntCast(getCertifiedSigType(idx), self(idx)));
    }
    
    // All UI items with range (vslider, hslider, nentry) are treated
    // as float 'constant numerical expressions'. See realeval in eval.cpp
    
    // Bargraph
    else if (isSigHBargraph(sig, label, min, max, t0)) {
        Type tx0 = getCertifiedSigType(t0);
        return sigHBargraph(label, self(min), self(max), smartFloatCast(tx0, self(t0)));
    }
    
    else if (isSigVBargraph(sig, label, min, max, t0)) {
        Type tx0 = getCertifiedSigType(t0);
        return sigVBargraph(label, self(min), self(max), smartFloatCast(tx0, self(t0)));
    }
    
    // Other cases => identity transformation
    else {
        return SignalIdentity::transformation(sig);
    }
}

Tree SignalPromotion::smartCast(Type t1, Type t2, Tree sig)
{
    return smartCast(t1->nature(), t2->nature(), sig);
}

Tree SignalPromotion::smartCast(int t1, int t2, Tree sig)
{
    return (t1 != t2) ? cast(t1, sig) : sig;
}

Tree SignalPromotion::cast(Type t, Tree sig)
{
    return cast(t->nature(), sig);
}

Tree SignalPromotion::cast(int t, Tree sig)
{
    if (t == kReal) {
        return sigFloatCast(sig);
    } else if (t == kInt) {
        return sigIntCast(sig);
    } else if (t == kAny) {
        return sig;
    } else {
        faustassert(false);
        return nullptr;
    }
}

/*
## smartIntCast[S] : adds an intCast(S) only if needed

    smartIntCast[S] = intCast(S) when type(S) = float
    smartIntCast[S] = S          otherwise
*/

Tree SignalPromotion::smartIntCast(Type t, Tree sig)
{
    return (t->nature() == kReal) ? sigIntCast(sig) : sig;
}

/*
## smartFloatCast[S] : adds a floatCast(S) only if needed

    smartFloatCast[S] = floatCast(S) when type(S) = int
    smartFloatCast[S] = S            otherwise
*/
Tree SignalPromotion::smartFloatCast(Type t, Tree sig)
{
    return (t->nature() == kInt) ? sigFloatCast(sig) : sig;
}

Tree SignalBool2IntPromotion::transformation(Tree sig)
{
    int op;
    Tree x, y;
    
    if (isSigBinOp(sig, &op, x, y)) {
        if (isBoolOpcode(op)) {
            return sigIntCast(sigBinOp(op, self(x), self(y)));
        } else {
            return SignalIdentity::transformation(sig);
        }
    // Other cases => identity transformation
    } else {
        return SignalIdentity::transformation(sig);
    }
}

Tree SignalTablePromotion::safeSigRDTbl(Tree sig, Tree tb, Tree size, Tree idx)
{
    interval idx_i = getCertifiedSigType(idx)->getInterval();
    if (idx_i.lo < 0 || idx_i.hi >= tree2int(size)) {
        stringstream error;
        error << "WARNING : RDTbl read index [" << idx_i.lo << ":" << idx_i.hi
              << "] is outside of table size (" << tree2int(size) << ") in " << ppsig(sig);
        if (gAllWarning) gWarningMessages.push_back(error.str());
        return sigRDTbl(self(tb), sigMax(sigInt(0), sigMin(self(idx), sigSub(size, sigInt(1)))));
    } else {
        return SignalIdentity::transformation(sig);
    }
}

Tree SignalTablePromotion::safeSigWRTbl(Tree sig, Tree id, Tree tb, Tree size, Tree idx, Tree ws)
{
    interval idx_i = getCertifiedSigType(idx)->getInterval();
    if (idx_i.lo < 0 || idx_i.hi >= tree2int(size)) {
        stringstream error;
        error << "WARNING : WRTbl write index [" << idx_i.lo << ":" << idx_i.hi
              << "] is outside of table size (" << tree2int(size) << ") in " << ppsig(sig);
        if (gAllWarning) gWarningMessages.push_back(error.str());
        return sigWRTbl(id, self(tb), sigMax(sigInt(0), sigMin(self(idx), sigSub(size, sigInt(1)))), self(ws));
    } else {
        return SignalIdentity::transformation(sig);
    }
}

Tree SignalTablePromotion::getSize(Tree sig)
{
    Tree id, tb, size, content, idx, ws;
    
    if (isSigTable(sig, id, size, content)) {
        return size;
    } else if (isSigWRTbl(sig, id, tb, idx, ws)) {
        return getSize(tb);
    } else {
        faustassert(false);
        return nullptr;
    }
}

Tree SignalTablePromotion::transformation(Tree sig)
{
    Tree tb, id, idx, ws;
    
    if (isSigRDTbl(sig, tb, idx)) {
        return safeSigRDTbl(sig, tb, getSize(tb), idx);
    } else if (isSigWRTbl(sig, id, tb, idx, ws)) {
        return safeSigWRTbl(sig, id, tb, getSize(tb), idx, ws);
    // Other cases => identity transformation
    } else {
        return SignalIdentity::transformation(sig);
    }
}

Tree SignalUIPromotion::transformation(Tree sig)
{
    Tree label, init, min, max, step;
    
    if (isSigVSlider(sig, label, init, min, max, step)
        || isSigHSlider(sig, label, init, min, max, step)
        || isSigNumEntry(sig, label, init, min, max, step)) {
        return sigMax(min, sigMin(max, sig));
    // Other cases => identity transformation
    } else {
        return SignalIdentity::transformation(sig);
    }
}

// Public API
Tree sigPromote(Tree sig, bool trace)
{
    // Check that the root tree is properly type annotated
    getCertifiedSigType(sig);

    SignalPromotion SP;
    if (trace) SP.trace(true, "Cast");
    return SP.mapself(sig);
}

Tree sigBool2IntPromote(Tree sig)
{
    // Check that the root tree is properly type annotated
    getCertifiedSigType(sig);
    
    SignalBool2IntPromotion SP;
    return SP.mapself(sig);
}

Tree signalTablePromote(Tree sig)
{
    // Check that the root tree is properly type annotated
    getCertifiedSigType(sig);
    
    SignalTablePromotion SP;
    return SP.mapself(sig);
}

Tree signalUIPromote(Tree sig)
{
    // Check that the root tree is properly type annotated
    getCertifiedSigType(sig);
    
    SignalUIPromotion SP;
    return SP.mapself(sig);
}
