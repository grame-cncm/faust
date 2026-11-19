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

#include <string>
#include <unordered_map>

#include "signals.hh"

/**
 * The guards of the temporaries (by default in cpp, c and ocpp ; -nogt computes every
 * temporary at each sample, as -sts does, and -lazyselect guards the branches of ocpp
 * themselves). The code of select2(s, x, y) is (s) ? y : x, and the C++ compiler
 * computes only the branch it reads. A signal read several times is a temporary, computed
 * at each sample where it is defined, before the expressions that read it : a branch whose
 * value is read twice loses its laziness. The saturated conversion int(x) of a value that
 * may be NaN reads x three times, and the envelopes of dx7 compute six exp at each sample,
 * read only when a modulation sensitivity is not 0.
 *
 * selectGuards gives every signal of L read only within one branch of select2 whose
 * selector is computed once per block (a control, a constant) that selector and that
 * branch : y is read when s is not 0, x when s is 0. A signal read by an expression is read
 * when the expression is : the guard goes down through the operations that compute a value
 * from the values of their operands, and stops at everything else (a delay, a recursion, a
 * table, a foreign function), whose operands are computed at each sample. A signal read in
 * two branches, or by two selectors, or outside a guarded branch, has no guard. The
 * innermost guard is kept : a value read under s and t is computed under t, perhaps when s
 * is 0, never in vain for its value.
 *
 * The value of a guarded temporary is that of its signal when it is read : the code is
 * computed by the same instructions, its rounding is unchanged.
 */
struct SelectGuard {
    Tree selector = nullptr;  ///< computed once per block
    bool second   = false;    ///< read when the selector is not 0 (y), else when it is (x)
};

std::unordered_map<Tree, SelectGuard> selectGuards(Tree L);

/// a function of the libm that costs tens of cycles (exp, log, pow, the trigonometric functions,
/// sqrt, fmod, ...), named as the generators write it : with or without std::, with or without
/// the suffix f or l of its precision
bool isCostlyMathFunction(const std::string& name);
