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
 * The long sums of a program in interleaved partial sums (by default ; -nosl keeps the
 * chains). The code generators compute a Sum node as the chain ((t0 + t1) + ...) + tn,
 * the association its interval follows : each addition waits for the previous one, and
 * the C++ compiler, which may not reassociate without -ffast-math, can neither vectorize
 * nor overlap them. sumLanes rewrites a real Sum with at least 8 terms computed at the
 * sample rate : its slower terms first, as the normal form orders them, then the
 * sample-rate terms t0, ..., tm in 4 partial sums added as a balanced tree. The rounding
 * changes : the pass runs on the computation form, after the certified typing
 * (computeForm.hh), and leaves a sum whose value may reach a delay amount, an index or an
 * integer conversion as the certification bounded it (decisionCone.hh). It reads the
 * attributes in the types and leaves its result typed (typedAttributes.hh) ; image, when
 * given, receives every node of L with its rewriting.
 *
 * How the terms are dealt to the partial sums depends on the code generator :
 * - interleaved, Sum(t0, t4, t8, ...), Sum(t1, t5, ...), ... : each step of the four sums
 *   adds four consecutive terms, one vector for the C++ compiler. The generators of the
 *   instruction compiler (cpp and the others) emit the terms in the same order whatever
 *   the sum ;
 * - contiguous, Sum(t0, ..., t(k-1)), Sum(tk, ...), ... : the ocpp scheduler emits each
 *   computation where it is first read, and interleaved sums would emit the terms in the
 *   order t0, t4, t8, ..., t1, ... : isomorphic computations (the bands of a vocoder) are
 *   no longer adjacent, and the C++ compiler no longer vectorizes them.
 */
enum class LaneOrder { kInterleaved, kContiguous };

Tree sumLanes(Tree L, LaneOrder order, std::unordered_map<Tree, Tree>* image = nullptr);
