#include "revealIIR.hh"

#include <iostream>
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
// Instruction probe : what would splitting the letrecs along the
// projection SCCs buy ? (FAUST_SS_SPLIT, measured on the tree the
// reveals see -- i.e. AFTER simplification, which may already have
// disentangled definitions that merely seemed mutually recursive.)
//----------------------------------------------------------------------

void projSCCReport(Tree L)
{
    ProjSCCIndex index(L);
    const auto&  scc   = index.sccMap();
    const auto&  group = index.groupMap();

    // current grouping : live projections per letrec group
    std::unordered_map<Tree, std::vector<Tree>> byGroup;
    for (const auto& [p, g] : group) {
        byGroup[g].push_back(p);
    }
    // ideal grouping : projections per component
    std::unordered_map<int, std::vector<Tree>> byScc;
    std::unordered_map<int, std::unordered_set<Tree>> sccGroups;
    for (const auto& [p, id] : scc) {
        byScc[id].push_back(p);
        sccGroups[id].insert(group.at(p));
    }

    int g1 = 0, gm = 0, splittable = 0;
    for (const auto& [g, projs] : byGroup) {
        if (projs.size() == 1) {
            g1++;
            continue;
        }
        gm++;
        std::unordered_set<int> parts;
        for (Tree p : projs) {
            parts.insert(scc.at(p));
        }
        if (parts.size() > 1) {
            splittable++;
        }
    }

    int singNonRec = 0, singSelfRec = 0, multi = 0, spanning = 0, maxScc = 0;
    for (const auto& [id, members] : byScc) {
        maxScc = std::max(maxScc, int(members.size()));
        if (sccGroups.at(id).size() > 1) {
            spanning++;  // a knot across several current letrecs : a MERGE, not a split
        }
        if (members.size() > 1) {
            multi++;
            continue;
        }
        // singleton : self-recursive iff its definition reaches it
        Tree p0 = members[0];
        int  p;
        Tree rg, var, le;
        isProj(p0, &p, rg);
        isRec(rg, var, le);
        Tree def = (le && !isNil(le)) ? nth(le, p) : nullptr;
        if (def && index.reaches(def, p0)) {
            singSelfRec++;
        } else {
            singNonRec++;
        }
    }

    std::cerr << "SS_SPLIT groups=" << byGroup.size() << " projs=" << group.size()
              << " g1=" << g1 << " gmulti=" << gm << " splittable=" << splittable
              << " sccs=" << byScc.size() << " sccSingleSelfrec=" << singSelfRec
              << " sccSingleNonrec=" << singNonRec << " sccMulti=" << multi
              << " sccSpanningGroups=" << spanning << " maxScc=" << maxScc << std::endl;
}

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

    auto pre     = [](Tree) -> std::optional<Tree> { return std::nullopt; };
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
        faustassert(isSigFIR(R[0], coef1));
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
        coef2.push_back(gGlobal->nil);
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
        return sigIIR(coef2);
    };

    return treeRewritePairedMemo(L1, pre, rule, memo, defRule);
}
