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
    } else {
        // we have a delay occurrence
        fCountDelay++;
        fMaxDelay = std::max(fMaxDelay, d);
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

std::ostream& operator<<(std::ostream& os, const Occurrences& occ)
{
    os << "Occurrences: {" << std::endl;
    os << "  X Variability: " << occ.fXVariability << std::endl;
    os << "  Occurrences: [";
    for (int i = 0; i < 4; ++i) {
        os << occ.fOccurrences[i];
        if (i < 3) {
            os << ", ";
        }
    }
    os << "]" << std::endl;
    os << "  Multi-Occurrences: " << (occ.fMultiOcc ? "true" : "false") << std::endl;
    os << "  Out Delay Occurrences: " << (occ.fOutDelayOcc ? "true" : "false") << std::endl;
    os << "  Min Delay: " << occ.fMinDelay << std::endl;
    os << "  Max Delay: " << occ.fMaxDelay << std::endl;
    os << "  Delay Count: " << occ.fCountDelay << std::endl;
    os << "  Exec Condition: " << occ.getExecCondition() << std::endl;
    os << "}";

    return os;
}

//----------------------------------------------------
//	Mark and retrieve occurrences of subtrees of root
//----------------------------------------------------

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
    //    std::cerr << "incOcc " << v << ", " << r << ", " << d << " for tree " << *t << std::endl;
    // Check if we have already visited this tree
    Occurrences* occ        = getOcc(t);
    bool         firstVisit = (occ == 0);
    if (firstVisit) {
        // 1) We build initial occurence information
        Type ty = getCertifiedSigType(t);
        int  v0 = ty->variability();
        int  r0 = getRecursivness(t);
        // fConditions may have been initialized empty
        Tree c0 = (fConditions.find(t) == fConditions.end()) ? gGlobal->nil : fConditions[t];
        occ     = new Occurrences(v0, r0, c0);
        setOcc(t, occ);

        // We mark the subtrees of t
        Tree x, y;
        tvec V;
        if (isSigDelay(t, x, y)) {
            Type g2 = getCertifiedSigType(y);
            int  d2 = checkDelayInterval(g2);
            faustassert(d2 >= 0);
            incOcc(env, v0, r0, d2, c0, x);
            incOcc(env, v0, r0, 0, c0, y);
        } else if (isSigPrefix(t, y, x)) {
            incOcc(env, v0, r0, 1, c0, x);
            incOcc(env, v0, r0, 0, c0, y);

        } else if (isSigFIR(t, V)) {
            // a FIR is computed at kSamp
            faustassert(v0 == kSamp);
            faustassert(V.size() >= 2);  // Otherwise not a proper FIR
            for (unsigned int i = 1; i < V.size(); i++) {
                incOcc(env, kSamp, r0, 0, c0, V[i]);  // increment the occurences of the coefficient
                if (!isZero(V[i])) {
                    incOcc(env, kSamp, r0, i - 1, c0,
                           V[0]);  // increment the delayed occurences of the signal}
                }
            }

        } else if (isSigIIR(t, V)) {
            // an IIR is computed at kSamp
            // IIR[_,X,C0,C1,C2,...] -> Y(t) = X(t) + C0*Y(t-0) + C1*Y(t-1) + ...
            //     0 1  2  3  4
            faustassert(v0 == kSamp);
            faustassert(V.size() >= 4);  // IIR[_,X,C0,C1] Otherwise not a proper FIR

            // increment occurences of the input signal
            incOcc(env, kSamp, r0, 0, c0, V[1]);

            for (unsigned int i = 3; i < V.size(); i++) {
                // increment the coefficient i
                incOcc(env, kSamp, r0, 0, c0, V[i]);
                // but also the IIR itself with appropriate delay
                incOcc(env, kSamp, r0, i - 2, c0, t);
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
    //    std::cerr << "Occurences for tree " << *t << " are " << *retrieve(t) << std::endl;
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
    // if (isSigClocked(t)) {
    //     std::cerr << "We have occurrences for sigcloked signal " << t << ": " << *occ << endl;
    // }
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
