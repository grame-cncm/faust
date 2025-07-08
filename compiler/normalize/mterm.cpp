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
 * @file mterm.cpp
 * @brief Implementation of the multiplicative term (`mterm`) class. (New Documentation)
 *
 * This file contains the logic for manipulating multiplicative terms, which
 * are a cornerstone of Faust's symbolic simplification engine. It handles
 * parsing expression trees into mterms, performing arithmetic, and
 * reconstructing canonical expression trees from them.
 */

#include "mterm.hh"
#include "exception.hh"
#include "global.hh"
#include "ppsig.hh"
#include "signals.hh"
#include "xtended.hh"

#undef TRACE
using namespace std;

typedef map<Tree, int> MP;

mterm::mterm() : fCoef(sigInt(0))
{
}
mterm::mterm(int k) : fCoef(sigInt(k))
{
}
mterm::mterm(double k) : fCoef(sigReal(k))
{
}
mterm::mterm(const mterm& m) : fCoef(m.fCoef), fFactors(m.fFactors)
{
}

/**
 * @brief Create a mterm from a tree expression
 */
/**
 * @brief Creates an mterm from a Faust expression tree. (New Documentation)
 *
 * This constructor initializes the mterm with a multiplicative identity (a
 * coefficient of 1) and then uses the in-place multiplication operator (`*=`)
 * to recursively parse the input tree and build the mterm's internal state.
 * @param t The input expression tree to deconstruct.
 */
mterm::mterm(Tree t) : fCoef(sigInt(1))
{
#ifdef TRACE
    cerr << "mterm::mterm (Tree t) : " << ppsig(t) << endl;
#endif
    *this *= t;
#ifdef TRACE
    cerr << "MTERM(" << ppsig(t) << ") -> " << *this << endl;
#endif
}

/**
 * @brief true if mterm doesn't represent number 0
 */
/**
 * @brief Checks if the mterm's coefficient is not zero. (New Documentation)
 * @return True if the coefficient is non-zero, false otherwise.
 */
bool mterm::isNotZero() const
{
    return !isZero(fCoef);
}

/**
 * @brief true if mterm is strictly negative
 */
/**
 * @brief Checks if the mterm has a negative coefficient. (New Documentation)
 * @return True if the coefficient is strictly negative.
 */
bool mterm::isNegative() const
{
    return !isGEZero(fCoef);
}

/**
 * @brief Print a mterm in a human readable format
 */
/**
 * @brief Prints a human-readable representation of the mterm. (New Documentation)
 *
 * The format is `k * f1**p1 * f2**p2 ...`. The coefficient `k` is omitted
 * if it is 1 and there are other factors.
 * @param dst The output stream.
 * @return A reference to the output stream.
 */
ostream& mterm::print(ostream& dst) const
{
    const char* sep = "";
    if (!isOne(fCoef) || fFactors.empty()) {
        dst << ppsig(fCoef);
        sep = " * ";
    }
    // if (true) { dst << ppsig(fCoef); sep = " * "; }
    for (const auto& p : fFactors) {
        dst << sep << ppsig(p.first);
        if (p.second != 1) {
            dst << "**" << p.second;
        }
        sep = " * ";
    }
    return dst;
}

/**
 * @brief Compute the "complexity" of a mterm, that is the number of
 * factors it contains (weighted by the importance of these factors)
 */
/**
 * @brief Computes the "complexity" of the mterm. (New Documentation)
 *
 * Complexity is a metric used for optimization decisions, such as in choosing
 * a common divisor for factorization. It's a weighted sum of the term's
 * components:
 * - A non-unity, non-minus-one coefficient adds 1.
 * - Each factor adds `(1 + order) * abs(power)`, where `order` is the
 * factor's signal order (e.g., signal-rate is higher order than control-rate).
 * @return An integer representing the term's complexity.
 */
