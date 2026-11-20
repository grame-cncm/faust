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
 * The compound operations of the computation form written as the operations their code
 * computes, so that the computation form is what the emission translates : every value
 * the code computes is a node, shared, counted by the occurrences, stored at its rate.
 *
 *  - mix(c, a, b), in its form (mixForm.hh) : a + c * (b - a), b + (1 - c) * (a - b), or
 *    b + t * (a - b) when c is written 1 - t ;
 *  - phase(x, p) : (x % p) / p, fmod(x, p) / p for reals ; for ints, float(x % p) / float(p),
 *    or float(x % p) * (1 / float(p)) when the node says so ;
 *  - frac(x) = x - floor(x) (its approximated floor under -mapp), cfrac(x) = x - rint(x),
 *    tpt(x) = x / (x + 1).
 *
 * A subterm the program already holds (floor(x), rint(x), x % p, fmod(x, p), x + 1 :
 * DefinitionIndex) is read, as the emission read it ; the others are built. The operations
 * are those of the emission, in its order : the values are the same, bit for bit. A node
 * built has the nature of the operation, the rate of its operands and an unbounded
 * interval, never read (typedAttributes.hh) ; the node rewritten keeps the type of its
 * source. Not under -fx, whose fixed-point types are read in the intervals ; image, when
 * given, receives every node of L with its rewriting.
 */
Tree lowerComposites(Tree L, std::unordered_map<Tree, Tree>* image = nullptr);
