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

#include <cstdlib>
#include <map>

#include "Text.hh"
#include "global.hh"
#include "ppsig.hh"
#include "property.hh"
#include "signals.hh"
#include "sigtyperules.hh"
#include "tlib.hh"
#include "tree.hh"
#include "treeTraversal.hh"

//------------------------------------------------------------------------------
// TreeTraversal: Bottom up traversal
//------------------------------------------------------------------------------
// This is an abstract class. Derived class just have to implement the
// `transformation(t)` method. The `transformation(t)` method
// should not call itself recursively directly, but exclusively via `self(t)`
// (or `mapself(lt)` for a list).
//------------------------------------------------------------------------------

void TreeTraversal::self(Tree t)
{
    if (fTraceFlag) traceEnter(t);
    fIndent++;

    if (!fVisited.count(t)) {
        fVisited.insert(t);
        visit(t);
    }
    fIndent--;
    if (fTraceFlag) traceExit(t);
}

void TreeTraversal::traceEnter(Tree t)
{
    tab(fIndent, cerr);
    cerr << fMessage << " Enter: " << *t << endl;
}

void TreeTraversal::traceExit(Tree t)
{
    tab(fIndent, cerr);
    cerr << fMessage << "  Exit: " << *t << endl;
}

void TreeTraversal::mapself(Tree lt)
{
    if (!isNil(lt)) {
        self(hd(lt));
        mapself(tl(lt));
    }
}