int mterm::complexity() const
{
    int c = isOne(fCoef) ? 0 : (isMinusOne(fCoef) ? 0 : 1);
    for (const auto& p : fFactors) {
        c += (1 + getSigOrder(p.first)) * abs(p.second);
    }
    // cerr << __LINE__ << ":" << __FUNCTION__ << "(" << *this << ") --> " << c << endl;
    return c;
}

/**
 * @brief Match x^p with p:int
 */
/**
 * @brief Checks if a signal tree is an integer power operation (`x**n`). (New Documentation)
 * @param sig The tree to check.
 * @param[out] x The base of the power (`x`).
 * @param[out] n The integer exponent (`n`).
 * @return True if the tree matches the power pattern, false otherwise.
 */
static bool isSigPow(Tree sig, Tree& x, int& n)
{
    // cerr << "isSigPow("<< *sig << ')' << endl;
    xtended* p = (xtended*)getUserData(sig);
    if (p == gGlobal->gPowPrim) {
        if (isSigInt(sig->branch(1), &n)) {
            x = sig->branch(0);
            // cerr << "factor of isSigPow " << *x << endl;
            return true;
        }
    }
    return false;
}

/**
 * @brief Produce x^p with p:int
 */
/**
 * @brief Creates a signal tree for an integer power operation (`x**p`). (New Documentation)
 * @param x The base of the power.
 * @param p The integer exponent.
 * @return A new `Tree` representing `x**p`.
 */
static Tree sigPow(Tree x, int p)
{
    return tree(gGlobal->gPowPrim->symbol(), x, sigInt(p));
}

/**
 * @brief Multiply a mterm by an expression tree. Go down recursively looking
 * for multiplications and divisions
 */
/**
 * @brief Multiplies the mterm by a Faust expression tree in-place. (New Documentation)
 *
 * This operator recursively deconstructs the multiplier tree `t` to update
 * the mterm. It handles numerical values, multiplications, divisions, and
 * symbolic factors, including explicit power terms.
 * @param t The expression tree to multiply by.
 * @return A const reference to the modified mterm (`*this`).
 */
const mterm& mterm::operator*=(Tree t)
{
    int  op, n;
    Tree x, y;

    faustassert(t);

    if (isNum(t)) {
        fCoef = mulNums(fCoef, t);

    } else if (isSigBinOp(t, &op, x, y) && (op == kMul)) {
        *this *= x;
        *this *= y;

    } else if (isSigBinOp(t, &op, x, y) && (op == kDiv)) {
        *this *= x;
        *this /= y;

    } else {
        if (isSigPow(t, x, n)) {
            fFactors[x] += n;
        } else {
            fFactors[t] += 1;
        }
    }
    return *this;
}

/**
 * @brief Divide a mterm by an expression tree t. Go down recursively looking
 * for multiplications and divisions
 */
/**
 * @brief Divides the mterm by a Faust expression tree in-place, recursively processing
 * multiplications and divisions. (New Documentation)
 *
 * This operator updates the `mterm` in-place by dividing it by the provided
 * expression tree `t`. It deconstructs the divisor `t` to correctly modify the
 * `mterm`'s coefficient (`fCoef`) and its symbolic factors (`fFactors`).
 *
 * The logic handles several cases for the divisor `t`:
 *
 * - **Numerical Divisor**: If `t` is a number, the mterm's coefficient `fCoef`
 * is divided by it. A critical check for division by zero is included to prevent errors.
 *
 * - **Division by a Product (e.g., `x * y`)**: Following the rule `A / (x * y) = (A / x) / y`,
 * the function recursively calls itself on each branch of the multiplication.
 *
 * - **Division by a Quotient (e.g., `x / y`)**: Following the rule `A / (x / y) = (A * y) / x`,
 * the function recursively divides by the numerator `x` and multiplies by the denominator `y`.
 *
 * - **Symbolic Factor**: If `t` is a symbolic term (not a number or a `*`/`/` operation),
 * it directly affects the exponents in the `fFactors` map.
 * - If `t` is a power expression like `base**exp`, the exponent `exp` is
 * subtracted from the exponent of the `base` factor.
 * - For any other symbolic factor, its exponent is simply decremented by 1.
 *
 * @param t The expression tree to divide the mterm by.
 * @return A const reference to the modified mterm (`*this`).
 */
