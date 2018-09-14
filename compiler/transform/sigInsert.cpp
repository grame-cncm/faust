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

#include "sigInsert.hh"
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

//-------------------------SignalInsert-------------------------------
// Adds explicite int or float cast when needed. This is needed prior
// to any optimisations to avoid to scramble int and float expressions
//----------------------------------------------------------------------

Tree SignalInsert::transformation(Tree sig)
{
    int  i;
    Tree sel, x, y, z;

    Type ttt = getCertifiedSigType(sig);
    assert(ttt);

    Tree r   = SignalIdentity::transformation(sig);
    cerr << "indent " << fIndent  << " type: " << ttt << endl;
    switch (fIndent) {
        case 1 : return sigIntCast(r);
        case 2 : return sigFloatCast(r);
    }

    return r;
}
