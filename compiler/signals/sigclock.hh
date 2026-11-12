/************************************************************************
 ************************************************************************
    FAUST signal library
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#pragma once

#include "sigs-export.hh"
#include "tlib.hh"

/**
 * The clock of a signal : the instants at which it is computed (the clock calculus is
 * specified in clocks.md, repository faust-ondemand-spec).
 *
 * STEP 0 : the natural clocks only. A constant has no clock of its own and takes the one
 * of the computation that uses it ; the block clock is the set of the block starts ; the
 * sample clock is the set of the samples. They form a chain, kClkConst < kClkBlock <
 * kClkSample, encoded so that the bitwise OR is the maximum. No program has a derived
 * clock yet (ondemand, upsampling, downsampling) : the clock is computed beside the
 * variability, changes no generated code, and is checked against it.
 */
enum SigClock { kClkConst = 0, kClkBlock = 1, kClkSample = 3 };

/// The variability a clock projects on : constant, block or sample.
SIGS_API int clockVariability(int clock);

/**
 * The clocks of one root, solved once and queryable per signal, bottom-up : the clock of
 * a computation without memory is the densest of the clocks of its operands, the clock
 * of a computation that counts time is the one of its lexical context.
 */
class SIGS_API ClockSolver {
    struct Impl;
    Impl* fImpl;

   public:
    explicit ClockSolver(Tree root);
    ~ClockSolver();
    ClockSolver(const ClockSolver&)            = delete;
    ClockSolver& operator=(const ClockSolver&) = delete;

    int clock(Tree sig) const;
};

/**
 * The concordance of the clocks with the variability, under FAUST_CHECK_CLOCKS : every
 * typed signal reachable from L must have a clock that projects on its variability.
 * Prints one line, `clocks : <n> signals, <d> differ`, and the first divergences.
 */
SIGS_API void checkClockConcordance(Tree L);
