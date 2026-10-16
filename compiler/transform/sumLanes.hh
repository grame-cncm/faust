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
 * The long sums of a program in interleaved partial sums (by default ; -nosl keeps the
 * chains). The code generators compute a Sum node as the chain ((t0 + t1) + ...) + tn,
 * the association its interval follows : each addition waits for the previous one, and
 * the C++ compiler, which may not reassociate without -ffast-math, can neither vectorize
 * nor overlap them. sumLanes rewrites a real Sum with at least 8 terms computed at the
 * sample rate : its slower terms first, as the normal form orders them, then the
 * sample-rate terms t0, ..., tm in 4 partial sums Sum(t0, t4, t8, ...), Sum(t1, t5, ...),
 * Sum(t2, ...), Sum(t3, ...), added as a balanced tree. The rounding changes : the pass
 * runs before the certified typing, which bounds the rewritten program itself.
 */
Tree sumLanes(Tree L);
