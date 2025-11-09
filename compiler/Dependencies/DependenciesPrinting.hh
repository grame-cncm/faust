#pragma once

#include <iostream>
#include <map>
#include "DependenciesScheduling.hh"
#include "occurrences.hh"

#pragma once

#include <iostream>
#include <map>
#include "DependenciesScheduling.hh"

/**
 * @brief Prints the hierarchical schedule of signals.
 *
 * @param hs The hierarchical schedule to print.
 */
void printHsched(const Hsched& hs);

/**
 * @brief Prints the hierarchical schedule of signals with max delay information.
 *
 * @param hs The hierarchical schedule to print.
 * @param maxDelays Map of signals to their maximum delays.
 */
void printHschedWithDelays(const Hsched& hs, OccMarkup* OM);

/**
 * @brief Recursively prints the schedule of signals with indentation.
 *
 * @param os The output stream to print to.
 * @param sigSchedules A map of signals to their schedules.
 * @param stepNumbers A map of signals to their step numbers.
 * @param schedule The schedule to print.
 * @param indent The indentation level.
 */
void recPrinting(std::ostream& os, const std::map<Tree, schedule<Tree>>& sigSchedules,
                 const std::map<Tree, int>& stepNumbers, const schedule<Tree>& schedule,
                 int indent);

/**
 * @brief Recursively prints the schedule of signals with indentation and delay information.
 *
 * @param os The output stream to print to.
 * @param sigSchedules A map of signals to their schedules.
 * @param stepNumbers A map of signals to their step numbers.
 * @param maxDelays Map of signals to their maximum delays.
 * @param schedule The schedule to print.
 * @param indent The indentation level.
 */
void recPrintingWithDelays(std::ostream& os, const std::map<Tree, schedule<Tree>>& sigSchedules,
                           const std::map<Tree, int>& stepNumbers, OccMarkup* OM,
                           const schedule<Tree>& schedule, int indent);

/**
 * @brief Prints a signal with step references to the output stream.
 *
 * @param os The output stream to print to.
 * @param sig The signal to print.
 * @param stepNumbers A map of signals to their step numbers.
 * @param OM Occurrence markup object for delay information (can be nullptr).
 */
void printSigWithStepRefs(std::ostream& os, Tree sig, const std::map<Tree, int>& stepNumbers, OccMarkup* OM);

/**
 * @brief Prints a step reference to the output stream.
 *
 * @param os The output stream to print to.
 * @param sig The signal to print.
 * @param stepNumbers A map of signals to their step numbers.
 */
void printStepRefs(std::ostream& os, Tree sig, const std::map<Tree, int>& stepNumbers);

/**
 * @brief Generates a map of signals to their step numbers for scheduling.
 *
 * @param hs The hierarchical schedule to number.
 * @return A map of signals to their step numbers.
 */
std::map<Tree, int> numberSchedule(const Hsched& hs);

/**
 * @brief Recursively numbers the signals in a schedule.
 *
 * @param sigSchedules A map of signals to their schedules.
 * @param stepNumbers A map of signals to their step numbers.
 * @param schedule The schedule to number.
 * @param step The starting step number.
 * @return The updated step number after numbering the signals in the schedule.
 */
int recNumbering(const std::map<Tree, schedule<Tree>>& sigSchedules,
                 std::map<Tree, int>& stepNumbers, const schedule<Tree>& schedule, int step);

/**
 * @brief Prints the clock of a signal to the output stream.
 *
 * @param os The output stream to print to.
 * @param clk The clock to print.
 */
void printClock(std::ostream& os, Tree clk);

/**
 * @brief Generates a DOT graph representation of the hierarchical schedule.
 *
 * @param hs The hierarchical schedule to convert to DOT format.
 * @param os The output stream to write the DOT graph to.
 */
void printHschedDOT(const Hsched& hs, std::ostream& os);

/**
 * @brief Recursively generates DOT nodes and edges for the schedule.
 *
 * @param os The output stream to write to.
 * @param sigSchedules A map of signals to their schedules.
 * @param stepNumbers A map of signals to their step numbers.
 * @param schedule The schedule to convert.
 * @param subgraphName Name for the subgraph (cluster).
 */
void recDOTPrinting(std::ostream& os, const std::map<Tree, schedule<Tree>>& sigSchedules,
                    const std::map<Tree, int>& stepNumbers, const schedule<Tree>& schedule,
                    const std::string& subgraphName);

/**
 * @brief Generates a DOT node representation for a signal.
 *
 * @param os The output stream to write to.
 * @param sig The signal to convert.
 * @param stepNumbers A map of signals to their step numbers.
 */
void printSigDOTNode(std::ostream& os, Tree sig, const std::map<Tree, int>& stepNumbers);

/**
 * @brief Generates DOT edges for signal dependencies.
 *
 * @param os The output stream to write to.
 * @param sig The signal to process.
 * @param stepNumbers A map of signals to their step numbers.
 */
void printSigDOTEdges(std::ostream& os, Tree sig, const std::map<Tree, int>& stepNumbers);