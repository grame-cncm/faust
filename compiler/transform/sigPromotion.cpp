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
#include <map>
#include "global.hh"
#include "property.hh"
#include "signals.hh"
#include "sigtyperules.hh"
#include "tlib.hh"
#include "tree.hh"
#include "xtended.hh"
#include "prim2.hh"

void SignalTreeChecker::visit(Tree sig)
{
    SignalVisitor::visit(sig);
  
    int opnum;
    Tree x, y, sel, sf, chan, part, ridx;
    
    // Extended
    xtended* p = (xtended*)getUserData(sig);
    if (p && strcmp(p->name(), "pow") != 0) { // 'pow' can have args of both int and real types
        vector<Type> vt;
        for (Tree b : sig->branches()) {
            vt.push_back(getCertifiedSigType(b));
        }
        Type tx = p->infereSigType(vt);
        
        for (Tree b : sig->branches()) {
            if (tx->nature() != getCertifiedSigType(b)->nature()) {
                cerr << "ERROR : xtended wih args of incorrect types : " << *sig << endl;
                faustassert(false);
            }
        }
    } else if (isSigBinOp(sig, &opnum, x, y)) {
        Type tx = getCertifiedSigType(x);
        Type ty = getCertifiedSigType(y);
        
        if (tx->nature() != ty->nature()) {
            cerr << "ERROR : isSigBinOp of args with different types : " << *sig << endl;
            faustassert(false);
        }
    } else if (isSigSelect2(sig, sel, x, y )) {
        if (getCertifiedSigType(sel)->nature() != kInt) {
            cerr << "ERROR : isSigSelect2 with wrong typed selector : " << *sig << endl;
            faustassert(false);
        }
    
    } else if (isSigDelay(sig, x, y)) {
        if (getCertifiedSigType(y)->nature() != kInt) {
            cerr << "ERROR : isSigDelay with a wrong typed delay : " << *sig << endl;
            faustassert(false);
        }
        
    } else if (isSigIntCast(sig, x)) {
        if (getCertifiedSigType(x)->nature() == kInt) {
            cerr << "ERROR : isSigIntCast of a kInt signal : " << *sig << endl;
            faustassert(false);
        }
        
    } else if (isSigFloatCast(sig, x)) {
        if (getCertifiedSigType(x)->nature() == kReal) {
            cerr << "ERROR : isSigFloatCast of a kReal signal : " << *sig << endl;
            faustassert(false);
        }
        
    } else if (isSigSoundfileLength(sig, sf, part)) {
        if (getCertifiedSigType(part)->nature() != kInt) {
            cerr << "ERROR : isSigSoundfileLength with a wrong typed part : " << *sig << endl;
            faustassert(false);
        }
        
    } else if (isSigSoundfileRate(sig, sf, part)) {
        if (getCertifiedSigType(part)->nature() != kInt) {
            cerr << "ERROR : isSigSoundfileRate with a wrong typed part : " << *sig << endl;
            faustassert(false);
        }
        
    } else if (isSigSoundfileBuffer(sig, sf, chan, part, ridx)) {
        if (getCertifiedSigType(part)->nature() != kInt) {
            cerr << "ERROR : isSigSoundfileBuffer with a wrong typed part : " << *sig << endl;
            faustassert(false);
        }
        if (getCertifiedSigType(ridx)->nature() != kInt) {
            cerr << "ERROR : isSigSoundfileBuffer with a wrong typed ridx : " << *sig << endl;
            faustassert(false);
        }
    }
}

//-------------------------SignalPromotion-------------------------------
// Adds explicit int or float cast when needed. This is needed prior
// to any optimisations to avoid to scramble int and float expressions.
// The signal has to be properly typed with 'typeAnnotation'.
//----------------------------------------------------------------------

Tree SignalPromotion::transformation(Tree sig)
{
    int  op;
    Tree id, sel, x, y, ff, largs, sf, chan, part, tbl, idx, ridx, data;
    
    // Extended
    xtended* p = (xtended*)getUserData(sig);
    if (p) {
        vector<Type> vt;
        for (Tree b : sig->branches()) {
            vt.push_back(getCertifiedSigType(b));
        }
        Type tx = p->infereSigType(vt);
        
        vector<Tree> new_branches;
        for (Tree b : sig->branches()) {
            new_branches.push_back(smartCast(tx, getCertifiedSigType(b), self(b)));
        }
        
        return tree(sig->node(), new_branches);
    }
    
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
                // Done here instead of 'simplify' to be sure the signals are correctly typed.
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
                // These operations require integers
                return sigBinOp(op, smartIntCast(tx, self(x)), smartIntCast(ty, self(y)));
             
            default:
                return sigBinOp(op, self(x), self(y));
        }
    }
    
    // Foreign functions
    else if (isSigFFun(sig, ff, largs)) {
        siglist clargs;
        int len = ffarity(ff) - 1;
        for (int i = 0; i < ffarity(ff); i++) {
            Tree arg = nth(largs, i);
            Type ta = getCertifiedSigType(arg);
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
    else if (isSigWRTbl(sig, id, tbl, idx, data)) {
        Type t1 = getCertifiedSigType(tbl);
        Type t2 = getCertifiedSigType(data);
        return sigWRTbl(id, self(tbl), self(idx), smartCast(t1, t2, self(data)));
    }
    
    // Soundfiles
    else if (isSigSoundfileLength(sig, sf, part)) {
        return sigSoundfileLength(self(sf), smartIntCast(getCertifiedSigType(part), self(part)));
    }
    else if (isSigSoundfileRate(sig, sf, part)) {
        return sigSoundfileRate(self(sf), smartIntCast(getCertifiedSigType(part), self(part)));
    }
    else if (isSigSoundfileBuffer(sig, sf, chan, part, ridx)) {
        return sigSoundfileBuffer(self(sf), self(chan),
                                  smartIntCast(getCertifiedSigType(part), self(part)),
                                  smartIntCast(getCertifiedSigType(ridx), self(ridx)));
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

// Public API
Tree castPromote(Tree sig, bool trace)
{
    // Check that the root tree is properly type annotated
    getCertifiedSigType(sig);
    
    SignalPromotion SP;
    if (trace) SP.trace(true, "Cast");
    return SP.mapself(sig);
}
