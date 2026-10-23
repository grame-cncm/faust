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

#include "mterm.hh"
#include "sigs-state.hh"
#include "exception.hh"
#include "global.hh"
#include "ppsig.hh"
#include "signals.hh"
#include "xtended.hh"
#include "double_double.hh"

using namespace std;

typedef map<Tree, int, treeorder> MP;

/**
 * The coefficient c + clo op (t + tlo), folded as exactly as possible : in double-double when
 * the result is a real, its hi the tree of the coefficient (the value rounded once), its lo
 * the error kept for the next operations ; plain is the result of the operation on the
 * trees, kept as it is otherwise (an int, an infinity...).
 */
static void foldCoef(Tree& c, double& clo, Tree t, double tlo, Tree plain,
                     itv::DoubleDouble (*op)(itv::DoubleDouble, itv::DoubleDouble))
{
    // the value of a number node, an int or a double (an int64 is left to the plain result)
    auto value = [](Tree n, double& v) {
        const Node& x = n->node();
        if (x.type() == kDoubleNode) {
            v = x.getDouble();
            return true;
        }
        if (x.type() == kIntNode) {
            v = double(x.getInt());
            return true;
        }
        return false;
    };
    double a, b;
    if (plain->node().type() == kDoubleNode && value(c, a) && value(t, b)) {
        const itv::DoubleDouble r = op({a, clo}, {b, tlo});
        if (std::isfinite(r.hi)) {
            c   = tree(r.hi);
            clo = r.lo;
            return;
        }
    }
    c   = plain;
    clo = 0.0;
}

mterm::mterm() : fCoef(sigInt(0))
{
}
mterm::mterm(int k) : fCoef(sigInt(k))
{
}
mterm::mterm(double k) : fCoef(sigReal(k))
{
}
mterm::mterm(const mterm& m) : fCoef(m.fCoef), fLo(m.fLo), fFactors(m.fFactors)
{
}

/**
 * Create a mterm from a tree expression
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
 * true if mterm doesn't represent number 0
 */
bool mterm::isNotZero() const
{
    return !isZero(fCoef);
}

/**
 * true if the mterm is coef*factor : a single factor, of power 1
 */
bool mterm::isScaledFactor(Tree& coef, Tree& factor) const
{
    if (fFactors.size() != 1 || fFactors.begin()->second != 1) {
        return false;
    }
    coef   = fCoef;
    factor = fFactors.begin()->first;
    return true;
}

/**
 * the factors of power 1, in the order of the term
 */
std::vector<Tree> mterm::unitFactors() const
{
    std::vector<Tree> r;
    for (const auto& p : fFactors) {
        if (p.second == 1) {
            r.push_back(p.first);
        }
    }
    return r;
}

/**
 * true if the term holds g and (g + 1)^-k : the gain of a trapezoidal integrator,
 * g / (g + 1), can be taken out of it
 */
bool mterm::tptFactors(Tree& g, Tree& d) const
{
    for (const auto& p : fFactors) {
        int  op;
        Tree l, r;
        tvec subs;
        if (p.second >= 0) {
            continue;
        }
        if (isSigSum(p.first, subs) && subs.size() == 2) {
            l = subs[0];  // g + 1, as the normal form writes it
            r = subs[1];
        } else if (!isSigBinOp(p.first, &op, l, r) || op != kAdd) {
            continue;
        }
        Tree x = isOne(r) ? l : (isOne(l) ? r : nullptr);
        if (x == nullptr || isNum(x)) {
            continue;
        }
        auto it = fFactors.find(x);
        if (it != fFactors.end() && it->second >= 1) {
            g = x;
            d = p.first;
            return true;
        }
    }
    return false;
}

/**
 * true if the term is c * x@k : one factor of order 3 or more, of power 1, the source x
 * delayed by a constant k >= 0 (x itself, or x@0, for k = 0), and a coefficient c, the other
 * factors, all of them of order 2 or less (constant in the sample : a FIR multiplies the
 * sample of x read k samples ago by the coefficient of the current sample)
 */