const mterm& mterm::operator/=(Tree t)
{
    // cerr << "division in place : " << *this << " / " << ppsig(t) << endl;
    int  op, n;
    Tree x, y;

    faustassert(t);

    if (isNum(t)) {
        if (isZero(t)) {
            stringstream error;
            error << "ERROR : division by 0 in " << *this << " / " << ppsig(t) << endl;
            throw faustexception(error.str());
        }
        fCoef = divExtendedNums(fCoef, t);

    } else if (isSigBinOp(t, &op, x, y) && (op == kMul)) {
        *this /= x;
        *this /= y;

    } else if (isSigBinOp(t, &op, x, y) && (op == kDiv)) {
        *this /= x;
        *this *= y;

    } else {
        if (isSigPow(t, x, n)) {
            fFactors[x] -= n;
        } else {
            fFactors[t] -= 1;
        }
    }
    return *this;
}

/**
 * @brief Replace the content with a copy of m
 */
/**
 * @brief Replaces the content with a copy of another mterm. (New Documentation)
 * @param m The mterm to copy from.
 * @return A const reference to the modified mterm (`*this`).
 */
const mterm& mterm::operator=(const mterm& m)
{
    fCoef    = m.fCoef;
    fFactors = m.fFactors;
    return *this;
}

/**
 * @brief Clean a mterm by removing x**0 factors
 */
/**
 * @brief Cleans up the mterm's internal state. (New Documentation)
 *
 * If the coefficient is zero, all symbolic factors are cleared. Otherwise,
 * any factor with a power of zero is removed from the `fFactors` map.
 */
void mterm::cleanup()
{
    if (isZero(fCoef)) {
        fFactors.clear();
    } else {
        for (MP::iterator p = fFactors.begin(); p != fFactors.end();) {
            if (p->second == 0) {
                fFactors.erase(p++);
            } else {
                p++;
            }
        }
    }
}

/**
 * @brief Add in place an mterm. As we want the result to be
 * a mterm therefore essentially mterms of same signature can be added
 */
/**
 * @brief Adds another mterm in-place. (New Documentation)
 *
 * This operation is only valid if the mterms have the same signature (i.e.,
 * the same symbolic factors), which is enforced by an assertion. It works
 * by simply adding their numerical coefficients.
 * @param m The mterm to add.
 * @return A const reference to the modified mterm (`*this`).
 */
const mterm& mterm::operator+=(const mterm& m)
{
    if (isZero(m.fCoef)) {
        // nothing to do
    } else if (isZero(fCoef)) {
        // copy of m
        fCoef    = m.fCoef;
        fFactors = m.fFactors;
    } else {
        // only add mterms of same signature
        faustassert(signatureTree() == m.signatureTree());
        fCoef = addNums(fCoef, m.fCoef);
    }
    cleanup();
    return *this;
}

/**
 * @brief Substract in place an mterm. As we want the result to be
 * a mterm therefore essentially mterms of same signature can be substracted
 */
/**
 * @brief Subtracts another mterm in-place. (New Documentation)
 *
 * Like addition, this is only valid for mterms with the same signature. It
 * subtracts the given mterm's coefficient from this mterm's coefficient.
 * @param m The mterm to subtract.
 * @return A const reference to the modified mterm (`*this`).
 */
const mterm& mterm::operator-=(const mterm& m)
{
    if (isZero(m.fCoef)) {
        // nothing to do
    } else if (isZero(fCoef)) {
        // minus of m
        fCoef    = minusNum(m.fCoef);
        fFactors = m.fFactors;
    } else {
        // only add mterms of same signature
        faustassert(signatureTree() == m.signatureTree());
        fCoef = subNums(fCoef, m.fCoef);
    }
    cleanup();
    return *this;
}

/**
 * @brief Multiply a mterm by the content of another mterm
 */
