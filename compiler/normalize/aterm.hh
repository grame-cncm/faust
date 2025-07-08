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

#ifndef __ATERM__
#define __ATERM__

#include <stdio.h>
#include <list>
#include <map>

#include "exception.hh"
#include "garbageable.hh"
#include "mterm.hh"
#include "normalize.hh"
#include "signals.hh"
#include "sigorderrules.hh"
#include "sigprint.hh"
#include "simplify.hh"
#include "tlib.hh"

/**
 * @brief Represents an additive term composed of multiple multiplicative terms.
 * 
 * The aterm class implements an additive expression of the form:
 * m1 + m2 + m3 + ... where each mi is a multiplicative term (mterm).
 * 
 * This representation enables efficient algebraic simplification by:
 * - Grouping terms with the same signature
 * - Finding common factors across terms
 * - Factorizing expressions to reduce computational complexity
 * 
 * The class maintains a mapping between signal signatures and their
 * corresponding multiplicative terms, allowing for efficient addition
 * and factorization operations.
 * 
 * @see mterm for multiplicative term representation
 */
class aterm : public virtual Garbageable {
    /// Mapping between signal signatures and their corresponding multiplicative terms
    std::map<Tree, mterm> fSig2MTerms;

   public:
    /**
     * @brief Create an empty additive term (equivalent to mathematical 0).
     */
    aterm();
    
    /**
     * @brief Create an additive term from an expression tree.
     * 
     * Parses the given tree and decomposes it into constituent multiplicative
     * terms. Handles addition, subtraction, and nested expressions.
     * 
     * @param t The expression tree to convert to additive normal form
     */
    aterm(Tree t);

    /**
     * @brief Add an expression tree in place.
     * 
     * Decomposes the expression and adds its terms to this additive term.
     * Terms with the same signature are combined automatically.
     * 
     * @param t The additive expression tree to add
     * @return Reference to this aterm for method chaining
     */
    const aterm& operator+=(Tree t);
    
    /**
     * @brief Subtract an expression tree in place.
     * 
     * Decomposes the expression and subtracts its terms from this additive term.
     * Equivalent to adding the negation of each term.
     * 
     * @param t The additive expression tree to subtract
     * @return Reference to this aterm for method chaining
     */
    const aterm& operator-=(Tree t);

    /**
     * @brief Add a multiplicative term in place.
     * 
     * @param m The multiplicative term to add
     * @return Reference to this aterm for method chaining
     */
    const aterm& operator+=(const mterm& m);
    
    /**
     * @brief Subtract a multiplicative term in place.
     * 
     * @param m The multiplicative term to subtract
     * @return Reference to this aterm for method chaining
     */
    const aterm& operator-=(const mterm& m);
    
    /**
     * @brief Convert back to normalized expression tree.
     * 
     * Reconstructs a Faust expression tree from the internal additive
     * representation. The result is in normal form with common factors
     * properly organized.
     * 
     * @return The normalized expression tree
     */
    Tree normalizedTree() const;

    /**
     * @brief Print the additive term in human-readable form.
     * 
     * Outputs the term in the format: m1 + m2 + m3 + ...
     * 
     * @param dst Output stream to write to
     * @return Reference to the output stream
     */
    std::ostream& print(std::ostream& dst) const;
    
    /**
     * @brief Find the greatest common divisor of all multiplicative terms.
     * 
     * Computes the greatest multiplicative term that divides all terms
     * in this additive expression. This is used for factorization.
     * 
     * @return The greatest common divisor as a multiplicative term
     */
    mterm greatestDivisor() const;
    
    /**
     * @brief Factorize the additive term by a given divisor.
     * 
     * Reorganizes the expression by factoring out the given multiplicative
     * term from all constituent terms. This creates a more efficient
     * representation: d * (t1 + t2 + ...) where d is the divisor.
     * 
     * @param d The multiplicative term to factor out
     * @return A new factorized additive term
     */
    aterm factorize(const mterm& d);
};

/**
 * @brief Stream output operator for additive terms.
 * 
 * Convenience operator for printing additive terms directly to output streams.
 * 
 * @param s Output stream
 * @param a Additive term to print
 * @return Reference to the output stream
 */
inline std::ostream& operator<<(std::ostream& s, const aterm& a)
{
    return a.print(s);
}

/**
 * @brief Perform optimized addition of two expression trees.
 * 
 * This function provides an optimized way to add two expression trees
 * by using the additive term representation for simplification.
 * Unlike simple tree addition, this function may factorize common
 * terms and produce a more efficient result.
 * 
 * @param t1 First expression tree
 * @param t2 Second expression tree
 * @return Simplified sum of the two trees
 * 
 * @see aterm for the underlying additive representation
 */
Tree simplifyingAdd(Tree t1, Tree t2);

#endif
