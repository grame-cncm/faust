#include <map>
#include <optional>
#include <set>
#include <unordered_map>
#include <vector>

#include "sigs-state.hh"
#include "revealSum.hh"
#include "rewrite.hh"
#include "sigs-state.hh"
#include "simplify.hh"

// simplify() requires closed terms : during the rewrite, the subtrees of
// a recursive group carry open references (ref without a filled rec) that
// the rewriting machinery refuses (rewrite.hh, body != nullptr). The guard
// derives from the contract : a non rec-free term stays as it is -- the
// simplification is an optimization.
static Tree recSafeSimplify(Tree t)
{
    return t->isRecFree() ? simplify(t) : t;
}

// Negate a signal: S -> -S. The negation never rewrites the term : the
// general simplifier, applied to -1 * S, renormalizes S itself, and an n-ary
// Sum already revealed inside S (under a delay, say) went back to its binary
// spelling. The same delayed signal then lived under two spellings -- the
// revealed one where it is added, the binary one where it is subtracted : two
// delay lines for one signal, and one of them out of reach of the dispatch (a
// chain of two Hadamard matrices separated by delays wrote 15 lines for 8).
// A constant factor is NOT folded either : -1 * (k * x) keeps the product
// k * x it shares with its positive occurrences, where (-k) * x is one more
// multiplication and an atom the dispatch cannot pair.
static Tree sigNeg(Tree sig)
{
    Tree x, y;
    if (isSigMul(sig, x, y)) {
        if (isMinusOne(x)) {
            return y;
        }
        if (isMinusOne(y)) {
            return x;
        }
    }
    if (isNum(sig)) {
        return recSafeSimplify(sigMul(sigInt(-1), sig));
    }
    return sigMul(sigInt(-1), sig);
}

// occurrence count on the ORIGINAL tree (one per parent edge, rec bodies
// crossed once) : flattening THROUGH a shared sub-sum destroys structural
// sharing -- an FDN's butterfly stages are adds with two consumers each,
// and splicing them into every consumer turns O(N log N) additions into
// O(N^2) (fdnRev : 823 -> 3056). The reassociate pass learned the same
// lesson : a shared node is an ATOM of the enclosing spine.
static void countOcc(Tree root, std::map<Tree, int, treeorder>& occ)
{
    std::set<Tree>    seen;
    std::vector<Tree> work{root};
    while (!work.empty()) {
        Tree t = work.back();
        work.pop_back();
        Tree var, body;
        if (isRec(t, var, body)) {
            if (seen.insert(t).second && body) {
                work.push_back(body);
            }
            continue;
        }
        for (int k = 0; k < t->arity(); k++) {
            Tree c = t->branch(k);
            occ[c] += 1;
            if (seen.insert(c).second) {
                work.push_back(c);
            }
        }
    }
}

// Append the terms of x (rebuilt) to zsubs : spliced when x is a Sum whose
// ORIGINAL was single-use, kept as one opaque atom otherwise. A SHARED sum
// is spliced too when the caller gathers through the sharing (maxShared > 0)
// and the row stays within maxShared terms.
// Returns whether x was spliced (its terms taken) rather than kept as an atom.
static bool appendTerms(Tree xrebuilt, bool xShared, bool invert, tvec& zsubs, size_t maxShared)
{
    tvec subs;
    if (isSigSum(xrebuilt, subs) && (!xShared || zsubs.size() + subs.size() <= maxShared)) {
        for (Tree s : subs) {
            zsubs.push_back(invert ? sigNeg(s) : s);
        }
        return true;
    }
    zsubs.push_back(invert ? sigNeg(xrebuilt) : xrebuilt);
    return false;
}

// External API

// throughShared : gather THROUGH the shared sub-sums. The protection above
// is right when nothing rebuilds the sharing afterwards (-fir alone : the
// flattened Hadamard matrix of size n costs n(n-1) additions). When the
// dispatch of lowerSums follows, the opaque atoms are what keeps it away
// from the optimum : the shared sub-sums of the normal form are arbitrary
// partial nestings, not the stages of the butterfly, and the dispatch cannot
// undo them. Gathering everything lets it rebuild n.log2(n) on the Hadamard
// series, whatever the writing. The rows are bounded : a sum over a graph of
// shared sums can repeat its terms exponentially, and the dispatch is
// quadratic in the row size.
static const size_t kMaxGatheredRow = 256;

Tree revealSum(Tree L1, bool throughShared, std::unordered_map<Tree, Tree>* origins,
               std::unordered_map<Tree, std::vector<Tree>>* consumed)
{
    const size_t maxShared = throughShared ? kMaxGatheredRow : 0;
    std::map<Tree, int, treeorder> occ;
    countOcc(L1, occ);
    auto shared = [&occ](Tree t) {
        auto it = occ.find(t);
        return it != occ.end() && it->second > 1;
    };

    std::unordered_map<Tree, Tree> memo;
    auto pre     = [](Tree) -> std::optional<Tree> { return std::nullopt; };
    auto defRule = [](Tree, Tree rebuilt) -> Tree { return rebuilt; };

    // AUDIO sums only (see the conditioning note in the commit history :
    // flattening a slow add invites cancelling distributions). The
    // original side supplies the audio bit and the occurrences ; the
    // rebuilt side supplies the terms.
    // the original binary sums a revealed sum absorbed : the spliced operand
    // itself (an original node) and what it had absorbed in turn
    auto absorb = [&](Tree result, Tree xo, Tree xr, bool spliced) {
        if (!consumed || !spliced) {
            return;
        }
        auto& v = (*consumed)[result];
        v.push_back(xo);
        if (auto it = consumed->find(xr); it != consumed->end()) {
            v.insert(v.end(), it->second.begin(), it->second.end());
        }
    };
    auto reveal = [&](Tree orig, Tree rebuilt) -> Tree {
        if (!sigs::isAudioRate(orig)) {
            return rebuilt;
        }
        Tree xo, yo, xr, yr;
        if (isSigAdd(orig, xo, yo) && isSigAdd(rebuilt, xr, yr)) {
            tvec zsubs;
            bool sx = appendTerms(xr, shared(xo), false, zsubs, maxShared);
            bool sy = appendTerms(yr, shared(yo), false, zsubs, maxShared);
            Tree r  = sigSum(zsubs);
            absorb(r, xo, xr, sx);
            absorb(r, yo, yr, sy);
            return r;
        }
        if (isSigSub(orig, xo, yo) && isSigSub(rebuilt, xr, yr)) {
            tvec zsubs;
            bool sx = appendTerms(xr, shared(xo), false, zsubs, maxShared);
            bool sy = appendTerms(yr, shared(yo), true, zsubs, maxShared);
            Tree r  = sigSum(zsubs);
            absorb(r, xo, xr, sx);
            absorb(r, yo, yr, sy);
            return r;
        }
        return rebuilt;
    };
    auto rule = [&](Tree orig, Tree rebuilt) -> Tree {
        Tree result = reveal(orig, rebuilt);
        if (origins && result != orig) {
            (*origins)[result] = orig;
            // a group is reached through its projections only, and the rewrite
            // gives every group a fresh variable : its origin is recorded here
            int  i, j;
            Tree ng, og;
            if (isProj(result, &i, ng) && isProj(orig, &j, og) && ng != og) {
                (*origins)[ng] = og;
            }
        }
        return result;
    };

    return treeRewritePairedMemo(L1, pre, rule, memo, defRule);
}
