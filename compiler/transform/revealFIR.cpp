#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "ppsig.hh"
#include "revealFIR.hh"
#include "sigFIR.hh"
#include "sigIIR.hh"
#include "sigIdentity.hh"
#include "sigRecursiveDependencies.hh"
#include "sigorderrules.hh"

#define TRACE false

// Transform a signal expression by revealing FIR structures

// Tree revealIIR(Tree rt, Tree def);

class FIRRevealer : public SignalIdentity {
   protected:
    Tree postprocess(Tree L);
    Tree transformation(Tree L);
};

Tree FIRRevealer::transformation(Tree sig)
{
    Tree var, le;
    if (isRec(sig, var, le)) {
        Tree var2 = tree(unique("M"));
        Tree rec2 = rec(var2, gGlobal->nil);
        traceMsg("WARNING: We have set the definitions to nil for group", rec2);
        fResult.set(sig, rec2);     // We rename the recgroup
        Tree l2   = mapself(le);    // We transfom its definitions
        Tree rec3 = rec(var2, l2);  // We update the definition
        traceMsg("WARNING: We have updated the definitions of group", rec3);
        return rec3;

    } else {
        return SignalIdentity::transformation(sig);
    }
}

// isFirElem((x@d)*c) -> <x, d, c> with d integer constant
std::optional<std::tuple<Tree, int, Tree>> isFirElem(Tree s)
{
    if (Tree x, d; isSigDelay(s, x, d)) {
        if (int i; isSigInt(d, &i)) {
            return std::make_tuple(x, i, sigInt(1));
        }
        return std::nullopt;
    }

    if (Tree m, c, x, d; isSigMul(s, m, c) && isSigDelay(m, x, d)) {
        if (int i; isSigInt(d, &i)) {
            return std::make_tuple(x, i, c);
        }
        return std::nullopt;
    }

    if (Tree m, c, x, d; isSigMul(s, c, m) && isSigDelay(m, x, d)) {
        if (int i; isSigInt(d, &i)) {
            return std::make_tuple(x, i, c);
        }
        return std::nullopt;
    }

    return std::nullopt;
}
// multiply a sigSum sum by a signal c
static Tree mulSigSum(Tree sum, Tree c)
{
    tvec subs;
    for (Tree s : sum->branches()) {
        subs.push_back(mulSigFIR(s, c));
    }
    return sigSum(subs);
}

/**
 * @brief Collect recursively all the elements of a sum
 *
 * @param L
 * @param sig
 */
static void collectSigSumElements(tvec& L, Tree sig)
{
    if (isSigSum(sig)) {
        for (Tree s : sig->branches()) {
            collectSigSumElements(L, s);
        }
    } else {
        L.push_back(sig);
    }
}

/* FIR pattern matching rules
    - x@d -> FIR(x, C[0], C[1],..C[d]) if d is a constant and d > 0 with C[i] = 0 for i != d and
   C[d] = 1
    - x@d*c -> FIR(x, C[0], C[1],..C[d]) if d is a constant and d > 0 with C[i] = 0 for i != d and
   C[d] = c
    - SUM(...,FIR(x,C), FIR(x,C'),...) -> SUM(...,FIR(x, C+C'),...)
    - SUM(...,FIR(x,C), x*a, ...) -> SUM(...,FIR(x, C+a),...)
*/

