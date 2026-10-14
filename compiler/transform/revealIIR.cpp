#include "revealIIR.hh"
#include <set>
#include "simplify.hh"
#include <map>
#include <functional>

#include <iostream>
#include <numeric>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "DirectedGraph.hh"
#include "DirectedGraphAlgorythm.hh"
#include "global.hh"
#include "ppsig.hh"
#include "rewrite.hh"
#include "sigFIR.hh"
#include "sigIIR.hh"
#include "sigs-state.hh"
#include "signals.hh"

#define TRACE false

//----------------------------------------------------------------------
// The projection SCC index -- the analysis-side plan, on the INPUT tree
//----------------------------------------------------------------------
//
// The IIR question, for def(Wi) = x + FIR[Wi, 0, c1...] : does x reach Wi,
// directly or through other definitions ? The key fact making it cheap :
// every projection Rj met while walking x is a subterm of def(Wi), so the
// edge Wi -> Rj exists by construction, and therefore
//
//     Rj reaches Wi  <=>  Rj and Wi are in the same SCC
//
// of the PROJECTION graph (nodes = projections, one edge p -> q whenever
// def(p) contains q -- finer than the letrec groups : a multi-definition
// group splits into its real components). So the SCCs, computed once per
// pass by Tarjan, turn every reachability query into a tree walk of x where
// projections are LEAVES answered by an SCC lookup -- no definition is ever
// entered at query time : they were all entered exactly once, at graph
// construction.
//
// The index is read-only and dies with the pass ; it never crosses to the
// output tree (all candidacy questions are asked on the input side).
class ProjSCCIndex {
   private:
    std::unordered_map<Tree, int>  fScc;    // projection -> component id
    std::unordered_map<Tree, Tree> fGroup;  // projection -> its letrec group

   public:
    const std::unordered_map<Tree, int>&  sccMap() const { return fScc; }
    const std::unordered_map<Tree, Tree>& groupMap() const { return fGroup; }

    explicit ProjSCCIndex(Tree root)
    {
        // Discovery : all reachable projections and the edges p -> q.
        // Each definition is walked once, with a PER-WALK seen set : a
        // subtree shared between two definitions must contribute its
        // projections as edges of BOTH (a global set would silently drop
        // the second edge and under-connect the graph).
        digraph<Tree>            g;
        std::vector<Tree>        defQueue;
        std::unordered_set<Tree> known;

        auto walk = [&](Tree t0, Tree from) {
            std::unordered_set<Tree> seen;
            std::vector<Tree>        st{t0};
            while (!st.empty()) {
                Tree t = st.back();
                st.pop_back();
                if (!seen.insert(t).second) {
                    continue;
                }
                int  p;
                Tree rg, var, le;
                if (isProj(t, &p, rg) && isRec(rg, var, le) && le) {
                    // a projection is a LEAF of the walk : its definition
                    // is walked on its own turn, never inline
                    g.add(t);
                    if (from) {
                        g.add(from, t, 0);
                    }
                    if (known.insert(t).second) {
                        fGroup[t] = rg;
                        defQueue.push_back(t);
                    }
                    continue;
                }
                for (int k = 0; k < t->arity(); k++) {
                    st.push_back(t->branch(k));
                }
            }
        };

        walk(root, nullptr);
        for (std::size_t i = 0; i < defQueue.size(); i++) {
            Tree q = defQueue[i];
            int  p;
            Tree rg, var, le;
            isProj(q, &p, rg);
            isRec(rg, var, le);
            if (le && !isNil(le)) {
                walk(nth(le, p), q);
            }
        }

        Tarjan<Tree> tarjan(g);
        int          id = 0;
        for (const auto& comp : tarjan.partition()) {
            for (Tree m : comp) {
                fScc[m] = id;
            }
            id++;
        }
    }

