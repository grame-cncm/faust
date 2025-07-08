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

#ifndef __MTERM__
#define __MTERM__

#include <stdio.h>
#include <list>
#include <map>

#include "exception.hh"
#include "garbageable.hh"
#include "signals.hh"
#include "sigorderrules.hh"
#include "sigprint.hh"
#include "simplify.hh"
#include "tlib.hh"

/**
 * Implements a multiplicative term, a term of type
 * k*x^n*y^m*... and its arithmetic.
 */
/**
 * @class mterm
 * @brief Implements a multiplicative term and its arithmetic.
 *
 * An mterm represents a mathematical term in the form of a product:
 * k * f1**p1 * f2**p2 * ...
 * where 'k' is a numerical coefficient and 'f' are symbolic factors raised
 * to integer powers 'p'. This class is fundamental for Faust's symbolic
 * expression simplification engine.
 */
class mterm : public virtual Garbageable {
    /**
     * @brief The numerical coefficient 'k' of the term.
     *
     * It is stored as a Faust `Tree` and can represent an integer or a
     * floating-point value.
     */
    Tree fCoef;  ///< constant part of the term (usually 1 or -1)
    /**
     * @brief A map of symbolic factors to their integer powers.
     *
     * The map's keys are `Tree` nodes representing the symbolic factors (e.g., x, y),
     * and the values are their corresponding integer exponents (e.g., n, m).
     */
    std::map<Tree, int> fFactors;  ///< non constant terms and their power

   public:
    mterm();          ///< create a 0 mterm
    mterm(int k);     ///< create a simple integer mterm
    mterm(double k);  ///< create a simple float mterm
    /**
     * @brief Creates an mterm by parsing a Faust expression tree.
     * @param t The input expression tree to deconstruct.
     */
    mterm(Tree t);          ///< create a mterm from a multiplicative exp
    mterm(const mterm& m);  ///< create a copy of a mterm

    /**
     * @brief Removes factors with a power of zero.
     *
     * This utility function also clears all factors if the coefficient is zero,
     * ensuring the mterm remains in a canonical form.
     */
    void cleanup();  ///< remove used factors
    /**
     * @brief Returns true if the mterm's coefficient is not zero.
     */
    bool isNotZero() const;  ///< true if mterm doesn't represent number 0
    /**
     * @brief Returns true if the mterm's coefficient is strictly negative.
     */
    bool isNegative() const;  ///< true if mterm has a negative coefficient

    const mterm& operator=(const mterm& m);  ///< replace the content with a copy of m

    /**
     * @brief Multiplies the mterm by a Faust expression tree in-place.
     * @param m The expression tree to multiply by.
     */
    const mterm& operator*=(Tree m);  ///< multiply in place by a multiplicative exp
    /**
     * @brief Divides the mterm by a Faust expression tree in-place.
     * @param m The expression tree to divide by.
     */
    const mterm& operator/=(Tree m);  ///< divide in place by a multiplicative exp

    /**
     * @brief Adds another mterm in-place.
     * This operation is only valid if the mterms have the same signature.
     * It works by adding their numerical coefficients.
     * @param m The mterm to add.
     */
    const mterm& operator+=(const mterm& m);  ///< add in place an mterm of same signature
    /**
     * @brief Subtracts another mterm in-place.
     * This operation is only valid if the mterms have the same signature.
     * It works by subtracting their numerical coefficients.
     * @param m The mterm to subtract.
     */
    const mterm& operator-=(const mterm& m);  ///< add in place an mterm of same signature

    /**
     * @brief Multiplies by another mterm in-place.
     * The coefficients are multiplied, and the powers of the factors are added.
     * @param m The mterm to multiply by.
     */
    const mterm& operator*=(const mterm& m);  ///< multiply in place by a mterm
    /**
     * @brief Divides by another mterm in-place.
     * The coefficient is divided, and the powers of the factors are subtracted.
     * @param m The mterm to divide by.
     */
    const mterm& operator/=(const mterm& m);  ///< divide in place by a mterm

    mterm         operator*(const mterm& m) const;  ///< mterms multiplication
    mterm         operator/(const mterm& m) const;  ///< mterms division
    std::ostream& print(std::ostream& dst) const;   ///< print a mterm k*x1**n1*x2**n2...

    /**
     * @brief Calculates the complexity of the mterm.
     * Complexity is a metric for optimization, based on the number and order
     * of its factors and whether the coefficient is non-unity.
     */
    int complexity() const;  ///< return an evaluation of the complexity
    /**
     * @brief Reconstructs a canonical Faust expression tree from the mterm.
     * @param sign If true, operates in "signature mode," ignoring the coefficient.
     * @param neg If true, inverts the sign of the coefficient in the output tree.
     */
    Tree normalizedTree(bool sign = false,
                        bool neg  = false) const;  ///< return the normalized tree of the mterm
    /**
     * @brief Returns the signature tree of the mterm.
     * The signature is a canonical representation of the symbolic factors,
     * ignoring the coefficient. It is used to identify "like terms".
     */
    Tree signatureTree() const;  ///< return a signature (a normalized tree)

    /**
     * @brief Checks if this mterm can be divided by another mterm 'n'.
     * Divisibility requires that the division does not introduce new complexity,
     * for instance, by creating a negative power from a positive one.
     * @param n The potential divisor mterm.
     */
    bool hasDivisor(const mterm& n) const;  ///< return true if this can be divided by n
    /**
     * @brief Computes the greatest common divisor (GCD) of two mterms.
     *
     * The GCD consists of the common factors raised to the minimum common power.
     * The coefficient of the resulting GCD is typically simplified to 1.
     */
    friend mterm gcd(const mterm& m1, const mterm& m2);  /// greatest common divisor of two mterms
};

/**
 * @brief Stream insertion operator for printing an mterm. 
 * @param s The output stream.
 * @param m The mterm to print.
 * @return The output stream.
 */
inline std::ostream& operator<<(std::ostream& s, const mterm& m)
{
    return m.print(s);
}

#endif
