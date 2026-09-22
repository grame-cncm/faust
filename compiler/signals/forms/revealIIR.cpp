#include "revealIIR.hh"
#include "sigGenCut.hh"

#include <cstdlib>
#include <iostream>
#include <map>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "DirectedGraph.hh"
#include "DirectedGraphAlgorythm.hh"
#include "sigs-state.hh"
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

Tree revealIIR(Tree L1)
{
    std::unordered_map<Tree, Tree> memo;

    auto pre     = sigGenCut;  // NEVER TRANSFORM A GENERATOR (sigGenCut.hh)
    auto defRule = [](Tree, Tree rebuilt) -> Tree { return rebuilt; };

    // The candidacy analysis runs entirely on the ORIGINAL side (closed
    // input, valid pointer equality, SCC index) ; the pieces of a
    // recognized IIR cross to the output through the traversal MEMO --
    // when the rule fires on an external projection, the group's body is
    // already rebuilt, so the images of x and of the coefficients are
    // present : read, never re-descend.
    auto rule = [&](Tree orig, Tree rebuilt) -> Tree {
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
        if (!isSigSum(def)) {
            return rebuilt;
        }

        // def(Wi) = x + FIR[Wi, 0, c1, c2, ...] : exactly one FIR whose
        // source IS this projection (pointer equality, hash-consing)
        std::vector<Tree> R, L;
        for (Tree f : def->branches()) {
            if (isSigFIR(f) && (f->branch(0) == orig)) {
                R.push_back(f);
            }
        }
        if (R.size() != 1) {
            return rebuilt;
        }
        for (Tree f : def->branches()) {
            if (isSigFIR(f) && (f->branch(0) == orig)) {
                continue;
            }
            if (containsSelf(f, orig)) {
                return rebuilt;  // the feedback is not solely through the FIR
            }
            L.push_back(f);
        }
        if (L.empty()) {
            return rebuilt;
        }

        tvec coef1;
        TLIB_ASSERT(isSigFIR(R[0], coef1));
        // The COEFFICIENTS must be slow rate : an audio-rate coefficient
        // (state or input dependent) makes a nonlinear or time-varying
        // kernel, not an IIR. O(1) by the synthesized bit. This is a
        // DIFFERENT requirement from x's independence : well-foundedness
        // there, the LTI doctrine here.
        for (unsigned int i = 1; i < coef1.size(); i++) {
            if (sigs::isAudioRate(coef1[i])) {
                return rebuilt;
            }
        }

        // Assemble IIR[nil, x, 0, c1, c2, ...] from the memoized images
        auto image = [&](Tree t) -> Tree {
            auto it = memo.find(t);
            return (it != memo.end()) ? it->second : nullptr;
        };
        tvec coef2;
        coef2.push_back(nil());
        if (L.size() == 1) {
            Tree in = image(L[0]);
            if (!in) {
                return rebuilt;
            }
            coef2.push_back(in);
        } else {
            tvec ins;
            for (Tree f : L) {
                Tree in = image(f);
                if (!in) {
                    return rebuilt;
                }
                ins.push_back(in);
            }
            coef2.push_back(sigSum(ins));
        }
        for (unsigned int i = 1; i < coef1.size(); i++) {
            Tree c = image(coef1[i]);
            if (!c) {
                return rebuilt;
            }
            coef2.push_back(c);
        }
        // an IIR whose denominator coefficients are audio-rate is not a
        // polynomial over slow values : every product the kernel algebra
        // would build with them runs per sample, and the lift only
        // de-factors what the canonical recursion shared (dattorro's
        // smoothed allpass gains). Refuse the lift.
        for (size_t i = 3; i < coef2.size(); i++) {
            if (sigs::isAudioRate(coef2[i])) {
                return rebuilt;
            }
        }
        return sigIIR(coef2);
    };

    return treeRewritePairedMemo(L1, pre, rule, memo, defRule);
}

