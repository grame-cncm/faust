#include "DependenciesGraph.hh"
#include "ppsig.hh"
#include "tracer.hh"

/**
 * @brief Recursively adds dependencies to the dependency graph for a given signal.
 *
 * This function traverses the signal tree, identifying dependencies and adding them to the
 * provided directed graph. It handles external signals, control signals, and signals that
 * require a separate subgraph for scheduling.
 *
 * @param curclkenv The current clock environment.
 * @param visited A set of already visited signals to prevent infinite recursion.
 * @param subgraphs A map to store subgraphs for signals that require them.
 * @param externals A set to store external signals.
 * @param controls A set to store control signals.
 * @param graph The directed graph to which dependencies are added.
 * @param cursig The current signal being processed.
 */
static void addDependencies(const Tree& curclkenv, std::set<Tree>& visited,
                            std::map<Tree, digraph<Tree>>& subgraphs, std::set<Tree>& externals,
                            std::set<Tree>& controls, digraph<Tree>& graph, const Tree& cursig)
{
    // Handle signals that are external to the current clock environment
    if (isExternal(curclkenv, cursig)) {
        externals.insert(cursig);
        return;
    }

    // Handle signals that are external to the current clock environment
    if (isControl(cursig)) {
        controls.insert(cursig);
        return;
    }

    // Skip signals that have already been visited
    if (visited.find(cursig) != visited.end()) {
        return;
    }

    // Mark the signal as visited
    visited.insert(cursig);

    // handle double clocked signals internal and external
    // cursig = sigClocked(curclkenv,sigClocked(extclkenv,s2))
    if (Tree cei, cex, s1, s2; isSigClocked(cursig, cei, s1) && (cei == curclkenv) &&
                               isSigClocked(s1, cex, s2) && (cex != curclkenv)) {
        graph.add(cursig);
        externals.insert(s1);
        return;
    }
    // Handle signals that are constant or control rate
    Type ty = getCertifiedSigType(cursig);
    if ((ty->variability() < kSamp)) {
        std::cerr << "\n***Constant or control signals added to control: " << ppsig(cursig)
                  << std::endl;
        controls.insert(cursig);
        return;
    }

    // Get immediate and delayed dependencies of the signal
    auto [immediate, delayed] = getSignalDependencies(cursig);

    // Handle signals that require a subgraph. The clock of the subgraph is sigClocked to
    // keep track of the clock environment needed inside the subgraph.
    // In other words: clockedClk = sigClocked(subClkenv, realSubClk)
    if (Tree clockedClk; needSubGraph(cursig, clockedClk)) {
        faustassert(delayed.empty());

        Tree subClkenv, realSubClk;  // clockedClk = sigClocked(subClkenv, realSubClk);
        faustassert(
            isSigClocked(clockedClk, subClkenv, realSubClk));  // Clock env from the clock signal

        std::set<Tree> X{realSubClk};  // dependencies external to the subgraph
        digraph<Tree>& G = subgraphs[cursig];
        for (Tree s : immediate) {
            if (s != clockedClk) {  // the clock does not belong to the subgraph
                addDependencies(subClkenv, visited, subgraphs, X, controls, G, s);
            }
        }
        // graph.add(cursig, realSubClk);

        for (Tree s : X) {
            if (isExternal(curclkenv, s)) {
                externals.insert(s);
            } else if (isControl(s)) {
                controls.insert(s);
            } else {
                graph.add(cursig, s);
                addDependencies(curclkenv, visited, subgraphs, externals, controls, graph, s);
            }
        }
        return;
    }

    // Handle signals that do not require a subgraph
    graph.add(cursig);
    for (Tree ids : immediate) {
        if (isExternal(curclkenv, ids)) {
            externals.insert(ids);
        } else if (isControl(ids)) {
            controls.insert(ids);
        } else {
            graph.add(cursig, ids);
            addDependencies(curclkenv, visited, subgraphs, externals, controls, graph, ids);
        }
    }
    for (Tree dds : delayed) {
        if (isExternal(curclkenv, dds)) {
            externals.insert(dds);
        } else if (isControl(dds)) {
            controls.insert(dds);
        } else {
            addDependencies(curclkenv, visited, subgraphs, externals, controls, graph, dds);
        }
    }
}

/**
 * @brief Adds dependencies to the dependency graph for a given signal (simple version).
 *
 * This function adds dependencies to the provided directed graph. It is a simplified
 * version of addDependencies that does not handle external signals, control signals,
 * or signals that require a separate subgraph for scheduling.
 *
 * @param graph The directed graph to which dependencies are added.
 * @param sig The signal being processed.
 */
static void simpleAddDependencies(digraph<Tree>& graph, Tree sig)
{
    // Get immediate and delayed dependencies of the signal
    auto [immediate, delayed] = getSignalDependencies(sig);
    faustassert(delayed.empty());

    // Handle signals that do not require a subgraph
    graph.add(sig);
    for (Tree ids : immediate) {
        graph.add(sig, ids);
        simpleAddDependencies(graph, ids);
    }
}

/**
 * @brief Creates a hierarchical dependency graph for a list of signals.
 *
 * This function traverses the list of signals, adding dependencies to the graph and
 * creating subgraphs as needed. It identifies external signals and control signals,
 * and ensures that all dependencies are properly accounted for.
 *
 * @param signalList The list of signals for which to create the dependency graph.
 * @return A structure containing the list of output signals, the control graph, and a map
 *         of signals to their corresponding dependency graphs.
 */
Hgraph dependenciesGraphs(Tree signalList)
{
    std::set<Tree>                visited;
    std::map<Tree, digraph<Tree>> sigToGraph;

    // Traverse the list of output signals
    std::set<Tree> externals;
    std::set<Tree> controls;
    for (Tree sl = signalList; isList(sl); sl = tl(sl)) {
        addDependencies(gGlobal->nil, visited, sigToGraph, externals, controls,
                        sigToGraph[signalList], hd(sl));
    }
    // we are not supposed to have external signals left
    faustassert(externals.size() == 0);

    std::set<Tree> neoExternals;
    std::set<Tree> neoControls;
    digraph<Tree>  ctrlGraph;

    for (Tree s : controls) {
        simpleAddDependencies(ctrlGraph, s);
    }
    // we are not supposed to have externals and controls left
    faustassert(neoExternals.size() == 0);
    faustassert(neoControls.size() == 0);

    // Compute schedules
    return {signalList, ctrlGraph, sigToGraph};
}
