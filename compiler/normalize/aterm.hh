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
 * Implements a additive term, a set of mterms added together
 * m1 + m2 + m3 + ...
 */
/**
 * @class aterm
 * @brief Implements an additive term, representing a sum of multiplicative terms (mterms).
 *
 * An aterm represents a polynomial expression of the form:
 * m1 + m2 + m3 + ...
 * where each 'm' is an `mterm`. This class is the core of Faust's symbolic
 * simplification engine. It works by grouping `mterm`s that have the same
 * symbolic signature, allowing for algebraic simplification (e.g., 2*x + 3*x = 5*x).
 */
class aterm : public virtual Garbageable {
    /**
     * @brief A map from a signature tree to the corresponding mterm.
     *
     * This is the central data structure of the aterm. The key is the canonical
     * symbolic part of an mterm (from `mterm::signatureTree()`), and the value
     * is the mterm itself. This structure automatically groups "like terms"
     * for simplification.
     */
    std::map<Tree, mterm> fSig2MTerms;  ///< mapping between signatures and corresponding mterms

   public:
    aterm();  ///< create an empty aterm (equivalent to 0)
    /**
     * @brief Creates an aterm by parsing a Faust expression tree.
     * @param t The expression tree to deconstruct into a sum of mterms.
     */
    aterm(Tree t);  ///< create a aterm from an additive exp
                    // aterm (const aterm& a);                        ///< create a copy of an aterm

    /**
     * @brief Adds a Faust expression tree to the aterm in-place.
     * @param t The expression tree to add.
     */
    const aterm& operator+=(Tree t);  ///< add in place an additive expression tree
    /**
     * @brief Subtracts a Faust expression tree from the aterm in-place.
     * @param t The expression tree to subtract.
     */
    const aterm& operator-=(Tree t);  ///< add in place an additive expression tree

    /**
     * @brief Adds an mterm in-place, combining it with existing terms of the same signature.
     * @param m The mterm to add.
     */
    const aterm& operator+=(const mterm& m);  ///< add in place an mterm
    /**
     * @brief Subtracts an mterm in-place, combining it with existing terms of the same signature.
     * @param m The mterm to subtract.
     */
    const aterm& operator-=(const mterm& m);  ///< add in place an mterm
    /**
     * @brief Reconstructs a single, simplified, and canonical Faust expression tree from the aterm.
     */
    Tree normalizedTree() const;  ///< return the corresponding normalized expression tree

    std::ostream& print(std::ostream& dst) const;  ///< print a aterm m1 + m2 + m3 +...
    /**
     * @brief Finds the greatest common divisor (GCD) among all pairs of mterms.
     * This is used to find opportunities for factorization.
     */
    mterm greatestDivisor() const;  ///< return the greatest divisor of any two mterms
    /**
     * @brief Reorganizes the aterm by factoring out the divisor 'd'.
     * @param d The mterm to factor out.
     * @return A new aterm representing the factorized expression.
     */
    aterm factorize(const mterm& d);  ///< reorganize the aterm by factorizing d
};

/**
 * @brief Stream insertion operator for printing an aterm.
 */
inline std::ostream& operator<<(std::ostream& s, const aterm& a)
{
    return a.print(s);
}

/**
 * @brief Adds two expression trees, performing basic simplifications.
 *
 * Simplifies number+number, 0+t, and canonicalizes the order of operands
 * to improve sharing in the expression graph.
 * @param t1 The first tree.
 * @param t2 The second tree.
 * @return The simplified sum as a new tree.
 */
Tree simplifyingAdd(Tree t1, Tree t2);

#endif