    /// does f reach sig ? Tree walk with projections as SCC-lookup leaves.
    bool reaches(Tree f, Tree sig) const
    {
        auto itSig = fScc.find(sig);
        TLIB_ASSERT(itSig != fScc.end());
        std::unordered_set<Tree> seen;
        std::vector<Tree>        st{f};
        while (!st.empty()) {
            Tree t = st.back();
            st.pop_back();
            if (t == sig) {
                return true;
            }
            if (!seen.insert(t).second) {
                continue;
            }
            int  p;
            Tree rg;
            if (isProj(t, &p, rg)) {
                auto it = fScc.find(t);
                if (it == fScc.end() || it->second == itSig->second) {
                    return true;  // same component (or unknown : conservative)
                }
                continue;  // foreign component : opaque leaf, cannot come back
            }
            Tree var, le;
            if (isRec(t, var, le)) {
                return true;  // a bare rec group in expression position : conservative
            }
            for (int k = 0; k < t->arity(); k++) {
                st.push_back(t->branch(k));
            }
        }
        return false;
    }
};


//----------------------------------------------------------------------
// The reveal : one paired rule under the generic tlib rewrite
//----------------------------------------------------------------------
//
// REQUIRES a normalizeRecGroups-normalized input. On the normalized term
// the letrecs are minimal, which collapses the whole dependency analysis :
//
//   - the hosts are exactly the SINGLE-definition letrecs (a
//     multi-definition group is a true knot : every member depends on a
//     sibling, no member can be an IIR) ;
//   - any OTHER projection met in x belongs to a foreign component BY
//     CONSTRUCTION and cannot come back : "x independent of Wi" reduces
//     to "x does not contain Wi literally" -- a plain tree search with
//     projections as opaque leaves. No SCC index, no dependency machinery.
//
// (ProjSCCIndex above only survives for the SS_SPLIT instruction probe.)

// does f contain the projection self, other projections being opaque leaves ?
static bool containsSelf(Tree f, Tree self)
{
    std::unordered_set<Tree> seen;
    std::vector<Tree>        st{f};
    while (!st.empty()) {
        Tree t = st.back();
        st.pop_back();
        if (t == self) {
            return true;
        }
        if (!seen.insert(t).second) {
            continue;
        }
        int  i;
        Tree g;
        if (isProj(t, &i, g)) {
            continue;  // a foreign component : cannot come back
        }
        for (int k = 0; k < t->arity(); k++) {
            st.push_back(t->branch(k));
        }
    }
    return false;
}

// t is a feedback tap c * self@k (k >= 1) : self delayed by a constant k, times slow
// factors free of self (none : c = 1), possibly negated. Gives k, the factors of c and the
// sign.
static bool feedbackTap(Tree t, Tree self, int& k, std::vector<Tree>& coef, bool& negated)
{
    negated = false;
    Tree u;
    if (isSigNeg(t, u)) {
        negated = true;
        t       = u;
    }
    std::vector<Tree> fs;
    tvec              ps;
    Tree              x, y;
    if (isSigProd(t, ps)) {
        fs = ps;
    } else if (isSigMul(t, x, y)) {
        fs = {x, y};
    } else {
        fs = {t};
    }
    int found = -1;
    for (size_t i = 0; i < fs.size(); i++) {
        Tree d, n;
        if (isSigDelay(fs[i], d, n) && d == self && isSigInt(n, &k) && k >= 1) {
            if (found >= 0) {
                return false;
            }
            found = int(i);
        }
    }
    if (found < 0) {
        return false;
    }
    coef.clear();
    for (size_t i = 0; i < fs.size(); i++) {
        if (int(i) == found) {
            continue;
        }
        if (sigs::isAudioRate(fs[i]) || containsSelf(fs[i], self)) {
            return false;
        }
        coef.push_back(fs[i]);
    }
    return true;
}