//----------------------------------------------------------------------
// The common numerator : FIR_K(IIR_D(x)) = IIR_D(FIR_K(x))
//----------------------------------------------------------------------
//
// Two linear filters with CONSTANT coefficients commute -- their transfer
// functions do, N(z) * 1/D(z) = 1/D(z) * N(z) -- and the states of a Faust
// filter start at zero : both orders give the same signal from the first
// sample. A bank of IIRs on the same input x whose outputs go through the
// same kernel K (the modal models : englishBell's 50 modes are
// g_j * FIR[IIR[, x, 0, c1_j, c2_j], 1, 0, -1]) is rewritten so that every
// branch reads FIR_K(x) : one hash-consed node, the kernel computed once for
// the whole bank instead of once per filter.
//
// Conditions, all decided on the ORIGINAL tree :
//   - constant coefficients (numbers or init-time values, sigOrder <= 1),
//     for K and for D : block-rate coefficients do not commute across a
//     block edge, where the two orders would differ ;
//   - the IIR is read by that FIR only : otherwise the recursion would be
//     computed twice, once on x for its other readers, once on FIR_K(x) ;
//   - a group (x, K) of at least two such filters : alone, the moved kernel
//     reads x's history (a delay line may be born) and shares nothing.
// The gains stay outside : they multiply the branch after the filter in
// both forms, so a varying gain (a strike position) keeps the rewrite exact.
// Hoisting the kernel out of the SUM instead, K applied once to
// sum_j g_j * IIR_j(x), would be exact for constant gains only : refused.
Tree hoistCommonNumerators(Tree L1)
{
    const bool trace = getenv("FAUST_FIR_HOIST_TRACE") != nullptr;

    auto constFrom = [](const tvec& V, size_t from) -> bool {
        for (size_t i = from; i < V.size(); i++) {
            if (sigs::sigOrder(V[i]) > 1) {
                return false;
            }
        }
        return true;
    };

    // ---- analysis : readers of every IIR, and the candidate kernels -----
    std::unordered_map<Tree, int> iirReaders;  // IIR node -> number of distinct parent nodes
    std::vector<Tree>             candidates;  // FIR[IIR[...], ...] nodes, discovery order
    {
        std::unordered_set<Tree> seen;
        std::vector<Tree>        st{L1};
        while (!st.empty()) {
            Tree t = st.back();
            st.pop_back();
            if (!seen.insert(t).second) {
                continue;
            }
            Tree var, body;
            if (isRec(t, var, body) && body) {
                st.push_back(body);  // the definitions are reached through the rec's body
                continue;
            }
            std::unordered_set<Tree> kids;
            for (int k = 0; k < t->arity(); k++) {
                Tree b = t->branch(k);
                if (kids.insert(b).second && isSigIIR(b)) {
                    iirReaders[b]++;
                }
                st.push_back(b);
            }
            tvec K;
            if (isSigFIR(t, K) && K.size() >= 3 && isSigIIR(K[0])) {
                candidates.push_back(t);
            }
        }
    }

    // ---- groups (x, K) ----------------------------------------------------
    std::map<tvec, std::vector<Tree>> groups;  // key : {x, k0, k1, ...} (hash-consed pointers)
    std::vector<tvec>                 order;   // keys in discovery order (the trace)
    int                               refusedCoefs = 0, refusedShared = 0;
    for (Tree f : candidates) {
        tvec K, D;
        isSigFIR(f, K);
        isSigIIR(K[0], D);
        if (D.size() < 4 || !constFrom(K, 1) || !constFrom(D, 2)) {
            refusedCoefs++;
            continue;
        }
        if (iirReaders[K[0]] != 1) {
            refusedShared++;
            continue;
        }
        tvec key{D[1]};
        key.insert(key.end(), K.begin() + 1, K.end());
        auto& g = groups[key];
        if (g.empty()) {
            order.push_back(key);
        }
        g.push_back(f);
    }
    std::unordered_set<Tree> targets;
    int                      hoisted = 0, single = 0;
    for (const tvec& key : order) {
        const auto& g = groups[key];
        if (g.size() >= 2) {
            targets.insert(g.begin(), g.end());
            hoisted += (int)g.size();
        } else {
            single++;
        }
        if (trace) {
            std::cerr << "fir-hoist : group of " << g.size() << " filter(s), kernel of " << (key.size() - 1)
                      << " coefficients, " << (g.size() >= 2 ? "hoisted" : "left (alone)") << std::endl;
        }
    }
    if (trace) {
        std::cerr << "fir-hoist summary : FIR-over-IIR " << candidates.size() << ", refused (coefficients not constant) "
                  << refusedCoefs << ", refused (IIR read elsewhere) " << refusedShared << ", groups " << order.size()
                  << ", filters hoisted " << hoisted << ", alone " << single << std::endl;
    }
    if (targets.empty()) {
        return L1;
    }

    // ---- rewrite : built from the rebuilt pieces, decided on the original --
    std::unordered_map<Tree, Tree> memo;
    auto pre     = sigGenCut;  // NEVER TRANSFORM A GENERATOR (sigGenCut.hh)
    auto defRule = [](Tree, Tree rebuilt) -> Tree { return rebuilt; };
    auto rule    = [&](Tree orig, Tree rebuilt) -> Tree {
        if (targets.find(orig) == targets.end()) {
            return rebuilt;
        }
        tvec K, D;
        if (!isSigFIR(rebuilt, K) || K.empty() || !isSigIIR(K[0], D) || D.size() < 4) {
            return rebuilt;
        }
        tvec F = K;
        F[0]   = D[1];  // the kernel now reads the bank's input
        tvec D2 = D;
        D2[1]   = sigFIR(F);  // hash-consed : the same node for the whole group
        return sigIIR(D2);
    };
    return treeRewritePairedMemo(L1, pre, rule, memo, defRule);
}
