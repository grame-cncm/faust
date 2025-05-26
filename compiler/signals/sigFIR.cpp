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
 * @file sigFIR.cpp
 * @author Yann ORLAREY (yann.orlarey@inria.fr)
 * @brief Operations and predicats for FIR signals: [S, C0, C1, ...] = C0*S + C1*S@1 + ...
 * @version 0.1
 * @date 2024-01-10
 *
 * @copyright Copyright (c) 2024 INRIA
 *
 */

#include <cmath>
#include <complex>
#include <iostream>
#include <limits>
#include <vector>

#include "ppsig.hh"
#include "sigFIR.hh"
#include "sigtyperules.hh"
#include "simplify.hh"

// for test purposes
#include "occurrences.hh"
#include "recursivness.hh"
#include "sharing.hh"
#include "sigorderrules.hh"

//-------------------------------------------------------------------------
// Create an elementary FIR from a signal with a fixed delay
// S@d --> makeSigFIR(S,d) --> sigFIR([S, 0, 0, ..., 1])
// The vector V as d+2 elements: the signal itself, d zeros and a one.
Tree makeSigFIR(Tree sig, int d)
{
    tvec V;
    V.push_back(sig);
    for (int i = 0; i < d; i++) {
        V.push_back(sigInt(0));
    }
    V.push_back(sigInt(1));
    return sigFIR(V);
}

//-------------------------------------------------------------------------
// Create a FIR from a delayed signal if the delay is constant
Tree delaySigFIR(Tree s1, Tree s2)
{
    if (int d; isSigInt(s2, &d) && (d >= 0) && (d <= gGlobal->gMaxFIRSize)) {
        if (d > 0) {
            if (tvec V1; isSigFIR(s1, V1)) {
                tvec VR;
                VR.push_back(V1[0]);
                for (int i = 0; i < d; i++) {
                    VR.push_back(sigInt(0));
                }
                for (unsigned int i = 1; i < V1.size(); i++) {
                    VR.push_back(V1[i]);
                }
                return sigFIR(VR);
            } else if (Tree ck, f; isSigClocked(s1, ck, f) && isSigFIR(f)) {
                tvec V1 = f->branches();
                tvec VR;
                VR.push_back(V1[0]);
                for (int i = 0; i < d; i++) {
                    VR.push_back(sigInt(0));
                }
                for (unsigned int i = 1; i < V1.size(); i++) {
                    VR.push_back(V1[i]);
                }
                return sigFIR(VR);
            } else {
                return makeSigFIR(s1, d);
            }
        } else {
            // For some reason it is useful to have a clock around a rec with a delay of zero
            int j;
            if (Tree rg, var, le; isProj(s1, &j, rg) && isRec(rg, var, le)) {
                // std::cerr << "#### delaySigFIR: delay is zero for rec: " << ppsig(s1) <<
                // std::endl;
                if (Tree ck; hasClock(nth(le, j), ck)) {
                    // std::cerr << "#### delaySigFIR: rec has a clock: " << ppsig(ck) << std::endl;
                    return sigClocked(ck, s1);
                }
            }

            return s1;
        }
    } else {
        return sigDelay(s1, s2);
    }
}

//-------------------------------------------------------------------------
// Negate a signal: S -> -S
static Tree sigNeg(Tree sig)
{
    return simplify(sigMul(sigInt(-1), sig));
}

//-------------------------------------------------------------------------
// Negate a FIR
Tree negSigFIR(Tree sig)
{
    // -FIR[X,C0,C1,...] -> FIR[X,-C0,-C1,...]
    if (tvec V; isSigFIR(sig, V)) {
        for (unsigned int i = 1; i < V.size(); i++) {
            V[i] = sigNeg(V[i]);
        }
        return sigFIR(V);
    }

    // -(X+Y) -> -X+-Y
    if (Tree x, y; isSigAdd(sig, x, y)) {
        return addSigFIR(negSigFIR(x), negSigFIR(y));
    }

    // -(X-Y) -> -X+Y
    if (Tree x, y; isSigSub(sig, x, y)) {
        return addSigFIR(negSigFIR(x), y);
    }

    return sigNeg(sig);
}