// A linear recursion whose feedback lies under slow factors : y = c + k * (x + y@1),
// y = -k * (x + k' * y@1). The definition is read as a sum of signed terms, each one
// carrying the slow factors around it : a term free of y belongs to the input, a tap
// c * y@k to the feedback. Two forms are left as they are, the precision of the program
// asking so : a FIR on y under a factor (a biquad whose coefficients share a factor,
// y = x - k * FIR[y, 0, a, b] : the products k * a, computed in the precision of the
// program, move the poles of a low-frequency filter), and a delay fed by several terms
// (y@1 + g * (x - y@1), an interpolation : as IIR[g * x, 1 - g] it would repeat g, and
// 1 - g loses the precision of a small g). The factors are thereby distributed over the
// sum they multiply : the recursion is then bounded by its gain instead of its iterated
// definition. Any other reading of y (y@0, a product of two readings, a factor that
// changes every sample) leaves the recursion as it is. The images come from the memo of
// the rewrite ; the input and the coefficients are put in normal form.
namespace {
struct LinearTerm {
    std::vector<Tree> slow;  // the factors around the term (original side)
    bool              neg;
    Tree              core;  // the term, or the tap
    int               kind;  // 0 input, 1 tap y@k
    int               k;
};
}  // namespace

// does t read target, crossing into the definitions of the recursions it reads ? seen
// holds the nodes already explored (none of them reaches target), shared by the calls
static bool readsBack(Tree t, Tree target, std::set<Tree>& seen)
{
    std::vector<Tree> st{t};
    while (!st.empty()) {
        Tree u = st.back();
        st.pop_back();
        if (u == target) {
            return true;
        }
        if (!seen.insert(u).second) {
            continue;
        }
        int  i;
        Tree g, var, body;
        if (isProj(u, &i, g) && isRec(g, var, body) && body != nullptr) {
            st.push_back(body);
            continue;
        }
        for (int k = 0; k < u->arity(); k++) {
            st.push_back(u->branch(k));
        }
    }
    return false;
}

// IIR[k * x, c] = k * IIR[x, c] for a constant k, and IIR[-u, c] = -IIR[u, c] : the filter
// is linear in its input. The constant factors of the input go out, read once and applied
// to the output. A factor that may change in time (a control, the block size) stays in : the
// filter sums its past inputs, each one scaled by the value of k at its own instant.
static Tree scaledIIR(const tvec& iir)
{
    Tree in = iir[0];
    Tree u;
    bool neg = false;
    if (isSigNeg(in, u)) {
        neg = true;
        in  = u;
    }
    tvec fs, konst, rest;
    if (isSigProd(in, fs)) {
        for (Tree f : fs) {
            (sigs::sigOrder(f) <= 1 ? konst : rest).push_back(f);
        }
    }
    Tree r;
    if (!konst.empty() && !rest.empty()) {
        tvec v = iir;
        v[0]   = (rest.size() == 1) ? rest[0] : sigProd(rest);
        konst.push_back(sigIIR(v));
        r = sigProd(konst);
    } else {
        tvec v = iir;
        v[0]   = in;
        r      = sigIIR(v);
    }
    return neg ? sigNeg(r) : r;
}

