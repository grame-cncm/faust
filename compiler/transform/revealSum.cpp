#include <map>
#include <optional>
#include <set>
#include <unordered_map>
#include <vector>

#include "global.hh"
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

// Negate a signal: S -> -S
static Tree sigNeg(Tree sig)
{
    return recSafeSimplify(sigMul(sigInt(-1), sig));
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
// ORIGINAL was single-use, kept as one opaque atom otherwise.
static void appendTerms(Tree xrebuilt, bool xShared, bool invert, tvec& zsubs)
{
    tvec subs;
    if (!xShared && isSigSum(xrebuilt, subs)) {
        for (Tree s : subs) {
            zsubs.push_back(invert ? sigNeg(s) : s);
        }
        return;
    }
    zsubs.push_back(invert ? sigNeg(xrebuilt) : xrebuilt);
}

// External API

Tree revealSum(Tree L1)
{
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
    auto rule = [&](Tree orig, Tree rebuilt) -> Tree {
        if (!sigs::isAudioRate(orig)) {
            return rebuilt;
        }
        Tree xo, yo, xr, yr;
        if (isSigAdd(orig, xo, yo) && isSigAdd(rebuilt, xr, yr)) {
            tvec zsubs;
            appendTerms(xr, shared(xo), false, zsubs);
            appendTerms(yr, shared(yo), false, zsubs);
            return sigSum(zsubs);
        }
        if (isSigSub(orig, xo, yo) && isSigSub(rebuilt, xr, yr)) {
            tvec zsubs;
            appendTerms(xr, shared(xo), false, zsubs);
            appendTerms(yr, shared(yo), true, zsubs);
            return sigSum(zsubs);
        }
        return rebuilt;
    };

    return treeRewritePairedMemo(L1, pre, rule, memo, defRule);
}
