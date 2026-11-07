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
 * The exact weights of a program (option -xw). The normal form folds y - om * y into
 * (1 - om) * y. When om is small, 1 - om rounded to the precision of the code loses most of
 * the digits of om : in single precision, the floats below 1 are 6e-8 apart, and a weight
 * om = 1.6e-7 is off by 12 % once 1 - om is rounded. The error is systematic : a smoother
 * with that pole is that much too fast.
 *
 * exactWeights rewrites a real product whose factor is 1 + w, w a signal, as w * P + P
 * (P the other factors ; -(om * P) + P when w = -om) : om is read exactly. In a sum, the
 * other terms are added to w * P first, then P : (b + w * P) + P, the association of
 * y - (y * om - b), so that P does not absorb the low digits of the small terms. A product
 * that may reach a decision (a delay amount, an integer conversion, an index) is left as
 * it is : its rounding stays the one the certification bounded. The pass runs on the
 * computation form, after the certified typing (computeForm.hh) : it reads the attributes
 * and the certified intervals in the types, and leaves its result typed
 * (typedAttributes.hh) ; image, when given, receives every node of L with its rewriting.
 *
 * Only a small weight is rewritten, |w| < 2^-8 over its interval : 1 + w then loses 8 bits
 * of w at least. A larger weight keeps (1 + w) * y : the rewriting adds an operation on the
 * path of a recursion (2 to 7 % on a Karplus-Strong string bank), for a precision finer than
 * the uncertainty of a weight set by a control. On by default (-noxw) : without it, the
 * normal form, which flattens the sums, folded y + (b - om * y) of si.smoothq into
 * b + (1 - om) * y, which the library writes to avoid (single precision, 60 times the error
 * of master-dev against a double reference).
 */
Tree exactWeights(Tree L, std::unordered_map<Tree, Tree>* image = nullptr);
