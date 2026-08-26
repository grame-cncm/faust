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

// constant-class test of a coefficient vector (numeric or init-time)
static bool constClass(const tvec& c)
{
    for (size_t i = 1; i < c.size(); i++) {
        if (sigs::sigOrder(c[i]) > 1) {
            return false;
        }
    }
    return true;
}

Tree factorizeFIRs(Tree L)
{
    static int gSeenDelay = 0, gSeenDelayOfFIR = 0;
    auto rule = [](Tree sig) -> Tree {
        {
            Tree a, b;
            if (isSigDelay(sig, a, b)) {
                gSeenDelay++;
                if (isSigFIR(a)) {
                    gSeenDelayOfFIR++;
                }
            }
        }
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
                        // a unit coefficient absorbs k itself -- sigMul(k, 1)
                        // would emit a (1 * k) per sample
                        nc.push_back(isZero(coef[i]) ? coef[i]
                                     : isOne(coef[i]) ? k
                                                      : sigMul(k, coef[i]));
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
        // CASCADE LAW (spec LA-FORME-NOYAU, section 2, constant class) :
        // FIR[FIR[x, P], Q] = FIR[x, P (*) Q] -- composition is ordinary
        // polynomial convolution when BOTH coefficient vectors are
        // constant-class. This subsumes the shifted read (Q a monomial)
        // and eliminates the intermediate kernel VALUE entirely : the
        // plate's stencil kernels, read one sample back by their own
        // grid recursion through a nested kernel, each carried a State
        // pair -- flattened, the reads land on the projection's ring.
        // Restricted to projection sources, like the shift-in below.
        {
            tvec oc, ic;
            int  pi2;
            Tree pw2;
            if (isSigFIR(sig, oc) && oc.size() >= 2 && isSigFIR(oc[0], ic) &&
                isProj(ic[0], &pi2, pw2) && constClass(oc) && constClass(ic)) {
                int  n = int(ic.size()) - 1, m = int(oc.size()) - 1;
                tvec conv;
                conv.push_back(ic[0]);
                for (int k = 0; k < n + m - 1; k++) {
                    Tree acc = nullptr;
                    for (int i = 0; i < n; i++) {
                        int j = k - i;
                        if (j < 0 || j >= m) {
                            continue;
                        }
                        if (isZero(ic[1 + i]) || isZero(oc[1 + j])) {
                            continue;
                        }
                        Tree term = (isOne(ic[1 + i])) ? oc[1 + j]
                                    : (isOne(oc[1 + j])) ? ic[1 + i]
                                                         : sigMul(ic[1 + i], oc[1 + j]);
                        acc = acc ? sigAdd(acc, term) : term;
                    }
                    conv.push_back(acc ? acc : sigInt(0));
                }
                if (getenv("FAUST_FIRNORM_DEBUG")) {
                    fprintf(stderr, "FIRNORM cascade n=%d m=%d\n", n, m);
                }
                return sigFIR(conv);
            }
        }
        // SHIFT-IN LAW (spec LA-FORME-NOYAU, section 2, constant class) :
        // a kernel value read DELAYED is a kernel with a SHIFTED
        // polynomial -- K@d = FIR[x, z^-d . P]. Without it, every
        // delayed consumer of a kernel value gives the OPERATOR a
        // carried state pair (2dKirchhoffThinPlate : 360 State scalars,
        // one per stencil kernel read one sample back by its own grid
        // recursion) ; with it, the reads land on the source's existing
        // ring. Restricted to RECURSIVE PROJECTION sources : the dense
        // shifted windows of FFT-like programs (inputs) keep their
        // shared-kernel extraction.
        {
            Tree fk, dd;
            int  dv, pi;
            Tree pw;
            tvec kc;
            if (isSigDelay(sig, fk, dd) && isSigInt(dd, &dv) && dv > 0 && isSigFIR(fk, kc) &&
                isProj(kc[0], &pi, pw)) {
                bool constantClass = true;
                for (size_t i = 1; constantClass && i < kc.size(); i++) {
                    constantClass = (sigs::sigOrder(kc[i]) <= 1);
                }
                if (constantClass) {
                    if (getenv("FAUST_FIRNORM_DEBUG")) {
                        fprintf(stderr, "FIRNORM shift-in d=%d\n", dv);
                    }
                    tvec shifted;
                    shifted.push_back(kc[0]);
                    for (int z2 = 0; z2 < dv; z2++) {
                        shifted.push_back(sigInt(0));
                    }
                    for (size_t i = 1; i < kc.size(); i++) {
                        shifted.push_back(kc[i]);
                    }
                    return sigFIR(shifted);
                }
            }
        }
        tvec coef;
        if (!isSigFIR(sig, coef)) {
            return sig;
        }
        // ENVELOPE NORMALIZATION (spec LA-FORME-NOYAU, section 3) : the
        // canonical envelope is level * (kernel(source) @ delay), level
        // OUTSIDE the delay. A single-tap kernel therefore collapses to
        // its envelope spelling -- legal in BOTH coefficient classes,
        // because the level stage never crosses the delay (the vocalFOF
        // trap, avoided by construction) :
        //   FIR[x, c]         -> c * x          (order-0 kernel, unit level absent)
        //   FIR[x, 0..0, 1]   -> x @ d          (the pure monomial)
        //   FIR[x, 0..0, c]   -> c * (x @ d)
        // The plate measured why : each shared monomial READ, spelled as
        // a kernel, becomes a cacheable value node (360 scalar caches on
        // 2dKirchhoffThinPlate against 0 in the free world) where the
        // bare delayed read is a buffer access that costs nothing.
        {
            int nz = 0, pos = 0;
            for (size_t i = 1; i < coef.size(); i++) {
                if (!isZero(coef[i])) {
                    nz++;
                    pos = int(i) - 1;
                }
            }
            if (nz == 0) {
                return sigReal(0.0);  // zero polynomial : the signal 0, never a FIR
            }
            if (nz == 1) {
                Tree c = coef[1 + pos];
                Tree r;
                if (pos == 0) {
                    r = coef[0];
                } else {
                    // delayed read of a constant-class projection kernel :
                    // shift IN rather than build Delay(FIR) (the one-shot
                    // rewrite would never revisit it)
                    tvec ic2;
                    int  pj;
                    Tree pw3;
                    if (isSigFIR(coef[0], ic2) && isProj(ic2[0], &pj, pw3) && constClass(ic2)) {
                        tvec sh;
                        sh.push_back(ic2[0]);
                        for (int z2 = 0; z2 < pos; z2++) {
                            sh.push_back(sigInt(0));
                        }
                        for (size_t i = 1; i < ic2.size(); i++) {
                            sh.push_back(ic2[i]);
                        }
                        r = sigFIR(sh);
                    } else {
                        r = sigDelay(coef[0], sigInt(pos));
                    }
                }
                return isOne(c) ? r : sigMul(c, r);
            }
        }
        if (coef.size() < 3) {
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
            // NEVER on a projection source : extracting the monomial
            // turns the kernel into a DELAYED OPERATOR VALUE, and the
            // emitter gives it a carried state pair -- 2dKirchhoff's 360
            // State scalars were exactly rule 1's own output on stencil
            // kernels. Leading zeros kept IN, the taps read the
            // projection's existing ring at 1..n : no entity at all.
            // Non-recursive sources keep the extraction (the shared
            // dense windows of the FFT family).
            int  pj4;
            Tree pw5;
            if (constant && z > 1 && z < coef.size() && coef.size() - z >= 2 &&
                !isProj(coef[0], &pj4, pw5)) {
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
        fprintf(stderr, "FIRNORM visited : delay=%d delay-of-FIR=%d\n", gSeenDelay, gSeenDelayOfFIR);
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
        // nature des sources des noyaux survivants
        {
            std::unordered_map<Tree, bool> seen2;
            int nfir = 0, srcProj = 0, srcFir = 0, srcDelay = 0, srcOther = 0, ccl = 0;
            std::function<void(Tree)>      w2 = [&](Tree t) {
                if (seen2.count(t)) {
                    return;
                }
                seen2[t] = true;
                Tree var, body;
                if (isRec(t, var, body)) {
                    if (body) w2(body);
                    return;
                }
                if (tvec c; isSigFIR(t, c)) {
                    nfir++;
                    int  pi3;
                    Tree pw4, a, b;
                    if (isProj(c[0], &pi3, pw4)) srcProj++;
                    else if (isSigFIR(c[0])) srcFir++;
                    else if (isSigDelay(c[0], a, b)) srcDelay++;
                    else srcOther++;
                    if (constClass(c)) ccl++;
                    if (nfir <= 3) {
                        std::cerr << "  FIRNORM survivor src=" << ppsig(c[0], 2)
                                  << " taps=" << (c.size() - 1) << std::endl;
                    }
                }
                for (int k = 0; k < t->arity(); k++) {
                    w2(t->branch(k));
                }
            };
            w2(R);
            fprintf(stderr,
                    "FIRNORM post : fir=%d srcProj=%d srcFir=%d srcDelay=%d srcOther=%d "
                    "constClass=%d\n",
                    nfir, srcProj, srcFir, srcDelay, srcOther, ccl);
        }
    }
    return R;
}