/**
 * @brief Multiplies by another mterm in-place. (New Documentation)
 *
 * The coefficients of the two mterms are multiplied, and the powers of their
 * common factors are added together.
 * @param m The mterm to multiply by.
 * @return A const reference to the modified mterm (`*this`).
 */
const mterm& mterm::operator*=(const mterm& m)
{
    fCoef = mulNums(fCoef, m.fCoef);
    for (const auto& p : m.fFactors) {
        fFactors[p.first] += p.second;
    }
    cleanup();
    return *this;
}

/**
 * @brief Divide a mterm by the content of another mterm
 */
/**
 * @brief Divides by another mterm in-place. (New Documentation)
 *
 * The coefficient is divided, and the powers of the divisor's factors are
 * subtracted from this mterm's corresponding factor powers.
 * @param m The mterm to divide by.
 * @return A const reference to the modified mterm (`*this`).
 */
const mterm& mterm::operator/=(const mterm& m)
{
    // cerr << "division en place : " << *this << " / " << m << endl;
    if (m.fCoef == nullptr) {
        stringstream error;
        error << "ERROR : division by 0 in " << *this << " / " << m << endl;
        throw faustexception(error.str());
    }
    fCoef = divExtendedNums(fCoef, m.fCoef);
    for (const auto& p : m.fFactors) {
        fFactors[p.first] -= p.second;
    }
    cleanup();
    return *this;
}

/**
 * @brief Multiply two mterms
 */
/**
 * @brief Returns the product of this mterm and another. (New Documentation)
 * @param m The mterm to multiply by.
 * @return A new `mterm` representing the product.
 */
mterm mterm::operator*(const mterm& m) const
{
    mterm r(*this);
    r *= m;
    return r;
}

/**
 * @brief Divide two mterms
 */
/**
 * @brief Returns the result of dividing this mterm by another. (New Documentation)
 * @param m The mterm to divide by.
 * @return A new `mterm` representing the quotient.
 */
mterm mterm::operator/(const mterm& m) const
{
    mterm r(*this);
    r /= m;
    return r;
}

/**
 * @brief Return the "common quantity" of two numbers
 */
/**
 * @brief Determines the common exponent for a factor when calculating a GCD. (New Documentation)
 *
 * This helper function is called by `gcd` to find the correct exponent for a
 * symbolic factor that is present in two different `mterm`s. The logic is designed
 * to find the "largest" factor that can be divided out from both terms.
 *
 * The rules are:
 * - **Positive Exponents**: If both exponents `a` and `b` are positive, the function
 * returns `min(a, b)`. For example, the greatest common divisor of `x^5` and `x^3` is `x^3`.
 *
 * - **Negative Exponents**: If both `a` and `b` are negative, the function returns
 * `max(a, b)` (the value closer to zero). For example, the greatest common divisor
 * of `x^-2` and `x^-4` is `x^-2`, as `x^-2 = x^-2 * 1` and `x^-4 = x^-2 * x^-2`.
 *
 * - **Mixed Signs**: If the exponents have different signs (or one is zero), there is no
 * common part that can be factored out in a simplifying way. The function returns `0`,
 * which causes the `gcd` function to exclude this factor from the result.
 *
 * @param a The exponent of the factor in the first mterm.
 * @param b The exponent of the factor in the second mterm.
 * @return The resulting exponent for the common factor in the GCD, or 0 if none.
 */
static int common(int a, int b)
{
    if ((a > 0) & (b > 0)) {
        return std::min(a, b);
    } else if ((a < 0) & (b < 0)) {
        return std::max(a, b);
    } else {
        return 0;
    }
}

/**
 * @brief Return a mterm that is the greatest common divisor of two mterms
 */