static bool linearRecursion(Tree def, Tree self, const std::function<Tree(Tree)>& image, Tree& result)
{
    std::vector<LinearTerm>                                     terms;
    std::function<bool(Tree, const std::vector<Tree>&, bool)> expand = [&](Tree t, const std::vector<Tree>& slow,
                                                                            bool neg) -> bool {
        Tree u, d, n;
        int  k;
        tvec v;
        if (!containsSelf(t, self)) {
            terms.push_back({slow, neg, t, 0, 0});
            return true;
        }
        if (isSigNeg(t, u)) {
            return expand(u, slow, !neg);
        }
        if (isSigSum(t, v)) {
            for (Tree b : v) {
                if (!expand(b, slow, neg)) return false;
            }
            return true;
        }
        if (isSigDelay(t, d, n) && d == self && isSigInt(n, &k) && k >= 1) {
            terms.push_back({slow, neg, t, 1, k});
            return true;
        }
        if (isSigFIR(t, v) && v[0] == self) {
            return false;  // a FIR on y under a factor : left as it is (see above)
        }
        std::vector<Tree> fs;
        Tree              x, y;
        if (isSigProd(t, v)) {
            fs = v;
        } else if (isSigMul(t, x, y)) {
            fs = {x, y};
        } else {
            return false;
        }
        Tree              inner = nullptr;
        std::vector<Tree> s2    = slow;
        for (Tree f : fs) {
            if (containsSelf(f, self)) {
                if (inner != nullptr) return false;  // two readings of y : not linear
                inner = f;
            } else if (sigs::isAudioRate(f)) {
                return false;  // a coefficient that changes every sample
            } else {
                s2.push_back(f);
            }
        }
        return inner != nullptr && expand(inner, s2, neg);
    };
    if (!expand(def, {}, false)) {
        return false;
    }
    // an input that reads y back through another recursion : the filter is a part of a
    // larger loop, whose analysis would bound it again at every one of its own steps
    std::set<Tree> seen;  // the nodes that do not reach y, shared by the terms
    for (const LinearTerm& t : terms) {
        if (t.kind == 0 && !t.core->isRecFree() && readsBack(t.core, self, seen)) {
            return false;
        }
    }
    // normal form of a piece free of recursion ; a piece holding a recursion is kept as it
    // is : rewritten again, its groups would be copies, computed twice
    auto normal = [](Tree t) { return t->isRecFree() ? simplify(t) : t; };
    // a signed product of images : the slow factors (in normal form) then the given factor
    // (nullptr : none)
    auto product = [&](const LinearTerm& t, Tree last) -> Tree {
        Tree k = nullptr;
        for (Tree f : t.slow) {
            Tree g = image(f);
            if (g == nullptr) return nullptr;
            k = (k == nullptr) ? g : sigMul(k, g);
        }
        Tree p;
        if (last == nullptr) {
            p = (k == nullptr) ? sigInt(1) : normal(k);
        } else if (k == nullptr) {
            p = last;
        } else if (last->isRecFree()) {
            p = normal(sigMul(k, last));
        } else {
            Tree nk = normal(k);
            p       = sigProd({nk, last});
        }
        return t.neg ? sigNeg(p) : p;
    };
    std::map<int, Tree> coefs;  // delay -> coefficient
    tvec                inputs;
    for (const LinearTerm& t : terms) {
        if (t.kind == 0) {
            Tree c = image(t.core);
            Tree p = (c == nullptr) ? nullptr : product(t, c);
            if (p == nullptr) return false;
            inputs.push_back(p);
        } else if (t.kind == 1) {
            if (coefs.count(t.k)) return false;  // a delay fed by several terms (see above)
            Tree p = product(t, nullptr);
            if (p == nullptr) return false;
            coefs[t.k] = p;
        }
    }
    if (inputs.empty() || coefs.empty()) {
        return false;
    }
    // the order, after the decimation by the step of the non null coefficients (as above)
    size_t step = 0;
    for (const auto& c : coefs) step = std::gcd(step, size_t(c.first));
    const int order = coefs.rbegin()->first;
    if (step == 0 || size_t(order) / step > 128) {
        return false;
    }
    Tree input = (inputs.size() == 1) ? inputs[0] : sigSum(inputs);
    tvec iir{normal(input)};
    for (int k = 1; k <= order; k++) {
        auto it = coefs.find(k);
        iir.push_back(it == coefs.end() ? tree(0) : simplify(it->second));
    }
    for (size_t j = 1; j < iir.size(); j++) {
        if (sigs::isAudioRate(iir[j])) return false;
    }
    result = scaledIIR(iir);
    return true;
}

