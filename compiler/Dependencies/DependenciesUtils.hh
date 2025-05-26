#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include "signals.hh"
#include "sigtyperules.hh"

/**
 * @brief Checks if a signal requires a separate subgraph for scheduling.
 *
 * This is typically the case for on-demand signals (OD, US, DS).
 *
 * @param sig The signal to check.
 * @param clk Reference to a Tree where the clock of the subgraph will be stored if needed.
 * @return True if a subgraph is needed, false otherwise.
 */
bool needSubGraph(Tree sig, Tree& clk);

/**
 * @brief Checks if a signal is external to the current clock environment.
 *
 * A signal is considered external if it belongs to a different clock domain.
 *
 * @param clkenv The current clock environment.
 * @param sig The signal to check.
 * @return True if the signal is external, false otherwise.
 */

bool isExternal(Tree clkenv, Tree sig);

/**
 * @brief Checks if a signal is a control signal.
 *
 * Control signals have a variability less than kSamp and are typically
 * used for parameters or control logic.
 *
 * @param sig The signal to check.
 * @return True if the signal is a control signal, false otherwise.
 */
bool isControl(Tree sig);

/**
 * @brief Extracts the immediate and delayed subsignals of a given signal.
 *
 * This function analyzes the signal and separates its dependencies into
 * two categories: immediate and delayed.
 *
 * @param sig The signal to analyze.
 * @return A pair containing two vectors:
 *         - first: vector of immediate subsignals.
 *         - second: vector of delayed subsignals.
 */
std::pair<std::vector<Tree>, std::vector<Tree>> getSignalDependencies(Tree sig);