/**
 * @brief Computes the greatest common divisor (GCD) of two mterms. (New Documentation)
 *
 * This function is crucial for expression optimization, particularly for factorization.
 * It identifies the common symbolic parts between two multiplicative terms (`mterm`)
 * so that they can be factored out by the `aterm` class. For example, in an
 * expression like `a*b + a*c`, this function would identify `a` as the GCD,
 * enabling the expression to be simplified to `a*(b+c)`.
 *
 * The algorithm operates as follows:
 *
 * 1.  **Coefficient Simplification**: The process is focused on symbolic factors, so a
 * true numerical GCD of the coefficients is not calculated. The resulting
 * coefficient is set to 1, unless the two input coefficients have the exact
 * same magnitude, in which case the first term's coefficient is used.
 *
 * 2.  **Common Factor Identification**: It iterates through the factors of the first
 * term (`m1`). For each factor, it checks if the same factor exists in the
 * second term (`m2`).
 *
 * 3.  **Exponent Calculation**: If a factor is common to both terms, their
 * exponents are passed to the `common()` helper function.
 *
 * 4.  **Result Construction**: The common factor with its newly calculated exponent is
 * added to the result `mterm`, but only if the exponent is not zero.
 *
 * @param m1 The first mterm for the comparison.
 * @param m2 The second mterm for the comparison.
 * @return A new `mterm` representing the greatest common symbolic divisor.
 */
mterm gcd(const mterm& m1, const mterm& m2)
{
    // cerr << "GCD of " << m1 << " and " << m2 << endl;

    Tree  c = (sameMagnitude(m1.fCoef, m2.fCoef))
                  ? m1.fCoef
                  : tree(1);  // common coefficient (real gcd not needed)
    mterm R(c);
    for (const auto& p1 : m1.fFactors) {
        Tree               t  = p1.first;
        MP::const_iterator p2 = m2.fFactors.find(t);
        if (p2 != m2.fFactors.end()) {
            int v1 = p1.second;
            int v2 = p2->second;
            int c1 = common(v1, v2);
            if (c1 != 0) {
                R.fFactors[t] = c1;
            }
        }
    }
    // cerr << "GCD of " << m1 << " and " << m2 << " is : " << R << endl;
    return R;
}

/**
 * @brief We say that a "contains" b if a/b > 0. For example 3 contains 2 and
 * -4 contains -2, but 3 doesn't contains -2 and -3 doesn't contains 1
 */
/**
 * @brief Checks if integer `a` "contains" integer `b`. (New Documentation)
 *
 * "Contains" means that `b` can be factored out of `a` without changing signs.
 * This is true if `b` is zero or if `a` and `b` have the same sign.
 * It is used in `hasDivisor` to check if exponents are compatible for division.
 * @param a The dividend exponent.
 * @param b The divisor exponent.
 * @return True if `a` contains `b`.
 */
static bool contains(int a, int b)
{
    return (b == 0) || (a / b > 0);
}

/**
 * @brief Check if M accept N has a divisor. We can say that N is
 * a divisor of M if M = N*Q and the complexity is preserved :
 * complexity(M) = complexity(N)+complexity(Q)
 * x**u has divisor x**v if u >= v
 * x**-u has divisor x**-v if -u <= -v
 */
/**
 * @brief Checks if this mterm is cleanly divisible by another mterm `n`. (New Documentation)
 *
 * This function determines if `n` can be factored out of the current mterm.
 * Divisibility is defined not just mathematically, but in a way that preserves
 * simplification goals. For each factor `f^v` in `n`, this mterm must contain
 * a factor `f^u` where the exponent `u` "contains" `v` (i.e., they have the
 * same sign and `|u| >= |v|`).
 * @param n The potential divisor mterm.
 * @return True if this mterm has `n` as a divisor.
 */
bool mterm::hasDivisor(const mterm& n) const
{
    if (n.fFactors.size() == 0) {
        // n is a pure number
        return sameMagnitude(fCoef, n.fCoef);
    }
    for (const auto& p1 : n.fFactors) {
        // for each factor f**q of m
        Tree f = p1.first;
        int  v = p1.second;

        // check that f is also a factor of *this
        MP::const_iterator p2 = fFactors.find(f);
        if (p2 == fFactors.end()) {
            return false;
        }

        // analyze quantities
        int u = p2->second;
        if (!contains(u, v)) {
            return false;
        }
    }
    // cerr << __LINE__ << ":" << __func__ << *this << " is divisible by " << n << endl;
    return true;
}