Tree revealIIR(Tree L1)
{
    std::unordered_map<Tree, Tree> memo;

    auto pre     = [](Tree) -> std::optional<Tree> { return std::nullopt; };
    auto defRule = [](Tree, Tree rebuilt) -> Tree { return rebuilt; };

    // The candidacy analysis runs entirely on the ORIGINAL side (closed
    // input, valid pointer equality, SCC index) ; the pieces of a
    // recognized IIR cross to the output through the traversal MEMO --
    // when the rule fires on an external projection, the group's body is
    // already rebuilt, so the images of x and of the coefficients are
    // present : read, never re-descend.
    auto rule = [&](Tree orig, Tree rebuilt) -> Tree {
        // a projection read at delay 0 (x@0, the normal form's writing) that became an
        // IIR : the IIR itself
        // (or the product by its slow factors, see scaledIIR : the normal form keeps x@0 for
        // a recursive projection only, any other x@0 comes from this rewrite)
        int pz;
        if (Tree x, d, g; isSigDelay(rebuilt, x, d) && isZero(d) && !isProj(x, &pz, g)) {
            return x;
        }
        int  p;
        Tree rgroup, var, le;
        if (!(isProj(orig, &p, rgroup) && isRec(rgroup, var, le) && le && !isNil(le))) {
            return rebuilt;
        }

        // Internal or external occurrence ? While the group is being
        // rebuilt the memo maps it to a still-open reference : its
        // self-references stay plain projections, only external
        // occurrences are IIR candidates.
        if (auto it = memo.find(rgroup); it != memo.end()) {
            Tree v2, b2;
            if (isRec(it->second, v2, b2) && (b2 == nullptr)) {
                return rebuilt;
            }
        }

        if (len(le) != 1) {
            return rebuilt;  // a true knot : never an IIR host (see header)
        }
        Tree def = nth(le, p);
        auto image = [&](Tree t) -> Tree {
            auto it = memo.find(t);
            return (it != memo.end()) ? it->second : nullptr;
        };
        // the feedback under slow factors, when the direct reading below does not apply
        auto fallback = [&]() -> Tree {
            Tree r;
            return linearRecursion(def, orig, image, r) ? r : rebuilt;
        };
        if (!isSigSum(def)) {
            return fallback();
        }

        // def(Wi) = x + FIR[Wi, 0, c1, c2, ...], or x + c * Wi@k (a single feedback tap,
        // which the normal form does not write as a FIR) : exactly one feedback term
        // whose source IS this projection (pointer equality, hash-consing)
        std::vector<Tree> R, L;
        for (Tree f : def->branches()) {
            int               k;
            std::vector<Tree> cf;
            bool              neg;
            if ((isSigFIR(f) && (f->branch(0) == orig)) || feedbackTap(f, orig, k, cf, neg)) {
                R.push_back(f);
            }
        }
        if (R.size() != 1) {
            return fallback();
        }
        for (Tree f : def->branches()) {
            if (f == R[0]) {
                continue;
            }
            if (containsSelf(f, orig)) {
                return fallback();  // the feedback is not solely through the FIR
            }
            L.push_back(f);
        }
        if (L.empty()) {
            return rebuilt;
        }

        // the coefficients c1, c2, ... (rebuilt side) : the FIR's beyond its null c0, or
        // the single tap's, zeros before its delay
        tvec coefs;
        if (tvec coef1; isSigFIR(R[0], coef1)) {
            // The COEFFICIENTS must be slow rate : an audio-rate coefficient
            // (state or input dependent) makes a nonlinear or time-varying
            // kernel, not an IIR. O(1) by the synthesized bit. This is a
            // DIFFERENT requirement from x's independence : well-foundedness
            // there, the LTI doctrine here.
            if (coef1.size() < 3 || !isZero(coef1[1])) {
                return rebuilt;  // a feedback at delay 0 : not a recursion of the past
            }
            for (unsigned int i = 2; i < coef1.size(); i++) {
                if (sigs::isAudioRate(coef1[i])) {
                    return rebuilt;
                }
                Tree c = image(coef1[i]);
                if (!c) {
                    return rebuilt;
                }
                coefs.push_back(c);
            }
        } else {
            int               k;
            std::vector<Tree> cf;
            bool              neg;
            feedbackTap(R[0], orig, k, cf, neg);
            tvec ci;
            for (Tree f : cf) {
                Tree c = image(f);
                if (!c) {
                    return rebuilt;
                }
                ci.push_back(c);
            }
            Tree c = ci.empty() ? tree(1) : (ci.size() == 1 ? ci[0] : sigProd(ci));
            if (neg) {
                c = sigNeg(c);
            }
            for (int d = 1; d < k; d++) {
                coefs.push_back(tree(0));
            }
            coefs.push_back(c);
        }

        // An IIR of a high order stays a recursion : its bound (companion matrices of the
        // order, after the decimation by the step of its non null coefficients) would
        // cost more than it brings. A comb x + g y@N is of order 1 after decimation.
        {
            size_t step = 0;
            for (size_t k = 0; k < coefs.size(); k++) {
                if (!isZero(coefs[k])) {
                    step = std::gcd(step, k + 1);
                }
            }
            if (step == 0 || coefs.size() / step > 128) {
                return rebuilt;
            }
        }

        // Assemble IIR[x, c1, c2, ...] from the memoized images
        tvec iir;
        if (L.size() == 1) {
            Tree in = image(L[0]);
            if (!in) {
                return rebuilt;
            }
            iir.push_back(in);
        } else {
            tvec ins;
            for (Tree f : L) {
                Tree in = image(f);
                if (!in) {
                    return rebuilt;
                }
                ins.push_back(in);
            }
            iir.push_back(sigSum(ins));
        }
        // an IIR whose denominator coefficients are audio-rate is not a
        // polynomial over slow values : every product the kernel algebra
        // would build with them runs per sample, and the lift only
        // de-factors what the canonical recursion shared (dattorro's
        // smoothed allpass gains). Refuse the lift.
        for (Tree c : coefs) {
            if (sigs::isAudioRate(c)) {
                return rebuilt;
            }
            iir.push_back(c);
        }
        return scaledIIR(iir);
    };

    return treeRewritePairedMemo(L1, pre, rule, memo, defRule);
}

