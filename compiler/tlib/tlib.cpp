/************************************************************************
 ************************************************************************
    TLIB : tree library
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
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

#include "tlib.hh"

#include "garbageable.hh"

// Internal reset hooks : the library owns a few lazily interned symbols and
// key trees (the list cons/nil, the recursion symbols). They die with the
// session like every other tree, so the lazily-filled caches that hold them
// must be reset whenever the tree population is reset.
void tlibResetListInternals();  // defined in list.cpp
void tlibResetRecInternals();   // defined in recursive-tree.cpp

namespace tlib {

static void resetInternals()
{
    CTree::init();
    Symbol::init();
    tlibResetListInternals();
    tlibResetRecInternals();
}

void init()
{
    resetInternals();
}

void cleanup()
{
    // Delete every Garbageable created so far (trees, symbols, property
    // tables...), then reset the tables and internal caches so the library is
    // immediately ready for a new session.
    Garbageable::cleanup();
    resetInternals();
}

void setHashLoadFactor(double f)
{
    CTree::setHashLoadFactor(f);
    Symbol::setHashLoadFactor(f);
}

}  // namespace tlib
