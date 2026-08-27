#include "factorizeFIRs.hh"

#include <cmath>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <vector>

#include "global.hh"
#include "ppsig.hh"
#include "rewrite.hh"
#include "signals.hh"
#include "sigs-state.hh"

// KERNELIZE. The reveal keeps sigFIR as its internal WORKING form (its
// merging machinery reads it) ; this pass, at the end of the chain, applies
// the kernel normal form (the same rules the former normalization pass
// applied to working kernels) and spells every surviving kernel in the
// typed core -- no sigFIR crosses the boundary :
//
//   constant coefficients            -> delay?(DENSE(x, KFORM(C)), d)
//   proportional (numeric ratios)    -> mul(u, delay?(DENSE(x, KFORM(R))))
//   single tap                       -> mul(c, delay?(x, d))   (envelope)
//   slow coefficients (residue)      -> LTVFIR[x, 0..0, C..]   (zeros INSIDE)
//
// The delayed DENSE spelling covers BOTH former forms : on a RECURSIVE
// PROJECTION source the consumers traverse it (shifted taps on the ring,
// the former zeros-inside kernel) ; on any other source it is a delayed
// read of the materialized kernel VALUE (the former Delay(FIR), which is
// what lets the FFT family share one window across shifted readers).

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

// constant-class test of a working coefficient vector (numeric or init-time)
static bool constClass(const tvec& c)
{
    for (size_t i = 1; i < c.size(); i++) {
        if (sigs::sigOrder(c[i]) > 1) {
            return false;
        }
    }
    return true;
}

// a DENSE read : bare DENSE (sh == 0) or delay(DENSE, literal)
static bool denseRead(Tree t, Tree& x, Tree& kf, int& sh)
{
    Tree a, b;
    int  d;
    if (isSigDense(t, x, kf)) {
        sh = 0;
        return true;
    }
    if (isSigDelay(t, a, b) && isSigInt(b, &d) && isSigDense(a, x, kf)) {
        sh = d;
        return true;
    }
    return false;
}

// the working vector [x, c0..cn] of a core read (the shift re-spelled as
// leading zeros), for rule inspection and cascade convolution
static bool coreWorkVec(Tree t, tvec& V)
{
    if (isSigLtvFIR(t, V)) {
        return true;
    }
    Tree x, kf;
    int  sh;
    if (denseRead(t, x, kf, sh)) {
        V.clear();
        V.push_back(x);
        for (int k = 0; k < sh; k++) {
            V.push_back(sigInt(0));
        }
        for (Tree c : kf->branches()) {
            V.push_back(c);
        }
        return true;
    }
    return false;
}

// spell a working vector in the typed core WITHOUT proportional
// extraction and WITHOUT the delay extraction (the former rules 2 and 3
// emitted their vectors once, zeros in place, and never revisited them --
// a leading-zero kernel spelled here stays an INLINE read)
static Tree spellVerbatim(const tvec& coef);

// spell a CASCADE result : structural typing WITH the delay extraction
// (the source is a projection, the consumers traverse the spelling, and
// a further outer kernel can cascade again through it)
static Tree spellCore(const tvec& coef);