//----------------------------------------------------------------------
// The infinite recursive mix
//----------------------------------------------------------------------
//
// A single-definition recursion y = mix(c, x, y@1) or mix(c, y@1, x), x and c free of y,
// or an IIR of order 1 whose input carries the factor 1 - c of its coefficient c, is the
// node IRM(x; p) : y = mix(p, x, y@1), p the pole, the weight of y@1 (c, or 1 - c
// for the second writing). The two writings of a smoother reach one node, and its
// interval is an invariant of the mix instead of the fixpoint of a recursion. The
// external readings of the projection become readings of the node, as for an IIR ; x
// and c are read through the memo of the rewrite. An x or a c that reads y back through
// another recursion leaves y as it is : the smoother is a part of a larger loop.

// t is y@1, y the projection self
static bool isSelfDelay1(Tree t, Tree self)
{
    Tree x, d;
    int  k;
    return isSigDelay(t, x, d) && x == self && isSigInt(d, &k) && k == 1;
}

// 1 - c as the normal form writes a complement, Sum(1, neg(c)) : the code generators read
// the weight c of the input back from it, exact (1 - (1 - c) would lose the precision of a
// small c). The complement of a complement Sum(1, neg(t)) is t ; of a number, a number.
static Tree complementWeight(Tree c)
{
    Tree x;
    tvec ws;
    if (isSigSum(c, ws) && ws.size() == 2 && isOne(ws[0]) && isSigNeg(ws[1], x)) {
        return x;
    }
    if (isNum(c)) {
        return simplify(sigSub(sigReal(1.0), c));
    }
    return sigSum({sigReal(1.0), sigNeg(c)});
}

// a and b are complements : one is Sum(1, neg(other)), the normal form's 1 - other
static bool complements(Tree a, Tree b)
{
    tvec ws;
    Tree x;
    auto isOneMinus = [&](Tree s, Tree t) {
        return isSigSum(s, ws) && ws.size() == 2 && isOne(ws[0]) && isSigNeg(ws[1], x) && x == t;
    };
    return isOneMinus(a, b) || isOneMinus(b, a);
}

