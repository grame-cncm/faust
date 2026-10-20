/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2026 GRAME, Centre National de Creation Musicale
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

#pragma once

#include "tlib.hh"

/**
 * Two trees compared by what they are, not by when they were created : the kind of node
 * first (the numbers before the symbols), a number by its value, a symbol by its name (an
 * operation, a function such as cos or pow, an element of interface), then the arity,
 * then the arguments one by one. A recursive group, whose variable is named after its
 * creation, and a comparison deeper than a few levels fall back to the order of creation.
 *
 * Used only to choose between equivalent forms (the weight of the symmetric mix
 * mix(a, b, 1) = mix(b, a, 1), the orientation of a mix), never to order the terms of a
 * sum : their order is their association, the order the program wrote.
 *
 * Returns a negative number when a comes first, 0 when a and b are the same tree.
 */
int valueCompare(Tree a, Tree b);

inline bool valueLess(Tree a, Tree b)
{
    return valueCompare(a, b) < 0;
}
