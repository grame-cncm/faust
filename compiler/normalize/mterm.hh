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
#include "normalize.hh"
#include "signals.hh"
#include "sigorderrules.hh"
#include "sigprint.hh"
#include "simplify.hh"
#include "tlib.hh"

/**
 * @brief Represents a multiplicative term in algebraic normal form.
 * 
 * The mterm class implements a multiplicative expression of the form:
 * k * x^n * y^m * ... where:
 * - k is a constant coefficient (integer or floating-point)
 * - x, y, ... are signal variables/expressions
 * - n, m, ... are integer powers
 * 
 * This representation enables efficient algebraic operations:
 * - Multiplication by combining powers of like terms
 * - Division by subtracting powers
 * - Finding greatest common divisors for factorization
 * - Computing complexity metrics for optimization decisions
 * 
 * The class maintains separate storage for the constant coefficient
 * and a map of signal factors to their powers, allowing for efficient
 * arithmetic operations and normalization.
 * 
 * @see aterm for additive combinations of multiplicative terms
 */
class mterm : public virtual Garbageable {
    /// Constant coefficient of the multiplicative term (typically 1, -1, or other numeric values)
    Tree fCoef;
    /// Non-constant signal factors mapped to their integer powers
    std::map<Tree, int> fFactors;

   public:
    /**
     * @brief Create a zero multiplicative term.
     * 
     * Initializes an mterm representing mathematical zero.
     */
    mterm();
    
    /**
     * @brief Create a simple integer multiplicative term.
     * 
     * @param k The integer coefficient
     */
    mterm(int k);
    
    /**
     * @brief Create a simple floating-point multiplicative term.
     * 
     * @param k The floating-point coefficient
     */
    mterm(double k);
    
    /**
     * @brief Create a multiplicative term from an expression tree.
     * 
     * Parses a multiplicative expression and decomposes it into
     * coefficient and factor components.
     * 
     * @param t The multiplicative expression tree
     */
    mterm(Tree t);
    
    /**
     * @brief Copy constructor.
     * 
     * @param m The multiplicative term to copy
     */
    mterm(const mterm& m);

    /**
     * @brief Remove factors with zero power.
     * 
     * Cleans up the internal representation by removing any factors
     * that have been reduced to power zero (which equals 1).
     */
    void cleanup();
    
    /**
     * @brief Check if the term represents a non-zero value.
     * 
     * @return true if the term is not mathematically zero
     */
    bool isNotZero() const;
    
    /**
     * @brief Check if the term has a negative coefficient.
     * 
     * @return true if the coefficient is negative
     */
    bool isNegative() const;

    /**
     * @brief Assignment operator.
     * 
     * Replaces the content of this term with a copy of another term.
     * 
     * @param m The multiplicative term to copy from
     * @return Reference to this term
     */
    const mterm& operator=(const mterm& m);

    /**
     * @brief Multiply in place by an expression tree.
     * 
     * Decomposes the expression and multiplies it with this term.
     * 
     * @param m The multiplicative expression to multiply by
     * @return Reference to this term
     */
    const mterm& operator*=(Tree m);
    
    /**
     * @brief Divide in place by an expression tree.
     * 
     * Decomposes the expression and divides this term by it.
     * 
     * @param m The multiplicative expression to divide by
     * @return Reference to this term
     */
    const mterm& operator/=(Tree m);

    /**
     * @brief Add another multiplicative term in place.
     * 
     * Only valid for terms with the same signature (same factors).
     * Combines coefficients while keeping factors unchanged.
     * 
     * @param m The multiplicative term to add (must have same signature)
     * @return Reference to this term
     */
    const mterm& operator+=(const mterm& m);
    
    /**
     * @brief Subtract another multiplicative term in place.
     * 
     * Only valid for terms with the same signature (same factors).
     * 
     * @param m The multiplicative term to subtract (must have same signature)
     * @return Reference to this term
     */
    const mterm& operator-=(const mterm& m);

    /**
     * @brief Multiply in place by another multiplicative term.
     * 
     * Combines coefficients and adds powers of like factors.
     * 
     * @param m The multiplicative term to multiply by
     * @return Reference to this term
     */
    const mterm& operator*=(const mterm& m);
    
    /**
     * @brief Divide in place by another multiplicative term.
     * 
     * Divides coefficients and subtracts powers of like factors.
     * 
     * @param m The multiplicative term to divide by
     * @return Reference to this term
     */
    const mterm& operator/=(const mterm& m);

    /**
     * @brief Multiply two multiplicative terms.
     * 
     * @param m The multiplicative term to multiply with
     * @return A new multiplicative term representing the product
     */
    mterm operator*(const mterm& m) const;
    
    /**
     * @brief Divide two multiplicative terms.
     * 
     * @param m The multiplicative term to divide by
     * @return A new multiplicative term representing the quotient
     */
    mterm operator/(const mterm& m) const;
    
    /**
     * @brief Print the term in human-readable form.
     * 
     * Outputs the term in the format: k*x1^n1*x2^n2*...
     * 
     * @param dst Output stream to write to
     * @return Reference to the output stream
     */
    std::ostream& print(std::ostream& dst) const;

    /**
     * @brief Compute a complexity metric for the term.
     * 
     * Returns an integer representing the computational complexity
     * of this term, used for optimization decisions.
     * 
     * @return Complexity value (higher means more complex)
     */
    int complexity() const;
    
    /**
     * @brief Convert to normalized expression tree.
     * 
     * Reconstructs a Faust expression tree from the internal
     * multiplicative representation.
     * 
     * @param sign Whether to force a positive sign
     * @param neg Whether to negate the result
     * @return The normalized expression tree
     */
    Tree normalizedTree(bool sign = false, bool neg = false) const;
    
    /**
     * @brief Get the signature of this term.
     * 
     * Returns a normalized tree representing the non-coefficient
     * part of the term (the factors without their powers or coefficients).
     * Terms with the same signature can be combined additively.
     * 
     * @return The signature tree
     */
    Tree signatureTree() const;

    /**
     * @brief Check if this term can be divided by another term.
     * 
     * Returns true if all factors in the divisor appear in this term
     * with powers greater than or equal to those in the divisor.
     * 
     * @param n The potential divisor term
     * @return true if this term is divisible by n
     */
    bool hasDivisor(const mterm& n) const;
    
    /**
     * @brief Compute the greatest common divisor of two multiplicative terms.
     * 
     * Finds the largest multiplicative term that divides both input terms.
     * 
     * @param m1 First multiplicative term
     * @param m2 Second multiplicative term
     * @return The greatest common divisor as a multiplicative term
     */
    friend mterm gcd(const mterm& m1, const mterm& m2);
};

/**
 * @brief Stream output operator for multiplicative terms.
 * 
 * Convenience operator for printing multiplicative terms directly to output streams.
 * 
 * @param s Output stream
 * @param m Multiplicative term to print
 * @return Reference to the output stream
 */
inline std::ostream& operator<<(std::ostream& s, const mterm& m)
{
    return m.print(s);
}

#endif
