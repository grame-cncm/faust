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



/*****************************************************************************
******************************************************************************
							FAUST SIGNAL COMPILER
						Y. Orlarey, (c) Grame 2002
------------------------------------------------------------------------------
Compile a list of FAUST signals into a C++ class .

 History :
 ---------
 	2002-02-08 : First version

******************************************************************************
*****************************************************************************/



#include <stdio.h>

#include "compile_vect.hh"
#include "compile_scal.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"
#include "sigprint.hh"



/*****************************************************************************
******************************************************************************

						   		SHARING ANALYSIS

******************************************************************************
*****************************************************************************/

//------------------------------------------------------------------------------
// Create a specific property key for the sharing count of subtrees of t
//------------------------------------------------------------------------------

int ScalarCompiler::getSharingCount(Tree sig)
{
	//cerr << "getSharingCount of : " << *sig << " = ";
	Tree c;
	if (getProperty(sig, fSharingKey, c)) {
		//cerr << c->node().getInt() << endl;
		return c->node().getInt();
	} else {
		//cerr << 0 << endl;
		return 0;
	}
}

void ScalarCompiler::setSharingCount(Tree sig, int count)
{
	//cerr << "setSharingCount of : " << *sig << " <- " << count << endl;
	setProperty(sig, fSharingKey, tree(count));
}



//------------------------------------------------------------------------------
// Create a specific property key for the sharing count of subtrees of t
//------------------------------------------------------------------------------


void ScalarCompiler::sharingAnalysis(Tree t)
{
	fSharingKey = shprkey(t);
	if (isList(t)) {
		while (isList(t)) {
			sharingAnnotation(kSamp, hd(t));
			t = tl(t);
		}
	} else {
		sharingAnnotation(kSamp, t);
	}
}



//------------------------------------------------------------------------------
// Create a specific property key for the sharing count of subtrees of t
//------------------------------------------------------------------------------
void ScalarCompiler::sharingAnnotation(int vctxt, Tree sig)
{
	Tree	c, x, y, z;

	//cerr << "START sharing annotation of " << *sig << endl;
	int count = getSharingCount(sig);

	if (count > 0) {
		// it is not our first visit
		setSharingCount(sig, count+1);

	} else {
		// it is our first visit,
		int v = getCertifiedSigType(sig)->variability();

		// check "time sharing" cases
		if (v < vctxt) {
			setSharingCount(sig, 2); 	// time sharing occurence : slower expression in faster context
		} else {
			setSharingCount(sig, 1);	// regular occurence
		}

		if (isSigSelect3(sig,c,y,x,z)) {
			// make a special case for select3 implemented with real if
			// because the c expression will be used twice in the C++
			// translation
			sharingAnnotation(v, c);
			sharingAnnotation(v, c);
			sharingAnnotation(v, x);
			sharingAnnotation(v, y);
			sharingAnnotation(v, z);
		} else {
			// Annotate the sub signals
			vector<Tree> subsig;
			int n = getSubSignals(sig, subsig);
			if (n>0 && ! isSigGen(sig)) {
				for (int i=0; i<n; i++) sharingAnnotation(v, subsig[i]);
			}
		}
	}
	//cerr << "END sharing annotation of " << *sig << endl;
}
