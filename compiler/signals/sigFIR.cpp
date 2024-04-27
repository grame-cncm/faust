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

#include <iostream>

#include "ppsig.hh"
#include "sigFIR.hh"
#include "sigtyperules.hh"
#include "simplify.hh"

// for test purposes
#include "occurrences.hh"
#include "recursivness.hh"
#include "sharing.hh"

//-------------------------------------------------------------------------
// Create a FIR form a signal with a fixed delay
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
    int d;
    if (isSigInt(s2, &d) && (d < 10)) {
        if (d > 0) {
            tvec V1;
            if (isSigFIR(s1, V1)) {
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
static Tree negSigFIR(Tree sig)
{
    tvec V;
    if (isSigFIR(sig, V)) {
        for (unsigned int i = 1; i < V.size(); i++) {
            V[i] = sigNeg(V[i]);
        }
        return sigFIR(V);
    } else {
        return sigNeg(sig);
    }
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
#if 0
        } else if (haveEquivCoefs(V1, V2)) {
            // CASE 1.2: [S1, C0, C1, ...] + [S2, C0, C1, ...]= [S1+S2, C0, C1, ...]

            tvec V;
            V.push_back(sigAdd(V1[0], V2[0]));
            for (unsigned int i = 1; i < V1.size(); i++) {
                V.push_back(V1[i]);
            }
            return sigFIR(V);
        } else if (haveComplementaryCoefs(V1, V2)) {
            // CASE 1.3: [S1, C0, C1, ...] + [S2, -C0, -C1, ...]= [S1-S2, C0, C1, ...]
            tvec V;
            V.push_back(sigSub(V1[0], V2[0]));
            for (unsigned int i = 1; i < V1.size(); i++) {
                V.push_back(V1[i]);
            }
            return sigFIR(V);
#endif
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
    } else {
        // CASE 3: Not a FIR

        return simplify(sigMul(s1, s2));
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
    tvec V;
    if (isSigFIR(sig, V)) {
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
        if (lnz == 1) {
            // not a real FIR
            return simplify(sigMul(V[0], V[1]));
        }
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