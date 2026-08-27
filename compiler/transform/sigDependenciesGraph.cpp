#include "sigDependenciesGraph.hh"

#include "kernelCandidacy.hh"
#include "ppsig.hh"
#include "signals.hh"
#include "sigtyperules.hh"
#include "exception.hh"

#undef TRACE
/**
 * @brief A signal visitor that builds a graph of dependencies
 * when full is true, the graph contains all dependencies,
 * otherwise it contains only immediate dependencies.
 */
class SigDependenciesGraph : public SignalVisitor {
   protected:
    digraph<Tree> fGraph;
    bool          fFullGraph;

   public:
    SigDependenciesGraph(bool full) : SignalVisitor(), fFullGraph(full)
    {
        fTrace   = false;
        fMessage = "SigDependenciesGraph";
    }

    digraph<Tree> getGraph() { return fGraph; }

   protected:
    void visit(Tree t) override;
};

/**
 * @brief Add the dependencies of a signal to the graph
 * The dependencies are the subsignals of the signal.
 * These dependencies are always immediate, unless the signal
 * is a delay expression.
 *
 * @param full: boolean to indicate if we want the full graph
 */
void SigDependenciesGraph::visit(Tree t)
{
    int  i;
    Tree w, x, y, tbl, ri;
    Tree size, gen, wi, ws;
#ifdef TRACE
    std::cerr << "Visiting: " << t << " : " << ppsig(t, 10) << "\n";
#endif
    fGraph.add(t);
    if (isProj(t, &i, w)) {
        // The immediate dependency of a projection is
        // its definition
        Tree id, le;
        faustassert(isRec(w, id, le));
        Tree d = nth(le, i);
        fGraph.add(t, d, 0);
        self(d);
    } else if (isSigDelay(t, x, y)) {
        int  sh;
        Tree tdsrc, tdkf;
        if (isSigInt(y, &sh) && isSigDense(x, tdsrc, tdkf) && isKernelInline(t)) {
            // the delay traverses the DENSE (one shifted read site) : the
            // kernel never becomes a schedulable node of its own. Edge and
            // visit order mirror the former FIR[x, 0..0, C..] case exactly
            // (dgorder reads insertion order).
            for (Tree c : tdkf->branches()) {
                if (!isZero(c)) {
                    fGraph.add(t, c, 0);
                }
            }
            if (fFullGraph || (sh == 0)) {
                fGraph.add(t, tdsrc, sh);
            }
            self(tdsrc);
            for (Tree c : tdkf->branches()) {
                if (!isZero(c)) {
                    self(c);
                }
            }
            return;
        }
        // We place x in the graph only if:
        // - we want the full graph
        // - or the dependency to x is immediate
        //  (i.e. the delay can potentially be 0)
        Type     Ty   = getCertifiedSigType(y);
        interval Iy   = Ty->getInterval();
        int      dmin = int(Iy.lo());
        if (fFullGraph || (dmin == 0)) {
            // x is an immediate dependencies
            // std::cerr << "The interval of y is: " << Iy << "\n";
            fGraph.add(t, x, dmin);
        }
        fGraph.add(t, y, 0);
        self(x);
        self(y);
    } else if (isSigDelay1(t, x)) {
        faustassert(false);
        // We place x in the graph only if:
        // - we want the full graph
        // - or the dependency to x is immediate
        //  (i.e. the delay can potentially be 0)
        if (fFullGraph) {
            // x is an immediate dependencies
            // std::cerr << "The interval of y is: " << Iy << "\n";
            fGraph.add(t, x, 1);
        }
        self(x);
    } else if (tvec V; isSigIIR(t, V)) {
        // IIR[nil,X,C0=0,C1,...] : X and the non-zero coefficients are
        // immediate dependencies ; the self-loop (full graph only) carries
        // the delay of the first non-zero self-coefficient
        faustassert(V.size() >= 4);
        int dmin = INT32_MAX;
        for (unsigned int k = 2; k < V.size(); k++) {
            if (!isZero(V[k])) {
                fGraph.add(t, V[k], 0);
                dmin = std::min(dmin, int(k) - 2);
            }
        }
        faustassert(dmin > 0 && dmin < INT32_MAX);
        fGraph.add(t, V[1], 0);
        if (fFullGraph) {
            fGraph.add(t, t, dmin);
        }
        for (auto s2 : V) {
            if (!isNil(s2) && !isZero(s2)) {
                self(s2);
            }
        }
    } else if (Tree dsrc, dkf; isSigDense(t, dsrc, dkf)) {
        // DENSE(x, KFORM(C)) : anchored (c0 != 0), the source is an
        // IMMEDIATE dependency. Edge and visit order mirror the former
        // FIR[x, C..] case exactly (dgorder reads insertion order).
        for (Tree c : dkf->branches()) {
            if (!isZero(c)) {
                fGraph.add(t, c, 0);
            }
        }
        fGraph.add(t, dsrc, 0);
        self(dsrc);
        for (Tree c : dkf->branches()) {
            if (!isZero(c)) {
                self(c);
            }
        }
    } else if (tvec V; isSigLtvFIR(t, V)) {
        // like the working FIR : non-zero coefficients immediate, the
        // source enters at the delay of the first non-zero tap
        faustassert(V.size() >= 2);
        int dmin2 = INT32_MAX;
        for (unsigned int k = 1; k < V.size(); k++) {
            if (!isZero(V[k])) {
                fGraph.add(t, V[k], 0);
                dmin2 = std::min(dmin2, int(k) - 1);
            }
        }
        faustassert(dmin2 < INT32_MAX);
        if (fFullGraph || (dmin2 == 0)) {
            fGraph.add(t, V[0], dmin2);
        }
        for (auto s2 : V) {
            if (!isZero(s2)) {
                self(s2);
            }
        }
    } else if (tvec V; isSigFIR(t, V)) {
        // FIR[X,C0,C1,...] : the non-zero coefficients are immediate
        // dependencies ; the source X enters with the delay of the first
        // non-zero coefficient (immediate only when that delay is 0)
        faustassert(V.size() >= 2);
        int dmin = INT32_MAX;
        for (unsigned int k = 1; k < V.size(); k++) {
            if (!isZero(V[k])) {
                fGraph.add(t, V[k], 0);
                dmin = std::min(dmin, int(k) - 1);
            }
        }
        faustassert(dmin < INT32_MAX);
        if (fFullGraph || (dmin == 0)) {
            fGraph.add(t, V[0], dmin);
        }
        for (auto s : V) {
            if (!isZero(s)) {
                self(s);
            }
        }
    } else if (isSigRDTbl(t, tbl, ri)) {
        // special case for tables. We can't compile the content without knowing the context

        if (isSigWRTbl(tbl, size, gen)) {
            fGraph.add(t, ri, 0);
            self(ri);
        } else if (isSigWRTbl(tbl, size, gen, wi, ws)) {
            fGraph.add(t, ri, 0);
            fGraph.add(t, wi, 0);
            fGraph.add(t, ws, 0);
            self(ri);
            self(wi);
            self(ws);
        } else {
            // not supposed to happen
            faustassert(false);
        }
    } else if (isSigWRTbl(t, size, gen, wi, ws)) {
        // not supposed to happen
        faustassert(false);
    } else {
        tvec subs;
        int  n = getSubSignals(t, subs, false);
        if (n == 0) {
            // A signal without dependencies
            fGraph.add(t);
        } else {
            // A signal with dependencies
            for (auto s : subs) {
                fGraph.add(t, s, 0);
            }
            // We visit the dependencies
            for (auto s : subs) {
                self(s);
            }
        }
    }
}

/**
 * @brief Compute the immediate Graph (containing only immediate dependencies)
 * of a list of signals
 *
 * @param L list of signals
 * @return digraph<Tree>
 */
digraph<Tree> immediateGraph(Tree L)
{
    SigDependenciesGraph g(false);
    g.mapself(L);
    return g.getGraph();
}

/**
 * @brief Compute the full Graph (all dependencies) of a list of signals
 *
 * @param L list of signals
 * @return digraph<Tree>
 */
digraph<Tree> fullGraph(Tree L)
{
    SigDependenciesGraph g(true);
    g.mapself(L);
    return g.getGraph();
}

/**
 * @brief Compute in which order the list of signals L should be compiled
 *
 * @param L a list of signals
 * @return std::vector<Tree> The first element of the vector is the first signal to compile
 */
std::vector<Tree> compilationOrder(Tree L)
{
    digraph<Tree> G = immediateGraph(L);
    return serialize(G);
}
