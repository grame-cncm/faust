#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "ppsig.hh"
#include "revealFIR.hh"
#include "sigFIR.hh"
#include "sigIIR.hh"
#include "sigIdentity.hh"

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

    if (Tree ck, h, f, d; isSigDelay(sig, ck, d) && isSigClocked(ck, h, f) && isSigFIR(f)) {
        return delaySigFIR(f, d);
    }

    if (Tree f, d; isSigDelay(sig, f, d) && isSigFIR(f)) {
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

// External API

Tree revealFIR(Tree L1)
{
    FIRRevealer R;
    R.trace(TRACE, "revealFIR");
    Tree L2 = R.mapself(L1);
    return L2;
}
