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

#include "sigPromotion.hh"
#include <stdlib.h>
#include <cstdlib>
#include <map>
#include "global.hh"
#include "ppsig.hh"
#include "property.hh"
#include "signals.hh"
#include "sigtyperules.hh"
#include "tlib.hh"
#include "tree.hh"
#include "xtended.hh"

//-------------------------SignalPromotion-------------------------------
// Adds explicit int or float cast when needed. This is needed prior
// to any optimisations to avoid to scramble int and float expressions
//----------------------------------------------------------------------

Tree SignalPromotion::transformation(Tree sig)
{
    int  i;
    Tree sel, x, y, z;

    if (isSigFixDelay(sig, x, y)) {
        return sigFixDelay(self(x), smartIntCast(getCertifiedSigType(y), self(y)));
    }

    // Binary operations
    // kAdd, kSub, kMul, kDiv, kRem, kLsh, kARsh, kGT, kLT, kGE, kLE, kEQ, kNE, kAND, kOR, kXOR };
    else if (isSigBinOp(sig, &i, x, y)) {
        Type tx = getCertifiedSigType(x);
        Type ty = getCertifiedSigType(y);

        switch (i) {
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
                    return sigBinOp(i, self(x), self(y));
                } else {
                    // float promotion needed
                    return sigBinOp(i, smartFloatCast(tx, self(x)), smartFloatCast(ty, self(y)));
                }

            case kRem:
                if (tx->nature() == kInt && ty->nature() == kInt) {
                    // int arguments => no promotion needed
                    return sigBinOp(i, self(x), self(y));
                } else {
                    // float promotion needed, rem (%) replaced by fmod
                    vector<Tree> lsig = {smartFloatCast(tx, self(x)), smartFloatCast(ty, self(y))};
                    return gGlobal->gFmodPrim->computeSigOutput(lsig);
                }

            case kDiv:
                // the result of a division is always a float
                return sigBinOp(i, smartFloatCast(tx, self(x)), smartFloatCast(ty, self(y)));

            case kAND:
            case kOR:
            case kXOR:
            case kLsh:
            case kARsh:
                // these operations require integers
                return sigBinOp(i, smartIntCast(tx, self(x)), smartIntCast(ty, self(y)));

            default:
                // TODO: no clear rules here
                return sigBinOp(i, self(x), self(y));
        }
    }

    // Select2 and Select3
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
    } else if (isSigSelect3(sig, sel, x, y, z)) {
        Type ts = getCertifiedSigType(sel);
        Type tx = getCertifiedSigType(x);
        Type ty = getCertifiedSigType(y);
        Type tz = getCertifiedSigType(z);

        if ((tx->nature() == ty->nature()) && (tx->nature() == tz->nature())) {
            // same nature => no promotion needed
            return sigSelect3(smartIntCast(ts, self(sel)), self(x), self(y), self(z));
        } else {
            // float promotion needed
            return sigSelect3(smartIntCast(ts, self(sel)), smartFloatCast(tx, self(x)), smartFloatCast(ty, self(y)),
                              smartFloatCast(tz, self(z)));
        }
    }

    // Int and Float Cast
    else if (isSigIntCast(sig, x)) {
        return smartIntCast(getCertifiedSigType(x), self(x));
    } else if (isSigFloatCast(sig, x)) {
        return smartFloatCast(getCertifiedSigType(x), self(x));
    }

    // Other cases => identity transformation
    else {
        return SignalIdentity::transformation(sig);
    }
}

/*
## smartIntCast[S] : adds an intCast(S) only if needed

    smartIntCast[S]     = intCast(S)    when type(S) = float
    smartIntCast[S]     = S             otherwise
*/

Tree SignalPromotion::smartIntCast(Type t, Tree sig)
{
    if (t->nature() == kReal) {
        return sigIntCast(sig);
    } else {
        return sig;
    }
}

/*
## smartFloatCast[S] : adds a floatCast(S) only if needed

    smartFloatCast[S]   = floatCast(S)      when type(S) = int
                        = S                 otherwise

*/
Tree SignalPromotion::smartFloatCast(Type t, Tree sig)
{
    if (t->nature() == kInt) {
        return sigFloatCast(sig);
    } else {
        return sig;
    }
}
