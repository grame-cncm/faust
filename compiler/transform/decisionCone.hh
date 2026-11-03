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

#include <unordered_set>

#include "signals.hh"

/**
 * The cone of the decisions : every signal whose value may reach a decision, directly or
 * through a recursion. A decision is always the amount of a delay, the operand of an
 * integer conversion, the index of a table or of a soundfile.
 *
 * With discontinuities, a decision is also the operand of a comparison, the selector of a
 * select2, and the operand of a function that jumps : floor, ceil, rint, round, fmod,
 * remainder, the Frac, Cfrac and Phase nodes, the input of a Bpf. There, a rounding that
 * moves a value by an ulp may move the result by a step : a writing chosen for its cost
 * must not change a rounding that such a value depends on.
 */
std::unordered_set<Tree> decisionCone(Tree L, bool discontinuities);
