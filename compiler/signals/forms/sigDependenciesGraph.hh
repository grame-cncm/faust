#pragma once
#include "DirectedGraph.hh"
#include "DirectedGraphAlgorythm.hh"
#include "signalVisitor.hh"

/**
 * @brief Compute the immediate Graph of a list of signals
 *
 * @param L list of signals
 * @return digraph<Tree>
 */
digraph<Tree> immediateGraph(Tree L);

/**
 * @brief Compute the full Graph of a list of signals
 *
 * @param L list of signals
 * @return digraph<Tree>
 */
digraph<Tree> fullGraph(Tree L);

/**
 * @brief Compute in which order the list of signals L should be compiled
 *
 * @param L a list of signals
 * @return std::vector<Tree> The first element of the vector is the first signal to compile
 */
std::vector<Tree> compilationOrder(Tree L);
