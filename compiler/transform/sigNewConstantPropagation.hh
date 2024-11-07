/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2023 INRIA
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

#include "signals.hh"

/**
 * @brief Do constant propagation using the interval library. If the interval of an expression is
 * reduced to a single number, then this expression can be replaced by this single number.
 *
 * @param sig
 * @param trace
 * @return Tree
 */
Tree newConstantPropagation(Tree sig, bool trace = false);
