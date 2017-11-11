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

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <set>

#include "recursivness.hh"
#include "property.hh"
#include "exception.hh"
#include "global.hh"
#include "signals.hh"
#include "ppsig.hh"

using namespace std;

/**
 * @file recursivness.cpp
 * Annotate a signal expression with recursivness information. Recursiveness
 * indicates the amount of recursive dependencies of a signal. A closed signal
 * has a recursivness of 0 because is has no recursive dependencies. This means
 * that the succesive samples of this signal can be computed in parallel.
 * In a signal of type \x.(...F(x)...), F(x) has a recursivness of 1. In a
 * signal of type \x.(... \y.(...F(x)...G(y)...)...) F(x) has a recursivness of 2
 * while G(y) has a recursivness of 1.
 */

//--------------------------------------------------------------------------
static int annotate(Tree env, Tree sig);
static int position (Tree env, Tree t, int p = 1);
//--------------------------------------------------------------------------

/**
 * Annotate a signal with recursivness. Should be used before
 * calling getRecursivness
 * @param sig signal to annotate
 */
void recursivnessAnnotation(Tree sig)
{
	annotate(gGlobal->nil, sig);
}

/**
 * Return the recursivness of a previously
 * annotated signal. An error is generated
 * if the signal has no recursivness property
 * @param sig signal
 * @return recursivness of the signal
 */
int getRecursivness(Tree sig)
{
	Tree tr;
	if (!getProperty(sig, gGlobal->RECURSIVNESS, tr)) {
        stringstream error;
        error << "ERROR in getRecursivness of " << *sig << endl;
        throw faustexception(error.str());
	}
	return tree2int(tr);
}

//-------------------------------------- IMPLEMENTATION ------------------------------------
/**
 * Annotate a signal with recursivness
 * @param env the current environment
 * @param sig signal to annotate
 * @return recursivness of the signal
 */
static int annotate(Tree env, Tree sig)
{
	Tree tr, var, body;

	if (getProperty(sig, gGlobal->RECURSIVNESS, tr)) {
		return tree2int(tr);	// already annotated
	} else if (isRec(sig, var, body)) {
		int p = position(env, sig);
		if (p > 0) {
			return p;	// we are inside \x.(...)
		} else {
			int r = annotate(cons(sig, env), body) - 1;
			if (r<0) r = 0;
			setProperty(sig, gGlobal->RECURSIVNESS, tree(r));
			return r;
		}
	} else {
		int rmax = 0;
		vector<Tree> v; getSubSignals(sig, v);
		for (unsigned int i = 0; i < v.size(); i++) {
			int r = annotate(env, v[i]);
			if (r>rmax) rmax = r;
		}
		setProperty(sig, gGlobal->RECURSIVNESS, tree(rmax));
		return rmax;
	}
}



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

//-----------------------------------list recursive symbols-----------------------

/**
 * return the set of recursive symbols appearing in a signal.
 * @param sig the signal to analyze
 * @return the set of symbols
 */

Tree symlistVisit(Tree sig, set<Tree>& visited)
{
    Tree S;
    
    if (gGlobal->gSymListProp->get(sig, S)) {
        return S;
    } else if (visited.count(sig) > 0) {
        return gGlobal->nil;
    } else {
        visited.insert(sig);
        Tree id, body;
        if (isRec(sig, id, body)) {
            Tree U = singleton(sig);
            for (int i = 0; i < len(body); i++) {
                U = setUnion(U, symlistVisit(nth(body,i), visited));
            }
            return U;
        } else {
            vector<Tree> subsigs;
            int n = getSubSignals(sig, subsigs, true); // il faut visiter aussi les tables
            Tree U = gGlobal->nil;
            for (int i = 0; i < n; i++) {
                U = setUnion(U, symlistVisit(subsigs[i], visited));
            }
            return U;
        }
    }
}

Tree symlist(Tree sig)
{
    Tree S;
    
    if (!gGlobal->gSymListProp->get(sig, S)) {
        set<Tree> visited;
        S = symlistVisit(sig, visited);
        gGlobal->gSymListProp->set(sig, S);
    }
    //cerr << "SYMLIST " << *S << " OF " << ppsig(sig) << endl;
    return S;
}
