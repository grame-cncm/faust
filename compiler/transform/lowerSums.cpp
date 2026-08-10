#include "lowerSums.hh"

#include <algorithm>
#include <map>
#include <set>
#include <vector>

#include "global.hh"
#include "rewrite.hh"

// Deterministic unordered-pair key : both components in treeorder.
using TPair = std::pair<Tree, Tree>;

struct PairOrder {
    bool operator()(const TPair& a, const TPair& b) const
    {
        treeorder lt;
        if (lt(a.first, b.first)) {
            return true;
        }
        if (lt(b.first, a.first)) {
            return false;
        }
        return lt(a.second, b.second);
    }
};

static TPair makePair(Tree a, Tree b)
{
    treeorder lt;
    return lt(a, b) ? TPair{a, b} : TPair{b, a};
}

// Collect every distinct Sum node reachable from the root (rec bodies
// crossed once) and count the unordered term pairs across all of them.
static void collectSums(Tree root, std::vector<Tree>& sums,
                        std::map<TPair, int, PairOrder>& count)
{
    std::set<Tree>    seen;
    std::vector<Tree> work{root};
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
            sums.push_back(t);
            for (size_t i = 0; i < subs.size(); i++) {
                for (size_t j = i + 1; j < subs.size(); j++) {
                    if (subs[i] != subs[j]) {
                        count[makePair(subs[i], subs[j])] += 1;
                    }
                }
            }
        }
        for (int k = 0; k < t->arity(); k++) {
            work.push_back(t->branch(k));
        }
    }
}

// Lower ONE sum : greedy merge of the globally most frequent pair while
// one occurs in at least two sums, then canonically-sorted left comb.
static Tree lowerOneSum(const tvec& subs0, const std::map<TPair, int, PairOrder>& count)
{
    std::vector<Tree> terms(subs0.begin(), subs0.end());
    treeorder         lt;

    while (terms.size() > 2) {
        // the globally most frequent pair present in THIS sum
        int    best = 1;  // needs >= 2 to be worth a shared node
        size_t bi = 0, bj = 0;
        TPair  bkey{nullptr, nullptr};
        for (size_t i = 0; i < terms.size(); i++) {
            for (size_t j = i + 1; j < terms.size(); j++) {
                if (terms[i] == terms[j]) {
                    continue;
                }
                TPair key = makePair(terms[i], terms[j]);
                auto  it  = count.find(key);
                int   c   = (it == count.end()) ? 0 : it->second;
                if (c > best || (c == best && bkey.first != nullptr &&
                                 PairOrder()(key, bkey))) {
                    best = c;
                    bi   = i;
                    bj   = j;
                    bkey = key;
                }
            }
        }
        if (bkey.first == nullptr) {
            break;  // no shared pair left : fold canonically
        }
        Tree merged = sigAdd(bkey.first, bkey.second);  // treeorder operand order
        terms[bi]   = merged;
        terms.erase(terms.begin() + bj);
    }

    // canonically-sorted left comb : identical term multisets fold to the
    // same tree, common prefixes become shared nodes
    std::sort(terms.begin(), terms.end(), lt);
    Tree acc = terms[0];
    for (size_t k = 1; k < terms.size(); k++) {
        acc = sigAdd(acc, terms[k]);
    }
    return acc;
}

Tree lowerSums(Tree L)
{
    std::vector<Tree>               sums;
    std::map<TPair, int, PairOrder> count;
    collectSums(L, sums, count);
    if (sums.empty()) {
        return L;
    }

    // the lowering rule : counts are keyed on the ORIGINAL terms ; a term
    // rewritten by an inner lowering (a sum nested through a Mul...) simply
    // misses its counts and falls back to the canonical fold
    auto rule = [&count](Tree sig) -> Tree {
        if (tvec subs; isSigSum(sig, subs)) {
            if (subs.size() == 1) {
                return subs[0];
            }
            return lowerOneSum(subs, count);
        }
        return sig;
    };
    return treeRewrite(L, rule);
}
