/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2024 INRIA
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
 * @file sigIIR.cpp
 * @author Yann ORLAREY (yann.orlarey@inria.fr)
 * @brief Operations and predicats for IIR signals: [Vi, X, C0, C1, C2, ...] ==> Vi = X + C0*Vi
 * C1*Vi@1 + C2*Vi@2 + ...
 * @version 0.1
 * @date 2024-01-15
 *
 * @copyright Copyright (c) 2024 INRIA
 *
 */

/*
Vi: recursive group variable V, projection i
X : non recursive input signal
Cj: coefficients

Main rules:
-----------
(R1) Vi --> [Vi 0 1] -> Vi = 0 + 1*Vi = Vi
(R2) [Vi X C0 C1...]@d -> [Vi X@d 0 0 ... C0@d C1@d...] -> Vi = X + C0@d*Vi@d + C1@d*Vi@(d+1 + ...
if Ci constant, then (Ci@d)*(Vi@(d+k)) = Ci*(Vi@(d+k)) PROOF t<d+k : Vi@(d+k) = 0 => Ci@d*0 = Ci*0
                                                             t>=d+k: Ci@d = Ci

*/
#include <cmath>
#include <complex>
#include <iostream>
#include <limits>
#include <vector>

#include "ppsig.hh"
#include "sigIIR.hh"
#include "sigtyperules.hh"
#include "simplify.hh"

// for test purposes
#include "occurrences.hh"
#include "recursivness.hh"
#include "sharing.hh"

#define TRACE 1
// We use nil to indicate that a recursive expression is not representable by an IIR
bool hasNonValidArgs(Tree sig)
{
    if (isNil(sig)) {
        return true;
    }
    for (Tree b : sig->branches()) {
        if (isNil(b)) {
            return true;
        }
    }
    return false;
}

// Check if a signal sub-expression is a concerned IIR
bool hasConcernedIIRArgs(Tree rt, Tree sig)
{
    if (isSigIIR(sig)) {
        return true;
    } else {
        for (Tree b : sig->branches()) {
            if (tvec coef; concernedIIR(rt, b, coef)) {
                return true;
            }
        }
        return false;
    }
}

//-------------------------------------------------------------------------
// True if a signal represents a number, and if so,
// the number is returned as an int.
static bool isSigNum(Tree sig, int& n)
{
    int    i;
    double d;

    if (isSigInt(sig, &i)) {
        n = i;
        return true;
    } else if (isSigReal(sig, &d)) {
        n = (int)d;
        return true;
    } else {
        return false;
    }
}

//-------------------------------------------------------------------------
// compare two rec proj.
// - 0 if they are the same,
// - 1 if they are different and
// - -1 if they are in the same recursive group but different projections
static int compareRecProj(Tree x, Tree y)
{
    int  ix, iy;
    Tree rx = nullptr;
    Tree ry = nullptr;

    faustassert(isProj(x, &ix, rx) && isProj(y, &iy, ry));

    if (rx != ry) {
        return 1;  // different recursive groups
    }
    if (ix != iy) {
        return -1;  // same recursive group but different projections
    }
    return 0;  // same recursive group and same projection
}

//-------------------------------------------------------------------------
// delay coefficients only when needed
static Tree delayCoef(Tree c, int d)
{
    if (int n; isSigInt(c, &n)) {
        return c;  // no need to delay constant int coefficients
    } else if (double x; isSigReal(c, &x)) {
        return c;  // no need to delay constant real coefficients
    }
    // non constant coefficients need to be delayed
    return sigDelay(c, sigInt(d));
}

//-------------------------------------------------------------------------
// Create an IIR from a recursive variable projection Vi
// Vi --> [Vi 0 1] -> Vi = 0 + 1*Vi = Vi

