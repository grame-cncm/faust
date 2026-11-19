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
 * The divisions of a program by a reciprocal (by default ; -norcp keeps the divisions). A
 * division costs 10 to 20 cycles where a product costs 3 to 4, and the C++ compiler may not
 * replace x / d by x * (1 / d) without -freciprocal-math : the result may differ by one
 * rounding. reciprocals rewrites a real division x / d as x * (1 / d) when the reciprocal
 * is computed less often than the division :
 * - d is slower than the division (a control, a constant of the instance) : 1 / d is
 *   computed at the rate of d ;
 * - d divides at least two signals : 1 / d is computed once, for every division by d (the
 *   oscillators of virtualAnalog, 33 divisions by 9 frequencies).
 * A single division at the rate of its divisor keeps its one rounding.
 *
 * x * (1 / d) is x / d within two roundings. The pass runs on the computation form, after
 * the certified typing (computeForm.hh), and leaves a division whose value may reach a
 * decision as it is : a delay amount, an index, an integer conversion, or a discontinuity
 * (a comparison, floor, ...) (decisionCone.hh). The certified interval of d lies within
 * [2^-100, 2^100] or its opposite : 1 / d is then finite and normal, and x * (1 / d) has the
 * zeros, infinities and NaNs of x / d. It reads the attributes in the types and leaves its
 * result typed (typedAttributes.hh) ; image, when given, receives every node of L with its
 * rewriting.
 */
Tree reciprocals(Tree L, std::unordered_map<Tree, Tree>* image = nullptr);