bool mterm::tapOf(Tree& source, int& delay, mterm& coef) const
{
    if (isZero(fCoef)) {
        return false;
    }
    Tree f = nullptr;
    for (const auto& p : fFactors) {
        if (sigs::sigOrder(p.first) >= 3) {
            if (f != nullptr || p.second != 1) {
                return false;
            }
            f = p.first;
        }
    }
    if (f == nullptr) {
        return false;
    }
    // (a recursive projection read at delay 0 is written x@0 by the normal form)
    Tree x, d;
    int  k;
    if (isSigDelay(f, x, d) && isSigInt(d, &k) && k >= 0) {
        source = x;
        delay  = k;
    } else {
        source = f;
        delay  = 0;
    }
    if (isNum(source)) {
        return false;  // a delayed constant is a step, not a tap
    }
    coef = *this / mterm(f);
    return true;
}

/**
 * this without the factors that q holds (with a non null power), coefficient kept
 */
mterm mterm::withoutFactorsOf(const mterm& q) const
{
    mterm r(*this);
    for (const auto& p : q.fFactors) {
        if (p.second != 0) {
            r.fFactors.erase(p.first);
        }
    }
    return r;
}

/**
 * true if mterm is strictly negative
 */
bool mterm::isNegative() const
{
    return !isGEZero(fCoef);
}

/**
 * Print a mterm in a human readable format
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
 * Compute the "complexity" of a mterm, that is the number of
 * factors it contains (weighted by the importance of these factors)
 */
int mterm::complexity() const
{
    int c = isOne(fCoef) ? 0 : (isMinusOne(fCoef) ? 0 : 1);
    for (const auto& p : fFactors) {
        c += (1 + sigs::sigOrder(p.first)) * abs(p.second);
    }
    // cerr << __LINE__ << ":" << __FUNCTION__ << "(" << *this << ") --> " << c << endl;
    return c;
}

/**
 * Match x^p with p:int, or p a real holding an integer in [1, 8] : the promotion makes the
 * exponent of a real base real (x^2 is pow(x, 2.0)), and the generator writes such a power
 * as the product of its factors, as x * x
 */
static bool isSigPow(Tree sig, Tree& x, int& n)
{
    xtended* p = (xtended*)getUserData(sig);
    if (p == gGlobal->gPowPrim) {
        double r;
        if (isSigInt(sig->branch(1), &n)) {
            x = sig->branch(0);
            return true;
        } else if (isSigReal(sig->branch(1), &r) && r >= 1 && r <= 8 && r == double(int(r))) {
            n = int(r);
            x = sig->branch(0);
            return true;
        }
    }
    return false;
}

/**
 * Produce x^p with p:int
 */
static Tree sigPow(Tree x, int p)
{
    return tree(gGlobal->gPowPrim->symbol(), x, sigInt(p));
}

/**
 * Multiply a mterm by an expression tree. Go down recursively looking
 * for multiplications and divisions
 */