Tree proj2SigIIR(Tree rt, Tree sig)
{
    Tree tg, sg;
    int  ti, si;

    faustassert(isProj(rt, &ti, tg));
    faustassert(isProj(sig, &si, sg));

    if (rt == sig) {
        // same recursive variable, can be represented by an IIR
        tvec coef = {sig, sigInt(0), sigInt(1)};
        return sigIIR(coef);
    } else if (tg == sg) {
        // same group but different projection, can't be represente as an IIR
        return gGlobal->nil;
    } else {
        // not recursive with respect to rt
        return sig;
    }
}

//-------------------------------------------------------------------------
// Delay an IIR by d samples
// [Vi X C0 C1...]@d -> [Vi X@d 0 0 ... C0@d C1@d...] -> Vi = X + C0@d*Vi@d + C1@d*Vi@(d+1 + ...
Tree delayIIRCoef(tvec& coef, int d)
{
    tvec coef2 = {coef[0], delayCoef(coef[1], d)};
    // push d zeros coefficients
    for (int ii = 0; ii < d; ii++) {
        coef2.push_back(sigInt(0));
    }
    // push the ci@d coefficients
    for (unsigned int ii = 2; ii < coef.size(); ii++) {
        coef2.push_back(delayCoef(coef[ii], d));
    }
    return sigIIR(coef2);
}

//-------------------------------------------------------------------------
// Returns true if x is an IIR concerning recursive variable rt
bool concernedIIR(Tree rt, Tree x, tvec& coef)
{
    if (isSigIIR(x, coef)) {
        return coef[0] == rt;
    } else {
        return false;
    }
}

//-------------------------------------------------------------------------
// Create an IIR from a delayed signal if the delay is constant
Tree delaySigIIR_real(Tree rt, Tree x, Tree y)
{
    tvec coef1, coef2;
    bool cx = concernedIIR(rt, x, coef1);
    bool cy = concernedIIR(rt, y, coef2);
    if (cy) {
        return gGlobal->nil;  // a signal delay by a concerned IIR can't be expressed has an IIR
    }
    if (cx) {
        if (int d; isSigNum(y, d)) {
            return delayIIRCoef(coef1, d);  // we can delay the IIR
        } else {
            return gGlobal->nil;  // can't be expressed as an IIR
        }
    }
    return sigDelay(x, y);  // x and y are not concerned IIR, normal delay
}

Tree delaySigIIR(Tree rt, Tree x, Tree y)
{
    if (TRACE) {
        std::cerr << "delaySigIIR: " << rt << ", " << ppsig(x) << " by " << ppsig(y) << "\n";
    }
    Tree res = delaySigIIR_real(rt, x, y);
    if (TRACE) {
        std::cerr << "delaySigIIR: " << rt << ", " << ppsig(x) << " by " << ppsig(y) << " ==> "
                  << ppsig(res) << "\n";
    }
    return res;
}

//-------------------------------------------------------------------------
// Add two IIRs, or sigAdd(s1,s2) if s1 and s2 are not concerned IIRs
// Assume x and y are not nil
Tree addSigIIR_real(Tree rt, Tree x, Tree y)
{
    tvec coef1, coef2;
    bool cx = concernedIIR(rt, x, coef1);
    bool cy = concernedIIR(rt, y, coef2);
    if (cx && cy) {
        // we have two concerned IIRs, we can add them together
        // [v, a, c0, c1, c2, ...] + [v, b, d0, d1, d2, ...] -> [v, a+b, c0+d0, c1+d1, c2+d2, ...]
        tvec coef;
        coef.push_back(coef1[0]);  // Vi
        unsigned int n = std::min(coef1.size(), coef2.size());
        // add coefficients of the same order
        for (unsigned int i = 1; i < n; i++) {
            coef.push_back(simplify(sigAdd(coef1[i], coef2[i])));
        }
        // copy coefficients of the longuest IIR
        for (unsigned int i = n; i < coef1.size(); i++) {
            coef.push_back(coef1[i]);
        }
        for (unsigned int i = n; i < coef2.size(); i++) {
            coef.push_back(coef2[i]);
        }
        return sigIIR(coef);
    } else if (cx) {
        // x is a concerned IIR but y is not, we add y to the input signal of x
        // [v, a, c0, c1, c2, ...] + y -> [v, a+y, c0, c1, c2, ...]
        coef1[1] = simplify(sigAdd(coef1[1], y));
        return sigIIR(coef1);
    } else if (cy) {
        // x is not concerned, but y is, we add x to the input signal of y
        // x + [v, b, c0, c1, c2, ...] -> [v, x+b, c0, c1, c2, ...]
        coef2[1] = simplify(sigAdd(coef2[1], x));  // add x to the input signal of the IIR
        return sigIIR(coef2);
    } else {
        // x and y are unrelated to the recursive variable
        return simplify(sigAdd(x, y));
    }
}

