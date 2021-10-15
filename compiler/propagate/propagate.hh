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

#ifndef _PROPAGATE_
#define _PROPAGATE_

#include <vector>
#include "boxes.hh"

/**
 * makeSigInputList : create a list of input signals
 */

siglist makeSigInputList(int n);

/**
 * boxPropagateSig : path box listOfSignal-> listOfSignal'
 *
 * Propagate a list of signals into a block-diagram. For example to
 * compute the list of outputs of a block-diagram with n inputs, do:
 * Tree lsig = boxPropagateSig(box, makeSigInputList(n));
 */

Tree boxPropagateSig(Tree path, Tree box, const siglist& lsig);

/**
 * Propagate a list of signals into a block diagram. Do memoization.
 *
 * @param slotenv environment associating slots and signals
 * @param path user interface group path
 * @param box the block diagram
 * @param lsig the list of input signals to propagate
 * @return the resulting list of output signals
 */
siglist propagate(Tree slotenv, Tree path, Tree box, const siglist& lsig);

#endif
