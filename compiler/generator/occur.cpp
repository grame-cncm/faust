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
/**
 * @file occurrences.cpp
 * Count the number of occurrences of each subtree of a root tree.
 */

// Construction of graphic representations

#include "occur.hh"
#include <cstdio>

/**
 * Count the number of occurrences of each subtree of root
 */
Occur::Occur(Tree root)
{
    fKey = specificKey(root);
    countOccurrences(root);
    setCount(root, 0);  // root as no occurrences in itself
}

/**
 * Get the number of occurrences of t
 */
int Occur::getCount(Tree t)
{
    Tree c;
    return (getProperty(t, fKey, c)) ? c->node().getInt() : 0;
}

/**
 * Set the number of occurrences of t
 */
void Occur::setCount(Tree t, int c)
{
    setProperty(t, fKey, tree(c));
}

/**
 * Creates a specific property key for occurrences count in root
 */
Tree Occur::specificKey(Tree root)
{
    // one fresh key per analyzed root. unique() alone guarantees the
    // uniqueness ; the root's ADDRESS must never enter the name -- a
    // symbol content derived from the memory layout contaminates every
    // canonical hash downstream (the build-determinism doctrine)
    (void)root;
    return tree(unique("OCCURRENCES COUNT IN"));
}

/**
 * Increment the occurrences count of t and its subtrees
 */
void Occur::countOccurrences(Tree t)
{
    setCount(t, getCount(t) + 1);  // increment t occurrences count
    for (int i = 0; i < t->arity(); i++) {
        countOccurrences(t->branch(i));
    }
}
