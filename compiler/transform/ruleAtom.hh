/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#ifndef __RULEATOM__
#define __RULEATOM__

#include <functional>
#include <optional>
#include "global.hh"
#include "signals.hh"
#include "tree.hh"

//------------------------------------------------------------------------------
// Rule Atoms: Composable rule fragments for pattern matching
//------------------------------------------------------------------------------
// Type system for optimized rule composition:
//
// I = void -> optional<Tree>        (Input type with centralized state)
// T = Tree -> optional<Tree>        (Pure transformation - signal guaranteed non-null)
// O = optional<Tree> -> boolean     (Output type)
//
// Architecture principles:
//   - Only InputAtom maintains state and performs null checks
//   - Pattern atoms receive guaranteed non-null Tree and return optional<Tree>
//   - Automatic short-circuit: if any operator() returns nullopt, chain stops
//   - Performance: 1 test per chain instead of N redundant tests
//
// Composition rules:
//   I >> T = I    (input + pattern = input, with centralized testing)
//   I >> O = bool (input + output = boolean)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Type aliases for readability
//------------------------------------------------------------------------------
using TreeOpt = std::optional<Tree>;

//------------------------------------------------------------------------------
// Forward declarations
//------------------------------------------------------------------------------
class ClockedAtom;
class DelayedAtom;
class OutputAtom;

//------------------------------------------------------------------------------
// OutputAtom: Final extraction of result
//------------------------------------------------------------------------------
class OutputAtom {
   private:
    Tree& fResultVar;

   public:
    OutputAtom(Tree& resultVar) : fResultVar(resultVar) {}

    // Process the signal and return success
    bool process(TreeOpt signal)
    {
        if (signal) {
            fResultVar = *signal;
            return true;
        }
        return false;
    }
};

//------------------------------------------------------------------------------
// InputAtom: Starting point for pattern matching chain - maintains internal state
//------------------------------------------------------------------------------
class InputAtom {
   private:
    TreeOpt fState;  // Internal state that gets transformed through the chain

   public:
    InputAtom(Tree signal) : fState(signal) {}
    InputAtom(TreeOpt signal) : fState(signal) {}

    // Operator for pattern atoms - applies transformation and returns moved *this
    template <typename PatternAtom>
    InputAtom operator>>(PatternAtom&& pattern) &&
    {
        if (fState) {                   // Only call operator() if we have a valid state
            fState = pattern(*fState);  // Dereference the optional
        }
        // If fState is nullopt, it stays nullopt (short-circuit)
        return std::move(*this);
    }

    // Special case for OutputAtom - extracts final result
    bool operator>>(OutputAtom&& output) && { return output.process(fState); }
};

//------------------------------------------------------------------------------
// ClockedAtom: Pure transformation to match clocked signals
//------------------------------------------------------------------------------
class ClockedAtom {
   private:
    Tree& fClockVar;

   public:
    ClockedAtom(Tree& clockVar) : fClockVar(clockVar) {}

    // Pure transformation: Tree -> optional<Tree> (signal guaranteed non-null)
    TreeOpt operator()(Tree signal)
    {
        Tree body;
        if (isSigClocked(signal, fClockVar, body)) {
            return body;
        }
        return std::nullopt;  // No match
    }
};

//------------------------------------------------------------------------------
// DelayedAtom: Pure transformation to match delayed signals
//------------------------------------------------------------------------------
class DelayedAtom {
   private:
    Tree& fDelayVar;

   public:
    DelayedAtom(Tree& delayVar) : fDelayVar(delayVar) {}

    // Pure transformation: Tree -> optional<Tree> (signal guaranteed non-null)
    TreeOpt operator()(Tree signal)
    {
        Tree body;
        if (isSigDelay(signal, body, fDelayVar)) {
            return body;
        }
        return std::nullopt;  // No match
    }
};

//------------------------------------------------------------------------------
// DelayedAtom: Pure transformation to match delayed signals
//------------------------------------------------------------------------------
class RecAtom {
   private:
    Tree& fDef;

   public:
    RecAtom(Tree& defVar) : fDef(defVar) {}

    // Pure transformation: Tree -> optional<Tree> (signal guaranteed non-null)
    TreeOpt operator()(Tree signal)
    {
        if (hasProjDefinition(signal, fDef)) {
            return signal;
        }
        return std::nullopt;  // No match
    }
};

//------------------------------------------------------------------------------
// Factory functions for common patterns
//------------------------------------------------------------------------------

/**
 * @brief Create an input atom from a signal
 */
InputAtom input(Tree signal);

/**
 * @brief Pattern to match a clocked signal and extract the clock
 */
ClockedAtom clocked(Tree& clockVar);

/**
 * @brief Pattern to match a delayed signal and extract the delay
 */
DelayedAtom delayed(Tree& delayVar);

/**
 * @brief Pattern to match a recursive projection and extract its definition
 */
RecAtom recursive(Tree& def);

/**
 * @brief Output atom that extracts the final signal
 */
OutputAtom output(Tree& resultVar);

#endif