Tree addSigIIR(Tree rt, Tree x, Tree y)
{
    if (TRACE) {
        std::cerr << "addSigIIR: " << rt << ", " << ppsig(x) << " by " << ppsig(y) << "\n";
    }
    Tree res = addSigIIR_real(rt, x, y);
    if (TRACE) {
        std::cerr << "addSigIIR: " << rt << ", " << ppsig(x) << " by " << ppsig(y) << " ==> "
                  << ppsig(res) << "\n";
    }
    return res;
}

//-------------------------------------------------------------------------
// Sub two IIRs, or sigSub(s1,s2) if s1 and s2 are not concernedIIRs
// Assume x and y are not nil
Tree subSigIIR_real(Tree rt, Tree x, Tree y)
{
    tvec coef1, coef2;
    bool cx = concernedIIR(rt, x, coef1);
    bool cy = concernedIIR(rt, y, coef2);
    if (cx && cy) {
        // we have two concerned IIRs, we can substrcat them together
        // [v, a, c0, c1, c2, ...] - [v, b, d0, d1, d2, ...] -> [v, a-b, c0-d0, c1-d1, c2-d2, ...]
        tvec coef;
        coef.push_back(coef1[0]);  // Vi
        unsigned int n = std::min(coef1.size(), coef2.size());
        // add coefficients of the same order
        for (unsigned int i = 1; i < n; i++) {
            coef.push_back(simplify(sigSub(coef1[i], coef2[i])));
        }
        // copy coefficients of the longuest IIR
        for (unsigned int i = n; i < coef1.size(); i++) {
            coef.push_back(coef1[i]);
        }
        for (unsigned int i = n; i < coef2.size(); i++) {
            coef.push_back(simplify(sigSub(sigInt(0), coef2[i])));
        }
        return sigIIR(coef);
    } else if (cx) {
        // x is a concerned IIR but y is not, we add y to the input signal of x
        // [v, a, c0, c1, c2, ...] + y -> [v, a+y, c0, c1, c2, ...]
        coef1[1] = simplify(sigSub(coef1[1], y));
        return sigIIR(coef1);
    } else if (cy) {
        // x is not concerned, but y is, we add x to the input signal of y
        // x + [v, b, c0, c1, c2, ...] -> [v, x-b, -c0, -c1, -c2, ...]
        // we invert y coefficients
        for (unsigned int j = 1; j < coef2.size(); j++) {
            coef2[j] = simplify(sigSub(sigInt(0), coef2[j]));
        }
        coef2[1] = simplify(sigAdd(x, coef2[1]));  // add x to the input signal of the IIR
        return sigIIR(coef2);
    } else {
        // x and y are unrelated to the recursive variable
        return simplify(sigSub(x, y));
    }
}

Tree subSigIIR(Tree rt, Tree x, Tree y)
{
    if (TRACE) {
        std::cerr << "subSigIIR: " << rt << ", " << ppsig(x) << " by " << ppsig(y) << "\n";
    }
    Tree res = subSigIIR_real(rt, x, y);
    if (TRACE) {
        std::cerr << "subSigIIR: " << rt << ", " << ppsig(x) << " by " << ppsig(y) << " ==> "
                  << ppsig(res) << "\n";
    }
    return res;
}

