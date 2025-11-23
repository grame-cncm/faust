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

#ifndef __SIGSELECT2SIMPLIFICATION__
#define __SIGSELECT2SIMPLIFICATION__

#include "tree.hh"

/**
 * @brief Simplify sigSelect2 based on selector interval analysis
 *
 * This transformation simplifies select2 signals when:
 * - The selector interval is [0,0] → returns first branch
 * - The selector interval doesn't contain 0 → returns second branch
 * - Both branches are identical → returns the branch
 *
 * Precondition: signals must have been typed (typeAnnotation must have been called)
 *
 * @param siglist The list of signals to transform
 * @param trace Enable debug tracing (optional)
 * @return Tree The transformed signal list
 */
Tree simplifySelect2(Tree siglist, bool trace = false);

#endif