/**
 * @brief Produce the canonical tree corresponding to a mterm
 */

/**
 * @brief Build a power term of type f**q -> (((f.f).f)..f) with q>0
 */
/**
 * @brief Builds a power term `f**q` where `q` > 0. (New Documentation)
 * @param f The base tree.
 * @param q The positive integer exponent.
 * @return A tree representing `f` if `q` is 1, or `f**q` otherwise.
 */
static Tree buildPowTerm(Tree f, int q)
{
    faustassert(f);
    faustassert(q > 0);
    if (q > 1) {
        return sigPow(f, q);
    } else {
        return f;
    }
}

/**
 * @brief Combine R and A doing R = R*A or R = A
 */
/**
 * @brief Helper to combine two trees with multiplication. (New Documentation)
 *
 * If `R` is an existing tree, the result is `R * A`.
 * If `R` is null, the result is `A`.
 * @param[in,out] R The tree to be multiplied into.
 * @param A The tree to multiply.
 */
static void combineMulLeft(Tree& R, Tree A)
{
    if (R && A) {
        R = sigMul(R, A);
    } else if (A) {
        R = A;
    } else {
        cerr << "ERROR : combineMulLeft\n";
        faustassert(false);
    }
}

/**
 * @brief Combine R and A doing R = R/A or R = A
 */
/**
 * @brief Helper to combine two trees with division. (New Documentation)
 *
 * If `R` is an existing tree, the result is `R / A`.
 * If `R` is null, the result is `1 / A`.
 * @param[in,out] R The numerator tree.
 * @param A The denominator tree.
 */
static void combineDivLeft(Tree& R, Tree A)
{
    if (R && A) {
        R = sigDiv(R, A);
    } else if (A) {
        R = sigDiv(tree(1.0f), A);
    } else {
        cerr << "ERROR : combineDivLeft\n";
        faustassert(false);
    }
}

/**
 * @brief Do M = M * f**q or D = D * f**-q
 */
/**
 * @brief Adds a factor `f**q` to a numerator/denominator pair of trees. (New Documentation)
 *
 * This function is used during tree reconstruction in `normalizedTree`.
 * If `q` is positive, `f**q` is multiplied into the numerator tree `M`.
 * If `q` is negative, `f**(-q)` is multiplied into the denominator tree `D`.
 * @param[in,out] M The numerator tree.
 * @param[in,out] D The denominator tree.
 * @param f The factor's base tree.
 * @param q The factor's exponent.
 */
static void combineMulDiv(Tree& M, Tree& D, Tree f, int q)
{
#ifdef TRACE
    cerr << "combineMulDiv (" << M << "/" << D << "*" << ppsig(f) << "**" << q << endl;
#endif
    if (f) {
        faustassert(q != 0);
        if (q > 0) {
            combineMulLeft(M, buildPowTerm(f, q));
        } else if (q < 0) {
            combineMulLeft(D, buildPowTerm(f, -q));
        }
    }
}

/**
 * @brief Returns a normalized (canonical) tree expression of structure :
 * ((v1/v2)*(c1/c2))*(s1/s2)
 */
/**
 * @brief Returns the signature tree of the mterm. (New Documentation)
 *
 * The signature is a canonical tree representing the symbolic part of the
 * mterm (all factors and their powers), ignoring the numerical coefficient.
 * It is crucial for identifying "like terms" that can be simplified in an `aterm`.
 * This is a convenience method that calls `normalizedTree(true)`.
 * @return A `Tree` representing the mterm's signature.
 */
Tree mterm::signatureTree() const
{
    return normalizedTree(true);
}

/**
 * @brief Returns a normalized (canonical) tree expression of structure :
 * ((k*(v1/v2))*(c1/c2))*(s1/s2)
 * In signature mode the fCoef factor is ommited
 * In negativeMode the sign of the fCoef factor is inverted
 */