//-------------------------------------------------------------------------
// Multiply an IIR, or sigMul(s1,s2) if s1 and s2 are not concerned IIRs
// Assume x and y are not nil
Tree mulSigIIR_real(Tree rt, Tree x, Tree y)
{
    tvec coef1, coef2;
    bool cx = concernedIIR(rt, x, coef1);
    bool cy = concernedIIR(rt, y, coef2);
    if (cx && cy) {
        // we have two concerned IIRs, their multiplication can't be an IIR !
        return gGlobal->nil;
    } else if (cx) {
        // x is a concerned IIR but y is not, we multiply by all the coefficients of x
        // [v, a, c0, c1, c2, ...] * y -> [v, a*y, c0*y, c1*y, c2*y, ...]
        tvec coef;
        coef.push_back(coef1[0]);  // Vi
        for (unsigned int i = 1; i < coef1.size(); i++) {
            coef.push_back(simplify(sigMul(coef1[i], y)));
        }
        return sigIIR(coef);
    } else if (cy) {
        // y is a concerned IIR but x is not, therefore we multiply by x all the coefficients of y
        // [v, a, c0, c1, c2, ...] * x -> [v, a*x, c0*x, c1*x, c2*x, ...]
        tvec coef;
        coef.push_back(coef2[0]);  // Vi
        for (unsigned int i = 1; i < coef2.size(); i++) {
            coef.push_back(simplify(sigMul(coef2[i], x)));
        }
        return sigIIR(coef);
    } else {
        // x and y are unrelated to the recursive variable
        return simplify(sigMul(x, y));
    }
}

Tree mulSigIIR(Tree rt, Tree x, Tree y)
{
    if (TRACE) {
        std::cerr << "mulSigIIR: " << rt << ", " << ppsig(x) << " by " << ppsig(y) << "\n";
    }
    Tree res = mulSigIIR_real(rt, x, y);
    if (TRACE) {
        std::cerr << "mulSigIIR: " << rt << ", " << ppsig(x) << " by " << ppsig(y) << " ==> "
                  << ppsig(res) << "\n";
    }
    return res;
}

//-------------------------------------------------------------------------
// Divide an IIR, or sigMul(s1,s2) if s1 and s2 are not concerned IIRs
// Assume x and y are not nil
Tree divSigIIR_real(Tree rt, Tree x, Tree y)
{
    tvec coef1, coef2;
    bool cx = concernedIIR(rt, x, coef1);
    bool cy = concernedIIR(rt, y, coef2);
    if (cy) {
        // a division by an IIR can't be an IIR
        return gGlobal->nil;
    } else if (cx) {
        // x is a concerned IIR, we divide by y all the coefficients of x
        // [v, a, c0, c1, c2, ...] * y -> [v, a/y, c0/y, c1/y, c2/y, ...]
        tvec coef;
        coef.push_back(coef1[0]);  // Vi
        for (unsigned int i = 1; i < coef1.size(); i++) {
            coef.push_back(simplify(sigDiv(coef1[i], y)));
        }
        return sigIIR(coef);
    } else {
        // x and y are unrelated to the recursive variable
        return simplify(sigDiv(x, y));
    }
}

Tree divSigIIR(Tree rt, Tree x, Tree y)
{
    if (TRACE) {
        std::cerr << "divSigIIR: " << rt << ", " << ppsig(x) << " by " << ppsig(y) << "\n";
    }
    Tree res = divSigIIR_real(rt, x, y);
    if (TRACE) {
        std::cerr << "divSigIIR: " << rt << ", " << ppsig(x) << " by " << ppsig(y) << " ==> "
                  << ppsig(res) << "\n";
    }
    return res;
}

