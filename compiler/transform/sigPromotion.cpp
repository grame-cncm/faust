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

#include <stdlib.h>
#include <cstdlib>
#include <sstream>

#include "sigPromotion.hh"
#include "global.hh"
#include "prim2.hh"
#include "signals.hh"
#include "sigtyperules.hh"
#include "xtended.hh"
#include "floats.hh"

using namespace std;

SignalTypePrinter::SignalTypePrinter(Tree L)
{
    // Check that the root tree is properly type annotated
    getCertifiedSigType(L);
    visitRoot(L);
    /*
     HACK: since the signal tree shape is still not deterministic,
     we sort the list to be sure it stays the same.
     To be removed if the tree shape becomes deterministic.
     */
    std::sort(fPrinted.begin(), fPrinted.end());
    std::cout << "Size = " << fPrinted.size() << std::endl;
    for (const auto& it : fPrinted) {
        std::cout << it;
    }
}

void SignalTypePrinter::visit(Tree sig)
{
    stringstream type;
    type << "Type = " << getCertifiedSigType(sig) << endl;
    fPrinted.push_back(type.str());
    
    // Default case and recursion
    SignalVisitor::visit(sig);
}

void SignalChecker::isRange(Tree sig, Tree init_aux, Tree min_aux, Tree max_aux)
{
    std::stringstream error;
    double init = tree2float(init_aux);
    double min = tree2float(min_aux);
    double max = tree2float(max_aux);
    if (min > max) {
        error << "ERROR : min = " << min << " should be less than max = " << max << " in '" << ppsig(sig) << "'\n";
        throw faustexception(error.str());
    } else if (init < min || init > max) {
        error << "ERROR : init = " << init << " outside of [" << min << " " << max << "] range in '" << ppsig(sig) << "'\n";
        throw faustexception(error.str());
    }
}

