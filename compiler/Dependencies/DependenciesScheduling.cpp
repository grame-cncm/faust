#include "DependenciesScheduling.hh"

/**
 * @brief Converts a hierarchical graph (Hgraph) to a hierarchical schedule (Hsched).
 *
 * This function takes a hierarchical graph and a scheduling function as input, and
 * produces a hierarchical schedule by applying the scheduling function to each
 * subgraph in the hierarchical graph.
 *
 * @param hg The hierarchical graph to convert.
 * @param f The scheduling function to apply to each subgraph.
 * @return A hierarchical schedule representing the scheduled graph.
 */
static Hsched hgraph2hsched(const Hgraph& hg, const SchedulingFunction& f)
{
    Hsched rs;

    rs.outSigList = hg.outSigList;
    rs.controls   = f(hg.controls);
    for (const auto& [sig, graph] : hg.siggraph) {
        rs.sigsched[sig] = f(graph);
    }
    return rs;
}

/**
 * @brief Computes a hierarchical schedule for a list of signals.
 *
 * This function takes a list of signals and a scheduling function as input, and
 * computes a hierarchical schedule by first creating a hierarchical graph from the
 * list of signals, and then converting the hierarchical graph to a hierarchical
 * schedule using the provided scheduling function.
 *
 * @param signalList The list of signals to schedule.
 * @param f The scheduling function to apply to each subgraph.
 * @return A hierarchical schedule representing the scheduled signals.
 */
Hsched scheduleSigList(Tree signalList, const SchedulingFunction& f)
{
    Hgraph hg = dependenciesGraphs(signalList);
    Hsched hs = hgraph2hsched(hg, f);
    return hs;
}