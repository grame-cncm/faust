#include "kernelCandidacy.hh"

#include <cstdio>
#include <cstdlib>
#include <functional>
#include <map>
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
    return treeRewrite(L, rule);
}
