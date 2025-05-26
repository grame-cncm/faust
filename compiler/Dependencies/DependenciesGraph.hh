#pragma once

#include <map>
#include <set>
#include "DependenciesUtils.hh"
#include "DirectedGraph.hh"

/**
 * @brief Represents a hierarchical dependency graph.
 *
 * This structure contains the output signal list, the control graph, and a map of signals
 * to their corresponding dependency graphs.
 */
struct Hgraph {
    Tree outSigList;  ///< The output signals of a circuit and entry point for the siggraph map
    digraph<Tree> controls;  ///< Non sample rate signals that need to be scheduled first
    std::map<Tree, digraph<Tree>> siggraph;  ///< Map of signals to dependency graphs
};

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
Hgraph dependenciesGraphs(Tree signalList);