void SignalChecker::visit(Tree sig)
{
    int  opnum;
    Tree size, gen, wi, ri, x, y, sel, sf, ff, largs, chan, part, tb, ws, label, init, min, max, step, t0;

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
                cerr << "ASSERT : xtended with args of incorrect types : " << ppsig(sig, MAX_ERROR_SIZE) << endl;
                faustassert(false);
            }
        }

        // Binary operations
    } else if (isSigBinOp(sig, &opnum, x, y)) {
        Type tx = getCertifiedSigType(x);
        Type ty = getCertifiedSigType(y);
        if (tx->nature() != ty->nature()) {
            cerr << "ASSERT : isSigBinOp of args with different types : " << ppsig(sig, MAX_ERROR_SIZE) << endl;
            faustassert(false);
        }

        // Foreign functions
    } else if (isSigFFun(sig, ff, largs)) {
        int len = ffarity(ff) - 1;
        for (int i = 0; i < ffarity(ff); i++) {
            int type = ffargtype(ff, len - i);
            if (getCertifiedSigType(nth(largs, i))->nature() != type && type != kAny) {
                cerr << "ASSERT : isSigFFun of args with incoherent types : " << ppsig(sig, MAX_ERROR_SIZE) << endl;
                faustassert(false);
            }
        }
        if (ffrestype(ff) != getCertifiedSigType(sig)->nature()) {
            cerr << "ASSERT : isSigFFun of res with incoherent type : " << ppsig(sig, MAX_ERROR_SIZE) << endl;
            faustassert(false);
        }

        // Select2 (and Select3 expressed with Select2)
    } else if (isSigSelect2(sig, sel, x, y)) {
        if (getCertifiedSigType(sel)->nature() != kInt) {
            cerr << "ASSERT : isSigSelect2 with wrong typed selector : " << ppsig(sig, MAX_ERROR_SIZE) << endl;
            faustassert(false);
        }

        // Delay
    } else if (isSigDelay(sig, x, y)) {
        if (getCertifiedSigType(y)->nature() != kInt) {
            cerr << "ASSERT : isSigDelay with a wrong typed delay : " << ppsig(sig, MAX_ERROR_SIZE) << endl;
            faustassert(false);
        }

        // Int, Bit and Float Cast
    } else if (isSigIntCast(sig, x)) {
        if (getCertifiedSigType(x)->nature() == kInt) {
            cerr << "ASSERT : isSigIntCast of a kInt signal : " << ppsig(sig, MAX_ERROR_SIZE) << endl;
            faustassert(false);
        }
        
    } else if (isSigBitCast(sig, x)) {
        if (getCertifiedSigType(x)->nature() == kInt) {
            cerr << "ASSERT : isSigBitCast of a kInt signal : " << ppsig(sig, MAX_ERROR_SIZE) << endl;
            faustassert(false);
        }

    } else if (isSigFloatCast(sig, x)) {
        if (getCertifiedSigType(x)->nature() == kReal) {
            cerr << "ASSERT : isSigFloatCast of a kReal signal : " << ppsig(sig, MAX_ERROR_SIZE) << endl;
            faustassert(false);
        }

        // Tables
    } else if (isSigRDTbl(sig, tb, ri)) {
        if (getCertifiedSigType(ri)->nature() != kInt) {
            cerr << "ASSERT : isSigRDTbl with a wrong typed rdx : " << ppsig(sig, MAX_ERROR_SIZE) << endl;
            faustassert(false);
        }

    } else if (isSigWRTbl(sig, size, gen, wi, ws)) {
        if ((wi != gGlobal->nil) && getCertifiedSigType(wi)->nature() != kInt) {
            cerr << "ASSERT : isSigWRTbl with a wrong typed wdx : " << ppsig(sig, MAX_ERROR_SIZE) << endl;
            faustassert(false);
        }
        if ((wi != gGlobal->nil) && getCertifiedSigType(gen)->nature() != getCertifiedSigType(ws)->nature()) {
            cerr << "ASSERT : isSigWRTbl with non matching gen and ws types : " << ppsig(sig, MAX_ERROR_SIZE) << endl;
            faustassert(false);
        }

        // Soundfiles
    } else if (isSigSoundfileLength(sig, sf, part)) {
        if (getCertifiedSigType(part)->nature() != kInt) {
            cerr << "ASSERT : isSigSoundfileLength with a wrong typed part : " << ppsig(sig, MAX_ERROR_SIZE) << endl;
            faustassert(false);
        }

    } else if (isSigSoundfileRate(sig, sf, part)) {
        if (getCertifiedSigType(part)->nature() != kInt) {
            cerr << "ASSERT : isSigSoundfileRate with a wrong typed part : " << ppsig(sig, MAX_ERROR_SIZE) << endl;
            faustassert(false);
        }

    } else if (isSigSoundfileBuffer(sig, sf, chan, part, ri)) {
        if (getCertifiedSigType(part)->nature() != kInt) {
            cerr << "ASSERT : isSigSoundfileBuffer with a wrong typed part : " << ppsig(sig, MAX_ERROR_SIZE) << endl;
            faustassert(false);
        }
        if (getCertifiedSigType(ri)->nature() != kInt) {
            cerr << "ASSERT : isSigSoundfileBuffer with a wrong typed ri : " << ppsig(sig, MAX_ERROR_SIZE) << endl;
            faustassert(false);
        }
        
        // Sliders and nentry
    } else if (isSigVSlider(sig, label, init, min, max, step)
               || isSigHSlider(sig, label, init, min, max, step)
               || isSigNumEntry(sig, label, init, min, max, step)) {
        isRange(sig, init, min, max);

        // Bargraph
    } else if (isSigHBargraph(sig, label, min, max, t0)) {
        if (getCertifiedSigType(t0)->nature() == kInt) {
            cerr << "ASSERT : isSigHBargraph of a kInt signal : " << ppsig(sig, MAX_ERROR_SIZE) << endl;
            faustassert(false);
        }

    } else if (isSigVBargraph(sig, label, min, max, t0)) {
        if (getCertifiedSigType(t0)->nature() == kInt) {
            cerr << "ASSERT : isSigVBargraph of a kInt signal : " << ppsig(sig, MAX_ERROR_SIZE) << endl;
            faustassert(false);
        }
        
        // signal bounds
    } else if (isSigLowest(sig, x) || isSigHighest(sig, x)) {
        cerr << "ASSERT : annotations should have been deleted in Simplification process" << endl;
        faustassert(false);
        
        // enable/control
    } else if (isSigControl(sig, x, y) && gGlobal->gVectorSwitch) {
        throw faustexception("ERROR : 'control/enable' can only be used in scalar mode\n");
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
    Tree size, gen, wi, ri, sel, x, y, ff, largs, sf, chan, part, tb, ws, min, max, label, t0;

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
                if (i1.isValid() && j1.isValid() && gGlobal->gMathExceptions && j1.hasZero()) {
                    stringstream error;
                    error << "WARNING : potential division by zero (" << i1 << "/" << j1 << ")";
                    gWarningMessages.push_back(error.str());
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

    // Int, Bit and Float Cast
    else if (isSigIntCast(sig, x)) {
        return smartIntCast(getCertifiedSigType(x), self(x));
    } else if (isSigBitCast(sig, x)) {
        return sigBitCast(self(x));
    } else if (isSigFloatCast(sig, x)) {
        return smartFloatCast(getCertifiedSigType(x), self(x));
    }

    // Tables
    else if (isSigRDTbl(sig, tb, ri)) {
        Type tx = getCertifiedSigType(ri);
        return sigRDTbl(self(tb), smartIntCast(tx, self(ri)));
    }

    else if (isSigWRTbl(sig, size, gen, wi, ws)) {
        if (wi == gGlobal->nil) {
            // rdtable
            return sigWRTbl(self(size), self(gen));
        } else {
            // rwtable
            Type tx = getCertifiedSigType(wi);
            Type t1 = getCertifiedSigType(gen);
            Type t2 = getCertifiedSigType(ws);
            return sigWRTbl(self(size), self(gen), smartIntCast(tx, self(wi)), smartCast(t1, t2, self(ws)));
        }
    }

    // Soundfiles
    else if (isSigSoundfileLength(sig, sf, part)) {
        return sigSoundfileLength(self(sf), smartIntCast(getCertifiedSigType(part), self(part)));
    } else if (isSigSoundfileRate(sig, sf, part)) {
        return sigSoundfileRate(self(sf), smartIntCast(getCertifiedSigType(part), self(part)));
    } else if (isSigSoundfileBuffer(sig, sf, chan, part, ri)) {
        return sigSoundfileBuffer(self(sf), self(chan), smartIntCast(getCertifiedSigType(part), self(part)),
                                  smartIntCast(getCertifiedSigType(ri), self(ri)));
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
   
    else {
        // Other cases => identity transformation
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
    int  op;
    Tree x, y;
    
    if (isSigBinOp(sig, &op, x, y)) {
        if (isBoolOpcode(op)) {
            return sigIntCast(sigBinOp(op, self(x), self(y)));
        } else {
            return SignalIdentity::transformation(sig);
        }
    } else {
        // Other cases => identity transformation
        return SignalIdentity::transformation(sig);
    }
}

Tree SignalFXPromotion::transformation(Tree sig)
{
    Tree sel, x, y;
    if (isSigSelect2(sig, sel, x, y)) {
        return sigSelect2(self(sel), sigFloatCast(self(x)), sigFloatCast(self(y)));
    } else {
        // Other cases => identity transformation
        return SignalIdentity::transformation(sig);
   }
}

Tree SignalTablePromotion::safeSigRDTbl(Tree sig, Tree tbl, Tree size_aux, Tree ri)
{
    int size = tree2int(size_aux);
    if (size <= 0) {
        stringstream error;
        error << "ERROR : RDTbl size = " << size << " should be > 0 \n";
        throw faustexception(error.str());
    }
    interval ri_i = getCertifiedSigType(ri)->getInterval();
    if (ri_i.lo() < 0 || ri_i.hi() >= size) {
        if (gAllWarning) {
            stringstream error;
            error << "WARNING : RDTbl read index [" << ri_i.lo() << ":" << ri_i.hi() << "] is outside of table size ("
                  << size << ") in : " << ppsig(sig, MAX_ERROR_SIZE);
            gWarningMessages.push_back(error.str());
        }
        return sigRDTbl(self(tbl), sigMax(sigInt(0), sigMin(self(ri), sigSub(size_aux, sigInt(1)))));
    } else {
        // Other cases => identity transformation
        return SignalIdentity::transformation(sig);
    }
}

Tree SignalTablePromotion::safeSigWRTbl(Tree sig, Tree size_aux, Tree gen, Tree wi, Tree ws)
{
    int size = tree2int(size_aux);
    if (size <= 0) {
        stringstream error;
        error << "ERROR : WRTbl size = " << size << " should be > 0 \n";
        throw faustexception(error.str());
    }
    interval wi_i = getCertifiedSigType(wi)->getInterval();
    if (wi_i.lo() < 0 || wi_i.hi() >= size) {
        if (gAllWarning) {
            stringstream error;
            error << "WARNING : WRTbl write index [" << wi_i.lo() << ":" << wi_i.hi() << "] is outside of table size ("
                  << size << ") in : " << ppsig(sig, MAX_ERROR_SIZE);
            gWarningMessages.push_back(error.str());
        }
        return sigWRTbl(self(size_aux), self(gen), sigMax(sigInt(0), sigMin(self(wi), sigSub(size_aux, sigInt(1)))), self(ws));
    } else {
        // Other cases => identity transformation
        return SignalIdentity::transformation(sig);
    }
}

Tree SignalTablePromotion::transformation(Tree sig)
{
    Tree tbl, size, gen, wi, ws, ri;

    if (isSigRDTbl(sig, tbl, ri)) {
        isSigWRTbl(tbl, size, gen, wi, ws);
        if (wi == gGlobal->nil) {
            // rdtable
            return safeSigRDTbl(sig, tbl, size, ri);
        } else {
            // rwtable
            return safeSigRDTbl(sig, safeSigWRTbl(tbl, size, gen, wi, ws), size, ri);
        }
    } else {
        // Other cases => identity transformation
        return SignalIdentity::transformation(sig);
    }
}

Tree SignalIntCastPromotion::transformation(Tree sig)
{
    Tree x;
    if (isSigIntCast(sig, x)) {
        interval x_i = getCertifiedSigType(x)->getInterval();
        if (x_i.lo() <= INT32_MIN || x_i.hi() >= INT32_MAX) {
            if (gAllWarning) {
                stringstream error;
                error << "WARNING : float to integer conversion [" << x_i.lo() << ":" << x_i.hi()
                      << "] is outside of integer range in " << ppsig(sig, MAX_ERROR_SIZE);
                gWarningMessages.push_back(error.str());
            }
            return sigIntCast(sigMin(sigReal(INT32_MAX), sigMax(x, sigReal(INT32_MIN))));
        }
    }
    
    // Other cases => identity transformation
    return SignalIdentity::transformation(sig);
}

Tree SignalUIPromotion::transformation(Tree sig)
{
    Tree label, init, min, max, step;
    
    if (isSigVSlider(sig, label, init, min, max, step)
        || isSigHSlider(sig, label, init, min, max, step)
        || isSigNumEntry(sig, label, init, min, max, step)) {
        return sigMax(min, sigMin(max, sig));
    } else {
        // Other cases => identity transformation
        return SignalIdentity::transformation(sig);
    }
}

Tree SignalUIFreezePromotion::transformation(Tree sig)
{
    Tree label, init, min, max, step;

    if (isSigVSlider(sig, label, init, min, max, step)
        || isSigHSlider(sig, label, init, min, max, step)
        || isSigNumEntry(sig, label, init, min, max, step)) {
        /*
         Freeze with the init value.
         TODO:
            - possibly use a [freeze:1] metadata) to only freeze choosen UI controls
            - or even a JSON file with 'freeze' metadata to externally change the setup
         */
        return init;
    } else {
        // Other cases => identity transformation
        return SignalIdentity::transformation(sig);
    }
}

Tree SignalFTZPromotion::selfRec(Tree l)
{
    // Recursion here
    l = self(l);
    
    // Add FTZ on real signals only
    if (getCertifiedSigType(l)->nature() == kReal) {
        if (gGlobal->gFTZMode == 1) {
            return sigSelect2(sigGT(sigAbs(l), sigReal(inummin())), sigReal(0.0), l);
        } else if (gGlobal->gFTZMode == 2) {
            if (gGlobal->gFloatSize == 1) {
                return sigSelect2(sigAND(sigBitCast(l), sigInt(inummax())), sigReal(0.0), l);
            } else if (gGlobal->gFloatSize == 2) {
                return sigSelect2(sigAND(sigBitCast(l), sigInt64(inummax())), sigReal(0.0), l);
            }
        }
    }
    
    return l;
}

// Public API
Tree signalPromote(Tree sig, bool trace)
{
    // Check that the root tree is properly type annotated
    getCertifiedSigType(sig);

    SignalPromotion SP;
    if (trace) SP.trace(true, "Cast");
    return SP.mapself(sig);
}

Tree signalBool2IntPromote(Tree sig)
{
    // Check that the root tree is properly type annotated
    getCertifiedSigType(sig);

    SignalBool2IntPromotion SP;
    return SP.mapself(sig);
}

Tree signalFXPromote(Tree sig)
{
    // Check that the root tree is properly type annotated
    getCertifiedSigType(sig);
    
    SignalFXPromotion SP;
    return SP.mapself(sig);
}

Tree signalTablePromote(Tree sig)
{
    // Check that the root tree is properly type annotated
    getCertifiedSigType(sig);

    SignalTablePromotion SP;
    return SP.mapself(sig);
}

Tree signalIntCastPromote(Tree sig)
{
    // Check that the root tree is properly type annotated
    getCertifiedSigType(sig);
    
    SignalIntCastPromotion SP;
    return SP.mapself(sig);
}

Tree signalUIPromote(Tree sig)
{
    // Check that the root tree is properly type annotated
    getCertifiedSigType(sig);

    SignalUIPromotion SP;
    return SP.mapself(sig);
}

Tree signalUIFreezePromote(Tree sig)
{
    // Check that the root tree is properly type annotated
    getCertifiedSigType(sig);
    
    SignalUIFreezePromotion SP;
    return SP.mapself(sig);
}

Tree signalFTZPromote(Tree sig)
{
    // Check that the root tree is properly type annotated
    getCertifiedSigType(sig);
    
    SignalFTZPromotion SP;
    return SP.mapself(sig);
}
