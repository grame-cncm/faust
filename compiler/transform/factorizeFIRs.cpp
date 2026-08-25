#include "factorizeFIRs.hh"

#include <cmath>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "global.hh"
#include "ppsig.hh"
#include "rewrite.hh"
#include "sigs-state.hh"

// The kernel normal form, three rules in one bottom-up pass. A kernel is
// a polynomial : everything a polynomial admits -- delay extraction,
// scalar factorization, constant folding into coefficients -- is done
// HERE, because the generic signal simplifier does not see through
// FIR[...] nodes (the bells lesson : 49 modes emitting (-1) * (g * ...)
// chains per sample that the canonical form folds away).
//
//  1. Leading zeros become an outer delay (constant coefficients only) :
//     FIR[x, 0..0, C] == Delay(FIR[x, C]) by time invariance.
//  2. Proportional coefficients factor out : when every non-zero
//     coefficient is r_i * u with the SAME symbolic part u and NUMERIC
//     ratios r_i, the kernel becomes u * FIR[x, r...]. The numeric
//     kernel is then shared by hash-consing across every consumer with
//     the same shape : the 49 modes of a bell all read g_i * [1,0,-1],
//     one shared difference serves them all, as the canonical form did.
//  3. Scalar multipliers absorb : k1 * (k2 * ... * FIR[x, c...]) with
//     the k's control-rate or slower and NON-proportional coefficients
//     folds the k's into the coefficients, which are evaluated at
//     control rate -- the sample loop loses the outer multiplies (and
//     the (-1) * (...) sign chains). A numeric kernel of two or more
//     taps is never absorbed into : that would destroy the sharing rule
//     2 just built, and the pair of rules would cycle.

// c -> (r, u) with c == r * u, r numeric, u symbolic (nullptr for a
// pure number). Recognizes numbers and products with a numeric side.
static bool numericHead(Tree c, double& r, Tree& u)
{
    double f;
    int    i;
    if (isDouble(c->node(), &f)) {
        r = f;
        u = nullptr;
        return true;
    }
    if (isInt(c->node(), &i)) {
        r = double(i);
        u = nullptr;
        return true;
    }
    Tree x, y;
    if (isSigMul(c, x, y)) {
        if (isDouble(x->node(), &f)) {
            r = f;
            u = y;
            return true;
        }
        if (isInt(x->node(), &i)) {
            r = double(i);
            u = y;
            return true;
        }
        if (isDouble(y->node(), &f)) {
            r = f;
            u = x;
            return true;
        }
        if (isInt(y->node(), &i)) {
            r = double(i);
            u = x;
            return true;
        }
    }
    r = 1.0;
    u = c;
    return true;
}

// a factor that evaluates at control rate or slower. sigOrder alone is
// too pessimistic here : a table read whose index is slow IS slow, but
// the table generator's init-time recursions poison the kind bits (the
// documented pessimism) -- and the per-mode strike and t60 gains of the
// bells are exactly such reads.
static bool isSlowFactor(Tree t)
{
    if (sigs::sigOrder(t) <= 2) {
        return true;
    }
    Tree tb, ri;
    if (isSigRDTbl(t, tb, ri)) {
        return sigs::sigOrder(ri) <= 2;
    }
    return false;
}

// numeric ratio as the smallest faithful tree
static Tree ratioTree(double r)
{
    if (r == std::rint(r) && std::fabs(r) < 2147483647.0) {
        return sigInt(int(r));
    }
    return sigReal(r);
}