// classification of a reveal-produced working kernel : the former rules
// 1 (leading zeros out, via the delayed-DENSE spelling), 2 (proportional
// factor out) and the envelope normalization, then the structural typing
static Tree classify(const tvec& coef, bool allowProportional)
{
    Tree x  = coef[0];
    int  n  = int(coef.size()) - 1;  // taps at delays 0..n-1
    int  lo = 1;
    while (lo <= n && isZero(coef[lo])) {
        lo++;
    }
    if (lo > n) {
        return sigReal(0.0);  // zero polynomial : the signal 0, never a node
    }
    int hi = n;
    while (isZero(coef[hi])) {
        hi--;  // trailing zero taps are absent reads
    }
    int d = lo - 1;
    // -- ENVELOPE NORMALIZATION : a single tap is a gain and a delay,
    //    level OUTSIDE the delay (never crossing it). A delayed read of a
    //    projection kernel folds into the kernel's own shift instead of
    //    cascading two delays.
    if (lo == hi && getenv("FAUST_KERNEL_NO_ENVELOPE")) {
        tvec lc0;
        lc0.push_back(x);
        for (int i = 1; i <= hi; i++) {
            lc0.push_back(coef[i]);
        }
        return sigLtvFIR(lc0);
    }
    if (lo == hi) {
        Tree c = coef[lo];
        Tree r;
        if (d == 0) {
            r = x;
        } else {
            Tree kx, kkf;
            int  ksh, pj;
            Tree pw;
            if (denseRead(x, kx, kkf, ksh) && isProj(kx, &pj, pw)) {
                r = sigDelay(sigDense(kx, kkf), sigInt(ksh + d));
            } else {
                r = sigDelay(x, sigInt(d));
            }
        }
        return isOne(c) ? r : sigMul(c, r);
    }
    // -- constant class -> delayed DENSE (rule 1's extraction ; on a
    //    projection source the consumers traverse it, which is the former
    //    zeros-inside spelling, emission identical)
    bool constant = true;
    for (int i = lo; constant && i <= hi; i++) {
        constant = (sigs::sigOrder(coef[i]) <= 1);
    }
    if (constant) {
        if (d > 0 && getenv("FAUST_KERNEL_NO_EXTRACT")) {
            tvec lc1;
            lc1.push_back(x);
            for (int i = 1; i <= hi; i++) {
                lc1.push_back(coef[i]);
            }
            return sigLtvFIR(lc1);
        }
        tvec tail(coef.begin() + lo, coef.begin() + hi + 1);
        Tree K = sigDense(x, sigKForm(tail));
        return (d > 0) ? sigDelay(K, sigInt(d)) : K;
    }
    // -- rule 2 : proportional coefficients factor out. Same acceptance
    //    as the former pass : a common SYMBOLIC part u with numeric
    //    ratios, at least two taps, not entirely numeric.
    if (allowProportional && !getenv("FAUST_KERNEL_NO_PROP")) {
        Tree                u            = nullptr;
        int                 nz           = 0;
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
            return sigMul(u, spellVerbatim(rc));
        }
    }
    // -- residue : LTVFIR, leading zeros INSIDE (a coefficient never
    //    crosses time), trailing zeros dropped
    tvec lc;
    lc.push_back(x);
    for (int i = 1; i <= hi; i++) {
        lc.push_back(coef[i]);
    }
    return sigLtvFIR(lc);
}

static Tree spellVerbatim(const tvec& coef)
{
    Tree x  = coef[0];
    int  n  = int(coef.size()) - 1;
    int  lo = 1;
    while (lo <= n && isZero(coef[lo])) {
        lo++;
    }
    if (lo > n) {
        return sigReal(0.0);
    }
    int hi = n;
    while (isZero(coef[hi])) {
        hi--;
    }
    // single tap : the envelope spelling (no single-tap node exists)
    if (lo == hi) {
        Tree c = coef[lo];
        int  d = lo - 1;
        Tree r = (d > 0) ? sigDelay(x, sigInt(d)) : x;
        return isOne(c) ? r : sigMul(c, r);
    }
    // no leading zeros and constant : the bare DENSE
    if (lo == 1) {
        bool constant = true;
        for (int i = 1; constant && i <= hi; i++) {
            constant = (sigs::sigOrder(coef[i]) <= 1);
        }
        if (constant) {
            tvec tail(coef.begin() + 1, coef.begin() + hi + 1);
            return sigDense(x, sigKForm(tail));
        }
    }
    // zeros in place : the inline spelling (trailing zeros dropped)
    tvec lc;
    lc.push_back(x);
    for (int i = 1; i <= hi; i++) {
        lc.push_back(coef[i]);
    }
    return sigLtvFIR(lc);
}

static Tree spellCore(const tvec& coef)
{
    return classify(coef, false);
}

