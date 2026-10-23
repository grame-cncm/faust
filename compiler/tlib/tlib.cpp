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
#include "tlib-error.hh"

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

// Armed by init(), disarmed by cleanup(). A second init() over a live
// population would restart the serial counter and re-intern the lazy
// internals : addresses and serials of still-alive trees would be reissued
// for different terms -- the corruption is silent, so the guard is loud.
static bool gInitialized = false;

void init()
{
    TLIB_ASSERT(!gInitialized);
    // A tree or a symbol made before the first init() (from a static initializer) would keep
    // its serial and leave the tables : init() would issue its serial again to another tree,
    // and its name to another symbol, mixing them up in silence. A property declared at
    // namespace scope makes its key on first use, so it makes none then. (After cleanup(),
    // the trees of the session are gone, and the symbols left are tlib's own internals.)
    if (CTree::session() == 0 && (CTree::serialCounter() != 0 || Symbol::count() != 0)) {
        tlib::error("ERROR : a tree or a symbol was made before tlib::init() (" +
                    std::to_string(CTree::serialCounter()) + " trees, " + std::to_string(Symbol::count()) +
                    " symbols)\n");
    }
    gInitialized = true;
    // After cleanup(), the tables are already reset and tlib's internals interned again : a
    // second reset would drop them from the tables without deleting them.
    if (CTree::session() == 0) {
        resetInternals();
    }
}

void cleanup()
{
    // Delete every Garbageable created so far (trees, symbols, property
    // tables...), then reset the tables and internal caches so the library is
    // immediately ready for a new session.
    Garbageable::cleanup();
    resetInternals();
    gInitialized = false;
}

void setHashLoadFactor(double f)
{
    CTree::setHashLoadFactor(f);
    Symbol::setHashLoadFactor(f);
}

}  // namespace tlib
