
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

string ScalarCompiler::generateIIR(Tree sig, const tvec& coefs)
{
    // IIR[-,X,0,b,c,...]
    // idx 0,1,2,3,4,....
    // for (int i0 = 0; i0 < count; i0 = i0 + 1) {
    //     fRec0[IOTA0 & 1] = float(input0[i0]) + 0.5f * fRec0[(IOTA0 - 1) & 1];
    //     output0[i0]      = FAUSTFLOAT(fRec0[IOTA0 & 1]);
    //     IOTA0            = IOTA0 + 1;
    // }

    Type         ty = getCertifiedSigType(sig);
    Occurrences* o  = fOccMarkup->retrieve(sig);

    faustassert(o);
    faustassert(coefs.size() > 2);

    std::string vname, ctype;
    getTypedNames(ty, "IIR", ctype, vname);

    // std::cerr << gGlobal->gSTEP << " generateIIR: " << ppsig(sig) << std::endl;

    // Build the IIR expressions X + C1*Y(t-1) + C2*Y(t-2) + ...
    std::ostringstream oss;
    oss << CS(coefs[1]);  // the input signal X

    // Invert the order of computation has it seems faster
    // for (unsigned int i = 3; i < coefs.size(); ++i) {
    for (unsigned int i = coefs.size() - 1; i >= 3; i--) {
        if (isZero(coefs[i])) {
            continue;
        }
        string access = generateDelayAccess(sig, sig, i - 2);
        if (isOne(coefs[i])) {
            oss << " + " << access;
        } else {
            oss << " + "
                << "(" << CS(coefs[i]) << ") * " << access;
        }
    }
    std::string exp = oss.str();

    // generate the delay line
    std::string Y0 = generateDelayVec(sig, exp, ctype, vname, o->getMaxDelay(), o->getDelayCount());
    // return the current value
    return Y0;
}

#if 0
string ScalarCompiler::generateIIRSmallExpression(const string& dlname, Tree sig, const tvec& coefs)
{
    std::ostringstream oss;
    oss << CS(coefs[1]);  // the input signal

    for (int unsigned i = 3; i < coefs.size(); i++) {
        if (isZero(coefs[i])) {
            continue;
        }
        string idx = "[" + to_string(i - 2) + "]";
        if (isOne(coefs[i])) {
            oss << " + " << dlname << idx;
        } else {
            oss << " + "
                << "(" << CS(coefs[i]) << ") * " << dlname << idx;
        }
    }
    oss << "/*IIR small expression*/";

    return oss.str();
}

string ScalarCompiler::generateIIRBigExpression(const string& dlname, int mxd, Tree sig,
                                                const tvec& coefs)
{
    int N = pow2limit(mxd + 1);

    std::ostringstream oss;
    oss << CS(coefs[1]);  // the input signal

    for (int i = 2; i < int(coefs.size()); ++i) {
        if (isZero(coefs[i])) {
            continue;
        }
        string idx = subst("$0[(IOTA-$2)&$1]", dlname, T(N - 1), T(i - 2));
        if (isOne(coefs[i])) {
            oss << " + " << idx;
        } else {
            oss << " + "
                << "(" << CS(coefs[i]) << ") * " << idx;
        }
    }
    oss << "/*IIR big expression*/";
    return oss.str();
}
#endif
