/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include "rewriteRule.hh"
#include <algorithm>
#include <sstream>
#include "exception.hh"
#include "signals/ppsig.hh"

using namespace std;

// Helper function to get a pointer representation of a signal
static string ptrToString(Tree signal)
{
    stringstream ss;
    ss << signal;
    return ss.str();
}

// Helper function to get a string representation of a signal for debug
static string signalToString(Tree signal)
{
    // Use ppsig for proper signal pretty-printing
    stringstream ss;
    ss << ppsig(signal);
    return ss.str();
}

// Helper function to join strings with a delimiter
static string join(const vector<string>& elements, const string& delimiter)
{
    if (elements.empty()) {
        return "";
    }

    stringstream ss;
    ss << elements[0];
    for (size_t i = 1; i < elements.size(); ++i) {
        ss << delimiter << elements[i];
    }
    return ss.str();
}

//------------------------------------------------------------------------------
// Normalize implementation
//------------------------------------------------------------------------------

Normalize::Normalize(vector<unique_ptr<RewriteRule>> rules)
    : fRules(std::move(rules)), fDebugLevel(DebugLevel::NONE), fDebugOutput(&std::cerr)
{
}

Tree Normalize::operator()(Tree signal)
{
    // Check cache first to avoid recomputation
    if (Tree cached; fCache.get(signal, cached)) {
        if (fDebugLevel >= DebugLevel::VERBOSE) {
            *fDebugOutput << "[CACHED] " << ptrToString(signal) << " -> " << ptrToString(cached)
                          << endl;
        }
        return cached;
    }

    const int MAX_ITERATIONS = 1000;

    Tree           originalSignal = signal;
    Tree           currentSignal  = signal;
    vector<Tree>   history;
    vector<string> appliedRules;

    history.push_back(currentSignal);

    // Apply rules until fixpoint, cycle, or max iterations
    for (int iteration = 0; iteration < MAX_ITERATIONS; ++iteration) {
        bool ruleApplied = false;

        // Try each rule in order
        for (auto& rule : fRules) {
            if (auto result = (*rule)(currentSignal)) {
                appliedRules.push_back(rule->getRuleName());
                currentSignal = *result;

                // Cycle detection
                auto cyclePos = find(history.begin(), history.end(), currentSignal);
                if (cyclePos != history.end()) {
                    int cycleStart = distance(history.begin(), cyclePos);

                    // Debug output before assert
                    if (fDebugLevel >= DebugLevel::BASIC) {
                        *fDebugOutput << "CYCLE: " << ptrToString(originalSignal) << " -["
                                      << join(appliedRules, ",") << "]-> "
                                      << ptrToString(currentSignal) << " (cycle starts at rule "
                                      << cycleStart << ")" << endl;
                    }

                    faustassert(false);
                }

                history.push_back(currentSignal);
                ruleApplied = true;
                break;  // Restart from first rule after any change
            }
        }

        if (!ruleApplied) {
            // Normal form reached
            bool isTransformation = (originalSignal != currentSignal);
            bool showResult       = (fDebugLevel >= DebugLevel::BASIC && isTransformation) ||
                              (fDebugLevel >= DebugLevel::VERBOSE);

            if (showResult) {
                *fDebugOutput << ptrToString(originalSignal) << " -[" << join(appliedRules, ",")
                              << "]-> " << ptrToString(currentSignal) << endl;

                if (fDebugLevel >= DebugLevel::DETAILED && isTransformation) {
                    *fDebugOutput << "  input:  " << ptrToString(originalSignal) << " "
                                  << signalToString(originalSignal) << endl;
                    *fDebugOutput << "  output: " << ptrToString(currentSignal) << " "
                                  << signalToString(currentSignal) << endl;
                } else if (fDebugLevel >= DebugLevel::VERBOSE && !isTransformation) {
                    *fDebugOutput << "  signal: " << ptrToString(originalSignal) << " "
                                  << signalToString(originalSignal) << endl;
                }
            }

            // Cache the result
            fCache.set(originalSignal, currentSignal);
            return currentSignal;
        }
    }

    // Maximum iterations reached
    if (fDebugLevel >= DebugLevel::BASIC) {
        *fDebugOutput << "MAX_ITER: " << ptrToString(originalSignal) << " -["
                      << join(appliedRules, ",") << "...]-> " << ptrToString(currentSignal) << endl;
    }

    faustassert(false);
    return currentSignal;
}

void Normalize::setDebugLevel(DebugLevel level)
{
    fDebugLevel = level;
}

void Normalize::setDebugOutput(ostream& output)
{
    fDebugOutput = &output;
}
