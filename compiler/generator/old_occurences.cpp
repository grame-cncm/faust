/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
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

#include <stdlib.h>
#include <iostream>

#include "recursivness.hh"
#include "old_occurences.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"
#include "global.hh"

using namespace std;

/**
 * Extended Variability with recursiveness indication
 */
static int xVariability(int v, int r)
{
	//cerr << "xVariability (" << v << ", " <<  r << ")" << endl;
	//assert (v < 3);				// kKonst=0, kBlock=1, kSamp=2
	//assert(r==0 | v==2);
	if (r>1) r=1;
	return min(3, v + r);
}

//-------------------------------------------------
//	Occurences methods
//-------------------------------------------------

old_Occurences::old_Occurences(int v, int r, Tree xc) : fXVariability(xVariability(v,r))
{
	for (int i=0; i<4; i++) fOccurences[i]=0;
	fMultiOcc = false;
    fMaxDelay = 0;
    fOutDelayOcc = false;
    fExecCondition = xc;
}

old_Occurences* old_Occurences::incOccurences(int v, int r, int d, Tree xc)
{
	int ctxt = xVariability(v,r);
	//assert (ctxt >= fXVariability);
	fOccurences[ctxt] += 1;
	fMultiOcc = fMultiOcc | (ctxt > fXVariability) | (fOccurences[ctxt] > 1);
	if (d == 0) {
		//cerr << "Occurence outside a delay " << endl;
		fOutDelayOcc = true;
	}
	if (d > fMaxDelay) {
		//cerr << "Max delay : " << fMaxDelay << " <- " << d << endl;
		fMaxDelay = d;
	}

    // check if used in different execution conditions
    if (fExecCondition != xc) {
        fMultiOcc = true;
    }
	return this;
}

bool old_Occurences::hasMultiOccurences() const	{ return fMultiOcc; }

bool old_Occurences::hasOutDelayOccurences() const { return fOutDelayOcc; }

int old_Occurences::getMaxDelay() const
{
    return fMaxDelay;
}

Tree old_Occurences::getExecCondition() const
{
    return fExecCondition;
}

//--------------------------------------------------
//	Mark and retrieve occurences of subtrees of root
//--------------------------------------------------

void old_OccMarkup::mark(Tree root)
{
	fRootTree = root;
	fPropKey = tree(unique("OCCURRENCES"));

	if (isList(root)) {
		while (isList(root)) {
			//incOcc(kSamp, 1, hd(root));
            incOcc(gGlobal->nil, kSamp, 0, 0, gGlobal->nil, hd(root));
			root = tl(root);
		}
		//cerr << "END OF LIST IS " << *root << endl;
	} else {
		//incOcc(kSamp, 1, root);
        incOcc(gGlobal->nil, kSamp, 0, 0, gGlobal->nil, root);
	}
}

old_Occurences* old_OccMarkup::retrieve(Tree t)
{
	old_Occurences* p = getOcc(t);
	if (p == 0) {
		//cerr << "No Occurences info attached to : " << *t << endl;
		//exit(1);
	}
	return p;
}

//------------------------------------------------------------------------------
// Increment the occurences of t within context v,r,d,xc and proceed recursively
// xc : exec condition expression
//------------------------------------------------------------------------------

void old_OccMarkup::incOcc(Tree env, int v, int r, int d, Tree xc, Tree t)
{
	// Check if we have already visited this tree
	old_Occurences* occ = getOcc(t);

	if (occ == 0) {
		// 1) We build initial occurence information
		Type	ty = getCertifiedSigType(t);
        int     v0 = ty->variability();
        int     r0 = getRecursivness(t);
        Tree    c0 = fConditions[t];
        occ = new old_Occurences(v0, r0, c0);
		setOcc(t, occ);

		// We mark the subtrees of t
        Tree c, x, y, z;
		if (isSigFixDelay(t,x,y)) {
			Type g2 = getCertifiedSigType(y);
			int d2 = checkDelayInterval(g2);
			faustassert(d2>=0);
            incOcc(env, v0, r0, d2, c0, x);
            incOcc(env, v0, r0, 0, c0, y);
        } else if (isSigPrefix(t,y,x)) {
            incOcc(env, v0, r0, 1, c0, x);
            incOcc(env, v0, r0, 0, c0, y);
        } else if (isSigSelect3(t,c,y,x,z)) {
            // make a special case for select3 implemented with real if
            // because the c expression will be used twice in the C++
            // translation
            incOcc(env, v0, r0, 0, c0, c);
            incOcc(env, v0, r0, 0, c0, c);
            incOcc(env, v0, r0, 0, c0, x);
            incOcc(env, v0, r0, 0, c0, y);
            incOcc(env, v0, r0, 0, c0, z);
        } else {
			vector<Tree> br;
			int n = getSubSignals(t, br);
			if (n>0 && ! isSigGen(t)) {
                for (int i=0; i<n; i++) incOcc(env, v0, r0, 0, c0, br[i]);
			}
		}
	}

    occ->incOccurences(v,r,d,xc);
}

old_Occurences* old_OccMarkup::getOcc(Tree t)
{
	Tree p = t->getProperty(fPropKey);
	if (p) {
		return (old_Occurences*) tree2ptr(p);
	} else {
		return 0;
	}
}

void old_OccMarkup::setOcc(Tree t, old_Occurences* occ)
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
	else return position (tl(env), t, p+1);
}
#endif
