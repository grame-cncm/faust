#include "sigDependenciesGraph.hh"
#include "ppsig.hh"
#include "signals.hh"
#include "sigtyperules.hh"

#undef TRACE
/**
 * @brief A signal visitor that builds a graph of dependencies
 * when full is true, the graph contains all dependencies,
 * otherwise it contains only immediate dependencies.
 */
class SigDependenciesGraph : public SignalVisitor {
   protected:
    digraph<Tree, CTreeComparator> fGraph;
    bool                           fFullGraph;

   public:
    SigDependenciesGraph(bool full) : SignalVisitor(), fFullGraph(full)
    {
        fTrace   = false;
        fMessage = "SigDependenciesGraph";
    }

    digraph<Tree, CTreeComparator> getGraph() { return fGraph; }

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
#ifdef TRACE
    std::cerr << "Visiting: " << t << " : " << ppsig(t, 10) << "\n";
#endif

    fGraph.add(t);

    {
        Tree w;
        if (int i; isProj(t, &i, w)) {
            // The immediate dependency of a projection is
            // its definition
            Tree id, le;
            faustassert(isRec(w, id, le));
            Tree d = nth(le, i);
            fGraph.add(t, d, 0);
            self(d);
            return;
        }
    }

    if (Tree x, y; isSigDelay(t, x, y)) {
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
        return;
    }

    if (Tree x; isSigDelay1(t, x)) {
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
        return;
    }

    if (tvec V; isSigFIR(t, V)) {
        // Structure: FIR[X,C0,C1,C2,...]
        // Semantics: T = C0.X + C1.X@1 + C2.X@2 + ...
        // Immediate dependencies are X (if C0!=0) and the Ci != 0
        // The full depenecies also include X

        // Check well formed FIR
        faustassert(V.size() >= 2);

        // All non-zero coefs are immediate dependencies
        int dmin = INT32_MAX;  // the minimum delay
        for (unsigned int i = 1; i < V.size(); i++) {
            if (!isZero(V[i])) {
                // All non-zero coefs are immediate dependencies
                fGraph.add(t, V[i], 0);
                // the first non-zero coef determines the delay of the input signal of the FIR
                dmin = std::min(dmin, int(i - 1));
            }
        }

        // Check we have a valid FIR with at least one non-zero coef
        faustassert(dmin<INT32_MAX);

        // Is the input signal of the FIR an immediate dependency?
        if (fFullGraph || (dmin == 0)) {
            fGraph.add(t, V[0], dmin);
        }

        // Compute the dependencies of the sub expressions
        for (auto s : V) {
            if (!isZero(s)) {
                self(s);
            }
        }

        return;
    }

    if (tvec V; isSigIIR(t, V)) {
        // Structure: IIR[nil,X,C0,C1,c2,...] with C0=0
        // Semantics: T = X + C0.T@0 + c1.T@1 + c2.T@2 + ...
        // Immediate dependencies are X and the Ci != 0
        // Full dependencies include T->T@i

        // Check well formed IIR
        faustassert(V.size() >= 3);
        faustassert(isZero(V[2]));

        // Compute the minimal dependency to itself (the first Ci != 0)
        int dmin = INT32_MAX;  // the minimum delay
        for (unsigned int i = 2; i < V.size(); i++) {
            if (!isZero(V[i])) {
                // All non-zero coefs are immediate dependencies
                fGraph.add(t, V[i], 0);
                // the first non-zero coef determines the delay of the input signal of the FIR
                dmin = std::min(dmin, int(i - 2));
            }
        }

        // Check we have a valid IIR
        faustassert(dmin > 0);
        faustassert(dmin < INT32_MAX);

        // Add the input signal has an immediate dependency
        fGraph.add(t, V[1], 0); 

        // If full graph request, add the recursive dependencies to itself
        if (fFullGraph) {
            fGraph.add(t, t, dmin);
        }

        // Compute the dependencies of the sub expressions
        for (auto s : V) {
            if (!isNil(s) && !isZero(s)) {
                self(s);
            }
        }
        return;
    }

    if (Tree tbl, ri; isSigRDTbl(t, tbl, ri)) {
        // special case for tables. We can't compile the content without knowing the context
        Tree size, gen, wi, ws;
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
        return;
    }

    if (Tree size, gen, wi, ws; isSigWRTbl(t, size, gen, wi, ws)) {
        // not supposed to happen
        faustassert(false);
        return;
    }

    // general case
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

/**
 * @brief Compute the immediate Graph (containing only immediate dependencies)
 * of a list of signals
 *
 * @param L list of signals
 * @return digraph<Tree, CTreeComparator>
 */
digraph<Tree, CTreeComparator> immediateGraph(Tree L)
{
    SigDependenciesGraph g(false);
    g.mapself(L);
    return g.getGraph();
}

/**
 * @brief Compute the full Graph (all dependencies) of a list of signals
 *
 * @param L list of signals
 * @return digraph<Tree, CTreeComparator>
 */
digraph<Tree, CTreeComparator> fullGraph(Tree L)
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
    digraph<Tree, CTreeComparator> G = immediateGraph(L);
    return serialize(G);
}
