#pragma once

#include <iostream>
#include <map>
#include "DependenciesScheduling.hh"

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
 * @brief Prints a signal with step references to the output stream.
 *
 * @param os The output stream to print to.
 * @param sig The signal to print.
 * @param stepNumbers A map of signals to their step numbers.
 */
void printSigWithStepRefs(std::ostream& os, Tree sig, const std::map<Tree, int>& stepNumbers);

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