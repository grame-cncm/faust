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
        // LEADING ZEROS become an outer delay : FIR[x, 0..0, C] is the
        // dense kernel FIR[x, C] delayed (time invariance, exact). Two
        // SHIFTED WINDOWS of the same source then hash-cons to the SAME
        // dense kernel plus two delays -- the sharing the FFT's 283
        // shifted pairs were waiting for. The dense form also feeds the
        // sliding-sum and symmetry detections better.
        {
            size_t z = 1;
            while (z < coef.size() && isZero(coef[z])) {
                z++;
            }
            // CONSTANT coefficients only : time invariance is what makes
            // the rewrite exact, and a delayed kernel evaluates its
            // coefficients k samples EARLIER -- with slider-driven or
            // smoothed coefficients (vocalFOF) the two forms differ
            // STRUCTURALLY (3e-04 surviving the -double discriminator).
            bool numeric = true;
            for (size_t i = z; numeric && i < coef.size(); i++) {
                int     ni;
                int64_t n64;
                double  nr;
                numeric = isZero(coef[i]) || isSigInt(coef[i], &ni) ||
                          isSigInt64(coef[i], &n64) || isSigReal(coef[i], &nr);
            }
            if (numeric && z > 1 && z < coef.size() && coef.size() - z >= 2) {
                // (>= 2 taps denses : la forme a 1 coefficient serait un
                // gain retarde, et sigFIR[x,c0] exige une source audio)
                tvec dense;
                dense.push_back(coef[0]);
                for (size_t i = z; i < coef.size(); i++) {
                    dense.push_back(coef[i]);
                }
                return sigDelay(sigFIR(dense), sigInt(int(z) - 1));
            }
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
