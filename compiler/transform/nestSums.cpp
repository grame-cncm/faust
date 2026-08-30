#include "nestSums.hh"

#include <algorithm>
#include <map>
#include <set>
#include <vector>

#include "global.hh"
#include "rewrite.hh"
#include "signals.hh"
#include "sigs-state.hh"

// Occurrence-ordered re-nesting of the revealed sums.
//
// revealSum's flattening destroys the prefix sharing of the canonical
// binary nesting : two flat sums that differ by one term share nothing,
// where their nested spellings shared every partial (the staircase of
// Sum(13..9) nodes of freeverb and crazyGuiro, each re-adding almost
// the same terms). The repair orders the terms of every sum by
// DESCENDING occurrence -- the number of sums that contain the term --
// and folds them into left-nested BINARY sums : sums that agree on
// their most frequent terms rebuild the same partial nodes, and
// maximal sharing does the rest. Binary Sum nodes (not sigAdd chains)
// keep the unsigned spelling of integer sums, whose modular
// associativity makes the re-nesting exact ; for floats it is a legal
// reassociation, judged by the onset gate like every other. Ties break
// on the canonical tree order : the nesting is deterministic.

Tree nestSums(Tree L)
{
    // census : in how many distinct sums does each term appear
    std::map<Tree, int, treeorder> occ;
    {
        std::set<Tree>    seen;
        std::vector<Tree> work{L};
        while (!work.empty()) {
            Tree t = work.back();
            work.pop_back();
            if (!seen.insert(t).second) {
                continue;
            }
            Tree var, body;
            if (isRec(t, var, body)) {
                if (body) {
                    work.push_back(body);
                }
                continue;
            }
            if (tvec subs; isSigSum(t, subs)) {
                std::set<Tree, treeorder> uniq(subs.begin(), subs.end());
                for (Tree s : uniq) {
                    occ[s]++;
                }
            }
            for (int k = 0; k < t->arity(); k++) {
                work.push_back(t->branch(k));
            }
        }
    }
    auto rule = [&occ](Tree sig) -> Tree {
        tvec subs;
        if (!isSigSum(sig, subs) || subs.size() < 3) {
            return sig;
        }
        tvec sorted = subs;
        std::stable_sort(sorted.begin(), sorted.end(), [&occ](Tree a, Tree b) {
            auto ita = occ.find(a);
            auto itb = occ.find(b);
            int  oa  = (ita != occ.end()) ? ita->second : 0;
            int  ob  = (itb != occ.end()) ? itb->second : 0;
            if (oa != ob) {
                return oa > ob;  // most shared terms deepest
            }
            return treeorder()(a, b);
        });
        Tree acc = sigSum(tvec{sorted[0], sorted[1]});
        for (size_t i = 2; i < sorted.size(); i++) {
            acc = sigSum(tvec{acc, sorted[i]});
        }
        return acc;
    };
    return treeRewrite(L, rule);
}
