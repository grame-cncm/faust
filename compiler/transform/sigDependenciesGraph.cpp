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