//-------------------------------------------------------------------------
// Check if s is divisible by c
// return true and r if s/c = r
static bool isDivisibleBy(Tree s, Tree c, Tree& r)
{
    Tree x, y;
    if (s == c) {
        r = sigInt(1);
        return true;
    } else if (isSigMul(s, x, y)) {
        // s = x*y
        Tree r1, r2;
        if (isDivisibleBy(x, c, r1)) {
            // x=c*r1 => s = c*r1*y => s/c = r1*y
            r = sigMul(r1, y);
            return true;
        } else if (isDivisibleBy(y, c, r2)) {
            // y=c*r2 => s = x*c*r2 => s/c = r2*x
            r = sigMul(r2, x);
            return true;
        } else {
            // not divisible
            return false;
        }
    } else {
        return false;
    }
}

//-------------------------------------------------------------------------
// Analyze the coefficients of a FIR for compatibility with multiplication
// static int analyzeFIRCoefs(Tree s)
// {
//     tvec V;
//     if (isSigFIR(s, V)) {
//         int countCoef     = 0;  // total number of non-zero coefficients
//         int countCtrlRate = 0;  // total number of non-zero coefficients that are constant or
//         ctrl rate for (unsigned int i = 1; i < V.size(); i++) {
//             if (!isZero(V[i])) {
//                 std::cerr << "tutu1" << std::endl;

//                 countCoef++;
//                 typeAnnotation(V[i], true);
//                 Type t = getSigType(V[i]);
//                 if (t && t->variability() <= kBlock) { countCtrlRate++; }
//                 std::cerr << "tutu2 " << countCoef << ":" << countCtrlRate << std::endl;
//             }
//         }
//         // encode the result
//         if ((countCoef == 1) || (countCoef == countCtrlRate)) {
//             std::cerr << "all non-zero coefficients are constant or control rate: " << ppsig(s)
//             << std::endl; return countCoef;
//         } else {
//             // some non-zero coefficients are sample rate
//             std::cerr << "some non-zero coefficients are sample rate: " << ppsig(s) << std::endl;
//             return 0;
//         }
//     }
//     return 0;
// }

//-------------------------------------------------------------------------
// Analyze the coefficients of a FIR for compatibility with multiplication
static int analyzeFIRCoefs(Tree s)
{
    tvec   V;
    int    n;
    double x;

    if (isSigFIR(s, V)) {
        int countCoef = 0;  // total number of non-zero coefficients
        int countNum  = 0;  // total number of non-zero coefficients that are numerical constants
        for (unsigned int i = 1; i < V.size(); i++) {
            if (!isZero(V[i])) {
                countCoef++;
                if (isSigInt(V[i], &n) || isSigReal(V[i], &x)) {
                    countNum++;
                }
            }
        }
        // encode the result
        if ((countCoef == 1) || (countCoef == countNum)) {
            return countCoef;
        } else {
            // some non-zero coefficients are not numerical constants
            return 0;
        }
    }
    return 0;
}

//-------------------------------------------------------------------------
// We can add two FIRs if:
// a) they applies to the same signal, in this case the coefficients are added together;
// b) if the two FIRs are applied to two different signals, but have the same coefficients,
// in this case the two signals are added,
// c) if the two have complementary coefficients, in this case the two signals are subtracted.
Tree addSigFIR(Tree s1, Tree s2)
{
    tvec V1, V2;
    Tree r;

    if (isSigFIR(s1, V1) && isSigFIR(s2, V2)) {
        // CASE 1: two FIRs
        if (V1[0] == V2[0]) {
            // CASE 1.1: [S, C0, C1, ...] + [S, D0, D1, ...]= [S, C0+D0, C1+D1, ...]
            tvec V;
            V.push_back(V1[0]);
            unsigned int minsize = std::min(V1.size(), V2.size());
            for (unsigned int i = 1; i < minsize; i++) {
                V.push_back(simplify(sigAdd(V1[i], V2[i])));
            }
            for (unsigned int i = minsize; i < V1.size(); i++) {
                V.push_back(V1[i]);
            }  // V1 longuer
            for (unsigned int i = minsize; i < V2.size(); i++) {
                V.push_back(V2[i]);
            }  // V2 longuer

            normalizeFIRCoefs(V);  // TODO : simplify coefs, normalize
            if (V.size() == 1) {
                // All coefficients are zero, return the zero signal !
                return sigInt(0);
            } else if (V.size() == 2) {
                // Only one non zero coefficient, not a FIR anymore !
                return sigMul(V[1], V[0]);
            }
            // Still a real FIR
            return sigFIR(V);
        } else {
            // Two uncompatible FIRs
            return sigAdd(s1, s2);
        }
    } else if (isSigFIR(s1, V1) && isDivisibleBy(s2, V1[0], r)) {
        // CASE 2: [S, C0, C1, ...] + S*R = [S, C0+R, C1, ...]
        V1[1] = simplify(sigAdd(V1[1], r));
        return sigFIR(V1);
    } else if (isSigFIR(s2, V2) && isDivisibleBy(s1, V2[0], r)) {
        // CASE 3: S*R + [S, C0, C1, ...] = [S, C0+R, C1, ...]
        V2[1] = simplify(sigAdd(V2[1], r));
        return sigFIR(V2);
    } else {
        // CASE 4: Not two FIRs
        return simplify(sigAdd(s1, s2));
    }
}

