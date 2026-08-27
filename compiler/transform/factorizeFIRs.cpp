#include "factorizeFIRs.hh"

#include <cmath>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "global.hh"
#include "ppsig.hh"
#include "rewrite.hh"
#include "signals.hh"
#include "sigs-state.hh"

// KERNELIZE, v7 : the kernel normal form on the ORDINARY signal algebra.
// No dedicated node -- every kernel is the existing n-ary sigFIR, whose
// branches are all signals, spelled as the canonical triple
//
//     k * FIR[ x@d , c0..cN ]
//
//   - ANCHORED : c0 != 0 and cN != 0. Leading zeros live in the SOURCE
//     delay (an ordinary sigDelay), trailing zeros are dropped, interior
//     zeros stay (sparse kernels).
//   - coefficients at time t : y(t) = k(t) * sum ci(t) * x(t-d-i). The
//     delay is on the source, no coefficient or level ever crosses time,
//     for EVERY class -- the vocalFOF trap is gone by construction.
//   - content extraction is UNIT-PINNED : k comes out only when one of
//     the residual coefficients is 1 or -1 (a unit tap costs nothing, so
//     the freed tap-mult pays for the outer mul ; and the pin keeps the
//     rewrite exact -- ratios are read from the structure, never divided).
//
// The materialized spelling FIR[x,C]@d (one value, one line, k loads) is
// NOT produced here : it is the retiming law, legal for constant C only,
// applied per site by kernelCandidacy right after this pass.

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

// constant-class test of a coefficient list (numeric or init-time)
static bool constCoefs(const tvec& V, size_t from)
{
    for (size_t i = from; i < V.size(); i++) {
        if (sigs::sigOrder(V[i]) > 1) {
            return false;
        }
    }
    return true;
}

// source of a kernel read : unwrap ONE literal delay. x@d -> (x, d) ;
// anything else -> (t, 0).
static Tree kernelSrc(Tree t, int& sh)
{
    Tree a, b;
    int  d;
    if (isSigDelay(t, a, b) && isSigInt(b, &d)) {
        sh = d;
        return a;
    }
    sh = 0;
    return t;
}

// delayed source, collapsing a literal delay of a literal delay (the
// kernel shifts compose : (x@a)@b reads are x@(a+b) reads)
static Tree mkShiftedSrc(Tree x, int d)
{
    if (d == 0) {
        return x;
    }
    int  sh0;
    Tree x0 = kernelSrc(x, sh0);
    return sigDelay(x0, sigInt(sh0 + d));
}

// dense spelling WITHOUT content extraction (used for law outputs the
// former pass emitted once -- cascade -- and as the residue spelling)
static Tree spellDense(Tree x, const tvec& coef, int lo, int hi)
{
    // single tap : the envelope spelling (gain and delay are canonical
    // by judgment, never a one-tap kernel)
    if (lo == hi) {
        Tree c = coef[lo];
        Tree r = (lo - 1 > 0) ? mkShiftedSrc(x, lo - 1) : x;
        return isOne(c) ? r : sigMul(c, r);
    }
    tvec nc;
    nc.push_back(mkShiftedSrc(x, lo - 1));
    for (int i = lo; i <= hi; i++) {
        nc.push_back(coef[i]);
    }
    return sigFIR(nc);
}

