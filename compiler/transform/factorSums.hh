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
 * The sums of products factored (by default ; -noshs keeps them). The normal form factors
 * a common divisor out of a sum only when the divisor remains in no quotient
 * (aterm::greatestDivisor) : in y + 3 * y^2 = y * (1 + 3 * y), y would be read twice and its
 * exact power lost, for the interval. A polynomial then stays expanded : the second divided
 * difference u1^2 + u2^2 + u3^2 + u1 * u2 + u1 * u3 + u2 * u3 - 2 of os.sawN(4) in single
 * precision, 3 squares and 3 products, where u1 * (u1 + u2 + u3) + u2 * (u2 + u3) + u3^2 - 2
 * holds 3 products.
 *
 * In a real sum at the sample rate, the terms are monomials : a number, times factors, a
 * square pow(x, 2) being the factor x twice. The factor at the sample rate that the most
 * terms hold, saving one product at least, is factored, f * (the terms divided by f) + the
 * rest ; the inner sum and the rest are factored likewise (greedy, as aterm::factorize).
 * A factor held by k terms saves k - 1 products, less one per term that is f alone ; ties
 * go to the factor met first. The numbers stay in their terms ; an inner sum whose terms are
 * all negated is read negated. A slower factor is left in place : the generators compute
 * the slow factors of a product at their rate, and factoring one out would add a product
 * at the sample rate. A term, a product or a square that another signal reads too stays
 * whole : it is computed once for all its readers, and dividing it would compute its
 * factors again (moogVCF : c1 * x and c2 * x^2 shared by three sums).
 *
 * The rounding changes. The pass runs on the computation form, after the certified typing
 * (computeForm.hh) : a sum whose value may reach a delay amount, an index or an integer
 * conversion (decisionCone.hh) is left as the certification bounded it. It reads the
 * attributes in the types, and leaves its result typed (typedAttributes.hh) ; image, when
 * given, receives every node of L with its rewriting.
 */
Tree factorSums(Tree L, std::unordered_map<Tree, Tree>* image = nullptr);
