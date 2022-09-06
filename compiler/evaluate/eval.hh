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

#ifndef __EVALBOXES__
#define __EVALBOXES__

/**
 * \file eval.hh
 *
 * Interface of the block diagram evaluator.
 *
 * A strict lambda-calculus evaluator for block diagram expressions.
 *
 **/

#include "boxes.hh"

/**
 * Eval the definition of 'process'.
 *
 * Eval the definition of 'process' in the environment passed as argument
 * @param eqlist the global environment (a list of definitions)
 * @return the 'process' block diagram in normal form
 **/
Tree evalprocess(Tree eqlist);

/* Eval a documentation expression. */
Tree evaldocexpr(Tree docexpr, Tree eqlist);

/* Numeric simplification of pattern arguments */
Tree simplifyPattern(Tree pattern);

#endif
