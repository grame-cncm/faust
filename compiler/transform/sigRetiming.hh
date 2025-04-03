/************************************************************************
 ************************************************************************
    FAUST compiler / Retiming transformation
    Copyright (C) 2024-2024 INRIA
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

#include <stdlib.h>
#include <cstdlib>

#include "signals.hh"

/**
 * @brief add registers to a list of signal to balance timing
 *
 * @param lsig a list of signals without registers
 * @param trace optional trace flag
 * @return Tree a list of signals with registers
 */
Tree sigRetiming(Tree lsig, bool trace = false);
