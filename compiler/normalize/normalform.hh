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

#ifndef _SIMPLIFY_TO_NF_
#define _SIMPLIFY_TO_NF_

#include "tree.hh"

/**
 *  Simplify a signal to its normal form, where:
 *  - all possible optimisations, simplications, and compile time computations have been done
 *  - the mathematical functions (primitives and binary functions), delay, select2, soundfile primitive...
 *  are properly typed (arguments and result)
 *  - signal cast are properly done when needed
 *
 * @param sig - the signal to be processed
 *
 * @return the signal in normal form.
 */
LIBFAUST_API Tree simplifyToNormalForm(Tree sig);

/**
 *  Simplify a signal list to its normal form, where:
 *  - all possible optimisations, simplications, and compile time computations have been done
 *  - the mathematical functions (primitives and binary functions), delay, select2, soundfile primitive...
 *  are properly typed (arguments and result)
 *  - signal cast are properly done when needed
 *
 * @param siglist - the signal vector to be processed
 *
 * @return the signal list in normal form.
 */
LIBFAUST_API tvec simplifyToNormalForm2(tvec siglist);

/**
 * Print the signal.
 *
 * @param sig - the signal to be printed
 * @param shared - whether the identical sub signals are printed as identifiers
 * @param max_size - the maximum number of characters to be printed (possibly needed for big expressions in non shared mode)
 *
 * @return the printed signal as a string
 */
LIBFAUST_API std::string printSignal(Tree sig, bool shared, int max_size);

/**
 * Print the box.
 *
 * @param box - the box to be printed
 * @param shared - whether the identical sub boxes are printed as identifiers
 * @param max_size - the maximum number of characters to be printed (possibly needed for big expressions in non shared mode)
 *
 * @return the printed box as a string
 */
LIBFAUST_API std::string printBox(Tree box, bool shared, int max_size);

#endif