/**
 * @brief Reconstructs a canonical Faust expression tree from the mterm's internal state. (New
 * Documentation)
 *
 * This function is the counterpart to the `mterm` constructor; it converts the
 * internal representation (a coefficient and a map of factors) back into a
 * standard, simplified Faust expression tree. The resulting tree is "normalized,"
 * meaning it has a canonical structure that helps in subsequent compilation stages.
 *
 * The normalization process involves:
 * 1.  **Factor Sorting by Order**: Symbolic factors are first sorted into groups based
 * on their "signal order" (e.g., constant, control-rate, signal-rate).
 * This ensures that expressions are always built in the same way, for instance,
 * with signal-rate components appearing before control-rate components.
 *
 * 2.  **Numerator/Denominator Separation**: Factors with positive exponents are collected
 * as numerators, while those with negative exponents are collected as denominators.
 *
 * 3.  **Coefficient Handling**: The mterm's numerical coefficient is handled based on the
 * function's parameters. It can be included, ignored (in signature mode), or inverted.
 *
 * 4.  **Tree Assembly**: The sorted parts are combined into a final expression tree,
 * typically of the form `(coefficient * Numerator) / Denominator`.
 *
 * @param signatureMode If true, the `fCoef` factor is ignored (effectively treated as 1).
 * This is used to generate a tree representing only the symbolic part of the mterm,
 * which is essential for identifying like terms.
 *
 * @param negativeMode If true, the sign of the `fCoef` is inverted in the resulting tree.
 * This is used when reconstructing negative terms in an `aterm`.
 *
 * @return A normalized, canonical Faust expression `Tree`.
 */
Tree mterm::normalizedTree(bool signatureMode, bool negativeMode) const
{
#ifdef TRACE
    cout << "normalizedTree " << *this << endl;
#endif

    if (fFactors.empty() || isZero(fCoef)) {
        // it's a pure number
        if (signatureMode) {
            return tree(1);
        }
        if (negativeMode) {
            return minusNum(fCoef);
        } else {
            return fCoef;
        }
    } else {
        // it's not a pure number, it has factors
        Tree A[4], B[4];

        // group by order
        for (int order = 0; order < 4; order++) {
            A[order] = 0;
            B[order] = 0;
            for (const auto& p : fFactors) {
                Tree f = p.first;   // f = factor
                int  q = p.second;  // q = power of f
                if (f && q && getSigOrder(f) == order) {
                    combineMulDiv(A[order], B[order], f, q);
                }
            }
        }
#if 1
        if (A[0] != 0) {
            cerr << "A[0] == " << *A[0] << endl;
        }
        if (B[0] != 0) {
            cerr << "B[0] == " << *B[0] << endl;
        }
        // in principle here zero order is empty because it corresponds to the numerical coef
        faustassert(A[0] == nullptr);
        faustassert(B[0] == nullptr);
#endif

        // we only use a coeficient if it differs from 1 and if we are not in signature mode
        if (!(signatureMode || isOne(fCoef))) {
            A[0] = (negativeMode) ? minusNum(fCoef) : fCoef;
        }

        if (signatureMode) {
            A[0] = 0;
        } else if (negativeMode) {
            if (isMinusOne(fCoef)) {
                A[0] = 0;
            } else {
                A[0] = minusNum(fCoef);
            }
        } else if (isOne(fCoef)) {
            A[0] = 0;
        } else {
            A[0] = fCoef;
        }

        // combine each order separately : R[i] = A[i]/B[i]
        Tree RR = 0;
        for (int order = 0; order < 4; order++) {
            if (A[order] && B[order]) {
                combineMulLeft(RR, sigDiv(A[order], B[order]));
            } else if (A[order]) {
                combineMulLeft(RR, A[order]);
            } else if (B[order]) {
                combineDivLeft(RR, B[order]);
            }
        }
        if (RR == nullptr) {
            RR = tree(1);  // to check *******************
        }

        faustassert(RR);
#ifdef TRACE
        cout << "Normalized Tree of " << *this << " is " << ppsig(RR) << endl;
#endif
        return RR;
    }
}
