/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.
 ************************************************************************
 ************************************************************************/

#pragma once

#include <unordered_map>

#include "sigtype.hh"
#include "sigtyperules.hh"

/**
 * The lowerings that change the rounding (shareSums, exactWeights, sumLanes) run on the
 * computation form, after the certified typing, where every signal is annotated : they
 * read the attributes of a signal in its type, and leave their result annotated.
 */

/// The exact attributes of the signals of a typed program, read in their types : the
/// certified types carry the nature and the rate of the light typing (FAUST_CHECK_LIGHT_TYPES)
struct TypedAttributes {
    int nature(Tree t) const { return getCertifiedSigType(t)->nature(); }
    int variability(Tree t) const { return getCertifiedSigType(t)->variability(); }
};

/**
 * Annotates the result of a rewrite of a typed program : a node rebuilt from a source keeps
 * the type of its source (memo : source -> result), the same value but for a rounding ; a
 * node the rewrite built of its own (a number, a sum, a product, a negation, an arithmetic
 * operation) gets the attributes composed from its operands and an unbounded interval,
 * never read : a lowering builds only real arithmetic outside the cone of the decisions, and
 * the code generation reads no interval there. Any other node left without a type is an
 * error.
 */
void completeTypes(Tree result, const std::unordered_map<Tree, Tree>& memo);

/// image := memo o image : a map from the sources of a program to its nodes, after a
/// rewrite of that program (memo : node -> rewritten node)
void composeImage(std::unordered_map<Tree, Tree>& image, const std::unordered_map<Tree, Tree>& memo);
