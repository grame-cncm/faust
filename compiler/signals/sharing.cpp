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

/*****************************************************************************
******************************************************************************
                            FAUST SIGNAL COMPILER
                        Y. Orlarey, (c) Grame 2002
------------------------------------------------------------------------------
 History :
 ---------
    2002-02-08 : First version

******************************************************************************
*****************************************************************************/

#include <stdio.h>

#include "sigtyperules.hh"
#include "sharing.hh"

using namespace std;

/*****************************************************************************
******************************************************************************

                                SHARING ANALYSIS

******************************************************************************
*****************************************************************************/

static void setSharingCount(Tree sig, Tree key, int count)
{
    setProperty(sig, key, tree(count));
}

//------------------------------------------------------------------------------
// Create a specific property key for the sharing count of subtrees of t
//------------------------------------------------------------------------------

static void sharingAnnotation(int vctxt, Tree sig, Tree key)
{
    int count = getSharingCount(sig, key);
    if (count > 0) {
        // it is not our first visit
        setSharingCount(sig, key, count + 1);
        
    } else {
        // it is our first visit,
        int v = getCertifiedSigType(sig)->variability();
        
        // check "time sharing" cases
        if (v < vctxt) {
            setSharingCount(sig, key, 2);  // time sharing occurence : slower expression in faster context
        } else {
            setSharingCount(sig, key, 1);  // regular occurence
        }
        
        // Annotate the sub signals
        tvec subsig;
        int  n = getSubSignals(sig, subsig);
        if (n > 0 && !isSigGen(sig)) {
            for (int i = 0; i < n; i++) sharingAnnotation(v, subsig[i], key);
        }
    }
}

//------------------------------------------------------------------------------
// Get the sharing count of sig
//------------------------------------------------------------------------------

int getSharingCount(Tree sig, Tree key)
{
    Tree c;
    if (getProperty(sig, key, c)) {
        return c->node().getInt();
    } else {
        return 0;
    }
}

//------------------------------------------------------------------------------
// Create a specific property key for the sharing count of subtrees of sig
//------------------------------------------------------------------------------

void sharingAnalysis(Tree sig, Tree& key)
{
    key = shprkey(sig);
    if (isList(sig)) {
        while (isList(sig)) {
            sharingAnnotation(kSamp, hd(sig), key);
            sig = tl(sig);
        }
    } else {
        sharingAnnotation(kSamp, sig, key);
    }
}
