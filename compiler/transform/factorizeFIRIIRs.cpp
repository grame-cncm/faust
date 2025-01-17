#include "factorizeFIRIIRs.hh"
#include "ppsig.hh"
#include "sigIdentity.hh"
#include "signals.hh"

#define TRACE false

//---------------Private implementation-----------------

// Transform FIRs and IIRs by factorizing common coefficients when possible
class FIRIIRFactorizer : public SignalIdentity {
   protected:
    Tree transformation(Tree sig);
    Tree postprocess(Tree L);
    bool hasCommonCoef(const tvec& C, Tree& factor, tvec& newC);
};

bool FIRIIRFactorizer::hasCommonCoef(const tvec& C, Tree& commonfactor, tvec& newC)
{
    // compute the most common factor and its number of occurrences
    std::map<Tree, int> coefMap;
    Tree                factor    = gGlobal->nil;
    int                 nbfactors = 0;
    int                 maxCoef   = 0;
    for (int i = 1; i < C.size(); i++) {
        Tree c = C[i];
        // we analyze all non zero factors
        if (!isZero(c)) {
            nbfactors++;
            if (coefMap.find(c) == coefMap.end()) {
                coefMap[c] = 1;
            } else {
                coefMap[c]++;
            }
            if (coefMap[c] > maxCoef) {
                maxCoef = coefMap[c];
                factor  = c;
            }
        }
    }
    // std::cerr << "factor: " << ppsig(factor) << " count: " << maxCoef << " nbfactors: " <<
    // nbfactors
    //           << std::endl;
    // Case 1: the common factor is equal to all nz coefficients
    if (maxCoef == nbfactors) {
        for (Tree c : C) {
            if (c == factor) {
                newC.push_back(sigInt(1));
            } else {
                newC.push_back(c);
            }
        }
        commonfactor = factor;
        return true;
    }

    return false;
}

Tree FIRIIRFactorizer::transformation(Tree sig)
{
    Tree var, le;
    if (isRec(sig, var, le)) {
        Tree var2 = tree(unique("MM"));
        Tree rec2 = rec(var2, gGlobal->nil);
        traceMsg("WARNING: We have set the definitions to nil for group", rec2);
        fResult.set(sig, rec2);     // We rename the recgroup
        Tree l2   = mapself(le);    // We transfom its definitions
        Tree rec3 = rec(var2, l2);  // We update the definition
        traceMsg("WARNING: We have updated the definitions of group", rec3);
        return rec3;

    } else {
        return SignalIdentity::transformation(sig);
    }
}

Tree FIRIIRFactorizer::postprocess(Tree sig)
{
    // std::cerr << "Postprocess: " << ppsig(sig) << std::endl;
    if (tvec coef; isSigFIR(sig, coef)) {
        // std::cerr << "factorizeFIRIIRs: FIR " << ppsig(sig) << std::endl;
        Tree factor;
        tvec newCoef;
        if (hasCommonCoef(coef, factor, newCoef)) {
            return sigMul(factor, sigFIR(newCoef));
        }
    }
    return sig;
}

//----------------------Public API----------------------
/**
 * @brief Factorize the IIRs and FIRs in the list of signals L
 *
 * @param L the list of signal to transform
 * @return L' the transformed list of signals
 */
Tree factorizeFIRIIRs(Tree L1)
{
    // FIRIIRFactorizer F;
    // F.trace(TRACE, "fractorizeFIRIIRs");
    // Tree L2 = F.mapself(L1);
    // return L2;
    FIRIIRFactorizer F;
    F.trace(TRACE, "factorizeFIRIIRs");
    Tree L2 = F.mapself(L1);
    return L2;
}
