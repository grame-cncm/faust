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

#include "treeTransform.hh"
#include <stdlib.h>
#include <cstdlib>
#include "Text.hh"
#include "ppsig.hh"

//------------------------------------------------------------------------------
// TreeTransform: Recursive transformation of a Tree with memoization
//------------------------------------------------------------------------------
// This is an abstract class. Derived class just have to implement the
// `transformation(t)` method. The `transformation(t)` method
// should not call itself recursively directly, but exclusively via `self(t)`
// (or `mapself(lt)` for a list).
//------------------------------------------------------------------------------

Tree TreeTransform::self(Tree t)
{
    if (fTrace) traceEnter(t);
    fIndent++;
    Tree r;
    if (!fResult.get(t, r)) {
        r = transformation(t);
        fResult.set(t, r);
    }
    fIndent--;
    if (fTrace) traceExit(t, r);
    return r;
}

void TreeTransform::traceEnter(Tree t)
{
    tab(fIndent, cerr);
    cerr << fMessage << ": " << *t << endl;
}

void TreeTransform::traceExit(Tree t, Tree r)
{
    tab(fIndent, cerr);
    cerr << fMessage << ": " << *t << " ==> " << *r << endl;
}

Tree TreeTransform::mapself(Tree lt)
{
    if (isNil(lt)) {
        return lt;
    } else {
        return cons(self(hd(lt)), mapself(tl(lt)));
    }
}
