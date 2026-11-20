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

#include "signals.hh"

/**
 * The slow prefixes of the sums and products of the computation form, as nodes of their
 * own. The code of Sum(t0, ..., tn) and of Prod(f0, ..., fn) is a chain in the order of the
 * node (emitSum, emitProd, sumLayout.hh) ; a computed prefix of the chain slower than the
 * next operand and than the node is computed at its own rate. slowPrefixes writes each such
 * prefix as a node : Prod(0.5, E0, y@1), the prefix 0.5 * E0 of a block rate and y@1 of the
 * sample rate, becomes Prod(Prod(0.5, E0), y@1). The prefix is then a tree like any other :
 * the products of several recursions that hold it share it, the occurrences count its reads,
 * and the code computes it once at its rate.
 *
 * The chains stay the same, operation for operation : a prefix is cut where the emission
 * stored it, and the emission of the result stores nothing more. A prefix has the nature of
 * its node (the real product of two ints multiplies them as the product did, then stores the
 * result in a real) ; an Int32 prefix has the range of its partial result, as the emission
 * computed it (intOpWraps), so that the wraps of the chain are the same ; a real prefix has
 * an unbounded interval, never read (typedAttributes.hh). The pass runs on the computation
 * form, after the certified typing, and leaves its result typed ; image, when given,
 * receives every node of L with its rewriting.
 */
Tree slowPrefixes(Tree L, std::unordered_map<Tree, Tree>* image = nullptr);