Tree factorizeFIRs(Tree L)
{
    auto rule = [](Tree sig) -> Tree {
        // ---- rule 3 : absorption of scalar multiply chains ------------
        if (Tree mx, my; isSigMul(sig, mx, my)) {
            std::vector<Tree>         scalars;
            std::vector<Tree>         firs;
            bool                      flat_ok = true;
            std::function<void(Tree)> flat    = [&](Tree t) {
                Tree a, b;
                if (isSigMul(t, a, b)) {
                    flat(a);
                    flat(b);
                } else if (tvec c; isSigFIR(t, c)) {
                    firs.push_back(t);
                } else if (isSlowFactor(t)) {
                    scalars.push_back(t);
                } else {
                    flat_ok = false;  // an audio factor : not our pattern
                }
            };
            flat(sig);
            if (flat_ok && firs.size() == 1 && !scalars.empty()) {
                tvec coef;
                isSigFIR(firs[0], coef);
                int  nz       = 0;
                bool numeric  = true;
                int  maxOrder = 0;
                for (size_t i = 1; i < coef.size(); i++) {
                    if (isZero(coef[i])) {
                        continue;
                    }
                    nz++;
                    numeric  = numeric && isNum(coef[i]);
                    maxOrder = std::max(maxOrder, sigs::sigOrder(coef[i]));
                }
                // a shared numeric kernel stays shared ; audio-rate
                // coefficients would pay the fold per sample and per tap
                bool absorb = (nz >= 1) && !(numeric && nz >= 2) && (maxOrder <= 2 || nz == 1);
                if (absorb) {
                    if (getenv("FAUST_FIRNORM_DEBUG")) {
                        fprintf(stderr, "FIRNORM absorb scalars=%zu nz=%d\n", scalars.size(), nz);
                    }
                    Tree k = scalars[0];
                    for (size_t i = 1; i < scalars.size(); i++) {
                        k = sigMul(k, scalars[i]);
                    }
                    tvec nc;
                    nc.push_back(coef[0]);
                    for (size_t i = 1; i < coef.size(); i++) {
                        nc.push_back(isZero(coef[i]) ? coef[i] : sigMul(k, coef[i]));
                    }
                    return sigFIR(nc);
                }
                // kept kernel : still REGROUP the scalar chain around it,
                // so k1 * (FIR * k2) costs ONE sample multiply (the
                // product of the k's evaluates at control rate)
                if (scalars.size() >= 2) {
                    Tree k = scalars[0];
                    for (size_t i = 1; i < scalars.size(); i++) {
                        k = sigMul(k, scalars[i]);
                    }
                    Tree regrouped = sigMul(firs[0], k);
                    if (regrouped != sig) {
                        if (getenv("FAUST_FIRNORM_DEBUG")) {
                            fprintf(stderr, "FIRNORM regroup scalars=%zu\n", scalars.size());
                        }
                        return regrouped;
                    }
                }
                if (getenv("FAUST_FIRNORM_DEBUG")) {
                    fprintf(stderr, "FIRNORM keep scalars=%zu nz=%d numeric=%d maxOrder=%d\n",
                            scalars.size(), nz, numeric, maxOrder);
                }
            }
            return sig;
        }
        tvec coef;
        if (!isSigFIR(sig, coef) || coef.size() < 3) {
            return sig;
        }
        // ---- rule 1 : leading zeros become an outer delay -------------
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
            bool constant = true;
            for (size_t i = z; constant && i < coef.size(); i++) {
                constant = (sigs::sigOrder(coef[i]) <= 1);  // number or constant
            }
            if (constant && z > 1 && z < coef.size() && coef.size() - z >= 2) {
                // (>= 2 dense taps : the 1-coefficient form would be a
                // delayed gain, and sigFIR[x,c0] requires an audio source)
                tvec dense;
                dense.push_back(coef[0]);
                for (size_t i = z; i < coef.size(); i++) {
                    dense.push_back(coef[i]);
                }
                return sigDelay(sigFIR(dense), sigInt(int(z) - 1));
            }
        }
        // ---- rule 2 : proportional coefficients factor out ------------
        {
            Tree                u  = nullptr;
            int                 nz = 0;
            bool                proportional = true;
            bool                allNumeric   = true;
            std::vector<double> ratio(coef.size(), 0.0);
            for (size_t i = 1; proportional && i < coef.size(); i++) {
                if (isZero(coef[i])) {
                    continue;
                }
                double r;
                Tree   ui;
                numericHead(coef[i], r, ui);
                if (ui == nullptr) {
                    allNumeric = allNumeric && true;
                    // a pure number among symbolic coefficients breaks
                    // proportionality unless the whole kernel is numeric
                    if (nz > 0 && u != nullptr) {
                        proportional = false;
                    }
                } else {
                    allNumeric = false;
                    if (nz == 0 || u == nullptr) {
                        if (nz > 0 && u == nullptr) {
                            proportional = false;  // numbers came first
                        }
                        u = ui;
                    } else if (ui != u) {
                        proportional = false;  // two distinct symbolic parts
                    }
                }
                ratio[i] = r;
                nz++;
            }
            if (proportional && !allNumeric && u != nullptr && nz >= 2) {
                tvec rc;
                rc.push_back(coef[0]);
                for (size_t i = 1; i < coef.size(); i++) {
                    rc.push_back(isZero(coef[i]) ? coef[i] : ratioTree(ratio[i]));
                }
                return sigMul(u, sigFIR(rc));
            }
        }
        return sig;
    };
    Tree R = treeRewrite(L, rule);
    if (getenv("FAUST_FIRNORM_DEBUG")) {
        // post-pass census : every surviving mul-around-FIR site
        std::unordered_map<Tree, bool> seen;
        int                            sites = 0;
        std::function<void(Tree)>      walk  = [&](Tree t) {
            if (seen.count(t)) {
                return;
            }
            seen[t] = true;
            Tree x, y;
            tvec c;
            if (isSigMul(t, x, y) && (isSigFIR(x, c) || isSigFIR(y, c))) {
                if (++sites <= 5) {
                    std::cerr << "FIRNORM post mul-of-FIR : " << ppsig(t, 3) << std::endl;
                }
            }
            for (int k = 0; k < t->arity(); k++) {
                walk(t->branch(k));
            }
        };
        walk(R);
        fprintf(stderr, "FIRNORM post : %d mul-of-FIR sites left\n", sites);
    }
    return R;
}
