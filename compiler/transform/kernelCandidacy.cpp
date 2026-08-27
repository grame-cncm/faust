#include "kernelCandidacy.hh"

#include <cstdio>
#include <cstdlib>
#include <functional>
#include <map>
#include <set>
#include <vector>

#include "signals.hh"

// the verdict key : present on a delay node = traversal site
static Tree inlineKey()
{
    return tree(symbol("KERNELINLINE"));
}

bool isKernelInline(Tree t)
{
    return t->getProperty(inlineKey()) != nullptr;
}

// a shifted kernel read : delay(DENSE(proj(W), K), literal d > 0)
static bool isShiftedProjKernelRead(Tree t, Tree& w)
{
    Tree x, y, src, kf, pw;
    int  d, pj;
    if (isSigDelay(t, x, y) && isSigInt(y, &d) && d > 0 && isSigDense(x, src, kf) &&
        isProj(src, &pj, pw)) {
        w = pw;
        return true;
    }
    return false;
}

// The subtrees LEXICALLY inside a group's definitions : descend every
// branch but never through a projection of ANOTHER group -- what sits in
// V's body is V's, even when W uses V. (A projection's group tree is one
// of its branches ; following it would annex the neighbour's body.)
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

void kernelCandidacy(Tree L)
{
    // ---- census : every shifted projection-kernel read, with its group
    std::vector<std::pair<Tree, Tree>> sites;  // (delay node, group tree)
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
            Tree w;
            if (isShiftedProjKernelRead(t, w)) {
                sites.push_back({t, w});
            }
            for (int k = 0; k < t->arity(); k++) {
                work.push_back(t->branch(k));
            }
        }
    }
    if (sites.empty()) {
        return;
    }
    // ---- residence : the group bodies, computed once per group
    std::map<Tree, std::set<Tree>> bodies;
    for (auto& [t, w] : sites) {
        if (!bodies.count(w)) {
            subTreesOf(w, bodies[w]);
        }
    }
    // ---- verdict : SELF (the site lives in its own source's group)
    //      traverses ; every other shifted read materializes
    int nself = 0, ncross = 0;
    for (auto& [t, w] : sites) {
        if (bodies[w].count(t)) {
            t->setProperty(inlineKey(), tree(1));
            nself++;
        } else {
            ncross++;
        }
    }
    if (getenv("FAUST_KERNEL_CANDIDACY")) {
        fprintf(stderr, "CANDIDACY : %d shifted proj reads -> self/inline=%d cross/mat=%d\n",
                int(sites.size()), nself, ncross);
    }
}