//-------------------------------------------------------------------------
// Try to add two FIRs if:
// a) they applies to the same signal, in this case the coefficients are added together;
// b) if the two FIRs are applied to two different signals, but have the same coefficients,
// in this case the two signals are added,
// c) if the two have complementary coefficients, in this case the two signals are subtracted.
// return a sigFIR if it succeeded, or a nullptr
Tree TryAddSigFIR(Tree s1, Tree s2)
{
    tvec V1, V2;
    Tree r;

    // std::cerr << "TryAddSigFIR(" << ppsig(s1) << ", " << ppsig(s2) << ")\n";

    if (isSigFIR(s1, V1) && isSigFIR(s2, V2)) {
        // CASE 1: two FIRs
        if (V1[0] == V2[0]) {
            // CASE 1.1: [S, C0, C1, ...] + [S, D0, D1, ...]= [S, C0+D0, C1+D1, ...]
            tvec V;
            V.push_back(V1[0]);
            unsigned int minsize = std::min(V1.size(), V2.size());
            for (unsigned int i = 1; i < minsize; i++) {
                V.push_back(simplify(sigAdd(V1[i], V2[i])));
            }
            for (unsigned int i = minsize; i < V1.size(); i++) {
                V.push_back(V1[i]);
            }  // V1 longuer
            for (unsigned int i = minsize; i < V2.size(); i++) {
                V.push_back(V2[i]);
            }  // V2 longuer

            normalizeFIRCoefs(V);  // TODO : simplify coefs, normalize
            if (V.size() == 1) {
                // All coefficients are zero, return the zero signal !
                return sigInt(0);
            } else if (V.size() == 2) {
                // Only one non zero coefficient, not a FIR anymore !
                return sigMul(V[1], V[0]);
            }
            // Still a real FIR
            return sigFIR(V);
        } else {
            // Two uncompatible FIRs
            return gGlobal->nil;
        }
    } else if (isSigFIR(s1, V1) && isDivisibleBy(s2, V1[0], r)) {
        // CASE 2: [S, C0, C1, ...] + S*R = [S, C0+R, C1, ...]
        V1[1] = simplify(sigAdd(V1[1], r));
        return sigFIR(V1);
    } else if (isSigFIR(s2, V2) && isDivisibleBy(s1, V2[0], r)) {
        // CASE 3: S*R + [S, C0, C1, ...] = [S, C0+R, C1, ...]
        V2[1] = simplify(sigAdd(V2[1], r));
        return sigFIR(V2);
    } else {
        // CASE 4: Not two FIRs
        return gGlobal->nil;
    }
}

Tree smartAddSigFIR(Tree t1, Tree t2)
{
    std::cerr << "smartAddSigFIR(" << ppsig(t1) << ", " << ppsig(t2) << ")\n";
    // traverse add/sub trees
    if (Tree a, b; isSigAdd(t1, a, b)) {
        Tree c = smartAddSigFIR(smartAddSigFIR(a, t2), b);
        // std::cerr << "smartAddSigFIR(" << ppsig(t1) << ", " << ppsig(t2) << ") ==> " << ppsig(c)
        // << "\n";
        return c;
    }

    if (Tree a, b; isSigAdd(t2, a, b)) {
        Tree c = smartAddSigFIR(smartAddSigFIR(t1, a), b);
        // std::cerr << "smartAddSigFIR(" << ppsig(t1) << ", " << ppsig(t2) << ") ==> " <<
        // ppsig(c) << "\n";
        return c;
    }

    // not add terms, try compatible FIRs
    Tree t3 = TryAddSigFIR(t1, t2);
    if (t3 != gGlobal->nil) {
        return t3;
    }
    // nothing we can do, simple add
    Tree c = sigAdd(t1, t2);
    // std::cerr << "smartAddSigFIR(" << ppsig(t1) << ", " << ppsig(t2) << ") ==> " << ppsig(c) <<
    // "\n";
    return c;
}

