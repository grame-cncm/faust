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

/**
 * @file simplify.hh
 * @brief Signal simplification functions for the Faust compiler
 * 
 * This module provides functions to simplify signal expressions by applying
 * algebraic identities, constant folding, and other optimization techniques.
 * 
 * The simplification process performs compile-time optimizations such as:
 * - Constant folding (e.g., 2 + 3 -> 5)
 * - Algebraic identities (e.g., x * 1 -> x, x + 0 -> x)
 * - Dead code elimination
 * - Expression canonicalization
 * 
 * Note that simplification may introduce type promotion issues that need
 * to be resolved using castPromote in subsequent passes.
 * 
 * @author GRAME
 * @version 2.75+
 */

#ifndef _SIMPLIFY_
#define _SIMPLIFY_

/**
 * @brief Simplify a signal expression.
 * 
 * This function applies various algebraic simplification rules to reduce
 * the complexity of signal expressions while preserving their semantic
 * meaning. The simplification includes:
 * 
 * - Constant folding for compile-time evaluation
 * - Application of algebraic identities (x*1->x, x+0->x, etc.)
 * - Elimination of redundant operations
 * - Normalization of expression structure
 * 
 * The function recursively processes the signal tree, applying appropriate
 * simplification rules at each node. Some optimizations may change the
 * type structure of expressions, requiring subsequent type promotion.
 * 
 * @param sig The signal expression to simplify
 * @return A simplified signal expression with equivalent semantics
 * 
 * @note The resulting tree may contain incorrectly promoted subtrees
 *       that need to be processed using castPromote.
 * 
 * @see castPromote() for handling type promotion after simplification
 * @see normalizeAddTerm() for additive expression normalization
 */
Tree simplify(Tree sig);

/**
 * @brief Convert regular tables to documentation tables.
 * 
 * This function transforms standard read/write table operations into
 * special documentation table forms that are used for mathematical
 * documentation generation. Documentation tables have special semantics
 * that facilitate the creation of mathematical descriptions and diagrams.
 * 
 * The conversion affects:
 * - rdtable operations -> sigDocAccessTbl
 * - rwtable operations -> sigDocWriteTbl
 * - Constant table initialization -> sigDocConstantTbl
 * 
 * This transformation is typically used when generating mathematical
 * documentation (-mdoc option) to create more readable representations
 * of table operations in the generated LaTeX output.
 * 
 * @param sig The signal expression containing table operations
 * @return Signal expression with documentation table operations
 * 
 * @see sigDocAccessTbl() for documentation table access
 * @see sigDocWriteTbl() for documentation table writing
 * @see sigDocConstantTbl() for documentation constant tables
 */
Tree docTableConvertion(Tree sig);

#endif
