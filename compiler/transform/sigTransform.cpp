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

#include "sigTransform.hh"
#include "ppsig.hh"
#include "signals.hh"
#include "sigtype.hh"

using namespace std;

// Internal functions with explicit cache for performance
static Tree sigTransformCached(Normalize& normalize, property<Tree>& cache, Tree signal,
                               bool visitgen);
static Tree sigListTransformCached(Normalize& normalize, property<Tree>& cache, Tree lsig,
                                   bool visitgen);

/**
 * @brief Apply normalization recursively to signal tree (TF function)
 *
 * Implements the mathematical transformation rules:
 *   TF(op[s1,s2,...]) -> N(op[TF(s1),TF(s2),...])   [general case]
 *   TF(x = [s1,s2,...]) -> x = [TF(s1),TF(s2),...]  [recursive definitions]
 *
 * @param normalize The normalizer N using rewrite rules
 * @param cache Property map for memoization - stores TF(s) results
 * @param signal The input signal tree to transform
 * @param visitgen If true, visit generator signals; if false, skip them
 * @return Tree The transformed signal tree TF(signal)
 */
static Tree sigTransformCached(Normalize& normalize, property<Tree>& cache, Tree signal,
                               bool visitgen)
{
    // Check cache first: avoid recomputation and prevent infinite cycles
    if (Tree cached; cache.get(signal, cached)) {
        return cached;
    }

    // Special case for recursive definitions: TF(x = [s1,s2,...]) -> x = [TF(s1),TF(s2),...]
    if (Tree id, ldefs; isRec(signal, id, ldefs)) {
        // Cache immediately to prevent infinite recursion
        cache.set(signal, signal);

        // Transform the definitions: [s1,s2,...] -> [TF(s1),TF(s2),...]
        Tree result = rec(id, sigListTransformCached(normalize, cache, ldefs, visitgen));

        // Sanity check: recursive group structure unchanged
        faustassert(signal == result);
        return signal;
    }

    // General case: TF(op[s1,s2,...]) -> F(op[TF(s1),TF(s2),...])

    // Extract subsignals: op[s1,s2,...] -> [s1,s2,...]
    tvec subsignals;
    (void)getSubSignals(signal, subsignals, visitgen);

    // Transform each subsignal: si -> TF(si)
    for (auto& sub : subsignals) {
        sub = sigTransformCached(normalize, cache, sub, visitgen);
    }

    // Reconstruct with transformed subsignals: op[TF(s1),TF(s2),...]
    Tree tmp = setSubSignals(signal, subsignals, visitgen);

    // Apply normalization: N(op[TF(s1),TF(s2),...])
    Tree result = normalize(tmp);

    // Propagate type and recursiveness information from original signal to transformed signal
    if (signal != result) {
        // Copy TYPE property
        if (Type sigType = getSigType(signal); sigType && !getSigType(result)) {
            setSigType(result, sigType);
        }
        // Copy RECURSIVNESS property
        if (Tree recProp; getProperty(signal, gGlobal->RECURSIVNESS, recProp)) {
            if (Tree resultRecProp; !getProperty(result, gGlobal->RECURSIVNESS, resultRecProp)) {
                setProperty(result, gGlobal->RECURSIVNESS, recProp);
            }
        }
    }

    // Cache and return result
    cache.set(signal, result);
    return result;
}

/**
 * @brief Transform a list of signals: [s1,s2,...] -> [TF(s1),TF(s2),...]
 *
 * Implements list transformation using head/tail recursion:
 *   TF([]) = []
 *   TF([s|rest]) = [TF(s)|TF(rest)]
 *
 * @param normalize The normalizer N using rewrite rules
 * @param cache Property map for memoization
 * @param lsig The signal list [s1,s2,...] (nil-terminated)
 * @param visitgen If true, visit generator signals; if false, skip them
 * @return Tree The transformed list [TF(s1),TF(s2),...]
 */
static Tree sigListTransformCached(Normalize& normalize, property<Tree>& cache, Tree lsig,
                                   bool visitgen)
{
    // Base case: TF([]) = []
    if (isNil(lsig)) {
        return lsig;
    } else {
        // Recursive case: TF([s|rest]) = [TF(s)|TF(rest)]
        Tree f = sigTransformCached(normalize, cache, hd(lsig), visitgen);
        return cons(f, sigListTransformCached(normalize, cache, tl(lsig), visitgen));
    }
}

/**
 * @brief Apply normalization recursively to signal tree (TF function)
 *
 * Simplified API that creates its own cache internally.
 *
 * Implements the mathematical transformation rules:
 *   TF(op[s1,s2,...]) -> N(op[TF(s1),TF(s2),...])   [general case]
 *   TF(x = [s1,s2,...]) -> x = [TF(s1),TF(s2),...]  [recursive definitions]
 *
 * @param normalize The normalizer N using rewrite rules
 * @param signal The input signal tree to transform
 * @param visitgen If true, visit generator signals; if false, skip them
 * @return Tree The transformed signal tree TF(signal)
 */
Tree sigTransform(Normalize& normalize, Tree signal, bool visitgen)
{
    property<Tree> cache;
    return sigTransformCached(normalize, cache, signal, visitgen);
}

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
Tree sigListTransform(Normalize& normalize, Tree lsig, bool visitgen)
{
    property<Tree> cache;
    return sigListTransformCached(normalize, cache, lsig, visitgen);
}