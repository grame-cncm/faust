#include "sigDependenciesGraph.hh"
#include "ppsig.hh"
#include "sigRecursiveDependencies.hh"
#include "signals.hh"
#include "sigtyperules.hh"
#include "DirectedGraphAlgorythm.hh"
#include <fstream>

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
    bool          fLimitOndemand = false;  // don't go beyond tempvar signals

   public:
    SigDependenciesGraph(bool full, bool limit)
        : SignalVisitor(), fFullGraph(full), fLimitOndemand(limit)
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
        faustassert(dmin < INT32_MAX);

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

    if (tvec V; isSigSum(t, V)) {
        // We only have immediate dependencies
        for (auto s : V) {
            fGraph.add(t, s, 0);
        }
        for (auto s : V) {
            self(s);
        }
        return;
    }

    if (Tree x; isSigTempVar(t, x)) {
        fGraph.add(t, x, 0);
        if (!fLimitOndemand) {
            // We go beyond tempvar signals if we are not in ondemand mode
            self(x);
        }
        return;
    }

    if (Tree x; isSigPermVar(t, x)) {
        fGraph.add(t, x, 0);
        self(x);
        return;
    }

    if (Tree x, n; isSigZeroPad(t, x, n)) {
        fGraph.add(t, x, 0);
        self(x);
        return;
    }

    // if (Tree x, y; isSigSeq(t, x, y)) {
    //     // Indicate a dependency to x (typically an ondemand).
    //     fGraph.add(t, y, 0);
    //     fGraph.add(y, x, 0);  // we need x to compile y
    //     self(x);
    //     self(y);
    //     return;
    // }

    if (Tree x, y; isSigSeq(t, x, y)) {
        // Indicate a dependency to x (typically an ondemand).
        // Because y is a result of x, no need to add a dependency to y
        fGraph.add(t, x, 0);
        self(x);
        return;
    }

    if (tvec V; isSigOD(t, V) || isSigUS(t, V) || isSigDS(t, V)) {
        // V = H,Y1,...
        // immediate dependencies are H only
        if (V.size() > 0) {
            fGraph.add(t, V[0], 0);  // H is the clock
            self(V[0]);
        }
        return;
    }

    if (Tree c, y; isSigClocked(t, c, y)) {
        // the clock c is here to differentiate various version of y for delays
        fGraph.add(t, y, 0);
        self(y);
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
 * @return digraph<Tree>
 */
digraph<Tree> immediateGraph(Tree L)
{
    SigDependenciesGraph g(false, false);
    g.mapself(L);
    return g.getGraph();
}

/**
 * @brief Compute the immediate Graph (containing only immediate dependencies)
 * of a list of signals and not going beyond tempvar signals
 *
 * @param L list of signals
 * @return digraph<Tree>
 */
digraph<Tree> ondemandGraph(const tvec& signals)
{
    SigDependenciesGraph g(false, true);
    for (Tree s : signals) {
        g.self(s);
    }
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
    SigDependenciesGraph g(true, false);
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

/**
 * @brief Compute in which order the list of signals L should be compiled
 *
 * @param L a list of signals
 * @return std::vector<Tree> The first element of the vector is the first signal to compile
 */
std::vector<Tree> ondemandCompilationOrder(const tvec& signals)
{
    digraph<Tree> G = ondemandGraph(signals);
    return serialize(G);
}

/**
 * @brief Check if a signal is a projection and get its definition
 *
 * @param sig the signal to check
 * @param def reference to store the definition if found
 * @return true if sig is a projection, false otherwise
 */
static bool hasProjDefinition(Tree sig, Tree& def)
{
    int  i;
    Tree w;

    // Check if sig is a projection
    if (isProj(sig, &i, w)) {
        // Get the definition
        Tree id, le;
        faustassert(isRec(w, id, le));
        def = nth(le, i);
        return true;
    }

    return false;
}

/**
 * @brief Visit recursive definitions and build the recursion graph
 *
 * @param graph the graph being constructed
 * @param visited set of already visited signals
 * @param parent the recursive signal currently being explored (or nil at start)
 * @param sig the signal to visit
 */
static void visitRecDefinitions(digraph<Tree>& graph, std::set<Tree>& visited, Tree parent,
                                Tree sig)
{
    if (Tree def; hasProjDefinition(sig, def)) {
        // Case (a): sig is a projection
        graph.add(parent, sig, 0);

        if (visited.find(sig) == visited.end()) {
            visited.insert(sig);
            visitRecDefinitions(graph, visited, sig, def);
        }
    } else {
        // Case (b): sig is not a projection
        if (visited.find(sig) == visited.end()) {
            visited.insert(sig);

            tvec subsignals;
            (void)getSubSignals(sig, subsignals, true);

            for (auto subsig : subsignals) {
                visitRecDefinitions(graph, visited, parent, subsig);
            }
        }
    }
}

/**
 * @brief Compute the graph of dependencies between recursive definition of a list of signals
 *
 * @param L list of signals
 * @return digraph<Tree>
 */
digraph<Tree> recursionGraph(Tree L)
{
    digraph<Tree>  graph;
    std::set<Tree> visited;

    // Iterate through all signals in the list
    Tree current = L;
    while (!isNil(current)) {
        Tree sig = hd(current);
        visitRecDefinitions(graph, visited, gGlobal->nil, sig);
        current = tl(current);
    }

    return graph;
}

/**
 * @brief Print recursion graph in DOT format
 *
 * @param graph the recursion graph
 * @param filename output filename
 */
void printRecursionGraphDot(const digraph<Tree>& graph, const std::string& filename)
{
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: cannot open file " << filename << std::endl;
        return;
    }
    
    // Find degenerate recursions
    std::set<Tree> degenerateRecursions = analyzeDegenerateRecursions(graph);
    
    file << "digraph RecursionGraph {\n";
    file << "    rankdir=TB;\n";
    file << "    node [shape=box];\n\n";
    
    // Get all nodes from the graph
    const std::set<Tree>& nodes = graph.nodes();
    
    // Print nodes with labels (skip nil)
    for (Tree node : nodes) {
        if (node != gGlobal->nil) {
            int i;
            Tree w;
            faustassert(isProj(node, &i, w));
            Tree id, le;
            faustassert(isRec(w, id, le));
            std::string nodeName = std::string(tree2str(id)) + "_" + std::to_string(i);
            
            // Color degenerate recursions differently
            if (degenerateRecursions.find(node) != degenerateRecursions.end()) {
                file << "    \"" << node << "\" [label=\"" << nodeName << "\" fillcolor=red style=filled];\n";
            } else {
                file << "    \"" << node << "\" [label=\"" << nodeName << "\"];\n";
            }
        }
    }
    
    file << "\n";
    
    // Print edges (skip edges from/to nil)
    const auto& connections = graph.connections();
    for (const auto& fromPair : connections) {
        Tree from = fromPair.first;
        if (from != gGlobal->nil) {
            for (const auto& toPair : fromPair.second) {
                Tree to = toPair.first;
                if (to != gGlobal->nil) {
                    file << "    \"" << from << "\" -> \"" << to << "\";\n";
                }
            }
        }
    }
    
    file << "}\n";
    file.close();
}

/**
 * @brief Analyze a recursion graph to find degenerate recursions
 *
 * A degenerate recursion is a strongly connected component that:
 * - Contains only one recursive projection
 * - Has no connections (not connected to itself)
 *
 * @param graph the recursion graph produced by recursionGraph()
 * @return std::set<Tree> set of degenerate recursive projections
 */
std::set<Tree> analyzeDegenerateRecursions(const digraph<Tree>& graph)
{
    std::set<Tree> degenerateRecursions;
    
    // Transform the graph into a DAG of strongly connected components
    digraph<digraph<Tree>> dag = graph2dag(graph);
    
    // Iterate through each strongly connected component (supernode)
    for (const digraph<Tree>& component : dag.nodes()) {
        const std::set<Tree>& nodes = component.nodes();
        
        // Check if the component contains exactly one node
        if (nodes.size() == 1) {
            Tree singleNode = *nodes.begin();
            
            // Skip nil nodes
            if (singleNode == gGlobal->nil) {
                continue;
            }
            
            // Check if the component has no internal connections
            if (component.destinations(singleNode).empty()) {
                degenerateRecursions.insert(singleNode);
            }
        }
    }
    
    return degenerateRecursions;
}