// IIR(x; c) of order 1 whose input is (1 - c) * A : IRM(A; c), y = (1 - c) A + c y@1. The
// IIR reveal reads the smoother whose target is 1, or whose input carries the weight, as a
// linear recursion ; as a mix it is bounded by its target instead of its gain.
static Tree iirAsIRM(Tree t)
{
    tvec v;
    if (!isSigIIR(t, v) || v.size() != 2) {
        return nullptr;
    }
    Tree x = v[0], c = v[1];
    if (complements(x, c)) {
        return sigIRM(sigReal(1.0), c);
    }
    tvec fs;
    if (!isSigProd(x, fs)) {
        return nullptr;
    }
    for (size_t k = 0; k < fs.size(); k++) {
        if (!complements(fs[k], c)) continue;
        tvec rest;
        for (size_t j = 0; j < fs.size(); j++) {
            if (j != k) rest.push_back(fs[j]);
        }
        Tree a = (rest.size() == 1) ? rest[0] : sigProd(rest);
        return sigIRM(a, c);
    }
    return nullptr;
}

Tree revealIRM(Tree L1)
{
    std::unordered_map<Tree, Tree> memo;

    auto pre     = [](Tree) -> std::optional<Tree> { return std::nullopt; };
    auto defRule = [](Tree, Tree rebuilt) -> Tree { return rebuilt; };

    auto rule = [&](Tree orig, Tree rebuilt) -> Tree {
        // a projection read at delay 0 that became an IRM : the IRM itself
        int pz;
        if (Tree x, d, g; isSigDelay(rebuilt, x, d) && isZero(d) && !isProj(x, &pz, g)) {
            return x;
        }
        if (Tree m = iirAsIRM(rebuilt)) {
            return m;
        }
        int  p;
        Tree rgroup, var, le;
        if (!(isProj(orig, &p, rgroup) && isRec(rgroup, var, le) && le && !isNil(le))) {
            return rebuilt;
        }
        // an internal occurrence (the group is being rebuilt) stays a projection
        if (auto it = memo.find(rgroup); it != memo.end()) {
            Tree v2, b2;
            if (isRec(it->second, v2, b2) && (b2 == nullptr)) {
                return rebuilt;
            }
        }
        if (len(le) != 1) {
            return rebuilt;
        }
        Tree def = nth(le, p);
        Tree c, a, b;
        if (!isSigMix(def, c, a, b)) {
            return rebuilt;
        }
        Tree x;
        bool swapped;
        if (isSelfDelay1(b, orig)) {
            x = a, swapped = false;
        } else if (isSelfDelay1(a, orig)) {
            x = b, swapped = true;
        } else {
            return rebuilt;
        }
        if (containsSelf(x, orig) || containsSelf(c, orig)) {
            return rebuilt;
        }
        std::set<Tree> seen;
        for (Tree t : {x, c}) {
            if (!t->isRecFree() && readsBack(t, orig, seen)) {
                return rebuilt;
            }
        }
        auto image = [&](Tree t) -> Tree {
            auto it = memo.find(t);
            return (it != memo.end()) ? it->second : nullptr;
        };
        Tree ix = image(x), ic = image(c);
        if (ix == nullptr || ic == nullptr) {
            return rebuilt;
        }
        return sigIRM(ix, swapped ? complementWeight(ic) : ic);
    };

    return treeRewritePairedMemo(L1, pre, rule, memo, defRule);
}

//----------------------------------------------------------------------
// The break-point function
//----------------------------------------------------------------------
//
// A chain of select2 whose conditions all compare the same x to constants, x < c (or
// c > x), is the selection of a break-point function (ba.bpf) : the node
// Bpf(x; t1, ..., tn; r0, ..., rn), x read once, each region r the leaf the chain gives
// for x in its range. A chain met below (rewritten first) is absorbed with its
// thresholds. Two regions in a row with the same expression are one. A single
// comparison stays a select2.

