#include "factorizeFIRIIRs.hh"
#include "ppsig.hh"
#include "sigIdentity.hh"
#include "signals.hh"

#define TRACE false

//---------------Private implementation-----------------

// Transform FIRs by factorizing common coefficients when possible
class FIRFactorizer : public SignalIdentity {
   protected:
    Tree transformation(Tree sig);
    Tree postprocess(Tree L);
    bool hasCommonCoef(const tvec& C, Tree& factor, tvec& newC);
};

/**
 * @brief Determine if the coefficients C of a FIR can be factorized. If thats possible, it returns
 * the new factorized coefficients and the common factor.
 *
 * @param C the vector of coefficients
 * @param commonfactor the common factor if factorisation is possible
 * @param newC the new vector of coefficients if factorization is possible
 * @return true, factorization is possible
 * @return false, factorization is not possible
 */
bool FIRFactorizer::hasCommonCoef(const tvec& C, Tree& commonfactor, tvec& newC)
{
    // compute the most common factor and its number of occurrences
    std::map<Tree, int> coefOcc;
    Tree                factor    = gGlobal->nil;
    int                 nbfactors = 0;
    int                 maxocc    = 0;
    for (unsigned int i = 1; i < C.size(); i++) {
        Tree c = C[i];
        // we analyze all non zero factors
        if (!isZero(c)) {
            nbfactors++;
            if (coefOcc.find(c) == coefOcc.end()) {
                coefOcc[c] = 1;
            } else {
                coefOcc[c]++;
            }
            if (coefOcc[c] > maxocc) {
                maxocc = coefOcc[c];
                factor = c;
            }
        }
    }
    // std::cerr << "factor: " << ppsig(factor) << " count: " << maxocc << " nbfactors: " <<
    // nbfactors
    //           << std::endl;
    // Case 1: the common factor is equal to all nz coefficients
    if (maxocc == nbfactors) {
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

Tree FIRFactorizer::transformation(Tree sig)
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

Tree FIRFactorizer::postprocess(Tree sig)
{
    // std::cerr << "Postprocess: " << ppsig(sig) << std::endl;
    if (tvec coef; isSigFIR(sig, coef)) {
        // std::cerr << "factorizeFIRIIRs: FIR " << ppsig(sig) << std::endl;
        Tree factor;
        tvec newCoef;
        if (hasCommonCoef(coef, factor, newCoef)) {
            if (isOne(factor)) {
                return sigFIR(newCoef);
            }
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
    FIRFactorizer F;
    F.trace(TRACE, "factorizeFIRs");
    Tree L2 = F.mapself(L1);
    return L2;
}
