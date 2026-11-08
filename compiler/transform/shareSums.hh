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
 *  0. two atoms u, v that several rows hold in one ratio rho = c_v / c_u other than +-1
 *     (a sub-sum read at several scales, distributed by the normal form in each reading :
 *     the phase (p + s * 2^-24) * 2^-30 of an oscillator read at four scales) become one
 *     atom P = u + rho * v, each row holding c_u * P ; P is written on the atom of
 *     coefficient +-1 in the most rows. A term whose magnitude another term of its row
 *     holds is left to the factoring by magnitude and to the pairs of coefficients +-1 ;
 *  1. in each row, the terms whose coefficients have the same magnitude are factored :
 *     c * a - c * b + c * d becomes c * (a - b + d), and c * a - c * b of two terms
 *     c * (a - b) ; the magnitudes the program cannot tell apart count as one (equal once
 *     rounded to a float in single precision, within a relative 2^-46 in double :
 *     constants folded along different paths differ by a few ulps) ;
 *  2. a product c * S that several rows hold, up to its sign, is one tree ;
 *  3. in every sum of coefficients +-1 that remains, the signed pair of terms the most
 *     sums hold becomes a sum of its own, until no pair is held twice ; a difference
 *     u - v is built v - u, its exact opposite, when that leaves fewer negations in the
 *     sums that read it (a sum whose terms are all negated is a negation) ;
 *  4. in a real product at the sample rate that holds a slower factor, the number of a
 *     factor k * S or of a gain kernel FIR[x, k] joins the product, its factors ordered by
 *     rate : the generators compute k times the slower factors at their rate ;
 *  5. in a real product, a negated factor (neg(x), FIR(x; -1, ..., -1), a sum of negations)
 *     is replaced by its opposite and the product negated, up to the sum that reads it and
 *     subtracts it : c * (-x0 - x1) + t becomes t - c * (x0 + x1), the same bit for bit.
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
