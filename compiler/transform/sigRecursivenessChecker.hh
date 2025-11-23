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

#ifndef __SIG_RECURSIVNESS_CHECKER__
#define __SIG_RECURSIVNESS_CHECKER__

#include "signals.hh"

/**
 * @brief Check that all signals in the tree have recursiveness annotations
 *
 * @param siglist The signal list to check
 * @return Tree The same signal list (identity transformation)
 */
Tree checkAllSignalsHaveRecursiveness(Tree siglist);

#endif
