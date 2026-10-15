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

#include "signals.hh"

/**
 * The exact weights of a program (by default ; -noxw keeps the products). The normal form
 * folds y - om * y into (1 - om) * y. When om is small, 1 - om rounded to the precision of
 * the code loses most of the digits of om : in single precision, the floats below 1 are
 * 6e-8 apart, and a weight om = 1.6e-7 is off by 12 % once 1 - om is rounded. The error
 * is systematic : a smoother with that pole is that much too fast.
 *
 * exactWeights rewrites a real product whose factor is 1 + w, w a signal, as w * P + P
 * (P the other factors ; -(om * P) + P when w = -om) : om is read exactly. In a sum, the
 * other terms are added to w * P first, then P : (b + w * P) + P, the association of
 * y - (y * om - b), so that P does not absorb the low digits of the small terms. A product
 * that may reach a decision (a delay amount, an integer conversion, an index) is left as
 * it is : P read twice widens its interval. The pass runs before the certified typing,
 * which bounds the rewritten program.
 */
Tree exactWeights(Tree L);
