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
#include <algorithm>
#include <iostream>

#include "global.hh"
#include "occurrences.hh"
#include "recursivness.hh"
#include "sigtyperules.hh"

using namespace std;

/**
 * Extended Variability with recursiveness indication
 */
static int xVariability(int v, int r)
{
    // cerr << "xVariability (" << v << ", " <<  r << ")" << endl;
    // faustassert(v < 3);				// kKonst=0, kBlock=1, kSamp=2
    // faustassert(r==0 | v==2);
    if (r > 1) {
        r = 1;
    }
    return std::min<int>(3, v + r);
}

//-------------------------------------------------
//	Occurences methods
//-------------------------------------------------

int Occurrences::getOccurrence(int variability) const
{
    return fOccurrences[variability];
}

Occurrences::Occurrences(int v, int r, Tree xc) : fXVariability(xVariability(v, r))
{
    for (int i = 0; i < 4; i++) {
        fOccurrences[i] = 0;
    }
    fMultiOcc      = false;
    fOutDelayOcc   = false;
    fMinDelay      = 0;
    fMaxDelay      = 0;
    fCountDelay    = 0;  // number of times this sig occurs delay
    fExecCondition = xc;
}

Occurrences* Occurrences::incOccurrences(int v, int r, int d, Tree xc)
{
    int ctxt = xVariability(v, r);
    // assert (ctxt >= fXVariability);
    fOccurrences[ctxt] += 1;
    fMultiOcc = fMultiOcc | (ctxt > fXVariability) | (fOccurrences[ctxt] > 1);
    if (d == 0) {
        // cerr << "Occurence outside a delay " << endl;
        fOutDelayOcc = true;
    }
    if (d > fMaxDelay) {
        // cerr << "Max delay : " << fMaxDelay << " <- " << d << endl;
        fMaxDelay = d;
        fCountDelay++;
    }

    // check if used in different execution conditions
    if (fExecCondition != xc) {
        fMultiOcc = true;
    }

    return this;
}

bool Occurrences::hasMultiOccurrences() const
{
    return fMultiOcc;
}

bool Occurrences::hasOutDelayOccurrences() const
{
    return fOutDelayOcc;
}

int Occurrences::getMaxDelay() const
{
    return fMaxDelay;
}

int Occurrences::getDelayCount() const
{
    return fCountDelay;
}

Tree Occurrences::getExecCondition() const
{
    return fExecCondition;
}

//----------------------------------------------------
//	Mark and retrieve occurrences of subtrees of root
//----------------------------------------------------


// an all-ones CONTIGUOUS FIR from tap 0 with at least 4 taps : a moving
// sum, eligible for the O(1) sliding emission (y = y' + x - x@T)
static bool isSlidingSumFIR(const tvec& coef, int& T)
{
    if (coef.size() < 5) {
        return false;  // fewer than 4 taps
    }
    for (size_t i = 1; i < coef.size(); i++) {
        if (!isOne(coef[i])) {
            return false;
        }
    }
    T = int(coef.size()) - 1;
    return true;
}

void OccMarkup::mark(Tree root)
{
    fRootTree = root;
    fPropKey  = tree(unique("OCCURRENCES"));

    if (isList(root)) {
        while (isList(root)) {
            // incOcc(kSamp, 1, hd(root));
            incOcc(gGlobal->nil, kSamp, 0, 0, gGlobal->nil, hd(root));
            root = tl(root);
        }
        // cerr << "END OF LIST IS " << *root << endl;
    } else {
        // incOcc(kSamp, 1, root);
        incOcc(gGlobal->nil, kSamp, 0, 0, gGlobal->nil, root);
    }
}

Occurrences* OccMarkup::retrieve(Tree t)
{
    return getOcc(t);
}

//------------------------------------------------------------------------------
// Increment the occurrences of t within context v,r,d,xc and proceed recursively
// xc : exec condition expression
//------------------------------------------------------------------------------