/**
 * @brief Transforms a FIR filter applied to an IIR filter into an IIR filter applied to a FIR
 * filter.
 *
 * This function takes a signal of the form FIR[IIR[w,x,c0,c1,...],d0,d1,...] and transforms it into
 * IIR[w,FIR[x,d0,d1,...],[c0,c1,...]x[d0,d1,...]]. This transformation is useful for optimization
 * purposes.
 *
 * @param rt  The recursive variable.
 * @param fir The FIR filter applied to an IIR filter.
 * @return    The transformed signal, or gGlobal->nil if the transformation is not possible.
 */
Tree embeddedIIR(Tree rt, Tree fir)
{
    tvec cfir, ciir;
    faustassert(isSigFIR(fir, cfir) && isSigIIR(cfir[0], ciir) && (ciir[0] == rt));
    // we have a concerned IIR inside a FIR
    // if (TRACE) std::cerr << "fir : " << ppsig(fir) << "\n";
    // if (TRACE) std::cerr << "iir : " << ppsig(cfir[0]) << "\n";

    // Tree iir = cfir[0];
    Tree x = ciir[1];  // partie non recursive
    // application du FIR sur x -> fx;
    tvec coef1 = cfir;
    coef1[0]   = x;
    Tree fx    = sigFIR(coef1);
    // if (TRACE) std::cerr << "fx  : " << ppsig(fx) << "\n";
    //  application du FIR sur iir -> fiir;
    tvec coef2 = ciir;
    coef2[1]   = sigInt(0);
    Tree iir2  = sigIIR(coef2);
    Tree res   = mulSigIIR(rt, iir2, cfir[1]);
    // if (TRACE) std::cerr << "res0: " << ppsig(res) << "\n";
    for (unsigned int i = 2; i < cfir.size(); i++) {
        Tree t1 = delaySigIIR(rt, iir2, sigInt(i - 1));
        Tree t2 = mulSigIIR(rt, t1, cfir[i]);
        res     = addSigIIR(rt, res, t2);
        // if (TRACE) std::cerr << "res+: " << ppsig(res) << "\n";
    }
    Tree res2 = addSigIIR(rt, res, fx);
    // if (TRACE) std::cerr << "res2: " << ppsig(res2) << "\n";
    return res2;
}

/**************************************************************************************************
 * @brief Calculates the worst-case peak gain of the recursive part of an IIR filter.
 *
 * This function computes the minimum magnitude of the denominator polynomial A(z) of the IIR filter
 * on the unit circle, and returns the inverse of this minimum magnitude. This provides an estimate
 * of the maximum gain of the recursive part of the filter.
 *
 * @param a_coeffs A vector containing the coefficients of the denominator polynomial A(z) of the
 * IIR filter. The coefficients are ordered from a1 to aN, where A(z) = 1 + a1*z^-1 + a2*z^-2 + ...
 * + aN*z^-N.
 * @param num_points The number of points to evaluate the magnitude of A(z) at.
 *                   A larger number of points will result in a more accurate estimate of the peak
 * gain, but will also increase the computation time.
 * @return The worst-case peak gain of the recursive part of the IIR filter, which is the inverse of
 * the minimum magnitude of its denominator polynomial A(z) on the unit circle.
 */
double IIRWorstPeakGain(const std::vector<double>& a_coeffs, int num_points)
{
    using namespace std;
    const double pi      = acos(-1);
    double       min_mag = numeric_limits<double>::max();

    for (int i = 0; i < num_points; ++i) {
        double          omega = pi * i / (num_points - 1);
        complex<double> ejw   = polar(1.0, -omega);
        complex<double> A     = 1.0;

        complex<double> ejw_pow = 1.0;
        for (size_t k = 0; k < a_coeffs.size(); ++k) {
            ejw_pow *= ejw;
            A += a_coeffs[k] * ejw_pow;
        }

        double mag = abs(A);
        if (mag < min_mag) {
            min_mag = mag;
        }
    }

    return 1.0 / min_mag;
}
