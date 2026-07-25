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

#include <string>
#include <vector>

#include "interval_def.hh"
#include "sigs-export.hh"
#include "tlib.hh"

/**
 * The HORIZON analysis (see HORIZON.md in the migration repo).
 *
 * The validity horizon T* of a Faust program is the duration during which its
 * computations behave like exact mathematics. Two mechanisms bound it: int32 WRAP (a
 * unit counter overflows after 2^31 samples, ~12.4h at 48kHz) and FLOAT ABSORPTION (a
 * single-precision accumulator stops incrementing once the ulp of its value exceeds its
 * increment: at 2^24 counts, ~5.8 MINUTES at 48kHz -- the classic frozen-phasor bug).
 *
 * The analysis runs the fixpoint engine over AFFINE-IN-TIME bounds
 * [a0 + a1*t, b0 + b1*t]: linear operations preserve the form, a delay shifts the
 * intercept by -n*rate (which is what makes an accumulator STATIONARY instead of
 * endlessly growing), nonlinear operations collapse to the horizon interval. The rate
 * of an accumulator then dates its failure modes analytically.
 */

/// One dated finding: a recursive signal that stops behaving like exact math.
struct HorizonEvent {
    std::string signal;      ///< printed form of the culprit projection
    double      rate;        ///< growth in value units per sample (of the faster bound)
    double      wrapAt;      ///< samples until int32 wrap (int signals; inf if never)
    double      absorb32At;  ///< samples until float32 absorption (float; inf if never)
    double      absorb53At;  ///< samples until double absorption
};

/// The report: every rate-carrying recursive signal, dated; T* = the earliest event.
/// Two readings of the same program: WORST CASE (parameters anywhere in their declared
/// ranges) and NOMINAL (parameters at their default values, buttons released). The gap
/// between the two says the horizon is parameter-driven -- some knob's excursion breaks
/// a contraction -- which is itself a user diagnostic.
struct HorizonReport {
    std::vector<HorizonEvent> events;             ///< worst-case events
    double horizonSamples        = -1;  ///< worst-case T* (single-precision reading)
    double horizonDefaultSamples = -1;  ///< nominal T* (parameters at defaults)
    int    defaultEventCount     = 0;   ///< dated accumulators in the nominal reading
};

/**
 * @brief Run the affine-in-time interval analysis over L and date every accumulator.
 * L must have been through typeAnnotation() first (natures are read for int/float
 * classification of the wrap/absorption modes).
 *
 * @param L the annotated list of output signals
 * @param verbose print one line per event and a final T* summary
 */
SIGS_API HorizonReport horizonAnalysis(Tree L, bool verbose);

/**
 * Read access to the horizon-bounded interval of any signal: the affine form evaluated
 * over [0, T] and collapsed to an ordinary interval. Under a declared lifetime T this
 * is the reading that reconciles the interval's two roles: a counter is [0, T*rate]
 * instead of the wrap range, so a (x + counter) % N table index is provably in bounds
 * FOR THE DECLARED LIFETIME, and the integer bits of a fixed-point format come back.
 * Worst-case parameters (full declared ranges).
 */
class SIGS_API HorizonReader {
   public:
    explicit HorizonReader(Tree L);
    ~HorizonReader();
    HorizonReader(const HorizonReader&)            = delete;
    HorizonReader& operator=(const HorizonReader&) = delete;

    itv::interval at(Tree sig) const;  ///< horizon interval of sig

   private:
    struct Impl;
    Impl* fImpl;
};