// t compares x to a constant : x < c or c > x ; gives x and c
static bool lessThanConstant(Tree t, Tree& x, double& c)
{
    int  op;
    Tree a, b;
    if (!isSigBinOp(t, &op, a, b)) return false;
    auto num = [](Tree u, double& v) {
        int i;
        return isSigReal(u, &v) || (isSigInt(u, &i) && ((v = i), true));
    };
    if (op == kLT && num(b, c)) {
        x = a;
        return true;
    }
    if (op == kGT && num(a, c)) {
        x = b;
        return true;
    }
    return false;
}

// the thresholds (value -> tree) of the chain rooted at t on x
static void bpfThresholds(Tree t, Tree x, std::map<double, Tree>& th)
{
    Tree sel, s0, s1, y;
    double c;
    tvec   bt, br;
    if (isSigSelect2(t, sel, s0, s1) && lessThanConstant(sel, y, c) && y == x) {
        int  op;
        Tree a, b;
        isSigBinOp(sel, &op, a, b);
        th.emplace(c, op == kLT ? b : a);
        bpfThresholds(s0, x, th);
        bpfThresholds(s1, x, th);
    } else if (isSigBpf(t, y, bt, br) && y == x) {
        for (Tree ti : bt) {
            double v;
            int    i;
            if (isSigReal(ti, &v) || (isSigInt(ti, &i) && ((v = i), true))) th.emplace(v, ti);
        }
        for (Tree r : br) bpfThresholds(r, x, th);
    }
}

// the leaf of the chain rooted at t for x in [lo, hi[ (lo and hi consecutive thresholds)
static Tree bpfRegion(Tree t, Tree x, double lo, double hi)
{
    Tree   sel, s0, s1, y;
    double c;
    tvec   bt, br;
    if (isSigSelect2(t, sel, s0, s1) && lessThanConstant(sel, y, c) && y == x) {
        // select2(x < c, s0, s1) : s1 when x < c, the whole region lying below c or above
        return bpfRegion(hi <= c ? s1 : s0, x, lo, hi);
    }
    if (isSigBpf(t, y, bt, br) && y == x) {
        size_t i = 0;
        for (; i < bt.size(); i++) {
            double v;
            int    k;
            if (!(isSigReal(bt[i], &v) || (isSigInt(bt[i], &k) && ((v = k), true)))) return t;
            if (hi <= v) break;
        }
        return bpfRegion(br[i], x, lo, hi);
    }
    return t;
}

static Tree bpfOf(Tree t)
{
    Tree   sel, s0, s1, x;
    double c;
    if (!isSigSelect2(t, sel, s0, s1) || !lessThanConstant(sel, x, c)) {
        return nullptr;
    }
    std::map<double, Tree> th;
    bpfThresholds(t, x, th);
    if (th.size() < 2) {
        return nullptr;
    }
    std::vector<double> v;
    tvec                tt;
    for (const auto& p : th) {
        v.push_back(p.first);
        tt.push_back(p.second);
    }
    tvec regions;
    for (size_t i = 0; i <= v.size(); i++) {
        const double lo = (i == 0) ? -HUGE_VAL : v[i - 1];
        const double hi = (i == v.size()) ? HUGE_VAL : v[i];
        regions.push_back(bpfRegion(t, x, lo, hi));
    }
    // two regions in a row with the same expression are one
    tvec t2{}, r2{regions[0]};
    for (size_t i = 0; i < tt.size(); i++) {
        if (regions[i + 1] == r2.back()) continue;
        t2.push_back(tt[i]);
        r2.push_back(regions[i + 1]);
    }
    if (t2.size() < 2) {
        return nullptr;
    }
    return sigBpf(x, t2, r2);
}

Tree revealBpf(Tree L1)
{
    std::unordered_map<Tree, Tree> memo;
    auto pre     = [](Tree) -> std::optional<Tree> { return std::nullopt; };
    auto defRule = [](Tree, Tree rebuilt) -> Tree { return rebuilt; };
    auto rule    = [&](Tree, Tree rebuilt) -> Tree {
        Tree b = bpfOf(rebuilt);
        return b ? b : rebuilt;
    };
    return treeRewritePairedMemo(L1, pre, rule, memo, defRule);
}