Tree FIRRevealer::postprocess(Tree sig)
{
    // std::cerr << "postprocess: " << ppsig(sig) << "\n";

    if (Tree ck, f; isSigClocked(sig, ck, f) && isSigFIR(f)) {
        // std::cerr << "Rule 0: pass clock inside fir\n";
        tvec V = f->branches();
        V[0]   = sigClocked(ck, V[0]);
        return sigFIR(V);
    }

    if (Tree f, d; isSigDelay(sig, f, d)) {
        // std::cerr << "Rule 1\n";
        return delaySigFIR(f, d);
    }

    if (Tree ck, h, f, c; isSigMul(sig, ck, c) && isSigClocked(ck, h, f) && isSigFIR(f)) {
        // std::cerr << "Rule 6\n";
        return mulSigFIR(f, c);
    }

    if (Tree ck, h, f, c; isSigMul(sig, c, ck) && isSigClocked(ck, h, f) && isSigFIR(f)) {
        // std::cerr << "Rule 7\n";
        return mulSigFIR(f, c);
    }

    if (Tree x, y, u, v, h, f; isSigMul(sig, x, y) && isSigMul(y, u, v) && isSigClocked(v, h, f)) {
        // std::cerr << "Rule 8\n";
        return sigMul(sigMul(x, u), v);
    }

    if (Tree x, y, u, v, h, f; isSigMul(sig, x, y) && isSigMul(y, v, u) && isSigClocked(v, h, f)) {
        // std::cerr << "Rule 9\n";
        return sigMul(sigMul(x, u), v);
    }

    if (Tree x, y, u, v, h, f; isSigMul(sig, y, x) && isSigMul(y, u, v) && isSigClocked(v, h, f)) {
        // std::cerr << "Rule 10\n";
        return sigMul(sigMul(x, u), v);
    }

    if (Tree x, y, u, v, h, f; isSigMul(sig, y, x) && isSigMul(y, v, u) && isSigClocked(v, h, f)) {
        // std::cerr << "Rule 11\n";
        return sigMul(sigMul(x, u), v);
    }

    if (Tree sum, c; isSigMul(sig, sum, c) && isSigSum(sum)) {
        // std::cerr << "Rule 12\n";
        return mulSigSum(sum, c);
    }

    if (Tree sum, c; isSigMul(sig, c, sum) && isSigSum(sum)) {
        // std::cerr << "Rule 13\n";
        return mulSigSum(sum, c);
    }

    if (Tree f, c; isSigMul(sig, f, c) && isSigFIR(f)) {
        // std::cerr << "Rule 14\n";
        return mulSigFIR(f, c);
    }

    if (Tree f, c; isSigMul(sig, c, f) && isSigFIR(f)) {
        // std::cerr << "Rule 15\n";
        return mulSigFIR(f, c);
    }

    if (Tree ck, h, f, c; isSigDiv(sig, ck, c) && isSigClocked(ck, h, f) && isSigFIR(f)) {
        // std::cerr << "Rule 16\n";
        return divSigFIR(f, c);
    }

    if (Tree f, c; isSigDiv(sig, f, c) && isSigFIR(f)) {
        // std::cerr << "Rule 17\n";
        return divSigFIR(f, c);
    }

    if (Tree x, y; isSigMul(sig, x, y) && (getSigOrder(x) < 3) && isSigFIR(y)) {
        // std::cerr << "Rule 2\n";
        return mulSigFIR(y, x);
    }

    if (Tree x, y; isSigMul(sig, y, x) && (getSigOrder(x) < 3) && isSigFIR(y)) {
        // std::cerr << "Rule 3\n";
        return mulSigFIR(y, x);
    }

    if (Tree x, y; isSigMul(sig, x, y) && (getSigOrder(x) < 3) && (getSigOrder(y) == 3)) {
        // std::cerr << "Rule 4\n";
        tvec v{y, x};
        return sigFIR(v);
    }

    if (Tree x, y; isSigMul(sig, y, x) && (getSigOrder(x) < 3) && (getSigOrder(y) == 3)) {
        // std::cerr << "Rule 5\n";
        tvec v{y, x};
        return sigFIR(v);
    }

    if (isSigSum(sig)) {
        // std::cerr << "\nWe have a sum: " << ppsig(sig) << "\n";
        tvec subs;
        collectSigSumElements(subs, sig);
        std::map<Tree, Tree> M;
        std::vector<Tree>    L;
        // 1 - combine FIRs and collect non-FIR elements
        for (Tree f : subs) {
            if (tvec coefs; isSigFIR(f, coefs)) {
                Tree x = coefs[0];  // the input signal of the FIR
                if (M.find(x) == M.end()) {
                    M[x] = f;  // add a new fir association
                } else {
                    M[x] = addSigFIR(M[x], f);  // combine FIRs with the same input signal
                }
                // std::cerr << "We have a new FIR association: " << ppsig(x) << " -> " <<
                // ppsig(M[x])
                //           << "\n";
            } else {
                // std::cerr << "We have a non-FIR element: " << ppsig(f) << "\n";
                L.push_back(f);  // collect non-FIR elements
            }
        }
        // 2 - check for non-FIR elements that are input signals of collected FIRs
        std::vector<Tree> L2;
        for (Tree f : L) {
            if (M.find(f) != M.end()) {
                M[f] = addSigFIR(M[f], f);
            } else if (Tree x, y; isSigMul(f, x, y)) {
                if (M.find(x) != M.end()) {
                    M[x] = addSigFIR(M[x], f);
                } else if (M.find(y) != M.end()) {
                    M[y] = addSigFIR(M[y], f);
                } else {
                    L2.push_back(f);
                }
            } else {
                L2.push_back(f);
            }
        }

        // combine all FIRs in M and non-FIR elements in L2
        std::vector<Tree> V;
        for (auto [x, f] : M) {
            V.push_back(f);  // add FIRs to the final sum
        }
        for (Tree f : L2) {
            V.push_back(f);
        }
        if (V.size() == 1) {
            return V[0];
        } else {
            return sigSum(V);
        }
    }

    return sig;
}

