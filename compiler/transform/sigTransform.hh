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

#ifndef __SIGTRANSFORM__
#define __SIGTRANSFORM__

#include <functional>
#include "global.hh"
#include "property.hh"
#include "rewriteRule.hh"
#include "signals.hh"
#include "tree.hh"

using namespace std;

//------------------------------------------------------------------------------
// sigTransform: Recursive signal transformation with memoization
//------------------------------------------------------------------------------
// Mathematical framework for recursive signal transformations:
//
// Notation:
//   F  = base transformation function (parameter 'transform')
//   TF = recursive transformation function (sigTransform)
//   op[s1,s2,...] = signal node 'op' with subsignals s1,s2,...
//   x = [s1,s2,...] = recursive group 'x' with definitions s1,s2,...
//
// Transformation rules:
//   TF(op[s1,s2,...]) -> F(op[TF(s1),TF(s2),...])   [general case]
//   TF(x = [s1,s2,...]) -> x = [TF(s1),TF(s2),...]  [recursive definitions]
//
// Properties:
//   - Bottom-up evaluation: subsignals transformed before parent
//   - Memoization: TF(s) computed once, cached for subsequent uses
//   - Cycle prevention: essential for recursive signal definitions
//
// Usage:
//   property<Tree> cache;
//   Tree result = sigTransform(F, cache, signal);
//------------------------------------------------------------------------------

/**
 * @brief Apply normalization recursively to signal tree (TF function)
 *
 * Simplified API that creates its own cache internally.
 *
 * Implements: TF(op[s1,s2,...]) -> N(op[TF(s1),TF(s2),...])
 *            TF(x = [s1,s2,...]) -> x = [TF(s1),TF(s2),...]
 *
 * @param normalize The normalizer N using rewrite rules
 * @param signal The input signal tree to transform
 * @param visitgen If true, visit generator signals; if false, skip them
 * @return Tree The transformed signal tree TF(signal)
 */
Tree sigTransform(Normalize& normalize, Tree signal, bool visitgen = true);

/**
 * @brief Transform a list of signals: [s1,s2,...] -> [TF(s1),TF(s2),...]
 *
 * Simplified API that creates its own cache internally.
 *
 * @param normalize The normalizer N using rewrite rules
 * @param lsig The signal list [s1,s2,...] (nil-terminated)
 * @param visitgen If true, visit generator signals; if false, skip them
 * @return Tree The transformed list [TF(s1),TF(s2),...]
 */
Tree sigListTransform(Normalize& normalize, Tree lsig, bool visitgen = true);

#endif