Tree factorizeFIRs(Tree L)
{
    auto rule = [](Tree sig) -> Tree {
        // ---- rule 3 : absorption of scalar multiply chains ------------
        // Cores are the UNDELAYED kernels and the traversed (projection)
        // delayed DENSE -- the delayed read of a materialized kernel
        // VALUE is not a core (the level stays outside, as the former
        // pass left mul(k, Delay(FIR)) untouched).
        if (Tree mx, my; !getenv("FAUST_KERNEL_NO_ABSORB") && isSigMul(sig, mx, my)) {
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
                Tree cx, ckf;
                int  csh, pj;
                Tree pw;
                if (isSigLtvFIR(t)) {
                    cores.push_back(t);
                } else if (denseRead(t, cx, ckf, csh) &&
                           (csh == 0 || isProj(cx, &pj, pw))) {
                    cores.push_back(t);
                } else if (isSlowFactor(t)) {
                    scalars.push_back(t);
                } else {
                    flat_ok = false;  // audio factor or a kernel VALUE read
                }
            };
            flat(sig);
            if (getenv("FAUST_FIRNORM_DEBUG") && cores.size() >= 1) {
                fprintf(stderr, "FIRNORM3 mul flat_ok=%d cores=%zu scalars=%zu\n", int(flat_ok),
                        cores.size(), scalars.size());
            }
            if (flat_ok && cores.size() == 1 && !scalars.empty()) {
                tvec coef;
                coreWorkVec(cores[0], coef);
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
                if (getenv("FAUST_FIRNORM_DEBUG")) {
                    Tree qx, qkf;
                    int  qsh = -1, qpj;
                    Tree qpw;
                    char kind = isSigLtvFIR(cores[0]) ? 'L'
                                : (denseRead(cores[0], qx, qkf, qsh) ? 'D' : '?');
                    int  prj  = (kind == 'D') ? int(isProj(qx, &qpj, qpw)) : -1;
                    fprintf(stderr,
                            "FIRNORM3 absorb=%d scalars=%zu nz=%d numeric=%d maxOrder=%d "
                            "kind=%c sh=%d proj=%d\n",
                            int(absorb), scalars.size(), nz, int(numeric), maxOrder, kind, qsh,
                            prj);
                }
                if (absorb) {
                    Tree k = scalars[0];
                    for (size_t i = 1; i < scalars.size(); i++) {
                        k = sigMul(k, scalars[i]);
                    }
                    tvec nc;
                    nc.push_back(coef[0]);
                    for (size_t i = 1; i < coef.size(); i++) {
                        // a unit coefficient absorbs k itself -- sigMul(k, 1)
                        // would emit a (1 * k) per sample
                        nc.push_back(isZero(coef[i])  ? coef[i]
                                     : isOne(coef[i]) ? k
                                                      : sigMul(k, coef[i]));
                    }
                    return spellVerbatim(nc);
                }
                // kept kernel : still REGROUP the scalar chain around it,
                // so k1 * (E * k2) costs ONE sample multiply (the product
                // of the k's evaluates at control rate)
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
        // into the kernel's shift (one read site on the ring) instead of
        // cascading a line on the kernel's value
        {
            Tree fk, dd;
            int  dv;
            if (isSigDelay(sig, fk, dd) && isSigInt(dd, &dv) && dv > 0 &&
                !getenv("FAUST_KERNEL_NO_SHIFTIN")) {
                Tree kx, kkf;
                int  ksh, pj;
                Tree pw;
                if (denseRead(fk, kx, kkf, ksh) && isProj(kx, &pj, pw)) {
                    return sigDelay(sigDense(kx, kkf), sigInt(ksh + dv));
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
            Tree kx, kkf;
            int  ksh, pj;
            Tree pw;
            if (coef.size() >= 2 && denseRead(coef[0], kx, kkf, ksh) &&
                isProj(kx, &pj, pw) && constClass(coef) &&
                !getenv("FAUST_KERNEL_NO_CASCADE")) {
                tvec ic;
                ic.push_back(kx);
                for (int z2 = 0; z2 < ksh; z2++) {
                    ic.push_back(sigInt(0));
                }
                for (Tree c : kkf->branches()) {
                    ic.push_back(c);
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
                return spellCore(conv);
            }
        }
        // ---- classification of the reveal's working kernel ------------
        return classify(coef, true);
    };
    Tree R = treeRewrite(L, rule);
    if (getenv("FAUST_KERNEL_WELLFORMED") || getenv("FAUST_FIRNORM_DEBUG")) {
        // well-formedness census : no working sigFIR may survive the
        // classification ; count the core population on the way
        std::unordered_map<Tree, bool> seen;
        int                            nfir = 0, ndense = 0, nltv = 0, nkform = 0;
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
            if (isSigFIR(t)) {
                nfir++;
                if (nfir <= 3) {
                    std::cerr << "KERNELIZE surviving sigFIR : " << ppsig(t, 3) << std::endl;
                }
            }
            if (isSigDense(t)) {
                ndense++;
            }
            if (isSigLtvFIR(t)) {
                nltv++;
            }
            if (isSigKForm(t)) {
                nkform++;
            }
            for (int k = 0; k < t->arity(); k++) {
                walk(t->branch(k));
            }
        };
        walk(R);
        fprintf(stderr, "KERNELIZE post : sigFIR=%d DENSE=%d KFORM=%d LTVFIR=%d\n", nfir, ndense,
                nkform, nltv);
    }
    return R;
}