// Promote the signal or the coefficients of a FIR if needed
Tree promotionSigFIR(Tree sig)
{
    tvec V;
    if (isSigFIR(sig, V)) {
        // int n     = kInt;
        int cint  = 0;
        int creal = 0;
        for (Tree x : V) {
            // we ignore 0s and 1s
            if (isZero(x) || isOne(x)) {
                continue;
            }

            // we check the nature of the coefficient
            Type tx = getCertifiedSigType(x);
            int  n  = tx->nature();

            if (n == kInt) {
                cint++;
            } else {
                creal++;
            }
        }
        if ((cint > 0) && (creal > 0)) {
            // we have a mix of int and real and we need to promoto to real
            for (unsigned int i = 0; i < V.size(); i++) {
                // we promote the int signals that are not 0 or 1
                Tree x = V[i];
                if (isZero(x) || isOne(x)) {
                    continue;
                }
                Type tx = getCertifiedSigType(x);
                if (tx->nature() == kInt) {
                    V[i] = sigFloatCast(x);
                }
            }
            return sigFIR(V);
        } else {
            // we have only ints or reals, no need for promotion
            return sig;
        }
    } else {
        // not a FIR, no promotion to do
        return sig;
    }
}

//-------------------------------------------------------------------------
// We can substract two FIRs if:
// a) they applies to the same signal, in this case the coefficients are substracted together;
// b) if the two FIRs are applied to two different signals, but have the same coefficients,
// in this case the two signals are substracted,
// c) if the two have complementary coefficients, in this case the two signals are added.
Tree subSigFIR(Tree s1, Tree s2)
{
    return addSigFIR(s1, negSigFIR(s2));
}

//-------------------------------------------------------------------------
// We can multiply a FIR S1 with a signal S2 if we dont increase the number
// of multiplications at sample rate, that is if:
// a) the FIR contains only one non-zero coefficient,
// b) the FIR contains only constant or control-rate coefficients and S2 is constant or control rate
Tree mulSigFIR(Tree s1, Tree s2)
{
    tvec V;

    if (isSigFIR(s1, V)) {
        int n = analyzeFIRCoefs(s1);

        if (n == 1) {
            // CASE 1: [S, C0, C1, ...] * S2 = [S*C0, S*C1, ...]
            for (unsigned int i = 1; i < V.size(); i++) {
                if (!isZero(V[i])) {
                    V[i] = simplify(sigMul(V[i], s2));
                }
            }
            return sigFIR(V);
        } else if (n > 1) {
            int    ii;
            double r;

            // Type t = getSigType(s2);
            if (isSigInt(s2, &ii) || isSigReal(s2, &r)) {
                for (unsigned int i = 1; i < V.size(); i++) {
                    if (!isZero(V[i])) {
                        V[i] = simplify(sigMul(V[i], s2));
                    }
                }
                return sigFIR(V);
            } else {
                // CASE 2: Not a FIR
                return simplify(sigMul(s1, s2));
            }
        } else {
            // CASE 3: Not a FIR
            return simplify(sigMul(s1, s2));
        }
    } else if (isSigFIR(s2, V)) {
        return mulSigFIR(s2, s1);
    } else if (isMinusOne(s1)) {
        return negSigFIR(s2);
    } else if (isMinusOne(s2)) {
        return negSigFIR(s1);
    }
    // AJOUT YO
    else if (Tree x, y; isSigAdd(s1, x, y) && isSigFIR(x) && isSigFIR(y)) {
        return addSigFIR(mulSigFIR(x, s2), mulSigFIR(y, s2));
    } else if (Tree x, y; isSigAdd(s2, x, y) && isSigFIR(x) && isSigFIR(y)) {
        return addSigFIR(mulSigFIR(s1, x), mulSigFIR(s1, y));
    } else if (Tree x, y; isSigSub(s1, x, y) && isSigFIR(x) && isSigFIR(y)) {
        return subSigFIR(mulSigFIR(x, s2), mulSigFIR(y, s2));
    } else if (Tree x, y; isSigSub(s2, x, y) && isSigFIR(x) && isSigFIR(y)) {
        return subSigFIR(mulSigFIR(s1, x), mulSigFIR(s1, y));

    }
    // FIN AJOUT YO
    else {
        // CASE 3: Not a FIR

        Tree sr = simplify(sigMul(s1, s2));
        // std::cerr << "NOT A FIR : mulSigFIR(" << ppsig(s1) << ", " << ppsig(s2) << ") ==> "
        //           << ppsig(sr) << "\n";
        return sr;
    }
}