void OccMarkup::incOcc(Tree env, int v, int r, int d, Tree xc, Tree t)
{
    // Check if we have already visited this tree
    Occurrences* occ        = getOcc(t);
    bool         firstVisit = (occ == 0);
    if (firstVisit) {
        // 1) We build initial occurence information
        int v0 = sigVariability(t);
        int r0 = getRecursivness(t);
        // fConditions may have been initialized empty
        Tree c0 = (fConditions.find(t) == fConditions.end()) ? gGlobal->nil : fConditions[t];
        occ     = new Occurrences(v0, r0, c0);
        setOcc(t, occ);

        // We mark the subtrees of t
        Tree x, y;
        if (isSigDelay(t, x, y)) {
            Type g2 = getCertifiedSigType(y);
            int  d2 = checkDelayInterval(g2);
            faustassert(d2 >= 0);
            incOcc(env, v0, r0, d2, c0, x);
            incOcc(env, v0, r0, 0, c0, y);
        } else if (isSigPrefix(t, y, x)) {
            incOcc(env, v0, r0, 1, c0, x);
            incOcc(env, v0, r0, 0, c0, y);
        } else if (tvec V; isSigIIR(t, V)) {
            // IIR[nil,X,C0=0,C1,...] : y = X + sum Ci*y@i -- the node reads
            // ITSELF at delays i-2 (that sizes its own delay line), the
            // input and the coefficients at delay 0
            faustassert(V.size() >= 4);
            incOcc(env, v0, r0, 0, c0, V[1]);
            // the direct form reads ITSELF delayed ; a kernel ELECTED
            // transposed (property set by the pre-markup scan, same judge
            // as the emission) replaces those reads by its state chain
            bool transposed = (t->getProperty(tree(symbol("SIGIIRTRANSPOSED"))) != nullptr);
            for (unsigned int k = 3; k < V.size(); k++) {
                incOcc(env, v0, r0, 0, c0, V[k]);
                if (!isZero(V[k]) && !transposed) {
                    incOcc(env, v0, r0, int(k) - 2, c0, t);
                }
            }
        } else if (tvec V; isSigFIR(t, V)) {
            // sliding-sum candidates read the source one slot FURTHER
            // (x@T) than the widest tap : declare it here so the delay
            // line covers the O(1) emission (see generateFIR)
            {
                int T;
                if (isSlidingSumFIR(V, T)) {
                    incOcc(env, v0, r0, T, c0, V[0]);
                }
            }
            // FIR[X,C0,C1,...] : the source X is read at delays 0..n-1 (one
            // per non-zero coefficient) -- this is what sizes its delay
            // line ; the coefficients are ordinary immediate reads
            faustassert(V.size() >= 2);
            for (unsigned int k = 1; k < V.size(); k++) {
                incOcc(env, v0, r0, 0, c0, V[k]);
                if (!isZero(V[k])) {
                    incOcc(env, v0, r0, int(k) - 1, c0, V[0]);
                }
            }
            if (!getOcc(V[0])) {
                // degenerated FIR[X,0,0,...] : X still needs a mark
                incOcc(env, v0, r0, 0, c0, V[0]);
            }
        } else {
            tvec br;
            int  n = getSubSignals(t, br);
            if (n > 0 && !isSigGen(t)) {
                for (int i = 0; i < n; i++) {
                    incOcc(env, v0, r0, 0, c0, br[i]);
                }
            }
        }
    }

    occ->incOccurrences(v, r, d, xc);

    if (!firstVisit) {
        // Special case for -1*y. Because the sharing of -1*y will be ignored
        // at code generation, we need to propagate its sharing to y
        int  opnum;
        Tree x, y;
        if (isSigBinOp(t, &opnum, x, y) && (opnum == kMul) && isMinusOne(x)) {
            incOcc(env, v, r, d, xc, y);
        }
    }
}

Occurrences* OccMarkup::getOcc(Tree t)
{
    Tree p = t->getProperty(fPropKey);
    if (p) {
        return (Occurrences*)tree2ptr(p);
    } else {
        return 0;
    }
}

void OccMarkup::setOcc(Tree t, Occurrences* occ)
{
    t->setProperty(fPropKey, tree(occ));
}

#if 0

/**
 * return the position of a signal in the current recursive environment
 * @param env the current recursive environment of the signal
 * @param t signal we want to know the position
 * @return the position in the recursive environment
 */
static int position(Tree env, Tree t, int p)
{
	if (isNil(env)) return 0;	// was not in the environment
	if (hd(env) == t) return p;
	else return position(tl(env), t, p+1);
}
#endif