// classification of a reveal-produced working kernel [x, c0..cn] into
// the canonical triple
static Tree classify(const tvec& coef)
{
    Tree x  = coef[0];
    int  n  = int(coef.size()) - 1;
    int  lo = 1;
    while (lo <= n && isZero(coef[lo])) {
        lo++;
    }
    if (lo > n) {
        return sigReal(0.0);  // zero polynomial : the signal 0, never a node
    }
    int hi = n;
    while (isZero(coef[hi])) {
        hi--;  // trailing zeros are absent reads
    }
    if (lo == hi) {
        return spellDense(x, coef, lo, hi);  // envelope
    }
    // ---- content extraction, unit-pinned : coefficients r_i * u with a
    // common SYMBOLIC u, numeric ratios read from the structure, and at
    // least one ratio in {1, -1}
    {
        Tree                u            = nullptr;
        int                 nz           = 0;
        bool                proportional = true;
        bool                allNumeric   = true;
        bool                hasUnit      = false;
        std::vector<double> ratio(coef.size(), 0.0);
        for (size_t i = 1; proportional && i < coef.size(); i++) {
            if (isZero(coef[i])) {
                continue;
            }
            double r;
            Tree   ui;
            numericHead(coef[i], r, ui);
            if (ui == nullptr) {
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
            if (r == 1.0 || r == -1.0) {
                hasUnit = true;
            }
            ratio[i] = r;
            nz++;
        }
        if (proportional && !allNumeric && u != nullptr && nz >= 2 && hasUnit) {
            tvec rc;
            rc.push_back(x);
            for (size_t i = 1; i < coef.size(); i++) {
                rc.push_back(isZero(coef[i]) ? coef[i] : ratioTree(ratio[i]));
            }
            return sigMul(u, spellDense(x, rc, lo, hi));
        }
    }
    return spellDense(x, coef, lo, hi);
}

Tree factorizeFIRs(Tree L)
{
    auto rule = [](Tree sig) -> Tree {
        // ---- absorption of scalar multiply chains ---------------------
        // canonical spellings : k stays OUT of a kernel that owns a unit
        // coefficient (extraction's anti-cycle) or that is shared numeric
        // (nz >= 2, all numbers -- the hash-consed primitive kernels) ;
        // it is absorbed into every other kernel (the k*ci are slow, the
        // sample loop loses the outer multiply -- the lowShelf lesson).
        if (Tree mx, my; isSigMul(sig, mx, my)) {
            std::vector<Tree>         scalars;
            std::vector<Tree>         cores;
            bool                      flat_ok = true;
            std::function<void(Tree)> flat    = [&](Tree t) {
                Tree a, b;
                if (isSigMul(t, a, b)) {
                    flat(a);
                    flat(b);
                    return;
                }
                if (isSigFIR(t)) {
                    cores.push_back(t);
                } else if (isSlowFactor(t)) {
                    scalars.push_back(t);
                } else {
                    flat_ok = false;  // audio factor or a kernel VALUE read
                }
            };
            flat(sig);
            if (flat_ok && cores.size() == 1 && !scalars.empty()) {
                tvec coef;
                isSigFIR(cores[0], coef);
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
                // anti-cycle : extraction outputs are ALL-NUMERIC unit
                // kernels, already protected by the numeric guard below --
                // a symbolic kernel with a unit tap absorbs like any other
                // (mul(k, c) has no numeric head : no re-extraction)
                bool absorb =
                    (nz >= 1) && !(numeric && nz >= 2) && (maxOrder <= 2 || nz == 1);
                if (absorb) {
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
                // so k1 * (K * k2) costs ONE sample multiply
                if (scalars.size() >= 2) {
                    Tree k = scalars[0];
                    for (size_t i = 1; i < scalars.size(); i++) {
                        k = sigMul(k, scalars[i]);
                    }
                    Tree regrouped = sigMul(cores[0], k);
                    if (regrouped != sig) {
                        return regrouped;
                    }
                }
            }
            return sig;
        }
        // ---- SHIFT-IN LAW : a delayed read of a PROJECTION kernel folds
        // into the kernel's source shift (one read site on the ring)
        // instead of cascading a line on the kernel's value. Constant
        // coefficients only -- this is the retiming law right-to-left.
        {
            Tree fk, dd;
            int  dv;
            if (isSigDelay(sig, fk, dd) && isSigInt(dd, &dv) && dv > 0) {
                tvec kc;
                if (isSigFIR(fk, kc) && constCoefs(kc, 1)) {
                    int  ksh, pj;
                    Tree pw;
                    Tree kx = kernelSrc(kc[0], ksh);
                    if (isProj(kx, &pj, pw)) {
                        tvec nc;
                        nc.push_back(mkShiftedSrc(kx, ksh + dv));
                        for (size_t i = 1; i < kc.size(); i++) {
                            nc.push_back(kc[i]);
                        }
                        return sigFIR(nc);
                    }
                }
            }
        }
        tvec coef;
        if (!isSigFIR(sig, coef)) {
            return sig;
        }
        // ---- CASCADE LAW (constant class, projection source) : a kernel
        // of a kernel is ordinary polynomial convolution -- the nested
        // read lands on the projection's existing ring, no intermediate
        // kernel VALUE at all (the plate's stencil kernels).
        {
            tvec ic0;
            if (coef.size() >= 2 && isSigFIR(coef[0], ic0) && constCoefs(coef, 1) &&
                constCoefs(ic0, 1)) {
                int  ksh, pj;
                Tree pw;
                Tree kx = kernelSrc(ic0[0], ksh);
                if (isProj(kx, &pj, pw)) {
                    tvec ic;
                    ic.push_back(kx);
                    for (int z2 = 0; z2 < ksh; z2++) {
                        ic.push_back(sigInt(0));
                    }
                    for (size_t i = 1; i < ic0.size(); i++) {
                        ic.push_back(ic0[i]);
                    }
                    int  n = int(ic.size()) - 1, m = int(coef.size()) - 1;
                    tvec conv;
                    conv.push_back(ic[0]);
                    for (int k = 0; k < n + m - 1; k++) {
                        Tree acc = nullptr;
                        for (int i = 0; i < n; i++) {
                            int j = k - i;
                            if (j < 0 || j >= m) {
                                continue;
                            }
                            if (isZero(ic[1 + i]) || isZero(coef[1 + j])) {
                                continue;
                            }
                            Tree term = (isOne(ic[1 + i]))     ? coef[1 + j]
                                        : (isOne(coef[1 + j])) ? ic[1 + i]
                                                               : sigMul(ic[1 + i], coef[1 + j]);
                            acc = acc ? sigAdd(acc, term) : term;
                        }
                        conv.push_back(acc ? acc : sigInt(0));
                    }
                    // spell without extraction (emitted once, like the
                    // former pass)
                    int lo = 1, hi = int(conv.size()) - 1;
                    while (lo <= hi && isZero(conv[lo])) {
                        lo++;
                    }
                    if (lo > hi) {
                        return sigReal(0.0);
                    }
                    while (isZero(conv[hi])) {
                        hi--;
                    }
                    return spellDense(conv[0], conv, lo, hi);
                }
            }
        }
        // ---- classification into the canonical triple -----------------
        return classify(coef);
    };
    Tree R = treeRewrite(L, rule);
    if (getenv("FAUST_KERNEL_WELLFORMED") || getenv("FAUST_FIRNORM_DEBUG")) {
        // well-formedness census : every kernel is ANCHORED (no leading
        // zero -- the shift lives in the source delay)
        std::unordered_map<Tree, bool> seen;
        int                            nfir = 0, nbad = 0, nshifted = 0;
        std::function<void(Tree)>      walk = [&](Tree t) {
            if (seen.count(t)) {
                return;
            }
            seen[t] = true;
            Tree var, body;
            if (isRec(t, var, body)) {
                if (body) {
                    walk(body);
                }
                return;
            }
            if (tvec cs; isSigFIR(t, cs)) {
                nfir++;
                if (cs.size() < 3 || isZero(cs[1]) || isZero(cs.back())) {
                    nbad++;
                    if (nbad <= 3) {
                        std::cerr << "KERNELIZE non-anchored : " << ppsig(t, 3) << std::endl;
                    }
                }
                int  sh;
                Tree src = kernelSrc(cs[0], sh);
                (void)src;
                if (sh > 0) {
                    nshifted++;
                }
            }
            for (int k = 0; k < t->arity(); k++) {
                walk(t->branch(k));
            }
        };
        walk(R);
        fprintf(stderr, "KERNELIZE post : FIR=%d shifted=%d non-anchored=%d\n", nfir, nshifted,
                nbad);
    }
    return R;
}

bool kernelWorkVec(Tree t, tvec& V)
{
    tvec W;
    if (!isSigFIR(t, W)) {
        return false;
    }
    int  sh;
    Tree src = kernelSrc(W[0], sh);
    if (sh == 0) {
        V = W;
        return true;
    }
    V.clear();
    V.push_back(src);
    for (int k = 0; k < sh; k++) {
        V.push_back(sigInt(0));
    }
    for (size_t i = 1; i < W.size(); i++) {
        V.push_back(W[i]);
    }
    return true;
}