//-------------------------------------------------------------------------
// We can divide a FIR S1 with a signal S2 if we dont increase the number
// of multiplications at sample rate, that is if:
// a) the FIR contains only one non-zero coefficient,
// b) the FIR contains only constant or control-rate coefficients and S2 is constant or control rate
Tree divSigFIR(Tree s1, Tree s2)
{
    tvec V;

    if (isSigFIR(s1, V)) {
        int n = analyzeFIRCoefs(s1);

        if (n == 1) {
            // CASE 1: [S, C0, C1, ...] / S2 = [S, C0, S*C1, ...]
            for (unsigned int i = 1; i < V.size(); i++) {
                if (!isZero(V[i])) {
                    V[i] = simplify(sigDiv(V[i], s2));
                }
            }
            return sigFIR(V);
        } else if (n > 1) {
            int    ii;
            double r;

            if (isSigInt(s2, &ii) || isSigReal(s2, &r)) {
                for (unsigned int i = 1; i < V.size(); i++) {
                    if (!isZero(V[i])) {
                        V[i] = simplify(sigDiv(V[i], s2));
                    }
                }
                return sigFIR(V);
            } else {
                // CASE 2: Not a FIR
                return simplify(sigDiv(s1, s2));
            }
        } else {
            return simplify(sigDiv(s1, s2));
        }

    } else {
        return simplify(sigDiv(s1, s2));
    }
}

//-------------------------------------------------------------------------
// Convert a FIR [s,c_1,c_2,...] to a combination of delays c_1*s+c_2*s@1+...+c_n*s@(n-1)
Tree convertFIR2Sig(Tree sig)
{
    tvec V;
    if (isSigFIR(sig, V)) {
        Tree s = V[0];       // the base signal
        Tree r = sigInt(0);  // the resulting signal
        for (unsigned int i = 1; i < V.size(); i++) {
            Tree c = V[i];  // the current coefficient
            if (!isZero(c)) {
                if (i == 1) {
                    r = sigAdd(r, sigMul(c, s));  // no delay for the first coefficient
                } else {
                    r = sigAdd(r, sigMul(c, sigDelay(s, sigInt(i - 1))));
                }
            }
        }
        return r;
    } else {
        // not a FIR, no conversion to do
        return sig;
    }
}

//-------------------------------------------------------------------------
// FIR predicates
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
// True if the two FIRs have the equivalent coefficients : V1[i] - V2[i] = 0
bool haveEquivCoefs(const tvec& V1, const tvec& V2)
{
    if (V1.size() != V2.size()) {
        return false;
    }
    for (unsigned int i = 1; i < V1.size(); i++) {
        Tree c = simplify(sigSub(V1[i], V2[i]));
        if (!isZero(c)) {
            return false;
        }
    }
    return true;
}

//-------------------------------------------------------------------------
// True if the two FIRs have the complementary coefficients : V1[i] + V2[i] = 0
bool haveComplementaryCoefs(const tvec& V1, const tvec& V2)
{
    if (V1.size() != V2.size()) {
        return false;
    }
    for (unsigned int i = 1; i < V1.size(); i++) {
        Tree c = simplify(sigAdd(V1[i], V2[i]));
        if (!isZero(c)) {
            return false;
        }
    }
    return true;
}

//-------------------------------------------------------------------------
// remove trailing zero coefficients (inplace modification)
void normalizeFIRCoefs(tvec& V)
{
    while (V.size() > 1 && isZero(V.back())) {
        V.pop_back();
    }
}