const mterm& mterm::operator*=(Tree t)
{
    int  op, n;
    Tree x, y;

    faustassert(t);

    if (isNum(t)) {
        foldCoef(fCoef, fLo, t, 0.0, mulNums(fCoef, t), itv::ddMul);

    } else if (isSigBinOp(t, &op, x, y) && (op == kMul)) {
        *this *= x;
        *this *= y;

    } else if (tvec fs; isSigProd(t, fs)) {
        for (Tree f : fs) *this *= f;

    } else if (isSigBinOp(t, &op, x, y) && (op == kDiv)) {
        *this *= x;
        *this /= y;

    } else if (isSigNeg(t, x)) {
        fCoef = minusNum(fCoef);
        fLo   = -fLo;
        *this *= x;

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
 * Divide a mterm by an expression tree t. Go down recursively looking
 * for multiplications and divisions
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
        foldCoef(fCoef, fLo, t, 0.0, divExtendedNums(fCoef, t), itv::ddDiv);

    } else if (isSigBinOp(t, &op, x, y) && (op == kMul)) {
        *this /= x;
        *this /= y;

    } else if (tvec fs; isSigProd(t, fs)) {
        for (Tree f : fs) *this /= f;

    } else if (isSigBinOp(t, &op, x, y) && (op == kDiv)) {
        *this /= x;
        *this *= y;

    } else if (isSigNeg(t, x)) {
        fCoef = minusNum(fCoef);
        fLo   = -fLo;
        *this /= x;

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
 * Replace the content with a copy of m
 */
const mterm& mterm::operator=(const mterm& m)
{
    fCoef    = m.fCoef;
    fLo      = m.fLo;
    fFactors = m.fFactors;
    return *this;
}

/**
 * Clean a mterm by removing x**0 factors
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
 * Add in place an mterm. As we want the result to be
 * a mterm therefore essentially mterms of same signature can be added
 */
const mterm& mterm::operator+=(const mterm& m)
{
    if (isZero(m.fCoef)) {
        // nothing to do
    } else if (isZero(fCoef)) {
        // copy of m
        fCoef    = m.fCoef;
        fLo      = m.fLo;
        fFactors = m.fFactors;
    } else {
        // only add mterms of same signature
        Tree s1 = signatureTree();
        Tree s2 = m.signatureTree();
        faustassert(s1 == s2);
        foldCoef(fCoef, fLo, m.fCoef, m.fLo, addNums(fCoef, m.fCoef), itv::ddAdd);
    }
    cleanup();
    return *this;
}

/**
 * Substract in place an mterm. As we want the result to be
 * a mterm therefore essentially mterms of same signature can be substracted
 */
const mterm& mterm::operator-=(const mterm& m)
{
    if (isZero(m.fCoef)) {
        // nothing to do
    } else if (isZero(fCoef)) {
        // minus of m
        fCoef    = minusNum(m.fCoef);
        fLo      = -m.fLo;
        fFactors = m.fFactors;
    } else {
        // only add mterms of same signature
        Tree s1 = signatureTree();
        Tree s2 = m.signatureTree();
        faustassert(s1 == s2);
        foldCoef(fCoef, fLo, m.fCoef, m.fLo, subNums(fCoef, m.fCoef), itv::ddSub);
    }
    cleanup();
    return *this;
}

/**
 * Multiply a mterm by the content of another mterm
 */
const mterm& mterm::operator*=(const mterm& m)
{
    foldCoef(fCoef, fLo, m.fCoef, m.fLo, mulNums(fCoef, m.fCoef), itv::ddMul);
    for (const auto& p : m.fFactors) {
        fFactors[p.first] += p.second;
    }
    cleanup();
    return *this;
}

/**
 * Divide a mterm by the content of another mterm
 */
const mterm& mterm::operator/=(const mterm& m)
{
    // cerr << "division en place : " << *this << " / " << m << endl;
    if (m.fCoef == nullptr) {
        stringstream error;
        error << "ERROR : division by 0 in " << *this << " / " << m << endl;
        throw faustexception(error.str());
    }
    foldCoef(fCoef, fLo, m.fCoef, m.fLo, divExtendedNums(fCoef, m.fCoef), itv::ddDiv);
    for (const auto& p : m.fFactors) {
        fFactors[p.first] -= p.second;
    }
    cleanup();
    return *this;
}

/**
 * Multiply two mterms
 */
mterm mterm::operator*(const mterm& m) const
{
    mterm r(*this);
    r *= m;
    return r;
}

/**
 * Divide two mterms
 */
mterm mterm::operator/(const mterm& m) const
{
    mterm r(*this);
    r /= m;
    return r;
}

/**
 * Return the "common quantity" of two numbers
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
 * Return a mterm that is the greatest common divisor of two mterms
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
 * We say that a "contains" b if a/b > 0. For example 3 contains 2 and
 * -4 contains -2, but 3 doesn't contains -2 and -3 doesn't contains 1
 */
static bool contains(int a, int b)
{
    return (b == 0) || (a / b > 0);
}

/**
 * Check if M accept N has a divisor. We can say that N is
 * a divisor of M if M = N*Q and the complexity is preserved :
 * complexity(M) = complexity(N)+complexity(Q)
 * x**u has divisor x**v if u >= v
 * x**-u has divisor x**-v if -u <= -v
 */
/**
 * this divided by n stays a product, its divisions included : every factor of n with a
 * positive power divides this ; a factor with a negative power (a ratio : the mterm of
 * 44.1/SR is 44.1 * SR^-1) passes to the quotient as a product (44.1 * d / (44.1 * SR^-1) is
 * d * SR), which creates no division
 */
bool mterm::hasDivisorUpToReciprocals(const mterm& n) const
{
    if (n.fFactors.size() == 0) {
        return sameMagnitude(fCoef, n.fCoef);
    }
    for (const auto& p1 : n.fFactors) {
        if (p1.second < 0) {
            continue;
        }
        MP::const_iterator p2 = fFactors.find(p1.first);
        if (p2 == fFactors.end() || !contains(p2->second, p1.second)) {
            return false;
        }
    }
    return true;
}

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
 * Produce the canonical tree corresponding to a mterm
 */

/**
 * Build a power term of type f**q -> (((f.f).f)..f) with q>0
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
 * Returns a normalized (canonical) tree expression of structure :
 * 		Prod(v1/v2, c1/c2, s1/s2)
 */
Tree mterm::signatureTree() const
{
    return normalizedTree(true);
}

/**
 * Returns a normalized (canonical) tree expression of structure :
 * 		Prod(k, v1/v2, c1/c2, s1/s2), each part a Prod of its factors
 * In signature mode the fCoef factor is ommited
 * In negativeMode the sign of the fCoef factor is inverted
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
        // the numerator and denominator factors of each order, in the order of the term
        std::vector<Tree> A[5], B[5];
        for (int order = 0; order < 5; order++) {
            for (const auto& p : fFactors) {
                Tree f = p.first;   // f = factor
                int  q = p.second;  // q = power of f
                // level 4 capped to 3 HERE : the late state-join pays in
                // SUMS (aterm) ; in products the state factor's position is
                // recMII-neutral and the regrouping only flips clang's
                // scheduling luck (brightOrgan bisection, exp-rec4)
                if (f && q && std::min(sigs::sigOrder(f), 3) == order) {
                    if (q > 0) {
                        A[order].push_back(buildPowTerm(f, q));
                    } else {
                        B[order].push_back(buildPowTerm(f, -q));
                    }
                }
            }
        }
        // in principle here zero order is empty because it corresponds to the numerical coef
        faustassert(A[0].empty());
        faustassert(B[0].empty());

        // a negative coefficient written positively is the negation of the opposite : the
        // sign is carried by neg, the magnitude by the positive writing (-2x = neg(2x))
        if (!signatureMode && !negativeMode && isNegative()) {
            Tree opp = normalizedTree(false, true);
            return sigNeg(opp);
        }
        Tree       coef   = nullptr;
        if (signatureMode) {
            coef = nullptr;
        } else if (negativeMode) {
            coef = isMinusOne(fCoef) ? nullptr : minusNum(fCoef);
        } else if (!isOne(fCoef)) {
            coef = fCoef;
        }

        // Prod(f0, ..., fn) is the chain ((f0 * f1) * ...) * fn. The coefficient, then the
        // orders ascending, each one R = A / B, so the audio-recursive factors (order 4)
        // multiply nearest the root, off every slower factor's path ; an order with a
        // denominator only divides the product so far.
        auto product = [](const std::vector<Tree>& fs) -> Tree {
            if (fs.empty()) return nullptr;
            return (fs.size() == 1) ? fs[0] : sigProd(fs);
        };
        std::vector<Tree> chain;
        if (coef) {
            chain.push_back(coef);
        }
        for (int order = 0; order < 5; order++) {
            Tree a = product(A[order]);
            Tree b = product(B[order]);
            if (a && b) {
                chain.push_back(sigDiv(a, b));
            } else if (a) {
                chain.push_back(a);
            } else if (b) {
                Tree num = chain.empty() ? tree(1.0f) : product(chain);
                Tree d   = sigDiv(num, b);
                chain    = {d};
            }
        }
        Tree RR = chain.empty() ? tree(1) : product(chain);

        faustassert(RR);
#ifdef TRACE
        cout << "Normalized Tree of " << *this << " is " << ppsig(RR) << endl;
#endif
        return RR;
    }
}
