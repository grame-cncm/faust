#include <math.h>
#include <stdio.h>
#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "Schedule.hh"
#include "Text.hh"
#include "compatibility.hh"
#include "compile.hh"
#include "compile_scal.hh"
#include "dlcodegen.hh"
#include "factorizeFIRIIRs.hh"
#include "floats.hh"
#include "normalform.hh"
#include "ppsig.hh"
#include "prim2.hh"
#include "recursivness.hh"
#include "revealFIR.hh"
#include "revealIIR.hh"
#include "revealSum.hh"
#include "sharing.hh"
#include "sigDependenciesGraph.hh"
#include "sigNewConstantPropagation.hh"
#include "sigPromotion.hh"
#include "sigRecursiveDependencies.hh"
#include "sigRetiming.hh"
#include "sigToGraph.hh"
#include "sigprint.hh"
#include "sigtype.hh"
#include "timing.hh"
#include "xtended.hh"

using namespace std;

string ScalarCompiler::generateFIR(Tree sig, const tvec& coefs)
{
    faustassert(coefs.size() > 1);
    float density = computeDensity(coefs);
    if (coefs.size() == 2) {
        // special case for a simple gain
        return generateCacheCode(sig, subst("($0) * ($1)", CS(coefs[1]), CS(coefs[0])));
    }
    bool r1 = density * 100 < gGlobal->gMinDensity;
    bool r2 = int(coefs.size()) - 1 < gGlobal->gFirLoopSize;
    if (r1 || r2) {
        // we don't use a loop for small or low density FIR filters
        std::ostringstream oss;
        string             sep = "";
        Tree               exp = coefs[0];  // The input signal of the FIR

        // build the comment explaining this choice
        std::string comment = " /* ";
        comment += r1 ? "low-density " : "";
        comment += r2 ? "small " : "";
        comment += "FIR filter */";

        // build the FIR expression
        oss << '(';
        for (unsigned int i = 1; i < coefs.size(); ++i) {
            if (isZero(coefs[i])) {
                continue;
            }
            string access = generateDelayAccess(sig, exp, i - 1);
            if (isOne(coefs[i])) {
                oss << sep << access;
            } else if (Tree x, y; isSigAdd(coefs[i], x, y) || isSigSub(coefs[i], x, y)) {
                oss << sep << '(' << CS(coefs[i]) << ") * " << access;
            } else {
                oss << sep << CS(coefs[i]) << " * " << access;
            }
            sep = " + ";
        }
        oss << ')' << comment;

        return generateCacheCode(sig, oss.str());
    } else {
        // tous les coefs sont connus à la compilation et on peut declarer un tableau de
        // constantes statiques certains coefs sont connus à l'initialisation et on peut
        // declarer un tableau remplis dans la méthode init certains coefficients sont des
        // controles et on peut déclarer un tableau en début de compute certains coefficients
        // sont des signaux et on doit déclarer le tableau dans la boucle d'échantillons

        // 1) THE COEFFICIENT TABLE

        Type tc;  // Common type for all coefficients
        for (unsigned int i = 1; i < coefs.size(); ++i) {
            Type t = getCertifiedSigType(coefs[i]);
            if (i == 1) {
                tc = t;
            } else {
                tc = tc | t;
            }
        }

        // identifier for the coef table
        std::string ctype, ctable;
        getTypedNames(tc, "FIRCoefs", ctype, ctable);

        // Expression for the coefficients
        int mnzc = 1 << 20;  // minimum non zero coef

        std::ostringstream coefInitStream;
        coefInitStream << "{";
        for (unsigned int i = 1; i < coefs.size(); ++i) {
            if (i > 1) {
                coefInitStream << ", ";
            }
            if (!isZero(coefs[i]) && (int(i) < mnzc)) {
                // first non zero coef
                mnzc = i;
            }
            coefInitStream << CS(coefs[i]);
        }
        coefInitStream << "}";
        std::string coefInit = coefInitStream.str();

        // Declaration of the coefficient table
        std::string csize      = T(int(coefs.size() - 1));
        std::string ctabledecl = subst("const $0 \t$1[$2] = $3;", ctype, ctable, csize, coefInit);
        switch (tc->variability()) {
            case kKonst:
                if (tc->computability() == kComp) {
                    fClass->addDeclCode(ctabledecl);
                } else {
                    // special case for constant coefficients that can only be computed at init
                    // time
                    fClass->addDeclCode(subst("$0 \t$1[$2];", ctype, ctable, csize));
                    fClass->addInitCode(
                        subst("const $0 \t$1tmp[$2] = $3;", ctype, ctable, csize, coefInit));
                    fClass->addInitCode(
                        subst("for (int i = 0; i < $0; i++) { $1[i] = $1tmp[i]; }", csize, ctable));
                }
                break;
            case kBlock:
                fClass->addZone2(ctabledecl);
                break;
            case kSamp:
                fClass->addExecCode(Statement("", ctabledecl));
                break;
            default:
                faustassert(false);
        }

        // 2) THE FIR ACCUMULATION

        Tree        exp = coefs[0];  // The input signal of the FIR
        std::string idxaccess =
            generateDelayAccess(sig, exp, "ii");  // indexed access to the input signal

        // Type of the FIR itself (potentially different from the common type of the
        // coefficients)
        Type        ty = getCertifiedSigType(sig);
        std::string ftype, facc;
        getTypedNames(ty, "Acc", ftype, facc);

        // Declaration of the FIR accumulation
        fClass->addExecCode(Statement("", subst("$0 \t$1 = 0;", ftype, facc)));

        // if (mnzc > 1) {
        // std::cerr << "FIR filter non-zero coef: " << mnzc - 1 << " to " << coefs.size() - 2
        //   << "\n";
        // }
        // Code for the accumulation loop
        if (gGlobal->gHLSUnrollFactor > 0) {
            // we want an HLS unroll pragma here
            std::string l[4];
            l[0] = subst("for (int ii = $0; ii < $1; ii++) {", T(mnzc - 1), T(coefs.size() - 1));
            l[1] = subst("\t#pragma HLS unroll factor=$0", T(gGlobal->gHLSUnrollFactor));
            l[2] = subst("\t$0 += $1[ii] * $2;", facc, ctable, idxaccess);
            l[3] = "}";
            fClass->addExecCode(Statement("", l[0]));
            fClass->addExecCode(Statement("", l[1]));
            fClass->addExecCode(Statement("", l[2]));
            fClass->addExecCode(Statement("", l[3]));
        } else {
            std::string accloop = subst(
                "for (int ii = $4; ii < $0; ii++) { $1 += $2[ii] * $3; } /* Loop based FIR acc. */",
                T(int(coefs.size() - 1)), facc, ctable, idxaccess, T(mnzc - 1));
            fClass->addExecCode(Statement("", accloop));
        }
        return generateCacheCode(sig, facc);
    }
}