//-------------------------------------------------------------------------
// Simplify a FIR by removing trailing zeros and degenerated cases
Tree simplifyFIR(Tree sig)
{
    if (tvec V; isSigFIR(sig, V)) {
        // Degenerated cases, not a proper FIR
        if (V.size() < 2) {
            return sigInt(0);
        }

        // Since the base signal is 0 the result is 0
        if (isZero(V[0])) {
            return sigInt(0);
        }

        // It seems we have enough coefficients
        // We need to check the index of last non-zero coefficient (lnz)
        unsigned int lnz = 0;
        for (unsigned int i = 1; i < V.size(); i++) {
            if (!isZero(V[i])) {
                lnz = i;
            }
        }
        if (lnz == 0) {
            // all coefficients are zero
            return sigInt(0);
        }
        // if (lnz == 1) {
        //     // not a real FIR
        //     return simplify(sigMul(V[0], V[1]));
        // }
        if (lnz < V.size() - 1) {
            // remove trailing zeros
            V.resize(lnz + 1);
            return sigFIR(V);
        }
        // the FIR was already in normal form, nothing to do
        return sig;
    } else {
        // not a FIR, no simplification to do
        return sig;
    }
}

//-------------------------------------------------------------------------
// Split X -> (A,B) such that X = A*B
//
// -----------------
// K -> (1,K)
//
// X -> (A,B)    Y -> (C,D)
// ------------------------
// X*Y -> (AC,BD)
//
// X -> (A,B)    Y -> (C,D)
// ------------------------
// X/Y -> (A/C,B/D)
//
// -----------------
// S -> (S,1)
//

/**
 * @brief Split a signal into two signals <coef,sig2> such that sig = coef*sig2
 * and order(coef) < 3
 *
 * @param sig the signal to split
 * @return std::pair<Tree, Tree> the pair <coef,sig2>
 */
static std::pair<Tree, Tree> splitMulSig(Tree sig)
{
    if (getSigOrder(sig) < 3) {
        // sig is already a pure coef
        return {sig, sigInt(1)};
    }

    if (Tree x, y; isSigMul(sig, x, y)) {
        // sig is a multiplication
        auto [a, b] = splitMulSig(x);
        auto [c, d] = splitMulSig(y);
        return {simplify(sigMul(a, c)), simplify(sigMul(b, d))};
    }

    if (Tree x, y; isSigDiv(sig, x, y)) {
        // sig is a division
        auto [a, b] = splitMulSig(x);
        auto [c, d] = splitMulSig(y);
        return {simplify(sigDiv(a, c)), simplify(sigDiv(b, d))};
    }
    // sig is a pure signal
    return {sigInt(1), sig};
}

/**
 * @brief add sig to the appropriate entry in M.
 *
 * @param M contains the various FIRs collected so far
 * @param subflag when true we do a subtraction instead of an addition
 * @param sig the signal to add to M (addition, substraction, FIR or other)
 */

void combine(std::map<Tree, Tree>& M, bool subflag, Tree sig)
{
    if (Tree x, y; isSigAdd(sig, x, y)) {
        // if sig is an addition we combine its two subtrees with M
        combine(M, subflag, x);
        combine(M, subflag, y);
        return;
    }

    if (Tree x, y; isSigSub(sig, x, y)) {
        // if sig is a substraction we combine its two subtrees with M
        combine(M, subflag, x);
        combine(M, !subflag, y);  // but we invert the subflag for y
        return;
    }

    if (tvec coefs; isSigFIR(sig, coefs)) {
        // if sig is a FIR we combine it with the appropriate entry of M
        Tree key = coefs[0];
        Tree val = (subflag) ? negSigFIR(sig) : sig;
        if (M.find(key) == M.end()) {
            M[key] = val;
        } else {
            M[key] = addSigFIR(M[key], val);
        }
        return;
    }

    if (getSigOrder(sig) == 3) {
        // sig is a signal with order 3, we split it into a coef and a signal
        auto [coef, key] = splitMulSig(sig);
        tvec coefs       = {key, coef};
        Tree fir         = sigFIR(coefs);

        Tree val = (subflag) ? negSigFIR(fir) : fir;
        if (M.find(key) == M.end()) {
            M[key] = val;
        } else {
            M[key] = addSigFIR(M[key], val);
        }
        return;
    }

    // sig is a coefficient
    Tree key = gGlobal->nil;
    if (M.find(key) == M.end()) {
        M[key] = (subflag) ? sigNeg(sig) : sig;
    } else {
        M[key] = (subflag) ? simplify(sigSub(M[key], sig)) : simplify(sigAdd(M[key], sig));
    }
}

