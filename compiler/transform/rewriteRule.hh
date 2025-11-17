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

#ifndef __REWRITERULE__
#define __REWRITERULE__

#include <functional>
#include <optional>
#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include "global.hh"
#include "property.hh"
#include "tree.hh"

using namespace std;

//------------------------------------------------------------------------------
// Debug levels for rule tracing
//------------------------------------------------------------------------------
enum class DebugLevel {
    NONE = 0,      // No debug output
    BASIC = 1,     // Basic rule application info
    DETAILED = 2,  // Detailed transformation info
    VERBOSE = 3    // Full trace with signal details
};

//------------------------------------------------------------------------------
// RewriteRule: Base class for signal rewrite rules
//------------------------------------------------------------------------------
// Mathematical framework for signal rewriting:
//
// A rewrite rule R is a partial function: Tree -> Optional<Tree>
//   R(s) = nullopt     if rule doesn't apply to signal s
//   R(s) = Some(s')    if rule transforms s into s'
//
// Each rule integrates its own cache for memoization.
//------------------------------------------------------------------------------

/**
 * @brief Base class for signal rewrite rules
 * 
 * A rewrite rule is a callable object that can transform a signal.
 * It returns nullopt if the rule doesn't apply, or the transformed signal.
 * Each rule manages its own cache for performance.
 */
class RewriteRule {
protected:
    property<optional<Tree>> fCache;

public:
    virtual ~RewriteRule() = default;
    
    /**
     * @brief Get the name of this rule for debugging purposes
     * 
     * @return string The rule name (should be overridden by subclasses)
     */
    virtual string getRuleName() const { return "UnnamedRule"; }
    
    /**
     * @brief Apply the rewrite rule to a signal
     * 
     * @param signal The input signal to potentially transform
     * @return nullopt if rule doesn't apply, transformed signal otherwise
     */
    virtual optional<Tree> operator()(Tree signal) = 0;
    
};

//------------------------------------------------------------------------------
// Normalize: Signal normalizer using rewrite rules
//------------------------------------------------------------------------------
// Mathematical framework for signal normalization:
//
// Given a set of rules R = {R1, R2, ..., Rn}, the normalizer N computes
// the fixpoint of rule application:
//
//   N(s) = fixpoint(s) where fixpoint applies rules until convergence
//
// The result is a signal in "normal form" - no rule can transform it further.
//------------------------------------------------------------------------------

/**
 * @brief Signal normalizer using a set of rewrite rules
 * 
 * Applies rewrite rules repeatedly until no more transformations are possible.
 * The result is a signal in "normal form".
 */
class Normalize {
private:
    vector<unique_ptr<RewriteRule>> fRules;
    property<Tree> fCache;
    DebugLevel fDebugLevel;
    ostream* fDebugOutput;

public:
    /**
     * @brief Constructor with rule instances - convenient syntax
     * 
     * Usage: Normalize normalize(R1(), R2(), R3());
     * 
     * @param rules Rule instances (automatically wrapped in unique_ptr)
     */
    template<typename... Rules>
    Normalize(Rules&&... rules) : fRules(), fDebugLevel(DebugLevel::NONE), fDebugOutput(&std::cerr) {
        (fRules.push_back(make_unique<Rules>(std::forward<Rules>(rules))), ...);
    }
    
    /**
     * @brief Constructor with rewrite rules vector
     * 
     * @param rules Vector of rewrite rules (takes ownership)
     */
    Normalize(vector<unique_ptr<RewriteRule>> rules);
    
    /**
     * @brief Normalize a signal to its normal form
     * 
     * Applies all rewrite rules repeatedly until no more changes occur.
     * 
     * @param signal The input signal to normalize
     * @return Tree The normalized signal in normal form
     */
    Tree operator()(Tree signal);
    
    /**
     * @brief Set debug level for tracing rule applications
     * 
     * @param level The debug level to use
     */
    void setDebugLevel(DebugLevel level);
    
    /**
     * @brief Set debug output stream
     * 
     * @param output The output stream for debug messages
     */
    void setDebugOutput(ostream& output);
};

#endif