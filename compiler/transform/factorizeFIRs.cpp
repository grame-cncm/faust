#include "factorizeFIRs.hh"

#include "global.hh"
#include "rewrite.hh"

// FIR[x, c0..cn] with every non-zero coefficient EQUAL (hash-consing
// makes this pointer equality) : extract the gain. Coefficients equal to
// one are already extracted by construction.
Tree factorizeFIRs(Tree L)
{
    auto rule = [](Tree sig) -> Tree {
        tvec coef;
        if (!isSigFIR(sig, coef) || coef.size() < 3) {
            return sig;
        }
        Tree factor = nullptr;
        for (size_t i = 1; i < coef.size(); i++) {
            if (isZero(coef[i])) {
                continue;
            }
            if (factor == nullptr) {
                factor = coef[i];
            } else if (coef[i] != factor) {
                return sig;  // not a common factor
            }
        }
        if (factor == nullptr || isOne(factor)) {
            return sig;  // degenerated, or already normalized
        }
        tvec ones;
        ones.push_back(coef[0]);
        for (size_t i = 1; i < coef.size(); i++) {
            ones.push_back(isZero(coef[i]) ? coef[i] : sigInt(1));
        }
        return sigMul(factor, sigFIR(ones));
    };
    return treeRewrite(L, rule);
}