#if 0
Tree FIRRevealer::postprocess(Tree sig)
{
    if (tvec subs; isSigSum(sig, subs)) {
        std::map<Tree, std::map<int, Tree>> M;  // Map of all FIRs collected
        std::vector<Tree>                   L;  // vector of non-FIR elements
        // We collect all FIRs in M and non-FIR elements in L
        std::cerr << "\n\nWe have the sum: " << ppsig(sig) << "\n";
        std::cerr << "We have a sum of " << subs.size() << " elements\n";
        for (Tree s : subs) {
            if (auto elem = isFirElem(s)) {
                std::cerr << "We have a FIR element: " << ppsig(s) << "\n";
                auto [x, d, c] = *elem;
                if (M.find(x) == M.end()) {
                    M[x] = {{d, c}};
                } else if (M[x].find(d) == M[x].end()) {
                    M[x][d] = c;
                } else {
                    M[x][d] = sigAdd(M[x][d], c);
                }
            } else {
                std::cerr << "We have a non-FIR element: " << ppsig(s) << "\n";
                L.push_back(s);
            }
        }
        std::cerr << "We have " << M.size() << " FIRs and " << L.size() << " non-FIR elements\n";
        // We check if non-FIR elements in L are input signals of FIRs in M
        std::vector<Tree> L2;
        for (Tree s : L) {
            if (M.find(s) != M.end()) {
                // s is an input signal of a FIR in M
                if (M[s].find(0) != M[s].end()) {
                    M[s][0] = sigAdd(M[s][0], sigInt(1));
                } else {
                    M[s][0] = sigInt(1);
                }
            } else {
                // s is not an input signal of a FIR in M
                // check if it can be decomposed into an input signal and a coefficient
                if (Tree x, y; isSigMul(s, x, y)) {
                    if (M.find(x) != M.end()) {
                        // x is an input signal of a FIR in M
                        std::cerr << "We have a FIR input: " << ppsig(x) << " with coef "
                                  << ppsig(y) << "\n";
                        if (M[x].find(0) != M[x].end()) {
                            M[x][0] = sigAdd(M[x][0], y);
                        } else {
                            M[x][0] = y;
                        }
                    } else if (M.find(y) != M.end()) {
                        // y is an input signal of a FIR in M
                        std::cerr << "We have a FIR input: " << ppsig(y) << " with coef "
                                  << ppsig(x) << "\n";
                        if (M[y].find(0) != M[y].end()) {
                            M[y][0] = sigAdd(M[y][0], x);
                        } else {
                            M[y][0] = x;
                        }
                    } else {
                        L2.push_back(s);
                    }
                } else {
                    L2.push_back(s);
                }
            }
        }
        std::cerr << "We have " << L2.size() << " non-FIR elements after processing\n";
        // combine all FIRs in M and non-FIR elements in L2
        tvec V;
        for (auto [x, D] : M) {
            std::cerr << "We have a FIR with input " << ppsig(x) << " and " << D.size()
                      << " delays\n";
            int maxd = 0;
            for (auto [d, c] : D) {
                if (d > maxd) {
                    maxd = d;
                }
            }
            tvec v2(maxd + 2, sigInt(0));
            v2[0] = x;
            for (auto [d, c] : D) {
                v2[d + 1] = c;
            }

            Tree f = sigFIR(v2);
            std::cerr << "We have a FIR: " << ppsig(f) << "\n";
            V.push_back(f);
        }
        for (Tree s : L2) {
            V.push_back(s);
        }

        Tree res;
        if (V.size() == 1) {
            res = V[0];
        } else {
            res = sigSum(V);
        }
        std::cerr << "We have " << V.size() << " elements in the final sum\n";
        std::cerr << "The final sum is: " << ppsig(res) << "\n";
        return res;
    }


    if (Tree f, d; isSigDelay(sig, f, d)) {
        return delaySigFIR(f, d);
    }

    if (Tree ck, h, f, c; isSigMul(sig, ck, c) && isSigClocked(ck, h, f) && isSigFIR(f)) {
        return mulSigFIR(f, c);
    }

    if (Tree ck, h, f, c; isSigMul(sig, c, ck) && isSigClocked(ck, h, f) && isSigFIR(f)) {
        return mulSigFIR(f, c);
    }

    if (Tree f, c; isSigMul(sig, f, c) && isSigFIR(f)) {
        return mulSigFIR(f, c);
    }

    if (Tree f, c; isSigMul(sig, c, f) && isSigFIR(f)) {
        return mulSigFIR(f, c);
    }

    if (Tree ck, h, f, c; isSigDiv(sig, ck, c) && isSigClocked(ck, h, f) && isSigFIR(f)) {
        return divSigFIR(f, c);
    }

    if (Tree f, c; isSigDiv(sig, f, c) && isSigFIR(f)) {
        return divSigFIR(f, c);
    }

    return sig;
}
#endif

// External API

Tree revealFIR(Tree L1)
{
    FIRRevealer R;
    R.trace(TRACE, "revealFIR");
    Tree L2 = R.mapself(L1);
    return L2;
}