/**
 * @brief combine the FIRs contained in x and y
 *
 * @param x
 * @param y
 * @return Tree
 */

/**
 * @brief combine the FIRs contained in x and y
 *
 * @param x is added
 * @param y is added or substracted according to subflag
 * @param subflag indicates to substract y
 * @return Tree the resulting expression with all the FIRs combined
 */
Tree combineFIRs(Tree x, Tree y, bool subflag)
{
    std::map<Tree, Tree> M;  // Map of all FIRs collected

    combine(M, false, x);    // We add x to M
    combine(M, subflag, y);  // We add or substract y to M

    // Add together all the FIRs collected in M
    bool init = true;
    Tree result;
    for (auto t : M) {
        Tree term = t.second;
        if (tvec coefs; isSigFIR(term, coefs) && (coefs.size() == 2)) {
            // if the term is a FIR with only one non-zero coefficient we simplify it"
            term = simplify(sigMul(coefs[1], coefs[0]));
        }
        if (init) {
            result = term;
            init   = false;
        } else {
            result = sigAdd(result, term);
        }
    }
    return result;
}

void testFIR()
{
    std::cerr << "Tests for FIR reconstruction" << std::endl;
    Tree s1 = sigInput(1);
    Tree s2 = addSigFIR(makeSigFIR(s1, 4), makeSigFIR(s1, 3));
    Tree s3 = addSigFIR(s1, s2);

    std::cerr << "s1=" << ppsig(s1) << std::endl;
    std::cerr << "s2=" << ppsig(s2) << std::endl;
    std::cerr << "s3=" << ppsig(s3) << std::endl;

    Tree s4 = addSigFIR(sigMul(s1, sigInt(4)), s2);
    std::cerr << "s4=" << ppsig(s4) << std::endl;

    Tree s5 = mulSigFIR(s4, sigInt(-3));

    // prepare S5
    Tree L2          = cons(s5, gGlobal->nil);
    Tree fSharingKey = tree("sharingkey");
    // conditionAnnotation(L2);
    recursivnessAnnotation(L2);        // Annotate L2 with recursivness information
    typeAnnotation(L2, true);          // Annotate L2 with type information and check causality
    sharingAnalysis(L2, fSharingKey);  // Annotate L2 with sharing count
    OccMarkup occ;
    occ.mark(L2);  // Annotate L2 with occurrences analysis

    // end prepare

    // typeAnnotation(s5, true);
    Type ty5 = getCertifiedSigType(s5);
    Type ty1 = getCertifiedSigType(s1);
    std::cerr << "s5=" << ppsig(s5) << " and has type " << ty5 << std::endl;

    Occurrences* o = occ.retrieve(s1);
    std::cerr << "s1=" << ppsig(s1) << " has max delay " << o->getMaxDelay() << std::endl;
}

/**************************************************************************************************
 * @brief Calculates the worst-case peak gain of a FIR filter.
 *
 * This function computes the maximum magnitude of the frequency response of a FIR filter
 * by evaluating it at a number of points equally spaced on the unit circle.
 *
 * @param b_coeffs A vector containing the coefficients of the FIR filter.
 *                 The coefficients are ordered from b0 to bN, where N is the filter order.
 * @param num_points The number of points to evaluate the frequency response at.
 *                   A larger number of points will result in a more accurate estimate of the peak
 * gain, but will also increase the computation time.
 * @return The worst-case peak gain of the FIR filter, which is the maximum magnitude of its
 *         frequency response.
 */
double FIRWorstPeakGain(const std::vector<double>& b_coeffs, int num_points)
{
    using namespace std;
    const double pi      = acos(-1);
    double       max_mag = 0.0;

    for (int i = 0; i < num_points; ++i) {
        double          omega = pi * i / (num_points - 1);
        complex<double> ejw   = polar(1.0, -omega);
        complex<double> H     = 0.0;

        complex<double> ejw_pow = 1.0;
        for (double b_k : b_coeffs) {
            H += b_k * ejw_pow;
            ejw_pow *= ejw;
        }

        double mag = abs(H);
        if (mag > max_mag) {
            max_mag = mag;
        }
    }

    return max_mag;
}
