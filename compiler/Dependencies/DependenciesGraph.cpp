#include "DependenciesGraph.hh"
#include "DependenciesAudit.hh"
#include "clkEnvInference.hh"
#include "ppsig.hh"
#include "tracer.hh"

// DEBUG: Global map to track which graph each signal belongs to
// static std::map<Tree, const void*> gSignalToGraph;

// DEBUG: Helper to track signal insertion into graphs
// static void trackSignalInsertion(Tree sig, const digraph<Tree>& graph)
// {
//     const void* graphAddr = reinterpret_cast<const void*>(&graph);
//     auto        it        = gSignalToGraph.find(sig);
//
//     if (it != gSignalToGraph.end()) {
//         // Signal was already inserted - check if it's in a different graph
//         if (it->second != graphAddr) {
//             std::cerr << "\n*** DUPLICATE SIGNAL IN DIFFERENT GRAPHS ***" << std::endl;
//             std::cerr << "Signal " << sig << " of clkEnv " << ClkEnvInference::getClkEnv(sig)
//                       << " is being added to graph at address: " << graphAddr << std::endl;
//             std::cerr << "But it was already in a different graph at address: " << it->second
//                       << std::endl;
//             std::cerr << "*** END DUPLICATE ***\n" << std::endl;
//         }
//         // If same graph, it's fine - just multiple insertions (edges) in the same graph
//     } else {
//         // First time seeing this signal - record which graph it belongs to
//         gSignalToGraph[sig] = graphAddr;
//     }
// }

/**
 * @brief Recursively adds dependencies to the dependency graph for a given signal.
 *
 * This function traverses the signal tree, identifying dependencies and adding them to the
 * provided directed graph. It handles external signals, control signals, and signals that
 * require a separate subgraph for scheduling.
 *
 * @param curClkEnv The current clock environment.
 * @param visited A set of already visited signals to prevent infinite recursion.
 * @param subgraphs A map to store subgraphs for signals that require them.
 * @param externals A set to store external signals.
 * @param controls A set to store control signals.
 * @param graph The directed graph to which dependencies are added.
 * @param curSig The current signal being processed.
 */
static void addDependencies(const Tree& curClkEnv, std::set<Tree>& visited,
                            std::map<Tree, digraph<Tree>>& subgraphs, std::set<Tree>& externals,
                            std::set<Tree>& controls, digraph<Tree>& graph, const Tree& curSig)
{
    // Skip signals that have already been visited
    if (visited.find(curSig) != visited.end()) {
        return;
    }

    // Handle signals that are external to the current clock environment
    if (isControl(curSig)) {
        controls.insert(curSig);
        return;
    }

    if (isExternal(curClkEnv, curSig)) {
        externals.insert(curSig);
        return;
    }

    // Mark the signal as visited
    visited.insert(curSig);

    // Get immediate and delayed dependencies of the signal
    auto [immediate, delayed] = getSignalDependencies(curSig);

    // Handle signals that require a subgraph. The clock of the subgraph is sigClocked to
    // keep track of the clock environment needed inside the subgraph.
    // In other words: clockedClk = sigClocked(subClkEnv, realSubClk)
    if (Tree clockedClk; needSubGraph(curSig, clockedClk)) {
        faustassert(delayed.empty());

        Tree subClkEnv, realSubClk;
        faustassert(isSigClocked(clockedClk, subClkEnv, realSubClk));
        // Clock env from the clock signal

        // std::cerr << "DEBUG: Creating subgraph for signal " << curSig << std::endl;

        std::set<Tree> X{realSubClk};  // dependencies external to the subgraph
        digraph<Tree>& G = subgraphs[curSig];
        for (Tree s : immediate) {
            if (s != clockedClk) {  // the clock does not belong to the subgraph
                addDependencies(subClkEnv, visited, subgraphs, X, controls, G, s);
            }
        }

        for (Tree s : X) {
            if (isExternal(curClkEnv, s)) {
                externals.insert(s);
            } else if (isControl(s)) {
                controls.insert(s);
            } else {
                // DEBUG: trackSignalInsertion(curSig, graph);
                graph.add(curSig, s);
                addDependencies(curClkEnv, visited, subgraphs, externals, controls, graph, s);
            }
        }
        return;
    }

    // Handle signals that do not require a subgraph
    // DEBUG: trackSignalInsertion(curSig, graph);
    graph.add(curSig);
    for (Tree ids : immediate) {
        if (isExternal(curClkEnv, ids)) {
            externals.insert(ids);
        } else if (isControl(ids)) {
            controls.insert(ids);
        } else {
            graph.add(curSig, ids);
            addDependencies(curClkEnv, visited, subgraphs, externals, controls, graph, ids);
        }
    }
    for (Tree dds : delayed) {
        if (isExternal(curClkEnv, dds)) {
            externals.insert(dds);
        } else if (isControl(dds)) {
            controls.insert(dds);
        } else {
            addDependencies(curClkEnv, visited, subgraphs, externals, controls, graph, dds);
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
    // DEBUG: trackSignalInsertion(sig, graph);
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
    // DEBUG: Clear the global tracking map for this new graph construction
    // gSignalToGraph.clear();

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

    digraph<Tree> ctrlGraph;

    for (Tree s : controls) {
        simpleAddDependencies(ctrlGraph, s);
    }

    // Audit the graph before returning
    Hgraph hg = {signalList, ctrlGraph, sigToGraph};
    // DEBUG: auditHgraph(hg);

    // DEBUG: Test that each OD/US/DS signal has a unique clkEnv
    // ClkEnvInference::testClkEnvUniqueness(hg);

    // Compute schedules
    return hg;
}
