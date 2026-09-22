#include "kernelCandidacy.hh"
#include "sigGenCut.hh"

#include <cstdio>
#include <cstdlib>
#include <functional>
#include <map>
#include <optional>
#include <unordered_map>
#include <set>
#include <vector>

#include "rewrite.hh"
#include "signals.hh"
#include "sigs-state.hh"

// a shifted kernel site : FIR[x@d, c..] with a literal d > 0
static bool isShiftedKernel(Tree t, Tree& x, int& d, tvec& coef)
{
    Tree a, b;
    if (isSigFIR(t, coef) && isSigDelay(coef[0], a, b) && isSigInt(b, &d) && d > 0) {
        x = a;
        return true;
    }
    return false;
}

static bool constCoefs(const tvec& V)
{
    for (size_t i = 1; i < V.size(); i++) {
        if (sigs::sigOrder(V[i]) > 1) {
            return false;
        }
    }
    return true;
}

// The subtrees LEXICALLY inside a group's definitions : descend every
// branch but never through a projection of ANOTHER group -- what sits in
// V's body is V's, even when W uses V.
static void subTreesOf(Tree w, std::set<Tree>& sub)
{
    Tree id, le;
    if (!isRec(w, id, le)) {
        return;
    }
    std::function<void(Tree)> walk = [&](Tree t) {
        if (!sub.insert(t).second) {
            return;
        }
        int  pj;
        Tree pw;
        if (isProj(t, &pj, pw)) {
            return;  // a reference, not a residence
        }
        for (int k = 0; k < t->arity(); k++) {
            walk(t->branch(k));
        }
    };
    while (isList(le)) {
        walk(hd(le));
        le = tl(le);
    }
}

Tree kernelCandidacy(Tree L)
{
    // ---- census : shifted constant-class kernel sites and their verdict
    std::set<Tree> keep;     // self sites : stay inline whatever else
    std::set<Tree> retime;   // materialization candidates
    {
        std::set<Tree>                 seen;
        std::vector<Tree>              work;
        std::map<Tree, std::set<Tree>> bodies;
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
            Tree x;
            int  d, pj;
            Tree pw;
            tvec coef;
            if (isShiftedKernel(t, x, d, coef) && constCoefs(coef)) {
                if (isProj(x, &pj, pw)) {
                    if (!bodies.count(pw)) {
                        subTreesOf(pw, bodies[pw]);
                    }
                    if (bodies[pw].count(t)) {
                        keep.insert(t);  // self : inline, never carried state
                    } else {
                        retime.insert(t);  // cross-group projection read
                    }
                } else {
                    retime.insert(t);  // non-recursive source (FFT windows)
                }
            }
            for (int k = 0; k < t->arity(); k++) {
                work.push_back(t->branch(k));
            }
        }
    }
    for (Tree t : keep) {
        retime.erase(t);  // read from both sides : the state is the danger
    }
    if (retime.empty()) {
        return L;
    }
    // ---- the retiming law, applied to the elected sites ---------------
    auto rule = [&](Tree sig) -> Tree {
        Tree x;
        int  d;
        tvec coef;
        if (retime.count(sig) && isShiftedKernel(sig, x, d, coef)) {
            tvec nc;
            nc.push_back(x);
            for (size_t i = 1; i < coef.size(); i++) {
                nc.push_back(coef[i]);
            }
            return sigDelay(sigFIR(nc), sigInt(d));
        }
        return sig;
    };
    return treeRewrite(L, sigGenCut, rule);
}

//----------------------------------------------------------------------
// unit kernels : back to the sums
//----------------------------------------------------------------------

// every tap is a literal 0, +1 or -1, and two taps at least are not 0. The
// all-ones contiguous kernels of four taps and more stay kernels : they are
// moving sums, emitted in O(1) whatever their length (generateFIR).
static bool isUnitKernel(const tvec& V)
{
    bool sliding = V.size() >= 5;
    for (size_t i = 1; sliding && i < V.size(); i++) {
        sliding = isOne(V[i]);
    }
    if (sliding) {
        return false;
    }
    int taps = 0;
    for (size_t i = 1; i < V.size(); i++) {
        if (isZero(V[i])) {
            continue;
        }
        if (!isOne(V[i]) && !isMinusOne(V[i])) {
            return false;
        }
        taps++;
    }
    return taps >= 2;
}

Tree dissolveUnitKernels(Tree L)
{
    // parents of every node (one per edge, rec bodies crossed once) : a
    // dissolved kernel is spliced into its reader only when it has one
    std::map<Tree, int, treeorder> occ;
    {
        std::set<Tree>    seen;
        std::vector<Tree> work{L};
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
    std::set<Tree>                 born;  // the sums this pass made
    std::unordered_map<Tree, Tree> memo;
    auto pre     = sigGenCut;  // NEVER TRANSFORM A GENERATOR (sigGenCut.hh)
    auto defRule = [](Tree, Tree rebuilt) -> Tree { return rebuilt; };
    auto rule    = [&](Tree orig, Tree rebuilt) -> Tree {
        tvec V;
        if (isSigFIR(rebuilt, V) && isUnitKernel(V)) {
            // a shifted kernel FIR[x@d, c..] reads x itself, d samples later
            Tree x = V[0];
            int  d0 = 0;
            Tree a, b;
            if (isSigDelay(x, a, b) && isSigInt(b, &d0) && d0 > 0) {
                x = a;
            } else {
                d0 = 0;
            }
            tvec terms;
            for (size_t i = 1; i < V.size(); i++) {
                if (isZero(V[i])) {
                    continue;
                }
                int  d = d0 + int(i) - 1;
                Tree t = (d == 0) ? x : sigDelay(x, sigInt(d));
                terms.push_back(isMinusOne(V[i]) ? sigMul(sigInt(-1), t) : t);
            }
            Tree sum = sigSum(terms);
            born.insert(sum);
            return sum;
        }
        tvec subs, osubs;
        if (isSigSum(rebuilt, subs) && isSigSum(orig, osubs) && subs.size() == osubs.size()) {
            tvec flat;
            bool spliced = false;
            for (size_t k = 0; k < subs.size(); k++) {
                tvec inner;
                if (born.count(subs[k]) && occ[osubs[k]] == 1 && isSigSum(subs[k], inner)) {
                    flat.insert(flat.end(), inner.begin(), inner.end());
                    spliced = true;
                } else {
                    flat.push_back(subs[k]);
                }
            }
            if (spliced) {
                return sigSum(flat);
            }
        }
        return rebuilt;
    };
    return treeRewritePairedMemo(L, pre, rule, memo, defRule);
}

