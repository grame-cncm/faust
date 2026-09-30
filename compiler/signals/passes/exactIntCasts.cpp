#include "exactIntCasts.hh"

#include <cmath>
#include <cstdint>

#include "rewrite.hh"
#include "sigs-state.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"

/*
 A real coefficient c, as the normal form writes it, is often the double
 rounding of a rational p/q : a ratio of two sampling rates, a delay in samples
 divided by the rate it was tuned at. When a program converts c*Y to an integer
 (a delay length, a table size), the product is rounded twice, once in c and
 once in c*Y, and an integer result can land one ulp below the integer and be
 truncated one unit short. (p*Y)/q is rounded once when p*Y is exact : the
 division is correctly rounded, so an exact integer quotient is found exactly.

 Conditions, all checked on the original node :
   - the node is int(x), x a product whose leftmost factor is the real c
     (the normal form writes the coefficient first, the products nested left) ;
   - x is computed outside the sample loop : the division costs nothing there ;
   - c = p/q exactly after rounding to double, |p| and q below 2^24 (exact in
     single precision too), q not a power of two (c would be exact) ;
   - |p| * max|Y| stays below 2^m, m the mantissa of the precision (24 or 53),
     max|Y| taken from the interval of x : for an integer-valued Y (a sampling
     rate), p*Y is then exact.
*/

namespace {

constexpr double kMaxTerm = 16777216.0;  // 2^24

// p/q with (double)p/q == c, |p| and q below 2^24, found by continued fraction ;
// false when there is none
bool smallRational(double c, double& p, double& q)
{
    double v = std::fabs(c);
    double h0 = 0, h1 = 1, k0 = 1, k1 = 0;
    for (int n = 0; n < 64 && std::isfinite(v); n++) {
        double a  = std::floor(v);
        double h2 = a * h1 + h0;
        double k2 = a * k1 + k0;
        if (h2 >= kMaxTerm || k2 >= kMaxTerm) {
            return false;
        }
        if (h2 / k2 == std::fabs(c)) {
            p = c < 0 ? -h2 : h2;
            q = k2;
            return true;
        }
        double frac = v - a;
        if (frac == 0) {
            return false;
        }
        v  = 1 / frac;
        h0 = h1;
        h1 = h2;
        k0 = k1;
        k1 = k2;
    }
    return false;
}

bool isPowerOfTwo(double q)
{
    int e;
    return std::frexp(q, &e) == 0.5;
}

// the leftmost factor of a product nested left, or nullptr when t is not a product
Tree leftmostFactor(Tree t)
{
    int  op;
    Tree a, b;
    bool product = false;
    while (isSigBinOp(t, &op, a, b) && op == kMul) {
        t       = a;
        product = true;
    }
    return product ? t : nullptr;
}

// the product t with its leftmost factor (a real) replaced by p, dropped when p is 1
Tree rescaled(Tree t, double p)
{
    int  op;
    Tree a, b;
    if (isSigBinOp(t, &op, a, b) && op == kMul) {
        double c;
        if (isSigReal(a, &c)) {
            return p == 1 ? b : sigBinOp(kMul, sigReal(p), b);
        }
        return sigBinOp(kMul, rescaled(a, p), b);
    }
    return t;
}

}  // namespace

Tree exactIntCasts(Tree L)
{
    const int mantissa = sigs::g.gFloatSize == 1 ? 24 : 53;

    auto rule = [&](Tree orig, Tree rebuilt) -> Tree {
        Tree x, rx;
        if (!isSigIntCast(orig, x) || !isSigIntCast(rebuilt, rx)) {
            return rebuilt;
        }
        Tree   leaf = leftmostFactor(x);
        double c, p, q;
        if (!leaf || !isSigReal(leaf, &c) || !smallRational(c, p, q) || q == 1 || isPowerOfTwo(q)) {
            return rebuilt;
        }
        Type t = getSigType(x);
        if (!t || t->variability() == kSamp) {
            return rebuilt;
        }
        auto I = t->getInterval();
        if (!I.isValid() || !std::isfinite(I.lo()) || !std::isfinite(I.hi())) {
            return rebuilt;
        }
        double maxY = std::max(std::fabs(I.lo()), std::fabs(I.hi())) / std::fabs(c);
        if (std::fabs(p) * maxY >= std::ldexp(1.0, mantissa)) {
            return rebuilt;
        }
        Tree rleaf = leftmostFactor(rx);
        double rc;
        if (!rleaf || !isSigReal(rleaf, &rc) || rc != c) {
            return rebuilt;
        }
        return sigIntCast(sigBinOp(kDiv, rescaled(rx, p), sigReal(q)));
    };
    return treeRewriteMinimalPaired(L, rule);
}
