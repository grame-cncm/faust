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
 * The shared sums of a program (by default ; -noshs keeps the dense rows). The normal
 * form writes a linear combination of signals as one dense row : a Sum of terms c * x,
 * or a FIR of a signal over its taps. The rows of a Hadamard matrix or of a discrete Fourier
 * transform then repeat the sub-sums that butterflies would share. shareSums rewrites the real rows
 * :
 *
 *  1. in each row, the terms whose coefficients have the same magnitude are factored :
 *     c * a - c * b + c * d becomes c * (a - b + d), and c * a - c * b of two terms
 *     c * (a - b) ; the magnitudes the program cannot tell apart count as one (equal once
 *     rounded to a float in single precision, within a relative 2^-46 in double :
 *     constants folded along different paths differ by a few ulps) ;
 *  2. a product c * S that several rows hold, up to its sign, is one tree ;
 *  3. in every sum of coefficients +-1 that remains, the signed pair of terms the most
 *     sums hold becomes a sum of its own, until no pair is held twice ;
 *  4. in a real product at the sample rate that holds a slower factor, the number of a
 *     factor k * S or of a gain kernel FIR[x, k] joins the product, its factors ordered by
 *     rate : the generators compute k times the slower factors at their rate.
 *
 * The result computes the same linear combination with at most as many operations, in
 * another association : the rounding changes. The pass runs on the computation form, after
 * the certified typing (computeForm.hh) : a sum or a product whose value may reach a delay
 * amount, an index or an integer conversion (decisionCone.hh) is left as the certification
 * bounded it. It reads the attributes in the types, and leaves its result typed
 * (typedAttributes.hh) ; image, when given, receives every node of L with its rewriting.
 * Shared trees are emitted once by the code generators.
 */
Tree shareSums(Tree L, std::unordered_map<Tree, Tree>* image = nullptr);
