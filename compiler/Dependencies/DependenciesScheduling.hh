#pragma once

#include <functional>
#include <map>
#include "DependenciesGraph.hh"
#include "Schedule.hh"

/**
 * @brief Represents a hierarchical schedule of signals.
 *
 * This structure contains the output signal list, the control schedule, and a map of
 * signals to their corresponding schedules.
 */
struct Hsched {
    Tree                           outSigList;
    schedule<Tree>                 controls;
    std::map<Tree, schedule<Tree>> sigsched;
};

/**
 * @brief A strategy function that transforms a graph into a schedule
 */
using SchedulingFunction = std::function<schedule<Tree>(const digraph<Tree>&)>;

/**
 * @brief Computes a hierarchical schedule for a list of signals.
 *
 * This function takes a list of signals and a scheduling function as input, and computes
 * a hierarchical schedule by first creating a hierarchical graph from the list of signals,
 * and then converting the hierarchical graph to a hierarchical schedule using the provided
 * scheduling function.
 *
 * @param signalList The list of signals to schedule.
 * @param f The scheduling function to apply to each subgraph.
 * @return A hierarchical schedule representing the scheduled signals.
 */
Hsched scheduleSigList(Tree signalList, const SchedulingFunction& f);