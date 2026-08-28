#include "revealMatrix.hh"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <set>

#include "signals.hh"
#include "global.hh"
#include "sigs-state.hh"

// a factor that evaluates at control rate or slower (the kernel lesson :
// sigOrder alone is pessimistic on slow-indexed table reads)
static bool isSlowCoef(Tree t)
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

// a matrix-row candidate : every non-zero term is mul(slow c, x). Fills
// the (operand -> coefficient) map ; refuses duplicate operands (a row
// reads each column once).
static bool rowShape(const tvec& terms, std::map<Tree, Tree>& cols)
{
    for (Tree t : terms) {
        if (isZero(t)) {
            continue;
        }
        Tree a, b, c, x;
        if (!isSigMul(t, a, b)) {
            return false;
        }
        if (isSlowCoef(a) && !isSlowCoef(b)) {
            c = a;
            x = b;
        } else if (isSlowCoef(b) && !isSlowCoef(a)) {
            c = b;
            x = a;
        } else {
            return false;  // two slow (a constant fold) or two audio sides
        }
        if (!cols.insert({x, c}).second) {
            return false;  // duplicate column
        }
    }
    return cols.size() >= 2;
}

MatrixPlans revealMatrix(Tree L)
{
    MatrixPlans plans;
    // ---- census of row candidates ------------------------------------
    std::vector<std::pair<Tree, std::map<Tree, Tree>>> cand;  // (sum, cols)
    {
        std::set<Tree>    seen;
        std::vector<Tree> work;
        for (Tree l = L; isList(l); l = tl(l)) {
            work.push_back(hd(l));
        }
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
            if (tvec terms; isSigSum(t, terms) && terms.size() >= 4) {
                std::map<Tree, Tree> cols;
                if (rowShape(terms, cols)) {
                    cand.push_back({t, cols});
                }
            }
            for (int k = 0; k < t->arity(); k++) {
                work.push_back(t->branch(k));
            }
        }
    }
    // ---- families : group rows by OVERLAPPING operand sets. Greedy :
    // seed with a row, absorb every row sharing at least half of its
    // columns with the family's current tuple union, iterate. The final
    // acceptance re-checks the spec's budgets on the union.
    std::vector<char> used(cand.size(), 0);
    for (size_t i = 0; i < cand.size(); i++) {
        if (used[i]) {
            continue;
        }
        std::vector<size_t> members{i};
        std::set<Tree>      tuple;
        for (auto& [x, c] : cand[i].second) {
            tuple.insert(x);
        }
        bool grew = true;
        while (grew) {
            grew = false;
            for (size_t j = 0; j < cand.size(); j++) {
                if (used[j] || j == i ||
                    std::find(members.begin(), members.end(), j) != members.end()) {
                    continue;
                }
                int common = 0;
                for (auto& [x, c] : cand[j].second) {
                    if (tuple.count(x)) {
                        common++;
                    }
                }
                if (2 * common >= int(cand[j].second.size())) {
                    members.push_back(j);
                    for (auto& [x, c] : cand[j].second) {
                        tuple.insert(x);
                    }
                    grew = true;
                }
            }
        }
        // ---- spec budgets : K >= 3, n >= 4, zeros <= 10% of K x n ----
        int K = int(members.size()), n = int(tuple.size());
        if (K < 3 || n < 4) {
            continue;
        }
        long cells = long(K) * n, zeros = 0;
        for (size_t m : members) {
            zeros += n - long(cand[m].second.size());
        }
        if (10 * zeros > cells) {
            continue;
        }
        // ---- coefficient density : a table whose coefficient trees
        // repeat is SIGN/SHARE-STRUCTURED (an FDN's Hadamard butterfly :
        // +-g per column, 128 distinct trees in 1024 cells) -- there the
        // lowered binary form shares partial sums the literal dot
        // products cannot beat (measured x2 against it). The row regime
        // claims only information-dense tables : distinct coefficient
        // trees over at least half of the non-zero cells.
        {
            std::set<Tree> distinct;
            long           nonzero = 0;
            for (size_t m : members) {
                for (auto& [x, c] : cand[m].second) {
                    distinct.insert(c);
                    nonzero++;
                }
            }
            if (2 * long(distinct.size()) < nonzero) {
                continue;
            }
        }
        // ---- the plan : canonical column order = tlib tree order ------
        MatrixFamily F;
        F.tuple.assign(tuple.begin(), tuple.end());
        std::sort(F.tuple.begin(), F.tuple.end(), treeorder());
        Tree kl = gGlobal->nil;
        for (auto it = F.tuple.rbegin(); it != F.tuple.rend(); ++it) {
            kl = cons(*it, kl);
        }
        F.key = kl;
        for (size_t m : members) {
            used[m] = 1;
            std::vector<Tree> rc;
            for (Tree x : F.tuple) {
                auto it = cand[m].second.find(x);
                rc.push_back(it == cand[m].second.end() ? sigInt(0) : it->second);
            }
            plans.rowOf[cand[m].first] = {int(plans.families.size()), int(F.rows.size())};
            F.rows.push_back(cand[m].first);
            F.coef.push_back(rc);
        }
        plans.families.push_back(F);
    }
    if (getenv("FAUST_MATRIX_CENSUS")) {
        fprintf(stderr, "MATRIX census : %d candidats, %d familles\n", int(cand.size()),
                int(plans.families.size()));
        for (size_t f = 0; f < plans.families.size(); f++) {
            auto& F     = plans.families[f];
            long  cells = long(F.rows.size()) * F.tuple.size(), zeros = 0;
            for (auto& rc : F.coef) {
                for (Tree c : rc) {
                    if (isZero(c)) {
                        zeros++;
                    }
                }
            }
            fprintf(stderr, "  famille %zu : K=%zu n=%zu zeros=%ld/%ld\n", f, F.rows.size(),
                    F.tuple.size(), zeros, cells);
        }
    }
    return plans;
}
